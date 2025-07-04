/**
  ******************************************************************************
  * @file    stm32u5xx.h
  * @brief   CMSIS STM32U5xx Device Peripheral Access Layer Header File.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c.
  *          This file allows to select the STM32U5xx device used in the target
  *          application.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32u5xx
  * @{
  */

#ifndef STM32U5XX_H
#define STM32U5XX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(USE_EXTERNAL_ENV)
#include "stm32_external_env.h"
#endif /* USE_EXTERNAL_ENV */

/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * @brief STM32 Family
  */
#if !defined (STM32U5)
#define STM32U5
#endif /* STM32U5 */

/**
  * @brief STM32U5xx CMSIS Device version number 2.0.0
  */
#define STM32U5_CMSIS_VERSION_MAIN   (2) /*!< [31:24] main version */
#define STM32U5_CMSIS_VERSION_SUB1   (0) /*!< [23:16] sub1 version */
#define STM32U5_CMSIS_VERSION_SUB2   (0) /*!< [15:8]  sub2 version */
#define STM32U5_CMSIS_VERSION_RC     (0) /*!< [7:0]  release candidate */
#define STM32U5_CMSIS_VERSION        ((STM32U5_CMSIS_VERSION_MAIN << 24U)   \
                                      | (STM32U5_CMSIS_VERSION_SUB1 << 16U) \
                                      | (STM32U5_CMSIS_VERSION_SUB2 << 8U ) \
                                      | (STM32U5_CMSIS_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(STM32U535xx)
#include "stm32u535xx.h"
#elif defined(STM32U545xx)
#include "stm32u545xx.h"
#elif defined(STM32U575xx)
#include "stm32u575xx.h"
#elif defined(STM32U585xx)
#include "stm32u585xx.h"
#elif defined(STM32U595xx)
#include "stm32u595xx.h"
#elif defined(STM32U599xx)
#include "stm32u599xx.h"
#elif defined(STM32U5A5xx)
#include "stm32u5a5xx.h"
#elif defined(STM32U5A9xx)
#include "stm32u5a9xx.h"
#elif defined(STM32U5F7xx)
#include "stm32u5f7xx.h"
#elif defined(STM32U5F9xx)
#include "stm32u5f9xx.h"
#elif defined(STM32U5G7xx)
#include "stm32u5g7xx.h"
#elif defined(STM32U5G9xx)
#include "stm32u5g9xx.h"
#else
#error "Please select first the target STM32U5xx device used in your application"
#endif

/**
  * @}
  */

/** @addtogroup Exported_types
  * @{
  */

/* Legacy enumerations */

typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  SUCCESS = 0,
  ERROR = !SUCCESS
} ErrorStatus;

/**
  * @}
  */

/** @addtogroup Exported_macros
  * @{
  */

#define STM32_POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))

#define STM32_UNUSED(x)             ((void)(x))

#define STM32_SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define STM32_CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define STM32_READ_BIT(REG, BIT)    ((REG) & (BIT))

#define STM32_CLEAR_REG(REG)        ((REG) = 0U)

#define STM32_WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define STM32_READ_REG(REG)         ((REG))

#define STM32_MODIFY_REG(REG, CLEARMASK, SETMASK)                              \
  STM32_WRITE_REG((REG), (((STM32_READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define STM32_IS_BIT_SET(REG, BIT)  (((REG) & (BIT)) == (BIT))

#define STM32_IS_BIT_CLR(REG, BIT)  (((REG) & (BIT)) == 0U)

/* Use of CMSIS compiler intrinsics for register exclusive access */

/* Atomic 32-bit register access macro to set one or several bits */
#define STM32_ATOMIC_SET_BIT_32(REG, BIT)                                      \
  do {                                                                         \
    uint32_t val;                                                              \
    do {                                                                       \
      val = __LDREXW((__IO uint32_t *)&(REG)) | (BIT);                         \
    } while ((__STREXW(val,(__IO uint32_t *)&(REG))) != 0U);                   \
  } while(0)

/* Atomic 32-bit register access macro to clear one or several bits */
#define STM32_ATOMIC_CLEAR_BIT_32(REG, BIT)                                    \
  do {                                                                         \
    uint32_t val;                                                              \
    do {                                                                       \
      val = __LDREXW((__IO uint32_t *)&(REG)) & ~(BIT);                        \
    } while ((__STREXW(val,(__IO uint32_t *)&(REG))) != 0U);                   \
  } while(0)

/* Atomic 32-bit register access macro to clear and set one or several bits */
#define STM32_ATOMIC_MODIFY_REG_32(REG, CLEARMSK, SETMASK)                     \
  do {                                                                         \
    uint32_t val;                                                              \
    do {                                                                       \
      val = (__LDREXW((__IO uint32_t *)&(REG)) & ~(CLEARMSK)) | (SETMASK);     \
    } while ((__STREXW(val,(__IO uint32_t *)&(REG))) != 0U);                   \
  } while(0)

/* Atomic 16-bit register access macro to set one or several bits */
#define STM32_ATOMIC_SET_BIT_16(REG, BIT)                                      \
  do {                                                                         \
    uint16_t val;                                                              \
    do {                                                                       \
      val = __LDREXH((__IO uint16_t *)&(REG)) | (BIT);                         \
    } while ((__STREXH(val,(__IO uint16_t *)&(REG))) != 0U);                   \
  } while(0)

/* Atomic 16-bit register access macro to clear one or several bits */
#define STM32_ATOMIC_CLEAR_BIT_16(REG, BIT)                                    \
  do {                                                                         \
    uint16_t val;                                                              \
    do {                                                                       \
      val = __LDREXH((__IO uint16_t *)&(REG)) & ~(BIT);                        \
    } while ((__STREXH(val,(__IO uint16_t *)&(REG))) != 0U);                   \
  } while(0)

/* Atomic 16-bit register access macro to clear and set one or several bits */
#define STM32_ATOMIC_MODIFY_REG_16(REG, CLEARMSK, SETMASK)                     \
  do {                                                                         \
    uint16_t val;                                                              \
    do {                                                                       \
      val = (__LDREXH((__IO uint16_t *)&(REG)) & ~(CLEARMSK)) | (SETMASK);     \
    } while ((__STREXH(val,(__IO uint16_t *)&(REG))) != 0U);                   \
  } while(0)

/* Atomic 8-bit register access macro to set one or several bits */
#define STM32_ATOMIC_SET_BIT_8(REG, BIT)                                       \
  do {                                                                         \
    uint8_t val;                                                               \
    do {                                                                       \
      val = __LDREXB((__IO uint8_t *)&(REG)) | (BIT);                          \
    } while ((__STREXB(val,(__IO uint8_t *)&(REG))) != 0U);                    \
  } while(0)

/* Atomic 8-bit register access macro to clear one or several bits */
#define STM32_ATOMIC_CLEAR_BIT_8(REG, BIT)                                     \
  do {                                                                         \
    uint8_t val;                                                               \
    do {                                                                       \
      val = __LDREXB((__IO uint8_t *)&(REG)) & ~(BIT);                         \
    } while ((__STREXB(val,(__IO uint8_t *)&(REG))) != 0U);                    \
  } while(0)

/* Atomic 8-bit register access macro to clear and set one or several bits */
#define STM32_ATOMIC_MODIFY_REG_8(REG, CLEARMSK, SETMASK)                      \
  do {                                                                         \
    uint8_t val;                                                               \
    do {                                                                       \
      val = (__LDREXB((__IO uint8_t *)&(REG)) & ~(CLEARMSK)) | (SETMASK);      \
    } while ((__STREXB(val,(__IO uint8_t *)&(REG))) != 0U);                    \
  } while(0)

/* Legacy aliasing */
#define POSITION_VAL       STM32_POSITION_VAL
#define SET_BIT            STM32_SET_BIT
#define CLEAR_BIT          STM32_CLEAR_BIT
#define READ_BIT           STM32_READ_BIT
#define CLEAR_REG          STM32_CLEAR_REG
#define WRITE_REG          STM32_WRITE_REG
#define READ_REG           STM32_READ_REG
#define MODIFY_REG         STM32_MODIFY_REG
#define IS_BIT_SET         STM32_IS_BIT_SET
#define IS_BIT_CLR         STM32_IS_BIT_CLR
#define ATOMIC_SET_BIT     STM32_ATOMIC_SET_BIT_32
#define ATOMIC_CLEAR_BIT   STM32_ATOMIC_CLEAR_BIT_32
#define ATOMIC_MODIFY_REG  STM32_ATOMIC_MODIFY_REG_32
#define ATOMIC_SETH_BIT    STM32_ATOMIC_SET_BIT_16
#define ATOMIC_CLEARH_BIT  STM32_ATOMIC_CLEAR_BIT_16
#define ATOMIC_MODIFYH_REG STM32_ATOMIC_MODIFY_REG_16
#define ATOMIC_SETB_BIT    STM32_ATOMIC_SET_BIT_8
#define ATOMIC_CLEARB_BIT  STM32_ATOMIC_CLEAR_BIT_8
#define ATOMIC_MODIFYB_REG STM32_ATOMIC_MODIFY_REG_8

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_H */
/**
  * @}
  */

/**
  * @}
  */
