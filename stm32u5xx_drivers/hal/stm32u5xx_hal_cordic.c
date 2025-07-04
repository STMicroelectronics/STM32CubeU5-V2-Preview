/**
  ******************************************************************************
  * @file    stm32u5xx_hal_cordic.c
  * @brief   CORDIC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the CORDIC peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *           + Callback functions
  *           + callbacks
  *           + IRQ handler management
  *           + Peripheral state and error
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup CORDIC
  * @{

# How to use the CORDIC HAL module driver

1. Declare a hal_cordic_handle_t handle structure and initialize the CORDIC driver with a CORDIC instance using the
   HAL_CORDIC_Init().
   The CORDIC clock is enabled inside the HAL_CORDIC_Init() if USE_HAL_CORDIC_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO.
2. Configure the low level hardware (CLOCK, NVIC, DMA...):
  - Enable the CORDIC clock USE_HAL_CORDIC_CLK_ENABLE_MODEL is not defined or defined to "HAL_CLK_ENABLE_NO".
  - NVIC configuration if you need to use interrupt process
    - Configure the CORDIC interrupt priority using HAL_NVIC_SetPriority().
    - Enable the CORDIC IRQ handler using HAL_NVIC_EnableIRQ().
    - In CORDIC IRQ handler, call HAL_CORDIC_IRQHandler().
  - DMA configuration if you need to use DMA process
    - Enable the GPDMA1 interface clock using HAL_RCC_GPDMA1_EnableClock();
    - Configure and enable two DMA channels one for managing data transfer from memory to peripheral (input channel)
      and another channel for managing data transfer from peripheral to memory (output channel).
    - Associate the initialized DMA handle to the CORDIC DMA handle.
    - Configure the priority and enable the NVIC for the transfer complete interrupt on the two DMA channels by calling
      the HAL_NVIC_SetPriority() and HAL_NVIC_EnableIRQ() functions.

3. Configure the minimal configuration needed for the CORDIC driver by calling HAL_CORDIC_SetConfig().
  - This function configures:
    - Processing functions: Cosine, Sine, Phase, Modulus, Arctangent, Hyperbolic cosine, Hyperbolic sine,
      Hyperbolic arctangent, Natural log, Square root.
    - Scaling factor: 1 to 2exp(-7).
    - Width of input data: 32 bits input data size (Q1.31 format) or 16 bits input data size (Q1.15 format).
    - Width of output data: 32 bits output data size (Q1.31 format) or 16 bits output data size (Q1.15 format).
    - Number of 32-bit write expected for one calculation: One 32-bits write or Two 32-bit write.
    - Number of 32-bit read expected after one calculation: One 32-bits read or Two 32-bit read.
    - Precision: 1 to 15 cycles for calculation (the more cycles, the better precision).

4. Operation modes:
  - Polling mode operations:

    - Processing API is a blocking function i.e. it processes the data and waits until the RRDY flag is raised in the
      CORDIC_CSR register indicating that results are available in CORDIC_RDATA. That process is performed in the API
      by calling the HAL_CORDIC_Calculate() function.
    - HAL_CORDIC_Write() provides a way to give to the CORDIC a data input buffer. That function must be associated
      with a DMA out mode process or an output buffer in IT mode.
    - HAL_CORDIC_Read() permits to provides an output buffer in polling mode. That function must be associated with
      a DMA In mode process.
    - HAL_CORDIC_Write() and HAL_CORDIC_Read() cannot be associated  together to provide a full polling mode for input
      and output polling mode.

  - Zero-overhead mode operations:

    - Processing API is a blocking function i.e. it writes data to process and read immediately the CORDIC_RDATA
      register to get the result. Any attempt to read the CORDIC_RDATA register inserts bus wait state until the
      calculation is completed. That process is performed in the API by calling HAL_CORDIC_CalculateZeroOverhead().

  - Interrupt mode operations:

    - Processing API is not blocking function, an interrupt is generated whenever the RRDY flag is set. The result
      of calculation is read under interrupt service routine. However it is slower than directly reading the result
      or polling the flag due to interrupt handling delays. That process is performed by calling
      HAL_CORDIC_Calculate_IT().
    - When all the data are written, HAL_CORDIC_WriteDataCpltCallback() is executed. This callback is a weak function
      and can be overridden by the user or by registering a callback function.
     - When all the calculus are done, HAL_CORDIC_CalculateCpltCallback() is executed. This callback is a weak function
      and can be overridden by the user or by registering a callback function.
    - In case of flag error, the HAL_CORDIC_ErrorCallback() callback is executed. This callback is a weak function and
      can be overridden by the user or by registering a callback function.

  - DMA mode operations:

    - Processing API is not a blocking function and allows to offload the CPU. If both channels are enabled,
      the CORDIC can autonomously performs repeated calculations on a buffer of data without any CPU access.
      That process is performed by calling HAL_CORDIC_Calculate_DMA() function, that function operates with
      a DMA channel In and a DMA channel out only.
    - The DMA current transfer can be cancelled using the HAL_CORDIC_Abort() or HAL_CORDIC_Abort_IT() functions.
    - When half of all the data are written, HAL_CORDIC_WriteHalfCpltCallback() is executed. This callback is a weak
      function and can be overridden by the user or by registering a callback function.
    - When half of all the results reading is performed, HAL_CORDIC_ReadHalfCpltCallback() is executed. This callback
      is a weak function and can be overridden by the user or by registering a callback function.
    - When all the calculus are done, HAL_CORDIC_CalculateCpltCallback() is executed. This callback is a weak function
      and can be overridden by the user or by registering a callback function.
    - In case of flag error, HAL_CORDIC_ErrorCallback() function is executed. This callback is a weak function
      and can be overridden by the user or by registering a callback function.

5. Write and Read operations directly driven by another peripheral (Timer, ADC, DAC, etc) are available through:
    - Use of HAL_CORDIC_GetWriteAddress() and HAL_CORDIC_GetReadAddress() functions to get the addresses of the
      CORDIC_WDATA and CORDIC_RDATA registers according to the user application needs.
    - Whatever the process used with the CORDIC driver, the peripheral calls two dedicated functions:
        - HAL_CORDIC_LockWriteAccessForExternPeriph() to indicate that the driver is used and busy (ACTIVE state).
        - HAL_CORDIC_UnlockWriteAccessForExternPeriph() to indicate that the driver is now available (IDLE state).

6. Call HAL_CORDIC_DeInit() to de-initialize the CORDIC peripheral.

7. Callback definition in Interrupt or DMA mode:

  When the preprocessor directive USE_HAL_CORDIC_REGISTER_CALLBACKS is set to 1, the user can configure dynamically the
  driver callbacks, via its own method:

Callback name               | Default value                      | Callback registration function
----------------------------| -----------------------------------| --------------------------------------------
ErrorCallback               | HAL_CORDIC_ErrorCallback           | HAL_CORDIC_RegisterErrorCallback()
CalculationCpltCallback     | HAL_CORDIC_CalculateCpltCallback   | HAL_CORDIC_RegisterCalculateCpltCallback()
WriteDataCpltCallback       | HAL_CORDIC_WriteDataCpltCallback   | HAL_CORDIC_RegisterWriteDataCpltCallback()
AbortCpltCallback           | HAL_CORDIC_AbortCpltCallback       | HAL_CORDIC_RegisterAbortCpltCallback()
WriteHalfCpltCallback       | HAL_CORDIC_WriteHalfCpltCallback   | HAL_CORDIC_RegisterWriteHalfCpltCallback()
ReadHalfCpltCallback        | HAL_CORDIC_ReadHalfCpltCallback    | HAL_CORDIC_RegisterReadHalfCpltCallback()

  To unregister a callback, it must be done by registering the default callback.

  By default, after the HAL_CORDIC_Init() and when the state is @ref HAL_CORDIC_STATE_INIT, all callbacks are set to
  the corresponding weak functions.

  Callbacks can be registered in HAL_CORDIC_STATE_INIT or HAL_CORDIC_STATE_IDLE states only.

  When the preprocessing directive USE_HAL_CORDIC_REGISTER_CALLBACKS is set to 0 or undefined, the callback registration
  feature is not available and all callbacks are set to the corresponding weak functions.

# Configuration inside the CORDIC driver

Config defines                   | Where            | Default value     | Note
-------------------------------- | ---------------- | ----------------- | --------------------------------------------
PRODUCT                          | PreProcessor env |       NONE        | The selected device
USE_HAL_CORDIC_CLK_ENABLE_MODEL  | hal_conf.h       | HAL_CLK_ENABLE_NO | Enable peripheral clock in the HAL_CORDIC_Init
USE_HAL_CORDIC_MODULE            | hal_conf.h       |        1          | When set, HAL CORDIC module is enabled
USE_HAL_CORDIC_DMA               | hal_conf.h       |        1          | Enable DMA code inside CORDIC
USE_HAL_CORDIC_GET_LAST_ERRORS   | hal_conf.h       |        0          | Enable the get last errors
USE_HAL_CORDIC_USER_DATA         | hal_conf.h       |        0          | Enable the set/get user data
USE_HAL_CORDIC_REGISTER_CALLBACKS| hal_conf.h       |        0          | Enable the register callbacks assert
USE_HAL_CHECK_PARAM              | hal_conf.h       |        0          | Enable checking of vital parameters at runtime
USE_HAL_CHECK_PROCESS_STATE      | hal_conf.h       |        0          | Enable atomic access to process state check
USE_ASSERT_DBG_PARAM             | PreProcessor env |       NONE        | Enable the params assert
USE_ASSERT_DBG_STATE             | PreProcessor env |       NONE        | Enable the state assert

  */


#if defined(CORDIC)
#if defined(USE_HAL_CORDIC_MODULE) && (USE_HAL_CORDIC_MODULE == 1)

/* Private constants ---------------------------------------------------------*/
/** @defgroup CORDIC_Private_Constants CORDIC Private Constants
  * @{
  */
#define CORDIC_DMA_READ_ENABLE        CORDIC_CSR_DMAREN         /*!< DMA Read requests enable       */
#define CORDIC_DMA_WRITE_ENABLE       CORDIC_CSR_DMAWEN         /*!< DMA Write channel enable       */
#define CORDIC_IT_ENABLE              LL_CORDIC_IT_IEN          /*!< Result ready interrupt enable  */
#define CORDIC_FLAG_RRDY              LL_CORDIC_FLAG_RRDY       /*!< Result Ready Flag              */
#define CORDIC_ARGUMENT1              0x00000000                /*!< Default argument 1             */
#define CORDIC_ARGUMENT2              0x7FFFFFFF                /*!< Default argument 2             */
#define CORDIC_FLAG_NOT_ACTIVE        0UL                       /*!< Flag not active                */
#define CORDIC_FLAG_ACTIVE            1UL                       /*!< Flag active                    */
#define CORDIC_IT_DISABLED            0UL                       /*!< IT disabled                    */
#define CORDIC_IT_ENABLED             1UL                       /*!< IT enabled                     */
/**
  * @}
  */    /* CORDIC_Private_Constants CORDIC Private Constants */

/* Private macro -------------------------------------------------------------*/
/** @defgroup CORDIC_Private_Macros CORDIC Private Macros
  * @{
  */
/**
  * @brief Retrieve the CORDIC HW cmsis instance from the hal handle
  */
#define CORDIC_GET_INSTANCE(handle) \
  ((CORDIC_TypeDef *)((uint32_t)((handle)->instance)))

/**
  * @brief  Verify the CORDIC function
  */
#define IS_CORDIC_FUNCTION(function) (((function) == HAL_CORDIC_FUNCTION_COSINE)          \
                                      || ((function) == HAL_CORDIC_FUNCTION_SINE)         \
                                      || ((function) == HAL_CORDIC_FUNCTION_PHASE)        \
                                      || ((function) == HAL_CORDIC_FUNCTION_MODULUS)      \
                                      || ((function) == HAL_CORDIC_FUNCTION_ARCTANGENT)   \
                                      || ((function) == HAL_CORDIC_FUNCTION_HCOSINE)      \
                                      || ((function) == HAL_CORDIC_FUNCTION_HSINE)        \
                                      || ((function) == HAL_CORDIC_FUNCTION_HARCTANGENT)  \
                                      || ((function) == HAL_CORDIC_FUNCTION_NATURAL_LOG)  \
                                      || ((function) == HAL_CORDIC_FUNCTION_SQUARE_ROOT))

/**
  * @brief  Verify the CORDIC precision
  */
#define IS_CORDIC_PRECISION(precision) (((precision) == HAL_CORDIC_PRECISION_1CYCLE)      \
                                        || ((precision) == HAL_CORDIC_PRECISION_2CYCLES)  \
                                        || ((precision) == HAL_CORDIC_PRECISION_3CYCLES)  \
                                        || ((precision) == HAL_CORDIC_PRECISION_4CYCLES)  \
                                        || ((precision) == HAL_CORDIC_PRECISION_5CYCLES)  \
                                        || ((precision) == HAL_CORDIC_PRECISION_6CYCLES)  \
                                        || ((precision) == HAL_CORDIC_PRECISION_7CYCLES)  \
                                        || ((precision) == HAL_CORDIC_PRECISION_8CYCLES)  \
                                        || ((precision) == HAL_CORDIC_PRECISION_9CYCLES)  \
                                        || ((precision) == HAL_CORDIC_PRECISION_10CYCLES) \
                                        || ((precision) == HAL_CORDIC_PRECISION_11CYCLES) \
                                        || ((precision) == HAL_CORDIC_PRECISION_12CYCLES) \
                                        || ((precision) == HAL_CORDIC_PRECISION_13CYCLES) \
                                        || ((precision) == HAL_CORDIC_PRECISION_14CYCLES) \
                                        || ((precision) == HAL_CORDIC_PRECISION_15CYCLES))

/**
  * @brief  Verify the CORDIC scaling factor
  */
#define IS_CORDIC_SCALE(scale) (((scale) == HAL_CORDIC_SCALE_0)     \
                                || ((scale) == HAL_CORDIC_SCALE_1)  \
                                || ((scale) == HAL_CORDIC_SCALE_2)  \
                                || ((scale) == HAL_CORDIC_SCALE_3)  \
                                || ((scale) == HAL_CORDIC_SCALE_4)  \
                                || ((scale) == HAL_CORDIC_SCALE_5)  \
                                || ((scale) == HAL_CORDIC_SCALE_6)  \
                                || ((scale) == HAL_CORDIC_SCALE_7))

/**
  * @brief  Verify the CORDIC number of 32-bits arguments expected for one calculation
  */
#define IS_CORDIC_NBARGS(nbargs) (((nbargs) == HAL_CORDIC_ARG_NB_1) \
                                  || ((nbargs) == HAL_CORDIC_ARG_NB_2))

/**
  * @brief  Verify the CORDIC number of 32-bits results expected after one calculation
  */
#define IS_CORDIC_RESULT_NB(result_nb) (((result_nb) == HAL_CORDIC_RESULT_NB_1) \
                                        || ((result_nb) == HAL_CORDIC_RESULT_NB_2))

/**
  * @brief  Verify the CORDIC input data size for one calculation
  */
#define IS_CORDIC_IN_SIZE(in_size) (((in_size) == HAL_CORDIC_IN_SIZE_32BITS) \
                                    || ((in_size) == HAL_CORDIC_IN_SIZE_16BITS))

/**
  * @brief  Verify the CORDIC output data size for one calculation
  */
#define IS_CORDIC_OUT_SIZE(out_size) (((out_size) == HAL_CORDIC_OUT_SIZE_32BITS) \
                                      || ((out_size) == HAL_CORDIC_OUT_SIZE_16BITS))

/**
  * @brief  Verify that CORDIC input and output buffers are not both null.
  */
#define IS_CORDIC_BUFFERS_NOT_VALID(buff1, buff2) ((buff1 == NULL) && (buff2 == NULL))

/**
  * @brief  Verify write WDATA DMA optional interrupt
  * @param  interrupt Interrupt selection
  * @retval SET   interrupt is valid
  * @retval RESET interrupt is invalid
  */
#define IS_CORDIC_OPT_DMA_IT_WR(interrupt) (((interrupt) == HAL_CORDIC_OPT_DMA_NONE)\
                                            || ((interrupt) == HAL_CORDIC_OPT_DMA_IT_HALF_CPLT)\
                                            || ((interrupt) == HAL_CORDIC_OPT_DMA_ALL))

/**
  * @brief  Verify  read RDATA DMA optional interrupt
  * @param  interrupt Interrupt selection
  * @retval SET   interrupt is valid
  * @retval RESET interrupt is invalid
  */
#define IS_CORDIC_OPT_DMA_IT_RD(interrupt) (((interrupt) == HAL_CORDIC_OPT_DMA_NONE)\
                                            || ((interrupt) == HAL_CORDIC_OPT_DMA_IT_HALF_CPLT)\
                                            || ((interrupt) == HAL_CORDIC_OPT_DMA_ALL))


/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup CORDIC_Private_Functions CORDIC Private Functions
  * @{
  */
static inline void CORDIC_ResetArguments(hal_cordic_handle_t *hcordic);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
static inline uint32_t CORDIC_CheckPrecision(hal_cordic_function_t function, hal_cordic_precision_t precision);
static inline uint32_t CORDIC_CheckScale(hal_cordic_function_t function, hal_cordic_scale_factor_t scale);
#endif /* USE_HAL_CHECK_PARAM */
static uint32_t CORDIC_ValidateWriteNumber(uint32_t csr_reg, const hal_cordic_buffer_desc_t *p_inbuffer_desc);
static uint32_t CORDIC_ValidateReadNumber(uint32_t csr_reg, const hal_cordic_buffer_desc_t *p_outbuffer_desc);
static void CORDIC_WriteDataAndIncPtr(hal_cordic_handle_t *hcordic, const int32_t **pp_input_buffer);
static void CORDIC_ReadDataAndIncPtr(hal_cordic_handle_t *hcordic, int32_t **pp_output_buffer);
static hal_status_t CORDIC_Abort(hal_cordic_handle_t *hcordic);
#if defined(USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
static void CORDIC_DMAAbort(hal_dma_handle_t *hdma);
static void CORDIC_DMAInCplt(hal_dma_handle_t *hdma);
static void CORDIC_DMAInHalfCplt(hal_dma_handle_t *hdma);
static void CORDIC_DMAOutCplt(hal_dma_handle_t *hdma);
static void CORDIC_DMAOutHalfCplt(hal_dma_handle_t *hdma);
static void CORDIC_DMAError(hal_dma_handle_t *hdma);
#endif /* USE_HAL_CORDIC_DMA */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup CORDIC_Exported_Functions
  * @{
  */

/** @addtogroup CORDIC_Exported_Functions_Group1
  * @{

This section provides a set of functions allowing to initialize and deinitialize the CORDIC peripheral:

- Call the function HAL_CORDIC_Init() to initialize the selected CORDIC handle.
- Call the function HAL_CORDIC_DeInit() to deinitialize the selected CORDIC handle.
  */

/**
  * @brief  Initialize the HAL CORDIC handle and associate it to an instance of the CORDIC peripheral.
  * @param  hcordic  Pointer to a hal_cordic_handle_t.
  * @param  instance CORDIC instance.
  * @retval HAL_OK              CORDIC instance has been correctly initialized.
  * @retval HAL_INVALID_PARAM   Pointer to HAL CORDIC handle is NULL.
  */
hal_status_t HAL_CORDIC_Init(hal_cordic_handle_t *hcordic, hal_cordic_t instance)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM(IS_CORDIC_ALL_INSTANCE((CORDIC_TypeDef *)((uint32_t)instance)));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the CORDIC handle allocation */
  if (hcordic == NULL)
  {
    /* Return error status */
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Instance */
  hcordic->instance = instance;

#if defined (USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
  hcordic->p_dma_in  = NULL;
  hcordic->p_dma_out = NULL;
#endif /* USE_HAL_CORDIC_DMA */

#if defined (USE_HAL_CORDIC_USER_DATA) && (USE_HAL_CORDIC_USER_DATA == 1)
  hcordic->p_user_data = (void *) NULL;
#endif /* USE_HAL_CORDIC_USER_DATA */

#if defined(USE_HAL_CORDIC_REGISTER_CALLBACKS) && (USE_HAL_CORDIC_REGISTER_CALLBACKS == 1)
  if (hcordic->global_state == HAL_CORDIC_STATE_RESET)
  {
    /* Reset callbacks to legacy functions */
    hcordic->p_error_cb           = HAL_CORDIC_ErrorCallback;           /* Legacy weak ErrorCallback           */
    hcordic->p_calculate_cpt_cb   = HAL_CORDIC_CalculateCpltCallback;   /* Legacy weak CalculateCpltCallback   */
    hcordic->p_write_cpt_cb       = HAL_CORDIC_WriteDataCpltCallback;   /* Legacy weak WriteDataCpltCallback   */
    hcordic->p_abort_cplt_cb      = HAL_CORDIC_AbortCpltCallback;       /* Legacy weak Abort complete callback */
#if defined (USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
    hcordic->p_read_half_cplt_cb  = HAL_CORDIC_ReadHalfCpltCallback;    /* Legacy weak ReadhalfCpltCallback    */
    hcordic->p_write_half_cplt_cb = HAL_CORDIC_WriteHalfCpltCallback;   /* Legacy weak WritehalfCpltCallback   */
#endif /* USE_HAL_CORDIC_DMA */
  }
#endif /* (USE_HAL_CORDIC_REGISTER_CALLBACKS) */

#if defined(USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
  /* Set CORDIC error code to none */
  hcordic->last_error_codes = HAL_CORDIC_ERROR_NONE;
#endif /* USE_HAL_CORDIC_GET_LAST_ERRORS */

  /* Reset p_input_buffer and p_output_buffer */
  hcordic->p_input_buffer  = NULL;
  hcordic->p_output_buffer = NULL;

  /* Reset nb_calculus_to_do and nb_calculus_to_get */
  hcordic->nb_calculus_to_do  = 0UL;
  hcordic->nb_calculus_to_get = 0UL;

#if defined(USE_HAL_CORDIC_CLK_ENABLE_MODEL) && (USE_HAL_CORDIC_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  /* Enable CORDIC clock */
  if (instance == HAL_CORDIC)
  {
    HAL_RCC_CORDIC_EnableClock();
  }
#endif /* USE_HAL_CORDIC_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO */

  /* Change CORDIC peripheral state */
  hcordic->global_state = HAL_CORDIC_STATE_INIT;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  DeInitialize the CORDIC peripheral.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  */
void HAL_CORDIC_DeInit(hal_cordic_handle_t *hcordic)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM(IS_CORDIC_ALL_INSTANCE((CORDIC_TypeDef *)((uint32_t)hcordic->instance)));

  const hal_cordic_state_t temp_state = hcordic->global_state;
  if ((temp_state == HAL_CORDIC_STATE_IDLE) || (temp_state == HAL_CORDIC_STATE_ACTIVE))
  {
    /* Stop current process */
    (void)CORDIC_Abort(hcordic);
  }

  /* Change CORDIC peripheral state */
  hcordic->global_state = HAL_CORDIC_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup CORDIC_Exported_Functions_Group2
  * @{

This section provides a set of functions allowing the configuration the CORDIC driver:

- Call the function HAL_CORDIC_SetConfig() to configure the peripheral before starting the CORDIC driver.
- Call the function HAL_CORDIC_GetConfig() to retrieve the configuration.
- Call the function HAL_CORDIC_SetFunction() to set the mathematical function.
- Call the function HAL_CORDIC_GetFunction() to retrieve the current mathematical function.
- Call the function HAL_CORDIC_SetWidthInputSize() to set the width (16bits or 32bits) of the input data.
- Call the function HAL_CORDIC_GetWidthInputSize() to retrieve the current width of the input data.
- Call the function HAL_CORDIC_SetWidthOutputSize() to set the width (16bits or 32bits) of the output data.
- Call the function HAL_CORDIC_GetWidthOutputSize() to retrieve the current width of the output data.
- Call the function HAL_CORDIC_SetNumberArguments() to set the number of arguments of the function.
- Call the function HAL_CORDIC_GetNumberArguments() to retrieve the current number of arguments of the function.
- Call the function HAL_CORDIC_SetNumberResults() to set the number of results of the function.
- Call the function HAL_CORDIC_GetNumberResults() to retrieve the current number of results.
- Call the function HAL_CORDIC_SetPrecision() to set the precision required.
- Call the function HAL_CORDIC_GetPrecision() to retrieve the current precision.
- Call the function HAL_CORDIC_SetScale() to set the scaling factor.
- Call the function HAL_CORDIC_GetScale() to retrieve the current scaling factor.
- Call the function HAL_CORDIC_SetWriteDMA() to set the DMA channel for writing arguments.
- Call the function HAL_CORDIC_SetReadDMA() to set the DMA channel for reading results.
- Call the function HAL_CORDIC_GetWriteAddress() to get the address of the CORDIC_WDATA register.
- Call the function HAL_CORDIC_GetReadAddress() to get the address of the CORDIC_RDATA register.
- Call the function HAL_CORDIC_LockWriteAccessForExternPeriph() to Lock write access to WDATA in peripheral mode.
- Call the function HAL_CORDIC_UnlockWriteAccessForExternPeriph() to Unlock write access to WDATA in peripheral mode.
  */

/**
  * @brief  Configure the CORDIC driver.
  * @param  hcordic  Pointer to a hal_cordic_handle_t.
  * @param  p_config Pointer to a @ref hal_cordic_config_t structure.
  * @retval HAL_OK              CORDIC block has been correctly configured.
  * @retval HAL_INVALID_PARAM   When the p_config pointer is NULL.
  */
hal_status_t HAL_CORDIC_SetConfig(hal_cordic_handle_t *hcordic, const hal_cordic_config_t *p_config)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(IS_CORDIC_FUNCTION(p_config->function));
  ASSERT_DBG_PARAM(IS_CORDIC_PRECISION(p_config->precision));
  ASSERT_DBG_PARAM(IS_CORDIC_SCALE(p_config->scale));
  ASSERT_DBG_PARAM(IS_CORDIC_NBARGS(p_config->nb_args));
  ASSERT_DBG_PARAM(IS_CORDIC_RESULT_NB(p_config->nb_results));
  ASSERT_DBG_PARAM(IS_CORDIC_IN_SIZE(p_config->in_size));
  ASSERT_DBG_PARAM(IS_CORDIC_OUT_SIZE(p_config->out_size));

  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_INIT | (uint32_t)HAL_CORDIC_STATE_IDLE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }

  /* Check the scaling_factor vs the function */
  if (CORDIC_CheckScale(p_config->function, p_config->scale) == 0UL)
  {
    return HAL_INVALID_PARAM;
  }

  /* Check the precision vs the function */
  if (CORDIC_CheckPrecision(p_config->function, p_config->precision) == 0UL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Apply all configuration parameters in CORDIC control register */
  LL_CORDIC_Config(p_cordic, (uint32_t)(p_config->function), (uint32_t)(p_config->precision),
                   (uint32_t)(p_config->scale), (uint32_t)(p_config->nb_args),
                   (uint32_t)(p_config->nb_results), (uint32_t)(p_config->in_size),
                   (uint32_t)(p_config->out_size));


  /* Update the state */
  hcordic->global_state = HAL_CORDIC_STATE_IDLE;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Retrieve the CORDIC global configuration.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @param  p_config pointer to @ref hal_cordic_config_t structure.
  */
void HAL_CORDIC_GetConfig(const hal_cordic_handle_t *hcordic, hal_cordic_config_t *p_config)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE
                   | (uint32_t)HAL_CORDIC_STATE_ACTIVE
                   | (uint32_t)HAL_CORDIC_STATE_ABORT);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  p_config->function = (hal_cordic_function_t)LL_CORDIC_GetFunction(p_cordic);   /* Get the function                  */
  p_config->scale = (hal_cordic_scale_factor_t)LL_CORDIC_GetScale(p_cordic);     /* Get the scaling factor            */
  p_config->in_size = (hal_cordic_in_size_t)LL_CORDIC_GetInSize(p_cordic);       /* Get the width of arguments        */
  p_config->out_size = (hal_cordic_out_size_t)LL_CORDIC_GetOutSize(p_cordic);    /* Get the width of results          */
  p_config->precision = (hal_cordic_precision_t)LL_CORDIC_GetPrecision(p_cordic);/* Get the precision in cycles number*/
  p_config->nb_args = (hal_cordic_arg_nb_t)LL_CORDIC_GetNbWrite(p_cordic);       /* Get the number of arguments       */
  p_config->nb_results  = (hal_cordic_result_nb_t)LL_CORDIC_GetNbRead(p_cordic); /* Get the number of results         */
}

/**
  * @brief  Set the CORDIC function.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @param  function  The value can be value of @ref hal_cordic_function_t.
  * @retval HAL_OK    CORDIC function was successfully set.
  */
hal_status_t HAL_CORDIC_SetFunction(hal_cordic_handle_t *hcordic, hal_cordic_function_t function)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM(IS_CORDIC_FUNCTION(function));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE);

  /* Flush the argument register when calculation is over */
  CORDIC_ResetArguments(hcordic);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  LL_CORDIC_SetFunction(p_cordic, (uint32_t)function);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Retrieve the current CORDIC function
  * @param  hcordic Pointer to a hal_cordic_handle_t structure.
  * @retval hal_cordic_function_t CORDIC function.
  */
hal_cordic_function_t HAL_CORDIC_GetFunction(const hal_cordic_handle_t *hcordic)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE
                   | (uint32_t)HAL_CORDIC_STATE_ACTIVE
                   | (uint32_t)HAL_CORDIC_STATE_ABORT);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  return ((hal_cordic_function_t)LL_CORDIC_GetFunction(p_cordic));
}

/**
  * @brief  Set the CORDIC precision in multiple of 4 cycles number
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @param  precision The value can be a value of @ref hal_cordic_precision_t.
  * @retval HAL_OK      CORDIC precision was successfully configured.
  * @retval HAL_INVALID_PARAM The precision does not match the function requirements.
  */
hal_status_t HAL_CORDIC_SetPrecision(hal_cordic_handle_t *hcordic, const hal_cordic_precision_t precision)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM(IS_CORDIC_PRECISION(precision));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* read the CSR register */
  uint32_t csr_reg = LL_CORDIC_READ_REG((p_cordic), CSR);

  hal_cordic_function_t function  = (hal_cordic_function_t)(uint32_t)((csr_reg & CORDIC_CSR_FUNC_Msk)
                                                                      >> CORDIC_CSR_FUNC_Pos);

  /* Check coherency of the precision vs function already set */
  if (CORDIC_CheckPrecision(function, precision) == 0UL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_CORDIC_SetPrecision(p_cordic, (uint32_t)precision);
  /* Return function status */
  return HAL_OK;

}

/**
  * @brief  Retrieve the CORDIC precision.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @retval hal_cordic_precision_t CORDIC precision.
 */
hal_cordic_precision_t HAL_CORDIC_GetPrecision(const hal_cordic_handle_t *hcordic)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE
                   | (uint32_t)HAL_CORDIC_STATE_ACTIVE
                   | (uint32_t)HAL_CORDIC_STATE_ABORT);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  return ((hal_cordic_precision_t)LL_CORDIC_GetPrecision(p_cordic));
}

/**
  * @brief  Set the CORDIC scaling factor.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @param  scaling_factor The value can be a value of @ref hal_cordic_scale_factor_t.
  * @retval HAL_OK  CORDIC scaling factor was successfully configured.
  * @retval HAL_INVALID_PARAM The scale does not match the function requirements.
  */
hal_status_t HAL_CORDIC_SetScale(hal_cordic_handle_t *hcordic, const hal_cordic_scale_factor_t scaling_factor)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM(IS_CORDIC_SCALE(scaling_factor));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* read the CSR register */
  uint32_t csr_reg = LL_CORDIC_READ_REG((p_cordic), CSR);

  hal_cordic_function_t function  = (hal_cordic_function_t)(uint32_t)((csr_reg & CORDIC_CSR_FUNC_Msk)
                                                                      >> CORDIC_CSR_FUNC_Pos);

  /* Check coherency of the scale vs function already set */
  if (CORDIC_CheckScale(function, scaling_factor) == 0UL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_CORDIC_SetScale(p_cordic, (uint32_t)scaling_factor);
  /* Return function status */
  return HAL_OK;

}

/**
  * @brief  Retrieve the CORDIC scaling factor.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @retval hal_cordic_scale_factor_t CORDIC scaling factor.
  */
hal_cordic_scale_factor_t HAL_CORDIC_GetScale(const hal_cordic_handle_t *hcordic)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE
                   | (uint32_t)HAL_CORDIC_STATE_ACTIVE
                   | (uint32_t)HAL_CORDIC_STATE_ABORT);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  return ((hal_cordic_scale_factor_t)LL_CORDIC_GetScale(p_cordic));
}

/**
  * @brief  Set the CORDIC argument width.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @param  input_size The value can be a value of @ref hal_cordic_in_size_t.
  * @retval HAL_OK     Data arguments width was successfully configured.
  */
hal_status_t HAL_CORDIC_SetWidthInputSize(hal_cordic_handle_t *hcordic,
                                          const hal_cordic_in_size_t input_size)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM(IS_CORDIC_IN_SIZE(input_size));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  LL_CORDIC_SetInSize(p_cordic, (uint32_t)input_size);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Retrieve the CORDIC argument width.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @retval hal_cordic_in_size_t CORDIC argument width.
  */
hal_cordic_in_size_t HAL_CORDIC_GetWidthInputSize(const hal_cordic_handle_t *hcordic)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE
                   | (uint32_t)HAL_CORDIC_STATE_ACTIVE
                   | (uint32_t)HAL_CORDIC_STATE_ABORT);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  return ((hal_cordic_in_size_t)LL_CORDIC_GetInSize(p_cordic));
}

/**
  * @brief  Set the CORDIC result width.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @param  output_size The value can be a value of @ref hal_cordic_out_size_t.
  * @retval HAL_OK      Results width was successfully configured.
  */
hal_status_t HAL_CORDIC_SetWidthOutputSize(hal_cordic_handle_t *hcordic,
                                           const hal_cordic_out_size_t output_size)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM(IS_CORDIC_OUT_SIZE(output_size));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  LL_CORDIC_SetOutSize(p_cordic, (uint32_t)output_size);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Retrieve the CORDIC result width.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @retval hal_cordic_out_size_t CORDIC results width.
  */
hal_cordic_out_size_t HAL_CORDIC_GetWidthOutputSize(const hal_cordic_handle_t *hcordic)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE
                   | (uint32_t)HAL_CORDIC_STATE_ACTIVE
                   | (uint32_t)HAL_CORDIC_STATE_ABORT);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  return ((hal_cordic_out_size_t)LL_CORDIC_GetOutSize(p_cordic));
}

/**
  * @brief  Set the CORDIC  number of arguments expected by CORDIC_WDATA register.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @param  nb_argument The value can be a value of @ref hal_cordic_arg_nb_t.
  * @retval HAL_OK      Number of arguments was successfully configured.
  */
hal_status_t HAL_CORDIC_SetNumberArguments(hal_cordic_handle_t *hcordic, const hal_cordic_arg_nb_t nb_argument)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM(IS_CORDIC_NBARGS(nb_argument));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  LL_CORDIC_SetNbWrite(p_cordic, (uint32_t)nb_argument);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Retrieve the CORDIC number of arguments.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @retval hal_cordic_arg_nb_t CORDIC number of arguments
  */
hal_cordic_arg_nb_t HAL_CORDIC_GetNumberArguments(const hal_cordic_handle_t *hcordic)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE
                   | (uint32_t)HAL_CORDIC_STATE_ACTIVE
                   | (uint32_t)HAL_CORDIC_STATE_ABORT);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  return ((hal_cordic_arg_nb_t)LL_CORDIC_GetNbWrite(p_cordic));
}

/**
  * @brief  Set the CORDIC number of results expected by the CORDIC_RDATA register.
  * @param  hcordic pointer to a hal_cordic_handle_t.
  * @param  nb_results The value can be a value of @ref hal_cordic_result_nb_t.
  * @retval HAL_OK    Number of results was successfully configured.
  */
hal_status_t HAL_CORDIC_SetNumberResults(hal_cordic_handle_t *hcordic, const hal_cordic_result_nb_t nb_results)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM(IS_CORDIC_RESULT_NB(nb_results));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  LL_CORDIC_SetNbRead(p_cordic, (uint32_t)nb_results);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Retrieve the CORDIC number of results.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @retval HAL status
  */
hal_cordic_result_nb_t HAL_CORDIC_GetNumberResults(const hal_cordic_handle_t *hcordic)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE
                   | (uint32_t)HAL_CORDIC_STATE_ACTIVE
                   | (uint32_t)HAL_CORDIC_STATE_ABORT);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  return ((hal_cordic_result_nb_t)LL_CORDIC_GetNbRead(p_cordic));
}


/**
  * @brief  Get the CORDIC_WDATA write register address.
  *         Write data to CORDIC_WDATA can be directly driven by a timer or other peripheral such as an ADC.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @retval CORDIC_WDATA write register address
  */
volatile uint32_t *HAL_CORDIC_GetWriteAddress(const hal_cordic_handle_t *hcordic)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE
                   | (uint32_t)HAL_CORDIC_STATE_ACTIVE
                   | (uint32_t)HAL_CORDIC_STATE_ABORT);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  return (uint32_t *)(LL_CORDIC_DMA_GetRegAddr(p_cordic, LL_CORDIC_DMA_REG_DATA_IN));
}

/**
  * @brief  Get the CORDIC_RDATA read register address.
  *         Read data from CORDIC_RDATA can be directly driven by a timer or other peripheral such as a DAC.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @retval CORDIC_RDATA read register address
  */
volatile uint32_t *HAL_CORDIC_GetReadAddress(const hal_cordic_handle_t *hcordic)
{
  CORDIC_TypeDef *p_cordic;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE
                   | (uint32_t)HAL_CORDIC_STATE_ACTIVE
                   | (uint32_t)HAL_CORDIC_STATE_ABORT);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  return (uint32_t *)(LL_CORDIC_DMA_GetRegAddr(p_cordic, LL_CORDIC_DMA_REG_DATA_OUT));
}

/**
  * @brief Start write data to WDATA is directly driven by a timer or other peripheral such as an ADC.
  * @param  hcordic    Pointer to a hal_cordic_handle_t
  * @retval HAL_OK     Operation completed successfully
  * @retval HAL_BUSY     Concurrent process ongoing.
  */
hal_status_t HAL_CORDIC_LockWriteAccessForExternPeriph(hal_cordic_handle_t *hcordic)
{
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hcordic, global_state, HAL_CORDIC_STATE_IDLE, HAL_CORDIC_STATE_ACTIVE);

  return HAL_OK;
}

/**
  * @brief  Stop write data to WDATA directly driven by a timer or other peripheral such as an ADC.
  * @param  hcordic    Pointer to a hal_cordic_handle_t
  * @retval HAL_OK     Operation completed successfully
  */
hal_status_t HAL_CORDIC_UnlockWriteAccessForExternPeriph(hal_cordic_handle_t *hcordic)
{
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_ACTIVE);

  hcordic->global_state = HAL_CORDIC_STATE_IDLE;

  return HAL_OK;
}


#if defined (USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
/**
  * @brief  Set DMA channel for writing arguments.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @param  hdma_wr Pointer to a hal_dma_handle_t structure which contains the DMA instance.
  * @retval HAL_OK            The channel has been correctly set.
  * @retval HAL_INVALID_PARAM hdma_wr is NULL.
  */
hal_status_t HAL_CORDIC_SetWriteDMA(hal_cordic_handle_t *hcordic, hal_dma_handle_t *hdma_wr)
{
  ASSERT_DBG_PARAM(hcordic != NULL);
  ASSERT_DBG_PARAM(hdma_wr != NULL);

  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check input parameter */
  if (hdma_wr == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hcordic->p_dma_in = hdma_wr;
  hdma_wr->p_parent = hcordic;

  return HAL_OK;
}

/**
  * @brief  Set DMA channel for reading results.
  * @param  hcordic  Pointer to a hal_cordic_handle_t.
  * @param  hdma_rd  Pointer to a hal_dma_handle_t structure which contains the DMA instance.
  * @retval HAL_OK            The channel has been correctly set.
  * @retval HAL_INVALID_PARAM hdma_rd is NULL.
  */
hal_status_t HAL_CORDIC_SetReadDMA(hal_cordic_handle_t *hcordic, hal_dma_handle_t *hdma_rd)
{
  ASSERT_DBG_PARAM(hcordic != NULL);
  ASSERT_DBG_PARAM(hdma_rd != NULL);

  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check input parameter */
  if (hdma_rd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hcordic->p_dma_out = hdma_rd;
  hdma_rd->p_parent  = hcordic;

  return HAL_OK;
}

#endif /* USE_HAL_CORDIC_DMA */

/**
  * @}
  */


/** @addtogroup CORDIC_Exported_Functions_Group4
  * @{

This section provides a set of functions allowing the calculation modes of the CORDIC.

There are four modes of calculation:
- Blocking mode: The communication is performed in the polling mode.
  - HAL_CORDIC_Write() : Write data to WDATA register in polling mode.
  - HAL_CORDIC_Read() : Read data from RDATA register in polling mode.
  - HAL_CORDIC_Calculate() : Perform a write and read operations in polling mode.
  - HAL_CORDIC_CalculateZeroOverhead() : Perform write and read Zero-Overhead operations in polling mode.

- Non-blocking mode functions with interrupts are:
   - HAL_CORDIC_Write_IT() : Write data to WDATA register in IT mode.
   - HAL_CORDIC_Read_IT() : Read data from RDATA register in IT mode.
   - HAL_CORDIC_Calculate_IT() : Perform a write and read operations in IT mode.

- Non-blocking mode functions with DMA are:
  - HAL_CORDIC_Write_DMA() : Write data to WDATA register in DMA mode.
  - HAL_CORDIC_Write_DMA_opt() : Write data to WDATA register in DMA mode and optional interrupt.
  - HAL_CORDIC_Read_DMA() : Read data from RDATA register in DMA mode.
  - HAL_CORDIC_Read_DMA_opt() : Read data from RDATA register in DMA mode and optional interrupt.
  - HAL_CORDIC_Calculate_DMA() : Perform a write and read operations in DMA mode.

Take note that some functions must require one or two arguments for the considered function of the calculation.
The list hereafter summarizes the number of arguments needed by each function of the CORDIC IP driver.
  -  Cosine                 2 arguments
  -  Sine                   2 arguments
  -  Phase                  2 arguments
  -  Modulus                2 arguments
  -  Arctangent             1 argument
  -  Hyperbolic cosine      1 argument
  -  Hyperbolic sine        1 argument
  -  Hyperbolic arctangent  1 argument
  -  natural logarithm      1 argument
  -  Square root            1 argument

Keep in mind that invoking one function requiring two arguments and setting only one argument can generate
erroneous results. To prevent that case, the unused argument has to be set at default value +1 (0x7FFFFFFF).

Don't forget that some functions must require a scaling factor to produce correct results. Please refer to the
reference manual to configure correctly the required parameters for the considered functions.
 */

/**
  * @brief  Write data to CORDIC_WDATA register providing an input buffer (polling mode).
  * @param  hcordic   Pointer to a hal_cordic_handle_t.
  * @param  p_buff_in Pointer to buffer descriptor containing pointer the input data buffer and the buffer size.
  * @param  timeout_ms   Specify timeout value in milliseconds.
  * @warning That function provides a buffer input to the CORDIC with a DMA Out or IT Out only. That function cannot be
  * used with the counterpart HAL_CORDIC_Read().
  * @retval HAL_OK       Operation completed successfully.
  * @retval HAL_TIMEOUT  Operation cancelled due to timeout.
  * @retval HAL_INVALID_PARAM   Invalid parameter.
  * @retval HAL_BUSY     Concurrent process ongoing.
  */
hal_status_t HAL_CORDIC_Write(hal_cordic_handle_t *hcordic, const hal_cordic_buffer_desc_t *p_buff_in,
                              uint32_t timeout_ms)
{
  const int32_t *p_tmp_in_buff;
  const CORDIC_TypeDef *p_cordic;
  uint32_t csr_reg;
  uint32_t nb_calculus;
  uint32_t index;
  uint32_t tickstart;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM((p_buff_in != NULL));
  ASSERT_DBG_PARAM((p_buff_in->p_data != NULL));
  ASSERT_DBG_PARAM((p_buff_in->size_word > 0UL));

  /* Check handle state is IDLE */
  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check input parameters */
  if ((p_buff_in == NULL) || (p_buff_in->p_data == NULL) || (p_buff_in->size_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Change the CORDIC state */
  HAL_CHECK_UPDATE_STATE(hcordic, global_state, HAL_CORDIC_STATE_IDLE, HAL_CORDIC_STATE_ACTIVE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  /* read the CSR register */
  csr_reg = LL_CORDIC_READ_REG((p_cordic), CSR);

  /* Calculate the number of calculus vs the buffer size and the number of arguments */
  nb_calculus = CORDIC_ValidateWriteNumber(csr_reg, p_buff_in);

  p_tmp_in_buff = p_buff_in->p_data;

#if defined(USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
  /* Reset CORDIC error code */
  hcordic->last_error_codes = HAL_CORDIC_ERROR_NONE;
#endif  /* USE_HAL_CORDIC_GET_LAST_ERRORS */

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Write of input data in Write Data register, and increment input buffer pointer */
  CORDIC_WriteDataAndIncPtr(hcordic, &p_tmp_in_buff);

  /* Calculation is started. Provide next set of input data, until number of calculation is achieved */
  for (index = (nb_calculus - 1U); index > 0U; index--)
  {
    /* Write of input data in Write Data register, and increment input buffer pointer */
    CORDIC_WriteDataAndIncPtr(hcordic, &p_tmp_in_buff);

    /* Start user watchdog */
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if ((HAL_GetTick() - tickstart) > timeout_ms)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Read data from CORDIC_RDATA register in polling mode.
  * @param  hcordic    Pointer to a hal_cordic_handle_t.
  * @param  p_buff_out Pointer to buffer descriptor containing pointer the output data buffer and the buffer size.
  * @param  timeout_ms      Specify timeout value in milliseconds.
  * @warning That function provides a buffer output to the CORDIC with HAL_CORDIC_Write_IT(), HAL_CORDIC_Write_DMA()
  * and HAL_CORDIC_Write_DMA_opt() functions only. That function cannot be used with the counterpart HAL_CORDIC_Write()
  * in polling mode.
  * @retval HAL_OK          Operation completed successfully.
  * @retval HAL_TIMEOUT     Operation cancelled due to timeout.
  * @retval HAL_INVALID_PARAM   Invalid parameter.
  */
hal_status_t HAL_CORDIC_Read(hal_cordic_handle_t *hcordic, hal_cordic_buffer_desc_t *p_buff_out, uint32_t timeout_ms)
{
  CORDIC_TypeDef *p_cordic;
  uint32_t tickstart;
  uint32_t index;
  int32_t *p_tmp_out_buff;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM((p_buff_out != NULL));
  ASSERT_DBG_PARAM((p_buff_out->p_data != NULL));
  ASSERT_DBG_PARAM((p_buff_out->size_word > 0UL));

  /* Check handle state is IDLE */
  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_ACTIVE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Test that none pointer is NULL */
  if ((p_buff_out == NULL) || (p_buff_out->p_data == NULL) || (p_buff_out->size_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  p_tmp_out_buff = p_buff_out->p_data;

#if defined(USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
  /* Reset CORDIC error code */
  hcordic->last_error_codes = HAL_CORDIC_ERROR_NONE;
#endif  /* USE_HAL_CORDIC_GET_LAST_ERRORS */

  /* Get tick */
  tickstart = HAL_GetTick();

  for (index = (p_buff_out->size_word - 1U); index > 0U; index--)
  {
    /* Wait for RRDY flag to be raised */
    do
    {
      /* Check for the timeout */
      if (timeout_ms != HAL_MAX_DELAY)
      {
        if ((HAL_GetTick() - tickstart) > timeout_ms)
        {
          /* Return function status */
          return HAL_TIMEOUT;
        }
      }
    } while (LL_CORDIC_IsActiveFlag_RRDY(p_cordic) == CORDIC_FLAG_NOT_ACTIVE);

    /* Read output data from Read Data register, and increment output buffer pointer */
    CORDIC_ReadDataAndIncPtr(hcordic, &p_tmp_out_buff);
  }

  /* Read output data from Read Data register, and increment output buffer pointer */
  CORDIC_ReadDataAndIncPtr(hcordic, &p_tmp_out_buff);

  /* Change the CORDIC state */
  hcordic->global_state = HAL_CORDIC_STATE_IDLE;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Perform CORDIC processing in polling mode,
  *         according to the existing CORDIC configuration.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @param  p_buff_in  Pointer to buffer descriptor containing pointer the input data buffer and the buffer size.
  * @param  p_buff_out Pointer to buffer descriptor containing pointer the output data buffer and the buffer size.
  * @param  timeout_ms  Specify timeout value in milliseconds.
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_TIMEOUT Operation cancelled due to timeout.
  * @retval HAL_BUSY     Concurrent process ongoing.
  * @retval HAL_INVALID_PARAM   Invalid parameter.
  */
hal_status_t HAL_CORDIC_Calculate(hal_cordic_handle_t *hcordic, const hal_cordic_buffer_desc_t *p_buff_in,
                                  hal_cordic_buffer_desc_t *p_buff_out, uint32_t timeout_ms)
{
  CORDIC_TypeDef *p_cordic;
  uint32_t csr_reg;
  uint32_t nb_write;
  uint32_t tickstart;
  uint32_t index;
  const int32_t *p_tmp_in_buff;
  int32_t *p_tmp_out_buff;

  /* Check the parameters */
  ASSERT_DBG_PARAM(hcordic != NULL);
  ASSERT_DBG_PARAM(p_buff_in != NULL);
  ASSERT_DBG_PARAM(p_buff_out != NULL);
  ASSERT_DBG_PARAM(p_buff_in->p_data != NULL);
  ASSERT_DBG_PARAM(p_buff_out->p_data != NULL);
  ASSERT_DBG_PARAM(p_buff_in->size_word > 0UL);
  ASSERT_DBG_PARAM(p_buff_out->size_word > 0UL);

  /* Check handle state is IDLE */
  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check input parameters */
  if ((p_buff_in == NULL) || (p_buff_out == NULL)
      || (p_buff_in->p_data == NULL) || (p_buff_out->p_data == NULL)
      || (p_buff_in->size_word == 0UL) || (p_buff_out->size_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Change the CORDIC state */
  HAL_CHECK_UPDATE_STATE(hcordic, global_state, HAL_CORDIC_STATE_IDLE, HAL_CORDIC_STATE_ACTIVE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  /* read the CSR register */
  csr_reg = LL_CORDIC_READ_REG((p_cordic), CSR);
  nb_write = CORDIC_ValidateWriteNumber(csr_reg, p_buff_in);

#if defined(USE_ASSERT_DBG_PARAM)
  uint32_t nb_read = CORDIC_ValidateReadNumber(csr_reg, p_buff_out);
#endif /* USE_ASSERT_DBG_PARAM */

  /* Check that the nunmber of write is lower than the number of read. */
  ASSERT_DBG_PARAM((nb_write <= nb_read));

  p_tmp_in_buff = p_buff_in->p_data;
  p_tmp_out_buff = p_buff_out->p_data;

#if defined(USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
  /* Reset CORDIC error code */
  hcordic->last_error_codes = HAL_CORDIC_ERROR_NONE;
#endif  /* USE_HAL_CORDIC_GET_LAST_ERRORS */

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Write of input data in Write Data register, and increment input buffer pointer */
  CORDIC_WriteDataAndIncPtr(hcordic, &p_tmp_in_buff);

  /* Calculation is started.
     Provide next set of input data, until number of calculation is achieved */

  for (index = (nb_write - 1U); index > 0U; index--)
  {
    /* Write of input data in Write Data register, and increment input buffer pointer */
    CORDIC_WriteDataAndIncPtr(hcordic, &p_tmp_in_buff);

    /* Wait for RRDY flag to be raised */
    do
    {
      /* Check for the timeout */
      if (timeout_ms != HAL_MAX_DELAY)
      {
        if ((HAL_GetTick() - tickstart) > timeout_ms)
        {
          /* Change the CORDIC state */
          hcordic->global_state = HAL_CORDIC_STATE_IDLE;

          /* Return function status */
          return HAL_TIMEOUT;
        }
      }
    } while (LL_CORDIC_IsActiveFlag_RRDY(p_cordic) == CORDIC_FLAG_NOT_ACTIVE);
    /* Read output data from Read Data register, and increment output buffer pointer */
    CORDIC_ReadDataAndIncPtr(hcordic, &p_tmp_out_buff);
  }

  /* Read output data from Read Data register, and increment output buffer pointer */
  CORDIC_ReadDataAndIncPtr(hcordic, &p_tmp_out_buff);

  /* Change the CORDIC state */
  hcordic->global_state = HAL_CORDIC_STATE_IDLE;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Perform CORDIC processing in Zero-Overhead mode (output data being read
  *         soon as input data are written), according to the existing CORDIC configuration.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @param  p_buff_in  Pointer to buffer descriptor containing pointer the input data buffer and the buffer size.
  * @param  p_buff_out Pointer to buffer descriptor containing pointer the output data buffer and the buffer size.
  * @param  timeout_ms  Specify timeout value in milliseconds.
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_TIMEOUT Operation cancelled due to timeout.
  * @retval HAL_BUSY     Concurrent process ongoing.
  */
hal_status_t HAL_CORDIC_CalculateZeroOverhead(hal_cordic_handle_t *hcordic,
                                              const hal_cordic_buffer_desc_t *p_buff_in,
                                              hal_cordic_buffer_desc_t *p_buff_out, uint32_t timeout_ms)
{
  const CORDIC_TypeDef *p_cordic;
  const int32_t *p_tmp_in_buff;
  int32_t *p_tmp_out_buff;
  uint32_t csr_reg;
  uint32_t nb_write;
  uint32_t tickstart;
  uint32_t index;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM((p_buff_in != NULL));
  ASSERT_DBG_PARAM((p_buff_out != NULL));
  ASSERT_DBG_PARAM(p_buff_in->p_data != NULL);
  ASSERT_DBG_PARAM(p_buff_out->p_data != NULL);
  ASSERT_DBG_PARAM(p_buff_in->size_word > 0UL);
  ASSERT_DBG_PARAM(p_buff_out->size_word > 0UL);

  /* Check handle state is IDLE */
  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_buff_in == NULL) || (p_buff_out == NULL)
      || (p_buff_in->p_data == NULL) || (p_buff_out->p_data == NULL)
      || (p_buff_in->size_word  == 0UL) || (p_buff_out->size_word  == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Change the CORDIC state */
  HAL_CHECK_UPDATE_STATE(hcordic, global_state, HAL_CORDIC_STATE_IDLE, HAL_CORDIC_STATE_ACTIVE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  csr_reg  = LL_CORDIC_READ_REG((p_cordic), CSR);
  nb_write = CORDIC_ValidateWriteNumber(csr_reg, p_buff_in);

#if defined(USE_ASSERT_DBG_PARAM)
  uint32_t nb_read = CORDIC_ValidateReadNumber(csr_reg, p_buff_out);
#endif /* USE_ASSERT_DBG_PARAM */

  /* Check that the nunmber of write is lower than the number of read. */
  ASSERT_DBG_PARAM((nb_write <= nb_read));

  p_tmp_in_buff  = p_buff_in->p_data;
  p_tmp_out_buff = p_buff_out->p_data;

#if defined(USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
  /* Reset CORDIC error code */
  hcordic->last_error_codes = HAL_CORDIC_ERROR_NONE;
#endif  /* USE_HAL_CORDIC_GET_LAST_ERRORS */

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Write of input data in Write Data register, and increment input buffer pointer */
  CORDIC_WriteDataAndIncPtr(hcordic, &p_tmp_in_buff);

  /* Calculation is started. Provide next set of input data, until number of calculation is achieved */
  for (index = (nb_write - 1U); index > 0U; index--)
  {
    /* Write of input data in Write Data register, and increment input buffer pointer */
    CORDIC_WriteDataAndIncPtr(hcordic, &p_tmp_in_buff);

    /* Read output data from Read Data register, and increment output buffer pointer
       Reading is performed in Zero-Overhead mode: No Result Ready flag, only bus wait insertion. */
    CORDIC_ReadDataAndIncPtr(hcordic, &p_tmp_out_buff);

    /* Check for the timeout */
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if ((HAL_GetTick() - tickstart) > timeout_ms)
      {
        /* Change the CORDIC state */
        hcordic->global_state = HAL_CORDIC_STATE_IDLE;
        /* Return function status */
        return HAL_TIMEOUT;
      }
    }
  }

  /* Read output data from Read Data register, and increment output buffer pointer.
     The reading is performed in Zero-Overhead mode, reading is done immediately without waiting result ready flag */
  CORDIC_ReadDataAndIncPtr(hcordic, &p_tmp_out_buff);

  /* Change the CORDIC state */
  hcordic->global_state = HAL_CORDIC_STATE_IDLE;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Write arguments to CORDIC_WDATA in interrupt mode on result reading.
  * @param  hcordic       Pointer to a hal_cordic_handle_t.
  * @param  p_buff_in  Pointer to buffer descriptor containing pointer the input data buffer and the buffer size.
  * @warning   Because there is no IT on the writing operation, that process concerning the data writing is identical
  * to the polling or IT and scheduled by the data reading based on RDDY flag raising.
  * @retval HAL_OK       Operation completed successfully
  * @retval HAL_ERROR    Operation completed with error
  * @retval HAL_BUSY     Concurrent process ongoing.
  * @retval HAL_INVALID_PARAM Invalid parameter
  */
hal_status_t HAL_CORDIC_Write_IT(hal_cordic_handle_t *hcordic, const hal_cordic_buffer_desc_t *p_buff_in)
{
  CORDIC_TypeDef *p_cordic;
  const int32_t *tmp_pInBuff;

  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM((p_buff_in != NULL));
  ASSERT_DBG_PARAM((p_buff_in->p_data != NULL));
  ASSERT_DBG_PARAM((p_buff_in->size_word > 0UL));

  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_buff_in == NULL) || (p_buff_in->p_data == NULL) || (p_buff_in->size_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Change the CORDIC state */
  HAL_CHECK_UPDATE_STATE(hcordic, global_state, HAL_CORDIC_STATE_IDLE, HAL_CORDIC_STATE_ACTIVE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);
  /* read the CSR register */
  uint32_t csr_reg = LL_CORDIC_READ_REG((p_cordic), CSR);
  /* Check that the input buffer size is at least correct. */
  uint32_t write_nb = CORDIC_ValidateWriteNumber(csr_reg, p_buff_in);
  ASSERT_DBG_PARAM((write_nb >= 1U));

  tmp_pInBuff = p_buff_in->p_data;

  /* Store the buffers addresses and number of calculations in handle, provisioning initial write
     of input data that will be done */
  if (LL_CORDIC_GetNbWrite(p_cordic) == (uint32_t)HAL_CORDIC_ARG_NB_2)
  {
    /* Two writes of input data are expected */
    tmp_pInBuff++;
    tmp_pInBuff++;
  }
  else
  {
    /* One write of input data is expected */
    tmp_pInBuff++;
  }
  hcordic->p_input_buffer  = tmp_pInBuff;
  hcordic->nb_calculus_to_do = write_nb - 1U;

  /* Enable Result Ready Interrupt */
  LL_CORDIC_EnableIT(p_cordic);

  /* Set back pointer to start of input data buffer */
  tmp_pInBuff = p_buff_in->p_data;

  /*write of input data in the Write Data register, and increment input buffer pointer */
  CORDIC_WriteDataAndIncPtr(hcordic, &tmp_pInBuff);

  return HAL_OK;
}

/**
  * @brief  Read  result from CORDIC_RDATA in interrupt mode.
  * @param  hcordic         Pointer to a hal_cordic_handle_t.
  * @param  p_buff_out   Pointer to buffer descriptor containing pointer the output data buffer and the buffer size.
  * @note   An interrupt is generated when RRDY flag is raised.
  * @retval HAL_OK       Operation completed successfully
  * @retval HAL_ERROR    Operation completed with error
  * @retval HAL_BUSY     Concurrent process ongoing.
  * @retval HAL_INVALID_PARAM Invalid parameter
  */
hal_status_t HAL_CORDIC_Read_IT(hal_cordic_handle_t *hcordic, hal_cordic_buffer_desc_t *p_buff_out)
{
  CORDIC_TypeDef *p_cordic;
  uint32_t csr_reg;
  uint32_t nb_read;

  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM((p_buff_out != NULL));
  ASSERT_DBG_PARAM((p_buff_out->p_data != NULL));
  ASSERT_DBG_PARAM((p_buff_out->size_word > 0UL));

  /* Check the current state */
  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_buff_out == NULL) || (p_buff_out->p_data == NULL) || (p_buff_out->size_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);
  /* read the CSR register */
  csr_reg = LL_CORDIC_READ_REG((p_cordic), CSR);
  /* Get the number of read vs the resiults parameters */
  nb_read  = CORDIC_ValidateReadNumber(csr_reg, p_buff_out);

  /* Store output data location */
  hcordic->p_output_buffer    = p_buff_out->p_data;
  hcordic->nb_calculus_to_get = nb_read;

  /* Enable interrupt */
  LL_CORDIC_EnableIT(p_cordic);

  return HAL_OK;
}

/**
  * @brief  Perform CORDIC processing in interrupt mode, according to the existing CORDIC configuration.
  * @param  hcordic       Pointer to a hal_cordic_handle_t.
  * @param  p_buff_in  Pointer to buffer descriptor containing pointer the input data buffer and the buffer size.
  * @param  p_buff_out Pointer to buffer descriptor containing pointer the output data buffer and the buffer size.
  * @retval HAL_OK  Operation completed successfully.
  * @retval HAL_BUSY     Concurrent process ongoing.
  */
hal_status_t HAL_CORDIC_Calculate_IT(hal_cordic_handle_t *hcordic, const hal_cordic_buffer_desc_t *p_buff_in,
                                     hal_cordic_buffer_desc_t *p_buff_out)
{
  CORDIC_TypeDef *p_cordic;
  const int32_t *tmp_pInBuff;
  uint32_t csr_reg;
  uint32_t nb_write;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM((p_buff_in != NULL));
  ASSERT_DBG_PARAM((p_buff_out != NULL));
  ASSERT_DBG_PARAM(p_buff_in->p_data != NULL);
  ASSERT_DBG_PARAM(p_buff_out->p_data != NULL);
  ASSERT_DBG_PARAM(p_buff_in->size_word > 0UL);
  ASSERT_DBG_PARAM(p_buff_out->size_word > 0UL);

  /* Check handle state is IDLE */
  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_buff_in == NULL) || (p_buff_out == NULL)
      || (p_buff_in->p_data == NULL) || (p_buff_out->p_data == NULL)
      || (p_buff_in->size_word == 0UL) || (p_buff_out->size_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Change the CORDIC state */
  HAL_CHECK_UPDATE_STATE(hcordic, global_state, HAL_CORDIC_STATE_IDLE, HAL_CORDIC_STATE_ACTIVE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  /* read the CSR register */
  csr_reg  = LL_CORDIC_READ_REG((p_cordic), CSR);
  nb_write = CORDIC_ValidateWriteNumber(csr_reg, p_buff_in);

#if defined(USE_ASSERT_DBG_PARAM)
  uint32_t nb_read  = CORDIC_ValidateReadNumber(csr_reg, p_buff_out);
#endif /* USE_ASSERT_DBG_PARAM */

  /* Check that the input buffer size is at least correct vs the number of calculus. */
  ASSERT_DBG_PARAM((nb_write <= nb_read));

  tmp_pInBuff = p_buff_in->p_data;

#if defined(USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
  /* Reset CORDIC error code */
  hcordic->last_error_codes = HAL_CORDIC_ERROR_NONE;
#endif  /* USE_HAL_CORDIC_GET_LAST_ERRORS */

  /* Store the buffers addresses and number of calculations in handle, provisioning initial write
     of input data that will be done */
  if (LL_CORDIC_GetNbWrite(p_cordic) == (uint32_t)HAL_CORDIC_ARG_NB_2)
  {
    /* Two writes of input data are expected */
    tmp_pInBuff++;
    tmp_pInBuff++;
  }
  else
  {
    /* One write of input data is expected */
    tmp_pInBuff++;
  }
  hcordic->p_input_buffer     = tmp_pInBuff;
  hcordic->p_output_buffer    = p_buff_out->p_data;
  hcordic->nb_calculus_to_do  = nb_write - 1U;
  hcordic->nb_calculus_to_get = nb_write;

  /* Enable Result Ready Interrupt */
  LL_CORDIC_EnableIT(p_cordic);

  /* Set back pointer to start of input data buffer */
  tmp_pInBuff = p_buff_in->p_data;

  /*write of input data in the Write Data register, and increment input buffer pointer */
  CORDIC_WriteDataAndIncPtr(hcordic, &tmp_pInBuff);

  /* Return function status */
  return HAL_OK;
}

#if defined(USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)

/**
  * @brief  Write arguments to CORDIC_WDATA in DMA mode.
  * @param  hcordic      Pointer to a hal_cordic_handle_t
  * @param  p_buff_in Pointer to buffer descriptor containing pointer the input data buffer and the buffer size.
  * @retval HAL_OK            Operation completed successfully
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_INVALID_PARAM Invalid parameter
  */
hal_status_t HAL_CORDIC_Write_DMA(hal_cordic_handle_t *hcordic, const hal_cordic_buffer_desc_t *p_buff_in)
{
  hal_status_t status;
  CORDIC_TypeDef *p_cordic;
  uint32_t size_input_buffer;
  uint32_t csr_reg;
  uint32_t nb_write;

  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM((p_buff_in != NULL));
  ASSERT_DBG_PARAM(p_buff_in->p_data != NULL);
  ASSERT_DBG_PARAM(p_buff_in->size_word > 0UL);
  ASSERT_DBG_PARAM((hcordic->p_dma_in != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_buff_in == NULL) || (p_buff_in->p_data == NULL)
      || (p_buff_in->size_word == 0UL) || (hcordic->p_dma_in == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Change the CORDIC state */
  HAL_CHECK_UPDATE_STATE(hcordic, global_state, HAL_CORDIC_STATE_IDLE, HAL_CORDIC_STATE_ACTIVE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  /* read the CSR register */
  csr_reg = LL_CORDIC_READ_REG((p_cordic), CSR);
  /* get the number of calculus vs the CORDIC arguments configuration */
  nb_write = CORDIC_ValidateWriteNumber(csr_reg, p_buff_in);

  /* Check number of input data expected for each calculation, to retrieve the size of input data buffer */
  size_input_buffer = ((LL_CORDIC_GetNbWrite(p_cordic) == (uint32_t)(HAL_CORDIC_ARG_NB_2))
                       ? (2U * nb_write) : nb_write);

  /* Prepare DMA write xfer */
  hcordic->p_dma_in->p_xfer_cplt_cb        = CORDIC_DMAInCplt;     /* Set the CORDIC DMA transfer complete callback */
  hcordic->p_dma_in->p_xfer_halfcplt_cb    = CORDIC_DMAInHalfCplt; /* Set the CORDIC DMA transfer half complete cb  */
  hcordic->p_dma_in->p_xfer_error_cb       = CORDIC_DMAError;      /* Set the DMA error callback */

  /* Convert the input buffer size into corresponding number of bytes as DMA handles data at byte-level. */
  size_input_buffer = 4U * size_input_buffer;

  status = HAL_DMA_StartPeriphXfer_IT_Opt(hcordic->p_dma_in, (uint32_t)p_buff_in->p_data, (uint32_t)&p_cordic->WDATA,
                                          size_input_buffer, HAL_DMA_OPT_IT_NONE);

  if (status == HAL_OK)
  {
    /* Enable DMA Write request*/
    LL_CORDIC_EnableDMAReq_WR(p_cordic);
  }
  else
  {
    hcordic->global_state = HAL_CORDIC_STATE_IDLE;
  }

  return status;
}

/**
  * @brief  Write data to WDATA in DMA mode with option. Global state must be IDLE.
  * @param  hcordic       Pointer to a hal_cordic_handle_t
  * @param  p_buff_in  Pointer to input data descriptor: pointer to data and input size in word.
  * @param  opt_it        Optional interruption can be a combination of
  *                          @ref HAL_CORDIC_OPT_DMA_NONE
  *                          @ref HAL_CORDIC_OPT_DMA_IT_HALF_CPLT
  *                          @ref HAL_CORDIC_OPT_DMA_ALL
  * @retval HAL_OK        Operation completed successfully
  * @retval HAL_ERROR     Operation completed with error
  * @retval HAL_BUSY      Concurrent process ongoing.
  * @retval HAL_INVALID_PARAM Invalid parameter
  */
hal_status_t HAL_CORDIC_Write_DMA_opt(hal_cordic_handle_t *hcordic, const hal_cordic_buffer_desc_t *p_buff_in,
                                      uint32_t opt_it)
{
  hal_status_t status;
  CORDIC_TypeDef *p_cordic;
  uint32_t size_input_buffer;
  uint32_t it;
  uint32_t csr_reg;
  uint32_t nb_write;

  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM((p_buff_in != NULL));
  ASSERT_DBG_PARAM(p_buff_in->p_data != NULL);
  ASSERT_DBG_PARAM(p_buff_in->size_word > 0UL);
  ASSERT_DBG_PARAM((hcordic->p_dma_in != NULL));
  ASSERT_DBG_PARAM((IS_CORDIC_OPT_DMA_IT_WR(opt_it)));

  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_buff_in == NULL) || (p_buff_in->p_data == NULL)
      || (p_buff_in->size_word == 0UL) || (opt_it > HAL_CORDIC_OPT_DMA_ALL) || (hcordic->p_dma_in == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Change the CORDIC state */
  HAL_CHECK_UPDATE_STATE(hcordic, global_state, HAL_CORDIC_STATE_IDLE, HAL_CORDIC_STATE_ACTIVE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  /* read the CSR register */
  csr_reg = LL_CORDIC_READ_REG((p_cordic), CSR);
  /* Get the number of calculus vs the CORDIC arguments parameters */
  nb_write = CORDIC_ValidateWriteNumber(csr_reg, p_buff_in);

  /* Check number of input data expected for each calculation, to retrieve the size of input data buffer */
  size_input_buffer = ((LL_CORDIC_GetNbWrite(p_cordic) == (uint32_t)(HAL_CORDIC_ARG_NB_2))
                       ? (2U * nb_write) : nb_write);

  /* Prepare DMA write xfer */
  hcordic->p_dma_in->p_xfer_cplt_cb        = CORDIC_DMAInCplt;     /* Set the CORDIC DMA transfer complete callback */
  hcordic->p_dma_in->p_xfer_halfcplt_cb    = CORDIC_DMAInHalfCplt; /* Set the CORDIC DMA transfer half complete cb  */
  hcordic->p_dma_in->p_xfer_error_cb       = CORDIC_DMAError;      /* Set the DMA error callback                    */

  /* Convert the input buffer size into corresponding number of bytes as DMA handles data at byte-level. */
  size_input_buffer = 4U * size_input_buffer;

  if ((opt_it & HAL_CORDIC_OPT_DMA_IT_HALF_CPLT) != 0UL)
  {
    it = HAL_DMA_OPT_IT_HT;
  }
  else
  {
    it = HAL_DMA_OPT_IT_DEFAULT;
  }

  status = HAL_DMA_StartPeriphXfer_IT_Opt(hcordic->p_dma_in, (uint32_t)p_buff_in->p_data,
                                          (uint32_t)&p_cordic->WDATA, size_input_buffer, it);
  if (status == HAL_OK)
  {
    /* Enable DMA Write request*/
    LL_CORDIC_EnableDMAReq_WR(p_cordic);
  }
  else
  {
    hcordic->global_state = HAL_CORDIC_STATE_IDLE;
  }

  return status;
}

/**
  * @brief  Read result from CORDIC_RDATA in DMA mode.
  * @param  hcordic       Pointer to a hal_cordic_handle_t
  * @param  p_buff_out Pointer to buffer descriptor containing pointer the output data buffer and the buffer size.
  * @retval HAL_OK            Operation completed successfully
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_INVALID_PARAM Invalid parameter
  */
hal_status_t HAL_CORDIC_Read_DMA(hal_cordic_handle_t *hcordic, hal_cordic_buffer_desc_t *p_buff_out)
{
  hal_status_t status;
  CORDIC_TypeDef *p_cordic;
  uint32_t size_output_buffer;
  uint32_t csr_reg;
  uint32_t nb_read;

  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM((p_buff_out != NULL));
  ASSERT_DBG_PARAM(p_buff_out->p_data != NULL);
  ASSERT_DBG_PARAM(p_buff_out->size_word > 0UL);
  ASSERT_DBG_PARAM((hcordic->p_dma_out != NULL));


  /* Check the current global state */
  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_buff_out == NULL) || (p_buff_out->p_data == NULL)
      || (p_buff_out->size_word == 0UL) || (hcordic->p_dma_out == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  /* Read the CSR register */
  csr_reg = LL_CORDIC_READ_REG((p_cordic), CSR);
  /* Compute the number of results vs the CORDIC parameters */
  nb_read = CORDIC_ValidateReadNumber(csr_reg, p_buff_out);

  /* Check number of input data expected for each calculation, to retrieve the size of input data buffer */
  size_output_buffer = ((LL_CORDIC_GetNbRead(p_cordic) == (uint32_t)(HAL_CORDIC_RESULT_NB_2))
                        ? (2UL * nb_read) : nb_read);

  /* Prepare DMA read xfer */
  hcordic->p_dma_out->p_xfer_cplt_cb       = CORDIC_DMAOutCplt;    /* Set the CORDIC DMA transfer complete callback */
  hcordic->p_dma_out->p_xfer_halfcplt_cb   = CORDIC_DMAOutHalfCplt;/* Set the CORDIC DMA transfer half complete cb  */
  hcordic->p_dma_out->p_xfer_error_cb      = CORDIC_DMAError;      /* Set the DMA error callback */

  /* Convert the output buffer size into corresponding number of bytes as DMA handles data at byte-level. */
  size_output_buffer = 4U * size_output_buffer;

  status = HAL_DMA_StartPeriphXfer_IT_Opt(hcordic->p_dma_out, (uint32_t) &(p_cordic->RDATA),
                                          (uint32_t)p_buff_out->p_data, size_output_buffer, HAL_DMA_OPT_IT_NONE);
  if (status == HAL_OK)
  {
    /* Enable DMA Read request*/
    LL_CORDIC_EnableDMAReq_RD(p_cordic);
  }

  return status;
}

/**
  * @brief  Read data from RDATA in DMA mode. Global state must be IDLE.
  * @param  hcordic      Pointer to a hal_cordic_handle_t
  * @param  p_buff_out    Pointer to output data descriptor: pointer to data and output size in word.
  * @param  opt_it       Optional interruption can be a combination of
  *                          @ref HAL_CORDIC_OPT_DMA_NONE
  *                          @ref HAL_CORDIC_OPT_DMA_IT_HALF_CPLT
  *                          @ref HAL_CORDIC_OPT_DMA_ALL
  * @retval HAL_OK        Operation completed successfully
  * @retval HAL_ERROR     Operation completed with error
  * @retval HAL_BUSY      Concurrent process ongoing
  * @retval HAL_INVALID_PARAM Invalid parameter
  */
hal_status_t HAL_CORDIC_Read_DMA_opt(hal_cordic_handle_t *hcordic, hal_cordic_buffer_desc_t *p_buff_out,
                                     uint32_t opt_it)
{
  hal_status_t status;
  CORDIC_TypeDef *p_cordic;
  uint32_t size_output_buffer;
  uint32_t it;
  uint32_t csr_reg;
  uint32_t nb_read;

  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM((p_buff_out != NULL));
  ASSERT_DBG_PARAM(p_buff_out->p_data != NULL);
  ASSERT_DBG_PARAM(p_buff_out->size_word > 0UL);
  ASSERT_DBG_PARAM((hcordic->p_dma_out != NULL));
  ASSERT_DBG_PARAM((IS_CORDIC_OPT_DMA_IT_RD(opt_it)));

  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_buff_out == NULL) || (p_buff_out->p_data == NULL)
      || (p_buff_out->size_word == 0UL) || (opt_it > HAL_CORDIC_OPT_DMA_ALL) || (hcordic->p_dma_out == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);
  /* Read the CSR register */
  csr_reg = LL_CORDIC_READ_REG((p_cordic), CSR);
  /* Compute the number of results vs the CORDIC parameters */
  nb_read = CORDIC_ValidateReadNumber(csr_reg, p_buff_out);

  /* Check number of input data expected for each calculation, to retrieve the size of input data buffer */
  size_output_buffer = ((LL_CORDIC_GetNbRead(p_cordic) == (uint32_t)(HAL_CORDIC_RESULT_NB_2))
                        ? (2U * nb_read) : nb_read);

  /* Prepare DMA write xfer */
  hcordic->p_dma_out->p_xfer_cplt_cb        = CORDIC_DMAOutCplt;     /* Set the CORDIC DMA transfer complete callback */
  hcordic->p_dma_out->p_xfer_halfcplt_cb    = CORDIC_DMAOutHalfCplt; /* Set the CORDIC DMA transfer half complete cb  */
  hcordic->p_dma_out->p_xfer_error_cb       = CORDIC_DMAError;       /* Set the DMA error callback                    */

  if ((opt_it & HAL_CORDIC_OPT_DMA_IT_HALF_CPLT) != 0UL)
  {
    it = HAL_DMA_OPT_IT_HT;
  }
  else
  {
    it = HAL_DMA_OPT_IT_DEFAULT;
  }

  /* Convert the input buffer size into corresponding number of bytes as DMA handles data at byte-level. */
  size_output_buffer = 4U * size_output_buffer;

  status = HAL_DMA_StartPeriphXfer_IT_Opt(hcordic->p_dma_out, (uint32_t) &(p_cordic->RDATA),
                                          (uint32_t)p_buff_out->p_data, size_output_buffer, it);

  if (status == HAL_OK)
  {
    /* Enable DMA Read request*/
    LL_CORDIC_EnableDMAReq_RD(p_cordic);
  }

  return status;
}

/**
  * @brief  Perform  input data and output data of CORDIC processing in DMA mode according to the
  *         existing CORDIC configuration.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @param  p_buff_in  Pointer to buffer descriptor containing pointer the input data buffer and the buffer size.
  * @param  p_buff_out Pointer to buffer descriptor containing pointer the output data buffer and the buffer size.
  * @note   p_buff_in and output_buffer buffers must be 32-bit aligned to ensure a correct DMA transfer to and from
  *         the Peripheral. The function requires to configure the 2 DMA channels (Input and Output).
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         Operation error.
  * @retval HAL_BUSY     Concurrent process ongoing.
  */
hal_status_t HAL_CORDIC_Calculate_DMA(hal_cordic_handle_t *hcordic, const hal_cordic_buffer_desc_t *p_buff_in,
                                      hal_cordic_buffer_desc_t *p_buff_out)
{
  CORDIC_TypeDef *p_cordic;
  uint32_t csr_reg;
  uint32_t nb_write;
  uint32_t size_output_buffer;
  uint32_t size_input_buffer;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));
  ASSERT_DBG_PARAM((p_buff_out != NULL));
  ASSERT_DBG_PARAM((p_buff_in != NULL));
  ASSERT_DBG_PARAM(p_buff_in->p_data != NULL);
  ASSERT_DBG_PARAM(p_buff_in->size_word > 0UL);
  ASSERT_DBG_PARAM(p_buff_out->p_data != NULL);
  ASSERT_DBG_PARAM(p_buff_out->size_word > 0UL);
  ASSERT_DBG_PARAM((hcordic->p_dma_in != NULL));
  ASSERT_DBG_PARAM((hcordic->p_dma_out != NULL));

  /* Check handle state is IDLE */
  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check input parameters */
  if ((p_buff_in == NULL) || (p_buff_out == NULL))
  {
    return HAL_INVALID_PARAM;
  }
  /* Check input parameters */
  if ((hcordic->p_dma_out == NULL) || (hcordic->p_dma_in == NULL))
  {
    return HAL_INVALID_PARAM;
  }
  /* Check input parameters */
  if ((p_buff_in->p_data == NULL) || (p_buff_out->p_data == NULL)
      || (p_buff_in->size_word == 0UL) || (p_buff_out->size_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Change the CORDIC state */
  HAL_CHECK_UPDATE_STATE(hcordic, global_state, HAL_CORDIC_STATE_IDLE, HAL_CORDIC_STATE_ACTIVE);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);
  /* read the CSR register */
  csr_reg = LL_CORDIC_READ_REG((p_cordic), CSR);
  nb_write = CORDIC_ValidateWriteNumber(csr_reg, p_buff_in);

#if defined(USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
  /* Reset CORDIC error code */
  hcordic->last_error_codes = HAL_CORDIC_ERROR_NONE;
#endif  /* USE_HAL_CORDIC_GET_LAST_ERRORS */

  /* Prepare DMA read xfer */
  hcordic->p_dma_out->p_xfer_cplt_cb       = CORDIC_DMAOutCplt;    /* Set the CORDIC DMA transfer complete callback */
  hcordic->p_dma_out->p_xfer_halfcplt_cb   = CORDIC_DMAOutHalfCplt;/* Set the CORDIC DMA transfer half complete cb  */
  hcordic->p_dma_out->p_xfer_error_cb      = CORDIC_DMAError;      /* Set the DMA error callback */

  if (LL_CORDIC_GetNbRead(p_cordic) == (uint32_t)(HAL_CORDIC_RESULT_NB_2))
  {
    size_output_buffer = nb_write * 2U;
  }
  else
  {
    size_output_buffer = nb_write;
  }

  /* Convert the output buffer size into corresponding number of bytes as DMA handles data at byte-level. */
  size_output_buffer = 4U * size_output_buffer;

  /* Enable the DMA stream managing CORDIC output data read */
  if (HAL_DMA_StartPeriphXfer_IT_Opt(hcordic->p_dma_out, (uint32_t)&p_cordic->RDATA, (uint32_t)p_buff_out->p_data,
                                     size_output_buffer, HAL_DMA_OPT_IT_NONE) != HAL_OK)
  {
#if defined(USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
    hcordic->last_error_codes |= HAL_CORDIC_ERROR_DMA;
#endif /* USE_HAL_CORDIC_GET_LAST_ERRORS */
    hcordic->global_state = HAL_CORDIC_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Enable DMA Read request    */
  LL_CORDIC_EnableDMAReq_RD(p_cordic);

  /* Prepare DMA write xfer     */
  hcordic->p_dma_in->p_xfer_cplt_cb        = CORDIC_DMAInCplt;     /* Set the CORDIC DMA transfer complete callback */
  hcordic->p_dma_in->p_xfer_halfcplt_cb    = CORDIC_DMAInHalfCplt; /* Set the CORDIC DMA transfer half complete cb  */
  hcordic->p_dma_in->p_xfer_error_cb       = CORDIC_DMAError;      /* Set the DMA error callback */

  size_input_buffer = ((LL_CORDIC_GetNbWrite(p_cordic) == (uint32_t)(HAL_CORDIC_ARG_NB_2)) ?
                       (2U * nb_write) : nb_write);

  /* Convert the input buffer size into corresponding number of bytes as DMA handles data at byte-level. */
  size_input_buffer = 4U * size_input_buffer;

  /* Enable the DMA stream managing CORDIC input data write */
  if (HAL_DMA_StartPeriphXfer_IT_Opt(hcordic->p_dma_in, (uint32_t)p_buff_in->p_data, (uint32_t)&p_cordic->WDATA,
                                     size_input_buffer, HAL_DMA_OPT_IT_NONE) != HAL_OK)
  {
#if defined(USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
    /* Update the error code */
    hcordic->last_error_codes |= HAL_CORDIC_ERROR_DMA;
#endif /* USE_HAL_CORDIC_GET_LAST_ERRORS */
    /* Return error status */
    hcordic->global_state = HAL_CORDIC_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Enable DMA In request*/
  LL_CORDIC_EnableDMAReq_WR(p_cordic);

  /* Return function status */
  return HAL_OK;
}
#endif /* USE_HAL_CORDIC_DMA */

/**
  * @brief  Abort the ongoing transfer (blocking process).
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_ERROR   DMA abort error.
  */
hal_status_t HAL_CORDIC_Abort(hal_cordic_handle_t *hcordic)
{
  ASSERT_DBG_PARAM(hcordic != NULL);

  /* Check handle state is ACTIVE */
  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_ACTIVE);

  hcordic->global_state = HAL_CORDIC_STATE_ABORT;

  (void)CORDIC_Abort(hcordic);

  hcordic->global_state = HAL_CORDIC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Abort a CORDIC process (non-blocking process).
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @retval HAL_OK  Operation completed successfully.
  */
hal_status_t HAL_CORDIC_Abort_IT(hal_cordic_handle_t *hcordic)
{
  CORDIC_TypeDef *p_cordic;
  uint32_t abort_cplt;

  ASSERT_DBG_PARAM(hcordic != NULL);

  /* Check handle state is ACTIVE */
  ASSERT_DBG_STATE(hcordic->global_state, HAL_CORDIC_STATE_ACTIVE);

  hcordic->global_state = HAL_CORDIC_STATE_ABORT;

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  abort_cplt = 1U;

#if defined(USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
  /* Check if the DMA Read (output) is enabled */
  if (LL_CORDIC_IsEnabledDMAReq_RD(p_cordic) == 1U)
  {
    if (hcordic->p_dma_out->global_state == HAL_DMA_STATE_ACTIVE)
    {
      hcordic->p_dma_out->p_xfer_abort_cb = CORDIC_DMAAbort;
      if (HAL_DMA_Abort_IT(hcordic->p_dma_out) != HAL_OK)
      {
        hcordic->p_dma_out->p_xfer_abort_cb = NULL;
      }
      else
      {
        abort_cplt = 0U;
      }
    }
  }

  /* Check if the DMA Write (input) is enabled */
  if (LL_CORDIC_IsEnabledDMAReq_WR(p_cordic) == 1U)
  {
    if (hcordic->p_dma_in->global_state == HAL_DMA_STATE_ACTIVE)
    {
      hcordic->p_dma_in->p_xfer_abort_cb = CORDIC_DMAAbort;
      if (HAL_DMA_Abort_IT(hcordic->p_dma_in) != HAL_OK)
      {
        hcordic->p_dma_in->p_xfer_abort_cb = NULL;
      }
      else
      {
        abort_cplt = 0U;
      }
    }
  }
#endif /* USE_HAL_CORDIC_DMA */

  /* if no DMA abort complete callback execution is required => call user abort complete callback */
  if (abort_cplt == 1U)
  {
    /* Disable the Data Ready interrupt */
    LL_CORDIC_DisableIT(p_cordic);

    /* Reset the buffers and counters */
    hcordic->p_input_buffer  = NULL;
    hcordic->p_output_buffer = NULL;
    hcordic->nb_calculus_to_do  = 0UL;
    hcordic->nb_calculus_to_get = 0UL;

    hcordic->global_state = HAL_CORDIC_STATE_IDLE;

    /* As no DMA to be aborted, call directly user abort complete callback */
#if defined(USE_HAL_CORDIC_REGISTER_CALLBACKS) && (USE_HAL_CORDIC_REGISTER_CALLBACKS == 1)
    /* Call registered abort complete callback */
    hcordic->p_abort_cplt_cb(hcordic);
#else
    /* Call legacy weak abort complete callback */
    HAL_CORDIC_AbortCpltCallback(hcordic);
#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */

#if defined(USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
    hcordic->last_error_codes = HAL_CORDIC_ERROR_NONE;
#endif /* USE_HAL_CORDIC_GET_LAST_ERRORS */

  }

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup CORDIC_Exported_Functions_Group5
  * @{

This section provides functions allowing to:
- Handle the CORDIC interrupt request with HAL_CORDIC_IRQHandler().

There are two ways to use callbacks: override weak callback functions or register user callback functions.
They are used to indicate:
  - When all the calculus are done (HAL_CORDIC_CalculateCpltCallback() or callback function registered
    with HAL_CORDIC_RegisterCalculateCpltCallback()).
  - When half of all the calculus is read (HAL_CORDIC_ReadHalfCpltCallback() or callback function registered
    with HAL_CORDIC_RegisterReadHalfCpltCallback()).
  - When all the data has been written  (HAL_CORDIC_WriteDataCpltCallback() or callback function registered
    with HAL_CORDIC_RegisterWriteDataCpltCallback()).
  - When half of all the data has been written  (HAL_CORDIC_WriteHalfCpltCallback() or callback function registered
    with HAL_CORDIC_RegisterWriteHalfCpltCallback()).
  - When the abort is complete (HAL_CORDIC_AbortCpltCallback() or callback function registered with
    HAL_CORDIC_RegisterAbortCpltCallback()).
  - When an error occurs in the CORDIC driver (HAL_CORDIC_ErrorCallback() or callback function registered with
    HAL_CORDIC_RegisterErrorCallback()).

Depending on the process function one's use, different callback might be triggered:

| Process API \n \ \n Callbacks    | HAL_CORDIC_Calculate_IT | HAL_CORDIC_Write_IT | HAL_CORDIC_Read_IT |
|----------------------------------|:-----------------------:|:-------------------:|:------------------:|
| HAL_CORDIC_CalculateCpltCallback |            x            |                     |          x         |
| HAL_CORDIC_WriteDataCpltCallback |            x            |          x          |                    |
| HAL_CORDIC_ErrorCallback         |            x            |          x          |          x         |


| Process API \n \ \n Callbacks    | HAL_CORDIC_Calculate_DMA | HAL_CORDIC_Write_DMA | HAL_CORDIC_Read_DMA |
|----------------------------------|:------------------------:|:--------------------:|:-------------------:|
| HAL_CORDIC_CalculateCpltCallback |            x             |                      |          x          |
| HAL_CORDIC_WriteDataCpltCallback |            x             |           x          |                     |
| HAL_CORDIC_ReadHalfCpltCallback  |                          |                      |                     |
| HAL_CORDIC_WriteHalfCpltCallback |                          |                      |                     |
| HAL_CORDIC_AbortCpltCallback     |                          |                      |                     |
| HAL_CORDIC_ErrorCallback         |            x             |           x          |          x          |


| Process API \n \ \n Callbacks    | HAL_CORDIC_Calculate_DMA_opt | HAL_CORDIC_Write_DMA_opt | HAL_CORDIC_Read_DMA_opt |
|----------------------------------|:----------------------------:|:------------------------:|:-----------------------:|
| HAL_CORDIC_CalculateCpltCallback |             x                |                          |             x           |
| HAL_CORDIC_WriteDataCpltCallback |             x                |             x            |                         |
| HAL_CORDIC_ReadHalfCpltCallback* |             x                |                          |             x           |
| HAL_CORDIC_WriteHalfCpltCallback*|             x                |             x            |                         |
| HAL_CORDIC_AbortCpltCallback     |                              |                          |                         |
| HAL_CORDIC_ErrorCallback         |             x                |             x            |             x           |
@note with HAL_CORDIC_OPT_DMA_IT_HALF_CPLT argument value for interrupts parameter


| Process API \n \ \n Callbacks | HAL_CORDIC_Abort_IT |
|-------------------------------|:-------------------:|
| HAL_CORDIC_AbortCpltCallback  |          x          |
  */

/**
  * @brief  Handle CORDIC interrupt request.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  */
void HAL_CORDIC_IRQHandler(hal_cordic_handle_t *hcordic)
{
  CORDIC_TypeDef *p_cordic;

  ASSERT_DBG_PARAM((hcordic != NULL));

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  /* Check if calculation complete interrupt is enabled and if result ready flag is raised */
  if (LL_CORDIC_IsEnabledIT(p_cordic) != 0U)
  {
    if (LL_CORDIC_IsActiveFlag_RRDY(p_cordic) != CORDIC_FLAG_NOT_ACTIVE)
    {
      /* Decrement number of calculations to get */
      hcordic->nb_calculus_to_get--;

      /* Read output data from Read Data register, and increment output buffer pointer */
      CORDIC_ReadDataAndIncPtr(hcordic, &(hcordic->p_output_buffer));

      /* Check if calculations are still to be done */
      if (hcordic->nb_calculus_to_do > 0U)
      {
        /* Decrement number of calculations to do */
        hcordic->nb_calculus_to_do--;

        /* Continue the processing by providing another write of input data
           in the Write Data register, and increment input buffer pointer */
        CORDIC_WriteDataAndIncPtr(hcordic, &(hcordic->p_input_buffer));
      }

      /* Check if all calculations results are all done */
      if (hcordic->nb_calculus_to_get == 0UL)
      {
        /* Disable Result Ready Interrupt */
        LL_CORDIC_DisableIT(p_cordic);

        /* Change the CORDIC state */
        hcordic->global_state = HAL_CORDIC_STATE_IDLE;

        /* Call calculation complete callback */
#if defined(USE_HAL_CORDIC_REGISTER_CALLBACKS) && (USE_HAL_CORDIC_REGISTER_CALLBACKS == 1U)
        /*Call registered callback*/
        hcordic->p_calculate_cpt_cb(hcordic);
#else
        /*Call legacy weak (surcharged) callback*/
        HAL_CORDIC_CalculateCpltCallback(hcordic);
#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */
      }
    }
  }
}

/**
  * @brief  CORDIC error callback.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__weak void HAL_CORDIC_ErrorCallback(hal_cordic_handle_t *hcordic)
{
  /* Prevent unused argument(s) compilation warning */
  ASSERT_DBG_PARAM(hcordic != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hcordic);

  /* NOTE : This function must not be modified; when the callback is needed,
            the HAL_CORDIC_ErrorCallback can be implemented in the user file
   */
}

/**
  * @brief  CORDIC calculate complete callback.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__weak void HAL_CORDIC_CalculateCpltCallback(hal_cordic_handle_t *hcordic)
{
  /* Prevent unused argument(s) compilation warning */
  ASSERT_DBG_PARAM(hcordic != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hcordic);

  /* NOTE : This function must not be modified; when the callback is needed,
            the HAL_CORDIC_CalculateCpltCallback can be implemented in the user file
   */
}
#if defined (USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
/**
  * @brief  CORDIC Write data half complete callback.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__weak void HAL_CORDIC_WriteHalfCpltCallback(hal_cordic_handle_t *hcordic)
{
  /* Prevent unused argument(s) compilation warning */
  ASSERT_DBG_PARAM(hcordic != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hcordic);

  /* NOTE : This function must not be modified; when the callback is needed,
            the HAL_CORDIC_WriteHalfCpltCallback can be implemented in the user file
   */
}

/**
  * @brief  CORDIC Read data half complete callback.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__weak void HAL_CORDIC_ReadHalfCpltCallback(hal_cordic_handle_t *hcordic)
{
  /* Prevent unused argument(s) compilation warning */
  ASSERT_DBG_PARAM(hcordic != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hcordic);

  /* NOTE : This function must not be modified; when the callback is needed,
            the HAL_CORDIC_ReadHalfCpltCallback can be implemented in the user file
   */
}
#endif /* USE_HAL_CORDIC_DMA */

/**
  * @brief  CORDIC Write data complete callback.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__weak void HAL_CORDIC_WriteDataCpltCallback(hal_cordic_handle_t *hcordic)
{
  /* Prevent unused argument(s) compilation warning */
  ASSERT_DBG_PARAM(hcordic != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hcordic);

  /* NOTE : This function must not be modified; when the callback is needed,
            the HAL_CORDIC_WriteDataCpltCallback can be implemented in the user file
   */
}

/**
  * @brief Abort completed callback.
  * @param hcordic Pointer to a hal_cordic_handle_t.
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__weak void HAL_CORDIC_AbortCpltCallback(hal_cordic_handle_t *hcordic)
{
  /* Prevent unused argument(s) compilation warning */
  ASSERT_DBG_PARAM(hcordic != NULL);

  STM32_UNUSED(hcordic);
  /* NOTE : This function must not be modified; when the callback is needed,
            the HAL_CORDIC_AbortCpltCallback can be implemented in the user file
   */
}

#if defined(USE_HAL_CORDIC_REGISTER_CALLBACKS) && (USE_HAL_CORDIC_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User CORDIC callback for Error.
  * @param  hcordic    Pointer to a hal_cordic_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK            Register completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_CORDIC_RegisterErrorCallback(hal_cordic_handle_t *hcordic, hal_cordic_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hcordic != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_INIT | (uint32_t)HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hcordic->p_error_cb = p_callback;
  return HAL_OK;
}

/**
  * @brief  Register a User CORDIC callback for DMA Abort complete.
  * @param  hcordic  Pointer to a hal_cordic_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK   Register completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_CORDIC_RegisterAbortCpltCallback(hal_cordic_handle_t *hcordic, hal_cordic_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hcordic != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_INIT | (uint32_t)HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hcordic->p_abort_cplt_cb = p_callback;
  return HAL_OK;
}

/**
  * @brief  Register a User CORDIC callback for write data complete.
  * @param  hcordic   Pointer to a hal_cordic_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK  Register completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_CORDIC_RegisterWriteDataCpltCallback(hal_cordic_handle_t *hcordic, hal_cordic_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hcordic != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_INIT | (uint32_t)HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hcordic->p_write_cpt_cb = p_callback;
  return HAL_OK;
}

#if defined (USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
/**
  * @brief  Register the CORDIC Write Half complete callback.
  * @param  hcordic   Pointer to a hal_cordic_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK  Register completed successfully.
  */
hal_status_t HAL_CORDIC_RegisterWriteHalfCpltCallback(hal_cordic_handle_t *hcordic, hal_cordic_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hcordic != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_INIT | (uint32_t)HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hcordic->p_write_half_cplt_cb = p_callback;

  return HAL_OK;
}


/**
  * @brief  Register the CORDIC Read Half complete callback.
  * @param  hcordic   Pointer to a hal_cordic_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK  Register completed successfully.
  */
hal_status_t HAL_CORDIC_RegisterReadHalfCpltCallback(hal_cordic_handle_t *hcordic, hal_cordic_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hcordic != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_INIT | (uint32_t)HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hcordic->p_read_half_cplt_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_CORDIC_DMA */

/**
  * @brief  Register a User CORDIC callback for calculation complete.
  * @param  hcordic   Pointer to a hal_cordic_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK  Register completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_CORDIC_RegisterCalculateCpltCallback(hal_cordic_handle_t *hcordic, hal_cordic_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hcordic != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hcordic->global_state, (uint32_t)HAL_CORDIC_STATE_INIT | (uint32_t)HAL_CORDIC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hcordic->p_calculate_cpt_cb = p_callback;
  return HAL_OK;
}

#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */
/**
  * @}
  */

#if defined(USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
/** @addtogroup CORDIC_Exported_Functions_Group6
  * @{

This section permits to get in runtime the last error codes of the peripheral CORDIC with
HAL_CORDIC_GetLastErrorCodes().
  */

/**
  * @brief  Return the CORDIC peripheral error.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @retval uint32_t This return value can be a combination of the following values:
  *        @arg @ref HAL_CORDIC_ERROR_NONE
  *        @arg @ref HAL_CORDIC_ERROR_DMA
  */
uint32_t HAL_CORDIC_GetLastErrorCodes(const hal_cordic_handle_t *hcordic)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));

  /* Return CORDIC error code */
  return hcordic->last_error_codes;
}
/**
  * @}
  */
#endif  /* USE_HAL_CORDIC_GET_LAST_ERRORS */

/** @addtogroup CORDIC_Exported_Functions_Group7
  * @{

This section permits to get in runtime the state of the CORDIC peripheral using HAL_CORDIC_GetState() function.
  */

/**
  * @brief  Return the CORDIC handle state.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @retval hal_cordic_state_t CORDIC state.
  */
hal_cordic_state_t HAL_CORDIC_GetState(const hal_cordic_handle_t *hcordic)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hcordic != NULL));

  /* Return CORDIC handle state */
  return hcordic->global_state;
}
/**
  * @}
  */

#if defined(USE_HAL_CORDIC_USER_DATA) && (USE_HAL_CORDIC_USER_DATA == 1)
/** @addtogroup CORDIC_Exported_Functions_Group8
  * @{

This section provides functions allowing to set user specific data to a CORDIC instance:
    - HAL_CORDIC_SetUserData(): Set user data in handler.
    - HAL_CORDIC_GetUserData(): Get user data from handler.
  */

/**
  * @brief Store user data pointer into the handle.
  * @param hcordic     Pointer to a hal_cordic_handle_t.
  * @param p_user_data Pointer to the user data.
  */
void HAL_CORDIC_SetUserData(hal_cordic_handle_t *hcordic, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hcordic != NULL);

  /* Set user data */
  hcordic->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve user data pointer from the handle.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @retval void Pointer to the user data.
  */
const void *HAL_CORDIC_GetUserData(const hal_cordic_handle_t *hcordic)
{
  ASSERT_DBG_PARAM(hcordic != NULL);

  return (hcordic->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_CORDIC_USER_DATA */

/**
  * @}
  */    /* CORDIC_Exported_Functions*/

/** @addtogroup CORDIC_Private_Functions
  * @{
  */


/**
  * @brief  Calculate and Validate the number of calculus to be performed.
  * @param  csr_reg CORDIC_CSR register content
  * @param  p_inbuffer_desc Pointer to the input buffer descriptor.
  * @note   This function calculates the number of calculus using:
  *             - The buffer size
  *             - The calculus configuration (number of arguments and size of arguments)
  * @retval  computed_number_write the number of write given the set parameters and the input buffer size.
  */
static uint32_t CORDIC_ValidateWriteNumber(uint32_t csr_reg, const hal_cordic_buffer_desc_t *p_inbuffer_desc)
{
  /* number of word per calculus given the function configuration */
  /*                   \NARGS |  (1)  |   (2)                     */
  /*            ARG_SIZE \    |   0   |    1                      */
  /*                 -------------------------                    */
  /*         (32bits)   0     |   1   |    2                      */
  /*                 -------------------------                    */
  /*         (16bits)   1     |   1   |    1                      */
  /*                 -------------------------                    */

  hal_cordic_in_size_t arg_size;
  hal_cordic_arg_nb_t arg_number;
  uint32_t computed_number_write = p_inbuffer_desc->size_word;

  arg_size    = (hal_cordic_in_size_t)(uint32_t)(csr_reg & CORDIC_CSR_ARGSIZE_Msk);
  arg_number  = (hal_cordic_arg_nb_t)(uint32_t)(csr_reg & CORDIC_CSR_NARGS_Msk);

  /* Calculate the number of word per calculus */
  if ((arg_size == HAL_CORDIC_IN_SIZE_32BITS) && (arg_number == HAL_CORDIC_ARG_NB_2))
  {
    computed_number_write = p_inbuffer_desc->size_word >> 1;
  }

  return computed_number_write;
}

/**
  * @brief  Calculate and Validate the number of calculus to read.
  * @param  csr_reg CORDIC_CSR register content
  * @param  p_outbuffer_desc Pointer to the output buffer descriptor.
  * @note   This function calculates the number of calculus using:
  *           - The buffer size
  *           - The calculus configuration (number of results and size of results)
  * @retval  computed_number_read the number of results given the set parameters and the output buffer size.
  */
static uint32_t CORDIC_ValidateReadNumber(uint32_t csr_reg, const hal_cordic_buffer_desc_t *p_outbuffer_desc)
{
  /* number of word per calculus given the function configuration */
  /*                   \NARGS |  (1)  |   (2)                     */
  /*            ARG_SIZE \    |   0   |    1                      */
  /*                 -------------------------                    */
  /*         (32bits)   0     |   1   |    2                      */
  /*                 -------------------------                    */
  /*         (16bits)   1     |   1   |    1                      */
  /*                 -------------------------                    */

  hal_cordic_out_size_t res_size;
  hal_cordic_result_nb_t res_number;
  uint32_t computed_number_read = p_outbuffer_desc->size_word;

  res_size    = (hal_cordic_out_size_t)(uint32_t)(csr_reg & CORDIC_CSR_RESSIZE_Msk);
  res_number  = (hal_cordic_result_nb_t)(uint32_t)(csr_reg & CORDIC_CSR_NRES_Msk);

  /* Calculate the number of word per calculus */
  if ((res_size == HAL_CORDIC_OUT_SIZE_32BITS) && (res_number == HAL_CORDIC_RESULT_NB_2))
  {
    computed_number_read = p_outbuffer_desc->size_word >> 1;
  }

  return computed_number_read;
}

/**
  * @brief  Write blank data to CORDIC_WDATA register.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @warning   This function has to be called after the calculation is finished in order to avoid a non expected result
  *         when a 2 arguments function is used with only Arg1 set. Arg2 is set to its default value after reset (+1)
  */
static inline void CORDIC_ResetArguments(hal_cordic_handle_t *hcordic)
{
  CORDIC_TypeDef *p_cordic;
  uint32_t csr_reg;

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  /* Read the actual configuration */
  hal_cordic_config_t config;

  /* read the CSR register */
  csr_reg = LL_CORDIC_READ_REG((p_cordic), CSR);

  config.function  = (hal_cordic_function_t)(uint32_t)((csr_reg & CORDIC_CSR_FUNC_Msk));
  config.precision = (hal_cordic_precision_t)(uint32_t)((csr_reg & CORDIC_CSR_PRECISION_Msk));
  config.scale = (hal_cordic_scale_factor_t)(uint32_t)((csr_reg & CORDIC_CSR_SCALE_Msk));
  config.nb_args = (hal_cordic_arg_nb_t)(uint32_t)((csr_reg & CORDIC_CSR_NARGS_Msk));
  config.nb_results = (hal_cordic_result_nb_t)(uint32_t)((csr_reg & CORDIC_CSR_NRES_Msk));
  config.in_size = (hal_cordic_in_size_t)(uint32_t)((csr_reg & CORDIC_CSR_ARGSIZE_Msk));
  config.out_size = (hal_cordic_out_size_t)(uint32_t)((csr_reg & CORDIC_CSR_RESSIZE_Msk));

  /* Program a Sine function with 2 arguments of 32bits */
  LL_CORDIC_SetFunction(p_cordic, LL_CORDIC_FUNCTION_SINE);   /* Sine function    */
  LL_CORDIC_SetNbWrite(p_cordic, LL_CORDIC_NBWRITE_2);        /* Two arguments    */
  LL_CORDIC_SetInSize(p_cordic, LL_CORDIC_INSIZE_32BITS);     /* 32bits arguments */
  LL_CORDIC_SetNbRead(p_cordic, LL_CORDIC_NBREAD_2);          /* Two results      */
  LL_CORDIC_SetOutSize(p_cordic, LL_CORDIC_OUTSIZE_32BITS);   /* 32 bits results  */

  /* Write ARG1 to CORDIC_WDATA register - ZeroOverhead mode selected no need to wait for RRDY bit to raise.*/
  LL_CORDIC_WriteData(p_cordic, CORDIC_ARGUMENT1);
  /* Write ARG1 to CORDIC_WDATA register - ZeroOverhead mode selected no need to wait for RRDY bit to raise.*/
  LL_CORDIC_WriteData(p_cordic, CORDIC_ARGUMENT2);

  /* Read RES1 */
  (void)LL_CORDIC_ReadData(p_cordic);
  /* Read RES2 */
  (void)LL_CORDIC_ReadData(p_cordic);

  /* Set Initial configuration */
  /* Apply all configuration parameters in CORDIC control register */
  LL_CORDIC_Config(p_cordic, (uint32_t)(config.function), (uint32_t)(config.precision),
                   (uint32_t)(config.scale), (uint32_t)(config.nb_args),
                   (uint32_t)(config.nb_results), (uint32_t)(config.in_size),
                   (uint32_t)(config.out_size));

}

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
/**
  * @brief  Check that the given precision matches the selected function.
  * @param  function Function to be checked.
  * @param  precision Value of the precision to be set.
  * @warning   This function has to be called in ASSERT_DBG_PARAM() macro inside HAL_CORDIC_SetPrecision() function.
  * @retval 1 The passed precision parameter matches the function requirements.
  * @retval 0 The passed precision parameter does not match the function requirements.
  */
static inline uint32_t CORDIC_CheckPrecision(hal_cordic_function_t function, hal_cordic_precision_t precision)
{
  uint32_t result = 0UL;

  /* analyse the precision vs the function */
  if (function ==  HAL_CORDIC_FUNCTION_SQUARE_ROOT)
  {
    /* number of iterations: 4, 8, 12 */
    if ((precision >= HAL_CORDIC_PRECISION_1CYCLE) && (precision <= HAL_CORDIC_PRECISION_3CYCLES))
    {
      result = 1UL;
    }
    else
    {
      result = 0UL;
    }
  }
  else
  {
    if ((function == HAL_CORDIC_FUNCTION_COSINE) || (function == HAL_CORDIC_FUNCTION_SINE)
        || (function == HAL_CORDIC_FUNCTION_PHASE) || (function == HAL_CORDIC_FUNCTION_MODULUS)
        || (function == HAL_CORDIC_FUNCTION_ARCTANGENT) || (function == HAL_CORDIC_FUNCTION_HCOSINE)
        || (function == HAL_CORDIC_FUNCTION_HSINE) || (function == HAL_CORDIC_FUNCTION_HARCTANGENT)
        || (function == HAL_CORDIC_FUNCTION_NATURAL_LOG))
    {
      /* number of iterations: 4, 8, 12, 16, 20, 24 */
      if ((precision >= HAL_CORDIC_PRECISION_1CYCLE) && (precision <= HAL_CORDIC_PRECISION_6CYCLES))
      {
        result = 1UL;
      }
      else
      {
        result = 0UL;
      }
    }
    else
    {
      result = 0UL;
    }
  }

  return result;
}

/**
  * @brief  Check that the given scaling factor matches the selected function.
  * @param  function Function to be checked.
  * @param  scale Value of the scaling factor to be set.
  * @warning   This function has to be called in ASSERT_DBG_PARAM() macro inside HAL_CORDIC_SetScale() function.
  * @retval 1 The passed scale parameter matches the function requirements.
  * @retval 0 The passed scale parameter does not match the function requirements.
  */
static inline uint32_t CORDIC_CheckScale(hal_cordic_function_t function, hal_cordic_scale_factor_t scale)
{
  uint32_t result = 0UL;

  if ((function == HAL_CORDIC_FUNCTION_COSINE) || (function == HAL_CORDIC_FUNCTION_SINE)
      || (function == HAL_CORDIC_FUNCTION_PHASE) || (function == HAL_CORDIC_FUNCTION_MODULUS))
  {
    if (scale == HAL_CORDIC_SCALE_0)
    {
      result = 1UL;
    }
    else
    {
      result = 0UL;
    }
  }
  else
  {
    if (function == HAL_CORDIC_FUNCTION_ARCTANGENT)
    {
      result = 1UL;
    }

    if ((function == HAL_CORDIC_FUNCTION_HCOSINE) || (function == HAL_CORDIC_FUNCTION_HSINE)
        || (function == HAL_CORDIC_FUNCTION_HARCTANGENT))
    {
      if (scale == HAL_CORDIC_SCALE_1) /* scale = 1 only allowed by the hyperbolic functions */
      {
        result = 1UL;
      }
      else
      {
        result = 0UL;
      }
    }

    if (function == HAL_CORDIC_FUNCTION_NATURAL_LOG)
    {
      if ((scale >= HAL_CORDIC_SCALE_1) && (scale <= HAL_CORDIC_SCALE_4)) /* scale values from 1 to 4 */
      {
        result = 1UL;
      }
      else
      {
        result = 0UL;
      }
    }

    if (function == HAL_CORDIC_FUNCTION_SQUARE_ROOT)
    {
      if ((scale > HAL_CORDIC_SCALE_0) && (scale <= HAL_CORDIC_SCALE_2)) /* scale values from 0 to 2 */
      {
        result = 1UL;
      }
      else
      {
        result = 0UL;
      }
    }
  }

  return result;
}
#endif /* USE_HAL_CHECK_PARAM */

/**
  * @brief  Write data for CORDIC processing, and increment input buffer pointer.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @param  pp_input_buffer Pointer to pointer to input buffer.
  */
static void CORDIC_WriteDataAndIncPtr(hal_cordic_handle_t *hcordic, const int32_t **pp_input_buffer)
{
  CORDIC_TypeDef *p_cordic;

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  /* First write of input data in the Write Data register */
  LL_CORDIC_WriteData(p_cordic, (uint32_t) **pp_input_buffer);

  /* Increment input data pointer */
  (*pp_input_buffer)++;

  /* Check if second write of input data is expected */
  if (LL_CORDIC_GetNbWrite(p_cordic) == (uint32_t)HAL_CORDIC_ARG_NB_2)
  {
    /* Second write of input data in the Write Data register */
    LL_CORDIC_WriteData(p_cordic, (uint32_t) **pp_input_buffer);

    /* Increment input data pointer */
    (*pp_input_buffer)++;
  }
}

/**
  * @brief  Read data of CORDIC processing, and increment output buffer pointer.
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @param  pp_output_buffer Pointer to pointer to output buffer.
  */
static void CORDIC_ReadDataAndIncPtr(hal_cordic_handle_t *hcordic, int32_t **pp_output_buffer)
{
  CORDIC_TypeDef *p_cordic;

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  /* First read of output data from the Read Data register */
  **pp_output_buffer = (int32_t)LL_CORDIC_ReadData(p_cordic);

  /* Increment output data pointer */
  (*pp_output_buffer)++;

  /* Check if second read of output data is expected */
  if (LL_CORDIC_GetNbRead(p_cordic) == (uint32_t)HAL_CORDIC_RESULT_NB_2)
  {
    /* Second read of output data from the Read Data register */
    **pp_output_buffer = (int32_t)LL_CORDIC_ReadData(p_cordic);

    /* Increment output data pointer */
    (*pp_output_buffer)++;
  }
}

/**
  * @brief  Abort the ongoing transfer (blocking process).
  * @param  hcordic Pointer to a hal_cordic_handle_t.
  * @retval HAL_OK      Operation completed successfully.
  */
static hal_status_t CORDIC_Abort(hal_cordic_handle_t *hcordic)
{
  CORDIC_TypeDef *p_cordic;

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

#if defined(USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
  /* Check if the DMA Read (output) is enabled */
  if (LL_CORDIC_IsEnabledDMAReq_RD(p_cordic) == 1U)
  {
    /* Disable DMA Read */
    LL_CORDIC_DisableDMAReq_RD(p_cordic);

    if (hcordic->p_dma_out != NULL)
    {
      hcordic->p_dma_out->p_xfer_abort_cb = NULL;

      (void)HAL_DMA_Abort(hcordic->p_dma_out);

      /* Reset the output buffer */
      hcordic->p_output_buffer = NULL;
      /* Reset the counter of result to get */
      hcordic->nb_calculus_to_get = 0U;
    }
  }

  /* Check if the DMA Write (input) is enabled */
  if (LL_CORDIC_IsEnabledDMAReq_WR(p_cordic) == 1U)
  {
    /* Disable DMA Write */
    LL_CORDIC_DisableDMAReq_WR(p_cordic);

    if (hcordic->p_dma_in != NULL)
    {
      hcordic->p_dma_in->p_xfer_abort_cb = NULL;

      (void)HAL_DMA_Abort(hcordic->p_dma_in);

      /* Reset the input buffer */
      hcordic->p_input_buffer = NULL;
      /* Reset the counter of calculus to do */
      hcordic->nb_calculus_to_do = 0U;
    }
  }
#endif /* USE_HAL_CORDIC_DMA */

  /* Disable the Data Ready interrupt */
  LL_CORDIC_DisableIT(p_cordic);
#if defined(USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
  hcordic->last_error_codes = HAL_CORDIC_ERROR_NONE;
#endif /* USE_HAL_CORDIC_GET_LAST_ERRORS */

  return HAL_OK;
}

#if defined(USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
/**
  * @brief DMA CORDIC Input Data process complete callback.
  * @param hdma Pointer to a hal_dma_handle_t.
  */
static void CORDIC_DMAInCplt(hal_dma_handle_t *hdma)
{
  CORDIC_TypeDef *p_cordic;

  hal_cordic_handle_t *hcordic = (hal_cordic_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  /* Check if DMA in circular mode*/
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
#endif /* USE_HAL_DMA_LINKEDLIST */
  {
    hcordic->nb_calculus_to_do = 0UL;

    /* Get the CORDIC CMSIS handle */
    p_cordic = CORDIC_GET_INSTANCE(hcordic);

    /* Disable the DMA transfer for input request */
    LL_CORDIC_DisableDMAReq_WR(p_cordic);
  }

  /* Call calculation complete callback */
#if defined(USE_HAL_CORDIC_REGISTER_CALLBACKS) && (USE_HAL_CORDIC_REGISTER_CALLBACKS == 1U)
  /* Call registered callback*/
  hcordic->p_write_cpt_cb(hcordic);
#else
  /* Call legacy weak (surcharged) callback*/
  HAL_CORDIC_WriteDataCpltCallback(hcordic);
#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */
}

/**
  * @brief DMA CORDIC Input Data process half complete callback.
  * @param hdma Pointer to a hal_dma_handle_t.
  */
static void CORDIC_DMAInHalfCplt(hal_dma_handle_t *hdma)
{
  CORDIC_TypeDef *p_cordic;

  hal_cordic_handle_t *hcordic = (hal_cordic_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  /* Disable the DMA transfer for input request */
  LL_CORDIC_DisableDMAReq_WR(p_cordic);

  /* Call calculation complete callback */
#if defined(USE_HAL_CORDIC_REGISTER_CALLBACKS) && (USE_HAL_CORDIC_REGISTER_CALLBACKS == 1U)
  /* Call registered callback*/
  hcordic->p_write_half_cplt_cb(hcordic);
#else
  /* Call legacy weak (surcharged) callback*/
  HAL_CORDIC_WriteHalfCpltCallback(hcordic);
#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */
}

/**
  * @brief DMA CORDIC Output Data process complete callback.
  * @param hdma Pointer to a hal_dma_handle_t.
  */
static void CORDIC_DMAOutCplt(hal_dma_handle_t *hdma)
{
  CORDIC_TypeDef *p_cordic;

  hal_cordic_handle_t *hcordic = (hal_cordic_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  /* Check if DMA in circular mode*/
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
#endif /* USE_HAL_DMA_LINKEDLIST */
  {
    hcordic->nb_calculus_to_get = 0UL;

    /* Change the CORDIC state to idle */
    hcordic->global_state = HAL_CORDIC_STATE_IDLE;

    /* Disable the DMA transfer for output request */
    LL_CORDIC_DisableDMAReq_RD(p_cordic);

    /* Stop the interrupts error handling */
    LL_CORDIC_DisableIT(p_cordic);
  }

  /* Call calculation complete callback */
#if USE_HAL_CORDIC_REGISTER_CALLBACKS == 1
  /* Call registered callback*/
  hcordic->p_calculate_cpt_cb(hcordic);
#else
  /* Call legacy weak (surcharged) callback*/
  HAL_CORDIC_CalculateCpltCallback(hcordic);
#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */
}

/**
  * @brief DMA CORDIC Output Data read half complete callback.
  * @param hdma Pointer to a hal_dma_handle_t.
  */
static void CORDIC_DMAOutHalfCplt(hal_dma_handle_t *hdma)
{

  hal_cordic_handle_t *hcordic = (hal_cordic_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);

  /* Call calculation complete callback */
#if defined(USE_HAL_CORDIC_REGISTER_CALLBACKS) && (USE_HAL_CORDIC_REGISTER_CALLBACKS == 1)
  /* Call registered callback*/
  hcordic->p_read_half_cplt_cb(hcordic);
#else
  /* Call legacy weak (surcharged) callback*/
  HAL_CORDIC_ReadHalfCpltCallback(hcordic);
#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */
}

/**
  * @brief DMA CORDIC communication error callback.
  * @param hdma Pointer to a hal_dma_handle_t.
  */
static void CORDIC_DMAError(hal_dma_handle_t *hdma)
{
  hal_cordic_handle_t *hcordic = (hal_cordic_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);

  /* Set CORDIC handle state to idle */
  hcordic->global_state = HAL_CORDIC_STATE_IDLE;
#if defined(USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
  /* Set CORDIC handle error code to DMA error */
  hcordic->last_error_codes |= HAL_CORDIC_ERROR_DMA;
#endif  /* USE_HAL_CORDIC_GET_LAST_ERRORS */

  /* Call user callback */
#if defined(USE_HAL_CORDIC_REGISTER_CALLBACKS) && (USE_HAL_CORDIC_REGISTER_CALLBACKS == 1U)
  /* Call registered callback*/
  hcordic->p_error_cb(hcordic);
#else
  /* Call legacy weak (surcharged) callback*/
  HAL_CORDIC_ErrorCallback(hcordic);
#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA  Abort callback
  * @param  hdma Pointer to a hal_dma_handle_t structure which contains a DMA instance.
  */
static void CORDIC_DMAAbort(hal_dma_handle_t *hdma)
{
  CORDIC_TypeDef *p_cordic;

  hal_cordic_handle_t *hcordic = (hal_cordic_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);

  /* Get the CORDIC CMSIS handle */
  p_cordic = CORDIC_GET_INSTANCE(hcordic);

  if (hcordic->p_dma_in != NULL)
  {
    hcordic->p_dma_in->p_xfer_abort_cb = NULL;
    hcordic->nb_calculus_to_do = 0UL;
    /* Disable any DMA requests */
    LL_CORDIC_DisableDMAReq_WR(p_cordic);
  }

  if (hcordic->p_dma_out != NULL)
  {
    hcordic->p_dma_out->p_xfer_abort_cb = NULL;
    hcordic->nb_calculus_to_get = 0UL;
    LL_CORDIC_DisableDMAReq_RD(p_cordic);
  }

  /* Disable IT */
  LL_CORDIC_DisableIT(p_cordic);

  /* Reset the pointers to buffers */
  hcordic->p_input_buffer  = NULL;
  hcordic->p_output_buffer = NULL;

  /* Reset the counters of calculus/results */
  hcordic->nb_calculus_to_do  = 0U;
  hcordic->nb_calculus_to_get = 0U;

  hcordic->global_state = HAL_CORDIC_STATE_IDLE;

#if defined(USE_HAL_CORDIC_REGISTER_CALLBACKS) && (USE_HAL_CORDIC_REGISTER_CALLBACKS == 1)
  hcordic->p_abort_cplt_cb(hcordic);
#else
  HAL_CORDIC_AbortCpltCallback(hcordic);
#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */
}

#endif /* USE_HAL_CORDIC_DMA */

/**
  * @}
  */

#endif /* HAL_CORDIC_MODULE_ENABLED */
#endif /* CORDIC */

/**
  * @}
  */

/**
  * @}
  */

