/**
  **********************************************************************************************************************
  * @file    stm32u5xx_fmc_core.h
  * @brief   Header file of FMC HAL module.
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
#ifndef STM32U5XX_FMC_CORE_H
#define STM32U5XX_FMC_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"

#if defined (FMC_NORSRAM_BK1)

/** @defgroup FMC_Core FMC Core
  * @{
  */

/** @defgroup FMC_Core_Private_Macros FMC Core Private Macros
  * @{
  */
#define IS_FMC_ADDR_SETUP_TIME(time) ((time) <= 15U)
#define IS_FMC_ADDR_HOLD_TIME(time) (((time) > 0U) && ((time) <= 15U))
#define IS_FMC_DATASETUP_TIME(time) (((time) > 0U) && ((time) <= 255U))
#define IS_FMC_DATAHOLD_DURATION_RW(datahold) ((datahold) <= 3U)
#define IS_FMC_DATAHOLD_DURATION_R(datahold) ((datahold) <= 3U)
#define IS_FMC_DATAHOLD_DURATION_W(datahold) (((datahold) > 0U) && ((datahold) <= 4U))
#define IS_FMC_TURNAROUND_TIME(time) (((time) > 0U) && ((time) <= 16U))
#define IS_FMC_CLK_DIV(div) (((div) > 0U) && ((div) <= 16U))
#define IS_FMC_DATA_LATENCY(latency) (((latency) > 1U) && ((latency) <= 17U))
#define FMC_READ_FIELD(value, msk, pos) (((uint32_t)(value) & msk) >> pos)
#define FMC_WRITE_FIELD(value, msk, pos) (((uint32_t)(value) << pos) & msk)
/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup FMC_Core_Exported_Types FMC Core Exported Types
  * @{
  */
typedef FMC_NORSRAM_SUBBANK_TypeDef fmc_norsram_subbank_t;
/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup FMC_Core_Exported_Constants FMC Core Exported Constants
  * @{
  */

/** @defgroup FMC_Core_NORSRAM_Controller FMC NORSRAM Controller
  * @{
  */

/** @defgroup FMC_Write_Timing FMC Write Timing
  * @{
  */
#define FMC_WR_TIMING_VALUE 0x0FFFFFFFU
/**
  * @}
  */

/** @defgroup FMC_Memory_Type FMC Memory Type
  * @{
  */
#define FMC_MEMORY_TYPE_SRAM  0x00000000U
#define FMC_MEMORY_TYPE_PSRAM FMC_BCRx_MTYP_0
#define FMC_MEMORY_TYPE_NOR   FMC_BCRx_MTYP_1
/**
  * @}
  */

/** @defgroup FMC_Data_Address_Bus_Multiplexing FMC Data Address Bus Multiplexing
  * @{
  */
#define FMC_MUX_DATA_ADDR_DISABLE 0x00000000U
#define FMC_MUX_DATA_ADDR_ENABLE  FMC_BCRx_MUXEN
/**
  * @}
  */

/** @defgroup FMC_Data_Width FMC Data Width
  * @{
  */
#define FMC_MEM_BUS_WIDTH_8_BIT  0x00000000U
#define FMC_MEM_BUS_WIDTH_16_BIT FMC_BCRx_MWID_0
/**
  * @}
  */

/** @defgroup FMC_Write_FIFO FMC Write FIFO
  * @{
  */
#define FMC_WRITE_FIFO_ENABLE  0x00000000U
#define FMC_WRITE_FIFO_DISABLE FMC_BCR1_WFDIS
/**
  * @}
  */

/** @defgroup FMC_Byte_Lane FMC Byte Lane(NBL) Setup
  * @{
  */
#define FMC_BYTE_LANE_SOURCE_CLOCK_0_CYCLE 0x00000000U
#define FMC_BYTE_LANE_SOURCE_CLOCK_1_CYCLE FMC_BCRx_NBLSET_0
#define FMC_BYTE_LANE_SOURCE_CLOCK_2_CYCLE FMC_BCRx_NBLSET_1
#define FMC_BYTE_LANE_SOURCE_CLOCK_3_CYCLE FMC_BCRx_NBLSET_2
/**
  * @}
  */

/** @defgroup FMC_Wait_Signal_Polarity FMC Wait Signal Polarity
  * @{
  */
#define FMC_WAIT_SIGNAL_POLARITY_LOW  0x00000000U
#define FMC_WAIT_SIGNAL_POLARITY_HIGH FMC_BCRx_WAITPOL
/**
  * @}
  */

/** @defgroup FMC_Wait_Timing_Configuration FMC Wait Timing Configuration
  * @{
  */
#define FMC_WAIT_TIMING_CONFIG_BEFORE_WAITSTAT 0x00000000U
#define FMC_WAIT_TIMING_CONFIG_DURING_WAITSTAT FMC_BCRx_WAITCFG
/**
  * @}
  */

/** @defgroup FMC_Synchonous_Wait_Signal_State FMC Synchronous Wait Signal State
  * @{
  */
#define FMC_SYNC_WAIT_SIGNAL_DISABLE 0x00000000U
#define FMC_SYNC_WAIT_SIGNAL_ENABLE  FMC_BCRx_WAITEN
/**
  * @}
  */

/** @defgroup FMC_Asynchronous_Wait_Signal_State FMC Asynchronous Wait Signal State
  * @{
  */
#define FMC_ASYNC_WAIT_SIGNAL_DISABLE 0x00000000U
#define FMC_ASYNC_WAIT_SIGNAL_ENABLE  FMC_BCRx_ASYNCWAIT
/**
  * @}
  */

/** @defgroup FMC_Continous_Clock FMC Continuous Clock
  * @{
  */
#define FMC_CONTINUOUS_CLOCK_SYNC_ONLY  0x00000000U
#define FMC_CONTINUOUS_CLOCK_SYNC_ASYNC FMC_BCR1_CCLKEN
/**
  * @}
  */

/** @defgroup FMC_Page_Size FMC Page Size
  * @{
  */
#define FMC_PAGE_SIZE_NONE      0x00000000U
#define FMC_PAGE_SIZE_128_BYTE  FMC_BCRx_CPSIZE_0
#define FMC_PAGE_SIZE_256_BYTE  FMC_BCRx_CPSIZE_1
#define FMC_PAGE_SIZE_512_BYTE  (FMC_BCRx_CPSIZE_0 | FMC_BCRx_CPSIZE_1)
#define FMC_PAGE_SIZE_1024_BYTE FMC_BCRx_CPSIZE_2
/**
  * @}
  */

/** @defgroup FMC_Access_Mode FMC Access Mode
  * @{
  */
#define FMC_ACCESS_MODE_A 0x00000000U
#define FMC_ACCESS_MODE_B FMC_BTRx_ACCMOD_0
#define FMC_ACCESS_MODE_C FMC_BTRx_ACCMOD_1
#define FMC_ACCESS_MODE_D FMC_BTRx_ACCMOD_2
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/* Expoted macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup FMC_Core_Exported_Macros FMC Core Exported Macros
  * @{
This subsection provides a macro allowing to check the current NOR handle state and move it to a new state
in an atomic way.
  */
#if defined(USE_HAL_NOR_MODULE) && (USE_HAL_NOR_MODULE == 1U)
#if defined(USE_HAL_CHECK_PROCESS_STATE) && (USE_HAL_CHECK_PROCESS_STATE == 1U)
#define FMC_NOR_CHECK_UPDATE_STATE(handle, state_field, ppp_conditional_state, ppp_new_state, old_state)            \
  do {                                                                                                              \
    do {                                                                                                            \
      /* Return HAL_BUSY if the status is not ready */                                                              \
      if ((__LDREXW((volatile uint32_t *)((uint32_t)&(handle)->state_field)) &                                      \
           (uint32_t)(ppp_conditional_state)) == 0U)                                                                \
      {                                                                                                             \
        return HAL_BUSY;                                                                                            \
      }                                                                                                             \
      (old_state) = (handle)->state_field;                                                                          \
      /* if state is ready then attempt to change the state to the new one */                                       \
    } while (__STREXW((uint32_t)(ppp_new_state), (volatile uint32_t *)((uint32_t)&((handle)->state_field))) != 0U); \
    /* Do not start any other memory access until memory barrier is complete */                                     \
    __DMB();                                                                                                        \
  } while (0)
#else
#define FMC_NOR_CHECK_UPDATE_STATE(handle, state_field, ppp_conditional_state, ppp_new_state, old_state)            \
  do {                                                                                                              \
    (old_state)           = (handle)->state_field;                                                                  \
    (handle)->state_field = (ppp_new_state);                                                                        \
  } while(0)
#endif /* USE_HAL_CHECK_PROCESS_STATE == 1U */
#endif /* USE_HAL_NOR_MODULE */
/**
  * @}
  */

/* Private Functions -------------------------------------------------------------------------------------------------*/
/** @defgroup FMC_Core_Private_Functions FMC Core Private Functions
  * @{
This subsection provides a set of functions allowing to :
- Enable and disable the FMC.
- Enable and disable the NORSRAM device.
- Get the corresponding NORSRAM device status.
- Enable and disable the NORSRAM device write protection.
- Get the corresponding NORSRAM device write protection status.
  */

/**
  * @brief Enable the FMC peripheral.
  */
__STATIC_INLINE void FMC_Enable(void)
{
  SET_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_FMCEN);
}

/**
  * @brief Disable the FMC peripheral.
  */
__STATIC_INLINE void FMC_Disable(void)
{
  CLEAR_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_FMCEN);
}

/**
  * @brief Enable the NORSRAM device.
  * @param p_instance Pointer to the device instance.
  */
__STATIC_INLINE void FMC_NOR_SRAM_Enable(fmc_norsram_subbank_t *p_instance)
{
  SET_BIT(p_instance->BCR, FMC_BCRx_MBKEN);
}

/**
  * @brief Disable the NORSRAM device.
  * @param p_instance Pointer to the device instance.
  */
__STATIC_INLINE void FMC_NOR_SRAM_Disable(fmc_norsram_subbank_t *p_instance)
{
  CLEAR_BIT(p_instance->BCR, FMC_BCRx_MBKEN);
}

/**
  * @brief  Get the NORSRAM device status.
  * @param  p_instance Pointer to the device instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FMC_NOR_SRAM_IsEnabled(const fmc_norsram_subbank_t *p_instance)
{
  return (((READ_BIT(p_instance->BCR, FMC_BCRx_MBKEN) == FMC_BCRx_MBKEN) ? 1UL : 0UL));
}

/**
  * @brief Enable the NORSRAM device write protection.
  * @param p_instance Pointer to the device instance.
  */
__STATIC_INLINE void FMC_NOR_SRAM_EnableWriteProtection(fmc_norsram_subbank_t *p_instance)
{
  CLEAR_BIT(p_instance->BCR, FMC_BCRx_WREN_Msk);
}

/**
  * @brief Disable the NORSRAM device write protection.
  * @param p_instance Pointer to the device instance.
  */
__STATIC_INLINE void FMC_NOR_SRAM_DisableWriteProtection(fmc_norsram_subbank_t *p_instance)
{
  SET_BIT(p_instance->BCR, FMC_BCRx_WREN_Msk);
}

/**
  * @brief  Get the corresponding NORSRAM device write protection status.
  * @param  p_instance Pointer to the device instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FMC_NOR_SRAM_IsEnabled_Protection(const fmc_norsram_subbank_t *p_instance)
{
  return (((READ_BIT(p_instance->BCR, FMC_BCRx_WREN_Msk) == FMC_BCRx_WREN_Msk) ? 0UL : 1UL));
}

/**
  * @brief  Convert the timing parameters from source clock cycle number to nanoseconds.
  * @param  timing_cycle  The timing parameter in source clock cycle number.
  * @retval timing parameter in nanoseconds.
  */
__STATIC_INLINE uint32_t FMC_ConvertClockCycleToNanoseconds(uint32_t timing_cycle, uint32_t source_clk_freq_hz)
{
  return ((uint32_t)(((uint64_t)timing_cycle * (uint64_t)1000000000) / source_clk_freq_hz));
}

/**
  * @brief  Calculate the Nor device address.
  * @param  instance Pointer to the device instance.
  * @param  offset   NOR memory offset address
  * @retval NOR address value.
  */
__STATIC_INLINE uint32_t FMC_NOR_CalculateMemoryAddress(uint32_t instance, uint16_t offset)
{
  return ((uint32_t)((((((uint32_t)instance - (uint32_t)FMC_NORSRAM1_SUBBANK1) / 8UL) * 0x04000000UL) + FMC_BASE) +
                     (2U * (uint32_t)(offset))));
}

/**
  * @brief Write the NOR memory data to specified address.
  * @param address NOR memory address.
  * @param data    Data to write.
  */
__STATIC_INLINE void FMC_NOR_Write(uint32_t address, uint16_t data)
{
  *(volatile uint16_t *)address = data;
  __DSB();
}

/**
  * @brief  Convert the voltage supply value from CFI format to millivolts.
  * @param  voltage_cfi_value The voltage value obtained from the device info in CFI format.
  * @retval The resulting voltage value in millivolts.
  */
__STATIC_INLINE uint32_t FMC_NOR_Convert_Voltage(uint16_t voltage_cfi_value)
{
  return ((uint32_t)(((voltage_cfi_value & 0x0FUL) * 100UL) + (((voltage_cfi_value & 0xF0UL) >> 4U) * 1000UL)));
}
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup FMC_Core_Exported_Functions FMC Core Exported Functions
  *  @{
  */

/** @defgroup FMC_CORE_NORSRAM_Exported_Functions NORSRAM configuration functions
  *  @{
  */
void FMC_NOR_SRAM_SetConfig(fmc_norsram_subbank_t *p_instance, uint32_t config);
void FMC_NOR_SRAM_GetConfig(const fmc_norsram_subbank_t *p_instance, uint32_t *p_config);
void FMC_NOR_SRAM_SetConfigMemory(fmc_norsram_subbank_t *p_instance, uint32_t control_cfg,
                                  uint32_t counter_cfg, uint32_t timing_cfg);
void FMC_NOR_SRAM_GetConfigMemory(const fmc_norsram_subbank_t *p_instance, uint32_t *p_control_cfg,
                                  uint32_t *p_counter_cfg, uint32_t *p_timing_cfg);
void FMC_NOR_SRAM_SetClock(uint32_t clock_cfg, uint32_t clock_div_cfg);
void FMC_NOR_SRAM_SetWrTiming(fmc_norsram_subbank_t *p_instance, uint32_t rd_access_mode, uint32_t wr_timing_cfg);
void FMC_NOR_SRAM_GetWrTiming(const fmc_norsram_subbank_t *p_instance, uint32_t *p_rd_access_mode,
                              uint32_t *p_wr_timing_cfg);
uint32_t FMC_ConvertNanosecondsToClockCycle(uint32_t timing_nsec, uint32_t source_clk_freq_hz);
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

#endif /* STM32U5XX_FMC_CORE_H */
