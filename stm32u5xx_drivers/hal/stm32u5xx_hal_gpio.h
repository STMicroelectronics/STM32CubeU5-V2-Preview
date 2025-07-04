/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_gpio.h
  * @brief   Header file of GPIO HAL module.
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
#ifndef STM32U5XX_HAL_GPIO_H
#define STM32U5XX_HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_gpio.h"
#include "stm32u5xx_ll_lpgpio.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup GPIO GPIO
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/

/** @defgroup GPIO_Exported_Types HAL GPIO Types
  * @{
  */

/**
  * @brief HAL GPIO instance
  */
typedef enum
{
  HAL_GPIOA = (uint32_t)GPIOA,     /*!< GPIO port A */
  HAL_GPIOB = (uint32_t)GPIOB,     /*!< GPIO port B */
  HAL_GPIOC = (uint32_t)GPIOC,     /*!< GPIO port C */
  HAL_GPIOD = (uint32_t)GPIOD,     /*!< GPIO port D */
  HAL_GPIOE = (uint32_t)GPIOE,     /*!< GPIO port E */
#if defined (GPIOF)
  HAL_GPIOF = (uint32_t)GPIOF,     /*!< GPIO port F */
#endif /* GPIOF */
  HAL_GPIOG = (uint32_t)GPIOG,     /*!< GPIO port G */
  HAL_GPIOH = (uint32_t)GPIOH,     /*!< GPIO port H */
#if defined (GPIOI)
  HAL_GPIOI = (uint32_t)GPIOI,     /*!< GPIO port I */
#endif /* GPIOI */
#if defined (GPIOJ)
  HAL_GPIOJ = (uint32_t)GPIOJ,     /*!< GPIO port J */
#endif /* GPIOJ */
  HAL_LPGPIO1 = (uint32_t)LPGPIO1, /*!< LPGPIO port */
} hal_gpio_t;

/**
  * @brief HAL GPIO mode
  */
typedef enum
{
  HAL_GPIO_MODE_INPUT     =  LL_GPIO_MODE_INPUT,      /*!< Input Floating mode */
  HAL_GPIO_MODE_OUTPUT    =  LL_GPIO_MODE_OUTPUT,     /*!< Output mode         */
  HAL_GPIO_MODE_ALTERNATE =  LL_GPIO_MODE_ALTERNATE,  /*!< Alternate mode      */
  HAL_GPIO_MODE_ANALOG    =  LL_GPIO_MODE_ANALOG      /*!< Analog mode         */
} hal_gpio_mode_t;

/**
  * @brief HAL GPIO Output Type
  */
typedef enum
{
  HAL_GPIO_OUTPUT_PUSHPULL  = LL_GPIO_OUTPUT_PUSHPULL,   /*!< Select push-pull as output type  */
  HAL_GPIO_OUTPUT_OPENDRAIN = LL_GPIO_OUTPUT_OPENDRAIN   /*!< Select open-drain as output type */
} hal_gpio_output_t;

/**
  * @brief HAL GPIO speed
  * @note  Refer to the device datasheet for the frequency specifications, and the power supply and load conditions
  *        for each speed.
  */
typedef enum
{
  HAL_GPIO_SPEED_FREQ_LOW        = LL_GPIO_SPEED_FREQ_LOW,        /*!< Low speed       */
  HAL_GPIO_SPEED_FREQ_MEDIUM     = LL_GPIO_SPEED_FREQ_MEDIUM,     /*!< Medium speed    */
  HAL_GPIO_SPEED_FREQ_HIGH       = LL_GPIO_SPEED_FREQ_HIGH,       /*!< High speed      */
  HAL_GPIO_SPEED_FREQ_VERY_HIGH  = LL_GPIO_SPEED_FREQ_VERY_HIGH   /*!< Very-high speed */
} hal_gpio_speed_freq_t;

/**
  * @brief HAL GPIO pull
  */
typedef enum
{
  HAL_GPIO_PULL_NO   = LL_GPIO_PULL_NO,   /*!< No Pull-up or Pull-down activation  */
  HAL_GPIO_PULL_UP   = LL_GPIO_PULL_UP,   /*!< Pull-up activation                  */
  HAL_GPIO_PULL_DOWN = LL_GPIO_PULL_DOWN  /*!< Pull-down activation                */
} hal_gpio_pull_t;

/**
  * @brief HAL GPIO Alternate function
  */
typedef enum
{
  HAL_GPIO_AF_0  = LL_GPIO_AF_0,  /*!< Select alternate function 0  */
  HAL_GPIO_AF_1  = LL_GPIO_AF_1,  /*!< Select alternate function 1  */
  HAL_GPIO_AF_2  = LL_GPIO_AF_2,  /*!< Select alternate function 2  */
  HAL_GPIO_AF_3  = LL_GPIO_AF_3,  /*!< Select alternate function 3  */
  HAL_GPIO_AF_4  = LL_GPIO_AF_4,  /*!< Select alternate function 4  */
  HAL_GPIO_AF_5  = LL_GPIO_AF_5,  /*!< Select alternate function 5  */
  HAL_GPIO_AF_6  = LL_GPIO_AF_6,  /*!< Select alternate function 6  */
  HAL_GPIO_AF_7  = LL_GPIO_AF_7,  /*!< Select alternate function 7  */
  HAL_GPIO_AF_8  = LL_GPIO_AF_8,  /*!< Select alternate function 8  */
  HAL_GPIO_AF_9  = LL_GPIO_AF_9,  /*!< Select alternate function 9  */
  HAL_GPIO_AF_10 = LL_GPIO_AF_10, /*!< Select alternate function 10 */
  HAL_GPIO_AF_11 = LL_GPIO_AF_11, /*!< Select alternate function 11 */
  HAL_GPIO_AF_12 = LL_GPIO_AF_12, /*!< Select alternate function 12 */
  HAL_GPIO_AF_13 = LL_GPIO_AF_13, /*!< Select alternate function 13 */
  HAL_GPIO_AF_14 = LL_GPIO_AF_14, /*!< Select alternate function 14 */
  HAL_GPIO_AF_15 = LL_GPIO_AF_15  /*!< Select alternate function 15 */
} hal_gpio_af_t;

/**
  * @brief  GPIO Bit SET and Bit RESET enumeration
  */
typedef enum
{
  HAL_GPIO_PIN_RESET = 0U,  /*!< Pin state is reset/low */
  HAL_GPIO_PIN_SET   = 1U   /*!< Pin state is set/high  */
} hal_gpio_pin_state_t;

/**
  * @brief   GPIO Init structure definition
  */
typedef struct
{
  hal_gpio_mode_t       mode;            /*!< Specifies the operating mode for the selected pins */
  hal_gpio_pull_t       pull;            /*!< Specifies the Pull-up or Pull-Down activation for the selected pins */
  hal_gpio_speed_freq_t speed;           /*!< Specifies the speed for the selected pins */
  hal_gpio_output_t     output_type;     /*!< Specifies the operating output type for the selected pins */
  hal_gpio_af_t         alternate;       /*!< Specifies the alternate function for the selected pins */
  hal_gpio_pin_state_t  init_state;      /*!< Specifies the initial state Set or Reset for the selected pins */
} hal_gpio_config_t;

/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Constants HAL GPIO Constants
  * @{
  */

/** @defgroup GPIO_pins GPIO pins
  * @{
  */

#define HAL_GPIO_PIN_0                 LL_GPIO_PIN_0    /*!< GPIO pin 0  */
#define HAL_GPIO_PIN_1                 LL_GPIO_PIN_1    /*!< GPIO pin 1  */
#define HAL_GPIO_PIN_2                 LL_GPIO_PIN_2    /*!< GPIO pin 2  */
#define HAL_GPIO_PIN_3                 LL_GPIO_PIN_3    /*!< GPIO pin 3  */
#define HAL_GPIO_PIN_4                 LL_GPIO_PIN_4    /*!< GPIO pin 4  */
#define HAL_GPIO_PIN_5                 LL_GPIO_PIN_5    /*!< GPIO pin 5  */
#define HAL_GPIO_PIN_6                 LL_GPIO_PIN_6    /*!< GPIO pin 6  */
#define HAL_GPIO_PIN_7                 LL_GPIO_PIN_7    /*!< GPIO pin 7  */
#define HAL_GPIO_PIN_8                 LL_GPIO_PIN_8    /*!< GPIO pin 8  */
#define HAL_GPIO_PIN_9                 LL_GPIO_PIN_9    /*!< GPIO pin 9  */
#define HAL_GPIO_PIN_10                LL_GPIO_PIN_10   /*!< GPIO pin 10 */
#define HAL_GPIO_PIN_11                LL_GPIO_PIN_11   /*!< GPIO pin 11 */
#define HAL_GPIO_PIN_12                LL_GPIO_PIN_12   /*!< GPIO pin 12 */
#define HAL_GPIO_PIN_13                LL_GPIO_PIN_13   /*!< GPIO pin 13 */
#define HAL_GPIO_PIN_14                LL_GPIO_PIN_14   /*!< GPIO pin 14 */
#define HAL_GPIO_PIN_15                LL_GPIO_PIN_15   /*!< GPIO pin 15 */
#define HAL_GPIO_PIN_ALL               LL_GPIO_PIN_ALL  /*!< GPIO pin all*/
/**
  * @}
  */

/** @defgroup GPIO_Alternates GPIO Alternates
  * @{
  */
/**
  * @brief   AF 0 selection
  */
#define HAL_GPIO_AF0_CSLEEP              HAL_GPIO_AF_0 /*!< CSLEEP mode                       */
#define HAL_GPIO_AF0_CSTOP               HAL_GPIO_AF_0 /*!< CSTOP mode                        */
#define HAL_GPIO_AF0_CDSTOP              HAL_GPIO_AF_0 /*!< CDSTOP mode                       */
#define HAL_GPIO_AF0_CRS                 HAL_GPIO_AF_0 /*!< CRS Alternate Function mapping    */
#define HAL_GPIO_AF0_CRS_SYNC            HAL_GPIO_AF_0 /*!< CRS synchronization               */
#define HAL_GPIO_AF0_LPTIM1              HAL_GPIO_AF_0 /*!< LPTIM1 Alternate Function mapping */
#define HAL_GPIO_AF0_LPTIM1_CH2          HAL_GPIO_AF_0 /*!< LPTIM1 Multi-purpose Channel 2    */
#define HAL_GPIO_AF0_MCO                 HAL_GPIO_AF_0 /*!< MCO (MCO1 and MCO2                */
#define HAL_GPIO_AF0_SRDSTOP             HAL_GPIO_AF_0 /*!< SRDSTOP mode                      */
#define HAL_GPIO_AF0_RTC_REFIN           HAL_GPIO_AF_0 /*!< RTC Reference input               */
#define HAL_GPIO_AF0_SWJ                 HAL_GPIO_AF_0 /*!< SWJ (SWD and JTAG)                */
#define HAL_GPIO_AF0_TRACECLK            HAL_GPIO_AF_0 /*!< TRACE Clock                       */
#define HAL_GPIO_AF0_TRACED0             HAL_GPIO_AF_0 /*!< TRACE Data Output 0               */
#define HAL_GPIO_AF0_TRACED1             HAL_GPIO_AF_0 /*!< TRACE Data Output 1               */
#define HAL_GPIO_AF0_TRACED2             HAL_GPIO_AF_0 /*!< TRACE Data Output 2               */
#define HAL_GPIO_AF0_TRACED3             HAL_GPIO_AF_0 /*!< TRACE Data Output 3               */

/**
  * @brief   AF 1 selection
  */
#define HAL_GPIO_AF1_TIM1                HAL_GPIO_AF_1 /*!< TIM1 Alternate Function mapping   */
#define HAL_GPIO_AF1_TIM1_BKIN           HAL_GPIO_AF_1 /*!< TIM1 Break input                  */
#define HAL_GPIO_AF1_TIM1_ETR            HAL_GPIO_AF_1 /*!< TIM1 External trigger input       */
#define HAL_GPIO_AF1_TIM1_CH1N           HAL_GPIO_AF_1 /*!< TIM1 CH1 complementary output     */
#define HAL_GPIO_AF1_TIM1_CH1            HAL_GPIO_AF_1 /*!< TIM1 Multi-purpose Channel 1      */
#define HAL_GPIO_AF1_TIM1_IN1            HAL_GPIO_AF_1 /*!< TIM1 Channel 1 Input              */
#define HAL_GPIO_AF1_TIM1_CH2N           HAL_GPIO_AF_1 /*!< TIM1 CH2 complementary output     */
#define HAL_GPIO_AF1_TIM1_CH2            HAL_GPIO_AF_1 /*!< TIM1 Multi-purpose Channel 2      */
#define HAL_GPIO_AF1_TIM1_IN2            HAL_GPIO_AF_1 /*!< TIM1 Channel 2 Input              */
#define HAL_GPIO_AF1_TIM1_CH3N           HAL_GPIO_AF_1 /*!< TIM1 CH3 complementary output     */
#define HAL_GPIO_AF1_TIM1_CH3            HAL_GPIO_AF_1 /*!< TIM1 Multi-purpose Channel 3      */
#define HAL_GPIO_AF1_TIM1_CH4N           HAL_GPIO_AF_1 /*!< TIM1 CH4 complementary output     */
#define HAL_GPIO_AF1_TIM1_CH4            HAL_GPIO_AF_1 /*!< TIM1 Multi-purpose Channel 4      */
#define HAL_GPIO_AF1_TIM2                HAL_GPIO_AF_1 /*!< TIM2 Alternate Function mapping   */
#define HAL_GPIO_AF1_TIM2_CH1            HAL_GPIO_AF_1 /*!< TIM2 Multi-purpose Channel 1      */
#define HAL_GPIO_AF1_TIM2_CH2            HAL_GPIO_AF_1 /*!< TIM2 Multi-purpose Channel 2      */
#define HAL_GPIO_AF1_TIM2_CH3            HAL_GPIO_AF_1 /*!< TIM2 Multi-purpose Channel 3      */
#define HAL_GPIO_AF1_TIM2_CH4            HAL_GPIO_AF_1 /*!< TIM2 Multi-purpose Channel 4      */
#define HAL_GPIO_AF1_TIM5                HAL_GPIO_AF_1 /*!< TIM5 Alternate Function mapping   */
#define HAL_GPIO_AF1_TIM5_ETR            HAL_GPIO_AF_1 /*!< TIM5 External trigger input       */
#define HAL_GPIO_AF1_TIM8                HAL_GPIO_AF_1 /*!< TIM8 Alternate Function mapping   */
#define HAL_GPIO_AF1_TIM8_BKIN           HAL_GPIO_AF_1 /*!< TIM8 Break input                  */
#define HAL_GPIO_AF1_LPTIM1              HAL_GPIO_AF_1 /*!< LPTIM1 Alternate Function mapping */
#define HAL_GPIO_AF1_LPTIM1_ETR          HAL_GPIO_AF_1 /*!< LPTIM1 External trigger input     */
#define HAL_GPIO_AF1_LPTIM1_CH1          HAL_GPIO_AF_1 /*!< LPTIM1 Multi-purpose Channel 1    */
#define HAL_GPIO_AF1_LPTIM1_IN1          HAL_GPIO_AF_1 /*!< LPTIM1 Channel 1 Input            */
#define HAL_GPIO_AF1_LPTIM1_CH2          HAL_GPIO_AF_1 /*!< LPTIM1 Multi-purpose Channel 2    */
#define HAL_GPIO_AF1_LPTIM1_IN2          HAL_GPIO_AF_1 /*!< LPTIM1 Channel 2 Input            */
#define HAL_GPIO_AF1_IR_OUT              HAL_GPIO_AF_1 /*!< Infrared output                   */

/**
  * @brief   AF 2 selection
  */
#define HAL_GPIO_AF2_TIM1                HAL_GPIO_AF_2 /*!< TIM1 Alternate Function mapping   */
#define HAL_GPIO_AF2_TIM1_BKIN2          HAL_GPIO_AF_2 /*!< TIM1 Break input 2                */
#define HAL_GPIO_AF2_TIM2                HAL_GPIO_AF_2 /*!< TIM2 Alternate Function mapping   */
#define HAL_GPIO_AF2_TIM2_ETR            HAL_GPIO_AF_2 /*!< TIM2 External trigger input       */
#define HAL_GPIO_AF2_TIM3                HAL_GPIO_AF_2 /*!< TIM3 Alternate Function mapping   */
#define HAL_GPIO_AF2_TIM3_ETR            HAL_GPIO_AF_2 /*!< TIM3 External trigger input       */
#define HAL_GPIO_AF2_TIM3_CH1            HAL_GPIO_AF_2 /*!< TIM3 Multi-purpose Channel 1      */
#define HAL_GPIO_AF2_TIM3_CH2            HAL_GPIO_AF_2 /*!< TIM3 Multi-purpose Channel 2      */
#define HAL_GPIO_AF2_TIM3_CH3            HAL_GPIO_AF_2 /*!< TIM3 Multi-purpose Channel 3      */
#define HAL_GPIO_AF2_TIM3_CH4            HAL_GPIO_AF_2 /*!< TIM3 Multi-purpose Channel 4      */
#define HAL_GPIO_AF2_TIM4                HAL_GPIO_AF_2 /*!< TIM4 Alternate Function mapping   */
#define HAL_GPIO_AF2_TIM4_ETR            HAL_GPIO_AF_2 /*!< TIM4 External trigger input       */
#define HAL_GPIO_AF2_TIM4_CH1            HAL_GPIO_AF_2 /*!< TIM4 Multi-purpose Channel 1      */
#define HAL_GPIO_AF2_TIM4_CH2            HAL_GPIO_AF_2 /*!< TIM3 Multi-purpose Channel 2      */
#define HAL_GPIO_AF2_TIM4_CH3            HAL_GPIO_AF_2 /*!< TIM3 Multi-purpose Channel 3      */
#define HAL_GPIO_AF2_TIM4_CH4            HAL_GPIO_AF_2 /*!< TIM3 Multi-purpose Channel 4      */
#define HAL_GPIO_AF2_TIM5                HAL_GPIO_AF_2 /*!< TIM5 Alternate Function mapping   */
#define HAL_GPIO_AF2_TIM5_CH1            HAL_GPIO_AF_2 /*!< TIM5 Multi-purpose Channel 1      */
#define HAL_GPIO_AF2_TIM5_CH2            HAL_GPIO_AF_2 /*!< TIM5 Multi-purpose Channel 2      */
#define HAL_GPIO_AF2_TIM5_CH3            HAL_GPIO_AF_2 /*!< TIM5 Multi-purpose Channel 3      */
#define HAL_GPIO_AF2_TIM5_CH4            HAL_GPIO_AF_2 /*!< TIM5 Multi-purpose Channel 4      */
#define HAL_GPIO_AF2_LPTIM1              HAL_GPIO_AF_2 /*!< LPTIM1 Alternate Function mapping */
#define HAL_GPIO_AF2_LPTIM1_CH1          HAL_GPIO_AF_2 /*!< LPTIM1 Multi-purpose Channel 1    */
#define HAL_GPIO_AF2_LPTIM2              HAL_GPIO_AF_2 /*!< LPTIM2 Alternate Function mapping */
#define HAL_GPIO_AF2_LPTIM2_CH2          HAL_GPIO_AF_2 /*!< LPTIM2 Multi-purpose Channel 2    */
#define HAL_GPIO_AF2_LPTIM2_IN2          HAL_GPIO_AF_2 /*!< LPTIM2 Channel 2 Input            */
#define HAL_GPIO_AF2_LPTIM3              HAL_GPIO_AF_2 /*!< LPTIM3 Alternate Function mapping */
#define HAL_GPIO_AF2_LPTIM3_ETR          HAL_GPIO_AF_2 /*!< LPTIM3 External trigger input     */
#define HAL_GPIO_AF2_LPTIM3_CH1          HAL_GPIO_AF_2 /*!< LPTIM3 Multi-purpose Channel 1    */
#define HAL_GPIO_AF2_LPTIM3_IN1          HAL_GPIO_AF_2 /*!< LPTIM3 Channel 1 Input            */
#define HAL_GPIO_AF2_LPTIM3_CH2          HAL_GPIO_AF_2 /*!< LPTIM3 Multi-purpose Channel 2    */
#if defined(I2C5)
#define HAL_GPIO_AF2_I2C5                HAL_GPIO_AF_2 /*!< I2C5 Alternate Function mapping   */
#define HAL_GPIO_AF2_I2C5_SCL            HAL_GPIO_AF_2 /*!< I2C5 Clock                        */
#define HAL_GPIO_AF2_I2C5_SDA            HAL_GPIO_AF_2 /*!< I2C5 Data                         */
#define HAL_GPIO_AF2_I2C5_SMBA           HAL_GPIO_AF_2 /*!< I2C5 SMBus Alert                  */
#endif /* I2C5 */
#if defined(I2C6)
#define HAL_GPIO_AF2_I2C6                HAL_GPIO_AF_2 /*!< I2C6 Alternate Function mapping   */
#define HAL_GPIO_AF2_I2C6_SCL            HAL_GPIO_AF_2 /*!< I2C6 Clock                        */
#define HAL_GPIO_AF2_I2C6_SDA            HAL_GPIO_AF_2 /*!< I2C6 Data                         */
#define HAL_GPIO_AF2_I2C6_SMBA           HAL_GPIO_AF_2 /*!< I2C6 SMBus Alert                  */
#endif /* I2C6 */
#if defined(GFXTIM)
#define HAL_GPIO_AF2_GFXTIM              HAL_GPIO_AF_2 /*!< GFXTIM Alternate Function mapping     */
#define HAL_GPIO_AF2_GFXTIM_LCKCAL       HAL_GPIO_AF_2 /*!< GFXTIM Line Clock Calibration Output  */
#define HAL_GPIO_AF2_GFXTIM_FCKCAL       HAL_GPIO_AF_2 /*!< GFXTIM Frame Clock Calibration Output */
#endif /* GFXTIM */

/**
  * @brief   AF 3 selection
  */
#define HAL_GPIO_AF3_I2C4                HAL_GPIO_AF_3 /*!< I2C4 Alternate Function mapping     */
#define HAL_GPIO_AF3_I2C4_SCL            HAL_GPIO_AF_3 /*!< I2C4 Clock                          */
#define HAL_GPIO_AF3_I2C4_SDA            HAL_GPIO_AF_3 /*!< I2C4 Data                           */
#define HAL_GPIO_AF3_OCTOSPIM_P1         HAL_GPIO_AF_3 /*!< OCTOSPIM_P1 Alternate Function mapping */
#define HAL_GPIO_AF3_OCTOSPIM_P1_NCS     HAL_GPIO_AF_3 /*!< OCTOSPIM_P1 Memory Chip Select         */
#define HAL_GPIO_AF3_OCTOSPIM_P1_NCLK    HAL_GPIO_AF_3 /*!< OCTOSPIM_P1 Inverted Clock             */
#define HAL_GPIO_AF3_OCTOSPIM_P1_CLK     HAL_GPIO_AF_3 /*!< OCTOSPIM_P1 Clock                      */
#define HAL_GPIO_AF3_OCTOSPIM_P1_DQS     HAL_GPIO_AF_3 /*!< OCTOSPIM_P1 Memory Data Strobe I/O     */
#define HAL_GPIO_AF3_OCTOSPIM_P1_IO5     HAL_GPIO_AF_3 /*!< OCTOSPIM_P1 Data Pin 5                 */
#define HAL_GPIO_AF3_OCTOSPIM_P1_IO7     HAL_GPIO_AF_3 /*!< OCTOSPIM_P1 Data Pin 7                 */
#define HAL_GPIO_AF3_SAI1                HAL_GPIO_AF_3 /*!< SAI1 Alternate Function mapping     */
#define HAL_GPIO_AF3_SAI1_CK1            HAL_GPIO_AF_3 /*!< SAI1 PDM Bitstream Clock 1          */
#define HAL_GPIO_AF3_SAI1_D1             HAL_GPIO_AF_3 /*!< SAI1 PDM Bitstream Data 1           */
#define HAL_GPIO_AF3_SAI1_CK2            HAL_GPIO_AF_3 /*!< SAI1 PDM Bitstream Clock 2          */
#define HAL_GPIO_AF3_SAI1_D2             HAL_GPIO_AF_3 /*!< SAI1 PDM Bitstream Data 2           */
#define HAL_GPIO_AF3_SAI1_D3             HAL_GPIO_AF_3 /*!< SAI1 PDM Bitstream Data3            */
#define HAL_GPIO_AF3_SPI2                HAL_GPIO_AF_3 /*!< SPI2 Alternate Function mapping     */
#define HAL_GPIO_AF3_SPI2_SCK            HAL_GPIO_AF_3 /*!< SPI2 Master Clock Output            */
#define HAL_GPIO_AF3_SPI2_MOSI           HAL_GPIO_AF_3 /*!< SPI2 Master-In/Slave-Out Data       */
#define HAL_GPIO_AF3_TIM1                HAL_GPIO_AF_3 /*!< TIM1 Alternate Function mapping     */
#define HAL_GPIO_AF3_TIM1_CH4N           HAL_GPIO_AF_3 /*!< TIM1 CH4 complementary output       */
#define HAL_GPIO_AF3_TIM8                HAL_GPIO_AF_3 /*!< TIM8 Alternate Function mapping     */
#define HAL_GPIO_AF3_TIM8_ETR            HAL_GPIO_AF_3 /*!< TIM8 External trigger input         */
#define HAL_GPIO_AF3_TIM8_BKIN           HAL_GPIO_AF_3 /*!< TIM8 Break input                    */
#define HAL_GPIO_AF3_TIM8_BKIN2          HAL_GPIO_AF_3 /*!< TIM8 Break input 2                  */
#define HAL_GPIO_AF3_TIM8_CH1            HAL_GPIO_AF_3 /*!< TIM8 Multi-purpose Channel 1        */
#define HAL_GPIO_AF3_TIM8_CH1N           HAL_GPIO_AF_3 /*!< TIM8 CH1 complementary output       */
#define HAL_GPIO_AF3_TIM8_CH2            HAL_GPIO_AF_3 /*!< TIM8 Multi-purpose Channel 2        */
#define HAL_GPIO_AF3_TIM8_CH2N           HAL_GPIO_AF_3 /*!< TIM8 CH2 complementary output       */
#define HAL_GPIO_AF3_TIM8_CH3            HAL_GPIO_AF_3 /*!< TIM8 Multi-purpose Channel 3        */
#define HAL_GPIO_AF3_TIM8_CH3N           HAL_GPIO_AF_3 /*!< TIM8 CH3 complementary output       */
#define HAL_GPIO_AF3_TIM8_CH4            HAL_GPIO_AF_3 /*!< TIM8 Multi-purpose Channel 4        */
#define HAL_GPIO_AF3_TIM8_CH4N           HAL_GPIO_AF_3 /*!< TIM8 CH4 complementary output       */
#if defined (USART2)
#define HAL_GPIO_AF3_USART2              HAL_GPIO_AF_3 /*!< USART2 Alternate Function mapping   */
#define HAL_GPIO_AF3_USART2_RX           HAL_GPIO_AF_3 /*!< USART2 Serial Data Receive Input    */
#endif /* USART2 */
#define HAL_GPIO_AF3_ADF1                HAL_GPIO_AF_3 /*!< ADF1 Alternate Function mapping     */
#define HAL_GPIO_AF3_ADF1_CCK0           HAL_GPIO_AF_3 /*!< ADF1 External sensors clock 0       */
#define HAL_GPIO_AF3_ADF1_CCK1           HAL_GPIO_AF_3 /*!< ADF1 External sensors clock 1       */
#define HAL_GPIO_AF3_ADF1_SDI0           HAL_GPIO_AF_3 /*!< ADF1 Data from external sensors     */
#if defined(USB_OTG_HS)
#define HAL_GPIO_AF3_USB_OTG_HS          HAL_GPIO_AF_3 /*!< USB OTG Alternate Function mapping  */
#endif /* USB_OTG_HS */

/**
  * @brief   AF 4 selection
  */
#define HAL_GPIO_AF4_I2C1                HAL_GPIO_AF_4 /*!< I2C1 Alternate Function mapping   */
#define HAL_GPIO_AF4_I2C1_SCL            HAL_GPIO_AF_4 /*!< I2C1 Clock                        */
#define HAL_GPIO_AF4_I2C1_SDA            HAL_GPIO_AF_4 /*!< I2C1 Data                         */
#define HAL_GPIO_AF4_I2C1_SMBA           HAL_GPIO_AF_4 /*!< I2C1 SMBus Alert                  */
#define HAL_GPIO_AF4_I2C2                HAL_GPIO_AF_4 /*!< I2C2 Alternate Function mapping   */
#define HAL_GPIO_AF4_I2C2_SCL            HAL_GPIO_AF_4 /*!< I2C2 Clock                        */
#define HAL_GPIO_AF4_I2C2_SDA            HAL_GPIO_AF_4 /*!< I2C2 Data                         */
#define HAL_GPIO_AF4_I2C2_SMBA           HAL_GPIO_AF_4 /*!< I2C2 SMBus Alert                  */
#define HAL_GPIO_AF4_I2C3                HAL_GPIO_AF_4 /*!< I2C3 Alternate Function mapping   */
#define HAL_GPIO_AF4_I2C3_SCL            HAL_GPIO_AF_4 /*!< I2C3 Clock                        */
#define HAL_GPIO_AF4_I2C3_SDA            HAL_GPIO_AF_4 /*!< I2C3 Data                         */
#define HAL_GPIO_AF4_I2C3_SMBA           HAL_GPIO_AF_4 /*!< I2C3 SMBus Alert                  */
#define HAL_GPIO_AF4_I2C4                HAL_GPIO_AF_4 /*!< I2C4 Alternate Function mapping   */
#define HAL_GPIO_AF4_I2C4_SCL            HAL_GPIO_AF_4 /*!< I2C4 Clock                        */
#define HAL_GPIO_AF4_I2C4_SDA            HAL_GPIO_AF_4 /*!< I2C4 Data                         */
#define HAL_GPIO_AF4_I2C4_SMBA           HAL_GPIO_AF_4 /*!< I2C4 SMBus Alert                  */
#define HAL_GPIO_AF4_PSSI                HAL_GPIO_AF_4 /*!< PSSI Alternate Function mapping   */
#define HAL_GPIO_AF4_PSSI_D2             HAL_GPIO_AF_4 /*!< PSSI Data I/O 2                   */
#define HAL_GPIO_AF4_PSSI_D3             HAL_GPIO_AF_4 /*!< PSSI Data I/O 3                   */
#define HAL_GPIO_AF4_PSSI_D5             HAL_GPIO_AF_4 /*!< PSSI Data I/O 5                   */
#define HAL_GPIO_AF4_PSSI_D10            HAL_GPIO_AF_4 /*!< PSSI Data I/O 10                  */
#define HAL_GPIO_AF4_PSSI_D12            HAL_GPIO_AF_4 /*!< PSSI Data I/O 12                  */
#define HAL_GPIO_AF4_PSSI_D14            HAL_GPIO_AF_4 /*!< PSSI Data I/O 14                  */
#define HAL_GPIO_AF4_PSSI_D15            HAL_GPIO_AF_4 /*!< PSSI Data I/O 15                  */
#define HAL_GPIO_AF4_PSSI_PDCK           HAL_GPIO_AF_4 /*!< PSSI Parallel data clock input    */
#define HAL_GPIO_AF4_DCMI                HAL_GPIO_AF_4 /*!< DCMI Alternate Function mapping   */
#define HAL_GPIO_AF4_DCMI_D2             HAL_GPIO_AF_4 /*!< DCMI Data I/O 2                   */
#define HAL_GPIO_AF4_DCMI_D3             HAL_GPIO_AF_4 /*!< DCMI Data I/O 3                   */
#define HAL_GPIO_AF4_DCMI_D5             HAL_GPIO_AF_4 /*!< DCMI Data I/O 5                   */
#define HAL_GPIO_AF4_DCMI_D10            HAL_GPIO_AF_4 /*!< DCMI Data I/O 10                  */
#define HAL_GPIO_AF4_DCMI_D12            HAL_GPIO_AF_4 /*!< DCMI Data I/O 12                  */
#define HAL_GPIO_AF4_DCMI_PIXCLK         HAL_GPIO_AF_4 /*!< DCMI Parallel data clock input    */
#define HAL_GPIO_AF4_LPTIM3              HAL_GPIO_AF_4 /*!< LPTIM3 Alternate Function mapping */
#define HAL_GPIO_AF4_LPTIM3_CH1          HAL_GPIO_AF_4 /*!< LPTIM3 Multi-purpose Channel 1    */
#define HAL_GPIO_AF4_LPTIM3_CH2          HAL_GPIO_AF_4 /*!< LPTIM3 Multi-purpose Channel 2    */
#if defined (I2C5)
#define HAL_GPIO_AF4_I2C5                HAL_GPIO_AF_4 /*!< I2C5 Alternate Function mapping     */
#define HAL_GPIO_AF4_I2C5_SCL            HAL_GPIO_AF_4 /*!< I2C5 Clock                          */
#define HAL_GPIO_AF4_I2C5_SDA            HAL_GPIO_AF_4 /*!< I2C5 Data                           */
#define HAL_GPIO_AF4_I2C5_SMBA           HAL_GPIO_AF_4 /*!< I2C5 SMBus Alert                    */
#endif /* I2C5 */

/**
  * @brief   AF 5 selection
  */
#define HAL_GPIO_AF5_I2C4                HAL_GPIO_AF_5 /*!< I2C4 Alternate Function mapping       */
#define HAL_GPIO_AF5_I2C4_SCL            HAL_GPIO_AF_5 /*!< I2C4 Clock                            */
#define HAL_GPIO_AF5_I2C4_SDA            HAL_GPIO_AF_5 /*!< I2C4 Data                             */
#define HAL_GPIO_AF5_I2C4_SMBA           HAL_GPIO_AF_5 /*!< I2C4 SMBus Alert                      */
#define HAL_GPIO_AF5_OCTOSPIM_P1         HAL_GPIO_AF_5 /*!< OCTOSPIM_P1 Alternate Function mapping   */
#define HAL_GPIO_AF5_OCTOSPIM_P1_NCS     HAL_GPIO_AF_5 /*!< OCTOSPIM_P1 Memory Chip Select           */
#if defined (OCTOSPI2)
#define HAL_GPIO_AF5_OCTOSPIM_P2         HAL_GPIO_AF_5 /*!< OCTOSPIM_P2 Alternate Function mapping   */
#define HAL_GPIO_AF5_OCTOSPIM_P2_IO0     HAL_GPIO_AF_5 /*!< OCTOSPIM_P2 Data Pin 0                   */
#define HAL_GPIO_AF5_OCTOSPIM_P2_IO1     HAL_GPIO_AF_5 /*!< OCTOSPIM_P2 Data Pin 1                   */
#define HAL_GPIO_AF5_OCTOSPIM_P2_IO2     HAL_GPIO_AF_5 /*!< OCTOSPIM_P2 Data Pin 2                   */
#define HAL_GPIO_AF5_OCTOSPIM_P2_IO3     HAL_GPIO_AF_5 /*!< OCTOSPIM_P2 Data Pin 3                   */
#define HAL_GPIO_AF5_OCTOSPIM_P2_IO4     HAL_GPIO_AF_5 /*!< OCTOSPIM_P2 Data Pin 4                   */
#define HAL_GPIO_AF5_OCTOSPIM_P2_IO5     HAL_GPIO_AF_5 /*!< OCTOSPIM_P2 Data Pin 5                   */
#define HAL_GPIO_AF5_OCTOSPIM_P2_IO6     HAL_GPIO_AF_5 /*!< OCTOSPIM_P2 Data Pin 6                   */
#define HAL_GPIO_AF5_OCTOSPIM_P2_IO7     HAL_GPIO_AF_5 /*!< OCTOSPIM_P2 Data Pin 7                   */
#define HAL_GPIO_AF5_OCTOSPIM_P2_CLK     HAL_GPIO_AF_5 /*!< OCTOSPIM_P2 Clock                        */
#define HAL_GPIO_AF5_OCTOSPIM_P2_NCLK    HAL_GPIO_AF_5 /*!< OCTOSPIM_P2 Inverted Clock               */
#define HAL_GPIO_AF5_OCTOSPIM_P2_NCS     HAL_GPIO_AF_5 /*!< OCTOSPIM_P2 Memory Chip Select           */
#define HAL_GPIO_AF5_OCTOSPIM_P2_DQS     HAL_GPIO_AF_5 /*!< OCTOSPIM_P2 Memory Data Strobe I/O       */
#endif /* OCTOSPI2 */
#define HAL_GPIO_AF5_SPI1                HAL_GPIO_AF_5 /*!< SPI1 Alternate Function mapping       */
#define HAL_GPIO_AF5_SPI1_MISO           HAL_GPIO_AF_5 /*!< SPI1 Master-In/Slave-Out              */
#define HAL_GPIO_AF5_SPI1_MOSI           HAL_GPIO_AF_5 /*!< SPI1 Master-Out/Slave-In              */
#define HAL_GPIO_AF5_SPI1_NSS            HAL_GPIO_AF_5 /*!< SPI1 Slave Selection                  */
#define HAL_GPIO_AF5_SPI1_RDY            HAL_GPIO_AF_5 /*!< SPI1 Master-In/Slave-Out FIFOs status */
#define HAL_GPIO_AF5_SPI1_SCK            HAL_GPIO_AF_5 /*!< SPI1 Master-Out/Slave-In Clock        */
#define HAL_GPIO_AF5_SPI2                HAL_GPIO_AF_5 /*!< SPI2 Alternate Function mapping       */
#define HAL_GPIO_AF5_SPI2_MISO           HAL_GPIO_AF_5 /*!< SPI2 Master-In/Slave-Out              */
#define HAL_GPIO_AF5_SPI2_MOSI           HAL_GPIO_AF_5 /*!< SPI2 Master-Out/Slave-In              */
#define HAL_GPIO_AF5_SPI2_NSS            HAL_GPIO_AF_5 /*!< SPI2 Slave Selection                  */
#define HAL_GPIO_AF5_SPI2_RDY            HAL_GPIO_AF_5 /*!< SPI2 Master-In/Slave-Out FIFOs status */
#define HAL_GPIO_AF5_SPI2_SCK            HAL_GPIO_AF_5 /*!< SPI2 Master-Out/Slave-In Clock        */
#define HAL_GPIO_AF5_SPI3                HAL_GPIO_AF_5 /*!< SPI3 Alternate Function mapping       */
#define HAL_GPIO_AF5_SPI3_MISO           HAL_GPIO_AF_5 /*!< SPI3 Master-In/Slave-Out              */
#define HAL_GPIO_AF5_SPI3_MOSI           HAL_GPIO_AF_5 /*!< SPI3 Master-Out/Slave-In              */
#define HAL_GPIO_AF5_SPI3_NSS            HAL_GPIO_AF_5 /*!< SPI3 Slave Selection                  */
#define HAL_GPIO_AF5_SPI3_RDY            HAL_GPIO_AF_5 /*!< SPI3 Master-In/Slave-Out FIFOs status */
#define HAL_GPIO_AF5_SPI3_SCK            HAL_GPIO_AF_5 /*!< SPI3 Master-Out/Slave-In Clock        */
#define HAL_GPIO_AF5_DCMI                HAL_GPIO_AF_5 /*!< DCMI Alternate Function mapping       */
#define HAL_GPIO_AF5_DCMI_D0             HAL_GPIO_AF_5 /*!< DCMI Data I/O 0                       */
#define HAL_GPIO_AF5_DCMI_D1             HAL_GPIO_AF_5 /*!< DCMI Data I/O 1                       */
#define HAL_GPIO_AF5_MDF1                HAL_GPIO_AF_5 /*!< MDF1 Alternate Function mapping       */
#define HAL_GPIO_AF5_MDF1_CCK0           HAL_GPIO_AF_5 /*!< MDF1 External sensors clock 0         */
#define HAL_GPIO_AF5_PSSI                HAL_GPIO_AF_5 /*!< PSSI Alternate Function mapping       */
#define HAL_GPIO_AF5_PSSI_D0             HAL_GPIO_AF_5 /*!< PSSI Data I/O 0                       */
#define HAL_GPIO_AF5_PSSI_D1             HAL_GPIO_AF_5 /*!< PSSI Data I/O 1                       */
#if defined(GFXTIM)
#define HAL_GPIO_AF5_GFXTIM              HAL_GPIO_AF_5 /*!< GFXTIM Alternate Function mapping     */
#define HAL_GPIO_AF5_GFXTIM_LCKCAL       HAL_GPIO_AF_5 /*!< GFXTIM Line Clock Calibration Output  */
#define HAL_GPIO_AF5_GFXTIM_TE           HAL_GPIO_AF_5 /*!< GFXTIM Frame Clock Calibration Output */
#endif /* GFXTIM */

/**
  * @brief   AF 6 selection
  */
#if defined (OCTOSPI2)
#define HAL_GPIO_AF6_OCTOSPIM_P2         HAL_GPIO_AF_6 /*!< OCTOSPIM_P2 Alternate Function mapping     */
#define HAL_GPIO_AF6_OCTOSPIM_P2_NCS     HAL_GPIO_AF_6 /*!< OCTOSPIM_P2 Memory Chip Select             */
#define HAL_GPIO_AF6_OCTOSPI2_P2_IO0     HAL_GPIO_AF_6 /*!< OCTOSPIM_P2 Data Pin 0                     */
#define HAL_GPIO_AF6_OCTOSPI2_P2_IO1     HAL_GPIO_AF_6 /*!< OCTOSPIM_P2 Data Pin 1                     */
#define HAL_GPIO_AF6_OCTOSPI2_P2_IO2     HAL_GPIO_AF_6 /*!< OCTOSPIM_P2 Data Pin 2                     */
#endif /* OCTOSPI2 */
#define HAL_GPIO_AF6_MDF1                HAL_GPIO_AF_6 /*!< MDF1 Alternate Function mapping         */
#define HAL_GPIO_AF6_MDF1_SDI0           HAL_GPIO_AF_6 /*!< MDF1 External sensors data signal 0     */
#define HAL_GPIO_AF6_MDF1_SDI1           HAL_GPIO_AF_6 /*!< MDF1 External sensors data signal 1     */
#define HAL_GPIO_AF6_MDF1_SDI2           HAL_GPIO_AF_6 /*!< MDF1 External sensors data signal 2     */
#define HAL_GPIO_AF6_MDF1_SDI3           HAL_GPIO_AF_6 /*!< MDF1 External sensors data signal 3     */
#define HAL_GPIO_AF6_MDF1_SDI4           HAL_GPIO_AF_6 /*!< MDF1 External sensors data signal 4     */
#define HAL_GPIO_AF6_MDF1_SDI5           HAL_GPIO_AF_6 /*!< MDF1 External sensors data signal 5     */
#define HAL_GPIO_AF6_MDF1_CCK0           HAL_GPIO_AF_6 /*!< MDF1 External sensors clock 0           */
#define HAL_GPIO_AF6_MDF1_CCK1           HAL_GPIO_AF_6 /*!< MDF1 External sensors clock 1           */
#define HAL_GPIO_AF6_MDF1_CKI0           HAL_GPIO_AF_6 /*!< MDF1 External sensors dedicated clock 0 */
#define HAL_GPIO_AF6_MDF1_CKI1           HAL_GPIO_AF_6 /*!< MDF1 External sensors dedicated clock 1 */
#define HAL_GPIO_AF6_MDF1_CKI2           HAL_GPIO_AF_6 /*!< MDF1 External sensors dedicated clock 2 */
#define HAL_GPIO_AF6_MDF1_CKI3           HAL_GPIO_AF_6 /*!< MDF1 External sensors dedicated clock 3 */
#define HAL_GPIO_AF6_MDF1_CKI4           HAL_GPIO_AF_6 /*!< MDF1 External sensors dedicated clock 4 */
#define HAL_GPIO_AF6_MDF1_CKI5           HAL_GPIO_AF_6 /*!< MDF1 External sensors dedicated clock 5 */
#define HAL_GPIO_AF6_SPI3                HAL_GPIO_AF_6 /*!< SPI3 Alternate Function mapping         */
#define HAL_GPIO_AF6_SPI3_MISO           HAL_GPIO_AF_6 /*!< SPI3 Master-In/Slave-Out                */
#define HAL_GPIO_AF6_SPI3_MOSI           HAL_GPIO_AF_6 /*!< SPI3 Master-Out/Slave-In                */
#define HAL_GPIO_AF6_SPI3_NSS            HAL_GPIO_AF_6 /*!< SPI3 Slave Selection                    */
#define HAL_GPIO_AF6_SPI3_RDY            HAL_GPIO_AF_6 /*!< SPI3 Master-In/Slave-Out FIFOs status   */
#define HAL_GPIO_AF6_SPI3_SCK            HAL_GPIO_AF_6 /*!< SPI3 Master-Out/Slave-In Clock          */
#define HAL_GPIO_AF6_I2C3                HAL_GPIO_AF_6 /*!< I2C3 Alternate Function mapping         */
#define HAL_GPIO_AF6_I2C3_SCL            HAL_GPIO_AF_6 /*!< I2C3 Clock                              */
#define HAL_GPIO_AF6_I2C3_SDA            HAL_GPIO_AF_6 /*!< I2C3 Data                               */
#define HAL_GPIO_AF6_I2C3_SMBA           HAL_GPIO_AF_6 /*!< I2C3 SMBus Alert                        */

/**
  * @brief   AF 7 selection
  */
#define HAL_GPIO_AF7_USART1              HAL_GPIO_AF_7 /*!< USART1 Alternate Function mapping                      */
#define HAL_GPIO_AF7_USART1_CK           HAL_GPIO_AF_7 /*!< USART1 Synchronous master/Smartcard modes Clock output */
#define HAL_GPIO_AF7_USART1_TX           HAL_GPIO_AF_7 /*!< USART1 Transmit Data Output                            */
#define HAL_GPIO_AF7_USART1_RX           HAL_GPIO_AF_7 /*!< USART1 Serial Data Receive Input                       */
#define HAL_GPIO_AF7_USART1_CTS          HAL_GPIO_AF_7 /*!< USART1 Clear to send                                   */
#define HAL_GPIO_AF7_USART1_RTS_DE       HAL_GPIO_AF_7 /*!< USART1 Request to send/Driver enable                   */
#if defined (USART2)
#define HAL_GPIO_AF7_USART2              HAL_GPIO_AF_7 /*!< USART2 Alternate Function mapping                      */
#define HAL_GPIO_AF7_USART2_CTS          HAL_GPIO_AF_7 /*!< USART2 Clear to send                                   */
#define HAL_GPIO_AF7_USART2_RTS_DE       HAL_GPIO_AF_7 /*!< USART2 Request to send/Driver enable                   */
#define HAL_GPIO_AF7_USART2_TX           HAL_GPIO_AF_7 /*!< USART2 Transmit Data Output                            */
#define HAL_GPIO_AF7_USART2_RX           HAL_GPIO_AF_7 /*!< USART2 Serial Data Receive Input                       */
#define HAL_GPIO_AF7_USART2_CK           HAL_GPIO_AF_7 /*!< USART2 Synchronous master/Smartcard modes Clock output */
#endif /* USART2 */
#define HAL_GPIO_AF7_USART3              HAL_GPIO_AF_7 /*!< USART3 Alternate Function mapping                      */
#define HAL_GPIO_AF7_USART3_RX           HAL_GPIO_AF_7 /*!< USART3 Serial Data Receive Input                       */
#define HAL_GPIO_AF7_USART3_CTS          HAL_GPIO_AF_7 /*!< USART3 Clear to send                                   */
#define HAL_GPIO_AF7_USART3_TX           HAL_GPIO_AF_7 /*!< USART3 Transmit Data Output                            */
#define HAL_GPIO_AF7_USART3_CK           HAL_GPIO_AF_7 /*!< USART3 Synchronous master/Smartcard modes Clock output */
#define HAL_GPIO_AF7_USART3_RTS_DE       HAL_GPIO_AF_7 /*!< USART3 Request to send/Driver enable                   */
#if defined(USART6)
#define HAL_GPIO_AF7_USART6              HAL_GPIO_AF_7 /*!< USART6 Alternate Function mapping                      */
#define HAL_GPIO_AF7_USART6_CK           HAL_GPIO_AF_7 /*!< USART6 Synchronous master/Smartcard modes Clock output */
#define HAL_GPIO_AF7_USART6_TX           HAL_GPIO_AF_7 /*!< USART6 Transmit Data Output                            */
#define HAL_GPIO_AF7_USART6_RX           HAL_GPIO_AF_7 /*!< USART6 Serial Data Receive Input                       */
#define HAL_GPIO_AF7_USART6_CTS          HAL_GPIO_AF_7 /*!< USART6 Clear to send                                   */
#define HAL_GPIO_AF7_USART6_RTS_DE       HAL_GPIO_AF_7 /*!< USART6 Request to send/Driver enable                   */
#endif /* USART6 */
#if defined(LTDC)
#define HAL_GPIO_AF7_LTDC                HAL_GPIO_AF_7 /*!< LTDC Alternate Function mapping */
#define HAL_GPIO_AF7_LTDC_B1             HAL_GPIO_AF_7 /*!< LTDC Blue data bit 1            */
#define HAL_GPIO_AF7_LTDC_R0             HAL_GPIO_AF_7 /*!< LTDC Red data bit 0             */
#define HAL_GPIO_AF7_LTDC_R1             HAL_GPIO_AF_7 /*!< LTDC Red data bit 1             */
#endif /* LTDC */

/**
  * @brief   AF 8 selection
  */
#define HAL_GPIO_AF8_LPUART1             HAL_GPIO_AF_8 /*!< LPUART1 Alternate Function mapping                    */
#define HAL_GPIO_AF8_LPUART1_TX          HAL_GPIO_AF_8 /*!< LPUART1 Transmit Data Output                          */
#define HAL_GPIO_AF8_LPUART1_RX          HAL_GPIO_AF_8 /*!< LPUART1 Serial Data Receive Input                     */
#define HAL_GPIO_AF8_LPUART1_CTS         HAL_GPIO_AF_8 /*!< LPUART1 Clear to send                                 */
#define HAL_GPIO_AF8_LPUART1_RTS_DE      HAL_GPIO_AF_8 /*!< LPUART1 Request to send/Driver enable                 */
#define HAL_GPIO_AF8_UART4               HAL_GPIO_AF_8 /*!< UART4 Alternate Function mapping                      */
#define HAL_GPIO_AF8_UART4_TX            HAL_GPIO_AF_8 /*!< UART4 Transmit Data Output                            */
#define HAL_GPIO_AF8_UART4_RX            HAL_GPIO_AF_8 /*!< UART4 Serial Data Receive Input                       */
#define HAL_GPIO_AF8_UART4_CK            HAL_GPIO_AF_8 /*!< UART4 Synchronous master/Smartcard modes Clock output */
#define HAL_GPIO_AF8_UART4_RTS_DE        HAL_GPIO_AF_8 /*!< UART4 Request to send/Driver enable                   */
#define HAL_GPIO_AF8_UART4_CTS           HAL_GPIO_AF_8 /*!< UART4 Clear to send                                   */
#define HAL_GPIO_AF8_SDMMC1              HAL_GPIO_AF_8 /*!< SDMMC1 Alternate Function mapping                     */
#define HAL_GPIO_AF8_SDMMC1_CKIN         HAL_GPIO_AF_8 /*!< SDMMC1 External driver clock feedback                 */
#define HAL_GPIO_AF8_SDMMC1_CDIR         HAL_GPIO_AF_8 /*!< SDMMC1 Card I/O signal direction indication           */
#define HAL_GPIO_AF8_SDMMC1_D0DIR        HAL_GPIO_AF_8 /*!< SDMMC1 Card I/O data line 0 direction indication      */
#define HAL_GPIO_AF8_SDMMC1_D123DIR      HAL_GPIO_AF_8 /*!< SDMMC1 Card I/O data lines 1,2,3 direction indication */
#if defined (SDMMC2)
#define HAL_GPIO_AF8_SDMMC2              HAL_GPIO_AF_8 /*!< SDMMC2 Alternate Function mapping                     */
#define HAL_GPIO_AF8_SDMMC2_D1           HAL_GPIO_AF_8 /*!< SDMMC2 Card bidirectional data line 1                 */
#endif /* SDMMC2 */
#define HAL_GPIO_AF8_UART5               HAL_GPIO_AF_8 /*!< UART5 Alternate Function mapping                      */
#define HAL_GPIO_AF8_UART5_TX            HAL_GPIO_AF_8 /*!< UART5 Transmit Data Output                            */
#define HAL_GPIO_AF8_UART5_RX            HAL_GPIO_AF_8 /*!< UART5 Serial Data Receive Input                       */
#define HAL_GPIO_AF8_UART5_RTS_DE        HAL_GPIO_AF_8 /*!< UART5 Request to send/Driver enable                   */
#define HAL_GPIO_AF8_UART5_CTS           HAL_GPIO_AF_8 /*!< UART5 Clear to send                                   */
#if defined(LTDC)
#define HAL_GPIO_AF8_LTDC                HAL_GPIO_AF_8 /*!< LTDC Alternate Function mapping  */
#define HAL_GPIO_AF8_LTDC_G0             HAL_GPIO_AF_8 /*!< LTDC Green data bit 0            */
#define HAL_GPIO_AF8_LTDC_G1             HAL_GPIO_AF_8 /*!< LTDC Green data bit 1            */
#define HAL_GPIO_AF8_LTDC_G2             HAL_GPIO_AF_8 /*!< LTDC Green data bit 2            */
#define HAL_GPIO_AF8_LTDC_G3             HAL_GPIO_AF_8 /*!< LTDC Green data bit 3            */
#define HAL_GPIO_AF8_LTDC_G4             HAL_GPIO_AF_8 /*!< LTDC Green data bit 4            */
#define HAL_GPIO_AF8_LTDC_G5             HAL_GPIO_AF_8 /*!< LTDC Green data bit 5            */
#define HAL_GPIO_AF8_LTDC_G6             HAL_GPIO_AF_8 /*!< LTDC Green data bit 6            */
#define HAL_GPIO_AF8_LTDC_G7             HAL_GPIO_AF_8 /*!< LTDC Green data bit 7            */
#define HAL_GPIO_AF8_LTDC_B0             HAL_GPIO_AF_8 /*!< LTDC Blue data bit 0             */
#define HAL_GPIO_AF8_LTDC_B1             HAL_GPIO_AF_8 /*!< LTDC Blue data bit 1             */
#define HAL_GPIO_AF8_LTDC_B2             HAL_GPIO_AF_8 /*!< LTDC Blue data bit 2             */
#define HAL_GPIO_AF8_LTDC_B3             HAL_GPIO_AF_8 /*!< LTDC Blue data bit 3             */
#define HAL_GPIO_AF8_LTDC_B4             HAL_GPIO_AF_8 /*!< LTDC Blue data bit 4             */
#define HAL_GPIO_AF8_LTDC_B5             HAL_GPIO_AF_8 /*!< LTDC Blue data bit 5             */
#define HAL_GPIO_AF8_LTDC_B6             HAL_GPIO_AF_8 /*!< LTDC Blue data bit 6             */
#define HAL_GPIO_AF8_LTDC_B7             HAL_GPIO_AF_8 /*!< LTDC Blue data bit 7             */
#define HAL_GPIO_AF8_LTDC_CLK            HAL_GPIO_AF_8 /*!< LTDC Clock output                */
#define HAL_GPIO_AF8_LTDC_DE             HAL_GPIO_AF_8 /*!< LTDC Not data enable             */
#define HAL_GPIO_AF8_LTDC_R0             HAL_GPIO_AF_8 /*!< LTDC Red data bit 0              */
#define HAL_GPIO_AF8_LTDC_R1             HAL_GPIO_AF_8 /*!< LTDC Red data bit 1              */
#define HAL_GPIO_AF8_LTDC_R2             HAL_GPIO_AF_8 /*!< LTDC Red data bit 2              */
#define HAL_GPIO_AF8_LTDC_R3             HAL_GPIO_AF_8 /*!< LTDC Red data bit 3              */
#define HAL_GPIO_AF8_LTDC_R4             HAL_GPIO_AF_8 /*!< LTDC Red data bit 4              */
#define HAL_GPIO_AF8_LTDC_R5             HAL_GPIO_AF_8 /*!< LTDC Red data bit 5              */
#define HAL_GPIO_AF8_LTDC_R6             HAL_GPIO_AF_8 /*!< LTDC Red data bit 6              */
#define HAL_GPIO_AF8_LTDC_R7             HAL_GPIO_AF_8 /*!< LTDC Red data bit 7              */
#define HAL_GPIO_AF8_LTDC_VSYNC          HAL_GPIO_AF_8 /*!< LTDC Vertical Synchronization    */
#define HAL_GPIO_AF8_LTDC_HSYNC          HAL_GPIO_AF_8 /*!< LTDC Horizontal Synchronization  */
#endif /* LTDC */
#if defined(HSPI1)
#define HAL_GPIO_AF8_HSPI1               HAL_GPIO_AF_8 /*!< HSPI1 Alternate Function mapping  */
#define HAL_GPIO_AF8_HSPI1_DQS0          HAL_GPIO_AF_8 /*!< HSPI1 Memory Data Strobe I/O 0    */
#define HAL_GPIO_AF8_HSPI1_DQS1          HAL_GPIO_AF_8 /*!< HSPI1 Memory Data Strobe I/O 1    */
#define HAL_GPIO_AF8_HSPI1_CLK           HAL_GPIO_AF_8 /*!< HSPI1 Clock                       */
#define HAL_GPIO_AF8_HSPI1_NCLK          HAL_GPIO_AF_8 /*!< HSPI1 Inverted Clock              */
#define HAL_GPIO_AF8_HSPI1_NCS           HAL_GPIO_AF_8 /*!< HSPI1 Memory Chip Select          */
#define HAL_GPIO_AF8_HSPI1_IO0           HAL_GPIO_AF_8 /*!< HSPI1 Data pin 0                  */
#define HAL_GPIO_AF8_HSPI1_IO1           HAL_GPIO_AF_8 /*!< HSPI1 Data pin 1                  */
#define HAL_GPIO_AF8_HSPI1_IO2           HAL_GPIO_AF_8 /*!< HSPI1 Data pin 2                  */
#define HAL_GPIO_AF8_HSPI1_IO3           HAL_GPIO_AF_8 /*!< HSPI1 Data pin 3                  */
#define HAL_GPIO_AF8_HSPI1_IO4           HAL_GPIO_AF_8 /*!< HSPI1 Data pin 4                  */
#define HAL_GPIO_AF8_HSPI1_IO5           HAL_GPIO_AF_8 /*!< HSPI1 Data pin 5                  */
#define HAL_GPIO_AF8_HSPI1_IO6           HAL_GPIO_AF_8 /*!< HSPI1 Data pin 6                  */
#define HAL_GPIO_AF8_HSPI1_IO7           HAL_GPIO_AF_8 /*!< HSPI1 Data pin 7                  */
#define HAL_GPIO_AF8_HSPI1_IO8           HAL_GPIO_AF_8 /*!< HSPI1 Data pin 8                  */
#define HAL_GPIO_AF8_HSPI1_IO9           HAL_GPIO_AF_8 /*!< HSPI1 Data pin 9                  */
#define HAL_GPIO_AF8_HSPI1_IO10          HAL_GPIO_AF_8 /*!< HSPI1 Data pin 10                 */
#define HAL_GPIO_AF8_HSPI1_IO11          HAL_GPIO_AF_8 /*!< HSPI1 Data pin 11                 */
#define HAL_GPIO_AF8_HSPI1_IO12          HAL_GPIO_AF_8 /*!< HSPI1 Data pin 12                 */
#define HAL_GPIO_AF8_HSPI1_IO13          HAL_GPIO_AF_8 /*!< HSPI1 Data pin 13                 */
#define HAL_GPIO_AF8_HSPI1_IO14          HAL_GPIO_AF_8 /*!< HSPI1 Data pin 14                 */
#define HAL_GPIO_AF8_HSPI1_IO15          HAL_GPIO_AF_8 /*!< HSPI1 Data pin 15                 */
#endif /* HSPI1 */

/**
  * @brief   AF 9 selection
  */
#define HAL_GPIO_AF9_FDCAN1              HAL_GPIO_AF_9 /*!< FDCAN1 Alternate Function mapping */
#define HAL_GPIO_AF9_FDCAN1_RX           HAL_GPIO_AF_9 /*!< FDCAN1 Receive pin                */
#define HAL_GPIO_AF9_FDCAN1_TX           HAL_GPIO_AF_9 /*!< FDCAN1 Transmit pin               */
#define HAL_GPIO_AF9_TSC                 HAL_GPIO_AF_9 /*!< TSC Alternate Function mapping    */
#define HAL_GPIO_AF9_TSC_G1_IO1          HAL_GPIO_AF_9 /*!< TSC Analog Group 1 I/O 1          */
#define HAL_GPIO_AF9_TSC_G1_IO2          HAL_GPIO_AF_9 /*!< TSC Analog Group 1 I/O 2          */
#define HAL_GPIO_AF9_TSC_G1_IO3          HAL_GPIO_AF_9 /*!< TSC Analog Group 1 I/O 3          */
#define HAL_GPIO_AF9_TSC_G2_IO1          HAL_GPIO_AF_9 /*!< TSC Analog Group 2 I/O 1          */
#define HAL_GPIO_AF9_TSC_G2_IO2          HAL_GPIO_AF_9 /*!< TSC Analog Group 2 I/O 2          */
#define HAL_GPIO_AF9_TSC_G2_IO3          HAL_GPIO_AF_9 /*!< TSC Analog Group 2 I/O 3          */
#define HAL_GPIO_AF9_TSC_G2_IO4          HAL_GPIO_AF_9 /*!< TSC Analog Group 2 I/O 4          */
#define HAL_GPIO_AF9_TSC_G3_IO1          HAL_GPIO_AF_9 /*!< TSC Analog Group 3 I/O 1          */
#define HAL_GPIO_AF9_TSC_G3_IO2          HAL_GPIO_AF_9 /*!< TSC Analog Group 3 I/O 2          */
#define HAL_GPIO_AF9_TSC_G3_IO3          HAL_GPIO_AF_9 /*!< TSC Analog Group 3 I/O 3          */
#define HAL_GPIO_AF9_TSC_G3_IO4          HAL_GPIO_AF_9 /*!< TSC Analog Group 3 I/O 4          */
#define HAL_GPIO_AF9_TSC_G4_IO1          HAL_GPIO_AF_9 /*!< TSC Analog Group 4 I/O 1          */
#define HAL_GPIO_AF9_TSC_G4_IO2          HAL_GPIO_AF_9 /*!< TSC Analog Group 4 I/O 2          */
#define HAL_GPIO_AF9_TSC_G4_IO3          HAL_GPIO_AF_9 /*!< TSC Analog Group 4 I/O 3          */
#define HAL_GPIO_AF9_TSC_G4_IO4          HAL_GPIO_AF_9 /*!< TSC Analog Group 4 I/O 4          */
#define HAL_GPIO_AF9_TSC_G5_IO1          HAL_GPIO_AF_9 /*!< TSC Analog Group 5 I/O 1          */
#define HAL_GPIO_AF9_TSC_G5_IO2          HAL_GPIO_AF_9 /*!< TSC Analog Group 5 I/O 2          */
#define HAL_GPIO_AF9_TSC_G5_IO3          HAL_GPIO_AF_9 /*!< TSC Analog Group 5 I/O 3          */
#define HAL_GPIO_AF9_TSC_G5_IO4          HAL_GPIO_AF_9 /*!< TSC Analog Group 5 I/O 4          */
#define HAL_GPIO_AF9_TSC_G6_IO1          HAL_GPIO_AF_9 /*!< TSC Analog Group 6 I/O 1          */
#define HAL_GPIO_AF9_TSC_G6_IO2          HAL_GPIO_AF_9 /*!< TSC Analog Group 6 I/O 2          */
#define HAL_GPIO_AF9_TSC_G6_IO3          HAL_GPIO_AF_9 /*!< TSC Analog Group 6 I/O 3          */
#define HAL_GPIO_AF9_TSC_G6_IO4          HAL_GPIO_AF_9 /*!< TSC Analog Group 6 I/O 4          */
#define HAL_GPIO_AF9_TSC_G7_IO1          HAL_GPIO_AF_9 /*!< TSC Analog Group 7 I/O 1          */
#define HAL_GPIO_AF9_TSC_G7_IO2          HAL_GPIO_AF_9 /*!< TSC Analog Group 7 I/O 2          */
#define HAL_GPIO_AF9_TSC_G7_IO3          HAL_GPIO_AF_9 /*!< TSC Analog Group 7 I/O 3          */
#define HAL_GPIO_AF9_TSC_G7_IO4          HAL_GPIO_AF_9 /*!< TSC Analog Group 7 I/O 4          */
#define HAL_GPIO_AF9_TSC_G8_IO1          HAL_GPIO_AF_9 /*!< TSC Analog Group 8 I/O 1          */
#define HAL_GPIO_AF9_TSC_G8_IO2          HAL_GPIO_AF_9 /*!< TSC Analog Group 8 I/O 2          */
#define HAL_GPIO_AF9_TSC_G8_IO3          HAL_GPIO_AF_9 /*!< TSC Analog Group 8 I/O 3          */
#define HAL_GPIO_AF9_TSC_G8_IO4          HAL_GPIO_AF_9 /*!< TSC Analog Group 8 I/O 4          */
#define HAL_GPIO_AF9_TSC_SYNC            HAL_GPIO_AF_9 /*!< TSC Synchronization enable        */

/**
  * @brief   AF 10 selection
  */
#define HAL_GPIO_AF10_DCMI               HAL_GPIO_AF_10 /*!< DCMI Alternate Function mapping     */
#define HAL_GPIO_AF10_DCMI_HSYNC         HAL_GPIO_AF_10 /*!< DCMI Horizontal Synchronization     */
#define HAL_GPIO_AF10_DCMI_VSYNC         HAL_GPIO_AF_10 /*!< DCMI Vertical Synchronization       */
#define HAL_GPIO_AF10_DCMI_PIXCLK        HAL_GPIO_AF_10 /*!< DCMI Parallel data clock input      */
#define HAL_GPIO_AF10_DCMI_D0            HAL_GPIO_AF_10 /*!< DCMI Data I/O 0                     */
#define HAL_GPIO_AF10_DCMI_D1            HAL_GPIO_AF_10 /*!< DCMI Data I/O 1                     */
#define HAL_GPIO_AF10_DCMI_D2            HAL_GPIO_AF_10 /*!< DCMI Data I/O 2                     */
#define HAL_GPIO_AF10_DCMI_D3            HAL_GPIO_AF_10 /*!< DCMI Data I/O 3                     */
#define HAL_GPIO_AF10_DCMI_D4            HAL_GPIO_AF_10 /*!< DCMI Data I/O 4                     */
#define HAL_GPIO_AF10_DCMI_D5            HAL_GPIO_AF_10 /*!< DCMI Data I/O 5                     */
#define HAL_GPIO_AF10_DCMI_D6            HAL_GPIO_AF_10 /*!< DCMI Data I/O 6                     */
#define HAL_GPIO_AF10_DCMI_D7            HAL_GPIO_AF_10 /*!< DCMI Data I/O 7                     */
#define HAL_GPIO_AF10_DCMI_D8            HAL_GPIO_AF_10 /*!< DCMI Data I/O 8                     */
#define HAL_GPIO_AF10_DCMI_D9            HAL_GPIO_AF_10 /*!< DCMI Data I/O 9                     */
#define HAL_GPIO_AF10_DCMI_D10           HAL_GPIO_AF_10 /*!< DCMI Data I/O 10                    */
#define HAL_GPIO_AF10_DCMI_D11           HAL_GPIO_AF_10 /*!< DCMI Data I/O 11                    */
#define HAL_GPIO_AF10_DCMI_D12           HAL_GPIO_AF_10 /*!< DCMI Data I/O 12                    */
#define HAL_GPIO_AF10_DCMI_D13           HAL_GPIO_AF_10 /*!< DCMI Data I/O 13                    */
#define HAL_GPIO_AF10_PSSI               HAL_GPIO_AF_10 /*!< PSSI Alternate Function mapping     */
#define HAL_GPIO_AF10_PSSI_D0            HAL_GPIO_AF_10 /*!< PSSI Data I/O 0                     */
#define HAL_GPIO_AF10_PSSI_D1            HAL_GPIO_AF_10 /*!< PSSI Data I/O 1                     */
#define HAL_GPIO_AF10_PSSI_D2            HAL_GPIO_AF_10 /*!< PSSI Data I/O 2                     */
#define HAL_GPIO_AF10_PSSI_D3            HAL_GPIO_AF_10 /*!< PSSI Data I/O 3                     */
#define HAL_GPIO_AF10_PSSI_D4            HAL_GPIO_AF_10 /*!< PSSI Data I/O 4                     */
#define HAL_GPIO_AF10_PSSI_D5            HAL_GPIO_AF_10 /*!< PSSI Data I/O 5                     */
#define HAL_GPIO_AF10_PSSI_D6            HAL_GPIO_AF_10 /*!< PSSI Data I/O 6                     */
#define HAL_GPIO_AF10_PSSI_D7            HAL_GPIO_AF_10 /*!< PSSI Data I/O 7                     */
#define HAL_GPIO_AF10_PSSI_D8            HAL_GPIO_AF_10 /*!< PSSI Data I/O 8                     */
#define HAL_GPIO_AF10_PSSI_D9            HAL_GPIO_AF_10 /*!< PSSI Data I/O 9                     */
#define HAL_GPIO_AF10_PSSI_D10           HAL_GPIO_AF_10 /*!< PSSI Data I/O 10                    */
#define HAL_GPIO_AF10_PSSI_D11           HAL_GPIO_AF_10 /*!< PSSI Data I/O 11                    */
#define HAL_GPIO_AF10_PSSI_D12           HAL_GPIO_AF_10 /*!< PSSI Data I/O 12                    */
#define HAL_GPIO_AF10_PSSI_D13           HAL_GPIO_AF_10 /*!< PSSI Data I/O 13                    */
#define HAL_GPIO_AF10_PSSI_D14           HAL_GPIO_AF_10 /*!< PSSI Data I/O 14                    */
#define HAL_GPIO_AF10_PSSI_PDCK          HAL_GPIO_AF_10 /*!< PSSI Parallel Data Clock Input      */
#define HAL_GPIO_AF10_PSSI_DE            HAL_GPIO_AF_10 /*!< PSSI Data enable signal             */
#define HAL_GPIO_AF10_PSSI_RDY           HAL_GPIO_AF_10 /*!< PSSI Ready signal                   */
#define HAL_GPIO_AF10_OCTOSPIM_P1        HAL_GPIO_AF_10 /*!< OCTOSPIM_P1 Alternate Function mapping */
#define HAL_GPIO_AF10_OCTOSPIM_P1_IO0    HAL_GPIO_AF_10 /*!< OCTOSPIM_P1 Data Pin 0                 */
#define HAL_GPIO_AF10_OCTOSPIM_P1_IO1    HAL_GPIO_AF_10 /*!< OCTOSPIM_P1 Data Pin 1                 */
#define HAL_GPIO_AF10_OCTOSPIM_P1_IO2    HAL_GPIO_AF_10 /*!< OCTOSPIM_P1 Data Pin 2                 */
#define HAL_GPIO_AF10_OCTOSPIM_P1_IO3    HAL_GPIO_AF_10 /*!< OCTOSPIM_P1 Data Pin 3                 */
#define HAL_GPIO_AF10_OCTOSPIM_P1_IO4    HAL_GPIO_AF_10 /*!< OCTOSPIM_P1 Data Pin 4                 */
#define HAL_GPIO_AF10_OCTOSPIM_P1_IO5    HAL_GPIO_AF_10 /*!< OCTOSPIM_P1 Data Pin 5                 */
#define HAL_GPIO_AF10_OCTOSPIM_P1_IO6    HAL_GPIO_AF_10 /*!< OCTOSPIM_P1 Data Pin 6                 */
#define HAL_GPIO_AF10_OCTOSPIM_P1_IO7    HAL_GPIO_AF_10 /*!< OCTOSPIM_P1 Data Pin 7                 */
#define HAL_GPIO_AF10_OCTOSPIM_P1_DQS    HAL_GPIO_AF_10 /*!< OCTOSPIM_P1 Memory Data Strobe I/O     */
#define HAL_GPIO_AF10_OCTOSPIM_P1_NCS    HAL_GPIO_AF_10 /*!< OCTOSPIM_P1 Memory Chip Select         */
#define HAL_GPIO_AF10_OCTOSPIM_P1_CLK    HAL_GPIO_AF_10 /*!< OCTOSPIM_P1 Clock                      */
#define HAL_GPIO_AF10_OCTOSPIM_P1_NCLK   HAL_GPIO_AF_10 /*!< OCTOSPIM_P1 Inverted Clock             */
#if defined(OCTOSPI2)
#define HAL_GPIO_AF10_OCTOSPIM_P2        HAL_GPIO_AF_10 /*!< OCTOSPIM_P2 Alternate Function mapping */
#define HAL_GPIO_AF10_OCTOSPIM_P2_NCS    HAL_GPIO_AF_10 /*!< OCTOSPIM_P2 Memory Chip Select         */
#endif /* OCTOSPI2 */
#define HAL_GPIO_AF10_CRS                HAL_GPIO_AF_10 /*!< CRS Alternate Function mapping      */
#define HAL_GPIO_AF10_CRS_SYNC           HAL_GPIO_AF_10 /*!< CRS Synchronization source          */
#if defined(USB_OTG_HS)
#define HAL_GPIO_AF10_USB_OTG_HS         HAL_GPIO_AF_10 /*!< USB OTG Alternate Function mapping  */
#define HAL_GPIO_AF10_USB_OTG_HS_SOF     HAL_GPIO_AF_10 /*!< USB OTG Start of frame              */
#define HAL_GPIO_AF10_USB_OTG_HS_ID      HAL_GPIO_AF_10 /*!< USB OTG Device Identification       */
#endif /* USB_OTG_HS */
#if defined(GFXTIM)
#define HAL_GPIO_AF10_GFXTIM             HAL_GPIO_AF_10 /*!< GFXTIM Alternate Function mapping   */
#define HAL_GPIO_AF10_GFXTIM_TE          HAL_GPIO_AF_10 /*!< GFXTIM Tearing Effect               */
#endif /* GFXTIM */
#if defined(DSI)
#define HAL_GPIO_AF10_DSI                HAL_GPIO_AF_10 /*!< DSI Alternate Function mapping      */
#define HAL_GPIO_AF10_DSI_TE             HAL_GPIO_AF_10 /*!< DSI Tearing Effect                  */
#endif /* DSI */

/**
  * @brief   AF 11 selection
  */
#if defined (UCPD1)
#define HAL_GPIO_AF11_UCPD1              HAL_GPIO_AF_11 /*!< UCPD1 Alternate Function mapping                  */
#define HAL_GPIO_AF11_UCPD1_FRSTX1       HAL_GPIO_AF_11 /*!< UCPD1 Fast Role Swap signaling output 1           */
#define HAL_GPIO_AF11_UCPD1_FRSTX2       HAL_GPIO_AF_11 /*!< UCPD1 Fast Role Swap signaling output 2           */
#endif /* UCPD1 */
#define HAL_GPIO_AF11_LPGPIO1            HAL_GPIO_AF_11 /*!< LPGPIO1 Alternate Function mapping                */
#define HAL_GPIO_AF11_LPGPIO1_P0         HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 0                                     */
#define HAL_GPIO_AF11_LPGPIO1_P1         HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 1                                     */
#define HAL_GPIO_AF11_LPGPIO1_P2         HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 2                                     */
#define HAL_GPIO_AF11_LPGPIO1_P3         HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 3                                     */
#define HAL_GPIO_AF11_LPGPIO1_P4         HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 4                                     */
#define HAL_GPIO_AF11_LPGPIO1_P5         HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 5                                     */
#define HAL_GPIO_AF11_LPGPIO1_P6         HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 6                                     */
#define HAL_GPIO_AF11_LPGPIO1_P7         HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 7                                     */
#define HAL_GPIO_AF11_LPGPIO1_P8         HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 8                                     */
#define HAL_GPIO_AF11_LPGPIO1_P9         HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 9                                     */
#define HAL_GPIO_AF11_LPGPIO1_P10        HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 10                                    */
#define HAL_GPIO_AF11_LPGPIO1_P11        HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 11                                    */
#define HAL_GPIO_AF11_LPGPIO1_P12        HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 12                                    */
#define HAL_GPIO_AF11_LPGPIO1_P13        HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 13                                    */
#define HAL_GPIO_AF11_LPGPIO1_P14        HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 14                                    */
#define HAL_GPIO_AF11_LPGPIO1_P15        HAL_GPIO_AF_11 /*!< LPGPIO1 Pin 15                                    */
#if defined (FMC_BASE)
#define HAL_GPIO_AF11_FMC                HAL_GPIO_AF_11 /*!< FMC Alternate Function mapping                    */
#define HAL_GPIO_AF11_FMC_NBL1           HAL_GPIO_AF_11 /*!< FMC Byte lane output 1                            */
#endif /* FMC_BASE */
#if defined (SDMMC2)
#define HAL_GPIO_AF11_SDMMC2             HAL_GPIO_AF_11 /*!< SDMMC2 Alternate Function mapping                 */
#define HAL_GPIO_AF11_SDMMC2_CMD         HAL_GPIO_AF_11 /*!< SDMMC2 Card bidirectional command/response signal */
#define HAL_GPIO_AF11_SDMMC2_CK          HAL_GPIO_AF_11 /*!< SDMMC2 Card clock                                 */
#define HAL_GPIO_AF11_SDMMC2_D4          HAL_GPIO_AF_11 /*!< SDMMC2 Card bidirectional data line 4             */
#define HAL_GPIO_AF11_SDMMC2_D5          HAL_GPIO_AF_11 /*!< SDMMC2 Card bidirectional data line 5             */
#define HAL_GPIO_AF11_SDMMC2_D6          HAL_GPIO_AF_11 /*!< SDMMC2 Card bidirectional data line 6             */
#define HAL_GPIO_AF11_SDMMC2_D7          HAL_GPIO_AF_11 /*!< SDMMC2 Card bidirectional data line 7             */
#endif /* SDMMC2 */
#if defined(DSI)
#define HAL_GPIO_AF11_DSI                HAL_GPIO_AF_11 /*!< DSI Alternate Function mapping                    */
#define HAL_GPIO_AF11_DSI_TE             HAL_GPIO_AF_11 /*!< DSI Tearing Effect                                */
#endif /*  DSI */
#if defined(GFXTIM)
#define HAL_GPIO_AF11_GFXTIM             HAL_GPIO_AF_11 /*!< GFXTIM Alternate Function mapping                 */
#define HAL_GPIO_AF11_GFXTIM_FCKCAL      HAL_GPIO_AF_11 /*!< GFXTIM Frame Clock Calibration Output             */
#define HAL_GPIO_AF11_GFXTIM_LCKCAL      HAL_GPIO_AF_11 /*!< GFXTIM Line Clock Calibration Output              */
#define HAL_GPIO_AF11_GFXTIM_TE          HAL_GPIO_AF_11 /*!< GFXTIM Tearing Effect                             */
#endif /* GFXTIM */

/**
  * @brief   AF 12 selection
  */
#define HAL_GPIO_AF12_TRACECLK           HAL_GPIO_AF_12 /*!< TRACE Clock                                       */
#define HAL_GPIO_AF12_COMP1              HAL_GPIO_AF_12 /*!< COMP1 Alternate Function mapping                  */
#define HAL_GPIO_AF12_COMP1_OUT          HAL_GPIO_AF_12 /*!< COMP1 Output channel                              */
#if defined (COMP2)
#define HAL_GPIO_AF12_COMP2              HAL_GPIO_AF_12 /*!< COMP2 Alternate Function mapping                  */
#define HAL_GPIO_AF12_COMP2_OUT          HAL_GPIO_AF_12 /*!< COMP2 Output channel                              */
#endif /* COMP2 */
#if defined (FMC_BASE)
#define HAL_GPIO_AF12_FMC                HAL_GPIO_AF_12 /*!< FMC Alternate Function mapping                    */
#define HAL_GPIO_AF12_FMC_ALE            HAL_GPIO_AF_12 /*!< FMC Address Latch Enable                          */
#define HAL_GPIO_AF12_FMC_CLE            HAL_GPIO_AF_12 /*!< FMC Command Latch Enable                          */
#define HAL_GPIO_AF12_FMC_CLK            HAL_GPIO_AF_12 /*!< FMC Clock Output                                  */
#define HAL_GPIO_AF12_FMC_INT            HAL_GPIO_AF_12 /*!< FMC NAND flash ready/busy input                   */
#define HAL_GPIO_AF12_FMC_NBL0           HAL_GPIO_AF_12 /*!< FMC Byte lane output 0                            */
#define HAL_GPIO_AF12_FMC_NBL1           HAL_GPIO_AF_12 /*!< FMC Byte lane output 1                            */
#define HAL_GPIO_AF12_FMC_NCE            HAL_GPIO_AF_12 /*!< FMC NAND Chip select                              */
#define HAL_GPIO_AF12_FMC_NE1            HAL_GPIO_AF_12 /*!< FMC Chip select 1                                 */
#define HAL_GPIO_AF12_FMC_NE2            HAL_GPIO_AF_12 /*!< FMC Chip select 2                                 */
#define HAL_GPIO_AF12_FMC_NE3            HAL_GPIO_AF_12 /*!< FMC Chip select 3                                 */
#define HAL_GPIO_AF12_FMC_NE4            HAL_GPIO_AF_12 /*!< FMC Chip select 4                                 */
#define HAL_GPIO_AF12_FMC_NL             HAL_GPIO_AF_12 /*!< FMC Latch enable                                  */
#define HAL_GPIO_AF12_FMC_NOE            HAL_GPIO_AF_12 /*!< FMC Output enable A                               */
#define HAL_GPIO_AF12_FMC_NWE            HAL_GPIO_AF_12 /*!< FMC Write enable                                  */
#define HAL_GPIO_AF12_FMC_NWAIT          HAL_GPIO_AF_12 /*!< FMC NAND flash ready/busy input                   */
#define HAL_GPIO_AF12_FMC_A0             HAL_GPIO_AF_12 /*!< FMC Address bus bit 0                             */
#define HAL_GPIO_AF12_FMC_A1             HAL_GPIO_AF_12 /*!< FMC Address bus bit 1                             */
#define HAL_GPIO_AF12_FMC_A2             HAL_GPIO_AF_12 /*!< FMC Address bus bit 2                             */
#define HAL_GPIO_AF12_FMC_A3             HAL_GPIO_AF_12 /*!< FMC Address bus bit 3                             */
#define HAL_GPIO_AF12_FMC_A4             HAL_GPIO_AF_12 /*!< FMC Address bus bit 4                             */
#define HAL_GPIO_AF12_FMC_A5             HAL_GPIO_AF_12 /*!< FMC Address bus bit 5                             */
#define HAL_GPIO_AF12_FMC_A6             HAL_GPIO_AF_12 /*!< FMC Address bus bit 6                             */
#define HAL_GPIO_AF12_FMC_A7             HAL_GPIO_AF_12 /*!< FMC Address bus bit 7                             */
#define HAL_GPIO_AF12_FMC_A8             HAL_GPIO_AF_12 /*!< FMC Address bus bit 8                             */
#define HAL_GPIO_AF12_FMC_A9             HAL_GPIO_AF_12 /*!< FMC Address bus bit 9                             */
#define HAL_GPIO_AF12_FMC_A10            HAL_GPIO_AF_12 /*!< FMC Address bus bit 10                            */
#define HAL_GPIO_AF12_FMC_A11            HAL_GPIO_AF_12 /*!< FMC Address bus bit 11                            */
#define HAL_GPIO_AF12_FMC_A12            HAL_GPIO_AF_12 /*!< FMC Address bus bit 12                            */
#define HAL_GPIO_AF12_FMC_A13            HAL_GPIO_AF_12 /*!< FMC Address bus bit 13                            */
#define HAL_GPIO_AF12_FMC_A14            HAL_GPIO_AF_12 /*!< FMC Address bus bit 14                            */
#define HAL_GPIO_AF12_FMC_A15            HAL_GPIO_AF_12 /*!< FMC Address bus bit 15                            */
#define HAL_GPIO_AF12_FMC_A16            HAL_GPIO_AF_12 /*!< FMC Address bus bit 16                            */
#define HAL_GPIO_AF12_FMC_A17            HAL_GPIO_AF_12 /*!< FMC Address bus bit 17                            */
#define HAL_GPIO_AF12_FMC_A18            HAL_GPIO_AF_12 /*!< FMC Address bus bit 18                            */
#define HAL_GPIO_AF12_FMC_A19            HAL_GPIO_AF_12 /*!< FMC Address bus bit 19                            */
#define HAL_GPIO_AF12_FMC_A20            HAL_GPIO_AF_12 /*!< FMC Address bus bit 20                            */
#define HAL_GPIO_AF12_FMC_A21            HAL_GPIO_AF_12 /*!< FMC Address bus bit 21                            */
#define HAL_GPIO_AF12_FMC_A22            HAL_GPIO_AF_12 /*!< FMC Address bus bit 22                            */
#define HAL_GPIO_AF12_FMC_A23            HAL_GPIO_AF_12 /*!< FMC Address bus bit 23                            */
#define HAL_GPIO_AF12_FMC_A24            HAL_GPIO_AF_12 /*!< FMC Address bus bit 24                            */
#define HAL_GPIO_AF12_FMC_A25            HAL_GPIO_AF_12 /*!< FMC Address bus bit 25                            */
#define HAL_GPIO_AF12_FMC_D0             HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 0                  */
#define HAL_GPIO_AF12_FMC_D1             HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 1                  */
#define HAL_GPIO_AF12_FMC_D2             HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 2                  */
#define HAL_GPIO_AF12_FMC_D3             HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 3                  */
#define HAL_GPIO_AF12_FMC_D4             HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 4                  */
#define HAL_GPIO_AF12_FMC_D5             HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 5                  */
#define HAL_GPIO_AF12_FMC_D6             HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 6                  */
#define HAL_GPIO_AF12_FMC_D7             HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 7                  */
#define HAL_GPIO_AF12_FMC_D8             HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 8                  */
#define HAL_GPIO_AF12_FMC_D9             HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 9                  */
#define HAL_GPIO_AF12_FMC_D10            HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 10                 */
#define HAL_GPIO_AF12_FMC_D11            HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 11                 */
#define HAL_GPIO_AF12_FMC_D12            HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 12                 */
#define HAL_GPIO_AF12_FMC_D13            HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 13                 */
#define HAL_GPIO_AF12_FMC_D14            HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 14                 */
#define HAL_GPIO_AF12_FMC_D15            HAL_GPIO_AF_12 /*!< FMC Bidirectional data bus bit 15                 */
#endif /* FMC_BASE */
#define HAL_GPIO_AF12_SDMMC1             HAL_GPIO_AF_12 /*!< SDMMC1 Alternate Function mapping                 */
#define HAL_GPIO_AF12_SDMMC1_CMD         HAL_GPIO_AF_12 /*!< SDMMC1 Card bidirectional command/response signal */
#define HAL_GPIO_AF12_SDMMC1_CK          HAL_GPIO_AF_12 /*!< SDMMC1 Card clock                                 */
#define HAL_GPIO_AF12_SDMMC1_D0          HAL_GPIO_AF_12 /*!< SDMMC2 Card bidirectional data line 0             */
#define HAL_GPIO_AF12_SDMMC1_D1          HAL_GPIO_AF_12 /*!< SDMMC2 Card bidirectional data line 1             */
#define HAL_GPIO_AF12_SDMMC1_D2          HAL_GPIO_AF_12 /*!< SDMMC2 Card bidirectional data line 2             */
#define HAL_GPIO_AF12_SDMMC1_D3          HAL_GPIO_AF_12 /*!< SDMMC2 Card bidirectional data line 3             */
#define HAL_GPIO_AF12_SDMMC1_D4          HAL_GPIO_AF_12 /*!< SDMMC2 Card bidirectional data line 4             */
#define HAL_GPIO_AF12_SDMMC1_D5          HAL_GPIO_AF_12 /*!< SDMMC2 Card bidirectional data line 5             */
#define HAL_GPIO_AF12_SDMMC1_D6          HAL_GPIO_AF_12 /*!< SDMMC2 Card bidirectional data line 6             */
#define HAL_GPIO_AF12_SDMMC1_D7          HAL_GPIO_AF_12 /*!< SDMMC2 Card bidirectional data line 7             */
#if defined (SDMMC2)
#define HAL_GPIO_AF12_SDMMC2             HAL_GPIO_AF_12 /*!< SDMMC2 Alternate Function mapping                 */
#define HAL_GPIO_AF12_SDMMC2_CMD         HAL_GPIO_AF_12 /*!< SDMMC2 Card bidirectional command/response signal */
#define HAL_GPIO_AF12_SDMMC2_CK          HAL_GPIO_AF_12 /*!< SDMMC2 Card clock                                 */
#define HAL_GPIO_AF12_SDMMC2_D0          HAL_GPIO_AF_12 /*!< SDMMC2 Card bidirectional data line 0             */
#define HAL_GPIO_AF12_SDMMC2_D1          HAL_GPIO_AF_12 /*!< SDMMC2 Card bidirectional data line 1             */
#define HAL_GPIO_AF12_SDMMC2_D2          HAL_GPIO_AF_12 /*!< SDMMC2 Card bidirectional data line 2             */
#define HAL_GPIO_AF12_SDMMC2_D3          HAL_GPIO_AF_12 /*!< SDMMC2 Card bidirectional data line 3             */
#endif /* SDMMC2 */

/**
  * @brief   AF 13 selection
  */
#define HAL_GPIO_AF13_AUDIOCLK           HAL_GPIO_AF_13 /*!< Audio Clock                              */
#define HAL_GPIO_AF13_SAI1               HAL_GPIO_AF_13 /*!< SAI1 Alternate Function mapping          */
#define HAL_GPIO_AF13_SAI1_MCLK_A        HAL_GPIO_AF_13 /*!< SAI1 Audio Block A master clock          */
#define HAL_GPIO_AF13_SAI1_MCLK_B        HAL_GPIO_AF_13 /*!< SAI1 Audio Block B master clock          */
#define HAL_GPIO_AF13_SAI1_SCK_A         HAL_GPIO_AF_13 /*!< SAI1 Audio Block A bit clock             */
#define HAL_GPIO_AF13_SAI1_SCK_B         HAL_GPIO_AF_13 /*!< SAI1 Audio Block B bit clock             */
#define HAL_GPIO_AF13_SAI1_FS_A          HAL_GPIO_AF_13 /*!< SAI1 Audio Block A Frame synchronization */
#define HAL_GPIO_AF13_SAI1_FS_B          HAL_GPIO_AF_13 /*!< SAI1 Audio Block A Frame synchronization */
#define HAL_GPIO_AF13_SAI1_SD_A          HAL_GPIO_AF_13 /*!< SAI1 Audio Block A Data line             */
#define HAL_GPIO_AF13_SAI1_SD_B          HAL_GPIO_AF_13 /*!< SAI1 Audio Block B Data line             */
#if defined (SAI2)
#define HAL_GPIO_AF13_SAI2               HAL_GPIO_AF_13 /*!< SAI2 Alternate Function mapping          */
#define HAL_GPIO_AF13_SAI2_MCLK_A        HAL_GPIO_AF_13 /*!< SAI2 Audio Block A master clock          */
#define HAL_GPIO_AF13_SAI2_MCLK_B        HAL_GPIO_AF_13 /*!< SAI2 Audio Block B master clock          */
#define HAL_GPIO_AF13_SAI2_SCK_A         HAL_GPIO_AF_13 /*!< SAI2 Audio Block A bit clock             */
#define HAL_GPIO_AF13_SAI2_SCK_B         HAL_GPIO_AF_13 /*!< SAI2 Audio Block B bit clock             */
#define HAL_GPIO_AF13_SAI2_FS_A          HAL_GPIO_AF_13 /*!< SAI2 Audio Block A Frame synchronization */
#define HAL_GPIO_AF13_SAI2_FS_B          HAL_GPIO_AF_13 /*!< SAI2 Audio Block A Frame synchronization */
#define HAL_GPIO_AF13_SAI2_SD_A          HAL_GPIO_AF_13 /*!< SAI2 Audio Block A Data line             */
#define HAL_GPIO_AF13_SAI2_SD_B          HAL_GPIO_AF_13 /*!< SAI2 Audio Block B Data line             */
#endif /* SAI2 */
#define HAL_GPIO_AF13_LPTIM4             HAL_GPIO_AF_13 /*!< LPTIM4 Alternate Function mapping        */
#define HAL_GPIO_AF13_LPTIM4_ETR         HAL_GPIO_AF_13 /*!< LPTIM4 External trigger input            */
#define HAL_GPIO_AF13_LPTIM4_IN1         HAL_GPIO_AF_13 /*!< LPTIM4 Channel 1 Input                   */
#define HAL_GPIO_AF13_LPTIM4_OUT         HAL_GPIO_AF_13 /*!< LPTIM4 Output                            */
#define HAL_GPIO_AF13_LPTIM2             HAL_GPIO_AF_13 /*!< LPTIM2 Alternate Function mapping        */
#define HAL_GPIO_AF13_LPTIM2_CH2         HAL_GPIO_AF_13 /*!< LPTIM2 Multi-purpose Channel 2           */
#if defined(GFXTIM)
#define HAL_GPIO_AF13_GFXTIM             HAL_GPIO_AF_13 /*!< GFXTIM Alternate Function mapping         */
#define HAL_GPIO_AF13_GFXTIM_FCKCAL      HAL_GPIO_AF_13 /*!< GFXTIM Frame Clock Calibration            */
#define HAL_GPIO_AF13_GFXTIM_LCKCAL      HAL_GPIO_AF_13 /*!< GFXTIM Line Clock Calibration             */
#endif /* GFXTIM */

/**
  * @brief   AF 14 selection
  */
#define HAL_GPIO_AF14_LPTIM2             HAL_GPIO_AF_14 /*!< LPTIM2 Alternate Function mapping */
#define HAL_GPIO_AF14_LPTIM2_CH1         HAL_GPIO_AF_14 /*!< LPTIM2 Multi-purpose Channel 1    */
#define HAL_GPIO_AF14_LPTIM2_IN1         HAL_GPIO_AF_14 /*!< LPTIM2 Channel 1 Input            */
#define HAL_GPIO_AF14_LPTIM2_CH2         HAL_GPIO_AF_14 /*!< LPTIM2 Multi-purpose Channel 2    */
#define HAL_GPIO_AF14_LPTIM2_ETR         HAL_GPIO_AF_14 /*!< LPTIM2 External trigger input     */
#define HAL_GPIO_AF14_LPTIM3             HAL_GPIO_AF_14 /*!< LPTIM3 Alternate Function mapping */
#define HAL_GPIO_AF14_LPTIM3_CH1         HAL_GPIO_AF_14 /*!< LPTIM3 Multi-purpose Channel 1    */
#define HAL_GPIO_AF14_LPTIM3_IN1         HAL_GPIO_AF_14 /*!< LPTIM3 Channel 1 Input            */
#define HAL_GPIO_AF14_LPTIM3_CH2         HAL_GPIO_AF_14 /*!< LPTIM3 Multi-purpose Channel 2    */
#define HAL_GPIO_AF14_LPTIM3_ETR         HAL_GPIO_AF_14 /*!< LPTIM3 External trigger input     */
#define HAL_GPIO_AF14_TIM2               HAL_GPIO_AF_14 /*!< TIM2 Alternate Function mapping   */
#define HAL_GPIO_AF14_TIM2_ETR           HAL_GPIO_AF_14 /*!< TIM2 External trigger input       */
#define HAL_GPIO_AF14_TIM15              HAL_GPIO_AF_14 /*!< TIM15 Alternate Function mapping  */
#define HAL_GPIO_AF14_TIM15_BKIN         HAL_GPIO_AF_14 /*!< TIM15 Break input                 */
#define HAL_GPIO_AF14_TIM15_CH1N         HAL_GPIO_AF_14 /*!< TIM15 CH1 complementary output    */
#define HAL_GPIO_AF14_TIM15_CH1          HAL_GPIO_AF_14 /*!< TIM15 Multi-purpose Channel 1     */
#define HAL_GPIO_AF14_TIM15_CH2          HAL_GPIO_AF_14 /*!< TIM15 Multi-purpose Channel 2     */
#define HAL_GPIO_AF14_TIM16              HAL_GPIO_AF_14 /*!< TIM16 Alternate Function mapping  */
#define HAL_GPIO_AF14_TIM16_CH1N         HAL_GPIO_AF_14 /*!< TIM16 CH1 complementary output    */
#define HAL_GPIO_AF14_TIM16_CH1          HAL_GPIO_AF_14 /*!< TIM16 Multi-purpose Channel 1     */
#define HAL_GPIO_AF14_TIM17              HAL_GPIO_AF_14 /*!< TIM17 Alternate Function mapping  */
#define HAL_GPIO_AF14_TIM17_BKIN         HAL_GPIO_AF_14 /*!< TIM17 Break input                 */
#define HAL_GPIO_AF14_TIM17_CH1          HAL_GPIO_AF_14 /*!< TIM17 Multi-purpose Channel 1     */
#define HAL_GPIO_AF14_TIM17_CH1N         HAL_GPIO_AF_14 /*!< TIM17 CH1 complementary output    */
#if defined (FMC_BASE)
#define HAL_GPIO_AF14_FMC                HAL_GPIO_AF_14 /*!< FMC Alternate Function mapping    */
#define HAL_GPIO_AF14_FMC_A20            HAL_GPIO_AF_14 /*!< FMC Address bus bit 20            */
#endif /* FMC_BASE */

/**
  * @brief   AF 15 selection
  */
#define HAL_GPIO_AF15_EVENTOUT           HAL_GPIO_AF_15 /*!< EVENTOUT Alternate Function mapping */
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Functions HAL GPIO Functions
  * @{
  */

/** @defgroup GPIO_Exported_Functions_Group1 Initialization/de-initialization functions
  * @{
  */

hal_status_t  HAL_GPIO_Init(hal_gpio_t gpiox, uint32_t pins, const hal_gpio_config_t *p_config);
void          HAL_GPIO_DeInit(hal_gpio_t  gpiox, uint32_t pins);

/**
  * @}
  */

/** @defgroup GPIO_Exported_Functions_Group2 IO operation functions
  * @{
  */

hal_gpio_pin_state_t HAL_GPIO_ReadPin(hal_gpio_t gpiox, uint32_t pin);
void HAL_GPIO_WritePin(hal_gpio_t gpiox, uint32_t pins, hal_gpio_pin_state_t pin_state);
void HAL_GPIO_WriteMultipleStatePin(hal_gpio_t gpiox, uint32_t pins_reset, uint32_t pins_set);
void HAL_GPIO_TogglePin(hal_gpio_t gpiox, uint32_t pins);
hal_status_t HAL_GPIO_LockPin(hal_gpio_t gpiox, uint32_t pins);
#if defined(USE_HAL_GPIO_HSLV) && (USE_HAL_GPIO_HSLV == 1U)
void HAL_GPIO_EnableHighSpeedLowVoltage(hal_gpio_t gpiox, uint32_t pins);
void HAL_GPIO_DisableHighSpeedLowVoltage(hal_gpio_t gpiox, uint32_t pins);
#endif /* USE_HAL_GPIO_HSLV */
hal_status_t HAL_GPIO_EnableSystemDependencies(hal_gpio_t gpiox, uint32_t pins);
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

#endif /* STM32U5XX_HAL_GPIO_H */
