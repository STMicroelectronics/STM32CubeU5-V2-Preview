/**
  ******************************************************************************
  * @file    stm32u5xx_hal_rcc.c
  * @brief   RCC HAL module driver.
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
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup RCC RCC
  * @{
This file provides firmware functions to manage the following
functionalities of the Reset and Clock Control (RCC) peripheral:

- Configuration and reset functions
- Oscillators and Peripherals Control functions
- Bus configuration functions

Main APIs are not allowed to perform any other actions that their main objectif (for instance, it is not allowed to
disable a PLL or an oscillator inside an enable function).

For performance reasons, few functionalities are not supported by the HAL driver but these functionalities are covered
by the LL driver (for instance, interrupt management).

The driver is responsible of the update of SystemCoreClock variable (used by CMSIS) and System tick.

## RCC specific features

After exiting from standby or reset, the device is running from Multiple Speed Internal System (MSIS) oscillator
(by default to 4MHz but set to another value if MSIS Range after standby or reset has been modified).

- There is no prescaler on High speed (AHBs) and Low speed (APBs) busses:
all peripherals mapped on these busses are running at sysclk frequency.
- The clock for all peripherals is switched off, except the SRAM and FLASH.

Once the device started from reset, the user application could:

- Configure the clock source to be used to drive the System clock
(if the application needs higher frequency/performance)
- Configure the System clock frequency and Flash settings
- Configure the AHB and APB busses prescalers
- Enable the clock for the peripheral(s) to be used
- Configure the clock source(s) for peripherals which clocks receive an independent kernel clocks.
- Configure peripherals supporting the autonomous mode (These peripherals are able to generate a kernel clock
request and a AHB/APB bus clock request when they need, in order to operate and update their status register
even in Stop mode).

## Configuration inside the RCC driver

Config defines            | Description               | Default value | Note
------------------------- | ------------------------- | ------------- | ------------------------------------
PRODUCT                   | from IDE                  | Defined       | The selected product (ex STM32U585xx)
PERIPHERAL                | from CMSIS                | Defined       | Peripheral available on the product (ex USART1)
USE_ASSERT_DBG_PARAM      | from IDE                  | None          | When defined, enable the params assert
USE_HAL_CHECK_PARAM       | from hal_conf.h           | 0             | When set, parameters are checked in runtime
USE_HAL_RCC_MODULE        | from hal_conf.h           | 1             | When set, HAL RCC module is enabled
USE_EXTERNAL_ENV          | from IDE                  | Defined       | When set, ext. oscillators values are defined
LSE_VALUE                 | From stm32_external_env.h | 32 kHz        | Frequency of LSE oscillator (USE_EXTERNAL_ENV)
HSE_VALUE                 | From stm32_external_env.h | 32 MHz        | Frequency of HSE oscillator (USE_EXTERNAL_ENV)
EXTERNAL_SAI1_CLOCK_VALUE | From stm32_external_env.h | 48 kHz        | SAI1 External clock source (USE_EXTERNAL_ENV)
EXTERNAL_SAI2_CLOCK_VALUE | From stm32_external_env.h | 48 kHz        | SAI2 External clock source (USE_EXTERNAL_ENV)
__ARM_FEATURE_CMSE        | Trust Zone                | NA            | Defined in secure context
HSI_VALUE                 | st32u5xxxx.h              | 16 MHz        | Frequency of HSI oscillator
MSI_RESET_VALUE           | st32u5xxxx.h              | 4 MHz         | Default Frequency of MSI oscillator
MSIRangeTable             | system_stm32u5xx.c        | -             | MSIS/MSIK frequency for each range
  *
  */

#if defined(USE_HAL_RCC_MODULE) && (USE_HAL_RCC_MODULE == 1)

/* Private typedef -----------------------------------------------------------*/
/** @defgroup RCC_Private_Typedef RCC Private Type definition
  * @{
  */
typedef  uint32_t (*rcc_cb_timeout_t)(void); /*!< RCC internal Callback pointer definition */
typedef  uint32_t (*rcc_periph_clock_freq)(void); /*!< RCC Get Peripheral clock frequency pointer definition */
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup RCC_Private_Constants RCC Private Constants and enumerations
  * @{
  */
/**
  * @brief Timeout values
  * @{
  */
#define RCC_PLL_FRAC_WAIT_VALUE       1U  /*!< PLL Fractional part waiting time before new latch enable : 1 ms  */
#if defined(HSE_VALUE)
#define RCC_HSE_TIMEOUT_VALUE         HSE_STARTUP_TIMEOUT /*!< HSE Timeout value                                */
#endif /* HSE_VALUE */
#define RCC_MSI_TIMEOUT_VALUE         2U    /*!< 2 ms (minimum Tick + 1) timeout for MSIK & MSIS                */
#if defined(LSE_VALUE)
#define RCC_LSE_TIMEOUT_VALUE         LSE_STARTUP_TIMEOUT /*!< LSE Timeout value                                */
#endif /* LSE_VALUE */
#define RCC_PLL1_TIMEOUT_VALUE        2UL    /*!< 2 ms (minimum Tick + 1)                                       */
#define RCC_PLL2_TIMEOUT_VALUE        2UL    /*!< 2 ms (minimum Tick + 1)                                       */
#define RCC_PLL3_TIMEOUT_VALUE        2UL    /*!< 2 ms (minimum Tick + 1)                                       */
/* LSI maximum timeout is 16 us plus 4 LSI clock cycles when prediv is used                                     */
#define RCC_LSI_TIMEOUT_VALUE         ((10u * 128u * 1000u) / LSI_VALUE) /*!< 40 ms for LSI at 32kHz            */
#define RCC_HSI48_TIMEOUT_VALUE       2UL    /*!< 2 ms (minimum Tick + 1)                                       */
#define RCC_HSI_TIMEOUT_VALUE         2UL    /*!< 2 ms (minimum Tick + 1)                                       */
#define RCC_CLOCKSWITCH_TIMEOUT_VALUE 5000UL /*!< 5 s                                                           */

/**
  * @}
  */

/** @brief PLL index to define PLL1, PLL2 or PLL3
  * @{
  */
typedef enum
{
  PLL_1 = 0U,       /*!< ID on PLL1 */
  PLL_2 = 1U,       /*!< ID on PLL2 */
  PLL_3 = 2U,       /*!< ID on PLL3 */
} rcc_pll_id_t;
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */
/**
  * @brief Calculate the LSI frequency depending of LSI divider
  */
#define RCC_GET_LSI_FREQUENCY()   (IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSIPREDIV) ? (LSI_VALUE / 128U) : LSI_VALUE)

/**
  * @brief Calculate the MSIS frequency
  */
#define RCC_GET_MSIS_FREQUENCY()  MSIRangeTable[((uint32_t)HAL_RCC_MSIS_GetRange() >> RCC_ICSCR1_MSISRANGE_Pos)]

/**
  * @brief Calculate the MSIK frequency
  */
#define RCC_GET_MSIK_FREQUENCY()  MSIRangeTable[((uint32_t)HAL_RCC_MSIK_GetRange() >> RCC_ICSCR1_MSIKRANGE_Pos)]

/**
  * @brief IS_RCC Macros checks definition
  * @{
  */
#define IS_RCC_MSIS_CLOCK_RANGE(range) (((range) == HAL_RCC_MSIS_FREQ_48MHZ)       \
                                        || ((range) == HAL_RCC_MSIS_FREQ_24MHZ)    \
                                        || ((range) == HAL_RCC_MSIS_FREQ_16MHZ)    \
                                        || ((range) == HAL_RCC_MSIS_FREQ_12MHZ)    \
                                        || ((range) == HAL_RCC_MSIS_FREQ_4MHZ)     \
                                        || ((range) == HAL_RCC_MSIS_FREQ_2MHZ)     \
                                        || ((range) == HAL_RCC_MSIS_FREQ_1330KHZ)  \
                                        || ((range) == HAL_RCC_MSIS_FREQ_1MHZ)     \
                                        || ((range) == HAL_RCC_MSIS_FREQ_3072KHZ)  \
                                        || ((range) == HAL_RCC_MSIS_FREQ_1536KHZ)  \
                                        || ((range) == HAL_RCC_MSIS_FREQ_1024KHZ)  \
                                        || ((range) == HAL_RCC_MSIS_FREQ_768KHZ)   \
                                        || ((range) == HAL_RCC_MSIS_FREQ_400KHZ)   \
                                        || ((range) == HAL_RCC_MSIS_FREQ_200KHZ)   \
                                        || ((range) == HAL_RCC_MSIS_FREQ_133KHZ)   \
                                        || ((range) == HAL_RCC_MSIS_FREQ_100KHZ))

#define IS_RCC_MSIS_STANDBY_CLOCK_RANGE(range) (((range) == HAL_RCC_MSIS_FREQ_4MHZ)        \
                                                || ((range) == HAL_RCC_MSIS_FREQ_2MHZ)     \
                                                || ((range) == HAL_RCC_MSIS_FREQ_1330KHZ)  \
                                                || ((range) == HAL_RCC_MSIS_FREQ_1MHZ)     \
                                                || ((range) == HAL_RCC_MSIS_FREQ_3072KHZ))

#define IS_RCC_MSIK_CLOCK_RANGE(range) (((range) == HAL_RCC_MSIK_FREQ_48MHZ)       \
                                        || ((range) == HAL_RCC_MSIK_FREQ_24MHZ)    \
                                        || ((range) == HAL_RCC_MSIK_FREQ_16MHZ)    \
                                        || ((range) == HAL_RCC_MSIK_FREQ_12MHZ)    \
                                        || ((range) == HAL_RCC_MSIK_FREQ_4MHZ)     \
                                        || ((range) == HAL_RCC_MSIK_FREQ_2MHZ)     \
                                        || ((range) == HAL_RCC_MSIK_FREQ_1330KHZ)  \
                                        || ((range) == HAL_RCC_MSIK_FREQ_1MHZ)     \
                                        || ((range) == HAL_RCC_MSIK_FREQ_3072KHZ)  \
                                        || ((range) == HAL_RCC_MSIK_FREQ_1536KHZ)  \
                                        || ((range) == HAL_RCC_MSIK_FREQ_1024KHZ)  \
                                        || ((range) == HAL_RCC_MSIK_FREQ_768KHZ)   \
                                        || ((range) == HAL_RCC_MSIK_FREQ_400KHZ)   \
                                        || ((range) == HAL_RCC_MSIK_FREQ_200KHZ)   \
                                        || ((range) == HAL_RCC_MSIK_FREQ_133KHZ)   \
                                        || ((range) == HAL_RCC_MSIK_FREQ_100KHZ))

#define IS_RCC_MSIK_STANDBY_CLOCK_RANGE(range) (((range) == HAL_RCC_MSIK_FREQ_4MHZ)       \
                                                || ((range) == HAL_RCC_MSIK_FREQ_2MHZ)    \
                                                || ((range) == HAL_RCC_MSIK_FREQ_1330KHZ) \
                                                || ((range) == HAL_RCC_MSIK_FREQ_1MHZ)    \
                                                || ((range) == HAL_RCC_MSIK_FREQ_3072KHZ))

#define IS_RCC_MSI_CALIBRATION_VALUE(value) ((value) <= 255U)

#define IS_RCC_MSI_RANGE_CALIBRATION(range) (((range) == HAL_RCC_MSI_RANGE_CALIB_0_TO_3)      \
                                             || ((range) == HAL_RCC_MSI_RANGE_CALIB_4_TO_7)   \
                                             || ((range) == HAL_RCC_MSI_RANGE_CALIB_8_TO_11)  \
                                             || ((range) == HAL_RCC_MSI_RANGE_CALIB_12_TO_15))

#define IS_RCC_MSI_PLLMODE_STARTUP(source) (((source) == HAL_RCC_MSI_PLL_MODE_NORMAL) \
                                            || ((source) == HAL_RCC_MSI_PLL_MODE_FAST))

#define IS_RCC_MSI_PLLMODE_SELECT(mode) (((mode) == HAL_RCC_MSI_PLL_MODE_SEL_MSIS) \
                                         || ((mode) == HAL_RCC_MSI_PLL_MODE_SEL_MSIK))

#define IS_RCC_MSI_BIAS_MODE(mode) (((mode) == HAL_RCC_MSI_BIAS_MODE_CONTINUOUS) \
                                    || ((mode) == HAL_RCC_MSI_BIAS_MODE_SAMPLING))

#define IS_RCC_HSE_MODE_ENABLE(mode)  (((mode) == HAL_RCC_HSE_ON) \
                                       || ((mode) == HAL_RCC_HSE_BYPASS) \
                                       || ((mode) == HAL_RCC_HSE_BYPASS_DIGITAL))

#define IS_RCC_LSE_MODE_ENABLE(mode)  (((mode) == HAL_RCC_LSE_ON_RTC_ONLY) \
                                       || ((mode) == HAL_RCC_LSE_ON) \
                                       || ((mode) == HAL_RCC_LSE_BYPASS_RTC_ONLY) \
                                       || ((mode) == HAL_RCC_LSE_BYPASS))

#define IS_RCC_LSE_DRIVE(drive) (((drive) == HAL_RCC_LSE_DRIVE_LOW) \
                                 || ((drive) == HAL_RCC_LSE_DRIVE_MEDIUMLOW) \
                                 || ((drive) == HAL_RCC_LSE_DRIVE_MEDIUMHIGH) \
                                 || ((drive) == HAL_RCC_LSE_DRIVE_HIGH))

#define IS_RCC_LSE_GLITCH(filter) (((filter) == HAL_RCC_LSE_GLITCH_FILTER_DISABLE) \
                                   || ((filter) == HAL_RCC_LSE_GLITCH_FILTER_ENABLE))

#define IS_RCC_HSI_CALIBRATION_VALUE(value) ((value) <= (uint32_t)( RCC_ICSCR3_HSITRIM  >> RCC_ICSCR3_HSITRIM_Pos))

#define IS_RCC_LSI_DIV(lsi_div)  (((lsi_div) == HAL_RCC_LSI_DIV1) || ((lsi_div) == HAL_RCC_LSI_DIV128))

#define IS_RCC_PLLMBOOST_VALUE(value) (((value) == HAL_RCC_PLLMBOOST_DIV1) \
                                       || ((value) == HAL_RCC_PLLMBOOST_DIV2) \
                                       || ((value) == HAL_RCC_PLLMBOOST_DIV4) \
                                       || ((value) == HAL_RCC_PLLMBOOST_DIV6) \
                                       || ((value) == HAL_RCC_PLLMBOOST_DIV8) \
                                       || ((value) == HAL_RCC_PLLMBOOST_DIV10) \
                                       || ((value) == HAL_RCC_PLLMBOOST_DIV12) \
                                       || ((value) == HAL_RCC_PLLMBOOST_DIV14) \
                                       || ((value) == HAL_RCC_PLLMBOOST_DIV16))

#define IS_RCC_PLLVCI_VALUE(value) (((value) == HAL_RCC_PLLVCI_RANGE_0) \
                                    || ((value) == HAL_RCC_PLLVCI_RANGE_1))

#define IS_RCC_PLLM_VALUE(value) ((1U <= (value)) && ((value) <= 16U))

#define IS_RCC_PLLN_VALUE(value) ((4U <= (value)) && ((value) <= 512U))

#define IS_RCC_PLLP_VALUE(value) ((1U <= (value)) && ((value) <= 128U))

#define IS_RCC_PLLQ_VALUE(value) ((1U <= (value)) && ((value) <= 128U))

#define IS_RCC_PLLR_VALUE(value) ((1U <= (value)) && ((value) <= 128U))

#define IS_RCC_PLLSOURCE(source) (((source) == HAL_RCC_PLL_SRC_MSIS) \
                                  || ((source) == HAL_RCC_PLL_SRC_HSI) \
                                  || ((source) == HAL_RCC_PLL_SRC_HSE))

#define IS_RCC_PLL_FRACN_VALUE(value) ((value) <= 8191U)

#define IS_RCC_PLL1_OUTPUT(value) \
  ((((value) & (HAL_RCC_PLL1_OUTPUT_P | HAL_RCC_PLL1_OUTPUT_Q | HAL_RCC_PLL1_OUTPUT_R)) != 0x00u) \
   &&  (((value) & ~(HAL_RCC_PLL1_OUTPUT_P | HAL_RCC_PLL1_OUTPUT_Q | HAL_RCC_PLL1_OUTPUT_R)) == 0x00u))

#define IS_RCC_PLL2_OUTPUT(value) \
  ((((value) & (HAL_RCC_PLL2_OUTPUT_P | HAL_RCC_PLL2_OUTPUT_Q | HAL_RCC_PLL2_OUTPUT_R)) != 0x00u) \
   &&  (((value) & ~(HAL_RCC_PLL2_OUTPUT_P | HAL_RCC_PLL2_OUTPUT_Q | HAL_RCC_PLL2_OUTPUT_R)) == 0x00u))

#define IS_RCC_PLL3_OUTPUT(value) \
  ((((value) & (HAL_RCC_PLL3_OUTPUT_P | HAL_RCC_PLL3_OUTPUT_Q | HAL_RCC_PLL3_OUTPUT_R)) != 0x00u) \
   &&  (((value) & ~(HAL_RCC_PLL3_OUTPUT_P | HAL_RCC_PLL3_OUTPUT_Q | HAL_RCC_PLL3_OUTPUT_R)) == 0x00u))

#define IS_RCC_ITEM_ATTRIBUTES(item) ((0U < (item)) && ((item) <= 0x1FFFU))

#define IS_RCC_STOP_WAKEUPCLOCK(source) (((source) == HAL_RCC_STOP_WAKEUPCLOCK_MSI) \
                                         || ((source) == HAL_RCC_STOP_WAKEUPCLOCK_HSI))

#define IS_RCC_STOP_KERWAKEUPCLOCK(source) (((source) == HAL_RCC_STOP_KERWAKEUPCLOCK_MSI) \
                                            || ((source) == HAL_RCC_STOP_KERWAKEUPCLOCK_HSI))

#define IS_RCC_SYSCLKSOURCE(source) (((source) == HAL_RCC_SYSCLK_SRC_MSIS) \
                                     || ((source) == HAL_RCC_SYSCLK_SRC_HSI) \
                                     || ((source) == HAL_RCC_SYSCLK_SRC_HSE) \
                                     || ((source) == HAL_RCC_SYSCLK_SRC_PLLCLK))

#define IS_RCC_HCLK(hclk) (((hclk) == HAL_RCC_HCLK_PRESCALER1)   || ((hclk) == HAL_RCC_HCLK_PRESCALER2) \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER4)   || ((hclk) == HAL_RCC_HCLK_PRESCALER8) \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER16)  || ((hclk) == HAL_RCC_HCLK_PRESCALER64) \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER128) || ((hclk) == HAL_RCC_HCLK_PRESCALER256) \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER512))

#define IS_RCC_PCLK(pclk) (((pclk) == HAL_RCC_PCLK_PRESCALER1) || ((pclk) == HAL_RCC_PCLK_PRESCALER2) \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER4) || ((pclk) == HAL_RCC_PCLK_PRESCALER8) \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER16))

#define IS_RCC_MCO1SOURCE(source) (((source) == HAL_RCC_MCO_SRC_NOCLOCK) \
                                   || ((source) == HAL_RCC_MCO_SRC_SYSCLK) \
                                   || ((source) == HAL_RCC_MCO_SRC_MSI) \
                                   || ((source) == HAL_RCC_MCO_SRC_HSI) \
                                   || ((source) == HAL_RCC_MCO_SRC_HSE) \
                                   || ((source) == HAL_RCC_MCO_SRC_PLL1CLK) \
                                   || ((source) == HAL_RCC_MCO_SRC_LSI) \
                                   || ((source) == HAL_RCC_MCO_SRC_LSE) \
                                   || ((source) == HAL_RCC_MCO_SRC_HSI48) \
                                   || ((source) == HAL_RCC_MCO_SRC_MSIK))

#define IS_RCC_MCOPRE(div) (((div) == HAL_RCC_MCO_PRESCALER1) || ((div) == HAL_RCC_MCO_PRESCALER2) \
                            || ((div) == HAL_RCC_MCO_PRESCALER4) || ((div) == HAL_RCC_MCO_PRESCALER8) \
                            || ((div) == HAL_RCC_MCO_PRESCALER16))

#define IS_RCC_LSCOSOURCE(source) (((source) == HAL_RCC_LSCO_SRC_LSI) \
                                   || ((source) == HAL_RCC_LSCO_SRC_LSE))

#define IS_RCC_USART1_CLK(source)  \
  (((source) == HAL_RCC_USART1_CLK_SRC_PCLK2) \
   || ((source) == HAL_RCC_USART1_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_USART1_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_USART1_CLK_SRC_LSE))

#define IS_RCC_USART2_CLK(source)  \
  (((source) == HAL_RCC_USART2_CLK_SRC_PCLK1) \
   || ((source) == HAL_RCC_USART2_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_USART2_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_USART2_CLK_SRC_LSE))

#define IS_RCC_USART3_CLK(source)  \
  (((source) == HAL_RCC_USART3_CLK_SRC_PCLK1) \
   || ((source) == HAL_RCC_USART3_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_USART3_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_USART3_CLK_SRC_LSE))

#define IS_RCC_UART4_CLK(source)  \
  (((source) == HAL_RCC_UART4_CLK_SRC_PCLK1) \
   || ((source) == HAL_RCC_UART4_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_UART4_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_UART4_CLK_SRC_LSE))

#define IS_RCC_UART5_CLK(source)  \
  (((source) == HAL_RCC_UART5_CLK_SRC_PCLK1) \
   || ((source) == HAL_RCC_UART5_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_UART5_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_UART5_CLK_SRC_LSE))

#if defined(USART6)
#define IS_RCC_USART6_CLK(source)  \
  (((source) == HAL_RCC_USART6_CLK_SRC_PCLK1) \
   || ((source) == HAL_RCC_USART6_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_USART6_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_USART6_CLK_SRC_LSE))
#endif /* USART6 */

#define IS_RCC_LPUART1_CLK(source)  \
  (((source) == HAL_RCC_LPUART1_CLK_SRC_PCLK3) \
   || ((source) == HAL_RCC_LPUART1_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_LPUART1_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_LPUART1_CLK_SRC_LSE) \
   || ((source) == HAL_RCC_LPUART1_CLK_SRC_MSIK))

#define IS_RCC_I2C1_CLK(source)   \
  (((source) == HAL_RCC_I2C1_CLK_SRC_PCLK1) \
   || ((source) == HAL_RCC_I2C1_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_I2C1_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_I2C1_CLK_SRC_MSIK))

#define IS_RCC_I2C2_CLK(source)   \
  (((source) == HAL_RCC_I2C2_CLK_SRC_PCLK1) \
   || ((source) == HAL_RCC_I2C2_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_I2C2_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_I2C2_CLK_SRC_MSIK))

#define IS_RCC_I2C3_CLK(source)   \
  (((source) == HAL_RCC_I2C3_CLK_SRC_PCLK3) \
   || ((source) == HAL_RCC_I2C3_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_I2C3_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_I2C3_CLK_SRC_MSIK))

#define IS_RCC_I2C4_CLK(source)   \
  (((source) == HAL_RCC_I2C4_CLK_SRC_PCLK1) \
   || ((source) == HAL_RCC_I2C4_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_I2C4_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_I2C4_CLK_SRC_MSIK))

#if defined(I2C5)
#define IS_RCC_I2C5_CLK(source)   \
  (((source) == HAL_RCC_I2C5_CLK_SRC_PCLK1) \
   || ((source) == HAL_RCC_I2C5_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_I2C5_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_I2C5_CLK_SRC_MSIK))
#endif /* I2C5 */

#if defined(I2C6)
#define IS_RCC_I2C6_CLK(source)   \
  (((source) == HAL_RCC_I2C6_CLK_SRC_PCLK1) \
   || ((source) == HAL_RCC_I2C6_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_I2C6_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_I2C6_CLK_SRC_MSIK))
#endif /* I2C6 */

#define IS_RCC_SAI1_CLK(source)   \
  (((source) == HAL_RCC_SAI1_CLK_SRC_PLL2P) \
   || ((source) == HAL_RCC_SAI1_CLK_SRC_PLL3P) \
   || ((source) == HAL_RCC_SAI1_CLK_SRC_PLL1P) \
   || ((source) == HAL_RCC_SAI1_CLK_SRC_PIN) \
   || ((source) == HAL_RCC_SAI1_CLK_SRC_HSI))

#define IS_RCC_SAI2_CLK(source)   \
  (((source) == HAL_RCC_SAI2_CLK_SRC_PLL2P) \
   || ((source) == HAL_RCC_SAI2_CLK_SRC_PLL3P) \
   || ((source) == HAL_RCC_SAI2_CLK_SRC_PLL1P) \
   || ((source) == HAL_RCC_SAI2_CLK_SRC_PIN) \
   || ((source) == HAL_RCC_SAI2_CLK_SRC_HSI))

#define IS_RCC_LPTIM1_CLK(source)  \
  (((source) == HAL_RCC_LPTIM1_CLK_SRC_MSIK) \
   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_LSI) \
   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_LSE))

#define IS_RCC_LPTIM2_CLK(source)  \
  (((source) == HAL_RCC_LPTIM2_CLK_SRC_PCLK1) \
   || ((source) == HAL_RCC_LPTIM2_CLK_SRC_LSI) \
   || ((source) == HAL_RCC_LPTIM2_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_LPTIM2_CLK_SRC_LSE))

#define IS_RCC_LPTIM34_CLK(source)  \
  (((source) == HAL_RCC_LPTIM34_CLK_SRC_MSIK) \
   || ((source) == HAL_RCC_LPTIM34_CLK_SRC_LSI) \
   || ((source) == HAL_RCC_LPTIM34_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_LPTIM34_CLK_SRC_LSE))

#define IS_RCC_FDCAN_CLK(source)  \
  (((source) == HAL_RCC_FDCAN_CLK_SRC_HSE) \
   || ((source) == HAL_RCC_FDCAN_CLK_SRC_PLL1Q) \
   || ((source) == HAL_RCC_FDCAN_CLK_SRC_PLL2P))

#define IS_RCC_SDMMC_CLK(source)  \
  (((source) == HAL_RCC_SDMMC_CLK_SRC_CLK48) \
   || ((source) == HAL_RCC_SDMMC_CLK_SRC_PLL1P))

#define IS_RCC_RNG_CLK(source)  \
  (((source) == HAL_RCC_RNG_CLK_SRC_HSI48) \
   || ((source) == HAL_RCC_RNG_CLK_SRC_HSI48_DIV2) \
   || ((source) == HAL_RCC_RNG_CLK_SRC_HSI))

#define IS_RCC_SAES_CLK(source)  \
  (((source) == HAL_RCC_SAES_CLK_SRC_SHSI) \
   || ((source) == HAL_RCC_SAES_CLK_SRC_SHSI_DIV2))

#define IS_RCC_ADCDAC_CLK(source)  \
  (((source) == HAL_RCC_ADCDAC_CLK_SRC_HCLK) \
   || ((source) == HAL_RCC_ADCDAC_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_ADCDAC_CLK_SRC_PLL2R) \
   || ((source) == HAL_RCC_ADCDAC_CLK_SRC_HSE) \
   || ((source) == HAL_RCC_ADCDAC_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_ADCDAC_CLK_SRC_MSIK))

#define IS_RCC_MDF1_CLK(source)  \
  (((source) == HAL_RCC_MDF1_CLK_SRC_HCLK) \
   || ((source) == HAL_RCC_MDF1_CLK_SRC_PLL1P) \
   || ((source) == HAL_RCC_MDF1_CLK_SRC_PLL3Q) \
   || ((source) == HAL_RCC_MDF1_CLK_SRC_PIN) \
   || ((source) == HAL_RCC_MDF1_CLK_SRC_MSIK))

#define IS_RCC_ADF1_CLK(source)  \
  (((source) == HAL_RCC_ADF1_CLK_SRC_HCLK) \
   || ((source) == HAL_RCC_ADF1_CLK_SRC_PLL1P) \
   || ((source) == HAL_RCC_ADF1_CLK_SRC_PLL3Q) \
   || ((source) == HAL_RCC_ADF1_CLK_SRC_PIN) \
   || ((source) == HAL_RCC_ADF1_CLK_SRC_MSIK))

#define IS_RCC_OCTOSPI_CLK(source)  \
  (((source) == HAL_RCC_OCTOSPI_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_OCTOSPI_CLK_SRC_MSIK) \
   || ((source) == HAL_RCC_OCTOSPI_CLK_SRC_PLL1Q) \
   || ((source) == HAL_RCC_OCTOSPI_CLK_SRC_PLL2Q))

#if defined(HSPI1)
#define IS_RCC_HSPI1_CLK(source)  \
  (((source) == HAL_RCC_HSPI1_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_HSPI1_CLK_SRC_PLL1Q) \
   || ((source) == HAL_RCC_HSPI1_CLK_SRC_PLL2Q) \
   || ((source) == HAL_RCC_HSPI1_CLK_SRC_PLL3R))
#endif /* HSPI1 */

#define IS_RCC_ICLK_CLK(source)\
  (((source) == HAL_RCC_ICLK_CLK_SRC_HSI48) \
   || ((source) == HAL_RCC_ICLK_CLK_SRC_PLL2Q) \
   || ((source) == HAL_RCC_ICLK_CLK_SRC_PLL1Q) \
   || ((source) == HAL_RCC_ICLK_CLK_SRC_MSIK))

#define IS_RCC_SPI1_CLK(source) \
  (((source) == HAL_RCC_SPI1_CLK_SRC_PCLK2) \
   || ((source) == HAL_RCC_SPI1_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_SPI1_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_SPI1_CLK_SRC_MSIK))

#define IS_RCC_SPI2_CLK(source) \
  (((source) == HAL_RCC_SPI2_CLK_SRC_PCLK1) \
   || ((source) == HAL_RCC_SPI2_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_SPI2_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_SPI2_CLK_SRC_MSIK))

#define IS_RCC_SPI3_CLK(source) \
  (((source) == HAL_RCC_SPI3_CLK_SRC_PCLK3) \
   || ((source) == HAL_RCC_SPI3_CLK_SRC_SYSCLK) \
   || ((source) == HAL_RCC_SPI3_CLK_SRC_HSI) \
   || ((source) == HAL_RCC_SPI3_CLK_SRC_MSIK))

#define IS_RCC_DAC1_CLK(source) \
  (((source) == HAL_RCC_DAC1_CLK_SRC_LSE) \
   || ((source) == HAL_RCC_DAC1_CLK_SRC_LSI))

#define IS_RCC_TIMIC_CLK(source) (((source) == HAL_RCC_TIMIC_CLK_SRC_NONE) \
                                  || ((source) == HAL_RCC_TIMIC_CLK_SRC_HSI_256) \
                                  || ((source) == HAL_RCC_TIMIC_CLK_SRC_MSIS_1024) \
                                  || ((source) == HAL_RCC_TIMIC_CLK_SRC_MSIS_4) \
                                  || ((source) == HAL_RCC_TIMIC_CLK_SRC_MSIK_4) \
                                  || ((source) == HAL_RCC_TIMIC_CLK_SRC_MSIK_1024))

#define IS_RCC_RTC_CLK(source) (((source) == HAL_RCC_RTC_CLK_SRC_NO_CLK) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_LSE) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_LSI) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV32))

#if defined(LTDC)
#define IS_RCC_LTDC_CLK(source) \
  (((source) == HAL_RCC_LTDC_CLK_SRC_PLL3R) \
   || ((source) == HAL_RCC_LTDC_CLK_SRC_PLL2R))
#endif /* LTDC */

#if defined(DSI)
#define IS_RCC_DSI_CLK(source) \
  (((source) == HAL_RCC_DSI_CLK_SRC_PLL3) \
   || ((source) == HAL_RCC_DSI_CLK_SRC_DSIPHY))
#endif /* DSI */

#if defined(USB_OTG_HS)
#define IS_RCC_USBHSPHY_CLK(source) \
  (((source) == HAL_RCC_USBHSPHY_CLK_SRC_HSE) \
   || ((source) == HAL_RCC_USBHSPHY_CLK_SRC_HSE_DIV2) \
   || ((source) == HAL_RCC_USBHSPHY_CLK_SRC_PLL1P) \
   || ((source) == HAL_RCC_USBHSPHY_CLK_SRC_PLL1P_DIV2))
#endif /* USB_OTG_HS */

#define IS_RCC_SYSTICK_CLK(source) (((source) == HAL_RCC_SYSTICK_CLK_SRC_HCLKDIV8)    \
                                    || ((source) == HAL_RCC_SYSTICK_CLK_SRC_LSI)      \
                                    || ((source) == HAL_RCC_SYSTICK_CLK_SRC_LSE))

#define RCC_UPDATE_SYSTEMCORECLOCK()  (SystemCoreClock = HAL_RCC_GetSYSCLKFreq() >> \
                                                         AHBPrescTable[LL_RCC_GetAHBPrescaler()])
/**
  * @}
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_Private_Functions RCC Private Functions
  * @{
  */
static hal_status_t RCC_WaitForTimeout(const rcc_cb_timeout_t p_timeout_cb, uint32_t timeout, uint32_t status);
static hal_status_t RCC_PLL_SetConfig(rcc_pll_id_t pll_id, const hal_rcc_pll_config_t *p_config);
static void         RCC_PLL_GetConfig(rcc_pll_id_t pll_id, hal_rcc_pll_config_t *p_config);

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup RCC_Exported_Functions
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1_0
  * @{
  */

/**
  * @brief   Reset the RCC clock configuration to the default reset state.
  * @note    SystemCoreClock and HAL timebase are updated in this function.
  * @note    Resources under backup domain reset if USE_HAL_RCC_RESET_RTC_DOMAIN set to 1U
  * @note    Peripherals clock enable and source selection reset if USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT set to 1U
  * @warning Access to RTC domain must be enabled to disable RTC domain source clock.
  */
void HAL_RCC_Reset(void)
{
  uint32_t tickstart_ms;
  uint32_t read_value;

  /* Disable RCC interrupts */
  LL_RCC_DisableIT(LL_RCC_IT_LSIRDY | LL_RCC_IT_LSERDY | LL_RCC_IT_MSIRDY | LL_RCC_IT_HSIRDY \
                   | LL_RCC_IT_HSERDY | LL_RCC_IT_HSI48RDY | LL_RCC_IT_PLLRDY | LL_RCC_IT_PLL2RDY \
                   | LL_RCC_IT_PLL3RDY   | LL_RCC_IT_HSECSS | LL_RCC_IT_MSIKRDY | LL_RCC_IT_SHSIRDY);

#if defined(USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT) && (USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT == 1U)
  /* Reset peripheral clock enable */
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_ALL & (~(LL_AHB1_GRP1_PERIPH_FLASH | LL_AHB1_GRP1_PERIPH_SRAM1 \
                                                         | LL_AHB1_GRP1_PERIPH_DCACHE1 \
                                                         | LL_AHB1_GRP1_PERIPH_BKPSRAM)));
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_ALL & (~(LL_AHB2_GRP1_PERIPH_SRAM2 | LL_AHB2_GRP1_PERIPH_SRAM3)));
  LL_AHB2_GRP2_DisableClock(LL_AHB2_GRP2_PERIPH_ALL);
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_ALL & (~LL_AHB3_GRP1_PERIPH_SRAM4));
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_ALL);
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_ALL);
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_ALL);
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_ALL);

  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_ALL);
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_ALL);
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP2_PERIPH_ALL);
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_ALL);
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_ALL);
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_ALL);
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_ALL);

  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_ALL);

  /* Reset peripheral clock source selection */

#if defined(USART2)
#define  USART2_SEL RCC_CCIPR1_USART2SEL
#else
#define  USART2_SEL 0U
#endif /* USART2 */

  read_value = LL_RCC_READ_REG(CCIPR1);
#define RCC_CCIPR1_RESET (RCC_CCIPR1_USART1SEL | USART2_SEL | RCC_CCIPR1_USART3SEL | RCC_CCIPR1_UART4SEL \
                          | RCC_CCIPR1_UART5SEL | RCC_CCIPR1_I2C1SEL | RCC_CCIPR1_I2C2SEL | RCC_CCIPR1_I2C4SEL \
                          | RCC_CCIPR1_SPI2SEL | RCC_CCIPR1_LPTIM2SEL | RCC_CCIPR1_SPI1SEL | RCC_CCIPR1_ICLKSEL \
                          | RCC_CCIPR1_FDCANSEL)
  LL_RCC_WRITE_REG(CCIPR1, (read_value & ~RCC_CCIPR1_RESET));

#if defined(OCTOSPI1)
#define  OCTOSPI1_SEL RCC_CCIPR2_OCTOSPISEL
#else
#define  OCTOSPI1_SEL 0U
#endif /* OCTOSPI1 */

#if defined(I2C5)
#define  I2C5_SEL RCC_CCIPR2_I2C5SEL
#else
#define  I2C5_SEL 0U
#endif /* I2C5 */

#if defined(I2C6)
#define  I2C6_SEL RCC_CCIPR2_I2C6SEL
#else
#define  I2C6_SEL 0U
#endif /* I2C6 */

#if defined(HSPI1)
#define  HSPI1_SEL RCC_CCIPR2_HSPISEL
#else
#define  HSPI1_SEL 0U
#endif /* HSPI1 */

#if defined(LTDC)
#define  LTDC_SEL RCC_CCIPR2_LTDCSEL
#else
#define  LTDC_SEL 0U
#endif /* LTDC */

#if defined(USART6)
#define  USART6_SEL RCC_CCIPR2_USART6SEL
#else
#define  USART6_SEL 0U
#endif /* USART6 */

#if defined(DSI)
#define  DSI_SEL RCC_CCIPR2_DSIHOSTSEL
#else
#define  DSI_SEL 0U
#endif /* DSI */

#if defined(SAES)
#define  SAES_SEL RCC_CCIPR2_SAESSEL
#else
#define  SAES_SEL 0U
#endif /* SAES */

#if defined(SAI2)
#define  SAI2_SEL RCC_CCIPR2_SAI2SEL
#else
#define  SAI2_SEL 0U
#endif /* SAI2 */

#if defined(OTGHS)
#define  OTGHS_SEL RCC_CCIPR2_OTGHSSEL
#else
#define  OTGHS_SEL 0U
#endif /* OTGHS */

  read_value = LL_RCC_READ_REG(CCIPR2);
#define RCC_CCIPR2_RESET (RCC_CCIPR2_MDF1SEL | RCC_CCIPR2_SAI1SEL  | RCC_CCIPR2_RNGSEL | RCC_CCIPR2_SDMMCSEL \
                          | OCTOSPI1_SEL | SAI2_SEL | SAES_SEL | DSI_SEL | USART6_SEL | LTDC_SEL | HSPI1_SEL \
                          | I2C5_SEL | I2C6_SEL | OTGHS_SEL)
  LL_RCC_WRITE_REG(CCIPR2, (read_value & ~RCC_CCIPR2_RESET));

  read_value = LL_RCC_READ_REG(CCIPR3);
#define RCC_CCIPR3_RESET (RCC_CCIPR3_LPUART1SEL | RCC_CCIPR3_SPI3SEL | RCC_CCIPR3_I2C3SEL | RCC_CCIPR3_LPTIM34SEL \
                          | RCC_CCIPR3_LPTIM1SEL | RCC_CCIPR3_ADCDACSEL | RCC_CCIPR3_DAC1SEL | RCC_CCIPR3_ADF1SEL)
  LL_RCC_WRITE_REG(CCIPR3, (read_value & ~RCC_CCIPR3_RESET));
#endif /* USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT */

  /* Reset System clock */
  LL_RCC_MSIS_Enable();

  (void) RCC_WaitForTimeout(LL_RCC_MSIS_IsReady, RCC_MSI_TIMEOUT_VALUE, 1U);

  /* Set MSIRANGE default value */
  LL_RCC_MSIS_SwitchRange(LL_RCC_MSISRANGE_4);

  tickstart_ms = HAL_GetTick();

  /* MSIS is selected as system clock source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_MSIS);

  /* Wait till clock switch is ready */
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_MSIS)
  {
    if ((HAL_GetTick() - tickstart_ms) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
    {
      break;
    }
  }
  /* Reset wakeup system clock, wakeup kernel clock and MCO */
  read_value = LL_RCC_READ_REG(CFGR1);
#define RCC_CFGR1_RESET (RCC_CFGR1_STOPWUCK | RCC_CFGR1_STOPKERWUCK | RCC_CFGR1_MCOSEL | RCC_CFGR1_MCOPRE)
  LL_RCC_WRITE_REG(CFGR1, (read_value & ~RCC_CFGR1_RESET));

  /* Reset Buses clock disable and buses prescalers */
  read_value = LL_RCC_READ_REG(CFGR2);

#define RCC_CFGR2_RESET (RCC_CFGR2_HPRE | RCC_CFGR2_PPRE1 | RCC_CFGR2_PPRE2 | RCC_CFGR2_AHB1DIS | RCC_CFGR2_AHB2DIS1 \
                         | RCC_CFGR2_AHB2DIS2 | RCC_CFGR2_APB1DIS | RCC_CFGR2_APB2DIS)
#if defined(RCC_CFGR2_PPRE_DPHY)
  LL_RCC_WRITE_REG(CFGR2, ((read_value & ~RCC_CFGR2_RESET) | RCC_CFGR2_PPRE_DPHY_2 | RCC_CFGR2_PPRE_DPHY_1));
#else
  LL_RCC_WRITE_REG(CFGR2, (read_value & ~RCC_CFGR2_RESET));
#endif /* RCC_CFGR2_PPRE_DPHY */

  read_value = LL_RCC_READ_REG(CFGR3);
#define RCC_CFGR3_RESET (RCC_CFGR3_PPRE3 | RCC_CFGR3_AHB3DIS | RCC_CFGR3_APB3DIS)
  LL_RCC_WRITE_REG(CFGR3, (read_value & ~RCC_CFGR3_RESET));

  SystemCoreClock = MSI_RESET_VALUE;

  LL_RCC_SetSystickClockSource(LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8);

  /* Adapt Systick interrupt period */
  (void)HAL_InitTick(HAL_TICK_FREQ_DEFAULT, uwTickPrio);

#if defined(USE_HAL_RCC_RESET_RTC_DOMAIN ) && (USE_HAL_RCC_RESET_RTC_DOMAIN  == 1U)
  /* Reset backup domain */
  LL_RCC_ForceBackupDomainReset();
  LL_RCC_ReleaseBackupDomainReset();
#endif /* USE_HAL_RCC_RESET_RTC_DOMAIN  */


  /* Reset all remaining oscillators not in backup domain (except the one used for System clock) */
  read_value = LL_RCC_READ_REG(CR);
#define RCC_CR_RESET1 (RCC_CR_MSIKERON | RCC_CR_MSIPLLEN | RCC_CR_MSIPLLSEL | RCC_CR_MSIPLLFAST \
                       | RCC_CR_HSION | RCC_CR_HSIKERON | RCC_CR_HSI48ON | RCC_CR_SHSION \
                       | RCC_CR_HSEON | RCC_CR_HSEON | RCC_CR_PLL1ON | RCC_CR_PLL2ON | RCC_CR_PLL3ON)
#define RCC_CR_RESET2 (RCC_CR_RESET1 | RCC_CR_HSEBYP | RCC_CR_HSEEXT)
  LL_RCC_WRITE_REG(CR, (read_value & ~RCC_CR_RESET1));
  LL_RCC_WRITE_REG(CR, (read_value & ~RCC_CR_RESET2));   /* HSE EXT and BYP disabled only when HSE has been disabled */

  read_value = LL_RCC_READ_REG(ICSCR1);
#define RCC_ICSCR1_RESET (RCC_ICSCR1_MSIBIAS | RCC_ICSCR1_MSIRGSEL)
  LL_RCC_WRITE_REG(ICSCR1, ((read_value & ~RCC_ICSCR1_RESET) | RCC_ICSCR1_MSISRANGE_2 | RCC_ICSCR1_MSIKRANGE_2));


#define RCC_ICSCR2_RESET (RCC_ICSCR2_MSITRIM3_4 | RCC_ICSCR2_MSITRIM2_4 | RCC_ICSCR2_MSITRIM1_4 \
                          | RCC_ICSCR2_MSITRIM0_4)
  LL_RCC_WRITE_REG(ICSCR2, RCC_ICSCR2_RESET);

#define RCC_ICSCR3_RESET (RCC_ICSCR3_HSITRIM_4)
  LL_RCC_WRITE_REG(ICSCR3, RCC_ICSCR3_RESET);

  LL_RCC_LSI_Disable();

  read_value = LL_RCC_READ_REG(BDCR);
#define RCC_BDCR_RESET (RCC_BDCR_LSCOSEL | RCC_BDCR_LSCOEN)
  LL_RCC_WRITE_REG(BDCR, (read_value & ~RCC_BDCR_RESET));

  /* Reset PLL1 */
  read_value = LL_RCC_READ_REG(PLL1CFGR);
#define RCC_PLL1CFGR_RESET (RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1RGE | RCC_PLL1CFGR_PLL1FRACEN | RCC_PLL1CFGR_PLL1M\
                            | RCC_PLL1CFGR_PLL1MBOOST | RCC_PLL1CFGR_PLL1PEN | RCC_PLL1CFGR_PLL1QEN \
                            | RCC_PLL1CFGR_PLL1REN)
  LL_RCC_WRITE_REG(PLL1CFGR, (read_value & ~RCC_PLL1CFGR_RESET));

#define RCC_PLL1DIVR_RESET (RCC_PLL1DIVR_PLL1N_7 | RCC_PLL1DIVR_PLL1P_0 | RCC_PLL1DIVR_PLL1Q_0 | RCC_PLL1DIVR_PLL1R_0)
  LL_RCC_WRITE_REG(PLL1DIVR, RCC_PLL1DIVR_RESET);

  read_value = LL_RCC_READ_REG(PLL1FRACR);
#define RCC_PLL1FRACR_RESET (RCC_PLL1FRACR_PLL1FRACN)
  LL_RCC_WRITE_REG(PLL1FRACR, (read_value & ~RCC_PLL1FRACR_RESET));

  /* Reset PLL2 */
  read_value = LL_RCC_READ_REG(PLL2CFGR);
#define RCC_PLL2CFGR_RESET (RCC_PLL2CFGR_PLL2SRC | RCC_PLL2CFGR_PLL2RGE | RCC_PLL2CFGR_PLL2FRACEN | RCC_PLL2CFGR_PLL2M\
                            | RCC_PLL2CFGR_PLL2PEN | RCC_PLL2CFGR_PLL2QEN | RCC_PLL2CFGR_PLL2REN)
  LL_RCC_WRITE_REG(PLL2CFGR, (read_value & ~RCC_PLL2CFGR_RESET));

#define RCC_PLL2DIVR_RESET (RCC_PLL2DIVR_PLL2N_7 | RCC_PLL2DIVR_PLL2P_0 | RCC_PLL2DIVR_PLL2Q_0 | RCC_PLL2DIVR_PLL2R_0)
  LL_RCC_WRITE_REG(PLL2DIVR, RCC_PLL2DIVR_RESET);

  read_value = LL_RCC_READ_REG(PLL2FRACR);
#define RCC_PLL2FRACR_RESET (RCC_PLL2FRACR_PLL2FRACN)
  LL_RCC_WRITE_REG(PLL2FRACR, (read_value & ~RCC_PLL2FRACR_RESET));

  /* Reset PLL3 */
  read_value = LL_RCC_READ_REG(PLL3CFGR);
#define RCC_PLL3CFGR_RESET (RCC_PLL3CFGR_PLL3SRC | RCC_PLL3CFGR_PLL3RGE | RCC_PLL3CFGR_PLL3FRACEN | RCC_PLL3CFGR_PLL3M\
                            | RCC_PLL3CFGR_PLL3PEN | RCC_PLL3CFGR_PLL3QEN | RCC_PLL3CFGR_PLL3REN)
  LL_RCC_WRITE_REG(PLL3CFGR, (read_value & ~RCC_PLL3CFGR_RESET));

#define RCC_PLL3DIVR_RESET (RCC_PLL3DIVR_PLL3N_7 | RCC_PLL3DIVR_PLL3P_0 | RCC_PLL3DIVR_PLL3Q_0 | RCC_PLL3DIVR_PLL3R_0)
  LL_RCC_WRITE_REG(PLL3DIVR, RCC_PLL3DIVR_RESET);

  read_value = LL_RCC_READ_REG(PLL3FRACR);
#define RCC_PLL3FRACR_RESET (RCC_PLL3FRACR_PLL3FRACN)
  LL_RCC_WRITE_REG(PLL3FRACR, (read_value & ~RCC_PLL3FRACR_RESET));

  /* Clear RCC flags */
  LL_RCC_ClearFlag(LL_RCC_IT_LSIRDY | LL_RCC_IT_LSERDY | LL_RCC_IT_MSIRDY | LL_RCC_IT_HSIRDY \
                   | LL_RCC_IT_HSERDY | LL_RCC_IT_HSERDY | LL_RCC_IT_PLLRDY | LL_RCC_IT_PLL2RDY \
                   | LL_RCC_IT_PLL3RDY | LL_RCC_IT_HSI48RDY | LL_RCC_IT_HSECSS | LL_RCC_IT_MSIKRDY | LL_RCC_IT_SHSIRDY);

  LL_RCC_ClearResetFlags();
}


/**
  * @brief  Reset the RCC clock configuration to the default system clock (MSIS at 4 MHz)
  * @note   SystemCoreClock and Systick are updated in this function.
  * @retval HAL_OK    System clock switched to MSIS (4MHz)
  * @retval HAL_ERROR Timeout issue to enable the MSIS oscillator\n
  *                   Switch to MSIS as source clock failed\n
  *                   Issue to reconfigure the System tick
  */
hal_status_t HAL_RCC_ResetSystemClock(void)
{
  uint32_t tickstart;

  LL_RCC_MSIS_Enable();

  if (RCC_WaitForTimeout(LL_RCC_MSIS_IsReady, RCC_MSI_TIMEOUT_VALUE, 1U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Set MSIRANGE default value */
  LL_RCC_MSIS_SwitchRange(LL_RCC_MSISRANGE_4);

  tickstart = HAL_GetTick();

  /* MSIS is selected as system clock source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_MSIS);

  /* Wait till clock switch is ready */
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_MSIS)
  {
    if ((HAL_GetTick() - tickstart) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_MSIS)
      {
        return HAL_ERROR;
      }
    }
  }

  LL_RCC_SetAHBPrescaler(LL_RCC_HCLK_PRESCALER_1);
  SystemCoreClock = MSI_RESET_VALUE;

  /* Adapt Systick interrupt period */
  return (HAL_InitTick(HAL_TICK_FREQ_DEFAULT, TICK_INT_PRIORITY));
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group1_1
  * @{
  */

/**
  * @brief  Enable the HSI oscillator.
  * @retval HAL_OK      HSI oscillator has been activated successfully
  * @retval HAL_ERROR   Timeout linked to HSI ready flag not set
  */
hal_status_t HAL_RCC_HSI_Enable(void)
{
  LL_RCC_HSI_Enable();

  return RCC_WaitForTimeout(LL_RCC_HSI_IsReady, RCC_HSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the HSI oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      HSI oscillator has been deactivated successfully
  * @retval HAL_ERROR   HSI is used as system clock or source clock of the main PLL used as system clock\n
  *                     Timeout linked to HSI ready flag not reset
  */
hal_status_t HAL_RCC_HSI_Disable(void)
{
  uint32_t pll_config;
  uint32_t sysclk_source;
  hal_status_t status;

  sysclk_source = LL_RCC_GetSysClkSource();
  pll_config    = LL_RCC_PLL1_GetMainSource();

  /* Check that HSI is not used as system clock or as PLL source when PLL is selected as system clock */
  if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
      || ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PLL1) && (pll_config == LL_RCC_PLL1SOURCE_HSI)))
  {
    status = HAL_ERROR;
  }
  else
  {
    LL_RCC_HSI_Disable();
    status = RCC_WaitForTimeout(LL_RCC_HSI_IsReady, RCC_HSI_TIMEOUT_VALUE, 0U);
  }

  return status;
}

/**
  * @brief  Enable HSI even in stop mode.
  * @retval HAL_OK      HSI oscillator has been activated in stop mode
  */
hal_status_t HAL_RCC_HSI_EnableInStopMode(void)
{
  /* Enable HSI Oscillator in stop mode*/
  LL_RCC_HSI_EnableInStopMode();

  return HAL_OK;
}

/**
  * @brief  Disable HSI in stop mode.
  * @retval HAL_OK     HSI oscillator has been deactivated in stop mode
  */
hal_status_t HAL_RCC_HSI_DisableInStopMode(void)
{
  /* Disable HSI Oscillator in stop mode*/
  LL_RCC_HSI_DisableInStopMode();

  return HAL_OK;
}

/**
  * @brief  Check if HSI is enabled.
  * @retval hal_rcc_osc_enable_status_t HSI enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_HSI_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_HSI_IsEnabled();
}

/**
  * @brief  Check if HSI is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       HSI is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   HSI can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_HSI_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_HSI_IsReady();
}

/**
  * @brief  Check if HSI in stop mode is enabled.
  * @retval status based on @ref hal_rcc_osc_stop_mode_status_t
  * @retval HAL_RCC_OSC_DISABLED_IN_STOP_MODE   HSI is disabled in stop mode
  * @retval HAL_RCC_OSC_ENABLED_IN_STOP_MODE    HSI is enabled in stop mode
  */
hal_rcc_osc_stop_mode_status_t HAL_RCC_HSI_IsEnabledInStopMode(void)
{
  return (hal_rcc_osc_stop_mode_status_t)LL_RCC_HSI_IsEnabledInStopMode();
}

/**
  * @brief  Configure the HSI oscillator trimming value.
  * @param  value  Trimming value (default is @ref HAL_RCC_HSICALIBRATION_DEFAULT).
  *                This parameter must be a number between 0 and 31.
  * @note   The trimming is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @note   The trimming value might be updated while the HSI oscillator is enabled.
  */
void HAL_RCC_HSI_SetTrimming(uint32_t value)
{
  ASSERT_DBG_PARAM(IS_RCC_HSI_CALIBRATION_VALUE(value));

  LL_RCC_HSI_SetCalibTrimming(value);
}

/**
  * @brief  Get the HSI oscillator trimming value.
  * @retval Trimming Number between 0 and 31.
  */
uint32_t HAL_RCC_HSI_GetTrimming(void)
{
  return LL_RCC_HSI_GetCalibTrimming();
}

/**
  * @brief  Get the HSI oscillator calibration value.
  * @retval Calibration Number between 0x00 and 0xFFF.
  */
uint32_t  HAL_RCC_HSI_GetCalibration(void)
{
  return LL_RCC_HSI_GetCalibration();
}

/**
  * @brief  Enable the HSI48 oscillator.
  * @retval HAL_OK      HSI48 oscillator has been activated successfully
  * @retval HAL_ERROR   Timeout linked to HSI48 ready flag not set
  */
hal_status_t HAL_RCC_HSI48_Enable(void)
{
  LL_RCC_HSI48_Enable();

  return RCC_WaitForTimeout(LL_RCC_HSI48_IsReady, RCC_HSI48_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the HSI48 oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      HSI48 oscillator has been deactivated successfully
  * @retval HAL_ERROR   Timeout linked to HSI48 ready flag not reset
  */
hal_status_t HAL_RCC_HSI48_Disable(void)
{
  LL_RCC_HSI48_Disable();

  return RCC_WaitForTimeout(LL_RCC_HSI48_IsReady, RCC_HSI48_TIMEOUT_VALUE, 0U);
}

/**
  * @brief  Check if HSI48 is enabled.
  * @retval hal_rcc_osc_enable_status_t HSI48 enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_HSI48_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_HSI48_IsEnabled();
}

/**
  * @brief  Check if HSI48 is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       HSI48 is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   HSI48 can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_HSI48_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_HSI48_IsReady();
}

/**
  * @brief  Enable the Secure Internal High Speed oscillator (SHSI).
  * @retval HAL_OK      SHSI oscillator has been activated successfully
  * @retval HAL_ERROR   Timeout linked to SHSI ready flag not set
  */
hal_status_t HAL_RCC_SHSI_Enable(void)
{
  LL_RCC_SHSI_Enable();

  return RCC_WaitForTimeout(LL_RCC_SHSI_IsReady, RCC_HSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the Secure Internal High Speed oscillator (SHSI).
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      SHSI oscillator has been deactivated successfully
  * @retval HAL_ERROR   Timeout linked to SHSI ready flag not reset
  */
hal_status_t HAL_RCC_SHSI_Disable(void)
{
  LL_RCC_SHSI_Disable();

  return RCC_WaitForTimeout(LL_RCC_SHSI_IsReady, RCC_HSI_TIMEOUT_VALUE, 0U);
}

/**
  * @brief  Check if SHSI is enabled.
  * @retval hal_rcc_osc_enable_status_t SHSI enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_SHSI_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_SHSI_IsEnabled();
}

/**
  * @brief  Check if SHSI is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       SHSI is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   SHSI can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_SHSI_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_SHSI_IsReady();
}
/**
  * @brief  Enable the Internal High Speed oscillator (MSIS) with selected frequency range.
  * @param  clock_range MSIS Clock Range
  * @note   If MSIS used as system clock, an update of clock range will change the system clock.
  * @note   SystemCoreClock and Systick are updated in this function in case of adaptation of System clock.
  * @retval HAL_OK      MSIS oscillator has been activated successfully
  * @retval HAL_ERROR   Timeout linked to MSIS ready flag not set\n
  *                     Issue to reconfigure the System tick
  */
hal_status_t HAL_RCC_MSIS_Enable(hal_rcc_msis_range_t clock_range)
{
  uint32_t pll_config;
  uint32_t sysclk_source;
  hal_status_t status;

  ASSERT_DBG_PARAM(IS_RCC_MSIS_CLOCK_RANGE(clock_range));

  LL_RCC_MSIS_Enable();
  status = RCC_WaitForTimeout(LL_RCC_MSIS_IsReady, RCC_MSI_TIMEOUT_VALUE, 1U);
  if (status == HAL_OK)
  {
    /* Selects the Multiple Speed oscillator (MSI) clock range */
    LL_RCC_MSIS_SwitchRange((uint32_t)clock_range);

    sysclk_source = LL_RCC_GetSysClkSource();
    pll_config    = LL_RCC_PLL1_GetMainSource();

    /* Update the SystemCoreClock global variable
      if MSI is used as system clock or as PLL source when PLL is selected as system clock */
    if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_MSIS)
        || ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PLL1) && (pll_config == LL_RCC_PLL1SOURCE_MSIS)))
    {
      /* Update the SystemCoreClock global variable */
      RCC_UPDATE_SYSTEMCORECLOCK();

      /* Configure the source of time base considering new system clocks settings*/
      status = HAL_InitTick(uwTickFreq, uwTickPrio);
    }
  }
  return status;
}

/**
  * @brief  Disable the Internal High Speed oscillator (MSIS).
  * @warning Only possible if MSIS is not used as system clock and not the source clock
  *          of the main PLL used as system clock.
  * @warning This oscillator might be used as peripheral clock source
  *          and this function will stop any peripheral functions.
  * @retval HAL_OK      MSIS oscillator has been deactivated successfully
  * @retval HAL_ERROR   MSIS is used as system clock or source clock of the main PLL used as system clock\n
  *                     Timeout linked to MSIS ready flag not reset
  */
hal_status_t HAL_RCC_MSIS_Disable(void)
{
  uint32_t pll_config;
  uint32_t sysclk_source;
  hal_status_t status;

  sysclk_source = LL_RCC_GetSysClkSource();
  pll_config    = LL_RCC_PLL1_GetMainSource();

  /* Check that MSI is not used as system clock or as PLL source when PLL is selected as system clock */
  if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_MSIS)
      || ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PLL1) && (pll_config == LL_RCC_PLL1SOURCE_MSIS)))
  {
    status = HAL_ERROR;
  }
  else
  {
    LL_RCC_MSIS_Disable();
    status = RCC_WaitForTimeout(LL_RCC_MSIS_IsReady, RCC_MSI_TIMEOUT_VALUE, 0U);
  }

  return status;
}

/**
  * @brief  Check if MSIS is enabled.
  * @retval hal_rcc_osc_enable_status_t MSIS enable state

  */
hal_rcc_osc_enable_status_t HAL_RCC_MSIS_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_MSIS_IsEnabled();
}

/**
  * @brief  Check if MSIS is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       MSIS is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   MSIS can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_MSIS_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_MSIS_IsReady();
}

/**
  * @brief  Get the current MSIS range
  * @note   After a standby or a reset, MSI clock range selection is at 0 and the MSIS range
  *         value is provided by MSISSRANGE (only few ranges available).
  *         If MSI clock range selection has been set, MSIS range is provided in MSISRANGE (full range possible).
  * @note   MSI clock range selection can be modified through @ref HAL_RCC_MSIS_Enable().
  * @retval HAL_RCC_MSIS_FREQ_48MHZ    Range 0 around 48 MHz
  * @retval HAL_RCC_MSIS_FREQ_24MHZ    Range 1 around 24 MHz
  * @retval HAL_RCC_MSIS_FREQ_16MHZ    Range 2 around 16 MHz
  * @retval HAL_RCC_MSIS_FREQ_12MHZ    Range 3 around 12 MHz
  * @retval HAL_RCC_MSIS_FREQ_4MHZ     Range 4 around 4 MHz (available after standby)
  * @retval HAL_RCC_MSIS_FREQ_2MHZ     Range 5 around 2 MHz (available after standby)
  * @retval HAL_RCC_MSIS_FREQ_1330KHZ  Range 6 around 1.330 MHz (available after standby)
  * @retval HAL_RCC_MSIS_FREQ_1MHZ     Range 7 around 1 MHz (available after standby)
  * @retval HAL_RCC_MSIS_FREQ_3072KHZ  Range 8 around 3.072 MHz (available after standby)
  * @retval HAL_RCC_MSIS_FREQ_1536KHZ  Range 9 around 1.536 MHz
  * @retval HAL_RCC_MSIS_FREQ_1024KHZ  Range 10 around 1.024 MHz
  * @retval HAL_RCC_MSIS_FREQ_768KHZ   Range 11 around 768 kHz
  * @retval HAL_RCC_MSIS_FREQ_400KHZ   Range 12 around 400 kHz
  * @retval HAL_RCC_MSIS_FREQ_200KHZ   Range 13 around 200 kHz
  * @retval HAL_RCC_MSIS_FREQ_133KHZ   Range 14 around 133 kHz
  * @retval HAL_RCC_MSIS_FREQ_100KHZ   Range 15 around 100 kHz
  */
hal_rcc_msis_range_t HAL_RCC_MSIS_GetRange(void)
{
  return (hal_rcc_msis_range_t)(uint32_t)((LL_RCC_MSI_IsEnabledRangeSelect() != 0U) ? LL_RCC_MSIS_GetRange() :
                                          (LL_RCC_MSIS_GetRangeAfterStandby() <<
                                           (RCC_ICSCR1_MSISRANGE_Pos - RCC_CSR_MSISSRANGE_Pos)));
}

/**
  * @brief  Configure the MSIS range after standby mode.
  * @param  msi_range  MSI range
  *         This parameter can be one of the following values:
  *            @arg @ref HAL_RCC_MSIS_FREQ_4MHZ      Range 4 around 4 MHz (reset value)
  *            @arg @ref HAL_RCC_MSIS_FREQ_2MHZ      Range 5 around 2 MHz
  *            @arg @ref HAL_RCC_MSIS_FREQ_1330KHZ   Range 6 around 1.3 MHz
  *            @arg @ref HAL_RCC_MSIS_FREQ_1MHZ      Range 7 around 1 MHz
  *            @arg @ref HAL_RCC_MSIS_FREQ_3072KHZ   Range 8 around 3.072 MHz
  * @note   After exiting Standby, its frequency can be selected between 5 possible values.
  * @note   Using same RC as MSIK is reducing consumption.
  */
void HAL_RCC_MSIS_SetStandbyRange(hal_rcc_msis_range_t msi_range)
{
  ASSERT_DBG_PARAM(IS_RCC_MSIS_STANDBY_CLOCK_RANGE(msi_range));

  /* MSISSRANGE can be written only when MSIRGSEL = 1 */
  LL_RCC_MSI_EnableRangeSelection();
  LL_RCC_MSIS_SetRangeAfterStandby(((uint32_t)msi_range) >> (RCC_ICSCR1_MSISRANGE_Pos - RCC_CSR_MSISSRANGE_Pos));
}

/**
  * @brief  Enable the Internal kernel High Speed oscillator (MSIK) with selected frequency range.
  * @param  clock_range MSIK Clock Range
  * @retval HAL_OK      MSIK oscillator has been activated successfully
  * @retval HAL_ERROR   Timeout linked to MSIK ready flag not set
  */
hal_status_t HAL_RCC_MSIK_Enable(hal_rcc_msik_range_t clock_range)
{
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(IS_RCC_MSIK_CLOCK_RANGE(clock_range));

  LL_RCC_MSIK_Enable();
  if (RCC_WaitForTimeout(LL_RCC_MSIK_IsReady, RCC_MSI_TIMEOUT_VALUE, 1U) == HAL_OK)
  {
    /* Selects the Multiple Speed of kernel high speed oscillator (MSIK) clock range  */
    LL_RCC_MSIK_SwitchRange((uint32_t)clock_range);
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Disable the Internal High Speed Kernel oscillator (MSIK).
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      MSIK oscillator has been deactivated successfully
  * @retval HAL_ERROR   Timeout linked to MSIK ready flag not reset
  */
hal_status_t HAL_RCC_MSIK_Disable(void)
{
  LL_RCC_MSIK_Disable();

  return RCC_WaitForTimeout(LL_RCC_MSIK_IsReady, RCC_MSI_TIMEOUT_VALUE, 0U);
}

/**
  * @brief  Check if MSIK is enabled.
  * @retval hal_rcc_osc_enable_status_t MSIK enable state

  */
hal_rcc_osc_enable_status_t HAL_RCC_MSIK_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_MSIK_IsEnabled();
}

/**
  * @brief  Check if MSIK is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       MSIK is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   MSIK can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_MSIK_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_MSIK_IsReady();
}

/**
  * @brief  Get the current MSIK range
  * @note   After a standby or a reset, MSIK clock range selection is at 0 and the MSIK range
  *         value is provided by MSIKSRANGE (only few ranges available).
  *         If MSIK clock range selection has been set, MSIK range is provided in MSIKRANGE (full range possible).
  * @note   MSIK clock range selection can be modified through @ref HAL_RCC_MSIK_Enable().
  * @retval HAL_RCC_MSIK_FREQ_48MHZ    Range 0 around 48 MHz
  * @retval HAL_RCC_MSIK_FREQ_24MHZ    Range 1 around 24 MHz
  * @retval HAL_RCC_MSIK_FREQ_16MHZ    Range 2 around 16 MHz
  * @retval HAL_RCC_MSIK_FREQ_12MHZ    Range 3 around 12 MHz
  * @retval HAL_RCC_MSIK_FREQ_4MHZ     Range 4 around 4 MHz (available after standby)
  * @retval HAL_RCC_MSIK_FREQ_2MHZ     Range 5 around 2 MHz (available after standby)
  * @retval HAL_RCC_MSIK_FREQ_1330KHZ  Range 6 around 1.330 MHz (available after standby)
  * @retval HAL_RCC_MSIK_FREQ_1MHZ     Range 7 around 1 MHz (available after standby)
  * @retval HAL_RCC_MSIK_FREQ_3072KHZ  Range 8 around 3.072 MHz (available after standby)
  * @retval HAL_RCC_MSIK_FREQ_1536KHZ  Range 9 around 1.536 MHz
  * @retval HAL_RCC_MSIK_FREQ_1024KHZ  Range 10 around 1.024 MHz
  * @retval HAL_RCC_MSIK_FREQ_768KHZ   Range 11 around 768 kHz
  * @retval HAL_RCC_MSIK_FREQ_400KHZ   Range 12 around 400 kHz
  * @retval HAL_RCC_MSIK_FREQ_200KHZ   Range 13 around 200 kHz
  * @retval HAL_RCC_MSIK_FREQ_133KHZ   Range 14 around 133 kHz
  * @retval HAL_RCC_MSIK_FREQ_100KHZ   Range 15 around 100 kHz
  */
hal_rcc_msik_range_t HAL_RCC_MSIK_GetRange(void)
{
  return (hal_rcc_msik_range_t)(uint32_t)((LL_RCC_MSI_IsEnabledRangeSelect() != 0U) ? LL_RCC_MSIK_GetRange() :
                                          (LL_RCC_MSIK_GetRangeAfterStandby() <<
                                           (RCC_ICSCR1_MSIKRANGE_Pos - RCC_CSR_MSIKSRANGE_Pos)));
}

/**
  * @brief  Configure the MSIK range after standby mode.
  * @param  msik_range  MSIK range
  *         This parameter can be one of the following values:
  *            @arg @ref HAL_RCC_MSIK_FREQ_4MHZ      Range 4 around 4 MHz (reset value)
  *            @arg @ref HAL_RCC_MSIK_FREQ_2MHZ      Range 5 around 2 MHz
  *            @arg @ref HAL_RCC_MSIK_FREQ_1330KHZ   Range 6 around 1.3 MHz
  *            @arg @ref HAL_RCC_MSIK_FREQ_1MHZ      Range 7 around 1 MHz
  *            @arg @ref HAL_RCC_MSIK_FREQ_3072KHZ   Range 8 around 3.072 MHz
  * @note   After exiting Standby, its frequency can be selected between 5 possible values.
  * @note   Using same RC as MSIS is reducing consumption.
  */
void HAL_RCC_MSIK_SetStandbyRange(hal_rcc_msik_range_t msik_range)

{
  ASSERT_DBG_PARAM(IS_RCC_MSIK_STANDBY_CLOCK_RANGE(msik_range));

  /* MSIKSRANGE can be written only when MSIRGSEL = 1 */
  LL_RCC_MSI_EnableRangeSelection();
  LL_RCC_MSIK_SetRangeAfterStandby(((uint32_t)msik_range) >> (RCC_ICSCR1_MSIKRANGE_Pos - RCC_CSR_MSIKSRANGE_Pos));
}

/**
  * @brief  Enable MSIK even in stop mode.
  * @retval HAL_OK      MSIK oscillator has been activated in stop mode
  */
hal_status_t HAL_RCC_MSIK_EnableInStopMode(void)
{
  /* Enable MSIK oscillator in stop mode*/
  LL_RCC_MSIK_EnableInStopMode();

  return HAL_OK;
}

/**
  * @brief  Disable MSIK in stop mode.
  * @retval HAL_OK      MSIK oscillator has been deactivated in stop mode
  */
hal_status_t HAL_RCC_MSIK_DisableInStopMode(void)
{
  /* Disable MSIK oscillator in stop mode*/
  LL_RCC_MSIK_DisableInStopMode();

  return HAL_OK;
}

/**
  * @brief  Check if MSIK in stop mode is enabled.
  * @retval status based on @ref hal_rcc_osc_stop_mode_status_t
  * @retval HAL_RCC_OSC_DISABLED_IN_STOP_MODE   MSIK is disabled in stop mode
  * @retval HAL_RCC_OSC_ENABLED_IN_STOP_MODE    MSIK is enabled in stop mode
  */
hal_rcc_osc_stop_mode_status_t HAL_RCC_MSIK_IsEnabledInStopMode(void)
{
  return (hal_rcc_osc_stop_mode_status_t)LL_RCC_MSIK_IsEnabledInStopMode();
}

/**
  * @brief  Configure the MSIS/MSIK oscillators trimming value (used for SW trimming).
  * @param  value  Trimming value (default is @ref HAL_RCC_MSICALIBRATION_DEFAULT).
  *                This parameter must be a number between 0 and 31.
  * @param  ranges Select MSI ranges to be calibrated.
  * @note   The trimming is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal MSI RCx (x from 0 to 3).
  * @note   The trimming value might be updated while the MSI oscillator is enabled.
  */
void         HAL_RCC_MSI_SetTrimming(uint32_t value, hal_rcc_msi_range_calib_t ranges)
{
  ASSERT_DBG_PARAM(IS_RCC_MSI_CALIBRATION_VALUE(value));
  ASSERT_DBG_PARAM(IS_RCC_MSI_RANGE_CALIBRATION(ranges));

  LL_RCC_MSI_SetCalibTrimming(value, (uint32_t)ranges);
}

/**
  * @brief  Get the MSIS/MSIK oscillators trimming value.
  * @param  ranges Select MSI ranges.
  * @retval uint32_t MSIS/MSIK trimming value between 0 and 31.
  */
uint32_t     HAL_RCC_MSI_GetTrimming(hal_rcc_msi_range_calib_t ranges)
{
  ASSERT_DBG_PARAM(IS_RCC_MSI_RANGE_CALIBRATION(ranges));
  return LL_RCC_MSI_GetCalibTrimming((uint32_t)ranges);
}

/**
  * @brief  Get the MSIS/MSIK oscillators calibration value.
  * @param  ranges Select MSI ranges.
  * @retval uint32_t MSIS/MSIK calibration value between 0 and 31.
  */
uint32_t     HAL_RCC_MSI_GetCalibration(hal_rcc_msi_range_calib_t ranges)
{
  ASSERT_DBG_PARAM(IS_RCC_MSI_RANGE_CALIBRATION(ranges));
  return LL_RCC_MSI_GetCalibration((uint32_t)ranges);
}

#if defined(LSE_VALUE)
/**
  * @brief  Enable HW auto trimming with LSE.
  * @param  type      Select MSI used with the PLL (MSIK or MSIS).
  * @param  pll_mode  Activation of MSI PLL-mode stabilization time
  * @warning LSE must be present and started.
  * @warning The HW auto trimming with LSE must not be used in conjunction with software trimming.
  * @retval HAL_OK    HW Autocalibration ready
  * @retval HAL_ERROR LSE oscillator is not enabled\n
  *                   PLL mode is enabled (MSIPLLEN = 1)
  */
hal_status_t HAL_RCC_MSI_EnableHWAutoCalib(hal_rcc_msi_pll_mode_sel_t type, hal_rcc_msi_pll_mode_startup_t pll_mode)
{
  ASSERT_DBG_PARAM(IS_RCC_MSI_PLLMODE_SELECT(type));
  ASSERT_DBG_PARAM(IS_RCC_MSI_PLLMODE_STARTUP(pll_mode));

  if (LL_RCC_LSE_IsReady() == 0U)
  {
    return HAL_ERROR;
  }

  if (LL_RCC_IsEnabledPLLMode() != 0U)
  {
    return HAL_ERROR;
  }

  /* Select MSIS or MSIK used for calibration */
  /* Enable MSI PLL mode fast startup if requested */
  LL_RCC_MSI_ConfigHWAutoCalib((uint32_t)type, (uint32_t)pll_mode);
  LL_RCC_MSI_EnablePLLMode();

  return HAL_OK;
}

/**
  * @brief  Disable HW auto calibration with LSE.
  * @note   Fast mode will be automatically disabled.
  */
void     HAL_RCC_MSI_DisableHWAutoCalib(void)
{
  /*
   * Disable the PLL mode
   * Disable MSI PLL mode fast startup
   * Select MSIK used for calibration
   */
  LL_RCC_MSI_DisablePLLMode();
  LL_RCC_MSI_ConfigHWAutoCalib(LL_RCC_PLLMODE_MSIK, LL_RCC_PLLFAST_NORMAL);
}

/**
  * @brief Select which MSI output clock uses the PLL mode.
  * @param msipll_mode_selection specifies which MSI output clock uses the PLL mode.
  * @note  Prior to disable PLL-mode (MSIPLLEN = 0) before call HAL_RCC_MSI_EnablePLLModeSelection.
  * @note  The MSI kernel clock output uses the same oscillator source than the MSI system
  *        clock output, then the PLL mode is applied to the both clocks outputs.
  * @retval HAL_OK    PLL Mode selected
  * @retval HAL_ERROR PLL mode is enabled (MSIPLLEN = 1)
  */
hal_status_t HAL_RCC_MSI_EnablePLLModeSelection(hal_rcc_msi_pll_mode_sel_t msipll_mode_selection)
{
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(IS_RCC_MSI_PLLMODE_SELECT(msipll_mode_selection));

  if (LL_RCC_IsEnabledPLLMode() == 0U)
  {
    /* This bit is used only if PLL mode is disabled (MSIPLLEN = 0) */
    LL_RCC_SetMSIPLLMode((uint32_t)msipll_mode_selection);
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief Enable the fast PLL mode start-up of the MSI clock
  * @note  Prior to enable PLL-mode (MSIPLLEN = 1) before call HAL_RCC_MSI_EnablePLLFastStartup.
  * @note  The fast start-up feature is not active the first time the PLL mode is selected. The
  *        fast start-up is active when the MSI in PLL mode returns from switch off.
  * @retval HAL_OK    Fast PLL mode start-up enabled
  * @retval HAL_ERROR PLL-mode is not enabled
  */
hal_status_t HAL_RCC_MSI_EnablePLLFastStartup(void)
{
  hal_status_t status = HAL_ERROR;

  if (LL_RCC_IsEnabledPLLMode() != 0U)
  {
    /* This bit is used only if PLL mode is selected (MSIPLLEN = 1) */
    LL_RCC_Enable_MSIPLLFAST();
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief Disable the fast PLL mode start-up of the MSI clock
  * @note  the MSI fast startup mode disabled only when PLL-mode is enabled.
  * @retval HAL_OK    Fast PLL Mode start-up disabled
  * @retval HAL_ERROR PLL-mode is not enabled
  */
hal_status_t HAL_RCC_MSI_DisablePLLFastStartup(void)
{
  hal_status_t status = HAL_ERROR;

  if (LL_RCC_IsEnabledPLLMode() != 0U)
  {
    /* This bit is used only if PLL mode is selected (MSIPLLEN = 1) */
    LL_RCC_Disable_MSIPLLFAST();
    status = HAL_OK;
  }
  return status;
}

/**
  * @brief  Enable the PLL-mode of the MSI.
  * @note   Prior to enable the PLL-mode of the MSI for automatic hardware
  *         calibration, LSE oscillator must be enabled with HAL_RCC_LSE_Enable().
  * @retval HAL_OK    PLL-mode enabled
  * @retval HAL_ERROR LSE oscillator is not ready
  */
hal_status_t HAL_RCC_MSI_EnablePLLMode(void)
{
  hal_status_t status = HAL_ERROR;

  if (LL_RCC_LSE_IsReady() != 0U)
  {
    LL_RCC_MSI_EnablePLLMode();
    status = HAL_OK;
  }
  return status;
}

/**
  * @brief  Disable the PLL-mode of the MSI.
  * @note   PLL-mode of the MSI is automatically reset when LSE oscillator is disabled.
  */
void HAL_RCC_MSI_DisablePLLMode(void)
{
  LL_RCC_MSI_DisablePLLMode();
}
#endif /* LSE_VALUE */

/**
  * @brief  Set MSI Bias mode
  * @param  bias_mode MSI Bias mode based on @ref hal_rcc_msi_bias_mode_t
  */
void HAL_RCC_MSI_SetBiasMode(hal_rcc_msi_bias_mode_t bias_mode)
{
  ASSERT_DBG_PARAM(IS_RCC_MSI_BIAS_MODE(bias_mode));
  LL_RCC_MSI_SetMSIBiasMode((uint32_t)bias_mode);
}

/**
  * @brief  Get MSI Bias mode
  * @retval hal_rcc_msi_bias_mode_t MSI Bias mode
  */
hal_rcc_msi_bias_mode_t HAL_RCC_MSI_GetBiasMode(void)
{
  return (hal_rcc_msi_bias_mode_t)LL_RCC_MSI_GetMSIBiasMode();
}

/**
  * @brief  Enable the Internal Low Speed oscillator (LSI) with selected divider.
  * @param  divider     LSI divider
  * @warning Access to backup domain must be enabled.
  * @retval HAL_OK      LSI oscillator has been configured successfully
  * @retval HAL_ERROR   Timeout linked to LSI ready flag not set\n
  *                     LSION not set and LSIRDY set, LSI divider cannot be updated\n
  *                     Backup domain is not enabled
  */
hal_status_t HAL_RCC_LSI_Enable(hal_rcc_lsi_div_t divider)
{
  uint32_t bdcr_temp = LL_RCC_READ_REG(BDCR);

  ASSERT_DBG_PARAM(IS_RCC_LSI_DIV(divider));

  if (HAL_PWR_IsEnabledRTCDomainWriteProtection() != HAL_PWR_RTC_DOMAIN_WRP_DISABLED)
  {
    return HAL_ERROR;
  }

  if ((uint32_t)divider != READ_BIT(bdcr_temp, RCC_BDCR_LSIPREDIV))
  {
    /* This bit can be written only when the LSI is disabled */
    if (IS_BIT_SET(bdcr_temp, RCC_BDCR_LSIRDY))
    {
      return HAL_ERROR;
    }
    LL_RCC_LSI_SetPrescaler((uint32_t)divider);
  }

  /* Enable the Internal Low Speed oscillator (LSI) */
  LL_RCC_LSI_Enable();

  return RCC_WaitForTimeout(LL_RCC_LSI_IsReady, RCC_LSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the LSI oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @warning Access to backup domain must be enabled.
  * @retval HAL_OK      LSI oscillator has been deactivated successfully
  * @retval HAL_ERROR   Timeout linked to LSI ready flag not reset\n
  *                     Backup domain is not enabled
  */
hal_status_t HAL_RCC_LSI_Disable(void)
{
  if (HAL_PWR_IsEnabledRTCDomainWriteProtection() != HAL_PWR_RTC_DOMAIN_WRP_DISABLED)
  {
    return HAL_ERROR;
  }

  LL_RCC_LSI_Disable();

  return RCC_WaitForTimeout(LL_RCC_LSI_IsReady, RCC_LSI_TIMEOUT_VALUE, 0U);
}

/**
  * @brief  Check if LSI is enabled.
  * @retval hal_rcc_osc_enable_status_t LSI enable state

  */
hal_rcc_osc_enable_status_t HAL_RCC_LSI_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_LSI_IsEnabled();
}

/**
  * @brief  Check if LSI is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       LSI is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   LSI can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_LSI_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_LSI_IsReady();
}

#if defined(HSE_VALUE)
/**
  * @brief  Enable the HSE oscillator in the selected mode.
  * @param  mode        HSE mode.\n This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_HSE_ON
  *         @arg @ref HAL_RCC_HSE_BYPASS
  *         @arg @ref HAL_RCC_HSE_BYPASS_DIGITAL
  * @note   Transitions HSE Bypass to HSE On and HSE On to HSE Bypass are not
  *         supported by this function.
  * @retval HAL_OK      HSE oscillator has been activated configured
  * @retval HAL_ERROR   Timeout linked to HSE ready flag not set
  */
hal_status_t HAL_RCC_HSE_Enable(hal_rcc_hse_t mode)
{
  ASSERT_DBG_PARAM(IS_RCC_HSE_MODE_ENABLE(mode));

  /* Set the new HSE configuration */
  if (((uint32_t)mode & RCC_CR_HSEBYP) == RCC_CR_HSEBYP)
  {
    LL_RCC_HSE_ConfigBypass((uint32_t)mode & RCC_CR_HSEEXT);
  }

  LL_RCC_HSE_Enable();

  return RCC_WaitForTimeout(LL_RCC_HSE_IsReady, RCC_HSE_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the HSE oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      HSE oscillator has been deactivated successfully
  * @retval HAL_ERROR   HSE is used as system clock or source clock of the main PLL used as system clock\n
  *                     Timeout linked to HSE ready flag not reset
  */
hal_status_t HAL_RCC_HSE_Disable(void)
{
  uint32_t pll_config;
  uint32_t sysclk_source;
  hal_status_t status;

  sysclk_source = LL_RCC_GetSysClkSource();
  pll_config    = LL_RCC_PLL1_GetMainSource();

  /* When the HSE is used as system clock or clock source for PLL in these cases it is not allowed to be disabled */
  if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSE)
      || ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PLL1) && (pll_config == LL_RCC_PLL1SOURCE_HSE)))
  {
    status = HAL_ERROR;
  }
  else
  {
    LL_RCC_HSE_Disable();
    LL_RCC_HSE_DisableBypass();
    LL_RCC_HSE_SetClockMode(LL_RCC_HSE_ANALOG_MODE);
    status = RCC_WaitForTimeout(LL_RCC_HSE_IsReady, RCC_HSE_TIMEOUT_VALUE, 0U);

  }

  return status;
}

/**
  * @brief  Check if HSE is enabled.
  * @retval hal_rcc_osc_enable_status_t HSE enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_HSE_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_HSE_IsEnabled();
}

/**
  * @brief  Check if HSE is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       HSE is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   HSE can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_HSE_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_HSE_IsReady();
}
#endif /* HSE_VALUE */

#if defined(LSE_VALUE)
/**
  * @brief  Enable the LSE oscillator in the selected mode with a oscillator drive capability.
  * @param  mode        LSE mode.\n This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_LSE_ON_RTC_ONLY
  *         @arg @ref HAL_RCC_LSE_ON
  *         @arg @ref HAL_RCC_LSE_BYPASS_RTC_ONLY
  *         @arg @ref HAL_RCC_LSE_BYPASS
  * @param  drive         LSE drive capability
  * @param  glitch_filter LSE clock glitch filter
  * @warning Access to backup domain must be enabled.
  * @note   Drive capability is relevant only in Xtal mode (means not in bypass mode)
  * @retval HAL_OK      LSE oscillator has been configured successfully
  * @retval HAL_ERROR   Backup domain is not enabled\n
  *                     Timeout linked to LSE ready flag not set\n
  *                     LSE propagation enable issue (HAL_RCC_LSE_ON or HAL_RCC_LSE_BYPASS)\n
  *                     LSE propagation disable issue (HAL_RCC_LSE_ON_RTC_ONLY or HAL_RCC_LSE_BYPASS_RTC_ONLY)
  */
hal_status_t HAL_RCC_LSE_Enable(hal_rcc_lse_t mode, hal_rcc_lse_drive_t drive,
                                hal_rcc_lse_glitch_filter_t glitch_filter)
{
  ASSERT_DBG_PARAM(IS_RCC_LSE_MODE_ENABLE(mode));
  ASSERT_DBG_PARAM(IS_RCC_LSE_DRIVE(drive));
  ASSERT_DBG_PARAM(IS_RCC_LSE_GLITCH(glitch_filter));

  if (HAL_PWR_IsEnabledRTCDomainWriteProtection() != HAL_PWR_RTC_DOMAIN_WRP_DISABLED)
  {
    return HAL_ERROR;
  }

  /* Set the new LSE configuration ---------------------------------------*/
  if (((uint32_t)mode & RCC_BDCR_LSEBYP) == RCC_BDCR_LSEBYP)
  {
    LL_RCC_LSE_EnableBypass();
  }
  else
  {
    /* LSE drive capability can be configured */
    LL_RCC_LSE_SetDriveCapability((uint32_t)drive);
  }

  /* Glitch filter activation ? */
  if (glitch_filter == HAL_RCC_LSE_GLITCH_FILTER_DISABLE)
  {
    LL_RCC_LSE_DisableGlitchFilter();
  }
  else
  {
    LL_RCC_LSE_EnableGlitchFilter();
  }

  /* Enable LSE and wait for activation */
  LL_RCC_LSE_Enable();
  if (RCC_WaitForTimeout(LL_RCC_LSE_IsReady, RCC_LSE_TIMEOUT_VALUE, 1U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Enable LSESYS additionally if requested */
  if (((uint32_t)mode & RCC_BDCR_LSESYSEN) == RCC_BDCR_LSESYSEN)
  {
    LL_RCC_LSE_EnablePropagation();
    if (RCC_WaitForTimeout(LL_RCC_LSE_IsPropagationReady, RCC_LSE_TIMEOUT_VALUE, 1U) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }
  else
  {
    /* Make sure LSESYSEN/LSESYSRDY are reset */
    LL_RCC_LSE_DisablePropagation();
    if (RCC_WaitForTimeout(LL_RCC_LSE_IsPropagationReady, RCC_LSE_TIMEOUT_VALUE, 0U) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Disable the LSE oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this function.
  * @warning Access to backup domain must be enabled.
  * @retval HAL_OK      LSE oscillator has been configured successfully
  * @retval HAL_ERROR   Backup domain is not enabled\n
  *                     Timeout linked to LSE ready flag not reset\n
  *                     LSE propagation not disabled
  */
hal_status_t HAL_RCC_LSE_Disable(void)
{
  if (HAL_PWR_IsEnabledRTCDomainWriteProtection() != HAL_PWR_RTC_DOMAIN_WRP_DISABLED)
  {
    return HAL_ERROR;
  }

  LL_RCC_LSE_Disable();
  LL_RCC_LSE_DisableBypass();
  if (RCC_WaitForTimeout(LL_RCC_LSE_IsReady, RCC_LSE_TIMEOUT_VALUE, 0U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (LL_RCC_LSE_IsPropagationEnabled() != 0U)
  {
    /* Reset LSESYSEN once LSE is disabled */
    LL_RCC_LSE_DisablePropagation();
    if (RCC_WaitForTimeout(LL_RCC_LSE_IsPropagationReady, RCC_LSE_TIMEOUT_VALUE, 0U) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  /* Reset LSE drive to low value (default) */
  LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_LOW);

  LL_RCC_LSE_DisableGlitchFilter();

  return HAL_OK;
}

/**
  * @brief  Check if LSE is enabled.
  * @retval hal_rcc_osc_enable_status_t LSE enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_LSE_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_LSE_IsEnabled();
}

/**
  * @brief  Check if LSE is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       LSE is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   LSE can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_LSE_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_LSE_IsReady();
}

#endif /* LSE_VALUE */

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group1_2
  * @{
  */
/**
  * @brief  Set the CPU bus clock source (SYSCLK).
  * @param  source  System clock source based on @ref hal_rcc_sysclk_src_t
  * @note   SystemCoreClock and Systick are updated in this function.
  * @retval HAL_OK    Success\n
  * @retval HAL_ERROR System clock source has not been applied\n
  *                   Output PLL1R not enabled to switch to PLLCLK\n
  *                   Issue to reconfigure the System tick
  */
hal_status_t HAL_RCC_SetSYSCLKSource(hal_rcc_sysclk_src_t source)
{
  uint32_t tickstart;
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(IS_RCC_SYSCLKSOURCE(source));

  LL_RCC_SetSysClkSource((uint32_t)source);

  tickstart = HAL_GetTick();

  while (HAL_RCC_GetSYSCLKSource() != source)
  {
    if ((HAL_GetTick() - tickstart) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
    {
      status = HAL_ERROR;
      break;
    }
  }

  if (status == HAL_OK)
  {
    RCC_UPDATE_SYSTEMCORECLOCK();

    /* Configure the source of time base considering new system clocks settings*/
    status = HAL_InitTick(uwTickFreq, uwTickPrio);
  }

  return status;
}

/**
  * @brief   Get the system clock source (SYSCLK).
  * @retval  hal_rcc_sysclk_src_t System Clock source
  */
hal_rcc_sysclk_src_t HAL_RCC_GetSYSCLKSource(void)
{
  return (hal_rcc_sysclk_src_t)(uint32_t)((LL_RCC_GetSysClkSource() >> RCC_CFGR1_SWS_Pos) << RCC_CFGR1_SW_Pos);
}

/**
  * @brief  Set the AHB clock (HCLK) divider.
  * @param  prescaler  Prescaler value
  * @note   SystemCoreClock and Systick are updated in this function.
  * @retval HAL_OK     HCLK prescaler has been changed successfully
  * @retval HAL_ERROR  Issue to reconfigure the System tick
  */
hal_status_t HAL_RCC_SetHCLKPrescaler(hal_rcc_hclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_HCLK(prescaler));

  LL_RCC_SetAHBPrescaler((uint32_t)prescaler);

  RCC_UPDATE_SYSTEMCORECLOCK();

  /* Configure the source of time base considering new system clocks settings */
  return HAL_InitTick(uwTickFreq, uwTickPrio);
}

/**
  * @brief  Set the APB1 clock (PCLK1) divider
  * @param prescaler  Prescaler value
  */
void HAL_RCC_SetPCLK1Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB1Prescaler((uint32_t)prescaler);
}

/**
  * @brief  Set the APB2 clock (PCLK2) divider
  * @param prescaler  Prescaler value
  */
void HAL_RCC_SetPCLK2Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB2Prescaler(((uint32_t)prescaler) << 4U);
}

/**
  * @brief  Set the APB3 clock (PCLK3) divider
  * @param prescaler  Prescaler value
  */
void HAL_RCC_SetPCLK3Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB3Prescaler((uint32_t)prescaler);
}

#if defined(RCC_CFGR2_PPRE_DPHY)
/**
  * @brief  Set the DSI PHY prescaler (DPHY).
  * @param prescaler  Prescaler value
  */
void HAL_RCC_DSI_SetDPHYPrescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetDPHYPrescaler(((uint32_t)prescaler) << 8U);
}
#endif /* RCC_CFGR2_PPRE_DPHY */

/**
  * @brief  Get the AHB bus clock prescaler (HCLK).
  * @retval hal_rcc_hclk_prescaler_t Prescaler value
  */
hal_rcc_hclk_prescaler_t HAL_RCC_GetHCLKPrescaler(void)
{
  return (hal_rcc_hclk_prescaler_t)LL_RCC_GetAHBPrescaler();
}

/**
  * @brief  Set the APB1 bus clock prescaler (PCLK1).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK1Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)LL_RCC_GetAPB1Prescaler();
}

/**
  * @brief  Set the APB1 bus clock prescaler (PCLK2).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK2Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB2Prescaler() >> 4U);
}

/**
  * @brief  Set the APB1 bus clock prescaler (PCLK3).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK3Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)LL_RCC_GetAPB3Prescaler();
}

#if defined(RCC_CFGR2_PPRE_DPHY)
/**
  * @brief  Set the DSI PHY prescaler (DPHY).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_DSI_GetDPHYPrescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetDPHYPrescaler() >> 8U);
}
#endif /* RCC_CFGR2_PPRE_DPHY */

/**
  * @brief  Configure the bus dividers
  * @param  p_config Pointer based on @ref hal_rcc_bus_clk_config_t structure
  * @note   SystemCoreClock and Systick are updated in this function.
  * @warning FLASH latency must be adjusted according to the targeted system clock
  *          frequency and voltage scaling.
  * @retval HAL_OK            Success
  * @retval HAL_ERROR         Issue to reconfigure the System tick
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  */
hal_status_t HAL_RCC_SetBusClockConfig(const hal_rcc_bus_clk_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_HCLK(p_config->hclk_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk1_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk2_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk3_prescaler));

  /* Configure prescalers for the available Bus */
  LL_RCC_ConfigBusClock((uint32_t)p_config->hclk_prescaler  |
                        (uint32_t)p_config->pclk1_prescaler |
                        (uint32_t)((uint32_t)p_config->pclk2_prescaler << 4UL),
                        (uint32_t)p_config->pclk3_prescaler);

  RCC_UPDATE_SYSTEMCORECLOCK();

  /* Configure the source of time base considering new system clocks settings*/
  return HAL_InitTick(uwTickFreq, uwTickPrio);
}

/**
  * @brief Retrieve the bus dividers
  * @param p_config Pointer on @ref hal_rcc_bus_clk_config_t structure
  */
void HAL_RCC_GetBusClockConfig(hal_rcc_bus_clk_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  /* Get Bus prescalers */
  p_config->hclk_prescaler = (hal_rcc_hclk_prescaler_t)LL_RCC_GetAHBPrescaler();
  p_config->pclk1_prescaler = (hal_rcc_pclk_prescaler_t)LL_RCC_GetAPB1Prescaler();
  p_config->pclk2_prescaler = (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB2Prescaler() >> 4);
  p_config->pclk3_prescaler = (hal_rcc_pclk_prescaler_t)LL_RCC_GetAPB3Prescaler();
}

/**
  * @brief  Return the SYSCLK frequency.
  * @note   The system frequency computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source.
  * @note   If SYSCLK source is MSI, function returns values based on MSI
  *           Value as defined by the MSI range (***).
  * @note   If SYSCLK source is HSI, function returns values based on HSI_VALUE(*).
  * @note   If SYSCLK source is HSE, function returns values based on HSE_VALUE(**).
  * @note   If SYSCLK source is PLL, function returns values based on HSE_VALUE(**),
  *         HSI_VALUE(*) or MSI Value multiplied/divided by the PLL factors.
  * @note   This function can be used by the user application to compute the
  *         baudrate for the communication peripherals or configure other parameters.
  * @warning Each time SYSCLK changes, this function must be called to update the
  *          right SYSCLK value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t SYSCLK frequency in Hz
  */
uint32_t HAL_RCC_GetSYSCLKFreq(void)
{
  uint32_t sysclockfreq;
  uint32_t sysclk_source;
  uint8_t  msi_sel;

  sysclk_source = LL_RCC_GetSysClkSource();

  if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_MSIS)
  {
    /* MSI used as system clock source */
    msi_sel = ((LL_RCC_MSI_IsEnabledRangeSelect() == 0U) ? LL_RCC_MSIRANGESEL_STANDBY : LL_RCC_MSIRANGESEL_RUN);
    sysclockfreq = LL_RCC_CALC_MSIS_FREQ(msi_sel,
                                         ((msi_sel == LL_RCC_MSIRANGESEL_RUN) ?
                                          LL_RCC_MSIS_GetRange() :
                                          LL_RCC_MSIS_GetRangeAfterStandby()));
  }
  else if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
    /* HSI used as system clock source */
    sysclockfreq = HSI_VALUE;
  }
#if defined(HSE_VALUE)
  else if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSE)
  {
    /* HSE used as system clock source */
    sysclockfreq = HSE_VALUE;
  }
#endif /* HSE_VALUE */
  else
  {
    float_t pll_r;
    float_t pll_m;
    float_t pll_n;
    uint32_t pllfracen;
    uint32_t pll_oscsource;
    float_t fracn;
    float_t pllvco;
    /* PLL used as system clock  source
     *  PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_RANGE_VALUE / PLL1M) * (PLL1N + (PLL1FRACN /0x2000) + 1)
     *  SYSCLK = PLL_VCO / PLL1R
     */
    pll_oscsource = LL_RCC_PLL1_GetMainSource();
    pll_m = (float_t)LL_RCC_PLL1_GetDivider();
    pll_n = (float_t)LL_RCC_PLL1_GetN();
    pllfracen = LL_RCC_PLL1FRACN_IsEnabled();
    fracn = (float_t)(uint32_t)(pllfracen * LL_RCC_PLL1_GetFRACN());

    switch (pll_oscsource)
    {
      case HAL_RCC_PLL_SRC_HSI:  /* HSI used as PLL clock source */
        pllvco = (float_t)HSI_VALUE;
        break;

#if defined(HSE_VALUE)
      case HAL_RCC_PLL_SRC_HSE:  /* HSE used as PLL clock source */
        pllvco = (float_t)HSE_VALUE;
        break;
#endif /* HSE_VALUE */

      case HAL_RCC_PLL_SRC_MSIS:  /* MSI used as PLL clock source */
      default:
        msi_sel = ((LL_RCC_MSI_IsEnabledRangeSelect() == 0U) ? LL_RCC_MSIRANGESEL_STANDBY : LL_RCC_MSIRANGESEL_RUN);
        pllvco = (float_t)LL_RCC_CALC_MSIS_FREQ(msi_sel,
                                                ((msi_sel == LL_RCC_MSIRANGESEL_RUN) ?
                                                 LL_RCC_MSIS_GetRange() :
                                                 LL_RCC_MSIS_GetRangeAfterStandby()));
        break;
    }

    pll_r = (float_t)LL_RCC_PLL1_GetR();
    pll_n = (pll_n + (fracn / (float_t)0x2000));
    sysclockfreq = (uint32_t)(float_t)LL_RCC_CALC_PLL1CLK_FREQ(pllvco, pll_m, pll_n, pll_r);
  }

  return sysclockfreq;
}

/**
  * @brief  Return the HCLK frequency.
  * @warning Each time HCLK changes, this function must be called to update the
  *          right HCLK value. Otherwise, any configuration based on this function will be incorrect.
  * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency.
  * @retval uint32_t HCLK frequency in Hz
  */
uint32_t HAL_RCC_GetHCLKFreq(void)
{
  RCC_UPDATE_SYSTEMCORECLOCK();
  return SystemCoreClock;
}

/**
  * @brief  Return the PCLK1 frequency.
  * @warning Each time PCLK1 changes, this function must be called to update the
  *          right PCLK1 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t PCLK1 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK1Freq(void)
{
  /* Get HCLK source and Compute PCLK1 frequency */
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB1Prescaler() >> RCC_CFGR2_PPRE1_Pos]);
}

/**
  * @brief  Return the PCLK2 frequency.
  * @warning Each time PCLK2 changes, this function must be called to update the
  *          right PCLK2 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t PCLK2 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK2Freq(void)
{
  /* Get HCLK source and Compute PCLK2 frequency */
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB2Prescaler() >> RCC_CFGR2_PPRE2_Pos]);
}

/**
  * @brief  Return the PCLK3 frequency.
  * @warning Each time PCLK3 changes, this function must be called to update the
  *          right PCLK3 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t PCLK3 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK3Freq(void)
{
  /* Get HCLK source and Compute PCLK2 frequency */
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB3Prescaler() >> RCC_CFGR3_PPRE3_Pos]);
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group1_3
  * @{
  */

/**
  * @brief   Configure PLL1 without enabling outputs.
  * @details The config function will perform the following actions:
  *           - Check in PLL1 is well deactivated (if enabled exit from this function)
  *           - Configure the PLL1 with full list of parameters
  * @param p_config pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL1
  * @retval HAL_OK            PLL1 has been correctly configured\n
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  * @retval HAL_ERROR         PLL1 is already enabled and can not be modified.
  */
hal_status_t HAL_RCC_PLL1_SetConfig(const hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_PLLSOURCE(p_config->pll_source));
  ASSERT_DBG_PARAM(IS_RCC_PLLM_VALUE(p_config->pll_m));
  ASSERT_DBG_PARAM(IS_RCC_PLLN_VALUE(p_config->pll_n));
  ASSERT_DBG_PARAM(IS_RCC_PLLP_VALUE(p_config->pll_p));
  ASSERT_DBG_PARAM(IS_RCC_PLLQ_VALUE(p_config->pll_q));
  ASSERT_DBG_PARAM(IS_RCC_PLLR_VALUE(p_config->pll_r));
  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(p_config->pll_fracn));
  ASSERT_DBG_PARAM(IS_RCC_PLLMBOOST_VALUE(p_config->pll_m_boost));

  return RCC_PLL_SetConfig(PLL_1, p_config);
}

/**
  * @brief Enable output(s) of PLL1.
  * @param output Output to enable for PLL1
  *               It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_P
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_Q
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_R or @ref HAL_RCC_PLL1_SYSCLK
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been activated
  */
hal_status_t HAL_RCC_PLL1_EnableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL1_OUTPUT(output));

  LL_RCC_PLL1_EnableOutput(output);

  return HAL_OK;
}

/**
  * @brief  Disable output(s) of PLL1.
  * @param  output Output to disable for PLL1
  *                It can be a combination of the following values:
  *                   @arg @ref HAL_RCC_PLL1_OUTPUT_P
  *                   @arg @ref HAL_RCC_PLL1_OUTPUT_Q
  *                   @arg @ref HAL_RCC_PLL1_OUTPUT_R or @ref HAL_RCC_PLL1_SYSCLK
  *                   @arg @ref HAL_RCC_PLL1_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been deactivated
  * @retval HAL_ERROR Output is used as system clock and cannot be deactivated
  */
hal_status_t HAL_RCC_PLL1_DisableOutput(uint32_t output)
{
  hal_rcc_sysclk_src_t src_clk;
  hal_status_t status = HAL_ERROR;
  ASSERT_DBG_PARAM(IS_RCC_PLL1_OUTPUT(output));
  /*
    - If output is used as system clock => return an error
    - else disable output(s) of the PLL1
  */
  src_clk = HAL_RCC_GetSYSCLKSource();
  if ((src_clk != HAL_RCC_SYSCLK_SRC_PLLCLK)
      || ((src_clk == HAL_RCC_SYSCLK_SRC_PLLCLK)
          && ((output & HAL_RCC_PLL1_OUTPUT_R) != HAL_RCC_PLL1_OUTPUT_R)))
  {
    LL_RCC_PLL1_DisableOutput(output);
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Enable PLL1.
  * @note   If PLL is not enabled, enable it and wait for RDY state.
  * @retval HAL_OK    PLL1 correctly enabled or already enabled.
  * @retval HAL_ERROR Timeout detected during enabling of the PLL1
  */
hal_status_t HAL_RCC_PLL1_Enable(void)
{
  hal_status_t status = HAL_OK;
  /*
    - If PLL not enabled => enable it and wait for RDY state (error only if pb to enable)
  */
  if (LL_RCC_PLL1_IsReady() == 0U)
  {
    LL_RCC_PLL1_Enable();
    status = RCC_WaitForTimeout(LL_RCC_PLL1_IsReady, RCC_PLL1_TIMEOUT_VALUE, 1U);
  }

  return status;
}

/**
  * @brief   Disable PLL1.
  * @details PLL1 cannot be disabled if used as system level
  *           - If PLL1 Output is as used as system level => return an error
  *           - If PLL1 enabled => disable PLL1 and wait for deactivation (error only if pb to disable)
  * @retval HAL_OK    PLL1 correctly deactivated or already deactivated.
  * @retval HAL_ERROR PLL1 is used as system level and cannot be deactivated\n
  *                   Timeout detected during disabling of the PLL1
  */
hal_status_t HAL_RCC_PLL1_Disable(void)
{
  hal_status_t status = HAL_ERROR;
  /*
    - If PLL1 is as used as system level => return an error
    - Else disable PLL1 and wait for deactivation (error only if pb to disable)
  */
  if (HAL_RCC_GetSYSCLKSource() != HAL_RCC_SYSCLK_SRC_PLLCLK)
  {
    LL_RCC_PLL1_Disable();
    status = RCC_WaitForTimeout(LL_RCC_PLL1_IsReady, RCC_PLL1_TIMEOUT_VALUE, 0U);
  }
  return status;
}

/**
  * @brief    Disable PLL1 for power consumption perspective.
  * @warning  To enable again PLL1, a new configuration must be applied.
  * @details  This function allow to reset all the parameters which might impact power
  *           like PLLSRC, outputs...
  * @retval HAL_OK    PLL1 is correctly disabled\n
  * @retval HAL_ERROR Output is used as system level and cannot be disabled\n
  *                   Timeout to disable PLL1
  */
hal_status_t HAL_RCC_PLL1_Reset(void)
{
  hal_status_t status = HAL_ERROR;

  if (HAL_RCC_GetSYSCLKSource() != HAL_RCC_SYSCLK_SRC_PLLCLK)
  {
    LL_RCC_PLL1_Disable();
    if (RCC_WaitForTimeout(LL_RCC_PLL1_IsReady, RCC_PLL1_TIMEOUT_VALUE, 0U) == HAL_OK)
    {
      /* To save power disable the PLL1 Source, FRACN and Clock outputs */
      CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1PEN | RCC_PLL1CFGR_PLL1QEN | RCC_PLL1CFGR_PLL1REN
                | RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1FRACEN);
      status = HAL_OK;
    }
  }
  return status;
}

/**
  * @brief Return the configuration of PLL1.
  * @param p_config  pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL1
  */
void HAL_RCC_PLL1_GetConfig(hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  RCC_PLL_GetConfig(PLL_1, p_config);
}

/**
  * @brief  Return the enabled output(s) of PLL1.
  * @retval output PLL1 outputs.
  *         It can be a combination of the following values:
  *            @arg @ref HAL_RCC_PLL1_OUTPUT_P
  *            @arg @ref HAL_RCC_PLL1_OUTPUT_Q
  *            @arg @ref HAL_RCC_PLL1_OUTPUT_R or @ref HAL_RCC_PLL1_SYSCLK
  */
uint32_t HAL_RCC_PLL1_GetOutput(void)
{
  return LL_RCC_PLL1_GetOutput();
}

/**
  * @brief Check if the PLL1 is ready.
  * @retval HAL_RCC_PLL_ENABLED  PLL1 is ready
  * @retval HAL_RCC_PLL_DISABLED PLL1 is not ready
  */
hal_rcc_pll_status_t HAL_RCC_PLL1_IsReady(void)
{
  return (hal_rcc_pll_status_t)LL_RCC_PLL1_IsReady();
}

/**
  * @brief  Returns the PLL1 clock frequencies: pll_p_freq, pll_q_freq and pll_r_freq
  * @param  p_clk Contains the frequency for each PLL1 output (in Hz).
  * @note   The PLL1 clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source.
  * @note   The function returns values based on HSE_VALUE, HSI_VALUE or MSI Value multiplied/divided by the PLL
  *         factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @warning Each time PLL1CLK changes, this function must be called to update the
  *          right PLL1CLK value. Otherwise, any configuration based on this function will be incorrect.
  */
void HAL_RCC_PLL1_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk)
{
  uint32_t pll_source;
  uint32_t pll_m;
  uint32_t pll_n;
  uint32_t pll_fracen;
  uint32_t pll_cfgr;
  uint32_t pll_divr;
  float_t fracn;
  float_t pll_vco;

  ASSERT_DBG_PARAM(p_clk != (void *)NULL);

  p_clk->pll_p_freq = 0U;
  p_clk->pll_q_freq = 0U;
  p_clk->pll_r_freq = 0U;

  /* If PLL1 is not ready, return directly all the outputs frequencies set at 0 */
  if (LL_RCC_PLL1_IsReady() == 0U)
  {
    return;
  }

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLL1M) * PLL1N
     PLL1xCLK = PLL1_VCO / PLL1x */
  pll_cfgr = LL_RCC_READ_REG(PLL1CFGR);
  pll_source = READ_BIT(pll_cfgr, RCC_PLL1CFGR_PLL1SRC);
  pll_m = (READ_BIT(pll_cfgr, RCC_PLL1CFGR_PLL1M) >> RCC_PLL1CFGR_PLL1M_Pos) + 1U;
  pll_fracen = READ_BIT(pll_cfgr, RCC_PLL1CFGR_PLL1FRACEN) >> RCC_PLL1CFGR_PLL1FRACEN_Pos;
  pll_divr = LL_RCC_READ_REG(PLL1DIVR);
  pll_n = READ_BIT(pll_divr, RCC_PLL1DIVR_PLL1N) + 1U;
  fracn = (float_t)(uint32_t)(pll_fracen * LL_RCC_PLL1_GetFRACN());

  switch (pll_source)
  {
    case HAL_RCC_PLL_SRC_HSI:  /* HSI used as PLL clock source */
      pll_vco = ((float_t)HSI_VALUE
                 / (float_t)pll_m) * ((float_t)pll_n + (fracn / (float_t)0x2000));
      break;
    case HAL_RCC_PLL_SRC_MSIS:  /* MSI used as PLL clock source */
      pll_vco = ((float_t)RCC_GET_MSIS_FREQUENCY()
                 / (float_t)pll_m) * ((float_t)pll_n + (fracn / (float_t)0x2000));
      break;
#if defined(HSE_VALUE)
    case HAL_RCC_PLL_SRC_HSE:  /* HSE used as PLL clock source */
      pll_vco = ((float_t)HSE_VALUE
                 / (float_t)pll_m) * ((float_t)pll_n + (fracn / (float_t)0x2000));
      break;
#endif /* HSE_VALUE */
    default:
      pll_vco = (float_t)0;
      break;
  }

  if (IS_BIT_SET(pll_cfgr, LL_RCC_PLL1_OUTPUT_P))
  {
    p_clk->pll_p_freq = (uint32_t)(float_t)(pll_vco /
                                            ((float_t)(uint32_t)(READ_BIT(pll_divr, RCC_PLL1DIVR_PLL1P)
                                                                 >> RCC_PLL1DIVR_PLL1P_Pos) + (float_t)1));
  }

  if (IS_BIT_SET(pll_cfgr, LL_RCC_PLL1_OUTPUT_Q))
  {
    p_clk->pll_q_freq = (uint32_t)(float_t)(pll_vco /
                                            ((float_t)(uint32_t)(READ_BIT(pll_divr, RCC_PLL1DIVR_PLL1Q)
                                                                 >> RCC_PLL1DIVR_PLL1Q_Pos) + (float_t)1));
  }

  if (IS_BIT_SET(pll_cfgr, LL_RCC_PLL1_OUTPUT_R))
  {
    p_clk->pll_r_freq = (uint32_t)(float_t)(pll_vco /
                                            ((float_t)(uint32_t)(READ_BIT(pll_divr, RCC_PLL1DIVR_PLL1R)
                                                                 >> RCC_PLL1DIVR_PLL1R_Pos) + (float_t)1));
  }
}

/**
  * @brief  Set the fractional part (FRACN) of the multiplication factor of PLL1 on-the-fly.
  * @param  fracn The new fractional value to be set for PLL1.
  * @retval HAL_OK     The FRACN value has been correctly set.
  * @retval HAL_ERROR  The FRACN value update has failed.
  */
hal_status_t HAL_RCC_PLL1_SetFRACN(uint16_t fracn)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(fracn));

  /* FRACN1 on-the-fly value update */
  if (LL_RCC_PLL1_GetFRACN() != fracn)
  {
    LL_RCC_PLL1FRACN_Disable();

    tickstart = HAL_GetTick();
    /* Wait at least 2 CK_REF (PLL1 input source divided by M) period to make sure next latched value will be taken
      into account. */
    while ((HAL_GetTick() - tickstart) < RCC_PLL_FRAC_WAIT_VALUE)
    {
    }

    LL_RCC_PLL1_SetFRACN(fracn);

    /* Enable PLL1FRACN to latch the new value. */
    LL_RCC_PLL1FRACN_Enable();
  }

  return HAL_OK;
}

/**
  * @brief  Get the current fractional part (FRACN) of the multiplication factor of PLL1.
  * @retval The current fractional value of PLL1.
  */
uint16_t HAL_RCC_PLL1_GetFRACN(void)
{
  return (uint16_t)LL_RCC_PLL1_GetFRACN();
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group1_4
  * @{
  */

/**
  * @brief   Configure PLL2 without enabling outputs.
  * @details The config function will perform the following actions:
  *           - Check in PLL2 is well deactivated (if enabled exit from this function)
  *           - Configure the PLL2 with full list of parameters
  * @param  p_config pointer to a @ref hal_rcc_pll_config_t structure that
  *                  contains the configuration information for the PLL2
  * @retval HAL_OK    PLL2 has been correctly configured
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  * @retval HAL_ERROR PLL2 is already enabled and can not be modified.
  */
hal_status_t HAL_RCC_PLL2_SetConfig(const hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_PLLSOURCE(p_config->pll_source));
  ASSERT_DBG_PARAM(IS_RCC_PLLM_VALUE(p_config->pll_m));
  ASSERT_DBG_PARAM(IS_RCC_PLLN_VALUE(p_config->pll_n));
  ASSERT_DBG_PARAM(IS_RCC_PLLP_VALUE(p_config->pll_p));
  ASSERT_DBG_PARAM(IS_RCC_PLLQ_VALUE(p_config->pll_q));
  ASSERT_DBG_PARAM(IS_RCC_PLLR_VALUE(p_config->pll_r));
  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(p_config->pll_fracn));

  return RCC_PLL_SetConfig(PLL_2, p_config);
}

/**
  * @brief  Enable PLL2.
  * @note   If PLL2 is not enabled, enable it and wait for RDY state.
  * @retval HAL_OK    PLL2 correctly enabled or already enabled.
  * @retval HAL_ERROR Timeout detected during enabling of the PLL2
  */
hal_status_t HAL_RCC_PLL2_Enable(void)
{
  hal_status_t status = HAL_OK;
  /* If PLL1 not enabled => enable it and wait for RDY state (error only if pb to enable) */
  if (LL_RCC_PLL2_IsReady() == 0U)
  {
    LL_RCC_PLL2_Enable();
    status = RCC_WaitForTimeout(LL_RCC_PLL2_IsReady, RCC_PLL2_TIMEOUT_VALUE, 1U);
  }

  return status;
}

/**
  * @brief  Disable PLL2.
  * @retval HAL_OK    PLL2 correctly deactivated or PLL2 was already disabled.
  * @retval HAL_ERROR Timeout detected during disabling of the PLL2
  */
hal_status_t HAL_RCC_PLL2_Disable(void)
{
  LL_RCC_PLL2_Disable();

  return RCC_WaitForTimeout(LL_RCC_PLL2_IsReady, RCC_PLL2_TIMEOUT_VALUE, 0U);
}

/**
  * @brief Enable output(s) of PLL2.
  * @param output Output to enable for PLL2.
  *               It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_P
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_Q
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_R
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been activated
  */
hal_status_t HAL_RCC_PLL2_EnableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL2_OUTPUT(output));

  LL_RCC_PLL2_EnableOutput(output);

  return HAL_OK;
}

/**
  * @brief  Disable output(s) of PLL2.
  * @param  output Output to disable for PLL2.
  *                It can be a combination of the following values:
  *                   @arg @ref HAL_RCC_PLL2_OUTPUT_P
  *                   @arg @ref HAL_RCC_PLL2_OUTPUT_Q
  *                   @arg @ref HAL_RCC_PLL2_OUTPUT_R
  *                   @arg @ref HAL_RCC_PLL2_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been deactivated
  */
hal_status_t HAL_RCC_PLL2_DisableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL2_OUTPUT(output));

  LL_RCC_PLL2_DisableOutput(output);

  return HAL_OK;
}

/**
  * @brief Return the configuration of PLL2.
  * @param p_config  pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL2
  */
void HAL_RCC_PLL2_GetConfig(hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  RCC_PLL_GetConfig(PLL_2, p_config);
}

/**
  * @brief  Return the enabled output(s) of PLL2.
  * @retval output PLL2 outputs.
  *                It can be a combination of the following values:
  *                   @arg @ref HAL_RCC_PLL2_OUTPUT_P
  *                   @arg @ref HAL_RCC_PLL2_OUTPUT_Q
  *                   @arg @ref HAL_RCC_PLL2_OUTPUT_R
  */
uint32_t HAL_RCC_PLL2_GetOutput(void)
{
  return LL_RCC_PLL2_GetOutput();
}

/**
  * @brief Check if the PLL2 is ready.
  * @retval HAL_RCC_PLL_ENABLED   PLL2 is ready
  * @retval HAL_RCC_PLL_DISABLED PLL2 is not ready
  */
hal_rcc_pll_status_t HAL_RCC_PLL2_IsReady(void)
{
  return (hal_rcc_pll_status_t)LL_RCC_PLL2_IsReady();
}

/**
  * @brief  Returns the PLL2 clock frequencies: pll_p_freq, pll_r_freq and pll_q_freq
  * @param  p_clk Contains the frequency for each PLL2 output (in Hz).
  * @note   The PLL2 clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source.
  * @note   The function returns values based on HSE_VALUE, HSI_VALUE or MSI Value multiplied/divided by the PLL
  *         factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @warning Each time PLL2CLK changes, this function must be called to update the
  *          right PLL2CLK value. Otherwise, any configuration based on this function will be incorrect.
  */
void HAL_RCC_PLL2_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk)
{
  uint32_t pll_source;
  uint32_t pll_m;
  uint32_t pll_n;
  uint32_t pll_fracen;
  uint32_t pll_divr;
  uint32_t pll_cfgr;
  float_t fracn;
  float_t pll_vco;

  ASSERT_DBG_PARAM(p_clk != (void *)NULL);

  p_clk->pll_p_freq = 0U;
  p_clk->pll_q_freq = 0U;
  p_clk->pll_r_freq = 0U;

  /* If PLL2 is not ready, return directly all the outputs frequencies set at 0 */
  if (LL_RCC_PLL2_IsReady() == 0U)
  {
    return;
  }

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLL2M) * PLL2N
     PLL2xCLK = PLL2_VCO / PLL2x */
  pll_cfgr = LL_RCC_READ_REG(PLL2CFGR);
  pll_source = READ_BIT(pll_cfgr, RCC_PLL2CFGR_PLL2SRC);
  pll_m = (READ_BIT(pll_cfgr, RCC_PLL2CFGR_PLL2M) >> RCC_PLL2CFGR_PLL2M_Pos) + 1U;
  pll_fracen = READ_BIT(pll_cfgr, RCC_PLL2CFGR_PLL2FRACEN) >> RCC_PLL2CFGR_PLL2FRACEN_Pos;
  pll_divr = LL_RCC_READ_REG(PLL2DIVR);
  pll_n = READ_BIT(pll_divr, RCC_PLL2DIVR_PLL2N) + 1U;
  fracn = (float_t)(uint32_t)(pll_fracen * LL_RCC_PLL2_GetFRACN());

  switch (pll_source)
  {
    case HAL_RCC_PLL_SRC_HSI:  /* HSI used as PLL clock source */
      pll_vco = ((float_t)HSI_VALUE
                 / (float_t)pll_m) * ((float_t)pll_n + (fracn / (float_t)0x2000));
      break;
    case HAL_RCC_PLL_SRC_MSIS:  /* MSI used as PLL clock source */
      pll_vco = ((float_t)RCC_GET_MSIS_FREQUENCY()
                 / (float_t)pll_m) * ((float_t)pll_n + (fracn / (float_t)0x2000));
      break;
#if defined(HSE_VALUE)
    case HAL_RCC_PLL_SRC_HSE:  /* HSE used as PLL clock source */
      pll_vco = ((float_t)HSE_VALUE
                 / (float_t)pll_m) * ((float_t)pll_n + (fracn / (float_t)0x2000));
      break;
#endif /* HSE_VALUE */
    default:
      pll_vco = (float_t)0;
      break;
  }

  if (IS_BIT_SET(pll_cfgr, LL_RCC_PLL2_OUTPUT_P))
  {
    p_clk->pll_p_freq = (uint32_t)(float_t)(pll_vco /
                                            ((float_t)(uint32_t)(READ_BIT(pll_divr, RCC_PLL2DIVR_PLL2P)
                                                                 >> RCC_PLL2DIVR_PLL2P_Pos) + (float_t)1));
  }

  if (IS_BIT_SET(pll_cfgr, LL_RCC_PLL2_OUTPUT_Q))
  {
    p_clk->pll_q_freq = (uint32_t)(float_t)(pll_vco /
                                            ((float_t)(uint32_t)(READ_BIT(pll_divr, RCC_PLL2DIVR_PLL2Q)
                                                                 >> RCC_PLL2DIVR_PLL2Q_Pos) + (float_t)1));
  }

  if (IS_BIT_SET(pll_cfgr, LL_RCC_PLL2_OUTPUT_R))
  {
    p_clk->pll_r_freq = (uint32_t)(float_t)(pll_vco /
                                            ((float_t)(uint32_t)(READ_BIT(pll_divr, RCC_PLL2DIVR_PLL2R)
                                                                 >> RCC_PLL2DIVR_PLL2R_Pos) + (float_t)1));
  }
}

/**
  * @brief  Set the fractional part (FRACN) of the multiplication factor of PLL2 on-the-fly.
  * @param  fracn The new fractional value to be set for PLL2.
  * @retval HAL_OK     The FRACN value has been correctly set.
  * @retval HAL_ERROR  The FRACN value update has failed.
  */
hal_status_t HAL_RCC_PLL2_SetFRACN(uint16_t fracn)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(fracn));

  /* FRACN on-the-fly value update */
  if (LL_RCC_PLL2_GetFRACN() != fracn)
  {
    LL_RCC_PLL2FRACN_Disable();

    tickstart = HAL_GetTick();
    /* Wait at least 2 CK_REF (PLL2 input source divided by M) period to make sure next latched value will be taken
      into account. */
    while ((HAL_GetTick() - tickstart) < RCC_PLL_FRAC_WAIT_VALUE)
    {
    }

    LL_RCC_PLL2_SetFRACN(fracn);

    /* Enable PLL2FRACN to latch the new value. */
    LL_RCC_PLL2FRACN_Enable();
  }

  return HAL_OK;
}

/**
  * @brief  Get the current fractional part (FRACN) of the multiplication factor of PLL2.
  * @retval The current fractional value of PLL2.
  */
uint16_t HAL_RCC_PLL2_GetFRACN(void)
{
  return (uint16_t)LL_RCC_PLL2_GetFRACN();
}

/**
  * @brief    Disable PLL2 for power consumption perspective.
  * @warning  To enable again PLL2, a new configuration must be applied.
  * @details  This function allow to reset all the parameters which might impact power like PLLSRC, outputs...
  * @retval   HAL_OK    PLL2 is correctly disabled
  * @retval   HAL_ERROR PLL2 not disabled
  */
hal_status_t HAL_RCC_PLL2_Reset(void)
{
  hal_status_t status = HAL_ERROR;

  LL_RCC_PLL2_Disable();
  if (RCC_WaitForTimeout(LL_RCC_PLL2_IsReady, RCC_PLL2_TIMEOUT_VALUE, 0U) == HAL_OK)
  {
    /* To save power disable the PLL2 Source, FRACN and Clock outputs */
    CLEAR_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2PEN | RCC_PLL2CFGR_PLL2QEN | RCC_PLL2CFGR_PLL2REN |
              RCC_PLL2CFGR_PLL2SRC | RCC_PLL2CFGR_PLL2FRACEN);
    status = HAL_OK;
  }

  return status;
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group1_5
  * @{
  */

/**
  * @brief   Configure PLL3 without enabling outputs.
  * @details The config function will perform the following actions:
  *           - Check in PLL3 is well deactivated (if enabled exit from this function)
  *           - Configure the PLL3 with full list of parameters
  * @param p_config pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL3
  * @retval HAL_OK    PLL3 has been correctly configured
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  * @retval HAL_ERROR PLL3 is already enabled and can not be modified.
  */
hal_status_t HAL_RCC_PLL3_SetConfig(const hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_PLLSOURCE(p_config->pll_source));
  ASSERT_DBG_PARAM(IS_RCC_PLLM_VALUE(p_config->pll_m));
  ASSERT_DBG_PARAM(IS_RCC_PLLN_VALUE(p_config->pll_n));
  ASSERT_DBG_PARAM(IS_RCC_PLLP_VALUE(p_config->pll_p));
  ASSERT_DBG_PARAM(IS_RCC_PLLQ_VALUE(p_config->pll_q));
  ASSERT_DBG_PARAM(IS_RCC_PLLR_VALUE(p_config->pll_r));
  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(p_config->pll_fracn));

  return RCC_PLL_SetConfig(PLL_3, p_config);
}

/**
  * @brief  Enable PLL3.
  * @note   If PLL is not enabled, enable it and wait for RDY state.
  * @retval HAL_OK    PLL3 correctly enabled or already enabled.
  * @retval HAL_ERROR Timeout detected during enabling of the PLL3
  */
hal_status_t HAL_RCC_PLL3_Enable(void)
{
  hal_status_t status = HAL_OK;
  /*
    - If PLL3 not enabled => enable it and wait for RDY state (error only if pb to enable)
  */
  if (LL_RCC_PLL3_IsReady() == 0U)
  {
    LL_RCC_PLL3_Enable();
    status = RCC_WaitForTimeout(LL_RCC_PLL3_IsReady, RCC_PLL3_TIMEOUT_VALUE, 1U);
  }
  return status;
}

/**
  * @brief  Disable PLL3.
  * @retval HAL_OK    PLL3 correctly deactivated or PLL3 was already disabled.
  * @retval HAL_ERROR Timeout detected during disabling of the PLL3
  */
hal_status_t HAL_RCC_PLL3_Disable(void)
{
  LL_RCC_PLL3_Disable();

  return RCC_WaitForTimeout(LL_RCC_PLL3_IsReady, RCC_PLL3_TIMEOUT_VALUE, 0U);
}

/**
  * @brief Enable output(s) of PLL3.
  * @param output Output to enable for PLL3.
  *               It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_P
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_Q
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_R
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been activated
  */
hal_status_t HAL_RCC_PLL3_EnableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL3_OUTPUT(output));

  LL_RCC_PLL3_EnableOutput(output);

  return HAL_OK;
}

/**
  * @brief  Disable output(s) of PLL3.
  * @param  output Output to disable for PLL3.
  *                It can be a combination of the following values:
  *                   @arg @ref HAL_RCC_PLL3_OUTPUT_P
  *                   @arg @ref HAL_RCC_PLL3_OUTPUT_Q
  *                   @arg @ref HAL_RCC_PLL3_OUTPUT_R
  *                   @arg @ref HAL_RCC_PLL3_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been deactivated
  */
hal_status_t HAL_RCC_PLL3_DisableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL3_OUTPUT(output));

  LL_RCC_PLL3_DisableOutput(output);

  return HAL_OK;
}

/**
  * @brief Return the configuration of PLL3.
  * @param p_config  pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL3
  */
void HAL_RCC_PLL3_GetConfig(hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  RCC_PLL_GetConfig(PLL_3, p_config);
}

/**
  * @brief  Return the enabled output(s) of PLL3.
  * @retval output PLL3 outputs.
  *                It can be a combination of the following values:
  *                   @arg @ref HAL_RCC_PLL3_OUTPUT_P
  *                   @arg @ref HAL_RCC_PLL3_OUTPUT_Q
  *                   @arg @ref HAL_RCC_PLL3_OUTPUT_R
  */
uint32_t HAL_RCC_PLL3_GetOutput(void)
{
  return LL_RCC_PLL3_GetOutput();
}

/**
  * @brief Check if the PLL3 is ready.
  * @retval HAL_RCC_PLL_ENABLED  PLL3 is ready
  * @retval HAL_RCC_PLL_DISABLED PLL3 is not ready
  */
hal_rcc_pll_status_t HAL_RCC_PLL3_IsReady(void)
{
  return (hal_rcc_pll_status_t)LL_RCC_PLL3_IsReady();
}

/**
  * @brief  Returns the PLL3 clock frequencies: pll_p_freq, pll_r_freq and pll_q_freq
  * @param  p_clk Contains the frequency for each PLL3 output (in Hz).
  * @note   The PLL3 clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source.
  * @note   The function returns values based on HSE_VALUE, HSI_VALUE or MSI Value multiplied/divided by the PLL
  *         factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @warning Each time PLL3CLK changes, this function must be called to update the
  *          right PLL3CLK value. Otherwise, any configuration based on this function will be incorrect.
  */
void HAL_RCC_PLL3_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk)
{
  uint32_t pll_source;
  uint32_t pll_m;
  uint32_t pll_n;
  uint32_t pll_fracen;
  uint32_t pll_cfgr;
  uint32_t pll_divr;
  float_t fracn;
  float_t pll_vco;

  ASSERT_DBG_PARAM(p_clk != (void *)NULL);

  p_clk->pll_p_freq = 0U;
  p_clk->pll_q_freq = 0U;
  p_clk->pll_r_freq = 0U;

  /* If PLL3 is not ready, return directly all the outputs frequencies set at 0 */
  if (LL_RCC_PLL3_IsReady() == 0U)
  {
    return;
  }

  /* PLL3_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLL3M) * PLL3N
     PLL3xCLK = PLL3_VCO / PLLxR */
  pll_cfgr = LL_RCC_READ_REG(PLL3CFGR);
  pll_source = READ_BIT(pll_cfgr, RCC_PLL3CFGR_PLL3SRC);
  pll_m = (READ_BIT(pll_cfgr, RCC_PLL3CFGR_PLL3M) >> RCC_PLL3CFGR_PLL3M_Pos) + 1U;
  pll_fracen = READ_BIT(pll_cfgr, RCC_PLL3CFGR_PLL3FRACEN) >> RCC_PLL3CFGR_PLL3FRACEN_Pos;
  pll_divr = LL_RCC_READ_REG(PLL3DIVR);
  pll_n = READ_BIT(pll_divr, RCC_PLL3DIVR_PLL3N) + 1U;
  fracn = (float_t)(uint32_t)(pll_fracen * LL_RCC_PLL3_GetFRACN());

  switch (pll_source)
  {
    case HAL_RCC_PLL_SRC_HSI:  /* HSI used as PLL clock source */
      pll_vco = ((float_t)HSI_VALUE
                 / (float_t)pll_m) * ((float_t)pll_n + (fracn / (float_t)0x2000));
      break;
    case HAL_RCC_PLL_SRC_MSIS:  /* MSI used as PLL clock source */
      pll_vco = ((float_t)RCC_GET_MSIS_FREQUENCY()
                 / (float_t)pll_m) * ((float_t)pll_n + (fracn / (float_t)0x2000));
      break;
#if defined(HSE_VALUE)
    case HAL_RCC_PLL_SRC_HSE:  /* HSE used as PLL clock source */
      pll_vco = ((float_t)HSE_VALUE
                 / (float_t)pll_m) * ((float_t)pll_n + (fracn / (float_t)0x2000));
      break;
#endif /* HSE_VALUE */
    default:
      pll_vco = (float_t)0;
      break;
  }

  if (IS_BIT_SET(pll_cfgr, LL_RCC_PLL3_OUTPUT_P))
  {
    p_clk->pll_p_freq = (uint32_t)(float_t)(pll_vco /
                                            ((float_t)(uint32_t)(READ_BIT(pll_divr, RCC_PLL3DIVR_PLL3P)
                                                                 >> RCC_PLL3DIVR_PLL3P_Pos) + (float_t)1));
  }

  if (IS_BIT_SET(pll_cfgr, LL_RCC_PLL3_OUTPUT_Q))
  {
    p_clk->pll_q_freq = (uint32_t)(float_t)(pll_vco /
                                            ((float_t)(uint32_t)(READ_BIT(pll_divr, RCC_PLL3DIVR_PLL3Q)
                                                                 >> RCC_PLL3DIVR_PLL3Q_Pos) + (float_t)1));
  }

  if (IS_BIT_SET(pll_cfgr, LL_RCC_PLL3_OUTPUT_R))
  {
    p_clk->pll_r_freq = (uint32_t)(float_t)(pll_vco /
                                            ((float_t)(uint32_t)(READ_BIT(pll_divr, RCC_PLL3DIVR_PLL3R)
                                                                 >> RCC_PLL3DIVR_PLL3R_Pos) + (float_t)1));
  }
}

/**
  * @brief  Set the fractional part (FRACN) of the multiplication factor of PLL3 on-the-fly.
  * @param  fracn The new fractional value to be set for PLL3.
  * @retval HAL_OK     The FRACN value has been correctly set.
  * @retval HAL_ERROR  The FRACN value update has failed.
  */
hal_status_t HAL_RCC_PLL3_SetFRACN(uint16_t fracn)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(fracn));

  /* FRACN on-the-fly value update */
  if (LL_RCC_PLL3_GetFRACN() != fracn)
  {
    LL_RCC_PLL3FRACN_Disable();

    tickstart = HAL_GetTick();
    /* Wait at least 2 CK_REF (PLL3 input source divided by M) period to make sure next latched value will be taken
      into account. */
    while ((HAL_GetTick() - tickstart) < RCC_PLL_FRAC_WAIT_VALUE)
    {
    }

    LL_RCC_PLL3_SetFRACN(fracn);

    /* Enable PLL3FRACN to latch the new value. */
    LL_RCC_PLL3FRACN_Enable();
  }

  return HAL_OK;
}

/**
  * @brief  Get the current fractional part (FRACN) of the multiplication factor of PLL3.
  * @retval The current fractional value of PLL3.
  */
uint16_t HAL_RCC_PLL3_GetFRACN(void)
{
  return (uint16_t)LL_RCC_PLL3_GetFRACN();
}

/**
  * @brief    Disable PLL3 for power consumption perspective.
  * @warning  To enable again PLL3, a new configuration must be applied.
  * @details  This function allow to reset all the parameters which might impact power
  *           like PLLSRC, outputs...
  * @retval   HAL_OK    PLL3 is correctly disabled
  * @retval   HAL_ERROR Timeout detected during disabling of the PLL3
  */
hal_status_t HAL_RCC_PLL3_Reset(void)
{
  hal_status_t status = HAL_ERROR;

  LL_RCC_PLL3_Disable();

  if (RCC_WaitForTimeout(LL_RCC_PLL3_IsReady, RCC_PLL3_TIMEOUT_VALUE, 0U) == HAL_OK)
  {
    /* To save power disable the PLL3 Source and Clock outputs */
    CLEAR_BIT(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3PEN | RCC_PLL3CFGR_PLL3QEN | RCC_PLL3CFGR_PLL3REN |
              RCC_PLL3CFGR_PLL3SRC | RCC_PLL3CFGR_PLL3FRACEN);
    status = HAL_OK;
  }

  return status;
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group1_6
  * @{
  */

/**
  * @brief  Set the Systick external clock source
  * @param  clk_src Systick external clock source selection based on @ref hal_rcc_systick_clk_src_t
  */
void HAL_RCC_SetSysTickExternalClkSource(hal_rcc_systick_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SYSTICK_CLK(clk_src));

  LL_RCC_SetSystickClockSource((uint32_t)clk_src);
}

/**
  * @brief  Get the Systick external clock source
  * @retval Systick external clock source based on @ref hal_rcc_systick_clk_src_t
  */
hal_rcc_systick_clk_src_t HAL_RCC_GetSysTickExternalClkSource(void)
{
  return (hal_rcc_systick_clk_src_t)LL_RCC_GetSystickClockSource();
}

/**
  * @brief  Get the Systick external clock frequency
  * @retval uint32_t Frequency in Hz
  */
uint32_t HAL_RCC_GetSysTickExternalClkFreq(void)
{
  uint32_t frequency = 0;
  uint32_t clk_src = LL_RCC_GetSystickClockSource();

  switch (clk_src)
  {
    case LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8:
      frequency = (HAL_RCC_GetHCLKFreq() >> 3U);
      break;

    case LL_RCC_SYSTICK_CLKSOURCE_LSI:
      frequency = RCC_GET_LSI_FREQUENCY();
      break;

#if defined(LSE_VALUE)
    case LL_RCC_SYSTICK_CLKSOURCE_LSE:
      frequency = LSE_VALUE;
      break;
#endif /* LSE_VALUE */

    default:
      break;
  }

  return frequency;
}
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */

/**
  * @brief  Select the clock source to output on MCO pin.
  * @param  mco_src  specifies the clock source to output.
  * @param  mco_div  specifies the MCO prescaler.
  * @warning MCO selected pin must be configured in alternate function mode.
  */
void HAL_RCC_SetConfigMCO(hal_rcc_mco_src_t mco_src, hal_rcc_mco_prescaler_t mco_div)
{
  ASSERT_DBG_PARAM(IS_RCC_MCO1SOURCE(mco_src));
  ASSERT_DBG_PARAM(IS_RCC_MCOPRE(mco_div));

  LL_RCC_ConfigMCO((uint32_t)mco_src, (uint32_t)mco_div);
}

/**
  * @brief  Get and clear reset flags
  * @note   Once reset flags are retrieved, this API is clearing them in order to isolate next reset source.
  * @retval uint32_t Reset flags based on a combination of @ref RCC_Reset_Flag
  */
uint32_t HAL_RCC_GetResetSource(void)
{
  uint32_t reset;

  /* Get all reset flags */
  reset = RCC->CSR & HAL_RCC_RESET_FLAG_ALL;

  LL_RCC_ClearResetFlags();

  return reset;
}

#if defined(HSE_VALUE)
/**
  * @brief  Enable the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (Clock Security System Interrupt, CSSI),
  *         allowing the MCU to perform rescue operations. The CSS interrupt is linked to
  *         the Cortex-M33 NMI (Non-Maskable Interrupt) exception vector.
  * @note   The Clock Security System can only be cleared by reset.
  */
void HAL_RCC_HSE_EnableCSS(void)
{
  LL_RCC_HSE_EnableCSS();
}

/**
  * @brief Handle the RCC HSE Clock Security System interrupt request.
  * @warning This API must be called under the NMI_Handler().
  * @retval HAL_OK    NMI has been managed and NMI_Handler() might exit
  * @retval HAL_ERROR NMI has not been managed and NMI_Handler() might exit
  */
hal_status_t HAL_RCC_NMI_IRQHandler(void)
{
  hal_status_t cb_status = HAL_ERROR;

  if (LL_RCC_IsActiveFlag(LL_RCC_IT_HSECSS) != 0U)
  {
    if (HAL_RCC_HSE_CSSCallback() == HAL_OK)
    {
      LL_RCC_ClearFlag(LL_RCC_IT_HSECSS);
      cb_status = HAL_OK;
    }
  }

  return cb_status;
}

/**
  * @brief  RCC Clock Security System interrupt callback.
  * @retval HAL_OK    ECC error has been managed.
  * @retval HAL_ERROR ECC error not has been managed.
  */
__WEAK hal_status_t HAL_RCC_HSE_CSSCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_HSE_CSSCallback must be implemented in the user file
   */
  /* Status to be updated to HAL_OK when the user callback managed the HSECSS error */
  return HAL_ERROR;
}

#endif /* HSE_VALUE */

/**
  * @brief   Configure the oscillator clock source for wakeup from Stop and CSS backup clock.
  * @param   wakeup_clk  Wakeup clock
  *          This parameter can be one of the following values:
  *            @arg @ref HAL_RCC_STOP_WAKEUPCLOCK_MSI  MSI oscillator selection
  *            @arg @ref HAL_RCC_STOP_WAKEUPCLOCK_HSI  HSI oscillator selection
  * @warning This function must not be called after the Clock Security System on HSE has been enabled.
  */
void HAL_RCC_SetClockAfterWakeFromStop(hal_rcc_stop_wakeup_clk_t wakeup_clk)
{
  ASSERT_DBG_PARAM(IS_RCC_STOP_WAKEUPCLOCK(wakeup_clk));

  LL_RCC_SetClkAfterWakeFromStop((uint32_t)wakeup_clk);
}

/**
  * @brief   Get the oscillator clock source for wakeup from Stop and CSS backup clock.
  * @retval  hal_rcc_stop_wakeup_clk_t  Wakeup clock source
  */
hal_rcc_stop_wakeup_clk_t HAL_RCC_GetClockAfterWakeFromStop(void)
{
  return (hal_rcc_stop_wakeup_clk_t)LL_RCC_GetClkAfterWakeFromStop();
}

/**
  * @brief  Configure the oscillator Kernel clock source for wakeup from Stop
  * @param  wakeup_clk Kernel Wakeup clock
  */
void HAL_RCC_SetKernelClkAfterWakeFromStop(hal_rcc_stop_wakeup_kerclk_t wakeup_clk)
{
  ASSERT_DBG_PARAM(IS_RCC_STOP_KERWAKEUPCLOCK(wakeup_clk));

  LL_RCC_SetKerClkAfterWakeFromStop((uint32_t)wakeup_clk);
}

/**
  * @brief  Get the oscillator Kernel clock source for wakeup from Stop
  * @retval hal_rcc_stop_wakeup_kerclk_t Kernel Wakeup clock
  */
hal_rcc_stop_wakeup_kerclk_t HAL_RCC_GetKernelClkAfterWakeFromStop(void)
{
  return (hal_rcc_stop_wakeup_kerclk_t)LL_RCC_GetKerClkAfterWakeFromStop();
}

#if defined(LSE_VALUE)
/**
  * @brief  Enable the LSE Clock Security System.
  * @note   Prior to enable the LSE Clock Security System, LSE oscillator must be enabled
  *         with HAL_RCC_LSE_Enable() and  LSE oscillator clock is to be selected as RTC
  *         clock with HAL_RCC_RTC_SetKernelClkSource().
  */
void HAL_RCC_LSE_EnableCSS(void)
{
  LL_RCC_LSE_EnableCSS();
}

/**
  * @brief  Disable the LSE Clock Security System.
  * @note   LSE Clock Security System can only be disabled after a LSE failure detection.
  */
void HAL_RCC_LSE_DisableCSS(void)
{
  LL_RCC_LSE_DisableCSS();
}

/**
  * @brief   Handle the RCC LSE Clock Security System interrupt request.
  * @warning TAMP3 interruption line must be previously configured and enabled to detect this interruption.
  * @note    LSECSS EXTI interrupt line available in U5 except STM32U575/585 rev. X and STM32U59x/5Ax rev. B/Y devices.
  */
void HAL_RCC_LSECSS_IRQHandler(void)
{
  if (LL_RCC_LSE_IsCSSDetected() != 0U)
  {
    /* RCC LSE Clock Security System interrupt user callback */
    HAL_RCC_LSE_CSSCallback();
  }
}

/**
  * @brief  RCC LSE Clock Security System interrupt callback.
  */
__WEAK void HAL_RCC_LSE_CSSCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the @ref HAL_RCC_LSE_CSSCallback must be implemented in the user file
   */
}

/**
  * @brief   Handle the RCC MSI PLL Unlock interrupt request.
  * @warning EXTI line must be previously configured and enabled to detect this interruption.
  * @note    Not available in STM32U575/585 rev. X and and STM32U59x/5Ax rev. B/Y devices.
  */
void HAL_RCC_MSI_PLLUnlock_IRQHandler(void)
{
  HAL_RCC_MSI_PLLUnlock_Callback();
}

/**
  * @brief  RCC RCC MSI PLL Unlock interrupt callback.
  * @note   Not available in STM32U575/585 rev. X and and STM32U59x/5Ax rev. B/Y devices.
  */
__WEAK void HAL_RCC_MSI_PLLUnlock_Callback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the @ref HAL_RCC_MSI_PLLUnlock_Callback must be implemented in the user file
   */
}
#endif /* LSE_VALUE */

/**
  * @brief   Select source clock to use on the Low Speed Clock Output (LSCO).
  * @param   source  specifies the Low Speed clock source to output.
  * @note    PWR and backup domain are to enabled before calling this function.
  * @retval  HAL_OK      LSCO activated
  * @retval  HAL_ERROR   Backup domain is not enabled
  */
hal_status_t HAL_RCC_EnableLSCO(hal_rcc_lsco_src_t source)
{
  ASSERT_DBG_PARAM(IS_RCC_LSCOSOURCE(source));

  if (HAL_PWR_IsEnabledRTCDomainWriteProtection() != HAL_PWR_RTC_DOMAIN_WRP_DISABLED)
  {
    return HAL_ERROR;
  }

  LL_RCC_ConfigLSCO((uint32_t)source);

  return HAL_OK;
}

/**
  * @brief  Disable the Low Speed Clock Output (LSCO).
  * @note   PWR and backup domain are to enabled before calling this function.
  * @retval HAL_OK      LSCO Deactivated
  * @retval HAL_ERROR   Backup domain is not enabled
  */
hal_status_t HAL_RCC_DisableLSCO(void)
{
  if (HAL_PWR_IsEnabledRTCDomainWriteProtection() != HAL_PWR_RTC_DOMAIN_WRP_DISABLED)
  {
    return HAL_ERROR;
  }

  LL_RCC_LSCO_Disable();

  return HAL_OK;
}

/**
  * @brief Enable RTC and TAMP kernel clock.
  * @note  PWR and backup domain are to enabled before calling this function.
  * @retval HAL_OK      RTC and TAMP kernel clock enabled
  * @retval HAL_ERROR   Backup domain is not enabled
  */
hal_status_t HAL_RCC_RTC_EnableKernelClock(void)
{
  if (HAL_PWR_IsEnabledRTCDomainWriteProtection() != HAL_PWR_RTC_DOMAIN_WRP_DISABLED)
  {
    return HAL_ERROR;
  }

  LL_RCC_EnableRTC();

  return HAL_OK;
}

/**
  * @brief Disable RTC and TAMP kernel clock.
  * @note  PWR and backup domain are to enabled before calling this function.
  * @retval HAL_OK      RTC and TAMP kernel clock disabled
  * @retval HAL_ERROR   Backup domain is not enabled
  */
hal_status_t HAL_RCC_RTC_DisableKernelClock(void)
{
  if (HAL_PWR_IsEnabledRTCDomainWriteProtection() != HAL_PWR_RTC_DOMAIN_WRP_DISABLED)
  {
    return HAL_ERROR;
  }

  LL_RCC_DisableRTC();

  return HAL_OK;
}

/**
  * @brief  Set the Clocks sources for TIM16,TIM17 and LPTIM2 internal input capture
  * @param  clk_src Clock source selection based on @ref hal_rcc_timic_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SetTimerInputCaptureClockSource(hal_rcc_timic_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_TIMIC_CLK(clk_src));

  LL_RCC_SetTIMICClockSource((uint32_t)clk_src);

  return HAL_OK;
}

/**
  * @brief  Get the Clocks sources for TIM16,TIM17 and LPTIM2 internal input capture
  * @retval clk_src Clock source based on @ref hal_rcc_timic_clk_src_t
  */
hal_rcc_timic_clk_src_t HAL_RCC_GetTimerInputCaptureClockSource(void)
{
  return (hal_rcc_timic_clk_src_t)LL_RCC_GetTIMICClockSource();
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group3
  * @{
  */
/**
  * @brief  Set the USART1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_usart1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USART1_SetKernelClkSource(hal_rcc_usart1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USART1_CLK(clk_src));

  LL_RCC_SetUSARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined (USART2)
/**
  * @brief  Set the USART2 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_usart2_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USART2_SetKernelClkSource(hal_rcc_usart2_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USART2_CLK(clk_src));

  LL_RCC_SetUSARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* USART2 */

/**
  * @brief  Set the USART3 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_usart3_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USART3_SetKernelClkSource(hal_rcc_usart3_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USART3_CLK(clk_src));

  LL_RCC_SetUSARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the UART4 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_uart4_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_UART4_SetKernelClkSource(hal_rcc_uart4_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_UART4_CLK(clk_src));

  LL_RCC_SetUARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the UART5 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_uart5_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_UART5_SetKernelClkSource(hal_rcc_uart5_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_UART5_CLK(clk_src));

  LL_RCC_SetUARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined(USART6)
/**
  * @brief  Set the USART6 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_usart6_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USART6_SetKernelClkSource(hal_rcc_usart6_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USART6_CLK(clk_src));

  LL_RCC_SetUSARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* USART6 */

/**
  * @brief  Set the LPUART1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_lpuart1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LPUART1_SetKernelClkSource(hal_rcc_lpuart1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LPUART1_CLK(clk_src));

  LL_RCC_SetLPUARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the I2C1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_i2c1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I2C1_SetKernelClkSource(hal_rcc_i2c1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I2C1_CLK(clk_src));

  LL_RCC_SetI2CClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the I2C2 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_i2c2_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I2C2_SetKernelClkSource(hal_rcc_i2c2_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I2C2_CLK(clk_src));

  LL_RCC_SetI2CClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the I2C3 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_i2c3_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I2C3_SetKernelClkSource(hal_rcc_i2c3_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I2C3_CLK(clk_src));

  LL_RCC_SetI2CClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the I2C4 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_i2c4_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I2C4_SetKernelClkSource(hal_rcc_i2c4_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I2C4_CLK(clk_src));

  LL_RCC_SetI2CClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined(I2C5)
/**
  * @brief  Set the I2C5 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_i2c5_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I2C5_SetKernelClkSource(hal_rcc_i2c5_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I2C5_CLK(clk_src));

  LL_RCC_SetI2CClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* I2C5 */

#if defined(I2C6)
/**
  * @brief  Set the I2C6 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_i2c6_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I2C6_SetKernelClkSource(hal_rcc_i2c6_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I2C6_CLK(clk_src));

  LL_RCC_SetI2CClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* I2C6 */

/**
  * @brief  Set the LPTIM1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_lptim1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LPTIM1_SetKernelClkSource(hal_rcc_lptim1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LPTIM1_CLK(clk_src));

  LL_RCC_SetLPTIMClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the LPTIM2 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_lptim2_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LPTIM2_SetKernelClkSource(hal_rcc_lptim2_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LPTIM2_CLK(clk_src));

  LL_RCC_SetLPTIMClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the LPTIM34 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_lptim34_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LPTIM34_SetKernelClkSource(hal_rcc_lptim34_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LPTIM34_CLK(clk_src));

  LL_RCC_SetLPTIMClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the FDCAN clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_fdcan_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_FDCAN_SetKernelClkSource(hal_rcc_fdcan_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_FDCAN_CLK(clk_src));

  LL_RCC_SetFDCANClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the MDF1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_mdf1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_MDF1_SetKernelClkSource(hal_rcc_mdf1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_MDF1_CLK(clk_src));

  LL_RCC_SetMDF1ClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the ADF1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_adf1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_ADF1_SetKernelClkSource(hal_rcc_adf1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_ADF1_CLK(clk_src));

  LL_RCC_SetADF1ClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SAI1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_sai1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SAI1_SetKernelClkSource(hal_rcc_sai1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SAI1_CLK(clk_src));

  LL_RCC_SetSAIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined (SAI2)
/**
  * @brief  Set the SAI2 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_sai2_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SAI2_SetKernelClkSource(hal_rcc_sai2_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SAI2_CLK(clk_src));

  LL_RCC_SetSAIClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* SAI2 */

/**
  * @brief  Set the RNG clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_rng_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_RNG_SetKernelClkSource(hal_rcc_rng_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_RNG_CLK(clk_src));

  LL_RCC_SetRNGClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined(SAES)
/**
  * @brief  Set the SAES clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_saes_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SAES_SetKernelClkSource(hal_rcc_saes_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SAES_CLK(clk_src));

  LL_RCC_SetSAESClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* SAES */

/**
  * @brief  Set the ICLK clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_iclk_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_ICLK_SetKernelClkSource(hal_rcc_iclk_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_ICLK_CLK(clk_src));

  LL_RCC_SetSDMMCClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SDMMC clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_sdmmc_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SDMMC_SetKernelClkSource(hal_rcc_sdmmc_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SDMMC_CLK(clk_src));

  LL_RCC_SetSDMMCKernelClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the ADCDAC clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_adcdac_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_ADCDAC_SetKernelClkSource(hal_rcc_adcdac_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_ADCDAC_CLK(clk_src));

  LL_RCC_SetADCDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC1_SetSampleAndHoldClkSource(hal_rcc_dac1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC1_CLK(clk_src));

  LL_RCC_SetDAC1ClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the OCTOSPI clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_octospi_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_OCTOSPI_SetKernelClkSource(hal_rcc_octospi_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_OCTOSPI_CLK(clk_src));

  LL_RCC_SetOCTOSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined(HSPI1)
/**
  * @brief  Set the HSPI1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_hspi1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_HSPI1_SetKernelClkSource(hal_rcc_hspi1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_HSPI1_CLK(clk_src));

  LL_RCC_SetHSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* HSPI1 */

/**
  * @brief  Set the SPI1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI1_SetKernelClkSource(hal_rcc_spi1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI1_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SPI2 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi2_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI2_SetKernelClkSource(hal_rcc_spi2_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI2_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SPI3 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi3_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI3_SetKernelClkSource(hal_rcc_spi3_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI3_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the RTC clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_rtc_clk_src_t
  * @note   Access to Backup domain has to be enabled.
  * @retval HAL_OK    RTC source clock has been selected
  * @retval HAL_ERROR LSE activation failed after reset of Backup domain
  */
hal_status_t HAL_RCC_RTC_SetKernelClkSource(hal_rcc_rtc_clk_src_t clk_src)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(IS_RCC_RTC_CLK(clk_src));

  /* Reset the Backup domain only if the RTC Clock source selection is modified from default */
  uint32_t tmpregister = LL_RCC_GetRTCClockSource();

  if ((tmpregister != LL_RCC_RTC_CLKSOURCE_NONE) && (tmpregister != (uint32_t)clk_src))
  {
    /* Store the content of BDCR register before the reset of Backup Domain */
    tmpregister = READ_BIT(RCC->BDCR, ~(RCC_BDCR_RTCSEL));
    /* RTC Clock selection can be changed only if the Backup Domain is reset */
    HAL_RCC_ResetBackupDomain();
    /* Restore the Content of BDCR register */
    RCC->BDCR = tmpregister;
  }

#if defined(LSE_VALUE)
  /* Wait for LSE reactivation if LSE was enable prior to Backup Domain reset */
  if (IS_BIT_SET(tmpregister, RCC_BDCR_LSEON))
  {
    status = RCC_WaitForTimeout(LL_RCC_LSE_IsReady, RCC_LSE_TIMEOUT_VALUE, 1U);
  }

  /* Wait for LSESYS reactivation if LSESYS was enable prior to Backup Domain reset */
  if ((status == HAL_OK) && (IS_BIT_SET(tmpregister, RCC_BDCR_LSESYSEN)))
  {
    status = RCC_WaitForTimeout(LL_RCC_LSE_IsPropagationReady, RCC_LSE_TIMEOUT_VALUE, 1U);
  }

  if (status == HAL_OK)
#endif /* LSE_VALUE */
  {
    /* Apply new RTC clock source selection */
    LL_RCC_SetRTCClockSource((uint32_t)clk_src);
  }

  return status;
}

#if defined(LTDC)
/**
  * @brief  Set the LTDC clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_ltdc_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LTDC_SetKernelClkSource(hal_rcc_ltdc_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LTDC_CLK(clk_src));

  LL_RCC_SetLTDCClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* LTDC */

#if defined(DSI)
/**
  * @brief  Set the DSI clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_dsi_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DSI_SetKernelClkSource(hal_rcc_dsi_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DSI_CLK(clk_src));

  LL_RCC_SetDSIClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* DSI */

#if defined(USB_OTG_HS)
/**
  * @brief  Set the OTG_HS PHY clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_usbhsphy_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USBHSPHY_SetKernelClkSource(hal_rcc_usbhsphy_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USBHSPHY_CLK(clk_src));

  LL_RCC_SetUSBHSPHYClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* USB_OTG_HS */

/**
  * @brief  Get the USART1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_usart1_clk_src_t
  */
hal_rcc_usart1_clk_src_t HAL_RCC_USART1_GetKernelClkSource(void)
{
  return (hal_rcc_usart1_clk_src_t)LL_RCC_GetUSARTClockSource(LL_RCC_USART1_CLKSOURCE);
}

#if defined (USART2)
/**
  * @brief  Get the USART2 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_usart2_clk_src_t
  */
hal_rcc_usart2_clk_src_t HAL_RCC_USART2_GetKernelClkSource(void)
{
  return (hal_rcc_usart2_clk_src_t)LL_RCC_GetUSARTClockSource(LL_RCC_USART2_CLKSOURCE);
}
#endif /* USART2 */

/**
  * @brief  Get the USART3 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_usart3_clk_src_t
  */
hal_rcc_usart3_clk_src_t HAL_RCC_USART3_GetKernelClkSource(void)
{
  return (hal_rcc_usart3_clk_src_t)LL_RCC_GetUSARTClockSource(LL_RCC_USART3_CLKSOURCE);
}

#if defined(USART6)
/**
  * @brief  Get the USART6 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_usart6_clk_src_t
  */
hal_rcc_usart6_clk_src_t HAL_RCC_USART6_GetKernelClkSource(void)
{
  return (hal_rcc_usart6_clk_src_t)LL_RCC_GetUSARTClockSource(LL_RCC_USART6_CLKSOURCE);
}
#endif /* USART6 */

/**
  * @brief  Get the UART4 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_uart4_clk_src_t
  */
hal_rcc_uart4_clk_src_t HAL_RCC_UART4_GetKernelClkSource(void)
{
  return (hal_rcc_uart4_clk_src_t)LL_RCC_GetUARTClockSource(LL_RCC_UART4_CLKSOURCE);
}

/**
  * @brief  Get the UART5 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_uart5_clk_src_t
  */
hal_rcc_uart5_clk_src_t HAL_RCC_UART5_GetKernelClkSource(void)
{
  return (hal_rcc_uart5_clk_src_t)LL_RCC_GetUARTClockSource(LL_RCC_UART5_CLKSOURCE);
}

/**
  * @brief  Get the LPUART1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_lpuart1_clk_src_t
  */
hal_rcc_lpuart1_clk_src_t HAL_RCC_LPUART1_GetKernelClkSource(void)
{
  return (hal_rcc_lpuart1_clk_src_t)LL_RCC_GetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE);
}

/**
  * @brief  Get the I2C1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_i2c1_clk_src_t
  */
hal_rcc_i2c1_clk_src_t HAL_RCC_I2C1_GetKernelClkSource(void)
{
  return (hal_rcc_i2c1_clk_src_t)LL_RCC_GetI2CClockSource(LL_RCC_I2C1_CLKSOURCE);
}

/**
  * @brief  Get the I2C2 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_i2c2_clk_src_t
  */
hal_rcc_i2c2_clk_src_t HAL_RCC_I2C2_GetKernelClkSource(void)
{
  return (hal_rcc_i2c2_clk_src_t)LL_RCC_GetI2CClockSource(LL_RCC_I2C2_CLKSOURCE);
}

/**
  * @brief  Get the I2C3 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_i2c3_clk_src_t
  */
hal_rcc_i2c3_clk_src_t HAL_RCC_I2C3_GetKernelClkSource(void)
{
  return (hal_rcc_i2c3_clk_src_t)LL_RCC_GetI2CClockSource(LL_RCC_I2C3_CLKSOURCE);
}

/**
  * @brief  Get the I2C4 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_i2c4_clk_src_t
  */
hal_rcc_i2c4_clk_src_t HAL_RCC_I2C4_GetKernelClkSource(void)
{
  return (hal_rcc_i2c4_clk_src_t)LL_RCC_GetI2CClockSource(LL_RCC_I2C4_CLKSOURCE);
}

#if defined(I2C5)
/**
  * @brief  Get the I2C5 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_i2c5_clk_src_t
  */
hal_rcc_i2c5_clk_src_t HAL_RCC_I2C5_GetKernelClkSource(void)
{
  return (hal_rcc_i2c5_clk_src_t)LL_RCC_GetI2CClockSource(LL_RCC_I2C5_CLKSOURCE);
}
#endif /* I2C5 */

#if defined(I2C6)
/**
  * @brief  Get the I2C6 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_i2c6_clk_src_t
  */
hal_rcc_i2c6_clk_src_t HAL_RCC_I2C6_GetKernelClkSource(void)
{
  return (hal_rcc_i2c6_clk_src_t)LL_RCC_GetI2CClockSource(LL_RCC_I2C6_CLKSOURCE);
}
#endif /* I2C6 */

/**
  * @brief  Get the LPTIM1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_lptim1_clk_src_t
  */
hal_rcc_lptim1_clk_src_t HAL_RCC_LPTIM1_GetKernelClkSource(void)
{
  return (hal_rcc_lptim1_clk_src_t)LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE);
}

/**
  * @brief  Get the LPTIM2 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_lptim2_clk_src_t
  */
hal_rcc_lptim2_clk_src_t HAL_RCC_LPTIM2_GetKernelClkSource(void)
{
  return (hal_rcc_lptim2_clk_src_t)LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM2_CLKSOURCE);
}

/**
  * @brief  Get the LPTIM34 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_lptim34_clk_src_t
  */
hal_rcc_lptim34_clk_src_t HAL_RCC_LPTIM34_GetKernelClkSource(void)
{
  return (hal_rcc_lptim34_clk_src_t)LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM34_CLKSOURCE);
}

/**
  * @brief  Get the FDCAN clock source
  * @retval clk_src Clock source based on @ref hal_rcc_fdcan_clk_src_t
  */
hal_rcc_fdcan_clk_src_t HAL_RCC_FDCAN_GetKernelClkSource(void)
{
  return (hal_rcc_fdcan_clk_src_t)LL_RCC_GetFDCANClockSource(LL_RCC_FDCAN_CLKSOURCE);
}

/**
  * @brief  Get the MDF1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_mdf1_clk_src_t
  */
hal_rcc_mdf1_clk_src_t HAL_RCC_MDF1_GetKernelClkSource(void)
{
  return (hal_rcc_mdf1_clk_src_t)LL_RCC_GetMDF1ClockSource(LL_RCC_MDF1_CLKSOURCE);
}

/**
  * @brief  Get the ADF1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_adf1_clk_src_t
  */
hal_rcc_adf1_clk_src_t HAL_RCC_ADF1_GetKernelClkSource(void)
{
  return (hal_rcc_adf1_clk_src_t)LL_RCC_GetADF1ClockSource(LL_RCC_ADF1_CLKSOURCE);
}

/**
  * @brief  Get the SAI1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_sai1_clk_src_t
  */
hal_rcc_sai1_clk_src_t HAL_RCC_SAI1_GetKernelClkSource(void)
{
  return (hal_rcc_sai1_clk_src_t)LL_RCC_GetSAIClockSource(LL_RCC_SAI1_CLKSOURCE);
}

#if defined (SAI2)
/**
  * @brief  Get the SAI2 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_sai2_clk_src_t
  */
hal_rcc_sai2_clk_src_t HAL_RCC_SAI2_GetKernelClkSource(void)
{
  return (hal_rcc_sai2_clk_src_t)LL_RCC_GetSAIClockSource(LL_RCC_SAI2_CLKSOURCE);
}
#endif /* SAI2 */

/**
  * @brief  Get the RNG clock source
  * @retval clk_src Clock source based on @ref hal_rcc_rng_clk_src_t
  */
hal_rcc_rng_clk_src_t HAL_RCC_RNG_GetKernelClkSource(void)
{
  return (hal_rcc_rng_clk_src_t)LL_RCC_GetRNGClockSource(LL_RCC_RNG_CLKSOURCE);
}

#if defined(SAES)
/**
  * @brief  Get the SAES clock source
  * @retval clk_src Clock source based on @ref hal_rcc_saes_clk_src_t
  */
hal_rcc_saes_clk_src_t HAL_RCC_SAES_GetKernelClkSource(void)
{
  return (hal_rcc_saes_clk_src_t)LL_RCC_GetSAESClockSource(LL_RCC_SAES_CLKSOURCE);
}
#endif /* SAES */

/**
  * @brief  Get the ICLK clock source
  * @retval clk_src Clock source based on @ref hal_rcc_iclk_clk_src_t
  */
hal_rcc_iclk_clk_src_t HAL_RCC_ICLK_GetKernelClkSource(void)
{
  return (hal_rcc_iclk_clk_src_t)LL_RCC_GetUSBClockSource(LL_RCC_USB_CLKSOURCE);
}

/**
  * @brief  Get the SDMMC clock source
  * @retval clk_src Clock source based on @ref hal_rcc_sdmmc_clk_src_t
  */
hal_rcc_sdmmc_clk_src_t HAL_RCC_SDMMC_GetKernelClkSource(void)
{
  return (hal_rcc_sdmmc_clk_src_t)LL_RCC_GetSDMMCKernelClockSource(LL_RCC_SDMMC_KERNELCLKSOURCE);
}

/**
  * @brief  Get the ADCDAC clock source
  * @retval clk_src Clock source based on @ref hal_rcc_adcdac_clk_src_t
  */
hal_rcc_adcdac_clk_src_t HAL_RCC_ADCDAC_GetKernelClkSource(void)
{
  return (hal_rcc_adcdac_clk_src_t)LL_RCC_GetADCDACClockSource(LL_RCC_ADCDAC_CLKSOURCE);
}

/**
  * @brief  Get the DAC1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_dac1_clk_src_t
  */
hal_rcc_dac1_clk_src_t HAL_RCC_DAC1_GetSampleHoldClkSource(void)
{
  return (hal_rcc_dac1_clk_src_t)LL_RCC_GetDAC1ClockSource(LL_RCC_DAC1_CLKSOURCE);
}

/**
  * @brief  Get the OCTOSPI clock source
  * @retval clk_src Clock source based on @ref hal_rcc_octospi_clk_src_t
  */
hal_rcc_octospi_clk_src_t HAL_RCC_OCTOSPI_GetKernelClkSource(void)
{
  return (hal_rcc_octospi_clk_src_t)LL_RCC_GetOCTOSPIClockSource(LL_RCC_OCTOSPI_CLKSOURCE);
}

#if defined(HSPI1)
/**
  * @brief  Get the HSPI clock source
  * @retval clk_src Clock source based on @ref hal_rcc_hspi1_clk_src_t
  */
hal_rcc_hspi1_clk_src_t HAL_RCC_HSPI1_GetKernelClkSource(void)
{
  return (hal_rcc_hspi1_clk_src_t)LL_RCC_GetHSPIClockSource(LL_RCC_HSPI_CLKSOURCE);
}
#endif /* HSPI1 */

/**
  * @brief  Get the SPI1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_spi1_clk_src_t
  */
hal_rcc_spi1_clk_src_t HAL_RCC_SPI1_GetKernelClkSource(void)
{
  return (hal_rcc_spi1_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI1_CLKSOURCE);
}

/**
  * @brief  Get the SPI2 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_spi2_clk_src_t
  */
hal_rcc_spi2_clk_src_t HAL_RCC_SPI2_GetKernelClkSource(void)
{
  return (hal_rcc_spi2_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI2_CLKSOURCE);
}

/**
  * @brief  Get the SPI3 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_spi3_clk_src_t
  */
hal_rcc_spi3_clk_src_t HAL_RCC_SPI3_GetKernelClkSource(void)
{
  return (hal_rcc_spi3_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI3_CLKSOURCE);
}

/**
  * @brief  Get the RTC clock source
  * @retval clk_src Clock source based on @ref hal_rcc_rtc_clk_src_t
  */
hal_rcc_rtc_clk_src_t HAL_RCC_RTC_GetKernelClkSource(void)
{
  return (hal_rcc_rtc_clk_src_t)LL_RCC_GetRTCClockSource();
}

#if defined(LTDC)
/**
  * @brief  Get the LTDC clock source
  * @retval clk_src Clock source based on @ref hal_rcc_ltdc_clk_src_t
  */
hal_rcc_ltdc_clk_src_t HAL_RCC_LTDC_GetKernelClkSource(void)
{
  return (hal_rcc_ltdc_clk_src_t)LL_RCC_GetLTDCClockSource(LL_RCC_LTDC_CLKSOURCE);
}
#endif /* LTDC */

#if defined(DSI)
/**
  * @brief  Get the DSI clock source
  * @retval clk_src Clock source based on @ref hal_rcc_dsi_clk_src_t
  */
hal_rcc_dsi_clk_src_t HAL_RCC_DSI_GetKernelClkSource(void)
{
  return (hal_rcc_dsi_clk_src_t)LL_RCC_GetDSIClockSource(LL_RCC_DSI_CLKSOURCE);
}
#endif /* DSI */

#if defined(USB_OTG_HS)
/**
  * @brief  Get the USB HS PHY clock source
  * @retval clk_src Clock source based on @ref hal_rcc_usbhsphy_clk_src_t
  */
hal_rcc_usbhsphy_clk_src_t HAL_RCC_USBHSPHY_GetKernelClkSource(void)
{
  return (hal_rcc_usbhsphy_clk_src_t)LL_RCC_GetUSBHSPHYClockSource(LL_RCC_USBHSPHY_CLKSOURCE);
}
#endif /* USB_OTG_HS */

/**
  * @brief  Return the peripheral clock frequency for RTC
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_RTC_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetRTCClockSource();
  uint32_t bdcr_temp = LL_RCC_READ_REG(BDCR);

  switch (srcclk)
  {
    case LL_RCC_RTC_CLKSOURCE_LSI:
      if (IS_BIT_SET(bdcr_temp, RCC_BDCR_LSIRDY))
      {
        frequency = RCC_GET_LSI_FREQUENCY();
      }
      break;

#if defined(LSE_VALUE)
    case LL_RCC_RTC_CLKSOURCE_LSE:
      if (IS_BIT_SET(bdcr_temp, RCC_BDCR_LSERDY))
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

#if defined(HSE_VALUE)
    case LL_RCC_RTC_CLKSOURCE_HSE_DIV32:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE / 32U;
      }
      break;
#endif /* HSE_VALUE */
    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SAI
  * @param  saix SAI instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_SAI_GetKernelClkFreq(const SAI_TypeDef *saix)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)saix)
  {
    case (uint32_t)SAI1:
      frequency = HAL_RCC_SAI1_GetKernelClkFreq();
      break;

#if defined(SAI2)
    case (uint32_t)SAI2:
      frequency = HAL_RCC_SAI2_GetKernelClkFreq();
      break;
#endif /* SAI2 */

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SAI1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_SAI1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetSAIClockSource(LL_RCC_SAI1_CLKSOURCE);
  switch (srcclk)
  {
    case LL_RCC_SAI1_CLKSOURCE_PLL1:
      /* Clock source is on PLL1 output P */
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_SAI1_CLKSOURCE_PLL2:
      /* Clock source is on PLL2 output P */
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_SAI1_CLKSOURCE_PLL3:
      /* Clock source is on PLL3 output P */
      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

#if defined(EXTERNAL_SAI1_CLOCK_VALUE)
    case LL_RCC_SAI1_CLKSOURCE_PIN:

      frequency = EXTERNAL_SAI1_CLOCK_VALUE;
      break;
#endif /* EXTERNAL_SAI1_CLOCK_VALUE */

    case LL_RCC_SAI1_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    default :
      break;
  }
  return frequency;
}

#if defined (SAI2)
/**
  * @brief  Return the peripheral clock frequency for SAI2
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_SAI2_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetSAIClockSource(LL_RCC_SAI2_CLKSOURCE);
  switch (srcclk)
  {
    case LL_RCC_SAI2_CLKSOURCE_PLL1:
      /* Clock source is on PLL1 output P */
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_SAI2_CLKSOURCE_PLL2:
      /* Clock source is on PLL2 output P */
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_SAI2_CLKSOURCE_PLL3:
      /* Clock source is on PLL3 output P */
      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

#if defined(EXTERNAL_SAI1_CLOCK_VALUE)
    case LL_RCC_SAI2_CLKSOURCE_PIN:

      frequency = EXTERNAL_SAI1_CLOCK_VALUE;
      break;
#endif /* EXTERNAL_SAI1_CLOCK_VALUE */

    case LL_RCC_SAI2_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    default :
      break;
  }
  return frequency;
}
#endif /* SAI2 */

#if defined(SAES)
/**
  * @brief  Return the peripheral clock frequency for SAES
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SAES_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;

  if (LL_RCC_SHSI_IsReady() != 0U)
  {
    uint32_t srcclk = LL_RCC_GetSAESClockSource(LL_RCC_SAES_CLKSOURCE);

    if (srcclk == LL_RCC_SAES_CLKSOURCE_SHSI)
    {
      frequency = SHSI_VALUE;
    }
    else
    {
      frequency = SHSI_VALUE >> 1U;
    }
  }

  return frequency;
}
#endif /* SAES */

/**
  * @brief  Return the peripheral clock frequency for ICLK
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_ICLK_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetUSBClockSource(LL_RCC_USB_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_USB_CLKSOURCE_HSI48:
      if (LL_RCC_HSI48_IsReady() != 0U)
      {
        frequency = HSI48_VALUE;
      }
      break;

    case LL_RCC_USB_CLKSOURCE_MSIK:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;

    case LL_RCC_USB_CLKSOURCE_PLL1:
      /* Clock source is on PLL1 output Q */
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    default:
      /* Clock source is on PLL2 output Q */
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SDMMC
  * @param  sdmmcx SDMMC instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_SDMMC_GetKernelClkFreq(const SDMMC_TypeDef *sdmmcx)
{
  STM32_UNUSED(sdmmcx);

  return HAL_RCC_SDMMC12_GetKernelClkFreq();
}

/**
  * @brief  Return the peripheral clock frequency for SDMMC12
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_SDMMC12_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetSDMMCKernelClockSource(LL_RCC_SDMMC_KERNELCLKSOURCE);

  if (srcclk == LL_RCC_SDMMC12_KERCLKSOURCE_48CLK)
  {
    srcclk = LL_RCC_GetSDMMCClockSource(LL_RCC_SDMMC_CLKSOURCE);

    switch (srcclk)
    {
      case LL_RCC_SDMMC12_CLKSOURCE_HSI48:
        if (LL_RCC_HSI48_IsReady() != 0U)
        {
          frequency = HSI48_VALUE;
        }
        break;

      case LL_RCC_SDMMC12_CLKSOURCE_MSIK:
        if (LL_RCC_MSIK_IsReady() != 0U)
        {
          frequency = RCC_GET_MSIK_FREQUENCY();
        }
        break;

      case LL_RCC_SDMMC12_CLKSOURCE_PLL1:
        /* Clock source is on PLL1 output Q */
        HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
        frequency = pll_clocks.pll_q_freq;
        break;

      default:
        /* Clock source is on PLL2 output Q */
        HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
        frequency = pll_clocks.pll_q_freq;
        break;
    }
  }
  else
  {
    if (srcclk == LL_RCC_SDMMC12_KERCLKSOURCE_PLL1)
    {
      /* Clock source is on PLL1 output P */
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
    }
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for USART/SMARTCARD
  * @param  usartx USART instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USART_GetKernelClkFreq(const USART_TypeDef *usartx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)usartx)
  {
    case (uint32_t)USART1:
      frequency = HAL_RCC_USART1_GetKernelClkFreq();
      break;

#if defined(USART2)
    case (uint32_t)USART2:
      frequency = HAL_RCC_USART2_GetKernelClkFreq();
      break;
#endif /* USART2 */

    case (uint32_t)USART3:
      frequency = HAL_RCC_USART3_GetKernelClkFreq();
      break;

#if defined(USART6)
    case (uint32_t)USART6:
      frequency = HAL_RCC_USART6_GetKernelClkFreq();
      break;
#endif /* USART6 */

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for UART/LPUART
  * @param  uartx UART instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_UART_GetKernelClkFreq(const USART_TypeDef *uartx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)uartx)
  {
    case (uint32_t)USART1:
      frequency = HAL_RCC_USART1_GetKernelClkFreq();
      break;

#if defined(USART2)
    case (uint32_t)USART2:
      frequency = HAL_RCC_USART2_GetKernelClkFreq();
      break;
#endif /* USART2 */

    case (uint32_t)USART3:
      frequency = HAL_RCC_USART3_GetKernelClkFreq();
      break;

    case (uint32_t)UART4:
      frequency = HAL_RCC_UART4_GetKernelClkFreq();
      break;

    case (uint32_t)UART5:
      frequency = HAL_RCC_UART5_GetKernelClkFreq();
      break;

#if defined(USART6)
    case (uint32_t)USART6:
      frequency = HAL_RCC_USART6_GetKernelClkFreq();
      break;
#endif /* USART6 */

    case (uint32_t)LPUART1:
      frequency = HAL_RCC_LPUART1_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for USART1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USART1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUSARTClockSource(LL_RCC_USART1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_USART1_CLKSOURCE_PCLK2:
      frequency = HAL_RCC_GetPCLK2Freq();
      break;

    case LL_RCC_USART1_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

#if defined(LSE_VALUE)
    case LL_RCC_USART1_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_USART1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    default:
      break;
  }

  return frequency;
}

#if defined (USART2)
/**
  * @brief  Return the peripheral clock frequency for USART2
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USART2_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUSARTClockSource(LL_RCC_USART2_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_USART2_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_USART2_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

#if defined(LSE_VALUE)
    case LL_RCC_USART2_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_USART2_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    default:
      break;
  }

  return frequency;
}
#endif /* USART2 */

/**
  * @brief  Return the peripheral clock frequency for USART3
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USART3_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUSARTClockSource(LL_RCC_USART3_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_USART3_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_USART3_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

#if defined(LSE_VALUE)
    case LL_RCC_USART3_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_USART3_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for UART4
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_UART4_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUARTClockSource(LL_RCC_UART4_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_UART4_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_UART4_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

#if defined(LSE_VALUE)
    case LL_RCC_UART4_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_UART4_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for UART5
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_UART5_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUARTClockSource(LL_RCC_UART5_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_UART5_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_UART5_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

#if defined(LSE_VALUE)
    case LL_RCC_UART5_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_UART5_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    default:
      break;
  }

  return frequency;
}

#if defined(USART6)
/**
  * @brief  Return the peripheral clock frequency for USART6
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USART6_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUSARTClockSource(LL_RCC_USART6_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_USART6_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_USART6_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

#if defined(LSE_VALUE)
    case LL_RCC_USART6_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_USART6_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    default:
      break;
  }

  return frequency;
}
#endif /* USART6 */

/**
  * @brief  Return the peripheral clock frequency for LPUART1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_LPUART1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_LPUART1_CLKSOURCE_PCLK3:
      frequency = HAL_RCC_GetPCLK3Freq();
      break;

    case LL_RCC_LPUART1_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

    case LL_RCC_LPUART1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

#if defined(LSE_VALUE)
    case LL_RCC_LPUART1_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_LPUART1_CLKSOURCE_MSIK:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for ADC
  * @param  adcx ADC instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_ADC_GetKernelClkFreq(const ADC_TypeDef *adcx)
{
  STM32_UNUSED(adcx);

  return HAL_RCC_ADCDAC_GetKernelClkFreq();
}

/**
  * @brief  Return the peripheral clock frequency for DAC
  * @param  dacx DAC instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_DAC_GetKernelClkFreq(const DAC_TypeDef *dacx)
{
  STM32_UNUSED(dacx);

  return HAL_RCC_ADCDAC_GetKernelClkFreq();
}

/**
  * @brief  Return the peripheral clock frequency for ADCDAC
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_ADCDAC_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetADCDACClockSource(LL_RCC_ADCDAC_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll2_clocks;

  switch (srcclk)
  {
    case LL_RCC_ADCDAC_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

    case LL_RCC_ADCDAC_CLKSOURCE_PLL2:
      /* Clock source is on PLL2 output R */
      HAL_RCC_PLL2_GetClockFreq(&pll2_clocks);
      frequency = pll2_clocks.pll_r_freq;
      break;

    case LL_RCC_ADCDAC_CLKSOURCE_HCLK:
      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_ADCDAC_CLKSOURCE_MSIK:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;

#if defined(HSE_VALUE)
    case LL_RCC_ADCDAC_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */

    case LL_RCC_ADCDAC_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for MDF1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_MDF1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetMDF1ClockSource(LL_RCC_MDF1_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_MDF1_CLKSOURCE_HCLK:
      frequency = HAL_RCC_GetHCLKFreq();
      break;

#if defined(EXTERNAL_SAI1_CLOCK_VALUE)
    case LL_RCC_MDF1_CLKSOURCE_PIN:
      frequency = EXTERNAL_SAI1_CLOCK_VALUE;
      break;
#endif /* EXTERNAL_SAI1_CLOCK_VALUE */

    case LL_RCC_MDF1_CLKSOURCE_MSIK:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;

    case LL_RCC_MDF1_CLKSOURCE_PLL1:
      /* Clock source on PLL1 output P */
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_MDF1_CLKSOURCE_PLL3:
      /* Clock source on PLL3 output Q */
      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for ADF1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_ADF1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetADF1ClockSource(LL_RCC_ADF1_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_ADF1_CLKSOURCE_HCLK:
      frequency = HAL_RCC_GetHCLKFreq();
      break;

#if defined(EXTERNAL_SAI1_CLOCK_VALUE)
    case LL_RCC_ADF1_CLKSOURCE_PIN:
      frequency = EXTERNAL_SAI1_CLOCK_VALUE;
      break;
#endif /* EXTERNAL_SAI1_CLOCK_VALUE */

    case LL_RCC_ADF1_CLKSOURCE_MSIK:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;

    case LL_RCC_ADF1_CLKSOURCE_PLL1:
      /* Clock source on PLL1 output P */
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_ADF1_CLKSOURCE_PLL3:
      /* Clock source on PLL3 output Q */
      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for I2C/SMBUS
  * @param  i2cx I2C instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_I2C_GetKernelClkFreq(const I2C_TypeDef *i2cx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)i2cx)
  {
    case (uint32_t)I2C1:
      frequency = HAL_RCC_I2C1_GetKernelClkFreq();
      break;

    case (uint32_t)I2C2:
      frequency = HAL_RCC_I2C2_GetKernelClkFreq();
      break;

    case (uint32_t)I2C3:
      frequency = HAL_RCC_I2C3_GetKernelClkFreq();
      break;

    case (uint32_t)I2C4:
      frequency = HAL_RCC_I2C4_GetKernelClkFreq();
      break;

#if defined(I2C5)
    case (uint32_t)I2C5:
      frequency = HAL_RCC_I2C5_GetKernelClkFreq();
      break;
#endif /* I2C5 */

#if defined(I2C6)
    case (uint32_t)I2C6:
      frequency = HAL_RCC_I2C6_GetKernelClkFreq();
      break;
#endif /* I2C6 */

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for I2C1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_I2C1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_I2C1_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_I2C1_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

    case LL_RCC_I2C1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_I2C1_CLKSOURCE_MSIK:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for I2C2
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_I2C2_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C2_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_I2C2_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_I2C2_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

    case LL_RCC_I2C2_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_I2C2_CLKSOURCE_MSIK:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for I2C3
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_I2C3_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C3_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_I2C3_CLKSOURCE_PCLK3:
      frequency = HAL_RCC_GetPCLK3Freq();
      break;

    case LL_RCC_I2C3_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_I2C3_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

    case LL_RCC_I2C3_CLKSOURCE_MSIK:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for I2C4
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_I2C4_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C4_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_I2C4_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_I2C4_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

    case LL_RCC_I2C4_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_I2C4_CLKSOURCE_MSIK:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;

    default:
      break;
  }

  return frequency;
}

#if defined (I2C5)
/**
  * @brief  Return the peripheral clock frequency for I2C5
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_I2C5_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C5_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_I2C5_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_I2C5_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

    case LL_RCC_I2C5_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_I2C5_CLKSOURCE_MSIK:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;

    default:
      break;
  }

  return frequency;
}
#endif /* I2C5 */

#if defined (I2C6)
/**
  * @brief  Return the peripheral clock frequency for I2C6
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_I2C6_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C6_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_I2C6_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_I2C6_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

    case LL_RCC_I2C6_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_I2C6_CLKSOURCE_MSIK:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;

    default:
      break;
  }

  return frequency;
}
#endif /* I2C6 */

/**
  * @brief  Return the peripheral clock frequency for TIM
  * @param  timx TIM instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_TIM_GetKernelClkFreq(const TIM_TypeDef *timx)
{
  uint32_t frequency = 0U;

  if (IS_TIM_APB1_INSTANCE(timx) != 0U)
  {
    frequency = HAL_RCC_GetPCLK1Freq();

    if (LL_RCC_GetAPB1Prescaler() != LL_RCC_APB1_PRESCALER_1)
    {
      frequency = frequency << 1UL;
    }
  }
  else if (IS_TIM_APB2_INSTANCE(timx) != 0U)
  {
    frequency = HAL_RCC_GetPCLK2Freq();

    if (LL_RCC_GetAPB2Prescaler() != LL_RCC_APB2_PRESCALER_1)
    {
      frequency = frequency << 1UL;
    }
  }
  else
  {
    /* Do nothing */
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for LPTIM
  * @param  lptimx LPTIM instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_LPTIM_GetKernelClkFreq(const LPTIM_TypeDef *lptimx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)lptimx)
  {
    case (uint32_t)LPTIM1:
      frequency = HAL_RCC_LPTIM1_GetKernelClkFreq();
      break;

    case (uint32_t)LPTIM2:
      frequency = HAL_RCC_LPTIM2_GetKernelClkFreq();
      break;

    case (uint32_t)LPTIM3:
    case (uint32_t)LPTIM4:
      frequency = HAL_RCC_LPTIM34_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for LPTIM34
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_LPTIM34_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM34_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_LPTIM34_CLKSOURCE_MSIK:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;

    case LL_RCC_LPTIM34_CLKSOURCE_LSI:
      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = RCC_GET_LSI_FREQUENCY();
      }
      break;

#if defined(LSE_VALUE)
    case LL_RCC_LPTIM34_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_LPTIM34_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for LPTIM1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_LPTIM1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_LPTIM1_CLKSOURCE_MSIK:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;

    case LL_RCC_LPTIM1_CLKSOURCE_LSI:
      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = RCC_GET_LSI_FREQUENCY();
      }
      break;

#if defined(LSE_VALUE)
    case LL_RCC_LPTIM1_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_LPTIM1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for LPTIM2
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_LPTIM2_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM2_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_LPTIM2_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_LPTIM2_CLKSOURCE_LSI:
      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = RCC_GET_LSI_FREQUENCY();
      }
      break;

#if defined(LSE_VALUE)
    case LL_RCC_LPTIM2_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_LPTIM2_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for FDCAN
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_FDCAN_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetFDCANClockSource(LL_RCC_FDCAN_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_FDCAN_CLKSOURCE_PLL1:
      /* Clock source is on PLL1 output Q */
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

#if defined(HSE_VALUE)
    case LL_RCC_FDCAN_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */

    case LL_RCC_FDCAN_CLKSOURCE_PLL2:
      /* Clock source is on PLL2 output P */
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI
  * @param  spix SPI instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI_GetKernelClkFreq(const SPI_TypeDef *spix)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)spix)
  {
    case (uint32_t)SPI1:
      frequency = HAL_RCC_SPI1_GetKernelClkFreq();
      break;

    case (uint32_t)SPI2:
      frequency = HAL_RCC_SPI2_GetKernelClkFreq();
      break;

    case (uint32_t)SPI3:
      frequency = HAL_RCC_SPI3_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_SPI1_CLKSOURCE_PCLK2:

      frequency = HAL_RCC_GetPCLK2Freq();
      break;

    case LL_RCC_SPI1_CLKSOURCE_SYSCLK:

      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

    case LL_RCC_SPI1_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_SPI1_CLKSOURCE_MSIK:
    default:

      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI2
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI2_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI2_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_SPI2_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_SPI2_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

    case LL_RCC_SPI2_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_SPI2_CLKSOURCE_MSIK:
    default:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI3
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI3_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI3_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_SPI3_CLKSOURCE_PCLK3:
      frequency = HAL_RCC_GetPCLK3Freq();
      break;

    case LL_RCC_SPI3_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

    case LL_RCC_SPI3_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_SPI3_CLKSOURCE_MSIK:
    default:
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for XSPI
  * @param  xspix XSPI instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_XSPI_GetKernelClkFreq(const XSPI_TypeDef *xspix)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)xspix)
  {
    case (uint32_t)OCTOSPI1:
      frequency = HAL_RCC_OCTOSPI_GetKernelClkFreq();
      break;

#if defined(OCTOSPI2)
    case (uint32_t)OCTOSPI2:
      frequency = HAL_RCC_OCTOSPI_GetKernelClkFreq();
      break;
#endif /* OCTOSPI2 */

#if defined(HSPI1)
    case (uint32_t)HSPI1:
      frequency = HAL_RCC_HSPI1_GetKernelClkFreq();
      break;
#endif /* HSPI1 */

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for OCTOSPI
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_OCTOSPI_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetOCTOSPIClockSource(LL_RCC_OCTOSPI_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_OCTOSPI_CLKSOURCE_PLL2:
      /* Clock source is on PLL2 output Q */
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_OCTOSPI_CLKSOURCE_PLL1:
      /* Clock source is on PLL1 output Q */
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_OCTOSPI_CLKSOURCE_SYSCLK:

      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

    case LL_RCC_OCTOSPI_CLKSOURCE_MSIK:
    default:

      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        frequency = RCC_GET_MSIK_FREQUENCY();
      }
      break;
  }

  return frequency;
}

#if defined(HSPI1)
/**
  * @brief  Return the peripheral clock frequency for HSPI1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_HSPI1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetHSPIClockSource(LL_RCC_HSPI_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_HSPI_CLKSOURCE_SYSCLK:
      frequency = HAL_RCC_GetSYSCLKFreq();
      break;

    case LL_RCC_HSPI_CLKSOURCE_PLL3:
      /* Clock source on PLL3 output R */
      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_HSPI_CLKSOURCE_PLL1:
      /* Clock source on PLL1 output Q */
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_HSPI_CLKSOURCE_PLL2:
      /* Clock source on PLL2 output Q */
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    default:
      break;
  }

  return frequency;
}
#endif /* defined(HSPI1) */

/**
  * @brief  Return the peripheral clock frequency for DAC1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC1_GetSampleHoldClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDAC1ClockSource(LL_RCC_DAC1_CLKSOURCE);

  /* Check if LSI is ready and if DAC1 clock selection is LSI */
  if ((LL_RCC_LSI_IsReady() != 0U) && (srcclk == LL_RCC_DAC1_CLKSOURCE_LSI))
  {
    frequency = RCC_GET_LSI_FREQUENCY();
  }
#if defined(LSE_VALUE)
  /* Check if LSE is ready and if DAC1 clock selection is LSE */
  else
  {
    if ((LL_RCC_LSE_IsReady() != 0U) && (srcclk == LL_RCC_DAC1_CLKSOURCE_LSE))
    {
      frequency = LSE_VALUE;
    }
  }
#endif /* LSE_VALUE */

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for RNG
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_RNG_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetRNGClockSource(LL_RCC_RNG_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_RNG_CLKSOURCE_HSI48:
      if (LL_RCC_HSI48_IsReady() != 0U)
      {
        frequency = HSI48_VALUE;
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_HSI48_DIV2:
      if (LL_RCC_HSI48_IsReady() != 0U)
      {
        frequency = HSI48_VALUE >> 1U;
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = HSI_VALUE;
      }
      break;

    default:
      break;
  }

  return frequency;
}

#if defined(LTDC)
/**
  * @brief  Return the peripheral clock frequency for LTDC
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (PLL not ready)
  */
uint32_t HAL_RCC_LTDC_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetLTDCClockSource(LL_RCC_LTDC_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  if (srcclk == LL_RCC_LTDC_CLKSOURCE_PLL3)
  {
    /* Clock source is on PLL3 output R */
    HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
    frequency = pll_clocks.pll_r_freq;
  }
  else if (srcclk == LL_RCC_LTDC_CLKSOURCE_PLL2)
  {
    /* Clock source is on PLL2 output R */
    HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
    frequency = pll_clocks.pll_r_freq;
  }
  else
  {
    /* Do nothing */
  }

  return frequency;
}
#endif /* defined(LTDC) */

#if defined(DSI)
/**
  * @brief  Return the peripheral clock frequency for DSI
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (PLL3Q not ready or internal DSI PHY PLL using HSE)
  */
uint32_t HAL_RCC_DSI_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDSIClockSource(LL_RCC_DSI_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  if (srcclk == LL_RCC_DSI_CLKSOURCE_PLL3)
  {
    /* Clock source is on PLL3 output P */
    HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
    frequency = pll_clocks.pll_p_freq;
  }
  /* else LL_RCC_DSI_CLKSOURCE_PHY then frequency cannot be calculated */

  return frequency;
}
#endif /* defined(DSI) */

#if defined(USB_OTG_HS)
/**
  * @brief  Return the peripheral clock frequency for USB HS PHY
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_USBHSPHY_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUSBHSPHYClockSource(LL_RCC_USBHSPHY_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_USBHSPHYCLKSOURCE_PLL1:
      /* Clock source is on PLL1 output P */
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

#if defined(HSE_VALUE)
    case LL_RCC_USBHSPHYCLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;

    case LL_RCC_USBHSPHYCLKSOURCE_HSE_DIV2:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE >> 1U;
      }
      break;
#endif /* HSE_VALUE */

    case LL_RCC_USBHSPHYCLKSOURCE_PLL1_DIV2:
      /* Clock source is on PLL1 output P */
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = (pll_clocks.pll_p_freq) / 2U;
      break;

    default:
      break;
  }

  return frequency;
}
#endif /* defined(USB_OTG_HS) */

/**
  * @}
  */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @addtogroup RCC_Private_Functions
  * @{
  */
/** @brief  Wait for clock timeout
  * @param  p_timeout_cb Callback on the timeout function
  * @param  timeout      Timeout value
  * @param  status       Status to be checked
  * @retval HAL_OK       Not timeout detected
  * @retval HAL_ERROR    Timeout detected during clock activation or deactivation
  */
static hal_status_t RCC_WaitForTimeout(const rcc_cb_timeout_t p_timeout_cb, uint32_t timeout, uint32_t status)
{
  uint32_t tickstart;
  hal_status_t hal_status = HAL_OK;
  tickstart = HAL_GetTick();

  while (p_timeout_cb() != status)
  {
    if ((HAL_GetTick() - tickstart) > timeout)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (p_timeout_cb() != status)
      {
        hal_status = HAL_ERROR;
        break;
      }
    }
  }

  return hal_status;
}

/**
  * @brief   Configure PLLx without enabling outputs.
  * @details The config function will perform the following actions:
  *           - Check if PLLx is well deactivated (if enabled exit from this function)
  *           - Configure the PLLx with full list of parameters
  * @param pll_id   ID on the targeted PLLx (PLL1, PLL2 or PLL3)
  * @param p_config pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLLx
  * @retval HAL_OK            PLLx has been correctly configured\n
  * @retval HAL_ERROR         PLLx is already enabled and can not be modified.
  */
static hal_status_t RCC_PLL_SetConfig(rcc_pll_id_t pll_id, const hal_rcc_pll_config_t *p_config)
{
  hal_status_t status = HAL_ERROR;

  /*
    The config function will perform the following actions:
    - Check if PLLx is well deactivated (if enabled exit from this function)
    - Configure the PLLx with full list of parameters
  */
  if ((READ_BIT(RCC->CR, (1UL << (RCC_CR_PLL1RDY_Pos + ((uint32_t)pll_id * 2U))))) == 0U)
  {
    uint32_t pllvco = 0U;
    volatile uint32_t *p_addr_pllcfgr;
    volatile uint32_t *p_addr_reg2;

    /* Configure the main PLL clock source, multiplication and division factors */
    p_addr_pllcfgr = (volatile uint32_t *)((uint32_t)&RCC->PLL1CFGR + ((uint32_t)pll_id * 4U));
    /* PLL1MBOOST only available for PLL1 */
    if (pll_id == PLL_1)
    {
      MODIFY_REG(RCC->PLL1CFGR, (RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1M | RCC_PLL1CFGR_PLL1MBOOST),
                 ((uint32_t)p_config->pll_source << (uint32_t)RCC_PLL1CFGR_PLL1SRC_Pos)
                 | ((uint32_t)(p_config->pll_m - 1UL)  << (uint32_t)RCC_PLL1CFGR_PLL1M_Pos)
                 | (uint32_t)p_config->pll_m_boost);
    }
    else
    {
      MODIFY_REG(*p_addr_pllcfgr, (RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1M),
                 ((uint32_t)p_config->pll_source << RCC_PLL1CFGR_PLL1SRC_Pos)
                 | ((uint32_t)(p_config->pll_m - 1UL) << RCC_PLL1CFGR_PLL1M_Pos));

    }

    p_addr_reg2 = (volatile uint32_t *)((uint32_t)&RCC->PLL1DIVR + ((uint32_t)pll_id * 8U));
    MODIFY_REG(*p_addr_reg2, (RCC_PLL1DIVR_PLL1N | RCC_PLL1DIVR_PLL1P | RCC_PLL1DIVR_PLL1Q | RCC_PLL1DIVR_PLL1R),
               (((uint32_t)(p_config->pll_n - 1UL) & RCC_PLL1DIVR_PLL1N) |
                (((uint32_t)(p_config->pll_p - 1UL) << RCC_PLL1DIVR_PLL1P_Pos) & RCC_PLL1DIVR_PLL1P) |
                (((uint32_t)(p_config->pll_q - 1UL) << RCC_PLL1DIVR_PLL1Q_Pos) & RCC_PLL1DIVR_PLL1Q) |
                (((uint32_t)(p_config->pll_r - 1UL) << RCC_PLL1DIVR_PLL1R_Pos) & RCC_PLL1DIVR_PLL1R)));

    CLEAR_BIT(*p_addr_pllcfgr, RCC_PLL1CFGR_PLL1FRACEN);

    /* Configure PLL PLLxFRACN */
    p_addr_reg2 = (volatile uint32_t *)((uint32_t)&RCC->PLL1FRACR + ((uint32_t)pll_id * 8U));
    MODIFY_REG(*p_addr_reg2, RCC_PLL1FRACR_PLL1FRACN,
               ((uint32_t)p_config->pll_fracn << (uint32_t)RCC_PLL1FRACR_PLL1FRACN_Pos));

    SET_BIT(*p_addr_pllcfgr, RCC_PLL1CFGR_PLL1FRACEN);

    /* Configure VCO input depending on the PLLx source and divider M
        - if VCO input higher than 8MHz => RGE = 1 */
    switch (p_config->pll_source)
    {
#if defined(HSE_VALUE)
      case HAL_RCC_PLL_SRC_HSE:  /* HSE used as PLL clock source */
        pllvco = HSE_VALUE / p_config->pll_m;
        break;
#endif /* HSE_VALUE */
      case HAL_RCC_PLL_SRC_HSI:  /* HSI used as PLL clock source */
        pllvco = HSI_VALUE / p_config->pll_m;
        break;
      case HAL_RCC_PLL_SRC_MSIS:  /* MSI used as PLL clock source */
        pllvco = RCC_GET_MSIS_FREQUENCY()
                 / p_config->pll_m;
        break;
      default:
        break;
    }

    if (pllvco >= 8000000U)
    {
      /* Select PLL1 input reference frequency range: VCI */
      MODIFY_REG(*p_addr_pllcfgr, RCC_PLL1CFGR_PLL1RGE, LL_RCC_PLLINPUTRANGE_8_16);
    }
    else
    {
      /* Select PLL2/PLL3 input reference frequency range: VCI */
      MODIFY_REG(*p_addr_pllcfgr, RCC_PLL1CFGR_PLL1RGE, LL_RCC_PLLINPUTRANGE_4_8);
    }

    status = HAL_OK;
  }
  return status;
}

/**
  * @brief Return the configuration of PLLx.
  * @param pll_id    ID on the targeted PLLx (PLL1, PLL2 or PLL3)
  * @param p_config  pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLLx
  */
static void RCC_PLL_GetConfig(rcc_pll_id_t pll_id, hal_rcc_pll_config_t *p_config)
{
  uint32_t temp_reg;

  /* Read PLL1CFGR register */
  temp_reg = (uint32_t) * (READ_REG((volatile uint32_t *)((uint32_t)&RCC->PLL1CFGR + ((uint32_t)pll_id * 4U))));
  p_config->pll_source  = (hal_rcc_pll_src_t)(uint32_t)(READ_BIT(temp_reg, RCC_PLL1CFGR_PLL1SRC));
  p_config->pll_m       = (uint8_t)((READ_BIT(temp_reg, RCC_PLL1CFGR_PLL1M) >>  RCC_PLL1CFGR_PLL1M_Pos) + 1UL);
  /* PLL1MBOOST only available for PLL1 */
  if (pll_id == PLL_1)
  {
    p_config->pll_m_boost = (hal_rcc_pll_mboost_div_t)(uint32_t)(READ_BIT(temp_reg, RCC_PLL1CFGR_PLL1MBOOST));
  }

  /* Read PLL1DIVR register */
  temp_reg = (uint32_t) * (READ_REG((volatile uint32_t *)((uint32_t)&RCC->PLL1DIVR + ((uint32_t)pll_id * 8U))));
  p_config->pll_n = (uint16_t)((READ_BIT(temp_reg, RCC_PLL1DIVR_PLL1N) >>  RCC_PLL1DIVR_PLL1N_Pos) + 1UL);
  p_config->pll_p = (uint8_t)((READ_BIT(temp_reg, RCC_PLL1DIVR_PLL1P) >>  RCC_PLL1DIVR_PLL1P_Pos) + 1UL);
  p_config->pll_q = (uint8_t)((READ_BIT(temp_reg, RCC_PLL1DIVR_PLL1Q) >>  RCC_PLL1DIVR_PLL1Q_Pos) + 1UL);
  p_config->pll_r = (uint8_t)((READ_BIT(temp_reg, RCC_PLL1DIVR_PLL1R) >>  RCC_PLL1DIVR_PLL1R_Pos) + 1UL);

  /* Read PLL1FRACN register */
  temp_reg = (uint32_t) * (READ_REG((volatile uint32_t *)((uint32_t)&RCC->PLL1FRACR + ((uint32_t)pll_id * 8U))));
  p_config->pll_fracn = (uint16_t)(READ_BIT(temp_reg, RCC_PLL1FRACR_PLL1FRACN) >>  RCC_PLL1FRACR_PLL1FRACN_Pos);
}

/**
  * @}
  */

#endif /* USE_HAL_RCC_MODULE */
/**
  * @}
  */

/**
  * @}
  */
