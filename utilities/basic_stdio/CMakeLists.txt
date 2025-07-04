# origin-pack: STMicroelectronics::basic_stdio@0.6.1
# created-by: conversion-manager@0.0.53
project(STMicroelectronics_basic_stdio_0_6_1)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_basic_stdio_0_6_1 INTERFACE)

# List of all CMSIS properties that influence conditions for this package


# Device specific defined symbols


# Include RTE_Components.h globally if needed


# Include Pre_Include_Global.h globally if needed


# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_basic_stdio_0_6_1)
  set(CMSIS_USE_Utility_Basic_stdio_Core_0_6_0 true)
  set(CMSIS_USE_Utility_Basic_stdio_itf_io_UART_0_6_0 true)
  set(CMSIS_USE_Utility_Basic_stdio_itf_io_ITM_0_6_0 true)
  set(CMSIS_USE_Utility_Basic_stdio_itf_io_Template_0_6_0 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.basic_stdio.0.6.1:Cortex-M ITM
# description: ARM Cortex-M ITM as low level component
set(STMicroelectronics.basic_stdio.0.6.1:Cortex-M_ITM true)
message(DEBUG "CMSIS condition STMicroelectronics.basic_stdio.0.6.1:Cortex-M_ITM enabled")


# condition: STMicroelectronics.basic_stdio.0.6.1:STM32 HAL UART
# description: STMicroelectronics UART HAL Driver as low level component
set(STMicroelectronics.basic_stdio.0.6.1:STM32_HAL_UART true)
message(DEBUG "CMSIS condition STMicroelectronics.basic_stdio.0.6.1:STM32_HAL_UART enabled")


# condition: STMicroelectronics.basic_stdio.0.6.1:interface
# description: selection of io interface is required to use the component
set(STMicroelectronics.basic_stdio.0.6.1:interface true)
message(DEBUG "CMSIS condition STMicroelectronics.basic_stdio.0.6.1:interface enabled")

# Files and components in this package
if(CMSIS_USE_Utility_Basic_stdio_Core_0_6_0)  # stm32 basic STDIO core part
  message(DEBUG "Using component Utility_Basic_stdio_Core_0_6_0")
  if(STMicroelectronics.basic_stdio.0.6.1:interface)
    target_compile_definitions(STMicroelectronics_basic_stdio_0_6_1 INTERFACE -DCMSIS_USE_Utility_Basic_stdio_Core_0_6_0=1)
    target_sources(STMicroelectronics_basic_stdio_0_6_1 INTERFACE basic_stdio_core.c)
    target_include_directories(STMicroelectronics_basic_stdio_0_6_1 INTERFACE )
    target_include_directories(STMicroelectronics_basic_stdio_0_6_1 INTERFACE interface_io)
  endif()
endif()

if(CMSIS_USE_Utility_Basic_stdio_itf_io_UART_0_6_0)  # UART-based basic stdio redirection (no configuration)
  message(DEBUG "Using component Utility_Basic_stdio_itf_io_UART_0_6_0")
  if(STMicroelectronics.basic_stdio.0.6.1:STM32_HAL_UART)
    target_compile_definitions(STMicroelectronics_basic_stdio_0_6_1 INTERFACE -DCMSIS_USE_Utility_Basic_stdio_itf_io_UART_0_6_0=1)
    target_sources(STMicroelectronics_basic_stdio_0_6_1 INTERFACE interface_io/basic_stdio_itfio_uart.c)
  endif()
endif()

if(CMSIS_USE_Utility_Basic_stdio_itf_io_ITM_0_6_0)  # ITM-based basic stdio redirection (no configuration)
  message(DEBUG "Using component Utility_Basic_stdio_itf_io_ITM_0_6_0")
  if(STMicroelectronics.basic_stdio.0.6.1:Cortex-M_ITM)
    target_compile_definitions(STMicroelectronics_basic_stdio_0_6_1 INTERFACE -DCMSIS_USE_Utility_Basic_stdio_itf_io_ITM_0_6_0=1)
    target_sources(STMicroelectronics_basic_stdio_0_6_1 INTERFACE interface_io/basic_stdio_itfio_itm.c)
  endif()
endif()

if(CMSIS_USE_Utility_Basic_stdio_itf_io_Template_0_6_0)  # No stdio redirection at all: up to you to implement the services based on the templates
  message(DEBUG "Using component Utility_Basic_stdio_itf_io_Template_0_6_0")
  target_compile_definitions(STMicroelectronics_basic_stdio_0_6_1 INTERFACE -DCMSIS_USE_Utility_Basic_stdio_itf_io_Template_0_6_0=1)
  target_sources(STMicroelectronics_basic_stdio_0_6_1 INTERFACE interface_io/basic_stdio_itfio_template.c)
endif()

