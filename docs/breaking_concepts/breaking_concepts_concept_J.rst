
Optimized input checks
**********************

by avoiding systematic params and state checks and use dbg asserts for params, pointers and states

.. _breaking_concepts_concept_J1:

Replace parameter and state checks with assertions.
====================================================

HAL1: Asserts Implementation and Usage
--------------------------------------

In HAL1, the macro ``assert_param`` is provided and used exclusively within the ``HAL_PPP_Init`` function to check the validity of the Init parameters.
A default implementation of this ``assert_param`` is provided in the template file ``stm32_assert.h`` as follows:

.. code-block:: c

   #ifdef  USE_FULL_ASSERT
   /**
     * @brief  The assert_param macro is used for function's parameters check.
     * @param  expr If expr is false, it calls assert_failed function
     *         which reports the name of the source file and the source
     *         line number of the call that failed.
     *         If expr is true, it returns no value.
     * @retval None
     */

   #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))

   /* Exported functions ------------------------------------------------------- */
   void assert_failed(uint8_t *file, uint32_t line);
 
   #else

   #define assert_param(expr) ((void)0U)

   #endif /* USE_FULL_ASSERT */

To activate the assertion, the user needs to:

- Add the compilation switch ``USE_FULL_ASSERT`` to their IDE pre-processor settings.
- Provide an implementation of the function ``assert_failed``.
- An implementation of this function is also provided within the various HAL1 examples as follows:

.. code-block:: c

   void assert_failed(uint8_t *file, uint32_t line)
   {
     /* USER CODE BEGIN 6 */
     /* User can add their own implementation to report the file name and line number,
        ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

     /* Infinite loop */
     while (1)
     {
     }
     /* USER CODE END 6 */
   }

Additionally, the state validity check when calling a HAL1 API is done at run-time.
Example:

.. code-block:: c

   HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size)
   {
   ...
     /* Check that a Tx process is not already ongoing */
     if (huart->gState == HAL_UART_STATE_READY)
     {
       huart->gState = HAL_UART_STATE_BUSY_TX;  
       ..
     }
   }

HAL2: Asserts Implementation and Usage
--------------------------------------

In HAL2, all the HAL APIs check the input parameters using the ``ASSERT_DBG_PARAM`` macro (it is not limited to the Init or Config functions). 
The HAL2 APIs also check the validity of the current state for a given operation (configuration, feature setting, process, etc.) using assertions. The macro ``ASSERT_DBG_STATE`` is used for that purpose.

Example:

.. code-block:: c

   hal_status_t HAL_UART_Transmit_DMA(hal_uart_handle_t *huart, const void *p_data, uint32_t size_byte)
   {
     ASSERT_DBG_PARAM(huart != NULL);
     ASSERT_DBG_PARAM(p_data != NULL);
     ASSERT_DBG_PARAM(size_byte != 0);
     ASSERT_DBG_PARAM(huart->hdma_tx != NULL);

     ASSERT_DBG_STATE(huart->global_state, HAL_UART_STATE_CONFIGURED);
     ASSERT_DBG_STATE(huart->tx_state, HAL_UART_TX_STATE_IDLE);
     ..
   }

A default implementation of the macros ``ASSERT_DBG_PARAM`` and ``ASSERT_DBG_STATE`` is provided in the template file ``stm32_assert.h`` as follows:

.. code-block:: c

   #if defined(USE_ASSERT_DBG_PARAM)
 
   /**
     * @brief  The ASSERT_DBG_PARAM macro is used for function's parameters check.
     * @param  expr If expr is false, it calls assert_dbg_param_failed function
     *         which reports the name of the source file and the source
     *         line number of the call that failed.
     *         If expr is true, it returns no value.
     * @retval None
     */

   #define ASSERT_DBG_PARAM(expr) ((expr) ? (void)0U : assert_dbg_param_failed((uint8_t *)__FILE__, __LINE__))

   /* Exported functions ------------------------------------------------------- */
   void assert_dbg_param_failed(uint8_t *file, uint32_t line);

   #else

   #define ASSERT_DBG_PARAM(expr) ((void)0U)

   #endif /* USE_ASSERT_DBG_PARAM */


.. code-block:: c

   #if defined(USE_ASSERT_DBG_STATE)
   /**
     * @brief  The ASSERT_DBG_STATE macro is used for function's states check.
     * @param  __STATE__ the state field within the PPP handle
     * @param  __VAL__ the authorized states value(s) to be checked
     *                 can be a combination of states
     * @note   if __STATE__ & __VAL__ is zero (unauthorized state) then
     * @note   assert_dbg_state_failed function is called which reports
     *         the name of the source file and the source line number of the call that failed.
     *         if __STATE__ & __VAL__ is zero (unauthorized state) then, the ASSERT_DBG_STATE macro returns no value.
     */

   #define ASSERT_DBG_STATE(__STATE__,__VAL__) (((((uint32_t)(__STATE__)) &  ((uint32_t)(__VAL__))) != 0U) ?  \
                                                (void)0U :                                                    \
                                                assert_dbg_state_failed((uint8_t *)__FILE__, __LINE__))

   /* Exported functions ------------------------------------------------------- */
   void assert_dbg_state_failed(uint8_t *file, uint32_t line);

   #else

   #define ASSERT_DBG_STATE(__STATE__,__VAL__) ((void)0U)

   #endif /* USE_ASSERT_DBG_STATE  */

To activate the assertion, the user needs to:

- Add the compilation switch ``USE_ASSERT_DBG_PARAM`` to their IDE pre-processor settings to activate assertion on parameters.
  - In this case, provide an implementation of the function ``assert_dbg_param_failed`` as per HAL1.
- Add the compilation switch ``USE_ASSERT_DBG_STATE`` to their IDE pre-processor settings to activate assertion on states.
  - In this case, provide an implementation of the function ``assert_dbg_state_failed`` similar to ``assert_dbg_param_failed``.


Summary 
--------

.. list-table:: HAL1 vs HAL2 Asserts Implementation and Usage
   :header-rows: 1

   * - **Aspect**
     - **HAL1**
     - **HAL2**
   * - **Macro for Parameter Check**
     - ``assert_param``
     - ``ASSERT_DBG_PARAM``
   * - **Macro for State Check**
     - Not available
     - ``ASSERT_DBG_STATE``
   * - **Scope of Parameter Check**
     - Used exclusively within ``HAL_PPP_Init`` functions
     - Used in all HAL APIs
   * - **Scope of State Check**
     - State validity checks done at run-time within specific functions
     - State validity checks are performed using ASSERT_DBG_STATE in all HAL APIs, except for HAL_PPP_Init and HAL_PPP_Deinit, which serve as the entry and exit points to the HAL PPP driver state machine.
   * - **Default Implementation File**
     - ``stm32_assert.h`` template
     - ``stm32_assert.h`` template
   * - **assert params macros default Implementation**
     - .. code-block:: c

           #ifdef  USE_FULL_ASSERT
           #define assert_param(expr) ((expr) ? \
           (void)0U : \
           assert_failed((uint8_t *)__FILE__, __LINE__))

           void assert_failed(uint8_t *file, uint32_t line);

           #else

           #define assert_param(expr) ((void)0U)

           #endif /* USE_FULL_ASSERT */
     - .. code-block:: c

           #if defined(USE_ASSERT_DBG_PARAM)
           #define ASSERT_DBG_PARAM(expr) ((expr) ? \
           (void)0U : \
           assert_dbg_param_failed((uint8_t *)__FILE__, __LINE__))

           void assert_dbg_param_failed(uint8_t *file, uint32_t line);

           #else

           #define ASSERT_DBG_PARAM(expr) ((void)0U)

           #endif /* USE_ASSERT_DBG_PARAM */

   * - **Assert state macros default Implementation**
     - Not available
     - .. code-block:: c

           #if defined(USE_ASSERT_DBG_STATE)
           #define ASSERT_DBG_STATE(__STATE__,__VAL__) \
           (((((uint32_t)(__STATE__)) &  ((uint32_t)(__VAL__))) != 0U) ? \
           (void)0U : 
           assert_dbg_state_failed((uint8_t *)__FILE__, __LINE__))

           void assert_dbg_state_failed(uint8_t *file, uint32_t line);

           #else

           #define ASSERT_DBG_STATE(__STATE__,__VAL__) ((void)0U)

           #endif /* USE_ASSERT_DBG_STATE */
   * - **Activation of Assertions**
     - Add ``USE_FULL_ASSERT`` to IDE pre-processor settings
     - Add ``USE_ASSERT_DBG_PARAM`` and/or ``USE_ASSERT_DBG_STATE`` to IDE pre-processor settings
   * - **Implementation of Failed Function at user application**
     - User provides ``assert_failed`` function implementation
     - User provides ``assert_dbg_param_failed`` and/or ``assert_dbg_state_failed`` function implementation
   * - **Example of Checks inside the HAL**
     - .. code-block:: c

           HAL_StatusTypeDef HAL_UART_Transmit_DMA(
                               UART_HandleTypeDef *huart,
                               const uint8_t *pData,
                               uint16_t Size) 
           {
             if (huart->gState == HAL_UART_STATE_READY)
             {
               huart->gState = HAL_UART_STATE_BUSY_TX;
               ..
             }
           }
     - .. code-block:: c

           hal_status_t HAL_UART_Transmit_DMA(
                              hal_uart_handle_t *huart,
                              const void *p_data,
                              uint32_t size_byte) {
             ASSERT_DBG_PARAM(huart != NULL);
             ASSERT_DBG_PARAM(p_data != NULL);
             ASSERT_DBG_PARAM(size_byte != 0);
             ASSERT_DBG_PARAM(huart->hdma_tx != NULL);

             ASSERT_DBG_STATE(huart->global_state, HAL_UART_STATE_CONFIGURED);
             ASSERT_DBG_STATE(huart->tx_state, HAL_UART_TX_STATE_IDLE);
             ..
           }

