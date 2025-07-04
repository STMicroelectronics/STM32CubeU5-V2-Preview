/**
  ******************************************************************************
  * @file    stm32u5xx_hal_adc.h
  * @brief   Header file of ADC HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5XX_HAL_ADC_H
#define STM32U5XX_HAL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_adc.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup ADC ADC
  * @{
  */

/* Private constants ---------------------------------------------------------*/
/** @addtogroup ADC_Private_Constants
  *  @{
  */
#define HAL_ADC_CALIB_FACTORS_BUF_SIZE  9U   /*!< ADC calibration factors buffer size */

#define HAL_ADC_GROUPS_COUNT            2U   /*!< HAL ADC handle internal tables size to manage ADC groups
                                                  (on this STM32 series, ADC groups available : regular, injected) */

#define HAL_ADC_OPT_DMA_SHIFT           16U  /*!< Optional interruptions literals HAL_ADC_OPT_DMA_x bitfield shift
                                                  for compliance with literals HAL_ADC_OPT_IT_x. */
/**
  * @}
  */

/* Exported constants ---------------------------------------------------------*/
/** @defgroup ADC_Exported_Constants ADC Exported Constants
  * @{
  */

#if defined(USE_HAL_ADC_GET_LAST_ERRORS) && (USE_HAL_ADC_GET_LAST_ERRORS == 1)
/** @defgroup  ADC_error_codes Error codes defined has bitfields
  * @{
  */
#define HAL_ADC_ERROR_NONE              (0UL)                 /*!< No error */
#define HAL_ADC_ERROR_INTERNAL          (1UL << 0U)           /*!< ADC peripheral hardware error (issue of clocking,
                                                                   erroneous state, lock up, ...) */
/* ADC group regular specific errors */
#define HAL_ADC_REG_ERROR_OVR           (1UL << 1U)           /*!< ADC group regular overrun error */
#define HAL_ADC_REG_ERROR_DMA           (1UL << 2U)           /*!< ADC group regular DMA transfer error */

/**
  * @}
  */
#endif /* USE_HAL_ADC_GET_LAST_ERRORS */

/** @defgroup ADC_optional_interruptions Optional interruptions
  * @note     To be used as parameters of functions HAL_ADC_..._StartConv_IT_Opt(),
  *           HAL_ADC_..._StartConv_DMA_Opt()
  * @{
  */
#define HAL_ADC_OPT_IT_NONE             (0U)                    /*!< ADC optional interruptions disabled  */
#define HAL_ADC_OPT_IT_REG_EOSMP        (LL_ADC_IT_EOSMP)       /*!< ADC optional interruption group regular end of
                                        sampling phase */
#define HAL_ADC_OPT_IT_REG_EOC          (LL_ADC_IT_EOC)         /*!< ADC optional interruption group regular end of
                                        unitary conversion */
#define HAL_ADC_OPT_IT_REG_EOS          (LL_ADC_IT_EOS)         /*!< ADC optional interruption group regular end of
                                        sequence conversions */
#define HAL_ADC_OPT_IT_REG_OVR          (LL_ADC_IT_OVR)         /*!< ADC optional interruption group regular
                                        overrun */
#define HAL_ADC_OPT_IT_INJ_EOC          (LL_ADC_IT_JEOC)        /*!< ADC optional interruption group injected end of
                                        unitary conversion */
#define HAL_ADC_OPT_IT_INJ_EOS          (LL_ADC_IT_JEOS)        /*!< ADC optional interruption group injected end of
                                        sequence conversions */
#define HAL_ADC_OPT_IT_AWD_1            (LL_ADC_IT_AWD1)        /*!< ADC optional interruption analog watchdog 1
                                        out of window event */
#define HAL_ADC_OPT_IT_AWD_2            (LL_ADC_IT_AWD2)        /*!< ADC optional interruption analog watchdog 2
                                        out of window event */
#define HAL_ADC_OPT_IT_AWD_3            (LL_ADC_IT_AWD3)        /*!< ADC optional interruption analog watchdog 3
                                        out of window event */

#if defined(USE_HAL_ADC_DMA) && (USE_HAL_ADC_DMA == 1)
#define HAL_ADC_OPT_DMA_IT_NONE         (HAL_DMA_OPT_IT_NONE)   /*!< ADC data transfer with DMA optional interruptions
                                        disabled.
                                        DMA default interruptions: transfer complete, transfer error.
                                        DMA optional interruptions: refer to literals below. */
#define HAL_ADC_OPT_DMA_IT_HT           (HAL_DMA_OPT_IT_HT << HAL_ADC_OPT_DMA_SHIFT) /*!< ADC data transfer with
                                        DMA optional interruption buffer half transfer */
#define HAL_ADC_OPT_DMA_IT_DEFAULT      (HAL_DMA_OPT_IT_DEFAULT << HAL_ADC_OPT_DMA_SHIFT) /*!< ADC data transfer with
                                        DMA optional interruptions all enabled */
#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#define HAL_ADC_OPT_DMA_IT_SILENT       (HAL_DMA_OPT_IT_SILENT) /*!< ADC data transfer with all interruptions
                                        disabled (ADC and DMA interruptions) */
#endif /* USE_HAL_DMA_LINKEDLIST */
#endif /* USE_HAL_ADC_DMA */
/**
  * @}
  */

/** @defgroup ADC_helper_macro  Definitions of constants used by helper macro
  * @{
  */
#define HAL_ADC_TEMPERATURE_CALC_ERROR  LL_ADC_TEMPERATURE_CALC_ERROR /*!< Temperature calculation error using helper
                                        macro @ref HAL_ADC_CALC_TEMPERATURE(), due to issue on calibration parameters.
                                        This value is coded on 16 bits (to fit on signed word or double word) and
                                        corresponds to an inconsistent temperature value. */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro -------------------------------------------------------------*/
/** @defgroup ADC_Exported_Macro ADC Exported Macro
  * @{
  */

/**
  * @brief  Helper macro to calculate the voltage (unit: mV)
  *         corresponding to a ADC conversion data (unit: digital value).
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref HAL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @note   Arguments data type converted to signed (int32_t) to handle all possible input values
  *         (conversion data can be negative after post-processing computation: offset feature)
  * @param  vref_analog_voltage Analog reference voltage Vref+ (unit: mV)
  * @param  conv_data  ADC conversion data (unit: digital value)
  * @param  resolution ADC resolution at which ADC conversion has been performed.
  *                    Value among @ref hal_adc_resolution_t
  * @retval ADC conversion data equivalent voltage value (unit: mV)
  */
#define HAL_ADC_CALC_DATA_TO_VOLTAGE(vref_analog_voltage, \
                                     conv_data, \
                                     resolution) \
LL_ADC_CALC_DATA_TO_VOLTAGE((vref_analog_voltage), \
                            (conv_data), \
                            (uint32_t)(resolution))

/**
  * @brief  Helper macro to calculate the ADC conversion data (unit: digital value)
  *         corresponding to a voltage (unit: mV).
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref HAL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @note   Arguments data type converted to signed (int32_t) to handle all possible input values
  *         (conversion data can be negative after post-processing computation: offset feature)
  * @param  vref_analog_voltage Analog reference voltage Vref+ (unit: mV)
  * @param  voltage_mv ADC conversion data voltage value (unit: mV)
  * @param  resolution ADC resolution at which ADC conversion has been performed.
  *                    Value among @ref hal_adc_resolution_t
  * @retval ADC conversion data equivalent value (unit: digital value)
  */
#define HAL_ADC_CALC_VOLTAGE_TO_DATA(vref_analog_voltage, \
                                     voltage_mv, \
                                     resolution) \
LL_ADC_CALC_VOLTAGE_TO_DATA((vref_analog_voltage), \
                            (voltage_mv), \
                            (uint32_t)(resolution))

/**
  * @brief  Helper macro to calculate the voltage (unit: mV)
  *         corresponding to a ADC conversion data (unit: digital value)
  *         in differential ended mode.
  * @note   On STM32U5, this feature is available on ADC instances: ADC1, ADC2.
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref HAL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @param  vref_analog_voltage Analog reference voltage (unit: mV)
  * @param  conv_data  ADC conversion data (unit: digital value).
  * @param  resolution ADC resolution at which ADC conversion has been performed.
  *                    Value among hal_adc_resolution_t
  * @retval ADC conversion data equivalent voltage value (unit: mV)
  */
#define HAL_ADC_CALC_DIFF_DATA_TO_VOLTAGE(vref_analog_voltage, \
                                          conv_data, \
                                          resolution) \
LL_ADC_CALC_DIFF_DATA_TO_VOLTAGE((vref_analog_voltage), \
                                 (conv_data), \
                                 (uint32_t)(resolution))

/**
  * @brief  Helper macro to calculate analog reference voltage (Vref+)
  *         (unit: mV) from ADC conversion data of internal voltage
  *         reference VrefInt.
  * @note   Computation is using VrefInt calibration value
  *         stored in system memory for each device during production.
  * @note   This voltage depends on user board environment: voltage level
  *         connected to pin Vref+.
  *         On devices with small package, the pin Vref+ is not present
  *         and internally bonded to pin Vdda.
  * @param  vrefint_conv_data ADC conversion data
  *         of internal voltage reference VrefInt (unit: digital value).
  * @param  resolution ADC resolution at which ADC conversion has been performed.
  *                    Value among hal_adc_resolution_t
  * @retval Analog reference voltage (unit: mV)
  */
#define HAL_ADC_CALC_VREFANALOG_VOLTAGE(vrefint_conv_data, \
                                        resolution) \
LL_ADC_CALC_VREFANALOG_VOLTAGE((vrefint_conv_data), \
                               (uint32_t)(resolution))

/**
  * @brief  Helper macro to calculate the temperature (unit: degree Celsius)
  *         from ADC conversion data of internal temperature sensor.
  * @note   Computation is using temperature sensor calibration values
  *         stored in system memory for each device during production.
  *         To calculate temperature using temperature sensor
  *                  datasheet typical values (generic values less, therefore
  *                  less accurate than calibrated values),
  *                  use helper macro LL_ADC_CALC_TEMPERATURE_TYP_PARAMS().
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref HAL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @param  vref_analog_voltage  Analog reference voltage Vref+ (unit: mV)
  * @param  tempsensor_conv_data ADC conversion data of internal
  *                              temperature sensor (unit: digital value).
  * @param  resolution ADC resolution at which ADC conversion has been performed.
  *                    Value among hal_adc_resolution_t
  * @retval Temperature (unit: degree Celsius) or error code (value HAL_ADC_TEMPERATURE_CALC_ERROR)
  */
#define HAL_ADC_CALC_TEMPERATURE(vref_analog_voltage, \
                                 tempsensor_conv_data, \
                                 resolution) \
LL_ADC_CALC_TEMPERATURE((vref_analog_voltage), \
                        (tempsensor_conv_data), \
                        (uint32_t)(resolution))

/**
  * @brief  Helper macro to calculate the battery voltage (unit: degree Celsius)
  *         from ADC conversion data of vbat channel.
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref HAL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @param  vref_analog_voltage  Analog reference voltage Vref+ (unit: mV)
  * @param  vbat_conv_data ADC conversion data of vbat channel
  *                        (unit: digital value).
  * @param  resolution ADC resolution at which ADC conversion has been performed.
  *                    Value among hal_adc_resolution_t
  * @retval Temperature (unit: degree Celsius)
  */
#define HAL_ADC_CALC_VBAT(vref_analog_voltage, \
                          vbat_conv_data, \
                          resolution) \
LL_ADC_CALC_VBAT((vref_analog_voltage), \
                 (vbat_conv_data), \
                 (uint32_t)(resolution))

/**
  * @brief  Helper macro to get ADC channel number in decimal format
  *         from literals HAL_ADC_CHANNEL_x.
  * @note   Example:
  *           HAL_ADC_CHANNEL_TO_DECIMAL_NB(HAL_ADC_CHANNEL_4)
  *           will return decimal number "4".
  * @note   Channels compliants are channels connected to GPIO (not internal channels).
  *         For more details, refer to LL_ADC_CHANNEL_TO_DECIMAL_NB().
  * @param  channel Value among hal_adc_channel_t, limited to channels HAL_ADC_CHANNEL_x.
  * @retval Value between Min_Data=0 and Max_Data=23
  */
#define HAL_ADC_CHANNEL_TO_DECIMAL_NB(channel) \
  LL_ADC_CHANNEL_TO_DECIMAL_NB((uint32_t)(channel))

/**
  * @brief  Helper macro to get ADC channel in literal format HAL_ADC_CHANNEL_x
  *         from number in decimal format.
  * @note   Example:
  *           HAL_ADC_DECIMAL_NB_TO_CHANNEL(4)
  *           will return a data equivalent to "HAL_ADC_CHANNEL_4".
  * @note   Channels compliants are channels connected to GPIO (not internal channels).
  *         For more details, refer to LL_ADC_DECIMAL_NB_TO_CHANNEL().
  * @param  decimal_nb Value between Min_Data=0 and Max_Data=23
  * @retval Value among hal_adc_channel_t, limited to channels HAL_ADC_CHANNEL_x.
  */
#define HAL_ADC_DECIMAL_NB_TO_CHANNEL(decimal_nb) \
  LL_ADC_DECIMAL_NB_TO_CHANNEL((uint32_t)(decimal_nb))

/**
  * @brief  Helper macro to define the ADC conversion data full-scale digital
  *         maximum value corresponding to the selected ADC resolution.
  * @note   ADC conversion data full-scale corresponds to voltage range
  *         determined by analog voltage references Vref+ and Vref- (refer to reference manual).
  * @note   Value returned corresponds to range maximum value without post-processing computation.
  *         With post-processing (offset, gain), conversion data maximum value can exceed this range
  *         (as well as minimum value in negative range).
  * @param  resolution Value among hal_adc_resolution_t
  * @retval ADC conversion data full-scale digital value
  */
#define HAL_ADC_DIGITAL_SCALE(resolution) \
  LL_ADC_DIGITAL_SCALE((uint32_t)(resolution))

/**
  * @brief  Helper macro to convert the ADC conversion data from
  *         a resolution to another resolution.
  * @param  data ADC conversion data to be converted
  * @param  adc_res_current Value among hal_adc_resolution_t
  * @param  adc_res_target Value among hal_adc_resolution_t
  * @retval ADC conversion data to the requested resolution
  */
#define HAL_ADC_CONVERT_DATA_RESOLUTION(data, \
                                        adc_res_current, \
                                        adc_res_target) \
LL_ADC_CONVERT_DATA_RESOLUTION((data), \
                               (uint32_t)(adc_res_current), \
                               (uint32_t)(adc_res_target))

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup  ADC_Exported_Types ADC Exported Types
  * @{
  */

/**
  * @brief HAL ADC instance
  */
typedef enum
{
  HAL_ADC1  = (uint32_t)ADC1,
#if defined(ADC2)
  HAL_ADC2  = (uint32_t)ADC2,
#endif /* ADC2 */
  HAL_ADC4  = (uint32_t)ADC4,
} hal_adc_t;

/**
  * @brief ADC global state
  */
typedef enum
{
  HAL_ADC_STATE_RESET                   = 0U,              /*!< ADC not yet initialized */
  HAL_ADC_STATE_INIT                    = (1U << 31U),     /*!< ADC initialized but not yet configured */
  HAL_ADC_STATE_CONFIGURING             = (1U << 30U),     /*!< ADC configuration on going (step optional
                                        depending on series or ADC instances) */
  HAL_ADC_STATE_IDLE                    = (1U << 29U),     /*!< ADC configured and ready to be activated */
  HAL_ADC_STATE_ACTIVE                  = (1U << 28U),     /*!< ADC activated, ready to operate
                                        (ADC conversions depending on ADC groups state) */
  HAL_ADC_STATE_CALIB                   = (1U << 27U),     /*!< ADC calibration on going */
} hal_adc_state_t;

/**
  * @brief ADC group (regular, injected) state
  */
typedef enum
{
  HAL_ADC_GROUP_STATE_RESET             = (1U << 31U), /*!< ADC group not yet initialized */
  HAL_ADC_GROUP_STATE_IDLE              = (1U << 30U), /*!< ADC group initialized and ready to operate */
  HAL_ADC_GROUP_STATE_ACTIVE            = (1U << 29U), /*!< ADC group operating (ADC conversion on going
                                        or can start upon trigger request) */
#if defined(USE_HAL_ADC_DMA) && (USE_HAL_ADC_DMA == 1)
  HAL_ADC_GROUP_STATE_ACTIVE_SILENT     = (1U << 28U), /*!< ADC group operating (ADC conversion on going
                                        or can start upon trigger request) without any
                                        interruption */
#endif /* USE_HAL_ADC_DMA */
} hal_adc_group_state_t;

/**
  * @brief HAL ADC handle link to common instance state
  */
typedef enum
{
  HAL_ADC_COMMON_STATE_RESET            = 0,           /*!< HAL ADC handle link to common instance not yet initialized*/
  HAL_ADC_COMMON_STATE_INDEPT           = (1U << 31U), /*!< HAL ADC handle independent (not linked to common instance)*/
  HAL_ADC_COMMON_STATE_LINKED           = (1U << 30U), /*!< HAL ADC handle linked to other handles of common instance */
  HAL_ADC_COMMON_STATE_MM               = (1U << 29U), /*!< HAL ADC handle linked to other handles of common instance
                                        and configured in multimode */
} hal_adc_common_state_t;

/**
  * @brief HAL ADC group conversions per conversion start configuration
  */
typedef enum
{
  HAL_ADC_GROUP_CONV_UNIT               = 0U,   /*!< HAL ADC group configured to have a unitary (only one) conversion
                                        per conversion start */
  HAL_ADC_GROUP_CONV_MULTIPLE           = 1U,   /*!< HAL ADC group configured to have multiple conversions
                                        from one conversion start (for example: continuous mode,
                                        trigger from timer, ...) */
} hal_adc_group_conv_per_start_t;

/**
  * @brief HAL ADC kernel clock source and prescaler
  */
typedef enum
{
  HAL_ADC_CLOCK_ASYNC_DIV1              = LL_ADC_CLOCK_ASYNC_DIV1,   /*!< ADC kernel clock source asynchronous
                                        with clock without prescaler */
  HAL_ADC_CLOCK_ASYNC_DIV2              = LL_ADC_CLOCK_ASYNC_DIV2,   /*!< ADC kernel clock source asynchronous
                                        with clock prescaler div 2 */
  HAL_ADC_CLOCK_ASYNC_DIV4              = LL_ADC_CLOCK_ASYNC_DIV4,   /*!< ADC kernel clock source asynchronous
                                        with clock prescaler div 4 */
  HAL_ADC_CLOCK_ASYNC_DIV6              = LL_ADC_CLOCK_ASYNC_DIV6,   /*!< ADC kernel clock source asynchronous
                                        with clock prescaler div 6 */
  HAL_ADC_CLOCK_ASYNC_DIV8              = LL_ADC_CLOCK_ASYNC_DIV8,   /*!< ADC kernel clock source asynchronous
                                        with clock prescaler div 8 */
  HAL_ADC_CLOCK_ASYNC_DIV10             = LL_ADC_CLOCK_ASYNC_DIV10,  /*!< ADC kernel clock source asynchronous
                                        with clock prescaler div 10 */
  HAL_ADC_CLOCK_ASYNC_DIV12             = LL_ADC_CLOCK_ASYNC_DIV12,  /*!< ADC kernel clock source asynchronous
                                        with clock prescaler div 12 */
  HAL_ADC_CLOCK_ASYNC_DIV16             = LL_ADC_CLOCK_ASYNC_DIV16,  /*!< ADC kernel clock source asynchronous
                                        with clock prescaler div 16 */
  HAL_ADC_CLOCK_ASYNC_DIV32             = LL_ADC_CLOCK_ASYNC_DIV32,  /*!< ADC kernel clock source asynchronous
                                        with clock prescaler div 32 */
  HAL_ADC_CLOCK_ASYNC_DIV64             = LL_ADC_CLOCK_ASYNC_DIV64,  /*!< ADC kernel clock source asynchronous
                                        with clock prescaler div 64 */
  HAL_ADC_CLOCK_ASYNC_DIV128            = LL_ADC_CLOCK_ASYNC_DIV128, /*!< ADC kernel clock source asynchronous
                                        with clock prescaler div 128 */
  HAL_ADC_CLOCK_ASYNC_DIV256            = LL_ADC_CLOCK_ASYNC_DIV256  /*!< ADC kernel clock source asynchronous
                                        with clock prescaler div 256 */
} hal_adc_clock_t;

/**
  * @brief HAL ADC resolution
  */
typedef enum
{
  HAL_ADC_RESOLUTION_6_BIT              = LL_ADC_RESOLUTION_6B,   /*!< ADC resolution 6 bit (ADC4 only)
                                        Specific to ADC instance: ADC4. */
  HAL_ADC_RESOLUTION_8_BIT              = LL_ADC_RESOLUTION_8B,   /*!< ADC resolution 8 bit */
  HAL_ADC_RESOLUTION_10_BIT             = LL_ADC_RESOLUTION_10B,  /*!< ADC resolution 10 bit */
  HAL_ADC_RESOLUTION_12_BIT             = LL_ADC_RESOLUTION_12B,  /*!< ADC resolution 12 bit. Default for ADC4. */
  HAL_ADC_RESOLUTION_14_BIT             = LL_ADC_RESOLUTION_14B,  /*!< ADC resolution 14 bit
                                        Specific to ADC instance: ADC1, ADC2. Default for ADC1, ADC2. */
} hal_adc_resolution_t;

/**
  * @brief HAL ADC data shift left
  */
typedef enum
{
  HAL_ADC_LEFT_BIT_SHIFT_NONE           = LL_ADC_LEFT_BIT_SHIFT_NONE, /*!< ADC conversion data not shifted
                                        (alignment right, on data register MSB bit 0) */
  HAL_ADC_LEFT_BIT_SHIFT_1_BIT          = LL_ADC_LEFT_BIT_SHIFT_1,    /*!< ADC conversion data shift left of 1 bits
                                        (data multiplicated by 2). Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_LEFT_BIT_SHIFT_2_BITS         = LL_ADC_LEFT_BIT_SHIFT_2,    /*!< ADC conversion data shift left of 2 bits
                                        (data multiplicated by 4) */
  HAL_ADC_LEFT_BIT_SHIFT_3_BITS         = LL_ADC_LEFT_BIT_SHIFT_3,    /*!< ADC conversion data shift left of 3 bits
                                        (data multiplicated by 8) */
  HAL_ADC_LEFT_BIT_SHIFT_4_BITS         = LL_ADC_LEFT_BIT_SHIFT_4,    /*!< ADC conversion data shift left of 4 bits
                                        (data multiplicated by 16) */
  HAL_ADC_LEFT_BIT_SHIFT_5_BITS         = LL_ADC_LEFT_BIT_SHIFT_5,    /*!< ADC conversion data shift left of 5 bits
                                        (data multiplicated by 32) */
  HAL_ADC_LEFT_BIT_SHIFT_6_BITS         = LL_ADC_LEFT_BIT_SHIFT_6,    /*!< ADC conversion data shift left of 6 bits
                                        (data multiplicated by 64) */
  HAL_ADC_LEFT_BIT_SHIFT_7_BITS         = LL_ADC_LEFT_BIT_SHIFT_7,    /*!< ADC conversion data shift left of 7 bits
                                        (data multiplicated by 128) */
  HAL_ADC_LEFT_BIT_SHIFT_8_BITS         = LL_ADC_LEFT_BIT_SHIFT_8,    /*!< ADC conversion data shift left of 8 bits
                                        (data multiplicated by 256) */
  HAL_ADC_LEFT_BIT_SHIFT_9_BITS         = LL_ADC_LEFT_BIT_SHIFT_9,    /*!< ADC conversion data shift left of 9 bits
                                        (data multiplicated by 512) */
  HAL_ADC_LEFT_BIT_SHIFT_10_BITS        = LL_ADC_LEFT_BIT_SHIFT_10,    /*!< ADC conversion data shift left of 10 bits
                                        (data multiplicated by 1024) */
  HAL_ADC_LEFT_BIT_SHIFT_11_BITS        = LL_ADC_LEFT_BIT_SHIFT_11,    /*!< ADC conversion data shift left of 11 bits
                                        (data multiplicated by 2048) */
  HAL_ADC_LEFT_BIT_SHIFT_12_BITS        = LL_ADC_LEFT_BIT_SHIFT_12,    /*!< ADC conversion data shift left of 12 bits
                                        (data multiplicated by 4096) */
  HAL_ADC_LEFT_BIT_SHIFT_13_BITS        = LL_ADC_LEFT_BIT_SHIFT_13,    /*!< ADC conversion data shift left of 13 bits
                                        (data multiplicated by 8192) */
  HAL_ADC_LEFT_BIT_SHIFT_14_BITS        = LL_ADC_LEFT_BIT_SHIFT_14,    /*!< ADC conversion data shift left of 14 bits
                                        (data multiplicated by 16384) */
  HAL_ADC_LEFT_BIT_SHIFT_15_BITS        = LL_ADC_LEFT_BIT_SHIFT_15,    /*!< ADC conversion data shift left of 15 bits
                                        (data multiplicated by 32768) */
  HAL_ADC_LEFT_BIT_SHIFT_POS_15         = LL_ADC_DATA_ALIGN_LEFT       /*!< ADC conversion data alignment: left aligned
                                        (alignment on data register MSB bit 15). Specific to ADC instance: ADC4. */
} hal_adc_left_bit_shift_t;

/**
  * @brief HAL ADC low power feature auto wait
  */
typedef enum
{
  HAL_ADC_LP_AUTO_WAIT_DISABLE          = LL_ADC_LP_MODE_NONE, /*!< ADC low power mode auto delay disabled. */
  HAL_ADC_LP_AUTO_WAIT_ENABLE           = LL_ADC_LP_AUTOWAIT   /*!< ADC low power mode auto delay enabled: dynamic
                                        low power mode, ADC conversions are performed only when necessary
                                        (when previous ADC conversion data is read).
                                        Refer to detailed description of function LL_ADC_SetLPModeAutoWait(). */
} hal_adc_lp_auto_wait_state_t;

/**
  * @brief HAL ADC low power feature auto power-off
  */
typedef enum
{
  HAL_ADC_LP_AUTO_POWER_OFF_DISABLE     = LL_ADC_LP_AUTOPOWEROFF_DISABLE, /*!< ADC low power mode auto power-off
                                        disabled */
  HAL_ADC_LP_AUTO_POWER_OFF_ENABLE      = LL_ADC_LP_AUTOPOWEROFF_ENABLE   /*!< ADC low power mode auto power-off
                                        enabled: the ADC automatically powers-off after a ADC conversion
                                        and automatically wakes up when a new ADC conversion is triggered
                                        (with startup time between trigger and start of sampling). Refer
                                        to detailed description of function LL_ADC_SetLPModeAutoPowerOff().
                                        It can be combined with mode low power mode auto wait.
                                        Specific to ADC instance: ADC4. */
} hal_adc_lp_auto_power_off_state_t;

/**
  * @brief HAL ADC low power autonomous deep power down mode
  */
typedef enum
{
  HAL_ADC_LP_AUTONOMOUS_DPD_DISABLE     = LL_ADC_LP_AUTONOMOUS_DPD_DISABLE, /*!< ADC deep power down in autonomous mode
                                        disabled. Specific to ADC instance: ADC4. */
  HAL_ADC_LP_AUTONOMOUS_DPD_ENABLE      = LL_ADC_LP_AUTONOMOUS_DPD_ENABLE   /*!< ADC deep power down in autonomous mode
                                        enabled. Specific to ADC instance: ADC4. */
} hal_adc_lp_autonomous_dpd_state_t;

/**
  * @brief HAL ADC trigger frequency mode
  */
typedef enum
{
  HAL_ADC_TRIGGER_FREQ_HIGH             = LL_ADC_TRIGGER_FREQ_HIGH, /*!< ADC trigger frequency mode to high frequency.
                                        Note: ADC trigger frequency mode must be set to low frequency
                                              when a duration is exceeded before ADC conversion start trigger event
                                              (between ADC enable and ADC conversion start trigger event
                                              or between two ADC conversion start trigger event).
                                              Duration value: Refer to device datasheet, parameter "tIdle".
                                              Specific to ADC instance: ADC1, ADC2 (ADC4 fixed to low frequency). */
  HAL_ADC_TRIGGER_FREQ_LOW              = LL_ADC_TRIGGER_FREQ_LOW   /*!< ADC trigger frequency mode to low frequency.
                                        Note: ADC trigger frequency mode must be set to low frequency
                                              when a duration is exceeded before ADC conversion start trigger event
                                              (between ADC enable and ADC conversion start trigger event
                                              or between two ADC conversion start trigger event).
                                              Duration value: Refer to device datasheet, parameter "tIdle".
                                              Specific to ADC instance: ADC1, ADC2 (ADC4 fixed to low frequency). */
} hal_adc_trigger_freq_mode_t;

/**
  * @brief HAL ADC sampling mode
  */
typedef enum
{
  HAL_ADC_SAMPLING_MODE_NORMAL          = LL_ADC_SAMPLING_MODE_NORMAL, /*!< ADC conversions sampling phase duration
                                        is defined using hal_adc_sampling_time_t. */
  HAL_ADC_SAMPLING_MODE_BULB            = LL_ADC_SAMPLING_MODE_BULB,   /*!< ADC conversions sampling phase starts
                                        immediately after end of conversion, stops upon trigger event.
                                        Note: First conversion is using minimal sampling time
                                              (refer to hal_adc_sampling_time_t).
                                        Note: Usable only if conversions from ADC group regular (not ADC group injected)
                                              and not in continuous mode. */
  HAL_ADC_SAMPLING_MODE_TRIGGER_CTRL    = LL_ADC_SAMPLING_MODE_TRIGGER_CTRL /*!< ADC conversions sampling phase
                                        by trigger events: trigger rising edge starts sampling,
                                        trigger falling edge stops sampling and start conversion.
                                        Note: Usable only if conversions from ADC group regular (not ADC group injected)
                                              and not in continuous mode. */
} hal_adc_sampling_mode_t;

/**
  * @brief HAL ADC sampling time (common to group of channels)
  */
typedef enum
{
  HAL_ADC_SAMPLING_TIME_1CYCLE_5        = LL_ADC4_SAMPLINGTIME_1CYCLE_5,    /*!< Sampling time 1.5 ADC clock cycle
                                        (specific to ADC instance: ADC4) */
  HAL_ADC_SAMPLING_TIME_3CYCLES_5       = LL_ADC4_SAMPLINGTIME_3CYCLES_5,   /*!< Sampling time 3.5 ADC clock cycles
                                        (specific to ADC instance: ADC4) */
  HAL_ADC_SAMPLING_TIME_7CYCLES_5       = LL_ADC4_SAMPLINGTIME_7CYCLES_5,   /*!< Sampling time 7.5 ADC clock cycles
                                        (specific to ADC instance: ADC4) */
  HAL_ADC_SAMPLING_TIME_12CYCLES_5      = LL_ADC4_SAMPLINGTIME_12CYCLES_5,  /*!< Sampling time 12.5 ADC clock cycles
                                        (specific to ADC instance: ADC4) */
  HAL_ADC_SAMPLING_TIME_19CYCLES_5      = LL_ADC4_SAMPLINGTIME_19CYCLES_5,  /*!< Sampling time 19.5 ADC clock cycles
                                        (specific to ADC instance: ADC4) */
  HAL_ADC_SAMPLING_TIME_39CYCLES_5      = LL_ADC4_SAMPLINGTIME_39CYCLES_5,  /*!< Sampling time 39.5 ADC clock cycles
                                        (specific to ADC instance: ADC4) */
  HAL_ADC_SAMPLING_TIME_79CYCLES_5      = LL_ADC4_SAMPLINGTIME_79CYCLES_5,  /*!< Sampling time 79.5 ADC clock cycles
                                        (specific to ADC instance: ADC4) */
  HAL_ADC_SAMPLING_TIME_814CYCLES_5     = LL_ADC4_SAMPLINGTIME_814CYCLES_5, /*!< Sampling time 814.5 ADC clock cycles
                                        (specific to ADC instance: ADC4) */
} hal_adc_sampling_time_com_t;

/**
  * @brief HAL ADC Vref+ protection mode
  */
typedef enum
{
  HAL_ADC_VREF_PROT_DISABLE             = LL_ADC_VREF_PROT_DISABLE,            /*!< ADC Vref+ protection disabled
                                        (specific to ADC instance: ADC4) */
  HAL_ADC_VREF_PROT_FIRST_SAMP_ENABLE   = LL_ADC_VREF_PROT_FIRST_SAMP_ENABLE,  /*!< ADC Vref+ protection enabled:
                                        In case of simultaneous sampling phase of ADC4 and ADC1/2, ADC4 is put
                                        on hold during one ADC4 clock cycle to avoid noise on Vref+.
                                        (specific to ADC instance: ADC4) */
  HAL_ADC_VREF_PROT_SECOND_SAMP_ENABLE  = LL_ADC_VREF_PROT_SECOND_SAMP_ENABLE, /*!< ADC Vref+ protection enabled:
                                        In case of simultaneous sampling phase of ADC4 and ADC1/2, ADC4 is put
                                        on hold during two ADC4 clock cycles to avoid noise on Vref+.
                                        (specific to ADC instance: ADC4) */
} hal_adc_vref_protection_t;

/**
  * @brief HAL ADC groups
  */
typedef enum
{
  HAL_ADC_GROUP_REGULAR                 = LL_ADC_GROUP_REGULAR,          /*!< ADC group regular */
  HAL_ADC_GROUP_INJECTED                = LL_ADC_GROUP_INJECTED,         /*!< ADC group injected */
  HAL_ADC_GROUP_REGULAR_INJECTED        = LL_ADC_GROUP_REGULAR_INJECTED, /*!< ADC both groups regular and injected
                                        (usable only by specific functions: analog watchdog configuration) */
  HAL_ADC_GROUP_NONE                    = LL_ADC_GROUP_NONE,             /*!< ADC group none.
                                        Note: Can be used to remove a channel from sequencer in mode not fully
                                              configurable (specific to ADC instance: ADC4)
                                              or remove a channel from analog watchdog monitoring. */
} hal_adc_group_t;

/**
  * @brief HAL ADC group regular conversion trigger source
  */
typedef enum
{
  /* ADC group regular trigger sources common to all ADC instances */
  HAL_ADC_REG_TRIG_SOFTWARE_START       = LL_ADC_REG_TRIG_SOFTWARE,                 /*!< ADC group regular conversion
                                        trigger from software start */
  HAL_ADC_REG_TRIG_TIM1_TRGO2           = LL_ADC_REG_TRIG_EXT_TIM1_TRGO2,           /*!< ADC group regular conversion
                                        trigger from periph: TIM1 channel 1 event (capture compare). */
  HAL_ADC_REG_TRIG_TIM2_TRGO            = LL_ADC_REG_TRIG_EXT_TIM2_TRGO,            /*!< ADC group regular conversion
                                        trigger from periph: TIM2 TRGO event. */
  HAL_ADC_REG_TRIG_TIM6_TRGO            = LL_ADC_REG_TRIG_EXT_TIM6_TRGO,            /*!< ADC group regular conversion
                                        trigger from periph: TIM6 TRGO event */
  HAL_ADC_REG_TRIG_TIM15_TRGO           = LL_ADC_REG_TRIG_EXT_TIM15_TRGO,           /*!< ADC group regular conversion
                                        trigger from periph: TIM15 TRGO event */
  HAL_ADC_REG_TRIG_LPTIM1_CH1           = LL_ADC_REG_TRIG_EXT_LPTIM1_CH1,           /*!< ADC group regular conversion
                                        trigger from periph: LPTIM1 channel 1 event (capture compare). */
  HAL_ADC_REG_TRIG_EXTI15               = LL_ADC_REG_TRIG_EXT_EXTI_LINE15,          /*!< ADC group regular conversion
                                        trigger from periph: external interrupt line 15 event. */

  /* ADC group regular trigger sources specific to ADC instance: ADC1, ADC2 (if available) */
  HAL_ADC_REG_TRIG_TIM1_TRGO            = LL_ADC_REG_TRIG_EXT_TIM1_TRGO,            /*!< ADC group regular conversion
                                        trigger from periph: TIM1 TRGO event.
                                        Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_REG_TRIG_TIM1_CH1             = LL_ADC_REG_TRIG_EXT_TIM1_CH1,             /*!< ADC group regular conversion
                                        trigger from periph: TIM1 channel 1 event (capture compare).
                                        Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_REG_TRIG_TIM1_CH2             = LL_ADC_REG_TRIG_EXT_TIM1_CH2,             /*!< ADC group regular conversion
                                        trigger from periph: TIM1 channel 2 event (capture compare).
                                        Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_REG_TRIG_TIM1_CH3             = LL_ADC_REG_TRIG_EXT_TIM1_CH3,             /*!< ADC group regular conversion
                                        trigger from periph: TIM1 channel 3 event (capture compare).
                                        Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_REG_TRIG_TIM2_CH2             = LL_ADC_REG_TRIG_EXT_TIM2_CH2,             /*!< ADC group regular conversion
                                        trigger from periph: TIM2 channel 2 event (capture compare).
                                        Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_REG_TRIG_TIM3_TRGO            = LL_ADC_REG_TRIG_EXT_TIM3_TRGO,            /*!< ADC group regular conversion
                                        trigger from periph: TIM3 TRGO event.
                                        Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_REG_TRIG_TIM4_CH4             = LL_ADC_REG_TRIG_EXT_TIM4_CH4,             /*!< ADC group regular conversion
                                        trigger from periph: TIM4 channel 4 event (capture compare).
                                        Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_REG_TRIG_EXTI11               = LL_ADC_REG_TRIG_EXT_EXTI_LINE11,          /*!< ADC group regular conversion
                                        trigger from periph: external interrupt line 11 event.
                                        Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_REG_TRIG_TIM8_TRGO            = LL_ADC_REG_TRIG_EXT_TIM8_TRGO,            /*!< ADC group regular conversion
                                        trigger from periph: TIM8 TRGO event.
                                        Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_REG_TRIG_TIM8_TRGO2           = LL_ADC_REG_TRIG_EXT_TIM8_TRGO2,           /*!< ADC group regular conversion
                                        trigger from periph: TIM8 channel 1 event (capture compare).
                                        Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_REG_TRIG_TIM4_TRGO            = LL_ADC_REG_TRIG_EXT_TIM4_TRGO,            /*!< ADC group regular conversion
                                        trigger from periph: TIM4 TRGO event (capture compare).
                                        Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_REG_TRIG_TIM3_CH4             = LL_ADC_REG_TRIG_EXT_TIM3_CH4,             /*!< ADC group regular conversion
                                        trigger from periph: TIM3 channel 4 event (capture compare).
                                        Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_REG_TRIG_LPTIM2_CH1           = LL_ADC_REG_TRIG_EXT_LPTIM2_CH1,           /*!< ADC group regular conversion
                                        trigger from periph: LPTIM2 channel 1 event (capture compare).
                                        Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_REG_TRIG_LPTIM3_CH1           = LL_ADC_REG_TRIG_EXT_LPTIM3_CH1,           /*!< ADC group regular conversion
                                        trigger from periph: LPTIM3 channel 1 event (capture compare).
                                        Specific to ADC instance: ADC1, ADC2. */
  HAL_ADC_REG_TRIG_LPTIM4_OUT           = LL_ADC_REG_TRIG_EXT_LPTIM4_OUT,           /*!< ADC group regular conversion
                                        trigger from periph: LPTIM4 output event.
                                        Specific to ADC instance: ADC1, ADC2. */

  /* ADC group regular trigger sources specific to ADC instance: ADC4 */
  HAL_ADC_REG_TRIG_TIM1_CH4             = LL_ADC_REG_TRIG_EXT_TIM1_CH4_ADC4,        /*!< ADC group regular conversion
                                        trigger from periph: TIM1 channel 4 event (capture compare).
                                        Specific to ADC instance: ADC4. */
  HAL_ADC_REG_TRIG_LPTIM3_CH2           = LL_ADC_REG_TRIG_EXT_LPTIM3_CH2_ADC4,      /*!< ADC group regular conversion
                                        trigger from periph: LPTIM3 channel 2 event (capture compare).
                                        Specific to ADC instance: ADC4. */
} hal_adc_reg_trig_src_t;

/**
  * @brief HAL ADC group regular conversion trigger edge
  */
typedef enum
{
  HAL_ADC_REG_TRIG_EDGE_NONE            = 0x00000000UL,                      /*!< ADC group regular conversion
                                        trigger disabled (SW start) */
  HAL_ADC_REG_TRIG_EDGE_RISING          = LL_ADC_REG_TRIG_EXT_RISING,        /*!< ADC group regular conversion
                                        trigger polarity set to rising edge */
  HAL_ADC_REG_TRIG_EDGE_FALLING         = LL_ADC_REG_TRIG_EXT_FALLING,       /*!< ADC group regular conversion
                                        trigger polarity set to falling edge */
  HAL_ADC_REG_TRIG_EDGE_RISING_FALLING  = LL_ADC_REG_TRIG_EXT_RISINGFALLING, /*!< ADC group regular conversion
                                        trigger polarity set to both rising and falling edges */
} hal_adc_reg_trig_edge_t;

/**
  * @brief HAL ADC group regular sequencer scan discontinuous length
  */
typedef enum
{
  HAL_ADC_REG_SEQ_DISCONT_DISABLE       = LL_ADC_REG_SEQ_DISCONT_DISABLE, /*!< ADC group regular sequencer discontinuous
                                        mode disabled */
  HAL_ADC_REG_SEQ_DISCONT_1RANK         = LL_ADC_REG_SEQ_DISCONT_1RANK,   /*!< ADC group regular sequencer discontinuous
                                        mode enabled with sequence interruption every rank */
  HAL_ADC_REG_SEQ_DISCONT_2RANKS        = LL_ADC_REG_SEQ_DISCONT_2RANKS,  /*!< ADC group regular sequencer discontinuous
                                        mode enabled with sequence interruption every 2 ranks.
                                        (specific to ADC instance: ADC1, ADC2) */
  HAL_ADC_REG_SEQ_DISCONT_3RANKS        = LL_ADC_REG_SEQ_DISCONT_3RANKS,  /*!< ADC group regular sequencer discontinuous
                                        mode enabled with sequence interruption every 3 ranks.
                                        (specific to ADC instance: ADC1, ADC2) */
  HAL_ADC_REG_SEQ_DISCONT_4RANKS        = LL_ADC_REG_SEQ_DISCONT_4RANKS,  /*!< ADC group regular sequencer discontinuous
                                        mode enabled with sequence interruption every 4 ranks.
                                        (specific to ADC instance: ADC1, ADC2) */
  HAL_ADC_REG_SEQ_DISCONT_5RANKS        = LL_ADC_REG_SEQ_DISCONT_5RANKS,  /*!< ADC group regular sequencer discontinuous
                                        mode enabled with sequence interruption every 5 ranks.
                                        (specific to ADC instance: ADC1, ADC2) */
  HAL_ADC_REG_SEQ_DISCONT_6RANKS        = LL_ADC_REG_SEQ_DISCONT_6RANKS,  /*!< ADC group regular sequencer discontinuous
                                        mode enabled with sequence interruption every 6 ranks.
                                        (specific to ADC instance: ADC1, ADC2) */
  HAL_ADC_REG_SEQ_DISCONT_7RANKS        = LL_ADC_REG_SEQ_DISCONT_7RANKS,  /*!< ADC group regular sequencer discontinuous
                                        mode enabled with sequence interruption every 7 ranks.
                                        (specific to ADC instance: ADC1, ADC2) */
  HAL_ADC_REG_SEQ_DISCONT_8RANKS        = LL_ADC_REG_SEQ_DISCONT_8RANKS   /*!< ADC group regular sequencer discontinuous
                                        mode enabled with sequence interruption every 8 ranks.
                                        (specific to ADC instance: ADC1, ADC2) */
} hal_adc_reg_seq_discont_length_t;

/**
  * @brief HAL ADC group regular sequencer configuration flexibility
  */
typedef enum
{
  HAL_ADC_REG_SEQ_FIXED                 = LL_ADC_REG_SEQ_FIXED,        /*!< Sequencer configured to not fully
                                        configurable: sequencer length and each rank affectation to a channel
                                        are fixed by channel HW number.
                                        Conversion order: forward (lowest to highest channel number in the sequence),
                                        default case.
                                        (specific to ADC instance: ADC4) */
  HAL_ADC_REG_SEQ_FIXED_BACKWARD        = (LL_ADC_REG_SEQ_FIXED
                                           | LL_ADC_REG_SEQ_SCAN_DIR_BACKWARD), /*!< Sequencer configured to not fully
                                        configurable: sequencer length and each rank affectation to a channel
                                        are fixed by channel HW number.
                                        Conversion order: backward (highest to lowest channel number in the sequence)
                                        (specific to ADC instance: ADC4) */
  HAL_ADC_REG_SEQ_CONFIGURABLE          = LL_ADC_REG_SEQ_CONFIGURABLE /*!< Sequencer configured to fully
                                        configurable: sequencer length and each rank affectation to a channel
                                        are configurable. Limitation: channel number up to 14 maximum.
                                        (specific to ADC instance: ADC4) */
} hal_adc_reg_seq_mode_t;

/**
  * @brief HAL ADC group regular continuous mode
  */
typedef enum
{
  HAL_ADC_REG_CONV_SINGLE               = LL_ADC_REG_CONV_SINGLE,    /*!< ADC conversions performed in single mode:
                                        one conversion per trigger */
  HAL_ADC_REG_CONV_CONTINUOUS           = LL_ADC_REG_CONV_CONTINUOUS /*!< ADC conversions performed in continuous mode:
                                        after the first trigger, following conversions launched successively
                                        automatically */
} hal_adc_reg_continuous_mode_t;

/**
  * @brief HAL ADC group regular overrun mode
  * @note     Overrun occurs when conversion is completed while conversion data in data register (from previous
  *           conversion) has not ben fetched (by CPU or DMA).
  */
typedef enum
{
  HAL_ADC_REG_OVR_DATA_PRESERVED        = LL_ADC_REG_OVR_DATA_PRESERVED,    /*!< ADC group regular behavior in case of
                                        overrun: data preserved.
                                        Note: an internal FIFO of 8 elements in enabled in this mode. Overrun occurs
                                              when the FIFO overflows. FIFO is emptied by successive reads of
                                              data register. */
  HAL_ADC_REG_OVR_DATA_OVERWRITTEN      = LL_ADC_REG_OVR_DATA_OVERWRITTEN /*!< ADC group regular behavior in case of
                                        overrun: data overwritten */
} hal_adc_reg_overrun_mode_t;

/**
  * @brief HAL ADC group regular data transfer
  */
typedef enum
{
  HAL_ADC_REG_DATA_TRANSFER_NONE        = LL_ADC_REG_DR_TRANSFER,            /*!< ADC conversion data are not
                                        transferred (available in ADC data register only)
                                        Note: data transfer to DMA mode (one shot, circular) is managed by function
                                              HAL_ADC_REG_StartConv_DMA(). This literal can be used in this
                                              case. */
  HAL_ADC_REG_DATA_TRANSFER_MDF         = LL_ADC_REG_MDF_TRANSFER            /*!< ADC conversion data are transferred
                                        to peripheral MDF.
                                        Specific to ADC instance: ADC1, ADC2 */
} hal_adc_reg_data_transfer_mode_t;

/**
  * @brief HAL ADC group injected conversion trigger source
  */
typedef enum
{
  HAL_ADC_INJ_TRIG_SOFTWARE_START       = LL_ADC_INJ_TRIG_SOFTWARE,            /*!< ADC group injected conversion
                                        trigger from software start */
  HAL_ADC_INJ_TRIG_TIM1_TRGO            = LL_ADC_INJ_TRIG_EXT_TIM1_TRGO,       /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM1 TRGO event */
  HAL_ADC_INJ_TRIG_TIM1_CH4             = LL_ADC_INJ_TRIG_EXT_TIM1_CH4,        /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM1 channel 4 event (capture compare). */
  HAL_ADC_INJ_TRIG_TIM2_TRGO            = LL_ADC_INJ_TRIG_EXT_TIM2_TRGO,       /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM2 TRGO event */
  HAL_ADC_INJ_TRIG_TIM2_CH1             = LL_ADC_INJ_TRIG_EXT_TIM2_CH1,        /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM2 channel 1 event (capture compare). */
  HAL_ADC_INJ_TRIG_TIM3_CH4             = LL_ADC_INJ_TRIG_EXT_TIM3_CH4,        /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM3 channel 4 event (capture compare). */
  HAL_ADC_INJ_TRIG_TIM4_TRGO            = LL_ADC_INJ_TRIG_EXT_TIM4_TRGO,       /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM4 TRGO event */
  HAL_ADC_INJ_TRIG_EXTI15               = LL_ADC_INJ_TRIG_EXT_EXTI_LINE15,     /*!< ADC group injected conversion
                                        trigger from external peripheral: external interrupt line 15 event. */
  HAL_ADC_INJ_TRIG_TIM8_CH4             = LL_ADC_INJ_TRIG_EXT_TIM8_CH4,        /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM8 channel 4 event (capture compare). */
  HAL_ADC_INJ_TRIG_TIM1_TRGO2           = LL_ADC_INJ_TRIG_EXT_TIM1_TRGO2,      /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM1 TRGO2 event */
  HAL_ADC_INJ_TRIG_TIM8_TRGO            = LL_ADC_INJ_TRIG_EXT_TIM8_TRGO,       /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM8 TRGO event */
  HAL_ADC_INJ_TRIG_TIM8_TRGO2           = LL_ADC_INJ_TRIG_EXT_TIM8_TRGO2,      /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM8 TRGO2 event */
  HAL_ADC_INJ_TRIG_TIM3_CH3             = LL_ADC_INJ_TRIG_EXT_TIM3_CH3,        /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM3 channel 3 event (capture compare). */
  HAL_ADC_INJ_TRIG_TIM3_TRGO            = LL_ADC_INJ_TRIG_EXT_TIM3_TRGO,       /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM3 TRGO event */
  HAL_ADC_INJ_TRIG_TIM3_CH1             = LL_ADC_INJ_TRIG_EXT_TIM3_CH1,        /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM3 channel 1 event (capture compare). */
  HAL_ADC_INJ_TRIG_TIM6_TRGO            = LL_ADC_INJ_TRIG_EXT_TIM6_TRGO,       /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM6 TRGO event */
  HAL_ADC_INJ_TRIG_TIM15_TRGO           = LL_ADC_INJ_TRIG_EXT_TIM15_TRGO,      /*!< ADC group injected conversion
                                        trigger from external peripheral: TIM15 TRGO event */
  HAL_ADC_INJ_TRIG_LPTIM1_CH2           = LL_ADC_INJ_TRIG_EXT_LPTIM1_CH2,      /*!< ADC group injected conversion
                                        trigger from external peripheral: LPTIM1 channel 1 event (capture compare). */
  HAL_ADC_INJ_TRIG_LPTIM2_CH2           = LL_ADC_INJ_TRIG_EXT_LPTIM2_CH2,      /*!< ADC group injected conversion
                                        trigger from external peripheral: LPTIM2 channel 2 event (capture compare). */
  HAL_ADC_INJ_TRIG_LPTIM3_CH1           = LL_ADC_INJ_TRIG_EXT_LPTIM3_CH1,      /*!< ADC group injected conversion
                                        trigger from external peripheral: LPTIM3 channel 1 event (capture compare). */
  HAL_ADC_INJ_TRIG_LPTIM4_OUT           = LL_ADC_INJ_TRIG_EXT_LPTIM4_OUT,      /*!< ADC group injected conversion
                                        trigger from external peripheral: LPTIM4 output event. */
  HAL_ADC_INJ_TRIG_FROM_REGULAR         = LL_ADC_INJ_TRIG_FROM_REGULAR /*!< ADC group injected conversion
                                        trigger from ADC group regular end of sequence (no action ADC group injected
                                        conversion start or stop).
                                        Intended usage: extend ADC group regular sequencer length. */
} hal_adc_inj_trig_src_t;

/**
  * @brief HAL ADC group injected conversion trigger edge
  */
typedef enum
{
  HAL_ADC_INJ_TRIG_EDGE_NONE            = 0x00000000UL,                      /*!< ADC group injected conversion
                                        trigger disabled (SW start) */
  HAL_ADC_INJ_TRIG_EDGE_RISING          = LL_ADC_INJ_TRIG_EXT_RISING,        /*!< ADC group injected conversion
                                        trigger polarity set to rising edge */
  HAL_ADC_INJ_TRIG_EDGE_FALLING         = LL_ADC_INJ_TRIG_EXT_FALLING,       /*!< ADC group injected conversion
                                        trigger polarity set to falling edge */
  HAL_ADC_INJ_TRIG_EDGE_RISING_FALLING  = LL_ADC_INJ_TRIG_EXT_RISINGFALLING, /*!< ADC group injected conversion
                                        trigger polarity set to both rising and falling edges */
} hal_adc_inj_trig_edge_t;

/**
  * @brief HAL ADC group injected sequencer scan discontinuous length
  */
typedef enum
{
  HAL_ADC_INJ_SEQ_DISCONT_DISABLE       = LL_ADC_INJ_SEQ_DISCONT_DISABLE, /*!< ADC group injected sequencer discontinuous
                                        mode disabled */
  HAL_ADC_INJ_SEQ_DISCONT_1RANK         = LL_ADC_INJ_SEQ_DISCONT_1RANK,   /*!< ADC group injected sequencer discontinuous
                                        mode enabled with sequence interruption every rank */
} hal_adc_inj_seq_discont_length_t;

/**
  * @brief HAL ADC channel
  */
typedef enum
{
  HAL_ADC_CHANNEL_0                     = LL_ADC_CHANNEL_0,               /*!< ADC channel to GPIO pin ADCx_IN0  */
  HAL_ADC_CHANNEL_1                     = LL_ADC_CHANNEL_1,               /*!< ADC channel to GPIO pin ADCx_IN1  */
  HAL_ADC_CHANNEL_2                     = LL_ADC_CHANNEL_2,               /*!< ADC channel to GPIO pin ADCx_IN2  */
  HAL_ADC_CHANNEL_3                     = LL_ADC_CHANNEL_3,               /*!< ADC channel to GPIO pin ADCx_IN3  */
  HAL_ADC_CHANNEL_4                     = LL_ADC_CHANNEL_4,               /*!< ADC channel to GPIO pin ADCx_IN4  */
  HAL_ADC_CHANNEL_5                     = LL_ADC_CHANNEL_5,               /*!< ADC channel to GPIO pin ADCx_IN5  */
  HAL_ADC_CHANNEL_6                     = LL_ADC_CHANNEL_6,               /*!< ADC channel to GPIO pin ADCx_IN6  */
  HAL_ADC_CHANNEL_7                     = LL_ADC_CHANNEL_7,               /*!< ADC channel to GPIO pin ADCx_IN7  */
  HAL_ADC_CHANNEL_8                     = LL_ADC_CHANNEL_8,               /*!< ADC channel to GPIO pin ADCx_IN8  */
  HAL_ADC_CHANNEL_9                     = LL_ADC_CHANNEL_9,               /*!< ADC channel to GPIO pin ADCx_IN9  */
  HAL_ADC_CHANNEL_10                    = LL_ADC_CHANNEL_10,              /*!< ADC channel to GPIO pin ADCx_IN10 */
  HAL_ADC_CHANNEL_11                    = LL_ADC_CHANNEL_11,              /*!< ADC channel to GPIO pin ADCx_IN11 */
  HAL_ADC_CHANNEL_12                    = LL_ADC_CHANNEL_12,              /*!< ADC channel to GPIO pin ADCx_IN12 */
  HAL_ADC_CHANNEL_13                    = LL_ADC_CHANNEL_13,              /*!< ADC channel to GPIO pin ADCx_IN13 */
  HAL_ADC_CHANNEL_14                    = LL_ADC_CHANNEL_14,              /*!< ADC channel to GPIO pin ADCx_IN14 */
  HAL_ADC_CHANNEL_15                    = LL_ADC_CHANNEL_15,              /*!< ADC channel to GPIO pin ADCx_IN15 */
  HAL_ADC_CHANNEL_16                    = LL_ADC_CHANNEL_16,              /*!< ADC channel to GPIO pin ADCx_IN16 */
  HAL_ADC_CHANNEL_17                    = LL_ADC_CHANNEL_17,              /*!< ADC channel to GPIO pin ADCx_IN17 */
  HAL_ADC_CHANNEL_18                    = LL_ADC_CHANNEL_18,              /*!< ADC channel to GPIO pin ADCx_IN18 */
  HAL_ADC_CHANNEL_19                    = LL_ADC_CHANNEL_19,              /*!< ADC channel to GPIO pin ADCx_IN19 */
  HAL_ADC_CHANNEL_20                    = LL_ADC_CHANNEL_20,              /*!< ADC channel to GPIO pin ADCx_IN20 */
  HAL_ADC_CHANNEL_21                    = LL_ADC_CHANNEL_21,              /*!< ADC channel to GPIO pin ADCx_IN21 */
  HAL_ADC_CHANNEL_22                    = LL_ADC_CHANNEL_22,              /*!< ADC channel to GPIO pin ADCx_IN22 */
  HAL_ADC_CHANNEL_23                    = LL_ADC_CHANNEL_23,              /*!< ADC channel to GPIO pin ADCx_IN23 */
  HAL_ADC_CHANNEL_VREFINT               = LL_ADC_CHANNEL_VREFINT,         /*!< ADC channel to VrefInt (internal
                                        voltage reference) */
  HAL_ADC_CHANNEL_TEMPSENSOR            = LL_ADC_CHANNEL_TEMPSENSOR,      /*!< ADC channel to internal temperature
                                        sensor. */
  HAL_ADC_CHANNEL_VBAT                  = LL_ADC_CHANNEL_VBAT,            /*!< ADC channel to Vbat/4: Vbat voltage
                                        through a divider ladder of factor 1/4 (to have Vbat always below Vdda) */
  HAL_ADC_CHANNEL_DAC1CH1               = LL_ADC_CHANNEL_DAC1CH1_ADC4,    /*!< ADC channel to DAC1 channel 1,
                                        specific to ADC instance: ADC4 */
  HAL_ADC_CHANNEL_DAC1CH2               = LL_ADC_CHANNEL_DAC1CH2_ADC4,    /*!< ADC channel to DAC1 channel 2,
                                        specific to ADC instance: ADC4 */
  HAL_ADC_CHANNEL_VDDCORE               = LL_ADC_CHANNEL_VDDCORE,          /*!< ADC channel to VddCore,
                                        specific to ADC instance: ADC4 */
  HAL_ADC_CHANNEL_NONE                  = LL_ADC_CHANNEL_NONE,             /*!< No ADC channels selected (usable only
                                        by specific functions: analog watchdog configuration) */
  HAL_ADC_CHANNEL_ALL                   = LL_ADC_CHANNEL_ALL,              /*!< All ADC channels selected (usable only
                                        by specific functions: analog watchdog configuration) */
} hal_adc_channel_t;

/**
  * @brief HAL ADC sampling time (channel wise)
  */
typedef enum
{
  HAL_ADC_SAMPLING_TIME_5CYCLES         = LL_ADC_SAMPLINGTIME_5CYCLES,      /*!< Sampling time 5 ADC clock cycles
                                        (specific to ADC instance: ADC1, ADC2) */
  HAL_ADC_SAMPLING_TIME_6CYCLES         = LL_ADC_SAMPLINGTIME_6CYCLES,      /*!< Sampling time 6 ADC clock cycles
                                        (specific to ADC instance: ADC1, ADC2) */
  HAL_ADC_SAMPLING_TIME_12CYCLES        = LL_ADC_SAMPLINGTIME_12CYCLES,     /*!< Sampling time 12 ADC clock cycles
                                        (specific to ADC instance: ADC1, ADC2) */
  HAL_ADC_SAMPLING_TIME_20CYCLES        = LL_ADC_SAMPLINGTIME_20CYCLES,     /*!< Sampling time 20 ADC clock cycles
                                        (specific to ADC instance: ADC1, ADC2) */
  HAL_ADC_SAMPLING_TIME_36CYCLES        = LL_ADC_SAMPLINGTIME_36CYCLES,     /*!< Sampling time 36 ADC clock cycles
                                        (specific to ADC instance: ADC1, ADC2) */
  HAL_ADC_SAMPLING_TIME_68CYCLES        = LL_ADC_SAMPLINGTIME_68CYCLES,     /*!< Sampling time 68 ADC clock cycles
                                        (specific to ADC instance: ADC1, ADC2) */
  HAL_ADC_SAMPLING_TIME_391CYCLES       = LL_ADC_SAMPLINGTIME_391CYCLES,    /*!< Sampling time 391 ADC clock cycles
                                        (specific to ADC instance: ADC1, ADC2) */
  HAL_ADC_SAMPLING_TIME_814CYCLES       = LL_ADC_SAMPLINGTIME_814CYCLES,    /*!< Sampling time 814 ADC clock cycles
                                        (specific to ADC instance: ADC1, ADC2) */
  HAL_ADC_SAMPLING_TIME_COMMON_1        = LL_ADC_SAMPLINGTIME_COMMON_1,    /*!< Sampling time common to a group of
                                        channels: sampling time nb 1 (specific to ADC instance: ADC4) */
  HAL_ADC_SAMPLING_TIME_COMMON_2        = LL_ADC_SAMPLINGTIME_COMMON_2,    /*!< Sampling time common to a group of
                                        channels: sampling time nb 2 (specific to ADC instance: ADC4) */
} hal_adc_sampling_time_t;

/**
  * @brief HAL ADC channel input mode (single, differential ended)
  */
typedef enum
{
  HAL_ADC_IN_SINGLE_ENDED               = LL_ADC_IN_SINGLE_ENDED, /*!< ADC channel input set to single-ended */
  HAL_ADC_IN_DIFFERENTIAL               = LL_ADC_IN_DIFFERENTIAL, /*!< ADC channel input set to differential */
} hal_adc_in_mode_t;

/**
  * @brief HAL ADC analog watchdog instance
  * @note  Analog watchdog instances specificities:
  *        - AWD standard (instance AWD1):
  *          - channels monitored: can monitor 1 channel or all channels.
  *          - groups monitored: ADC groups regular and-or injected.
  *          - resolution: resolution is not limited (corresponds to ADC resolution configured).
  *        - AWD flexible (instances AWD2, AWD3):
  *          - channels monitored: flexible on channels monitored, selection is channel wise,
  *            from from 1 to all channels.
  *          - groups monitored: no selection possible (monitoring on both groups regular and injected).
  */
typedef enum
{
  HAL_ADC_AWD_1                         = LL_ADC_AWD_1, /*!< ADC analog watchdog number 1 */
  HAL_ADC_AWD_2                         = LL_ADC_AWD_2, /*!< ADC analog watchdog number 2 */
  HAL_ADC_AWD_3                         = LL_ADC_AWD_3  /*!< ADC analog watchdog number 3 */
} hal_adc_awd_instance_t;

/**
  * @brief HAL ADC analog watchdog threshold selection
  */
typedef enum
{
  HAL_ADC_AWD_THRESHOLD_HIGH            = LL_ADC_AWD_THRESHOLD_HIGH, /*!< ADC analog watchdog threshold high */
  HAL_ADC_AWD_THRESHOLD_LOW             = LL_ADC_AWD_THRESHOLD_LOW,  /*!< ADC analog watchdog threshold low */
} hal_adc_awd_threshold_sel_t;

/**
  * @brief HAL ADC analog watchdog filtering
  */
typedef enum
{
  HAL_ADC_AWD_FILTERING_NONE            = LL_ADC_AWD_FILTERING_NONE,     /*!< ADC analog watchdog no filtering, one
                                        out-of-window sample triggers flag raise */
  HAL_ADC_AWD_FILTERING_2SAMPLES        = LL_ADC_AWD_FILTERING_2SAMPLES, /*!< ADC analog watchdog 2 consecutives
                                        out-of-window samples trigger flag raise */
  HAL_ADC_AWD_FILTERING_3SAMPLES        = LL_ADC_AWD_FILTERING_3SAMPLES, /*!< ADC analog watchdog 3 consecutives
                                        out-of-window samples trigger flag raise */
  HAL_ADC_AWD_FILTERING_4SAMPLES        = LL_ADC_AWD_FILTERING_4SAMPLES, /*!< ADC analog watchdog 4 consecutives
                                        out-of-window samples trigger flag raise */
  HAL_ADC_AWD_FILTERING_5SAMPLES        = LL_ADC_AWD_FILTERING_5SAMPLES, /*!< ADC analog watchdog 5 consecutives
                                        out-of-window samples trigger flag raise */
  HAL_ADC_AWD_FILTERING_6SAMPLES        = LL_ADC_AWD_FILTERING_6SAMPLES, /*!< ADC analog watchdog 6 consecutives
                                        out-of-window samples trigger flag raise */
  HAL_ADC_AWD_FILTERING_7SAMPLES        = LL_ADC_AWD_FILTERING_7SAMPLES, /*!< ADC analog watchdog 7 consecutives
                                        out-of-window samples trigger flag raise */
  HAL_ADC_AWD_FILTERING_8SAMPLES        = LL_ADC_AWD_FILTERING_8SAMPLES /*!< ADC analog watchdog 8 consecutives
                                        out-of-window samples trigger flag raise */
} hal_adc_awd_filtering_t;

/**
  * @brief HAL ADC oversampling instance
  */
typedef enum
{
  HAL_ADC_OVS_1                         = LL_ADC_OVS_1, /*!< ADC oversampling instance for standard oversampling:
                                        a single oversampling accumulator is common to regular and injected conversions.
                                        Therefore, settings ratio and shift are common and process is sequential.
                                        For constraints of oversampling on groups regular and injected,
                                        refer to parameters of @ref hal_adc_ovs_scope_t. */
} hal_adc_ovs_instance_t;

/**
  * @brief HAL ADC oversampling scope
  */
typedef enum
{
  HAL_ADC_OVS_DISABLE                   = LL_ADC_OVS_DISABLE, /*!< ADC oversampling disabled. */
  HAL_ADC_OVS_REG_CONTINUED             = LL_ADC_OVS_REG_CONTINUED, /*!< ADC oversampling on conversions of
                                        ADC group regular.
                                        If ADC group injected conversion insertion within regular sequence: oversampling
                                        on group regular is temporary stopped and, after injected conversion, continued
                                        (oversampling accumulator maintained). */
  HAL_ADC_OVS_REG_RESUMED               = LL_ADC_OVS_REG_RESUMED, /*!< ADC oversampling on conversions of
                                        ADC group regular.
                                        If ADC group injected conversion insertion within regular sequence: after
                                        injected conversion, oversampling on group regular is resumed from start
                                        (oversampler accumulator reset). */
  HAL_ADC_OVS_INJ                       = LL_ADC_OVS_INJ, /*!< ADC oversampling on conversions of
                                        ADC group injected, in sequential mode:
                                        oversampling conversions sequence sequential, switching data registers
                                        after each oversampling process (all ratio occurrences, shift).
                                        Note: A single oversampling accumulator is common to regular
                                              and injected conversions. Therefore, settings ratio and shift are common
                                              and process is sequential. */
  HAL_ADC_OVS_INJ_REG_RESUMED           = LL_ADC_OVS_INJ_REG_RESUMED, /*!< ADC oversampling on conversions
                                        of ADC groups regular and injected.
                                        Combination of LL_ADC_OVS_REG_RESUMED and LL_ADC_OVS_INJ: refer to
                                        description of these parameters. */
} hal_adc_ovs_scope_t;

/**
  * @brief HAL ADC oversampling discontinuous mode
  */
typedef enum
{
  HAL_ADC_OVS_CONT                      = LL_ADC_OVS_CONT,   /*!< ADC oversampling discontinuous mode: continuous
                                        (all conversions of oversampling ratio start from 1 trigger) */
  HAL_ADC_OVS_DISCONT                   = LL_ADC_OVS_DISCONT /*!< ADC oversampling discontinuous mode: discontinuous
                                        (each conversion of oversampling ratio needs a trigger) */
} hal_adc_ovs_discont_t;

/**
  * @brief HAL ADC offset instance
  */
typedef enum
{
  HAL_ADC_OFFSET_1                      = LL_ADC_OFFSET_1, /*!< ADC offset instance 1: ADC channel and offset level
                                        to which the offset programmed will be applied (independently of channel
                                        assigned on ADC group regular or injected sequencer) */
  HAL_ADC_OFFSET_2                      = LL_ADC_OFFSET_2, /*!< ADC offset instance 2: ADC channel and offset level
                                        to which the offset programmed will be applied (independently of channel
                                        assigned on ADC group regular or injected sequencer) */
  HAL_ADC_OFFSET_3                      = LL_ADC_OFFSET_3, /*!< ADC offset instance 3: ADC channel and offset level
                                        to which the offset programmed will be applied (independently of channel
                                        assigned on ADC group regular or injected sequencer) */
  HAL_ADC_OFFSET_4                      = LL_ADC_OFFSET_4, /*!< ADC offset instance 4: ADC channel and offset level
                                        to which the offset programmed will be applied (independently of channel
                                        assigned on ADC group regular or injected sequencer) */
} hal_adc_offset_instance_t;

/**
  * @brief HAL ADC offset signed saturation
  */
typedef enum
{
  HAL_ADC_OFFSET_SAT_SIGNED_DISABLE     = LL_ADC_OFFSET_SIGNED_SATURATION_DISABLE, /*!< ADC offset signed saturation
                                        disabled */
  HAL_ADC_OFFSET_SAT_SIGNED_ENABLE      = LL_ADC_OFFSET_SIGNED_SATURATION_ENABLE   /*!< ADC offset signed saturation
                                        enabled */
} hal_adc_offset_sat_sign_state_t;

/**
  * @brief HAL ADC offset unsigned saturation
  */
typedef enum
{
  HAL_ADC_OFFSET_SAT_UNSIGNED_DISABLE   = LL_ADC_OFFSET_UNSIGNED_SATURATION_DISABLE, /*!< ADC offset unsigned saturation
                                        disabled */
  HAL_ADC_OFFSET_SAT_UNSIGNED_ENABLE    = LL_ADC_OFFSET_UNSIGNED_SATURATION_ENABLE   /*!< ADC offset unsigned saturation
                                        enabled */
} hal_adc_offset_sat_unsign_state_t;

#if defined(ADC_MULTIMODE_SUPPORT)
/**
  * @brief HAL ADC multimode - Instances
  */
typedef enum
{
  HAL_ADC_MM_MASTER                     = LL_ADC_MULTI_MASTER,      /*!< Multimode ADC instance selection: ADC master */
  HAL_ADC_MM_SLAVE                      = LL_ADC_MULTI_SLAVE,       /*!< Multimode ADC instance selection: ADC slave */
  HAL_ADC_MM_MASTER_SLAVE               = LL_ADC_MULTI_MASTER_SLAVE /*!< Multimode ADC instance selection: both
                                        ADC master and ADC slave */
} hal_adc_mm_inst_t;

/**
  * @brief HAL ADC multimode - Mode
  */
typedef enum
{
  HAL_ADC_MM_INDEPENDENT                = LL_ADC_MULTI_INDEPENDENT,          /*!< ADC dual mode disabled
                                        (ADC independent mode) */
  HAL_ADC_MM_DUAL_REG_SIMULT            = LL_ADC_MULTI_DUAL_REG_SIMULT,      /*!< ADC dual mode group regular
                                        simultaneous */
  HAL_ADC_MM_DUAL_REG_INTERL            = LL_ADC_MULTI_DUAL_REG_INTERL,      /*!< ADC dual mode group regular
                                        interleaved */
  HAL_ADC_MM_DUAL_INJ_SIMULT            = LL_ADC_MULTI_DUAL_INJ_SIMULT,      /*!< ADC dual mode group injected
                                        simultaneous */
  HAL_ADC_MM_DUAL_INJ_ALTERN            = LL_ADC_MULTI_DUAL_INJ_ALTERN,      /*!< ADC dual mode group injected
                                        alternate trigger. Works only with external triggers (not SW start) */
  HAL_ADC_MM_DUAL_REG_SIM_INJ_SIM       = LL_ADC_MULTI_DUAL_REG_SIM_INJ_SIM, /*!< ADC dual mode combined group regular
                                        simultaneous + group injected simultaneous */
  HAL_ADC_MM_DUAL_REG_SIM_INJ_ALT       = LL_ADC_MULTI_DUAL_REG_SIM_INJ_ALT, /*!< ADC dual mode combined group regular
                                        simultaneous + group injected alternate trigger */
  HAL_ADC_MM_DUAL_REG_INT_INJ_SIM       = LL_ADC_MULTI_DUAL_REG_INT_INJ_SIM, /*!< ADC dual mode combined group regular
                                        interleaved + group injected simultaneous */
} hal_adc_mm_mode_t;

/**
  * @brief HAL ADC multimode - Data format
  */
typedef enum
{
  HAL_ADC_MM_REG_DATA_EACH_ADC          = LL_ADC_MULTI_REG_DMA_EACH_ADC,   /*!< ADC multimode group regular
                                        data format: full range, no data packing.
                                        Intended for cases:
                                        - multimode without DMA transfer
                                        - multimode with DMA transfer in two different buffers.
                                        - high data width (can exceed ADC resolution in case of
                                          oversampling or post-processing: offset, ...) over data packing constraints.
                                        For no data transfer:
                                        - to retrieve conversion data, use @ref HAL_ADC_REG_GetValue() with each
                                          ADC instance.
                                        For data transfer by DMA:
                                        - use function @ref HAL_ADC_MM_REG_StartConvM_DMA().
                                          Each ADC uses its own DMA channel, with its individual DMA transfer
                                          settings. Therefore, two destination buffers. */
  HAL_ADC_MM_REG_DATA_PACK_32_BITS      = LL_ADC_MULTI_REG_DMA_RES_32_10B, /*!< ADC multimode group regular
                                        data format: full range (no packing) and 2 data packing on 32 bits.
                                        Intended for cases:
                                        - multimode with DMA transfer in a single buffer.
                                        - high data width (can exceed ADC resolution in case of
                                          oversampling or post-processing: offset, ...) over data packing constraints.
                                        For no data transfer:
                                        - to retrieve conversion data, use @ref HAL_ADC_MM_REG_GetValue()
                                          or @ref HAL_ADC_REG_GetValue() with each ADC instance.
                                        For data transfer by DMA:
                                        - with data packing on 32 bits: ADC master and slave data are concatenated
                                          (data master in [15; 0], data slave in [31; 16]),
                                          therefore data width must be lower than 16 bits.
                                          Use parameter hal_adc_mm_reg_data_transfer_pack_t
                                          value @ref HAL_ADC_MM_REG_DATA_TRANSFER_PACK.
                                        - with no data packing: data of master and slave are alternatively set in full
                                          register width 32 bits, therefore no constraint on data width.
                                          Use parameter hal_adc_mm_reg_data_transfer_pack_t
                                          value @ref HAL_ADC_MM_REG_DATA_TRANSFER_UNPACK. */
  HAL_ADC_MM_REG_DATA_PACK_16_BITS      = LL_ADC_MULTI_REG_DMA_RES_8B      /*!< ADC multimode group regular
                                        data format: full range (no packing) and 2 data packing on 16 bits.
                                        Intended for cases:
                                        - multimode with DMA transfer in a single buffer with elements 16 bits.
                                        For no data transfer:
                                        - to retrieve conversion data, use @ref HAL_ADC_REG_GetValue() with each
                                          ADC instance.
                                        For data transfer by DMA:
                                        - with data packing on 16 bits: ADC master and slave data are concatenated
                                          (data master in [7; 0], data slave in [15; 8]),
                                          therefore data width must be lower than 8 bits.
                                          Use parameter hal_adc_mm_reg_data_transfer_pack_t
                                          value @ref HAL_ADC_MM_REG_DATA_TRANSFER_PACK.
                                        - with no data packing: same as setting HAL_ADC_MM_REG_DATA_PACK_32_BITS. */
} hal_adc_mm_reg_data_format_t;

#if defined(USE_HAL_ADC_DMA) && (USE_HAL_ADC_DMA == 1)
/**
  * @brief HAL ADC multimode - Data transfer
  */
typedef enum
{
  HAL_ADC_MM_REG_DATA_TRANSFER_PACK     = LL_ADC_DMA_REG_MM_REGULAR_PACK_DATA, /*!< ADC multimode group regular
                                        data transfer by DMA with packing: data transfer is performed
                                        every 2 conversions of ADC instances part of multimode.
                                        Therefore, for dual mode, destination buffer each element is composed
                                        of data from ADC master and ADC slave concatenated (buffer size equal to
                                        size of each ADC expected number of conversions).
                                        Concatenation format: refer to @ref hal_adc_mm_reg_data_format_t.
                                        Benefit: Number of DMA requests reduced.
                                        Limitation: Setting not compliant with all data width (can exceed ADC
                                        resolution in case of oversampling or post-processing: offset, ...).*/
  HAL_ADC_MM_REG_DATA_TRANSFER_UNPACK   = LL_ADC_DMA_REG_MM_REGULAR_UNPACK_DATA, /*!< ADC multimode group regular
                                        data transfer by DMA without packing: data transfer is performed
                                        for each conversion of ADC instances part of multimode.
                                        Therefore, for dual mode, destination buffer each element is composed
                                        alternatively of data from ADC master and ADC slave (buffer size must be twice
                                        the size of each ADC expected number of conversions).
                                        Benefit: Setting compliant with all data width (can exceed ADC
                                        resolution in case of oversampling or post-processing: offset, ...). */
} hal_adc_mm_reg_data_transfer_pack_t;
#endif /* USE_HAL_ADC_DMA */

/**
  * @brief HAL ADC multimode - Delay between two sampling phases (for mode interleaved)
  */
typedef enum
{
  HAL_ADC_MM_INTERL_DELAY_1CYCLE        = LL_ADC_MULTI_TWOSMP_DELAY_1CYCLE,   /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 1 ADC clock cycle for all resolutions */
  HAL_ADC_MM_INTERL_DELAY_2CYCLES       = LL_ADC_MULTI_TWOSMP_DELAY_2CYCLES,  /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 2 ADC clock cycles for all resolutions */
  HAL_ADC_MM_INTERL_DELAY_3CYCLES       = LL_ADC_MULTI_TWOSMP_DELAY_3CYCLES,  /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 3 ADC clock cycles for all resolutions */
  HAL_ADC_MM_INTERL_DELAY_4CYCLES       = LL_ADC_MULTI_TWOSMP_DELAY_4CYCLES,  /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 4 ADC clock cycles for all resolutions */
  HAL_ADC_MM_INTERL_DELAY_5CYCLES       = LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES,  /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 5 ADC clock cycles for all resolutions */
  HAL_ADC_MM_INTERL_DELAY_6CYCLES       = LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES,  /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 6 ADC clock cycles for all resolutions */
  HAL_ADC_MM_INTERL_DELAY_7CYCLES       = LL_ADC_MULTI_TWOSMP_DELAY_7CYCLES,  /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 7 ADC clock cycles for all resolutions */
  HAL_ADC_MM_INTERL_DELAY_8CYCLES       = LL_ADC_MULTI_TWOSMP_DELAY_8CYCLES,  /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 8 ADC clock cycles for all resolutions */
  HAL_ADC_MM_INTERL_DELAY_9CYCLES       = LL_ADC_MULTI_TWOSMP_DELAY_9CYCLES,  /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 9 ADC clock cycles for all resolutions */
  HAL_ADC_MM_INTERL_DELAY_10CYCLES      = LL_ADC_MULTI_TWOSMP_DELAY_10CYCLES, /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 10 ADC clock cycles for all resolutions */
  HAL_ADC_MM_INTERL_DELAY_11CYCLES      = LL_ADC_MULTI_TWOSMP_DELAY_11CYCLES, /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 11 ADC clock cycles for all resolutions */
  HAL_ADC_MM_INTERL_DELAY_12CYCLES      = LL_ADC_MULTI_TWOSMP_DELAY_12CYCLES, /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 12 ADC clock cycles for all resolutions */
  HAL_ADC_MM_INTERL_DELAY_13CYCLES      = LL_ADC_MULTI_TWOSMP_DELAY_13CYCLES, /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 13 ADC clock cycles for all resolutions */
  HAL_ADC_MM_INTERL_DELAY_14CYCLES      = LL_ADC_MULTI_TWOSMP_DELAY_14CYCLES, /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 14 ADC clock cycles for resolutions
                                        14, 12, 10 bit */
  HAL_ADC_MM_INTERL_DELAY_15CYCLES      = LL_ADC_MULTI_TWOSMP_DELAY_15CYCLES, /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 15 ADC clock cycles for resolution
                                        14, 12, 10 bit */
  HAL_ADC_MM_INTERL_DELAY_16CYCLES      = LL_ADC_MULTI_TWOSMP_DELAY_16CYCLES, /*!< ADC multimode (mode interleaved only)
                                        delay between two sampling phases: 16 ADC clock cycles for resolutions
                                        14, 12 bit */
} hal_adc_mm_interl_delay_t;

#endif /* ADC_MULTIMODE_SUPPORT */

/**
  * @brief HAL ADC events
  */
typedef enum
{
  HAL_ADC_EVENT_EOC                     = LL_ADC_FLAG_EOC,    /*!< ADC event group regular end of unitary conversion */
  HAL_ADC_EVENT_EOS                     = LL_ADC_FLAG_EOS,    /*!< ADC event group regular end of sequence
                                        conversions */
  HAL_ADC_EVENT_OVR                     = LL_ADC_FLAG_OVR,    /*!< ADC event group regular overrun */
  HAL_ADC_EVENT_EOSMP                   = LL_ADC_FLAG_EOSMP,  /*!< ADC event group regular end of sampling phase */
  HAL_ADC_EVENT_JEOC                    = LL_ADC_FLAG_JEOC,   /*!< ADC event group injected end of unitary conversion */
  HAL_ADC_EVENT_JEOS                    = LL_ADC_FLAG_JEOS,   /*!< ADC event group injected end of sequence
                                        conversions */
  HAL_ADC_EVENT_AWD_1                   = LL_ADC_FLAG_AWD1,   /*!< ADC event analog watchdog 1 */
  HAL_ADC_EVENT_AWD_2                   = LL_ADC_FLAG_AWD2,   /*!< ADC event analog watchdog 2 */
  HAL_ADC_EVENT_AWD_3                   = LL_ADC_FLAG_AWD3,   /*!< ADC event analog watchdog 3 */
} hal_adc_event_t;

/**
  * @brief ADC instance configuration
  */
typedef struct
{
  hal_adc_clock_t                       clock;              /*!< ADC kernel clock source and prescaler */
  hal_adc_resolution_t                  resolution;         /*!< ADC resolution */
  hal_adc_trigger_freq_mode_t           trigger_freq_mode;  /*!< ADC trigger frequency mode
                                        (specific to ADC instance: ADC1, ADC2. For ADC4, fixed to low frequency.) */
  hal_adc_sampling_mode_t               sampling_mode;      /*!< ADC sampling mode */
  hal_adc_sampling_time_com_t           sampling_time_com1; /*!< ADC sampling time common to group of channels: group 1
                                        (specific to ADC instance: ADC4) */
  hal_adc_sampling_time_com_t           sampling_time_com2; /*!< ADC sampling time common to group of channels: group 2
                                        (specific to ADC instance: ADC4) */
} hal_adc_config_t;

/**
  * @brief ADC instance configuration advanced: conversion data post processing
  */
typedef struct
{
  hal_adc_left_bit_shift_t              left_bit_shift;          /*!< ADC data post-processing: left bit shift */
  uint32_t                              gain_compensation_x1000; /*!< ADC data post-processing: ADC gain coefficient
                                        applied to raw conversions data. Value multiplicated by 1000 to have an integer
                                        value (example: to set coefficient 0.982, parameter value must be 982).
                                        Therefore, unitary gain corresponds to value 1000.
                                        Can be a number between: Min_Data = 0, Max_Data = 3999
                                        (specific to ADC instance: ADC1, ADC2).
                                        Note: Coefficient resolution managed by ADC peripheral is higher than 1/1000,
                                              if needed to reach more accurate resolution, refer to function
                                              LL_ADC_SetGainCompensation() */
} hal_adc_post_processing_config_t;

/**
  * @brief ADC instance configuration advanced: low power features
  * @note  On this STM32 series, ADC features autonomous operation and the low-power background autonomous mode (LPBAM)
  *        can be enabled from RCC, refer to ref manual "peripheral clock enable in Sleep and Stop modes"
  *        (specific to ADC instance: ADC4).
  */
typedef struct
{
  hal_adc_lp_auto_wait_state_t          lp_auto_wait;       /*!< ADC low power feature autowait */
  hal_adc_lp_auto_power_off_state_t     lp_auto_power_off;  /*!< ADC low power feature auto power-off.
                                        Note: this feature can be combined with auto wait and autonomous operation
                                              (LPBAM).
                                        (specific to ADC instance: ADC4) */
  hal_adc_lp_autonomous_dpd_state_t     lp_autonomous_dpd;  /*!< ADC low power feature deep power down (DPD) mode during
                                        autonomous operation (LPBAM).
                                        Note: this feature is optional for autonomous operation, it allows to optimize
                                              power consumption (with constraint of additional latency delay
                                              from conversion trigger event)
                                        (specific to ADC instance: ADC4) */
} hal_adc_low_power_config_t;

/**
  * @brief ADC calibration data
  */
typedef struct
{
  uint32_t                              factors[HAL_ADC_CALIB_FACTORS_BUF_SIZE]; /*!< ADC calibration factors buffer.
                                        Depending on ADC instance, buffer content differs:
                                        - ADC1, ADC2: 1st index for offset factor, others for
                                          linearity factors.
                                        - ADC4: 1st index for offset factor, others unused. */
} hal_adc_calib_t;

/**
  * @brief ADC group regular configuration
  */
typedef struct
{
  hal_adc_reg_trig_src_t                trigger_src;        /*!< ADC group regular conversion trigger source */
  hal_adc_reg_trig_edge_t               trigger_edge;       /*!< ADC group regular conversion trigger edge */
  uint8_t                               sequencer_length;   /*!< ADC group regular sequencer scan length.
                                        Note: Specificity with ADC instance ADC4: parameter conditioned to
                                              parameter "sequencer_mode" set to configurable (otherwise, length equal
                                              to number of channels set)
                                        Depending on ADC instance, can be a number between:
                                        - ADC1, ADC2: Min_Data = 1, Max_Data = 16
                                        - ADC4: Min_Data = 1, Max_Data = 8 */
  hal_adc_reg_seq_discont_length_t      sequencer_discont;  /*!< ADC group regular sequencer scan discontinuous
                                        length */
  hal_adc_reg_seq_mode_t                sequencer_mode;     /*!< ADC group regular sequencer configurability
                                        (specific to ADC instance: ADC4) */
  hal_adc_reg_continuous_mode_t         continuous;         /*!< ADC group regular continuous mode */
  hal_adc_reg_overrun_mode_t            overrun;            /*!< ADC group regular overrun mode */
  hal_adc_reg_data_transfer_mode_t      data_transfer;      /*!< ADC group regular data transfer */
} hal_adc_reg_config_t;

/**
  * @brief ADC group injected configuration
  */
typedef struct
{
  hal_adc_inj_trig_src_t                trigger_src;        /*!< ADC group injected conversion trigger source */
  hal_adc_inj_trig_edge_t               trigger_edge;       /*!< ADC group injected conversion trigger edge */
  uint8_t                               sequencer_length;   /*!< ADC group injected sequencer scan length.
                                        Can be a number between Min_Data = 1, Max_Data = 4 */
  hal_adc_inj_seq_discont_length_t      sequencer_discont;  /*!< ADC group injected sequencer scan discontinuous length */
} hal_adc_inj_config_t;

/**
  * @brief ADC channel configuration
  */
typedef struct
{
  hal_adc_group_t                       group;              /*!< ADC group in which set the channel
                                        Note: to remove a channel from sequencer in mode not fully
                                              configurable (refer to hal_adc_reg_seq_mode_t), use HAL_ADC_GROUP_NONE
                                              (specific to ADC instance: ADC4).
                                        In other modes, overwrite rank with a new channel configuration. */
  uint8_t                               sequencer_rank;     /*!< ADC group sequencer rank (position in conversions sequence)
                                        Note: Specificity with ADC instance ADC4: parameter conditioned to
                                              parameter "sequencer_mode" set to configurable (otherwise, rank fixed to
                                              channel number)
                                        Can be a number in range of parameter "sequencer_length" in
                                        structures hal_adc_reg_config_t and hal_adc_inj_config_t:
                                        Min_Data = 1, Max_Data = {4; 8; 16} depending on ADC group and ADC instance. */
  hal_adc_sampling_time_t               sampling_time;      /*!< Sampling time
                                        Note: Sampling time scope depends on ADC instance: channel wise (ADC1, ADC2)
                                        or group of channels wise (ADC4) */
  hal_adc_in_mode_t                     input_mode;         /*!< ADC channel input mode (single, differential ended) */
} hal_adc_channel_config_t;

/**
  * @brief ADC analog watchdog configuration
  * @note  To use analog watchdog with interruption, start ADC conversion with optional interruption
  *        (HAL_ADC_xxx_StartConv_IT_Opt() or HAL_ADC_xxx_StartConv_DMA_Opt())
  *        and parameter HAL_ADC_OPT_IT_xxx_AWDx.
  */
typedef struct
{
  hal_adc_group_t                       group;              /*!< ADC group from which conversion data is compared
                                        to thresholds.
                                        Analog watchdog instances specificities impacting this parameter: refer to
                                        description of "hal_adc_awd_instance_t". */
  hal_adc_channel_t                     channel;            /*!< ADC channel to be monitored */
  int32_t                               threshold_high;     /*!< ADC analog watchdog threshold high value.
                                        Depending on ADC instance, can be a number:
                                        - ADC1, 2: between Min_Data=-16777216 (two's complement 0xFF000000)
                                          and Max_Data=+16777215 (0x00FFFFFF)
                                        - ADC4: between Min_Data=0x000 and Max_Data=0xFFF
                                        Note: Value is signed and can exceed ADC resolution with post-processing
                                              computation (offset, oversampling, data shift, ...).
                                        Note: To compute digital value from physical value (voltage), use helper macro
                                              @ref HAL_ADC_CALC_VOLTAGE_TO_DATA(). */
  int32_t                               threshold_low;      /*!< ADC analog watchdog threshold high value.
                                        Depending on ADC instance, can be a number:
                                        - ADC1, 2: between Min_Data=-16777216 (two's complement 0xFF000000)
                                          and Max_Data=+16777215 (0x00FFFFFF)
                                        - ADC4: between Min_Data=0x000 and Max_Data=0xFFF
                                        Note: Value is signed and can exceed ADC resolution with post-processing
                                              computation (offset, oversampling, data shift, ...).
                                        Note: To compute digital value from physical value (voltage), use helper macro
                                              @ref HAL_ADC_CALC_VOLTAGE_TO_DATA(). */
  hal_adc_awd_filtering_t               filtering;          /*!< ADC analog watchdog filtering
                                        (specific to ADC instance: ADC1, ADC2 and specific to AWD instance: AWD1) */
} hal_adc_awd_config_t;

/**
  * @brief ADC oversampling configuration
  */
typedef struct
{
  hal_adc_ovs_scope_t                   scope;              /*!< ADC oversampling scope */
  hal_adc_ovs_discont_t                 discont;            /*!< ADC oversampling discontinuous mode */
  uint16_t                              ratio;              /*!< ADC oversampling ratio: sum of conversions data
                                        computed to oversampling conversions data (before potential shift).
                                        Depending on ADC instance, can be a number:
                                        - ADC1, ADC2: between Min_Data = 1, Max_Data = 1024
                                        - ADC4: among list 2, 4, 8, 16, 32, 64, 128, 256 */
  uint8_t                               shift;              /*!< ADC oversampling shift: right bit shift to perform a
                                        division by multiple of 2 of oversampling accumulated data.
                                        Depending on ADC instance, can be a number:
                                        - ADC1, ADC2: between Min_Data = 1, Max_Data = 11
                                        - ADC4:  between Min_Data = 1, Max_Data = 8
                                        Note: to compute shift value from ratio value and keeping data resolution,
                                              use function "HAL_ADC_GetOverSamplingShiftKeepRes()". */
} hal_adc_ovs_config_t;

/**
  * @brief ADC offset configuration
  */
typedef struct
{
  hal_adc_channel_t                     channel;            /*!< ADC channel with related conversion data to be
                                        processed */
  int32_t                               level;              /*!< ADC offset level to be subtracted or added
                                        to the raw ADC converted data.
                                        Value between Min_Data= -1*0x1FFFFFF (two's complement 0xFE000001)
                                        and Max_Data=0x1FFFFFF.
                                        Note: Value is signed and can exceed ADC resolution with post-processing
                                              computation (offset, oversampling, data shift, ...).
                                        Note: To compute digital value from physical value (voltage), use helper macro
                                              @ref HAL_ADC_CALC_VOLTAGE_TO_DATA(). */
  hal_adc_offset_sat_sign_state_t       saturation_signed;  /*!< ADC offset signed saturation */
  hal_adc_offset_sat_unsign_state_t     saturation_unsigned; /*!< ADC offset unsigned saturation */
} hal_adc_offset_config_t;

#if defined(ADC_MULTIMODE_SUPPORT)
/**
  * @brief ADC multimode configuration
  */
typedef struct
{
  hal_adc_mm_mode_t                     mode;               /*!< ADC multimode mode */
  hal_adc_mm_reg_data_format_t          reg_data_format;    /*!< ADC multimode group regular data format */
#if defined(USE_HAL_ADC_DMA) && (USE_HAL_ADC_DMA == 1)
  hal_adc_mm_reg_data_transfer_pack_t   reg_data_transfer_packing; /*!< ADC multimode group regular data transfer
                                                           by DMA packing */
#endif /* USE_HAL_ADC_DMA */
  hal_adc_mm_interl_delay_t             interl_delay;       /*!< ADC multimode interleaved delay between two sampling
                                        phases (parameter applicable only for mode interleaved) */
} hal_adc_mm_config_t;

#endif /* ADC_MULTIMODE_SUPPORT */

/**
  * @brief HAL ADC Handle type definition
  */
typedef struct hal_adc_handle_s hal_adc_handle_t; /*!< ADC handle type definition */

#if defined(USE_HAL_ADC_REGISTER_CALLBACKS) && (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
/**
  * @brief HAL ADC pointers to callback functions
  */
typedef  void (*hal_adc_cb_t)(hal_adc_handle_t *hadc); /*!< pointer to ADC callback function */
typedef  void (*hal_adc_awd_cb_t)(hal_adc_handle_t *hadc, hal_adc_awd_instance_t awd_instance); /*!< pointer to ADC
                                        analog watchdog callback function */
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

/**
  * @brief ADC Handle Structure Definition
  */
struct hal_adc_handle_s
{
  hal_adc_t                             instance;             /*!< Peripheral instance */

#if defined(ADC_INST_IN_COMMON_COUNT) && (ADC_INST_IN_COMMON_COUNT > 1)
  hal_adc_handle_t                      *p_link_next_handle;    /*!< Pointer to another HAL ADC handle of instance
                                        belonging to the same ADC common instance (therefore, sharing common features).
                                        Used to access multiple HAL ADC handles (daisy chain: from one to
                                        another and circular).
                                        Set using function @ref HAL_ADC_SetLinkNextHandle(). */
#endif /* ADC_INST_IN_COMMON_COUNT */

  volatile hal_adc_state_t              global_state;         /*!< HAL ADC global state */
  volatile hal_adc_group_state_t        group_state[HAL_ADC_GROUPS_COUNT]; /*!< HAL ADC groups (regular, injected)
                                        state */
  volatile hal_adc_common_state_t       common_state;         /*!< HAL ADC handle link to common instance state */

  volatile hal_adc_group_conv_per_start_t group_conv_per_start[HAL_ADC_GROUPS_COUNT];  /*!< ADC group conversions per
                                        conversion start configuration */

#if defined(USE_HAL_ADC_DMA) && (USE_HAL_ADC_DMA == 1)
  hal_dma_handle_t                      *hdma_reg;            /*!< Pointer of DMA handle assigned to ADC group regular */
#if defined(ADC_MULTIMODE_SUPPORT)
  hal_adc_mm_reg_data_transfer_pack_t   mm_reg_data_transfer_packing; /*!< ADC multimode group regular data transfer
                                        by DMA packing */
#endif /* ADC_MULTIMODE_SUPPORT */
#endif /* USE_HAL_ADC_DMA */

#if defined(USE_HAL_ADC_USER_DATA) && (USE_HAL_ADC_USER_DATA == 1)
  const void                            *p_user_data;         /*!< User Data Pointer */
#endif /* USE_HAL_ADC_USER_DATA */

#if defined(USE_HAL_ADC_REGISTER_CALLBACKS) && (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
  hal_adc_cb_t                          p_error_cb;           /*!< Callback function: Error */
  hal_adc_cb_t                          p_reg_end_of_sampling_cb; /*!< Callback function: ADC group regular end of
                                        sampling phase */
  hal_adc_cb_t                          p_reg_eoc_cb;         /*!< Callback function: ADC group regular end of
                                        unitary conversion */
  hal_adc_cb_t                          p_reg_eos_cb;         /*!< Callback function: ADC group regular end of
                                        sequence conversions */
#if defined(USE_HAL_ADC_DMA) && (USE_HAL_ADC_DMA == 1)
  hal_adc_cb_t                          p_reg_xfer_half_cb;   /*!< Callback function: ADC group regular conversion data
                                        buffer half transfer */
  hal_adc_cb_t                          p_reg_xfer_cplt_cb;   /*!< Callback function: ADC group regular conversion data
                                        buffer transfer complete */
  hal_adc_cb_t                          p_reg_xfer_stop_cb;   /*!< Callback function: ADC group regular conversion data
                                        transfer abort */
#endif /* USE_HAL_ADC_DMA */
  hal_adc_cb_t                          p_inj_eoc_cb;         /*!< Callback function: ADC group injected end of
                                        unitary conversion */
  hal_adc_cb_t                          p_inj_eos_cb;         /*!< Callback function: ADC group injected end of
                                        sequence conversions */
  hal_adc_awd_cb_t                      p_awd_out_window_cb;  /*!< Callback function: ADC analog watchdog out of window
                                        event */
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

#if defined(USE_HAL_ADC_GET_LAST_ERRORS) && (USE_HAL_ADC_GET_LAST_ERRORS == 1)
  volatile uint32_t last_error_codes;   /*!< Last error codes (bitfields of @ref ADC_error_codes) */
#endif /* USE_HAL_ADC_GET_LAST_ERRORS */
};

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup ADC_Exported_Functions ADC Exported Functions
  * @{
  */

/** @defgroup ADC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_ADC_Init(hal_adc_handle_t *hadc, hal_adc_t instance);
void HAL_ADC_DeInit(hal_adc_handle_t *hadc);

#if defined(ADC_INST_IN_COMMON_COUNT) && (ADC_INST_IN_COMMON_COUNT > 1)
hal_status_t HAL_ADC_SetLinkNextHandle(hal_adc_handle_t *hadc_a, hal_adc_handle_t *hadc_b);
#endif /* ADC_INST_IN_COMMON_COUNT */

#if defined(USE_HAL_ADC_DMA) && (USE_HAL_ADC_DMA == 1)
hal_status_t HAL_ADC_REG_SetDMA(hal_adc_handle_t *hadc, hal_dma_handle_t *hdma);
#endif /* USE_HAL_ADC_DMA */
/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group2_1 Configuration functions (mandatory features)
  * @{
  */
hal_status_t HAL_ADC_SetConfig(hal_adc_handle_t *hadc, const hal_adc_config_t *p_config);
void         HAL_ADC_GetConfig(const hal_adc_handle_t *hadc, hal_adc_config_t *p_config);

hal_status_t HAL_ADC_REG_SetConfig(hal_adc_handle_t *hadc, const hal_adc_reg_config_t *p_config);
void         HAL_ADC_REG_GetConfig(const hal_adc_handle_t *hadc, hal_adc_reg_config_t *p_config);

hal_status_t HAL_ADC_INJ_SetConfig(hal_adc_handle_t *hadc, const hal_adc_inj_config_t *p_config);
void         HAL_ADC_INJ_GetConfig(const hal_adc_handle_t *hadc, hal_adc_inj_config_t *p_config);

hal_status_t HAL_ADC_SetConfigChannel(hal_adc_handle_t *hadc, hal_adc_channel_t channel,
                                      const hal_adc_channel_config_t *p_config);
void HAL_ADC_GetConfigChannel(const hal_adc_handle_t *hadc, hal_adc_channel_t channel,
                              hal_adc_channel_config_t *p_config);

#if defined(ADC_MULTIMODE_SUPPORT)
hal_status_t HAL_ADC_MM_SetConfig(hal_adc_handle_t *hadc, const hal_adc_mm_config_t *p_config);
void         HAL_ADC_MM_GetConfig(const hal_adc_handle_t *hadc, hal_adc_mm_config_t *p_config);
hal_status_t HAL_ADC_MM_REG_SetMultiDMA(hal_adc_handle_t *hadc, const uint8_t *p_data, uint32_t size_byte);
#endif /* ADC_MULTIMODE_SUPPORT */
/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group2_2 Configuration functions (optional features)
  * @{
  */
hal_status_t HAL_ADC_SetConfigPostProcessing(hal_adc_handle_t *hadc, const hal_adc_post_processing_config_t *p_config);
void         HAL_ADC_GetConfigPostProcessing(const hal_adc_handle_t *hadc, hal_adc_post_processing_config_t *p_config);
hal_status_t HAL_ADC_SetConfigLowPower(hal_adc_handle_t *hadc, const hal_adc_low_power_config_t *p_config);
void         HAL_ADC_GetConfigLowPower(const hal_adc_handle_t *hadc, hal_adc_low_power_config_t *p_config);
hal_status_t HAL_ADC_SetVrefProtection(hal_adc_handle_t *hadc, hal_adc_vref_protection_t vref_protection);
hal_adc_vref_protection_t HAL_ADC_GetVrefProtection(const hal_adc_handle_t *hadc);

hal_status_t HAL_ADC_SetConfigAnalogWD(hal_adc_handle_t *hadc, hal_adc_awd_instance_t awd_instance,
                                       const hal_adc_awd_config_t *p_config);
void         HAL_ADC_GetConfigAnalogWD(const hal_adc_handle_t *hadc, hal_adc_awd_instance_t awd_instance,
                                       hal_adc_awd_config_t *p_config);
hal_status_t HAL_ADC_SetAnalogWDThresholds(hal_adc_handle_t *hadc, hal_adc_awd_instance_t awd_instance,
                                           hal_adc_awd_threshold_sel_t awd_threshold_sel, int32_t awd_threshold_value);
int32_t      HAL_ADC_GetAnalogWDThresholds(const hal_adc_handle_t *hadc, hal_adc_awd_instance_t awd_instance,
                                           hal_adc_awd_threshold_sel_t awd_threshold_sel);
hal_status_t HAL_ADC_SetAnalogWDChannel(hal_adc_handle_t *hadc, hal_adc_awd_instance_t awd_instance,
                                        hal_adc_channel_t channel);
hal_adc_channel_t HAL_ADC_GetAnalogWDChannel(const hal_adc_handle_t *hadc, hal_adc_awd_instance_t awd_instance);

hal_status_t HAL_ADC_SetConfigOverSampling(hal_adc_handle_t *hadc, hal_adc_ovs_instance_t ovs_instance,
                                           const hal_adc_ovs_config_t *p_config);
void         HAL_ADC_GetConfigOverSampling(const hal_adc_handle_t *hadc, hal_adc_ovs_instance_t ovs_instance,
                                           hal_adc_ovs_config_t *p_config);
uint32_t     HAL_ADC_GetOverSamplingShiftKeepRes(uint32_t ratio);

hal_status_t HAL_ADC_SetConfigOffset(hal_adc_handle_t *hadc,  hal_adc_offset_instance_t offset_instance,
                                     const hal_adc_offset_config_t *p_config);
void         HAL_ADC_GetConfigOffset(const hal_adc_handle_t *hadc,  hal_adc_offset_instance_t offset_instance,
                                     hal_adc_offset_config_t *p_config);
hal_status_t HAL_ADC_SetOffsetLevel(hal_adc_handle_t *hadc, hal_adc_offset_instance_t offset_instance,
                                    int32_t offset_level);
int32_t      HAL_ADC_GetOffsetLevel(const hal_adc_handle_t *hadc, hal_adc_offset_instance_t offset_instance);
/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group3 IRQHandler and Callbacks functions
  * @{
  */
void HAL_ADC_IRQHandler(hal_adc_handle_t *hadc);
void HAL_ADC_IRQHandler_REG(hal_adc_handle_t *hadc);
void HAL_ADC_IRQHandler_INJ(hal_adc_handle_t *hadc);
void HAL_ADC_IRQHandler_AWD(hal_adc_handle_t *hadc);

void HAL_ADC_ErrorCallback(hal_adc_handle_t *hadc);
void HAL_ADC_REG_EndOfSamplingCallback(hal_adc_handle_t *hadc);
void HAL_ADC_REG_UnitaryConvCpltCallback(hal_adc_handle_t *hadc);
void HAL_ADC_REG_SequenceConvCpltCallback(hal_adc_handle_t *hadc);
#if defined(USE_HAL_ADC_DMA) && (USE_HAL_ADC_DMA == 1)
void HAL_ADC_REG_DataTransferHalfCallback(hal_adc_handle_t *hadc);
void HAL_ADC_REG_DataTransferCpltCallback(hal_adc_handle_t *hadc);
void HAL_ADC_REG_DataTransferStopCallback(hal_adc_handle_t *hadc);
#endif /* USE_HAL_ADC_DMA */
void HAL_ADC_INJ_UnitaryConvCpltCallback(hal_adc_handle_t *hadc);
void HAL_ADC_INJ_SequenceConvCpltCallback(hal_adc_handle_t *hadc);
void HAL_ADC_AnalogWD_OutOfWindowCallback(hal_adc_handle_t *hadc, hal_adc_awd_instance_t awd_instance);

#if defined(USE_HAL_ADC_REGISTER_CALLBACKS) && (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
hal_status_t HAL_ADC_RegisterErrorCallback(hal_adc_handle_t *hadc, hal_adc_cb_t p_callback);
hal_status_t HAL_ADC_RegisterRegEndOfSamplingCallback(hal_adc_handle_t *hadc, hal_adc_cb_t p_callback);
hal_status_t HAL_ADC_RegisterRegUnitaryConvCpltCallback(hal_adc_handle_t *hadc, hal_adc_cb_t p_callback);
hal_status_t HAL_ADC_RegisterRegSequenceConvCpltCallback(hal_adc_handle_t *hadc, hal_adc_cb_t p_callback);
#if defined(USE_HAL_ADC_DMA) && (USE_HAL_ADC_DMA == 1)
hal_status_t HAL_ADC_RegisterDataTransferHalfCallback(hal_adc_handle_t *hadc, hal_adc_cb_t p_callback);
hal_status_t HAL_ADC_RegisterDataTransferCpltCallback(hal_adc_handle_t *hadc, hal_adc_cb_t p_callback);
hal_status_t HAL_ADC_RegisterDataTransferStopCallback(hal_adc_handle_t *hadc, hal_adc_cb_t p_callback);
#endif /* USE_HAL_ADC_DMA */
hal_status_t HAL_ADC_RegisterInjUnitaryConvCpltCallback(hal_adc_handle_t *hadc, hal_adc_cb_t p_callback);
hal_status_t HAL_ADC_RegisterInjSequenceConvCpltCallback(hal_adc_handle_t *hadc, hal_adc_cb_t p_callback);
hal_status_t HAL_ADC_RegisterAwdOutOfWindowCallback(hal_adc_handle_t *hadc, hal_adc_awd_cb_t p_callback);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group4 Peripheral State, Error functions
  * @{
  */
hal_adc_state_t HAL_ADC_GetState(const hal_adc_handle_t *hadc);
hal_adc_group_state_t HAL_ADC_GetStateGroup(const hal_adc_handle_t *hadc, hal_adc_group_t group);
hal_adc_common_state_t HAL_ADC_GetStateCommon(const hal_adc_handle_t *hadc);
#if defined(USE_HAL_ADC_GET_LAST_ERRORS) && (USE_HAL_ADC_GET_LAST_ERRORS == 1)
uint32_t HAL_ADC_GetLastErrorCodes(const hal_adc_handle_t *hadc);
#endif /* USE_HAL_ADC_GET_LAST_ERRORS */
uint32_t HAL_ADC_GetClockFreq(const hal_adc_handle_t *hadc);
/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group5 Process functions
  * @{
  */
hal_status_t HAL_ADC_Start(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_Stop(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_Calibrate(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_GetCalibrationFactor(hal_adc_handle_t *hadc, hal_adc_calib_t *p_calib);
hal_status_t HAL_ADC_SetCalibrationFactor(hal_adc_handle_t *hadc, const hal_adc_calib_t *p_calib);
hal_status_t HAL_ADC_PollForEvent(hal_adc_handle_t *hadc, hal_adc_event_t event, uint32_t timeout_ms);

hal_status_t HAL_ADC_REG_StartConv(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_REG_StartConv_IT(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_REG_StartConv_IT_Opt(hal_adc_handle_t *hadc, uint32_t it_opt);
#if defined(USE_HAL_ADC_DMA) && (USE_HAL_ADC_DMA == 1)
hal_status_t HAL_ADC_REG_StartConv_DMA(hal_adc_handle_t *hadc, const uint8_t *p_data, uint32_t size_byte);
hal_status_t HAL_ADC_REG_StartConv_DMA_Opt(hal_adc_handle_t *hadc, const uint8_t *p_data, uint32_t size_byte,
                                           uint32_t it_opt);
#endif /* USE_HAL_ADC_DMA */
hal_status_t HAL_ADC_REG_TrigNextConv(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_REG_StopConv(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_REG_StopConv_IT(hal_adc_handle_t *hadc);
#if defined(USE_HAL_ADC_DMA) && (USE_HAL_ADC_DMA == 1)
hal_status_t HAL_ADC_REG_StopConv_DMA(hal_adc_handle_t *hadc);
#endif /* USE_HAL_ADC_DMA */
hal_status_t HAL_ADC_REG_PollForConv(hal_adc_handle_t *hadc, uint32_t timeout_ms);
int32_t      HAL_ADC_REG_GetValue(const hal_adc_handle_t *hadc);

hal_status_t HAL_ADC_INJ_StartConv(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_INJ_StartConv_IT(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_INJ_StartConv_IT_Opt(hal_adc_handle_t *hadc, uint32_t it_opt);
hal_status_t HAL_ADC_INJ_TrigNextConv(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_INJ_StopConv(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_INJ_StopConv_IT(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_INJ_PollForConv(hal_adc_handle_t *hadc, uint32_t timeout_ms);
int32_t      HAL_ADC_INJ_GetValue(const hal_adc_handle_t *hadc, uint8_t sequencer_rank);

#if defined(ADC_MULTIMODE_SUPPORT)
hal_status_t HAL_ADC_MM_Start(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_MM_Stop(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_MM_Calibrate(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_MM_REG_StartConv(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_MM_REG_StartConv_IT(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_MM_REG_StartConv_IT_Opt(hal_adc_handle_t *hadc, uint32_t it_opt);
#if defined(USE_HAL_ADC_DMA) && (USE_HAL_ADC_DMA == 1)
hal_status_t HAL_ADC_MM_REG_StartConv_DMA(hal_adc_handle_t *hadc, const uint8_t *p_data, uint32_t size_byte);
hal_status_t HAL_ADC_MM_REG_StartConv_DMA_Opt(hal_adc_handle_t *hadc, const uint8_t *p_data, uint32_t size_byte,
                                              uint32_t it_opt);
hal_status_t HAL_ADC_MM_REG_StartConvM_DMA(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_MM_REG_StartConvM_DMA_Opt(hal_adc_handle_t *hadc, uint32_t it_opt);
#endif /* USE_HAL_ADC_DMA */
hal_status_t HAL_ADC_MM_REG_TrigNextConv(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_MM_REG_StopConv(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_MM_REG_StopConv_IT(hal_adc_handle_t *hadc);
#if defined(USE_HAL_ADC_DMA) && (USE_HAL_ADC_DMA == 1)
hal_status_t HAL_ADC_MM_REG_StopConv_DMA(hal_adc_handle_t *hadc);
#endif /* USE_HAL_ADC_DMA */
hal_status_t HAL_ADC_MM_REG_PollForConv(hal_adc_handle_t *hadc, uint32_t timeout_ms);
uint32_t     HAL_ADC_MM_REG_GetValue(const hal_adc_handle_t *hadc, hal_adc_mm_inst_t multi_inst);
hal_status_t HAL_ADC_MM_INJ_StartConv(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_MM_INJ_StartConv_IT(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_MM_INJ_StartConv_IT_Opt(hal_adc_handle_t *hadc, uint32_t it_opt);
hal_status_t HAL_ADC_MM_INJ_TrigNextConv(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_MM_INJ_StopConv(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_MM_INJ_StopConv_IT(hal_adc_handle_t *hadc);
hal_status_t HAL_ADC_MM_INJ_PollForConv(hal_adc_handle_t *hadc, uint32_t timeout_ms);
uint32_t     HAL_ADC_MM_INJ_GetValue(const hal_adc_handle_t *hadc, hal_adc_mm_inst_t multi_inst,
                                     uint8_t sequencer_rank);
#endif /* ADC_MULTIMODE_SUPPORT */

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group6 User data functions
  * @{
  */
#if defined(USE_HAL_ADC_USER_DATA) && (USE_HAL_ADC_USER_DATA == 1)
void HAL_ADC_SetUserData(hal_adc_handle_t *hadc, const void *p_user_data);
const void *HAL_ADC_GetUserData(const hal_adc_handle_t *hadc);
#endif /* USE_HAL_ADC_USER_DATA */
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

#endif /* STM32U5XX_HAL_ADC_H */
