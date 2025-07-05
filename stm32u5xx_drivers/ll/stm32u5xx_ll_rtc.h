/**
  ******************************************************************************
  * @file    stm32u5xx_ll_rtc.h
  * @brief   Header file of RTC LL module
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5xx_LL_RTC_H
#define STM32U5xx_LL_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined(RTC)

/** @defgroup RTC_LL RTC
  * @{
  */

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup RTC_LL_Private_Constants RTC Private Constants
  * @{
  */

/**
  * @brief Masks Definition
  */
#define RTC_LL_INIT_MASK 0xFFFFFFFFU
#define RTC_LL_RSF_MASK  0xFFFFFF5FU

/**
  * @brief Write protection defines
  */
#define RTC_WRITE_PROTECTION_DISABLE  (uint32_t)0xFF
#define RTC_WRITE_PROTECTION_ENABLE_1 (uint32_t)0xCA
#define RTC_WRITE_PROTECTION_ENABLE_2 (uint32_t)0x53

/**
  * @brief Defines used to combine date & time
  */
#define RTC_OFFSET_WEEKDAY 24U
#define RTC_OFFSET_DAY     16U
#define RTC_OFFSET_MONTH    8U
#define RTC_OFFSET_HOUR    16U
#define RTC_OFFSET_MINUTE   8U
#define RTC_OFFSET_FORMAT  24U

/**
  * @brief Defines offset between alarm A and B registers
  */
#define RTC_ALRBR_ALRAR_OFFSET       0x02U
#define RTC_ALRBSSR_ALRASSR_OFFSET   0x02U
#define RTC_ALRBBINR_ALRABINR_OFFSET 0x01U

/**
  * @brief Defines offset between alarm A and B bits
  */
#define RTC_ALRB_ALRA_FLAGS_OFFSET          0x01U
#define RTC_ALRB_ALRA_FLAG_AUTOCLEAR_OFFSET 0x01U
#define RTC_ALRB_ALRA_EN_OFFSET             0x01U
#define RTC_ALRB_ALRA_INT_EN_OFFSET         0x01U

/**
  * @brief Defines used to combine alarm mask subseconds and subseconds
  */
#define RTC_OFFSET_ALR_MASK_SUBS_SECONDS 16U
/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup RTC_LL_Exported_Constants RTC Exported Constants
  * @{
  */

/** @defgroup RTC_LL_EC_ALM Alarm A and alarm B
  * @{
  */
#define LL_RTC_ALARM_A    0U /*!< Alarm A */
#define LL_RTC_ALARM_B    1U /*!< Alarm B */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALMA_WEEKDAY_SELECTION RTC Alarm A Date WeekDay
  * @{
  */
#define LL_RTC_ALMA_DATEWEEKDAYSEL_DATE    0U               /*!< Alarm A Date is selected    */
#define LL_RTC_ALMA_DATEWEEKDAYSEL_WEEKDAY RTC_ALRMAR_WDSEL /*!< Alarm A WeekDay is selected */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALMB_WEEKDAY_SELECTION RTC Alarm B Date WeekDay
  * @{
  */
#define LL_RTC_ALMB_DATEWEEKDAYSEL_DATE    0U               /*!< Alarm B Date is selected    */
#define LL_RTC_ALMB_DATEWEEKDAYSEL_WEEKDAY RTC_ALRMBR_WDSEL /*!< Alarm B WeekDay is selected */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_TIMESTAMP_FLAGS Timestamp Flags Defines
  * @brief    Timestamp flags defines
  * @{
  */
#define LL_RTC_SR_ITSF  RTC_SR_ITSF
#define LL_RTC_SR_TSOVF RTC_SR_TSOVF
#define LL_RTC_SR_TSF   RTC_SR_TSF
/**
  * @}
  */

/** @defgroup RTC_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_RTC_READ_REG function
  * @{
  */
#define LL_RTC_SCR_SSRUF    RTC_SCR_CSSRUF
#define LL_RTC_SCR_ITSF     RTC_SCR_CITSF
#define LL_RTC_SCR_TSOVF    RTC_SCR_CTSOVF
#define LL_RTC_SCR_TSF      RTC_SCR_CTSF
#define LL_RTC_SCR_WUTF     RTC_SCR_CWUTF
#define LL_RTC_SCR_ALRBF    RTC_SCR_CALRBF
#define LL_RTC_SCR_ALRAF    RTC_SCR_CALRAF
#define LL_RTC_ICSR_RECALPF RTC_ICSR_RECALPF
#define LL_RTC_ICSR_BCDU_2  RTC_ICSR_BCDU_2
#define LL_RTC_ICSR_BCDU_1  RTC_ICSR_BCDU_1
#define LL_RTC_ICSR_BCDU_0  RTC_ICSR_BCDU_0
#define LL_RTC_ICSR_BIN_1   RTC_ICSR_BIN_1
#define LL_RTC_ICSR_BIN_0   RTC_ICSR_BIN_0
#define LL_RTC_ICSR_INITF   RTC_ICSR_INITF
#define LL_RTC_ICSR_RSF     RTC_ICSR_RSF
#define LL_RTC_ICSR_INITS   RTC_ICSR_INITS
#define LL_RTC_ICSR_SHPF    RTC_ICSR_SHPF
#define LL_RTC_ICSR_WUTWF   RTC_ICSR_WUTWF
/**
  * @}
  */

/** @defgroup RTC_LL_EC_IT IT Defines
  * @brief    IT defines which can be  used with LL_RTC_READ_REG and  LL_RTC_WRITE_REG functions
  * @{
  */
#define LL_RTC_CR_TSIE   RTC_CR_TSIE
#define LL_RTC_CR_WUTIE  RTC_CR_WUTIE
#define LL_RTC_CR_ALRBIE RTC_CR_ALRBIE
#define LL_RTC_CR_ALRAIE RTC_CR_ALRAIE
/**
  * @}
  */

/** @defgroup RTC_LL_EC_WEEKDAY  WEEK DAY
  * @{
  */
#define LL_RTC_WEEKDAY_MONDAY    (uint32_t)0x01 /*!< Monday    */
#define LL_RTC_WEEKDAY_TUESDAY   (uint32_t)0x02 /*!< Tuesday   */
#define LL_RTC_WEEKDAY_WEDNESDAY (uint32_t)0x03 /*!< Wednesday */
#define LL_RTC_WEEKDAY_THURSDAY  (uint32_t)0x04 /*!< Thrusday  */
#define LL_RTC_WEEKDAY_FRIDAY    (uint32_t)0x05 /*!< Friday    */
#define LL_RTC_WEEKDAY_SATURDAY  (uint32_t)0x06 /*!< Saturday  */
#define LL_RTC_WEEKDAY_SUNDAY    (uint32_t)0x07 /*!< Sunday    */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_MONTH  MONTH
  * @{
  */
#define LL_RTC_MONTH_JANUARY   (uint32_t)0x01  /*!< January   */
#define LL_RTC_MONTH_FEBRUARY  (uint32_t)0x02  /*!< February  */
#define LL_RTC_MONTH_MARCH     (uint32_t)0x03  /*!< March     */
#define LL_RTC_MONTH_APRIL     (uint32_t)0x04  /*!< April     */
#define LL_RTC_MONTH_MAY       (uint32_t)0x05  /*!< May       */
#define LL_RTC_MONTH_JUNE      (uint32_t)0x06  /*!< June      */
#define LL_RTC_MONTH_JULY      (uint32_t)0x07  /*!< July      */
#define LL_RTC_MONTH_AUGUST    (uint32_t)0x08  /*!< August    */
#define LL_RTC_MONTH_SEPTEMBER (uint32_t)0x09  /*!< September */
#define LL_RTC_MONTH_OCTOBER   (uint32_t)0x10  /*!< October   */
#define LL_RTC_MONTH_NOVEMBER  (uint32_t)0x11  /*!< November  */
#define LL_RTC_MONTH_DECEMBER  (uint32_t)0x12  /*!< December  */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_HOUR_FORMAT  HOUR FORMAT
  * @{
  */
#define LL_RTC_HOUR_FORMAT_24HOUR 0U         /*!< 24 hour/day format */
#define LL_RTC_HOUR_FORMAT_AMPM   RTC_CR_FMT /*!< AM/PM hour format  */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_REF_CLOCK Reference clock
  * @{
  */
#define LL_RTC_REF_CLOCK_DISABLE 0U             /*!< Reference clock detection disable */
#define LL_RTC_REF_CLOCK_ENABLE  RTC_CR_REFCKON /*!< Reference clock detection enable  */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_SHADOW_REGISTER Shadow register
  * @{
  */
#define LL_RTC_SHADOW_REG_KEEP   0U             /*!< Disable Bypass shadow register */
#define LL_RTC_SHADOW_REG_BYPASS RTC_CR_BYPSHAD /*!< Enable Bypass shadow register  */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_BKP_REGISTER Bakcup Register for daylight saving time
  * @{
  */
#define LL_RTC_BKP_REGISTER_UNSET 0U          /*!< Daylight time change has been not performed */
#define LL_RTC_BKP_REGISTER_SET   RTC_CR_BKP  /*!< Daylight time change has been performed     */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALARMOUT  ALARM OUTPUT
  * @{
  */
#define LL_RTC_ALARMOUT_DISABLE 0U              /*!< Output disable        */
#define LL_RTC_ALARMOUT_ALARM_A    RTC_CR_OSEL_0 /*!< Alarm A output enable */
#define LL_RTC_ALARMOUT_ALARM_B    RTC_CR_OSEL_1 /*!< Alarm B output enable */
#define LL_RTC_ALARMOUT_WAKEUP  RTC_CR_OSEL     /*!< Wakeup output enable  */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALARM_OUTPUTTYPE  ALARM Output type
  * @{
  */
#define LL_RTC_ALARM_OUTPUTTYPE_PUSHPULL    0U                   /*!< RTC_ALARM is push-pull output  */
#define LL_RTC_ALARM_OUTPUTTYPE_OPENDRAIN   RTC_CR_TAMPALRM_TYPE /*!< RTC_ALARM is open-drain output */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALARM_OUTPUT_PULLUP  ALARM Output pull-up
  * @{
  */
#define LL_RTC_ALARM_OUTPUT_PULLUP_NONE   0U                 /*!< No pull-up is applied on TAMPALRM output */
#define LL_RTC_ALARM_OUTPUT_PULLUP_ON     RTC_CR_TAMPALRM_PU /*!< A pull-up is applied on TAMPALRM output  */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALARM_OUTPUT_REMAP  ALARM Output REMAP
  * @{
  */
#define LL_RTC_ALARM_OUTPUT_REMAP_NONE  0U             /*!< RTC_OUT2 output disable */
#define LL_RTC_ALARM_OUTPUT_REMAP_POS1  RTC_CR_OUT2EN  /*!< RTC_OUT2 output enable  */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_OUTPUTPOLARITY_PIN  OUTPUT POLARITY PIN
  * @{
  */
#define LL_RTC_OUTPUTPOLARITY_PIN_HIGH  0U          /*!< Pin is high when selected TAMPALRM is asserted */
#define LL_RTC_OUTPUTPOLARITY_PIN_LOW   RTC_CR_POL  /*!< Pin is low when selected TAMPALRM is asserted  */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_TIME_FORMAT TIME FORMAT
  * @{
  */
#define LL_RTC_TIME_FORMAT_AM_24H     0U          /*!< AM or 24-hour format */
#define LL_RTC_TIME_FORMAT_PM         RTC_TR_PM   /*!< PM                   */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_SHIFT_SECOND  SHIFT SECOND
  * @{
  */
#define LL_RTC_SHIFT_SECOND_DELAY   0U               /*!< Delay (seconds) = SUBFS / (PREDIV_S + 1)     */
#define LL_RTC_SHIFT_SECOND_ADVANCE RTC_SHIFTR_ADD1S /*!< Advance (seconds) = (1-(SUBFS/(PREDIV_S+1))) */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALMA_MASK  ALARMA MASK
  * @{
  */
#define LL_RTC_ALMA_MASK_NONE        0U               /*!< No masks applied on alarm A                */
#define LL_RTC_ALMA_MASK_DATEWEEKDAY RTC_ALRMAR_MSK4  /*!< Date/day do not care in alarm A comparison */
#define LL_RTC_ALMA_MASK_HOURS       RTC_ALRMAR_MSK3  /*!< Hours do not care in alarm A comparison    */
#define LL_RTC_ALMA_MASK_MINUTES     RTC_ALRMAR_MSK2  /*!< Minutes do not care in alarm A comparison  */
#define LL_RTC_ALMA_MASK_SECONDS     RTC_ALRMAR_MSK1  /*!< Seconds do not care in alarm A comparison  */
#define LL_RTC_ALMA_MASK_ALL         (RTC_ALRMAR_MSK4 | RTC_ALRMAR_MSK3 | RTC_ALRMAR_MSK2 | RTC_ALRMAR_MSK1)
/*!< Masks all */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALMA_TIME_FORMAT  ALARMA TIME FORMAT
  * @{
  */
#define LL_RTC_ALMA_TIME_FORMAT_AM_24H  0U            /*!< AM or 24-hour format */
#define LL_RTC_ALMA_TIME_FORMAT_PM      RTC_ALRMAR_PM /*!< PM                   */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALMA_AUTOCLR RTC Alarm auto clear
  * @{
  */
#define LL_RTC_ALM_AUTOCLR_NO  0U              /*!< Alarm autoclear disable */
#define LL_RTC_ALM_AUTOCLR_YES RTC_CR_ALRAFCLR /*!< Alarm autoclear enable  */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALMA_SUBSECONDBIN_AUTOCLR  RTC Alarm Sub Seconds with binary mode auto clear Definitions
  * @{
  */
#define LL_RTC_ALMA_SUBSECONDBIN_AUTOCLR_NO  0UL                /*!< The synchronous binary counter \
                                                                    (SS[31:0] in RTC_SSR) is free-running */
#define LL_RTC_ALMA_SUBSECONDBIN_AUTOCLR_YES RTC_ALRMASSR_SSCLR /*!< The synchronous binary counter (SS[31:0] \
                                                                     in RTC_SSR) is running from 0xFFFF FFFF to \
                                                                     -> SS[31:0] value and is automatically \
                                                                     reloaded with 0xFFFF FFFF when reaching \
                                                                     RTC_ALRABINR -> SS[31:0] */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALMB_MASK  ALARMB MASK
  * @{
  */
#define LL_RTC_ALMB_MASK_NONE        0U              /*!< No masks applied on Alarm B                */
#define LL_RTC_ALMB_MASK_DATEWEEKDAY RTC_ALRMBR_MSK4 /*!< Date/day do not care in Alarm B comparison */
#define LL_RTC_ALMB_MASK_HOURS       RTC_ALRMBR_MSK3 /*!< Hours do not care in Alarm B comparison    */
#define LL_RTC_ALMB_MASK_MINUTES     RTC_ALRMBR_MSK2 /*!< Minutes do not care in Alarm B comparison  */
#define LL_RTC_ALMB_MASK_SECONDS     RTC_ALRMBR_MSK1 /*!< Seconds do not care in Alarm B comparison  */
#define LL_RTC_ALMB_MASK_ALL         (RTC_ALRMBR_MSK4 | RTC_ALRMBR_MSK3 | RTC_ALRMBR_MSK2 | RTC_ALRMBR_MSK1)
/*!< Masks all */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALMB_TIME_FORMAT  ALARMB TIME FORMAT
  * @{
  */
#define LL_RTC_ALMB_TIME_FORMAT_AM_24H 0U            /*!< AM or 24-hour format */
#define LL_RTC_ALMB_TIME_FORMAT_PM RTC_ALRMBR_PM /*!< PM                   */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALMB_SUBSECONDBIN_AUTOCLR  Alarm Sub Seconds with binary mode auto clear Definitions
  * @{
  */
#define LL_RTC_ALMB_SUBSECONDBIN_AUTOCLR_NO  0UL                /*!< The synchronous binary counter \
                                                                     (SS[31:0] in RTC_SSR) is free-running */
#define LL_RTC_ALMB_SUBSECONDBIN_AUTOCLR_YES RTC_ALRMBSSR_SSCLR /*!< The synchronous binary counter \
                                                                     (SS[31:0] in RTC_SSR) is running \
                                                                     from 0xFFFF FFFF to RTC_ALRABINR -> SS[31:0]\
                                                                     value and is automatically reloaded with \
                                                                     0xFFFF FFFF when reaching \
                                                                     RTC_ALRABINR -> SS[31:0] */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_TIMESTAMP_EDGE  TIMESTAMP EDGE
  * @{
  */
#define LL_RTC_TIMESTAMP_EDGE_RISING  0U            /*!< RTC_TS input rising edge generates a time-stamp event */
#define LL_RTC_TIMESTAMP_EDGE_FALLING RTC_CR_TSEDGE /*!< RTC_TS input falling edge generates a time-stamp even */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_TIMESTAMP_PIN_ENABLE Timestamp pin source enable
  * @{
  */

#define LL_RTC_TIMESTAMP_PIN_DISABLE 0U
#define LL_RTC_TIMESTAMP_PIN_ENABLE  RTC_CR_TSE
/**
  * @}
  */

/** @defgroup RTC_LL_EC_TIMESTAMP_TAMPER_ENABLE Timestamp tamper source enable
  * @{
  */

#define LL_RTC_TIMESTAMP_TAMPER_DISABLE 0U
#define LL_RTC_TIMESTAMP_TAMPER_ENABLE  RTC_CR_TAMPTS
/**
  * @}
  */

/** @defgroup RTC_LL_EC_TIMESTAMP_INTERNAL_ENABLE Timestamp internal enable
  * @{
  */
#define LL_RTC_TIMESTAMP_INTERNAL_DISABLE 0U
#define LL_RTC_TIMESTAMP_INTERNAL_ENABLE  RTC_CR_ITSE
/**
  * @}
  */

/** @defgroup RTC_LL_EC_TS_TIME_FORMAT  TIMESTAMP TIME FORMAT
  * @{
  */
#define LL_RTC_TS_TIME_FORMAT_AM_24H 0U          /*!< AM or 24-hour format */
#define LL_RTC_TS_TIME_FORMAT_PM     RTC_TSTR_PM /*!< PM                   */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_WAKEUPCLOCK_DIV  WAKEUP CLOCK DIV
  * @{
  */
#define LL_RTC_WAKEUPCLOCK_DIV_16     0U                                    /*!< RTC/16 clock is selected */
#define LL_RTC_WAKEUPCLOCK_DIV_8      RTC_CR_WUCKSEL_0                      /*!< RTC/8 clock is selected  */
#define LL_RTC_WAKEUPCLOCK_DIV_4      RTC_CR_WUCKSEL_1                      /*!< RTC/4 clock is selected  */
#define LL_RTC_WAKEUPCLOCK_DIV_2      (RTC_CR_WUCKSEL_1 | RTC_CR_WUCKSEL_0) /*!< RTC/2 clock is selected  */
#define LL_RTC_WAKEUPCLOCK_CKSPRE     RTC_CR_WUCKSEL_2                      /*!< ck_spre (usually 1 Hz) clock is
                                                                                 selected */
#define LL_RTC_WAKEUPCLOCK_CKSPRE_WUT (RTC_CR_WUCKSEL_2 | RTC_CR_WUCKSEL_1) /*!< ck_spre (usually 1 Hz) clock is
                                                                                 selected and 2exp16 is added to the WUT
                                                                                 counter value */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_TAMPER_OUTPUT Tamper event output
  * @{
  */
#define LL_RTC_OUTPUT_TAMPER_DISABLE 0U
#define LL_RTC_OUTPUT_TAMPER_ENABLE  RTC_CR_TAMPOE
/**
  * @}
  */

/** @defgroup RTC_LL_EC_CALIB_FREQUENCY_OUTPUT Calibration frequency output
  * @{
  */
#define LL_RTC_CALIB_FREQUENCY_512HZ  0U
#define LL_RTC_CALIB_FREQUENCY_1HZ    RTC_CR_COSEL
/**
  * @}
  */

/** @defgroup RTC_LL_EC_CALIB_OUTPUT  Calibration output
  * @{
  */
#define LL_RTC_CALIB_OUTPUT_NONE    0U                          /*!< Calibration output disabled  */
#define LL_RTC_CALIB_OUTPUT_ENABLE  RTC_CR_COE                  /*!< Calibration output enabled with current
                                                                     configuration */
#define LL_RTC_CALIB_OUTPUT_1HZ     (RTC_CR_COE | RTC_CR_COSEL) /*!< Calibration output is 1 Hz   */
#define LL_RTC_CALIB_OUTPUT_512HZ   RTC_CR_COE                  /*!< Calibration output is 512 Hz */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_CALIB_INSERTPULSE  Calibration pulse insertion
  * @{
  */
#define LL_RTC_CALIB_INSERTPULSE_NONE 0U            /*!< No RTCCLK pulses are added */
#define LL_RTC_CALIB_INSERTPULSE_SET  RTC_CALR_CALP /*!< One RTCCLK pulse is effectively inserted every 2exp11 pulses
                                                         (frequency increased by 488.5 ppm) */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_CALIB_PERIOD  Calibration period
  * @{
  */
#define LL_RTC_CALIB_PERIOD_32SEC 0U              /*!< Use a 32-second calibration cycle period */
#define LL_RTC_CALIB_PERIOD_16SEC RTC_CALR_CALW16 /*!< Use a 16-second calibration cycle period */
#define LL_RTC_CALIB_PERIOD_8SEC  RTC_CALR_CALW8  /*!< Use a 8-second calibration cycle period  */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_CALIB_LOWPOWER  Calibration low power
  * @{
  */
#define LL_RTC_CALIB_LOWPOWER_NONE 0U             /*!< High-consumption mode      */
#define LL_RTC_CALIB_LOWPOWER_SET  RTC_CALR_LPCAL /*!< Ultra-low consumption mode */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_BINARY_MODE  Binary mode (Sub Second Register)
  * @{
  */
#define LL_RTC_BINARY_NONE 0U             /*!< Free running BCD calendar mode (Binary mode disabled) */
#define LL_RTC_BINARY_ONLY RTC_ICSR_BIN_0 /*!< Free running Binary mode (BCD mode disabled)          */
#define LL_RTC_BINARY_MIX  RTC_ICSR_BIN_1 /*!< Free running BCD calendar and Binary mode enable      */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_BINARY_MIX_BCDU  Calendar second incrementation in Binary mix mode
  * @{
  */
#define LL_RTC_BINARY_MIX_BCDU_SHIFT RTC_ICSR_BCDU_Pos
#define LL_RTC_BINARY_MIX_BCDU_0     0U                           /*!< 1s calendar increment is generated each time
                                                                       SS[7:0] = 0 */
#define LL_RTC_BINARY_MIX_BCDU_1     (0x1UL << RTC_ICSR_BCDU_Pos) /*!< 1s calendar increment is generated each time
                                                                       SS[8:0] = 0 */
#define LL_RTC_BINARY_MIX_BCDU_2     (0x2UL << RTC_ICSR_BCDU_Pos) /*!< 1s calendar increment is generated each time
                                                                       SS[9:0] = 0 */
#define LL_RTC_BINARY_MIX_BCDU_3     (0x3UL << RTC_ICSR_BCDU_Pos) /*!< 1s calendar increment is generated each time
                                                                       SS[10:0] = 0 */
#define LL_RTC_BINARY_MIX_BCDU_4     (0x4UL << RTC_ICSR_BCDU_Pos) /*!< 1s calendar increment is generated each time
                                                                       SS[11:0] = 0 */
#define LL_RTC_BINARY_MIX_BCDU_5     (0x5UL << RTC_ICSR_BCDU_Pos) /*!< 1s calendar increment is generated each time
                                                                       SS[12:0] = 0 */
#define LL_RTC_BINARY_MIX_BCDU_6     (0x6UL << RTC_ICSR_BCDU_Pos) /*!< 1s calendar increment is generated each time
                                                                       SS[13:0] = 0 */
#define LL_RTC_BINARY_MIX_BCDU_7     (0x7UL << RTC_ICSR_BCDU_Pos) /*!< 1s calendar increment is generated each time
                                                                       SS[14:0] = 0 */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_SECURE_RTC_FULL  Secure full rtc
  * @{
  */
#define LL_RTC_SECURE_FULL_YES RTC_SECCFGR_SEC /*!< RTC full secure */
#define LL_RTC_SECURE_FULL_NO  0U              /*!< RTC is not full secure, features can be secure
                                                    See RTC_LL_EC_SECURE_RTC_FEATURE */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_UNSECURE_RTC_FEATURE  UnSecure features rtc in case of LL_RTC_SECURE_FULL_NO
  * @{
  */
#define LL_RTC_SECURE_FEATURE_INIT RTC_SECCFGR_INITSEC /*!< Initialization feature is secure */
#define LL_RTC_SECURE_FEATURE_CAL  RTC_SECCFGR_CALSEC  /*!< Calibration feature is secure */
#define LL_RTC_SECURE_FEATURE_TS   RTC_SECCFGR_TSSEC   /*!< Time stamp feature is secure */
#define LL_RTC_SECURE_FEATURE_WUT  RTC_SECCFGR_WUTSEC  /*!< Wake up timer feature is secure */
#define LL_RTC_SECURE_FEATURE_ALRA RTC_SECCFGR_ALRASEC /*!< Alarm A feature is secure */
#define LL_RTC_SECURE_FEATURE_ALRB RTC_SECCFGR_ALRBSEC /*!< Alarm B feature is secure */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_PRIVILEGE_RTC_FULL  Privilege full rtc
  * @{
  */
#define LL_RTC_PRIVILEGE_FULL_YES RTC_PRIVCFGR_PRIV /*!< RTC full privilege */
#define LL_RTC_PRIVILEGE_FULL_NO  0U                /*!< RTC is not full privilege, features can be unprivilege
                                                         See RTC_LL_EC_PRIVILEGE_RTC_FEATURE */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_PRIVILEGE_RTC_FEATURE  Privilege rtc features in case of LL_RTC_PRIVILEGE_FULL_NO
  * @{
  */
#define LL_RTC_PRIVILEGE_FEATURE_INIT RTC_PRIVCFGR_INITPRIV /*!< Initialization feature is privilege */
#define LL_RTC_PRIVILEGE_FEATURE_CAL  RTC_PRIVCFGR_CALPRIV  /*!< Calibration feature is privilege */
#define LL_RTC_PRIVILEGE_FEATURE_TS   RTC_PRIVCFGR_TSPRIV   /*!< Time stamp feature is privilege */
#define LL_RTC_PRIVILEGE_FEATURE_WUT  RTC_PRIVCFGR_WUTPRIV  /*!< Wake up timer feature is privilege */
#define LL_RTC_PRIVILEGE_FEATURE_ALRA RTC_PRIVCFGR_ALRAPRIV /*!< Alarm A feature is privilege */
#define LL_RTC_PRIVILEGE_FEATURE_ALRB RTC_PRIVCFGR_ALRBPRIV /*!< Alarm B feature is privilege */
/**
  * @}
  */

/** @defgroup RTC_LL_EC_WAKEUP_TIMER_INTERRUPT wakeup timer interrupt definition
  * @{
  */
#define LL_RTC_WAKEUP_TIMER_IT_DISABLE 0U
#define LL_RTC_WAKEUP_TIMER_IT_ENABLE  RTC_CR_WUTIE
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALARMA_INTERRUPT alarm a interrupt definition
  * @{
  */
#define LL_RTC_ALMA_IT_DISABLE 0U
#define LL_RTC_ALMA_IT_ENABLE  RTC_CR_ALRAIE
/**
  * @}
  */

/** @defgroup RTC_LL_EC_ALARMB_INTERRUPT alarm b interrupt definition
  * @{
  */
#define LL_RTC_ALMB_IT_DISABLE 0U
#define LL_RTC_ALMB_IT_ENABLE  RTC_CR_ALRBIE
/**
  * @}
  */

/** @defgroup RTC_LL_EC_TIMESTAMP_INTERRUPT timestamp interrupt definition
  * @{
  */
#define LL_RTC_TIMESTAMP_IT_DISABLE 0U
#define LL_RTC_TIMESTAMP_IT_ENABLE  RTC_CR_TSIE
/**
  * @}
  */

/** @defgroup RTC_LL_EC_SSRU_INTERRUPT sub seconds register underflow interrupt definition
  * @{
  */
#define LL_RTC_SSRU_IT_DISABLE 0U
#define LL_RTC_SSRU_IT_ENABLE  RTC_CR_SSRUIE
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/** @defgroup RTC_LL_Exported_Macros RTC Exported Macros
  * @{
  */

/** @defgroup RTC_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in RTC register
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_RTC_WRITE_REG(reg, value) WRITE_REG(RTC->reg, (value))

/**
  * @brief  Read a value in RTC register
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_RTC_READ_REG(reg) READ_REG(RTC->reg)

/**
  * @}
  */

/** @defgroup RTC_LL_EM_Convert Convert helper Macros
  * @{
  */

/**
  * @brief  Helper macro to convert a value from 2 digit decimal format to BCD format
  * @param  value Byte to be converted
  * @retval Converted byte
  */
#define LL_RTC_CONVERT_BIN2BCD(value) ((uint32_t)((((value) / 10U) << 4U) | ((value) % 10U)))

/**
  * @brief  Helper macro to convert a value from BCD format to 2 digit decimal format
  * @param  value BCD value to be converted
  * @retval Converted byte
  */
#define LL_RTC_CONVERT_BCD2BIN(value) ((uint32_t)((((uint32_t)((value) & (uint32_t)0xF0U) >> \
                                                    (uint32_t)0x4U) * 10U) + ((value) & (uint32_t)0x0FU)))

/**
  * @}
  */

/** @defgroup RTC_LL_EM_Global Global configuration helper Macros
  * @{
  */

/**
  * @brief  Helper macro to retrieve the value of the asynchronous prescaler
  * @param  value Value returned by @ref LL_RTC_GetPrescalers
  * @retval Value of the asynchronous prescaler
  */
#define LL_RTC_GET_ASYNCH_PRESCALER(value) (((value) & RTC_PRER_PREDIV_A) >> RTC_PRER_PREDIV_A_Pos)

/**
  * @brief  Helper macro to retrieve the value of the synchronous prescaler
  * @param  value Value returned by @ref LL_RTC_GetPrescalers
  * @retval Value of the synchrounous prescaler
  */
#define LL_RTC_GET_SYNCH_PRESCALER(value) (((value) & RTC_PRER_PREDIV_S) >> RTC_PRER_PREDIV_S_Pos)

/**
  * @}
  */

/**
  * @brief  Helper macro to retrieve the value of BCD update
  * @param  value Value returned by @ref LL_RTC_GetConfigBinaryMode
  * @retval Value of the BCD update in mixed mode
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_0
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_1
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_2
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_3
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_4
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_5
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_6
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_7
  */
#define LL_RTC_GET_BCDU(value) (((value) & RTC_ICSR_BCDU))

/**
  * @brief  Helper macro to retrieve the mode of RTC
  * @param  value Value returned by @ref LL_RTC_GetConfigBinaryMode
  * @retval Mode of the RTC can be one of the value:
  *         @arg @ref LL_RTC_BINARY_NONE
  *         @arg @ref LL_RTC_BINARY_ONLY
  *         @arg @ref LL_RTC_BINARY_MIX
  */
#define LL_RTC_GET_BIN(value) (((value) & RTC_ICSR_BIN))

/** @defgroup RTC_LL_EM_Calendar Calendar helper macros
  * @{
  */

/**
  * @brief  Helper macro to retrieve the calendar format value
  * @param  value CR register value
  * @retval Mode of the RTC can be one of the value:
  *         @arg @ref LL_RTC_TIME_FORMAT_AM_24H
  *         @arg @ref LL_RTC_TIME_FORMAT_PM
  */
#define LL_RTC_GET_CALENDAR_HOUR_FORMAT(value) (((value) & RTC_CR_FMT))

/**
  * @brief Helper macro to retrieve the state of the bypass shadow register
  * @param value CR register value
  * @retval Mode of the RTC can be one of the value:
  *        @arg @ref LL_RTC_SHADOW_REG_KEEP
  *        @arg @ref LL_RTC_SHADOW_REG_BYPASS
  */
#define LL_RTC_GET_SHADOW_REG_BYPASS(value) (((value) & RTC_CR_BYPSHAD))

/**
  * @}
  */

/** @defgroup RTC_LL_EM_Date Date helper Macros
  * @{
  */

/**
  * @brief  Helper macro to retrieve weekday
  * @param  rtc_date Date returned by @ref  LL_RTC_DATE_Get function
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_WEEKDAY_MONDAY
  *         @arg @ref LL_RTC_WEEKDAY_TUESDAY
  *         @arg @ref LL_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref LL_RTC_WEEKDAY_THURSDAY
  *         @arg @ref LL_RTC_WEEKDAY_FRIDAY
  *         @arg @ref LL_RTC_WEEKDAY_SATURDAY
  *         @arg @ref LL_RTC_WEEKDAY_SUNDAY
  */
#define LL_RTC_GET_WEEKDAY(rtc_date) (((rtc_date) >> RTC_OFFSET_WEEKDAY) & 0x000000FFU)

/**
  * @brief  Helper macro to retrieve Year in BCD format
  * @param  rtc_date Value returned by @ref  LL_RTC_DATE_Get
  * @retval Year in BCD format (0x00 . . . 0x99)
  */
#define LL_RTC_GET_YEAR(rtc_date) ((rtc_date) & 0x000000FFU)

/**
  * @brief  Helper macro to retrieve Month in BCD format
  * @param  rtc_date Value returned by @ref  LL_RTC_DATE_Get
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_MONTH_JANUARY
  *         @arg @ref LL_RTC_MONTH_FEBRUARY
  *         @arg @ref LL_RTC_MONTH_MARCH
  *         @arg @ref LL_RTC_MONTH_APRIL
  *         @arg @ref LL_RTC_MONTH_MAY
  *         @arg @ref LL_RTC_MONTH_JUNE
  *         @arg @ref LL_RTC_MONTH_JULY
  *         @arg @ref LL_RTC_MONTH_AUGUST
  *         @arg @ref LL_RTC_MONTH_SEPTEMBER
  *         @arg @ref LL_RTC_MONTH_OCTOBER
  *         @arg @ref LL_RTC_MONTH_NOVEMBER
  *         @arg @ref LL_RTC_MONTH_DECEMBER
  */
#define LL_RTC_GET_MONTH(rtc_date) (((rtc_date) >>RTC_OFFSET_MONTH) & 0x000000FFU)

/**
  * @brief  Helper macro to retrieve Day in BCD format
  * @param  rtc_date Value returned by @ref  LL_RTC_DATE_Get
  * @retval Day in BCD format (0x01 . . . 0x31)
  */
#define LL_RTC_GET_DAY(rtc_date) (((rtc_date) >>RTC_OFFSET_DAY) & 0x000000FFU)

/**
  * @}
  */

/** @defgroup RTC_LL_EM_Time Time helper Macros
  * @{
  */

/**
  * @brief  Helper macro to retrieve hour in BCD format
  * @param  rtc_time RTC time returned by @ref LL_RTC_TIME_Get function
  * @retval Hours in BCD format (0x01. . .0x12 or between Min_Data=0x00 and Max_Data=0x23)
  */
#define LL_RTC_GET_HOUR(rtc_time) (((rtc_time) >> RTC_OFFSET_HOUR) & 0x000000FFU)

/**
  * @brief  Helper macro to retrieve minute in BCD format
  * @param  rtc_time RTC time returned by @ref LL_RTC_TIME_Get function
  * @retval Minutes in BCD format (0x00. . .0x59)
  */
#define LL_RTC_GET_MINUTE(rtc_time) (((rtc_time) >> RTC_OFFSET_MINUTE) & 0x000000FFU)

/**
  * @brief  Helper macro to retrieve second in BCD format
  * @param  rtc_time RTC time returned by @ref LL_RTC_TIME_Get function
  * @retval Seconds in BCD format (0x00. . .0x59)
  */
#define LL_RTC_GET_SECOND(rtc_time) ((rtc_time) & 0x000000FFU)

/**
  * @brief  Helper macro to retrieve format
  * @param  rtc_time RTC time returned by @ref LL_RTC_TIME_Get function
  * @retval Format
  */
#define LL_RTC_GET_FORMAT(rtc_time) (((rtc_time) >> RTC_OFFSET_FORMAT) & 0x0000000FU)

/**
  * @}
  */

/** @defgroup RTC_LL_EM_Output Output helper macros
  *  @{
  */

/**
  * @brief  Helper macro to retrieve the output polarity from the CR register
  * @param  value CR register value
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_OUTPUTPOLARITY_PIN_HIGH
  *         @arg @ref LL_RTC_OUTPUTPOLARITY_PIN_LOW
  */
#define LL_RTC_GET_OUTPUT_POLARITY(value) (((value) & RTC_CR_TAMPALRM_TYPE) >> RTC_CR_TAMPALRM_TYPE_Pos)

/**
  * @brief  Helper macro to retrieve the output type from the CR register
  * @param  value CR register value
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_OUTPUTTYPE_PUSHPULL
  *         @arg @ref LL_RTC_ALARM_OUTPUTTYPE_OPENDRAIN
  */
#define LL_RTC_GET_OUTPUT_TYPE(value) (((value) & RTC_CR_TAMPALRM_TYPE) >> RTC_CR_TAMPALRM_TYPE_Pos)

/**
  * @brief  Helper macro to retrieve the output pull-up status from the CR register
  * @param  value CR register value
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_OUTPUT_PULLUP_NONE
  *         @arg @ref LL_RTC_ALARM_OUTPUT_PULLUP_ON
  */
#define LL_RTC_GET_OUTPUT_PULLUP(value) (((value) & RTC_CR_POL) >> RTC_CR_POL_Pos)

/**
  * @}
  */

/** @defgroup RTC_LL_EM_Alarm_Time alarm helper macros
  * @{
  */

/**
  * @brief  Helper macro to retrieve alarm hour in BCD format
  * @param  rtc_alarm_time_date Alarm time and date returned
  * @retval Hours in BCD format (0x01. . .0x12 or between Min_Data=0x00 and Max_Data=0x23)
  */
#define LL_RTC_GET_ALARM_HOUR(rtc_alarm_time_date) (((rtc_alarm_time_date) & \
                                                     (RTC_ALRMAR_HU_Msk | RTC_ALRMAR_HT_Msk)) >> RTC_ALRMAR_HU_Pos)

/**
  * @brief  Helper macro to retrieve alarm minute in BCD format
  * @param  rtc_alarm_time_date Alarm time and date returned
  * @retval Minutes in BCD format (0x00. . .0x59)
  */
#define LL_RTC_GET_ALARM_MINUTE(rtc_alarm_time_date) (((rtc_alarm_time_date) & \
                                                       (RTC_ALRMAR_MNU_Msk | RTC_ALRMAR_MNT_Msk)) >>\
                                                      RTC_ALRMAR_MNU_Pos )

/**
  * @brief  Helper macro to retrieve alarm second in BCD format
  * @param  rtc_alarm_time_date Alarm time and date returned
  * @retval Seconds in BCD format (0x00. . .0x59)
  */
#define LL_RTC_GET_ALARM_SECOND(rtc_alarm_time_date) (((rtc_alarm_time_date) & \
                                                       (RTC_ALRMAR_SU_Msk | RTC_ALRMAR_ST_Msk)) \
                                                      >> RTC_ALRMAR_SU_Pos )

/**
  * @brief  Helper macro to retrieve alarm time format
  * @param  rtc_alarm_time_date Alarm time and date returned
  * @retval Format
  */
#define LL_RTC_GET_ALARM_FORMAT(rtc_alarm_time_date) (((rtc_alarm_time_date) & (RTC_ALRMAR_PM_Msk)))

/**
  * @brief  Helper macro to retrieve alarm day in BCD format
  * @param  rtc_alarm_time_date Alarm time and date returned
  * @retval Day in BCD format (0x00. . .0x31)
  */
#define LL_RTC_GET_ALARM_DAY(rtc_alarm_time_date) (((rtc_alarm_time_date) & (RTC_ALRMAR_DU_Msk | RTC_ALRMAR_DT_Msk))\
                                                   >> RTC_ALRMAR_DU_Pos )

/**
  * @brief  Helper macro to retrieve alarm day week day selection in BCD format
  * @param  rtc_alarm_time_date Alarm time and date returned
  * @retval Day weekday selection
  */
#define LL_RTC_GET_ALARM_DAY_WDAY_SEL(rtc_alarm_time_date) (((rtc_alarm_time_date) & (RTC_ALRMAR_WDSEL_Msk)))

/**
  * @brief  Helper macro to retrieve alarm mask selection in BCD format
  * @param  rtc_alarm_time_date Alarm time and date returned
  * @retval Alarm mask selection
  */
#define LL_RTC_GET_ALARM_MASKS(rtc_alarm_time_date) ((rtc_alarm_time_date) & (RTC_ALRMAR_MSK4 | RTC_ALRMAR_MSK3 | \
                                                                              RTC_ALRMAR_MSK2 | RTC_ALRMAR_MSK1))

/**
  * @brief  Helper macro to retrieve alarm subsecond  in BCD format
  * @param  rtc_alarm_ss Alarm subseconds mask and value returned
  * @retval Alarm subseconds
  */
#define LL_RTC_ALARM_GET_SS(rtc_alarm_ss) ((rtc_alarm_ss) & 0xFFFFU)

/**
  * @brief  Helper macro to retrieve alarm subsecond mask selection in BCD format
  * @param  rtc_alarm_ss Alarm subseconds mask and value returned
  * @retval Alarm subseconds mask selection
  */
#define LL_RTC_ALARM_GET_MASK_SS(rtc_alarm_ss) (((rtc_alarm_ss)>> RTC_OFFSET_ALR_MASK_SUBS_SECONDS) & 0xFFU)

/**
  * @brief  Helper macro to retrieve the alarm A flag
  * @param  rtc_flags Flags retrieved from RTC_SR register
  * @retval 0U when the alarm flag A is unset
  * @retval 1U when the alarm flag A is set
  */
#define LL_RTC_ALARM_A_GET_FLAG(rtc_flags) ((((rtc_flags) & RTC_SR_ALRAF) == RTC_SR_ALRAF) ? 1U : 0U)

/**
  * @brief  Helper macro to retrieve the alarm B flag
  * @param  rtc_flags Flags retrieved from RTC_SR register
  * @retval 0U when the alarm flag B is unset
  * @retval 1U when the alarm flag B is set
  */
#define LL_RTC_ALARM_B_GET_FLAG(rtc_flags) ((((rtc_flags) & RTC_SR_ALRBF) == RTC_SR_ALRBF) ? 1U : 0U)

/**
  * @brief  Helper macro to retrieve the wake-up timer flag
  * @param  rtc_flags Flags retrieved from RTC_SR
  * @retval 0U when the wake-up timer flag is unset
  * @retval 1U when the wake-up timer flag is set
  */
#define LL_RTC_WAKEUP_GET_FLAG(rtc_flags) ((((rtc_flags) & RTC_SR_WUTF) == RTC_SR_WUTF) ? 1U : 0U)
/**
  * @brief  Helper macro to retrieve the timestamp flag
  * @param  rtc_flags Timestamp flags retrieved from RTC_SR
  * @retval 0U when the timestamp is unset
  * @retval 1U when the timestamp is set
  */
#define LL_RTC_TIMESTAMP_GET_FLAG(rtc_flags) ((((rtc_flags) & RTC_SR_TSF) == RTC_SR_TSF) ? 1U : 0U)

/**
  * @brief  Helper macro to retrieve the SSR underflow flag
  * @param  rtc_flags SSRU flags retrieved from RTC_SR
  * @retval 0U when the SRRU flag is unset
  * @retval 1U when the SRRU flag is set
  */
#define LL_RTC_SSRU_GET_FLAG(rtc_flags) ((((rtc_flags) & RTC_SR_SSRUF) == RTC_SR_SSRUF) ? 1U : 0U)

/**
  * @}
  */

/** @defgroup RTC_LL_EM_Wakeup_Time Wake-up timer helper macros
  * @{
  */

/**
  * @brief  Helper macro to retrieve the value of the wake-up auto-reload value
  * @param  value WUTR register value
  * @retval Returned value between 0x0 and 0xFFFF
  */
#define LL_RTC_GET_WAKEUP_AUTORELOAD(value) (((value) & RTC_WUTR_WUT) >> RTC_WUTR_WUT_Pos)

/**
  * @brief  Helper macro to retrieve the value of the auto-clear value
  * @param  value WUTR register value
  * @retval Returned value between 0x0 and 0xFFFF
  */
#define LL_RTC_GET_WAKEUP_AUTOCLEAR(value) (((value) & RTC_WUTR_WUTOCLR) >> RTC_WUTR_WUTOCLR_Pos)

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup RTC_LL_Exported_Functions RTC Exported Functions
  * @{
  */

/** @defgroup RTC_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Set Hours format (24 hour/day or AM/PM hour format)
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function)
  * @rmtoll
  *  RTC_CR           FMT           LL_RTC_SetHourFormat
  * @param  HourFormat This parameter can be one of the following values:
  *         @arg @ref LL_RTC_HOUR_FORMAT_24HOUR
  *         @arg @ref LL_RTC_HOUR_FORMAT_AMPM
  */
__STATIC_INLINE void LL_RTC_SetHourFormat(uint32_t HourFormat)
{
  MODIFY_REG(RTC->CR, RTC_CR_FMT, HourFormat);
}

/**
  * @brief  Get Hours format (24 hour/day or AM/PM hour format)
  * @rmtoll
  *  RTC_CR           FMT           LL_RTC_GetHourFormat
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_HOUR_FORMAT_24HOUR
  *         @arg @ref LL_RTC_HOUR_FORMAT_AMPM
  */
__STATIC_INLINE uint32_t LL_RTC_GetHourFormat(void)
{
  return (uint32_t)(READ_BIT(RTC->CR, RTC_CR_FMT));
}

/**
  * @brief  Select the flag to be routed to RTC_ALARM output
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           OSEL          LL_RTC_SetAlarmOutEvent
  * @param  AlarmOutput This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARMOUT_DISABLE
  *         @arg @ref LL_RTC_ALARMOUT_ALARM_A
  *         @arg @ref LL_RTC_ALARMOUT_ALARM_B
  *         @arg @ref LL_RTC_ALARMOUT_WAKEUP
  */
__STATIC_INLINE void LL_RTC_SetAlarmOutEvent(uint32_t AlarmOutput)
{
  MODIFY_REG(RTC->CR, RTC_CR_OSEL, AlarmOutput);
}

/**
  * @brief  Get the flag to be routed to RTC_ALARM output
  * @rmtoll
  *  RTC_CR           OSEL          LL_RTC_GetAlarmOutEvent
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_ALARMOUT_DISABLE
  *         @arg @ref LL_RTC_ALARMOUT_ALARM_A
  *         @arg @ref LL_RTC_ALARMOUT_ALARM_B
  *         @arg @ref LL_RTC_ALARMOUT_WAKEUP
  */
__STATIC_INLINE uint32_t LL_RTC_GetAlarmOutEvent(void)
{
  return (uint32_t)(READ_BIT(RTC->CR, RTC_CR_OSEL));
}

/**
  * @brief  Set RTC_ALARM output type (ALARM in push-pull or open-drain output)
  * @rmtoll
  *  RTC_CR           TAMPALRM_TYPE          LL_RTC_SetAlarmOutputType
  * @param  Output This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_OUTPUTTYPE_OPENDRAIN
  *         @arg @ref LL_RTC_ALARM_OUTPUTTYPE_PUSHPULL
  */
__STATIC_INLINE void LL_RTC_SetAlarmOutputType(uint32_t Output)
{
  MODIFY_REG(RTC->CR, RTC_CR_TAMPALRM_TYPE, Output);
}

/**
  * @brief  Get RTC_ALARM output type (ALARM in push-pull or open-drain output)
  * @rmtoll
  *  RTC_CR           TAMPALRM_TYPE          LL_RTC_GetAlarmOutputType
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_OUTPUTTYPE_OPENDRAIN
  *         @arg @ref LL_RTC_ALARM_OUTPUTTYPE_PUSHPULL
  */
__STATIC_INLINE uint32_t LL_RTC_GetAlarmOutputType(void)
{
  return (uint32_t)(READ_BIT(RTC->CR, RTC_CR_TAMPALRM_TYPE));
}

/**
  * @brief  Enable initialization mode
  * @note   Initialization mode is used to program time and date register (RTC_TR and RTC_DR)
  *         and prescaler register (RTC_PRER)
  *         Counters are stopped and start counting from the new value when INIT is reset
  * @rmtoll
  *  RTC_ICSR          INIT          LL_RTC_EnableInitMode
  */
__STATIC_INLINE void LL_RTC_EnableInitMode(void)
{
  /* Set the Initialization mode */
  SET_BIT(RTC->ICSR, RTC_ICSR_INIT);
}

/**
  * @brief  Disable initialization mode (Free running mode)
  * @rmtoll
  *  RTC_ICSR          INIT          LL_RTC_DisableInitMode
  */
__STATIC_INLINE void LL_RTC_DisableInitMode(void)
{
  /* Exit Initialization mode */
  CLEAR_BIT(RTC->ICSR, RTC_ICSR_INIT);

}

/**
  * @brief  Set Binary mode (Sub Second Register)
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function)
  * @rmtoll
  *  RTC_ICSR           BIN           LL_RTC_SetBinaryMode
  * @param  BinaryMode can be one of the following values:
  *         @arg @ref LL_RTC_BINARY_NONE
  *         @arg @ref LL_RTC_BINARY_ONLY
  *         @arg @ref LL_RTC_BINARY_MIX
  */
__STATIC_INLINE void LL_RTC_SetBinaryMode(uint32_t BinaryMode)
{
  MODIFY_REG(RTC->ICSR, RTC_ICSR_BIN, BinaryMode);
}

/**
  * @brief  Get Binary mode (Sub Second Register)
  * @rmtoll
  *  RTC_ICSR           BIN           LL_RTC_GetBinaryMode
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_RTC_BINARY_NONE
  *         @arg @ref LL_RTC_BINARY_ONLY
  *         @arg @ref LL_RTC_BINARY_MIX
  */
__STATIC_INLINE uint32_t LL_RTC_GetBinaryMode(void)
{
  return (uint32_t)(READ_BIT(RTC->ICSR, RTC_ICSR_BIN));
}

/**
  * @brief  Set Binary Mix mode BCDU
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function)
  * @rmtoll
  *  RTC_ICSR           BCDU          LL_RTC_SetBinMixBCDU
  * @param  BinMixBcdU can be one of the following values:
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_0
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_1
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_2
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_3
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_4
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_5
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_6
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_7
  */
__STATIC_INLINE void LL_RTC_SetBinMixBCDU(uint32_t BinMixBcdU)
{
  MODIFY_REG(RTC->ICSR, RTC_ICSR_BCDU, BinMixBcdU);
}

/**
  * @brief  Get Binary Mix mode BCDU
  * @rmtoll
  *  RTC_ICSR           BCDU          LL_RTC_GetBinMixBCDU
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_0
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_1
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_2
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_3
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_4
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_5
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_6
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_7
  */
__STATIC_INLINE uint32_t LL_RTC_GetBinMixBCDU(void)
{
  return (uint32_t)(READ_BIT(RTC->ICSR, RTC_ICSR_BCDU));
}

/**
  * @brief  Set Binary mode (Sub Second Register) and Mix mode BCDU
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function)
  * @rmtoll
  *  RTC_ICSR           BIN           LL_RTC_SetConfigBinaryMode \n
  *  RTC_ICSR           BCDU          LL_RTC_SetConfigBinaryMode
  * @param  BinaryMode can be one of the following values:
  *         @arg @ref LL_RTC_BINARY_NONE
  *         @arg @ref LL_RTC_BINARY_ONLY
  *         @arg @ref LL_RTC_BINARY_MIX
  * @param  BinMixBcdU can be one of the following values:
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_0
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_1
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_2
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_3
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_4
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_5
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_6
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_7
  */
__STATIC_INLINE void LL_RTC_SetConfigBinaryMode(uint32_t BinaryMode, uint32_t BinMixBcdU)
{
  MODIFY_REG(RTC->ICSR, RTC_ICSR_BIN | RTC_ICSR_BCDU, BinaryMode | BinMixBcdU);
}

/**
  * @brief  Get Binary mode (Sub Second Register) and Mix mode BCDU
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function)
  * @rmtoll
  *  RTC_ICSR           BIN           LL_RTC_GetConfigBinaryMode \n
  *  RTC_ICSR           BCDU          LL_RTC_GetConfigBinaryMode
  * @retval  A combination one of the following values:
  *         @arg @ref LL_RTC_BINARY_NONE
  *         @arg @ref LL_RTC_BINARY_ONLY
  *         @arg @ref LL_RTC_BINARY_MIX
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_0
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_1
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_2
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_3
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_4
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_5
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_6
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_7
  */
__STATIC_INLINE uint32_t LL_RTC_GetConfigBinaryMode(void)
{
  return (uint32_t) READ_BIT(RTC->ICSR, RTC_ICSR_BIN | RTC_ICSR_BCDU);
}

/**
  * @brief  Set Output polarity
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           POL           LL_RTC_SetOutputPolarity
  * @param  Polarity This parameter can be one of the following values:
  *         @arg @ref LL_RTC_OUTPUTPOLARITY_PIN_HIGH
  *         @arg @ref LL_RTC_OUTPUTPOLARITY_PIN_LOW
  */
__STATIC_INLINE void LL_RTC_SetOutputPolarity(uint32_t Polarity)
{
  MODIFY_REG(RTC->CR, RTC_CR_POL, Polarity);
}

/**
  * @brief  Get Output polarity
  * @rmtoll
  *  RTC_CR           POL           LL_RTC_GetOutputPolarity
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_OUTPUTPOLARITY_PIN_HIGH
  *         @arg @ref LL_RTC_OUTPUTPOLARITY_PIN_LOW
  */
__STATIC_INLINE uint32_t LL_RTC_GetOutputPolarity(void)
{
  return (uint32_t)(READ_BIT(RTC->CR, RTC_CR_POL));
}

/**
  * @brief  Enable bypass of the shadow registers
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   When bypass enable, Calendar values (when reading from RTC_SSR, RTC_TR, and RTC_DR) are taken
  *         directly from the calendar counters
  * @note   If the frequency of the APB clock is less than seven times the frequency of RTCCLK,
  *         BYPSHAD must be set to 1
  * @rmtoll
  *  RTC_CR           BYPSHAD       LL_RTC_EnableBypassShadowReg
  */
__STATIC_INLINE void LL_RTC_EnableBypassShadowReg(void)
{
  SET_BIT(RTC->CR, RTC_CR_BYPSHAD);
}

/**
  * @brief  Disable bypass of the shadow registers
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           BYPSHAD       LL_RTC_DisableBypassShadowReg
  */
__STATIC_INLINE void LL_RTC_DisableBypassShadowReg(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_BYPSHAD);
}

/**
  * @brief  Check if the bypass of the shadow registers is enabled or not
  * @rmtoll
  *  RTC_CR           BYPSHAD       LL_RTC_IsEnabledBypassShadowReg
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsEnabledBypassShadowReg(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_BYPSHAD) == (RTC_CR_BYPSHAD)) ? 1U : 0U);
}

/**
  * @brief  Set Hours format (24 hour/day or AM/PM hour format) and bypass shadow registers
  * @note   Bits are write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function)
  * @rmtoll
  *  RTC_CR           FMT           LL_RTC_SetHourFormatAndShadowRegBypass \n
  *  RTC_CR           BYPSHAD       LL_RTC_SetHourFormatAndShadowRegBypass
  * @param  HourFormat This parameter can be one of the following values:
  *         @arg @ref LL_RTC_HOUR_FORMAT_24HOUR
  *         @arg @ref LL_RTC_HOUR_FORMAT_AMPM
  * @param  Bypass This parameter can be one of the following values:
  *         @arg @ref LL_RTC_SHADOW_REG_KEEP
  *         @arg @ref LL_RTC_SHADOW_REG_BYPASS
  */
__STATIC_INLINE void LL_RTC_SetHourFormatAndShadowRegBypass(uint32_t HourFormat, uint32_t Bypass)
{
  MODIFY_REG(RTC->CR, RTC_CR_FMT | RTC_CR_BYPSHAD, HourFormat | Bypass);
}

/**
  * @brief  Enable RTC_REFIN reference clock detection (50 or 60 Hz)
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function)
  * @rmtoll
  *  RTC_CR           REFCKON       LL_RTC_EnableRefClock
  */
__STATIC_INLINE void LL_RTC_EnableRefClock(void)
{
  SET_BIT(RTC->CR, RTC_CR_REFCKON);
}

/**
  * @brief  Disable RTC_REFIN reference clock detection (50 or 60 Hz)
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function)
  * @rmtoll
  *  RTC_CR           REFCKON       LL_RTC_DisableRefClock
  */
__STATIC_INLINE void LL_RTC_DisableRefClock(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_REFCKON);
}

/**
  * @brief  Check if reference clock is enabled or not
  * @rmtoll
  *  RTC_CR           REFCKON       LL_RTC_IsEnabledRefClock
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsEnabledRefClock(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_REFCKON) == (RTC_CR_REFCKON)) ? 1U : 0U);
}

/**
  * @brief  Set the different prescalers factor
  * @rmtoll
  *  RTC_PRER         PREDIV_A      LL_RTC_SetPrescalers \n
  *  RTC_PRER         PREDIV_S      LL_RTC_SetPrescalers
  * @param  AsynchPrescaler Value between Min_Data = 0 and Max_Data = 0x7F
  * @param  SynchPrescaler Value between Min_Data = 0 and Max_Data = 0x7FFF
  */
__STATIC_INLINE void LL_RTC_SetPrescalers(uint32_t AsynchPrescaler, uint32_t SynchPrescaler)
{
  WRITE_REG(RTC->PRER, (SynchPrescaler | (AsynchPrescaler << RTC_PRER_PREDIV_A_Pos)));
}

/**
  * @brief  Get the different prescalers factor
  * @rmtoll
  *  RTC_PRER         PREDIV_A      LL_RTC_GetPrescalers \n
  *  RTC_PRER         PREDIV_S      LL_RTC_GetPrescalers
  * @retval AsynchPrescaler Value between Min_Data = 0 and Max_Data = 0x7F and
  *         SynchPrescaler Value between Min_Data = 0 and Max_Data = 0x7FFF
  */
__STATIC_INLINE uint32_t LL_RTC_GetPrescalers(void)
{
  return READ_REG(RTC->PRER);
}

/**
  * @brief  Set Asynchronous prescaler factor
  * @rmtoll
  *  RTC_PRER         PREDIV_A      LL_RTC_SetAsynchPrescaler
  * @param  AsynchPrescaler Value between Min_Data = 0 and Max_Data = 0x7F
  */
__STATIC_INLINE void LL_RTC_SetAsynchPrescaler(uint32_t AsynchPrescaler)
{
  MODIFY_REG(RTC->PRER, RTC_PRER_PREDIV_A, AsynchPrescaler << RTC_PRER_PREDIV_A_Pos);
}

/**
  * @brief  Set Synchronous prescaler factor
  * @rmtoll
  *  RTC_PRER         PREDIV_S      LL_RTC_SetSynchPrescaler
  * @param  SynchPrescaler Value between Min_Data = 0 and Max_Data = 0x7FFF
  */
__STATIC_INLINE void LL_RTC_SetSynchPrescaler(uint32_t SynchPrescaler)
{
  MODIFY_REG(RTC->PRER, RTC_PRER_PREDIV_S, SynchPrescaler);
}

/**
  * @brief  Get Asynchronous prescaler factor
  * @rmtoll
  *  RTC_PRER         PREDIV_A      LL_RTC_GetAsynchPrescaler
  * @retval Value between Min_Data = 0 and Max_Data = 0x7F
  */
__STATIC_INLINE uint32_t LL_RTC_GetAsynchPrescaler(void)
{
  return (uint32_t)(READ_BIT(RTC->PRER, RTC_PRER_PREDIV_A) >> RTC_PRER_PREDIV_A_Pos);
}

/**
  * @brief  Get Synchronous prescaler factor
  * @rmtoll
  *  RTC_PRER         PREDIV_S      LL_RTC_GetSynchPrescaler
  * @retval Value between Min_Data = 0 and Max_Data = 0x7FFF
  */
__STATIC_INLINE uint32_t LL_RTC_GetSynchPrescaler(void)
{
  return (uint32_t)(READ_BIT(RTC->PRER, RTC_PRER_PREDIV_S));
}

/**
  * @brief  Enable the write protection for RTC registers
  * @rmtoll
  *  RTC_WPR          KEY           LL_RTC_EnableWriteProtection
  */
__STATIC_INLINE void LL_RTC_EnableWriteProtection(void)
{
  WRITE_REG(RTC->WPR, RTC_WRITE_PROTECTION_DISABLE);
}

/**
  * @brief  Disable the write protection for RTC registers
  * @rmtoll
  *  RTC_WPR          KEY           LL_RTC_DisableWriteProtection
  */
__STATIC_INLINE void LL_RTC_DisableWriteProtection(void)
{
  WRITE_REG(RTC->WPR, RTC_WRITE_PROTECTION_ENABLE_1);
  WRITE_REG(RTC->WPR, RTC_WRITE_PROTECTION_ENABLE_2);
}

/**
  * @brief  Enable tamper output
  * @note   When the tamper output is enabled, all external and internal tamper flags
  *         are ORed and routed to the TAMPALRM output
  * @rmtoll
  *  RTC_CR           TAMPOE       LL_RTC_EnableTamperOutput
  */
__STATIC_INLINE void LL_RTC_EnableTamperOutput(void)
{
  SET_BIT(RTC->CR, RTC_CR_TAMPOE);
}

/**
  * @brief  Disable tamper output
  * @rmtoll
  *  RTC_CR           TAMPOE       LL_RTC_DisableTamperOutput
  */
__STATIC_INLINE void LL_RTC_DisableTamperOutput(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_TAMPOE);
}

/**
  * @brief  Check if tamper output is enabled or not
  * @rmtoll
  *  RTC_CR           TAMPOE       LL_RTC_IsEnabledTamperOutput
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsEnabledTamperOutput(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_TAMPOE) == (RTC_CR_TAMPOE)) ? 1U : 0U);
}

/**
  * @brief  Enable internal pull-up in output mode
  * @rmtoll
  *  RTC_CR           TAMPALRM_PU       LL_RTC_EnableAlarmPullUp
  */
__STATIC_INLINE void LL_RTC_EnableAlarmPullUp(void)
{
  SET_BIT(RTC->CR, RTC_CR_TAMPALRM_PU);
}

/**
  * @brief  Disable internal pull-up in output mode
  * @rmtoll
  *  RTC_CR           TAMPALRM_PU       LL_RTC_DisableAlarmPullUp
  */
__STATIC_INLINE void LL_RTC_DisableAlarmPullUp(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_TAMPALRM_PU);
}

/**
  * @brief  Check if internal pull-up in output mode is enabled or not
  * @rmtoll
  *  RTC_CR           TAMPALRM_PU       LL_RTC_IsEnabledAlarmPullUp
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsEnabledAlarmPullUp(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_TAMPALRM_PU) == (RTC_CR_TAMPALRM_PU)) ? 1U : 0U);
}

/**
  * @brief  Enable RTC_OUT2 output
  * @note   RTC_OUT2 mapping depends on both OSEL (@ref LL_RTC_SetAlarmOutEvent)
  *         and COE (@ref LL_RTC_CAL_SetOutputFreq) settings
  * @rmtoll
  *  RTC_CR           OUT2EN       LL_RTC_EnableOutput2
  */
__STATIC_INLINE void LL_RTC_EnableOutput2(void)
{
  SET_BIT(RTC->CR, RTC_CR_OUT2EN);
}

/**
  * @brief  Disable RTC_OUT2 output
  * @rmtoll
  *  RTC_CR           OUT2EN       LL_RTC_DisableOutput2
  */
__STATIC_INLINE void LL_RTC_DisableOutput2(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_OUT2EN);
}

/**
  * @brief  Check if RTC_OUT2 output is enabled or not
  * @rmtoll
  *  RTC_CR           OUT2EN       LL_RTC_IsEnabledOutput2
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsEnabledOutput2(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_OUT2EN) == (RTC_CR_OUT2EN)) ? 1U : 0U);
}


/**
  * @brief  Enable the output of the calibration signal or tampalarm signal
  * @rmtoll
  *  RTC_CR        OUT2EN        LL_RTC_EnableOutput \n
  *  RTC_CR        TAMPOE        LL_RTC_EnableOutput \n
  *  RTC_CR        OSEL          LL_RTC_EnableOutput \n
  *  RTC_CR        COE           LL_RTC_EnableOutput \n
  *  RTC_CR        COSEL         LL_RTC_EnableOutput
  * @param  Output This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARMOUT_ALARM_A
  *         @arg @ref LL_RTC_ALARMOUT_ALARM_B
  *         @arg @ref LL_RTC_ALARM_OUTPUT_REMAP_POS1
  *         @arg @ref LL_RTC_ALARMOUT_WAKEUP
  *         @arg @ref LL_RTC_OUTPUT_TAMPER_ENABLE
  *         @arg @ref LL_RTC_CALIB_OUTPUT_1HZ
  *         @arg @ref LL_RTC_CALIB_OUTPUT_512HZ
  */
__STATIC_INLINE void LL_RTC_EnableOutput(uint32_t Output)
{
  MODIFY_REG(RTC->CR, RTC_CR_OUT2EN | RTC_CR_TAMPOE | RTC_CR_OSEL_0 | RTC_CR_OSEL_1 | RTC_CR_COE | RTC_CR_COSEL,
             Output);
}

/**
  * @brief  Disable the output of the calibration signal or tampalarm signal
  * @rmtoll
  *  RTC_CR              OUT2EN        LL_RTC_DisableOutput \n
  *  RTC_CR              TAMPOE        LL_RTC_DisableOutput \n
  *  RTC_CR              OSEL          LL_RTC_DisableOutput \n
  *  RTC_CR              COE           LL_RTC_DisableOutput \n
  *  RTC_CR              COSEL         LL_RTC_DisableOutput
  */
__STATIC_INLINE void LL_RTC_DisableOutput(void)
{
  MODIFY_REG(RTC->CR, RTC_CR_OUT2EN | RTC_CR_TAMPOE | RTC_CR_OSEL_0 | RTC_CR_OSEL_1 | RTC_CR_COE | RTC_CR_COSEL, 0U);
}

/**
  * @brief  Get the output status of the calibration signal or tampalarm signal
  * @rmtoll
  *  RTC_CR              OUT2EN        LL_RTC_IsEnabledOutput \n
  *  TAMPOE        LL_RTC_IsEnabledOutput \n
  *  OSEL          LL_RTC_IsEnabledOutput \n
  *  COE           LL_RTC_IsEnabledOutput \n
  *  COSEL         LL_RTC_IsEnabledOutput
  * @retval 0 output disabled
  * @retval 1 output enabled
  */
__STATIC_INLINE uint32_t LL_RTC_IsEnabledOutput(void)
{
  return (((READ_REG(RTC->CR) & (RTC_CR_OUT2EN | RTC_CR_TAMPOE | RTC_CR_OSEL_0 | RTC_CR_OSEL_1 | RTC_CR_COE |
                                 RTC_CR_COSEL)) == 0U) ? 0U : 1U);
}

/**
  * @brief  Get the output detailed status of the calibration signal or tampalarm signal
  * @rmtoll
  *  RTC_CR              OUT2EN        LL_RTC_IsEnabledDetailedOutput \n
  *  RTC_CR              AMPOE         LL_RTC_IsEnabledDetailedOutput \n
  *  RTC_CR              OSEL          LL_RTC_IsEnabledDetailedOutput \n
  *  RTC_CR              COE           LL_RTC_IsEnabledDetailedOutput \n
  *  RTC_CR              COSEL         LL_RTC_IsEnabledDetailedOutput
  * @param  Output This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARMOUT_ALARM_A
  *         @arg @ref LL_RTC_ALARMOUT_ALARM_B
  *         @arg @ref LL_RTC_ALARM_OUTPUT_REMAP_POS1
  *         @arg @ref LL_RTC_ALARMOUT_WAKEUP
  *         @arg @ref LL_RTC_OUTPUT_TAMPER_ENABLE
  *         @arg @ref LL_RTC_CALIB_OUTPUT_1HZ
  *         @arg @ref LL_RTC_CALIB_OUTPUT_512HZ
  * @retval 0 output disabled, 1 output enabled
  */
__STATIC_INLINE uint32_t LL_RTC_IsEnabledDetailedOutput(const uint32_t Output)
{
  return (((READ_REG(RTC->CR) & (RTC_CR_OUT2EN | RTC_CR_TAMPOE | RTC_CR_OSEL_0 | RTC_CR_OSEL_1 |
                                 RTC_CR_COE | RTC_CR_COSEL)) == Output) ? 1U : 0U);


}

/**
  * @brief  Configure the Output polarity and pull-up
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           POL                      LL_RTC_ConfigTampalarm \n
  *  RTC_CR           TAMPALRM_TYPE            LL_RTC_ConfigTampalarm \n
  *  RTC_CR           TAMPALRM_PU              LL_RTC_ConfigTampalarm
  * @param  Polarity This parameter can be one of the following values:
  *         @arg @ref LL_RTC_OUTPUTPOLARITY_PIN_HIGH
  *         @arg @ref LL_RTC_OUTPUTPOLARITY_PIN_LOW
  * @param  Type This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_OUTPUTTYPE_OPENDRAIN
  *         @arg @ref LL_RTC_ALARM_OUTPUTTYPE_PUSHPULL
  * @param  PullUp This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_OUTPUT_PULLUP_NONE
  *         @arg @ref LL_RTC_ALARM_OUTPUT_PULLUP_ON
  */
__STATIC_INLINE void LL_RTC_ConfigTampalarm(uint32_t Polarity,
                                            uint32_t Type, uint32_t PullUp)
{
  MODIFY_REG(RTC->CR, RTC_CR_POL | RTC_CR_TAMPALRM_TYPE | RTC_CR_TAMPALRM_PU, Polarity | Type | PullUp);
}

/**
  * @}
  */

/** @defgroup RTC_LL_EF_Time Time
  * @{
  */

/**
  * @brief  Set time format (AM/24-hour or PM notation)
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function)
  * @rmtoll
  *  RTC_TR           PM            LL_RTC_TIME_SetFormat
  * @param  TimeFormat This parameter can be one of the following values:
  *         @arg @ref LL_RTC_TIME_FORMAT_AM_24H
  *         @arg @ref LL_RTC_TIME_FORMAT_PM
  */
__STATIC_INLINE void LL_RTC_TIME_SetFormat(uint32_t TimeFormat)
{
  MODIFY_REG(RTC->TR, RTC_TR_PM, TimeFormat);
}

/**
  * @brief  Get time format (AM/24-hour or PM notation)
  * @note   if RTC shadow registers are not bypassed (BYPSHAD=0), need to check if RSF flag is set
  *         before reading this bit
  * @note   Read either RTC_SSR or RTC_TR locks the values in the higher-order calendar
  *         shadow registers until RTC_DR is read (LL_RTC_READ_REG(DR))
  * @rmtoll
  *  RTC_TR           PM            LL_RTC_TIME_GetFormat
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_TIME_FORMAT_AM_24H
  *         @arg @ref LL_RTC_TIME_FORMAT_PM
  */
__STATIC_INLINE uint32_t LL_RTC_TIME_GetFormat(void)
{
  return (uint32_t)(READ_BIT(RTC->TR, RTC_TR_PM));
}

/**
  * @brief  Set Hours in BCD format
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function)
  * @note   helper macro LL_RTC_CONVERT_BIN2BCD is available to convert hour from binary to BCD format
  * @rmtoll
  *  RTC_TR           HT            LL_RTC_TIME_SetHour \n
  *  RTC_TR           HU            LL_RTC_TIME_SetHour
  * @param  Hours Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  */
__STATIC_INLINE void LL_RTC_TIME_SetHour(uint32_t Hours)
{
  MODIFY_REG(RTC->TR, (RTC_TR_HT | RTC_TR_HU),
             (((Hours & 0xF0U) << (RTC_TR_HT_Pos - 4U)) | ((Hours & 0x0FU) << RTC_TR_HU_Pos)));
}

/**
  * @brief  Get Hours in BCD format
  * @note   if RTC shadow registers are not bypassed (BYPSHAD=0), need to check if RSF flag is set
  *         before reading this bit
  * @note   Read either RTC_SSR or RTC_TR locks the values in the higher-order calendar
  *         shadow registers until RTC_DR is read (LL_RTC_READ_REG(DR))
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert hour from BCD to
  *         Binary format
  * @rmtoll
  *  RTC_TR           HT            LL_RTC_TIME_GetHour \n
  *  RTC_TR           HU            LL_RTC_TIME_GetHour
  * @retval Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  */
__STATIC_INLINE uint32_t LL_RTC_TIME_GetHour(void)
{
  return (uint32_t)((READ_BIT(RTC->TR, (RTC_TR_HT | RTC_TR_HU))) >> RTC_TR_HU_Pos);
}

/**
  * @brief  Set Minutes in BCD format
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function)
  * @note   helper macro LL_RTC_CONVERT_BIN2BCD is available to convert Minutes from binary to BCD format
  * @rmtoll
  *  RTC_TR           MNT           LL_RTC_TIME_SetMinute \n
  *  RTC_TR           MNU           LL_RTC_TIME_SetMinute
  * @param  Minutes Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE void LL_RTC_TIME_SetMinute(uint32_t Minutes)
{
  MODIFY_REG(RTC->TR, (RTC_TR_MNT | RTC_TR_MNU),
             (((Minutes & 0xF0U) << (RTC_TR_MNT_Pos - 4U)) | ((Minutes & 0x0FU) << RTC_TR_MNU_Pos)));
}

/**
  * @brief  Get Minutes in BCD format
  * @note   if RTC shadow registers are not bypassed (BYPSHAD=0), need to check if RSF flag is set
  *         before reading this bit
  * @note   Read either RTC_SSR or RTC_TR locks the values in the higher-order calendar
  *         shadow registers until RTC_DR is read (LL_RTC_READ_REG(DR))
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert minute from BCD
  *         to Binary format
  * @rmtoll
  *  RTC_TR           MNT           LL_RTC_TIME_GetMinute \n
  *  RTC_TR           MNU           LL_RTC_TIME_GetMinute
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t LL_RTC_TIME_GetMinute(void)
{
  return (uint32_t)(READ_BIT(RTC->TR, (RTC_TR_MNT | RTC_TR_MNU)) >> RTC_TR_MNU_Pos);
}

/**
  * @brief  Set Seconds in BCD format
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function)
  * @note   helper macro LL_RTC_CONVERT_BIN2BCD is available to convert Seconds from binary to BCD format
  * @rmtoll
  *  RTC_TR           ST            LL_RTC_TIME_SetSecond \n
  *  RTC_TR           SU            LL_RTC_TIME_SetSecond
  * @param  Seconds Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE void LL_RTC_TIME_SetSecond(uint32_t Seconds)
{
  MODIFY_REG(RTC->TR, (RTC_TR_ST | RTC_TR_SU),
             (((Seconds & 0xF0U) << (RTC_TR_ST_Pos - 4U)) | ((Seconds & 0x0FU) << RTC_TR_SU_Pos)));
}

/**
  * @brief  Get Seconds in BCD format
  * @note   if RTC shadow registers are not bypassed (BYPSHAD=0), need to check if RSF flag is set
  *         before reading this bit
  * @note   Read either RTC_SSR or RTC_TR locks the values in the higher-order calendar
  *         shadow registers until RTC_DR is read (LL_RTC_READ_REG(DR))
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Seconds from BCD
  *         to Binary format
  * @rmtoll
  *  RTC_TR           ST            LL_RTC_TIME_GetSecond \n
  *  RTC_TR           SU            LL_RTC_TIME_GetSecond
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t LL_RTC_TIME_GetSecond(void)
{
  return (uint32_t)(READ_BIT(RTC->TR, (RTC_TR_ST | RTC_TR_SU)) >> RTC_TR_SU_Pos);
}

/**
  * @brief  Set time (hour, minute and second) in BCD format
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function)
  * @note   TimeFormat and Hours must preferably follow the same format
  * @rmtoll
  *  RTC_TR           PM            LL_RTC_TIME_Config \n
  *  RTC_TR           HT            LL_RTC_TIME_Config \n
  *  RTC_TR           HU            LL_RTC_TIME_Config \n
  *  RTC_TR           MNT           LL_RTC_TIME_Config \n
  *  RTC_TR           MNU           LL_RTC_TIME_Config \n
  *  RTC_TR           ST            LL_RTC_TIME_Config \n
  *  RTC_TR           SU            LL_RTC_TIME_Config
  * @param  Format12_24 This parameter can be one of the following values:
  *         @arg @ref LL_RTC_TIME_FORMAT_AM_24H
  *         @arg @ref LL_RTC_TIME_FORMAT_PM
  * @param  Hours Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  * @param  Minutes Value between Min_Data=0x00 and Max_Data=0x59
  * @param  Seconds Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE void LL_RTC_TIME_Config(uint32_t Format12_24, uint32_t Hours, uint32_t Minutes,
                                        uint32_t Seconds)
{
  uint32_t temp;

  temp = Format12_24                                                                                    | \
         (((Hours & 0xF0U) << (RTC_TR_HT_Pos - 4U)) | ((Hours & 0x0FU) << RTC_TR_HU_Pos))     | \
         (((Minutes & 0xF0U) << (RTC_TR_MNT_Pos - 4U)) | ((Minutes & 0x0FU) << RTC_TR_MNU_Pos)) | \
         (((Seconds & 0xF0U) << (RTC_TR_ST_Pos - 4U)) | ((Seconds & 0x0FU) << RTC_TR_SU_Pos));
  WRITE_REG(RTC->TR, temp);
}

/**
  * @brief  Get time (hour, minute and second) in BCD format
  * @note   if RTC shadow registers are not bypassed (BYPSHAD=0), need to check if RSF flag is set
  *         before reading this bit
  * @note   Read either RTC_SSR or RTC_TR locks the values in the higher-order calendar
  *         shadow registers until RTC_DR is read (LL_RTC_READ_REG(DR))
  * @note   helper macros LL_RTC_GET_HOUR, LL_RTC_GET_MINUTE and LL_RTC_GET_SECOND
  *         are available to get independently each parameter
  * @rmtoll
  *  RTC_TR           HT            LL_RTC_TIME_Get \n
  *  RTC_TR           HU            LL_RTC_TIME_Get \n
  *  RTC_TR           MNT           LL_RTC_TIME_Get \n
  *  RTC_TR           MNU           LL_RTC_TIME_Get \n
  *  RTC_TR           ST            LL_RTC_TIME_Get \n
  *  RTC_TR           SU            LL_RTC_TIME_Get
  * @retval Combination of hours, minutes and seconds (Format: 0x00HHMMSS)
  */
__STATIC_INLINE uint32_t LL_RTC_TIME_Get(void)
{
  uint32_t temp;

  temp = READ_BIT(RTC->TR, (RTC_TR_HT | RTC_TR_HU | RTC_TR_MNT | RTC_TR_MNU | RTC_TR_ST | RTC_TR_SU));
  return (uint32_t)((((((temp & RTC_TR_HT) >> RTC_TR_HT_Pos) << 4U) | ((temp & RTC_TR_HU) >> RTC_TR_HU_Pos)) \
                     << RTC_OFFSET_HOUR) | (((((temp & RTC_TR_MNT) >> RTC_TR_MNT_Pos) << 4U) | \
                                             ((temp & RTC_TR_MNU) >> RTC_TR_MNU_Pos)) << RTC_OFFSET_MINUTE) | \
                    ((((temp & RTC_TR_ST) >> RTC_TR_ST_Pos) << 4U) | ((temp & RTC_TR_SU) >> RTC_TR_SU_Pos)));
}

/**
  * @brief  Get time (hour, minute and second) in BCD format and time format
  * @note   helper macros LL_RTC_GET_FORMAT LL_RTC_GET_HOUR, LL_RTC_GET_MINUTE
  *         and LL_RTC_GET_SECOND are available to get independently each parameter
  * @rmtoll
  *  RTC_TR        PM            LL_RTC_TIME_GetTimeAndFormat \n
  *  RTC_TR        HT            LL_RTC_TIME_GetTimeAndFormat \n
  *  RTC_TR        HU            LL_RTC_TIME_GetTimeAndFormat \n
  *  RTC_TR        MNT           LL_RTC_TIME_GetTimeAndFormat \n
  *  RTC_TR        MNU           LL_RTC_TIME_GetTimeAndFormat \n
  *  RTC_TR        ST            LL_RTC_TIME_GetTimeAndFormat \n
  *  RTC_TR        SU            LL_RTC_TIME_GetTimeAndFormat
  * @retval Combination of format, hours, minutes and seconds (Format: 0x0FHHMMSS)
  */
__STATIC_INLINE uint32_t LL_RTC_TIME_GetTimeAndFormat(void)
{
  uint32_t temp;

  temp = READ_REG(RTC->TR);
  return (uint32_t)((((temp & RTC_TR_PM) >> RTC_TR_PM_Pos) << RTC_OFFSET_FORMAT) | \
                    (((((temp & RTC_TR_HT) >> RTC_TR_HT_Pos) << 4U) | ((temp & RTC_TR_HU) >> RTC_TR_HU_Pos)) \
                     << RTC_OFFSET_HOUR) | (((((temp & RTC_TR_MNT) >> RTC_TR_MNT_Pos) << 4U) | \
                                             ((temp & RTC_TR_MNU) >> RTC_TR_MNU_Pos)) << RTC_OFFSET_MINUTE) | \
                    ((((temp & RTC_TR_ST) >> RTC_TR_ST_Pos) << 4U) | ((temp & RTC_TR_SU) >> RTC_TR_SU_Pos)));
}

/**
  * @brief  Memorize whether the daylight saving time change has been performed
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           BKP           LL_RTC_TIME_EnableDayLightStore
  */
__STATIC_INLINE void LL_RTC_TIME_EnableDayLightStore(void)
{
  SET_BIT(RTC->CR, RTC_CR_BKP);
}

/**
  * @brief  Disable memorization whether the daylight saving time change has been performed
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           BKP           LL_RTC_TIME_DisableDayLightStore
  */
__STATIC_INLINE void LL_RTC_TIME_DisableDayLightStore(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_BKP);
}

/**
  * @brief  Check if RTC Day Light Saving stored operation is enabled or not
  * @rmtoll
  *  RTC_CR           BKP           LL_RTC_TIME_IsEnabledDayLightStore
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_TIME_IsEnabledDayLightStore(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_BKP) == (RTC_CR_BKP)) ? 1U : 0U);
}

/**
  * @brief  Subtract 1 hour (winter time change)
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           SUB1H         LL_RTC_TIME_DecHour
  */
__STATIC_INLINE void LL_RTC_TIME_DecHour(void)
{
  SET_BIT(RTC->CR, RTC_CR_SUB1H);
}

/**
  * @brief  Add 1 hour (summer time change)
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           ADD1H         LL_RTC_TIME_IncHour
  */
__STATIC_INLINE void LL_RTC_TIME_IncHour(void)
{
  SET_BIT(RTC->CR, RTC_CR_ADD1H);
}

/**
  * @brief  Get Sub second value in the synchronous prescaler counter
  * @note   You can use both SubSeconds value and SecondFraction (PREDIV_S through
  *         LL_RTC_GetSynchPrescaler function) terms returned to convert Calendar
  *         SubSeconds value in second fraction ratio with time unit following
  *         generic formula:
  *         ==> Seconds fraction ratio * time_unit= [(SecondFraction-SubSeconds)/(SecondFraction+1)] * time_unit
  *         This conversion can be performed only if no shift operation is pending
  *         (ie. SHFP=0) when PREDIV_S >= SS
  * @rmtoll
  *  RTC_SSR          SS            LL_RTC_TIME_GetSubSecond
  * @retval If binary mode is none, Value between Min_Data=0x0 and Max_Data=0x7FFF
  *         else Value between Min_Data=0x0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_RTC_TIME_GetSubSecond(void)
{
  return (uint32_t)(READ_BIT(RTC->SSR, RTC_SSR_SS));
}

/**
  * @brief  Synchronize to a remote clock with a high degree of precision
  * @note   This operation effectively subtracts from (delays) or advance the clock of a fraction of a second
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   When REFCKON is set, firmware must not write to Shift control register
  * @rmtoll
  *  RTC_SHIFTR       ADD1S         LL_RTC_TIME_Synchronize \n
  *  RTC_SHIFTR       SUBFS         LL_RTC_TIME_Synchronize
  * @param  ShiftSecond This parameter can be one of the following values:
  *         @arg @ref LL_RTC_SHIFT_SECOND_DELAY
  *         @arg @ref LL_RTC_SHIFT_SECOND_ADVANCE
  * @param  Fraction Number of Seconds Fractions (any value from 0 to 0x7FFF)
  */
__STATIC_INLINE void LL_RTC_TIME_Synchronize(uint32_t ShiftSecond, uint32_t Fraction)
{
  WRITE_REG(RTC->SHIFTR, ShiftSecond | Fraction);
}

/**
  * @}
  */

/** @defgroup RTC_LL_EF_Date Date
  * @{
  */

/**
  * @brief  Set Year in BCD format
  * @note   helper macro LL_RTC_CONVERT_BIN2BCD is available to convert Year from binary to BCD format
  * @rmtoll
  *  RTC_DR           YT            LL_RTC_DATE_SetYear \n
  *  RTC_DR           YU            LL_RTC_DATE_SetYear
  * @param  Year Value between Min_Data=0x00 and Max_Data=0x99
  */
__STATIC_INLINE void LL_RTC_DATE_SetYear(uint32_t Year)
{
  MODIFY_REG(RTC->DR, (RTC_DR_YT | RTC_DR_YU),
             (((Year & 0xF0U) << (RTC_DR_YT_Pos - 4U)) | ((Year & 0x0FU) << RTC_DR_YU_Pos)));
}

/**
  * @brief  Get Year in BCD format
  * @note   if RTC shadow registers are not bypassed (BYPSHAD=0), need to check if RSF flag is set
  *         before reading this bit
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Year from BCD to Binary format
  * @rmtoll
  *  RTC_DR           YT            LL_RTC_DATE_GetYear \n
  *  RTC_DR           YU            LL_RTC_DATE_GetYear
  * @retval Value between Min_Data=0x00 and Max_Data=0x99
  */
__STATIC_INLINE uint32_t LL_RTC_DATE_GetYear(void)
{
  return (uint32_t)((READ_BIT(RTC->DR, (RTC_DR_YT | RTC_DR_YU))) >> RTC_DR_YU_Pos);
}

/**
  * @brief  Set Week day
  * @rmtoll
  *  RTC_DR           WDU           LL_RTC_DATE_SetWeekDay
  * @param  WeekDay This parameter can be one of the following values:
  *         @arg @ref LL_RTC_WEEKDAY_MONDAY
  *         @arg @ref LL_RTC_WEEKDAY_TUESDAY
  *         @arg @ref LL_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref LL_RTC_WEEKDAY_THURSDAY
  *         @arg @ref LL_RTC_WEEKDAY_FRIDAY
  *         @arg @ref LL_RTC_WEEKDAY_SATURDAY
  *         @arg @ref LL_RTC_WEEKDAY_SUNDAY
  */
__STATIC_INLINE void LL_RTC_DATE_SetWeekDay(uint32_t WeekDay)
{
  MODIFY_REG(RTC->DR, RTC_DR_WDU, WeekDay << RTC_DR_WDU_Pos);
}

/**
  * @brief  Get Week day
  * @note   if RTC shadow registers are not bypassed (BYPSHAD=0), need to check if RSF flag is set
  *         before reading this bit
  * @rmtoll
  *  RTC_DR           WDU           LL_RTC_DATE_GetWeekDay
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_WEEKDAY_MONDAY
  *         @arg @ref LL_RTC_WEEKDAY_TUESDAY
  *         @arg @ref LL_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref LL_RTC_WEEKDAY_THURSDAY
  *         @arg @ref LL_RTC_WEEKDAY_FRIDAY
  *         @arg @ref LL_RTC_WEEKDAY_SATURDAY
  *         @arg @ref LL_RTC_WEEKDAY_SUNDAY
  */
__STATIC_INLINE uint32_t LL_RTC_DATE_GetWeekDay(void)
{
  return (uint32_t)(READ_BIT(RTC->DR, RTC_DR_WDU) >> RTC_DR_WDU_Pos);
}

/**
  * @brief  Set Month in BCD format
  * @note   helper macro LL_RTC_CONVERT_BIN2BCD is available to convert Month from binary to BCD format
  * @rmtoll
  *  RTC_DR           MT            LL_RTC_DATE_SetMonth \n
  *  RTC_DR           MU            LL_RTC_DATE_SetMonth
  * @param  Month This parameter can be one of the following values:
  *         @arg @ref LL_RTC_MONTH_JANUARY
  *         @arg @ref LL_RTC_MONTH_FEBRUARY
  *         @arg @ref LL_RTC_MONTH_MARCH
  *         @arg @ref LL_RTC_MONTH_APRIL
  *         @arg @ref LL_RTC_MONTH_MAY
  *         @arg @ref LL_RTC_MONTH_JUNE
  *         @arg @ref LL_RTC_MONTH_JULY
  *         @arg @ref LL_RTC_MONTH_AUGUST
  *         @arg @ref LL_RTC_MONTH_SEPTEMBER
  *         @arg @ref LL_RTC_MONTH_OCTOBER
  *         @arg @ref LL_RTC_MONTH_NOVEMBER
  *         @arg @ref LL_RTC_MONTH_DECEMBER
  */
__STATIC_INLINE void LL_RTC_DATE_SetMonth(uint32_t Month)
{
  MODIFY_REG(RTC->DR, (RTC_DR_MT | RTC_DR_MU),
             (((Month & 0xF0U) << (RTC_DR_MT_Pos - 4U)) | ((Month & 0x0FU) << RTC_DR_MU_Pos)));
}

/**
  * @brief  Get Month in BCD format
  * @note   if RTC shadow registers are not bypassed (BYPSHAD=0), need to check if RSF flag is set
  *         before reading this bit
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Month from BCD to Binary format
  * @rmtoll
  *  RTC_DR           MT            LL_RTC_DATE_GetMonth \n
  *  RTC_DR           MU            LL_RTC_DATE_GetMonth
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_MONTH_JANUARY
  *         @arg @ref LL_RTC_MONTH_FEBRUARY
  *         @arg @ref LL_RTC_MONTH_MARCH
  *         @arg @ref LL_RTC_MONTH_APRIL
  *         @arg @ref LL_RTC_MONTH_MAY
  *         @arg @ref LL_RTC_MONTH_JUNE
  *         @arg @ref LL_RTC_MONTH_JULY
  *         @arg @ref LL_RTC_MONTH_AUGUST
  *         @arg @ref LL_RTC_MONTH_SEPTEMBER
  *         @arg @ref LL_RTC_MONTH_OCTOBER
  *         @arg @ref LL_RTC_MONTH_NOVEMBER
  *         @arg @ref LL_RTC_MONTH_DECEMBER
  */
__STATIC_INLINE uint32_t LL_RTC_DATE_GetMonth(void)
{
  return (uint32_t)((READ_BIT(RTC->DR, (RTC_DR_MT | RTC_DR_MU))) >> RTC_DR_MU_Pos);
}

/**
  * @brief  Set Day in BCD format
  * @note   helper macro LL_RTC_CONVERT_BIN2BCD is available to convert Day from binary to BCD format
  * @rmtoll
  *  RTC_DR           DT            LL_RTC_DATE_SetDay \n
  *  RTC_DR           DU            LL_RTC_DATE_SetDay
  * @param  Day Value between Min_Data=0x01 and Max_Data=0x31
  */
__STATIC_INLINE void LL_RTC_DATE_SetDay(uint32_t Day)
{
  MODIFY_REG(RTC->DR, (RTC_DR_DT | RTC_DR_DU),
             (((Day & 0xF0U) << (RTC_DR_DT_Pos - 4U)) | ((Day & 0x0FU) << RTC_DR_DU_Pos)));
}

/**
  * @brief  Get Day in BCD format
  * @note   if RTC shadow registers are not bypassed (BYPSHAD=0), need to check if RSF flag is set
  *         before reading this bit
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Day from BCD to Binary format
  * @rmtoll
  *  RTC_DR           DT            LL_RTC_DATE_GetDay \n
  *  RTC_DR           DU            LL_RTC_DATE_GetDay
  * @retval Value between Min_Data=0x01 and Max_Data=0x31
  */
__STATIC_INLINE uint32_t LL_RTC_DATE_GetDay(void)
{
  return (uint32_t)((READ_BIT(RTC->DR, (RTC_DR_DT | RTC_DR_DU))) >> RTC_DR_DU_Pos);
}

/**
  * @brief  Set date (WeekDay, Day, Month and Year) in BCD format
  * @rmtoll
  *  RTC_DR           WDU           LL_RTC_DATE_Config \n
  *  RTC_DR           MT            LL_RTC_DATE_Config \n
  *  RTC_DR           MU            LL_RTC_DATE_Config \n
  *  RTC_DR           DT            LL_RTC_DATE_Config \n
  *  RTC_DR           DU            LL_RTC_DATE_Config \n
  *  RTC_DR           YT            LL_RTC_DATE_Config \n
  *  RTC_DR           YU            LL_RTC_DATE_Config
  * @param  WeekDay This parameter can be one of the following values:
  *         @arg @ref LL_RTC_WEEKDAY_MONDAY
  *         @arg @ref LL_RTC_WEEKDAY_TUESDAY
  *         @arg @ref LL_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref LL_RTC_WEEKDAY_THURSDAY
  *         @arg @ref LL_RTC_WEEKDAY_FRIDAY
  *         @arg @ref LL_RTC_WEEKDAY_SATURDAY
  *         @arg @ref LL_RTC_WEEKDAY_SUNDAY
  * @param  Day Value between Min_Data=0x01 and Max_Data=0x31
  * @param  Month This parameter can be one of the following values:
  *         @arg @ref LL_RTC_MONTH_JANUARY
  *         @arg @ref LL_RTC_MONTH_FEBRUARY
  *         @arg @ref LL_RTC_MONTH_MARCH
  *         @arg @ref LL_RTC_MONTH_APRIL
  *         @arg @ref LL_RTC_MONTH_MAY
  *         @arg @ref LL_RTC_MONTH_JUNE
  *         @arg @ref LL_RTC_MONTH_JULY
  *         @arg @ref LL_RTC_MONTH_AUGUST
  *         @arg @ref LL_RTC_MONTH_SEPTEMBER
  *         @arg @ref LL_RTC_MONTH_OCTOBER
  *         @arg @ref LL_RTC_MONTH_NOVEMBER
  *         @arg @ref LL_RTC_MONTH_DECEMBER
  * @param  Year Value between Min_Data=0x00 and Max_Data=0x99
  */
__STATIC_INLINE void LL_RTC_DATE_Config(uint32_t WeekDay, uint32_t Day, uint32_t Month,
                                        uint32_t Year)
{
  uint32_t temp;

  temp = (WeekDay << RTC_DR_WDU_Pos)                                                        | \
         (((Year & 0xF0U) << (RTC_DR_YT_Pos - 4U)) | ((Year & 0x0FU) << RTC_DR_YU_Pos))   | \
         (((Month & 0xF0U) << (RTC_DR_MT_Pos - 4U)) | ((Month & 0x0FU) << RTC_DR_MU_Pos)) | \
         (((Day & 0xF0U) << (RTC_DR_DT_Pos - 4U)) | ((Day & 0x0FU) << RTC_DR_DU_Pos));

  WRITE_REG(RTC->DR, temp);
}

/**
  * @brief  Get date (WeekDay, Day, Month and Year) in BCD format
  * @note   if RTC shadow registers are not bypassed (BYPSHAD=0), need to check if RSF flag is set
  *         before reading this bit
  * @note   helper macros LL_RTC_GET_WEEKDAY, LL_RTC_GET_YEAR, LL_RTC_GET_MONTH,
  *         and LL_RTC_GET_DAY are available to get independently each parameter
  * @rmtoll
  *  RTC_DR           WDU           LL_RTC_DATE_Get \n
  *  RTC_DR           MT            LL_RTC_DATE_Get \n
  *  RTC_DR           MU            LL_RTC_DATE_Get \n
  *  RTC_DR           DT            LL_RTC_DATE_Get \n
  *  RTC_DR           DU            LL_RTC_DATE_Get \n
  *  RTC_DR           YT            LL_RTC_DATE_Get \n
  *  RTC_DR           YU            LL_RTC_DATE_Get
  * @retval Combination of WeekDay, Day, Month and Year (Format: 0xWWDDMMYY)
  */
__STATIC_INLINE uint32_t LL_RTC_DATE_Get(void)
{
  uint32_t temp;

  temp = READ_BIT(RTC->DR, (RTC_DR_WDU | RTC_DR_MT | RTC_DR_MU | RTC_DR_DT | RTC_DR_DU | RTC_DR_YT | RTC_DR_YU));
  return (uint32_t)((((temp & RTC_DR_WDU) >> RTC_DR_WDU_Pos) << RTC_OFFSET_WEEKDAY) | \
                    (((((temp & RTC_DR_DT) >> RTC_DR_DT_Pos) << 4U) | ((temp & RTC_DR_DU) >> RTC_DR_DU_Pos)) \
                     << RTC_OFFSET_DAY)   | (((((temp & RTC_DR_MT) >> RTC_DR_MT_Pos) << 4U) | \
                                              ((temp & RTC_DR_MU) >> RTC_DR_MU_Pos)) << RTC_OFFSET_MONTH) | \
                    ((((temp & RTC_DR_YT) >> RTC_DR_YT_Pos) << 4U) | ((temp & RTC_DR_YU) >> RTC_DR_YU_Pos)));
}

/**
  * @}
  */

/** @defgroup RTC_LL_EF_ALARM ALARMA ALARMB
  * @{
  */

/**
  * @brief  Set alarm A or B Binary mode auto clear
  * @note   This register can be written only when ALRAE or ALRBE is reset in RTC_CR register,
  *         or in initialization mode
  * @note   SSCLR must be kept to 0 when BCD or mixed mode is used (BIN = 00, 10 or 11).
  * @rmtoll
  *  RTC_ALRMASSR    SSCLR        LL_RTC_ALM_SetBinAutoClr \n
  *  RTC_ALRMBSSR    SSCLR        LL_RTC_ALM_SetBinAutoClr
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  * @param  BinaryAutoClr This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALMA_SUBSECONDBIN_AUTOCLR_NO
  *         @arg @ref LL_RTC_ALMA_SUBSECONDBIN_AUTOCLR_YES
  */
__STATIC_INLINE void LL_RTC_ALM_SetBinAutoClr(uint32_t Alarm, uint32_t BinaryAutoClr)
{
  MODIFY_REG(*(&(RTC->ALRMASSR) + (RTC_ALRBSSR_ALRASSR_OFFSET * Alarm)), RTC_ALRMASSR_SSCLR, BinaryAutoClr);
}

/**
  * @brief  Get alarm A or B Binary mode auto clear
  * @rmtoll
  *  RTC_ALRMASSR    SSCLR        LL_RTC_ALM_GetBinAutoClr \n
  *  RTC_ALRMBSSR    SSCLR        LL_RTC_ALM_GetBinAutoClr
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  * @retval Returned value can be can be one of the following values:
  *         @arg @ref LL_RTC_ALMA_SUBSECONDBIN_AUTOCLR_NO
  *         @arg @ref LL_RTC_ALMA_SUBSECONDBIN_AUTOCLR_YES
  */
__STATIC_INLINE uint32_t LL_RTC_ALM_GetBinAutoClr(const uint32_t Alarm)
{
  return (uint32_t)(READ_BIT(*(&(RTC->ALRMASSR) + (RTC_ALRBSSR_ALRASSR_OFFSET * Alarm)), \
                             RTC_ALRMASSR_SSCLR));
}

/**
  * @brief  Set alarm A or B flag automatic clear
  * @note   This register can be written only when ALRAE or ALRBE is reset in RTC_CR register,
  *         or in initialization mode
  * @rmtoll
  *  RTC_CR   ALRAFCLR        LL_RTC_ALM_SetFlagAutoClr \n
  *  RTC_CR   ALRBFCLR        LL_RTC_ALM_SetFlagAutoClr
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  * @param  AutoClr This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALM_AUTOCLR_NO
  *         @arg @ref LL_RTC_ALM_AUTOCLR_YES
  */
__STATIC_INLINE void LL_RTC_ALM_SetFlagAutoClr(uint32_t Alarm, uint32_t AutoClr)
{
  MODIFY_REG(RTC->CR, RTC_CR_ALRAFCLR << Alarm, AutoClr << Alarm);
}

/**
  * @brief  Get alarm A or B flag automatic clear
  * @rmtoll
  *  RTC_CR   ALRAFCLR        LL_RTC_ALM_GetFlagAutoClr \n
  *  RTC_CR   ALRBFCLR        LL_RTC_ALM_GetFlagAutoClr
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  * @retval Returned value can be can be one of the following values:
  *         @arg @ref LL_RTC_ALM_AUTOCLR_NO
  *         @arg @ref LL_RTC_ALM_AUTOCLR_YES
  */
__STATIC_INLINE uint32_t LL_RTC_ALM_GetFlagAutoClr(const uint32_t Alarm)
{
  return (uint32_t)(READ_BIT(RTC->CR, (RTC_CR_ALRAFCLR << Alarm)) >> Alarm);
}

/**
  * @brief  Set alarm A or B Time (hour, minute and second) in BCD format, time format,
  *         Day (Week day or day), Weekday or day selection and Masks
  * @note   This register can be written only when ALRAE or ALRBE is reset in RTC_CR register,
  *         or in initialization mode
  * @rmtoll
  *  RTC_ALRMBR       PM            LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMBR       HT            LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMBR       HU            LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMBR       MNT           LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMBR       MNU           LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMBR       ST            LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMBR       SU            LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMBR       MSK4          LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMBR       MSK3          LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMBR       MSK2          LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMBR       MSK1          LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMBR       WDSEL         LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMBR       DT            LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMBR       DU            LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMAR       PM            LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMAR       HT            LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMAR       HU            LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMAR       MNT           LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMAR       MNU           LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMAR       ST            LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMAR       SU            LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMAR       MSK4          LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMAR       MSK3          LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMAR       MSK2          LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMAR       MSK1          LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMAR       WDSEL         LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMAR       DT            LL_RTC_ALM_ConfigDateTime \n
  *  RTC_ALRMAR       DU            LL_RTC_ALM_ConfigDateTime
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  * @param  Mask This parameter can be a combination of the following values:
  *         @arg @ref LL_RTC_ALMA_MASK_NONE
  *         @arg @ref LL_RTC_ALMA_MASK_DATEWEEKDAY
  *         @arg @ref LL_RTC_ALMA_MASK_HOURS
  *         @arg @ref LL_RTC_ALMA_MASK_MINUTES
  *         @arg @ref LL_RTC_ALMA_MASK_SECONDS
  *         @arg @ref LL_RTC_ALMA_MASK_ALL
  * @param  DayWeekDaySelection This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALMA_DATEWEEKDAYSEL_DATE
  *         @arg @ref LL_RTC_ALMA_DATEWEEKDAYSEL_WEEKDAY
  * @param  Day Value between Min_Data=0x01 and Max_Data=0x31 if the week day is not selected
  *                   if week day is selected can be one of the following values:
  *         @arg @ref LL_RTC_WEEKDAY_MONDAY
  *         @arg @ref LL_RTC_WEEKDAY_TUESDAY
  *         @arg @ref LL_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref LL_RTC_WEEKDAY_THURSDAY
  *         @arg @ref LL_RTC_WEEKDAY_FRIDAY
  *         @arg @ref LL_RTC_WEEKDAY_SATURDAY
  *         @arg @ref LL_RTC_WEEKDAY_SUNDAY
  * @param  Format12_24 This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALMA_TIME_FORMAT_AM_24H
  *         @arg @ref LL_RTC_ALMA_TIME_FORMAT_PM
  * @param  Hours Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  * @param  Minutes Value between Min_Data=0x00 and Max_Data=0x59
  * @param  Seconds Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE void LL_RTC_ALM_SetConfigDateTime(uint32_t Alarm,
                                                  uint32_t Mask, uint32_t DayWeekDaySelection,
                                                  uint32_t Day, uint32_t Format12_24,
                                                  uint32_t Hours, uint32_t Minutes,
                                                  uint32_t Seconds)
{
  WRITE_REG(*(&(RTC->ALRMAR) + (RTC_ALRBR_ALRAR_OFFSET * Alarm)), (Seconds << RTC_ALRMAR_SU_Pos)
            | (Minutes << RTC_ALRMAR_MNU_Pos) | (Hours << RTC_ALRMAR_HU_Pos) | (Format12_24) | (DayWeekDaySelection)
            | (Day << RTC_ALRMAR_DU_Pos) | Mask);
}

/**
  * @brief  Get alarm A or B Time (hour, minute and second) in BCD format, time format,
  *         Day (Week day or day), Weekday or day selection and Masks
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  * @retval Content of the RTC_ALRMAR or RTC_ALRMBR register
  */
__STATIC_INLINE uint32_t LL_RTC_ALM_GetConfigDateTime(const uint32_t Alarm)
{
  return READ_REG(*(&(RTC->ALRMAR) + (RTC_ALRBR_ALRAR_OFFSET * Alarm)));
}

/**
  * @brief  Set alarm A or B sub seconds mask and value
  * @note   This register can be written only when ALRAE or ALRBE is reset in RTC_CR register,
  *         or in initialization mode
  * @rmtoll
  *  RTC_ALRMBSSR     MASKSS        LL_RTC_ALM_SetConfigSubSecond \n
  *  RTC_ALRMBSSR     SS            LL_RTC_ALM_SetConfigSubSecond \n
  *  RTC_ALRMASSR     MASKSS        LL_RTC_ALM_SetConfigSubSecond \n
  *  RTC_ALRMASSR     SS            LL_RTC_ALM_SetConfigSubSecond
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  * @param  Mask If binary mode is none, Value between Min_Data=0x0 and Max_Data=0xF
  *              else Value between Min_Data=0x0 and Max_Data=0x3F
  * @param  Subsecond Value between Min_Data=0x00 and Max_Data=0x7FFF
  */
__STATIC_INLINE void LL_RTC_ALM_SetConfigSubSecond(uint32_t Alarm,
                                                   uint32_t Mask,  uint32_t Subsecond)
{
  MODIFY_REG(*(&(RTC->ALRMASSR) + (RTC_ALRBSSR_ALRASSR_OFFSET * Alarm)),
             RTC_ALRMASSR_MASKSS | RTC_ALRMASSR_SS, (Mask << RTC_ALRMASSR_MASKSS_Pos)
             | Subsecond);
}

/**
  * @brief  Get alarm A or B sub seconds mask and value
  * @rmtoll
  *  RTC_ALRMASSR     MASKSS        LL_RTC_ALM_GetConfigSubSecond \n
  *  RTC_ALRMASSR     SS            LL_RTC_ALM_GetConfigSubSecond \n
  *  RTC_ALRMBSSR     MASKSS        LL_RTC_ALM_GetConfigSubSecond \n
  *  RTC_ALRMBSSR     SS            LL_RTC_ALM_GetConfigSubSecond
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  * @retval Mask If binary mode is none, Value between Min_Data=0x0 and Max_Data=0xF
  *              else Value between Min_Data=0x0 and Max_Data=0x3F
  *         Subsecond Value between Min_Data=0x00 and Max_Data=0x7FFF
  *         Result is given in the form 0x00MMSSSS
  */
__STATIC_INLINE uint32_t LL_RTC_ALM_GetConfigSubSecond(const uint32_t Alarm)
{
  uint32_t temp = READ_BIT(*(&(RTC->ALRMASSR) + (RTC_ALRBSSR_ALRASSR_OFFSET * Alarm)),
                           RTC_ALRMASSR_MASKSS | RTC_ALRMASSR_SS);

  return ((((temp & RTC_ALRMASSR_MASKSS) >> RTC_ALRMASSR_MASKSS_Pos) << RTC_OFFSET_ALR_MASK_SUBS_SECONDS) | \
          ((temp & RTC_ALRMASSR_SS) >> RTC_ALRMASSR_SS_Pos));
}

/**
  * @brief  Start alarm A or B
  * @rmtoll
  *  RTC_CR     ALRBIE        LL_RTC_ALM_Start \n
  *  RTC_CR     ALRBE         LL_RTC_ALM_Start \n
  *  RTC_CR     ALRAIE        LL_RTC_ALM_Start \n
  *  RTC_CR     ALRAE         LL_RTC_ALM_Start
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  * @param  Interruption This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALMA_IT_DISABLE
  *         @arg @ref LL_RTC_ALMA_IT_ENABLE
  */
__STATIC_INLINE void LL_RTC_ALM_Start(uint32_t Alarm, uint32_t Interruption)
{
  MODIFY_REG(RTC->CR, (RTC_CR_ALRAIE << Alarm) |
             (RTC_CR_ALRAE << Alarm),
             (RTC_CR_ALRAE << Alarm) |
             (Interruption << Alarm));
}

/**
  * @brief  Stop alarm A or B
  * @rmtoll
  *  RTC_CR     ALRBIE        LL_RTC_ALM_Stop \n
  *  RTC_CR     ALRBE         LL_RTC_ALM_Stop \n
  *  RTC_CR     ALRAIE        LL_RTC_ALM_Stop \n
  *  RTC_CR     ALRAE         LL_RTC_ALM_Stop
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  */
__STATIC_INLINE void LL_RTC_ALM_Stop(uint32_t Alarm)
{
  MODIFY_REG(RTC->CR, (RTC_CR_ALRAIE << Alarm) | (RTC_CR_ALRAE << Alarm), 0U);
}

/**
  * @brief  Is alarm A or B Enabled
  * @rmtoll
  *  RTC_CR     ALRBIE        LL_RTC_ALM_IsStarted \n
  *  RTC_CR     ALRBE         LL_RTC_ALM_IsStarted \n
  *  RTC_CR     ALRAIE        LL_RTC_ALM_IsStarted \n
  *  RTC_CR     ALRAIE        LL_RTC_ALM_IsStarted
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_ALM_IsStarted(const uint32_t Alarm)
{
  return (((READ_REG(RTC->CR) & (RTC_CR_ALRAE << Alarm)) == 0U) ? 0U : 1U);
}

/**
  * @brief  Set alarm A or B Sub seconds value
  * @rmtoll
  *  RCT_ALRABINR      SS            LL_RTC_ALM_SetBinarySubSecond \n
  *  RCT_ALRBBINR      SS            LL_RTC_ALM_SetBinarySubSecond
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  * @param  Subsecond If binary mode is none, Value between Min_Data=0x0 and Max_Data=0x7FFF
  *                   else Value between Min_Data=0x0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE void LL_RTC_ALM_SetBinarySubSecond(uint32_t Alarm, uint32_t Subsecond)
{
  WRITE_REG(*(&(RTC->ALRABINR) + (RTC_ALRBBINR_ALRABINR_OFFSET * Alarm)), Subsecond);
}

/**
  * @brief  Get alarm A or B Sub seconds value
  * @rmtoll
  *  RCT_ALRABINR      SS            LL_RTC_ALM_GetBinarySubSecond \n
  *  RCT_ALRBBINR      SS            LL_RTC_ALM_GetBinarySubSecond
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  * @retval If binary mode is none, Value between Min_Data=0x0 and Max_Data=0x7FFF
  *         else Value between Min_Data=0x0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_RTC_ALM_GetBinarySubSecond(const uint32_t Alarm)
{
  return (uint32_t)(READ_REG(*(&(RTC->ALRABINR) + (RTC_ALRBBINR_ALRABINR_OFFSET * Alarm))));
}

/**
  * @brief  Set alarm A or B Sub seconds mask
  * @note   This register can be written only when ALRAE or ALRBE is reset in RTC_CR register,
  *         or in initialization mode
  * @rmtoll
  *  RTC_ALRMASSR     MASKSS        LL_RTC_ALM_SetSubSecondMask \n
  *  RTC_ALRMBSSR     MASKSS        LL_RTC_ALM_SetSubSecondMask
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  * @param  Mask If binary mode is none, Value between Min_Data=0x0 and Max_Data=0xF
  *              else Value between Min_Data=0x0 and Max_Data=0x3F
  */
__STATIC_INLINE void LL_RTC_ALM_SetSubSecondMask(uint32_t Alarm, uint32_t Mask)
{
  MODIFY_REG(*(&(RTC->ALRMASSR) + (RTC_ALRBSSR_ALRASSR_OFFSET * Alarm)),
             RTC_ALRMASSR_MASKSS, (Mask << RTC_ALRMASSR_MASKSS_Pos));
}

/**
  * @brief  Get alarm A or B sub seconds mask
  * @rmtoll
  *  RTC_ALRMASSR     MASKSS        LL_RTC_ALM_GetSubSecondMask \n
  *  RTC_ALRMBSSR     MASKSS        LL_RTC_ALM_GetSubSecondMask
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  * @retval Mask If binary mode is none, Value between Min_Data=0x0 and Max_Data=0xF
  *              else Value between Min_Data=0x0 and Max_Data=0x3F
  */
__STATIC_INLINE uint32_t LL_RTC_ALM_GetSubSecondMask(const uint32_t Alarm)
{
  uint32_t temp = READ_BIT(*(&(RTC->ALRMASSR) + (RTC_ALRBSSR_ALRASSR_OFFSET * Alarm)),
                           RTC_ALRMASSR_MASKSS);

  return temp >> (RTC_ALRMASSR_MASKSS_Pos);
}

/**
  * @}
  */

/** @defgroup RTC_LL_EF_ALARMA ALARMA
  * @{
  */

/**
  * @brief  Enable alarm A
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           ALRAE         LL_RTC_ALMA_Enable
  */
__STATIC_INLINE void LL_RTC_ALMA_Enable(void)
{
  SET_BIT(RTC->CR, RTC_CR_ALRAE);
}

/**
  * @brief  Disable alarm A
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           ALRAE         LL_RTC_ALMA_Disable
  */
__STATIC_INLINE void LL_RTC_ALMA_Disable(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_ALRAE);
}

/**
  * @brief  Specify the alarm A masks
  * @rmtoll
  *  RTC_ALRMAR       MSK4          LL_RTC_ALMA_SetMask \n
  *  RTC_ALRMAR       MSK3          LL_RTC_ALMA_SetMask \n
  *  RTC_ALRMAR       MSK2          LL_RTC_ALMA_SetMask \n
  *  RTC_ALRMAR       MSK1          LL_RTC_ALMA_SetMask
  * @param  Mask This parameter can be a combination of the following values:
  *         @arg @ref LL_RTC_ALMA_MASK_NONE
  *         @arg @ref LL_RTC_ALMA_MASK_DATEWEEKDAY
  *         @arg @ref LL_RTC_ALMA_MASK_HOURS
  *         @arg @ref LL_RTC_ALMA_MASK_MINUTES
  *         @arg @ref LL_RTC_ALMA_MASK_SECONDS
  *         @arg @ref LL_RTC_ALMA_MASK_ALL
  */
__STATIC_INLINE void LL_RTC_ALMA_SetMask(uint32_t Mask)
{
  MODIFY_REG(RTC->ALRMAR, RTC_ALRMAR_MSK4 | RTC_ALRMAR_MSK3 | RTC_ALRMAR_MSK2 | RTC_ALRMAR_MSK1, Mask);
}

/**
  * @brief  Get the alarm A masks
  * @rmtoll
  *  RTC_ALRMAR       MSK4          LL_RTC_ALMA_GetMask \n
  *  RTC_ALRMAR       MSK3          LL_RTC_ALMA_GetMask \n
  *  RTC_ALRMAR       MSK2          LL_RTC_ALMA_GetMask \n
  *  RTC_ALRMAR       MSK1          LL_RTC_ALMA_GetMask
  * @retval Returned value can be can be a combination of the following values:
  *         @arg @ref LL_RTC_ALMA_MASK_NONE
  *         @arg @ref LL_RTC_ALMA_MASK_DATEWEEKDAY
  *         @arg @ref LL_RTC_ALMA_MASK_HOURS
  *         @arg @ref LL_RTC_ALMA_MASK_MINUTES
  *         @arg @ref LL_RTC_ALMA_MASK_SECONDS
  *         @arg @ref LL_RTC_ALMA_MASK_ALL
  */
__STATIC_INLINE uint32_t LL_RTC_ALMA_GetMask(void)
{
  return (uint32_t)(READ_BIT(RTC->ALRMAR, RTC_ALRMAR_MSK4 | RTC_ALRMAR_MSK3 | RTC_ALRMAR_MSK2 | RTC_ALRMAR_MSK1));
}

/**
  * @brief  Enable alarm A Week day selection (DU[3:0] represents the week day. DT[1:0] is do not care)
  * @rmtoll
  *  RTC_ALRMAR       WDSEL         LL_RTC_ALMA_EnableWeekday
  */
__STATIC_INLINE void LL_RTC_ALMA_EnableWeekday(void)
{
  SET_BIT(RTC->ALRMAR, RTC_ALRMAR_WDSEL);
}

/**
  * @brief  Disable alarm A Week day selection (DU[3:0] represents the date )
  * @rmtoll
  *  RTC_ALRMAR       WDSEL         LL_RTC_ALMA_DisableWeekday
  */
__STATIC_INLINE void LL_RTC_ALMA_DisableWeekday(void)
{
  CLEAR_BIT(RTC->ALRMAR, RTC_ALRMAR_WDSEL);
}

/**
  * @brief  Check if alarm A Week day selection is enabled or not
  * @rmtoll
  *  RTC_ALRMAR       WDSEL         LL_RTC_ALMA_IsEnabledWeekday
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_ALMA_IsEnabledWeekday(void)
{
  return ((READ_BIT(RTC->ALRMAR, RTC_ALRMAR_WDSEL) == (RTC_ALRMAR_WDSEL)) ? 1U : 0U);
}

/**
  * @brief  Set alarm A Day in BCD format
  * @note   helper macro LL_RTC_CONVERT_BIN2BCD is available to convert Day from binary to BCD format
  * @rmtoll
  *  RTC_ALRMAR       DT            LL_RTC_ALMA_SetDay \n
  *  RTC_ALRMAR       DU            LL_RTC_ALMA_SetDay
  * @param  Day Value between Min_Data=0x01 and Max_Data=0x31
  */
__STATIC_INLINE void LL_RTC_ALMA_SetDay(uint32_t Day)
{
  MODIFY_REG(RTC->ALRMAR, (RTC_ALRMAR_DT | RTC_ALRMAR_DU),
             (((Day & 0xF0U) << (RTC_ALRMAR_DT_Pos - 4U)) | ((Day & 0x0FU) << RTC_ALRMAR_DU_Pos)));
}

/**
  * @brief  Get alarm A Day in BCD format
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Day from BCD to Binary format
  * @rmtoll
  *  RTC_ALRMAR       DT            LL_RTC_ALMA_GetDay \n
  *  RTC_ALRMAR       DU            LL_RTC_ALMA_GetDay
  * @retval Value between Min_Data=0x01 and Max_Data=0x31
  */
__STATIC_INLINE uint32_t LL_RTC_ALMA_GetDay(void)
{
  return (uint32_t)((READ_BIT(RTC->ALRMAR, (RTC_ALRMAR_DT | RTC_ALRMAR_DU))) >> RTC_ALRMAR_DU_Pos);
}

/**
  * @brief  Set alarm A Weekday
  * @rmtoll
  *  RTC_ALRMAR       DU            LL_RTC_ALMA_SetWeekDay
  * @note   DU in week day mode only if WDSEL is enabled
  * @param  WeekDay This parameter can be one of the following values:
  *         @arg @ref LL_RTC_WEEKDAY_MONDAY
  *         @arg @ref LL_RTC_WEEKDAY_TUESDAY
  *         @arg @ref LL_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref LL_RTC_WEEKDAY_THURSDAY
  *         @arg @ref LL_RTC_WEEKDAY_FRIDAY
  *         @arg @ref LL_RTC_WEEKDAY_SATURDAY
  *         @arg @ref LL_RTC_WEEKDAY_SUNDAY
  */
__STATIC_INLINE void LL_RTC_ALMA_SetWeekDay(uint32_t WeekDay)
{
  MODIFY_REG(RTC->ALRMAR, RTC_ALRMAR_DU, WeekDay << RTC_ALRMAR_DU_Pos);
}

/**
  * @brief  Get alarm A Weekday
  * @rmtoll
  *  RTC_ALRMAR       DU            LL_RTC_ALMA_GetWeekDay
  * @note   DU in week day mode only if WDSEL is enabled
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_WEEKDAY_MONDAY
  *         @arg @ref LL_RTC_WEEKDAY_TUESDAY
  *         @arg @ref LL_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref LL_RTC_WEEKDAY_THURSDAY
  *         @arg @ref LL_RTC_WEEKDAY_FRIDAY
  *         @arg @ref LL_RTC_WEEKDAY_SATURDAY
  *         @arg @ref LL_RTC_WEEKDAY_SUNDAY
  */
__STATIC_INLINE uint32_t LL_RTC_ALMA_GetWeekDay(void)
{
  return (uint32_t)(READ_BIT(RTC->ALRMAR, RTC_ALRMAR_DU) >> RTC_ALRMAR_DU_Pos);
}

/**
  * @brief  Set alarm A time format (AM/24-hour or PM notation)
  * @rmtoll
  *  RTC_ALRMAR       PM            LL_RTC_ALMA_SetTimeFormat
  * @param  TimeFormat This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALMA_TIME_FORMAT_AM_24H
  *         @arg @ref LL_RTC_ALMA_TIME_FORMAT_PM
  */
__STATIC_INLINE void LL_RTC_ALMA_SetTimeFormat(uint32_t TimeFormat)
{
  MODIFY_REG(RTC->ALRMAR, RTC_ALRMAR_PM, TimeFormat);
}

/**
  * @brief  Get alarm A time format (AM or PM notation)
  * @rmtoll
  *  RTC_ALRMAR       PM            LL_RTC_ALMA_GetTimeFormat
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_ALMA_TIME_FORMAT_AM_24H
  *         @arg @ref LL_RTC_ALMA_TIME_FORMAT_PM
  */
__STATIC_INLINE uint32_t LL_RTC_ALMA_GetTimeFormat(void)
{
  return (uint32_t)(READ_BIT(RTC->ALRMAR, RTC_ALRMAR_PM));
}

/**
  * @brief  Set alarm A Hours in BCD format
  * @note   helper macro LL_RTC_CONVERT_BIN2BCD is available to convert Hours from binary to BCD format
  * @rmtoll
  *  RTC_ALRMAR       HT            LL_RTC_ALMA_SetHour \n
  *  RTC_ALRMAR       HU            LL_RTC_ALMA_SetHour
  * @param  Hours Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  */
__STATIC_INLINE void LL_RTC_ALMA_SetHour(uint32_t Hours)
{
  MODIFY_REG(RTC->ALRMAR, (RTC_ALRMAR_HT | RTC_ALRMAR_HU),
             (((Hours & 0xF0U) << (RTC_ALRMAR_HT_Pos - 4U)) | ((Hours & 0x0FU) << RTC_ALRMAR_HU_Pos)));
}

/**
  * @brief  Get alarm A Hours in BCD format
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Hours from BCD to Binary format
  * @rmtoll
  *  RTC_ALRMAR       HT            LL_RTC_ALMA_GetHour \n
  *  RTC_ALRMAR       HU            LL_RTC_ALMA_GetHour
  * @retval Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  */
__STATIC_INLINE uint32_t LL_RTC_ALMA_GetHour(void)
{
  return (uint32_t)((READ_BIT(RTC->ALRMAR, (RTC_ALRMAR_HT | RTC_ALRMAR_HU))) >> RTC_ALRMAR_HU_Pos);
}

/**
  * @brief  Set alarm A Minutes in BCD format
  * @note   helper macro LL_RTC_CONVERT_BIN2BCD is available to convert Minutes from binary to BCD format
  * @rmtoll
  *  RTC_ALRMAR       MNT           LL_RTC_ALMA_SetMinute \n
  *  RTC_ALRMAR       MNU           LL_RTC_ALMA_SetMinute
  * @param  Minutes Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE void LL_RTC_ALMA_SetMinute(uint32_t Minutes)
{
  MODIFY_REG(RTC->ALRMAR, (RTC_ALRMAR_MNT | RTC_ALRMAR_MNU),
             (((Minutes & 0xF0U) << (RTC_ALRMAR_MNT_Pos - 4U)) | ((Minutes & 0x0FU) << RTC_ALRMAR_MNU_Pos)));
}

/**
  * @brief  Get alarm A Minutes in BCD format
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Minutes from BCD to Binary format
  * @rmtoll
  *  RTC_ALRMAR       MNT           LL_RTC_ALMA_GetMinute \n
  *  RTC_ALRMAR       MNU           LL_RTC_ALMA_GetMinute
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t LL_RTC_ALMA_GetMinute(void)
{
  return (uint32_t)((READ_BIT(RTC->ALRMAR, (RTC_ALRMAR_MNT | RTC_ALRMAR_MNU))) >> RTC_ALRMAR_MNU_Pos);
}

/**
  * @brief  Set alarm A Seconds in BCD format
  * @note   helper macro LL_RTC_CONVERT_BIN2BCD is available to convert Seconds from binary to BCD format
  * @rmtoll
  *  RTC_ALRMAR       ST            LL_RTC_ALMA_SetSecond \n
  *  RTC_ALRMAR       SU            LL_RTC_ALMA_SetSecond
  * @param  Seconds Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE void LL_RTC_ALMA_SetSecond(uint32_t Seconds)
{
  MODIFY_REG(RTC->ALRMAR, (RTC_ALRMAR_ST | RTC_ALRMAR_SU),
             (((Seconds & 0xF0U) << (RTC_ALRMAR_ST_Pos - 4U)) | ((Seconds & 0x0FU) << RTC_ALRMAR_SU_Pos)));
}

/**
  * @brief  Get alarm A Seconds in BCD format
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Seconds from BCD to Binary format
  * @rmtoll
  *  RTC_ALRMAR       ST            LL_RTC_ALMA_GetSecond \n
  *  RTC_ALRMAR       SU            LL_RTC_ALMA_GetSecond
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t LL_RTC_ALMA_GetSecond(void)
{
  return (uint32_t)((READ_BIT(RTC->ALRMAR, (RTC_ALRMAR_ST | RTC_ALRMAR_SU))) >> RTC_ALRMAR_SU_Pos);
}

/**
  * @brief  Set alarm A Time (hour, minute and second) in BCD format
  * @rmtoll
  *  RTC_ALRMAR       PM            LL_RTC_ALMA_ConfigTime \n
  *  RTC_ALRMAR       HT            LL_RTC_ALMA_ConfigTime \n
  *  RTC_ALRMAR       HU            LL_RTC_ALMA_ConfigTime \n
  *  RTC_ALRMAR       MNT           LL_RTC_ALMA_ConfigTime \n
  *  RTC_ALRMAR       MNU           LL_RTC_ALMA_ConfigTime \n
  *  RTC_ALRMAR       ST            LL_RTC_ALMA_ConfigTime \n
  *  RTC_ALRMAR       SU            LL_RTC_ALMA_ConfigTime
  * @param  Format12_24 This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALMA_TIME_FORMAT_AM_24H
  *         @arg @ref LL_RTC_ALMA_TIME_FORMAT_PM
  * @param  Hours Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  * @param  Minutes Value between Min_Data=0x00 and Max_Data=0x59
  * @param  Seconds Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE void LL_RTC_ALMA_ConfigTime(uint32_t Format12_24, uint32_t Hours, uint32_t Minutes,
                                            uint32_t Seconds)
{
  uint32_t temp;

  temp = Format12_24 | (((Hours & 0xF0U) << (RTC_ALRMAR_HT_Pos - 4U)) | ((Hours & 0x0FU) << RTC_ALRMAR_HU_Pos))    | \
         (((Minutes & 0xF0U) << (RTC_ALRMAR_MNT_Pos - 4U)) | ((Minutes & 0x0FU) << RTC_ALRMAR_MNU_Pos)) | \
         (((Seconds & 0xF0U) << (RTC_ALRMAR_ST_Pos - 4U)) | ((Seconds & 0x0FU) << RTC_ALRMAR_SU_Pos));

  MODIFY_REG(RTC->ALRMAR, RTC_ALRMAR_PM | RTC_ALRMAR_HT | RTC_ALRMAR_HU | RTC_ALRMAR_MNT | RTC_ALRMAR_MNU | \
             RTC_ALRMAR_ST | RTC_ALRMAR_SU, temp);
}

/**
  * @brief  Get alarm A Time (hour, minute and second) in BCD format
  * @note   helper macros LL_RTC_GET_HOUR, LL_RTC_GET_MINUTE and LL_RTC_GET_SECOND
  *         are available to get independently each parameter
  * @rmtoll
  *  RTC_ALRMAR       HT            LL_RTC_ALMA_GetTime \n
  *  RTC_ALRMAR       HU            LL_RTC_ALMA_GetTime \n
  *  RTC_ALRMAR       MNT           LL_RTC_ALMA_GetTime \n
  *  RTC_ALRMAR       MNU           LL_RTC_ALMA_GetTime \n
  *  RTC_ALRMAR       ST            LL_RTC_ALMA_GetTime \n
  *  RTC_ALRMAR       SU            LL_RTC_ALMA_GetTime
  * @retval Combination of hours, minutes and seconds
  */
__STATIC_INLINE uint32_t LL_RTC_ALMA_GetTime(void)
{
  return (uint32_t)((LL_RTC_ALMA_GetHour() << RTC_OFFSET_HOUR) | (LL_RTC_ALMA_GetMinute() << \
                                                                  RTC_OFFSET_MINUTE) | LL_RTC_ALMA_GetSecond());
}

/**
  * @brief  Set alarm A Mask the most-significant bits starting at this bit
  * @note   This register can be written only when ALRAE is reset in RTC_CR register,
  *         or in initialization mode
  * @rmtoll
  *  RTC_ALRMASSR     MASKSS        LL_RTC_ALMA_SetSubSecondMask
  * @param  Mask If binary mode is none, Value between Min_Data=0x0 and Max_Data=0xF
  *              else Value between Min_Data=0x0 and Max_Data=0x3F
  */
__STATIC_INLINE void LL_RTC_ALMA_SetSubSecondMask(uint32_t Mask)
{
  MODIFY_REG(RTC->ALRMASSR, RTC_ALRMASSR_MASKSS, Mask << RTC_ALRMASSR_MASKSS_Pos);
}

/**
  * @brief  Get alarm A Mask the most-significant bits starting at this bit
  * @rmtoll
  *  RTC_ALRMASSR     MASKSS        LL_RTC_ALMA_GetSubSecondMask
  * @retval If binary mode is none, Value between Min_Data=0x0 and Max_Data=0xF
  *         else Value between Min_Data=0x0 and Max_Data=0x3F
  */
__STATIC_INLINE uint32_t LL_RTC_ALMA_GetSubSecondMask(void)
{
  return (uint32_t)(READ_BIT(RTC->ALRMASSR, RTC_ALRMASSR_MASKSS) >> RTC_ALRMASSR_MASKSS_Pos);
}

/**
  * @brief  Set alarm A Binary mode auto clear
  * @note   This register can be written only when ALRAE is reset in RTC_CR register,
  *         or in initialization mode
  * @note   SSCLR must be kept to 0 when BCD or mixed mode is used (BIN = 00, 10 or 11).
  * @rmtoll
  *  RTC_ALRMASSR    SSCLR        LL_RTC_ALMA_SetBinAutoClr
  * @param  BinaryAutoClr This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALMA_SUBSECONDBIN_AUTOCLR_NO
  *         @arg @ref LL_RTC_ALMA_SUBSECONDBIN_AUTOCLR_YES
  */
__STATIC_INLINE void LL_RTC_ALMA_SetBinAutoClr(uint32_t BinaryAutoClr)
{
  MODIFY_REG(RTC->ALRMASSR, RTC_ALRMASSR_SSCLR, BinaryAutoClr);
}

/**
  * @brief  Get alarm A Binary mode auto clear
  * @rmtoll
  *  RTC_ALRMASSR     SSCLR        LL_RTC_ALMA_GetBinAutoClr
  * @retval It can be one of the following values:
  *         @arg @ref LL_RTC_ALMA_SUBSECONDBIN_AUTOCLR_NO
  *         @arg @ref LL_RTC_ALMA_SUBSECONDBIN_AUTOCLR_YES
  */
__STATIC_INLINE uint32_t LL_RTC_ALMA_GetBinAutoClr(void)
{
  return (uint32_t)(READ_BIT(RTC->ALRMASSR, RTC_ALRMASSR_SSCLR));
}

/**
  * @brief  Set alarm A Sub seconds value
  * @rmtoll
  *  RCT_ALRMASSR     SS            LL_RTC_ALMA_SetSubSecond
  * @param  Subsecond If binary mode is none, Value between Min_Data=0x0 and Max_Data=0x7FFF
  *                   else Value between Min_Data=0x0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE void LL_RTC_ALMA_SetSubSecond(uint32_t Subsecond)
{
  MODIFY_REG(RTC->ALRMASSR, RTC_ALRMASSR_SS, Subsecond);
}

/**
  * @brief  Get alarm A Sub seconds value
  * @rmtoll
  *  RCT_ALRMASSR     SS            LL_RTC_ALMA_GetSubSecond
  * @retval If binary mode is none, Value between Min_Data=0x0 and Max_Data=0x7FFF
  *         else Value between Min_Data=0x0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_RTC_ALMA_GetSubSecond(void)
{
  return (uint32_t)(READ_BIT(RTC->ALRMASSR, RTC_ALRMASSR_SS));
}

/**
  * @}
  */

/** @defgroup RTC_LL_EF_ALARMB ALARMB
  * @{
  */

/**
  * @brief  Enable alarm B
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           ALRBE         LL_RTC_ALMB_Enable
  */
__STATIC_INLINE void LL_RTC_ALMB_Enable(void)
{
  SET_BIT(RTC->CR, RTC_CR_ALRBE);
}

/**
  * @brief  Disable alarm B
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           ALRBE         LL_RTC_ALMB_Disable
  */
__STATIC_INLINE void LL_RTC_ALMB_Disable(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_ALRBE);
}

/**
  * @brief  Specify the alarm B masks
  * @rmtoll
  *  RTC_ALRMBR       MSK4          LL_RTC_ALMB_SetMask \n
  *  RTC_ALRMBR       MSK3          LL_RTC_ALMB_SetMask \n
  *  RTC_ALRMBR       MSK2          LL_RTC_ALMB_SetMask \n
  *  RTC_ALRMBR       MSK1          LL_RTC_ALMB_SetMask
  * @param  Mask This parameter can be a combination of the following values:
  *         @arg @ref LL_RTC_ALMB_MASK_NONE
  *         @arg @ref LL_RTC_ALMB_MASK_DATEWEEKDAY
  *         @arg @ref LL_RTC_ALMB_MASK_HOURS
  *         @arg @ref LL_RTC_ALMB_MASK_MINUTES
  *         @arg @ref LL_RTC_ALMB_MASK_SECONDS
  *         @arg @ref LL_RTC_ALMB_MASK_ALL
  */
__STATIC_INLINE void LL_RTC_ALMB_SetMask(uint32_t Mask)
{
  MODIFY_REG(RTC->ALRMBR, RTC_ALRMBR_MSK4 | RTC_ALRMBR_MSK3 | RTC_ALRMBR_MSK2 | RTC_ALRMBR_MSK1, Mask);
}

/**
  * @brief  Get the alarm B masks
  * @rmtoll
  *  RTC_ALRMBR       MSK4          LL_RTC_ALMB_GetMask \n
  *  RTC_ALRMBR       MSK3          LL_RTC_ALMB_GetMask \n
  *  RTC_ALRMBR       MSK2          LL_RTC_ALMB_GetMask \n
  *  RTC_ALRMBR       MSK1          LL_RTC_ALMB_GetMask
  * @retval Returned value can be can be a combination of the following values:
  *         @arg @ref LL_RTC_ALMB_MASK_NONE
  *         @arg @ref LL_RTC_ALMB_MASK_DATEWEEKDAY
  *         @arg @ref LL_RTC_ALMB_MASK_HOURS
  *         @arg @ref LL_RTC_ALMB_MASK_MINUTES
  *         @arg @ref LL_RTC_ALMB_MASK_SECONDS
  *         @arg @ref LL_RTC_ALMB_MASK_ALL
  */
__STATIC_INLINE uint32_t LL_RTC_ALMB_GetMask(void)
{
  return (uint32_t)(READ_BIT(RTC->ALRMBR, RTC_ALRMBR_MSK4 | RTC_ALRMBR_MSK3 | RTC_ALRMBR_MSK2 | RTC_ALRMBR_MSK1));
}

/**
  * @brief  Enable alarm B Week day selection (DU[3:0] represents the week day. DT[1:0] is do not care)
  * @rmtoll
  *  RTC_ALRMBR       WDSEL         LL_RTC_ALMB_EnableWeekday
  */
__STATIC_INLINE void LL_RTC_ALMB_EnableWeekday(void)
{
  SET_BIT(RTC->ALRMBR, RTC_ALRMBR_WDSEL);
}

/**
  * @brief  Disable alarm B Week day selection (DU[3:0] represents the date )
  * @rmtoll
  *  RTC_ALRMBR       WDSEL         LL_RTC_ALMB_DisableWeekday
  */
__STATIC_INLINE void LL_RTC_ALMB_DisableWeekday(void)
{
  CLEAR_BIT(RTC->ALRMBR, RTC_ALRMBR_WDSEL);
}

/**
  * @brief  Check if alarm B Week day selection is enabled or not
  * @rmtoll
  *  RTC_ALRMBR       WDSEL         LL_RTC_ALMB_IsEnabledWeekday
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_ALMB_IsEnabledWeekday(void)
{
  return ((READ_BIT(RTC->ALRMBR, RTC_ALRMBR_WDSEL) == (RTC_ALRMBR_WDSEL)) ? 1U : 0U);
}


/**
  * @brief  Set alarm B Day in BCD format
  * @note   helper macro LL_RTC_CONVERT_BIN2BCD is available to convert Day from binary to BCD format
  * @rmtoll
  *  RTC_ALRMBR       DT            LL_RTC_ALMB_SetDay \n
  *  RTC_ALRMBR       DU            LL_RTC_ALMB_SetDay
  * @param  Day Value between Min_Data=0x01 and Max_Data=0x31
  */
__STATIC_INLINE void LL_RTC_ALMB_SetDay(uint32_t Day)
{
  MODIFY_REG(RTC->ALRMBR, (RTC_ALRMBR_DT | RTC_ALRMBR_DU),
             (((Day & 0xF0U) << (RTC_ALRMBR_DT_Pos - 4U)) | ((Day & 0x0FU) << RTC_ALRMBR_DU_Pos)));
}

/**
  * @brief  Get alarm B Day in BCD format
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Day from BCD to Binary format
  * @rmtoll
  *  RTC_ALRMBR       DT            LL_RTC_ALMB_GetDay \n
  *  RTC_ALRMBR       DU            LL_RTC_ALMB_GetDay
  * @retval Value between Min_Data=0x01 and Max_Data=0x31
  */
__STATIC_INLINE uint32_t LL_RTC_ALMB_GetDay(void)
{
  return (uint32_t)((READ_BIT(RTC->ALRMBR, (RTC_ALRMBR_DT | RTC_ALRMBR_DU))) >> RTC_ALRMBR_DU_Pos);
}

/**
  * @brief  Set alarm B Weekday
  * @rmtoll
  *  RTC_ALRMBR       DU            LL_RTC_ALMB_SetWeekDay
  * @param  WeekDay This parameter can be one of the following values:
  *         @arg @ref LL_RTC_WEEKDAY_MONDAY
  *         @arg @ref LL_RTC_WEEKDAY_TUESDAY
  *         @arg @ref LL_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref LL_RTC_WEEKDAY_THURSDAY
  *         @arg @ref LL_RTC_WEEKDAY_FRIDAY
  *         @arg @ref LL_RTC_WEEKDAY_SATURDAY
  *         @arg @ref LL_RTC_WEEKDAY_SUNDAY
  */
__STATIC_INLINE void LL_RTC_ALMB_SetWeekDay(uint32_t WeekDay)
{
  MODIFY_REG(RTC->ALRMBR, RTC_ALRMBR_DU, WeekDay << RTC_ALRMBR_DU_Pos);
}

/**
  * @brief  Get alarm B Weekday
  * @rmtoll
  *  RTC_ALRMBR       DU            LL_RTC_ALMB_GetWeekDay
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_WEEKDAY_MONDAY
  *         @arg @ref LL_RTC_WEEKDAY_TUESDAY
  *         @arg @ref LL_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref LL_RTC_WEEKDAY_THURSDAY
  *         @arg @ref LL_RTC_WEEKDAY_FRIDAY
  *         @arg @ref LL_RTC_WEEKDAY_SATURDAY
  *         @arg @ref LL_RTC_WEEKDAY_SUNDAY
  */
__STATIC_INLINE uint32_t LL_RTC_ALMB_GetWeekDay(void)
{
  return (uint32_t)(READ_BIT(RTC->ALRMBR, RTC_ALRMBR_DU) >> RTC_ALRMBR_DU_Pos);
}

/**
  * @brief  Set alarm B time format (AM/24-hour or PM notation)
  * @rmtoll
  *  RTC_ALRMBR       PM            LL_RTC_ALMB_SetTimeFormat
  * @param  TimeFormat This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALMB_TIME_FORMAT_AM_24H
  *         @arg @ref LL_RTC_ALMB_TIME_FORMAT_PM
  */
__STATIC_INLINE void LL_RTC_ALMB_SetTimeFormat(uint32_t TimeFormat)
{
  MODIFY_REG(RTC->ALRMBR, RTC_ALRMBR_PM, TimeFormat);
}

/**
  * @brief  Get alarm B time format (AM/24-hour or PM notation)
  * @rmtoll
  *  RTC_ALRMBR       PM            LL_RTC_ALMB_GetTimeFormat
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_ALMB_TIME_FORMAT_AM_24H
  *         @arg @ref LL_RTC_ALMB_TIME_FORMAT_PM
  */
__STATIC_INLINE uint32_t LL_RTC_ALMB_GetTimeFormat(void)
{
  return (uint32_t)(READ_BIT(RTC->ALRMBR, RTC_ALRMBR_PM));
}

/**
  * @brief  Set alarm B Hours in BCD format
  * @note   helper macro LL_RTC_CONVERT_BIN2BCD is available to convert Hours from binary to BCD format
  * @rmtoll
  *  RTC_ALRMBR       HT            LL_RTC_ALMB_SetHour \n
  *  RTC_ALRMBR       HU            LL_RTC_ALMB_SetHour
  * @param  Hours Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  */
__STATIC_INLINE void LL_RTC_ALMB_SetHour(uint32_t Hours)
{
  MODIFY_REG(RTC->ALRMBR, (RTC_ALRMBR_HT | RTC_ALRMBR_HU),
             (((Hours & 0xF0U) << (RTC_ALRMBR_HT_Pos - 4U)) | ((Hours & 0x0FU) << RTC_ALRMBR_HU_Pos)));
}

/**
  * @brief  Get alarm B Hours in BCD format
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Hours from BCD to Binary format
  * @rmtoll
  *  RTC_ALRMBR       HT            LL_RTC_ALMB_GetHour \n
  *  RTC_ALRMBR       HU            LL_RTC_ALMB_GetHour
  * @retval Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  */
__STATIC_INLINE uint32_t LL_RTC_ALMB_GetHour(void)
{
  return (uint32_t)((READ_BIT(RTC->ALRMBR, (RTC_ALRMBR_HT | RTC_ALRMBR_HU))) >> RTC_ALRMBR_HU_Pos);
}

/**
  * @brief  Set alarm B Minutes in BCD format
  * @note   helper macro LL_RTC_CONVERT_BIN2BCD is available to convert Minutes from binary to BCD format
  * @rmtoll
  *  RTC_ALRMBR       MNT           LL_RTC_ALMB_SetMinute \n
  *  RTC_ALRMBR       MNU           LL_RTC_ALMB_SetMinute
  * @param  Minutes between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE void LL_RTC_ALMB_SetMinute(uint32_t Minutes)
{
  MODIFY_REG(RTC->ALRMBR, (RTC_ALRMBR_MNT | RTC_ALRMBR_MNU),
             (((Minutes & 0xF0U) << (RTC_ALRMBR_MNT_Pos - 4U)) | ((Minutes & 0x0FU) << RTC_ALRMBR_MNU_Pos)));
}

/**
  * @brief  Get alarm B Minutes in BCD format
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Minutes from BCD to Binary format
  * @rmtoll
  *  RTC_ALRMBR       MNT           LL_RTC_ALMB_GetMinute \n
  *  RTC_ALRMBR       MNU           LL_RTC_ALMB_GetMinute
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t LL_RTC_ALMB_GetMinute(void)
{
  return (uint32_t)((READ_BIT(RTC->ALRMBR, (RTC_ALRMBR_MNT | RTC_ALRMBR_MNU))) >> RTC_ALRMBR_MNU_Pos);
}

/**
  * @brief  Set alarm B Seconds in BCD format
  * @note   helper macro LL_RTC_CONVERT_BIN2BCD is available to convert Seconds from binary to BCD format
  * @rmtoll
  *  RTC_ALRMBR       ST            LL_RTC_ALMB_SetSecond \n
  *  RTC_ALRMBR       SU            LL_RTC_ALMB_SetSecond
  * @param  Seconds Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE void LL_RTC_ALMB_SetSecond(uint32_t Seconds)
{
  MODIFY_REG(RTC->ALRMBR, (RTC_ALRMBR_ST | RTC_ALRMBR_SU),
             (((Seconds & 0xF0U) << (RTC_ALRMBR_ST_Pos - 4U)) | ((Seconds & 0x0FU) << RTC_ALRMBR_SU_Pos)));
}

/**
  * @brief  Get alarm B Seconds in BCD format
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Seconds from BCD to Binary format
  * @rmtoll
  *  RTC_ALRMBR       ST            LL_RTC_ALMB_GetSecond \n
  *  RTC_ALRMBR       SU            LL_RTC_ALMB_GetSecond
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t LL_RTC_ALMB_GetSecond(void)
{
  return (uint32_t)((READ_BIT(RTC->ALRMBR, (RTC_ALRMBR_ST | RTC_ALRMBR_SU))) >> RTC_ALRMBR_SU_Pos);
}

/**
  * @brief  Set alarm B Time (hour, minute and second) in BCD format
  * @rmtoll
  *  RTC_ALRMBR       PM            LL_RTC_ALMB_ConfigTime \n
  *  RTC_ALRMBR       HT            LL_RTC_ALMB_ConfigTime \n
  *  RTC_ALRMBR       HU            LL_RTC_ALMB_ConfigTime \n
  *  RTC_ALRMBR       MNT           LL_RTC_ALMB_ConfigTime \n
  *  RTC_ALRMBR       MNU           LL_RTC_ALMB_ConfigTime \n
  *  RTC_ALRMBR       ST            LL_RTC_ALMB_ConfigTime \n
  *  RTC_ALRMBR       SU            LL_RTC_ALMB_ConfigTime
  * @param  Format12_24 This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALMB_TIME_FORMAT_AM_24H
  *         @arg @ref LL_RTC_ALMB_TIME_FORMAT_PM
  * @param  Hours Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  * @param  Minutes Value between Min_Data=0x00 and Max_Data=0x59
  * @param  Seconds Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE void LL_RTC_ALMB_ConfigTime(uint32_t Format12_24, uint32_t Hours, uint32_t Minutes,
                                            uint32_t Seconds)
{
  uint32_t temp;

  temp = Format12_24 | (((Hours & 0xF0U) << (RTC_ALRMBR_HT_Pos - 4U)) | ((Hours & 0x0FU) << RTC_ALRMBR_HU_Pos))    | \
         (((Minutes & 0xF0U) << (RTC_ALRMBR_MNT_Pos - 4U)) | ((Minutes & 0x0FU) << RTC_ALRMBR_MNU_Pos)) | \
         (((Seconds & 0xF0U) << (RTC_ALRMBR_ST_Pos - 4U)) | ((Seconds & 0x0FU) << RTC_ALRMBR_SU_Pos));

  MODIFY_REG(RTC->ALRMBR, RTC_ALRMBR_PM | RTC_ALRMBR_HT | RTC_ALRMBR_HU | RTC_ALRMBR_MNT | RTC_ALRMBR_MNU | \
             RTC_ALRMBR_ST | RTC_ALRMBR_SU, temp);
}

/**
  * @brief  Get alarm B Time (hour, minute and second) in BCD format
  * @note   helper macros LL_RTC_GET_HOUR, LL_RTC_GET_MINUTE and LL_RTC_GET_SECOND
  *         are available to get independently each parameter
  * @rmtoll
  *  RTC_ALRMBR       HT            LL_RTC_ALMB_GetTime \n
  *  RTC_ALRMBR       HU            LL_RTC_ALMB_GetTime \n
  *  RTC_ALRMBR       MNT           LL_RTC_ALMB_GetTime \n
  *  RTC_ALRMBR       MNU           LL_RTC_ALMB_GetTime \n
  *  RTC_ALRMBR       ST            LL_RTC_ALMB_GetTime \n
  *  RTC_ALRMBR       SU            LL_RTC_ALMB_GetTime
  * @retval Combination of hours, minutes and seconds
  */
__STATIC_INLINE uint32_t LL_RTC_ALMB_GetTime(void)
{
  return (uint32_t)((LL_RTC_ALMB_GetHour() << RTC_OFFSET_HOUR) | (LL_RTC_ALMB_GetMinute() << \
                                                                  RTC_OFFSET_MINUTE) | LL_RTC_ALMB_GetSecond());
}

/**
  * @brief  Set alarm B Mask the most-significant bits starting at this bit
  * @note   This register can be written only when ALRBE is reset in RTC_CR register,
  *         or in initialization mode
  * @rmtoll
  *  RTC_ALRMBSSR     MASKSS        LL_RTC_ALMB_SetSubSecondMask
  * @param  Mask If binary mode is none, Value between Min_Data=0x0 and Max_Data=0xF
  *              else Value between Min_Data=0x0 and Max_Data=0x3F
  */
__STATIC_INLINE void LL_RTC_ALMB_SetSubSecondMask(uint32_t Mask)
{
  MODIFY_REG(RTC->ALRMBSSR, RTC_ALRMBSSR_MASKSS, Mask << RTC_ALRMBSSR_MASKSS_Pos);
}

/**
  * @brief  Get alarm B Mask the most-significant bits starting at this bit
  * @rmtoll
  *  RTC_ALRMBSSR     MASKSS        LL_RTC_ALMB_GetSubSecondMask
  * @retval If binary mode is none, Value between Min_Data=0x0 and Max_Data=0xF
  *         else Value between Min_Data=0x0 and Max_Data=0x3F
  */
__STATIC_INLINE uint32_t LL_RTC_ALMB_GetSubSecondMask(void)
{
  return (uint32_t)(READ_BIT(RTC->ALRMBSSR, RTC_ALRMBSSR_MASKSS) >> RTC_ALRMBSSR_MASKSS_Pos);
}

/**
  * @brief  Set alarm B Binary mode auto clear
  * @note   This register can be written only when ALRBE is reset in RTC_CR register,
  *         or in initialization mode
  * @note   SSCLR must be kept to 0 when BCD or mixed mode is used (BIN = 00, 10 or 11).
  * @rmtoll
  *  RTC_ALRMBSSR     SSCLR        LL_RTC_ALMB_SetBinAutoClr
  * @param  BinaryAutoClr This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALMB_SUBSECONDBIN_AUTOCLR_NO
  *         @arg @ref LL_RTC_ALMB_SUBSECONDBIN_AUTOCLR_YES
  */
__STATIC_INLINE void LL_RTC_ALMB_SetBinAutoClr(uint32_t BinaryAutoClr)
{
  MODIFY_REG(RTC->ALRMBSSR, RTC_ALRMBSSR_SSCLR, BinaryAutoClr);
}

/**
  * @brief  Get alarm B Binary mode auto clear
  * @rmtoll
  *  RTC_ALRMBSSR     SSCLR        LL_RTC_ALMB_GetBinAutoClr
  * @retval It can be one of the following values:
  *         @arg @ref LL_RTC_ALMB_SUBSECONDBIN_AUTOCLR_NO
  *         @arg @ref LL_RTC_ALMB_SUBSECONDBIN_AUTOCLR_YES
  */
__STATIC_INLINE uint32_t LL_RTC_ALMB_GetBinAutoClr(void)
{
  return (uint32_t)(READ_BIT(RTC->ALRMBSSR, RTC_ALRMBSSR_SSCLR));
}

/**
  * @brief  Set alarm B Sub seconds value
  * @rmtoll
  *  RTC_ALRMBSSR     SS            LL_RTC_ALMB_SetSubSecond
  * @param  Subsecond If binary mode is none, Value between Min_Data=0x0 and Max_Data=0x7FFF
  *                   else Value between Min_Data=0x0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE void LL_RTC_ALMB_SetSubSecond(uint32_t Subsecond)
{
  MODIFY_REG(RTC->ALRMBSSR, RTC_ALRMBSSR_SS, Subsecond);
}

/**
  * @brief  Get alarm B Sub seconds value
  * @rmtoll
  *  RTC_ALRMBSSR     SS            LL_RTC_ALMB_GetSubSecond
  * @retval If binary mode is none, Value between Min_Data=0x0 and Max_Data=0x7FFF
  *         else Value between Min_Data=0x0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_RTC_ALMB_GetSubSecond(void)
{
  return (uint32_t)(READ_BIT(RTC->ALRMBSSR, RTC_ALRMBSSR_SS));
}

/**
  * @}
  */

/** @defgroup RTC_LL_EF_Timestamp Timestamp
  * @{
  */

/**
  * @brief  Enable internal event timestamp
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           ITSE          LL_RTC_TS_EnableInternalEvent
  */
__STATIC_INLINE void LL_RTC_TS_EnableInternalEvent(void)
{
  SET_BIT(RTC->CR, RTC_CR_ITSE);
}

/**
  * @brief  Disable internal event timestamp
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           ITSE          LL_RTC_TS_DisableInternalEvent
  */
__STATIC_INLINE void LL_RTC_TS_DisableInternalEvent(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_ITSE);
}

/**
  * @brief  Check if internal event timestamp is enable or not
  * @rmtoll
  *  RTC_CR           RTC_CR_ITSE          LL_RTC_TS_IsEnabled
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_TS_IsEnabledInternalEvent(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_ITSE) == (RTC_CR_ITSE)) ? 1U : 0U);
}

/**
  * @brief  Enable Timestamp
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           TSE           LL_RTC_TS_Enable
  */
__STATIC_INLINE void LL_RTC_TS_Enable(void)
{
  SET_BIT(RTC->CR, RTC_CR_TSE);
}

/**
  * @brief  Disable Timestamp
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           TSE           LL_RTC_TS_Disable
  */
__STATIC_INLINE void LL_RTC_TS_Disable(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_TSE);
}

/**
  * @brief  Check if timestamp is enabled or not
  * @rmtoll
  *  RTC_CR           TSE          LL_RTC_TS_IsEnabled
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_TS_IsEnabled(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_TSE) == (RTC_CR_TSE)) ? 1U : 0U);
}

/**
  * @brief  Set Timestamp event active edge
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   TSE must be reset when TSEDGE is changed to avoid unwanted TSF setting
  * @rmtoll
  *  RTC_CR           TSEDGE        LL_RTC_TS_SetActiveEdge
  * @param  Edge This parameter can be one of the following values:
  *         @arg @ref LL_RTC_TIMESTAMP_EDGE_RISING
  *         @arg @ref LL_RTC_TIMESTAMP_EDGE_FALLING
  */
__STATIC_INLINE void LL_RTC_TS_SetActiveEdge(uint32_t Edge)
{
  MODIFY_REG(RTC->CR, RTC_CR_TSEDGE, Edge);
}

/**
  * @brief  Get Timestamp event active edge
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           TSEDGE        LL_RTC_TS_GetActiveEdge
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_TIMESTAMP_EDGE_RISING
  *         @arg @ref LL_RTC_TIMESTAMP_EDGE_FALLING
  */
__STATIC_INLINE uint32_t LL_RTC_TS_GetActiveEdge(void)
{
  return (uint32_t)(READ_BIT(RTC->CR, RTC_CR_TSEDGE));
}

/**
  * @brief  Get Timestamp AM/PM notation (AM or 24-hour format)
  * @rmtoll
  *  RTC_TSTR         PM            LL_RTC_TS_GetTimeFormat
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_TS_TIME_FORMAT_AM_24H
  *         @arg @ref LL_RTC_TS_TIME_FORMAT_PM
  */
__STATIC_INLINE uint32_t LL_RTC_TS_GetTimeFormat(void)
{
  return (uint32_t)(READ_BIT(RTC->TSTR, RTC_TSTR_PM));
}

/**
  * @brief  Get Timestamp Hours in BCD format
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Hours from BCD to Binary format
  * @rmtoll
  *  RTC_TSTR         HT            LL_RTC_TS_GetHour \n
  *  RTC_TSTR         HU            LL_RTC_TS_GetHour
  * @retval Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  */
__STATIC_INLINE uint32_t LL_RTC_TS_GetHour(void)
{
  return (uint32_t)(READ_BIT(RTC->TSTR, RTC_TSTR_HT | RTC_TSTR_HU) >> RTC_TSTR_HU_Pos);
}

/**
  * @brief  Get Timestamp Minutes in BCD format
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Minutes from BCD to Binary format
  * @rmtoll
  *  RTC_TSTR         MNT           LL_RTC_TS_GetMinute \n
  *  RTC_TSTR         MNU           LL_RTC_TS_GetMinute
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t LL_RTC_TS_GetMinute(void)
{
  return (uint32_t)(READ_BIT(RTC->TSTR, RTC_TSTR_MNT | RTC_TSTR_MNU) >> RTC_TSTR_MNU_Pos);
}

/**
  * @brief  Get Timestamp Seconds in BCD format
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Seconds from BCD to Binary format
  * @rmtoll
  *  RTC_TSTR         ST            LL_RTC_TS_GetSecond \n
  *  RTC_TSTR         SU            LL_RTC_TS_GetSecond
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t LL_RTC_TS_GetSecond(void)
{
  return (uint32_t)(READ_BIT(RTC->TSTR, RTC_TSTR_ST | RTC_TSTR_SU));
}

/**
  * @brief  Get Timestamp time (hour, minute and second) in BCD format
  * @note   helper macros LL_RTC_GET_HOUR, LL_RTC_GET_MINUTE and LL_RTC_GET_SECOND
  *         are available to get independently each parameter
  * @rmtoll
  *  RTC_TSTR         HT            LL_RTC_TS_GetTime \n
  *  RTC_TSTR         HU            LL_RTC_TS_GetTime \n
  *  RTC_TSTR         MNT           LL_RTC_TS_GetTime \n
  *  RTC_TSTR         MNU           LL_RTC_TS_GetTime \n
  *  RTC_TSTR         ST            LL_RTC_TS_GetTime \n
  *  RTC_TSTR         SU            LL_RTC_TS_GetTime
  * @retval Combination of hours, minutes and seconds
  */
__STATIC_INLINE uint32_t LL_RTC_TS_GetTime(void)
{
  return (uint32_t)(READ_BIT(RTC->TSTR,
                             RTC_TSTR_HT | RTC_TSTR_HU | RTC_TSTR_MNT | RTC_TSTR_MNU | RTC_TSTR_ST | RTC_TSTR_SU));
}

/**
  * @brief  Get Timestamp time (hour, minute and second) in BCD format and time format
  * @note   helper macros LL_RTC_GET_FORMAT LL_RTC_GET_HOUR, LL_RTC_GET_MINUTE
  *         and LL_RTC_GET_SECOND are available to get independently each parameter
  * @rmtoll
  *  RTC_TSTR        PM            LL_RTC_TS_GetTimeAndFormat \n
  *  RTC_TSTR        HT            LL_RTC_TS_GetTimeAndFormat \n
  *  RTC_TSTR        HU            LL_RTC_TS_GetTimeAndFormat \n
  *  RTC_TSTR        MNT           LL_RTC_TS_GetTimeAndFormat \n
  *  RTC_TSTR        MNU           LL_RTC_TS_GetTimeAndFormat \n
  *  RTC_TSTR        ST            LL_RTC_TS_GetTimeAndFormat \n
  *  RTC_TSTR        SU            LL_RTC_TS_GetTimeAndFormat
  * @retval Combination of format, hours, minutes and seconds (Format: 0x0FHHMMSS)
  */
__STATIC_INLINE uint32_t LL_RTC_TS_GetTimeAndFormat(void)
{
  uint32_t temp;

  temp = READ_BIT(RTC->TSTR, (RTC_TSTR_PM | RTC_TSTR_HT | RTC_TSTR_HU | RTC_TSTR_MNT | RTC_TSTR_MNU | \
                              RTC_TSTR_ST | RTC_TSTR_SU));
  return (uint32_t)((((temp & RTC_TSTR_PM) >> RTC_TSTR_PM_Pos) << RTC_OFFSET_FORMAT) | \
                    (((((temp & RTC_TSTR_HT) >> RTC_TSTR_HT_Pos) << 4U) | \
                      ((temp & RTC_TSTR_HU) >> RTC_TSTR_HU_Pos)) << RTC_OFFSET_HOUR) | \
                    (((((temp & RTC_TSTR_MNT) >> RTC_TSTR_MNT_Pos) << 4U) | \
                      ((temp & RTC_TSTR_MNU) >> RTC_TSTR_MNU_Pos)) << RTC_OFFSET_MINUTE) | \
                    ((((temp & RTC_TSTR_ST) >> RTC_TSTR_ST_Pos) << 4U) | ((temp & RTC_TSTR_SU) >> RTC_TSTR_SU_Pos)));
}

/**
  * @brief  Get Timestamp Week day
  * @rmtoll
  *  RTC_TSDR         WDU           LL_RTC_TS_GetWeekDay
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_WEEKDAY_MONDAY
  *         @arg @ref LL_RTC_WEEKDAY_TUESDAY
  *         @arg @ref LL_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref LL_RTC_WEEKDAY_THURSDAY
  *         @arg @ref LL_RTC_WEEKDAY_FRIDAY
  *         @arg @ref LL_RTC_WEEKDAY_SATURDAY
  *         @arg @ref LL_RTC_WEEKDAY_SUNDAY
  */
__STATIC_INLINE uint32_t LL_RTC_TS_GetWeekDay(void)
{
  return (uint32_t)(READ_BIT(RTC->TSDR, RTC_TSDR_WDU) >> RTC_TSDR_WDU_Pos);
}

/**
  * @brief  Get Timestamp Month in BCD format
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Month from BCD to Binary format
  * @rmtoll
  *  RTC_TSDR         MT            LL_RTC_TS_GetMonth \n
  *  RTC_TSDR         MU            LL_RTC_TS_GetMonth
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_MONTH_JANUARY
  *         @arg @ref LL_RTC_MONTH_FEBRUARY
  *         @arg @ref LL_RTC_MONTH_MARCH
  *         @arg @ref LL_RTC_MONTH_APRIL
  *         @arg @ref LL_RTC_MONTH_MAY
  *         @arg @ref LL_RTC_MONTH_JUNE
  *         @arg @ref LL_RTC_MONTH_JULY
  *         @arg @ref LL_RTC_MONTH_AUGUST
  *         @arg @ref LL_RTC_MONTH_SEPTEMBER
  *         @arg @ref LL_RTC_MONTH_OCTOBER
  *         @arg @ref LL_RTC_MONTH_NOVEMBER
  *         @arg @ref LL_RTC_MONTH_DECEMBER
  */
__STATIC_INLINE uint32_t LL_RTC_TS_GetMonth(void)
{
  return (uint32_t)(READ_BIT(RTC->TSDR, RTC_TSDR_MT | RTC_TSDR_MU) >> RTC_TSDR_MU_Pos);
}

/**
  * @brief  Get Timestamp Day in BCD format
  * @note   helper macro LL_RTC_CONVERT_BCD2BIN is available to convert Day from BCD to Binary format
  * @rmtoll
  *  RTC_TSDR         DT            LL_RTC_TS_GetDay \n
  *  RTC_TSDR         DU            LL_RTC_TS_GetDay
  * @retval Value between Min_Data=0x01 and Max_Data=0x31
  */
__STATIC_INLINE uint32_t LL_RTC_TS_GetDay(void)
{
  return (uint32_t)(READ_BIT(RTC->TSDR, RTC_TSDR_DT | RTC_TSDR_DU));
}

/**
  * @brief  Get Timestamp date (WeekDay, Day and Month) in BCD format
  * @note   helper macros LL_RTC_GET_WEEKDAY, LL_RTC_GET_MONTH,
  *         and LL_RTC_GET_DAY are available to get independently each parameter
  * @rmtoll
  *  RTC_TSDR         WDU           LL_RTC_TS_GetDate \n
  *  RTC_TSDR         MT            LL_RTC_TS_GetDate \n
  *  RTC_TSDR         MU            LL_RTC_TS_GetDate \n
  *  RTC_TSDR         DT            LL_RTC_TS_GetDate \n
  *  RTC_TSDR         DU            LL_RTC_TS_GetDate
  * @retval Combination of Weekday, Day and Month
  */
__STATIC_INLINE uint32_t LL_RTC_TS_GetDate(void)
{
  uint32_t temp;

  temp = READ_BIT(RTC->TSDR, (RTC_TSDR_WDU | RTC_TSDR_MT | RTC_TSDR_MU | RTC_TSDR_DT | RTC_TSDR_DU));
  return (uint32_t)((((temp & RTC_TSDR_WDU) >> RTC_TSDR_WDU_Pos) << RTC_OFFSET_WEEKDAY) | \
                    (((((temp & RTC_TSDR_DT) >> RTC_TSDR_DT_Pos) << 4U) | ((temp & RTC_TSDR_DU) >> RTC_TSDR_DU_Pos)) \
                     << RTC_OFFSET_DAY)   | (((((temp & RTC_TSDR_MT) >> RTC_TSDR_MT_Pos) << 4U) | \
                                              ((temp & RTC_TSDR_MU) >> RTC_TSDR_MU_Pos)) << RTC_OFFSET_MONTH));
}

/**
  * @brief  Get time-stamp sub second value
  * @rmtoll
  *  RTC_TSSSR        SS            LL_RTC_TS_GetSubSecond
  * @retval If binary mode is none, Value between Min_Data=0x0 and Max_Data=0x7FFF
  *         else Value between Min_Data=0x0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_RTC_TS_GetSubSecond(void)
{
  return (uint32_t)(READ_BIT(RTC->TSSSR, RTC_TSSSR_SS));
}
/**
  * @brief  Enable timestamp on tamper detection event
  * @rmtoll
  *  RTC_CR       TAMPTS        LL_RTC_TS_EnableOnTamper
  */
__STATIC_INLINE void LL_RTC_TS_EnableOnTamper(void)
{
  SET_BIT(RTC->CR, RTC_CR_TAMPTS);
}

/**
  * @brief  Disable timestamp on tamper detection event
  * @rmtoll
  *  RTC_CR       TAMPTS        LL_RTC_TS_DisableOnTamper
  */
__STATIC_INLINE void LL_RTC_TS_DisableOnTamper(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_TAMPTS);
}

/**
  * @brief  Check if timestamp on tamper detection is enabled or not
  * @rmtoll
  *  RTC_CR           TSE          LL_RTC_TS_IsEnabledOnTamper
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_TS_IsEnabledOnTamper(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_TAMPTS) == (RTC_CR_TAMPTS)) ? 1U : 0U);
}

/**
  * @}
  */

/** @defgroup RTC_LL_EF_Wakeup Wakeup
  * @{
  */

/**
  * @brief  Enable Wakeup timer
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           WUTE          LL_RTC_WAKEUP_Enable
  */
__STATIC_INLINE void LL_RTC_WAKEUP_Enable(void)
{
  SET_BIT(RTC->CR, RTC_CR_WUTE);
}

/**
  * @brief  Disable Wakeup timer
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           WUTE          LL_RTC_WAKEUP_Disable
  */
__STATIC_INLINE void LL_RTC_WAKEUP_Disable(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_WUTE);
}

/**
  * @brief  Check if Wakeup timer is enabled or not
  * @rmtoll
  *  RTC_CR           WUTE          LL_RTC_WAKEUP_IsEnabled
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_WAKEUP_IsEnabled(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_WUTE) == (RTC_CR_WUTE)) ? 1U : 0U);
}

/**
  * @brief  Start Wakeup timer in interruption or polling mode
  * @rmtoll
  *  RTC_CR          WUTE          LL_RTC_WAKEUP_Start \n
  *  RTC_CR          WUTIE         LL_RTC_WAKEUP_Start
  * @param  Interruption This parameter can be one of the following values:
  *         @arg @ref LL_RTC_WAKEUP_TIMER_IT_DISABLE
  *         @arg @ref LL_RTC_WAKEUP_TIMER_IT_ENABLE
  */
__STATIC_INLINE void LL_RTC_WAKEUP_Start(uint32_t Interruption)
{
  MODIFY_REG(RTC->CR, RTC_CR_WUTE | RTC_CR_WUTIE, RTC_CR_WUTE | Interruption);
}

/**
  * @brief  Stop Wakeup timer
  * @rmtoll
  *  RTC_CR          WUTE          LL_RTC_WAKEUP_Stop \n
  *  RTC_CR          WUTIE         LL_RTC_WAKEUP_Stop
  */
__STATIC_INLINE void LL_RTC_WAKEUP_Stop(void)
{
  MODIFY_REG(RTC->CR, RTC_CR_WUTE | RTC_CR_WUTIE, 0U);
}

/**
  * @brief  Select Wakeup clock
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   Bit can be written only when RTC_CR WUTE bit = 0 and RTC_ICSR WUTWF bit = 1
  * @rmtoll
  *  RTC_CR           WUCKSEL       LL_RTC_WAKEUP_SetClock
  * @param  WakeupClock This parameter can be one of the following values:
  *         @arg @ref LL_RTC_WAKEUPCLOCK_DIV_16
  *         @arg @ref LL_RTC_WAKEUPCLOCK_DIV_8
  *         @arg @ref LL_RTC_WAKEUPCLOCK_DIV_4
  *         @arg @ref LL_RTC_WAKEUPCLOCK_DIV_2
  *         @arg @ref LL_RTC_WAKEUPCLOCK_CKSPRE
  *         @arg @ref LL_RTC_WAKEUPCLOCK_CKSPRE_WUT
  */
__STATIC_INLINE void LL_RTC_WAKEUP_SetClock(uint32_t WakeupClock)
{
  MODIFY_REG(RTC->CR, RTC_CR_WUCKSEL, WakeupClock);
}

/**
  * @brief  Get Wakeup clock
  * @rmtoll
  *  RTC_CR           WUCKSEL       LL_RTC_WAKEUP_GetClock
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_WAKEUPCLOCK_DIV_16
  *         @arg @ref LL_RTC_WAKEUPCLOCK_DIV_8
  *         @arg @ref LL_RTC_WAKEUPCLOCK_DIV_4
  *         @arg @ref LL_RTC_WAKEUPCLOCK_DIV_2
  *         @arg @ref LL_RTC_WAKEUPCLOCK_CKSPRE
  *         @arg @ref LL_RTC_WAKEUPCLOCK_CKSPRE_WUT
  */
__STATIC_INLINE uint32_t LL_RTC_WAKEUP_GetClock(void)
{
  return (uint32_t)(READ_BIT(RTC->CR, RTC_CR_WUCKSEL));
}

/**
  * @brief  Set Wakeup auto-reload value
  * @note   Bit can be written only when WUTWF is set to 1 in RTC_ICSR
  * @rmtoll
  *  RTC_WUTR         WUT           LL_RTC_WAKEUP_SetAutoReload
  * @param  Value Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE void LL_RTC_WAKEUP_SetAutoReload(uint32_t Value)
{
  MODIFY_REG(RTC->WUTR, RTC_WUTR_WUT, Value);
}

/**
  * @brief  Get Wakeup auto-reload value
  * @rmtoll
  *  RTC_WUTR         WUT           LL_RTC_WAKEUP_GetAutoReload
  * @retval Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_RTC_WAKEUP_GetAutoReload(void)
{
  return (uint32_t)(READ_BIT(RTC->WUTR, RTC_WUTR_WUT));
}

/**
  * @brief  Set Wakeup auto-reload clear value
  * @note   Bit can be written only when WUTWF is set to 1 in RTC_ICSR
  * @rmtoll
  *  RTC_WUTR         WUTOCLR           LL_RTC_WAKEUP_SetAutoClear
  * @param  Value Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE void LL_RTC_WAKEUP_SetAutoClear(uint32_t Value)
{
  MODIFY_REG(RTC->WUTR, RTC_WUTR_WUTOCLR, Value << RTC_WUTR_WUTOCLR_Pos);
}

/**
  * @brief  Get Wakeup auto-reload clear value
  * @rmtoll
  *  RTC_WUTR         WUTOCLR           LL_RTC_WAKEUP_GetAutoClear
  * @retval Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_RTC_WAKEUP_GetAutoClear(void)
{
  return (uint32_t)(READ_BIT(RTC->WUTR, RTC_WUTR_WUTOCLR) >> RTC_WUTR_WUTOCLR_Pos);
}

/**
  * @brief  Set Wakeup auto-reload and auto-reload clear values
  * @note   Bit can be written only when WUTWF is set to 1 in RTC_ICSR
  * @rmtoll
  *  RTC_WUTR         WUTOCLR           LL_RTC_WAKEUP_Config \n
  *  RTC_WUTR         WUT               LL_RTC_WAKEUP_Config
  * @param  Reload Value between Min_Data=0x00 and Max_Data=0xFFFF
  * @param  Clear Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE void LL_RTC_WAKEUP_Config(uint32_t Reload, uint32_t Clear)
{
  WRITE_REG(RTC->WUTR, ((Clear << RTC_WUTR_WUTOCLR_Pos) & RTC_WUTR_WUTOCLR_Msk) | (Reload & RTC_WUTR_WUT_Msk));
}

/**
  * @}
  */

/** @defgroup RTC_LL_EF_Calibration Calibration
  * @{
  */

/**
  * @brief  Set Calibration output frequency (1 Hz or 512 Hz)
  * @note    Bits are write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           COE           LL_RTC_CAL_SetOutputFreq \n
  *  RTC_CR           COSEL         LL_RTC_CAL_SetOutputFreq
  * @param  Frequency This parameter can be one of the following values:
  *         @arg @ref LL_RTC_CALIB_OUTPUT_NONE
  *         @arg @ref LL_RTC_CALIB_OUTPUT_1HZ
  *         @arg @ref LL_RTC_CALIB_OUTPUT_512HZ
  */
__STATIC_INLINE void LL_RTC_CAL_SetOutputFreq(uint32_t Frequency)
{
  MODIFY_REG(RTC->CR, RTC_CR_COE | RTC_CR_COSEL, Frequency);
}

/**
  * @brief  Get Calibration output frequency (1 Hz or 512 Hz)
  * @rmtoll
  *  RTC_CR           COE           LL_RTC_CAL_GetOutputFreq \n
  *  RTC_CR           COSEL         LL_RTC_CAL_GetOutputFreq
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_CALIB_OUTPUT_NONE
  *         @arg @ref LL_RTC_CALIB_OUTPUT_1HZ
  *         @arg @ref LL_RTC_CALIB_OUTPUT_512HZ
  */
__STATIC_INLINE uint32_t LL_RTC_CAL_GetOutputFreq(void)
{
  return (uint32_t)(READ_BIT(RTC->CR, RTC_CR_COE | RTC_CR_COSEL));
}

/**
  * @brief  Insert or not One RTCCLK pulse every 2exp11 pulses (frequency increased by 488.5 ppm)
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   Bit can be written only when RECALPF is set to 0 in RTC_ICSR
  * @rmtoll
  *  RTC_CALR         CALP          LL_RTC_CAL_SetPulse
  * @param  Pulse This parameter can be one of the following values:
  *         @arg @ref LL_RTC_CALIB_INSERTPULSE_NONE
  *         @arg @ref LL_RTC_CALIB_INSERTPULSE_SET
  */
__STATIC_INLINE void LL_RTC_CAL_SetPulse(uint32_t Pulse)
{
  MODIFY_REG(RTC->CALR, RTC_CALR_CALP, Pulse);
}

/**
  * @brief  Check if one RTCCLK has been inserted or not every 2exp11 pulses (frequency increased by 488.5 ppm)
  * @rmtoll
  *  RTC_CALR         CALP          LL_RTC_CAL_IsPulseInserted
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_CAL_IsPulseInserted(void)
{
  return ((READ_BIT(RTC->CALR, RTC_CALR_CALP) == (RTC_CALR_CALP)) ? 1U : 0U);
}

/**
  * @brief  Set the calibration cycle period
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   Bit can be written only when RECALPF is set to 0 in RTC_ICSR
  * @rmtoll
  *  RTC_CALR         CALW8         LL_RTC_CAL_SetPeriod \n
  *  RTC_CALR         CALW16        LL_RTC_CAL_SetPeriod
  * @param  Period This parameter can be one of the following values:
  *         @arg @ref LL_RTC_CALIB_PERIOD_32SEC
  *         @arg @ref LL_RTC_CALIB_PERIOD_16SEC
  *         @arg @ref LL_RTC_CALIB_PERIOD_8SEC
  */
__STATIC_INLINE void LL_RTC_CAL_SetPeriod(uint32_t Period)
{
  MODIFY_REG(RTC->CALR, RTC_CALR_CALW8 | RTC_CALR_CALW16, Period);
}

/**
  * @brief  Get the calibration cycle period
  * @rmtoll
  *  RTC_CALR         CALW8         LL_RTC_CAL_GetPeriod \n
  *  RTC_CALR         CALW16        LL_RTC_CAL_GetPeriod
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RTC_CALIB_PERIOD_32SEC
  *         @arg @ref LL_RTC_CALIB_PERIOD_16SEC
  *         @arg @ref LL_RTC_CALIB_PERIOD_8SEC
  */
__STATIC_INLINE uint32_t LL_RTC_CAL_GetPeriod(void)
{
  return (uint32_t)(READ_BIT(RTC->CALR, RTC_CALR_CALW8 | RTC_CALR_CALW16));
}

/**
  * @brief  Set Calibration minus
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   Bit can be written only when RECALPF is set to 0 in RTC_ICSR
  * @rmtoll
  *  RTC_CALR         CALM          LL_RTC_CAL_SetMinus
  * @param  CalibMinus Value between Min_Data=0x00 and Max_Data=0x1FF
  */
__STATIC_INLINE void LL_RTC_CAL_SetMinus(uint32_t CalibMinus)
{
  MODIFY_REG(RTC->CALR, RTC_CALR_CALM, CalibMinus);
}

/**
  * @brief  Get Calibration minus
  * @rmtoll
  *  RTC_CALR         CALM          LL_RTC_CAL_GetMinus
  * @retval Value between Min_Data=0x00 and Max_Data= 0x1FF
  */
__STATIC_INLINE uint32_t LL_RTC_CAL_GetMinus(void)
{
  return (uint32_t)(READ_BIT(RTC->CALR, RTC_CALR_CALM));
}

/**
  * @brief Set smooth calibration
  * @rmtoll
  *  RTC_CALR         CALP          LL_RTC_CAL_SetSmoothCalibration \n
  *  RTC_CALR         CALW8         LL_RTC_CAL_SetSmoothCalibration \n
  *  RTC_CALR         CALW16        LL_RTC_CAL_SetSmoothCalibration \n
  *  RTC_CALR         CALM          LL_RTC_CAL_SetSmoothCalibration
  * @param SmoothCalibPeriod This parameter can be one of the following values:
  *        @arg @ref LL_RTC_CALIB_PERIOD_32SEC
  *        @arg @ref LL_RTC_CALIB_PERIOD_16SEC
  *        @arg @ref LL_RTC_CALIB_PERIOD_8SEC
  * @param SmoothCalibPlusPulses This parameter can be one of the following values:
  *        @arg @ref LL_RTC_CALIB_INSERTPULSE_NONE
  *        @arg @ref LL_RTC_CALIB_INSERTPULSE_SET
  * @param SmoothCalibMinusPulsesValue Value between Min_Data=0x00 and Max_Data= 0x1FF
  */
__STATIC_INLINE void LL_RTC_CAL_SetSmoothCalibration(uint32_t SmoothCalibPeriod,
                                                     uint32_t SmoothCalibPlusPulses,
                                                     uint32_t SmoothCalibMinusPulsesValue)
{
  MODIFY_REG(RTC->CALR, (RTC_CALR_CALP | RTC_CALR_CALW8 | RTC_CALR_CALW16 | RTC_CALR_CALM),
             (uint32_t)(SmoothCalibPeriod | SmoothCalibPlusPulses | SmoothCalibMinusPulsesValue));
}

/**
  * @brief  Check if the smooth calibration is enabled
  * @rmtoll
  *  RTC_CALR         CALP          LL_RTC_CAL_IsEnabledSmoothCalibration \n
  *  RTC_CALR         CALM          LL_RTC_CAL_IsEnabledSmoothCalibration
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_CAL_IsEnabledSmoothCalibration(void)
{
  return ((READ_BIT(RTC->CALR, RTC_CALR_CALP | RTC_CALR_CALM) == 0U) ? 0U : 1U);
}

/**
  * @brief  Enable Calibration Low Power
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   Bit can be written only when RECALPF is set to 0
  * @rmtoll
  *  RTC_CALR         LPCAL          LL_RTC_CAL_LowPower_Enable
  */
__STATIC_INLINE void LL_RTC_CAL_LowPower_Enable(void)
{
  SET_BIT(RTC->CALR, RTC_CALR_LPCAL);
}

/**
  * @brief  Disable Calibration Low Power
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @note   Bit can be written only when RECALPF is set to 0
  * @rmtoll
  *  RTC_CALR         LPCAL          LL_RTC_CAL_LowPower_Disable
  */
__STATIC_INLINE void LL_RTC_CAL_LowPower_Disable(void)
{
  CLEAR_BIT(RTC->CALR, RTC_CALR_LPCAL);
}

/**
  * @brief  Check if Calibration Low Power is enabled or not
  * @rmtoll
  *  RTC_CALR         LPCAL          LL_RTC_CAL_LowPower_IsEnabled
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_CAL_LowPower_IsEnabled(void)
{
  return ((READ_BIT(RTC->CALR, RTC_CALR_LPCAL) == (RTC_CALR_LPCAL)) ? 1U : 0U);
}

/**
  * @}
  */

/** @defgroup RTC_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Get Recalibration pending flag
  * @rmtoll
  *  RTC_ICSR          RECALPF       LL_RTC_IsActiveFlag_RECALP
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_RECALP(void)
{
  return ((READ_BIT(RTC->ICSR, RTC_ICSR_RECALPF) == (RTC_ICSR_RECALPF)) ? 1U : 0U);
}

/**
  * @brief  Get Timestamp flag
  * @rmtoll
  *  RTC_SR          TSF           LL_RTC_IsActiveFlag_TS
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_TS(void)
{
  return ((READ_BIT(RTC->SR, RTC_SR_TSF) == (RTC_SR_TSF)) ? 1U : 0U);
}

/**
  * @brief  Get Timestamp overflow flag
  * @rmtoll
  *  RTC_SR          TSOVF         LL_RTC_IsActiveFlag_TSOV
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_TSOV(void)
{
  return ((READ_BIT(RTC->SR, RTC_SR_TSOVF) == (RTC_SR_TSOVF)) ? 1U : 0U);
}

/**
  * @brief  Get Internal Timestamp flag
  * @rmtoll
  *  RTC_SR          ITSF          LL_RTC_IsActiveFlag_ITS
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_ITS(void)
{
  return ((READ_BIT(RTC->SR, RTC_SR_ITSF) == (RTC_SR_ITSF)) ? 1U : 0U);
}

/**
  * @brief  Get Wakeup timer flag
  * @rmtoll
  *  RTC_SR          WUTF          LL_RTC_IsActiveFlag_WUT
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_WUT(void)
{
  return ((READ_BIT(RTC->SR, RTC_SR_WUTF) == (RTC_SR_WUTF)) ? 1U : 0U);
}

/**
  * @brief  Get alarm A flag
  * @rmtoll
  *  RTC_SR          ALRAF         LL_RTC_IsActiveFlag_ALRA
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_ALRA(void)
{
  return ((READ_BIT(RTC->SR, RTC_SR_ALRAF) == (RTC_SR_ALRAF)) ? 1U : 0U);
}

/**
  * @brief  Get alarm B flag
  * @rmtoll
  *  RTC_SR          ALRBF         LL_RTC_IsActiveFlag_ALRB
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_ALRB(void)
{
  return ((READ_BIT(RTC->SR, RTC_SR_ALRBF) == (RTC_SR_ALRBF)) ? 1U : 0U);
}

/**
  * @brief  Get selected alarm flag
  * @rmtoll
  *  RTC_SR          ALRAF         LL_RTC_IsActiveFlag_ALR
  *  RTC_SR          ALRBF         LL_RTC_IsActiveFlag_ALR
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A
  *         @arg @ref LL_RTC_ALARM_B
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_ALR(const uint32_t Alarm)
{
  return ((READ_BIT(RTC->SR, (RTC_SR_ALRAF << Alarm)) == (RTC_SR_ALRAF << Alarm)) ? 1U : 0U);
}

/**
  * @brief  Get SSR Underflow flag
  * @rmtoll
  *  RTC_SR          SSRUF         LL_RTC_IsActiveFlag_SSRU
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_SSRU(void)
{
  return ((READ_BIT(RTC->SR, RTC_SR_SSRUF) == (RTC_SR_SSRUF)) ? 1U : 0U);
}

/**
  * @brief  Clear Timestamp flag
  * @rmtoll
  *  RTC_SR         CTSF           LL_RTC_ClearFlag_TS
  */
__STATIC_INLINE void LL_RTC_ClearFlag_TS(void)
{
  WRITE_REG(RTC->SCR, RTC_SCR_CTSF);
}

/**
  * @brief  Clear Timestamp overflow flag
  * @rmtoll
  *  RTC_SCR          CTSOVF         LL_RTC_ClearFlag_TSOV
  */
__STATIC_INLINE void LL_RTC_ClearFlag_TSOV(void)
{
  WRITE_REG(RTC->SCR, RTC_SCR_CTSOVF);
}

/**
  * @brief  Clear Internal Timestamp flag
  * @rmtoll
  *  RTC_SCR          CITSF          LL_RTC_ClearFlag_ITS
  */
__STATIC_INLINE void LL_RTC_ClearFlag_ITS(void)
{
  WRITE_REG(RTC->SCR, RTC_SCR_CITSF);
}

/**
  * @brief  Clear Wakeup timer flag
  * @rmtoll
  *  RTC_SCR          CWUTF          LL_RTC_ClearFlag_WUT
  */
__STATIC_INLINE void LL_RTC_ClearFlag_WUT(void)
{
  WRITE_REG(RTC->SCR, RTC_SCR_CWUTF);
}

/**
  * @brief  Clear alarm A flag
  * @rmtoll
  *  RTC_SCR          CALRAF         LL_RTC_ClearFlag_ALRA
  */
__STATIC_INLINE void LL_RTC_ClearFlag_ALRA(void)
{
  WRITE_REG(RTC->SCR, RTC_SCR_CALRAF);
}

/**
  * @brief  Clear alarm B flag
  * @rmtoll
  *  RTC_SCR          CALRBF         LL_RTC_ClearFlag_ALRB
  */
__STATIC_INLINE void LL_RTC_ClearFlag_ALRB(void)
{
  WRITE_REG(RTC->SCR, RTC_SCR_CALRBF);
}

/**
  * @brief  Clear the selected alarm flag
  * @rmtoll
  *  RTC_SCR          CALRAF         LL_RTC_ClearFlag_ALR
  *         RTC_SCR          CALRBF         LL_RTC_ClearFlag_ALR
  * @param  Alarm This parameter can be one of the following values:
  *         @arg @ref LL_RTC_ALARM_A Alarm A
  *         @arg @ref LL_RTC_ALARM_B Alarm B
  */
__STATIC_INLINE void LL_RTC_ClearFlag_ALR(uint32_t Alarm)
{
  WRITE_REG(RTC->SCR, RTC_SCR_CALRAF << Alarm);
}

/**
  * @brief  Clear SSR Underflow flag
  * @rmtoll
  *  RTC_SCR          CSSRUF         LL_RTC_ClearFlag_SSRU
  */
__STATIC_INLINE void LL_RTC_ClearFlag_SSRU(void)
{
  WRITE_REG(RTC->SCR, RTC_SCR_CSSRUF);
}

/**
  * @brief  Get Initialization flag
  * @rmtoll
  *  RTC_ICSR          INITF         LL_RTC_IsActiveFlag_INIT
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_INIT(void)
{
  return ((READ_BIT(RTC->ICSR, RTC_ICSR_INITF) == (RTC_ICSR_INITF)) ? 1U : 0U);
}

/**
  * @brief  Get Registers synchronization flag
  * @rmtoll
  *  RTC_ICSR          RSF           LL_RTC_IsActiveFlag_RS
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_RS(void)
{
  return ((READ_BIT(RTC->ICSR, RTC_ICSR_RSF) == (RTC_ICSR_RSF)) ? 1U : 0U);
}

/**
  * @brief  Clear Registers synchronization flag
  * @rmtoll
  *  RTC_ICSR          RSF           LL_RTC_ClearFlag_RS
  */
__STATIC_INLINE void LL_RTC_ClearFlag_RS(void)
{
  CLEAR_BIT(RTC->ICSR, RTC_ICSR_RSF);
}

/**
  * @brief  Get Initialization status flag
  * @rmtoll
  *  RTC_ICSR          INITS         LL_RTC_IsActiveFlag_INITS
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_INITS(void)
{
  return ((READ_BIT(RTC->ICSR, RTC_ICSR_INITS) == (RTC_ICSR_INITS)) ? 1U : 0U);
}

/**
  * @brief  Get Shift operation pending flag
  * @rmtoll
  *  RTC_ICSR          SHPF          LL_RTC_IsActiveFlag_SHP
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_SHP(void)
{
  return ((READ_BIT(RTC->ICSR, RTC_ICSR_SHPF) == (RTC_ICSR_SHPF)) ? 1U : 0U);
}

/**
  * @brief  Get Wakeup timer write flag
  * @rmtoll
  *  RTC_ICSR          WUTWF         LL_RTC_IsActiveFlag_WUTW
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_WUTW(void)
{
  return ((READ_BIT(RTC->ICSR, RTC_ICSR_WUTWF) == (RTC_ICSR_WUTWF)) ? 1U : 0U);
}

/**
  * @brief  Get alarm A masked flag
  * @rmtoll
  *  RTC_MISR          ALRAMF        LL_RTC_IsActiveFlag_ALRAM
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_ALRAM(void)
{
  return ((READ_BIT(RTC->MISR, RTC_MISR_ALRAMF) == (RTC_MISR_ALRAMF)) ? 1U : 0U);
}

/**
  * @brief  Get SSR Underflow masked flag
  * @rmtoll
  *  RTC_MISR          SSRUMF        LL_RTC_IsActiveFlag_SSRUM
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_SSRUM(void)
{
  return ((READ_BIT(RTC->MISR, RTC_MISR_SSRUMF) == (RTC_MISR_SSRUMF)) ? 1U : 0U);
}

/**
  * @brief  Get alarm B masked flag
  * @rmtoll
  *  RTC_MISR          ALRBMF        LL_RTC_IsActiveFlag_ALRBM
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_ALRBM(void)
{
  return ((READ_BIT(RTC->MISR, RTC_MISR_ALRBMF) == (RTC_MISR_ALRBMF)) ? 1U : 0U);
}

/**
  * @brief  Get Wakeup timer masked flag
  * @rmtoll
  *  RTC_MISR          WUTMF        LL_RTC_IsActiveFlag_WUTM
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_WUTM(void)
{
  return ((READ_BIT(RTC->MISR, RTC_MISR_WUTMF) == (RTC_MISR_WUTMF)) ? 1U : 0U);
}

/**
  * @brief  Get Timestamp masked flag
  * @rmtoll
  *  RTC_MISR          TSMF        LL_RTC_IsActiveFlag_TSM
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_TSM(void)
{
  return ((READ_BIT(RTC->MISR, RTC_MISR_TSMF) == (RTC_MISR_TSMF)) ? 1U : 0U);
}

/**
  * @brief  Get Timestamp overflow masked flag
  * @rmtoll
  *  RTC_MISR          TSOVMF        LL_RTC_IsActiveFlag_TSOVM
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_TSOVM(void)
{
  return ((READ_BIT(RTC->MISR, RTC_MISR_TSOVMF) == (RTC_MISR_TSOVMF)) ? 1U : 0U);
}

/**
  * @brief  Get Internal Timestamp masked flag
  * @rmtoll
  *  RTC_MISR          ITSMF        LL_RTC_IsActiveFlag_ITSM
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsActiveFlag_ITSM(void)
{
  return ((READ_BIT(RTC->MISR, RTC_MISR_ITSMF) == (RTC_MISR_ITSMF)) ? 1U : 0U);
}

/**
  * @}
  */

/** @defgroup RTC_LL_EF_SECURITY SECURITY_Management
  * @{
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/**
  * @brief  Set RTC secure level
  * @note   secure features are relevant if LL_RTC_SECURE_FULL_NO
  * @rmtoll
  *  RTC_SECCFGR           SEC           LL_RTC_ConfigSecure \n
  *  RTC_SECCFGR           INITSEC       LL_RTC_ConfigSecure \n
  *  RTC_SECCFGR           CALSEC        LL_RTC_ConfigSecure \n
  *  RTC_SECCFGR           TSSEC         LL_RTC_ConfigSecure \n
  *  RTC_SECCFGR           WUTSEC        LL_RTC_ConfigSecure \n
  *  RTC_SECCFGR           ALRASEC       LL_RTC_ConfigSecure \n
  *  RTC_SECCFGR           ALRBSEC       LL_RTC_ConfigSecure
  * @param  attribute This parameter can be a combination of the following values:
  *         @arg @ref LL_RTC_SECURE_FULL_YES
  *         @arg @ref LL_RTC_SECURE_FULL_NO
  *         @arg @ref LL_RTC_SECURE_FEATURE_INIT
  *         @arg @ref LL_RTC_SECURE_FEATURE_CAL
  *         @arg @ref LL_RTC_SECURE_FEATURE_TS
  *         @arg @ref LL_RTC_SECURE_FEATURE_WUT
  *         @arg @ref LL_RTC_SECURE_FEATURE_ALRA
  *         @arg @ref LL_RTC_SECURE_FEATURE_ALRB
  */
__STATIC_INLINE void LL_RTC_ConfigSecure(uint32_t attribute)
{
  MODIFY_REG(RTC->SECCFGR, RTC_SECCFGR_SEC | RTC_SECCFGR_INITSEC | RTC_SECCFGR_CALSEC | RTC_SECCFGR_TSSEC | \
             RTC_SECCFGR_WUTSEC | RTC_SECCFGR_ALRASEC | RTC_SECCFGR_ALRBSEC, attribute);
}
#endif /* #if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Get RTC secure level
  * @note   Secure features is relevant if LL_RTC_SECURE_FULL_YES
  * @rmtoll
  *  RTC_SECCFGR           SEC           LL_RTC_ConfigSecure \n
  *  RTC_SECCFGR           INISEC        LL_RTC_ConfigSecure \n
  *  RTC_SECCFGR           CALSEC        LL_RTC_ConfigSecure \n
  *  RTC_SECCFGR           TSSEC         LL_RTC_ConfigSecure \n
  *  RTC_SECCFGR           WUTSEC        LL_RTC_ConfigSecure \n
  *  RTC_SECCFGR           ALRASEC       LL_RTC_ConfigSecure \n
  *  RTC_SECCFGR           ALRBSEC       LL_RTC_ConfigSecure
  * @retval Combination of the following values:
  *         @arg @ref LL_RTC_SECURE_FULL_YES
  *         @arg @ref LL_RTC_SECURE_FULL_NO
  *         @arg @ref LL_RTC_SECURE_FEATURE_INIT
  *         @arg @ref LL_RTC_SECURE_FEATURE_CAL
  *         @arg @ref LL_RTC_SECURE_FEATURE_TS
  *         @arg @ref LL_RTC_SECURE_FEATURE_WUT
  *         @arg @ref LL_RTC_SECURE_FEATURE_ALRA
  *         @arg @ref LL_RTC_SECURE_FEATURE_ALRB
  */
__STATIC_INLINE uint32_t LL_RTC_GetConfigSecure(void)
{
  return READ_BIT(RTC->SECCFGR, RTC_SECCFGR_SEC | RTC_SECCFGR_INITSEC | RTC_SECCFGR_CALSEC | RTC_SECCFGR_TSSEC | \
                  RTC_SECCFGR_WUTSEC | RTC_SECCFGR_ALRASEC | RTC_SECCFGR_ALRBSEC);
}

/**
  * @}
  */

/** @defgroup RTC_LL_EF_PRIVILEGE PRIVILEGE_Management
  * @{
  */

/**
  * @brief  Set RTC privilege level
  * @note   Privilege features are relevant if LL_RTC_PRIVILEGE_FULL_NO
  * @rmtoll
  *  RTC_PRIVCFGR           PRIV              LL_RTC_ConfigPrivilege \n
  *  RTC_PRIVCFGR           INITPRIV          LL_RTC_ConfigPrivilege \n
  *  RTC_PRIVCFGR           CALPRIV           LL_RTC_ConfigPrivilege \n
  *  RTC_PRIVCFGR           TSPRIV            LL_RTC_ConfigPrivilege \n
  *  RTC_PRIVCFGR           WUTPRIV           LL_RTC_ConfigPrivilege \n
  *  RTC_PRIVCFGR           ALRAPRIV          LL_RTC_ConfigPrivilege \n
  *  RTC_PRIVCFGR           ALRBPRIV          LL_RTC_ConfigPrivilege
  * @param  attribute This parameter can be a combination of the following values:
  *         @arg @ref LL_RTC_PRIVILEGE_FULL_YES
  *         @arg @ref LL_RTC_PRIVILEGE_FULL_NO
  *         @arg @ref LL_RTC_PRIVILEGE_FEATURE_INIT
  *         @arg @ref LL_RTC_PRIVILEGE_FEATURE_CAL
  *         @arg @ref LL_RTC_PRIVILEGE_FEATURE_TS
  *         @arg @ref LL_RTC_PRIVILEGE_FEATURE_WUT
  *         @arg @ref LL_RTC_PRIVILEGE_FEATURE_ALRA
  *         @arg @ref LL_RTC_PRIVILEGE_FEATURE_ALRB
  */
__STATIC_INLINE void LL_RTC_ConfigPrivilege(uint32_t attribute)
{
  MODIFY_REG(RTC->PRIVCFGR, RTC_PRIVCFGR_PRIV | RTC_PRIVCFGR_INITPRIV | RTC_PRIVCFGR_CALPRIV | RTC_PRIVCFGR_TSPRIV | \
             RTC_PRIVCFGR_WUTPRIV | RTC_PRIVCFGR_ALRAPRIV | RTC_PRIVCFGR_ALRBPRIV, attribute);
}

/**
  * @brief  Get RTC privilege level
  * @note   Privilege features are relevant if LL_RTC_PRIVILEGE_FULL_NO
  * @rmtoll
  *  RTC_PRIVCFGR           PRIV              LL_RTC_ConfigPrivilege \n
  *  RTC_PRIVCFGR           INITPRIV          LL_RTC_ConfigPrivilege \n
  *  RTC_PRIVCFGR           CALPRIV           LL_RTC_ConfigPrivilege \n
  *  RTC_PRIVCFGR           TSPRIV            LL_RTC_ConfigPrivilege \n
  *  RTC_PRIVCFGR           WUTPRIV           LL_RTC_ConfigPrivilege \n
  *  RTC_PRIVCFGR           ALRAPRIV          LL_RTC_ConfigPrivilege \n
  *  RTC_PRIVCFGR           ALRBPRIV          LL_RTC_ConfigPrivilege
  * @retval Combination of the following values:
  *         @arg @ref LL_RTC_PRIVILEGE_FULL_YES
  *         @arg @ref LL_RTC_PRIVILEGE_FULL_NO
  *         @arg @ref LL_RTC_PRIVILEGE_FEATURE_INIT
  *         @arg @ref LL_RTC_PRIVILEGE_FEATURE_CAL
  *         @arg @ref LL_RTC_PRIVILEGE_FEATURE_TS
  *         @arg @ref LL_RTC_PRIVILEGE_FEATURE_WUT
  *         @arg @ref LL_RTC_PRIVILEGE_FEATURE_ALRA
  *         @arg @ref LL_RTC_PRIVILEGE_FEATURE_ALRB
  */
__STATIC_INLINE uint32_t LL_RTC_GetConfigPrivilege(void)
{
  return READ_BIT(RTC->PRIVCFGR, RTC_PRIVCFGR_PRIV | RTC_PRIVCFGR_INITPRIV | RTC_PRIVCFGR_CALPRIV | \
                  RTC_PRIVCFGR_TSPRIV | RTC_PRIVCFGR_WUTPRIV | RTC_PRIVCFGR_ALRAPRIV | RTC_PRIVCFGR_ALRBPRIV);
}

/**
  * @}
  */

/** @defgroup RTC_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable Timestamp interrupt
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR          TSIE         LL_RTC_EnableIT_TS
  */
__STATIC_INLINE void LL_RTC_EnableIT_TS(void)
{
  SET_BIT(RTC->CR, RTC_CR_TSIE);
}

/**
  * @brief  Disable Timestamp interrupt
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR          TSIE         LL_RTC_DisableIT_TS
  */
__STATIC_INLINE void LL_RTC_DisableIT_TS(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_TSIE);
}

/**
  * @brief  Enable Wakeup timer interrupt
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR          WUTIE         LL_RTC_EnableIT_WUT
  */
__STATIC_INLINE void LL_RTC_EnableIT_WUT(void)
{
  SET_BIT(RTC->CR, RTC_CR_WUTIE);
}

/**
  * @brief  Disable Wakeup timer interrupt
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR          WUTIE         LL_RTC_DisableIT_WUT
  */
__STATIC_INLINE void LL_RTC_DisableIT_WUT(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_WUTIE);
}

/**
  * @brief  Enable Alarm B interrupt
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           ALRBIE        LL_RTC_EnableIT_ALRB
  */
__STATIC_INLINE void LL_RTC_EnableIT_ALRB(void)
{
  SET_BIT(RTC->CR, RTC_CR_ALRBIE);
}

/**
  * @brief  Disable alarm B interrupt
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           ALRBIE        LL_RTC_DisableIT_ALRB
  */
__STATIC_INLINE void LL_RTC_DisableIT_ALRB(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_ALRBIE);
}

/**
  * @brief  Enable alarm A interrupt
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           ALRAIE        LL_RTC_EnableIT_ALRA
  */
__STATIC_INLINE void LL_RTC_EnableIT_ALRA(void)
{
  SET_BIT(RTC->CR, RTC_CR_ALRAIE);
}

/**
  * @brief  Disable alarm A interrupt
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           ALRAIE        LL_RTC_DisableIT_ALRA
  */
__STATIC_INLINE void LL_RTC_DisableIT_ALRA(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_ALRAIE);
}

/**
  * @brief  Enable SSR Underflow interrupt
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           SSRUIE        LL_RTC_EnableIT_SSRU
  */
__STATIC_INLINE void LL_RTC_EnableIT_SSRU(void)
{
  SET_BIT(RTC->CR, RTC_CR_SSRUIE);
}

/**
  * @brief  Disable SSR Underflow interrupt
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function must preferably be called before
  * @rmtoll
  *  RTC_CR           SSRUIE        LL_RTC_DisableIT_SSRU
  */
__STATIC_INLINE void LL_RTC_DisableIT_SSRU(void)
{
  CLEAR_BIT(RTC->CR, RTC_CR_SSRUIE);
}

/**
  * @brief  Check if Timestamp interrupt is enabled or not
  * @rmtoll
  *  RTC_CR           TSIE          LL_RTC_IsEnabledIT_TS
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsEnabledIT_TS(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_TSIE) == (RTC_CR_TSIE)) ? 1U : 0U);
}

/**
  * @brief  Check if Wakeup timer interrupt is enabled or not
  * @rmtoll
  *  RTC_CR           WUTIE         LL_RTC_IsEnabledIT_WUT
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsEnabledIT_WUT(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_WUTIE) == (RTC_CR_WUTIE)) ? 1U : 0U);
}

/**
  * @brief  Check if alarm A interrupt is enabled or not
  * @rmtoll
  *  RTC_CR           ALRAIE        LL_RTC_IsEnabledIT_ALRA
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsEnabledIT_ALRA(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_ALRAIE) == (RTC_CR_ALRAIE)) ? 1U : 0U);
}

/**
  * @brief  Check if alarm B interrupt is enabled or not
  * @rmtoll
  *  RTC_CR           ALRBIE        LL_RTC_IsEnabledIT_ALRB
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsEnabledIT_ALRB(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_ALRBIE) == (RTC_CR_ALRBIE)) ? 1U : 0U);
}

/**
  * @brief  Check if SSR Underflow interrupt is enabled or not
  * @rmtoll
  *  RTC_CR           SSRUIE        LL_RTC_IsEnabledIT_SSRU
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RTC_IsEnabledIT_SSRU(void)
{
  return ((READ_BIT(RTC->CR, RTC_CR_SSRUIE) == (RTC_CR_SSRUIE)) ? 1U : 0U);
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

#endif /* defined(RTC) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_LL_RTC_H */
