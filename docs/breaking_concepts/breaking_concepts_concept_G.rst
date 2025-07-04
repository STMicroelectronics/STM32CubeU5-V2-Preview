
Enhanced control services 
*************************

The following changes aim to reinforce HAL over LL layering regarding the HAL RCC clock enable/disable services
and to use static inline functions instead of macros. 
Additionally, we offer the user more control over the involved interrupts in asynchronous interrupt-based and DMA-based processes:

____

.. _breaking_concepts_concept_G2:

Convert the current __HAL_RCC_PPP_CLK_ENABLE and __HAL_RCC_PPP_CLK_DISABLE macros into HAL RCC inline functions.
=================================================================================================================
In HAL2, the various PPP peripherals RCC clock enable and disable macros are converted into static inline functions. 
From a user migration point of view, this change consists of a simple renaming. 

The rationale behind this change is to:

- Avoid macros that are less user-friendly for debugging.
- Reinforce the HAL over LL layering as the new static inline HAL RCC function will wrap to the corresponding LL RCC function.

Example:

.. list-table::
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

         #define __HAL_RCC_TIM1_CLK_ENABLE() ..           

         #define __HAL_RCC_TIM1_CLK_DISABLE() ..

         #define __HAL_RCC_TIM1_IS_CLK_ENABLED() ..	 
     - .. code-block:: c

         __STATIC_INLINE void HAL_RCC_TIM1_EnableClock(void)

         __STATIC_INLINE void HAL_RCC_TIM1_DisableClock(void)

         __STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM1_IsEnabledClock(void)

____

.. _breaking_concepts_concept_G3:

Provide new APIs to filter optional asynchronous process interrupts.
=====================================================================
The conventional HAL PPP asynchronous processes (interrupt-based and DMA-based) typically enable all the interrupts related to the given process.
Some of these interrupts are mandatory (e.g., Transfer Complete),
while others are informative and not mandatory for the HAL process (e.g., Half Transfer).

In HAL2, the conventional HAL PPP asynchronous process APIs are maintained with the same behavior as in HAL1 as described above.
In addition to these APIs, users are provided with additional asynchronous process APIs that allow filtering of optional interrupts.

For analog peripherals (ADC, DAC, and TIM), a **SILENT** asynchronous mode is also provided: a non-blocking mode with DMA in circular mode and without any interrupt signaling.

Examples:

**UART HAL1 to HAL2 comparative table**:

.. list-table::
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

         /*
           Conventional HAL UART Transmit API
           in interrupt based model 
         */
         HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart,
                                                const uint8_t *pData,
                                                uint16_t Size);
     - .. code-block:: c

         /*
           Conventional HAL UART Transmit API
           in interrupt based model 
         */
         hal_status_t HAL_UART_Transmit_IT(hal_uart_handle_t *huart, 
                                           const void *p_data,
                                           uint32_t size_byte);

   * - .. code-block:: c

         /* None */

     - .. code-block:: c

         /* 
           New HAL UART Transmit API 
           with interrupt filtering capability
         */
         /*! Do not activate optional interrupts
             on TX IT process */
         #define HAL_UART_OPT_TX_IT_NONE ..

         /*! Activate FIFO Empty optional interrupt */
         #define HAL_UART_OPT_TX_IT_FIFO_EMPTY ..

         /*! Activate Clear To Send optional interrupt */
         #define HAL_UART_OPT_TX_IT_CLEAR_TO_SEND ..

         /*! Activate FIFO Empty and Clear To Send optional interrupts */
         #define HAL_UART_OPT_TX_IT_DEFAULT ..

         hal_status_t HAL_UART_Transmit_IT_Opt(hal_uart_handle_t *huart,
                                               const void *p_data,
                                               uint32_t size_byte,
                                               uint32_t interrupts);
   * - .. code-block:: c

         /*
           Conventional HAL UART Transmit API
           in DMA based model 
         */
         HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart,
                                                 const uint8_t *pData,
                                                 uint16_t Size);
     - .. code-block:: c

         /*
           Conventional HAL UART Transmit API
           in DMA based model 
         */
         hal_status_t HAL_UART_Transmit_DMA(hal_uart_handle_t *huart, 
                                            const void *p_data,
                                            uint32_t size_byte);

   * - .. code-block:: c

         /* None */

     - .. code-block:: c

         /* 
           New HAL UART Transmit API in DMA based model 
           with interrupt filtering capability
         */
         /*! Do not activate optional interrupts
             on TX DMA process */
         #define HAL_UART_OPT_DMA_TX_IT_NONE ..

         /*! Activate DMA Half Transfer optional interrupt */
         #define HAL_UART_OPT_DMA_TX_IT_HT ..

         /*! Activate DMA Half Transfer optional interrupt */
         #define HAL_UART_OPT_DMA_TX_IT_DEFAULT ..

         /*! Activate Silent Mode on DMA */
         #define HAL_UART_OPT_DMA_TX_IT_SILENT ..

         hal_status_t HAL_UART_Transmit_DMA_Opt(hal_uart_handle_t *huart,
                                                const void *p_data,
                                                uint32_t size_byte,
                                                uint32_t interrupts);

**ADC HAL1 to HAL2 comparative table**:

.. list-table::
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

         /* Conventional HAL ADC regular conversion API
            in interrupt based model 
         */
         HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef *hadc);
     - .. code-block:: c

         /* Conventional HAL ADC regular conversion API
            in interrupt based model 
         */
         hal_status_t HAL_ADC_REG_StartConv_IT(hal_adc_handle_t *hadc);

   * - .. code-block:: c

         /* None */

     - .. code-block:: c

         /* New HAL ADC regular conversion API 
            with interrupt filtering capability
         */

         /* ADC optional interrupts disabled */
         #define HAL_ADC_OPT_IT_NONE ..
         
         /* ADC optional interrupt group regular 
            end of sampling phase */
         #define HAL_ADC_OPT_IT_REG_EOSMP..
         
         /* ADC optional interrupt group regular
            end of unitary conversion */
         #define HAL_ADC_OPT_IT_REG_EOC ..
         
         /* ADC optional interrupt group regular
            end of sequence conversions */
         #define HAL_ADC_OPT_IT_REG_EOS ..
         
         /* ADC optional interrupt group regular overrun */
         #define HAL_ADC_OPT_IT_REG_OVR ..
         
         /* ADC optional interrupt group injected
            end of unitary conversion */
         #define HAL_ADC_OPT_IT_INJ_EOC ..
         
         /* ADC optional interrupt group injected
            end of sequence conversions */
         #define HAL_ADC_OPT_IT_INJ_EOS ..
         
         /* ADC optional interrupt analog watchdog 1
            out of window event */
         #define HAL_ADC_OPT_IT_AWD_1 ..
         
         /* ADC optional interrupt analog watchdog 2
            out of window event */
         #define HAL_ADC_OPT_IT_AWD_2 ..
         
         /* ADC optional interrupt analog watchdog 3 out
            of window event */
         #define HAL_ADC_OPT_IT_AWD_3 ..

         hal_status_t HAL_ADC_REG_StartConv_IT_Opt(hal_adc_handle_t *hadc, uint32_t it_opt);

   * - .. code-block:: c

         /* Conventional HAL ADC regular conversion API
            in DMA based model 
         */
         HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef *hadc,
                                             const uint32_t *pData,
                                             uint32_t Length);
     - .. code-block:: c

         /* Conventional HAL ADC regular conversion API
            in DMA based model 
         */
         hal_status_t HAL_ADC_REG_StartConv_DMA(hal_adc_handle_t *hadc,
                                                const uint8_t *p_data,
                                                uint32_t size_byte);

   * - .. code-block:: c

         /* None */

     - .. code-block:: c

         /* New HAL ADC regular conversion API in DMA based model 
            with interrupt filtering capability
         */
        /* ADC optional interrupts disabled */
         #define HAL_ADC_OPT_IT_NONE ..
         
         /* ADC optional interrupt group regular 
            end of sampling phase */
         #define HAL_ADC_OPT_IT_REG_EOSMP..
         
         /* ADC optional interrupt group regular
            end of unitary conversion */
         #define HAL_ADC_OPT_IT_REG_EOC ..
         
         /* ADC optional interrupt group regular
            end of sequence conversions */
         #define HAL_ADC_OPT_IT_REG_EOS ..
         
         /* ADC optional interrupt group regular overrun */
         #define HAL_ADC_OPT_IT_REG_OVR ..
         
         /* ADC optional interrupt group injected
            end of unitary conversion */
         #define HAL_ADC_OPT_IT_INJ_EOC ..
         
         /* ADC optional interrupt group injected
            end of sequence conversions */
         #define HAL_ADC_OPT_IT_INJ_EOS ..
         
         /* ADC optional interrupt analog watchdog 1
            out of window event */
         #define HAL_ADC_OPT_IT_AWD_1 ..
         
         /* ADC optional interrupt analog watchdog 2
            out of window event */
         #define HAL_ADC_OPT_IT_AWD_2 ..
         
         /* ADC optional interrupt analog watchdog 3 out
            of window event */
         #define HAL_ADC_OPT_IT_AWD_3 ..

         /* ADC data transfer with DMA optional interruptions disabled.
            DMA default interruptions: transfer complete, transfer error.
            DMA optional interruptions: refer to literals below. */
         #define HAL_ADC_OPT_DMA_IT_NONE ..
         
         /* ADC data transfer with DMA optional interrupt buffer half transfer */
         #define HAL_ADC_OPT_DMA_IT_HT ..
         
         /* ADC data transfer with DMA optional interrupt all enabled */
         #define HAL_ADC_OPT_DMA_IT_DEFAULT ..
         
         /* ADC data transfer with all interruptions disabled (ADC and DMA interruptions) */
         #define HAL_ADC_OPT_DMA_IT_SILENT ..

         hal_status_t HAL_ADC_REG_StartConv_DMA_Opt(hal_adc_handle_t *hadc,
                                                    const uint8_t *p_data,
                                                    uint32_t size_byte,
                                                    uint32_t it_opt);