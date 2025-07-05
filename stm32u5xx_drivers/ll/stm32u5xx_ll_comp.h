/**
  ******************************************************************************
  * @file    stm32u5xx_ll_comp.h
  * @brief   Header file of COMP LL module.
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
#ifndef STM32U5XX_LL_COMP_H
#define STM32U5XX_LL_COMP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined (COMP1) || defined (COMP2)

/** @defgroup COMP_LL COMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup COMP_LL_Private_Constants COMP Private Constants
  * @{
  */

/* Internal masks and bitfields for pair of comparators instances window mode
To select into literals LL_COMP_WINDOW_x the relevant bits for (concatenation of multiple bits used in different
registers):
- Comparator instance selected as master for window mode : register offset
- Window mode enable or disable: bit value */
#define LL_COMP_WINDOW_COMP_ODD_REGOFFSET_MASK  (0x00000000UL) /* Register of COMP instance odd (COMP1_CSR, ...)
                                        defined as reference register */
#define LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK (0x00000001UL) /* Register of COMP instance even (COMP2_CSR, ...)
                                        offset vs register of COMP instance odd */
#define LL_COMP_WINDOW_COMP_REGOFFSET_MASK (LL_COMP_WINDOW_COMP_ODD_REGOFFSET_MASK \
                                            | LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK)
#define LL_COMP_WINDOW_COMP_X_SETTING_MASK (COMP_CSR_WINMODE) /* Bitfield to select window mode */
#define LL_COMP_WINDOW_OUT_SETTING_MASK (COMP_CSR_WINOUT) /* Bitfield to select window output */
#define LL_COMP_WINDOW_OUT_XOR_BOTH_MASK (COMP_CSR_WINOUT << 1UL) /* Differentiator of window output settings */
#define LL_COMP_WINDOW_OUT_XOR_BOTH_POS_VS_WINDOW (1UL) /* Bitfields position differences between
                                        LL_COMP_WINDOW_OUT_XOR_BOTH_MASK and LL_COMP_WINDOW_COMP_X_SETTING_MASK */

/* COMP instances relative position in COMP common instance */
#define LL_COMP_WINDOW_COMP_ODD         (LL_COMP_WINDOW_COMP_ODD_REGOFFSET_MASK)  /* Comparator instance odd
                                        (COMP1, ...) */
#define LL_COMP_WINDOW_COMP_EVEN        (LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK) /* Comparator instance even
                                        (COMP2, ...) */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup COMP_LL_Private_Macros COMP Private Macros
  * @{
  */

/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  __REG__ Register basis from which the offset is applied.
  * @param  __REG_OFFFSET__ Offset to be applied (unit: number of registers).
  * @retval Pointer to register address.
  */
#define LL_COMP_PTR_REG_OFFSET(__REG__, __REG_OFFFSET__) \
  ((__IO uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFFSET__) << 2UL))))

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Constants COMP Exported Constants
  * @{
  */

#if defined(COMP_WINDOW_MODE_SUPPORT)
/** @defgroup COMP_LL_EC_COMMON_WINDOWMODE Comparator common modes - Window mode
  * @{
  */
#define LL_COMP_WINDOW_DISABLE          (0x00000000UL) /*!< Window mode disable: comparators pair are independent */
#define LL_COMP_WINDOW_INPUT_PLUS_ODD   (COMP_CSR_WINMODE | LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK) /*!< Window mode
                                        enable: comparators instances pair have their input plus connected together.
                                        The common input is the one of instance index odd (COMP1, ...).
                                        Input plus of the other comparator is no more accessible. */
#define LL_COMP_WINDOW_INPUT_PLUS_EVEN  (COMP_CSR_WINMODE | LL_COMP_WINDOW_COMP_ODD_REGOFFSET_MASK) /*!< Window mode
                                        enable: comparators instances pair have their input plus connected together.
                                        The common input is the one of instance index even (COMP2, ...).
                                        Input plus of the other comparator is no more accessible. */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_COMMON_WINDOWOUTPUT Comparator common modes - Window output
  * @{
  */
#define LL_COMP_WINDOW_OUTPUT_INDEPT    (0x00000000UL)/*!< Comparators window output default mode:
                                        both comparators output are independent, indicating each their own state.
                                        Note: To know signal state versus window thresholds, read each comparator
                                              output and perform a logical "exclusive or" operation. */
#define LL_COMP_WINDOW_OUTPUT_XOR_ODD   (COMP_CSR_WINOUT | LL_COMP_WINDOW_COMP_ODD_REGOFFSET_MASK)  /*!< Window output
                                        synthesized on COMP1 output: COMP1 output is no more indicating its own state,
                                        but global window mode state. Logical high means monitored signal is within
                                        comparators window.
                                        Note: impacts only comparator output signal level (propagated to GPIO, EXTI
                                              lines, timers, ...), does not impact output digital state
                                              (@ref LL_COMP_ReadOutputLevel()) always reflecting each comparator
                                              output state.*/
#define LL_COMP_WINDOW_OUTPUT_XOR_EVEN  (COMP_CSR_WINOUT | LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK) /*!< Window output
                                        synthesized on COMP2 output: COMP2 output is no more indicating its own state,
                                        but global window mode state. Logical high means monitored signal is within
                                        comparators window.
                                        Note: impacts only comparator output signal level (propagated to GPIO, EXTI
                                              lines, timers, ...), does not impact output digital state
                                              (@ref LL_COMP_ReadOutputLevel()) always reflecting each comparator
                                              output state.*/
#define LL_COMP_WINDOW_OUTPUT_XOR_BOTH  (COMP_CSR_WINOUT | LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK \
                                         | LL_COMP_WINDOW_OUT_XOR_BOTH_MASK) /*!< Window output synthesized on both
                                        comparators output of pair of comparator selected (COMP1 and COMP2):
                                        both comparators outputs are no more indicating their own state, but global
                                        window mode state (XOR: logical "exclusive or"). Logical high means monitored
                                        signal is within comparators window thresholds).
                                        This is a specific configuration (technically possible but not relevant from
                                        application point of view: 2 comparators output used for the same signal level),
                                        standard configuration for window mode is one of the settings above.
                                        Note: impacts only comparator output signal level (propagated to GPIO, EXTI
                                              lines, timers, ...), does not impact output digital state
                                              (@ref LL_COMP_ReadOutputLevel()) always reflecting each comparator
                                              output state.*/
/**
  * @}
  */

#endif /* COMP_WINDOW_MODE_SUPPORT */
/** @defgroup COMP_LL_EC_POWERMODE Comparator modes - Power mode
  * @{
  */
#define LL_COMP_POWERMODE_HIGHSPEED     (0x00000000UL)         /*!< Comparator power mode to high speed */
#define LL_COMP_POWERMODE_MEDIUMSPEED   (COMP_CSR_PWRMODE_0)   /*!< Comparator power mode to medium speed */
#define LL_COMP_POWERMODE_ULTRALOWPOWER (COMP_CSR_PWRMODE_1 | COMP_CSR_PWRMODE_0) /*!< Comparator power mode to ultra-low power */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_PLUS Comparator inputs - Input plus (input non-inverting) selection
  * @{
  */
#define LL_COMP_INPUT_PLUS_IO1          (0x00000000UL)       /*!< Comparator input plus connected to IO1
                                        (for GPIO mapping, refer to datasheet parameters "COMPx_INP1") */
#define LL_COMP_INPUT_PLUS_IO2          (COMP_CSR_INPSEL_0)  /*!< Comparator input plus connected to IO2
                                        (for GPIO mapping, refer to datasheet parameters "COMPx_INP2") */
#define LL_COMP_INPUT_PLUS_IO3          (COMP_CSR_INPSEL_1)  /*!< Comparator input plus connected to IO3
                                        (for GPIO mapping, refer to datasheet parameters "COMPx_INP3") */
#if defined(COMP_CSR_INPSEL_2)
#define LL_COMP_INPUT_PLUS_IO4          (COMP_CSR_INPSEL_1 | COMP_CSR_INPSEL_0) /*!< Comparator input plus connected
                                        to IO4 (for GPIO mapping, refer to datasheet parameters "COMPx_INP4") */
#define LL_COMP_INPUT_PLUS_IO5          (COMP_CSR_INPSEL_2)                     /*!< Comparator input plus connected
                                        to IO5 (for GPIO mapping, refer to datasheet parameters "COMPx_INP5") */
#define LL_COMP_INPUT_PLUS_IO6          (COMP_CSR_INPSEL_2 | COMP_CSR_INPSEL_0) /*!< Comparator input plus connected
                                        to IO6 (for GPIO mapping, refer to datasheet parameters "COMPx_INP6") */
#endif /* COMP_CSR_INPSEL_2 */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_MINUS Comparator inputs - Input minus (input inverting) selection
  * @{
  */
#define LL_COMP_INPUT_MINUS_VREFINT     (COMP_CSR_INMSEL_1 | COMP_CSR_INMSEL_0) /*!< Comparator input minus connected
                                        to VrefInt (for VrefInt voltage value, refer to datasheet). */
#define LL_COMP_INPUT_MINUS_1_4VREFINT  (0x00000000UL)      /*!< Comparator input minus connected to 1/4 VrefInt
                                        (for VrefInt voltage value, refer to datasheet). */
#define LL_COMP_INPUT_MINUS_1_2VREFINT  (COMP_CSR_INMSEL_0) /*!< Comparator input minus connected to 1/2 VrefInt
                                        (for VrefInt voltage value, refer to datasheet). */
#define LL_COMP_INPUT_MINUS_3_4VREFINT  (COMP_CSR_INMSEL_1) /*!< Comparator input minus connected to 3/4 VrefInt
                                        (for VrefInt voltage value, refer to datasheet). */
#define LL_COMP_INPUT_MINUS_IO1         (COMP_CSR_INMSEL_2 | COMP_CSR_INMSEL_1) /*!< Comparator input plus connected
                                        to IO1 (for GPIO mapping, refer to datasheet parameters "COMPx_INM1") */
#define LL_COMP_INPUT_MINUS_IO2         (COMP_CSR_INMSEL_2 | COMP_CSR_INMSEL_1 | COMP_CSR_INMSEL_0) /*!< Comparator
                                        input plus connected to IO2 (for GPIO mapping, refer to datasheet
                                        parameters "COMPx_INM2") */
#define LL_COMP_INPUT_MINUS_DAC1_CH1    (COMP_CSR_INMSEL_2) /*!< Comparator input minus connected
                                        to DAC1 channel 1 */
#define LL_COMP_INPUT_MINUS_DAC1_CH2    (COMP_CSR_INMSEL_2 | COMP_CSR_INMSEL_0) /*!< Comparator input minus connected
                                        to DAC1 channel 2 */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_HYSTERESIS Comparator input - Hysteresis
  * @{
  */
#define LL_COMP_HYSTERESIS_NONE         (0x00000000UL)                      /*!< No hysteresis */
#define LL_COMP_HYSTERESIS_LOW          (COMP_CSR_HYST_0)                   /*!< Hysteresis level low */
#define LL_COMP_HYSTERESIS_MEDIUM       (COMP_CSR_HYST_1)                   /*!< Hysteresis level medium */
#define LL_COMP_HYSTERESIS_HIGH         (COMP_CSR_HYST_1 | COMP_CSR_HYST_0) /*!< Hysteresis level high */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_POLARITY Comparator output - Output polarity
  * @{
  */
#define LL_COMP_OUTPUTPOL_NONINVERTED   (0x00000000UL) /*!< Comparator output polarity not inverted:
                                        comparator output at high level when input voltages: plus higher than minus */
#define LL_COMP_OUTPUTPOL_INVERTED      (COMP_CSR_POLARITY)   /*!< Comparator output polarity not inverted:
                                        comparator output at low level when input voltages: plus higher than minus */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_BLANKING_SOURCE Comparator output - Blanking source
  * @{
  */
#define LL_COMP_BLANKINGSRC_NONE        (0x00000000UL)        /*!< Comparator output without blanking */
#define LL_COMP_BLANKINGSRC_TIM1_OC5    (COMP_CSR_BLANKSEL_0) /*!< Comparator output blanking source TIM1 OC5
                                        (specific to comparator instance: COMP1) */
#define LL_COMP_BLANKINGSRC_TIM2_OC3    (COMP_CSR_BLANKSEL_1) /*!< Comparator output blanking source TIM2 OC3
                                        (specific to comparator instance: COMP1) */
#define LL_COMP_BLANKINGSRC_TIM3_OC3    (COMP_CSR_BLANKSEL_2) /*!< Comparator output blanking source TIM3 OC3
                                        (specific to comparator instance: COMP1) */
#define LL_COMP_BLANKINGSRC_TIM3_OC4    (COMP_CSR_BLANKSEL_0) /*!< Comparator output blanking source TIM3 OC4
                                        (specific to comparator instance: COMP2) */
#define LL_COMP_BLANKINGSRC_TIM8_OC5    (COMP_CSR_BLANKSEL_1) /*!< Comparator output blanking source TIM8 OC5
                                        (specific to comparator instance: COMP2) */
#define LL_COMP_BLANKINGSRC_TIM15_OC1   (COMP_CSR_BLANKSEL_2) /*!< Comparator output blanking source TIM15 OC1
                                        (specific to comparator instance: COMP2) */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_LEVEL Comparator output - Output level
  * @{
  */
#define LL_COMP_OUTPUT_LEVEL_LOW        (0x00000000UL) /*!< Comparator output level low (with polarity not inverted) */
#define LL_COMP_OUTPUT_LEVEL_HIGH       (0x00000001UL) /*!< Comparator output level high (with polarity not inverted) */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_HW_DELAYS  Definitions of COMP hardware constraints delays
  * @note   Only COMP peripheral HW delays are defined in COMP LL driver driver, not timeout values.
  * @{
  */

/* Delay for comparator startup time.                                         */
/* Note: Delay required to reach propagation delay specification.             */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART").                                                       */
/* Unit: us                                                                   */
#define LL_COMP_DELAY_STARTUP_US        (80UL) /*!< Delay for comparator startup time.
                                        Delay set to maximum value (refer to device datasheet, parameter "tSTART").
                                        Unit: us.
                                        Note: At comparator enable, delay required to reach propagation delay
                                              specification. */

/* Delay for comparator voltage scaler stabilization time.                    */
/* Note: Voltage scaler is used when selecting comparator input               */
/*       based on VrefInt (VrefInt or subdivision of VrefInt).                */
/* Note: To get scaler bridge configuration,                                  */
/*       refer to @ref LL_COMP_IsInputScalerEnabled().                        */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART_SCALER").                                                */
/* Unit: us                                                                   */
#define LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US (220UL) /*!< Delay for comparator voltage scaler stabilization time
                                        Delay set to maximum value (refer to device datasheet,
                                        parameter "tSTART_SCALER").
                                        Unit: us.
                                        Note: Voltage scaler is used when selecting comparator input
                                              based on VrefInt (VrefInt or subdivision of VrefInt).
                                        Note: To get scaler bridge configuration,
                                              refer to @ref LL_COMP_IsInputScalerEnabled().
                                        */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Macros COMP Exported Macros
  * @{
  */
/** @defgroup COMP_LL_EM_WRITE_READ Common write and read registers macro
  * @{
  */

/**
  * @brief  Write a value in COMP register
  * @param  __INSTANCE__ comparator instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  */
#define LL_COMP_WRITE_REG(__INSTANCE__, __REG__, __VALUE__) WRITE_REG((__INSTANCE__)->__REG__, (__VALUE__))

/**
  * @brief  Read a value in COMP register
  * @param  __INSTANCE__ comparator instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_COMP_READ_REG(__INSTANCE__, __REG__) READ_REG((__INSTANCE__)->__REG__)
/**
  * @}
  */

/** @defgroup COMP_LL_EM_HELPER_MACRO COMP helper macro
  * @{
  */

/**
  * @brief  Helper macro to select the COMP common instance
  *         to which is belonging the selected COMP instance.
  * @note   COMP common register instance can be used to
  *         set parameters common to several COMP instances.
  *         Refer to functions having argument "p_comp_common" as parameter.
  * @param  instance COMP instance
  * @retval COMP common instance or value "0" if there is no COMP common instance.
  */
#define LL_COMP_COMMON_INSTANCE(instance) (COMP12_COMMON)

/**
  * @brief  Helper macro to define comparator instance position generic identification (odd or even)
  *         from comparator instance.
  * @param  instance Comparator instance.
  * @retval Comparator common instance or value "0" if there is no COMP common instance.
  */
#define LL_COMP_WINDOW_INST_POS_ID(instance)                                   \
  ((((instance) == COMP1))                                                     \
   ? ((LL_COMP_WINDOW_COMP_ODD))                                               \
   :                                                                           \
   ((LL_COMP_WINDOW_COMP_EVEN))                                                \
  )

/**
  * @brief  Helper macro to select literal LL_COMP_WINDOW_INPUT_PLUS_x with suffix odd or even
  *         from comparator instance.
  * @note   Helper macro intended to be used with function LL_COMP_SetCommonWindowMode()
  * @param  instance COMP instance.
  * @retval COMP common instance or value "0" if there is no COMP common instance.
  */
#define LL_COMP_WINDOW_INST_TO_INPUT_PLUS(instance)                           \
  (((LL_COMP_WINDOW_INST_POS_ID(instance) == LL_COMP_WINDOW_COMP_ODD))        \
   ? ((LL_COMP_WINDOW_INPUT_PLUS_ODD))                                        \
   :                                                                          \
   ((LL_COMP_WINDOW_INPUT_PLUS_EVEN))                                         \
  )

/**
  * @brief  Helper macro to select literal LL_COMP_WINDOW_OUTPUT_x with suffix odd or even
  *         from comparator instance.
  * @note   Helper macro intended to be used with function LL_COMP_SetCommonWindowOutput()
  * @param  instance COMP instance.
  * @retval COMP common instance or value "0" if there is no COMP common instance.
  */
#define LL_COMP_WINDOW_INST_TO_OUTPUT(instance)                               \
  (((LL_COMP_WINDOW_INST_POS_ID(instance) == LL_COMP_WINDOW_COMP_ODD))        \
   ? ((LL_COMP_WINDOW_OUTPUT_XOR_ODD))                                        \
   :                                                                          \
   ((LL_COMP_WINDOW_OUTPUT_XOR_EVEN))                                         \
  )
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Functions COMP Exported Functions
  * @{
  */

#if defined(COMP_WINDOW_MODE_SUPPORT)
/** @defgroup COMP_LL_EF_Configuration_comparator_common Configuration of COMP hierarchical scope:
  *           common to several COMP instances
  * @{
  */

/**
  * @brief  Set window mode of a pair of comparators instances
  *         (2 consecutive COMP instances COMP<x> and COMP<x+1>).
  * @rmtoll
  *  CSR      WINMODE        LL_COMP_SetCommonWindowMode
  * @param  p_comp_common Comparator common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref LL_COMP_COMMON_INSTANCE() )
  * @param  window_mode This parameter can be one of the following values:
  *         @arg @ref LL_COMP_WINDOW_DISABLE
  *         @arg @ref LL_COMP_WINDOW_INPUT_PLUS_ODD
  *         @arg @ref LL_COMP_WINDOW_INPUT_PLUS_EVEN
  *         Note: Parameters values with suffix odd or even can also be selected from comparator instance
  *               using helper macro LL_COMP_WINDOW_INST_TO_INPUT_PLUS.
  */
__STATIC_INLINE void LL_COMP_SetCommonWindowMode(COMP_Common_TypeDef *p_comp_common, uint32_t window_mode)
{
  /* Note: On this STM32 series, window mode can be set from any instance     */
  /*       of the pair of comparator instances.                               */

  __IO uint32_t *preg = LL_COMP_PTR_REG_OFFSET(p_comp_common->CSR_ODD,
                                               (window_mode & LL_COMP_WINDOW_COMP_REGOFFSET_MASK));

  /* Clear the potential previous setting of window mode */
  __IO uint32_t *preg_clear = LL_COMP_PTR_REG_OFFSET(p_comp_common->CSR_ODD,
                                                     (~(window_mode & LL_COMP_WINDOW_COMP_REGOFFSET_MASK) & 0x1UL)
                                                    );
  CLEAR_BIT(*preg_clear, COMP_CSR_WINMODE);

  /* Set window mode */
  MODIFY_REG(*preg, COMP_CSR_WINMODE, (window_mode & LL_COMP_WINDOW_COMP_X_SETTING_MASK));
}

/**
  * @brief  Get window mode of a pair of comparators instances
  *         (2 consecutive COMP instances COMP<x> and COMP<x+1>).
  * @rmtoll
  *  CSR      WINMODE        LL_COMP_GetCommonWindowMode
  * @param  p_comp_common Comparator common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref LL_COMP_COMMON_INSTANCE() ).
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_WINDOW_DISABLE
  *         @arg @ref LL_COMP_WINDOW_INPUT_PLUS_ODD
  *         @arg @ref LL_COMP_WINDOW_INPUT_PLUS_EVEN
  */
__STATIC_INLINE uint32_t LL_COMP_GetCommonWindowMode(const COMP_Common_TypeDef *p_comp_common)
{
  /* Note: On this STM32 series, window mode can be set from any instance      */
  /*       of the pair of comparator instances.                               */

  const uint32_t window_mode_comp_odd = (uint32_t)READ_BIT(p_comp_common->CSR_ODD, COMP_CSR_WINMODE);
  const uint32_t window_mode_comp_even = (uint32_t)READ_BIT(p_comp_common->CSR_EVEN, COMP_CSR_WINMODE);

  return (uint32_t)(window_mode_comp_odd
                    | window_mode_comp_even
                    | (window_mode_comp_even >> COMP_CSR_WINMODE_Pos)
                   );
}

/**
  * @brief  Set window output of a pair of comparators instances
  *         (2 consecutive COMP instances COMP<x> and COMP<x+1>).
  * @rmtoll
  *  CSR      WINOUT         LL_COMP_SetCommonWindowOutput
  * @param  p_comp_common Comparator common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref LL_COMP_COMMON_INSTANCE() ).
  * @param  window_output This parameter can be one of the following values:
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_INDEPT
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_XOR_ODD
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_XOR_EVEN
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_XOR_BOTH
  *         Note: Parameters values with suffix odd or even can also be selected from comparator instance
  *               using helper LL_COMP_WINDOW_INST_TO_OUTPUT.
  */
__STATIC_INLINE void LL_COMP_SetCommonWindowOutput(COMP_Common_TypeDef *p_comp_common, uint32_t window_output)
{
  __IO uint32_t *preg = LL_COMP_PTR_REG_OFFSET(p_comp_common->CSR_ODD,
                                               (window_output & LL_COMP_WINDOW_COMP_REGOFFSET_MASK));

  /* Clear the potential previous setting of window output on the relevant comparator instance */
  /* (clear bit of window output unless specific case of setting of comparator both output selected) */
  __IO uint32_t *preg_clear = LL_COMP_PTR_REG_OFFSET(p_comp_common->CSR_ODD,
                                                     (~(window_output & LL_COMP_WINDOW_COMP_REGOFFSET_MASK) & 0x1UL)
                                                    );
  MODIFY_REG(*preg_clear,
             COMP_CSR_WINOUT,
             ((window_output & LL_COMP_WINDOW_OUT_XOR_BOTH_MASK)
              >> LL_COMP_WINDOW_OUT_XOR_BOTH_POS_VS_WINDOW)
            );

  /* Set window output */
  MODIFY_REG(*preg,
             COMP_CSR_WINOUT,
             (window_output & LL_COMP_WINDOW_OUT_SETTING_MASK)
            );
}

/**
  * @brief  Get window output of a pair of comparators instances
  *         (2 consecutive COMP instances COMP<x> and COMP<x+1>).
  * @rmtoll
  *  CSR      WINMODE        LL_COMP_GetCommonWindowOutput
  * @param  p_comp_common Comparator common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref LL_COMP_COMMON_INSTANCE() ).
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_INDEPT
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_XOR_ODD
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_XOR_EVEN
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_XOR_BOTH
  */
__STATIC_INLINE uint32_t LL_COMP_GetCommonWindowOutput(const COMP_Common_TypeDef *p_comp_common)
{
  const uint32_t window_output_comp_odd = (uint32_t)READ_BIT(p_comp_common->CSR_ODD, COMP_CSR_WINOUT);
  const uint32_t window_output_comp_even = (uint32_t)READ_BIT(p_comp_common->CSR_EVEN, COMP_CSR_WINOUT);

  /* Construct value corresponding to LL_COMP_WINDOWOUTPUT_xxx */
  return (uint32_t)(window_output_comp_odd
                    | window_output_comp_even
                    | ((window_output_comp_even >> COMP_CSR_WINOUT_Pos) * LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK)
                    | (window_output_comp_odd + window_output_comp_even));
}
/**
  * @}
  */

#endif /* COMP_WINDOW_MODE_SUPPORT */

/** @defgroup COMP_LL_EF_Configuration_comparator_modes Configuration of comparator modes
  * @{
  */

/**
  * @brief  Set comparator instance operating mode to adjust power and speed.
  * @rmtoll
  *  CSR      PWRMODE        LL_COMP_SetPowerMode
  * @param  p_comp Comparator instance.
  * @param  power_mode This parameter can be one of the following values:
  *         @arg @ref LL_COMP_POWERMODE_HIGHSPEED
  *         @arg @ref LL_COMP_POWERMODE_MEDIUMSPEED
  *         @arg @ref LL_COMP_POWERMODE_ULTRALOWPOWER
  */
__STATIC_INLINE void LL_COMP_SetPowerMode(COMP_TypeDef *p_comp, uint32_t power_mode)
{
  MODIFY_REG(p_comp->CSR, COMP_CSR_PWRMODE, power_mode);
}

/**
  * @brief  Get comparator instance operating mode to adjust power and speed.
  * @rmtoll
  *  CSR      PWRMODE        LL_COMP_GetPowerMode
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_POWERMODE_HIGHSPEED
  *         @arg @ref LL_COMP_POWERMODE_MEDIUMSPEED
  *         @arg @ref LL_COMP_POWERMODE_ULTRALOWPOWER
  */
__STATIC_INLINE uint32_t LL_COMP_GetPowerMode(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(READ_BIT(p_comp->CSR, COMP_CSR_PWRMODE));
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_Configuration_comparator_inputs Configuration of comparator inputs
  * @{
  */

/**
  * @brief  Set comparator inputs minus (inverting) and plus (non-inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @note   Voltage scaler is used when selecting comparator input based on VrefInt (VrefInt or subdivision of VrefInt).
  *         In this case, specific delay must be fulfilled for voltage stabilization when enabling comparator,
  *         refer to LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US.
  * @note   On this STM32 series, a voltage scaler is used
  *         when COMP input is based on VrefInt (VrefInt or subdivision
  *         of VrefInt):
  *         Voltage scaler requires a delay for voltage stabilization.
  *         Refer to device datasheet, parameter "tSTART_SCALER".
  * @rmtoll
  *  CSR      INPSEL         LL_COMP_ConfigInputs \n
  *  CSR      INMSEL         LL_COMP_ConfigInputs
  * @param  p_comp Comparator instance
  * @param  input_minus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH2
  * @param  input_plus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO3
  * @if COMP_CSR_INPSEL_2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO4
  *         @arg @ref LL_COMP_INPUT_PLUS_IO5
  *         @arg @ref LL_COMP_INPUT_PLUS_IO6
  *     On STM32U5, parameter available only on devices: U535xx and U545xx
  * @endif
  */
__STATIC_INLINE void LL_COMP_ConfigInputs(COMP_TypeDef *p_comp, uint32_t input_minus, uint32_t input_plus)
{
  MODIFY_REG(p_comp->CSR,
             COMP_CSR_INMSEL | COMP_CSR_INPSEL,
             input_minus | input_plus);
}

/**
  * @brief  Set comparator input plus.
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll
  *  CSR      INPSEL         LL_COMP_SetInputPlus
  * @param  p_comp Comparator instance
  * @param  input_plus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO3
  * @if COMP_CSR_INPSEL_2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO4
  *         @arg @ref LL_COMP_INPUT_PLUS_IO5
  *         @arg @ref LL_COMP_INPUT_PLUS_IO6
  *     On STM32U5, parameter available only on devices: U535xx and U545xx
  * @endif
  */
__STATIC_INLINE void LL_COMP_SetInputPlus(COMP_TypeDef *p_comp, uint32_t input_plus)
{
  MODIFY_REG(p_comp->CSR, COMP_CSR_INPSEL, input_plus);
}

/**
  * @brief  Get comparator input plus.
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll
  *  CSR      INPSEL         LL_COMP_GetInputPlus
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO3
  * @if COMP_CSR_INPSEL_2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO4
  *         @arg @ref LL_COMP_INPUT_PLUS_IO5
  *         @arg @ref LL_COMP_INPUT_PLUS_IO6
  *     On STM32U5, parameter available only on devices: U535xx and U545xx
  * @endif
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputPlus(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(READ_BIT(p_comp->CSR, COMP_CSR_INPSEL));
}

/**
  * @brief  Set comparator input minus.
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @note   Voltage scaler is used when selecting comparator input based on VrefInt (VrefInt or subdivision of VrefInt).
  *         In this case, specific delay must be fulfilled for voltage stabilization when enabling comparator,
  *         refer to LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US.
  * @rmtoll
  *  CSR      INMSEL         LL_COMP_SetInputMinus
  * @param  p_comp Comparator instance
  * @param  input_minus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH2
  */
__STATIC_INLINE void LL_COMP_SetInputMinus(COMP_TypeDef *p_comp, uint32_t input_minus)
{
  MODIFY_REG(p_comp->CSR, COMP_CSR_INMSEL, input_minus);
}

/**
  * @brief  Get comparator input minus.
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll
  *  CSR      INMSEL         LL_COMP_GetInputMinus
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH2
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputMinus(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(READ_BIT(p_comp->CSR, COMP_CSR_INMSEL));
}

/**
  * @brief  Get comparator input voltage scaler bridge configuration.
  * @note   Voltage scaler is used when selecting comparator input based on VrefInt (VrefInt or subdivision of VrefInt).
  *         In this case, specific delay must be fulfilled for voltage stabilization when enabling comparator,
  *         refer to LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US.
  * @rmtoll
  *  CSR      INMSEL         LL_COMP_IsInputScalerEnabled
  * @param  p_comp Comparator instance
  * @retval State of scaler bridge configuration (value "1" for enabled, value "0" for disabled).
  */
__STATIC_INLINE uint32_t LL_COMP_IsInputScalerEnabled(const COMP_TypeDef *p_comp)
{
  return ((READ_BIT(p_comp->CSR, COMP_CSR_INMSEL_2) == 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Set comparator input hysteresis.
  * @note   Hysteresys applied on comparator input minus.
  * @rmtoll
  *  CSR      HYST           LL_COMP_SetInputHysteresis
  * @param  p_comp Comparator instance
  * @param  input_hysteresis This parameter can be one of the following values:
  *         @arg @ref LL_COMP_HYSTERESIS_NONE
  *         @arg @ref LL_COMP_HYSTERESIS_LOW
  *         @arg @ref LL_COMP_HYSTERESIS_MEDIUM
  *         @arg @ref LL_COMP_HYSTERESIS_HIGH
  */
__STATIC_INLINE void LL_COMP_SetInputHysteresis(COMP_TypeDef *p_comp, uint32_t input_hysteresis)
{
  MODIFY_REG(p_comp->CSR, COMP_CSR_HYST, input_hysteresis);
}

/**
  * @brief  Get comparator instance hysteresis mode of the minus (inverting) input.
  * @rmtoll
  *  CSR      HYST           LL_COMP_GetInputHysteresis
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_HYSTERESIS_NONE
  *         @arg @ref LL_COMP_HYSTERESIS_LOW
  *         @arg @ref LL_COMP_HYSTERESIS_MEDIUM
  *         @arg @ref LL_COMP_HYSTERESIS_HIGH
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputHysteresis(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(READ_BIT(p_comp->CSR, COMP_CSR_HYST));
}

/** @defgroup COMP_LL_EF_Configuration_comparator_output Configuration of comparator output
  * @{
  */

/**
  * @brief  Set comparator instance output polarity.
  * @rmtoll
  *  CSR      POLARITY       LL_COMP_SetOutputPolarity
  * @param  p_comp Comparator instance
  * @param  output_polarity This parameter can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUTPOL_NONINVERTED
  *         @arg @ref LL_COMP_OUTPUTPOL_INVERTED
  */
__STATIC_INLINE void LL_COMP_SetOutputPolarity(COMP_TypeDef *p_comp, uint32_t output_polarity)
{
  MODIFY_REG(p_comp->CSR, COMP_CSR_POLARITY, output_polarity);
}

/**
  * @brief  Get comparator instance output polarity.
  * @rmtoll
  *  CSR      POLARITY       LL_COMP_GetOutputPolarity
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUTPOL_NONINVERTED
  *         @arg @ref LL_COMP_OUTPUTPOL_INVERTED
  */
__STATIC_INLINE uint32_t LL_COMP_GetOutputPolarity(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(READ_BIT(p_comp->CSR, COMP_CSR_POLARITY));
}

/**
  * @brief  Set comparator instance blanking source.
  * @note   Availability of parameters of blanking source from peripherals
  *         depends on their availability on the selected device.
  * @note   Blanking source can be specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll
  *  CSR      BLANKSEL       LL_COMP_SetOutputBlankingSource
  * @param  p_comp Comparator instance
  * @param  blanking_source This parameter can be one of the following values:
  *         @arg @ref LL_COMP_BLANKINGSRC_NONE
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC4
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM15_OC1
  */
__STATIC_INLINE void LL_COMP_SetOutputBlankingSource(COMP_TypeDef *p_comp, uint32_t blanking_source)
{
  MODIFY_REG(p_comp->CSR, COMP_CSR_BLANKSEL, blanking_source);
}

/**
  * @brief  Get comparator instance blanking source.
  * @note   Availability of parameters of blanking source from peripherals
  *         depends on their availability on the selected device.
  * @note   Blanking source can be specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll
  *  CSR      BLANKSEL       LL_COMP_GetOutputBlankingSource
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_BLANKINGSRC_NONE
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC4
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM15_OC1
  */
__STATIC_INLINE uint32_t LL_COMP_GetOutputBlankingSource(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(READ_BIT(p_comp->CSR, COMP_CSR_BLANKSEL));
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_Operation Operation on comparator instance
  * @{
  */

/**
  * @brief  Enable comparator instance.
  * @note   After enable, comparator requires a delay to reach reach propagation delay specification,
  *         refer to LL_COMP_DELAY_STARTUP_US.
  * @note   Voltage scaler is used when selecting comparator input based on VrefInt (VrefInt or subdivision of VrefInt).
  *         In this case, specific delay must be fulfilled for voltage stabilization when enabling comparator,
  *         refer to LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US.
  *         To get scaler bridge configuration, refer to @ref LL_COMP_IsInputScalerEnabled().
  * @rmtoll
  *  CSR      EN             LL_COMP_Enable
  * @param  p_comp Comparator instance
  */
__STATIC_INLINE void LL_COMP_Enable(COMP_TypeDef *p_comp)
{
  SET_BIT(p_comp->CSR, COMP_CSR_EN);
}

/**
  * @brief  Disable comparator instance.
  * @rmtoll
  *  CSR      EN             LL_COMP_Disable
  * @param  p_comp Comparator instance
  */
__STATIC_INLINE void LL_COMP_Disable(COMP_TypeDef *p_comp)
{
  CLEAR_BIT(p_comp->CSR, COMP_CSR_EN);
}

/**
  * @brief  Get comparator enable state.
  * @rmtoll
  *  CSR      EN             LL_COMP_IsEnabled
  * @param  p_comp Comparator instance
  * @retval Value "0" for comparator disabled, value "1" for comparator enabled.
  */
__STATIC_INLINE uint32_t LL_COMP_IsEnabled(const COMP_TypeDef *p_comp)
{
  return ((READ_BIT(p_comp->CSR, COMP_CSR_EN) == (COMP_CSR_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Lock comparator instance.
  * @note   Once locked, comparator configuration can be accessed in read-only.
  * @note   The only way to unlock the comparator is a device system reset.
  * @rmtoll
  *  CSR      LOCK           LL_COMP_Lock
  * @param  p_comp Comparator instance
  */
__STATIC_INLINE void LL_COMP_Lock(COMP_TypeDef *p_comp)
{
  SET_BIT(p_comp->CSR, COMP_CSR_LOCK);
}

/**
  * @brief  Get comparator lock state.
  * @note   Once locked, comparator configuration can be accessed in read-only.
  * @note   The only way to unlock the comparator is a device system reset.
  * @rmtoll
  *  CSR      LOCK           LL_COMP_IsLocked
  * @param  p_comp Comparator instance
  * @retval Value "0" for comparator unlocked, value "1" for comparator locked.
  */
__STATIC_INLINE uint32_t LL_COMP_IsLocked(const COMP_TypeDef *p_comp)
{
  return ((READ_BIT(p_comp->CSR, COMP_CSR_LOCK) == (COMP_CSR_LOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Read comparator instance output level.
  * @note   The comparator output level depends on the selected polarity
  *         (Refer to function @ref LL_COMP_SetOutputPolarity()).
  *         If the comparator polarity is not inverted:
  *          - Comparator output is low when the input plus
  *            is at a lower voltage than the input minus
  *          - Comparator output is high when the input plus
  *            is at a higher voltage than the input minus
  *         If the comparator polarity is inverted:
  *          - Comparator output is high when the input plus
  *            is at a lower voltage than the input minus
  *          - Comparator output is low when the input plus
  *            is at a higher voltage than the input minus
  * @rmtoll
  *  CSR      VALUE          LL_COMP_ReadOutputLevel
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUT_LEVEL_LOW
  *         @arg @ref LL_COMP_OUTPUT_LEVEL_HIGH
  */
__STATIC_INLINE uint32_t LL_COMP_ReadOutputLevel(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(READ_BIT(p_comp->CSR, COMP_CSR_VALUE) >> COMP_CSR_VALUE_Pos);
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

#endif /* COMP1 || COMP2 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_LL_COMP_H */
