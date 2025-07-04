# created-by: conversion-manager@0.0.53
cmake_minimum_required (VERSION 3.20)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
# enable below if you want to use the Open-CMSIS-Pack way to include cmake toolchain target flags
set(CPU ${CMSIS_Dcore})
set(FPU ${CMSIS_Dfpu})
set(DSP ${CMSIS_Ddsp})
if(CMAKE_BUILD_TYPE STREQUAL "release_GCC_NUCLEO-U575ZI-Q")
    include(GCC.12.3.1.cmake)
else()
    message(FATAL_ERROR "Please select a preset, 'cube cmake --list-presets', then configure using 'cube cmake --preset <preset>' and finally build using 'cube cmake --build --preset <preset>'")
endif()

project(hal_spi_fd_2B_crc_com_it_cntrl)
add_executable(hal_spi_fd_2B_crc_com_it_cntrl)

if(CMAKE_BUILD_TYPE STREQUAL "release_GCC_NUCLEO-U575ZI-Q")
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES SUFFIX ".elf")
    target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC ${CPU_FLAGS})
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE ../../../application/example.c ../../../application/example.h ../../../application/main.c ../../../application/main.h ../../generated/hal/mx_icache.c ../../generated/hal/mx_rcc.c ../../generated/hal/mx_spi1.c ../../generated/hal/mx_cortex_nvic.c ../../generated/hal/mx_system.c ../../generated/hal/mx_usart1.c)
    target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -Os -fdata-sections -ffunction-sections -std=gnu11 -Wall -fstack-usage -fcyclomatic-complexity --specs=nano.specs --specs=nosys.specs)
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ../../generated/_release_GCC_NUCLEO-U575ZI-Q ../../../../../../../arch/cmsis/CMSIS/Core/Include ../../generated/hal ../../../../../../../stm32u5xx_dfp/Include ../../../../../../../stm32u5xx_drivers/hal ../../../../../../../stm32u5xx_drivers/ll ../../../../../../../stm32u5xx_drivers/timebases ../../../../../../../utilities/basic_stdio ../../../../../../../utilities/basic_stdio/interface_io)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC USE_TRACE=0 STM32U575xx _RTE_)
    target_link_options(${CMAKE_PROJECT_NAME} PUBLIC -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections -Wl,--start-group -lc -lm -Wl,--end-group -static --specs=nano.specs --specs=nosys.specs)
    target_link_options(${CMAKE_PROJECT_NAME} PUBLIC ${CPU_FLAGS})
endif()


# Start cube-components-section
add_subdirectory(../../../../../../../arch/cmsis ${CMAKE_BINARY_DIR}/ARM.CMSIS.6.1.0)
add_subdirectory(../../../../../../../stm32u5xx_dfp ${CMAKE_BINARY_DIR}/STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1)
add_subdirectory(../../../../../../../stm32u5xx_drivers ${CMAKE_BINARY_DIR}/STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-beta.1.1)
add_subdirectory(../../../../../../../utilities/basic_stdio ${CMAKE_BINARY_DIR}/STMicroelectronics.basic_stdio.0.6.1)
add_subdirectory(../../../../../../../utilities/syscalls ${CMAKE_BINARY_DIR}/STMicroelectronics.syscalls.0.2.1)
target_link_libraries(${CMAKE_PROJECT_NAME} ARM_CMSIS_6_1_0 STMicroelectronics_basic_stdio_0_6_1 STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 STMicroelectronics_stm32u5xx_hal_drivers_2_0_0_beta_1_1 STMicroelectronics_syscalls_0_2_1)
# End cube-components-section
