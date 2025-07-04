
Split clock and IRQ management
******************************

The concept
============

The goal of this item is to break down the heavy HAL1 RCC functions, such as ``HAL_RCC_OscConfig`` and ``HAL_RCC_ClockConfig``, into unitary, specialized, and highly efficient functions.

Functions like ``HAL_RCC_OscConfig``, ``HAL_RCC_ClockConfig``, and ``HAL_RCCEx_PeriphCLKConfig`` in HAL1 are monolithic:

- They take input structures representing all possible configurations.
  - For instance, ``HAL_RCCEx_PeriphCLKConfig`` takes the ``RCC_PeriphCLKInitTypeDef`` structure, which contains all peripherals with all possible source clocks.
- They implement extensive switch-case and if/else combinations to handle all possibilities within their scope.
  - For example, ``HAL_RCCEx_PeriphCLKConfig`` uses an enormous if/else sequence to list every single peripheral instance and, for each, another if/else to handle every possible source clock for that given instance.

HAL2 changes the paradigm by offering users HAL RCC APIs "à la carte" according to their needs, removing the monolithic APIs.
This allows a considerable gain in terms of footprint (more than 60% of the HAL RCC footprint is saved in HAL2 compared to HAL1 for a typical use case).

Almost the same principle applies to the ``HAL_PPP_IRQHandler`` functions that in HAL1 handle all the possible interrupts of the given PPP peripheral.
In HAL2, these ``HAL_PPP_IRQHandler`` functions are kept unchanged and, in addition, specialized HAL PPP IRQ handler functions are provided.
This allows HAL users to optimize the IRQ execution by embedding only the code relative to the interrupts they are using in the given application.
These specialized IRQ handlers are not introduced in all HAL drivers but only in the drivers where the processing and footprint gain is significant, such as the HAL TIM.

____

.. _breaking_concepts_concept_C1:

Replace HAL_RCC_OscConfig Service with Atomic Configuration APIs for Each RCC Oscillator
===========================================================================================

When transitioning from HAL1 to HAL2 for configuring the STM32 oscillators and PLL, the main changes involve a shift from using generalized structures
and single function calls to more specific and granular function calls.
In HAL1, configurations are made using structures like ``RCC_OscInitTypeDef`` and a single function call ``HAL_RCC_OscConfig`` to apply the settings.
This approach is footprint-consuming as it involves structures and functions that account for all possible oscillators and the PLL,
leading to a large if/else combination within the HAL library.

In contrast, HAL2 introduces distinct function calls for each configuration step, such as ``HAL_RCC_MSIS_Enable`` for enabling the MSI oscillator
and ``HAL_RCC_MSI_SetTrimming`` for setting its trimming. PLL configuration in HAL2 is handled using a dedicated structure ``hal_rcc_pll_config_t``
and separate function calls like ``HAL_RCC_PLL1_SetConfig``, ``HAL_RCC_PLL1_Enable``, and ``HAL_RCC_PLL1_EnableOutput``.
This approach in HAL2 provides more explicit and modular control over the oscillator and PLL settings, enhancing clarity and maintainability of the code.
Additionally, HAL2 is more efficient in terms of memory footprint, as it uses one function per single oscillator or PLL and for one specific purpose (enable/disable, configure, etc.),
thereby reducing the overhead associated with the generalized and extensive if/else structures in HAL1.

.. list-table:: Comparison of HAL1 and HAL2 (oscillators Configuration)
   :header-rows: 1

   * - **Scope**
     - **HAL1**
     - **HAL2**
   * - **Structures**
     - .. code-block:: c

           RCC_OscInitTypeDef RCC_OscInitStruct;
     - .. code-block:: c

           hal_rcc_pll_config_t config_pll1;

   * - **Oscillator Initialization**
     - .. code-block:: c

           RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
           RCC_OscInitStruct.MSIState = RCC_MSI_ON;
           RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
           RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_4;
     - .. code-block:: c

           HAL_RCC_MSIS_Enable(HAL_RCC_MSIS_FREQ_4MHZ);
           HAL_RCC_MSI_SetTrimming(HAL_RCC_MSICALIBRATION_DEFAULT, HAL_RCC_MSI_RANGE_CALIB_4_TO_7);
   * - **PLL Configuration**
     - .. code-block:: c

           RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
           RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
           RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV1;
           RCC_OscInitStruct.PLL.PLLM = 1;
           RCC_OscInitStruct.PLL.PLLN = 80;
           RCC_OscInitStruct.PLL.PLLP = 2;
           RCC_OscInitStruct.PLL.PLLQ = 2;
           RCC_OscInitStruct.PLL.PLLR = 2;
           RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_0;
           RCC_OscInitStruct.PLL.PLLFRACN = 0;
     - .. code-block:: c

           config_pll1.pll_source  = HAL_RCC_PLLSOURCE_MSIS;
           config_pll1.pll_m_boost = HAL_RCC_PLLMBOOST_DIV1;
           config_pll1.pll_m       = 1;
           config_pll1.pll_n       = 80;
           config_pll1.pll_p       = 2;
           config_pll1.pll_q       = 2;
           config_pll1.pll_r       = 2;
           config_pll1.pll_fracn   = 0;
   * - **Function Calls**
     - .. code-block:: c

           HAL_RCC_OscConfig(&RCC_OscInitStruct);
     - .. code-block:: c

           HAL_RCC_PLL1_SetConfig(&config_pll1);
           HAL_RCC_PLL1_Enable();
           HAL_RCC_PLL1_EnableOutput(HAL_RCC_PLL1_SYSCLK);

____

.. _breaking_concepts_concept_C2:

Replace HAL_RCC_ClockConfig Service with  Atomic Configuration APIs for Clock Sources
===========================================================================================
When transitioning from HAL1 to HAL2 for configuring the CPU, AHB, and APB buses clocks, the main changes involve moving from a single structure-based configuration to more granular function calls.
In HAL1, the clock configuration is done using the ``RCC_ClkInitTypeDef`` structure and a single function call ``HAL_RCC_ClockConfig``.
This method is footprint-consuming due to the inclusion of all possible clock types and dividers within a single structure.
In contrast, HAL2 uses specific function calls for each configuration step, such as ``HAL_RCC_SetSysClkSource`` for setting the system clock source
and ``HAL_RCC_SetBusClockConfig`` for configuring the bus clocks. Additionally, HAL2 provides unitary APIs to set and get individual bus prescalers,
such as ``HAL_RCC_SetPCLK1Prescaler``, ``HAL_RCC_SetPCLK2Prescaler``, ``HAL_RCC_SetPCLK3Prescaler``, and corresponding get functions.
This approach in HAL2 provides more explicit and modular control over the clock settings, enhancing clarity and maintainability of the code while reducing memory footprint.

.. list-table:: Comparison of HAL1 and HAL2 (System Clock source nad buses Configuration)
   :header-rows: 1

   * - **Scope**
     - **HAL1**
     - **HAL2**
   * - **Structures**
     - .. code-block:: c

           RCC_ClkInitTypeDef RCC_ClkInitStruct;
     - .. code-block:: c

           hal_rcc_bus_clk_divider_t config_bus;
   * - **Clock Initialization**
     - .. code-block:: c

           RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                        |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                                        |RCC_CLOCKTYPE_PCLK3;
           RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
           RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
           RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
           RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
           RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

           HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
     - .. code-block:: c

           HAL_RCC_SetSysClkSource(HAL_RCC_SYSCLKSOURCE_PLLCLK);

           config_bus.ahb_clk_divider  = HAL_RCC_HCLK_DIV1;
           config_bus.apb1_clk_divider = HAL_RCC_PCLK_DIV1;
           config_bus.apb2_clk_divider = HAL_RCC_PCLK_DIV1;
           config_bus.apb3_clk_divider = HAL_RCC_PCLK_DIV1;

           HAL_RCC_SetBusClockConfig(&config_bus);
   * - **Unitary APIs**
     - N/A
     - .. code-block:: c

           void HAL_RCC_SetPCLK1Prescaler(hal_rcc_pclk_div_t prescaler);
           void HAL_RCC_SetPCLK2Prescaler(hal_rcc_pclk_div_t prescaler);
           void HAL_RCC_SetPCLK3Prescaler(hal_rcc_pclk_div_t prescaler);

           hal_rcc_hclk_div_t HAL_RCC_GetHCLKPrescaler(void);
           hal_rcc_pclk_div_t HAL_RCC_GetPCLK1Prescaler(void);
           hal_rcc_pclk_div_t HAL_RCC_GetPCLK2Prescaler(void);
           hal_rcc_pclk_div_t HAL_RCC_GetPCLK3Prescaler(void);

____

.. _breaking_concepts_concept_C3:

Provide Unitary Configuration APIs to Manage PLLs
==================================================

When transitioning from HAL1 to HAL2 for managing PLL configurations, the main changes involve moving from macro-based and structure-based
configurations to more granular function calls.
In HAL1, the ``HAL_RCC_OscConfig`` API allows users to configure all oscillators and the main PLL parameters.
Additionally, this function forces the enabling of the PLL and its main output that is used to clock the system.
However, it does not allow enabling other PLL outputs (such as PLLP and PLLQ) directly.
Configuring these PLL outputs requires additional macro calls, making the method footprint-consuming and harder to maintain.
Furthermore, since the PLL configuration and enabling are forced inside the ``HAL_RCC_OscConfig`` API,
it is not possible for the user to customize the configuration and enabling sequence.

In contrast, HAL2 provides specific function calls for each configuration step.
For example, ``HAL_RCC_PLL1_SetConfig`` is used for setting PLL1 parameters,
and ``HAL_RCC_PLL1_EnableOutput`` is used for enabling PLL outputs.
This approach in HAL2 offers more explicit and modular control over the PLL settings, enhancing the clarity and maintainability
of the code while reducing the memory footprint.

.. list-table:: Comparison of HAL1 and HAL2 (PLL Management)
   :header-rows: 1

   * - **Scope**
     - **HAL1**
     - **HAL2**
   * - **PLL Configuration**
     - .. code-block:: c

           RCC_OscInitTypeDef RCC_OscInitStruct;

           RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
           RCC_OscInitStruct.MSIState = RCC_MSI_ON;
           RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_4;
           RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
           RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
           RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
           RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV1;
           RCC_OscInitStruct.PLL.PLLM = 1;
           RCC_OscInitStruct.PLL.PLLN = 80;
           RCC_OscInitStruct.PLL.PLLR = 2;
           RCC_OscInitStruct.PLL.PLLP = 2;
           RCC_OscInitStruct.PLL.PLLQ = 2;
           RCC_OscInitStruct.PLL.PLLFRACN = 0;
           RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_0;

           HAL_RCC_OscConfig(&RCC_OscInitStruct);
     - .. code-block:: c

           config_pll1.pll_source = HAL_RCC_PLLSOURCE_MSIS;
           config_pll1.pll_m_boost = HAL_RCC_PLLMBOOST_DIV1;
           config_pll1.pll_m = 1;
           config_pll1.pll_n = 80;
           config_pll1.pll_p = 2;
           config_pll1.pll_q = 2;
           config_pll1.pll_r = 2;
           config_pll1.pll_fracn = 0;

           HAL_RCC_PLL1_SetConfig(&config_pll1);
           HAL_RCC_PLL1_Enable();
           HAL_RCC_PLL1_EnableOutput(HAL_RCC_PLL1_SYSCLK);
   * - **PLL Services**
     - .. code-block:: c

           #define __HAL_RCC_PLL_ENABLE()
           #define __HAL_RCC_PLL_DISABLE()

           #define __HAL_RCC_PLLCLKOUT_ENABLE(..)
           #define __HAL_RCC_PLLCLKOUT_DISABLE(..)

           #define __HAL_RCC_GET_PLLCLKOUT_CONFIG(..)

           #define __HAL_RCC_PLLFRACN_ENABLE()
           #define __HAL_RCC_PLLFRACN_DISABLE()

           #define __HAL_RCC_PLL_CONFIG(..)

           #define __HAL_RCC_PLL_PLLSOURCE_CONFIG(..)

           #define __HAL_RCC_PLLFRACN_CONFIG(..)

           #define __HAL_RCC_PLL_VCIRANGE(..)

           #define __HAL_RCC_GET_PLL_OSCSOURCE()
     - .. code-block:: c

           hal_status_t HAL_RCC_PLL1_SetConfig(const hal_rcc_pll_config_t *p_config);
           hal_status_t HAL_RCC_PLL1_Enable(void);
           hal_status_t HAL_RCC_PLL1_Disable(void);
           hal_status_t HAL_RCC_PLL1_EnableOutput(uint32_t output);
           hal_status_t HAL_RCC_PLL1_DisableOutput(uint32_t output);
           hal_status_t HAL_RCC_PLL1_Reset(void);
           void HAL_RCC_PLL1_GetConfig(hal_rcc_pll_config_t *p_config);
           uint32_t HAL_RCC_PLL1_GetOutput(void);
           hal_rcc_pll_status_t HAL_RCC_PLL1_IsReady(void);
           void HAL_RCC_PLL1_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk);
           hal_status_t HAL_RCC_PLL1_SetFRACN(uint16_t fracn);
           uint16_t HAL_RCC_PLL1_GetFRACN(void);

For the auxiliary PLLs (PLLs that are used to clock peripherals) such as PLL2 and PLL3,
HAL1 provides a structure-based configuration and a function to configure and enable the PLL. In HAL1,
the ``HAL_RCCEx_EnablePLL2`` function configures all the PLL parameters, enables the PLL, and its outputs.
The same structure and enable/disable services are provided for other PLLs such as PLL3.
In HAL1, the function ``HAL_RCCEx_DisablePLL2`` fully disables the PLL and its outputs.

In addition to the global ``HAL_RCCEx_EnablePLL2`` and ``HAL_RCCEx_DisablePLL2`` functions,
several macros are provided to give more granularity to the user.
However, these macros' scope and content are redundant with parts of these functions.


In HAL2, the same services as the main PLL1 are provided for auxiliary PLLs (example PLL2),
allowing users to have the exact same sequence and approach for all the PLLs without distinguishing
between the configuration and enabling sequence of the main PLL (PLL1) and the auxiliary PLLs.
Additionally, there are no more macros in HAL2; instead, unitary functions are provided with a clear distinction between
the configuration function scope and other unitary control services such as enable/disable and enable/disable outputs.

.. list-table:: Comparison of HAL1 and HAL2 (example for PLL2 Services)
   :header-rows: 1

   * - **Scope**
     - **HAL1**
     - **HAL2**
   * - **PLL2 Configuration Structure**
     - .. code-block:: c

           typedef struct
           {
             uint32_t PLL2Source;
             uint32_t PLL2M;
             uint32_t PLL2N;
             uint32_t PLL2P;
             uint32_t PLL2Q;
             uint32_t PLL2R;
             uint32_t PLL2RGE;
             uint32_t PLL2FRACN;
             uint32_t PLL2ClockOut;
           } RCC_PLL2InitTypeDef;
     - .. code-block:: c

           typedef struct
           {
             uint16_t pll_n;
             uint16_t pll_fracn;
             uint8_t pll_m;
             uint8_t pll_p;
             uint8_t pll_q;
             uint8_t pll_r;
             hal_rcc_pll_mboost_div_t pll_m_boost;
             hal_rcc_pll_src_t pll_source;
           } hal_rcc_pll_config_t;
   * - **PLL2 Configuration Function**
     - .. code-block:: c

           HAL_StatusTypeDef HAL_RCCEx_EnablePLL2(RCC_PLL2InitTypeDef
                                                  *PLL2Init);
     - .. code-block:: c

           hal_status_t HAL_RCC_PLL2_SetConfig(const hal_rcc_pll_config_t
                                               *p_config);
   * - **PLL2 Enable/Disable Functions**
     - .. code-block:: c

           HAL_StatusTypeDef HAL_RCCEx_EnablePLL2(RCC_PLL2InitTypeDef
                                                  *PLL2Init);
           HAL_StatusTypeDef HAL_RCCEx_DisablePLL2(void);
     - .. code-block:: c

           hal_status_t HAL_RCC_PLL2_Enable(void);
           hal_status_t HAL_RCC_PLL2_Disable(void);
           hal_status_t HAL_RCC_PLL2_EnableOutput(uint32_t output);
           hal_status_t HAL_RCC_PLL2_DisableOutput(uint32_t output);
           hal_status_t HAL_RCC_PLL2_Reset(void);
           hal_rcc_pll_status_t HAL_RCC_PLL2_IsReady(void);
   * - **PLL2 Macros**
     - .. code-block:: c

           #define __HAL_RCC_PLL2_ENABLE()
           #define __HAL_RCC_PLL2_DISABLE()

           #define __HAL_RCC_PLL2CLKOUT_ENABLE(..)
           #define __HAL_RCC_PLL2CLKOUT_DISABLE(..)

           #define __HAL_RCC_PLL2_PLLSOURCE_CONFIG(..)
           #define __HAL_RCC_GET_PLL2_OSCSOURCE()

           #define __HAL_RCC_PLL2_CONFIG(..)

           #define __HAL_RCC_GET_PLL2CLKOUT_CONFIG(..)

           #define __HAL_RCC_PLL2FRACN_ENABLE()
           #define __HAL_RCC_PLL2FRACN_DISABLE()

           #define __HAL_RCC_PLL2FRACN_CONFIG(..)
     - .. code-block:: c

           hal_status_t HAL_RCC_PLL2_Enable(void);
           hal_status_t HAL_RCC_PLL2_Disable(void);

           hal_status_t HAL_RCC_PLL2_EnableOutput(uint32_t output);
           hal_status_t HAL_RCC_PLL2_DisableOutput(uint32_t output);

           hal_status_t HAL_RCC_PLL2_Reset(void);

           hal_rcc_pll_status_t HAL_RCC_PLL2_IsReady(void);

           hal_status_t HAL_RCC_PLL2_SetFRACN(uint16_t fracn);
           uint16_t HAL_RCC_PLL2_GetFRACN(void);

____

.. _breaking_concepts_concept_C4:

Provide Simple Peripheral Clock Source Selection APIs Per Peripheral
=====================================================================

When transitioning from HAL1 to HAL2 for configuring peripheral clocks, the main changes involve moving from a single structure-based configuration to more granular function calls.
In HAL1, peripheral clock configurations are done using the ``RCC_PeriphCLKInitTypeDef`` structure and a single function call ``HAL_RCCEx_PeriphCLKConfig``.
This method is footprint-consuming due to the inclusion of all possible peripheral instances (such as USART1, USART2 ... SPI3, SPI4) and their possible source clocks within a single structure.
In contrast, HAL2 uses specific function calls for each configuration step, such as ``HAL_RCC_ADCDAC_SetKernelClkSource`` for setting the ADC/DAC clock source
and ``HAL_RCC_SAI1_SetKernelClkSource`` for setting the SAI1 clock source.
This approach in HAL2 provides more explicit and modular control over the peripheral clock settings, enhancing clarity and maintainability of the code while reducing memory footprint.

.. list-table:: Comparison of HAL1 and HAL2 (Peripheral Clock Configuration)
   :header-rows: 1

   * - **Scope**
     - **HAL1**
     - **HAL2**
   * - **Example 1: ADC/DAC Clock Configuration**
     - .. code-block:: c

           RCC_PeriphCLKInitTypeDef PeriphClkInit;

           PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADCDAC;
           PeriphClkInit.AdcDacClockSelection = RCC_ADCDACCLKSOURCE_HSI;

           HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
     - .. code-block:: c

           HAL_RCC_ADCDAC_SetKernelClkSource(HAL_RCC_ADCDAC_CLK_SRC_HSI);
   * - **Example 2: SAI1 Clock Configuration**
     - .. code-block:: c

           GPIO_InitTypeDef GPIO_InitStruct;
           RCC_PeriphCLKInitTypeDef PeriphClkInit;

           PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_SAI1;
           PeriphClkInit.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLL2;

           PeriphClkInit.PLL2.PLL2Source = RCC_PLLSOURCE_MSI;
           PeriphClkInit.PLL2.PLL2M = 1;
           PeriphClkInit.PLL2.PLL2N = 48;
           PeriphClkInit.PLL2.PLL2P = 17;
           PeriphClkInit.PLL2.PLL2Q = 2;
           PeriphClkInit.PLL2.PLL2R = 2;
           PeriphClkInit.PLL2.PLL2RGE = RCC_PLLVCIRANGE_0;
           PeriphClkInit.PLL2.PLL2FRACN = 0;
           PeriphClkInit.PLL2.PLL2ClockOut = RCC_PLL2_DIVP;

           HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

     - .. code-block:: c

           hal_rcc_pll_config_t pll2_config;





           pll2_config.pll_source = HAL_RCC_PLLSOURCE_MSIS;
           pll2_config.pll_m = 1;
           pll2_config.pll_n = 48;
           pll2_config.pll_p = 17;
           pll2_config.pll_q = 2;
           pll2_config.pll_r = 2;
           pll2_config.pll_fracn = 0;

           HAL_RCC_PLL2_SetConfig(&pll2_config);
           HAL_RCC_PLL2_Enable();
           HAL_RCC_PLL2_EnableOutput(HAL_RCC_PLL2_OUTPUT_P);

           HAL_RCC_SAI1_SetKernelClkSource(HAL_RCC_SAI1_CLK_SOURCE_PLL2P);

____

.. _breaking_concepts_concept_C5:

Keep Global HAL PPP IRQ Handler and Provide Specialized HAL PPP IRQ Handlers for Individual scope
==================================================================================================
In HAL1, a ``HAL_PPP_IRQHandler`` function is provided for drivers that support interrupt modes.
This function handles all possible interrupts of the peripherals, clears all related flags,
and issues all possible callbacks related to these flags. For certain HAL drivers, such as the HAL TIM,
this makes the `HAL_PPP_IRQHandler` processing time and footprint heavy compared to what the user application actually needs.
Usually, a user application will need a subset of the possible available interrupts but not all of them.
Checking all the interrupt flags each time may be problematic for applications that have high real-time constraints.

To improve the situation, HAL2 retains this global ``HAL_PPP_IRQHandler`` and provides additional specialized HAL IRQ handlers.
The scope of these specialized IRQ handlers is limited to a given process or coherent events.
These specialized HAL IRQ handlers will manage only the interrupts, flags, and callbacks within their scope.

.. list-table:: Comparison of HAL1 and HAL2 (IRQ Handlers)
   :header-rows: 1

   * - **Scope**
     - **HAL1**
     - **HAL2**
   * - **HAL TIM IRQ Handler**
     - .. code-block:: c

           void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim);
     - .. code-block:: c

           void HAL_TIM_IRQHandler(hal_tim_handle_t *htim);

           void HAL_TIM_UPD_IRQHandler(hal_tim_handle_t *htim);
           void HAL_TIM_CC_IRQHandler(hal_tim_handle_t *htim);
           void HAL_TIM_BRK_TERR_IERR_IRQHandler(hal_tim_handle_t *htim);
           void HAL_TIM_TRGI_COM_DIR_IDX_IRQHandler(hal_tim_handle_t *htim);
   * - **HAL LTDC IRQ Handler**
     - .. code-block:: c

           void HAL_LTDC_IRQHandler(LTDC_HandleTypeDef *hltdc);
     - .. code-block:: c

           void HAL_LTDC_IRQHandler(hal_ltdc_handle_t *hltdc);

           void HAL_LTDC_ERR_IRQHandler(hal_ltdc_handle_t *hltdc);
           void HAL_LTDC_LineDetectionIRQHandler(hal_ltdc_handle_t *hltdc);
           void HAL_LTDC_ReloadEventIRQHandler(hal_ltdc_handle_t *hltdc);






