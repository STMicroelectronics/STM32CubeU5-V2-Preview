
Misc. updates
*************


.. _breaking_concepts_concept_P1:

Move the "UNUSED" macro into the CMSIS common device file.
==========================================================

In HAL1, the macro ``UNUSED`` is provided within the ``stm32u5xx_hal_def.h``.
In HAL2, this macro is renamed to ``STM32_UNUSED`` and moved to the ``stm32u5xx.h`` device header file provided by the DFP.

See also :ref:`breaking_concepts_concept_L10`.

____

.. _breaking_concepts_concept_P3:

Add HAL_GPIO_WriteMultipleStatePin, allowing setting and clearing several pins of a dedicated port with a single register access.
==================================================================================================================================

In HAL2, a HAL GPIO API is provided that allows setting and clearing multiple pins of a dedicated port in the same register WRITE cycle.
Note that in HAL1, this API is not fully deployed for all STM32 series. In HAL2, the API is fully deployed for all STM32 series.

.. list-table:: HAL1 vs HAL2
   :header-rows: 1

   * - HAL Version
     - Code
   * - HAL1
     - .. code-block:: c

        /**
         * @brief  Set and clear several pins of a dedicated port in the same cycle.
         * @note   This function uses GPIOx_BSRR and GPIOx_BRR registers to allow atomic read/modify
         *         accesses.
         * @param  GPIOx or LPGPIOx: where x can be (A..I) for the GPIO and (1) for LPGPIO to select the 
         *         corresponding peripheral for the STM32U5 family.
         * @param  PinReset specifies the port bits to be reset.
         *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15) or zero.
         * @param  PinSet specifies the port bits to be set.
         *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15) or zero.
         * @note   Both PinReset and PinSet combinations shall not share any common bit, otherwise
         *         an assert would be triggered.
         * @note   At least one of the two parameters used to set or reset must be different from zero.
         * @retval None
         */
        void HAL_GPIO_WriteMultipleStatePin(GPIO_TypeDef *GPIOx, uint16_t PinReset, uint16_t PinSet);
   * - HAL2
     - .. code-block:: c

        /**
         * @brief    Set and clear a pin or a set of pins of a GPIO port in the same cycle.
         * @note     This function uses the GPIOx_BSRR register to set the level of several pins
         *           and reset the level of several other pins in the same cycle.
         * @param    gpiox HAL_GPIOx or HAL_LPGPIOx: selected GPIO or LPGPIO based on @ref hal_gpio_t.
         * @param    pins_reset specifies the port bits to be reset.
         *           This parameter can be any combination of HAL_GPIO_Pin_x where x can be (0..15) or zero.
         * @param    pins_set specifies the port bits to be set.
         *           This parameter can be any combination of HAL_GPIO_Pin_x where x can be (0..15) or zero.
         * @warning  Both pins_reset and pins_set combinations must not share any common bit, otherwise
         *           an assert would be triggered.
         * @note     At least one of the two parameters used to set or reset must be different from zero.
         */
        void HAL_GPIO_WriteMultipleStatePin(hal_gpio_t gpiox, uint32_t pins_reset, uint32_t pins_set);

See also :ref:`hal_gpio_exported_functions_io_operation`

____

.. _breaking_concepts_concept_P4:

Update the GPIO init structure and function to move Pins as a standalone parameter of the function.
===================================================================================================

In HAL1, within the HAL_GPIO_Init function, the pin(s) selection is done through a dedicated field of the ``GPIO_InitTypeDef`` structure.
In HAL2, the pin(s) selection is done through a dedicated parameter passed to the ``HAL_GPIO_Init`` function and not as a field in the equivalent ``hal_gpio_config_t`` structure.

This allows the configuration choices to be independent of the selected pins, making it possible to reuse the same configuration structure for different ports and pins.

.. list-table:: HAL1 vs HAL2
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

        typedef struct
        {
          uint32_t Pin;
          uint32_t Mode;
          uint32_t Pull;
          uint32_t Speed;
          uint32_t Alternate;
        } GPIO_InitTypeDef;


        void HAL_GPIO_Init(GPIO_TypeDef *GPIOx,
                           const GPIO_InitTypeDef *pGPIO_Init);
     - .. code-block:: c

        typedef struct
        {
          hal_gpio_mode_t       mode;       
          hal_gpio_pull_t       pull;       
          hal_gpio_speed_freq_t speed;      
          hal_gpio_output_t     output_type;
          hal_gpio_af_t         alternate;  
          hal_gpio_pin_state_t  init_state; 
        } hal_gpio_config_t;

        hal_status_t HAL_GPIO_Init(hal_gpio_t gpiox,
                                   uint32_t pins,
                                   const hal_gpio_config_t *p_config);

See also :ref:`hal_gpio_exported_functions_io_operation`

____

.. _breaking_concepts_concept_P5:

Remove EXTI Intrinsic Management in System HAL Drivers; Let Users Rely on EXTI HAL Driver.
===========================================================================================

In HAL2, for system HAL drivers such as GPIO, PWR, RCC, RTC, and TAMP, the EXTI management is removed.
Users should rely on the dedicated HAL EXTI to configure and enable the required EXTI lines if needed.

In HAL1, the EXTI management is duplicated in both the given HAL system driver and the HAL EXTI.

This change allows for the following improvements:

- Makes the system HAL driver more consistent with the hardware implementation.

- Reduces the footprint of the system drivers when the EXTI line is not required.

- Improves the HAL driver quality and reduces maintenance effort by removing the EXTI management duplication.
    
See also ``Configure EXTI line to specific GPIO pin use case`` in :ref:`hal_gpio_use_cases`
 
____

.. _breaking_concepts_concept_P6:

Split Peripheral Configuration from Start in System HAL Drivers.
=================================================================

The main purpose of this change is to split the configuration phase from the start/enable phase in system peripherals. This change applies to system peripherals such as ICACHE, DCACHE, RTC, EXTI, IWDG, WWDG, PWR, and RAMCFG.

Concretely, the ``HAL_PPP_SetConfig`` or ``HAL_PPP_SetConfigFeature`` functions shall configure the peripheral or the feature only, without starting it. An additional API ``HAL_PPP_Start`` or ``HAL_PPP_Enable`` is provided to allow starting or enabling the operation.

Examples:

.. list-table:: HAL1 vs HAL2
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

        HAL_StatusTypeDef HAL_IWDG_Init(IWDG_HandleTypeDef *hiwdg);






        HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer(RTC_HandleTypeDef *hrtc,
                                                   uint32_t WakeUpCounter,
                                                   uint32_t WakeUpClock);
        HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer_IT(RTC_HandleTypeDef *hrtc,
                                                      uint32_t WakeUpCounter,
                                                      uint32_t WakeUpClock,
                                                      uint32_t WakeUpAutoClr);


        HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, 
                                                 EXTI_ConfigTypeDef *pExtiConfig);
  
  
     - .. code-block:: c

        hal_status_t HAL_IWDG_Init(hal_iwdg_handle_t *hiwdg, hal_iwdg_t instance);
        hal_status_t HAL_IWDG_Start(hal_iwdg_handle_t *hiwdg,
                                    uint32_t min_time,
                                    uint32_t max_time,
                                    uint32_t early_wakeup_time);


        hal_status_t HAL_RTC_WAKEUP_SetConfig(const hal_rtc_wakeup_config_t 
                                                   *p_config_wakeup_timer);
        hal_status_t HAL_RTC_WAKEUP_Start(uint32_t interruption);






        hal_status_t HAL_EXTI_SetConfig(hal_exti_handle_t *hexti,
                                        const hal_exti_config_t *p_exti_config);
        hal_status_t HAL_EXTI_Enable(hal_exti_handle_t *hexti,
                                     hal_exti_mode_t mode);

____

.. _breaking_concepts_concept_P9:

Add HAL PPP Services for Drivers with Handle to Retrieve Corresponding Peripheral Clock Frequency.
===================================================================================================

In HAL2, new HAL PPP APIs are provided to retrieve the given PPPi peripheral clock frequency in Hz. These APIs are provided by the given HAL PPP itself, taking the HAL PPP handle as a parameter, thereby abstracting the physical instance from the user.

Note that the HAL RCC driver also provides HAL RCC APIs to retrieve the peripheral frequencies. However, these HAL RCC APIs take the physical peripheral instance as input, which makes them not necessarily portable from one series to another (as the peripheral instances might change from one series to another).

Additionally, the HAL PPP APIs (taking the HAL PPP handle as input) are built on top of the HAL RCC APIs for better consistency.

Examples:

.. list-table:: HAL RCC APIs vs HAL PPP APIs
   :header-rows: 1

   * - HAL RCC APIs
     - HAL PPP APIs
   * - .. code-block:: c

        uint32_t HAL_RCC_UART_GetKernelClkFreq(const USART_TypeDef *uartx);

        uint32_t HAL_RCC_ADC_GetKernelClkFreq(const ADC_TypeDef *adcx);

        uint32_t HAL_RCC_TIM_GetKernelClkFreq(const TIM_TypeDef *timx);
     - .. code-block:: c

        uint32_t HAL_UART_GetClockFreq(const hal_uart_handle_t *huart);

        uint32_t HAL_ADC_GetClockFreq(const hal_adc_handle_t *hadc);

        uint32_t HAL_TIM_GetClockFreq(const hal_tim_handle_t *htim);

____

.. _breaking_concepts_concept_P10:

Replace Finite Parameter Defines (Including PPP Instances) with Enum Types at HAL Levels.
=========================================================================================

In HAL1, most of the parameters provided to various functions or encapsulated into structures are given
as numerical ``uint32_t`` with a set of defines to fill them.

In HAL2, the approach is based on enumerations with clear types to specify these parameters.
Moving to enumerations has several advantages such as:

- Easier usage of the HAL and reduced risk of bugs at the application level by providing dedicated parameter types.

- Better debugging experience as the parameter choices will be shown explicitly when watching a parameter
  (not just raw numerical values as in HAL1).


.. note::
   For rapid register access, the possible enumeration values are redirected to LL defines,
   which in turn are redirected to the various register bit field masks.
   The same approach applies to the PPPi instances that are now provided as enumerations in HAL2,
   with values redirected to the CMSIS PPPi physical instances.

.. note::
   When a function or structure parameter accepts a combination of several possible values,
   it is kept as a raw numerical type, ``uint32_t``, with a set of defines allowing the user to combine them
   according to their needs. In other words, moving to enumerations concerns only parameters where a choice over a list is needed.

Examples

.. list-table:: HAL1 vs HAL2 instances
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

        /* defines in CMSIS device header file */

        /* example stm32u585xx */
        #define I2C1 I2C1_BASE  
        #define I2C2 I2C2_BASE  
        #define I2C3 I2C3_BASE  
        #define I2C4 I2C4_BASE

        /* example stm32u599xx */
        #define I2C1 I2C1_BASE  
        #define I2C2 I2C2_BASE  
        #define I2C3 I2C3_BASE  
        #define I2C4 I2C4_BASE
        #define I2C5 I2C5_BASE
        #define I2C6 I2C6_BASE  
     - .. code-block:: c

        /* new HAL enumeration with values redirected to the CMSIS defines */

        typedef enum
        {
          HAL_I2C1 = (uint32_t)I2C1,
          HAL_I2C2 = (uint32_t)I2C2,
          HAL_I2C3 = (uint32_t)I2C3,
          HAL_I2C4 = (uint32_t)I2C4,

        #if defined(I2C5)
          /* I2C5 is available on some devices only
             of this series */
          HAL_I2C5 = (uint32_t)I2C5,
        #endif /* I2C5 */

        #if defined(I2C6)
          /* I2C6 is available on some devices only
             of this series */
          HAL_I2C6 = (uint32_t)I2C6,
        #endif /* I2C6 */
        } hal_i2c_t;


.. list-table:: HAL1 vs HAL2 parameters selection
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

        /* using defines */


        #define SPI_FIRSTBIT_MSB (0x00000000UL)
        #define SPI_FIRSTBIT_LSB SPI_CFG2_LSBFRST
     - .. code-block:: c

        /* using enumeration */
        typedef enum
        {
          HAL_SPI_MSB_FIRST = LL_SPI_MSB_FIRST,
          HAL_SPI_LSB_FIRST = LL_SPI_LSB_FIRST,
        } hal_spi_first_bit_t;

____

.. _breaking_concepts_concept_P14:

Change Channel Argument to 0-Based Enumeration in Timer Channels
=================================================================

For better interfacing with the HAL TIM driver at the application or middleware level,
the HAL TIM channels are now represented as an incremental 0-based enumeration.

.. list-table:: HAL1 vs HAL2
   :header-rows: 1

   * - HAL1
     - HAL2
   * - .. code-block:: c

        /* TIM channels defines*/


        #define TIM_CHANNEL_1    0x00000000U 
        #define TIM_CHANNEL_2    0x00000004U 
        #define TIM_CHANNEL_3    0x00000008U 
        #define TIM_CHANNEL_4    0x0000000CU 
        #define TIM_CHANNEL_5    0x00000010U 
        #define TIM_CHANNEL_6    0x00000014U
     - .. code-block:: c

        /* TIM channels incremental 0-based enumeration */
        typedef enum
        {
          HAL_TIM_CHANNEL_1   = 0U,
          HAL_TIM_CHANNEL_2   = 1U,
          HAL_TIM_CHANNEL_3   = 2U,
          HAL_TIM_CHANNEL_4   = 3U,
          HAL_TIM_CHANNEL_5   = 4U,
          HAL_TIM_CHANNEL_6   = 5U,
          HAL_TIM_CHANNEL_1N  = 6U,
          HAL_TIM_CHANNEL_2N  = 7U,
          HAL_TIM_CHANNEL_3N  = 8U,
          HAL_TIM_CHANNEL_4N  = 9U,
        } hal_tim_channel_t;

See also :ref:`hal_tim_constants_apis_listing`


____

.. _breaking_concepts_concept_P15:

Move Queuing/Linked List Logical Services into a Standalone HAL Queuing Driver
===============================================================================

Some STM32 devices provide peripherals such as ``DMA`` and ``SDMMC`` that support linked lists.

In HAL1, the APIs related to logical linked list and queuing manipulation are provided by each driver,
for instance, ``HAL DMA``, ``HAL SD``, and ``HAL MCC``.

In HAL2, the APIs related to logical linked list and queuing are provided in a common new HAL driver:
``stm32tnxx_hal_q.h`` and ``stm32tnxx_hal_q.c``, where ``Q`` stands for Queue.

Please refer to the dedicated ``HAL DMA``, ``HAL SD``, and ``HAL SDMMC`` migration guide pages for full details.       

____

.. _breaking_concepts_concept_P17:

Optimize HAL PPP IRQ Handlers by Reordering Processes and Error Management Statements to Prioritize Critical Interrupts
=======================================================================================================================

In HAL2, the implementation of the various ``HAL_PPP_IRQHandler`` functions is enhanced to prioritize handling
critical interrupts first, such as critical error interrupts and receiving interrupts
(For instance to avoid receiver FIFO overflow, which can lead to data loss).

____

.. _breaking_concepts_concept_P18:

Add HAL_PPP Prefix to All HAL Peripheral APIs (Defines, Macros, Types, and Functions).
=======================================================================================

Compared to HAL1, in HAL2 all APIs (defines, types, functions) start with the module name prefix ``HAL_PPP_``.
The same applies to the LL drivers; all APIs in the ``stm32tnxx_ll_ppp.h`` start with the ``LL_PPP_`` prefix.

Example:

.. list-table:: HAL1 vs HAL2 API Prefixes
   :header-rows: 1
   :widths: 50 50

   * - HAL1
     - HAL2
   * - .. code-block:: c

         /* Defines example */
         #define TIM_BREAKINPUTSOURCE_COMP1

         /* Struct example */
         typedef struct
         {
         } I2C_InitTypeDef;

         /* Enum example */
         typedef enum
         {
         } HAL_I2C_StateTypeDef;

         /* Function example */
         HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c);
     - .. code-block:: c

         /* Defines example */
         #define HAL_TIM_BREAK_INPUT_COMP1

         /* Struct example */
         typedef struct
         {
         } hal_i2c_config_t;

         /* Enum example */
         typedef enum
         {
         } hal_i2c_state_t;

         /* Function example */
         hal_status_t HAL_I2C_Init(hal_i2c_handle_t *hi2c, hal_i2c_t instance);



