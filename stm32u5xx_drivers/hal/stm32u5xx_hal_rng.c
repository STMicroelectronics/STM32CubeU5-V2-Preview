/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_rng.c
  * @brief   RNG HAL module driver
  *          This file provides firmware functions to manage the following functionalities of the Random Number
  *          Generator (RNG) peripheral:
  *           + Initialization and de-initialization functions
  *           + Configurations functions
  *           + IO operation functions
  *           + Peripheral state and errors functions
  *
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup RNG
  * @brief RNG HAL module driver.
  * @{

## The RNG main features:

The true random number generator (RNG) is a NIST SP 800-90B compliant entropy source delivers a 32-bit random numbers,
It has an AMBA AHB slave peripheral, accessible through 32-bit word single accesses only. It can be disabled to reduce
power consumption, or enabled with an automatic low power mode (default configuration).The RNG has been pre-certified
NIST SP800-90B and it has been also tested with the German BSI statistical tests of AIS-31 (T0 to T8).

# How to use the HAL RNG driver

## The HAL RNG driver can be used as follows:

- Initialize the RNG handle by calling the HAL_RNG_Init() API that performs these operations:
  - Associate instance to the handle
  - Enable the RNG clock interface (When USE_HAL_RNG_CLK_ENABLE_MODEL compilation flag is set to
    HAL_CLK_ENABLE_PERIPH_ONLY or HAL_CLK_ENABLE_PERIPH_PWR_SYSTEM in the stm32u5xx_hal_conf.h module)
  - The initialization of the handle state to the HAL_RNG_STATE_IDLE. \n

- Configure the RNG peripheral with one of the following configuration :
  1. Custom Configuration:
     - Declare a @ref hal_rng_config_t structure
     - Fill all parameters of the declared configuration structure
     - Call HAL_RNG_SetConfig() function  with the filled configuration structure
  2. NIST compliant configuration:
     - Call HAL_RNG_SetCertifiedNISTConfig() function.
  3. Candidate NIST compliant configuration:
     - Call HAL_RNG_SetCandidateNISTConfig() function.
  4. Candidate German BSI compliant configuration:
     - Call HAL_RNG_SetCandidateGermanBSIConfig() function.
- To protect the peripheral from any configuration, call the HAL_RNG_LockConfig(). When locked, it's not allowed to
  apply any new configuration. The configuration is then possible only after a system reset or RNG peripheral reset
  through RCC.

- When needed, unitary reconfiguration can be done through:
  - HAL_RNG_EnableClockErrorDetection() and HAL_RNG_DisableClockErrorDetection() to enable (resp. disable) the clock
    error detection feature.
  - HAL_RNG_EnableAutoReset() and HAL_RNG_DisableAutoReset() to enable (resp. disable) the automatic reset after seed
    error feature.
  - HAL_RNG_SetClockDivider() to set a new kernel clock divider.

- The RNG can generates random numbers in two different modes:
  - Polling mode:
    1. Call HAL_RNG_GenerateRandomNumber() with specifying :
       - The number of words to be generated.
       - The application buffer where the data will be stored.
         - The maximum timeout for random number words to be generated.
    2. When a seed error occurs, call the HAL_RNG_RecoverSeedError(). (The recovery is not granted through this
         function due to hardware constraint)
  - Interrupt mode operation:
    1. Call HAL_RNG_GenerateRandomNumber_IT() with specifying :
       - The number of words to be generated.
       - The application buffer where the data will be stored.
    2. Call HAL_RNG_IRQHandler() to handle RNG interrupts and to store the generated number words within the specified
       user buffer.
    3. When all random numbers specified by the user are generated, HAL_RNG_GenerationCpltCallback() is executed.
    4. When a seed error occurs during the generation process, HAL_RNG_ErrorCallback() is executed where it is
       recommended to call HAL_RNG_RecoverSeedError().

- Deinitialize the RNG peripheral user can call the HAL_RNG_DeInit().

- Retrieve the HAL RNG information:
  - Use HAL_RNG_GetState() function to return the RNG state.
  - Use HAL_RNG_GetConfig() to get RNG configurations.
  - Use HAL_RNG_IsEnabledClockErrorDetection() to check whether the clock error detection feature is enabled or not.
  - Use HAL_RNG_IsEnabledAutoReset() to check whether the auto reset feature is enabled or not.
  - Use HAL_RNG_GetClockDivider() to get the clock divider configuration.
  - Set the compilation flag USE_HAL_RNG_GET_LAST_ERRORS to 1U in the stm32u5xx_hal_conf.h module to
   retrieve the last error code detected by the HAL RNG driver through the HAL_RNG_GetLastErrorCodes API.

- Register callback:
  - When the compilation flag USE_HAL_RNG_REGISTER_CALLBACKS is set to 1 in the stm32u5xx_hal_conf.h,
  it allows to configure dynamically the driver callbacks instead of using default ones.
  - Call HAL_RNG_RegisterGenerationCpltCallback() for end of generation random number event.
  - Call HAL_RNG_RegisterErrorCallback() for generation random number error events.

## Configuration inside the RNG driver

Config defines                 | Description              | Default value     | Note
------------------------------ | -------------------------| ------------------| ----------------------------------------
PRODUCT                        | from IDE                 | NA                | Ex:STM32U5XXxx.
USE_ASSERT_DBG_PARAM           | from IDE                 | None              | Enable the parameters asserts.
USE_ASSERT_DBG_STATE           | from IDE                 | None              | Enable the state asserts.
USE_HAL_CHECK_PARAM            | from hal_conf.h          | 0                 | Parameters runtime check.
USE_HAL_SECURE_CHECK_PARAM  | from hal_conf.h          | 0                 | Parameters runtime check for sensitive APIs
USE_HAL_RNG_MODULE             | from hal_conf.h          | 1                 | Enable the HAL RNG module.
USE_HAL_RNG_CLK_ENABLE_MODEL   | from hal_conf.h          | HAL_CLK_ENABLE_NO | Enable the HAL_RNG_CLK.
USE_HAL_RNG_REGISTER_CALLBACKS | from hal_conf.h          | 0                 | Enable the register callbacks assert.
USE_HAL_RNG_GET_LAST_ERRORS    | from hal_conf.h          | 0                 | Allows to get the last errors codes.
USE_HAL_RNG_USER_DATA          | from hal_conf.h          | 0                 | Allows to Enable/Disable user data.
RNG_CERT_NIST                  | from stm32u5xxxx.h | NA                | Product dependent values from DFP.
  */

#if defined(USE_HAL_RNG_MODULE) && (USE_HAL_RNG_MODULE == 1)

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private defines ---------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup RNG_Private_Macros RNG Private Macros
  * @{
  */
/*! Check the clock divider */
#define IS_RNG_CLOCK_DIVIDER(clock_div)               \
  (((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_1)        \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_2)     \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_4)     \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_8)     \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_16)    \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_32)    \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_64)    \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_128)   \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_256)   \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_512)   \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_1024)  \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_2048)  \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_4096)  \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_8192)  \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_16384) \
   || ((clock_div) == HAL_RNG_CLOCK_DIVIDER_BY_32768))

/*! Check the NIST Compliance parameters */
#define IS_RNG_STANDARD(standard) \
  (((standard) == HAL_RNG_NIST) || ((standard) == HAL_RNG_CUSTOM))

/*! Check config_1 parameter */
#define IS_RNG_CONFIG1(config1) ((config1) <= 0x3FUL)

/*! Check config_2 parameter */
#define IS_RNG_CONFIG2(config2) ((config2) <= 0x07UL)

/*! Check config_3 parameter */
#define IS_RNG_CONFIG3(config3) ((config3) <= 0xFUL)

/*! Check noise source parameter */
#define IS_RNG_NOISE_SOURCE(noise_src)                                            \
  ((((noise_src) & (HAL_RNG_OSCILLATOR_SOURCE_1 | HAL_RNG_OSCILLATOR_SOURCE_2     \
                    | HAL_RNG_OSCILLATOR_SOURCE_3)) != 0x00U)                     \
   && (((noise_src) & ~(HAL_RNG_OSCILLATOR_SOURCE_1 | HAL_RNG_OSCILLATOR_SOURCE_2 \
                        | HAL_RNG_OSCILLATOR_SOURCE_3)) == 0x0U))

/*! Check RNG clock error detection */
#define IS_RNG_CED(rng_ced) \
  (((rng_ced) == HAL_RNG_CLOCK_ERROR_DETECTION_ENABLED) || ((rng_ced) == HAL_RNG_CLOCK_ERROR_DETECTION_DISABLED))
/*! Convert the HAL RNG instance into CMSIS RNG instance */
#define RNG_GET_INSTANCE(handle) ((RNG_TypeDef *)(uint32_t)(handle)->instance)
/**
  * @}
  */

/* Private constants--------------------------------------------------------------------------------------------------*/
/** @defgroup RNG_Private_Constants RNG Private Constants
  * @{
  */
#define  RNG_SEED_ERROR_RECOVER_TRIALS  4U           /*!< RNG RNG recover trial value        */
#define  RNG_CONDRST_TIMEOUT_MS         1U           /*!< RNG CONDRST timeout in millisecond */
#define  RNG_CONFIG_1_MASK              0x03F00000UL /*!< RNG config1 mask                   */
#define  RNG_CONFIG_2_MASK              0x0000E000UL /*!< RNG config2 mask                   */
#define  RNG_CONFIG_3_MASK              0x00000F00UL /*!< RNG config3 mask                   */
#define  RNG_NIST_MASK                  0x00000001UL /*!< RNG NIST mask                      */
#define  RNG_CED_MASK                   0x00000001UL /*!< RNG CED mask                       */
#define  RNG_CLKDIV_MASK                0x000F0000UL /*!< RNG CLK divider mask               */
/**
  * @}
  */

/* Private functions prototypes --------------------------------------------------------------------------------------*/
/** @defgroup RNG_Private_Functions RNG Private Functions
  * @{
  */
static hal_status_t RNG_WaitOnFlagUntilTimeout(hal_rng_handle_t *hrng);
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup RNG_Exported_Functions
  * @{
  */

/** @addtogroup RNG_Exported_Functions_Group1
  * @{
This subsection provides a set of functions allowing to initialize an de-initialize the RNG peripheral:
- HAL_RNG_Init() to initialize the selected HAl RNG handle and associate a RNG peripheral instance.
- HAL_RNG_DeInit() to de-initialize the given HAL RNG instance and resetting the state machine.
  */

/**
  * @brief  Initialize the RNG handle and associates an instance.
  * @param  hrng              pointer to @ref hal_rng_handle_t structure.
  * @param  instance          one of the values of the enumeration @ref hal_rng_t.
  * @retval HAL_OK            RNG handle has been correctly initialized.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_RNG_Init(hal_rng_handle_t *hrng, hal_rng_t instance)
{
  ASSERT_DBG_PARAM(hrng != NULL);
  ASSERT_DBG_PARAM(IS_RNG_ALL_INSTANCE((RNG_TypeDef *)(uint32_t)instance));

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
    || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  hrng->instance = instance;

#if defined(USE_HAL_RNG_REGISTER_CALLBACKS) && (USE_HAL_RNG_REGISTER_CALLBACKS == 1)
  hrng->p_generation_cplt_cb = HAL_RNG_GenerationCpltCallback;
  hrng->p_error_cb           = HAL_RNG_ErrorCallback;
#endif /* USE_HAL_RNG_REGISTER_CALLBACKS */

  hrng->p_data = NULL;
  hrng->count  = 0U;

#if defined(USE_HAL_RNG_GET_LAST_ERRORS) && (USE_HAL_RNG_GET_LAST_ERRORS == 1)
  hrng->last_error_codes = HAL_RNG_ERROR_NONE;
#endif /* USE_HAL_RNG_GET_LAST_ERRORS */

#if defined (USE_HAL_RNG_USER_DATA) && (USE_HAL_RNG_USER_DATA == 1)
  hrng->p_user_data = NULL;
#endif /* USE_HAL_RNG_USER_DATA */

#if defined (USE_HAL_RNG_CLK_ENABLE_MODEL) && (USE_HAL_RNG_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_RNG_EnableClock();
#endif /* USE_HAL_RNG_CLK_ENABLE_MODEL */

  hrng->global_state = HAL_RNG_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  DeInitialize the RNG peripheral.
  * @param  hrng pointer to @ref hal_rng_handle_t structure.
  */
void HAL_RNG_DeInit(hal_rng_handle_t *hrng)
{
  ASSERT_DBG_PARAM(hrng != NULL);
  ASSERT_DBG_PARAM(IS_RNG_ALL_INSTANCE(RNG_GET_INSTANCE(hrng)));

  LL_RNG_Disable(RNG_GET_INSTANCE(hrng));

  hrng->global_state = HAL_RNG_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup RNG_Exported_Functions_Group2
  * @{
This subsection provides a set of APIs allowing to configure the RNG peripheral:
- HAL_RNG_SetConfig() set the configuration of the RNG peripheral.
- HAL_RNG_SetCertifiedNISTConfig() set RNG peripheral within a NIST compliant configuration.
- HAL_RNG_SetCandidateNISTConfig() set RNG peripheral within candidate NIST compliant configuration.
- HAL_RNG_SetCandidateGermanBSIConfig() set RNG peripheral within candidate German BSI compliant configuration.
- HAL_RNG_GetConfig() retrieve the RNG peripheral configuration.
- HAL_RNG_EnableClockErrorDetection() enable the clock error detection feature.
- HAL_RNG_DisableClockErrorDetection() disable the clock error detection feature.
- HAL_RNG_IsEnabledClockErrorDetection() check if the clock error detection feature is enabled or not.
- HAL_RNG_EnableAutoReset() enable the auto reset feature.
- HAL_RNG_DisableAutoReset() disable the auto reset feature.
- HAL_RNG_IsEnabledAutoReset() check if the auto reset feature is enabled or not.
- HAL_RNG_SetClockDivider() set the clock divider.
- HAL_RNG_GetClockDivider() retrieve the clock divider value.
  */

/**
  * @brief  Configure the RNG with the specified parameters in the @ref hal_rng_config_t.
  * @param  hrng              pointer to @ref hal_rng_handle_t structure.
  * @param  p_config          pointer to @ref hal_rng_config_t structure.
  * @retval HAL_OK            configuration succeeded.
  * @retval HAL_ERROR         configuration fail.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_RNG_SetConfig(hal_rng_handle_t *hrng, const hal_rng_config_t *p_config)
{
  RNG_TypeDef *p_rngx;
  uint32_t config;
  uint32_t noise_source;
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(hrng != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_RNG_CONFIG1(p_config->config_1));
  ASSERT_DBG_PARAM(IS_RNG_CONFIG2(p_config->config_2));
  ASSERT_DBG_PARAM(IS_RNG_CONFIG3(p_config->config_3));
  ASSERT_DBG_PARAM(IS_RNG_CLOCK_DIVIDER(p_config->clock_divider));
  ASSERT_DBG_PARAM(IS_RNG_STANDARD(p_config->standard));
  ASSERT_DBG_PARAM(IS_RNG_CED(p_config->clock_error_detection));
  ASSERT_DBG_PARAM(IS_RNG_NOISE_SOURCE(p_config->noise_src.osc_1_src));
  ASSERT_DBG_PARAM(IS_RNG_NOISE_SOURCE(p_config->noise_src.osc_2_src));
  ASSERT_DBG_PARAM(IS_RNG_NOISE_SOURCE(p_config->noise_src.osc_3_src));
  ASSERT_DBG_PARAM(IS_RNG_NOISE_SOURCE(p_config->noise_src.osc_4_src));
  ASSERT_DBG_PARAM(IS_RNG_NOISE_SOURCE(p_config->noise_src.osc_5_src));
  ASSERT_DBG_PARAM(IS_RNG_NOISE_SOURCE(p_config->noise_src.osc_6_src));

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_INIT | (uint32_t)HAL_RNG_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  p_rngx  = RNG_GET_INSTANCE(hrng);

  config = ((p_config->config_1  << RNG_CR_RNG_CONFIG1_Pos) | (p_config->config_2  << RNG_CR_RNG_CONFIG2_Pos) \
            | (p_config->config_3 << RNG_CR_RNG_CONFIG3_Pos) | ((uint32_t)p_config->clock_divider)            \
            | ((uint32_t)p_config->clock_error_detection) | ((uint32_t)p_config->standard));

  noise_source = (((uint32_t)p_config->noise_src.osc_1_src << RNG_NSCR_EN_OSC1_Pos)   \
                  | ((uint32_t)p_config->noise_src.osc_2_src << RNG_NSCR_EN_OSC2_Pos) \
                  | ((uint32_t)p_config->noise_src.osc_3_src << RNG_NSCR_EN_OSC3_Pos) \
                  | ((uint32_t)p_config->noise_src.osc_4_src << RNG_NSCR_EN_OSC4_Pos) \
                  | ((uint32_t)p_config->noise_src.osc_5_src << RNG_NSCR_EN_OSC5_Pos) \
                  | ((uint32_t)p_config->noise_src.osc_6_src << RNG_NSCR_EN_OSC6_Pos));
  if (LL_RNG_IsConfigLocked(p_rngx) == 0U)
  {
    LL_RNG_SetConfig(p_rngx, config);
    LL_RNG_WRITE_REG(p_rngx, NSCR, noise_source);
    LL_RNG_SetHealthConfig(p_rngx, (uint32_t)(p_config->health_test));
    LL_RNG_DisableCondReset(p_rngx);
    status = RNG_WaitOnFlagUntilTimeout(hrng);
  }
  return status;
}

#if defined(RNG_CERT_NIST) && (RNG_CERT_NIST == 1)
/**
  * @brief  Configure the RNG with the NIST compliant configuration.
  * @param  hrng              pointer to @ref hal_rng_handle_t structure.
  * @retval HAL_OK            configuration succeeded.
  * @retval HAL_ERROR         configuration fail.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_RNG_SetCertifiedNISTConfig(hal_rng_handle_t *hrng)
{
  RNG_TypeDef *p_rngx;
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(hrng != NULL);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_INIT | (uint32_t)HAL_RNG_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  p_rngx = RNG_GET_INSTANCE(hrng);
  if (LL_RNG_IsConfigLocked(p_rngx) == 0U)
  {
    /* Apply Certified NIST configuration */
    LL_RNG_WRITE_REG(p_rngx, CR, ((uint32_t)RNG_CERT_NIST_CR_VALUE | (uint32_t)RNG_CR_CONDRST));
    LL_RNG_WRITE_REG(p_rngx, NSCR, RNG_CERT_NIST_NSCR_VALUE);
    LL_RNG_WRITE_REG(p_rngx, HTCR, RNG_CERT_NIST_HTCR_VALUE);
    LL_RNG_DisableCondReset(p_rngx);

    status = RNG_WaitOnFlagUntilTimeout(hrng);
  }
  return status;
}
#endif /* RNG_CERT_NIST */

/**
  * @brief  Configure the RNG with the candidate NIST compliant configuration.
  * @param  hrng              pointer to @ref hal_rng_handle_t structure.
  * @retval HAL_OK            configuration succeeded.
  * @retval HAL_ERROR         configuration fail.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_RNG_SetCandidateNISTConfig(hal_rng_handle_t *hrng)
{
  RNG_TypeDef *p_rngx;
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(hrng != NULL);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_INIT | (uint32_t)HAL_RNG_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  p_rngx = RNG_GET_INSTANCE(hrng);

  if (LL_RNG_IsConfigLocked(p_rngx) == 0U)
  {
    /* Apply Candidate NIST configuration */
    LL_RNG_WRITE_REG(p_rngx, CR, ((uint32_t)RNG_CAND_NIST_CR_VALUE | (uint32_t)RNG_CR_CONDRST));
    LL_RNG_WRITE_REG(p_rngx, NSCR, RNG_CAND_NIST_NSCR_VALUE);
    LL_RNG_WRITE_REG(p_rngx, HTCR, RNG_CAND_NIST_HTCR_VALUE);
    LL_RNG_DisableCondReset(p_rngx);

    status = RNG_WaitOnFlagUntilTimeout(hrng);
  }
  return status;
}

/**
  * @brief  Configure the RNG with the candidate German BSI compliant configuration.
  * @param  hrng              pointer to @ref hal_rng_handle_t structure.
  * @retval HAL_OK            configuration succeeded.
  * @retval HAL_ERROR         configuration fail.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_RNG_SetCandidateGermanBSIConfig(hal_rng_handle_t *hrng)
{
  RNG_TypeDef *p_rngx;
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(hrng != NULL);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_INIT | (uint32_t)HAL_RNG_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  p_rngx = RNG_GET_INSTANCE(hrng);
  if (LL_RNG_IsConfigLocked(p_rngx) == 0U)
  {
    /* Apply Candidate GermanBSI configuration */
    LL_RNG_WRITE_REG(p_rngx, CR, ((uint32_t)RNG_CAND_GermanBSI_CR_VALUE | (uint32_t)RNG_CR_CONDRST));
    LL_RNG_WRITE_REG(p_rngx, NSCR, RNG_CAND_GermanBSI_NSCR_VALUE);
    LL_RNG_WRITE_REG(p_rngx, HTCR, RNG_CAND_GermanBSI_HTCR_VALUE);
    LL_RNG_DisableCondReset(p_rngx);

    status = RNG_WaitOnFlagUntilTimeout(hrng);
  }
  return status;
}
/**
  * @brief  Get the RNG configuration and fill parameters in the @ref hal_rng_config_t.
  * @param  hrng     pointer to @ref hal_rng_handle_t structure.
  * @param  p_config pointer to @ref hal_rng_config_t structure.
  *                  module
  */
void HAL_RNG_GetConfig(const hal_rng_handle_t *hrng, hal_rng_config_t *p_config)
{
  RNG_TypeDef *p_rngx;
  uint32_t config_reg;
  uint32_t noise_source;

  ASSERT_DBG_PARAM(hrng != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_IDLE | (uint32_t) HAL_RNG_STATE_ACTIVE \
                   | (uint32_t) HAL_RNG_STATE_ERROR);

  p_rngx     = RNG_GET_INSTANCE(hrng);
  config_reg = LL_RNG_GetConfig(p_rngx);
  noise_source  = LL_RNG_READ_REG(p_rngx, NSCR);

  p_config->config_1              = (config_reg & RNG_CONFIG_1_MASK) >> RNG_CR_RNG_CONFIG1_Pos;
  p_config->config_2              = (config_reg & RNG_CONFIG_2_MASK) >> RNG_CR_RNG_CONFIG2_Pos;
  p_config->config_3              = (config_reg & RNG_CONFIG_3_MASK) >> RNG_CR_RNG_CONFIG3_Pos;
  p_config->clock_divider         = (hal_rng_clock_divider_t)(uint32_t)(config_reg & RNG_CR_CLKDIV_Msk);
  p_config->standard              = (hal_rng_standard_t)(uint32_t)(config_reg & (RNG_NIST_MASK << RNG_CR_NISTC_Pos));
  p_config->clock_error_detection = (hal_rng_clock_error_detection_status_t)   \
                                    (uint32_t)(config_reg & (RNG_CED_MASK << RNG_CR_CED_Pos));
  p_config->health_test           = LL_RNG_GetHealthConfig(p_rngx);
  p_config->noise_src.osc_1_src   = (uint8_t)((noise_source & RNG_NSCR_EN_OSC1_Msk) >> RNG_NSCR_EN_OSC1_Pos);
  p_config->noise_src.osc_2_src   = (uint8_t)((noise_source & RNG_NSCR_EN_OSC2_Msk) >> RNG_NSCR_EN_OSC2_Pos);
  p_config->noise_src.osc_3_src   = (uint8_t)((noise_source & RNG_NSCR_EN_OSC3_Msk) >> RNG_NSCR_EN_OSC3_Pos);
  p_config->noise_src.osc_4_src   = (uint8_t)((noise_source & RNG_NSCR_EN_OSC4_Msk) >> RNG_NSCR_EN_OSC4_Pos);
  p_config->noise_src.osc_5_src   = (uint8_t)((noise_source & RNG_NSCR_EN_OSC5_Msk) >> RNG_NSCR_EN_OSC5_Pos);
  p_config->noise_src.osc_6_src   = (uint8_t)((noise_source & RNG_NSCR_EN_OSC6_Msk) >> RNG_NSCR_EN_OSC6_Pos);
}

/**
  * @brief  Enable the clock error detection feature.
  * @param  hrng              pointer to @ref hal_rng_handle_t structure.
  * @retval HAL_OK            configuration succeeded.
  * @retval HAL_ERROR         configuration fail.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_RNG_EnableClockErrorDetection(hal_rng_handle_t *hrng)
{
  RNG_TypeDef *p_rngx;

  ASSERT_DBG_PARAM(hrng != NULL);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  p_rngx = RNG_GET_INSTANCE(hrng);

  if (LL_RNG_IsConfigLocked(p_rngx) != 0U)
  {
    return HAL_ERROR;
  }

  LL_RNG_EnableClkErrorDetect(p_rngx);

  return HAL_OK;
}

/**
  * @brief  Disable the clock error detection feature.
  * @param  hrng              pointer to @ref hal_rng_handle_t structure.
  * @retval HAL_OK            configuration succeeded.
  * @retval HAL_ERROR         configuration fail.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_RNG_DisableClockErrorDetection(hal_rng_handle_t *hrng)
{
  RNG_TypeDef *p_rngx;

  ASSERT_DBG_PARAM(hrng != NULL);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  p_rngx = RNG_GET_INSTANCE(hrng);

  if (LL_RNG_IsConfigLocked(p_rngx) != 0U)
  {
    return HAL_ERROR;
  }

  LL_RNG_DisableClkErrorDetect(p_rngx);

  return HAL_OK;
}

/**
  * @brief  Check the clock error detection status.
  * @param  hrng                                  pointer to @ref hal_rng_handle_t structure.
  * @retval hal_rng_clock_error_detection_status_t error detection state.
  */
hal_rng_clock_error_detection_status_t HAL_RNG_IsEnabledClockErrorDetection(const hal_rng_handle_t *hrng)
{
  ASSERT_DBG_PARAM(hrng != NULL);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_IDLE | (uint32_t) HAL_RNG_STATE_ACTIVE \
                   | (uint32_t) HAL_RNG_STATE_ERROR);

  return ((hal_rng_clock_error_detection_status_t)
          (uint32_t)(((~LL_RNG_IsEnabledClkErrorDetect(RNG_GET_INSTANCE(hrng))) & RNG_CED_MASK) << RNG_CR_CED_Pos));
}

/**
  * @brief  Enable the automatic reset.
  * @param  hrng              pointer to @ref hal_rng_handle_t structure.
  * @retval HAL_OK            auto-reset enabled successfully.
  * @retval HAL_ERROR         fail to enable the auto-reset.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_RNG_EnableAutoReset(hal_rng_handle_t *hrng)
{
  RNG_TypeDef *p_rngx;

  ASSERT_DBG_PARAM(hrng != NULL);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  p_rngx = RNG_GET_INSTANCE(hrng);

  if (LL_RNG_IsConfigLocked(p_rngx) != 0U)
  {
    return HAL_ERROR;
  }

  LL_RNG_EnableArdis(p_rngx);

  return HAL_OK;
}

/**
  * @brief  Disable the auto reset.
  * @param  hrng pointer to @ref hal_rng_handle_t structure.
  * @retval HAL_OK            auto-reset disabled successfully.
  * @retval HAL_ERROR         fail to disable the auto-reset.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_RNG_DisableAutoReset(hal_rng_handle_t *hrng)
{
  RNG_TypeDef *p_rngx;

  ASSERT_DBG_PARAM(hrng != NULL);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  p_rngx = RNG_GET_INSTANCE(hrng);

  if (LL_RNG_IsConfigLocked(p_rngx) != 0U)
  {
    return HAL_ERROR;
  }

  LL_RNG_DisableArdis(p_rngx);

  return HAL_OK;
}

/**
  * @brief  Check the status of the auto reset.
  * @param  hrng                       pointer to @ref hal_rng_handle_t structure.
  * @retval hal_rng_auto_reset_status_t auto-reset state
  */
hal_rng_auto_reset_status_t HAL_RNG_IsEnabledAutoReset(const hal_rng_handle_t *hrng)
{
  ASSERT_DBG_PARAM(hrng != NULL);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_IDLE | (uint32_t) HAL_RNG_STATE_ACTIVE \
                   | (uint32_t) HAL_RNG_STATE_ERROR);

  return ((hal_rng_auto_reset_status_t)LL_RNG_IsEnabledArdis(RNG_GET_INSTANCE(hrng)));
}

/**
  * @brief  Set RNG  Clock divider factor.
  * @param  hrng        pointer to @ref hal_rng_handle_t structure.
  * @param  clk_divider is a value of the @ref hal_rng_clock_divider_t enumeration.
  * @retval HAL_OK            clock divider set successfully.
  * @retval HAL_ERROR         fail to set the clock divider.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_RNG_SetClockDivider(hal_rng_handle_t *hrng, hal_rng_clock_divider_t clk_divider)
{
  RNG_TypeDef *p_rngx;

  ASSERT_DBG_PARAM(hrng != NULL);
  ASSERT_DBG_PARAM(IS_RNG_CLOCK_DIVIDER(clk_divider));

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  p_rngx = RNG_GET_INSTANCE(hrng);

  if (LL_RNG_IsConfigLocked(p_rngx) != 0U)
  {
    return HAL_ERROR;
  }

  LL_RNG_SetClockDivider(p_rngx, (uint32_t) clk_divider);

  return HAL_OK;
}

/**
  * @brief  Get RNG  Clock divider factor.
  * @param  hrng                    pointer to @ref hal_rng_handle_t structure.
  * @retval hal_rng_clock_divider_t Clock divider.
  */
hal_rng_clock_divider_t HAL_RNG_GetClockDivider(const hal_rng_handle_t *hrng)
{
  ASSERT_DBG_PARAM(hrng != NULL);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_IDLE | (uint32_t) HAL_RNG_STATE_ACTIVE \
                   | (uint32_t) HAL_RNG_STATE_ERROR);

  return ((hal_rng_clock_divider_t) LL_RNG_GetClockDivider(RNG_GET_INSTANCE(hrng)));
}
/**
  * @}
  */

/** @addtogroup RNG_Exported_Functions_Group3
  * @{
This subsection provides a set of APIs allowing to generate random number in polling and interrupt mode :
- HAL_RNG_GenerateRandomNumber() generate a N random number word in polling mode.
- HAL_RNG_GenerateRandomNumber_IT() generate a N random number word in interrupt mode.
- HAL_RNG_IRQHandler() handle RNG interrupt requests.
  */
/**
  * @brief  Generate a N x 32-bit random number in polling mode.
  * @param  hrng              pointer to @ref hal_rng_handle_t structure.
  * @param  p_data            pointer to be filled with random number.
  * @param  size_word         total number of random number to be generated.
  * @param  timeout_ms        timeout in millisecond.
  * @retval HAL_OK            random numbers are generated successfully.
  * @retval HAL_ERROR         seed error occurred when generated random number.
  * @retval HAL_TIMEOUT       timeout occurred when generating random number.
  * @retval HAL_BUSY          process is already ongoing.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_RNG_GenerateRandomNumber(hal_rng_handle_t *hrng, uint32_t *p_data, uint32_t size_word,
                                          uint32_t timeout_ms)
{
  uint32_t *p_temp;
  uint32_t count;
  uint32_t tickstart;
  RNG_TypeDef *p_rngx;

  ASSERT_DBG_PARAM(hrng != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_word > 0U);
  ASSERT_DBG_PARAM(timeout_ms > 0U);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1))\
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_data == NULL) || (size_word == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hrng == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hrng, global_state, HAL_RNG_STATE_IDLE, HAL_RNG_STATE_ACTIVE);

#if defined(USE_HAL_RNG_GET_LAST_ERRORS) && (USE_HAL_RNG_GET_LAST_ERRORS == 1)
  hrng->last_error_codes = HAL_RNG_ERROR_NONE;
#endif /* USE_HAL_RNG_GET_LAST_ERRORS */

  count     = size_word;
  p_temp    = p_data;
  tickstart = HAL_GetTick();
  p_rngx    = RNG_GET_INSTANCE(hrng);

  LL_RNG_Enable(p_rngx);

  while (((HAL_GetTick() - tickstart) < timeout_ms) && (count != 0U))
  {
    if (LL_RNG_IsActiveFlag_SEIS(p_rngx) != 0U)
    {
      if (LL_RNG_IsActiveFlag_SECS(p_rngx) == 0U)
      {
        /* RNG IP performed the reset automatically (auto-reset) */
        LL_RNG_ClearFlag_SEIS(p_rngx);
      }
      else
      {
#if defined(USE_HAL_RNG_GET_LAST_ERRORS) && (USE_HAL_RNG_GET_LAST_ERRORS == 1)
        hrng->last_error_codes = HAL_RNG_ERROR_SEED;
#endif /* USE_HAL_RNG_GET_LAST_ERRORS */
        LL_RNG_Disable(p_rngx);
        hrng->global_state = HAL_RNG_STATE_ERROR;
        return HAL_ERROR;
      }
    }
    /* When a clock error is detected, update the last error code, clear the flag and continue the process operation */
    if (LL_RNG_IsActiveFlag_CEIS(p_rngx) != 0U)
    {
#if defined(USE_HAL_RNG_GET_LAST_ERRORS) && (USE_HAL_RNG_GET_LAST_ERRORS == 1)
      hrng->last_error_codes = HAL_RNG_ERROR_CLOCK;
#endif /* USE_HAL_RNG_GET_LAST_ERRORS */

      LL_RNG_ClearFlag_CEIS(p_rngx);
    }

    while ((LL_RNG_IsActiveFlag_DRDY(p_rngx) != 0U) && (count != 0U))
    {
      *p_temp = LL_RNG_ReadRandData32(p_rngx);
      p_temp++;
      count--;

      if (count == 0U)
      {
        LL_RNG_Disable(p_rngx);
      }
    }
  }

  if ((HAL_GetTick() - tickstart) >= timeout_ms)
  {
    LL_RNG_Disable(p_rngx);
    hrng->global_state = HAL_RNG_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  hrng->global_state = HAL_RNG_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Generate a N x 32-bit random number in interrupt mode.
  * @param  hrng              pointer to @ref hal_rng_handle_t structure.
  * @param  p_data            pointer to be filled with random number.
  * @param  size_word         total number of random number to be generated.
  * @retval HAL_OK            32-bit random number generated successfully.
  * @retval HAL_BUSY          process is already ongoing.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_RNG_GenerateRandomNumber_IT(hal_rng_handle_t *hrng, uint32_t *p_data, uint32_t size_word)
{
  RNG_TypeDef *p_rngx;

  ASSERT_DBG_PARAM(hrng != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_word > 0U);
  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_data == NULL) || (size_word == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hrng, global_state, HAL_RNG_STATE_IDLE, HAL_RNG_STATE_ACTIVE);

  /* Set process information */
  hrng->p_data = p_data;
  hrng->count  = size_word;
  p_rngx       = RNG_GET_INSTANCE(hrng);

  /* Enable the RNG interrupts */
  LL_RNG_EnableIT(p_rngx);
  LL_RNG_Enable(p_rngx);

  return HAL_OK;
}

/**
  * @brief  Handle the RNG interrupt request.
  * @param  hrng pointer to @ref hal_rng_handle_t structure.
  */
void HAL_RNG_IRQHandler(hal_rng_handle_t *hrng)
{
  RNG_TypeDef *p_rngx;
  uint32_t itflags;

  ASSERT_DBG_PARAM(hrng != NULL);

  p_rngx  = RNG_GET_INSTANCE(hrng);
  itflags = LL_RNG_READ_REG(p_rngx, SR);

  if ((itflags & RNG_SR_CEIS) != 0U)
  {
#if defined(USE_HAL_RNG_GET_LAST_ERRORS) && (USE_HAL_RNG_GET_LAST_ERRORS == 1)
    hrng->last_error_codes |= HAL_RNG_ERROR_CLOCK;
#endif /* USE_HAL_RNG_GET_LAST_ERRORS */
    LL_RNG_ClearFlag_CEIS(p_rngx);
  }

  if ((itflags & RNG_SR_SEIS)  != 0U)
  {
    if ((itflags & RNG_SR_SECS) == 0U)
    {
      /* RNG IP performed the reset automatically (auto-reset) */
      LL_RNG_ClearFlag_SEIS(p_rngx);
    }
    else
    {
      LL_RNG_DisableIT(p_rngx);
      LL_RNG_Disable(p_rngx);

#if defined(USE_HAL_RNG_GET_LAST_ERRORS) && (USE_HAL_RNG_GET_LAST_ERRORS == 1)
      /* Seed Error has not been recovered : Update the error code */
      hrng->last_error_codes |= HAL_RNG_ERROR_SEED;
#endif /* USE_HAL_RNG_GET_LAST_ERRORS */

      hrng->global_state = HAL_RNG_STATE_ERROR;
    }
  }

  if ((itflags & (RNG_SR_SEIS | RNG_SR_CEIS)) != 0U)
  {
#if defined (USE_HAL_RNG_REGISTER_CALLBACKS) && (USE_HAL_RNG_REGISTER_CALLBACKS == 1)
    hrng->p_error_cb(hrng);
#else
    HAL_RNG_ErrorCallback(hrng);
#endif /* USE_HAL_RNG_REGISTER_CALLBACKS */

    if ((itflags & RNG_SR_SEIS) != 0U)
    {
      return;
    }
  }

  /* Wait until DRDY flag is set */
  while ((LL_RNG_IsActiveFlag_DRDY(p_rngx) != 0U))
  {
    /* Read 32-bit random data from RNDATA register */
    *hrng->p_data = LL_RNG_ReadRandData32(p_rngx);
    hrng->p_data++;
    hrng->count--;

    if (hrng->count == 0U)
    {
      LL_RNG_DisableIT(p_rngx);
      LL_RNG_Disable(p_rngx);
      hrng->global_state = HAL_RNG_STATE_IDLE;
#if defined (USE_HAL_RNG_REGISTER_CALLBACKS) && (USE_HAL_RNG_REGISTER_CALLBACKS == 1)
      hrng->p_generation_cplt_cb(hrng);
#else
      HAL_RNG_GenerationCpltCallback(hrng);
#endif /* USE_HAL_RNG_REGISTER_CALLBACKS */
      break;
    }
  }
}
/**
  * @}
  */

/** @addtogroup RNG_Exported_Functions_Group4
  * @{
This subsection provides the RNG recover from seed error function :
- HAL_RNG_RecoverSeedError() recover seed error when occurs.
  */
/**
  * @brief  Recover the RNG sequence when a seed error occurs.
  * @param  hrng              pointer to @ref hal_rng_handle_t structure.
  * @retval HAL_OK            operation succeeded
  * @retval HAL_ERROR         operation failed
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_RNG_RecoverSeedError(hal_rng_handle_t *hrng)
{
  RNG_TypeDef *p_rngx;
  __IO uint32_t count = 0U;

  ASSERT_DBG_PARAM(hrng != NULL);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_ERROR);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  p_rngx  = RNG_GET_INSTANCE(hrng);

  LL_RNG_Enable(p_rngx);

  if (LL_RNG_IsActiveFlag_SECS(p_rngx) == 0U)
  {
    /* Clear SEIS flag when automatic reset is activated */
    LL_RNG_ClearFlag_SEIS(p_rngx);
  }
  else
  {
    /* SECS bit is set, which mean a software reset (no auto-reset) by writing CONDRST at 1 and at 0 is needed to
       recover seed */
    LL_RNG_EnableCondReset(p_rngx);
    LL_RNG_DisableCondReset(p_rngx);

    /* Wait for conditioning reset process to be completed */
    count =  RNG_SEED_ERROR_RECOVER_TRIALS;
    do
    {
      count-- ;
      if (count == 0U)
      {
#if defined(USE_HAL_RNG_GET_LAST_ERRORS) && (USE_HAL_RNG_GET_LAST_ERRORS == 1)
        hrng->last_error_codes |= HAL_RNG_ERROR_SEED;
#endif /* USE_HAL_RNG_GET_LAST_ERRORS */
        return HAL_ERROR;
      }
    } while (LL_RNG_IsEnabledCondReset(p_rngx) == 1U);

    /* Confirm that SEIS bit is cleared, otherwise clear it to continue the recover seed process */
    if (LL_RNG_IsActiveFlag_SEIS(p_rngx) != 0U)
    {
      LL_RNG_ClearFlag_SEIS(p_rngx);
    }

    /* wait for SECS to be cleared */
    count =  RNG_SEED_ERROR_RECOVER_TRIALS;
    do
    {
      count-- ;
      if (count == 0U)
      {
#if defined(USE_HAL_RNG_GET_LAST_ERRORS) && (USE_HAL_RNG_GET_LAST_ERRORS == 1)
        hrng->last_error_codes = HAL_RNG_ERROR_SEED;
#endif /* USE_HAL_RNG_GET_LAST_ERRORS */

        return HAL_ERROR;
      }

    } while (LL_RNG_IsActiveFlag_SECS(p_rngx) == 1U);
  }

#if defined(USE_HAL_RNG_GET_LAST_ERRORS) && (USE_HAL_RNG_GET_LAST_ERRORS == 1)
  hrng->last_error_codes &= ~ HAL_RNG_ERROR_SEED;
#endif /* USE_HAL_RNG_GET_LAST_ERRORS */

  LL_RNG_Disable(p_rngx);

  hrng->global_state = HAL_RNG_STATE_IDLE;

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup RNG_Exported_Functions_Group5
  * @{
This subsection provides a set the RNG callbacks registration APIs :
- HAL_RNG_RegisterGenerationCpltCallback() register callback function for interrupts when generate completed.
- HAL_RNG_RegisterErrorCallback() register callback function for interrupts when error occurs.
  */
/**
  * @brief  Handle the RNG error callback.
  * @param  hrng pointer to @ref hal_rng_handle_t structure.
  */
__WEAK void HAL_RNG_ErrorCallback(hal_rng_handle_t *hrng)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hrng);
  /* Warning : This function must not be modified. When the callback is needed,
    *           function HAL_RNG_ErrorCallback must be implemented in the user file.
    */
}

/**
  * @brief  Handle the Random number generation complete callback in non-blocking mode.
  * @param  hrng pointer to @ref hal_rng_handle_t structure.
  */
__WEAK void HAL_RNG_GenerationCpltCallback(hal_rng_handle_t *hrng)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hrng);
  /* Warning : This function must not be modified. When the callback is needed,
    *           function HAL_RNG_GenerationCpltCallback must be implemented in the user file.
    */
}

#if defined (USE_HAL_RNG_REGISTER_CALLBACKS) && (USE_HAL_RNG_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register random number RNG generation complete callback. \n
  *         To be used instead of the weak HAL_RNG_GenerationCpltCallback().
  * @param  hrng              pointer to @ref hal_rng_handle_t structure.
  * @param  callback          pointer to the random number Ready callback function.
  * @retval HAL_OK            succeed.
  * @retval HAL_INVALID_PARAM invalid callback.
  */
hal_status_t HAL_RNG_RegisterGenerationCpltCallback(hal_rng_handle_t *hrng, hal_rng_cb_t callback)
{

  ASSERT_DBG_PARAM((hrng != NULL));
  ASSERT_DBG_PARAM((callback != NULL));

#if (defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  hrng->p_generation_cplt_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Register a User RNG callback. \n
  *         To be used instead of the weak HAL_RNG_RegisterErrorCallback.
  * @param  hrng              pointer to @ref hal_rng_handle_t structure.
  * @param  callback          pointer to the callback function
  * @retval HAL_OK            succeed.
  * @retval HAL_INVALID_PARAM invalid callback.
  */
hal_status_t HAL_RNG_RegisterErrorCallback(hal_rng_handle_t *hrng, hal_rng_cb_t callback)
{
  ASSERT_DBG_PARAM((hrng != NULL));
  ASSERT_DBG_PARAM((callback != NULL));

#if (defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  hrng->p_error_cb = callback;

  return HAL_OK;
}
#endif /* USE_HAL_RNG_REGISTER_CALLBACKS */
/**
  * @}
  */

#if defined (USE_HAL_RNG_USER_DATA) && (USE_HAL_RNG_USER_DATA == 1)
/** @addtogroup RNG_Exported_Functions_Group6
  * @{
This subsection provides a set of functions allowing to Set and Get user data :
- HAL_RNG_SetUserData() store user data pointer into the handle.
- HAL_RNG_GetUserData() retrieve user data pointer from the handle.
  */
/**
  * @brief Store the user data into the RNG handle.
  * @param hrng        pointer to @ref hal_rng_handle_t structure.
  * @param p_user_data pointer to the user data
  */
void HAL_RNG_SetUserData(hal_rng_handle_t *hrng, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hrng != NULL);
  ASSERT_DBG_PARAM(p_user_data != NULL);

  hrng->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the user data from the RNG handle.
  * @param  hrng Pointer to RNG handle
  * @retval Pointer to the user data
  */
const void *HAL_RNG_GetUserData(const hal_rng_handle_t *hrng)
{
  ASSERT_DBG_PARAM(hrng != NULL);

  return (hrng->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_RNG_USER_DATA */

/** @addtogroup RNG_Exported_Functions_Group7
  * @{
This subsection provides a set of functions to retrieve the state and the error codes
- HAL_RNG_GetState() retrieve the global state of the current RNG peripheral.
- HAL_RNG_GetLastErrorCodes() retrieve the last error code of the RNG peripheral.
  */
/**
  * @brief  Return the RNG state.
  * @param  hrng pointer to @ref hal_rng_handle_t structure.
  * @retval hal_rng_state_t RNG global state.
  */
hal_rng_state_t HAL_RNG_GetState(const hal_rng_handle_t *hrng)
{
  ASSERT_DBG_PARAM(hrng != NULL);

  return (hrng->global_state);
}

#if defined(USE_HAL_RNG_GET_LAST_ERRORS) && (USE_HAL_RNG_GET_LAST_ERRORS == 1)
/**
  * @brief  Return the RNG handle error code.
  * @param  hrng pointer to @ref hal_rng_handle_t structure.
  * @retval uint32_t RNG last error codes.
  */
uint32_t HAL_RNG_GetLastErrorCodes(const hal_rng_handle_t *hrng)
{
  ASSERT_DBG_PARAM(hrng != NULL);

  return (hrng->last_error_codes);
}
#endif /* USE_HAL_RNG_GET_LAST_ERRORS */
/**
  * @}
  */

/** @addtogroup RNG_Exported_Functions_Group8
  * @{
This subsection provides a set of functions to lock RNG configuration
- HAL_RNG_LockConfig() lock the RNG configuration.
- HAL_RNG_IsConfigLocked() check if the RNG peripheral configuration is locked or not.
  */
/**
  * @brief   Lock the current RNG  configuration.
  * @warning This function allows to lock RNG peripheral configuration. Once locked, a system reset or RNG peripheral
  *          reset through RCC has to be performed prior any further configuration update.
  * @param   hrng              pointer to @ref hal_rng_handle_t structure.
  * @retval  HAL_OK            configuration locked successfully.
  * @retval  HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_RNG_LockConfig(hal_rng_handle_t *hrng)
{
  ASSERT_DBG_PARAM(hrng != NULL);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hrng == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_RNG_ConfigLock(RNG_GET_INSTANCE(hrng));

  return HAL_OK;
}

/**
  * @brief  Check if RNG Config Lock is enabled.
  * @param  hrng pointer to @ref hal_rng_handle_t structure.
  * @retval hal_rng_lock_config_status_t  RNG lock config state.
  */
hal_rng_lock_config_status_t HAL_RNG_IsConfigLocked(const hal_rng_handle_t *hrng)
{
  ASSERT_DBG_PARAM(hrng != NULL);

  ASSERT_DBG_STATE(hrng->global_state, (uint32_t)HAL_RNG_STATE_IDLE | (uint32_t) HAL_RNG_STATE_ACTIVE \
                   | (uint32_t) HAL_RNG_STATE_ERROR);

  return ((hal_rng_lock_config_status_t) LL_RNG_IsConfigLocked(RNG_GET_INSTANCE(hrng)));
}
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup RNG_Private_Functions RNG Private Functions
  * @{
  */
/**
  * @brief Wait for a flag state until timeout in non-blocking mode.
  * @param  hrng      pointer to @ref hal_rng_handle_t structure.
  * @retval HAL_OK    operation completed successfully.
  * @retval HAL_ERROR operation exceeds the conditioning reset timeout.
  */
static hal_status_t RNG_WaitOnFlagUntilTimeout(hal_rng_handle_t *hrng)
{
  uint32_t tickstart;

  tickstart = HAL_GetTick();
  do
  {
    if (LL_RNG_IsEnabledCondReset(RNG_GET_INSTANCE(hrng)) == 0U)
    {
      hrng->global_state = HAL_RNG_STATE_IDLE;
      return HAL_OK;
    }

  } while ((HAL_GetTick() - tickstart) <= RNG_CONDRST_TIMEOUT_MS);

  return HAL_ERROR;
}
/**
  * @}
  */

#endif /* USE_HAL_RNG_MODULE */
/**
  * @}
  */

/**
  * @}
  */
