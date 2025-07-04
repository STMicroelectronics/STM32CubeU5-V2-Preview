# origin-pack: STMicroelectronics::tcpp01_part_drivers@0.4.0
# created-by: conversion-manager@0.0.53
project(STMicroelectronics_tcpp01_part_drivers_0_4_0)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_tcpp01_part_drivers_0_4_0 INTERFACE)

# List of all CMSIS properties that influence conditions for this package


# Device specific defined symbols


# Include RTE_Components.h globally if needed


# Include Pre_Include_Global.h globally if needed


# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_tcpp01_part_drivers_0_4_0)
  set(CMSIS_USE_Board_Part_USBPD_TCPP01_Core_0_3_0 true)
  set(CMSIS_USE_Board_Part_USBPD_TCPP01_IO_ADC_EXTI_0_3_0 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.tcpp01_part_drivers.0.4.0:TCPP01 Core Condition
# description: STMicroelectronics TCPP01 Core Driver
set(STMicroelectronics.tcpp01_part_drivers.0.4.0:TCPP01_Core_Condition true)
message(DEBUG "CMSIS condition STMicroelectronics.tcpp01_part_drivers.0.4.0:TCPP01_Core_Condition enabled")


# condition: STMicroelectronics.tcpp01_part_drivers.0.4.0:TCPP01 IO ADC EXTI Condition
# description: STMicroelectronics TCPP01 IO ADC Polling and EXTI Drivers
set(STMicroelectronics.tcpp01_part_drivers.0.4.0:TCPP01_IO_ADC_EXTI_Condition true)
message(DEBUG "CMSIS condition STMicroelectronics.tcpp01_part_drivers.0.4.0:TCPP01_IO_ADC_EXTI_Condition enabled")

# Files and components in this package
if(CMSIS_USE_Board_Part_USBPD_TCPP01_Core_0_3_0)  # Driver for TCPP01 part
  message(DEBUG "Using component Board_Part_USBPD_TCPP01_Core_0_3_0")
  if(STMicroelectronics.tcpp01_part_drivers.0.4.0:TCPP01_Core_Condition)
    target_compile_definitions(STMicroelectronics_tcpp01_part_drivers_0_4_0 INTERFACE -DCMSIS_USE_Board_Part_USBPD_TCPP01_Core_0_3_0=1)
    target_include_directories(STMicroelectronics_tcpp01_part_drivers_0_4_0 INTERFACE )
    target_sources(STMicroelectronics_tcpp01_part_drivers_0_4_0 INTERFACE tcpp01.c)
  endif()
endif()

if(CMSIS_USE_Board_Part_USBPD_TCPP01_IO_ADC_EXTI_0_3_0)  # ADC EXTI IO for TCPP01 part
  message(DEBUG "Using component Board_Part_USBPD_TCPP01_IO_ADC_EXTI_0_3_0")
  if(STMicroelectronics.tcpp01_part_drivers.0.4.0:TCPP01_IO_ADC_EXTI_Condition)
    target_compile_definitions(STMicroelectronics_tcpp01_part_drivers_0_4_0 INTERFACE -DCMSIS_USE_Board_Part_USBPD_TCPP01_IO_ADC_EXTI_0_3_0=1)
    target_include_directories(STMicroelectronics_tcpp01_part_drivers_0_4_0 INTERFACE interfaces/adc_exti)
    target_sources(STMicroelectronics_tcpp01_part_drivers_0_4_0 INTERFACE interfaces/adc_exti/tcpp01_io.c)
  endif()
endif()

