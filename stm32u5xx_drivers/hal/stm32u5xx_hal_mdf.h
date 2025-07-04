/**
  ******************************************************************************
  * @file    stm32u5xx_hal_mdf.h
  * @brief   Header file of MDF HAL module.
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
#ifndef STM32U5XX_HAL_MDF_H
#define STM32U5XX_HAL_MDF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup MDF MDF
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup MDF_Exported_Constants MDF exported constants
  * @{
  */

#if defined(USE_HAL_MDF_GET_LAST_ERRORS) && (USE_HAL_MDF_GET_LAST_ERRORS == 1)
/** @defgroup MDF_Error_Codes MDF error codes
  * @{
  */
#define HAL_MDF_ERROR_NONE               (0UL)       /*!< No error */
#define HAL_MDF_ERROR_DFLT_ACQ_OVERFLOW  (1UL << 0U) /*!< Overflow occurs during acquisition */
#define HAL_MDF_ERROR_DFLT_RSF_OVERRUN   (1UL << 1U) /*!< Overrun occurs on reshape filter */
#define HAL_MDF_ERROR_SITF_CLOCK_ABSENCE (1UL << 2U) /*!< Clock absence detection occurs */
#define HAL_MDF_ERROR_SHORT_CIRCUIT      (1UL << 3U) /*!< Short circuit detection occurs */
#define HAL_MDF_ERROR_DFLT_SATURATION    (1UL << 4U) /*!< Saturation detection occurs */
#if defined (USE_HAL_MDF_DMA) && (USE_HAL_MDF_DMA == 1)
#define HAL_MDF_ERROR_DMA                (1UL << 5U) /*!< DMA error occurs */
#endif /* USE_HAL_MDF_DMA */
/**
  * @}
  */
#endif /* USE_HAL_MDF_GET_LAST_ERRORS */

/** @defgroup MDF_Break_Signals MDF break signals
  * @{
  */
#define HAL_MDF_SIGNAL_NO_BREAK    (0UL)       /*!< No break signal */
#define HAL_MDF_SIGNAL_TIM1_BREAK  (1UL << 0U) /*!< TIM1_BREAK signal */
#define HAL_MDF_SIGNAL_TIM1_BREAK2 (1UL << 1U) /*!< TIM1_BREAK2 signal */
#define HAL_MDF_SIGNAL_TIM8_BREAK  (1UL << 2U) /*!< TIM8_BREAK signal */
#define HAL_MDF_SIGNAL_TIM8_BREAK2 (1UL << 3U) /*!< TIM8_BREAK2 signal */
/**
  * @}
  */

/** @defgroup MDF_Optional_Interrupts MDF optional interrupts
  * @{
  */
#define HAL_MDF_DFLT_OPT_IT_NONE    (0U)                             /*!< No optional interrupt */
#define HAL_MDF_DFLT_OPT_IT_ACQ_OVR (1UL << 0U)                      /*!< Acquisition overflow interrupt */
#define HAL_MDF_DFLT_OPT_IT_RSF_OVR (1UL << 1U)                      /*!< Reshape filter overrun interrupt */
#define HAL_MDF_DFLT_OPT_IT_SAT     (1UL << 2U)                      /*!< Saturation interrupt */
#define HAL_MDF_DFLT_OPT_IT_ALL     (HAL_MDF_DFLT_OPT_IT_ACQ_OVR \
                                     | HAL_MDF_DFLT_OPT_IT_RSF_OVR \
                                     | HAL_MDF_DFLT_OPT_IT_SAT)      /*!< All optional interrupts */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup MDF_Exported_Types MDF exported types
  * @{
  */

/** @defgroup MDF_Exported_Types_Group1 Enumerations
  * @{
  */

/**
  * @brief HAL MDF instances definitions.
  */
typedef enum
{
  HAL_MDF1 = (uint32_t)MDF1 /*!< Peripheral instance MDF1 */
} hal_mdf_t;

/**
  * @brief HAL MDF states definitions.
  */
typedef enum
{
  HAL_MDF_STATE_RESET  = (0U),        /*!< MDF not initialized */
  HAL_MDF_STATE_INIT   = (1UL << 31U), /*!< MDF Initialized but processing clock divider not yet configured */
  HAL_MDF_STATE_IDLE   = (1UL << 30U), /*!< MDF Initialized, at least processing clock divider configured
                                           but clock generator disabled */
  HAL_MDF_STATE_ACTIVE = (1UL << 29U)  /*!< MDF clock generator enabled */
} hal_mdf_state_t;

/**
  * @brief HAL MDF output clocks definitions.
  */
typedef enum
{
  HAL_MDF_OUTPUT_CLOCK_NONE =  0U,                  /*!< MDF_CCK0 and MDF_CCK1 are used as input clocks */
  HAL_MDF_OUTPUT_CLOCK_CCK0 =  MDF_CKGCR_CCK0DIR,   /*!< Only MDF_CCK0 is used as output clock */
  HAL_MDF_OUTPUT_CLOCK_CCK1 =  MDF_CKGCR_CCK1DIR,   /*!< Only MDF_CCK1 is used as output clock */
  HAL_MDF_OUTPUT_CLOCK_ALL  = (MDF_CKGCR_CCK0DIR \
                               | MDF_CKGCR_CCK1DIR) /*!< MDF_CCK0 and MDF_CCK1 are used as output clocks */
} hal_mdf_output_clock_pins_t;

/**
  * @brief HAL MDF output clocks status definitions.
  */
typedef enum
{
  HAL_MDF_OUTPUT_CLOCK_DISABLED     = 0U, /*!< MDF_CCK0 and MDF_CCK1 output clocks disabled */
  HAL_MDF_OUTPUT_CLOCK_CCK0_ENABLED = 1U, /*!< Only MDF_CCK0 output clock enabled */
  HAL_MDF_OUTPUT_CLOCK_CCK1_ENABLED = 2U, /*!< Only MDF_CCK1 output clock enabled */
  HAL_MDF_OUTPUT_CLOCK_ALL_ENABLED  = 3U  /*!< MDF_CCK0 and MDF_CCK1 output clocks enabled */
} hal_mdf_output_clock_status_t;

/**
  * @brief HAL MDF output clock trigger sources definitions.
  */
typedef enum
{
  HAL_MDF_OUT_CLOCK_TRIG_TRGO       =  0U,                    /*!< Source is TRGO signal */
  HAL_MDF_OUT_CLOCK_TRIG_TIM1_TRGO  =  MDF_CKGCR_TRGSRC_1,    /*!< Source is TIM1_TRGO signal */
  HAL_MDF_OUT_CLOCK_TRIG_TIM1_TRGO2 = (MDF_CKGCR_TRGSRC_0 \
                                       | MDF_CKGCR_TRGSRC_1), /*!< Source is TIM1_TRGO2 signal */
  HAL_MDF_OUT_CLOCK_TRIG_TIM8_TRGO  =  MDF_CKGCR_TRGSRC_2,    /*!< Source is TIM8_TRGO signal */
  HAL_MDF_OUT_CLOCK_TRIG_TIM8_TRGO2 = (MDF_CKGCR_TRGSRC_0 \
                                       | MDF_CKGCR_TRGSRC_2), /*!< Source is TIM8_TRGO2 signal */
  HAL_MDF_OUT_CLOCK_TRIG_TIM3_TRGO  = (MDF_CKGCR_TRGSRC_1 \
                                       | MDF_CKGCR_TRGSRC_2), /*!< Source is TIM3_TRGO signal */
  HAL_MDF_OUT_CLOCK_TRIG_TIM4_TRGO  = (MDF_CKGCR_TRGSRC_0 \
                                       | MDF_CKGCR_TRGSRC_1 \
                                       | MDF_CKGCR_TRGSRC_2), /*!< Source is TIM4_TRGO signal */
  HAL_MDF_OUT_CLOCK_TRIG_TIM16_OC1  =  MDF_CKGCR_TRGSRC_3,    /*!< Source is TIM16_OC1 signal */
  HAL_MDF_OUT_CLOCK_TRIG_TIM6_TRGO  = (MDF_CKGCR_TRGSRC_0 \
                                       | MDF_CKGCR_TRGSRC_3), /*!< Source is TIM6_TRGO signal */
  HAL_MDF_OUT_CLOCK_TRIG_TIM7_TRGO  = (MDF_CKGCR_TRGSRC_1 \
                                       | MDF_CKGCR_TRGSRC_3), /*!< Source is TIM7_TRGO signal */
  HAL_MDF_OUT_CLOCK_TRIG_SAD_DET    = (MDF_CKGCR_TRGSRC_0 \
                                       | MDF_CKGCR_TRGSRC_1 \
                                       | MDF_CKGCR_TRGSRC_3), /*!< Source is SAD_DET signal */
  HAL_MDF_OUT_CLOCK_TRIG_EXTI11     = (MDF_CKGCR_TRGSRC_2 \
                                       | MDF_CKGCR_TRGSRC_3), /*!< Source is EXTI11 signal */
  HAL_MDF_OUT_CLOCK_TRIG_EXTI15     = (MDF_CKGCR_TRGSRC_0 \
                                       | MDF_CKGCR_TRGSRC_2 \
                                       | MDF_CKGCR_TRGSRC_3), /*!< Source is EXTI15 signal */
  HAL_MDF_OUT_CLOCK_TRIG_LPTIM1_OUT = (MDF_CKGCR_TRGSRC_1 \
                                       | MDF_CKGCR_TRGSRC_2 \
                                       | MDF_CKGCR_TRGSRC_3), /*!< Source is LPTIM1_OUT signal */
  HAL_MDF_OUT_CLOCK_TRIG_SAD_TRGO   =  MDF_CKGCR_TRGSRC       /*!< Source is SAD_TRGO signal */
} hal_mdf_output_clock_trigger_source_t;

/**
  * @brief HAL MDF output clock trigger edges definitions.
  */
typedef enum
{
  HAL_MDF_OUT_CLOCK_TRIG_RISING_EDGE  = 0U,               /*!< Rising edge */
  HAL_MDF_OUT_CLOCK_TRIG_FALLING_EDGE = MDF_CKGCR_TRGSENS /*!< Falling edge */
} hal_mdf_output_clock_trigger_edge_t;

/**
  * @brief HAL MDF output clock trigger status definitions.
  */
typedef enum
{
  HAL_MDF_OUT_CLOCK_TRIG_DISABLED = 0U, /*!< Output clock trigger disabled */
  HAL_MDF_OUT_CLOCK_TRIG_ENABLED  = 1U  /*!< Output clock trigger enabled */
} hal_mdf_output_clock_trigger_status_t;

/**
  * @brief HAL MDF trigger output status definitions.
  */
typedef enum
{
  HAL_MDF_TRIGGER_OUTPUT_DISABLED = 0U, /*!< Trigger output disabled */
  HAL_MDF_TRIGGER_OUTPUT_ENABLED  = 1U  /*!< Trigger output enabled */
} hal_mdf_trigger_output_status_t;

/**
  * @brief HAL MDF block indexes definitions.
  */
typedef enum
{
  HAL_MDF_BLOCK_INDEX_0 = 0U, /*!< MDF block 0 */
  HAL_MDF_BLOCK_INDEX_1 = 1U, /*!< MDF block 1 */
#if (MDF1_BLOCKS_NUMBER > 2U)
  HAL_MDF_BLOCK_INDEX_2 = 2U, /*!< MDF block 2 */
  HAL_MDF_BLOCK_INDEX_3 = 3U, /*!< MDF block 3 */
  HAL_MDF_BLOCK_INDEX_4 = 4U, /*!< MDF block 4 */
  HAL_MDF_BLOCK_INDEX_5 = 5U  /*!< MDF block 5 */
#endif /* MDF1_BLOCKS_NUMBER */
} hal_mdf_block_index_t;

/**
  * @brief HAL MDF serial interface states definitions.
  */
typedef enum
{
  HAL_MDF_SITF_STATE_RESET  = (1UL << 31U), /*!< MDF serial interface not configured */
  HAL_MDF_SITF_STATE_IDLE   = (1UL << 30U), /*!< MDF serial interface configured but not activated */
  HAL_MDF_SITF_STATE_ACTIVE = (1UL << 29U)  /*!< MDF serial interface activated */
} hal_mdf_serial_interface_state_t;

/**
  * @brief HAL MDF serial interface modes definitions.
  */
typedef enum
{
  HAL_MDF_SITF_MODE_LF_MASTER_SPI      = 0U,                   /*!< LF master SPI mode */
  HAL_MDF_SITF_MODE_NORMAL_SPI         = MDF_SITFCR_SITFMOD_0, /*!< Normal SPI mode */
  HAL_MDF_SITF_MODE_MANCHESTER_FALLING = MDF_SITFCR_SITFMOD_1, /*!< Manchester falling mode */
  HAL_MDF_SITF_MODE_MANCHESTER_RISING  = MDF_SITFCR_SITFMOD    /*!< Manchester rising mode */
} hal_mdf_serial_interface_mode_t;

/**
  * @brief HAL MDF serial interface clock sources definitions.
  */
typedef enum
{
  HAL_MDF_SITF_CLOCK_SOURCE_CCK0 = 0U,                  /*!< Common clock 0 source */
  HAL_MDF_SITF_CLOCK_SOURCE_CCK1 = MDF_SITFCR_SCKSRC_0, /*!< Common clock 1 source */
  HAL_MDF_SITF_CLOCK_SOURCE_CKI  = MDF_SITFCR_SCKSRC_1  /*!< Dedicated input clock source */
} hal_mdf_serial_interface_clock_source_t;

/**
  * @brief HAL MDF clock absence status definitions.
  */
typedef enum
{
  HAL_MDF_SITF_CKAB_NOT_DETECTED = 0U, /*!< Clock absence not detected */
  HAL_MDF_SITF_CKAB_DETECTED     = 1U  /*!< Clock absence detected */
} hal_mdf_sitf_ckab_status_t;

/**
  * @brief HAL MDF bitstream input edges definitions.
  */
typedef enum
{
  HAL_MDF_BSMX_INPUT_RISING  = 0U, /*!< Rising edge */
  HAL_MDF_BSMX_INPUT_FALLING = 1U  /*!< Falling edge */
} hal_mdf_bitstream_input_edge_t;

/**
  * @brief HAL MDF short-circuit detector states definitions.
  */
typedef enum
{
  HAL_MDF_SCD_STATE_RESET  = (1UL << 31U), /*!< MDF short-circuit detector not configured */
  HAL_MDF_SCD_STATE_IDLE   = (1UL << 30U), /*!< MDF short-circuit detector configured but not activated */
  HAL_MDF_SCD_STATE_ACTIVE = (1UL << 29U)  /*!< MDF short-circuit detector activated */
} hal_mdf_scd_state_t;

/**
  * @brief HAL MDF short-circuit detector status definitions.
  */
typedef enum
{
  HAL_MDF_SHORT_CIRCUIT_NOT_DETECTED = 0U, /*!< Short-circuit not detected */
  HAL_MDF_SHORT_CIRCUIT_DETECTED     = 1U  /*!< Short-circuit detected */
} hal_mdf_scd_status_t;

/**
  * @brief HAL MDF digital filter states definitions.
  */
typedef enum
{
  HAL_MDF_DFLT_STATE_RESET  = (1UL << 31U), /*!< MDF digital filter not configured */
  HAL_MDF_DFLT_STATE_IDLE   = (1UL << 30U), /*!< MDF digital filter configured but not activated */
  HAL_MDF_DFLT_STATE_ACTIVE = (1UL << 29U)  /*!< MDF digital filter activated */
} hal_mdf_digital_filter_state_t;

/**
  * @brief HAL MDF digital filter data sources definitions.
  */
typedef enum
{
  HAL_MDF_DFLT_DATA_SOURCE_BSMX    = 0U,                    /*!< Bitstream matrix */
  HAL_MDF_DFLT_DATA_SOURCE_ADCITF1 = MDF_DFLTCICR_DATSRC_1, /*!< ADC interface 1 */
#if defined(ADC2)
  HAL_MDF_DFLT_DATA_SOURCE_ADCITF2 = MDF_DFLTCICR_DATSRC    /*!< ADC interface 2 */
#endif /* ADC2 */
} hal_mdf_dflt_data_source_t;

/**
  * @brief HAL MDF digital filter CIC modes definitions.
  */
typedef enum
{
  HAL_MDF_DFLT_CIC_SPLIT_FASTSINC_MCIC =  0U,                       /*!< Two filters, main filter in FastSinc order */
  HAL_MDF_DFLT_CIC_SPLIT_SINC1_MCIC    =  MDF_DFLTCICR_CICMOD_0,    /*!< Two filters, main filter in Sinc1 order */
  HAL_MDF_DFLT_CIC_SPLIT_SINC2_MCIC    =  MDF_DFLTCICR_CICMOD_1,    /*!< Two filters, main filter in Sinc2 order */
  HAL_MDF_DFLT_CIC_SPLIT_SINC3_MCIC    = (MDF_DFLTCICR_CICMOD_0 \
                                          | MDF_DFLTCICR_CICMOD_1), /*!< Two filters, main filter in Sinc3 order */
  HAL_MDF_DFLT_CIC_ONE_FILTER_SINC4    =  MDF_DFLTCICR_CICMOD_2,    /*!< One filter in Sinc4 order */
  HAL_MDF_DFLT_CIC_ONE_FILTER_SINC5    = (MDF_DFLTCICR_CICMOD_0 \
                                          | MDF_DFLTCICR_CICMOD_2)  /*!< One filter in Sinc5 order */
} hal_mdf_dflt_cic_mode_t;

/**
  * @brief HAL MDF digital filter acquisition modes definitions.
  */
typedef enum
{
  HAL_MDF_DFLT_ACQ_MODE_ASYNC_CONT    =  0U,                     /*!< Asynchronous, continuous */
  HAL_MDF_DFLT_ACQ_MODE_ASYNC_SINGLE  =  MDF_DFLTCR_ACQMOD_0,    /*!< Asynchronous, single-shot */
  HAL_MDF_DFLT_ACQ_MODE_SYNC_CONT     =  MDF_DFLTCR_ACQMOD_1,    /*!< Synchronous, continuous */
  HAL_MDF_DFLT_ACQ_MODE_SYNC_SINGLE   = (MDF_DFLTCR_ACQMOD_0 \
                                         | MDF_DFLTCR_ACQMOD_1), /*!< Synchronous, single-shot */
  HAL_MDF_DFLT_ACQ_MODE_WINDOW_CONT   =  MDF_DFLTCR_ACQMOD_2,    /*!< Window, continuous */
  HAL_MDF_DFLT_ACQ_MODE_SYNC_SNAPSHOT = (MDF_DFLTCR_ACQMOD_0 \
                                         | MDF_DFLTCR_ACQMOD_2)  /*!< Synchronous, snapshot */
} hal_mdf_dflt_acquisition_mode_t;

/**
  * @brief HAL MDF digital filter trigger sources definitions.
  */
typedef enum
{
  HAL_MDF_DFLT_TRIG_TRGO        =  0U,                     /*!< Source is TRGO signal */
  HAL_MDF_DFLT_TRIG_OLD_EVENT   =  MDF_DFLTCR_TRGSRC_0,    /*!< Source is OLD event signal */
  HAL_MDF_DFLT_TRIG_TIM1_TRGO   =  MDF_DFLTCR_TRGSRC_1,    /*!< Source is TIM1_TRGO signal */
  HAL_MDF_DFLT_TRIG_TIM1_TRGO2  = (MDF_DFLTCR_TRGSRC_0 \
                                   | MDF_DFLTCR_TRGSRC_1), /*!< Source is TIM1_TRGO2 signal */
  HAL_MDF_DFLT_TRIG_TIM8_TRGO   =  MDF_DFLTCR_TRGSRC_2,    /*!< Source is TIM8_TRGO signal */
  HAL_MDF_DFLT_TRIG_TIM8_TRGO2  = (MDF_DFLTCR_TRGSRC_0 \
                                   | MDF_DFLTCR_TRGSRC_2), /*!< Source is TIM8_TRGO2 signal */
  HAL_MDF_DFLT_TRIG_TIM3_TRGO   = (MDF_DFLTCR_TRGSRC_1 \
                                   | MDF_DFLTCR_TRGSRC_2), /*!< Source is TIM3_TRGO signal */
  HAL_MDF_DFLT_TRIG_TIM4_TRGO   = (MDF_DFLTCR_TRGSRC_0 \
                                   | MDF_DFLTCR_TRGSRC_1 \
                                   | MDF_DFLTCR_TRGSRC_2), /*!< Source is TIM4_TRGO signal */
  HAL_MDF_DFLT_TRIG_TIM16_OC1   =  MDF_DFLTCR_TRGSRC_3,    /*!< Source is TIM16_OC1 signal */
  HAL_MDF_DFLT_TRIG_TIM6_TRGO   = (MDF_DFLTCR_TRGSRC_0 \
                                   | MDF_DFLTCR_TRGSRC_3), /*!< Source is TIM6_TRGO signal */
  HAL_MDF_DFLT_TRIG_TIM7_TRGO   = (MDF_DFLTCR_TRGSRC_1 \
                                   | MDF_DFLTCR_TRGSRC_3), /*!< Source is TIM7_TRGO signal */
  HAL_MDF_DFLT_TRIG_ADF_SAD_DET = (MDF_DFLTCR_TRGSRC_0 \
                                   | MDF_DFLTCR_TRGSRC_1 \
                                   | MDF_DFLTCR_TRGSRC_3), /*!< Source is ADF SAD_DET signal */
  HAL_MDF_DFLT_TRIG_EXTI11      = (MDF_DFLTCR_TRGSRC_2 \
                                   | MDF_DFLTCR_TRGSRC_3), /*!< Source is EXTI11 signal */
  HAL_MDF_DFLT_TRIG_EXTI15      = (MDF_DFLTCR_TRGSRC_0 \
                                   | MDF_DFLTCR_TRGSRC_2 \
                                   | MDF_DFLTCR_TRGSRC_3), /*!< Source is EXTI15 signal */
  HAL_MDF_DFLT_TRIG_LPTIM1_OUT  = (MDF_DFLTCR_TRGSRC_1 \
                                   | MDF_DFLTCR_TRGSRC_2 \
                                   | MDF_DFLTCR_TRGSRC_3), /*!< Source is LPTIM1_OUT signal */
  HAL_MDF_DFLT_TRIG_ADF_TRGO    =  MDF_DFLTCR_TRGSRC       /*!< Source is ADF TRGO signal */
} hal_mdf_dflt_trigger_source_t;

/**
  * @brief HAL MDF digital filter trigger edges definitions.
  */
typedef enum
{
  HAL_MDF_DFLT_TRIG_RISING_EDGE  = 0U,                /*!< Rising edge */
  HAL_MDF_DFLT_TRIG_FALLING_EDGE = MDF_DFLTCR_TRGSENS /*!< Falling edge */
} hal_mdf_dflt_trigger_edge_t;

/**
  * @brief HAL MDF digital filter integrator output division values definitions.
  */
typedef enum
{
  HAL_MDF_DLFT_INT_OUTPUT_DIV_128 = 0U,                    /*!< Integrator data outputs are divided by 128 */
  HAL_MDF_DLFT_INT_OUTPUT_DIV_32  = MDF_DFLTINTR_INTDIV_0, /*!< Integrator data outputs are divided by 32 */
  HAL_MDF_DLFT_INT_OUTPUT_DIV_4   = MDF_DFLTINTR_INTDIV_1, /*!< Integrator data outputs are divided by 4 */
  HAL_MDF_DLFT_INT_OUTPUT_NO_DIV  = MDF_DFLTINTR_INTDIV    /*!< Integrator data outputs are not divided */
} hal_mdf_dflt_int_output_division_t;

/**
  * @brief HAL MDF digital filter FIFO thresholds definitions.
  */
typedef enum
{
  HAL_MDF_DFLT_FIFO_THRESHOLD_NOT_EMPTY = 0U,            /*!< Event generated when FIFO is not empty */
  HAL_MDF_DFLT_FIFO_THRESHOLD_HALF_FULL = MDF_DFLTCR_FTH /*!< Event generated when FIFO is half-full */
} hal_mdf_dflt_fifo_threshold_t;

/**
  * @brief HAL MDF digital filter snapshot formats definitions.
  */
typedef enum
{
  HAL_MDF_DFLT_SNAPSHOT_23BITS = 0U,                /*!< Snapshot format of 23 bits */
  HAL_MDF_DFLT_SNAPSHOT_16BITS = MDF_DFLTCR_SNPSFMT /*!< Snapshot format of 16 bits */
} hal_mdf_dflt_snapshot_format_t;

/**
  * @brief HAL MDF reshape filter decimation ratios definitions.
  */
typedef enum
{
  HAL_MDF_DFLT_RSF_DR_4 = 0U,                 /*!< Reshape filter decimation ratio is 4 */
  HAL_MDF_DFLT_RSF_DR_1 = MDF_DFLTRSFR_RSFLTD /*!< Reshape filter decimation ratio is 1 */
} hal_mdf_dflt_rsf_decimation_ratio_t;

/**
  * @brief HAL MDF reshape filter status definitions.
  */
typedef enum
{
  HAL_MDF_DFLT_RSF_DISABLED = 0U, /*!< Reshape filter disabled */
  HAL_MDF_DFLT_RSF_ENABLED  = 1U  /*!< Reshape filter enabled */
} hal_mdf_dflt_rsf_status_t;

/**
  * @brief HAL MDF high-pass filter cut-off frequencies definitions.
  */
typedef enum
{
  HAL_MDF_DFLT_HPF_CUT_OFF_0_000625FPCM = 0U,                  /*!< Cut-off frequency of 0.000625xFpcm */
  HAL_MDF_DFLT_HPF_CUT_OFF_0_00125FPCM  = MDF_DFLTRSFR_HPFC_0, /*!< Cut-off frequency of 0.00125xFpcm */
  HAL_MDF_DFLT_HPF_CUT_OFF_0_0025FPCM   = MDF_DFLTRSFR_HPFC_1, /*!< Cut-off frequency of 0.0025xFpcm */
  HAL_MDF_DFLT_HPF_CUT_OFF_0_0095FPCM   = MDF_DFLTRSFR_HPFC    /*!< Cut-off frequency of 0.0095xFpcm */
} hal_mdf_dflt_hpf_cut_off_frequency_t;

/**
  * @brief HAL MDF high-pass filter status definitions.
  */
typedef enum
{
  HAL_MDF_DFLT_HPF_DISABLED = 0U, /*!< High-pass filter disabled */
  HAL_MDF_DFLT_HPF_ENABLED  = 1U  /*!< High-pass filter enabled */
} hal_mdf_dflt_hpf_status_t;

#if defined (USE_HAL_MDF_DMA) && (USE_HAL_MDF_DMA == 1)
/**
  * @brief HAL MDF DMA data resolutions definitions.
  */
typedef enum
{
  HAL_MDF_DMA_DATA_RESOLUTION_FULL     = 0U, /*!< Transfer the full 24 bits of the acquisition data */
  HAL_MDF_DMA_DATA_RESOLUTION_MSB_ONLY = 1U  /*!< Transfer only the 16 MSB of the acquisition data */
} hal_mdf_dma_data_resolution_t;
#endif /* USE_HAL_MDF_DMA */

/**
  * @brief HAL MDF out-of-limit detector states definitions.
  */
typedef enum
{
  HAL_MDF_OLD_STATE_RESET  = (1UL << 31U), /*!< MDF out-of-limit detector not configured */
  HAL_MDF_OLD_STATE_IDLE   = (1UL << 30U), /*!< MDF out-of-limit detector configured but not activated */
  HAL_MDF_OLD_STATE_ACTIVE = (1UL << 29U)  /*!< MDF out-of-limit detector activated */
} hal_mdf_old_state_t;

/**
  * @brief HAL MDF out-of-limit detector CIC orders definitions.
  */
typedef enum
{
  HAL_MDF_OLD_CIC_ORDER_FASTSINC = 0U,                /*!< Out-of-limit detector filter in FastSinc order */
  HAL_MDF_OLD_CIC_ORDER_SINC1    = MDF_OLDCR_ACICN_0, /*!< Out-of-limit detector filter in Sinc1 order */
  HAL_MDF_OLD_CIC_ORDER_SINC2    = MDF_OLDCR_ACICN_1, /*!< Out-of-limit detector filter in Sinc2 order */
  HAL_MDF_OLD_CIC_ORDER_SINC3    = MDF_OLDCR_ACICN    /*!< Out-of-limit detector filter in Sinc3 order */
} hal_mdf_old_cic_order_t;

/**
  * @brief HAL MDF out-of-limit detector event configurations definitions.
  */
typedef enum
{
  HAL_MDF_OLD_EVENT_OUTSIDE_THRESHOLDS = 0U,             /*!< Event generated when signal is outside thresholds */
  HAL_MDF_OLD_EVENT_IN_THRESHOLDS      = MDF_OLDCR_THINB /*!< Event generated when signal is in thresholds */
} hal_mdf_old_event_config_t;

/**
  * @brief HAL MDF out-of-limit detector status definitions.
  */
typedef enum
{
  HAL_MDF_OUT_OF_LIMIT_NOT_DETECTED = 0U, /*!< Out-of-limit not detected */
  HAL_MDF_OUT_OF_LIMIT_DETECTED     = 1U  /*!< Out-of-limit detected */
} hal_mdf_old_status_t;

/**
  * @brief HAL MDF out-of-limit detector threshold information definitions.
  */
typedef enum
{
  HAL_MDF_OLD_THRESHOLDS_IN  = 0U, /*!< Signal was in thresholds when out-of-limit detected */
  HAL_MDF_OLD_THRESHOLD_HIGH = 1U, /*!< Signal was higher than high threshold when out-of-limit detected */
  HAL_MDF_OLD_THRESHOLD_LOW  = 2U  /*!< Signal was lower than low threshold when out-of-limit detected */
} hal_mdf_old_threshold_info_t;

/**
  * @}
  */

/** @defgroup MDF_Exported_Types_Group2 MDF handle structure
  * @{
  */

typedef struct hal_mdf_handle_s hal_mdf_handle_t; /*!< MDF handle type definition */

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
typedef void (*hal_mdf_cb_t)(hal_mdf_handle_t *, hal_mdf_block_index_t); /*!< Pointer to generic callback */
typedef void (*hal_mdf_old_cb_t)(hal_mdf_handle_t *,
                                 hal_mdf_block_index_t,
                                 hal_mdf_old_threshold_info_t); /*!< Pointer to out-of-limit detector callback */
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */

/**
  * @brief HAL MDF handle structure definition.
  */
struct hal_mdf_handle_s
{
  /*! Peripheral instance */
  hal_mdf_t                                 instance;
  /*! Global state */
  volatile hal_mdf_state_t                  global_state;
  /*! Serial interfaces states */
  volatile hal_mdf_serial_interface_state_t serial_interface_states[MDF1_BLOCKS_NUMBER];
  /*! Short-circuit detectors states */
  volatile hal_mdf_scd_state_t              short_circuit_detect_states[MDF1_BLOCKS_NUMBER];
  /*! Digital filters states */
  volatile hal_mdf_digital_filter_state_t   digital_filter_states[MDF1_BLOCKS_NUMBER];
  /*! Out-of-limit detectors states */
  volatile hal_mdf_old_state_t              out_of_limit_detect_states[MDF1_BLOCKS_NUMBER];
#if defined (USE_HAL_MDF_GET_LAST_ERRORS) && (USE_HAL_MDF_GET_LAST_ERRORS == 1)
  /*! Errors limited to the last process. This parameter can be a combination of @ref MDF_Error_Codes */
  volatile uint32_t                         last_error_codes[MDF1_BLOCKS_NUMBER];
#endif /* USE_HAL_MDF_GET_LAST_ERRORS */
#if defined (USE_HAL_MDF_DMA) && (USE_HAL_MDF_DMA == 1)
  /*! DMA handles */
  hal_dma_handle_t                         *hdma[MDF1_BLOCKS_NUMBER];
#endif /* USE_HAL_MDF_DMA */
#if defined (USE_HAL_MDF_USER_DATA) && (USE_HAL_MDF_USER_DATA == 1)
  /*! User data pointer */
  const void                               *p_user_data;
#endif /* USE_HAL_MDF_USER_DATA */
#if defined (USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
  /*! Out-of-limit detector callback */
  hal_mdf_old_cb_t                          p_out_of_limit_detector_cb;
  /*! Acquisition complete callback */
  hal_mdf_cb_t                              p_acquisition_cplt_cb;
  /*! Acquisition half complete callback */
  hal_mdf_cb_t                              p_acquisition_half_cplt_cb;
  /*! Acquisition stop callback */
  hal_mdf_cb_t                              p_acquisition_stop_cb;
  /*! Error callback */
  hal_mdf_cb_t                              p_error_cb;
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
};

/**
  * @}
  */

/** @defgroup MDF_Exported_Types_Group3 MDF configuration structures
  * @{
  */

/**
  * @brief HAL MDF serial interface configuration structure definition.
  */
typedef struct
{
  hal_mdf_serial_interface_mode_t         mode;         /*!< Serial interface mode */
  hal_mdf_serial_interface_clock_source_t clock_source; /*!< Serial interface clock source */
  uint32_t                                threshold;    /*!< Threshold for clock absence detection or manchester symbol
                                                             threshold. This parameter must be a number between
                                                             Min_Data = 4 and Max_Data = 31 */
} hal_mdf_serial_interface_config_t;

/**
  * @brief HAL MDF digital filter trigger configuration structure definition.
  */
typedef struct
{
  hal_mdf_dflt_trigger_source_t source; /*!< Trigger source */
  hal_mdf_dflt_trigger_edge_t   edge;   /*!< Trigger edge */
} hal_mdf_dflt_trigger_config_t;

/**
  * @brief HAL MDF digital filter configuration structure definition.
  */
typedef struct
{
  hal_mdf_dflt_data_source_t      data_source;      /*!< Data source */
  hal_mdf_dflt_cic_mode_t         cic_mode;         /*!< CIC mode */
  uint32_t                        decimation_ratio; /*!< Decimation ratio. This parameter must be a number between
                                                         Min_Data = 2 and Max_Data = 512 */
  int32_t                         gain;             /*!< Gain in step of around 3db (from -48db to 72dB).
                                                         This parameter must be a number between Min_Data = -16
                                                         and Max_Data = 24 */
  hal_mdf_dflt_acquisition_mode_t acquisition_mode; /*!< Acquisition mode */
  hal_mdf_dflt_trigger_config_t   trigger;          /*!< Trigger configuration */
} hal_mdf_digital_filter_config_t;

/**
  * @brief HAL MDF out-of-limit detector configuration structure definition.
  */
typedef struct
{
  hal_mdf_old_cic_order_t    cic_order;        /*!< CIC order */
  uint32_t                   decimation_ratio; /*!< Decimation ratio. This parameter must be a number between
                                                    Min_Data = 1 and Max_Data = 32 */
  int32_t                    high_threshold;   /*!< High threshold. This parameter must be a number between
                                                    Min_Data = -33554432 and Max_Data = 33554431 */
  int32_t                    low_threshold;    /*!< Low threshold. This parameter must be a number between
                                                    Min_Data = -33554432 and Max_Data = 33554431 */
  hal_mdf_old_event_config_t event_config;     /*!< Event configuration */
  uint32_t                   break_signals;    /*!< Break signals. This parameter can be a combination
                                                    of @ref MDF_Break_Signals */
} hal_mdf_old_config_t;

#if defined (USE_HAL_MDF_DMA) && (USE_HAL_MDF_DMA == 1)
/**
  * @brief HAL MDF DMA configuration structure definition.
  */
typedef struct
{
  uint32_t                      address;          /*!< Destination address */
  uint32_t                      data_length_byte; /*!< Data length in bytes */
  hal_mdf_dma_data_resolution_t data_resolution;  /*!< Data resolution */
} hal_mdf_dma_config_t;
#endif /* USE_HAL_MDF_DMA */

/**
  * @}
  */

/** @defgroup MDF_Exported_Types_Group4 MDF parameter structures
  * @{
  */

/**
  * @brief HAL MDF snapshot parameter structure definition.
  */
typedef struct
{
  int32_t   value;               /*!< Snapshot acquisition value */
  uint32_t  decimation_counter;  /*!< Decimation counter value when snapshot trigger occurs */
  uint32_t  integrator_counter;  /*!< Integrator counter value when snapshot trigger occurs.
                                      This value is available only with snapshot format of 16 bits */
} hal_mdf_dflt_snapshot_param_t;

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup MDF_Exported_Functions MDF exported functions
  * @{
  */

/** @defgroup MDF_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_MDF_Init(hal_mdf_handle_t *hmdf, hal_mdf_t instance);
void         HAL_MDF_DeInit(hal_mdf_handle_t *hmdf);
/**
  * @}
  */

/** @defgroup MDF_Exported_Functions_Group2 Common clock generator and features functions
  * @{
  */
/* Configuration functions */
hal_status_t HAL_MDF_SetConfig(hal_mdf_handle_t *hmdf, uint32_t proc_clock_divider);
void         HAL_MDF_GetConfig(const hal_mdf_handle_t *hmdf, uint32_t *p_proc_clock_divider);

hal_status_t HAL_MDF_SetConfigOutputClock(const hal_mdf_handle_t *hmdf, hal_mdf_output_clock_pins_t pins,
                                          uint32_t output_clock_divider);
void         HAL_MDF_GetConfigOutputClock(const hal_mdf_handle_t *hmdf, hal_mdf_output_clock_pins_t *p_pins,
                                          uint32_t *p_output_clock_divider);

hal_status_t HAL_MDF_SetConfigOutputClockTrigger(const hal_mdf_handle_t *hmdf,
                                                 hal_mdf_output_clock_trigger_source_t source,
                                                 hal_mdf_output_clock_trigger_edge_t edge);
void         HAL_MDF_GetConfigOutputClockTrigger(const hal_mdf_handle_t *hmdf,
                                                 hal_mdf_output_clock_trigger_source_t *p_source,
                                                 hal_mdf_output_clock_trigger_edge_t *p_edge);

hal_status_t HAL_MDF_SetInterleavedFilters(const hal_mdf_handle_t *hmdf, uint32_t interleaved_filters);
uint32_t     HAL_MDF_GetInterleavedFilters(const hal_mdf_handle_t *hmdf);

#if defined (USE_HAL_MDF_DMA) && (USE_HAL_MDF_DMA == 1)
hal_status_t HAL_MDF_SetDMA(hal_mdf_handle_t     *hmdf,
                            hal_mdf_block_index_t block_index,
                            hal_dma_handle_t     *hdma);
#endif /* USE_HAL_MDF_DMA */

uint32_t     HAL_MDF_GetClockFreq(const hal_mdf_handle_t *hmdf);

#if defined (USE_HAL_MDF_USER_DATA) && (USE_HAL_MDF_USER_DATA == 1)
void        HAL_MDF_SetUserData(hal_mdf_handle_t *hmdf, const void *p_user_data);
const void *HAL_MDF_GetUserData(const hal_mdf_handle_t *hmdf);
#endif /* USE_HAL_SAI_USER_DATA */

#if defined(USE_HAL_MDF_GET_LAST_ERRORS) && (USE_HAL_MDF_GET_LAST_ERRORS == 1)
uint32_t     HAL_MDF_GetLastErrorCodes(const hal_mdf_handle_t *hmdf,
                                       hal_mdf_block_index_t   block_index);
#endif /* USE_HAL_MDF_GET_LAST_ERRORS */


/* Control functions */
hal_status_t                          HAL_MDF_EnableOutputClock(const hal_mdf_handle_t *hmdf,
                                                                hal_mdf_output_clock_pins_t pins);
hal_status_t                          HAL_MDF_DisableOutputClock(const hal_mdf_handle_t *hmdf,
                                                                 hal_mdf_output_clock_pins_t pins);
hal_mdf_output_clock_status_t         HAL_MDF_IsEnabledOutputClock(const hal_mdf_handle_t *hmdf);

hal_status_t                          HAL_MDF_EnableOutputClockTrigger(const hal_mdf_handle_t *hmdf);
hal_status_t                          HAL_MDF_DisableOutputClockTrigger(const hal_mdf_handle_t *hmdf);
hal_mdf_output_clock_trigger_status_t HAL_MDF_IsEnabledOutputClockTrigger(const hal_mdf_handle_t *hmdf);

hal_status_t                          HAL_MDF_EnableTriggerOutput(const hal_mdf_handle_t *hmdf);
hal_mdf_trigger_output_status_t       HAL_MDF_IsEnabledTriggerOutput(const hal_mdf_handle_t *hmdf);

/* Process functions */
hal_status_t HAL_MDF_Start(hal_mdf_handle_t *hmdf);
hal_status_t HAL_MDF_Stop(hal_mdf_handle_t *hmdf);
/**
  * @}
  */

/** @defgroup MDF_Exported_Functions_Group3 Serial interface functions
  * @{
  */
/* Configuration functions */
hal_status_t HAL_MDF_SITF_SetConfig(hal_mdf_handle_t *hmdf,
                                    hal_mdf_block_index_t serial_interface_index,
                                    const hal_mdf_serial_interface_config_t *p_config);
void         HAL_MDF_SITF_GetConfig(const hal_mdf_handle_t *hmdf,
                                    hal_mdf_block_index_t serial_interface_index,
                                    hal_mdf_serial_interface_config_t *p_config);

/* Process functions */
hal_status_t HAL_MDF_SITF_Start(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t serial_interface_index);
hal_status_t HAL_MDF_SITF_Stop(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t serial_interface_index);

/* Clock absence detection functions */
hal_mdf_sitf_ckab_status_t HAL_MDF_SITF_IsClockAbsenceDetected(const hal_mdf_handle_t *hmdf,
                                                               hal_mdf_block_index_t serial_interface_index);

hal_status_t HAL_MDF_SITF_StartClockAbsenceDetect_IT(const hal_mdf_handle_t *hmdf,
                                                     hal_mdf_block_index_t serial_interface_index);
hal_status_t HAL_MDF_SITF_StopClockAbsenceDetect_IT(const hal_mdf_handle_t *hmdf,
                                                    hal_mdf_block_index_t serial_interface_index);
/**
  * @}
  */

/** @defgroup MDF_Exported_Functions_Group4 Bitstream matrix functions
  * @{
  */
/* Configuration functions */
hal_status_t HAL_MDF_BSMX_SetConfig(const hal_mdf_handle_t *hmdf,
                                    hal_mdf_block_index_t bitstream_matrix_index,
                                    hal_mdf_block_index_t serial_interface_index,
                                    hal_mdf_bitstream_input_edge_t edge);
void         HAL_MDF_BSMX_GetConfig(const hal_mdf_handle_t *hmdf,
                                    hal_mdf_block_index_t bitstream_matrix_index,
                                    hal_mdf_block_index_t *p_serial_interface_index,
                                    hal_mdf_bitstream_input_edge_t *p_edge);
/**
  * @}
  */

/** @defgroup MDF_Exported_Functions_Group5 Short-circuit detector functions
  * @{
  */
/* Configuration functions */
hal_status_t HAL_MDF_SCD_SetConfig(hal_mdf_handle_t *hmdf,
                                   hal_mdf_block_index_t short_circuit_detector_index,
                                   uint32_t threshold,
                                   uint32_t break_signals);
void         HAL_MDF_SCD_GetConfig(const hal_mdf_handle_t *hmdf,
                                   hal_mdf_block_index_t short_circuit_detector_index,
                                   uint32_t *p_threshold,
                                   uint32_t *p_break_signals);

/* Process functions */
hal_status_t HAL_MDF_SCD_Start(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t short_circuit_detector_index);
hal_status_t HAL_MDF_SCD_Stop(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t short_circuit_detector_index);
hal_status_t HAL_MDF_SCD_Start_IT(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t short_circuit_detector_index);
hal_status_t HAL_MDF_SCD_Stop_IT(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t short_circuit_detector_index);

/* Control functions */
hal_mdf_scd_status_t HAL_MDF_SCD_IsDetected(const hal_mdf_handle_t *hmdf,
                                            hal_mdf_block_index_t short_circuit_detector_index);
/**
  * @}
  */

/** @defgroup MDF_Exported_Functions_Group6 Digital filter functions
  * @{
  */
/* Configuration functions */
hal_status_t HAL_MDF_DFLT_SetConfig(hal_mdf_handle_t *hmdf,
                                    hal_mdf_block_index_t digital_filter_index,
                                    const hal_mdf_digital_filter_config_t *p_config);
void         HAL_MDF_DFLT_GetConfig(const hal_mdf_handle_t *hmdf,
                                    hal_mdf_block_index_t digital_filter_index,
                                    hal_mdf_digital_filter_config_t *p_config);

hal_status_t HAL_MDF_DFLT_SetSamplesDelay(const hal_mdf_handle_t *hmdf,
                                          hal_mdf_block_index_t digital_filter_index,
                                          uint32_t samples_delay);
uint32_t     HAL_MDF_DFLT_GetSamplesDelay(const hal_mdf_handle_t *hmdf,
                                          hal_mdf_block_index_t digital_filter_index);

hal_status_t HAL_MDF_DFLT_SetOffsetCompensation(const hal_mdf_handle_t *hmdf,
                                                hal_mdf_block_index_t digital_filter_index,
                                                int32_t offset_compensation);
int32_t      HAL_MDF_DFLT_GetOffsetCompensation(const hal_mdf_handle_t *hmdf,
                                                hal_mdf_block_index_t digital_filter_index);

hal_status_t HAL_MDF_DFLT_SetGain(const hal_mdf_handle_t *hmdf,
                                  hal_mdf_block_index_t digital_filter_index,
                                  int32_t gain);
int32_t      HAL_MDF_DFLT_GetGain(const hal_mdf_handle_t *hmdf,
                                  hal_mdf_block_index_t digital_filter_index);

hal_status_t HAL_MDF_DFLT_SetIntegrator(const hal_mdf_handle_t *hmdf,
                                        hal_mdf_block_index_t digital_filter_index,
                                        uint32_t value,
                                        hal_mdf_dflt_int_output_division_t output_division);
void         HAL_MDF_DFLT_GetIntegrator(const hal_mdf_handle_t *hmdf,
                                        hal_mdf_block_index_t digital_filter_index,
                                        uint32_t *p_value,
                                        hal_mdf_dflt_int_output_division_t *p_output_division);

hal_status_t                  HAL_MDF_DFLT_SetFifoThreshold(const hal_mdf_handle_t *hmdf,
                                                            hal_mdf_block_index_t digital_filter_index,
                                                            hal_mdf_dflt_fifo_threshold_t fifo_threshold);
hal_mdf_dflt_fifo_threshold_t HAL_MDF_DFLT_GetFifoThreshold(const hal_mdf_handle_t *hmdf,
                                                            hal_mdf_block_index_t digital_filter_index);

hal_status_t HAL_MDF_DFLT_SetDiscardSamples(const hal_mdf_handle_t *hmdf,
                                            hal_mdf_block_index_t digital_filter_index,
                                            uint32_t discard_samples);
uint32_t     HAL_MDF_DFLT_GetDiscardSamples(const hal_mdf_handle_t *hmdf,
                                            hal_mdf_block_index_t digital_filter_index);

hal_status_t                   HAL_MDF_DFLT_SetSnapshotFormat(const hal_mdf_handle_t *hmdf,
                                                              hal_mdf_block_index_t digital_filter_index,
                                                              hal_mdf_dflt_snapshot_format_t snapshot_format);
hal_mdf_dflt_snapshot_format_t HAL_MDF_DFLT_GetSnapshotFormat(const hal_mdf_handle_t *hmdf,
                                                              hal_mdf_block_index_t digital_filter_index);

/* Control functions */
hal_status_t HAL_MDF_DFLT_EnableReshapeFilter(const hal_mdf_handle_t *hmdf,
                                              hal_mdf_block_index_t digital_filter_index,
                                              hal_mdf_dflt_rsf_decimation_ratio_t decimation_ratio);
hal_status_t HAL_MDF_DFLT_DisableReshapeFilter(const hal_mdf_handle_t *hmdf,
                                               hal_mdf_block_index_t digital_filter_index);
hal_mdf_dflt_rsf_status_t HAL_MDF_DFLT_IsEnabledReshapeFilter(const hal_mdf_handle_t *hmdf,
                                                              hal_mdf_block_index_t digital_filter_index);
hal_mdf_dflt_rsf_decimation_ratio_t HAL_MDF_DFLT_GetReshapeFilterDecimationRatio(const hal_mdf_handle_t *hmdf,
    hal_mdf_block_index_t digital_filter_index);

hal_status_t HAL_MDF_DFLT_EnableHighPassFilter(const hal_mdf_handle_t *hmdf,
                                               hal_mdf_block_index_t digital_filter_index,
                                               hal_mdf_dflt_hpf_cut_off_frequency_t cut_off_frequency);
hal_status_t HAL_MDF_DFLT_DisableHighPassFilter(const hal_mdf_handle_t *hmdf,
                                                hal_mdf_block_index_t digital_filter_index);
hal_mdf_dflt_hpf_status_t HAL_MDF_DFLT_IsEnabledHighPassFilter(const hal_mdf_handle_t *hmdf,
                                                               hal_mdf_block_index_t digital_filter_index);
hal_mdf_dflt_hpf_cut_off_frequency_t HAL_MDF_DFLT_GetHighPassFilterCutOffFrequency(const hal_mdf_handle_t *hmdf,
    hal_mdf_block_index_t digital_filter_index);

/* Process functions */
hal_status_t HAL_MDF_DFLT_StartAcq(hal_mdf_handle_t *hmdf,
                                   hal_mdf_block_index_t digital_filter_index);
hal_status_t HAL_MDF_DFLT_StopAcq(hal_mdf_handle_t *hmdf,
                                  hal_mdf_block_index_t digital_filter_index);
hal_status_t HAL_MDF_DFLT_PollForAcq(hal_mdf_handle_t *hmdf,
                                     hal_mdf_block_index_t digital_filter_index,
                                     uint32_t timeout_ms);
int32_t      HAL_MDF_DFLT_GetAcqValue(const hal_mdf_handle_t *hmdf,
                                      hal_mdf_block_index_t digital_filter_index);
hal_status_t HAL_MDF_DFLT_PollForSnapshotAcq(const hal_mdf_handle_t *hmdf,
                                             hal_mdf_block_index_t digital_filter_index,
                                             uint32_t timeout_ms);
void         HAL_MDF_DFLT_GetSnapshotAcqValue(const hal_mdf_handle_t *hmdf,
                                              hal_mdf_block_index_t digital_filter_index,
                                              hal_mdf_dflt_snapshot_param_t *p_snapshot_param);

hal_status_t HAL_MDF_DFLT_StartAcq_IT(hal_mdf_handle_t *hmdf,
                                      hal_mdf_block_index_t digital_filter_index);
hal_status_t HAL_MDF_DFLT_StopAcq_IT(hal_mdf_handle_t *hmdf,
                                     hal_mdf_block_index_t digital_filter_index);
hal_status_t HAL_MDF_DFLT_StartAcq_IT_Opt(hal_mdf_handle_t *hmdf,
                                          hal_mdf_block_index_t digital_filter_index,
                                          uint32_t interruptions);

#if defined (USE_HAL_MDF_DMA) && (USE_HAL_MDF_DMA == 1)
hal_status_t HAL_MDF_DFLT_StartAcq_DMA(hal_mdf_handle_t *hmdf,
                                       hal_mdf_block_index_t digital_filter_index,
                                       const hal_mdf_dma_config_t *p_dma_config);
hal_status_t HAL_MDF_DFLT_StopAcq_DMA(hal_mdf_handle_t *hmdf,
                                      hal_mdf_block_index_t digital_filter_index);
hal_status_t HAL_MDF_DFLT_StartAcq_DMA_Opt(hal_mdf_handle_t *hmdf,
                                           hal_mdf_block_index_t digital_filter_index,
                                           const hal_mdf_dma_config_t *p_dma_config,
                                           uint32_t interruptions);
#endif /* USE_HAL_MDF_DMA */
/**
  * @}
  */

/** @defgroup MDF_Exported_Functions_Group7 Out-of-limit detector functions
  * @{
  */
/* Configuration functions */
hal_status_t HAL_MDF_OLD_SetConfig(hal_mdf_handle_t *hmdf,
                                   hal_mdf_block_index_t out_of_limit_detector_index,
                                   const hal_mdf_old_config_t *p_config);
void         HAL_MDF_OLD_GetConfig(const hal_mdf_handle_t *hmdf,
                                   hal_mdf_block_index_t out_of_limit_detector_index,
                                   hal_mdf_old_config_t *p_config);

/* Process functions */
hal_status_t HAL_MDF_OLD_Start(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t out_of_limit_detector_index);
hal_status_t HAL_MDF_OLD_Stop(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t out_of_limit_detector_index);
hal_status_t HAL_MDF_OLD_Start_IT(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t out_of_limit_detector_index);
hal_status_t HAL_MDF_OLD_Stop_IT(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t out_of_limit_detector_index);

/* Control functions */
hal_mdf_old_status_t HAL_MDF_OLD_IsDetected(const hal_mdf_handle_t *hmdf,
                                            hal_mdf_block_index_t out_of_limit_detector_index,
                                            hal_mdf_old_threshold_info_t *p_threshold_info);
/**
  * @}
  */

/** @defgroup MDF_Exported_Functions_Group8 IRQ handler and callback functions
  * @{
  */
void HAL_MDF_IRQHandler(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t block_index);
void HAL_MDF_DFLT_AcqCpltCallback(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t digital_filter_index);
void HAL_MDF_DFLT_AcqHalfCpltCallback(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t digital_filter_index);
void HAL_MDF_DFLT_AcqStopCpltCallback(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t digital_filter_index);
void HAL_MDF_OLD_Callback(hal_mdf_handle_t *hmdf,
                          hal_mdf_block_index_t out_of_limit_detector_index,
                          hal_mdf_old_threshold_info_t threshold_info);
void HAL_MDF_ErrorCallback(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t block_index);

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
hal_status_t HAL_MDF_DFLT_RegisterAcqCpltCallback(hal_mdf_handle_t *hmdf, hal_mdf_cb_t p_callback);
hal_status_t HAL_MDF_DFLT_RegisterAcqHalfCpltCallback(hal_mdf_handle_t *hmdf, hal_mdf_cb_t p_callback);
hal_status_t HAL_MDF_DFLT_RegisterAcqStopCpltCallback(hal_mdf_handle_t *hmdf, hal_mdf_cb_t p_callback);
hal_status_t HAL_MDF_OLD_RegisterCallback(hal_mdf_handle_t *hmdf, hal_mdf_old_cb_t p_callback);
hal_status_t HAL_MDF_RegisterErrorCallback(hal_mdf_handle_t *hmdf, hal_mdf_cb_t p_callback);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup MDF_Exported_Functions_Group9 State functions
  * @{
  */
hal_mdf_state_t HAL_MDF_GetState(const hal_mdf_handle_t *hmdf);

hal_mdf_serial_interface_state_t HAL_MDF_SITF_GetState(const hal_mdf_handle_t *hmdf,
                                                       hal_mdf_block_index_t serial_interface_index);

hal_mdf_scd_state_t HAL_MDF_SCD_GetState(const hal_mdf_handle_t *hmdf,
                                         hal_mdf_block_index_t short_circuit_detector_index);

hal_mdf_digital_filter_state_t HAL_MDF_DFLT_GetState(const hal_mdf_handle_t *hmdf,
                                                     hal_mdf_block_index_t digital_filter_index);

hal_mdf_old_state_t HAL_MDF_OLD_GetState(const hal_mdf_handle_t *hmdf,
                                         hal_mdf_block_index_t out_of_limit_detector_index);
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

#endif /* STM32U5XX_HAL_MDF_H */
