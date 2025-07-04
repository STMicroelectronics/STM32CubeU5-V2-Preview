
Atomic configuration methods
****************************

The concept
============

In HAL2, several key updates have been introduced to improve flexibility and efficiency.

- Unitary configuration APIs now allow configuring or retrieving a single item for a peripheral, such as setting the UART baud rate, without reapplying the entire configuration.
- The generic ``__HAL_LINKDMA`` macro has been replaced with dedicated DMA link APIs, providing clearer and more maintainable code.
- New APIs for setting and getting user data within HAL handles enable applications to store and retrieve application-specific data flexibly.
- Additionally, the callback registration mechanism has been optimized by splitting the global register callback API into individual APIs for each callback, eliminating the "UnRegister" callback API and reducing overhead.

These enhancements collectively improve the usability and performance of the HAL2 library.

____

.. _breaking_concepts_concept_B1:

Add unitary configuration APIs
------------------------------

In HAL 2, unitary configuration APIs allow configuring or retrieving a single item for a given peripheral, such as setting the UART baud rate.
Depending on the peripheral, the unitary item can be applicable to the entire PPP instance, a specific PPP instance sub-block (e.g., a TIM Output Compare sub-block), or a PPP sub-instance (e.g., a TIM channel).
These APIs are intended to dynamically modify or retrieve a unitary item, meaning that a global or sub-block configuration has already been applied.

These functions allow modification of a single configuration item without the need to call the full configuration function again.
For some HAL drivers (e.g., HAL I2C), these are new services. For other HAL drivers (e.g., HAL TIM), these unitary APIs replace macros or functions previously used to dynamically modify a single item.

**TIM Example**

.. list-table:: Comparative Table for HAL1 and HAL2 TIM period
   :header-rows: 1
   :widths: 50 50

   * - HAL1
     - HAL2
   * - .. code-block:: c

          TIM_HandleTypeDef htim;

          /* Change the TIM Period */
          __HAL_TIM_SET_AUTORELOAD(&htim, new_tim_period);

          /* Change the TIM channel source */
          HAL_TIMEx_TISelection(&htim,
                                TIM_TIM2_TI1_COMP2,
                                TIM_CHANNEL_1);

     - .. code-block:: c

          hal_tim_handle_t htim;

          /* Change the TIM Period */
          HAL_TIM_SetPeriod(&htim, new_tim_period);

          /* Change the TIM channel source */
          HAL_TIM_IC_SetChannelSource(&htim,
                                      HAL_TIM_CHANNEL_1,
                                      HAL_TIM_INPUT_TIM2_TI2_COMP2);

**CRC Example**

.. list-table:: Comparative Table for HAL1 and HAL2 CRC Polynomial
   :header-rows: 1
   :widths: 50 50

   * - HAL1
     - HAL2
   * - .. code-block:: c

          /* X^8 + X^7 + X^4 + X^3 + X + 1 */
          #define APP_CRC_POLYNOMIAL_8B 0x9B

          CRC_HandleTypeDef hcrc;

          /* Change the CRC Polynomial */
          __HAL_CRC_POLYNOMIAL_CONFIG(&hcrc, APP_CRC_POLYNOMIAL_8B);

     - .. code-block:: c

          /* X^8 + X^7 + X^4 + X^3 + X + 1 */
          #define APP_CRC_POLYNOMIAL_8B 0x9B

          hal_crc_handle_t hcrc;

          /* Change the CRC Polynomial */
          HAL_CRC_SetConfigPolynomial(&hcrc, APP_CRC_POLYNOMIAL_8B,
                                             HAL_CRC_POLY_SIZE_8B,
                                             0xFFFFFFFF);

____

.. _breaking_concepts_concept_B2:

Remove __HAL_LINKDMA generic macro and provide a dedicated API per DMA field​
-----------------------------------------------------------------------------

In HAL1, the link between a given peripheral handle and a DMA handle (within the MspInit) is ensured by the helper macro ``__HAL_LINKDMA``.

.. code-block:: c

    #define __HAL_LINKDMA(__HANDLE__, __PPP_DMA_FIELD__, __DMA_HANDLE__)             \
                        do{                                                          \
                            (__HANDLE__)->__PPP_DMA_FIELD__ = &(__DMA_HANDLE__);     \
                            (__DMA_HANDLE__).Parent = (__HANDLE__);                  \
                        } while(0)

The usage of this service macro requires the knowledge of the PPP handle internal DMA field (``__PPP_DMA_FIELD__``) that is a private field of the handle.

In HAL2, for each HAL driver that supports DMA-based processes, dedicated DMA link APIs are provided with explicit naming and parameters.

**UART Example**

.. list-table:: Comparative Table for HAL1 and HAL2 UART DMA Linking
   :header-rows: 1
   :widths: 50 50

   * - HAL1
     - HAL2
   * - .. code-block:: c

          /* Link the DMA handle to the UART handle for Rx processing */
          __HAL_LINKDMA(huart, hdmarx, hdma_gpdma1_channel1);

     - .. code-block:: c

          /* Link the DMA handle to the UART handle for Rx processing */
          HAL_UART_SetTxDMA(&huart, &hdma_gpdma1_channel1);

**TIM Example**

.. list-table:: Comparative Table for HAL1 and HAL2 TIM DMA Linking
   :header-rows: 1
   :widths: 50 50

   * - HAL1
     - HAL2
   * - .. code-block:: c

          /* Link the DMA handle to the TIM handle
             for channel3 compare capture */
          __HAL_LINKDMA(&htim, hdma[TIM_DMA_ID_CC3], &hdma_tim);

     - .. code-block:: c

          /* Link the DMA handle to the TIM handle
             for channel3 compare capture */
          HAL_TIM_SetDMA(&htim, HAL_TIM_DMA_ID_CC3, &hdma_tim);

____

.. _breaking_concepts_concept_B3:

Add HAL User Data Set/Get APIs
------------------------------

In HAL2, the HAL driver introduces a new service that allows users to associate application-specific user data with the HAL PPP handle.
This enables applications to store and retrieve a user data pointer within the handle, which can vary in type and format between different applications.
The user data pointer is defined as a void pointer, ensuring flexibility.
The HAL driver does not perform any operations or checks on this user data, except for initializing it to NULL during the HAL_PPP_Init process.
Once initialized, the pointer belongs entirely to the user, with the HAL driver simply storing and restoring it through the HAL_PPP_SetUserData and HAL_PPP_GetUserData functions.
A typical use case involves setting the user data pointer before starting a process and then retrieving it within the user process completion callback.
These services are available when the USE_HAL_PPP_USER_DATA define is set to "1" in the stm32tnxx_hal_conf configuration file.

**Example**

.. code-block:: c

    struct hal_tim_handle_s;
    typedef struct hal_tim_handle_s hal_tim_handle_t;

    struct hal_tim_handle_s
    {
      /* HAL TIM instance */
      hal_tim_t instance;
      ...
      #if defined (USE_HAL_TIM_USER_DATA) && (USE_HAL_TIM_USER_DATA == 1)
      /* User Data Pointer  */
      const void *p_user_data;
      #endif /* USE_HAL_TIM_USER_DATA */
    };

    #if defined (USE_HAL_TIM_USER_DATA) && (USE_HAL_TIM_USER_DATA == 1)
    void HAL_TIM_SetUserData(hal_tim_handle_t *htim, const void *p_user_data);
    const void *HAL_TIM_GetUserData(const hal_tim_handle_t *htim);
    #endif /* USE_HAL_TIM_USER_DATA */

____

.. _breaking_concepts_concept_B4:

Split Global Register callback API to one register API per callback and remove unregister callback API
-------------------------------------------------------------------------------------------------------


In HAL2, the callback registration mechanism has been optimized compared to HAL1 for improved efficiency and reduced footprint.
Instead of using a common register callback API that introduces overhead through a switch case, HAL2 provides individual register APIs for each callback, resulting in a more streamlined and efficient implementation.
The "UnRegister" callback API has been removed; users can simply re-register the default HAL PPP weak callbacks when needed.
Callback pointers are still stored within the HAL handle, and the compilation define USE_HAL_PPP_REGISTER_CALLBACK is still needed to activate the register callback HAL feature.
Additionally, dedicated types for callback prototypes are provided to ensure clarity and consistency.

**UART Example**

.. list-table:: Comparative Table for HAL1 and HAL2 UART Callback Registration
   :header-rows: 1
   :widths: 50 50

   * - HAL1
     - HAL2
   * - .. code-block:: c

          UART_HandleTypeDef uart_handle;

          void TxTransferCpltCallback(UART_HandleTypeDef *huart);
          void RxTransferCpltCallback(UART_HandleTypeDef *huart,
                                             uint16_t Size);

          void TransferErrorCallback(UART_HandleTypeDef *huart);

           /* Register Tx Complete Callback */
          HAL_UART_RegisterCallback(&uart_handle,
                                    HAL_UART_TX_COMPLETE_CB_ID,
                                    TxTransferCpltCallback);

          /* Register Rx Complete Callback */
          HAL_UART_RegisterCallback(&uart_handle,
                                     HAL_UART_RX_COMPLETE_CB_ID,
                                     RxTransferCpltCallback);

          /* Register Error Callback */
          HAL_UART_RegisterCallback(&uart_handle,
                                    HAL_UART_ERROR_CB_ID,
                                    TransferErrorCallback);

          /* UnRegister Tx Complete Callback */
          HAL_UART_UnRegisterCallback(&uart_handle,
                                    HAL_UART_TX_COMPLETE_CB_ID);
     - .. code-block:: c

          hal_uart_handle_t uart_handle;

          void TxTransferCpltCallback(hal_uart_handle_t *huart);
          void RxTransferCpltCallback(hal_uart_handle_t *huart,
                                             uint16_t size_byte,
                                             hal_uart_rx_event_types_t rx_event);
          void TransferErrorCallback(hal_uart_handle_t *huart);

          /* Register Tx Complete Callback */
          HAL_UART_RegisterTxCpltCallback(&uart_handle,
                                          TxTransferCpltCallback);


          /* Register Rx Complete Callback */
          HAL_UART_RegisterRxCpltCallback(&uart_handle,
                                          RxTransferCpltCallback);


          /* Register Error Callback */
          HAL_UART_RegisterErrorCallback(&uart_handle,
                                         TransferErrorCallback);


          /* UnRegister Tx Complete Callback */
          HAL_UART_RegisterTxCpltCallback(&uart_handle,
                                          HAL_UART_TxCpltCallback);

**TIM Example**

.. list-table:: Comparative Table for HAL1 and HAL2 TIM Callback Registration
   :header-rows: 1
   :widths: 50 50

   * - HAL1
     - HAL2
   * - .. code-block:: c

          hal_tim_handle_t tim_handle;

          void UpdateCallback(hal_tim_handle_t *htim);
          void InputCaptureCallback(hal_tim_handle_t *htim);


          /* Register Update Callback */
          HAL_TIM_RegisterCallback(&tim_handle,
                                   HAL_TIM_PERIOD_ELAPSED_CB_ID,
                                   UpdateCallback);

          /* Register Input Capture Callback */
          HAL_TIM_RegisterCallback(&tim_handle,
                                   HAL_TIM_IC_CAPTURE_CB_ID,
                                   InputCaptureCallback);

          /* UnRegister Update Callback */
          HAL_TIM_UnRegisterCallback(&tim_handle,
                                     HAL_TIM_PERIOD_ELAPSED_CB_ID);

     - .. code-block:: c

          hal_tim_handle_t tim_handle;

          void UpdateCallback(hal_tim_handle_t *htim);
          void InputCaptureCallback(hal_tim_handle_t *htim,
                                    hal_tim_channel_t channel);

          /* Register Update Callback */
          HAL_TIM_RegisterUpdateCallback(&tim_handle,
                                         UpdateCallback);


          /* Register Input Capture Callback */
          HAL_TIM_RegisterInputCaptureCallback(&tim_handle,
                                               InputCaptureCallback);


          /* UnRegister Update Callback */
          HAL_TIM_RegisterUpdateCallback(&tim_handle,
                                         HAL_TIM_UpdateCallback);


