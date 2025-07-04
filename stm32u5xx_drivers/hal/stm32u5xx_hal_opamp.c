/**
  ******************************************************************************
  * @file    stm32u5xx_hal_opamp.c
  * @brief   OPAMP HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the operational amplifier(s) peripheral:
  *           + Initialization and de-initialization functions
  *           + Input and output operation functions
  *           + Peripheral Control functions
  *           + Peripheral state functions
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

#if defined(USE_HAL_OPAMP_MODULE) && (USE_HAL_OPAMP_MODULE == 1)
#if defined (OPAMP1) || defined (OPAMP2)

/** @defgroup OPAMP OPAMP
  * @{

  # OPAMP peripheral main features

  ## OPAMP instances

   The U5 device integrates one or two operational amplifiers: OPAMP1 & OPAMP2

  ## OPAMP configuration mode

    The OPAMP provide(s) several exclusive configuration modes.
    - Standalone mode
    - Programmable Gain Amplifier (PGA) mode, with or without external filtering (A capacitor can be connected between
      OPAMP output and inverting input for filtering purpose, refer to reference manual)
    - Follower mode

  ## OPAMP power mode

    Each OPAMP instance can be configured in normal-power or low-power mode.

  ## OPAMP speed mode

    Each OPAMP instance can be configured in normal speed or high speed.


  ## OPAMP calibration feature

    The OPAMP provide(s) calibration capabilities.
    - Calibration aims at improving voltage offset accuracy
    - The OPAMP uses either factory calibration settings or user defined
        calibration settings (i.e. trimming mode).
    - The user trimming values can be figured out by calling calibration
        handled by HAL_OPAMP_Calibrate().
    - HAL_OPAMP_Calibrate()
      - Run automatically the calibration.
      - Enables the user trimming mode.
      - Updates the trimming registers values with fresh calibration results.
         The user might store the calibration results for latter usage
         (for example, monitoring the trimming based on temperature).
    - HAL_OPAMP_CalibrateParallel()
      -  Run calibration in parallel for linked HAL OPAMP handles to speed up calibration processing time.

  ## OPAMP configuration mode:
    ### Standalone mode
    - OPAMP input and output are not internally connected.
      User can implement any circuitry using external components.

    ### Follower mode
    - Inverting Input is connected internally, no external connection on inverting input.

    ### Programmable Gain Amplifier (PGA) mode (Resistor feedback output)

    - The OPAMP output(s) is internally connected to resistor feedback.
    - OPAMP internal programmable gain is either x2, x4, x8 or x16.
      Two usages:
        - inverting output not used, only programmable gain.
        - inverting input used for external filtering coupled with programmable gain
          (ex: connected capacitor for low-pass filtering).

  ## The OPAMPs inverting input
     The OPAMPs inverting input can be selected according to the Reference Manual
        "OPAMP functional description" chapter.

  ## The OPAMPs non inverting input
     The OPAMPs non inverting input can be selected according to the Reference Manual
        "OPAMP functional description" chapter.

  # How to use HAL OPAMP module driver

  ## The OPAMP HAL driver can be used as follows:

  ### How to initialize the OPAMP low level resources:
    - OPAMP bus clock must be enabled to get read and write access to OPAMP registers.

      @note  clock is enabled inside HAL_OPAMP_Init() whenever USE_HAL_OPAMP_CLK_ENABLE_MODEL is not set
             to HAL_CLK_ENABLE_NO.
    - Configure the OPAMP input pins and output pin in analog mode using
      HAL_GPIO_Init() to map the OPAMP output to the GPIO pin.
    - Declare a hal_opamp_handle_t handle structure.
    - Initialize OPAMP instance using HAL_OPAMP_Init().
    - Configure the OPAMP instance with HAL_OPAMP_SetConfig() function.
    - Select the inverting input and the non-inverting input using HAL_OPAMP_SetConfigInputConnection()
    - By default factory trimming is set, else,
      call HAL_OPAMP_Calibrate() or HAL_OPAMP_SetConfigTrimming() functions to use "user trimming" mode
      with the user PMOS and NMOS trimming values.

  ### How to start and stop the OPAMP instances:
    - Start the OPAMP instance using HAL_OPAMP_Start() function.
    - Stop the OPAMP instance using HAL_OPAMP_Stop() function.

  ## Operational amplifier possible pin connections:
    - Cf Reference Manual

  ******************************************************************************
  # Configuration inside the OPAMP driver

  Config defines                | Description          | Default value | Note                                     |
--------------------------------| ---------------------| ------------- | ------------------------------------------
USE_HAL_OPAMP_MODULE            | from hal_conf.h   | 1 | HAL OPAMP module is enabled
USE_HAL_OPAMP_CALIBRATE_PARALLEL| from hal_conf.h   | 0 | enable the parallel calibration
USE_HAL_OPAMP_USER_DATA         | from hal_conf.h   | 0 | enable the user data
USE_HAL_OPAMP_CLK_ENABLE_MODEL  | from hal_conf.h   | HAL_CLK_ENABLE_NO | else clock is enabled inside HAL_OPAMP_Init()
USE_HAL_CHECK_PARAM             | from hal_conf.h   | 0 | to use the run-time checks on function parameters
USE_HAL_CHECK_PROCESS_STATE     | from hal_conf.h   | 0 | to use the run-time checks on the state during processing
USE_ASSERT_DBG_PARAM            | Pre-processor env | None | to use the assert checks on function parameters
USE_ASSERT_DBG_STATE            | Pre-processor env | None | to use the assert checks on module state

  ******************************************************************************
  */

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup OPAMP_Private_Constants OPAMP Private Constants
  * @brief   OPAMP Private constants and defines
  * @{
  */
#define OPAMP_STATE_ALL (((uint32_t) HAL_OPAMP_STATE_IDLE)  \
                         | ((uint32_t) HAL_OPAMP_STATE_ACTIVE))  /*!< OPAMP all states except RESET and CALIB */

/* Non inverting input bit position in OTR and LPOTR (ie PMOS) */
#define OPAMP_TRIM_PMOS_BIT_SHIFT  (OPAMP_OTR_TRIMOFFSETP_Pos) /*!< Bit shift in trimming register OTR or LPOTR
                                                                    for non inverting input (ie PMOS)*/

/* Offset trimming time: during calibration, minimum time needed between two  */
/* steps to have 1 mV accuracy.                                               */
/* The CALOUT flag needs up to 1 ms after the trimming value is changed to become steady */
/* Unit: ms.                                                                  */
#define OPAMP_TRIMMING_DELAY_MS      ((uint32_t) 1U)  /*!< Trimming delay in milli-seconds */

/**
  * @}
  */

/* Private macros -------------------------------------------------------------*/
/** @defgroup OPAMP_Private_Macros OPAMP Private Macros
  * @{
  */

/*! Retrieve OPAMP instance from handle */
#define OPAMP_GET_INSTANCE(hopamp) ((OPAMP_TypeDef *)((uint32_t)((hopamp)->instance)))

/*! Check configuration mode */
#define IS_OPAMP_CONFIGURATION_MODE(mode) (((mode) == HAL_OPAMP_MODE_STANDALONE) \
                                           || ((mode) == HAL_OPAMP_MODE_PGA) \
                                           || ((mode) == HAL_OPAMP_MODE_FOLLOWER))

/*! Check non inverting input for STANDALONE, FOLLOWER, or PGA */
#define IS_OPAMP_NON_INVERTING_INPUT(input) (((input) ==  HAL_OPAMP_NON_INVERTING_INPUT_GPIO) \
                                             || ((input) ==  HAL_OPAMP_NON_INVERTING_INPUT_DAC))

/*! Check inverting input */
#define IS_OPAMP_INVERTING_INPUT(input) (((input) ==  HAL_OPAMP_INVERTING_INPUT_GPIO_0) \
                                         || ((input) ==  HAL_OPAMP_INVERTING_INPUT_GPIO_1) \
                                         || ((input) ==  HAL_OPAMP_INVERTING_INPUT_NO_EXT_CON))

/*! Check inverting input for standalone configuration */
#define IS_OPAMP_INVERTING_INPUT_STANDALONE(input)  (((input) ==  HAL_OPAMP_INVERTING_INPUT_GPIO_0) \
                                                     || ((input) ==  HAL_OPAMP_INVERTING_INPUT_GPIO_1))

/*! Check inverting input for follower configuration */
#define IS_OPAMP_INVERTING_INPUT_FOLLOWER(input) (1U) /* In FOLLOWER mode inverting input is not applicable */

/*! Check inverting input for PGA configuration */
#define IS_OPAMP_INVERTING_INPUT_PGA(input)  (((input) ==  HAL_OPAMP_INVERTING_INPUT_GPIO_0) \
                                              || ((input) ==  HAL_OPAMP_INVERTING_INPUT_GPIO_1) \
                                              || ((input) ==  HAL_OPAMP_INVERTING_INPUT_NO_EXT_CON))

/*! Check PGA gain */
#define IS_OPAMP_PGA_GAIN(gain) (((gain) == HAL_OPAMP_PGA_GAIN_2) \
                                 || ((gain) == HAL_OPAMP_PGA_GAIN_4) \
                                 || ((gain) == HAL_OPAMP_PGA_GAIN_8) \
                                 || ((gain) == HAL_OPAMP_PGA_GAIN_16))

/*! Check power mode */
#define IS_OPAMP_POWER_MODE(power_mode) (((power_mode) == HAL_OPAMP_POWER_MODE_NORMAL) \
                                         || ((power_mode) == HAL_OPAMP_POWER_MODE_LOW))

/*! Check speed mode */
#define IS_OPAMP_SPEED_MODE(speed_mode) (((speed_mode) == HAL_OPAMP_SPEED_MODE_NORMAL) \
                                         || ((speed_mode) == HAL_OPAMP_SPEED_MODE_HIGH))

/*! Check trimming mode */
#define IS_OPAMP_TRIMMING_MODE(trimming_mode) (((trimming_mode) == HAL_OPAMP_TRIMMING_FACTORY) \
                                               || ((trimming_mode) == HAL_OPAMP_TRIMMING_USER))

/*! Check trimming value */
#define IS_OPAMP_TRIMMING_VALUE(trimming_value) ((trimming_value) <= 31U)

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @addtogroup OPAMP_Private_Variables OPAMP Private Variables
  * @{
  */

/**
  * @}
  */

/* Private functions prototypes ---------------------------------------------------------*/
/** @defgroup OPAMP_Private_Functions OPAMP Private Functions
  * @{
  */
#if defined(USE_HAL_OPAMP_CALIBRATE_PARALLEL) && (USE_HAL_OPAMP_CALIBRATE_PARALLEL == 1)
static void OPAMP_SetLinkNextHandle(hal_opamp_handle_t *hopamp_x, hal_opamp_handle_t *hopamp_y);

static void OPAMP_CalibrateParallel(hal_opamp_handle_t *hopamp,
                                    hal_opamp_power_mode_t power_mode, uint32_t max_nb_opamp);
#else
static void OPAMP_CalibrateSingle(hal_opamp_handle_t *hopamp, hal_opamp_power_mode_t power_mode);
#endif /* USE_HAL_OPAMP_CALIBRATE_PARALLEL */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup OPAMP_Exported_Functions OPAMP Exported Functions
  * @{
  */

/** @defgroup OPAMP_Exported_Functions_Group1 Initialization, de-initialization, configuration, calibration functions
    This section provides functions allowing to:
      + initialize the OPAMP,
      + de-initialize the OPAMP,
      + configure the OPAMP,
      + calibration setting.
  * @{
  */

/**
  * @brief  Initializes the OPAMP according to the specified
  *         parameters in the hal_opamp_config_t and initialize the associated handle.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @param  instance A OPAMP hardware peripheral base address.
  * @note   After calling this function the OPAMP jump to HAL_OPAMP_STATE_IDLE, and it is possible
  *         to call directly HAL_OPAMP_Start() without calling HAL_OPAMP_SetConfig().\n
  *         The OPAMP default configuration parameters are:
  *         + OPAMP is disabled
  *         + normal mode operation (ie: not in calibration mode)
  *         + normal power mode
  *         + normal speed mode
  *         + standalone configuration
  *         + PGA gain x2
  *         + GPIO connected to non-inverting input
  *         + GPIO connected to inverting input
  * @retval HAL_OK OPAMP Instance has been correctly initialized.
  * @retval HAL_INVALID_PARAM A parameter is invalid.
  */
hal_status_t HAL_OPAMP_Init(hal_opamp_handle_t *hopamp, hal_opamp_t instance)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM((hopamp != NULL));

  ASSERT_DBG_PARAM(IS_OPAMP_ALL_INSTANCE((OPAMP_TypeDef *)((uint32_t)instance)));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hopamp == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hopamp->instance = instance;

#if defined(USE_HAL_OPAMP_CALIBRATE_PARALLEL) && (USE_HAL_OPAMP_CALIBRATE_PARALLEL == 1)
  hopamp->p_next_link = hopamp; /* by default only one element in the circular linked list */
#endif /* USE_HAL_OPAMP_CALIBRATE_PARALLEL */

#if defined(USE_HAL_OPAMP_USER_DATA) && (USE_HAL_OPAMP_USER_DATA == 1)
  hopamp->p_user_data = NULL;
#endif /* USE_HAL_OPAMP_USER_DATA */

#if defined(USE_HAL_OPAMP_CLK_ENABLE_MODEL) && (USE_HAL_OPAMP_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_OPAMP_EnableClock();
#endif /* USE_HAL_OPAMP_CLK_ENABLE_MODEL */

  /* This bit must be set before enabling the OPAMP.
     The RANGE bit is a common configuration for all OPAMP instances and it must be set to high
  */
  LL_OPAMP_SetCommonPowerRange((OPAMP_Common_TypeDef *)LL_OPAMP_COMMON_INSTANCE(instance),
                               LL_OPAMP_POWERSUPPLY_RANGE_HIGH);

  hopamp->global_state = HAL_OPAMP_STATE_IDLE;

  return status;
}

/**
  * @brief  DeInitialize the OPAMP peripheral.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @note   Stop the OPAMP and restore the state machine to reset state.
  */
void HAL_OPAMP_DeInit(hal_opamp_handle_t *hopamp)
{
  OPAMP_TypeDef *p_instance;

  ASSERT_DBG_PARAM((hopamp != NULL));

  p_instance = OPAMP_GET_INSTANCE(hopamp);
  ASSERT_DBG_PARAM(IS_OPAMP_ALL_INSTANCE(p_instance));

#if defined(USE_HAL_OPAMP_CALIBRATE_PARALLEL) && (USE_HAL_OPAMP_CALIBRATE_PARALLEL == 1)
  OPAMP_SetLinkNextHandle(hopamp, hopamp);  /* by default only one element in the circular linked list */
#endif /* USE_HAL_OPAMP_CALIBRATE_PARALLEL */

#if defined (USE_HAL_OPAMP_USER_DATA) && (USE_HAL_OPAMP_USER_DATA == 1)
  hopamp->p_user_data = NULL;
#endif /* USE_HAL_OPAMP_USER_DATA */

  /* OPAMP must be disabled first separately */
  LL_OPAMP_Disable(p_instance);  /* OPAMP must be disabled first separately */

  /* Then set OPAMP_CSR register to reset value */
  /* Mind that CSR RANGE bit of OPAMP1 remains unchanged (applies to both OPAMPs) */
  LL_OPAMP_ResetConfig(p_instance);

  hopamp->global_state = HAL_OPAMP_STATE_RESET;
}

/**
  * @brief  Configure the OPAMP peripheral according to the specified parameters in the hal_opamp_config_t.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @param  p_config  The configuration that contains information for the specified OPAMP.
  * @retval HAL_OK OPAMP Instance has been correctly configured.
  * @retval HAL_INVALID_PARAM If p_config is NULL
  */
hal_status_t HAL_OPAMP_SetConfig(hal_opamp_handle_t *hopamp, const hal_opamp_config_t *p_config)
{
  OPAMP_TypeDef *p_instance;
  hal_opamp_inverting_input_t     inverting_input;
  hal_opamp_non_inverting_input_t non_inverting_input;

  ASSERT_DBG_PARAM((hopamp != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

  ASSERT_DBG_PARAM(IS_OPAMP_POWER_MODE(p_config->power_mode));
  ASSERT_DBG_PARAM(IS_OPAMP_SPEED_MODE(p_config->speed_mode));
  ASSERT_DBG_PARAM(IS_OPAMP_CONFIGURATION_MODE(p_config->configuration_mode));

  ASSERT_DBG_STATE(hopamp->global_state, HAL_OPAMP_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_instance = OPAMP_GET_INSTANCE(hopamp);

  /* Set OPAMP input connections according to the configuration mode */
  switch (p_config->configuration_mode)
  {
    case HAL_OPAMP_MODE_PGA:
      inverting_input         = HAL_OPAMP_INVERTING_INPUT_GPIO_0;
      non_inverting_input     = HAL_OPAMP_NON_INVERTING_INPUT_GPIO;
      break;

    case HAL_OPAMP_MODE_FOLLOWER:
      inverting_input         = HAL_OPAMP_INVERTING_INPUT_NO_EXT_CON;
      non_inverting_input     = HAL_OPAMP_NON_INVERTING_INPUT_GPIO;
      break;

    case HAL_OPAMP_MODE_STANDALONE:
    default:
      inverting_input         = HAL_OPAMP_INVERTING_INPUT_GPIO_0;
      non_inverting_input     = HAL_OPAMP_NON_INVERTING_INPUT_GPIO;
      break;
  }

  /* Configure CSR bits: functional mode, power mode, speed mode, configuration mode, inputs */
  LL_OPAMP_SetConfig(p_instance, ((uint32_t)(LL_OPAMP_MODE_FUNCTIONAL)  /* Set normal operating mode */
                                  | (uint32_t)(p_config->power_mode)
                                  | (uint32_t)(p_config->speed_mode)
                                  | (uint32_t)(p_config->configuration_mode)
                                  | (uint32_t)(inverting_input)
                                  | (uint32_t)(non_inverting_input)
                                 ));

  return HAL_OK;
}

/**
  * @brief  Return the configuration parameters of the OPAMP peripheral
  *         in the hal_opamp_config_t.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @param  p_config The configuration parameters.
  */
void HAL_OPAMP_GetConfig(const hal_opamp_handle_t *hopamp, hal_opamp_config_t *p_config)
{
  const OPAMP_TypeDef *p_instance;
  uint32_t reg_value;

  ASSERT_DBG_PARAM((hopamp != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

  ASSERT_DBG_STATE(hopamp->global_state, OPAMP_STATE_ALL);

  p_instance = OPAMP_GET_INSTANCE(hopamp);

  /* Fill config structure parameter */
  reg_value = LL_OPAMP_GetConfig(p_instance);

  p_config->power_mode  = (hal_opamp_power_mode_t)((uint32_t)(reg_value & (OPAMP_CSR_OPALPM)));
  p_config->speed_mode  = (hal_opamp_speed_mode_t)((uint32_t)(reg_value & (OPAMP_CSR_HSM)));
  p_config->configuration_mode = (hal_opamp_config_mode_t)((uint32_t)(reg_value & (OPAMP_CSR_OPAMODE)));
}

/**
  * @brief  Reset the configuration parameters of the OPAMP peripheral.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @note   Configuration parameters of the OPAMP are reset to:
  *         + OPAMP is disabled
  *         + normal mode operation (ie: not in calibration mode)
  *         + normal power mode
  *         + normal speed mode
  *         + standalone configuration
  *         + PGA gain x2
  *         + GPIO connected to non-inverting input
  *         + GPIO connected to inverting input
  */
void  HAL_OPAMP_ResetConfig(hal_opamp_handle_t *hopamp)
{
  OPAMP_TypeDef *p_instance;

  ASSERT_DBG_PARAM((hopamp != NULL));

  p_instance = OPAMP_GET_INSTANCE(hopamp);

  ASSERT_DBG_STATE(hopamp->global_state, ((uint32_t)HAL_OPAMP_STATE_IDLE));

  LL_OPAMP_Disable(p_instance);

  /* Set some CSR bits to reset value */
  /* Mind that CSR RANGE bit of OPAMP remains unchanged (applies to both OPAMPs) */
  LL_OPAMP_ResetConfig(p_instance);
}

/**
  * @brief  Run the self calibration of one OPAMP according to power mode.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @param  power_mode Low_power or normal_power.
  * @note   At the end of calibration offset trimming values (PMOS & NMOS) are updated,
  *         user trimming is enabled, and the initial configuration mode is restored.
  * @note   Calibration runs about 10 ms (5 dichotomy steps, repeated for P
  *         and N transistors: 10 steps with 1 ms for each step).
  * @retval HAL_OK OPAMP Instance calibration has been correctly done.
  * @retval HAL_INVALID_PARAM A parameter is invalid.
  * @retval HAL_BUSY If the define USE_HAL_CHECK_PROCESS_STATE is set to "1" and the current state doesn't match
  *                  HAL_OPAMP_STATE_IDLE.
  */
hal_status_t HAL_OPAMP_Calibrate(hal_opamp_handle_t *hopamp, hal_opamp_power_mode_t power_mode)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM((hopamp != NULL));
  ASSERT_DBG_PARAM(IS_OPAMP_POWER_MODE(power_mode));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hopamp == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hopamp->global_state, (uint32_t)HAL_OPAMP_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hopamp, global_state, HAL_OPAMP_STATE_IDLE, HAL_OPAMP_STATE_CALIB);

#if defined(USE_HAL_OPAMP_CALIBRATE_PARALLEL) && (USE_HAL_OPAMP_CALIBRATE_PARALLEL == 1)
  OPAMP_CalibrateParallel(hopamp, power_mode, 1); /* 1: to force a single calibration although there might be more
                                                     than one element in the circular list */
#else
  OPAMP_CalibrateSingle(hopamp, power_mode); /* Calibration for a single OPAMP instance */
#endif /* USE_HAL_OPAMP_CALIBRATE_PARALLEL */

  hopamp->global_state = HAL_OPAMP_STATE_IDLE;

  return status;
}

#if defined(USE_HAL_OPAMP_CALIBRATE_PARALLEL) && (USE_HAL_OPAMP_CALIBRATE_PARALLEL == 1)
/**
  * @brief  Run the self calibration of the opamp chained instances in parallel according to the specified power mode.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure,
  *                this handle contains a linked list of OPAMP handle to be calibrated.
  * @param  power_mode Low_power or normal_power.
  * @note   Running all calibration in parallel reduce total calibration time.
  * @note   The head of the chained list of OPAMP handles is hopamp itself, the next element must have been linked
  *         previously by calling HAL_OPAMP_SetLinkNextHandle(hopamp_x, hopamp_y).
  * @note   At the end of calibration, for each opamp, offset trimming values (PMOS & NMOS) are updated,
            user trimming mode is enabled whenever calibration is successful,
            and the initial configuration mode is restored.
  * @note   Calibration runs about 10 ms (5 dichotomy steps, repeated for P
  *         and N transistors: 10 steps with 1 ms for each step).
  * @retval HAL_OK OPAMP Chained instances parallel calibration has been correctly done.
  * @retval HAL_INVALID_PARAM A parameter is invalid.
  * @retval HAL_BUSY If the define USE_HAL_CHECK_PROCESS_STATE is set to "1" and the current state doesn't match
  *                  HAL_OPAMP_STATE_IDLE.
  */
hal_status_t HAL_OPAMP_CalibrateParallel(hal_opamp_handle_t *hopamp, hal_opamp_power_mode_t power_mode)
{
  hal_status_t status = HAL_OK;
  hal_opamp_handle_t *hopamp_current;

  ASSERT_DBG_PARAM((hopamp != NULL));
  ASSERT_DBG_PARAM(IS_OPAMP_POWER_MODE(power_mode));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hopamp == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hopamp->global_state, (uint32_t)HAL_OPAMP_STATE_IDLE);

  hopamp_current = hopamp;
  do
  {
    HAL_CHECK_UPDATE_STATE(hopamp_current, global_state, HAL_OPAMP_STATE_IDLE, HAL_OPAMP_STATE_CALIB);
    hopamp_current = hopamp_current->p_next_link;
  } while (hopamp_current != hopamp);

  OPAMP_CalibrateParallel(hopamp, power_mode, OPAMP_INSTANCES_NB);

  hopamp_current = hopamp;
  do
  {
    hopamp_current->global_state = HAL_OPAMP_STATE_IDLE;
    hopamp_current = hopamp_current->p_next_link;
  } while (hopamp_current != hopamp);

  return status;
}

/**
  * @brief  Set hopamp_y handle element inside the circular list of hopamp_x handle.
  * @param  hopamp_x Pointer to a hal_opamp_handle_t structure, this is the first linked element.
  * @param  hopamp_y Pointer to a hal_opamp_handle_t structure, this is the second linked element
  *                  to be inserted in the circular list of the first element.
  *                  By the way hopamp_y is removed from other non-singleton list.
  * @note   This function must be called to build a circular chained list of OPAMP handles
  *         that is calibrated later in parallel time when calling HAL_OPAMP_CalibrateParallel().
  *         Handles must not be NULL.
  * @note   To remove a handle element from all chains, call this function with same handles in both params.
  * @retval HAL_OK OPAMP instances linkage has been correctly done.
  */
hal_status_t HAL_OPAMP_SetLinkNextHandle(hal_opamp_handle_t *hopamp_x, hal_opamp_handle_t *hopamp_y)
{
  ASSERT_DBG_PARAM((hopamp_x != NULL));
  ASSERT_DBG_PARAM((hopamp_y != NULL));

  ASSERT_DBG_STATE(hopamp_x->global_state, (uint32_t)HAL_OPAMP_STATE_IDLE);
  ASSERT_DBG_STATE(hopamp_y->global_state, (uint32_t)HAL_OPAMP_STATE_IDLE);

  OPAMP_SetLinkNextHandle(hopamp_x, hopamp_y);

  return HAL_OK;
}
#endif /* USE_HAL_OPAMP_CALIBRATE_PARALLEL */

/**
  * @brief  Set the OPAMP peripheral offset trimming values according to the specified parameters in
  *         the hal_opamp_trimming_config_t, for normal-power or low-power mode.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @param  p_config  The offset trimming configuration that contains information for the specified OPAMP.
  * @param  power_mode Normal-power or low-power mode.
  * @retval HAL_OK OPAMP Instance offset trimming has been correctly configured.
  * @retval HAL_INVALID_PARAM If p_config is NULL
  */
hal_status_t HAL_OPAMP_SetConfigTrimming(const hal_opamp_handle_t *hopamp,
                                         const hal_opamp_trimming_offset_pair_t *p_config,
                                         hal_opamp_power_mode_t power_mode)
{
  OPAMP_TypeDef *p_instance;
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM((hopamp != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(IS_OPAMP_POWER_MODE(power_mode));

  ASSERT_DBG_PARAM(IS_OPAMP_TRIMMING_VALUE(p_config->trim_offset_p));
  ASSERT_DBG_PARAM(IS_OPAMP_TRIMMING_VALUE(p_config->trim_offset_n));

  ASSERT_DBG_STATE(hopamp->global_state, HAL_OPAMP_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_instance = OPAMP_GET_INSTANCE(hopamp);

  /* Set user calibration mode */
  LL_OPAMP_SetTrimmingMode(p_instance, LL_OPAMP_TRIMMING_USER);

  /* Set values for transistors differential pair high (PMOS) and low (NMOS) */
  LL_OPAMP_SetOffsetTrimAllValue(p_instance, (uint32_t) power_mode, p_config->trim_offset_p, p_config->trim_offset_n);

  return status;
}

/**
  * @brief  Get the OPAMP peripheral offset trimming values for normal-power or low-power mode.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @param  p_config The retrieved offset trimming values that contain information for the specified OPAMP.
  * @param  power_mode Low_power or normal_power.
  * @note   Careful: to retrieve the factory offset trimming pairs, this function must be called when
  *         OPAMP trimming_mode is still set to trimming factory,
  *         this means before:
  *          - OPAMP calibration process,
  *            (call of HAL_OPAMP_Calibrate()),
  *          - and before a user trimming has been set,
  *            (call of HAL_OPAMP_SetConfigTrimming()),
  *         Otherwise, the user trimming values are retrieved.
  */
void HAL_OPAMP_GetConfigTrimming(const hal_opamp_handle_t *hopamp,
                                 hal_opamp_trimming_offset_pair_t *p_config,
                                 hal_opamp_power_mode_t power_mode)
{
  const OPAMP_TypeDef *p_instance;
  uint32_t read_value;

  ASSERT_DBG_PARAM((hopamp != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(IS_OPAMP_POWER_MODE(power_mode));

  ASSERT_DBG_STATE(hopamp->global_state, OPAMP_STATE_ALL);

  p_instance = OPAMP_GET_INSTANCE(hopamp);
  /* Read trimming value in the register depending of power mode (OTR or LPOTR) */
  read_value = LL_OPAMP_GetOffsetTrimAllValue(p_instance, (uint32_t) power_mode);

  p_config->trim_offset_n  = read_value & OPAMP_OTR_TRIMOFFSETN_Msk;
  p_config->trim_offset_p  = ((read_value >> OPAMP_TRIM_PMOS_BIT_SHIFT) & OPAMP_OTR_TRIMOFFSETN_Msk);
}

/**
  * @brief  Get the user trimming mode for OPAMP peripheral.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @retval HAL_OPAMP_TRIMMING_MODE_FACTORY If this function has been called before:
  *          - OPAMP calibration process, (call of HAL_OPAMP_Calibrate() or HAL_OPAMP_CalibrateParallel()),
  *          - and before a user trimming has been set, (call of HAL_OPAMP_SetConfigTrimming()).
  * @retval HAL_OPAMP_TRIMMING_MODE_USER After a call to one of the above functions.
  */
hal_opamp_trimming_mode_t HAL_OPAMP_GetTrimmingMode(const hal_opamp_handle_t *hopamp)
{
  OPAMP_TypeDef *p_instance;
  hal_opamp_trimming_mode_t trimming_mode;

  ASSERT_DBG_PARAM((hopamp != NULL));

  ASSERT_DBG_STATE(hopamp->global_state, OPAMP_STATE_ALL);

  p_instance = OPAMP_GET_INSTANCE(hopamp);
  trimming_mode = (hal_opamp_trimming_mode_t) LL_OPAMP_GetTrimmingMode(p_instance);

  return trimming_mode;
}

/**
  * @}
  */

/** @defgroup OPAMP_Exported_Functions_Group2 Output operation functions
  * This section provides functions allowing to:
      + start the OPAMP,
      + stop  the OPAMP.
  * @{
  */

/**
  * @brief  Start the OPAMP.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @retval HAL_OK
  */
hal_status_t HAL_OPAMP_Start(hal_opamp_handle_t *hopamp)
{
  OPAMP_TypeDef *p_instance;

  ASSERT_DBG_PARAM((hopamp != NULL));

  ASSERT_DBG_STATE(hopamp->global_state, HAL_OPAMP_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hopamp, global_state, HAL_OPAMP_STATE_IDLE, HAL_OPAMP_STATE_ACTIVE);

  p_instance = OPAMP_GET_INSTANCE(hopamp);
  LL_OPAMP_Enable(p_instance);

  return HAL_OK;
}

/**
  * @brief  Stop the OPAMP.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @retval HAL_OK
  */
hal_status_t HAL_OPAMP_Stop(hal_opamp_handle_t *hopamp)
{
  OPAMP_TypeDef *p_instance;

  ASSERT_DBG_PARAM((hopamp != NULL));

  ASSERT_DBG_STATE(hopamp->global_state, HAL_OPAMP_STATE_ACTIVE);

  p_instance = OPAMP_GET_INSTANCE(hopamp);
  LL_OPAMP_Disable(p_instance);

  hopamp->global_state = HAL_OPAMP_STATE_IDLE;

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup OPAMP_Exported_Functions_Group3 Peripheral Control functions
    This section provides functions allowing to set and control the OPAMP main features:
      + the configuration of input connection,
      + the Programmable Gain Amplifier gain.
  * @{
  */

/**
  * @brief  Configure input connection of the OPAMP peripheral according to
  *         the specified parameters in the hal_opamp_config_input_connection_t.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @param  p_config The configuration that contains input connections for the specified OPAMP.
  * @retval HAL_OK OPAMP Instance input connections has been correctly configured.
  * @retval HAL_INVALID_PARAM If p_config is NULL.
  */
hal_status_t HAL_OPAMP_SetConfigInputConnection(const hal_opamp_handle_t *hopamp,
                                                const hal_opamp_config_input_connection_t *p_config)
{
  OPAMP_TypeDef *p_instance;

  ASSERT_DBG_PARAM((hopamp != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_OPAMP_NON_INVERTING_INPUT(p_config->non_inverting_input));

  p_instance = OPAMP_GET_INSTANCE(hopamp);

#if defined(USE_ASSERT_DBG_PARAM)
  /* check available input according to configuration mode */
  /* get configuration mode */
  hal_opamp_config_mode_t configuration_mode;
  configuration_mode = (hal_opamp_config_mode_t) LL_OPAMP_GetConfigurationMode(p_instance);

  if (configuration_mode == HAL_OPAMP_MODE_PGA)
  {
    ASSERT_DBG_PARAM(IS_OPAMP_INVERTING_INPUT_PGA(p_config->inverting_input));
  }
  else if (configuration_mode == HAL_OPAMP_MODE_STANDALONE)
  {
    ASSERT_DBG_PARAM(IS_OPAMP_INVERTING_INPUT_STANDALONE(p_config->inverting_input));
  }
  /* In HAL_OPAMP_MODE_FOLLOWER configuration the inverting_input is not applicable, no ASSERT on inverting_input */
#endif /* USE_ASSERT_DBG_PARAM */

  ASSERT_DBG_STATE(hopamp->global_state, (uint32_t)HAL_OPAMP_STATE_IDLE);

  /* Set OPAMP inputs connections */
  LL_OPAMP_SetInputs(p_instance, (uint32_t)p_config->non_inverting_input, (uint32_t)p_config->inverting_input);

  return HAL_OK;
}

/**
  * @brief  Get the input connection of the OPAMP peripheral.
  *         the specified parameters in the hal_opamp_config_input_connection_t.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @param  p_config Structure that contains input connection for the specified OPAMP.
  */
void HAL_OPAMP_GetConfigInputConnection(const hal_opamp_handle_t *hopamp,
                                        hal_opamp_config_input_connection_t *p_config)
{
  OPAMP_TypeDef *p_instance;
  uint32_t vp_vm_inputs;
  ASSERT_DBG_PARAM((hopamp != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

  ASSERT_DBG_STATE(hopamp->global_state, (uint32_t)OPAMP_STATE_ALL);

  p_instance = OPAMP_GET_INSTANCE(hopamp);

  vp_vm_inputs = LL_OPAMP_GetInputs(p_instance);
  p_config->inverting_input     = (hal_opamp_inverting_input_t)((uint32_t)(vp_vm_inputs & (OPAMP_CSR_VM_SEL)));
  p_config->non_inverting_input = (hal_opamp_non_inverting_input_t)((uint32_t)(vp_vm_inputs & (OPAMP_CSR_VP_SEL)));
}

/**
  * @brief  Set the PGA gain to be used when the OPAMP is configured in Programmable Gain Amplifier (OPAMP_PGA_MODE).
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @param  gain specifies the gain (x2, x4, x8 or x16) in PGA mode
  * @retval HAL_OK  The PGA gain has been correctly set.
  * @retval HAL_ERROR If a parameter is invalid.
  */
hal_status_t HAL_OPAMP_SetGain(const hal_opamp_handle_t *hopamp, hal_opamp_pga_gain_t gain)
{
  OPAMP_TypeDef *p_instance;

  ASSERT_DBG_PARAM((hopamp != NULL));
  ASSERT_DBG_PARAM(IS_OPAMP_PGA_GAIN(gain));

  ASSERT_DBG_STATE(hopamp->global_state, (uint32_t)HAL_OPAMP_STATE_IDLE);

  p_instance = OPAMP_GET_INSTANCE(hopamp);
  LL_OPAMP_SetPGAGain(p_instance, (uint32_t) gain);

  return HAL_OK;
}

/**
  * @brief  Get the PGA gain used when the OPAMP is configured in Programmable Gain Amplifier (OPAMP_PGA_MODE).
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @retval HAL_OPAMP_PGA_GAIN_2   When PGA gain is x2.
  * @retval HAL_OPAMP_PGA_GAIN_4   When PGA gain is x4.
  * @retval HAL_OPAMP_PGA_GAIN_8   When PGA gain is x8.
  * @retval HAL_OPAMP_PGA_GAIN_16  When PGA gain is x16.
  */
hal_opamp_pga_gain_t HAL_OPAMP_GetGain(const hal_opamp_handle_t *hopamp)
{
  OPAMP_TypeDef *p_instance;
  hal_opamp_pga_gain_t gain;

  ASSERT_DBG_PARAM((hopamp != NULL));

  ASSERT_DBG_STATE(hopamp->global_state, (uint32_t)OPAMP_STATE_ALL);

  p_instance = OPAMP_GET_INSTANCE(hopamp);

  gain = (hal_opamp_pga_gain_t) LL_OPAMP_GetPGAGain(p_instance);
  return gain;
}

/**
  * @}
  */

/** @defgroup OPAMP_Exported_Functions_Group4 Peripheral state functions
    This subsection permits to get in run-time the status of the peripheral:
      + retrieve the HAL OPAMP handle state.
  * @{
  */

/**
  * @brief  Return the OPAMP handle state.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure.
  * @retval HAL_OPAMP_STATE_RESET   If OPAMP not yet initialized or is de-initialized.
  * @retval HAL_OPAMP_STATE_IDLE    If OPAMP is initialized.
  * @retval HAL_OPAMP_STATE_CALIB   If OPAMP is being calibrated.
  * @retval HAL_OPAMP_STATE_ACTIVE  If OPAMP is active.
  */
hal_opamp_state_t HAL_OPAMP_GetState(const hal_opamp_handle_t *hopamp)
{
  ASSERT_DBG_PARAM((hopamp != NULL));

  ASSERT_DBG_STATE(hopamp->global_state, (uint32_t)OPAMP_STATE_ALL);

  return hopamp->global_state;
}

/**
  * @}
  */

/** @defgroup OPAMP_Exported_Functions_Group6  User Data API functions
    This subsection provides functions allowing to:
      + set a user data pointer (ex: a user context) in a OPAMP handle,
      + get a user data pointer (ex: a user context) from a OPAMP handle.
    @note A typical usage is to set user data pointer before starting an OPAMP,<br>
          then retrieve it when needed.
  * @{
  */
#if defined(USE_HAL_OPAMP_USER_DATA) && (USE_HAL_OPAMP_USER_DATA == 1)
/**
  * @brief  Store user data pointer into the OPAMP handle.
  * @param  hopamp Pointer to a hal_opamp_handle_t.
  * @param  p_user_data Pointer to the user data.
  */
void HAL_OPAMP_SetUserData(hal_opamp_handle_t *hopamp, const void *p_user_data)
{
  ASSERT_DBG_PARAM((hopamp != NULL));
  ASSERT_DBG_STATE(hopamp->global_state, OPAMP_STATE_ALL);

  hopamp->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve user data pointer from the OPAMP handle.
  * @param  hopamp Pointer to a hal_opamp_handle_t.
  * @retval (void*) The pointer to the user data, when previously set by HAL_OPAMP_SetUserData().
  * @retval NULL Other way.
  */
const void *HAL_OPAMP_GetUserData(const hal_opamp_handle_t *hopamp)
{
  ASSERT_DBG_PARAM((hopamp != NULL));
  ASSERT_DBG_STATE(hopamp->global_state, OPAMP_STATE_ALL);

  return (hopamp->p_user_data);
}
#endif /* USE_HAL_OPAMP_USER_DATA */

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup OPAMP_Private_Functions
  * @{
  */

#if defined(USE_HAL_OPAMP_CALIBRATE_PARALLEL) && (USE_HAL_OPAMP_CALIBRATE_PARALLEL == 1)
/**
  * @brief  Set hopamp_y handle element inside the circular list of hopamp_x handle.
  * @param  hopamp_x Pointer to a hal_opamp_handle_t structure, this is the first linked element.
  * @param  hopamp_y Pointer to a hal_opamp_handle_t structure, this is the second linked element
  *                  to be inserted in the circular list of the first element.
  *                  By the way hopamp_y is removed from other non-singleton list.
  * @note   This function must be called to build a circular chained list of OPAMP handles.
  *         Handles and p_next_link field must not be NULL, (to be check by caller).
  */
static void OPAMP_SetLinkNextHandle(hal_opamp_handle_t *hopamp_x, hal_opamp_handle_t *hopamp_y)
{
  hal_opamp_handle_t *temp_hopamp;
  hal_opamp_handle_t *previous_hopamp;

  /* first step: remove hopamp_y out of its circular list
     (can be either a singleton list or multi instances list)
  */
  temp_hopamp = hopamp_y;
  while (temp_hopamp->p_next_link !=  hopamp_y) /* get previous link of hopamp_y */
  {
    temp_hopamp = temp_hopamp->p_next_link;
  }
  previous_hopamp = temp_hopamp;
  previous_hopamp->p_next_link = hopamp_y->p_next_link; /* close the circular list of hopamp_y */

  /* then insert hopamp_y in hopamp_x list (can be either a singleton list or multi instances list) */
  temp_hopamp = hopamp_x->p_next_link;
  hopamp_x->p_next_link = hopamp_y;
  hopamp_y->p_next_link = temp_hopamp;
}

/**
  * @brief  Run the self calibration of the opamp chained instances in parallel according to the specified power mode.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure,
  *                it contains a linked list of OPAMP handle to be calibrated.
  * @param  power_mode Low_power or normal_power.
  * @param  max_nb_opamp Maximum number of hopamp to be calibrated in parallel,
  *                      must be less or equal to OPAMP_INSTANCES_NB
  * @note   Running all calibration in parallel reduce total calibration time.
  * @note   Trimming values (PMOS & NMOS) are updated and user trimming is
  *         enabled whenever calibration is successful.
  * @note   Calibration runs about 10 ms (5 dichotomy steps, repeated for P
  *         and N transistors: 10 steps with 1 ms for each step).
  */
static void OPAMP_CalibrateParallel(hal_opamp_handle_t *hopamp,
                                    hal_opamp_power_mode_t power_mode, uint32_t max_nb_opamp)
{
  OPAMP_TypeDef *opamp_instance[OPAMP_INSTANCES_NB];
  uint32_t memo_opamp_mode[OPAMP_INSTANCES_NB] = {0};
  uint32_t trim_value[OPAMP_INSTANCES_NB] = {0};
  uint32_t nb_instance;
  uint32_t diff_pair;
  uint32_t delta;
  uint32_t index;

  hal_opamp_handle_t *hopamp_current;
  hopamp_current = hopamp;
  nb_instance = 0;
  do
  {
    opamp_instance[nb_instance] = OPAMP_GET_INSTANCE(hopamp_current);
    nb_instance++;
    hopamp_current = hopamp_current->p_next_link;
  } while ((hopamp_current != hopamp) && (nb_instance < max_nb_opamp));

  for (index = 0U; index < nb_instance; index++)
  {
    /* At first save OPAMP configuration mode */
    memo_opamp_mode[index] = LL_OPAMP_GetConfigurationMode(opamp_instance[index]);

    /* Then change OPAMP configuration mode (because calibration processing is not working in PGA mode) */
    /* Use the standalone mode */
    LL_OPAMP_SetConfigurationMode(opamp_instance[index], LL_OPAMP_MODE_STANDALONE);

    /*  User trimming values are used for offset calibration */
    LL_OPAMP_SetTrimmingMode(opamp_instance[index], LL_OPAMP_TRIMMING_USER);
  }

  for (uint32_t loop = 0U ; loop < 2U; loop++)
  {
    if (loop == 0U)
    {
      diff_pair = LL_OPAMP_TRIMMING_NMOS;  /* 1st calibration - N */
    }
    else
    {
      diff_pair = LL_OPAMP_TRIMMING_PMOS;  /* 2nd calibration - P */
    }

    for (index = 0U ; index < nb_instance; index++)
    {
      /* Enable calibration */
      LL_OPAMP_SetMode(opamp_instance[index], LL_OPAMP_MODE_CALIBRATION);

      LL_OPAMP_SetCalibrationSelection(opamp_instance[index], diff_pair); /* calibration N or P */

      LL_OPAMP_Enable(opamp_instance[index]);

      /* Init trimming value : to medium value */
      trim_value[index] = 16U;
    }

    delta = 8U;
    while (delta != 0U)
    {
      for (index = 0U; index < nb_instance; index++)
      {
        /* Set candidate trimming value in the register depending of power mode (OTR or LPOTR) */
        LL_OPAMP_SetOffsetTrimValue(opamp_instance[index], (uint32_t)power_mode,
                                    diff_pair, trim_value[index]);
      }

      /* Wait 1 ms delay as per datasheet (electrical characteristics). */
      /* Offset trim time: during calibration, minimum time needed between */
      /* two steps to have 1 mV accuracy. */
      HAL_Delay(OPAMP_TRIMMING_DELAY_MS);

      /* Check CALOUT CSR bit value */
      for (index = 0U; index < nb_instance; index++)
      {
        if (LL_OPAMP_IsCalibrationOutputSet(opamp_instance[index]) == 1U)
        {
          /* OPAMP_CSR_CALOUT is HIGH try lower trimming */
          trim_value[index] -= delta;
        }
        else
        {
          /* OPAMP_CSR_CALOUT is LOW try higher trimming */
          trim_value[index] += delta;
        }
      }
      /* Divide range by 2 to continue dichotomy sweep */
      delta >>= 1U;
    }

    /* Still need to check if right calibration is current value or one step below */
    /* Indeed the first value that causes the CALOUT bit to change from 0 to 1  */
    /* Set candidate trimming */
    for (index = 0U; index < nb_instance; index++)
    {
      LL_OPAMP_SetOffsetTrimValue(opamp_instance[index], (uint32_t)power_mode,
                                  diff_pair, trim_value[index]);
    }

    /* Wait 1 ms delay as per datasheet (electrical characteristics). */
    /* Offset trim time: during calibration, minimum time needed between */
    /* two steps to have 1 mV accuracy. */
    HAL_Delay(OPAMP_TRIMMING_DELAY_MS);

    for (index = 0U; index < nb_instance; index++)
    {
      if (LL_OPAMP_IsCalibrationOutputSet(opamp_instance[index]) == 0U)
      {
        /* Trimming value is actually one value more */
        trim_value[index]++;
        LL_OPAMP_SetOffsetTrimValue(opamp_instance[index], (uint32_t)power_mode,
                                    diff_pair, trim_value[index]);
      }
    }
  } /* end for(loop) */

  for (index = 0U; index < nb_instance; index++)
  {
    /* Disable the OPAMPs */
    LL_OPAMP_Disable(opamp_instance[index]);
    /* Reset calibration selection to NMOS */
    LL_OPAMP_SetCalibrationSelection(opamp_instance[index], LL_OPAMP_TRIMMING_NMOS);
    /* Disable calibration */
    LL_OPAMP_SetMode(opamp_instance[index], LL_OPAMP_MODE_FUNCTIONAL);

    /* Restore OPAMP mode after calibration */
    LL_OPAMP_SetConfigurationMode(opamp_instance[index], memo_opamp_mode[index]);
  }
}
#else
/**
  * @brief  Run the self calibration for a single OPAMP instance according to the specified power mode.
  * @param  hopamp Pointer to a hal_opamp_handle_t structure of OPAMP to be calibrated.
  * @param  power_mode Low_power or normal_power.
  * @note   Trimming values (PMOS & NMOS) are updated and user trimming is
  *         enabled whenever calibration is successful.
  * @note   Calibration runs about 10 ms (5 dichotomy steps, repeated for P
  *         and N transistors: 10 steps with 1 ms for each step).
  */
static void OPAMP_CalibrateSingle(hal_opamp_handle_t *hopamp, hal_opamp_power_mode_t power_mode)
{
  OPAMP_TypeDef *p_instance;
  uint32_t memo_opamp_mode;
  uint32_t trim_value;
  uint32_t diff_pair;
  uint32_t delta;

  p_instance = OPAMP_GET_INSTANCE(hopamp);

  /* At first save OPAMP configuration mode */
  memo_opamp_mode = LL_OPAMP_GetConfigurationMode(p_instance);

  /* Then change OPAMP configuration mode (because calibration processing is not working in PGA mode) */
  /* Use the standalone mode */
  LL_OPAMP_SetConfigurationMode(p_instance, LL_OPAMP_MODE_STANDALONE);

  /*  User trimming values are used for offset calibration */
  LL_OPAMP_SetTrimmingMode(p_instance, LL_OPAMP_TRIMMING_USER);

  for (uint32_t loop = 0U ; loop < 2U; loop++)
  {
    if (loop == 0U)
    {
      diff_pair = LL_OPAMP_TRIMMING_NMOS;  /* 1st calibration - N */
    }
    else
    {
      diff_pair = LL_OPAMP_TRIMMING_PMOS;  /* 2nd calibration - P */
    }

    /* Enable calibration */
    LL_OPAMP_SetMode(p_instance, LL_OPAMP_MODE_CALIBRATION);

    LL_OPAMP_SetCalibrationSelection(p_instance, diff_pair); /* calibration N or P */

    LL_OPAMP_Enable(p_instance);

    /* Init trimming value : to medium value */
    trim_value = 16U;

    delta = 8U;
    while (delta != 0U)
    {
      /* Set candidate trimming value in the register depending of power mode (OTR or LPOTR) */
      LL_OPAMP_SetOffsetTrimValue(p_instance, (uint32_t)power_mode, diff_pair, trim_value);

      /* Wait 1 ms delay as per datasheet (electrical characteristics). */
      /* Offset trim time: during calibration, minimum time needed between */
      /* two steps to have 1 mV accuracy. */
      HAL_Delay(OPAMP_TRIMMING_DELAY_MS);

      /* Check CALOUT CSR bit value */
      if (LL_OPAMP_IsCalibrationOutputSet(p_instance) == 1U)
      {
        /* OPAMP_CSR_CALOUT is HIGH try lower trimming */
        trim_value -= delta;
      }
      else
      {
        /* OPAMP_CSR_CALOUT is LOW try higher trimming */
        trim_value += delta;
      }

      /* Divide range by 2 to continue dichotomy sweep */
      delta >>= 1U;
    }

    /* Still need to check if right calibration is current value or one step below */
    /* Indeed the first value that causes the CALOUT bit to change from 0 to 1  */
    /* Set candidate trimming */
    LL_OPAMP_SetOffsetTrimValue(p_instance, (uint32_t)power_mode, diff_pair, trim_value);

    /* Wait 1 ms delay as per datasheet (electrical characteristics). */
    /* Offset trim time: during calibration, minimum time needed between */
    /* two steps to have 1 mV accuracy. */
    HAL_Delay(OPAMP_TRIMMING_DELAY_MS);

    if (LL_OPAMP_IsCalibrationOutputSet(p_instance) == 0U)
    {
      /* Trimming value is actually one value more */
      trim_value++;
      LL_OPAMP_SetOffsetTrimValue(p_instance, (uint32_t)power_mode, diff_pair, trim_value);
    }
  } /* end for(loop) */

  /* Disable the OPAMPs */
  LL_OPAMP_Disable(p_instance);
  /* Reset calibration selection to NMOS */
  LL_OPAMP_SetCalibrationSelection(p_instance, LL_OPAMP_TRIMMING_NMOS);
  /* Disable calibration */
  LL_OPAMP_SetMode(p_instance, LL_OPAMP_MODE_FUNCTIONAL);

  /* Restore OPAMP mode after calibration */
  LL_OPAMP_SetConfigurationMode(p_instance, memo_opamp_mode);
}
#endif /* USE_HAL_OPAMP_CALIBRATE_PARALLEL */

/**
  * @}
  */

/**
  * @}
  */

#endif /* OPAMP1 || OPAMP2 */
#endif /* USE_HAL_OPAMP_MODULE */
/**
  * @}
  */
