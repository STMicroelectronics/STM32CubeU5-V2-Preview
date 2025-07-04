/**
  **********************************************************************************************************************
  * @file    stm32u5xx_ll_flash.h
  * @brief   Header file of FLASH LL module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2021-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */


/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_LL_FLASH_H
#define STM32U5XX_LL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */
/** @defgroup FLASH_LL FLASH
  * @{
  */

#if defined (FLASH)

/** @defgroup FLASH_LL_Exported_Constants FLASH Exported Constants
  * @{
  */

/** @defgroup FLASH_Interrupt FLASH Interrupt
  * @{
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define LL_FLASH_IT_EOP FLASH_SECCR_EOPIE                       /*!< LL FLASH Secure end of operation interrupt */
#define LL_FLASH_IT_ERR FLASH_SECCR_ERRIE                       /*!< LL FLASH Secure operation error interrupt  */
#define LL_FLASH_IT_ALL (FLASH_SECCR_EOPIE | FLASH_SECCR_ERRIE) /*!< LL FLASH All Secure interrupts             */
#else
#define LL_FLASH_IT_EOP FLASH_NSCR_EOPIE                      /*!< LL FLASH Non-Secure end of operation interrupt */
#define LL_FLASH_IT_ERR FLASH_NSCR_ERRIE                      /*!< LL FLASH Non-Secure operation error interrupt  */
#define LL_FLASH_IT_ALL (FLASH_NSCR_EOPIE | FLASH_NSCR_ERRIE) /*!< LL FLASH All Non-Secure interrupts             */
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/** @defgroup FLASH_Errors FLASH Errors
  * @{
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define LL_FLASH_FLAG_EOP        FLASH_SECSR_EOP      /*!< LL FLASH Secure end of operation            */
#define LL_FLASH_FLAG_OPERR      FLASH_SECSR_OPERR    /*!< LL FLASH Secure operation error             */
#define LL_FLASH_FLAG_PROGERR    FLASH_SECSR_PROGERR  /*!< LL FLASH Secure programming error           */
#define LL_FLASH_FLAG_WRPERR     FLASH_SECSR_WRPERR   /*!< LL FLASH Secure write protection error      */
#define LL_FLASH_FLAG_PGAERR     FLASH_SECSR_PGAERR   /*!< LL FLASH Secure programming alignment error */
#define LL_FLASH_FLAG_SIZERR     FLASH_SECSR_SIZERR   /*!< LL FLASH Secure size error                  */
#define LL_FLASH_FLAG_PGSERR     FLASH_SECSR_PGSERR   /*!< LL FLASH Secure programming sequence error  */
#define LL_FLASH_FLAG_BSY        FLASH_SECSR_BSY      /*!< LL FLASH Secure busy                        */
#define LL_FLASH_FLAG_WDW        FLASH_SECSR_WDW      /*!< LL FLASH Secure wait data to write          */
#define LL_FLASH_FLAG_ERRORS_ALL (FLASH_SECSR_OPERR  | FLASH_SECSR_PROGERR | FLASH_SECSR_WRPERR | \
                                  FLASH_SECSR_PGAERR | FLASH_SECSR_SIZERR  | FLASH_SECSR_PGSERR)
#define LL_FLASH_FLAG_ALL        (FLASH_SECSR_EOP | LL_FLASH_FLAG_ERRORS_ALL)
#else
#define LL_FLASH_FLAG_EOP        FLASH_NSSR_EOP       /*!< LL FLASH Non-Secure end of operation            */
#define LL_FLASH_FLAG_OPERR      FLASH_NSSR_OPERR     /*!< LL FLASH Non-Secure operation error             */
#define LL_FLASH_FLAG_PROGERR    FLASH_NSSR_PROGERR   /*!< LL FLASH Non-Secure programming error           */
#define LL_FLASH_FLAG_WRPERR     FLASH_NSSR_WRPERR    /*!< LL FLASH Non-Secure write protection error      */
#define LL_FLASH_FLAG_PGAERR     FLASH_NSSR_PGAERR    /*!< LL FLASH Non-Secure programming alignment error */
#define LL_FLASH_FLAG_SIZERR     FLASH_NSSR_SIZERR    /*!< LL FLASH Non-Secure size error                  */
#define LL_FLASH_FLAG_PGSERR     FLASH_NSSR_PGSERR    /*!< LL FLASH Non-Secure programming sequence error  */
#define LL_FLASH_FLAG_BSY        FLASH_NSSR_BSY       /*!< LL FLASH Non-Secure busy                        */
#define LL_FLASH_FLAG_WDW        FLASH_NSSR_WDW       /*!< LL FLASH Non-Secure wait data to write          */
#define LL_FLASH_FLAG_ERRORS_ALL (FLASH_NSSR_OPERR  | FLASH_NSSR_PROGERR | FLASH_NSSR_WRPERR | FLASH_NSSR_PGAERR | \
                                  FLASH_NSSR_SIZERR | FLASH_NSSR_PGSERR  | FLASH_NSSR_OPTWERR)
#define LL_FLASH_FLAG_ALL        (FLASH_NSSR_EOP | LL_FLASH_FLAG_ERRORS_ALL)
#endif /* __ARM_FEATURE_CMSE */

#define LL_FLASH_FLAG_OPTWERR    FLASH_NSSR_OPTWERR   /*!< LL FLASH Option bytes write error  */
#define LL_FLASH_FLAG_PD1        FLASH_NSSR_PD1       /*!< LL FLASH Bank 1 in power-down mode */
#define LL_FLASH_FLAG_PD2        FLASH_NSSR_PD2       /*!< LL FLASH Bank 2 in power-down mode */

#define LL_FLASH_FLAG_ECCC       FLASH_ECCR_ECCC      /*!< LL FLASH ECC single error                */
#define LL_FLASH_FLAG_ECCD       FLASH_ECCR_ECCD      /*!< LL FLASH ECC double error                */
#define LL_FLASH_FLAG_ECCIE      FLASH_ECCR_ECCIE     /*!< LL FLASH ECC correction interrupt enable */
#define LL_FLASH_FLAG_BK_ECC     FLASH_ECCR_BK_ECC    /*!< LL FLASH ECC bank fail                   */
#define LL_FLASH_FLAG_SYSF_ECC   FLASH_ECCR_SYSF_ECC  /*!< LL FLASH ECC System fail                 */
#define LL_FLASH_FLAG_ADDR_ECC   FLASH_ECCR_ADDR_ECC  /*!< LL FLASH ECC fail address                */
#define LL_FLASH_FLAG_ECC_ALL    (FLASH_ECCR_ECCC | FLASH_ECCR_ECCD | FLASH_ECCR_ECCIE | FLASH_ECCR_BK_ECC | \
                                  FLASH_ECCR_SYSF_ECC | FLASH_ECCR_ADDR_ECC)

#define LL_FLASH_FLAG_ADDR_OP    FLASH_OPSR_ADDR_OP   /*!< LL FLASH Interrupted operation address         */
#define LL_FLASH_FLAG_BK_OP      FLASH_OPSR_BK_OP     /*!< LL FLASH Interrupted operation bank            */
#define LL_FLASH_FLAG_SYSF_OP    FLASH_OPSR_SYSF_OP   /*!< LL FLASH Interrupted operation in System Flash */
#define LL_FLASH_FLAG_CODE_OP    FLASH_OPSR_CODE_OP   /*!< LL FLASH Interrupted operation code            */
#define LL_FLASH_FLAG_OP_ALL     (LL_FLASH_FLAG_ADDR_OP | LL_FLASH_FLAG_BK_OP | LL_FLASH_FLAG_SYSF_OP | \
                                  LL_FLASH_FLAG_CODE_OP)

/**
  * @}
  */

/** @defgroup FLASH_Latency FLASH Latency
  * @{
  */
#define LL_FLASH_LATENCY_0WS  FLASH_ACR_LATENCY_0WS  /*!< LL FLASH Zero wait state      */
#define LL_FLASH_LATENCY_1WS  FLASH_ACR_LATENCY_1WS  /*!< LL FLASH One wait state       */
#define LL_FLASH_LATENCY_2WS  FLASH_ACR_LATENCY_2WS  /*!< LL FLASH Two wait states      */
#define LL_FLASH_LATENCY_3WS  FLASH_ACR_LATENCY_3WS  /*!< LL FLASH Three wait states    */
#define LL_FLASH_LATENCY_4WS  FLASH_ACR_LATENCY_4WS  /*!< LL FLASH Four wait states     */
#define LL_FLASH_LATENCY_5WS  FLASH_ACR_LATENCY_5WS  /*!< LL FLASH Five wait state      */
#define LL_FLASH_LATENCY_6WS  FLASH_ACR_LATENCY_6WS  /*!< LL FLASH Six wait state       */
#define LL_FLASH_LATENCY_7WS  FLASH_ACR_LATENCY_7WS  /*!< LL FLASH Seven wait states    */
#define LL_FLASH_LATENCY_8WS  FLASH_ACR_LATENCY_8WS  /*!< LL FLASH Eight wait states    */
#define LL_FLASH_LATENCY_9WS  FLASH_ACR_LATENCY_9WS  /*!< LL FLASH Nine wait states     */
#define LL_FLASH_LATENCY_10WS FLASH_ACR_LATENCY_10WS /*!< LL FLASH Ten wait state       */
#define LL_FLASH_LATENCY_11WS FLASH_ACR_LATENCY_11WS /*!< LL FLASH Eleven wait state    */
#define LL_FLASH_LATENCY_12WS FLASH_ACR_LATENCY_12WS /*!< LL FLASH Twelve wait states   */
#define LL_FLASH_LATENCY_13WS FLASH_ACR_LATENCY_13WS /*!< LL FLASH Thirteen wait states */
#define LL_FLASH_LATENCY_14WS FLASH_ACR_LATENCY_14WS /*!< LL FLASH Fourteen wait states */
#define LL_FLASH_LATENCY_15WS FLASH_ACR_LATENCY_15WS /*!< LL FLASH Fifteen wait states  */
/**
  * @}
  */

/** @defgroup FLASH_Power_Down_Run_Bank_Selection FLASH Power Down Run Bank Selection
  * @{
  */
#define LL_FLASH_PWR_DOWN_RUN_BANK_1 FLASH_ACR_PDREQ1 /*!< LL FLASH Power down run bank 1 */
#define LL_FLASH_PWR_DOWN_RUN_BANK_2 FLASH_ACR_PDREQ2 /*!< LL FLASH Power down run bank 2 */
/**
  * @}
  */

/** @defgroup FLASH_Power_Sleep_Mode FLASH Power Sleep Mode
  * @{
  */
#define LL_FLASH_IDLE_SLEEP_MODE     0x00000000U        /*!< LL FLASH in idle mode during sleep mode       */
#define LL_FLASH_PWR_DOWN_SLEEP_MODE FLASH_ACR_SLEEP_PD /*!< LL FLASH in power down mode during sleep mode */
/**
  * @}
  */

/** @defgroup FLASH_Unlock_Keys FLASH Unlock Keys
  * @{
  */
#define LL_FLASH_KEY1 0x45670123U /*!< LL FLASH key1 */
#define LL_FLASH_KEY2 0xCDEF89ABU /*!< LL FLASH key2 */
/**
  * @}
  */

/** @defgroup FLASH_OB_Unlock_Keys FLASH OB Unlock Keys
  * @{
  */
#define LL_FLASH_OB_OPTKEY1 0x08192A3BU /*!< LL FLASH option byte key1 */
#define LL_FLASH_OB_OPTKEY2 0x4C5D6E7FU /*!< LL FLASH option byte key2 */
/**
  * @}
  */

/** @defgroup FLASH_Power_Down_Keys FLASH Power Down Keys
  * @{
  */
#define LL_FLASH_PDKEY1_1 0x04152637U /*!< LL FLASH Bank 1 power down key1 */
#define LL_FLASH_PDKEY1_2 0xFAFBFCFDU /*!< LL FLASH Bank 1 power down key2 */
#define LL_FLASH_PDKEY2_1 0x40516273U /*!< LL FLASH Bank 2 power down key1 */
#define LL_FLASH_PDKEY2_2 0xAFBFCFDFU /*!< LL FLASH Bank 2 power down key2 */
/**
  * @}
  */

/** @defgroup FLASH_Bank_Selection FLASH Bank Selection
  * @{
  */
#define LL_FLASH_BANK_1 0x00U /*!< LL FLASH bank 1 */
#define LL_FLASH_BANK_2 0x04U /*!< LL FLASH bank 2 */
/**
  * @}
  */

/** @defgroup FLASH_OB_Bank_Area_Selection FLASH Option bytes Bank Area Selection
  * @{
  */
#define LL_FLASH_OB_BANK_AREA_A 0x0U /*!< LL FLASH Option bytes Bank Area A */
#define LL_FLASH_OB_BANK_AREA_B 0x1U /*!< LL FLASH Option bytes Bank Area B */
/**
  * @}
  */

/** @defgroup FLASH_Page_Erase_Bank_Selection FLASH Page Erase Bank Selection
  * @{
  */
#define LL_FLASH_PAGE_ERASE_BANK_1 0x00000000U     /*!< LL FLASH Page erase bank 1 */
#define LL_FLASH_PAGE_ERASE_BANK_2 FLASH_NSCR_BKER /*!< LL FLASH Page erase bank 2 */
/**
  * @}
  */

/** @defgroup FLASH_Mass_Erase_Bank_Selection FLASH Mass Erase Bank Selection
  * @{
  */
#define LL_FLASH_MASS_ERASE_BANK_1 FLASH_NSCR_MER1                       /*!< LL FLASH Mass erase bank 1   */
#define LL_FLASH_MASS_ERASE_BANK_2 FLASH_NSCR_MER2                       /*!< LL FLASH Mass erase bank 2   */
#define LL_FLASH_MASS_ERASE_BANK_ALL (FLASH_NSCR_MER1 | FLASH_NSCR_MER2) /*!< LL FLASH Mass erase all bank */
/**
  * @}
  */

/** @defgroup FLASH_Program_Mode_Selection FLASH Program Mode Selection
  * @{
  */
#define LL_FLASH_PROGRAM_QUADWORD_MODE 0x00000000U    /*!< LL FLASH programming by quadword mode */
#define LL_FLASH_PROGRAM_BURST_MODE    FLASH_NSCR_BWR /*!< LL FLASH programming by burst mode    */
/**
  * @}
  */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/** @defgroup FLASH_Security_Inversion FLASH Security Inversion
  * @{
  */
#define LL_FLASH_SEC_NOT_INVERTED 0x00000000U     /*!< LL FLASH Security state not inverted */
#define LL_FLASH_SEC_INVERTED     FLASH_SECCR_INV /*!< LL FLASH Security state inverted     */
/**
  * @}
  */
#endif /* __ARM_FEATURE_CMSE */

/** @defgroup FLASH_Interrupted_Operation_Code FLASH Interrupted Operation Code
  * @{
  */
#define LL_FLASH_INTERRUPTED_NO_OPERATION 0x00000000U /*!< LL FLASH interrupted no operation        */
#define LL_FLASH_INTERRUPTED_SINGLE_WRITE 0x20000000U /*!< LL FLASH interrupted single write        */
#define LL_FLASH_INTERRUPTED_BURST_WRITE  0x40000000U /*!< LL FLASH interrupted burst write         */
#define LL_FLASH_INTERRUPTED_PAGE_ERASE   0x60000000U /*!< LL FLASH interrupted page erase          */
#define LL_FLASH_INTERRUPTED_BANK_ERASE   0x80000000U /*!< LL FLASH interrupted bank erase          */
#define LL_FLASH_INTERRUPTED_MASS_ERASE   0xA0000000U /*!< LL FLASH interrupted mass erase          */
#define LL_FLASH_INTERRUPTED_OB_CHANGE    0xC0000000U /*!< LL FLASH interrupted option bytes change */
/**
  * @}
  */

/** @defgroup FLASH_OB_Read_Protection_Level FLASH OB Read Protection Level
  * @{
  */
#define LL_FLASH_OB_RDP_LEVEL_0   0xAAU /*!< LL FLASH option bytes RDP level 0   */
#define LL_FLASH_OB_RDP_LEVEL_0_5 0x55U /*!< LL FLASH option bytes RDP level 0.5 */
#define LL_FLASH_OB_RDP_LEVEL_1   0xBBU /*!< LL FLASH option bytes RDP level 1   */
#define LL_FLASH_OB_RDP_LEVEL_2   0xCCU /*!< LL FLASH option bytes RDP level 2   */
/**
  * @}
  */

/** @defgroup FLASH_OB_OEM_Selection FLASH Option bytes OEM Selection
  * @{
  */
#define LL_FLASH_OB_OEM_1 0x0U /*!< LL FLASH option bytes OEM 1 */
#define LL_FLASH_OB_OEM_2 0x2U /*!< LL FLASH option bytes OEM 2 */
/**
  * @}
  */

/** @defgroup FLASH_OB_BOR_Level FLASH OB BOR Level
  * @{
  */
#define LL_FLASH_OB_BOR_LEVEL_0 0x000U /*!< LL FLASH Reset level threshold is around 1.7V */
#define LL_FLASH_OB_BOR_LEVEL_1 0x100U /*!< LL FLASH Reset level threshold is around 2.0V */
#define LL_FLASH_OB_BOR_LEVEL_2 0x200U /*!< LL FLASH Reset level threshold is around 2.2V */
#define LL_FLASH_OB_BOR_LEVEL_3 0x300U /*!< LL FLASH Reset level threshold is around 2.5V */
#define LL_FLASH_OB_BOR_LEVEL_4 0x400U /*!< LL FLASH Reset level threshold is around 2.8V */
/**
  * @}
  */

/** @defgroup FLASH_OB_Reset_Generation_Stop_Mode FLASH OB Reset Generation Stop Mode
  * @{
  */
#define LL_FLASH_OB_RST_STOP_MODE    0x00000000U          /*!< LL FLASH option bytes reset in stop mode    */
#define LL_FLASH_OB_NO_RST_STOP_MODE FLASH_OPTR_nRST_STOP /*!< LL FLASH option bytes no reset in stop mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_Reset_Generation_Standby_Mode FLASH OB Reset Generation standby Mode
  * @{
  */
#define LL_FLASH_OB_RST_STDBY_MODE    0x00000000U           /*!< LL FLASH option bytes reset in standby mode    */
#define LL_FLASH_OB_NO_RST_STDBY_MODE FLASH_OPTR_nRST_STDBY /*!< LL FLASH option bytes no reset in standby mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_Reset_Generation_shutdown_Mode FLASH OB Reset Generation shutdown Mode
  * @{
  */
#define LL_FLASH_OB_RST_SHDW_MODE    0x00000000U          /*!< LL FLASH option bytes reset in shutdown mode    */
#define LL_FLASH_OB_NO_RST_SHDW_MODE FLASH_OPTR_nRST_SHDW /*!< LL FLASH option bytes no reset in shutdown mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_Erase_Sram_System_Reset FLASH OB Erase Sram System Reset
  * @{
  */
#define LL_FLASH_OB_ERASED_SRAM_SYS_RST     0x00000000U         /*!< LL FLASH OB erased sram in sys reset */
#define LL_FLASH_OB_NOT_ERASED_SRAM_SYS_RST FLASH_OPTR_SRAM_RST /*!< LL FLASH OB not erased sram in sys reset */
/**
  * @}
  */

/** @defgroup FLASH_OB_IWDG_HW_SW_Selection FLASH OB IWDG HW SW Selection
  * @{
  */
#define LL_FLASH_OB_IWDG_HW 0x00000000U        /*!< LL FLASH OB IWDG Hardware selection */
#define LL_FLASH_OB_IWDG_SW FLASH_OPTR_IWDG_SW /*!< LL FLASH OB IWDG Software selection */
/**
  * @}
  */

/** @defgroup FLASH_OB_WWDG_HW_SW_Selection FLASH OB WWDG HW SW Selection
  * @{
  */
#define LL_FLASH_OB_WWDG_HW 0x00000000U        /*!< LL FLASH OB WWDG Hardware selection */
#define LL_FLASH_OB_WWDG_SW FLASH_OPTR_WWDG_SW /*!< LL FLASH OB WWDG Software selection */
/**
  * @}
  */

/** @defgroup FLASH_OB_Swap_Bank FLASH OB Swap Bank
  * @{
  */
#define LL_FLASH_OB_BANK_NOT_SWAPPED 0x00000000U          /*!< LL FLASH OB Bank not swapped */
#define LL_FLASH_OB_BANK_SWAPPED     FLASH_OPTR_SWAP_BANK /*!< LL FLASH OB Bank swapped     */
/**
  * @}
  */

/** @defgroup FLASH_OB_Single_Dual_Bank FLASH OB Single Dual Bank
  * @{
  */
#define LL_FLASH_OB_SINGLE_BANK 0x00000000U          /*!< LL FLASH OB Single bank */
#define LL_FLASH_OB_DUAL_BANK   FLASH_OPTR_DUALBANK  /*!< LL FLASH OB Dual bank   */
/**
  * @}
  */

/** @defgroup FLASH_OB_Erase_Sram2_System_Reset FLASH OB Erase Sram2 System Reset
  * @{
  */
#define LL_FLASH_OB_ERASED_SRAM2_SYS_RST     0x00000000U          /*!< LL FLASH OB Erased sram2 upon system reset */
#define LL_FLASH_OB_NOT_ERASED_SRAM2_SYS_RST FLASH_OPTR_SRAM2_RST /*!< LL FLASH OB Not erased sram2 upon system reset */
/**
  * @}
  */

/** @defgroup FLASH_OB_Boot0_Selection FLASH OB Boot0 Selection
  * @{
  */
#define LL_FLASH_OB_BOOT0_NBOOTBIT 0x00000000U         /*!< LL FLASH OB Boot0 NBOOT0  */
#define LL_FLASH_OB_BOOT0_BOOTPIN  FLASH_OPTR_nSWBOOT0 /*!< LL FLASH OB Boot0 BOOTPIN */
/**
  * @}
  */

/** @defgroup FLASH_OB_NBOOT0_Option FLASH OB NBOOT0 Option
  * @{
  */
#define LL_FLASH_OB_BOOT0_LOW  0x00000000U       /*!< LL FLASH OB NBOOT0 0 */
#define LL_FLASH_OB_BOOT0_HIGH FLASH_OPTR_nBOOT0 /*!< LL FLASH OB NBOOT0 1 */
/**
  * @}
  */

/** @defgroup FLASH_OB_Address_Selection FLASH Option bytes Address Selection
  * @{
  */
#define LL_FLASH_OB_ADDR_0 0x0U /*!< LL FLASH OB Address 1 */
#define LL_FLASH_OB_ADDR_1 0x1U /*!< LL FLASH OB Address 2 */
/**
  * @}
  */

/** @defgroup FLASH_OB_Bank_Group_Selection FLASH OB Bank Group Selection
  * @{
  */
#define LL_FLASH_BANK_GRP1 0x00U /*!< LL FLASH OB Bank group 1 */
#if defined (SRAM3_BASE)
#define LL_FLASH_BANK_GRP2 0x01U /*!< LL FLASH OB Bank group 2 */
#define LL_FLASH_BANK_GRP3 0x02U /*!< LL FLASH OB Bank group 3 */
#define LL_FLASH_BANK_GRP4 0x03U /*!< LL FLASH OB Bank group 4 */
#endif /* SRAM3_BASE */
#if defined (SRAM5_BASE)
#define LL_FLASH_BANK_GRP5 0x04U /*!< LL FLASH OB Bank group 5 */
#define LL_FLASH_BANK_GRP6 0x05U /*!< LL FLASH OB Bank group 6 */
#define LL_FLASH_BANK_GRP7 0x06U /*!< LL FLASH OB Bank group 7 */
#define LL_FLASH_BANK_GRP8 0x07U /*!< LL FLASH OB Bank group 8 */
#endif /* SRAM5_BASE */
/**
  * @}
  */

/** @defgroup FLASH_OB_Hide_Protection_Access_Bank FLASH OB Hide Protection Access Bank
  * @{
  */
#define LL_FLASH_HDP_ACCESS_BANK_1 FLASH_SECHDPCR_HDP1_ACCDIS /*!< LL FLASH OB HDP access bank 1 */
#define LL_FLASH_HDP_ACCESS_BANK_2 FLASH_SECHDPCR_HDP2_ACCDIS /*!< LL FLASH OB HDP access bank 2 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Macros FLASH Exported Macros
  * @{
  */

/**
  * @brief  Write a value in FLASH register.
  * @param  FLASH instance.
  * @param  reg   Register to be written.
  * @param  value Value to be written in the register.
  */
#define LL_FLASH_WRITE_REG(instance, reg, value) WRITE_REG(instance->reg, (value))

/**
  * @brief  Read a value from FLASH register
  * @param  FLASH instance.
  * @param  reg      Register to be read
  * @retval Register value
  */
#define LL_FLASH_READ_REG(instance, reg) READ_REG(instance->reg)


/**
  * @brief  Read a bits value from FLASH register
  * @param  FLASH instance.
  * @param  reg Register to be read
  * @param  msk Mask to be read
  * @retval Register value
  */
#define LL_FLASH_READ_BIT(instance, reg, msk) READ_REG(instance->reg & msk)

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/

/** @defgroup FLASH_LL_Exported_Functions FLASH Exported Functions
  * @{
  */

/**
  * @brief  Set Flash latency.
  * @rmtoll
  *  ACR           LATENCY           LL_FLASH_SetLatency
  * @param  FLASH instance.
  * @param  latency
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0WS
  *         @arg @ref LL_FLASH_LATENCY_1WS
  *         @arg @ref LL_FLASH_LATENCY_2WS
  *         @arg @ref LL_FLASH_LATENCY_3WS
  *         @arg @ref LL_FLASH_LATENCY_4WS
  *         @arg @ref LL_FLASH_LATENCY_5WS
  *         @arg @ref LL_FLASH_LATENCY_6WS
  *         @arg @ref LL_FLASH_LATENCY_7WS
  *         @arg @ref LL_FLASH_LATENCY_8WS
  *         @arg @ref LL_FLASH_LATENCY_9WS
  *         @arg @ref LL_FLASH_LATENCY_10WS
  *         @arg @ref LL_FLASH_LATENCY_11WS
  *         @arg @ref LL_FLASH_LATENCY_12WS
  *         @arg @ref LL_FLASH_LATENCY_13WS
  *         @arg @ref LL_FLASH_LATENCY_14WS
  *         @arg @ref LL_FLASH_LATENCY_15WS
  */
__STATIC_INLINE void LL_FLASH_SetLatency(FLASH_TypeDef *flashx, uint32_t latency)
{
  MODIFY_REG(flashx->ACR, FLASH_ACR_LATENCY, latency);
}

/**
  * @brief  Get Flash latency.
  * @rmtoll
  * @param  FLASH instance.
  *  ACR           LATENCY           LL_FLASH_GetLatency
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0WS
  *         @arg @ref LL_FLASH_LATENCY_1WS
  *         @arg @ref LL_FLASH_LATENCY_2WS
  *         @arg @ref LL_FLASH_LATENCY_3WS
  *         @arg @ref LL_FLASH_LATENCY_4WS
  *         @arg @ref LL_FLASH_LATENCY_5WS
  *         @arg @ref LL_FLASH_LATENCY_6WS
  *         @arg @ref LL_FLASH_LATENCY_7WS
  *         @arg @ref LL_FLASH_LATENCY_8WS
  *         @arg @ref LL_FLASH_LATENCY_9WS
  *         @arg @ref LL_FLASH_LATENCY_10WS
  *         @arg @ref LL_FLASH_LATENCY_11WS
  *         @arg @ref LL_FLASH_LATENCY_12WS
  *         @arg @ref LL_FLASH_LATENCY_13WS
  *         @arg @ref LL_FLASH_LATENCY_14WS
  *         @arg @ref LL_FLASH_LATENCY_15WS
  */
__STATIC_INLINE uint32_t LL_FLASH_GetLatency(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->ACR, FLASH_ACR_LATENCY));
}

/**
  * @brief  Enable flash prefetch.
  * @rmtoll
  *  ACR           PRFTEN           LL_FLASH_EnablePrefetch
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnablePrefetch(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->ACR, FLASH_ACR_PRFTEN);
}

/**
  * @brief  Disable flash prefetch.
  * @rmtoll
  *  ACR           PRFTEN           LL_FLASH_DisablePrefetch
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisablePrefetch(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->ACR, FLASH_ACR_PRFTEN);
}

/**
  * @brief  Check if the flash prefetch is enabled or disabled.
  * @rmtoll
  *  ACR           PRFTEN           LL_FLASH_IsEnabledPrefetch
  * @param  FLASH instance.
  * @retval State of flash prefetch (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPrefetch(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->ACR, FLASH_ACR_PRFTEN) == (FLASH_ACR_PRFTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable flash low power read mode.
  * @rmtoll
  *  ACR           LPM           LL_FLASH_EnableLowPWRReadMode
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableLowPWRReadMode(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->ACR, FLASH_ACR_LPM);
}

/**
  * @brief  Disable flash low power read mode.
  * @rmtoll
  *  ACR           LPM           LL_FLASH_DisableLowPWRReadMode
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableLowPWRReadMode(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->ACR, FLASH_ACR_LPM);
}

/**
  * @brief  Check if the flash low power read mode is enabled or disabled.
  * @rmtoll
  *  ACR           LPM           LL_FLASH_IsEnabledLowPWRReadMode
  * @param  FLASH instance.
  * @retval State of flash low power read mode (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledLowPWRReadMode(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->ACR, FLASH_ACR_LPM) == (FLASH_ACR_LPM)) ? 1UL : 0UL);
}

/**
  * @brief  Request flash bank power down mode during run mode.
  * @rmtoll ACR        PDREQx (x : 1 to 2)        LL_FLASH_BANK_RequestPWRDownRunMode
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_PWR_DOWN_RUN_BANK_1
  *         @arg @ref LL_FLASH_PWR_DOWN_RUN_BANK_2
  */
__STATIC_INLINE void LL_FLASH_BANK_RequestPWRDownRunMode(FLASH_TypeDef *flashx, uint32_t bank)
{
  SET_BIT(flashx->ACR, bank);
}

/**
  * @brief  Set the flash power mode during sleep mode.
  * @rmtoll
  *  ACR        SLEEP_PD        LL_FLASH_SetPWRDownSleepMode
  * @param  FLASH instance.
  * @param  mode
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_IDLE_SLEEP_MODE
  *         @arg @ref LL_FLASH_PWR_DOWN_SLEEP_MODE
  */
__STATIC_INLINE void LL_FLASH_SetPWRDownSleepMode(FLASH_TypeDef *flashx, uint32_t mode)
{
  MODIFY_REG(flashx->ACR, FLASH_ACR_SLEEP_PD, mode);
}

/**
  * @brief  Get the flash power mode during sleep mode.
  * @rmtoll
  *  ACR        SLEEP_PD        LL_FLASH_GetPWRDownSleepMode
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_IDLE_SLEEP_MODE
  *         @arg @ref LL_FLASH_PWR_DOWN_SLEEP_MODE
  */
__STATIC_INLINE uint32_t LL_FLASH_GetPWRDownSleepMode(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->ACR, FLASH_ACR_SLEEP_PD));
}


/**
  * @brief  Set the flash power down key.
  * @rmtoll PDKEY1R/PDKEY2R           PDKEY1/PDKEY2             LL_FLASH_BANK_SetPWRDownRunModeKey
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  key
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_PDKEY1_1 for LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_PDKEY1_2 for LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_PDKEY2_1 for LL_FLASH_BANK_2
  *         @arg @ref LL_FLASH_PDKEY2_2 for LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_BANK_SetPWRDownRunModeKey(FLASH_TypeDef *flashx, uint32_t bank, uint32_t key)
{
  uint32_t reg_addr = (uint32_t)&flashx->PDKEY1R;
  WRITE_REG(*(__IO uint32_t *)(reg_addr + bank), key);
}

/**
  * @brief  Set the flash unlock key.
  * @rmtoll NSKEYR/SECKEYR           NSKEY/SECKEY           LL_FLASH_SetUnlockKey
  * @param  FLASH instance.
  * @param  key
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_KEY1
  *         @arg @ref LL_FLASH_KEY2
  */
__STATIC_INLINE void LL_FLASH_SetUnlockKey(FLASH_TypeDef *flashx, uint32_t key)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  WRITE_REG(flashx->SECKEYR, key);
#else
  WRITE_REG(flashx->NSKEYR, key);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Set the flash unlock key for the non-secure flash memory.
  * @rmtoll
  *  NSKEYR           NSKEY           LL_FLASH_NS_SetUnlockKey
  * @param  FLASH instance.
  * @param  key
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_KEY1
  *         @arg @ref LL_FLASH_KEY2
  */
__STATIC_INLINE void LL_FLASH_NS_SetUnlockKey(FLASH_TypeDef *flashx, uint32_t key)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  WRITE_REG(FLASH_NS->NSKEYR, key);
}
#endif /* __ARM_FEATURE_CMSE */

/** @defgroup FLASH_LL_EF_FLAG_Management Flag Management
  * @{
  */

/**
  * @brief  Set the flash option bytes unlock key.
  * @rmtoll
  *  OPTKEYR           OPTKEY           LL_FLASH_OB_SetUnlockKey
  * @param  FLASH instance.
  * @param  key
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_OPTKEY1
  *         @arg @ref LL_FLASH_OB_OPTKEY2
  */
__STATIC_INLINE void LL_FLASH_OB_SetUnlockKey(FLASH_TypeDef *flashx, uint32_t key)
{
  WRITE_REG(flashx->OPTKEYR, key);
}

/**
  * @brief  Check if any of the selected flags is active.
  * @rmtoll NSSR/SECSR      EOP/OPERR/PROGERR/WRPERR/PGAERR/SIZERR/PGSERR      LL_FLASH_IsActiveFlag
  * @param  FLASH instance.
  * @param  flag
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_EOP
  *         @arg @ref LL_FLASH_FLAG_OPERR
  *         @arg @ref LL_FLASH_FLAG_PROGERR
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGAERR
  *         @arg @ref LL_FLASH_FLAG_SIZERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_BSY
  *         @arg @ref LL_FLASH_FLAG_WDW
  *         @arg @ref LL_FLASH_FLAG_ALL
  * @retval State of selected flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag(const FLASH_TypeDef *flashx, uint32_t flag)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECSR, flag) != 0U) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSSR, flag) != 0U) ? 1UL : 0UL);
#endif
}

/**
  * @brief  Read the state of selected flash operation flag.
  * @rmtoll NSSR/SECSR      EOP/OPERR/PROGERR/WRPERR/PGAERR/SIZERR/PGSERR/BSY/WDW     LL_FLASH_ReadFlag_SR
  * @param  FLASH instance.
  * @param  flag
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_EOP
  *         @arg @ref LL_FLASH_FLAG_OPERR
  *         @arg @ref LL_FLASH_FLAG_PROGERR
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGAERR
  *         @arg @ref LL_FLASH_FLAG_SIZERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_BSY
  *         @arg @ref LL_FLASH_FLAG_WDW
  *         @arg @ref LL_FLASH_FLAG_ALL
  * @retval State of selected flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_ReadFlag_SR(const FLASH_TypeDef *flashx, uint32_t flag)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return (READ_BIT(flashx->SECSR, flag));
#else
  return (READ_BIT(flashx->NSSR, flag));
#endif /* __ARM_FEATURE_CMSE */
}

/**
  * @brief  Read the state of selected flash ECC operation flag.
  * @rmtoll ECCR      ECCC/ECCD/ECCIE/BK/SYSF/ADDR      LL_FLASH_ReadFlag_ECCR
  * @param  FLASH instance.
  * @param  flag
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_ECCC
  *         @arg @ref LL_FLASH_FLAG_ECCD
  *         @arg @ref LL_FLASH_FLAG_ECCIE
  *         @arg @ref LL_FLASH_FLAG_BK_ECC
  *         @arg @ref LL_FLASH_FLAG_SYSF_ECC
  *         @arg @ref LL_FLASH_FLAG_ADDR_ECC
  *         @arg @ref LL_FLASH_FLAG_ECC_ALL
  * @retval State of selected flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_ReadFlag_ECCR(const FLASH_TypeDef *flashx, uint32_t flag)
{
  return (READ_BIT(flashx->ECCR, flag));
}

/**
  * @brief  Read the state of selected flash operation status flag.
  * @rmtoll OPSR      CODE/SYSF/BK/ADDR      LL_FLASH_ReadFlag_OPSR
  * @param  FLASH instance.
  * @param  flag
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_ADDR_OP
  *         @arg @ref LL_FLASH_FLAG_BK_OP
  *         @arg @ref LL_FLASH_FLAG_SYSF_OP
  *         @arg @ref LL_FLASH_FLAG_CODE_OP
  *         @arg @ref LL_FLASH_FLAG_OP_ALL
  * @retval State of selected flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_ReadFlag_OPSR(const FLASH_TypeDef *flashx, uint32_t flag)
{
  return (READ_BIT(flashx->OPSR, flag));
}

/**
  * @brief  Clear the flash operation flag.
  * @rmtoll NSSR/SECSR      EOP/OPERR/PROGERR/WRPERR/PGAERR/SIZERR/PGSERR      LL_FLASH_ClearFlag
  * @param  FLASH instance.
  * @param  flag
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_EOP
  *         @arg @ref LL_FLASH_FLAG_OPERR
  *         @arg @ref LL_FLASH_FLAG_PROGERR
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGAERR
  *         @arg @ref LL_FLASH_FLAG_SIZERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_ALL
  */
__STATIC_INLINE void LL_FLASH_ClearFlag(FLASH_TypeDef *flashx, uint32_t flag)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECSR, flag);
#else
  SET_BIT(flashx->NSSR, flag);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if any of the selected non-secure flags is active.
  * @rmtoll NSSR       EOP/OPERR/PROGERR/WRPERR/PGAERR/SIZERR/PGSERR      LL_FLASH_NS_IsActiveFlag
  * @param  FLASH instance.
  * @param  flag
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_EOP
  *         @arg @ref LL_FLASH_FLAG_OPERR
  *         @arg @ref LL_FLASH_FLAG_PROGERR
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGAERR
  *         @arg @ref LL_FLASH_FLAG_SIZERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_BSY
  *         @arg @ref LL_FLASH_FLAG_WDW
  *         @arg @ref LL_FLASH_FLAG_ALL
  * @retval State of selected flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag(const FLASH_TypeDef *flashx, uint32_t flag)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return (READ_BIT(FLASH_NS->NSSR, flag) != 0U) ? 1UL : 0UL;
}

/**
  * @brief  Read the state of selected flash operation flag for the non-secure flash memory.
  * @rmtoll NSSR      EOP/OPERR/PROGERR/WRPERR/PGAERR/SIZERR/PGSERR/BSY/WDW      LL_FLASH_NS_ReadFlag
  * @param  FLASH instance.
  * @param  flag
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_EOP
  *         @arg @ref LL_FLASH_FLAG_OPERR
  *         @arg @ref LL_FLASH_FLAG_PROGERR
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGAERR
  *         @arg @ref LL_FLASH_FLAG_SIZERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_BSY
  *         @arg @ref LL_FLASH_FLAG_WDW
  *         @arg @ref LL_FLASH_FLAG_ALL
  * @retval State of selected flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_ReadFlag_SR(const FLASH_TypeDef *flashx, uint32_t flag)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return (READ_BIT(FLASH_NS->NSSR, flag));
}

/**
  * @brief  Clear the flash operation flag for the non-secure flash memory.
  * @rmtoll NSSR      EOP/OPERR/PROGERR/WRPERR/PGAERR/SIZERR/PGSERR      LL_FLASH_NS_ClearFlag
  * @param  FLASH instance.
  * @param  flag
  *         This parameter can be a combination of the following values :
  *         @arg @ref LL_FLASH_FLAG_EOP
  *         @arg @ref LL_FLASH_FLAG_OPERR
  *         @arg @ref LL_FLASH_FLAG_PROGERR
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGAERR
  *         @arg @ref LL_FLASH_FLAG_SIZERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_ALL
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag(FLASH_TypeDef *flashx, uint32_t flag)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  SET_BIT(FLASH_NS->NSSR, flag);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash end of operation flag is active.
  * @rmtoll NSSR/SECSR           EOP           LL_FLASH_IsActiveFlag_EOP
  * @param  FLASH instance.
  * @retval State of EOP flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_EOP(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECSR, FLASH_SECSR_EOP) == (FLASH_SECSR_EOP)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSSR, FLASH_NSSR_EOP) == (FLASH_NSSR_EOP)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if the flash end of operation flag is active for the non-secure flash memory.
  * @rmtoll
  *  NSSR           EOP           LL_FLASH_NS_IsActiveFlag_EOP
  * @param  FLASH instance.
  * @retval State of non-secure EOP flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_EOP(const FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSSR, FLASH_NSSR_EOP) == (FLASH_NSSR_EOP)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Clear the flash end of operation flag.
  * @rmtoll NSSR/SECSR           EOP           LL_FLASH_ClearFlag_EOP
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_EOP(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECSR, FLASH_SECSR_EOP);
#else
  SET_BIT(flashx->NSSR, FLASH_NSSR_EOP);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Clear the flash end of operation flag for the non-secure flash memory.
  * @rmtoll
  *  NSSR           EOP           LL_FLASH_NS_ClearFlag_EOP
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_EOP(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  SET_BIT(FLASH_NS->NSSR, FLASH_NSSR_EOP);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash operation error flag is active.
  * @rmtoll NSSR/SECSR           OPERR           LL_FLASH_IsActiveFlag_OPERR
  * @param  FLASH instance.
  * @retval State of ERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OPERR(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECSR, FLASH_SECSR_OPERR) == (FLASH_SECSR_OPERR)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSSR, FLASH_NSSR_OPERR) == (FLASH_NSSR_OPERR)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if the flash operation error flag is active for the non-secure flash memory.
  * @rmtoll
  *  NSSR           OPERR           LL_FLASH_NS_IsActiveFlag_OPERR
  * @param  FLASH instance.
  * @retval State of non-secure ERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_OPERR(const FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSSR, FLASH_NSSR_OPERR) == (FLASH_NSSR_OPERR)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Clear the flash operation error flag.
  * @rmtoll NSSR/SECSR           OPERR           LL_FLASH_ClearFlag_OPERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_OPERR(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECSR, FLASH_SECSR_OPERR);
#else
  SET_BIT(flashx->NSSR, FLASH_NSSR_OPERR);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Clear the flash operation error flag for the non-secure flash memory.
  * @rmtoll
  *  NSSR           OPERR           LL_FLASH_NS_ClearFlag_OPERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_OPERR(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  SET_BIT(FLASH_NS->NSSR, FLASH_NSSR_OPERR);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash programming error flag is active.
  * @rmtoll NSSR/SECSR           PROGERR           LL_FLASH_IsActiveFlag_PROGERR
  * @param  FLASH instance.
  * @retval State of PROGERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_PROGERR(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECSR, FLASH_SECSR_PROGERR) == (FLASH_SECSR_PROGERR)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSSR, FLASH_NSSR_PROGERR) == (FLASH_NSSR_PROGERR)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if the flash programming error flag is active for the non-secure flash memory.
  * @rmtoll
  *  NSSR           PROGERR           LL_FLASH_NS_IsActiveFlag_PROGERR
  * @param  FLASH instance.
  * @retval State of non-secure PROGERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_PROGERR(const FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSSR, FLASH_NSSR_PROGERR) == (FLASH_NSSR_PROGERR)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Clear the flash programming error flag.
  * @rmtoll NSSR/SECSR           PROGERR           LL_FLASH_ClearFlag_PROGERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_PROGERR(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECSR, FLASH_SECSR_PROGERR);
#else
  SET_BIT(flashx->NSSR, FLASH_NSSR_PROGERR);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Clear the flash programming error flag for the non-secure flash memory.
  * @rmtoll
  *  NSSR           PROGERR           LL_FLASH_NS_ClearFlag_PROGERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_PROGERR(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  SET_BIT(FLASH_NS->NSSR, FLASH_NSSR_PROGERR);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash write protection error flag is active.
  * @rmtoll NSSR/SECSR           WRPERR           LL_FLASH_IsActiveFlag_WRPERR
  * @param  FLASH instance.
  * @retval State of WRPERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_WRPERR(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECSR, FLASH_SECSR_WRPERR) == (FLASH_SECSR_WRPERR)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSSR, FLASH_NSSR_WRPERR) == (FLASH_NSSR_WRPERR)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if the flash write protection error flag is activefor the non-secure flash memory.
  * @rmtoll
  *  NSSR           WRPERR           LL_FLASH_NS_IsActiveFlag_WRPERR
  * @param  FLASH instance.
  * @retval State of non-secure WRPERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_WRPERR(const FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSSR, FLASH_NSSR_WRPERR) == (FLASH_NSSR_WRPERR)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Clear the flash write protection error flag.
  * @rmtoll NSSR/SECSR           WRPERR           LL_FLASH_ClearFlag_WRPERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_WRPERR(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECSR, FLASH_SECSR_WRPERR);
#else
  SET_BIT(flashx->NSSR, FLASH_NSSR_WRPERR);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Clear the flash write protection error flag for the non-secure flash memory.
  * @rmtoll
  *  NSSR           WRPERR           LL_FLASH_NS_ClearFlag_WRPERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_WRPERR(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  SET_BIT(FLASH_NS->NSSR, FLASH_NSSR_WRPERR);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash programming alignment error flag is active.
  * @rmtoll NSSR/SECSR           PGAERR           LL_FLASH_IsActiveFlag_PGAERR
  * @param  FLASH instance.
  * @retval State of PGAERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_PGAERR(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECSR, FLASH_SECSR_PGAERR) == (FLASH_SECSR_PGAERR)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSSR, FLASH_NSSR_PGAERR) == (FLASH_NSSR_PGAERR)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if the flash programming alignment error flag is active for the non-secure flash memory.
  * @rmtoll
  *  NSSR           PGAERR           LL_FLASH_NS_IsActiveFlag_PGAERR
  * @param  FLASH instance.
  * @retval State of non-secure PGAERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_PGAERR(const FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSSR, FLASH_NSSR_PGAERR) == (FLASH_NSSR_PGAERR)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Clear the flash programming alignment error flag.
  * @rmtoll NSSR/SECSR           PGAERR           LL_FLASH_ClearFlag_PGAERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_PGAERR(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECSR, FLASH_SECSR_PGAERR);
#else
  SET_BIT(flashx->NSSR, FLASH_NSSR_PGAERR);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Clear the flash programming alignment error flag for the non-secure flash memory.
  * @rmtoll
  *  NSSR           PGAERR           LL_FLASH_NS_ClearFlag_PGAERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_PGAERR(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  SET_BIT(FLASH_NS->NSSR, FLASH_NSSR_PGAERR);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash size error flag is active.
  * @rmtoll NSSR/SECSR           SIZERR           LL_FLASH_IsActiveFlag_SIZERR
  * @param  FLASH instance.
  * @retval State of SIZERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_SIZERR(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECSR, FLASH_SECSR_SIZERR) == (FLASH_SECSR_SIZERR)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSSR, FLASH_NSSR_SIZERR) == (FLASH_NSSR_SIZERR)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if the flash size error flag is active for the non-secure flash memory.
  * @rmtoll
  *  NSSR           SIZERR           LL_FLASH_NS_IsActiveFlag_SIZERR
  * @param  FLASH instance.
  * @retval State of non-secure SIZERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_SIZERR(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSSR, FLASH_NSSR_SIZERR) == (FLASH_NSSR_SIZERR)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Clear the flash size error flag.
  * @rmtoll NSSR/SECSR           SIZERR           LL_FLASH_ClearFlag_SIZERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_SIZERR(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECSR, FLASH_SECSR_SIZERR);
#else
  SET_BIT(flashx->NSSR, FLASH_NSSR_SIZERR);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Clear the flash size error flag for the non-secure flash memory.
  * @rmtoll
  *  NSSR           SIZERR           LL_FLASH_NS_ClearFlag_SIZERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_SIZERR(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  SET_BIT(FLASH_NS->NSSR, FLASH_NSSR_SIZERR);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash programming sequence error flag is active.
  * @rmtoll NSSR/SECSR           PGSERR           LL_FLASH_IsActiveFlag_PGSERR
  * @param  FLASH instance.
  * @retval State of PGSERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_PGSERR(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECSR, FLASH_SECSR_PGSERR) == (FLASH_SECSR_PGSERR)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSSR, FLASH_NSSR_PGSERR) == (FLASH_NSSR_PGSERR)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if the flash programming sequence error flag is active for the non-secure flash memory.
  * @rmtoll
  *  NSSR           PGSERR           LL_FLASH_NS_IsActiveFlag_PGSERR
  * @param  FLASH instance.
  * @retval State of non-secure PGSERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_PGSERR(const FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSSR, FLASH_NSSR_PGSERR) == (FLASH_NSSR_PGSERR)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Clear the flash programming sequence error flag.
  * @rmtoll NSSR/SECSR           PGSERR           LL_FLASH_ClearFlag_PGSERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_PGSERR(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECSR, FLASH_SECSR_PGSERR);
#else
  SET_BIT(flashx->NSSR, FLASH_NSSR_PGSERR);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Clear the flash programming sequence error flag for the non-secure flash memory.
  * @rmtoll
  *  NSSR           PGSERR           LL_FLASH_NS_ClearFlag_PGSERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_PGSERR(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  SET_BIT(FLASH_NS->NSSR, FLASH_NSSR_PGSERR);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash option bytes write error flag is active.
  * @rmtoll
  *  NSSR           OPTWERR           LL_FLASH_IsActiveFlag_OPTWERR
  * @param  FLASH instance.
  * @retval State of OPTWERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OPTWERR(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->NSSR, FLASH_NSSR_OPTWERR) == (FLASH_NSSR_OPTWERR)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the flash option bytes write error flag.
  * @rmtoll
  *  NSSR           OPTWERR           LL_FLASH_ClearFlag_OPTWERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_OPTWERR(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->NSSR, FLASH_NSSR_OPTWERR);
}

/**
  * @brief  Check if the flash busy flag is active.
  * @rmtoll NSSR/SECSR           BSY           LL_FLASH_IsActiveFlag_BSY
  * @param  FLASH instance.
  * @retval State of BSY flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_BSY(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECSR, FLASH_SECSR_BSY) == (FLASH_SECSR_BSY)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSSR, FLASH_NSSR_BSY) == (FLASH_NSSR_BSY)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if the flash busy flag is active for the non-secure flash memory.
  * @rmtoll
  *  NSSR           BSY           LL_FLASH_NS_IsActiveFlag_BSY
  * @param  FLASH instance.
  * @retval State of non-secure BSY flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_BSY(const FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSSR, FLASH_NSSR_BSY) == (FLASH_NSSR_BSY)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash wait data to write flag is active.
  * @rmtoll NSSR/SECSR           WDW           LL_FLASH_IsActiveFlag_WDW
  * @param  FLASH instance.
  * @retval State of WDW flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_WDW(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECSR, FLASH_SECSR_WDW) == (FLASH_SECSR_WDW)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSSR, FLASH_NSSR_WDW) == (FLASH_NSSR_WDW)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if the flash wait data to write flag is active for the non-secure flash memory.
  * @rmtoll
  *  NSSR           WDW           LL_FLASH_NS_IsActiveFlag_WDW
  * @param  FLASH instance.
  * @retval State of non-secure WDW flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_WDW(const FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSSR, FLASH_NSSR_WDW) == (FLASH_NSSR_WDW)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash OEM1 lock flag is active.
  * @rmtoll
  *  NSSR           OEM1LOCK           LL_FLASH_IsActiveFlag_OEM1LOCK
  * @param  FLASH instance.
  * @retval State of OEM1LOCK flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OEM1LOCK(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->NSSR, FLASH_NSSR_OEM1LOCK) == (FLASH_NSSR_OEM1LOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the flash OEM2 lock flag is active.
  * @rmtoll
  *  NSSR           OEM2LOCK           LL_FLASH_IsActiveFlag_OEM2LOCK
  * @param  FLASH instance.
  * @retval State of OEM2LOCK flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OEM2LOCK(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->NSSR, FLASH_NSSR_OEM2LOCK) == (FLASH_NSSR_OEM2LOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the flash bank1 power down mode flag is active.
  * @rmtoll
  *  NSSR           PD1           LL_FLASH_IsActiveFlag_PD1
  * @param  FLASH instance.
  * @retval State of PD1 flag
  *     0 : the FLASH memory bank 1 is in normal mode.
  *     1 : the FLASH memory bank 1 is in power-down mode.
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_PD1(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->NSSR, FLASH_NSSR_PD1) == (FLASH_NSSR_PD1)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the flash bank2 power down mode flag is active.
  * @rmtoll
  *  NSSR           PD2           LL_FLASH_IsActiveFlag_PD2
  * @param  FLASH instance.
  * @retval State of PD2 flag
  *     0 : the FLASH memory bank 2 is in normal mode.
  *     1 : the FLASH memory bank 2 is in power-down mode.
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_PD2(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->NSSR, FLASH_NSSR_PD2) == (FLASH_NSSR_PD2)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the flash bank1 or bank2 power down mode flag is active.
  * @rmtoll
  *  NSSR           PD           LL_FLASH_IsActiveFlag_PD
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_FLAG_PD1
  *         @arg @ref LL_FLASH_FLAG_PD2
  * @retval State of PDx flag
  *     0 : the FLASH memory bank1 or bank2 is in normal mode.
  *     1 : the FLASH memory bank1 or bank2 is in power-down mode.
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_PD(const FLASH_TypeDef *flashx, uint32_t bank)
{
  return ((READ_BIT(flashx->NSSR, bank) == (bank)) ? 1UL : 0UL);
}

/**
  * @}
  */

/**
  * @brief  Enable the flash programming.
  * @rmtoll NSCR/SECCR           PG           LL_FLASH_EnableProgramming
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableProgramming(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECCR, FLASH_SECCR_PG);
#else
  SET_BIT(flashx->NSCR, FLASH_NSCR_PG);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Enable the flash programming for the non-secure flash memory.
  * @rmtoll
  *  NSCR           PG           LL_FLASH_NS_EnableProgramming
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnableProgramming(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  SET_BIT(FLASH_NS->NSCR, FLASH_NSCR_PG);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Disable the flash programming.
  * @rmtoll NSCR/SECCR           PG           LL_FLASH_DisableProgramming
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableProgramming(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  CLEAR_BIT(flashx->SECCR, FLASH_SECCR_PG);
#else
  CLEAR_BIT(flashx->NSCR, FLASH_NSCR_PG);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Disable the flash programming for the non-secure flash memory.
  * @rmtoll
  *  NSCR           PG           LL_FLASH_NS_DisableProgramming
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableProgramming(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  CLEAR_BIT(FLASH_NS->NSCR, FLASH_NSCR_PG);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash programming is enabled or disabled.
  * @rmtoll NSCR/SECCR           PG           LL_FLASH_IsEnabledProgramming
  * @param  FLASH instance.
  * @retval State of flash programming (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledProgramming(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECCR, FLASH_SECCR_PG) == (FLASH_SECCR_PG)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSCR, FLASH_NSCR_PG) == (FLASH_NSCR_PG)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if the flash programming is enabled or disabled for the non-secure flash memory.
  * @rmtoll
  *  NSCR           PG           LL_FLASH_NS_IsEnabledProgramming
  * @param  FLASH instance.
  * @retval State of flash non-secure programming (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledProgramming(const FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSCR, FLASH_NSCR_PG) == (FLASH_NSCR_PG)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Enable the flash page erase.
  * @rmtoll NSCR/SECCR           PER           LL_FLASH_EnablePageErase
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnablePageErase(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECCR, FLASH_SECCR_PER);
#else
  SET_BIT(flashx->NSCR, FLASH_NSCR_PER);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Enable the flash page erase for the non-secure flash memory.
  * @rmtoll
  *  NSCR           PER           LL_FLASH_NS_EnablePageErase
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnablePageErase(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  SET_BIT(FLASH_NS->NSCR, FLASH_NSCR_PER);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Disable the flash page erase.
  * @rmtoll NSCR/SECCR           PER           LL_FLASH_DisablePageErase
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisablePageErase(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  CLEAR_BIT(flashx->SECCR, FLASH_SECCR_PER);
#else
  CLEAR_BIT(flashx->NSCR, FLASH_NSCR_PER);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Disable the flash page erase for the non-secure flash memory.
  * @rmtoll
  *  NSCR           PER           LL_FLASH_NS_DisablePageErase
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisablePageErase(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  CLEAR_BIT(FLASH_NS->NSCR, FLASH_NSCR_PER);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash page erase is enabled or disabled.
  * @rmtoll NSCR/SECCR           PER           LL_FLASH_IsEnabledPageErase
  * @param  FLASH instance.
  * @retval State of flash page erase (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPageErase(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECCR, FLASH_SECCR_PER) == (FLASH_SECCR_PER)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSCR, FLASH_NSCR_PER) == (FLASH_NSCR_PER)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if the flash page erase is enabled or disabled for the non-secure flash memory.
  * @rmtoll
  *  NSCR           PER           LL_FLASH_NS_IsEnabledPageErase
  * @param  FLASH instance.
  * @retval State of flash non-secure page erase (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledPageErase(const FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSCR, FLASH_NSCR_PER) == (FLASH_NSCR_PER)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Enable the flash bank mass erase.
  * @rmtoll NSCR/SECCR           MER1/MER2           LL_FLASH_BANK_EnableMassErase
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_1
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_2
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_ALL
  */
__STATIC_INLINE void LL_FLASH_BANK_EnableMassErase(FLASH_TypeDef *flashx, uint32_t bank)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  MODIFY_REG(flashx->SECCR, (FLASH_SECCR_MER1 | FLASH_SECCR_MER2), bank);
#else
  MODIFY_REG(flashx->NSCR, (FLASH_NSCR_MER1 | FLASH_NSCR_MER2), bank);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Enable the flash bank mass erase for the non-secure flash memory.
  * @rmtoll NSCR           MER1/MER2           LL_FLASH_NS_BANK_EnableMassErase
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_1
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_2
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_ALL
  */
__STATIC_INLINE void LL_FLASH_NS_BANK_EnableMassErase(FLASH_TypeDef *flashx, uint32_t bank)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  MODIFY_REG(FLASH_NS->NSCR, (FLASH_NSCR_MER1 | FLASH_NSCR_MER2), bank);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Disable the flash bank mass erase.
  * @rmtoll NSCR/SECCR           MER1/MER2           LL_FLASH_BANK_DisableMassErase
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_1
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_2
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_ALL
  */
__STATIC_INLINE void LL_FLASH_BANK_DisableMassErase(FLASH_TypeDef *flashx, uint32_t bank)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  CLEAR_BIT(flashx->SECCR, bank);
#else
  CLEAR_BIT(flashx->NSCR, bank);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Disable the flash bank mass erase for the non-secure flash memory.
  * @rmtoll NSCR           MER1/MER2           LL_FLASH_EnableBank1MassErase
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_1
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_2
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_ALL
  */
__STATIC_INLINE void LL_FLASH_NS_BANK_DisableMassErase(FLASH_TypeDef *flashx, uint32_t bank)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  CLEAR_BIT(FLASH_NS->NSCR, bank);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash bank mass erase is enabled or disabled.
  * @rmtoll NSCR/SECCR           MER1/MER2           LL_FLASH_BANK_IsEnabledMassErase
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_1
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_2
  * @retval State of flash mass erase (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_BANK_IsEnabledMassErase(const FLASH_TypeDef *flashx, uint32_t bank)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECCR, bank) == (bank)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSCR, bank) == (bank)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if the flash bank mass erase is enabled or disabled for the non-secure flash memory.
  * @rmtoll NSCR           MER1/MER2           LL_FLASH_NS_BANK_IsEnabledMassErase
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_1
  *         @arg @ref LL_FLASH_MASS_ERASE_BANK_2
  * @retval State of flash non-secure mass erase (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_BANK_IsEnabledMassErase(const FLASH_TypeDef *flashx, uint32_t bank)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSCR, bank) == (bank)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Set the flash page erase index.
  * @rmtoll NSCR/SECCR           BKER/PNB           LL_FLASH_BANK_SetPageEraseIndex
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_PAGE_ERASE_BANK_1
  *         @arg @ref LL_FLASH_PAGE_ERASE_BANK_2
  * @param  page_idx This parameter a value in [0:127]
  */
__STATIC_INLINE void LL_FLASH_BANK_SetPageEraseIndex(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page_idx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  MODIFY_REG(flashx->SECCR, FLASH_SECCR_BKER | FLASH_SECCR_PNB, (bank | (page_idx << FLASH_SECCR_PNB_Pos)));
#else
  MODIFY_REG(flashx->NSCR, FLASH_NSCR_BKER | FLASH_NSCR_PNB, (bank | (page_idx << FLASH_NSCR_PNB_Pos)));
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Set the flash page erase index for the non-secure flash memory.
  * @rmtoll NSCR           BKER/PNB           LL_FLASH_NS_BANK_SetPageEraseIndex
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_PAGE_ERASE_BANK_1
  *         @arg @ref LL_FLASH_PAGE_ERASE_BANK_2
  * @param  page_idx This parameter a value in [0:127]
  */
__STATIC_INLINE void LL_FLASH_NS_BANK_SetPageEraseIndex(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page_idx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  MODIFY_REG(FLASH_NS->NSCR, FLASH_NSCR_BKER | FLASH_NSCR_PNB, (bank | (page_idx << FLASH_NSCR_PNB_Pos)));
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Set the flash programming mode.
  * @rmtoll NSCR/SECCR           BWR           LL_FLASH_SetProgrammingMode
  * @param  FLASH instance.
  * @param  programming_mode
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_PROGRAM_QUADWORD_MODE
  *         @arg @ref LL_FLASH_PROGRAM_BURST_MODE
  */
__STATIC_INLINE void LL_FLASH_SetProgrammingMode(FLASH_TypeDef *flashx, uint32_t programming_mode)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  MODIFY_REG(flashx->SECCR, FLASH_SECCR_BWR, programming_mode);
#else
  MODIFY_REG(flashx->NSCR, FLASH_NSCR_BWR, programming_mode);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Set the flash programming mode for the non-secure flash memory.
  * @rmtoll
  *  NSCR           BWR           LL_FLASH_NS_SetProgrammingMode
  * @param  FLASH instance.
  * @param  programming_mode
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_PROGRAM_QUADWORD_MODE
  *         @arg @ref LL_FLASH_PROGRAM_BURST_MODE
  */
__STATIC_INLINE void LL_FLASH_NS_SetProgrammingMode(FLASH_TypeDef *flashx, uint32_t programming_mode)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  MODIFY_REG(FLASH_NS->NSCR, FLASH_NSCR_BWR, programming_mode);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Get the flash programming mode.
  * @rmtoll NSCR/SECCR           BWR           LL_FLASH_GetProgrammingMode
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_PROGRAM_QUADWORD_MODE
  *         @arg @ref LL_FLASH_PROGRAM_BURST_MODE
  */
__STATIC_INLINE uint32_t LL_FLASH_GetProgrammingMode(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return (READ_BIT(flashx->SECCR, FLASH_SECCR_BWR)) ;
#else
  return (READ_BIT(flashx->NSCR, FLASH_NSCR_BWR));
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Get the flash programming mode for the non-secure flash memory.
  * @rmtoll
  *  NSCR           BWR           LL_FLASH_NS_GetProgrammingMode
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_PROGRAM_QUADWORD_MODE
  *         @arg @ref LL_FLASH_PROGRAM_BURST_MODE
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_GetProgrammingMode(const FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return (READ_BIT(FLASH_NS->NSCR, FLASH_NSCR_BWR));
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Set the configuration of flash programming.
  * @rmtoll NSCR/SECCR           PG/BWR           LL_FLASH_SetConfigProgramming
  * @param  FLASH instance.
  * @param  programming_mode
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_PROGRAM_QUADWORD_MODE
  *         @arg @ref LL_FLASH_PROGRAM_BURST_MODE
  */
__STATIC_INLINE void LL_FLASH_SetConfigProgramming(FLASH_TypeDef *flashx, uint32_t programming_mode)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  MODIFY_REG(flashx->SECCR, FLASH_SECCR_BWR | FLASH_SECCR_PG, programming_mode | FLASH_SECCR_PG);
#else
  MODIFY_REG(flashx->NSCR, FLASH_NSCR_BWR | FLASH_NSCR_PG, programming_mode | FLASH_NSCR_PG);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Set the configuration of flash programming for the non-secure flash memory.
  * @rmtoll NSCR           PG/BWR           LL_FLASH_NS_SetConfigProgramming
  * @param  FLASH instance.
  * @param  programming_mode
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_PROGRAM_QUADWORD_MODE
  *         @arg @ref LL_FLASH_PROGRAM_BURST_MODE
  */
__STATIC_INLINE void LL_FLASH_NS_SetConfigProgramming(FLASH_TypeDef *flashx, uint32_t programming_mode)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  MODIFY_REG(FLASH_NS->NSCR, FLASH_NSCR_BWR | FLASH_NSCR_PG, programming_mode | FLASH_NSCR_PG);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Start the flash erase operation.
  * @rmtoll NSCR/SECCR           STRT           LL_FLASH_StartEraseOperation
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_StartEraseOperation(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECCR, FLASH_SECCR_STRT);
#else
  SET_BIT(flashx->NSCR, FLASH_NSCR_STRT);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Start the flash erase operation for the non-secure flash memory.
  * @rmtoll
  *  NSCR           STRT           LL_FLASH_NS_StartEraseOperation
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_StartEraseOperation(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  __IO uint32_t *reg_addr = &FLASH_NS->NSCR;
  SET_BIT(*reg_addr, FLASH_NSCR_STRT);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Start the flash erase page.
  * @rmtoll NSCR/SECCR           BKER/PNB/PER/STRT           LL_FLASH_StartErasePage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_PAGE_ERASE_BANK_1
  *         @arg @ref LL_FLASH_PAGE_ERASE_BANK_2
  * @param  page_idx This parameter a value in [0:127]
  */
__STATIC_INLINE void LL_FLASH_StartErasePage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page_idx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  MODIFY_REG(flashx->SECCR, FLASH_SECCR_BKER | FLASH_SECCR_PNB | FLASH_SECCR_PER | FLASH_SECCR_STRT,
             (bank | (page_idx << FLASH_SECCR_PNB_Pos) | FLASH_SECCR_PER | FLASH_SECCR_STRT));
#else
  MODIFY_REG(flashx->NSCR, FLASH_NSCR_BKER | FLASH_NSCR_PNB | FLASH_NSCR_PER | FLASH_NSCR_STRT,
             (bank | (page_idx << FLASH_NSCR_PNB_Pos) | FLASH_NSCR_PER | FLASH_NSCR_STRT));
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Start the flash erase page for the non-secure flash memory.
  * @rmtoll NSCR           BKER/PNB/PER/STRT           LL_FLASH_NS_StartErasePage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_PAGE_ERASE_BANK_1
  *         @arg @ref LL_FLASH_PAGE_ERASE_BANK_2
  * @param  page_idx This parameter a value in [0:127]
  */
__STATIC_INLINE void LL_FLASH_NS_StartErasePage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page_idx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  __IO uint32_t *reg_addr = &FLASH_NS->NSCR;
  MODIFY_REG(*reg_addr, FLASH_NSCR_BKER | FLASH_NSCR_PNB | FLASH_NSCR_PER | FLASH_NSCR_STRT,
             (bank | (page_idx << FLASH_NSCR_PNB_Pos) | FLASH_NSCR_PER | FLASH_NSCR_STRT));
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Start the flash erase bank.
  * @rmtoll NSCR/SECCR           MER1/MER2/STRT           LL_FLASH_StartEraseBank
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_PAGE_ERASE_BANK_1
  *         @arg @ref LL_FLASH_PAGE_ERASE_BANK_2
  */
__STATIC_INLINE void LL_FLASH_StartEraseBank(FLASH_TypeDef *flashx, uint32_t bank)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  MODIFY_REG(flashx->SECCR, FLASH_SECCR_MER1 | FLASH_SECCR_MER2 | FLASH_SECCR_STRT, (bank | FLASH_SECCR_STRT));
#else
  MODIFY_REG(flashx->NSCR, FLASH_NSCR_MER1 | FLASH_NSCR_MER2 | FLASH_NSCR_STRT, (bank | FLASH_NSCR_STRT));
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Start the flash erase bank for the non-secure flash memory.
  * @rmtoll NSCR           MER1/MER2/STRT           LL_FLASH_NS_StartEraseBank
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_PAGE_ERASE_BANK_1
  *         @arg @ref LL_FLASH_PAGE_ERASE_BANK_2
  */
__STATIC_INLINE void LL_FLASH_NS_StartEraseBank(FLASH_TypeDef *flashx, uint32_t bank)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  __IO uint32_t *reg_addr = &FLASH_NS->NSCR;
  MODIFY_REG(*reg_addr, FLASH_NSCR_MER1 | FLASH_NSCR_MER2 | FLASH_NSCR_STRT, (bank | FLASH_NSCR_STRT));
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Disable all flash operation.
  * @rmtoll NSCR/SECCR           EOPIE/ERRIE/PG/PER/MER1/MER2           LL_FLASH_DisableAllOperation
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableAllOperation(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  CLEAR_BIT(flashx->SECCR, FLASH_SECCR_EOPIE | FLASH_SECCR_ERRIE | FLASH_SECCR_PG \
            | FLASH_SECCR_PER | FLASH_SECCR_MER1 | FLASH_SECCR_MER2);
#else
  CLEAR_BIT(flashx->NSCR, FLASH_NSCR_EOPIE | FLASH_NSCR_ERRIE | FLASH_NSCR_PG \
            | FLASH_NSCR_PER | FLASH_NSCR_MER1 | FLASH_NSCR_MER2);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Disable all flash operation for the non-secure flash memory.
  * @rmtoll NSCR           EOPIE/ERRIE/PG/PER/MER1/MER2          LL_FLASH_NS_DisableAllOperation
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableAllOperation(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  CLEAR_BIT(FLASH_NS->NSCR, FLASH_NSCR_EOPIE | FLASH_NSCR_ERRIE | FLASH_NSCR_PG \
            | FLASH_NSCR_PER | FLASH_NSCR_MER1 | FLASH_NSCR_MER2);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Start the flash option bytes modification.
  * @rmtoll
  *  NSCR           OPTSTRT           LL_FLASH_OB_StartModification
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_StartModification(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->NSCR, FLASH_NSCR_OPTSTRT);
}

/**
  * @brief  Enable the flash interrupt.
  * @rmtoll NSCR/SECCR          EOPIE/ERRIE        LL_FLASH_EnableIT
  * @param  FLASH instance.
  * @param  interrupt
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_IT_EOP
  *         @arg @ref LL_FLASH_IT_ERR
  *         @arg @ref LL_FLASH_IT_ALL
  */
__STATIC_INLINE void LL_FLASH_EnableIT(FLASH_TypeDef *flashx, uint32_t interrupt)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECCR, interrupt);
#else
  SET_BIT(flashx->NSCR, interrupt);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Enable the flash interrupt for the non-secure flash memory.
  * @rmtoll NSCR          EOPIE/ERRIE        LL_FLASH_NS_EnableIT
  * @param  FLASH instance.
  * @param  interrupt
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_IT_EOP
  *         @arg @ref LL_FLASH_IT_ERR
  *         @arg @ref LL_FLASH_IT_ALL
  */
__STATIC_INLINE void LL_FLASH_NS_EnableIT(FLASH_TypeDef *flashx, uint32_t interrupt)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  SET_BIT(FLASH_NS->NSCR, interrupt);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Disable the flash interrupt.
  * @rmtoll NSCR/SECCR          EOPIE/ERRIE        LL_FLASH_DisableIT
  * @param  FLASH instance.
  * @param  interrupt
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_IT_EOP
  *         @arg @ref LL_FLASH_IT_ERR
  *         @arg @ref LL_FLASH_IT_ALL
  */
__STATIC_INLINE void LL_FLASH_DisableIT(FLASH_TypeDef *flashx, uint32_t interrupt)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  CLEAR_BIT(flashx->SECCR, interrupt);
#else
  CLEAR_BIT(flashx->NSCR, interrupt);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Disable the flash interrupt for the non-secure flash memory.
  * @rmtoll NSCR          EOPIE/ERRIE        LL_FLASH_NS_DisableIT
  * @param  FLASH instance.
  * @param  interrupt
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_IT_EOP
  *         @arg @ref LL_FLASH_IT_ERR
  *         @arg @ref LL_FLASH_IT_ALL
  */
__STATIC_INLINE void LL_FLASH_NS_DisableIT(FLASH_TypeDef *flashx, uint32_t interrupt)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  CLEAR_BIT(FLASH_NS->NSCR, interrupt);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Enable the flash end of operation interrupt.
  * @rmtoll NSCR/SECCR          EOPIE        LL_FLASH_EnableIT_EOP
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableIT_EOP(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECCR, FLASH_SECCR_EOPIE);
#else
  SET_BIT(flashx->NSCR, FLASH_NSCR_EOPIE);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Enable the flash end of operation interrupt for the non-secure flash memory.
  * @rmtoll
  *  NSCR          EOPIE        LL_FLASH_NS_EnableIT_EOP
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnableIT_EOP(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  SET_BIT(FLASH_NS->NSCR, FLASH_NSCR_EOPIE);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Disable the flash end of operation interrupt.
  * @rmtoll
  *  NSCR          EOPIE        LL_FLASH_DisableIT_EOP
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableIT_EOP(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  CLEAR_BIT(flashx->SECCR, FLASH_SECCR_EOPIE);
#else
  CLEAR_BIT(flashx->NSCR, FLASH_NSCR_EOPIE);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Disable the flash end of operation interrupt for the non-secure flash memory.
  * @rmtoll
  *  NSCR          EOPIE        LL_FLASH_NS_DisableIT_EOP
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableIT_EOP(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  CLEAR_BIT(FLASH_NS->NSCR, FLASH_NSCR_EOPIE);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash end of operation interrupt is enabled or disabled.
  * @rmtoll NSCR/SECCR          EOPIE        LL_FLASH_IsEnabledIT_EOP
  * @param  FLASH instance.
  * @retval State of flash EOP interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_EOP(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECCR, FLASH_SECCR_EOPIE) == (FLASH_SECCR_EOPIE)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSCR, FLASH_NSCR_EOPIE) == (FLASH_NSCR_EOPIE)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if the flash end of operation interrupt is enabled or disabled for the non-secure flash memory.
  * @rmtoll
  *  NSCR          EOPIE        LL_FLASH_NS_IsEnabledIT_EOP
  * @param  FLASH instance.
  * @retval State of flash non-secure EOP interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledIT_EOP(const FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSCR, FLASH_NSCR_EOPIE) == (FLASH_NSCR_EOPIE)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Enable the flash error interrupt.
  * @rmtoll NSCR/SECCR          ERRIE        LL_FLASH_EnableIT_ERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableIT_ERR(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECCR, FLASH_SECCR_ERRIE);
#else
  SET_BIT(flashx->NSCR, FLASH_NSCR_ERRIE);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Enable the flash error interrupt for the non-secure flash memory.
  * @rmtoll
  *  NSCR          ERRIE        LL_FLASH_NS_EnableIT_ERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnableIT_ERR(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  SET_BIT(FLASH_NS->NSCR, FLASH_NSCR_ERRIE);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Disable the flash error interrupt.
  * @rmtoll
  *  NSCR          ERRIE        LL_FLASH_DisableIT_ERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableIT_ERR(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  CLEAR_BIT(flashx->SECCR, FLASH_SECCR_ERRIE);
#else
  CLEAR_BIT(flashx->NSCR, FLASH_NSCR_ERRIE);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Disable the flash error interrupt for the non-secure flash memory.
  * @rmtoll
  *  NSCR          ERRIE        LL_FLASH_NS_DisableIT_ERR
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableIT_ERR(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  CLEAR_BIT(FLASH_NS->NSCR, FLASH_NSCR_ERRIE);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash error interrupt is enabled or disabled.
  * @rmtoll NSCR/SECCR          ERRIE        LL_FLASH_IsEnabledIT_ERR
  * @param  FLASH instance.
  * @retval State of flash ERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_ERR(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECCR, FLASH_SECCR_ERRIE) == (FLASH_SECCR_ERRIE)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSCR, FLASH_NSCR_ERRIE) == (FLASH_NSCR_ERRIE)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if the flash error interrupt is enabled or disabled for the non-secure flash memory.
  * @rmtoll
  *  NSCR          ERRIE        LL_FLASH_NS_IsEnabledIT_ERR
  * @param  FLASH instance.
  * @retval State of flash non-secure ERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledIT_ERR(const FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSCR, FLASH_NSCR_ERRIE) == (FLASH_NSCR_ERRIE)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Launch the flash option bytes loading.
  * @rmtoll
  *  NSCR           OBL_LAUNCH           LL_FLASH_OB_Launch
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_Launch(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->NSCR, FLASH_NSCR_OBL_LAUNCH);
}

/**
  * @brief  Check if the flash option bytes loading is launched.
  * @rmtoll
  *  NSCR           OBL_LAUNCH           LL_FLASH_OB_IsLaunched
  * @param  FLASH instance.
  * @retval State of flash option bytes launch (1 launched / 0 not launched).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsLaunched(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->NSCR, FLASH_NSCR_OBL_LAUNCH) == (FLASH_NSCR_OBL_LAUNCH)) ? 1UL : 0UL);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Set the flash security state inversion.
  * @rmtoll
  *  SECCR           INV           LL_FLASH_SetSecurityStateInversion
  * @param  FLASH instance.
  * @param  sec_state_inversion
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_SEC_NOT_INVERTED
  *         @arg @ref LL_FLASH_SEC_INVERTED
  */
__STATIC_INLINE void LL_FLASH_SetSecurityStateInversion(FLASH_TypeDef *flashx, uint32_t sec_state_inversion)
{
  MODIFY_REG(flashx->SECCR, FLASH_SECCR_INV, sec_state_inversion);
}

/**
  * @brief  Get the flash security state inversion.
  * @rmtoll
  *  SECCR           INV           LL_FLASH_GetSecurityStateInversion
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_SEC_NOT_INVERTED
  *         @arg @ref LL_FLASH_SEC_INVERTED
  */
__STATIC_INLINE uint32_t LL_FLASH_GetSecurityStateInversion(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->SECCR, FLASH_SECCR_INV));
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Lock the flash option bytes control access registers.
  * @rmtoll
  *  NSCR           OPTLOCK           LL_FLASH_OB_Lock
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_Lock(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->NSCR, FLASH_NSCR_OPTLOCK);
}

/**
  * @brief  Check the flash option bytes control access registers lock state.
  * @rmtoll
  *  NSCR           OPTLOCK           LL_FLASH_OB_IsLocked
  * @param  FLASH instance.
  * @retval State of flash option bytes lock (1 locked / 0 unlocked).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsLocked(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->NSCR, FLASH_NSCR_OPTLOCK) == (FLASH_NSCR_OPTLOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Lock the flash control assess registers.
  * @rmtoll NSCR/SECCR           LOCK           LL_FLASH_Lock
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_Lock(FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(flashx->SECCR, FLASH_SECCR_LOCK);
#else
  SET_BIT(flashx->NSCR, FLASH_NSCR_LOCK);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Lock the flash control assess registers for the non-secure flash memory.
  * @rmtoll
  *  NSCR           LOCK           LL_FLASH_NS_Lock
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_Lock(FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  SET_BIT(FLASH_NS->NSCR, FLASH_NSCR_LOCK);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check the flash control access registers lock state.
  * @rmtoll NSCR/SECCR           LOCK           LL_FLASH_IsLocked
  * @param  FLASH instance.
  * @retval State of flash lock (1 locked / 0 unlocked).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsLocked(const FLASH_TypeDef *flashx)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(flashx->SECCR, FLASH_SECCR_LOCK) == (FLASH_SECCR_LOCK)) ? 1UL : 0UL);
#else
  return ((READ_BIT(flashx->NSCR, FLASH_NSCR_LOCK) == (FLASH_NSCR_LOCK)) ? 1U : 0U);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check the flash control access registers lock state for the non-secure flash memory.
  * @rmtoll
  *  NSCR           LOCK           LL_FLASH_NS_IsLocked
  * @param  FLASH instance.
  * @retval State of flash non-secure lock (1 locked / 0 unlocked).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsLocked(const FLASH_TypeDef *flashx)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  return ((READ_BIT(FLASH_NS->NSCR, FLASH_NSCR_LOCK) == (FLASH_NSCR_LOCK)) ? 1U : 0U);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Get the flash ECC fail address offset.
  * @rmtoll
  *  ECCR           ADDR_ECC           LL_FLASH_GetECCFailAddressOffset
  * @param  FLASH instance.
  * @retval Returned value : ECC failed address offset.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetECCFailAddressOffset(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->ECCR, FLASH_ECCR_ADDR_ECC));
}

/**
  * @brief  Get the flash ECC fail bank.
  * @rmtoll
  *  ECCR           BK_ECC           LL_FLASH_GetECCFailBank
  * @param  FLASH instance.
  * @retval Returned value : ECC failed bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetECCFailBank(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->ECCR, FLASH_ECCR_BK_ECC));
}

/**
  * @brief  Get the flash ECC fail system flash.
  * @rmtoll
  *  ECCR           SYSF_ECC           LL_FLASH_GetECCFailFlash
  * @param  FLASH instance.
  * @retval Returned value : ECC failed systeme flash.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetECCFailFlash(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->ECCR, FLASH_ECCR_SYSF_ECC));
}

/**
  * @brief  Get the flash ECC fail area.
  * @rmtoll ECCR           BK_ECC/SYSF_ECC           LL_FLASH_GetECCFailArea
  * @param  FLASH instance.
  * @retval Returned value : ECC failed systeme flash.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetECCFailArea(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->ECCR, (FLASH_ECCR_BK_ECC | FLASH_ECCR_SYSF_ECC)));
}

/**
  * @brief  Enable the flash ECC interrupt.
  * @rmtoll
  *  ECCR           ECCIE           LL_FLASH_EnableIT_ECC
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableIT_ECC(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->ECCR, FLASH_ECCR_ECCIE);
}

/**
  * @brief  Disable the flash ECC interrupt.
  * @rmtoll
  *  ECCR           ECCIE           LL_FLASH_DisableIT_ECC
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableIT_ECC(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->ECCR, FLASH_ECCR_ECCIE);
}

/**
  * @brief  Check if the flash ECC interrupt is enabled or disabled.
  * @rmtoll
  *  ECCR           ECCIE           LL_FLASH_IsEnabledIT_ECC
  * @param  FLASH instance.
  * @retval State of flash ECC interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_ECC(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->ECCR, FLASH_ECCR_ECCIE) == (FLASH_ECCR_ECCIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the flash ECC single error flag is active.
  * @rmtoll
  *  ECCR           ECCC           LL_FLASH_IsActiveFlag_ECCC
  * @param  FLASH instance.
  * @retval State of flash ECCC flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_ECCC(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->ECCR, FLASH_ECCR_ECCC) == (FLASH_ECCR_ECCC)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the flash ECC single error flag.
  * @rmtoll
  *  ECCR           ECCC           LL_FLASH_ClearFlag_ECCC
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_ECCC(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->ECCR, FLASH_ECCR_ECCC);
}

/**
  * @brief  Check if the flash ECC double error flag is active.
  * @rmtoll
  *  ECCR           ECCD           LL_FLASH_IsActiveFlag_ECCD
  * @param  FLASH instance.
  * @retval State of flash ECCD flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_ECCD(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->ECCR, FLASH_ECCR_ECCD) == (FLASH_ECCR_ECCD)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the flash ECC double error flag.
  * @rmtoll
  *  ECCR           ECCD           LL_FLASH_ClearFlag_ECCD
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_ECCD(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->ECCR, FLASH_ECCR_ECCD);
}

/**
  * @brief  Get the flash interrupted operation address offset.
  * @rmtoll
  *  OPSR           ADDR_OP           LL_FLASH_GetOperInterruptedAddressOffset
  * @param  FLASH instance.
  * @retval Returned value : the flash interrupted operation address offset.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetOperInterruptedAddressOffset(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPSR, FLASH_OPSR_ADDR_OP));
}

/**
  * @brief  Get the flash interrupted operation bank.
  * @rmtoll
  *  OPSR           BK_OP           LL_FLASH_GetOperInterruptedBank
  * @param  FLASH instance.
  * @retval Returned value : the flash interrupted operation bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetOperInterruptedBank(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPSR, FLASH_OPSR_BK_OP));
}

/**
  * @brief  Get the flash interrupted operation system flash.
  * @rmtoll
  *  OPSR           SYSF_OP           LL_FLASH_GetOperInterruptedFlash
  * @param  FLASH instance.
  * @retval Returned value : the flash interrupted operation system flash.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetOperInterruptedFlash(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPSR, FLASH_OPSR_SYSF_OP));
}

/**
  * @brief  Get the flash interrupted operation code.
  * @rmtoll
  *  OPSR           CODE_OP           LL_FLASH_GetOperInterruptedCode
  * @param  FLASH instance.
  * @retval Returned value : the flash interrupted operation code.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetOperInterruptedCode(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPSR, FLASH_OPSR_CODE_OP));
}

/**
  * @brief Set the flash Readout protection level.
  * @rmtoll
  *  OPTR           RDP           LL_FLASH_OB_SetRDPLevel
  * @param  FLASH instance.
  * @param  rdp_level
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RDP_LEVEL_0
  *         @arg @ref LL_FLASH_OB_RDP_LEVEL_0_5
  *         @arg @ref LL_FLASH_OB_RDP_LEVEL_1
  *         @arg @ref LL_FLASH_OB_RDP_LEVEL_2
  */
__STATIC_INLINE void LL_FLASH_OB_SetRDPLevel(FLASH_TypeDef *flashx, uint32_t rdp_level)
{
  MODIFY_REG(flashx->OPTR, FLASH_OPTR_RDP, rdp_level);
}

/**
  * @brief  Get the flash Readout protection level.
  * @rmtoll
  *  OPTR           RDP           LL_FLASH_OB_GetRDPLevel
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RDP_LEVEL_0
  *         @arg @ref LL_FLASH_OB_RDP_LEVEL_0_5
  *         @arg @ref LL_FLASH_OB_RDP_LEVEL_1
  *         @arg @ref LL_FLASH_OB_RDP_LEVEL_2
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetRDPLevel(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPTR, FLASH_OPTR_RDP));
}

/**
  * @brief  Set the flash BOR level.
  * @rmtoll
  *  OPTR           BOR_LEV           LL_FLASH_OB_SetBORLevel
  * @param  FLASH instance.
  * @param  bor_level
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_0
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_1
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_2
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_3
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_4
  */
__STATIC_INLINE void LL_FLASH_OB_SetBORLevel(FLASH_TypeDef *flashx, uint32_t bor_level)
{
  MODIFY_REG(flashx->OPTR, FLASH_OPTR_BOR_LEV, bor_level);
}

/**
  * @brief  Get the flash BOR level.
  * @rmtoll
  *  OPTR           BOR_LEV           LL_FLASH_OB_GetBORLevel
  * @param  FLASH instance.

  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_0
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_1
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_2
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_3
  *         @arg @ref LL_FLASH_OB_BOR_LEVEL_4
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetBORLevel(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPTR, FLASH_OPTR_BOR_LEV));
}

/**
  * @brief  Set the flash reset generation in stop mode.
  * @rmtoll
  *  OPTR           NRST_STOP           LL_FLASH_OB_SetNRSTStopMode
  * @param  FLASH instance.
  * @param  rst_generation
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RST_STOP_MODE
  *         @arg @ref LL_FLASH_OB_NO_RST_STOP_MODE
  */
__STATIC_INLINE void LL_FLASH_OB_SetNRSTStopMode(FLASH_TypeDef *flashx, uint32_t rst_generation)
{
  MODIFY_REG(flashx->OPTR, FLASH_OPTR_nRST_STOP, rst_generation);
}

/**
  * @brief  Get the flash reset generation in stop mode.
  * @rmtoll
  *  OPTR           NRST_STOP           LL_FLASH_OB_DisableNRSTStopMode
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RST_STOP_MODE
  *         @arg @ref LL_FLASH_OB_NO_RST_STOP_MODE
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetNRSTStopMode(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPTR, FLASH_OPTR_nRST_STOP));
}

/**
  * @brief  Set the flash reset generation in standby mode.
  * @rmtoll
  *  OPTR           NRST_STDBY           LL_FLASH_OB_SetNRSTStandbyMode
  * @param  FLASH instance.
  * @param  rst_generation
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RST_STDBY_MODE
  *         @arg @ref LL_FLASH_OB_NO_RST_STDBY_MODE
  */
__STATIC_INLINE void LL_FLASH_OB_SetNRSTStandbyMode(FLASH_TypeDef *flashx, uint32_t rst_generation)
{
  MODIFY_REG(flashx->OPTR, FLASH_OPTR_nRST_STDBY, rst_generation);
}

/**
  * @brief  Get the flash reset generation in standby mode.
  * @rmtoll
  *  OPTR           NRST_STDBY           LL_FLASH_OB_DisableNRSTStopMode
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RST_STDBY_MODE
  *         @arg @ref LL_FLASH_OB_NO_RST_STDBY_MODE
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetNRSTStandbyMode(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPTR, FLASH_OPTR_nRST_STDBY));
}

/**
  * @brief  Set the flash reset generation in shutdown mode.
  * @rmtoll
  *  OPTR           NRST_SHDW           LL_FLASH_OB_SetNRSTShutdownMode
  * @param  FLASH instance.
  * @param  rst_generation
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RST_SHDW_MODE
  *         @arg @ref LL_FLASH_OB_NO_RST_SHDW_MODE
  */
__STATIC_INLINE void LL_FLASH_OB_SetNRSTShutdownMode(FLASH_TypeDef *flashx, uint32_t rst_generation)
{
  MODIFY_REG(flashx->OPTR, FLASH_OPTR_nRST_SHDW, rst_generation);
}

/**
  * @brief  Get the flash reset generation in shutdown mode.
  * @rmtoll
  *  OPTR           NRST_SHDW           LL_FLASH_OB_GetNRSTShutdownMode
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RST_SHDW_MODE
  *         @arg @ref LL_FLASH_OB_NO_RST_SHDW_MODE
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetNRSTShutdownMode(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPTR, FLASH_OPTR_nRST_SHDW));
}

/**
  * @brief  Set the flash erase sram upon system reset.
  * @rmtoll
  *  OPTR           SRAM_RST           LL_FLASH_OB_SetSystemRstSRAMErase
  * @param  FLASH instance.
  * @param  erase_sram
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_ERASED_SRAM_SYS_RST
  *         @arg @ref LL_FLASH_OB_NOT_ERASED_SRAM_SYS_RST
  */
__STATIC_INLINE void LL_FLASH_OB_SetSystemRstSRAMErase(FLASH_TypeDef *flashx, uint32_t erase_sram)
{
  MODIFY_REG(flashx->OPTR, FLASH_OPTR_SRAM_RST, erase_sram);
}

/**
  * @brief  Get the flash erase sram upon system reset.
  * @rmtoll
  *  OPTR           SRAM_RST           LL_FLASH_OB_GetSystemRstSRAMErase
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_ERASED_SRAM_SYS_RST
  *         @arg @ref LL_FLASH_OB_NOT_ERASED_SRAM_SYS_RST
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetSystemRstSRAMErase(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPTR, FLASH_OPTR_SRAM_RST));
}

/**
  * @brief  Set the flash independent watchdog selection.
  * @rmtoll
  *  OPTR           IWDG_SW           LL_FLASH_OB_SetIWDGSelection
  * @param  FLASH instance.
  * @param  hw_sw_selection
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_IWDG_HW
  *         @arg @ref LL_FLASH_OB_IWDG_SW
  */
__STATIC_INLINE void LL_FLASH_OB_SetIWDGSelection(FLASH_TypeDef *flashx, uint32_t hw_sw_selection)
{
  MODIFY_REG(flashx->OPTR, FLASH_OPTR_IWDG_SW, hw_sw_selection);
}

/**
  * @brief  Get the flash independent watchdog selection.
  * @rmtoll
  *  OPTR           IWDG_SW           LL_FLASH_OB_GetIWDGSelection
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_IWDG_HW
  *         @arg @ref LL_FLASH_OB_IWDG_SW
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetIWDGSelection(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPTR, FLASH_OPTR_IWDG_SW));
}

/**
  * @brief  Freeze the flash independent watchdog counter in stop mode.
  * @rmtoll
  *  OPTR           IWDG_STOP           LL_FLASH_OB_FreezeIWDGStopMode
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_FreezeIWDGStopMode(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->OPTR, FLASH_OPTR_IWDG_STOP);
}

/**
  * @brief  Unfreeze the flash independent watchdog counter in stop mode.
  * @rmtoll
  *  OPTR           IWDG_STOP           LL_FLASH_OB_UnfreezeIWDGStopMode
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_UnfreezeIWDGStopMode(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->OPTR, FLASH_OPTR_IWDG_STOP);
}

/**
  * @brief  Check the flash independent watchdog counter in stop mode is frozen.
  * @rmtoll
  *  OPTR           IWDG_STOP           LL_FLASH_OB_IsFrozenIWDGStopMode
  * @param  FLASH instance.
  * @retval State of flash option bytes IWDG counter in stop mode (1 frozen / 0 not frozen).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsFrozenIWDGStopMode(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->OPTR, FLASH_OPTR_IWDG_STOP) == (FLASH_OPTR_IWDG_STOP)) ? 0UL : 1UL);
}

/**
  * @brief  Freeze the flash independent watchdog counter in standby mode.
  * @rmtoll
  *  OPTR           IWDG_STDBY           LL_FLASH_OB_FreezeIWDGStandbyMode
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_FreezeIWDGStandbyMode(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->OPTR, FLASH_OPTR_IWDG_STDBY);
}

/**
  * @brief  Unfreeze the flash independent watchdog counter in standby mode.
  * @rmtoll
  *  OPTR           IWDG_STDBY           LL_FLASH_OB_UnfreezeIWDGStandbyMode
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_UnfreezeIWDGStandbyMode(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->OPTR, FLASH_OPTR_IWDG_STDBY);
}

/**
  * @brief  Check the flash independent watchdog counter in standby mode is frozen.
  * @rmtoll
  *  OPTR           IWDG_STDBY           LL_FLASH_OB_IsFrozenIWDGStandbyMode
  * @param  FLASH instance.
  * @retval State of flash option bytes IWDG counter in standby mode (1 frozen / 0 not frozen).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsFrozenIWDGStandbyMode(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->OPTR, FLASH_OPTR_IWDG_STDBY) == (FLASH_OPTR_IWDG_STDBY)) ? 0UL : 1UL);
}

/**
  * @brief  Set the flash window watchdog selection.
  * @rmtoll
  *  OPTR           WWDG_SW           LL_FLASH_OB_SetWWDGSelection
  * @param  FLASH instance.
  * @param  hw_sw_selection
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_WWDG_HW
  *         @arg @ref LL_FLASH_OB_WWDG_SW
  */
__STATIC_INLINE void LL_FLASH_OB_SetWWDGSelection(FLASH_TypeDef *flashx, uint32_t hw_sw_selection)
{
  MODIFY_REG(flashx->OPTR, FLASH_OPTR_WWDG_SW, hw_sw_selection);
}

/**
  * @brief  Get the flash window watchdog selection.
  * @rmtoll
  *  OPTR           WWDG_SW           LL_FLASH_OB_GetWWDGSelection
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_WWDG_HW
  *         @arg @ref LL_FLASH_OB_WWDG_SW
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetWWDGSelection(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPTR, FLASH_OPTR_WWDG_SW));
}

/**
  * @brief  Set the flash swap banks.
  * @rmtoll
  *  OPTR           SWAP_BANK           LL_FLASH_OB_SetSwapBanks
  * @param  FLASH instance.
  * @param  swap_bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BANK_NOT_SWAPPED
  *         @arg @ref LL_FLASH_OB_BANK_SWAPPED
  */
__STATIC_INLINE void LL_FLASH_OB_SetSwapBanks(FLASH_TypeDef *flashx, uint32_t swap_bank)
{
  MODIFY_REG(flashx->OPTR, FLASH_OPTR_SWAP_BANK, swap_bank);
}

/**
  * @brief  Get the flash swap banks.
  * @rmtoll
  *  OPTR          SWAP_BANK        LL_FLASH_OB_GetSwapBanks
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BANK_NOT_SWAPPED
  *         @arg @ref LL_FLASH_OB_BANK_SWAPPED
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetSwapBanks(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPTR, FLASH_OPTR_SWAP_BANK));
}

/**
  * @brief  Set the flash single or dual bank.
  * @rmtoll
  *  OPTR           DUALBANK           LL_FLASH_OB_SetBank
  * @param  FLASH instance.
  * @param  single_dual_bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_SINGLE_BANK
  *         @arg @ref LL_FLASH_OB_DUAL_BANK
  */
__STATIC_INLINE void LL_FLASH_OB_SetBank(FLASH_TypeDef *flashx, uint32_t single_dual_bank)
{
  MODIFY_REG(flashx->OPTR, FLASH_OPTR_DUALBANK, single_dual_bank);
}

/**
  * @brief  Get the flash single or dual bank.
  * @rmtoll
  *  OPTR           DUALBANK           LL_FLASH_OB_GetBank
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_SINGLE_BANK
  *         @arg @ref LL_FLASH_OB_DUAL_BANK
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetBank(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPTR, FLASH_OPTR_DUALBANK));
}

/**
  * @brief  Enable the flash backup ram ECC.
  * @rmtoll
  *  OPTR           BKPRAM_ECC           LL_FLASH_OB_EnableECCBKPRAM
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_EnableECCBKPRAM(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->OPTR, FLASH_OPTR_BKPRAM_ECC);
}

/**
  * @brief  Disable the flash backup ram ECC.
  * @rmtoll
  *  OPTR           BKPRAM_ECC           LL_FLASH_OB_DisableECCBKPRAM
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_DisableECCBKPRAM(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->OPTR, FLASH_OPTR_BKPRAM_ECC);
}

/**
  * @brief  Check if flash backup rAM ECC is enabled or disabled.
  * @rmtoll
  *  OPTR           BKPRAM_ECC           LL_FLASH_OB_IsEnabledECCBKPRAM
  * @param  FLASH instance.
  * @retval State of flash option bytes ECCBKPRAM (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledECCBKPRAM(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->OPTR, FLASH_OPTR_BKPRAM_ECC) == (FLASH_OPTR_BKPRAM_ECC)) ? 0UL : 1UL);
}

#if defined (SRAM3_BASE)
/**
  * @brief  Enable the flash sram3 ECC.
  * @rmtoll
  *  OPTR           SRAM3_ECC           LL_FLASH_OB_EnableECCSRAM3
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_EnableECCSRAM3(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->OPTR, FLASH_OPTR_SRAM3_ECC);
}

/**
  * @brief  Disable the flash sram3 ECC.
  * @rmtoll
  *  OPTR           SRAM3_ECC           LL_FLASH_OB_DisableECCSRAM3
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_DisableECCSRAM3(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->OPTR, FLASH_OPTR_SRAM3_ECC);
}

/**
  * @brief  Check if the flash sram3 ECC is enabled or disabled.
  * @rmtoll
  *  OPTR           SRAM3_ECC           LL_FLASH_OB_IsEnabledECCSRAM3
  * @param  FLASH instance.
  * @retval State of flash option bytes ECCSRAM3 (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledECCSRAM3(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->OPTR, FLASH_OPTR_SRAM3_ECC) == (FLASH_OPTR_SRAM3_ECC)) ? 0UL : 1UL);
}
#endif /* SRAM3_BASE */

/**
  * @brief  Enable the flash sram2 ECC.
  * @rmtoll
  *  OPTR           SRAM2_ECC           LL_FLASH_OB_EnableECCSRAM2
  * @param  FLASH instance.

  */
__STATIC_INLINE void LL_FLASH_OB_EnableECCSRAM2(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->OPTR, FLASH_OPTR_SRAM2_ECC);
}

/**
  * @brief  Disable the flash sram2 ECC.
  * @rmtoll
  *  OPTR           SRAM2_ECC           LL_FLASH_OB_DisableECCSRAM2
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_DisableECCSRAM2(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->OPTR, FLASH_OPTR_SRAM2_ECC);
}

/**
  * @brief  Check if the flash sram2 ECC is enabled or disabled.
  * @rmtoll
  *  OPTR           SRAM2_ECC           LL_FLASH_OB_IsEnabledECCSRAM2
  * @param  FLASH instance.
  * @retval State of flash option bytes ECCSRAM2 (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledECCSRAM2(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->OPTR, FLASH_OPTR_SRAM2_ECC) == (FLASH_OPTR_SRAM2_ECC)) ? 0UL : 1UL);
}

/**
  * @brief  Set the flash sram2 erase upon system reset.
  * @rmtoll
  *  OPTR           SRAM2_RST           LL_FLASH_OB_SetSystemRstSRAM2Erase
  * @param  FLASH instance.
  * @param  erase_sram2
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_ERASED_SRAM2_SYS_RST
  *         @arg @ref LL_FLASH_OB_NOT_ERASED_SRAM2_SYS_RST
  */
__STATIC_INLINE void LL_FLASH_OB_SetSystemRstSRAM2Erase(FLASH_TypeDef *flashx, uint32_t erase_sram2)
{
  MODIFY_REG(flashx->OPTR, FLASH_OPTR_SRAM2_RST, erase_sram2);
}

/**
  * @brief  Get the flash sram2 erase upon system reset.
  * @rmtoll
  *  OPTR           SRAM2_RST           LL_FLASH_OB_GetSystemRstSRAM2Erase
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_ERASED_SRAM2_SYS_RST
  *         @arg @ref LL_FLASH_OB_NOT_ERASED_SRAM2_SYS_RST
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetSystemRstSRAM2Erase(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPTR, FLASH_OPTR_SRAM2_RST));
}

/**
  * @brief  Set the flash software boot0.
  * @rmtoll
  *  OPTR           nSWBOOT0           LL_FLASH_OB_SetSWBoot0
  * @param  FLASH instance.
  * @param  sw_boot0
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BOOT0_NBOOTBIT
  *         @arg @ref LL_FLASH_OB_BOOT0_BOOTPIN
  */
__STATIC_INLINE void LL_FLASH_OB_SetSWBoot0(FLASH_TypeDef *flashx, uint32_t sw_boot0)
{
  MODIFY_REG(flashx->OPTR, FLASH_OPTR_nSWBOOT0, sw_boot0);
}

/**
  * @brief  Get the flash software boot0.
  * @rmtoll
  *  OPTR           NBOOT0           LL_FLASH_OB_GetSWBoot0
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BOOT0_NBOOTBIT
  *         @arg @ref LL_FLASH_OB_BOOT0_BOOTPIN
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetSWBoot0(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPTR, FLASH_OPTR_nSWBOOT0));
}

/**
  * @brief  Set the flash NBOOT0 option bit.
  * @rmtoll
  *  OPTR           NBOOT0           LL_FLASH_OB_SetNBoot0
  * @param  FLASH instance.
  * @param  nboot0
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BOOT0_LOW
  *         @arg @ref LL_FLASH_OB_BOOT0_HIGH
  */
__STATIC_INLINE void LL_FLASH_OB_SetNBoot0(FLASH_TypeDef *flashx, uint32_t nboot0)
{
  MODIFY_REG(flashx->OPTR, FLASH_OPTR_nBOOT0, nboot0);
}

/**
  * @brief  Get the flash NBOOT0 option bit.
  * @rmtoll
  *  OPTR           NBOOT0           LL_FLASH_OB_GetNBoot0
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BOOT0_LOW
  *         @arg @ref LL_FLASH_OB_BOOT0_HIGH
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetNBoot0(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPTR, FLASH_OPTR_nBOOT0));
}

/**
  * @brief  Set the flash NBOOT0 option bit.
  * @rmtoll
  *  OPTR           BOOT0            LL_FLASH_OB_SetBoot0
  * @param  FLASH instance.
  * @param  boot0
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BOOT0_LOW
  *         @arg @ref LL_FLASH_OB_BOOT0_HIGH
  *         @arg @ref LL_FLASH_OB_BOOT0_BOOTPIN
  */
__STATIC_INLINE void LL_FLASH_OB_SetBoot0(FLASH_TypeDef *flashx, uint32_t boot0)
{
  MODIFY_REG(flashx->OPTR, (FLASH_OPTR_nBOOT0 | FLASH_OPTR_nSWBOOT0), boot0);
}

/**
  * @brief  Get the flash NBOOT0 option bit.
  * @rmtoll
  *  OPTR           BOOT0            LL_FLASH_OB_GetBoot0
  * @param  FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BOOT0_LOW
  *         @arg @ref LL_FLASH_OB_BOOT0_HIGH
  *         @arg @ref LL_FLASH_OB_BOOT0_BOOTPIN
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetBoot0(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->OPTR, (FLASH_OPTR_nBOOT0 | FLASH_OPTR_nSWBOOT0)));
}

/**
  * @brief  Enable the flash PA15 pull-up.
  * @rmtoll
  *  OPTR           PA15_PUPEN           LL_FLASH_OB_EnablePA15PullUp
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_EnablePA15PullUp(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->OPTR, FLASH_OPTR_PA15_PUPEN);
}

/**
  * @brief  Disable the flash PA15 pull-up.
  * @rmtoll
  *  OPTR          PA15_PUPEN        LL_FLASH_OB_DisablePA15PullUp
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_DisablePA15PullUp(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->OPTR, FLASH_OPTR_PA15_PUPEN);
}

/**
  * @brief  Check if the flash PA15 pull-up is enabled or disabled.
  * @rmtoll
  *  OPTR          PA15_PUPEN        LL_FLASH_OB_IsEnabledPA15PullUp
  * @param  FLASH instance.
  * @retval State of flash option bytes PA15 pull-up (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledPA15PullUp(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->OPTR, FLASH_OPTR_PA15_PUPEN) == ((FLASH_OPTR_PA15_PUPEN))) ? 1UL : 0UL);
}

/**
  * @brief  Enable the flash high speed IO at low VDD voltage.
  * @rmtoll
  *  OPTR          IO_VDD_HSLV          LL_FLASH_OB_EnableVddIOHSLV
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_EnableVddIOHSLV(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->OPTR, FLASH_OPTR_IO_VDD_HSLV);
}

/**
  * @brief  Disable the flash high speed IO at low VDD voltage.
  * @rmtoll
  *  OPTR          IO_VDD_HSLV          LL_FLASH_OB_DisableVddIOHSLV
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_DisableVddIOHSLV(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->OPTR, FLASH_OPTR_IO_VDD_HSLV);
}

/**
  * @brief  Check if the flash high speed IO at low VDD voltage is enabled or disabled.
  * @rmtoll
  *  OPTR          IO_VDD_HSLV          LL_FLASH_OB_IsEnabledVddIOHSLV
  * @param  FLASH instance.
  * @retval State of flash option bytes high speed IO at low VDD voltage (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledVddIOHSLV(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->OPTR, FLASH_OPTR_IO_VDD_HSLV) == ((FLASH_OPTR_IO_VDD_HSLV))) ? 1UL : 0UL);
}

/**
  * @brief  Enable the flash high speed IO at low VDDIO2 voltage.
  * @rmtoll
  *  OPTR          IO_VDDIO2_HSLV          LL_FLASH_OB_EnableVddIO2HSLV
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_EnableVddIO2HSLV(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->OPTR, FLASH_OPTR_IO_VDDIO2_HSLV);
}

/**
  * @brief  Disable the flash high speed IO at low VDDIO2 voltage.
  * @rmtoll
  *  OPTR          IO_VDDIO2_HSLV          LL_FLASH_OB_DisableVddIO2HSLV
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_DisableVddIO2HSLV(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->OPTR, FLASH_OPTR_IO_VDDIO2_HSLV);
}

/**
  * @brief  Check if the flash high speed IO at low VDDIO2 voltage is enabled or disabled.
  * @rmtoll
  *  OPTR          IO_VDDIO2_HSLV          LL_FLASH_OB_IsEnabledVddIO2HSLV
  * @param  FLASH instance.
  * @retval State of flash option bytes high speed IO at low VDDIO2 voltage (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledVddIO2HSLV(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->OPTR, FLASH_OPTR_IO_VDDIO2_HSLV) == ((FLASH_OPTR_IO_VDDIO2_HSLV))) ? 1UL : 0UL);
}

/**
  * @brief  Enable the flash global TrustZone security.
  * @rmtoll
  *  OPTR          TZEN          LL_FLASH_OB_EnableTrustZone
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_EnableTrustZone(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->OPTR, FLASH_OPTR_TZEN);
}

/**
  * @brief  Disable the flash global TrustZone security.
  * @rmtoll
  *  OPTR          TZEN          LL_FLASH_OB_DisableTrustZone
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_DisableTrustZone(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->OPTR, FLASH_OPTR_TZEN);
}

/**
  * @brief  Check if the flash global TrustZone security is enabled or disabled.
  * @rmtoll
  *  OPTR          TZEN          LL_FLASH_OB_IsEnabledTrustZone
  * @param  FLASH instance.
  * @retval State of flash option bytes trustzone (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledTrustZone(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->OPTR, FLASH_OPTR_TZEN) == ((FLASH_OPTR_TZEN))) ? 1UL : 0UL);
}

/**
  * @brief  Set the flash non-secure boot base address 0.
  * @rmtoll
  *  NSBOOTADD0R          NSBOOTADD0          LL_FLASH_OB_SetNSecBootAddr0
  * @param  FLASH instance.
  * @param  boot_addr
  *         This parameter can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE void LL_FLASH_OB_SetNSecBootAddr0(FLASH_TypeDef *flashx, uint32_t boot_addr)
{
  MODIFY_REG(flashx->NSBOOTADD0R, FLASH_NSBOOTADD0R_NSBOOTADD0, boot_addr);
}

/**
  * @brief  Set the flash non-secure boot base address 0.
  * @rmtoll
  *  NSBOOTADD0R          NSBOOTADD0          LL_FLASH_OB_GetNSecBootAddr0
  * @param  FLASH instance.
  * @retval Returned value can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetNSecBootAddr0(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->NSBOOTADD0R, FLASH_NSBOOTADD0R_NSBOOTADD0));
}

/**
  * @brief  Set the flash non-secure boot base address 1.
  * @rmtoll
  *  NSBOOTADD1R          NSBOOTADD1          LL_FLASH_OB_SetNSecBootAddr1
  * @param  FLASH instance.
  * @param  boot_addr
  *         This parameter can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE void LL_FLASH_OB_SetNSecBootAddr1(FLASH_TypeDef *flashx, uint32_t boot_addr)
{
  MODIFY_REG(flashx->NSBOOTADD1R, FLASH_NSBOOTADD1R_NSBOOTADD1, boot_addr);
}

/**
  * @brief  Set the flash non-secure boot base address 1.
  * @rmtoll
  *  NSBOOTADD1R          NSBOOTADD1          LL_FLASH_OB_GetNSecBootAddr1
  * @param  FLASH instance.
  * @retval Returned value can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetNSecBootAddr1(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->NSBOOTADD1R, FLASH_NSBOOTADD1R_NSBOOTADD1));
}

/**
  * @brief  Set the flash non-secure boot base address.
  * @rmtoll NSBOOTADD0R/NSBOOTADD1R          NSBOOTADD0/NSBOOTADD1          LL_FLASH_OB_SetNSecBootAddr
  * @param  FLASH instance.
  * @param  addr_idx
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_ADDR_0
  *         @arg @ref LL_FLASH_OB_ADDR_1
  * @param  boot_addr
  *         This parameter can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE void LL_FLASH_OB_SetNSecBootAddr(FLASH_TypeDef *flashx, uint32_t addr_idx, uint32_t boot_addr)
{
  __IO uint32_t *reg_addr = &flashx->NSBOOTADD0R + addr_idx;
  MODIFY_REG(*reg_addr, FLASH_NSBOOTADD0R_NSBOOTADD0, boot_addr);
}

/**
  * @brief  Set the flash non-secure boot base address.
  * @rmtoll NSBOOTADD0R/NSBOOTADD1R          NSBOOTADD0/NSBOOTADD1          LL_FLASH_OB_GetNSecBootAddr
  * @param  FLASH instance.
  * @param  addr_idx
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_ADDR_0
  *         @arg @ref LL_FLASH_OB_ADDR_1
  * @retval Returned value can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetNSecBootAddr(const FLASH_TypeDef *flashx, uint32_t addr_idx)
{
  const __IO uint32_t *reg_addr = &flashx->NSBOOTADD0R + addr_idx;
  return (READ_BIT(*reg_addr, FLASH_NSBOOTADD0R_NSBOOTADD0));
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Lock the flash secure boot address 0.
  * @rmtoll
  *  SECBOOTADD0R          BOOT_LOCK          LL_FLASH_OB_LockBootConfiguration
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_LockBootConfiguration(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->SECBOOTADD0R, FLASH_SECBOOTADD0R_BOOT_LOCK);
}

/**
  * @brief  Unlock the flash secure boot address 0.
  * @rmtoll
  *  SECBOOTADD0R          BOOT_LOCK          LL_FLASH_OB_UnlockBootConfiguration
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_UnlockBootConfiguration(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->SECBOOTADD0R, FLASH_SECBOOTADD0R_BOOT_LOCK);
}

/**
  * @brief  Check the flash secure boot address 0 lock state.
  * @rmtoll
  *  SECBOOTADD0R          BOOT_LOCK          LL_FLASH_OB_IsLockedBootConfiguration
  * @param  FLASH instance.
  * @retval State of flash option bytes secure boot lock (1 locked / 0 unlocked).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsLockedBootConfiguration(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->SECBOOTADD0R, FLASH_SECBOOTADD0R_BOOT_LOCK) == ((FLASH_SECBOOTADD0R_BOOT_LOCK))) ?
          1UL : 0UL);
}

/**
  * @brief  Set the flash secure boot base address 0.
  * @rmtoll
  *  SECBOOTADD0R          SECBOOTADD0          LL_FLASH_OB_SetSecBootAddr0
  * @param  FLASH instance.
  * @param  boot_addr
  *         This parameter can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE void LL_FLASH_OB_SetSecBootAddr0(FLASH_TypeDef *flashx, uint32_t boot_addr)
{
  MODIFY_REG(flashx->SECBOOTADD0R, FLASH_SECBOOTADD0R_SECBOOTADD0, boot_addr);
}

/**
  * @brief  Get the flash secure boot base address 0.
  * @rmtoll
  *  SECBOOTADD0R          SECBOOTADD0          LL_FLASH_OB_GetSecBootAddr0
  * @param  FLASH instance.
  * @retval Returned value can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetSecBootAddr0(const FLASH_TypeDef *flashx)
{
  return (READ_BIT(flashx->SECBOOTADD0R, FLASH_SECBOOTADD0R_SECBOOTADD0));
}

/**
  * @brief  Set the flash start page of the secure watermark area by bank.
  * @rmtoll SECWM1R1/SECWM2R1          SECWM1_PSTRT/SECWM2_PSTRT          LL_FLASH_OB_BANK_SetWMAreaStartPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  start_page
  *         This parameter can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_SetWMAreaStartPage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t start_page)
{
  __IO uint32_t *reg_addr = &flashx->SECWM1R1 + bank;
  MODIFY_REG(*reg_addr, FLASH_SECWM1R1_SECWM1_PSTRT, start_page);
}

/**
  * @brief  Get the flash start page of the secure watermark area by bank.
  * @rmtoll SECWM1R1/SECWM2R1          SECWM1_PSTRT/SECWM2_PSTRT          LL_FLASH_OB_BANK_GetWMAreaStartPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_BANK_GetWMAreaStartPage(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = &flashx->SECWM1R1 + bank;
  return (READ_BIT(*reg_addr, FLASH_SECWM1R1_SECWM1_PSTRT));
}

/**
  * @brief  Set the flash end page of the secure watermark area by bank.
  * @rmtoll SECWM1R1/SECWM2R1          SECWM1_PEND/SECWM2_PEND          LL_FLASH_OB_BANK_SetWMAreaEndPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  end_page
  *         This parameter can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_SetWMAreaEndPage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t end_page)
{
  __IO uint32_t *reg_addr = &flashx->SECWM1R1 + bank;
  MODIFY_REG(*reg_addr, FLASH_SECWM1R1_SECWM1_PEND, (end_page << FLASH_SECWM1R1_SECWM1_PEND_Pos));
}

/**
  * @brief  Get the flash end page of the secure watermark area by bank.
  * @rmtoll SECWM1R1          SECWM1_PEND/SECWM2_PEND          LL_FLASH_OB_BANK_GetWMAreaEndPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_BANK_GetWMAreaEndPage(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = &flashx->SECWM1R1 + bank;
  return (READ_BIT(*reg_addr, FLASH_SECWM1R1_SECWM1_PEND));
}

/**
  * @brief  Configuration the flash secure watermark area by bank.
  * @rmtoll SECWM1R1/SECWM2R1   SECWM1_PSTRT/SECWM2_PSTRT/SECWM1_PEND/SECWM2_PEND   LL_FLASH_OB_BANK_ConfigSecureWMArea
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  start_page
  *         This parameter can be a value between 0x00U and the maximum number of pages per bank.
  * @param  end_page
  *         This parameter can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_ConfigSecureWMArea(FLASH_TypeDef *flashx,
                                                         uint32_t bank,
                                                         uint32_t start_page,
                                                         uint32_t end_page)
{
  __IO uint32_t *reg_addr = &flashx->SECWM1R1 + bank;
  MODIFY_REG(*reg_addr, (FLASH_SECWM1R1_SECWM1_PSTRT | FLASH_SECWM1R1_SECWM1_PEND),
             (start_page | (end_page << FLASH_SECWM1R1_SECWM1_PEND_Pos)));
}

/**
  * @brief  Set the flash end page of the hide protection area by bank.
  * @rmtoll SECWM1R2/SECWM2R2          HDP1_PEND/HDP2_PEND          LL_FLASH_OB_BANK_SetHDPAreaEndPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  end_page
  *         This parameter can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_SetHDPAreaEndPage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t end_page)
{
  __IO uint32_t *reg_addr = &flashx->SECWM1R2 + bank;
  MODIFY_REG(*reg_addr, FLASH_SECWM1R2_HDP1_PEND, (end_page << FLASH_SECWM1R2_HDP1_PEND_Pos));
}

/**
  * @brief  Get the flash end page of the hide protection area by bank.
  * @rmtoll SECWM1R2/SECWM2R2          HDP1_PEND/HDP2_PEND          LL_FLASH_OB_BANK_GetHDPAreaEndPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_BANK_GetHDPAreaEndPage(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = &flashx->SECWM1R2 + bank;
  return (READ_BIT(*reg_addr, FLASH_SECWM1R2_HDP1_PEND));
}

/**
  * @brief  Enable the flash hide protection area by bank.
  * @rmtoll SECWM1R2/SECWM2R2          HDP1EN/HDP2EN          LL_FLASH_OB_BANK_EnableHDPArea
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_EnableHDPArea(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = &flashx->SECWM1R2 + bank;
  SET_BIT(*reg_addr, FLASH_SECWM1R2_HDP1EN);
}

/**
  * @brief  Disable the flash hide protection area by bank.
  * @rmtoll SECWM1R2/SECWM2R2          HDP1EN/HDP2EN          LL_FLASH_OB_BANK_DisableHDPArea
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_DisableHDPArea(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = &flashx->SECWM1R2 + bank;
  CLEAR_BIT(*reg_addr, FLASH_SECWM1R2_HDP1EN);
}

/**
  * @brief  Check if the flash hide protection area is enabled or disabled by bank.
  * @rmtoll SECWM1R2/SECWM2R2          HDP1EN/HDP2EN          LL_FLASH_OB_BANK_IsEnabledHDPArea
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash option bytes hide protection area (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_BANK_IsEnabledHDPArea(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = &flashx->SECWM1R2 + bank;
  return ((READ_BIT(*reg_addr, FLASH_SECWM1R2_HDP1EN) == (FLASH_SECWM1R2_HDP1EN)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Set the flash start page of the write protection area A by bank.
  * @rmtoll WRP1AR/WRP2AR          WRP1A_PSTRT/WRP2A_PSTRT          LL_FLASH_OB_BANK_SetAreaAWRPStartPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  start_page
  *         This parameter can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_SetAreaAWRPStartPage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t start_page)
{
  __IO uint32_t *reg_addr = &flashx->WRP1AR + bank;
  MODIFY_REG(*reg_addr, FLASH_WRP1AR_WRP1A_PSTRT, start_page);
}

/**
  * @brief  Get the flash start page of the write protection area A by bank.
  * @rmtoll WRP1AR/WRP2AR          WRP1A_PSTRT/WRP2A_PSTRT          LL_FLASH_OB_BANK_GetAreaAWRPStartPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_BANK_GetAreaAWRPStartPage(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = &flashx->WRP1AR + bank;
  return (READ_BIT(*reg_addr, FLASH_WRP1AR_WRP1A_PSTRT));
}

/**
  * @brief  Set the flash end page of the write protection area A by bank.
  * @rmtoll WRP1AR/WRP2AR          WRP1A_PEND/WRP2A_PEND          LL_FLASH_OB_BANK_SetAreaAWRPEndPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  end_page
  *         This parameter can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_SetAreaAWRPEndPage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t end_page)
{
  __IO uint32_t *reg_addr = &flashx->WRP1AR + bank;
  MODIFY_REG(*reg_addr, FLASH_WRP1AR_WRP1A_PEND, (end_page << FLASH_WRP1AR_WRP1A_PEND_Pos));
}

/**
  * @brief  Get the flash end page of the write protection area A by bank.
  * @rmtoll WRP1AR/WRP2AR          WRP1A_PEND/WRP2A_PEND          LL_FLASH_OB_BANK_GetAreaAWRPEndPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_BANK_GetAreaAWRPEndPage(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = &flashx->WRP1AR + bank;
  return (READ_BIT(*reg_addr, FLASH_WRP1AR_WRP1A_PEND));
}

/**
  * @brief  Lock the flash write protection area A by bank.
  * @rmtoll WRP1AR/WRP2AR          UNLOCK          LL_FLASH_OB_BANK_LockAreaAWRP
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_LockAreaAWRP(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = &flashx->WRP1AR + bank;
  CLEAR_BIT(*reg_addr, FLASH_WRP1AR_UNLOCK);
}

/**
  * @brief  Unlock the flash write protection area A by bank.
  * @rmtoll WRP1AR/WRP2AR          UNLOCK          LL_FLASH_OB_BANK_UnlockAreaAWRP
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_UnlockAreaAWRP(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = &flashx->WRP1AR + bank;
  SET_BIT(*reg_addr, FLASH_WRP1AR_UNLOCK);
}

/**
  * @brief  Check the flash write protection area A lock state by bank.
  * @rmtoll WRP1AR/WRP2AR          UNLOCK          LL_FLASH_OB_BANK_IsLockedAreaAWRP
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash option bytes write protection area A configuration lock (1 locked / 0 unlocked).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_BANK_IsLockedAreaAWRP(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = &flashx->WRP1AR + bank;
  return ((READ_BIT(*reg_addr, FLASH_WRP1AR_UNLOCK) == ((FLASH_WRP1AR_UNLOCK))) ? 0UL : 1UL);
}

/**
  * @brief  Set the flash start page of the write protection area B by bank.
  * @rmtoll WRP1BR/WRP2BR          WRP1B_PSTRT/WRP2B_PSTRT          LL_FLASH_OB_BANK_SetAreaBWRPStartPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  start_page
  *         This parameter can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_SetAreaBWRPStartPage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t start_page)
{
  __IO uint32_t *reg_addr = &flashx->WRP1BR + bank;
  MODIFY_REG(*reg_addr, FLASH_WRP1BR_WRP1B_PSTRT, start_page);
}

/**
  * @brief  Get the flash start page of the write protection area B by bank.
  * @rmtoll WRP1BR/WRP2BR          WRP1B_PSTRT/WRP2B_PSTRT          LL_FLASH_OB_BANK_GetAreaBWRPStartPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_BANK_GetAreaBWRPStartPage(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = &flashx->WRP1BR + bank;
  return (READ_BIT(*reg_addr, FLASH_WRP1BR_WRP1B_PSTRT));
}

/**
  * @brief  Set the flash end page of the write protection area B by bank.
  * @rmtoll WRP1BR/WRP2BR          WRP1B_PEND/WRP2B_PEND          LL_FLASH_OB_BANK_SetAreaBWRPEndPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  end_page
  *         This parameter can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_SetAreaBWRPEndPage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t end_page)
{
  __IO uint32_t *reg_addr = &flashx->WRP1BR + bank;
  MODIFY_REG(*reg_addr, FLASH_WRP1BR_WRP1B_PEND, (end_page << FLASH_WRP1BR_WRP1B_PEND_Pos));
}

/**
  * @brief  Get the flash end page of the write protection area B by bank.
  * @rmtoll WRP1BR/WRP2BR          WRP1B_PEND/WRP2B_PEND          LL_FLASH_OB_BANK_GetAreaBWRPEndPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_BANK_GetAreaBWRPEndPage(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = &flashx->WRP1BR + bank;
  return (READ_BIT(*reg_addr, FLASH_WRP1BR_WRP1B_PEND));
}

/**
  * @brief  Lock the flash write protection area B by bank.
  * @rmtoll WRP1BR/WRP2BR          UNLOCK          LL_FLASH_OB_BANK_LockAreaBWRP
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_LockAreaBWRP(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = &flashx->WRP1BR + bank;
  CLEAR_BIT(*reg_addr, FLASH_WRP1BR_UNLOCK);
}

/**
  * @brief  Unlock the flash write protection area B by bank.
  * @rmtoll WRP1BR/WRP2BR          UNLOCK          LL_FLASH_OB_BANK_UnlockAreaBWRP
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_UnlockAreaBWRP(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = &flashx->WRP1BR + bank;
  SET_BIT(*reg_addr, FLASH_WRP1BR_UNLOCK);
}

/**
  * @brief  Check the flash write protection area B lock state by bank.
  * @rmtoll WRP1BR/WRP2BR          UNLOCK          LL_FLASH_OB_BANK_IsLockedAreaBWRP
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash option bytes write protection area B configuration lock (1 locked / 0 unlocked).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_BANK_IsLockedAreaBWRP(const FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = &flashx->WRP1BR + bank;
  return ((READ_BIT(*reg_addr, FLASH_WRP1BR_UNLOCK) == ((FLASH_WRP1BR_UNLOCK))) ? 0UL : 1UL);
}

/**
  * @brief  Configuration the flash write protection area by bank.
  * @rmtoll
  *  WRP1AR          WRP1A_PSTRT/WRP1A_PEND         LL_FLASH_OB_BANK_ConfigAreaWRP \n
  *  WRP2AR          WRP2A_PSTRT/WRP2A_PEND         LL_FLASH_OB_BANK_ConfigAreaWRP \n
  *  WRP1BR          WRP1B_PSTRT/WRP1B_PEND         LL_FLASH_OB_BANK_ConfigAreaWRP \n
  *  WRP2BR          WRP2B_PSTRT/WRP2B_PEND         LL_FLASH_OB_BANK_ConfigAreaWRP
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  area
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BANK_AREA_A
  *         @arg @ref LL_FLASH_OB_BANK_AREA_B
  * @param  start_page
  *         This parameter can be a value between 0x00U and the maximum number of pages per bank.
  * @param  end_page
  *         This parameter can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_ConfigAreaWRP(FLASH_TypeDef *flashx,
                                                    uint32_t bank,
                                                    uint32_t area,
                                                    uint32_t start_page,
                                                    uint32_t end_page)
{
  __IO uint32_t *reg_addr = &flashx->WRP1AR + bank + area;
  MODIFY_REG(*reg_addr, (FLASH_WRP1AR_WRP1A_PSTRT | FLASH_WRP1AR_WRP1A_PEND),
             (start_page | (end_page << FLASH_WRP1AR_WRP1A_PEND_Pos)));
}

/**
  * @brief  Get the flash start page of the write protection area per bank area.
  * @rmtoll
  *  WRP1AR          WRP1A_PSTRT         LL_FLASH_OB_BANK_GetAreaWRPStartPage \n
  *  WRP2AR          WRP2A_PSTRT         LL_FLASH_OB_BANK_GetAreaWRPStartPage \n
  *  WRP1BR          WRP1B_PSTRT         LL_FLASH_OB_BANK_GetAreaWRPStartPage \n
  *  WRP2BR          WRP2B_PSTRT         LL_FLASH_OB_BANK_GetAreaWRPStartPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  area
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BANK_AREA_A
  *         @arg @ref LL_FLASH_OB_BANK_AREA_B
  * @retval Returned value can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_BANK_GetAreaWRPStartPage(const FLASH_TypeDef *flashx, uint32_t bank, uint32_t area)
{
  const __IO uint32_t *reg_addr = &flashx->WRP1AR + bank + area;
  return (READ_BIT(*reg_addr, FLASH_WRP1AR_WRP1A_PSTRT));
}

/**
  * @brief  Get the flash end page of the write protection area per bank area.
  * @rmtoll
  *  WRP1AR          WRP1A_PEND         LL_FLASH_OB_BANK_GetAreaWRPEndPage \n
  *  WRP2AR          WRP2A_PEND         LL_FLASH_OB_BANK_GetAreaWRPEndPage \n
  *  WRP1BR          WRP1B_PEND         LL_FLASH_OB_BANK_GetAreaWRPEndPage \n
  *  WRP2BR          WRP2B_PEND         LL_FLASH_OB_BANK_GetAreaWRPEndPage
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  area
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BANK_AREA_A
  *         @arg @ref LL_FLASH_OB_BANK_AREA_B
  * @retval Returned value can be a value between 0x00U and the maximum number of pages per bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_BANK_GetAreaWRPEndPage(const FLASH_TypeDef *flashx, uint32_t bank, uint32_t area)
{
  const __IO uint32_t *reg_addr = &flashx->WRP1AR + bank + area;
  return (READ_BIT(*reg_addr, FLASH_WRP1AR_WRP1A_PEND));
}

/**
  * @brief  Lock the flash write protection area by bank by area.
  * @rmtoll WRP1AR/WRP2AR/WRP1BR/WRP2BR    UNLOCK    LL_FLASH_OB_BANK_LockAreaWRP
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  area
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BANK_AREA_A
  *         @arg @ref LL_FLASH_OB_BANK_AREA_B
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_LockAreaWRP(FLASH_TypeDef *flashx, uint32_t bank, uint32_t area)
{
  __IO uint32_t *reg_addr = &flashx->WRP1AR + bank + area;
  CLEAR_BIT(*reg_addr, FLASH_WRP1AR_UNLOCK);
}

/**
  * @brief  Unlock the flash write protection area by bank and area.
  * @rmtoll WRP1AR/WRP2AR/WRP1BR/WRP2BR    UNLOCK    LL_FLASH_OB_BANK_UnlockAreaWRP
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  area
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BANK_AREA_A
  *         @arg @ref LL_FLASH_OB_BANK_AREA_B
  */
__STATIC_INLINE void LL_FLASH_OB_BANK_UnlockAreaWRP(FLASH_TypeDef *flashx, uint32_t bank, uint32_t area)
{
  __IO uint32_t *reg_addr = &flashx->WRP1AR + bank + area;
  SET_BIT(*reg_addr, FLASH_WRP1AR_UNLOCK);
}

/**
  * @brief  Check the flash write protection area lock state by bank by area.
  * @rmtoll WRP1AR/WRP2AR/WRP1BR/WRP2BR    UNLOCK    LL_FLASH_OB_BANK_IsLockedAreaWRP
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  area
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BANK_AREA_A
  *         @arg @ref LL_FLASH_OB_BANK_AREA_B
  * @retval State of flash option bytes write protection area A configuration lock (1 locked / 0 unlocked).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_BANK_IsLockedAreaWRP(const FLASH_TypeDef *flashx, uint32_t bank, uint32_t area)
{
  const __IO uint32_t *reg_addr = &flashx->WRP1AR + bank + area;
  return ((READ_BIT(*reg_addr, FLASH_WRP1AR_UNLOCK) == ((FLASH_WRP1AR_UNLOCK))) ? 0UL : 1UL);
}

/**
  * @brief  Set the flash OEM1 least significant bytes key.
  * @rmtoll
  *  OEM1KEYR1          OEM1KEY          LL_FLASH_SetOEM1KeyLowBytes
  * @param  FLASH instance.
  * @param  oem1_key1
  *         This parameter can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE void LL_FLASH_SetOEM1KeyLowBytes(FLASH_TypeDef *flashx, uint32_t oem1_key1)
{
  WRITE_REG(flashx->OEM1KEYR1, oem1_key1);
}

/**
  * @brief  Set the flash OEM1 most significant bytes key.
  * @rmtoll
  *  OEM1KEYR2          OEM1KEY          LL_FLASH_SetOEM1KeyHighBytes
  * @param  FLASH instance.
  * @param  oem1_key2
  *         This parameter can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE void LL_FLASH_SetOEM1KeyHighBytes(FLASH_TypeDef *flashx, uint32_t oem1_key2)
{
  WRITE_REG(flashx->OEM1KEYR2, oem1_key2);
}

/**
  * @brief  Set the flash OEM2 least significant bytes key.
  * @rmtoll
  *  OEM2KEYR1          OEM2KEY          LL_FLASH_SetOEM2KeyLowBytes
  * @param  FLASH instance.
  * @param  oem2_key1
  *         This parameter can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE void LL_FLASH_SetOEM2KeyLowBytes(FLASH_TypeDef *flashx, uint32_t oem2_key1)
{
  WRITE_REG(flashx->OEM2KEYR1, oem2_key1);
}

/**
  * @brief  Set the flash OEM2 most significant bytes key.
  * @rmtoll
  *  OEM2KEYR2          OEM2KEY          LL_FLASH_SetOEM2KeyHighBytes
  * @param  FLASH instance.
  * @param  oem2_key2
  *         This parameter can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE void LL_FLASH_SetOEM2KeyHighBytes(FLASH_TypeDef *flashx, uint32_t oem2_key2)
{
  WRITE_REG(flashx->OEM2KEYR2, oem2_key2);
}

/**
  * @brief  Set the flash OEMx least significant bytes key.
  * @rmtoll OEM1KEYR1/OEM2KEYR1          OEM1KEY/OEM2KEY          LL_FLASH_SetOEMxKeyLowBytes
  * @param  FLASH instance.
  * @param  oem_idx
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_OEM_1
  *         @arg @ref LL_FLASH_OB_OEM_2
  * @param  oemx_key1
  *         This parameter can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE void LL_FLASH_SetOEMxKeyLowBytes(FLASH_TypeDef *flashx, uint32_t oem_idx, uint32_t oemx_key1)
{
  __IO uint32_t *reg_addr = &flashx->OEM1KEYR1 + oem_idx;
  WRITE_REG(*reg_addr, oemx_key1);
}

/**
  * @brief  Set the flash OEMx most significant bytes key.
  * @rmtoll OEM1KEYR2/OEM2KEYR2          OEM1KEY/OEM2KEY          LL_FLASH_SetOEMxKeyHighBytes
  * @param  FLASH instance.
  * @param  oem_idx
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_OEM_1
  *         @arg @ref LL_FLASH_OB_OEM_2
  * @param  oemx_key2
  *         This parameter can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE void LL_FLASH_SetOEMxKeyHighBytes(FLASH_TypeDef *flashx, uint32_t oem_idx, uint32_t oemx_key2)
{
  __IO uint32_t *reg_addr = &flashx->OEM1KEYR2 + oem_idx;
  WRITE_REG(*reg_addr, oemx_key2);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Set the flash security attribute for the bank block based.
  * @rmtoll SECBB1Rx/SECBB2Rx [x : 0 to 8]   SEC1BBi/SEC2BBi [i : 0 to 31]   LL_FLASH_BANK_SetBBSecure
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  bank_group
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_GRP1
  * @if SRAM3_BASE
  *         @arg @ref LL_FLASH_BANK_GRP2
  *         @arg @ref LL_FLASH_BANK_GRP3
  *         @arg @ref LL_FLASH_BANK_GRP4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref LL_FLASH_BANK_GRP5
  *         @arg @ref LL_FLASH_BANK_GRP6
  *         @arg @ref LL_FLASH_BANK_GRP7
  *         @arg @ref LL_FLASH_BANK_GRP8
  * @endif
  * @param  sec_attr
  *         This parameter can be a value between Min_Data=0x00000000U to Max_Data=0xFFFFFFFFU
  */
__STATIC_INLINE void LL_FLASH_BANK_SetBBSecure(FLASH_TypeDef *flashx,
                                               uint32_t bank,
                                               uint32_t bank_group,
                                               uint32_t sec_attr)
{
  __IO uint32_t *reg_addr = &flashx->SECBB1R1 + (bank * 0x2UL) + bank_group;
  WRITE_REG(*reg_addr, sec_attr);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Get the flash security attribute for the bank block based.
  * @rmtoll SECBB1Rx/SECBB2Rx [x : 0 to 8]   SEC1BBi/SEC2BBi [i : 0 to 31]   LL_FLASH_BANK_GetBBSecure
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  bank_group
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_GRP1
  * @if SRAM3_BASE
  *         @arg @ref LL_FLASH_BANK_GRP2
  *         @arg @ref LL_FLASH_BANK_GRP3
  *         @arg @ref LL_FLASH_BANK_GRP4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref LL_FLASH_BANK_GRP5
  *         @arg @ref LL_FLASH_BANK_GRP6
  *         @arg @ref LL_FLASH_BANK_GRP7
  *         @arg @ref LL_FLASH_BANK_GRP8
  * @endif
  * @retval Returned value can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE uint32_t LL_FLASH_BANK_GetBBSecure(const FLASH_TypeDef *flashx, uint32_t bank, uint32_t bank_group)
{
  const __IO uint32_t *reg_addr = &flashx->SECBB1R1 + (bank * 0x2UL) + bank_group;
  return (READ_REG(*reg_addr));
}

/**
  * @brief  Set the flash privilege attribute for the bank block based.
  * @rmtoll PRIVBB1Rx/PRIVBB2Rx [x : 0 to 8]   PRIV1BBi/PRIV2BBi [i : 0 to 31]   LL_FLASH_BANK_SetBBPrivilege
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  bank_group
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_GRP1
  * @if SRAM3_BASE
  *         @arg @ref LL_FLASH_BANK_GRP2
  *         @arg @ref LL_FLASH_BANK_GRP3
  *         @arg @ref LL_FLASH_BANK_GRP4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref LL_FLASH_BANK_GRP5
  *         @arg @ref LL_FLASH_BANK_GRP6
  *         @arg @ref LL_FLASH_BANK_GRP7
  *         @arg @ref LL_FLASH_BANK_GRP8
  * @endif
  * @param  priv_attr
  *         This parameter can be a value between Min_Data=0x00000000U to Max_Data=0xFFFFFFFFU
  */
__STATIC_INLINE void LL_FLASH_BANK_SetBBPrivilege(FLASH_TypeDef *flashx, uint32_t bank, uint32_t bank_group,
                                                  uint32_t priv_attr)
{
  __IO uint32_t *reg_addr = &flashx->PRIVBB1R1 + (bank * 0x2UL) + bank_group;
  WRITE_REG(*reg_addr, priv_attr);
}

/**
  * @brief  Get the flash privilege attribute for the bank block based.
  * @rmtoll PRIVBB1Rx/PRIVBB2Rx [x : 0 to 8]   PRIV1BBi/PRIV2BBi [i : 0 to 31]   LL_FLASH_BANK_GetBBPrivilege
  * @param  FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  bank_group
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_GRP1
  * @if SRAM3_BASE
  *         @arg @ref LL_FLASH_BANK_GRP2
  *         @arg @ref LL_FLASH_BANK_GRP3
  *         @arg @ref LL_FLASH_BANK_GRP4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref LL_FLASH_BANK_GRP5
  *         @arg @ref LL_FLASH_BANK_GRP6
  *         @arg @ref LL_FLASH_BANK_GRP7
  *         @arg @ref LL_FLASH_BANK_GRP8
  * @endif
  * @retval Returned value can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE uint32_t LL_FLASH_BANK_GetBBPrivilege(const FLASH_TypeDef *flashx, uint32_t bank, uint32_t bank_group)
{
  const __IO uint32_t *reg_addr = &flashx->PRIVBB1R1 + (bank * 0x2UL) + bank_group;
  return (READ_REG(*reg_addr));
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Disable the flash hide protection area access.
  * @rmtoll SECHDPCR          HDP1_ACCDIS/HDP2_ACCDIS          LL_FLASH_BANK_DisableHDPAreaAccess
  * @param  FLASH instance.
  * @param  hdp_bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_HDP_ACCESS_BANK_1
  *         @arg @ref LL_FLASH_HDP_ACCESS_BANK_2
  */
__STATIC_INLINE void LL_FLASH_BANK_DisableHDPAreaAccess(FLASH_TypeDef *flashx, uint32_t hdp_bank)
{
  SET_BIT(flashx->SECHDPCR, hdp_bank);
}

/**
  * @brief  Check if the flash hide protection area access is enabled or disabled.
  * @rmtoll SECHDPCR          HDP1_ACCDIS/HDP2_ACCDIS          LL_FLASH_BANK_IsEnabledHDPAreaAccess
  * @param  FLASH instance.
  * @param  hdp_bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_HDP_ACCESS_BANK_1
  *         @arg @ref LL_FLASH_HDP_ACCESS_BANK_2
  * @retval State of flash hide protection area access (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_BANK_IsEnabledHDPAreaAccess(const FLASH_TypeDef *flashx, uint32_t hdp_bank)
{
  return ((READ_BIT(flashx->SECHDPCR, hdp_bank) == hdp_bank) ? 0UL : 1UL);
}

/**
  * @brief  Enable the flash privileged protection for the secure registers.
  * @rmtoll
  *  PRIVCFGR          SPRIV          LL_FLASH_EnableSecurePrivilege
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableSecurePrivilege(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_SPRIV);
}

/**
  * @brief  Disable the flash privileged protection for the secure registers.
  * @rmtoll
  *  PRIVCFGR          SPRIV          LL_FLASH_DisableSecurePrivilege
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableSecurePrivilege(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_SPRIV);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the flash privileged protection for the secure registers is enabled or disabled.
  * @rmtoll
  *  PRIVCFGR          SPRIV          LL_FLASH_IsEnabledSecurePrivilege
  * @param  FLASH instance.
  * @retval State of flash secure privilege (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledSecurePrivilege(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_SPRIV) == (FLASH_PRIVCFGR_SPRIV)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the flash privileged protection for the non-secure registers.
  * @rmtoll
  *  PRIVCFGR          NSPRIV          LL_FLASH_EnableNSecurePrivilege
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableNSecurePrivilege(FLASH_TypeDef *flashx)
{
  SET_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_NSPRIV);
}

/**
  * @brief  Disable the flash privileged protection for the non-secure registers.
  * @rmtoll
  *  PRIVCFGR          NSPRIV          LL_FLASH_DisableNSecurePrivilege
  * @param  FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableNSecurePrivilege(FLASH_TypeDef *flashx)
{
  CLEAR_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_NSPRIV);
}

/**
  * @brief  Check if the flash privileged protection for the non-secure registers is enabled or disabled.
  * @rmtoll
  *  PRIVCFGR          NSPRIV          LL_FLASH_IsEnabledNSecurePrivilege
  * @param  FLASH instance.
  * @retval State of flash non-secure privilege (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledNSecurePrivilege(const FLASH_TypeDef *flashx)
{
  return ((READ_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_NSPRIV) == (FLASH_PRIVCFGR_NSPRIV)) ? 1UL : 0UL);
}
/**
  * @}
  */
#endif /* defined (FLASH) */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_LL_FLASH_H */
