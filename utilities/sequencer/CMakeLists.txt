# origin-pack: STMicroelectronics::sequencer@2.0.0-alpha.2.1
# created-by: conversion-manager@0.0.53
project(STMicroelectronics_sequencer_2_0_0_alpha_2_1)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_sequencer_2_0_0_alpha_2_1 INTERFACE)

# List of all CMSIS properties that influence conditions for this package


# Device specific defined symbols


# Include RTE_Components.h globally if needed


# Include Pre_Include_Global.h globally if needed


# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_sequencer_2_0_0_alpha_2_1)
  set(CMSIS_USE_Utility_SEQUENCER_Core_0_2_0 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.sequencer.2.0.0-alpha.2.1:Seq Config
# description: STMicroelectronics Utility Sequencer Config
set(STMicroelectronics.sequencer.2.0.0-alpha.2.1:Seq_Config true)
message(DEBUG "CMSIS condition STMicroelectronics.sequencer.2.0.0-alpha.2.1:Seq_Config enabled")

# Files and components in this package
if(CMSIS_USE_Utility_SEQUENCER_Core_0_2_0)  # Utility sequencer (SEQ) driver 
  message(DEBUG "Using component Utility_SEQUENCER_Core_0_2_0")
  target_compile_definitions(STMicroelectronics_sequencer_2_0_0_alpha_2_1 INTERFACE -DCMSIS_USE_Utility_SEQUENCER_Core_0_2_0=1)
  target_sources(STMicroelectronics_sequencer_2_0_0_alpha_2_1 INTERFACE sequencer.c)
  target_include_directories(STMicroelectronics_sequencer_2_0_0_alpha_2_1 INTERFACE )
  target_include_directories(STMicroelectronics_sequencer_2_0_0_alpha_2_1 INTERFACE template)
endif()

