/**
  ******************************************************************************
  * @file    stm32u5xx_ll_tsc.h
  * @brief   Header file of TSC LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************

    Table 1. IOs for the STM32U5xx devices
    +--------------------------------+
    |       IOs    |   TSC functions |
    |--------------|-----------------|
    |   PB12 (AF9) |   TSC_G1_IO1    |
    |   PB13 (AF9) |   TSC_G1_IO2    |
    |   PB14 (AF9) |   TSC_G1_IO3    |
    |   PC3 (AF9)  |   TSC_G1_IO4    |
    |--------------|-----------------|
    |   PB4 (AF9)  |   TSC_G2_IO1    |
    |   PB5 (AF9)  |   TSC_G2_IO2    |
    |   PB6 (AF9)  |   TSC_G2_IO3    |
    |   PB7 (AF9)  |   TSC_G2_IO4    |
    |--------------|-----------------|
    |   PC2 (AF9)  |   TSC_G3_IO1    |
    |   PC10 (AF9) |   TSC_G3_IO2    |
    |   PC11 (AF9) |   TSC_G3_IO3    |
    |   PC12 (AF9) |   TSC_G3_IO4    |
    |--------------|-----------------|
    |   PC6 (AF9)  |   TSC_G4_IO1    |
    |   PC7 (AF9)  |   TSC_G4_IO2    |
    |   PC8 (AF9)  |   TSC_G4_IO3    |
    |   PC9 (AF9)  |   TSC_G4_IO4    |
    |--------------|-----------------|
    |   PE10 (AF9) |   TSC_G5_IO1    |
    |   PE11 (AF9) |   TSC_G5_IO2    |
    |   PE12 (AF9) |   TSC_G5_IO3    |
    |   PE13 (AF9) |   TSC_G5_IO4    |
    |--------------|-----------------|
    |   PD10 (AF9) |   TSC_G6_IO1    |
    |   PD11 (AF9) |   TSC_G6_IO2    |
    |   PD12 (AF9) |   TSC_G6_IO3    |
    |   PD13 (AF9) |   TSC_G6_IO4    |
    |--------------|-----------------|
    |   PE2 (AF9)  |   TSC_G7_IO1    |
    |   PE3 (AF9)  |   TSC_G7_IO2    |
    |   PE4 (AF9)  |   TSC_G7_IO3    |
    |   PE5 (AF9)  |   TSC_G7_IO4    |
    |--------------|-----------------|
    |   PF14 (AF9) |   TSC_G8_IO1    |
    |   PF15 (AF9) |   TSC_G8_IO2    |
    |   PG0 (AF9)  |   TSC_G8_IO3    |
    |   PG1 (AF9)  |   TSC_G8_IO4    |
    |--------------|-----------------|
    |   PB10 (AF9) |   TSC_SYNC      |
    |   PD2 (AF9)  |                 |
    +--------------------------------+

  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5XX_LL_TSC_H
#define STM32U5XX_LL_TSC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"


/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

/** @defgroup TSC_LL TSC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
#if defined(TSC_IOCCR_G8_IO1)
#define  TSC_NB_OF_GROUPS  (8U)
#else
#define  TSC_NB_OF_GROUPS  (7U)
#endif /* TSC_IOCCR_G8_IO1 */

/* Private functions ---------------------------------------------------------*/
/** @defgroup TSC_LL_Private_Functions TSC Private Functions
  * @{
  */

/**
  * @brief  Utility function used to set the acquired groups mask.
  * @param  iomask Channels IOs mask
  * @retval Acquired groups mask
  */
static uint32_t TSC_extract_groups(uint32_t iomask)
{
  uint32_t groups = 0UL;
  uint32_t idx;

  for (idx = 0UL; idx < (uint32_t)TSC_NB_OF_GROUPS; idx++)
  {
    if ((iomask & (0x0FUL << (idx * 4UL))) != 0UL)
    {
      groups |= (1UL << idx);
    }
  }

  return groups;
}
/**
  * @}
  */
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup TSC_LL_Exported_Constants TSC Exported Constants
  * @{
  */

/** @defgroup TSC_LL_EC_Acquisition_Mode TSC Acquisition Mode
  * @{
  */
/** Normal acquisition mode (acquisition starts as soon as START bit is set) */
#define LL_TSC_ACQ_MODE_NORMAL     0x00000000UL
/** Synchronized acquisition mode (acquisition starts if START bit is set and
     when the selected signal is detected on the SYNC input pin) */
#define LL_TSC_ACQ_MODE_SYNCHRO    TSC_CR_AM
/**
  * @}
  */

/** @defgroup TSC_LL_EC_Synchro_Pin_Polarity TSC Synchro Pin Polarity
  * @{
  */
#define LL_TSC_SYNC_POLARITY_FALLING  0x00000000UL   /*!< Falling edge only          */
#define LL_TSC_SYNC_POLARITY_RISING   TSC_CR_SYNCPOL /*!< Rising edge and high level */
/**
  * @}
  */

/** @defgroup TSC_LL_EC_IO_Default_Mode TSC IO Default Mode
  * @{
  */
#define LL_TSC_IODEF_OUT_PP_LOW    0x00000000UL /*!< I/Os are forced to output push-pull low */
#define LL_TSC_IODEF_IN_FLOAT      TSC_CR_IODEF /*!< I/Os are in input floating              */
/**
  * @}
  */

/** @defgroup TSC_LL_EC_Max_Count_Value TSC Max Count Value
  * @{
  */
/** 255 maximum number of charge transfer pulses   */
#define LL_TSC_MAX_COUNT_VALUE_255     0x00000000UL
/** 511 maximum number of charge transfer pulses   */
#define LL_TSC_MAX_COUNT_VALUE_511     TSC_CR_MCV_0
/** 1023 maximum number of charge transfer pulses  */
#define LL_TSC_MAX_COUNT_VALUE_1023    TSC_CR_MCV_1
/** 2047 maximum number of charge transfer pulses  */
#define LL_TSC_MAX_COUNT_VALUE_2047    (TSC_CR_MCV_1 | TSC_CR_MCV_0)
/** 4095 maximum number of charge transfer pulses  */
#define LL_TSC_MAX_COUNT_VALUE_4095    TSC_CR_MCV_2
/** 8191 maximum number of charge transfer pulses  */
#define LL_TSC_MAX_COUNT_VALUE_8191    (TSC_CR_MCV_2 | TSC_CR_MCV_0)
/** 16383 maximum number of charge transfer pulses */
#define LL_TSC_MAX_COUNT_VALUE_16383   (TSC_CR_MCV_2 | TSC_CR_MCV_1)
/**
  * @}
  */

/** @defgroup TSC_LL_EC_Pulse_Generator_Prescaler TSC Pulse Generator Prescaler
  * @{
  */
/** Pulse Generator HCLK Div1   */
#define LL_TSC_PULSE_GEN_PRESCALER_DIV1       0x00000000UL
/** Pulse Generator HCLK Div2   */
#define LL_TSC_PULSE_GEN_PRESCALER_DIV2       TSC_CR_PGPSC_0
/** Pulse Generator HCLK Div4   */
#define LL_TSC_PULSE_GEN_PRESCALER_DIV4       TSC_CR_PGPSC_1
/** Pulse Generator HCLK Div8   */
#define LL_TSC_PULSE_GEN_PRESCALER_DIV8       (TSC_CR_PGPSC_1 | TSC_CR_PGPSC_0)
/** Pulse Generator HCLK Div16  */
#define LL_TSC_PULSE_GEN_PRESCALER_DIV16      TSC_CR_PGPSC_2
/** Pulse Generator HCLK Div32  */
#define LL_TSC_PULSE_GEN_PRESCALER_DIV32      (TSC_CR_PGPSC_2 | TSC_CR_PGPSC_0)
/** Pulse Generator HCLK Div64  */
#define LL_TSC_PULSE_GEN_PRESCALER_DIV64      (TSC_CR_PGPSC_2 | TSC_CR_PGPSC_1)
/** Pulse Generator HCLK Div128 */
#define LL_TSC_PULSE_GEN_PRESCALER_DIV128     (TSC_CR_PGPSC_2 | TSC_CR_PGPSC_1 | TSC_CR_PGPSC_0)
/**
  * @}
  */

/** @defgroup TSC_LL_EC_Spread_Spectrum TSC Spread Spectrum
  * @{
  */
#define  LL_TSC_SPREAD_SPECTRUM_ENABLE       1UL /*!< Spread Spectrum Enable  */
#define  LL_TSC_SPREAD_SPECTRUM_DISABLE      0UL /*!< Spread Spectrum Disable */
/**
  * @}
  */

/** @defgroup TSC_LL_EC_Charge_Transfer_Pulse_High TSC Charge Transfer Pulse High
  * @{
  */
/** Charge transfer pulse high during 1 cycle (PGCLK)   */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_1CYCLE   0x00000000UL
/** Charge transfer pulse high during 2 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_2CYCLES  TSC_CR_CTPH_0
/** Charge transfer pulse high during 3 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_3CYCLES  TSC_CR_CTPH_1
/** Charge transfer pulse high during 4 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_4CYCLES  (TSC_CR_CTPH_1 | TSC_CR_CTPH_0)
/** Charge transfer pulse high during 5 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_5CYCLES  TSC_CR_CTPH_2
/** Charge transfer pulse high during 6 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_6CYCLES  (TSC_CR_CTPH_2 | TSC_CR_CTPH_0)
/** Charge transfer pulse high during 7 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_7CYCLES  (TSC_CR_CTPH_2 | TSC_CR_CTPH_1)
/** Charge transfer pulse high during 8 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_8CYCLES  (TSC_CR_CTPH_2 | TSC_CR_CTPH_1 | TSC_CR_CTPH_0)
/** Charge transfer pulse high during 9 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_9CYCLES  TSC_CR_CTPH_3
/** Charge transfer pulse high during 10 cycles (PGCLK) */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_10CYCLES (TSC_CR_CTPH_3 | TSC_CR_CTPH_0)
/** Charge transfer pulse high during 11 cycles (PGCLK) */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_11CYCLES (TSC_CR_CTPH_3 | TSC_CR_CTPH_1)
/** Charge transfer pulse high during 12 cycles (PGCLK) */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_12CYCLES (TSC_CR_CTPH_3 | TSC_CR_CTPH_1 | TSC_CR_CTPH_0)
/** Charge transfer pulse high during 13 cycles (PGCLK) */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_13CYCLES (TSC_CR_CTPH_3 | TSC_CR_CTPH_2)
/** Charge transfer pulse high during 14 cycles (PGCLK) */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_14CYCLES (TSC_CR_CTPH_3 | TSC_CR_CTPH_2 | TSC_CR_CTPH_0)
/** Charge transfer pulse high during 15 cycles (PGCLK) */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_15CYCLES (TSC_CR_CTPH_3 | TSC_CR_CTPH_2 | TSC_CR_CTPH_1)
/** Charge transfer pulse high during 16 cycles (PGCLK) */
#define LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_16CYCLES (TSC_CR_CTPH_3 | TSC_CR_CTPH_2 | TSC_CR_CTPH_1 | TSC_CR_CTPH_0)
/**
  * @}
  */

/** @defgroup TSC_LL_EC_Charge_Transfer_Pulse_Low TSC Charge Transfer Pulse Low
  * @{
  */
/** Charge transfer pulse low during 1 cycle (PGCLK)   */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_1CYCLE         0x00000000UL
/** Charge transfer pulse low during 2 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_2CYCLES        TSC_CR_CTPL_0
/** Charge transfer pulse low during 3 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_3CYCLES        TSC_CR_CTPL_1
/** Charge transfer pulse low during 4 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_4CYCLES        (TSC_CR_CTPL_1 | TSC_CR_CTPL_0)
/** Charge transfer pulse low during 5 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_5CYCLES        TSC_CR_CTPL_2
/** Charge transfer pulse low during 6 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_6CYCLES        (TSC_CR_CTPL_2 | TSC_CR_CTPL_0)
/** Charge transfer pulse low during 7 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_7CYCLES        (TSC_CR_CTPL_2 | TSC_CR_CTPL_1)
/** Charge transfer pulse low during 8 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_8CYCLES        (TSC_CR_CTPL_2 | TSC_CR_CTPL_1 | TSC_CR_CTPL_0)
/** Charge transfer pulse low during 9 cycles (PGCLK)  */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_9CYCLES        TSC_CR_CTPL_3
/** Charge transfer pulse low during 10 cycles (PGCLK) */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_10CYCLES       (TSC_CR_CTPL_3 | TSC_CR_CTPL_0)
/** Charge transfer pulse low during 11 cycles (PGCLK) */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_11CYCLES       (TSC_CR_CTPL_3 | TSC_CR_CTPL_1)
/** Charge transfer pulse low during 12 cycles (PGCLK) */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_12CYCLES       (TSC_CR_CTPL_3 | TSC_CR_CTPL_1 | TSC_CR_CTPL_0)
/** Charge transfer pulse low during 13 cycles (PGCLK) */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_13CYCLES       (TSC_CR_CTPL_3 | TSC_CR_CTPL_2)
/** Charge transfer pulse low during 14 cycles (PGCLK) */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_14CYCLES       (TSC_CR_CTPL_3 | TSC_CR_CTPL_2 | TSC_CR_CTPL_0)
/** Charge transfer pulse low during 15 cycles (PGCLK) */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_15CYCLES       (TSC_CR_CTPL_3 | TSC_CR_CTPL_2 | TSC_CR_CTPL_1)
/** Charge transfer pulse low during 16 cycles (PGCLK) */
#define LL_TSC_CHARGE_TRANSFER_PULSE_LOW_16CYCLES       (TSC_CR_CTPL_3 | TSC_CR_CTPL_2 | TSC_CR_CTPL_1 | TSC_CR_CTPL_0)
/**
  * @}
  */

/** @defgroup TSC_LL_EC_Interrupt TSC Interrupts
  * @{
  */
#define LL_TSC_IT_EOA              TSC_IER_EOAIE /*!< End of acquisition interrupt enable */
#define LL_TSC_IT_MCE              TSC_IER_MCEIE /*!< Max count error interrupt enable    */
/**
  * @}
  */

/** @defgroup TSC_LL_EC_Flags TSC Flags
  * @{
  */
#define LL_TSC_FLAG_EOA            TSC_ISR_EOAF /*!< End of acquisition flag */
#define LL_TSC_FLAG_MCE            TSC_ISR_MCEF /*!< Max count error flag    */
/**
  * @}
  */

/** @defgroup TSC_LL_EC_Group_Index TSC Group Index
  * @{
  */
#define  LL_TSC_GROUP1_IDX          (0x00UL) /*!< TSC Group1 index */
#define  LL_TSC_GROUP2_IDX          (0x01UL) /*!< TSC Group2 index */
#define  LL_TSC_GROUP3_IDX          (0x02UL) /*!< TSC Group3 index */
#define  LL_TSC_GROUP4_IDX          (0x03UL) /*!< TSC Group4 index */
#define  LL_TSC_GROUP5_IDX          (0x04UL) /*!< TSC Group5 index */
#define  LL_TSC_GROUP6_IDX          (0x05UL) /*!< TSC Group6 index */
#define  LL_TSC_GROUP7_IDX          (0x06UL) /*!< TSC Group7 index */
#if defined(TSC_IOCCR_G8_IO1)
#define  LL_TSC_GROUP8_IDX          (0x07UL) /*!< TSC Group8 index */
#endif /* TSC_IOCCR_G8_IO1 */
/**
  * @}
  */

/** @defgroup TSC_LL_EC_Groups TSC Groups
  * @{
  */
#define LL_TSC_GROUP1               (0x1UL << LL_TSC_GROUP1_IDX) /*!< TSC Group1 */
#define LL_TSC_GROUP2               (0x1UL << LL_TSC_GROUP2_IDX) /*!< TSC Group2 */
#define LL_TSC_GROUP3               (0x1UL << LL_TSC_GROUP3_IDX) /*!< TSC Group3 */
#define LL_TSC_GROUP4               (0x1UL << LL_TSC_GROUP4_IDX) /*!< TSC Group4 */
#define LL_TSC_GROUP5               (0x1UL << LL_TSC_GROUP5_IDX) /*!< TSC Group5 */
#define LL_TSC_GROUP6               (0x1UL << LL_TSC_GROUP6_IDX) /*!< TSC Group6 */
#define LL_TSC_GROUP7               (0x1UL << LL_TSC_GROUP7_IDX) /*!< TSC Group7 */
#if defined(TSC_IOCCR_G8_IO1)
#define LL_TSC_GROUP8               (0x1UL << LL_TSC_GROUP8_IDX) /*!< TSC Group8 */
#endif /* TSC_IOCCR_G8_IO1 */

#define LL_TSC_GROUPX_NOT_SUPPORTED 0xFF000000UL                 /*!< TSC GroupX not supported */
/**
  * @}
  */

/** @defgroup TSC_LL_EC_Groups_IOs TSC Groups IOs
  * @{
  */
#define LL_TSC_GROUP1_IO1           TSC_IOCCR_G1_IO1             /*!< TSC Group1 IO1 */
#define LL_TSC_GROUP1_IO2           TSC_IOCCR_G1_IO2             /*!< TSC Group1 IO2 */
#define LL_TSC_GROUP1_IO3           TSC_IOCCR_G1_IO3             /*!< TSC Group1 IO3 */
#if defined(TSC_IOCCR_G1_IO4)
#define LL_TSC_GROUP1_IO4           TSC_IOCCR_G1_IO4             /*!< TSC Group1 IO4 */
#else
#define LL_TSC_GROUP1_IO4           LL_TSC_GROUPX_NOT_SUPPORTED  /*!< TSC Group1 IO4 not supported */
#endif /* TSC_IOCCR_G1_IO4 */

#define LL_TSC_GROUP2_IO1           TSC_IOCCR_G2_IO1             /*!< TSC Group2 IO1 */
#define LL_TSC_GROUP2_IO2           TSC_IOCCR_G2_IO2             /*!< TSC Group2 IO2 */
#define LL_TSC_GROUP2_IO3           TSC_IOCCR_G2_IO3             /*!< TSC Group2 IO3 */
#define LL_TSC_GROUP2_IO4           TSC_IOCCR_G2_IO4             /*!< TSC Group2 IO4 */

#if defined(TSC_IOCCR_G3_IO1)
#define LL_TSC_GROUP3_IO1           TSC_IOCCR_G3_IO1             /*!< TSC Group3 IO1 */
#else
#define LL_TSC_GROUP3_IO1           LL_TSC_GROUPX_NOT_SUPPORTED  /*!< TSC Group3 IO1 not supported */
#endif /* TSC_IOCCR_G3_IO1 */
#define LL_TSC_GROUP3_IO2           TSC_IOCCR_G3_IO2             /*!< TSC Group3 IO2 */
#define LL_TSC_GROUP3_IO3           TSC_IOCCR_G3_IO3             /*!< TSC Group3 IO3 */
#define LL_TSC_GROUP3_IO4           TSC_IOCCR_G3_IO4             /*!< TSC Group3 IO4 */

#define LL_TSC_GROUP4_IO1           TSC_IOCCR_G4_IO1             /*!< TSC Group4 IO1 */
#define LL_TSC_GROUP4_IO2           TSC_IOCCR_G4_IO2             /*!< TSC Group4 IO2 */
#define LL_TSC_GROUP4_IO3           TSC_IOCCR_G4_IO3             /*!< TSC Group4 IO3 */
#define LL_TSC_GROUP4_IO4           TSC_IOCCR_G4_IO4             /*!< TSC Group4 IO4 */

#define LL_TSC_GROUP5_IO1           TSC_IOCCR_G5_IO1             /*!< TSC Group5 IO1 */
#define LL_TSC_GROUP5_IO2           TSC_IOCCR_G5_IO2             /*!< TSC Group5 IO2 */
#define LL_TSC_GROUP5_IO3           TSC_IOCCR_G5_IO3             /*!< TSC Group5 IO3 */
#define LL_TSC_GROUP5_IO4           TSC_IOCCR_G5_IO4             /*!< TSC Group5 IO4 */

#define LL_TSC_GROUP6_IO1           TSC_IOCCR_G6_IO1             /*!< TSC Group6 IO1 */
#define LL_TSC_GROUP6_IO2           TSC_IOCCR_G6_IO2             /*!< TSC Group6 IO2 */
#define LL_TSC_GROUP6_IO3           TSC_IOCCR_G6_IO3             /*!< TSC Group6 IO3 */
#define LL_TSC_GROUP6_IO4           TSC_IOCCR_G6_IO4             /*!< TSC Group6 IO4 */

#define LL_TSC_GROUP7_IO1           TSC_IOCCR_G7_IO1             /*!< TSC Group7 IO1 */
#define LL_TSC_GROUP7_IO2           TSC_IOCCR_G7_IO2             /*!< TSC Group7 IO2 */
#define LL_TSC_GROUP7_IO3           TSC_IOCCR_G7_IO3             /*!< TSC Group7 IO3 */
#define LL_TSC_GROUP7_IO4           TSC_IOCCR_G7_IO4             /*!< TSC Group7 IO4 */

#if defined(TSC_IOCCR_G8_IO1)
#define LL_TSC_GROUP8_IO1           TSC_IOCCR_G8_IO1             /*!< TSC Group8 IO1 */
#define LL_TSC_GROUP8_IO2           TSC_IOCCR_G8_IO2             /*!< TSC Group8 IO2 */
#define LL_TSC_GROUP8_IO3           TSC_IOCCR_G8_IO3             /*!< TSC Group8 IO3 */
#define LL_TSC_GROUP8_IO4           TSC_IOCCR_G8_IO4             /*!< TSC Group8 IO4 */
#else
#define LL_TSC_GROUP8_IO1           (uint32_t)(0x00000080UL | \
                                               LL_TSC_GROUPX_NOT_SUPPORTED) /*!< TSC Group8 IO1 not supported */
#define LL_TSC_GROUP8_IO2           LL_TSC_GROUP8_IO1            /*!< TSC Group8 IO2 not supported */
#define LL_TSC_GROUP8_IO3           LL_TSC_GROUP8_IO1            /*!< TSC Group8 IO3 not supported */
#define LL_TSC_GROUP8_IO4           LL_TSC_GROUP8_IO1            /*!< TSC Group8 IO4 not supported */
#endif /* TSC_IOCCR_G8_IO1 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup TSC_LL_Exported_Macros TSC Exported Macros
  * @{
  */

/**
  * @brief  Write a value in TSC register.
  * @param  instance TSC Instance.
  * @param  reg      Register to be written.
  * @param  value    Value to be written in the register.
  */
#define LL_TSC_WRITE_REG(instance, reg, value) WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in TSC register.
  * @param  instance TSC Instance.
  * @param  reg      Register to be read.
  * @retval Register value.
  */
#define LL_TSC_READ_REG(instance, reg) READ_REG((instance)->reg)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup TSC_LL_Exported_Functions TSC Exported Functions
  * @{
  */

/** @defgroup TSC_LL_EF_Configuration1 Configuration
  * @{
  */

/**
  * @brief Enable the TSC peripheral.
  * @rmtoll
  *  CR          TSCE         LL_TSC_Enable
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_Enable(TSC_TypeDef *tscx)
{
  SET_BIT(tscx->CR, TSC_CR_TSCE);
}

/**
  * @brief Disable the TSC peripheral.
  * @rmtoll
  *  CR          TSCE         LL_TSC_Disable
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_Disable(TSC_TypeDef *tscx)
{
  CLEAR_BIT(tscx->CR, TSC_CR_TSCE);
}

/**
  * @brief Check if the TSC peripheral is enabled or disabled.
  * @rmtoll
  *  CR          TSCE         LL_TSC_IsEnabled
  * @param  tscx TSC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsEnabled(const TSC_TypeDef *tscx)
{
  return ((READ_BIT(tscx->CR, TSC_CR_TSCE) == (TSC_CR_TSCE)) ? 1UL : 0UL);
}

/**
  * @brief Start Acquisition.
  * @rmtoll
  *  CR          START         LL_TSC_StartAcq
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_StartAcq(TSC_TypeDef *tscx)
{
  SET_BIT(tscx->CR, TSC_CR_START);
}

/**
  * @brief Stop Acquisition.
  * @rmtoll
  *  CR          START         LL_TSC_StopAcq
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_StopAcq(TSC_TypeDef *tscx)
{
  CLEAR_BIT(tscx->CR, TSC_CR_START);
}

/**
  * @brief Check if the TSC Acquisition is started or Stopped.
  * @rmtoll
  *  CR          START         LL_TSC_IsStartedAcq
  * @param  tscx TSC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsStartedAcq(const TSC_TypeDef *tscx)
{
  return ((READ_BIT(tscx->CR, TSC_CR_START) == (TSC_CR_START)) ? 1UL : 0UL);
}

/**
  * @brief Set Normal Acquisition mode.
  * @rmtoll
  *  CR          AM         LL_TSC_SetNormalAcqMode
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_SetNormalAcqMode(TSC_TypeDef *tscx)
{
  CLEAR_BIT(tscx->CR, TSC_CR_AM);
}

/**
  * @brief Set synchronization Acquisition mode.
  * @rmtoll
  *  CR          AM         LL_TSC_SetSynchronizedAcqMode
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_SetSynchronizedAcqMode(TSC_TypeDef *tscx)
{
  SET_BIT(tscx->CR, TSC_CR_AM);
}

/**
  * @brief Get Acquisition mode.
  * @rmtoll
  *  CR          AM         LL_TSC_GetAcqMode
  * @param  tscx TSC Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TSC_ACQ_MODE_NORMAL
  *         @arg @ref LL_TSC_ACQ_MODE_SYNCHRO
  */
__STATIC_INLINE uint32_t LL_TSC_GetAcqMode(const TSC_TypeDef *tscx)
{
  return (uint32_t)(READ_BIT(tscx->CR, TSC_CR_AM));
}

/**
  * @brief Set synchronization polarity to falling edge.
  * @rmtoll
  *  CR          SYNCPOL         LL_TSC_SetSyncPolarityFailling
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_SetSyncPolarityFailling(TSC_TypeDef *tscx)
{
  CLEAR_BIT(tscx->CR, TSC_CR_SYNCPOL);
}

/**
  * @brief Set synchronization polarity to rising edge.
  * @rmtoll
  *  CR          SYNCPOL         LL_TSC_SetSyncPolarityRising
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_SetSyncPolarityRising(TSC_TypeDef *tscx)
{
  SET_BIT(tscx->CR, TSC_CR_SYNCPOL);
}

/**
  * @brief Get synchronization polarity.
  * @rmtoll
  *  CR          SYNCPOL         LL_TSC_GetSyncPolarity
  * @param  tscx TSC Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TSC_SYNC_POLARITY_FALLING
  *         @arg @ref LL_TSC_SYNC_POLARITY_RISING
  */
__STATIC_INLINE uint32_t LL_TSC_GetSyncPolarity(const TSC_TypeDef *tscx)
{
  return (uint32_t)(READ_BIT(tscx->CR, TSC_CR_SYNCPOL));
}

/**
  * @brief Set IO default mode to output push-pull low.
  * @rmtoll
  *  CR          IODEF         LL_TSC_SetIODefaultPushPull
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_SetIODefaultPushPull(TSC_TypeDef *tscx)
{
  CLEAR_BIT(tscx->CR, TSC_CR_IODEF);
}

/**
  * @brief Set IO default mode to input floating.
  * @rmtoll
  *  CR          IODEF         LL_TSC_SetIODefaultFloat
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_SetIODefaultFloat(TSC_TypeDef *tscx)
{
  SET_BIT(tscx->CR, TSC_CR_IODEF);
}

/**
  * @brief Get IO default mode.
  * @rmtoll
  *  CR          IODEF         LL_TSC_GetIODefaultMode
  * @param  tscx TSC Instance.
  * @retval IReturned value can be one of the following values:
  *         @arg @ref LL_TSC_IODEF_OUT_PP_LOW
  *         @arg @ref LL_TSC_IODEF_IN_FLOAT
  */
__STATIC_INLINE uint32_t LL_TSC_GetIODefaultMode(const TSC_TypeDef *tscx)
{
  return (uint32_t)(READ_BIT(tscx->CR, TSC_CR_IODEF));
}

/**
  * @brief Set Max count Value.
  * @rmtoll
  *  CR          MCV         LL_TSC_SetMaxCountValue
  * @param  tscx TSC Instance.
  * @param  max_count_value max count value, This parameter can be one of the following values:
  *         @arg @ref LL_TSC_MAX_COUNT_VALUE_255
  *         @arg @ref LL_TSC_MAX_COUNT_VALUE_511
  *         @arg @ref LL_TSC_MAX_COUNT_VALUE_1023
  *         @arg @ref LL_TSC_MAX_COUNT_VALUE_2047
  *         @arg @ref LL_TSC_MAX_COUNT_VALUE_4095
  *         @arg @ref LL_TSC_MAX_COUNT_VALUE_8191
  *         @arg @ref LL_TSC_MAX_COUNT_VALUE_16383
  */
__STATIC_INLINE void LL_TSC_SetMaxCountValue(TSC_TypeDef *tscx, const uint32_t max_count_value)
{
  MODIFY_REG(tscx->CR, TSC_CR_MCV, max_count_value);
}

/**
  * @brief Get Max count Value.
  * @rmtoll
  *  CR          MCV         LL_TSC_GetMaxCountValue
  * @param  tscx TSC Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TSC_MAX_COUNT_VALUE_255
  *         @arg @ref LL_TSC_MAX_COUNT_VALUE_511
  *         @arg @ref LL_TSC_MAX_COUNT_VALUE_1023
  *         @arg @ref LL_TSC_MAX_COUNT_VALUE_2047
  *         @arg @ref LL_TSC_MAX_COUNT_VALUE_4095
  *         @arg @ref LL_TSC_MAX_COUNT_VALUE_8191
  *         @arg @ref LL_TSC_MAX_COUNT_VALUE_16383
  */
__STATIC_INLINE uint32_t LL_TSC_GetMaxCountValue(const TSC_TypeDef *tscx)
{
  return (uint32_t)(READ_BIT(tscx->CR, TSC_CR_MCV));
}

/**
  * @brief Set Pulse Generator Prescaler.
  * @rmtoll
  *  CR          PGPSC         LL_TSC_SetPulseGenPrescaler
  * @param  tscx TSC Instance.
  * @param  pulse_gen_prescaler Pulse Generator Prescaler, This parameter can be one of the following values:
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV1
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV2
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV4
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV8
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV16
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV32
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV64
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV128
  */
__STATIC_INLINE void LL_TSC_SetPulseGenPrescaler(TSC_TypeDef *tscx, const uint32_t pulse_gen_prescaler)
{
  MODIFY_REG(tscx->CR, TSC_CR_PGPSC, pulse_gen_prescaler);
}

/**
  * @brief Get Pulse Generator Prescaler.
  * @rmtoll
  *  CR          PGPSC         LL_TSC_GetPulseGenPrescaler
  * @param  tscx TSC Instance.
  * @retval  returned value can be one of the following values:
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV1
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV2
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV4
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV8
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV16
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV32
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV64
  *         @arg @ref LL_TSC_PULSE_GEN_PRESCALER_DIV128
  */
__STATIC_INLINE uint32_t LL_TSC_GetPulseGenPrescaler(const TSC_TypeDef *tscx)
{
  return (uint32_t)(READ_BIT(tscx->CR, TSC_CR_PGPSC));
}

/**
  * @brief Enable the Spread Spectrum Prescaler.
  * @rmtoll
  *  CR          SSPSC         LL_TSC_EnableSpreadSpecPrescaler
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_EnableSpreadSpecPrescaler(TSC_TypeDef *tscx)
{
  SET_BIT(tscx->CR, TSC_CR_SSPSC);
}

/**
  * @brief Disable the Spread Spectrum Prescaler.
  * @rmtoll
  *  CR          SSPSC         LL_TSC_DisableSpreadSpecPrescaler
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_DisableSpreadSpecPrescaler(TSC_TypeDef *tscx)
{
  CLEAR_BIT(tscx->CR, TSC_CR_SSPSC);
}

/**
  * @brief Check if Spread Spectrum Prescaler is enabled or disabled.
  * @rmtoll
  *  CR          SSPSC         LL_TSC_IsEnabledSpreadSpecPrescaler
  * @param  tscx TSC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsEnabledSpreadSpecPrescaler(const TSC_TypeDef *tscx)
{
  return ((READ_BIT(tscx->CR, TSC_CR_SSPSC) == (TSC_CR_SSPSC)) ? 1UL : 0UL);
}

/**
  * @brief Enable Spread Spectrum.
  * @rmtoll
  *  CR          SSE         LL_TSC_EnableSpreadSpectrum
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_EnableSpreadSpectrum(TSC_TypeDef *tscx)
{
  SET_BIT(tscx->CR, TSC_CR_SSE);
}

/**
  * @brief Disable Spread Spectrum.
  * @rmtoll
  *  CR          SSE         LL_TSC_DisableSpreadSpectrum
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_DisableSpreadSpectrum(TSC_TypeDef *tscx)
{
  CLEAR_BIT(tscx->CR, TSC_CR_SSE);
}

/**
  * @brief Check if the Spread Spectrum is enabled or disabled.
  * @rmtoll
  *  CR          SSE         LL_TSC_IsEnabledSpreadSpectrum
  * @param  tscx TSC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsEnabledSpreadSpectrum(const TSC_TypeDef *tscx)
{
  return ((READ_BIT(tscx->CR, TSC_CR_SSE) == (TSC_CR_SSE)) ? 1UL : 0UL);
}

/**
  * @brief Set Spread spectrum deviation.
  * @rmtoll
  *  CR          SSD         LL_TSC_SetSpreadSpecDeviation
  * @param  tscx TSC Instance.
  * @param  spread_spec_deviation Spread spectrum deviation,
  *         This parameter can be be a number between Min_Data = 0 and Max_Data = 127.
  */
__STATIC_INLINE void LL_TSC_SetSpreadSpecDeviation(TSC_TypeDef *tscx, const uint32_t spread_spec_deviation)
{
  MODIFY_REG(tscx->CR, TSC_CR_SSD, spread_spec_deviation);
}

/**
  * @brief Get Spread spectrum deviation.
  * @rmtoll
  *  CR          SSD         LL_TSC_GetSpreadSpecDeviation
  * @param  tscx TSC Instance.
  * @retval Returned value can be be a number between Min_Data = 0 and Max_Data = 127.
  */
__STATIC_INLINE uint32_t LL_TSC_GetSpreadSpecDeviation(const TSC_TypeDef *tscx)
{
  return (uint32_t)(READ_BIT(tscx->CR, TSC_CR_SSD));
}

/**
  * @brief Set Charge transfer pulse low.
  * @rmtoll
  *  CR          CTPL         LL_TSC_SetChargeTransferPulseLow
  * @param  tscx TSC Instance.
  * @param  charge_transfer_pulse_low Charge transfer pulse low, This parameter can be one of the following values:
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_1CYCLE
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_2CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_3CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_4CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_5CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_6CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_7CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_8CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_9CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_10CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_11CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_12CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_13CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_14CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_15CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_16CYCLES
  */
__STATIC_INLINE void LL_TSC_SetChargeTransferPulseLow(TSC_TypeDef *tscx, const uint32_t charge_transfer_pulse_low)
{
  MODIFY_REG(tscx->CR, TSC_CR_CTPL, charge_transfer_pulse_low);
}

/**
  * @brief Get Charge transfer pulse low.
  * @rmtoll
  *  CR          CTPL         LL_TSC_GetChargeTransferPulseLow
  * @param  tscx TSC Instance.
  * @retval returned value can be one of the following values:
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_1CYCLE
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_2CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_3CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_4CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_5CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_6CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_7CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_8CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_9CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_10CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_11CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_12CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_13CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_14CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_15CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_LOW_16CYCLES
  */
__STATIC_INLINE uint32_t LL_TSC_GetChargeTransferPulseLow(const TSC_TypeDef *tscx)
{
  return (uint32_t)(READ_BIT(tscx->CR, TSC_CR_CTPL));
}

/**
  * @brief Set Charge transfer pulse High.
  * @rmtoll
  *  CR          CTPH         LL_TSC_SetChargeTransferPulseHigh
  * @param  tscx TSC Instance.
  * @param  charge_transfer_pulse_high Charge transfer pulse High, This parameter can be one of the following values:
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_1CYCLE
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_2CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_3CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_4CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_5CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_6CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_7CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_8CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_9CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_10CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_11CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_12CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_13CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_14CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_15CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_16CYCLES
  */
__STATIC_INLINE void LL_TSC_SetChargeTransferPulseHigh(TSC_TypeDef *tscx, const uint32_t charge_transfer_pulse_high)
{
  MODIFY_REG(tscx->CR, TSC_CR_CTPH, charge_transfer_pulse_high);
}

/**
  * @brief Get Charge transfer pulse High.
  * @rmtoll
  *  CR          CTPH         LL_TSC_GetChargeTransferPulseHigh
  * @param  tscx TSC Instance.
  * @retval returned value can be one of the following values:
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_1CYCLE
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_2CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_3CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_4CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_5CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_6CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_7CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_8CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_9CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_10CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_11CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_12CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_13CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_14CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_15CYCLES
  *         @arg @ref LL_TSC_CHARGE_TRANSFER_PULSE_HIGH_16CYCLES
  */
__STATIC_INLINE uint32_t LL_TSC_GetChargeTransferPulseHigh(const TSC_TypeDef *tscx)
{
  return (uint32_t)(READ_BIT(tscx->CR, TSC_CR_CTPH));
}

/**
  * @brief Configure the specified TSC Config.
  * @rmtoll
  *  CR          CTPH         LL_TSC_Config \n
  *  CR          CTPL         LL_TSC_Config \n
  *  CR          PGPSC        LL_TSC_Config \n
  *  CR          MCV          LL_TSC_Config \n
  *  IOCCR       Gx_IOy       LL_TSC_Config \n
  *  IOSCR       Gx_IOy       LL_TSC_Config \n
  *  IOGCSR      GxE          LL_TSC_Config
  * @param  tscx       TSC Instance.
  * @param  cr_config  This parameter can be a combination of the following groups:
  *         @arg @ref TSC_LL_EC_Pulse_Generator_Prescaler
  *         @arg @ref TSC_LL_EC_Charge_Transfer_Pulse_Low
  *         @arg @ref TSC_LL_EC_Charge_Transfer_Pulse_High
  *         @arg @ref TSC_LL_EC_Max_Count_Value
  * @param  channels  This parameter can be a combination of the following group:
  *         @arg @ref TSC_LL_EC_Groups_IOs
  * @param  shields  This parameter can be a combination of the following group:
  *         @arg @ref TSC_LL_EC_Groups_IOs
  * @param  samplings  This parameter can be a combination of the following group:
  *         @arg @ref TSC_LL_EC_Groups_IOs
  */
__STATIC_INLINE void LL_TSC_Config(TSC_TypeDef *tscx, const uint32_t cr_config,
                                   uint32_t channels,
                                   uint32_t shields,
                                   uint32_t samplings)
{
  /* Configure the TSC Pulse */
  MODIFY_REG(tscx->CR, (TSC_CR_CTPH | TSC_CR_CTPL | TSC_CR_PGPSC | TSC_CR_MCV), cr_config);

  /* Set channels and shields IOs */
  SET_BIT(tscx->IOCCR, (channels | shields));

  /* Set samplings IOs */
  SET_BIT(tscx->IOSCR, samplings);

  /* Set groups to be acquired */
  SET_BIT(tscx->IOGCSR, TSC_extract_groups(channels));
}
/**
  * @}
  */

/** @defgroup TSC_LL_EF_IT_Management IT Management
  * @{
  */

/**
  * @brief  Enable EOA interrupt.
  * @rmtoll
  *  IER          EOAIE         LL_TSC_EnableIT_EOA
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_EnableIT_EOA(TSC_TypeDef *tscx)
{
  SET_BIT(tscx->IER, TSC_IER_EOAIE);
}

/**
  * @brief  Disable EOA interrupt.
  * @rmtoll
  *  IER          EOAIE         LL_TSC_DisableIT_EOA
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_DisableIT_EOA(TSC_TypeDef *tscx)
{
  CLEAR_BIT(tscx->IER, TSC_IER_EOAIE);
}

/**
  * @brief  Check if EOA interrupt is enabled or disabled.
  * @rmtoll
  *  IER          EOAIE         LL_TSC_IsEnabledIT_EOA
  * @param  tscx TSC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsEnabledIT_EOA(const TSC_TypeDef *tscx)
{
  return ((READ_BIT(tscx->IER, TSC_IER_EOAIE) == (TSC_IER_EOAIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable MCE interrupt.
  * @rmtoll
  *  IER          MCEIE         LL_TSC_EnableIT_MCE
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_EnableIT_MCE(TSC_TypeDef *tscx)
{
  SET_BIT(tscx->IER, TSC_IER_MCEIE);
}

/**
  * @brief  Disable MCE interrupt.
  * @rmtoll
  *  IER          MCEIE         LL_TSC_DisableIT_MCE
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_DisableIT_MCE(TSC_TypeDef *tscx)
{
  CLEAR_BIT(tscx->IER, TSC_IER_MCEIE);
}

/**
  * @brief  Check if MCE interrupt is enabled or disabled.
  * @rmtoll
  *  IER          MCEIE         LL_TSC_IsEnabledIT_MCE
  * @param  tscx TSC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsEnabledIT_MCE(const TSC_TypeDef *tscx)
{
  return ((READ_BIT(tscx->IER, TSC_IER_MCEIE) == (TSC_IER_MCEIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable interrupts.
  * @rmtoll
  *  IER          EOAIE         LL_TSC_EnableIT \n
  *  IER          MCEIE         LL_TSC_EnableIT
  * @param  tscx TSC Instance.
  * @param  interrupts
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_IT_EOA
  *         @arg @ref LL_TSC_IT_MCE

  */
__STATIC_INLINE void LL_TSC_EnableIT(TSC_TypeDef *tscx, uint32_t interrupts)
{
  SET_BIT(tscx->IER, interrupts);
}

/**
  * @brief  Disable interrupts.
  * @rmtoll
  *  IER          EOAIE         LL_TSC_DisableIT \n
  *  IER          MCEIE         LL_TSC_DisableIT
  * @param  tscx TSC Instance.
  * @param  interrupts
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_IT_EOA
  *         @arg @ref LL_TSC_IT_MCE
  */
__STATIC_INLINE void LL_TSC_DisableIT(TSC_TypeDef *tscx, uint32_t interrupts)
{
  CLEAR_BIT(tscx->IER, interrupts);
}

/**
  * @brief  Check if the interrupts are enabled or disabled.
  * @rmtoll
  *  IER          EOAIE         LL_TSC_IsEnabledIT \n
  *  IER          MCEIE         LL_TSC_IsEnabledIT
  * @param  tscx TSC Instance.
  * @param  interrupts
  *         This parameter can be a combination of the following values :
  *         @arg @ref LL_TSC_IT_EOA
  *         @arg @ref LL_TSC_IT_MCE
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsEnabledIT(const TSC_TypeDef *tscx, uint32_t interrupts)
{
  return ((READ_BIT(tscx->IER, interrupts) == (interrupts)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup TSC_LL_EF_FLAG_management FLAG management
  * @{
  */

/**
  * @brief Clear EOA flag.
  * @rmtoll
  *  ICR          EOAIC        LL_TSC_ClearFlag_EOA
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_ClearFlag_EOA(TSC_TypeDef *tscx)
{
  SET_BIT(tscx->ICR, TSC_ICR_EOAIC);
}

/**
  * @brief Clear MCE flag.
  * @rmtoll
  *  ICR          MCEIC         LL_TSC_ClearFlag_MCE
  * @param  tscx TSC Instance.
  */
__STATIC_INLINE void LL_TSC_ClearFlag_MCE(TSC_TypeDef *tscx)
{
  SET_BIT(tscx->ICR, TSC_ICR_MCEIC);
}

/**
  * @brief Clear flags.
  * @rmtoll
  *  ICR          EOAIC         LL_TSC_ClearFlag \n
  *  ICR          MCEIC         LL_TSC_ClearFlag
  * @param  tscx TSC Instance.
  * @param  flags
  *         This parameter can be a combination of the following values :
  *         @arg @ref LL_TSC_FLAG_EOA
  *         @arg @ref LL_TSC_FLAG_MCE
  */
__STATIC_INLINE void LL_TSC_ClearFlag(TSC_TypeDef *tscx, uint32_t flags)
{
  SET_BIT(tscx->ICR, flags);
}

/**
  * @brief Check whether the EOA flag is activate.
  * @rmtoll
  *  ISR          EOAF         LL_TSC_IsActiveFlag_EOA
  * @param  tscx TSC Instance.
  * @retval State of FLAG sources (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsActiveFlag_EOA(const TSC_TypeDef *tscx)
{
  return ((READ_BIT(tscx->ISR, TSC_ISR_EOAF) == (TSC_ISR_EOAF)) ? 1UL : 0UL);
}

/**
  * @brief Check whether the MCE flag is activate.
  * @rmtoll
  *  ISR          MCEF         LL_TSC_IsActiveFlag_MCE
  * @param  tscx TSC Instance.
  * @retval State of FLAG sources (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsActiveFlag_MCE(const TSC_TypeDef *tscx)
{
  return ((READ_BIT(tscx->ISR, TSC_ISR_MCEF) == (TSC_ISR_MCEF)) ? 1UL : 0UL);
}

/**
  * @brief Check whether the flags are activate.
  * @rmtoll
  *  ISR          EOAF         LL_TSC_IsActiveFlag \n
  *  ISR          MCEF         LL_TSC_IsActiveFlag
  * @param  tscx TSC Instance.
  * @param  flags
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_FLAG_EOA
  *         @arg @ref LL_TSC_FLAG_MCE
  * @retval State of flags sources (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsActiveFlag(const TSC_TypeDef *tscx, uint32_t flags)
{
  return ((READ_BIT(tscx->ISR, flags) == (flags)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup TSC_LL_EF_Configuration2 Configuration
  * @{
  */

/**
  * @brief Enable schmitt trigger hysteresis on a group of IOs.
  * @rmtoll
  *  IOHCR        Gx_IOy         LL_TSC_EnableHysteresis
  * @param  tscx TSC Instance.
  * @param  gx_ioy_mask IOs mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1_IO1
  *         @arg @ref LL_TSC_GROUP1_IO2
  *         @arg @ref LL_TSC_GROUP1_IO3
  *         @arg @ref LL_TSC_GROUP1_IO4
  *         @arg @ref LL_TSC_GROUP2_IO1
  *         @arg @ref LL_TSC_GROUP2_IO2
  *         @arg @ref LL_TSC_GROUP2_IO3
  *         @arg @ref LL_TSC_GROUP2_IO4
  *         @arg @ref LL_TSC_GROUP3_IO1
  *         @arg @ref LL_TSC_GROUP3_IO2
  *         @arg @ref LL_TSC_GROUP3_IO3
  *         @arg @ref LL_TSC_GROUP3_IO4
  *         @arg @ref LL_TSC_GROUP4_IO1
  *         @arg @ref LL_TSC_GROUP4_IO2
  *         @arg @ref LL_TSC_GROUP4_IO3
  *         @arg @ref LL_TSC_GROUP4_IO4
  *         @arg @ref LL_TSC_GROUP5_IO1
  *         @arg @ref LL_TSC_GROUP5_IO2
  *         @arg @ref LL_TSC_GROUP5_IO3
  *         @arg @ref LL_TSC_GROUP5_IO4
  *         @arg @ref LL_TSC_GROUP6_IO1
  *         @arg @ref LL_TSC_GROUP6_IO2
  *         @arg @ref LL_TSC_GROUP6_IO3
  *         @arg @ref LL_TSC_GROUP6_IO4
  *         @arg @ref LL_TSC_GROUP7_IO1
  *         @arg @ref LL_TSC_GROUP7_IO2
  *         @arg @ref LL_TSC_GROUP7_IO3
  *         @arg @ref LL_TSC_GROUP7_IO4
  *         @arg @ref LL_TSC_GROUP8_IO1
  *         @arg @ref LL_TSC_GROUP8_IO2
  *         @arg @ref LL_TSC_GROUP8_IO3
  *         @arg @ref LL_TSC_GROUP8_IO4
  */
__STATIC_INLINE void LL_TSC_EnableHysteresis(TSC_TypeDef *tscx, const uint32_t gx_ioy_mask)
{
  SET_BIT(tscx->IOHCR, gx_ioy_mask);
}

/**
  * @brief Disable schmitt trigger hysteresis on a group of IOs.
  * @rmtoll
  *  IOHCR        Gx_IOy         LL_TSC_DisableHysteresis
  * @param  tscx TSC Instance.
  * @param  gx_ioy_mask IOs mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1_IO1
  *         @arg @ref LL_TSC_GROUP1_IO2
  *         @arg @ref LL_TSC_GROUP1_IO3
  *         @arg @ref LL_TSC_GROUP1_IO4
  *         @arg @ref LL_TSC_GROUP2_IO1
  *         @arg @ref LL_TSC_GROUP2_IO2
  *         @arg @ref LL_TSC_GROUP2_IO3
  *         @arg @ref LL_TSC_GROUP2_IO4
  *         @arg @ref LL_TSC_GROUP3_IO1
  *         @arg @ref LL_TSC_GROUP3_IO2
  *         @arg @ref LL_TSC_GROUP3_IO3
  *         @arg @ref LL_TSC_GROUP3_IO4
  *         @arg @ref LL_TSC_GROUP4_IO1
  *         @arg @ref LL_TSC_GROUP4_IO2
  *         @arg @ref LL_TSC_GROUP4_IO3
  *         @arg @ref LL_TSC_GROUP4_IO4
  *         @arg @ref LL_TSC_GROUP5_IO1
  *         @arg @ref LL_TSC_GROUP5_IO2
  *         @arg @ref LL_TSC_GROUP5_IO3
  *         @arg @ref LL_TSC_GROUP5_IO4
  *         @arg @ref LL_TSC_GROUP6_IO1
  *         @arg @ref LL_TSC_GROUP6_IO2
  *         @arg @ref LL_TSC_GROUP6_IO3
  *         @arg @ref LL_TSC_GROUP6_IO4
  *         @arg @ref LL_TSC_GROUP7_IO1
  *         @arg @ref LL_TSC_GROUP7_IO2
  *         @arg @ref LL_TSC_GROUP7_IO3
  *         @arg @ref LL_TSC_GROUP7_IO4
  *         @arg @ref LL_TSC_GROUP8_IO1
  *         @arg @ref LL_TSC_GROUP8_IO2
  *         @arg @ref LL_TSC_GROUP8_IO3
  *         @arg @ref LL_TSC_GROUP8_IO4
  */
__STATIC_INLINE void LL_TSC_DisableHysteresis(TSC_TypeDef *tscx, const uint32_t gx_ioy_mask)
{
  CLEAR_BIT(tscx->IOHCR, gx_ioy_mask);
}

/**
  * @brief Check if the Schmitt trigger hysteresis mode is set or not.
  * @rmtoll
  *  IOHCR          Gx_IOy         LL_TSC_IsEnabledHysteresis
  * @param  tscx TSC Instance.
  * @param  gx_ioy_mask IOs mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1_IO1
  *         @arg @ref LL_TSC_GROUP1_IO2
  *         @arg @ref LL_TSC_GROUP1_IO3
  *         @arg @ref LL_TSC_GROUP1_IO4
  *         @arg @ref LL_TSC_GROUP2_IO1
  *         @arg @ref LL_TSC_GROUP2_IO2
  *         @arg @ref LL_TSC_GROUP2_IO3
  *         @arg @ref LL_TSC_GROUP2_IO4
  *         @arg @ref LL_TSC_GROUP3_IO1
  *         @arg @ref LL_TSC_GROUP3_IO2
  *         @arg @ref LL_TSC_GROUP3_IO3
  *         @arg @ref LL_TSC_GROUP3_IO4
  *         @arg @ref LL_TSC_GROUP4_IO1
  *         @arg @ref LL_TSC_GROUP4_IO2
  *         @arg @ref LL_TSC_GROUP4_IO3
  *         @arg @ref LL_TSC_GROUP4_IO4
  *         @arg @ref LL_TSC_GROUP5_IO1
  *         @arg @ref LL_TSC_GROUP5_IO2
  *         @arg @ref LL_TSC_GROUP5_IO3
  *         @arg @ref LL_TSC_GROUP5_IO4
  *         @arg @ref LL_TSC_GROUP6_IO1
  *         @arg @ref LL_TSC_GROUP6_IO2
  *         @arg @ref LL_TSC_GROUP6_IO3
  *         @arg @ref LL_TSC_GROUP6_IO4
  *         @arg @ref LL_TSC_GROUP7_IO1
  *         @arg @ref LL_TSC_GROUP7_IO2
  *         @arg @ref LL_TSC_GROUP7_IO3
  *         @arg @ref LL_TSC_GROUP7_IO4
  *         @arg @ref LL_TSC_GROUP8_IO1
  *         @arg @ref LL_TSC_GROUP8_IO2
  *         @arg @ref LL_TSC_GROUP8_IO3
  *         @arg @ref LL_TSC_GROUP8_IO4
  * @retval State of these bits (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsEnabledHysteresis(const TSC_TypeDef *tscx, const uint32_t gx_ioy_mask)
{
  return ((READ_BIT(tscx->IOHCR, gx_ioy_mask) == (gx_ioy_mask)) ? 1UL : 0UL);
}

/**
  * @brief Close analog switch on a group of IOs.
  * @rmtoll
  *  IOASCR        Gx_IOy         LL_TSC_EnableAnalogSwitch
  * @param  tscx TSC Instance.
  * @param  gx_ioy_mask IOs mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1_IO1
  *         @arg @ref LL_TSC_GROUP1_IO2
  *         @arg @ref LL_TSC_GROUP1_IO3
  *         @arg @ref LL_TSC_GROUP1_IO4
  *         @arg @ref LL_TSC_GROUP2_IO1
  *         @arg @ref LL_TSC_GROUP2_IO2
  *         @arg @ref LL_TSC_GROUP2_IO3
  *         @arg @ref LL_TSC_GROUP2_IO4
  *         @arg @ref LL_TSC_GROUP3_IO1
  *         @arg @ref LL_TSC_GROUP3_IO2
  *         @arg @ref LL_TSC_GROUP3_IO3
  *         @arg @ref LL_TSC_GROUP3_IO4
  *         @arg @ref LL_TSC_GROUP4_IO1
  *         @arg @ref LL_TSC_GROUP4_IO2
  *         @arg @ref LL_TSC_GROUP4_IO3
  *         @arg @ref LL_TSC_GROUP4_IO4
  *         @arg @ref LL_TSC_GROUP5_IO1
  *         @arg @ref LL_TSC_GROUP5_IO2
  *         @arg @ref LL_TSC_GROUP5_IO3
  *         @arg @ref LL_TSC_GROUP5_IO4
  *         @arg @ref LL_TSC_GROUP6_IO1
  *         @arg @ref LL_TSC_GROUP6_IO2
  *         @arg @ref LL_TSC_GROUP6_IO3
  *         @arg @ref LL_TSC_GROUP6_IO4
  *         @arg @ref LL_TSC_GROUP7_IO1
  *         @arg @ref LL_TSC_GROUP7_IO2
  *         @arg @ref LL_TSC_GROUP7_IO3
  *         @arg @ref LL_TSC_GROUP7_IO4
  *         @arg @ref LL_TSC_GROUP8_IO1
  *         @arg @ref LL_TSC_GROUP8_IO2
  *         @arg @ref LL_TSC_GROUP8_IO3
  *         @arg @ref LL_TSC_GROUP8_IO4
  */
__STATIC_INLINE void LL_TSC_EnableAnalogSwitch(TSC_TypeDef *tscx, const uint32_t gx_ioy_mask)
{
  SET_BIT(tscx->IOASCR, gx_ioy_mask);
}

/**
  * @brief Open analog switch on a group of IOs.
  * @rmtoll
  *  IOASCR        Gx_IOy         LL_TSC_DisableAnalogSwitch
  * @param  tscx TSC Instance.
  * @param  gx_ioy_mask IOs mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1_IO1
  *         @arg @ref LL_TSC_GROUP1_IO2
  *         @arg @ref LL_TSC_GROUP1_IO3
  *         @arg @ref LL_TSC_GROUP1_IO4
  *         @arg @ref LL_TSC_GROUP2_IO1
  *         @arg @ref LL_TSC_GROUP2_IO2
  *         @arg @ref LL_TSC_GROUP2_IO3
  *         @arg @ref LL_TSC_GROUP2_IO4
  *         @arg @ref LL_TSC_GROUP3_IO1
  *         @arg @ref LL_TSC_GROUP3_IO2
  *         @arg @ref LL_TSC_GROUP3_IO3
  *         @arg @ref LL_TSC_GROUP3_IO4
  *         @arg @ref LL_TSC_GROUP4_IO1
  *         @arg @ref LL_TSC_GROUP4_IO2
  *         @arg @ref LL_TSC_GROUP4_IO3
  *         @arg @ref LL_TSC_GROUP4_IO4
  *         @arg @ref LL_TSC_GROUP5_IO1
  *         @arg @ref LL_TSC_GROUP5_IO2
  *         @arg @ref LL_TSC_GROUP5_IO3
  *         @arg @ref LL_TSC_GROUP5_IO4
  *         @arg @ref LL_TSC_GROUP6_IO1
  *         @arg @ref LL_TSC_GROUP6_IO2
  *         @arg @ref LL_TSC_GROUP6_IO3
  *         @arg @ref LL_TSC_GROUP6_IO4
  *         @arg @ref LL_TSC_GROUP7_IO1
  *         @arg @ref LL_TSC_GROUP7_IO2
  *         @arg @ref LL_TSC_GROUP7_IO3
  *         @arg @ref LL_TSC_GROUP7_IO4
  *         @arg @ref LL_TSC_GROUP8_IO1
  *         @arg @ref LL_TSC_GROUP8_IO2
  *         @arg @ref LL_TSC_GROUP8_IO3
  *         @arg @ref LL_TSC_GROUP8_IO4
  */
__STATIC_INLINE void LL_TSC_DisableAnalogSwitch(TSC_TypeDef *tscx, const uint32_t gx_ioy_mask)
{
  CLEAR_BIT(tscx->IOASCR, gx_ioy_mask);
}

/**
  * @brief Check if the analog switch on a group of IOs is set or not.
  * @rmtoll
  *  IOASCR          Gx_IOy         LL_TSC_IsEnabledAnalogSwitch
  * @param  tscx TSC Instance.
  * @param  gx_ioy_mask IOs mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1_IO1
  *         @arg @ref LL_TSC_GROUP1_IO2
  *         @arg @ref LL_TSC_GROUP1_IO3
  *         @arg @ref LL_TSC_GROUP1_IO4
  *         @arg @ref LL_TSC_GROUP2_IO1
  *         @arg @ref LL_TSC_GROUP2_IO2
  *         @arg @ref LL_TSC_GROUP2_IO3
  *         @arg @ref LL_TSC_GROUP2_IO4
  *         @arg @ref LL_TSC_GROUP3_IO1
  *         @arg @ref LL_TSC_GROUP3_IO2
  *         @arg @ref LL_TSC_GROUP3_IO3
  *         @arg @ref LL_TSC_GROUP3_IO4
  *         @arg @ref LL_TSC_GROUP4_IO1
  *         @arg @ref LL_TSC_GROUP4_IO2
  *         @arg @ref LL_TSC_GROUP4_IO3
  *         @arg @ref LL_TSC_GROUP4_IO4
  *         @arg @ref LL_TSC_GROUP5_IO1
  *         @arg @ref LL_TSC_GROUP5_IO2
  *         @arg @ref LL_TSC_GROUP5_IO3
  *         @arg @ref LL_TSC_GROUP5_IO4
  *         @arg @ref LL_TSC_GROUP6_IO1
  *         @arg @ref LL_TSC_GROUP6_IO2
  *         @arg @ref LL_TSC_GROUP6_IO3
  *         @arg @ref LL_TSC_GROUP6_IO4
  *         @arg @ref LL_TSC_GROUP7_IO1
  *         @arg @ref LL_TSC_GROUP7_IO2
  *         @arg @ref LL_TSC_GROUP7_IO3
  *         @arg @ref LL_TSC_GROUP7_IO4
  *         @arg @ref LL_TSC_GROUP8_IO1
  *         @arg @ref LL_TSC_GROUP8_IO2
  *         @arg @ref LL_TSC_GROUP8_IO3
  *         @arg @ref LL_TSC_GROUP8_IO4
  * @retval State of these bits (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsEnabledAnalogSwitch(const TSC_TypeDef *tscx, const uint32_t gx_ioy_mask)
{
  return ((READ_BIT(tscx->IOASCR, gx_ioy_mask) == (gx_ioy_mask)) ? 1UL : 0UL);
}

/**
  * @brief Enable a group of IOs in sampling mode.
  * @rmtoll
  *  IOSCR        Gx_IOy         LL_TSC_EnableSampling
  * @param  tscx TSC Instance.
  * @param  gx_ioy_mask IOs mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1_IO1
  *         @arg @ref LL_TSC_GROUP1_IO2
  *         @arg @ref LL_TSC_GROUP1_IO3
  *         @arg @ref LL_TSC_GROUP1_IO4
  *         @arg @ref LL_TSC_GROUP2_IO1
  *         @arg @ref LL_TSC_GROUP2_IO2
  *         @arg @ref LL_TSC_GROUP2_IO3
  *         @arg @ref LL_TSC_GROUP2_IO4
  *         @arg @ref LL_TSC_GROUP3_IO1
  *         @arg @ref LL_TSC_GROUP3_IO2
  *         @arg @ref LL_TSC_GROUP3_IO3
  *         @arg @ref LL_TSC_GROUP3_IO4
  *         @arg @ref LL_TSC_GROUP4_IO1
  *         @arg @ref LL_TSC_GROUP4_IO2
  *         @arg @ref LL_TSC_GROUP4_IO3
  *         @arg @ref LL_TSC_GROUP4_IO4
  *         @arg @ref LL_TSC_GROUP5_IO1
  *         @arg @ref LL_TSC_GROUP5_IO2
  *         @arg @ref LL_TSC_GROUP5_IO3
  *         @arg @ref LL_TSC_GROUP5_IO4
  *         @arg @ref LL_TSC_GROUP6_IO1
  *         @arg @ref LL_TSC_GROUP6_IO2
  *         @arg @ref LL_TSC_GROUP6_IO3
  *         @arg @ref LL_TSC_GROUP6_IO4
  *         @arg @ref LL_TSC_GROUP7_IO1
  *         @arg @ref LL_TSC_GROUP7_IO2
  *         @arg @ref LL_TSC_GROUP7_IO3
  *         @arg @ref LL_TSC_GROUP7_IO4
  *         @arg @ref LL_TSC_GROUP8_IO1
  *         @arg @ref LL_TSC_GROUP8_IO2
  *         @arg @ref LL_TSC_GROUP8_IO3
  *         @arg @ref LL_TSC_GROUP8_IO4
  */
__STATIC_INLINE void LL_TSC_EnableSampling(TSC_TypeDef *tscx, const uint32_t gx_ioy_mask)
{
  SET_BIT(tscx->IOSCR, gx_ioy_mask);
}

/**
  * @brief Disable a group of sampling IOs.
  * @rmtoll
  *  IOSCR        Gx_IOy         LL_TSC_DisableSampling
  * @param  tscx TSC Instance.
  * @param  gx_ioy_mask IOs mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1_IO1
  *         @arg @ref LL_TSC_GROUP1_IO2
  *         @arg @ref LL_TSC_GROUP1_IO3
  *         @arg @ref LL_TSC_GROUP1_IO4
  *         @arg @ref LL_TSC_GROUP2_IO1
  *         @arg @ref LL_TSC_GROUP2_IO2
  *         @arg @ref LL_TSC_GROUP2_IO3
  *         @arg @ref LL_TSC_GROUP2_IO4
  *         @arg @ref LL_TSC_GROUP3_IO1
  *         @arg @ref LL_TSC_GROUP3_IO2
  *         @arg @ref LL_TSC_GROUP3_IO3
  *         @arg @ref LL_TSC_GROUP3_IO4
  *         @arg @ref LL_TSC_GROUP4_IO1
  *         @arg @ref LL_TSC_GROUP4_IO2
  *         @arg @ref LL_TSC_GROUP4_IO3
  *         @arg @ref LL_TSC_GROUP4_IO4
  *         @arg @ref LL_TSC_GROUP5_IO1
  *         @arg @ref LL_TSC_GROUP5_IO2
  *         @arg @ref LL_TSC_GROUP5_IO3
  *         @arg @ref LL_TSC_GROUP5_IO4
  *         @arg @ref LL_TSC_GROUP6_IO1
  *         @arg @ref LL_TSC_GROUP6_IO2
  *         @arg @ref LL_TSC_GROUP6_IO3
  *         @arg @ref LL_TSC_GROUP6_IO4
  *         @arg @ref LL_TSC_GROUP7_IO1
  *         @arg @ref LL_TSC_GROUP7_IO2
  *         @arg @ref LL_TSC_GROUP7_IO3
  *         @arg @ref LL_TSC_GROUP7_IO4
  *         @arg @ref LL_TSC_GROUP8_IO1
  *         @arg @ref LL_TSC_GROUP8_IO2
  *         @arg @ref LL_TSC_GROUP8_IO3
  *         @arg @ref LL_TSC_GROUP8_IO4
  */
__STATIC_INLINE void LL_TSC_DisableSampling(TSC_TypeDef *tscx, const uint32_t gx_ioy_mask)
{
  CLEAR_BIT(tscx->IOSCR, gx_ioy_mask);
}

/**
  * @brief Check if the sampling IOs is enable or disable.
  * @rmtoll
  *  IOSCR          Gx_IOy         LL_TSC_IsEnabledSampling
  * @param  tscx TSC Instance.
  * @param  gx_ioy_mask IOs mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1_IO1
  *         @arg @ref LL_TSC_GROUP1_IO2
  *         @arg @ref LL_TSC_GROUP1_IO3
  *         @arg @ref LL_TSC_GROUP1_IO4
  *         @arg @ref LL_TSC_GROUP2_IO1
  *         @arg @ref LL_TSC_GROUP2_IO2
  *         @arg @ref LL_TSC_GROUP2_IO3
  *         @arg @ref LL_TSC_GROUP2_IO4
  *         @arg @ref LL_TSC_GROUP3_IO1
  *         @arg @ref LL_TSC_GROUP3_IO2
  *         @arg @ref LL_TSC_GROUP3_IO3
  *         @arg @ref LL_TSC_GROUP3_IO4
  *         @arg @ref LL_TSC_GROUP4_IO1
  *         @arg @ref LL_TSC_GROUP4_IO2
  *         @arg @ref LL_TSC_GROUP4_IO3
  *         @arg @ref LL_TSC_GROUP4_IO4
  *         @arg @ref LL_TSC_GROUP5_IO1
  *         @arg @ref LL_TSC_GROUP5_IO2
  *         @arg @ref LL_TSC_GROUP5_IO3
  *         @arg @ref LL_TSC_GROUP5_IO4
  *         @arg @ref LL_TSC_GROUP6_IO1
  *         @arg @ref LL_TSC_GROUP6_IO2
  *         @arg @ref LL_TSC_GROUP6_IO3
  *         @arg @ref LL_TSC_GROUP6_IO4
  *         @arg @ref LL_TSC_GROUP7_IO1
  *         @arg @ref LL_TSC_GROUP7_IO2
  *         @arg @ref LL_TSC_GROUP7_IO3
  *         @arg @ref LL_TSC_GROUP7_IO4
  *         @arg @ref LL_TSC_GROUP8_IO1
  *         @arg @ref LL_TSC_GROUP8_IO2
  *         @arg @ref LL_TSC_GROUP8_IO3
  *         @arg @ref LL_TSC_GROUP8_IO4
  * @retval State of these bits (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsEnabledSampling(const TSC_TypeDef *tscx, const uint32_t gx_ioy_mask)
{
  return ((READ_BIT(tscx->IOSCR, gx_ioy_mask) == (gx_ioy_mask)) ? 1UL : 0UL);
}

/**
  * @brief Enable a group of IOs in channel mode.
  * @rmtoll
  *  IOCCR        Gx_IOy         LL_TSC_EnableChannel
  * @param  tscx TSC Instance.
  * @param  gx_ioy_mask IOs mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1_IO1
  *         @arg @ref LL_TSC_GROUP1_IO2
  *         @arg @ref LL_TSC_GROUP1_IO3
  *         @arg @ref LL_TSC_GROUP1_IO4
  *         @arg @ref LL_TSC_GROUP2_IO1
  *         @arg @ref LL_TSC_GROUP2_IO2
  *         @arg @ref LL_TSC_GROUP2_IO3
  *         @arg @ref LL_TSC_GROUP2_IO4
  *         @arg @ref LL_TSC_GROUP3_IO1
  *         @arg @ref LL_TSC_GROUP3_IO2
  *         @arg @ref LL_TSC_GROUP3_IO3
  *         @arg @ref LL_TSC_GROUP3_IO4
  *         @arg @ref LL_TSC_GROUP4_IO1
  *         @arg @ref LL_TSC_GROUP4_IO2
  *         @arg @ref LL_TSC_GROUP4_IO3
  *         @arg @ref LL_TSC_GROUP4_IO4
  *         @arg @ref LL_TSC_GROUP5_IO1
  *         @arg @ref LL_TSC_GROUP5_IO2
  *         @arg @ref LL_TSC_GROUP5_IO3
  *         @arg @ref LL_TSC_GROUP5_IO4
  *         @arg @ref LL_TSC_GROUP6_IO1
  *         @arg @ref LL_TSC_GROUP6_IO2
  *         @arg @ref LL_TSC_GROUP6_IO3
  *         @arg @ref LL_TSC_GROUP6_IO4
  *         @arg @ref LL_TSC_GROUP7_IO1
  *         @arg @ref LL_TSC_GROUP7_IO2
  *         @arg @ref LL_TSC_GROUP7_IO3
  *         @arg @ref LL_TSC_GROUP7_IO4
  *         @arg @ref LL_TSC_GROUP8_IO1
  *         @arg @ref LL_TSC_GROUP8_IO2
  *         @arg @ref LL_TSC_GROUP8_IO3
  *         @arg @ref LL_TSC_GROUP8_IO4
  */
__STATIC_INLINE void LL_TSC_EnableChannel(TSC_TypeDef *tscx, const uint32_t gx_ioy_mask)
{
  SET_BIT(tscx->IOCCR, gx_ioy_mask);
}

/**
  * @brief Disable a group of channel IOs.
  * @rmtoll
  *  IOCCR        Gx_IOy         LL_TSC_DisableChannel
  * @param  tscx TSC Instance.
  * @param  gx_ioy_mask IOs mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1_IO1
  *         @arg @ref LL_TSC_GROUP1_IO2
  *         @arg @ref LL_TSC_GROUP1_IO3
  *         @arg @ref LL_TSC_GROUP1_IO4
  *         @arg @ref LL_TSC_GROUP2_IO1
  *         @arg @ref LL_TSC_GROUP2_IO2
  *         @arg @ref LL_TSC_GROUP2_IO3
  *         @arg @ref LL_TSC_GROUP2_IO4
  *         @arg @ref LL_TSC_GROUP3_IO1
  *         @arg @ref LL_TSC_GROUP3_IO2
  *         @arg @ref LL_TSC_GROUP3_IO3
  *         @arg @ref LL_TSC_GROUP3_IO4
  *         @arg @ref LL_TSC_GROUP4_IO1
  *         @arg @ref LL_TSC_GROUP4_IO2
  *         @arg @ref LL_TSC_GROUP4_IO3
  *         @arg @ref LL_TSC_GROUP4_IO4
  *         @arg @ref LL_TSC_GROUP5_IO1
  *         @arg @ref LL_TSC_GROUP5_IO2
  *         @arg @ref LL_TSC_GROUP5_IO3
  *         @arg @ref LL_TSC_GROUP5_IO4
  *         @arg @ref LL_TSC_GROUP6_IO1
  *         @arg @ref LL_TSC_GROUP6_IO2
  *         @arg @ref LL_TSC_GROUP6_IO3
  *         @arg @ref LL_TSC_GROUP6_IO4
  *         @arg @ref LL_TSC_GROUP7_IO1
  *         @arg @ref LL_TSC_GROUP7_IO2
  *         @arg @ref LL_TSC_GROUP7_IO3
  *         @arg @ref LL_TSC_GROUP7_IO4
  *         @arg @ref LL_TSC_GROUP8_IO1
  *         @arg @ref LL_TSC_GROUP8_IO2
  *         @arg @ref LL_TSC_GROUP8_IO3
  *         @arg @ref LL_TSC_GROUP8_IO4
  */
__STATIC_INLINE void LL_TSC_DisableChannel(TSC_TypeDef *tscx, const uint32_t gx_ioy_mask)
{
  CLEAR_BIT(tscx->IOCCR, gx_ioy_mask);
}

/**
  * @brief Check if the Channel IOs is enable or disable.
  * @rmtoll
  *  IOCCR          Gx_IOy         LL_TSC_IsEnabledChannel
  * @param  tscx TSC Instance.
  * @param  gx_ioy_mask IOs mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1_IO1
  *         @arg @ref LL_TSC_GROUP1_IO2
  *         @arg @ref LL_TSC_GROUP1_IO3
  *         @arg @ref LL_TSC_GROUP1_IO4
  *         @arg @ref LL_TSC_GROUP2_IO1
  *         @arg @ref LL_TSC_GROUP2_IO2
  *         @arg @ref LL_TSC_GROUP2_IO3
  *         @arg @ref LL_TSC_GROUP2_IO4
  *         @arg @ref LL_TSC_GROUP3_IO1
  *         @arg @ref LL_TSC_GROUP3_IO2
  *         @arg @ref LL_TSC_GROUP3_IO3
  *         @arg @ref LL_TSC_GROUP3_IO4
  *         @arg @ref LL_TSC_GROUP4_IO1
  *         @arg @ref LL_TSC_GROUP4_IO2
  *         @arg @ref LL_TSC_GROUP4_IO3
  *         @arg @ref LL_TSC_GROUP4_IO4
  *         @arg @ref LL_TSC_GROUP5_IO1
  *         @arg @ref LL_TSC_GROUP5_IO2
  *         @arg @ref LL_TSC_GROUP5_IO3
  *         @arg @ref LL_TSC_GROUP5_IO4
  *         @arg @ref LL_TSC_GROUP6_IO1
  *         @arg @ref LL_TSC_GROUP6_IO2
  *         @arg @ref LL_TSC_GROUP6_IO3
  *         @arg @ref LL_TSC_GROUP6_IO4
  *         @arg @ref LL_TSC_GROUP7_IO1
  *         @arg @ref LL_TSC_GROUP7_IO2
  *         @arg @ref LL_TSC_GROUP7_IO3
  *         @arg @ref LL_TSC_GROUP7_IO4
  *         @arg @ref LL_TSC_GROUP8_IO1
  *         @arg @ref LL_TSC_GROUP8_IO2
  *         @arg @ref LL_TSC_GROUP8_IO3
  *         @arg @ref LL_TSC_GROUP8_IO4
  * @retval State of these bits (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsEnabledChannel(const TSC_TypeDef *tscx, const uint32_t gx_ioy_mask)
{
  return ((READ_BIT(tscx->IOCCR, gx_ioy_mask) == (gx_ioy_mask)) ? 1UL : 0UL);
}

/**
  * @brief Enable acquisition groups.
  * @rmtoll
  *  IOGCSR       GxE         LL_TSC_EnableGroup
  * @param  tscx TSC Instance.
  * @param  gx_mask Groups mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1
  *         @arg @ref LL_TSC_GROUP2
  *         @arg @ref LL_TSC_GROUP3
  *         @arg @ref LL_TSC_GROUP4
  *         @arg @ref LL_TSC_GROUP5
  *         @arg @ref LL_TSC_GROUP6
  *         @arg @ref LL_TSC_GROUP7
  * @if TSC_IOCCR_G8_IO1
  *         @arg @ref LL_TSC_GROUP8
  * @endif
  */
__STATIC_INLINE void LL_TSC_EnableGroup(TSC_TypeDef *tscx, const uint32_t gx_mask)
{
  SET_BIT(tscx->IOGCSR, gx_mask);
}

/**
  * @brief Disable acquisition groups.
  * @rmtoll
  *  IOGCSR       GxE         LL_TSC_DisableGroup
  * @param  tscx TSC Instance.
  * @param  gx_mask Groups mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1
  *         @arg @ref LL_TSC_GROUP2
  *         @arg @ref LL_TSC_GROUP3
  *         @arg @ref LL_TSC_GROUP4
  *         @arg @ref LL_TSC_GROUP5
  *         @arg @ref LL_TSC_GROUP6
  *         @arg @ref LL_TSC_GROUP7
  * @if TSC_IOCCR_G8_IO1
  *         @arg @ref LL_TSC_GROUP8
  * @endif
  */
__STATIC_INLINE void LL_TSC_DisableGroup(TSC_TypeDef *tscx, const uint32_t gx_mask)
{
  CLEAR_BIT(tscx->IOGCSR, gx_mask);
}

/**
  * @brief Check if the group is enable or disable.
  * @rmtoll
  *  IOGCSR          Gx_IOy         LL_TSC_IsEnabledGroup
  * @param  tscx TSC Instance.
  * @param  gx_mask Groups mask, This parameter can be a combination of the following values:
  *         @arg @ref LL_TSC_GROUP1
  *         @arg @ref LL_TSC_GROUP2
  *         @arg @ref LL_TSC_GROUP3
  *         @arg @ref LL_TSC_GROUP4
  *         @arg @ref LL_TSC_GROUP5
  *         @arg @ref LL_TSC_GROUP6
  *         @arg @ref LL_TSC_GROUP7
  * @if TSC_IOCCR_G8_IO1
  *         @arg @ref LL_TSC_GROUP8
  * @endif
  * @retval State of these bits (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_IsEnabledGroup(const TSC_TypeDef *tscx, const uint32_t gx_mask)
{
  return ((READ_BIT(tscx->IOGCSR, gx_mask) == (gx_mask)) ? 1UL : 0UL);
}

/**
  * @brief Get acquisition group status.
  * @rmtoll
  *  IOGCSR       GxS         LL_TSC_GetGroupStatus
  * @param  tscx TSC Instance.
  * @param  gx_index Group index, This parameter can be one of the following values:
  *         @arg @ref LL_TSC_GROUP1_IDX
  *         @arg @ref LL_TSC_GROUP2_IDX
  *         @arg @ref LL_TSC_GROUP3_IDX
  *         @arg @ref LL_TSC_GROUP4_IDX
  *         @arg @ref LL_TSC_GROUP5_IDX
  *         @arg @ref LL_TSC_GROUP6_IDX
  *         @arg @ref LL_TSC_GROUP7_IDX
  * @if TSC_IOCCR_G8_IO1
  *         @arg @ref LL_TSC_GROUP8_IDX
  * @endif
  * @retval State of group index (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TSC_GetGroupStatus(const TSC_TypeDef *tscx, const uint32_t gx_index)
{
  return ((READ_BIT(tscx->IOGCSR, (uint32_t)(1UL << (((gx_index) & 0xFUL) + 16UL))) == \
           (uint32_t)(1UL << (((gx_index) & 0xFUL) + 16UL))) ? 1UL : 0UL);
}

/**
  * @brief Get the group acquisition counter.
  * @rmtoll
  *  IOGXCR       CNT         LL_TSC_GetGroupAcquisitionCounter
  * @param  tscx TSC Instance.
  * @param  gx_index Group index, This parameter can be one of the following values:
  *         @arg @ref LL_TSC_GROUP1_IDX
  *         @arg @ref LL_TSC_GROUP2_IDX
  *         @arg @ref LL_TSC_GROUP3_IDX
  *         @arg @ref LL_TSC_GROUP4_IDX
  *         @arg @ref LL_TSC_GROUP5_IDX
  *         @arg @ref LL_TSC_GROUP6_IDX
  *         @arg @ref LL_TSC_GROUP7_IDX
  * @if TSC_IOCCR_G8_IO1
  *         @arg @ref LL_TSC_GROUP8_IDX
  * @endif
  * @retval value of the group acquisition counter.
  */
__STATIC_INLINE uint32_t LL_TSC_GetGroupAcquisitionCounter(const TSC_TypeDef *tscx, const uint32_t gx_index)
{
  return (uint32_t)(READ_BIT(tscx->IOGXCR[gx_index], TSC_IOGXCR_CNT));
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

#endif /* STM32U5XX_LL_TSC_H */

