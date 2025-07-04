
Improved driver mechanisms
**************************

To reinforce thread safety and prevent race condition in some functional cases

____

.. _breaking_concepts_concept_F1:

Revise and optimize the HAL state machine.
===========================================

In HAL2, when a HAL driver is built around a handle object, the state machine implementation and usage are updated according to the following principles:

- **State Transition Management**: The state machines are designed to ensure proper transitions between the driver's functional states. This helps maintain a clear and controlled flow of operations within the driver.
- **Not for Lock Mechanism**: The state machines are not intended to be used as a lock mechanism. Their purpose is to manage state transitions, not to control access to resources.
- **Not for Identifying Functional Modes**: The state machines are not meant to identify functional modes (e.g., I2C master/slave mode). Functional modes are managed separately from the state machine.
- **Unitary States**: The states are revised to be unitary, relative to a single process step. The state variable within the HAL PPP handle is designed to handle one state at a time, ensuring no mixing between different states in HAL2.
- **Dedicated Assertions for State Checks**: In HAL2, state checks are performed through dedicated assertions, allowing the footprint to be reduced when not in debug mode. This ensures that state validation does not impact performance in production builds.

.. _breaking_concepts_concept_F1_global_state_machine:

Global state machine
---------------------
In HAL2, each HAL driver that is built around a handle provides a global state machine with the following minimum states to manage the driver's functional states effectively:

- **HAL_PPP_STATE_RESET = 0**: This is the default state when the handle is not initialized with the appropriate ``HAL_PPP_Init`` function. It is also the state that shall be set during the ``HAL_PPP_DeInit()`` service. This state indicates that the driver is in its default, uninitialized state.

- **HAL_PPP_STATE_INIT**: The appropriate ``HAL_PPP_Init`` function shall apply this state when the initialization is performed. This involves resetting the handle object and linking it to the physical instance. This state indicates that the HAL handle is initialized but the corresponding peripheral instance is not yet ready to start a process.

- **HAL_PPP_STATE_IDLE**: This state shall be applied by a global configuration API, such as ``HAL_PPP_SetConfig``. It indicates that a global configuration has been applied and the driver is ready to start a process that does not require a sub-block configuration. Examples include UART transmit or I2C receive operations.

- **HAL_PPP_STATE_FAULT**: This state indicates that the peripheral has encountered a fatal error that requires a recovery sequence in the application code. This state shall only be provided if the peripheral can encounter a non-recoverable blocking error that necessitates a recovery sequence. If the peripheral does not have such errors, this state should not be included.

The global state is stored within the HAL PPP handle structure, which links the state machine to the peripheral instance. The function ``HAL_PPP_GetState`` is provided to allow retrieval of the global state.

Global state machine example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
When the peripheral allows a single process at a time (e.g., I2C), the global state machine is extended to include the different process states.
This ensures that the driver can accurately reflect the current operation being performed by the peripheral.

Example:

.. list-table::
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

         typedef enum
         {
           /* Peripheral is not yet Initialized */
           HAL_I2C_STATE_RESET             = 0x00U,

           /* Peripheral Initialized and ready for use */
           HAL_I2C_STATE_READY             = 0x20U,

           /* An internal process is ongoing */
           HAL_I2C_STATE_BUSY              = 0x24U,

           /* Data Transmission process is ongoing */
           HAL_I2C_STATE_BUSY_TX           = 0x21U,

           /* Data Reception process is ongoing */
           HAL_I2C_STATE_BUSY_RX           = 0x22U,

           /* Address Listen Mode is ongoing */
           HAL_I2C_STATE_LISTEN            = 0x28U,

           /* Address Listen Mode and Data Transmission process is ongoing */
           HAL_I2C_STATE_BUSY_TX_LISTEN    = 0x29U,

           /* Address Listen Mode and Data Reception process is ongoing */
           HAL_I2C_STATE_BUSY_RX_LISTEN    = 0x2AU,

           /* Abort user request ongoing */
           HAL_I2C_STATE_ABORT             = 0x60U,

           /* Timeout state */
           HAL_I2C_STATE_TIMEOUT           = 0xA0U,

           /* Error */
           HAL_I2C_STATE_ERROR             = 0xE0U
         } HAL_I2C_StateTypeDef;

         typedef struct __I2C_HandleTypeDef
         {

           I2C_TypeDef                *Instance;

           __IO HAL_I2C_StateTypeDef  State;
         } I2C_HandleTypeDef;

         HAL_I2C_StateTypeDef HAL_I2C_GetState(I2C_HandleTypeDef *hi2c);
     - .. code-block:: c

         typedef enum
         {
           /* Not yet Initialized */
           HAL_I2C_STATE_RESET     = (0UL),

           /* Initialized but not yet configured */
           HAL_I2C_STATE_INIT      = (1UL << 31),

           /* Initialized and a global config applied */
           HAL_I2C_STATE_IDLE      = (1UL << 30),

           /* Data Transmission process is ongoing */
           HAL_I2C_STATE_TX        = (1UL << 29),

           /* Data Reception process is ongoing */
           HAL_I2C_STATE_RX        = (1UL << 28),

           /* Address Listen Mode is ongoing */
           HAL_I2C_STATE_LISTEN    = (1UL << 27),

           /* Address Listen Mode and Data Transmission process is ongoing */
           HAL_I2C_STATE_TX_LISTEN = (1UL << 26),

           /* Address Listen Mode and Data Reception process is ongoing */
           HAL_I2C_STATE_RX_LISTEN = (1UL << 25),

           /* Abort user request ongoing */
           HAL_I2C_STATE_ABORT     = (1UL << 24),
         } hal_i2c_state_t;






         typedef struct hal_i2c_handle_s hal_i2c_handle_t;
         struct hal_i2c_handle_s
         {
           hal_i2c_t                   instance;   


           volatile hal_i2c_state_t    global_state;
         };

         hal_i2c_state_t HAL_I2C_GetState(const hal_i2c_handle_t *hi2c);

.. _breaking_concepts_concept_F1_simultaneous_parallel_processes:

Case of Simultaneous parallel processes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When the peripheral allows several process in parallel Ex UART Tx/Rx, The global state machine contains the 3 basic states only: RESET, INIT and CONFIGURED.
The global state machine is not used for process state transitions.
Instead, each process has its own dedicated state machine that reflects its specific states.
The function ``HAL_PPP_GetState`` is provided to retrieve the global state.
Additionally, for each process state machine, a dedicated function is provided. For example, ``HAL_UART_GetState``, ``HAL_UART_GetTxState``, and ``HAL_UART_GetRxState``.

Example:

.. list-table::
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

         /* Peripheral is not initialized
            Value is allowed for gState and RxState */
         #define  HAL_UART_STATE_RESET         0x00000000U

         /* Peripheral Initialized and ready for use
            Value is allowed for gState and RxState */
         #define  HAL_UART_STATE_READY         0x00000020U

         /* An internal process is ongoing
            Value is allowed for gState only */
         #define  HAL_UART_STATE_BUSY          0x00000024U

         /* Data Transmission process is ongoing
            Value is allowed for gState only */
         #define  HAL_UART_STATE_BUSY_TX       0x00000021U

         /* Data Reception process is ongoing
            Value is allowed for RxState only */
         #define  HAL_UART_STATE_BUSY_RX       0x00000022U

         /* Data Transmission and Reception process is ongoing
            Not to be used for neither gState nor RxState. Value is result
            of combination (Or) between gState and RxState values */
         #define  HAL_UART_STATE_BUSY_TX_RX    0x00000023U

         /* Timeout state
            Value is allowed for gState only */
         #define  HAL_UART_STATE_TIMEOUT       0x000000A0U

         /* Error
            Value is allowed for gState only */
         #define  HAL_UART_STATE_ERROR         0x000000E0U

         typedef uint32_t HAL_UART_StateTypeDef;










         typedef struct __UART_HandleTypeDef
         {
           USART_TypeDef            *Instance;

           __IO HAL_UART_StateTypeDef    gState;
           __IO HAL_UART_StateTypeDef    RxState; 
         } UART_HandleTypeDef;


         HAL_UART_StateTypeDef HAL_UART_GetState(UART_HandleTypeDef *huart);
     - .. code-block:: c

         typedef enum
         {
           /*! Peripheral is not initialized */
           HAL_UART_STATE_RESET                     = 0U,

           /*! Peripheral is initialized but not configured */
           HAL_UART_STATE_INIT                      = (1UL << 31U),

           /*! Peripheral is initialized and a global config is set */
           HAL_UART_STATE_CONFIGURED                = (1UL << 30U),
         } hal_uart_state_t;

         typedef enum
         {
           /*! Data Reception process is in reset */
           HAL_UART_RX_STATE_RESET                  = 1U,

           /*! Data Reception process is idling */
           HAL_UART_RX_STATE_IDLE                   = (1UL << 31U),

           /*! Data Reception process is ongoing */
           HAL_UART_RX_STATE_ACTIVE                 = (1UL << 30U),

           /*! Data Reception process is aborting */
           HAL_UART_RX_STATE_ABORT                  = (1UL << 29U),
         } hal_uart_rx_state_t;

         typedef enum
         {
           /*! Data Transmission process is in reset */
           HAL_UART_TX_STATE_RESET                  = 1U,

           /*! Data Transmission process is idling */
           HAL_UART_TX_STATE_IDLE                   = (1UL << 31U),

           /*! Data Transmission process is ongoing */
           HAL_UART_TX_STATE_ACTIVE                 = (1UL << 30U),

           /*! Data Transmission process is aborting */
           HAL_UART_TX_STATE_ABORT                  = (1UL << 29U),
         } hal_uart_tx_state_t;

         typedef struct hal_uart_handle_s hal_uart_handle_t;

         struct hal_uart_handle_s
         {
           hal_uart_t instance;

           volatile hal_uart_state_t global_state;
           volatile hal_uart_rx_state_t    rx_state;
           volatile hal_uart_tx_state_t    tx_state;
         };

         hal_uart_state_t HAL_UART_GetState(const hal_uart_handle_t *huart);
         hal_uart_tx_state_t HAL_UART_GetTxState(const hal_uart_handle_t *huart);
         hal_uart_rx_state_t HAL_UART_GetRxState(const hal_uart_handle_t *huart);

.. _breaking_concepts_concept_F1_sub_instances:

Case of sub-instances process management
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
When the peripheral includes several ``sub-instance processes`` (e.g., TIMER ``channels``):

- The global state machine contains handle to global state of the peripheral but the sub-instances states.
- Each sub-instance has its own dedicated state machine that reflects its specific states (e.g., TIM channel state machine).
- These sub-instance states should account for sub-blocks when available.
  For example, IC (Input Compare) and OC (Output Compare) are sub-blocks Of the TIM.

Example:

.. list-table::
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

         typedef enum
         {
           /* Peripheral not yet initialized or disabled */
           HAL_TIM_STATE_RESET             = 0x00U,

           /* Peripheral Initialized and ready for use */
           HAL_TIM_STATE_READY             = 0x01U,

           /* An internal process is ongoing */
           HAL_TIM_STATE_BUSY              = 0x02U,

           /* Timeout state */
           HAL_TIM_STATE_TIMEOUT           = 0x03U,

           /* Reception process is ongoing */
           HAL_TIM_STATE_ERROR             = 0x04U
         } HAL_TIM_StateTypeDef;


         typedef enum
         {
           /* TIM Channel initial state */
           HAL_TIM_CHANNEL_STATE_RESET             = 0x00U,

           /* TIM Channel ready for use */
           HAL_TIM_CHANNEL_STATE_READY             = 0x01U,

           /* An internal process is ongoing on the TIM channel */
           HAL_TIM_CHANNEL_STATE_BUSY              = 0x02U
         } HAL_TIM_ChannelStateTypeDef;

         typedef enum
         {
           /* DMA Burst initial state */
           HAL_DMA_BURST_STATE_RESET             = 0x00U,

           /* DMA Burst ready for use */
           HAL_DMA_BURST_STATE_READY             = 0x01U,

           /* Ongoing DMA Burst */
           HAL_DMA_BURST_STATE_BUSY              = 0x02U
         } HAL_TIM_DMABurstStateTypeDef;






         typedef struct __TIM_HandleTypeDef
         {
           TIM_TypeDef                        *Instance;

           __IO HAL_TIM_StateTypeDef          State;
           __IO HAL_TIM_ChannelStateTypeDef   ChannelState[6];
           __IO HAL_TIM_ChannelStateTypeDef   ChannelNState[4];
         } TIM_HandleTypeDef;

         HAL_TIM_StateTypeDef
         HAL_TIM_Base_GetState(TIM_HandleTypeDef *htim);

         HAL_TIM_StateTypeDef
         HAL_TIM_OC_GetState(TIM_HandleTypeDef *htim);

         HAL_TIM_StateTypeDef
         HAL_TIM_PWM_GetState(TIM_HandleTypeDef *htim);
         HAL_TIM_StateTypeDef
         HAL_TIM_IC_GetState(TIM_HandleTypeDef *htim);
         HAL_TIM_StateTypeDef
         HAL_TIM_OnePulse_GetState(TIM_HandleTypeDef *htim);
         HAL_TIM_StateTypeDef
         HAL_TIM_Encoder_GetState(TIM_HandleTypeDef *htim);

         HAL_TIM_ChannelStateTypeDef
         HAL_TIM_GetChannelState(TIM_HandleTypeDef *htim,
                                 uint32_t Channel);

         HAL_TIM_DMABurstStateTypeDef
         HAL_TIM_DMABurstState(TIM_HandleTypeDef *htim);
     - .. code-block:: c

         typedef enum
         {
           /** Peripheral not yet initialized                     */
           HAL_TIM_STATE_RESET   = 0U,

           /** Peripheral initialized but not yet configured      */
           HAL_TIM_STATE_INIT    = (1UL << 31U),

           /** Peripheral initialized and a global config applied */
           HAL_TIM_STATE_IDLE    = (1UL << 30U),

           /** Counter is running */
           HAL_TIM_STATE_ACTIVE  = (1UL << 29U),

           HAL_TIM_STATE_ACTIVE_SILENT = (HAL_TIM_STATE_ACTIVE | HAL_TIM_ACTIVE_SILENT),

         } hal_tim_state_t;

         /**
           * @brief  TIM Channel States definition
           */
         typedef enum
         {
           /** TIM Channel initial state */
           HAL_TIM_CHANNEL_STATE_RESET       = (1UL << 31U),

           /** TIM Channel ready for use as output channel  */
           HAL_TIM_OC_CHANNEL_STATE_IDLE     = (1UL << 30U),

           /** An internal process is ongoing on the TIM output channel */
           HAL_TIM_OC_CHANNEL_STATE_ACTIVE   = (1UL << 29U),

           /** An internal process is ongoing on the TIM output channel in DMA silent mode */
           HAL_TIM_OC_CHANNEL_STATE_ACTIVE_SILENT,

           /** TIM Channel ready for use as input channel               */
           HAL_TIM_IC_CHANNEL_STATE_IDLE     = (1UL << 28U),

           /** An internal process is ongoing on the TIM input channel  */
           HAL_TIM_IC_CHANNEL_STATE_ACTIVE   = (1UL << 27U),

           /** An internal process is ongoing on the TIM input channel in DMA silent mode */
           HAL_TIM_IC_CHANNEL_STATE_ACTIVE_SILENT

         } hal_tim_channel_state_t;

         typedef struct hal_tim_handle_s hal_tim_handle_t;

         struct hal_tim_handle_s
         {
           hal_tim_t instance;

           volatile hal_tim_state_t global_state;
           volatile hal_tim_channel_state_t channel_states[HAL_TIM_CHANNELS];
         };





         hal_tim_state_t
         HAL_TIM_GetState(const hal_tim_handle_t *htim);










         hal_tim_channel_state_t
         HAL_TIM_GetChannelState(const hal_tim_handle_t *htim,
                                 hal_tim_channel_t channel);


____

.. _breaking_concepts_concept_F2:

Revise and optimize the status return of HAL APIs.
==================================================
The HAL APIs return status are reworked and optimized in HAL2 compared to HAL1 according to the following:

.. list-table::
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

         typedef enum
         {
           HAL_OK       = 0x00,
           HAL_ERROR    = 0x01,
           HAL_BUSY     = 0x02,

           HAL_TIMEOUT  = 0x03
         } HAL_StatusTypeDef;
     - .. code-block:: c

         typedef enum
         {
           HAL_OK            = 0x00000000U,
           HAL_ERROR         = 0xFFFFFFFFU,
           HAL_BUSY          = 0x55555555U,
           HAL_INVALID_PARAM = 0xAAAAAAAAU,
           HAL_TIMEOUT       = 0x5A5A5A5AU 
         } hal_status_t;

.. note::

   In HAL2:
   
   - ``HAL_ERROR`` is returned in case of an internal error, including exceeding an intrinsic hardware timeout.
   - ``HAL_INVALID_PARAM`` is returned in case of an invalid parameter that can lead to a hard fault or a memory exception (e.g., null pointer).
   - ``HAL_BUSY`` is returned when trying to start a process while a concurrent one is ongoing.
   - ``HAL_TIMEOUT`` is used exclusively when the operation exceeds the user-defined timeout (e.g., Polling API with user timeout as a parameter).

.. note::

   In HAL2, the values of the ``hal_status_t`` enumeration are set to have a minimum Hamming distance of at least 8 for function return values.
   This is to ensure compliance with the secure coding rule: "Return value of sensitive function must have a Hamming distance of at least 8."

____
   
.. _breaking_concepts_concept_F3:

Revise and optimize HAL error management.
=========================================
Regarding error management, almost the same principles remain applicable in HAL2 as in HAL1 (with some minor renaming).
This means that a driver built around a handle holds inside the handle the last occurred errors during processing.
This ``last_error_codes`` variable is reset in the ``HAL_PPP_Init`` and then at the beginning of each process function.

The error codes are retrievable thanks to the ``HAL_PPP_GetLastErrorCodes`` function in HAL2, which offers the same services
as the HAL1 ``HAL_PPP_GetError``.

A new feature in HAL2 compared to HAL1 is that the error code storing and retrieval are now optional and available under
a dedicated compilation define ``USE_HAL_PPP_GET_LAST_ERRORS``.
The error code details are available when the define ``USE_HAL_PPP_GET_LAST_ERRORS`` is set to ``1`` in the HAL configuration header file
(e.g., ``stm32u5xx_hal_conf.h``).
By default, the define ``USE_HAL_PPP_GET_LAST_ERRORS`` is set to zero, allowing to save footprint related to error code management.
If the error code details are needed, the HAL configuration header file must be edited to set the define ``USE_HAL_PPP_GET_LAST_ERRORS`` to ``1``.

Additionally, in HAL2, the error codes have been rationalized as follows:

- Error codes reflect only the process errors, i.e., the errors that are relative to the peripheral process execution and correspond to HW error flags:

  - The ``HAL_PPP_ERROR_INVALID_PARAM`` error code is removed.
    A function encountering a wrong parameter will simply return ``HAL_INVALID_PARAM`` without saving the issue as an error code.
    See also :ref:`breaking_concepts_concept_F2`.
  - The ``HAL_PPP_ERROR_INVALID_CALLBACK`` error code is removed.
    The register callback HAL function simply returns ``HAL_INVALID_PARAM`` in case of an invalid callback pointer without saving the issue as an error code.
  - The ``HAL_PPP_ERROR_TIMEOUT`` error code is kept only in case the peripheral provides a HW timeout error flag.
    If a timeout occurs within a HAL processing function due to exceeding a user timeout given within the function parameters,
    the function simply returns ``HAL_TIMEOUT``, without storing the issue in the error codes.
    See also :ref:`breaking_concepts_concept_F2`.
  - Error codes are provided as bitmapped defines and organized/grouped by:
    - Common errors: for processes common errors.
    - Specific process #i errors (for both cases: single process at a time and parallel processes).
    - This also allows retrieving all last errors combined using ``uint32_t HAL_PPP_GetLastErrors(hppp)`` for both cases: single process at a time and parallel processes.

Examples:

.. list-table::
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

         /*  No error */
         #define HAL_SPI_ERROR_NONE    (0x00000000UL)

         /* MODF error */
         #define HAL_SPI_ERROR_MODF    (0x00000001UL)

         /* CRC error */
         #define HAL_SPI_ERROR_CRC     (0x00000002UL)

         /* OVR error */
         #define HAL_SPI_ERROR_OVR     (0x00000004UL)

         /* FRE error */
         #define HAL_SPI_ERROR_FRE     (0x00000008UL)

         /* DMA transfer error */
         #define HAL_SPI_ERROR_DMA     (0x00000010UL)

         /* Error on RXNE/TXE/BSY/FTLVL/FRLVL Flag */
         #define HAL_SPI_ERROR_FLAG    (0x00000020UL)

         /* Error during SPI Abort procedure */
         #define HAL_SPI_ERROR_ABORT   (0x00000040UL)

         /* Underrun error */
         #define HAL_SPI_ERROR_UDR     (0x00000080UL)

         /* Timeout error */
         #define HAL_SPI_ERROR_TIMEOUT (0x00000100UL)

         /* Unknown error */
         #define HAL_SPI_ERROR_UNKNOW  (0x00000200UL)

         /* Requested operation not supported */
         #define HAL_SPI_ERROR_NOT_SUPPORTED    (0x00000400UL)

         #if (USE_HAL_SPI_REGISTER_CALLBACKS == 1UL)
         /* Invalid Callback error */
         #define HAL_SPI_ERROR_INVALID_CALLBACK (0x00000800UL)
         #endif /* USE_HAL_SPI_REGISTER_CALLBACKS */

         typedef struct __SPI_HandleTypeDef
         {
           SPI_TypeDef                *Instance;


           __IO uint32_t              ErrorCode;
         } SPI_HandleTypeDef;



         uint32_t HAL_SPI_GetError(SPI_HandleTypeDef *hspi);


     - .. code-block:: c

         #if (USE_HAL_SPI_GET_LAST_ERRORS == 1)
         /* No error */
         #define HAL_SPI_ERROR_NONE      (0UL)

         /* Mode fault error */
         #define HAL_SPI_ERROR_MODF      (0x01UL << 0U)

         /* CRC error */
         #define HAL_SPI_ERROR_CRC       (0x01UL << 1U)

         /* Overrun error */
         #define HAL_SPI_ERROR_OVR       (0x01UL << 2U)

         /* Frame format error */
         #define HAL_SPI_ERROR_FRE       (0x01UL << 3U)

         /* DMA transfer error */
         #define HAL_SPI_ERROR_DMA       (0x01UL << 4U)

         /* Error during SPI Abort procedure */
         #define HAL_SPI_ERROR_ABORT     (0x01UL << 5U)

         /* Underrun error */
         #define HAL_SPI_ERROR_UDR       (0x01UL << 6U)

         /* Locked IO error */
         #define HAL_SPI_ERROR_IO_LOCKED (0x01UL << 7U)
         #endif /* USE_HAL_SPI_GET_LAST_ERRORS */











         typedef struct hal_spi_handle_s hal_spi_handle_t;

         struct hal_spi_handle_s
         {
           hal_spi_t                  instance;

           #if (USE_HAL_SPI_GET_LAST_ERRORS == 1)
           volatile uint32_t          last_error_codes;
           #endif /* USE_HAL_SPI_GET_LAST_ERRORS */
         };

         #if (USE_HAL_SPI_GET_LAST_ERRORS == 1)
         uint32_t HAL_SPI_GetLastErrorsCodes(const hal_spi_handle_t *hspi);
         #endif /* USE_HAL_SPI_GET_LAST_ERRORS */

   * - .. code-block:: c

         /* No error */
         #define HAL_UART_ERROR_NONE  (0x00000000U)

         /* Parity error */
         #define HAL_UART_ERROR_PE    (0x00000001U)

         /* Noise error */
         #define HAL_UART_ERROR_NE    (0x00000002U)

         /* Frame error */
         #define HAL_UART_ERROR_FE    (0x00000004U)

         /* Overrun error */
         #define HAL_UART_ERROR_ORE   (0x00000008U)

         /* DMA transfer error */
         #define HAL_UART_ERROR_DMA   (0x00000010U)

         /* Receiver Timeout error */
         #define HAL_UART_ERROR_RTO   (0x00000020U)

         #if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
         /* Invalid Callback error */
         #define HAL_UART_ERROR_INVALID_CALLBACK (0x00000040U)
         #endif /* USE_HAL_UART_REGISTER_CALLBACKS */









         typedef struct __UART_HandleTypeDef
         {
           USART_TypeDef            *Instance;


           __IO uint32_t            ErrorCode;
         } UART_HandleTypeDef;






         uint32_t HAL_UART_GetError(UART_HandleTypeDef *huart);

     - .. code-block:: c

         #if (USE_HAL_UART_GET_LAST_ERRORS == 1)
         /*! No error on RX */
         #define HAL_UART_RECEIVE_ERROR_NONE     (0UL)

         /*! Parity error on RX */
         #define HAL_UART_RECEIVE_ERROR_PE   (0x1UL << 0)

         /*! Noise error on RX */
         #define HAL_UART_RECEIVE_ERROR_NE   (0x1UL << 1U)

         /*! Frame error on RX */
         #define HAL_UART_RECEIVE_ERROR_FE   (0x1UL << 2U)

         /*! Overrun error on RX */
         #define HAL_UART_RECEIVE_ERROR_ORE  (0x1UL << 3U)

         #if defined (USE_HAL_UART_DMA) && (USE_HAL_UART_DMA == 1U)
         /*! DMA transfer error on RX */
         #define HAL_UART_RECEIVE_ERROR_DMA   (0x1UL << 4U)
         #endif /* USE_HAL_UART_DMA */

         /*! Receiver Timeout error on RX */
         #define HAL_UART_RECEIVE_ERROR_RTO   (0x1UL << 5U)

         /*! No error on TX */
         #define HAL_UART_TRANSMIT_ERROR_NONE (0UL << 16U)

         /*! DMA transfer error on TX */
         #define HAL_UART_TRANSMIT_ERROR_DMA  (0x1UL << 17U)
         #endif /* USE_HAL_UART_GET_LAST_ERRORS */


         typedef struct hal_uart_handle_s hal_uart_handle_t;

         struct hal_uart_handle_s
         {
           hal_uart_t instance;

           #if (USE_HAL_UART_GET_LAST_ERRORS == 1)
           /*! Last error codes on reception side */
           volatile uint32_t last_reception_error_codes;
           /*! Last error codes on transmission side */
           volatile uint32_t last_transmission_error_codes;
           #endif /* USE_HAL_UART_GET_LAST_ERRORS */
         };

         #if (USE_HAL_UART_GET_LAST_ERRORS == 1)  
         uint32_t HAL_UART_GetLastErrorCodes(const hal_uart_handle_t *huart);
         #endif /* USE_HAL_UART_GET_LAST_ERRORS */

