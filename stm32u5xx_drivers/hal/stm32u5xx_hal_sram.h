/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_sram.h
  * @brief   Header file of SRAM HAL module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_HAL_SRAM_H
#define STM32U5XX_HAL_SRAM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_fmc_core.h"

#if defined (FMC_NORSRAM_BK1)

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup SRAM SRAM
  * @{
  */

/* Exported typedef --------------------------------------------------------------------------------------------------*/
/** @defgroup SRAM_Exported_Types SRAM Exported Types
  * @{
  */
/**
  * @brief SRAM Instance Enumeration Definition
  */
typedef enum
{
  HAL_SRAM1 = (uint32_t)FMC_NORSRAM1_SUBBANK1, /*!< SRAM1 bank1 */
  HAL_SRAM2 = (uint32_t)FMC_NORSRAM1_SUBBANK2, /*!< SRAM2 bank1 */
  HAL_SRAM3 = (uint32_t)FMC_NORSRAM1_SUBBANK3, /*!< SRAM3 bank1 */
  HAL_SRAM4 = (uint32_t)FMC_NORSRAM1_SUBBANK4  /*!< SRAM4 bank1 */
} hal_sram_t;

/**
  * @brief SRAM State Enumeration Definition
  */
typedef enum
{
  HAL_SRAM_STATE_RESET             = (0UL),        /*!< SRAM not yet initialized                                      */
  HAL_SRAM_STATE_INIT              = (1UL << 31U), /*!< SRAM initialized but not yet configured                       */
  HAL_SRAM_STATE_CONFIGURED        = (1UL << 30U), /*!< SRAM initialized, FMC peripheral configured but not yet ready
                                                        to use                                                        */
  HAL_SRAM_STATE_MEMORY_CONFIGURED = (1UL << 29U), /*!< SRAM initialized, FMC, memory configured but not yet
                                                        ready to use                                                  */
  HAL_SRAM_STATE_IDLE              = (1UL << 28U)  /*!< SRAM initialized, FMC, memory configured, SRAM is enabled and
                                                        ready to use                                                  */
} hal_sram_state_t;

/**
  * @brief SRAM Write Protection Status Enumeration Definition
  */
typedef enum
{
  HAL_SRAM_WR_NOT_PROTECTED = 0x00U, /*!< SRAM write access is not protected */
  HAL_SRAM_WR_PROTECTED     = 0x01U  /*!< SRAM write access is protected     */
} hal_sram_wr_protection_status_t;

/**
  * @brief SRAM Status Enumeration Definition
  */
typedef enum
{
  HAL_SRAM_DISABLED = 0x00U, /*!< SRAM is disabled */
  HAL_SRAM_ENABLED  = 0x01U  /*!< SRAM is enabled  */
} hal_sram_status_t;

/**
  * @brief SRAM Memory Type Enumeration Definition
  */
typedef enum
{
  HAL_SRAM_MEMORY_TYPE_SRAM  = FMC_MEMORY_TYPE_SRAM, /*!< SRAM memory type  */
  HAL_SRAM_MEMORY_TYPE_PSRAM = FMC_MEMORY_TYPE_PSRAM /*!< PSRAM memory type */
} hal_sram_memory_type_t;

/**
  * @brief SRAM Data Address Bus Multiplexing Enumeration Definition
  */
typedef enum
{
  HAL_SRAM_MUX_DATA_ADDR_DISABLE = FMC_MUX_DATA_ADDR_DISABLE, /*!< SRAM data/address non multiplexed */
  HAL_SRAM_MUX_DATA_ADDR_ENABLE  = FMC_MUX_DATA_ADDR_ENABLE   /*!< SRAM data/address multiplexed     */
} hal_sram_mux_mode_t;

/**
  * @brief SRAM Data Width Enumeration Definition
  */
typedef enum
{
  HAL_SRAM_MEMORY_BUS_WIDTH_8_BIT  = FMC_MEM_BUS_WIDTH_8_BIT, /*!< SRAM bus width 8 bits  */
  HAL_SRAM_MEMORY_BUS_WIDTH_16_BIT = FMC_MEM_BUS_WIDTH_16_BIT /*!< SRAM bus width 16 bits */
} hal_sram_data_width_t;

/**
  * @brief SRAM Write FIFO Enumeration Definition
  */
typedef enum
{
  HAL_SRAM_WRITE_FIFO_DISABLE = FMC_WRITE_FIFO_DISABLE, /*!< SRAM write FIFO disable */
  HAL_SRAM_WRITE_FIFO_ENABLE  = FMC_WRITE_FIFO_ENABLE   /*!< SRAM write FIFO enable  */
} hal_sram_write_fifo_t;

/**
  * @brief SRAM Byte Lane(NBL) Setup Enumeration Definition
  */
typedef enum
{
  HAL_SRAM_BYTE_LANE_SRC_CLK_0_CYCLE = FMC_BYTE_LANE_SOURCE_CLOCK_0_CYCLE, /*!< SRAM byte lane 0 clock source cycle  */
  HAL_SRAM_BYTE_LANE_SRC_CLK_1_CYCLE = FMC_BYTE_LANE_SOURCE_CLOCK_1_CYCLE, /*!< SRAM byte lane 1 clock source cycle  */
  HAL_SRAM_BYTE_LANE_SRC_CLK_2_CYCLE = FMC_BYTE_LANE_SOURCE_CLOCK_2_CYCLE, /*!< SRAM byte lane 2 clock source cycles */
  HAL_SRAM_BYTE_LANE_SRC_CLK_3_CYCLE = FMC_BYTE_LANE_SOURCE_CLOCK_3_CYCLE  /*!< SRAM byte lane 3 clock source cycles */
} hal_sram_byte_lane_source_clock_cycle_t;

/**
  * @brief SRAM Wait Signal Polarity Enumeration Definition
  */
typedef enum
{
  HAL_SRAM_WAIT_SIGNAL_POLARITY_LOW  = FMC_WAIT_SIGNAL_POLARITY_LOW, /*!< SRAM wait signal polarity low  */
  HAL_SRAM_WAIT_SIGNAL_POLARITY_HIGH = FMC_WAIT_SIGNAL_POLARITY_HIGH /*!< SRAM wait signal polarity high */
} hal_sram_wait_signal_polarity_t;

/**
  * @brief SRAM Synchronous Wait Signal State Enumeration Definition
  */
typedef enum
{
  HAL_SRAM_SYNC_WAIT_SIGNAL_DISABLE = FMC_SYNC_WAIT_SIGNAL_DISABLE, /*!< SRAM synchronous wait signal disable */
  HAL_SRAM_SYNC_WAIT_SIGNAL_ENABLE  = FMC_SYNC_WAIT_SIGNAL_ENABLE   /*!< SRAM synchronous wait signal enable  */
} hal_sram_sync_wait_signal_state_t;

/**
  * @brief SRAM Asynchronous Wait Signal State Enumeration Definition
  */
typedef enum
{
  HAL_SRAM_ASYNC_WAIT_SIGNAL_DISABLE = FMC_ASYNC_WAIT_SIGNAL_DISABLE, /*!< SRAM asynchronous wait signal disable */
  HAL_SRAM_ASYNC_WAIT_SIGNAL_ENABLE  = FMC_ASYNC_WAIT_SIGNAL_ENABLE   /*!< SRAM asynchronous wait signal enable  */
} hal_sram_async_wait_signal_state_t;

/**
  * @brief SRAM Continuous Clock Enumeration Definition
  */
typedef enum
{
  HAL_SRAM_CONTINUOUS_CLOCK_SYNC_ONLY  = FMC_CONTINUOUS_CLOCK_SYNC_ONLY, /*!< SRAM clock only in synchronous access */
  HAL_SRAM_CONTINUOUS_CLOCK_SYNC_ASYNC = FMC_CONTINUOUS_CLOCK_SYNC_ASYNC /*!< SRAM clock in asynchronous and synchronous
                                                                              access                                */
} hal_sram_continuous_clock_t;

/**
  * @brief CRAM Page Size Enumeration Definition
  */
typedef enum
{
  HAL_SRAM_PAGE_SIZE_NONE      = FMC_PAGE_SIZE_NONE,     /*!< No burst split when crossing page boundary */
  HAL_SRAM_PAGE_SIZE_128_BYTE  = FMC_PAGE_SIZE_128_BYTE, /*!< CRAM page size 128  bytes                  */
  HAL_SRAM_PAGE_SIZE_256_BYTE  = FMC_PAGE_SIZE_256_BYTE, /*!< CRAM page size 256  bytes                  */
  HAL_SRAM_PAGE_SIZE_512_BYTE  = FMC_PAGE_SIZE_512_BYTE, /*!< CRAM page size 512 bytes                   */
  HAL_SRAM_PAGE_SIZE_1024_BYTE = FMC_PAGE_SIZE_1024_BYTE /*!< CRAM page size 1024 bytes                  */
} hal_sram_cram_page_size_t;

/**
  * @brief SRAM Access Mode Enumeration Definition
  */
typedef enum
{
  HAL_SRAM_ACCESS_MODE_A = FMC_ACCESS_MODE_A, /*!< SRAM access mode A */
  HAL_SRAM_ACCESS_MODE_D = FMC_ACCESS_MODE_D  /*!< SRAM access mode D */
} hal_sram_access_mode_t;

/**
  * @brief SRAM Configuration Parameters Structure Definition
  */
typedef struct
{
  hal_sram_memory_type_t          memory_type;          /*!< Specify the type of external memory attached to
                                                             the corresponding memory bank */

  hal_sram_write_fifo_t           write_fifo;           /*!< Enable or disable the write FIFO used by the FMC
                                                             controller                    */

  hal_sram_wait_signal_polarity_t wait_signal_polarity; /*!< Specify the wait signal polarity, when asserting the wait
                                                             state management              */
} hal_sram_config_t;

/**
  * @brief SRAM Memory Configuration Parameters Structure Definition
  */
typedef struct
{
  hal_sram_data_width_t                   data_width;                  /*!< Specify the external memory device width
                                                                            in bits                            */

  hal_sram_cram_page_size_t               cram_page_size_byte;         /*!< Specify the CRAM memory page size in byte
                                                                            @note page size is selected only when using
                                                                            a CRAM memory, otherwise this parameter must
                                                                            be set to HAL_SRAM_PAGE_SIZE_NONE  */

  hal_sram_mux_mode_t                     mux_mode;                    /*!< Specify whether address and data values are
                                                                            multiplexed on the data bus or not */

  hal_sram_byte_lane_source_clock_cycle_t byte_lane_setup_cycle;       /*!< Specify the byte lane (NBL) setup timing in
                                                                            the source clock cycles            */

  uint32_t                                psram_chipsel_maxpulse_nsec; /*!< Specify the maximum chip select pulse time
                                                                            in nanoseconds for PSRAM refresh
                                                                            @note when this parameter has a value
                                                                            different from zero, the PSRAM device
                                                                            refresh is enabled separately in the
                                                                            corresponding SRAM sub-bank and the chip
                                                                            select pulse time value is common to all
                                                                            SRAM sub-banks
                                                                            when this parameter is 0, the PSRAM device
                                                                            refresh is disabled only in the
                                                                            corresponding SRAM sub-bank        */
} hal_sram_memory_config_t;

/**
  * @brief SRAM Timing Parameters Structure Definition
  */
typedef struct
{
  uint32_t addr_setup_nsec; /*!< Define the duration of the address setup timing in nanoseconds */

  uint32_t addr_hold_nsec;  /*!< Define the duration of the address hold timing in nanoseconds  */

  uint32_t data_setup_nsec; /*!< Define the duration of the data setup timing in nanoseconds    */

  uint32_t data_hold_nsec;  /*!< Define the duration of the data hold timing in nanoseconds     */
} hal_sram_timings_t;

/**
  * @brief SRAM Read Asynchronous And Write Asynchronous Structure Definition
  */
typedef struct
{
  hal_sram_async_wait_signal_state_t async_wait;           /*!< Enable or disable the asynchronous wait state     */

  hal_sram_timings_t                 async_access_timings; /*!< Define the timings for both read and write access
                                                                @note when separate timing configurations for read and
                                                                write transactions are needed, the
                                                                HAL_SRAM_SetWrAsyncTimings() API must be called to set
                                                                the write timing parameters. In this case, this field
                                                                defines timing only for read access               */

  uint32_t                           bus_turnaround_nsec;  /*!< Define the duration of the bus turnaround phase to
                                                                configure in nanoseconds for both read and write access
                                                                @note when separate timing configurations for read and
                                                                write transactions are needed, the
                                                                HAL_SRAM_SetWrAsyncTimings() API must be called to set
                                                                the write bus turnaround parameter. In this case, this
                                                                field defines bus turnaround only for read access */
} hal_sram_rd_wr_async_timings_t;

/**
  * @brief SRAM Synchronous Protocol Parameters Structure Definition
  */
typedef struct
{
  hal_sram_sync_wait_signal_state_t wait_signal_state; /*!< Enable or disable the synchronous wait state */

  hal_sram_continuous_clock_t       continuous_clock;  /*!< Enable or disable the FMC clock output to external memory
                                                            devices                                      */

  uint32_t                          clk_period_nsec;   /*!< Define the clock period of the output signal expressed in
                                                            nanoseconds
                                                            @note If the continuous clock bit is set, the synchronous
                                                            memories connected to other banks than SRAM bank 1 are
                                                            clocked by the same clock                    */
} hal_sram_sync_protocol_config_t;

/**
  * @brief SRAM Read Synchronous And Write Synchronous Structure Definition
  */
typedef struct
{
  hal_sram_sync_protocol_config_t sync_protocol;       /*!< Define the synchronous configuration for read and write
                                                            access         */

  uint32_t                        bus_turnaround_nsec; /*!< Define the duration of the bus turnaround phase to configure
                                                            in nanoseconds */
} hal_sram_rd_wr_sync_timings_t;

/**
  * @brief SRAM Read Asynchronous And Write Synchronous Or Read Synchronous And Write Asynchronous
  *        Structure Definition
  */
typedef struct
{
  hal_sram_sync_protocol_config_t    sync_protocol;        /*!< Define the configuration for the synchronous access  */

  hal_sram_async_wait_signal_state_t async_wait;           /*!< Enable or disable the asynchronous wait state access */

  hal_sram_timings_t                 async_access_timings; /*!< Define the timing for the asynchronous access        */

  uint32_t                           bus_turnaround_nsec;  /*!< Define the duration of the bus turnaround phase to
                                                                configure in nanoseconds                             */
} hal_sram_sync_async_timings_t;

/**
  * @brief SRAM Read and Write Asynchronous Memory Configuration Structure Definition
  */
typedef struct
{
  hal_sram_memory_config_t       memory;  /*!< Configure memory parameters                       */

  hal_sram_rd_wr_async_timings_t timings; /*!< Configure the read and write asynchronous timings */

} hal_sram_rd_wr_async_memory_config_t;

/**
  * @brief SRAM Timing Write Asynchronous Parameters Structure Definition
  */
typedef struct
{
  hal_sram_timings_t     async_access_timings; /*!< Define the timings for write access          */

  uint32_t               bus_turnaround_nsec;  /*!< Define the duration of the bus turnaround phase
                                                    to configure in nanoseconds for write access */

  hal_sram_access_mode_t write_access_mode;    /*!< Define the write access mode                 */

  hal_sram_access_mode_t read_access_mode;     /*!< Define the read access mode                  */

} hal_sram_wr_async_timings_t;

/**
  * @brief SRAM Read and Write Synchronous Memory Configuration Structure Definition
  */
typedef struct
{
  hal_sram_memory_config_t      memory;  /*!< Configure memory parameters                      */

  hal_sram_rd_wr_sync_timings_t timings; /*!< Configure the read and write synchronous timings */

} hal_sram_rd_wr_sync_memory_config_t;

/**
  * @brief SRAM Read Synchronous and Write Asynchronous / Read Asynchronous and Write Synchronous
  *        Memory Configuration Structure Definition
  */
typedef struct
{
  hal_sram_memory_config_t      memory;  /*!< Configure memory parameters                        */

  hal_sram_sync_async_timings_t timings; /*!< Configure the synchronous and asynchronous timings */

} hal_sram_rd_sync_wr_async_memory_config_t, hal_sram_rd_async_wr_sync_memory_config_t;

/**
  * @brief SRAM Handle Structure Definition
  */
typedef struct
{
  hal_sram_t                               instance;             /*!< SRAM instance                */

  volatile hal_sram_state_t                global_state;         /*!< SRAM global state            */

  volatile hal_sram_wr_protection_status_t wr_protection_status; /*!< SRAM write protection status */

#if defined(USE_HAL_SRAM_USER_DATA) && (USE_HAL_SRAM_USER_DATA == 1)
  const void                               *p_user_data;         /*!< SRAM user data pointer       */
#endif /* USE_HAL_SRAM_USER_DATA */
} hal_sram_handle_t;
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup SRAM_Exported_Functions SRAM Exported Functions
  * @{
  */

/** @defgroup SRAM_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_SRAM_Init(hal_sram_handle_t *hsram, hal_sram_t instance);
void HAL_SRAM_DeInit(hal_sram_handle_t *hsram);
/**
  * @}
  */

/** @defgroup SRAM_Exported_Functions_Group2 Configuration functions
  * @{
  */
/* Configuration functions */
hal_status_t HAL_SRAM_SetConfig(hal_sram_handle_t *hsram, const hal_sram_config_t *p_config);
void HAL_SRAM_GetConfig(const hal_sram_handle_t *hsram, hal_sram_config_t *p_config);

/* Asynchronous memory configuration functions */
hal_status_t HAL_SRAM_SetConfigRdWrAsyncMemory(hal_sram_handle_t *hsram,
                                               const hal_sram_rd_wr_async_memory_config_t *p_config);
void HAL_SRAM_GetConfigRdWrAsyncMemory(const hal_sram_handle_t *hsram, hal_sram_rd_wr_async_memory_config_t *p_config);

/* Optional functions when different timings for write transactions is needed */
hal_status_t HAL_SRAM_SetWrAsyncTimings(hal_sram_handle_t *hsram, const hal_sram_wr_async_timings_t *p_timings);
void HAL_SRAM_GetWrAsyncTimings(const hal_sram_handle_t *hsram, hal_sram_wr_async_timings_t *p_timings);

/* Synchronous memory configuration functions */
hal_status_t HAL_SRAM_SetConfigRdWrSyncMemory(hal_sram_handle_t *hsram,
                                              const hal_sram_rd_wr_sync_memory_config_t *p_config);
void HAL_SRAM_GetConfigRdWrSyncMemory(const hal_sram_handle_t *hsram, hal_sram_rd_wr_sync_memory_config_t *p_config);

/* Synchronous/Asynchronous memory configuration functions */
hal_status_t HAL_SRAM_SetConfigRdSyncWrAsyncMemory(hal_sram_handle_t *hsram,
                                                   const hal_sram_rd_sync_wr_async_memory_config_t *p_config);
void HAL_SRAM_GetConfigRdSyncWrAsyncMemory(const hal_sram_handle_t *hsram,
                                           hal_sram_rd_sync_wr_async_memory_config_t *p_config);

hal_status_t HAL_SRAM_SetConfigRdAsyncWrSyncMemory(hal_sram_handle_t *hsram,
                                                   const hal_sram_rd_async_wr_sync_memory_config_t *p_config);
void HAL_SRAM_GetConfigRdAsyncWrSyncMemory(const hal_sram_handle_t *hsram,
                                           hal_sram_rd_async_wr_sync_memory_config_t *p_config);

/* Enable and disable memory functions */
hal_status_t HAL_SRAM_EnableMemory(hal_sram_handle_t *hsram);
hal_status_t HAL_SRAM_DisableMemory(hal_sram_handle_t *hsram);
/**
  * @}
  */

/** @defgroup SRAM_Exported_Functions_Group3 Control functions
  * @{
  */
hal_status_t HAL_SRAM_EnableWriteProtection(hal_sram_handle_t *hsram);
hal_status_t HAL_SRAM_DisableWriteProtection(hal_sram_handle_t *hsram);
hal_sram_wr_protection_status_t HAL_SRAM_IsEnabledWriteProtection(const hal_sram_handle_t *hsram);

hal_status_t HAL_SRAM_Enable(hal_sram_handle_t *hsram);
hal_status_t HAL_SRAM_Disable(hal_sram_handle_t *hsram);
hal_sram_status_t HAL_SRAM_IsEnabled(const hal_sram_handle_t *hsram);
/**
  * @}
  */

#if defined(USE_HAL_SRAM_USER_DATA) && (USE_HAL_SRAM_USER_DATA == 1)
/** @defgroup SRAM_Exported_Functions_Group4 User data functions
  * @{
  */
void HAL_SRAM_SetUserData(hal_sram_handle_t *hsram, const void *p_user_data);
const void *HAL_SRAM_GetUserData(const hal_sram_handle_t *hsram);
/**
  * @}
  */
#endif /* USE_HAL_SRAM_USER_DATA */

/** @defgroup SRAM_Exported_Functions_Group5 Peripheral state functions, Clock Frequency
  * @{
  */
uint32_t HAL_SRAM_GetClockFreq(const hal_sram_handle_t *hsram);
hal_sram_state_t HAL_SRAM_GetState(const hal_sram_handle_t *hsram);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(FMC_NORSRAM_BK1) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_HAL_SRAM_H */
