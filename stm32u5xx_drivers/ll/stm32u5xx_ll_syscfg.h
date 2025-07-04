/**
  **********************************************************************************************************************
  * @file    stm32u5xx_ll_syscfg.h
  * @brief   Header file of LL syscfg module.
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
#ifndef STM32U5XX_LL_SYSCFG_H
#define STM32U5XX_LL_SYSCFG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

/** @defgroup LL_SYSCFG LL syscfg
  * @{
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup LL_Syscfg_Private_Constants LL syscfg private constants
  * @{
  */
#if defined(SYSCFG_CFGR1_ENDCAP)
/** @defgroup SYSCFG_DECOUPLING_CAPACITANCE SYSCFG decoupling capacitance
  * @{
  */
#define LL_SYSCFG_HSPI_CAPA_OFF      0x0U                  /*!< Capacitance off on HSPI supply  */
#define LL_SYSCFG_HSPI_CAPA_1_DIV_3  SYSCFG_CFGR1_ENDCAP_0 /*!< 1/3 capacitance on HSPI supply  */
#define LL_SYSCFG_HSPI_CAPA_2_DIV_3  SYSCFG_CFGR1_ENDCAP_1 /*!< 2/3 capacitance on HSPI supply  */
#define LL_SYSCFG_HSPI_CAPA_FULL     SYSCFG_CFGR1_ENDCAP   /*!< Full capacitance on HSPI supply */
/**
  * @}
  */
#endif /* SYSCFG_CFGR1_ENDCAP */

/** @defgroup SYSCFG_ANALOG_SWITCHE SYSCFG I/O analog switch supply
  * @{
  */
#define LL_SYSCFG_VDDA_SUPPLY    0U                     /*!< Analog IO switch to VDDA supply     */
#define LL_SYSCFG_BOOSTER_SUPPLY SYSCFG_CFGR1_BOOSTEN   /*!< Analog IO switch to booster supply  */
#define LL_SYSCFG_VDD_2V4_SUPPLY SYSCFG_CFGR1_ANASWVDD  /*!< Analog IO switch to VDD 2.4V supply */
/**
  * @}
  */

/** @defgroup SYSCFG_LL_EC_CCELL_CODE SYSCFG compensation cell Code source
  * @{
  */
#define LL_SYSCFG_CCELL_DEFAULT_CODE 0U /*!< I/Os code from the cell (available in the SYSCFG_CCVR) */
#define LL_SYSCFG_CCELL_CUSTOM_CODE  1U /*!< I/Os code from the SYSCFG compensation cell code register
                                                    (SYSCFG_CCCR) */
/**
  * @}
  */

/** @defgroup SYSCFG_LL_EC_CS1 SYSCFG Vdd compensation cell Code selection
  * @{
  */
#define LL_SYSCFG_CCELL_VDDIO_DEFAULT_CODE 0U               /*!< VDD I/Os code from the cell
                                                                        (available in the SYSCFG_CCVR) */
#define LL_SYSCFG_CCELL_VDDIO_CUSTOM_CODE  SYSCFG_CCCSR_CS1 /*!< VDD I/Os code from the SYSCFG compensation
                                                                        cell code register (SYSCFG_CCCR)*/
/**
  * @}
  */

/** @defgroup SYSCFG_LL_EC_CS2 SYSCFG VddIO2 compensation cell Code selection
  * @{
  */
#define LL_SYSCFG_CCELL_VDDIO2_DEFAULT_CODE 0U               /*!< VDDIO2 I/Os code from the cell (available in
                                                                         the SYSCFG_CCVR) */
#define LL_SYSCFG_CCELL_VDDIO2_CUSTOM_CODE  SYSCFG_CCCSR_CS2 /*!< VDDIO2 I/Os code from the SYSCFG compensation
                                                                         cell code register (SYSCFG_CCCR)*/
/**
  * @}
  */

#if defined(SYSCFG_CCCSR_CS3)
/** @defgroup SYSCFG_LL_EC_CS3 SYSCFG VddHSPI compensation cell Code selection
  * @{
  */
#define LL_SYSCFG_CCELL_HSPIIO_DEFAULT_CODE 0U               /*!< VDD HSPI I/Os code from the cell (available
                                                                         in the SYSCFG_CCVR) */
#define LL_SYSCFG_CCELL_HSPIIO_CUSTOM_CODE  SYSCFG_CCCSR_CS3 /*!< VDD HSPI I/Os code from the SYSCFG compensation
                                                                         cell code register (SYSCFG_CCCR) */
/**
  * @}
  */
#endif /* SYSCFG_CCCSR_CS3 */

/** @defgroup SYSCFG_LL_EC_ERASE_MEMORIES_STATUS SYSCFG MEMORIES ERASE STATUS
  * @{
  */
#define LL_SYSCFG_IPMEE_ERASE_ON_GOING  0U                /*!< Memory erase ongoing */
#define LL_SYSCFG_IPMEE_ERASE_ENDED     SYSCFG_MESR_IPMEE /*!< Memory erase done    */

#define LL_SYSCFG_MCLR_ERASE_ON_GOING   0U                /*!< Memory erase ongoing */
#define LL_SYSCFG_MCLR_ERASE_ENDED      SYSCFG_MESR_MCLR  /*!< Memory erase done    */
/**
  * @}
  */

/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/

/** @defgroup SYSCFG_LL_Exported_Constants SYSCFG Exported Constants
  * @{
  */


/** @defgroup SYSCFG_LL_EC_FASTMODEPLUS SYSCFG fast mode plus
  * @{
  */
#define LL_SYSCFG_DRIVE_PB6 SYSCFG_CFGR1_PB6_FMP  /*!< Enables the Fast Mode Plus on PB6 */
#define LL_SYSCFG_DRIVE_PB7 SYSCFG_CFGR1_PB7_FMP  /*!< Enables the Fast Mode Plus on PB7 */
#define LL_SYSCFG_DRIVE_PB8 SYSCFG_CFGR1_PB8_FMP  /*!< Enables the Fast Mode Plus on PB8 */
#define LL_SYSCFG_DRIVE_PB9 SYSCFG_CFGR1_PB9_FMP  /*!< Enables the Fast Mode Plus on PB9 */
#define LL_SYSCFG_DRIVE_ALL (SYSCFG_CFGR1_PB6_FMP | SYSCFG_CFGR1_PB7_FMP | \
                             SYSCFG_CFGR1_PB8_FMP | SYSCFG_CFGR1_PB9_FMP)
/*!< Enables all Fast mode plus driving capability */
/**
  * @}
  */

/** @defgroup SYSCFG_LL_EC_FLOATING_POINT_UNIT_INTERRUPTs SYSCFG floating point unit interrupts
  * @{
  */
#define LL_SYSCFG_IT_FPU_IOC SYSCFG_FPUIMR_FPU_IE_0 /*!< Invalid operation interrupt                    */
#define LL_SYSCFG_IT_FPU_DZC SYSCFG_FPUIMR_FPU_IE_1 /*!< Divide-by-zero interrupt                       */
#define LL_SYSCFG_IT_FPU_UFC SYSCFG_FPUIMR_FPU_IE_2 /*!< underflow interrupt                            */
#define LL_SYSCFG_IT_FPU_OFC SYSCFG_FPUIMR_FPU_IE_3 /*!< Overflow interrupt                             */
#define LL_SYSCFG_IT_FPU_IDC SYSCFG_FPUIMR_FPU_IE_4 /*!< Input abnormal interrupt                       */
#define LL_SYSCFG_IT_FPU_IXC SYSCFG_FPUIMR_FPU_IE_5 /*!< Inexact interrupt                              */
#define LL_SYSCFG_IT_FPU_ALL (SYSCFG_FPUIMR_FPU_IE_0 | SYSCFG_FPUIMR_FPU_IE_1 | SYSCFG_FPUIMR_FPU_IE_2 | \
                              SYSCFG_FPUIMR_FPU_IE_3 | SYSCFG_FPUIMR_FPU_IE_4 | SYSCFG_FPUIMR_FPU_IE_5)
/*!< All floating point unit interrupts interrupt   */

/**
  * @}
  */

/** @defgroup SYSCFG_LL_EC_TIMBREAK SYSCFG TIMER BREAK
  * @{
  */
#define LL_SYSCFG_FLASH_ECC_DOUBLE_ERROR SYSCFG_CFGR2_ECCL /*!< Enables and locks the FLASH ECC error signal
                                                                  with Break Input of TIM1/8/15/16/17 */
#define LL_SYSCFG_PVD                    SYSCFG_CFGR2_PVDL /*!< Enables and locks the PVD connection
                                                                  with TIM1/8/15/16/17 Break Input and also the PVDE
                                                                  and PLS bits of the Power Control Interface */
#define LL_SYSCFG_SRAM_ECC_DOUBLE_ERROR  SYSCFG_CFGR2_SPL /*!< Enables and locks the SRAM ECC double error signal
                                                                  with Break Input of TIM1/8/15/16/17 */
#define LL_SYSCFG_LOCKUP_OUT             SYSCFG_CFGR2_CLL  /*!< Enables and locks the LOCKUP output of CortexM33
                                                                  with Break Input of TIM1/15/16/17 */

#define LL_SYSCFG_TIM_BREAK_INPUTS_ALL   (SYSCFG_CFGR2_ECCL | SYSCFG_CFGR2_PVDL | \
                                          SYSCFG_CFGR2_SPL   | SYSCFG_CFGR2_CLL)
/*!< Enables and locks the all with Break Input
of TIM1/15/16/17 */
/**
  * @}
  */


#define LL_SYSCFG_CCELL_VDDIO      SYSCFG_CCCSR_EN1 /*!< Compensation cell selection for VDDIO  */
#define LL_SYSCFG_CCELL_VDDIO2     SYSCFG_CCCSR_EN2 /*!< Compensation cell selection for VDDIO2 */
#if defined(SYSCFG_CCCSR_EN3)
#define LL_SYSCFG_CCELL_HSPIIO     SYSCFG_CCCSR_EN3 /*!< Compensation cell selection for HSPIIO */
#endif /* SYSCFG_CCCSR__CCELLEN3 */
#if defined(SYSCFG_CCCSR_EN3)
#define LL_SYSCFG_CCELL_ALL        (SYSCFG_CCCSR_EN1 | SYSCFG_CCCSR_EN2 | SYSCFG_CCCSR_EN3)
#else
#define LL_SYSCFG_CCELL_ALL        (SYSCFG_CCCSR_EN1 | SYSCFG_CCCSR_EN2)
#endif /* SYSCFG_CCCSR_EN3 */

/** @defgroup SYSCFG_USB_PHY_RefenceClockFrequency SYSCFG USB PHY Reference Clock frequency
  * @{
  */
#define LL_SYSCFG_USBHSPHY_16MHZ   (SYSCFG_OTGHSPHYCR_CLKSEL_0 | SYSCFG_OTGHSPHYCR_CLKSEL_1) /*!< Clock frequency
                                                                                                         16 MHz */
#define LL_SYSCFG_USBHSPHY_19_2MHZ SYSCFG_OTGHSPHYCR_CLKSEL_3                                /*!< Clock frequency
                                                                                                         19.2 MHz */
#define LL_SYSCFG_USBHSPHY_20MHZ   (SYSCFG_OTGHSPHYCR_CLKSEL_0 | SYSCFG_OTGHSPHYCR_CLKSEL_3) /*!< Clock frequency
                                                                                                         20 MHz */
#define LL_SYSCFG_USBHSPHY_24MHZ   (SYSCFG_OTGHSPHYCR_CLKSEL_1 | SYSCFG_OTGHSPHYCR_CLKSEL_3) /*!< Clock frequency
                                                                                                         24 MHz   */
#define LL_SYSCFG_USBHSPHY_26MHZ   (SYSCFG_OTGHSPHYCR_CLKSEL_1 | SYSCFG_OTGHSPHYCR_CLKSEL_2 | \
                                    SYSCFG_OTGHSPHYCR_CLKSEL_3)                              /*!< Clock frequency
                                                                                                         26 MHz   */
#define LL_SYSCFG_USBHSPHY_32MHZ   (SYSCFG_OTGHSPHYCR_CLKSEL_0 | SYSCFG_OTGHSPHYCR_CLKSEL_1 | \
                                    SYSCFG_OTGHSPHYCR_CLKSEL_3)                              /*!< Clock frequency
                                                                                                         32 MHz   */
/**
  * @}
  */

/** @defgroup SYSCFG_USBHSPHY_TRANSMITTER_PREEMPHASIS_CURRENT SYSCFG USB HS PHY transmitter preemphasis current
  * @{
  */
#define LL_SYSCFG_SRC_CURRENT_NO 0U                                      /*!< Transmitter preemphasis disabled */
#define LL_SYSCFG_SRC_CURRENT_1  SYSCFG_OTGHSPHYTUNER2_TXPREEMPAMPTUNE_0 /*!< Transmitter preemphasis circuit
                                                                                     sources 1x */
#define LL_SYSCFG_SRC_CURRENT_2  SYSCFG_OTGHSPHYTUNER2_TXPREEMPAMPTUNE_1 /*!< Transmitter preemphasis circuit
                                                                                     sources 2x */
#define LL_SYSCFG_SRC_CURRENT_3  SYSCFG_OTGHSPHYTUNER2_TXPREEMPAMPTUNE   /*!< Transmitter preemphasis circuit
                                                                                     sources 3x */
/**
  * @}
  */

/** @defgroup SYSCFG_SQUELCH_THRESHOLD_ADJUSTMENT SYSCFG squelch threshold adjustment
  * @{
  */
#define LL_SYSCFG_SQUELCH_ADJUST_0_PERCENT       (SYSCFG_OTGHSPHYTUNER2_SQRXTUNE_0 \
                                                  | SYSCFG_OTGHSPHYTUNER2_SQRXTUNE_1)  /*!< 0% (default value) */

#define LL_SYSCFG_SQUELCH_ADJUST_PLUS_15_PERCENT 0U   /*!< +15% (recommended value) */

/**
  * @}
  */

/** @defgroup SYSCFG_DISCONNECT_THRESHOLD_ADJUSTMENT SYSCFG disconnect threshold adjustment
  * @{
  */
#define LL_SYSCFG_DIS_ADJUST_0_PERCENT        SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE_0 /*!< Adjusts the voltage level
                        for the threshold used to detect a disconnect event at the host by 0% (default value) */
#define LL_SYSCFG_DIS_ADJUST_PLUS_5_9_PERCENT SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE_1 /*!< Adjusts the voltage level
                        for the threshold used to detect a disconnect event at the host by +5.9% (recommended value) */
/**
  * @}
  */

/** @defgroup SYSCFG_LL_EC_SECURE_ATTRIBUTES Secure attributes
  * @note Only available when syscfg implements security (TZEN=1)
  * @{
  */
#define LL_SYSCFG_CLOCK_SEC   SYSCFG_SECCFGR_SYSCFGSEC /*!< SYSCFG clock configuration secure-only access */
#define LL_SYSCFG_CLOCK_NSEC  0U                       /*!< SYSCFG clock configuration secure/non-secure access*/
#define LL_SYSCFG_CLASSB_SEC  SYSCFG_SECCFGR_CLASSBSEC /*!< Class B configuration secure-only access */
#define LL_SYSCFG_CLASSB_NSEC 0U                       /*!< Class B configuration secure/non-secure access */
#define LL_SYSCFG_FPU_SEC     SYSCFG_SECCFGR_FPUSEC    /*!< FPU configuration secure-only access */
#define LL_SYSCFG_FPU_NSEC    0U                       /*!< FPU configuration secure/non-secure access */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup SYSCFG_LL_Exported_Macros SYSCFG Exported Macros
  * @{
  */

/** @defgroup SYSCFG_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in SYSCFG register
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_SYSCFG_WRITE_REG(reg, value) WRITE_REG(SYSCFG->reg, (value))

/**
  * @brief  Read a value in SYSCFG register
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_SYSCFG_READ_REG(reg) READ_REG(SYSCFG->reg)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup LL_Syscfg_Exported_Functions LL syscfg exported functions
  * @{
  */

/**
  * @brief  Set I/O analog switch supply.
  * @rmtoll
  *  SYSCFG_CFGR1 ANASWVDD BOOSTEN   LL_SYSCFG_SetAnalogIOSwitchSupply
  * @param  analog_switch This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SYSCFG_VDDA_SUPPLY
  *         @arg @ref LL_SYSCFG_BOOSTER_SUPPLY
  *         @arg @ref LL_SYSCFG_VDD_2V4_SUPPLY
  */
__STATIC_INLINE void LL_SYSCFG_SetAnalogIOSwitchSupply(uint32_t analog_switch)
{
  MODIFY_REG(SYSCFG->CFGR1, (SYSCFG_CFGR1_BOOSTEN | SYSCFG_CFGR1_ANASWVDD), analog_switch);
}

/**
  * @brief  Get I/O analog switch supply.
  * @rmtoll
  *  SYSCFG_CFGR1 ANASWVDD  LL_SYSCFG_GetAnalogIOSwitchSupply \n
  *  SYSCFG_CFGR1 BOOSTEN   LL_SYSCFG_GetAnalogIOSwitchSupply
  * @retval Returned This value can be one of the following values:
  *         @arg @ref LL_SYSCFG_VDDA_SUPPLY
  *         @arg @ref LL_SYSCFG_BOOSTER_SUPPLY
  *         @arg @ref LL_SYSCFG_VDD_2V4_SUPPLY
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetAnalogIOSwitchSupply(void)
{
  return (READ_BIT(SYSCFG->CFGR1, (SYSCFG_CFGR1_BOOSTEN | SYSCFG_CFGR1_ANASWVDD)));
}

/**
  * @brief  Enable I/O analog switches supplied by VDD.
  * @rmtoll
  *  SYSCFG_CFGR1 ANASWVDD      LL_SYSCFG_EnableAnalogSwitchVdd
  */
__STATIC_INLINE void LL_SYSCFG_EnableAnalogSwitchVdd(void)
{
  SET_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_ANASWVDD);
}

/**
  * @brief  Disable I/O analog switches supplied by VDD.
  * @rmtoll
  *  SYSCFG_CFGR1 ANASWVDD      LL_SYSCFG_DisableAnalogSwitchVdd
  * @note   I/O analog switches are supplied by VDDA or booster
  *         when booster in on.
  *         Dedicated voltage booster (supplied by VDD) is the recommended
  *         configuration with low VDDA voltage operation.
  */
__STATIC_INLINE void LL_SYSCFG_DisableAnalogSwitchVdd(void)
{
  CLEAR_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_ANASWVDD);
}

/**
  * @brief  Enable I/O analog switch voltage booster.
  * @rmtoll
  *  SYSCFG_CFGR1 BOOSTEN       LL_SYSCFG_EnableAnalogBooster
  * @note   When voltage booster is enabled, I/O analog switches are supplied
  *         by a dedicated voltage booster, from VDD power domain. This is
  *         the recommended configuration with low VDDA voltage operation.
  * @note   The I/O analog switch voltage booster is relevant for peripherals
  *         using I/O in analog input: ADC, COMP, OPAMP.
  *         However, COMP and OPAMP inputs have a high impedance and
  *         voltage booster does not impact performance significantly.
  *         Therefore, the voltage booster is mainly intended for
  *         usage with ADC.
  */
__STATIC_INLINE void LL_SYSCFG_EnableAnalogBooster(void)
{
  SET_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_BOOSTEN);
}

/**
  * @brief  Disable I/O analog switch voltage booster.
  * @rmtoll
  *  SYSCFG_CFGR1 BOOSTEN       LL_SYSCFG_DisableAnalogBooster
  * @note   When voltage booster is enabled, I/O analog switches are supplied
  *         by a dedicated voltage booster, from VDD power domain. This is
  *         the recommended configuration with low VDDA voltage operation.
  * @note   The I/O analog switch voltage booster is relevant for peripherals
  *         using I/O in analog input: ADC, COMP, OPAMP.
  *         However, COMP and OPAMP inputs have a high impedance and
  *         voltage booster does not impact performance significantly.
  *         Therefore, the voltage booster is mainly intended for
  *         usage with ADC.
  */
__STATIC_INLINE void LL_SYSCFG_DisableAnalogBooster(void)
{
  CLEAR_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_BOOSTEN);
}

/**
  * @brief  Enable the fast mode plus driving capability.
  * @rmtoll
  *  SYSCFG_CFGR1 PBx_FMP   LL_SYSCFG_EnableFastModePlus
  * @param  fast_mode_plus This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SYSCFG_DRIVE_PB6
  *         @arg @ref LL_SYSCFG_DRIVE_PB7
  *         @arg @ref LL_SYSCFG_DRIVE_PB8
  *         @arg @ref LL_SYSCFG_DRIVE_PB9
  */
__STATIC_INLINE void LL_SYSCFG_EnableFastModePlus(uint32_t fast_mode_plus)
{
  SET_BIT(SYSCFG->CFGR1, fast_mode_plus);
}

/**
  * @brief  Disable the fast mode plus driving capability.
  * @rmtoll
  *  SYSCFG_CFGR1 PBx_FMP   LL_SYSCFG_DisableFastModePlus
  * @param  fast_mode_plus This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SYSCFG_DRIVE_PB6
  *         @arg @ref LL_SYSCFG_DRIVE_PB7
  *         @arg @ref LL_SYSCFG_DRIVE_PB8
  *         @arg @ref LL_SYSCFG_DRIVE_PB9
  */
__STATIC_INLINE void LL_SYSCFG_DisableFastModePlus(uint32_t fast_mode_plus)
{
  CLEAR_BIT(SYSCFG->CFGR1, fast_mode_plus);
}

/**
  * @brief  Check if fast mode plus is enabled or disabled.
  * @rmtoll
  *  SYSCFG_CFGR1 PB6_FMP   LL_SYSCFG_IsEnabledFastModePlus \n
  *  SYSCFG_CFGR1 PB7_FMP   LL_SYSCFG_IsEnabledFastModePlus \n
  *  SYSCFG_CFGR1 PB8_FMP   LL_SYSCFG_IsEnabledFastModePlus \n
  *  SYSCFG_CFGR1 PB9_FMP   LL_SYSCFG_IsEnabledFastModePlus
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledFastModePlus(uint32_t fast_mode_plus)
{
  return ((READ_BIT(SYSCFG->CFGR1, fast_mode_plus) == fast_mode_plus) ? 1UL : 0UL);
}

#if defined(SYSCFG_CFGR1_ENDCAP)
/**
  * @brief  Set decoupling capacitance on HSPI supply.
  * @rmtoll
  *  SYSCFG_CFGR1 ENDCAP   LL_SYSCFG_SetHSPISupplyDecouplingCapacitance
  * @param  capacitance This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_HSPI_CAPA_OFF
  *         @arg @ref LL_SYSCFG_HSPI_CAPA_1_DIV_3
  *         @arg @ref LL_SYSCFG_HSPI_CAPA_2_DIV_3
  *         @arg @ref LL_SYSCFG_HSPI_CAPA_FULL
  */
__STATIC_INLINE void LL_SYSCFG_SetHSPISupplyDecouplingCapacitance(uint32_t capacitance)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_ENDCAP, capacitance);
}

/**
  * @brief  Get decoupling capacitance on HSPI supply.
  * @rmtoll
  *  SYSCFG_CFGR1 ENDCAP   LL_SYSCFG_GetHSPISupplyDecouplingCapacitance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_HSPI_CAPA_OFF
  *         @arg @ref LL_SYSCFG_HSPI_CAPA_1_DIV_3
  *         @arg @ref LL_SYSCFG_HSPI_CAPA_2_DIV_3
  *         @arg @ref LL_SYSCFG_HSPI_CAPA_FULL
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetHSPISupplyDecouplingCapacitance(void)
{
  return (READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_ENDCAP));
}
#endif /* SYSCFG_CFGR1_ENDCAP */

#if defined(SYSCFG_CFGR1_SRAMCACHED)
/**
  * @brief  Enable internal SRAMs cacheability by DCACHE2.
  * @rmtoll
  *  SYSCFG_CFGR1 SRAMCACHED   LL_SYSCFG_EnableDCACHE2SRAMCacheability
  */
__STATIC_INLINE void LL_SYSCFG_EnableDCACHE2SRAMCacheability(void)
{
  SET_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_SRAMCACHED);
}

/**
  * @brief  Disable internal SRAMs cacheability by DCACHE2.
  * @rmtoll
  *  SYSCFG_CFGR1 SRAMCACHED   LL_SYSCFG_DisableDCACHE2SRAMCacheability
  */
__STATIC_INLINE void LL_SYSCFG_DisableDCACHE2SRAMCacheability(void)
{
  CLEAR_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_SRAMCACHED);
}

/**
  * @brief  Check if internal SRAMs cacheability by DCACHE2 is enabled or disabled.
  * @rmtoll
  *  SYSCFG_CFGR1 SRAMCACHED   LL_SYSCFG_IsEnabledDCACHE2SRAMCacheability
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledDCACHE2SRAMCacheability(void)
{
  return ((READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_SRAMCACHED) == SYSCFG_CFGR1_SRAMCACHED) ? 1UL : 0UL);
}
#endif /* SYSCFG_CFGR1_SRAMCACHED */

/**
  * @brief  Enable floating point unit interrupts bits.
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_0   LL_SYSCFG_EnableFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_1   LL_SYSCFG_EnableFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_2   LL_SYSCFG_EnableFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_3   LL_SYSCFG_EnableFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_4   LL_SYSCFG_EnableFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_5   LL_SYSCFG_EnableFPUIT
  * @param  floating_point This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SYSCFG_IT_FPU_IOC
  *         @arg @ref LL_SYSCFG_IT_FPU_DZC
  *         @arg @ref LL_SYSCFG_IT_FPU_UFC
  *         @arg @ref LL_SYSCFG_IT_FPU_OFC
  *         @arg @ref LL_SYSCFG_IT_FPU_IDC
  *         @arg @ref LL_SYSCFG_IT_FPU_IXC
  */
__STATIC_INLINE void LL_SYSCFG_EnableFPUIT(uint32_t floating_point)
{
  SET_BIT(SYSCFG->FPUIMR, floating_point);
}

/**
  * @brief  Disable floating point unit interrupts bits.
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_0   LL_SYSCFG_DisableFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_1   LL_SYSCFG_DisableFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_2   LL_SYSCFG_DisableFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_3   LL_SYSCFG_DisableFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_4   LL_SYSCFG_DisableFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_5   LL_SYSCFG_DisableFPUIT
  * @param  floating_point This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SYSCFG_IT_FPU_IOC
  *         @arg @ref LL_SYSCFG_IT_FPU_DZC
  *         @arg @ref LL_SYSCFG_IT_FPU_UFC
  *         @arg @ref LL_SYSCFG_IT_FPU_OFC
  *         @arg @ref LL_SYSCFG_IT_FPU_IDC
  *         @arg @ref LL_SYSCFG_IT_FPU_IXC
  */
__STATIC_INLINE void LL_SYSCFG_DisableFPUIT(uint32_t floating_point)
{
  CLEAR_BIT(SYSCFG->FPUIMR, floating_point);
}

/**
  * @brief  Check if floating point unit interrupts bits is enabled.
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_0   LL_SYSCFG_IsenabledFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_1   LL_SYSCFG_IsenabledFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_2   LL_SYSCFG_IsenabledFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_3   LL_SYSCFG_IsenabledFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_4   LL_SYSCFG_IsenabledFPUIT \n
  *  SYSCFG_FPUIMR FPU_IE_5   LL_SYSCFG_IsenabledFPUIT
  * @param  floating_point This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_IT_FPU_IOC
  *         @arg @ref LL_SYSCFG_IT_FPU_DZC
  *         @arg @ref LL_SYSCFG_IT_FPU_UFC
  *         @arg @ref LL_SYSCFG_IT_FPU_OFC
  *         @arg @ref LL_SYSCFG_IT_FPU_IDC
  *         @arg @ref LL_SYSCFG_IT_FPU_IXC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsenabledFPUIT(uint32_t floating_point)
{
  return ((READ_BIT(SYSCFG->FPUIMR, floating_point) == floating_point) ? 1UL : 0UL);
}

/**
  * @brief  Enable Floating Point Unit Invalid operation Interrupt
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_0      LL_SYSCFG_EnableIT_FPU_IOC
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_IOC(void)
{
  SET_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_0);
}

/**
  * @brief  Disable Floating Point Unit Invalid operation Interrupt
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_0      LL_SYSCFG_DisableIT_FPU_IOC
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_IOC(void)
{
  CLEAR_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_0);
}

/**
  * @brief  Check if Floating Point Unit Invalid operation Interrupt source is enabled or disabled.
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_0      LL_SYSCFG_IsEnabledIT_FPU_IOC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_IOC(void)
{
  return ((READ_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_0) == SYSCFG_FPUIMR_FPU_IE_0) ? 1UL : 0UL);
}

/**
  * @brief  Enable Floating Point Unit Divide-by-zero Interrupt
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_1      LL_SYSCFG_EnableIT_FPU_DZC
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_DZC(void)
{
  SET_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_1);
}

/**
  * @brief  Disable Floating Point Unit Divide-by-zero Interrupt
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_1      LL_SYSCFG_DisableIT_FPU_DZC
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_DZC(void)
{
  CLEAR_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_1);
}

/**
  * @brief  Check if Floating Point Unit Divide-by-zero Interrupt source is enabled or disabled.
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_1      LL_SYSCFG_IsEnabledIT_FPU_DZC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_DZC(void)
{
  return ((READ_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_1) == SYSCFG_FPUIMR_FPU_IE_1) ? 1UL : 0UL);
}

/**
  * @brief  Enable Floating Point Unit Underflow Interrupt
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_2      LL_SYSCFG_EnableIT_FPU_UFC
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_UFC(void)
{
  SET_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_2);
}

/**
  * @brief  Disable Floating Point Unit Underflow Interrupt
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_2      LL_SYSCFG_DisableIT_FPU_UFC
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_UFC(void)
{
  CLEAR_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_2);
}

/**
  * @brief  Check if Floating Point Unit Underflow Interrupt source is enabled or disabled.
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_2      LL_SYSCFG_IsEnabledIT_FPU_UFC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_UFC(void)
{
  return ((READ_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_2) == SYSCFG_FPUIMR_FPU_IE_2) ? 1UL : 0UL);
}

/**
  * @brief  Enable Floating Point Unit Overflow Interrupt
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_3      LL_SYSCFG_EnableIT_FPU_OFC
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_OFC(void)
{
  SET_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_3);
}

/**
  * @brief  Disable Floating Point Unit Overflow Interrupt
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_3      LL_SYSCFG_DisableIT_FPU_OFC
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_OFC(void)
{
  CLEAR_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_3);
}

/**
  * @brief  Check if Floating Point Unit Overflow Interrupt source is enabled or disabled.
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_3      LL_SYSCFG_IsEnabledIT_FPU_OFC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_OFC(void)
{
  return ((READ_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_3) == SYSCFG_FPUIMR_FPU_IE_3) ? 1UL : 0UL);
}

/**
  * @brief  Enable Floating Point Unit Input denormal Interrupt
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_4      LL_SYSCFG_EnableIT_FPU_IDC
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_IDC(void)
{
  SET_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_4);
}

/**
  * @brief  Disable Floating Point Unit Input denormal Interrupt
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_4      LL_SYSCFG_DisableIT_FPU_IDC
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_IDC(void)
{
  CLEAR_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_4);
}

/**
  * @brief  Check if Floating Point Unit Input denormal Interrupt source is enabled or disabled.
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_4      LL_SYSCFG_IsEnabledIT_FPU_IDC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_IDC(void)
{
  return ((READ_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_4) == SYSCFG_FPUIMR_FPU_IE_4) ? 1UL : 0UL);
}

/**
  * @brief  Enable Floating Point Unit Inexact Interrupt
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_5      LL_SYSCFG_EnableIT_FPU_IXC
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_IXC(void)
{
  SET_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_5);
}

/**
  * @brief  Disable Floating Point Unit Inexact Interrupt
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_5      LL_SYSCFG_DisableIT_FPU_IXC
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_IXC(void)
{
  CLEAR_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_5);
}

/**
  * @brief  Check if Floating Point Unit Inexact Interrupt source is enabled or disabled.
  * @rmtoll
  *  SYSCFG_FPUIMR FPU_IE_5      LL_SYSCFG_IsEnabledIT_FPU_IXC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_IXC(void)
{
  return ((READ_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_5) == SYSCFG_FPUIMR_FPU_IE_5) ? 1UL : 0UL);
}

/**
  * @brief  Set connections to TIM1/8/15/16/17 break inputs.
  * @rmtoll
  *  SYSCFG_CFGR2 CLL          LL_SYSCFG_EnableTIMBreakInputs \n
  *  SYSCFG_CFGR2 SPL          LL_SYSCFG_EnableTIMBreakInputs \n
  *  SYSCFG_CFGR2 PVDL         LL_SYSCFG_EnableTIMBreakInputs \n
  *  SYSCFG_CFGR2 ECCL         LL_SYSCFG_EnableTIMBreakInputs
  * @param  break_input This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SYSCFG_FLASH_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SYSCFG_PVD
  *         @arg @ref LL_SYSCFG_SRAM_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SYSCFG_LOCKUP_OUT
  */
__STATIC_INLINE void LL_SYSCFG_EnableTIMBreakInputs(uint32_t break_input)
{
  MODIFY_REG(SYSCFG->CFGR2, (SYSCFG_CFGR2_CLL | SYSCFG_CFGR2_SPL | SYSCFG_CFGR2_PVDL | SYSCFG_CFGR2_ECCL), break_input);
}

/**
  * @brief  Get connections to TIM1/8/15/16/17 break inputs.
  * @rmtoll
  *  SYSCFG_CFGR2   CLL     LL_SYSCFG_IsEnabledTIMBreakInputs \n
  *  SYSCFG_CFGR2   SPL     LL_SYSCFG_IsEnabledTIMBreakInputs \n
  *  SYSCFG_CFGR2   PVDL    LL_SYSCFG_IsEnabledTIMBreakInputs \n
  *  SYSCFG_CFGR2   ECCL    LL_SYSCFG_IsEnabledTIMBreakInputs
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_FLASH_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SYSCFG_PVD
  *         @arg @ref LL_SYSCFG_SRAM_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SYSCFG_LOCKUP_OUT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledTIMBreakInputs(uint32_t break_input)
{
  return ((READ_BIT(SYSCFG->CFGR2, break_input) == (break_input)) ? 1UL : 0UL);
}

/** @defgroup SYSCFG_LL_EF_COMPENSATION SYSCFG COMPENSATION
  * @{
  */

/**
  * @brief  Set the compensation cell code of each compensation cell.
  * @rmtoll CCCSR    CSx x= [1..3]  LL_SYSCFG_SetConfigCompensationCellCodeSource
  * @param  comp_cell This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref LL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  *         @arg @ref LL_SYSCFG_CCELL_ALL
  * @param  code_source: This parameter can be one of the following values:
  *         @arg LL_SYSCFG_CCELL_DEFAULT_CODE
  *         @arg LL_SYSCFG_CCELL_CUSTOM_CODE
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_SYSCFG_SetConfigCompensationCellCodeSource(uint32_t comp_cell, uint32_t code_source)
{
  ATOMIC_MODIFY_REG(SYSCFG->CCCSR, (comp_cell << 1U), (code_source * (comp_cell << 1U)));
}

/**
  * @brief  Get the compensation cell code.
  * @rmtoll
  *  SYSCFG_CCCSR    CS1    LL_SYSCFG_GetCompensationCellCode \n
  *  SYSCFG_CCCSR    CS2    LL_SYSCFG_GetCompensationCellCode \n
  *  SYSCFG_CCCSR    CS3    LL_SYSCFG_GetCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref LL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  * @note   (*) value not defined in all devices
  * @retval Returned value can be one of the following values:
  *   @arg LL_SYSCFG_CCELL_CODE_DEFAULT: Selected Code is from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_CCELL_CODE_CUSTOM: Selected Code is from the SYSCFG compensation
  *                                            cell code register (SYSCFG_CCCR)
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetConfigCompensationCellCodeSource(uint32_t comp_cell)
{
  return (READ_BIT(SYSCFG->CCCSR, (SYSCFG_CCCSR_CS1 << POSITION_VAL(comp_cell))) >> POSITION_VAL(comp_cell << 1U));
}

/**
  * @brief  Set the compensation cell code selection of GPIO supplied by VDD
  * @rmtoll
  *  CCCSR   CS1    LL_SYSCFG_SetVddIOCompensationCellCodeSource
  * @param  code_source: Select the code to be applied for the Vdd compensation cell
  *   This parameter can be one of the following values:
  *   @arg LL_SYSCFG_CCELL_VDDIO_DEFAULT_CODE: Select Code from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_CCELL_VDDIO_CUSTOM_CODE: Select Code from the SYSCFG compensation cell code
  *                                                  register (SYSCFG_CCCR)
  */
__STATIC_INLINE void LL_SYSCFG_SetVddIOCompensationCellCodeSource(uint32_t code_source)
{
  ATOMIC_SET_BIT(SYSCFG->CCCSR, code_source);
}

/**
  * @brief  Get the compensation cell code selection of GPIO supplied by VDD
  * @rmtoll
  *  CCCSR   CS1    LL_SYSCFG_GetVddIOCompensationCellCodeSource
  * @retval Returned value can be one of the following values:
  *   @arg LL_SYSCFG_CCELL_VDDIO_DEFAULT_CODE : Selected Code is from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_CCELL_VDDIO_CUSTOM_CODE: Selected Code is from the SYSCFG compensation cell code
  *                                            register (SYSCFG_CCCR)
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetVddIOCompensationCellCodeSource(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_CS1));
}

/**
  * @brief  Set the compensation cell code selection of GPIO supplied by VDDIO2
  * @rmtoll
  *  CCCSR   CS2    LL_SYSCFG_SetVddIO2CompensationCellCodeSource
  * @param  code_source: Selects the code to be applied for the VddIO compensation cell
  *   This parameter can be one of the following values:
  *   @arg LL_SYSCFG_CCELL_VDDIO2_DEFAULT_CODE: Select Code from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_CCELL_VDDIO2_CUSTOM_CODE: Select Code from the SYSCFG compensation cell code
  *                                                   register (SYSCFG_CCCR)
  */
__STATIC_INLINE void LL_SYSCFG_SetVddIO2CompensationCellCodeSource(uint32_t code_source)
{
  ATOMIC_SET_BIT(SYSCFG->CCCSR, code_source);
}

/**
  * @brief  Get the compensation cell code selection of GPIO supplied by VDDIO2
  * @rmtoll
  *  CCCSR   CS2    LL_SYSCFG_GetVddIO2CompensationCellCodeSource
  * @retval Returned value can be one of the following values:
  *   @arg LL_SYSCFG_CCELL_VDDIO2_DEFAULT_CODE : Selected Code is from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_CCELL_VDDIO2_CUSTOM_CODE: Selected Code is from the SYSCFG compensation
  *   cell code register (SYSCFG_CCCR)
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetVddIO2CompensationCellCodeSource(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_CS2));
}

#if defined(SYSCFG_CCCSR_CS3)
/**
  * @brief  Set the compensation cell code selection of HSPI IO supplied by VDD
  * @rmtoll
  *  CCCSR   CS3    LL_SYSCFG_SetVddHSPICompensationCellCodeSource
  * @param  code_source: Selects the code to be applied for the VddIO compensation cell
  *   This parameter can be one of the following values:
  *   @arg LL_SYSCFG_CCELL_HSPIIO_DEFAULT_CODE : Select Code from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_CCELL_HSPIIO_CUSTOM_CODE: Select Code from the SYSCFG compensation cell code
  *                                                   register (SYSCFG_CCCR)
  */
__STATIC_INLINE void LL_SYSCFG_SetVddHSPICompensationCellCodeSource(uint32_t code_source)
{
  ATOMIC_SET_BIT(SYSCFG->CCCSR, code_source);
}

/**
  * @brief  Get the compensation cell code selection of HSPI IO supplied by VDD
  * @rmtoll
  *  CCCSR   CS3    LL_SYSCFG_GetVddHSPICompensationCellCodeSource
  * @retval Returned value can be one of the following values:
  *   @arg LL_SYSCFG_CCELL_HSPIIO_DEFAULT_CODE : Selected Code is from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_CCELL_HSPIIO_CUSTOM_CODE: Selected Code is from the SYSCFG compensation
  *    cell code register (SYSCFG_CCCR)
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetVddHSPICompensationCellCodeSource(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_CS3));
}
#endif /* SYSCFG_CCCSR_CS3 */

/**
  * @brief  Enable the Compensation Cell.
  * @rmtoll CCCSR   ENX   X[1..3]    LL_SYSCFG_EnableCompensationCell
  * @param  comp_cell This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref LL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  *         @arg @ref LL_SYSCFG_CCELL_ALL
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_SYSCFG_EnableCompensationCell(uint32_t comp_cell)
{
  ATOMIC_SET_BIT(SYSCFG->CCCSR, comp_cell);
}

/**
  * @brief  Disable the Compensation Cell.
  * @rmtoll CCCSR   ENX   X[1..3]    LL_SYSCFG_DisableCompensationCell
  * @param  comp_cell This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref LL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  *         @arg @ref LL_SYSCFG_CCELL_ALL
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_SYSCFG_DisableCompensationCell(uint32_t comp_cell)
{
  ATOMIC_CLEAR_BIT(SYSCFG->CCCSR, comp_cell);
}

/**
  * @brief  Check if the Compensation Cell is enable
  * @rmtoll CCCSR   ENx x=[1..3]    LL_SYSCFG_IsEnabledCompensationCell
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref LL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  * @note   (*) value not defined in all devices
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledCompensationCell(uint32_t comp_cell)
{
  return ((READ_BIT(SYSCFG->CCCSR, comp_cell) == comp_cell) ? 1U : 0U);
}

/**
  * @brief  Enable the Compensation Cell of GPIO supplied by VDD
  * @rmtoll
  *  CCCSR   EN1    LL_SYSCFG_EnableVddIOCompensationCell
  * @note   The vdd compensation cell can be used only when the device supply
  *         voltage ranges from 1.71 to 3.6 V
  */
__STATIC_INLINE void LL_SYSCFG_EnableVddIOCompensationCell(void)
{
  ATOMIC_SET_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_EN1);
}

/**
  * @brief  Disable the Compensation Cell of GPIO supplied by VDD
  * @rmtoll
  *  CCCSR   EN1    LL_SYSCFG_DisableVddIOCompensationCell
  * @note   The Vdd compensation cell can be used only when the device supply
  *         voltage ranges from 1.71 to 3.6 V
  */
__STATIC_INLINE void LL_SYSCFG_DisableVddIOCompensationCell(void)
{
  ATOMIC_CLEAR_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_EN1);
}

/**
  * @brief  Check if the Compensation Cell of GPIO supplied by VDD is enable
  * @rmtoll
  *  CCCSR   EN1    LL_SYSCFG_IsEnabled_VddIOCompensationCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabled_VddIOCompensationCell(void)
{
  return ((READ_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_EN1) == SYSCFG_CCCSR_EN1) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Compensation Cell of GPIO supplied by VDDIO2
  * @rmtoll
  *  CCCSR   EN2    LL_SYSCFG_EnableVddIO2CompensationCell
  * @note   The Vdd I/O compensation cell can be used only when the device supply
  *         voltage ranges from 1.08 to 3.6 V
  */
__STATIC_INLINE void LL_SYSCFG_EnableVddIO2CompensationCell(void)
{
  ATOMIC_SET_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_EN2);
}

/**
  * @brief  Disable the Compensation Cell of GPIO supplied by VDDIO2
  * @rmtoll
  *  CCCSR   EN2    LL_SYSCFG_DisableVddIO2CompensationCell
  * @note   The Vdd I/O compensation cell can be used only when the device supply
  *         voltage ranges from 1.08 to 3.6 V
  */
__STATIC_INLINE void LL_SYSCFG_DisableVddIO2CompensationCell(void)
{
  ATOMIC_CLEAR_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_EN2);
}

/**
  * @brief  Check if the Compensation Cell of GPIO supplied by VDDIO2 is enable
  * @rmtoll
  *  CCCSR   EN2   LL_SYSCFG_IsEnabled_VddIO2CompensationCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabled_VddIO2CompensationCell(void)
{
  return ((READ_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_EN2) == SYSCFG_CCCSR_EN2) ? 1UL : 0UL);
}

#if defined(SYSCFG_CCCSR_EN3)
/**
  * @brief  Enable the Compensation Cell of HSPI IO supplied by VDD
  * @rmtoll
  *  CCCSR   EN3    LL_SYSCFG_EnableVddHSPICompensationCell
  */
__STATIC_INLINE void LL_SYSCFG_EnableVddHSPICompensationCell(void)
{
  ATOMIC_SET_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_EN3);
}

/**
  * @brief  Disable the Compensation Cell of HSPI IO supplied by VDD
  * @rmtoll
  *  CCCSR   EN3    LL_SYSCFG_DisableVddHSPICompensationCell
  */
__STATIC_INLINE void LL_SYSCFG_DisableVddHSPICompensationCell(void)
{
  ATOMIC_CLEAR_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_EN3);
}

/**
  * @brief  Check if the Compensation Cell of HSPI IO supplied by VDD is enable
  * @rmtoll
  *  CCCSR   EN3   LL_SYSCFG_IsEnabled_VddHSPICompensationCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabled_VddHSPICompensationCell(void)
{
  return ((READ_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_EN3) == SYSCFG_CCCSR_EN3) ? 1UL : 0UL);
}
#endif /* SYSCFG_CCCSR_EN3 */

/**
  * @brief  Get the PMOS transistor of the compensation cell value
  * @rmtoll CCVR    PCVx x=[1..3]   LL_SYSCFG_GetPMOSCompensationCellValue
  * @param  comp_cell The PMOS compensation cell
  * @retval Returned value of the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSCompensationCellValue(uint32_t comp_cell)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCVR, ((SYSCFG_CCVR_NCV1 << (POSITION_VAL(comp_cell << 1U) * 4U))))
                    >> (POSITION_VAL(comp_cell << 1U) * 4U));
}

/**
  * @brief  Get the NMOS transistor of the compensation cell value
  * @rmtoll CCVR    NCVx x=[1..3]   LL_SYSCFG_GetNMOSCompensationCellValue
  * @param  comp_cell The NMOS compensation cell
  * @retval Returned value of the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSCompensationCellValue(uint32_t comp_cell)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCVR, ((SYSCFG_CCVR_NCV1 << (POSITION_VAL(comp_cell) * 4U))))
                    >> (POSITION_VAL(comp_cell) * 4U));
}

/**
  * @brief  Get the compensation cell value of the GPIO PMOS transistor supplied by VDD
  * @rmtoll
  *  CCVR    PCV1   LL_SYSCFG_GetPMOSVddIOCompensationCellValue
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddIOCompensationCellValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCVR, SYSCFG_CCVR_PCV1));
}

/**
  * @brief  Get the compensation cell value of the GPIO NMOS transistor supplied by VDD
  * @rmtoll
  *  CCVR    NCV1   LL_SYSCFG_GetNMOSVddIOCompensationCellValue
  * @retval Returned value is the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddIOCompensationCellValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCVR, SYSCFG_CCVR_NCV1));
}

/**
  * @brief  Get the compensation cell value of the GPIO PMOS transistor supplied by VDDIO2
  * @rmtoll
  *  CCVR    PCV2   LL_SYSCFG_GetPMOSVddIO2CompensationCellValue
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddIO2CompensationCellValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCVR, SYSCFG_CCVR_PCV2));
}

/**
  * @brief  Get the compensation cell value of the GPIO NMOS transistor supplied by VDDIO2
  * @rmtoll
  *  CCVR    NCV2   LL_SYSCFG_GetNMOSVddIO2CompensationCellValue
  * @retval Returned value is the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddIO2CompensationCellValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCVR, SYSCFG_CCVR_NCV2));
}

#if defined(SYSCFG_CCVR_PCV3)
/**
  * @brief  Get the compensation cell value of the HSPI IO PMOS transistor supplied by VDD
  * @rmtoll
  *  CCVR    PCV3   LL_SYSCFG_GetPMOSVddHSPIIOCompensationCellValue
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddHSPIIOCompensationCellValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCVR, SYSCFG_CCVR_PCV3));
}

/**
  * @brief  Get the compensation cell value of the HSPI IO NMOS transistor supplied by VDD
  * @rmtoll
  *  CCVR    NCV3   LL_SYSCFG_GetNMOSVddHSPIIOCompensationCellValue
  * @retval Returned value is the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddHSPIIOCompensationCellValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCVR, SYSCFG_CCVR_NCV3));
}
#endif /* SYSCFG_CCVR_PCV3 */

/**
  * @brief  Set the compensation cell code of PMOS transistor
  * @rmtoll
  *  CCCR    PCC1   LL_SYSCFG_SetPMOSCompensationCellCode \n
  *  CCCR    PCC2   LL_SYSCFG_SetPMOSCompensationCellCode \n
  *  CCCR    PCC3   LL_SYSCFG_SetPMOSCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref LL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  * @param  pmos_code PMOS compensation code
  * @note   This code is applied to the PMOS compensation cell when the CSx x=[1..3] bits of the SYSCFG_CCCSR is set
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_SYSCFG_SetPMOSCompensationCellCode(uint32_t comp_cell, uint32_t pmos_code)
{
  ATOMIC_MODIFY_REG(SYSCFG->CCCR, (SYSCFG_CCCR_NCC1 << (POSITION_VAL(comp_cell << 1U) * 4U)),
                    (pmos_code << (POSITION_VAL(comp_cell << 1U) * 4U)));
}

/**
  * @brief  Get the compensation cell code of PMOS transistor
  * @rmtoll
  *  CCCR    PCC1   LL_SYSCFG_GetPMOSCompensationCellCode \n
  *  CCCR    PCC2   LL_SYSCFG_GetPMOSCompensationCellCode \n
  *  CCCR    PCC3   LL_SYSCFG_GetPMOSCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref LL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  * @note   This code is applied to the PMOS compensation cell when the CSx x=[1..3] bits of the SYSCFG_CCCSR is set
  * @note   (*) value not defined in all devices
  * @retval Returned value of the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSCompensationCellCode(uint32_t comp_cell)
{
  return (READ_BIT(SYSCFG->CCCR, (SYSCFG_CCCR_NCC1 << (POSITION_VAL(comp_cell << 1U) * 4U))));
}

/**
  * @brief  Set the compensation cell code of NMOS transistor
  * @rmtoll
  *  CCCR    NCC1   LL_SYSCFG_SetNMOSCompensationCellCode \n
  *  CCCR    NCC2   LL_SYSCFG_SetNMOSCompensationCellCode \n
  *  CCCR    NCC3   LL_SYSCFG_SetNMOSCompensationCellCode (*)
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref LL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  * @param  nmos_code NMOS compensation code
  * @note   This code is applied to the PMOS compensation cell when the CSx x=[1..3] bits of the SYSCFG_CCCSR is set
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_SYSCFG_SetNMOSCompensationCellCode(uint32_t comp_cell, uint32_t nmos_code)
{
  ATOMIC_MODIFY_REG(SYSCFG->CCCR, (SYSCFG_CCCR_NCC1 << (POSITION_VAL(comp_cell) * 4U)),
                    (nmos_code << (POSITION_VAL(comp_cell) * 4U)));
}

/**
  * @brief  Get the NMOS transistor of the compensation cell value
  * @rmtoll
  *  CCCR    PCC1   LL_SYSCFG_GetNMOSCompensationCellCode \n
  *  CCCR    PCC2   LL_SYSCFG_GetNMOSCompensationCellCode \n
  *  CCCR    PCC3   LL_SYSCFG_GetNMOSCompensationCellCode (*)
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO
  *         @arg @ref LL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref LL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  * @note   (*) value not defined in all devices
  * @note   This code is applied to the NMOS compensation cell when the CSx x=[1..3] bits of the SYSCFG_CCCSR is set
  * @retval Returned value of the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSCompensationCellCode(uint32_t comp_cell)
{
  return (READ_BIT(SYSCFG->CCCR, (SYSCFG_CCCR_NCC1 << (POSITION_VAL(comp_cell) * 4U))));
}

/**
  * @brief  Set the compensation cell code of the GPIO PMOS and NMOS transistor supplied by VDD
  * @rmtoll
  *  CCCR    NCC1  LL_SYSCFG_SetxMOSVddIOCompensationCellCode \n
  *  CCCR    PCC1  LL_SYSCFG_SetxMOSVddIOCompensationCellCode
  * @param  pmos_code PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS1 bit of the
  *         SYSCFG_CCCSR is set
  * @param  nmos_code NMOS compensation code
  */
__STATIC_INLINE void LL_SYSCFG_SetxMOSVddIOCompensationCellCode(uint32_t pmos_code, uint32_t nmos_code)
{
  MODIFY_REG(SYSCFG->CCCR, (SYSCFG_CCCR_PCC1 | SYSCFG_CCCR_NCC1), ((pmos_code << SYSCFG_CCCR_PCC1_Pos) | \
                                                                   (nmos_code << SYSCFG_CCCR_NCC1_Pos)));
}

/**
  * @brief  Set the compensation cell code of the GPIO PMOS and NMOS transistor supplied by VDD
  * @rmtoll
  *  CCCR    NCC2  LL_SYSCFG_SetxMOSVddIO2CompensationCellCode \n
  *  CCCR    PCC2  LL_SYSCFG_SetxMOSVddIO2CompensationCellCode
  * @param  pmos_code PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS2 bit of the
  *         SYSCFG_CCCSR is set
  * @param  nmos_code NMOS compensation code
  */
__STATIC_INLINE void LL_SYSCFG_SetxMOSVddIO2CompensationCellCode(uint32_t pmos_code, uint32_t nmos_code)
{
  MODIFY_REG(SYSCFG->CCCR, (SYSCFG_CCCR_PCC2 | SYSCFG_CCCR_NCC2), ((pmos_code << SYSCFG_CCCR_PCC2_Pos) | \
                                                                   (nmos_code << SYSCFG_CCCR_NCC2_Pos)));
}

#if defined(SYSCFG_CCCR_PCC3)
/**
  * @brief  Set the compensation cell code of the GPIO PMOS and NMOS transistor supplied by VDDIO2
  * @rmtoll
  *  CCCR    NCC3  LL_SYSCFG_SetxMOSVddHSPIIOCompensationCellCode \n
  *  CCCR    PCC3  LL_SYSCFG_SetxMOSVddHSPIIOCompensationCellCode
  * @param  pmos_code PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS3 bit of the
  *         SYSCFG_CCCSR is set
  * @param  nmos_code NMOS compensation code
  */
__STATIC_INLINE void LL_SYSCFG_SetxMOSVddHSPIIOCompensationCellCode(uint32_t pmos_code, uint32_t nmos_code)
{
  MODIFY_REG(SYSCFG->CCCR, (SYSCFG_CCCR_PCC3 | SYSCFG_CCCR_NCC3), ((pmos_code << SYSCFG_CCCR_PCC3_Pos) | \
                                                                   (nmos_code << SYSCFG_CCCR_NCC3_Pos)));
}
#endif /* SYSCFG_CCCR_PCC3 */

/**
  * @brief  Set the compensation cell code of the GPIO PMOS transistor supplied by VDD
  * @rmtoll
  *  CCCR    PCC1  LL_SYSCFG_SetPMOSVddIOCompensationCellCode
  * @param  pmos_code PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS1 bit of the
  *         SYSCFG_CCCSR is set
  */
__STATIC_INLINE void LL_SYSCFG_SetPMOSVddIOCompensationCellCode(uint32_t pmos_code)
{
  MODIFY_REG(SYSCFG->CCCR, SYSCFG_CCCR_PCC1, pmos_code << SYSCFG_CCCR_PCC1_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO PMOS transistor supplied by VDD
  * @rmtoll
  *  CCCR    PCC1   LL_SYSCFG_GetPMOSVddIOCompensationCellCode
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddIOCompensationCellCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCCR, SYSCFG_CCCR_PCC1));
}

/**
  * @brief  Set the compensation cell code of the GPIO NMOS transistor supplied by VDD
  * @rmtoll
  *  CCCR    PCC2  LL_SYSCFG_SetNMOSVddIOCompensationCellCode
  * @param  nmos_code NMOS compensation code
  *         This code is applied to the NMOS compensation cell when the CS2 bit of the
  *         SYSCFG_CMPCR is set
  */
__STATIC_INLINE void LL_SYSCFG_SetNMOSVddIOCompensationCellCode(uint32_t nmos_code)
{
  MODIFY_REG(SYSCFG->CCCR, SYSCFG_CCCR_NCC1, nmos_code << SYSCFG_CCCR_NCC1_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO NMOS transistor supplied by VDD
  * @rmtoll
  *  CCCR    NCC1   LL_SYSCFG_GetNMOSVddIOCompensationCellCode
  * @retval Returned value is the Vdd compensation cell code for NMOS transistors
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddIOCompensationCellCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCCR, SYSCFG_CCCR_NCC1));
}

/**
  * @brief  Set the compensation cell code of the GPIO PMOS transistor supplied by VDDIO2
  * @rmtoll
  *  CCCR    PCC2  LL_SYSCFG_SetPMOSVddIO2CompensationCellCode
  * @param  pmos_code PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS2 bit of the
  *         SYSCFG_CCCSR is set
  */
__STATIC_INLINE void LL_SYSCFG_SetPMOSVddIO2CompensationCellCode(uint32_t pmos_code)
{
  MODIFY_REG(SYSCFG->CCCR, SYSCFG_CCCR_PCC2, pmos_code << SYSCFG_CCCR_PCC2_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO PMOS transistor supplied by VDDIO2
  * @rmtoll
  *  CCCR    PCC2   LL_SYSCFG_GetPMOSVddIO2CompensationCellCode
  * @retval Returned value is the PMOS compensation
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddIO2CompensationCellCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCCR, SYSCFG_CCCR_PCC2));
}

/**
  * @brief  Set the compensation cell code of the GPIO NMOS transistor supplied by VDDIO2
  * @rmtoll
  *  CCCR    NCC2  LL_SYSCFG_SetNMOSVddIO2CompensationCellCode
  * @param  nmos_code NMOS compensation code
  *         This code is applied to the NMOS compensation cell when the CS2 bit of the
  *         SYSCFG_CMPCR is set
  */
__STATIC_INLINE void LL_SYSCFG_SetNMOSVddIO2CompensationCellCode(uint32_t nmos_code)
{
  MODIFY_REG(SYSCFG->CCCR, SYSCFG_CCCR_NCC2, nmos_code << SYSCFG_CCCR_NCC2_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO NMOS transistor supplied by VDDIO2
  * @rmtoll
  *  CCCR    NCC2   LL_SYSCFG_GetNMOSVddIO2CompensationCellCode
  * @retval Returned value is the NMOS compensation cell code
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddIO2CompensationCellCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCCR, SYSCFG_CCCR_NCC2));
}

#if defined(SYSCFG_CCCR_PCC3)
/**
  * @brief  Set the compensation cell code of the HSPI IO PMOS transistor supplied by VDD
  * @rmtoll
  *  CCCR    PCC3  LL_SYSCFG_SetPMOSVddHSPIIOCompensationCellCode
  * @param  pmos_code PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS3 bit of the
  *         SYSCFG_CCCSR is set
  */
__STATIC_INLINE void LL_SYSCFG_SetPMOSVddHSPIIOCompensationCellCode(uint32_t pmos_code)
{
  MODIFY_REG(SYSCFG->CCCR, SYSCFG_CCCR_PCC3, pmos_code << SYSCFG_CCCR_PCC3_Pos);
}

/**
  * @brief  Get the compensation cell code of the HSPI IO PMOS transistor supplied by VDD
  * @rmtoll
  *  CCCR    PCC3   LL_SYSCFG_GetPMOSVddHSPIIOCompensationCellCode
  * @retval Returned value is the PMOS compensation
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddHSPIIOCompensationCellCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCCR, SYSCFG_CCCR_PCC3));
}

/**
  * @brief  Set the compensation cell code of the HSPI IO NMOS transistor supplied by VDD
  * @rmtoll
  *  CCCR    NCC3  LL_SYSCFG_SetNMOSVddHSPIIOCompensationCellCode
  * @param  nmos_code NMOS compensation code
  *         This code is applied to the NMOS compensation cell when the CS3 bit of the
  *         SYSCFG_CCCSR is set
  */

__STATIC_INLINE void LL_SYSCFG_SetNMOSVddHSPIIOCompensationCellCode(uint32_t nmos_code)
{
  MODIFY_REG(SYSCFG->CCCR, SYSCFG_CCCR_NCC3, nmos_code << SYSCFG_CCCR_NCC3_Pos);
}

/**
  * @brief  Get the compensation cell code of the HSPI IO NMOS transistor supplied by VDD
  * @rmtoll
  *  CCCR    NCC3   LL_SYSCFG_GetNMOSVddHSPIIOCompensationCellCode
  * @retval Returned value is the NMOS compensation cell code
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddHSPIIOCompensationCellCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CCCR, SYSCFG_CCCR_NCC3));
}
#endif /* SYSCFG_CCCR_PCC3 */

/**
  * @brief  Get Compensation Cell ready Flag of GPIO supplied by VDD
  * @rmtoll
  *  CCCSR   RDY1   LL_SYSCFG_IsActiveFlag_RDY1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_RDY1(void)
{
  return ((READ_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_RDY1) == (SYSCFG_CCCSR_RDY1)) ? 1UL : 0UL);
}

/**
  * @brief  Get Compensation Cell ready Flag of GPIO supplied by VDDIO2
  * @rmtoll
  *  CCCSR   RDY2   LL_SYSCFG_IsActiveFlag_RDY2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_RDY2(void)
{
  return ((READ_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_RDY2) == (SYSCFG_CCCSR_RDY2)) ? 1UL : 0UL);
}

#if defined(SYSCFG_CCCSR_RDY3)
/**
  * @brief  Get Compensation Cell ready Flag of HSPI IO supplied by VDD
  * @rmtoll
  *  CCCSR   RDY3   LL_SYSCFG_IsActiveFlag_RDY3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_RDY3(void)
{
  return ((READ_BIT(SYSCFG->CCCSR, SYSCFG_CCCSR_RDY3) == (SYSCFG_CCCSR_RDY3)) ? 1UL : 0UL);
}
#endif /* SYSCFG_CCCSR_RDY3 */

/**
  * @}
  */

/** @defgroup SYSCFG_LL_EF_USB_HS_PHY SYSCFG USB HS PHY
  * @{
  */

#if defined(SYSCFG_OTGHSPHYCR_EN)
/**
  * @brief  Enable the USB HS PHY feature.
  * @rmtoll
  *  OTGHSPHYCR    EN   LL_SYSCFG_EnableUSBHSPHY
  */
__STATIC_INLINE void LL_SYSCFG_EnableUSBHSPHY(void)
{
  SET_BIT(SYSCFG->OTGHSPHYCR, SYSCFG_OTGHSPHYCR_EN);
}

/**
  * @brief  Disable the USB HS PHY feature.
  * @rmtoll
  *  OTGHSPHYCR    EN   LL_SYSCFG_DisableUSBHSPHY
  */
__STATIC_INLINE void LL_SYSCFG_DisableUSBHSPHY(void)
{
  CLEAR_BIT(SYSCFG->OTGHSPHYCR, SYSCFG_OTGHSPHYCR_EN);
}

/**
  * @brief  Check that USB HS PHY is enabled.
  * @rmtoll
  *  OTGHSPHYCR    EN   LL_SYSCFG_IsEnabledUSBHSPHY
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledUSBHSPHY(void)
{
  return ((READ_BIT(SYSCFG->OTGHSPHYCR, SYSCFG_OTGHSPHYCR_EN) == (SYSCFG_OTGHSPHYCR_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the USB HS PHY  Power-Down control.
  * @rmtoll
  *  OTGHSPHYCR    PDCTRL   LL_SYSCFG_EnableUSBHSPHYPowerDown
  */
__STATIC_INLINE void LL_SYSCFG_EnableUSBHSPHYPowerDown(void)
{
  CLEAR_BIT(SYSCFG->OTGHSPHYCR, SYSCFG_OTGHSPHYCR_PDCTRL);
}

/**
  * @brief  Disable the USB HS PHY  Power-Down control.
  * @rmtoll
  *  OTGHSPHYCR    PDCTRL   LL_SYSCFG_DisableUSBHSPHYPowerDown
  */
__STATIC_INLINE void LL_SYSCFG_DisableUSBHSPHYPowerDown(void)
{
  SET_BIT(SYSCFG->OTGHSPHYCR, SYSCFG_OTGHSPHYCR_PDCTRL);
}

/**
  * @brief  Check that USB HS PHY power-down is enabled.
  * @rmtoll
  *  OTGHSPHYCR    EN   LL_SYSCFG_IsEnabledUSBHSPHYPowerDown
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledUSBHSPHYPowerDown(void)
{
  return ((READ_BIT(SYSCFG->OTGHSPHYCR, SYSCFG_OTGHSPHYCR_PDCTRL) == (SYSCFG_OTGHSPHYCR_PDCTRL)) ? 1UL : 0UL);
}

/**
  * @brief  Set the USB HS PHY reference clock frequency selection.
  * @rmtoll
  *  OTGHSPHYCR   CLKSEL    LL_SYSCFG_SetUSBHSPHYReferenceClockFrequency
  * @param  clk_frequency This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_USBHSPHY_16MHZ
  *         @arg @ref LL_SYSCFG_USBHSPHY_19_2MHZ
  *         @arg @ref LL_SYSCFG_USBHSPHY_20MHZ
  *         @arg @ref LL_SYSCFG_USBHSPHY_24MHZ
  *         @arg @ref LL_SYSCFG_USBHSPHY_26MHZ
  *         @arg @ref LL_SYSCFG_USBHSPHY_32MHZ
  */
__STATIC_INLINE void LL_SYSCFG_SetUSBHSPHYReferenceClockFrequency(uint32_t clk_frequency)
{
  MODIFY_REG(SYSCFG->OTGHSPHYCR, SYSCFG_OTGHSPHYCR_CLKSEL, clk_frequency);
}

/**
  * @brief  Get the USB HS PHY reference clock frequency selection.
  * @rmtoll
  *  OTGHSPHYCR    CLKSEL   LL_SYSCFG_GetUSBHSPHYReferenceClockFrequency
  * @retval Returned the current applied reference clock frequency selection
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetUSBHSPHYReferenceClockFrequency(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->OTGHSPHYCR, SYSCFG_OTGHSPHYCR_CLKSEL));
}
#endif /* SYSCFG_OTGHSPHYCR_EN */

#if defined(SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE)

/**
  * @brief  Set all USB HS PHY tune in same time.
  * @rmtoll
  *  OTGHSPHYTUNER2   COMPDISTUNE       LL_SYSCFG_SetConfigUSBHSPHY \n
  *  OTGHSPHYTUNER2   SQRXTUNE          LL_SYSCFG_SetConfigUSBHSPHY \n
  *  OTGHSPHYTUNER2   TXPREEMPAMPTUNE   LL_SYSCFG_SetConfigUSBHSPHY
  * @param  disconnect_threshold This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_DIS_ADJUST_0_PERCENT
  *         @arg @ref LL_SYSCFG_DIS_ADJUST_PLUS_5_9_PERCENT
  * @param  squelch_threshold This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_SQUELCH_ADJUST_0_PERCENT
  *         @arg @ref LL_SYSCFG_SQUELCH_ADJUST_PLUS_15_PERCENT
  * @param  src_current This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_SRC_CURRENT_NO
  *         @arg @ref LL_SYSCFG_SRC_CURRENT_1
  *         @arg @ref LL_SYSCFG_SRC_CURRENT_2
  *         @arg @ref LL_SYSCFG_SRC_CURRENT_3
  */
__STATIC_INLINE void LL_SYSCFG_SetConfigUSBHSPHY(uint32_t disconnect_threshold,
                                                 uint32_t squelch_threshold,
                                                 uint32_t src_current)
{
  MODIFY_REG(SYSCFG->OTGHSPHYTUNER2, \
             (SYSCFG_OTGHSPHYTUNER2_TXPREEMPAMPTUNE | SYSCFG_OTGHSPHYTUNER2_SQRXTUNE |
              SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE),
             (src_current | squelch_threshold | disconnect_threshold));
}

/**
  * @brief  Set the USB PHY disconnect threshold adjustment.
  * @rmtoll
  *  OTGHSPHYTUNER2    COMPDISTUNE  LL_SYSCFG_SetUSBHSPHYDisconnectThresholdAdjustment
  * @param  disconnect_threshold This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_DIS_ADJUST_0_PERCENT
  *         @arg @ref LL_SYSCFG_DIS_ADJUST_PLUS_5_9_PERCENT
  */
__STATIC_INLINE void LL_SYSCFG_SetUSBHSPHYDisconnectThresholdAdjustment(uint32_t disconnect_threshold)
{
  MODIFY_REG(SYSCFG->OTGHSPHYTUNER2, SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE, disconnect_threshold);
}

/**
  * @brief  Get the USB PHY disconnect threshold adjustment.
  * @rmtoll
  *  OTGHSPHYTUNER2    COMPDISTUNE  LL_SYSCFG_GetUSBHSPHYDisconnectThresholdAdjustment
  * @retval Returned value can be one of the following values:
  *   @arg LL_SYSCFG_SQUELCH_ADJUST_0_PERCENT : 0 %
  *   @arg LL_SYSCFG_SQUELCH_ADJUST_PLUS_15_PERCENT: +15%
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetUSBHSPHYDisconnectThresholdAdjustment(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->OTGHSPHYTUNER2, SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE));
}
#endif /* SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE */

#if defined(SYSCFG_OTGHSPHYTUNER2_SQRXTUNE)
/**
  * @brief  Set the USB HS PHY squelch threshold adjustment.
  * @rmtoll
  *  OTGHSPHYTUNER2    SQRXTUNE  LL_SYSCFG_SetUSBHSPHYSquelchThresholdAdjustment
  * @param  squelch_threshold This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_SQUELCH_ADJUST_0_PERCENT
  *         @arg @ref LL_SYSCFG_SQUELCH_ADJUST_PLUS_15_PERCENT
  */
__STATIC_INLINE void LL_SYSCFG_SetUSBHSPHYSquelchThresholdAdjustment(uint32_t squelch_threshold)
{
  MODIFY_REG(SYSCFG->OTGHSPHYTUNER2, SYSCFG_OTGHSPHYTUNER2_SQRXTUNE, squelch_threshold);
}

/**
  * @brief  Get the USB PHY squelch threshold adjustment.
  * @rmtoll
  *  OTGHSPHYTUNER2    SQRXTUNE  LL_SYSCFG_GetUSBHSPHYSquelchThresholdAdjustment
  * @retval Returned value can be one of the following values:
  *   @arg LL_SYSCFG_SQUELCH_ADJUST_0_PERCENT : 0 %
  *   @arg LL_SYSCFG_SQUELCH_ADJUST_PLUS_15_PERCENT: +15%
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetUSBHSPHYSquelchThresholdAdjustment(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->OTGHSPHYTUNER2, SYSCFG_OTGHSPHYTUNER2_SQRXTUNE));
}
#endif /* SYSCFG_OTGHSPHYTUNER2_SQRXTUNE */

#if defined(SYSCFG_OTGHSPHYTUNER2_TXPREEMPAMPTUNE)
/**
  * @brief  Set the USB HS PHY transmitter preemphasis current.
  * @rmtoll
  *  OTGHSPHYTUNER2    TXPREEMPAMPTUNE  LL_SYSCFG_SetUSBHSPHYTransmitterPreemphasisCurrent
  * @param  src_current This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_SRC_CURRENT_NO
  *         @arg @ref LL_SYSCFG_SRC_CURRENT_1
  *         @arg @ref LL_SYSCFG_SRC_CURRENT_2
  *         @arg @ref LL_SYSCFG_SRC_CURRENT_3
  */
__STATIC_INLINE void LL_SYSCFG_SetUSBHSPHYTransmitterPreemphasisCurrent(uint32_t src_current)
{
  MODIFY_REG(SYSCFG->OTGHSPHYTUNER2, SYSCFG_OTGHSPHYTUNER2_TXPREEMPAMPTUNE, src_current);
}

/**
  * @brief  Set the USB HS PHY transmitter preemphasis current.
  * @rmtoll
  *  OTGHSPHYTUNER2    TXPREEMPAMPTUNE  LL_SYSCFG_GetUSBHSPHYTransmitterPreemphasisCurrent
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_SRC_CURRENT_NO
  *         @arg @ref LL_SYSCFG_SRC_CURRENT_1
  *         @arg @ref LL_SYSCFG_SRC_CURRENT_2
  *         @arg @ref LL_SYSCFG_SRC_CURRENT_3
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetUSBHSPHYTransmitterPreemphasisCurrent(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->OTGHSPHYTUNER2, SYSCFG_OTGHSPHYTUNER2_TXPREEMPAMPTUNE));
}
#endif /* SYSCFG_OTGHSPHYTUNER2_TXPREEMPAMPTUNE */

/**
  * @}
  */

/** @defgroup SYSCFG_LL_EF_ERASE_MEMORIE_STATUS SYSCFG ERASE MEMORIE STATUS
  * @{
  */

/**
  * @brief  Clear Status of End of Erase for ICACHE and PKA RAMs
  * @rmtoll
  *  MESR   IPMEE    LL_SYSCFG_ClearFlag_IPMEE
  */
__STATIC_INLINE void LL_SYSCFG_ClearFlag_IPMEE(void)
{
  SET_BIT(SYSCFG->MESR, SYSCFG_MESR_IPMEE);
}

/**
  * @brief  Get Status of End of Erase for ICACHE and PKA RAMs
  * @rmtoll
  *  MESR   IPMEE    LL_SYSCFG_IsActiveFlag_IPEE
  * @retval Returned value can be one of the following values:
  *   @arg LL_SYSCFG_IPMEE_ERASE_ON_GOING : Erase of memories not yet done
  *   @arg LL_SYSCFG_IPMEE_ERASE_ENDED: Erase of memories ended
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_IPEE(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->MESR, SYSCFG_MESR_IPMEE));
}

/**
  * @brief  Clear Status of End of Erase after reset  for SRAM2, BKPRAM, ICACHE, DCACHE,PKA rams
  * @rmtoll
  *  MESR   MCLR    LL_SYSCFG_ClearFlag_MCLR
  */
__STATIC_INLINE void LL_SYSCFG_ClearFlag_MCLR(void)
{
  SET_BIT(SYSCFG->MESR, SYSCFG_MESR_MCLR);
}

/**
  * @brief  Get Status of End of Erase after reset  for SRAM2, BKPRAM, ICACHE, DCACHE,PKA rams
  * @rmtoll
  *  MESR   MCLR    LL_SYSCFG_IsActiveFlag_MCLR
  * @retval Returned value can be one of the following values:
  *   @arg LL_SYSCFG_MCLR_ERASE_ON_GOING : Erase of memories not yet done
  *   @arg LL_SYSCFG_MCLR_ERASE_ENDED: Erase of memories ended
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_MCLR(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->MESR, SYSCFG_MESR_MCLR));
}
/**
  * @}
  */

/** @defgroup SYSCFG_LL_EF_SYSCFG_Secure_Management Secure Management
  * @{
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Configure Secure mode
  * @rmtoll
  *  SECCFGR     SYSCFGSEC     LL_SYSCFG_ConfigSecurity \n
  *  SECCFGR     CLASSBSEC     LL_SYSCFG_ConfigSecurity \n
  *  SECCFGR     FPUSEC        LL_SYSCFG_ConfigSecurity
  * @param  configuration This parameter must be the full combination
  *         of the following values:
  *         @arg @ref LL_SYSCFG_CLOCK_SEC or LL_SYSCFG_CLOCK_NSEC
  *         @arg @ref LL_SYSCFG_CLASSB_SEC or LL_SYSCFG_CLASSB_NSEC
  *         @arg @ref LL_SYSCFG_FPU_SEC or LL_SYSCFG_FPU_NSEC
  * @note   Only available from secure state when system implements security (TZEN=1)
  */
__STATIC_INLINE void LL_SYSCFG_ConfigSecurity(uint32_t configuration)
{
  WRITE_REG(SYSCFG->SECCFGR, configuration);
}
#endif /* __ARM_FEATURE_CMSE && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Get Secure mode configuration
  * @rmtoll
  *  SECCFGR     SYSCFGSEC     LL_SYSCFG_GetConfigSecurity \n
  *  SECCFGR     CLASSBSEC     LL_SYSCFG_GetConfigSecurity \n
  *  SECCFGR     FPUSEC        LL_SYSCFG_GetConfigSecurity
  * @note   Only available when system implements security (TZEN=1)
  * @retval Returned value is the combination of the following values:
  *         @arg @ref LL_SYSCFG_CLOCK_SEC or LL_SYSCFG_CLOCK_NSEC
  *         @arg @ref LL_SYSCFG_CLASSB_SEC or LL_SYSCFG_CLASSB_NSEC
  *         @arg @ref LL_SYSCFG_FPU_SEC or LL_SYSCFG_FPU_NSEC
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetConfigSecurity(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->SECCFGR, 0xBU));
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Lock the SAU registers
  * @rmtoll
  *  CSLCKR     LOCKSAU        LL_SYSCFG_LockSAU
  * @note   Only available from secure state when system implements security (TZEN=1)
  */
__STATIC_INLINE void LL_SYSCFG_LockSAU(void)
{
  SET_BIT(SYSCFG->CSLCKR, SYSCFG_CSLCKR_LOCKSAU);
}

/**
  * @brief  Check if the SAU registers are locked or unlocked
  * @rmtoll
  *  CSLCKR    LOCKSAU   LL_SYSCFG_IsLockedSAU
  * @note   Only available from secure state when system implements security (TZEN=1)
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsLockedSAU(void)
{
  return ((READ_BIT(SYSCFG->CSLCKR, SYSCFG_CSLCKR_LOCKSAU) == (SYSCFG_CSLCKR_LOCKSAU)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Lock the MPU registers
  * @rmtoll
  *  CSLCKR      LOCKSMPU        LL_SYSCFG_LockMPU \n
  *  CNSLCKR     LOCKNSMPU       LL_SYSCFG_LockMPU
  * @note   Setting lock secure MPU depends on the privilege mode in secure/non-secure code
  */
__STATIC_INLINE void LL_SYSCFG_LockMPU(void)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(SYSCFG->CSLCKR, SYSCFG_CSLCKR_LOCKSMPU);
#else
  SET_BIT(SYSCFG->CNSLCKR, SYSCFG_CNSLCKR_LOCKNSMPU);
#endif /* __ARM_FEATURE_CMSE */
}

/**
  * @brief  Check if the MPU registers are locked or unlocked
  * @rmtoll
  *  CSLCKR     LOCKSMPU   LL_SYSCFG_IsLockedMPU \n
  *  CNSLCKR    LOCKNSMPU  LL_SYSCFG_IsLockedMPU
  * @note   Setting lock MPU depends on privilege mode in secure/non-secure code
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsLockedMPU(void)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(SYSCFG->CSLCKR, SYSCFG_CSLCKR_LOCKSMPU) == (SYSCFG_CSLCKR_LOCKSMPU)) ? 1UL : 0UL);
#else
  return ((READ_BIT(SYSCFG->CNSLCKR, SYSCFG_CNSLCKR_LOCKNSMPU) == (SYSCFG_CNSLCKR_LOCKNSMPU)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Lock the non-secure MPU registers
  * @rmtoll
  *  CNSLCKR      LOCKNSMPU        LL_SYSCFG_LockMPU_NS
  * @note   Setting lock non-secure MPU depends on privilege mode in secure/non-secure code
  */
__STATIC_INLINE void LL_SYSCFG_LockMPU_NS(void)
{
  SET_BIT(SYSCFG->CNSLCKR, SYSCFG_CNSLCKR_LOCKNSMPU);
}

/**
  * @brief  Check if the non-secure MPU registers are locked or unlocked
  * @rmtoll
  *  CNSLCKR    LOCKNSMPU   LL_SYSCFG_IsLockedMPU_NS
  * @note   Setting lock non-secure MPU depends on privilege mode in secure/non-secure code
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsLockedMPU_NS(void)
{
  return ((READ_BIT(SYSCFG->CNSLCKR, SYSCFG_CNSLCKR_LOCKNSMPU) == (SYSCFG_CNSLCKR_LOCKNSMPU)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Lock  the secure/ non-secure VTOR register
  * @rmtoll
  *  CSLCKR      LOCKSVTAIRCR        LL_SYSCFG_LockVTOR \n
  *  CNSLCKR     LOCKNSVTAIRCR       LL_SYSCFG_LockVTOR
  * @note   Setting lock secure VTOR depends on privilege mode in secure/non-secure code
  */
__STATIC_INLINE void LL_SYSCFG_LockVTOR(void)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(SYSCFG->CSLCKR, SYSCFG_CSLCKR_LOCKSVTAIRCR);
#else
  SET_BIT(SYSCFG->CNSLCKR, SYSCFG_CNSLCKR_LOCKNSVTOR);
#endif /* __ARM_FEATURE_CMSE */
}

/**
  * @brief  Check if the VTOR register is locked or unlocked
  * @rmtoll
  *  CSLCKR     LOCKSVTAIRCR   LL_SYSCFG_IsLockedVTOR \n
  *  CNSLCKR    LOCKNSVTOR     LL_SYSCFG_IsLockedVTOR
  * @note   Setting lock VTOR depends on privilege mode in secure/non-secure code
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsLockedVTOR(void)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(SYSCFG->CSLCKR, SYSCFG_CSLCKR_LOCKSVTAIRCR) == (SYSCFG_CSLCKR_LOCKSVTAIRCR)) ? 1UL : 0UL);
#else
  return ((READ_BIT(SYSCFG->CNSLCKR, SYSCFG_CNSLCKR_LOCKNSVTOR) == (SYSCFG_CNSLCKR_LOCKNSVTOR)) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Lock the non-secure VTOR register
  * @rmtoll
  *  CNSLCKR      LOCKNSVTOR        LL_SYSCFG_LockVTOR_NS
  * @note   Setting lock VTOR non-secure depends on privilege mode in secure/non-secure code
  */
__STATIC_INLINE void LL_SYSCFG_LockVTOR_NS(void)
{
  SET_BIT(SYSCFG->CNSLCKR, SYSCFG_CNSLCKR_LOCKNSVTOR);
}

/**
  * @brief  Check if the non-secure VTOR is locked or unlocked
  * @rmtoll
  *  CNSLCKR    LOCKNSVTOR   LL_SYSCFG_IsLockedVTOR_NS
  * @note   Setting lock non-secure VTOR depends on privilege mode in secure/non-secure code
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsLockedVTOR_NS(void)
{
  return ((READ_BIT(SYSCFG->CNSLCKR, SYSCFG_CNSLCKR_LOCKNSVTOR) == (SYSCFG_CNSLCKR_LOCKNSVTOR)) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */

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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_LL_SYSCFG_H */
