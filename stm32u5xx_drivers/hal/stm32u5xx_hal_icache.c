/**
  ******************************************************************************
  * @file    stm32u5xx_hal_icache.c
  * @brief   ICACHE HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Instruction Cache (ICACHE).
  *           + Initialization and Configuration
  *           + Invalidate functions
  *           + Monitoring management
  *           + Memory address remap management
  ******************************************************************************
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

/** @addtogroup ICACHE
  * @{

# ICACHE Introduction
    The Instruction Cache (ICACHE) is introduced on C-AHB code bus of
    Cortex-M33 processor to improve performance when fetching instruction
    and data from both internal and external memories. Some specific
    features like dual master ports, hit-under-miss, and critical-word-first
    refill policy, allow close to zero-wait-state performance in most use cases.

# Main features
The main features of ICACHE are described below:

- Bus interface
  - one 32-bit AHB slave port, the execution port (input from Cortex-M33 C-AHB code interface)
  - two AHB master ports: master1 and master2 ports (outputs to Fast and Slow buses of main AHB bus matrix,
  respectively)
  - one 32-bit AHB slave port for control (input from AHB peripherals interconnect, for ICACHE registers access)

- Cache access
  - 0 wait-state on hits
  - Hit-under-miss capability: ability to serve processor requests (access to cached data) during an ongoing line refill
   due to a previous cache miss
  - Dual master access: feature used to decouple the traffic according to targeted memory. For example, the ICACHE
  assigns fast traffic (addressing flash and SRAM memories) to the AHB master1 port, and slow traffic (addressing
  external memories) to the AHB master2 port, thus preventing processor stalls on lines refills from external memories.
  This allows ISR (interrupt service routine) fetching on internal flash memory to take place in parallel with a cache
  line refill from external memories.
  - Minimal impact on interrupt latency, thanks to dual master
  - Optimal cache line refill thanks to WRAPw bursts of the size of the cache line (32-bit word size, w, aligned on
  cache line size)
  - n-way set-associative default configuration with possibility to configure as 1-way, means direct mapped

- Memory address remap
  - Possibility to remap input address falling into up to four memory regions (used to remap aliased code in SRAM
  memories to the Code region, for execution from C-AHB code interface).

- Replacement and refill
  - pLRU-t replacement policy (pseudo-least-recently-used, based on binary tree), algorithm with best
  complexity/performance balance
  - Critical-word-first refill policy, minimizing processor stalls
  - Possibility to configure burst type of AHB memory transaction for remapped regions: INCRw or WRAPw
  (size w aligned on cache line size)

- Performance counters
  ICACHE implements two performance counters:
  - Hit monitor counter (32-bit)
  - Miss monitor counter (16-bit)

- Error management
  - Possibility to detect an unexpected cacheable write access, to flag an error and optionally to raise
  an interrupt

- Trust Zone security support

- Maintenance operation
  - Cache invalidate: full cache invalidation, fast command, non interruptible.

# How to use the HAL ICACHE driver
## The HAL ICACHE driver can be used as follows:
### Main use

- Initialize the ICACHE according to the associated handle with HAL_ICACHE_Init().
- Set the configuration of the ICACHE to choose associativity mode with HAL_ICACHE_SetAssociativityMode() function
(default is 2-ways).
- Enable and disable up to four regions to remap input address from external memories to the internal Code region for
execution with HAL_ICACHE_EnableRemapRegion() and HAL_ICACHE_DisableRemapRegion() functions.
- Then start the ICACHE driver with HAL_ICACHE_Start().
   You can enable the Error interrupt detection and allow to receive callbacks in case of cache function error.
- Execute the ICACHE maintenance operations if necessary :
  - Use HAL_ICACHE_Invalidate() to invalidate the full cache content:
    - Cache content is lost, and reloaded when needed.
    - Used for complete invalidate of the ICACHE in case.
    - Blocking call until operation is done.

### Monitoring performance
- The performance monitoring Hit and Miss counters can be used as follows :
HAL_ICACHE_EnableMonitors() and HAL_ICACHE_DisableMonitors() respectively enable and disable any monitors.
To retrieve the counters value use HAL_ICACHE_GetMonitorHitValue() or HAL_ICACHE_GetMonitorMissValue() functions.
HAL_ICACHE_ResetMonitors() function allows to clear any monitors value.


### Interrupt Mode
- The ICACHE provides two sources of interrupt :
  - The error interrupt.
  - The invalidate completion interrupt.

- For each interrupt, there is a corresponding callback launched in the HAL_ICACHE_IRQHandler() function.
- In case of interrupt, depending which registering callback method used, it either triggers the weak callback
 or the register one.

- Error :
  - Override weak definition for following callbacks:
     - HAL_ICACHE_ErrorCallback()
  - Or use register callbacks(USE_HAL_ICACHE_REGISTER_CALLBACKS = 1):
     - HAL_ICACHE_RegisterErrorCallback()
  - Start the ICACHE driver with HAL_ICACHE_Start(hicache,HAL_ICACHE_IT_ERROR) as explain above.

- Maintenance operation:
  - Override weak definition for following callbacks:
     - HAL_ICACHE_InvalidateCompleteCallback()
  - Or use register callbacks(USE_HAL_ICACHE_REGISTER_CALLBACKS = 1):
     - HAL_ICACHE_RegisterInvalidateCompleteCallback()
  - Launch a maintenance operation with Interrupt: HAL_ICACHE_Invalidate_IT().

## HAL ICACHE Driver State
- Use HAL_ICACHE_GetState() function to return HAL ICACHE state.


## Configuration inside the ICACHE driver :

Config defines                    | Description     | Default value | Note                                          |
--------------------------------- | ----------------| ------------- | ----------------------------------------------|
USE_HAL_ICACHE_MODULE             | From hal_conf.h |       1       | Allows to use HAL ICACHE module.              |
USE_HAL_ICACHE_REGISTER_CALLBACKS | From hal_conf.h |       0       | Allows to use the register callbacks.         |
USE_HAL_CHECK_PARAM               | From hal_conf.h |       0       | Allows to use the run-time checks parameters. |
USE_ASSERT_DBG_PARAM              | From IDE        |       NA      | Allows to use the assert check parameters.    |
USE_ASSERT_DBG_STATE              | From IDE        |       NA      | Allows to use the assert check states.        |
USE_HAL_ICACHE_GET_LAST_ERRORS    | From hal_conf.h |       1       | Allow to use error code mechanism.            |
USE_HAL_ICACHE_USER_DATA          | From hal_conf.h |       0       | Allows to use user data.                      |
  */

#if defined (USE_HAL_ICACHE_MODULE) && (USE_HAL_ICACHE_MODULE == 1)

/* Private defines -----------------------------------------------------------*/
/** @defgroup ICACHE_Private_Defines ICACHE Private Defines

  * @{
  */
#define ICACHE_MAINTENANCE_TIMEOUT_VALUE           1U   /*!< 1ms */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup ICACHE_Private_Macros ICACHE Private Macros
  * @{
  */

/**
  * @brief Monitor type
  */
#define IS_ICACHE_MONITOR_TYPE(type)  (((type) & ~HAL_ICACHE_MONITOR_ALL) == 0U)

/**
  * @brief Error Interrupt
  */
#define IS_ICACHE_IT(it)      (((it) & ~HAL_ICACHE_IT_ERROR) == 0U)

/**
  * @brief Associativity Mode
  */
#define IS_ICACHE_ASSOCIATIVITY_MODE(mode)  (((mode) == HAL_ICACHE_ASSOCIATIVITY_1WAY) \
                                             || ((mode) == HAL_ICACHE_ASSOCIATIVITY_2WAYS))

/**
  * @brief Region number
  */
#define IS_ICACHE_REGION_NUMBER(number)    (((number) == HAL_ICACHE_REGION_0) \
                                            || ((number) == HAL_ICACHE_REGION_1) \
                                            || ((number) == HAL_ICACHE_REGION_2) \
                                            || ((number) == HAL_ICACHE_REGION_3))

/**
  * @brief Region base address
  */
#define IS_ICACHE_REGION_BASE_ADDRESS(baseaddr)  ((baseaddr) <= 0x1FFFFFFFUL)

/**
  * @brief Region size
  */
#define IS_ICACHE_REGION_SIZE(size)     (((size) == HAL_ICACHE_REGION_SIZE_2MBYTES)   \
                                         || ((size) == HAL_ICACHE_REGION_SIZE_4MBYTES)   \
                                         || ((size) == HAL_ICACHE_REGION_SIZE_8MBYTES)   \
                                         || ((size) == HAL_ICACHE_REGION_SIZE_16MBYTES)  \
                                         || ((size) == HAL_ICACHE_REGION_SIZE_32MBYTES)  \
                                         || ((size) == HAL_ICACHE_REGION_SIZE_64MBYTES)  \
                                         || ((size) == HAL_ICACHE_REGION_SIZE_128MBYTES))

/**
  * @brief Region master port
  */
#define IS_ICACHE_REGION_MASTER_PORT(masterport)  (((masterport) == HAL_ICACHE_MASTER1_PORT) \
                                                   || ((masterport) == HAL_ICACHE_MASTER2_PORT))

/**
  * @brief Region output burst
  */
#define IS_ICACHE_REGION_BURST(burst) (((burst) == HAL_ICACHE_BURST_WRAP) \
                                       || ((burst) == HAL_ICACHE_BURST_INCR))
/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup ICACHE_Exported_Functions
  * @{
  */

/** @addtogroup ICACHE_Exported_Functions_Group1
  * @{
This section provides a set of functions allowing to initialize and deinitialize the ICACHE peripheral:
- Call the function HAL_ICACHE_Init() to initialize the selected ICACHE handle and associate an instance.
- Call the function HAL_ICACHE_DeInit():
  - to reset the ICACHE to the initial state by resetting the monitors,
  - to reset and disable remap regions,
  - to set burst type to WRAP mode, master1 port selected, 2-ways associativity mode,
  - to disable interrupts,
  - to reset and stop ongoing commands if any,
  - to stop the cache and clear the flags.
  */

/**
  * @brief  Initialize the ICACHE according to the associated handle.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *              the handle information for the specified ICACHE.
  * @param  instance ICACHE instance.
  * @retval HAL_INVALID_PARAM When the handle is NULL.
  * @retval HAL_OK            HAL ICACHE driver correctly Initialized for the given ICACHE instance.
  */
hal_status_t HAL_ICACHE_Init(hal_icache_handle_t *hicache, hal_icache_t instance)
{
  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  ASSERT_DBG_PARAM(IS_ICACHE_INSTANCE((ICACHE_TypeDef *)(uint32_t)instance));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the handle struct pointer */
  if (hicache == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hicache->instance = instance;

#if defined(USE_HAL_ICACHE_REGISTER_CALLBACKS) && (USE_HAL_ICACHE_REGISTER_CALLBACKS == 1)
  /* Initialize the ICACHE Callback settings */
  hicache->p_error_cb            = HAL_ICACHE_ErrorCallback;  /* Error Callback */
  hicache->p_invalidate_cplt_cb  = HAL_ICACHE_InvalidateCompleteCallback;  /* Invalidate complete Callback */
#endif /* USE_HAL_ICACHE_REGISTER_CALLBACKS */

#if defined(USE_HAL_ICACHE_GET_LAST_ERRORS) && (USE_HAL_ICACHE_GET_LAST_ERRORS == 1)
  /* In case of single process at a time: one single variable storing the last errors */
  hicache->last_error_codes = HAL_ICACHE_ERROR_NONE;
#endif /* USE_HAL_ICACHE_GET_LAST_ERRORS */

  /* Initialize the ICACHE handle global_state */
  hicache->global_state = HAL_ICACHE_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  DeInitialize the ICACHE.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                 the handle information for the specified ICACHE instance.
  * @note   The goal of this function is to reset the ICACHE to the initial state:
  *           - stop the ICACHE,
  *           - disable and reset the monitors,
  *           - set the associativity in 2-ways mode (default),
  *           - disable the interrupts,
  *           - clear the interrupt flags,
  *           - disable and reset the remapped regions,
  *           - and reset the last error code.
  */
void HAL_ICACHE_DeInit(hal_icache_handle_t *hicache)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state, \
                   (uint32_t)HAL_ICACHE_STATE_IDLE | \
                   (uint32_t)HAL_ICACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_ICACHE_STATE_MAINTENANCE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  LL_ICACHE_Disable(p_icachex);

  LL_ICACHE_ResetMonitors(p_icachex, LL_ICACHE_MONITOR_ALL);

  /* Reset the Control Register: 2-ways associativity mode is set, maintenance operation finished,
     ICACHE and monitors disabled */
  LL_ICACHE_WRITE_REG(p_icachex, CR, LL_ICACHE_2WAYS);

  /* Reset the Interrupt Enable Register: clear ERRIE and BSYENDIE flags */
  LL_ICACHE_WRITE_REG(p_icachex, IER, 0U);

  /* Reset the Flag Clear Register: clear ERR and BSYEND flags */
  LL_ICACHE_ClearFlag(p_icachex, (LL_ICACHE_FCR_CERRF | LL_ICACHE_FCR_CBSYENDF));

  /* Reset and disable remapped regions */
  LL_ICACHE_WRITE_REG(p_icachex, CRR0, ICACHE_CRRx_RSIZE_0);
  LL_ICACHE_WRITE_REG(p_icachex, CRR1, ICACHE_CRRx_RSIZE_0);
  LL_ICACHE_WRITE_REG(p_icachex, CRR2, ICACHE_CRRx_RSIZE_0);
  LL_ICACHE_WRITE_REG(p_icachex, CRR3, ICACHE_CRRx_RSIZE_0);

#if defined(USE_HAL_ICACHE_GET_LAST_ERRORS) && (USE_HAL_ICACHE_GET_LAST_ERRORS == 1)
  /* In case of single process at a time: one single variable storing the last errors */
  hicache->last_error_codes = HAL_ICACHE_ERROR_NONE;
#endif /* USE_HAL_ICACHE_GET_LAST_ERRORS */

  hicache->global_state = HAL_ICACHE_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup ICACHE_Exported_Functions_Group2
  * @{
This section provides a set of functions allowing to configure the ICACHE peripheral:
- HAL_ICACHE_SetAssociativityMode() to set the chosen associativity mode.
- HAL_ICACHE_GetAssociativityMode() to read the current associativity mode.
- HAL_ICACHE_SetConfigRemapRegion() to configure the different fields in the region remap register.
- HAL_ICACHE_GetConfigRemapRegion() to read the different fields in the region remap register.
  */

/**
  * @brief  Set the ICACHE associativity mode selection.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                the handle information for the specified ICACHE instance.
  * @param  mode Associativity mode to be applied.
  * @note   If ICACHE is enabled, the mode cannot be set.
  * @retval HAL_OK ICACHE associativity mode has been correctly configured.
  */
hal_status_t HAL_ICACHE_SetAssociativityMode(hal_icache_handle_t *hicache, hal_icache_associativity_t mode)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  ASSERT_DBG_PARAM(IS_ICACHE_ASSOCIATIVITY_MODE(mode));

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state, HAL_ICACHE_STATE_IDLE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  LL_ICACHE_SetMode(p_icachex, (uint32_t)mode);

  return HAL_OK;
}


/**
  * @brief  Get the ICACHE associativity mode selection.
  * @param hicache Pointer to a hal_icache_handle_t structure that contains
  *                the handle information for the specified ICACHE instance.
  * @retval HAL_ICACHE_ASSOCIATIVITY_1WAY Associativity mode is 1-way.
  * @retval HAL_ICACHE_ASSOCIATIVITY_2WAYS Associativity mode is 2-ways.
  */
hal_icache_associativity_t HAL_ICACHE_GetAssociativityMode(const hal_icache_handle_t *hicache)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  return ((hal_icache_associativity_t)LL_ICACHE_GetMode(p_icachex));
}

/**
  * @brief  Configure the ICACHE remap region.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                the handle information for the specified ICACHE instance.
  * @param  region Region number.
  * @param  p_region_config Pointer to region config structure.
  * @note   If ICACHE is enabled, the remap region cannot be set.
  * @retval HAL_OK ICACHE remap region has been correctly initialized.
  */
hal_status_t HAL_ICACHE_SetConfigRemapRegion(hal_icache_handle_t *hicache, hal_icache_region_t region,
                                             const hal_icache_region_config_t *p_region_config)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  ASSERT_DBG_PARAM(IS_ICACHE_REGION_NUMBER(region));

  /* Check region allocation */
  ASSERT_DBG_PARAM(p_region_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the region struct pointer */
  if (p_region_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check region parameters */
  ASSERT_DBG_PARAM(IS_ICACHE_REGION_BASE_ADDRESS(p_region_config->base_address));
  ASSERT_DBG_PARAM(IS_ICACHE_REGION_SIZE(p_region_config->size));
  ASSERT_DBG_PARAM(IS_ICACHE_REGION_MASTER_PORT(p_region_config->master_port));
  ASSERT_DBG_PARAM(IS_ICACHE_REGION_BURST(p_region_config->output_burst));

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state, HAL_ICACHE_STATE_IDLE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  LL_ICACHE_SetConfigRemapRegion(p_icachex, (uint32_t)region, p_region_config->base_address,
                                 p_region_config->remap_address, (uint32_t)p_region_config->size,
                                 (uint32_t)p_region_config->master_port, (uint32_t)p_region_config->output_burst);
  return HAL_OK;
}

/**
  * @brief  Get the ICACHE remap region configuration.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                 the handle information for the specified ICACHE instance.
  * @param  region Region number.
  * @param  p_region_config Pointer to config region structure.
  */
void HAL_ICACHE_GetConfigRemapRegion(const hal_icache_handle_t *hicache, hal_icache_region_t region,
                                     hal_icache_region_config_t *p_region_config)
{
  uint32_t config;
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  ASSERT_DBG_PARAM(IS_ICACHE_REGION_NUMBER(region));

  /* Check region allocation */
  ASSERT_DBG_PARAM(p_region_config != NULL);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  config = LL_ICACHE_GetConfigRemapRegion(p_icachex, (uint32_t)region);

  p_region_config->base_address = READ_BIT(config, ICACHE_CRRx_BASEADDR) << LL_ICACHE_ADDRESS_SHIFT;
  p_region_config->remap_address = (READ_BIT(config, ICACHE_CRRx_REMAPADDR) >> ICACHE_CRRx_REMAPADDR_Pos)
                                   << LL_ICACHE_ADDRESS_SHIFT;
  p_region_config->size = (hal_icache_region_size_t)(uint32_t)(READ_BIT(config, ICACHE_CRRx_RSIZE)
                                                               >> ICACHE_CRRx_RSIZE_Pos);
  p_region_config->master_port = (hal_icache_master_port_t)(uint32_t)READ_BIT(config, ICACHE_CRRx_MSTSEL);
  p_region_config->output_burst = (hal_icache_region_burst_t)(uint32_t)READ_BIT(config, ICACHE_CRRx_HBURST);
}
/**
  * @}
  */

/** @addtogroup ICACHE_Exported_Functions_Group3
  * @{
The functions are :
- HAL_ICACHE_Start() to start the ICACHE with error interrupt control.
- HAL_ICACHE_Stop() to stop the ICACHE.
- HAL_ICACHE_EnableRemapRegion() to enable the configured region.
- HAL_ICACHE_DisableRemapRegion() to disable the corresponding region.
- HAL_ICACHE_IsEnabledRemapRegion() to ensure if the corresponding region is enabled or not.
  */

/**
  * @brief  Start ICACHE.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                 the handle information for the specified ICACHE instance.
  * @param  interrupts Interrupts
  *            @arg HAL_ICACHE_IT_NONE
  *            @arg HAL_ICACHE_IT_ERROR
  * @note This function can enable the interrupts, and starts the ICACHE.
  * @retval HAL_OK Only success, even if there is any ongoing cache operation.
  */
hal_status_t HAL_ICACHE_Start(hal_icache_handle_t *hicache, uint32_t interrupts)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Check the ICACHE error interrupt bit */
  ASSERT_DBG_PARAM(IS_ICACHE_IT(interrupts));

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state, HAL_ICACHE_STATE_IDLE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

#if defined(USE_HAL_ICACHE_GET_LAST_ERRORS) && (USE_HAL_ICACHE_GET_LAST_ERRORS == 1)
  hicache->last_error_codes = HAL_ICACHE_ERROR_NONE;
#endif /* USE_HAL_ICACHE_GET_LAST_ERRORS */

  /* Set Interrupts */
  LL_ICACHE_WRITE_REG(p_icachex, IER, interrupts);

  LL_ICACHE_Enable(p_icachex);

  hicache->global_state = HAL_ICACHE_STATE_ACTIVE;

  return HAL_OK;
}

/**
  * @brief  Stop ICACHE.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                 the handle information for the specified ICACHE instance.
  * @note This function disables interrupts, clears the flags and stops the ICACHE.
  * @note   This function disables the Error Interrupt detection following an eviction or a clean operation,
            clears the error flag and stop the ICACHE driver.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_ICACHE_Stop(hal_icache_handle_t *hicache)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state, \
                   (uint32_t)HAL_ICACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_ICACHE_STATE_MAINTENANCE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  LL_ICACHE_Disable(p_icachex);

  LL_ICACHE_DisableIT_ERR(p_icachex);

  LL_ICACHE_ClearFlag_ERR(p_icachex);

  hicache->global_state = HAL_ICACHE_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Enable the memory remapping for a predefined region.
  * @param  hicache Pointer to the ICACHE handle.
  * @param  region Region number.
  * @note   If ICACHE is enabled, the remap region cannot be enabled.
  * @retval HAL_OK ICACHE remap region has been correctly activated.
  */
hal_status_t HAL_ICACHE_EnableRemapRegion(hal_icache_handle_t *hicache, hal_icache_region_t region)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  ASSERT_DBG_PARAM(IS_ICACHE_REGION_NUMBER(region));

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state, HAL_ICACHE_STATE_IDLE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  LL_ICACHE_EnableRegion(p_icachex, (uint32_t)region);

  return HAL_OK;
}

/**
  * @brief  Disable the memory remapping for a predefined region.
  * @param  hicache Pointer to the ICACHE handle.
  * @param  region Region number.
  * @note   If ICACHE is enabled, the remap region cannot be disabled.
  * @retval HAL_OK ICACHE remap region has been correctly de-activated.
  */
hal_status_t  HAL_ICACHE_DisableRemapRegion(hal_icache_handle_t *hicache, hal_icache_region_t region)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  ASSERT_DBG_PARAM(IS_ICACHE_REGION_NUMBER(region));

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state, HAL_ICACHE_STATE_IDLE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  LL_ICACHE_DisableRegion(p_icachex, (uint32_t)region);

  return HAL_OK;
}

/**
  * @brief  Check if corresponding region is enabled or not.
  * @param  hicache Pointer to the ICACHE handle.
  * @param  region Region number.
  * @retval HAL_ICACHE_REMAP_REGION_DISABLED Remap region is disabled.
  * @retval HAL_ICACHE_REMAP_REGION_ENABLED  Remap region is enabled.
  */
hal_icache_remap_region_status_t HAL_ICACHE_IsEnabledRemapRegion(const hal_icache_handle_t *hicache,
                                                                 hal_icache_region_t region)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  ASSERT_DBG_PARAM(IS_ICACHE_REGION_NUMBER(region));

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state,
                   (uint32_t)HAL_ICACHE_STATE_IDLE | \
                   (uint32_t)HAL_ICACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_ICACHE_STATE_MAINTENANCE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  return ((hal_icache_remap_region_status_t)LL_ICACHE_IsEnabledRegion(p_icachex, (uint32_t)region));
}

/**
  * @}
  */

/** @addtogroup ICACHE_Exported_Functions_Group5
  * @{
This section provides functions allowing to monitor ICACHE:
 - Call HAL_ICACHE_EnableMonitors() to enable the Instruction Cache performance monitoring.
 - Call HAL_ICACHE_DisableMonitors() to disable the Instruction Cache performance monitoring.
 - Call HAL_ICACHE_ResetMonitors() to reset the Instruction Cache performance monitoring values.
 - Call HAL_ICACHE_GetMonitorHitValue() to get the Instruction Cache performance Hit monitoring value.
 - Call HAL_ICACHE_GetMonitorMissValue() to get the Instruction Cache performance Miss monitoring value.
  */
/**
  * @brief  Enable the ICACHE performance monitoring.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                 the handle information for the specified ICACHE instance.
  * @param  monitor_type It can be a combination of the following values:
  *            @arg HAL_ICACHE_MONITOR_HIT
  *            @arg HAL_ICACHE_MONITOR_MISS
  *            @arg HAL_ICACHE_MONITOR_ALL
  * @retval HAL_OK ICACHE Monitor(s) enabled successfully.
  */
hal_status_t HAL_ICACHE_EnableMonitors(hal_icache_handle_t *hicache, uint32_t monitor_type)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Check the monitor type (HIT, MISS or both) */
  ASSERT_DBG_PARAM(IS_ICACHE_MONITOR_TYPE(monitor_type));

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state,
                   (uint32_t)HAL_ICACHE_STATE_IDLE | \
                   (uint32_t)HAL_ICACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_ICACHE_STATE_MAINTENANCE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  LL_ICACHE_EnableMonitors(p_icachex, monitor_type);

  return HAL_OK;
}

/**
  * @brief  Disable the ICACHE performance monitoring.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                 the handle information for the specified ICACHE instance.
  * @note   Stopping the monitoring does not reset the values.
  * @param  monitor_type It can be a combination of the following values:
  *         @arg HAL_ICACHE_MONITOR_HIT
  *         @arg HAL_ICACHE_MONITOR_MISS
  *         @arg HAL_ICACHE_MONITOR_ALL
  * @retval HAL_OK ICACHE Monitor(s) disabled successfully.
  */
hal_status_t HAL_ICACHE_DisableMonitors(hal_icache_handle_t *hicache, uint32_t monitor_type)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Check the monitor type (HIT, MISS or both) */
  ASSERT_DBG_PARAM(IS_ICACHE_MONITOR_TYPE(monitor_type));

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state,
                   (uint32_t)HAL_ICACHE_STATE_IDLE | \
                   (uint32_t)HAL_ICACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_ICACHE_STATE_MAINTENANCE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  LL_ICACHE_DisableMonitors(p_icachex, monitor_type);

  return HAL_OK;
}

/**
  * @brief  Reset the ICACHE performance monitoring values.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                 the handle information for the specified ICACHE instance.
  * @param  monitor_type It can be a combination of the following values:
  *         @arg HAL_ICACHE_MONITOR_HIT
  *         @arg HAL_ICACHE_MONITOR_MISS
  *         @arg HAL_ICACHE_MONITOR_ALL
  * @retval HAL_OK Monitor(s) reset successfully.
  */
hal_status_t HAL_ICACHE_ResetMonitors(hal_icache_handle_t *hicache, uint32_t monitor_type)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Check the monitor type (HIT, MISS or both) */
  ASSERT_DBG_PARAM(IS_ICACHE_MONITOR_TYPE(monitor_type));

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state,
                   (uint32_t)HAL_ICACHE_STATE_IDLE | \
                   (uint32_t)HAL_ICACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_ICACHE_STATE_MAINTENANCE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  LL_ICACHE_ResetMonitors(p_icachex, monitor_type);

  return HAL_OK;
}

/**
  * @brief  Get the ICACHE performance Hit monitoring value.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                 the handle information for the specified ICACHE instance.
  * @note   Upon reaching the maximum value, monitor does not wrap.
  * @retval uint32_t Hit monitoring value.
  */
uint32_t HAL_ICACHE_GetMonitorHitValue(const hal_icache_handle_t *hicache)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state,
                   (uint32_t)HAL_ICACHE_STATE_IDLE | \
                   (uint32_t)HAL_ICACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_ICACHE_STATE_MAINTENANCE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  return (LL_ICACHE_GetHitMonitor(p_icachex));
}

/**
  * @brief  Get the ICACHE performance Miss monitoring value.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                 the handle information for the specified ICACHE instance.
  * @note   Upon reaching the maximum value, monitor does not wrap.
  * @retval uint32_t Miss monitoring value.
  */
uint32_t HAL_ICACHE_GetMonitorMissValue(const hal_icache_handle_t *hicache)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state,
                   (uint32_t)HAL_ICACHE_STATE_IDLE | \
                   (uint32_t)HAL_ICACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_ICACHE_STATE_MAINTENANCE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  return (LL_ICACHE_GetMissMonitor(p_icachex));
}
/**
  * @}
  */

/** @addtogroup ICACHE_Exported_Functions_Group6
  * @{
This section provides functions allowing to launch maintenance operation:
 - Call HAL_ICACHE_Invalidate() to invalidate the Instruction Cache in polling mode.
 - Call HAL_ICACHE_Invalidate_IT() to launch the invalidation of the Instruction Cache in interrupt mode.
  */

/**
  * @brief  Invalidate the ICACHE.
  * @param  hicache Pointer to the ICACHE handle.
  * @retval HAL_OK ICACHE Invalidate operation ended successfully.
  * @retval HAL_ERROR Operation error.
  */
hal_status_t HAL_ICACHE_Invalidate(hal_icache_handle_t *hicache)
{
  uint32_t tickstart;
  ICACHE_TypeDef *p_icachex;
  hal_status_t status = HAL_OK;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state, HAL_ICACHE_STATE_ACTIVE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

#if defined(USE_HAL_ICACHE_GET_LAST_ERRORS) && (USE_HAL_ICACHE_GET_LAST_ERRORS == 1)
  hicache->last_error_codes = HAL_ICACHE_ERROR_NONE;
#endif /* USE_HAL_ICACHE_GET_LAST_ERRORS */

  /* Check no ongoing operation */
  if (LL_ICACHE_IsActiveFlag_BUSY(p_icachex) == 0U)
  {
    hicache->global_state = HAL_ICACHE_STATE_MAINTENANCE;

    /* Launch ICACHE invalidation */
    LL_ICACHE_Invalidate(p_icachex);
  }

  tickstart = HAL_GetTick();

  /* Wait for end of ICACHE invalidation */
  while (LL_ICACHE_IsActiveFlag_BSYEND(p_icachex) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > ICACHE_MAINTENANCE_TIMEOUT_VALUE)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if ((LL_ICACHE_IsActiveFlag_BSYEND(p_icachex)) == 0UL)
      {
        status = HAL_ERROR;
        break;
      }
    }
  }

  /* Clear BSYENDF */
  LL_ICACHE_ClearFlag_BSYEND(p_icachex);

  hicache->global_state = HAL_ICACHE_STATE_ACTIVE;

#if defined(USE_HAL_ICACHE_GET_LAST_ERRORS) && (USE_HAL_ICACHE_GET_LAST_ERRORS == 1)
  uint32_t error_flags = LL_ICACHE_IsActiveFlag(p_icachex, LL_ICACHE_SR_ERRF);
  if (error_flags != 0U)
  {
    hicache->last_error_codes = HAL_ICACHE_ERROR_WRITE_INTRUSION;
    status = HAL_ERROR;
  }
#endif /* USE_HAL_ICACHE_GET_LAST_ERRORS */

  return status;
}

/**
  * @brief  Invalidate the ICACHE with interrupt.
  * @param  hicache Pointer to the ICACHE handle.
  * @retval HAL_OK ICACHE Invalidate operation started successfully.
  * @retval HAL_BUSY ICACHE driver busy with another ongoing operation.
  */
hal_status_t HAL_ICACHE_Invalidate_IT(hal_icache_handle_t *hicache)
{
  ICACHE_TypeDef *p_icachex;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state, HAL_ICACHE_STATE_ACTIVE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

#if defined(USE_HAL_ICACHE_GET_LAST_ERRORS) && (USE_HAL_ICACHE_GET_LAST_ERRORS == 1)
  hicache->last_error_codes = HAL_ICACHE_ERROR_NONE;
#endif /* USE_HAL_ICACHE_GET_LAST_ERRORS */

  /* Check no ongoing operation */
  if (LL_ICACHE_IsActiveFlag_BUSY(p_icachex) != 0U)
  {
    return HAL_BUSY;
  }
  else
  {
    hicache->global_state = HAL_ICACHE_STATE_MAINTENANCE;

    /* Make sure BSYENDF is reset before to start ICACHE invalidation */
    LL_ICACHE_ClearFlag_BSYEND(p_icachex);

    /* Enable end of ICACHE invalidation interrupt */
    LL_ICACHE_EnableIT_BSYEND(p_icachex);

    /* Launch ICACHE invalidation */
    LL_ICACHE_Invalidate(p_icachex);
  }
  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup ICACHE_Exported_Functions_Group7
  * @{
The functions are :
- HAL_ICACHE_IRQHandler() to manage the two types of interrupt : Error or Invalidate.
- HAL_ICACHE_ErrorCallback() : Error Callback.
- HAL_ICACHE_InvalidateCompleteCallback() : Maintenance Callback.
- HAL_ICACHE_RegisterErrorCallback() to initialize the Error callback pointer.
- HAL_ICACHE_RegisterInvalidateCompleteCallback() to initialize the Invalidate callback pointer.
  * @note The register user callback functions can be used only if USE_HAL_ICACHE_REGISTER_CALLBACKS = 1
  */

/**
  * @brief  Handle the ICACHE interrupt request.
  * @param  hicache Pointer to the ICACHE handle.
  * @note  This function must be called from ICACHE_IRQHandler().
  * @note  This function disables the interrupt related to a detected operation flag.
  */
void HAL_ICACHE_IRQHandler(hal_icache_handle_t *hicache)
{
  ICACHE_TypeDef *p_icachex;
  uint32_t it_flags_sources;

  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state, (uint32_t)HAL_ICACHE_STATE_MAINTENANCE | (uint32_t)HAL_ICACHE_STATE_ACTIVE);

  p_icachex = (ICACHE_TypeDef *)((uint32_t)hicache->instance);

  /* Get current interrupt flags and interrupt sources value */
  it_flags_sources = LL_ICACHE_READ_REG(p_icachex, SR);
  it_flags_sources &= LL_ICACHE_READ_REG(p_icachex, IER);

  /* Check ICACHE Error interrupt flag */
  if ((it_flags_sources & LL_ICACHE_SR_ERRF) != 0U)
  {
#if defined(USE_HAL_ICACHE_GET_LAST_ERRORS) && (USE_HAL_ICACHE_GET_LAST_ERRORS == 1)
    hicache->last_error_codes = HAL_ICACHE_ERROR_WRITE_INTRUSION;
#endif /* USE_HAL_ICACHE_GET_LAST_ERRORS */

    /* Clear ICACHE error pending flag */
    LL_ICACHE_ClearFlag_ERR(p_icachex);

    /* Call the Error callback */
#if defined(USE_HAL_ICACHE_REGISTER_CALLBACKS) && (USE_HAL_ICACHE_REGISTER_CALLBACKS == 1)
    hicache->p_error_cb(hicache);
#else
    HAL_ICACHE_ErrorCallback(hicache);
#endif /* USE_HAL_ICACHE_REGISTER_CALLBACKS */
  }

  if ((it_flags_sources & LL_ICACHE_SR_BSYENDF) != 0U)
  {
    /* Disable end of ICACHE invalidation interrupt */
    LL_ICACHE_DisableIT_BSYEND(p_icachex);

    /* Clear end of ICACHE invalidation interrupt flag */
    LL_ICACHE_ClearFlag_BSYEND(p_icachex);

    hicache->global_state = HAL_ICACHE_STATE_ACTIVE;

    /* Call the invalidate complete callback */
#if defined(USE_HAL_ICACHE_REGISTER_CALLBACKS) && (USE_HAL_ICACHE_REGISTER_CALLBACKS == 1)
    hicache->p_invalidate_cplt_cb(hicache);
#else
    HAL_ICACHE_InvalidateCompleteCallback(hicache);
#endif /* USE_HAL_ICACHE_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  ICACHE Error callback.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                 the handle information for the specified ICACHE instance.
  */
__WEAK void HAL_ICACHE_ErrorCallback(hal_icache_handle_t *hicache)
{
  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hicache);

  /* NOTE : This function must not be modified in this file, when the callback is needed,
            the HAL_ICACHE_ErrorCallback() must preferably be implemented in the user file
   */
}

/**
  * @brief  ICACHE Invalidate complete callback.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                 the handle information for the specified ICACHE instance.
  */
__WEAK void HAL_ICACHE_InvalidateCompleteCallback(hal_icache_handle_t *hicache)
{
  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hicache);

  /* NOTE : This function must not be modified in this file, when the callback is needed,
            the HAL_ICACHE_InvalidateCompleteCallback() can be implemented in the user file
   */
}

#if defined(USE_HAL_ICACHE_REGISTER_CALLBACKS) && (USE_HAL_ICACHE_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User ICACHE callback for error.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                 the handle information for the specified ICACHE instance.
  * @param  p_callback Pointer to the hal_icache_error_cb_t Error Callback function.
  * @note   The function is only available if USE_HAL_ICACHE_REGISTER_CALLBACKS = 1.
  * @retval HAL_OK Callback registered successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_ICACHE_RegisterErrorCallback(hal_icache_handle_t *hicache, hal_icache_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hicache != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state, (uint32_t)HAL_ICACHE_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hicache->p_error_cb = p_callback;
  return HAL_OK;
}

/**
  * @brief  Register a User ICACHE callback for invalidate.
  * @param hicache Pointer to a hal_icache_handle_t structure that contains
  *                the handle information for the specified ICACHE instance.
  * @param p_callback Pointer to the hal_icache_cb_t Callback function.
  * @note   The function is only available if USE_HAL_ICACHE_REGISTER_CALLBACKS = 1.
  * @retval HAL_OK Callback registered successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_ICACHE_RegisterInvalidateCompleteCallback(hal_icache_handle_t *hicache, hal_icache_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hicache != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hicache->global_state, (uint32_t)HAL_ICACHE_STATE_IDLE | (uint32_t)HAL_ICACHE_STATE_ACTIVE);

  hicache->p_invalidate_cplt_cb = p_callback;
  return HAL_OK;
}
#endif  /* USE_HAL_ICACHE_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @addtogroup ICACHE_Exported_Functions_Group8
  * @{
The function is :
- HAL_ICACHE_GetState() to retrieve the state value.
  */
/**
  * @brief  Get the ICACHE handle state.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                 the handle information for the specified ICACHE instance.
  * @retval HAL_ICACHE_STATE_RESET ICACHE driver not initialized and not started.
  * @retval HAL_ICACHE_STATE_IDLE ICACHE driver initialized and not started.
  * @retval HAL_ICACHE_STATE_ACTIVE ICACHE driver initialized and started.
  * @retval HAL_ICACHE_STATE_MAINTENANCE ICACHE driver initialized, started and a maintenance operation is ongoing.
  */
hal_icache_state_t HAL_ICACHE_GetState(const hal_icache_handle_t *hicache)
{
  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  return hicache->global_state;
}

/**
  * @}
  */

#if defined(USE_HAL_ICACHE_GET_LAST_ERRORS) && (USE_HAL_ICACHE_GET_LAST_ERRORS == 1)
/** @addtogroup ICACHE_Exported_Functions_Group9
  * @{
This section permits to get in runtime the last error codes of the peripheral ICACHE.
- HAL_ICACHE_GetLastErrorCodes() to get the ICACHE last error codes.
  */
/**
  * @brief  Get the ICACHE last error codes.
  * @param  hicache Pointer to a hal_icache_handle_t structure that contains
  *                 the handle information for the specified ICACHE instance.
  * @retval HAL_ICACHE_ERROR_NONE
  * @retval HAL_ICACHE_ERROR_WRITE_INTRUSION
  */
uint32_t HAL_ICACHE_GetLastErrorCodes(const hal_icache_handle_t *hicache)
{
  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Return the ICACHE last error codes */
  return hicache->last_error_codes;
}

/**
  * @}
  */
#endif /* USE_HAL_ICACHE_GET_LAST_ERRORS */

#if defined(USE_HAL_ICACHE_USER_DATA) && (USE_HAL_ICACHE_USER_DATA == 1)
/** @addtogroup ICACHE_Exported_Functions_Group10
  * @{
This section provides functions allowing to Set and Get user data:
- HAL_ICACHE_SetUserData() to store the user data into the ICACHE handle.
- HAL_ICACHE_GetUserData() retrieve the user data from the ICACHE handle.
  */

/**
  * @brief Store the user data into the ICACHE handle.
  * @param hicache Pointer to a hal_icache_handle_t structure that contains
  *                the handle information for the specified ICACHE instance.
  * @param p_user_data Pointer to the user data.
  */
void HAL_ICACHE_SetUserData(hal_icache_handle_t *hicache, const void *p_user_data)
{
  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  /* Set user data */
  hicache->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the user data from the ICACHE handle.
  * @param hicache Pointer to a hal_icache_handle_t structure that contains
  *                the handle information for the specified ICACHE instance.
  * @retval Pointer to the user data.
  */
const void *HAL_ICACHE_GetUserData(const hal_icache_handle_t *hicache)
{
  /* Check the ICACHE handle allocation */
  ASSERT_DBG_PARAM(hicache != NULL);

  return (hicache->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_ICACHE_USER_DATA */

/**
  * @}
  */

#endif /* USE_HAL_ICACHE_MODULE */

/**
  * @}
  */

/**
  * @}
  */
