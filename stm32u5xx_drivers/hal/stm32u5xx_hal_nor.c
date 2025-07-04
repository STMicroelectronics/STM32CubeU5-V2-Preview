/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_nor.c
  * @brief   NOR HAL module driver.
  *          This file provides a generic firmware to drive NOR memories mounted as external device.
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

#if defined (FMC_NORSRAM_BK1)

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup NOR
  * @{

# How to use the NOR HAL module driver

## The FMC NOR main features :

This NOR HAL driver is a generic driver which contains a set of APIs used to configure the FMC NOR sub-banks and to
interface with CFI (Common Flash Interface) compliant 16-bits NOR memories with these commands set ID :
  - Command Set ID 0001.
  - Command Set ID 0002.
  - Command Set ID 0003.

The FMC NOR peripheral supports the following read and write access modes :

   - Asynchronous read and asynchronous write with identical timing for both operations.
   - Asynchronous read and asynchronous write with distinct timing for each operation.
   - Synchronous read and asynchronous write.

The FMC NOR peripheral supports the write protection feature.

## The NOR HAL driver can be used as follows :

This module provides 6 different sets of APIs that allows to :

- Initialize and deinitialize the logical FMC NOR object (hal_nor_handle_t) :
  - Initialize the logical FMC NOR object and associate it to a physical instance (sub-bank).
    This functionality is ensured by HAL_NOR_Init() function.
  - Deinitialize the logical FMC NOR object and disable the NOR sub-bank.
    This functionality is ensured by HAL_NOR_DeInit() function.

- Configure the FMC NOR to be ready to use and retrieve the current configuration :

  - Configure the FMC NOR through three steps by following the order below :

    - Step 1 (FMC configuration) : is the first step to perform once the HAL NOR driver is initialized.
      This functionality is ensured by HAL_NOR_SetConfig() function.

      At this stage, the NOR is partially configured but not yet ready to use.

    - Step 2 (Memory configuration) : is the second step to perform once the FMC is initialized.
      This functionality is ensured by one of these 5 functions depending on the external device access mode :
      - HAL_NOR_SetConfigRdWrAsyncMemory() function to set the configuration for memories with asynchronous read and
        asynchronous write access mode. This API sets identical timing for both aceesses.
      - HAL_NOR_SetWrAsyncTimings() function to be called after HAL_NOR_SetConfigRdWrAsyncMemory(), when memory with
        asynchronous read and asynchronous write access mode requires a different timing configuration for write
        transactions.
      - HAL_NOR_SetConfigRdSyncWrAsyncMemory() function to set the configuration for memories with synchronous read and
        asynchronous write access mode.

        At this stage, the NOR is fully configured but not yet ready to use.

    - Step 3 (Memory enable/disable) : is the third step to perform once the NOR is fully configured.
      This functionality is ensured by HAL_NOR_EnableMemory() and HAL_NOR_DisableMemory() functions.
      - HAL_NOR_EnableMemory() : function to enable the NOR sub-bank and make it accessible for read and write
        operations.
      - HAL_NOR_DisableMemory() : function to disable the NOR sub-bank which is useful when memory configuration
        adjustments are needed. After making the necessary adjustments, the HAL_NOR_EnableMemory() must be recalled to
        enable the memory and make it accessible.

        At this stage, the NOR is fully configured, enabled and ready for use.

  - Retrieve the current configuration through the following functions :

    - Retrieve the FMC configuration :
      This functionality is ensured by HAL_NOR_GetConfig().

    - Retrieve the memory configuration :
      This functionality is ensured by one of these 3 functions depending on the external device access mode :
      - HAL_NOR_GetConfigRdWrAsyncMemory() function to get the memory configuration for memories with asynchronous read
        and asynchronous write access mode.
      - HAL_NOR_GetWrAsyncTimings() function to get the timing configuration for write operations, when the memory with
        asynchronous read and asynchronous write access mode has a different timing configuration for write
        transactions.
      - HAL_NOR_GetConfigRdSyncWrAsyncMemory() function to get the memory configuration for memories with synchronous
        read and asynchronous write access mode.

- Interface with CFI compliant 16-bits NOR memories :

  - Retrieve the CFI query data structure that provides all the necessary information for controlling the NOR memory
    operations.
    This functionality is ensured by these two common APIs; used for all CFI compliant NOR memory regardless their
    command set ID :
    - HAL_NOR_CFI_ReadDeviceInfo() function to retrieve NOR flash CFI information.
    - HAL_NOR_CFI_ReadDeviceRegionInfo() function to retrieve the NOR flash erase block region information.

  - Control the NOR memory input and output access operations.
    This functionality is ensured by these 3 sets of APIs depending on the command set ID :

    - Command set ID 0001 :
      - HAL_NOR_CFI_0001_Reset() function to reset the NOR flash device.
      - HAL_NOR_CFI_0001_ReadArray() function to read data from the NOR flash memory.
      - HAL_NOR_CFI_0001_ReadDeviceIdentifier() function to read NOR flash memory identifier.
      - HAL_NOR_CFI_0001_ReadStatusRegister() function to read the NOR flash memory operation status.
      - HAL_NOR_CFI_0001_ClearStatusRegister() function to clear the NOR flash memory status register.
      - HAL_NOR_CFI_0001_Program() function to write data to the NOR flash memory.
      - HAL_NOR_CFI_0001_BufferedProgram() function to write a buffer of data to the NOR flash memory.
      - HAL_NOR_CFI_0001_BufferedEnhancedFactoryProgram() function to  write a buffer of data to the NOR flash memory
        using an enhanced programming algorithm.
      - HAL_NOR_CFI_0001_BlockErase() function to erase a specified block of the NOR flash memory.
      - HAL_NOR_CFI_0001_ProgramSuspend() function to suspend the programming operation of the NOR flash memory.
      - HAL_NOR_CFI_0001_EraseSuspend() function to suspend the block erase operation of the NOR flash memory.
      - HAL_NOR_CFI_0001_ProgramResume() function to resume the programming operation of the NOR flash memory.
      - HAL_NOR_CFI_0001_EraseResume() function to resume the block erase operation of the NOR flash memory.
      - HAL_NOR_CFI_0001_BlockLock() function to lock a specified block of the NOR flash memory.
      - HAL_NOR_CFI_0001_BlockUnlock() function to unlock a specified block of the NOR flash memory.
      - HAL_NOR_CFI_0001_BlockLockDown() function to lock-down a specified block of the NOR flash memory.
      - HAL_NOR_CFI_0001_ConfigureReadConfigurationRegister() function to modify the configuration register of the NOR
        flash memory.
      - HAL_NOR_CFI_0001_BlockBlankCheck() function to check whether a specified main block of the NOR flash memory is
        completely erased.
      - HAL_NOR_CFI_0001_ProgramProtectionRegister() function to program any of the protection registers of the NOR
        flash memory.
      - HAL_NOR_CFI_0001_ProgramLockRegister() function to lock any of the protection register of the NOR flash memory.

    - Command set ID 0002 :
      - HAL_NOR_CFI_0002_Reset() function to reset the NOR flash device.
      - HAL_NOR_CFI_0002_Read() function to read data from the NOR flash memory.
      - HAL_NOR_CFI_0002_ReadDeviceIdentifier() function to read NOR flash memory identifier.
      - HAL_NOR_CFI_0002_ReadStatusRegister() function to read the NOR flash memory operation status.
      - HAL_NOR_CFI_0002_UnlockBypass() function to activate the Unlock Bypass mode.
      - HAL_NOR_CFI_0002_UnlockBypassReset() function to reset the unlock bypass mode.
      - HAL_NOR_CFI_0002_Program() function to write data to the NOR flash memory.
      - HAL_NOR_CFI_0002_UnlockBypassProgram() function to write data to the NOR flash memory in the Unlock Bypass mode.
      - HAL_NOR_CFI_0002_DoubleDataProgram() function to write double adjacent data to the NOR flash memory.
      - HAL_NOR_CFI_0002_QuadrupleDataProgram() function to write four adjacent data to the NOR flash memory
      - HAL_NOR_CFI_0002_BufferedProgram() function to write a buffer of data to the NOR flash memory.
      - HAL_NOR_CFI_0002_EnhancedBufferedProgram() function to write a buffer of data to the NOR flash memory using
        an enhanced programming algorithm.
      - HAL_NOR_CFI_0002_UnlockBypassBufferedProgram() function to write a buffer of data to the NOR flash memory in the
        Unlock Bypass mode.
      - HAL_NOR_CFI_0002_EnhancedUnlockBypassBufferedProgram() function to write a buffer of data to the NOR flash
        memory in the Unlock Bypass mode, using an enhanced programming algorithm.
      - HAL_NOR_CFI_0002_ProgramSuspend() function to suspend the programming operation of the NOR flash memory.
      - HAL_NOR_CFI_0002_EraseSuspend() function to suspend the block erase operation of the NOR flash memory.
      - HAL_NOR_CFI_0002_ProgramResume() function to resume the programming operation of the NOR flash memory.
      - HAL_NOR_CFI_0002_EraseResume() function to resume the block erase operation of the NOR flash memory.
      - HAL_NOR_CFI_0002_ChipErase() function to erase the entire NOR flash memory.
      - HAL_NOR_CFI_0002_ChipEraseUnlockBypass() function to erase the entire NOR chip in the Unlock Bypass mode.
      - HAL_NOR_CFI_0002_BlockErase() function to erase a specified block of the NOR flash memory.
      - HAL_NOR_CFI_0002_BlockEraseUnlockBypass() function to erase a specified block of the NOR flash memory
        in the Unlock Bypass mode.
      - HAL_NOR_CFI_0002_BlockBlankCheck() function to check whether a specified main block of the NOR flash memory
        is completely erased.

    - Command set ID 0003 :
      - HAL_NOR_CFI_0003_Reset() function to reset the NOR flash device.
      - HAL_NOR_CFI_0003_ReadArray() function to read data from the NOR flash memory.
      - HAL_NOR_CFI_0003_ReadDeviceIdentifier() function to read NOR flash memory identifier.
      - HAL_NOR_CFI_0003_ReadStatusRegister() function to read the NOR flash memory operation status.
      - HAL_NOR_CFI_0003_ClearStatusRegister() function to clear the NOR flash memory status register.
      - HAL_NOR_CFI_0003_Program() function to write data to the NOR flash memory.
      - HAL_NOR_CFI_0003_DoubleDataProgram() function to write double adjacent data to the NOR flash memory.
      - HAL_NOR_CFI_0003_QuadrupleDataProgram() function to write four adjacent data to the NOR flash memory.
      - HAL_NOR_CFI_0003_BlockErase() function to erase a specified block of the NOR flash memory.
      - HAL_NOR_CFI_0003_ProgramSuspend() function to suspend the programming operation of the NOR flash memory.
      - HAL_NOR_CFI_0003_EraseSuspend() function to suspend the block erase operation of the NOR flash memory.
      - HAL_NOR_CFI_0003_ProgramResume() function to resume the programming operation of the NOR flash memory.
      - HAL_NOR_CFI_0003_EraseResume() function to resume the block erase operation of the NOR flash memory.
      - HAL_NOR_CFI_0003_BlockLock() function to lock a specified block of the NOR flash memory.
      - HAL_NOR_CFI_0003_BlockLockDown() function to lock-down a specified block of the NOR flash memory.
      - HAL_NOR_CFI_0003_BlockUnlock() function to unlock a specified block of the NOR flash memory.
      - HAL_NOR_CFI_0003_ProgramProtectionRegister() function to program any of the protection registers of the NOR
        flash memory.

- Manage the FMC NOR peripheral access :

  - Enable the FMC NOR write protection (when disabled) to prevent any write access to the external device.
    This functionality is ensured by HAL_NOR_EnableWriteProtection() function.

  - Disable the FMC NOR write protection (when enabled) to allow any write access to the external device.
    This functionality is ensured by HAL_NOR_DisableWriteProtection() function.

  - Retrieve the FMC NOR sub-bank write protection state.
    This functionality is ensured by HAL_NOR_IsEnabledWriteProtection() function.

  - Enable the FMC NOR sub-bank (when disabled).
    This functionality is ensured by HAL_NOR_Enable() function.

  - Disable the FMC NOR sub-bank (when enabled).
    This functionality is ensured by HAL_NOR_Disable() function.

  - Retrieve the FMC NOR sub-bank state.
    This functionality is ensured by HAL_NOR_IsEnabled() function.

- Store and retrieve user data :

  - Store user data pointer into the handle.
    This functionality is ensured by HAL_NOR_SetUserData() function.

  - Retrieve user data pointer from the handle.
    This functionality is ensured by HAL_NOR_GetUserData() function.

- Retrieve the HAL NOR state and clock frequency :

  - Retrieve the HAL NOR state.
    This functionality is ensured by HAL_NOR_GetState() function.

  - Retrieve the clock frequency.
    This functionality is ensured by HAL_NOR_GetClockFreq() function.

## Configuration inside the NOR driver

Config defines               | Description     | Default value     | Note
-------------------------    | --------------- | ----------------- | ---------------------------------------------------
USE_ASSERT_DBG_PARAM         | from IDE        | NA                | Allows to use the assert check parameters.
USE_ASSERT_DBG_STATE         | from IDE        | NA                | Allows to use the assert check states.
USE_HAL_CHECK_PARAM          | from hal_conf.h | 0U                | Allows to use the run-time check parameters.
USE_HAL_CHECK_PROCESS_STATE  | from hal_conf.h | 0U                | Allows to ensure a safe state transition.
USE_HAL_NOR_MODULE           | from hal_conf.h | 1U                | Allows to use the HAL NOR module.
USE_HAL_NOR_PROTECTION       | from hal_conf.h | 0U                | Allows to enable program protection register.
USE_FMC_CLK_ENABLE_MODEL     | from hal_conf.h | HAL_CLK_ENABLE_NO | Allows to enable the FMC clock.
USE_HAL_NOR_USER_DATA        | from hal_conf.h | 0U                | Allows to use user data.
  */

#if defined(USE_HAL_NOR_MODULE) && (USE_HAL_NOR_MODULE == 1U)

/* Private constant --------------------------------------------------------------------------------------------------*/
/** @defgroup NOR_Private_Constants NOR Private Constants
  * @{
  */
/* Constant to define address for NOR memory CFI query command */
#define NOR_CFI_ADDR                                0x0055U      /*!< CFI entry address                          */

/* Constants to define addresses for CFI query structure */
#define NOR_CFI_ADDR_DEVICE_SUPPLY_MIN              0x001BU /*!< Vcc minimum logic supply voltage address        */
#define NOR_CFI_ADDR_DEVICE_SUPPLY_MAX              0x001CU /*!< Vcc maximum logic supply voltage address        */
#define NOR_CFI_ADDR_ERASE_PGM_SUPPLY_MIN           0x001DU /*!< Vpp minimum logic program/erase voltage address */
#define NOR_CFI_ADDR_ERASE_PGM_SUPPLY_MAX           0x001EU /*!< Vpp maximum logic program/erase voltage address */
#define NOR_CFI_ADDR_PGM_TIMEOUT                    0x001FU /*!< Typical timeout for program address             */
#define NOR_CFI_ADDR_BUFFER_PGM_TIMEOUT             0x0020U /*!< Typical timeout for buffer program address      */
#define NOR_CFI_ADDR_BLOCK_ERASE_TIMEOUT            0x0021U /*!< Typical timeout for block erase address         */
#define NOR_CFI_ADDR_FULL_ERASE_TIMEOUT             0x0022U /*!< Typical timeout for full chip erase address     */
#define NOR_CFI_ADDR_MAX_PGM_TIMEOUT                0x0023U /*!< Maximum timeout for program address             */
#define NOR_CFI_ADDR_MAX_BUFFER_PGM_TIMEOUT         0x0024U /*!< Maximum timeout for buffer program address      */
#define NOR_CFI_ADDR_MAX_BLOCK_ERASE_TIMEOUT        0x0025U /*!< Maximum timeout for block erase address         */
#define NOR_CFI_ADDR_MAX_FULL_ERASE_TIMEOUT         0x0026U /*!< Maximum timeout for full chip erase address     */
#define NOR_CFI_ADDR_DEVICE_SIZE_BYTE               0x0027U /*!< Device size address                             */
#define NOR_CFI_ADDR_MAX_BUFFER_BYTE                0x002AU /*!< Maximum bytes number in buffer program address  */
#define NOR_CFI_ADDR_CMD_SET                        0x0013U /*!< Primary command set address                     */
#define NOR_CFI_ADDR_PRIMARY_TABLE                  0x0015U /*!< Address for primary algorithm query address     */
#define NOR_CFI_ADDR_ALTERNATE_CMD_SET              0x0017U /*!< Alternate algorithm address                     */
#define NOR_CFI_ADDR_SECONDARY_TABLE                0x0019U /*!< Address for secondary algorithm query address   */
#define NOR_CFI_ADDR_DEVICE_INTERFACE_CODE          0x0028U /*!< Device interface address                        */
#define NOR_CFI_ADDR_QUERY_UNIQUE                   0x0010U /*!< Query unique ASCII string address               */
#define NOR_CFI_ADDR_ERASE_BLOCK_REGION_NB          0x002CU /*!< Number of erase block region address            */
#define NOR_CFI_ADDR_REGION_INFO                    0x002DU /*!< Region Information address                      */

/* NOR device IDs addresses */
#define NOR_CFI_ADDR_MANUFACTURER_CODE              0x0000U /*!< Manufacturer code address                       */
#define NOR_CFI_ADDR_DEVICE_CODE_1                  0x0001U /*!< Device code 1 address                           */
#define NOR_CFI_ADDR_DEVICE_CODE_2                  0x000EU /*!< Device code 2 address address                   */
#define NOR_CFI_ADDR_DEVICE_CODE_3                  0x000FU /*!< Device code 3 address address                   */
#define NOR_CFI_ADDR_DEVICE_INDICATOR_BITS          0x0003U /*!< Indicator bits address                          */


/* Mask on NOR STATUS REGISTER */
#define NOR_CFI_DQ0_MASK                            0x0001U /*!< NOR status DQ0 mask                             */
#define NOR_CFI_DQ4_MASK                            0x0010U /*!< NOR status DQ4 mask                             */
#define NOR_CFI_DQ5_MASK                            0x0020U /*!< NOR status DQ5 mask                             */
#define NOR_CFI_DQ6_MASK                            0x0040U /*!< NOR status DQ6 mask                             */
#define NOR_CFI_DQ7_MASK                            0x0080U /*!< NOR status DQ7 mask                             */

/* Constants to define data for common NOR memory commands */
#define NOR_CFI_CMD                                 0x0098U /*!< CFI entry command data                          */
#define NOR_CFI_CMD_READ_DEVICE_ID                  0x0090U /*!< Read device identifier command data             */

/* Constants to define data for NOR memory Command set 1 */
#define NOR_CFI_0001_CMD_READ_ARRAY                 0x00FFU /*!< Read array command data                         */
#define NOR_CFI_0001_CMD_READ_STATUS_REG            0x0070U /*!< Read status register command data               */
#define NOR_CFI_0001_CMD_CLEAR_STATUS_REG           0x0050U /*!< Clear status register command data              */
#define NOR_CFI_0001_CMD_PGM                        0x0040U /*!< Program command data                            */
#define NOR_CFI_0001_CMD_BUFFERED_PGM               0x00E8U /*!< Buffered program command data                   */
#define NOR_CFI_0001_CMD_CONFIRM                    0x00D0U /*!< Confirm command data                            */
#define NOR_CFI_0001_CMD_BEFP_SETUP                 0x0080U /*!< BEFP setup command data                         */
#define NOR_CFI_0001_CMD_BLOCK_ERASE_SETUP          0x0020U /*!< Block erase setup command data                  */
#define NOR_CFI_0001_CMD_SUSPEND                    0x00B0U /*!< Suspend command data                            */
#define NOR_CFI_0001_CMD_BLOCK_LOCK_SETUP           0x0060U /*!< Block lock setup command data                   */
#define NOR_CFI_0001_CMD_BLOCK_LOCK                 0x0001U /*!< Block lock command data                         */
#define NOR_CFI_0001_CMD_BLOCK_UNLOCK               0x00D0U /*!< Block unlock command data                       */
#define NOR_CFI_0001_CMD_BLOCK_LOCK_DOWN            0x002FU /*!< Block lock down command data                    */
#define NOR_CFI_0001_CMD_PROTECTION_PGM_SETUP       0x00C0U /*!< Protection program setup command data           */
#define NOR_CFI_0001_CMD_BLOCK_BLANK_CHECK          0x00BCU /*!< Blank check command data                        */
#define NOR_CFI_0001_CMD_READ_CONFIG_REG_SETUP      0x0060U /*!< Read configuration register setup command data  */
#define NOR_CFI_0001_CMD_READ_CONFIG_REG            0x0003U /*!< Read configuration register command data        */

/* Constant to define addresses for NOR memory commands */
#define NOR_CFI_0002_ADDR_FIRST                     0x0555U /*!< First cycle address                             */
#define NOR_CFI_0002_ADDR_SECOND                    0x02AAU /*!< Second cycle address                            */
#define NOR_CFI_0002_ADDR_THIRD                     0x0555U /*!< Third cycle address                             */

/* Constants to define data for NOR memory Command set 2 */
#define NOR_CFI_0002_CMD_UNLOCK_FIRST               0x00AAU /*!< First unlock cycle command data                 */
#define NOR_CFI_0002_CMD_UNLOCK_SECOND              0x0055U /*!< Second unlock cycle command data                */
#define NOR_CFI_0002_CMD_RESET                      0x00F0U /*!< Reset command data                              */
#define NOR_CFI_0002_CMD_UNLOCK_BYPASS              0x0020U /*!< Unlock bypass command data                      */
#define NOR_CFI_0002_CMD_UNLOCK_BYPASS_RESET_FIRST  0x0090U /*!< Unlock bypass reset first cycle command data    */
#define NOR_CFI_0002_CMD_UNLOCK_BYPASS_RESET_SECOND 0x0000U /*!< Unlock bypass reset second command data         */
#define NOR_CFI_0002_CMD_DATA_PGM                   0x00A0U /*!< Program command data                            */
#define NOR_CFI_0002_CMD_DOUBLE_PGM                 0x0050U /*!< Double data program command data                */
#define NOR_CFI_0002_CMD_QUADRUPLE_PGM              0x0056U /*!< Quadruple data program command data             */
#define NOR_CFI_0002_CMD_BUFFER_PGM                 0x0025U /*!< Buffer program command data                     */
#define NOR_CFI_0002_CMD_CONFIRM                    0x0029U /*!< Confirm command data                            */
#define NOR_CFI_0002_CMD_ENHANCED_BUFFER_PGM        0x0033U /*!< Enhanced buffer program command data            */
#define NOR_CFI_0002_CMD_UNLOCK_BYPASS_BUFFER_PGM   0x0025U /*!< Unlock bypass buffer program command data       */
#define NOR_CFI_0002_CMD_SUSPEND                    0x00B0U /*!< Suspend command data                            */
#define NOR_CFI_0002_CMD_RESUME                     0x0030U /*!< Resume command data                             */
#define NOR_CFI_0002_CMD_ERASE_SETUP                0x0080U /*!< Erase setup command data                        */
#define NOR_CFI_0002_CMD_CHIP_ERASE                 0x0010U /*!< Chip erase command data                         */
#define NOR_CFI_0002_CMD_BLOCK_ERASE                0x0030U /*!< Block erase command data                        */
#define NOR_CFI_0002_CMD_BLANK_CHECK_SETUP_FIRST    0x00EBU /*!< First blank check setup command data            */
#define NOR_CFI_0002_CMD_BLANK_CHECK_SETUP_SECOND   0x0076U /*!< Second blank check setup command data           */
#define NOR_CFI_0002_CMD_BLANK_CHECK_SETUP_THIRD    0x0000U /*!< Third blank check setup command data            */
#define NOR_CFI_0002_CMD_BLANK_CHECK_SETUP_FOURTH   0x0000U /*!< Fourth blank check setup command data           */

/* Constants to define data for NOR memory Command set 3 */
#define NOR_CFI_0003_CMD_READ_ARRAY                 0x00FFU /*!< Read array command data                         */
#define NOR_CFI_0003_CMD_READ_STATUS_REG            0x0070U /*!< Read status register command data               */
#define NOR_CFI_0003_CMD_CLEAR_STATUS_REG           0x0050U /*!< Clear status register command data              */
#define NOR_CFI_0003_CMD_PGM                        0x0040U /*!< Program command data                            */
#define NOR_CFI_0003_CMD_DOUBLE_PGM                 0x0030U /*!< Double data program command data                */
#define NOR_CFI_0003_CMD_QUADRPLE_PGM               0x0056U /*!< Quadruple command data                          */
#define NOR_CFI_0003_CMD_BLOCK_ERASE_SETUP          0x0020U /*!< Block erase setup command data                  */
#define NOR_CFI_0003_CMD_CONFIRM                    0x00D0U /*!< Confirm command data                            */
#define NOR_CFI_0003_CMD_SUSPEND                    0x00B0U /*!< Suspend command data                            */
#define NOR_CFI_0003_CMD_BLOCK_LOCK_SETUP           0x0060U /*!< Block lock setup command data                   */
#define NOR_CFI_0003_CMD_BLOCK_LOCK                 0x0001U /*!< Block lock command data                         */
#define NOR_CFI_0003_CMD_BLOCK_LOCK_DOWN            0x002FU /*!< Block lock down command data                    */
#define NOR_CFI_0003_CMD_PROTECTION_PGM_SETUP       0x00C0U /*!< Protection program setup command data           */

/* Constants to define the status latency */
#define NOR_STATUS_LATENCY                          0x0002U /*!< Status latency                                  */
/**
  * @}
  */

/* Private macro -----------------------------------------------------------------------------------------------------*/
/** @defgroup NOR_Private_Macros NOR Private Macros
  * @{
  */
/*! Check the data address multiplexing parameter */
#define IS_NOR_MUX(mux) (((mux) == HAL_NOR_MUX_DATA_ADDR_DISABLE) \
                         || ((mux) == HAL_NOR_MUX_DATA_ADDR_ENABLE))

/*! Check the write fifo parameter */
#define IS_NOR_WRITE_FIFO(fifo) (((fifo) == HAL_NOR_WRITE_FIFO_DISABLE) \
                                 || ((fifo) == HAL_NOR_WRITE_FIFO_ENABLE))

/*! Check the byte lane parameter */
#define IS_NOR_NBL_SETUPTIME(nbl) (((nbl) == HAL_NOR_BYTE_SRC_CLK_0_CYCLE)    \
                                   || ((nbl) == HAL_NOR_BYTE_SRC_CLK_1_CYCLE) \
                                   || ((nbl) == HAL_NOR_BYTE_SRC_CLK_2_CYCLE) \
                                   || ((nbl) == HAL_NOR_BYTE_SRC_CLK_3_CYCLE))

/*! Check the wait signal polarity parameter */
#define IS_NOR_WAIT_POLARITY(polarity) (((polarity) == HAL_NOR_WAIT_SIGNAL_POLARITY_LOW) \
                                        || ((polarity) == HAL_NOR_WAIT_SIGNAL_POLARITY_HIGH))

/*! Check the synchronous wait signal state parameter */
#define IS_NOR_SYNC_WAIT_SIGNAL(signal) (((signal) == HAL_NOR_SYNC_WAIT_SIGNAL_DISABLE) \
                                         || ((signal) == HAL_NOR_SYNC_WAIT_SIGNAL_ENABLE))

/*! Check the synchronous wait signal state configuration */
#define IS_NOR_SYNC_WAIT_SIGNAL_CONFIG(signal) (((signal) == HAL_NOR_WAIT_TIMING_CONFIG_BEFORE_WAITSTATE) \
                                                || ((signal) == HAL_NOR_WAIT_TIMING_CONFIG_DURING_WAITSTATE))

/*! Check the asynchronous wait signal state parameter */
#define IS_NOR_ASYNC_WAIT_SIGNAL(signal) (((signal) == HAL_NOR_ASYNC_WAIT_SIGNAL_DISABLE) \
                                          || ((signal) == HAL_NOR_ASYNC_WAIT_SIGNAL_ENABLE))

/*! Check the continuous clock parameter */
#define IS_NOR_CONTINOUS_CLOCK(clock) (((clock) == HAL_NOR_CONTINUOUS_CLOCK_SYNC_ONLY) \
                                       || ((clock) == HAL_NOR_CONTINUOUS_CLOCK_SYNC_ASYNC))

/*! Check the access mode parameter */
#define IS_NOR_ACCESS_MODE(mode) (((mode) == HAL_NOR_ACCESS_MODE_B) \
                                  || ((mode) == HAL_NOR_ACCESS_MODE_C))

/*! Check the offset parameter is 16-bits aligned */
#define IS_NOR_OFFSET_16_BITS_ALIGNED(offset) (((offset) % 2UL) == 0UL)

/*! Check the buffer size is 16-bits multiple */
#define IS_NOR_BUFFER_SIZE_16_BITS_MULTIPLE(size_byte) (((size_byte) % 2UL) == 0UL)

/*! Get the handle instance */
#define NOR_GET_INSTANCE(handle) ((fmc_norsram_subbank_t *)((uint32_t)(handle)->instance))
/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @defgroup NOR_Private_Functions NOR Private Functions
  * @{
  */
static hal_nor_device_state_t NOR_CFI_0001_ReadStatusRegister(const hal_nor_handle_t *hnor, uint32_t offset_byte);
static hal_nor_device_state_t NOR_CFI_0002_ReadStatusRegister(const hal_nor_handle_t *hnor, uint32_t offset_byte);
static hal_nor_device_state_t NOR_CFI_0003_ReadStatusRegister(const hal_nor_handle_t *hnor, uint32_t offset_byte);
static hal_status_t NOR_CFI_0001_PollForOperationStatus(hal_nor_handle_t *hnor, uint32_t offset_byte,
                                                        uint32_t timeout_ms);
static hal_status_t NOR_CFI_0002_PollForOperationStatus(hal_nor_handle_t *hnor, uint32_t offset_byte,
                                                        uint32_t timeout_ms);
static hal_status_t NOR_CFI_0003_PollForOperationStatus(hal_nor_handle_t *hnor, uint32_t offset_byte,
                                                        uint32_t timeout_ms);
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup NOR_Exported_Functions
  * @{
 */

/** @addtogroup NOR_Exported_Functions_Group1
  * @{
This subsection provides a set of functions allowing to initialize and deinitialize the NOR driver :
- The HAL_NOR_Init() API : allows to initialize the NOR handle and enable the peripheral clock when
  USE_FMC_CLK_ENABLE_MODEL is different from HAL_CLK_ENABLE_NO.
  In case of the USE_FMC_CLK_ENABLE_MODEL compilation is not defined or define to HAL_CLK_ENABLE_NO, the application
  needs to explicitly call the HAL RCC API HAL_RCC_FSMC_EnableClock() in order to enable the clock of FMC controller.

- The HAL_NOR_DeInit() API : allows to deinitialize the HAL NOR driver for the given handle and disable the write
  protection and the corresponding NOR sub-bank.
  */

/**
  * @brief  Initialize the NOR handle field and associate a physical instance.
  * @param  hnor              Pointer to a hal_nor_handle_t structure.
  * @param  instance          @ref hal_nor_t enumerated type variable to be set according to the physical instance.
  * @note   The FMC clock can be activated within the HAL_NOR_Init() function by setting the USE_FMC_CLK_ENABLE_MODEL
  *         flag to HAL_CLK_ENABLE_PERIPH_ONLY in the configuration file stm32u5xx_hal_conf.h or by explicitly
  *         calling the HAL_RCC_FSMC_EnableClock() API within the application when the USE_FMC_CLK_ENABLE_MODEL is not
  *         defined or defined to flag HAL_CLK_ENABLE_NO.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the NOR handle is NULL.
  * @retval HAL_OK            The HAL NOR driver is initialized according to the given handle and instance.
  */
hal_status_t HAL_NOR_Init(hal_nor_handle_t *hnor, hal_nor_t instance)
{
  ASSERT_DBG_PARAM(hnor != NULL);
  ASSERT_DBG_PARAM(IS_FMC_NORSRAM_ALL_INSTANCE((fmc_norsram_subbank_t *)(uint32_t)instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hnor == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hnor->instance = instance;

#if defined (USE_FMC_CLK_ENABLE_MODEL) && (USE_FMC_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_FSMC_EnableClock();
#endif /* USE_FMC_CLK_ENABLE_MODEL */

#if defined(USE_HAL_NOR_USER_DATA) && (USE_HAL_NOR_USER_DATA == 1U)
  hnor->p_user_data = NULL;
#endif /* USE_HAL_NOR_USER_DATA */

  hnor->wr_protection_state = HAL_NOR_WR_NOT_PROTECTED;

  hnor->global_state = HAL_NOR_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief Deinitialize the HAL NOR driver for the given handle and disable the write protection and the
  *        corresponding NOR sub-bank.
  * @param hnor Pointer to a hal_nor_handle_t structure.
  */
void HAL_NOR_DeInit(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);
  ASSERT_DBG_PARAM(IS_FMC_NORSRAM_ALL_INSTANCE(NOR_GET_INSTANCE(hnor)));

  FMC_NOR_SRAM_Disable(NOR_GET_INSTANCE(hnor));

  FMC_NOR_SRAM_DisableWriteProtection(NOR_GET_INSTANCE(hnor));

  hnor->wr_protection_state = HAL_NOR_WR_NOT_PROTECTED;

  hnor->global_state = HAL_NOR_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup NOR_Exported_Functions_Group2
  * @{
This subsection provides a set of functions allowing to configure the FMC NOR sub-banks and to retrieve the current
configuration.

The full configuration is done through three steps and following the order below :
- Step 1 (Static configuration of FMC peripheral) :
  - HAL_NOR_SetConfig() : used to apply the user static configuration of FMC peripheral specified within
                          @ref hal_nor_config_t structure.

- Step 2 (Memory configuration) :
  Depending on the external device, one of these APIs is called :
  - HAL_NOR_SetConfigRdWrAsyncMemory()     : used to apply the user memory configuration for memories with asynchronous
                                             read and asynchronous write access mode within
                                             @ref hal_nor_rd_wr_async_memory_config_t structure.
                                             @note when separate timing configuration for read and write transactions
                                             is needed, the HAL_NOR_SetWrAsyncTimings() API must be called after
                                             HAL_NOR_SetConfigRdWrAsyncMemory(), to set the write timing parameters.
                                             In this case, the HAL_NOR_SetConfigRdWrAsyncMemory() function sets timing
                                             only for read access.
  - HAL_NOR_SetWrAsyncTimings()            : used to apply a different timing configuration for write transactions, for
                                             memories with asynchronous read and asynchronous write access mode within
                                             @ref hal_nor_wr_async_timings_t structure.
  - HAL_NOR_SetConfigRdSyncWrAsyncMemory() : used to apply the user memory configuration for memories with synchronous
                                             read and asynchronous write access mode within
                                             @ref hal_nor_rd_sync_wr_async_memory_config_t structure.

- Step 3 (Memory enable/disable) :
  - HAL_NOR_EnableMemory()                 : used to enable the NOR sub-bank and make it accessible for read and write
                                             operations.
  - HAL_NOR_DisableMemory()                : used to disable the NOR sub-bank which is useful when memory configuration
                                             adjustments are needed.

The configuration parameters are retrieved through these APIs :
- Static configuration of FMC peripheral :
  - HAL_NOR_GetConfig() : used to retrieve the FMC configuration and to fill it into @ref hal_nor_config_t structure.

- Memory configuration :
  - HAL_NOR_GetConfigRdWrAsyncMemory()     : used to retrieve the user memory configuration for memories with
                                             asynchronous read and asynchronous write access mode and to fill it into
                                             @ref hal_nor_rd_wr_async_memory_config_t structure.
  - HAL_NOR_GetWrAsyncTimings()            : used to retrieve the user timing configuration for write operations, when
                                             the memory with asynchronous read and asynchronous write access mode has a
                                             different timing configuration for write transactions and to fill it into
                                             @ref hal_nor_wr_async_timings_t structure.
  - HAL_NOR_GetConfigRdSyncWrAsyncMemory() : used to retrieve the user memory configuration for memories with
                                             synchronous read and asynchronous write access mode and to fill it into
                                             @ref hal_nor_rd_sync_wr_async_memory_config_t structure.
  */

/**
  * @brief  Set the static configuration of FMC peripheral.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  p_config          Pointer to a @ref hal_nor_config_t structure.
  * @note   This API is the first API to call once the HAL NOR driver is initialized.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the configuration structure pointer is NULL.
  * @retval HAL_OK            The static FMC configuration is successfully configured.
  */
hal_status_t HAL_NOR_SetConfig(hal_nor_handle_t *hnor, const hal_nor_config_t *p_config)
{
  ASSERT_DBG_PARAM(hnor     != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_PARAM(IS_NOR_WRITE_FIFO(p_config->write_fifo));
  ASSERT_DBG_PARAM(IS_NOR_WAIT_POLARITY(p_config->wait_signal_polarity));

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_INIT);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_Disable();

  FMC_NOR_SRAM_SetConfig(NOR_GET_INSTANCE(hnor), ((uint32_t)p_config->write_fifo           |
                                                  (uint32_t)p_config->wait_signal_polarity |
                                                  FMC_MEMORY_TYPE_NOR | FMC_BCRx_FACCEN));

  hnor->global_state = HAL_NOR_STATE_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief Retrieve the static configuration of FMC peripheral.
  * @param hnor     Pointer to a @ref hal_nor_handle_t structure.
  * @param p_config Pointer to a @ref hal_nor_config_t structure filled with the retrieved static
  *                 FMC peripheral configuration.
  */
void HAL_NOR_GetConfig(const hal_nor_handle_t *hnor, hal_nor_config_t *p_config)
{
  uint32_t config;

  ASSERT_DBG_PARAM(hnor     != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_CONFIGURED |
                   (uint32_t)HAL_NOR_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_NOR_STATE_IDLE);

  FMC_NOR_SRAM_GetConfig(NOR_GET_INSTANCE(hnor), &config);

  p_config->write_fifo           = (hal_nor_write_fifo_t)(uint32_t)READ_BIT(config, FMC_BCR1_WFDIS);
  p_config->wait_signal_polarity = (hal_nor_wait_signal_polarity_t)(uint32_t)READ_BIT(config, FMC_BCRx_WAITPOL);
}

/**
  * @brief  Set the memory configuration for memories with asynchronous read and asynchronous write access mode.
  * @param  hnor              Pointer to a  @ref hal_nor_handle_t structure.
  * @param  p_config          Pointer to a  @ref hal_nor_rd_wr_async_memory_config_t structure.
  * @note   The first use of this API must be done after calling HAL_NOR_SetConfig() API for NOR memories then,
                              it can be reused multi-time to adjust memory configuration when needed.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the memory configuration structure pointer is NULL.
  * @retval HAL_OK            The memory is successfully configured.
  */
hal_status_t HAL_NOR_SetConfigRdWrAsyncMemory(hal_nor_handle_t *hnor,
                                              const hal_nor_rd_wr_async_memory_config_t *p_config)
{
  uint32_t timing_mask;
  uint32_t control_mask;
  uint32_t clock_freq = HAL_RCC_GetHCLKFreq();

  ASSERT_DBG_PARAM(hnor     != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_PARAM(IS_NOR_MUX(p_config->memory.mux_mode));
  ASSERT_DBG_PARAM(IS_NOR_NBL_SETUPTIME(p_config->memory.byte_lane_setup_cycle));
  ASSERT_DBG_PARAM(IS_NOR_ASYNC_WAIT_SIGNAL(p_config->timings.async_wait));
  ASSERT_DBG_PARAM(IS_FMC_ADDR_SETUP_TIME(FMC_ConvertNanosecondsToClockCycle
                                          (p_config->timings.access_timings.addr_setup_nsec, clock_freq)));
  ASSERT_DBG_PARAM(IS_FMC_ADDR_HOLD_TIME(FMC_ConvertNanosecondsToClockCycle
                                         (p_config->timings.access_timings.addr_hold_nsec, clock_freq)));
  ASSERT_DBG_PARAM(IS_FMC_DATASETUP_TIME(FMC_ConvertNanosecondsToClockCycle
                                         (p_config->timings.access_timings.data_setup_nsec, clock_freq)));
  ASSERT_DBG_PARAM(IS_FMC_DATAHOLD_DURATION_RW(FMC_ConvertNanosecondsToClockCycle
                                               (p_config->timings.access_timings.data_hold_nsec, clock_freq)));
  ASSERT_DBG_PARAM(IS_FMC_TURNAROUND_TIME(FMC_ConvertNanosecondsToClockCycle(p_config->timings.bus_turnaround_nsec,
                                                                             clock_freq)));

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_CONFIGURED | (uint32_t)HAL_NOR_STATE_MEMORY_CONFIGURED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Set configuration mask value */
  control_mask = (uint32_t)p_config->memory.mux_mode | (uint32_t)p_config->memory.byte_lane_setup_cycle |
                 (uint32_t)p_config->timings.async_wait | FMC_MEM_BUS_WIDTH_16_BIT;

  timing_mask = FMC_ConvertNanosecondsToClockCycle(p_config->timings.access_timings.addr_setup_nsec, clock_freq) |
                FMC_WRITE_FIELD
                ((FMC_ConvertNanosecondsToClockCycle(p_config->timings.access_timings.addr_hold_nsec,
                                                     clock_freq)), FMC_BTRx_ADDHLD_Msk, FMC_BTRx_ADDHLD_Pos)     |
                FMC_WRITE_FIELD
                ((FMC_ConvertNanosecondsToClockCycle(p_config->timings.access_timings.data_setup_nsec,
                                                     clock_freq)), FMC_BTRx_DATAST_Msk, FMC_BTRx_DATAST_Pos)     |
                FMC_WRITE_FIELD
                ((FMC_ConvertNanosecondsToClockCycle(p_config->timings.access_timings.data_hold_nsec,
                                                     clock_freq)), FMC_BTRx_DATAHLD_Msk, FMC_BTRx_DATAHLD_Pos)   |
                FMC_WRITE_FIELD
                (FMC_ConvertNanosecondsToClockCycle(p_config->timings.bus_turnaround_nsec, clock_freq) - 1U,
                 FMC_BTRx_BUSTURN_Msk, FMC_BTRx_BUSTURN_Pos) | FMC_BTRx_CLKDIV | FMC_BTRx_DATLAT;

  FMC_Disable();

  FMC_NOR_SRAM_SetConfigMemory(NOR_GET_INSTANCE(hnor), control_mask, 0U, timing_mask);

  FMC_Enable();

  hnor->global_state = HAL_NOR_STATE_MEMORY_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief Retrieve the memory configuration for memories with asynchronous read and asynchronous write access mode.
  * @param hnor     Pointer to a @ref hal_nor_handle_t structure.
  * @param p_config Pointer to a @ref hal_nor_rd_wr_async_memory_config_t structure filled with the retrieved memory
  *                 configuration.
  */
void HAL_NOR_GetConfigRdWrAsyncMemory(const hal_nor_handle_t *hnor, hal_nor_rd_wr_async_memory_config_t *p_config)
{
  uint32_t memory_cfg;
  uint32_t timing_cfg;
  uint32_t counter_cfg;
  uint32_t clock_freq = HAL_RCC_GetHCLKFreq();

  ASSERT_DBG_PARAM(hnor     != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_NOR_STATE_IDLE);

  /* Get configuration value */
  FMC_NOR_SRAM_GetConfigMemory(NOR_GET_INSTANCE(hnor), &memory_cfg, &counter_cfg, &timing_cfg);

  p_config->memory.mux_mode              = (hal_nor_mux_mode_t)(uint32_t)READ_BIT(memory_cfg, FMC_BCRx_MUXEN);
  p_config->memory.byte_lane_setup_cycle = (hal_nor_byte_lane_source_clock_cycle_t)(uint32_t)READ_BIT(memory_cfg,
                                           FMC_BCRx_NBLSET);
  p_config->timings.async_wait = (hal_nor_async_wait_signal_state_t)(uint32_t)READ_BIT(memory_cfg, FMC_BCRx_ASYNCWAIT);
  p_config->timings.access_timings.addr_setup_nsec = FMC_ConvertClockCycleToNanoseconds(READ_BIT(timing_cfg,
                                                     FMC_BTRx_ADDSET), clock_freq);
  p_config->timings.access_timings.addr_hold_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(timing_cfg,
                                                    FMC_BTRx_ADDHLD_Msk, FMC_BTRx_ADDHLD_Pos), clock_freq);
  p_config->timings.access_timings.data_setup_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(timing_cfg,
                                                     FMC_BTRx_DATAST_Msk, FMC_BTRx_DATAST_Pos), clock_freq);
  p_config->timings.access_timings.data_hold_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(timing_cfg,
                                                    FMC_BTRx_DATAHLD_Msk, FMC_BTRx_DATAHLD_Pos), clock_freq);
  p_config->timings.bus_turnaround_nsec = FMC_ConvertClockCycleToNanoseconds
                                          ((FMC_READ_FIELD(timing_cfg, FMC_BTRx_BUSTURN_Msk, FMC_BTRx_BUSTURN_Pos)
                                            + 1U), clock_freq);
}

/**
  * @brief  Set the timing configuration for asynchronous write transactions.
  * @param  hnor              Pointer to a  @ref hal_nor_handle_t structure.
  * @param  p_timings         Pointer to a  @ref hal_nor_wr_async_timings_t structure.
  * @note   When separate timing configuration for read and write transactions is needed, this API must be called after
  *         HAL_NOR_SetConfigRdWrAsyncMemory(), to set the write timing parameters, it can be reused multi-time
  *         to adjust timings for write transactions when needed.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the timing configuration structure pointer is NULL.
  * @retval HAL_OK            The timing is successfully configured.
  */
hal_status_t HAL_NOR_SetWrAsyncTimings(hal_nor_handle_t *hnor, const hal_nor_wr_async_timings_t *p_timings)
{
  uint32_t rd_access_mode_mask;
  uint32_t wr_timing_mask;
  uint32_t clock_freq = HAL_RCC_GetHCLKFreq();

  ASSERT_DBG_PARAM(hnor      != NULL);
  ASSERT_DBG_PARAM(p_timings != NULL);

  ASSERT_DBG_PARAM(IS_FMC_ADDR_SETUP_TIME(FMC_ConvertNanosecondsToClockCycle
                                          (p_timings->async_access_timings.addr_setup_nsec, clock_freq)));
  ASSERT_DBG_PARAM(IS_FMC_ADDR_HOLD_TIME(FMC_ConvertNanosecondsToClockCycle
                                         (p_timings->async_access_timings.addr_hold_nsec, clock_freq)));
  ASSERT_DBG_PARAM(IS_FMC_DATASETUP_TIME(FMC_ConvertNanosecondsToClockCycle
                                         (p_timings->async_access_timings.data_setup_nsec, clock_freq)));
  ASSERT_DBG_PARAM(IS_FMC_DATAHOLD_DURATION_W(FMC_ConvertNanosecondsToClockCycle
                                              (p_timings->async_access_timings.data_hold_nsec, clock_freq)));
  ASSERT_DBG_PARAM(IS_FMC_TURNAROUND_TIME(FMC_ConvertNanosecondsToClockCycle
                                          (p_timings->bus_turnaround_nsec, clock_freq)));
  ASSERT_DBG_PARAM(IS_NOR_ACCESS_MODE(p_timings->write_access_mode));
  ASSERT_DBG_PARAM(IS_NOR_ACCESS_MODE(p_timings->read_access_mode));

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_MEMORY_CONFIGURED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_timings == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Set timing mask values */
  wr_timing_mask = FMC_ConvertNanosecondsToClockCycle(p_timings->async_access_timings.addr_setup_nsec, clock_freq)  |
                   FMC_WRITE_FIELD
                   ((FMC_ConvertNanosecondsToClockCycle(p_timings->async_access_timings.addr_hold_nsec,
                                                        clock_freq)), FMC_BWTRx_ADDHLD_Msk, FMC_BWTRx_ADDHLD_Pos)   |
                   FMC_WRITE_FIELD
                   ((FMC_ConvertNanosecondsToClockCycle(p_timings->async_access_timings.data_setup_nsec,
                                                        clock_freq)), FMC_BWTRx_DATAST_Msk, FMC_BWTRx_DATAST_Pos)   |
                   FMC_WRITE_FIELD
                   ((FMC_ConvertNanosecondsToClockCycle(p_timings->async_access_timings.data_hold_nsec, clock_freq)
                     - 1U), FMC_BWTRx_DATAHLD_Msk, FMC_BWTRx_DATAHLD_Pos)                                           |
                   FMC_WRITE_FIELD
                   ((FMC_ConvertNanosecondsToClockCycle(p_timings->bus_turnaround_nsec, clock_freq) - 1U),
                    FMC_BWTRx_BUSTURN_Msk, FMC_BWTRx_BUSTURN_Pos)                                                   |
                   (uint32_t)p_timings->write_access_mode;

  rd_access_mode_mask = (uint32_t)p_timings->read_access_mode;

  FMC_Disable();

  FMC_NOR_SRAM_SetWrTiming(NOR_GET_INSTANCE(hnor), rd_access_mode_mask, wr_timing_mask);

  FMC_Enable();

  return HAL_OK;
}

/**
  * @brief Retrieve the timing configuration for asynchronous write transactions.
  * @param hnor      Pointer to a @ref hal_nor_handle_t structure.
  * @param p_timings Pointer to a @ref hal_nor_wr_async_timings_t structure.
  */
void HAL_NOR_GetWrAsyncTimings(const hal_nor_handle_t *hnor, hal_nor_wr_async_timings_t *p_timings)
{
  uint32_t rd_access_mode;
  uint32_t wr_timing_cfg;
  uint32_t clock_freq = HAL_RCC_GetHCLKFreq();

  ASSERT_DBG_PARAM(hnor      != NULL);
  ASSERT_DBG_PARAM(p_timings != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_NOR_STATE_IDLE);

  FMC_NOR_SRAM_GetWrTiming(NOR_GET_INSTANCE(hnor), &rd_access_mode, &wr_timing_cfg);

  p_timings->async_access_timings.addr_setup_nsec = FMC_ConvertClockCycleToNanoseconds(READ_BIT(wr_timing_cfg,
                                                    FMC_BWTRx_ADDSET), clock_freq);
  p_timings->async_access_timings.addr_hold_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(wr_timing_cfg,
                                                   FMC_BWTRx_ADDHLD_Msk, FMC_BWTRx_ADDHLD_Pos), clock_freq);
  p_timings->async_access_timings.data_setup_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(wr_timing_cfg,
                                                    FMC_BWTRx_DATAST_Msk, FMC_BWTRx_DATAST_Pos), clock_freq);
  p_timings->async_access_timings.data_hold_nsec = FMC_ConvertClockCycleToNanoseconds((FMC_READ_FIELD(wr_timing_cfg,
                                                   FMC_BWTRx_DATAHLD_Msk, FMC_BWTRx_DATAHLD_Pos) + 1U), clock_freq);
  p_timings->bus_turnaround_nsec = FMC_ConvertClockCycleToNanoseconds
                                   ((FMC_READ_FIELD(wr_timing_cfg, FMC_BWTRx_BUSTURN_Msk, FMC_BWTRx_BUSTURN_Pos) + 1U),
                                    clock_freq);
  p_timings->read_access_mode = (hal_nor_access_mode_t)rd_access_mode;
  p_timings->write_access_mode = (hal_nor_access_mode_t)(uint32_t)READ_BIT(wr_timing_cfg, FMC_BWTRx_ACCMOD);
}

/**
  * @brief  Set the memory configuration for memories with synchronous read and asynchronous write access mode.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  p_config          Pointer to a @ref hal_nor_rd_sync_wr_async_memory_config_t structure.
  * @note   The first use of this API must be done after calling HAL_NOR_SetConfig() API for NOR mories then,
  *                          it can be reused multi-time to adjust memory configuration when needed.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the memory configuration structure pointer is NULL.
  * @retval HAL_OK            The memory is successfully configured.
  */
hal_status_t HAL_NOR_SetConfigRdSyncWrAsyncMemory(hal_nor_handle_t *hnor,
                                                  const hal_nor_rd_sync_wr_async_memory_config_t *p_config)
{
  uint32_t control_mask;
  uint32_t timing_mask;
  uint32_t clk_period_mask;
  uint32_t clock_freq = HAL_RCC_GetHCLKFreq();

  ASSERT_DBG_PARAM(hnor     != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_PARAM(IS_NOR_MUX(p_config->memory.mux_mode));
  ASSERT_DBG_PARAM(IS_NOR_NBL_SETUPTIME(p_config->memory.byte_lane_setup_cycle));
  ASSERT_DBG_PARAM(IS_NOR_SYNC_WAIT_SIGNAL(p_config->timings.sync_protocol.wait_signal_state));
  ASSERT_DBG_PARAM(IS_NOR_SYNC_WAIT_SIGNAL_CONFIG(p_config->timings.sync_protocol.wait_timing_config));
  ASSERT_DBG_PARAM(IS_NOR_CONTINOUS_CLOCK(p_config->timings.sync_protocol.continuous_clock));
  ASSERT_DBG_PARAM(IS_FMC_CLK_DIV(FMC_ConvertNanosecondsToClockCycle(p_config->timings.sync_protocol.clk_period_nsec,
                                                                     clock_freq)));
  ASSERT_DBG_PARAM(IS_FMC_DATA_LATENCY(FMC_ConvertNanosecondsToClockCycle(
                                         p_config->timings.sync_protocol.data_latency_nsec, clock_freq)));
  ASSERT_DBG_PARAM(IS_NOR_ASYNC_WAIT_SIGNAL(p_config->timings.async_wait));
  ASSERT_DBG_PARAM(IS_FMC_ADDR_SETUP_TIME(FMC_ConvertNanosecondsToClockCycle
                                          (p_config->timings.async_access_timings.addr_setup_nsec, clock_freq)));
  ASSERT_DBG_PARAM(IS_FMC_ADDR_HOLD_TIME(FMC_ConvertNanosecondsToClockCycle
                                         (p_config->timings.async_access_timings.addr_hold_nsec, clock_freq)));
  ASSERT_DBG_PARAM(IS_FMC_DATASETUP_TIME(FMC_ConvertNanosecondsToClockCycle
                                         (p_config->timings.async_access_timings.data_setup_nsec, clock_freq)));
  ASSERT_DBG_PARAM(IS_FMC_DATAHOLD_DURATION_W(FMC_ConvertNanosecondsToClockCycle
                                              (p_config->timings.async_access_timings.data_hold_nsec, clock_freq)));
  ASSERT_DBG_PARAM(IS_FMC_TURNAROUND_TIME(FMC_ConvertNanosecondsToClockCycle(p_config->timings.bus_turnaround_nsec,
                                                                             clock_freq)));

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_CONFIGURED | (uint32_t)HAL_NOR_STATE_MEMORY_CONFIGURED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Set configuration mask value */
  control_mask = (uint32_t) p_config->memory.mux_mode                          |
                 (uint32_t) p_config->memory.byte_lane_setup_cycle             |
                 (uint32_t) p_config->timings.sync_protocol.continuous_clock   |
                 (uint32_t) p_config->timings.sync_protocol.wait_signal_state  |
                 (uint32_t) p_config->timings.sync_protocol.wait_timing_config |
                 (uint32_t) p_config->timings.async_wait | FMC_BCRx_BURSTEN | FMC_MEM_BUS_WIDTH_16_BIT;

  clk_period_mask = FMC_WRITE_FIELD
                    ((FMC_ConvertNanosecondsToClockCycle(p_config->timings.sync_protocol.clk_period_nsec, clock_freq)
                      - 1U), FMC_BTRx_CLKDIV_Msk, FMC_BTRx_CLKDIV_Pos);

  timing_mask = (FMC_ConvertNanosecondsToClockCycle(p_config->timings.async_access_timings.addr_setup_nsec,
                                                    clock_freq)                                                        |
                 FMC_WRITE_FIELD(FMC_ConvertNanosecondsToClockCycle
                                 (p_config->timings.async_access_timings.addr_hold_nsec, clock_freq),
                                 FMC_BTRx_ADDHLD_Msk, FMC_BTRx_ADDHLD_Pos)                                             |
                 FMC_WRITE_FIELD
                 (FMC_ConvertNanosecondsToClockCycle(p_config->timings.async_access_timings.data_setup_nsec,
                                                     clock_freq), FMC_BTRx_DATAST_Msk, FMC_BTRx_DATAST_Pos)            |
                 FMC_WRITE_FIELD((FMC_ConvertNanosecondsToClockCycle
                                  (p_config->timings.async_access_timings.data_hold_nsec, clock_freq) - 1U),
                                 FMC_BTRx_DATAHLD_Msk, FMC_BTRx_DATAHLD_Pos)                                           |
                 FMC_WRITE_FIELD(FMC_ConvertNanosecondsToClockCycle(p_config->timings.bus_turnaround_nsec, clock_freq)
                                 - 1U, FMC_BTRx_BUSTURN_Msk, FMC_BTRx_BUSTURN_Pos)                                     |
                 FMC_WRITE_FIELD
                 ((FMC_ConvertNanosecondsToClockCycle(p_config->timings.sync_protocol.clk_period_nsec, clock_freq)
                   - 1U), FMC_BTRx_CLKDIV_Msk, FMC_BTRx_CLKDIV_Pos)                                                    |
                 FMC_WRITE_FIELD
                 ((FMC_ConvertNanosecondsToClockCycle(p_config->timings.sync_protocol.data_latency_nsec, clock_freq)
                   - 2U), FMC_BTRx_DATLAT_Msk, FMC_BTRx_DATLAT_Pos));

  FMC_Disable();

  FMC_NOR_SRAM_SetConfigMemory(NOR_GET_INSTANCE(hnor), control_mask, 0U, timing_mask);

  FMC_NOR_SRAM_SetClock((uint32_t)p_config->timings.sync_protocol.continuous_clock, clk_period_mask);

  FMC_Enable();

  hnor->global_state = HAL_NOR_STATE_MEMORY_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief Retrieve the memory configuration for memories with synchronous read and asynchronous write access mode.
  * @param hnor     Pointer to a @ref hal_nor_handle_t structure.
  * @param p_config Pointer to a @ref hal_sram_rd_sync_wr_async_memory_config_t structure filled with the retrieved
  *                 memory configuration.
  */
void HAL_NOR_GetConfigRdSyncWrAsyncMemory(const hal_nor_handle_t *hnor,
                                          hal_nor_rd_sync_wr_async_memory_config_t *p_config)
{
  uint32_t control_cfg;
  uint32_t counter_cfg;
  uint32_t timing_cfg;
  uint32_t clock_freq = HAL_RCC_GetHCLKFreq();

  ASSERT_DBG_PARAM(hnor     != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_NOR_STATE_IDLE);

  /* Get configuration value */
  FMC_NOR_SRAM_GetConfigMemory(NOR_GET_INSTANCE(hnor), &control_cfg, &counter_cfg, &timing_cfg);

  p_config->memory.mux_mode              = (hal_nor_mux_mode_t)(uint32_t)READ_BIT(control_cfg, FMC_BCRx_MUXEN);
  p_config->memory.byte_lane_setup_cycle = (hal_nor_byte_lane_source_clock_cycle_t)(uint32_t)READ_BIT(control_cfg,
                                           FMC_BCRx_NBLSET);
  p_config->timings.sync_protocol.wait_signal_state = (hal_nor_sync_wait_signal_state_t)(uint32_t)READ_BIT(control_cfg,
                                                      FMC_BCRx_WAITEN);
  p_config->timings.sync_protocol.wait_timing_config = (hal_nor_wait_timing_config_t)(uint32_t)READ_BIT(control_cfg,
                                                       FMC_BCRx_WAITCFG);
  p_config->timings.sync_protocol.continuous_clock = (hal_nor_continuous_clock_t)(uint32_t)READ_BIT(control_cfg,
                                                     FMC_BCR1_CCLKEN);
  p_config->timings.sync_protocol.clk_period_nsec = FMC_ConvertClockCycleToNanoseconds
                                                    ((FMC_READ_FIELD(timing_cfg, FMC_BTRx_CLKDIV_Msk,
                                                                     FMC_BTRx_CLKDIV_Pos) + 1U), clock_freq);
  p_config->timings.sync_protocol.data_latency_nsec = FMC_ConvertClockCycleToNanoseconds
                                                      ((FMC_READ_FIELD(timing_cfg, FMC_BTRx_DATLAT_Msk,
                                                                       FMC_BTRx_DATLAT_Pos) + 2U), clock_freq);
  p_config->timings.async_wait = (hal_nor_async_wait_signal_state_t)(uint32_t)READ_BIT(control_cfg,
                                 FMC_BCRx_ASYNCWAIT);
  p_config->timings.async_access_timings.addr_setup_nsec = FMC_ConvertClockCycleToNanoseconds(READ_BIT(timing_cfg,
                                                           FMC_BTRx_ADDSET), clock_freq);
  p_config->timings.async_access_timings.addr_hold_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(timing_cfg,
                                                          FMC_BTRx_ADDHLD_Msk, FMC_BTRx_ADDHLD_Pos), clock_freq);
  p_config->timings.async_access_timings.data_setup_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(timing_cfg,
                                                           FMC_BTRx_DATAST_Msk, FMC_BTRx_DATAST_Pos), clock_freq);
  p_config->timings.async_access_timings.data_hold_nsec = FMC_ConvertClockCycleToNanoseconds
                                                          ((FMC_READ_FIELD(timing_cfg, FMC_BTRx_DATAHLD_Msk,
                                                                           FMC_BTRx_DATAHLD_Pos) + 1U), clock_freq);
  p_config->timings.bus_turnaround_nsec = FMC_ConvertClockCycleToNanoseconds
                                          ((FMC_READ_FIELD(timing_cfg, FMC_BTRx_BUSTURN_Msk, FMC_BTRx_BUSTURN_Pos)
                                            + 1U), clock_freq);
}

/**
  * @brief  Enable the corresponding NOR device.
  * @param  hnor  Pointer to a @ref hal_nor_handle_t structure.
  * @note   This API can be used once the NOR is fully configured.
  * @retval HAL_OK The NOR is successfully enabled.
  */
hal_status_t HAL_NOR_EnableMemory(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_MEMORY_CONFIGURED);

  FMC_NOR_SRAM_Enable(NOR_GET_INSTANCE(hnor));

  hnor->global_state = HAL_NOR_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Disable the corresponding NOR device.
  * @param  hnor  Pointer to a @ref hal_nor_handle_t structure.
  * @note   This API must be called when a memory configuration adjustment is needed.
  * @retval HAL_OK The NOR is successfully disabled.
  */
hal_status_t HAL_NOR_DisableMemory(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  FMC_NOR_SRAM_Disable(NOR_GET_INSTANCE(hnor));

  hnor->global_state = HAL_NOR_STATE_MEMORY_CONFIGURED;

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup NOR_Exported_Functions_Group3
  * @{
This subsection provides a set of functions allowing to retrieve the CFI query string for all CFI compliant
NOR memories, regardless their command set ID :
  - HAL_NOR_CFI_ReadDeviceInfo() : used to retrieve the NOR flash CFI information and fill it into
                                   hal_nor_cfi_device_info_t structure.
  - HAL_NOR_CFI_ReadDeviceRegionInfo() : used to retrieve the NOR flash erase block region information and fill it into
                                         hal_nor_cfi_device_region_info_t structure.
  */

/**
  * @brief  Read the NOR flash CFI database structure information.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  p_device_info     Pointer to @ref hal_nor_cfi_device_info_t structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the CFI device info structure pointer is NULL.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_OK            The CFI info is successfully retrieved.
  */
hal_status_t HAL_NOR_CFI_ReadDeviceInfo(hal_nor_handle_t *hnor, hal_nor_cfi_device_info_t *p_device_info)
{
  volatile hal_nor_state_t previous_state;
  uint16_t temp;

  ASSERT_DBG_PARAM(hnor          != NULL);
  ASSERT_DBG_PARAM(p_device_info != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                   (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_device_info == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                              (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED), HAL_NOR_STATE_READ_ACTIVE, previous_state);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR), NOR_CFI_CMD);

  for (uint16_t i = 0U; i < 3U; ++i)
  {
    p_device_info->query_unique_ascii[i] =
      *(volatile uint8_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, (NOR_CFI_ADDR_QUERY_UNIQUE + i));
  }

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_CMD_SET);
  p_device_info->primary_command_set =
    (temp | ((*(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_CMD_SET + 1U))
             << 8U));

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_PRIMARY_TABLE);
  p_device_info->extended_primary_table_address =
    (temp | ((*(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_PRIMARY_TABLE
                                                                   + 1U)) << 8U));

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_ALTERNATE_CMD_SET);
  p_device_info->alternate_command_set =
    (temp | ((*(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                                                   NOR_CFI_ADDR_ALTERNATE_CMD_SET + 1U)) << 8U));

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_SECONDARY_TABLE);
  p_device_info->extended_secondary_table_address =
    (temp | ((*(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                                                   NOR_CFI_ADDR_SECONDARY_TABLE + 1U)) << 8U));

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                                              NOR_CFI_ADDR_DEVICE_INTERFACE_CODE);
  p_device_info->device_interface_code =
    (temp | ((*(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                                                   NOR_CFI_ADDR_DEVICE_INTERFACE_CODE + 1U)) << 8U));

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_MAX_BUFFER_BYTE);
  p_device_info->max_buffer_byte =
    1UL << (temp | ((*(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                                                          NOR_CFI_ADDR_MAX_BUFFER_BYTE + 1U)) << 8U));

  p_device_info->erase_block_region_nb = (*(volatile uint8_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                          NOR_CFI_ADDR_ERASE_BLOCK_REGION_NB));

  p_device_info->device_size_byte =
    1UL << (*(volatile uint8_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                                                NOR_CFI_ADDR_DEVICE_SIZE_BYTE));

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_DEVICE_SUPPLY_MIN);
  p_device_info->device_supply_min_mvolt = FMC_NOR_Convert_Voltage(temp);

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_DEVICE_SUPPLY_MAX);
  p_device_info->device_supply_max_mvolt = FMC_NOR_Convert_Voltage(temp);

  temp =
    *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_ERASE_PGM_SUPPLY_MIN);
  p_device_info->erase_program_supply_min_mvolt = FMC_NOR_Convert_Voltage(temp);

  temp =
    *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_ERASE_PGM_SUPPLY_MAX);
  p_device_info->erase_program_supply_max_mvolt = FMC_NOR_Convert_Voltage(temp);

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_PGM_TIMEOUT);
  p_device_info->word_program_timeout_usec = temp;
  if (temp != 0UL)
  {
    p_device_info->word_program_timeout_usec = 1UL << temp;
  }

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                                              NOR_CFI_ADDR_BUFFER_PGM_TIMEOUT);
  p_device_info->buffer_program_timeout_usec = temp;
  if (temp != 0UL)
  {
    p_device_info->buffer_program_timeout_usec  = 1UL << temp;
  }

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                                              NOR_CFI_ADDR_BLOCK_ERASE_TIMEOUT);
  p_device_info->block_erase_timeout_msec = temp;
  if (temp != 0UL)
  {
    p_device_info->block_erase_timeout_msec  = 1UL << temp;
  }

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                                              NOR_CFI_ADDR_FULL_ERASE_TIMEOUT);
  p_device_info->full_erase_timeout_msec = temp;
  if (temp != 0UL)
  {
    p_device_info->full_erase_timeout_msec  = 1UL << temp;
  }

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_MAX_PGM_TIMEOUT);
  p_device_info->max_word_program_timeout_usec = temp;
  if (temp != 0UL)
  {
    p_device_info->max_word_program_timeout_usec = (1UL << temp) * p_device_info->word_program_timeout_usec;
  }

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                                              NOR_CFI_ADDR_MAX_BUFFER_PGM_TIMEOUT);
  p_device_info->max_buffer_program_timeout_usec = temp;
  if (temp != 0UL)
  {
    p_device_info->max_buffer_program_timeout_usec = (1UL << temp) * p_device_info->buffer_program_timeout_usec;
  }

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                                              NOR_CFI_ADDR_MAX_BLOCK_ERASE_TIMEOUT);
  p_device_info->max_block_erase_timeout_msec = temp;
  if (temp != 0UL)
  {
    p_device_info->max_block_erase_timeout_msec = (1UL << temp) * p_device_info->block_erase_timeout_msec;
  }

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                                              NOR_CFI_ADDR_MAX_FULL_ERASE_TIMEOUT);
  p_device_info->max_full_erase_timeout_msec = temp;
  if (temp != 0UL)
  {
    p_device_info->max_full_erase_timeout_msec = (1UL << temp) * p_device_info->full_erase_timeout_msec;
  }

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Read the NOR flash erase block region information.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  region_index      NOR memory erase block region index.
  * @param  p_region_info     Pointer to @ref hal_nor_cfi_device_region_info_t structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the device region info structure pointer or the region index
  *                           is NULL.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_OK            The region info is successfully retrieved.
  */
hal_status_t HAL_NOR_CFI_ReadDeviceRegionInfo(hal_nor_handle_t *hnor, uint8_t region_index,
                                              hal_nor_cfi_device_region_info_t *p_region_info)
{
  volatile hal_nor_state_t previous_state;
  uint16_t base_region_addr;
  uint16_t temp;
  uint8_t  region_nb;

  ASSERT_DBG_PARAM(hnor          != NULL);
  ASSERT_DBG_PARAM(p_region_info != NULL);
  ASSERT_DBG_PARAM(region_index  != 0U);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                   (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_region_info == NULL) || (region_index == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                              (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED), HAL_NOR_STATE_READ_ACTIVE, previous_state);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR), NOR_CFI_CMD);

  region_nb = (*(volatile uint8_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                                                   NOR_CFI_ADDR_ERASE_BLOCK_REGION_NB));
  if (region_index > region_nb)
  {
    hnor->global_state = previous_state;
    return HAL_ERROR;
  }

  base_region_addr = NOR_CFI_ADDR_REGION_INFO + (4U * ((uint16_t)region_index - 1U));
  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, base_region_addr);
  p_region_info->block_nbr =
    (temp | ((*(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, base_region_addr + 1U))
             << 8U)) + 1U;

  temp = *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, base_region_addr + 2U);
  p_region_info->block_size_byte =
    ((uint32_t)temp | ((uint32_t)(*(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance,
                                  base_region_addr + 3U)) << 8U)) * 256UL;

  hnor->global_state = previous_state;

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup NOR_Exported_Functions_Group4
  * @{
This subsection provides a set of functions allowing to control the input and output operations of the CFI compliant
16-bits NOR memories with the command set ID 0001 :
  - HAL_NOR_CFI_0001_Reset()
  - HAL_NOR_CFI_0001_ReadArray()
  - HAL_NOR_CFI_0001_ReadDeviceIdentifier()
  - HAL_NOR_CFI_0001_ReadStatusRegister()
  - HAL_NOR_CFI_0001_ClearStatusRegister()
  - HAL_NOR_CFI_0001_Program()
  - HAL_NOR_CFI_0001_BufferedProgram()
  - HAL_NOR_CFI_0001_BufferedEnhancedFactoryProgram()
  - HAL_NOR_CFI_0001_BlockErase()
  - HAL_NOR_CFI_0001_ProgramSuspend()
  - HAL_NOR_CFI_0001_EraseSuspend()
  - HAL_NOR_CFI_0001_ProgramResume()
  - HAL_NOR_CFI_0001_EraseResume()
  - HAL_NOR_CFI_0001_BlockLock()
  - HAL_NOR_CFI_0001_BlockUnlock()
  - HAL_NOR_CFI_0001_BlockLockDown()
  - HAL_NOR_CFI_0001_ConfigureReadConfigurationRegister()
  - HAL_NOR_CFI_0001_BlockBlankCheck()
  - HAL_NOR_CFI_0001_ProgramProtectionRegister()
  - HAL_NOR_CFI_0001_ProgramLockRegister()
  */

/**
  * @brief  Reset the NOR flash device  with command set ID 0001.
  * @param  hnor     Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_BUSY NOR state is active when calling this API.
  * @retval HAL_OK   The NOR flash device is reset successfully.
  */
hal_status_t HAL_NOR_CFI_0001_Reset(hal_nor_handle_t *hnor)
{
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_FAULT |
                   (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_FAULT |
                              (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0001_CMD_READ_ARRAY);

  if (previous_state == HAL_NOR_STATE_FAULT)
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }
  else
  {
    hnor->global_state = previous_state;
  }

  return HAL_OK;
}

/**
  * @brief  Read data from the NOR flash memory with command set ID 0001.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte       NOR memory internal offset to read from in bytes.
  * @param  p_data            Pointer to the buffer that receives the data read from the NOR memory.
  * @param  size_byte         Number of bytes to read.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data pointer is NULL or when the size is 0 byte.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_OK            The data is successfully read.
  */
hal_status_t HAL_NOR_CFI_0001_ReadArray(hal_nor_handle_t *hnor, uint32_t offset_byte, void *p_data, uint32_t size_byte)
{
  uint32_t device_addr;
  uint32_t addr;
  uint32_t size;
  volatile hal_nor_state_t previous_state;
  uint8_t *p_dest_data;

  ASSERT_DBG_PARAM(hnor      != NULL);
  ASSERT_DBG_PARAM(p_data    != NULL);
  ASSERT_DBG_PARAM(size_byte != 0U);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                   (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                              (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED), HAL_NOR_STATE_READ_ACTIVE, previous_state);
  size = size_byte;
  p_dest_data = (uint8_t *)(uint32_t)p_data;
  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U);
  addr = device_addr + offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_READ_ARRAY);

  while (size > 0U)
  {
    *p_dest_data = *(volatile uint8_t *)addr;
    ++p_dest_data;
    ++addr;
    --size;
  }

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Read NOR flash memory identifier with command set ID 0001.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  p_nor_id          Pointer to a @ref hal_nor_cfi_0001_device_id_t structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the device identifier structure pointer is NULL.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_OK            The device identifier is successfully read.
  */
hal_status_t HAL_NOR_CFI_0001_ReadDeviceIdentifier(hal_nor_handle_t *hnor, hal_nor_cfi_0001_device_id_t *p_nor_id)
{
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor     != NULL);
  ASSERT_DBG_PARAM(p_nor_id != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                   (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_nor_id == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                              (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED), HAL_NOR_STATE_READ_ACTIVE, previous_state);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_CMD_READ_DEVICE_ID);

  p_nor_id->device_manufacturer_code =
    *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_MANUFACTURER_CODE);
  p_nor_id->device_code =
    *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_DEVICE_CODE_1);

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Read the NOR flash memory operation status with command set ID 0001.
  * @param  hnor                         Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte                  NOR memory internal offset where the process was issued.
  * @retval HAL_NOR_DEVICE_STATE_SUCCESS NOR internal processing successfully completed.
  * @retval HAL_NOR_DEVICE_STATE_ONGOING NOR internal processing is ongoing.
  * @retval HAL_NOR_DEVICE_STATE_ERROR   NOR internal processing is failed.
  */
hal_nor_device_state_t HAL_NOR_CFI_0001_ReadStatusRegister(hal_nor_handle_t *hnor, uint32_t offset_byte)
{
  hal_nor_device_state_t status;

  ASSERT_DBG_PARAM(hnor != NULL);
  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_FAULT |
                   (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  status = NOR_CFI_0001_ReadStatusRegister(hnor, offset_byte);

  return status;
}

/**
  * @brief  Clear the NOR flash memory status register with command set ID 0001.
  * @param  hnor     Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_BUSY NOR state is active when calling this API.
  * @retval HAL_OK   The status register is cleared.
  */
hal_status_t HAL_NOR_CFI_0001_ClearStatusRegister(hal_nor_handle_t *hnor)
{
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0001_CMD_CLEAR_STATUS_REG);

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Write a 16-bits data to the NOR flash memory with command set ID 0001.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte NOR memory internal offset to write in, in bytes.
  * @param  data        Data to write in the NOR memory.
  * @param  timeout_ms  NOR programming timeout.
  * @retval HAL_BUSY    NOR state is active when calling this API.
  * @retval HAL_TIMEOUT NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR   NOR internal processing is failed.
  * @retval HAL_OK      The data is successfully written.
  */
hal_status_t HAL_NOR_CFI_0001_Program(hal_nor_handle_t *hnor, uint32_t offset_byte, uint16_t data, uint32_t timeout_ms)
{
  uint32_t device_addr;
  volatile hal_nor_state_t previous_state;
  hal_status_t status;

  ASSERT_DBG_PARAM(hnor != NULL);
  ASSERT_DBG_PARAM(IS_NOR_OFFSET_16_BITS_ALIGNED(offset_byte));

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_PGM);
  FMC_NOR_Write(device_addr, data);

  status = NOR_CFI_0001_PollForOperationStatus(hnor, offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = previous_state;
  }

  return (status);
}

/**
  * @brief  Write a 16-bits data buffer to the NOR flash memory with command set ID 0001.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte       NOR memory internal offset to write in, in bytes.
  * @param  p_data            Pointer to data to write in the NOR memory.
  * @param  size_byte         Number of bytes to write in that must be a multiple of 2.
  * @param  timeout_ms        NOR buffer programming timeout.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data pointer is NULL or when the size is 0 byte.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_TIMEOUT       NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR         NOR internal processing is failed.
  * @retval HAL_OK            The buffer is successfully written.
  */
hal_status_t HAL_NOR_CFI_0001_BufferedProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, const void *p_data,
                                              uint32_t size_byte, uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;
  volatile hal_nor_state_t previous_state;
  uint16_t *p_current_address;
  const uint16_t *p_end_address;
  const uint16_t *p_temp;

  ASSERT_DBG_PARAM(hnor      != NULL);
  ASSERT_DBG_PARAM(p_data    != NULL);
  ASSERT_DBG_PARAM(size_byte != 0U);

  ASSERT_DBG_PARAM(IS_NOR_OFFSET_16_BITS_ALIGNED(offset_byte));
  ASSERT_DBG_PARAM(IS_NOR_BUFFER_SIZE_16_BITS_MULTIPLE(size_byte));

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  p_temp = (const uint16_t *)(uint32_t)p_data;
  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + offset_byte;
  /* Initialize variables */
  p_current_address = (uint16_t *)device_addr;
  p_end_address     = (uint16_t *)(device_addr + (size_byte - 1U));

  /* Load write buffer command sequence */
  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_BUFFERED_PGM);
  FMC_NOR_Write(device_addr, (uint16_t)((size_byte / 2U) - 1U));

  while (p_current_address <= p_end_address)
  {
    FMC_NOR_Write((uint32_t)p_current_address, *p_temp);
    ++p_current_address;
    ++p_temp;
  }

  FMC_NOR_Write((device_addr + offset_byte), NOR_CFI_0001_CMD_CONFIRM);

  status = NOR_CFI_0001_PollForOperationStatus(hnor, offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = previous_state;
  }

  return (status);
}

/**
  * @brief  Write a 16-bits data buffer to the NOR flash memory with command set ID 0001 using an enhanced programming
            algorithm.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte       NOR memory internal offset to write in, in bytes.
  * @param  p_data            Pointer to data to write in the NOR memory.
  * @param  size_byte         Number of bytes to write in that must be a multiple of 2.
  * @param  timeout_ms        NOR buffer programming timeout.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data pointer is NULL or when the size is 0 byte.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_TIMEOUT       NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR         NOR internal processing is failed.
  * @retval HAL_OK            The buffer is successfully written.
  */
hal_status_t HAL_NOR_CFI_0001_BufferedEnhancedFactoryProgram(hal_nor_handle_t *hnor, uint32_t offset_byte,
                                                             const void *p_data, uint32_t size_byte,
                                                             uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;
  uint16_t *p_current_address;
  const uint16_t *p_end_address;
  const uint16_t *p_temp;

  ASSERT_DBG_PARAM(hnor      != NULL);
  ASSERT_DBG_PARAM(p_data    != NULL);
  ASSERT_DBG_PARAM(size_byte != 0U);

  ASSERT_DBG_PARAM(IS_NOR_OFFSET_16_BITS_ALIGNED(offset_byte));
  ASSERT_DBG_PARAM(IS_NOR_BUFFER_SIZE_16_BITS_MULTIPLE(size_byte));

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_PROGRAM_ACTIVE);

  p_temp = (const uint16_t *)(uint32_t)p_data;
  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + offset_byte;

  /* Initialize variables */
  p_current_address = (uint16_t *)device_addr;
  p_end_address     = (uint16_t *)(device_addr + (size_byte - 1U));

  /* Load write buffer command sequence */
  FMC_NOR_Write((device_addr + offset_byte), NOR_CFI_0001_CMD_BEFP_SETUP);
  FMC_NOR_Write((device_addr + offset_byte), NOR_CFI_0001_CMD_CONFIRM);

  while (p_current_address <= p_end_address)
  {
    FMC_NOR_Write((uint32_t)p_current_address, *p_temp);
    ++p_current_address;
    ++p_temp;
  }

  status = NOR_CFI_0001_PollForOperationStatus(hnor, offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}

/**
  * @brief  Erase a specified block of the NOR flash memory with command set ID 0001.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  block_offset_byte NOR memory internal block offset to erase in bytes.
  * @param  timeout_ms        NOR erasing timeout.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_TIMEOUT       NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR         NOR internal processing is failed.
  * @retval HAL_OK            The block is successfully erased.
  */
hal_status_t HAL_NOR_CFI_0001_BlockErase(hal_nor_handle_t *hnor, uint32_t block_offset_byte, uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_ERASE_ACTIVE);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + block_offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_BLOCK_ERASE_SETUP);
  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_CONFIRM);

  status = NOR_CFI_0001_PollForOperationStatus(hnor, block_offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}

/**
  * @brief  Suspend the programming operation of the NOR flash memory with command set ID 0001.
  * @param  hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_OK The program operation is suspended.
  */
hal_status_t HAL_NOR_CFI_0001_ProgramSuspend(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_PROGRAM_ACTIVE);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0001_CMD_SUSPEND);

  hnor->global_state = HAL_NOR_STATE_PROGRAM_SUSPENDED;

  return HAL_OK;
}

/**
  * @brief  Suspend the block erase operation of the NOR flash memory with command set ID 0001.
  * @param  hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_OK The erase operation is suspended.
  */
hal_status_t HAL_NOR_CFI_0001_EraseSuspend(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_ERASE_ACTIVE);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0001_CMD_SUSPEND);

  hnor->global_state = HAL_NOR_STATE_ERASE_SUSPENDED;

  return HAL_OK;
}

/**
  * @brief  Resume the programming operation of the NOR flash memory with command set ID 0001.
  * @param  hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_OK The suspended program operation is resumed.
  */
hal_status_t HAL_NOR_CFI_0001_ProgramResume(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_PROGRAM_SUSPENDED);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0001_CMD_CONFIRM);

  hnor->global_state = HAL_NOR_STATE_PROGRAM_ACTIVE;

  return HAL_OK;
}

/**
  * @brief  Resume the block erase operation of the NOR flash memory with command set ID 0001.
  * @param  hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_OK The suspended erase operation is resumed.
  */
hal_status_t HAL_NOR_CFI_0001_EraseResume(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0001_CMD_CONFIRM);

  hnor->global_state = HAL_NOR_STATE_ERASE_ACTIVE;

  return HAL_OK;
}

/**
  * @brief  Lock a specified block of the NOR flash memory with command set ID 0001.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  block_offset_byte NOR memory internal block offset to lock in bytes.
  * @note   Locked blocks cannot be programmed or erased, they can only be read.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_OK            The block is successfully locked.
  */
hal_status_t HAL_NOR_CFI_0001_BlockLock(hal_nor_handle_t *hnor, uint32_t block_offset_byte)
{
  uint32_t device_addr;
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + block_offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_BLOCK_LOCK_SETUP);
  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_BLOCK_LOCK);

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Unlock a specified block of the NOR flash memory with command set ID 0001.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  block_offset_byte NOR memory internal block offset to unlock in bytes.
  * @note   Unlocked blocks can be read, programmed and erased.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_OK            The block is successfully unlocked.
  */
hal_status_t HAL_NOR_CFI_0001_BlockUnlock(hal_nor_handle_t *hnor, uint32_t block_offset_byte)
{
  uint32_t device_addr;
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + block_offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_BLOCK_LOCK_SETUP);
  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_BLOCK_UNLOCK);

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Lock-down a specified block of the NOR flash memory with command set ID 0001.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  block_offset_byte NOR memory internal block offset to lock-down in bytes.
  * @note   locked-down blocks cannot be programmed or erased, they can only be read. The locked-down blocks can only
  *         be unlocked by issuing the unlock block with 'WP' Write Protect pin de-asserted.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_OK            The block is successfully locked-down.
  */
hal_status_t HAL_NOR_CFI_0001_BlockLockDown(hal_nor_handle_t *hnor, uint32_t block_offset_byte)
{
  uint32_t device_addr;
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state, ((uint32_t)(uint32_t)HAL_NOR_STATE_IDLE  |
                                                  (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + block_offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_BLOCK_LOCK_SETUP);
  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_BLOCK_LOCK_DOWN);

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Modify the configuration register of the NOR flash memory with command set ID 0001.
  * @param  hnor     Pointer to a @ref hal_nor_handle_t structure.
  * @param  data     Data to write in the configuration register.
  * @retval HAL_BUSY NOR state is active when calling this API.
  * @retval HAL_OK   The read configuration register is successfully modified.
  */
hal_status_t HAL_NOR_CFI_0001_ConfigureReadConfigurationRegister(hal_nor_handle_t *hnor, uint16_t data)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_PROGRAM_ACTIVE);

  FMC_NOR_Write(data, NOR_CFI_0001_CMD_READ_CONFIG_REG_SETUP);
  FMC_NOR_Write(data, NOR_CFI_0001_CMD_READ_CONFIG_REG);

  hnor->global_state = HAL_NOR_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Check whether a specified main block of the NOR flash memory is completely erased with command set ID 0001.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  block_offset_byte NOR memory internal block offset to erase in bytes.
  * @param  timeout_ms        NOR blank check timeout.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_TIMEOUT       NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR         NOR block is not completely erased.
  * @retval HAL_OK            The NOR block is successfully erased.
  */
hal_status_t HAL_NOR_CFI_0001_BlockBlankCheck(hal_nor_handle_t *hnor, uint32_t block_offset_byte, uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_READ_ACTIVE);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + block_offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_BLOCK_BLANK_CHECK);
  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_CONFIRM);

  status = NOR_CFI_0001_PollForOperationStatus(hnor, block_offset_byte, timeout_ms);
  if (status == HAL_TIMEOUT)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}

#if defined(USE_HAL_NOR_PROTECTION) && (USE_HAL_NOR_PROTECTION == 1U)

/**
  * @brief  Program any of the protection registers of the NOR flash memory with command set ID 0001.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte NOR memory internal protection register offset to program in bytes.
  * @param  data        Data to write in the protection register.
  * @retval HAL_BUSY    NOR state is active when calling this API.
  * @retval HAL_OK      The protection register is successfully programmed.
  */
hal_status_t HAL_NOR_CFI_0001_ProgramProtectionRegister(hal_nor_handle_t *hnor, uint32_t offset_byte, uint16_t data)
{
  uint32_t device_addr;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_PROGRAM_ACTIVE);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_PROTECTION_PGM_SETUP);
  FMC_NOR_Write(device_addr, data);

  hnor->global_state = HAL_NOR_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Lock any of the protection register of the NOR flash memory with command set ID 0001.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte NOR memory internal lock register offset to program in bytes.
  * @param  data        Data to write in the lock register.
  * @note   After being locked, the protection registers cannot be unlocked.
  * @retval HAL_BUSY    NOR state is active when calling this API.
  * @retval HAL_OK      The protection register is successfully locked.
  */
hal_status_t HAL_NOR_CFI_0001_ProgramLockRegister(hal_nor_handle_t *hnor, uint32_t offset_byte, uint16_t data)
{
  uint32_t device_addr;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_PROGRAM_ACTIVE);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_PROTECTION_PGM_SETUP);
  FMC_NOR_Write(device_addr, data);

  hnor->global_state = HAL_NOR_STATE_IDLE;

  return HAL_OK;
}
#endif /* USE_HAL_NOR_PROTECTION */
/**
  * @}
  */

/** @addtogroup NOR_Exported_Functions_Group5
  * @{
This subsection provides a set of functions allowing to control the input and output operations of the CFI compliant
16-bits NOR memories with the command set ID 0002 :
  - HAL_NOR_CFI_0002_Reset()
  - HAL_NOR_CFI_0002_Read()
  - HAL_NOR_CFI_0002_ReadDeviceIdentifier()
  - HAL_NOR_CFI_0002_ReadStatusRegister()
  - HAL_NOR_CFI_0002_UnlockBypass()
  - HAL_NOR_CFI_0002_UnlockBypassReset()
  - HAL_NOR_CFI_0002_Program()
  - HAL_NOR_CFI_0002_UnlockBypassProgram()
  - HAL_NOR_CFI_0002_DoubleDataProgram()
  - HAL_NOR_CFI_0002_QuadrupleDataProgram()
  - HAL_NOR_CFI_0002_BufferedProgram()
  - HAL_NOR_CFI_0002_EnhancedBufferedProgram()
  - HAL_NOR_CFI_0002_UnlockBypassBufferedProgram()
  - HAL_NOR_CFI_0002_EnhancedUnlockBypassBufferedProgram()
  - HAL_NOR_CFI_0002_ProgramSuspend()
  - HAL_NOR_CFI_0002_EraseSuspend()
  - HAL_NOR_CFI_0002_ProgramResume()
  - HAL_NOR_CFI_0002_EraseResume()
  - HAL_NOR_CFI_0002_ChipErase()
  - HAL_NOR_CFI_0002_ChipEraseUnlockBypass()
  - HAL_NOR_CFI_0002_BlockErase()
  - HAL_NOR_CFI_0002_BlockEraseUnlockBypass()
  - HAL_NOR_CFI_0002_BlockBlankCheck()
  */

/**
  * @brief  Reset the NOR flash device with command set ID 0002.
  * @param  hnor     Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_BUSY NOR state is active when calling this API.
  * @retval HAL_OK   The NOR flash device is reset successfully.
  */
hal_status_t HAL_NOR_CFI_0002_Reset(hal_nor_handle_t *hnor)
{
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_FAULT |
                   (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_FAULT |
                              (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0002_CMD_RESET);

  if (previous_state == HAL_NOR_STATE_FAULT)
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }
  else
  {
    hnor->global_state = previous_state;
  }

  return HAL_OK;
}

/**
  * @brief  Read data from the NOR flash memory with command set ID 0002.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte       NOR memory internal offset to read from in bytes.
  * @param  p_data            Pointer to the buffer that receives the data read from the NOR memory.
  * @param  size_byte         Number of bytes to read.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data pointer is NULL or when the size is 0 byte.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_OK            The data is successfully read.
  */
hal_status_t HAL_NOR_CFI_0002_Read(hal_nor_handle_t *hnor, uint32_t offset_byte, void *p_data, uint32_t size_byte)
{
  uint32_t addr;
  uint32_t size;
  volatile hal_nor_state_t previous_state;
  uint8_t *p_dest_data;

  ASSERT_DBG_PARAM(hnor      != NULL);
  ASSERT_DBG_PARAM(p_data    != NULL);
  ASSERT_DBG_PARAM(size_byte != 0U);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                   (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                              (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED), HAL_NOR_STATE_READ_ACTIVE, previous_state);

  size = size_byte;
  p_dest_data = (uint8_t *)(uint32_t)p_data;
  addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + offset_byte;

  while (size > 0U)
  {
    *p_dest_data = *(volatile uint8_t *)addr;
    ++p_dest_data;
    ++addr;
    --size;
  }

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Read NOR flash memory identifier with command set ID 0002.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  p_nor_id          Pointer to a @ref hal_nor_cfi_0002_device_id_t structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_nor_id pointer is NULL.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_OK            The device identifier is successfully read.
  */
hal_status_t HAL_NOR_CFI_0002_ReadDeviceIdentifier(hal_nor_handle_t *hnor, hal_nor_cfi_0002_device_id_t *p_nor_id)
{
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor     != NULL);
  ASSERT_DBG_PARAM(p_nor_id != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                   (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_nor_id == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                              (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED), HAL_NOR_STATE_READ_ACTIVE, previous_state);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_FIRST),
                NOR_CFI_0002_CMD_UNLOCK_FIRST);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_SECOND),
                NOR_CFI_0002_CMD_UNLOCK_SECOND);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_THIRD),
                NOR_CFI_CMD_READ_DEVICE_ID);

  p_nor_id->device_manufacturer_code =
    *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_MANUFACTURER_CODE);
  p_nor_id->device_code_1  =
    *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_DEVICE_CODE_1);
  p_nor_id->device_code_2  =
    *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_DEVICE_CODE_2);
  p_nor_id->device_code_3  =
    *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_DEVICE_CODE_3);
  p_nor_id->indicator_bits =
    *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_DEVICE_INDICATOR_BITS);

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Read the NOR flash memory operation status with command set ID 0002.
  * @param  hnor                         Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte                  NOR memory internal offset where the process was issued.
  * @retval HAL_NOR_DEVICE_STATE_SUCCESS NOR internal processing successfully completed.
  * @retval HAL_NOR_DEVICE_STATE_ONGOING NOR internal processing is ongoing.
  * @retval HAL_NOR_DEVICE_STATE_ERROR   NOR internal processing is failed.
  */
hal_nor_device_state_t HAL_NOR_CFI_0002_ReadStatusRegister(hal_nor_handle_t *hnor, uint32_t offset_byte)
{
  hal_nor_device_state_t status;

  ASSERT_DBG_PARAM(hnor != NULL);
  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_FAULT |
                   (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  status = NOR_CFI_0002_ReadStatusRegister(hnor, offset_byte);

  return status;
}

/**
  * @brief  Activate the Unlock Bypass mode to facilitate faster programming time with command set ID 0002.
  * @param  hnor     Pointer to a @ref hal_nor_handle_t structure.
  * @note   During the Unlock Bypass mode, only the Unlock bypass Program, Unlock bypass Buffered Program and
  *         Unlock Bypass Reset commands are valid.
  * @retval HAL_BUSY NOR state is active when calling this API.
  * @retval HAL_OK   The unlock bypass mode is activated successfully.
  */
hal_status_t HAL_NOR_CFI_0002_UnlockBypass(hal_nor_handle_t *hnor)
{
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_FIRST),
                NOR_CFI_0002_CMD_UNLOCK_FIRST);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_SECOND),
                NOR_CFI_0002_CMD_UNLOCK_SECOND);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_THIRD),
                NOR_CFI_0002_CMD_UNLOCK_BYPASS);

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Exit the Unlock Bypass mode.
  * @param  hnor     Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_BUSY NOR state is active when calling this API.
  * @retval HAL_OK   The unlock bypass mode is exited successfully.
  */
hal_status_t HAL_NOR_CFI_0002_UnlockBypassReset(hal_nor_handle_t *hnor)
{
  uint32_t device_addr;
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U);

  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_UNLOCK_BYPASS_RESET_FIRST);
  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_UNLOCK_BYPASS_RESET_SECOND);

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Write a 16-bits data to the NOR flash memory with command set ID 0002.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte NOR memory internal offset to write in, in bytes.
  * @param  data        Data to write in the NOR memory.
  * @param  timeout_ms  NOR programming timeout.
  * @retval HAL_BUSY    NOR state is active when calling this API.
  * @retval HAL_TIMEOUT NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR   NOR internal processing is failed.
  * @retval HAL_OK      The data is successfully written.
  */
hal_status_t HAL_NOR_CFI_0002_Program(hal_nor_handle_t *hnor, uint32_t offset_byte, uint16_t data, uint32_t timeout_ms)
{
  hal_status_t status;
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);
  ASSERT_DBG_PARAM(IS_NOR_OFFSET_16_BITS_ALIGNED(offset_byte));

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_FIRST),
                NOR_CFI_0002_CMD_UNLOCK_FIRST);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_SECOND),
                NOR_CFI_0002_CMD_UNLOCK_SECOND);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_THIRD),
                NOR_CFI_0002_CMD_DATA_PGM);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + offset_byte, data);

  status = NOR_CFI_0002_PollForOperationStatus(hnor, offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = previous_state;
  }

  return (status);
}

/**
  * @brief  Write a 16-bits data to the NOR flash memory with command set ID 0002 in the Unlock Bypass mode.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte NOR memory internal offset to write in, in bytes.
  * @param  data        Data to write in the NOR memory.
  * @param  timeout_ms  NOR programming timeout.
  * @retval HAL_BUSY    NOR state is active when calling this API.
  * @retval HAL_TIMEOUT NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR   NOR internal processing is failed.
  * @retval HAL_OK      The data is successfully written.
  */
hal_status_t HAL_NOR_CFI_0002_UnlockBypassProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, uint16_t data,
                                                  uint32_t timeout_ms)
{

  uint32_t device_addr;
  hal_status_t status;
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);
  ASSERT_DBG_PARAM(IS_NOR_OFFSET_16_BITS_ALIGNED(offset_byte));

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U);

  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_DATA_PGM);

  FMC_NOR_Write(device_addr + offset_byte, data);

  status = NOR_CFI_0002_PollForOperationStatus(hnor, offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = previous_state;
  }

  return (status);
}

/**
  * @brief  Write double adjacent 16-bits data to the NOR flash memory with command set ID 0002.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte NOR memory internal offset to write in, in bytes.
  * @param  data        Data to write in the NOR memory.
  * @param  timeout_ms  NOR programming timeout.
  * @retval HAL_BUSY    NOR state is active when calling this API.
  * @retval HAL_TIMEOUT NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR   NOR internal processing is failed.
  * @retval HAL_OK      The data is successfully written.
  */
hal_status_t HAL_NOR_CFI_0002_DoubleDataProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, uint32_t data,
                                                uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;

  ASSERT_DBG_PARAM(hnor != NULL);
  ASSERT_DBG_PARAM(IS_NOR_OFFSET_16_BITS_ALIGNED(offset_byte));

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_PROGRAM_ACTIVE);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + offset_byte;

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_FIRST),
                NOR_CFI_0002_CMD_DOUBLE_PGM);

  FMC_NOR_Write(device_addr, (uint16_t)(data & 0xFFFFU));
  FMC_NOR_Write((device_addr + 2U), (uint16_t)((data >> 16U) & 0xFFFFU));

  status = NOR_CFI_0002_PollForOperationStatus(hnor, offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}

/**
  * @brief  Write four adjacent 16-bits data to the NOR flash memory with command set ID 0002.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte NOR memory internal offset to write in, in bytes.
  * @param  data_msb    MSB data to write in the NOR memory.
  * @param  data_lsb    LSB data to write in the NOR memory.
  * @param  timeout_ms  NOR programming timeout.
  * @retval HAL_BUSY    NOR state is active when calling this API.
  * @retval HAL_TIMEOUT NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR   NOR internal processing is failed.
  * @retval HAL_OK      The data is successfully written.
  */
hal_status_t HAL_NOR_CFI_0002_QuadrupleDataProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, uint32_t data_msb,
                                                   uint32_t data_lsb, uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;

  ASSERT_DBG_PARAM(hnor != NULL);
  ASSERT_DBG_PARAM(IS_NOR_OFFSET_16_BITS_ALIGNED(offset_byte));

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_PROGRAM_ACTIVE);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + offset_byte;

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_FIRST),
                NOR_CFI_0002_CMD_QUADRUPLE_PGM);

  FMC_NOR_Write(device_addr, (uint16_t)(data_lsb & 0xFFFFU));
  FMC_NOR_Write((device_addr + 2U), (uint16_t)((data_lsb >> 16U) & 0xFFFFU));

  FMC_NOR_Write((device_addr + 4U), (uint16_t)(data_msb & 0xFFFFU));
  FMC_NOR_Write((device_addr + 6U), (uint16_t)((data_msb >> 16U) & 0xFFFFU));

  status = NOR_CFI_0002_PollForOperationStatus(hnor, offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}

/**
  * @brief  Write a 16-bits data buffer to the NOR flash memory with command set ID 0002.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte       NOR memory internal offset to write in, in bytes.
  * @param  p_data            Pointer to data to write in the NOR memory.
  * @param  size_byte         Number of bytes to write in that must be a multiple of 2.
  * @param  timeout_ms        NOR buffer programming timeout.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data pointer is NULL or when the size is 0 byte.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_TIMEOUT       NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR         NOR internal processing is failed
  * @retval HAL_OK            The buffer is successfully written.
  */
hal_status_t HAL_NOR_CFI_0002_BufferedProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, const void *p_data,
                                              uint32_t size_byte, uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;
  volatile hal_nor_state_t previous_state;
  uint16_t *p_current_address;
  const uint16_t *p_end_address;
  const uint16_t *p_temp;

  ASSERT_DBG_PARAM(hnor      != NULL);
  ASSERT_DBG_PARAM(p_data    != NULL);
  ASSERT_DBG_PARAM(size_byte != 0U);
  ASSERT_DBG_PARAM(IS_NOR_OFFSET_16_BITS_ALIGNED(offset_byte));
  ASSERT_DBG_PARAM(IS_NOR_BUFFER_SIZE_16_BITS_MULTIPLE(size_byte));

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  p_temp = (const uint16_t *)(uint32_t)p_data;
  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + offset_byte;

  /* Initialize variables */
  p_current_address = (uint16_t *)device_addr;
  p_end_address     = (uint16_t *)(device_addr + (size_byte - 1U));

  /* Issue unlock command sequence */
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_FIRST),
                NOR_CFI_0002_CMD_UNLOCK_FIRST);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_SECOND),
                NOR_CFI_0002_CMD_UNLOCK_SECOND);
  FMC_NOR_Write((device_addr), NOR_CFI_0002_CMD_BUFFER_PGM);
  FMC_NOR_Write((device_addr), (uint16_t)((size_byte / 2U) - 1U));

  while (p_current_address <= p_end_address)
  {
    FMC_NOR_Write((uint32_t)p_current_address, *p_temp);
    ++p_current_address;
    ++p_temp;
  }

  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_CONFIRM);

  status = NOR_CFI_0002_PollForOperationStatus(hnor, offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = previous_state;
  }

  return (status);
}

/**
  * @brief  Write a 16-bits data buffer to the NOR flash memory with command set ID 0002 using an enhanced programming
            algorithm.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte       NOR memory internal offset to write in, in bytes.
  * @param  p_data            Pointer to data to write in the NOR memory.
  * @param  size_byte         Number of bytes to write in that must be a multiple of 2.
  * @param  timeout_ms        NOR buffer programming timeout.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data pointer is NULL or when the size is 0 byte.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_TIMEOUT       NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR         NOR internal processing is failed.
  * @retval HAL_OK            The buffer is successfully written.
  */
hal_status_t HAL_NOR_CFI_0002_EnhancedBufferedProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, const void *p_data,
                                                      uint32_t size_byte, uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;
  uint16_t *p_current_address;
  const uint16_t *p_end_address;
  const uint16_t *p_temp;

  ASSERT_DBG_PARAM(hnor      != NULL);
  ASSERT_DBG_PARAM(p_data    != NULL);
  ASSERT_DBG_PARAM(size_byte != 0U);
  ASSERT_DBG_PARAM(IS_NOR_OFFSET_16_BITS_ALIGNED(offset_byte));
  ASSERT_DBG_PARAM(IS_NOR_BUFFER_SIZE_16_BITS_MULTIPLE(size_byte));

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_PROGRAM_ACTIVE);

  p_temp = (const uint16_t *)(uint32_t)p_data;
  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + offset_byte;

  /* Initialize variables */
  p_current_address = (uint16_t *)device_addr;
  p_end_address     = (uint16_t *)(device_addr + (size_byte - 1U));

  /* Issue unlock command sequence */
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_FIRST),
                NOR_CFI_0002_CMD_UNLOCK_FIRST);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_SECOND),
                NOR_CFI_0002_CMD_UNLOCK_SECOND);
  FMC_NOR_Write((device_addr + offset_byte), NOR_CFI_0002_CMD_ENHANCED_BUFFER_PGM);

  while (p_current_address <= p_end_address)
  {
    FMC_NOR_Write((uint32_t)p_current_address, *p_temp);
    ++p_current_address;
    ++p_temp;
  }

  FMC_NOR_Write(device_addr + offset_byte, NOR_CFI_0002_CMD_CONFIRM);

  status = NOR_CFI_0002_PollForOperationStatus(hnor, offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}

/**
  * @brief  Write a 16-bits data buffer to the NOR flash memory with command set ID 0002 in the Unlock Bypass mode.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte       NOR memory internal offset to write in, in bytes.
  * @param  p_data            Pointer to data to write in the NOR memory.
  * @param  size_byte         Number of bytes to write in that must be a multiple of 2.
  * @param  timeout_ms        NOR buffer programming timeout.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data pointer is NULL or when the size is 0 byte.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_TIMEOUT       NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR         NOR internal processing is failed.
  * @retval HAL_OK            The buffer is successfully written.
  */
hal_status_t HAL_NOR_CFI_0002_UnlockBypassBufferedProgram(hal_nor_handle_t *hnor, uint32_t offset_byte,
                                                          const void *p_data, uint32_t size_byte, uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;
  volatile hal_nor_state_t previous_state;
  uint16_t *p_current_address;
  const uint16_t *p_end_address;
  const uint16_t *p_temp;

  ASSERT_DBG_PARAM(hnor      != NULL);
  ASSERT_DBG_PARAM(p_data    != NULL);
  ASSERT_DBG_PARAM(size_byte != 0U);
  ASSERT_DBG_PARAM(IS_NOR_OFFSET_16_BITS_ALIGNED(offset_byte));
  ASSERT_DBG_PARAM(IS_NOR_BUFFER_SIZE_16_BITS_MULTIPLE(size_byte));

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  p_temp = (const uint16_t *)(uint32_t)p_data;
  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U);

  /* Initialize variables */
  p_current_address = (uint16_t *)(device_addr + offset_byte);
  p_end_address     = (uint16_t *)(device_addr + offset_byte + (size_byte - 1U));

  /* Issue unlock command sequence */
  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_UNLOCK_BYPASS_BUFFER_PGM);
  FMC_NOR_Write(device_addr, (uint16_t)((size_byte / 2U) - 1U));

  while (p_current_address <= p_end_address)
  {
    FMC_NOR_Write((uint32_t)p_current_address, *p_temp);
    ++p_current_address;
    ++p_temp;
  }

  FMC_NOR_Write(device_addr + offset_byte, NOR_CFI_0002_CMD_CONFIRM);

  status = NOR_CFI_0002_PollForOperationStatus(hnor, offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = previous_state;
  }

  return (status);
}

/**
  * @brief  Write a 16-bits data buffer to the NOR flash memory with command set ID 0002 in the Unlock Bypass mode,
  *         using an enhanced programming algorithm.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte       NOR memory internal offset to write in, in bytes.
  * @param  p_data            Pointer to data to write in the NOR memory.
  * @param  size_byte         Number of bytes to write in that must be a multiple of 2.
  * @param  timeout_ms        NOR buffer programming timeout.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data pointer is NULL or when the size is 0 byte.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_TIMEOUT       NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR         NOR internal processing is failed.
  * @retval HAL_OK            The buffer is successfully written.
  */
hal_status_t HAL_NOR_CFI_0002_EnhancedUnlockBypassBufferedProgram(hal_nor_handle_t *hnor, uint32_t offset_byte,
                                                                  const void *p_data, uint32_t size_byte,
                                                                  uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;
  uint16_t *p_current_address;
  const uint16_t *p_end_address;
  const uint16_t *p_temp;

  ASSERT_DBG_PARAM(hnor      != NULL);
  ASSERT_DBG_PARAM(p_data    != NULL);
  ASSERT_DBG_PARAM(size_byte != 0U);
  ASSERT_DBG_PARAM(IS_NOR_OFFSET_16_BITS_ALIGNED(offset_byte));
  ASSERT_DBG_PARAM(IS_NOR_BUFFER_SIZE_16_BITS_MULTIPLE(size_byte));

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_PROGRAM_ACTIVE);

  p_temp = (const uint16_t *)(uint32_t)p_data;
  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + offset_byte;

  /* Initialize variables */
  p_current_address = (uint16_t *)device_addr;
  p_end_address     = (uint16_t *)(device_addr + (size_byte - 1U));

  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_ENHANCED_BUFFER_PGM);

  while (p_current_address <= p_end_address)
  {
    FMC_NOR_Write((uint32_t)p_current_address, *p_temp);
    ++p_current_address;
    ++p_temp;
  }

  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_CONFIRM);

  status = NOR_CFI_0002_PollForOperationStatus(hnor, offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}

/**
  * @brief  Suspend the programming operation of the NOR flash memory with command set ID 0002.
  * @param  hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_OK The program operation is suspended.
  */
hal_status_t HAL_NOR_CFI_0002_ProgramSuspend(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_PROGRAM_ACTIVE);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0002_CMD_SUSPEND);

  hnor->global_state = HAL_NOR_STATE_PROGRAM_SUSPENDED;

  return HAL_OK;
}

/**
  * @brief  Suspend the block erase operation of the NOR flash memory with command set ID 0002.
  * @param  hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_OK The erase operation is suspended.
  */
hal_status_t HAL_NOR_CFI_0002_EraseSuspend(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_ERASE_ACTIVE);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0002_CMD_SUSPEND);

  hnor->global_state = HAL_NOR_STATE_ERASE_SUSPENDED;

  return HAL_OK;
}

/**
  * @brief  Resume the programming operation of the NOR flash memory with command set ID 0002.
  * @param  hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_OK The suspended program operation is resumed.
  */
hal_status_t HAL_NOR_CFI_0002_ProgramResume(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_PROGRAM_SUSPENDED);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0002_CMD_RESUME);

  hnor->global_state = HAL_NOR_STATE_PROGRAM_ACTIVE;

  return HAL_OK;
}

/**
  * @brief  Resume the block erase operation of the NOR flash memory with command set ID 0002.
  * @param  hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_OK The suspended erase operation is resumed.
  */
hal_status_t HAL_NOR_CFI_0002_EraseResume(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0002_CMD_RESUME);

  hnor->global_state = HAL_NOR_STATE_ERASE_ACTIVE;

  return HAL_OK;
}

/**
  * @brief  Erase the entire NOR flash memory with command set ID 0002.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  timeout_ms  NOR erasing timeout.
  * @retval HAL_BUSY    NOR state is active when calling this API.
  * @retval HAL_TIMEOUT NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR   NOR internal processing is failed.
  * @retval HAL_OK      The NOR flash device is successfully erased.
  */
hal_status_t HAL_NOR_CFI_0002_ChipErase(hal_nor_handle_t *hnor, uint32_t timeout_ms)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_ERASE_ACTIVE);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_FIRST),
                NOR_CFI_0002_CMD_UNLOCK_FIRST);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_SECOND),
                NOR_CFI_0002_CMD_UNLOCK_SECOND);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_THIRD),
                NOR_CFI_0002_CMD_ERASE_SETUP);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_FIRST),
                NOR_CFI_0002_CMD_UNLOCK_FIRST);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_SECOND),
                NOR_CFI_0002_CMD_UNLOCK_SECOND);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_THIRD),
                NOR_CFI_0002_CMD_CHIP_ERASE);

  status = NOR_CFI_0002_PollForOperationStatus(hnor, 0U, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}

/**
  * @brief  Erase the entire NOR chip with command set ID 0002 in the Unlock Bypass mode.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  timeout_ms  NOR erasing timeout.
  * @retval HAL_BUSY    NOR state is active when calling this API.
  * @retval HAL_TIMEOUT NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR   NOR internal processing is failed.
  * @retval HAL_OK      The NOR flash device is successfully erased.
  */
hal_status_t HAL_NOR_CFI_0002_ChipEraseUnlockBypass(hal_nor_handle_t *hnor, uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_ERASE_ACTIVE);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U);

  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_ERASE_SETUP);
  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_CHIP_ERASE);

  status = NOR_CFI_0002_PollForOperationStatus(hnor, 0U, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}

/**
  * @brief  Erase a specified block of the NOR flash memory with command set ID 0002.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  block_offset_byte NOR memory internal block offset to erase in bytes.
  * @param  timeout_ms        NOR erasing timeout.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_TIMEOUT       NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR         NOR internal processing is failed.
  * @retval HAL_OK            The block is successfully erased.
  */
hal_status_t HAL_NOR_CFI_0002_BlockErase(hal_nor_handle_t *hnor, uint32_t block_offset_byte, uint32_t timeout_ms)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_ERASE_ACTIVE);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_FIRST),
                NOR_CFI_0002_CMD_UNLOCK_FIRST);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_SECOND),
                NOR_CFI_0002_CMD_UNLOCK_SECOND);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_THIRD),
                NOR_CFI_0002_CMD_ERASE_SETUP);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_FIRST),
                NOR_CFI_0002_CMD_UNLOCK_FIRST);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_SECOND),
                NOR_CFI_0002_CMD_UNLOCK_SECOND);
  FMC_NOR_Write((FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + block_offset_byte),
                NOR_CFI_0002_CMD_BLOCK_ERASE);

  status = NOR_CFI_0002_PollForOperationStatus(hnor, block_offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}

/**
  * @brief  Erase a specified block of the NOR flash memory with command set ID 0002 in the Unlock Bypass mode.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  block_offset_byte NOR memory internal block offset to erase in bytes.
  * @param  timeout_ms        NOR erasing timeout.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_TIMEOUT       NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR         NOR internal processing is failed.
  * @retval HAL_OK            The block is successfully erased.
  */
hal_status_t HAL_NOR_CFI_0002_BlockEraseUnlockBypass(hal_nor_handle_t *hnor, uint32_t block_offset_byte,
                                                     uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_ERASE_ACTIVE);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U);

  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_ERASE_SETUP);
  FMC_NOR_Write((device_addr + block_offset_byte), NOR_CFI_0002_CMD_BLOCK_ERASE);

  status = NOR_CFI_0002_PollForOperationStatus(hnor, block_offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}

/**
  * @brief  Check whether a specified main block of the NOR flash memory is completely erased with command set ID 0002.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  block_offset_byte NOR memory internal block offset to erase in bytes.
  * @param  timeout_ms        NOR blank check timeout.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_TIMEOUT       NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR         NOR block is not completely erased.
  * @retval HAL_OK            The NOR block is successfully erased.
  */
hal_status_t HAL_NOR_CFI_0002_BlockBlankCheck(hal_nor_handle_t *hnor, uint32_t block_offset_byte, uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_READ_ACTIVE);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + block_offset_byte;

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_FIRST),
                NOR_CFI_0002_CMD_UNLOCK_FIRST);
  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_0002_ADDR_SECOND),
                NOR_CFI_0002_CMD_UNLOCK_SECOND);
  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_BLANK_CHECK_SETUP_FIRST);
  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_BLANK_CHECK_SETUP_SECOND);
  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_BLANK_CHECK_SETUP_THIRD);
  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_BLANK_CHECK_SETUP_FOURTH);
  FMC_NOR_Write(device_addr, NOR_CFI_0002_CMD_CONFIRM);

  status = NOR_CFI_0002_PollForOperationStatus(hnor, block_offset_byte, timeout_ms);
  if (status == HAL_TIMEOUT)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}
/**
  * @}
  */
/** @addtogroup NOR_Exported_Functions_Group6
  * @{
This subsection provides a set of functions allowing to control the input and output operations of the CFI compliant
16-bits NOR memories with the command set ID 0003 :
  - HAL_NOR_CFI_0003_Reset()
  - HAL_NOR_CFI_0003_ReadArray()
  - HAL_NOR_CFI_0003_ReadDeviceIdentifier()
  - HAL_NOR_CFI_0003_ReadStatusRegister()
  - HAL_NOR_CFI_0003_ClearStatusRegister()
  - HAL_NOR_CFI_0003_Program()
  - HAL_NOR_CFI_0003_DoubleDataProgram()
  - HAL_NOR_CFI_0003_QuadrupleDataProgram()
  - HAL_NOR_CFI_0003_BlockErase()
  - HAL_NOR_CFI_0003_ProgramSuspend()
  - HAL_NOR_CFI_0003_EraseSuspend()
  - HAL_NOR_CFI_0003_ProgramResume()
  - HAL_NOR_CFI_0003_EraseResume()
  - HAL_NOR_CFI_0003_BlockLock()
  - HAL_NOR_CFI_0003_BlockLockDown()
  - HAL_NOR_CFI_0003_BlockUnlock()
  - HAL_NOR_CFI_0003_ProgramProtectionRegister()
  */

/**
  * @brief  Reset the NOR flash device  with command set ID 0003.
  * @param  hnor     Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_BUSY NOR state is active when calling this API.
  * @retval HAL_OK   The NOR flash device is reset successfully.
  */
hal_status_t HAL_NOR_CFI_0003_Reset(hal_nor_handle_t *hnor)
{
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_FAULT |
                   (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_FAULT |
                              (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0003_CMD_READ_ARRAY);

  if (previous_state == HAL_NOR_STATE_FAULT)
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }
  else
  {
    hnor->global_state = previous_state;
  }

  return HAL_OK;
}

/**
  * @brief  Read data from the NOR flash memory with command set ID 0003.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte       NOR memory internal offset to read from in bytes.
  * @param  p_data            Pointer to the buffer that receives the data read from the NOR memory.
  * @param  size_byte         Number of bytes to read.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data pointer is NULL or when the size is 0 byte.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_OK            The data is successfully read.
  */
hal_status_t HAL_NOR_CFI_0003_ReadArray(hal_nor_handle_t *hnor, uint32_t offset_byte, void *p_data, uint32_t size_byte)
{
  uint32_t device_addr;
  uint32_t addr;
  uint32_t size = size_byte;
  volatile hal_nor_state_t previous_state;
  uint8_t *p_dest_data;

  ASSERT_DBG_PARAM(hnor      != NULL);
  ASSERT_DBG_PARAM(p_data    != NULL);
  ASSERT_DBG_PARAM(size_byte != 0U);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                   (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                              (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED), HAL_NOR_STATE_READ_ACTIVE, previous_state);

  p_dest_data = (uint8_t *)(uint32_t)p_data;
  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U);
  addr = device_addr + offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_READ_ARRAY);

  while (size > 0U)
  {
    *p_dest_data = *(volatile uint8_t *)addr;
    ++p_dest_data;
    ++addr;
    --size;
  }

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Read NOR flash memory identifier with command set ID 0003.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  p_nor_id          Pointer to a @ref hal_nor_cfi_0003_device_id_t structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_nor_id pointer is NULL.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_OK            The device identifier is successfully read.
  */
hal_status_t HAL_NOR_CFI_0003_ReadDeviceIdentifier(hal_nor_handle_t *hnor, hal_nor_cfi_0003_device_id_t *p_nor_id)
{
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor     != NULL);
  ASSERT_DBG_PARAM(p_nor_id != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                   (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_nor_id == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED |
                              (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED), HAL_NOR_STATE_READ_ACTIVE, previous_state);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_CMD_READ_DEVICE_ID);

  p_nor_id->device_manufacturer_code =
    *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_MANUFACTURER_CODE);
  p_nor_id->device_code =
    *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, NOR_CFI_ADDR_DEVICE_CODE_1);

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Read the NOR flash memory operation status with command set ID 0003.
  * @param  hnor                         Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte                  NOR memory internal offset where the process was issued.
  * @retval HAL_NOR_DEVICE_STATE_SUCCESS NOR internal processing successfully completed.
  * @retval HAL_NOR_DEVICE_STATE_ONGOING NOR internal processing is ongoing.
  * @retval HAL_NOR_DEVICE_STATE_ERROR   NOR internal processing is failed.
  */
hal_nor_device_state_t HAL_NOR_CFI_0003_ReadStatusRegister(hal_nor_handle_t *hnor, uint32_t offset_byte)
{
  hal_nor_device_state_t status;

  ASSERT_DBG_PARAM(hnor != NULL);
  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_FAULT |
                   (uint32_t)HAL_NOR_STATE_PROGRAM_SUSPENDED | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  status = NOR_CFI_0003_ReadStatusRegister(hnor, offset_byte);

  return status;
}

/**
  * @brief  Clear the NOR flash memory status register with command set ID 0003.
  * @param  hnor     Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_BUSY NOR state is active when calling this API.
  * @retval HAL_OK   The status register is cleared.
  */
hal_status_t HAL_NOR_CFI_0003_ClearStatusRegister(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_PROGRAM_ACTIVE);


  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0003_CMD_CLEAR_STATUS_REG);

  hnor->global_state = HAL_NOR_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Write a 16-bits data to the NOR flash memory with command set ID 0003.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte NOR memory internal offset to write in, in bytes.
  * @param  data        Data to write in the NOR memory.
  * @param  timeout_ms  NOR programming timeout.
  * @retval HAL_BUSY    NOR state is active when calling this API.
  * @retval HAL_TIMEOUT NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR   NOR internal processing is failed.
  * @retval HAL_OK      The data is successfully written.
  */
hal_status_t HAL_NOR_CFI_0003_Program(hal_nor_handle_t *hnor, uint32_t offset_byte, uint16_t data, uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);
  ASSERT_DBG_PARAM(IS_NOR_OFFSET_16_BITS_ALIGNED(offset_byte));

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U);

  FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_PGM);

  FMC_NOR_Write(device_addr + offset_byte, data);

  status = NOR_CFI_0003_PollForOperationStatus(hnor, offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = previous_state;
  }

  return (status);
}

/**
  * @brief  Write double adjacent 16-bits data to the NOR flash memory with command set ID 0003.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte NOR memory internal offset to write in, in bytes.
  * @param  data        Data to write in the NOR memory.
  * @param  timeout_ms  NOR programming timeout.
  * @retval HAL_BUSY    NOR state is active when calling this API.
  * @retval HAL_TIMEOUT NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR   NOR internal processing is failed.
  * @retval HAL_OK      The data is successfully written.
  */
hal_status_t HAL_NOR_CFI_0003_DoubleDataProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, uint32_t data,
                                                uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;

  ASSERT_DBG_PARAM(hnor != NULL);
  ASSERT_DBG_PARAM(IS_NOR_OFFSET_16_BITS_ALIGNED(offset_byte));

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_PROGRAM_ACTIVE);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U);

  FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_DOUBLE_PGM);

  FMC_NOR_Write(device_addr, (uint16_t)(data & 0xFFFFU));
  FMC_NOR_Write((device_addr + 2U), (uint16_t)((data >> 16U) & 0xFFFFU));

  status = NOR_CFI_0003_PollForOperationStatus(hnor, offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}

/**
  * @brief  Write four adjacent 16-bits data to the NOR flash memory with command set ID 0003.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte NOR memory internal offset to write in, in bytes.
  * @param  data_msb    MSB data to write in the NOR memory.
  * @param  data_lsb    LSB data to write in the NOR memory.
  * @param  timeout_ms  NOR programming timeout.
  * @retval HAL_BUSY    NOR state is active when calling this API.
  * @retval HAL_TIMEOUT NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR   NOR internal processing is failed.
  * @retval HAL_OK      The data is successfully written.
  */
hal_status_t HAL_NOR_CFI_0003_QuadrupleDataProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, uint32_t data_msb,
                                                   uint32_t data_lsb, uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;

  ASSERT_DBG_PARAM(hnor != NULL);
  ASSERT_DBG_PARAM(IS_NOR_OFFSET_16_BITS_ALIGNED(offset_byte));

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_PROGRAM_ACTIVE);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U);

  FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_QUADRPLE_PGM);

  FMC_NOR_Write(device_addr, (uint16_t)(data_lsb & 0xFFFFU));
  FMC_NOR_Write((device_addr + 2U), (uint16_t)((data_lsb >> 16U) & 0xFFFFU));

  FMC_NOR_Write((device_addr + 4U), (uint16_t)(data_msb & 0xFFFFU));
  FMC_NOR_Write((device_addr + 6U), (uint16_t)((data_msb >> 16U) & 0xFFFFU));

  status = NOR_CFI_0003_PollForOperationStatus(hnor, offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}

/**
  * @brief  Erase a specified block of the NOR flash memory with command set ID 0003.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  block_offset_byte NOR memory internal block offset to erase in bytes.
  * @param  timeout_ms        NOR erasing timeout.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_TIMEOUT       NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR         NOR internal processing is failed.
  * @retval HAL_OK            The block is successfully erased.
  */
hal_status_t HAL_NOR_CFI_0003_BlockErase(hal_nor_handle_t *hnor, uint32_t block_offset_byte, uint32_t timeout_ms)
{
  uint32_t device_addr;
  hal_status_t status;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_ERASE_ACTIVE);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + block_offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_BLOCK_ERASE_SETUP);
  FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_CONFIRM);

  status = NOR_CFI_0003_PollForOperationStatus(hnor, block_offset_byte, timeout_ms);
  if (status != HAL_OK)
  {
    hnor->global_state = HAL_NOR_STATE_FAULT;
  }
  else
  {
    hnor->global_state = HAL_NOR_STATE_IDLE;
  }

  return (status);
}

/**
  * @brief  Suspend the programming operation of the NOR flash memory with command set ID 0003.
  * @param  hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_OK The program operation is suspended.
  */
hal_status_t HAL_NOR_CFI_0003_ProgramSuspend(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_PROGRAM_ACTIVE);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0003_CMD_SUSPEND);

  hnor->global_state = HAL_NOR_STATE_PROGRAM_SUSPENDED;

  return HAL_OK;
}

/**
  * @brief  Suspend the block erase operation of the NOR flash memory with command set ID 0003.
  * @param  hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_OK The erase operation is suspended.
  */
hal_status_t HAL_NOR_CFI_0003_EraseSuspend(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_ERASE_ACTIVE);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0003_CMD_SUSPEND);

  hnor->global_state = HAL_NOR_STATE_ERASE_SUSPENDED;

  return HAL_OK;
}

/**
  * @brief  Resume the programming operation of the NOR flash memory with command set ID 0003.
  * @param  hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_OK The suspended program operation is resumed.
  */
hal_status_t HAL_NOR_CFI_0003_ProgramResume(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_PROGRAM_SUSPENDED);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0003_CMD_CONFIRM);

  hnor->global_state = HAL_NOR_STATE_PROGRAM_ACTIVE;

  return HAL_OK;
}

/**
  * @brief  Resume the block erase operation of the NOR flash memory with command set ID 0003.
  * @param  hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_OK The suspended erase operation is resumed.
  */
hal_status_t HAL_NOR_CFI_0003_EraseResume(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_Write(FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U), NOR_CFI_0003_CMD_CONFIRM);

  hnor->global_state = HAL_NOR_STATE_ERASE_ACTIVE;

  return HAL_OK;
}

/**
  * @brief  Lock a specified block of the NOR flash memory with command set ID 0003,
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  block_offset_byte NOR memory internal block offset to lock in bytes.
  * @note   Locked blocks cannot be programmed or erased, they can only be read.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_OK            The block is successfully locked.
  */
hal_status_t HAL_NOR_CFI_0003_BlockLock(hal_nor_handle_t *hnor, uint32_t block_offset_byte)
{
  uint32_t device_addr;
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + block_offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_BLOCK_LOCK_SETUP);
  FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_BLOCK_LOCK);

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Lock-down a specified block of the NOR flash memory with command set ID 0003.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  block_offset_byte NOR memory internal block offset to lock-down in bytes.
  * @note   Locked-down blocks cannot be programmed or erased, they can only be read. The locked-down blocks can only
  *         be unlocked by issuing the unlock block with 'WP' Write Protect pin de-asserted.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_OK            The block is successfully locked-down.
  */
hal_status_t HAL_NOR_CFI_0003_BlockLockDown(hal_nor_handle_t *hnor, uint32_t block_offset_byte)
{
  uint32_t device_addr;
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + block_offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_BLOCK_LOCK_SETUP);
  FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_BLOCK_LOCK_DOWN);

  hnor->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Unlock a specified block of the NOR flash memory with command set ID 0003.
  * @param  hnor              Pointer to a @ref hal_nor_handle_t structure.
  * @param  block_offset_byte NOR memory internal block offset to unlock in bytes.
  * @note   Unlocked blocks can be read, programmed and erased.
  * @retval HAL_BUSY          NOR state is active when calling this API.
  * @retval HAL_OK            The block is successfully unlocked.
  */
hal_status_t HAL_NOR_CFI_0003_BlockUnlock(hal_nor_handle_t *hnor, uint32_t block_offset_byte)
{
  uint32_t device_addr;
  volatile hal_nor_state_t previous_state;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, (uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED);

  FMC_NOR_CHECK_UPDATE_STATE(hnor, global_state,
                             ((uint32_t)HAL_NOR_STATE_IDLE | (uint32_t)HAL_NOR_STATE_ERASE_SUSPENDED),
                             HAL_NOR_STATE_PROGRAM_ACTIVE, previous_state);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + block_offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_BLOCK_LOCK_SETUP);
  FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_CONFIRM);

  hnor->global_state = previous_state;

  return HAL_OK;
}

#if defined(USE_HAL_NOR_PROTECTION) && (USE_HAL_NOR_PROTECTION == 1U)

/**
  * @brief  Program any of the protection registers of the NOR flash memory with command set ID 0001.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte NOR memory internal protection register offset to program in bytes.
  * @param  data        Data to write in the protection register.
  * @retval HAL_BUSY    NOR state is active when calling this API.
  * @retval HAL_OK      The protection register is successfully programmed.
  */
hal_status_t HAL_NOR_CFI_0003_ProgramProtectionRegister(hal_nor_handle_t *hnor, uint32_t offset_byte, uint16_t data)
{
  uint32_t device_addr;

  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnor, global_state, HAL_NOR_STATE_IDLE, HAL_NOR_STATE_PROGRAM_ACTIVE);

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + offset_byte;

  FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_PROTECTION_PGM_SETUP);
  FMC_NOR_Write(device_addr, data);

  hnor->global_state = HAL_NOR_STATE_IDLE;

  return HAL_OK;
}

#endif /* USE_HAL_NOR_PROTECTION */
/**
  * @}
  */

/** @addtogroup NOR_Exported_Functions_Group7
  * @{
This subsection provides a set of functions allowing to control the NOR device :

- HAL_NOR_EnableWriteProtection()    : used to enable the write protection of the corresponding NOR device.
- HAL_NOR_DisableWriteProtection()   : used to disable the write protection of the corresponding NOR device.
- HAL_NOR_IsEnabledWriteProtection() : used to get the corresponding NOR device write protection status.

- HAL_NOR_Enable()    : used to enable the corresponding NOR device.
- HAL_NOR_Disable()   : used to disable the corresponding NOR device.
- HAL_NOR_IsEnabled() : used to get the corresponding NOR device status.
  */

/**
  * @brief   Enable the corresponding NOR device write protection.
  * @param   hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @warning This API can be used once the NOR is fully configured, when both memory and timing configuration APIs
  *          are called.
  * @retval  HAL_OK The write protection is successfully enabled.
  */
hal_status_t HAL_NOR_EnableWriteProtection(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  FMC_NOR_SRAM_EnableWriteProtection(NOR_GET_INSTANCE(hnor));

  hnor->wr_protection_state = HAL_NOR_WR_PROTECTED;

  return HAL_OK;
}

/**
  * @brief   Disable the corresponding NOR device write protection.
  * @param   hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @warning This API can be used once the NOR is fully configured, when both memory and timing configuration APIs
  *          are called.
  * @retval  HAL_OK The write protection is successfully disabled.
  */
hal_status_t HAL_NOR_DisableWriteProtection(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  FMC_NOR_SRAM_DisableWriteProtection(NOR_GET_INSTANCE(hnor));

  hnor->wr_protection_state = HAL_NOR_WR_NOT_PROTECTED;

  return HAL_OK;
}

/**
  * @brief  Get the corresponding NOR device write protection status.
  * @param  hnor                     Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_NOR_WR_NOT_PROTECTED The NOR write protection is disabled.
  * @retval HAL_NOR_WR_PROTECTED     The NOR write protection is enabled.
  */
hal_nor_wr_protection_state_t HAL_NOR_IsEnabledWriteProtection(const hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  return ((hal_nor_wr_protection_state_t)(uint32_t)FMC_NOR_SRAM_IsEnabled_Protection(NOR_GET_INSTANCE(hnor)));
}

/**
  * @brief   Enable the corresponding NOR device.
  * @param   hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @warning This API can be used once the NOR is fully configured, when both memory and timing configuration APIs
  *          are called.
  * @retval  HAL_OK The NOR is successfully enabled.

  */
hal_status_t HAL_NOR_Enable(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  FMC_NOR_SRAM_Enable(NOR_GET_INSTANCE(hnor));

  return HAL_OK;
}

/**
  * @brief   Disable the corresponding NOR device.
  * @param   hnor   Pointer to a @ref hal_nor_handle_t structure.
  * @warning This API can be used once the NOR is fully configured (both memory and timing configuration APIs are
  *          performed). In case no write or read access is running, this API can be called to save power and maintain
  *          the current configuration instead of calling HAL_NOR_DeInit() API then resuming the configuration sequence.
  * @retval  HAL_OK The NOR is successfully disabled.
  */
hal_status_t HAL_NOR_Disable(hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  ASSERT_DBG_STATE(hnor->global_state, HAL_NOR_STATE_IDLE);

  FMC_NOR_SRAM_Disable(NOR_GET_INSTANCE(hnor));

  return HAL_OK;
}

/**
  * @brief  Get the corresponding NOR device status.
  * @param  hnor             Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_NOR_DISABLED The NOR is disabled.
  * @retval HAL_NOR_ENABLED  The NOR is enabled.
  */
hal_nor_status_t HAL_NOR_IsEnabled(const hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  return ((hal_nor_status_t)(uint32_t)FMC_NOR_SRAM_IsEnabled(NOR_GET_INSTANCE(hnor)));
}
/**
  * @}
  */

#if defined(USE_HAL_NOR_USER_DATA) && (USE_HAL_NOR_USER_DATA == 1U)

/** @addtogroup NOR_Exported_Functions_Group8
  * @{
This subsection provides a set of functions allowing to set and retrieve user specific data :
- The HAL_NOR_SetUserData() API : used to store user data pointer into the handle.
- The HAL_NOR_GetUserData() API : used to retrieve user data pointer from the handle.
  */

/**
  * @brief  Store user data pointer into the handle.
  * @param  hnor       Pointer to a hal_nor_handle_t structure.
  * @param p_user_data Pointer to the user data.
  */
void HAL_NOR_SetUserData(hal_nor_handle_t *hnor, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  hnor->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve user data pointer from the handle.
  * @param  hnor Pointer to a hal_nor_handle_t structure.
  * @retval Pointer to the user data.
  */
const void *HAL_NOR_GetUserData(const hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  return (hnor->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_NOR_USER_DATA */

/** @addtogroup NOR_Exported_Functions_Group9
  * @{
This subsection provides a set of functions allowing to retrieve the NOR global state and the clock frequency :
- HAL_NOR_GetClockFreq() : used to retrieve clock frequency.
- HAL_NOR_GetState()     : used to retrieve current global state.
  */

/**
  * @brief  Get the clock frequency.
  * @param  hnor Pointer to a @ref hal_nor_handle_t structure.
  * @retval uint32_t Frequency in Hz.
  */
uint32_t HAL_NOR_GetClockFreq(const hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM((hnor != NULL));
  ASSERT_DBG_STATE(hnor->global_state, (hal_nor_state_t)((uint32_t)HAL_NOR_STATE_INIT              |
                                                         (uint32_t)HAL_NOR_STATE_CONFIGURED        |
                                                         (uint32_t)HAL_NOR_STATE_MEMORY_CONFIGURED |
                                                         (uint32_t)HAL_NOR_STATE_IDLE));
  STM32_UNUSED(hnor);

  return HAL_RCC_GetHCLKFreq();
}

/**
  * @brief  Get the current global state.
  * @param  hnor                            Pointer to a @ref hal_nor_handle_t structure.
  * @retval HAL_NOR_STATE_RESET             The NOR not yet initialized.
  * @retval HAL_NOR_STATE_INIT              The NOR initialized but not yet configured.
  * @retval HAL_NOR_STATE_CONFIGURED        The NOR initialized, FMC peripheral configured but not yet ready for use
  * @retval HAL_NOR_STATE_MEMORY_CONFIGURED The NOR initialized, FMC, memory configured but not yet ready for use.
  * @retval HAL_NOR_STATE_IDLE              The NOR initialized, FMC, memory configured, NOR enabled and ready for use.
  * @retval HAL_NOR_STATE_PROGRAM_ACTIVE    The NOR internal program processing is ongoing.
  * @retval HAL_NOR_STATE_ERASE_ACTIVE      The NOR internal erase processing is ongoing.
  * @retval HAL_NOR_STATE_READ_ACTIVE       The NOR internal read processing is ongoing.
  * @retval HAL_NOR_STATE_PROGRAM_SUSPENDED The NOR program operation is suspended.
  * @retval HAL_NOR_STATE_ERASE_SUSPENDED   The NOR erase operation is suspended.
  * @retval HAL_NOR_STATE_FAULT             The NOR internal processing encountered an error.
  */
hal_nor_state_t  HAL_NOR_GetState(const hal_nor_handle_t *hnor)
{
  ASSERT_DBG_PARAM(hnor != NULL);

  return hnor->global_state;
}
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup NOR_Private_Functions
  * @{
This subsection provides a set of functions allowing to provide information on the current operations :
- The NOR_CFI_0001_ReadStatusRegister() API : Used to get the NOR device status register with command set 1.
- The NOR_CFI_0002_ReadStatusRegister() API : Used to get the NOR device status register with command set 2.
- The NOR_CFI_0003_ReadStatusRegister() API : Used to get the NOR device status register with command set 3.
- The NOR_CFI_0001_PollForOperationStatus() API : Used to retrieve the NOR current operation status with command set 1.
- The NOR_CFI_0002_PollForOperationStatus() API : Used to retrieve the NOR current operation status with command set 2.
- The NOR_CFI_0003_PollForOperationStatus() API : Used to retrieve the NOR current operation status with command set 3.
  */

/**
  * @brief  Get the the NOR device status register with command set 0001.
  * @param  hnor                         Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte                  NOR memory internal offset where the process was issued.
  * @retval HAL_NOR_DEVICE_STATE_SUCCESS NOR internal processing successfully completed.
  * @retval HAL_NOR_DEVICE_STATE_ONGOING NOR internal processing is ongoing.
  * @retval HAL_NOR_DEVICE_STATE_ERROR   NOR internal processing is failed.
  */
hal_nor_device_state_t NOR_CFI_0001_ReadStatusRegister(const hal_nor_handle_t *hnor, uint32_t offset_byte)
{
  uint32_t device_addr;
  uint16_t status_reg_1;
  uint16_t status_reg_2;
  hal_nor_device_state_t status = HAL_NOR_DEVICE_STATE_ONGOING;

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U);

  FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_READ_STATUS_REG);
  status_reg_1 = *(volatile uint16_t *)(device_addr + offset_byte);

  if ((status_reg_1 & NOR_CFI_DQ7_MASK) != 0U)
  {
    FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_READ_STATUS_REG);
    status_reg_2 = *(volatile uint16_t *)(device_addr + offset_byte);
    if ((status_reg_2  & (NOR_CFI_DQ5_MASK | NOR_CFI_DQ4_MASK)) != 0U)
    {
      /* Clear the Status Register  */
      FMC_NOR_Write(device_addr, NOR_CFI_0001_CMD_CLEAR_STATUS_REG);
      status = HAL_NOR_DEVICE_STATE_ERROR;
    }
    else if ((status_reg_2  & NOR_CFI_DQ0_MASK) != 0U)
    {
      status = HAL_NOR_DEVICE_STATE_ONGOING;
    }
    else
    {
      status = HAL_NOR_DEVICE_STATE_SUCCESS;
    }
  }
  return status;
}

/**
  * @brief  Get the the NOR device status register with command set 0002.
  * @param  hnor                         Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte                  NOR memory internal offset where the process was issued.
  * @retval HAL_NOR_DEVICE_STATE_SUCCESS NOR internal processing successfully completed.
  * @retval HAL_NOR_DEVICE_STATE_ONGOING NOR internal processing is ongoing.
  * @retval HAL_NOR_DEVICE_STATE_ERROR   NOR internal processing is failed.
  */
hal_nor_device_state_t NOR_CFI_0002_ReadStatusRegister(const hal_nor_handle_t *hnor, uint32_t offset_byte)
{
  uint32_t device_addr;
  uint16_t status_reg_1;
  uint16_t status_reg_2;
  hal_nor_device_state_t status = HAL_NOR_DEVICE_STATE_ONGOING;

  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U) + offset_byte;

  /* Read NOR status register */
  status_reg_1 = *(volatile uint16_t *)device_addr;
  status_reg_2 = *(volatile uint16_t *)device_addr;

  /* If DQ6 did not toggle between the two reads then return HAL_NOR_DEVICE_STATE_SUCCESS */
  if ((status_reg_1 & NOR_CFI_DQ6_MASK) == (status_reg_2 & NOR_CFI_DQ6_MASK))
  {
    return HAL_NOR_DEVICE_STATE_SUCCESS ;
  }

  if ((status_reg_1 & NOR_CFI_DQ5_MASK) == NOR_CFI_DQ5_MASK)
  {
    status = HAL_NOR_DEVICE_STATE_ONGOING;
  }

  status_reg_1 = *(volatile uint16_t *)device_addr;
  status_reg_2 = *(volatile uint16_t *)device_addr;

  /* If DQ6 did not toggle between the two reads then return HAL_NOR_DEVICE_STATE_SUCCESS */
  if ((status_reg_1 & NOR_CFI_DQ6_MASK) == (status_reg_2 & NOR_CFI_DQ6_MASK))
  {
    return HAL_NOR_DEVICE_STATE_SUCCESS;
  }
  if ((status_reg_1 & NOR_CFI_DQ5_MASK) == NOR_CFI_DQ5_MASK)
  {
    return HAL_NOR_DEVICE_STATE_ERROR;
  }

  return status;
}

/**
  * @brief  Get the NOR device status register with command set 0003.
  * @param  hnor                         Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte                  NOR memory internal offset where the process was issued.
  * @retval HAL_NOR_DEVICE_STATE_SUCCESS NOR internal processing successfully completed.
  * @retval HAL_NOR_DEVICE_STATE_ONGOING NOR internal processing is ongoing.
  * @retval HAL_NOR_DEVICE_STATE_ERROR   NOR internal processing is failed.
  */
hal_nor_device_state_t NOR_CFI_0003_ReadStatusRegister(const hal_nor_handle_t *hnor, uint32_t offset_byte)
{
  uint32_t device_addr;
  uint16_t status_reg_1;
  uint16_t status_reg_2;
  hal_nor_device_state_t status = HAL_NOR_DEVICE_STATE_ONGOING;
  device_addr = FMC_NOR_CalculateMemoryAddress((uint32_t)hnor->instance, 0U);

  FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_READ_STATUS_REG);
  status_reg_1 = *(volatile uint16_t *)(device_addr + offset_byte);

  if ((status_reg_1 & NOR_CFI_DQ7_MASK) != 0U)
  {
    FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_READ_STATUS_REG);
    status_reg_2 = *(volatile uint16_t *)(device_addr + offset_byte);
    if ((status_reg_2  & (NOR_CFI_DQ5_MASK | NOR_CFI_DQ4_MASK)) != 0U)
    {
      /* Clear the Status Register  */
      FMC_NOR_Write(device_addr, NOR_CFI_0003_CMD_CLEAR_STATUS_REG);
      status = HAL_NOR_DEVICE_STATE_ERROR;
    }
    else
    {
      status = HAL_NOR_DEVICE_STATE_SUCCESS;
    }
  }
  return status;
}

/**
  * @brief Get the status of the current operation with command set 0001.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte NOR memory internal offset where the process was issued.
  * @param  timeout_ms  NOR operation timeout.
  * @retval HAL_TIMEOUT NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR   NOR internal processing is failed.
  * @retval HAL_OK      NOR internal processing is successfully completed.
  */
static hal_status_t NOR_CFI_0001_PollForOperationStatus(hal_nor_handle_t *hnor, uint32_t offset_byte,
                                                        uint32_t timeout_ms)
{
  uint64_t timeout = (((uint64_t)timeout_ms * (uint64_t)1000) / NOR_STATUS_LATENCY) + 1U;
  hal_nor_device_state_t status = HAL_NOR_DEVICE_STATE_ONGOING;

  while ((status == HAL_NOR_DEVICE_STATE_ONGOING) && (timeout > 0U))
  {
    status = NOR_CFI_0001_ReadStatusRegister(hnor, offset_byte);
    if (status == HAL_NOR_DEVICE_STATE_ERROR)
    {
      return  HAL_ERROR;
    }
    timeout--;
  }
  if (timeout == 0U)
  {
    return HAL_TIMEOUT;
  }
  return HAL_OK;
}

/**
  * @brief Get the status of the current operation with command set 0002.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte NOR memory internal offset where the process was issued.
  * @param  timeout_ms  NOR operation timeout.
  * @retval HAL_TIMEOUT NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR   NOR internal processing is failed.
  * @retval HAL_OK      NOR internal processing is successfully completed.
  */
static hal_status_t NOR_CFI_0002_PollForOperationStatus(hal_nor_handle_t *hnor, uint32_t offset_byte,
                                                        uint32_t timeout_ms)
{
  uint64_t timeout = (((uint64_t)timeout_ms * (uint64_t)1000) / NOR_STATUS_LATENCY) + 1U;
  hal_nor_device_state_t status = HAL_NOR_DEVICE_STATE_ONGOING;

  while ((status == HAL_NOR_DEVICE_STATE_ONGOING) && (timeout > 0U))
  {
    status = NOR_CFI_0002_ReadStatusRegister(hnor, offset_byte);
    if (status == HAL_NOR_DEVICE_STATE_ERROR)
    {
      return  HAL_ERROR;
    }
    timeout--;
  }
  if (timeout == 0U)
  {
    return HAL_TIMEOUT;
  }
  return HAL_OK;
}

/**
  * @brief Get the status of the current operation with command set 0003.
  * @param  hnor        Pointer to a @ref hal_nor_handle_t structure.
  * @param  offset_byte NOR memory internal offset where the process was issued.
  * @param  timeout_ms  NOR operation timeout.
  * @retval HAL_TIMEOUT NOR internal processing exceeded the timeout.
  * @retval HAL_ERROR   NOR internal processing is failed.
  * @retval HAL_OK      NOR internal processing is successfully completed.
  */
static hal_status_t NOR_CFI_0003_PollForOperationStatus(hal_nor_handle_t *hnor, uint32_t offset_byte,
                                                        uint32_t timeout_ms)
{
  uint64_t timeout = (((uint64_t)timeout_ms * (uint64_t)1000) / NOR_STATUS_LATENCY) + 1U;
  hal_nor_device_state_t status = HAL_NOR_DEVICE_STATE_ONGOING;

  while ((status == HAL_NOR_DEVICE_STATE_ONGOING) && (timeout > 0U))
  {
    status = NOR_CFI_0003_ReadStatusRegister(hnor, offset_byte);
    if (status == HAL_NOR_DEVICE_STATE_ERROR)
    {
      return  HAL_ERROR;
    }
    timeout--;
  }
  if (timeout == 0U)
  {
    return HAL_TIMEOUT;
  }
  return HAL_OK;
}
/**
  * @}
  */

#endif /* HAL_NOR_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
#endif /* defined(FMC_NORSRAM_BK1) */
