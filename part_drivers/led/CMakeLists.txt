# origin-pack: STMicroelectronics::led_part_drivers@0.11.2
# created-by: conversion-manager@0.0.53
project(STMicroelectronics_led_part_drivers_0_11_2)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_led_part_drivers_0_11_2 INTERFACE)

# List of all CMSIS properties that influence conditions for this package


# Device specific defined symbols


# Include RTE_Components.h globally if needed


# Include Pre_Include_Global.h globally if needed


# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_led_part_drivers_0_11_2)
  set(CMSIS_USE_Board_Part_LED_GPIO_0_10_1 true)
  set(CMSIS_USE_Board_Part_LED_PWM_0_11_1 true)
  set(CMSIS_USE_Board_Part_LED_MFXSTM32L152_0_11_1 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.led_part_drivers.0.11.2:HAL GPIO
# description: STMicroelectronics LED GPIO HAL Driver
set(STMicroelectronics.led_part_drivers.0.11.2:HAL_GPIO true)
message(DEBUG "CMSIS condition STMicroelectronics.led_part_drivers.0.11.2:HAL_GPIO enabled")


# condition: STMicroelectronics.led_part_drivers.0.11.2:HAL PWM
# description: STMicroelectronics LED PWM HAL Driver
set(STMicroelectronics.led_part_drivers.0.11.2:HAL_PWM true)
message(DEBUG "CMSIS condition STMicroelectronics.led_part_drivers.0.11.2:HAL_PWM enabled")


# condition: STMicroelectronics.led_part_drivers.0.11.2:LED GPIO CFG Condition
# description: STMicroelectronics configuration for LED part driver
set(STMicroelectronics.led_part_drivers.0.11.2:LED_GPIO_CFG_Condition true)
message(DEBUG "CMSIS condition STMicroelectronics.led_part_drivers.0.11.2:LED_GPIO_CFG_Condition enabled")


# condition: STMicroelectronics.led_part_drivers.0.11.2:Part MFX
# description: STMicroelectronics LED IOE Driver
set(STMicroelectronics.led_part_drivers.0.11.2:Part_MFX true)
message(DEBUG "CMSIS condition STMicroelectronics.led_part_drivers.0.11.2:Part_MFX enabled")

# Files and components in this package
if(CMSIS_USE_Board_Part_LED_GPIO_0_10_1)  # Driver for LED driven by GPIO based on STM32 HAL
  message(DEBUG "Using component Board_Part_LED_GPIO_0_10_1")
  if(STMicroelectronics.led_part_drivers.0.11.2:HAL_GPIO)
    target_compile_definitions(STMicroelectronics_led_part_drivers_0_11_2 INTERFACE -DCMSIS_USE_Board_Part_LED_GPIO_0_10_1=1)
    target_include_directories(STMicroelectronics_led_part_drivers_0_11_2 INTERFACE gpio)
  endif()
endif()

if(CMSIS_USE_Board_Part_LED_PWM_0_11_1)  # Driver for LED driven by PWM based on STM32 HAL
  message(DEBUG "Using component Board_Part_LED_PWM_0_11_1")
  if(STMicroelectronics.led_part_drivers.0.11.2:HAL_PWM)
    target_compile_definitions(STMicroelectronics_led_part_drivers_0_11_2 INTERFACE -DCMSIS_USE_Board_Part_LED_PWM_0_11_1=1)
    target_include_directories(STMicroelectronics_led_part_drivers_0_11_2 INTERFACE pwm)
    target_sources(STMicroelectronics_led_part_drivers_0_11_2 INTERFACE pwm/led_pwm.c)
  endif()
endif()

if(CMSIS_USE_Board_Part_LED_MFXSTM32L152_0_11_1)  # Driver for LED driven by IOE based on STM32 HAL
  message(DEBUG "Using component Board_Part_LED_MFXSTM32L152_0_11_1")
  if(STMicroelectronics.led_part_drivers.0.11.2:Part_MFX)
    target_compile_definitions(STMicroelectronics_led_part_drivers_0_11_2 INTERFACE -DCMSIS_USE_Board_Part_LED_MFXSTM32L152_0_11_1=1)
    target_include_directories(STMicroelectronics_led_part_drivers_0_11_2 INTERFACE mfxstm32l152)
    target_sources(STMicroelectronics_led_part_drivers_0_11_2 INTERFACE mfxstm32l152/led_mfx.c)
  endif()
endif()

