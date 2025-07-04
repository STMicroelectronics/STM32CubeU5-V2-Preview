/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_flash.c
  * @brief   This file provides HAL FLASH IO memory services.
  **********************************************************************************************************************
  * @attention

  * Copyright (c) 2021-2025 STMicroelectronics.
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

/** @addtogroup FLASH
  * @{
This file provides firmware functions to manage the following functionalities of the Flash memory area

- Initialization and De-initialization functions
- Configuration functions
- Process operation functions
- IRQHandler functions
- Callback functions
- Status functions

# Flash main features

The flash memory interface manages accesses to flash memory, maximizing throughput to CPU, instruction cache and DMAs.
It implements the flash memory erase and program operations as well as the read and write protection mechanisms.
It also implements the security and privilege access control features.
It is optimized in terms of power consumption with dedicated modes when the MCU is in low-power modes.

Up to 4 Mbytes of flash memory supporting read-while-write capability (RWW).
- Dual bank architecture (bank 1 and bank 2)
- Main memory: up to 2 Mbytes per bank
- Information block: 64.5 Kbytes in bank 1
 128-bit wide data read with prefetch
- Standard and burst programming modes
- Read, program and erase operations in all voltage ranges
- 10 kcycles endurance on all flash memory. 100 kcycles on up to 256 Kbytes per bank
- Page erase, bank erase and mass erase (both banks)
- Bank swapping: the user flash memory address mapping of each bank can be swapped.
- Product security activated by TrustZone option bit (TZEN)
- Device life cycle managed by readout protection option byte (RDP)
- Four write protection areas (two per bank)
- TrustZone support:
- Two secure areas (1 per bank)
- Two secure HDP (hide protection) areas part of the secure areas (one per bank)
- Configurable protection against unprivileged accesses with flash page granularity
- Error code correction: 9-bit ECC per 128-bit quad-word allowing two bits error detection and one bit error correction
- Option-byte loader
- Advanced low-power modes (low-power read mode, bank power-down mode)

# Flash memory organization

The flash memory has the following main features:
- Capacity up to 4 Mbytes
- Dual-bank mode:
- up to 2 Mbytes per bank for main memory
- 8 Kbytes page size
- 137 bits wide data read and write (128 effective bits plus 9 ECC bits)
- Page, bank and mass erase
- Support read-while-write feature
- Support bank shutdown feature for power consumption saving
The flash memory is organized as follows:
- Main memory block organized as two banks of up to 2 Mbytes each containing up to 256 pages of 8 Kbytes
- An information block containing:
- 32 Kbytes for system memory. This area is immutable and reserved for use by STMicroelectronics.
  It contains the bootloader that is used to reprogram the flash memory through one of the user communication interfaces
  such as USB (DFU). The system memory is programmed by STMicroelectronics when the device is manufactured.
  For further details, refer to the application note STM32 microcontroller system memory boot mode (AN2606).
- 32 Kbytes immutable secure area containing the root security services (RSS and RSS library) developed by ST.
- 512 bytes OTP (one-time programmable) bytes for user data (32 quad-words).
  The OTP data cannot be erased and can be written only once.
- option bytes for user configuration. Unlike user flash memory and system memory, it is not mapped to any memory
  address and can be accessed only through the flash register interface

# How to use the Flash HAL module driver

## Initialization and De-initialization functions :
- Use HAL_FLASH_Init() to initialize the Flash handle and associate the physical instance.
- Use HAL_FLASH_DeInit() to de-initialize the Flash instance, When called, the API wait for end of ongoing process
  and put the Flash state machine in idle state.

## Configuration functions :
- Use HAL_FLASH_SetProgrammingMode() to set the programming mode. (After reset the Quad-word programming is selected).
- Use HAL_FLASH_GetProgrammingMode() to get the programming mode.

## Process operation functions :

### Polling mode operations :
- Use HAL_FLASH_ProgramByAddr() to program any Flash memory User area in polling mode using flash address according
  to selected programming mode.
- Use HAL_FLASH_ProgramByAddrAdapt() to program any Flash memory User area in polling mode using flash address with
  adaptive programming mode.
  The adaptive mode allows to optimize Flash programming access versus remaining data size with ignoring Flash
  programming mode selected by HAL_FLASH_SetProgrammingMode() API.
- Use HAL_FLASH_OTP_ProgramByAddr() to program any Flash memory OTP area in polling mode using flash OTP address
  according to selected programming mode.
- Use HAL_FLASH_OTP_ProgramByAddrAdapt() to program any Flash memory OTP area in polling mode using flash OTP address
  with adaptive programming mode.
  The adaptive mode allows to optimize Flash programming access versus remaining data size with ignoring Flash
  programming mode selected by HAL_FLASH_SetProgrammingMode() API.

- Use HAL_FLASH_EraseByAddr() to erase by address any Flash memory area in polling mode.
- Use HAL_FLASH_ErasePage() to erase by page any Flash memory area in polling mode.
- Use HAL_FLASH_EraseBank() to erase by bank any Flash memory area in polling mode.
- Use HAL_FLASH_MassErase() to mass erase the entire Flash memory area in polling mode.

- Use HAL_FLASH_NS_ProgramByAddr() to program any NSecure Flash memory User area from Secure context in polling mode
  using flash address according to selected programming mode.
- Use HAL_FLASH_NS_ProgramByAddrAdapt() to program any NSecure Flash memory User area from Secure context
  in polling mode using flash address with adaptive programming mode.
  The adaptive mode allows to optimize Flash programming access versus remaining data size with ignoring Flash
  programming mode selected by HAL_FLASH_SetProgrammingMode() API.
- Use HAL_FLASH_NS_OTP_ProgramByAddr() to program any Flash memory OTP area from Secure context in polling mode using
  flash OTP address according to selected programming mode.
- Use HAL_FLASH_NS_OTP_ProgramByAddrAdapt() to program any Flash memory OTP area from Secure context in polling mode
  using flash OTP address with adaptive programming mode.
  The adaptive mode allows to optimize Flash programming access versus remaining data size with ignoring Flash
  programming mode selected by HAL_FLASH_SetProgrammingMode() API.

- Use HAL_FLASH_NS_EraseByAddr() to erase by address any NSecure Flash memory area from Secure context in polling mode.
- Use HAL_FLASH_NS_ErasePage() to erase by page any NSecure Flash memory area from Secure context in polling mode.
- Use HAL_FLASH_NS_EraseBank() to erase by bank any NSecure Flash memory area from Secure context in polling mode.
- Use HAL_FLASH_NS_MassErase() to mass erase the entire NSecure Flash memory area from Secure context in polling mode.

### Interrupt mode operations :
- Configure the Flash interrupt priority using HAL_CORTEX_NVIC_SetPriority() function
- Enable the Flash IRQ handler using HAL_CORTEX_NVIC_EnableIRQ() function

- Use HAL_FLASH_RegisterProgramCpltCallback() to register the Flash program by address complete callback.
- Use HAL_FLASH_RegisterEraseByAddrCpltCallback() to register the Flash erase by address complete callback.
- Use HAL_FLASH_RegisterErasePageCpltCallback() to register the Flash erase by page complete callback.
- Use HAL_FLASH_RegisterEraseBankCpltCallback() to register the Flash erase by bank complete callback.
- Use HAL_FLASH_RegisterMassEraseCpltCallback() to register the Flash mass erase complete callback.
- Use HAL_FLASH_RegisterErrorCallback() to register the Flash error callback.
- Use HAL_FLASH_RegisterECCErrorCallback() to register the Flash ECC error callback.

- Use HAL_FLASH_ProgramByAddr_IT() to program any Flash memory User area in interrupt mode using flash address
  according to selected programming mode.
- Use HAL_FLASH_ProgramByAddrAdapt_IT() to program any Flash memory User area in interrupt mode using flash address
  with adaptive programming mode.
  The adaptive mode allows to optimize Flash programming access versus remaining data size with ignoring Flash
  programming mode selected by HAL_FLASH_SetProgrammingMode() API.
- Use HAL_FLASH_OTP_ProgramByAddr_IT() to program any Flash memory OTP area in interrupt mode using flash OTP address
  according to selected programming mode.
- Use HAL_FLASH_OTP_ProgramByAddrAdapt_IT() to program any Flash memory OTP area in interrupt mode using flash OTP
  address with adaptive programming mode.
  The adaptive mode allows to optimize Flash programming access versus remaining data size with ignoring Flash
  programming mode selected by HAL_FLASH_SetProgrammingMode() API.

- Use HAL_FLASH_EraseByAddr_IT() to erase by address any Flash memory area in interrupt mode.
- Use HAL_FLASH_ErasePage_IT() to erase by page any Flash memory area in interrupt mode.
- Use HAL_FLASH_EraseBank_IT() to erase by bank any Flash memory area in interrupt mode.
- Use HAL_FLASH_MassErase_IT() to mass erase the entire Flash memory area in interrupt mode.

- Use HAL_FLASH_NS_ProgramByAddr_IT() to program any NSecure Flash memory User area from Secure context in interrupt
  mode using flash address according to selected programming mode.
- Use HAL_FLASH_NS_ProgramByAddrAdapt_IT() to program any Flash memory User area from Secure context in interrupt
  mode using flash address with adaptive programming mode.
  The adaptive mode allows to optimize Flash programming access versus remaining data size with ignoring Flash
  programming mode selected by HAL_FLASH_SetProgrammingMode() API.
- Use HAL_FLASH_NS_OTP_ProgramByAddr_IT() to program any Flash memory OTP area from Secure context in interrupt mode
  using flash OTP address according to selected programming mode.
- Use HAL_FLASH_NS_OTP_ProgramByAddrAdapt_IT() to program any Flash memory OTP area from Secure context in interrupt
  mode using flash OTP address with adaptive programming mode.
  The adaptive mode allows to optimize Flash programming access versus remaining data size with ignoring Flash
  programming mode selected by HAL_FLASH_SetProgrammingMode() API.

- Use HAL_FLASH_NS_EraseByAddr_IT() to erase by address any NSecure Flash memory area from Secure context
  in interrupt mode.
- Use HAL_FLASH_NS_ErasePage()_IT() to erase by page any NSecure Flash memory area from Secure context
  in interrupt mode.
- Use HAL_FLASH_NS_EraseBank()_IT() to erase by bank any NSecure Flash memory area from Secure context
  in interrupt mode.
- Use HAL_FLASH_NS_MassErase()_IT() to mass erase the entire NSecure Flash memory area from Secure context
  in interrupt mode.

- Use HAL_FLASH_IRQHandler() to handle any Flash interrupt.
- Use HAL_FLASH_ProgramByAddr_IRQHandler() to handle any Flash program by address interrupt.
- Use HAL_FLASH_EraseByAddr_IRQHandler() to handle any Flash erase by address interrupt.
- Use HAL_FLASH_ErasePage_IRQHandler() to handle any Flash page erase interrupt.
- Use HAL_FLASH_EraseBank_IRQHandler() to handle any Flash bank erase interrupt.
- Use HAL_FLASH_MassErase_IRQHandler() to handle any Flash mass erase interrupt.

- Use HAL_FLASH_ECC_IRQHandler() interrupt subroutines to handle any Flash ECC single error correction interrupt.
- Use HAL_FLASH_NMI_IRQHandler() interrupt subroutine to handle any Flash NMI interrupt.

- Use HAL_FLASH_NS_IRQHandler() to handle any NSecure Flash interrupt from Secure context.
- Use HAL_FLASH_NS_ProgramByAddr_IRQHandler() to handle any NSecure Flash program by address interrupt
  from Secure context.
- Use HAL_FLASH_NS_EraseByAddr_IRQHandler() to handle any NSecure Flash erase by address interrupt
  from Secure context.
- Use HAL_FLASH_NS_ErasePage_IRQHandler() to handle any NSecure Flash page erase interrupt from Secure context.
- Use HAL_FLASH_NS_EraseBank_IRQHandler() to handle any NSecure Flash bank erase interrupt from Secure context.
- Use HAL_FLASH_NS_MassErase_IRQHandler() to handle any NSecure Flash mass erase interrupt from Secure context.

## Status functions :
- Use HAL_FLASH_GetOperation() to get the last Flash ongoing operation.
- Use HAL_FLASH_GetProgramOperationInfo() to get the last Flash programming operation information.
- Use HAL_FLASH_GetEraseByAddrOperationInfo() to get the last Flash erase by address operation information.
- Use HAL_FLASH_GetErasePageOperationInfo() to get the last Flash erase by page operation information.
- Use HAL_FLASH_GetEraseBankOperationInfo() to get the last Flash erase by bank operation information.
- Use HAL_FLASH_GetInterruptedByResetOperationInfo() to get the Flash interrupted by reset operation information.
- Use HAL_FLASH_GetInfo() to get the Flash memory organization information.
- Use HAL_FLASH_ECC_GetFailInfo() to get Flash ECC fail information.
- Use HAL_FLASH_GetSizeByte() to get the total Flash size in bytes.
- Use HAL_FLASH_GetBankNbr() to get the total Flash number of banks.
- Use HAL_FLASH_GetBankSizeByte() to get the total Flash size per bank.
- Use HAL_FLASH_GetUserFlashSizeByte() to get the User Flash size in bytes of any given bank.
- Use HAL_FLASH_GetUserFlashPageNbr() to get the User Flash number of pages per bank.
- Use HAL_FLASH_GetUserFlashPageSizeByte() to get the User Flash size of any given page.
- Use HAL_FLASH_GetUserFlashAddrOffset() to get the User Flash offset address of any given page.
- Use HAL_FLASH_GetState() to get the Flash current global state.
- Use HAL_FLASH_GetLastErrorCodes() to get the Flash last error codes.
- Use HAL_FLASH_SetUserData() to set the Flash User data within the handle.
- Use HAL_FLASH_GetUserData() to get the Flash User data from the handle.

## Configuration inside the Flash IO driver

Configuration defines            | Description     | Default value     | Note                                          |
---------------------------------|-----------------|-------------------|-----------------------------------------------|
PRODUCT                          | from IDE        |        NA         | The selected device (e.g., STM32U575xx)       |
USE_HAL_FLASH_MODULE             | from hal_conf.h |         1         | Allows usage of HAL Flash module              |
USE_ASSERT_DBG_PARAM             | from IDE        |       None        | Allows usage of parameter assertions          |
USE_ASSERT_DBG_STATE             | from IDE        |       None        | Allows usage of state assertions              |
USE_HAL_CHECK_PARAM              | from hal_conf.h |         0         | Allows usage of run-time parameter checks     |
USE_HAL_CHECK_PROCESS_STATE      | from hal_conf.h |         0         | Allows usage of load/store exclusive checks   |
USE_HAL_FLASH_CLK_ENABLE_MODEL   | from hal_conf.h | HAL_CLK_ENABLE_NO | Allows enabling the clock model for Flash     |
USE_HAL_FLASH_REGISTER_CALLBACKS | from hal_conf.h |         0         | Allows enabling callbacks register for Flash  |
USE_HAL_FLASH_GET_LAST_ERRORS    | from hal_conf.h |         0         | Allows usage of error code mechanism          |
USE_HAL_FLASH_USER_DATA          | from hal_conf.h |         0         | Allows usage of User data                     |
USE_HAL_FLASH_PROGRAM_BY_ADDR    | from hal_conf.h |         1         | Allows usage of program by address feature    |
USE_HAL_FLASH_ERASE_BY_ADDR      | from hal_conf.h |         1         | Allows usage of erase by address feature      |
USE_HAL_FLASH_ERASE_PAGE         | from hal_conf.h |         1         | Allows usage of erase by page feature         |
USE_HAL_FLASH_ERASE_BANK         | from hal_conf.h |         1         | Allows usage of erase by bank feature         |
USE_HAL_FLASH_MASS_ERASE         | from hal_conf.h |         1         | Allows usage of mass erase feature            |
USE_HAL_FLASH_ECC                | from hal_conf.h |         1         | Allows usage of ECC error handling feature    |
__ARM_FEATURE_CMSE               | from IDE        |         3         | Allows Secure access for current context      |
  */

#if defined (USE_HAL_FLASH_MODULE) && (USE_HAL_FLASH_MODULE == 1)

/* Private Constants -------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Private_Constants FLASH Private Constants
  * @{
  */
#define FLASH_QUADWORD_SIZE_IN_BYTE              16U   /*!< Flash quad-word Size in bytes                       */
#define FLASH_OPERATION_MAX_TIMEOUT              1000U /*!< Flash max timeout for various operations            */
#define FLASH_PROGRAM_OPERATION_QUADWORD_TIMEOUT 1U    /*!< Flash max timeout for a quad-word program operation */
#define FLASH_PROGRAM_OPERATION_BURST_TIMEOUT    1U    /*!< Flash max timeout for a burst program operation     */
#define FLASH_ERASE_PAGE_OPERATION_TIMEOUT       2U    /*!< Flash max timeout for a page erase operation        */

#define FLASH_ADAPTIVE_PROGRAMMING_QUADWORD 0x10U /*!< Flash adaptive quad-word granularity */
#define FLASH_ADAPTIVE_PROGRAMMING_BURST    0x80U /*!< Flash adaptive burst granularity     */
#define FLASH_ADAPTIVE_PROGRAMMING_ENABLED  0x01U /*!< Flash adaptive programming mode is disabled */
#define FLASH_ADAPTIVE_PROGRAMMING_DISABLED 0U    /*!< Flash adaptive programming mode is disabled */
/**
  * @}
  */

/* Private Macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Private_Macros FLASH Private Macros
  * @{
  */

/*! Macro to get the Flash instance from the handle */
#define FLASH_GET_INSTANCE(hflash) ((FLASH_TypeDef *)((uint32_t)(hflash)->instance))

/*! Macro to check Flash instance */
#define IS_FLASH_INSTANCE(instance) ((instance) == HAL_FLASH)

/*! Macro to check Flash programming mode */
#define IS_FLASH_PROGRAM_MODE_TYPE(value) (((value) == HAL_FLASH_PROGRAM_QUADWORD) \
                                           || ((value) == HAL_FLASH_PROGRAM_BURST))

/*! Macro to check Flash memory bank */
#define IS_FLASH_BANK(value) (((value) == HAL_FLASH_BANK_1) \
                              || ((value) == HAL_FLASH_BANK_2) \
                              || ((value) == HAL_FLASH_BANK_ALL))

/*! Macro to check Flash memory address */
#define IS_FLASH_ADDRESS(value) (((value) >= FLASH_BASE) ? \
                                 (((value) % FLASH_QUADWORD_SIZE_IN_BYTE) == 0U) : (0 == 1))

/*! Macro to check NSecure Flash memory address */
#define IS_FLASH_NS_ADDRESS(value) (((value) >= FLASH_BASE_NS) ? \
                                    (((value) % FLASH_QUADWORD_SIZE_IN_BYTE) == 0U) : (0 == 1))

/*! Macro to check Flash memory size is within valid range */
#define IS_FLASH_SIZE_IN_RANGE(flash_addr, size_byte) (((flash_addr) + (size_byte)) \
                                                       <= (FLASH_BASE + FLASH_SIZE_DEFAULT))

/*! Macro to check NSecure Flash memory size is within valid range */
#define IS_FLASH_NS_SIZE_IN_RANGE(flash_addr, size_byte) (((flash_addr) + (size_byte)) \
                                                          <= (FLASH_BASE_NS + FLASH_SIZE_DEFAULT))

/*! Macro to check Flash OTP memory address granularity */
#define IS_FLASH_OTP_ADDRESS(value) (((value) >= FLASH_OTP_BASE) ? \
                                     (((value) % FLASH_QUADWORD_SIZE_IN_BYTE) == 0U) : (0 == 1))

/*! Macro to check Flash OTP memory size is within valid range */
#define IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte) (((otp_addr) + (size_byte)) \
                                                         <= (FLASH_OTP_BASE + FLASH_OTP_SIZE))

/*! Macro to check Flash memory page and page number are within valid range */
#define IS_FLASH_PAGE_IN_RANGE(page, page_nbr) (((page) + (page_nbr)) <= (uint32_t)FLASH_PAGE_NB_DEFAULT)

/*! Macro to get the Flash erase bank */
#define FLASH_GET_ERASE_BANK(value) (((value) == HAL_FLASH_BANK_1) ? LL_FLASH_MASS_ERASE_BANK_1 : \
                                     ((value) == HAL_FLASH_BANK_2) ? LL_FLASH_MASS_ERASE_BANK_2 : \
                                     LL_FLASH_MASS_ERASE_BANK_ALL)

/*! Macro to get the Flash program operation timeout */
#define FLASH_GET_PROGRAM_OPERATION_TIMEOUT(value) (((value) == HAL_FLASH_PROGRAM_QUADWORD) ? \
                                                    FLASH_PROGRAM_OPERATION_QUADWORD_TIMEOUT : \
                                                    FLASH_PROGRAM_OPERATION_BURST_TIMEOUT)

/**
  * @}
  */

/* Private Functions Prototypes --------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Private_Functions FLASH Private Functions
  * @{
  */
static hal_status_t FLASH_WaitForEndOfOperation(hal_flash_handle_t *hflash, uint32_t timeout_msec);

#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) || defined (USE_HAL_FLASH_ERASE_BY_ADDR)  \
     || defined (USE_HAL_FLASH_ERASE_PAGE)   || defined (USE_HAL_FLASH_ERASE_BANK)     \
     || defined (USE_HAL_FLASH_MASS_ERASE))  && ((USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U) \
     || (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)  || (USE_HAL_FLASH_ERASE_PAGE       == 1U) \
     || (USE_HAL_FLASH_ERASE_BANK    == 1U)  || (USE_HAL_FLASH_MASS_ERASE       == 1U))
static hal_status_t FLASH_CheckEndOfOperation(const hal_flash_handle_t *hflash);
static void FLASH_HandleErrorIT(hal_flash_handle_t *hflash);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR || USE_HAL_FLASH_ERASE_PAGE
       || USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE */

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
static uint32_t FLASH_UpdateAdaptiveProgrammingMode(const hal_flash_handle_t *hflash);

static hal_status_t FLASH_Program(hal_flash_handle_t *hflash,
                                  uint32_t flash_addr,
                                  const uint32_t *p_data,
                                  uint32_t size_byte,
                                  uint32_t timeout_msec);

static hal_status_t FLASH_Program_IT(hal_flash_handle_t *hflash,
                                     uint32_t flash_addr,
                                     const uint32_t *p_data,
                                     uint32_t size_byte);

static void FLASH_ProgramByBurst(const hal_flash_handle_t *hflash);
static void FLASH_ProgramByQuadWord(const hal_flash_handle_t *hflash);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if (defined (USE_HAL_FLASH_ERASE_BANK)   || defined (USE_HAL_FLASH_MASS_ERASE)) \
     && ((USE_HAL_FLASH_ERASE_BANK == 1U) || (USE_HAL_FLASH_MASS_ERASE == 1U))
static hal_status_t FLASH_EraseBank(hal_flash_handle_t *hflash, uint32_t timeout_msec);
static void FLASH_EraseBank_IT(hal_flash_handle_t *hflash);
#endif /* USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE */

#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
static void FLASH_FillErrorCode(hal_flash_handle_t *hflash, uint32_t flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) || defined (USE_HAL_FLASH_ERASE_BY_ADDR)  \
     || defined (USE_HAL_FLASH_ERASE_PAGE)   || defined (USE_HAL_FLASH_ERASE_BANK)     \
     || defined (USE_HAL_FLASH_MASS_ERASE))  && ((USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U) \
     || (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)  || (USE_HAL_FLASH_ERASE_PAGE       == 1U) \
     || (USE_HAL_FLASH_ERASE_BANK    == 1U)  || (USE_HAL_FLASH_MASS_ERASE       == 1U))
static hal_status_t FLASH_NS_WaitForEndOfOperation(hal_flash_handle_t *hflash, uint32_t timeout_msec);
static hal_status_t FLASH_NS_CheckEndOfOperation(const hal_flash_handle_t *hflash);
static void FLASH_NS_HandleErrorIT(hal_flash_handle_t *hflash);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR || USE_HAL_FLASH_ERASE_PAGE
       || USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE */

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
static hal_status_t FLASH_NS_Program(hal_flash_handle_t *hflash,
                                     uint32_t flash_addr,
                                     const uint32_t *p_data,
                                     uint32_t size_byte,
                                     uint32_t timeout_msec);

static hal_status_t FLASH_NS_Program_IT(hal_flash_handle_t *hflash,
                                        uint32_t flash_addr,
                                        const uint32_t *p_data,
                                        uint32_t size_byte);

static void FLASH_NS_ProgramByBurst(const hal_flash_handle_t *hflash);
static void FLASH_NS_ProgramByQuadWord(const hal_flash_handle_t *hflash);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if (defined (USE_HAL_FLASH_ERASE_BANK)   || defined (USE_HAL_FLASH_MASS_ERASE)) \
     && ((USE_HAL_FLASH_ERASE_BANK == 1U) || (USE_HAL_FLASH_MASS_ERASE == 1U))
static hal_status_t FLASH_NS_EraseBank(hal_flash_handle_t *hflash, uint32_t timeout_msec);
static void FLASH_NS_EraseBank_IT(hal_flash_handle_t *hflash);
#endif /* USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE */

#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
static void FLASH_NS_FillErrorCode(hal_flash_handle_t *hflash, uint32_t flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */
#endif /* __ARM_FEATURE_CMSE */

/**
  * @}
  */

/* Exported Functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup FLASH_Exported_Functions
  * @{
  */

/** @addtogroup FLASH_Exported_Functions_Group1
  * @{
  * This subsection provides a set of functions to initialize and de-initialize the Flash peripheral:

  * - Call HAL_FLASH_Init() to initialize the Flash handle and associate a physical instance.
      (Optionally, the Flash clock is enabled inside the function)

  * - Call HAL_FLASH_DeInit() to de-initialize the Flash instance, When called, the API wait for end of ongoing process
      and put the Flash state machine in idle state.

  */

/**
  * @brief  Initialize the Flash handle and associate a physical Flash instance.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  instance           Specifies the Flash instance based on \ref hal_flash_t enumeration.
  * @retval HAL_INVALID_PARAM  Invalid parameter when hflash pointer is NULL.
  * @retval HAL_OK             Flash is successfully initialized.
  */
hal_status_t HAL_FLASH_Init(hal_flash_handle_t *hflash, hal_flash_t instance)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hflash == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hflash->instance = instance;

#if defined(USE_HAL_FLASH_CLK_ENABLE_MODEL) && (USE_HAL_FLASH_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_FLASH_EnableClock();
#endif /* USE_HAL_FLASH_CLK_ENABLE_MODEL */

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
  hflash->p_program_cplt_cb       = HAL_FLASH_ProgramCpltCallback;
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */
#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
  hflash->p_erase_by_addr_cplt_cb = HAL_FLASH_EraseByAddrCpltCallback;
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */
#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
  hflash->p_erase_page_cplt_cb    = HAL_FLASH_ErasePageCpltCallback;
#endif /* USE_HAL_FLASH_ERASE_PAGE */
#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
  hflash->p_erase_bank_cplt_cb    = HAL_FLASH_EraseBankCpltCallback;
#endif /* USE_HAL_FLASH_ERASE_BANK */
#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1U)
  hflash->p_mass_erase_cplt_cb    = HAL_FLASH_MassEraseCpltCallback;
#endif /* USE_HAL_FLASH_MASS_ERASE */
  hflash->p_error_cb              = HAL_FLASH_ErrorCallback;
#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1U)
  hflash->p_ecc_error_cb          = HAL_FLASH_ECC_ErrorCallback;
#endif /* USE_HAL_FLASH_ECC */
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */

#if defined(USE_HAL_FLASH_USER_DATA) && (USE_HAL_FLASH_USER_DATA == 1)
  hflash->p_user_data = NULL;
#endif /* USE_HAL_FLASH_USER_DATA */

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
  hflash->programming_mode = HAL_FLASH_PROGRAM_QUADWORD;
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1U)
  hflash->type = HAL_FLASH_ECC_FAIL_NONE;
#endif /* USE_HAL_FLASH_ECC */

  hflash->global_state = HAL_FLASH_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  De-initialize the Flash handle.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_DeInit(hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(hflash->instance));

  (void)FLASH_WaitForEndOfOperation(hflash, FLASH_OPERATION_MAX_TIMEOUT);

  hflash->global_state = HAL_FLASH_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group2
  * @{

  * This subsection provides a set of functions to configure the Flash programming mode:

  * - Call the function HAL_FLASH_SetProgrammingMode() to set the programming mode.
      (After reset the Quad-word programming is selected).

  * - Call the function HAL_FLASH_GetProgrammingMode() to get the programming mode.

  */

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  Set the Flash programming mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  programming_mode  This parameter is one element of \ref hal_flash_program_mode_t enumeration.
  * @retval HAL_OK            Programming mode is successfully configured.
  */
hal_status_t HAL_FLASH_SetProgrammingMode(hal_flash_handle_t *hflash, hal_flash_program_mode_t programming_mode)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_PROGRAM_MODE_TYPE(programming_mode));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  hflash->programming_mode = programming_mode;

  return HAL_OK;
}

/**
  * @brief  Get the Flash programming mode.
  * @param  hflash                    Pointer to a \ref hal_flash_handle_t structure.
  * @retval hal_flash_program_mode_t  Programming mode.
  */
hal_flash_program_mode_t HAL_FLASH_GetProgrammingMode(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  return (hflash->programming_mode);
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group3
  * @{

  * This subsection provides a set of functions to program and erase any Flash main user memory area:

  * - Call HAL_FLASH_ProgramByAddr() to program any Flash memory user area in polling mode using flash address
      according to selected programming mode.

  * - Call HAL_FLASH_ProgramByAddrAdapt() to program any Flash memory user area in polling mode using flash address
      with adaptive programming mode.

  * - Call HAL_FLASH_ProgramByAddr_IT() to program any Flash memory user area in interrupt mode using flash address
      according to selected programming mode.

  * - Call HAL_FLASH_ProgramByAddrAdapt_IT() to program any Flash memory user area in interrupt mode using flash
      address with adaptive programming mode.

  * - Call HAL_FLASH_OTP_ProgramByAddr() to program any Flash memory OTP area in polling mode using flash OTP address
      according to selected programming mode.

  * - Call HAL_FLASH_OTP_ProgramByAddrAdapt() to program any Flash memory OTP area in polling mode using flash OTP
      address with adaptive programming mode.

  * - Call HAL_FLASH_OTP_ProgramByAddr_IT() to program any Flash memory OTP area in interrupt mode using flash OTP
      address according to selected programming mode.

  * - Call HAL_FLASH_OTP_ProgramByAddrAdapt_IT() to program any Flash memory OTP area in interrupt mode using flash
      OTP address with adaptive programming mode.

  * - Call HAL_FLASH_EraseByAddr() to erase by address any Flash memory area in polling mode.

  * - Call HAL_FLASH_EraseByAddr_IT() to erase by address any Flash memory area in interrupt mode.

  * - Call HAL_FLASH_ErasePage() to erase by page any Flash memory area in polling mode.

  * - Call HAL_FLASH_ErasePage_IT() to erase by page any Flash memory area in interrupt mode.

  * - Call HAL_FLASH_EraseBank() to erase by bank any Flash memory area in polling mode.

  * - Call HAL_FLASH_EraseBank_IT() to erase by bank any Flash memory area in interrupt mode.

  * - Call HAL_FLASH_MassErase() to mass erase the entire Flash memory area in polling mode.

  * - Call HAL_FLASH_MassErase_IT() to mass erase the entire Flash memory area in interrupt mode.

  * - Call HAL_FLASH_IRQHandler() to handle any Flash interrupt.

  * - Call HAL_FLASH_ProgramByAddr_IRQHandler() to handle any Flash program by address interrupt.

  * - Call HAL_FLASH_EraseByAddr_IRQHandler() to handle any Flash erase by address interrupt.

  * - Call HAL_FLASH_ErasePage_IRQHandler() to handle any Flash page erase interrupt.

  * - Call HAL_FLASH_EraseBank_IRQHandler() to handle any Flash bank erase interrupt.

  * - Call HAL_FLASH_MassErase_IRQHandler() to handle any Flash mass erase interrupt.

  * - Call HAL_FLASH_ECC_IRQHandler() to handle any Flash ECC single error detection correction interrupt.

  * - Call HAL_FLASH_NMI_IRQHandler() to handle any Flash NMI interrupt.

  * - Call HAL_FLASH_NS_ProgramByAddr() to program any NSecure Flash memory User area from Secure context
      in polling mode using flash address according to selected programming mode.

  * - Call HAL_FLASH_NS_ProgramByAddrAdapt() to program any NSecure Flash memory User area from Secure context
      in polling mode using flash address with adaptive programming mode.

  * - Call HAL_FLASH_NS_ProgramByAddr_IT() to program any NSecure Flash memory User area from Secure context
      in interrupt mode using flash address according to selected programming mode.

  * - Call HAL_FLASH_NS_ProgramByAddrAdapt_IT() to program any Flash memory User area from Secure context
      in interrupt mode using flash address with adaptive programming mode.

  * - Call HAL_FLASH_NS_OTP_ProgramByAddr() to program any Flash memory OTP area from Secure context
      in polling mode using flash OTP address according to selected programming mode.

  * - Call HAL_FLASH_NS_OTP_ProgramByAddrAdapt() to program any Flash memory OTP area from Secure context
      in polling mode using flash OTP address with adaptive programming mode.

  * - Call HAL_FLASH_NS_OTP_ProgramByAddr_IT() to program any Flash memory OTP area from Secure context
      in interrupt mode using flash OTP address according to selected programming mode.

  * - Call HAL_FLASH_NS_OTP_ProgramByAddrAdapt_IT() to program any NSecure Flash memory OTP area from secure context
      in interrupt mode using flash OTP address with adaptive programming mode.

  * - Call HAL_FLASH_NS_EraseByAddr() to erase by address any NSecure Flash memory area from Secure context
      in polling mode.

  * - Call HAL_FLASH_NS_EraseByAddr_IT() to erase by address any NSecure Flash memory area from Secure context
      in interrupt mode.

  * - Call HAL_FLASH_NS_ErasePage() to erase by page any NSecure Flash memory area from Secure context
      in polling mode.

  * - Call HAL_FLASH_NS_ErasePage_IT() to erase by page any NSecure Flash memory area from Secure context
      in interrupt mode.

  * - Call HAL_FLASH_NS_EraseBank() to erase by bank any NSecure Flash memory area from Secure context
      in polling mode.

  * - Call HAL_FLASH_NS_EraseBank_IT() to erase by bank any NSecure Flash memory area from Secure context
      in interrupt mode.

  * - Call HAL_FLASH_NS_MassErase() to mass erase the entire NSecure Flash memory area from Secure context
      in polling mode.

  * - Call HAL_FLASH_NS_MassErase_IT() to mass erase the entire NSecure Flash memory area from Secure context
      in interrupt mode.

  * - Call HAL_FLASH_NS_IRQHandler() to handle any NSecure Flash interrupt from Secure context.

  * - Call HAL_FLASH_NS_ProgramByAddr_IRQHandler() to handle any NSecure Flash program by address interrupt
      from Secure context.

  * - Call HAL_FLASH_NS_EraseByAddr_IRQHandler() to handle any NSecure Flash erase by address interrupt
      from Secure context.

  * - Call HAL_FLASH_NS_ErasePage_IRQHandler() to handle any NSecure Flash page erase interrupt from Secure context.

  * - Call HAL_FLASH_NS_EraseBank_IRQHandler() to handle any NSecure Flash bank erase interrupt from Secure context.

  * - Call HAL_FLASH_NS_MassErase_IRQHandler() to handle any NSecure Flash mass erase interrupt from Secure context.

  */
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  Program any Flash memory User area in polling mode using flash address according to selected
  *         programming mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr         Start address of the programming operation.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @param  timeout_msec       Timeout value for the programming operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT        Returned when internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_ProgramByAddr(hal_flash_handle_t *hflash,
                                     uint32_t flash_addr,
                                     const uint32_t *p_data,
                                     uint32_t size_byte,
                                     uint32_t timeout_msec)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ADDRESS(flash_addr));
  ASSERT_DBG_PARAM(IS_FLASH_SIZE_IN_RANGE(flash_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_DISABLED;

  status = FLASH_Program(hflash, flash_addr, p_data, size_byte, timeout_msec);

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;

  hflash->global_state = HAL_FLASH_STATE_IDLE;

  return status;
}

/**
  * @brief  Program any Flash memory User area in polling mode using flash address with adaptive programming mode.
  *         The adaptive mode allows to optimize Flash programming access versus remaining data size with ignoring
  *         Flash programming mode selected by HAL_FLASH_SetProgrammingMode() API.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr         Start address of the programming operation.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @param  timeout_msec       Timeout value for the programming operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT        Returned when internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_ProgramByAddrAdapt(hal_flash_handle_t *hflash,
                                          uint32_t flash_addr,
                                          const uint32_t *p_data,
                                          uint32_t size_byte,
                                          uint32_t timeout_msec)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ADDRESS(flash_addr));
  ASSERT_DBG_PARAM(IS_FLASH_SIZE_IN_RANGE(flash_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_ENABLED;

  status = FLASH_Program(hflash, flash_addr, p_data, size_byte, timeout_msec);

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;

  hflash->global_state = HAL_FLASH_STATE_IDLE;

  return status;
}

/**
  * @brief  Program any Flash memory User area in interrupt mode using flash address according to selected
  *         programming mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr         Start address of the programming operation.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_ProgramByAddr_IT(hal_flash_handle_t *hflash,
                                        uint32_t flash_addr,
                                        const uint32_t *p_data,
                                        uint32_t size_byte)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ADDRESS(flash_addr));
  ASSERT_DBG_PARAM(IS_FLASH_SIZE_IN_RANGE(flash_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_DISABLED;

  status = FLASH_Program_IT(hflash, flash_addr, p_data, size_byte);

  return status;
}

/**
  * @brief  Program any Flash memory User area in interrupt mode using flash address with adaptive programming mode.
  *         The adaptive mode allows to optimize Flash programming access versus remaining data size with ignoring
  *         Flash programming mode selected by HAL_FLASH_SetProgrammingMode() API.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr         Start address of the programming operation.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_ProgramByAddrAdapt_IT(hal_flash_handle_t *hflash,
                                             uint32_t flash_addr,
                                             const uint32_t *p_data,
                                             uint32_t size_byte)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ADDRESS(flash_addr));
  ASSERT_DBG_PARAM(IS_FLASH_SIZE_IN_RANGE(flash_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_ENABLED;

  status = FLASH_Program_IT(hflash, flash_addr, p_data, size_byte);

  return status;
}

#if !defined (__ARM_FEATURE_CMSE) || (__ARM_FEATURE_CMSE < 3U)
/**
  * @brief  Program any Flash memory OTP area in polling mode using flash OTP address according to selected
  *         programming mode.
  * @warning This API must be used only when TrustZone is disabled.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr           OTP address.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @param  timeout_msec       Timeout value for the programming operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT        Returned when internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_OTP_ProgramByAddr(hal_flash_handle_t *hflash,
                                         uint32_t otp_addr,
                                         const uint32_t *p_data,
                                         uint32_t size_byte,
                                         uint32_t timeout_msec)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_DISABLED;

  status = FLASH_Program(hflash, otp_addr, p_data, size_byte, timeout_msec);

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;

  hflash->global_state = HAL_FLASH_STATE_IDLE;

  return status;
}

/**
  * @brief  Program any Flash memory OTP area in polling mode using flash OTP address with adaptive programming mode.
  *         The adaptive mode allows to optimize Flash programming access versus remaining data size with ignoring
  *         Flash programming mode selected by HAL_FLASH_SetProgrammingMode() API.
  * @warning This API must be used only when TrustZone is disabled.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr           OTP address.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @param  timeout_msec       Timeout value for the programming operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT        Returned when internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_OTP_ProgramByAddrAdapt(hal_flash_handle_t *hflash,
                                              uint32_t otp_addr,
                                              const uint32_t *p_data,
                                              uint32_t size_byte,
                                              uint32_t timeout_msec)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_ENABLED;

  status = FLASH_Program(hflash, otp_addr, p_data, size_byte, timeout_msec);

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;

  hflash->global_state = HAL_FLASH_STATE_IDLE;

  return status;
}

/**
  * @brief  Program any Flash memory OTP area in interrupt mode using flash OTP address according to selected
  *         programming mode.
  * @warning This API must be used only when TrustZone is disabled.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr           OTP address.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_OTP_ProgramByAddr_IT(hal_flash_handle_t *hflash,
                                            uint32_t otp_addr,
                                            const uint32_t *p_data,
                                            uint32_t size_byte)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_DISABLED;

  status = FLASH_Program_IT(hflash, otp_addr, p_data, size_byte);

  return status;
}

/**
  * @brief  Program any Flash memory OTP area in interrupt mode using flash OTP address with adaptive programming mode.
  *         The adaptive mode allows to optimize Flash programming access versus remaining data size with ignoring
  *         Flash programming mode selected by HAL_FLASH_SetProgrammingMode() API.
  * @warning This API must be used only when TrustZone is disabled.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr           OTP address.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_OTP_ProgramByAddrAdapt_IT(hal_flash_handle_t *hflash,
                                                 uint32_t otp_addr,
                                                 const uint32_t *p_data,
                                                 uint32_t size_byte)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_ENABLED;

  status = FLASH_Program_IT(hflash, otp_addr, p_data, size_byte);

  return status;
}
#endif /*(__ARM_FEATURE_CMSE) || (__ARM_FEATURE_CMSE < 3U) */
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
/**
  * @brief  Erase any Flash memory User area in polling mode using flash address.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr         Start address of the erase operation.
  * @param  size_byte          Size of the data to be erased (in bytes).
  * @param  timeout_msec       Timeout value for the erasing by address operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT        Returned when internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_EraseByAddr(hal_flash_handle_t *hflash,
                                   uint32_t flash_addr,
                                   uint32_t size_byte,
                                   uint32_t timeout_msec)
{
  hal_status_t status = HAL_OK;
  uint32_t     start_page;
  uint32_t     page_nbr;
  uint32_t     tickstart;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ADDRESS(flash_addr));
  ASSERT_DBG_PARAM(IS_FLASH_SIZE_IN_RANGE(flash_addr, size_byte));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  start_page  = (flash_addr - FLASH_BASE) / FLASH_PAGE_SIZE;
  page_nbr = ((((flash_addr - FLASH_BASE) % FLASH_PAGE_SIZE) + size_byte) / FLASH_PAGE_SIZE);
  page_nbr += (((((flash_addr - FLASH_BASE) % FLASH_PAGE_SIZE) + size_byte) % FLASH_PAGE_SIZE) == 0U) ? 0U : 1U;

  hflash->ongoing_operation = HAL_FLASH_ADDR_ERASE;
  hflash->erase_page        = start_page;
  hflash->erase_bank        = (start_page < (uint32_t)FLASH_PAGE_NB_DEFAULT) ? HAL_FLASH_BANK_1 : HAL_FLASH_BANK_2;
  hflash->count             = (int32_t)page_nbr;
  hflash->size              = size_byte;

  LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

  tickstart = HAL_GetTick();
  while ((status == HAL_OK) && (hflash->count > 0))
  {
    LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash),
                            (uint32_t)hflash->erase_bank * LL_FLASH_PAGE_ERASE_BANK_2, hflash->erase_page);

    hflash->erase_page ++;
    hflash->erase_bank = (hflash->erase_page < (uint32_t)FLASH_PAGE_NB_DEFAULT) ? HAL_FLASH_BANK_1 : HAL_FLASH_BANK_2;
    hflash->count --;

    status = FLASH_WaitForEndOfOperation(hflash, FLASH_ERASE_PAGE_OPERATION_TIMEOUT);

    if (((HAL_GetTick() - tickstart) > timeout_msec) && (status == HAL_OK))
    {
      status = HAL_TIMEOUT;
    }
  }

  LL_FLASH_ClearFlag_EOP(FLASH_GET_INSTANCE(hflash));
  LL_FLASH_DisablePageErase(FLASH_GET_INSTANCE(hflash));

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
  hflash->global_state = HAL_FLASH_STATE_IDLE;

  return status;
}

/**
  * @brief  Erase any Flash memory User area in interrupt mode using flash address.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr         Start address of the erase operation.
  * @param  size_byte          Size of the data to be erased (in bytes).
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_EraseByAddr_IT(hal_flash_handle_t *hflash,
                                      uint32_t flash_addr,
                                      uint32_t size_byte)
{
  uint32_t start_page;
  uint32_t page_nbr;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ADDRESS(flash_addr));
  ASSERT_DBG_PARAM(IS_FLASH_SIZE_IN_RANGE(flash_addr, size_byte));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  start_page  = (flash_addr - FLASH_BASE) / FLASH_PAGE_SIZE;
  page_nbr = ((((flash_addr - FLASH_BASE) % FLASH_PAGE_SIZE) + size_byte) / FLASH_PAGE_SIZE);
  page_nbr += (((((flash_addr - FLASH_BASE) % FLASH_PAGE_SIZE) + size_byte) % FLASH_PAGE_SIZE) == 0U) ? 0U : 1U;

  hflash->ongoing_operation = HAL_FLASH_ADDR_ERASE;
  hflash->erase_page        = start_page;
  hflash->erase_bank        = (start_page < (uint32_t)FLASH_PAGE_NB_DEFAULT) ? HAL_FLASH_BANK_1 : HAL_FLASH_BANK_2;
  hflash->count             = (int32_t)page_nbr;
  hflash->size              = size_byte;

  LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);
  LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
  LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash),
                          (uint32_t)hflash->erase_bank * LL_FLASH_PAGE_ERASE_BANK_2, hflash->erase_page);

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
/**
  * @brief  Erase by page any Flash memory User area in polling mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank               This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page               First page to be erased.
  * @param  page_nbr           Number of page(s) to be erased.
  * @param  timeout_msec       Timeout value for the page erasing operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT        Internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_ErasePage(hal_flash_handle_t *hflash,
                                 hal_flash_bank_t bank,
                                 uint32_t page,
                                 uint32_t page_nbr,
                                 uint32_t timeout_msec)
{
  hal_status_t status = HAL_OK;
  uint32_t     tickstart;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(bank != HAL_FLASH_BANK_ALL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_PAGE_IN_RANGE(page, page_nbr));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PAGE_ERASE;
  hflash->erase_page        = page;
  hflash->erase_bank        = bank;
  hflash->count             = (int32_t)page_nbr;
  hflash->size              = page_nbr;

  LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

  tickstart = HAL_GetTick();
  while ((status == HAL_OK) && (hflash->count > 0))
  {
    LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash),
                            (uint32_t)hflash->erase_bank * LL_FLASH_PAGE_ERASE_BANK_2, hflash->erase_page);

    hflash->erase_page++;
    hflash->count--;

    status = FLASH_WaitForEndOfOperation(hflash, FLASH_ERASE_PAGE_OPERATION_TIMEOUT);

    if (((HAL_GetTick() - tickstart) > timeout_msec) && (status == HAL_OK))
    {
      status = HAL_TIMEOUT;
    }
  }

  LL_FLASH_ClearFlag_EOP(FLASH_GET_INSTANCE(hflash));
  LL_FLASH_DisablePageErase(FLASH_GET_INSTANCE(hflash));

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
  hflash->global_state = HAL_FLASH_STATE_IDLE;

  return status;
}

/**
  * @brief  Erase by page any Flash memory User area in interrupt mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank               This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page               First page to be erased.
  * @param  page_nbr           Number of page(s) to be erased.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_ErasePage_IT(hal_flash_handle_t *hflash,
                                    hal_flash_bank_t bank,
                                    uint32_t page,
                                    uint32_t page_nbr)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(bank != HAL_FLASH_BANK_ALL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_PAGE_IN_RANGE(page, page_nbr));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PAGE_ERASE;
  hflash->erase_page        = page;
  hflash->erase_bank        = bank;
  hflash->count             = (int32_t)page_nbr;
  hflash->size              = page_nbr;

  LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);
  LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
  LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash),
                          (uint32_t)hflash->erase_bank * LL_FLASH_PAGE_ERASE_BANK_2, hflash->erase_page);

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
/**
  * @brief  Erase by bank any Flash memory User area in polling mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank               Bank to be erased.
  * @param  timeout_msec       Timeout value for the bank erasing operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT        Internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_EraseBank(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t timeout_msec)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_BANK_ERASE;
  hflash->erase_bank        = bank;

  return FLASH_EraseBank(hflash, timeout_msec);
}

/**
  * @brief  Erase by bank any Flash memory User area in interrupt mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank               Bank to be erased.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_EraseBank_IT(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_BANK_ERASE;
  hflash->erase_bank        = bank;

  FLASH_EraseBank_IT(hflash);

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_BANK */

#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1U)
/**
  * @brief  Mass erase the entire Flash memory User area in polling mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  timeout_msec       Timeout value for the mass erasing operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT        Internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_MassErase(hal_flash_handle_t *hflash, uint32_t timeout_msec)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_MASS_ERASE;
  hflash->erase_bank        = HAL_FLASH_BANK_ALL;

  return FLASH_EraseBank(hflash, timeout_msec);
}

/**
  * @brief  Mass erase the entire Flash memory User area in interrupt mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_MassErase_IT(hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_MASS_ERASE;
  hflash->erase_bank        = HAL_FLASH_BANK_ALL;

  FLASH_EraseBank_IT(hflash);

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_MASS_ERASE */

/**
  * @brief  Handle the Flash interrupt requests.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_IRQHandler(hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
  HAL_FLASH_ProgramByAddr_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
  HAL_FLASH_EraseByAddr_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
  HAL_FLASH_ErasePage_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
  HAL_FLASH_EraseBank_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_ERASE_BANK */

#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1U)
  HAL_FLASH_MassErase_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_MASS_ERASE */

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1U)
  HAL_FLASH_ECC_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_ECC */

#if (!defined(USE_HAL_FLASH_PROGRAM_BY_ADDR)   || (USE_HAL_FLASH_PROGRAM_BY_ADDR != 1U)) \
     && (!defined(USE_HAL_FLASH_ERASE_BY_ADDR) || (USE_HAL_FLASH_ERASE_BY_ADDR   != 1U)) \
     && (!defined(USE_HAL_FLASH_ERASE_PAGE)    || (USE_HAL_FLASH_ERASE_PAGE      != 1U)) \
     && (!defined(USE_HAL_FLASH_ERASE_BANK)    || (USE_HAL_FLASH_ERASE_BANK      != 1U)) \
     && (!defined(USE_HAL_FLASH_MASS_ERASE)    || (USE_HAL_FLASH_MASS_ERASE      != 1U)) \
     && (!defined(USE_HAL_FLASH_ECC)           || (USE_HAL_FLASH_ECC             != 1U))
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR || USE_HAL_FLASH_ERASE_PAGE
       || USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE || USE_HAL_FLASH_ECC */
}

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  Handle the Flash program by address interrupt request.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_ProgramByAddr_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;
  uint32_t programming_data_width;

  ASSERT_DBG_PARAM(hflash != NULL);

  if (hflash->ongoing_operation == HAL_FLASH_PROGRAM)
  {
    flags = LL_FLASH_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    if ((flags & LL_FLASH_FLAG_EOP) != 0U)
    {
      if (hflash->adaptive_prog != FLASH_ADAPTIVE_PROGRAMMING_DISABLED)
      {
        programming_data_width = hflash->adaptive_prog;
      }
      else
      {
        programming_data_width = (uint32_t)hflash->programming_mode;
      }

      hflash->count -= (int32_t)programming_data_width;

      /* Check if there are still data to program */
      if (hflash->count > 0)
      {
        hflash->prog_data_addr  += programming_data_width;
        hflash->prog_flash_addr += programming_data_width;

        if (hflash->adaptive_prog != FLASH_ADAPTIVE_PROGRAMMING_DISABLED)
        {
          programming_data_width = FLASH_UpdateAdaptiveProgrammingMode(hflash);
          hflash->adaptive_prog = programming_data_width;
        }

        if (programming_data_width >= (uint32_t)HAL_FLASH_PROGRAM_BURST)
        {
          FLASH_ProgramByBurst(hflash);
        }
        else
        {
          FLASH_ProgramByQuadWord(hflash);
        }
      }
      else
      {
        LL_FLASH_DisableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
        LL_FLASH_DisableProgramming(FLASH_GET_INSTANCE(hflash));

        hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
        hflash->global_state = HAL_FLASH_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
        hflash->p_program_cplt_cb(hflash);
#else
        HAL_FLASH_ProgramCpltCallback(hflash);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
      }
    }

    if ((flags & LL_FLASH_FLAG_OPERR) != 0U)
    {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      FLASH_FillErrorCode(hflash, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      FLASH_HandleErrorIT(hflash);
    }
  }
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
/**
  * @brief  Handle the Flash erase by address interrupt request.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_EraseByAddr_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;

  ASSERT_DBG_PARAM(hflash != NULL);

  if (hflash->ongoing_operation == HAL_FLASH_ADDR_ERASE)
  {
    flags = LL_FLASH_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    if ((flags & LL_FLASH_FLAG_EOP) != 0U)
    {
      hflash->count--;

      /* Check if there are still pages to erase */
      if (hflash->count > 0)
      {
        hflash->erase_page++;
        hflash->erase_bank = (hflash->erase_page < (uint32_t)FLASH_PAGE_NB_DEFAULT) ? \
                             HAL_FLASH_BANK_1 : HAL_FLASH_BANK_2;
        LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash), (uint32_t)hflash->erase_bank * LL_FLASH_PAGE_ERASE_BANK_2,
                                hflash->erase_page);
      }
      else
      {
        LL_FLASH_DisableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
        LL_FLASH_DisablePageErase(FLASH_GET_INSTANCE(hflash));

        hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
        hflash->global_state = HAL_FLASH_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
        hflash->p_erase_by_addr_cplt_cb(hflash, hflash->erase_page, (uint32_t)(hflash->count));
#else
        HAL_FLASH_EraseByAddrCpltCallback(hflash, hflash->erase_page, (uint32_t)(hflash->count));
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
      }
    }

    if ((flags & LL_FLASH_FLAG_OPERR) != 0U)
    {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      FLASH_FillErrorCode(hflash, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      FLASH_HandleErrorIT(hflash);
    }
  }
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
/**
  * @brief  Handle the Flash erase by page interrupt request.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_ErasePage_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;

  ASSERT_DBG_PARAM(hflash != NULL);

  if (hflash->ongoing_operation == HAL_FLASH_PAGE_ERASE)
  {
    flags = LL_FLASH_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    if ((flags & LL_FLASH_FLAG_EOP) != 0U)
    {
      hflash->count--;

      /* Check if there are still pages to erase */
      if (hflash->count > 0)
      {
        hflash->erase_page++;
        LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash), (uint32_t)hflash->erase_bank * LL_FLASH_PAGE_ERASE_BANK_2,
                                hflash->erase_page);
      }
      else
      {
        LL_FLASH_DisableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
        LL_FLASH_DisablePageErase(FLASH_GET_INSTANCE(hflash));

        hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
        hflash->global_state = HAL_FLASH_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
        hflash->p_erase_page_cplt_cb(hflash, hflash->erase_bank, hflash->erase_page,
                                     (uint32_t)(hflash->count));
#else
        HAL_FLASH_ErasePageCpltCallback(hflash, hflash->erase_bank, hflash->erase_page,
                                        (uint32_t)(hflash->count));
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
      }
    }

    if ((flags & LL_FLASH_FLAG_OPERR) != 0U)
    {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      FLASH_FillErrorCode(hflash, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      FLASH_HandleErrorIT(hflash);
    }
  }
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
/**
  * @brief  Handle the Flash erase by bank interrupt request.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_EraseBank_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;

  ASSERT_DBG_PARAM(hflash != NULL);

  if (hflash->ongoing_operation == HAL_FLASH_BANK_ERASE)
  {
    flags = LL_FLASH_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    if ((flags & LL_FLASH_FLAG_EOP) != 0U)
    {
      LL_FLASH_DisableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
      LL_FLASH_BANK_DisableMassErase(FLASH_GET_INSTANCE(hflash), FLASH_GET_ERASE_BANK(hflash->erase_bank));

      hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
      hflash->global_state = HAL_FLASH_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
      hflash->p_erase_bank_cplt_cb(hflash, hflash->erase_bank);
#else
      HAL_FLASH_EraseBankCpltCallback(hflash, hflash->erase_bank);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
    }

    if ((flags & LL_FLASH_FLAG_OPERR) != 0U)
    {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      FLASH_FillErrorCode(hflash, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      FLASH_HandleErrorIT(hflash);
    }
  }
}
#endif /* USE_HAL_FLASH_ERASE_BANK */

#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1U)
/**
  * @brief  Handle the Flash mass erase interrupt request.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_MassErase_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;

  ASSERT_DBG_PARAM(hflash != NULL);

  if (hflash->ongoing_operation == HAL_FLASH_MASS_ERASE)
  {
    flags = LL_FLASH_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    if ((flags & LL_FLASH_FLAG_EOP) != 0U)
    {
      LL_FLASH_DisableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
      LL_FLASH_BANK_DisableMassErase(FLASH_GET_INSTANCE(hflash), FLASH_GET_ERASE_BANK(hflash->erase_bank));

      hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
      hflash->global_state = HAL_FLASH_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
      hflash->p_mass_erase_cplt_cb(hflash);
#else
      HAL_FLASH_MassEraseCpltCallback(hflash);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
    }

    if ((flags & LL_FLASH_FLAG_OPERR) != 0U)
    {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      FLASH_FillErrorCode(hflash, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      FLASH_HandleErrorIT(hflash);
    }
  }
}
#endif /* USE_HAL_FLASH_MASS_ERASE */

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1U)
/**
  * @brief  Handle the Flash ECC single error detection correction interrupt request.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_ECC_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;
  uint32_t its;

  ASSERT_DBG_PARAM(hflash != NULL);

  flags = LL_FLASH_ReadFlag_ECCR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ECCC);

  its = LL_FLASH_ReadFlag_ECCR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ECCIE) << 6U;

  if (((flags & its) & LL_FLASH_FLAG_ECCC) != 0U)
  {
    hflash->type = HAL_FLASH_ECC_FAIL_ECCC;

    LL_FLASH_ClearFlag_ECCC(FLASH_GET_INSTANCE(hflash));

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
    hflash->p_ecc_error_cb(hflash);
#else
    HAL_FLASH_ECC_ErrorCallback(hflash);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Handle the Flash NMI interrupt request.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @retval cb_status         Return of ECC error callback status
  */
hal_status_t HAL_FLASH_NMI_IRQHandler(hal_flash_handle_t *hflash)
{
  hal_status_t cb_status = HAL_ERROR;

  ASSERT_DBG_PARAM(hflash != NULL);

  if (LL_FLASH_IsActiveFlag_ECCD(FLASH_GET_INSTANCE(hflash)) != 0U)
  {
    hflash->type = HAL_FLASH_ECC_FAIL_ECCD;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
    if (hflash->p_ecc_error_cb(hflash) == HAL_OK)
#else
    if (HAL_FLASH_ECC_ErrorCallback(hflash) == HAL_OK)
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
    {
      /* In this particular NMI error case we have an exception: we clear the flag not before the
         callback but if the callback returns HAL_OK */
      LL_FLASH_ClearFlag_ECCD(FLASH_GET_INSTANCE(hflash));

      cb_status = HAL_OK;
    }
  }

  return cb_status;
}
#endif /* USE_HAL_FLASH_ECC */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  Program the NSecure Flash memory area at a specified address in polling mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr         Start address of the NSecure Flash memory to be programmed.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @param  timeout_msec       Timeout value for the programming operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT        Returned when internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_ProgramByAddr(hal_flash_handle_t *hflash,
                                        uint32_t flash_addr,
                                        const uint32_t *p_data,
                                        uint32_t size_byte,
                                        uint32_t timeout_msec)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_NS_ADDRESS(flash_addr));
  ASSERT_DBG_PARAM(IS_FLASH_NS_SIZE_IN_RANGE(flash_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_DISABLED;

  status = FLASH_NS_Program(hflash, flash_addr, p_data, size_byte, timeout_msec);

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;

  hflash->global_state = HAL_FLASH_STATE_IDLE;

  return status;
}

/**
  * @brief  Program the NSecure Flash memory area at a specified address using adaptive width in polling mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr         Start address of the NSecure Flash memory to be programmed.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @param  timeout_msec       Timeout value for the programming operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT        Returned when internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_ProgramByAddrAdapt(hal_flash_handle_t *hflash,
                                             uint32_t flash_addr,
                                             const uint32_t *p_data,
                                             uint32_t size_byte,
                                             uint32_t timeout_msec)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_NS_ADDRESS(flash_addr));
  ASSERT_DBG_PARAM(IS_FLASH_NS_SIZE_IN_RANGE(flash_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_ENABLED;

  status = FLASH_NS_Program(hflash, flash_addr, p_data, size_byte, timeout_msec);

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;

  hflash->global_state = HAL_FLASH_STATE_IDLE;

  return status;
}

/**
  * @brief  Program the NSecure Flash memory area at a specified address in interrupt mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr         Start address of the NSecure programming operation.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_ProgramByAddr_IT(hal_flash_handle_t *hflash,
                                           uint32_t flash_addr,
                                           const uint32_t *p_data,
                                           uint32_t size_byte)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_NS_ADDRESS(flash_addr));
  ASSERT_DBG_PARAM(IS_FLASH_NS_SIZE_IN_RANGE(flash_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_DISABLED;

  status = FLASH_NS_Program_IT(hflash, flash_addr, p_data, size_byte);

  return status;
}

/**
  * @brief  Program the NSecure Flash memory area at a specified address using adaptive width in interrupt mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr         Start address of the NSecure programming operation.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_ProgramByAddrAdapt_IT(hal_flash_handle_t *hflash,
                                                uint32_t flash_addr,
                                                const uint32_t *p_data,
                                                uint32_t size_byte)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_NS_ADDRESS(flash_addr));
  ASSERT_DBG_PARAM(IS_FLASH_NS_SIZE_IN_RANGE(flash_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_ENABLED;

  status = FLASH_NS_Program_IT(hflash, flash_addr, p_data, size_byte);

  return status;
}

/**
  * @brief  Program the OTP area at a specified address in polling mode.
  * @warning This API must be used only through NSecure world when TrustZone is enabled.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr           OTP address.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @param  timeout_msec       Timeout value for the programming operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked or when TrustZone is disabled.
  * @retval HAL_TIMEOUT        Returned when internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_OTP_ProgramByAddr(hal_flash_handle_t *hflash,
                                            uint32_t otp_addr,
                                            const uint32_t *p_data,
                                            uint32_t size_byte,
                                            uint32_t timeout_msec)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_DISABLED;

  status = FLASH_NS_Program(hflash, otp_addr, p_data, size_byte, timeout_msec);

  return status;
}

/**
  * @brief  Program the OTP area at a specified address using adaptive width in polling mode.
  * @warning This API must be used only through NSecure world when TrustZone is enabled.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr           OTP address.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @param  timeout_msec       Timeout value for the programming operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked or when TrustZone is disabled.
  * @retval HAL_TIMEOUT        Returned when internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_OTP_ProgramByAddrAdapt(hal_flash_handle_t *hflash,
                                                 uint32_t otp_addr,
                                                 const uint32_t *p_data,
                                                 uint32_t size_byte,
                                                 uint32_t timeout_msec)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_ENABLED;

  status = FLASH_NS_Program(hflash, otp_addr, p_data, size_byte, timeout_msec);

  return status;
}

/**
  * @brief  Program the OTP area at a specified address in interrupt mode.
  * @warning This API must be used only through NSecure access when TrustZone is enabled.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr           OTP address.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked or when TrustZone is disabled.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_OTP_ProgramByAddr_IT(hal_flash_handle_t *hflash,
                                               uint32_t otp_addr,
                                               const uint32_t *p_data,
                                               uint32_t size_byte)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_DISABLED;

  status = FLASH_NS_Program_IT(hflash, otp_addr, p_data, size_byte);

  return status;
}

/**
  * @brief  Program the OTP area at a specified address using adaptive width in interrupt mode.
  * @warning This API must be used only through NSecure access when TrustZone is enabled.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr           OTP address.
  * @param  p_data             Pointer to the data to be programmed.
  * @param  size_byte          Size of the data to be programmed (in bytes).
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked or when TrustZone is disabled.
  * @retval HAL_OK             Returned when the programming operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_OTP_ProgramByAddrAdapt_IT(hal_flash_handle_t *hflash,
                                                    uint32_t otp_addr,
                                                    const uint32_t *p_data,
                                                    uint32_t size_byte)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM(size_byte >= (uint32_t)hflash->programming_mode);
  ASSERT_DBG_PARAM((size_byte % (uint32_t)hflash->programming_mode) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PROGRAM;

  hflash->adaptive_prog = FLASH_ADAPTIVE_PROGRAMMING_ENABLED;

  status = FLASH_NS_Program_IT(hflash, otp_addr, p_data, size_byte);

  return status;
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
/**
  * @brief  Erase the Flash memory area at a specified address in polling mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr         Start address of the erase operation.
  * @param  size_byte          Size of the data to be erased (in bytes).
  * @param  timeout_msec       Timeout value for the erasing by address operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT        Internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_EraseByAddr(hal_flash_handle_t *hflash,
                                      uint32_t flash_addr,
                                      uint32_t size_byte,
                                      uint32_t timeout_msec)
{
  hal_status_t status = HAL_OK;
  uint32_t     start_page;
  uint32_t     page_nbr;
  uint32_t     tickstart;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_NS_ADDRESS(flash_addr));
  ASSERT_DBG_PARAM(IS_FLASH_NS_SIZE_IN_RANGE(flash_addr, size_byte));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  start_page  = (flash_addr - FLASH_BASE_NS) / FLASH_PAGE_SIZE;
  page_nbr = ((((flash_addr - FLASH_BASE_NS) % FLASH_PAGE_SIZE) + size_byte) / FLASH_PAGE_SIZE);
  page_nbr += (((((flash_addr - FLASH_BASE_NS) % FLASH_PAGE_SIZE) + size_byte) % FLASH_PAGE_SIZE) == 0U) ? 0U : 1U;

  hflash->ongoing_operation = HAL_FLASH_ADDR_ERASE;
  hflash->erase_page        = start_page;
  hflash->erase_bank        = (start_page < (uint32_t)FLASH_PAGE_NB_DEFAULT) ? HAL_FLASH_BANK_1 : HAL_FLASH_BANK_2;
  hflash->count             = (int32_t)page_nbr;
  hflash->size              = size_byte;

  LL_FLASH_NS_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

  tickstart = HAL_GetTick();
  while ((status == HAL_OK) && (hflash->count > 0))
  {
    LL_FLASH_NS_StartErasePage(FLASH_GET_INSTANCE(hflash),
                               (uint32_t)hflash->erase_bank * LL_FLASH_PAGE_ERASE_BANK_2, hflash->erase_page);

    hflash->erase_page ++;
    hflash->erase_bank = (hflash->erase_page < (uint32_t)FLASH_PAGE_NB_DEFAULT) ? HAL_FLASH_BANK_1 : HAL_FLASH_BANK_2;
    hflash->count --;

    status = FLASH_NS_WaitForEndOfOperation(hflash, FLASH_ERASE_PAGE_OPERATION_TIMEOUT);

    if (((HAL_GetTick() - tickstart) > timeout_msec) && (status == HAL_OK))
    {
      status = HAL_TIMEOUT;
    }
  }

  LL_FLASH_NS_ClearFlag_EOP(FLASH_GET_INSTANCE(hflash));
  LL_FLASH_NS_DisablePageErase(FLASH_GET_INSTANCE(hflash));

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
  hflash->global_state = HAL_FLASH_STATE_IDLE;

  return status;
}

/**
  * @brief  Erase the Flash memory area at a specified address in interrupt mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr         Start address of the erase operation.
  * @param  size_byte          Size of the data to be erased (in bytes).
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_EraseByAddr_IT(hal_flash_handle_t *hflash,
                                         uint32_t flash_addr,
                                         uint32_t size_byte)
{
  uint32_t start_page;
  uint32_t page_nbr;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_NS_ADDRESS(flash_addr));
  ASSERT_DBG_PARAM(IS_FLASH_NS_SIZE_IN_RANGE(flash_addr, size_byte));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  start_page  = (flash_addr - FLASH_BASE_NS) / FLASH_PAGE_SIZE;
  page_nbr = ((((flash_addr - FLASH_BASE_NS) % FLASH_PAGE_SIZE) + size_byte) / FLASH_PAGE_SIZE);
  page_nbr += (((((flash_addr - FLASH_BASE_NS) % FLASH_PAGE_SIZE) + size_byte) % FLASH_PAGE_SIZE) == 0U) ? 0U : 1U;

  hflash->ongoing_operation = HAL_FLASH_ADDR_ERASE;
  hflash->erase_page        = start_page;
  hflash->erase_bank        = (start_page < (uint32_t)FLASH_PAGE_NB_DEFAULT) ? HAL_FLASH_BANK_1 : HAL_FLASH_BANK_2;
  hflash->count             = (int32_t)page_nbr;
  hflash->size              = size_byte;

  LL_FLASH_NS_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);
  LL_FLASH_NS_EnableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
  LL_FLASH_NS_StartErasePage(FLASH_GET_INSTANCE(hflash),
                             (uint32_t)hflash->erase_bank * LL_FLASH_PAGE_ERASE_BANK_2, hflash->erase_page);

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
/**
  * @brief  Erase by page the NSecure Flash memory area in polling mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank               This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page               First page to be erased.
  * @param  page_nbr           Number of page(s) to be erased.
  * @param  timeout_msec       Timeout value for the page(s) erase operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT        Internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_ErasePage(hal_flash_handle_t *hflash,
                                    hal_flash_bank_t bank,
                                    uint32_t page,
                                    uint32_t page_nbr,
                                    uint32_t timeout_msec)
{
  hal_status_t status = HAL_OK;
  uint32_t     tickstart;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(bank != HAL_FLASH_BANK_ALL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_PAGE_IN_RANGE(page, page_nbr));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PAGE_ERASE;
  hflash->erase_page        = page;
  hflash->erase_bank        = bank;
  hflash->count             = (int32_t)page_nbr;
  hflash->size              = page_nbr;

  LL_FLASH_NS_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

  tickstart = HAL_GetTick();
  while ((status == HAL_OK) && (hflash->count > 0))
  {
    LL_FLASH_NS_StartErasePage(FLASH_GET_INSTANCE(hflash),
                               (uint32_t)hflash->erase_bank * LL_FLASH_PAGE_ERASE_BANK_2, hflash->erase_page);

    hflash->erase_page ++;
    hflash->count --;

    status = FLASH_NS_WaitForEndOfOperation(hflash, FLASH_ERASE_PAGE_OPERATION_TIMEOUT);

    if (((HAL_GetTick() - tickstart) > timeout_msec) && (status == HAL_OK))
    {
      status = HAL_TIMEOUT;
    }
  }

  LL_FLASH_NS_ClearFlag_EOP(FLASH_GET_INSTANCE(hflash));
  LL_FLASH_NS_DisablePageErase(FLASH_GET_INSTANCE(hflash));

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
  hflash->global_state = HAL_FLASH_STATE_IDLE;

  return status;
}

/**
  * @brief  Erase by page the NSecure Flash memory area in interrupt mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank               This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page               First page to be erased.
  * @param  page_nbr           Number of pages to be erased.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_ErasePage_IT(hal_flash_handle_t *hflash,
                                       hal_flash_bank_t bank,
                                       uint32_t page,
                                       uint32_t page_nbr)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(bank != HAL_FLASH_BANK_ALL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_PAGE_IN_RANGE(page, page_nbr));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_PAGE_ERASE;
  hflash->erase_page        = page;
  hflash->erase_bank        = bank;
  hflash->count             = (int32_t)page_nbr;
  hflash->size              = page_nbr;

  LL_FLASH_NS_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);
  LL_FLASH_NS_EnableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
  LL_FLASH_NS_StartErasePage(FLASH_GET_INSTANCE(hflash),
                             (uint32_t)hflash->erase_bank * LL_FLASH_PAGE_ERASE_BANK_2, hflash->erase_page);

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
/**
  * @brief  Erase by bank the NSecure Flash memory area in polling mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank               Bank to be erased.
  * @param  timeout_msec       Timeout value for the bank erasing operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT        Internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_EraseBank(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t timeout_msec)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_BANK_ERASE;
  hflash->erase_bank        = bank;

  return FLASH_NS_EraseBank(hflash, timeout_msec);
}

/**
  * @brief  Erase by bank the NSecure Flash memory area in interrupt mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank               Bank to be erased.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter selected.
  * @retval HAL_ERROR          Returned when the control registers access locked.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_EraseBank_IT(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_BANK_ERASE;
  hflash->erase_bank        = bank;

  FLASH_NS_EraseBank_IT(hflash);

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_BANK */

#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1U)
/**
  * @brief  Mass erase the entire NSecure Flash memory in polling mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  timeout_msec       Timeout value for the mass erasing operation.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT        Internal processing exceeded the timeout.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_MassErase(hal_flash_handle_t *hflash, uint32_t timeout_msec)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_MASS_ERASE;
  hflash->erase_bank        = HAL_FLASH_BANK_ALL;

  return FLASH_NS_EraseBank(hflash, timeout_msec);
}

/**
  * @brief  Mass erase the entire NSecure Flash memory in interrupt mode.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR          Returned when the control registers access is locked.
  * @retval HAL_OK             Returned when the erasing operation is completed successfully.
  */
hal_status_t HAL_FLASH_NS_MassErase_IT(hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  if (FLASH_NS_CheckEndOfOperation(hflash) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, global_state, HAL_FLASH_STATE_IDLE, HAL_FLASH_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation = HAL_FLASH_MASS_ERASE;
  hflash->erase_bank        = HAL_FLASH_BANK_ALL;

  FLASH_NS_EraseBank_IT(hflash);

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_MASS_ERASE */

/**
  * @brief  Handle the NSecure Flash interrupt requests.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_NS_IRQHandler(hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
  HAL_FLASH_NS_ProgramByAddr_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
  HAL_FLASH_NS_EraseByAddr_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
  HAL_FLASH_NS_ErasePage_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
  HAL_FLASH_NS_EraseBank_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_ERASE_BANK */

#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1U)
  HAL_FLASH_NS_MassErase_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_MASS_ERASE */

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1U)
  HAL_FLASH_ECC_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_ECC */

#if (!defined(USE_HAL_FLASH_PROGRAM_BY_ADDR)   || (USE_HAL_FLASH_PROGRAM_BY_ADDR != 1U)) \
     && (!defined(USE_HAL_FLASH_ERASE_BY_ADDR) || (USE_HAL_FLASH_ERASE_BY_ADDR   != 1U)) \
     && (!defined(USE_HAL_FLASH_ERASE_PAGE)    || (USE_HAL_FLASH_ERASE_PAGE      != 1U)) \
     && (!defined(USE_HAL_FLASH_ERASE_BANK)    || (USE_HAL_FLASH_ERASE_BANK      != 1U)) \
     && (!defined(USE_HAL_FLASH_MASS_ERASE)    || (USE_HAL_FLASH_MASS_ERASE      != 1U)) \
     && (!defined(USE_HAL_FLASH_ECC)           || (USE_HAL_FLASH_ECC             != 1U))
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR || USE_HAL_FLASH_ERASE_PAGE
      ||  USE_HAL_FLASH_ERASE_BANK ||  USE_HAL_FLASH_MASS_ERASE ||  USE_HAL_FLASH_ECC */
}

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  Handle the NSecure Flash standard and adaptive program by address interrupt request.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_NS_ProgramByAddr_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;
  uint32_t programming_data_width;

  ASSERT_DBG_PARAM(hflash != NULL);

  if (hflash->ongoing_operation == HAL_FLASH_PROGRAM)
  {
    flags = LL_FLASH_NS_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    LL_FLASH_NS_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    if ((flags & LL_FLASH_FLAG_EOP) != 0U)
    {
      if (hflash->adaptive_prog != FLASH_ADAPTIVE_PROGRAMMING_DISABLED)
      {
        programming_data_width = hflash->adaptive_prog;
      }
      else
      {
        programming_data_width = (uint32_t)hflash->programming_mode;
      }

      hflash->count -= (int32_t)programming_data_width;

      /* Check if there are still data to program */
      if (hflash->count > 0)
      {
        hflash->prog_data_addr  += programming_data_width;
        hflash->prog_flash_addr += programming_data_width;

        if (hflash->adaptive_prog != FLASH_ADAPTIVE_PROGRAMMING_DISABLED)
        {
          programming_data_width = FLASH_UpdateAdaptiveProgrammingMode(hflash);
          hflash->adaptive_prog = programming_data_width;
        }

        if (programming_data_width >= (uint32_t)HAL_FLASH_PROGRAM_BURST)
        {
          FLASH_NS_ProgramByBurst(hflash);
        }
        else
        {
          FLASH_NS_ProgramByQuadWord(hflash);
        }
      }
      else
      {
        LL_FLASH_NS_DisableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
        LL_FLASH_NS_DisableProgramming(FLASH_GET_INSTANCE(hflash));

        hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
        hflash->global_state = HAL_FLASH_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
        hflash->p_program_cplt_cb(hflash);
#else
        HAL_FLASH_ProgramCpltCallback(hflash);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
      }
    }

    if ((flags & LL_FLASH_FLAG_OPERR) != 0U)
    {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      FLASH_NS_FillErrorCode(hflash, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      FLASH_NS_HandleErrorIT(hflash);
    }
  }
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
/**
  * @brief  Handle the NSecure Flash erase by address interrupt request.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_NS_EraseByAddr_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;

  ASSERT_DBG_PARAM(hflash != NULL);

  if (hflash->ongoing_operation == HAL_FLASH_ADDR_ERASE)
  {
    flags = LL_FLASH_NS_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    LL_FLASH_NS_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    if ((flags & LL_FLASH_FLAG_EOP) != 0U)
    {
      hflash->count--;

      /* Check if there are still pages to erase */
      if (hflash->count > 0)
      {
        hflash->erase_page++;
        hflash->erase_bank = (hflash->erase_page < (uint32_t)FLASH_PAGE_NB_DEFAULT) ? \
                             HAL_FLASH_BANK_1 : HAL_FLASH_BANK_2;
        LL_FLASH_NS_StartErasePage(FLASH_GET_INSTANCE(hflash),
                                   (uint32_t)hflash->erase_bank * LL_FLASH_PAGE_ERASE_BANK_2, hflash->erase_page);
      }
      else
      {
        LL_FLASH_NS_DisableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
        LL_FLASH_NS_DisablePageErase(FLASH_GET_INSTANCE(hflash));

        hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
        hflash->global_state = HAL_FLASH_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
        hflash->p_erase_by_addr_cplt_cb(hflash, hflash->erase_page, (uint32_t)(hflash->count));
#else
        HAL_FLASH_EraseByAddrCpltCallback(hflash, hflash->erase_page, (uint32_t)(hflash->count));
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
      }
    }

    if ((flags & LL_FLASH_FLAG_OPERR) != 0U)
    {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      FLASH_NS_FillErrorCode(hflash, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      FLASH_NS_HandleErrorIT(hflash);
    }
  }
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
/**
  * @brief  Handle the NSecure Flash erase by page interrupt request.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_NS_ErasePage_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;

  ASSERT_DBG_PARAM(hflash != NULL);

  if (hflash->ongoing_operation == HAL_FLASH_PAGE_ERASE)
  {
    flags = LL_FLASH_NS_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    LL_FLASH_NS_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    if ((flags & LL_FLASH_FLAG_EOP) != 0U)
    {
      hflash->count--;

      /* Check if there are still pages to erase */
      if (hflash->count > 0)
      {
        hflash->erase_page++;
        LL_FLASH_NS_StartErasePage(FLASH_GET_INSTANCE(hflash),
                                   (uint32_t)hflash->erase_bank * LL_FLASH_PAGE_ERASE_BANK_2, hflash->erase_page);
      }
      else
      {
        LL_FLASH_NS_DisableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
        LL_FLASH_NS_DisablePageErase(FLASH_GET_INSTANCE(hflash));

        hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
        hflash->global_state = HAL_FLASH_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
        hflash->p_erase_page_cplt_cb(hflash, hflash->erase_bank, hflash->erase_page,
                                     (uint32_t)(hflash->count));
#else
        HAL_FLASH_ErasePageCpltCallback(hflash, hflash->erase_bank, hflash->erase_page,
                                        (uint32_t)(hflash->count));
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
      }
    }

    if ((flags & LL_FLASH_FLAG_OPERR) != 0U)
    {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      FLASH_NS_FillErrorCode(hflash, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      FLASH_NS_HandleErrorIT(hflash);
    }
  }
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
/**
  * @brief  Handle the NSecure Flash erase by bank interrupt request.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_NS_EraseBank_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;

  ASSERT_DBG_PARAM(hflash != NULL);

  if (hflash->ongoing_operation == HAL_FLASH_BANK_ERASE)
  {
    flags = LL_FLASH_NS_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    LL_FLASH_NS_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    if ((flags & LL_FLASH_FLAG_EOP) != 0U)
    {
      LL_FLASH_NS_DisableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
      LL_FLASH_NS_BANK_DisableMassErase(FLASH_GET_INSTANCE(hflash), LL_FLASH_MASS_ERASE_BANK_ALL);

      hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
      hflash->global_state = HAL_FLASH_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
      hflash->p_erase_bank_cplt_cb(hflash, hflash->erase_bank);
#else
      HAL_FLASH_EraseBankCpltCallback(hflash, hflash->erase_bank);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
    }

    if ((flags & LL_FLASH_FLAG_OPERR) != 0U)
    {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      FLASH_NS_FillErrorCode(hflash, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      FLASH_NS_HandleErrorIT(hflash);
    }
  }
}
#endif /* USE_HAL_FLASH_ERASE_BANK */

#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1U)
/**
  * @brief  Handle the NSecure Flash mass erase interrupt request.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_NS_MassErase_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;

  ASSERT_DBG_PARAM(hflash != NULL);

  if (hflash->ongoing_operation == HAL_FLASH_MASS_ERASE)
  {
    flags = LL_FLASH_NS_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    LL_FLASH_NS_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

    if ((flags & LL_FLASH_FLAG_EOP) != 0U)
    {
      LL_FLASH_NS_DisableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
      LL_FLASH_NS_BANK_DisableMassErase(FLASH_GET_INSTANCE(hflash), LL_FLASH_MASS_ERASE_BANK_ALL);

      hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
      hflash->global_state = HAL_FLASH_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
      hflash->p_mass_erase_cplt_cb(hflash);
#else
      HAL_FLASH_MassEraseCpltCallback(hflash);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
    }

    if ((flags & LL_FLASH_FLAG_OPERR) != 0U)
    {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      FLASH_NS_FillErrorCode(hflash, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      FLASH_NS_HandleErrorIT(hflash);
    }
  }
}
#endif /* USE_HAL_FLASH_MASS_ERASE */
#endif /* __ARM_FEATURE_CMSE */

/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group4
  * @{
  *
  * This subsection provides a set of functions allowing to register the Flash callbacks:

  * - Call HAL_FLASH_ProgramCpltCallback() to be redefined within user application for the program complete callback.

  * - Call HAL_FLASH_EraseByAddrCpltCallback() to be redefined within user application for the erase by address
      complete callback.

  * - Call HAL_FLASH_ErasePageCpltCallback() to be redefined within user application for the erase by page complete
      callback.

  * - Call HAL_FLASH_EraseBankCpltCallback() to be redefined within user application for the bank erase complete
      callback.

  * - Call HAL_FLASH_MassEraseCpltCallback() to be redefined within user application for the mass erase complete
      callback.

  * - Call HAL_FLASH_ErrorCallback() to be redefined within user application for the error callback.

  * - Call HAL_FLASH_ECC_ErrorCallback() to be redefined within user application for the ECC error callback.

  * - Call HAL_FLASH_RegisterProgramCpltCallback() to register the Flash program by address complete callback.

  * - Call HAL_FLASH_RegisterEraseByAddrCpltCallback() to register the Flash erase by address complete callback.

  * - Call HAL_FLASH_RegisterErasePageCpltCallback() to register the Flash erase by page complete callback.

  * - Call HAL_FLASH_RegisterEraseBankCpltCallback() to register the Flash erase by bank complete callback.

  * - Call HAL_FLASH_RegisterMassEraseCpltCallback() to register the Flash mass erase complete callback.

  * - Call HAL_FLASH_RegisterErrorCallback() to register the Flash error callback.

  * - Call HAL_FLASH_RegisterECCErrorCallback() to register the Flash ECC error callback.

  */

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  Flash program by address complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
__WEAK void HAL_FLASH_ProgramCpltCallback(hal_flash_handle_t *hflash)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);

  /*! <b>WARNING:</b> When the HAL_FLASH_ProgramCpltCallback() callback is needed, it must be implemented within
                      user application for the program complete callback. */
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
/**
  * @brief  Flash erase by address complete callback.
  * @param  hflash      Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr  Erased address.
  * @param  size_byte   Erased size in byte.
  */
__WEAK void HAL_FLASH_EraseByAddrCpltCallback(hal_flash_handle_t *hflash, uint32_t flash_addr, uint32_t size_byte)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(flash_addr);
  STM32_UNUSED(size_byte);

  /*! <b>WARNING:</b> When the HAL_FLASH_EraseByAddrCpltCallback() callback is needed, it must be implemented within
                      user application for the erase by address complete callback. */
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
/**
  * @brief  Flash erase by page complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page              Index of the erased page(s).
  * @param  page_nbr          Number of the erased page(s).
  */
__WEAK void HAL_FLASH_ErasePageCpltCallback(hal_flash_handle_t *hflash,
                                            hal_flash_bank_t bank,
                                            uint32_t page,
                                            uint32_t page_nbr)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);
  STM32_UNUSED(page);
  STM32_UNUSED(page_nbr);

  /*! <b>WARNING:</b> When the HAL_FLASH_ErasePageCpltCallback() callback is needed, it must be implemented within
                      user application for the page erase complete callback. */
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
/**
  * @brief  Flash erase by bank complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              Pointer to a \ref hal_flash_bank_t structure.
  */
__WEAK void HAL_FLASH_EraseBankCpltCallback(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  /*! <b>WARNING:</b> When the HAL_FLASH_EraseBankCpltCallback() callback is needed, it must be implemented within
                      user application for the bank erase complete callback. */
}
#endif /* USE_HAL_FLASH_ERASE_BANK */

#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1U)
/**
  * @brief  Flash mass erase complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
__WEAK void HAL_FLASH_MassEraseCpltCallback(hal_flash_handle_t *hflash)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);

  /*! <b>WARNING:</b> When the HAL_FLASH_MassEraseCpltCallback() callback is needed, it must be implemented within
                      user application for the mass erase complete callback. */
}
#endif /* USE_HAL_FLASH_MASS_ERASE */

/**
  * @brief  Flash error callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
__WEAK void HAL_FLASH_ErrorCallback(hal_flash_handle_t *hflash)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);

  /*! <b>WARNING:</b> When the HAL_FLASH_ErrorCallback() callback is needed, it must be implemented within
                      user application for the error callback. */
}

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1U)
/**
  * @brief  Flash ECC error callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @retval HAL_ERROR         Returned when an ECC error occurred.
  */
__WEAK hal_status_t HAL_FLASH_ECC_ErrorCallback(hal_flash_handle_t *hflash)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);

  /*! <b>WARNING:</b> When the HAL_FLASH_ECC_ErrorCallback() callback is needed, it must be implemented within
                      user application for the ECC error callback. */

  return HAL_ERROR;
}
#endif /* USE_HAL_FLASH_ECC */

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  Register the Flash program by address complete callback.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback           Specifies the program complete callback.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_OK             Returned when the registration of the callback is completed successfully.
  */
hal_status_t HAL_FLASH_RegisterProgramCpltCallback(hal_flash_handle_t *hflash,
                                                   hal_flash_program_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Register the Flash program by address complete callback */
  hflash->p_program_cplt_cb = callback;

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
/**
  * @brief  Register the Flash erase by address complete callback.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback           Specifies the erase by address complete callback.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_OK             Returned when the registration of the callback is completed successfully.
  */
hal_status_t HAL_FLASH_RegisterEraseByAddrCpltCallback(hal_flash_handle_t *hflash,
                                                       hal_flash_erase_by_addr_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Register the Flash erase by address complete callback */
  hflash->p_erase_by_addr_cplt_cb = callback;

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
/**
  * @brief  Register the Flash erase by page complete callback.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback           Specifies the erase by page complete callback.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is selected.
  * @retval HAL_OK             Returned when the registration of the callback is completed successfully.
  */
hal_status_t HAL_FLASH_RegisterErasePageCpltCallback(hal_flash_handle_t *hflash,
                                                     hal_flash_erase_page_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Register the Flash erase by page complete callback */
  hflash->p_erase_page_cplt_cb = callback;

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
/**
  * @brief  Register the Flash erase by bank complete callback.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback           Specifies the bank erase complete callback.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is provided.
  * @retval HAL_OK             Returned when the registration of the callback is successful.
  */
hal_status_t HAL_FLASH_RegisterEraseBankCpltCallback(hal_flash_handle_t *hflash,
                                                     hal_flash_erase_bank_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Register the Flash erase by bank complete callback */
  hflash->p_erase_bank_cplt_cb = callback;

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_BANK */

#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1U)
/**
  * @brief  Register the Flash mass erase complete callback.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback           Specifies the mass erase complete callback.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is provided.
  * @retval HAL_OK             Returned when the registration of the callback is successful.
  */
hal_status_t HAL_FLASH_RegisterMassEraseCpltCallback(hal_flash_handle_t *hflash,
                                                     hal_flash_mass_erase_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Register the Flash mass erase complete callback */
  hflash->p_mass_erase_cplt_cb = callback;

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_MASS_ERASE */

/**
  * @brief  Register the Flash error callback.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback           Specifies the error callback.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is provided.
  * @retval HAL_OK             Returned when the registration of the callback is successful.
  */
hal_status_t HAL_FLASH_RegisterErrorCallback(hal_flash_handle_t *hflash,
                                             hal_flash_error_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Register the Flash error callback  */
  hflash->p_error_cb = callback;

  return HAL_OK;
}

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1U)
/**
  * @brief  Register the Flash ECC error callback.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback           Specifies the ECC error callback.
  * @retval HAL_INVALID_PARAM  Returned when an invalid input parameter is provided.
  * @retval HAL_OK             Returned when the registration of the callback is successful.
  */
hal_status_t HAL_FLASH_RegisterECCErrorCallback(hal_flash_handle_t *hflash,
                                                hal_flash_ecc_error_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Register the Flash ECC error callback  */
  hflash->p_ecc_error_cb = callback;

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ECC */
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group5
  * @{

  * This subsection provides functions to get Flash general data information and status:

  * - Call HAL_FLASH_GetOperation() to get the last Flash ongoing operation.

  * - Call HAL_FLASH_GetProgramOperationInfo() to get the last program operation info.

  * - Call HAL_FLASH_GetEraseByAddrOperationInfo() to get the last erase by address operation info.

  * - Call HAL_FLASH_GetErasePageOperationInfo() to get the last erase by page operation info.

  * - Call HAL_FLASH_GetEraseBankOperationInfo() to get the last bank erase operation info.

  * - Call HAL_FLASH_GetInterruptedByResetOperationInfo() to get the Flash interrupted operation info.

  * - Call HAL_FLASH_GetInfo() to get the Flash memory organization information.

  * - Call HAL_FLASH_ECC_GetFailInfo() to get the Flash ECC error information.

  * - Call HAL_FLASH_GetSizeByte() to get the total Flash size in bytes.

  * - Call HAL_FLASH_GetBankNbr() to get the total Flash number of banks.

  * - Call HAL_FLASH_GetBankSizeByte() to get the total Flash size per bank.

  * - Call HAL_FLASH_GetUserFlashSizeByte() to get the User Flash size in bytes of any given bank.

  * - Call HAL_FLASH_GetUserFlashPageNbr() to get the User Flash number of pages per bank.

  * - Call HAL_FLASH_GetUserFlashPageSizeByte() to get the User Flash size of any given page.

  * - Call HAL_FLASH_GetUserFlashAddrOffset() to get the User Flash offset address of any given page.

  * - Call HAL_FLASH_GetState() to get the Flash current state.

  * - Call HAL_FLASH_GetLastErrorCodes() to get the Flash last error codes.

  * - Call HAL_FLASH_SetUserData() to set user data in the Flash handle.

  * - Call HAL_FLASH_GetUserData() to set user data from the Flash handle.

  */

/**
  * @brief  Get the last Flash operation.
  * @param  hflash                 Pointer to a \ref hal_flash_handle_t structure.
  * @retval hal_flash_operation_t  The last operation performed.
  */
hal_flash_operation_t HAL_FLASH_GetOperation(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  return (hflash->ongoing_operation);
}

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  Get the last programming operation information.
  * @param  hflash                Pointer to a \ref hal_flash_handle_t structure.
  * @param  prog_data_addr        Address of the data to be programmed.
  * @param  prog_flash_addr       Address in the Flash where the data is programmed
  * @param  programmed_data_byte  Size in bytes of the programmed data.
  */
void HAL_FLASH_GetProgramOperationInfo(const hal_flash_handle_t *hflash,
                                       uint32_t *prog_flash_addr,
                                       uint32_t *prog_data_addr,
                                       uint32_t *programmed_data_byte)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(prog_flash_addr != NULL);
  ASSERT_DBG_PARAM(prog_data_addr != NULL);
  ASSERT_DBG_PARAM(programmed_data_byte != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  *prog_flash_addr      = hflash->prog_flash_addr;
  *prog_data_addr       = hflash->prog_data_addr;
  *programmed_data_byte = hflash->size - (uint32_t)hflash->count;
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
/**
  * @brief  Get the last address erase operation information.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Address of the first page erased.
  * @param  erased_size_byte  Size in bytes of the erased page.
  */
void HAL_FLASH_GetEraseByAddrOperationInfo(const hal_flash_handle_t *hflash,
                                           uint32_t *flash_addr,
                                           uint32_t *erased_size_byte)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(flash_addr != NULL);
  ASSERT_DBG_PARAM(erased_size_byte != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  *flash_addr       = (hflash->erase_page * FLASH_PAGE_SIZE) + FLASH_BASE;
  *erased_size_byte = hflash->size - ((uint32_t)hflash->count * FLASH_PAGE_SIZE);
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
/**
  * @brief  Get the last page erase operation information.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              Erased bank.
  * @param  page              Index of the first page erased.
  * @param  erased_page_nbr   Number of page(s) erased.
  */
void HAL_FLASH_GetErasePageOperationInfo(const hal_flash_handle_t *hflash,
                                         hal_flash_bank_t *bank,
                                         uint32_t *page,
                                         uint32_t *erased_page_nbr)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(bank != NULL);
  ASSERT_DBG_PARAM(page != NULL);
  ASSERT_DBG_PARAM(erased_page_nbr != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  *bank            = hflash->erase_bank;
  *page            = hflash->erase_page;
  *erased_page_nbr = hflash->size - (uint32_t)hflash->count;
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
/**
  * @brief  Get the last bank erase operation information.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @retval hal_flash_bank_t  Index of the erased bank.
  */
hal_flash_bank_t HAL_FLASH_GetEraseBankOperationInfo(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  return (hflash->erase_bank);
}
#endif /* USE_HAL_FLASH_ERASE_BANK */

/**
  * @brief  Get the interrupted Flash operation information.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  p_info            Pointer to a \ref hal_flash_interrupted_by_reset_operation_info_t structure.
  */
void HAL_FLASH_GetInterruptedByResetOperationInfo(const hal_flash_handle_t *hflash,
                                                  hal_flash_interrupted_by_reset_operation_info_t *p_info)
{
  uint32_t int_by_rst_op_info;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_info != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);

  int_by_rst_op_info = LL_FLASH_ReadFlag_OPSR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_OP_ALL);

  p_info->operation = (hal_flash_interrupted_operation_t)((uint32_t)(int_by_rst_op_info & LL_FLASH_FLAG_CODE_OP));

  if (p_info->operation != HAL_FLASH_INTERRUPTED_NO_OPERATION)
  {
    p_info->addr = (FLASH_SYSTEM_BASE_ADDR + (int_by_rst_op_info & LL_FLASH_FLAG_ADDR_OP));

    if ((int_by_rst_op_info & LL_FLASH_FLAG_SYSF_OP) == 0U)
    {
      p_info->addr = (FLASH_BASE + (int_by_rst_op_info & LL_FLASH_FLAG_ADDR_OP));

      if ((int_by_rst_op_info & FLASH_OPSR_BK_OP) != 0U)
      {
        p_info->addr += FLASH_BANK_SIZE_DEFAULT;
      }
    }
  }
}

/**
  * @brief  Get the Flash general information (size, number and size of banks, number and size of pages).
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  p_info            Pointer to a \ref hal_flash_info_t structure.
  */
void HAL_FLASH_GetInfo(const hal_flash_handle_t *hflash, hal_flash_info_t *p_info)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_info != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  p_info->flash_size_byte = FLASH_SIZE_DEFAULT;
  p_info->bank_nbr        = FLASH_BANK_NB_DEFAULT;

  for (uint32_t bank = 0; bank < FLASH_BANK_NB_DEFAULT; bank++)
  {
    p_info->bank[bank].area_nbr       = 1U;
    p_info->bank[bank].bank_size_byte = FLASH_BANK_SIZE_DEFAULT;

    /* USER Flash area */
    p_info->bank[bank].user_flash.base_addr      = FLASH_BASE + (bank * FLASH_BANK_SIZE_DEFAULT);
    p_info->bank[bank].user_flash.area_size_byte = FLASH_BANK_SIZE_DEFAULT;
    p_info->bank[bank].user_flash.page_nbr       = FLASH_PAGE_NB_DEFAULT;
  }
  STM32_UNUSED(hflash);
}

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1U)
/**
  * @brief  Get the Flash ECC fail information.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  p_info            Pointer to a \ref hal_flash_ecc_fail_info_t structure.
  */
void HAL_FLASH_ECC_GetFailInfo(hal_flash_handle_t *hflash, hal_flash_ecc_fail_info_t *p_info)
{
  uint32_t ecc_fail_info;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_info != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  if (hflash->type == HAL_FLASH_ECC_FAIL_NONE)
  {
    hflash->type = (hal_flash_ecc_fail_type_t)((uint32_t)(LL_FLASH_ReadFlag_ECCR(FLASH_GET_INSTANCE(hflash), \
                                                                                 (LL_FLASH_FLAG_ECCC | \
                                                                                  LL_FLASH_FLAG_ECCD))));
  }

  if (hflash->type != HAL_FLASH_ECC_FAIL_NONE)
  {
    p_info->type  = hflash->type;
    ecc_fail_info = LL_FLASH_ReadFlag_ECCR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ECC_ALL);

    p_info->addr = (FLASH_SYSTEM_BASE_ADDR + (ecc_fail_info & LL_FLASH_FLAG_ADDR_ECC));

    if ((ecc_fail_info & LL_FLASH_FLAG_SYSF_ECC) == 0U)
    {
      p_info->addr = (FLASH_BASE + (ecc_fail_info & LL_FLASH_FLAG_ADDR_ECC));

      if ((ecc_fail_info & LL_FLASH_FLAG_BK_ECC) != 0U)
      {
        p_info->addr += FLASH_BANK_SIZE_DEFAULT;
      }
    }
  }
}
#endif /* USE_HAL_FLASH_ECC */

/**
  * @brief  Get the total Flash size (in bytes).
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @retval uint32_t          Total Flash size (in bytes).
  */
uint32_t HAL_FLASH_GetSizeByte(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  STM32_UNUSED(hflash);

  return FLASH_SIZE_DEFAULT;
}

/**
  * @brief  Get the total Flash number of banks.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @retval uint32_t          Total Flash number of banks.
  */
uint8_t HAL_FLASH_GetBankNbr(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  STM32_UNUSED(hflash);

  return (uint8_t) FLASH_BANK_NB_DEFAULT;
}

/**
  * @brief  Get the total Flash size per bank (in bytes).
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              Selected bank.
  * @retval uint32_t          Total Flash size per bank (in bytes).
  */
uint32_t HAL_FLASH_GetBankSizeByte(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  return FLASH_BANK_SIZE_DEFAULT;
}

/**
  * @brief  Get the User Flash size of the specified bank (in bytes).
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              Selected bank.
  * @retval uint32_t          User Flash size of the specified bank (in bytes).
  */
uint32_t HAL_FLASH_GetUserFlashSizeByte(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  return FLASH_BANK_SIZE;
}

/**
  * @brief  Get the User Flash number of pages per bank.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              Selected bank.
  * @retval uint32_t          User Flash number of pages per bank.
  */
uint16_t HAL_FLASH_GetUserFlashPageNbr(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  return (uint16_t)FLASH_PAGE_NB;
}

/**
  * @brief  Get the User Flash size of the specified page (in bytes).
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              Selected bank.
  * @param  page              Selected page.
  * @retval uint32_t          User Flash size of the specified page (in bytes).
  */
uint32_t HAL_FLASH_GetUserFlashPageSizeByte(const hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t page)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(page < (uint32_t)FLASH_PAGE_NB_DEFAULT);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);
  STM32_UNUSED(page);

  return FLASH_PAGE_SIZE;
}

/**
  * @brief  Get the User Flash offset address of the specified page.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              Selected bank.
  * @param  page              Selected page within the specified bank.
  * @retval uint32_t          Offset address of the specified page.
  */
uint32_t HAL_FLASH_GetUserFlashAddrOffset(const hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t page)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(page < (uint32_t)FLASH_PAGE_NB_DEFAULT);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE | (uint32_t)HAL_FLASH_STATE_ACTIVE);

  STM32_UNUSED(hflash);

  return ((uint32_t)bank * FLASH_BANK_SIZE) + (page * FLASH_PAGE_SIZE);
}

/**
  * @brief  Get the current Flash global state.
  * @param  hflash             Pointer to a \ref hal_flash_handle_t structure.
  * @retval hal_flash_state_t  Current global state of the Flash.
  */
hal_flash_state_t HAL_FLASH_GetState(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  return (hflash->global_state);
}

#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
/**
  * @brief  Get the current Flash last error codes.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @retval uint32_t          Flash last error codes.
  */
uint32_t HAL_FLASH_GetLastErrorCodes(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  return (hflash->last_error_codes);
}
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

#if defined (USE_HAL_FLASH_USER_DATA) && (USE_HAL_FLASH_USER_DATA == 1)
/**
  * @brief  Store the User data pointer within the Flash handle.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  p_user_data       Pointer to the user data.
  */
void HAL_FLASH_SetUserData(hal_flash_handle_t *hflash, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  hflash->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the User data pointer from the Flash handle.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @retval void*             Pointer to the user data.
  */
const void *HAL_FLASH_GetUserData(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  return (hflash->p_user_data);
}
#endif /* USE_HAL_FLASH_USER_DATA */

/**
  * @}
  */

/** @addtogroup FLASH_Private_Functions
  * @{
  * This subsection provides a set of functions intrinsically called to manage various Flash operations:

  * - FLASH_WaitForEndOfOperation() is called to wait for any ongoing Flash operation to be completed.

  * - FLASH_CheckEndOfOperation() is called to check for any ongoing Flash operation if completed.

  * - FLASH_HandleErrorIT() is called to handle any Flash error interrupt.

  * - FLASH_UpdateAdaptiveProgrammingMode() is called to automatically adjust the programming size
      for a any program by address operation regardless of the programming data size given by the user.

  * - FLASH_Program() is called to program a quad-word or burst programming depending on the programming mode
      configuration in polling mode.

  * - FLASH_Program_IT() is called to program a quad-word or burst programming depending on the programming mode
      configuration in interrupt mode.

  * - FLASH_ProgramByBurst() is called to perform a burst granularity data size program (8x quad-words).

  * - FLASH_ProgramByQuadWord() is called to perform a quad-word granularity data size program (128 bits).

  * - FLASH_EraseBank() is called to perform an erase by bank operation in polling mode.

  * - FLASH_EraseBank_IT() is called to perform an erase by bank operation in interrupt mode.

  * - FLASH_FillErrorCode() is called to fill the Flash last error codes filed within the handle.

  * - FLASH_NS_CheckEndOfOperation() is called to check for an ongoing NSecure Flash operation if completed.

  * - FLASH_NS_HandleErrorIT() is called to check for any ongoing NSecure Flash operation errors.

  * - FLASH_NS_Program() is called to program a NSecure quad-word or burst programming depending
      on the programming mode configuration in polling mode.

  * - FLASH_NS_Program_IT() is called to program a NSecure quad-word or burst programming depending
      on the programming mode configuration in interrupt mode.

  * - FLASH_NS_ProgramByBurst() is called to perform a NSecure burst granularity data size program
      (8x quad-words).

  * - FLASH_NS_ProgramByQuadWord() is called to perform a NSecure quad-word granularity data size program
      (128 bits).

  * - FLASH_NS_EraseBank() is called to perform a NSecure erase by bank operation in polling mode.

  * - FLASH_NS_EraseBank_IT() is called to perform a NSecure erase by bank operation in interrupt mode.

  * - FLASH_NS_FillErrorCode() is called to fill the NSecure Flash last error codes filed within the handle.

  */

/**
  * @brief  Wait for an ongoing Flash operation to be completed.
  * @param  hflash                  Pointer to a \ref hal_flash_handle_t structure.
  * @param  timeout_msec            Maximum Flash operation timeout.
  * @retval HAL_ERROR               There is an operation in progress.
  * @retval HAL_OK                  No operation is waiting.
  */
static hal_status_t FLASH_WaitForEndOfOperation(hal_flash_handle_t *hflash, uint32_t timeout_msec)
{
  uint32_t tickstart;
  uint32_t flags;
  uint32_t error_flags;

  flags = LL_FLASH_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), (LL_FLASH_FLAG_BSY | LL_FLASH_FLAG_WDW));

  tickstart = HAL_GetTick();
  while (flags != 0U)
  {
    if ((HAL_GetTick() - tickstart) > timeout_msec)
    {
      return HAL_ERROR;
    }

    flags = LL_FLASH_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), (LL_FLASH_FLAG_BSY | LL_FLASH_FLAG_WDW));
  }

  error_flags = LL_FLASH_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ERRORS_ALL);

  if (error_flags != 0U)
  {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    FLASH_FillErrorCode(hflash, error_flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */
    LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ERRORS_ALL);

    return HAL_ERROR;
  }

  return HAL_OK;
}

#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) || defined (USE_HAL_FLASH_ERASE_BY_ADDR)  \
     || defined (USE_HAL_FLASH_ERASE_PAGE)   || defined (USE_HAL_FLASH_ERASE_BANK)     \
     || defined (USE_HAL_FLASH_MASS_ERASE))  && ((USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U) \
     || (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)  || (USE_HAL_FLASH_ERASE_PAGE       == 1U) \
     || (USE_HAL_FLASH_ERASE_BANK    == 1U)  || (USE_HAL_FLASH_MASS_ERASE       == 1U))

/**
  * @brief  Check the Flash last operation if completed.
  * @param  hflash               Pointer to a \ref hal_flash_handle_t structure.
  * @retval HAL_ERROR            Returned when an error occurred.
  * @retval HAL_OK               No operation is waiting.
  */
static hal_status_t FLASH_CheckEndOfOperation(const hal_flash_handle_t *hflash)
{
  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash)) != 0U)
  {
    return HAL_ERROR;
  }

  if (LL_FLASH_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), (LL_FLASH_FLAG_BSY | LL_FLASH_FLAG_WDW)) != 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Handle any Flash error interrupt.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
static void FLASH_HandleErrorIT(hal_flash_handle_t *hflash)
{
  LL_FLASH_DisableAllOperation(FLASH_GET_INSTANCE(hflash));

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
  hflash->global_state = HAL_FLASH_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
  hflash->p_error_cb(hflash);
#else
  HAL_FLASH_ErrorCallback(hflash);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR || USE_HAL_FLASH_ERASE_PAGE
       || USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE */

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  Automatically Adjust the right programming size depending on the given data size by the user.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @retval count             Adapted data size count for each programming iteration.
  */
static uint32_t FLASH_UpdateAdaptiveProgrammingMode(const hal_flash_handle_t *hflash)
{
  uint32_t prog_size;

  /* Flash user data address to be programmed */
  if (((uint32_t)hflash->count < FLASH_ADAPTIVE_PROGRAMMING_BURST) \
      || (((hflash->prog_flash_addr >= FLASH_OTP_BASE) \
           && (hflash->prog_flash_addr <= (FLASH_OTP_BASE + FLASH_OTP_SIZE)))))
  {
    prog_size = FLASH_ADAPTIVE_PROGRAMMING_QUADWORD;
  }
  else
  {
    prog_size = FLASH_ADAPTIVE_PROGRAMMING_BURST;
  }

  return prog_size;
}

/**
  * @brief  Program a quad-word (128-bit) or burst programming (8x quad-words)
  *         at a specified address in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of Flash to be programmed.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @param  timeout_msec      Timeout value for programming operation.
  * @retval HAL_ERROR         Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the programming operation is completed successfully.
  */
static hal_status_t FLASH_Program(hal_flash_handle_t *hflash,
                                  uint32_t flash_addr,
                                  const uint32_t *p_data,
                                  uint32_t size_byte,
                                  uint32_t timeout_msec)
{
  hal_status_t status = HAL_OK;
  uint32_t prog_size;
  uint32_t tickstart;

  hflash->prog_data_addr    = (uint32_t)p_data;
  hflash->prog_flash_addr   = flash_addr;
  hflash->count             = (int32_t)size_byte;
  hflash->size              = size_byte;

  LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

  LL_FLASH_EnableProgramming(FLASH_GET_INSTANCE(hflash));

  tickstart = HAL_GetTick();
  while ((status == HAL_OK) && (hflash->count > 0))
  {
    if (hflash->adaptive_prog)
    {
      prog_size = FLASH_UpdateAdaptiveProgrammingMode(hflash);
    }
    else
    {
      prog_size = (uint32_t)hflash->programming_mode;
    }

    if (prog_size >= (uint32_t)HAL_FLASH_PROGRAM_BURST)
    {
      FLASH_ProgramByBurst(hflash);
    }
    else
    {
      FLASH_ProgramByQuadWord(hflash);
    }

    status = FLASH_WaitForEndOfOperation(hflash, FLASH_GET_PROGRAM_OPERATION_TIMEOUT \
                                         ((hal_flash_program_mode_t)hflash->programming_mode));

    if (((HAL_GetTick() - tickstart) > timeout_msec) && (status == HAL_OK))
    {
      status = HAL_TIMEOUT;
    }

    hflash->count           -= (int32_t)prog_size;
    hflash->prog_data_addr  += prog_size;
    hflash->prog_flash_addr += prog_size;
  }

  LL_FLASH_DisableProgramming(FLASH_GET_INSTANCE(hflash));
  LL_FLASH_ClearFlag_EOP(FLASH_GET_INSTANCE(hflash));

  return status;
}

/**
  * @brief  Program a quad-word (128-bit) or burst programming (8x quad-words)
  *         at a specified address in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Address in Flash memory to be programmed.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @retval HAL_ERROR         Returned when the control registers access is locked.
  * @retval HAL_OK            Operation completed successfully.
  */
static hal_status_t FLASH_Program_IT(hal_flash_handle_t *hflash,
                                     uint32_t flash_addr,
                                     const uint32_t *p_data,
                                     uint32_t size_byte)
{
  hflash->prog_data_addr    = (uint32_t)p_data;
  hflash->prog_flash_addr   = flash_addr;
  hflash->count             = (int32_t)size_byte;
  hflash->size              = size_byte;

  LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);
  LL_FLASH_EnableProgramming(FLASH_GET_INSTANCE(hflash));
  LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);

  if (hflash->adaptive_prog != FLASH_ADAPTIVE_PROGRAMMING_DISABLED)
  {
    hflash->adaptive_prog = FLASH_UpdateAdaptiveProgrammingMode(hflash);
  }
  else
  {
    hflash->adaptive_prog = (uint32_t)hflash->programming_mode;
  }

  if (hflash->adaptive_prog >= (uint32_t)HAL_FLASH_PROGRAM_BURST)
  {
    FLASH_ProgramByBurst(hflash);
  }
  else
  {
    FLASH_ProgramByQuadWord(hflash);
  }

  return HAL_OK;
}

/**
  * @brief  Perform a Burst programming granularity (8x quad-words).
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
static void FLASH_ProgramByBurst(const hal_flash_handle_t *hflash)
{
  uint8_t  increment_index = (uint8_t)(HAL_FLASH_PROGRAM_BURST) / 4U;
  uint32_t *dest_addr      = (uint32_t *)(hflash->prog_flash_addr);
  uint32_t *src_addr       = (uint32_t *)(hflash->prog_data_addr);
  uint32_t primask_bit;

  LL_FLASH_SetConfigProgramming(FLASH_GET_INSTANCE(hflash), LL_FLASH_PROGRAM_BURST_MODE);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    increment_index--;
  } while (increment_index != 0U);

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  Perform a Quad-word programming granularity (128-bit).
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
static void FLASH_ProgramByQuadWord(const hal_flash_handle_t *hflash)
{
  uint8_t  increment_index = (uint8_t)(HAL_FLASH_PROGRAM_QUADWORD) / 4U;
  uint32_t *dest_addr      = (uint32_t *)(hflash->prog_flash_addr);
  uint32_t *src_addr       = (uint32_t *)(hflash->prog_data_addr);
  uint32_t primask_bit;

  LL_FLASH_SetConfigProgramming(FLASH_GET_INSTANCE(hflash), LL_FLASH_PROGRAM_QUADWORD_MODE);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    increment_index--;
  } while (increment_index != 0U);

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if (defined (USE_HAL_FLASH_ERASE_BANK) || defined (USE_HAL_FLASH_MASS_ERASE)) \
     &&((USE_HAL_FLASH_ERASE_BANK == 1U) || (USE_HAL_FLASH_MASS_ERASE == 1U))
/**
  * @brief  Erase by bank the Flash memory area in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  timeout_msec      Timeout value for erase operation.
  * @retval HAL_ERROR         Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the erase operation is completed successfully.
  */
static hal_status_t FLASH_EraseBank(hal_flash_handle_t *hflash, uint32_t timeout_msec)
{
  hal_status_t status;

  LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);
  LL_FLASH_StartEraseBank(FLASH_GET_INSTANCE(hflash), FLASH_GET_ERASE_BANK(hflash->erase_bank));

  status = FLASH_WaitForEndOfOperation(hflash, timeout_msec);

  LL_FLASH_ClearFlag_EOP(FLASH_GET_INSTANCE(hflash));
  LL_FLASH_BANK_DisableMassErase(FLASH_GET_INSTANCE(hflash), FLASH_GET_ERASE_BANK(hflash->erase_bank));

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
  hflash->global_state = HAL_FLASH_STATE_IDLE;

  return status;
}

/**
  * @brief  Erase by bank the Flash memory area in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
static void FLASH_EraseBank_IT(hal_flash_handle_t *hflash)
{
  LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);
  LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
  LL_FLASH_StartEraseBank(FLASH_GET_INSTANCE(hflash), FLASH_GET_ERASE_BANK(hflash->erase_bank));
}

#endif /* USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE */

#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
/**
  * @brief  Fill the last error code within the handle.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flags             Flash Error flags.
  */
static void FLASH_FillErrorCode(hal_flash_handle_t *hflash, uint32_t flags)
{
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
  if ((flags & LL_FLASH_FLAG_PROGERR) != 0U)
  {
    hflash->last_error_codes |= HAL_FLASH_ERROR_PROG;
  }

  if ((flags & LL_FLASH_FLAG_PGAERR) != 0U)
  {
    hflash->last_error_codes |= HAL_FLASH_ERROR_PGA;
  }

  if ((flags & LL_FLASH_FLAG_SIZERR) != 0U)
  {
    hflash->last_error_codes |= HAL_FLASH_ERROR_SIZE;
  }
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) || defined (USE_HAL_FLASH_ERASE_BY_ADDR)  \
     || defined (USE_HAL_FLASH_ERASE_PAGE)   || defined (USE_HAL_FLASH_ERASE_BANK)     \
     || defined (USE_HAL_FLASH_MASS_ERASE))  && ((USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U) \
     || (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)  || (USE_HAL_FLASH_ERASE_PAGE       == 1U) \
     || (USE_HAL_FLASH_ERASE_BANK    == 1U)  || (USE_HAL_FLASH_MASS_ERASE       == 1U))
  if ((flags & LL_FLASH_FLAG_WRPERR) != 0U)
  {
    hflash->last_error_codes |= HAL_FLASH_ERROR_WRP;
  }

  if ((flags & LL_FLASH_FLAG_PGSERR) != 0U)
  {
    hflash->last_error_codes |= HAL_FLASH_ERROR_PGS;
  }
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR || USE_HAL_FLASH_ERASE_PAGE
       || USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE */
}
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) || defined (USE_HAL_FLASH_ERASE_BY_ADDR)  \
     || defined (USE_HAL_FLASH_ERASE_PAGE)   || defined (USE_HAL_FLASH_ERASE_BANK)     \
     || defined (USE_HAL_FLASH_MASS_ERASE))  && ((USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U) \
     || (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)  || (USE_HAL_FLASH_ERASE_PAGE       == 1U) \
     || (USE_HAL_FLASH_ERASE_BANK    == 1U)  || (USE_HAL_FLASH_MASS_ERASE       == 1U))
/**
  * @brief  Wait for an ongoing NSecure Flash operation to be completed.
  * @param  hflash                  Pointer to a \ref hal_flash_handle_t structure.
  * @param  timeout_msec            Maximum Flash operation timeout.
  * @retval HAL_ERROR               There is an operation in progress.
  * @retval HAL_OK                  No operation is waiting.
  */
static hal_status_t FLASH_NS_WaitForEndOfOperation(hal_flash_handle_t *hflash, uint32_t timeout_msec)
{
  uint32_t tickstart;
  uint32_t flags;
  uint32_t error_flags;

  flags = LL_FLASH_NS_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), (LL_FLASH_FLAG_BSY | LL_FLASH_FLAG_WDW));

  tickstart = HAL_GetTick();
  while (flags != 0U)
  {
    if ((HAL_GetTick() - tickstart) > timeout_msec)
    {
      return HAL_ERROR;
    }

    flags = LL_FLASH_NS_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), (LL_FLASH_FLAG_BSY | LL_FLASH_FLAG_WDW));
  }

  error_flags = LL_FLASH_NS_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ERRORS_ALL);

  if (error_flags != 0U)
  {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    FLASH_NS_FillErrorCode(hflash, error_flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */
    LL_FLASH_NS_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ERRORS_ALL);

    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Check the Flash last NSecure operation if completed.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @retval HAL_ERROR         Returned when the control registers access is locked.
  *                           Returned when there is already an ongoing Flash operation.
  * @retval HAL_OK            No current ongoing Flash operation.
  */
static hal_status_t FLASH_NS_CheckEndOfOperation(const hal_flash_handle_t *hflash)
{
  if (LL_FLASH_NS_IsLocked(FLASH_GET_INSTANCE(hflash)) != 0U)
  {
    return HAL_ERROR;
  }

  if (LL_FLASH_NS_ReadFlag_SR(FLASH_GET_INSTANCE(hflash), (LL_FLASH_FLAG_BSY | LL_FLASH_FLAG_WDW)) != 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Handle the Flash NSecure error interrupt.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
static void FLASH_NS_HandleErrorIT(hal_flash_handle_t *hflash)
{
  LL_FLASH_NS_DisableAllOperation(FLASH_GET_INSTANCE(hflash));

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
  hflash->global_state = HAL_FLASH_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
  hflash->p_error_cb(hflash);
#else
  HAL_FLASH_ErrorCallback(hflash);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR || USE_HAL_FLASH_ERASE_PAGE
       || USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE */

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  Program a quad-word (128-bit) or burst programming (8x quad-words)
  *         at a specified NSecure Flash address in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of Flash to be programmed.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @param  timeout_msec      Timeout value for programming operation.
  * @retval HAL_ERROR         Returned when the control registers access is locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the programming operation is completed successfully.
  */
static hal_status_t FLASH_NS_Program(hal_flash_handle_t *hflash,
                                     uint32_t flash_addr,
                                     const uint32_t *p_data,
                                     uint32_t size_byte,
                                     uint32_t timeout_msec)
{
  hal_status_t status = HAL_OK;
  uint32_t prog_size;
  uint32_t tickstart;

  hflash->prog_data_addr    = (uint32_t)p_data;
  hflash->prog_flash_addr   = flash_addr;
  hflash->count             = (int32_t)size_byte;
  hflash->size              = size_byte;

  LL_FLASH_NS_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);

  LL_FLASH_NS_EnableProgramming(FLASH_GET_INSTANCE(hflash));

  tickstart = HAL_GetTick();
  while ((status == HAL_OK) && (hflash->count > 0))
  {
    if (hflash->adaptive_prog)
    {
      prog_size = FLASH_UpdateAdaptiveProgrammingMode(hflash);
    }
    else
    {
      prog_size = (uint32_t)hflash->programming_mode;
    }

    if (prog_size >= (uint32_t)HAL_FLASH_PROGRAM_BURST)
    {
      FLASH_NS_ProgramByBurst(hflash);
    }
    else
    {
      FLASH_NS_ProgramByQuadWord(hflash);
    }

    status = FLASH_NS_WaitForEndOfOperation(hflash, FLASH_GET_PROGRAM_OPERATION_TIMEOUT \
                                            ((hal_flash_program_mode_t)hflash->programming_mode));

    if (((HAL_GetTick() - tickstart) > timeout_msec) && (status == HAL_OK))
    {
      status = HAL_TIMEOUT;
    }

    hflash->count           -= (int32_t)prog_size;
    hflash->prog_data_addr  += prog_size;
    hflash->prog_flash_addr += prog_size;
  }

  LL_FLASH_NS_DisableProgramming(FLASH_GET_INSTANCE(hflash));
  LL_FLASH_NS_ClearFlag_EOP(FLASH_GET_INSTANCE(hflash));

  return status;
}

/**
  * @brief  Program a quad-word (128-bit) or burst programming (8x quad-words)
  *         at a specified NSecure Flash address in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of Flash to be programmed.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @retval HAL_ERROR         Returned when the control registers access is locked.
  * @retval HAL_OK            Returned when the programming operation is completed successfully.
  */
static hal_status_t FLASH_NS_Program_IT(hal_flash_handle_t *hflash,
                                        uint32_t flash_addr,
                                        const uint32_t *p_data,
                                        uint32_t size_byte)
{
  hflash->prog_data_addr    = (uint32_t)p_data;
  hflash->prog_flash_addr   = flash_addr;
  hflash->count             = (int32_t)size_byte;
  hflash->size              = size_byte;

  LL_FLASH_NS_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);
  LL_FLASH_NS_EnableProgramming(FLASH_GET_INSTANCE(hflash));
  LL_FLASH_NS_EnableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);

  if (hflash->adaptive_prog != FLASH_ADAPTIVE_PROGRAMMING_DISABLED)
  {
    hflash->adaptive_prog = FLASH_UpdateAdaptiveProgrammingMode(hflash);
  }
  else
  {
    hflash->adaptive_prog = (uint32_t)hflash->programming_mode;
  }

  if (hflash->adaptive_prog >= (uint32_t)HAL_FLASH_PROGRAM_BURST)
  {
    FLASH_NS_ProgramByBurst(hflash);
  }
  else
  {
    FLASH_NS_ProgramByQuadWord(hflash);
  }

  return HAL_OK;
}

/**
  * @brief  Perform a NSecure Burst programming granularity (8x quad-words).
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
static void FLASH_NS_ProgramByBurst(const hal_flash_handle_t *hflash)
{
  uint8_t  increment_index = (uint8_t)(HAL_FLASH_PROGRAM_BURST) / 4U;
  uint32_t *dest_addr      = (uint32_t *)(hflash->prog_flash_addr);
  uint32_t *src_addr       = (uint32_t *)(hflash->prog_data_addr);
  uint32_t primask_bit;

  LL_FLASH_NS_SetConfigProgramming(FLASH_GET_INSTANCE(hflash), LL_FLASH_PROGRAM_BURST_MODE);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    increment_index--;
  } while (increment_index != 0U);

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  Perform a NSecure Quad-word programming granularity (128-bit).
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
static void FLASH_NS_ProgramByQuadWord(const hal_flash_handle_t *hflash)
{
  uint8_t  increment_index = (uint8_t)(HAL_FLASH_PROGRAM_QUADWORD) / 4U;
  uint32_t *dest_addr      = (uint32_t *)(hflash->prog_flash_addr);
  uint32_t *src_addr       = (uint32_t *)(hflash->prog_data_addr);
  uint32_t primask_bit;

  LL_FLASH_NS_SetConfigProgramming(FLASH_GET_INSTANCE(hflash), LL_FLASH_PROGRAM_QUADWORD_MODE);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    increment_index--;
  } while (increment_index != 0U);

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if (defined (USE_HAL_FLASH_ERASE_BANK)  || defined (USE_HAL_FLASH_MASS_ERASE)) \
    && ((USE_HAL_FLASH_ERASE_BANK == 1U) || (USE_HAL_FLASH_MASS_ERASE == 1U))
/**
  * @brief  Erase by bank the NSecure Flash memory area in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  timeout_msec      Timeout value for erase operation.
  * @retval status            Flash bank erase operation status.
  */
static hal_status_t FLASH_NS_EraseBank(hal_flash_handle_t *hflash, uint32_t timeout_msec)
{
  hal_status_t status;

  LL_FLASH_NS_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);
  LL_FLASH_NS_StartEraseBank(FLASH_GET_INSTANCE(hflash), FLASH_GET_ERASE_BANK(hflash->erase_bank));

  status = FLASH_NS_WaitForEndOfOperation(hflash, timeout_msec);

  LL_FLASH_NS_ClearFlag_EOP(FLASH_GET_INSTANCE(hflash));
  LL_FLASH_NS_BANK_DisableMassErase(FLASH_GET_INSTANCE(hflash), FLASH_GET_ERASE_BANK(hflash->erase_bank));

  hflash->ongoing_operation = HAL_FLASH_NO_OPERATION;
  hflash->global_state = HAL_FLASH_STATE_IDLE;

  return status;
}

/**
  * @brief  Erase by bank the NSecure Flash memory area in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  */
static void FLASH_NS_EraseBank_IT(hal_flash_handle_t *hflash)
{
  LL_FLASH_NS_ClearFlag(FLASH_GET_INSTANCE(hflash), LL_FLASH_FLAG_ALL);
  LL_FLASH_NS_EnableIT(FLASH_GET_INSTANCE(hflash), LL_FLASH_IT_ALL);
  LL_FLASH_NS_StartEraseBank(FLASH_GET_INSTANCE(hflash), FLASH_GET_ERASE_BANK(hflash->erase_bank));
}

#endif /* USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE */

#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
/**
  * @brief  Fill the NSecure last error code within the handle.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flags             NSecure Flash Error flags.
  */
static void FLASH_NS_FillErrorCode(hal_flash_handle_t *hflash, uint32_t flags)
{
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
  if ((flags & LL_FLASH_FLAG_PROGERR) != 0U)
  {
    hflash->last_error_codes |= HAL_FLASH_NS_ERROR_PROG;
  }

  if ((flags & LL_FLASH_FLAG_PGAERR) != 0U)
  {
    hflash->last_error_codes |= HAL_FLASH_NS_ERROR_PGA;
  }

  if ((flags & LL_FLASH_FLAG_SIZERR) != 0U)
  {
    hflash->last_error_codes |= HAL_FLASH_NS_ERROR_SIZE;
  }
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) || defined (USE_HAL_FLASH_ERASE_BY_ADDR)  \
     || defined (USE_HAL_FLASH_ERASE_PAGE)   || defined (USE_HAL_FLASH_ERASE_BANK)     \
     || defined (USE_HAL_FLASH_MASS_ERASE))  && ((USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U) \
     || (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)  || (USE_HAL_FLASH_ERASE_PAGE       == 1U) \
     || (USE_HAL_FLASH_ERASE_BANK    == 1U)  || (USE_HAL_FLASH_MASS_ERASE       == 1U))
  if ((flags & LL_FLASH_FLAG_WRPERR) != 0U)
  {
    hflash->last_error_codes |= HAL_FLASH_NS_ERROR_WRP;
  }

  if ((flags & LL_FLASH_FLAG_PGSERR) != 0U)
  {
    hflash->last_error_codes |= HAL_FLASH_NS_ERROR_PGS;
  }
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR || USE_HAL_FLASH_ERASE_PAGE
      || USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE */
}
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */
#endif /* __ARM_FEATURE_CMSE */

/**
  * @}
  */

#endif /* USE_HAL_FLASH_MODULE */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
