/**
  *********************************************************************************************************************
  * @file    stm32u5xx_hal_pssi.c
  * @brief   PSSI HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Parallel Synchronous Slave Interface (PSSI) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral State and Errors functions
  *
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

/* Includes ---------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup PSSI
  * @{

# How to use the PSSI HAL module driver

The PSSI HAL driver can be used as follows:

1. Declare a hal_pssi_handle_t handle structure, for example:
   hal_pssi_handle_t hpssi;

2. Initialize the pssix driver with a PSSI HW instance by calling the HAL_PSSI_Init().
   The pssix clock is enabled inside the HAL_PSSI_Init() if USE_HAL_PSSI_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO.
3. Configure the low level hardware (GPIO, CLOCK, NVIC...etc):
    - Enable the pssix interface clock if USE_HAL_PSSI_CLK_ENABLE_MODEL = HAL_CLK_ENABLE_NO
    - PSSI pins configuration
        - Enable the clock for the PSSI GPIOs
        - Configure PSSI pins as alternate function open-drain
    - NVIC configuration if you need to use interrupt process
        - Configure the pssix interrupt priority
        - Enable the NVIC PSSI IRQ Channel
    - DMA Configuration if you need to use DMA process
        - Declare hal_dma_handle_t handles structure for the transmit and receive
        - Enable the DMAx interface clock
        - Configure the DMA handle parameters
        - Configure the DMA Tx and Rx
        - Associate the initialized DMA handle to the hpssi DMA Tx and Rx handle respectively using
        HAL_PSSI_SetTxDMA() or HAL_PSSI_SetRxDMA()
        - Configure the priority and enable the NVIC for the transfer complete interrupt on
          the DMA Tx and Rx

4. Configure the Communication Bus Width,  Control Signals, Input Polarity and Output Polarity
   by calling HAL_PSSI_SetConfig()

   - When using Ready signal in reception process, there might be a data shift in the user reception buffer as follows:
     - @ref HAL_PSSI_BUS_WIDTH_8LINE : One Byte data shift
     - @ref HAL_PSSI_BUS_WIDTH_16LINE : Two Bytes data shift
   - It's recommended to use Data Enable signal to ensure synchronization between the controller and the target.

5. For PSSI IO operations, two operation modes are available within this driver :

  - Polling mode IO operation
    - Transmit an amount of data by byte in blocking mode using HAL_PSSI_Transmit()
    - Receive an amount of data by byte in blocking mode using HAL_PSSI_Receive()

  - DMA mode IO operation
    - Transmit an amount of data in non-blocking mode (DMA) using HAL_PSSI_Transmit_DMA()
    - At transmission end of transfer, HAL_PSSI_TxCpltCallback() is executed and user can
      add his own code by customizing the weak function HAL_PSSI_TxCpltCallback()
    - Receive an amount of data in non-blocking mode (DMA) using HAL_PSSI_Receive_DMA()
    - At reception end of transfer, HAL_PSSI_RxCpltCallback() is executed and user can
      add his own code by customizing the weak function HAL_PSSI_RxCpltCallback()
    - In case of transfer Error, HAL_PSSI_ErrorCallback() function is executed and user can
      add his own code by customizing the weak function HAL_PSSI_ErrorCallback()
    - Abort a PSSI process communication with Polling using HAL_PSSI_Abort()
    - Abort a PSSI process communication with Interrupt using HAL_PSSI_Abort_IT()
    - End of abort process, HAL_PSSI_AbortCpltCallback() is executed and user can
      add his own code by customizing the weak function HAL_PSSI_AbortCpltCallback()

6. Callback registration

  - When the compilation flag USE_HAL_PSSI_REGISTER_CALLBACKS is set to 1, User is allowed to dynamically configure
    the driver callbacks by providing function pointers to be used instead of the weak callback functions.
    Use the following callbacks registration APIs for this purpose:
     - HAL_PSSI_RegisterTxCpltCallback() for transmission end of transfer callback registration.
     - HAL_PSSI_RegisterRxCpltCallback() for reception end of transfer callback registration.
     - HAL_PSSI_RegisterErrorCallback() for error callback registration.
     - HAL_PSSI_RegisterAbortCpltCallback() for abort completion callback registration.
  - These functions take as parameters the HAL peripheral handle and a pointer to the user callback function.

  - When the compilation flag is set to 0 or not defined, the callback registration
    feature is not available and all callbacks are set to the corresponding weak functions.

7. Acquire/Release the HAL PSSI handle
  - When the compilation flag USE_HAL_MUTEX is set to 1, a multi-thread user application is allowed to acquire/take
    the whole PSSI HAL handle in order to execute a transmit or a receive process or a sequence of transmit receive.
    When the given process or sequence ends the user must release the PSSI HAL handle.
  - The HAL Acquire/Release are based on the HAL OS abstraction layer (stm32_hal_os.c/.h osal) :
     - HAL_PSSI_AcquireBus() Allows to acquire/take the HAL PSSI handle.
     - HAL_PSSI_ReleaseBus() Allows to release the HAL PSSI handle.

8. Configuration inside the PSSI driver

Config defines                  | Description           | Default value     | Note
--------------------------------| --------------------- | ----------------- | -----------------------------------
USE_HAL_PSSI_CLK_ENABLE_MODEL   | stm32u5xx_hal_conf.h  | HAL_CLK_ENABLE_NO | Enable the gating of the periph clk
USE_HAL_PSSI_MODULE             | stm32u5xx_hal_conf.h  | 1                 | When set, HAL PSSI module is enabled
USE_HAL_PSSI_DMA                | stm32u5xx_hal_conf.h  | 1                 | Enable DMA code inside PSSI
USE_HAL_PSSI_GET_LAST_ERRORS    | stm32u5xx_hal_conf.h  | 0                 | Enable the get last process error
USE_HAL_PSSI_USER_DATA          | stm32u5xx_hal_conf.h  | 0                 | Enable the set/get user data
USE_HAL_PSSI_REGISTER_CALLBACKS | stm32u5xx_hal_conf.h  | 0                 | Enable the register callbacks assert
USE_HAL_CHECK_PARAM             | stm32u5xx_hal_conf.h  | 0                 | Parameters are checked in runtime
USE_HAL_CHECK_PROCESS_STATE     | stm32u5xx_hal_conf.h  | 0                 | Check/Update the HAL PSSI state
USE_HAL_MUTEX                   | stm32u5xx_hal_conf.h  | 0                 | Enable the acquire/release bus services
USE_ASSERT_DBG_PARAM            | from PreProcessor env | NA                | Enable the params assert
USE_ASSERT_DBG_STATE            | from PreProcessor env | NA                | Enable the state assert
  */

#if defined(USE_HAL_PSSI_MODULE) && (USE_HAL_PSSI_MODULE == 1U)
#if defined(PSSI)
/* Private types ----------------------------------------------------------------------------------------------------*/
/* Private constants ------------------------------------------------------------------------------------------------*/
/** @defgroup PSSI_Private_Constants PSSI Private Constants
  * @{
  */
#define PSSI_MAX_NBYTE_SIZE 0xFFFCU /*!< 64 KB */

#define PSSI_CR_MASK 0xC01C4D60U /*!< Control register mask */
/**
  * @}
  */
/* Private define ---------------------------------------------------------------------------------------------------*/

/** @defgroup PSSI_Private_Define PSSI Private Define
  * @{
  */

/**
  * @brief All States except Init and Idle
  */
#define PSSI_STATE_ALL_ACTIVE (((uint32_t)HAL_PSSI_STATE_TX) \
                               | ((uint32_t)HAL_PSSI_STATE_RX))
/**
  * @brief All States except Init
  */
#define PSSI_STATE_ALL_EXCEPT_INIT (((uint32_t)HAL_PSSI_STATE_IDLE)     \
                                    | ((uint32_t)PSSI_STATE_ALL_ACTIVE) \
                                    | ((uint32_t)HAL_PSSI_STATE_ABORT))
/**
  * @brief All States
  */
#define PSSI_STATE_ALL (((uint32_t)HAL_PSSI_STATE_INIT) \
                        | ((uint32_t)PSSI_STATE_ALL_EXCEPT_INIT))

/**
  * @}
  */
/* Private macros ---------------------------------------------------------------------------------------------------*/
/** @defgroup PSSI_Private_Macros PSSI Private Macros
  * @{
  */
/*! Get PSSI instance from the selected HAL PSSI handle */
#define PSSI_GET_INSTANCE(handle) (PSSI_TypeDef *)((uint32_t)(handle)->instance)

/**
  * @brief  Check whether the PSSI Control signal is valid.
  */
#define IS_PSSI_CONTROL_SIGNAL(control) (((control) == HAL_PSSI_CONTROL_SIGNAL_DE_RDY_DISABLE)          \
                                         || ((control) == HAL_PSSI_CONTROL_SIGNAL_RDY_ENABLE)           \
                                         || ((control) == HAL_PSSI_CONTROL_SIGNAL_DE_ENABLE)            \
                                         || ((control) == HAL_PSSI_CONTROL_SIGNAL_DE_RDY_ALT_ENABLE)    \
                                         || ((control) == HAL_PSSI_CONTROL_SIGNAL_MAP_RDY_BIDIR_ENABLE) \
                                         || ((control) == HAL_PSSI_CONTROL_SIGNAL_RDY_MAP_ENABLE)       \
                                         || ((control) == HAL_PSSI_CONTROL_SIGNAL_DE_MAP_ENABLE)        \
                                         || ((control) == HAL_PSSI_CONTROL_SIGNAL_MAP_DE_BIDIR_ENABLE))

/**
  * @brief  Check whether the PSSI bus Width is valid.
  */
#define IS_PSSI_BUSWIDTH(buswidth) (((buswidth) == HAL_PSSI_BUS_WIDTH_8LINE) \
                                    || ((buswidth) == HAL_PSSI_BUS_WIDTH_16LINE))

/**

  * @brief  Check whether the PSSI Clock Polarity is valid.
  */
#define IS_PSSI_CLOCK_POLARITY(clockpol) (((clockpol) == HAL_PSSI_CLOCK_POLARITY_RX_FALLING_TX_RISING_EDGE) \
                                          || ((clockpol) == HAL_PSSI_CLOCK_POLARITY_RX_RISING_TX_FALLING_EDGE))

/**
  * @brief  Check whether the PSSI Data Enable Polarity is valid.
  */
#define IS_PSSI_DE_POLARITY(depol) (((depol) == HAL_PSSI_DATA_ENABLE_POLARITY_LOW) \
                                    || ((depol) == HAL_PSSI_DATA_ENABLE_POLARITY_HIGH))

/**
  * @brief  Check whether the PSSI Ready Polarity is valid.
  */
#define IS_PSSI_RDY_POLARITY(rdypol) (((rdypol) == HAL_PSSI_READY_POLARITY_LOW) \
                                      || ((rdypol) == HAL_PSSI_READY_POLARITY_HIGH))

/**
  * @brief  Check whether the PSSI Data Width is valid.
  */
#define IS_PSSI_DATAWIDTH(dwidth) (((dwidth) == HAL_PSSI_DATA_WIDTH_8BIT)     \
                                   || ((dwidth) == HAL_PSSI_DATA_WIDTH_16BIT) \
                                   || ((dwidth) == HAL_PSSI_DATA_WIDTH_32BIT))


/**
  * @}
  */
/* Private variables ------------------------------------------------------------------------------------------------*/
/* Private function prototypes --------------------------------------------------------------------------------------*/

/** @defgroup PSSI_Private_Functions PSSI Private Functions
  * @{
  */

__STATIC_INLINE void PSSI_Enable(PSSI_TypeDef *p_instance);
__STATIC_INLINE void PSSI_Disable(PSSI_TypeDef *p_instance);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
__STATIC_INLINE hal_pssi_bus_width_t PSSI_GetBusWidth(const PSSI_TypeDef *p_instance);
#endif /* USE_HAL_CHECK_PARAM */
__STATIC_INLINE void PSSI_SetControlSignal(PSSI_TypeDef *p_instance, const uint32_t control_signal);
__STATIC_INLINE hal_pssi_control_signal_t PSSI_GetControlSignal(const PSSI_TypeDef *p_instance);
__STATIC_INLINE void PSSI_SetDataEnablePolarity(PSSI_TypeDef *p_instance, const uint32_t data_enable_polarity);
__STATIC_INLINE hal_pssi_data_enable_polarity_t PSSI_GetDataEnablePolarity(const PSSI_TypeDef *p_instance);
__STATIC_INLINE void PSSI_SetReadyPolarity(PSSI_TypeDef *p_instance, const uint32_t ready_polarity);
__STATIC_INLINE hal_pssi_ready_polarity_t PSSI_GetReadyPolarity(const PSSI_TypeDef *p_instance);
__STATIC_INLINE void PSSI_SetClockPolarity(PSSI_TypeDef *p_instance, const uint32_t clock_polarity);
__STATIC_INLINE hal_pssi_clock_polarity_t PSSI_GetClockPolarity(const PSSI_TypeDef *p_instance);
#if defined(USE_HAL_PSSI_DMA) && (USE_HAL_PSSI_DMA == 1U)
__STATIC_INLINE void PSSI_DisableDMA(PSSI_TypeDef *p_instance);
__STATIC_INLINE uint32_t PSSI_IsEnabledDMA(const PSSI_TypeDef *p_instance);
#endif /* USE_HAL_PSSI_DMA */
__STATIC_INLINE void PSSI_WriteData8(PSSI_TypeDef *p_instance, const uint8_t p_data);
__STATIC_INLINE void PSSI_WriteData16(PSSI_TypeDef *p_instance, const uint16_t p_data);
__STATIC_INLINE void PSSI_WriteData32(PSSI_TypeDef *p_instance, const uint32_t p_data);
__STATIC_INLINE uint8_t PSSI_ReadData8(PSSI_TypeDef *p_instance);
__STATIC_INLINE uint16_t PSSI_ReadData16(PSSI_TypeDef *p_instance);
__STATIC_INLINE uint32_t PSSI_ReadData32(PSSI_TypeDef *p_instance);
#if defined(USE_HAL_PSSI_DMA) && (USE_HAL_PSSI_DMA == 1U)
/* Private functions to handle DMA transfer */
static void PSSI_DMATransmitCplt(hal_dma_handle_t *hdma);
static void PSSI_DMAReceiveCplt(hal_dma_handle_t *hdma);
static void PSSI_DMAError(hal_dma_handle_t *hdma);
static void PSSI_DMAAbort(hal_dma_handle_t *hdma);
#endif /* USE_HAL_PSSI_DMA */

/* Private functions to handle flags during polling transfer */
static hal_status_t PSSI_WaitOnStatusUntilTimeout(hal_pssi_handle_t *hpssi, uint32_t flag, FlagStatus status,
                                                  uint32_t timeout_ms);

/**
  * @}
  */

/* Exported functions -----------------------------------------------------------------------------------------------*/

/** @addtogroup PSSI_Exported_Functions PSSI Exported Functions
  * @{
  */

/** @addtogroup PSSI_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
This subsection provides a set of functions allowing to initialize and
deinitialize the pssix peripheral:

  - HAL_PSSI_Init() : initialize the selected device with the PSSI instance.
  - HAL_PSSI_DeInit() : restore the default configuration of the selected pssix peripheral.
  */

/**
  * @brief  Initialize the HAL PSSI handle and associate it to an instance.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @param  instance HAL PSSI instance
  * @retval HAL_OK HAL PSSI instance has been correctly initialized.
  * @retval HAL_INVALID_PARAM HAL PSSI instance is NULL
  * @retval HAL_ERROR HAL PSSI semaphore creation is failed (USE_HAL_MUTEX is set to 1U)
  */
hal_status_t HAL_PSSI_Init(hal_pssi_handle_t *hpssi, hal_pssi_t instance)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM(IS_PSSI_ALL_INSTANCE((PSSI_TypeDef *)((uint32_t)instance)));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpssi == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpssi->instance = instance;

#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
  hpssi->p_tx_cplt_cb = HAL_PSSI_TxCpltCallback;       /* Legacy weak TxCpltCallback      */
  hpssi->p_rx_cplt_cb = HAL_PSSI_RxCpltCallback;       /* Legacy weak RxCpltCallback      */
  hpssi->p_error_cb = HAL_PSSI_ErrorCallback;          /* Legacy weak ErrorCallback       */
  hpssi->p_abort_cplt_cb = HAL_PSSI_AbortCpltCallback; /* Legacy weak AbortCpltCallback   */
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */

  /* Other internal fields */
  hpssi->p_buf_ptr = (uint8_t *)NULL;
  hpssi->xfer_size_byte = 0U;
  hpssi->xfer_count = 0U;
  hpssi->data_width_bit = (hal_pssi_data_width_t)0U;

#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
  hpssi->last_error_codes = HAL_PSSI_ERROR_NONE;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

#if defined(USE_HAL_PSSI_DMA) && (USE_HAL_PSSI_DMA == 1U)
  hpssi->hdma_tx = (hal_dma_handle_t *)NULL;
  hpssi->hdma_rx = (hal_dma_handle_t *)NULL;
#endif /* USE_HAL_PSSI_DMA */

#if defined(USE_HAL_PSSI_CLK_ENABLE_MODEL) && (USE_HAL_PSSI_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  /* Enable pssix Clock */
  HAL_RCC_DCMI_PSSI_EnableClock();
#endif /* USE_HAL_PSSI_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1U)
  if (HAL_OS_SemaphoreCreate(&hpssi->semaphore) != HAL_OS_OK)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_MUTEX */

#if defined(USE_HAL_PSSI_USER_DATA) && (USE_HAL_PSSI_USER_DATA == 1U)
  hpssi->p_user_data = NULL;
#endif /* USE_HAL_PSSI_USER_DATA */

  hpssi->global_state = HAL_PSSI_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  DeInitialize the HAL PSSI driver for the given handle and disable the peripheral.
  * @param  hpssi Pointer to a hal_pssi_handle_t structure.
  */
void HAL_PSSI_DeInit(hal_pssi_handle_t *hpssi)
{
  PSSI_TypeDef *p_pssix;

  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM(IS_PSSI_ALL_INSTANCE((PSSI_TypeDef *)((uint32_t)hpssi->instance)));

  p_pssix = PSSI_GET_INSTANCE(hpssi);

  PSSI_Disable(p_pssix);
  HAL_PSSI_DisableIT_OVR_UDR(hpssi);
  HAL_PSSI_ClearFlag_OVR_UDR(hpssi);

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1U)
  /* Delete the PSSI semaphore */
  (void)HAL_OS_SemaphoreDelete(&hpssi->semaphore);
#endif /* USE_HAL_MUTEX */

  /* Reset the global state */
  hpssi->global_state = HAL_PSSI_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup PSSI_Exported_Functions_Group2 Configuration functions
  * @{
A set of functions allowing to configure the pssix peripheral:

- Global configuration :
  - HAL_PSSI_SetConfig(): Allowing to set the HAL peripheral instance into a ready to use state
  (idle) according to the user parameters.
  - HAL_PSSI_GetConfig() : Allowing to retrieve the HAL peripheral configuration.

- Unitary configuration :
  - HAL_PSSI_SetControlSignal()          : Allowing to set the Control signal
  - HAL_PSSI_GetControlSignal()          : Allowing to retrieve the Control signal
  - HAL_PSSI_SetDataEnablePolarity()     : Allowing to set the Data enable polarity
  - HAL_PSSI_GetDataEnablePolarity()     : Allowing to retrieve the Data enable polarity
  - HAL_PSSI_SetReadyPolarity()          : Allowing to set the Ready polarity
  - HAL_PSSI_GetReadyPolarity()          : Allowing to retrieve the Ready polarity
  - HAL_PSSI_SetClockPolarity()          : Allowing to set the Clock polarity
  - HAL_PSSI_GetClockPolarity()          : Allowing to retrieve the Clock polarity
- Callback registration :
  - HAL_PSSI_RegisterTxCpltCallback()    : Allowing to Register the PSSI Tx Transfer completed callback
  - HAL_PSSI_RegisterRxCpltCallback()    : Allowing to Register the PSSI Rx Transfer completed callback
  - HAL_PSSI_RegisterErrorCallback()     : Allowing to Register the PSSI Error callback
  - HAL_PSSI_RegisterAbortCpltCallback() : Allowing to Register the PSSI Abort completed callback
- DMA linking :
  - HAL_PSSI_SetTxDMA()                  : Allowing to Link the Transmit DMA handle to the PSSI handle
  - HAL_PSSI_SetRxDMA()                  : Allowing to Link the Receive DMA handle to the PSSI handle
  */
/**
  * @brief  Configure the PSSI according to the user parameters.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @param  p_config Pointer to the configuration structure
  * @note   When using @ref HAL_PSSI_DATA_WIDTH_8BIT in polling mode or using HAL_DMA_SRC_DATA_WIDTH_BYTE in DMA mode,
  *         the Bus Width must be @ref HAL_PSSI_BUS_WIDTH_8LINE.
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_INVALID_PARAM Invalid parameter
  */
hal_status_t HAL_PSSI_SetConfig(hal_pssi_handle_t *hpssi, const hal_pssi_config_t *p_config)
{
  PSSI_TypeDef *p_pssix;

  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(IS_PSSI_CONTROL_SIGNAL(p_config->control_signal));
  ASSERT_DBG_PARAM(IS_PSSI_BUSWIDTH(p_config->bus_width_line));
  ASSERT_DBG_PARAM(IS_PSSI_CLOCK_POLARITY(p_config->clock_polarity));
  ASSERT_DBG_PARAM(IS_PSSI_DE_POLARITY(p_config->data_enable_polarity));
  ASSERT_DBG_PARAM(IS_PSSI_RDY_POLARITY(p_config->ready_polarity));
  ASSERT_DBG_PARAM(IS_PSSI_DATAWIDTH(p_config->data_width_bit));
  ASSERT_DBG_STATE(hpssi->global_state, (uint32_t)HAL_PSSI_STATE_INIT |
                   (uint32_t)HAL_PSSI_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_pssix = PSSI_GET_INSTANCE(hpssi);

  PSSI_Disable(p_pssix);

  /*---------------------------- pssix CR Configuration ----------------------*/
  /* Configure pssix: Control Signal, Ready and Data Enable Polarity */
  MODIFY_REG(p_pssix->CR, PSSI_CR_MASK,
             (uint32_t)(p_config->control_signal) | (uint32_t)(p_config->data_enable_polarity) |
             (uint32_t)(p_config->ready_polarity) | (uint32_t)(p_config->clock_polarity) |
             (uint32_t)(p_config->bus_width_line));

  /*---------------------------- PSSI handle Configuration ----------------------*/
  /* Configure PSSI handle: Data Width */
  hpssi->data_width_bit = p_config->data_width_bit;

  hpssi->global_state = HAL_PSSI_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Retrieve the PSSI configuration.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @param  p_config Pointer to the configuration structure
  */
void HAL_PSSI_GetConfig(const hal_pssi_handle_t *hpssi, hal_pssi_config_t *p_config)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_STATE(hpssi->global_state, PSSI_STATE_ALL_EXCEPT_INIT);

  /* Get PSSI configuration */
  volatile uint32_t cr_reg_value = READ_REG((PSSI_GET_INSTANCE(hpssi))->CR);

  p_config->control_signal = ((hal_pssi_control_signal_t)((uint32_t)(cr_reg_value & PSSI_CR_DERDYCFG)));
  p_config->data_enable_polarity = ((hal_pssi_data_enable_polarity_t)((uint32_t)(cr_reg_value & PSSI_CR_DEPOL)));
  p_config->ready_polarity = ((hal_pssi_ready_polarity_t)((uint32_t)(cr_reg_value & PSSI_CR_RDYPOL)));
  p_config->clock_polarity = ((hal_pssi_clock_polarity_t)((uint32_t)(cr_reg_value & PSSI_CR_CKPOL)));
  p_config->bus_width_line = ((hal_pssi_bus_width_t)((uint32_t)(cr_reg_value & PSSI_CR_EDM)));
  p_config->data_width_bit = hpssi->data_width_bit;
}

/**
  * @brief  Configure the PSSI Control Signal.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @param  control_signal This parameter can be a value of @ref hal_pssi_control_signal_t
  * @retval HAL_OK.
  */
hal_status_t HAL_PSSI_SetControlSignal(hal_pssi_handle_t *hpssi, hal_pssi_control_signal_t control_signal)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM(IS_PSSI_CONTROL_SIGNAL(control_signal));
  ASSERT_DBG_STATE(hpssi->global_state, HAL_PSSI_STATE_IDLE);

  PSSI_Disable(PSSI_GET_INSTANCE(hpssi));

  PSSI_SetControlSignal(PSSI_GET_INSTANCE(hpssi), (uint32_t)control_signal);

  return HAL_OK;
}

/**
  * @brief  Retrieve the current PSSI Control Signal configuration.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @retval HAL_PSSI_CONTROL_SIGNAL_DE_RDY_DISABLE
  * @retval HAL_PSSI_CONTROL_SIGNAL_RDY_ENABLE
  * @retval HAL_PSSI_CONTROL_SIGNAL_DE_ENABLE
  * @retval HAL_PSSI_CONTROL_SIGNAL_DE_RDY_ALT_ENABLE
  * @retval HAL_PSSI_CONTROL_SIGNAL_MAP_RDY_BIDIR_ENABLE
  * @retval HAL_PSSI_CONTROL_SIGNAL_RDY_MAP_ENABLE
  * @retval HAL_PSSI_CONTROL_SIGNAL_DE_MAP_ENABLE
  * @retval HAL_PSSI_CONTROL_SIGNAL_MAP_DE_BIDIR_ENABLE
  */
hal_pssi_control_signal_t HAL_PSSI_GetControlSignal(const hal_pssi_handle_t *hpssi)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_STATE(hpssi->global_state, PSSI_STATE_ALL_EXCEPT_INIT);

  return PSSI_GetControlSignal(PSSI_GET_INSTANCE(hpssi));
}

/**
  * @brief  Configure the PSSI Data Enable Polarity.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @param  data_enable_polarity This parameter can be a value of @ref hal_pssi_data_enable_polarity_t
  * @retval HAL_OK.
  */
hal_status_t HAL_PSSI_SetDataEnablePolarity(hal_pssi_handle_t *hpssi,
                                            hal_pssi_data_enable_polarity_t data_enable_polarity)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((IS_PSSI_DE_POLARITY(data_enable_polarity)));
  ASSERT_DBG_STATE(hpssi->global_state, HAL_PSSI_STATE_IDLE);

  PSSI_Disable(PSSI_GET_INSTANCE(hpssi));

  PSSI_SetDataEnablePolarity(PSSI_GET_INSTANCE(hpssi), (uint32_t)data_enable_polarity);

  return HAL_OK;
}

/**
  * @brief  Retrieve the current PSSI Data Enable Polarity configuration.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @retval HAL_PSSI_DATA_ENABLE_POLARITY_LOW
  * @retval HAL_PSSI_DATA_ENABLE_POLARITY_HIGH
  */
hal_pssi_data_enable_polarity_t HAL_PSSI_GetDataEnablePolarity(const hal_pssi_handle_t *hpssi)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_STATE(hpssi->global_state, PSSI_STATE_ALL_EXCEPT_INIT);

  return PSSI_GetDataEnablePolarity(PSSI_GET_INSTANCE(hpssi));
}

/**
  * @brief  Configure the PSSI Ready Polarity.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @param  ready_polarity This parameter can be a value of @ref hal_pssi_ready_polarity_t
  * @retval HAL_OK.
  */
hal_status_t HAL_PSSI_SetReadyPolarity(hal_pssi_handle_t *hpssi, hal_pssi_ready_polarity_t ready_polarity)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((IS_PSSI_RDY_POLARITY(ready_polarity)));
  ASSERT_DBG_STATE(hpssi->global_state, HAL_PSSI_STATE_IDLE);

  PSSI_Disable(PSSI_GET_INSTANCE(hpssi));

  PSSI_SetReadyPolarity(PSSI_GET_INSTANCE(hpssi), (uint32_t)ready_polarity);

  return HAL_OK;
}

/**
  * @brief  Retrieve the current PSSI Ready Polarity configuration.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @retval HAL_PSSI_READY_POLARITY_LOW
  * @retval HAL_PSSI_READY_POLARITY_HIGH
  */
hal_pssi_ready_polarity_t HAL_PSSI_GetReadyPolarity(const hal_pssi_handle_t *hpssi)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_STATE(hpssi->global_state, PSSI_STATE_ALL_EXCEPT_INIT);

  return PSSI_GetReadyPolarity(PSSI_GET_INSTANCE(hpssi));
}

/**
  * @brief  Configure the PSSI Clock Polarity.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @param  clock_polarity This parameter can be a value of @ref hal_pssi_clock_polarity_t
  * @retval HAL_OK.
  */
hal_status_t HAL_PSSI_SetClockPolarity(hal_pssi_handle_t *hpssi, hal_pssi_clock_polarity_t clock_polarity)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((IS_PSSI_CLOCK_POLARITY(clock_polarity)));
  ASSERT_DBG_STATE(hpssi->global_state, HAL_PSSI_STATE_IDLE);

  PSSI_Disable(PSSI_GET_INSTANCE(hpssi));

  PSSI_SetClockPolarity(PSSI_GET_INSTANCE(hpssi), (uint32_t)clock_polarity);

  return HAL_OK;
}

/**
  * @brief  Retrieve the current PSSI Clock Polarity configuration.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @retval HAL_PSSI_CLOCK_POLARITY_RX_FALLING_TX_RISING_EDGE
  * @retval HAL_PSSI_CLOCK_POLARITY_RX_RISING_TX_FALLING_EDGE
  */
hal_pssi_clock_polarity_t HAL_PSSI_GetClockPolarity(const hal_pssi_handle_t *hpssi)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_STATE(hpssi->global_state, PSSI_STATE_ALL_EXCEPT_INIT);

  return PSSI_GetClockPolarity(PSSI_GET_INSTANCE(hpssi));
}


#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register the PSSI Tx Transfer completed callback.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @param  p_callback Pointer to the Tx Transfer completed callback function
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_INVALID_PARAM Invalid parameter
  */
hal_status_t HAL_PSSI_RegisterTxCpltCallback(hal_pssi_handle_t *hpssi, hal_pssi_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpssi->global_state, (uint32_t)HAL_PSSI_STATE_INIT |
                   (uint32_t)HAL_PSSI_STATE_IDLE);

  hpssi->p_tx_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the PSSI Rx Transfer completed callback.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @param  p_callback Pointer to the Rx Transfer completed callback function
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_INVALID_PARAM Invalid parameter
  */
hal_status_t HAL_PSSI_RegisterRxCpltCallback(hal_pssi_handle_t *hpssi, hal_pssi_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpssi->global_state, (uint32_t)HAL_PSSI_STATE_INIT |
                   (uint32_t)HAL_PSSI_STATE_IDLE);

  hpssi->p_rx_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the PSSI Error callback.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @param  p_callback Pointer to the Error callback function
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_INVALID_PARAM Invalid parameter
  */
hal_status_t HAL_PSSI_RegisterErrorCallback(hal_pssi_handle_t *hpssi, hal_pssi_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpssi->global_state, (uint32_t)HAL_PSSI_STATE_INIT |
                   (uint32_t)HAL_PSSI_STATE_IDLE);

  hpssi->p_error_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the PSSI Abort completed callback.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @param  p_callback Pointer to the Abort completed callback function
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_INVALID_PARAM Invalid parameter
  */
hal_status_t HAL_PSSI_RegisterAbortCpltCallback(hal_pssi_handle_t *hpssi, hal_pssi_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpssi->global_state, (uint32_t)HAL_PSSI_STATE_INIT |
                   (uint32_t)HAL_PSSI_STATE_IDLE);

  hpssi->p_abort_cplt_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */

#if defined(USE_HAL_PSSI_DMA) && (USE_HAL_PSSI_DMA == 1U)
/**
  * @brief  Link the Transmit DMA handle to the PSSI handle.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @param  hdma Pointer to a hal_dma_handle_t structure
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_INVALID_PARAM Invalid parameter
  */
hal_status_t HAL_PSSI_SetTxDMA(hal_pssi_handle_t *hpssi, hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((hdma != NULL));
  ASSERT_DBG_STATE(hpssi->global_state, (uint32_t)HAL_PSSI_STATE_INIT |
                   (uint32_t)HAL_PSSI_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Link the DMA handle to the PSSI handle */
  hpssi->hdma_tx = hdma;
  hdma->p_parent = hpssi;

  return HAL_OK;
}

/**
  * @brief  Link the Receive DMA handle to the PSSI handle.
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @param  hdma Pointer to a hal_dma_handle_t structure
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_INVALID_PARAM Invalid parameter
  */
hal_status_t HAL_PSSI_SetRxDMA(hal_pssi_handle_t *hpssi, hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((hdma != NULL));
  ASSERT_DBG_STATE(hpssi->global_state, (uint32_t)HAL_PSSI_STATE_INIT |
                   (uint32_t)HAL_PSSI_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Link the DMA handle to the PSSI handle */
  hpssi->hdma_rx = hdma;
  hdma->p_parent = hpssi;

  return HAL_OK;
}
#endif /* USE_HAL_PSSI_DMA */
/**
  * @}
  */

/** @addtogroup PSSI_Exported_Functions_Group3 Input and Output operation functions
  * @{
This subsection provides a set of functions allowing to manage the PSSI data
transfers.
- There are two modes of transfer:
     - Blocking mode : The communication is performed in the polling mode.
                       The status of all data processing is returned by the same function
                       after finishing transfer.
     - No-Blocking mode : The communication is performed using DMA.
                          These functions return the status of the transfer startup.
                          The end of the transfer is signaled by a dedicated callback
- Blocking mode functions are :
      - HAL_PSSI_Transmit()
      - HAL_PSSI_Receive()

- No-Blocking mode functions with DMA are :
      - HAL_PSSI_Transmit_DMA()
      - HAL_PSSI_Receive_DMA()
      - HAL_PSSI_Abort_IT()
      - HAL_PSSI_Abort()
  */

/**
  * @brief  Transmit in master mode an amount of data in blocking mode.
  * @param  hpssi Pointer to a hal_pssi_handle_t structure.
  * @param  p_data Pointer to data buffer
  * @param  size_byte Amount of data to be sent (in bytes)
  * @param  timeout_ms Timeout duration
  * @warning The PSSI has an eight-word FIFO.
  *          A delay of some PDCK cycles (between 0 and 32 cycles) must be added after using this API.
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_TIMEOUT Timeout exceeded
  * @retval HAL_ERROR Underrun Error Occurred
  * @retval HAL_BUSY there is ongoing process
  */
hal_status_t HAL_PSSI_Transmit(hal_pssi_handle_t *hpssi, const void *p_data, uint32_t size_byte, uint32_t timeout_ms)
{
  PSSI_TypeDef *p_pssix;
  uint32_t transfer_size = size_byte;

  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((p_data != NULL));
  ASSERT_DBG_PARAM((size_byte != 0));
  ASSERT_DBG_STATE(hpssi->global_state, HAL_PSSI_STATE_IDLE);

  p_pssix = PSSI_GET_INSTANCE(hpssi);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (((PSSI_GetBusWidth(p_pssix) != HAL_PSSI_BUS_WIDTH_8LINE)                              \
       && (hpssi->data_width_bit == HAL_PSSI_DATA_WIDTH_8BIT))                              \
      || ((hpssi->data_width_bit == HAL_PSSI_DATA_WIDTH_16BIT) && ((size_byte % 2U) != 0U)) \
      || ((hpssi->data_width_bit == HAL_PSSI_DATA_WIDTH_32BIT) && ((size_byte % 4U) != 0U)) \
      || (p_data == NULL)                                                                   \
      || (size_byte == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hpssi, global_state, HAL_PSSI_STATE_IDLE, HAL_PSSI_STATE_TX);

#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
  hpssi->last_error_codes = HAL_PSSI_ERROR_NONE;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

  hpssi->p_buf_ptr = (uint8_t *)p_data;

  /* Configure transfer parameters */
  PSSI_Disable(p_pssix);

  MODIFY_REG(p_pssix->CR, PSSI_CR_OUTEN | PSSI_CR_DMAEN, PSSI_CR_OUTEN);

  PSSI_Enable(p_pssix);

  if (hpssi->data_width_bit == HAL_PSSI_DATA_WIDTH_8BIT)
  {
    while (transfer_size > 0U)
    {
      /* Wait until Fifo is ready to transfer one byte flag is set */
      if (PSSI_WaitOnStatusUntilTimeout(hpssi, HAL_PSSI_FLAG_RTT1B, RESET, timeout_ms) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }

      /* Write data to DR */
      PSSI_WriteData8(p_pssix, *hpssi->p_buf_ptr);
      hpssi->p_buf_ptr++;
      transfer_size--;
    }
  }
  else if (hpssi->data_width_bit == HAL_PSSI_DATA_WIDTH_16BIT)
  {
    while (transfer_size > 0U)
    {
      /* Wait until Fifo is ready to transfer four bytes flag is set */
      if (PSSI_WaitOnStatusUntilTimeout(hpssi, HAL_PSSI_FLAG_RTT4B, RESET, timeout_ms) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }

      /* Write data to DR */
      PSSI_WriteData16(p_pssix, *(const uint16_t *)hpssi->p_buf_ptr);
      hpssi->p_buf_ptr += sizeof(uint16_t);
      transfer_size -= 2U;
    }
  }
  else
  {
    while (transfer_size > 0U)
    {
      /* Wait until Fifo is ready to transfer four bytes flag is set */
      if (PSSI_WaitOnStatusUntilTimeout(hpssi, HAL_PSSI_FLAG_RTT4B, RESET, timeout_ms) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }

      /* Write data to DR */
      PSSI_WriteData32(p_pssix, *(const uint32_t *)hpssi->p_buf_ptr);
      hpssi->p_buf_ptr += sizeof(uint32_t);
      transfer_size -= 4U;
    }
  }

  /* Check Errors Flags */
  if (HAL_PSSI_IsActiveFlag_OVR_UDR_RIS(hpssi) != 0U)
  {
    PSSI_Disable(p_pssix);
    HAL_PSSI_ClearFlag_OVR_UDR(hpssi);

#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
    hpssi->last_error_codes = HAL_PSSI_ERROR_UNDER_RUN;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

    hpssi->global_state = HAL_PSSI_STATE_IDLE;

    return HAL_ERROR;
  }
  hpssi->global_state = HAL_PSSI_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Receive an amount of data in blocking mode.
  * @param  hpssi Pointer to a hal_pssi_handle_t structure.
  * @param  p_data Pointer to data buffer
  * @param  size_byte Amount of data to be received (in bytes)
  * @param  timeout_ms Timeout duration
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_TIMEOUT Timeout exceeded
  * @retval HAL_ERROR Overrun Error Occurred
  * @retval HAL_BUSY there is ongoing process
  */
hal_status_t HAL_PSSI_Receive(hal_pssi_handle_t *hpssi, void *p_data, uint32_t size_byte, uint32_t timeout_ms)
{
  PSSI_TypeDef *p_pssix;
  uint32_t transfer_size = size_byte;

  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((p_data != NULL));
  ASSERT_DBG_PARAM((size_byte != 0));
  ASSERT_DBG_STATE(hpssi->global_state, HAL_PSSI_STATE_IDLE);

  p_pssix = PSSI_GET_INSTANCE(hpssi);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (((PSSI_GetBusWidth(p_pssix) != HAL_PSSI_BUS_WIDTH_8LINE)                              \
       && (hpssi->data_width_bit == HAL_PSSI_DATA_WIDTH_8BIT))                              \
      || ((hpssi->data_width_bit == HAL_PSSI_DATA_WIDTH_16BIT) && ((size_byte % 2U) != 0U)) \
      || ((hpssi->data_width_bit == HAL_PSSI_DATA_WIDTH_32BIT) && ((size_byte % 4U) != 0U)) \
      || (p_data == NULL)                                                                   \
      || (size_byte == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hpssi, global_state, HAL_PSSI_STATE_IDLE, HAL_PSSI_STATE_RX);

#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
  hpssi->last_error_codes = HAL_PSSI_ERROR_NONE;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

  hpssi->p_buf_ptr = (uint8_t *)p_data;

  /* Configure transfer parameters */
  PSSI_Disable(p_pssix);

  CLEAR_BIT(p_pssix->CR, PSSI_CR_OUTEN | PSSI_CR_DMAEN);

  PSSI_Enable(p_pssix);

  if (hpssi->data_width_bit == HAL_PSSI_DATA_WIDTH_8BIT)
  {
    while (transfer_size > 0U)
    {
      /* Wait until Fifo is ready to receive one byte flag is set */
      if (PSSI_WaitOnStatusUntilTimeout(hpssi, HAL_PSSI_FLAG_RTT1B, RESET, timeout_ms) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }

      /* Read data from DR */
      *hpssi->p_buf_ptr = PSSI_ReadData8(p_pssix);
      hpssi->p_buf_ptr++;
      transfer_size--;
    }
  }
  else if (hpssi->data_width_bit == HAL_PSSI_DATA_WIDTH_16BIT)
  {
    while (transfer_size > 0U)
    {
      /* Wait until Fifo is ready to receive four bytes flag is set */
      if (PSSI_WaitOnStatusUntilTimeout(hpssi, HAL_PSSI_FLAG_RTT4B, RESET, timeout_ms) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }

      /* Read data from DR */
      *((uint16_t *)hpssi->p_buf_ptr) = PSSI_ReadData16(p_pssix);
      hpssi->p_buf_ptr += sizeof(uint16_t);
      transfer_size -= 2U;
    }
  }
  else
  {
    while (transfer_size > 0U)
    {
      /* Wait until Fifo is ready to receive four bytes flag is set */
      if (PSSI_WaitOnStatusUntilTimeout(hpssi, HAL_PSSI_FLAG_RTT4B, RESET, timeout_ms) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }

      /* Read data from DR */
      *((uint32_t *)hpssi->p_buf_ptr) = PSSI_ReadData32(p_pssix);
      hpssi->p_buf_ptr += sizeof(uint32_t);
      transfer_size -= 4U;
    }
  }

  /* Check Errors Flags */
  if (HAL_PSSI_IsActiveFlag_OVR_UDR_RIS(hpssi) != 0U)
  {
    PSSI_Disable(p_pssix);
    HAL_PSSI_ClearFlag_OVR_UDR(hpssi);

#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
    hpssi->last_error_codes = HAL_PSSI_ERROR_OVER_RUN;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

    hpssi->global_state = HAL_PSSI_STATE_IDLE;

    return HAL_ERROR;
  }

  hpssi->global_state = HAL_PSSI_STATE_IDLE;

  return HAL_OK;
}

#if defined(USE_HAL_PSSI_DMA) && (USE_HAL_PSSI_DMA == 1U)
/**
  * @brief   Transmit an amount of data in non-blocking mode with DMA
  * @param   hpssi Pointer to a hal_pssi_handle_t structure.
  * @param   p_data Pointer to data buffer
  * @param   size_byte Amount of data to be sent (in bytes)
  * @warning The PSSI has an eight-word FIFO. A delay of some PDCK cycles (between 0 and 32 cycles)
  *          must be added after calling the HAL_PSSI_TxCpltCallback()
  * @retval  HAL_OK Operation completed successfully
  * @retval  HAL_INVALID_PARAM Invalid parameter
  * @retval  HAL_ERROR DMA failed to start the transfer
  * @retval  HAL_BUSY there is ongoing process
  */
hal_status_t HAL_PSSI_Transmit_DMA(hal_pssi_handle_t *hpssi, const void *p_data, uint32_t size_byte)
{
  PSSI_TypeDef *p_pssix;
  hal_status_t hal_status;

  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((hpssi->hdma_tx != NULL));
  ASSERT_DBG_PARAM((p_data != NULL));
  ASSERT_DBG_STATE(hpssi->global_state, HAL_PSSI_STATE_IDLE);

  p_pssix = PSSI_GET_INSTANCE(hpssi);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  hal_dma_direct_xfer_config_t p_dma_tx_config;

  /* Get DMA channel basic transfer configuration */
  HAL_DMA_GetConfigDirectXfer(hpssi->hdma_tx, &p_dma_tx_config);

  if (((PSSI_GetBusWidth(p_pssix) != HAL_PSSI_BUS_WIDTH_8LINE)                                             \
       && (p_dma_tx_config.src_data_width == HAL_DMA_SRC_DATA_WIDTH_BYTE))                                 \
      || ((p_dma_tx_config.src_data_width == HAL_DMA_SRC_DATA_WIDTH_HALFWORD) && ((size_byte % 2U) != 0U)) \
      || ((p_dma_tx_config.src_data_width == HAL_DMA_SRC_DATA_WIDTH_WORD) && ((size_byte % 4U) != 0U))     \
      || (p_data == NULL)                                                                                  \
      || (size_byte == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hpssi, global_state, HAL_PSSI_STATE_IDLE, HAL_PSSI_STATE_TX);

#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
  hpssi->last_error_codes = HAL_PSSI_ERROR_NONE;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

  PSSI_Disable(p_pssix);

  /* Prepare transfer parameters */
  hpssi->p_buf_ptr = (uint8_t *)p_data;
  hpssi->xfer_count = size_byte;

  if (hpssi->xfer_count > PSSI_MAX_NBYTE_SIZE)
  {
    hpssi->xfer_size_byte = PSSI_MAX_NBYTE_SIZE;
  }
  else
  {
    hpssi->xfer_size_byte = hpssi->xfer_count;
  }

  hpssi->hdma_tx->p_xfer_cplt_cb = PSSI_DMATransmitCplt;
  hpssi->hdma_tx->p_xfer_error_cb = PSSI_DMAError;

  /* Enable the DMA */
  hal_status = HAL_DMA_StartPeriphXfer_IT_Opt(hpssi->hdma_tx,
                                              (uint32_t)hpssi->p_buf_ptr, (uint32_t)&p_pssix->DR,
                                              hpssi->xfer_size_byte, HAL_DMA_OPT_IT_NONE);

  if (hal_status == HAL_OK)
  {
    /* Update xfer_count value */
    hpssi->xfer_count -= hpssi->xfer_size_byte;

    /* Enable UNDERRUN interrupt */
    HAL_PSSI_EnableIT_OVR_UDR(hpssi);

    /* Set transfer direction and enable DMA request */
    MODIFY_REG(p_pssix->CR, PSSI_CR_OUTEN | PSSI_CR_DMAEN, PSSI_CR_OUTEN | PSSI_CR_DMAEN);

    PSSI_Enable(p_pssix);
  }
  else
  {
#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
    hpssi->last_error_codes = HAL_PSSI_ERROR_DMA;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

    hpssi->global_state = HAL_PSSI_STATE_IDLE;
  }
  return hal_status;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with DMA
  * @param  hpssi Pointer to a hal_pssi_handle_t structure.
  * @param  p_data Pointer to data buffer
  * @param  size_byte Amount of data to be received (in bytes)
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_ERROR DMA failed to start the transfer
  * @retval HAL_BUSY there is ongoing process
  */
hal_status_t HAL_PSSI_Receive_DMA(hal_pssi_handle_t *hpssi, void *p_data, uint32_t size_byte)
{
  PSSI_TypeDef *p_pssix;
  hal_status_t hal_status;

  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_PARAM((hpssi->hdma_rx != NULL));
  ASSERT_DBG_PARAM((p_data != NULL));
  ASSERT_DBG_STATE(hpssi->global_state, HAL_PSSI_STATE_IDLE);

  p_pssix = PSSI_GET_INSTANCE(hpssi);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  hal_dma_direct_xfer_config_t p_dma_rx_config;

  /* Get DMA channel basic transfer configuration */
  HAL_DMA_GetConfigDirectXfer(hpssi->hdma_rx, &p_dma_rx_config);

  if (((PSSI_GetBusWidth(p_pssix) != HAL_PSSI_BUS_WIDTH_8LINE)                                             \
       && (p_dma_rx_config.src_data_width == HAL_DMA_SRC_DATA_WIDTH_BYTE))                                 \
      || ((p_dma_rx_config.src_data_width == HAL_DMA_SRC_DATA_WIDTH_HALFWORD) && ((size_byte % 2U) != 0U)) \
      || ((p_dma_rx_config.src_data_width == HAL_DMA_SRC_DATA_WIDTH_WORD) && ((size_byte % 4U) != 0U))     \
      || (p_data == NULL)                                                                                  \
      || (size_byte == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hpssi, global_state, HAL_PSSI_STATE_IDLE, HAL_PSSI_STATE_RX);

#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
  hpssi->last_error_codes = HAL_PSSI_ERROR_NONE;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

  PSSI_Disable(p_pssix);

  /* Prepare transfer parameters */
  hpssi->p_buf_ptr = (uint8_t *)p_data;
  hpssi->xfer_count = size_byte;

  if (hpssi->xfer_count > PSSI_MAX_NBYTE_SIZE)
  {
    hpssi->xfer_size_byte = PSSI_MAX_NBYTE_SIZE;
  }
  else
  {
    hpssi->xfer_size_byte = hpssi->xfer_count;
  }

  hpssi->hdma_rx->p_xfer_cplt_cb = PSSI_DMAReceiveCplt;
  hpssi->hdma_rx->p_xfer_error_cb = PSSI_DMAError;

  /* Enable the DMA */
  hal_status = HAL_DMA_StartPeriphXfer_IT_Opt(hpssi->hdma_rx,
                                              (uint32_t)&p_pssix->DR, (uint32_t)hpssi->p_buf_ptr,
                                              hpssi->xfer_size_byte, HAL_DMA_OPT_IT_NONE);

  if (hal_status == HAL_OK)
  {
    /* Update xfer_count value */
    hpssi->xfer_count -= hpssi->xfer_size_byte;

    /* Enable OVERRUN interrupt */
    HAL_PSSI_EnableIT_OVR_UDR(hpssi);

    /* Set transfer direction and enable DMA request */
    MODIFY_REG(p_pssix->CR, PSSI_CR_OUTEN | PSSI_CR_DMAEN, PSSI_CR_DMAEN);
    PSSI_Enable(p_pssix);
  }
  else
  {
#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
    hpssi->last_error_codes = HAL_PSSI_ERROR_DMA;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

    hpssi->global_state = HAL_PSSI_STATE_IDLE;
  }
  return hal_status;
}

/**
  * @brief  Abort a DMA process communication with Polling.
  * @param  hpssi Pointer to a hal_pssi_handle_t structure.
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_ERROR DMA is not processing any transfer
  */
hal_status_t HAL_PSSI_Abort(hal_pssi_handle_t *hpssi)
{
  PSSI_TypeDef *p_pssix;
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_STATE(hpssi->global_state, PSSI_STATE_ALL_ACTIVE);

  p_pssix = PSSI_GET_INSTANCE(hpssi);
  HAL_PSSI_DisableIT_OVR_UDR(hpssi);

  /* Abort DMA TX transfer if any */
  if (PSSI_IsEnabledDMA(p_pssix) != 0U)
  {
    if (hpssi->global_state == HAL_PSSI_STATE_TX)
    {
      hpssi->global_state = HAL_PSSI_STATE_ABORT;
      PSSI_Disable(p_pssix);
      PSSI_DisableDMA(p_pssix);

      if (hpssi->hdma_tx != NULL)
      {
        /* Abort DMA TX */
        status = HAL_DMA_Abort(hpssi->hdma_tx);
      }
      else
      {
        status = HAL_ERROR;
      }
    }
    /* Abort DMA RX transfer if any */
    else if (hpssi->global_state == HAL_PSSI_STATE_RX)
    {
      hpssi->global_state = HAL_PSSI_STATE_ABORT;
      PSSI_Disable(p_pssix);
      PSSI_DisableDMA(p_pssix);

      if (hpssi->hdma_rx != NULL)
      {
        /* Abort DMA RX */
        status = HAL_DMA_Abort(hpssi->hdma_rx);
      }
      else
      {
        status = HAL_ERROR;
      }
    }
    else
    {
      /* Do nothing */
    }
  }
  else
  {
    status = HAL_ERROR;
  }

  if (status != HAL_OK)
  {
#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
    hpssi->last_error_codes |= HAL_PSSI_ERROR_DMA;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */
  }
  hpssi->global_state = HAL_PSSI_STATE_IDLE;
  return status;
}

/**
  * @brief  Abort a DMA process communication with Interrupt.
  * @param  hpssi Pointer to a hal_pssi_handle_t structure.
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_ERROR DMA is not processing any transfer
  */
hal_status_t HAL_PSSI_Abort_IT(hal_pssi_handle_t *hpssi)
{
  PSSI_TypeDef *p_pssix;

  ASSERT_DBG_PARAM((hpssi != NULL));
  ASSERT_DBG_STATE(hpssi->global_state, PSSI_STATE_ALL_ACTIVE);

  p_pssix = PSSI_GET_INSTANCE(hpssi);

  HAL_PSSI_DisableIT_OVR_UDR(hpssi);

  /* Abort DMA TX transfer if any */
  if (PSSI_IsEnabledDMA(p_pssix) != 0U)
  {
    if (hpssi->global_state == HAL_PSSI_STATE_TX)
    {
      hpssi->global_state = HAL_PSSI_STATE_ABORT;

      PSSI_Disable(p_pssix);
      PSSI_DisableDMA(p_pssix);

      if (hpssi->hdma_tx != NULL)
      {
        /* Set the PSSI DMA Abort callback :
           will lead to call HAL_PSSI_ErrorCallback() at end of DMA abort procedure */
        hpssi->hdma_tx->p_xfer_abort_cb = PSSI_DMAAbort;

        /* Abort DMA TX */
        if (HAL_DMA_Abort_IT(hpssi->hdma_tx) != HAL_OK)
        {
          /* Call directly p_xfer_abort_cb function in case of error */
          hpssi->hdma_tx->p_xfer_abort_cb(hpssi->hdma_tx);

#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
          hpssi->last_error_codes |= HAL_PSSI_ERROR_DMA;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

          return HAL_ERROR;
        }
      }
      else
      {
#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
        hpssi->last_error_codes |= HAL_PSSI_ERROR_DMA;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

        hpssi->global_state = HAL_PSSI_STATE_IDLE;

#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
        hpssi->p_error_cb(hpssi);
#else
        HAL_PSSI_ErrorCallback(hpssi);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */

        return HAL_ERROR;
      }
    }
    /* Abort DMA RX transfer if any */
    else if (hpssi->global_state == HAL_PSSI_STATE_RX)
    {
      hpssi->global_state = HAL_PSSI_STATE_ABORT;
      PSSI_Disable(p_pssix);
      PSSI_DisableDMA(p_pssix);

      if (hpssi->hdma_rx != NULL)
      {
        /* Set the PSSI DMA Abort callback :
           will lead to call HAL_PSSI_ErrorCallback() at end of DMA abort procedure */
        hpssi->hdma_rx->p_xfer_abort_cb = PSSI_DMAAbort;

        /* Abort DMA RX */
        if (HAL_DMA_Abort_IT(hpssi->hdma_rx) != HAL_OK)
        {
          /* Call directly hpssi->hdma->p_xfer_abort_cb function in case of error */
          hpssi->hdma_rx->p_xfer_abort_cb(hpssi->hdma_rx);

#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
          hpssi->last_error_codes |= HAL_PSSI_ERROR_DMA;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

          return HAL_ERROR;
        }
      }
      else
      {
#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
        hpssi->last_error_codes |= HAL_PSSI_ERROR_DMA;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

        hpssi->global_state = HAL_PSSI_STATE_IDLE;

#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
        hpssi->p_error_cb(hpssi);
#else
        HAL_PSSI_ErrorCallback(hpssi);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */

        return HAL_ERROR;
      }
    }
    else
    {
      /* Do nothing */
    }
  }
  else
  {
    /* DMA transfer is already disabled */
#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
    hpssi->p_error_cb(hpssi);
#else
    HAL_PSSI_ErrorCallback(hpssi);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */

    return HAL_ERROR;
  }
  return HAL_OK;
}
#endif /* USE_HAL_PSSI_DMA */

/**
  * @}
  */

/** @addtogroup PSSI_Exported_Functions_Group4 IRQ Handler and Weak Callbacks Functions
  * @{
A set of functions allowing to register IRQ Handler, Callbacks/weak functions.
PSSI IRQHandler and Callbacks are used in non blocking modes (DMA).
The end of the data processing will be indicated through the dedicated PSSI IRQ.
- IRQHandler and Callbacks/weak functions are :
      - HAL_PSSI_IRQHandler()
      - HAL_PSSI_TxCpltCallback()
      - HAL_PSSI_RxCpltCallback()
      - HAL_PSSI_ErrorCallback()
      - HAL_PSSI_AbortCpltCallback()
  */

/**
  * @brief  Handle PSSI event interrupt request.
  * @param  hpssi Pointer to a hal_pssi_handle_t structure.
  */
void HAL_PSSI_IRQHandler(hal_pssi_handle_t *hpssi)
{
  ASSERT_DBG_PARAM((hpssi != NULL));

  PSSI_TypeDef *p_pssix = PSSI_GET_INSTANCE(hpssi);

  /* Overrun/Underrun Errors */
  if (HAL_PSSI_IsActiveFlag_OVR_UDR_RIS(hpssi) != 0U)
  {
    HAL_PSSI_DisableIT_OVR_UDR(hpssi);
    PSSI_Disable(p_pssix);

    /* Clear OVR/UDR flag */
    HAL_PSSI_ClearFlag_OVR_UDR(hpssi);

    /* Reset handle parameters */
    hpssi->xfer_count = 0U;

#if defined(USE_HAL_PSSI_DMA) && (USE_HAL_PSSI_DMA == 1U)
    /* Abort DMA TX transfer if any */
    if (PSSI_IsEnabledDMA(p_pssix) != 0U)
    {
      if (hpssi->global_state == HAL_PSSI_STATE_TX)
      {
#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
        hpssi->last_error_codes |= HAL_PSSI_ERROR_UNDER_RUN;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

        PSSI_DisableDMA(p_pssix);

        if (hpssi->hdma_tx != NULL)
        {
          /* Set the PSSI DMA Abort callback :
             will lead to call HAL_PSSI_ErrorCallback() at end of DMA abort procedure */
          hpssi->hdma_tx->p_xfer_abort_cb = PSSI_DMAAbort;

          /* Abort DMA TX */
          if (HAL_DMA_Abort_IT(hpssi->hdma_tx) != HAL_OK)
          {
            /* Call directly p_xfer_abort_cb function in case of error */
            hpssi->hdma_tx->p_xfer_abort_cb(hpssi->hdma_tx);
          }
        }
        else
        {
          hpssi->global_state = HAL_PSSI_STATE_IDLE;

          /* Call the corresponding callback to inform upper layer of End of Transfer */
#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
          hpssi->p_error_cb(hpssi);
#else
          HAL_PSSI_ErrorCallback(hpssi);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */
        }
      }
      /* Abort DMA RX transfer if any */
      else if (hpssi->global_state == HAL_PSSI_STATE_RX)
      {
#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
        hpssi->last_error_codes |= HAL_PSSI_ERROR_OVER_RUN;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

        PSSI_DisableDMA(p_pssix);

        if (hpssi->hdma_rx != NULL)
        {
          /* Set the PSSI DMA Abort callback :
             will lead to call HAL_PSSI_ErrorCallback() at end of DMA abort procedure */
          hpssi->hdma_rx->p_xfer_abort_cb = PSSI_DMAAbort;

          /* Abort DMA RX */
          if (HAL_DMA_Abort_IT(hpssi->hdma_rx) != HAL_OK)
          {
            /* Call directly hpssi->hdma->p_xfer_abort_cb function in case of error */
            hpssi->hdma_rx->p_xfer_abort_cb(hpssi->hdma_rx);
          }
        }
        else
        {
          hpssi->global_state = HAL_PSSI_STATE_IDLE;

          /* Call the corresponding callback to inform upper layer of End of Transfer */
#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
          hpssi->p_error_cb(hpssi);
#else
          HAL_PSSI_ErrorCallback(hpssi);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */
        }
      }
      else
      {
        /* Do nothing, the Error has been already treated by the DMA IRQHandler */
      }
      return;
    }
#endif /* USE_HAL_PSSI_DMA */

    if (hpssi->global_state != HAL_PSSI_STATE_IDLE)
    {
      hpssi->global_state = HAL_PSSI_STATE_IDLE;

      /* Call the corresponding callback to inform upper layer of End of Transfer */
#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
      hpssi->p_error_cb(hpssi);
#else
      HAL_PSSI_ErrorCallback(hpssi);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */
    }
    else
    {
      /* Do nothing */
    }
  }
}

/**
  * @brief  Tx Transfer complete callback.
  * @param  hpssi Pointer to a hal_pssi_handle_t structure.
  */
__weak void HAL_PSSI_TxCpltCallback(hal_pssi_handle_t *hpssi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpssi);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_PSSI_TxCpltCallback can be implemented in the user file
   */
}

/**
  * @brief  Rx Transfer complete callback.
  * @param  hpssi Pointer to a hal_pssi_handle_t structure.
  */
__weak void HAL_PSSI_RxCpltCallback(hal_pssi_handle_t *hpssi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpssi);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_PSSI_RxCpltCallback can be implemented in the user file
   */
}

/**
  * @brief  PSSI error callback.
  * @param  hpssi Pointer to a hal_pssi_handle_t structure.
  */
__weak void HAL_PSSI_ErrorCallback(hal_pssi_handle_t *hpssi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpssi);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_PSSI_ErrorCallback could be implemented in the user file
   */
}

/**
  * @brief  PSSI abort callback.
  * @param  hpssi Pointer to a hal_pssi_handle_t structure.
  */
__weak void HAL_PSSI_AbortCpltCallback(hal_pssi_handle_t *hpssi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpssi);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_PSSI_AbortCpltCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/** @addtogroup PSSI_Exported_Functions_Group5 Peripheral State and Error functions
  * @{
This subsection permits to get in run-time the status of the peripheral
and the data flow.
- A set of functions is provided :
      - HAL_PSSI_GetState()
      - HAL_PSSI_GetLastErrorCodes()
  */

/**
  * @brief  Return the PSSI handle state.
  * @param  hpssi Pointer to a hal_pssi_handle_t structure.
  * @retval HAL_PSSI_STATE_INIT
  * @retval HAL_PSSI_STATE_IDLE
  * @retval HAL_PSSI_STATE_TX
  * @retval HAL_PSSI_STATE_RX
  * @retval HAL_PSSI_STATE_ABORT
  */
hal_pssi_state_t HAL_PSSI_GetState(const hal_pssi_handle_t *hpssi)
{
  ASSERT_DBG_PARAM(hpssi != NULL);
  ASSERT_DBG_STATE(hpssi->global_state, PSSI_STATE_ALL);

  return hpssi->global_state;
}

#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
/**
  * @brief  Return the PSSI errors codes.
  * @param  hpssi Pointer to a hal_pssi_handle_t structure.
  * @return uint32_t Returned value can be a combination of the following values:
  *         @arg HAL_PSSI_ERROR_NONE
  *         @arg HAL_PSSI_ERROR_UNDER_RUN
  *         @arg HAL_PSSI_ERROR_OVER_RUN
  *         @arg HAL_PSSI_ERROR_DMA
  */
uint32_t HAL_PSSI_GetLastErrorCodes(const hal_pssi_handle_t *hpssi)
{
  ASSERT_DBG_PARAM(hpssi != NULL);
  ASSERT_DBG_STATE(hpssi->global_state, PSSI_STATE_ALL);

  return hpssi->last_error_codes;
}
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */
/**
  * @}
  */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1U)
/** @addtogroup PSSI_Exported_Functions_Group6 Peripheral Acquire/Release/Free the bus
  * @{
A set of functions allowing to Acquire/Release the HAL PSSI handle based on
the HAL OS abstraction layer (stm32_hal_os.c/.h osal):
 - The HAL_PSSI_AcquireBus() must be called from thread mode only (not from handler mode i.e from ISR).
 - The HAL_PSSI_ReleaseBus() can be called from thread mode or from handler mode i.e from ISR.
  */

/**
  * @brief  Acquire the HAL PSSI handle thanks to the HAL OS abstraction layer (stm32_hal_os.c/.h osal).
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @param  timeout_ms timeout duration in millisecond.
  * @note   The HAL_PSSI_AcquireBus must be called from thread mode only (not from handler mode i.e from ISR).
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_ERROR PSSI handle did not acquired
  */
hal_status_t HAL_PSSI_AcquireBus(hal_pssi_handle_t *hpssi, uint32_t timeout_ms)
{
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM((hpssi != NULL));

  if (HAL_OS_SemaphoreTake(&hpssi->semaphore, timeout_ms) == HAL_OS_OK)
  {
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Release the HAL PSSI handle thanks to the HAL OS abstraction layer (stm32_hal_os.c/.h osal).
  * @param  hpssi Pointer to a hal_pssi_handle_t
  * @note   The HAL_PSSI_ReleaseBus can be called from thread mode or from handler mode i.e from ISR.
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_ERROR PSSI handle did not released
  */
hal_status_t HAL_PSSI_ReleaseBus(hal_pssi_handle_t *hpssi)
{
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM((hpssi != NULL));

  if (HAL_OS_SemaphoreRelease(&hpssi->semaphore) == HAL_OS_OK)
  {
    status = HAL_OK;
  }

  return status;
}

/**
  * @}
  */
#endif /* USE_HAL_MUTEX */

#if defined(USE_HAL_PSSI_USER_DATA) && (USE_HAL_PSSI_USER_DATA == 1U)
/** @addtogroup PSSI_Exported_Functions_Group7 Set/Get user data
  * @{
A set of functions allowing to manage a user data pointer stored to the PSSI handle:
 - HAL_PSSI_SetUserData() Set the user data into the handle
 - HAL_PSSI_GetUserData() Get the user data from the handle
  */

/**
  * @brief Store the user data pointer into the handle.
  * @param hpssi Pointer to a hal_pssi_handle_t
  * @param p_user_data Pointer to the user data.
  */
void HAL_PSSI_SetUserData(hal_pssi_handle_t *hpssi, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hpssi != NULL);
  ASSERT_DBG_STATE(hpssi->global_state, PSSI_STATE_ALL);

  hpssi->p_user_data = p_user_data;
}

/**
  * @brief Get the user data pointer from the handle.
  * @param hpssi Pointer to a hal_pssi_handle_t
  * @return Pointer to the user data.
  */
const void *HAL_PSSI_GetUserData(const hal_pssi_handle_t *hpssi)
{
  ASSERT_DBG_PARAM(hpssi != NULL);
  ASSERT_DBG_STATE(hpssi->global_state, PSSI_STATE_ALL);

  return (hpssi->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_PSSI_USER_DATA */

/**
  * @}
  */

/** @addtogroup PSSI_Private_Functions
  * @{
  */
#if defined(USE_HAL_PSSI_DMA) && (USE_HAL_PSSI_DMA == 1U)
/**
  * @brief  DMA PSSI slave transmit process complete callback.
  * @param  hdma DMA handle
  */
static void PSSI_DMATransmitCplt(hal_dma_handle_t *hdma)
{
  /* Derogation MISRAC2012-Rule-11.5 */
  hal_pssi_handle_t *hpssi = (hal_pssi_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);

  PSSI_TypeDef *p_pssix = PSSI_GET_INSTANCE(hpssi);

  /* If last transfer, set global_state to IDLE */
  if (hpssi->xfer_count == 0U)
  {
    hpssi->global_state = HAL_PSSI_STATE_IDLE;

    /* Call the corresponding callback to inform upper layer of End of Transfer */
#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
    hpssi->p_tx_cplt_cb(hpssi);
#else
    HAL_PSSI_TxCpltCallback(hpssi);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */
  }
  /* else prepare a new DMA transfer */
  else
  {
    /* Update Buffer pointer */
    hpssi->p_buf_ptr += hpssi->xfer_size_byte;

    /* Set the XferSize to transfer */
    if (hpssi->xfer_count > PSSI_MAX_NBYTE_SIZE)
    {
      hpssi->xfer_size_byte = PSSI_MAX_NBYTE_SIZE;
    }
    else
    {
      hpssi->xfer_size_byte = hpssi->xfer_count;
    }

    if (HAL_DMA_StartPeriphXfer_IT_Opt(hpssi->hdma_tx,
                                       (uint32_t)hpssi->p_buf_ptr, (uint32_t)&p_pssix->DR,
                                       hpssi->xfer_size_byte, HAL_DMA_OPT_IT_NONE) != HAL_OK)
    {
      PSSI_Disable(p_pssix);
      PSSI_DisableDMA(p_pssix);

      /* Disable Interrupts */
      HAL_PSSI_DisableIT_OVR_UDR(hpssi);

#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
      hpssi->last_error_codes = HAL_PSSI_ERROR_DMA;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

      hpssi->global_state = HAL_PSSI_STATE_IDLE;

      /* Call the corresponding callback to inform upper layer of End of Transfer */
#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
      hpssi->p_error_cb(hpssi);
#else
      HAL_PSSI_ErrorCallback(hpssi);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */
    }
    else
    {
      /* Update xfer_count value */
      hpssi->xfer_count -= hpssi->xfer_size_byte;
    }
  }
}

/**
  * @brief  DMA PSSI master receive process complete callback.
  * @param  hdma DMA handle
  */
static void PSSI_DMAReceiveCplt(hal_dma_handle_t *hdma)
{
  /* Derogation MISRAC2012-Rule-11.5 */
  hal_pssi_handle_t *hpssi = (hal_pssi_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);

  PSSI_TypeDef *p_pssix = PSSI_GET_INSTANCE(hpssi);

  /* If last transfer, Disable PSSI and Disable DMA */
  if (hpssi->xfer_count == 0U)
  {
    PSSI_Disable(p_pssix);
    PSSI_DisableDMA(p_pssix);

    /* Disable Interrupts */
    HAL_PSSI_DisableIT_OVR_UDR(hpssi);

    hpssi->global_state = HAL_PSSI_STATE_IDLE;

    /* Call the corresponding callback to inform upper layer of End of Transfer */
#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
    hpssi->p_rx_cplt_cb(hpssi);
#else
    HAL_PSSI_RxCpltCallback(hpssi);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */
  }
  /* else prepare a new DMA transfer */
  else
  {
    /* Update Buffer pointer */
    hpssi->p_buf_ptr += hpssi->xfer_size_byte;

    /* Set the XferSize to transfer */
    if (hpssi->xfer_count > PSSI_MAX_NBYTE_SIZE)
    {
      hpssi->xfer_size_byte = PSSI_MAX_NBYTE_SIZE;
    }
    else
    {
      hpssi->xfer_size_byte = hpssi->xfer_count;
    }

    if (HAL_DMA_StartPeriphXfer_IT_Opt(hpssi->hdma_rx,
                                       (uint32_t)&p_pssix->DR, (uint32_t)hpssi->p_buf_ptr,
                                       hpssi->xfer_size_byte, HAL_DMA_OPT_IT_NONE) != HAL_OK)
    {
      PSSI_Disable(p_pssix);
      PSSI_DisableDMA(p_pssix);

      /* Disable Interrupts */
      HAL_PSSI_DisableIT_OVR_UDR(hpssi);

#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
      hpssi->last_error_codes = HAL_PSSI_ERROR_DMA;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

      hpssi->global_state = HAL_PSSI_STATE_IDLE;

      /* Call the corresponding callback to inform upper layer of End of Transfer */
#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
      hpssi->p_error_cb(hpssi);
#else
      HAL_PSSI_ErrorCallback(hpssi);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */
    }
    else
    {
      /* Update xfer_count value */
      hpssi->xfer_count -= hpssi->xfer_size_byte;
    }
  }
}

/**
  * @brief DMA PSSI communication abort callback
  *        (To be called at end of DMA Abort procedure).
  * @param hdma DMA handle.
  */
static void PSSI_DMAAbort(hal_dma_handle_t *hdma)
{
  /* Derogation MISRAC2012-Rule-11.5 */
  hal_pssi_handle_t *hpssi = (hal_pssi_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);

  /* Reset AbortCpltCallback */
  if (hpssi->hdma_tx != NULL)
  {
    hpssi->hdma_tx->p_xfer_abort_cb = NULL;
  }

  if (hpssi->hdma_rx != NULL)
  {
    hpssi->hdma_rx->p_xfer_abort_cb = NULL;
  }

  /* Check if it comes from a user abort */
  if (hpssi->global_state == HAL_PSSI_STATE_ABORT)
  {
    hpssi->global_state = HAL_PSSI_STATE_IDLE;

    /* Call the corresponding callback to inform upper layer of End of Transfer */
#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
    hpssi->p_abort_cplt_cb(hpssi);
#else
    HAL_PSSI_AbortCpltCallback(hpssi);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */
  }
  else
  {
    hpssi->global_state = HAL_PSSI_STATE_IDLE;

    /* Call the corresponding callback to inform upper layer of End of Transfer */
#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
    hpssi->p_error_cb(hpssi);
#else
    HAL_PSSI_ErrorCallback(hpssi);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */
  }
}
#endif /* USE_HAL_PSSI_DMA */

/**
  * @brief  This function handles PSSI Communication Timeout.
  * @param  hpssi Pointer to a hal_pssi_handle_t structure.
  * @param  flag Specifies the PSSI flag to check.
  * @param  status The new Flag status (SET or RESET).
  * @param  timeout_ms Timeout duration
  * @retval HAL_TIMEOUT Timeout exceeded
  * @retval HAL_OK Operation completed successfully
  */
static hal_status_t PSSI_WaitOnStatusUntilTimeout(hal_pssi_handle_t *hpssi, uint32_t flag, FlagStatus status,
                                                  uint32_t timeout_ms)
{
  /* Init tickstart for timeout management*/
  uint32_t tickstart = HAL_GetTick();

  hal_status_t status_tmp = HAL_OK;

  while (HAL_PSSI_IsActiveFlag_SR(hpssi, flag) == (uint32_t)status)
  {
    /* Check for the Timeout */
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        if (HAL_PSSI_IsActiveFlag_SR(hpssi, flag) == (uint32_t)status)
        {
          PSSI_Disable(PSSI_GET_INSTANCE(hpssi));
          hpssi->global_state = HAL_PSSI_STATE_IDLE;
          status_tmp = HAL_TIMEOUT;
        }
        break;
      }
    }
  }
  return status_tmp;
}

#if defined(USE_HAL_PSSI_DMA) && (USE_HAL_PSSI_DMA == 1U)
/**
  * @brief  This function handles PSSI DMA error.
  * @param  hdma Pointer to a hal_dma_handle_t structure that contains.
  */
static void PSSI_DMAError(hal_dma_handle_t *hdma)
{
  /* Derogation MISRAC2012-Rule-11.5 */
  hal_pssi_handle_t *hpssi = (hal_pssi_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);

  PSSI_Disable(PSSI_GET_INSTANCE(hpssi));
  PSSI_DisableDMA(PSSI_GET_INSTANCE(hpssi));

  HAL_PSSI_DisableIT_OVR_UDR(hpssi);

  /* Call the corresponding callback to inform upper layer of End of Transfer */
  if (hpssi->global_state == HAL_PSSI_STATE_ABORT)
  {
#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1U)
    hpssi->last_error_codes |= HAL_PSSI_ERROR_DMA;
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

    /* Call the corresponding callback to inform upper layer of End of Transfer */
#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
    hpssi->p_abort_cplt_cb(hpssi);
#else
    HAL_PSSI_AbortCpltCallback(hpssi);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */
  }
  else
  {
    /* Call the corresponding callback to inform upper layer of End of Transfer */
#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
    hpssi->p_error_cb(hpssi);
#else
    HAL_PSSI_ErrorCallback(hpssi);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */
  }

  hpssi->global_state = HAL_PSSI_STATE_IDLE;
}
#endif /* USE_HAL_PSSI_DMA */

/**
  * @brief  Enable the PSSI.
  * @param  p_instance PSSI Instance
  */
__STATIC_INLINE void PSSI_Enable(PSSI_TypeDef *p_instance)
{
  SET_BIT(p_instance->CR, PSSI_CR_ENABLE);
}
/**
  * @brief  Disable the PSSI.
  * @param  p_instance PSSI handle
  */
__STATIC_INLINE void PSSI_Disable(PSSI_TypeDef *p_instance)
{
  CLEAR_BIT(p_instance->CR, PSSI_CR_ENABLE);
}

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
/**
  * @brief  Get the current HAL PSSI handle Width configuration.
  * @param  p_instance PSSI Instance.
  * @retval HAL_PSSI_BUS_WIDTH_8LINE
  * @retval HAL_PSSI_BUS_WIDTH_16LINE
  */
__STATIC_INLINE hal_pssi_bus_width_t PSSI_GetBusWidth(const PSSI_TypeDef *p_instance)
{
  return (hal_pssi_bus_width_t)(uint32_t)(READ_BIT(p_instance->CR, PSSI_CR_EDM));
}
#endif /* USE_HAL_CHECK_PARAM */

/**
  * @brief  Configure PSSI Control Signal.
  * @param  p_instance PSSI Instance.
  * @param  control_signal This parameter can be one of @ref hal_pssi_control_signal_t
  * @note   This bit can only be programmed when the PSSI is disabled (ENABLE = 0).
  */
__STATIC_INLINE void PSSI_SetControlSignal(PSSI_TypeDef *p_instance, const uint32_t control_signal)
{
  MODIFY_REG(p_instance->CR, PSSI_CR_DERDYCFG, control_signal);
}
/**
  * @brief  Get the current PSSI Control Signal configuration.
  * @param  p_instance PSSI Instance.
  * @retval HAL_PSSI_CONTROL_SIGNAL_DE_RDY_DISABLE
  * @retval HAL_PSSI_CONTROL_SIGNAL_RDY_ENABLE
  * @retval HAL_PSSI_CONTROL_SIGNAL_DE_ENABLE
  * @retval HAL_PSSI_CONTROL_SIGNAL_DE_RDY_ALT_ENABLE
  * @retval HAL_PSSI_CONTROL_SIGNAL_MAP_RDY_BIDIR_ENABLE
  * @retval HAL_PSSI_CONTROL_SIGNAL_RDY_MAP_ENABLE
  * @retval HAL_PSSI_CONTROL_SIGNAL_DE_MAP_ENABLE
  * @retval HAL_PSSI_CONTROL_SIGNAL_MAP_DE_BIDIR_ENABLE
  */
__STATIC_INLINE hal_pssi_control_signal_t PSSI_GetControlSignal(const PSSI_TypeDef *p_instance)
{
  return (hal_pssi_control_signal_t)(uint32_t)(READ_BIT(p_instance->CR, PSSI_CR_DERDYCFG));
}

/**
  * @brief  Configure PSSI Data Enable Polarity.
  * @param  p_instance PSSI Instance.
  * @param  data_enable_polarity This parameter can be one of @ref hal_pssi_data_enable_polarity_t
  * @note   This bit can only be programmed when the PSSI is disabled (ENABLE = 0).
  */
__STATIC_INLINE void PSSI_SetDataEnablePolarity(PSSI_TypeDef *p_instance, const uint32_t data_enable_polarity)
{
  MODIFY_REG(p_instance->CR, PSSI_CR_DEPOL, data_enable_polarity);
}

/**
  * @brief  Get the current PSSI Data Enable Polarity configuration.
  * @param  p_instance PSSI Instance.
  * @retval HAL_PSSI_DATA_ENABLE_POLARITY_LOW
  * @retval HAL_PSSI_DATA_ENABLE_POLARITY_HIGH
  */
__STATIC_INLINE hal_pssi_data_enable_polarity_t PSSI_GetDataEnablePolarity(const PSSI_TypeDef *p_instance)
{
  return (hal_pssi_data_enable_polarity_t)(uint32_t)(READ_BIT(p_instance->CR, PSSI_CR_DEPOL));
}

/**
  * @brief  Configure PSSI Ready Polarity.
  * @param  p_instance PSSI Instance.
  * @param  ready_polarity This parameter can be one of @ref hal_pssi_ready_polarity_t
  * @note   This bit can only be programmed when the PSSI is disabled (ENABLE = 0).
  */
__STATIC_INLINE void PSSI_SetReadyPolarity(PSSI_TypeDef *p_instance, const uint32_t ready_polarity)
{
  MODIFY_REG(p_instance->CR, PSSI_CR_RDYPOL, ready_polarity);
}

/**
  * @brief  Get the current PSSI Ready Polarity configuration.
  * @param  p_instance PSSI Instance.
  * @retval HAL_PSSI_READY_POLARITY_LOW
  * @retval HAL_PSSI_READY_POLARITY_HIGH
  */
__STATIC_INLINE hal_pssi_ready_polarity_t PSSI_GetReadyPolarity(const PSSI_TypeDef *p_instance)
{
  return (hal_pssi_ready_polarity_t)(uint32_t)(READ_BIT(p_instance->CR, PSSI_CR_RDYPOL));
}

/**
  * @brief  Configure PSSI Clock Polarity.
  * @param  p_instance PSSI Instance.
  * @param  clock_polarity This parameter can be one of @ref hal_pssi_clock_polarity_t
  * @note   This bit can only be programmed when the PSSI is disabled (ENABLE = 0).
  */
__STATIC_INLINE void PSSI_SetClockPolarity(PSSI_TypeDef *p_instance, const uint32_t clock_polarity)
{
  MODIFY_REG(p_instance->CR, PSSI_CR_CKPOL, clock_polarity);
}

/**
  * @brief  Get the current PSSI Clock Polarity configuration.
  * @param  p_instance PSSI Instance.
  * @retval HAL_PSSI_CLOCK_POLARITY_RX_FALLING_TX_RISING_EDGE
  * @retval HAL_PSSI_CLOCK_POLARITY_RX_RISING_TX_FALLING_EDGE
  */
__STATIC_INLINE hal_pssi_clock_polarity_t PSSI_GetClockPolarity(const PSSI_TypeDef *p_instance)
{
  return (hal_pssi_clock_polarity_t)(uint32_t)(READ_BIT(p_instance->CR, PSSI_CR_CKPOL));
}


#if defined(USE_HAL_PSSI_DMA) && (USE_HAL_PSSI_DMA == 1U)
/**
  * @brief  Disable DMA bit.
  * @param  p_instance PSSI Instance.
  */
__STATIC_INLINE void PSSI_DisableDMA(PSSI_TypeDef *p_instance)
{
  CLEAR_BIT(p_instance->CR, PSSI_CR_DMAEN);
}
/**
  * @brief  Check if DMA bit is enabled or disabled.
  * @param  p_instance PSSI Instance.
  * @retval 0 DMA is disabled.
  * @retval 1 DMA is enabled.
  */
__STATIC_INLINE uint32_t PSSI_IsEnabledDMA(const PSSI_TypeDef *p_instance)
{
  return ((READ_BIT(p_instance->CR, PSSI_CR_DMAEN) == (PSSI_CR_DMAEN)) ? 1UL : 0UL);
}
#endif /* USE_HAL_PSSI_DMA */

/**
  * @brief  Write 8 bit in data register
  * @param  p_instance PSSI Instance
  * @param  p_data 0..0xFF
  */
__STATIC_INLINE void PSSI_WriteData8(PSSI_TypeDef *p_instance, const uint8_t p_data)
{
  *((volatile uint8_t *)&p_instance->DR) = p_data;
}

/**
  * @brief  Write 16 bit in data register
  * @param  p_instance PSSI Instance
  * @param  p_data 0..0xFFFF
  */
__STATIC_INLINE void PSSI_WriteData16(PSSI_TypeDef *p_instance, const uint16_t p_data)
{
#if defined(__GNUC__)
  volatile uint16_t *pssidr = ((volatile uint16_t *)&p_instance->DR);
  *pssidr = p_data;
#else
  *((volatile uint16_t *)&p_instance->DR) = p_data;
#endif /* __GNUC__ */
}

/**
  * @brief  Write 32 bit in data register
  * @param  p_instance PSSI Instance
  * @param  p_data 0..0xFFFFFFFF
  */
__STATIC_INLINE void PSSI_WriteData32(PSSI_TypeDef *p_instance, const uint32_t p_data)
{
  *((volatile uint32_t *)&p_instance->DR) = p_data;
}

/**
  * @brief  Read 8 bit from data register
  * @param  p_instance PSSI Instance
  * @return uint8_t Value read in data register (0x00..0xFF)
  */
__STATIC_INLINE uint8_t PSSI_ReadData8(PSSI_TypeDef *p_instance)
{
  return (*((volatile uint8_t *)&p_instance->DR));
}

/**
  * @brief  Read 16 bit from data register
  * @param  p_instance PSSI Instance
  * @return uint16_t Value read in data register (0x0000..0xFFFF)
  */
__STATIC_INLINE uint16_t PSSI_ReadData16(PSSI_TypeDef *p_instance)
{
#if defined(__GNUC__)
  volatile uint16_t *pssidr = (volatile uint16_t *)(&(p_instance->DR));
  return (*pssidr);
#else
  return (*((volatile uint16_t *)&p_instance->DR));
#endif /* __GNUC__ */
}

/**
  * @brief  Read 32 bit from data register
  * @param  p_instance PSSI Instance
  * @return uint32_t Value read in data register (0x00000000..0xFFFFFFFF)
  */
__STATIC_INLINE uint32_t PSSI_ReadData32(PSSI_TypeDef *p_instance)
{
  return (*((volatile uint32_t *)&p_instance->DR));
}

/**
  * @}
  */
#endif /* PSSI */
#endif /* HAL_PSSI_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
