/**
  ******************************************************************************
  * @file    stm32u5xx_ll_opamp.h
  * @brief   Header file of OPAMP LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5XX_LL_OPAMP_H
#define STM32U5XX_LL_OPAMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */
#if defined (OPAMP1) || defined (OPAMP2)

/** @defgroup OPAMP_LL OPAMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup OPAMP_LL_Private_Constants OPAMP Private Constants
  * @{
  */

/* Internal mask for OPAMP power mode:                                        */
/* To select into literal LL_OPAMP_POWERMODE_x the relevant bits for:         */
/* - OPAMP power mode into control register                                   */
/* - OPAMP trimming register offset                                           */

/* Internal register offset for OPAMP trimming configuration */
#define OPAMP_POWERMODE_OTR_REGOFFSET            (0x00000000U)
#define OPAMP_POWERMODE_LPOTR_REGOFFSET          (0x00000002U)
#define OPAMP_POWERMODE_OTR_REGOFFSET_MASK       (OPAMP_POWERMODE_OTR_REGOFFSET | OPAMP_POWERMODE_LPOTR_REGOFFSET)

/* Mask for OPAMP power mode into control register */
#define OPAMP_SPEED_MODE_CSR_BIT_MASK            (OPAMP_CSR_HSM)
#define OPAMP_LOW_POWER_MODE_CSR_BIT_MASK        (OPAMP_CSR_OPALPM)
#define OPAMP_POWERMODE_CSR_BIT_MASK             (OPAMP_LOW_POWER_MODE_CSR_BIT_MASK | OPAMP_SPEED_MODE_CSR_BIT_MASK)

/* CSR register reset value */
#define OPAMP_CSR_RESET_VALUE  ((uint32_t)0x00000000) /*!< CSR reset value.*/

#define OPAMP_CSR_RESET_BITS                     (OPAMP_CSR_OPAEN      \
                                                  | OPAMP_CSR_OPALPM   \
                                                  | OPAMP_CSR_OPAMODE  \
                                                  | OPAMP_CSR_PGA_GAIN \
                                                  | OPAMP_CSR_VM_SEL   \
                                                  | OPAMP_CSR_VP_SEL   \
                                                  | OPAMP_CSR_CALON    \
                                                  | OPAMP_CSR_CALSEL   \
                                                  | OPAMP_CSR_HSM      \
                                                 )  /*!< CSR reset all bits, except USERTRIM and OPA_RANGE */

/* Internal mask for OPAMP trimming of transistors differential pair NMOS     */
/* or PMOS.                                                                   */
/* To select into literal LL_OPAMP_TRIMMING_x the relevant bits for:          */
/* - OPAMP trimming selection of transistors differential pair                */
/* - OPAMP trimming values of transistors differential pair                   */
#define OPAMP_TRIMMING_SELECT_MASK               (OPAMP_CSR_CALSEL)
#define OPAMP_TRIMMING_VALUE_MASK                (OPAMP_OTR_TRIMOFFSETP | OPAMP_OTR_TRIMOFFSETN)

/**
  * @}
  */

/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  reg Register basis from which the offset is applied.
  * @param  reg_offset Offset to be applied (unit: number of registers).
  * @retval Register address
  */
#define OPAMP_PTR_REG_OFFSET(reg, reg_offset)    ((uint32_t *)((uint32_t) ((uint32_t)(&(reg)) + ((reg_offset) << 1U))))

/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         OTR or LPOTR register depending of power_mode.
  * @param  p_opamp OPAMP instance
  * @param  power_mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWER_MODE_NORMAL
  *         @arg @ref LL_OPAMP_POWER_MODE_LOW
  * @retval Register address
  */
#define OPAMP_REG_OTR_LPOTR(p_opamp, power_mode) ((uint32_t *)((uint32_t) ((uint32_t)(&((p_opamp)->OTR))  \
                                                                           + ((power_mode) << 1U))))


/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup OPAMP_LL_Exported_Constants OPAMP Exported Constants
  * @{
  */

/** @defgroup OPAMP_LL_EC_POWERSUPPLY_RANGE OPAMP power supply range
  * @{
  */
#define LL_OPAMP_POWERSUPPLY_RANGE_LOW           (0x00000000U)         /*!< Power supply range low  */
#define LL_OPAMP_POWERSUPPLY_RANGE_HIGH          (OPAMP_CSR_OPARANGE)  /*!< Power supply range high -
                                                 recommended for performance purpose */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_POWERMODE OPAMP power mode
  * @{
  */

#define LL_OPAMP_POWER_MODE_NORMAL               (0x00000000U)       /*!< OPAMP power mode: normal-power */
#define LL_OPAMP_POWER_MODE_LOW                  (OPAMP_CSR_OPALPM)  /*!< OPAMP power mode: low-power */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_SPEEDMODE OPAMP speed mode
  * @{
  */
#define LL_OPAMP_SPEED_MODE_NORMAL               (0x00000000U)       /*!< OPAMP speed mode: normal-speed */
#define LL_OPAMP_SPEED_MODE_HIGH                 (OPAMP_CSR_HSM)     /*!< OPAMP speed mode: high-speed */

/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_MODE OPAMP mode calibration or functional.
  * @{
  */
#define LL_OPAMP_MODE_FUNCTIONAL                 (0x00000000U)          /*!< OPAMP functional mode  */
#define LL_OPAMP_MODE_CALIBRATION                (OPAMP_CSR_CALON)      /*!< OPAMP calibration mode */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_FUNCTIONAL_MODE OPAMP functional mode
  * @{
  */
#define LL_OPAMP_MODE_STANDALONE                 (0x00000000U)                               /*!< OPAMP functional mode,
                                                 OPAMP operation in standalone */
#define LL_OPAMP_MODE_FOLLOWER                   (OPAMP_CSR_OPAMODE_1 | OPAMP_CSR_OPAMODE_0) /*!< OPAMP functional mode,
                                                 OPAMP operation in follower */
#define LL_OPAMP_MODE_PGA                        (OPAMP_CSR_OPAMODE_1)                       /*!< OPAMP functional mode,
                                                 OPAMP operation in PGA */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_MODE_PGA_GAIN OPAMP PGA gain (relevant when OPAMP is in functional mode PGA)
  * @{
  */
#define LL_OPAMP_PGA_GAIN_2                      (0x00000000UL)            /*!< OPAMP PGA gain 2  */
#define LL_OPAMP_PGA_GAIN_4                      (OPAMP_CSR_PGA_GAIN_0)    /*!< OPAMP PGA gain 4  */
#define LL_OPAMP_PGA_GAIN_8                      (OPAMP_CSR_PGA_GAIN_1)    /*!< OPAMP PGA gain 8  */
#define LL_OPAMP_PGA_GAIN_16                     (OPAMP_CSR_PGA_GAIN_1 \
                                                  | OPAMP_CSR_PGA_GAIN_0)  /*!< OPAMP PGA gain 16 */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_INPUT_NONINVERTING OPAMP input non-inverting
  * @{
  */
#define LL_OPAMP_INPUT_NONINVERT_IO0             (0x00000000U)        /*!< OPAMP non inverting input connected to
                                                 GPIO pin (pin PA0 for OPAMP1, pin PA6 for OPAMP2) */
#define LL_OPAMP_INPUT_NONINVERT_DAC1_CH1        (OPAMP_CSR_VP_SEL)   /*!< OPAMP non inverting input connected to
                                                 DAC1 channel output (channel1 for OPAMP1, channel2 for OPAMP2) */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_INPUT_INVERTING OPAMP input inverting
  * @{
  */
#define LL_OPAMP_INPUT_INVERT_IO0                (0x00000000U)          /*!< OPAMP inverting input connected to
                                                 GPIO pin (valid also in PGA mode for filtering).
                                                 Note: OPAMP inverting input is used with OPAMP in mode standalone or
                                                       PGA with external capacitors for filtering circuit.
                                                       Otherwise (OPAMP in mode follower), OPAMP inverting input is
                                                       not used (not connected to GPIO pin). */
#define LL_OPAMP_INPUT_INVERT_IO1                (OPAMP_CSR_VM_SEL_0)  /*!< OPAMP inverting input (low leakage input)
                                                 connected to GPIO pin (available only on package BGA132).
                                                 Note: OPAMP inverting input is used with OPAMP in mode standalone or
                                                       PGA with external capacitors for filtering circuit.
                                                       Otherwise (OPAMP in mode follower), OPAMP inverting input is
                                                       not used (not connected to GPIO pin). */
#define LL_OPAMP_INPUT_INVERT_CONNECT_NO         (OPAMP_CSR_VM_SEL_1)  /*!< OPAMP inverting input not externally
                                                 connected (intended for OPAMP in mode follower or
                                                 PGA without external capacitors for filtering) */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_INPUT_LEGACY OPAMP inputs legacy literals name
  * @{
  */
#define LL_OPAMP_NONINVERTINGINPUT_IO0           LL_OPAMP_INPUT_NONINVERT_IO0
#define LL_OPAMP_NONINVERTINGINPUT_DAC_CH        LL_OPAMP_INPUT_NONINVERT_DAC1_CH1

#define LL_OPAMP_INVERTINGINPUT_IO0              LL_OPAMP_INPUT_INVERT_IO0
#define LL_OPAMP_INVERTINGINPUT_IO1              LL_OPAMP_INPUT_INVERT_IO1
#define LL_OPAMP_INVERTINGINPUT_CONNECT_NO       LL_OPAMP_INPUT_INVERT_CONNECT_NO

#define LL_OPAMP_INPUT_NONINV_DAC1_CH1           LL_OPAMP_INPUT_NONINVERT_DAC1_CH1
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_TRIMMING_MODE OPAMP trimming mode
  * @{
  */
#define LL_OPAMP_TRIMMING_FACTORY                (0x00000000U)      /*!< OPAMP trimming factors set to factory values */
#define LL_OPAMP_TRIMMING_USER                   (OPAMP_CSR_USERTRIM)  /*!< OPAMP trimming factors set to user values */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_TRIMMING_TRANSISTORS_DIFF_PAIR OPAMP trimming of transistors differential pair NMOS or PMOS
  * @{
  */
#define LL_OPAMP_TRIMMING_NMOS                   (OPAMP_OTR_TRIMOFFSETN)  /*!< OPAMP trim for NMOS differential pairs */
#define LL_OPAMP_TRIMMING_PMOS                   (OPAMP_OTR_TRIMOFFSETP \
                                                  | OPAMP_CSR_CALSEL)     /*!< OPAMP trim for PMOS differential pairs */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_HW_DELAYS  Definitions of OPAMP hardware constraints delays
  * @note   Only OPAMP IP HW delays are defined in OPAMP LL driver driver,
  *         not timeout values.
  *         For details on delays values, refer to descriptions in source code
  *         above each literal definition.
  * @{
  */

/* Delay for OPAMP startup time (transition from state disable to enable).    */
/* Note: OPAMP startup time depends on board application environment:         */
/*       impedance connected to OPAMP output.                                 */
/*       The delay below is specified under conditions:                       */
/*        - OPAMP in mode low power                                           */
/*        - OPAMP in functional mode follower                                 */
/*        - load impedance of 4kOhm (min), 50pF (max)                         */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tWAKEUP").                                                      */
/* Unit: us                                                                   */
#define LL_OPAMP_DELAY_STARTUP_US                ((uint32_t) 30U)  /*!< Delay for OPAMP startup time */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup OPAMP_LL_Exported_Macros OPAMP Exported Macros
  * @{
  */
/** @defgroup OPAMP_LL_EM_WRITE_READ Common write and read registers macro
  * @{
  */

/**
  * @brief  Write a value in OPAMP register
  * @param  instance OPAMP Instance
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_OPAMP_WRITE_REG(instance, reg, value) WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in OPAMP register
  * @param  instance OPAMP Instance
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_OPAMP_READ_REG(instance, reg) READ_REG((instance)->reg)

/**
  * @}
  */

/** @defgroup OPAMP_LL_EM_HELPER_MACRO OPAMP helper macro
  * @{
  */

/**
  * @brief  Helper macro to select the OPAMP common instance
  *         to which is belonging the selected OPAMP instance.
  * @param  p_opamp OPAMP instance
  * @note   OPAMP common register instance can be used to
  *         set parameters common to several OPAMP instances.
  *         Refer to functions having argument "p_opamp_COMMON" as parameter.
  * @retval OPAMP common instance
  */
#define LL_OPAMP_COMMON_INSTANCE(p_opamp) (OPAMP12_COMMON)

/**
  * @brief  Helper macro to check if all OPAMP instances sharing the same
  *         OPAMP common instance are disabled.
  * @note   This check is required by functions with setting conditioned to
  *         OPAMP state:
  *         All OPAMP instances of the OPAMP common group must be disabled.
  *         Refer to functions having argument "p_opamp_COMMON" as parameter.
  * @retval 0: All OPAMP instances sharing the same OPAMP common instance
  *            are disabled.
  *         1: At least one OPAMP instance sharing the same OPAMP common instance
  *            is enabled
  */
#if defined(OPAMP1) && defined(OPAMP2)
#define LL_OPAMP_IS_ENABLED_ALL_COMMON_INSTANCE()  (LL_OPAMP_IsEnabled(OPAMP1) | LL_OPAMP_IsEnabled(OPAMP2))
#else
#define LL_OPAMP_IS_ENABLED_ALL_COMMON_INSTANCE()  (LL_OPAMP_IsEnabled(OPAMP1))
#endif /* defined(OPAMP1) && defined(OPAMP2) */
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup OPAMP_LL_Exported_Functions OPAMP Exported Functions
  * @{
  */

/** @defgroup OPAMP_LL_EF_Configuration_opamp_common Configuration of OPAMP hierarchical scope: common OPAMP instances
  * @{
  */

/**
  * @brief  Set OPAMP power range.
  * @rmtoll
  *  CSR      OPARANGE       LL_OPAMP_SetCommonPowerRange
  * @param  p_opamp_common OPAMP common instance
  * @param  power_range This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWERSUPPLY_RANGE_LOW
  *         @arg @ref LL_OPAMP_POWERSUPPLY_RANGE_HIGH
  * @note   The OPAMP power range applies to several OPAMP instances
  *         (if several OPAMP instances available on the selected device).
  *         It is mandatory to set already the power range to high for performance purpose.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         OPAMP state:
  *         All OPAMP instances of the OPAMP common group must be disabled.
  *         This check can be done with function @ref LL_OPAMP_IsEnabled() for each
  *         OPAMP instance.
  * @note   LL_OPAMP_POWERSUPPLY_RANGE_HIGH parameter is highly recommended for performance purpose.
  */
__STATIC_INLINE void LL_OPAMP_SetCommonPowerRange(OPAMP_Common_TypeDef *p_opamp_common, uint32_t power_range)
{
  MODIFY_REG(p_opamp_common->CSR, OPAMP_CSR_OPARANGE, power_range);
}

/**
  * @brief  Get OPAMP power range.
  * @rmtoll
  *  CSR      OPARANGE       LL_OPAMP_GetCommonPowerRange
  * @param  p_opamp_common OPAMP common instance
  * @note   The OPAMP power range applies to several OPAMP instances
  *         (if several OPAMP instances available on the selected device).
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_POWERSUPPLY_RANGE_LOW
  *         @arg @ref LL_OPAMP_POWERSUPPLY_RANGE_HIGH
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetCommonPowerRange(const OPAMP_Common_TypeDef *p_opamp_common)
{
  return (uint32_t)(READ_BIT(p_opamp_common->CSR, OPAMP_CSR_OPARANGE));
}

/**
  * @}
  */

/** @defgroup OPAMP_LL_EF_CONFIGURATION_OPAMP_INSTANCE Configuration of OPAMP hierarchical scope: OPAMP instance
  * @{
  */

/**
  * @brief  Reset OPAMP CSR register, reset all bits except USERTRIM and OPA_RANGE.
  * @rmtoll
  *  CSR  OPAHSM    LL_OPAMP_ResetConfig \n
  *  CSR  CALOUT    LL_OPAMP_ResetConfig \n
  *  CSR  USERTRIM  LL_OPAMP_ResetConfig \n
  *  CSR  CALSEL    LL_OPAMP_ResetConfig \n
  *  CSR  CALON     LL_OPAMP_ResetConfig \n
  *  CSR  VP_SEL    LL_OPAMP_ResetConfig
  * @param  p_opamp OPAMP instance
  * @note   The OPAMP must be disabled to change this configuration.
  */
__STATIC_INLINE void LL_OPAMP_ResetConfig(OPAMP_TypeDef *p_opamp)
{
  /* Set OPAMP_CSR register to reset value */
  /* Mind that CSR RANGE bit of OPAMP1 remains unchanged (applies to both OPAMPs) */
  MODIFY_REG(p_opamp->CSR, (OPAMP_CSR_RESET_BITS), OPAMP_CSR_RESET_VALUE);
}
/**
  * @brief  Set OPAMP low power and speed mode.
  * @rmtoll
  *  CSR      OPALPM         LL_OPAMP_Set_LowPower_Speed_Mode \n
  *  CSR      OPAHSM         LL_OPAMP_Set_LowPower_Speed_Mode
  * @param  p_opamp OPAMP instance
  * @param  power_mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWER_MODE_NORMAL
  *         @arg @ref LL_OPAMP_POWER_MODE_LOW
  * @param  speed_mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_SPEED_MODE_NORMAL
  *         @arg @ref LL_OPAMP_SPEED_MODE_HIGH
  * @note   The OPAMP must be disabled to change this configuration.
  */
__STATIC_INLINE void LL_OPAMP_Set_LowPower_Speed_Mode(OPAMP_TypeDef *p_opamp, uint32_t power_mode, uint32_t speed_mode)
{
  MODIFY_REG(p_opamp->CSR, OPAMP_POWERMODE_CSR_BIT_MASK, power_mode | speed_mode);
}

/**
  * @brief  Set OPAMP low or normal power mode.
  * @rmtoll
  *  CSR      OPALPM         LL_OPAMP_SetLowPowerMode
  * @param  p_opamp OPAMP instance
  * @param  power_mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWER_MODE_NORMAL
  *         @arg @ref LL_OPAMP_POWER_MODE_LOW
  * @note   The OPAMP must be disabled to change this configuration.
  */
__STATIC_INLINE void LL_OPAMP_SetLowPowerMode(OPAMP_TypeDef *p_opamp, uint32_t power_mode)
{
  MODIFY_REG(p_opamp->CSR, OPAMP_LOW_POWER_MODE_CSR_BIT_MASK, power_mode);
}

/**
  * @brief  Get OPAMP low or normal power mode.
  * @rmtoll
  *  CSR      OPALPM      LL_OPAMP_GetLowPowerMode
  * @param  p_opamp OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_POWER_MODE_NORMAL
  *         @arg @ref LL_OPAMP_POWER_MODE_LOW
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetLowPowerMode(const OPAMP_TypeDef *p_opamp)
{
  uint32_t power_mode = (READ_BIT(p_opamp->CSR, OPAMP_LOW_POWER_MODE_CSR_BIT_MASK));

  return (uint32_t)(power_mode);
}

/**
  * @brief  Set OPAMP speed mode.
  * @rmtoll
  *  CSR     HSM         LL_OPAMP_SetSpeedMode
  * @param  p_opamp OPAMP instance
  * @param  speed_mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_SPEED_MODE_NORMAL
  *         @arg @ref LL_OPAMP_SPEED_MODE_HIGH
  * @note   The OPAMP must be disabled to change this configuration.
  */
__STATIC_INLINE void LL_OPAMP_SetSpeedMode(OPAMP_TypeDef *p_opamp, uint32_t speed_mode)
{
  MODIFY_REG(p_opamp->CSR, OPAMP_SPEED_MODE_CSR_BIT_MASK, speed_mode);
}

/**
  * @brief  Get OPAMP speed mode.
  * @rmtoll
  *  CSR     HSM      LL_OPAMP_GetSpeedMode
  * @param  p_opamp OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_SPEED_MODE_NORMAL
  *         @arg @ref LL_OPAMP_SPEED_MODE_HIGH
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetSpeedMode(const OPAMP_TypeDef *p_opamp)
{
  uint32_t speed_mode = (READ_BIT(p_opamp->CSR, OPAMP_SPEED_MODE_CSR_BIT_MASK));

  return (uint32_t)(speed_mode);
}

/**
  * @brief  Set OPAMP mode calibration or functional.
  * @rmtoll
  *  CSR      CALON         LL_OPAMP_SetMode
  * @param  p_opamp OPAMP instance
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_MODE_FUNCTIONAL
  *         @arg @ref LL_OPAMP_MODE_CALIBRATION
  * @note   OPAMP mode corresponds to functional or calibration mode:
  *          - functional mode: OPAMP operation in standalone, follower, ...
  *            Set functional mode using function
  *            @ref LL_OPAMP_SetConfigurationMode().
  *          - calibration mode: offset calibration of the selected
  *            transistors differential pair NMOS or PMOS.
  * @note   On this STM32 series, during calibration, OPAMP functional
  *         mode must be set to standalone or follower mode
  *         (in order to open internal connections to resistors of PGA mode).
  *         Refer to function @ref LL_OPAMP_SetConfigurationMode().
  */
__STATIC_INLINE void LL_OPAMP_SetMode(OPAMP_TypeDef *p_opamp, uint32_t mode)
{
  MODIFY_REG(p_opamp->CSR, OPAMP_CSR_CALON, mode);
}

/**
  * @brief  Get OPAMP mode calibration or functional.
  * @rmtoll
  *  CSR      CALON          LL_OPAMP_GetMode
  * @param  p_opamp OPAMP instance
  * @note   OPAMP mode corresponds to functional or calibration mode:
  *          - functional mode: OPAMP operation in standalone, follower, ...
  *            Set functional mode using function
  *            @ref LL_OPAMP_SetConfigurationMode().
  *          - calibration mode: offset calibration of the selected
  *            transistors differential pair NMOS or PMOS.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_MODE_FUNCTIONAL
  *         @arg @ref LL_OPAMP_MODE_CALIBRATION
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetMode(const OPAMP_TypeDef *p_opamp)
{
  return (uint32_t)(READ_BIT(p_opamp->CSR, OPAMP_CSR_CALON));
}

/**
  * @brief  Set OPAMP configuration mode by setting internal connections.
  * @rmtoll
  *  CSR      OPAMODE        LL_OPAMP_SetConfigurationMode
  * @param  p_opamp OPAMP instance
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_MODE_STANDALONE
  *         @arg @ref LL_OPAMP_MODE_FOLLOWER
  *         @arg @ref LL_OPAMP_MODE_PGA
  *         OPAMP operation in standalone, follower, ...
  * @note   This function reset bit of calibration mode to ensure
  *         to be in functional mode, in order to have OPAMP parameters
  *         (inputs selection, ...) set with the corresponding OPAMP mode
  *         to be effective.
  */
__STATIC_INLINE void LL_OPAMP_SetConfigurationMode(OPAMP_TypeDef *p_opamp, uint32_t mode)
{
  /* Note: Bit OPAMP_CSR_CALON reset to ensure to be in functional mode */
  MODIFY_REG(p_opamp->CSR, OPAMP_CSR_OPAMODE | OPAMP_CSR_CALON, mode);
}

/**
  * @brief  Get OPAMP configuration mode from setting of internal connections.
  *         OPAMP operation in standalone, follower, ...
  * @rmtoll
  *  CSR      OPAMODE        LL_OPAMP_GetConfigurationMode
  * @param  p_opamp OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_MODE_STANDALONE
  *         @arg @ref LL_OPAMP_MODE_FOLLOWER
  *         @arg @ref LL_OPAMP_MODE_PGA
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetConfigurationMode(const OPAMP_TypeDef *p_opamp)
{
  return (uint32_t)(READ_BIT(p_opamp->CSR, OPAMP_CSR_OPAMODE));
}

/**
  * @brief  Set OPAMP PGA gain.
  * @rmtoll
  *  CSR      gain         LL_OPAMP_SetPGAGain
  * @param  p_opamp OPAMP instance
  * @param  gain This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_PGA_GAIN_2
  *         @arg @ref LL_OPAMP_PGA_GAIN_4
  *         @arg @ref LL_OPAMP_PGA_GAIN_8
  *         @arg @ref LL_OPAMP_PGA_GAIN_16
  * @note   Preliminarily, OPAMP must be set in mode PGA
  *         using function @ref LL_OPAMP_SetConfigurationMode().
  */
__STATIC_INLINE void LL_OPAMP_SetPGAGain(OPAMP_TypeDef *p_opamp, uint32_t gain)
{
  MODIFY_REG(p_opamp->CSR, OPAMP_CSR_PGA_GAIN, gain);
}

/**
  * @brief  Get OPAMP PGA gain.
  * @rmtoll
  *  CSR      PGA_GAIN         LL_OPAMP_GetPGAGain
  * @param  p_opamp OPAMP instance
  * @note   Preliminarily, OPAMP must be set in mode PGA
  *         using function @ref LL_OPAMP_SetConfigurationMode().
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_PGA_GAIN_2
  *         @arg @ref LL_OPAMP_PGA_GAIN_4
  *         @arg @ref LL_OPAMP_PGA_GAIN_8
  *         @arg @ref LL_OPAMP_PGA_GAIN_16
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetPGAGain(const OPAMP_TypeDef *p_opamp)
{
  return (uint32_t)(READ_BIT(p_opamp->CSR, OPAMP_CSR_PGA_GAIN));
}

/**
  * @brief  Set OPAMP in one time configuration parameters.
  * @rmtoll
  *  CSR      CALON         LL_OPAMP_SetConfig \n
  *  CSR      OPAMODE       LL_OPAMP_SetConfig \n
  *  CSR      OPALPM        LL_OPAMP_SetConfig \n
  *  CSR      HSM           LL_OPAMP_SetConfig \n
  *  CSR      VM_SEL        LL_OPAMP_SetConfig \n
  *  CSR      VP_SEL        LL_OPAMP_SetConfig
  * @param  p_opamp OPAMP instance
  * @param  reg_value This parameter is a concatenation of bits CALON,
  *                   OPAMODE, OPALPM,
  *                   HSM,
  *                   VM_SEL, VP_SEL
  * @note   Preliminarily, OPAMP must be disabled.
  */
__STATIC_INLINE void LL_OPAMP_SetConfig(OPAMP_TypeDef *p_opamp, uint32_t reg_value)
{
  MODIFY_REG(p_opamp->CSR, ((OPAMP_CSR_CALON)                                       /* To set functional mode */
                            | (uint32_t)(OPAMP_CSR_OPAMODE_1 | OPAMP_CSR_OPAMODE_0) /* To set configuration mode */
                            | (uint32_t)(OPAMP_CSR_OPALPM)                          /* To set low power mode */
                            | (uint32_t)(OPAMP_CSR_HSM)                             /* To set high speed mode */
                            | (uint32_t)(OPAMP_CSR_VM_SEL)                          /* To set inverting input */
                            | (uint32_t)(OPAMP_CSR_VP_SEL)                          /* To set non inverting input */
                           ), reg_value);
}

/**
  * @brief  Get OPAMP configuration parameters bit fields.
  * @rmtoll
  *  CSR      CALON         LL_OPAMP_GetConfig \n
  *  CSR      OPAMODE       LL_OPAMP_GetConfig \n
  *  CSR      OPALPM        LL_OPAMP_GetConfig \n
  *  CSR      HSM           LL_OPAMP_GetConfig \n
  *  CSR      VM_SEL        LL_OPAMP_GetConfig \n
  *  CSR      VP_SEL        LL_OPAMP_GetConfig
  * @param  p_opamp OPAMP instance
  * @retval Returned value is the contents of CSR register
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetConfig(const OPAMP_TypeDef *p_opamp)
{
  return (uint32_t)(READ_REG(p_opamp->CSR));
}

/**
  * @}
  */

/** @defgroup OPAMP_LL_EF_CONFIGURATION_INPUTS Configuration of OPAMP inputs
  * @{
  */

/**
  * @brief  Set OPAMP non-inverting input connection.
  * @rmtoll
  *  CSR      VPSEL          LL_OPAMP_SetInputNonInverting
  * @param  p_opamp OPAMP instance
  * @param  input_non_inverting This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO0
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_DAC1_CH1
  */
__STATIC_INLINE void LL_OPAMP_SetInputNonInverting(OPAMP_TypeDef *p_opamp, uint32_t input_non_inverting)
{
  MODIFY_REG(p_opamp->CSR, OPAMP_CSR_VP_SEL, input_non_inverting);
}

/**
  * @brief  Get OPAMP non-inverting input connection.
  * @rmtoll
  *  CSR      VPSEL          LL_OPAMP_GetInputNonInverting
  * @param  p_opamp OPAMP instance
  * @retval Returned value can be one of the following values:
  *         This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO0
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_DAC1_CH1
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetInputNonInverting(const OPAMP_TypeDef *p_opamp)
{
  return (uint32_t)(READ_BIT(p_opamp->CSR, OPAMP_CSR_VP_SEL));
}

/**
  * @brief  Set OPAMP inverting input connection.
  * @rmtoll
  *  CSR      VMSEL          LL_OPAMP_SetInputInverting
  * @param  p_opamp OPAMP instance
  * @param  input_inverting This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO0
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO1
  *         @arg @ref LL_OPAMP_INPUT_INVERT_CONNECT_NO
  * @note   OPAMP inverting input is used with OPAMP in mode standalone
  *         or PGA with external capacitors for filtering circuit.
  *         Otherwise (OPAMP in mode follower), OPAMP inverting input
  *         is not used (not connected to GPIO pin).
  */
__STATIC_INLINE void LL_OPAMP_SetInputInverting(OPAMP_TypeDef *p_opamp, uint32_t input_inverting)
{
  MODIFY_REG(p_opamp->CSR, OPAMP_CSR_VM_SEL, input_inverting);
}

/**
  * @brief  Get OPAMP inverting input connection.
  * @rmtoll
  *  CSR      VMSEL          LL_OPAMP_GetInputInverting
  * @param  p_opamp OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO0
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO1
  *         @arg @ref LL_OPAMP_INPUT_INVERT_CONNECT_NO
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetInputInverting(const OPAMP_TypeDef *p_opamp)
{
  return (uint32_t)(READ_BIT(p_opamp->CSR, OPAMP_CSR_VM_SEL));
}

/**
  * @brief  Set OPAMP both inverting input and non-inverting input connections.
  * @rmtoll
  *  CSR      VPSEL          LL_OPAMP_SetInputs \n
  *  CSR      VMSEL          LL_OPAMP_SetInputs
  * @param  p_opamp OPAMP instance
  * @param  input_non_inverting This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO0
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_DAC1_CH1
  * @param  input_inverting This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO0
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO1
  *         @arg @ref LL_OPAMP_INPUT_INVERT_CONNECT_NO
  * @note   OPAMP inverting input is used with OPAMP in mode standalone
  *         or PGA with external capacitors for filtering circuit.
  *         Otherwise (OPAMP in mode follower), OPAMP inverting input
  *         is not used (not connected to GPIO pin).
  */
__STATIC_INLINE void LL_OPAMP_SetInputs(OPAMP_TypeDef *p_opamp,
                                        uint32_t input_non_inverting, uint32_t input_inverting)
{
  MODIFY_REG(p_opamp->CSR, (OPAMP_CSR_VP_SEL | OPAMP_CSR_VM_SEL), (input_non_inverting | input_inverting));
}

/**
  * @brief  Get OPAMP both non-inverting input and inverting input connection.
  * @rmtoll
  *  CSR      VPSEL          LL_OPAMP_GetInputs \n
  *  CSR      VMSEL          LL_OPAMP_GetInputs
  * @param  p_opamp OPAMP instance
  * @retval Returned value is inverting input and non-inverting input both contained in an uint32_t.
  *         This bit field contains the following values inside the [31,0] bit field:
  *         VP_SEL bit [10]
  *         VM_SEL bit [9,8]
  *         Those parameters can be one of the following values
  *         for VP_SEL:
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO0
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_DAC1_CH1
  *         for VM_SEL:
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO0
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO1
  *         @arg @ref LL_OPAMP_INPUT_INVERT_CONNECT_NO
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetInputs(const OPAMP_TypeDef *p_opamp)
{
  return (uint32_t)(READ_BIT(p_opamp->CSR, (OPAMP_CSR_VP_SEL | OPAMP_CSR_VM_SEL)));
}
/**
  * @}
  */

/** @defgroup OPAMP_LL_EF_Configuration_Legacy_Functions Configuration of OPAMP, legacy functions name
  * @{
  */
/* Old functions name kept for legacy purpose, to be replaced by the          */
/* current functions name.                                                    */
__STATIC_INLINE void LL_OPAMP_SetNonInvertingInput(OPAMP_TypeDef *p_opamp, uint32_t non_inverting_input)
{
  LL_OPAMP_SetInputNonInverting(p_opamp, non_inverting_input);
}

__STATIC_INLINE void LL_OPAMP_SetInvertingInput(OPAMP_TypeDef *p_opamp, uint32_t inverting_input)
{
  LL_OPAMP_SetInputInverting(p_opamp, inverting_input);
}

__STATIC_INLINE void LL_OPAMP_SetFunctionalMode(OPAMP_TypeDef *p_opamp, uint32_t mode)
{
  LL_OPAMP_SetConfigurationMode(p_opamp, mode);
}

__STATIC_INLINE uint32_t LL_OPAMP_GetFunctionalMode(const OPAMP_TypeDef *p_opamp)
{
  return (uint32_t) LL_OPAMP_GetConfigurationMode(p_opamp);
}

/**
  * @}
  */
/** @defgroup OPAMP_LL_EF_OPAMP_TRIMMING Configuration and operation of OPAMP trimming
  * @{
  */

/**
  * @brief  Set OPAMP trimming mode.
  * @rmtoll
  *  CSR      USERTRIM       LL_OPAMP_SetTrimmingMode
  * @param  p_opamp OPAMP instance
  * @param  trimming_mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_FACTORY
  *         @arg @ref LL_OPAMP_TRIMMING_USER
  */
__STATIC_INLINE void LL_OPAMP_SetTrimmingMode(OPAMP_TypeDef *p_opamp, uint32_t trimming_mode)
{
  MODIFY_REG(p_opamp->CSR, OPAMP_CSR_USERTRIM, trimming_mode);
}

/**
  * @brief  Get OPAMP trimming mode.
  * @rmtoll
  *  CSR      USERTRIM       LL_OPAMP_GetTrimmingMode
  * @param  p_opamp OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_FACTORY
  *         @arg @ref LL_OPAMP_TRIMMING_USER
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetTrimmingMode(const OPAMP_TypeDef *p_opamp)
{
  return (uint32_t)(READ_BIT(p_opamp->CSR, OPAMP_CSR_USERTRIM));
}

/**
  * @brief  Set OPAMP offset to calibrate the selected transistors
  *         differential pair NMOS or PMOS.
  * @rmtoll
  *  CSR      CALSEL         LL_OPAMP_SetCalibrationSelection
  * @param  p_opamp OPAMP instance
  * @param  transistors_diff_pair This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS
  * @note   Preliminarily, OPAMP must be set in mode calibration
  *         using function @ref LL_OPAMP_SetMode().
  */
__STATIC_INLINE void LL_OPAMP_SetCalibrationSelection(OPAMP_TypeDef *p_opamp, uint32_t transistors_diff_pair)
{
  /* Parameter used with mask "OPAMP_TRIMMING_SELECT_MASK" because            */
  /* containing other bits reserved for other purpose.                        */
  MODIFY_REG(p_opamp->CSR, OPAMP_CSR_CALSEL, (transistors_diff_pair & OPAMP_TRIMMING_SELECT_MASK));
}

/**
  * @brief  Get OPAMP offset to calibrate the selected transistors
  *         differential pair NMOS or PMOS.
  * @rmtoll
  *  CSR      CALSEL         LL_OPAMP_GetCalibrationSelection
  * @param  p_opamp OPAMP instance
  * @note   Preliminarily, OPAMP must be set in mode calibration
  *         using function @ref LL_OPAMP_SetMode().
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetCalibrationSelection(const OPAMP_TypeDef *p_opamp)
{
  uint32_t calib_sel = (uint32_t)(READ_BIT(p_opamp->CSR, OPAMP_CSR_CALSEL));

  return (calib_sel | (((calib_sel & OPAMP_CSR_CALSEL) == 0UL) ? LL_OPAMP_TRIMMING_NMOS : LL_OPAMP_TRIMMING_PMOS));
}

/**
  * @brief  Get OPAMP calibration result of toggling output.
  * @rmtoll
  *  CSR      CALOUT         LL_OPAMP_IsCalibrationOutputSet
  * @param  p_opamp OPAMP instance
  * @retval 0 If the offset is not enough compensated with the current trim offset value.
  * @retval 1 If the offset is enough compensated.
  */
__STATIC_INLINE uint32_t LL_OPAMP_IsCalibrationOutputSet(const OPAMP_TypeDef *p_opamp)
{
  return ((READ_BIT(p_opamp->CSR, OPAMP_CSR_CALOUT) == OPAMP_CSR_CALOUT) ? 1UL : 0UL);
}

/**
  * @brief  Set OPAMP trimming factor for the selected transistors
  *         differential pair NMOS or PMOS, corresponding to the selected
  *         power mode.
  * @rmtoll
  *  OTR      TRIMOFFSETN    LL_OPAMP_SetTrimmingValue \n
  *  OTR      TRIMOFFSETP    LL_OPAMP_SetTrimmingValue \n
  *  LPOTR    TRIMLPOFFSETN  LL_OPAMP_SetTrimmingValue \n
  *  LPOTR    TRIMLPOFFSETP  LL_OPAMP_SetTrimmingValue
  * @param  p_opamp OPAMP instance
  * @param  power_mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWER_MODE_NORMAL
  *         @arg @ref LL_OPAMP_POWER_MODE_LOW
  * @param  transistors_diff_pair This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS
  * @param  trimming_value 0x00...0x1F
  */
__STATIC_INLINE void LL_OPAMP_SetTrimmingValue(OPAMP_TypeDef *p_opamp, uint32_t power_mode,
                                               uint32_t transistors_diff_pair, uint32_t trimming_value)
{
  __IO uint32_t *preg = OPAMP_PTR_REG_OFFSET(p_opamp->OTR, (power_mode & OPAMP_POWERMODE_OTR_REGOFFSET_MASK));

  /* Set bits with position in register depending on parameter                */
  /* "transistors_diff_pair".                                                 */
  /* Parameter used with mask "OPAMP_TRIMMING_VALUE_MASK" because             */
  /* containing other bits reserved for other purpose.                        */
  MODIFY_REG(*preg,
             (transistors_diff_pair & OPAMP_TRIMMING_VALUE_MASK),
             (trimming_value << ((transistors_diff_pair == LL_OPAMP_TRIMMING_NMOS) ?
                                 OPAMP_OTR_TRIMOFFSETN_Pos : OPAMP_OTR_TRIMOFFSETP_Pos))
            );
}

/**
  * @brief  Get OPAMP trimming factor for the selected transistors
  *         differential pair NMOS or PMOS, corresponding to the selected
  *         power mode.
  * @rmtoll
  *  OTR      TRIMOFFSETN    LL_OPAMP_GetTrimmingValue \n
  *  OTR      TRIMOFFSETP    LL_OPAMP_GetTrimmingValue \n
  *  LPOTR    TRIMLPOFFSETN  LL_OPAMP_GetTrimmingValue \n
  *  LPOTR    TRIMLPOFFSETP  LL_OPAMP_GetTrimmingValue
  * @param  p_opamp OPAMP instance
  * @param  power_mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWER_MODE_NORMAL
  *         @arg @ref LL_OPAMP_POWER_MODE_LOW
  * @param  transistors_diff_pair This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS
  * @retval 0x0...0x1F
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetTrimmingValue(const OPAMP_TypeDef *p_opamp, uint32_t power_mode,
                                                   uint32_t transistors_diff_pair)
{
  const __IO uint32_t *preg = OPAMP_PTR_REG_OFFSET(p_opamp->OTR, (power_mode & OPAMP_POWERMODE_OTR_REGOFFSET_MASK));

  /* Retrieve bits with position in register depending on parameter           */
  /* "transistors_diff_pair".                                                 */
  /* Parameter used with mask "OPAMP_TRIMMING_VALUE_MASK" because             */
  /* containing other bits reserved for other purpose.                        */
  return (uint32_t)(READ_BIT(*preg, (transistors_diff_pair & OPAMP_TRIMMING_VALUE_MASK))
                    >> ((transistors_diff_pair == LL_OPAMP_TRIMMING_NMOS) ?
                        OPAMP_OTR_TRIMOFFSETN_Pos : OPAMP_OTR_TRIMOFFSETP_Pos)
                   );
}

/**
  * @brief  Set OPAMP trimming factor for the selected transistors
  *         differential pair NMOS or PMOS, corresponding to the selected
  *         power mode.
  * @rmtoll
  *  OTR      TRIMOFFSETN    LL_OPAMP_SetOffsetTrimValue \n
  *  OTR      TRIMOFFSETP    LL_OPAMP_SetOffsetTrimValue \n
  *  LPOTR    TRIMLPOFFSETN  LL_OPAMP_SetOffsetTrimValue \n
  *  LPOTR    TRIMLPOFFSETP  LL_OPAMP_SetOffsetTrimValue
  * @param  p_opamp OPAMP instance
  * @param  power_mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWER_MODE_NORMAL
  *         @arg @ref LL_OPAMP_POWER_MODE_LOW
  * @param  transistors_diff_pair This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS
  * @param  trimming_value 0x00...0x1F
  */
__STATIC_INLINE void LL_OPAMP_SetOffsetTrimValue(OPAMP_TypeDef *p_opamp, uint32_t power_mode,
                                                 uint32_t transistors_diff_pair, uint32_t trimming_value)
{
  __IO uint32_t *preg = OPAMP_REG_OTR_LPOTR(p_opamp, power_mode);

  /* Set bits with position in register depending on parameter    */
  /* "transistors_diff_pair".                                     */
  /* Parameter used with mask "OPAMP_TRIMMING_VALUE_MASK" because */
  /* containing other bits reserved for other purpose.            */
  MODIFY_REG(*preg,
             (transistors_diff_pair & OPAMP_TRIMMING_VALUE_MASK),
             (trimming_value << ((transistors_diff_pair == LL_OPAMP_TRIMMING_NMOS) ?
                                 OPAMP_OTR_TRIMOFFSETN_Pos : OPAMP_OTR_TRIMOFFSETP_Pos
                                ))
            );
}

/**
  * @brief  Get OPAMP trimming factor for the selected transistors
  *         differential pair NMOS or PMOS, corresponding to the selected
  *         power mode.
  * @rmtoll
  *  OTR      TRIMOFFSETN    LL_OPAMP_GetOffsetTrimValue \n
  *  OTR      TRIMOFFSETP    LL_OPAMP_GetOffsetTrimValue \n
  *  LPOTR    TRIMLPOFFSETN  LL_OPAMP_GetOffsetTrimValue \n
  *  LPOTR    TRIMLPOFFSETP  LL_OPAMP_GetOffsetTrimValue
  * @param  p_opamp OPAMP instance
  * @param  power_mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWER_MODE_NORMAL
  *         @arg @ref LL_OPAMP_POWER_MODE_LOW
  * @param  transistors_diff_pair This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS
  * @retval 0x0...0x1F
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetOffsetTrimValue(const OPAMP_TypeDef *p_opamp, uint32_t power_mode,
                                                     uint32_t transistors_diff_pair)
{
  const __IO uint32_t *preg = OPAMP_REG_OTR_LPOTR(p_opamp, power_mode);

  /* Retrieve bits with position in register depending on parameter */
  /* "transistors_diff_pair".                                       */
  /* Parameter used with mask "OPAMP_TRIMMING_VALUE_MASK" because   */
  /* containing other bits reserved for other purpose.              */
  return (uint32_t)(READ_BIT(*preg, (transistors_diff_pair & OPAMP_TRIMMING_VALUE_MASK))
                    >> ((transistors_diff_pair == LL_OPAMP_TRIMMING_NMOS) ?
                        OPAMP_OTR_TRIMOFFSETN_Pos : OPAMP_OTR_TRIMOFFSETP_Pos
                       )
                   );
}

/**
  * @brief  Set OPAMP all differential pair trimming (PMOS and NMOS) values for the selected power mode.
  * @rmtoll
  *  OTR      TRIMOFFSETN    LL_OPAMP_SetOffsetTrimAllValue \n
  *  OTR      TRIMOFFSETP    LL_OPAMP_SetOffsetTrimAllValue \n
  *  LPOTR    TRIMLPOFFSETN  LL_OPAMP_SetOffsetTrimAllValue \n
  *  LPOTR    TRIMLPOFFSETP  LL_OPAMP_SetOffsetTrimAllValue
  * @param  p_opamp OPAMP instance
  * @param  power_mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWER_MODE_NORMAL
  *         @arg @ref LL_OPAMP_POWER_MODE_LOW
  * @param  p_trim_value 0x00...0x1F
  * @param  n_trim_value 0x00...0x1F
  */
__STATIC_INLINE void LL_OPAMP_SetOffsetTrimAllValue(OPAMP_TypeDef *p_opamp, uint32_t power_mode,
                                                    uint32_t p_trim_value, uint32_t n_trim_value)
{
  __IO uint32_t *preg = OPAMP_REG_OTR_LPOTR(p_opamp, power_mode);

  /* Set bits in register OTR or LPOTR depending on parameter power_mode */
  MODIFY_REG(*preg,
             OPAMP_TRIMMING_VALUE_MASK,
             ((((p_trim_value) << OPAMP_OTR_TRIMOFFSETP_Pos) | ((n_trim_value) << OPAMP_OTR_TRIMOFFSETN_Pos))
              & (OPAMP_TRIMMING_VALUE_MASK)
             )
            );
}

/**
  * @brief  Get OPAMP PMOS and NMOS differential pair trimming values for the selected power mode.
  * @rmtoll
  *  OTR      TRIMOFFSETN    LL_OPAMP_GetOffsetTrimAllValue \n
  *  OTR      TRIMOFFSETP    LL_OPAMP_GetOffsetTrimAllValue \n
  *  LPOTR    TRIMLPOFFSETN  LL_OPAMP_GetOffsetTrimAllValue \n
  *  LPOTR    TRIMLPOFFSETP  LL_OPAMP_GetOffsetTrimAllValue
  * @param  p_opamp OPAMP instance
  * @param  power_mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWER_MODE_NORMAL
  *         @arg @ref LL_OPAMP_POWER_MODE_LOW
  * @retval 0x0...0x1F
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetOffsetTrimAllValue(const OPAMP_TypeDef *p_opamp, uint32_t power_mode)
{
  const __IO uint32_t *preg = OPAMP_REG_OTR_LPOTR(p_opamp, power_mode);

  /* Retrieve bits with position in register depending on parameter           */
  /* "transistors_diff_pair".                                                   */
  /* Parameter used with mask "OPAMP_TRIMMING_VALUE_MASK" because             */
  /* containing other bits reserved for other purpose.                        */
  return (uint32_t)(READ_BIT(*preg, (OPAMP_TRIMMING_VALUE_MASK)));
}

/**
  * @}
  */

/** @defgroup OPAMP_LL_EF_OPERATION Operation on OPAMP instance
  * @{
  */
/**
  * @brief  Enable OPAMP instance.
  * @rmtoll
  *  CSR      OPAMPXEN       LL_OPAMP_Enable
  * @param  p_opamp OPAMP instance
  * @note   After enable from off state, OPAMP requires a delay
  *         to fulfill wake up time specification.
  *         Refer to device datasheet, parameter "tWAKEUP".
  */
__STATIC_INLINE void LL_OPAMP_Enable(OPAMP_TypeDef *p_opamp)
{
  SET_BIT(p_opamp->CSR, OPAMP_CSR_OPAEN);
}

/**
  * @brief  Disable OPAMP instance.
  * @rmtoll
  *  CSR      OPAMPXEN       LL_OPAMP_Disable
  * @param  p_opamp OPAMP instance
  */
__STATIC_INLINE void LL_OPAMP_Disable(OPAMP_TypeDef *p_opamp)
{
  CLEAR_BIT(p_opamp->CSR, OPAMP_CSR_OPAEN);
}

/**
  * @brief  Get OPAMP instance enable state
  * @rmtoll
  *  CSR      OPAMPXEN       LL_OPAMP_IsEnabled
  * @param  p_opamp OPAMP instance
  * @retval 1 if OPAMP is enabled.
  * @retval 0 if OPAMP is disabled.
  */
__STATIC_INLINE uint32_t LL_OPAMP_IsEnabled(const OPAMP_TypeDef *p_opamp)
{
  return ((READ_BIT(p_opamp->CSR, OPAMP_CSR_OPAEN) == (OPAMP_CSR_OPAEN)) ? 1UL : 0UL);
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
#endif /* OPAMP1 || OPAMP2 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_LL_OPAMP_H */

