/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_gtzc.c
  * @brief   GTZC HAL module driver.
  **********************************************************************************************************************
    * @attention
  *
  * Copyright (c) 2021-2025 STMicroelectronics.
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

/** @addtogroup GTZC
  * @{
This file provides firmware functions to manage the following functionalities of GTZC peripheral:

- Configure securable peripherals security and privilege attributes
- Lock the security and privilege attributes configurations of securable peripherals
- Configure memory subregion watermark security and privilege attributes
- Enable/Disable memory subregion watermark
- Lock the configurations of memory subregion watermark
- Configure block based memories security and privilege attributes
- Configure the clock security state of block based memories
- Configure the secure access state of block based memories
- Lock the configurations of block based memories
- Enable/Disable the illegal access interrupt of peripherals
- Treat the illegal access interrupt

# GTZC main features

Global TrustZone Controller (GTZC) composed of three sub-blocks:

1. TZSC: TrustZone security controller
This sub-block defines the secure/privileged state of master and slave peripherals. It also controls the
secure/privileged state of subregions for the watermark memory peripheral controller (MPCWM).

2. MPCBB: Block-Based memory protection controller
This sub-block defines the secure/privileged state of all blocks (block = 512-byte page) of the associated SRAM.

3. TZIC: TrustZone illegal access controller
This sub-block gathers all illegal access events in the system and generates a secure interrupt towards NVIC.

These sub-blocks are used to configure TrustZone system security in a product having bus agents with
programmable-security and privileged attributes (securable) such as:
- on-chip RAM with programmable secure and/or privilege blocks (pages)
- AHB and APB peripherals with programmable security and/or privilege access
- off-chip memories with secure and/or privilege areas

TZIC is accessible only with secure privileged transactions.\n
Secure and non-secure accesses are supported for privileged and unprivileged settings of TZSC and MPCBB.\n

# GTZC clock configuration
 - GTZC1 : clocked by AHB1 bus clock
 - GTZC2 : clocked by AHB3 bus clock

# How to use the GTZC HAL module driver

## The GTZC HAL driver can be used as follows:

1. Enable the GTZC low level resources using the functions HAL_RCC_GTZC1_EnableClock() for GTZC1 instance and
HAL_RCC_GTZC2_EnableClock() for GTZC2 instance

2. Declare a hal_gtzc_attr_config_t security attributes configuration structure:
  hal_gtzc_attr_config_t p_attr;

3. Set the security and privilege attributes of securable peripherals using:
  HAL_GTZC_SetPeriphAttr();

4. Get the security and privilege attributes of securable peripherals using:
  HAL_GTZC_GetPeriphAttr();

5. Lock the security and privilege attributes configurations of securable peripherals using:
  HAL_GTZC_LockPeriphAttr();

6. Retrieve the lock state of security and privilege attributes configurations of securable peripherals using:
  HAL_GTZC_IsPeriphAttrLocked();

7. Set the security and privilege attributes configurations of memory subregion watermark using:
  HAL_GTZC_WATERMARK_SetConfigMemSubRegionAttr();

8. Get the security and privilege attributes configurations of memory subregion watermark using:
  HAL_GTZC_WATERMARK_GetMemAreaAttr();

9. Get the security and privilege attributes configurations of all watermark memories area using:
  HAL_GTZC_WATERMARK_GetMemMapAttr();

10. Enable memory subregion watermark using:
  HAL_GTZC_WATERMARK_EnableMemSubRegionAttr();

11. Disable memory subregion watermark using:
  HAL_GTZC_WATERMARK_DisableMemSubRegionAttr();

12. Check if memory subregion watermark is enabled or disabled using:
  HAL_GTZC_WATERMARK_IsEnabledMemSubRegionAttr();

13. Lock the configurations of memory subregion watermark using:
  HAL_GTZC_WATERMARK_LockMemSubRegionConfig();

14. Check if memory subregion watermark configurations is locked or unlocked using:
  HAL_GTZC_WATERMARK_IsMemSubRegionConfigLocked();

15. Set the security and privilege attributes of block based memories by block entity using:
  HAL_GTZC_BLOCKBASED_SetMemBlockAttr();

16. Get the security and privilege attributes of block based memories by block entity using:
  HAL_GTZC_BLOCKBASED_GetMemBlockAttr();

17. Set the security and privilege attributes of block based memories by address entity using:
  HAL_GTZC_BLOCKBASED_SetMemAddrAttr();

18. Get the security and privilege attributes of block based memories by address entity using:
  HAL_GTZC_BLOCKBASED_GetMemAddrAttr();

19. Set the clock security state of block based memories using:
  HAL_GTZC_BLOCKBASED_SetMemClkSecStateInvertion();

20. Get the clock security state of block based memories using:
  HAL_GTZC_BLOCKBASED_GetMemClkSecStateInvertion();

21. Set the secure access state of block based memories using:
  HAL_GTZC_BLOCKBASED_SetMemSecAccessState();

22. Get the secure access state of block based memories using:
  HAL_GTZC_BLOCKBASED_GetMemSecAccessState();

23. Lock the security and privilege attributes configurations of block based memories by super block entity using:
  HAL_GTZC_BLOCKBASED_LockMemSuperBlockAttr();

24. Check if the security and privilege attributes configurations of block based memories is locked or unlocked by
super block entity using:
  HAL_GTZC_BLOCKBASED_IsMemSuperBlockAttrLocked();

25. Lock the security and privilege attributes configurations of block based memories by address entity using:
  HAL_GTZC_BLOCKBASED_LockMemAttr();

26. Check if the security and privilege attributes configurations of block based memories is locked or unlocked by
address entity using:
  HAL_GTZC_BLOCKBASED_IsMemAttrLocked();

27. Lock the block based memories configurations using:
  HAL_GTZC_BLOCKBASED_LockMemConfig();

28. Check if the block based memories configurations is locked or unlocked using:
  HAL_GTZC_BLOCKBASED_IsMemConfigLocked();

29. Activate the illegal access interrupt of peripherals using:
  HAL_GTZC_ILLEGALACCESS_EnableIT();

30. Deactivate the illegal access interrupt of peripherals using:
  HAL_GTZC_ILLEGALACCESS_DisableIT();

31. Check if the illegal access interrupt of peripheral is enabled or disabled using:
  HAL_GTZC_ILLEGALACCESS_IsEnabledIT();

32. Illegal access interrupt service routines are served by:
  HAL_GTZC_ILLEGALACCESS_IRQHandler();

33. User can add his own code using:
  HAL_GTZC_ILLEGALACCESS_Callback();

## Configuration inside the GTZC driver

Config defines      | Description        | Default value | Note
--------------------| ---------------    | ------------- | ----
PRODUCT             | from IDE           | NA            | The selected product (ex STM32U585xx)
USE_HAL_GTZC_MODULE | from hal_conf.h    | 1             | When set, HAL GTZC module is enabled
USE_ASSERT_DBG_PARAM| from IDE           | NA            | When defined, enable the params assert
USE_HAL_CHECK_PARAM | from hal_conf.h    | 0             | When set, parameters are checked in runtime
__ARM_FEATURE_CMSE  | from IDE           | NA            | When TrustZone active and the application in secure mode
  */

#if defined(USE_HAL_GTZC_MODULE) && (USE_HAL_GTZC_MODULE == 1U)

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/*! GTZC Watermark subregion overlap status */
typedef enum
{
  HAL_GTZC_WATERMARK_SUBREGIONS_OVERLAPPED     = 0U, /*!< GTZC watermark subregion A and B overlapped     */
  HAL_GTZC_WATERMARK_SUBREGIONS_NOT_OVERLAPPED = 1U  /*!< GTZC watermark subregion A and B not overlapped */
} hal_gtzc_watermark_subregion_overlap_status_t;

/*! GTZC Watermark area information */
typedef struct
{
  uint32_t                  start_overlap;          /*!< Start address of overlap subregion A and B         */

  uint32_t                  end_overlap;            /*!< End address of overlap subregion A and B           */

  uint32_t                  start_subregion_a;      /*!< Start address of subregion A                       */

  uint32_t                  end_subregion_a;        /*!< End address of subregion A                         */

  uint32_t                  sec_state_subregion_a;  /*!< Secure attribute state of subregion A              */

  uint32_t                  priv_state_subregion_a; /*!< Privilege attribute state of subregion A           */

  uint32_t                  start_subregion_b;      /*!< Start address of subregion B                       */

  uint32_t                  end_subregion_b;        /*!< End address of subregion B                         */

  uint32_t                  sec_state_subregion_b;  /*!< Secure attribute state of subregion B              */

  uint32_t                  priv_state_subregion_b; /*!< Privilege attribute state of subregion B           */

  uint32_t                  offset_byte;            /*!< Offset address in byte of watermark memory area   */

  uint32_t                  size_byte;              /*!< Size in byte of watermark memory area              */

  uint32_t                  granularity;            /*!< Granularity of watermark memory                    */

  hal_gtzc_security_attr_t  sec_state;              /*!< Secure attribute state of watermark memory area    */

  hal_gtzc_privilege_attr_t priv_state;             /*!< Privilege attribute state of watermark memory area */

} hal_gtzc_watermark_area_info_t;

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_Private_Constants GTZC Private Constants
  * @{
  */
#define GTZC_REG_MAX_FIELD         32U                                          /*!< GTZC maximum register field      */
#define GTZC_MPCWM_GRANULARITY_1   0x00000020U                                  /*!< BKPSRAM granularity: 32B         */
#define GTZC_MPCWM_GRANULARITY_2   0x00020000U                                  /*!< OCTOSPI & FMC & HSPI granularity:
                                                                                     128KB                            */
#define GTZC_MPCWM_RANGE_1         0x00000800U                                  /*!< 2KB max range                    */
#define GTZC_MPCWM_RANGE_2         0x10000000U                                  /*!< 256MB max range                  */
#define GTZC_MPCBB_BLOCK_SIZE      0x00000200U                                  /*!< MPCBB Block size: 512B           */
#define GTZC_MPCBB_SUPERBLOCK_SIZE (GTZC_MPCBB_BLOCK_SIZE * GTZC_REG_MAX_FIELD) /*!< MPCBB super-block size: 16KB     */
/**
  * @}
  */
/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_Private_Macros GTZC Private Constants
  * @{
  */

/*! Macro to check all peripherals */
#define IS_GTZC_PERIPH_ALL(periph) ((periph) == (uint32_t)HAL_GTZC_PERIPH_ALL)

/*! Macro to check the GTZC1 peripherals in the register 1 */
#define IS_GTZC1_PERIPH_REG1(periph) (((0x1UL << ((periph) % GTZC_REG_MAX_FIELD)) & LL_GTZC1_GRP1_ALL) == \
                                      (0x1UL << ((periph) % GTZC_REG_MAX_FIELD)))

/*! Macro to check the GTZC1 peripherals in the register 2 */
#define IS_GTZC1_PERIPH_REG2(periph) (((0x1UL << ((periph) % GTZC_REG_MAX_FIELD)) & LL_GTZC1_GRP2_ALL) == \
                                      (0x1UL << ((periph) % GTZC_REG_MAX_FIELD)))

/*! Macro to check the GTZC1 peripherals in the register 3 */
#define IS_GTZC1_PERIPH_REG3(periph) (((0x1UL << ((periph) % GTZC_REG_MAX_FIELD)) & LL_GTZC1_GRP3_ALL) == \
                                      (0x1UL << ((periph) % GTZC_REG_MAX_FIELD)))

/*! Macro to check the GTZC1 peripherals in the register 4 */
#define IS_GTZC1_PERIPH_REG4(periph) (((0x1UL << ((periph) % GTZC_REG_MAX_FIELD)) & LL_GTZC1_GRP4_ALL) == \
                                      (0x1UL << ((periph) % GTZC_REG_MAX_FIELD)))

/*! Macro to check the GTZC2 peripherals in the register 1 */
#define IS_GTZC2_PERIPH_REG1(periph) (((0x1UL << (((periph) - AHB3PERIPH_BASE_NS) % GTZC_REG_MAX_FIELD)) & \
                                       LL_GTZC2_GRP1_ALL) ==                                               \
                                      (0x1UL << (((periph) - AHB3PERIPH_BASE_NS) % GTZC_REG_MAX_FIELD)))

/*! Macro to check the GTZC2 peripherals in the register 2 */
#define IS_GTZC2_PERIPH_REG2(periph) (((0x1UL << (((periph) - AHB3PERIPH_BASE_NS) % GTZC_REG_MAX_FIELD)) & \
                                       LL_GTZC2_GRP2_ALL) ==                                                \
                                      (0x1UL << (((periph) - AHB3PERIPH_BASE_NS) % GTZC_REG_MAX_FIELD)))

/*! Macro to check securable peripherals */
#define IS_GTZC_SECURABLE_PERIPHERALS(periph) (((periph) < LL_GTZC1_PERIPH_REG2) ? IS_GTZC1_PERIPH_REG1(periph) : \
                                               (((periph) < LL_GTZC1_PERIPH_REG3) ? IS_GTZC1_PERIPH_REG2(periph) : \
                                                (((periph) < LL_GTZC1_PERIPH_REG4) ? IS_GTZC1_PERIPH_REG3(periph) : \
                                                 (((periph) < LL_GTZC2_PERIPH_REG1) ? (0U == 1U) : \
                                                  (((periph) < LL_GTZC2_PERIPH_REG2) ? IS_GTZC2_PERIPH_REG1(periph) : \
                                                   (0U == 1U))))))

/*! Macro to check illegal access peripherals */
#define IS_ILLEGAL_ACCESS_PERIPHERAL(periph) (IS_GTZC_PERIPH_ALL(periph) ? (1U == 1U) : \
                                              (((periph) < LL_GTZC1_PERIPH_REG2) ? IS_GTZC1_PERIPH_REG1(periph) : \
                                               (((periph) < LL_GTZC1_PERIPH_REG3) ? IS_GTZC1_PERIPH_REG2(periph) : \
                                                (((periph) < LL_GTZC1_PERIPH_REG4) ? IS_GTZC1_PERIPH_REG3(periph) : \
                                                 (((periph) < LL_GTZC2_PERIPH_REG1) ? IS_GTZC1_PERIPH_REG4(periph) : \
                                                  (((periph) < LL_GTZC2_PERIPH_REG2) ? IS_GTZC2_PERIPH_REG1(periph) : \
                                                   IS_GTZC2_PERIPH_REG2(periph)))))))

/*! Macro to check the lock peripherals */
#define IS_GTZC_LOCK_PERIPHERALS(periphs) (((periphs) == HAL_GTZC1_PERIPH_ALL) || ((periphs) == HAL_GTZC2_PERIPH_ALL))

/*! Macro to check the watermark memory */
#if defined (HSPI1)
#define IS_GTZC_WATERMARK_MEM(mem) (((mem) == HAL_GTZC_WATERMARK_OCTOSPI1)    \
                                    || ((mem) == HAL_GTZC_WATERMARK_FMC_NOR)  \
                                    || ((mem) == HAL_GTZC_WATERMARK_FMC_NAND) \
                                    || ((mem) == HAL_GTZC_WATERMARK_BKPSRAM)  \
                                    || ((mem) == HAL_GTZC_WATERMARK_OCTOSPI2) \
                                    || ((mem) == HAL_GTZC_WATERMARK_HSPI1))
#elif defined(FMC_BASE)
#define IS_GTZC_WATERMARK_MEM(mem) (((mem) == HAL_GTZC_WATERMARK_OCTOSPI1) || \
                                    ((mem) == HAL_GTZC_WATERMARK_FMC_NOR)  || \
                                    ((mem) == HAL_GTZC_WATERMARK_FMC_NAND) || \
                                    ((mem) == HAL_GTZC_WATERMARK_BKPSRAM)  || \
                                    ((mem) == HAL_GTZC_WATERMARK_OCTOSPI2))
#else
#define IS_GTZC_WATERMARK_MEM(mem) (((mem) == HAL_GTZC_WATERMARK_OCTOSPI1) || ((mem) == HAL_GTZC_WATERMARK_BKPSRAM))
#endif /* HSPI1 */

/*! Macro to check the watermark subregion */
#define IS_GTZC_WATERMARK_SUBREGION(subregion) (((subregion) == HAL_GTZC_WATERMARK_SUBREGION_A) || \
                                                ((subregion) == HAL_GTZC_WATERMARK_SUBREGION_B))

/*! Macro to check the blockbased memory */
#if defined (SRAM6_BASE)
#define IS_GTZC_BLOCKBASED_MEM(mem) (((mem) == HAL_GTZC_BLOCKBASED_SRAM1) || \
                                     ((mem) == HAL_GTZC_BLOCKBASED_SRAM2) || \
                                     ((mem) == HAL_GTZC_BLOCKBASED_SRAM3) || \
                                     ((mem) == HAL_GTZC_BLOCKBASED_SRAM4) || \
                                     ((mem) == HAL_GTZC_BLOCKBASED_SRAM5) || \
                                     ((mem) == HAL_GTZC_BLOCKBASED_SRAM6))
#elif defined (SRAM5_BASE)
#define IS_GTZC_BLOCKBASED_MEM(mem) (((mem) == HAL_GTZC_BLOCKBASED_SRAM1) || \
                                     ((mem) == HAL_GTZC_BLOCKBASED_SRAM2) || \
                                     ((mem) == HAL_GTZC_BLOCKBASED_SRAM3) || \
                                     ((mem) == HAL_GTZC_BLOCKBASED_SRAM4) || \
                                     ((mem) == HAL_GTZC_BLOCKBASED_SRAM5))
#elif defined (SRAM3_BASE)
#define IS_GTZC_BLOCKBASED_MEM(mem) (((mem) == HAL_GTZC_BLOCKBASED_SRAM1) || \
                                     ((mem) == HAL_GTZC_BLOCKBASED_SRAM2) || \
                                     ((mem) == HAL_GTZC_BLOCKBASED_SRAM3) || \
                                     ((mem) == HAL_GTZC_BLOCKBASED_SRAM4))
#else
#define IS_GTZC_BLOCKBASED_MEM(mem) (((mem) == HAL_GTZC_BLOCKBASED_SRAM1) || \
                                     ((mem) == HAL_GTZC_BLOCKBASED_SRAM2) || \
                                     ((mem) == HAL_GTZC_BLOCKBASED_SRAM4))
#endif /* SRAM6_BASE */

/*! Macro to check the blockbased memory clock security state */
#define IS_GTZC_BLOCKBASED_MEM_CLK_SEC_STATE(state) (((state) == HAL_GTZC_CLK_SEC_NOT_INVERTED) || \
                                                     ((state) == HAL_GTZC_CLK_SEC_INVERTED))

/*! Macro to check the blockbased memory secure access state */
#define IS_GTZC_BLOCKBASED_MEM_SEC_ACCESS_STATE(state) (((state) == HAL_GTZC_SEC_ACCESS_NOT_ALLOWED) || \
                                                        ((state) == HAL_GTZC_SEC_ACCESS_ALLOWED))


/*! Macro to get watermark memory granularity */
#define GTZC_GET_WATERMARK_MEM_GRANULARITY(mem) \
  (((mem) == HAL_GTZC_WATERMARK_BKPSRAM) ? GTZC_MPCWM_GRANULARITY_1 : GTZC_MPCWM_GRANULARITY_2)

/*! Macro to get watermark memory range */
#define GTZC_GET_WATERMARK_MEM_RANGE(mem) \
  (((mem) == HAL_GTZC_WATERMARK_BKPSRAM) ? GTZC_MPCWM_RANGE_1 : GTZC_MPCWM_RANGE_2)

/*! Macro to check parameters in range of watermark memory */
#define IS_WATERMARK_MEM_IN_RANGE(mem, offset, size) \
  (((mem) == HAL_GTZC_WATERMARK_BKPSRAM) ? (((offset) + (size)) <= GTZC_MPCWM_RANGE_1) : \
   (((offset) + (size)) <= GTZC_MPCWM_RANGE_2))

/*! Macro to check watermark memory granularity */
#define IS_WATERMARK_MEM_GRANULARITY(mem, offset, size) \
  (((mem) == HAL_GTZC_WATERMARK_BKPSRAM) ? \
   ((((offset) % GTZC_MPCWM_GRANULARITY_1) == 0U) && (((size) % GTZC_MPCWM_GRANULARITY_1) == 0U)) : \
   ((((offset) % GTZC_MPCWM_GRANULARITY_2) == 0U) && (((size) % GTZC_MPCWM_GRANULARITY_2) == 0U)))

/*! Macro to watermark memory subregion */
#if defined(FMC_BASE)
#define IS_WATERMARK_MEM_SUBREGION(mem, subregion) \
  ((((mem) == HAL_GTZC_WATERMARK_FMC_NAND) || ((mem) == HAL_GTZC_WATERMARK_BKPSRAM)) ? \
   ((subregion) == HAL_GTZC_WATERMARK_SUBREGION_A) : \
   (((subregion) == HAL_GTZC_WATERMARK_SUBREGION_A) || ((subregion) == HAL_GTZC_WATERMARK_SUBREGION_B)))
#else
#define IS_WATERMARK_MEM_SUBREGION(mem, subregion) \
  (((mem) == HAL_GTZC_WATERMARK_BKPSRAM) ? ((subregion) == HAL_GTZC_WATERMARK_SUBREGION_A) : \
   (((subregion) == HAL_GTZC_WATERMARK_SUBREGION_A) || ((subregion) == HAL_GTZC_WATERMARK_SUBREGION_B)))
#endif /* FMC_BASE */

/*! Macro to check parameters in range of block based memory */
#if defined (SRAM6_BASE)
#define IS_BLOCKBASED_MEM_IN_RANGE(mem, offset, size) \
  (((mem) == HAL_GTZC_BLOCKBASED_SRAM1) ? (((offset) + (size)) <= SRAM1_SIZE) : \
   ((mem) == HAL_GTZC_BLOCKBASED_SRAM2) ? (((offset) + (size)) <= SRAM2_SIZE) : \
   ((mem) == HAL_GTZC_BLOCKBASED_SRAM3) ? (((offset) + (size)) <= SRAM3_SIZE) : \
   ((mem) == HAL_GTZC_BLOCKBASED_SRAM4) ? (((offset) + (size)) <= SRAM4_SIZE) : \
   ((mem) == HAL_GTZC_BLOCKBASED_SRAM5) ? (((offset) + (size)) <= SRAM5_SIZE) : (((offset) + (size)) <= SRAM6_SIZE))
#elif defined (SRAM5_BASE)
#define IS_BLOCKBASED_MEM_IN_RANGE(mem, offset, size) \
  (((mem) == HAL_GTZC_BLOCKBASED_SRAM1) ? (((offset) + (size)) <= SRAM1_SIZE) : \
   ((mem) == HAL_GTZC_BLOCKBASED_SRAM2) ? (((offset) + (size)) <= SRAM2_SIZE) : \
   ((mem) == HAL_GTZC_BLOCKBASED_SRAM3) ? (((offset) + (size)) <= SRAM3_SIZE) : \
   ((mem) == HAL_GTZC_BLOCKBASED_SRAM4) ? (((offset) + (size)) <= SRAM4_SIZE) : (((offset) + (size)) <= SRAM5_SIZE))
#elif defined (SRAM3_BASE)
#define IS_BLOCKBASED_MEM_IN_RANGE(mem, offset, size) \
  (((mem) == HAL_GTZC_BLOCKBASED_SRAM1) ? (((offset) + (size)) <= SRAM1_SIZE) : \
   ((mem) == HAL_GTZC_BLOCKBASED_SRAM2) ? (((offset) + (size)) <= SRAM2_SIZE) : \
   ((mem) == HAL_GTZC_BLOCKBASED_SRAM3) ? (((offset) + (size)) <= SRAM3_SIZE) : (((offset) + (size)) <= SRAM4_SIZE))
#else
#define IS_BLOCKBASED_MEM_IN_RANGE(mem, offset, size) \
  (((mem) == HAL_GTZC_BLOCKBASED_SRAM1) ? (((offset) + (size)) <= SRAM1_SIZE) : \
   ((mem) == HAL_GTZC_BLOCKBASED_SRAM2) ? (((offset) + (size)) <= SRAM2_SIZE) : (((offset) + (size)) <= SRAM4_SIZE))
#endif /* SRAM6_BASE */

/*! Macro to check block size of block based memory */
#define IS_BLOCKBASED_MEM_BLOCK_GRANULARITY(offset, size) ((((offset) % GTZC_MPCBB_BLOCK_SIZE) == 0U) && \
                                                           (((size) % GTZC_MPCBB_BLOCK_SIZE) == 0U))

/*! Macro to check super-block size of block based memory */
#define IS_BLOCKBASED_MEM_SUPERBLOCK_GRANULARITY(offset, size) ((((offset) % GTZC_MPCBB_SUPERBLOCK_SIZE) == 0U) && \
                                                                (((size) % GTZC_MPCBB_SUPERBLOCK_SIZE) == 0U))

/**
  * @}
  */

/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------------------------------------------*/
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/** @defgroup DMA_Private_Functions DMA Private Functions
  * @{
  */
static hal_gtzc_watermark_subregion_overlap_status_t GTZC_GetAreaInfo(hal_gtzc_watermark_mem_t memory,
                                                                      hal_gtzc_watermark_area_info_t *p_area_info);

static void GTZC_GetOverlappedAreasAttr(hal_gtzc_watermark_mem_t memory,
                                        uint32_t block_idx,
                                        hal_gtzc_watermark_area_info_t *p_area_info);

static void GTZC_GetNotOverlappedAreasAttr(hal_gtzc_watermark_mem_t memory,
                                           uint32_t block_idx,
                                           hal_gtzc_watermark_area_info_t *p_area_info);

static void GTZC_IllegalAccessCallbackCall(uint32_t active_it, uint32_t tzic_register);
/**
  * @}
  */
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup GTZC_Exported_Functions
  * @{
  */

/** @addtogroup GTZC_Exported_Functions_Group1
  * @{

This section provides functions allowing to configure the security and privilege attributes of securable peripherals

  */

/**
  * @brief  Set securable peripherals security and privilege attributes.
  * @param  periph            Peripheral identifier\n
  *                           This parameter is an element of @ref hal_gtzc_periph_t enumeration.
  * @param  p_attr            Security and privilege attributes\n
  *                           A pointer to @ref hal_gtzc_attr_config_t structure that contains the security and
  *                           privilege attributes.
  * @note   Secure and non-secure attributes can only be set from the secure state when TZEN=1.
  * @note   Privilege and non-privilege attributes can only be set from the privilege state when TZEN=0 or TZEN=1.
  * @note   Default state of securable peripheral security attributes is non-secure and unprivileged access allowed.
  * @retval HAL_INVALID_PARAM Invalid parameter when the p_attr pointer is NULL.
  * @retval HAL_OK            Securable peripheral security and privilege attributes has been correctly configured.
  */
hal_status_t HAL_GTZC_SetPeriphAttr(hal_gtzc_periph_t periph, const hal_gtzc_attr_config_t *p_attr)
{
  uint32_t periph_msk;

  ASSERT_DBG_PARAM(p_attr != NULL);
  ASSERT_DBG_PARAM(IS_GTZC_SECURABLE_PERIPHERALS((uint32_t)periph));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_attr == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check GTZC TZSC instance */
  if ((uint32_t)periph < LL_GTZC2_PERIPH_REG1)
  {
    periph_msk = (0x01UL << ((uint32_t)periph % GTZC_REG_MAX_FIELD));

    /* Check which register contain the selected peripheral */
    if ((uint32_t)periph < LL_GTZC1_PERIPH_REG2)
    {
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
      LL_GTZC_TZSC_SetPeriphGrp1SecurityAttr(GTZC1_TZSC1_SEC_PERIPH, periph_msk, (uint32_t)p_attr->sec);
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

      LL_GTZC_TZSC_SetPeriphGrp1PrivilegeAttr(GTZC1_TZSC1_SEC_PERIPH, periph_msk, (uint32_t)p_attr->priv);
    }
    else if ((uint32_t)periph < LL_GTZC1_PERIPH_REG3)
    {
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
      LL_GTZC_TZSC_SetPeriphGrp2SecurityAttr(GTZC1_TZSC1_SEC_PERIPH, periph_msk, (uint32_t)p_attr->sec);
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

      LL_GTZC_TZSC_SetPeriphGrp2PrivilegeAttr(GTZC1_TZSC1_SEC_PERIPH, periph_msk, (uint32_t)p_attr->priv);
    }
    else
    {
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
      LL_GTZC_TZSC_SetPeriphGrp3SecurityAttr(GTZC1_TZSC1_SEC_PERIPH, periph_msk, (uint32_t)p_attr->sec);
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

      LL_GTZC_TZSC_SetPeriphGrp3PrivilegeAttr(GTZC1_TZSC1_SEC_PERIPH, periph_msk, (uint32_t)p_attr->priv);
    }
  }
  else
  {
    periph_msk = (0x01UL << (((uint32_t)periph - AHB3PERIPH_BASE_NS) % GTZC_REG_MAX_FIELD));

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    LL_GTZC_TZSC_SetPeriphGrp1SecurityAttr(GTZC2_TZSC1_SEC_PERIPH, periph_msk, (uint32_t)p_attr->sec);
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

    LL_GTZC_TZSC_SetPeriphGrp1PrivilegeAttr(GTZC2_TZSC1_SEC_PERIPH, periph_msk, (uint32_t)p_attr->priv);
  }
  return HAL_OK;
}

/**
  * @brief  Get the security and privilege attributes of securable peripherals.
  * @param  periph Peripheral identifier\n
  *                This parameter is an element of @ref hal_gtzc_periph_t enumeration.
  * @param  p_attr Security and privilege attributes\n
  *                A pointer to @ref hal_gtzc_attr_config_t structure that return the security and privilege
  *                attributes.
  */
void HAL_GTZC_GetPeriphAttr(hal_gtzc_periph_t periph, hal_gtzc_attr_config_t *p_attr)
{
  uint32_t periph_pos;
  uint32_t periph_msk;

  ASSERT_DBG_PARAM(p_attr != NULL);
  ASSERT_DBG_PARAM(IS_GTZC_SECURABLE_PERIPHERALS((uint32_t)periph));

  /* Check GTZC TZSC instance */
  if ((uint32_t)periph < LL_GTZC2_PERIPH_REG1)
  {
    periph_pos = ((uint32_t)periph % GTZC_REG_MAX_FIELD);
    periph_msk = (1UL << periph_pos);

    /* Check which register contain the selected peripheral */
    if ((uint32_t)periph < LL_GTZC1_PERIPH_REG2)
    {
      p_attr->sec  =
        (hal_gtzc_security_attr_t)(uint32_t)(LL_GTZC_TZSC_GetPeriphGrp1SecurityAttr(GTZC1_TZSC1_SEC_PERIPH,
                                                                                    periph_msk) >> periph_pos);

      p_attr->priv =
        (hal_gtzc_privilege_attr_t)(uint32_t)(LL_GTZC_TZSC_GetPeriphGrp1PrivilegeAttr(GTZC1_TZSC1_SEC_PERIPH,
                                                                                      periph_msk) >> periph_pos);
    }
    else if ((uint32_t)periph < LL_GTZC1_PERIPH_REG3)
    {
      p_attr->sec  =
        (hal_gtzc_security_attr_t)(uint32_t)(LL_GTZC_TZSC_GetPeriphGrp2SecurityAttr(GTZC1_TZSC1_SEC_PERIPH,
                                                                                    periph_msk) >> periph_pos);

      p_attr->priv =
        (hal_gtzc_privilege_attr_t)(uint32_t)(LL_GTZC_TZSC_GetPeriphGrp2PrivilegeAttr(GTZC1_TZSC1_SEC_PERIPH,
                                                                                      periph_msk) >> periph_pos);
    }
    else
    {
      p_attr->sec  =
        (hal_gtzc_security_attr_t)(uint32_t)(LL_GTZC_TZSC_GetPeriphGrp3SecurityAttr(GTZC1_TZSC1_SEC_PERIPH,
                                                                                    periph_msk) >> periph_pos);

      p_attr->priv =
        (hal_gtzc_privilege_attr_t)(uint32_t)(LL_GTZC_TZSC_GetPeriphGrp3PrivilegeAttr(GTZC1_TZSC1_SEC_PERIPH,
                                                                                      periph_msk) >> periph_pos);
    }
  }
  else
  {
    periph_pos = ((uint32_t)periph - AHB3PERIPH_BASE_NS);
    periph_msk = (1UL << periph_pos);

    p_attr->sec  =
      (hal_gtzc_security_attr_t)(uint32_t)(LL_GTZC_TZSC_GetPeriphGrp1SecurityAttr(GTZC2_TZSC1_SEC_PERIPH,
                                                                                  periph_msk) >> periph_pos);

    p_attr->priv =
      (hal_gtzc_privilege_attr_t)(uint32_t)(LL_GTZC_TZSC_GetPeriphGrp1PrivilegeAttr(GTZC2_TZSC1_SEC_PERIPH,
                                                                                    periph_msk) >> periph_pos);
  }
}
/**
  * @}
  */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/** @addtogroup GTZC_Exported_Functions_Group2
  * @{

This section provides functions allowing to lock the configurations of securable peripherals

  */

/**
  * @brief  Lock securable peripherals security attributes configuration.
  * @param  lock_periphs Peripherals to be locked either those on GTZC1 instance or those on GTZC2 instance\n
  *                      This parameter is an element of @ref hal_gtzc_lock_periphs_t enumeration.
  * @note   This function locks the configuration of TZSC_SECCFGRx and TZSC_PRIVCFGRx registers until next MCU HW reset.
  */
void HAL_GTZC_LockPeriphAttr(hal_gtzc_lock_periphs_t lock_periphs)
{
  ASSERT_DBG_PARAM(IS_GTZC_LOCK_PERIPHERALS(lock_periphs));

  LL_GTZC_TZSC_LockPeriphAttr((GTZC_TZSC_SecPeriph_TypeDef *)(uint32_t)lock_periphs);
}

/**
  * @brief  Get lock state of securable peripherals security attributes configuration.
  * @param  lock_periphs            Peripherals to be locked either those on GTZC1 instance or those on GTZC2 instance\n
  *                                 This parameter is an element of @ref hal_gtzc_lock_periphs_t enumeration.
  * @retval HAL_GTZC_ATTR_LOCKED    Securable peripherals security attributes configuration are locked.
  * @retval HAL_GTZC_ATTR_UNLOCKED  Securable peripherals security attributes configuration are unlocked.
  */
hal_gtzc_attr_lock_state_t HAL_GTZC_IsPeriphAttrLocked(hal_gtzc_lock_periphs_t lock_periphs)
{
  ASSERT_DBG_PARAM(IS_GTZC_LOCK_PERIPHERALS(lock_periphs));

  return (hal_gtzc_attr_lock_state_t)LL_GTZC_TZSC_IsLockedPeriphAttr
         ((GTZC_TZSC_SecPeriph_TypeDef *)(uint32_t)lock_periphs);
}
/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group3
  * @{
This section provides functions allowing to configure the security and privilege attributes of Watermark memories area

  */

/**
  * @brief  Set watermark memory subregion security and privilege attributes.
  * @param  memory            Watermark memory\n
  *                           This parameter is an element of @ref hal_gtzc_watermark_mem_t enumeration.
  * @param  offset_byte       Offset in byte of watermark memory subregion.
  * @param  size_byte         Length in byte of watermark memory subregion to be protected.
  * @param  sub_region        Subregion identifier\n
  *                           This parameter is an element of @ref hal_gtzc_watermark_subregion_t enumeration.
  * @param  p_attr            Security and privilege attributes\n
  *                           A pointer to @ref hal_gtzc_attr_config_t structure that contains the security and
  *                           privilege attributes.
  * @retval HAL_INVALID_PARAM Invalid parameter when the p_attr pointer is NULL.
  * @retval HAL_OK            Watermark memory subregion security and privilege attributes has been correctly
  *                           configured.
  */
hal_status_t HAL_GTZC_WATERMARK_SetConfigMemSubRegionAttr(hal_gtzc_watermark_mem_t memory,
                                                          uint32_t offset_byte,
                                                          uint32_t size_byte,
                                                          hal_gtzc_watermark_subregion_t sub_region,
                                                          const hal_gtzc_attr_config_t *p_attr)
{
  GTZC_TZSC_WaterMark_TypeDef *p_mem;
  uint32_t granularity;

  ASSERT_DBG_PARAM(p_attr != NULL);
  ASSERT_DBG_PARAM(IS_GTZC_WATERMARK_MEM(memory));
  ASSERT_DBG_PARAM(IS_WATERMARK_MEM_IN_RANGE(memory, offset_byte, size_byte));
  ASSERT_DBG_PARAM(IS_WATERMARK_MEM_GRANULARITY(memory, offset_byte, size_byte));
  ASSERT_DBG_PARAM(IS_WATERMARK_MEM_SUBREGION(memory, sub_region));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_attr == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_mem = (GTZC_TZSC_WaterMark_TypeDef *)((uint32_t)memory);

  granularity = GTZC_GET_WATERMARK_MEM_GRANULARITY(memory);

  LL_GTZC_TZSC_MPCWM_ConfigSubRegionArea(p_mem, (uint32_t)sub_region, (offset_byte / granularity),
                                         (size_byte / granularity));

  LL_GTZC_TZSC_MPCWM_SetSubRegionAttr(p_mem, (uint32_t)sub_region, (uint32_t)p_attr->sec, (uint32_t)p_attr->priv);

  return HAL_OK;
}

/**
  * @brief  Get watermark memory area security attributes.
  * @param  memory      Watermark memory\n
  *                     This parameter is an element of @ref hal_gtzc_watermark_mem_t enumeration.
  * @param  offset_byte Offset in byte of watermark memory area.
  * @param  size_byte   Length in byte of watermark memory area.
  * @param  p_attr      Security and privilege attributes\n
  *                     A pointer to @ref hal_gtzc_attr_config_t structure that return the security and privilege
  *                     attributes.
  * @retval HAL_OK      Watermark memory area security and privilege attributes has been returned correctly.
  * @retval HAL_ERROR   Watermark memory area have different security and privilege attributes configuration.
  */
hal_status_t HAL_GTZC_WATERMARK_GetMemAreaAttr(hal_gtzc_watermark_mem_t memory,
                                               uint32_t offset_byte,
                                               uint32_t size_byte,
                                               hal_gtzc_attr_config_t *p_attr)
{
  hal_gtzc_watermark_subregion_overlap_status_t is_area_overlapped;
  hal_gtzc_watermark_area_info_t                area_info;
  uint32_t                                      area_offset_byte;

  ASSERT_DBG_PARAM(p_attr != NULL);
  ASSERT_DBG_PARAM(IS_GTZC_WATERMARK_MEM(memory));
  ASSERT_DBG_PARAM(IS_WATERMARK_MEM_IN_RANGE(memory, offset_byte, size_byte));
  ASSERT_DBG_PARAM(IS_WATERMARK_MEM_GRANULARITY(memory, offset_byte, size_byte));

  /* Get the selected area information */
  is_area_overlapped = GTZC_GetAreaInfo(memory, &area_info);

  area_offset_byte = offset_byte;

  while (area_offset_byte < (size_byte + offset_byte))
  {
    area_info.sec_state  = HAL_GTZC_ATTR_SEC;
    area_info.priv_state = HAL_GTZC_ATTR_PRIV;

    /* When an overlap of subregion A and subregion B */
    if (is_area_overlapped == HAL_GTZC_WATERMARK_SUBREGIONS_OVERLAPPED)
    {
      GTZC_GetOverlappedAreasAttr(memory, area_offset_byte, &area_info);
    }
    /* When no overlap of subregion A and subregion B */
    else
    {
      GTZC_GetNotOverlappedAreasAttr(memory, area_offset_byte, &area_info);
    }

    /* Compare the security attributes with the latest state
    - No check of the first watermark memory granularity block
    - There must be no change of the current security attributes with the latest one
    */
    if (area_offset_byte != offset_byte)
    {
      if ((p_attr->sec != area_info.sec_state) || (p_attr->priv != area_info.priv_state))
      {
        return HAL_ERROR;
      }
    }
    else
    {
      p_attr->sec  = area_info.sec_state;
      p_attr->priv = area_info.priv_state;
    }

    /* Increment the watermark memory granularity block */
    area_offset_byte = area_offset_byte + area_info.granularity;
  }

  return HAL_OK;
}

/**
  * @brief  Get watermark memory details (offset_byte, size_byte, security attribute and privilege attribute) of
  *         different area and return the number of different area (Up to five different regions according to
  *         selected memory).
  * @param  memory   Watermark memory\n
  *                  This parameter is an element of @ref hal_gtzc_watermark_mem_t enumeration.
  * @param  p_map    Watermark memory mapping\n
  *                  This @ref hal_gtzc_watermark_mem_map_t structure filled with descriptors by the return of function.
  * @retval uint32_t Number of different area.
  */
uint32_t HAL_GTZC_WATERMARK_GetMemMapAttr(hal_gtzc_watermark_mem_t memory, hal_gtzc_watermark_mem_map_t *p_map)
{
  uint32_t area_offset_byte = 0U;
  uint32_t desc_idx  = 0U ;
  uint32_t tmp_offset_byte;
  uint32_t tmp_size_byte;
  uint32_t watermark_mem_range;
  hal_gtzc_watermark_subregion_overlap_status_t is_area_overlapped;
  hal_gtzc_watermark_area_info_t                area_info;

  ASSERT_DBG_PARAM(p_map != NULL);
  ASSERT_DBG_PARAM(IS_GTZC_WATERMARK_MEM(memory));

  watermark_mem_range = GTZC_GET_WATERMARK_MEM_RANGE(memory);

  /* Get the selected memory information */
  is_area_overlapped = GTZC_GetAreaInfo(memory, &area_info);

  tmp_offset_byte                       = 0U;
  tmp_size_byte                         = area_info.granularity;

  /* Repeat the check of the security attributes of all watermark memory granularity block */
  while (area_offset_byte < watermark_mem_range)
  {
    area_info.sec_state  = HAL_GTZC_ATTR_SEC;
    area_info.priv_state = HAL_GTZC_ATTR_PRIV;

    /* When an overlap of subregion A and subregion B */
    if (is_area_overlapped == HAL_GTZC_WATERMARK_SUBREGIONS_OVERLAPPED)
    {
      GTZC_GetOverlappedAreasAttr(memory, area_offset_byte, &area_info);
    }
    /* When no overlap of subregion A and subregion B */
    else
    {
      GTZC_GetNotOverlappedAreasAttr(memory, area_offset_byte, &area_info);
    }

    /* Compare the security attributes with the latest state
    - No check of the first watermark memory granularity block
    */
    if (area_offset_byte != 0U)
    {
      if ((p_map->mem_desc[desc_idx].attr.sec != area_info.sec_state) ||
          (p_map->mem_desc[desc_idx].attr.priv != area_info.priv_state))
      {
        tmp_offset_byte = area_info.offset_byte;
        tmp_size_byte   = area_info.size_byte;
        desc_idx++;
      }
      else
      {
        tmp_size_byte   = p_map->mem_desc[desc_idx].size_byte + area_info.granularity;
      }
    }

    /* Fill the descriptor with the current data */
    p_map->mem_desc[desc_idx].offset_byte = tmp_offset_byte;
    p_map->mem_desc[desc_idx].size_byte   = tmp_size_byte;
    p_map->mem_desc[desc_idx].attr.sec    = area_info.sec_state;
    p_map->mem_desc[desc_idx].attr.priv   = area_info.priv_state;

    /* Increment the watermark memory granularity block */
    area_offset_byte = area_offset_byte + area_info.granularity;
  }

  desc_idx ++;
  return desc_idx;
}

/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group4
  * @{

This section provides functions allowing to enable or disable watermark memories area

  */

/**
  * @brief  Enable watermark memory subregion.
  * @param  memory     Watermark memory\n
  *                    This parameter is an element of @ref hal_gtzc_watermark_mem_t enumeration.
  * @param  sub_region subregion identifier\n
  *                    This parameter is an element of @ref hal_gtzc_watermark_subregion_t enumeration.
  */
void HAL_GTZC_WATERMARK_EnableMemSubRegionAttr(hal_gtzc_watermark_mem_t memory,
                                               hal_gtzc_watermark_subregion_t sub_region)
{
  ASSERT_DBG_PARAM(IS_GTZC_WATERMARK_MEM(memory));
  ASSERT_DBG_PARAM(IS_GTZC_WATERMARK_SUBREGION(sub_region));

  LL_GTZC_TZSC_MPCWM_EnableSubRegion((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory, (uint32_t)sub_region);
}

/**
  * @brief  Disable watermark memory subregion.
  * @param  memory     Watermark memory\n
  *                    This parameter is an element of @ref hal_gtzc_watermark_mem_t enumeration.
  * @param  sub_region subregion identifier\n
  *                    This parameter is an element of @ref hal_gtzc_watermark_subregion_t enumeration.
  */
void HAL_GTZC_WATERMARK_DisableMemSubRegionAttr(hal_gtzc_watermark_mem_t memory,
                                                hal_gtzc_watermark_subregion_t sub_region)
{
  ASSERT_DBG_PARAM(IS_GTZC_WATERMARK_MEM(memory));
  ASSERT_DBG_PARAM(IS_GTZC_WATERMARK_SUBREGION(sub_region));

  LL_GTZC_TZSC_MPCWM_DisableSubRegion((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory, (uint32_t)sub_region);
}

/**
  * @brief  Check if watermark memory subregion enbled or disabled.
  * @param  memory     Watermark memory\n
  *                    This parameter is an element of @ref hal_gtzc_watermark_mem_t enumeration.
  * @param  sub_region subregion identifier\n
  *                    This parameter is an element of @ref hal_gtzc_watermark_subregion_t enumeration.
  * @retval HAL_GTZC_WATERMARK_SUBREGION_DISABLED Watermark memory subregion is disabled.
  * @retval HAL_GTZC_WATERMARK_SUBREGION_ENABLED  Watermark memory subregion is enabled.
  */
hal_gtzc_watermark_subregion_state_t HAL_GTZC_WATERMARK_IsEnabledMemSubRegionAttr(hal_gtzc_watermark_mem_t memory,
    hal_gtzc_watermark_subregion_t sub_region)
{
  ASSERT_DBG_PARAM(IS_GTZC_WATERMARK_MEM(memory));
  ASSERT_DBG_PARAM(IS_GTZC_WATERMARK_SUBREGION(sub_region));

  return (hal_gtzc_watermark_subregion_state_t)LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion
         ((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory, (uint32_t)sub_region);
}
/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group5
  * @{

This section provides functions allowing to lock the configurations of watermark memories area

  */

/**
  * @brief  Lock watermark memory subregion security and privilege attributes configuration.
  * @param  memory     Watermark memory\n
  *                    This parameter is an element of @ref hal_gtzc_watermark_mem_t enumeration.
  * @param  sub_region subregion identifier\n
  *                    This parameter is an element of @ref hal_gtzc_watermark_subregion_t enumeration.
  * @note   This function locks the configurations of GTZC1_TZSC_MPCWMxCFGR, GTZC1_TZSC_MPCWMxAR and GTZC1_TZSC_MPCWMxBR
  *         registers until next reset.
  */
void HAL_GTZC_WATERMARK_LockMemSubRegionConfig(hal_gtzc_watermark_mem_t memory,
                                               hal_gtzc_watermark_subregion_t sub_region)
{
  ASSERT_DBG_PARAM(IS_GTZC_WATERMARK_MEM(memory));
  ASSERT_DBG_PARAM(IS_GTZC_WATERMARK_SUBREGION(sub_region));

  LL_GTZC_TZSC_MPCWM_LockSubRegion((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory, (uint32_t)sub_region);
}

/**
  * @brief  Get lock state of watermark memory subregion security attributes configuration.
  * @param  memory                 Watermark memory\n
  *                                This parameter is an element of @ref hal_gtzc_watermark_mem_t enumeration.
  * @param  sub_region             subregion identifier\n
  *                                This parameter is an element of @ref hal_gtzc_watermark_subregion_t enumeration.
  * @retval HAL_GTZC_ATTR_LOCKED   Watermark memory subregion security and privilege attributes are locked.
  * @retval HAL_GTZC_ATTR_UNLOCKED Watermark memory subregion security and privilege attributes are unlocked.
  */
hal_gtzc_attr_lock_state_t HAL_GTZC_WATERMARK_IsMemSubRegionConfigLocked(hal_gtzc_watermark_mem_t memory,
                                                                         hal_gtzc_watermark_subregion_t sub_region)
{
  ASSERT_DBG_PARAM(IS_GTZC_WATERMARK_MEM(memory));
  ASSERT_DBG_PARAM(IS_GTZC_WATERMARK_SUBREGION(sub_region));

  return (hal_gtzc_attr_lock_state_t)LL_GTZC_TZSC_MPCWM_IsLockedSubRegion
         ((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory, (uint32_t)sub_region);
}
/**
  * @}
  */
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/** @addtogroup GTZC_Exported_Functions_Group6
  * @{

This section provides functions allowing to configure the security and privilege attributes of block based memories

  */

/**
  * @brief  Set block based memory security attributes by block.
  * @param  memory            block based memory\n
  *                           This parameter is an element of @ref hal_gtzc_blockbased_mem_t enumeration.
  * @param  block_idx         Memory Block index.
  * @param  block_nbr         Memory Block number.
  * @param  p_attr            Security and privilege attributes\n
  *                           A pointer to @ref hal_gtzc_attr_config_t structure that contains the security and
  *                           privilege attributes.
  * @retval HAL_INVALID_PARAM Invalid parameter when the p_attr pointer is NULL.
  * @retval HAL_OK            block based memory security and privilege attributes has been correctly configured.
  */
hal_status_t HAL_GTZC_BLOCKBASED_SetMemBlockAttr(hal_gtzc_blockbased_mem_t memory,
                                                 uint32_t block_idx,
                                                 uint32_t block_nbr,
                                                 const hal_gtzc_attr_config_t *p_attr)
{
  GTZC_BlockBased_TypeDef *p_mem;
  uint32_t                blk_idx;
  uint32_t                blk_nbr;
  uint32_t                super_blk_idx;
  uint32_t                blk_msk = 0U;

  ASSERT_DBG_PARAM(p_attr != NULL);
  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM(memory));
  ASSERT_DBG_PARAM(IS_BLOCKBASED_MEM_IN_RANGE(memory, (block_idx * GTZC_MPCBB_BLOCK_SIZE),
                                              (block_nbr * GTZC_MPCBB_BLOCK_SIZE)));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_attr == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_mem         = (GTZC_BlockBased_TypeDef *)(uint32_t)memory;
  blk_idx       = block_idx % GTZC_REG_MAX_FIELD;
  blk_nbr       = block_nbr;
  super_blk_idx = block_idx / GTZC_REG_MAX_FIELD;

  while (blk_nbr != 0U)
  {
    while ((blk_idx < GTZC_REG_MAX_FIELD) && (blk_nbr != 0U))
    {
      blk_msk |= (1UL << blk_idx);

      blk_idx++;

      blk_nbr--;
    }

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    LL_GTZC_MPCBB_SetBlkSecure(p_mem, super_blk_idx, blk_msk, (uint32_t)p_attr->sec);
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

    LL_GTZC_MPCBB_SetBlkPrivilege(p_mem, super_blk_idx, blk_msk, (uint32_t)p_attr->priv);

    blk_msk = 0U;

    blk_idx = 0U;

    super_blk_idx++;
  }

  return HAL_OK;
}

/**
  * @brief  Get block based memory security attributes by block.
  * @param  memory      block based memory\n
  *                     This parameter is an element of @ref hal_gtzc_blockbased_mem_t enumeration.
  * @param  block_idx   Memory Block index.
  * @param  p_attr      Security and privilege attributes\n
  *                     A pointer to @ref hal_gtzc_attr_config_t structure that return the security and privilege
  *                     attributes.
  */
void HAL_GTZC_BLOCKBASED_GetMemBlockAttr(hal_gtzc_blockbased_mem_t memory,
                                         uint32_t block_idx,
                                         hal_gtzc_attr_config_t *p_attr)
{
  GTZC_BlockBased_TypeDef *p_mem;
  uint32_t                super_blk_idx;

  ASSERT_DBG_PARAM(p_attr != NULL);
  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM(memory));
  ASSERT_DBG_PARAM(IS_BLOCKBASED_MEM_IN_RANGE(memory, (block_idx * GTZC_MPCBB_BLOCK_SIZE), 0U));

  p_mem = (GTZC_BlockBased_TypeDef *)(uint32_t)memory;
  super_blk_idx = block_idx / GTZC_REG_MAX_FIELD;

  p_attr->sec  =
    (hal_gtzc_security_attr_t)(uint32_t)((LL_GTZC_MPCBB_GetSuperBlkSecure(p_mem, super_blk_idx) &
                                          (1UL << ((block_idx / GTZC_REG_MAX_FIELD) % GTZC_REG_MAX_FIELD))) >>
                                         ((block_idx / GTZC_REG_MAX_FIELD) % GTZC_REG_MAX_FIELD));

  p_attr->priv =
    (hal_gtzc_privilege_attr_t)(uint32_t)((LL_GTZC_MPCBB_GetSuperBlkPrivilege(p_mem, super_blk_idx) &
                                           (1UL << ((block_idx / GTZC_REG_MAX_FIELD) % GTZC_REG_MAX_FIELD))) >>
                                          ((block_idx / GTZC_REG_MAX_FIELD) % GTZC_REG_MAX_FIELD));
}

/**
  * @brief  Set block based memory security attributes by address.
  * @param  memory            block based memory\n
  *                           This parameter is an element of @ref hal_gtzc_blockbased_mem_t enumeration.
  * @param  offset_byte       offset in byte of block based memory area.
  * @param  size_byte         Length in byte of block based memory area to be protected.
  * @param  p_attr            Security and privilege attributes\n
  *                           A pointer to @ref hal_gtzc_attr_config_t structure that contains the security and
  *                           privilege attributes.
  * @retval HAL_INVALID_PARAM Invalid parameter when the p_attr pointer is NULL.
  * @retval HAL_OK            block based memory security and privilege attributes has been correctly configured.
  */
hal_status_t HAL_GTZC_BLOCKBASED_SetMemAddrAttr(hal_gtzc_blockbased_mem_t memory,
                                                uint32_t offset_byte,
                                                uint32_t size_byte,
                                                const hal_gtzc_attr_config_t *p_attr)
{
  GTZC_BlockBased_TypeDef *p_mem;
  uint32_t                blk_idx;
  uint32_t                blk_nbr;
  uint32_t                super_blk_idx;
  uint32_t                blk_msk = 0U;

  ASSERT_DBG_PARAM(p_attr != NULL);
  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM(memory));
  ASSERT_DBG_PARAM(IS_BLOCKBASED_MEM_IN_RANGE(memory, offset_byte, size_byte));
  ASSERT_DBG_PARAM(IS_BLOCKBASED_MEM_BLOCK_GRANULARITY(offset_byte, size_byte));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_attr == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_mem         = (GTZC_BlockBased_TypeDef *)(uint32_t)memory;
  blk_idx       = (offset_byte / GTZC_MPCBB_BLOCK_SIZE) % GTZC_REG_MAX_FIELD;
  blk_nbr       = size_byte / GTZC_MPCBB_BLOCK_SIZE;
  super_blk_idx = offset_byte / GTZC_MPCBB_SUPERBLOCK_SIZE;

  while (blk_nbr != 0U)
  {
    while ((blk_idx < GTZC_REG_MAX_FIELD) && (blk_nbr != 0U))
    {
      blk_msk |= (1UL << blk_idx);

      blk_idx++;

      blk_nbr--;
    }

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    LL_GTZC_MPCBB_SetBlkSecure(p_mem, super_blk_idx, blk_msk, (uint32_t)p_attr->sec);
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

    LL_GTZC_MPCBB_SetBlkPrivilege(p_mem, super_blk_idx, blk_msk, (uint32_t)p_attr->priv);

    blk_msk = 0U;

    blk_idx = 0U;

    super_blk_idx++;
  }

  return HAL_OK;
}

/**
  * @brief  Get block based memory security attributes by address.
  * @param  memory      block based memory\n
  *                     This parameter is an element of @ref hal_gtzc_blockbased_mem_t enumeration.
  * @param  offset_byte Offset in bytes of block based memory.
  * @param  p_attr      Security and privilege attributes\n
  *                     A pointer to @ref hal_gtzc_attr_config_t structure that return the security and privilege
  *                     attributes.
  */
void HAL_GTZC_BLOCKBASED_GetMemAddrAttr(hal_gtzc_blockbased_mem_t memory,
                                        uint32_t offset_byte,
                                        hal_gtzc_attr_config_t *p_attr)
{
  GTZC_BlockBased_TypeDef *p_mem;
  uint32_t                super_blk_idx;
  uint32_t                blk_idx;

  ASSERT_DBG_PARAM(p_attr != NULL);
  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM(memory));
  ASSERT_DBG_PARAM(IS_BLOCKBASED_MEM_IN_RANGE(memory, offset_byte, 0U));
  ASSERT_DBG_PARAM(IS_BLOCKBASED_MEM_BLOCK_GRANULARITY(offset_byte, 0U));

  p_mem         = (GTZC_BlockBased_TypeDef *)(uint32_t)memory;
  super_blk_idx = offset_byte / GTZC_MPCBB_SUPERBLOCK_SIZE;
  blk_idx       = (offset_byte / GTZC_MPCBB_BLOCK_SIZE) % GTZC_REG_MAX_FIELD;

  p_attr->sec  =
    (hal_gtzc_security_attr_t)(uint32_t)((LL_GTZC_MPCBB_GetSuperBlkSecure(p_mem, super_blk_idx) &
                                          (1UL << blk_idx)) >> blk_idx);

  p_attr->priv =
    (hal_gtzc_privilege_attr_t)(uint32_t)((LL_GTZC_MPCBB_GetSuperBlkPrivilege(p_mem, super_blk_idx) &
                                           (1UL << blk_idx)) >> blk_idx);
}
/**
  * @}
  */
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/** @addtogroup GTZC_Exported_Functions_Group7
  * @{

This section provides functions allowing to configure the clock security state of block based memories

  */

/**
  * @brief  Set block based memory clock security state.
  * @param  memory        block based memory\n
  *                       This parameter is an element of @ref hal_gtzc_blockbased_mem_t enumeration.
  * @param  clk_sec_state Clock security state\n
  *                       This parameter is an element of @ref hal_gtzc_blockbased_mem_clk_sec_state_t enumeration.
  */
void HAL_GTZC_BLOCKBASED_SetMemClkSecStateInvertion(hal_gtzc_blockbased_mem_t memory,
                                                    hal_gtzc_blockbased_mem_clk_sec_state_t clk_sec_state)
{
  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM(memory));
  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM_CLK_SEC_STATE(clk_sec_state));

  LL_GTZC_MPCBB_SetClockSecurityState((GTZC_BlockBased_TypeDef *)(uint32_t)memory, (uint32_t)clk_sec_state);
}

/**
  * @brief  Get block based memory clock security state.
  * @param  memory                        block based memory\n
  *                                       This parameter is an element of @ref hal_gtzc_blockbased_mem_t enumeration.
  * @retval HAL_GTZC_CLK_SEC_NOT_INVERTED block based memory clock security not inverted.
  * @retval HAL_GTZC_CLK_SEC_INVERTED     block based memory clock security inverted.
  */
hal_gtzc_blockbased_mem_clk_sec_state_t HAL_GTZC_BLOCKBASED_GetMemClkSecStateInvertion(hal_gtzc_blockbased_mem_t memory)
{
  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM(memory));

  return (hal_gtzc_blockbased_mem_clk_sec_state_t)(uint32_t)LL_GTZC_MPCBB_GetClockSecurityState
         ((GTZC_BlockBased_TypeDef *)(uint32_t)memory);
}
/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group8
  * @{

This section provides functions allowing to configure the secure access state of block based memories

  */

/**
  * @brief  Set block based memory secure access state.
  * @param  memory block based memory\n
  *                This parameter is an element of @ref hal_gtzc_blockbased_mem_t enumeration.
  * @param  state  Secure access state\n
  *                This parameter is an element of @ref hal_gtzc_blockbased_mem_sec_access_state_t enumeration.
  */
void HAL_GTZC_BLOCKBASED_SetMemSecAccessState(hal_gtzc_blockbased_mem_t memory,
                                              hal_gtzc_blockbased_mem_sec_access_state_t state)
{
  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM(memory));
  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM_SEC_ACCESS_STATE(state));

  LL_GTZC_MPCBB_SetSecureAccessState((GTZC_BlockBased_TypeDef *)(uint32_t)memory, (uint32_t)state);
}

/**
  * @brief  Get block based secure access state.
  * @param  memory                          block based memory\n
  *                                         This parameter is an element of @ref hal_gtzc_blockbased_mem_t enumeration.
  * @retval HAL_GTZC_SEC_ACCESS_NOT_ALLOWED block based memory secure access not allowed.
  * @retval HAL_GTZC_SEC_ACCESS_ALLOWED     block based memory secure access allowed.
  */
hal_gtzc_blockbased_mem_sec_access_state_t HAL_GTZC_BLOCKBASED_GetMemSecAccessState(hal_gtzc_blockbased_mem_t memory)
{
  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM(memory));

  return (hal_gtzc_blockbased_mem_sec_access_state_t)(uint32_t)LL_GTZC_MPCBB_GetSecureAccessState
         ((GTZC_BlockBased_TypeDef *)(uint32_t)memory);
}
/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group9
  * @{

This section provides functions allowing to lock the configurations of block based memories

  */

/**
  * @brief  Lock block based memory security attributes configuration by super-block.
  * @param  memory        block based memory\n
  *                       This parameter is an element of @ref hal_gtzc_blockbased_mem_t enumeration.
  * @param  super_blk_idx Start index of memory super-block.
  * @param  super_blk_nbr Number of memory super-blocks.
  * @note   This function locks the configurations of GTZC1_MPCBBz_SECCFGRy and GTZC1_MPCBBz_PRIVCFGRy registers until
  *         next reset.
  */
void HAL_GTZC_BLOCKBASED_LockMemSuperBlockAttr(hal_gtzc_blockbased_mem_t memory,
                                               uint32_t super_blk_idx,
                                               uint32_t super_blk_nbr)
{
  uint32_t super_blk_mask = 0;

  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM(memory));
  ASSERT_DBG_PARAM(IS_BLOCKBASED_MEM_IN_RANGE(memory, (super_blk_idx * GTZC_MPCBB_SUPERBLOCK_SIZE),
                                              (super_blk_nbr * GTZC_MPCBB_SUPERBLOCK_SIZE)));

#if defined (SRAM5_BASE)
  if (super_blk_idx <= 31U)
#endif /* SRAM5_BASE */
  {
    for (uint32_t idx = super_blk_idx; idx < (super_blk_idx + super_blk_nbr); idx++)
    {
      super_blk_mask |= (1UL << idx);
    }

    LL_GTZC_MPCBB_LockSuperBlk_0_31((GTZC_BlockBased_TypeDef *)(uint32_t)memory, super_blk_mask);
  }
#if defined (SRAM5_BASE)
  else
  {
    for (uint32_t idx = super_blk_idx; idx < (super_blk_idx + super_blk_nbr); idx++)
    {
      super_blk_mask |= (1UL << (idx - GTZC_REG_MAX_FIELD));
    }

    LL_GTZC_MPCBB_LockSuperBlk_32_51((GTZC_BlockBased_TypeDef *)(uint32_t)memory, super_blk_mask);
  }
#endif /* SRAM5_BASE */
}

/**
  * @brief  Get lock state of block based memory security attributes configuration by super-block.
  * @param  memory                 block based memory\n
  *                                This parameter is an element of @ref hal_gtzc_blockbased_mem_t enumeration.
  * @param  super_blk_idx          Start index of memory super-block.
  * @retval HAL_GTZC_ATTR_LOCKED   Super-block memory security and privilege attributes configuration are locked.
  * @retval HAL_GTZC_ATTR_UNLOCKED Super-block memory security and privilege attributes configuration are unlocked.
  */
hal_gtzc_attr_lock_state_t HAL_GTZC_BLOCKBASED_IsMemSuperBlockAttrLocked(hal_gtzc_blockbased_mem_t memory,
                                                                         uint32_t super_blk_idx)
{
  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM(memory));
  ASSERT_DBG_PARAM(IS_BLOCKBASED_MEM_IN_RANGE(memory, (super_blk_idx * GTZC_MPCBB_SUPERBLOCK_SIZE), 0U));

#if defined (SRAM5_BASE)
  if (super_blk_idx <= 31U)
#endif /* SRAM5_BASE */
  {
    return (hal_gtzc_attr_lock_state_t)(uint32_t)((LL_GTZC_MPCBB_GetLockedSuperBlk_0_31
                                                   ((GTZC_BlockBased_TypeDef *)(uint32_t)memory) &
                                                   (1UL << super_blk_idx)) >> super_blk_idx);
  }
#if defined (SRAM5_BASE)
  else
  {
    return (hal_gtzc_attr_lock_state_t)(uint32_t)((LL_GTZC_MPCBB_GetLockedSuperBlk_32_51
                                                   ((GTZC_BlockBased_TypeDef *)(uint32_t)memory) &
                                                   (1UL << (super_blk_idx - GTZC_REG_MAX_FIELD))) >>
                                                  (super_blk_idx - GTZC_REG_MAX_FIELD));
  }
#endif /* SRAM5_BASE */
}

/**
  * @brief  Lock block based memory security attributes configuration by address.
  * @param  memory      block based memory\n
  *                     This parameter is a element of @ref hal_gtzc_blockbased_mem_t enumeration.
  * @param  offset_byte Offset in byte of block based memory area must be aligned with super_block size.
  * @param  size_byte   Length in byte of block based memory area to be locked must be aligned with super_block size.
  * @note   This function locks the configurations of GTZC1_MPCBBz_SECCFGRy and GTZC1_MPCBBz_PRIVCFGRy registers until
  *         next reset.
  */
void HAL_GTZC_BLOCKBASED_LockMemAttr(hal_gtzc_blockbased_mem_t memory, uint32_t offset_byte, uint32_t size_byte)
{
  uint32_t super_blk_idx;
  uint32_t super_blk_nbr;
  uint32_t super_blk_mask = 0;

  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM(memory));
  ASSERT_DBG_PARAM(IS_BLOCKBASED_MEM_IN_RANGE(memory, offset_byte, size_byte));
  ASSERT_DBG_PARAM(IS_BLOCKBASED_MEM_SUPERBLOCK_GRANULARITY(offset_byte, size_byte));

  super_blk_idx = offset_byte / GTZC_MPCBB_SUPERBLOCK_SIZE;
  super_blk_nbr = size_byte / GTZC_MPCBB_SUPERBLOCK_SIZE;

#if defined (SRAM5_BASE)
  if (super_blk_idx <= 31U)
#endif /* SRAM5_BASE */
  {
    for (uint32_t idx = super_blk_idx; idx < (super_blk_idx + super_blk_nbr); idx++)
    {
      super_blk_mask |= (1UL << idx);
    }

    LL_GTZC_MPCBB_LockSuperBlk_0_31((GTZC_BlockBased_TypeDef *)(uint32_t)memory, super_blk_mask);
  }
#if defined (SRAM5_BASE)
  else
  {
    for (uint32_t idx = super_blk_idx; idx < (super_blk_idx + super_blk_nbr); idx++)
    {
      super_blk_mask |= (1UL << (idx - GTZC_REG_MAX_FIELD));
    }

    LL_GTZC_MPCBB_LockSuperBlk_32_51((GTZC_BlockBased_TypeDef *)(uint32_t)memory, super_blk_mask);
  }
#endif /* SRAM5_BASE */
}

/**
  * @brief  Get lock state of block based memory security attributes configuration by address.
  * @param  memory      block based memory\n
  *                     This parameter is an element of @ref hal_gtzc_blockbased_mem_t enumeration.
  * @param  offset_byte Offset in bytes of blockblock basedbased memory must be aligned with super_block size.
  * @retval HAL_GTZC_ATTR_LOCKED   Super-block memory security and privilege attributes configuration are locked.
  * @retval HAL_GTZC_ATTR_UNLOCKED Super-block memory security and privilege attributes configuration are unlocked.
  */
hal_gtzc_attr_lock_state_t HAL_GTZC_BLOCKBASED_IsMemAttrLocked(hal_gtzc_blockbased_mem_t memory, uint32_t offset_byte)
{
  uint32_t super_blk_idx;

  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM(memory));
  ASSERT_DBG_PARAM(IS_BLOCKBASED_MEM_IN_RANGE(memory, offset_byte, 0U));
  ASSERT_DBG_PARAM(IS_BLOCKBASED_MEM_SUPERBLOCK_GRANULARITY(offset_byte, 0U));

  super_blk_idx = offset_byte / GTZC_MPCBB_SUPERBLOCK_SIZE;

#if defined (SRAM5_BASE)
  if (super_blk_idx <= 31U)
#endif /* SRAM5_BASE */
  {
    return (hal_gtzc_attr_lock_state_t)(uint32_t)((LL_GTZC_MPCBB_GetLockedSuperBlk_0_31
                                                   ((GTZC_BlockBased_TypeDef *)(uint32_t)memory) &
                                                   (1UL << super_blk_idx)) >> super_blk_idx);
  }
#if defined (SRAM5_BASE)
  else
  {
    return (hal_gtzc_attr_lock_state_t)(uint32_t)((LL_GTZC_MPCBB_GetLockedSuperBlk_32_51
                                                   ((GTZC_BlockBased_TypeDef *)(uint32_t)memory) &
                                                   (1UL << (super_blk_idx - GTZC_REG_MAX_FIELD))) >>
                                                  (super_blk_idx - GTZC_REG_MAX_FIELD));
  }
#endif /* SRAM5_BASE */
}

/**
  * @brief  Lock block based memory configuration.
  * @param  memory block based memory\n
  *                This parameter is an element of @ref hal_gtzc_blockbased_mem_t enumeration.
  * @note   This function locks the configuration of GTZCx_MPCBBz_CR registers until next reset.
  */
void HAL_GTZC_BLOCKBASED_LockMemConfig(hal_gtzc_blockbased_mem_t memory)
{
  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM(memory));

  LL_GTZC_MPCBB_LockConfig((GTZC_BlockBased_TypeDef *)(uint32_t)memory);
}

/**
  * @brief  Get lock state of block based memory configuration.
  * @param  memory                 block based memory\n
  *                                This parameter is an element of @ref hal_gtzc_blockbased_mem_t enumeration.
  * @retval HAL_GTZC_ATTR_LOCKED   block based memory configuration is locked.
  * @retval HAL_GTZC_ATTR_UNLOCKED block based memory configuration is unlocked.
  */
hal_gtzc_attr_lock_state_t HAL_GTZC_BLOCKBASED_IsMemConfigLocked(hal_gtzc_blockbased_mem_t memory)
{
  ASSERT_DBG_PARAM(IS_GTZC_BLOCKBASED_MEM(memory));

  return (hal_gtzc_attr_lock_state_t)LL_GTZC_MPCBB_IsLockedConfig((GTZC_BlockBased_TypeDef *)(uint32_t)memory);
}
/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group10
  * @{

This section provides functions allowing to enable or disable the illegal access interrupt of peripherals

  */

/**
  * @brief  Activate the illegal access interrupt to a peripheral.
  * @param  periph Peripheral identifier\n
  *                This parameter is an element of @ref hal_gtzc_periph_t enumeration.
  */
void HAL_GTZC_ILLEGALACCESS_EnableIT(hal_gtzc_periph_t periph)
{
  uint32_t periph_msk;

  ASSERT_DBG_PARAM(IS_ILLEGAL_ACCESS_PERIPHERAL((uint32_t)periph));

  if (periph == HAL_GTZC_PERIPH_ALL)
  {
    LL_GTZC_TZIC_EnableGrp1IT(GTZC1_TZIC1, LL_GTZC1_GRP1_ALL);
    LL_GTZC_TZIC_EnableGrp2IT(GTZC1_TZIC1, LL_GTZC1_GRP2_ALL);
    LL_GTZC_TZIC_EnableGrp3IT(GTZC1_TZIC1, LL_GTZC1_GRP3_ALL);
    LL_GTZC_TZIC_EnableGrp4IT(GTZC1_TZIC1, LL_GTZC1_GRP4_ALL);
    LL_GTZC_TZIC_EnableGrp1IT(GTZC2_TZIC1, LL_GTZC2_GRP1_ALL);
    LL_GTZC_TZIC_EnableGrp2IT(GTZC2_TZIC1, LL_GTZC2_GRP2_ALL);
  }
  else if ((uint32_t)periph < LL_GTZC2_PERIPH_REG1)
  {
    periph_msk = (0x01UL << ((uint32_t)periph % GTZC_REG_MAX_FIELD));

    if ((uint32_t)periph < LL_GTZC1_PERIPH_REG2)
    {
      LL_GTZC_TZIC_EnableGrp1IT(GTZC1_TZIC1, periph_msk);
    }
    else if ((uint32_t)periph < LL_GTZC1_PERIPH_REG3)
    {
      LL_GTZC_TZIC_EnableGrp2IT(GTZC1_TZIC1, periph_msk);
    }
    else if ((uint32_t)periph < LL_GTZC1_PERIPH_REG4)
    {
      LL_GTZC_TZIC_EnableGrp3IT(GTZC1_TZIC1, periph_msk);
    }
    else
    {
      LL_GTZC_TZIC_EnableGrp4IT(GTZC1_TZIC1, periph_msk);
    }
  }
  else
  {
    periph_msk = (0x01UL << (((uint32_t)periph - AHB3PERIPH_BASE_NS) % GTZC_REG_MAX_FIELD));

    if ((uint32_t)periph < LL_GTZC2_PERIPH_REG2)
    {
      LL_GTZC_TZIC_EnableGrp1IT(GTZC2_TZIC1, periph_msk);
    }
    else
    {
      LL_GTZC_TZIC_EnableGrp2IT(GTZC2_TZIC1, periph_msk);
    }
  }
}

/**
  * @brief  Deactivate the illegal access interrupt to a peripheral.
  * @param  periph Peripheral identifier\n
  *                This parameter is an element of @ref hal_gtzc_periph_t enumeration.
  */
void HAL_GTZC_ILLEGALACCESS_DisableIT(hal_gtzc_periph_t periph)
{
  uint32_t periph_msk;

  ASSERT_DBG_PARAM(IS_ILLEGAL_ACCESS_PERIPHERAL((uint32_t)periph));

  if (periph == HAL_GTZC_PERIPH_ALL)
  {
    LL_GTZC_TZIC_DisableGrp1IT(GTZC1_TZIC1, LL_GTZC1_GRP1_ALL);
    LL_GTZC_TZIC_DisableGrp2IT(GTZC1_TZIC1, LL_GTZC1_GRP2_ALL);
    LL_GTZC_TZIC_DisableGrp3IT(GTZC1_TZIC1, LL_GTZC1_GRP3_ALL);
    LL_GTZC_TZIC_DisableGrp4IT(GTZC1_TZIC1, LL_GTZC1_GRP4_ALL);
    LL_GTZC_TZIC_DisableGrp1IT(GTZC2_TZIC1, LL_GTZC2_GRP1_ALL);
    LL_GTZC_TZIC_DisableGrp2IT(GTZC2_TZIC1, LL_GTZC2_GRP2_ALL);
  }
  else if ((uint32_t)periph < LL_GTZC2_PERIPH_REG1)
  {
    periph_msk = (0x01UL << ((uint32_t)periph % GTZC_REG_MAX_FIELD));

    if ((uint32_t)periph < LL_GTZC1_PERIPH_REG2)
    {
      LL_GTZC_TZIC_DisableGrp1IT(GTZC1_TZIC1, periph_msk);
    }
    else if ((uint32_t)periph < LL_GTZC1_PERIPH_REG3)
    {
      LL_GTZC_TZIC_DisableGrp2IT(GTZC1_TZIC1, periph_msk);
    }
    else if ((uint32_t)periph < LL_GTZC1_PERIPH_REG4)
    {
      LL_GTZC_TZIC_DisableGrp3IT(GTZC1_TZIC1, periph_msk);
    }
    else
    {
      LL_GTZC_TZIC_DisableGrp4IT(GTZC1_TZIC1, periph_msk);
    }
  }
  else
  {
    periph_msk = (0x01UL << (((uint32_t)periph - AHB3PERIPH_BASE_NS) % GTZC_REG_MAX_FIELD));

    if ((uint32_t)periph < LL_GTZC2_PERIPH_REG2)
    {
      LL_GTZC_TZIC_DisableGrp1IT(GTZC2_TZIC1, periph_msk);
    }
    else
    {
      LL_GTZC_TZIC_DisableGrp2IT(GTZC2_TZIC1, periph_msk);
    }
  }
}

/**
  * @brief  Check if the illegal access interrupt to a peripheral enabled or disabled.
  * @param  periph Peripheral identifier\n
  *                This parameter is an element of @ref hal_gtzc_periph_t enumeration.
  * @retval HAL_GTZC_ILAC_IT_DISABLED Illegal access interrupt disabled.
  * @retval HAL_GTZC_ILAC_IT_ENABLED  Illegal access interrupt enabled.
  */
hal_gtzc_illegal_access_it_state_t HAL_GTZC_ILLEGALACCESS_IsEnabledIT(hal_gtzc_periph_t periph)
{
  uint32_t periph_msk;

  ASSERT_DBG_PARAM(IS_ILLEGAL_ACCESS_PERIPHERAL((uint32_t)periph));
  ASSERT_DBG_PARAM(periph != HAL_GTZC_PERIPH_ALL);

  if ((uint32_t)periph < LL_GTZC2_PERIPH_REG1)
  {
    periph_msk = (0x01UL << ((uint32_t)periph % GTZC_REG_MAX_FIELD));

    if ((uint32_t)periph < LL_GTZC1_PERIPH_REG2)
    {
      return ((hal_gtzc_illegal_access_it_state_t)LL_GTZC_TZIC_IsEnabledGrp1IT(GTZC1_TZIC1, periph_msk));
    }
    else if ((uint32_t)periph < LL_GTZC1_PERIPH_REG3)
    {
      return ((hal_gtzc_illegal_access_it_state_t)LL_GTZC_TZIC_IsEnabledGrp2IT(GTZC1_TZIC1, periph_msk));
    }
    else if ((uint32_t)periph < LL_GTZC1_PERIPH_REG4)
    {
      return ((hal_gtzc_illegal_access_it_state_t)LL_GTZC_TZIC_IsEnabledGrp3IT(GTZC1_TZIC1, periph_msk));
    }
    else
    {
      return ((hal_gtzc_illegal_access_it_state_t)LL_GTZC_TZIC_IsEnabledGrp4IT(GTZC1_TZIC1, periph_msk));
    }
  }
  else
  {
    periph_msk = (0x01UL << (((uint32_t)periph - AHB3PERIPH_BASE_NS) % GTZC_REG_MAX_FIELD));

    if ((uint32_t)periph < LL_GTZC2_PERIPH_REG2)
    {
      return ((hal_gtzc_illegal_access_it_state_t)LL_GTZC_TZIC_IsEnabledGrp1IT(GTZC2_TZIC1, periph_msk));
    }
    else
    {
      return ((hal_gtzc_illegal_access_it_state_t)LL_GTZC_TZIC_IsEnabledGrp2IT(GTZC2_TZIC1, periph_msk));
    }
  }
}
/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group11
  * @{

This section provides functions allowing to treat ISR and provide user callback

  */

/**
  * @brief  This function handles GTZC illegal access interrupt request.
  */
void HAL_GTZC_ILLEGALACCESS_IRQHandler(void)
{
  /* Get current enabled interrupts and its status flags on register 1 of GTZC1 TZIC1 */
  uint32_t active_flags = LL_GTZC_READ_REG(GTZC1_TZIC1, SR1);
  uint32_t active_it    = LL_GTZC_READ_REG(GTZC1_TZIC1, IER1) & active_flags;

  /*--------------------------------------------------  GTZC1 TZIC1  -------------------------------------------------*/
  if (active_it != 0U)
  {
    LL_GTZC_WRITE_REG(GTZC1_TZIC1, FCR1, active_it);

    GTZC_IllegalAccessCallbackCall(active_it, LL_GTZC1_PERIPH_REG1);
  }

  /* Get current enabled interrupts and its status flags on register 2 of GTZC1 TZIC1 */
  active_flags = LL_GTZC_READ_REG(GTZC1_TZIC1, SR2);
  active_it    = LL_GTZC_READ_REG(GTZC1_TZIC1, IER2) & active_flags;

  if (active_it != 0U)
  {
    LL_GTZC_WRITE_REG(GTZC1_TZIC1, FCR2, active_it);

    GTZC_IllegalAccessCallbackCall(active_it, LL_GTZC1_PERIPH_REG2);
  }

  /* Get current enabled interrupts and its status flags on register 3 of GTZC1 TZIC1 */
  active_flags = LL_GTZC_READ_REG(GTZC1_TZIC1, SR3);
  active_it    = LL_GTZC_READ_REG(GTZC1_TZIC1, IER3) & active_flags;

  if (active_it != 0U)
  {
    LL_GTZC_WRITE_REG(GTZC1_TZIC1, FCR3, active_it);

    GTZC_IllegalAccessCallbackCall(active_it, LL_GTZC1_PERIPH_REG3);
  }

  /* Get current enabled interrupts and its status flags on register 4 of GTZC1 TZIC1 */
  active_flags = LL_GTZC_READ_REG(GTZC1_TZIC1, SR4);
  active_it    = LL_GTZC_READ_REG(GTZC1_TZIC1, IER4) & active_flags;

  if (active_it != 0U)
  {
    LL_GTZC_WRITE_REG(GTZC1_TZIC1, FCR4, active_it);

    GTZC_IllegalAccessCallbackCall(active_it, LL_GTZC1_PERIPH_REG4);
  }

  /*--------------------------------------------------  GTZC2 TZIC1  -------------------------------------------------*/

  /* Get current enabled interrupts and its status flags on register 1 of GTZC2 TZIC1 */
  active_flags = LL_GTZC_READ_REG(GTZC2_TZIC1, SR1);
  active_it    = LL_GTZC_READ_REG(GTZC2_TZIC1, IER1) & active_flags;

  if (active_it != 0U)
  {
    LL_GTZC_WRITE_REG(GTZC2_TZIC1, FCR1, active_it);

    GTZC_IllegalAccessCallbackCall(active_it, LL_GTZC2_PERIPH_REG1);
  }

  /* Get current enabled interrupts and its status flags on register 2 of GTZC2 TZIC1 */
  active_flags = LL_GTZC_READ_REG(GTZC2_TZIC1, SR2);
  active_it    = LL_GTZC_READ_REG(GTZC2_TZIC1, IER2) & active_flags;

  if (active_it != 0U)
  {
    LL_GTZC_WRITE_REG(GTZC2_TZIC1, FCR2, active_it);

    GTZC_IllegalAccessCallbackCall(active_it, LL_GTZC2_PERIPH_REG2);
  }
}

/**
  * @brief  GTZC illegal access sub-block interrupt callback.
  * @param  periph Peripheral identifier
  *                This parameter can be an element of @ref hal_gtzc_periph_t enumeration.
  */
__WEAK void HAL_GTZC_ILLEGALACCESS_Callback(hal_gtzc_periph_t periph)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(periph);

  /* NOTE: This function must not be modified. When the callback is needed,
   * the HAL_GTZC_ILLEGALACCESS_Callback is to be implemented in the user file.
   */
}
/**
  * @}
  */

/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @addtogroup DMA_Private_Functions
  * @{
  */

/**
  * @brief  Get the overlap start and the overlap end between subregion A and subregion B for the watermark memory.
  * @param  memory                                       Watermark memory\n
  *                                                      An element of \ref hal_gtzc_watermark_mem_t enumeration.
  * @param  p_area_info                                  Pointer to watermark area info.
  * @retval HAL_GTZC_WATERMARK_SUBREGIONS_OVERLAPPED     When an overlap of subregion A and subregion B.
  * @retval HAL_GTZC_WATERMARK_SUBREGIONS_NOT_OVERLAPPED When no overlap of subregion A and subregion B.
  */
static hal_gtzc_watermark_subregion_overlap_status_t GTZC_GetAreaInfo(hal_gtzc_watermark_mem_t memory,
                                                                      hal_gtzc_watermark_area_info_t *p_area_info)
{
  p_area_info->granularity    = GTZC_GET_WATERMARK_MEM_GRANULARITY(memory);

  p_area_info->start_subregion_a =
    LL_GTZC_TZSC_MPCWM_GetSubRegionStart((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                         (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_A);

  p_area_info->end_subregion_a = (LL_GTZC_TZSC_MPCWM_GetSubRegionLength((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                                                        (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_A) >> \
                                  16U) + p_area_info->start_subregion_a;

  p_area_info->sec_state_subregion_a =
    LL_GTZC_TZSC_MPCWM_GetSubRegionSecure((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                          (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_A) >> 8U;

  p_area_info->priv_state_subregion_a =
    LL_GTZC_TZSC_MPCWM_GetSubRegionPrivilege((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                             (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_A) >> 9U;

  p_area_info->start_subregion_b = LL_GTZC_TZSC_MPCWM_GetSubRegionStart((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                                                        (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_B);

  p_area_info->end_subregion_b = (LL_GTZC_TZSC_MPCWM_GetSubRegionLength((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                                                        (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_B) >> \
                                  16U) + p_area_info->start_subregion_b;

  p_area_info->sec_state_subregion_b =
    LL_GTZC_TZSC_MPCWM_GetSubRegionSecure((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                          (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_B) >> 8U;

  p_area_info->priv_state_subregion_b =
    LL_GTZC_TZSC_MPCWM_GetSubRegionPrivilege((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                             (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_B) >> 9U;


  /* *************** State 1 ****************
  ----------------------
       subregion B
                        ---------------------
                     overlap
  ----------------------
                            subregion A
                        ---------------------
  **************************************** */
  if ((p_area_info->end_subregion_b >= p_area_info->end_subregion_a)  &&
      (p_area_info->end_subregion_a > p_area_info->start_subregion_b) &&
      (p_area_info->start_subregion_b >= p_area_info->start_subregion_a))
  {
    p_area_info->start_overlap = p_area_info->start_subregion_b;
    p_area_info->end_overlap   = p_area_info->end_subregion_a;
  }

  /* *************** State 2 ****************
  ----------------------
       subregion A
                        ---------------------
                     overlap
  ----------------------
                            subregion B
                        ---------------------
  **************************************** */
  else if ((p_area_info->end_subregion_a >= p_area_info->end_subregion_b)  &&
           (p_area_info->end_subregion_b > p_area_info->start_subregion_a) &&
           (p_area_info->start_subregion_a >= p_area_info->start_subregion_b))
  {
    p_area_info->start_overlap = p_area_info->start_subregion_a;
    p_area_info->end_overlap   = p_area_info->end_subregion_b;
  }

  /* *************** State 3 ****************
                       ---------------------
  ---------------------
  subregion B  = overlap       subregion A
  ---------------------
                       ---------------------
  *************************************** */
  else if ((p_area_info->end_subregion_a >= p_area_info->end_subregion_b) &&
           (p_area_info->start_subregion_b >= p_area_info->start_subregion_a))
  {
    p_area_info->start_overlap = p_area_info->start_subregion_b;
    p_area_info->end_overlap   = p_area_info->end_subregion_b;
  }

  /* *************** State 4 ****************
                       ---------------------
  ---------------------
  subregion A  = overlap       subregion B
  ---------------------
                       ---------------------
  *************************************** */
  else if ((p_area_info->end_subregion_b >= p_area_info->end_subregion_a) &&
           (p_area_info->start_subregion_a >= p_area_info->start_subregion_b))
  {
    p_area_info->start_overlap = p_area_info->start_subregion_a;
    p_area_info->end_overlap   = p_area_info->end_subregion_a;
  }

  /* ************************************* State 5 *****************************************
  ---------------------                       |   ---------------------
      subregion B                            |      subregion A
  ---------------------                       |   ---------------------
                   overlap = 0                |                    overlap =0
                       ---------------------  |                        ---------------------
                           subregion A       |                            subregion B
                       ---------------------  |                        ---------------------
  *************************************************************************************** */
  else
  {
    p_area_info->start_overlap = 0U;
    p_area_info->end_overlap   = 0U;

    return HAL_GTZC_WATERMARK_SUBREGIONS_NOT_OVERLAPPED;
  }

  return HAL_GTZC_WATERMARK_SUBREGIONS_OVERLAPPED;
}

/**
  * @brief  Get the selected watermark area details (offset_byte, size_byte, security attribute and privilege attribute)
  *         when an overlap of subregion A and subregion B.
  * @param  memory           Watermark memory\n
  *                          An element of \ref hal_gtzc_watermark_mem_t enumeration.
  * @param  area_offset_byte Index of current block of watermarmk area memory.
  * @param  p_area_info      Pointer to watermark area info.
  */
static void GTZC_GetOverlappedAreasAttr(hal_gtzc_watermark_mem_t memory,
                                        uint32_t area_offset_byte,
                                        hal_gtzc_watermark_area_info_t *p_area_info)
{
  /* Current watermark memory granularity block in first part */
  if ((area_offset_byte < (p_area_info->start_subregion_a * p_area_info->granularity)) &&
      (area_offset_byte < (p_area_info->start_subregion_b * p_area_info->granularity)))
  {
    p_area_info->offset_byte = 0U;
    p_area_info->size_byte   = area_offset_byte + p_area_info->granularity - p_area_info->offset_byte;
  }

  /* Current watermark memory granularity block in second part */
  else if ((area_offset_byte < (p_area_info->start_subregion_b * p_area_info->granularity)) ||
           (area_offset_byte < (p_area_info->start_subregion_a * p_area_info->granularity)))
  {
    p_area_info->offset_byte =
      (((p_area_info->start_subregion_a * p_area_info->granularity) <= (p_area_info->start_subregion_b *
                                                                        p_area_info->granularity)) ? \
       (p_area_info->start_subregion_a * p_area_info->granularity) : (p_area_info->start_subregion_b *
                                                                      p_area_info->granularity));

    p_area_info->size_byte   = area_offset_byte + p_area_info->granularity - p_area_info->offset_byte;

    if ((p_area_info->start_subregion_a * p_area_info->granularity) < (p_area_info->start_subregion_b *
                                                                       p_area_info->granularity))
    {
      if (LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                                (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_A) != 0U)
      {
        p_area_info->sec_state  = (hal_gtzc_security_attr_t)p_area_info->sec_state_subregion_a;
        p_area_info->priv_state = (hal_gtzc_privilege_attr_t)p_area_info->priv_state_subregion_a;
      }
    }
    else
    {
      if (LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                                (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_B) != 0U)
      {
        p_area_info->sec_state  = (hal_gtzc_security_attr_t)p_area_info->sec_state_subregion_b;
        p_area_info->priv_state = (hal_gtzc_privilege_attr_t)p_area_info->priv_state_subregion_b;
      }
    }
  }

  /* Current watermark memory granularity block in third part */
  else if (area_offset_byte < (p_area_info->end_overlap * p_area_info->granularity))
  {
    p_area_info->offset_byte = (p_area_info->start_overlap * p_area_info->granularity);
    p_area_info->size_byte   = area_offset_byte + p_area_info->granularity - p_area_info->offset_byte;

    /* Check the security attributes of current watermark granularity block */
    if (p_area_info->sec_state_subregion_a == 0U)
    {
      if (LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                                (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_A) != 0U)
      {
        p_area_info->sec_state = (hal_gtzc_security_attr_t)p_area_info->sec_state_subregion_a;
      }
    }
    else
    {
      if (LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                                (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_B) != 0U)
      {
        p_area_info->sec_state = (hal_gtzc_security_attr_t)p_area_info->sec_state_subregion_b;
      }
    }

    /* Check the privilege attributes of current watermark granularity block */
    if (p_area_info->priv_state_subregion_a == 0U)
    {
      if (LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                                (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_A) != 0U)
      {
        p_area_info->priv_state = (hal_gtzc_privilege_attr_t)p_area_info->priv_state_subregion_a;
      }
    }
    else
    {
      if (LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                                (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_B) != 0U)
      {
        p_area_info->priv_state = (hal_gtzc_privilege_attr_t)p_area_info->priv_state_subregion_b;
      }
    }
  }

  /* Current watermark memory granularity block in part 5 */
  else if ((area_offset_byte >= (p_area_info->end_subregion_a * p_area_info->granularity)) &&
           (area_offset_byte >= (p_area_info->end_subregion_b * p_area_info->granularity)))
  {
    p_area_info->offset_byte =
      (((p_area_info->end_subregion_a * p_area_info->granularity) <= \
        (p_area_info->end_subregion_b * p_area_info->granularity)) ? \
       (p_area_info->end_subregion_b * p_area_info->granularity) :  \
       (p_area_info->end_subregion_a * p_area_info->granularity));

    p_area_info->size_byte   = area_offset_byte + p_area_info->granularity - p_area_info->offset_byte;
  }

  /* Current watermark memory granularity block in part 4 */
  else
  {
    p_area_info->offset_byte =
      (((p_area_info->end_subregion_a * p_area_info->granularity) <= \
        (p_area_info->end_subregion_b * p_area_info->granularity)) ? \
       (p_area_info->end_subregion_a * p_area_info->granularity) :  \
       (p_area_info->end_subregion_b * p_area_info->granularity));

    p_area_info->size_byte   = area_offset_byte + p_area_info->granularity - p_area_info->offset_byte;

    if ((p_area_info->end_subregion_a * p_area_info->granularity) < (p_area_info->end_subregion_b *
                                                                     p_area_info->granularity))
    {
      if (LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                                (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_B) != 0U)
      {
        p_area_info->sec_state  = (hal_gtzc_security_attr_t)p_area_info->sec_state_subregion_b;
        p_area_info->priv_state = (hal_gtzc_privilege_attr_t)p_area_info->priv_state_subregion_b;
      }
    }
    else
    {
      if (LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                                (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_A) != 0U)
      {
        p_area_info->sec_state  = (hal_gtzc_security_attr_t)p_area_info->sec_state_subregion_a;
        p_area_info->priv_state = (hal_gtzc_privilege_attr_t)p_area_info->priv_state_subregion_a;
      }
    }
  }
}

/**
  * @brief  Get the selected watermark area details (offset_byte, size_byte, security attribute and privilege attribute)
  *         when no overlap of subregion A and subregion B.
  * @param  memory           Watermark memory\n
  *                          An element of \ref hal_gtzc_watermark_mem_t enumeration.
  * @param  area_offset_byte Index of current block of watermarmk area memory.
  * @param  p_area_info      Pointer to watermark area info.
  */
static void GTZC_GetNotOverlappedAreasAttr(hal_gtzc_watermark_mem_t memory, uint32_t area_offset_byte,
                                           hal_gtzc_watermark_area_info_t *p_area_info)
{
  /* Current watermark memory granularity block in first part */
  if ((area_offset_byte < (p_area_info->start_subregion_a * p_area_info->granularity)) &&
      (area_offset_byte < (p_area_info->start_subregion_b * p_area_info->granularity)))
  {
    p_area_info->offset_byte = 0U;
    p_area_info->size_byte   = area_offset_byte + p_area_info->granularity - p_area_info->offset_byte;
  }

  /* Current watermark memory granularity block in second part */
  else if ((area_offset_byte >= (p_area_info->start_subregion_a * p_area_info->granularity)) &&
           (area_offset_byte < (p_area_info->end_subregion_a * p_area_info->granularity)))
  {
    p_area_info->offset_byte = (p_area_info->start_subregion_a * p_area_info->granularity);
    p_area_info->size_byte   = area_offset_byte + p_area_info->granularity - p_area_info->offset_byte;

    if (LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                              (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_A) != 0U)
    {
      p_area_info->sec_state  = (hal_gtzc_security_attr_t)p_area_info->sec_state_subregion_a;
      p_area_info->priv_state = (hal_gtzc_privilege_attr_t)p_area_info->priv_state_subregion_a;
    }
  }

  /* Current watermark memory granularity block in third part */
  else if ((area_offset_byte >= (p_area_info->start_subregion_b * p_area_info->granularity)) &&
           (area_offset_byte < (p_area_info->end_subregion_b * p_area_info->granularity)))
  {
    p_area_info->offset_byte = (p_area_info->start_subregion_b * p_area_info->granularity);
    p_area_info->size_byte   = area_offset_byte + p_area_info->granularity - p_area_info->offset_byte;

    if (LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion((GTZC_TZSC_WaterMark_TypeDef *)(uint32_t)memory,
                                              (uint32_t)HAL_GTZC_WATERMARK_SUBREGION_B) != 0U)
    {
      p_area_info->sec_state   = (hal_gtzc_security_attr_t)p_area_info->sec_state_subregion_b;
      p_area_info->priv_state  = (hal_gtzc_privilege_attr_t)p_area_info->priv_state_subregion_b;
    }
  }

  /* Current watermark memory granularity block in part 4 */
  else if ((area_offset_byte >= (p_area_info->end_subregion_a * p_area_info->granularity)) &&
           (area_offset_byte >= (p_area_info->end_subregion_b * p_area_info->granularity)))
  {
    p_area_info->offset_byte =
      (((p_area_info->end_subregion_a * p_area_info->granularity) <= \
        (p_area_info->end_subregion_b * p_area_info->granularity)) ? \
       (p_area_info->end_subregion_b * p_area_info->granularity) :  \
       (p_area_info->end_subregion_a * p_area_info->granularity));

    p_area_info->size_byte   = area_offset_byte + p_area_info->granularity - p_area_info->offset_byte;
  }

  /* Current watermark memory granularity block in part 5 */
  else
  {
    p_area_info->offset_byte =
      (((p_area_info->end_subregion_a * p_area_info->granularity) <  \
        (p_area_info->end_subregion_b * p_area_info->granularity)) ? \
       (p_area_info->end_subregion_a * p_area_info->granularity) :  \
       (p_area_info->end_subregion_b * p_area_info->granularity));

    p_area_info->size_byte   = area_offset_byte + p_area_info->granularity - p_area_info->offset_byte;
  }
}

/**
  * @brief  Call the callback of the illegal access to peripherals.
  * @param  active_it     Active interrupts peripherals.
  * @param  tzic_register Peripherals register number.
  */
static void GTZC_IllegalAccessCallbackCall(uint32_t active_it, uint32_t tzic_register)
{
  /* Loop on active_it to check, which ones have been raised */
  for (uint32_t periph_pos = 0U; (active_it >> periph_pos) != 0U; periph_pos++)
  {
    if ((active_it & (1UL << periph_pos)) != 0U)
    {
      /* Call callback function */
      HAL_GTZC_ILLEGALACCESS_Callback((hal_gtzc_periph_t)(uint32_t)(periph_pos + tzic_register));
    }
  }
}
/**
  * @}
  */
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

#endif /* defined(USE_HAL_GTZC_MODULE) && (USE_HAL_GTZC_MODULE == 1U) */

/**
  * @}
  */

/**
  * @}
  */
