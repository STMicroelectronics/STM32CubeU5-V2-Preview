/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_dbgmcu.h
  * @brief   Header file of DBGMCU HAL module.
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
#ifndef STM32U5XX_HAL_DBGMCU_H
#define STM32U5XX_HAL_DBGMCU_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_dbgmcu.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup DBGMCU DBGMCU
  * @{
  */

/* Exported variables ------------------------------------------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup DBGMCU_Exported_Types DBGMCU Exported Types
  * @{
  */

/*! HAL DBGMCU DBGMCU Device ID enumeration definition */
typedef enum
{
  HAL_DBGMCU_DEV_ID_U535_U545 = LL_DBGMCU_DEV_ID_U535_U545, /*!< STM32U5 device ID for STM32U545/535 */
  HAL_DBGMCU_DEV_ID_U575_U585 = LL_DBGMCU_DEV_ID_U575_U585, /*!< STM32U5 device ID for STM32U575/585 */
  HAL_DBGMCU_DEV_ID_U595_U5A5 = LL_DBGMCU_DEV_ID_U595_U5A5, /*!< STM32U5 device ID for STM32U59x/5Ax */
  HAL_DBGMCU_DEV_ID_U5F5_U5G5 = LL_DBGMCU_DEV_ID_U5F5_U5G5  /*!< STM32U5 device ID for STM32U5Fx/5Gx */
} hal_dbgmcu_device_id_t;

/*! HAL DBGMCU debug in low power mode state enumeration definition */
typedef enum
{
  HAL_DBGMCU_DBG_LOW_POWER_MODE_DISABLED = 0U, /*!< Debug in low power mode
                                                   (Stop0/1/2 and Standby modes) is disabled */
  HAL_DBGMCU_DBG_LOW_POWER_MODE_ENABLED  = 1U  /*!< Debug in low power mode
                                                   (Stop0/1/2 and Standby modes) is enabled  */
} hal_dbgmcu_dbg_low_power_mode_status_t;
/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup DBGMCU_Exported_Constants DBGMCU Exported Constants
  * @{
  */

/** @defgroup DBGMCU_Low_Power_Mode_Debug DBGMCU Low power mode debug definition
  * @{
  */
#define HAL_DBGMCU_STOP_MODE_DEBUG    LL_DBGMCU_STOP_MODE_DEBUG    /*!< Debug during Stop mode           */
#define HAL_DBGMCU_STANDBY_MODE_DEBUG LL_DBGMCU_STANDBY_MODE_DEBUG /*!< Debug during Standby mode        */
#define HAL_DBGMCU_LP_MODE_DEBUG_ALL  LL_DBGMCU_LP_MODE_DEBUG_ALL  /*!< Debug during all Low power modes */
/**
  * @}
  */

/**
  * @}
  */
/* Exported macros ---------------------------------------------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup DBGMCU_Exported_Functions DBGMCU Exported Functions
  * @{
  */

/** @defgroup DBGMCU_Exported_Functions_Group1 DBGMCU Device identification functions
  * @{
  */
uint32_t HAL_DBGMCU_GetRevisionID(void);
hal_dbgmcu_device_id_t HAL_DBGMCU_GetDeviceID(void);
/**
  * @}
  */

/** @defgroup DBGMCU_Exported_Functions_Group2 DBGMCU Low power mode debug activation functions
  * @{
  */
void HAL_DBGMCU_EnableDebugLowPowerMode(uint32_t mode);
void HAL_DBGMCU_DisableDebugLowPowerMode(uint32_t mode);
hal_dbgmcu_dbg_low_power_mode_status_t HAL_DBGMCU_IsEnabledDebugLowPowerMode(uint32_t mode);
/**
  * @}
  */

/** @defgroup DBGMCU_Exported_Functions_Group3 DBGMCU Peripheral clock freeze and unfreeze functions
  * @{
  This section provides functions allowing to freeze and unfreeze the peripheral clock when the CPU is halted:
  - Call HAL_DBGMCU_PPPi_Freeze() function to freeze the peripheral clock of PPPi when the CPU is halted.
  - Call HAL_DBGMCU_PPPi_UnFreeze() function to unfreeze the peripheral clock of PPPi when the CPU is halted.
  */
/**
  * @details Freeze the clock of TIM1 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM1_Freeze(void)
{
  LL_DBGMCU_APB2_GRP1_FreezePeriph(LL_DBGMCU_TIM1_STOP);
}

/**
  * @details Unfreeze the clock of TIM1 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM1_UnFreeze(void)
{
  LL_DBGMCU_APB2_GRP1_UnFreezePeriph(LL_DBGMCU_TIM1_STOP);
}

/**
  * @details Freeze the clock of TIM2 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM2_Freeze(void)
{
  LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_TIM2_STOP);
}

/**
  * @details Unfreeze the clock of TIM2 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM2_UnFreeze(void)
{
  LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_TIM2_STOP);
}

/**
  * @details Freeze the clock of TIM3 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM3_Freeze(void)
{
  LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_TIM3_STOP);
}

/**
  * @details Unfreeze the clock of TIM3 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM3_UnFreeze(void)
{
  LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_TIM3_STOP);
}

/**
  * @details Freeze the clock of TIM4 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM4_Freeze(void)
{
  LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_TIM4_STOP);
}

/**
  * @details Unfreeze the clock of TIM4 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM4_UnFreeze(void)
{
  LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_TIM4_STOP);
}

/**
  * @details Freeze the clock of TIM5 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM5_Freeze(void)
{
  LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_TIM5_STOP);
}

/**
  * @details Unfreeze the clock of TIM5 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM5_UnFreeze(void)
{
  LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_TIM5_STOP);
}

/**
  * @details Freeze the clock of TIM6 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM6_Freeze(void)
{
  LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_TIM6_STOP);
}

/**
  * @details Unfreeze the clock of TIM6 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM6_UnFreeze(void)
{
  LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_TIM6_STOP);
}

/**
  * @details Freeze the clock of TIM7 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM7_Freeze(void)
{
  LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_TIM7_STOP);
}

/**
  * @details Unfreeze the clock of TIM7 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM7_UnFreeze(void)
{
  LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_TIM7_STOP);
}

/**
  * @details Freeze the clock of TIM8 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM8_Freeze(void)
{
  LL_DBGMCU_APB2_GRP1_FreezePeriph(LL_DBGMCU_TIM8_STOP);
}

/**
  * @details Unfreeze the clock of TIM8 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM8_UnFreeze(void)
{
  LL_DBGMCU_APB2_GRP1_UnFreezePeriph(LL_DBGMCU_TIM8_STOP);
}

/**
  * @details Freeze the clock of TIM15 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM15_Freeze(void)
{
  LL_DBGMCU_APB2_GRP1_FreezePeriph(LL_DBGMCU_TIM15_STOP);
}

/**
  * @details Unfreeze the clock of TIM15 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM15_UnFreeze(void)
{
  LL_DBGMCU_APB2_GRP1_UnFreezePeriph(LL_DBGMCU_TIM15_STOP);
}

/**
  * @details Freeze the clock of TIM16 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM16_Freeze(void)
{
  LL_DBGMCU_APB2_GRP1_FreezePeriph(LL_DBGMCU_TIM16_STOP);
}

/**
  * @details Unfreeze the clock of TIM16 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM16_UnFreeze(void)
{
  LL_DBGMCU_APB2_GRP1_UnFreezePeriph(LL_DBGMCU_TIM16_STOP);
}

/**
  * @details Freeze the clock of TIM17 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM17_Freeze(void)
{
  LL_DBGMCU_APB2_GRP1_FreezePeriph(LL_DBGMCU_TIM17_STOP);
}

/**
  * @details Unfreeze the clock of TIM17 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_TIM17_UnFreeze(void)
{
  LL_DBGMCU_APB2_GRP1_UnFreezePeriph(LL_DBGMCU_TIM17_STOP);
}

/**
  * @details Freeze the clock of I2C1 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_I2C1_Freeze(void)
{
  LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_I2C1_STOP);
}

/**
  * @details Unfreeze the clock of I2C1 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_I2C1_UnFreeze(void)
{
  LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_I2C1_STOP);
}

/**
  * @details Freeze the clock of I2C2 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_I2C2_Freeze(void)
{
  LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_I2C2_STOP);
}

/**
  * @details Unfreeze the clock of I2C2 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_I2C2_UnFreeze(void)
{
  LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_I2C2_STOP);
}

/**
  * @details Freeze the clock of I2C3 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_I2C3_Freeze(void)
{
  LL_DBGMCU_APB3_GRP1_FreezePeriph(LL_DBGMCU_I2C3_STOP);
}

/**
  * @details Unfreeze the clock of I2C3 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_I2C3_UnFreeze(void)
{
  LL_DBGMCU_APB3_GRP1_UnFreezePeriph(LL_DBGMCU_I2C3_STOP);
}

/**
  * @details Freeze the clock of I2C4 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_I2C4_Freeze(void)
{
  LL_DBGMCU_APB1_GRP2_FreezePeriph(LL_DBGMCU_I2C4_STOP);
}

/**
  * @details Unfreeze the clock of I2C4 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_I2C4_UnFreeze(void)
{
  LL_DBGMCU_APB1_GRP2_UnFreezePeriph(LL_DBGMCU_I2C4_STOP);
}

#if defined(DBGMCU_APB1FZR2_DBG_I2C5_STOP)
/**
  * @details Freeze the clock of I2C5 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_I2C5_Freeze(void)
{
  LL_DBGMCU_APB1_GRP2_FreezePeriph(LL_DBGMCU_I2C5_STOP);
}

/**
  * @details Unfreeze the clock of I2C5 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_I2C5_UnFreeze(void)
{
  LL_DBGMCU_APB1_GRP2_UnFreezePeriph(LL_DBGMCU_I2C5_STOP);
}
#endif /* DBGMCU_APB1FZR2_DBG_I2C5_STOP */

#if defined(DBGMCU_APB1FZR2_DBG_I2C6_STOP)
/**
  * @details Freeze the clock of I2C6 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_I2C6_Freeze(void)
{
  LL_DBGMCU_APB1_GRP2_FreezePeriph(LL_DBGMCU_I2C6_STOP);
}

/**
  * @details Unfreeze the clock of I2C6 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_I2C6_UnFreeze(void)
{
  LL_DBGMCU_APB1_GRP2_UnFreezePeriph(LL_DBGMCU_I2C6_STOP);
}
#endif /* DBGMCU_APB1FZR2_DBG_I2C6_STOP */

/**
  * @details Freeze the clock of WWDG when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_WWDG_Freeze(void)
{
  LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_WWDG_STOP);
}

/**
  * @details Unfreeze the clock of WWDG when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_WWDG_UnFreeze(void)
{
  LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_WWDG_STOP);
}

/**
  * @details Freeze the clock of IWDG when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_IWDG_Freeze(void)
{
  LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_IWDG_STOP);
}

/**
  * @details Unfreeze the clock of IWDG when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_IWDG_UnFreeze(void)
{
  LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_IWDG_STOP);
}

/**
  * @details Freeze the clock of RTC when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_RTC_Freeze(void)
{
  LL_DBGMCU_APB3_GRP1_FreezePeriph(LL_DBGMCU_RTC_STOP);
}

/**
  * @details Unfreeze the clock of RTC when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_RTC_UnFreeze(void)
{
  LL_DBGMCU_APB3_GRP1_UnFreezePeriph(LL_DBGMCU_RTC_STOP);
}

/**
  * @details Freeze the clock of LPTIM1 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPTIM1_Freeze(void)
{
  LL_DBGMCU_APB3_GRP1_FreezePeriph(LL_DBGMCU_LPTIM1_STOP);
}

/**
  * @details Unfreeze the clock of LPTIM1 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPTIM1_UnFreeze(void)
{
  LL_DBGMCU_APB3_GRP1_UnFreezePeriph(LL_DBGMCU_LPTIM1_STOP);
}

/**
  * @details Freeze the clock of LPTIM2 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPTIM2_Freeze(void)
{
  LL_DBGMCU_APB1_GRP2_FreezePeriph(LL_DBGMCU_LPTIM2_STOP);
}

/**
  * @details Unfreeze the clock of LPTIM2 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPTIM2_UnFreeze(void)
{
  LL_DBGMCU_APB1_GRP2_UnFreezePeriph(LL_DBGMCU_LPTIM2_STOP);
}

/**
  * @details Freeze the clock of LPTIM3 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPTIM3_Freeze(void)
{
  LL_DBGMCU_APB3_GRP1_FreezePeriph(LL_DBGMCU_LPTIM3_STOP);
}

/**
  * @details Unfreeze the clock of LPTIM3 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPTIM3_UnFreeze(void)
{
  LL_DBGMCU_APB3_GRP1_UnFreezePeriph(LL_DBGMCU_LPTIM3_STOP);
}

/**
  * @details Freeze the clock of LPTIM4 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPTIM4_Freeze(void)
{
  LL_DBGMCU_APB3_GRP1_FreezePeriph(LL_DBGMCU_LPTIM4_STOP);
}

/**
  * @details Unfreeze the clock of LPTIM4 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPTIM4_UnFreeze(void)
{
  LL_DBGMCU_APB3_GRP1_UnFreezePeriph(LL_DBGMCU_LPTIM4_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 0 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch0_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH0_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 0 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch0_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH0_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 1 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch1_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH1_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 1 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch1_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH1_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 2 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch2_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH2_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 2 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch2_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH2_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 3 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch3_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH3_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 3 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch3_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH3_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 4 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch4_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH4_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 4 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch4_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH4_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 5 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch5_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH5_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 5 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch5_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH5_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 6 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch6_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH6_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 6 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch6_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH6_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 7 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch7_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH7_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 7 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch7_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH7_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 8 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch8_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH8_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 8 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch8_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH8_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 9 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch9_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH9_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 9 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch9_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH9_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 10 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch10_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH10_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 10 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch10_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH10_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 11 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch11_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH11_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 11 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch11_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH11_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 12 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch12_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH12_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 12 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch12_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH12_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 13 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch13_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH13_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 13 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch13_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH13_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 14 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch14_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH14_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 14 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch14_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH14_STOP);
}

/**
  * @details Freeze the clock of GPDMA1 channel 15 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch15_Freeze(void)
{
  LL_DBGMCU_AHB1_GRP1_FreezePeriph(LL_DBGMCU_GPDMA1_CH15_STOP);
}

/**
  * @details Unfreeze the clock of GPDMA1 channel 15 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_GPDMA1_Ch15_UnFreeze(void)
{
  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(LL_DBGMCU_GPDMA1_CH15_STOP);
}

/**
  * @details Freeze the clock of LPDMA1 channel 0 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPDMA1_Ch0_Freeze(void)
{
  LL_DBGMCU_AHB3_GRP1_FreezePeriph(LL_DBGMCU_LPDMA1_CH0_STOP);
}

/**
  * @details Unfreeze the clock of LPDMA1 channel 0 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPDMA1_Ch0_UnFreeze(void)
{
  LL_DBGMCU_AHB3_GRP1_UnFreezePeriph(LL_DBGMCU_LPDMA1_CH0_STOP);
}

/**
  * @details Freeze the clock of LPDMA1 channel 1 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPDMA1_Ch1_Freeze(void)
{
  LL_DBGMCU_AHB3_GRP1_FreezePeriph(LL_DBGMCU_LPDMA1_CH1_STOP);
}

/**
  * @details Unfreeze the clock of LPDMA1 channel 1 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPDMA1_Ch1_UnFreeze(void)
{
  LL_DBGMCU_AHB3_GRP1_UnFreezePeriph(LL_DBGMCU_LPDMA1_CH1_STOP);
}

/**
  * @details Freeze the clock of LPDMA1 channel 2 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPDMA1_Ch2_Freeze(void)
{
  LL_DBGMCU_AHB3_GRP1_FreezePeriph(LL_DBGMCU_LPDMA1_CH2_STOP);
}

/**
  * @details Unfreeze the clock of LPDMA1 channel 2 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPDMA1_Ch2_UnFreeze(void)
{
  LL_DBGMCU_AHB3_GRP1_UnFreezePeriph(LL_DBGMCU_LPDMA1_CH2_STOP);
}

/**
  * @details Freeze the clock of LPDMA1 channel 3 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPDMA1_Ch3_Freeze(void)
{
  LL_DBGMCU_AHB3_GRP1_FreezePeriph(LL_DBGMCU_LPDMA1_CH3_STOP);
}

/**
  * @details Unfreeze the clock of LPDMA1 channel 3 when the CPU is halted.
  */
__STATIC_INLINE void HAL_DBGMCU_LPDMA1_Ch3_UnFreeze(void)
{
  LL_DBGMCU_AHB3_GRP1_UnFreezePeriph(LL_DBGMCU_LPDMA1_CH3_STOP);
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
#endif

#endif /* STM32U5XX_HAL_DBGMCU_H */
