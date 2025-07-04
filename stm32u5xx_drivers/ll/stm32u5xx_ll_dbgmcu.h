/**
  **********************************************************************************************************************
  * @file    stm32u5xx_ll_dbgmcu.h
  * @brief   Header file of LL dbgmcu module.
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
#ifndef STM32U5XX_LL_DBGMCU_H
#define STM32U5XX_LL_DBGMCU_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

/** @defgroup LL_DBGMCU LL DBGMCU
  * @{
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/

/** @defgroup DBGMCU_LL_Exported_Constants DBGMCU Exported Constants
  * @{
  */

/** @defgroup DBGMCU_DEV_ID DBGMCU Device ID definition
  * @{
  */
#define LL_DBGMCU_DEV_ID_U5F5_U5G5 0x0476U /*!< STM32U5 series device STM32U5Fx/5Gx */
#define LL_DBGMCU_DEV_ID_U595_U5A5 0x0481U /*!< STM32U5 series device STM32U59x/5Ax */
#define LL_DBGMCU_DEV_ID_U575_U585 0x0482U /*!< STM32U5 series device STM32U575/585 */
#define LL_DBGMCU_DEV_ID_U535_U545 0x0455U /*!< STM32U5 series device STM32U535/545 */
/**
  * @}
  */

/** @defgroup DBGMCU_REV_ID DBGMCU Device revision ID definition
  * @{
  */
#define LL_DBGMCU_REV_ID_A 0x1000U /*!< STM32U5 device revision A                              */
#define LL_DBGMCU_REV_ID_B 0x2000U /*!< STM32U5 device revision B                              */
#define LL_DBGMCU_REV_ID_C 0x3000U /*!< STM32U5 device revision C                              */
#define LL_DBGMCU_REV_ID_X 0x2001U /*!< STM32U5 device revision X (for devices: STM32U575/585) */

#if defined(STM32U595xx) || defined(STM32U5A9xx)
#define LL_DBGMCU_REV_ID_Y 0x2001U /*!< STM32U5 device revision Y (for devices: STM32U59x/5Ax) */
#else
#define LL_DBGMCU_REV_ID_Y 0x1003U /*!< STM32U5 device revision Y (for devices: STM32U575/585) */
#endif  /* DBGMCU_APB1FZR2_DBG_I2C5_STOP */

#define LL_DBGMCU_REV_ID_Z 0x1001U /*!< STM32U5 device revision Z (for devices: STM32U575/585) */

/**
  * @}
  */

/** @defgroup DBGMCU_DEBUG_LOW_POWER_MODE DBGMCU Debug low power mode
  * @{
  */
#define LL_DBGMCU_STOP_MODE_DEBUG    DBGMCU_CR_DBG_STOP    /*!< Debug during Stop0/1/2 mode */
#define LL_DBGMCU_STANDBY_MODE_DEBUG DBGMCU_CR_DBG_STANDBY /*!< Debug during Standby mode   */
#define LL_DBGMCU_LP_MODE_DEBUG_ALL  (DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_STANDBY)
/*!< Debug during Low power mode
 (Stop0/1/2 and Standby modes)   */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB1_GRP1_STOP_IP DBGMCU APB1 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_TIM2_STOP DBGMCU_APB1FZR1_DBG_TIM2_STOP /*!< The counter clock of TIM2 is stopped when the core
                                                                      is halted */
#define LL_DBGMCU_TIM3_STOP DBGMCU_APB1FZR1_DBG_TIM3_STOP /*!< The counter clock of TIM3 is stopped when the core
                                                                      is halted */
#define LL_DBGMCU_TIM4_STOP DBGMCU_APB1FZR1_DBG_TIM4_STOP /*!< The counter clock of TIM4 is stopped when the core
                                                                      is halted */
#define LL_DBGMCU_TIM5_STOP DBGMCU_APB1FZR1_DBG_TIM5_STOP /*!< The counter clock of TIM5 is stopped when the core
                                                                      is halted */
#define LL_DBGMCU_TIM6_STOP DBGMCU_APB1FZR1_DBG_TIM6_STOP /*!< The counter clock of TIM6 is stopped when the core
                                                                      is halted */
#define LL_DBGMCU_TIM7_STOP DBGMCU_APB1FZR1_DBG_TIM7_STOP /*!< The counter clock of TIM7 is stopped when the core
                                                                      is halted */
#define LL_DBGMCU_WWDG_STOP DBGMCU_APB1FZR1_DBG_WWDG_STOP /*!< The window watchdog counter clock is stopped when
                                                                      the core is halted      */
#define LL_DBGMCU_IWDG_STOP DBGMCU_APB1FZR1_DBG_IWDG_STOP /*!< The independent watchdog counter clock is stopped
                                                                      when the core is halted */
#define LL_DBGMCU_I2C1_STOP DBGMCU_APB1FZR1_DBG_I2C1_STOP /*!< The I2C1 SMBus timeout is frozen */
#define LL_DBGMCU_I2C2_STOP DBGMCU_APB1FZR1_DBG_I2C2_STOP /*!< The I2C2 SMBus timeout is frozen */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB1_GRP2_STOP_IP DBGMCU APB1 GRP2 STOP IP
  * @{
  */
#define LL_DBGMCU_I2C4_STOP     DBGMCU_APB1FZR2_DBG_I2C4_STOP   /*!< The I2C4 SMBus timeout is frozen */
#define LL_DBGMCU_LPTIM2_STOP   DBGMCU_APB1FZR2_DBG_LPTIM2_STOP /*!< The counter clock of LPTIM2 is stopped
                                                                            when the core is halted */
#define LL_DBGMCU_I2C5_STOP     DBGMCU_APB1FZR2_DBG_I2C5_STOP   /*!< The I2C5 SMBus timeout is frozen */
#define LL_DBGMCU_I2C6_STOP     DBGMCU_APB1FZR2_DBG_I2C6_STOP   /*!< The I2C6 SMBus timeout is frozen */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB2_GRP1_STOP_IP DBGMCU APB2 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_TIM1_STOP     DBGMCU_APB2FZR_DBG_TIM1_STOP  /*!< The counter clock of TIM1 is stopped when
                                                                          the core is halted  */
#define LL_DBGMCU_TIM8_STOP     DBGMCU_APB2FZR_DBG_TIM8_STOP  /*!< The counter clock of TIM8 is stopped when
                                                                          the core is halted  */
#define LL_DBGMCU_TIM15_STOP    DBGMCU_APB2FZR_DBG_TIM15_STOP /*!< The counter clock of TIM15 is stopped when
                                                                          the core is halted */
#define LL_DBGMCU_TIM16_STOP    DBGMCU_APB2FZR_DBG_TIM16_STOP /*!< The counter clock of TIM16 is stopped when
                                                                          the core is halted */
#define LL_DBGMCU_TIM17_STOP    DBGMCU_APB2FZR_DBG_TIM17_STOP /*!< The counter clock of TIM17 is stopped when
                                                                          the core is halted */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB3_GRP1_STOP_IP DBGMCU APB3 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_I2C3_STOP     DBGMCU_APB3FZR_DBG_I2C3_STOP   /*!< The counter clock of I2C3 is stopped when
                                                                           the core is halted   */
#define LL_DBGMCU_LPTIM1_STOP   DBGMCU_APB3FZR_DBG_LPTIM1_STOP /*!< The counter clock of LPTIM1 is stopped when
                                                                           the core is halted */
#define LL_DBGMCU_LPTIM3_STOP   DBGMCU_APB3FZR_DBG_LPTIM3_STOP /*!< The counter clock of LPTIM3 is stopped when
                                                                           the core is halted */
#define LL_DBGMCU_LPTIM4_STOP   DBGMCU_APB3FZR_DBG_LPTIM4_STOP /*!< The counter clock of LPTIM4 is stopped when
                                                                           the core is halted */
#define LL_DBGMCU_RTC_STOP      DBGMCU_APB3FZR_DBG_RTC_STOP    /*!< The counter clock of RTC is stopped when
                                                                           the core is halted    */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_AHB1_GRP1_STOP_IP DBGMCU AHB1 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_GPDMA1_CH0_STOP    DBGMCU_AHB1FZR_DBG_GPDMA0_STOP  /*!< The counter clock of GPDMA1 channel 0
                                                                                 is stopped when the core is halted  */
#define LL_DBGMCU_GPDMA1_CH1_STOP    DBGMCU_AHB1FZR_DBG_GPDMA1_STOP  /*!< The counter clock of GPDMA1 channel 1
                                                                                 is stopped when the core is halted  */
#define LL_DBGMCU_GPDMA1_CH2_STOP    DBGMCU_AHB1FZR_DBG_GPDMA2_STOP  /*!< The counter clock of GPDMA1 channel 2
                                                                                 is stopped when the core is halted  */
#define LL_DBGMCU_GPDMA1_CH3_STOP    DBGMCU_AHB1FZR_DBG_GPDMA3_STOP  /*!< The counter clock of GPDMA1 channel 3
                                                                                 is stopped when the core is halted  */
#define LL_DBGMCU_GPDMA1_CH4_STOP    DBGMCU_AHB1FZR_DBG_GPDMA4_STOP  /*!< The counter clock of GPDMA1 channel 4
                                                                                 is stopped when the core is halted  */
#define LL_DBGMCU_GPDMA1_CH5_STOP    DBGMCU_AHB1FZR_DBG_GPDMA5_STOP  /*!< The counter clock of GPDMA1 channel 5
                                                                                 is stopped when the core is halted  */
#define LL_DBGMCU_GPDMA1_CH6_STOP    DBGMCU_AHB1FZR_DBG_GPDMA6_STOP  /*!< The counter clock of GPDMA1 channel 6
                                                                                 is stopped when the core is halted  */
#define LL_DBGMCU_GPDMA1_CH7_STOP    DBGMCU_AHB1FZR_DBG_GPDMA7_STOP  /*!< The counter clock of GPDMA1 channel 7
                                                                                 is stopped when the core is halted  */
#define LL_DBGMCU_GPDMA1_CH8_STOP    DBGMCU_AHB1FZR_DBG_GPDMA8_STOP  /*!< The counter clock of GPDMA1 channel 8
                                                                                 is stopped when the core is halted  */
#define LL_DBGMCU_GPDMA1_CH9_STOP    DBGMCU_AHB1FZR_DBG_GPDMA9_STOP  /*!< The counter clock of GPDMA1 channel 9
                                                                                 is stopped when the core is halted  */
#define LL_DBGMCU_GPDMA1_CH10_STOP   DBGMCU_AHB1FZR_DBG_GPDMA10_STOP /*!< The counter clock of GPDMA1 channel 10
                                                                                 is stopped when the core is halted */
#define LL_DBGMCU_GPDMA1_CH11_STOP   DBGMCU_AHB1FZR_DBG_GPDMA11_STOP /*!< The counter clock of GPDMA1 channel 11
                                                                                 is stopped when the core is halted */
#define LL_DBGMCU_GPDMA1_CH12_STOP   DBGMCU_AHB1FZR_DBG_GPDMA12_STOP /*!< The counter clock of GPDMA1 channel 12
                                                                                 is stopped when the core is halted */
#define LL_DBGMCU_GPDMA1_CH13_STOP   DBGMCU_AHB1FZR_DBG_GPDMA13_STOP /*!< The counter clock of GPDMA1 channel 13
                                                                                 is stopped when the core is halted */
#define LL_DBGMCU_GPDMA1_CH14_STOP   DBGMCU_AHB1FZR_DBG_GPDMA14_STOP /*!< The counter clock of GPDMA1 channel 14
                                                                                 is stopped when the core is halted */
#define LL_DBGMCU_GPDMA1_CH15_STOP   DBGMCU_AHB1FZR_DBG_GPDMA15_STOP /*!< The counter clock of GPDMA1 channel 15
                                                                                 is stopped when the core is halted */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_AHB3_GRP1_STOP_IP DBGMCU AHB3 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_LPDMA1_CH0_STOP    DBGMCU_AHB3FZR_DBG_LPDMA0_STOP /*!< The counter clock of LPDMA1 channel 0
                                                                                is stopped when the core is halted */
#define LL_DBGMCU_LPDMA1_CH1_STOP    DBGMCU_AHB3FZR_DBG_LPDMA1_STOP /*!< The counter clock of LPDMA1 channel 1
                                                                                is stopped when the core is halted */
#define LL_DBGMCU_LPDMA1_CH2_STOP    DBGMCU_AHB3FZR_DBG_LPDMA2_STOP /*!< The counter clock of LPDMA1 channel 2
                                                                                is stopped when the core is halted */
#define LL_DBGMCU_LPDMA1_CH3_STOP    DBGMCU_AHB3FZR_DBG_LPDMA3_STOP /*!< The counter clock of LPDMA1 channel 3
                                                                                is stopped when the core is halted */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros ------------------------------------------------------------*/

/** @defgroup DBGMCU_LL_Exported_Macros DBGMCU Exported Macros
  * @{
  */

/** @defgroup DBGMCU_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in DBGMCU register
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_DBGMCU_WRITE_REG(reg, value) WRITE_REG(DBGMCU->reg, (value))

/**
  * @brief  Read a value in DBGMCU register
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_DBGMCU_READ_REG(reg) READ_REG(DBGMCU->reg)

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup DBGMCU_LL_Exported_Functions LL DBGMCU functions
  * @{
  */

/** @defgroup DBGMCU_LL_EF_ID LL DBGMCU Identifications
  * @{
  */

/**
  * @brief  Return the device identifier
  * @rmtoll
  *  DBGMCU_IDCODE DEV_ID        LL_DBGMCU_GetDeviceID
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DBGMCU_DEV_ID_U5F5_U5G5
  *         @arg @ref LL_DBGMCU_DEV_ID_U595_U5A5
  *         @arg @ref LL_DBGMCU_DEV_ID_U575_U585
  *         @arg @ref LL_DBGMCU_DEV_ID_U535_U545
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetDeviceID(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_DEV_ID));
}

/**
  * @brief  Return the device revision identifier
  * @rmtoll
  *  DBGMCU_IDCODE REV_ID        LL_DBGMCU_GetRevisionID
  * @note This field indicates the revision of the device.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DBGMCU_REV_ID_A
  *         @arg @ref LL_DBGMCU_REV_ID_B
  *         @arg @ref LL_DBGMCU_REV_ID_C
  *         @arg @ref LL_DBGMCU_REV_ID_X
  *         @arg @ref LL_DBGMCU_REV_ID_Y
  *         @arg @ref LL_DBGMCU_REV_ID_Z
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetRevisionID(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_REV_ID) >> DBGMCU_IDCODE_REV_ID_Pos);
}

/**
  * @}
  */

/** @defgroup DBGMCU_LL_EF_LOW_POWER_MODE LL DBGMCU Debug Low power mode
  * @{
  */

/**
  * @brief  Enable the debug module during low power mode (Stop0/1/2 and standby modes)
  * @rmtoll
  *  DBGMCU_CR    DBG_STOP       LL_DBGMCU_EnableDebugLowPowerMode \n
  *  DBGMCU_CR    DBG_STANBY     LL_DBGMCU_EnableDebugLowPowerMode
  * @param mode This parameter can be one of the following values:
  *         @arg @ref  LL_DBGMCU_STOP_MODE_DEBUG
  *         @arg @ref  LL_DBGMCU_STANDBY_MODE_DEBUG
  *         @arg @ref  LL_DBGMCU_LP_MODE_DEBUG_ALL
  */
__STATIC_INLINE void LL_DBGMCU_EnableDebugLowPowerMode(uint32_t mode)
{
  SET_BIT(DBGMCU->CR, mode);
}

/**
  * @brief  Disable the debug module during low power mode (Stop0/1/2 and standby modes)
  * @rmtoll
  *  DBGMCU_CR    DBG_STOP      LL_DBGMCU_DisableDebugLowPowerMode \n
  *  DBGMCU_CR    DBG_STANBY    LL_DBGMCU_DisableDebugLowPowerMode
  * @param mode This parameter can be one of the following values:
  *         @arg @ref  LL_DBGMCU_STOP_MODE_DEBUG
  *         @arg @ref  LL_DBGMCU_STANDBY_MODE_DEBUG
  *         @arg @ref  LL_DBGMCU_LP_MODE_DEBUG_ALL
  */
__STATIC_INLINE void LL_DBGMCU_DisableDebugLowPowerMode(uint32_t mode)
{
  CLEAR_BIT(DBGMCU->CR, mode);
}

/**
  * @brief  Check if the debug module during low power mode (Stop0/1/2 and standby modes) is enabled.
  * @rmtoll
  *  DBGMCU_CR    DBG_STOP      LL_DBGMCU_IsEnabledDebugLowPowerMode \n
  *  DBGMCU_CR    DBG_STANDBY   LL_DBGMCU_IsEnabledDebugLowPowerMode
  * @param mode This parameter can be one of the following values:
  *         @arg @ref  LL_DBGMCU_STOP_MODE_DEBUG
  *         @arg @ref  LL_DBGMCU_STANDBY_MODE_DEBUG
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDebugLowPowerMode(uint32_t mode)
{
  return ((READ_BIT(DBGMCU->CR, mode) == (mode)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the debug module during Stop0/1/2 mode
  * @rmtoll
  *  DBGMCU_CR    DBG_STOP      LL_DBGMCU_EnableDBGStopMode
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStopMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the debug module during Stop0/1/2 mode
  * @rmtoll
  *  DBGMCU_CR    DBG_STOP      LL_DBGMCU_DisableDBGStopMode
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Check if the debug module during Stop0/1/2 mode is enabled.
  * @rmtoll
  *  DBGMCU_CR    DBG_STOP      LL_DBGMCU_IsEnabledDBGStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGStopMode(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP) == (DBGMCU_CR_DBG_STOP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the debug module during Standby mode
  * @rmtoll
  *  DBGMCU_CR    DBG_STANDBY   LL_DBGMCU_EnableDBGStandbyMode
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStandbyMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Disable the debug module during Standby mode
  * @rmtoll
  *  DBGMCU_CR    DBG_STANDBY   LL_DBGMCU_DisableDBGStandbyMode
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStandbyMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Check if the debug module during Standby mode is enabled.
  * @rmtoll
  *  DBGMCU_CR    DBG_STANDBY      LL_DBGMCU_IsEnabledDBGStandbyMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGStandbyMode(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY) == (DBGMCU_CR_DBG_STANDBY)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup DBGMCU_LL_EF_FREEZE_UNFREEZE LL DBGMCU Freeze/Unfreeze
  * @{
  */

/**
  * @brief  Freeze APB1 peripherals (group1 peripherals)
  * @rmtoll
  *  DBGMCU_APB1FZR1 DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP1_FreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_TIM2_STOP
  *         @arg @ref LL_DBGMCU_TIM3_STOP
  *         @arg @ref LL_DBGMCU_TIM4_STOP
  *         @arg @ref LL_DBGMCU_TIM5_STOP
  *         @arg @ref LL_DBGMCU_TIM6_STOP
  *         @arg @ref LL_DBGMCU_TIM7_STOP
  *         @arg @ref LL_DBGMCU_WWDG_STOP
  *         @arg @ref LL_DBGMCU_IWDG_STOP
  *         @arg @ref LL_DBGMCU_I2C1_STOP
  *         @arg @ref LL_DBGMCU_I2C2_STOP
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_FreezePeriph(uint32_t periphs)
{
  ATOMIC_SET_BIT(DBGMCU->APB1FZR1, periphs);
}

/**
  * @brief  Unfreeze APB1 peripherals (group1 peripherals)
  * @rmtoll
  *  DBGMCU_APB1FZR1 DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP1_UnFreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_TIM2_STOP
  *         @arg @ref LL_DBGMCU_TIM3_STOP
  *         @arg @ref LL_DBGMCU_TIM4_STOP
  *         @arg @ref LL_DBGMCU_TIM5_STOP
  *         @arg @ref LL_DBGMCU_TIM6_STOP
  *         @arg @ref LL_DBGMCU_TIM7_STOP
  *         @arg @ref LL_DBGMCU_WWDG_STOP
  *         @arg @ref LL_DBGMCU_IWDG_STOP
  *         @arg @ref LL_DBGMCU_I2C1_STOP
  *         @arg @ref LL_DBGMCU_I2C2_STOP
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_UnFreezePeriph(uint32_t periphs)
{
  ATOMIC_CLEAR_BIT(DBGMCU->APB1FZR1, periphs);
}

/**
  * @brief  Freeze APB1 peripherals (group2 peripherals)
  * @rmtoll
  *  DBGMCU_APB1FZR2 DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP2_FreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_I2C4_STOP
  *         @arg @ref LL_DBGMCU_LPTIM2_STOP
  *         @arg @ref LL_DBGMCU_I2C5_STOP (*)
  *         @arg @ref LL_DBGMCU_I2C6_STOP (*)
  * @note   (*) Availability depends on devices.
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP2_FreezePeriph(uint32_t periphs)
{
  ATOMIC_SET_BIT(DBGMCU->APB1FZR2, periphs);
}

/**
  * @brief  Unfreeze APB1 peripherals (group2 peripherals)
  * @rmtoll
  *  DBGMCU_APB1FZR2 DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP2_UnFreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_I2C4_STOP
  *         @arg @ref LL_DBGMCU_LPTIM2_STOP
  *         @arg @ref LL_DBGMCU_I2C5_STOP (*)
  *         @arg @ref LL_DBGMCU_I2C6_STOP (*)
  * @note   (*) Availability depends on devices.
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP2_UnFreezePeriph(uint32_t periphs)
{
  ATOMIC_CLEAR_BIT(DBGMCU->APB1FZR2, periphs);
}

/**
  * @brief  Freeze APB2 peripherals
  * @rmtoll
  *  DBGMCU_APB2FZ DBG_TIMx_STOP  LL_DBGMCU_APB2_GRP1_FreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_TIM1_STOP
  *         @arg @ref LL_DBGMCU_TIM8_STOP
  *         @arg @ref LL_DBGMCU_TIM15_STOP
  *         @arg @ref LL_DBGMCU_TIM16_STOP
  *         @arg @ref LL_DBGMCU_TIM17_STOP
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_FreezePeriph(uint32_t periphs)
{
  ATOMIC_SET_BIT(DBGMCU->APB2FZR, periphs);
}

/**
  * @brief  Unfreeze APB2 peripherals
  * @rmtoll
  *  DBGMCU_APB2FZR DBG_TIMx_STOP  LL_DBGMCU_APB2_GRP1_UnFreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_TIM1_STOP
  *         @arg @ref LL_DBGMCU_TIM8_STOP
  *         @arg @ref LL_DBGMCU_TIM15_STOP
  *         @arg @ref LL_DBGMCU_TIM16_STOP
  *         @arg @ref LL_DBGMCU_TIM17_STOP
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_UnFreezePeriph(uint32_t periphs)
{
  ATOMIC_CLEAR_BIT(DBGMCU->APB2FZR, periphs);
}

/**
  * @brief  Freeze APB3 peripherals
  * @rmtoll
  *  DBGMCU_APB3FZ DBG_TIMx_STOP  LL_DBGMCU_APB3_GRP1_FreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_I2C3_STOP
  *         @arg @ref LL_DBGMCU_LPTIM1_STOP
  *         @arg @ref LL_DBGMCU_LPTIM3_STOP
  *         @arg @ref LL_DBGMCU_LPTIM4_STOP
  *         @arg @ref LL_DBGMCU_RTC_STOP
  */
__STATIC_INLINE void LL_DBGMCU_APB3_GRP1_FreezePeriph(uint32_t periphs)
{
  ATOMIC_SET_BIT(DBGMCU->APB3FZR, periphs);
}

/**
  * @brief  Unfreeze APB3 peripherals
  * @rmtoll
  *  DBGMCU_APB3FZR DBG_TIMx_STOP  LL_DBGMCU_APB3_GRP1_UnFreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_I2C3_STOP
  *         @arg @ref LL_DBGMCU_LPTIM1_STOP
  *         @arg @ref LL_DBGMCU_LPTIM3_STOP
  *         @arg @ref LL_DBGMCU_LPTIM4_STOP
  *         @arg @ref LL_DBGMCU_RTC_STOP
  */
__STATIC_INLINE void LL_DBGMCU_APB3_GRP1_UnFreezePeriph(uint32_t periphs)
{
  ATOMIC_CLEAR_BIT(DBGMCU->APB3FZR, periphs);
}

/**
  * @brief  Freeze AHB1 peripherals
  * @rmtoll
  *  DBGMCU_AHB1FZ DBG_GPDMAx_STOP  LL_DBGMCU_AHB1_GRP1_FreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_GPDMA1_CH0_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH1_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH2_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH3_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH4_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH5_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH6_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH7_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH8_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH9_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH10_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH11_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH12_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH13_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH14_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH15_STOP
  */
__STATIC_INLINE void LL_DBGMCU_AHB1_GRP1_FreezePeriph(uint32_t periphs)
{
  ATOMIC_SET_BIT(DBGMCU->AHB1FZR, periphs);
}

/**
  * @brief  Unfreeze AHB1 peripherals
  * @rmtoll
  *  DBGMCU_AHB1FZ DBG_GPDMAx_STOP  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_GPDMA1_CH0_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH1_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH2_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH3_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH4_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH5_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH6_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH7_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH8_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH9_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH10_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH11_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH12_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH13_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH14_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH15_STOP
  */
__STATIC_INLINE void LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(uint32_t periphs)
{
  ATOMIC_CLEAR_BIT(DBGMCU->AHB1FZR, periphs);
}

/**
  * @brief  Freeze AHB3 peripherals
  * @rmtoll
  *  DBGMCU_AHB3FZ DBG_LPDMAx_STOP  LL_DBGMCU_AHB3_GRP1_FreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_LPDMA1_CH0_STOP
  *         @arg @ref LL_DBGMCU_LPDMA1_CH1_STOP
  *         @arg @ref LL_DBGMCU_LPDMA1_CH2_STOP
  *         @arg @ref LL_DBGMCU_LPDMA1_CH3_STOP
  */
__STATIC_INLINE void LL_DBGMCU_AHB3_GRP1_FreezePeriph(uint32_t periphs)
{
  ATOMIC_SET_BIT(DBGMCU->AHB3FZR, periphs);
}

/**
  * @brief  Unfreeze AHB3 peripherals
  * @rmtoll
  *  DBGMCU_AHB3FZ DBG_LPDMAx_STOP  LL_DBGMCU_AHB3_GRP1_UnFreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_LPDMA1_CH0_STOP
  *         @arg @ref LL_DBGMCU_LPDMA1_CH1_STOP
  *         @arg @ref LL_DBGMCU_LPDMA1_CH2_STOP
  *         @arg @ref LL_DBGMCU_LPDMA1_CH3_STOP
  */
__STATIC_INLINE void LL_DBGMCU_AHB3_GRP1_UnFreezePeriph(uint32_t periphs)
{
  ATOMIC_CLEAR_BIT(DBGMCU->AHB3FZR, periphs);
}

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

#endif /* STM32U5XX_LL_DBGMCU_H */
