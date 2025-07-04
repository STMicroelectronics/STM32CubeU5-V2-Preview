
New coding rules
****************

.. _breaking_concepts_concept_I1:

Remove single or double underscore prefixes from any define or macro, as this is not allowed per the C standard.
================================================================================================================
To comply with C coding rules, in HAL2, any single or double underscore prefixes are removed from macros.
This change ensures better adherence to coding standards and avoids potential conflicts with reserved identifiers in the C language.

Example:

.. list-table::
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

         #define __HAL_ADC_CALC_DATA_TO_VOLTAGE(..) ..
     - .. code-block:: c

         #define HAL_ADC_CALC_DATA_TO_VOLTAGE(..) ..

____

.. _breaking_concepts_concept_I2:

Replace the "TypeDef" part of every typedef with "_t".
=======================================================
In HAL1, the C language types (structures, enumerations) end with ``TypeDef``. In HAL2, types end with ``_t``.

Example:

.. list-table::
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

         typedef struct
         {
         } ADC_ChannelConfTypeDef;
     - .. code-block:: c

         typedef struct
         {
         } hal_adc_channel_config_t;

____

.. _breaking_concepts_concept_I3:

Remove underscore prefixes from header file guards and replace them with #ifndef HAL_PPP_HDR_H (use _HDR_H suffix).
====================================================================================================================
Example:

.. list-table::
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

         #ifndef __STM32U5xx_HAL_DEF
         #define __STM32U5xx_HAL_DEF
     - .. code-block:: c

         #ifndef STM32U5XX_HAL_DEF_H
         #define STM32U5XX_HAL_DEF_H

____

.. _breaking_concepts_concept_I4:

Replace big macros with inline functions for consistency.
=========================================================
In HAL1, some macros (private or public) provide an implementation over several lines with multiple instructions.
Usually, these macros are encapsulated in a ``do { ... } while(0)`` construct to avoid issues when calling or nesting the macro in an expression.

In HAL2, these macros (private or public) are transformed into static inline functions.
The rationale behind this change is to improve debugging, as macros with multiple instructions (encapsulated in ``do { ... } while(0)``)
are hard to debug compared to static inline functions.

Example:

.. list-table:: 
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

         #define __HAL_RCC_TIM1_CLK_ENABLE()            
         do { \
              __IO uint32_t tmpreg; \
              SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN); \
              /* Delay after an RCC peripheral clock enabling */ \
              tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN); \
              UNUSED(tmpreg); \
            } while(0)
     - .. code-block:: c

         __STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM1_IsEnabledClock(void)
         {
           return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM1);
         }

____


.. _breaking_concepts_concept_I5:

Replace non-modifiable pointers with const keywords.
=====================================================
In HAL2, to adhere to MISRA-C 2012 coding rules, the ``const`` keyword is applied to any function parameter passed by pointer
if the function does not modify the data pointed to by that pointer.

Example:

.. list-table::
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

         HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(I2C_HandleTypeDef *hi2c,
                                                      uint16_t DevAddress,
                                                      uint8_t *pData,
                                                      uint16_t Size);
     - .. code-block:: c

         hal_status_t HAL_I2C_MASTER_Transmit_DMA(hal_i2c_handle_t *hi2c,
                                                  uint32_t device_addr,
                                                  const void *p_data,
                                                  uint32_t size_byte);
