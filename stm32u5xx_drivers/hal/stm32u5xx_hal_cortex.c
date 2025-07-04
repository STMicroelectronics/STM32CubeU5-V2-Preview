/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_cortex.c
  * @brief   CORTEX HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the CORTEX:
  *           + Initialization and Configuration functions
  *           + Peripheral Control functions
  *
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup CORTEX
  * @{

# CORTEX main features

## The HAL CORTEX driver contains four main blocks:

1. NVIC: Nested Vector Interrupt Controller

  - The NVIC is an embedded interrupt controller that supports low-latency interrupt processing.
     - It contains a configurable interrupt handling ability. Configured items can be:
        - Priority grouping that specifies the range of preemption priority and sub priority.
        - Preemption priority ability between interrupts.
        - Subpriority ability between interrupts.

  - Within the Cortex-M33, the NVIC block is banked :
     - Secure NVIC to handle secure configurable interrupts.
     - Non-Secure NVIC to handle non-secure configurable interrupts.

2. SYSTICK: System Timer

  - The SysTick, is a 24 bits count-down timer. It can be used as a simple counter or as tick timer in a real time
    operating system (RTOS).

  - Within the Cortex-M33, the SYSTICK block is banked :
     - Secure SYSTICK to be used for the secure application.
     - Non-Secure SYSTICK to be used for the non-secure application.

3. MPU: Memory Protection Unit

  - The MPU allows a privileged software to define memory regions, assign memory access permission and memory
    attributes to each of them to improve the system reliability.

  - Within the Cortex-M33, the MPU block is banked :
     - Secure MPU to be used for secure regions definition (Up to 12 regions).
     - Non-Secure MPU to be used for non-secure regions definition (Up to 8 regions).

4. SCB: System Control Block

  - The SCB provides system information and system control that includes configuration, control and reporting of
    system fault exceptions.

# How to use the CORTEX HAL module driver

## The CORTEX HAL driver can be used as follows :

This driver provides the HAL_CORTEX driver functions allowing to configure the NVIC, SYSTICK, MPU and SCB blocks.

1. How to configure NVIC Interrupts using CORTEX HAL driver :

  - Configure the NVIC Priority Grouping using HAL_CORTEX_NVIC_SetPriorityGrouping() function ones at startup.
     - When the HAL_CORTEX_NVIC_PRIORITY_GROUP_0 is selected, IRQ pre-emption is no more configurable. The pending IRQ
       priority is managed only by the sub-priority.
     - When the HAL_CORTEX_NVIC_PRIORITY_GROUP_1 is selected, there is one bit for preemption priority and three bits
       for sub-priority.
     - When the HAL_CORTEX_NVIC_PRIORITY_GROUP_2 is selected, there are two bits for preemption priority and two bits
       for sub-priority.
     - When the HAL_CORTEX_NVIC_PRIORITY_GROUP_3 is selected, there are three bits for preemption priority and one bit
       for sub-priority.
     - When the HAL_CORTEX_NVIC_PRIORITY_GROUP_4 is selected, IRQ sub-priority is no more configurable. The pending IRQ
       priority is managed only by the pre-emption priority.

  - Configure the priority of the selected IRQ channels using HAL_CORTEX_NVIC_SetPriority() function :
     - IRQ priority order (sorted by highest to lowest priority):
        - The lowest is the preemption priority numerical value, the highest is the preemption  priority.
        - The lowest is the subpriority numerical value, the the highest is the subpriority.
     - Get the priority grouping using HAL_CORTEX_NVIC_GetPriorityGrouping() function.
     - Get the priority of an interrupt using HAL_CORTEX_NVIC_GetPriority() function.

  - Enable the selected IRQ channels using HAL_CORTEX_NVIC_EnableIRQ() function.

  - Disable the selected IRQ channels using HAL_CORTEX_NVIC_DisableIRQ() function.

  - To check if an IRQ channel is enable or not, use HAL_CORTEX_NVIC_IsEnabledIRQ() function.

  - To check if an IRQ channel is active or not, use HAL_CORTEX_NVIC_IsActiveIRQ() function.

  - To set pending bit of an interrupt, use HAL_CORTEX_NVIC_SetPendingIRQ() function.

  - To check if the IRQn channel is in pending state or not, use HAL_CORTEX_NVIC_IsPendingIRQ() function. When pending,
    use HAL_CORTEX_NVIC_ClearPendingIRQ() to clear the event.

  - When a system reset is needed within the application, use HAL_CORTEX_NVIC_SystemReset() function.

  - Configure the security attribute of the selected interrupt using HAL_CORTEX_NVIC_SetIRQSecureAttr() function.

  - Get the security attribute of the Interrupt using HAL_CORTEX_NVIC_GetIRQSecureAttr() function.

  - Within the Cortex-M33 driver, all NVIC IRQ management functions are banked. APIs titled HAL_CORTEX_NVICNS_XXX() are
    provided to manage NVIC non-secure instance by a secure software.
     - To redirect an IRQ channel to secure NVIC instance or a non-secure NVIC instance, use
       HAL_CORTEX_NVIC_SetIRQSecureAttr(), this API can be used only by a secure code.

2. How to configure SYSTICK using CORTEX HAL driver :

  - Configure the SYSTICK notification frequency and its source clock using HAL_CORTEX_SYSTICK_SetFreq()
    and HAL_CORTEX_SYSTICK_SetClkSource() functions.

  - To suspend the SYSTICK, use HAL_CORTEX_SYSTICK_Suspend() function. when suspending use HAL_CORTEX_SYSTICK_Resume()
    function to resume the SYSTICK.

  - To handle the SYSTICK interrupts, use HAL_CORTEX_SYSTICK_IRQHandler() function.

  - Within the Cortex-M33 driver, the functions HAL_CORTEX_SYSTICK_SetFreq() and HAL_CORTEX_SYSTICK_SetClkSource()
    are banked. APIs titled HAL_CORTEX_SYSTICKNS_SetFreq() and  HAL_CORTEX_SYSTICKNS_SetClkSource() are provided
    to configure SYSTICK non-secure instance by a secure software.

3. How to configure MPU using CORTEX HAL driver :

  - To configure a device memory attribute, use HAL_CORTEX_MPU_SetDeviceMemAttr() function and to configure a normal
    memory (cache memory), use HAL_CORTEX_MPU_SetCacheMemAttr() function.

  - To get the device memory attributes config, use HAL_CORTEX_MPU_GetDeviceMemAttr() function.

  - To get the cache memory attributes config, use HAL_CORTEX_MPU_GetCacheMemAttr() function.

  - To configure an MPU region, use HAL_CORTEX_MPU_SetConfigRegion() function.

  - To get the MPU region config, use HAL_CORTEX_MPU_GetConfigRegion() function.

  - To enable or disable an MPU region, use HAL_CORTEX_MPU_EnableRegion() or HAL_CORTEX_MPU_DisableRegion() functions.

  - To enable or disable the MPU, use HAL_CORTEX_MPU_Enable() or HAL_CORTEX_MPU_Disable() functions.

  - To check if the MPU is enabled or not, use HAL_CORTEX_MPU_IsEnabled() function.

  - To check if the given MPU region is enabled or not, use HAL_CORTEX_MPU_IsEnabledRegion() function.

  - Within the Cortex-M33 driver, all MPU management functions are banked. APIs titled HAL_CORTEX_MPUNS_XXX() are
    provided to manage MPU non-secure instance by a secure software.

4. How to configure SCB using CORTEX HAL driver :

  - When there is a need to get the CPU ID information within the application, use HAL_CORTEX_SCB_GetInfo() function.

  - Some exceptions can be redirected to their own IRQ channels or to HARDFAULT IRQ channel. These exceptions are :
     - USAGE FAULT
     - BUS FAULT
     - MEMORY MANAGEMENT FAULT
     - SECURE FAULT (Limited to Cortex-M33 when TrustZone is enabled)

  - When there is a need to redirect any exception to a hardfault, use HAL_CORTEX_SCB_DisableHardFaultEscalation()
    function.

  - When there is a need to disable any hardfault redirection, use HAL_CORTEX_SCB_EnableHardFaultEscalation() function.

  - Within the Cortex-M33 driver, the functions HAL_CORTEX_SCB_DisableHardFaultEscalation()
    and HAL_CORTEX_SCB_EnableHardFaultEscalation() are banked.
    APIs titled HAL_CORTEX_SCBNS_DisableHardFaultEscalation() and HAL_CORTEX_SCBNS_EnableHardFaultEscalation()
    are provided to manage SCB non-secure instance by a secure software.

## Configuration inside the CORTEX driver

Config defines         | Description     | Default value | Note
-----------------------| --------------- | ------------- | ------------------------------------------
PRODUCT                | from IDE        |     NA        | The selected product.
USE_ASSERT_DBG_PARAM   | from IDE        |     NA        | When defined, enable the params assert
USE_ASSERT_CHECK_PARAM | from hal_conf.h |     0         | When set, the vital parameters are checked in run time
USE_HAL_CORTEX_MODULE  | from hal_conf.h |     1         | When set, HAL CORTEX module is enabled
__ARM_FEATURE_CMSE     | From IDE        |     NA        | When set to 3, the trust zone is enabled
  */

#if defined(USE_HAL_CORTEX_MODULE) && (USE_HAL_CORTEX_MODULE == 1U)

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup CORTEX_Private_Constants CORTEX Private Constants
  * @{
  */
#define CORTEX_DEVICE_MASK      (0x0000000CU) /*!< Device memory mask          */
#define CORTEX_NORMAL_MASK      (0x000000F0U) /*!< Normal memory mask          */
#define CORTEX_ATTR_OUTER_MASK  (0x000000F0U) /*!< Outer attribute mask        */
#define CORTEX_ATTR_INNER_MASK  (0x0000000FU) /*!< Inner attribute mask        */
#define CORTEX_ATTR_REG_NUM     (0x00000004U) /*!< Attribute register number   */
#define CORTEX_ATTR_BITS_NUM    (0x00000008U) /*!< Attribute bits number       */
#define CORTEX_REGION_ADDR_MASK (0xFFFFFFE0U) /*!< Base and limit address mask */
/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup CORTEX_Private_Macros CORTEX Private Macros
  * @{
  */
/*! Macro to identify irq number */
#if defined(JPEG)
#define IS_IRQ_NUMBER(irq_number) ((irq_number) <= JPEG_IRQn)
#elif defined(DCACHE2)
#define IS_IRQ_NUMBER(irq_number) ((irq_number) <= DCACHE2_IRQn)
#elif defined(HSPI1)
#define IS_IRQ_NUMBER(irq_number) ((irq_number) <= HSPI1_IRQn)
#else
#define IS_IRQ_NUMBER(irq_number) ((irq_number) <= LSECSSD_IRQn)
#endif /* defined(JPEG) */

/*! Macro to identify priority grouping */
#define IS_PRIORITY_GROUP(prio_grp) (((prio_grp) == HAL_CORTEX_NVIC_PRIORITY_GROUP_0)    \
                                     || ((prio_grp) == HAL_CORTEX_NVIC_PRIORITY_GROUP_1) \
                                     || ((prio_grp) == HAL_CORTEX_NVIC_PRIORITY_GROUP_2) \
                                     || ((prio_grp) == HAL_CORTEX_NVIC_PRIORITY_GROUP_3) \
                                     || ((prio_grp) == HAL_CORTEX_NVIC_PRIORITY_GROUP_4))

/*! Macro to identify preemption priority according the given priority group */
#define IS_PREEMP_PRIORITY(prio_grp, preemp_prio) (                                 \
    (((prio_grp)) == (HAL_CORTEX_NVIC_PRIORITY_GROUP_0)) ? (((preemp_prio)) == 0U): \
    (((prio_grp)) == (HAL_CORTEX_NVIC_PRIORITY_GROUP_1)) ? (((preemp_prio)) <= 1U): \
    (((prio_grp)) == (HAL_CORTEX_NVIC_PRIORITY_GROUP_2)) ? (((preemp_prio)) <= 3U): \
    (((prio_grp)) == (HAL_CORTEX_NVIC_PRIORITY_GROUP_3)) ? (((preemp_prio)) <= 7U): \
    (((preemp_prio) <= 15U)))

/*! Macro to identify sub-priority according the given priority group */
#define IS_SUB_PRIORITY(prio_grp, sub_prio) (                                      \
    (((prio_grp)) == (HAL_CORTEX_NVIC_PRIORITY_GROUP_0)) ? (((sub_prio) <= 15U)) : \
    (((prio_grp)) == (HAL_CORTEX_NVIC_PRIORITY_GROUP_1)) ? (((sub_prio) <= 7U))  : \
    (((prio_grp)) == (HAL_CORTEX_NVIC_PRIORITY_GROUP_2)) ? (((sub_prio) <= 3U))  : \
    (((prio_grp)) == (HAL_CORTEX_NVIC_PRIORITY_GROUP_3)) ? (((sub_prio) <= 1U))  : \
    (((sub_prio) == 0U)))

/*! Macro to identify the clock source*/
#define IS_CLOCK_SOURCE(clk_src) (((clk_src) == HAL_CORTEX_SYSTICK_CLKSOURCE_EXTERNAL) \
                                  || ((clk_src) == HAL_CORTEX_SYSTICK_CLKSOURCE_INTERNAL))

/*! Macro to identify the hardfault NMI state */
#define IS_NMI_STATE(fault_nmi) (((fault_nmi) == HAL_CORTEX_MPU_HARDFAULT_NMI_DISABLE)  \
                                 || ((fault_nmi) == HAL_CORTEX_MPU_HARDFAULT_NMI_ENABLE))

/*! Macro to identify the Access Privilege */
#define IS_ACCESS_PRIV(access_priv) (((access_priv) == HAL_CORTEX_MPU_ACCESS_FAULT_ALL)          \
                                     || ((access_priv) == HAL_CORTEX_MPU_ACCESS_FAULT_ONLY_PRIV))

/*! Macro to identify device memory attribute */
#define IS_DEVICE_MEM_ATTR(device_attr) (((device_attr) == HAL_CORTEX_MPU_DEVICE_MEM_NGNRNE)    \
                                         || ((device_attr) == HAL_CORTEX_MPU_DEVICE_MEM_NGNRE)  \
                                         || ((device_attr) == HAL_CORTEX_MPU_DEVICE_MEM_NGRE)   \
                                         || ((device_attr) == HAL_CORTEX_MPU_DEVICE_MEM_GRE))

/*! Macro to identify the memory attribute */
#define IS_NORMAL_MEM_ATTR(mem_attr) (((mem_attr) == HAL_CORTEX_MPU_NORMAL_MEM_NCACHEABLE)               \
                                      || ((mem_attr) == HAL_CORTEX_MPU_NORMAL_MEM_WT_NOA)                \
                                      || ((mem_attr) == HAL_CORTEX_MPU_NORMAL_MEM_WT_WA)                 \
                                      || ((mem_attr) == HAL_CORTEX_MPU_NORMAL_MEM_WT_RA)                 \
                                      || ((mem_attr) == HAL_CORTEX_MPU_NORMAL_MEM_WT_RWA)                \
                                      || ((mem_attr) == HAL_CORTEX_MPU_NORMAL_MEM_WB_NOA)                \
                                      || ((mem_attr) == HAL_CORTEX_MPU_NORMAL_MEM_WB_WA)                 \
                                      || ((mem_attr) == HAL_CORTEX_MPU_NORMAL_MEM_WB_RA)                 \
                                      || ((mem_attr) == HAL_CORTEX_MPU_NORMAL_MEM_WB_RWA))

/*! Macro to identify the memory attribute index */
#define IS_MEM_ATTR_IDX(mem_attr_idx) (((mem_attr_idx)   == HAL_CORTEX_MPU_MEM_ATTR_0)            \
                                       || ((mem_attr_idx) == HAL_CORTEX_MPU_MEM_ATTR_1)           \
                                       || ((mem_attr_idx) == HAL_CORTEX_MPU_MEM_ATTR_2)           \
                                       || ((mem_attr_idx) == HAL_CORTEX_MPU_MEM_ATTR_3)           \
                                       || ((mem_attr_idx) == HAL_CORTEX_MPU_MEM_ATTR_4)           \
                                       || ((mem_attr_idx) == HAL_CORTEX_MPU_MEM_ATTR_5)           \
                                       || ((mem_attr_idx) == HAL_CORTEX_MPU_MEM_ATTR_6)           \
                                       || ((mem_attr_idx) == HAL_CORTEX_MPU_MEM_ATTR_7))

/*! Macro to identify MPU region index */
#define IS_MPU_REGION(mpu_region) (((mpu_region) == HAL_CORTEX_MPU_REGION_0)    \
                                   || ((mpu_region) == HAL_CORTEX_MPU_REGION_1) \
                                   || ((mpu_region) == HAL_CORTEX_MPU_REGION_2) \
                                   || ((mpu_region) == HAL_CORTEX_MPU_REGION_3) \
                                   || ((mpu_region) == HAL_CORTEX_MPU_REGION_4) \
                                   || ((mpu_region) == HAL_CORTEX_MPU_REGION_5) \
                                   || ((mpu_region) == HAL_CORTEX_MPU_REGION_6) \
                                   || ((mpu_region) == HAL_CORTEX_MPU_REGION_7))

/*! Macro to identify fault exceptions */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_FAULT_EXCEPT(fault_except)                                                                  \
  ((((fault_except) & (HAL_CORTEX_SCB_USAGE_FAULT | HAL_CORTEX_SCB_BUS_FAULT  |                        \
                       HAL_CORTEX_SCB_MEM_MANAGEMENT_FAULT | HAL_CORTEX_SCB_SECURE_FAULT)) != 0x00U)   \
   && (((fault_except) & ~(HAL_CORTEX_SCB_USAGE_FAULT | HAL_CORTEX_SCB_BUS_FAULT |                     \
                           HAL_CORTEX_SCB_MEM_MANAGEMENT_FAULT | HAL_CORTEX_SCB_SECURE_FAULT)) == 0x00U))
#else
#define IS_FAULT_EXCEPT(fault_except)                                              \
  ((((fault_except) & (HAL_CORTEX_SCB_USAGE_FAULT | HAL_CORTEX_SCB_BUS_FAULT  |    \
                       HAL_CORTEX_SCB_MEM_MANAGEMENT_FAULT)) != 0x00U)             \
   && (((fault_except) & ~(HAL_CORTEX_SCB_USAGE_FAULT | HAL_CORTEX_SCB_BUS_FAULT | \
                           HAL_CORTEX_SCB_MEM_MANAGEMENT_FAULT)) == 0x00U))
#endif /* __ARM_FEATURE_CMSE */

/*! Macro to identify region access attribute */
#define IS_ACCESS_ATTR(access_attr) (((access_attr) == HAL_CORTEX_MPU_REGION_ONLY_PRIV_RW)    \
                                     || ((access_attr) == HAL_CORTEX_MPU_REGION_ALL_RW)       \
                                     || ((access_attr) == HAL_CORTEX_MPU_REGION_ONLY_PRIV_RO) \
                                     || ((access_attr) == HAL_CORTEX_MPU_REGION_ALL_RO))

/*! Macro to identify the execution attribute */
#define IS_EXEC_ATTR(exec_attr)      (((exec_attr) == HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE) \
                                      || ((exec_attr) == HAL_CORTEX_MPU_EXECUTION_ATTR_ENABLE))

/*! Macro to identify interrupt security attribute */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_SEC_ATTR(sec_attr)      (((sec_attr) == HAL_CORTEX_ATTR_NSEC)    \
                                    || ((sec_attr) == HAL_CORTEX_ATTR_SEC))
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup CORTEX_Exported_Functions
  * @{
  */

/** @addtogroup CORTEX_Exported_Functions_Group1
  * @{
- This subsection provides a set of functions allowing to configure cortex NVIC block features.
  - Use HAL_CORTEX_NVIC_SetPriorityGrouping() to set the priority grouping.
  - Use HAL_CORTEX_NVIC_GetPriorityGrouping() to get the priority grouping.
  - Use HAL_CORTEX_NVIC_SetPriority() to set the interrupt preemption priority.
  - Use HAL_CORTEX_NVIC_GetPriority() to get the interrupt preemption priority.
  - Use HAL_CORTEX_NVIC_EnableIRQ() to enable an interrupt.
  - Use HAL_CORTEX_NVIC_DisableIRQ() to disable the interrupt.
  - Use HAL_CORTEX_NVIC_IsEnabledIRQ() to check whether an interrupt is enabled or not.
  - Use HAL_CORTEX_NVIC_IsActiveIRQ() to check whether an interrupt is active or not.
  - Use HAL_CORTEX_NVIC_SetPendingIRQ() to set an interrupt in pending state.
  - Use HAL_CORTEX_NVIC_ClearPendingIRQ() to clear a pending interrupt.
  - Use HAL_CORTEX_NVIC_IsPendingIRQ() to check whether an interrupt is pending or not.
  - Use HAL_CORTEX_NVIC_SystemReset() to perform a system reset.
- Within the Cortex-M33 driver, all NVIC IRQ management functions are banked. There are
  equivalent APIs as mentioned above named HAL_CORTEX_NVICNS_XXX() and provided to manage NVIC
  non-secure instance by a secure software.
  */

/**
  * @brief   Set the priority grouping field (pre-emption priority and subpriority)
  *          using the required unlock sequence.
  * @param   prio_grp: The priority grouping bits length.
  *          This parameter is an element of \ref hal_cortex_nvic_priority_group_t enumeration.
  * @warning When the HAL_CORTEX_NVIC_PRIORITY_GROUP_0 is selected, IRQ pre-emption is no more possible.
  *          The pending IRQ priority is managed only by the subpriority.
  * @note    When the HAL_CORTEX_NVIC_PRIORITY_GROUP_1 is selected, there is one bit for preemption priority and three
  *          bits for sub-priority.
  * @note    When the HAL_CORTEX_NVIC_PRIORITY_GROUP_2 is selected, there are two bits for preemption priority and two
  *          bits for sub-priority.
  * @note    When the HAL_CORTEX_NVIC_PRIORITY_GROUP_3 is selected, there are three bits for preemption priority and one
  *          bit for sub-priority.
  * @warning When the HAL_CORTEX_NVIC_PRIORITY_GROUP_4 is selected, IRQ subpriority is no more possible.
  *          The pending IRQ priority is managed only by the pre-emption.
  */
void HAL_CORTEX_NVIC_SetPriorityGrouping(hal_cortex_nvic_priority_group_t prio_grp)
{
  ASSERT_DBG_PARAM(IS_PRIORITY_GROUP(prio_grp));

  NVIC_SetPriorityGrouping((uint32_t)prio_grp);
}

/**
  * @brief  Get the priority grouping field from the NVIC Interrupt Controller.
  * @retval hal_cortex_nvic_priority_group_t priority group value.
  */
hal_cortex_nvic_priority_group_t HAL_CORTEX_NVIC_GetPriorityGrouping(void)
{
  return ((hal_cortex_nvic_priority_group_t)NVIC_GetPriorityGrouping());
}

/**
  * @brief  Set the priority of an interrupt.
  * @param  irqn: The interrupt number.
  *         This parameter can be a value of IRQn_Type enumeration.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *          CMSIS device file (stm32u5xxxx.h))
  * @param  preemp_prio: Specify the pre-emption priority for the IRQn channel.
  *         This parameter is an element of \ref hal_cortex_nvic_preemp_priority_t enumeration.
  * @param  sub_prio: specify the subpriority level for the IRQ channel.
  *         This parameter is an element of \ref hal_cortex_nvic_sub_priority_t enumeration.
  */
void HAL_CORTEX_NVIC_SetPriority(IRQn_Type irqn, hal_cortex_nvic_preemp_priority_t preemp_prio,
                                 hal_cortex_nvic_sub_priority_t sub_prio)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));
  ASSERT_DBG_PARAM(IS_PREEMP_PRIORITY(NVIC_GetPriorityGrouping(), preemp_prio));
  ASSERT_DBG_PARAM(IS_SUB_PRIORITY(NVIC_GetPriorityGrouping(), sub_prio));

  /* Set the pre-emption priority and sub-priority according to the priority grouping meaning
     the number of allocated bits used respectively to encode the pre-emption and sub-priority*/
  NVIC_SetPriority(irqn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), (uint32_t)preemp_prio, (uint32_t)sub_prio));
}

/**
  * @brief  Get the priority of an interrupt.
  * @param  irqn: The interrupt number.
  *          This parameter can be a value of IRQn_Type enumeration.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *          CMSIS device file (stm32u5xxxx.h))
  * @param  p_preemp_prio: get the pre-emption priority for the IRQn channel.
  *         This parameter is an element of \ref hal_cortex_nvic_preemp_priority_t enumeration.
  * @param  p_sub_prio: get the subpriority level for the IRQ channel.
  *         This parameter is an element of \ref hal_cortex_nvic_sub_priority_t enumeration.
  */
void HAL_CORTEX_NVIC_GetPriority(IRQn_Type irqn, hal_cortex_nvic_preemp_priority_t *p_preemp_prio,
                                 hal_cortex_nvic_sub_priority_t *p_sub_prio)
{
  uint32_t preemp_prio = 0U;
  uint32_t sub_prio = 0U;

  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));
  ASSERT_DBG_PARAM(p_preemp_prio != NULL);
  ASSERT_DBG_PARAM(p_sub_prio != NULL);
  /* Retrieve the pre-emption priority and sub-priority according to the priority grouping meaning the number
     of allocated bits used respectively to encode the pre-emption and sub-priority */
  NVIC_DecodePriority(NVIC_GetPriority(irqn), (uint32_t)NVIC_GetPriorityGrouping(), &preemp_prio, &sub_prio);

  *p_preemp_prio = (hal_cortex_nvic_preemp_priority_t)preemp_prio;
  *p_sub_prio    = (hal_cortex_nvic_sub_priority_t)sub_prio;
}

/**
  * @brief  Enable the specific interrupt in the NVIC interrupt controller.
  * @param  irqn External interrupt number.
  *         This parameter can be a value of IRQn_Type.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *          CMSIS device file (stm32u5xxxx.h))
  */
void HAL_CORTEX_NVIC_EnableIRQ(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  NVIC_EnableIRQ(irqn);
}

/**
  * @brief  Disable the specific interrupt in the NVIC interrupt controller.
  * @param  irqn External interrupt number.
  *         This parameter can be a value of IRQn_Type.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *          CMSIS device file (stm32u5xxxx.h))
  */
void HAL_CORTEX_NVIC_DisableIRQ(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  NVIC_DisableIRQ(irqn);
}

/**
  * @brief Check if the specified irqn is enabled or disabled.
  * @param irqn: Specify the interrupt number.
  *        This parameter can be a value of IRQn_Type enumeration.
  *        (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *         CMSIS device file (stm32u5xxxx.h))
  * @retval hal_cortex_nvic_irq_status_t interrupt enable status value.
  */
hal_cortex_nvic_irq_status_t HAL_CORTEX_NVIC_IsEnabledIRQ(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  return ((hal_cortex_nvic_irq_status_t)NVIC_GetEnableIRQ(irqn));
}

/**
  * @brief Check active interrupt.
  * @param irqn: Specify the interrupt number.
  *         This parameter can be a value of IRQn_Type.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *          CMSIS device file (stm32u5xxxx.h))
  * @note  Reads the active register in NVIC and returns the active bit.
  * @retval hal_cortex_nvic_irq_active_status_t interrupt active status value.
  */
hal_cortex_nvic_irq_active_status_t HAL_CORTEX_NVIC_IsActiveIRQ(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  return ((hal_cortex_nvic_irq_active_status_t)NVIC_GetActive(irqn));
}

/**
  * @brief  Set Pending bit of an external interrupt.
  * @param  irqn External interrupt number.
  *         This parameter can be a value of IRQn_Type enumeration.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *          CMSIS device file (stm32u5xxxx.h))
  */
void HAL_CORTEX_NVIC_SetPendingIRQ(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  NVIC_SetPendingIRQ(irqn);
}

/**
  * @brief  Clear the pending bit of an external interrupt.
  * @param  irqn External interrupt number.
  *         This parameter can be a value of IRQn_Type enumeration.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *          CMSIS device file (stm32u5xxxx.h))
  */
void HAL_CORTEX_NVIC_ClearPendingIRQ(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  NVIC_ClearPendingIRQ(irqn);
}

/**
  * @brief  Check Pending Interrupt.
  * @note   Reads the NVIC pending register and returns the pending bit for the specified interrupt.
  * @param  irqn External interrupt number.
  *         This parameter can be a value of IRQn_Type enumeration.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *         CMSIS device file (stm32u5xxxx.h))
  * @retval hal_cortex_nvic_irq_pending_status_t interrupt pending status value.
  */
hal_cortex_nvic_irq_pending_status_t HAL_CORTEX_NVIC_IsPendingIRQ(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  return ((hal_cortex_nvic_irq_pending_status_t)NVIC_GetPendingIRQ(irqn));
}

/**
  * @brief  Initiate a system reset request to reset the MCU.
  */
__NO_RETURN void HAL_CORTEX_NVIC_SystemReset(void)
{
  NVIC_SystemReset();
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Set Interrupt security attribute.
  * @param  irqn External interrupt number.
  *         This parameter can be a value of IRQn_Type enumeration.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *         CMSIS device file (stm32u5xxxx.h))
  * @param  attr Specifies whether the IRQ is secure or not secure.
  *         This parameter is an element of \ref hal_cortex_security_attr_t enumeration.
  */
void HAL_CORTEX_NVIC_SetIRQSecureAttr(IRQn_Type irqn, hal_cortex_security_attr_t attr)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));
  ASSERT_DBG_PARAM(IS_SEC_ATTR(attr));

  if (attr == HAL_CORTEX_ATTR_SEC)
  {
    (void)NVIC_ClearTargetState(irqn);
  }
  else
  {
    (void)NVIC_SetTargetState(irqn);
  }
}

/**
  * @brief  Get Interrupt security attribute.
  * @param  irqn External interrupt number.
  *         This parameter can be a value of IRQn_Type enumeration.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *         CMSIS device file (stm32u5xxxx.h))
  * @retval hal_cortex_security_attr_t interrupt security attribute value.
  */
hal_cortex_security_attr_t HAL_CORTEX_NVIC_GetIRQSecureAttr(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  return ((hal_cortex_security_attr_t)NVIC_GetTargetState(irqn));
}

/**
  * @brief   Set the non-secure priority grouping field (pre-emption priority and subpriority)
  *          using the required unlock sequence.
  * @param   prio_grp: The priority grouping bits length.
  *          This parameter is an element of \ref hal_cortex_nvic_priority_group_t enumeration.
  * @warning This function behaves same as HAL_CORTEX_NVIC_SetPriorityGrouping() except that it is intended to called in
  *          secure code to set the priority grouping of the non-secure NVIC instance.
  * @note    When the HAL_CORTEX_NVIC_PRIORITY_GROUP_0 is selected, IRQ pre-emption is no more possible.
  *          The pending IRQ priority is managed only by the subpriority.
  * @note    When the HAL_CORTEX_NVIC_PRIORITY_GROUP_1 is selected, there is one bit for preemption priority and three
  *          bits for sub-priority.
  * @note    When the HAL_CORTEX_NVIC_PRIORITY_GROUP_2 is selected, there are two bits for preemption priority and two
  *          bits for sub-priority.
  * @note    When the HAL_CORTEX_NVIC_PRIORITY_GROUP_3 is selected, there are three bits for preemption priority and one
  *          bit for sub-priority.
  * @warning When the HAL_CORTEX_NVIC_PRIORITY_GROUP_4 is selected, IRQ subpriority is no more possible.
  *          The pending IRQ priority is managed only by the pre-emption.
  */
void HAL_CORTEX_NVICNS_SetPriorityGrouping(hal_cortex_nvic_priority_group_t prio_grp)
{
  ASSERT_DBG_PARAM(IS_PRIORITY_GROUP(prio_grp));

  TZ_NVIC_SetPriorityGrouping_NS((uint32_t)prio_grp);
}

/**
  * @brief  Get the non-secure priority grouping field from the NVIC Interrupt Controller.
  * @retval hal_cortex_nvic_priority_group_t priority group value.
  * @note   This function behaves same as HAL_CORTEX_NVIC_GetPriorityGrouping() except that it is intended to called in
  *         secure code to get the priority grouping of the non-secure NVIC instance.
  */
hal_cortex_nvic_priority_group_t HAL_CORTEX_NVICNS_GetPriorityGrouping(void)
{
  return ((hal_cortex_nvic_priority_group_t)TZ_NVIC_GetPriorityGrouping_NS());
}

/**
  * @brief  Set interrupt priority (non-secure).
  * @param  irqn: The interrupt number.
  *         This parameter can be a value of IRQn_Type enumeration.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *          CMSIS device file (stm32u5xxxx.h))
  * @param  preemp_prio: Specify the pre-emption priority for the IRQn channel.
  *         This parameter is an element of \ref hal_cortex_nvic_preemp_priority_t enumeration.
  * @param  sub_prio: specify the subpriority level for the IRQ channel.
  *         This parameter is an element of \ref hal_cortex_nvic_sub_priority_t enumeration.
  * @note   This function behaves same as HAL_CORTEX_NVIC_SetPriority() except that it is intended to called in
  *         secure code to set the priority of the non-secure NVIC instance.
  */
void HAL_CORTEX_NVICNS_SetPriority(IRQn_Type irqn, hal_cortex_nvic_preemp_priority_t preemp_prio,
                                   hal_cortex_nvic_sub_priority_t sub_prio)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));
  ASSERT_DBG_PARAM(IS_PREEMP_PRIORITY(TZ_NVIC_GetPriorityGrouping_NS(), preemp_prio));
  ASSERT_DBG_PARAM(IS_SUB_PRIORITY(TZ_NVIC_GetPriorityGrouping_NS(), sub_prio));

  TZ_NVIC_SetPriority_NS(irqn, NVIC_EncodePriority(TZ_NVIC_GetPriorityGrouping_NS(), (uint32_t)preemp_prio,
                                                   (uint32_t)sub_prio));
}

/**
  * @brief  Get interrupt priority (non-secure).
  * @param  irqn: The interrupt number.
  *          This parameter can be a value of IRQn_Type enumeration.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *          CMSIS device file (stm32u5xxxx.h))
  * @param  p_preemp_prio: get the pre-emption priority for the IRQn channel.
  *         This parameter is an element of \ref hal_cortex_nvic_preemp_priority_t enumeration.
  * @param  p_sub_prio: get the subpriority level for the IRQ channel.
  *         This parameter is an element of \ref hal_cortex_nvic_sub_priority_t enumeration.
  * @note   This function behaves same as HAL_CORTEX_NVIC_GetPriority() except that it is intended to called in
  *         secure code to get the interrupt priority of the non-secure NVIC instance.
  */
void HAL_CORTEX_NVICNS_GetPriority(IRQn_Type irqn, hal_cortex_nvic_preemp_priority_t *p_preemp_prio,
                                   hal_cortex_nvic_sub_priority_t *p_sub_prio)
{
  uint32_t preemp_prio = 0U;
  uint32_t sub_prio = 0U;

  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));
  ASSERT_DBG_PARAM(p_preemp_prio != NULL);
  ASSERT_DBG_PARAM(p_sub_prio != NULL);
  /* Retrieve the pre-emption priority and sub-priority according to the priority grouping meaning the number
     of allocated bits used respectively to encode the pre-emption and sub-priority */
  NVIC_DecodePriority(TZ_NVIC_GetPriority_NS(irqn), (uint32_t)TZ_NVIC_GetPriorityGrouping_NS(), &preemp_prio,
                      &sub_prio);
  *p_preemp_prio = (hal_cortex_nvic_preemp_priority_t)preemp_prio;
  *p_sub_prio    = (hal_cortex_nvic_sub_priority_t)sub_prio;
}

/**
  * @brief  Enable specific non-secure interrupt in the NVIC interrupt controller.
  * @param  irqn External interrupt number.
  *         This parameter can be a value of IRQn_Type enumeration.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *          CMSIS device file (stm32u5xxxx.h))
  * @note   This function behaves same as HAL_CORTEX_NVIC_EnableIRQ() except that it is intended to called in
  *         secure code to enable interrupt of the non -ecure NVIC instance.
  */
void HAL_CORTEX_NVICNS_EnableIRQ(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  TZ_NVIC_EnableIRQ_NS(irqn);
}

/**
  * @brief  Disable specific non-secure interrupt in the NVIC interrupt controller.
  * @param  irqn External interrupt number.
  *         This parameter can be a value of IRQn_Type enumeration.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *          CMSIS device file (stm32u5xxxx.h)).
  * @note   This function behaves same as HAL_CORTEX_NVIC_DisableIRQ() except that it is intended to called in
  *         secure code to disable interrupt of the non-secure NVIC instance.
  */
void HAL_CORTEX_NVICNS_DisableIRQ(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  TZ_NVIC_DisableIRQ_NS(irqn);
}

/**
  * @brief Check if the specified irqn in non-secure mode is enabled or disabled.
  * @param irqn: Specify the interrupt number.
  *        This parameter can be a value of IRQn_Type enumeration.
  *        (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *         CMSIS device file (stm32u5xxxx.h))
  * @retval hal_cortex_nvic_irq_status_t interrupt status enabled value.
  * @note   This function behaves same as HAL_CORTEX_NVIC_IsEnabledIRQ() except that it is intended to called in
  *         secure code to check if the irqn of the non-secure NVIC instance is enabled or disabled.
  */
hal_cortex_nvic_irq_status_t HAL_CORTEX_NVICNS_IsEnabledIRQ(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  return ((hal_cortex_nvic_irq_status_t)TZ_NVIC_GetEnableIRQ_NS(irqn));
}

/**
  * @brief Check active interrupt in non-secure mode (read the active register in NVIC and return the active bit).
  * @param irqn: Specify the interrupt number
  *        This parameter can be a value of IRQn_Type enumeration.
  *        (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *         CMSIS device file (stm32u5xxxx.h))
  * @retval hal_cortex_nvic_irq_active_status_t interrupt active status value.
  * @note   This function behaves same as HAL_CORTEX_NVIC_IsActiveIRQ() except that it is intended to called in
  *         secure code to check the irqn of the non-secure NVIC instance is active or not.
  */
hal_cortex_nvic_irq_active_status_t HAL_CORTEX_NVICNS_IsActiveIRQ(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  return ((hal_cortex_nvic_irq_active_status_t)TZ_NVIC_GetActive_NS(irqn));
}

/**
  * @brief  Set pending bit in non-secure mode of an external interrupt.
  * @param  irqn External interrupt number
  *         This parameter can be a value of IRQn_Type enumeration.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *          CMSIS device file (stm32u5xxxx.h))
  * @note   This function behaves same as HAL_CORTEX_NVIC_SetPendingIRQ() except that it is intended to called in
  *         secure code to set pending irqn of the non-secure NVIC instance.
  */
void HAL_CORTEX_NVICNS_SetPendingIRQ(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  TZ_NVIC_SetPendingIRQ_NS(irqn);
}

/**
  * @brief  Clear the pending bit in non-secure mode of an external interrupt.
  * @param  irqn External interrupt number.
  *         This parameter can be a value of IRQn_Type enumeration.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *          CMSIS device file (stm32u5xxxx.h))
  * @note   This function behaves same as HAL_CORTEX_NVIC_ClearPendingIRQ() except that it is intended to called in
  *         secure code to clear pending interrupt of the non-secure NVIC instance.
  */
void HAL_CORTEX_NVICNS_ClearPendingIRQ(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  TZ_NVIC_ClearPendingIRQ_NS(irqn);
}

/**
  * @brief  Check if the Pending Interrupt in non-secure mode is enabled or disabled
  *         (read the pending register in the NVIC
  *         and return the pending bit for the specified interrupt).
  * @param  irqn External interrupt number.
  *         This parameter can be a value of IRQn_Type enumeration.
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate
  *         CMSIS device file (stm32u5xxxx.h))
  * @retval hal_cortex_nvic_irq_pending_status_t interrupt pending status value.
  * @note   This function behaves same as HAL_CORTEX_NVIC_IsPendingIRQ() except that it is intended to called in
  *         secure code to check pending interrupt of the non-secure NVIC instance.
  */
hal_cortex_nvic_irq_pending_status_t HAL_CORTEX_NVICNS_IsPendingIRQ(IRQn_Type irqn)
{
  ASSERT_DBG_PARAM(IS_IRQ_NUMBER(irqn));

  return ((hal_cortex_nvic_irq_pending_status_t)TZ_NVIC_GetPendingIRQ_NS(irqn));
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @}
  */

/** @addtogroup CORTEX_Exported_Functions_Group2
  * @{
- This subsection provides a set of functions allowing to configure cortex SYSTICK block features.
  - Use HAL_CORTEX_SYSTICK_SetFreq() to configure SYSTICK block frequency.
  - Use HAL_CORTEX_SYSTICK_SetClkSource() to configure clock source.
  - Use HAL_CORTEX_SYSTICK_Suspend() to suspend the core ticks.
  - Use HAL_CORTEX_SYSTICK_Resume() to resume the core ticks.
  - Use HAL_CORTEX_SYSTICKNS_SetFreq() within a secure software to configure the non-secure SYSTICK block frequency.
  - Use HAL_CORTEX_SYSTICKNS_SetClkSource() within a secure software to configure the non-secure clock source.
  - Use HAL_CORTEX_SYSTICKNS_Suspend() within a secure software to suspend the core ticks.
  - Use HAL_CORTEX_SYSTICKNS_Resume()  within a secure software to resume the core ticks.
  */

/**
  * @brief  Configure the SysTick frequency.
  * @param  ticks_freq: specifies the frequency in Hz.
  * @retval HAL_OK              Function succeeded.
  * @retval HAL_ERROR           Function failed.
  * @retval HAL_INVALID_PARAM   Invalid parameter.
  */
hal_status_t HAL_CORTEX_SYSTICK_SetFreq(uint32_t ticks_freq)
{
  uint32_t ticks = 0U;

  /* Check the parameters */
  ASSERT_DBG_PARAM(ticks_freq > 0UL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (ticks_freq == 0UL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Get ticks frequency according to the SysTick source clock frequency */
  if (READ_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk) == SysTick_CTRL_CLKSOURCE_Msk)
  {
    /* The SysTick clock source is the CPU clock, get the CPU clock frequency */
    ticks = HAL_RCC_GetHCLKFreq();
  }
  else
  {
    /* The SysTick clock source is external (RCC). Get its frequency */
    ticks = HAL_RCC_GetSysTickExternalClkFreq();
  }

  ticks /= ticks_freq;

  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
  {
    /* Reload value impossible */
    return HAL_ERROR;
  }

  /* Set the SysTick reload counter according to the ticks frequency and requested frequency */
  WRITE_REG(SysTick->LOAD, (uint32_t)(ticks - 1UL));

  /* Load the SysTick counter Value */
  WRITE_REG(SysTick->VAL, 0UL);

  /* Enable the SysTick IRQ and SysTick Timer */
  MODIFY_REG(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk, \
             SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);

  return HAL_OK;
}

/**
  * @brief  Configure the SysTick clock source.
  * @param  clk_src: specifies the SysTick clock source.
  *         This parameter is an element of \ref hal_cortex_systick_clk_src_t enumeration.
  */
void HAL_CORTEX_SYSTICK_SetClkSource(hal_cortex_systick_clk_src_t clk_src)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(IS_CLOCK_SOURCE(clk_src));

  /* Configures the SysTick CPU clock source */
  MODIFY_REG(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk, (uint32_t)clk_src);
}

/**
  * @brief Suspend core ticks.
  */
void HAL_CORTEX_SYSTICK_Suspend(void)
{
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

/**
  * @brief Resume core ticks.
  */
void HAL_CORTEX_SYSTICK_Resume(void)
{
  SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk;
}

/**
  * @brief  Handle SYSTICK interrupt request.
  */
void HAL_CORTEX_SYSTICK_IRQHandler(void)
{
  HAL_CORTEX_SYSTICK_Callback();
}

/**
  * @brief  SYSTICK callback.
  */
__WEAK void HAL_CORTEX_SYSTICK_Callback(void)
{
  /* warning : This function must not be modified, when the callback is needed,
            the HAL_CORTEX_SYSTICK_Callback could be implemented in the user file
   */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Configure the SysTick_NS frequency.
  * @param  ticks_freq: specifies the frequency in Hz.
  * @retval HAL_OK              Function succeeded.
  * @retval HAL_ERROR           Function failed.
  * @retval HAL_INVALID_PARAM   Invalid parameter.
  */
hal_status_t HAL_CORTEX_SYSTICKNS_SetFreq(uint32_t ticks_freq)
{
  uint32_t ticks = 0U;

  /* Check the parameters */
  ASSERT_DBG_PARAM(ticks_freq > 0UL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)

  if (ticks_freq == 0UL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Get ticks frequency according to the SysTick source clock frequency */
  if (READ_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk) == SysTick_CTRL_CLKSOURCE_Msk)
  {
    /* The SysTick clock source is the CPU clock, get the CPU clock frequency */
    ticks = HAL_RCC_GetHCLKFreq();
  }
  else
  {
    /* The SysTick clock source is external (RCC). Get its frequency */
    ticks = HAL_RCC_GetSysTickExternalClkFreq();
  }

  ticks /= ticks_freq;

  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
  {
    /* Reload value impossible */
    return HAL_ERROR;
  }

  /* Set the SysTick reload counter according to the ticks frequency and requested frequency */
  WRITE_REG(SysTick_NS->LOAD, (uint32_t)(ticks - 1UL));

  /* Load the SysTick counter Value */
  WRITE_REG(SysTick_NS->VAL, 0UL);

  /* Enable the SysTick IRQ and SysTick Timer */
  MODIFY_REG(SysTick_NS->CTRL, SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk, \
             SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);

  return HAL_OK;
}

/**
  * @brief  Configure the SysTick_NS clock source.
  * @param  clk_src: specifies the SysTick clock source.
  *         This parameter is an element of \ref hal_cortex_systick_clk_src_t enumeration.
  */
void HAL_CORTEX_SYSTICKNS_SetClkSource(hal_cortex_systick_clk_src_t clk_src)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(IS_CLOCK_SOURCE(clk_src));

  /* Configures the SysTick CPU clock source */
  MODIFY_REG(SysTick_NS->CTRL, SysTick_CTRL_CLKSOURCE_Msk, (uint32_t)clk_src);
}

/**
  * @brief Suspend core ticks.
  */
void HAL_CORTEX_SYSTICKNS_Suspend(void)
{
  SysTick_NS->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

/**
  * @brief Resume core ticks..
  */
void HAL_CORTEX_SYSTICKNS_Resume(void)
{
  SysTick_NS->CTRL  |= SysTick_CTRL_TICKINT_Msk;
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @}
  */

/** @addtogroup CORTEX_Exported_Functions_Group3
  *  @{
- This subsection provides a set of functions allowing to configure the cortex MPU block features.
  - Use HAL_CORTEX_MPU_Enable() to enable the MPU.
  - Use HAL_CORTEX_MPU_Disable() to disable the MPU.
  - Use HAL_CORTEX_MPU_IsEnabled() to check whether the MPU is enabled or disabled.
  - Use HAL_CORTEX_MPU_GetDeviceMemAttr() to get device memory attributes.
  - Use HAL_CORTEX_MPU_SetDeviceMemAttr() to set device memory attributes.
  - Use HAL_CORTEX_MPU_GetCacheMemAttr() to get normal memory (cache) attributes.
  - Use HAL_CORTEX_MPU_SetCacheMemAttr() to set normal memory (cache) attributes.
  - Use HAL_CORTEX_MPU_SetConfigRegion() to set region configuration.
  - Use HAL_CORTEX_MPU_GetConfigRegion() to get region configuration.
  - Use HAL_CORTEX_MPU_EnableRegion() to enable a region configuration.
  - Use HAL_CORTEX_MPU_DisableRegion() to disable a region configuration.
  - Use HAL_CORTEX_MPU_IsEnabledRegion() to check whether a region memory enabled or not.
  - Within the Cortex-M33 driver, all MPU management functions are banked. There are equivalent APIs as mentioned
    above named HAL_CORTEX_MPUNS_XXX() and provided to manage MPU non-secure instance by a secure software.
  */

/**
  * @brief  Enable MPU and set the control mode of the MPU during hard fault,
  *         NMI, FAULTMASK and privileged access to the default memory.
  * @param  fault_state: configure the control mode during hard fault ,NMI and faultmask.
  *         This parameter is an element of \ref hal_cortex_mpu_hardfault_nmi_state_t enumeration.
  * @param  priv_default_state: configure the privileged access to the default memory.
  *         This parameter is an element of \ref hal_cortex_mpu_unmapped_addr_fault_t enumeration.
  */
void HAL_CORTEX_MPU_Enable(hal_cortex_mpu_hardfault_nmi_state_t fault_state,
                           hal_cortex_mpu_unmapped_addr_fault_t priv_default_state)
{
  ASSERT_DBG_PARAM(IS_NMI_STATE(fault_state));
  ASSERT_DBG_PARAM(IS_ACCESS_PRIV(priv_default_state));

  ARM_MPU_Enable(((uint32_t)fault_state) | ((uint32_t)priv_default_state));
}

/**
  * @brief  Disable MPU
  */
void HAL_CORTEX_MPU_Disable(void)
{
  ARM_MPU_Disable();
}

/**
  * @brief  Check if MPU is enabled or not.
  * @retval hal_cortex_mpu_status_t MPU status value.
  */
hal_cortex_mpu_status_t HAL_CORTEX_MPU_IsEnabled(void)
{
  return ((READ_BIT(MPU->CTRL, MPU_CTRL_ENABLE_Msk) == MPU_CTRL_ENABLE_Msk)
          ? HAL_CORTEX_MPU_ENABLED : HAL_CORTEX_MPU_DISABLED);
}

/**
  * @brief  Set the device memory attributes config.
  * @param  attr_idx: Specify the attributes index.
  *         This parameter is an element of \ref hal_cortex_mpu_mem_attr_idx_t enumeration.
  * @param  mem_attr: Specify the device.
  *         This parameter is an element of \ref hal_cortex_mpu_device_mem_attr_t enumeration.
  */
void HAL_CORTEX_MPU_SetDeviceMemAttr(hal_cortex_mpu_mem_attr_idx_t attr_idx, hal_cortex_mpu_device_mem_attr_t mem_attr)
{
  ASSERT_DBG_PARAM(IS_MEM_ATTR_IDX(attr_idx));
  ASSERT_DBG_PARAM(IS_DEVICE_MEM_ATTR(mem_attr));

  ARM_MPU_SetMemAttr((uint8_t)attr_idx, (uint8_t)mem_attr);
}

/**
  * @brief  Get the device memory attributes config.
  * @param  attr_idx: Specify the attributes index.
  *         This parameter is an element of \ref hal_cortex_mpu_mem_attr_idx_t enumeration.
  * @retval hal_cortex_mpu_device_mem_attr_t device memory attribute value.
  */
hal_cortex_mpu_device_mem_attr_t HAL_CORTEX_MPU_GetDeviceMemAttr(hal_cortex_mpu_mem_attr_idx_t attr_idx)
{
  hal_cortex_mpu_device_mem_attr_t mem_attr;
  uint8_t attr_reg_idx = 0U;
  uint8_t attr_bits_pos = 0U;
  uint8_t dev_attr = 0U;

  ASSERT_DBG_PARAM(IS_MEM_ATTR_IDX(attr_idx));

  attr_reg_idx  = (uint8_t)attr_idx / CORTEX_ATTR_REG_NUM;
  attr_bits_pos = (((uint8_t)attr_idx % CORTEX_ATTR_REG_NUM) * CORTEX_ATTR_BITS_NUM);
  dev_attr      = (uint8_t)(MPU->MAIR[attr_reg_idx] >> attr_bits_pos);

  if ((dev_attr & (~CORTEX_DEVICE_MASK)) == 0U)
  {
    mem_attr = (hal_cortex_mpu_device_mem_attr_t)(dev_attr);
  }
  else
  {
    mem_attr = HAL_CORTEX_MPU_DEVICE_MEM_INVALID;
  }

  return (mem_attr);
}

/**
  * @brief  Set cache memory attributes config.
  * @param  attr_idx: Specify the attributes index.
  *         This parameter is an element of \ref hal_cortex_mpu_mem_attr_idx_t enumeration.
  * @param  mem_attr: Specify the cache memory config.
  *         This parameter is an element of \ref hal_cortex_mpu_normal_mem_cache_attr_t enumeration.
  */
void HAL_CORTEX_MPU_SetCacheMemAttr(hal_cortex_mpu_mem_attr_idx_t attr_idx,
                                    hal_cortex_mpu_normal_mem_cache_attr_t mem_attr)
{
  ASSERT_DBG_PARAM(IS_MEM_ATTR_IDX(attr_idx));
  ASSERT_DBG_PARAM(IS_NORMAL_MEM_ATTR(mem_attr));

  ARM_MPU_SetMemAttr((uint8_t)attr_idx, (CORTEX_ATTR_INNER_MASK | (uint8_t)mem_attr));
}

/**
  * @brief  Get the cache memory attributes config.
  * @param  attr_idx: Specify the attributes index.
  *         This parameter is an element of \ref hal_cortex_mpu_mem_attr_idx_t enumeration.
  * @retval hal_cortex_mpu_normal_mem_cache_attr_t normal memory attribute value.
  */
hal_cortex_mpu_normal_mem_cache_attr_t HAL_CORTEX_MPU_GetCacheMemAttr(hal_cortex_mpu_mem_attr_idx_t attr_idx)
{
  hal_cortex_mpu_normal_mem_cache_attr_t mem_attr;
  uint8_t attr_reg_idx = 0U;
  uint8_t attr_bits_pos = 0U;
  uint8_t normal_mem_attr = 0U;

  ASSERT_DBG_PARAM(IS_MEM_ATTR_IDX(attr_idx));

  attr_reg_idx    = ((uint8_t)attr_idx / CORTEX_ATTR_REG_NUM);
  attr_bits_pos   = (((uint8_t)attr_idx % CORTEX_ATTR_REG_NUM) * CORTEX_ATTR_BITS_NUM);
  normal_mem_attr = (uint8_t)(MPU->MAIR[attr_reg_idx] >> attr_bits_pos);

  /* Check if the normal memory mode is enabled */
  if ((normal_mem_attr & CORTEX_NORMAL_MASK) != 0U)
  {
    mem_attr = (hal_cortex_mpu_normal_mem_cache_attr_t)(uint32_t)((uint32_t)normal_mem_attr & CORTEX_ATTR_OUTER_MASK);
  }
  else
  {
    mem_attr = HAL_CORTEX_MPU_NORMAL_MEM_INVALID;
  }

  return (mem_attr);
}

/**
  * @brief  Set MPU region configuration.
  * @param  region_idx: Specify the region index.
  *         This parameter is an element of \ref hal_cortex_mpu_region_idx_t enumeration.
  * @param  p_config: Pointer to the \ref hal_cortex_mpu_region_config_t structure
  *                   that contains the configuration for the MPU region.
  * @retval HAL_OK            Function succeeded.
  * @retval HAL_INVALID_PARAM Function failed (HAL_INVALID_PARAM).
  */
hal_status_t HAL_CORTEX_MPU_SetConfigRegion(hal_cortex_mpu_region_idx_t region_idx,
                                            const hal_cortex_mpu_region_config_t *p_config)
{
  ASSERT_DBG_PARAM(IS_MPU_REGION(region_idx));

  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_MEM_ATTR_IDX(p_config->attr_idx));
  ASSERT_DBG_PARAM(IS_ACCESS_ATTR(p_config->access_attr));
  ASSERT_DBG_PARAM(IS_EXEC_ATTR(p_config->exec_attr));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)

  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ARM_MPU_SetRegion((uint32_t)region_idx, (((uint32_t)p_config->base_addr & CORTEX_REGION_ADDR_MASK)
                                           | ((uint32_t)p_config->access_attr << MPU_RBAR_AP_Pos)
                                           | ((uint32_t)p_config->exec_attr   << MPU_RBAR_XN_Pos)),
                    (((uint32_t)p_config->limit_addr & CORTEX_REGION_ADDR_MASK)
                     | ((uint32_t)p_config->attr_idx << MPU_RLAR_AttrIndx_Pos)));

  return HAL_OK;
}

/**
  * @brief  Get MPU region config.
  * @param  region_idx: Specify the region index.
  *         This parameter is an element of \ref hal_cortex_mpu_region_idx_t enumeration.
  * @param  p_config: Pointer to the \ref hal_cortex_mpu_region_config_t structure
  *                   that contains the configuration for the MPU region.
  */
void HAL_CORTEX_MPU_GetConfigRegion(hal_cortex_mpu_region_idx_t region_idx,
                                    hal_cortex_mpu_region_config_t *p_config)
{
  ASSERT_DBG_PARAM(IS_MPU_REGION(region_idx));
  ASSERT_DBG_PARAM(p_config != NULL);

  WRITE_REG(MPU->RNR, (uint32_t)region_idx);
  p_config->base_addr   = _FLD2VAL(MPU_RBAR_BASE, MPU->RBAR) << MPU_RBAR_BASE_Pos;
  p_config->access_attr = (hal_cortex_mpu_region_access_attr_t)_FLD2VAL(MPU_RBAR_AP, MPU->RBAR);
  p_config->exec_attr   = (hal_cortex_mpu_execution_attr_t)(uint32_t)READ_BIT(MPU->RBAR, MPU_RBAR_XN_Msk);
  p_config->limit_addr  = (_FLD2VAL(MPU_RLAR_LIMIT, MPU->RLAR) << MPU_RLAR_LIMIT_Pos) + 0x1FUL;
  p_config->attr_idx    = (hal_cortex_mpu_mem_attr_idx_t) _FLD2VAL(MPU_RLAR_AttrIndx, MPU->RLAR);
}

/**
  * @brief  Enable the given MPU region.
  * @param  region_idx: Specify the region index.
  *         This parameter is an element of \ref hal_cortex_mpu_region_idx_t enumeration.
  */
void HAL_CORTEX_MPU_EnableRegion(hal_cortex_mpu_region_idx_t region_idx)
{
  ASSERT_DBG_PARAM(IS_MPU_REGION(region_idx));

  WRITE_REG(MPU->RNR, (uint32_t)region_idx);

  SET_BIT(MPU->RLAR, MPU_RLAR_EN_Msk);
}

/**
  * @brief  Disable the given MPU region.
  * @param  region_idx: Specify the region index
  *         This parameter is an element of \ref hal_cortex_mpu_region_idx_t enumeration.
  */
void HAL_CORTEX_MPU_DisableRegion(hal_cortex_mpu_region_idx_t region_idx)
{
  ASSERT_DBG_PARAM(IS_MPU_REGION(region_idx));

  WRITE_REG(MPU->RNR, (uint32_t)region_idx);

  CLEAR_BIT(MPU->RLAR, MPU_RLAR_EN_Msk);
}

/**
  * @brief  Check the given MPU region is enabled or not.
  * @param  region_idx: Specify the region index.
  *         This parameter is an element of \ref hal_cortex_mpu_region_idx_t enumeration.
  * @retval hal_cortex_mpu_region_status_t MPU region status value.
  */
hal_cortex_mpu_region_status_t HAL_CORTEX_MPU_IsEnabledRegion(hal_cortex_mpu_region_idx_t region_idx)
{
  ASSERT_DBG_PARAM(IS_MPU_REGION(region_idx));

  WRITE_REG(MPU->RNR, (uint32_t)region_idx);

  return ((READ_BIT(MPU->RLAR, MPU_RLAR_EN_Msk) == MPU_RLAR_EN_Msk)
          ? HAL_CORTEX_MPU_REGION_ENABLED : HAL_CORTEX_MPU_REGION_DISABLED);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Enable MPU non-secure and set the control mode of the MPU during hard fault,
  *         NMI, FAULTMASK and privileged access to the default memory.
  * @param  fault_state: configure the control mode during hard fault ,NMI and faultmask.
  *         This parameter is an element of \ref hal_cortex_mpu_hardfault_nmi_state_t enumeration.
  * @param  priv_default_state: configure the privileged access to the default memory.
  *         This parameter is an element of \ref hal_cortex_mpu_unmapped_addr_fault_t enumeration.
  * @note   This function behaves same as HAL_CORTEX_MPU_Enable() except that it is intended to called in
  *         secure code to enable non-secure MPU instance.
  */
void HAL_CORTEX_MPUNS_Enable(hal_cortex_mpu_hardfault_nmi_state_t fault_state,
                             hal_cortex_mpu_unmapped_addr_fault_t priv_default_state)
{
  ASSERT_DBG_PARAM(IS_NMI_STATE(fault_state));
  ASSERT_DBG_PARAM(IS_ACCESS_PRIV(priv_default_state));

  ARM_MPU_Enable_NS(((uint32_t)fault_state) | ((uint32_t)priv_default_state));
}

/**
  * @brief  Disable MPU non-secure
  */
void HAL_CORTEX_MPUNS_Disable(void)
{
  ARM_MPU_Disable_NS();
}

/**
  * @brief  Check if non-secure MPU is enabled or not.
  * @retval hal_cortex_mpu_status_t MPU status value.
  * @note   This function behaves same as HAL_CORTEX_MPU_IsEnabled() except that it is intended to called in
  *         secure code to check the non-secure MPU instance is enabled or disabled.
  */
hal_cortex_mpu_status_t HAL_CORTEX_MPUNS_IsEnabled(void)
{
  return ((READ_BIT(MPU_NS->CTRL, MPU_CTRL_ENABLE_Msk) == MPU_CTRL_ENABLE_Msk)
          ? HAL_CORTEX_MPU_ENABLED : HAL_CORTEX_MPU_DISABLED);
}

/**
  * @brief  Set the non-secure device memory attributes config.
  * @param  attr_idx: Specify the attributes index.
  *         This parameter is an element of \ref hal_cortex_mpu_mem_attr_idx_t enumeration.
  * @param  mem_attr: Specify the device.
  *         This parameter is an element of \ref hal_cortex_mpu_device_mem_attr_t enumeration.
  * @note   This function behaves same as HAL_CORTEX_MPU_SetDeviceMemAttr() except that it is intended to called in
  *         secure code to set device memory attribute of the MPU instance.
  */
void HAL_CORTEX_MPUNS_SetDeviceMemAttr(hal_cortex_mpu_mem_attr_idx_t attr_idx,
                                       hal_cortex_mpu_device_mem_attr_t mem_attr)
{
  ASSERT_DBG_PARAM(IS_MEM_ATTR_IDX(attr_idx));
  ASSERT_DBG_PARAM(IS_DEVICE_MEM_ATTR(mem_attr));

  ARM_MPU_SetMemAttr_NS((uint8_t)attr_idx, (uint8_t)mem_attr);
}

/**
  * @brief  Get the non-secure device memory attributes config.
  * @param  attr_idx: Specify the attributes index.
  *         This parameter is an element of \ref hal_cortex_mpu_mem_attr_idx_t enumeration.
  * @retval hal_cortex_mpu_device_mem_attr_t device memory attribute value.
  * @note   This function behaves same as HAL_CORTEX_MPU_GetDeviceMemAttr() except that it is intended to called in
  *         secure code to get the device memory attribute of the non-secure MPU instance.
  */
hal_cortex_mpu_device_mem_attr_t HAL_CORTEX_MPUNS_GetDeviceMemAttr(hal_cortex_mpu_mem_attr_idx_t attr_idx)
{
  hal_cortex_mpu_device_mem_attr_t mem_attr;
  uint8_t attr_reg_idx = 0U;
  uint8_t attr_bits_pos = 0U;
  uint8_t dev_attr = 0U;

  ASSERT_DBG_PARAM(IS_MEM_ATTR_IDX(attr_idx));

  attr_reg_idx     = (uint8_t)attr_idx / CORTEX_ATTR_REG_NUM;
  attr_bits_pos    = (((uint8_t)attr_idx % CORTEX_ATTR_REG_NUM) * CORTEX_ATTR_BITS_NUM);
  dev_attr         = (uint8_t)(MPU_NS->MAIR[attr_reg_idx] >> attr_bits_pos);

  /* Check if memory is configured as device */
  if ((dev_attr & (~CORTEX_DEVICE_MASK)) == 0U)
  {
    mem_attr = (hal_cortex_mpu_device_mem_attr_t)(dev_attr);
  }
  else
  {
    mem_attr = HAL_CORTEX_MPU_DEVICE_MEM_INVALID;
  }

  return (mem_attr);
}

/**
  * @brief  Set non-secure cache memory attributes config.
  * @param  attr_idx: Specify the attributes index.
  *         This parameter is an element of \ref hal_cortex_mpu_mem_attr_idx_t  enumeration.
  * @param  mem_attr: Specify the cache memory config.
  *         This parameter is an element of \ref hal_cortex_mpu_normal_mem_cache_attr_t enumeration.
  * @note   This function behaves same as HAL_CORTEX_MPU_SetCacheMemAttr() except that it is intended to called in
  *         secure code to set the cache memory of the non-secure MPU instance.
  */
void HAL_CORTEX_MPUNS_SetCacheMemAttr(hal_cortex_mpu_mem_attr_idx_t attr_idx,
                                      hal_cortex_mpu_normal_mem_cache_attr_t mem_attr)
{
  ASSERT_DBG_PARAM(IS_MEM_ATTR_IDX(attr_idx));
  ASSERT_DBG_PARAM(IS_NORMAL_MEM_ATTR(mem_attr));

  ARM_MPU_SetMemAttr_NS((uint8_t)attr_idx, (CORTEX_ATTR_INNER_MASK | (uint8_t)mem_attr));
}

/**
  * @brief  Get the non-secure cache memory attributes config.
  * @param  attr_idx: Specify the attributes index.
  *         This parameter is an element of \ref hal_cortex_mpu_mem_attr_idx_t enumeration.
  * @retval hal_cortex_mpu_normal_mem_cache_attr_t normal memory attribute value.
  * @note   This function behaves same as HAL_CORTEX_MPU_GetCacheMemAttr() except that it is intended to called in
  *         secure code to get the cache memory attribute of the non-secure MPU instance.
  */
hal_cortex_mpu_normal_mem_cache_attr_t HAL_CORTEX_MPUNS_GetCacheMemAttr(hal_cortex_mpu_mem_attr_idx_t attr_idx)
{
  hal_cortex_mpu_normal_mem_cache_attr_t mem_attr;
  uint8_t attr_reg_idx = 0U;
  uint8_t attr_bits_pos = 0U;
  uint8_t normal_mem_attr = 0U;

  ASSERT_DBG_PARAM(IS_MEM_ATTR_IDX(attr_idx));

  attr_reg_idx    = ((uint8_t)attr_idx / CORTEX_ATTR_REG_NUM);
  attr_bits_pos   = (((uint8_t)attr_idx % CORTEX_ATTR_REG_NUM) * CORTEX_ATTR_BITS_NUM);
  normal_mem_attr = (uint8_t)(MPU_NS->MAIR[attr_reg_idx] >> attr_bits_pos);

  if ((normal_mem_attr & CORTEX_NORMAL_MASK) != 0U)
  {
    mem_attr = (hal_cortex_mpu_normal_mem_cache_attr_t)(uint32_t)((uint32_t)normal_mem_attr & CORTEX_ATTR_OUTER_MASK);
  }
  else
  {
    mem_attr = HAL_CORTEX_MPU_NORMAL_MEM_INVALID;
  }

  return (mem_attr);
}

/**
  * @brief  Set non-secure MPU region config.
  * @param  region_idx: Specify the region index.
  *         This parameter is an element of \ref hal_cortex_mpu_region_idx_t enumeration.
  * @param  p_config: Pointer to the hal_cortex_mpu_region_config_t structure.
  *         This parameter is an element of \ref hal_cortex_mpu_region_config_t structure.
  * @retval HAL_OK             Function succeeded.
  * @retval HAL_INVALID_PARAM  Function failed.
  * @note   This function behaves same as HAL_CORTEX_MPU_SetConfigRegion() except that it is intended to called in
  *         secure code to configure region of the non-secure MPU instance.
  */
hal_status_t HAL_CORTEX_MPUNS_SetConfigRegion(hal_cortex_mpu_region_idx_t region_idx,
                                              const hal_cortex_mpu_region_config_t *p_config)
{
  ASSERT_DBG_PARAM(IS_MPU_REGION(region_idx));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(IS_MEM_ATTR_IDX(p_config->attr_idx));
  ASSERT_DBG_PARAM(IS_ACCESS_ATTR(p_config->access_attr));
  ASSERT_DBG_PARAM(IS_EXEC_ATTR(p_config->exec_attr));
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)

  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ARM_MPU_SetRegion_NS((uint32_t)region_idx, (((uint32_t)p_config->base_addr & CORTEX_REGION_ADDR_MASK)
                                              | ((uint32_t)p_config->access_attr << MPU_RBAR_AP_Pos)
                                              | ((uint32_t)p_config->exec_attr   << MPU_RBAR_XN_Pos)),
                       (((uint32_t)p_config->limit_addr & CORTEX_REGION_ADDR_MASK)
                        | ((uint32_t)p_config->attr_idx << MPU_RLAR_AttrIndx_Pos)));

  return (HAL_OK);
}

/**
  * @brief  Get non-secure MPU region config.
  * @param  region_idx: Specify the region index.
  *         This parameter is an element of \ref hal_cortex_mpu_region_idx_t enumeration.
  * @param  p_config: Pointer to the hal_cortex_mpu_region_config_t structure.
  *         This parameter can be a value of \ref hal_cortex_mpu_region_config_t structure.
  * @note   This function behaves same as HAL_CORTEX_MPU_GetConfigRegion() except that it is intended to called in
  *         secure code to get region configuration of the non-secure MPU instance.
  */
void HAL_CORTEX_MPUNS_GetConfigRegion(hal_cortex_mpu_region_idx_t region_idx,
                                      hal_cortex_mpu_region_config_t *p_config)
{
  ASSERT_DBG_PARAM(IS_MPU_REGION(region_idx));
  ASSERT_DBG_PARAM(p_config != NULL);

  MPU_NS->RNR = (uint32_t)region_idx;
  p_config->base_addr   = _FLD2VAL(MPU_RBAR_BASE, MPU_NS->RBAR) << MPU_RBAR_BASE_Pos;
  p_config->access_attr = (hal_cortex_mpu_region_access_attr_t)_FLD2VAL(MPU_RBAR_AP, MPU_NS->RBAR);
  p_config->exec_attr   = (hal_cortex_mpu_execution_attr_t)(uint32_t)READ_BIT(MPU_NS->RBAR, MPU_RBAR_XN_Msk);
  p_config->limit_addr  = (_FLD2VAL(MPU_RLAR_LIMIT, MPU_NS->RLAR) << MPU_RLAR_LIMIT_Pos) + 0x1FUL;
  p_config->attr_idx    = (hal_cortex_mpu_mem_attr_idx_t) _FLD2VAL(MPU_RLAR_AttrIndx, MPU_NS->RLAR);

}

/**
  * @brief  Enable the non-secure given MPU region.
  * @param  region_idx: Specify the region index.
  *         This parameter is an element of \ref hal_cortex_mpu_region_idx_t enumeration.
  * @note   This function behaves same as HAL_CORTEX_MPU_EnableRegion() except that it is intended to called in
  *         secure code to enable region of the non-secure MPU instance.
  */
void HAL_CORTEX_MPUNS_EnableRegion(hal_cortex_mpu_region_idx_t region_idx)
{
  ASSERT_DBG_PARAM(IS_MPU_REGION(region_idx));

  WRITE_REG(MPU_NS->RNR, (uint32_t)region_idx);

  SET_BIT(MPU_NS->RLAR, MPU_RLAR_EN_Msk);
}

/**
  * @brief  Disable the non-secure given MPU region.
  * @param  region_idx: Specify the region index
  *         This parameter is an element of \ref hal_cortex_mpu_region_idx_t enumeration.
  * @note   This function behaves same as HAL_CORTEX_MPU_DisableRegion() except that it is intended to called in
  *         secure code to disable region of the non-secure MPU instance.
  */
void HAL_CORTEX_MPUNS_DisableRegion(hal_cortex_mpu_region_idx_t region_idx)
{
  ASSERT_DBG_PARAM(IS_MPU_REGION(region_idx));

  WRITE_REG(MPU_NS->RNR, (uint32_t)region_idx);

  CLEAR_BIT(MPU_NS->RLAR, MPU_RLAR_EN_Msk);
}

/**
  * @brief  Check the given MPU_NS region is enabled or not.
  * @param  region_idx: Specify the region index.
  *         This parameter is an element of \ref hal_cortex_mpu_region_idx_t enumeration.
  * @retval hal_cortex_mpu_region_status_t MPU region status value.
  * @note   This function behaves same as HAL_CORTEX_MPU_IsEnabledRegion() except that it is intended to called in
  *         secure code to check region of the non-secure MPU instance is enabled or disabled.
  */
hal_cortex_mpu_region_status_t HAL_CORTEX_MPUNS_IsEnabledRegion(hal_cortex_mpu_region_idx_t region_idx)
{
  ASSERT_DBG_PARAM(IS_MPU_REGION(region_idx));

  WRITE_REG(MPU_NS->RNR, (uint32_t)region_idx);

  return ((READ_BIT(MPU_NS->RLAR, MPU_RLAR_EN_Msk) == MPU_RLAR_EN_Msk)
          ? HAL_CORTEX_MPU_REGION_ENABLED : HAL_CORTEX_MPU_REGION_DISABLED);

}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @}
  */

/** @addtogroup CORTEX_Exported_Functions_Group4
  *  @{
- This subsection provides a set of functions allowing to configure cortex SCB block features.
  - Use HAL_CORTEX_SCB_GetInfo() to get the CPU ID information.
  - Use HAL_CORTEX_SCB_DisableHardFaultEscalation() to enable an exception fault escalation.
  - Use HAL_CORTEX_SCB_EnableHardFaultEscalation() to disable an exception fault escalation.
  - Use HAL_CORTEX_SCBNS_DisableHardFaultEscalation() and Use HAL_CORTEX_SCBNS_EnableHardFaultEscalation()
    to manage SCB non-secure instance by a secure software.
 */

/**
  * @brief  Get CPU ID information.
  * @param  p_info: Get the hal_cortex_mpu_region_config_t structure.
  *         This parameter is an element of \ref hal_cortex_scb_cpuid_info_t structure.
  */
void HAL_CORTEX_SCB_GetInfo(hal_cortex_scb_cpuid_info_t *p_info)
{
  ASSERT_DBG_PARAM(p_info != NULL);

  p_info->revision    = _FLD2VAL(SCB_CPUID_REVISION, SCB->CPUID);
  p_info->part_number = _FLD2VAL(SCB_CPUID_PARTNO, SCB->CPUID);
  p_info->variant     = _FLD2VAL(SCB_CPUID_VARIANT, SCB->CPUID);
  p_info->implementer = _FLD2VAL(SCB_CPUID_IMPLEMENTER, SCB->CPUID);
}

/**
  * @brief  Enable a fault.
  * @param  faults This parameter can be a combination of the following values:
  *         @arg @ref HAL_CORTEX_SCB_USAGE_FAULT           Usage fault
  *         @arg @ref HAL_CORTEX_SCB_BUS_FAULT             Bus fault
  *         @arg @ref HAL_CORTEX_SCB_MEM_MANAGEMENT_FAULT  Memory management fault
  *         @arg @ref HAL_CORTEX_SCB_SECURE_FAULT          Secure fault
  */
void HAL_CORTEX_SCB_EnableHardFaultEscalation(uint32_t faults)
{
  ASSERT_DBG_PARAM(IS_FAULT_EXCEPT(faults));

  ATOMIC_SET_BIT(SCB->SHCSR, faults);
}

/**
  * @brief  Disable a fault, escalation to hardfault.
  * @param  faults This parameter can be a combination of the following values:
  *         @arg @ref HAL_CORTEX_SCB_USAGE_FAULT           Usage fault
  *         @arg @ref HAL_CORTEX_SCB_BUS_FAULT             Bus fault
  *         @arg @ref HAL_CORTEX_SCB_MEM_MANAGEMENT_FAULT  Memory management fault
  *         @arg @ref HAL_CORTEX_SCB_SECURE_FAULT          Secure fault
  */
void HAL_CORTEX_SCB_DisableHardFaultEscalation(uint32_t faults)
{
  ASSERT_DBG_PARAM(IS_FAULT_EXCEPT(faults));

  ATOMIC_CLEAR_BIT(SCB->SHCSR, faults);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Enable a fault.
  * @param  faults This parameter can be a combination of the following values:
  *         @arg @ref HAL_CORTEX_SCB_USAGE_FAULT           Usage fault
  *         @arg @ref HAL_CORTEX_SCB_MEM_MANAGEMENT_FAULT  Memory management fault
  */
void HAL_CORTEX_SCBNS_EnableHardFaultEscalation(uint32_t faults)
{
  ASSERT_DBG_PARAM((faults & ~(HAL_CORTEX_SCB_USAGE_FAULT | HAL_CORTEX_SCB_MEM_MANAGEMENT_FAULT)) == 0U);

  ATOMIC_SET_BIT(SCB_NS->SHCSR, faults);
}

/**
  * @brief  Disable a fault, escalation to hardfault.
  * @param  faults This parameter can be a combination of the following values:
  *         @arg @ref HAL_CORTEX_SCB_USAGE_FAULT           Usage fault
  *         @arg @ref HAL_CORTEX_SCB_MEM_MANAGEMENT_FAULT  Memory management fault
  */
void HAL_CORTEX_SCBNS_DisableHardFaultEscalation(uint32_t faults)
{
  ASSERT_DBG_PARAM((faults & ~(HAL_CORTEX_SCB_USAGE_FAULT | HAL_CORTEX_SCB_MEM_MANAGEMENT_FAULT)) == 0U);

  ATOMIC_CLEAR_BIT(SCB_NS->SHCSR, faults);
}
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/**
  * @}
  */
#endif /* USE_HAL_CORTEX_MODULE */
/**
  * @}
  */

/**
  * @}
  */
