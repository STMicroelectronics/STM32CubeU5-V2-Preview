/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_xspi.c
  * @brief   XSPI HAL module driver.
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

/** @addtogroup XSPI
  * @{
An explanation on XSPI overall usage :
- XSPI is the abbreviation of Expanded Serial Peripheral Interface. It's an interface that supports most external serial
  memories such as serial PSRAMs, serial NAND and serial NOR flash memories, HyperRAM and HyperFlash memories, with
  different functional mode.

- The XSPI I/O manager is a low-level interface that enables an efficient XSPIM pin
  assignment with a full I/O matrix (before alternate function map) and multiplex of
  single/dual/quad/octal SPI interfaces over the same bus.

This file provides firmware functions to manage the following functionalities of XSPI peripheral:

- Initialization and De-initialization functions
- Configuration functions
- Command and IO operation functions
- IRQHandler, link DMA and Callbacks functions
- Status functions
- Delay Block functions
- High-speed interface and calibration functions
- Interrupt functions

# How to use the XSPI HAL module driver

## Initialization and de-initialization functions:

- Declare a hal_xspi_handle_t handle structure, for example: hal_xspi_handle_t hxspi
- Use HAL_XSPI_Init() function to initialize the XSPI handle and associate the physical instance
- Use HAL_XSPI_DeInit() function to abort any ongoing operation then reset the state

## Configuration functions

- Use HAL_XSPI_SetConfig() function to configure the Regular/Hyperbus parameters of the XSPI peripheral

- Use HAL_XSPI_GetConfig() function to retrieve the current configuration for the XSPI instance

- Use HAL_XSPI_XSPIM_SetConfig() function to configure the XSPIM IO manager parameters in hal_xspi_xspim_config_t
  structure.

- Use HAL_XSPI_XSPIM_GetConfig() function to retrieve the current XSPIM I/O Manager configuration

- Once a global configuration applied (using HAL_XSPI_SetConfig()), optionally use the following unitary functions to
  update individually the different parameters:

  - HAL_XSPI_SetFifoThreshold()          Allowing to configure the Fifo threshold according to the user parameters
  - HAL_XSPI_GetFifoThreshold()          Allowing to retrieve the Fifo threshold configuration
  - HAL_XSPI_SetPrescaler()              Allowing to configure the Prescaler according to the user parameters
  - HAL_XSPI_GetPrescaler()              Allowing to retrieve the Prescaler configuration
  - HAL_XSPI_SetMemorySize()             Allowing to configure the Size of XSPI memory according to the user parameters
  - HAL_XSPI_GetMemorySize()             Allowing to retrieve the Size of XSPI memory configuration
  - HAL_XSPI_SetMemoryType()             Allowing to configure the Type of XSPI memory according to the user parameters
  - HAL_XSPI_GetMemoryType()             Allowing to retrieve the Type of XSPI memory configuration
  - HAL_XSPI_EnableFreeRunningClock()    Allowing to enable the free running clock
  - HAL_XSPI_DisableFreeRunningClock()   Allowing to disable the free running clock
  - HAL_XSPI_IsEnabledFreeRunningClock() Allowing to check the state of free running clock, whether it is enable or not
  - HAL_XSPI_EnableSIOO()                Allowing to enable the Send Instruction Only Once mode
  - HAL_XSPI_DisableSIOO()               Allowing to disable the Send Instruction Only Once mode
  - HAL_XSPI_IsEnabledSIOO()             Allowing to check the state of Send Instruction Only Once mode

## Command and IO operation functions

- In Regular mode, use HAL_XSPI_SendRegularCmd()
  or
  HAL_XSPI_SendRegularCmd_IT() function to configure the command sequence

- In Hyperbus mode, use HAL_XSPI_SendHyperbusCmd() function to configure the command sequence

- If no data is required for the command (only for Regular Command mode, not for Hyperbus mode), it is sent directly to
  the memory :

  - In polling mode, function returns when the command is complete
  - In interrupt mode, the function starts the process and returns, the process continue in background
    (based on the various interrupts). The HAL_XSPI_CmdCpltCallback() is called when the process is complete

- For the indirect write mode, use HAL_XSPI_Transmit(), HAL_XSPI_Transmit_DMA(), HAL_XSPI_Transmit_DMA_Opt()
  or  HAL_XSPI_Transmit_IT() after the command configuration :

  - In polling mode, function returns when the transfer is complete
  - In interrupt mode, the function starts the process and returns, the process continue in background
    (based on the various interrupts). The HAL_XSPI_TxCpltCallback() is called when the process is complete
  - In DMA mode:
      - HAL_XSPI_TxHalfCpltCallback() is called at the half transfer and
        HAL_XSPI_TxCpltCallback() is called when the transfer is complete
      - The half transfer is filtred with HAL_XSPI_Transmit_DMA_Opt() and
        HAL_XSPI_TxCpltCallback() is called when the transfer is complete

- For the indirect read mode, use HAL_XSPI_Receive(), HAL_XSPI_Receive_DMA(), HAL_XSPI_Receive_DMA_Opt()
  or HAL_XSPI_Receive_IT() after the command configuration :

  - In polling mode, function returns when the receive is complete
  - In interrupt mode, the function starts the process and returns, the process continue in background
    (based on the various interrupts). The HAL_XSPI_RxCpltCallback() is called when the process is complete
  - In DMA mode:
      - HAL_XSPI_RxHalfCpltCallback() is called at the half transfer and
        HAL_XSPI_RxCpltCallback() is called when the transfer is complete
      - The half transfer is filtred with HAL_XSPI_Receive_DMA_Opt() and
        HAL_XSPI_RxCpltCallback() is called when the transfer is complete

- Use HAL_XSPI_ExecRegularAutoPoll() or HAL_XSPI_ExecRegularAutoPoll_IT() function to Configure
  the auto-polling functional mode :

  - In polling mode, function returns when the status match is reached. The automatic stop is
    activated to avoid an infinite loop
  - In interrupt mode, HAL_XSPI_StatusMatchCallback() is called each time the status match is reached

- Use HAL_XSPI_Abort()
  or
  HAL_XSPI_Abort_IT() function to abort any on-going operation and to flush the fifo :

  - In polling mode, function returns when the transfer complete bit is set and the busy bit cleared
  - In interrupt mode, the function starts the process and returns, the process continue in background
    (based on the various interrupts). The HAL_XSPI_AbortCpltCallback() is called when the process is complete

- Use HAL_XSPI_StartMemoryMappedMode() function to start the memory-mapped functional mode

- Use HAL_XSPI_StopMemoryMappedMode() function to stop the memory-mapped functional mode

## XSPI IRQHandler , link DMA and Callbacks functions

- XSPI IRQHandler

  - Use HAL_XSPI_IRQHandler() function called under XSPI_IRQHandler interrupt subroutine to handle any XSPI interrupt

- link DMA

  - Use HAL_XSPI_SetTxDMA() function to link/store Tx HAL DMA handle into the HAL XSPI handle
  - Use HAL_XSPI_SetRxDMA() function to link/store Rx HAL DMA handle into the HAL XSPI handle

- Callbacks functions

  - Call the function HAL_XSPI_RegisterErrorCallback() to register the XSPI Error Callback to be used instead of
    the weak HAL_XSPI_ErrorCallback() predefined callback

  - Call the function HAL_XSPI_RegisterAbortCpltCallback() to register the XSPI abort complete Callback to be used
    instead of the weak HAL_XSPI_AbortCpltCallback() predefined callback

  - Call the function HAL_XSPI_RegisterFifoThresholdCallback() to register the XSPI Fifo Threshold Callback to be
    used instead of the weak HAL_XSPI_FifoThresholdCallback() predefined callback

  - Call the function HAL_XSPI_RegisterStatusMatchCallback() to register the XSPI Status Match Callback to be used
    instead of the weak HAL_XSPI_StatusMatchCallback() predefined callback

  - Call the function HAL_XSPI_RegisterTxCpltCallback() to register the XSPI Transfer complete Callback to be used
    instead of the weak HAL_XSPI_TxCpltCallback() predefined callback

  - Call the function HAL_XSPI_RegisterTxHalfCpltCallback() to register the XSPI half Transfer complete Callback to be
    used instead of the weak HAL_XSPI_TxHalfCpltCallback() predefined callback

  - Call the function HAL_XSPI_RegisterRxCpltCallback() to register the XSPI Receive complete Callback to be used
    instead of the weak HAL_XSPI_RxCpltCallback() predefined callback

  - Call the function HAL_XSPI_RegisterRxHalfCpltCallback() to register the XSPI half Receive complete Callback to be
    used instead of the weak HAL_XSPI_RxHalfCpltCallback() predefined callback

## State functions

- Use HAL_XSPI_GetState() function to get the current state of the HAL XSPI driver

## Clock frequency of the XSPI peripheral

- Use HAL_XSPI_GetClockFreq() to retrieve the current clock frequency of the XSPI peripheral.

## XSPI Delay Block functions

- The delay block (DLYB) is used to generate an output clock that is dephased from the input clock

  - Use HAL_XSPI_DLYB_SetConfigDelay() to set the delay configuration of the delay block peripheral
  - Use HAL_XSPI_DLYB_GetConfigDelay() to get the delay output clock phase of the delay block peripheral
  - Use HAL_XSPI_DLYB_CalculateMaxClockPhase() to calculate the maximum output clock phase of the
    delay block peripheral
  - Use HAL_XSPI_DLYB_Enable() to enable the delay block peripheral
  - Use HAL_XSPI_DLYB_Disable() to disable the delay block peripheral
  - Use HAL_XSPI_DLYB_IsEnabled() to check if the delay block peripheral is enabled or not

## XSPI High-speed interface and calibration functions

- The  purpose of High-speed interface is primary to shift data or data strobe by one quarter of octal bus clock period,
  with a correct timing accuracy. DLL must be calibrated versus this clock period
  The calibration process is automatically enabled when one of the three conditions below is met:

  - The xSPI exits Reset state
  - The Prescaler is set
  - The configuration of communication is set

- Use HAL_XSPI_HSIC_SetConfigDelay() function to configure the delay values of the high-speed interface DLLs

- Use HAL_XSPI_HSIC_GetConfigDelay() to retrieve the delay values of the high-speed interface DLLs

## XSPI OTFDEC functions

- The On-The Fly Decryption (OTFDEC) engine is a hardware block used to protect the confidentiality of read-only
  firmware libraries stored in SPI NOR flash devices. The OTFDEC performs on-the-fly decryption during XSPI
  memory-mapped read operation.

- The OTFDEC public services can be used as follows :

  1. Configure the OTFDEC region with user values as mentioned below:
     - Declare a hal_xspi_otfdec_config_t structure
     - Declare a hal_xspi_otfdec_key_t structure
     - Fill all parameters of the declared configuration and keys structures
     - Call HAL_XSPI_OTFDEC_SetConfigRegion() with the filled configuration and keys structures, region index.
     - Use HAL_XSPI_OTFDEC_GetConfigRegion() to retrieve the OTFDEC region parameters. <br>

  2. To protect the key from any write operation, call the HAL_XSPI_OTFDEC_LockRegionKey(). When locked, it's not
     allowed to write in key registers in region x. Applying new keys is then possible only after a system reset of the
     OTFDEC peripheral reset through the RCC.This step is optional. <br>
  3. To protect the peripheral from any configuration, call the HAL_XSPI_OTFDEC_LockRegionConfig(). When locked, it's
     not allowed to apply any new configuration or any other key for the given region. The region configuration is then
     possible only after a system reset of the OTFDEC peripheral reset through RCC. This step is optional. <br>
  4. The OTFDEC can perform encryption of plain data with the HAL_XSPI_OTFDEC_Encrypt() function. Note that : <br>
     - During the OTFDEC encryption, it is not possible to run any other XSPI operation. <br>
     - The encrypted buffer is not programmed/written into the target external memory. It is rather available in the RAM
       and it is up to  the user to program the target external memory with the encrypted buffer. <br>
  5. The On the Fly Decrypt can be started for a given region using HAL_XSPI_OTFDEC_EnableRegion().

## Interrupt functions

- Use HAL_XSPI_EnableIT() function to enable the interrupts

- Use HAL_XSPI_DisableIT() function to disable the interrupts

- Use HAL_XSPI_IsEnabledIT() function to get the source of interrupt

- Use HAL_XSPI_IsActiveFlag() function to get flags

- Use HAL_XSPI_ClearFlag() function to clear flags

## Configuration inside the XSPI driver

Config defines                  | Description     | Default value     | Note
------------------------------- | --------------- | ----------------- | ------------------------------------------------
PRODUCT                         | from IDE        | NA                | The selected device (Ex: STM32U5XX)
USE_HAL_XSPI_MODULE             | from hal_conf.h | 1                 | Allows to use HAL XSPI module
USE_ASSERT_DBG_PARAM            | from IDE        | NA                | Allows to use the assert check parameters
USE_ASSERT_DBG_STATE            | from IDE        | NA                | Allows to use the assert check states
USE_HAL_CHECK_PARAM             | from hal_conf.h | 0                 | Allows to use the run-time checks parameters
USE_HAL_CHECK_PROCESS_STATE     | from hal_conf.h | 0                 | Allows to use the load and store exclusive
USE_HAL_XSPI_DMA                | from hal_conf.h | 1                 | Allows to use DMA mode
USE_HAL_XSPI_HYPERBUS           | from hal_conf.h | 1                 | Allows to use HYPERBUS protocol
USE_HAL_XSPI_OTFDEC             | from hal_conf.h | 0                 | Allows to use OTFDEC peripheral
USE_HAL_SECURE_CHECK_PARAM      | from hal_conf.h | 0                 | Parameters run-time check for sensitive APIs
USE_HAL_XSPI_REGISTER_CALLBACKS | from hal_conf.h | 0                 | Allows to use register callbacks
USE_HAL_XSPI_CLK_ENABLE_MODEL   | from hal_conf.h | HAL_CLK_ENABLE_NO | Allows to use the clock enable model

 */
#if defined(HSPI1) || defined(OCTOSPI1)|| defined(OCTOSPI2)

#if defined (USE_HAL_XSPI_MODULE) && (USE_HAL_XSPI_MODULE == 1)

/** @defgroup XSPI_Private_Constants XSPI Private Constants
  * @{
  */
#define XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE 0x00000000U     /*!< Indirect write mode               */
#define XSPI_FUNCTIONAL_MODE_INDIRECT_READ  XSPI_CR_FMODE_0 /*!< Indirect read mode                */
#define XSPI_FUNCTIONAL_MODE_AUTO_POLLING   XSPI_CR_FMODE_1 /*!< Automatic polling mode            */
#define XSPI_FUNCTIONAL_MODE_MEMORY_MAPPED  XSPI_CR_FMODE   /*!< Memory-mapped mode                */

#define XSPI_TIMEOUT_DEFAULT_VALUE          5U              /*!< XSPI timeout 5 seconds            */

#define XSPIM_PORT_1                        0U              /*!< XSPI Port 1                       */
#define XSPIM_PORT_2                        1U              /*!< XSPI Port 2                       */
#define XSPIM_IO_HIGH_POS                   8U              /*!< Shifting from low to high IO port */
#define XSPI_FIFO_FULL_SIZE                 64U             /*!< Data pass through 64-byte FIFO    */
#define XSPI_FIFO_MEDIUM_SIZE               32U             /*!< Data pass through 32-byte FIFO    */
#if defined(XSPI_CR_MSEL)
#define XSPI_IO_SELECT_MSK                  XSPI_CR_MSEL    /*!< IO memory selection               */
#else
#define XSPI_IO_SELECT_MSK                  XSPI_CR_FSEL    /*!< IO memory selection               */
#endif /* XSPI_CR_MSEL */
/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup XSPI_Private_Macros XSPI Private Macros
  * @{
  */
/**
  * @brief Get the XSPI instance
  */
#define XSPI_GET_INSTANCE(handle) ((XSPI_TypeDef *)((uint32_t)(handle)->instance))

/**
  * @brief Get the XSPI instance within Delay Block
  */
#if defined(DLYB_OCTOSPI2)
#define XSPI_DLYB_GET_INSTANCE(instance) (((instance) == HAL_OCTOSPI1) ? DLYB_OCTOSPI1 : DLYB_OCTOSPI2)
#else
#define XSPI_DLYB_GET_INSTANCE(instance) \
  ({                                     \
    STM32_UNUSED((instance));            \
    DLYB_OCTOSPI1;                       \
  })
#endif /* DLYB_OCTOSPI2 */

/**
  * @brief Check the Functional mode
  */
#define IS_XSPI_FUNCTIONAL_MODE(mode) (((mode) == XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE)   \
                                       || ((mode) == XSPI_FUNCTIONAL_MODE_INDIRECT_READ) \
                                       || ((mode) == XSPI_FUNCTIONAL_MODE_AUTO_POLLING)  \
                                       || ((mode) == XSPI_FUNCTIONAL_MODE_MEMORY_MAPPED))

/**
  * @brief Check the Fifo threshold
  */
#define IS_XSPI_FIFO_THRESHOLD_BYTE(instance, threshold) ((IS_XSPI_FULL_FIFO_SIZE(instance)) ?      \
                                                          (((threshold) >= 1U)                      \
                                                           && ((threshold) <= XSPI_FIFO_FULL_SIZE)) \
                                                          :(((threshold) >= 1U)                     \
                                                            && ((threshold) <= XSPI_FIFO_MEDIUM_SIZE)))

/**
  * @brief Check the Memory mode
  */
#define IS_XSPI_MEMORY_MODE(mode)                 (((mode) == HAL_XSPI_MEMORY_SINGLE) \
                                                   || ((mode) == HAL_XSPI_MEMORY_DUAL))

/**
  * @brief Check the Memory type
  */
#define IS_XSPI_MEMORY_TYPE(type)                 (((type) == HAL_XSPI_MEMORY_TYPE_MICRON)          \
                                                   || ((type) == HAL_XSPI_MEMORY_TYPE_MACRONIX)     \
                                                   || ((type) == HAL_XSPI_MEMORY_TYPE_APMEM)        \
                                                   || ((type) == HAL_XSPI_MEMORY_TYPE_MACRONIX_RAM) \
                                                   || ((type) == HAL_XSPI_MEMORY_TYPE_HYPERBUS)     \
                                                   || ((type) == HAL_XSPI_MEMORY_TYPE_APMEM_16BIT))

/**
  * @brief Check the Memory size
  */
#define IS_XSPI_MEMORY_SIZE(size)                 (((size) == HAL_XSPI_MEMORY_SIZE_16BIT)      \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_32BIT)   \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_64BIT)   \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_128BIT)  \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_256BIT)  \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_512BIT)  \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_1KBIT)   \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_2KBIT)   \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_4KBIT)   \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_8KBIT)   \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_16KBIT)  \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_32KBIT)  \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_64KBIT)  \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_128KBIT) \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_256KBIT) \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_512KBIT) \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_1MBIT)   \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_2MBIT)   \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_4MBIT)   \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_8MBIT)   \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_16MBIT)  \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_32MBIT)  \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_64MBIT)  \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_128MBIT) \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_256MBIT) \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_512MBIT) \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_1GBIT)   \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_2GBIT)   \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_4GBIT)   \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_8GBIT)   \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_16GBIT)  \
                                                   || ((size) == HAL_XSPI_MEMORY_SIZE_32GBIT))

/**
  * @brief Check the Chip select high time cycle
  */
#define IS_XSPI_CS_HIGH_TIME_CYCLE(time)          (((time) >= 1U) && ((time) <= 64U))

/**
  * @brief Check the Clock polarity
  */
#define IS_XSPI_CLOCK_POLARITY(mode)              (((mode) == HAL_XSPI_CLOCK_LOW) \
                                                   || ((mode) == HAL_XSPI_CLOCK_HIGH))

/**
  * @brief Check the Wrap size
  */
#define IS_XSPI_WRAP_SIZE(size)                   (((size) == HAL_XSPI_WRAP_NOT_SUPPORTED) \
                                                   || ((size) == HAL_XSPI_WRAP_16BYTE)     \
                                                   || ((size) == HAL_XSPI_WRAP_32BYTE)     \
                                                   || ((size) == HAL_XSPI_WRAP_64BYTE)     \
                                                   || ((size) == HAL_XSPI_WRAP_128BYTE))

/**
  * @brief Check the prescaler factor
  */
#define IS_XSPI_CLOCK_PRESCALER(prescaler)        ((prescaler) <= 255U)

/**
  * @brief Check the Sample shift
  */
#define IS_XSPI_SAMPLE_SHIFT(cycle)               (((cycle) == HAL_XSPI_SAMPLE_SHIFT_NONE) \
                                                   || ((cycle) == HAL_XSPI_SAMPLE_SHIFT_HALFCYCLE))

/**
  * @brief Check the delay hold
  */
#define IS_XSPI_DELAY_HOLD(cycle)                 (((cycle) == HAL_XSPI_DELAY_HOLD_NONE) \
                                                   || ((cycle) == HAL_XSPI_DELAY_HOLD_QUARTCYCLE))

/**
  * @brief Check the chip select boundary
  */
#define IS_XSPI_CS_BOUNDARY(size)                 (((size) == HAL_XSPI_CS_BOUNDARY_NONE)       \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_16BIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_32BIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_64BIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_128BIT)  \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_256BIT)  \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_512BIT)  \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_1KBIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_2KBIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_4KBIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_8KBIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_16KBIT)  \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_32KBIT)  \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_64KBIT)  \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_128KBIT) \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_256KBIT) \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_512KBIT) \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_1MBIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_2MBIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_4MBIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_8MBIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_16MBIT)  \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_32MBIT)  \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_64MBIT)  \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_128MBIT) \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_256MBIT) \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_512MBIT) \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_1GBIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_2GBIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_4GBIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_8GBIT)   \
                                                   || ((size) == HAL_XSPI_CS_BOUNDARY_16GBIT))

/**
  * @brief Check the delay block bypass
  */
#define IS_XSPI_DLYB_BYPASS(dlyb)                 (((dlyb) == HAL_XSPI_DLYB_ON) \
                                                   || ((dlyb) == HAL_XSPI_DLYB_BYPASS))

/**
  * @brief Check the Chip select release time cycle
  */
#define IS_XSPI_MAXTRAN(nb_bytes)                 ((nb_bytes) <= 255U)

/**
  * @brief Check the Operation type
  */
#define IS_XSPI_OPERATION_TYPE(type)              (((type) == HAL_XSPI_OPERATION_READ_CFG)     \
                                                   || ((type) == HAL_XSPI_OPERATION_WRITE_CFG) \
                                                   || ((type) == HAL_XSPI_OPERATION_WRAP_CFG))

/**
  * @brief Check the I/O select
  */
#if defined(XSPI_CR_MSEL)
#define IS_XSPI_IO_SELECT(instance, memsel)       ((IS_XSPI_HSPI_INSTANCE(instance))?   \
                                                   (((memsel) == HAL_XSPI_IO_3_0)       \
                                                    || ((memsel) == HAL_XSPI_IO_7_4)    \
                                                    || ((memsel) == HAL_XSPI_IO_7_0)    \
                                                    || ((memsel) == HAL_XSPI_IO_11_8)   \
                                                    || ((memsel) == HAL_XSPI_IO_15_12)  \
                                                    || ((memsel) == HAL_XSPI_IO_15_8))  \
                                                   :(((memsel) == HAL_XSPI_IO_3_0)      \
                                                     || ((memsel) == HAL_XSPI_IO_7_4)   \
                                                     || ((memsel) == HAL_XSPI_IO_7_0)))
#else
#define IS_XSPI_IO_SELECT(instance, memsel)       (((memsel) == HAL_XSPI_IO_3_0)    \
                                                   || ((memsel) == HAL_XSPI_IO_7_4) \
                                                   || ((memsel) == HAL_XSPI_IO_7_0))
#endif /* XSPI_CR_MSEL */

/**
  * @brief Check the Instruction mode
  */
#define IS_XSPI_INSTRUCTION_MODE(mode)            (((mode) == HAL_XSPI_INSTRUCTION_NONE)      \
                                                   || ((mode) == HAL_XSPI_INSTRUCTION_1LINE)  \
                                                   || ((mode) == HAL_XSPI_INSTRUCTION_2LINES) \
                                                   || ((mode) == HAL_XSPI_INSTRUCTION_4LINES) \
                                                   || ((mode) == HAL_XSPI_INSTRUCTION_8LINES))

/**
  * @brief Check the Instruction width
  */
#define IS_XSPI_INSTRUCTION_WIDTH(width)          (((width) == HAL_XSPI_INSTRUCTION_8BIT)     \
                                                   || ((width) == HAL_XSPI_INSTRUCTION_16BIT) \
                                                   || ((width) == HAL_XSPI_INSTRUCTION_24BIT) \
                                                   || ((width) == HAL_XSPI_INSTRUCTION_32BIT))

/**
  * @brief Check the Instruction dtr mode
  */
#define IS_XSPI_INSTRUCTION_DTR_MODE(mode)        (((mode) == HAL_XSPI_INSTRUCTION_DTR_DISABLED) \
                                                   || ((mode) == HAL_XSPI_INSTRUCTION_DTR_ENABLED))

/**
  * @brief Check the Address mode
  */
#define IS_XSPI_ADDR_MODE(mode)                   (((mode) == HAL_XSPI_ADDR_NONE)      \
                                                   || ((mode) == HAL_XSPI_ADDR_1LINE)  \
                                                   || ((mode) == HAL_XSPI_ADDR_2LINES) \
                                                   || ((mode) == HAL_XSPI_ADDR_4LINES) \
                                                   || ((mode) == HAL_XSPI_ADDR_8LINES))

/**
  * @brief Check the Address width
  */
#define IS_XSPI_ADDR_WIDTH(width)                 (((width) == HAL_XSPI_ADDR_8BIT)     \
                                                   || ((width) == HAL_XSPI_ADDR_16BIT) \
                                                   || ((width) == HAL_XSPI_ADDR_24BIT) \
                                                   || ((width) == HAL_XSPI_ADDR_32BIT))

/**
  * @brief Check the Address dtr mode
  */
#define IS_XSPI_ADDR_DTR_MODE(mode)               (((mode) == HAL_XSPI_ADDR_DTR_DISABLED) \
                                                   || ((mode) == HAL_XSPI_ADDR_DTR_ENABLED))

/**
  * @brief Check the Alternate bytes mode
  */
#define IS_XSPI_ALTERNATE_BYTES_MODE(mode)        (((mode) == HAL_XSPI_ALTERNATE_BYTES_NONE)      \
                                                   || ((mode) == HAL_XSPI_ALTERNATE_BYTES_1LINE)  \
                                                   || ((mode) == HAL_XSPI_ALTERNATE_BYTES_2LINES) \
                                                   || ((mode) == HAL_XSPI_ALTERNATE_BYTES_4LINES) \
                                                   || ((mode) == HAL_XSPI_ALTERNATE_BYTES_8LINES))

/**
  * @brief Check the Alternate bytes width
  */
#define IS_XSPI_ALTERNATE_BYTES_WIDTH(width)      (((width) == HAL_XSPI_ALTERNATE_BYTES_8BIT)     \
                                                   || ((width) == HAL_XSPI_ALTERNATE_BYTES_16BIT) \
                                                   || ((width) == HAL_XSPI_ALTERNATE_BYTES_24BIT) \
                                                   || ((width) == HAL_XSPI_ALTERNATE_BYTES_32BIT))

/**
  * @brief Check the Alternate bytes dtr mode
  */
#define IS_XSPI_ALTERNATE_BYTES_DTR_MODE(mode)    (((mode) == HAL_XSPI_ALTERNATE_BYTES_DTR_DISABLED) \
                                                   || ((mode) == HAL_XSPI_ALTERNATE_BYTES_DTR_ENABLED))

/**
  * @brief Check the Regular data mode
  */
#if defined(XSPI_CR_MSEL)
#define IS_XSPI_REGULAR_DATA_MODE(instance, mode) ((IS_XSPI_HSPI_INSTANCE(instance))?             \
                                                   (((mode) == HAL_XSPI_REGULAR_DATA_NONE)        \
                                                    || ((mode) == HAL_XSPI_REGULAR_DATA_1LINE)    \
                                                    || ((mode) == HAL_XSPI_REGULAR_DATA_2LINES)   \
                                                    || ((mode) == HAL_XSPI_REGULAR_DATA_4LINES)   \
                                                    || ((mode) == HAL_XSPI_REGULAR_DATA_8LINES)   \
                                                    || ((mode) == HAL_XSPI_REGULAR_DATA_16LINES)) \
                                                   :(((mode) == HAL_XSPI_REGULAR_DATA_NONE)       \
                                                     || ((mode) == HAL_XSPI_REGULAR_DATA_1LINE)   \
                                                     || ((mode) == HAL_XSPI_REGULAR_DATA_2LINES)  \
                                                     || ((mode) == HAL_XSPI_REGULAR_DATA_4LINES)  \
                                                     || ((mode) == HAL_XSPI_REGULAR_DATA_8LINES)))
#else
#define IS_XSPI_REGULAR_DATA_MODE(instance, mode) (((mode) == HAL_XSPI_REGULAR_DATA_NONE)      \
                                                   || ((mode) == HAL_XSPI_REGULAR_DATA_1LINE)  \
                                                   || ((mode) == HAL_XSPI_REGULAR_DATA_2LINES) \
                                                   || ((mode) == HAL_XSPI_REGULAR_DATA_4LINES) \
                                                   || ((mode) == HAL_XSPI_REGULAR_DATA_8LINES))
#endif /* XSPI_CR_MSEL */

/**
  * @brief Check the Hyperbus data mode
  */
#if defined(XSPI_CR_MSEL)
#define IS_XSPI_HYPERBUS_DATA_MODE(instance, mode) ((IS_XSPI_HSPI_INSTANCE(instance))?              \
                                                    (((mode) == HAL_XSPI_HYPERBUS_DATA_8LINES)      \
                                                     || ((mode) == HAL_XSPI_HYPERBUS_DATA_16LINES)) \
                                                    :(((mode) == HAL_XSPI_HYPERBUS_DATA_8LINES)))
#else
#define IS_XSPI_HYPERBUS_DATA_MODE(instance, mode) (((mode) == HAL_XSPI_HYPERBUS_DATA_8LINES))
#endif /* XSPI_CR_MSEL */

/**
  * @brief Check the Data length
  */
#define IS_XSPI_DATA_LENGTH(number)               ((number) >= 1U)

/**
  * @brief Check the Data dtr mode
  */
#define IS_XSPI_DATA_DTR_MODE(mode)               (((mode) == HAL_XSPI_DATA_DTR_DISABLED) \
                                                   || ((mode) == HAL_XSPI_DATA_DTR_ENABLED))

/**
  * @brief Check the Dummy cycles
  */
#define IS_XSPI_DUMMY_CYCLES(number)              ((number) <= 31U)

/**
  * @brief Check the Dqs mode
  */
#define IS_XSPI_DQS_MODE(mode)                    (((mode) == HAL_XSPI_DQS_DISABLED) \
                                                   || ((mode) == HAL_XSPI_DQS_ENABLED))

/**
  * @brief Check the RW recovery time cycle
  */
#define IS_XSPI_RW_RECOVERY_TIME_CYCLE(cycle)     ((cycle) <= 255U)

/**
  * @brief Check the Access time cycle
  */
#define IS_XSPI_ACCESS_TIME_CYCLE(cycle)          ((cycle) <= 255U)

/**
  * @brief Check the Write zero latency
  */
#define IS_XSPI_WRITE_ZERO_LATENCY(mode)          (((mode) == HAL_XSPI_WRITE_ZERO_LATENCY_DISABLED) \
                                                   || ((mode) == HAL_XSPI_WRITE_ZERO_LATENCY_ENABLED))
/**
  * @brief Check the Latency mode
  */
#define IS_XSPI_LATENCY_MODE(mode)                (((mode) == HAL_XSPI_LATENCY_VARIABLE) \
                                                   || ((mode) == HAL_XSPI_LATENCY_FIXED))

/**
  * @brief Check the Address space
  */
#define IS_XSPI_ADDRESS_SPACE(SPACE)              (((SPACE) == HAL_XSPI_ADDR_MEMORY) \
                                                   || ((SPACE) == HAL_XSPI_ADDR_REGISTER))

/**
  * @brief Check the Match mode
  */
#define IS_XSPI_MATCH_MODE(mode)                  (((mode) == HAL_XSPI_MATCH_MODE_AND) \
                                                   || ((mode) == HAL_XSPI_MATCH_MODE_OR))

/**
  * @brief Check the Autromatic stop
  */
#define IS_XSPI_AUTOMATIC_STOP(mode)              (((mode) == HAL_XSPI_AUTOMATIC_STOP_ENABLED) \
                                                   || ((mode) == HAL_XSPI_AUTOMATIC_STOP_DISABLED))

/**
  * @brief Check the Interval time
  */
#define IS_XSPI_INTERVAL(interval)                ((interval) <= 0xFFFFU)

/**
  * @brief Check the Status bytes size
  */
#define IS_XSPI_STATUS_BYTES_SIZE(size)           (((size) >= 1U) && ((size) <= 4U))

/**
  * @brief Check the Timeout activation
  */
#define IS_XSPI_TIMEOUT_ACTIVATION(mode)          (((mode) == HAL_XSPI_TIMEOUT_DISABLE) \
                                                   || ((mode) == HAL_XSPI_TIMEOUT_ENABLE))

/**
  * @brief Check the Timeout period
  */
#define IS_XSPI_TIMEOUT_PERIOD(period)            ((period) <= 0xFFFFU)

#if defined(XSPIM)
/**
  * @brief Check the XSPIM Port
  */
#define IS_XSPIM_PORT(port)                       (((port) == HAL_XSPI_XSPIM_NONE)     \
                                                   || ((port) == HAL_XSPI_XSPIM_XSPI1) \
                                                   || ((port) == HAL_XSPI_XSPIM_XSPI2) \
                                                   || ((port) == HAL_XSPI_XSPIM_XSPI1_XSPI2))

/**
  * @brief Check the XSPIM I/O Port
  */
#define IS_XSPIM_IO_PORT(port)                    (((port) == HAL_XSPI_XSPIM_IO_NONE)               \
                                                   || ((port) == HAL_XSPI_XSPIM_XSPI1_IO_LOW)       \
                                                   || ((port) == HAL_XSPI_XSPIM_XSPI2_IO_LOW)       \
                                                   || ((port) == HAL_XSPI_XSPIM_XSPI1_IO_HIGH)      \
                                                   || ((port) == HAL_XSPI_XSPIM_XSPI2_IO_HIGH)      \
                                                   || ((port) == HAL_XSPI_XSPIM_XSPI1_XSPI2_IO_LOW) \
                                                   || ((port) == HAL_XSPI_XSPIM_XSPI1_XSPI2_IO_HIGH))

/**
  * @brief Check the minimum switching duration
  */
#define IS_XSPIM_REQ2ACKTIME(time)                (((time) >= 1U) && ((time) <= 256U))
#endif /* XSPIM */
#if defined(XSPI_CALFCR_FINE)
/**
  * @brief Check the maximum calibration
  */
#define IS_XSPI_HSIC_MAX_CAL(mode)                (((mode) == HAL_XSPI_HSIC_MAX_CAL_NOT_REACHED) \
                                                   || ((mode) == HAL_XSPI_HSIC_MAX_CAL_REACHED))

/**
  * @brief Check the Delay type
  */
#define IS_XSPI_HSIC_DELAY_CAL_TYPE(type)         (((type) == HAL_XSPI_HSIC_DELAY_CAL_FULL_CYCLE)      \
                                                   || ((type) == HAL_XSPI_HSIC_DELAY_CAL_FEEDBACK_CLK) \
                                                   || ((type) == HAL_XSPI_HSIC_DELAY_CAL_DATA_OUTPUT)  \
                                                   || ((type) == HAL_XSPI_HSIC_DELAY_CAL_DQS_INPUT))

/**
  * @brief Check the fine calibration value
  */
#define IS_XSPI_HSIC_FINECAL_VALUE(value)         ((value) <= 0x7FU)

/**
  * @brief Check the coarse calibration value
  */
#define IS_XSPI_HSIC_COARSECAL_VALUE(value)       ((value) <= 0x1FU)
#endif /* XSPI_CALFCR_FINE */

/**
  * @brief Check XSPI optional interrupt
  */
#define IS_XSPI_OPT_IT(value)                     (((value) == HAL_XSPI_OPT_IT_NONE)  \
                                                   || ((value) == HAL_XSPI_OPT_IT_HT) \
                                                   || ((value) == HAL_XSPI_OPT_IT_DEFAULT))

/**
  * @}
  */

#if defined (USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined (OTFDEC1)
/** @defgroup XSPI_OTFDEC_Private_Constants XSPI OTFDEC Private Constants
  * @{
  */
#if defined (OTFDEC2)
#define OCTOSPI_BASE_ADDRESS OCTOSPI2_BASE  /*!< OCTOSPI2 base address               */
#else
#define OCTOSPI_BASE_ADDRESS OCTOSPI1_BASE  /*!< OCTOSPI1 base address               */
#endif /* OTFDEC2 */

/**
  * @}
  */

/** @defgroup XSPI_OTFDEC_Private_Macros XSPI OTFDEC Private Macros
  * @{
  */
/**
  * @brief Get the XSPI OTFDEC instance
  */
#if defined (OTFDEC2)
#define XSPI_OTFDEC_GET_INSTANCE(instance) (((instance) == HAL_OCTOSPI1) ? OTFDEC1 : OTFDEC2)
#else
#define XSPI_OTFDEC_GET_INSTANCE(instance) \
  ({                                       \
    STM32_UNUSED((instance));              \
    OTFDEC1;                               \
  })
#endif /* OTFDEC2 */

/**
  * @brief Convert the region index into CMSIS region address
  */
#if defined (OTFDEC2)
#define XSPI_OTFDEC_GET_REGION_INSTANCE(instance, region_idx) (                                   \
    (((instance) == (OTFDEC1)) && (region_idx == HAL_XSPI_OTFDEC_REGION_1)) ? (OTFDEC1_REGION1): \
    (((instance) == (OTFDEC1)) && (region_idx == HAL_XSPI_OTFDEC_REGION_2)) ? (OTFDEC1_REGION2): \
    (((instance) == (OTFDEC1)) && (region_idx == HAL_XSPI_OTFDEC_REGION_3)) ? (OTFDEC1_REGION3): \
    (((instance) == (OTFDEC1)) && (region_idx == HAL_XSPI_OTFDEC_REGION_4)) ? (OTFDEC1_REGION4): \
    (((instance) == (OTFDEC2)) && (region_idx == HAL_XSPI_OTFDEC_REGION_1)) ? (OTFDEC2_REGION1): \
    (((instance) == (OTFDEC2)) && (region_idx == HAL_XSPI_OTFDEC_REGION_2)) ? (OTFDEC2_REGION2): \
    (((instance) == (OTFDEC2)) && (region_idx == HAL_XSPI_OTFDEC_REGION_3)) ? (OTFDEC2_REGION3): \
    (OTFDEC2_REGION4))
#else
#define XSPI_OTFDEC_GET_REGION_INSTANCE(instance, region_idx) (                                   \
    (((instance) == (OTFDEC1)) && (region_idx == HAL_XSPI_OTFDEC_REGION_1)) ? (OTFDEC1_REGION1): \
    (((instance) == (OTFDEC1)) && (region_idx == HAL_XSPI_OTFDEC_REGION_2)) ? (OTFDEC1_REGION2): \
    (((instance) == (OTFDEC1)) && (region_idx == HAL_XSPI_OTFDEC_REGION_3)) ? (OTFDEC1_REGION3): \
    (OTFDEC1_REGION4))
#endif /* OTFDEC2 */

/**
  * @brief Check the OTFDEC region index
  */
#define IS_XSPI_OTFDEC_REGION(otfdec_region)               (((otfdec_region) == HAL_XSPI_OTFDEC_REGION_1)    \
                                                            || ((otfdec_region) == HAL_XSPI_OTFDEC_REGION_2) \
                                                            || ((otfdec_region) == HAL_XSPI_OTFDEC_REGION_3) \
                                                            || ((otfdec_region) == HAL_XSPI_OTFDEC_REGION_4))

/**
  * @brief Check the OTFDEC operation mode
  */
#define IS_XSPI_OTFDEC_MODE(mode)                          (((mode) == (HAL_XSPI_OTFDEC_MODE_ALL_READ_ACCESS)) \
                                                            || ((mode) == (OTFDEC_MODE_ENHANCED_ENCRYPTION)))

/**
  * @brief Check the OTFDEC region lock configuration status
  */
#define IS_XSPI_OTFDEC_LOCK_CONFIG(lock_config)            (((lock_config) == HAL_XSPI_OTFDEC_LOCK_CONFIG_ENABLED) \
                                                            || ((lock_config) == HAL_XSPI_OTFDEC_LOCK_CONFIG_DISABLED))

/**
  * @brief Check the OTFDEC key lock configuration status
  */
#define IS_XSPI_OTFDEC_LOCK_KEY(lock_key)                  (((lock_key) == HAL_OTFDEC_LOCK_KEY_ENABLED) \
                                                            || ((lock_key) == HAL_OTFDEC_LOCK_KEY_DISABLED))

/**
  * @brief Check the OTFDEC privilege configuration attributes
  */
#define IS_XSPI_OTFDEC_PRIV_ATTR(attributes)               (((attributes) == HAL_OTFDEC_ATTRIBUTE_NON_PRIVILEGED) \
                                                            || ((attributes) == HAL_OTFDEC_ATTRIBUTE_PRIVILEGED))

/**
  * @brief Check OTFDEC interrupts
  */
#define IS_XSPI_OTFDEC_IT(it)                            (((it) == (HAL_XSPI_OTFDEC_IT_KEY_ERROR))                     \
                                                          || ((it) == (HAL_XSPI_OTFDEC_IT_SECURITY_ERROR))             \
                                                          || ((it) == (HAL_XSPI_OTFDEC_IT_EXEC_ONLY_EXEC_NEVER_ERROR)) \
                                                          || ((it) == (HAL_XSPI_OTFDEC_IT_ALL))                        \
                                                          || ((it) == (HAL_XSPI_OTFDEC_IT_NONE)))

/**
  * @brief Check the OTFDEC satrt address
  */
#define IS_XSPI_OTFDEC_START_ADRESS(start_address) ((start_address) >= (OCTOSPI_BASE_ADDRESS))

/**
  * @brief Check the OTFDEC region granularity
  */
#define IS_XSPI_OTFDEC_RGION_SIZE(start_address, end_address) (((end_address) - (start_address)) == (0xFFFU))

/**
  * @brief Number of OTFDEC regions
  */
#define OTFDEC_REGIONS   4U

/**
  * @}
  */
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */

/* Private types -----------------------------------------------------------------------------------------------------*/
/** @defgroup XSPI_Private_Types XSPI Private Types
  * @{
  */
/*! XSPI Interrupt state*/
typedef enum
{
  XSPI_INTERRUPT_DISABLE = 0U, /*!< HAL XSPI interrupt disabled */
  XSPI_INTERRUPT_ENABLE  = 1U, /*!< HAL XSPI interrupt enabled  */

} hal_xspi_interrupt_state_t;
/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @defgroup XSPI_Private_Functions XSPI Private Functions
  * @{
  */
static hal_status_t XSPI_WaitFlagStateUntilTimeout(hal_xspi_handle_t *hxspi, uint32_t flag,
                                                   hal_xspi_flag_status_t state, uint32_t timeout_ms);
static hal_status_t XSPI_SendRegularCmd(hal_xspi_handle_t *hxspi, const hal_xspi_regular_cmd_t *p_cmd,
                                        uint32_t timeout_ms, hal_xspi_interrupt_state_t it_state);
static hal_status_t XSPI_ExecRegularAutoPoll(hal_xspi_handle_t *hxspi, const hal_xspi_auto_polling_config_t *p_config,
                                             uint32_t timeout_ms, hal_xspi_interrupt_state_t it_state);
static hal_status_t XSPI_Abort(hal_xspi_handle_t *hxspi, uint32_t timeout_ms);

#if defined(USE_HAL_XSPI_DMA) && (USE_HAL_XSPI_DMA == 1)
static void  XSPI_DMACplt(hal_dma_handle_t *hdma);
static void  XSPI_DMAHalfCplt(hal_dma_handle_t *hdma);
static void  XSPI_DMAError(hal_dma_handle_t *hdma);
static void  XSPI_DMAAbort(hal_dma_handle_t *hdma);
static void  XSPI_DMAAbortOnError(hal_dma_handle_t *hdma);
#endif /* USE_HAL_XSPI_DMA */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup XSPI_Exported_Functions
  * @{
  */

/** @addtogroup XSPI_Exported_Functions_Group1
  * @{
This subsection provides a set of functions allowing to initialize and
deinitialize the XSPIx peripheral:
- Call the function HAL_XSPI_Init() to initialize the selected HAL XSPI handle and associate an XSPI peripheral instance
- Call the function HAL_XSPI_DeInit() to de-initialize the given HAL XSPI instance by stopping any ongoing process and
  resetting the state machine

  */

/**
  * @brief  Initialize the XSPI according to the associated instance.
  * @param  instance XSPI instance, can be one of the XSPI instances as defined in the CMSIS device
  *                  header file.
  * @param  hxspi    Pointer to a hal_xspi_handle_t structure that contains
  *                  handle information for the specified XSPI instance.
  * @note   The XSPI clock can be activated within the HAL_XSPI_Init() function by setting
  *         the <b> USE_XSPI_CLK_ENABLE_MODEL </b> flag to **HAL_CLK_ENABLE_XSPI_ONLY**
  *         in the configuration file ** stm32tnxx_hal_conf.h **.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            hxspi instance has been correctly Initialized.
  */
hal_status_t HAL_XSPI_Init(hal_xspi_handle_t *hxspi, hal_xspi_t instance)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_ALL_INSTANCE((XSPI_TypeDef *)((uint32_t)instance)));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hxspi == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif  /* USE_HAL_CHECK_PARAM */

  /* Associate physical instance to logical object */
  hxspi->instance = instance;

#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
  hxspi->p_error_cb          = HAL_XSPI_ErrorCallback;          /* Error callback reset             */
  hxspi->p_abort_cplt_cb     = HAL_XSPI_AbortCpltCallback;      /* Abort callback reset             */
  hxspi->p_fifo_threshold_cb = HAL_XSPI_FifoThresholdCallback;  /* Fifo Threshold callback reset    */
  hxspi->p_cmd_cplt_cb       = HAL_XSPI_CmdCpltCallback;        /* Command Complete callback reset  */
  hxspi->p_rx_cplt_cb        = HAL_XSPI_RxCpltCallback;         /* Rx Complete callback reset       */
  hxspi->p_tx_cplt_cb        = HAL_XSPI_TxCpltCallback;         /* Tx Complete callback reset       */
  hxspi->p_rx_half_cplt_cb   = HAL_XSPI_RxHalfCpltCallback;     /* Rx Half Complete callback reset  */
  hxspi->p_tx_half_cplt_cb   = HAL_XSPI_TxHalfCpltCallback;     /* Tx Half Complete callback reset  */
  hxspi->p_status_match_cb   = HAL_XSPI_StatusMatchCallback;    /* Status Match callback reset      */
#if defined (USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined (OTFDEC1)
  hxspi->p_otfdec_error_cb   = HAL_XSPI_OTFDEC_ErrorCallback;   /* Error callback of the OTFDEC peripheral */
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */

#if defined(USE_HAL_XSPI_CLK_ENABLE_MODEL) && (USE_HAL_XSPI_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  /* Enable the XSPI Peripheral Clock */
  switch (hxspi->instance)
  {
    case HAL_OCTOSPI1:
      /* Enable Clock */
      LL_AHB2_GRP2_EnableClock(LL_AHB2_GRP2_PERIPH_OCTOSPI1);
#if defined (USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined (OTFDEC1)
      LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_OTFDEC1);
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */
      break;
#if defined(OCTOSPI2)
    case HAL_OCTOSPI2:
      /* Enable Clock */
      LL_AHB2_GRP2_EnableClock(LL_AHB2_GRP2_PERIPH_OCTOSPI2);
#if defined (USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined (OTFDEC2)
      LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_OTFDEC2);
#endif /* OTFDEC2 */
#endif /* USE_HAL_XSPI_OTFDEC */
      break;
#endif /* OCTOSPI2 */
#if defined(HSPI1)
    case HAL_HSPI1:
      /* Enable Clock */
      LL_AHB2_GRP2_EnableClock(LL_AHB2_GRP2_PERIPH_HSPI1);
      break;
#endif /* HSPI1 */
    default:
      break;
  }
#endif /* USE_HAL_XSPI_CLK_ENABLE_MODEL */

#if defined (USE_HAL_XSPI_USER_DATA) && (USE_HAL_XSPI_USER_DATA == 1)
  hxspi->p_user_data = NULL;
#endif /* USE_HAL_XSPI_USER_DATA */

#if defined (USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  hxspi->last_error_codes = HAL_XSPI_ERROR_NONE;
#if defined(USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined (OTFDEC1)
  hxspi->last_otfdec_error_codes = HAL_XSPI_ERROR_OTFDEC_NONE;
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

#if defined (USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined (OTFDEC1)
  /* Reset regions state */
  for (uint32_t i = 0; i < OTFDEC_REGIONS; i++)
  {
    hxspi->region_state[i] = HAL_XSPI_OTFDEC_REGION_STATE_RESET;
  }
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */

  hxspi->global_state = HAL_XSPI_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  De-Initialize the XSPI peripheral.
  * @param  hxspi Pointer to a hal_xspi_handle_t structure that contains
  *               handle information for the specified XSPI instance.
  */
void HAL_XSPI_DeInit(hal_xspi_handle_t *hxspi)
{
#if defined (USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined (OTFDEC1)
  OTFDEC_TypeDef        *otfdec_instance;
  OTFDEC_Region_TypeDef *otfdec_region;
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_ALL_INSTANCE(XSPI_GET_INSTANCE(hxspi)));

#if defined (USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined (OTFDEC1)
  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */

  /* Abort the current XSPI operation */
  (void)XSPI_Abort(hxspi, XSPI_TIMEOUT_DEFAULT_VALUE);

  /* Disable XSPI Instances */
  CLEAR_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_EN);

#if defined (USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined (OTFDEC1)
  /* Disable all regions and reset regions state */
  for (uint32_t i = 0; i < OTFDEC_REGIONS; i++)
  {
    otfdec_region = XSPI_OTFDEC_GET_REGION_INSTANCE(otfdec_instance, (hal_xspi_otfdec_region_t)i);
    OTFDEC_StopRegionDecryption(otfdec_region);
    hxspi->region_state[i] = HAL_XSPI_OTFDEC_REGION_STATE_RESET;
  }
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */

  hxspi->global_state = HAL_XSPI_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup XSPI_Exported_Functions_Group2
  * @{
This subsection provides a set of functions allowing to configure the XSPIx peripheral:

There are 3 categories of HAL configuration APIs

- Global configuration APIs:
  - HAL_XSPI_SetConfig()  Allowing to set the HAL peripheral instance into a ready to use state (idle)
  according to the user parameters
  - HAL_XSPI_GetConfig()  Allowing to retrieve the HAL peripheral configuration
- Unitary configuration APIs:
  - HAL_XSPI_SetFifoThreshold()          Allowing to configure the Fifo threshold according to the user parameters
  - HAL_XSPI_GetFifoThreshold()          Allowing to retrieve the Fifo threshold configuration
  - HAL_XSPI_SetPrescaler()              Allowing to configure the Prescaler according to the user parameters
  - HAL_XSPI_GetPrescaler()              Allowing to retrieve the Prescaler configuration
  - HAL_XSPI_SetMemorySize()             Allowing to configure the Size of XSPI memory according to the user parameters
  - HAL_XSPI_GetMemorySize()             Allowing to retrieve the Size of XSPI memory configuration
  - HAL_XSPI_SetMemoryType()             Allowing to configure the Type of XSPI memory according to the user parameters
  - HAL_XSPI_GetMemoryType()             Allowing to retrieve the Type of XSPI memory configuration
  - HAL_XSPI_EnableFreeRunningClock()    Allowing to enable the free running clock
  - HAL_XSPI_DisableFreeRunningClock()   Allowing to disable the free running clock
  - HAL_XSPI_IsEnabledFreeRunningClock() Allowing to check the state of free running clock, whether it is enable or not
  - HAL_XSPI_EnableSIOO()                Allowing to enable the Send Instruction Only Once mode
  - HAL_XSPI_DisableSIOO()               Allowing to disable the Send Instruction Only Once mode
  - HAL_XSPI_IsEnabledSIOO()             Allowing to check the state of Send Instruction Only Once mode

These APIs are intended to dynamically modify/Retrieve a unitary item meaning that a global config has been already
applied
Unitary config APIs must check first if we are in IDLE state (meaning a global config was applied)
in order to modify or retrieve a single item
Items that can alter other config parameters must not be handled within unitary APIs
  */

/**
  * @brief  Configure the XSPI according to the user parameters.
  * @param  hxspi             Pointer to a hal_xspi_handle_t.
  * @param  p_config          Pointer to the hal_xspi_config_t structure.
  * @retval HAL_ERROR         XSPI instance is already configured and can not be modified.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            XSPI instance has been correctly configured.
  */
hal_status_t HAL_XSPI_SetConfig(hal_xspi_handle_t *hxspi, const hal_xspi_config_t *p_config)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_MEMORY_MODE(p_config->memory.mode));
  ASSERT_DBG_PARAM(IS_XSPI_MEMORY_TYPE(p_config->memory.type));
  ASSERT_DBG_PARAM(IS_XSPI_MEMORY_SIZE(p_config->memory.size_bit));
  ASSERT_DBG_PARAM(IS_XSPI_CLOCK_POLARITY(p_config->memory.clock_polarity));
  ASSERT_DBG_PARAM(IS_XSPI_WRAP_SIZE(p_config->memory.wrap_size_byte));
  ASSERT_DBG_PARAM(IS_XSPI_CS_BOUNDARY(p_config->memory.cs_boundary));
  ASSERT_DBG_PARAM(IS_XSPI_CS_HIGH_TIME_CYCLE(p_config->timing.cs_high_time_cycle));
  ASSERT_DBG_PARAM(IS_XSPI_CLOCK_PRESCALER(p_config->timing.clk_prescaler));
  ASSERT_DBG_PARAM(IS_XSPI_SAMPLE_SHIFT(p_config->timing.shift));
  ASSERT_DBG_PARAM(IS_XSPI_DELAY_HOLD(p_config->timing.hold));
  ASSERT_DBG_PARAM(IS_XSPI_DLYB_BYPASS(p_config->timing.dlyb_state));
  ASSERT_DBG_PARAM(IS_XSPI_MAXTRAN(p_config->timing.cs_release_time_cycle));
#if defined(USE_HAL_XSPI_HYPERBUS) && (USE_HAL_XSPI_HYPERBUS == 1)
  if (hxspi->type == HAL_XSPI_MEMORY_TYPE_HYPERBUS)
  {
    ASSERT_DBG_PARAM(IS_XSPI_WRITE_ZERO_LATENCY(p_config->hyperbus.write_zero_latency));
    ASSERT_DBG_PARAM(IS_XSPI_RW_RECOVERY_TIME_CYCLE(p_config->hyperbus.rw_recovery_time_cycle));
    ASSERT_DBG_PARAM(IS_XSPI_ACCESS_TIME_CYCLE(p_config->hyperbus.access_time_cycle));
    ASSERT_DBG_PARAM(IS_XSPI_LATENCY_MODE(p_config->hyperbus.latency_mode));
  }
#endif /* USE_HAL_XSPI_HYPERBUS */

  ASSERT_DBG_STATE(hxspi->global_state, (uint32_t)HAL_XSPI_STATE_INIT | (uint32_t)HAL_XSPI_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  CLEAR_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_EN);

  /* Configure memory type, device size, chip select high time cycle, clock mode */
  hxspi->type = p_config->memory.type ;
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->DCR1,
             (XSPI_DCR1_MTYP | XSPI_DCR1_DEVSIZE | XSPI_DCR1_CSHT |
              XSPI_DCR1_CKMODE),
             ((uint32_t)(p_config->memory.type) |
              ((uint32_t)(p_config->memory.size_bit)) |
              (((uint32_t)(p_config->timing.cs_high_time_cycle) - 1U) << XSPI_DCR1_CSHT_Pos) |
              (uint32_t)(p_config->memory.clock_polarity)));

  /* Configure delay block bypass */
  if (IS_XSPI_DLYB_INSTANCE(XSPI_GET_INSTANCE(hxspi)))
  {
    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->DCR1, XSPI_DCR1_DLYBYP, (uint32_t)(p_config->timing.dlyb_state));
  }

  /* Configure wrap size */
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->DCR2, XSPI_DCR2_WRAPSIZE, (uint32_t)(p_config->memory.wrap_size_byte));

  /* Configure chip select boundary */
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->DCR3, XSPI_DCR3_CSBOUND, ((uint32_t)(p_config->memory.cs_boundary)
                                                                 << XSPI_DCR3_CSBOUND_Pos));
#if defined(XSPIM)
  /* Configure maximum transfer */
  if (IS_XSPI_IO_MANAGER_INSTANCE(XSPI_GET_INSTANCE(hxspi)))
  {
    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->DCR3, XSPI_DCR3_MAXTRAN, (p_config->timing.cs_release_time_cycle
                                                                   << XSPI_DCR3_MAXTRAN_Pos));
  }
#endif /* XSPIM */

  /* Configure refresh */
  XSPI_GET_INSTANCE(hxspi)->DCR4 = p_config->timing.cs_refresh_time_cycle;

  /* Configure new fifo threshold */
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FTHRES, 0U);
  hxspi->fifo_threshold = 1U;

  /* Wait till busy flag is reset */
  if (XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY, HAL_XSPI_FLAG_NOT_ACTIVE,
                                     XSPI_TIMEOUT_DEFAULT_VALUE) == HAL_OK)
  {
    /* Configure clock prescaler */
    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->DCR2, XSPI_DCR2_PRESCALER, ((p_config->timing.clk_prescaler)
                                                                     << XSPI_DCR2_PRESCALER_Pos));
#if defined(XSPI_CALFCR_FINE)
    if (IS_XSPI_HSPI_INSTANCE(XSPI_GET_INSTANCE(hxspi)))
    {
      /* The configuration of clock prescaler trigger automatically a calibration process.
      So it is necessary to wait the calibration is complete */
      if (XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY, HAL_XSPI_FLAG_NOT_ACTIVE,
                                         XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        hxspi->global_state = HAL_XSPI_STATE_INIT;

        return HAL_ERROR;
      }
    }
#endif /* XSPI_CALFCR_FINE */

    /* Configure the Memory mode */
    hxspi->mode = p_config->memory.mode ;
    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_DMM, (uint32_t)(p_config->memory.mode));

    /* Configure sample shifting and delay hold quarter cycle */
    hxspi->hold = p_config->timing.hold;
    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->TCR, (XSPI_TCR_SSHIFT | XSPI_TCR_DHQC),
               ((uint32_t)p_config->timing.shift | (uint32_t)p_config->timing.hold));
  }
  else
  {
    hxspi->global_state = HAL_XSPI_STATE_INIT;

    return HAL_ERROR;
  }
#if defined(USE_HAL_XSPI_HYPERBUS) && (USE_HAL_XSPI_HYPERBUS == 1)
  /* Configure Hyperbus Memory */
  if (p_config->memory.type == HAL_XSPI_MEMORY_TYPE_HYPERBUS)
  {
    /* Wait till busy flag is reset */
    if (XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY, HAL_XSPI_FLAG_NOT_ACTIVE,
                                       XSPI_TIMEOUT_DEFAULT_VALUE) == HAL_OK)
    {
      /* Configure Hyperbus configuration Latency register */
      WRITE_REG(XSPI_GET_INSTANCE(hxspi)->HLCR,
                (((uint32_t)(p_config->hyperbus.rw_recovery_time_cycle) << XSPI_HLCR_TRWR_Pos) |
                 ((uint32_t)(p_config->hyperbus.access_time_cycle) << XSPI_HLCR_TACC_Pos)      |
                 (uint32_t)(p_config->hyperbus.write_zero_latency)                             |
                 (uint32_t)(p_config->hyperbus.latency_mode)));
    }
    else
    {
      hxspi->global_state = HAL_XSPI_STATE_INIT;

      return HAL_ERROR;
    }
  }
#endif /* USE_HAL_XSPI_HYPERBUS */

  /* Enable XSPI */
  SET_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_EN);

  hxspi->global_state = HAL_XSPI_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Get the XSPI configuration.
  * @param  hxspi    Pointer to a hal_xspi_handle_t.
  * @param  p_config Pointer to the hal_xspi_config_t structure.
  */
void HAL_XSPI_GetConfig(hal_xspi_handle_t *hxspi, hal_xspi_config_t *p_config)
{
  uint32_t tmp_dcr1_reg;
  uint32_t tmp_dcr2_reg;
  uint32_t tmp_dcr3_reg;
  uint32_t tmp_dcr4_reg;
  uint32_t tmp_tcr_reg;
  uint32_t tmp_cr_reg;
  uint32_t tmp_reg;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  tmp_dcr1_reg = READ_REG(XSPI_GET_INSTANCE(hxspi)->DCR1);
  tmp_dcr2_reg = READ_REG(XSPI_GET_INSTANCE(hxspi)->DCR2);
  tmp_dcr3_reg = READ_REG(XSPI_GET_INSTANCE(hxspi)->DCR3);
  tmp_dcr4_reg = READ_REG(XSPI_GET_INSTANCE(hxspi)->DCR4);
  tmp_cr_reg   = READ_REG(XSPI_GET_INSTANCE(hxspi)->CR) ;
  tmp_tcr_reg  = READ_REG(XSPI_GET_INSTANCE(hxspi)->TCR);

  /* Retrieve the value of chip select boundary */
  tmp_reg = READ_BIT(tmp_dcr3_reg, XSPI_DCR3_CSBOUND) >> XSPI_DCR3_CSBOUND_Pos;
  p_config->memory.cs_boundary = (hal_xspi_cs_boundary_t)tmp_reg;

  /* Retrieve the value of Memory mode */
  tmp_reg = READ_BIT(tmp_cr_reg, XSPI_CR_DMM);
  p_config->memory.mode = (hal_xspi_memory_mode_t)tmp_reg;
  hxspi->mode         = (hal_xspi_memory_mode_t)tmp_reg;

  /* Retrieve the value of Memory type */
  tmp_reg = READ_BIT(tmp_dcr1_reg, XSPI_DCR1_MTYP);
  p_config->memory.type = (hal_xspi_memory_type_t)tmp_reg;
  hxspi->type           = (hal_xspi_memory_type_t)tmp_reg;

  /* Retrieve the value of device size*/
  tmp_reg = READ_BIT(tmp_dcr1_reg, XSPI_DCR1_DEVSIZE);
  p_config->memory.size_bit = (hal_xspi_memory_size_t)tmp_reg;

  /* Retrieve the value of clock mode*/
  tmp_reg = READ_BIT(tmp_dcr1_reg, XSPI_DCR1_CKMODE);
  p_config->memory.clock_polarity = (hal_xspi_clock_polarity_t)tmp_reg;

  /* Retrieve the value of wrap size */
  tmp_reg = READ_BIT(tmp_dcr2_reg, XSPI_DCR2_WRAPSIZE);
  p_config->memory.wrap_size_byte = (hal_xspi_wrap_size_t)tmp_reg;

  /* Retrieve the value of chip select high time */
  tmp_reg = (READ_BIT(tmp_dcr1_reg, XSPI_DCR1_CSHT) >> XSPI_DCR1_CSHT_Pos) + 1U;
  p_config->timing.cs_high_time_cycle = tmp_reg;

  /* Retrieve the value of clock prescaler */
  tmp_reg = READ_BIT(tmp_dcr2_reg, XSPI_DCR2_PRESCALER) >> XSPI_DCR2_PRESCALER_Pos;
  p_config->timing.clk_prescaler = tmp_reg;

  /* Retrieve the value of sample shifting */
  tmp_reg = READ_BIT(tmp_tcr_reg, XSPI_TCR_SSHIFT);
  p_config->timing.shift = (hal_xspi_sample_shift_t)tmp_reg;

  /* Retrieve the value of delay hold quarter cycle */
  tmp_reg = READ_BIT(tmp_tcr_reg, XSPI_TCR_DHQC);
  p_config->timing.hold = (hal_xspi_delay_hold_t)tmp_reg;
  hxspi->hold           = (hal_xspi_delay_hold_t)tmp_reg;

  if (IS_XSPI_DLYB_INSTANCE(XSPI_GET_INSTANCE(hxspi)))
  {
    /* Retrieve the value of delay block bypass */
    tmp_reg = READ_BIT(tmp_dcr1_reg, XSPI_DCR1_DLYBYP);
    p_config->timing.dlyb_state = (hal_xspi_dlyb_state_t)tmp_reg;
  }

#if defined(XSPIM)
  if (IS_XSPI_IO_MANAGER_INSTANCE(XSPI_GET_INSTANCE(hxspi)))
  {
    /* Retrieve the value of maximum transfer */
    tmp_reg = READ_BIT(tmp_dcr3_reg, XSPI_DCR3_MAXTRAN) >> XSPI_DCR3_MAXTRAN_Pos;
    p_config->timing.cs_release_time_cycle = tmp_reg;
  }

#endif /* XSPIM */
  /* Retrieve the value of refresh */
  tmp_reg = READ_BIT(tmp_dcr4_reg, XSPI_DCR4_REFRESH);
  p_config->timing.cs_refresh_time_cycle = tmp_reg;

#if defined(USE_HAL_XSPI_HYPERBUS) && (USE_HAL_XSPI_HYPERBUS == 1)
  uint32_t tmp_HLCR = READ_REG(XSPI_GET_INSTANCE(hxspi)->HLCR);
  /* Retrieve the XSPI hyperbus configuration */
  if (p_config->memory.type == HAL_XSPI_MEMORY_TYPE_HYPERBUS)
  {
    tmp_reg = READ_BIT(tmp_HLCR, XSPI_HLCR_TRWR);
    p_config->hyperbus.rw_recovery_time_cycle = tmp_reg;

    tmp_reg = READ_BIT(tmp_HLCR, XSPI_HLCR_TACC);
    p_config->hyperbus.access_time_cycle = tmp_reg;

    tmp_reg = READ_BIT(tmp_HLCR, XSPI_HLCR_WZL) >> XSPI_HLCR_WZL_Pos;
    p_config->hyperbus.write_zero_latency = (hal_xspi_write_zero_latency_status_t)tmp_reg;

    tmp_reg = READ_BIT(tmp_HLCR, XSPI_HLCR_LM);
    p_config->hyperbus.latency_mode = (hal_xspi_latency_mode_t)tmp_reg;
  }
#endif /* USE_HAL_XSPI_HYPERBUS */
}

/** @brief  Set XSPI Fifo threshold.
  * @param  hxspi     XSPI handle.
  * @param  threshold Threshold of the Fifo can be a value from 0 to 31.
  * @retval HAL_OK    Fifo threshold has been correctly configured.
  */
hal_status_t HAL_XSPI_SetFifoThreshold(hal_xspi_handle_t *hxspi, uint32_t threshold)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_FIFO_THRESHOLD_BYTE(XSPI_GET_INSTANCE(hxspi), threshold));

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  /* Set the XSPI FIFO threshold */
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FTHRES, ((threshold - 1U) << XSPI_CR_FTHRES_Pos));

  hxspi->fifo_threshold = threshold;

  return HAL_OK;
}

/** @brief  Get XSPI Fifo threshold.
  * @param  hxspi     XSPI handle.
  * @return Retrieve the value Fifo threshold.
  */
uint32_t HAL_XSPI_GetFifoThreshold(const hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  /* Get the XSPI FIFO threshold */
  return ((READ_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FTHRES) >> XSPI_CR_FTHRES_Pos) + 1U);
}

/** @brief  Set XSPI Clock Prescaler.
  * @param  hxspi         XSPI handle.
  * @param  clk_prescaler Prescaler generating the external clock can be a value from 0 to 255.
  * @retval HAL_ERROR     An error has occurred.
  * @retval HAL_OK        Clock Prescaler has been correctly configured.
  */
hal_status_t HAL_XSPI_SetPrescaler(hal_xspi_handle_t *hxspi, uint32_t clk_prescaler)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_CLOCK_PRESCALER(clk_prescaler));

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  /* Wait till busy flag is reset */
  if (XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY, HAL_XSPI_FLAG_NOT_ACTIVE,
                                     XSPI_TIMEOUT_DEFAULT_VALUE) == HAL_OK)
  {
    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->DCR2, XSPI_DCR2_PRESCALER,
               (clk_prescaler << XSPI_DCR2_PRESCALER_Pos));

#if defined(XSPI_CALFCR_FINE)
    if (IS_XSPI_HSPI_INSTANCE(XSPI_GET_INSTANCE(hxspi)))
    {
      /* The configuration of clock prescaler trigger automatically a calibration process
      So it is necessary to wait the calibration is complete */
      if (XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY, HAL_XSPI_FLAG_NOT_ACTIVE,
                                         XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        return HAL_ERROR;
      }
    }
#endif /* XSPI_CALFCR_FINE */
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/** @brief  Get XSPI Clock Prescaler.
  * @param  hxspi         XSPI handle.
  * @return Retrieve the value clock prescaler.
  */
uint32_t HAL_XSPI_GetPrescaler(const hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  /* Get the XSPI prescaler */
  return (READ_BIT(XSPI_GET_INSTANCE(hxspi)->DCR2, XSPI_DCR2_PRESCALER) >> XSPI_DCR2_PRESCALER_Pos);
}

/** @brief  Configure device memory size.
  * @param  hxspi  XSPI handle.
  * @param  size   The size of the external device connected to the XSPI.
  * @retval HAL_OK Size has been correctly configured.
  */
hal_status_t HAL_XSPI_SetMemorySize(hal_xspi_handle_t *hxspi, hal_xspi_memory_size_t size)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_MEMORY_SIZE(size));

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  /* Set the XSPI memory size */
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->DCR1, XSPI_DCR1_DEVSIZE, (uint32_t)size);

  return HAL_OK;
}

/** @brief  Get XSPI Memory Size.
  * @param  hxspi XSPI handle.
  * @return Retrieve the value device memory size.
  */
hal_xspi_memory_size_t HAL_XSPI_GetMemorySize(const hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  /* Get the XSPI memory size */
  return ((hal_xspi_memory_size_t)(uint32_t)READ_BIT(XSPI_GET_INSTANCE(hxspi)->DCR1, XSPI_DCR1_DEVSIZE));
}

/** @brief  Set XSPI Memory Type.
  * @param  hxspi  XSPI handle.
  * @param  type   The type of the external device connected to the XSPI.
  * @retval HAL_OK Type has been correctly configured.
  */
hal_status_t HAL_XSPI_SetMemoryType(hal_xspi_handle_t *hxspi, hal_xspi_memory_type_t type)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_MEMORY_TYPE(type));

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  /* Set the XSPI memory type */
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->DCR1, XSPI_DCR1_MTYP, (uint32_t)type);

  hxspi->type = type;

  return HAL_OK;
}

/** @brief  Get XSPI Memory Type.
  * @param  hxspi  XSPI handle.
  * @return Retrieve the type of the external device connected to the XSPI.
  */
hal_xspi_memory_type_t HAL_XSPI_GetMemoryType(const hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  /* Get the XSPI memory type */
  return (hxspi->type);
}

/** @brief  Enable the free running clock.
  * @param  hxspi  XSPI handle.
  * @retval HAL_OK free running clock has been correctly enabled.
  */
hal_status_t HAL_XSPI_EnableFreeRunningClock(hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  /* Enable the free running clock */
  SET_BIT(XSPI_GET_INSTANCE(hxspi)->DCR1, XSPI_DCR1_FRCK);

  return HAL_OK;
}

/** @brief  Disable the free running clock.
  * @param  hxspi  XSPI handle.
  * @retval HAL_OK free running clock has been correctly disabled.
  */
hal_status_t HAL_XSPI_DisableFreeRunningClock(hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  /* Disable the free running clock */
  CLEAR_BIT(XSPI_GET_INSTANCE(hxspi)->DCR1, XSPI_DCR1_FRCK);

  return HAL_OK;
}

/** @brief  Check whether the free running clock is enabled or disabled.
  * @param  hxspi XSPI handle.
  * @return Retrieve the state of the free running clock.
  */
hal_xspi_free_running_clk_status_t HAL_XSPI_IsEnabledFreeRunningClock(const hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  /* Get the free running clock */
  return ((READ_BIT((XSPI_GET_INSTANCE(hxspi))->DCR1, XSPI_DCR1_FRCK) == 0UL) ? HAL_XSPI_FREE_RUNNING_CLK_DISABLED
          : HAL_XSPI_FREE_RUNNING_CLK_ENABLED);
}

/** @brief  Enable the Send Instruction Only Once mode.
  * @param  hxspi  XSPI handle.
  * @retval HAL_OK Send Instruction Only Once mode has been correctly enabled.
  */
hal_status_t HAL_XSPI_EnableSIOO(hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  /* Enable the Send Instruction Only Once mode */
  SET_BIT(XSPI_GET_INSTANCE(hxspi)->CCR, XSPI_CCR_SIOO);

  return HAL_OK;
}
/** @brief  Disable the Send Instruction Only Once mode.
  * @param  hxspi  XSPI handle.
  * @retval HAL_OK Send Instruction Only Once mode has been correctly disabled.
  */
hal_status_t HAL_XSPI_DisableSIOO(hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  /* Disable the Send Instruction Only Once mode */
  CLEAR_BIT(XSPI_GET_INSTANCE(hxspi)->CCR, XSPI_CCR_SIOO);

  return HAL_OK;
}
/** @brief  Check whether the Send Instruction Only Once mode is enabled or disabled.
  * @param  hxspi XSPI handle.
  * @return Retrieve the state of the Send Instruction Only Once mode.
  */
hal_xspi_sioo_status_t HAL_XSPI_IsEnabledSIOO(const hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, (uint32_t)HAL_XSPI_STATE_IDLE | (uint32_t)HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE);

  /* Get the Send Instruction Only Once mode */
  return ((READ_BIT((XSPI_GET_INSTANCE(hxspi))->CCR, XSPI_CCR_SIOO) == 0UL) ? HAL_XSPI_SIOO_DISABLED
          : HAL_XSPI_SIOO_ENABLED);
}

/**
  * @}
  */

/** @addtogroup XSPI_Exported_Functions_Group3
  * @{

This subsection provides a set of functions allowing to manage the data
  transfer from/to external memory

- HAL_XSPI_StartMemoryMappedMode() Allowing to start a XSPI Memory-Mapped mode according to the user parameters
- HAL_XSPI_StopMemoryMappedMode() Allowing to stop a XSPI Memory-Mapped mode

There are 3 categories of HAL functions APIs to manage the data transfer

- Blocking mode: Polling
  - HAL_XSPI_SendRegularCmd()
  - HAL_XSPI_SendHyperbusCmd()
  - HAL_XSPI_ExecRegularAutoPoll()
  - HAL_XSPI_Transmit()
  - HAL_XSPI_Receive()
  - HAL_XSPI_Abort()

- Non-Blocking mode: IT
 - HAL_XSPI_SendRegularCmd_IT()
 - HAL_XSPI_ExecRegularAutoPoll_IT()
 - HAL_XSPI_Transmit_IT()
 - HAL_XSPI_Receive_IT()
 - HAL_XSPI_Abort_IT()

- Non-Blocking mode: DMA
 - HAL_XSPI_Transmit_DMA()
 - HAL_XSPI_Receive_DMA()
 - HAL_XSPI_Transmit_DMA_Opt()
 - HAL_XSPI_Receive_DMA_Opt()
  */

/**
  * @brief  Start the Memory Mapped mode.
  * @param  hxspi             XSPI handle.
  * @param  p_config          Pointer to structure that contains the memory mapped configuration information.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_BUSY          XSPI state is active when calling this API.
  * @retval HAL_OK            XSPI instance has been correctly configured.
  */
hal_status_t HAL_XSPI_StartMemoryMappedMode(hal_xspi_handle_t *hxspi, const hal_xspi_memory_mapped_config_t *p_config)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_TIMEOUT_ACTIVATION(p_config->timeout_activation));
  ASSERT_DBG_PARAM(IS_XSPI_TIMEOUT_PERIOD(p_config->timeout_period_cycle));

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_IDLE, HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE);

  /* Start the memory mapped mode */
  /* Wait till busy flag is reset */
  if (XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY, HAL_XSPI_FLAG_NOT_ACTIVE,
                                     XSPI_TIMEOUT_DEFAULT_VALUE) == HAL_OK)
  {
    if (p_config->timeout_activation == HAL_XSPI_TIMEOUT_ENABLE)
    {
      /* Configure LPTR register */
      WRITE_REG(XSPI_GET_INSTANCE(hxspi)->LPTR, p_config->timeout_period_cycle);

      /* Clear Timeout flag */
      HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TO);

      /* Enable interrupt on the timeout flag */
      HAL_XSPI_EnableIT(hxspi, (uint32_t)HAL_XSPI_IT_TO);
    }
    /* Set functional mode as memory-mapped */
    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, (XSPI_CR_TCEN | XSPI_CR_FMODE),
               ((uint32_t)p_config->timeout_activation | XSPI_FUNCTIONAL_MODE_MEMORY_MAPPED));
  }
  else
  {
    hxspi->global_state = HAL_XSPI_STATE_IDLE;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Stop the Memory Mapped mode.
  * @param  hxspi     XSPI handle.
  * @note   This function is used only in Memory mapped Mode.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    XSPI instance has been correctly configured.
  */
hal_status_t HAL_XSPI_StopMemoryMappedMode(hal_xspi_handle_t *hxspi)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE);

  /* Abort the current XSPI operation if exist */
  status = XSPI_Abort(hxspi, XSPI_TIMEOUT_DEFAULT_VALUE);

  if (status == HAL_OK)
  {
    hxspi->global_state = HAL_XSPI_STATE_IDLE;
  }
  else
  {
    status = HAL_ERROR;
  }

  return status;
}
/**
  * @brief  Set the Regular command configuration.
  * @param  hxspi       XSPI handle.
  * @param  p_cmd       Structure that contains the Regular command configuration information.
  * @param  timeout_ms  Timeout duration.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_TIMEOUT In case of user timeout.
  * @retval HAL_BUSY    XSPI state is active when calling this API.
  * @retval HAL_OK      Operation completed.
  */
hal_status_t HAL_XSPI_SendRegularCmd(hal_xspi_handle_t *hxspi,
                                     const hal_xspi_regular_cmd_t *p_cmd,
                                     uint32_t timeout_ms)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_cmd != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OPERATION_TYPE(p_cmd->operation_type));
  ASSERT_DBG_PARAM(IS_XSPI_IO_SELECT(XSPI_GET_INSTANCE(hxspi), p_cmd->io_select));
  ASSERT_DBG_PARAM(IS_XSPI_INSTRUCTION_MODE(p_cmd->instruction_mode));
  ASSERT_DBG_PARAM(IS_XSPI_INSTRUCTION_WIDTH(p_cmd->instruction_width));
  ASSERT_DBG_PARAM(IS_XSPI_INSTRUCTION_DTR_MODE(p_cmd->instruction_dtr_mode_status));
  ASSERT_DBG_PARAM(IS_XSPI_ADDR_MODE(p_cmd->addr_mode));
  ASSERT_DBG_PARAM(IS_XSPI_ADDR_WIDTH(p_cmd->addr_width));
  ASSERT_DBG_PARAM(IS_XSPI_ADDR_DTR_MODE(p_cmd->addr_dtr_mode_status));
  ASSERT_DBG_PARAM(IS_XSPI_ALTERNATE_BYTES_MODE(p_cmd->alternate_bytes_mode));
  ASSERT_DBG_PARAM(IS_XSPI_ALTERNATE_BYTES_WIDTH(p_cmd->alternate_bytes_width));
  ASSERT_DBG_PARAM(IS_XSPI_ALTERNATE_BYTES_DTR_MODE(p_cmd->alternate_bytes_dtr_mode_status));
  ASSERT_DBG_PARAM(IS_XSPI_REGULAR_DATA_MODE(XSPI_GET_INSTANCE(hxspi), p_cmd->data_mode));
  ASSERT_DBG_PARAM(IS_XSPI_DATA_DTR_MODE(p_cmd->data_dtr_mode_status));
  ASSERT_DBG_PARAM(IS_XSPI_DUMMY_CYCLES(p_cmd->dummy_cycle));
  ASSERT_DBG_PARAM(IS_XSPI_DQS_MODE(p_cmd->dqs_mode_status));

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_cmd == NULL) || (hxspi->type == HAL_XSPI_MEMORY_TYPE_HYPERBUS))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check Data Length only if data are inside command */
  if (p_cmd->data_mode != HAL_XSPI_REGULAR_DATA_NONE)
  {
    ASSERT_DBG_PARAM(IS_XSPI_DATA_LENGTH(p_cmd->size_byte));
  }

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_IDLE, HAL_XSPI_STATE_CMD_ACTIVE);

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  hxspi->last_error_codes = HAL_XSPI_ERROR_NONE;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  /* Send regular command in blocking mode */
  status = XSPI_SendRegularCmd(hxspi, p_cmd, timeout_ms, XSPI_INTERRUPT_DISABLE);

  hxspi->global_state = HAL_XSPI_STATE_IDLE;

  return status;
}

/**
  * @brief  Set the Regular command configuration in interrupt mode.
  * @param  hxspi             XSPI handle.
  * @param  p_cmd             Structure that contains the Regular command configuration information.
  * @note   This function is used only in Indirect Read or Write Modes.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_BUSY          XSPI state is active when calling this API.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_XSPI_SendRegularCmd_IT(hal_xspi_handle_t *hxspi, const hal_xspi_regular_cmd_t *p_cmd)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_cmd != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OPERATION_TYPE(p_cmd->operation_type));
  ASSERT_DBG_PARAM(IS_XSPI_IO_SELECT(XSPI_GET_INSTANCE(hxspi), p_cmd->io_select));
  ASSERT_DBG_PARAM(IS_XSPI_INSTRUCTION_MODE(p_cmd->instruction_mode));
  ASSERT_DBG_PARAM(IS_XSPI_INSTRUCTION_WIDTH(p_cmd->instruction_width));
  ASSERT_DBG_PARAM(IS_XSPI_INSTRUCTION_DTR_MODE(p_cmd->instruction_dtr_mode_status));
  ASSERT_DBG_PARAM(IS_XSPI_ADDR_MODE(p_cmd->addr_mode));
  ASSERT_DBG_PARAM(IS_XSPI_ADDR_WIDTH(p_cmd->addr_width));
  ASSERT_DBG_PARAM(IS_XSPI_ADDR_DTR_MODE(p_cmd->addr_dtr_mode_status));
  ASSERT_DBG_PARAM(IS_XSPI_ALTERNATE_BYTES_MODE(p_cmd->alternate_bytes_mode));
  ASSERT_DBG_PARAM(IS_XSPI_ALTERNATE_BYTES_WIDTH(p_cmd->alternate_bytes_width));
  ASSERT_DBG_PARAM(IS_XSPI_ALTERNATE_BYTES_DTR_MODE(p_cmd->alternate_bytes_dtr_mode_status));
  ASSERT_DBG_PARAM(IS_XSPI_REGULAR_DATA_MODE(XSPI_GET_INSTANCE(hxspi), p_cmd->data_mode));
  ASSERT_DBG_PARAM(IS_XSPI_DATA_LENGTH(p_cmd->size_byte));
  ASSERT_DBG_PARAM(IS_XSPI_DATA_DTR_MODE(p_cmd->data_dtr_mode_status));
  ASSERT_DBG_PARAM(IS_XSPI_DUMMY_CYCLES(p_cmd->dummy_cycle));
  ASSERT_DBG_PARAM(IS_XSPI_DQS_MODE(p_cmd->dqs_mode_status));

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_cmd == NULL)
      || (hxspi->type == HAL_XSPI_MEMORY_TYPE_HYPERBUS)
      || (p_cmd->data_mode != HAL_XSPI_REGULAR_DATA_NONE)
      || (p_cmd->operation_type != HAL_XSPI_OPERATION_COMMON_CFG))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_IDLE, HAL_XSPI_STATE_CMD_ACTIVE);

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  hxspi->last_error_codes = HAL_XSPI_ERROR_NONE;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  /* Send regular command in non-blocking mode */
  if (XSPI_SendRegularCmd(hxspi, p_cmd, XSPI_TIMEOUT_DEFAULT_VALUE, XSPI_INTERRUPT_ENABLE) != HAL_OK)
  {
    hxspi->global_state = HAL_XSPI_STATE_IDLE;
    return HAL_ERROR;
  }

  return HAL_OK;
}

#if defined(USE_HAL_XSPI_HYPERBUS) && (USE_HAL_XSPI_HYPERBUS == 1)
/**
  * @brief  Set the Hyperbus command configuration.
  * @param  hxspi             XSPI handle.
  * @param  p_cmd             Structure containing the Hyperbus command.
  * @param  timeout_ms        Timeout duration.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_TIMEOUT       In case of user timeout.
  * @retval HAL_BUSY          XSPI state is active when calling this API.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_XSPI_SendHyperbusCmd(hal_xspi_handle_t *hxspi,
                                      const hal_xspi_hyperbus_cmd_t *p_cmd,
                                      uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_cmd != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_DATA_LENGTH(p_cmd->size_byte));
  ASSERT_DBG_PARAM(IS_XSPI_ADDRESS_SPACE(p_cmd->addr_space));
  ASSERT_DBG_PARAM(IS_XSPI_ADDR_WIDTH(p_cmd->addr_width));
  ASSERT_DBG_PARAM(IS_XSPI_DQS_MODE(p_cmd->dqs_mode_status));
  ASSERT_DBG_PARAM(IS_XSPI_HYPERBUS_DATA_MODE(XSPI_GET_INSTANCE(hxspi), p_cmd->data_mode));

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_cmd == NULL) || (hxspi->type != HAL_XSPI_MEMORY_TYPE_HYPERBUS))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_IDLE, HAL_XSPI_STATE_CMD_ACTIVE);

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  hxspi->last_error_codes = HAL_XSPI_ERROR_NONE;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  /* Send hyperbus command in blocking mode */
  /* Wait till busy flag is reset */
  if (XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY, HAL_XSPI_FLAG_NOT_ACTIVE,
                                     timeout_ms) == HAL_OK)
  {
    /* Re-initialize the value of the functional mode */
    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FMODE, 0U);

    /* Configure the address space */
    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->DCR1,  XSPI_DCR1_MTYP_0, (uint32_t)p_cmd->addr_space);

    /* Set the following configurations :
    - address size
    - DQS signal enabled (used as RWDS)
    - DTR mode enabled on address and data
    - address and data */
    WRITE_REG(XSPI_GET_INSTANCE(hxspi)->CCR, ((uint32_t)p_cmd->dqs_mode_status | XSPI_CCR_DDTR |
                                              (uint32_t)p_cmd->data_mode | (uint32_t)p_cmd->addr_width |
                                              XSPI_CCR_ADDTR | XSPI_CCR_ADMODE_2));
    WRITE_REG(XSPI_GET_INSTANCE(hxspi)->WCCR, ((uint32_t)p_cmd->dqs_mode_status | XSPI_WCCR_DDTR |
                                               (uint32_t)p_cmd->data_mode | (uint32_t)p_cmd->addr_width |
                                               XSPI_WCCR_ADDTR | XSPI_WCCR_ADMODE_2));

    /* Configure the number of data */
    WRITE_REG(XSPI_GET_INSTANCE(hxspi)->DLR, (p_cmd->size_byte - 1U));

    /* Configure the address value */
    WRITE_REG(XSPI_GET_INSTANCE(hxspi)->AR, p_cmd->addr);
  }
  else
  {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
    if (HAL_XSPI_IsActiveFlag(hxspi, HAL_XSPI_FLAG_TE) != HAL_XSPI_FLAG_NOT_ACTIVE)
    {
      hxspi->last_error_codes = HAL_XSPI_ERROR_TRANSFER;
    }
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

    return HAL_TIMEOUT;
  }

  hxspi->global_state = HAL_XSPI_STATE_IDLE;

  return HAL_OK;
}
#endif /* USE_HAL_XSPI_HYPERBUS */

/**
  * @brief  Execute the XSPI Automatic Polling Mode in blocking mode.
  * @param  hxspi             XSPI handle.
  * @param  p_config          Pointer to structure that contains the polling configuration information.
  * @param  timeout_ms        Timeout duration.
  * @note   This function is used only in Automatic Polling Mode for Regular protocol.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_TIMEOUT       In case of user timeout.
  * @retval HAL_BUSY          XSPI state is active when calling this API.
  * @retval HAL_OK            Operation completed.
  */

hal_status_t HAL_XSPI_ExecRegularAutoPoll(hal_xspi_handle_t *hxspi,
                                          const hal_xspi_auto_polling_config_t *p_config,
                                          uint32_t timeout_ms)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_STATUS_BYTES_SIZE(XSPI_GET_INSTANCE(hxspi)->DLR + 1U));
  ASSERT_DBG_PARAM(IS_XSPI_MATCH_MODE(p_config->match_mode));
  ASSERT_DBG_PARAM(IS_XSPI_INTERVAL(p_config->interval_cycle));
  ASSERT_DBG_PARAM(IS_XSPI_AUTOMATIC_STOP(p_config->automatic_stop_status));

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_config == NULL)
      || (hxspi->type == HAL_XSPI_MEMORY_TYPE_HYPERBUS)
      || (p_config->automatic_stop_status != HAL_XSPI_AUTOMATIC_STOP_ENABLED))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_IDLE, HAL_XSPI_STATE_AUTO_POLLING_ACTIVE);

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  hxspi->last_error_codes = HAL_XSPI_ERROR_NONE;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  /* Execute regular auto-polling in blocking mode */
  status = XSPI_ExecRegularAutoPoll(hxspi, p_config, timeout_ms, XSPI_INTERRUPT_DISABLE);

  hxspi->global_state = HAL_XSPI_STATE_IDLE;

  return status;
}

/**
  * @brief  Execute the XSPI Automatic Polling Mode in non-blocking mode.
  * @param  hxspi             XSPI handle.
  * @param  p_config          Pointer to structure that contains the polling configuration information
  * @note   This function is used only in Automatic Polling Mode for Regular protocol.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_BUSY          XSPI state is active when calling this API.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_XSPI_ExecRegularAutoPoll_IT(hal_xspi_handle_t *hxspi, const hal_xspi_auto_polling_config_t *p_config)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_STATUS_BYTES_SIZE(XSPI_GET_INSTANCE(hxspi)->DLR + 1U));
  ASSERT_DBG_PARAM(IS_XSPI_MATCH_MODE(p_config->match_mode));
  ASSERT_DBG_PARAM(IS_XSPI_INTERVAL(p_config->interval_cycle));
  ASSERT_DBG_PARAM(IS_XSPI_AUTOMATIC_STOP(p_config->automatic_stop_status));

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_config == NULL) || (hxspi->type == HAL_XSPI_MEMORY_TYPE_HYPERBUS))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_IDLE, HAL_XSPI_STATE_AUTO_POLLING_ACTIVE);

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  hxspi->last_error_codes = HAL_XSPI_ERROR_NONE;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  /* Execute regular auto-polling in non-blocking mode */
  if (XSPI_ExecRegularAutoPoll(hxspi, p_config, XSPI_TIMEOUT_DEFAULT_VALUE,
                               XSPI_INTERRUPT_ENABLE) != HAL_OK)
  {
    hxspi->global_state = HAL_XSPI_STATE_IDLE;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Transmit an amount of data in blocking mode.
  * @param  hxspi             XSPI handle.
  * @param  p_data            Pointer to data buffer.
  * @param  timeout_ms        Timeout duration.
  * @note   This function is used only in Indirect Write Mode.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_TIMEOUT       In case of user timeout.
  * @retval HAL_BUSY          XSPI state is active when calling this API.
  * @retval HAL_OK            Transfer completed.
  */
hal_status_t HAL_XSPI_Transmit(hal_xspi_handle_t *hxspi, const void *p_data, uint32_t timeout_ms)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  volatile uint32_t *p_data_reg = &XSPI_GET_INSTANCE(hxspi)->DR;

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_IDLE, HAL_XSPI_STATE_TX_ACTIVE);

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  hxspi->last_error_codes = HAL_XSPI_ERROR_NONE;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  /* Configure counters and size */
  hxspi->xfer_count = READ_REG(XSPI_GET_INSTANCE(hxspi)->DLR) + 1U;
  hxspi->xfer_size  = hxspi->xfer_count;
  hxspi->p_buffer   = (uint8_t *)((uint32_t)p_data);

  /* Configure the functional mode as indirect write */
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FMODE, XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE);

  /* Repeat for all data */
  do
  {
    /* Wait till fifo threshold flag is set to send data */
    status = XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_FT, HAL_XSPI_FLAG_ACTIVE,
                                            timeout_ms);

    if (status != HAL_OK)
    {
      break;
    }

    *((volatile uint8_t *)p_data_reg) = *hxspi->p_buffer;
    hxspi->p_buffer++;
    hxspi->xfer_count--;

  } while (hxspi->xfer_count > 0U);

  if (status == HAL_OK)
  {
    /* Wait till transfer complete flag is set to go back in idle state */
    status = XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_TC, HAL_XSPI_FLAG_ACTIVE,
                                            timeout_ms);

    if (status == HAL_OK)
    {
      /* Clear transfer complete flag */
      HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TC);
    }
  }

  hxspi->global_state = HAL_XSPI_STATE_IDLE;

  return status;
}

/**
  * @brief  Receive an amount of data in blocking mode.
  * @param  hxspi             XSPI handle.
  * @param  p_data            Pointer to data buffer.
  * @param  timeout_ms        Timeout duration.
  * @note   This function is used only in Indirect Read Mode.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_TIMEOUT       In case of user timeout.
  * @retval HAL_BUSY          XSPI state is active when calling this API.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_XSPI_Receive(hal_xspi_handle_t *hxspi, void *p_data, uint32_t timeout_ms)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

  volatile uint32_t *p_data_reg = &XSPI_GET_INSTANCE(hxspi)->DR;
  uint32_t addr_reg             = XSPI_GET_INSTANCE(hxspi)->AR;
  uint32_t ir_reg               = XSPI_GET_INSTANCE(hxspi)->IR;

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_IDLE, HAL_XSPI_STATE_RX_ACTIVE);

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  hxspi->last_error_codes = HAL_XSPI_ERROR_NONE;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  /* Configure counters and size */
  hxspi->xfer_count = READ_REG(XSPI_GET_INSTANCE(hxspi)->DLR) + 1U;
  hxspi->xfer_size  = hxspi->xfer_count;
  hxspi->p_buffer   = (uint8_t *)((uint32_t)p_data);

  /* Configure the functional mode as indirect read */
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FMODE, XSPI_FUNCTIONAL_MODE_INDIRECT_READ);

  /* Trig the transfer by re-writing address or instruction register */
  if (hxspi->type == HAL_XSPI_MEMORY_TYPE_HYPERBUS)
  {
    WRITE_REG(XSPI_GET_INSTANCE(hxspi)->AR, addr_reg);
  }
  else
  {
    if (READ_BIT(XSPI_GET_INSTANCE(hxspi)->CCR, XSPI_CCR_ADMODE) != (uint32_t)HAL_XSPI_ADDR_NONE)
    {
      WRITE_REG(XSPI_GET_INSTANCE(hxspi)->AR, addr_reg);
    }
    else
    {
      WRITE_REG(XSPI_GET_INSTANCE(hxspi)->IR, ir_reg);
    }
  }

  do
  {
    /* Wait till fifo threshold or transfer complete flags are set to read received data */
    status = XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_FT | (uint32_t)HAL_XSPI_FLAG_TC,
                                            HAL_XSPI_FLAG_ACTIVE,  timeout_ms);
    if (status != HAL_OK)
    {
      break;
    }

    *hxspi->p_buffer = *((volatile uint8_t *)p_data_reg);
    hxspi->p_buffer++;
    hxspi->xfer_count--;

  } while (hxspi->xfer_count > 0U);

  if (status == HAL_OK)
  {
    /* Wait till transfer complete flag is set to go back in idle state */
    status = XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_TC, HAL_XSPI_FLAG_ACTIVE,
                                            timeout_ms);

    if (status == HAL_OK)
    {
      HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TC);
    }
  }

  hxspi->global_state = HAL_XSPI_STATE_IDLE;

  return status;
}

/**
  * @brief  Send an amount of data in non-blocking mode with interrupt.
  * @param  hxspi             XSPI handle.
  * @param  p_data            Pointer to data buffer.
  * @note   This function is used only in Indirect Write Mode.
  * @retval HAL_BUSY          XSPI state is active when calling this API.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Transfer completed.
  */
hal_status_t HAL_XSPI_Transmit_IT(hal_xspi_handle_t *hxspi, const void *p_data)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_IDLE, HAL_XSPI_STATE_TX_ACTIVE);

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  hxspi->last_error_codes = HAL_XSPI_ERROR_NONE;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  /* Store counters and size */
  hxspi->xfer_count = READ_REG(XSPI_GET_INSTANCE(hxspi)->DLR) + 1U;
  hxspi->xfer_size  = hxspi->xfer_count;
  hxspi->p_buffer   = (uint8_t *)((uint32_t)p_data);

  /* Set functional mode as indirect write */
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FMODE, XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE);

  /* Clear flags related to interrupt */
  HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TE | (uint32_t)HAL_XSPI_FLAG_TC);

  /* Enable the transfer complete, fifo threshold and transfer error interrupts */
  HAL_XSPI_EnableIT(hxspi, (uint32_t)HAL_XSPI_IT_TC | (uint32_t)HAL_XSPI_IT_FT | (uint32_t)HAL_XSPI_IT_TE);

  return HAL_OK;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with interrupt.
  * @param  hxspi             XSPI handle.
  * @param  p_data            Pointer to data buffer.
  * @note   This function is used only in Indirect Read Mode.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_BUSY          XSPI state is active when calling this API.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_XSPI_Receive_IT(hal_xspi_handle_t *hxspi, void *p_data)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_IDLE, HAL_XSPI_STATE_RX_ACTIVE);

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  hxspi->last_error_codes = HAL_XSPI_ERROR_NONE;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  uint32_t addr_reg = XSPI_GET_INSTANCE(hxspi)->AR;
  uint32_t ir_reg = XSPI_GET_INSTANCE(hxspi)->IR;

  /* Store counters and size */
  hxspi->xfer_count = READ_REG(XSPI_GET_INSTANCE(hxspi)->DLR) + 1U;
  hxspi->xfer_size  = hxspi->xfer_count;
  hxspi->p_buffer   = (uint8_t *)((uint32_t)p_data);

  /* Set functional mode as indirect read */
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FMODE, XSPI_FUNCTIONAL_MODE_INDIRECT_READ);

  /* Clear flags related to interrupt */
  HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TE | (uint32_t)HAL_XSPI_FLAG_TC);

  /* Enable the transfer complete, fifo threshold and transfer error interrupts */
  HAL_XSPI_EnableIT(hxspi, (uint32_t)HAL_XSPI_IT_TC | (uint32_t)HAL_XSPI_IT_FT | (uint32_t)HAL_XSPI_IT_TE);

  /* Trig the transfer by re-writing address or instruction register */
  if (hxspi->type == HAL_XSPI_MEMORY_TYPE_HYPERBUS)
  {
    WRITE_REG(XSPI_GET_INSTANCE(hxspi)->AR, addr_reg);
  }
  else
  {
    if (READ_BIT(XSPI_GET_INSTANCE(hxspi)->CCR, XSPI_CCR_ADMODE) != (uint32_t)HAL_XSPI_ADDR_NONE)
    {
      WRITE_REG(XSPI_GET_INSTANCE(hxspi)->AR, addr_reg);
    }
    else
    {
      WRITE_REG(XSPI_GET_INSTANCE(hxspi)->IR, ir_reg);
    }
  }

  return HAL_OK;
}

#if defined(USE_HAL_XSPI_DMA) && (USE_HAL_XSPI_DMA == 1)
/**
  * @brief   Send an amount of data in non-blocking mode with DMA.
  * @param   hxspi  XSPI handle.
  * @param   p_data Pointer to data buffer.
  * @note    This function is used only in Indirect Write Mode.
  * @warning If DMA peripheral access is configured as halfword, the number of data and the fifo threshold must be
  *          aligned on halfword.
  * @warning If DMA peripheral access is configured as word, the number
  *          of data and the fifo threshold must be aligned on word.
  * @retval  HAL_ERROR         An error has occurred.
  * @retval  HAL_INVALID_PARAM Invalid parameter.
  * @retval  HAL_BUSY          XSPI state is active when calling this API.
  * @retval  HAL_OK            Operation completed.
  */
hal_status_t HAL_XSPI_Transmit_DMA(hal_xspi_handle_t *hxspi, const void *p_data)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_IDLE, HAL_XSPI_STATE_TX_ACTIVE);

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  hxspi->last_error_codes = HAL_XSPI_ERROR_NONE;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  uint32_t size_byte = XSPI_GET_INSTANCE(hxspi)->DLR + 1U;

  /* Configure counters and size */
  hxspi->xfer_count = size_byte;
  hxspi->xfer_size  = hxspi->xfer_count;
  hxspi->p_buffer   = (uint8_t *)((uint32_t)p_data);

  /* Set functional mode as indirect write */
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FMODE, XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE);

  /* Clear flags related to interrupt */
  HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TE | (uint32_t)HAL_XSPI_FLAG_TC);

  /* Set the DMA transfer complete callback */
  hxspi->p_dma_tx->p_xfer_cplt_cb = XSPI_DMACplt;

  /* Set the DMA Half transfer complete callback */
  hxspi->p_dma_tx->p_xfer_halfcplt_cb = XSPI_DMAHalfCplt;

  /* Set the DMA error callback */
  hxspi->p_dma_tx->p_xfer_error_cb = XSPI_DMAError;

  /* Clear the DMA abort callback */
  hxspi->p_dma_tx->p_xfer_abort_cb = NULL;

  /* Start DMA peripheral */
  if (HAL_DMA_StartPeriphXfer_IT_Opt(hxspi->p_dma_tx,
                                     (uint32_t)p_data,
                                     (uint32_t)&XSPI_GET_INSTANCE(hxspi)->DR,
                                     hxspi->xfer_size,
                                     HAL_DMA_OPT_IT_DEFAULT) == HAL_OK)
  {
    /* Enable the transfer error interrupt */
    HAL_XSPI_EnableIT(hxspi, (uint32_t)HAL_XSPI_IT_TE);

    /* Enable the DMA transfer */
    SET_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_DMAEN);
  }
  else
  {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
    hxspi->last_error_codes = HAL_XSPI_ERROR_DMA;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */
    hxspi->global_state = HAL_XSPI_STATE_IDLE;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief   Send an amount of data with DMA in interrupt mode with optional interrupts.
  * @param   hxspi      XSPI handle.
  * @param   p_data     Pointer to data buffer.
  * @param   interrupts Specifies the DMA optional interrupt to be enable.
  *                     This parameter can be one of @ref XSPI_Optional_Interrupt group.
  * @note    This function is used only in Indirect Write Mode.
  * @warning If DMA peripheral access is configured as halfword, the number of data and the fifo threshold must be
  *          aligned on halfword.
  * @warning If DMA peripheral access is configured as word, the number
  *          of data and the fifo threshold must be aligned on word.
  * @retval  HAL_ERROR         An error has occurred.
  * @retval  HAL_INVALID_PARAM Invalid parameter.
  * @retval  HAL_BUSY          XSPI state is active when calling this API.
  * @retval  HAL_OK            Operation completed.
  */
hal_status_t HAL_XSPI_Transmit_DMA_Opt(hal_xspi_handle_t *hxspi, const void *p_data, uint32_t interrupts)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OPT_IT(interrupts));

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_IDLE, HAL_XSPI_STATE_TX_ACTIVE);

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  hxspi->last_error_codes = HAL_XSPI_ERROR_NONE;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  uint32_t size_byte = XSPI_GET_INSTANCE(hxspi)->DLR + 1U;

  /* Store counters and size */
  hxspi->xfer_count = size_byte;
  hxspi->xfer_size  = hxspi->xfer_count;
  hxspi->p_buffer   = (uint8_t *)((uint32_t)p_data);

  /* Set functional mode as indirect write */
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FMODE, XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE);

  /* Clear flags related to interrupt */
  HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TE | (uint32_t)HAL_XSPI_FLAG_TC);

  /* Set the DMA transfer complete callback */
  hxspi->p_dma_tx->p_xfer_cplt_cb = XSPI_DMACplt;

  if ((interrupts & HAL_XSPI_OPT_IT_HT) != 0U)
  {
    /* Set the DMA Half transfer complete callback */
    hxspi->p_dma_tx->p_xfer_halfcplt_cb = XSPI_DMAHalfCplt;
  }

  /* Set the DMA error callback */
  hxspi->p_dma_tx->p_xfer_error_cb = XSPI_DMAError;

  /* Clear the DMA abort callback */
  hxspi->p_dma_tx->p_xfer_abort_cb = NULL;

  /* Start DMA peripheral */
  if (HAL_DMA_StartPeriphXfer_IT_Opt(hxspi->p_dma_tx,
                                     (uint32_t)p_data,
                                     (uint32_t)&XSPI_GET_INSTANCE(hxspi)->DR,
                                     hxspi->xfer_size,
                                     interrupts) == HAL_OK)
  {
    /* Enable the transfer error interrupt */
    HAL_XSPI_EnableIT(hxspi, (uint32_t)HAL_XSPI_IT_TE);

    /* Enable the DMA transfer */
    SET_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_DMAEN);
  }
  else
  {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
    hxspi->last_error_codes = HAL_XSPI_ERROR_DMA;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */
    hxspi->global_state = HAL_XSPI_STATE_IDLE;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief   Receive an amount of data in non-blocking mode with DMA.
  * @param   hxspi  XSPI handle.
  * @param   p_data Pointer to data buffer.
  * @note    This function is used only in Indirect Read Mode.
  * @warning If DMA peripheral access is configured as halfword, the number
  *          of data and the fifo threshold must be aligned on halfword.
  * @warning If DMA peripheral access is configured as word, the number
  *          of data and the fifo threshold must be aligned on word.
  * @retval  HAL_ERROR         An error has occurred.
  * @retval  HAL_INVALID_PARAM Invalid parameter.
  * @retval  HAL_BUSY          XSPI state is active when calling this API.
  * @retval  HAL_OK            Operation completed.
  */
hal_status_t HAL_XSPI_Receive_DMA(hal_xspi_handle_t *hxspi, void *p_data)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_IDLE, HAL_XSPI_STATE_RX_ACTIVE);

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  hxspi->last_error_codes = HAL_XSPI_ERROR_NONE;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  uint32_t size_byte = XSPI_GET_INSTANCE(hxspi)->DLR + 1U;
  uint32_t addr_reg = XSPI_GET_INSTANCE(hxspi)->AR;
  uint32_t ir_reg = XSPI_GET_INSTANCE(hxspi)->IR;

  /* Set counters and size */
  hxspi->xfer_count = size_byte;
  hxspi->xfer_size  = hxspi->xfer_count;
  hxspi->p_buffer   = (uint8_t *)((uint32_t)p_data);

  /* Set functional mode as indirect read */
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FMODE, XSPI_FUNCTIONAL_MODE_INDIRECT_READ);

  /* Clear flags related to interrupt */
  HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TE | (uint32_t)HAL_XSPI_FLAG_TC);

  /* Set the DMA transfer complete callback */
  hxspi->p_dma_rx->p_xfer_cplt_cb = XSPI_DMACplt;

  /* Set the DMA Half transfer complete callback */
  hxspi->p_dma_rx->p_xfer_halfcplt_cb = XSPI_DMAHalfCplt;

  /* Set the DMA error callback */
  hxspi->p_dma_rx->p_xfer_error_cb = XSPI_DMAError;

  /* Clear the DMA abort callback */
  hxspi->p_dma_rx->p_xfer_abort_cb = NULL;

  /* Start DMA peripheral */
  if (HAL_DMA_StartPeriphXfer_IT_Opt(hxspi->p_dma_rx,
                                     (uint32_t)&XSPI_GET_INSTANCE(hxspi)->DR,
                                     (uint32_t)p_data,
                                     hxspi->xfer_size,
                                     HAL_DMA_OPT_IT_DEFAULT) == HAL_OK)
  {
    /* Enable the transfer error interrupt */
    HAL_XSPI_EnableIT(hxspi, (uint32_t)HAL_XSPI_IT_TE);

    /* Trig the transfer by re-writing address or instruction register */
    if (hxspi->type == HAL_XSPI_MEMORY_TYPE_HYPERBUS)
    {
      WRITE_REG(XSPI_GET_INSTANCE(hxspi)->AR, addr_reg);
    }
    else
    {
      if (READ_BIT(XSPI_GET_INSTANCE(hxspi)->CCR, XSPI_CCR_ADMODE) != (uint32_t)HAL_XSPI_ADDR_NONE)
      {
        WRITE_REG(XSPI_GET_INSTANCE(hxspi)->AR, addr_reg);
      }
      else
      {
        WRITE_REG(XSPI_GET_INSTANCE(hxspi)->IR, ir_reg);
      }
    }

    /* Enable the DMA transfer */
    SET_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_DMAEN);
  }
  else
  {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
    hxspi->last_error_codes = HAL_XSPI_ERROR_DMA;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */
    hxspi->global_state = HAL_XSPI_STATE_IDLE;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief   Receive an amount of data with DMA in interrupt mode with optional interrupts.
  * @param   hxspi      XSPI handle.
  * @param   p_data     Pointer to data buffer.
  * @param   interrupts Specifies the DMA optional interrupt to be enable
  *                     This parameter can be one of @ref XSPI_Optional_Interrupt group.
  * @note    This function is used only in Indirect Read Mode.
  * @warning If DMA peripheral access is configured as halfword, the number
  *          of data and the fifo threshold must be aligned on halfword.
  * @warning If DMA peripheral access is configured as word, the number
  *          of data and the fifo threshold must be aligned on word.
  * @retval  HAL_ERROR         An error has occurred.
  * @retval  HAL_INVALID_PARAM Invalid parameter.
  * @retval  HAL_BUSY          XSPI state is active when calling this API.
  * @retval  HAL_OK            Operation completed.
  */
hal_status_t HAL_XSPI_Receive_DMA_Opt(hal_xspi_handle_t *hxspi, void *p_data, uint32_t interrupts)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OPT_IT(interrupts));

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_IDLE, HAL_XSPI_STATE_RX_ACTIVE);

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  hxspi->last_error_codes = HAL_XSPI_ERROR_NONE;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  uint32_t size_byte = XSPI_GET_INSTANCE(hxspi)->DLR + 1U;
  uint32_t addr_reg = XSPI_GET_INSTANCE(hxspi)->AR;
  uint32_t ir_reg = XSPI_GET_INSTANCE(hxspi)->IR;

  /* Set counters and size */
  hxspi->xfer_count = size_byte;
  hxspi->xfer_size  = hxspi->xfer_count;
  hxspi->p_buffer   = (uint8_t *)((uint32_t)p_data);

  /* Set functional mode as indirect read */
  MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FMODE, XSPI_FUNCTIONAL_MODE_INDIRECT_READ);

  /* Clear flags related to interrupt */
  HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TE | (uint32_t)HAL_XSPI_FLAG_TC);

  /* Set the DMA transfer complete callback */
  hxspi->p_dma_rx->p_xfer_cplt_cb = XSPI_DMACplt;

  if ((interrupts & HAL_XSPI_OPT_IT_HT) != 0U)
  {
    /* Set the DMA Half transfer complete callback */
    hxspi->p_dma_rx->p_xfer_halfcplt_cb = XSPI_DMAHalfCplt;
  }

  /* Set the DMA error callback */
  hxspi->p_dma_rx->p_xfer_error_cb = XSPI_DMAError;

  /* Clear the DMA abort callback */
  hxspi->p_dma_rx->p_xfer_abort_cb = NULL;

  /* Start DMA peripheral */
  if (HAL_DMA_StartPeriphXfer_IT_Opt(hxspi->p_dma_rx,
                                     (uint32_t)&XSPI_GET_INSTANCE(hxspi)->DR,
                                     (uint32_t)p_data,
                                     hxspi->xfer_size,
                                     interrupts) == HAL_OK)
  {
    /* Enable the transfer error interrupt */
    HAL_XSPI_EnableIT(hxspi, (uint32_t)HAL_XSPI_IT_TE);

    /* Trig the transfer by re-writing address or instruction register */
    if (hxspi->type == HAL_XSPI_MEMORY_TYPE_HYPERBUS)
    {
      WRITE_REG(XSPI_GET_INSTANCE(hxspi)->AR, addr_reg);
    }
    else
    {
      if (READ_BIT(XSPI_GET_INSTANCE(hxspi)->CCR, XSPI_CCR_ADMODE) != (uint32_t)HAL_XSPI_ADDR_NONE)
      {
        WRITE_REG(XSPI_GET_INSTANCE(hxspi)->AR, addr_reg);
      }
      else
      {
        WRITE_REG(XSPI_GET_INSTANCE(hxspi)->IR, ir_reg);
      }
    }

    /* Enable the DMA transfer */
    SET_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_DMAEN);
  }
  else
  {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
    hxspi->last_error_codes = HAL_XSPI_ERROR_DMA;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */
    hxspi->global_state = HAL_XSPI_STATE_IDLE;
    return HAL_ERROR;
  }

  return HAL_OK;
}
#endif /* USE_HAL_XSPI_DMA */

/**
  * @brief  Abort the current transmission.
  * @param  hxspi       XSPI handle.
  * @param  timeout_ms  Timeout duration.
  * @retval HAL_TIMEOUT In case of user timeout.
  * @retval HAL_OK      Operation completed.
  */
hal_status_t HAL_XSPI_Abort(hal_xspi_handle_t *hxspi, uint32_t timeout_ms)
{
  hal_status_t status ;

  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state,
                   (uint32_t)HAL_XSPI_STATE_IDLE | (uint32_t)HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE |
                   (uint32_t)HAL_XSPI_STATE_CMD_ACTIVE | (uint32_t)HAL_XSPI_STATE_AUTO_POLLING_ACTIVE |
                   (uint32_t)HAL_XSPI_STATE_TX_ACTIVE | (uint32_t)HAL_XSPI_STATE_RX_ACTIVE);

  hxspi->global_state = HAL_XSPI_STATE_ABORT;

  status = XSPI_Abort(hxspi, timeout_ms);

  /* Return to indirect mode */
  CLEAR_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FMODE);

  hxspi->global_state = HAL_XSPI_STATE_IDLE;

  return status;
}

/**
  * @brief  Abort the current transmission (non-blocking function).
  * @param  hxspi     XSPI handle.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
hal_status_t HAL_XSPI_Abort_IT(hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state,
                   (uint32_t)HAL_XSPI_STATE_IDLE | (uint32_t)HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE |
                   (uint32_t)HAL_XSPI_STATE_CMD_ACTIVE | (uint32_t)HAL_XSPI_STATE_AUTO_POLLING_ACTIVE |
                   (uint32_t)HAL_XSPI_STATE_TX_ACTIVE | (uint32_t)HAL_XSPI_STATE_RX_ACTIVE);

  /* Disable all interrupts */
  HAL_XSPI_DisableIT(hxspi, (uint32_t)HAL_XSPI_IT_ALL);

#if defined(USE_HAL_XSPI_DMA) && (USE_HAL_XSPI_DMA == 1)
  if ((XSPI_GET_INSTANCE(hxspi)->CR & XSPI_CR_DMAEN) != 0U)
  {
    /* Disable the DMA transfer on the XSPI side */
    CLEAR_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_DMAEN);

    if (hxspi->global_state == HAL_XSPI_STATE_TX_ACTIVE)
    {
      hxspi->global_state = HAL_XSPI_STATE_ABORT;

      /* Disable the DMA transmit on the DMA side */
      hxspi->p_dma_tx->p_xfer_abort_cb = XSPI_DMAAbort;
      (void)HAL_DMA_Abort_IT(hxspi->p_dma_tx);
    }
    else if (hxspi->global_state == HAL_XSPI_STATE_RX_ACTIVE)
    {
      hxspi->global_state = HAL_XSPI_STATE_ABORT;

      /* Disable the DMA receive on the DMA side */
      hxspi->p_dma_rx->p_xfer_abort_cb = XSPI_DMAAbort;
      (void)HAL_DMA_Abort_IT(hxspi->p_dma_rx);
    }
    else
    {
      return HAL_OK;
    }
  }
  else
#endif /* USE_HAL_XSPI_DMA */
  {
    if (HAL_XSPI_IsActiveFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY) != HAL_XSPI_FLAG_NOT_ACTIVE)
    {
      hxspi->global_state = HAL_XSPI_STATE_ABORT;

      /* Clear transfer complete flag */
      HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TC);

      /* Enable the transfer complete interrupts */
      HAL_XSPI_EnableIT(hxspi, (uint32_t)HAL_XSPI_IT_TC);

      /* Perform an abort of the XSPI */
      SET_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_ABORT);

      /* Return to indirect mode */
      CLEAR_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FMODE);
    }
    else
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup XSPI_Exported_Functions_Group4
  * @{

This subsection provides a set callback functions allowing to manage the data
  transfer from/to external memory
  */

/**
  * @brief  Handle the XSPI interrupt request.
  * @param  hxspi Pointer to a hal_xspi_handle_t structure that contains the handle information for the specified
            XSPI instance.
  */
void HAL_XSPI_IRQHandler(hal_xspi_handle_t *hxspi)
{
  volatile uint32_t *p_data_reg = &XSPI_GET_INSTANCE(hxspi)->DR;
  uint32_t flag                 = XSPI_GET_INSTANCE(hxspi)->SR;
  uint32_t itsource             = XSPI_GET_INSTANCE(hxspi)->CR;
  hal_xspi_state_t state        = hxspi->global_state;
  uint32_t itactive             = flag & (itsource >> XSPI_CR_TEIE_Pos);
  uint32_t threshold            = hxspi->fifo_threshold;

  /* XSPI fifo threshold interrupt occurred --------------------------------------------------------------------------*/
  if ((itactive & (uint32_t)HAL_XSPI_FLAG_FT) != 0U)
  {
    if (state == HAL_XSPI_STATE_RX_ACTIVE)
    {
      while (threshold > 0U)
      {
        *hxspi->p_buffer = *((volatile uint8_t *)p_data_reg);
        hxspi->p_buffer++;
        hxspi->xfer_count--;
        threshold--;
      }
    }

    if (state == HAL_XSPI_STATE_TX_ACTIVE)
    {
      while (threshold > 0U)
      {
        *((volatile uint8_t *)p_data_reg) = *hxspi->p_buffer;
        hxspi->p_buffer++;
        hxspi->xfer_count--;
        threshold--;
      }
    }

    /* All data have been received or transmitted for the transfer */
    if (hxspi->xfer_count == 0U)
    {
      /* Disable the interrupt on the fifo threshold flag  */
      HAL_XSPI_DisableIT(hxspi, (uint32_t)HAL_XSPI_IT_FT);
    }

#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
    hxspi->p_fifo_threshold_cb(hxspi);
#else
    HAL_XSPI_FifoThresholdCallback(hxspi);
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */
  }

  /* XSPI transfer complete interrupt occurred -----------------------------------------------------------------------*/
  if ((itactive & (uint32_t)HAL_XSPI_FLAG_TC) != 0U)
  {
    /* Clear transfer complete flag */
    HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TC);

    /* Disable the interrupts on the fifo threshold and the transfer complete flags */
    HAL_XSPI_DisableIT(hxspi, (uint32_t)HAL_XSPI_IT_TC | (uint32_t)HAL_XSPI_IT_FT | (uint32_t)HAL_XSPI_IT_TE);

    if (state == HAL_XSPI_STATE_RX_ACTIVE)
    {
      uint32_t Fifo = READ_BIT(XSPI_GET_INSTANCE(hxspi)->SR, XSPI_SR_FLEVEL) >>
                      XSPI_SR_FLEVEL_Pos;
      if ((hxspi->xfer_count > 0U) && (Fifo != 0U))
      {
        while (hxspi->xfer_count != 0U)
        {
          /* Read the last data received in the fifo */
          *hxspi->p_buffer = *((volatile uint8_t *)p_data_reg);
          hxspi->p_buffer++;
          hxspi->xfer_count--;
        }
      }
      hxspi->global_state = HAL_XSPI_STATE_IDLE;

#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
      hxspi->p_rx_cplt_cb(hxspi);
#else
      HAL_XSPI_RxCpltCallback(hxspi);
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */
    }
    else
    {
      if (state == HAL_XSPI_STATE_TX_ACTIVE)
      {
        hxspi->global_state = HAL_XSPI_STATE_IDLE;

#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
        hxspi->p_tx_cplt_cb(hxspi);
#else
        HAL_XSPI_TxCpltCallback(hxspi);
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */
      }

      if (state == HAL_XSPI_STATE_CMD_ACTIVE)
      {
        hxspi->global_state = HAL_XSPI_STATE_IDLE;

#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
        hxspi->p_cmd_cplt_cb(hxspi);
#else
        HAL_XSPI_CmdCpltCallback(hxspi);
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */
      }

      if (state == HAL_XSPI_STATE_ABORT)
      {
        hxspi->global_state = HAL_XSPI_STATE_IDLE;

#if defined(USE_HAL_XSPI_DMA) && (USE_HAL_XSPI_DMA == 1)
        if (hxspi->is_dma_error == 1U)
        {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
          hxspi->last_error_codes |= HAL_XSPI_ERROR_DMA;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

          /* Abort due to an error (eg : DMA error) */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
          hxspi->p_error_cb(hxspi);
#else
          HAL_XSPI_ErrorCallback(hxspi);
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */
        }
        else
#endif /* USE_HAL_XSPI_DMA */
        {
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
          hxspi->p_abort_cplt_cb(hxspi);
#else
          HAL_XSPI_AbortCpltCallback(hxspi);
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */
        }
      }
    }
  }

  /* XSPI status match interrupt occurred ----------------------------------------------------------------------------*/
  if ((itactive & (uint32_t)HAL_XSPI_FLAG_SM) != 0U)
  {
    /* Clear status match flag */
    HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_SM);

    /* Check if automatic poll mode stop is activated */
    if ((XSPI_GET_INSTANCE(hxspi)->CR & XSPI_CR_APMS) != 0U)
    {
      /* Disable the interrupts on the status match and the transfer error flags */
      HAL_XSPI_DisableIT(hxspi, ((uint32_t)HAL_XSPI_IT_SM | (uint32_t)HAL_XSPI_IT_TE));
      hxspi->global_state = HAL_XSPI_STATE_IDLE;
    }

#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
    hxspi->p_status_match_cb(hxspi);
#else
    HAL_XSPI_StatusMatchCallback(hxspi);
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */
  }

  /* XSPI transfer error interrupt occurred --------------------------------------------------------------------------*/
  if ((itactive & (uint32_t)HAL_XSPI_FLAG_TE) != 0U)
  {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
    hxspi->last_error_codes |= HAL_XSPI_ERROR_TRANSFER;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

    /* Clear Transfer error flag */
    HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TE);

    /* Disable all interrupts */
    HAL_XSPI_DisableIT(hxspi, (uint32_t)HAL_XSPI_IT_ALL);

#if defined(USE_HAL_XSPI_DMA) && (USE_HAL_XSPI_DMA == 1)
    if ((XSPI_GET_INSTANCE(hxspi)->CR & XSPI_CR_DMAEN) != 0U)
    {
      /* Disable the DMA transfer on the XSPI side */
      CLEAR_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_DMAEN);

      hxspi->is_dma_error = 1U;

      if (state == HAL_XSPI_STATE_TX_ACTIVE)
      {
        /* Disable the DMA transmit on the DMA side */
        hxspi->p_dma_tx->p_xfer_abort_cb = XSPI_DMAAbortOnError;

        /* Abort the DMA channel */
        (void)HAL_DMA_Abort_IT(hxspi->p_dma_tx);
      }

      if (state == HAL_XSPI_STATE_RX_ACTIVE)
      {
        /* Disable the DMA receive on the DMA side */
        hxspi->p_dma_rx->p_xfer_abort_cb = XSPI_DMAAbortOnError;

        /* Abort the DMA channel */
        (void)HAL_DMA_Abort_IT(hxspi->p_dma_rx);
      }
    }
    else
#endif /* USE_HAL_XSPI_DMA */
    {
      hxspi->global_state = HAL_XSPI_STATE_IDLE;

#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
      hxspi->p_error_cb(hxspi);
#else
      HAL_XSPI_ErrorCallback(hxspi);
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */
    }
  }

  /* XSPI timeout interrupt occurred ---------------------------------------------------------------------------------*/
  if ((itactive & (uint32_t)HAL_XSPI_FLAG_TO) != 0U)
  {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
    hxspi->last_error_codes |= HAL_XSPI_ERROR_TIMEOUT;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

    /* Clear timeout flag */
    HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TO);

#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
    hxspi->p_error_cb(hxspi);
#else
    HAL_XSPI_ErrorCallback(hxspi);
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */
  }
}

/**
  * @brief Error callback.
  * @param hxspi XSPI handle.

  */
__WEAK void HAL_XSPI_ErrorCallback(hal_xspi_handle_t *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hxspi);
  /* NOTE : This function must not be modified, when the callback is needed,
  the HAL_XSPI_ErrorCallback could be implemented in the user file
  */
}

/**
  * @brief Abort completed callback.
  * @param hxspi XSPI handle.

  */
__WEAK void HAL_XSPI_AbortCpltCallback(hal_xspi_handle_t *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hxspi);

  /* NOTE: This function must not be modified, when the callback is needed,
  the HAL_XSPI_AbortCpltCallback could be implemented in the user file
  */
}

/**
  * @brief FIFO Threshold callback.
  * @param hxspi XSPI handle.

  */
__WEAK void HAL_XSPI_FifoThresholdCallback(hal_xspi_handle_t *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hxspi);

  /* NOTE : This function must not be modified, when the callback is needed,
  the HAL_XSPI_FIFOThresholdCallback could be implemented in the user file
  */
}

/**
  * @brief Command completed callback.
  * @param hxspi XSPI handle.

  */
__WEAK void HAL_XSPI_CmdCpltCallback(hal_xspi_handle_t *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hxspi);

  /* NOTE: This function must not be modified, when the callback is needed,
  the HAL_XSPI_CmdCpltCallback could be implemented in the user file
  */
}

/**
  * @brief Rx Transfer completed callback.
  * @param hxspi XSPI handle.

  */
__WEAK void HAL_XSPI_RxCpltCallback(hal_xspi_handle_t *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hxspi);

  /* NOTE: This function must not be modified, when the callback is needed,
  the HAL_XSPI_RxCpltCallback could be implemented in the user file
  */
}

/**
  * @brief Tx Transfer completed callback.
  * @param hxspi XSPI handle.

  */
__WEAK void HAL_XSPI_TxCpltCallback(hal_xspi_handle_t *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hxspi);

  /* NOTE: This function must not be modified, when the callback is needed,
  the HAL_XSPI_TxCpltCallback could be implemented in the user file
  */
}

/**
  * @brief Rx Half Transfer completed callback.
  * @param hxspi XSPI handle.

  */
__WEAK void HAL_XSPI_RxHalfCpltCallback(hal_xspi_handle_t *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hxspi);

  /* NOTE: This function must not be modified, when the callback is needed,
  the HAL_XSPI_RxHalfCpltCallback could be implemented in the user file
  */
}

/**
  * @brief Tx Half Transfer completed callback.
  * @param hxspi XSPI handle.

  */
__WEAK void HAL_XSPI_TxHalfCpltCallback(hal_xspi_handle_t *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hxspi);

  /* NOTE: This function must not be modified, when the callback is needed,
  the HAL_XSPI_TxHalfCpltCallback could be implemented in the user file
  */
}

/**
  * @brief Status Match callback.
  * @param hxspi XSPI handle.

  */
__WEAK void HAL_XSPI_StatusMatchCallback(hal_xspi_handle_t *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hxspi);

  /* NOTE : This function must not be modified, when the callback is needed,
  the HAL_XSPI_StatusMatchCallback could be implemented in the user file
  */
}

#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register the XSPI Error Callback to be used instead of
  *         the weak HAL_XSPI_ErrorCallback() predefined callback.
  * @param  hxspi             Pointer to a hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  callback          Specifies the error callback.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_XSPI_RegisterErrorCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t callback)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Store the callback function within handle */
  hxspi->p_error_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Register the XSPI command complete Callback TO be used instead of
  *         the weak HAL_XSPI_CmdCpltCallback() predefined callback.
  * @param  hxspi             Pointer to a hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  callback          Specifies the command complete callback.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_XSPI_RegisterCmdCpltCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t  callback)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Store the callback function within handle */
  hxspi->p_cmd_cplt_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Register the XSPI Receive complete Callback TO be used instead of
  *         the weak HAL_XSPI_RxCpltCallback() predefined callback.
  * @param  hxspi             Pointer to a hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  callback          Specifies the receive complete callback.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_XSPI_RegisterRxCpltCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t  callback)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Store the callback function within handle */
  hxspi->p_rx_cplt_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Register the XSPI Transfer complete Callback TO be used instead of
  *         the weak HAL_XSPI_TxCpltCallback() predefined callback.
  * @param  hxspi             Pointer to a hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  callback          Specifies the transfer complete callback.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_XSPI_RegisterTxCpltCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t  callback)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Store the callback function within handle */
  hxspi->p_tx_cplt_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Register the XSPI Receive Half complete Callback TO be used instead of
  *         the weak HAL_XSPI_RxHalfCpltCallback() predefined callback.
  * @param  hxspi             Pointer to a hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  callback          Specifies the half receive complete callback.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_XSPI_RegisterRxHalfCpltCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t  callback)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Store the callback function within handle */
  hxspi->p_rx_half_cplt_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Register the XSPI Transfer Half complete Callback TO be used instead of
  *         the weak HAL_XSPI_TxHalfCpltCallback() predefined callback.
  * @param  hxspi             Pointer to a hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  callback          Specifies the half transfer complete callback.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_XSPI_RegisterTxHalfCpltCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t  callback)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Store the callback function within handle */
  hxspi->p_tx_half_cplt_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Register the XSPI Status Match Callback TO be used instead of
  *         the weak HAL_XSPI_StatusMatchCallback() predefined callback.
  * @param  hxspi             Pointer to a hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  callback          Specifies the status match callback.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_XSPI_RegisterStatusMatchCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t  callback)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Store the callback function within handle */
  hxspi->p_status_match_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Register the XSPI Abort complete Callback TO be used instead of
  *         the weak HAL_XSPI_AbortCpltCallback() predefined callback.
  * @param  hxspi             Pointer to a hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  callback          Specifies the abort complete callback.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_XSPI_RegisterAbortCpltCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t  callback)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Store the callback function within handle */
  hxspi->p_abort_cplt_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Register the XSPI Fifo Threshold Callback TO be used instead of
  *         the weak HAL_XSPI_FifoThresholdCallback() predefined callback.
  * @param  hxspi             Pointer to a hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  callback          Specifies the fifo threshold complete callback.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_XSPI_RegisterFifoThresholdCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t  callback)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Store the callback function within handle */
  hxspi->p_fifo_threshold_cb = callback;

  return HAL_OK;
}
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */

#if defined (USE_HAL_XSPI_USER_DATA) && (USE_HAL_XSPI_USER_DATA == 1)
/**
  * @brief  Store User Data pointer into the handle.
  * @param  hxspi       Pointer to a hal_xspi_handle_t.
  * @param  p_user_data Pointer to the user data.
  */
void HAL_XSPI_SetUserData(hal_xspi_handle_t *hxspi, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  hxspi->p_user_data = p_user_data;
}
/**
  * @brief  Retrieve User Data pointer from the handle.
  * @param  hxspi Pointer to a hal_xspi_handle_t.
  * @return Pointer to the user data.
  */
const void *HAL_XSPI_GetUserData(const hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  return (hxspi->p_user_data);
}
#endif /* USE_HAL_XSPI_USER_DATA == 1 */

#if defined(USE_HAL_XSPI_DMA) && (USE_HAL_XSPI_DMA == 1)
/**
  * @brief  link/store Tx HAL DMA handle into the HAL XSPI handle.
  * @param  hxspi             Pointer to a hal_xspi_handle_t.
  * @param  p_dma_tx          Pointer to a hal_dma_handle_t.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            The DMA Tx handle has been successfully linked and stored in the XSPI handle.
  */
hal_status_t HAL_XSPI_SetTxDMA(hal_xspi_handle_t *hxspi, hal_dma_handle_t *p_dma_tx)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_dma_tx != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, (uint32_t)HAL_XSPI_STATE_INIT | (uint32_t)HAL_XSPI_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_dma_tx == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hxspi->p_dma_tx    = p_dma_tx;
  p_dma_tx->p_parent = hxspi;

  return HAL_OK;
}

/**
  * @brief  link/store Rx HAL DMA handle into the HAL XSPI handle.
  * @param  hxspi             Pointer to a hal_xspi_handle_t.
  * @param  p_dma_rx          Pointer to a hal_dma_handle_t.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            The DMA Rx handle has been successfully linked and stored in the XSPI handle.
  */
hal_status_t HAL_XSPI_SetRxDMA(hal_xspi_handle_t *hxspi, hal_dma_handle_t *p_dma_rx)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_dma_rx != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, (uint32_t)HAL_XSPI_STATE_INIT | (uint32_t)HAL_XSPI_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_dma_rx == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hxspi->p_dma_rx    = p_dma_rx;
  p_dma_rx->p_parent = hxspi;

  return HAL_OK;
}
#endif /* USE_HAL_XSPI_DMA */
/**
  * @}
  */

/** @addtogroup XSPI_Exported_Functions_Group5
  * @{

This subsection provides a set of functions allowing to read peripheral
current frequency, state and last occurred errors.
  */

/** @brief  Return the peripheral clock frequency for XSPI.
  * @param  hxspi Pointer to a hal_xspi_handle_t structure that contains
  *               the configuration information for XSPI module.
  * @retval uint32_t Frequency in Hz.
  * @retval 0 source clock of the hxspi not configured or not ready.
  */
uint32_t HAL_XSPI_GetClockFreq(const hal_xspi_handle_t *hxspi)
{
  /* Check the XSPI handle & config allocation */
  ASSERT_DBG_PARAM((hxspi != NULL));

  /* Check the global state, the driver must be at least configured */
  ASSERT_DBG_STATE(hxspi->global_state, (uint32_t)HAL_XSPI_STATE_INIT | (uint32_t)HAL_XSPI_STATE_IDLE
                   | (uint32_t)HAL_XSPI_STATE_CMD_ACTIVE | (uint32_t)HAL_XSPI_STATE_AUTO_POLLING_ACTIVE
                   | (uint32_t)HAL_XSPI_STATE_TX_ACTIVE | (uint32_t)HAL_XSPI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE | (uint32_t)HAL_XSPI_STATE_ABORT);

  return HAL_RCC_XSPI_GetKernelClkFreq((XSPI_TypeDef *)((uint32_t)(hxspi->instance)));
}

/**
  * @brief  Retrieve the HAL XSPI Global State.
  * @param  hxspi Pointer to a hal_xspi_handle_t structure that contains
  *               handle information for the specified XSPI instance.
  * @return Retrieve the XSPI global state.
  */
hal_xspi_state_t HAL_XSPI_GetState(const hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  return (hal_xspi_state_t) hxspi->global_state;
}

#if defined (USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
/**
  * @brief  Return the XSPI error code.
  * @param  hxspi XSPI handle
  * @retval XSPI error code
  */
uint32_t HAL_XSPI_GetLastErrorCodes(const hal_xspi_handle_t *hxspi)
{
  return hxspi->last_error_codes;
}
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */
/**
  * @}
  */

/** @addtogroup XSPI_Exported_Functions_Group6
  * @{

This subsection provides a set of functions allowing to configure the Delay Block :

- Call the function HAL_XSPI_DLYB_SetConfigDelay() to set the delay configuration of the delay block peripheral
- Call the function HAL_XSPI_DLYB_GetConfigDelay() to get the delay output clock phase of the delay block peripheral
- Call the function HAL_XSPI_DLYB_CalculateMaxClockPhase() to calculate the maximum output clock phase of the
  delay block peripheral
- Call the function HAL_XSPI_DLYB_Enable() to enable the delay block peripheral
- Call the function HAL_XSPI_DLYB_Disable() to disable the delay block peripheral
- Call the function HAL_XSPI_DLYB_IsEnabled() to check if the delay block peripheral is enabled or not
  */

/**
  * @brief  Set the delay configuration of the delay block peripheral.
  * @param  hxspi             Pointer to XSPI handle.
  * @param  clock_phase_value The desired output clock phase value.
  * @retval HAL_INVALID_PARAM When no valid XSPI.
  * @retval HAL_OK            The delay is correctly configured.
  */
hal_status_t HAL_XSPI_DLYB_SetConfigDelay(hal_xspi_handle_t *hxspi, uint32_t clock_phase_value)
{
  hal_status_t status = HAL_ERROR;
  DLYB_TypeDef *instance;
  dlyb_state_t state;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_DLYB_INSTANCE(XSPI_GET_INSTANCE(hxspi)));
  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (IS_XSPI_DLYB_INSTANCE(XSPI_GET_INSTANCE(hxspi)) == 0U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  instance = XSPI_DLYB_GET_INSTANCE(hxspi->instance);

  state = DLYB_IsEnabled(instance);
  DLYB_Enable(instance);

  /* Enable XSPI Free Running Clock (mandatory) */
  SET_BIT(XSPI_GET_INSTANCE(hxspi)->DCR1, XSPI_DCR1_FRCK);

  if (DLYB_ConfigureUnitDelay(instance) == HAL_OK)
  {
    DLYB_SetOutputClockPhase(instance, clock_phase_value);
    status = HAL_OK;
  }

  (void)XSPI_Abort(hxspi, XSPI_TIMEOUT_DEFAULT_VALUE);

  /* Disable Free Running Clock */
  CLEAR_BIT(XSPI_GET_INSTANCE(hxspi)->DCR1, XSPI_DCR1_FRCK);

  if (state == DLYB_DISABLED)
  {
    DLYB_Disable(instance);
  }

  return status;
}

/**
  * @brief  Get the delay output clock phase of the delay block peripheral.
  * @param  hxspi              Pointer to XSPI handle.
  * @param  p_clock_phase      Pointer to the variable where the selected output clock phase value will be stored.
  * @retval HAL_INVALID_PARAM When no valid XSPI.
  * @retval HAL_OK            When the register reading was successful.
  */
hal_status_t HAL_XSPI_DLYB_GetConfigDelay(const hal_xspi_handle_t *hxspi, uint32_t *p_clock_phase)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_DLYB_INSTANCE(XSPI_GET_INSTANCE(hxspi)));
  ASSERT_DBG_PARAM(p_clock_phase != NULL);
  ASSERT_DBG_STATE(hxspi->global_state,
                   (uint32_t)HAL_XSPI_STATE_IDLE | (uint32_t)HAL_XSPI_STATE_CMD_ACTIVE
                   | (uint32_t)HAL_XSPI_STATE_AUTO_POLLING_ACTIVE | (uint32_t)HAL_XSPI_STATE_TX_ACTIVE
                   | (uint32_t)HAL_XSPI_STATE_RX_ACTIVE | (uint32_t)HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE
                   | (uint32_t)HAL_XSPI_STATE_ABORT);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((IS_XSPI_DLYB_INSTANCE(XSPI_GET_INSTANCE(hxspi)) == 0U) || (p_clock_phase == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  *p_clock_phase = DLYB_GetOutputClockPhase(XSPI_DLYB_GET_INSTANCE(hxspi->instance));

  return HAL_OK;
}

/**
  * @brief  Calculate maximum output clock phase of the delay block peripheral.
  * @param  hxspi             Pointer to XSPI handle.
  * @param  p_max_clock_phase Pointer to the variable where the maximum clock phase value will be stored.
  * @retval HAL_ERROR         The max clock phase is not correctly calculated.
  * @retval HAL_INVALID_PARAM When no valid XSPI or invalid p_max_clock_phase parameter.
  * @retval HAL_OK            The max clock phase is correctly calculated.
 */
hal_status_t HAL_XSPI_DLYB_CalculateMaxClockPhase(hal_xspi_handle_t *hxspi, uint32_t *p_max_clock_phase)
{
  hal_status_t status = HAL_ERROR;
  DLYB_TypeDef *instance;
  uint32_t sel;
  uint32_t unit;
  dlyb_state_t state;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_DLYB_INSTANCE(XSPI_GET_INSTANCE(hxspi)));
  ASSERT_DBG_PARAM(p_max_clock_phase != NULL);
  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((IS_XSPI_DLYB_INSTANCE(XSPI_GET_INSTANCE(hxspi)) == 0U) || (p_max_clock_phase == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  instance = XSPI_DLYB_GET_INSTANCE(hxspi->instance);

  state = DLYB_IsEnabled(instance);
  DLYB_Enable(instance);

  /* Enable XSPI Free Running Clock (mandatory) */
  SET_BIT(XSPI_GET_INSTANCE(hxspi)->DCR1, XSPI_DCR1_FRCK);

  DLYB_GetConfig(instance, &unit, &sel);

  if (DLYB_ConfigureUnitDelay(instance) == HAL_OK)
  {
    *p_max_clock_phase = DLYB_CalculateMaxOutputClockPhase(instance);
    status = HAL_OK;
  }

  DLYB_SetConfig(instance, unit, sel);

  /* Disable XSPI Free Running Clock */
  CLEAR_BIT(XSPI_GET_INSTANCE(hxspi)->DCR1, XSPI_DCR1_FRCK);

  if (state == DLYB_DISABLED)
  {
    DLYB_Disable(instance);
  }

  return status;
}

/**
  * @brief  Enable the delay block peripheral.
  * @param  hxspi             Pointer to XSPI handle.
  * @retval HAL_ERROR         The delay is not correctly configured.
  * @retval HAL_INVALID_PARAM When no valid XSPI instance.
  * @retval HAL_OK            The delay is correctly configured.
  */
hal_status_t HAL_XSPI_DLYB_Enable(hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_PARAM(IS_XSPI_DLYB_INSTANCE(XSPI_GET_INSTANCE(hxspi)));
  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (IS_XSPI_DLYB_INSTANCE(XSPI_GET_INSTANCE(hxspi)) == 0U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  DLYB_Enable(XSPI_DLYB_GET_INSTANCE(hxspi->instance));

  return HAL_OK;
}

/**
  * @brief  Disable the delay block peripheral.
  * @param  hxspi             Pointer to XSPI handle.
  * @retval HAL_INVALID_PARAM When no valid XSPI instance.
  * @retval HAL_OK            The delay block is disabled.
  */
hal_status_t HAL_XSPI_DLYB_Disable(hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_DLYB_INSTANCE(XSPI_GET_INSTANCE(hxspi)));

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (IS_XSPI_DLYB_INSTANCE(XSPI_GET_INSTANCE(hxspi)) == 0U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  DLYB_Disable(XSPI_DLYB_GET_INSTANCE(hxspi->instance));

  return HAL_OK;
}

/**
  * @brief  Check if the delay block peripheral is enabled or not.
  * @param  hxspi                  Pointer to XSPI handle.
  * @retval HAL_XSPI_DLYB_ENABLED  The delay block is enabled.
  * @retval HAL_XSPI_DLYB_DISABLED The delay block is disabled.
  */
hal_xspi_dlyb_status_t HAL_XSPI_DLYB_IsEnabled(const hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  return (hal_xspi_dlyb_status_t)DLYB_IsEnabled(XSPI_DLYB_GET_INSTANCE(hxspi->instance));
}
/**
  * @}
  */

#if defined(XSPI_CALFCR_FINE)
/** @addtogroup XSPI_Exported_Functions_Group7
  * @{

This subsection provides a set of functions allowing to configure the high-speed interface and calibration :

- Call the function HAL_XSPI_HSIC_SetConfigDelay() to set a delay value for the high-speed interface DLLs
- Call the function HAL_XSPI_HSIC_GetConfigDelay() to get the delay values of the high-speed interface DLLs
    of the selected XSPIx peripheral
  */

/**
  * @brief  Set a delay value for the high-speed interface DLLs.
  * @param  hxspi             Pointer to XSPI handle.
  * @param  p_config          Configuration of delay value specified in DelayValueType field.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK.
  */
hal_status_t HAL_XSPI_HSIC_SetConfigDelay(hal_xspi_handle_t *hxspi, const hal_xspi_hsic_config_t *p_config)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_HSIC_INSTANCE(XSPI_GET_INSTANCE(hxspi)));
  ASSERT_DBG_PARAM(IS_XSPI_HSIC_DELAY_CAL_TYPE(p_config->delay_value_type));
  ASSERT_DBG_PARAM(IS_XSPI_HSIC_FINECAL_VALUE(p_config->fine_cal_unit));
  ASSERT_DBG_PARAM(IS_XSPI_HSIC_COARSECAL_VALUE(p_config->coarse_cal_unit));
  ASSERT_DBG_PARAM(IS_XSPI_HSIC_MAX_CAL(p_config->max_cal));

  ASSERT_DBG_STATE(hxspi->global_state, HAL_XSPI_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((IS_XSPI_HSIC_INSTANCE(XSPI_GET_INSTANCE(hxspi)) == 0U) || (p_config == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (p_config->delay_value_type == HAL_XSPI_HSIC_DELAY_CAL_FEEDBACK_CLK)
  {
    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CALMR, (XSPI_CALMR_COARSE |  XSPI_CALMR_FINE),
               (p_config->fine_cal_unit | (p_config->coarse_cal_unit << XSPI_CALMR_COARSE_Pos)));
  }
  else if (p_config->delay_value_type == HAL_XSPI_HSIC_DELAY_CAL_DATA_OUTPUT)
  {
    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CALSOR, (XSPI_CALSOR_COARSE | XSPI_CALSOR_FINE),
               (p_config->fine_cal_unit | (p_config->coarse_cal_unit << XSPI_CALSOR_COARSE_Pos)));
  }
  else
  {
    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CALSIR, (XSPI_CALSIR_COARSE | XSPI_CALSIR_FINE),
               (p_config->fine_cal_unit | (p_config->coarse_cal_unit << XSPI_CALSIR_COARSE_Pos)));
  }

  return HAL_OK;
}

/**
  * @brief  Get the delay values of the high-speed interface DLLs.
  * @param  hxspi             Pointer to XSPI handle.
  * @param  p_config          Current delay values corresponding to the DelayValueType field.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK.
  */
hal_status_t HAL_XSPI_HSIC_GetConfigDelay(const hal_xspi_handle_t *hxspi,  hal_xspi_hsic_config_t *p_config)
{
  volatile uint32_t reg = 0;
  volatile uint32_t reg1 = 0;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_HSIC_INSTANCE(XSPI_GET_INSTANCE(hxspi)));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((IS_XSPI_HSIC_INSTANCE(XSPI_GET_INSTANCE(hxspi)) == 0U) || (p_config == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (p_config->delay_value_type == HAL_XSPI_HSIC_DELAY_CAL_FULL_CYCLE)
  {
    reg = XSPI_GET_INSTANCE(hxspi)->CALFCR;
    reg1 = (reg & XSPI_CALFCR_CALMAX);
    p_config->max_cal = (hal_xspi_hsic_max_cal_mode_t)reg1;
  }
  else if (p_config->delay_value_type == HAL_XSPI_HSIC_DELAY_CAL_FEEDBACK_CLK)
  {
    reg = XSPI_GET_INSTANCE(hxspi)->CALMR;
  }
  else if (p_config->delay_value_type == HAL_XSPI_HSIC_DELAY_CAL_DATA_OUTPUT)
  {
    reg = XSPI_GET_INSTANCE(hxspi)->CALSOR;
  }
  else
  {
    reg = XSPI_GET_INSTANCE(hxspi)->CALSIR;
  }

  p_config->fine_cal_unit   = (reg & XSPI_CALFCR_FINE);
  p_config->coarse_cal_unit = ((reg & XSPI_CALFCR_COARSE) >> XSPI_CALFCR_COARSE_Pos);

  return HAL_OK;
}
/**
  * @}
  */
#endif /* XSPI_CALFCR_FINE */

#if defined(XSPIM)
/** @addtogroup XSPI_Exported_Functions_Group8
  * @{

This subsection provides a set of functions allowing to configure the XSPIM IO Manager :

- IO manager (XSPIM) configuration APIs:
  - HAL_XSPI_XSPIM_SetConfig()   Allowing to configure a XSPIM according to the user parameters
  - HAL_XSPI_XSPIM_GetConfig()   Allowing to retrieve a XSPIM  configuration
  */

/**
  * @brief  Configure the XSPIM according to the user parameters.
  * @param  p_config          Pointer to the hal_xspi_xspim_config_t structure.
  * @note   XSPIM XSPI I/O Manager Instance.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         XSPI instance is enabled.
  * @retval HAL_OK            XSPIM instance has been correctly configured.
  */
hal_status_t HAL_XSPI_XSPIM_SetConfig(const hal_xspi_xspim_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_XSPIM_REQ2ACKTIME(p_config->req_ack_cycle));
  ASSERT_DBG_PARAM(IS_XSPIM_PORT(p_config->port1.clk));
  ASSERT_DBG_PARAM(IS_XSPIM_PORT(p_config->port1.dqs));
  ASSERT_DBG_PARAM(IS_XSPIM_PORT(p_config->port1.ncs));
  ASSERT_DBG_PARAM(IS_XSPIM_IO_PORT(p_config->port1.io_low));
  ASSERT_DBG_PARAM(IS_XSPIM_IO_PORT(p_config->port1.io_high));
  ASSERT_DBG_PARAM(IS_XSPIM_PORT(p_config->port2.clk));
  ASSERT_DBG_PARAM(IS_XSPIM_PORT(p_config->port2.dqs));
  ASSERT_DBG_PARAM(IS_XSPIM_PORT(p_config->port2.ncs));
  ASSERT_DBG_PARAM(IS_XSPIM_IO_PORT(p_config->port2.io_low));
  ASSERT_DBG_PARAM(IS_XSPIM_IO_PORT(p_config->port2.io_high));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

#if defined(USE_HAL_XSPI_XSPIM_CLK_ENABLE_MODE) && (USE_HAL_XSPI_XSPIM_CLK_ENABLE_MODE > HAL_CLK_ENABLE_NO)
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_OCTOSPIM);
#endif /* USE_HAL_XSPI_XSPIM_CLK_ENABLE_MODE */

  /* Check if OCTOSPI1 Clock is enabled */
  if (LL_AHB2_GRP2_IsEnabledClock(LL_AHB2_GRP2_PERIPH_OCTOSPI1) == 1UL)
  {
    /* Check if OCTOSPI1 instance is enabled */
    if (READ_BIT(OCTOSPI1->CR, XSPI_CR_EN) != 0U)
    {
      return HAL_ERROR;
    }
  }
#if defined(OCTOSPI2)
  /* Check if OCTOSPI2 Clock is enabled */
  if (LL_AHB2_GRP2_IsEnabledClock(LL_AHB2_GRP2_PERIPH_OCTOSPI2) == 1UL)
  {
    /* Check if OCTOSPI2 instance is enabled */
    if (READ_BIT(OCTOSPI2->CR, XSPI_CR_EN) != 0U)
    {
      return HAL_ERROR;
    }
  }
#endif /* OCTOSPI2 */

  /* Set clock port */
  MODIFY_REG(XSPIM->PCR[XSPIM_PORT_1], (XSPIM_PCR_CLKEN | XSPIM_PCR_CLKSRC),
             ((uint32_t)p_config->port1.clk) << XSPIM_PCR_CLKEN_Pos);
  MODIFY_REG(XSPIM->PCR[XSPIM_PORT_2], (XSPIM_PCR_CLKEN | XSPIM_PCR_CLKSRC),
             (((uint32_t)p_config->port2.clk) << XSPIM_PCR_CLKEN_Pos));

  /* Set ncs port */
  MODIFY_REG(XSPIM->PCR[XSPIM_PORT_1], (XSPIM_PCR_NCSEN | XSPIM_PCR_NCSSRC),
             (((uint32_t)p_config->port1.ncs) << XSPIM_PCR_NCSEN_Pos));
  MODIFY_REG(XSPIM->PCR[XSPIM_PORT_2], (XSPIM_PCR_NCSEN | XSPIM_PCR_NCSSRC),
             (((uint32_t)p_config->port2.ncs) << XSPIM_PCR_NCSEN_Pos));

  /* Set dqs port */
  MODIFY_REG(XSPIM->PCR[XSPIM_PORT_1], XSPIM_PCR_DQSEN | XSPIM_PCR_DQSSRC,
             (((uint32_t)p_config->port1.dqs) << XSPIM_PCR_DQSEN_Pos));
  MODIFY_REG(XSPIM->PCR[XSPIM_PORT_2], XSPIM_PCR_DQSEN | XSPIM_PCR_DQSSRC,
             (((uint32_t)p_config->port2.dqs) << XSPIM_PCR_DQSEN_Pos));

  /* Set i/o port port */
  MODIFY_REG(XSPIM->PCR[XSPIM_PORT_1], (XSPIM_PCR_IOLEN | XSPIM_PCR_IOLSRC),
             (uint32_t)p_config->port1.io_low);
  MODIFY_REG(XSPIM->PCR[XSPIM_PORT_1], (XSPIM_PCR_IOHEN | XSPIM_PCR_IOHSRC),
             (((uint32_t)p_config->port1.io_high) << XSPIM_IO_HIGH_POS));
  MODIFY_REG(XSPIM->PCR[XSPIM_PORT_2], (XSPIM_PCR_IOLEN | XSPIM_PCR_IOLSRC),
             (uint32_t)p_config->port2.io_low);
  MODIFY_REG(XSPIM->PCR[XSPIM_PORT_2], (XSPIM_PCR_IOHEN | XSPIM_PCR_IOHSRC),
             (((uint32_t)p_config->port2.io_high) << XSPIM_IO_HIGH_POS));

  uint32_t mux = (uint32_t)p_config->port1.clk | (uint32_t)p_config->port1.dqs | (uint32_t)p_config->port1.ncs |
                 (uint32_t)p_config->port1.io_high | (uint32_t)p_config->port1.io_low |
                 (uint32_t)p_config->port2.clk | (uint32_t)p_config->port2.dqs | (uint32_t)p_config->port2.ncs |
                 (uint32_t)p_config->port2.io_high | (uint32_t)p_config->port2.io_low;

  /* Set the multiplexed mode if a multiplexed configuration is found */
  if ((mux & HAL_XSPI_XSPIM_MUX_MASK) != 0U)
  {
    SET_BIT(XSPIM->CR, XSPIM_CR_MUXEN);
    MODIFY_REG(XSPIM->CR, XSPIM_CR_REQ2ACK_TIME,
               ((uint32_t)p_config->req_ack_cycle - 1U) << XSPIM_CR_REQ2ACK_TIME_Pos);
  }

  return HAL_OK;
}

/**
  * @brief  Get the current IOM configuration from XSPIM.
  * @param  p_config Pointer to the hal_xspi_xspim_config_t structure.
  */
void HAL_XSPI_XSPIM_GetConfig(hal_xspi_xspim_config_t *p_config)
{
  uint32_t tmp_reg;

  ASSERT_DBG_PARAM(p_config != NULL);

  /* Retrieve the value of clock port1 */
  tmp_reg = READ_BIT(XSPIM->PCR[XSPIM_PORT_1], (XSPIM_PCR_CLKEN | XSPIM_PCR_CLKSRC))
            >> (XSPIM_PCR_CLKEN_Pos);
  p_config->port1.clk = (hal_xspi_xspim_port_t)tmp_reg;

  /* Retrieve the value of clock port2 */
  tmp_reg = READ_BIT(XSPIM->PCR[XSPIM_PORT_2], (XSPIM_PCR_CLKEN | XSPIM_PCR_CLKSRC))
            >> (XSPIM_PCR_CLKEN_Pos);
  p_config->port2.clk = (hal_xspi_xspim_port_t)tmp_reg;

  /* Retrieve the value of NCS port1 */
  tmp_reg = READ_BIT(XSPIM->PCR[XSPIM_PORT_1], (XSPIM_PCR_NCSEN | XSPIM_PCR_NCSSRC))
            >> (XSPIM_PCR_NCSEN_Pos);
  p_config->port1.ncs = (hal_xspi_xspim_port_t)tmp_reg;

  /* Retrieve the value of NCS port2 */
  tmp_reg = READ_BIT(XSPIM->PCR[XSPIM_PORT_2], (XSPIM_PCR_NCSEN | XSPIM_PCR_NCSSRC))
            >> (XSPIM_PCR_NCSEN_Pos);
  p_config->port2.ncs = (hal_xspi_xspim_port_t)tmp_reg;

  /* Retrieve the value of DQS port1 */
  tmp_reg = READ_BIT(XSPIM->PCR[XSPIM_PORT_1], (XSPIM_PCR_DQSEN | XSPIM_PCR_DQSSRC))
            >> (XSPIM_PCR_DQSEN_Pos);
  p_config->port1.dqs = (hal_xspi_xspim_port_t)tmp_reg;

  /* Retrieve the value of DQS port2 */
  tmp_reg = READ_BIT(XSPIM->PCR[XSPIM_PORT_2], (XSPIM_PCR_DQSEN | XSPIM_PCR_DQSSRC))
            >> (XSPIM_PCR_DQSEN_Pos);
  p_config->port2.dqs = (hal_xspi_xspim_port_t)tmp_reg;

  /* Retrieve the value of I/O LOW port1 */
  tmp_reg = READ_BIT(XSPIM->PCR[XSPIM_PORT_1], (XSPIM_PCR_IOLEN | XSPIM_PCR_IOLSRC));
  p_config->port1.io_low = (hal_xspi_xspim_io_t)tmp_reg;

  /* Retrieve the value of I/O LOW port2 */
  tmp_reg = READ_BIT(XSPIM->PCR[XSPIM_PORT_2], (XSPIM_PCR_IOLEN | XSPIM_PCR_IOLSRC));
  p_config->port2.io_low = (hal_xspi_xspim_io_t)tmp_reg;

  /* Retrieve the value of I/O HIGH port1 */
  tmp_reg = READ_BIT(XSPIM->PCR[XSPIM_PORT_1], (XSPIM_PCR_IOHEN | XSPIM_PCR_IOHSRC))
            >> XSPIM_IO_HIGH_POS;
  p_config->port1.io_high = (hal_xspi_xspim_io_t)tmp_reg;

  /* Retrieve the value of I/O HIGH port2 */
  tmp_reg = READ_BIT(XSPIM->PCR[XSPIM_PORT_2], (XSPIM_PCR_IOHEN | XSPIM_PCR_IOHSRC))
            >> XSPIM_IO_HIGH_POS;
  p_config->port2.io_high = (hal_xspi_xspim_io_t)tmp_reg;

  /* Retrieve the value of mux mode */
  tmp_reg = READ_BIT(XSPIM->CR,
                     XSPIM_CR_REQ2ACK_TIME) >> (XSPIM_CR_REQ2ACK_TIME_Pos);
  p_config->req_ack_cycle = (tmp_reg + 1U);
}
/**
  * @}
  */
#endif /* XSPIM */

#if defined(USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined (OTFDEC1)
/** @addtogroup XSPI_Exported_Functions_Group10
  * @{

This subsection provides a set of functions allowing to configure the OTFDEC :

- Call the function HAL_XSPI_OTFDEC_SetConfigRegion() to configure the OTFDEC region according to the user parameters.
- Call the function HAL_XSPI_OTFDEC_GetConfigRegion() to get the OTFDEC region configuration.
- Call the function HAL_XSPI_OTFDEC_StartRegionDecryption() to start the decryption of the OTFDEC region.
- Call the function HAL_XSPI_OTFDEC_StopRegionDecryption() to stop the decryption of the OTFDEC region.
- Call the function HAL_XSPI_OTFDEC_Encrypt() to encrypt data in a dedicated region.
- Call the function HAL_XSPI_OTFDEC_GetRegionKeyCRC() to get region key CRC.
- Call the function HAL_XSPI_OTFDEC_EnablePrivAccess() to enable privilege access.
- Call the function HAL_XSPI_OTFDEC_DisablePrivAccess() to disable privilege access.
- Call the function HAL_XSPI_OTFDEC_IsEnabledPrivAccess() to check if privilege access is enabled or not.
- Call the function HAL_XSPI_OTFDEC_LockRegionConfig() to lock region configuration.
- Call the function HAL_XSPI_OTFDEC_IsLockedRegionConfig() to check if region configuration is locked or not.
- Call the function HAL_XSPI_OTFDEC_LockRegionKey() to lock region key.
- Call the function HAL_XSPI_OTFDEC_IsLockedRegionKey() to check if region key is locked or not.
  */

/**
  * @brief  Configure the OTFDEC region.
  * @param  hxspi Pointer to a @ref hal_xspi_handle_t structure that contains
  *               handle information for the specified XSPI instance.
  * @param  region            Region index, can be a value of @ref hal_xspi_otfdec_region_t.
  * @param  p_config          Pointer to the @ref hal_xspi_otfdec_config_t structure.
  * @param  p_key_config      Pointer to the @ref hal_xspi_otfdec_key_t.
  * @retval HAL_ERROR         OTFDEC region key is not correctly generated.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            OTFDEC region has been correctly configured.
  */
hal_status_t HAL_XSPI_OTFDEC_SetConfigRegion(hal_xspi_handle_t *hxspi,
                                             hal_xspi_otfdec_region_t region,
                                             const hal_xspi_otfdec_config_t *p_config,
                                             const hal_xspi_otfdec_key_t *p_key_config)
{
  OTFDEC_TypeDef        *otfdec_instance;
  OTFDEC_Region_TypeDef *otfdec_region;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_key_config != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_START_ADRESS(p_config->start_address));
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_RGION_SIZE(p_config->start_address, p_config->end_address));
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_MODE(p_config->mode));
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_REGION(region));

  /* The OTFDEC peripheral can work only if the XSPI is configured, which mean XSPI is in the IDLE state */
  ASSERT_DBG_STATE(hxspi->global_state, (uint32_t)HAL_XSPI_STATE_IDLE | (uint32_t)HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE);
  ASSERT_DBG_STATE(hxspi->region_state[region], (uint32_t)HAL_XSPI_OTFDEC_REGION_STATE_CONFIGURED \
                   | (uint32_t)HAL_XSPI_OTFDEC_REGION_STATE_RESET);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_config == NULL) || (p_key_config == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hxspi == NULL) || (p_config == NULL) || (p_key_config == NULL) \
      || ((uint32_t)IS_XSPI_OTFDEC_REGION(region) == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);
  otfdec_region   = XSPI_OTFDEC_GET_REGION_INSTANCE(otfdec_instance, region);

  if (OTFDEC_SetConfigRegion(otfdec_region, (uint8_t) p_config->mode, p_key_config->p_key,    \
                             p_config->nonce[0], p_config->nonce[1], p_config->start_address, \
                             p_config->end_address, p_config->version) != OTFDEC_CORE_OK)
  {
    return HAL_ERROR;
  }

  hxspi->region_state[region] = HAL_XSPI_OTFDEC_REGION_STATE_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief  Get the OTFDEC region configuration.
  * @param  hxspi             Pointer to a @ref hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  region            Region index, can be a value of @ref hal_xspi_otfdec_region_t.
  * @param  p_config          Pointer to the @ref hal_xspi_config_t structure.
  */
void  HAL_XSPI_OTFDEC_GetConfigRegion(hal_xspi_handle_t *hxspi,
                                      hal_xspi_otfdec_region_t  region,
                                      hal_xspi_otfdec_config_t *p_config)
{
  OTFDEC_TypeDef        *otfdec_instance;
  OTFDEC_Region_TypeDef *otfdec_region;
  uint8_t region_mode;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_REGION(region));

  ASSERT_DBG_STATE(hxspi->region_state[region], (uint32_t)HAL_XSPI_OTFDEC_REGION_STATE_CONFIGURED);

  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);
  otfdec_region   = XSPI_OTFDEC_GET_REGION_INSTANCE(otfdec_instance, region);

  OTFDEC_GetConfigRegion(otfdec_region, &region_mode, &(p_config->nonce[0]), &(p_config->nonce[1]),
                         &(p_config->start_address), &(p_config->end_address), &(p_config->version));

  p_config->mode = (hal_xspi_otfdec_mode_t)region_mode;
}

/** @brief  Start the OTFDEC region decryption.
  * @param  hxspi             Pointer to a @ref hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  region            region index, can be a value of @ref hal_xspi_otfdec_region_t.
  * @param  interrupts        Specifies the OTFDEC interrupt sources to be enabled. This parameter can be a combination
  *                           of @ref XSPI_OTFDEC_Interrupts group.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            OTFDEC region has been correctly enabled.
  */
hal_status_t HAL_XSPI_OTFDEC_StartRegionDecryption(hal_xspi_handle_t *hxspi,
                                                   hal_xspi_otfdec_region_t region,
                                                   uint32_t interrupts)
{
  OTFDEC_TypeDef        *otfdec_instance;
  OTFDEC_Region_TypeDef *otfdec_region;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_REGION(region));
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_IT(interrupts));

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hxspi == NULL) || ((uint32_t)IS_XSPI_OTFDEC_REGION(region) == 0UL) \
      || ((uint32_t)IS_XSPI_OTFDEC_IT(interrupts) == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  ASSERT_DBG_STATE(hxspi->global_state, (uint32_t)HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE);
  ASSERT_DBG_STATE(hxspi->region_state[region], (uint32_t)HAL_XSPI_OTFDEC_REGION_STATE_CONFIGURED);

  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);
  otfdec_region   = XSPI_OTFDEC_GET_REGION_INSTANCE(otfdec_instance, region);

  HAL_CHECK_UPDATE_STATE(hxspi, region_state[region], HAL_XSPI_OTFDEC_REGION_STATE_CONFIGURED, \
                         HAL_XSPI_OTFDEC_REGION_STATE_DECRYPT);

  OTFDEC_StartRegionDecryption(otfdec_instance, otfdec_region, interrupts);

  return HAL_OK;
}

/** @brief  Stop the OTFDEC region decryption.
  * @param  hxspi             Pointer to a @ref hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  region            Region index, can be a value of @ref hal_xspi_otfdec_region_t.
  * @retval HAL_INVALID_PARAM Invalid param return when the XSPI handle is NULL.
  * @retval HAL_OK            OTFDEC region has been correctly disabled.
  */
hal_status_t HAL_XSPI_OTFDEC_StopRegionDecryption(hal_xspi_handle_t *hxspi, hal_xspi_otfdec_region_t region)
{
  OTFDEC_TypeDef        *otfdec_instance;
  OTFDEC_Region_TypeDef *otfdec_region;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_REGION(region));

  ASSERT_DBG_STATE(hxspi->region_state[region], (uint32_t)HAL_XSPI_OTFDEC_REGION_STATE_DECRYPT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hxspi == NULL) || ((uint32_t)IS_XSPI_OTFDEC_REGION(region) == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);
  otfdec_region   = XSPI_OTFDEC_GET_REGION_INSTANCE(otfdec_instance, region);

  OTFDEC_StopRegionDecryption(otfdec_region);

  hxspi->region_state[region] = HAL_XSPI_OTFDEC_REGION_STATE_CONFIGURED;

  return HAL_OK;
}

/** @brief  Encrypt the OTFDEC region.
  * @param  hxspi             Pointer to a @ref hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  region            Region index, can be a value of @ref hal_xspi_otfdec_region_t.
  * @param  p_input           Pointer to plain data.
  * @param  p_output          Pointer to ciphered data.
  * @param  size_byte         Plain data size in byte.
  * @param  start_address     Starting address in the external memory area where the enciphered data will be eventually
  *                           stored.
  * @param  interrupts        Specifies the OTFDEC interrupt sources to be enabled. This parameter can be a combination
  *                           of @ref XSPI_OTFDEC_Interrupts group.
  * @retval HAL_INVALID_PARAM Invalid param return when one of the provided inputs is NULL.
  * @retval HAL_OK            OTFDEC region has been correctly encrypted.
  */
hal_status_t HAL_XSPI_OTFDEC_Encrypt(hal_xspi_handle_t *hxspi, hal_xspi_otfdec_region_t region, uint32_t *p_input,
                                     uint32_t *p_output, uint32_t size_byte, uint32_t start_address,
                                     uint32_t interrupts)
{
  OTFDEC_TypeDef        *otfdec_instance;
  OTFDEC_Region_TypeDef *otfdec_region;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_input != NULL);
  ASSERT_DBG_PARAM(p_output != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_REGION(region));
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_START_ADRESS(start_address));
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_IT(interrupts));

  ASSERT_DBG_STATE(hxspi->global_state, (uint32_t)HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE);
  ASSERT_DBG_STATE(hxspi->region_state[region], (uint32_t)HAL_XSPI_OTFDEC_REGION_STATE_CONFIGURED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_input == NULL) || (p_output == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hxspi == NULL) || (p_input == NULL) || (p_output == NULL) || (size_byte == 0UL) || (start_address == 0UL) \
      || ((uint32_t)IS_XSPI_OTFDEC_REGION(region) == 0UL) || ((uint32_t)IS_XSPI_OTFDEC_IT(interrupts) == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hxspi, global_state, HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE, HAL_XSPI_OTFDEC_STATE_ENCRYPT);

  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);
  otfdec_region   = XSPI_OTFDEC_GET_REGION_INSTANCE(otfdec_instance, region);

  OTFDEC_Encrypt(otfdec_instance, otfdec_region, p_input, p_output, size_byte, start_address, interrupts);

  hxspi->global_state = HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE;

  return HAL_OK;
}

/**
  * @brief  Get the region key crc.
  * @param  hxspi             Pointer to a @ref hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  region            Region index, can be a value of @ref hal_xspi_otfdec_region_t.
  * @param  p_key_crc         Pointer to be filled with crc key.
  * @retval HAL_INVALID_PARAM Invalid param return when one of the provided inputs is NULL.
  * @retval HAL_OK            OTFDEC region key crc has been returned correctly.
  */
hal_status_t HAL_XSPI_OTFDEC_GetRegionKeyCRC(hal_xspi_handle_t *hxspi,
                                             hal_xspi_otfdec_region_t region,
                                             uint8_t *p_key_crc)
{
  OTFDEC_TypeDef        *otfdec_instance;
  OTFDEC_Region_TypeDef *otfdec_region;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(p_key_crc != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_REGION(region));

  ASSERT_DBG_STATE(hxspi->region_state[region], (uint32_t)HAL_XSPI_OTFDEC_REGION_STATE_CONFIGURED);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_key_crc == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hxspi == NULL) || (p_key_crc == NULL) || ((uint32_t)IS_XSPI_OTFDEC_REGION(region) == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);
  otfdec_region = XSPI_OTFDEC_GET_REGION_INSTANCE(otfdec_instance, region);

  *p_key_crc = OTFDEC_GetRegionKeyCRC(otfdec_region);

  return HAL_OK;
}

/**
  * @brief  Enable the privilege access protection.
  * @param  hxspi             Pointer to a @ref hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            OTFDEC Privilege access protection has been correctly enabled.
  */
hal_status_t HAL_XSPI_OTFDEC_EnablePrivAccess(hal_xspi_handle_t *hxspi)
{
  OTFDEC_TypeDef *otfdec_instance;

  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, (uint32_t)HAL_XSPI_STATE_IDLE | (uint32_t)HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hxspi == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);

  OTFDEC_EnablePrivAccess(otfdec_instance);

  return HAL_OK;
}

/**
  * @brief  Disable the privilege access protection.
  * @param  hxspi             Pointer to a @ref hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            OTFDEC Privilege access protection has been correctly disabled.
  */
hal_status_t HAL_XSPI_OTFDEC_DisablePrivAccess(hal_xspi_handle_t *hxspi)
{
  OTFDEC_TypeDef *otfdec_instance;

  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, (uint32_t)HAL_XSPI_STATE_IDLE | (uint32_t)HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hxspi == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);

  OTFDEC_DisablePrivAccess(otfdec_instance);

  return HAL_OK;
}
/**
  * @brief  Check whether the otfdec privilege access protection is enabled or not.
  * @param  hxspi                                    Pointer to a @ref hal_xspi_handle_t structure that contains
  *                                                  handle information for the specified XSPI instance.
  * @retval HAL_XSPI_OTFDEC_ATTRIBUTE_NON_PRIVILEGED OTFDEC is accessed .in non privileged mode.
  * @retval HAL_XSPI_OTFDEC_ATTRIBUTE_PRIVILEGED     OTFDEC is accessed only in privileged mode.
  */
hal_xspi_otfdec_privilege_attr_t HAL_XSPI_OTFDEC_IsEnabledPrivAccess(hal_xspi_handle_t *hxspi)
{
  OTFDEC_TypeDef *otfdec_instance;

  ASSERT_DBG_PARAM(hxspi != NULL);

  ASSERT_DBG_STATE(hxspi->global_state, (uint32_t)HAL_XSPI_STATE_IDLE | (uint32_t)HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE);

  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);

  return (hal_xspi_otfdec_privilege_attr_t) OTFDEC_IsEnabledPrivAccess(otfdec_instance);
}

/**
  * @brief  Lock the OTFDEC region configuration.
  * @param  hxspi             Pointer to a @ref hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  region            region index, can be a value of @ref hal_xspi_otfdec_region_t.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK OTFDEC     Region configuration has been correctly locked.
  */
hal_status_t HAL_XSPI_OTFDEC_LockRegionConfig(hal_xspi_handle_t *hxspi, hal_xspi_otfdec_region_t region)
{
  OTFDEC_TypeDef        *otfdec_instance;
  OTFDEC_Region_TypeDef *otfdec_region;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_REGION(region));

  ASSERT_DBG_STATE(hxspi->region_state[region], (uint32_t)HAL_XSPI_OTFDEC_REGION_STATE_DECRYPT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hxspi == NULL) || ((uint32_t)IS_XSPI_OTFDEC_REGION(region) == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);
  otfdec_region   = XSPI_OTFDEC_GET_REGION_INSTANCE(otfdec_instance, region);

  OTFDEC_LockRegionConfig(otfdec_region);

  return HAL_OK;
}

/**
  * @brief  Check whether the OTFDEC region configuration is locked or not.
  * @param  hxspi                                Pointer to a @ref hal_xspi_handle_t structure that contains
  *                                              handle information for the specified XSPI instance.
  * @param  region                                Region index, can be a value of @ref hal_xspi_otfdec_region_t.
  * @retval HAL_XSPI_OTFDEC_LOCK_CONFIG_ENABLED  OTFDEC region configuration is locked.
  * @retval HAL_XSPI_OTFDEC_LOCK_CONFIG_DISABLED OTFDEC region configuration is not locked.
  */
hal_xspi_otfdec_lock_config_status_t HAL_XSPI_OTFDEC_IsLockedRegionConfig(hal_xspi_handle_t *hxspi,
                                                                          hal_xspi_otfdec_region_t region)
{
  OTFDEC_TypeDef        *otfdec_instance;
  OTFDEC_Region_TypeDef *otfdec_region;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_REGION(region));
  ASSERT_DBG_STATE(hxspi->region_state[region], (uint32_t)HAL_XSPI_OTFDEC_REGION_STATE_CONFIGURED \
                   | (uint32_t)HAL_XSPI_OTFDEC_REGION_STATE_DECRYPT);

  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);
  otfdec_region   = XSPI_OTFDEC_GET_REGION_INSTANCE(otfdec_instance, region);

  return (hal_xspi_otfdec_lock_config_status_t) OTFDEC_IsRegionConfigLocked(otfdec_region);
}

/**
  * @brief  Enable the OTFDEC region key lock.
  * @param  hxspi             Pointer to a @ref hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  region            Region index, can be a value of @ref hal_xspi_otfdec_region_t.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK Region     Key lock has been correctly locked.
  */
hal_status_t HAL_XSPI_OTFDEC_LockRegionKey(hal_xspi_handle_t *hxspi, hal_xspi_otfdec_region_t region)
{
  OTFDEC_TypeDef        *otfdec_instance;
  OTFDEC_Region_TypeDef *otfdec_region;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_REGION(region));
  ASSERT_DBG_STATE(hxspi->region_state[region], (uint32_t)HAL_XSPI_OTFDEC_REGION_STATE_CONFIGURED);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hxspi == NULL) || ((uint32_t)IS_XSPI_OTFDEC_REGION(region) == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);
  otfdec_region   = XSPI_OTFDEC_GET_REGION_INSTANCE(otfdec_instance, region);

  OTFDEC_LockRegionKey(otfdec_region);

  return HAL_OK;
}

/**
  * @brief  Check whether the region key is locked or not.
  * @param  hxspi                             Pointer to a @ref hal_xspi_handle_t structure that contains
  *                                           handle information for the specified XSPI instance.
  * @param  region                            Region index, can be a value of @ref hal_xspi_otfdec_region_t.
  * @retval HAL_XSPI_OTFDEC_LOCK_KEY_ENABLED  OTFDEC region key is locked.
  * @retval HAL_XSPI_OTFDEC_LOCK_KEY_DISABLED OTFDEC region key is not locked.
  */
hal_xspi_otfdec_lock_key_status_t HAL_XSPI_OTFDEC_IsLockedRegionKey(hal_xspi_handle_t *hxspi,
                                                                    hal_xspi_otfdec_region_t region)
{
  OTFDEC_TypeDef        *otfdec_instance;
  OTFDEC_Region_TypeDef *otfdec_region;

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_REGION(region));
  ASSERT_DBG_STATE(hxspi->region_state[region], (uint32_t)HAL_XSPI_OTFDEC_REGION_STATE_CONFIGURED);

  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);
  otfdec_region   = XSPI_OTFDEC_GET_REGION_INSTANCE(otfdec_instance, region);

  return (hal_xspi_otfdec_lock_key_status_t) OTFDEC_IsRegionKeyLocked(otfdec_region);
}

/**
  * @brief  Handle the OTFDEC interrupt request.
  * @param  hxspi Pointer to @ref hal_xspi_handle_t structure that contains the handle information for the specified
            XSPI instance.
  */
void HAL_XSPI_OTFDEC_IRQHandler(hal_xspi_handle_t *hxspi)
{
  OTFDEC_TypeDef        *otfdec_instance;

#if defined (USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  uint32_t otfdec_isr_reg;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  ASSERT_DBG_PARAM(hxspi != NULL);

  otfdec_instance = XSPI_OTFDEC_GET_INSTANCE(hxspi->instance);

#if defined (USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  /* Get current IT flags values */
  otfdec_isr_reg  = READ_REG(otfdec_instance->ISR);
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  /* Clear errors flags */
  WRITE_REG(otfdec_instance->ICR, OTFDEC_ICR_SEIF | OTFDEC_ICR_XONEIF | OTFDEC_ICR_KEIF);

  /* Update error code according the interrupt flag error source */
#if defined (USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  if ((otfdec_isr_reg & OTFDEC_ISR_SEIF) == OTFDEC_ISR_SEIF)
  {
    hxspi->last_otfdec_error_codes |= HAL_XSPI_ERROR_OTFDEC_SECURITY;
  }

  if ((otfdec_isr_reg & OTFDEC_ISR_XONEIF) == OTFDEC_ISR_XONEIF)
  {
    hxspi->last_otfdec_error_codes |= HAL_XSPI_ERROR_OTFDEC_EXEC_ONLY_EXEC_NEVER;
  }

  if ((otfdec_isr_reg & OTFDEC_ISR_KEIF) == OTFDEC_ISR_KEIF)
  {
    hxspi->last_otfdec_error_codes |= HAL_XSPI_ERROR_OTFDEC_KEY;
  }
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

  /* Call the Error Callback */
#if (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
  hxspi->p_otfdec_error_cb(hxspi);
#else
  HAL_XSPI_OTFDEC_ErrorCallback(hxspi);
#endif /* USE_HAL_XSPI_REGISTER_CALLBACKS */
}

/**
  * @brief  OTFDEC Error callback.
  * @param  hxspi Pointer to @ref hal_xspi_handle_t structure that contains the handle information for the specified
            XSPI instance.
  */
__WEAK void HAL_XSPI_OTFDEC_ErrorCallback(hal_xspi_handle_t *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hxspi);
  /* NOTE : This function must not be modified, when the callback is needed,
  the HAL_XSPI_OTFDEC_ErrorCallback could be implemented in the user file
  */
}

#if defined(USE_HAL_XSPI_REGISTER_CALLBACKS ) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register the XSPI OTFDEC Error Callback to be used instead of
  *         the weak HAL_XSPI_OTFDEC_ErrorCallback() predefined callback.
  * @param  hxspi             Pointer to a @ref hal_xspi_handle_t structure that contains
  *                           handle information for the specified XSPI instance.
  * @param  callback          Specifies the error callback.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_XSPI_OTFDEC_RegisterErrorCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t callback)
{

  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Store the callback function within handle */
  hxspi->p_otfdec_error_cb = callback;

  return HAL_OK;
}
#endif /* USE_HAL_XSPI_REGISTER_CALLBACKS */

/**
  * @brief  Return the XSPI OTFDEC region state.
  * @param  hxspi                                   Pointer to a @ref hal_xspi_handle_t structure that contains
  *                                                 handle information for the specified XSPI instance.
  * @param  region                                  Can be a value of @ref hal_xspi_otfdec_region_t.
  * @retval HAL_XSPI_OTFDEC_REGION_STATE_RESET      OTFDEC region is not yet configured.
  * @retval HAL_XSPI_OTFDEC_REGION_STATE_CONFIGURED OTFDEC region is configured.
  * @retval HAL_XSPI_OTFDEC_REGION_STATE_DECRYPT    OTFDEC region is decryption is ongoing.
  */
hal_xspi_otfdec_region_state_t HAL_XSPI_OTFDEC_GetRegionState(const hal_xspi_handle_t *hxspi,
                                                              hal_xspi_otfdec_region_t region)
{
  ASSERT_DBG_PARAM(hxspi != NULL);
  ASSERT_DBG_PARAM(IS_XSPI_OTFDEC_REGION(region));

  return (hal_xspi_otfdec_region_state_t) hxspi->region_state[region];
}

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
/**
  * @brief  Return the XSPI OTFDEC error code.
  * @param  hxspi    Pointer to a @ref hal_xspi_handle_t structure that contains
  *                  handle information for the specified XSPI instance.
  * @retval uint32_t Last error codes which can be a combination of @ref XSPI_OTFDEC_Error_Code
  */
uint32_t HAL_XSPI_OTFDEC_GetLastErrorCodes(const hal_xspi_handle_t *hxspi)
{
  ASSERT_DBG_PARAM(hxspi != NULL);

  return hxspi->last_otfdec_error_codes;
}
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */
/**
  * @}
  */
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */

/**
  * @}
  */

/** @addtogroup XSPI_Private_Functions XSPI Private Functions
  * @{
  */

/**
  * @brief  Wait for a flag state until timeout in non-blocking mode.
  * @param  hxspi      Pointer to XSPI handle.
  * @param  flag       Flag checked.
  * @param  state      Value of the flag expected.
  * @param  timeout_ms Timeout duration.
  * @retval HAL_ERROR  An error has occurred.
  * @retval HAL_OK     Flag is correctly set.
  */
static hal_status_t XSPI_WaitFlagStateUntilTimeout(hal_xspi_handle_t *hxspi,
                                                   uint32_t flag,
                                                   hal_xspi_flag_status_t state,
                                                   uint32_t timeout_ms)
{
  uint32_t timeout = (timeout_ms * ((HAL_RCC_GetHCLKFreq() / 8U / 1000U) + 1U));
  hal_xspi_flag_status_t tmp_flag;

  do
  {
    tmp_flag = HAL_XSPI_IsActiveFlag(hxspi, flag);
    timeout--;

  } while ((tmp_flag != state) && (timeout != 0U));

  if (timeout == 0U)
  {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
    if (HAL_XSPI_IsActiveFlag(hxspi, HAL_XSPI_FLAG_TE) != HAL_XSPI_FLAG_NOT_ACTIVE)
    {
      hxspi->last_error_codes = HAL_XSPI_ERROR_TRANSFER;
    }
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

    return HAL_ERROR;
  }

  return HAL_OK;
}

#if defined(USE_HAL_XSPI_DMA) && (USE_HAL_XSPI_DMA == 1)
/**
  * @brief DMA XSPI process complete callback.
  * @param hdma Pointer to DMA handle.
  */
static void XSPI_DMACplt(hal_dma_handle_t *hdma)
{
  hal_xspi_handle_t *hxspi = (hal_xspi_handle_t *)(hdma->p_parent);
  hxspi->xfer_count = 0;

  /* Disable the DMA transfer on the XSPI side */
  CLEAR_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_DMAEN);

  LL_DMA_DisableChannel((DMA_Channel_TypeDef *)((uint32_t)hdma->instance));

  /* Enable the XSPI transfer complete interrupt */
  HAL_XSPI_EnableIT(hxspi, (uint32_t)HAL_XSPI_IT_TC);
}

/**
  * @brief DMA XSPI process half complete callback.
  * @param hdma Pointer to DMA handle.
  */
static void XSPI_DMAHalfCplt(hal_dma_handle_t *hdma)
{
  hal_xspi_handle_t *hxspi = (hal_xspi_handle_t *)(hdma->p_parent);
  hxspi->xfer_count = (hxspi->xfer_count >> 1);

  if (READ_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FMODE) == XSPI_FUNCTIONAL_MODE_INDIRECT_READ)
  {
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
    hxspi->p_rx_half_cplt_cb(hxspi);
#else
    HAL_XSPI_RxHalfCpltCallback(hxspi);
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */
  }
  else
  {
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
    hxspi->p_tx_half_cplt_cb(hxspi);
#else
    HAL_XSPI_TxHalfCpltCallback(hxspi);
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */
  }
}

/**
  * @brief DMA XSPI communication error callback.
  * @param hdma Pointer to DMA handle.
  */
static void XSPI_DMAError(hal_dma_handle_t *hdma)
{
  hal_xspi_handle_t *hxspi = (hal_xspi_handle_t *)(hdma->p_parent);
  hxspi->xfer_count = 0;

  /* Disable the DMA transfer on the XSPI side */
  CLEAR_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_DMAEN);

  /* Abort the XSPI */
  if (HAL_XSPI_Abort_IT(hxspi) != HAL_OK)
  {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
    hxspi->last_error_codes |= HAL_XSPI_ERROR_DMA;
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

    HAL_XSPI_DisableIT(hxspi, (uint32_t)HAL_XSPI_IT_TC | (uint32_t)HAL_XSPI_IT_FT | (uint32_t)HAL_XSPI_IT_TE);

    hxspi->global_state = HAL_XSPI_STATE_IDLE;

#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
    hxspi->p_error_cb(hxspi);
#else
    HAL_XSPI_ErrorCallback(hxspi);
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */
  }
}

/**
  * @brief DMA XSPI abort complete callback.
  * @param hdma Pointer to DMA handle.
  */
static void XSPI_DMAAbortOnError(hal_dma_handle_t *hdma)
{
  hal_xspi_handle_t *hxspi = (hal_xspi_handle_t *)(hdma->p_parent);
  hxspi->xfer_count = 0;

  /* DMA abort called by XSPI abort */
  if (HAL_XSPI_IsActiveFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY) != HAL_XSPI_FLAG_NOT_ACTIVE)
  {
    /* Clear transfer complete flag */
    HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TC);

    /* Enable the transfer complete interrupts */
    HAL_XSPI_EnableIT(hxspi, (uint32_t)HAL_XSPI_IT_TC);

    /* Perform an abort of the XSPI */
    SET_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_ABORT);
  }
  else
  {
    return;
  }
}

/**
  * @brief DMA XSPI abort complete callback.
  * @param hdma Pointer to DMA handle.
  */
static void XSPI_DMAAbort(hal_dma_handle_t *hdma)
{
  hal_xspi_handle_t *hxspi = (hal_xspi_handle_t *)(hdma->p_parent);
  hxspi->xfer_count = 0;

  /* DMA abort called by XSPI abort */
  if (HAL_XSPI_IsActiveFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY) != HAL_XSPI_FLAG_NOT_ACTIVE)
  {
    /* Clear transfer complete flag */
    HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TC);

    /* Enable the interrupt on the transfer complete flag */
    HAL_XSPI_EnableIT(hxspi, (uint32_t)HAL_XSPI_IT_TC);

    /* Perform an abort of the XSPI */
    SET_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_ABORT);
  }
  else
  {
    return;
  }
}
#endif /* USE_HAL_XSPI_DMA */

/**
  * @brief  Set the Regular command configuration.
  * @param  hxspi       Pointer to XSPI handle.
  * @param  p_cmd       Structure that contains the Regular command configuration information.
  * @param  timeout_ms  Timeout duration.
  * @param  it_state    interrupt state.
  * @retval HAL_TIMEOUT In case of user timeout.
  * @retval HAL_OK      Operation completed.
  */
static hal_status_t XSPI_SendRegularCmd(hal_xspi_handle_t *hxspi,
                                        const hal_xspi_regular_cmd_t *p_cmd,
                                        uint32_t timeout_ms,
                                        hal_xspi_interrupt_state_t it_state)
{
  hal_status_t status = HAL_OK;
  volatile uint32_t *p_ccr_reg;
  volatile uint32_t *p_tcr_reg;
  volatile uint32_t *p_ir_reg;
  volatile uint32_t *p_abr_reg;

  /* Wait till busy flag is reset */
  if (XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY, HAL_XSPI_FLAG_NOT_ACTIVE,
                                     timeout_ms) == HAL_OK)
  {
    /* Clear transfer error and transfer complete flags */
    HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TE | (uint32_t)HAL_XSPI_FLAG_TC);

    /* Set functional mode */
    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FMODE, 0U);

    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_IO_SELECT_MSK, (uint32_t)p_cmd->io_select);

    p_ccr_reg = (volatile uint32_t *)((uint32_t)(&(XSPI_GET_INSTANCE(hxspi)->CCR)) + (uint32_t)p_cmd->operation_type);
    p_tcr_reg = (volatile uint32_t *)((uint32_t)(&(XSPI_GET_INSTANCE(hxspi)->TCR)) + (uint32_t)p_cmd->operation_type);
    p_ir_reg  = (volatile uint32_t *)((uint32_t)(&(XSPI_GET_INSTANCE(hxspi)->IR)) + (uint32_t)p_cmd->operation_type);
    p_abr_reg = (volatile uint32_t *)((uint32_t)(&(XSPI_GET_INSTANCE(hxspi)->ABR)) + (uint32_t)p_cmd->operation_type);

    /* Configure DQS modes */
    *p_ccr_reg = (uint32_t)p_cmd->dqs_mode_status | (uint32_t)p_cmd->alternate_bytes_mode |
                 (uint32_t)p_cmd->alternate_bytes_dtr_mode_status | (uint32_t)p_cmd->alternate_bytes_width |
                 (uint32_t)p_cmd->instruction_mode | (uint32_t)p_cmd->instruction_dtr_mode_status
                 | (uint32_t)p_cmd->instruction_width |
                 (uint32_t)p_cmd->addr_mode | (uint32_t)p_cmd->addr_dtr_mode_status | (uint32_t)p_cmd->addr_width  |
                 (uint32_t)p_cmd->data_mode | (uint32_t)p_cmd->data_dtr_mode_status;

    /* Workaround for Erratasheet: Memory-mapped write error response when DQS output is disabled */
    if (p_cmd->operation_type == HAL_XSPI_OPERATION_WRITE_CFG)
    {
      /* When doing memory-mapped writes, set the DQSE bit of the OCTOSPI_WCCR register,
         even for memories that have no DQS pin. */
      SET_BIT((*p_ccr_reg), XSPI_CCR_DQSE);
    }

    /* Configure alternate bytes */
    *p_abr_reg = p_cmd->alternate_bytes;

    /* Configure the number of dummy cycles */
    MODIFY_REG((*p_tcr_reg), XSPI_TCR_DCYC, p_cmd->dummy_cycle);

    /* Configure the number of data */
    XSPI_GET_INSTANCE(hxspi)->DLR = (p_cmd->size_byte - 1U);

    /* Configure the instruction value */
    *p_ir_reg = p_cmd->instruction;

    /* Configure the address value */
    XSPI_GET_INSTANCE(hxspi)->AR = p_cmd->addr;

    if (it_state == XSPI_INTERRUPT_DISABLE)
    {
      if (p_cmd->data_mode == HAL_XSPI_REGULAR_DATA_NONE)
      {
        /* When there is no data phase, the transfer start as soon as the configuration is done
        so wait until TC flag is set to go back in idle state */
        if (XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY, HAL_XSPI_FLAG_NOT_ACTIVE,
                                           timeout_ms) == HAL_OK)
        {
          HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TC);
        }
        else
        {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
          if (HAL_XSPI_IsActiveFlag(hxspi, HAL_XSPI_FLAG_TE) != HAL_XSPI_FLAG_NOT_ACTIVE)
          {
            hxspi->last_error_codes = HAL_XSPI_ERROR_TRANSFER;
          }
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

          status = HAL_TIMEOUT;
        }
      }
    }
    else
    {
      /* Enable the interrupts on transfer complete and transfer error flags */
      HAL_XSPI_EnableIT(hxspi, (uint32_t)HAL_XSPI_IT_TC | (uint32_t)HAL_XSPI_IT_TE);
    }
  }
  else
  {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
    if (HAL_XSPI_IsActiveFlag(hxspi, HAL_XSPI_FLAG_TE) != HAL_XSPI_FLAG_NOT_ACTIVE)
    {
      hxspi->last_error_codes = HAL_XSPI_ERROR_TRANSFER;
    }
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

    status = HAL_TIMEOUT;
  }

  return status;
}

/**
  * @brief  Configure the XSPI Automatic Polling Mode for Regular protocol.
  * @param  hxspi       Pointer to XSPI handle.
  * @param  p_config    Pointer to structure that contains the polling configuration information.
  * @param  timeout_ms  Timeout duration.
  * @param  it_state    Interrupt state.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_TIMEOUT In case of user timeout.
  * @retval HAL_BUSY    XSPI state is active when calling this API.
  * @retval HAL_OK      Operation completed.
  */
static hal_status_t XSPI_ExecRegularAutoPoll(hal_xspi_handle_t *hxspi,
                                             const hal_xspi_auto_polling_config_t *p_config,
                                             uint32_t timeout_ms,
                                             hal_xspi_interrupt_state_t it_state)
{
  uint32_t addr_reg = XSPI_GET_INSTANCE(hxspi)->AR;
  uint32_t ir_reg = XSPI_GET_INSTANCE(hxspi)->IR;

  /* Wait till busy flag is reset */
  if (XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY, HAL_XSPI_FLAG_NOT_ACTIVE,
                                     timeout_ms) == HAL_OK)
  {
    /* Set the following configurations :
    - match mask
    - match value
    - match mode
    - interval cycle
    - automatic stop */
    WRITE_REG(XSPI_GET_INSTANCE(hxspi)->PSMKR, p_config->match_mask);
    WRITE_REG(XSPI_GET_INSTANCE(hxspi)->PSMAR, p_config->match_value);
    WRITE_REG(XSPI_GET_INSTANCE(hxspi)->PIR,   p_config->interval_cycle);
    MODIFY_REG(XSPI_GET_INSTANCE(hxspi)->CR, (XSPI_CR_PMM | XSPI_CR_APMS | XSPI_CR_FMODE),
               ((uint32_t)p_config->match_mode | (uint32_t)p_config->automatic_stop_status |
                XSPI_FUNCTIONAL_MODE_AUTO_POLLING));

    if (it_state != XSPI_INTERRUPT_DISABLE)
    {
      /* Clear transfer error and status match flags */
      HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TE | (uint32_t)HAL_XSPI_FLAG_SM);

      /* Enable the interrupts on the status match and transfer error flags */
      HAL_XSPI_EnableIT(hxspi, (uint32_t)HAL_XSPI_IT_SM | (uint32_t)HAL_XSPI_IT_TE);
    }

    /* Trig the transfer by re-writing address or instruction register */
    if (READ_BIT(XSPI_GET_INSTANCE(hxspi)->CCR, XSPI_CCR_ADMODE) != (uint32_t)HAL_XSPI_ADDR_NONE)
    {
      WRITE_REG(XSPI_GET_INSTANCE(hxspi)->AR, addr_reg);
    }
    else
    {
      WRITE_REG(XSPI_GET_INSTANCE(hxspi)->IR, ir_reg);
    }

    if (it_state == XSPI_INTERRUPT_DISABLE)
    {
      /* Wait till status match flag is set to go back in idle state */
      if (XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_SM, HAL_XSPI_FLAG_ACTIVE,
                                         timeout_ms) == HAL_OK)
      {
        /* Clear status match flag */
        HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_SM);
      }
      else
      {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
        if (HAL_XSPI_IsActiveFlag(hxspi, HAL_XSPI_FLAG_TE) != HAL_XSPI_FLAG_NOT_ACTIVE)
        {
          hxspi->last_error_codes = HAL_XSPI_ERROR_TRANSFER;
        }
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

        return HAL_TIMEOUT;
      }
    }
  }
  else
  {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
    if (HAL_XSPI_IsActiveFlag(hxspi, HAL_XSPI_FLAG_TE) != HAL_XSPI_FLAG_NOT_ACTIVE)
    {
      hxspi->last_error_codes = HAL_XSPI_ERROR_TRANSFER;
    }
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

    return HAL_TIMEOUT;
  }

  return HAL_OK;
}

/**
  * @brief  Abort the current transmission.
  * @param  hxspi       Pointer to XSPI handle.
  * @param  timeout_ms  Timeout duration.
  * @retval HAL_TIMEOUT In case of user timeout.
  * @retval HAL_OK      Operation completed.
  */
static hal_status_t XSPI_Abort(hal_xspi_handle_t *hxspi, uint32_t timeout_ms)
{
#if defined(USE_HAL_XSPI_DMA) && (USE_HAL_XSPI_DMA == 1)
  if ((XSPI_GET_INSTANCE(hxspi)->CR & XSPI_CR_DMAEN) != 0U)
  {
    /* Disable the DMA transfer on the XSPI side */
    CLEAR_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_DMAEN);

    if (READ_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_FMODE) == XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE)
    {
      /* Disable the DMA transmit on the DMA side */
      if (HAL_DMA_Abort(hxspi->p_dma_tx) != HAL_OK)
      {
        return HAL_ERROR;
      }
    }
    else
    {
      /* Disable the DMA receive on the DMA side */
      if (HAL_DMA_Abort(hxspi->p_dma_rx) != HAL_OK)
      {
        return HAL_ERROR;
      }
    }
  }
#endif /* USE_HAL_XSPI_DMA */

  if (HAL_XSPI_IsActiveFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY) != HAL_XSPI_FLAG_NOT_ACTIVE)
  {
    /* Perform an abort of the XSPI */
    SET_BIT(XSPI_GET_INSTANCE(hxspi)->CR, XSPI_CR_ABORT);

    /* Wait until the transfer complete flag is set to go back in idle state */
    if (XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_TC, HAL_XSPI_FLAG_ACTIVE,
                                       timeout_ms) == HAL_OK)
    {
      /* Clear transfer complete flag */
      HAL_XSPI_ClearFlag(hxspi, (uint32_t)HAL_XSPI_FLAG_TC);

      /* Wait until the busy flag is reset to go back in idle state */
      if (XSPI_WaitFlagStateUntilTimeout(hxspi, (uint32_t)HAL_XSPI_FLAG_BUSY, HAL_XSPI_FLAG_NOT_ACTIVE,
                                         timeout_ms) != HAL_OK)
      {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
        if (HAL_XSPI_IsActiveFlag(hxspi, HAL_XSPI_FLAG_TE) != HAL_XSPI_FLAG_NOT_ACTIVE)
        {
          hxspi->last_error_codes = HAL_XSPI_ERROR_TRANSFER;
        }
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */

        return HAL_TIMEOUT;
      }
    }
    else
    {
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
      if (HAL_XSPI_IsActiveFlag(hxspi, HAL_XSPI_FLAG_TE) != HAL_XSPI_FLAG_NOT_ACTIVE)
      {
        hxspi->last_error_codes = HAL_XSPI_ERROR_TRANSFER;
      }
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */
      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

/**
  * @}
  */

#endif /* USE_HAL_XSPI_MODULE */

#endif /* HSPI1 || OCTOSPI1 || OCTOSPI2 */
/**
  * @}
  */

/**
  * @}
  */
