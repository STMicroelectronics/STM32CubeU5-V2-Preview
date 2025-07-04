/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_syscfg.h
  * @brief   Header file of SYSCFG HAL module driver.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2023-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software
  * component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_HAL_SYSCFG_H
#define STM32U5XX_HAL_SYSCFG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_syscfg.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup SYSCFG SYSCFG
  * @{
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/* Exported macros ---------------------------------------------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup SYSCFG_Exported_Types SYSCFG Exported Types
  * @{
  */

/*! HAL SYSCFG I/O analog switch value enumeration definition */
typedef enum
{
  HAL_SYSCFG_VDDA_SUPPLY    = LL_SYSCFG_VDDA_SUPPLY,     /*!< VDDA supply        */
  HAL_SYSCFG_BOOSTER_SUPPLY = LL_SYSCFG_BOOSTER_SUPPLY,  /*!< VDD booster supply */
  HAL_SYSCFG_VDD_SUPPLY     = LL_SYSCFG_VDD_2V4_SUPPLY   /*!< VDD supply         */
} hal_syscfg_analog_switch_t;


/*! HAL SYSCFG fast mode plus enumeration definition */
typedef enum
{
  HAL_SYSCFG_FAST_MODE_PLUS_DISABLED = 0U, /*!< Fast mode plus is disabled */
  HAL_SYSCFG_FAST_MODE_PLUS_ENABLED  = 1U  /*!< Fast mode plus is enabled  */
} hal_syscfg_fast_mode_plus_status_t;

#if defined(SYSCFG_CFGR1_ENDCAP)
/*! HAL SYSCFG decoupling capacitance value enumeration definition */
typedef enum
{
  HAL_SYSCFG_CAPACITANCE_OFF      = LL_SYSCFG_HSPI_CAPA_OFF,     /*!< Capacitance off on HSPI supply  */
  HAL_SYSCFG_CAPACITANCE_1_DIV_3  = LL_SYSCFG_HSPI_CAPA_1_DIV_3, /*!< 1/3 capacitance on HSPI supply  */
  HAL_SYSCFG_CAPACITANCE_2_DIV_3  = LL_SYSCFG_HSPI_CAPA_2_DIV_3, /*!< 2/3 capacitance on HSPI supply  */
  HAL_SYSCFG_CAPACITANCE_FULL     = LL_SYSCFG_HSPI_CAPA_FULL     /*!< Full capacitance on HSPI supply */
} hal_syscfg_capacitance_t;
#endif /* SYSCFG_CFGR1_ENDCAP */

#if defined(SYSCFG_CFGR1_SRAMCACHED)
/*! HAL SYSCFG internal SRAMs cacheability by DCACHE2 state enumeration definition */
typedef enum
{
  HAL_SYSCFG_DCACHE2_SRAM_DISABLED = 0U, /*!< SRAMx not cached by DCACHE2 */
  HAL_SYSCFG_DCACHE2_SRAM_ENABLED  = 1U  /*!< SRAMx cached by DCACHE2     */
} hal_syscfg_dcache2_sram_status_t;
#endif /* SYSCFG_CFGR1_SRAMCACHED */

/*! HAL SYSCFG floating point unit interrupts state enumeration definition */
typedef enum
{
  HAL_SYSCFG_IT_FPU_DISABLED = 0U, /*!< Floating point interrupt is disabled */
  HAL_SYSCFG_IT_FPU_ENABLED  = 1U  /*!< Floating point interrupt is enabled  */
} hal_syscfg_it_fpu_status_t;

/*! HAL SYSCFG TIM break inputs enumeration definition */
typedef enum
{
  HAL_SYSCFG_TIM_BREAK_INPUT_DISABLED = 0U, /*!< TIM break input is disabled */
  HAL_SYSCFG_TIM_BREAK_INPUT_ENABLED  = 1U  /*!< TIM break input is enabled  */
} hal_syscfg_tim_break_input_status_t;

/*! HAL SYSCFG compensation code enumeration definition */
typedef enum
{
  HAL_SYSCFG_CCELL_CODE_DEFAULT = 0U, /*!< Compensation code default value */
  HAL_SYSCFG_CCELL_CODE_CUSTOM  = 1U  /*!< Compnsation code custom value   */
} hal_syscfg_ccell_code_t;

/*! HAL SYSCFG compensation cell state enumeration definition */
typedef enum
{
  HAL_SYSCFG_CCELL_DISABLED = 0U, /*!< Compensationn cell is disabled */
  HAL_SYSCFG_CCELL_ENABLED  = 1U  /*!< Compensation cell is enabled   */
} hal_syscfg_ccell_status_t;

#if defined(SYSCFG_OTGHSPHYCR_EN)
/*! HAL SYSCFG USB HS PHY state enumeration definition */
typedef enum
{
  HAL_SYSCFG_USBHSPHY_DISABLED = 0U, /*!< USB HS PHY is disabled */
  HAL_SYSCFG_USBHSPHY_ENABLED  = 1U  /*!< USB HS PHY is enabled  */
} hal_syscfg_usbhsphy_status_t;

/*! HAL SYSCFG USB HS PHY power down state enumeration definition */
typedef enum
{
  HAL_SYSCFG_USBHSPHY_PWR_DOWN_DISABLED = 1U, /*!< USB HS PHY power down is disabled  */
  HAL_SYSCFG_USBHSPHY_PWR_DOWN_ENABLED  = 0U  /*!< USB HS PHY power down is enabled   */
} hal_syscfg_usbhsphy_power_down_status_t ;
#endif /* SYSCFG_OTGHSPHYCR_EN */

#if defined(SYSCFG_OTGHSPHYCR_CLKSEL)
/*! HAL SYSCFG reference clock frequency enumeration definition */
typedef enum
{
  HAL_SYSCFG_USBHSPHY_16MHZ   = LL_SYSCFG_USBHSPHY_16MHZ,   /*!< USB HS PHY reference clock of 16 Mhz   */
  HAL_SYSCFG_USBHSPHY_19_2MHZ = LL_SYSCFG_USBHSPHY_19_2MHZ, /*!< USB HS PHY reference clock of 19.2 Mhz */
  HAL_SYSCFG_USBHSPHY_20MHZ   = LL_SYSCFG_USBHSPHY_20MHZ,   /*!< USB HS PHY reference clock of 20 Mhz   */
  HAL_SYSCFG_USBHSPHY_24MHZ   = LL_SYSCFG_USBHSPHY_24MHZ,   /*!< USB HS PHY reference clock of 24 Mhz   */
  HAL_SYSCFG_USBHSPHY_26MHZ   = LL_SYSCFG_USBHSPHY_26MHZ,   /*!< USB HS PHY reference clock of 26 Mhz   */
  HAL_SYSCFG_USBHSPHY_32MHZ   = LL_SYSCFG_USBHSPHY_32MHZ    /*!< USB HS PHY reference clock of 32 Mhz   */
} hal_syscfg_usbhsphy_frequency_t;
#endif /* SYSCFG_OTGHSPHYCR_CLKSEL */

#if defined(SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE)
/*! HAL SYSCFG disconnect threshold adjustment enumeration definition */
typedef enum
{
  HAL_SYSCFG_DIS_ADJUST_0_PERCENT         = LL_SYSCFG_DIS_ADJUST_0_PERCENT,       /*!< Disconnect threshold adjustment default value     */
  HAL_SYSCFG_DIS_ADJUST_PLUS_5_9_PERCENT  = LL_SYSCFG_DIS_ADJUST_PLUS_5_9_PERCENT /*!< Disconnect threshold adjustment recommended value */
} hal_syscfg_disconnect_adjustment_t;

/*! HAL SYSCFG squelch threshold adjustment enumeration definition */
typedef enum
{
  HAL_SYSCFG_SQUELCH_ADJUST_0_PERCENT       = LL_SYSCFG_SQUELCH_ADJUST_0_PERCENT,      /*!< Squelch threshold adjustment default value     */
  HAL_SYSCFG_SQUELCH_ADJUST_PLUS_15_PERCENT = LL_SYSCFG_SQUELCH_ADJUST_PLUS_15_PERCENT /*!< Squelch threshold adjustment recommended value */
} hal_syscfg_squelch_adjust_t;

/*! HAL SYSCFG transmitter peemphasis current enumeration definition */
typedef enum
{
  HAL_SYSCFG_SRC_CURRENT_NO = LL_SYSCFG_SRC_CURRENT_NO, /*!< Transmitter preemphasis circuit disabled   */
  HAL_SYSCFG_SRC_CURRENT_1  = LL_SYSCFG_SRC_CURRENT_1,  /*!< Transmitter preemphasis circuit sources 1x */
  HAL_SYSCFG_SRC_CURRENT_2  = LL_SYSCFG_SRC_CURRENT_2,  /*!< Transmitter preemphasis circuit sources 2x */
  HAL_SYSCFG_SRC_CURRENT_3  = LL_SYSCFG_SRC_CURRENT_3   /*!< Transmitter preemphasis circuit sources 3x */
} hal_syscfg_src_current_t;
#endif /* SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE */

/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/

/** @defgroup SYSCFG_Exported_Constants SYSCFG Exported Constants
  * @{
  */

/** @defgroup SYSCFG_FLOATING_POINT_UNIT_INTERRUPTS SYSCFG Floating point unit interrupts
  * @{
  */
#define HAL_SYSCFG_IT_FPU_IOC LL_SYSCFG_IT_FPU_IOC /*!< Invalid operation interrupt        */
#define HAL_SYSCFG_IT_FPU_DZC LL_SYSCFG_IT_FPU_DZC /*!< Divide-by-zero interrupt           */
#define HAL_SYSCFG_IT_FPU_UFC LL_SYSCFG_IT_FPU_UFC /*!< underflow interrupt                */
#define HAL_SYSCFG_IT_FPU_OFC LL_SYSCFG_IT_FPU_OFC /*!< Overflow interrupt                 */
#define HAL_SYSCFG_IT_FPU_IDC LL_SYSCFG_IT_FPU_IDC /*!< Input abnormal interrupt           */
#define HAL_SYSCFG_IT_FPU_IXC LL_SYSCFG_IT_FPU_IXC /*!< Inexact interrupt                  */
#define HAL_SYSCFG_IT_FPU_ALL LL_SYSCFG_IT_FPU_ALL /*!< All floating point unit interrupts */
/**
  * @}
  */

/** @defgroup SYSCFG_TIM_BREAK_INPUTS SYSCFG TIM break inputs
  * @{
  */
#define HAL_SYSCFG_FLASH_ECC_DOUBLE_ERROR LL_SYSCFG_FLASH_ECC_DOUBLE_ERROR /*!< Flash ECC double error */
#define HAL_SYSCFG_PVD                    LL_SYSCFG_PVD                    /*!< PVD connection         */
#define HAL_SYSCFG_SRAM_ECC_DOUBLE_ERROR  LL_SYSCFG_SRAM_ECC_DOUBLE_ERROR  /*!< SRAM ECC double error  */
#define HAL_SYSCFG_LOCKUP_OUT             LL_SYSCFG_LOCKUP_OUT             /*!< Cortex-M33 LOCKUP      */
#define HAL_SYSCFG_TIM_BREAK_INPUTS_ALL   LL_SYSCFG_TIM_BREAK_INPUTS_ALL   /*!< All TIM break inputs   */
/**
  * @}
  */

/** @defgroup SYSCFG_FAST_MODE_PLUS_DRIVE SYSCFG Fast mode plus drive
  * @{
  */
#define HAL_SYSCFG_DRIVE_PB6 LL_SYSCFG_DRIVE_PB6  /*!< Fast mode plus driving capability activation on PB6 */
#define HAL_SYSCFG_DRIVE_PB7 LL_SYSCFG_DRIVE_PB7  /*!< Fast mode plus driving capability activation on PB7 */
#define HAL_SYSCFG_DRIVE_PB8 LL_SYSCFG_DRIVE_PB8  /*!< Fast mode plus driving capability activation on PB8 */
#define HAL_SYSCFG_DRIVE_PB9 LL_SYSCFG_DRIVE_PB9  /*!< Fast mode plus driving capability activation on PB9 */
#define HAL_SYSCFG_DRIVE_ALL LL_SYSCFG_DRIVE_ALL  /*!< ALL Fast mode plus driving capability activation    */
/**
  * @}
  */

/** @defgroup SYSCFG_COMPENSATION_CELL SYSCFG Compensation cell
  * @{
  */
#define HAL_SYSCFG_CCELL_VDDIO   LL_SYSCFG_CCELL_VDDIO  /*!< VDD I/O compensation cell    */
#define HAL_SYSCFG_CCELL_VDDIO2  LL_SYSCFG_CCELL_VDDIO2 /*!< VDDIO2 I/O compensation cell */
#if defined(SYSCFG_CCCSR_EN3)
#define HAL_SYSCFG_CCELL_HSPIIO  LL_SYSCFG_CCELL_HSPIIO /*!< HSPI I/O compensation cell   */
#endif /*  SYSCFG_CCCSR_EN3 */
#define HAL_SYSCFG_CCELL_ALL     LL_SYSCFG_CCELL_ALL    /*!< All compensation cell        */
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup SYSCFG_Exported_Functions SYSCFG Exported Functions
  * @{
  */

/** @defgroup SYSCFG_Exported_Functions_Group1 General management functions
  * @{
  */
void HAL_SYSCFG_SetAnalogIOSwitchSupply(hal_syscfg_analog_switch_t analog_switch);
hal_syscfg_analog_switch_t HAL_SYSCFG_GetAnalogIOSwitchSupply(void);

void HAL_SYSCFG_EnableFastModePlus(uint32_t fast_mode_plus);
void HAL_SYSCFG_DisableFastModePlus(uint32_t fast_mode_plus);
hal_syscfg_fast_mode_plus_status_t HAL_SYSCFG_IsEnabledFastModePlus(uint32_t fast_mode_plus);

#if defined(SYSCFG_CFGR1_ENDCAP)
void HAL_SYSCFG_SetHSPISupplyDecouplingCapacitance(hal_syscfg_capacitance_t capacitance);
hal_syscfg_capacitance_t HAL_SYSCFG_GetHSPISupplyDecouplingCapacitance(void);
#endif /* SYSCFG_CFGR1_ENDCAP */

#if defined(SYSCFG_CFGR1_SRAMCACHED)
void HAL_SYSCFG_EnableDCACHE2SRAMCacheability(void);
void HAL_SYSCFG_DisableDCACHE2SRAMCacheability(void);
hal_syscfg_dcache2_sram_status_t HAL_SYSCFG_IsEnabledDCACHE2SRAMCacheability(void);
#endif /* SYSCFG_CFGR1_SRAMCACHED */
/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Functions_Group2 Floating point unit interrupts management functions
  * @{
  */
void HAL_SYSCFG_EnableFPUIT(uint32_t floating_point);
void HAL_SYSCFG_DisableFPUIT(uint32_t floating_point);
hal_syscfg_it_fpu_status_t HAL_SYSCFG_IsEnabledFPUIT(uint32_t floating_point);
/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Functions_Group3 TIM break inputs management functions
  * @{
  */
void HAL_SYSCFG_EnableTIMBreakInputs(uint32_t break_input);
hal_syscfg_tim_break_input_status_t HAL_SYSCFG_IsEnabledTIMBreakInputs(uint32_t break_input);
/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Functions_Group4 Compensation cell control functions
  * @{
  */
void HAL_SYSCFG_SetConfigCompensationCellCode(uint32_t comp_cell, hal_syscfg_ccell_code_t code_select);
hal_syscfg_ccell_code_t HAL_SYSCFG_GetConfigCompensationCellCode(uint32_t comp_cell);
hal_status_t HAL_SYSCFG_EnableCompensationCell(uint32_t comp_cell);
void HAL_SYSCFG_DisableCompensationCell(uint32_t comp_cell);
hal_syscfg_ccell_status_t HAL_SYSCFG_IsEnabledCompensationCell(uint32_t comp_cell);
/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Functions_Group5 Compensation code management functions
  * @{
  */
uint32_t HAL_SYSCFG_GetPMOSCompensationCellValue(uint32_t comp_cell);
uint32_t HAL_SYSCFG_GetNMOSCompensationCellValue(uint32_t comp_cell);

void HAL_SYSCFG_SetxMOSCompensationCellCode(uint32_t comp_cell, uint32_t pmos_code, uint32_t nmos_code);
void HAL_SYSCFG_GetxMOSCompensationCellCode(uint32_t comp_cell, uint32_t *p_pmos_code, uint32_t *p_nmos_code);
/**
  * @}
  */

#if defined(SYSCFG_OTGHSPHYCR_EN)
/** @defgroup SYSCFG_Exported_Functions_Group6 USB HS PHY management functions
  * @{
  */
void HAL_SYSCFG_EnableUSBHSPHY(void);
void HAL_SYSCFG_DisableUSBHSPHY(void);
hal_syscfg_usbhsphy_status_t HAL_SYSCFG_IsEnabledUSBHSPHY(void);

void HAL_SYSCFG_EnableUSBHSPHYPowerDown(void);
void HAL_SYSCFG_DisableUSBHSPHYPowerDown(void);
hal_syscfg_usbhsphy_power_down_status_t HAL_SYSCFG_IsEnabledUSBHSPHYPowerDown(void);

void HAL_SYSCFG_SetUSBHSPHYReferenceClockFrequency(hal_syscfg_usbhsphy_frequency_t clk_frequency);
hal_syscfg_usbhsphy_frequency_t HAL_SYSCFG_GetUSBHSPHYReferenceClockFrequency(void);
/**
  * @}
  */
#endif /* SYSCFG_OTGHSPHYCR_EN */

#if defined(SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE)
/** @defgroup SYSCFG_Exported_Functions_Group7 USB HS PHY tune management functions
  * @{
  */
void HAL_SYSCFG_SetConfigUSBHSPHY(hal_syscfg_disconnect_adjustment_t disconnect_threshold,
                                  hal_syscfg_squelch_adjust_t squelch_threshold, hal_syscfg_src_current_t src_current);

void HAL_SYSCFG_GetConfigUSBHSPHY(hal_syscfg_disconnect_adjustment_t *p_disconnect_threshold,
                                  hal_syscfg_squelch_adjust_t *p_squelch_threshold,
                                  hal_syscfg_src_current_t *p_src_current);

void HAL_SYSCFG_SetUSBHSPHYDisconnectThresholdAdjustment(hal_syscfg_disconnect_adjustment_t disconnect_threshold);
hal_syscfg_disconnect_adjustment_t HAL_SYSCFG_GetUSBHSPHYDisconnectThresholdAdjustment(void);

void HAL_SYSCFG_SetUSBHSPHYSquelchThresholdAdjustment(hal_syscfg_squelch_adjust_t squelch_threshold);
hal_syscfg_squelch_adjust_t HAL_SYSCFG_GetUSBHSPHYSquelchThresholdAdjustment(void);

void HAL_SYSCFG_SetUSBHSPHYTransmitterPreemphasisCurrent(hal_syscfg_src_current_t src_current);
hal_syscfg_src_current_t HAL_SYSCFG_GetUSBHSPHYTransmitterPreemphasisCurrent(void);
/**
  * @}
  */
#endif /* SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_HAL_SYSCFG_H */
