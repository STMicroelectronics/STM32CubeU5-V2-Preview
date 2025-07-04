# origin-pack: STMicroelectronics::stm32u5xx_dfp@2.0.0-beta.1
# created-by: conversion-manager@0.0.53
project(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE)

# List of all CMSIS properties that influence conditions for this package
if(NOT DEFINED CMSIS_Dname)
  set(CMSIS_Dname "CMSIS_Dname not set")
  message(DEBUG "CMSIS_Dname is not set to any value")
endif()

if(NOT DEFINED CMSIS_Dsecure)
  set(CMSIS_Dsecure "CMSIS_Dsecure not set")
  message(DEBUG "CMSIS_Dsecure is not set to any value")
endif()

if(NOT DEFINED CMSIS_Dvendor)
  set(CMSIS_Dvendor "CMSIS_Dvendor not set")
  message(DEBUG "CMSIS_Dvendor is not set to any value")
endif()

if(NOT DEFINED CMSIS_Tcompiler)
  set(CMSIS_Tcompiler "CMSIS_Tcompiler not set")
  message(DEBUG "CMSIS_Tcompiler is not set to any value")
endif()


# Device specific defined symbols
if(CMSIS_Dname STREQUAL "STM32U535CBT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535CBT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535CBU6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535CBU6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535CCT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535CCT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535CCU6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535CCU6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535CCU6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535CET6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535CET6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535CEU6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535CEU6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535CEU6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535CEU6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535JEY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535NCY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535NEY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535RBI6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535RBI6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535RBT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535RBT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535RCI6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535RCI6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535RCT3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535RCT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535RCT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535REI3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535REI6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535REI6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535REI6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535RET6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535RET6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535RET6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535RET6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535VCI6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535VCI6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535VCT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535VCT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535VEI3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535VEI3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535VEI3TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535VEI6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535VEI6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535VET3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535VET3QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535VET6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535VET6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U535VET6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U535xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545CET6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545CET6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545CEU6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545CEU6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545CEU6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545JEY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545NEY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545REI6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545REI6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545RET3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545RET6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545RET6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545VEI6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545VEI6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545VET6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U545VET6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U545xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575AGI6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575AGI6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575AGI6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575AII6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575AII6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575CGT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575CGT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575CGU3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575CGU3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575CGU6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575CGU6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575CGU6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575CIT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575CIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575CIU6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575CIU6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575OGY3QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575OGY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575OIY3QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575OIY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575QGI3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575QGI3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575QGI3TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575QGI6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575QGI6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575QGI6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575QII3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575QII3TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575QII6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575QII6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575QII6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575RGT3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575RGT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575RGT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575RGT6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575RIT3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575RIT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575RIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575VGT3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575VGT3TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575VGT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575VGT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575VGT6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575VIT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575VIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575VIT6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575VIT6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575ZGT3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575ZGT3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575ZGT3QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575ZGT3TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575ZGT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575ZGT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575ZIT3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575ZIT3QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575ZIT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575ZIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U575ZIT6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U575xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585AII3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585AII6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585AII6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585AII6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585AII6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585CIT3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585CIT3TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585CIT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585CIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585CIU3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585CIU6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585CIU6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585CIU6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585OIY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585QII3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585QII3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585QII3QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585QII3TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585QII6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585QII6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585QII6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585QII6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585RIT3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585RIT3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585RIT3TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585RIT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585RIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585RIT6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585RIT6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585VIT3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585VIT3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585VIT3TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585VIT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585VIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585VIT6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585VIT6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585ZIT3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585ZIT3QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585ZIT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U585ZIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U585xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595AIH6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595AIH6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595AJH3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595AJH6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595AJH6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595QII6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595QII6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595QJI6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595QJI6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595QJI6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595RIT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595RIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595RIT6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595RIT6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595RJT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595RJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595VIT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595VIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595VIT6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595VJT3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595VJT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595VJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595ZIT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595ZIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595ZIY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595ZJT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595ZJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U595ZJY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U595xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5AJH3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5AJH3TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5AJH6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5AJH6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5AJH6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5QII3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5QJI3")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5QJI3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5QJI6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5QJI6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5RJT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5RJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5VJT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5VJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5ZJT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5ZJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5ZJT6TR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5ZJY3QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A5ZJY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U599BJY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U599xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U599NIH6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U599xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U599NIH6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U599xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U599NJH6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U599xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U599VIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U599xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U599VJT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U599xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U599VJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U599xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U599ZIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U599xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U599ZIY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U599xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U599ZJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U599xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U599ZJY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U599xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A9BJY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A9NJH3Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A9NJH3QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A9NJH6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A9VJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A9ZJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5A9ZJY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5A9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5F7VIT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5F7xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5F7VIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5F7xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5F7VJT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5F7xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5F7VJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5F7xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5G7VJT6")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5G7xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5G7VJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5G7xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5F9BJY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5F9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5F9NJH6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5F9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5F9VIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5F9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5F9VJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5F9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5F9ZIJ6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5F9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5F9ZIT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5F9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5F9ZJJ6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5F9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5F9ZJJ6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5F9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5F9ZJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5F9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5G9BJY6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5G9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5G9NJH6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5G9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5G9VJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5G9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5G9ZJJ6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5G9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5G9ZJJ6QTR")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5G9xx)
endif()
if(CMSIS_Dname STREQUAL "STM32U5G9ZJT6Q")
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE STM32U5G9xx)
endif()


# Include RTE_Components.h globally if needed
if(CMSIS_Tcompiler STREQUAL "IAR")
    target_compile_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE --preinclude=${CMAKE_CURRENT_LIST_DIR}/RTE_Components.h)
else()
    target_compile_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE --include=${CMAKE_CURRENT_LIST_DIR}/RTE_Components.h)
endif()

# Include Pre_Include_Global.h globally if needed


# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1)
  set(CMSIS_USE_Device_Startup_2_0_0_beta_1 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5
# description: 
if((CMSIS_Dname MATCHES "STM32U5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535
# description: 
if((CMSIS_Dname MATCHES "STM32U535.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.B.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.B.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.B.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.B.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.B.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.B.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.B.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.B.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.B.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.C.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.C.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.C.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.C.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.C.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.C.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.C.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.C.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U535.C.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U545
# description: 
if((CMSIS_Dname MATCHES "STM32U545.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U545 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U545 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575
# description: 
if((CMSIS_Dname MATCHES "STM32U575.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U575.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585
# description: 
if((CMSIS_Dname MATCHES "STM32U585.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U585.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U585.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U585.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U585.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U585.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U585.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U585.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U585.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U585.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595
# description: 
if((CMSIS_Dname MATCHES "STM32U595.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U595.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599
# description: 
if((CMSIS_Dname MATCHES "STM32U599.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U599.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5
# description: 
if((CMSIS_Dname MATCHES "STM32U5A5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5QI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5QI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5QI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5QI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5QI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5QI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5QI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5QI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5QI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A5.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9
# description: 
if((CMSIS_Dname MATCHES "STM32U5A9.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5A9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7
# description: 
if((CMSIS_Dname MATCHES "STM32U5F7.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VI.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9
# description: 
if((CMSIS_Dname MATCHES "STM32U5F9.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5F9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7
# description: 
if((CMSIS_Dname MATCHES "STM32U5G7.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G7VJ.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9
# description: 
if((CMSIS_Dname MATCHES "STM32U5G9.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9 enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5G9.J.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE ARMCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5.5.E.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_ARMCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_ARMCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE ARMCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5.5.E.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_ARMCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_ARMCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE ARMCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5.5.E.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_ARMCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_ARMCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE GCC Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5.5.E.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_GCC_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_GCC_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE GCC Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5.5.E.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_GCC_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_GCC_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE GCC TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5.5.E.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_GCC_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_GCC_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE IAR Non-secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5.5.E.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Non-secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_IAR_Non-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_IAR_Non-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE IAR Secure
# description: 
if(((CMSIS_Dname MATCHES "STM32U5.5.E.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "Secure"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_IAR_Secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_IAR_Secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE IAR TZ-disabled
# description: 
if(((CMSIS_Dname MATCHES "STM32U5.5.E.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR" AND CMSIS_Dsecure STREQUAL "TZ-disabled"))
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_IAR_TZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_IAR_TZ-disabled enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:isNon-secure
# description: 
if(CMSIS_Dsecure STREQUAL "Non-secure")
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:isNon-secure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:isNon-secure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:isSecure
# description: 
if(CMSIS_Dsecure STREQUAL "Secure")
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:isSecure true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:isSecure enabled")
endif()


# condition: STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:isTZ-disabled
# description: 
if(CMSIS_Dsecure STREQUAL "TZ-disabled")
  set(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:isTZ-disabled true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:isTZ-disabled enabled")
endif()

# Files and components in this package
if(CMSIS_USE_Device_Startup_2_0_0_beta_1)  # System Startup for STMicroelectronics STM32U5 Series
  message(DEBUG "Using component Device_Startup_2_0_0_beta_1")
  if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5)
    target_compile_definitions(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -DCMSIS_USE_Device_Startup_2_0_0_beta_1=1)
    target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include/)
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535)
      target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U545)
      target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575)
      target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585)
      target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595)
      target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599)
      target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5)
      target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9)
      target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7)
      target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9)
      target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7)
      target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9)
      target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    endif()
    target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include)
    target_include_directories(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Include)
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_ARMCC_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_ARMCC_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_ARMCC_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u535xb_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u535xb_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u535xb_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u535xc_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u535xc_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u535xc_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u575xg_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u575xg_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u575xg_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u575xi_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u575xi_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u575xi_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u585xi_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u585xi_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u585xi_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u595xi_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u595xi_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u595xi_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u595xj_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u595xj_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u595xj_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u599xi_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u599xi_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u599xi_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u599xj_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u599xj_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u599xj_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5a5qi_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5a5qi_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5a5qi_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5a5xj_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5a5xj_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5a5xj_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5a9xj_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5a9xj_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5a9xj_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5f7vi_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5f7vi_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5f7vi_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5f7vj_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5f7vj_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5f7vj_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5f9xi_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5f9xi_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5f9xi_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5f9xj_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5f9xj_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5f9xj_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5g7vj_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5g7vj_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5g7vj_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5g9xj_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5g9xj_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5g9xj_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_GCC_TZ-disabled)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5x5xe_flash.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_GCC_Non-secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5x5xe_flash_ns.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_GCC_Secure)
      target_link_options(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32u5x5xe_flash_s.ld)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xB_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535xC_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xG_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575xI_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585xI_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xI_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595xJ_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xI_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599xJ_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5QI_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5xJ_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9xJ_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VI_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7VJ_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xI_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9xJ_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7VJ_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9xJ_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_IAR_TZ-disabled)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_IAR_Non-secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5x5xE_IAR_Secure)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:isTZ-disabled)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/Templates/system_stm32u5xx.c)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:isNon-secure)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/Templates/system_stm32u5xx_ns.c)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:isSecure)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/Templates/system_stm32u5xx_s.c)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U535)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32u535xx.c)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U545)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32u545xx.c)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U575)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32u575xx.c)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U585)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32u585xx.c)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U595)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32u595xx.c)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U599)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32u599xx.c)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A5)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32u5a5xx.c)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5A9)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32u5a9xx.c)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F7)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32u5f7xx.c)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5F9)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32u5f9xx.c)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G7)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32u5g7xx.c)
    endif()
    if(STMicroelectronics.stm32u5xx_dfp.2.0.0-beta.1:STM32U5G9)
      target_sources(STMicroelectronics_stm32u5xx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32u5g9xx.c)
    endif()
  endif()
endif()

