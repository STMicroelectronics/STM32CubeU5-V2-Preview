/**
  ******************************************************************************
  * @file    stm32u5xx_ll_tamp.h
  * @brief   Header file of TAMP LL module.
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
#ifndef STM32U5XX_LL_TAMP_H
#define STM32U5XX_LL_TAMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined(TAMP)

/** @defgroup TAMP_LL TAMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
#define LL_POSITION_FIRST_ITAMP        TAMP_CR1_ITAMP1E_Pos
#define LL_POSITION_OFFSET_REG_ITAMP   16U
#define TAMP_CR2_CFG_MSK               (LL_TAMP_NOERASE_TAMPER_ALL \
                                        | LL_TAMP_ACTIVELEVEL_TAMP_ALL | LL_TAMP_MASK_TAMPER_ALL)

/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
#define LL_TAMP_NUMBER_TAMPERS         8U /*!< Number of tampers */
#define LL_TAMP_POSITION_FIRST_MASKED  TAMP_CR2_TAMP1MSK_Pos /*!< Tamper first masked */
#define LL_TAMP_BACKUP_NB              TAMP_BACKUP_NB /*!< Backup registers number */

/** @defgroup TAMP_LL_EC_TAMPER  TAMPER
  * @{
  */
#define LL_TAMP_1                    TAMP_CR1_TAMP1E /*!< Tamper 1 input detection */
#define LL_TAMP_2                    TAMP_CR1_TAMP2E /*!< Tamper 2 input detection */
#define LL_TAMP_3                    TAMP_CR1_TAMP3E /*!< Tamper 3 input detection */
#define LL_TAMP_4                    TAMP_CR1_TAMP4E /*!< Tamper 4 input detection */
#define LL_TAMP_5                    TAMP_CR1_TAMP5E /*!< Tamper 5 input detection */
#define LL_TAMP_6                    TAMP_CR1_TAMP6E /*!< Tamper 6 input detection */
#define LL_TAMP_7                    TAMP_CR1_TAMP7E /*!< Tamper 7 input detection */
#define LL_TAMP_8                    TAMP_CR1_TAMP8E /*!< Tamper 8 input detection */
#define LL_TAMP_ALL                  (TAMP_CR1_TAMP1E | TAMP_CR1_TAMP2E | TAMP_CR1_TAMP3E \
                                      | TAMP_CR1_TAMP4E | TAMP_CR1_TAMP5E | TAMP_CR1_TAMP6E \
                                      | TAMP_CR1_TAMP7E | TAMP_CR1_TAMP8E)
/*!< All tampers input selection */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_MASK  TAMPER MASK
  * @{
  */
#define LL_TAMP_MASK_NONE            0U
#define LL_TAMP_MASK_TAMPER          TAMP_CR2_TAMP1MSK /*!< Tamper 1 event generates a trigger event. TAMP1F is masked and internally cleared by hardware.The backup registers are not erased */
#define LL_TAMP_MASK_TAMPER1         TAMP_CR2_TAMP1MSK /*!< Tamper 1 event generates a trigger event. TAMP1F is masked and internally cleared by hardware.The backup registers are not erased */
#define LL_TAMP_MASK_TAMPER2         TAMP_CR2_TAMP2MSK /*!< Tamper 2 event generates a trigger event. TAMP2F is masked and internally cleared by hardware. The backup registers are not erased. */
#define LL_TAMP_MASK_TAMPER3         TAMP_CR2_TAMP3MSK /*!< Tamper 3 event generates a trigger event. TAMP3F is masked and internally cleared by hardware. The backup registers are not erased. */
#define LL_TAMP_MASK_TAMPER_ALL      (TAMP_CR2_TAMP1MSK | TAMP_CR2_TAMP2MSK | TAMP_CR2_TAMP3MSK)
/*!< Tamper 1-2-3 event generates a trigger event. TAMP1F-2F-3F are masked and internally cleared by hardware. The backup registers are not erased */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_NOERASE  TAMPER NO ERASE
  * @{
  */
#define LL_TAMP_ERASE_ACTIVATE_ALL   0U
#define LL_TAMP_NOERASE_TAMPER       TAMP_CR2_TAMP1NOERASE /*!< Tamper 1 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER1      TAMP_CR2_TAMP1NOERASE /*!< Tamper 1 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER2      TAMP_CR2_TAMP2NOERASE /*!< Tamper 2 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER3      TAMP_CR2_TAMP3NOERASE /*!< Tamper 3 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER4      TAMP_CR2_TAMP4NOERASE /*!< Tamper 4 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER5      TAMP_CR2_TAMP5NOERASE /*!< Tamper 5 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER6      TAMP_CR2_TAMP6NOERASE /*!< Tamper 6 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER7      TAMP_CR2_TAMP7NOERASE /*!< Tamper 7 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER8      TAMP_CR2_TAMP8NOERASE /*!< Tamper 8 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER_ALL   (TAMP_CR2_TAMP1NOERASE | TAMP_CR2_TAMP2NOERASE | TAMP_CR2_TAMP3NOERASE \
                                      | TAMP_CR2_TAMP4NOERASE | TAMP_CR2_TAMP5NOERASE | TAMP_CR2_TAMP6NOERASE \
                                      | TAMP_CR2_TAMP7NOERASE | TAMP_CR2_TAMP8NOERASE) /*!< All tampers events do not erase the backup registers. */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_BACKUP_BLOCK BACKUP BLOCKED
  * @{
  */

#define LL_TAMP_BACKUP_BLOCK_DISABLE   0U                /*!< Tamper backup block is disabled */
#define LL_TAMP_BACKUP_BLOCK_ENABLE    TAMP_CR2_BKBLOCK  /*!< Tamper backup block is enabled */

/**
  * @}
  */


/** @defgroup TAMP_LL_EC_TAMPER_DURATION  TAMPER DURATION
  * @{
  */
#define LL_TAMP_DURATION_1RTCCLK     0U                     /*!< Tamper pins are pre-charged before sampling during 1 RTCCLK cycle  */
#define LL_TAMP_DURATION_2RTCCLK     TAMP_FLTCR_TAMPPRCH_0  /*!< Tamper pins are pre-charged before sampling during 2 RTCCLK cycles */
#define LL_TAMP_DURATION_4RTCCLK     TAMP_FLTCR_TAMPPRCH_1  /*!< Tamper pins are pre-charged before sampling during 4 RTCCLK cycles */
#define LL_TAMP_DURATION_8RTCCLK     TAMP_FLTCR_TAMPPRCH    /*!< Tamper pins are pre-charged before sampling during 8 RTCCLK cycles */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_FILTER  TAMPER FILTER
  * @{
  */
#define LL_TAMP_FILTER_DISABLE       0U                      /*!< Tamper filter is disabled */
#define LL_TAMP_FILTER_2SAMPLES      TAMP_FLTCR_TAMPFLT_0    /*!< Tamper is activated after 2 consecutive samples at the active level */
#define LL_TAMP_FILTER_4SAMPLES      TAMP_FLTCR_TAMPFLT_1    /*!< Tamper is activated after 4 consecutive samples at the active level */
#define LL_TAMP_FILTER_8SAMPLES      TAMP_FLTCR_TAMPFLT      /*!< Tamper is activated after 8 consecutive samples at the active level. */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_SAMPLFREQDIV  TAMPER SAMPLING FREQUENCY DIVIDER
  * @{
  */
#define LL_TAMP_SAMPLFREQDIV_32768   0U                                              /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 32768 */
#define LL_TAMP_SAMPLFREQDIV_16384   TAMP_FLTCR_TAMPFREQ_0                           /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 16384 */
#define LL_TAMP_SAMPLFREQDIV_8192    TAMP_FLTCR_TAMPFREQ_1                           /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 8192 */
#define LL_TAMP_SAMPLFREQDIV_4096    (TAMP_FLTCR_TAMPFREQ_1 | TAMP_FLTCR_TAMPFREQ_0) /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 4096 */
#define LL_TAMP_SAMPLFREQDIV_2048    TAMP_FLTCR_TAMPFREQ_2                           /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 2048 */
#define LL_TAMP_SAMPLFREQDIV_1024    (TAMP_FLTCR_TAMPFREQ_2 | TAMP_FLTCR_TAMPFREQ_0) /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 1024 */
#define LL_TAMP_SAMPLFREQDIV_512     (TAMP_FLTCR_TAMPFREQ_2 | TAMP_FLTCR_TAMPFREQ_1) /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 512 */
#define LL_TAMP_SAMPLFREQDIV_256     TAMP_FLTCR_TAMPFREQ                             /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 256 */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_PULL_UP TAMPER PULL UP
  * @{
  */
#define LL_TAMP_PULL_UP_ENABLE        0U                    /*!< Precharge TAMP_INx pins before sampling (enable internal pull-up) */
#define LL_TAMP_PULL_UP_DISABLE       TAMP_FLTCR_TAMPPUDIS  /*!< Disable precharge of TAMP_INx pins                                */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_ACTIVELEVEL  TAMPER ACTIVE LEVEL
  * @{
  */
#define LL_TAMP_ACTIVELEVEL_DEACTIVATE_ALL  0U
#define LL_TAMP_ACTIVELEVEL_TAMP            TAMP_CR2_TAMP1TRG /*!< Tamper 1 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP1    TAMP_CR2_TAMP1TRG /*!< Tamper 1 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP2    TAMP_CR2_TAMP2TRG /*!< Tamper 2 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP3    TAMP_CR2_TAMP3TRG /*!< Tamper 3 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP4    TAMP_CR2_TAMP4TRG /*!< Tamper 4 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP5    TAMP_CR2_TAMP5TRG /*!< Tamper 5 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP6    TAMP_CR2_TAMP6TRG /*!< Tamper 6 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP7    TAMP_CR2_TAMP7TRG /*!< Tamper 7 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP8    TAMP_CR2_TAMP8TRG /*!< Tamper 8 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP_ALL (TAMP_CR2_TAMP1TRG | TAMP_CR2_TAMP2TRG | TAMP_CR2_TAMP3TRG \
                                      | TAMP_CR2_TAMP4TRG | TAMP_CR2_TAMP5TRG | TAMP_CR2_TAMP6TRG \
                                      | TAMP_CR2_TAMP7TRG | TAMP_CR2_TAMP8TRG) /*!< All tamper input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
/**
  * @}
  */


/** @defgroup TAMP_LL_EC_INTERNAL  INTERNAL TAMPER
  * @{
  */
#define LL_TAMP_ITAMP1                TAMP_CR1_ITAMP1E  /*!< Internal tamper 1: RTC supply voltage monitoring */
#define LL_TAMP_ITAMP2                TAMP_CR1_ITAMP2E  /*!< Internal tamper 2: Temperature monitoring */
#define LL_TAMP_ITAMP3                TAMP_CR1_ITAMP3E  /*!< Internal tamper 3: LSE monitoring */
#define LL_TAMP_ITAMP5                TAMP_CR1_ITAMP5E  /*!< Internal tamper 5: RTC calendar overflow */
#define LL_TAMP_ITAMP6                TAMP_CR1_ITAMP6E  /*!< Internal tamper 6: JTAG/SWD access when RDP > 0 */
#define LL_TAMP_ITAMP7                TAMP_CR1_ITAMP7E  /*!< Internal tamper 7: ADC4 analog watchdog monitoring 1 */
#define LL_TAMP_ITAMP8                TAMP_CR1_ITAMP8E  /*!< Internal tamper 8: Monotonic counter overflow */
#define LL_TAMP_ITAMP9                TAMP_CR1_ITAMP9E  /*!< Internal tamper 9: Cryptographic IPs fault*/
#define LL_TAMP_ITAMP11               TAMP_CR1_ITAMP11E /*!< Internal tamper 11: IWDG reset when tamper flag is set */
#define LL_TAMP_ITAMP12               TAMP_CR1_ITAMP12E /*!< Internal tamper 12: ADC4 analog watchdog monitoring 2*/
#define LL_TAMP_ITAMP13               TAMP_CR1_ITAMP13E /*!< Internal tamper 13: ADC4 analog watchdog monitoring 3 */
#define LL_TAMP_ITAMP_ALL             (TAMP_CR1_ITAMP1E | TAMP_CR1_ITAMP2E | TAMP_CR1_ITAMP3E \
                                       | TAMP_CR1_ITAMP5E | TAMP_CR1_ITAMP6E | TAMP_CR1_ITAMP7E \
                                       | TAMP_CR1_ITAMP8E | TAMP_CR1_ITAMP9E | TAMP_CR1_ITAMP11E \
                                       | TAMP_CR1_ITAMP12E | TAMP_CR1_ITAMP13E) /*!< All internal tampers */
/**
  * @}
  */

/**
  * @defgroup TAMP_LL_EC_INTERNAL_MODE INTERNAL TAMPER MODE
  * @{
  */
#define LL_TAMP_ITAMP_ERASE_ACTIVE_ALL    0U
#define LL_TAMP_ITAMP_NOERASE_TAMPER      TAMP_CR3_ITAMP1NOER  /*!< Internal tamper 1 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER1     TAMP_CR3_ITAMP1NOER  /*!< Internal tamper 1 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER2     TAMP_CR3_ITAMP2NOER  /*!< Internal tamper 2 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER3     TAMP_CR3_ITAMP3NOER  /*!< Internal tamper 3 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER5     TAMP_CR3_ITAMP5NOER  /*!< Internal tamper 5 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER6     TAMP_CR3_ITAMP6NOER  /*!< Internal tamper 6 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER7     TAMP_CR3_ITAMP7NOER  /*!< Internal tamper 7 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER8     TAMP_CR3_ITAMP8NOER  /*!< Internal tamper 8 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER9     TAMP_CR3_ITAMP9NOER  /*!< Internal tamper 9 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER11    TAMP_CR3_ITAMP11NOER /*!< Internal tamper 11 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER12    TAMP_CR3_ITAMP12NOER /*!< Internal tamper 12 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER13    TAMP_CR3_ITAMP13NOER /*!< Internal tamper 13 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER_ALL  (TAMP_CR3_ITAMP1NOER | TAMP_CR3_ITAMP2NOER | TAMP_CR3_ITAMP3NOER \
                                           | TAMP_CR3_ITAMP5NOER | TAMP_CR3_ITAMP6NOER | TAMP_CR3_ITAMP7NOER \
                                           | TAMP_CR3_ITAMP8NOER | TAMP_CR3_ITAMP9NOER | TAMP_CR3_ITAMP11NOER \
                                           | TAMP_CR3_ITAMP12NOER | TAMP_CR3_ITAMP13NOER)
/*!< All internal tampers events do not erase the device secrets. */

/**
  * @}
  */

/** @defgroup TAMP_LL_EC_ACTIVE_MODE   ACTIVE TAMPER MODE
  * @{
  */
#define LL_TAMP_ATAMP_TAMP1AM               TAMP_ATCR1_TAMP1AM /*!< tamper 1 is active */
#define LL_TAMP_ATAMP_TAMP2AM               TAMP_ATCR1_TAMP2AM /*!< tamper 2 is active */
#define LL_TAMP_ATAMP_TAMP3AM               TAMP_ATCR1_TAMP3AM /*!< tamper 3 is active */
#define LL_TAMP_ATAMP_TAMP4AM               TAMP_ATCR1_TAMP4AM /*!< tamper 4 is active */
#define LL_TAMP_ATAMP_TAMP5AM               TAMP_ATCR1_TAMP5AM /*!< tamper 5 is active */
#define LL_TAMP_ATAMP_TAMP6AM               TAMP_ATCR1_TAMP6AM /*!< tamper 6 is active */
#define LL_TAMP_ATAMP_TAMP7AM               TAMP_ATCR1_TAMP7AM /*!< tamper 7 is active */
#define LL_TAMP_ATAMP_TAMP8AM               TAMP_ATCR1_TAMP8AM /*!< tamper 8 is active */
#define LL_TAMP_ATAMP_TAMPAM_ALL            (TAMP_ATCR1_TAMP1AM | TAMP_ATCR1_TAMP2AM | TAMP_ATCR1_TAMP3AM \
                                             | TAMP_ATCR1_TAMP4AM | TAMP_ATCR1_TAMP5AM | TAMP_ATCR1_TAMP6AM \
                                             | TAMP_ATCR1_TAMP7AM | TAMP_ATCR1_TAMP8AM)
/*!< All tampers are active */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_ATCR1_REGISTER_ACTIVE_TAMP_OUTPUT_PERIOD  Active TAMPER output period
  * @{
  */
#define LL_TAMP_OUTPUT_PERIOD  (TAMP_ATCR1_ATPER_Msk >> TAMP_ATCR1_ATPER_Pos) /*!< Active tamper output period */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_ACTIVE_ASYNC_PRESCALER   ACTIVE TAMPER ASYNCHRONOUS PRESCALER CLOCK
  * @{
  */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK       0U                                                                      /*!< RTCCLK     */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_2     TAMP_ATCR1_ATCKSEL_0                                                    /*!< RTCCLK/2   */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_4     TAMP_ATCR1_ATCKSEL_1                                                    /*!< RTCCLK/4   */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_8     (TAMP_ATCR1_ATCKSEL_1 | TAMP_ATCR1_ATCKSEL_0)                           /*!< RTCCLK/8   */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_16    TAMP_ATCR1_ATCKSEL_2                                                    /*!< RTCCLK/16  */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_32    (TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_0)                           /*!< RTCCLK/32  */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_64    (TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_1)                           /*!< RTCCLK/64  */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_128   (TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_1 | TAMP_ATCR1_ATCKSEL_0)    /*!< RTCCLK/128 */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_2048  (TAMP_ATCR1_ATCKSEL_3 | TAMP_ATCR1_ATCKSEL_1 | TAMP_ATCR1_ATCKSEL_0)    /*!< RTCCLK/2048 */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_ACTIVE_FILTERING ACTIVE TAMPER FILTERING
  * @{
  */
#define LL_TAMP_ATAMP_FILTERING_DISABLE  0U                      /*!< Active tamper filtering disable */
#define LL_TAMP_ATAMP_FILTERING_ENABLE   TAMP_ATCR1_FLTEN        /*!< Active tamper filter enable     */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_ACTIVE_SHARING ACTIVE TAMPER SHARING
  * @{
  */
#define LL_TAMP_ATAMP_SHARING_DISABLE     0U                     /*!< Each active tamper input TAMP_INi is compared with its dedicated output TAMP_OUTi */
#define LL_TAMP_ATAMP_SHARING_ENABLE      TAMP_ATCR1_ATOSHARE    /*!< Each active tamper input TAMP_INi is compared with TAMPOUTSELi defined by ATOSELi bits. */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_ACTIVE_OUTPUT_SELECTION   ACTIVE TAMPER OUTPUT SELECTION
  * @{
  */
#define TAMP_ATCR2_ATOSEL_MSK       (TAMP_ATCR2_ATOSEL1 | TAMP_ATCR2_ATOSEL2 | TAMP_ATCR2_ATOSEL3 |\
                                     TAMP_ATCR2_ATOSEL4 | TAMP_ATCR2_ATOSEL5 | TAMP_ATCR2_ATOSEL6 |\
                                     TAMP_ATCR2_ATOSEL7 | TAMP_ATCR2_ATOSEL8)

#define LL_TAMP_ATAMP1IN_ATAMP1OUT  (0U << TAMP_ATCR2_ATOSEL1_Pos) /*!< Active tamper 1 output is set to TAMP_OUT1 */
#define LL_TAMP_ATAMP1IN_ATAMP2OUT  (1U << TAMP_ATCR2_ATOSEL1_Pos) /*!< Active tamper 1 output is set to TAMP_OUT2 */
#define LL_TAMP_ATAMP1IN_ATAMP3OUT  (2U << TAMP_ATCR2_ATOSEL1_Pos) /*!< Active tamper 1 output is set to TAMP_OUT3 */
#define LL_TAMP_ATAMP1IN_ATAMP4OUT  (3U << TAMP_ATCR2_ATOSEL1_Pos) /*!< Active tamper 1 output is set to TAMP_OUT4 */
#define LL_TAMP_ATAMP1IN_ATAMP5OUT  (4U << TAMP_ATCR2_ATOSEL1_Pos) /*!< Active tamper 1 output is set to TAMP_OUT5 */
#define LL_TAMP_ATAMP1IN_ATAMP6OUT  (5U << TAMP_ATCR2_ATOSEL1_Pos) /*!< Active tamper 1 output is set to TAMP_OUT6 */
#define LL_TAMP_ATAMP1IN_ATAMP7OUT  (6U << TAMP_ATCR2_ATOSEL1_Pos) /*!< Active tamper 1 output is set to TAMP_OUT7 */
#define LL_TAMP_ATAMP1IN_ATAMP8OUT  (7U << TAMP_ATCR2_ATOSEL1_Pos) /*!< Active tamper 1 output is set to TAMP_OUT8 */

#define LL_TAMP_ATAMP2IN_ATAMP1OUT  (0U << TAMP_ATCR2_ATOSEL2_Pos) /*!< Active tamper 2 output is set to TAMP_OUT1 */
#define LL_TAMP_ATAMP2IN_ATAMP2OUT  (1U << TAMP_ATCR2_ATOSEL2_Pos) /*!< Active tamper 2 output is set to TAMP_OUT2 */
#define LL_TAMP_ATAMP2IN_ATAMP3OUT  (2U << TAMP_ATCR2_ATOSEL2_Pos) /*!< Active tamper 2 output is set to TAMP_OUT3 */
#define LL_TAMP_ATAMP2IN_ATAMP4OUT  (3U << TAMP_ATCR2_ATOSEL2_Pos) /*!< Active tamper 2 output is set to TAMP_OUT4 */
#define LL_TAMP_ATAMP2IN_ATAMP5OUT  (4U << TAMP_ATCR2_ATOSEL2_Pos) /*!< Active tamper 2 output is set to TAMP_OUT5 */
#define LL_TAMP_ATAMP2IN_ATAMP6OUT  (5U << TAMP_ATCR2_ATOSEL2_Pos) /*!< Active tamper 2 output is set to TAMP_OUT6 */
#define LL_TAMP_ATAMP2IN_ATAMP7OUT  (6U << TAMP_ATCR2_ATOSEL2_Pos) /*!< Active tamper 2 output is set to TAMP_OUT7 */
#define LL_TAMP_ATAMP2IN_ATAMP8OUT  (7U << TAMP_ATCR2_ATOSEL2_Pos) /*!< Active tamper 2 output is set to TAMP_OUT8 */

#define LL_TAMP_ATAMP3IN_ATAMP1OUT  (0U << TAMP_ATCR2_ATOSEL3_Pos) /*!< Active tamper 3 output is set to TAMP_OUT1 */
#define LL_TAMP_ATAMP3IN_ATAMP2OUT  (1U << TAMP_ATCR2_ATOSEL3_Pos) /*!< Active tamper 3 output is set to TAMP_OUT2 */
#define LL_TAMP_ATAMP3IN_ATAMP3OUT  (2U << TAMP_ATCR2_ATOSEL3_Pos) /*!< Active tamper 3 output is set to TAMP_OUT3 */
#define LL_TAMP_ATAMP3IN_ATAMP4OUT  (3U << TAMP_ATCR2_ATOSEL3_Pos) /*!< Active tamper 3 output is set to TAMP_OUT4 */
#define LL_TAMP_ATAMP3IN_ATAMP5OUT  (4U << TAMP_ATCR2_ATOSEL3_Pos) /*!< Active tamper 3 output is set to TAMP_OUT5 */
#define LL_TAMP_ATAMP3IN_ATAMP6OUT  (5U << TAMP_ATCR2_ATOSEL3_Pos) /*!< Active tamper 3 output is set to TAMP_OUT6 */
#define LL_TAMP_ATAMP3IN_ATAMP7OUT  (6U << TAMP_ATCR2_ATOSEL3_Pos) /*!< Active tamper 3 output is set to TAMP_OUT7 */
#define LL_TAMP_ATAMP3IN_ATAMP8OUT  (7U << TAMP_ATCR2_ATOSEL3_Pos) /*!< Active tamper 3 output is set to TAMP_OUT8 */

#define LL_TAMP_ATAMP4IN_ATAMP1OUT  (0U << TAMP_ATCR2_ATOSEL4_Pos) /*!< Active tamper 4 output is set to TAMP_OUT1 */
#define LL_TAMP_ATAMP4IN_ATAMP2OUT  (1U << TAMP_ATCR2_ATOSEL4_Pos) /*!< Active tamper 4 output is set to TAMP_OUT2 */
#define LL_TAMP_ATAMP4IN_ATAMP3OUT  (2U << TAMP_ATCR2_ATOSEL4_Pos) /*!< Active tamper 4 output is set to TAMP_OUT3 */
#define LL_TAMP_ATAMP4IN_ATAMP4OUT  (3U << TAMP_ATCR2_ATOSEL4_Pos) /*!< Active tamper 4 output is set to TAMP_OUT4 */
#define LL_TAMP_ATAMP4IN_ATAMP5OUT  (4U << TAMP_ATCR2_ATOSEL4_Pos) /*!< Active tamper 4 output is set to TAMP_OUT5 */
#define LL_TAMP_ATAMP4IN_ATAMP6OUT  (5U << TAMP_ATCR2_ATOSEL4_Pos) /*!< Active tamper 4 output is set to TAMP_OUT6 */
#define LL_TAMP_ATAMP4IN_ATAMP7OUT  (6U << TAMP_ATCR2_ATOSEL4_Pos) /*!< Active tamper 4 output is set to TAMP_OUT7 */
#define LL_TAMP_ATAMP4IN_ATAMP8OUT  (7U << TAMP_ATCR2_ATOSEL4_Pos) /*!< Active tamper 4 output is set to TAMP_OUT8 */

#define LL_TAMP_ATAMP5IN_ATAMP1OUT  (0U << TAMP_ATCR2_ATOSEL5_Pos) /*!< Active tamper 5 output is set to TAMP_OUT1 */
#define LL_TAMP_ATAMP5IN_ATAMP2OUT  (1U << TAMP_ATCR2_ATOSEL5_Pos) /*!< Active tamper 5 output is set to TAMP_OUT2 */
#define LL_TAMP_ATAMP5IN_ATAMP3OUT  (2U << TAMP_ATCR2_ATOSEL5_Pos) /*!< Active tamper 5 output is set to TAMP_OUT3 */
#define LL_TAMP_ATAMP5IN_ATAMP4OUT  (3U << TAMP_ATCR2_ATOSEL5_Pos) /*!< Active tamper 5 output is set to TAMP_OUT4 */
#define LL_TAMP_ATAMP5IN_ATAMP5OUT  (4U << TAMP_ATCR2_ATOSEL5_Pos) /*!< Active tamper 5 output is set to TAMP_OUT5 */
#define LL_TAMP_ATAMP5IN_ATAMP6OUT  (5U << TAMP_ATCR2_ATOSEL5_Pos) /*!< Active tamper 5 output is set to TAMP_OUT6 */
#define LL_TAMP_ATAMP5IN_ATAMP7OUT  (6U << TAMP_ATCR2_ATOSEL5_Pos) /*!< Active tamper 5 output is set to TAMP_OUT7 */
#define LL_TAMP_ATAMP5IN_ATAMP8OUT  (7U << TAMP_ATCR2_ATOSEL5_Pos) /*!< Active tamper 5 output is set to TAMP_OUT8 */

#define LL_TAMP_ATAMP6IN_ATAMP1OUT  (0U << TAMP_ATCR2_ATOSEL6_Pos) /*!< Active tamper 6 output is set to TAMP_OUT1 */
#define LL_TAMP_ATAMP6IN_ATAMP2OUT  (1U << TAMP_ATCR2_ATOSEL6_Pos) /*!< Active tamper 6 output is set to TAMP_OUT2 */
#define LL_TAMP_ATAMP6IN_ATAMP3OUT  (2U << TAMP_ATCR2_ATOSEL6_Pos) /*!< Active tamper 6 output is set to TAMP_OUT3 */
#define LL_TAMP_ATAMP6IN_ATAMP4OUT  (3U << TAMP_ATCR2_ATOSEL6_Pos) /*!< Active tamper 6 output is set to TAMP_OUT4 */
#define LL_TAMP_ATAMP6IN_ATAMP5OUT  (4U << TAMP_ATCR2_ATOSEL6_Pos) /*!< Active tamper 6 output is set to TAMP_OUT5 */
#define LL_TAMP_ATAMP6IN_ATAMP6OUT  (5U << TAMP_ATCR2_ATOSEL6_Pos) /*!< Active tamper 6 output is set to TAMP_OUT6 */
#define LL_TAMP_ATAMP6IN_ATAMP7OUT  (6U << TAMP_ATCR2_ATOSEL6_Pos) /*!< Active tamper 6 output is set to TAMP_OUT7 */
#define LL_TAMP_ATAMP6IN_ATAMP8OUT  (7U << TAMP_ATCR2_ATOSEL6_Pos) /*!< Active tamper 6 output is set to TAMP_OUT8 */

#define LL_TAMP_ATAMP7IN_ATAMP1OUT  (0U << TAMP_ATCR2_ATOSEL7_Pos) /*!< Active tamper 7 output is set to TAMP_OUT1 */
#define LL_TAMP_ATAMP7IN_ATAMP2OUT  (1U << TAMP_ATCR2_ATOSEL7_Pos) /*!< Active tamper 7 output is set to TAMP_OUT2 */
#define LL_TAMP_ATAMP7IN_ATAMP3OUT  (2U << TAMP_ATCR2_ATOSEL7_Pos) /*!< Active tamper 7 output is set to TAMP_OUT3 */
#define LL_TAMP_ATAMP7IN_ATAMP4OUT  (3U << TAMP_ATCR2_ATOSEL7_Pos) /*!< Active tamper 7 output is set to TAMP_OUT4 */
#define LL_TAMP_ATAMP7IN_ATAMP5OUT  (4U << TAMP_ATCR2_ATOSEL7_Pos) /*!< Active tamper 7 output is set to TAMP_OUT5 */
#define LL_TAMP_ATAMP7IN_ATAMP6OUT  (5U << TAMP_ATCR2_ATOSEL7_Pos) /*!< Active tamper 7 output is set to TAMP_OUT6 */
#define LL_TAMP_ATAMP7IN_ATAMP7OUT  (6U << TAMP_ATCR2_ATOSEL7_Pos) /*!< Active tamper 7 output is set to TAMP_OUT7 */
#define LL_TAMP_ATAMP7IN_ATAMP8OUT  (7U << TAMP_ATCR2_ATOSEL7_Pos) /*!< Active tamper 7 output is set to TAMP_OUT8 */

#define LL_TAMP_ATAMP8IN_ATAMP1OUT  (0U << TAMP_ATCR2_ATOSEL8_Pos) /*!< Active tamper 8 output is set to TAMP_OUT1 */
#define LL_TAMP_ATAMP8IN_ATAMP2OUT  (1U << TAMP_ATCR2_ATOSEL8_Pos) /*!< Active tamper 8 output is set to TAMP_OUT2 */
#define LL_TAMP_ATAMP8IN_ATAMP3OUT  (2U << TAMP_ATCR2_ATOSEL8_Pos) /*!< Active tamper 8 output is set to TAMP_OUT3 */
#define LL_TAMP_ATAMP8IN_ATAMP4OUT  (3U << TAMP_ATCR2_ATOSEL8_Pos) /*!< Active tamper 8 output is set to TAMP_OUT4 */
#define LL_TAMP_ATAMP8IN_ATAMP5OUT  (4U << TAMP_ATCR2_ATOSEL8_Pos) /*!< Active tamper 8 output is set to TAMP_OUT5 */
#define LL_TAMP_ATAMP8IN_ATAMP6OUT  (5U << TAMP_ATCR2_ATOSEL8_Pos) /*!< Active tamper 8 output is set to TAMP_OUT6 */
#define LL_TAMP_ATAMP8IN_ATAMP7OUT  (6U << TAMP_ATCR2_ATOSEL8_Pos) /*!< Active tamper 8 output is set to TAMP_OUT7 */
#define LL_TAMP_ATAMP8IN_ATAMP8OUT  (7U << TAMP_ATCR2_ATOSEL8_Pos) /*!< Active tamper 8 output is set to TAMP_OUT8 */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_IT TAMPER IT
  * @{
  */
#define LL_TAMP_IT_NONE         0U
#define LL_TAMP_IT_TAMPER_1     TAMP_IER_TAMP1IE /*!< Tamper 1 interrupt enable */
#define LL_TAMP_IT_TAMPER_2     TAMP_IER_TAMP2IE /*!< Tamper 2 interrupt enable */
#define LL_TAMP_IT_TAMPER_3     TAMP_IER_TAMP3IE /*!< Tamper 3 interrupt enable */
#define LL_TAMP_IT_TAMPER_4     TAMP_IER_TAMP4IE /*!< Tamper 4 interrupt enable */
#define LL_TAMP_IT_TAMPER_5     TAMP_IER_TAMP5IE /*!< Tamper 5 interrupt enable */
#define LL_TAMP_IT_TAMPER_6     TAMP_IER_TAMP6IE /*!< Tamper 6 interrupt enable */
#define LL_TAMP_IT_TAMPER_7     TAMP_IER_TAMP7IE /*!< Tamper 7 interrupt enable */
#define LL_TAMP_IT_TAMPER_8     TAMP_IER_TAMP8IE /*!< Tamper 8 interrupt enable */
#define LL_TAMP_IT_ALL          (TAMP_IER_TAMP1IE | TAMP_IER_TAMP2IE \
                                 | TAMP_IER_TAMP3IE | TAMP_IER_TAMP4IE \
                                 | TAMP_IER_TAMP5IE | TAMP_IER_TAMP6IE \
                                 | TAMP_IER_TAMP7IE | TAMP_IER_TAMP8IE)
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_INTERNAL_TAMPER_IT INTERNAL TAMPER IT
  * @{
  */
#define LL_TAMP_INTERNAL_IT_NONE         0U
#define LL_TAMP_INTERNAL_IT_TAMPER_1    TAMP_IER_ITAMP1IE  /*!< Internal tamper 1 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_2    TAMP_IER_ITAMP2IE  /*!< Internal tamper 2 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_3    TAMP_IER_ITAMP3IE  /*!< Internal tamper 3 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_5    TAMP_IER_ITAMP5IE  /*!< Internal tamper 5 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_6    TAMP_IER_ITAMP6IE  /*!< Internal tamper 6 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_7    TAMP_IER_ITAMP7IE  /*!< Internal tamper 7 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_8    TAMP_IER_ITAMP8IE  /*!< Internal tamper 8 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_9    TAMP_IER_ITAMP9IE  /*!< Internal tamper 9 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_11   TAMP_IER_ITAMP11IE /*!< Internal tamper 11 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_12   TAMP_IER_ITAMP12IE /*!< Internal tamper 12 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_13   TAMP_IER_ITAMP13IE /*!< Internal tamper 13 interrupt enable */
#define LL_TAMP_INTERNAL_IT_ALL         (TAMP_IER_ITAMP1IE  | TAMP_IER_ITAMP2IE | TAMP_IER_ITAMP3IE \
                                         | TAMP_IER_ITAMP5IE  | TAMP_IER_ITAMP6IE | TAMP_IER_ITAMP7IE \
                                         | TAMP_IER_ITAMP8IE  | TAMP_IER_ITAMP9IE | TAMP_IER_ITAMP11IE \
                                         | TAMP_IER_ITAMP12IE | TAMP_IER_ITAMP13IE)
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_RESOURCE_PROTECTION RESOURCE PROTECTION
  * @{
  */
#define LL_TAMP_RESOURCE_0        TAMP_ERCFGR0
#define LL_TAMP_RESOURCES_ALL    (LL_TAMP_RESOURCE_0)
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_BKP  BACKUP REGISTER
  * @{
  */
#define LL_TAMP_BKP_NUMBER                  TAMP_BACKUP_NB /*!< TAMP backup registers number */
#define LL_TAMP_BKP_DR0                     0U /*!< TAMP backup registers 0 */
#define LL_TAMP_BKP_DR1                     1U /*!< TAMP backup registers 1 */
#define LL_TAMP_BKP_DR2                     2U /*!< TAMP backup registers 2 */
#define LL_TAMP_BKP_DR3                     3U /*!< TAMP backup registers 3 */
#define LL_TAMP_BKP_DR4                     4U /*!< TAMP backup registers 4 */
#define LL_TAMP_BKP_DR5                     5U /*!< TAMP backup registers 5 */
#define LL_TAMP_BKP_DR6                     6U /*!< TAMP backup registers 6 */
#define LL_TAMP_BKP_DR7                     7U /*!< TAMP backup registers 7 */
#define LL_TAMP_BKP_DR8                     8U   /*!< TAMP backup registers 8 */
#define LL_TAMP_BKP_DR9                     9U   /*!< TAMP backup registers 9 */
#define LL_TAMP_BKP_DR10                    10U  /*!< TAMP backup registers 10 */
#define LL_TAMP_BKP_DR11                    11U  /*!< TAMP backup registers 11 */
#define LL_TAMP_BKP_DR12                    12U  /*!< TAMP backup registers 12 */
#define LL_TAMP_BKP_DR13                    13U  /*!< TAMP backup registers 13 */
#define LL_TAMP_BKP_DR14                    14U  /*!< TAMP backup registers 14 */
#define LL_TAMP_BKP_DR15                    15U  /*!< TAMP backup registers 15 */
#define LL_TAMP_BKP_DR16                    16U  /*!< TAMP backup registers 16 */
#define LL_TAMP_BKP_DR17                    17U  /*!< TAMP backup registers 17 */
#define LL_TAMP_BKP_DR18                    18U  /*!< TAMP backup registers 18 */
#define LL_TAMP_BKP_DR19                    19U  /*!< TAMP backup registers 19 */
#define LL_TAMP_BKP_DR20                    20U  /*!< TAMP backup registers 20 */
#define LL_TAMP_BKP_DR21                    21U  /*!< TAMP backup registers 21 */
#define LL_TAMP_BKP_DR22                    22U  /*!< TAMP backup registers 22 */
#define LL_TAMP_BKP_DR23                    23U  /*!< TAMP backup registers 23 */
#define LL_TAMP_BKP_DR24                    24U  /*!< TAMP backup registers 24 */
#define LL_TAMP_BKP_DR25                    25U  /*!< TAMP backup registers 25 */
#define LL_TAMP_BKP_DR26                    26U  /*!< TAMP backup registers 26 */
#define LL_TAMP_BKP_DR27                    27U  /*!< TAMP backup registers 27 */
#define LL_TAMP_BKP_DR28                    28U  /*!< TAMP backup registers 28 */
#define LL_TAMP_BKP_DR29                    29U  /*!< TAMP backup registers 29 */
#define LL_TAMP_BKP_DR30                    30U  /*!< TAMP backup registers 30 */
#define LL_TAMP_BKP_DR31                    31U  /*!< TAMP backup registers 31 */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_SECURE_TAMP  Secure tamp
  * @{
  */
#define LL_TAMP_SECURE_FULL_YES            TAMP_SECCFGR_TAMPSEC  /*!< TAMP full secure */
#define LL_TAMP_SECURE_FULL_NO             0U                    /*!< TAMP is not secure */
/**
  * @}
  */


/** @defgroup TAMP_LL_EC_SECURE_MONO_CNT_1  Secure Monotonic counter 1
  * @{
  */
#define LL_TAMP_MONO_CNT_1_SECURE_YES      TAMP_SECCFGR_CNT1SEC  /*!< Monotonic counter 1 secure */
#define LL_TAMP_MONO_CNT_1_SECURE_NO       0U                    /*!< Monotonic counter 1 is not secure */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_PRIVILEGE_TAMP_FULL  Privilege full tamp
  * @{
  */
#define LL_TAMP_PRIVILEGE_FULL_YES         TAMP_PRIVCFGR_TAMPPRIV /*!< TAMP full privilege */
#define LL_TAMP_PRIVILEGE_FULL_NO          0U                     /*!< TAMP is not privilege */
/**
  * @}
  */


/** @defgroup TAMP_LL_EC_PRIVILEGE_MONO_CNT_1  Privilege Monotonic counter 1
  * @{
  */
#define LL_TAMP_MONO_CNT_1_PRIVILEGE_YES   TAMP_PRIVCFGR_CNT1SEC  /*!< Monotonic counter 1 privilege */
#define LL_TAMP_MONO_CNT_1_PRIVILEGE_NO    0U                    /*!< Monotonic counter 1 is not privilege */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_PRIVILEGE_BACKUP_REG_ZONE  Privilege Backup register privilege zone
  * @{
  */
#define LL_TAMP_PRIVILEGE_BKUP_ZONE_NONE    0U /*!< Backup registers no privilege protection */
#define LL_TAMP_PRIVILEGE_BKUP_ZONE_1       TAMP_PRIVCFGR_BKPRWPRIV /*!< Backup registers zone 1 privilege protection */
#define LL_TAMP_PRIVILEGE_BKUP_ZONE_2       TAMP_PRIVCFGR_BKPWPRIV  /*!< Backup registers zone 2 privilege protection */
#define LL_TAMP_PRIVILEGE_BKUP_ZONE_ALL     (LL_TAMP_PRIVILEGE_BKUP_ZONE_1 |  LL_TAMP_PRIVILEGE_BKUP_ZONE_2)
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup TAMP_LL_Exported_Macros TAMP Exported Macros
  * @{
  */

/** @defgroup TAMP_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */


/**
  * @brief  Write a value in TAMP register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  */
#define LL_TAMP_WRITE_REG(__REG__, __VALUE__) WRITE_REG(TAMP->__REG__, (__VALUE__))

/**
  * @brief  Read a value in TAMP register

  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_TAMP_READ_REG(__REG__) READ_REG(TAMP->__REG__)
/**
  * @}
  */

/** @defgroup TAMP_LL_EM_helper Helper macros
  * @{
  */

/**
  * @brief Helper macro to retrieve pull_up precharge configuration
  * @param tamp_config_value Value returned by @ref LL_TAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_PULL_UP_ENABLE
  *        @arg @ref LL_TAMP_PULL_UP_DISABLE
  */
#define LL_TAMP_GET_PULL_UP(tamp_config_value) ((tamp_config_value) & TAMP_FLTCR_TAMPPUDIS)

/**
  * @brief Helper macro to retrieve pull_up precharge duration configuration
  * @param tamp_config_value Value returned by @ref LL_TAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_DURATION_1RTCCLK
  *        @arg @ref LL_TAMP_DURATION_2RTCCLK
  *        @arg @ref LL_TAMP_DURATION_4RTCCLK
  *        @arg @ref LL_TAMP_DURATION_8RTCCLK
  */
#define LL_TAMP_GET_PRECHARGE_DURATION(tamp_config_value) ((tamp_config_value) & TAMP_FLTCR_TAMPPRCH)

/**
  * @brief Helper macro to retrieve pull_up precharge configuration
  * @param tamp_config_value Value returned by @ref LL_TAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_FILTER_DISABLE
  *        @arg @ref LL_TAMP_FILTER_2SAMPLES
  *        @arg @ref LL_TAMP_FILTER_4SAMPLES
  *        @arg @ref LL_TAMP_FILTER_8SAMPLES
  */
#define LL_TAMP_GET_FILTER_SAMPLE(tamp_config_value) ((tamp_config_value) & TAMP_FLTCR_TAMPFLT)

/**
  * @brief Helper macro to retrieve pull_up precharge configuration
  * @param tamp_config_value Value returned by @ref LL_TAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_32768
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_16384
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_8192
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_4096
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_2048
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_1024
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_512
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_256
  */
#define LL_TAMP_GET_FILTER_SAMPLE_FREQUENCY(tamp_config_value) ((tamp_config_value) & TAMP_FLTCR_TAMPFREQ)

/**
  * @brief Helper macro to retrieve the trigger edge or level.
  * @param tamp_config_indiv_value Value returned by @ref LL_TAMP_GetConfigTampers
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_TAMP_ACTIVELEVEL_DEACTIVATE_ALL
  *         @arg @ref LL_TAMP_ACTIVELEVEL_TAMP
  */
#define LL_TAMP_GET_TRIGGER(tamp_config_indiv_value) ((((tamp_config_indiv_value) & \
                                                        LL_TAMP_ACTIVELEVEL_TAMP_ALL) != 0U ) ?\
                                                      LL_TAMP_ACTIVELEVEL_TAMP : LL_TAMP_ACTIVELEVEL_DEACTIVATE_ALL)

/**
  * @brief Helper macro to retrieve the mode of the tamper.
  * @param tamp_config_indiv_value Value returned by @ref LL_TAMP_GetConfigTampers
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_TAMP_ERASE_ACTIVATE_ALL
  *         @arg @ref LL_TAMP_NOERASE_TAMPER
  */
#define LL_TAMP_GET_NOERASE(tamp_config_indiv_value) ((((tamp_config_indiv_value) &\
                                                        LL_TAMP_NOERASE_TAMPER_ALL) != 0U ) ?\
                                                      LL_TAMP_NOERASE_TAMPER : LL_TAMP_ERASE_ACTIVATE_ALL)

/**
  * @brief Helper macro to retrieve the mask of the tamper.
  * @param tamp_config_indiv_value Value returned by @ref LL_TAMP_GetConfigTampers
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_TAMP_MASK_NONE
  *         @arg @ref LL_TAMP_MASK_TAMPER
  */
#define LL_TAMP_GET_MASK(tamp_config_indiv_value) ((((tamp_config_indiv_value) &\
                                                     LL_TAMP_MASK_TAMPER_ALL) != 0U ) ?\
                                                   LL_TAMP_MASK_TAMPER : LL_TAMP_MASK_NONE)

/**
  * @brief Helper macro to retrieve the mode of the internal tamper.
  * @param itamp_config_indiv_value Value returned by @ref LL_TAMP_GetConfigInternalTampers
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_TAMP_ITAMP_ERASE_ACTIVE_ALL
  *         @arg @ref LL_TAMP_ITAMP_NOERASE_TAMPER
  */
#define LL_TAMP_INTERNAL_GET_NOERASE(itamp_config_indiv_value) ((((itamp_config_indiv_value) &\
                                                                  LL_TAMP_ITAMP_NOERASE_TAMPER_ALL) != 0U ) \
                                                                ? LL_TAMP_ITAMP_NOERASE_TAMPER : \
                                                                LL_TAMP_ITAMP_ERASE_ACTIVE_ALL)

/**
  * @brief Helper macro to retrieve the active filtering status.
  * @param atamp_config_value Value returned by @ref LL_TAMP_ATAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_ATAMP_FILTERING_DISABLE
  *        @arg @ref LL_TAMP_ATAMP_FILTERING_ENABLE
  */
#define LL_TAMP_ACTIVE_GET_FILTER(atamp_config_value) ((atamp_config_value) & TAMP_ATCR1_FLTEN)

/**
  * @brief Helper macro to retrieve the period when the output signals changes.
  * @param atamp_config_value Value returned by @ref LL_TAMP_ATAMP_GetConfig
  * @retval Return value is between 0 and 7.
  */
#define LL_TAMP_ACTIVE_GET_OUTPUT_PERIOD(atamp_config_value) (((atamp_config_value) &\
                                                               TAMP_ATCR1_ATPER) >> TAMP_ATCR1_ATPER_Pos)

/**
  * @brief Helper macro to retrieve the asysnchronous prescaler.
  * @param atamp_config_value Value returned by @ref LL_TAMP_ATAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_2
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_4
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_8
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_16
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_32
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_64
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_128
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_2048
  */
#define LL_TAMP_ACTIVE_GET_PRESCALER(atamp_config_value) ((atamp_config_value) & TAMP_ATCR1_ATCKSEL)

/**
  * @brief Helper macro to retrieve the sharing status of the active tampers
  * @param atamp_config_value Value returned by @ref LL_TAMP_ATAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_ATAMP_SHARING_DISABLE
  *        @arg @ref LL_TAMP_ATAMP_SHARING_ENABLE
  */
#define LL_TAMP_ACTIVE_GET_SHARING(atamp_config_value) ((atamp_config_value) & TAMP_ATCR1_ATOSHARE)

/**
  * @}
  */


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup TAMP_LL_Exported_Functions TAMP Exported Functions
  * @{
  */

/** @defgroup TAMP_LL_EF_Tamper Tamper
  * @{
  */

/**
  * @brief  Enable TAMPx input detection
  * @rmtoll
  *  TAMP_CR1       TAMPxE        LL_TAMP_Enable
  * @param  Tampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER
  */
__STATIC_INLINE void LL_TAMP_Enable(uint32_t Tampers)
{
  SET_BIT(TAMP->CR1, Tampers);
}

/**
  * @brief  Clear TAMPx input detection
  * @rmtoll
  *  TAMP_CR1       TAMPxE         LL_TAMP_Disable
  * @param  Tampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER
  */
__STATIC_INLINE void LL_TAMP_Disable(uint32_t Tampers)
{
  CLEAR_BIT(TAMP->CR1, Tampers);
}

/**
  * @brief  Get TAMPx that are enabled
  * @rmtoll
  *  TAMP_CR1       TAMPxE         LL_TAMP_GetEnabled
  * @param  Tampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER
  * @retval State of the tampers enable.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetEnabled(uint32_t Tampers)
{
  return READ_BIT(TAMP->CR1, Tampers);
}

/**
  * @brief  Enable TAMPx interruption
  * @rmtoll
  *  TAMP_IER       TAMPxIE       LL_TAMP_EnableIT
  * @param  TampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_IT
  */
__STATIC_INLINE void LL_TAMP_EnableIT(uint32_t TampersIT)
{
  SET_BIT(TAMP->IER, TampersIT);
}

/**
  * @brief  Disable TAMPx interruption
  * @rmtoll
  *  TAMP_IER       TAMPxIE       LL_TAMP_DisableIT
  * @param  TampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_IT
  */
__STATIC_INLINE void LL_TAMP_DisableIT(uint32_t TampersIT)
{
  CLEAR_BIT(TAMP->IER, TampersIT);
}

/**
  * @brief  Get TAMPx interruption that are enabled.
  * @rmtoll
  *  TAMP_IER       TAMPxIE        LL_TAMP_IsEnabledIT
  * @param  TampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_IT
  * @retval State of the tampers interruption enable (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledIT(uint32_t TampersIT)
{
  return ((READ_BIT(TAMP->IER, TampersIT) == (TampersIT)) ? 1UL : 0UL);

}

/**
  * @brief  Enable Tamper mask flag
  * @note Associated Tamper IT must not enabled when tamper mask is set.
  * @rmtoll
  *  TAMP_CR2       TAMPxMSK       LL_TAMP_EnableMask
  * @param  Mask
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_MASK
  */
__STATIC_INLINE void LL_TAMP_EnableMask(uint32_t Mask)
{
  SET_BIT(TAMP->CR2, Mask);
}

/**
  * @brief  Disable Tamper mask flag
  * @rmtoll
  *  TAMP_CR2       TAMPxMSK       LL_TAMP_DisableMask
  * @param  Mask
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_MASK
  */
__STATIC_INLINE void LL_TAMP_DisableMask(uint32_t Mask)
{
  CLEAR_BIT(TAMP->CR2, Mask);
}

/**
  * @brief  Get TAMPx mask flag that are enabled
  * @rmtoll
  *  TAMP_CR2       TAMPxMSK       LL_TAMP_GetMasked
  * @param  Mask
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_MASK
  * @retval State of the tampers mask flag enable.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetMasked(uint32_t Mask)
{
  return READ_BIT(TAMP->CR2, (Mask & LL_TAMP_MASK_TAMPER_ALL));
}

/**
  * @brief  Enable TAMPx potential mode
  * @rmtoll
  *  TAMP_CR2       TAMPxNOERASE     LL_TAMP_EnablePotentialMode
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_NOERASE
  * @note   In potential mode, the backup registers and devices secret can be blocked instead of erased.
  *         See TAMP interconnection table for more information.
  */
__STATIC_INLINE void LL_TAMP_EnablePotentialMode(uint32_t Tamper)
{
  SET_BIT(TAMP->CR2, Tamper);
}

/**
  * @brief  Disable TAMPx potential mode
  * @rmtoll
  *  TAMP_CR2       TAMPxNOERASE     LL_TAMP_DisablePotentialMode
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_NOERASE
  */
__STATIC_INLINE void LL_TAMP_DisablePotentialMode(uint32_t Tamper)
{
  CLEAR_BIT(TAMP->CR2, Tamper);
}

/**
  * @brief  Check if the TAMPx potential mode is enabled or disabled
  * @rmtoll
  *  TAMP_CR2       TAMPxNOERASE     LL_TAMP_IsEnabledPotentialMode
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_NOERASE
  * @retval State of TAMPx potential mode (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledPotentialMode(uint32_t Tamper)
{
  return ((READ_BIT(TAMP->CR2, Tamper) == (Tamper)) ? 1UL : 0UL);
}

/**
  * @brief Configure global tamper parameters
  * @rmtoll
  *  TAMP_FLTCR     TAMPPUDIS    LL_TAMP_SetConfig \n
  *  TAMP_FLTCR     TAMPPRCH     LL_TAMP_SetConfig \n
  *  TAMP_FLTCR     TAMPFREQ     LL_TAMP_SetConfig \n
  *  TAMP_FLTCR     TAMPFLT      LL_TAMP_SetConfig
  * @param Pullup pull-up (precharge of TAMP pins) can be one of the following values:
  *        @arg @ref LL_TAMP_PULL_UP_ENABLE
  *        @arg @ref LL_TAMP_PULL_UP_DISABLE
  * @param Precharge time duration of the precharge can be one of the following values:
  *        @arg @ref LL_TAMP_DURATION_1RTCCLK
  *        @arg @ref LL_TAMP_DURATION_2RTCCLK
  *        @arg @ref LL_TAMP_DURATION_4RTCCLK
  *        @arg @ref LL_TAMP_DURATION_8RTCCLK
  * @param FilterCounter filter counter, can be one of the following values:
  *        @arg @ref LL_TAMP_FILTER_DISABLE
  *        @arg @ref LL_TAMP_FILTER_2SAMPLES
  *        @arg @ref LL_TAMP_FILTER_4SAMPLES
  *        @arg @ref LL_TAMP_FILTER_8SAMPLES
  * @param SampleFrequency sample frequency, can be one of the following values:
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_32768
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_16384
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_8192
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_4096
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_2048
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_1024
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_512
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_256
  */
__STATIC_INLINE void LL_TAMP_SetConfig(uint32_t Pullup, uint32_t Precharge, uint32_t FilterCounter,
                                       uint32_t SampleFrequency)
{
  WRITE_REG(TAMP->FLTCR,  Pullup | Precharge | FilterCounter | SampleFrequency);
}

/**
  * @brief Retrieve the global tamper parameters configuration
  * @rmtoll
  *  TAMP_FLTCR     TAMPPUDIS    LL_TAMP_GetConfig \n
  *  TAMP_FLTCR     TAMPPRCH     LL_TAMP_GetConfig \n
  *  TAMP_FLTCR     TAMPFREQ     LL_TAMP_GetConfig \n
  *  TAMP_FLTCR     TAMPFLT      LL_TAMP_GetConfig
  * @retval Combined values of the pull-up precharge, precharge duration, sample frequency and filter
  */
__STATIC_INLINE uint32_t LL_TAMP_GetConfig(void)
{
  return READ_REG(TAMP->FLTCR);
}

/**
  * @brief Configure one or multiple tampers.
  * @rmtoll
  *  TAMP_CR2     TAMPxTRG    LL_TAMP_SetConfigTampers \n
  *  TAMP_CR2     TAMPxMSK    LL_TAMP_SetConfigTampers \n
  *  TAMP_CR2     TAMPxNOERASE    LL_TAMP_SetConfigTampers
  * @param Tampers
  *        tampers can be one of the group values @ref TAMP_LL_EC_TAMPER
  * @param Trigger trigger mode, can be one of the following values:
  *        @arg @ref LL_TAMP_ACTIVELEVEL_DEACTIVATE_ALL
  *        @arg @ref LL_TAMP_ACTIVELEVEL_TAMP
  * @param EraseSecrets tamper mode, can be one of the following values:
  *        @arg @ref LL_TAMP_ERASE_ACTIVATE_ALL
  *        @arg @ref LL_TAMP_NOERASE_TAMPER
  * @param Masked tamper masked, can be one of the following values:
  *        @arg @ref LL_TAMP_MASK_NONE
  *        @arg @ref LL_TAMP_MASK_TAMPER
  */
__STATIC_INLINE void LL_TAMP_SetConfigTampers(uint32_t Tampers, uint32_t Trigger, uint32_t EraseSecrets,
                                              uint32_t Masked)
{
  uint32_t temp1 = ((Tampers << TAMP_CR2_TAMP1TRG_Pos) | (Tampers << TAMP_CR2_TAMP1NOERASE_Pos)
                    | ((Tampers << TAMP_CR2_TAMP1MSK_Pos) & LL_TAMP_MASK_TAMPER_ALL)) & (TAMP_CR2_CFG_MSK);
  uint32_t temp2 = (Tampers * (Trigger | Masked | EraseSecrets)) & (TAMP_CR2_CFG_MSK);
  MODIFY_REG(TAMP->CR2, temp1, temp2);
}

/**
  * @brief Retrieve one configuration tamper.
  * @rmtoll
  *  TAMP_CR2     TAMPxTRG    LL_TAMP_GetConfigTampers \n
  *  TAMP_CR2     TAMPxMSK    LL_TAMP_GetConfigTampers \n
  *  TAMP_CR2     TAMPxNOERASE    LL_TAMP_GetConfigTampers
  * @param Tampers
  *        tampers can be one of the group values @ref TAMP_LL_EC_TAMPER
  * @retval Combined values of the tamper masked, mode and trigger mode.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetConfigTampers(uint32_t Tampers)
{
  return READ_BIT(TAMP->CR2, ((Tampers << TAMP_CR2_TAMP1TRG_Pos) | (Tampers << TAMP_CR2_TAMP1NOERASE_Pos)
                              | (Tampers << TAMP_CR2_TAMP1MSK_Pos)) & TAMP_CR2_CFG_MSK);
}

/**
  * @brief  Enable TAMPx pull-up (Precharge TAMPx pins before sampling)
  * @rmtoll
  *  TAMP_FLTCR       TAMPPUDIS     LL_TAMP_EnablePullUp
  */
__STATIC_INLINE void LL_TAMP_EnablePullUp(void)
{
  CLEAR_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPPUDIS);
}

/**
  * @brief  Disable TAMPx pull-up (Disable precharge of TAMPx pins)
  * @rmtoll
  *  TAMP_FLTCR       TAMPPUDIS     LL_TAMP_DisablePullUp
  */
__STATIC_INLINE void LL_TAMP_DisablePullUp(void)
{
  SET_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPPUDIS);
}

/**
  * @brief  Check if the TAMPx pull-up is enabled or disabled
  * @rmtoll
  *  TAMP_FLTCR       TAMPPUDIS     LL_TAMP_IsEnabledPullUp
  * @retval State of TAMPx pull-up (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledPullUp(void)
{
  return ((READ_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPPUDIS) == (TAMP_FLTCR_TAMPPUDIS)) ? 0UL : 1UL);
}

/**
  * @brief  Set TAMPx precharge duration
  * @rmtoll
  *  TAMP_FLTCR       TAMPPRCH      LL_TAMP_SetPrecharge
  * @param  Duration This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_DURATION_1RTCCLK
  *         @arg @ref LL_TAMP_DURATION_2RTCCLK
  *         @arg @ref LL_TAMP_DURATION_4RTCCLK
  *         @arg @ref LL_TAMP_DURATION_8RTCCLK
  */
__STATIC_INLINE void LL_TAMP_SetPrecharge(uint32_t Duration)
{
  MODIFY_REG(TAMP->FLTCR, TAMP_FLTCR_TAMPPRCH, Duration);
}

/**
  * @brief  Get TAMPx precharge duration
  * @rmtoll
  *  TAMP_FLTCR       TAMPPRCH      LL_TAMP_GetPrecharge
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TAMP_DURATION_1RTCCLK
  *         @arg @ref LL_TAMP_DURATION_2RTCCLK
  *         @arg @ref LL_TAMP_DURATION_4RTCCLK
  *         @arg @ref LL_TAMP_DURATION_8RTCCLK
  */
__STATIC_INLINE uint32_t LL_TAMP_GetPrecharge(void)
{
  return (uint32_t)(READ_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPPRCH));
}

/**
  * @brief  Set TAMPx filter count
  * @rmtoll
  *  TAMP_FLTCR       TAMPFLT       LL_TAMP_SetFilterCount
  * @param  FilterCount This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_FILTER_DISABLE
  *         @arg @ref LL_TAMP_FILTER_2SAMPLES
  *         @arg @ref LL_TAMP_FILTER_4SAMPLES
  *         @arg @ref LL_TAMP_FILTER_8SAMPLES
  */
__STATIC_INLINE void LL_TAMP_SetFilterCount(uint32_t FilterCount)
{
  MODIFY_REG(TAMP->FLTCR, TAMP_FLTCR_TAMPFLT, FilterCount);
}

/**
  * @brief  Get TAMPx filter count
  * @rmtoll
  *  TAMP_FLTCR       TAMPFLT       LL_TAMP_GetFilterCount
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TAMP_FILTER_DISABLE
  *         @arg @ref LL_TAMP_FILTER_2SAMPLES
  *         @arg @ref LL_TAMP_FILTER_4SAMPLES
  *         @arg @ref LL_TAMP_FILTER_8SAMPLES
  */
__STATIC_INLINE uint32_t LL_TAMP_GetFilterCount(void)
{
  return (uint32_t)(READ_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPFLT));
}

/**
  * @brief  Set Tamper sampling frequency
  * @rmtoll
  *  TAMP_FLTCR       TAMPFREQ      LL_TAMP_SetSamplingFreq
  * @param  SamplingFreq This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_32768
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_16384
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_8192
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_4096
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_2048
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_1024
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_512
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_256
  */
__STATIC_INLINE void LL_TAMP_SetSamplingFreq(uint32_t SamplingFreq)
{
  MODIFY_REG(TAMP->FLTCR, TAMP_FLTCR_TAMPFREQ, SamplingFreq);
}

/**
  * @brief  Get Tamper sampling frequency
  * @rmtoll
  *  TAMP_FLTCR       TAMPFREQ      LL_TAMP_GetSamplingFreq
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_32768
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_16384
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_8192
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_4096
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_2048
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_1024
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_512
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_256
  */
__STATIC_INLINE uint32_t LL_TAMP_GetSamplingFreq(void)
{
  return (uint32_t)(READ_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPFREQ));
}

/**
  * @brief  Enable Active level for Tamper input
  * @rmtoll
  *  TAMP_CR2       TAMPxTRG       LL_TAMP_EnableActiveLevel
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_ACTIVELEVEL
  */
__STATIC_INLINE void LL_TAMP_EnableActiveLevel(uint32_t Tamper)
{
  SET_BIT(TAMP->CR2, Tamper);
}

/**
  * @brief  Disable Active level for Tamper input
  * @rmtoll
  *  TAMP_CR2       TAMPxTRG      LL_TAMP_DisableActiveLevel
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_ACTIVELEVEL
  */
__STATIC_INLINE void LL_TAMP_DisableActiveLevel(uint32_t Tamper)
{
  CLEAR_BIT(TAMP->CR2, Tamper);
}

/**
  * @brief  Check if the TAMPx Active level is enabled or disabled.
  * @rmtoll
  *  TAMP_CR2       TAMPxTRG     LL_TAMP_IsEnabledActiveLevel
  * @param  Tamper
  *         This parameter can be a one of the group values @ref TAMP_LL_EC_TAMPER_ACTIVELEVEL
  * @retval State of TAMPx Active level (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledActiveLevel(uint32_t Tamper)
{
  return ((READ_BIT(TAMP->CR2, Tamper) == (Tamper)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_Internal_Tamper Internal Tamper
  * @{
  */

/**
  * @brief Configure one or multiple internal tampers.
  * @rmtoll
  *  TAMP_CR3     ITAMPxNOERASE        LL_TAMP_SetConfigInternalTampers
  * @param InternalTampers
  *        This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  * @param EraseSecrets tamper mode, can be one of the following values:
  *        @arg @ref LL_TAMP_ITAMP_ERASE_ACTIVE_ALL
  *        @arg @ref LL_TAMP_ITAMP_NOERASE_TAMPER
  */
__STATIC_INLINE void LL_TAMP_SetConfigInternalTampers(uint32_t InternalTampers, uint32_t EraseSecrets)
{
  uint32_t temp = InternalTampers >> LL_POSITION_FIRST_ITAMP;
  MODIFY_REG(TAMP->CR3, temp, temp * EraseSecrets);
}

/**
  * @brief Retrieve one configuration internal tamper.
  * @rmtoll
  *  TAMP_CR3     ITAMPxNOERASE        LL_TAMP_GetConfigInternalTampers
  * @param InternalTampers
  *        This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  * @retval Values of the select internal tampers no erase mode.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetConfigInternalTampers(uint32_t InternalTampers)
{
  uint32_t temp = InternalTampers >> LL_POSITION_OFFSET_REG_ITAMP;
  return READ_BIT(TAMP->CR3, temp);
}

/**
  * @brief  Enable ITAMPx input detection
  * @rmtoll
  *  TAMP_CR1       ITAMPxE        LL_TAMP_ITAMP_Enable
  * @param  InternalTampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  */
__STATIC_INLINE void LL_TAMP_ITAMP_Enable(uint32_t InternalTampers)
{
  SET_BIT(TAMP->CR1, InternalTampers);
}

/**
  * @brief  Disable ITAMPx input detection
  * @rmtoll
  *  TAMP_CR1       ITAMPxE         LL_TAMP_ITAMP_Disable
  * @param  InternalTampers
  *          This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  */
__STATIC_INLINE void LL_TAMP_ITAMP_Disable(uint32_t InternalTampers)
{
  CLEAR_BIT(TAMP->CR1, InternalTampers);
}

/**
  * @brief  Get ITAMPx that are enabled
  * @rmtoll
  *  TAMP_CR1       ITAMPxE         LL_TAMP_ITAMP_GetEnabled
  * @param  InternalTampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_ITAMP_GetEnabled(uint32_t InternalTampers)
{
  return READ_BIT(TAMP->CR1, InternalTampers);
}

/**
  * @brief  Enable ITAMPx input detection interruption
  * @rmtoll
  *  TAMP_IER       ITAMPxE        LL_TAMP_ITAMP_EnableIT
  * @param  InternalTampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL_TAMPER_IT
  */
__STATIC_INLINE void LL_TAMP_ITAMP_EnableIT(uint32_t InternalTampersIT)
{
  SET_BIT(TAMP->IER, InternalTampersIT);
}

/**
  * @brief  Clear ITAMPx input detection interruption
  * @rmtoll
  *  TAMP_IER       ITAMPxE         LL_TAMP_ITAMP_DisableIT
  * @param  InternalTampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL_TAMPER_IT
  */
__STATIC_INLINE void LL_TAMP_ITAMP_DisableIT(uint32_t InternalTampersIT)
{
  CLEAR_BIT(TAMP->IER, InternalTampersIT);
}

/**
  * @brief  Get ITAMPx interruption that are enabled
  * @rmtoll
  *  TAMP_IER       ITAMPxE         LL_TAMP_ITAMP_IsEnabledIT
  * @param  InternalTampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL_TAMPER_IT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_ITAMP_IsEnabledIT(uint32_t InternalTampersIT)
{
  return ((READ_BIT(TAMP->IER, InternalTampersIT) == (InternalTampersIT)) ? 1UL : 0UL);
}

/**
  * @}
  */
/** @defgroup TAMP_LL_EF_Active_Tamper Active Tamper
  * @{
  */

/**
  * @brief  Enable tamper active mode.
  * @rmtoll
  *  TAMP_ATCR1     TAMPxAM       LL_TAMP_ATAMP_EnableActiveMode
  * @param Tampers to configure as active.
  *                This parameter can be a combination of @arg @ref TAMP_LL_EC_ACTIVE_MODE
  */
__STATIC_INLINE void LL_TAMP_ATAMP_EnableActiveMode(uint32_t Tampers)
{
  SET_BIT(TAMP->ATCR1, Tampers);
}

/**
  * @brief  Disable tamper active mode.
  * @rmtoll
  *  TAMP_ATCR1     TAMPxAM       LL_TAMP_ATAMP_DisableActiveMode
  * @param Tampers to configure as active.
  *                This parameter can be a combination of @arg @ref TAMP_LL_EC_ACTIVE_MODE
  */
__STATIC_INLINE void LL_TAMP_ATAMP_DisableActiveMode(uint32_t Tampers)
{
  CLEAR_BIT(TAMP->ATCR1, Tampers);
}

/**
  * @brief  Retrieve the active tampers configuration.
  * @rmtoll
  *  TAMP_ATCR1     TAMPxM       LL_TAMP_ATAMP_GetActive
  * @retval Combined values of the active tampers.
  */
__STATIC_INLINE uint32_t LL_TAMP_ATAMP_GetActiveMode(void)
{
  return READ_BIT(TAMP->ATCR1, LL_TAMP_ATAMP_TAMPAM_ALL);
}

/**
  * @brief  Configure active tampers.
  * @rmtoll
  *  TAMP_ATCR1     FLTEN         LL_TAMP_ATAMP_SetConfig \n
  *  TAMP_ATCR1     ATPER         LL_TAMP_ATAMP_SetConfig \n
  *  TAMP_ATCR1     ATCKSEL       LL_TAMP_ATAMP_SetConfig \n
  *  TAMP_ATCR1     ATOSHARE      LL_TAMP_ATAMP_SetConfig
  */
__STATIC_INLINE void LL_TAMP_ATAMP_SetConfig(uint32_t Filter, uint32_t OutputPeriod, uint32_t Shared,
                                             uint32_t Prescaler)
{
  MODIFY_REG(TAMP->ATCR1, TAMP_ATCR1_FLTEN | TAMP_ATCR1_ATPER | TAMP_ATCR1_ATCKSEL | TAMP_ATCR1_ATOSHARE,
             Filter | (OutputPeriod << TAMP_ATCR1_ATPER_Pos) | Shared | Prescaler);
}

/**
  * @brief  Retrieve the active tampers configuration.
  * @rmtoll
  *  TAMP_ATCR1     FLTEN         LL_TAMP_ATAMP_GetConfig \n
  *  TAMP_ATCR1     ATPER         LL_TAMP_ATAMP_GetConfig \n
  *  TAMP_ATCR1     ATCKSEL       LL_TAMP_ATAMP_GetConfig \n
  *  TAMP_ATCR1     ATOSHARE      LL_TAMP_ATAMP_GetConfig
  * @retval Combined values of the filter, sharing, prescaler and output period
  * of the active tampers.
  */
__STATIC_INLINE uint32_t LL_TAMP_ATAMP_GetConfig(void)
{
  return READ_BIT(TAMP->ATCR1, TAMP_ATCR1_FLTEN | TAMP_ATCR1_ATPER | TAMP_ATCR1_ATCKSEL | TAMP_ATCR1_ATOSHARE);
}

/**
  * @brief  Enable active tamper filter.
  * @rmtoll
  *  TAMP_ATCR1     FLTEN         LL_TAMP_ATAMP_EnableFilter
  */
__STATIC_INLINE void LL_TAMP_ATAMP_EnableFilter(void)
{
  SET_BIT(TAMP->ATCR1, TAMP_ATCR1_FLTEN);
}

/**
  * @brief  Disable active tamper filter.
  * @rmtoll
  *  TAMP_ATCR1     FLTEN         LL_TAMP_ATAMP_DisableFilter
  */
__STATIC_INLINE void LL_TAMP_ATAMP_DisableFilter(void)
{
  CLEAR_BIT(TAMP->ATCR1, TAMP_ATCR1_FLTEN);
}

/**
  * @brief Check if active tamper filter is enabled.
  * @rmtoll
  *  TAMP_ATCR1     FLTEN      LL_TAMP_ATAMP_IsEnabledFilter
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_ATAMP_IsEnabledFilter(void)
{
  return ((READ_BIT(TAMP->ATCR1, TAMP_ATCR1_FLTEN) == (TAMP_ATCR1_FLTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set Active tamper output change period.
  * @rmtoll
  *  TAMP_ATCR1     ATPER         LL_TAMP_ATAMP_SetOutputChangePeriod
  * @param  ActiveOutputChangePeriod This parameter can be a value from 0 to 7
  */
__STATIC_INLINE void LL_TAMP_ATAMP_SetOutputChangePeriod(uint32_t ActiveOutputChangePeriod)
{
  MODIFY_REG(TAMP->ATCR1, TAMP_ATCR1_ATPER, (ActiveOutputChangePeriod << TAMP_ATCR1_ATPER_Pos));
}

/**
  * @brief  Get Active tamper output change period.
  * @rmtoll
  *  TAMP_ATCR1     ATPER         LL_TAMP_ATAMP_GetOutputChangePeriod
  * @retval Output change period. This parameter can be a value from 0 to 7.
  */
__STATIC_INLINE uint32_t LL_TAMP_ATAMP_GetOutputChangePeriod(void)
{
  return (READ_BIT(TAMP->ATCR1, TAMP_ATCR1_ATPER) >> TAMP_ATCR1_ATPER_Pos);
}

/**
  * @brief  Set Active tamper asynchronous prescaler clock selection.
  * @rmtoll
  *  TAMP_ATCR1     ATCKSEL       LL_TAMP_ATAMP_SetAsyncPrescaler
  * @param  ActiveAsynvPrescaler Specifies the Active Tamper asynchronous Prescaler clock.
            This parameter can be a value of the group @ref TAMP_LL_EC_ACTIVE_ASYNC_PRESCALER
  */
__STATIC_INLINE void LL_TAMP_ATAMP_SetAsyncPrescaler(uint32_t ActiveAsynvPrescaler)
{
  MODIFY_REG(TAMP->ATCR1, TAMP_ATCR1_ATCKSEL, ActiveAsynvPrescaler);
}

/**
  * @brief  Get Active tamper asynchronous prescaler clock selection.
  * @rmtoll
  *  TAMP_ATCR1     ATCKSEL       LL_TAMP_ATAMP_GetAsyncPrescaler
  * @retval One of @ref TAMP_LL_EC_ACTIVE_ASYNC_PRESCALER
  */
__STATIC_INLINE uint32_t LL_TAMP_ATAMP_GetAsyncPrescaler(void)
{
  return (READ_BIT(TAMP->ATCR1, TAMP_ATCR1_ATCKSEL));
}

/**
  * @brief  Enable active tamper output sharing.
  * @rmtoll
  *  TAMP_ATCR1     ATOSHARE      LL_TAMP_ATAMP_EnableOutputSharing
  */
__STATIC_INLINE void LL_TAMP_ATAMP_EnableOutputSharing(void)
{
  SET_BIT(TAMP->ATCR1, TAMP_ATCR1_ATOSHARE);
}

/**
  * @brief  Disable active tamper output sharing.
  * @rmtoll
  *  TAMP_ATCR1     ATOSHARE      LL_TAMP_ATAMP_DisableOutputSharing
  */
__STATIC_INLINE void LL_TAMP_ATAMP_DisableOutputSharing(void)
{
  CLEAR_BIT(TAMP->ATCR1, TAMP_ATCR1_ATOSHARE);
}

/**
  * @brief Check if active tamper output sharing is enabled.
  * @rmtoll
  *  TAMP_ATCR1     ATOSHARE      LL_TAMP_ATAMP_IsEnabledOutputSharing
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_ATAMP_IsEnabledOutputSharing(void)
{
  return ((READ_BIT(TAMP->ATCR1, TAMP_ATCR1_ATOSHARE) == (TAMP_ATCR1_ATOSHARE)) ? 1UL : 0UL);
}

/**
  * @brief  Set Active tamper shared output.
  * @rmtoll
  *  TAMP_ATCR2     ATOSELx       LL_TAMP_ATAMP_SetSharedOutputs
  * @param  OutputSelection Specifies all the output selection of the Active Tamper.
  *         This parameter is a one of the group values @ref TAMP_LL_EC_ACTIVE_OUTPUT_SELECTION
  * @param  Positions Specifies all the bits that need to be changed on the register
  *          ATCR2
  */
__STATIC_INLINE void LL_TAMP_ATAMP_SetSharedOutputs(uint32_t Positions, uint32_t OutputSelection)
{
  MODIFY_REG(TAMP->ATCR2, Positions, OutputSelection);
}

/**
  * @brief  Set Active tamper shared output selection.
  * @rmtoll
  *  TAMP_ATCR2     ATOSELx       LL_TAMP_ATAMP_SetSharedOutputSelection
  * @param  OutputSelection Specifies all the output selection of the Active Tamper.
  *         This parameter is a one of the group values @ref TAMP_LL_EC_ACTIVE_OUTPUT_SELECTION
  */
__STATIC_INLINE void LL_TAMP_ATAMP_SetSharedOutputSelection(uint32_t OutputSelection)
{
  MODIFY_REG(TAMP->ATCR2, TAMP_ATCR2_ATOSEL_MSK, OutputSelection);
}

/**
  * @brief  Get Active tamper shared output selection.
  * @rmtoll
  *  TAMP_ATCR2     ATOSELx       LL_TAMP_ATAMP_GetSharedOutputSelection
  * @retval A combination of @arg @ref TAMP_LL_EC_ACTIVE_OUTPUT_SELECTION
  */
__STATIC_INLINE uint32_t LL_TAMP_ATAMP_GetSharedOutputSelection(void)
{
  return READ_REG(TAMP->ATCR2);
}

/**
  * @brief  Write active tamper seed.
  * @rmtoll
  *  TAMP_ATSEEDR   SEED          LL_TAMP_ATAMP_WriteSeed
  * @param  Seed
  */
__STATIC_INLINE void LL_TAMP_ATAMP_WriteSeed(uint32_t Seed)
{
  WRITE_REG(TAMP->ATSEEDR, Seed);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Read pseudo-random generator value.
  * @rmtoll
  *  TAMP_ATOR   PRNG          LL_TAMP_ReadPRNG
  * @retval Pseudo-random generator value.
  * @note: Because of potential inconsistencies due to synchronization delays, PRNG must be read at least twice.
  */
__STATIC_INLINE uint32_t LL_TAMP_ReadPRNG(void)
{
  return (READ_BIT(TAMP->ATOR, TAMP_ATOR_PRNG));
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Get active tamper initialization status flag.
  * @rmtoll
  *  TAMP_ATOR      INITS         LL_TAMP_IsActiveFlag_ATAMP_INITS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_ATAMP_INITS(void)
{
  return ((READ_BIT(TAMP->ATOR, TAMP_ATOR_INITS) == (TAMP_ATOR_INITS)) ? 1UL : 0UL);
}

/**
  * @brief  Get active tamper seed running status flag.
  * @rmtoll
  *  TAMP_ATOR      SEEDF         LL_TAMP_IsActiveFlag_ATAMP_SEEDF
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_ATAMP_SEEDF(void)
{
  return ((READ_BIT(TAMP->ATOR, TAMP_ATOR_SEEDF) == (TAMP_ATOR_SEEDF)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_Backup_Registers Backup_Registers
  * @{
  */

/**
  * @brief  Writes a data in a specified Backup data register.
  * @rmtoll
  *  TAMP_BKPxR        BKP           LL_TAMP_BKP_SetRegister
  * @param  BackupRegister This parameter can be one of the group values @ref TAMP_LL_EC_BKP
  * @param  Data Value between Min_Data=0x00 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE void LL_TAMP_BKP_SetRegister(uint32_t BackupRegister, uint32_t Data)
{
  uint32_t tmp;

  tmp = (uint32_t)(&(TAMP->BKP0R));
  tmp += (BackupRegister * 4U);

  /* Write the specified register */
  *(__IO uint32_t *)tmp = (uint32_t)Data;
}

/**
  * @brief  Reads data from the specified TAMP Backup data Register.
  * @rmtoll
  *  TAMP_BKPxR        BKP           LL_TAMP_BKP_GetRegister
  * @param  BackupRegister This parameter can be one of the group values @ref TAMP_LL_EC_BKP
  * @retval Value between Min_Data=0x00 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_TAMP_BKP_GetRegister(uint32_t BackupRegister)
{
  uint32_t tmp;

  tmp = (uint32_t)(&(TAMP->BKP0R));
  tmp += (BackupRegister * 4U);

  /* Read the specified register */
  return (*(__IO uint32_t *)tmp);
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Get tampers interrupt flags.
  * @rmtoll
  *  TAMP_SR          TAMPx       LL_TAMP_IsActiveFlag_TAMP
  * @param Tampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_TAMPER
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_TAMP(uint32_t Tampers)
{
  return ((READ_BIT(TAMP->SR, Tampers) != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Get internal tampers interrupt flags.
  * @rmtoll
  *  TAMP_SR          ITAMPx       LL_TAMP_IsActiveFlag_ITAMP
  * @param InternalTampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_INTERNAL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_ITAMP(uint32_t InternalTampers)
{
  return ((READ_BIT(TAMP->SR, InternalTampers) != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Get tampers interrupt masked flags.
  * @rmtoll
  *  TAMP_MISR          TAMPxMF       LL_TAMP_IsActiveFlag_TAMPM
  * @param Tampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_TAMPER
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_TAMPM(uint32_t Tampers)
{
  return ((READ_BIT(TAMP->MISR, Tampers) != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Get internal tampers interrupt masked flags.
  * @rmtoll
  *  TAMP_MISR          ITAMPxMF       LL_TAMP_IsActiveFlag_ITAMPM
  * @param InternalTampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_INTERNAL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_ITAMPM(uint32_t InternalTampers)
{
  return ((READ_BIT(TAMP->MISR, InternalTampers) != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Clear tampers interrupt masked flags.
  * @rmtoll
  *  TAMP_SCR          CTAMPxF       LL_TAMP_ClearFlag_TAMP
  * @param Tampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_TAMPER
  */
__STATIC_INLINE void LL_TAMP_ClearFlag_TAMP(uint32_t Tampers)
{
  WRITE_REG(TAMP->SCR, Tampers);
}

/**
  * @brief  Clear internal tampers interrupt masked flags.
  * @rmtoll
  *  TAMP_SCR          CITAMPxF       LL_TAMP_ClearFlag_ITAMP
  * @param InternalTampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_INTERNAL
  */
__STATIC_INLINE void LL_TAMP_ClearFlag_ITAMP(uint32_t InternalTampers)
{
  WRITE_REG(TAMP->SCR, InternalTampers);
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_SECURITY SECURITY_Management
  * @{
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Enable TAMPER secure level.
  * @rmtoll
  *  TAMP_SECCFGR          TAMPSEC           LL_TAMP_EnableTampSecure
  */
__STATIC_INLINE void LL_TAMP_EnableTampSecure(void)
{
  SET_BIT(TAMP->SECCFGR, TAMP_SECCFGR_TAMPSEC);
}

/**
  * @brief  Disable TAMPER secure level.
  * @rmtoll
  *  TAMP_SECCFGR          TAMPSEC           LL_TAMP_DisableTampSecure
  */
__STATIC_INLINE void LL_TAMP_DisableTampSecure(void)
{
  CLEAR_BIT(TAMP->SECCFGR, TAMP_SECCFGR_TAMPSEC);
}

#endif /* #if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Check if  TAMPER secure level is enabled.
  * @rmtoll
  *  TAMP_SECCFGR          TAMPSEC           LL_TAMP_IsEnabledTampSecure
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledTampSecure(void)
{
  return ((READ_BIT(TAMP->SECCFGR, TAMP_SECCFGR_TAMPSEC) == (TAMP_SECCFGR_TAMPSEC)) ? 1UL : 0UL);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/**
  * @brief  Enable Monotonic counter 1 secure level.
  * @rmtoll
  *  TAMP_SECCFGR          CNT1SEC           LL_TAMP_EnableMonotonicCounter1Secure
  */
__STATIC_INLINE void LL_TAMP_EnableMonotonicCounter1Secure(void)
{
  SET_BIT(TAMP->SECCFGR, TAMP_SECCFGR_CNT1SEC);
}

/**
  * @brief  Disable Monotonic counter 1 secure level.
  * @rmtoll
  *  TAMP_SECCFGR          CNT1SEC           LL_TAMP_DisableMonotonicCounter1Secure
  */
__STATIC_INLINE void LL_TAMP_DisableMonotonicCounter1Secure(void)
{
  CLEAR_BIT(TAMP->SECCFGR, TAMP_SECCFGR_CNT1SEC);
}
#endif /* #if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Check if  TAMPER secure level is enabled.
  * @rmtoll
  *  TAMP_SECCFGR          CNT1SEC           LL_TAMP_IsEnabledMonotonicCounter1Secure
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledMonotonicCounter1Secure(void)
{
  return ((READ_BIT(TAMP->SECCFGR, TAMP_SECCFGR_CNT1SEC) == (TAMP_SECCFGR_CNT1SEC)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_PRIVILEGE PRIVILEGE_Management
  * @{
  */

/**
  * @brief  Enable TAMPER privilege
  * @rmtoll
  *  TAMP_PRIVCFGR          TAMPPRIV           LL_TAMP_SetTampPrivilege
  */
__STATIC_INLINE void LL_TAMP_EnableTampPrivilege(void)
{
  SET_BIT(TAMP->PRIVCFGR, TAMP_PRIVCFGR_TAMPPRIV);
}

/**
  * @brief  Disable TAMPER privilege
  * @rmtoll
  *  TAMP_PRIVCFGR          TAMPPRIV           LL_TAMP_DisableTampPrivilege
  */
__STATIC_INLINE void LL_TAMP_DisableTampPrivilege(void)
{
  CLEAR_BIT(TAMP->PRIVCFGR, TAMP_PRIVCFGR_TAMPPRIV);
}

/**
  * @brief  Get TAMPER privilege level.
  * @rmtoll
  *  TAMP_PRIVCFGR          TAMPPRIV           LL_TAMP_IsEnabledTampPrivilege
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledTampPrivilege(void)
{
  return ((READ_BIT(TAMP->PRIVCFGR, TAMP_PRIVCFGR_TAMPPRIV) == (TAMP_PRIVCFGR_TAMPPRIV)) ? 1UL : 0UL);
}
/**
  * @brief  Enable Monotonic counter 1 privilege level.
  * @rmtoll
  *  TAMP_PRIVCFGR          CNT1PRIV           LL_TAMP_EnableMonotonicCounter1Privilege
  */
__STATIC_INLINE void LL_TAMP_EnableMonotonicCounter1Privilege(void)
{
  SET_BIT(TAMP->PRIVCFGR, TAMP_PRIVCFGR_CNT1PRIV);
}

/**
  * @brief  Disable Monotonic counter 1 privilege level.
  * @rmtoll
  *  TAMP_PRIVCFGR          CNT1SEC           LL_TAMP_DisableMonotonicCounter1Privilege
  */
__STATIC_INLINE void LL_TAMP_DisableMonotonicCounter1Privilege(void)
{
  CLEAR_BIT(TAMP->PRIVCFGR, TAMP_PRIVCFGR_CNT1PRIV);
}

/**
  * @brief  Check if  TAMPER Privilege level is enabled.
  * @rmtoll
  *  TAMP_PRIVCFGR          CNT1SEC           LL_TAMP_IsEnabledMonotonicCounter1Privilege
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledMonotonicCounter1Privilege(void)
{
  return ((READ_BIT(TAMP->PRIVCFGR, TAMP_PRIVCFGR_CNT1PRIV) == (TAMP_PRIVCFGR_CNT1PRIV)) ? 1UL : 0UL);
}

/**
  * @brief  Set Backup Registers privilege level.
  * @note   BackupRegisterPrivilege is only writable in secure mode or if trustzone is disabled
  * @rmtoll
  *  TAMP_PRIVCFGR          BKPWPRIV           LL_TAMP_SetBackupRegisterPrivilege \n
  *  TAMP_PRIVCFGR          BKPRWPRIV          LL_TAMP_SetBackupRegisterPrivilege
  * @param  BackupRegisterPrivilege This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_NONE
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_1
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_2
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_ALL
  */
__STATIC_INLINE void LL_TAMP_SetBackupRegisterPrivilege(uint32_t BackupRegisterPrivilege)
{
  MODIFY_REG(TAMP->PRIVCFGR, (TAMP_PRIVCFGR_BKPWPRIV | TAMP_PRIVCFGR_BKPRWPRIV), BackupRegisterPrivilege);
}

/**
  * @brief  Get Backup Registers privilege level.
  * @rmtoll
  *  TAMP_PRIVCFGR          BKPWPRIV           LL_TAMP_GetBackupRegisterPrivilege \n
  *  TAMP_PRIVCFGR          BKPRWPRIV          LL_TAMP_GetBackupRegisterPrivilege
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_NONE
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_1
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_2
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_ALL
  */
__STATIC_INLINE uint32_t LL_TAMP_GetBackupRegisterPrivilege(void)
{
  return READ_BIT(TAMP->PRIVCFGR, (TAMP_PRIVCFGR_BKPWPRIV | TAMP_PRIVCFGR_BKPRWPRIV));
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_BACKUP_REG_PROTECTION PROTECTION_BACKUP_REG_Management
  * @{
  */

/**
  * @brief  Set Backup registers protection level.
  * @note   Zone 1 : read protection write protection
  * @note   Zone 2 : read non-protection  write protection
  * @note   Zone 3 : read non-protection  write non-protection
  * @note   Zone 1 : start from 0 to startZone2 start value
  * @note   Zone 2 : start from startZone2 start value to startZone3 start value
  * @note   Zone 3 : start from to startZone3 to the end of BACKUPREG
  * @note   Warning : this parameter is only writable in secure mode or if trustzone is disabled
  * @rmtoll
  *  TAMP_SECCFGR          BKPWSEC           LL_TAMP_SetBackupRegProtection \n
  *  TAMP_SECCFGR          BKPRWSEC          LL_TAMP_SetBackupRegProtection
  * @param  startZone2 This parameter can be one of the group values @ref TAMP_LL_EC_BKP
  * @param  startZone3 This parameter can be one of the group values @ref TAMP_LL_EC_BKP
  */
__STATIC_INLINE void LL_TAMP_SetBackupRegProtection(uint32_t startZone2, uint32_t startZone3)
{
  MODIFY_REG(TAMP->SECCFGR, (TAMP_SECCFGR_BKPRWSEC_Msk | TAMP_SECCFGR_BKPWSEC_Msk), \
             (startZone2 << TAMP_SECCFGR_BKPRWSEC_Pos) | (startZone3 << TAMP_SECCFGR_BKPWSEC_Pos));
}

/**
  * @brief  Get Backup registers protection level start zone 2.
  * @note   Zone 1 : read protection write protection
  * @note   Zone 2 : read non-protection  write protection
  * @note   Zone 3 : read non-protection  write non-protection
  * @rmtoll
  *  TAMP_SECCFGR          BKPRWSEC         LL_TAMP_GetBackupRegProtectionStartZone2
  * @retval Start zone 2
  */
__STATIC_INLINE uint32_t LL_TAMP_GetBackupRegProtectionStartZone2(void)
{
  return READ_BIT(TAMP->SECCFGR, TAMP_SECCFGR_BKPRWSEC_Msk) >> TAMP_SECCFGR_BKPRWSEC_Pos;
}

/**
  * @brief  Get Backup registers protection level start zone 3.
  * @note   Zone 1 : read protection write protection
  * @note   Zone 2 : read non-protection  write protection
  * @note   Zone 3 : read non-protection  write non-protection
  * @rmtoll
  *  TAMP_SECCFGR          BKPWSEC           LL_TAMP_GetBackupRegProtectionStartZone3
  * @retval Start zone 3
  */
__STATIC_INLINE uint32_t LL_TAMP_GetBackupRegProtectionStartZone3(void)
{
  return READ_BIT(TAMP->SECCFGR, TAMP_SECCFGR_BKPWSEC_Msk) >> TAMP_SECCFGR_BKPWSEC_Pos;
}
/**
  * @}
  */

/** @defgroup TAMP_LL_EF_Device_Secret_Management Device_Secret Management
  * @{
  */

/**
  * @brief Block access to the backup registers and device secrets.
  * @rmtoll
  *  TAMP_CR2      BKBLOCK    LL_TAMP_BlockDeviceSecretsAccess
  */
__STATIC_INLINE void LL_TAMP_BlockDeviceSecretsAccess(void)
{
  SET_BIT(TAMP->CR2, TAMP_CR2_BKBLOCK);
}

/**
  * @brief Unblock access to the backup registers and device secrets.
  * @rmtoll
  *  TAMP_CR2      BKBLOCK    LL_TAMP_UnblockDeviceSecretsAccess
  */
__STATIC_INLINE void LL_TAMP_UnblockDeviceSecretsAccess(void)
{
  CLEAR_BIT(TAMP->CR2, TAMP_CR2_BKBLOCK);
}

/**
  * @brief Check if the access to the backup registers and devices secrets is blocked.
  * @rmtoll
  *  TAMP_CR2      BKBLOCK    LL_TAMP_IsBlockedDeviceSecretsAccess
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsBlockedDeviceSecretsAccess(void)
{
  return ((READ_BIT(TAMP->CR2, TAMP_CR2_BKBLOCK) == (TAMP_CR2_BKBLOCK)) ? 1UL : 0UL);
}

/**
  * @brief Erase the backup registers and device secrets.
  * @rmtoll
  *  TAMP_CR2      BKERASE    LL_TAMP_EraseDeviceSecrets
  */
__STATIC_INLINE void LL_TAMP_EraseDeviceSecrets(void)
{
  SET_BIT(TAMP->CR2, TAMP_CR2_BKERASE);
}

/**
  * @brief Enable protection by TAMP peripheral of the device secrets.
  * @rmtoll
  *  TAMP_ERCFGR      ERCFGx    LL_TAMP_EnableResourceProtection
  * @param Resources can be a combination of the group values @ref TAMP_LL_EC_RESOURCE_PROTECTION
  */
__STATIC_INLINE void LL_TAMP_EnableResourceProtection(uint32_t Resources)
{
  SET_BIT(TAMP->ERCFGR, Resources);
}

/**
  * @brief Disable protection by TAMP peripheral of the device secrets.
  * @rmtoll
  *  TAMP_ERCFGR      ERCFGx    LL_TAMP_DisableResourceProtection
  * @param Resources can be a combination of the group values @ref TAMP_LL_EC_RESOURCE_PROTECTION
  */
__STATIC_INLINE void LL_TAMP_DisableResourceProtection(uint32_t Resources)
{
  CLEAR_BIT(TAMP->ERCFGR, Resources);
}

/**
  * @brief Check if the protection by TAMP peripheral of the device secret is enabled.
  * @rmtoll
  *  TAMP_ERCFGR      ERCFGx    LL_TAMP_IsEnabledResourceProtection
  * @param Resources can be a combination of the group values @ref TAMP_LL_EC_RESOURCE_PROTECTION
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledResourceProtection(uint32_t Resources)
{
  return ((READ_BIT(TAMP->ERCFGR, Resources) == (Resources)) ? 1UL : 0UL);
}

/**
  * @brief  Blocks access to the eight first backup registers corresponding to the hardware boot key.
  * @rmtoll
  *  TAMP_SECCFGR      BHKLOCK    LL_TAMP_EnableHardwareBootkeyBlock
  */
__STATIC_INLINE void LL_TAMP_EnableHardwareBootkeyBlock(void)
{
  SET_BIT(TAMP->SECCFGR, TAMP_SECCFGR_BHKLOCK);
}

/**
  * @brief Check if the eight first backup registers corresponding to the hardware boot key are blocked.
  * @rmtoll
  *  TAMP_SECCFGR      BHKLOCK    LL_TAMP_IsEnabledHardwareBootkeyBlock
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledHardwareBootkeyBlock(void)
{
  return ((READ_BIT(TAMP->SECCFGR, TAMP_SECCFGR_BHKLOCK) == (TAMP_SECCFGR_BHKLOCK)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup TAMP_LL_EF_Monotonic_Counter Monotonic Counter
  * @{
  */

/**
  * @brief  Increment Monotonic counter.
  * @rmtoll
  *  TAMP_COUNTR         COUNT        LL_TAMP_IncrementMonotonicCounter1
  */
__STATIC_INLINE void LL_TAMP_IncrementMonotonicCounter1(void)
{
  WRITE_REG(TAMP->COUNTR, 0U);
}

/**
  * @brief  Increment Monotonic counter.
  * @rmtoll
  *  TAMP_COUNTR         COUNT        LL_TAMP_GetMonotonicCounter1
  * @retval Monotonic counter value.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetMonotonicCounter1(void)
{
  return READ_REG(TAMP->COUNTR);
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

#endif /* defined(TAMP) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_LL_TAMP_H */
