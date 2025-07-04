# origin-pack: STMicroelectronics::syscalls@0.2.1
# created-by: conversion-manager@0.0.53
project(STMicroelectronics_syscalls_0_2_1)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_syscalls_0_2_1 INTERFACE)

# List of all CMSIS properties that influence conditions for this package
if(NOT DEFINED CMSIS_Tcompiler)
  set(CMSIS_Tcompiler "CMSIS_Tcompiler not set")
  message(DEBUG "CMSIS_Tcompiler is not set to any value")
endif()


# Device specific defined symbols


# Include RTE_Components.h globally if needed


# Include Pre_Include_Global.h globally if needed


# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_syscalls_0_2_1)
  set(CMSIS_USE_Utility_syscalls_Template_syscalls_0_2_0 true)
  set(CMSIS_USE_Utility_sysmem_Standalone_sysmem_0_2_0 true)
  set(CMSIS_USE_Utility_sysmem_Template_sysmem_0_2_0 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.syscalls.0.2.1:GCC
# description: newlib, usually linked by GCC compilers
if(CMSIS_Tcompiler STREQUAL "GCC")
  set(STMicroelectronics.syscalls.0.2.1:GCC true)
  message(DEBUG "CMSIS condition STMicroelectronics.syscalls.0.2.1:GCC enabled")
endif()


# condition: STMicroelectronics.syscalls.0.2.1:GCC + linker scripts
# description: STMicroelectronics' default linker scripts + newlib
if(CMSIS_Tcompiler STREQUAL "GCC")
  set(STMicroelectronics.syscalls.0.2.1:GCC_+_linker_scripts true)
  message(DEBUG "CMSIS condition STMicroelectronics.syscalls.0.2.1:GCC_+_linker_scripts enabled")
endif()

# Files and components in this package
if(CMSIS_USE_Utility_syscalls_Template_syscalls_0_2_0)  # newlib syscalls stubs: minimal dummy implementation.
  message(DEBUG "Using component Utility_syscalls_Template_syscalls_0_2_0")
  target_compile_definitions(STMicroelectronics_syscalls_0_2_1 INTERFACE -DCMSIS_USE_Utility_syscalls_Template_syscalls_0_2_0=1)
  if(STMicroelectronics.syscalls.0.2.1:GCC)
    target_sources(STMicroelectronics_syscalls_0_2_1 INTERFACE syscalls.c)
  endif()
endif()

if(CMSIS_USE_Utility_sysmem_Standalone_sysmem_0_2_0)  # Simple memory pool management for newlib malloc.
  message(DEBUG "Using component Utility_sysmem_Standalone_sysmem_0_2_0")
  target_compile_definitions(STMicroelectronics_syscalls_0_2_1 INTERFACE -DCMSIS_USE_Utility_sysmem_Standalone_sysmem_0_2_0=1)
  if(STMicroelectronics.syscalls.0.2.1:GCC_+_linker_scripts)
    target_sources(STMicroelectronics_syscalls_0_2_1 INTERFACE sysmem.c)
  endif()
endif()

if(CMSIS_USE_Utility_sysmem_Template_sysmem_0_2_0)  # Simple memory pool management for newlib malloc.
  message(DEBUG "Using component Utility_sysmem_Template_sysmem_0_2_0")
  target_compile_definitions(STMicroelectronics_syscalls_0_2_1 INTERFACE -DCMSIS_USE_Utility_sysmem_Template_sysmem_0_2_0=1)
  if(STMicroelectronics.syscalls.0.2.1:GCC_+_linker_scripts)
    target_sources(STMicroelectronics_syscalls_0_2_1 INTERFACE sysmem.c)
  endif()
endif()

