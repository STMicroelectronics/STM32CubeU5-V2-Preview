/**
  ******************************************************************************
  * @file    stm32u5xx_hal_dcache.c
  * @brief   DCACHE HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the DCACHE.
  *           + Initialization and Configuration
  *           + Cache coherency command
  *           + Monitoring management
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

/** @addtogroup DCACHE
  * @{
# DCACHE Introduction
    The data cache (DCACHE) is introduced on S-AHB system bus of
    the Cortex-M33 processor to improve the performance of data
    traffic to/from external memories. Some specific features like
    hit-under-miss and critical-word-first refill policy allow
    optimum performance on external memories data accesses.

# Main features
The main features of DCACHE are described below:

- Bus interface
  - one 32-Bit AHB slave port, the system port (input from Cortex-M33 S-AHB system Interface)
  - one 32-bit AHB master port (output to main AHB bus matrix)
  - one 32-bit AHB slave port for control (input from AHB peripherals interconnect, for DCACHE registers access)

- Cache access
  - 0 wait-state on hits
  - Hit-under-miss capability: ability to serve processor requests (access to cached data) during an ongoing line refill
   due to a previous cache miss
  - Optimized cache line refill thanks to WRAP bursts of the size of the cache line (such as WRAP4 for 128-bit cache
  line)
  - 2-ways set-associative
  - Supports both write-back and write-through policies (selectable with AHB bufferable attribute)
  - Read and write-back always allocate
  - Write-through always non-allocate (write-around)
  - Supports byte, half-word, and word writes

- Replacement and refill
  - pLRU-t replacement policy (pseudo-least-recently-used, based on binary tree), algorithm with best
  complexity/performance balance
  - Critical-word-first refill policy for read transactions, minimizing processor stalls
  - Possibility to configure burst type of all AHB memory transactions: INCRw or WRAPw
  (size w aligned on cache line size)

- Performance counters
  DCACHE implements four performance counters:
 - Two hit monitor counters (32-bit): number of read hits, number of write hits
 - Two miss monitor counters (16-bit): number of read misses, number of write misses

- Error management
  - Possibility to detect error for master port request initiated by DCACHE itself (a cache line written back
  into main memory, because of an eviction or a clean   operation), to flag this error, and optionally to raise
  an interrupt

- Trust Zone security support

- Maintenance operations
 - Cache invalidate: full cache invalidation
 - Cache invalidates range: invalidates cache lines
 - Cache clean range: cleans cache lines
 - Cache clean and invalidate range: cleans and invalidates cache lines

# How to use the HAL DCACHE driver
## The HAL DCACHE driver can be used as follows:
### Main use

- Initialize the DCACHE according to the associated handle with HAL_DCACHE_Init().
   DCACHE Clock is disabled by default but can be enabled in setting USE_HAL_DCACHE_CLK_ENABLE_MODEL
   to HAL_CLK_ENABLE_PERIPH_ONLY.
- Set the configuration of the DCACHE to choose the Read Burst Type with HAL_DCACHE_SetReadBurstType().
   This operation is optional, the user can keep the default configuration which is DCACHE_READ_BURST_WRAP.
- Then Start the DCACHE driver with HAL_DCACHE_Start().
   You can enable the Error interrupt detection and allow to receive callbacks in case of eviction
   or clean fails error.
- Execute the DCACHE maintenance operations if necessary :
  - Use HAL_DCACHE_Invalidate() to invalidate the full cache content:
    - Cache content is lost, and reloaded when needed.
    - Used for complete invalidate of the DCACHE in case.
    - Blocking call until operation is done.
  - Use HAL_DCACHE_InvalidateByAddr() to invalidate cache content for specific range:
    - Cache content for specific range is lost, and reloaded when needed.
    - Used when excepting a buffer to be updated by a peripheral (typically DMA transfer).
    - Blocking call until operation is done.
  - Use HAL_DCACHE_CleanByAddr() to clean cache content for a specific range:
    - Cache content for specific range is written back to memory.
    - Used when buffer is updated by CPU before usage by a peripheral (typically DMA transfer).
    - Blocking call until operation is done.
  - Use HAL_DCACHE_CleanInvalidByAddr() to clean and invalidate cache content for a specific range:
    - Cache content for specific range is written back to memory, and reloaded when needed.
    - Used when sharing buffer between CPU and other peripheral.
    - Recommended to use for MPU reprogramming.
    - Blocking call until operation is done.

### Monitoring performance
- The performance monitoring Read Hit, Read Miss, Write Hit and Write Miss counters can be used as follows :
HAL_DCACHE_EnableMonitors() and HAL_DCACHE_DisableMonitors() respectively enable and disable any monitors.
To retrieve the counters value use HAL_DCACHE_GetMonitorReadHitValue(), HAL_DCACHE_GetMonitorReadMissValue(),
HAL_DCACHE_GetMonitorWriteHitValue() or HAL_DCACHE_GetMonitorWriteMissValue() functions.
HAL_DCACHE_ResetMonitors() function allows to clear any monitors value.

### Interrupt Mode
- The DCACHE provides three sources of interrupt :
  - The error interrupt.
  - The invalidate completion interrupt.
  - The cache command completion interrupt.

- For each interrupt, there is a corresponding callback launched in the HAL_DCACHE_IRQHandler() function.
- In case of interrupt, depending which registering callback method used, it either triggers the weak callback
 or the register one.

- Error :
  - Override weak definition for following callbacks:
     - HAL_DCACHE_ErrorCallback()
  - Or use register callbacks (USE_HAL_DCACHE_REGISTER_CALLBACKS = 1):
     - HAL_DCACHE_RegisterErrorCallback()
  - Start the DCACHE driver with HAL_DCACHE_Start(hdcache,HAL_DCACHE_IT_ERROR) as explain above.

- Maintenance operation:
  - Override weak definition for following callbacks:
     - HAL_DCACHE_InvalidateCompleteCallback()
     - HAL_DCACHE_CleanInvalidByAddrCallback()
     - HAL_DCACHE_InvalidateByAddrCallback()
     - HAL_DCACHE_CleanByAddrCallback()
  - Or use register callbacks (USE_HAL_DCACHE_REGISTER_CALLBACKS = 1):
     - HAL_DCACHE_RegisterInvalidateCompleteCallback()
     - HAL_DCACHE_RegisterCleanInvalidByAddrCallback()
     - HAL_DCACHE_RegisterInvalidateByAddrCallback()
     - HAL_DCACHE_RegisterCleanByAddrCallback()
  - Launch a maintenance operation with Interrupt: HAL_DCACHE_Invalidate_IT(), HAL_DCACHE_InvalidateByAddr_IT(),
     HAL_DCACHE_CleanByAddr_IT() or HAL_DCACHE_CleanInvalidByAddr_IT().

## HAL DCACHE Driver State
- Use HAL_DCACHE_GetState() function to return the HAL DCACHE state.

## Configuration inside the DCACHE driver:

Config defines                    | Description     | Default value     | Note                                         |
--------------------------------- | ----------------| -------------     | ---------------------------------------------|
USE_HAL_ICACHE_MODULE             | From hal_conf.h |       1           | Allows to use HAL ICACHE module.             |
USE_HAL_ICACHE_REGISTER_CALLBACKS | From hal_conf.h |       0           | Allows to use the register callbacks.        |
USE_HAL_CHECK_PARAM               | From hal_conf.h |       0           | Allows to use the run-time checks parameters.|
USE_ASSERT_DBG_PARAM              | From IDE        |       NA          | Allows to use the assert check parameters.   |
USE_ASSERT_DBG_STATE              | From IDE        |       NA          | Allows to use the assert check states.       |
USE_HAL_DCACHE_CLK_ENABLE_MODEL   | from hal_conf.h | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock.   |
USE_HAL_ICACHE_GET_LAST_ERRORS    | From hal_conf.h |       1           | Allow to use error code mechanism.           |
USE_HAL_ICACHE_USER_DATA          | From hal_conf.h |       0           | Allows to use user data.                     |
  */

#if defined (DCACHE1) || defined (DCACHE2)
#if defined(USE_HAL_DCACHE_MODULE) && (USE_HAL_DCACHE_MODULE == 1)

/* Private defines -----------------------------------------------------------*/
/** @defgroup DCACHE_Private_Defines DCACHE Private Defines
  * @{
  */
#if defined(FMC_BASE)
#define START_ADDRESS FMC_BASE                         /*!< Start address to cache: 0x6000 0000 */
#if defined(HSPI1_BASE)
#define MAX_SIZE 0x50000000UL                          /*!< Address range cacheable: 0x6000 0000 - 0xAFFF FFFF */
#else
#define MAX_SIZE 0x40000000UL                          /*!< Address range cacheable: 0x6000 0000 - 0x9FFF FFFF */
#endif /* HSPI1_BASE */
#else
#define START_ADDRESS OCTOSPI1_BASE                    /*!< Start address to cache: 0x9000 0000 */
#define MAX_SIZE 0x10000000UL                          /*!< Address range cacheable: 0x9000 0000 - 0x9FFF FFFF */
#endif /* FMC_BASE */
#define DCACHE_COMMAND_TIMEOUT_VALUE           600U    /*!< 600ms */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup DCACHE_Private_Macros DCACHE Private Macros
  * @{
  */
/**
  * @brief Size range
  */
#define IS_DCACHE_SIZE(size)        ((0UL < (size)) \
                                     && ((size) <= MAX_SIZE))

/**
  * @brief Address range
  */
#define IS_DCACHE_ADDRESS(addr)        ((START_ADDRESS <= (addr)) \
                                        && ((addr) < (START_ADDRESS + MAX_SIZE)))

/**
  * @brief Monitor type
  */
#define IS_DCACHE_MONITOR_TYPE(type)        (((type) & ~HAL_DCACHE_MONITOR_ALL) == 0U)

/**
  * @brief Interrupt
  */
#define IS_DCACHE_IT(it)        (((it & ~HAL_DCACHE_IT_ALL) == 0UL))

/**
  * @brief Read Burst Type
  */
#define IS_DCACHE_READ_BURST_TYPE(type)  (((type) == HAL_DCACHE_READ_BURST_WRAP) \
                                          || ((type) == HAL_DCACHE_READ_BURST_INCR))
/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup DCACHE_Private_Functions DCACHE Private Functions
  * @{
  */
static void DCACHE_CommandByAddr(hal_dcache_handle_t *hdcache, uint32_t command, uint32_t addr, uint32_t size_byte);
static hal_status_t DCACHE_WaitOnFlagUntilTimeout(hal_dcache_handle_t *hdcache, uint32_t flag);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup DCACHE_Exported_Functions
  * @{
  */

/** @addtogroup DCACHE_Exported_Functions_Group1
  * @{
  * This section provides a set of functions allowing to initialize and deinitialize the DCACHE peripheral:
  *  - Call the function HAL_DCACHE_Init() to initialize the selected DCACHE handle and associate an instance.
  *  - Call the function HAL_DCACHE_DeInit():
  *    - to reset the DCACHE to the initial state by resetting the monitors,
  *    - to reset the burst type to WRAP mode
  *    - to disable interrupts,
  *    - to reset and stop ongoing commands if any,
  *    - to stop the cache and clear the flags.
  */

/**
  * @brief  Initialize the DCACHE according to the associated handle.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *              the handle information for the specified DCACHE.
  * @param  instance DCACHE instance.
  * @retval HAL_INVALID_PARAM When the handle is NULL.
  * @retval HAL_OK            HAL DCACHE driver correctly Initialized for the given DCACHE instance.
  */
hal_status_t HAL_DCACHE_Init(hal_dcache_handle_t *hdcache, hal_dcache_t instance)
{
  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  ASSERT_DBG_PARAM(IS_DCACHE_ALL_INSTANCE((DCACHE_TypeDef *)((uint32_t)instance)));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the handle struct pointer */
  if (hdcache == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdcache->instance = instance;

#if defined(USE_HAL_DCACHE_CLK_ENABLE_MODEL) && (USE_HAL_DCACHE_CLK_ENABLE_MODEL == HAL_CLK_ENABLE_PERIPH_ONLY)

  if (hdcache->instance == HAL_DCACHE1)
  {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DCACHE1);
  }

#if defined(DCACHE2)
  else /* (hdcache->instance == HAL_DCACHE2) */
  {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DCACHE2);
  }
#endif /* DCACHE2 */

#endif /* USE_HAL_DCACHE_CLK_ENABLE_MODEL */

#if defined(USE_HAL_DCACHE_REGISTER_CALLBACKS) && (USE_HAL_DCACHE_REGISTER_CALLBACKS == 1)
  /* Initialize the DCACHE Callback settings */
  hdcache->p_clean_by_addr_cb = HAL_DCACHE_CleanByAddrCallback; /* Clean by Address callback */
  hdcache->p_invalidate_by_addr_cb = HAL_DCACHE_InvalidateByAddrCallback; /* Invalidate by Address callback */
  hdcache->p_invalidate_cplt_cb = HAL_DCACHE_InvalidateCompleteCallback; /* Invalidate Complete callback */
  hdcache->p_clean_invalid_by_addr_cb = HAL_DCACHE_CleanInvalidByAddrCallback; /* Clean and Invalidate by
                                                                                  Address callback */
  hdcache->p_error_cb = HAL_DCACHE_ErrorCallback; /* Error callback */
#endif /* USE_HAL_DCACHE_REGISTER_CALLBACKS */

#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
  /* In case of single process at a time: one single variable storing the last errors */
  hdcache->last_error_codes = HAL_DCACHE_ERROR_NONE;
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

  /* Initialize the DCACHE handle global_state */
  hdcache->global_state = HAL_DCACHE_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  DeInitialize the Data Cache.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @note   The goal of this function is to reset the DCACHE to the initial state:
  *           - stop the DCACHE,
  *           - disable and reset the monitors,
  *           - reset the burst type to WRAP mode
  *           - disable interrupts,
  *           - clear the interrupt flags,
  *           - and reset the last error code.
  */
void HAL_DCACHE_DeInit(hal_dcache_handle_t *hdcache)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, \
                   (uint32_t)HAL_DCACHE_STATE_IDLE | \
                   (uint32_t)HAL_DCACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_DCACHE_STATE_MAINTENANCE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  LL_DCACHE_Disable(p_dcachex);

  LL_DCACHE_ResetMonitors(p_dcachex, LL_DCACHE_MONITOR_ALL);

  /* Reset the Control Register: burst type to WRAP, command operation finished, DCACHE and
     monitors disabled */
  LL_DCACHE_WRITE_REG(p_dcachex, CR, 0U);

  /* Reset the Interrupt Enable Register: clear ERRIE, CMDENDIE and BSYENDIE flags */
  LL_DCACHE_WRITE_REG(p_dcachex, IER, 0U);

  /* Reset the Flag Clear Register: clear ERR, CMDEND and BSYEND flags */
  LL_DCACHE_WRITE_REG(p_dcachex, FCR, LL_DCACHE_FCR_CERRF |
                      LL_DCACHE_FCR_CBSYENDF | LL_DCACHE_FCR_CCMDENDF);

#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
  hdcache->last_error_codes = HAL_DCACHE_ERROR_NONE;
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

  /* Return to the reset state */
  hdcache->global_state = HAL_DCACHE_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup DCACHE_Exported_Functions_Group2
  * @{
  * This section provides a set of functions allowing to configure the DCACHE peripheral:
  * - Call the function HAL_DCACHE_SetReadBurstType() to set the Read Burst Type.
  * - Call the function HAL_DCACHE_GetReadBurstType() to retrieve the value of the Read Burst Type.
  */

/**
  * @brief  Set the Read Burst Type.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                the handle information for the specified DCACHE instance.
  * @param  read_burst_type Burst Type to be applied.
  * @note   If DCACHE is enabled, the read burst type cannot be set.
  * @retval HAL_OK DCACHE instance has been correctly configured.
  */
hal_status_t HAL_DCACHE_SetReadBurstType(hal_dcache_handle_t *hdcache, hal_dcache_read_burst_t read_burst_type)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  ASSERT_DBG_PARAM(IS_DCACHE_READ_BURST_TYPE(read_burst_type));

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, HAL_DCACHE_STATE_IDLE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  LL_DCACHE_SetReadBurstType(p_dcachex, (uint32_t)read_burst_type);

  return HAL_OK;
}

/**
  * @brief Get the Read Burst Type.
  * @param hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                the handle information for the specified DCACHE instance.
  * @retval HAL_DCACHE_READ_BURST_WRAP WRAP Configuration
  * @retval HAL_DCACHE_READ_BURST_INCR INCR Configuration
  */
hal_dcache_read_burst_t HAL_DCACHE_GetReadBurstType(const hal_dcache_handle_t *hdcache)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  return (hal_dcache_read_burst_t)LL_DCACHE_GetReadBurstType(p_dcachex);
}

/**
  * @}
  */

/** @addtogroup DCACHE_Exported_Functions_Group3
  * @{
  * The functions are :
  * - HAL_DCACHE_Start() to start the DCACHE with error interrupt control.
  * - HAL_DCACHE_Stop() to stop the DCACHE.
  */

/**
  * @brief  Start the Data cache.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @param  interrupts Interrupts
  *            @arg HAL_DCACHE_IT_NONE
  *            @arg HAL_DCACHE_IT_ERROR
  * @note This function can enable the interrupts, and starts the DCACHE.
  * @retval HAL_OK Only success, even if there is any ongoing cache operation.
  */
hal_status_t HAL_DCACHE_Start(hal_dcache_handle_t *hdcache, uint32_t interrupts)
{
  DCACHE_TypeDef *p_dcachex;

  ASSERT_DBG_PARAM(hdcache != NULL);
  ASSERT_DBG_PARAM(IS_DCACHE_IT(interrupts));

  ASSERT_DBG_STATE(hdcache->global_state, HAL_DCACHE_STATE_IDLE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  HAL_CHECK_UPDATE_STATE(hdcache, global_state, HAL_DCACHE_STATE_IDLE, HAL_DCACHE_STATE_ACTIVE);

#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
  hdcache->last_error_codes = HAL_DCACHE_ERROR_NONE;
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

  LL_DCACHE_WRITE_REG(p_dcachex, IER, interrupts);

  LL_DCACHE_Enable(p_dcachex);

  return HAL_OK;
}

/**
  * @brief  Stop the Data cache.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @note This function disables interrupts, clears the flags and stops the DCACHE.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_DCACHE_Stop(hal_dcache_handle_t *hdcache)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, \
                   (uint32_t)HAL_DCACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_DCACHE_STATE_MAINTENANCE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  LL_DCACHE_Disable(p_dcachex);

  LL_DCACHE_DisableIT_ERR(p_dcachex);

  LL_DCACHE_ClearFlag_ERR(p_dcachex);

  hdcache->global_state = HAL_DCACHE_STATE_IDLE;

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup DCACHE_Exported_Functions_Group5
  * @{
  * This section provides functions allowing to monitor Data Cache:
  *  - Call HAL_DCACHE_EnableMonitors() to enable the Data Cache performance monitoring.
  *  - Call HAL_DCACHE_DisableMonitors() to disable the Data Cache performance monitoring.
  *  - Call HAL_DCACHE_ResetMonitors() to reset the Data Cache performance monitoring values.
  *  - Call HAL_DCACHE_GetMonitorReadHitValue() to get the Data Cache performance Read Hit monitoring value.
  *  - Call HAL_DCACHE_GetMonitorReadMissValue() to get the Data Cache performance Read Miss monitoring value.
  *  - Call HAL_DCACHE_GetMonitorWriteHitValue() to get the Data Cache performance Write Hit monitoring value.
  *  - Call HAL_DCACHE_GetMonitorWriteMissValue() to get the Data Cache performance Write Miss monitoring value.
  */

/**
  * @brief  Enable the Data Cache performance monitoring.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @param  monitor_type This parameter can be a combination of the following values:
  *            @arg HAL_DCACHE_MONITOR_READ_HIT
  *            @arg HAL_DCACHE_MONITOR_READ_MISS
  *            @arg HAL_DCACHE_MONITOR_WRITE_HIT
  *            @arg HAL_DCACHE_MONITOR_WRITE_MISS
  *            @arg HAL_DCACHE_MONITOR_ALL
  * @retval HAL_OK DCACHE Monitor(s) enabled successfully.
  */
hal_status_t HAL_DCACHE_EnableMonitors(hal_dcache_handle_t *hdcache, uint32_t monitor_type)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the parameters */
  ASSERT_DBG_PARAM(IS_DCACHE_MONITOR_TYPE(monitor_type));

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state,
                   (uint32_t)HAL_DCACHE_STATE_IDLE | \
                   (uint32_t)HAL_DCACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_DCACHE_STATE_MAINTENANCE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  LL_DCACHE_EnableMonitors(p_dcachex, monitor_type);

  return HAL_OK;
}

/**
  * @brief  Disable the Data Cache performance monitoring.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @note   Stopping the monitoring does not reset the values.
  * @param  monitor_type This parameter can be a combination of the following values:
  *            @arg HAL_DCACHE_MONITOR_READ_HIT
  *            @arg HAL_DCACHE_MONITOR_READ_MISS
  *            @arg HAL_DCACHE_MONITOR_WRITE_HIT
  *            @arg HAL_DCACHE_MONITOR_WRITE_MISS
  *            @arg HAL_DCACHE_MONITOR_ALL
  * @retval HAL_OK DCACHE Monitor(s) disabled successfully.
  */
hal_status_t HAL_DCACHE_DisableMonitors(hal_dcache_handle_t *hdcache, uint32_t monitor_type)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the parameters */
  ASSERT_DBG_PARAM(IS_DCACHE_MONITOR_TYPE(monitor_type));

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state,
                   (uint32_t)HAL_DCACHE_STATE_IDLE | \
                   (uint32_t)HAL_DCACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_DCACHE_STATE_MAINTENANCE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  LL_DCACHE_DisableMonitors(p_dcachex, monitor_type);

  return HAL_OK;
}

/**
  * @brief  Reset the Data Cache performance monitoring values.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @param  monitor_type This parameter can be a combination of the following values:
  *            @arg HAL_DCACHE_MONITOR_READ_HIT
  *            @arg HAL_DCACHE_MONITOR_READ_MISS
  *            @arg HAL_DCACHE_MONITOR_WRITE_HIT
  *            @arg HAL_DCACHE_MONITOR_WRITE_MISS
  *            @arg HAL_DCACHE_MONITOR_ALL
  * @retval HAL_OK DCACHE Monitor(s) reset successfully.
  */
hal_status_t HAL_DCACHE_ResetMonitors(hal_dcache_handle_t *hdcache, uint32_t monitor_type)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the parameters */
  ASSERT_DBG_PARAM(IS_DCACHE_MONITOR_TYPE(monitor_type));

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state,
                   (uint32_t)HAL_DCACHE_STATE_IDLE | \
                   (uint32_t)HAL_DCACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_DCACHE_STATE_MAINTENANCE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  /* Force/Release reset */
  LL_DCACHE_ResetMonitors(p_dcachex, monitor_type);

  return HAL_OK;
}

/**
  * @brief  Get the Data Cache performance Read Hit monitoring value.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @note   Upon reaching the maximum value, monitor does not wrap.
  * @retval uint32_t Read Hit monitoring value
  */
uint32_t HAL_DCACHE_GetMonitorReadHitValue(const hal_dcache_handle_t *hdcache)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state,
                   (uint32_t)HAL_DCACHE_STATE_IDLE | \
                   (uint32_t)HAL_DCACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_DCACHE_STATE_MAINTENANCE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  return LL_DCACHE_Monitor_GetReadHitValue(p_dcachex);
}

/**
  * @brief  Get the Data Cache performance Read Miss monitoring value.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @note   Upon reaching the maximum value, monitor does not wrap.
  * @retval uint32_t Read Miss monitoring value.
  */
uint32_t HAL_DCACHE_GetMonitorReadMissValue(const hal_dcache_handle_t *hdcache)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state,
                   (uint32_t)HAL_DCACHE_STATE_IDLE | \
                   (uint32_t)HAL_DCACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_DCACHE_STATE_MAINTENANCE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  return LL_DCACHE_Monitor_GetReadMissValue(p_dcachex);
}

/**
  * @brief  Get the Data Cache performance Write Hit monitoring value.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @note   Upon reaching the maximum value, monitor does not wrap.
  * @retval uint32_t Write Hit monitoring value
  */
uint32_t HAL_DCACHE_GetMonitorWriteHitValue(const hal_dcache_handle_t *hdcache)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state,
                   (uint32_t)HAL_DCACHE_STATE_IDLE | \
                   (uint32_t)HAL_DCACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_DCACHE_STATE_MAINTENANCE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  return LL_DCACHE_Monitor_GetWriteHitValue(p_dcachex);
}

/**
  * @brief  Get the Data Cache performance Write Miss monitoring value.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @note   Upon reaching the maximum value, monitor does not wrap.
  * @retval uint32_t Write Miss monitoring value
  */
uint32_t HAL_DCACHE_GetMonitorWriteMissValue(const hal_dcache_handle_t *hdcache)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state,
                   (uint32_t)HAL_DCACHE_STATE_IDLE | \
                   (uint32_t)HAL_DCACHE_STATE_ACTIVE | \
                   (uint32_t)HAL_DCACHE_STATE_MAINTENANCE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  return LL_DCACHE_Monitor_GetWriteMissValue(p_dcachex);
}

/**
  * @}
  */

/** @addtogroup DCACHE_Exported_Functions_Group6
  * @{
  * This section provides functions allowing to launch maintenance operation:
  *  - Call HAL_DCACHE_Invalidate() to invalidate the Data cache in polling mode.
  *  - Call HAL_DCACHE_Invalidate_IT() to BUSY END interrupt bit enable and to invalidate the Data cache.
  *  - Call HAL_DCACHE_InvalidateByAddr() to invalidate by Address the Data cache in polling mode.
  *  - Call HAL_DCACHE_InvalidateByAddr_IT() to CMD END interrupt bit enable and to invalidate by Address the Data
  *    cache.
  *  - Call HAL_DCACHE_CleanByAddr() to clean by Address the Data cache in polling mode.
  *  - Call HAL_DCACHE_CleanByAddr_IT() to CMD END interrupt bit enable and to clean by Address the Data cache.
  *  - Call HAL_DCACHE_CleanInvalidByAddr() to clean invalidate by Address the Data cache in polling mode.
  *  - Call HAL_DCACHE_CleanInvalidByAddr_IT() to CMD END interrupt bit enable and to clean invalidate by Address the
  *    Data cache.
  */

/**
  * @brief  Invalidate the Data cache.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @note   This function waits for end of full cache invalidation
  * @retval HAL_ERROR         Operation error.
  * @retval HAL_BUSY          DCACHE driver busy with another ongoing operation.
  * @retval HAL_OK            DCACHE Invalidate operation ended successfully.
  */
hal_status_t HAL_DCACHE_Invalidate(hal_dcache_handle_t *hdcache)
{
  DCACHE_TypeDef *p_dcachex;
  hal_status_t status = HAL_OK;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, HAL_DCACHE_STATE_ACTIVE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
  hdcache->last_error_codes = HAL_DCACHE_ERROR_NONE;
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

  /* Check no ongoing operation */
  if (LL_DCACHE_IsActiveFlag(p_dcachex,
                             LL_DCACHE_SR_BUSYF | LL_DCACHE_SR_BUSYCMDF) != 0U)
  {
    status = HAL_BUSY;
  }
  else
  {
    hdcache->global_state = HAL_DCACHE_STATE_MAINTENANCE;

    /* Make sure flags are reset */
    LL_DCACHE_ClearFlag(p_dcachex,
                        LL_DCACHE_FCR_CBSYENDF | LL_DCACHE_FCR_CCMDENDF);

    /* Launch DCACHE invalidation */
    LL_DCACHE_Invalidate(p_dcachex);

    if (HAL_OK != DCACHE_WaitOnFlagUntilTimeout(hdcache, LL_DCACHE_SR_BSYENDF))
    {
      status = HAL_ERROR;
    }
  }

  hdcache->global_state = HAL_DCACHE_STATE_ACTIVE;

#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
  uint32_t error_flags = LL_DCACHE_IsActiveFlag(p_dcachex, LL_DCACHE_SR_ERRF);
  if (error_flags != 0U)
  {
    hdcache->last_error_codes = HAL_DCACHE_ERROR_EVICTION_CLEAN;
    status = HAL_ERROR;
  }
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

  return status;
}

/**
  * @brief  Invalidate the Data cache with interrupt.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @note   This function launches maintenance operation and returns immediately.
  *         User must rely on the corresponding callback.
  * @retval HAL_BUSY          DCACHE driver busy with another ongoing operation.
  * @retval HAL_OK            DCACHE Invalidate operation started successfully.
  */
hal_status_t HAL_DCACHE_Invalidate_IT(hal_dcache_handle_t *hdcache)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, HAL_DCACHE_STATE_ACTIVE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  /* Check no ongoing operation */
  if (LL_DCACHE_IsActiveFlag(p_dcachex,
                             LL_DCACHE_SR_BUSYF | LL_DCACHE_SR_BUSYCMDF) != 0U)
  {
    return HAL_BUSY;
  }
  else
  {

    hdcache->global_state = HAL_DCACHE_STATE_MAINTENANCE;

    /* Make sure flags are reset */
    LL_DCACHE_ClearFlag(p_dcachex,
                        LL_DCACHE_FCR_CBSYENDF | LL_DCACHE_FCR_CCMDENDF);

    /* Set no operation on address range */
    LL_DCACHE_SetCommand(p_dcachex, LL_DCACHE_COMMAND_NO_OPERATION);

    /* Enable end of DCACHE invalidation interrupt line */
    LL_DCACHE_EnableIT_BSYEND(p_dcachex);

    /* Launch DCACHE invalidation */
    LL_DCACHE_Invalidate(p_dcachex);

    return HAL_OK;
  }
}

/**
  * @brief  Invalidate the Data cache by Address.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @param  addr Start address of the region to be Invalidated
  * @param  size_byte Size of the region to be Invalidated (in bytes)
  * @note   This function waits for end of DCACHE Invalidation.
  * @note   The Address must be aligned on 16 bytes and
  *         the Size must be a multiple of 16 or 32 bytes, it depends on U5 series (check the reference manual).
  * @retval HAL_ERROR         Operation error.
  * @retval HAL_BUSY          DCACHE driver busy with another ongoing operation.
  * @retval HAL_OK            DCACHE Invalidate by Address operation ended successfully.
  */

hal_status_t HAL_DCACHE_InvalidateByAddr(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte)
{
  DCACHE_TypeDef *p_dcachex;
  hal_status_t status = HAL_OK;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the parameters */
  ASSERT_DBG_PARAM(IS_DCACHE_SIZE(size_byte));
  ASSERT_DBG_PARAM(IS_DCACHE_ADDRESS(addr));

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, HAL_DCACHE_STATE_ACTIVE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
  hdcache->last_error_codes = HAL_DCACHE_ERROR_NONE;
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

  /* Check no ongoing operation */
  if (LL_DCACHE_IsActiveFlag(p_dcachex,
                             LL_DCACHE_SR_BUSYF | LL_DCACHE_SR_BUSYCMDF) != 0U)
  {
    status = HAL_BUSY;
  }
  else
  {
    hdcache->global_state = HAL_DCACHE_STATE_MAINTENANCE;

    DCACHE_CommandByAddr(hdcache, LL_DCACHE_COMMAND_INVALIDATE_BY_ADDR, addr, size_byte);

    /* Launch DCACHE command */
    LL_DCACHE_StartCommand(p_dcachex);

    if (HAL_OK != DCACHE_WaitOnFlagUntilTimeout(hdcache, LL_DCACHE_SR_CMDENDF))
    {
      status = HAL_ERROR;
    }
  }

  hdcache->global_state = HAL_DCACHE_STATE_ACTIVE;

#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
  uint32_t error_flags = LL_DCACHE_IsActiveFlag(p_dcachex, LL_DCACHE_SR_ERRF);
  if (error_flags != 0U)
  {
    hdcache->last_error_codes = HAL_DCACHE_ERROR_EVICTION_CLEAN;
    status = HAL_ERROR;
  }
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

  return status;
}

/**
  * @brief  Invalidate the Data cache by Address with interrupt.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @param  addr Start address of the region to be Invalidated
  * @param  size_byte Size of the region to be Invalidated
  * @note   This function launches maintenance operation and returns immediately.
  *         User must rely on the corresponding callback.
  * @note   The Address must be aligned on 16 bytes and
  *         the Size must be a multiple of 16 or 32 bytes, it depends on U5 series (check the reference manual).
  * @retval HAL_BUSY          DCACHE driver busy with another ongoing operation.
  * @retval HAL_OK            DCACHE Invalidate by Address operation started successfully.
  */
hal_status_t HAL_DCACHE_InvalidateByAddr_IT(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the parameters */
  ASSERT_DBG_PARAM(IS_DCACHE_SIZE(size_byte));
  ASSERT_DBG_PARAM(IS_DCACHE_ADDRESS(addr));

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, HAL_DCACHE_STATE_ACTIVE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  /* Check no ongoing operation */
  if (LL_DCACHE_IsActiveFlag(p_dcachex,
                             LL_DCACHE_SR_BUSYF | LL_DCACHE_SR_BUSYCMDF) != 0U)
  {
    return HAL_BUSY;
  }

  hdcache->global_state = HAL_DCACHE_STATE_MAINTENANCE;

  DCACHE_CommandByAddr(hdcache, LL_DCACHE_COMMAND_INVALIDATE_BY_ADDR, addr, size_byte);

  /* Enable end of DCACHE maintenance operation by address interrupt line */
  LL_DCACHE_EnableIT_CMDEND(p_dcachex);

  /* Launch cache command */
  LL_DCACHE_StartCommand(p_dcachex);

  return HAL_OK;
}

/**
  * @brief  Clean the Data cache by Address.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @param  addr Start address of the region to be Cleaned
  * @param  size_byte Size of the region to be Cleaned (in bytes)
  * @note   This function waits for end of DCACHE Clean.
  * @note   The Address must be aligned on 16 bytes and
  *         the Size must be a multiple of 16 or 32 bytes, it depends on U5 series (check the reference manual).
  * @retval HAL_ERROR         Operation error.
  * @retval HAL_BUSY          DCACHE driver busy with another ongoing operation.
  * @retval HAL_OK            DCACHE Clean by Address operation ended successfully.
  */
hal_status_t HAL_DCACHE_CleanByAddr(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte)
{
  DCACHE_TypeDef *p_dcachex;
  hal_status_t status = HAL_OK;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the parameters */
  ASSERT_DBG_PARAM(IS_DCACHE_SIZE(size_byte));
  ASSERT_DBG_PARAM(IS_DCACHE_ADDRESS(addr));

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, HAL_DCACHE_STATE_ACTIVE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
  hdcache->last_error_codes = HAL_DCACHE_ERROR_NONE;
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

  /* Check no ongoing operation */
  if (LL_DCACHE_IsActiveFlag(p_dcachex,
                             LL_DCACHE_SR_BUSYF | LL_DCACHE_SR_BUSYCMDF) != 0U)
  {
    status = HAL_BUSY;
  }
  else
  {
    hdcache->global_state = HAL_DCACHE_STATE_MAINTENANCE;

    DCACHE_CommandByAddr(hdcache, LL_DCACHE_COMMAND_CLEAN_BY_ADDR, addr, size_byte);

    /* Launch DCACHE command */
    LL_DCACHE_StartCommand(p_dcachex);

    if (HAL_OK != DCACHE_WaitOnFlagUntilTimeout(hdcache, LL_DCACHE_SR_CMDENDF))
    {
      status = HAL_ERROR;
    }

    hdcache->global_state = HAL_DCACHE_STATE_ACTIVE;
  }
#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
  {
    uint32_t error_flags = LL_DCACHE_IsActiveFlag(p_dcachex, LL_DCACHE_SR_ERRF);
    if (error_flags != 0U)
    {
      hdcache->last_error_codes = HAL_DCACHE_ERROR_EVICTION_CLEAN;
      status = HAL_ERROR;
    }
  }
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */
  return status;
}

/**
  * @brief  Clean the Data cache by Address with interrupt.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @param  addr Start address of the region to be Cleaned
  * @param  size_byte Size of the region to be Cleaned
  * @note   This function launches maintenance operation and returns immediately.
  *         User must rely on the corresponding callback.
  * @note   The Address must be aligned on 16 bytes and
  *         the Size must be a multiple of 16 or 32 bytes, it depends on U5 series (check the reference manual).
  * @retval HAL_BUSY          DCACHE driver busy with another ongoing operation.
  * @retval HAL_OK            DCACHE Clean by Address operation started successfully.
  */
hal_status_t HAL_DCACHE_CleanByAddr_IT(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the parameters */
  ASSERT_DBG_PARAM(IS_DCACHE_SIZE(size_byte));
  ASSERT_DBG_PARAM(IS_DCACHE_ADDRESS(addr));

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, HAL_DCACHE_STATE_ACTIVE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
  hdcache->last_error_codes = HAL_DCACHE_ERROR_NONE;
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

  /* Check no ongoing operation */
  if (LL_DCACHE_IsActiveFlag(p_dcachex,
                             LL_DCACHE_SR_BUSYF | LL_DCACHE_SR_BUSYCMDF) != 0U)
  {
    return HAL_BUSY;
  }

  hdcache->global_state = HAL_DCACHE_STATE_MAINTENANCE;

  DCACHE_CommandByAddr(hdcache, LL_DCACHE_COMMAND_CLEAN_BY_ADDR, addr, size_byte);

  /* Enable end of DCACHE maintenance operation by address interrupt line */
  LL_DCACHE_EnableIT_CMDEND(p_dcachex);

  /* Launch cache command */
  LL_DCACHE_StartCommand(p_dcachex);

  return HAL_OK;
}

/**
  * @brief  Clean and Invalidate the Data cache by Address.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @param  addr Start address of the region to be Cleaned and Invalidated
  * @param  size_byte Size of the region to be Cleaned and Invalidated (in bytes)
  * @note   This function waits for end of DCACHE Clean and Invalidation.
  * @note   The Address must be aligned on 16 bytes and
  *         the Size must be a multiple of 16 or 32 bytes, it depends on U5 series (check the reference manual).
  * @retval HAL_ERROR         Operation error.
  * @retval HAL_BUSY          DCACHE driver busy with another ongoing operation.
  * @retval HAL_OK            DCACHE Clean and Invalidate by Address operation ended successfully.
  */
hal_status_t HAL_DCACHE_CleanInvalidByAddr(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte)
{
  DCACHE_TypeDef *p_dcachex;
  hal_status_t status = HAL_OK;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the parameters */
  ASSERT_DBG_PARAM(IS_DCACHE_SIZE(size_byte));
  ASSERT_DBG_PARAM(IS_DCACHE_ADDRESS(addr));

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, HAL_DCACHE_STATE_ACTIVE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
  hdcache->last_error_codes = HAL_DCACHE_ERROR_NONE;
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

  /* Check no ongoing operation */
  if (LL_DCACHE_IsActiveFlag(p_dcachex,
                             LL_DCACHE_SR_BUSYF | LL_DCACHE_SR_BUSYCMDF) != 0U)
  {
    status = HAL_BUSY;
  }
  else
  {
    hdcache->global_state = HAL_DCACHE_STATE_MAINTENANCE;

    DCACHE_CommandByAddr(hdcache, LL_DCACHE_COMMAND_CLEAN_INVALIDATE_BY_ADDR, addr, size_byte);

    /* Launch DCACHE command */
    LL_DCACHE_StartCommand(p_dcachex);

    if (HAL_OK != DCACHE_WaitOnFlagUntilTimeout(hdcache, LL_DCACHE_SR_CMDENDF))
    {
      status = HAL_ERROR;
    }

    hdcache->global_state = HAL_DCACHE_STATE_ACTIVE;
  }
#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
  {
    uint32_t error_flags = LL_DCACHE_IsActiveFlag(p_dcachex, LL_DCACHE_SR_ERRF);
    if (error_flags != 0U)
    {
      hdcache->last_error_codes = HAL_DCACHE_ERROR_EVICTION_CLEAN;
      status = HAL_ERROR;
    }
  }
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */
  return status;
}

/**
  * @brief  Clean and Invalidate the Data cache by Address with interrupt.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @param  addr Start address of the region to be Cleaned and Invalidated
  * @param  size_byte Size of the region to be Cleaned and Invalidated
  * @note   This function launches maintenance operation and returns immediately.
  *         User must rely on the corresponding callback.
  * @note   The Address must be aligned on 16 bytes and
  *         the Size must be a multiple of 16 or 32 bytes, it depends on U5 series (check the reference manual).
  * @retval HAL_BUSY          DCACHE driver busy with another ongoing operation.
  * @retval HAL_OK            DCACHE Clean and Invalidate by Address operation started successfully.
  */
hal_status_t HAL_DCACHE_CleanInvalidByAddr_IT(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte)
{
  DCACHE_TypeDef *p_dcachex;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the parameters */
  ASSERT_DBG_PARAM(IS_DCACHE_SIZE(size_byte));
  ASSERT_DBG_PARAM(IS_DCACHE_ADDRESS(addr));

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, HAL_DCACHE_STATE_ACTIVE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
  hdcache->last_error_codes = HAL_DCACHE_ERROR_NONE;
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

  /* Check no ongoing operation */
  if (LL_DCACHE_IsActiveFlag(p_dcachex,
                             LL_DCACHE_SR_BUSYF | LL_DCACHE_SR_BUSYCMDF) != 0U)
  {
    return HAL_BUSY;
  }

  hdcache->global_state = HAL_DCACHE_STATE_MAINTENANCE;

  DCACHE_CommandByAddr(hdcache, LL_DCACHE_COMMAND_CLEAN_INVALIDATE_BY_ADDR, addr, size_byte);

  /* Enable end of DCACHE maintenance operation by address interrupt line */
  LL_DCACHE_EnableIT_CMDEND(p_dcachex);

  /* Launch cache command */
  LL_DCACHE_StartCommand(p_dcachex);

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup DCACHE_Exported_Functions_Group7
  * @{
  * The functions are :
  *  - HAL_DCACHE_IRQHandler() to manage the two types of interrupt : Error or Invalidate.
  *  - HAL_DCACHE_ErrorCallback() : Error Callback.
  *  - HAL_DCACHE_InvalidateCompleteCallback() : Maintenance Callback.
  *  - HAL_DCACHE_InvalidateByAddrCallback() : Invalidate by Address Callback.
  *  - HAL_DCACHE_CleanByAddrCallback() : Clean by Address Callback.
  *  - HAL_DCACHE_CleanInvalidByAddrCallback() : Clean Invalidate by Address Callback.
  *  - HAL_DCACHE_RegisterErrorCallback() to initialize the Error callback pointer.
  *  - HAL_DCACHE_RegisterInvalidateCompleteCallback() to initialize the Invalidate callback pointer.
  *  - HAL_DCACHE_RegisterInvalidateByAddrCallback() to initialize the Invalidate by Address callback pointer.
  *  - HAL_DCACHE_RegisterCleanByAddrCallback() to initialize the Clean by Address callback pointer.
  *  - HAL_DCACHE_RegisterCleanInvalidByAddrCallback() to initialize the Clean Invalidate by Address callback pointer.
  * @note The register user callback functions can be used only if USE_HAL_DCACHE_REGISTER_CALLBACKS = 1
  */

/**
  * @brief Handle the Data Cache interrupt request.
  * @param hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @note  This function must be called from DCACHE_IRQHandler().
  * @note  This function disables the interrupt related to a detected operation flag.
  */
void HAL_DCACHE_IRQHandler(hal_dcache_handle_t *hdcache)
{
  DCACHE_TypeDef *p_dcachex;
  uint32_t it_flags_sources;
  uint32_t command;

  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, (uint32_t)HAL_DCACHE_STATE_ACTIVE | (uint32_t)HAL_DCACHE_STATE_MAINTENANCE);

  p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  /* Get current interrupt flags and interrupt sources value */
  it_flags_sources = LL_DCACHE_READ_REG(p_dcachex, SR);
  it_flags_sources &= LL_DCACHE_READ_REG(p_dcachex, IER);

  /* Local variable to read the DCACHE command */
  command = LL_DCACHE_GetCommand(p_dcachex);

  /* Check Data cache Error interrupt flag */
  if ((it_flags_sources & LL_DCACHE_SR_ERRF) != 0U)
  {
#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
    hdcache->last_error_codes = HAL_DCACHE_ERROR_EVICTION_CLEAN;
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

    /* Clear DCACHE error pending flag */
    LL_DCACHE_ClearFlag_ERR(p_dcachex);

    /* Call the Error callback */
#if defined(USE_HAL_DCACHE_REGISTER_CALLBACKS) && (USE_HAL_DCACHE_REGISTER_CALLBACKS == 1)
    hdcache->p_error_cb(hdcache);
#else
    HAL_DCACHE_ErrorCallback(hdcache);
#endif /* USE_HAL_DCACHE_REGISTER_CALLBACKS */
  }

  if ((it_flags_sources & LL_DCACHE_SR_BSYENDF) != 0U)
  {
    /* Disable end of DCACHE invalidation interrupt line */
    LL_DCACHE_DisableIT_BSYEND(p_dcachex);

    /* Clear end of DCACHE invalidation interrupt flag */
    LL_DCACHE_ClearFlag_BSYEND(p_dcachex);

    hdcache->global_state = HAL_DCACHE_STATE_ACTIVE;

    /* Call the invalidate complete callback */
#if defined(USE_HAL_DCACHE_REGISTER_CALLBACKS) && (USE_HAL_DCACHE_REGISTER_CALLBACKS == 1)
    hdcache->p_invalidate_cplt_cb(hdcache);
#else
    HAL_DCACHE_InvalidateCompleteCallback(hdcache);
#endif /* USE_HAL_DCACHE_REGISTER_CALLBACKS */
  }
  if ((it_flags_sources & LL_DCACHE_SR_CMDENDF) != 0U)
  {
    /* Disable end of DCACHE maintenance operation by address interrupt line */
    LL_DCACHE_DisableIT_CMDEND(p_dcachex);

    /* Clear end of DCACHE maintenance operation by address interrupt flag */
    LL_DCACHE_ClearFlag_CMDEND(p_dcachex);

    hdcache->global_state = HAL_DCACHE_STATE_ACTIVE;

    if (command == LL_DCACHE_COMMAND_CLEAN_INVALIDATE_BY_ADDR)
    {
      /* Call the callback corresponding to DCACHE clean and invalidate by address operation */
#if defined(USE_HAL_DCACHE_REGISTER_CALLBACKS) && (USE_HAL_DCACHE_REGISTER_CALLBACKS == 1)
      hdcache->p_clean_invalid_by_addr_cb(hdcache);
#else
      HAL_DCACHE_CleanInvalidByAddrCallback(hdcache);
#endif /* USE_HAL_DCACHE_REGISTER_CALLBACKS */
    }
    else if (command == LL_DCACHE_COMMAND_CLEAN_BY_ADDR)
    {
      /* Call the callback corresponding to DCACHE clean by address operation */
#if defined(USE_HAL_DCACHE_REGISTER_CALLBACKS) && (USE_HAL_DCACHE_REGISTER_CALLBACKS == 1)
      hdcache->p_clean_by_addr_cb(hdcache);
#else
      HAL_DCACHE_CleanByAddrCallback(hdcache);
#endif /* USE_HAL_DCACHE_REGISTER_CALLBACKS */
    }
    else /* (command == LL_DCACHE_COMMAND_INVALIDATE_BY_ADDR) */
    {
      /* Call the callback corresponding to DCACHE invalidate by address operation */
#if defined(USE_HAL_DCACHE_REGISTER_CALLBACKS) && (USE_HAL_DCACHE_REGISTER_CALLBACKS == 1)
      hdcache->p_invalidate_by_addr_cb(hdcache);
#else
      HAL_DCACHE_InvalidateByAddrCallback(hdcache);
#endif /* USE_HAL_DCACHE_REGISTER_CALLBACKS */
    }
  }
}

/**
  * @brief  DCACHE Error callback.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  */
__WEAK void HAL_DCACHE_ErrorCallback(hal_dcache_handle_t *hdcache)
{
  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdcache);

  /* NOTE : This function must not be modified in this file, when the callback is needed,
            the HAL_DCACHE_ErrorCallback() must preferably be implemented in the user file
   */
}

/**
  * @brief  DCACHE Invalidation complete callback.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  */
__WEAK void HAL_DCACHE_InvalidateCompleteCallback(hal_dcache_handle_t *hdcache)
{
  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdcache);

  /* NOTE : This function must not be modified in this file, when the callback is needed,
            the HAL_DCACHE_InvalidateCompleteCallback() must preferably be implemented in the user file
   */
}

/**
  * @brief  Cache clean command by address callback.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  */
__WEAK void HAL_DCACHE_CleanByAddrCallback(hal_dcache_handle_t *hdcache)
{
  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdcache);

  /* NOTE : This function must not be modified in this file, when the callback is needed,
            the HAL_DCACHE_CleanByAddrCallback() must preferably be implemented in the user file
   */
}

/**
  * @brief  Cache Invalidate command by address callback.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  */
__WEAK void HAL_DCACHE_InvalidateByAddrCallback(hal_dcache_handle_t *hdcache)
{
  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdcache);

  /* NOTE : This function must not be modified in this file, when the callback is needed,
            the HAL_DCACHE_InvalidateByAddrCallback() must preferably be implemented in the user file
   */
}

/**
  * @brief  Cache clean and Invalidate command  by address callback.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  */
__WEAK void HAL_DCACHE_CleanInvalidByAddrCallback(hal_dcache_handle_t *hdcache)
{
  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdcache);

  /* NOTE : This function must not be modified in this file, when the callback is needed,
            the HAL_DCACHE_CleanInvalidByAddrCallback() must preferably be implemented in the user file
   */
}
#if defined(USE_HAL_DCACHE_REGISTER_CALLBACKS) && (USE_HAL_DCACHE_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User DCACHE callback for error.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @param  p_callback Pointer to the hal_dcache_error_cb_t Error Callback function.
  * @note   The function is only available if USE_HAL_DCACHE_REGISTER_CALLBACKS = 1.
  * @retval HAL_OK Callback registered successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_DCACHE_RegisterErrorCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hdcache != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, HAL_DCACHE_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdcache->p_error_cb = p_callback;
  return HAL_OK;
}

/**
  * @brief Register a User DCACHE callback for Invalidate.
  * @param hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                the handle information for the specified DCACHE instance.
  * @param p_callback Pointer to the hal_dcache_cb_t Callback function.
  * @note   The function is only available if USE_HAL_DCACHE_REGISTER_CALLBACKS = 1.
  * @retval HAL_OK Callback registered successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_DCACHE_RegisterInvalidateCompleteCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hdcache != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, (uint32_t)HAL_DCACHE_STATE_IDLE | (uint32_t)HAL_DCACHE_STATE_ACTIVE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdcache->p_invalidate_cplt_cb = p_callback;
  return HAL_OK;
}

/**
  * @brief Register a User DCACHE callback for CleanByAddr.
  * @param hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                the handle information for the specified DCACHE instance.
  * @param p_callback Pointer to the hal_dcache_cb_t Callback function.
  * @note   The function is only available if USE_HAL_DCACHE_REGISTER_CALLBACKS = 1.
  * @retval HAL_OK Callback registered successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_DCACHE_RegisterCleanByAddrCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hdcache != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, (uint32_t)HAL_DCACHE_STATE_IDLE | (uint32_t)HAL_DCACHE_STATE_ACTIVE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdcache->p_clean_by_addr_cb = p_callback;
  return HAL_OK;
}

/**
  * @brief Register a User DCACHE callback for InvalidateByAddr.
  * @param hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                the handle information for the specified DCACHE instance.
  * @param p_callback Pointer to the hal_dcache_cb_t Callback function.
  * @note   The function is only available if USE_HAL_DCACHE_REGISTER_CALLBACKS = 1.
  * @retval HAL_OK Callback registered successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_DCACHE_RegisterInvalidateByAddrCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hdcache != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, (uint32_t)HAL_DCACHE_STATE_IDLE | (uint32_t)HAL_DCACHE_STATE_ACTIVE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdcache->p_invalidate_by_addr_cb = p_callback;
  return HAL_OK;
}

/**
  * @brief Register a User DCACHE callback for CleanInvalidByAddr.
  * @param hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                the handle information for the specified DCACHE instance.
  * @param p_callback Pointer to the hal_dcache_cb_t Callback function.
  * @note   The function is only available if USE_HAL_DCACHE_REGISTER_CALLBACKS = 1.
  * @retval HAL_OK Callback registered successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_DCACHE_RegisterCleanInvalidByAddrCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hdcache != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hdcache->global_state, (uint32_t)HAL_DCACHE_STATE_IDLE | (uint32_t)HAL_DCACHE_STATE_ACTIVE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdcache->p_clean_invalid_by_addr_cb = p_callback;
  return HAL_OK;
}
#endif /* USE_HAL_DCACHE_REGISTER_CALLBACKS */
/**
  * @}
  */


/** @addtogroup DCACHE_Exported_Functions_Group8
  * @{
  * The function is :
  * - HAL_DCACHE_GetState() to retrieve the state value.
  */

/**
  * @brief  Get the DCACHE handle state.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @retval HAL_DCACHE_STATE_RESET DCACHE driver not initialized and not started.
  * @retval HAL_DCACHE_STATE_IDLE DCACHE driver initialized and not started.
  * @retval HAL_DCACHE_STATE_ACTIVE DCACHE driver initialized and started.
  * @retval HAL_DCACHE_STATE_MAINTENANCE DCACHE driver initialized, started and a maintenance operation is ongoing.
  */
hal_dcache_state_t HAL_DCACHE_GetState(const hal_dcache_handle_t *hdcache)
{
  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  return hdcache->global_state;
}

/**
  * @}
  */

#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
/** @addtogroup DCACHE_Exported_Functions_Group9
  * @{
This section permits to get in runtime the last error codes of the peripheral DCACHE.
- HAL_DCACHE_GetLastErrorCodes() to get the DCACHE last error codes.
  */
/**
  * @brief  Get the DCACHE last error codes.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the handle information for the specified DCACHE instance.
  * @retval HAL_DCACHE_ERROR_NONE No error.
  * @retval HAL_DCACHE_ERROR_EVICTION_CLEAN Error due to line eviction or clean operation.
  */
uint32_t HAL_DCACHE_GetLastErrorCodes(const hal_dcache_handle_t *hdcache)
{
  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Return the DCACHE last error codes */
  return hdcache->last_error_codes;
}

/**
  * @}
  */
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

#if defined(USE_HAL_DCACHE_USER_DATA) && (USE_HAL_DCACHE_USER_DATA == 1)
/** @addtogroup DCACHE_Exported_Functions_Group10
  * @{
  * This section provides functions allowing to Set and Get user data:
  * - HAL_DCACHE_SetUserData() to store the user data into the DCACHE handle.
  * - HAL_DCACHE_GetUserData() retrieve the user data from the DCACHE handle.
  */
/**
  * @brief Store the user data into the DCACHE handle.
  * @param hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                the handle information for the specified DCACHE instance.
  * @param p_user_data Pointer to the user data.
  */
void HAL_DCACHE_SetUserData(hal_dcache_handle_t *hdcache, const void *p_user_data)
{
  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  /* Set user data */
  hdcache->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the user data from the DCACHE handle.
  * @param hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                the handle information for the specified DCACHE instance.
  * @retval Pointer to the user data.
  */
const void *HAL_DCACHE_GetUserData(const hal_dcache_handle_t *hdcache)
{
  /* Check the DCACHE handle allocation */
  ASSERT_DBG_PARAM(hdcache != NULL);

  return (hdcache->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_DCACHE_USER_DATA */
/**
  * @}
  */

/** @addtogroup DCACHE_Private_Functions
  * @{
  */

/**
  * @brief  This static function allows to set a command to clean or invalidate (or both)
  *         a partition from DCACHE memory.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the configuration information for the specified DCACHE peripheral.
  * @param  command Command to be applied for the DCACHE
  *            @arg LL_DCACHE_COMMAND_INVALIDATE_BY_ADDR
  *            @arg LL_DCACHE_COMMAND_CLEAN_BY_ADDR
  *            @arg LL_DCACHE_COMMAND_CLEAN_INVALIDATE_BY_ADDR
  * @param  addr Start address of region to be Cleaned, Invalidated or Cleaned and Invalidated.
  * @param  size_byte Size of the region to be Cleaned, Invalidated or Cleaned and Invalidated (in bytes).
  */
static void DCACHE_CommandByAddr(hal_dcache_handle_t *hdcache, uint32_t command, uint32_t addr, uint32_t size_byte)
{
  DCACHE_TypeDef *p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);

  /* Make sure flags are reset */
  LL_DCACHE_ClearFlag(p_dcachex, LL_DCACHE_FCR_CBSYENDF | LL_DCACHE_FCR_CCMDENDF);

  /* Fill area start address */
  LL_DCACHE_SetStartAddress(p_dcachex, addr);

  /* Fill area end address */
  LL_DCACHE_SetEndAddress(p_dcachex, (addr + size_byte - 1U));

  /* Set command */
  LL_DCACHE_SetCommand(p_dcachex, command);
}

/**
  * @brief  This static function manages the end of maintenance operations
  *         with the DCACHE_COMMAND_TIMEOUT_VALUE.
  * @param  hdcache Pointer to a hal_dcache_handle_t structure that contains
  *                 the configuration information for the specified DCACHE peripheral.
  * @param  flag DCACHE flag to check
  *            @arg LL_DCACHE_SR_BSYENDF
  *            @arg LL_DCACHE_SR_CMDENDF
  * @retval HAL_ERROR         Operation failed.
  * @retval HAL_OK            Operation success.
  */
static hal_status_t DCACHE_WaitOnFlagUntilTimeout(hal_dcache_handle_t *hdcache, uint32_t flag)
{
  uint32_t tickstart;
  DCACHE_TypeDef *p_dcachex = (DCACHE_TypeDef *)((uint32_t)hdcache->instance);
  hal_status_t status = HAL_OK;

  /* Get timeout */
  tickstart = HAL_GetTick();

  /* Wait for end of DCACHE command */
  while (LL_DCACHE_IsActiveFlag(p_dcachex, flag) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > DCACHE_COMMAND_TIMEOUT_VALUE)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (LL_DCACHE_IsActiveFlag(p_dcachex, flag) == 0U)
      {
        status = HAL_ERROR;
        break;
      }
    }
  }
  return status;
}

/**
  * @}
  */

#endif /* USE_HAL_DCACHE_MODULE */
#endif /* DCACHE1 || DCACHE2 */

/**
  * @}
  */

/**
  * @}
  */
