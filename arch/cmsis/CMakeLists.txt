# origin-pack: ARM::CMSIS@6.1.0
# created-by: conversion-manager@0.0.53
project(ARM_CMSIS_6_1_0)
cmake_minimum_required(VERSION 3.20)
add_library(ARM_CMSIS_6_1_0 INTERFACE)

# List of all CMSIS properties that influence conditions for this package
if(NOT DEFINED CMSIS_Dcore)
  set(CMSIS_Dcore "CMSIS_Dcore not set")
  message(DEBUG "CMSIS_Dcore is not set to any value")
endif()

if(NOT DEFINED CMSIS_Dsecure)
  set(CMSIS_Dsecure "CMSIS_Dsecure not set")
  message(DEBUG "CMSIS_Dsecure is not set to any value")
endif()

if(NOT DEFINED CMSIS_Dtz)
  set(CMSIS_Dtz "CMSIS_Dtz not set")
  message(DEBUG "CMSIS_Dtz is not set to any value")
endif()


# Device specific defined symbols


# Include RTE_Components.h globally if needed


# Include Pre_Include_Global.h globally if needed


# Enable all components in this package
if(CMSIS_ENTIRE_ARM_CMSIS_6_1_0)
  set(CMSIS_USE_CMSIS_CORE_6_1_0 true)
  set(CMSIS_USE_CMSIS_CORE_6_1_0 true)
  set(CMSIS_USE_Device_IRQ_Controller_GIC_1_2_0 true)
  set(CMSIS_USE_CMSIS_OS_Tick_SysTick_1_0_5 true)
  set(CMSIS_USE_CMSIS_OS_Tick_Private_Timer_1_0_2 true)
  set(CMSIS_USE_CMSIS_OS_Tick_Generic_Physical_Timer_1_0_1 true)
  set(CMSIS_USE_CMSIS_Driver_USART_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_SPI_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_SAI_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_I2C_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_CAN_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_Flash_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_MCI_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_NAND_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_Ethernet_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_Ethernet_MAC_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_Ethernet_PHY_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_USB_Device_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_USB_Host_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_GPIO_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_WiFi_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_VIO_Custom_1_0_0 true)
  set(CMSIS_USE_CMSIS_Driver_VIO_Virtual_1_0_0 true)
endif()

# All conditions used by this package

# condition: ARM.CMSIS.6.1.0:ARMv6-M Device
# description: Armv6-M architecture based device
if((CMSIS_Dcore STREQUAL "Cortex-M0" OR CMSIS_Dcore STREQUAL "Cortex-M1" OR CMSIS_Dcore STREQUAL "Cortex-M0+" OR CMSIS_Dcore STREQUAL "SC000"))
  set(ARM.CMSIS.6.1.0:ARMv6-M_Device true)
  message(DEBUG "CMSIS condition ARM.CMSIS.6.1.0:ARMv6-M_Device enabled")
endif()


# condition: ARM.CMSIS.6.1.0:ARMv6_7_8-M Device
# description: Armv6_7_8-M architecture based device
if(((CMSIS_Dcore STREQUAL "Cortex-M0" OR CMSIS_Dcore STREQUAL "Cortex-M1" OR CMSIS_Dcore STREQUAL "Cortex-M0+" OR CMSIS_Dcore STREQUAL "SC000") OR (CMSIS_Dcore STREQUAL "Cortex-M3" OR CMSIS_Dcore STREQUAL "Cortex-M4" OR CMSIS_Dcore STREQUAL "Cortex-M7" OR CMSIS_Dcore STREQUAL "SC300") OR ((CMSIS_Dcore STREQUAL "ARMV8MBL" OR CMSIS_Dcore STREQUAL "Cortex-M23") OR (CMSIS_Dcore STREQUAL "ARMV8MML" OR CMSIS_Dcore STREQUAL "Cortex-M33" OR CMSIS_Dcore STREQUAL "Cortex-M35P" OR CMSIS_Dcore STREQUAL "Star-MC1") OR (CMSIS_Dcore STREQUAL "ARMV81MML" OR CMSIS_Dcore STREQUAL "Cortex-M52" OR CMSIS_Dcore STREQUAL "Cortex-M55" OR CMSIS_Dcore STREQUAL "Cortex-M85"))))
  set(ARM.CMSIS.6.1.0:ARMv6_7_8-M_Device true)
  message(DEBUG "CMSIS condition ARM.CMSIS.6.1.0:ARMv6_7_8-M_Device enabled")
endif()


# condition: ARM.CMSIS.6.1.0:ARMv7-A Device
# description: Armv7-A architecture based device
if((CMSIS_Dcore STREQUAL "Cortex-A5" OR CMSIS_Dcore STREQUAL "Cortex-A7" OR CMSIS_Dcore STREQUAL "Cortex-A9"))
  set(ARM.CMSIS.6.1.0:ARMv7-A_Device true)
  message(DEBUG "CMSIS condition ARM.CMSIS.6.1.0:ARMv7-A_Device enabled")
endif()


# condition: ARM.CMSIS.6.1.0:ARMv7-M Device
# description: Armv7-M architecture based device
if((CMSIS_Dcore STREQUAL "Cortex-M3" OR CMSIS_Dcore STREQUAL "Cortex-M4" OR CMSIS_Dcore STREQUAL "Cortex-M7" OR CMSIS_Dcore STREQUAL "SC300"))
  set(ARM.CMSIS.6.1.0:ARMv7-M_Device true)
  message(DEBUG "CMSIS condition ARM.CMSIS.6.1.0:ARMv7-M_Device enabled")
endif()


# condition: ARM.CMSIS.6.1.0:ARMv8-M Device
# description: Armv8-M architecture based device
if(((CMSIS_Dcore STREQUAL "ARMV8MBL" OR CMSIS_Dcore STREQUAL "Cortex-M23") OR (CMSIS_Dcore STREQUAL "ARMV8MML" OR CMSIS_Dcore STREQUAL "Cortex-M33" OR CMSIS_Dcore STREQUAL "Cortex-M35P" OR CMSIS_Dcore STREQUAL "Star-MC1") OR (CMSIS_Dcore STREQUAL "ARMV81MML" OR CMSIS_Dcore STREQUAL "Cortex-M52" OR CMSIS_Dcore STREQUAL "Cortex-M55" OR CMSIS_Dcore STREQUAL "Cortex-M85")))
  set(ARM.CMSIS.6.1.0:ARMv8-M_Device true)
  message(DEBUG "CMSIS condition ARM.CMSIS.6.1.0:ARMv8-M_Device enabled")
endif()


# condition: ARM.CMSIS.6.1.0:ARMv8-MBL Device
# description: Armv8-M base line architecture based device
if((CMSIS_Dcore STREQUAL "ARMV8MBL" OR CMSIS_Dcore STREQUAL "Cortex-M23"))
  set(ARM.CMSIS.6.1.0:ARMv8-MBL_Device true)
  message(DEBUG "CMSIS condition ARM.CMSIS.6.1.0:ARMv8-MBL_Device enabled")
endif()


# condition: ARM.CMSIS.6.1.0:ARMv8-MML Device
# description: Armv8-M main line architecture based device
if((CMSIS_Dcore STREQUAL "ARMV8MML" OR CMSIS_Dcore STREQUAL "Cortex-M33" OR CMSIS_Dcore STREQUAL "Cortex-M35P" OR CMSIS_Dcore STREQUAL "Star-MC1"))
  set(ARM.CMSIS.6.1.0:ARMv8-MML_Device true)
  message(DEBUG "CMSIS condition ARM.CMSIS.6.1.0:ARMv8-MML_Device enabled")
endif()


# condition: ARM.CMSIS.6.1.0:ARMv81-MML Device
# description: Armv8.1-M main line architecture based device
if((CMSIS_Dcore STREQUAL "ARMV81MML" OR CMSIS_Dcore STREQUAL "Cortex-M52" OR CMSIS_Dcore STREQUAL "Cortex-M55" OR CMSIS_Dcore STREQUAL "Cortex-M85"))
  set(ARM.CMSIS.6.1.0:ARMv81-MML_Device true)
  message(DEBUG "CMSIS condition ARM.CMSIS.6.1.0:ARMv81-MML_Device enabled")
endif()


# condition: ARM.CMSIS.6.1.0:OS Tick GTIM
# description: Components required for OS Tick Generic Physical Timer
if(CMSIS_Dcore STREQUAL "Cortex-A7")
  set(ARM.CMSIS.6.1.0:OS_Tick_GTIM true)
  message(DEBUG "CMSIS condition ARM.CMSIS.6.1.0:OS_Tick_GTIM enabled")
endif()


# condition: ARM.CMSIS.6.1.0:OS Tick PTIM
# description: Components required for OS Tick Private Timer
if((CMSIS_Dcore STREQUAL "Cortex-A5" OR CMSIS_Dcore STREQUAL "Cortex-A9"))
  set(ARM.CMSIS.6.1.0:OS_Tick_PTIM true)
  message(DEBUG "CMSIS condition ARM.CMSIS.6.1.0:OS_Tick_PTIM enabled")
endif()


# condition: ARM.CMSIS.6.1.0:OS Tick SysTick
# description: Components required for OS Tick SysTick Timer
if(((CMSIS_Dcore STREQUAL "Cortex-M0" OR CMSIS_Dcore STREQUAL "Cortex-M1" OR CMSIS_Dcore STREQUAL "Cortex-M0+" OR CMSIS_Dcore STREQUAL "SC000") OR (CMSIS_Dcore STREQUAL "Cortex-M3" OR CMSIS_Dcore STREQUAL "Cortex-M4" OR CMSIS_Dcore STREQUAL "Cortex-M7" OR CMSIS_Dcore STREQUAL "SC300") OR ((CMSIS_Dcore STREQUAL "ARMV8MBL" OR CMSIS_Dcore STREQUAL "Cortex-M23") OR (CMSIS_Dcore STREQUAL "ARMV8MML" OR CMSIS_Dcore STREQUAL "Cortex-M33" OR CMSIS_Dcore STREQUAL "Cortex-M35P" OR CMSIS_Dcore STREQUAL "Star-MC1") OR (CMSIS_Dcore STREQUAL "ARMV81MML" OR CMSIS_Dcore STREQUAL "Cortex-M52" OR CMSIS_Dcore STREQUAL "Cortex-M55" OR CMSIS_Dcore STREQUAL "Cortex-M85"))))
  set(ARM.CMSIS.6.1.0:OS_Tick_SysTick true)
  message(DEBUG "CMSIS condition ARM.CMSIS.6.1.0:OS_Tick_SysTick enabled")
endif()


# condition: ARM.CMSIS.6.1.0:TZ Secure
# description: TrustZone (Secure)
if((CMSIS_Dtz STREQUAL "TZ" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(ARM.CMSIS.6.1.0:TZ_Secure true)
  message(DEBUG "CMSIS condition ARM.CMSIS.6.1.0:TZ_Secure enabled")
endif()


# condition: ARM.CMSIS.6.1.0:TrustZone
# description: TrustZone
if(CMSIS_Dtz STREQUAL "TZ")
  set(ARM.CMSIS.6.1.0:TrustZone true)
  message(DEBUG "CMSIS condition ARM.CMSIS.6.1.0:TrustZone enabled")
endif()

# Files and components in this package
if(CMSIS_USE_CMSIS_CORE_6_1_0)  # CMSIS-CORE for Cortex-M, SC000, SC300, Star-MC1, ARMv8-M, ARMv8.1-M
  message(DEBUG "Using component CMSIS_CORE_6_1_0")
  if(ARM.CMSIS.6.1.0:ARMv6_7_8-M_Device)
    target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_CORE_6_1_0=1)
    target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Core/Include/)
    if(ARM.CMSIS.6.1.0:TrustZone)
      target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Core/Include)
    endif()
    if(ARM.CMSIS.6.1.0:TZ_Secure)
      target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Core/Template/ARMv8-M/main_s.c)
    endif()
    if(ARM.CMSIS.6.1.0:TZ_Secure)
      target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Core/Template/ARMv8-M/tz_context.c)
    endif()
  endif()
endif()

if(CMSIS_USE_CMSIS_CORE_6_1_0)  # CMSIS-CORE for Cortex-A
  message(DEBUG "Using component CMSIS_CORE_6_1_0")
  if(ARM.CMSIS.6.1.0:ARMv7-A_Device)
    target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_CORE_6_1_0=1)
    target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Core/Include/)
  endif()
endif()

if(CMSIS_USE_Device_IRQ_Controller_GIC_1_2_0)  # IRQ Controller implementation using GIC
  message(DEBUG "Using component Device_IRQ_Controller_GIC_1_2_0")
  if(ARM.CMSIS.6.1.0:ARMv7-A_Device)
    target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_Device_IRQ_Controller_GIC_1_2_0=1)
    target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Core/Source/irq_ctrl_gic.c)
  endif()
endif()

if(CMSIS_USE_CMSIS_OS_Tick_SysTick_1_0_5)  # OS Tick implementation using Cortex-M SysTick Timer
  message(DEBUG "Using component CMSIS_OS_Tick_SysTick_1_0_5")
  if(ARM.CMSIS.6.1.0:OS_Tick_SysTick)
    target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_OS_Tick_SysTick_1_0_5=1)
    target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/RTOS2/Source/os_systick.c)
  endif()
endif()

if(CMSIS_USE_CMSIS_OS_Tick_Private_Timer_1_0_2)  # OS Tick implementation using Private Timer
  message(DEBUG "Using component CMSIS_OS_Tick_Private_Timer_1_0_2")
  if(ARM.CMSIS.6.1.0:OS_Tick_PTIM)
    target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_OS_Tick_Private_Timer_1_0_2=1)
    target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/RTOS2/Source/os_tick_ptim.c)
  endif()
endif()

if(CMSIS_USE_CMSIS_OS_Tick_Generic_Physical_Timer_1_0_1)  # OS Tick implementation using Generic Physical Timer
  message(DEBUG "Using component CMSIS_OS_Tick_Generic_Physical_Timer_1_0_1")
  if(ARM.CMSIS.6.1.0:OS_Tick_GTIM)
    target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_OS_Tick_Generic_Physical_Timer_1_0_1=1)
    target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/RTOS2/Source/os_tick_gtim.c)
  endif()
endif()

if(CMSIS_USE_CMSIS_Driver_USART_Custom_1_0_0)  # Access to #include Driver_USART.h file and code template for custom implementation
  message(DEBUG "Using component CMSIS_Driver_USART_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_USART_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_USART.c)
endif()

if(CMSIS_USE_CMSIS_Driver_SPI_Custom_1_0_0)  # Access to #include Driver_SPI.h file and code template for custom implementation
  message(DEBUG "Using component CMSIS_Driver_SPI_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_SPI_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_SPI.c)
endif()

if(CMSIS_USE_CMSIS_Driver_SAI_Custom_1_0_0)  # Access to #include Driver_SAI.h file and code template for custom implementation
  message(DEBUG "Using component CMSIS_Driver_SAI_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_SAI_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_SAI.c)
endif()

if(CMSIS_USE_CMSIS_Driver_I2C_Custom_1_0_0)  # Access to #include Driver_I2C.h file and code template for custom implementation
  message(DEBUG "Using component CMSIS_Driver_I2C_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_I2C_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_I2C.c)
endif()

if(CMSIS_USE_CMSIS_Driver_CAN_Custom_1_0_0)  # Access to #include Driver_CAN.h file and code template for custom implementation
  message(DEBUG "Using component CMSIS_Driver_CAN_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_CAN_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_CAN.c)
endif()

if(CMSIS_USE_CMSIS_Driver_Flash_Custom_1_0_0)  # Access to #include Driver_Flash.h file and code template for custom implementation
  message(DEBUG "Using component CMSIS_Driver_Flash_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_Flash_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_Flash.c)
endif()

if(CMSIS_USE_CMSIS_Driver_MCI_Custom_1_0_0)  # Access to #include Driver_MCI.h file and code template for custom implementation
  message(DEBUG "Using component CMSIS_Driver_MCI_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_MCI_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_MCI.c)
endif()

if(CMSIS_USE_CMSIS_Driver_NAND_Custom_1_0_0)  # Access to #include Driver_NAND.h file and code template for custom implementation
  message(DEBUG "Using component CMSIS_Driver_NAND_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_NAND_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_NAND.c)
endif()

if(CMSIS_USE_CMSIS_Driver_Ethernet_Custom_1_0_0)  # Access to #include Driver_ETH_PHY/MAC.h files and code templates for custom implementation
  message(DEBUG "Using component CMSIS_Driver_Ethernet_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_Ethernet_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.c)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.c)
endif()

if(CMSIS_USE_CMSIS_Driver_Ethernet_MAC_Custom_1_0_0)  # Access to #include Driver_ETH_MAC.h file and code template for custom implementation
  message(DEBUG "Using component CMSIS_Driver_Ethernet_MAC_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_Ethernet_MAC_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.c)
endif()

if(CMSIS_USE_CMSIS_Driver_Ethernet_PHY_Custom_1_0_0)  # Access to #include Driver_ETH_PHY.h file and code template for custom implementation
  message(DEBUG "Using component CMSIS_Driver_Ethernet_PHY_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_Ethernet_PHY_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.c)
endif()

if(CMSIS_USE_CMSIS_Driver_USB_Device_Custom_1_0_0)  # Access to #include Driver_USBD.h file and code template for custom implementation
  message(DEBUG "Using component CMSIS_Driver_USB_Device_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_USB_Device_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_USBD.c)
endif()

if(CMSIS_USE_CMSIS_Driver_USB_Host_Custom_1_0_0)  # Access to #include Driver_USBH.h file and code template for custom implementation
  message(DEBUG "Using component CMSIS_Driver_USB_Host_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_USB_Host_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_USBH.c)
endif()

if(CMSIS_USE_CMSIS_Driver_GPIO_Custom_1_0_0)  # Access to #include Driver_GPIO.h file and code template for custom implementation
  message(DEBUG "Using component CMSIS_Driver_GPIO_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_GPIO_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_GPIO.c)
endif()

if(CMSIS_USE_CMSIS_Driver_WiFi_Custom_1_0_0)  # Access to #include Driver_WiFi.h file
  message(DEBUG "Using component CMSIS_Driver_WiFi_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_WiFi_Custom_1_0_0=1)
  target_include_directories(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/Include)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/DriverTemplates/Driver_WiFi.c)
endif()

if(CMSIS_USE_CMSIS_Driver_VIO_Custom_1_0_0)  # Virtual I/O custom implementation template
  message(DEBUG "Using component CMSIS_Driver_VIO_Custom_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_VIO_Custom_1_0_0=1)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/VIO/Source/vio.c)
endif()

if(CMSIS_USE_CMSIS_Driver_VIO_Virtual_1_0_0)  # Virtual I/O implementation using memory only
  message(DEBUG "Using component CMSIS_Driver_VIO_Virtual_1_0_0")
  target_compile_definitions(ARM_CMSIS_6_1_0 INTERFACE -DCMSIS_USE_CMSIS_Driver_VIO_Virtual_1_0_0=1)
  target_sources(ARM_CMSIS_6_1_0 INTERFACE CMSIS/Driver/VIO/Source/vio_memory.c)
endif()

