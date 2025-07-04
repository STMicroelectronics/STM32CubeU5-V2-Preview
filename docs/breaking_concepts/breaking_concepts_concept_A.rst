
Optimized init and config APIs
******************************

The concept
=============================

HAL1 Initialization and Configuration Principles
------------------------------------------------

In HAL1, the `HAL_PPP_Init` function is provided to:

- Link the logical handle object to a physical PPP instance, storing this instance in the handle object.
- Initialize the internal fields of the PPP handle logical object.
- Configure the peripheral according to the user parameters provided by a `PPP_InitTypeDef` structure, storing the PPP configuration in the handle object.

HAL1 User Responsibilities Before Calling `HAL_PPP_Init`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- **Set the Peripheral Physical Instance:** The user must access the handle to set the peripheral physical instance.
- **Set the Peripheral Parameters:** The user must also set the peripheral parameters.

**Important:** Users should not access other handle fields as they are managed internally by the HAL PPP.

HAL1 Msp callbacks: Sequence and Resource Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The sequence requires the user to enable the peripheral clock, select the clock source, and configure various resources needed by the peripheral (e.g., GPIOs, NVIC line, DMA). This is ensured by the `HAL_PPP_MspInit` callback. Similarly, the `HAL_PPP_MspDeInit` callback allows the user to release these resources during the `HAL_PPP_DeInit` sequence.

HAL1 Limitation
~~~~~~~~~~~~~~~

- **Ambiguity:** There is ambiguity between the PPP handle public fields that need to be set by the user.
- **Extra RAM Footprint:** The HAL PPP handle holds the full peripheral configuration/init parameters, leading to extra RAM usage.
- **Complexity:** The usage of Msp callbacks is not straightforward, as the user must know and implement the Msp callbacks. There is ambiguity in using the `HAL_PPP_MspInit` callback during initialization, and users may forget to implement or update the Msp callback function.

HAL2 Initialization and Configuration Principles
-------------------------------------------------

In HAL2, users do not need to access handle parameters directly as all HAL handle fields are private.

HAL2 `HAL_PPP_Init`
~~~~~~~~~~~~~~~~~~~~

The purpose of the `HAL_PPP_Init` API is to link the logical object (handle) to the physical peripheral instance and initialize the internal fields of the PPP handle logical object. The PPP instance is given as a parameter to the `HAL_PPP_Init` function, so users do not access the HAL PPP handle object directly.

HAL2 `HAL_PPP_SetConfig`
~~~~~~~~~~~~~~~~~~~~~~~~~

A new `HAL_PPP_SetConfig` API is provided to configure the peripherals according to user parameters. The PPP configuration is provided by a dedicated configuration structure passed by reference to the `HAL_PPP_SetConfig` function. The user PPP configuration parameters are applied to the register and not stored in the handle, reducing RAM footprint.

HAL2 Configuration Levels
~~~~~~~~~~~~~~~~~~~~~~~~~

The HAL configuration APIs provide two levels of settings:

- **Global:** Apply a set of peripheral parameters to start any process. For peripherals with different sub-blocks or sub-instances (e.g., TIM IC, OC), dedicated sub-block/sub-instance configuration APIs should be used in addition to the global config to start a process (e.g., `HAL_TIM_SetConfig` + `HAL_TIM_OC_SetConfigChannel`).
- **Unitary:** Apply a single parameter.

HAL2 Msp callbacks removed:Simplified Sequence
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As the sequence has been split into two functions with clear scopes (handle object initialization and peripheral configuration):

- The `HAL_PPP_MspInit` and `HAL_PPP_MspDeInit` APIs are no longer provided.
- Users simply insert the PPP resources settings (clock, GPIO, NVIC, DMA) between the calls to `HAL_PPP_Init` and `HAL_PPP_SetConfig` with the applicative code.

____

.. _breaking_concepts_concept_A1:

Split legacy HAL_PPP_Init into Init (build handle object) and config (apply configuration)
============================================================================================

.. list-table:: Comparative Table for HAL1 and HAL2
   :header-rows: 1
   :widths: 20 40 40

   * - Function
     - HAL1
     - HAL2
   * - **HAL_PPP_Init**
     - **Scope:** Initialize the specified HAL PPP handle object and the PPP peripheral according to parameters specified in `PPP_InitTypeDef`. **Prototype:** `HAL_StatusTypeDef HAL_PPP_Init(PPP_HandleTypeDef* hppp)`
     - **Scope:** Initialize the specified HAL PPP handle object and link it to the specified peripheral instance. **Prototype:** `hal_status_t HAL_PPP_Init(hal_ppp_handle_t *hppp, hal_ppp_t instance)`
   * - **HAL_PPP_SetConfig**
     - **N/A**
     - **Scope:** Configure the PPP peripheral according to parameters specified in `hal_ppp_config_t` given as parameter by reference. **Prototype:** `hal_status_t HAL_PPP_SetConfig(hal_ppp_handle_t *hppp, const hal_ppp_config_t *p_config)`
   * - **HAL_PPP_DeInit**
     - **Scope:** De-initialize the specified HAL PPP handle object and peripheral according to the configuration parameters defined in the peripheral's handle structure. **Prototype:** `HAL_StatusTypeDef HAL_PPP_DeInit(PPP_HandleTypeDef* hppp)`
     - **Scope:** Force stopping any ongoing operation(s) and restore the handle object to default/reset state. **Prototype:** `void HAL_PPP_DeInit(hal_ppp_handle_t *hppp)`
   * - **Usage**
     - .. code-block:: c

          /* Declare a HAL PPP handle */
          PPP_HandleTypeDef hppp;

          /* Instance selection */
          hppp.Instance = PPPi;

          /* Fill PPP init struct */
          hppp.Init.param1 = VALUE;
          hppp.Init.paramN = VALUE;

          /* PPP Init and config */
          HAL_PPP_Init(&hppp);



          /* De-initialize the PPP peripheral */
          HAL_PPP_DeInit(&hppp);
     - .. code-block:: c

          /* Declare a HAL PPP handle */
          hal_ppp_handle_t hppp;

          /* Fill PPP Config struct */
          ppp_config_t ppp_config;

          ppp_config.param1 = VALUE;
          ppp_config.paramN = VALUE;

          /* Init */
          HAL_PPP_Init(&hppp, PPPi);

          /* Config */
          HAL_PPP_SetConfig(&hppp, &ppp_config);

          /* De-initialize the PPP peripheral */
          HAL_PPP_DeInit(&hppp);

____

.. _breaking_concepts_concept_A2:

Remove Init structure from handle and convert Init structure into configuration one
=====================================================================================

In HAL2, the initialization structure is no longer stored within the HAL PPP handle. 
The PPP_InitTypeDef structure has been renamed to hal_ppp_config_t and is now provided as a parameter (by reference) to the HAL_PPP_SetConfig and HAL_PPP_GetConfig APIs.
Within the configuration structure, only the mandatory fields required to start using the peripheral are retained. The optional parameters from the former PPP_InitTypeDef are now accessible through dedicated Set/Get configuration functions.


.. list-table:: Comparative Table for HAL1 and HAL2 APIs
   :header-rows: 1
   :widths: 50 50

   * - HAL1
     - HAL2
   * - .. code-block:: c

          typedef struct
          {
            uint32_t Timing;
            uint32_t OwnAddress1;
            uint32_t AddressingMode;
            uint32_t DualAddressMode;
            uint32_t OwnAddress2;
            uint32_t OwnAddress2Masks;
            uint32_t GeneralCallMode;
            uint32_t NoStretchMode;
          } I2C_InitTypeDef;

          /* I2C handle structure type */
          typedef struct __I2C_HandleTypeDef
          {
            I2C_TypeDef *Instance;
            I2C_InitTypeDef Init;
            ...
          } I2C_HandleTypeDef;

          
          /* Initialization and configuration API */
          HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c);

     - .. code-block:: c

          typedef struct
          {
            uint32_t timing;
            uint32_t own_address1;
            hal_i2c_addressing_mode_t addressing_mode;
          } hal_i2c_config_t;

          
          
          
          
          
          /* I2C handle structure type */
          typedef struct hal_i2c_handle_s hal_i2c_handle_t;
          
          struct hal_i2c_handle_s
          {
            hal_i2c_t                   instance;
            ...
          };

          /* Initialization API */
          hal_status_t HAL_I2C_Init(hal_i2c_handle_t *hi2c, 
                                    hal_i2c_t instance);
          
          /* Configuration API */
          hal_status_t HAL_I2C_SetConfig(hal_i2c_handle_t *hi2c, 
                                         const hal_i2c_config_t *p_config);

          /* Optional APIs: OwnAddress 2 */
          hal_status_t HAL_I2C_SetConfigOwnAddress2(hal_i2c_handle_t *hi2c,
                                                    uint32_t addr, 
                                                    hal_i2c_own_addr2_mask_t mask);

          hal_status_t HAL_I2C_EnableOwnAddress2(hal_i2c_handle_t *hi2c);
          hal_status_t HAL_I2C_DisableOwnAddress2(hal_i2c_handle_t *hi2c);

          /* Optional APIs: Acknowledge General Call */
          hal_status_t HAL_I2C_SLAVE_EnableAckGeneralCall(hal_i2c_handle_t *hi2c);
          hal_status_t HAL_I2C_SLAVE_DisableAckGeneralCall(hal_i2c_handle_t *hi2c);

          /* Optional APIs: Clock Stretching */
          hal_status_t HAL_I2C_SLAVE_EnableClockStretching(hal_i2c_handle_t *hi2c);
          hal_status_t HAL_I2C_SLAVE_DisableClockStretching(hal_i2c_handle_t *hi2c);

____

.. _breaking_concepts_concept_A3:

Rename handle structure
=======================

In HAL2, the HAL PPP handle structure has been renamed from PPP_HandleTypeDef to hal_ppp_handle_t.

.. list-table:: Comparative Table for HAL1 and HAL2
   :header-rows: 1
   :widths: 50 50

   * - HAL1
     - HAL2
   * - .. code-block:: c

          /* I2C handle structure type */
          typedef struct __I2C_HandleTypeDef
          {
            I2C_TypeDef *Instance;
            I2C_InitTypeDef Init;
            ...
          } I2C_HandleTypeDef;
     - .. code-block:: c

          /* I2C handle structure type */
          typedef struct hal_i2c_handle_s hal_i2c_handle_t;
          
          struct hal_i2c_handle_s
          {
            hal_i2c_t instance;
            ...
          };

____

.. _breaking_concepts_concept_A4:

Rename unitary init structures
===============================

This item covers any initialization structure used to configure a dedicated feature, sub-block, or sub-instance. 
The term "InitTypeDef" is no longer used in HAL2. Instead, a configuration structure is named "xxx_config_t".

____

.. _breaking_concepts_concept_A5:

Remove MspInit and MspDeInit callbacks
=======================================

Within HAL1 drivers, the MspInit/DeInit callbacks are used to intercept the initialization and de-initialization sequence (within HAL_PPP_Init/HAL_PPP_DeInit) and insert the PPP resource settings (clock, GPIO, NVIC, DMA, and RCC force/release reset for the DeInit). 
The usage of the MspInit/MspDenit callbacks is not straightforward, as the user must know a priori the usage of these callbacks and implement them accordingly.

In HAL2, the HAL_PPP_Init function is split into HAL_PPP_Init and HAL_PPP_SetConfig, thus no longer requiring the interception of the initialization sequence using a specific MspInit callback.

Removing the MspInit/DeInit callbacks also saves footprint within the HAL PPP handle, as there is no longer a need to store these callback pointers within the handle, especially since these callbacks are only used during the initialization sequence.

Example: HAL I2C Full initialization and configuration  
======================================================

.. _breaking_concepts_concept_examples_A:

.. list-table:: Comparative Table for HAL1 and HAL2
   :header-rows: 1
   :widths: 33 33 33

   * - File
     - HAL1
     - HAL2
   * - stm32c5xx_hal_msp.c
     - .. code-block:: c

          void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
          {
            GPIO_InitTypeDef GPIO_InitStruct = {0};
            RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

            /* I2C1 GPIOs Init */
            __HAL_RCC_GPIOB_CLK_ENABLE();

            GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
            GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
            GPIO_InitStruct.Pull = GPIO_PULLUP;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
            GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
            HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

            /* Set the I2C1 clock source */
            PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
            PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
            HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

            /* I2C1 clock enable */
            __HAL_RCC_I2C1_CLK_ENABLE();

            /* I2C1 interrupts Init */
            HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
            HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
            HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 0);
            HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
          }

          void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
          {
            /* I2C1 clock disable */
            __HAL_RCC_I2C1_CLK_DISABLE();

            /* I2C1 GPIOs DeInit */
            HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8);
            HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);

            /* I2C1 interrupt DeInit */
            HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
            HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
          }

     - .. code-block:: c

          /* No Msp Callback in HAL2 more */

   * - main.c (or applicative file)
     - .. code-block:: c

          /* HAL I2C handle */
          I2C_HandleTypeDef hi2c;

          /* I2C instance selection */
          hi2c.Instance = I2C1;

          /* Fill I2C init struct */
          hi2c.Init.Timing = 0x00C01F67;
          hi2c.Init.OwnAddress1 = I2C_ADDRESS;
          hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_10BIT;
          hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
          hi2c.Init.OwnAddress2 = 0;
          hi2c.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
          hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
          hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

          /* Init */
          HAL_I2C_Init(&hi2c);



































          /* De-initialize the I2C peripheral */
          HAL_I2C_DeInit(&hi2c);

     - .. code-block:: c

          /* HAL I2C handle */
          hal_i2c_handle_t hi2c;

          
          
          
          /* Fill I2C Config struct */
          hal_i2c_config_t i2c_config;

          i2c_config.timing = 0x00C01F67;
          i2c_config.own_address1 = I2C_ADDRESS;
          i2c_config.addressing_mode = HAL_I2C_ADDRESSING_10BIT;




          /* Init */
          HAL_I2C_Init(&hi2c, HAL_I2C1);

          /* MspInit equivalent sequence */

          /* Set the I2C1 clock source */
          HAL_RCC_I2C1_SetPeriphClockSource(HAL_RCC_I2C1_CLK_SOURCE_PCLK1);

          /* I2C1 GPIOs Init */
          HAL_RCC_GPIOB_EnableClock();

          hal_gpio_config_t gpio_config;
          gpio_config.mode = HAL_GPIO_MODE_ALTERNATE;
          gpio_config.output_type = HAL_GPIO_OUTPUT_OPENDRAIN;
          gpio_config.pull = HAL_GPIO_PULL_UP;
          gpio_config.speed = HAL_GPIO_SPEED_FREQ_LOW;
          gpio_config.alternate = HAL_GPIO_AF4_I2C1;

          HAL_GPIO_Init(HAL_GPIOB, HAL_GPIO_PIN_8 | HAL_GPIO_PIN_9, &gpio_config);

          /* I2C1 clock enable */
          HAL_RCC_I2C1_EnableClock();

          /* I2C1 interrupts Init */
          HAL_CORTEX_NVIC_SetPriority(I2C1_EV_IRQn, 
                                      HAL_CORTEX_NVIC_PREEMP_PRIORITY_1,
                                      HAL_CORTEX_NVIC_SUB_PRIORITY_0);
          HAL_CORTEX_NVIC_EnableIRQ(I2C1_EV_IRQn);

          HAL_CORTEX_NVIC_SetPriority(I2C1_ER_IRQn, 
                                     HAL_CORTEX_NVIC_PREEMP_PRIORITY_1, 
                                     HAL_CORTEX_NVIC_SUB_PRIORITY_0);
          HAL_CORTEX_NVIC_EnableIRQ(I2C1_ER_IRQn);

          /* Config */
          HAL_I2C_SetConfig(&hi2c, &i2c_config);

          /* De-initialize the I2C1 */
          HAL_I2C_DeInit(&hi2c);

