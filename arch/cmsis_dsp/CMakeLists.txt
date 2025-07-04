# origin-pack: ARM::CMSIS-DSP@1.16.1
# created-by: conversion-manager@0.0.53
project(ARM_CMSIS_DSP_1_16_1)
cmake_minimum_required(VERSION 3.20)
add_library(ARM_CMSIS_DSP_1_16_1 INTERFACE)

# List of all CMSIS properties that influence conditions for this package
if(NOT DEFINED CMSIS_Dcore)
  set(CMSIS_Dcore "CMSIS_Dcore not set")
  message(DEBUG "CMSIS_Dcore is not set to any value")
endif()


# Device specific defined symbols


# Include RTE_Components.h globally if needed


# Include Pre_Include_Global.h globally if needed


# Enable all components in this package
if(CMSIS_ENTIRE_ARM_CMSIS_DSP_1_16_1)
  set(CMSIS_USE_CMSIS_DSP_Source_1_16_1 true)
endif()

# All conditions used by this package

# condition: ARM.CMSIS-DSP.1.16.1:ARMv7-A Device
# description: Armv7-A architecture based device
if((CMSIS_Dcore STREQUAL "Cortex-A5" OR CMSIS_Dcore STREQUAL "Cortex-A7" OR CMSIS_Dcore STREQUAL "Cortex-A9"))
  set(ARM.CMSIS-DSP.1.16.1:ARMv7-A_Device true)
  message(DEBUG "CMSIS condition ARM.CMSIS-DSP.1.16.1:ARMv7-A_Device enabled")
endif()


# condition: ARM.CMSIS-DSP.1.16.1:CMSISCORE
# description: Components required for CMSIS Core
set(ARM.CMSIS-DSP.1.16.1:CMSISCORE true)
message(DEBUG "CMSIS condition ARM.CMSIS-DSP.1.16.1:CMSISCORE enabled")

# Files and components in this package
if(CMSIS_USE_CMSIS_DSP_Source_1_16_1)  # CMSIS-DSP Library for Cortex-M and Cortex-A
  message(DEBUG "Using component CMSIS_DSP_Source_1_16_1")
  if(ARM.CMSIS-DSP.1.16.1:CMSISCORE)
    target_compile_definitions(ARM_CMSIS_DSP_1_16_1 INTERFACE -DCMSIS_USE_CMSIS_DSP_Source_1_16_1=1)
    target_include_directories(ARM_CMSIS_DSP_1_16_1 INTERFACE Include)
    target_include_directories(ARM_CMSIS_DSP_1_16_1 INTERFACE Include)
    target_include_directories(ARM_CMSIS_DSP_1_16_1 INTERFACE Include)
    target_include_directories(ARM_CMSIS_DSP_1_16_1 INTERFACE Include)
    target_include_directories(ARM_CMSIS_DSP_1_16_1 INTERFACE Include)
    target_include_directories(ARM_CMSIS_DSP_1_16_1 INTERFACE Include)
    target_include_directories(ARM_CMSIS_DSP_1_16_1 INTERFACE PrivateInclude/)
    target_include_directories(ARM_CMSIS_DSP_1_16_1 INTERFACE Include/)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/BasicMathFunctions/BasicMathFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/QuaternionMathFunctions/QuaternionMathFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/BayesFunctions/BayesFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/CommonTables/CommonTables.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/ComplexMathFunctions/ComplexMathFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/ControllerFunctions/ControllerFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/DistanceFunctions/DistanceFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/FastMathFunctions/FastMathFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/FilteringFunctions/FilteringFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/MatrixFunctions/MatrixFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/StatisticsFunctions/StatisticsFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/SupportFunctions/SupportFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/SVMFunctions/SVMFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/TransformFunctions/TransformFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/InterpolationFunctions/InterpolationFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/WindowFunctions/WindowFunctions.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/BasicMathFunctions/BasicMathFunctionsF16.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/ComplexMathFunctions/ComplexMathFunctionsF16.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/FilteringFunctions/FilteringFunctionsF16.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/CommonTables/CommonTablesF16.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/TransformFunctions/TransformFunctionsF16.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/MatrixFunctions/MatrixFunctionsF16.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/InterpolationFunctions/InterpolationFunctionsF16.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/StatisticsFunctions/StatisticsFunctionsF16.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/SupportFunctions/SupportFunctionsF16.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/FastMathFunctions/FastMathFunctionsF16.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/DistanceFunctions/DistanceFunctionsF16.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/BayesFunctions/BayesFunctionsF16.c)
    target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE Source/SVMFunctions/SVMFunctionsF16.c)
    if(ARM.CMSIS-DSP.1.16.1:ARMv7-A_Device)
      target_include_directories(ARM_CMSIS_DSP_1_16_1 INTERFACE ComputeLibrary/Include)
    endif()
    if(ARM.CMSIS-DSP.1.16.1:ARMv7-A_Device)
      target_sources(ARM_CMSIS_DSP_1_16_1 INTERFACE ComputeLibrary/Source/arm_cl_tables.c)
    endif()
  endif()
endif()

