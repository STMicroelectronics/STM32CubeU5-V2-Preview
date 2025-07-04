# origin-pack: STMicroelectronics::stm32u5xx_hal_drivers@2.0.0-beta.1.1
# created-by: conversion-manager@0.0.53
project(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE)

# List of all CMSIS properties that influence conditions for this package
if(NOT DEFINED CMSIS_Dname)
  set(CMSIS_Dname "CMSIS_Dname not set")
  message(DEBUG "CMSIS_Dname is not set to any value")
endif()

if(NOT DEFINED CMSIS_Dvendor)
  set(CMSIS_Dvendor "CMSIS_Dvendor not set")
  message(DEBUG "CMSIS_Dvendor is not set to any value")
endif()


# Device specific defined symbols


# Include RTE_Components.h globally if needed


# Include Pre_Include_Global.h globally if needed


# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1)
  set(CMSIS_USE_Device_STM32_HAL_timebases_SYSTICK_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_timebases_RTC_ALARM_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_timebases_RTC_WAKEUP_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_TIM_template_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_timebases_TIM_0_2_1 true)
  set(CMSIS_USE_Device_STM32_HAL_Core_0_4_2 true)
  set(CMSIS_USE_Device_STM32_HAL_UTILS_I2C_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_UTILS_FDCAN_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_ASSERT_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_template_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_ADC_0_5_1 true)
  set(CMSIS_USE_Device_STM32_HAL_ADF_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_AES_0_2_1 true)
  set(CMSIS_USE_Device_STM32_HAL_COMP_0_2_3 true)
  set(CMSIS_USE_Device_STM32_HAL_CORDIC_0_2_2 true)
  set(CMSIS_USE_Device_STM32_HAL_CORTEX_0_5_0 true)
  set(CMSIS_USE_Device_STM32_HAL_CRC_0_3_1 true)
  set(CMSIS_USE_Device_STM32_HAL_CRS_0_2_1 true)
  set(CMSIS_USE_Device_STM32_HAL_DAC_0_4_2 true)
  set(CMSIS_USE_Device_STM32_HAL_DBGMCU_0_2_2 true)
  set(CMSIS_USE_Device_STM32_HAL_DCACHE_0_3_1 true)
  set(CMSIS_USE_Device_STM32_HAL_DCMI_0_2_2 true)
  set(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_DLYB_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_DMA_0_7_0 true)
  set(CMSIS_USE_Device_STM32_HAL_DMA2D_0_3_3 true)
  set(CMSIS_USE_Device_STM32_HAL_DSI_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_EXTI_0_3_3 true)
  set(CMSIS_USE_Device_STM32_HAL_FDCAN_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_FLASH_0_6_0 true)
  set(CMSIS_USE_Device_STM32_HAL_FLASH_ITF_0_4_0 true)
  set(CMSIS_USE_Device_STM32_HAL_FMAC_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_FMC_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_GFXMMU_0_1_4 true)
  set(CMSIS_USE_Device_STM32_HAL_GFXTIM_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_GPU2D_0_3_1 true)
  set(CMSIS_USE_Device_STM32_HAL_GPIO_0_2_6 true)
  set(CMSIS_USE_Device_STM32_HAL_GTZC_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_HASH_0_4_0 true)
  set(CMSIS_USE_Device_STM32_HAL_HCD_0_4_0 true)
  set(CMSIS_USE_Device_STM32_HAL_I2C_0_5_0 true)
  set(CMSIS_USE_Device_STM32_HAL_ICACHE_0_4_0 true)
  set(CMSIS_USE_Device_STM32_HAL_JPEG_0_1_4 true)
  set(CMSIS_USE_Device_STM32_HAL_IWDG_0_3_1 true)
  set(CMSIS_USE_Device_STM32_HAL_LPTIM_0_5_0 true)
  set(CMSIS_USE_Device_STM32_HAL_LTDC_0_6_0 true)
  set(CMSIS_USE_Device_STM32_HAL_MDF_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_MMC_0_2_1 true)
  set(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_OTFDEC_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_NAND_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_NOR_0_4_0 true)
  set(CMSIS_USE_Device_STM32_HAL_OPAMP_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_PCD_0_4_1 true)
  set(CMSIS_USE_Device_STM32_HAL_PKA_0_3_2 true)
  set(CMSIS_USE_Device_STM32_HAL_PSSI_0_1_5 true)
  set(CMSIS_USE_Device_STM32_HAL_PWR_0_5_2 true)
  set(CMSIS_USE_Device_STM32_HAL_Q_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_RAMCFG_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_RCC_0_6_0 true)
  set(CMSIS_USE_Device_STM32_HAL_RNG_0_3_3 true)
  set(CMSIS_USE_Device_STM32_HAL_RTC_0_2_4 true)
  set(CMSIS_USE_Device_STM32_HAL_SAI_0_2_2 true)
  set(CMSIS_USE_Device_STM32_HAL_SD_0_7_0 true)
  set(CMSIS_USE_Device_STM32_HAL_SDIO_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_SDMMC_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_SMARTCARD_0_3_1 true)
  set(CMSIS_USE_Device_STM32_HAL_SMBUS_0_3_1 true)
  set(CMSIS_USE_Device_STM32_HAL_SPI_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_SYSCFG_0_5_0 true)
  set(CMSIS_USE_Device_STM32_HAL_SRAM_0_4_0 true)
  set(CMSIS_USE_Device_STM32_HAL_TAMP_0_3_1 true)
  set(CMSIS_USE_Device_STM32_HAL_TIM_0_4_0 true)
  set(CMSIS_USE_Device_STM32_HAL_UART_0_4_1 true)
  set(CMSIS_USE_Device_STM32_HAL_UCPD_0_1_4 true)
  set(CMSIS_USE_Device_STM32_HAL_USART_0_2_4 true)
  set(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_CORE_DEF_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_DRD_0_2_2 true)
  set(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_OTG_0_2_2 true)
  set(CMSIS_USE_Device_STM32_HAL_VREFBUF_0_2_2 true)
  set(CMSIS_USE_Device_STM32_HAL_WWDG_0_4_3 true)
  set(CMSIS_USE_Device_STM32_HAL_XSPI_0_6_5 true)
  set(CMSIS_USE_Device_STM32_LL_Common_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_ADC_0_3_0 true)
  set(CMSIS_USE_Device_STM32_LL_BUS_0_1_1 true)
  set(CMSIS_USE_Device_STM32_LL_COMP_0_1_2 true)
  set(CMSIS_USE_Device_STM32_LL_CORDIC_0_1_2 true)
  set(CMSIS_USE_Device_STM32_LL_CRC_0_1_2 true)
  set(CMSIS_USE_Device_STM32_LL_CRS_0_1_1 true)
  set(CMSIS_USE_Device_STM32_LL_DAC_0_1_2 true)
  set(CMSIS_USE_Device_STM32_LL_DBGMCU_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_DCACHE_0_1_3 true)
  set(CMSIS_USE_Device_STM32_LL_DMA_0_3_0 true)
  set(CMSIS_USE_Device_STM32_LL_DMA2D_0_2_0 true)
  set(CMSIS_USE_Device_STM32_LL_FLASH_0_2_0 true)
  set(CMSIS_USE_Device_STM32_LL_EXTI_0_1_2 true)
  set(CMSIS_USE_Device_STM32_LL_FMAC_0_1_2 true)
  set(CMSIS_USE_Device_STM32_LL_GFXTIM_0_3_0 true)
  set(CMSIS_USE_Device_STM32_LL_GPIO_0_1_1 true)
  set(CMSIS_USE_Device_STM32_LL_GTZC_0_2_0 true)
  set(CMSIS_USE_Device_STM32_LL_I2C_0_2_1 true)
  set(CMSIS_USE_Device_STM32_LL_ICACHE_0_2_0 true)
  set(CMSIS_USE_Device_STM32_LL_IWDG_0_2_0 true)
  set(CMSIS_USE_Device_STM32_LL_LPGPIO_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_LPTIM_0_4_0 true)
  set(CMSIS_USE_Device_STM32_LL_LPUART_0_3_0 true)
  set(CMSIS_USE_Device_STM32_LL_OPAMP_0_1_2 true)
  set(CMSIS_USE_Device_STM32_LL_PKA_0_1_2 true)
  set(CMSIS_USE_Device_STM32_LL_PWR_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_RAMCFG_0_3_0 true)
  set(CMSIS_USE_Device_STM32_LL_RCC_0_4_0 true)
  set(CMSIS_USE_Device_STM32_LL_RNG_0_2_1 true)
  set(CMSIS_USE_Device_STM32_LL_RTC_0_3_0 true)
  set(CMSIS_USE_Device_STM32_LL_TAMP_0_3_0 true)
  set(CMSIS_USE_Device_STM32_LL_SPI_0_3_0 true)
  set(CMSIS_USE_Device_STM32_LL_SYSCFG_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_SYSTEM_0_1_2 true)
  set(CMSIS_USE_Device_STM32_LL_TIM_0_2_0 true)
  set(CMSIS_USE_Device_STM32_LL_TSC_0_1_1 true)
  set(CMSIS_USE_Device_STM32_LL_UCPD_0_1_1 true)
  set(CMSIS_USE_Device_STM32_LL_USART_0_3_0 true)
  set(CMSIS_USE_Device_STM32_LL_UTILS_0_2_0 true)
  set(CMSIS_USE_Device_STM32_LL_VREFBUF_0_1_1 true)
  set(CMSIS_USE_Device_STM32_LL_WWDG_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_HAL_OS_NO_OS_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_HAL_OS_FreeRTOS_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_HAL_OS_TEMPLATE_OS_0_1_0 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1
# description: 
if((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:CMSIS Core
# description: STMicroelectronics STM32U5 and HAL Common
if((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:CMSIS_Core true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:CMSIS_Core enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL ADC
# description: HAL ADC dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_ADC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_ADC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL COMP
# description: HAL COMP dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_COMP true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_COMP enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CONF
# description: 
set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CONF true)
message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CONF enabled")


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CONF Init
# description: 
set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CONF_Init true)
message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CONF_Init enabled")


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CONF template
# description: 
set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CONF_template true)
message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CONF_template enabled")


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORDIC
# description: HAL CORDIC dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORDIC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORDIC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE
# description: STMicroelectronics STM32U5 and HAL system
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE DMA
# description: STMicroelectronics STM32U5 and HAL with DMA
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE DMA Init
# description: STMicroelectronics HAL CORE and DMA Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA_Init true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA_Init enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE DMA Init and AES
# description: STMicroelectronics HAL AES Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA_Init_and_AES true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA_Init_and_AES enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE DMA Init and HASH
# description: STMicroelectronics HAL HASH Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA_Init_and_HASH true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA_Init_and_HASH enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE DMA Init and JPEG
# description: STMicroelectronics HAL JPEG Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA_Init_and_JPEG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA_Init_and_JPEG enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE FMC
# description: HAL CORE FMC dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_FMC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_FMC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO DMA Init
# description: STMicroelectronics HAL CORE, GPIO and DMA Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO DMA Init and ADC
# description: STMicroelectronics HAL ADC Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_ADC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_ADC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO DMA Init and DAC
# description: STMicroelectronics HAL DAC Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_DAC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_DAC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO DMA Init and I2C
# description: STMicroelectronics HAL I2C Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_I2C true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_I2C enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO DMA Init and LPTIM
# description: STMicroelectronics HAL LPTIM Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_LPTIM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_LPTIM enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO DMA Init and PSSI
# description: STMicroelectronics HAL PSSI Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_PSSI true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_PSSI enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO DMA Init and SMARTCARD
# description: STMicroelectronics HAL SMARTCARD Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_SMARTCARD true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_SMARTCARD enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO DMA Init and SPI
# description: STMicroelectronics HAL SPI Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_SPI true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_SPI enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO DMA Init and TIM
# description: STMicroelectronics HAL TIM Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_TIM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_TIM enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO DMA Init and UART
# description: STMicroelectronics HAL UART Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_UART true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_UART enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO DMA Init and USART
# description: STMicroelectronics HAL USART Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_USART true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_USART enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO DMA Init and XSPI
# description: STMicroelectronics HAL SPI Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_XSPI true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_DMA_Init_and_XSPI enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO Init and COMP
# description: HAL COMP Init dependencies
if(((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_COMP true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_COMP enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO Init and DCMI
# description: STMicroelectronics HAL DCMI Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_DCMI true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_DCMI enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO Init and FDCAN
# description: STMicroelectronics HAL FDCAN Init dependencies
if(((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_FDCAN true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_FDCAN enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO Init and GFXTIM
# description: STMicroelectronics HAL GFXTIM Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_GFXTIM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_GFXTIM enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO Init and LTDC
# description: STMicroelectronics HAL LTDC Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_LTDC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_LTDC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO Init and MMC
# description: STMicroelectronics HAL MMC Init dependencies
if(((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_MMC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_MMC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO Init and OPAMP
# description: STMicroelectronics HAL OPAMP Init dependencies
if(((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_OPAMP true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_OPAMP enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO Init and RTC
# description: STMicroelectronics HAL RTC Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_RTC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_RTC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO Init and SD
# description: STMicroelectronics HAL SD Init dependencies
if(((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_SD true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_SD enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO Init and SDIO
# description: STMicroelectronics HAL SDIO Init dependencies
if(((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_SDIO true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_SDIO enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO Init and SMBUS
# description: STMicroelectronics HAL SMBUS Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_SMBUS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_SMBUS enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE GPIO Init and TAMP
# description: STMicroelectronics HAL TAMP Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_TAMP true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_GPIO_Init_and_TAMP enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and CORTEX
# description: STMicroelectronics HAL CORTEX Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_CORTEX true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_CORTEX enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and CRC
# description: STMicroelectronics HAL CRC Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_CRC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_CRC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and CRS
# description: STMicroelectronics HAL CRS Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_CRS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_CRS enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and DCACHE
# description: STMicroelectronics HAL DCACHE Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_DCACHE true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_DCACHE enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and DMA2D
# description: STMicroelectronics HAL DMA2D Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_DMA2D true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_DMA2D enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and FLASH
# description: STMicroelectronics HAL FLASH Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_FLASH true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_FLASH enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and GFXMMU
# description: STMicroelectronics HAL GFXMMU Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_GFXMMU true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_GFXMMU enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and GPU2D
# description: STMicroelectronics HAL GPU2D Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_GPU2D true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_GPU2D enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and ICACHE
# description: STMicroelectronics HAL ICACHE Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_ICACHE true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_ICACHE enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and IWDG
# description: STMicroelectronics HAL IWDG Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_IWDG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_IWDG enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and NAND
# description: STMicroelectronics HAL NAND Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_NAND true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_NAND enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and NOR
# description: STMicroelectronics HAL NOR Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_NOR true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_NOR enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and PKA
# description: STMicroelectronics HAL PKA Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_PKA true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_PKA enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and RAMCFG
# description: STMicroelectronics HAL RAMCFG Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_RAMCFG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_RAMCFG enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and RNG
# description: STMicroelectronics HAL RNG Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_RNG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_RNG enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and SRAM
# description: STMicroelectronics HAL SRAM Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_SRAM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_SRAM enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and SYSCFG
# description: STMicroelectronics HAL SYSCFG Init dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_SYSCFG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_SYSCFG enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and VREFBUF
# description: STMicroelectronics HAL VREFBUF Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_VREFBUF true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_VREFBUF enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE Init and WWDG
# description: STMicroelectronics HAL WWDG Init dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_WWDG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_Init_and_WWDG enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE SDMMC
# description: HAL CORE SDMMC dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_SDMMC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_SDMMC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE SRAM
# description: HAL CORE SRAM dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_SRAM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_SRAM enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE USB
# description: HAL CORE USB dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_USB true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_USB enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORE XSPI
# description: HAL CORE XSPI dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_XSPI true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_XSPI enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CORTEX
# description: HAL CORTEX dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORTEX true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORTEX enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CRC
# description: HAL CRC dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CRC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CRC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL CRS
# description: HAL CRS dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CRS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CRS enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL Common
# description: STMicroelectronics STM32U5 and HAL common
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_Common true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_Common enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL DAC
# description: HAL DAC dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DAC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DAC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL DBGMCU
# description: HAL DBGMCU dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DBGMCU true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DBGMCU enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL DCACHE
# description: HAL DCACHE dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DCACHE true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DCACHE enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL DMA
# description: HAL DMA dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DMA true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DMA enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL DMA2D
# description: HAL DMA2D dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DMA2D true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DMA2D enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL EXTI
# description: HAL EXTI dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_EXTI true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_EXTI enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL FLASH
# description: HAL FLASH dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_FLASH true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_FLASH enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL FMAC
# description: HAL FMAC dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_FMAC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_FMAC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL GFXMMU
# description: HAL GFXMMU dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_GFXMMU true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_GFXMMU enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL GFXTIM
# description: HAL GFXTIM dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_GFXTIM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_GFXTIM enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL GPIO
# description: HAL GPIO dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_GPIO true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_GPIO enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL GPIO Init
# description: STMicroelectronics HAL Common Init
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_GPIO_Init true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_GPIO_Init enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL GTZC
# description: HAL GTZC dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_GTZC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_GTZC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL Generated code
# description: STMicroelectronics HAL components used for code Generation
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_Generated_code true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_Generated_code enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL I2C
# description: HAL I2C dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_I2C true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_I2C enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL ICACHE
# description: HAL ICACHE dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_ICACHE true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_ICACHE enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL IWDG
# description: HAL IWDG dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_IWDG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_IWDG enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL LPTIM
# description: HAL LPTIM dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_LPTIM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_LPTIM enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL OPAMP
# description: HAL OPAMP dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_OPAMP true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_OPAMP enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL PKA
# description: HAL PKA dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_PKA true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_PKA enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL PWR
# description: HAL PWR dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_PWR true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_PWR enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL RAMCFG
# description: HAL RAMCFG dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_RAMCFG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_RAMCFG enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL RCC
# description: HAL RCC dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_RCC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_RCC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL RNG
# description: HAL RNG dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_RNG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_RNG enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL RTC
# description: HAL RTC dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_RTC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_RTC enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL SMARTCARD
# description: HAL SMARTCARD dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_SMARTCARD true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_SMARTCARD enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL SMBUS
# description: HAL SMBUS dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_SMBUS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_SMBUS enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL SPI
# description: HAL SPI dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_SPI true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_SPI enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL SYSCFG
# description: HAL SYSCFG dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_SYSCFG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_SYSCFG enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL System Init
# description: STMicroelectronics HAL Common Init
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_System_Init true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_System_Init enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL TAMP
# description: HAL TAMP dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_TAMP true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_TAMP enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL TIM
# description: HAL TIM dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_TIM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_TIM enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL UART
# description: HAL UART dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_UART true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_UART enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL UCPD
# description: HAL UCPD dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_UCPD true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_UCPD enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL USART
# description: HAL USART dependencies
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_USART true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_USART enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL VREFBUF
# description: HAL VREFBUF dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_VREFBUF true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_VREFBUF enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL WWDG
# description: HAL WWDG dependencies
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_WWDG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_WWDG enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL
# description: STMicroelectronics STM32U5 and LL
if((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:MW FreeRTOS
# description: MW FreeRTOS used for HAL OS
if((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:MW_FreeRTOS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:MW_FreeRTOS enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:NO OS
# description: NO MW used for HAL OS
if((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:NO_OS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:NO_OS enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:RCC Init
# description: STMicroelectronics HAL Common Init
if((((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:RCC_Init true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:RCC_Init enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:STM32U5
# description: STMicroelectronics STM32U5
if((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:STM32U5 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:STM32U5 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:TEMPLATE OS
# description: TEMPLATE OS used for HAL OS
if((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:TEMPLATE_OS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:TEMPLATE_OS enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase
# description: 
set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase true)
message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase enabled")


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase HAL RTC ALARM
# description: HAL timebase based on RTC ALARM
if((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_HAL_RTC_ALARM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_HAL_RTC_ALARM enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase HAL RTC WKUP
# description: HAL timebase based on RTC WKUP
if((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_HAL_RTC_WKUP true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_HAL_RTC_WKUP enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase HAL TIM
# description: HAL timebase based on TIM
if((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_HAL_TIM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_HAL_TIM enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase Init
# description: 
set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_Init true)
message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_Init enabled")


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase NONE
# description: HAL timebase NONE
if((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_NONE true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_NONE enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase template
# description: 
set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_template true)
message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_template enabled")


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Use external env
# description: STMicroelectronics HAL condition to check if stm32_external_env.h must be generated
set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Use_external_env true)
message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Use_external_env enabled")


# condition: STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Use mutex
# description: STMicroelectronics HAL condition to check if USE_HAL_MUTEX is enabled
if(((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Use_mutex true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Use_mutex enabled")
endif()

# Files and components in this package
if(CMSIS_USE_Device_STM32_HAL_timebases_SYSTICK_0_1_0)  # HAL timebases based on Systick
  message(DEBUG "Using component Device_STM32_HAL_timebases_SYSTICK_0_1_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_NONE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_timebases_SYSTICK_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE timebases/)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_timebases_RTC_ALARM_0_1_1)  # HAL timebases based on RTC alarm
  message(DEBUG "Using component Device_STM32_HAL_timebases_RTC_ALARM_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_HAL_RTC_WKUP)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_timebases_RTC_ALARM_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE timebases/)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE timebases/stm32u5xx_hal_timebase_rtc_alarm.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_timebases_RTC_WAKEUP_0_1_1)  # HAL timebases based on RTC wakeup
  message(DEBUG "Using component Device_STM32_HAL_timebases_RTC_WAKEUP_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_HAL_RTC_ALARM)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_timebases_RTC_WAKEUP_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE timebases/)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE timebases/stm32u5xx_hal_timebase_rtc_wakeup.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_TIM_template_0_1_1)  # HAL templates
  message(DEBUG "Using component Device_STM32_HAL_TIM_template_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_Common)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_TIM_template_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE templates/common/)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE templates/timebases/)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE templates/common)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE templates/timebases)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE templates/timebases/mx_tim6.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_timebases_TIM_0_2_1)  # HAL timebases based on TIM
  message(DEBUG "Using component Device_STM32_HAL_timebases_TIM_0_2_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:Timebase_HAL_TIM)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_timebases_TIM_0_2_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE timebases/)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE timebases/stm32u5xx_hal_timebase_tim.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_Core_0_4_2)  # Common HAL driver
  message(DEBUG "Using component Device_STM32_HAL_Core_0_4_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_Common)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_Core_0_4_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll/)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_UTILS_I2C_0_1_0)  # Utilities I2C
  message(DEBUG "Using component Device_STM32_HAL_UTILS_I2C_0_1_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_Common)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_UTILS_I2C_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE utils/i2c_timing)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE utils/i2c_timing/stm32_utils_i2c.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_UTILS_FDCAN_0_1_0)  # Utilities FDCAN
  message(DEBUG "Using component Device_STM32_HAL_UTILS_FDCAN_0_1_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_Common)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_UTILS_FDCAN_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE utils/fdcan_timing)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE utils/fdcan_timing/stm32_utils_fdcan.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_ASSERT_0_1_1)  # HAL ASSERT template
  message(DEBUG "Using component Device_STM32_HAL_ASSERT_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_Common)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_ASSERT_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE templates/common)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_template_0_1_1)  # HAL templates
  message(DEBUG "Using component Device_STM32_HAL_template_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_Common)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_template_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE templates/common/)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE templates/common)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE templates/common)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_ADC_0_5_1)  # Analog-to-digital converter (ADC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_ADC_0_5_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_ADC)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_ADC_0_5_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_adc.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_ADF_0_1_1)  # ADF HAL driver
  message(DEBUG "Using component Device_STM32_HAL_ADF_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_ADF_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_adf.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_AES_0_2_1)  # Advanced Encryption Standard (AES) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_AES_0_2_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_AES_0_2_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_aes.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_COMP_0_2_3)  # Comparator (COMP) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_COMP_0_2_3")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_COMP)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_COMP_0_2_3=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_comp.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_CORDIC_0_2_2)  # CORDIC HAL driver
  message(DEBUG "Using component Device_STM32_HAL_CORDIC_0_2_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORDIC)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_CORDIC_0_2_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_cordic.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_CORTEX_0_5_0)  # Cortex (CORTEX) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_CORTEX_0_5_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORTEX)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_CORTEX_0_5_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_cortex.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_CRC_0_3_1)  # CRC calculation unit (CRC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_CRC_0_3_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CRC)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_CRC_0_3_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_crc.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_CRS_0_2_1)  # Clock Recovery CORE (CRS) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_CRS_0_2_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CRS)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_CRS_0_2_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_crs.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DAC_0_4_2)  # Digital-to-analog converter (DAC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DAC_0_4_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DAC)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DAC_0_4_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_dac.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DBGMCU_0_2_2)  # Microcontroller debug unit (DBGMCU) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DBGMCU_0_2_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DBGMCU)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DBGMCU_0_2_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_dbgmcu.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DCACHE_0_3_1)  # DCACHE HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DCACHE_0_3_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DCACHE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DCACHE_0_3_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_dcache.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DCMI_0_2_2)  # Digital camera interface HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DCMI_0_2_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DCMI_0_2_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_dcmi.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_DLYB_0_1_1)  # Delay Block (DLYB) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_DLYB_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_DLYB_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_dlyb_core.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DMA_0_7_0)  # DMA controller (DMA) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DMA_0_7_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DMA)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DMA_0_7_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_dma.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DMA2D_0_3_3)  # DMA2D controller (DMA2D) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DMA2D_0_3_3")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_DMA2D)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DMA2D_0_3_3=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_dma2d.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DSI_0_1_0)  # DSI HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DSI_0_1_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DSI_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_dsi.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_EXTI_0_3_3)  # External interrupts and events (EXTI) controller
  message(DEBUG "Using component Device_STM32_HAL_EXTI_0_3_3")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_EXTI)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_EXTI_0_3_3=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_exti.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_FDCAN_0_3_0)  # FDCAN HAL Driver
  message(DEBUG "Using component Device_STM32_HAL_FDCAN_0_3_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_FDCAN_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_fdcan.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_FLASH_0_6_0)  # Embedded FLASH memory HAL driver
  message(DEBUG "Using component Device_STM32_HAL_FLASH_0_6_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_FLASH)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_FLASH_0_6_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_flash.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_FLASH_ITF_0_4_0)  # Embedded FLASH Option Bytes HAL driver
  message(DEBUG "Using component Device_STM32_HAL_FLASH_ITF_0_4_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_FLASH)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_FLASH_ITF_0_4_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_flash_itf.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_FMAC_0_3_0)  # FMAC HAL Driver
  message(DEBUG "Using component Device_STM32_HAL_FMAC_0_3_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_FMAC)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_FMAC_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_fmac.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_FMC_0_1_0)  # FMC low layer (FMC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_FMC_0_1_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_FMC_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_fmc_core.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_GFXMMU_0_1_4)  # GFXMMU HAL driver
  message(DEBUG "Using component Device_STM32_HAL_GFXMMU_0_1_4")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_GFXMMU)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_GFXMMU_0_1_4=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_gfxmmu.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_GFXTIM_0_2_0)  # Graphic timer (GFXTIM) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_GFXTIM_0_2_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_GFXTIM)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_GFXTIM_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_gfxtim.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_GPU2D_0_3_1)  # GPU2D HAL driver
  message(DEBUG "Using component Device_STM32_HAL_GPU2D_0_3_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_GPU2D_0_3_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_gpu2d.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_GPIO_0_2_6)  # General-purpose I/O (GPIO) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_GPIO_0_2_6")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_GPIO)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_GPIO_0_2_6=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_gpio.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_GTZC_0_3_0)  # GTZC HAL driver
  message(DEBUG "Using component Device_STM32_HAL_GTZC_0_3_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_GTZC)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_GTZC_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_gtzc.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_HASH_0_4_0)  # HASH HAL driver
  message(DEBUG "Using component Device_STM32_HAL_HASH_0_4_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_HASH_0_4_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_hash.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_HCD_0_4_0)  # HCD HAL driver
  message(DEBUG "Using component Device_STM32_HAL_HCD_0_4_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_USB)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_HCD_0_4_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_hcd.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_I2C_0_5_0)  # Inter-integrated circuit (I2C) interface HAL driver
  message(DEBUG "Using component Device_STM32_HAL_I2C_0_5_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_I2C)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_I2C_0_5_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_i2c.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_ICACHE_0_4_0)  # ICACHE HAL driver
  message(DEBUG "Using component Device_STM32_HAL_ICACHE_0_4_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_ICACHE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_ICACHE_0_4_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_icache.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_JPEG_0_1_4)  # JPEG HAL driver
  message(DEBUG "Using component Device_STM32_HAL_JPEG_0_1_4")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_JPEG_0_1_4=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_jpeg.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_IWDG_0_3_1)  # Independent watchdog (IWDG) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_IWDG_0_3_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_IWDG)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_IWDG_0_3_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_iwdg.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_LPTIM_0_5_0)  # Low-power timer (LPTIM) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_LPTIM_0_5_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_LPTIM)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_LPTIM_0_5_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_lptim.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_LTDC_0_6_0)  # LTDC HAL driver
  message(DEBUG "Using component Device_STM32_HAL_LTDC_0_6_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_LTDC_0_6_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_ltdc.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_MDF_0_3_0)  # MDF HAL driver
  message(DEBUG "Using component Device_STM32_HAL_MDF_0_3_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_MDF_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_mdf.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_MMC_0_2_1)  # MMC HAL driver
  message(DEBUG "Using component Device_STM32_HAL_MMC_0_2_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_SDMMC)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_MMC_0_2_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_mmc.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_OTFDEC_0_1_1)  # On-the-fly decryption engine (OTFDEC) HAL Core driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_OTFDEC_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_OTFDEC_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_otfdec_core.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_NAND_0_1_1)  # NAND Flash controller HAL driver
  message(DEBUG "Using component Device_STM32_HAL_NAND_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_FMC)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_NAND_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_nand.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_NOR_0_4_0)  # NOR Flash controller HAL driver
  message(DEBUG "Using component Device_STM32_HAL_NOR_0_4_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_FMC)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_NOR_0_4_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_nor.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_OPAMP_0_1_1)  # OPAMP HAL driver
  message(DEBUG "Using component Device_STM32_HAL_OPAMP_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_OPAMP)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_OPAMP_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_opamp.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_PCD_0_4_1)  # USB Peripheral controller (PCD) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_PCD_0_4_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_USB)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_PCD_0_4_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_pcd.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_PKA_0_3_2)  # PKA HAL driver
  message(DEBUG "Using component Device_STM32_HAL_PKA_0_3_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_PKA)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_PKA_0_3_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_pka.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_PSSI_0_1_5)  # PSSI HAL driver
  message(DEBUG "Using component Device_STM32_HAL_PSSI_0_1_5")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_PSSI_0_1_5=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_pssi.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_PWR_0_5_2)  # Power controller (PWR) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_PWR_0_5_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_PWR)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_PWR_0_5_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_pwr.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_Q_0_1_1)  # Queue (Q) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_Q_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_Q_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_q.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_RAMCFG_0_3_0)  # RAMCFG HAL driver
  message(DEBUG "Using component Device_STM32_HAL_RAMCFG_0_3_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_RAMCFG)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_RAMCFG_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_ramcfg.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_RCC_0_6_0)  # Reset and clock control (RCC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_RCC_0_6_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_RCC)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_RCC_0_6_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_rcc.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_RNG_0_3_3)  # Random number generator (RNG) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_RNG_0_3_3")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_RNG)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_RNG_0_3_3=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_rng.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_RTC_0_2_4)  # Real-time clock (RTC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_RTC_0_2_4")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_RTC)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_RTC_0_2_4=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_rtc.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SAI_0_2_2)  # Serial audio interface (SAI) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SAI_0_2_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_DMA)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SAI_0_2_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_sai.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SD_0_7_0)  # SD HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SD_0_7_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_SDMMC)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SD_0_7_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_sd.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SDIO_0_2_0)  # SDIO HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SDIO_0_2_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_SDMMC)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SDIO_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_sdio.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_SDMMC_0_1_1)  # SD/MMC low layer (SDMMC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_SDMMC_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_SDMMC_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_sdmmc_core.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SMARTCARD_0_3_1)  # SMARTCARD HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SMARTCARD_0_3_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_SMARTCARD)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SMARTCARD_0_3_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_smartcard.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SMBUS_0_3_1)  # SMBus (SMBUS) interface HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SMBUS_0_3_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_SMBUS)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SMBUS_0_3_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_smbus.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SPI_0_2_0)  # Serial peripheral interface (SPI) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SPI_0_2_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_SPI)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SPI_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_spi.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SYSCFG_0_5_0)  # CORE configuration controller (SYSCFG) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SYSCFG_0_5_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_SYSCFG)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SYSCFG_0_5_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_syscfg.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SRAM_0_4_0)  # SRAM controller (SRAM) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SRAM_0_4_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_SRAM)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SRAM_0_4_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_sram.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_TAMP_0_3_1)  # Tampers (TAMP) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_TAMP_0_3_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_TAMP)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_TAMP_0_3_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_tamp.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_TIM_0_4_0)  # Timers (TIM) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_TIM_0_4_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_TIM)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_TIM_0_4_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_tim.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_UART_0_4_1)  # Universal asynchronous receiver transmitter (UART) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_UART_0_4_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_UART)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_UART_0_4_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_uart.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_UCPD_0_1_4)  # USB Type-C / USB Power Delivery (UCPD) interface HAL driver
  message(DEBUG "Using component Device_STM32_HAL_UCPD_0_1_4")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_UCPD)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_UCPD_0_1_4=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_ucpd.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_USART_0_2_4)  # Universal synchronous asynchronous receiver transmitter (USART) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_USART_0_2_4")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_USART)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_USART_0_2_4=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_usart.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_CORE_DEF_0_1_0)  # USB Core Def (USB CORE DEF) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_USB_CORE_DEF_0_1_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_CORE_DEF_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_DRD_0_2_2)  # USB DRD Core (USB DRD) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_USB_DRD_0_2_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_DRD_0_2_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_usb_drd_core.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_OTG_0_2_2)  # USB OTG Core (USB OTG) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_USB_OTG_0_2_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_OTG_0_2_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_usb_otg_core.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_VREFBUF_0_2_2)  # Voltage reference buffer (VREFBUF) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_VREFBUF_0_2_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_VREFBUF)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_VREFBUF_0_2_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_vrefbuf.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_WWDG_0_4_3)  # Window watchdog (WWDG) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_WWDG_0_4_3")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_WWDG)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_WWDG_0_4_3=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_wwdg.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_XSPI_0_6_5)  # Octo-SPI/Hexa-SPI (XSPI) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_XSPI_0_6_5")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:HAL_CORE_XSPI)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_XSPI_0_6_5=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE hal/stm32u5xx_hal_xspi.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_Common_0_1_0)  # Common LL driver
  message(DEBUG "Using component Device_STM32_LL_Common_0_1_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:CMSIS_Core)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_Common_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll/)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_ADC_0_3_0)  # Analog-to-digital converter (ADC) LL driver
  message(DEBUG "Using component Device_STM32_LL_ADC_0_3_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_ADC_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_BUS_0_1_1)  # LL BUS driver
  message(DEBUG "Using component Device_STM32_LL_BUS_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_BUS_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_COMP_0_1_2)  # COMP LL driver
  message(DEBUG "Using component Device_STM32_LL_COMP_0_1_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_COMP_0_1_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_CORDIC_0_1_2)  # CORDIC LL driver
  message(DEBUG "Using component Device_STM32_LL_CORDIC_0_1_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_CORDIC_0_1_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_CRC_0_1_2)  # CRC calculation unit (CRC) LL driver
  message(DEBUG "Using component Device_STM32_LL_CRC_0_1_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_CRC_0_1_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_CRS_0_1_1)  # (CRS) LL driver
  message(DEBUG "Using component Device_STM32_LL_CRS_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_CRS_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_DAC_0_1_2)  # Digital-to-analog converter (DAC) LL driver
  message(DEBUG "Using component Device_STM32_LL_DAC_0_1_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_DAC_0_1_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_DBGMCU_0_1_0)  # System configuration (DBGMCU) LL driver
  message(DEBUG "Using component Device_STM32_LL_DBGMCU_0_1_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_DBGMCU_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_DCACHE_0_1_3)  # DCACHE LL driver
  message(DEBUG "Using component Device_STM32_LL_DCACHE_0_1_3")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_DCACHE_0_1_3=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_DMA_0_3_0)  # DMA controller (DMA) LL driver
  message(DEBUG "Using component Device_STM32_LL_DMA_0_3_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_DMA_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_DMA2D_0_2_0)  # DMA2D LL driver
  message(DEBUG "Using component Device_STM32_LL_DMA2D_0_2_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_DMA2D_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_FLASH_0_2_0)  # FLASH LL driver
  message(DEBUG "Using component Device_STM32_LL_FLASH_0_2_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_FLASH_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_EXTI_0_1_2)  # Extended interrupts and events controller (EXTI) LL driver
  message(DEBUG "Using component Device_STM32_LL_EXTI_0_1_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_EXTI_0_1_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_FMAC_0_1_2)  #  (FMAC) LL driver
  message(DEBUG "Using component Device_STM32_LL_FMAC_0_1_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_FMAC_0_1_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_GFXTIM_0_3_0)  # Graphic timer (GFXTIM) LL driver
  message(DEBUG "Using component Device_STM32_LL_GFXTIM_0_3_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_GFXTIM_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_GPIO_0_1_1)  # General-purpose I/O (GPIO) LL driver
  message(DEBUG "Using component Device_STM32_LL_GPIO_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_GPIO_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_GTZC_0_2_0)  # Global TrustZone controller (GTZC) LL driver
  message(DEBUG "Using component Device_STM32_LL_GTZC_0_2_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_GTZC_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_I2C_0_2_1)  # Inter-integrated circuit (I2C) interface LL driver
  message(DEBUG "Using component Device_STM32_LL_I2C_0_2_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_I2C_0_2_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_ICACHE_0_2_0)  # ICACHE interface LL driver
  message(DEBUG "Using component Device_STM32_LL_ICACHE_0_2_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_ICACHE_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_IWDG_0_2_0)  # Independent watchdog (IWDG) LL driver
  message(DEBUG "Using component Device_STM32_LL_IWDG_0_2_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_IWDG_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_LPGPIO_0_1_0)  # LPGPIO interface LL driver
  message(DEBUG "Using component Device_STM32_LL_LPGPIO_0_1_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_LPGPIO_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_LPTIM_0_4_0)  # Low-power timer (LPTIM) interface LL driver
  message(DEBUG "Using component Device_STM32_LL_LPTIM_0_4_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_LPTIM_0_4_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_LPUART_0_3_0)  # Low-power universal asynchronous receiver transmitter (LPUART) LL driver
  message(DEBUG "Using component Device_STM32_LL_LPUART_0_3_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_LPUART_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_OPAMP_0_1_2)  # (OPAMP) LL driver
  message(DEBUG "Using component Device_STM32_LL_OPAMP_0_1_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_OPAMP_0_1_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_PKA_0_1_2)  # PKA LL driver
  message(DEBUG "Using component Device_STM32_LL_PKA_0_1_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_PKA_0_1_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_PWR_0_1_0)  # Power controller (PWR) LL driver
  message(DEBUG "Using component Device_STM32_LL_PWR_0_1_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_PWR_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_RAMCFG_0_3_0)  # RAM configuration controller (RAMCFG) LL driver
  message(DEBUG "Using component Device_STM32_LL_RAMCFG_0_3_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_RAMCFG_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_RCC_0_4_0)  # Reset and clock control (RCC) LL driver
  message(DEBUG "Using component Device_STM32_LL_RCC_0_4_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_RCC_0_4_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_RNG_0_2_1)  # Random number generator (RNG) LL driver
  message(DEBUG "Using component Device_STM32_LL_RNG_0_2_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_RNG_0_2_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_RTC_0_3_0)  # Real-time clock (RTC) LL driver
  message(DEBUG "Using component Device_STM32_LL_RTC_0_3_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_RTC_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_TAMP_0_3_0)  # (TAMP) LL driver
  message(DEBUG "Using component Device_STM32_LL_TAMP_0_3_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_TAMP_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_SPI_0_3_0)  # Serial peripheral interface (SPI) LL driver
  message(DEBUG "Using component Device_STM32_LL_SPI_0_3_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_SPI_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_SYSCFG_0_1_0)  # System configuration (SYSCFG) LL driver
  message(DEBUG "Using component Device_STM32_LL_SYSCFG_0_1_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_SYSCFG_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_SYSTEM_0_1_2)  # System configuration LL driver
  message(DEBUG "Using component Device_STM32_LL_SYSTEM_0_1_2")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_SYSTEM_0_1_2=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_TIM_0_2_0)  # Timers (TIM) LL driver
  message(DEBUG "Using component Device_STM32_LL_TIM_0_2_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_TIM_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_TSC_0_1_1)  # Touch Sensing Controller (TSC) LL driver
  message(DEBUG "Using component Device_STM32_LL_TSC_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_TSC_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_UCPD_0_1_1)  # USB Type-C / USB Power Delivery interface (UCPD) LL driver
  message(DEBUG "Using component Device_STM32_LL_UCPD_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_UCPD_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_USART_0_3_0)  # Universal synchronous asynchronous receiver transmitter (USART) LL driver
  message(DEBUG "Using component Device_STM32_LL_USART_0_3_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_USART_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_UTILS_0_2_0)  # Utils LL driver
  message(DEBUG "Using component Device_STM32_LL_UTILS_0_2_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:STM32U5)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_UTILS_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_VREFBUF_0_1_1)  # Voltage reference buffer (VREFBUF) LL driver
  message(DEBUG "Using component Device_STM32_LL_VREFBUF_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_VREFBUF_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_WWDG_0_1_1)  # System window watchdog (WWDG) LL driver
  message(DEBUG "Using component Device_STM32_LL_WWDG_0_1_1")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:LL)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_LL_WWDG_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_HAL_OS_NO_OS_0_1_0)  # HAL OS port without OS
  message(DEBUG "Using component Device_STM32_HAL_HAL_OS_NO_OS_0_1_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:NO_OS)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_HAL_OS_NO_OS_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE os_port/no_os/)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE os_port/no_os)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE os_port/no_os/stm32_hal_os.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_HAL_OS_FreeRTOS_0_1_0)  # HAL OS port with MW FreeRTOS
  message(DEBUG "Using component Device_STM32_HAL_HAL_OS_FreeRTOS_0_1_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:MW_FreeRTOS)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_HAL_OS_FreeRTOS_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE os_port/freertos/)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE os_port/freertos)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE os_port/freertos/stm32_hal_os.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_HAL_OS_TEMPLATE_OS_0_1_0)  # HAL OS port with CMSIS OS
  message(DEBUG "Using component Device_STM32_HAL_HAL_OS_TEMPLATE_OS_0_1_0")
  if(STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1:TEMPLATE_OS)
    target_compile_definitions(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE -DCMSIS_USE_Device_STM32_HAL_HAL_OS_TEMPLATE_OS_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE templates/os_port)
    target_sources(STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 INTERFACE templates/os_port/stm32_hal_os.c)
  endif()
endif()

