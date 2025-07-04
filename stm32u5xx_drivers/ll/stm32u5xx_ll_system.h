/**
  **********************************************************************************************************************
  * @file    stm32u5xx_ll_system.h
  * @brief   Header file of LL system module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_LL_SYSTEM_H
#define STM32U5XX_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

/** @defgroup LL_SYSTEM LL system
  * @{
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/

/** @defgroup SYSTEM_LL_Exported_Constants SYSTEM Exported Constants
  * @{
  */

/** @defgroup DEVICE_ID_PACKAGE Device package identification
  * @{
  */
#define LL_ID_PACKAGE_LQFP64           0x00000000U /*!< Package LQFP64 */
#define LL_ID_PACKAGE_LQFP100          0x00000002U /*!< Package LQFP100 */
#define LL_ID_PACKAGE_UFBGA132         0x00000003U /*!< Package UFBGA132 */
#define LL_ID_PACKAGE_LQFP144          0x00000004U /*!< Package LQFP144 */
#define LL_ID_PACKAGE_LQFP48           0x00000005U /*!< Package LQFP48 */
#define LL_ID_PACKAGE_UFBGA169         0x00000007U /*!< Package UFBGA169 */
#define LL_ID_PACKAGE_LQFP64_SMPS      0x00000008U /*!< Package LQFP64 with internal SMPS */
#define LL_ID_PACKAGE_WLSCP90_SMPS     0x00000009U /*!< Package WLSCP90 with internal SMPS */
#define LL_ID_PACKAGE_LQFP100_SMPS     0x0000000AU /*!< Package LQFP100 with internal SMPS */
#define LL_ID_PACKAGE_UFBGA132_SMPS    0x0000000BU /*!< Package UFBGA132 with internal SMPS */
#define LL_ID_PACKAGE_LQFP144_SMPS     0x0000000CU /*!< Package LQFP144 with internal SMPS */
#define LL_ID_PACKAGE_LQFP48_SMPS      0x0000000DU /*!< Package LQFP48 with internal SMPS */
#define LL_ID_PACKAGE_UFBGA169_SMPS    0x0000000FU /*!< Package UFBGA169 with internal SMPS */
#define LL_ID_PACKAGE_WLCSP144         0x00000010U /*!< Package WLCSP144 */
#define LL_ID_PACKAGE_UFBGA144         0x00000011U /*!< Package UFBGA144 */
#define LL_ID_PACKAGE_WLCSP144_SMPS    0x00000018U /*!< Package WLCSP144 with internal SMPS */
#define LL_ID_PACKAGE_UFBGA144_SMPS    0x00000019U /*!< Package UFBGA144 with internal SMPS */
#define LL_ID_PACKAGE_WLCSP208_SMPS    0x0000001BU /*!< Package WLCSP208 with internal SMPS */
#define LL_ID_PACKAGE_TFBGA216_SMPS    0x0000001CU /*!< Package TFBGA216 with internal SMPS */
#define LL_ID_PACKAGE_UFBGA100_SMPS    0x0000001DU /*!< UFBGA100 with internal SMPS */
#define LL_ID_PACKAGE_WLCSP56_SMPS     0x0000001EU /*!< Package WLCSP56 with internal SMPS */
#define LL_ID_PACKAGE_WLCSP150_SMPS    0x0000001FU /*!< Package WLCSP150 or WLCSP150 DSI with internal SMPS */
/**
  * @}
  */

/** @defgroup PACKAGE_MASK package data mask
  * @{
  */
#define LL_SYSTEM_PACKAGE_MASK 0x1FU /*!< Mask to get package data */
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup LL_System_Exported_Functions LL system exported functions
  * @{
  */

/** @defgroup LL_System_Device_Identification Device identification (electronic signature)
  * @{
  */

/**
  * @brief  Get Word0 of the device unique identifier (UID based on 96 bits)
  * @retval UID[31:0]: X and Y coordinates on the wafer expressed in BCD format
  */
__STATIC_INLINE uint32_t LL_GetUID_Word0(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)UID_BASE)));
}

/**
  * @brief  Get Word1 of the device unique identifier (UID based on 96 bits)
  * @retval UID[63:32]: Wafer number (UID[39:32]) & LOT_NUM[23:0] (UID[63:40])
  */
__STATIC_INLINE uint32_t LL_GetUID_Word1(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)(UID_BASE + 4U))));
}

/**
  * @brief  Get Word2 of the device unique identifier (UID based on 96 bits)
  * @retval UID[95:64]: Lot number (ASCII encoded) - LOT_NUM[55:24]
  */
__STATIC_INLINE uint32_t LL_GetUID_Word2(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)(UID_BASE + 8U))));
}

/**
  * @brief  Get Package type
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ID_PACKAGE_LQFP64
  *         @arg @ref LL_ID_PACKAGE_LQFP100
  *         @arg @ref LL_ID_PACKAGE_UFBGA132
  *         @arg @ref LL_ID_PACKAGE_LQFP144
  *         @arg @ref LL_ID_PACKAGE_LQFP48
  *         @arg @ref LL_ID_PACKAGE_UFBGA169
  *         @arg @ref LL_ID_PACKAGE_LQFP64_SMPS
  *         @arg @ref LL_ID_PACKAGE_WLSCP90_SMPS
  *         @arg @ref LL_ID_PACKAGE_LQFP100_SMPS
  *         @arg @ref LL_ID_PACKAGE_UFBGA132_SMPS
  *         @arg @ref LL_ID_PACKAGE_LQFP144_SMPS
  *         @arg @ref LL_ID_PACKAGE_LQFP48_SMPS
  *         @arg @ref LL_ID_PACKAGE_UFBGA169_SMPS
  *         @arg @ref LL_ID_PACKAGE_WLCSP144
  *         @arg @ref LL_ID_PACKAGE_UFBGA144
  *         @arg @ref LL_ID_PACKAGE_WLCSP144_SMPS
  *         @arg @ref LL_ID_PACKAGE_UFBGA144_SMPS
  *         @arg @ref LL_ID_PACKAGE_WLCSP208_SMPS
  *         @arg @ref LL_ID_PACKAGE_TFBGA216_SMPS
  *         @arg @ref LL_ID_PACKAGE_UFBGA100_SMPS
  *         @arg @ref LL_ID_PACKAGE_WLCSP56_SMPS
  *         @arg @ref LL_ID_PACKAGE_WLCSP150_SMPS
  */
__STATIC_INLINE uint32_t LL_GetPackageType(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)PACKAGE_BASE)) & LL_SYSTEM_PACKAGE_MASK);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_LL_SYSTEM_H */
