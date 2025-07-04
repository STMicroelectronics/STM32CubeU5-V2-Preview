
/**
  ******************************************************************************
  * @file           : mx_rcc.c
  * @brief          : STM32 RCC program body
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

/* Includes ------------------------------------------------------------------*/
#include "mx_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/******************************************************************************/
/* Exported functions for RCC in HAL layer */
/******************************************************************************/
/**
  * Configure the system core clock only and activate it using the HAL RCC unitary APIs (footprint optimization)
  *         The system Clock is configured as follow :
  *            System Clock source            = PLLCLK (MSIS)
  *            SYSCLK(Hz)                     = 160000000
  *            HCLK(Hz)                       = 160000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            APB3 Prescaler                 = 1
  *            PLL1M                          = 1
  *            PLL1N                          = 80
  *            PLL1P                          = 2
  *            PLL1Q                          = 2
  *            PLL1R                          = 2
      *            Flash Latency(WS)              = 4
  */
system_status_t mx_rcc_hal_init(void)
{
  hal_rcc_bus_clk_config_t config_bus;
  hal_rcc_pll_config_t config_pll1;


  HAL_RCC_MSIS_Enable(HAL_RCC_MSIS_FREQ_4MHZ);

  HAL_RCC_MSI_SetTrimming(16, HAL_RCC_MSI_RANGE_CALIB_4_TO_7);
            config_pll1.pll_source  = HAL_RCC_PLL_SRC_MSIS;
  config_pll1.pll_m_boost = HAL_RCC_PLLMBOOST_DIV1;
  config_pll1.pll_m       = 1;
  config_pll1.pll_n       = 80;
  config_pll1.pll_p       = 2;
  config_pll1.pll_q       = 2;
  config_pll1.pll_r       = 2;
  config_pll1.pll_fracn   = 0;
  HAL_RCC_PLL1_SetConfig(&config_pll1);

  /** Configure the main internal regulator output voltage
  */
  HAL_RCC_PWR_EnableClock();
  if (HAL_PWR_SetMainRegulatorVoltageScalingRange(HAL_PWR_VOLT_SCALE_1) != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  if (HAL_RCC_PLL1_Enable() != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  HAL_RCC_PLL1_EnableOutput(HAL_RCC_PLL1_SYSCLK);

  /** Frequency will be increased */
  HAL_FLASH_ITF_SetLatency(FLASH, HAL_FLASH_ITF_LATENCY_4);
  HAL_RCC_SetSYSCLKSource(HAL_RCC_SYSCLK_SRC_PLLCLK);

  /** Initializes the CPU, AHB and APB busses clocks
  */
  config_bus.hclk_prescaler  = HAL_RCC_HCLK_PRESCALER1;
  config_bus.pclk1_prescaler = HAL_RCC_PCLK_PRESCALER1;
  config_bus.pclk2_prescaler = HAL_RCC_PCLK_PRESCALER1;
  config_bus.pclk3_prescaler = HAL_RCC_PCLK_PRESCALER1;

  HAL_RCC_SetBusClockConfig(&config_bus);


    HAL_RCC_MSIS_SetStandbyRange(HAL_RCC_MSIS_FREQ_4MHZ);
  HAL_RCC_MSIK_SetStandbyRange(HAL_RCC_MSIK_FREQ_4MHZ);


  return SYSTEM_OK;
}

/**
  * configures and activate the clocks used by all the peripherals selected within the project
  */
system_status_t mx_rcc_peripherals_clock_config(void)
{
  /* Peripherals clocked with PCLK1 at 160000000 Hz
     I2C1
  */

  /* Peripherals clocked with PCLK2 at 160000000 Hz
     USART1
  */


  return SYSTEM_OK;
}
