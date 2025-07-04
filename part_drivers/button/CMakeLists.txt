# origin-pack: STMicroelectronics::button_part_drivers@0.5.0
# created-by: conversion-manager@0.0.53
project(STMicroelectronics_button_part_drivers_0_5_0)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_button_part_drivers_0_5_0 INTERFACE)

# List of all CMSIS properties that influence conditions for this package


# Device specific defined symbols


# Include RTE_Components.h globally if needed


# Include Pre_Include_Global.h globally if needed


# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_button_part_drivers_0_5_0)
  set(CMSIS_USE_Board_Part_Button_gpio_0_5_0 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.button_part_drivers.0.5.0:Button CFG Condition
# description: STMicroelectronics configuration for Button part driver
set(STMicroelectronics.button_part_drivers.0.5.0:Button_CFG_Condition true)
message(DEBUG "CMSIS condition STMicroelectronics.button_part_drivers.0.5.0:Button_CFG_Condition enabled")


# condition: STMicroelectronics.button_part_drivers.0.5.0:HAL GPIO
# description: STMicroelectronics GPIO HAL Driver
set(STMicroelectronics.button_part_drivers.0.5.0:HAL_GPIO true)
message(DEBUG "CMSIS condition STMicroelectronics.button_part_drivers.0.5.0:HAL_GPIO enabled")

# Files and components in this package
if(CMSIS_USE_Board_Part_Button_gpio_0_5_0)  # Driver for button based on STM32 HAL
  message(DEBUG "Using component Board_Part_Button_gpio_0_5_0")
  if(STMicroelectronics.button_part_drivers.0.5.0:HAL_GPIO)
    target_compile_definitions(STMicroelectronics_button_part_drivers_0_5_0 INTERFACE -DCMSIS_USE_Board_Part_Button_gpio_0_5_0=1)
    target_include_directories(STMicroelectronics_button_part_drivers_0_5_0 INTERFACE gpio)
    target_sources(STMicroelectronics_button_part_drivers_0_5_0 INTERFACE gpio/button.c)
  endif()
endif()

