/**
  ******************************************************************************
  * @file    stm32u5xx_ll_dcache.h
  * @brief   Header file of DCACHE LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_LL_DCACHE_H
#define STM32U5xx_LL_DCACHE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined (DCACHE1) || defined (DCACHE2)

/** @defgroup DCACHE_LL DCACHE
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup DCACHE_Private_Constants DCACHE Private Constants
  * @{
  */
#define LL_DCACHE_COMMAND_NO_OPERATION                    0U
#define LL_DCACHE_COMMAND_CLEAN_BY_ADDR                   DCACHE_CR_CACHECMD_0
#define LL_DCACHE_COMMAND_INVALIDATE_BY_ADDR              DCACHE_CR_CACHECMD_1
#define LL_DCACHE_COMMAND_CLEAN_INVALIDATE_BY_ADDR        (DCACHE_CR_CACHECMD_0|DCACHE_CR_CACHECMD_1)
/**
  * @}
  */

/** @defgroup DCACHE_Read_Burst_Type Remapped Output burst type
  * @{
  */
#define LL_DCACHE_READ_BURST_WRAP         0U                    /*!< WRAP */
#define LL_DCACHE_READ_BURST_INCR         DCACHE_CR_HBURST      /*!< INCR */
/**
  * @}
  */

/** @defgroup DCACHE_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_DCACHE_READ_REG function
  * @{
  */
#define LL_DCACHE_SR_ERRF              DCACHE_SR_ERRF      /*!< Cache error flag */
#define LL_DCACHE_SR_BUSYF             DCACHE_SR_BUSYF     /*!< Busy flag */
#define LL_DCACHE_SR_CMDENDF           DCACHE_SR_CMDENDF   /*!< Command end flag */
#define LL_DCACHE_SR_BSYENDF           DCACHE_SR_BSYENDF   /*!< Full invalidate busy end flag */
#define LL_DCACHE_SR_BUSYCMDF          DCACHE_SR_BUSYCMDF  /*!< Command busy flag */
/**
  * @}
  */

/** @defgroup DCACHE_LL_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with LL_DCACHE_WRITE_REG function
  * @{
  */
#define LL_DCACHE_FCR_CERRF            DCACHE_FCR_CERRF    /*!< Cache error flag */
#define LL_DCACHE_FCR_CBSYENDF         DCACHE_FCR_CBSYENDF /*!< Full invalidate busy end flag */
#define LL_DCACHE_FCR_CCMDENDF         DCACHE_FCR_CCMDENDF /*!< Command end flag*/
/**
  * @}
  */

/** @defgroup DCACHE_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_DCACHE_READ_REG and  LL_DCACHE_WRITE_REG functions
  * @{
  */
#define LL_DCACHE_IER_BSYENDIE         DCACHE_IER_BSYENDIE /*!< Busy end interrupt */
#define LL_DCACHE_IER_ERRIE            DCACHE_IER_ERRIE    /*!< Cache error interrupt */
#define LL_DCACHE_IER_CMDENDIE         DCACHE_IER_CMDENDIE /*!< Command end interrupt */
/**
  * @}
  */

/** @defgroup DCACHE_Monitor_Type Monitor type
  * @{
  */
#define LL_DCACHE_MONITOR_READ_HIT        DCACHE_CR_RHITMEN   /*!< Read Hit monitoring */
#define LL_DCACHE_MONITOR_READ_MISS       DCACHE_CR_RMISSMEN  /*!< Read Miss monitoring */
#define LL_DCACHE_MONITOR_WRITE_HIT       DCACHE_CR_WHITMEN   /*!< Write Hit monitoring */
#define LL_DCACHE_MONITOR_WRITE_MISS      DCACHE_CR_WMISSMEN  /*!< Write Miss monitoring */
#define LL_DCACHE_MONITOR_ALL             (DCACHE_CR_RHITMEN | DCACHE_CR_RMISSMEN \
                                           | DCACHE_CR_WHITMEN | DCACHE_CR_WMISSMEN)
/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup DCACHE_LL_Exported_Macros DCACHE Exported Macros
  * @{
  */

/** @defgroup DCACHE_LL_EM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in DCACHE register
  * @param  instance DCACHE Instance
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_DCACHE_WRITE_REG(instance, reg, value) WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in DCACHE register
  * @param  instance DCACHE Instance
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_DCACHE_READ_REG(instance, reg) READ_REG((instance)->reg)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup DCACHE_LL_Exported_Functions DCACHE Exported Functions
  * @{
  */

/** @defgroup DCACHE_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Enable the selected DCACHE instance.
  * @rmtoll
  *  CR       EN           LL_DCACHE_Enable
  * @param  dcachex DCACHE instance
  */
__STATIC_INLINE void LL_DCACHE_Enable(DCACHE_TypeDef *dcachex)
{
  SET_BIT(dcachex->CR, DCACHE_CR_EN);
}

/**
  * @brief  Disable the selected DCACHE instance.
  * @rmtoll
  *  CR       EN           LL_DCACHE_Disable
  * @param  dcachex DCACHE instance
  */
__STATIC_INLINE void LL_DCACHE_Disable(DCACHE_TypeDef *dcachex)
{
  CLEAR_BIT(dcachex->CR, DCACHE_CR_EN);
}

/**
  * @brief  Get the selected DCACHE instance enable state.
  * @rmtoll
  *  CR       EN           LL_DCACHE_IsEnabled
  * @param  dcachex DCACHE instance
  * @retval 0: DCACHE is disabled, 1: DCACHE is enabled.
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsEnabled(const DCACHE_TypeDef *dcachex)
{
  return ((READ_BIT(dcachex->CR, DCACHE_CR_EN) == (DCACHE_CR_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the DCACHE instance start command address.
  * @rmtoll
  *  CR       CMDRSADDRR          LL_DCACHE_SetStartAddress
  * @param  dcachex DCACHE instance
  * @param  addr DCACHE command start address (Clean, Invalidate or Clean and Invalidate).
  */
__STATIC_INLINE void LL_DCACHE_SetStartAddress(DCACHE_TypeDef *dcachex, uint32_t addr)
{
  WRITE_REG(dcachex->CMDRSADDRR, addr);
}

/**
  * @brief  Get the DCACHE command start address.
  * @rmtoll
  *  CR       CMDRSADDRR         LL_DCACHE_GetStartAddress
  * @param  dcachex DCACHE instance
  * @retval Start address of DCACHE command
  */
__STATIC_INLINE uint32_t LL_DCACHE_GetStartAddress(const DCACHE_TypeDef *dcachex)
{
  return (uint32_t)(READ_REG(dcachex->CMDRSADDRR));
}

/**
  * @brief  Set the DCACHE instance End command address.
  * @rmtoll
  *  CR       CMDREADDRR          LL_DCACHE_SetEndAddress
  * @param  dcachex DCACHE instance
  * @param  addr DCACHE command end address (Clean, Invalidate or Clean and Invalidate).
  */
__STATIC_INLINE void LL_DCACHE_SetEndAddress(DCACHE_TypeDef *dcachex, uint32_t addr)
{
  WRITE_REG(dcachex->CMDREADDRR, addr);
}

/**
  * @brief  Get the DCACHE command End address.
  * @rmtoll
  *  CR       CMDREADDRR          LL_DCACHE_GetEndAddress
  * @param  dcachex DCACHE instance
  * @retval End address of DCACHE command
  */
__STATIC_INLINE uint32_t LL_DCACHE_GetEndAddress(const DCACHE_TypeDef *dcachex)
{
  return (uint32_t)(READ_REG(dcachex->CMDREADDRR));
}

/**
  * @brief  Set DCACHE command.
  * @rmtoll
  *  CR       CACHECMD          LL_DCACHE_SetCommand
  * @param  dcachex DCACHE instance
  * @param  command Command to be applied for the DCACHE
  *         Command can be one of the following values:
  *         @arg @ref LL_DCACHE_COMMAND_INVALIDATE_BY_ADDR
  *         @arg @ref LL_DCACHE_COMMAND_CLEAN_BY_ADDR
  *         @arg @ref LL_DCACHE_COMMAND_CLEAN_INVALIDATE_BY_ADDR
  *         @arg @ref LL_DCACHE_COMMAND_NO_OPERATION
  */
__STATIC_INLINE void LL_DCACHE_SetCommand(DCACHE_TypeDef *dcachex, uint32_t command)
{
  MODIFY_REG(dcachex->CR, DCACHE_CR_CACHECMD, command);
}

/**
  * @brief  Set DCACHE command.
  * @rmtoll
  *  CR       CACHECMD          LL_DCACHE_GetCommand
  * @param  dcachex DCACHE instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DCACHE_COMMAND_NO_OPERATION
  *         @arg @ref LL_DCACHE_COMMAND_CLEAN_BY_ADDR
  *         @arg @ref LL_DCACHE_COMMAND_INVALIDATE_BY_ADDR
  *         @arg @ref LL_DCACHE_COMMAND_CLEAN_INVALIDATE_BY_ADDR
  */
__STATIC_INLINE uint32_t LL_DCACHE_GetCommand(const DCACHE_TypeDef *dcachex)
{
  return (uint32_t)(READ_BIT(dcachex->CR, DCACHE_CR_CACHECMD));
}

/**
  * @brief  Launch DCACHE Command.
  * @rmtoll
  *  CR       CACHECMD          LL_DCACHE_StartCommand
  * @param  dcachex DCACHE instance
  */
__STATIC_INLINE void LL_DCACHE_StartCommand(DCACHE_TypeDef *dcachex)
{
  SET_BIT(dcachex->CR, DCACHE_CR_STARTCMD);
}

/**
  * @brief  Set requested read burst type.
  * @rmtoll
  *  CR       HBURST          LL_DCACHE_SetReadBurstType
  * @param  dcachex DCACHE instance
  * @param  read_burst_type Burst type to be applied for Data Cache
  *         Burst type can be one of the following values:
  *         @arg @ref LL_DCACHE_READ_BURST_WRAP
  *         @arg @ref LL_DCACHE_READ_BURST_INCR
  */
__STATIC_INLINE void LL_DCACHE_SetReadBurstType(DCACHE_TypeDef *dcachex, uint32_t read_burst_type)
{
  MODIFY_REG(dcachex->CR, DCACHE_CR_HBURST, read_burst_type);
}

/**
  * @brief  Get requested read burst type.
  * @rmtoll
  *  CR       HBURST          LL_DCACHE_GetReadBurstType
  * @param  dcachex DCACHE instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DCACHE_READ_BURST_WRAP
  *         @arg @ref LL_DCACHE_READ_BURST_INCR
  */
__STATIC_INLINE uint32_t LL_DCACHE_GetReadBurstType(const DCACHE_TypeDef *dcachex)
{
  return (uint32_t)(READ_BIT(dcachex->CR, DCACHE_CR_HBURST));
}

/**
  * @brief  Invalidate the DCACHE.
  * @rmtoll
  *  CR       CACHEINV          LL_DCACHE_Invalidate
  * @param  dcachex DCACHE instance
  */
__STATIC_INLINE void LL_DCACHE_Invalidate(DCACHE_TypeDef *dcachex)
{
  SET_BIT(dcachex->CR, DCACHE_CR_CACHEINV);
}

/**
  * @}
  */


/** @defgroup DCACHE_LL_EF_Monitor Monitor
  * @{
  */

/**
  * @brief  Enable the hit/miss monitor(s).
  * @rmtoll
  *  CR     (RMISSMEN/RHITMEN/WMISSMEN/WHITMEN)       LL_DCACHE_EnableMonitors
  * @param  dcachex DCACHE instance
  * @param  monitors This parameter can be one or a combination of the following values:
  *            @arg LL_DCACHE_MONITOR_READ_HIT
  *            @arg LL_DCACHE_MONITOR_READ_MISS
  *            @arg LL_DCACHE_MONITOR_WRITE_HIT
  *            @arg LL_DCACHE_MONITOR_WRITE_MISS
  *            @arg LL_DCACHE_MONITOR_ALL
  */
__STATIC_INLINE void LL_DCACHE_EnableMonitors(DCACHE_TypeDef *dcachex, uint32_t monitors)
{
  SET_BIT(dcachex->CR, monitors);
}

/**
  * @brief  Disable the hit/miss monitor(s).
  * @rmtoll
  *  CR     (RMISSMEN/RHITMEN/WMISSMEN/WHITMEN)       LL_DCACHE_DisableMonitors
  * @param  dcachex DCACHE instance
  * @param  monitors This parameter can be one or a combination of the following values:
  *            @arg LL_DCACHE_MONITOR_READ_HIT
  *            @arg LL_DCACHE_MONITOR_READ_MISS
  *            @arg LL_DCACHE_MONITOR_WRITE_HIT
  *            @arg LL_DCACHE_MONITOR_WRITE_MISS
  *            @arg LL_DCACHE_MONITOR_ALL
  */
__STATIC_INLINE void LL_DCACHE_DisableMonitors(DCACHE_TypeDef *dcachex, uint32_t monitors)
{
  CLEAR_BIT(dcachex->CR, monitors);
}

/**
  * @brief  Return the hit/miss monitor(s) enable state.
  * @rmtoll
  *  CR     (RMISSMEN/RHITMEN/WMISSMEN/WHITMEN)     LL_DCACHE_IsEnabledMonitors
  * @param  dcachex DCACHE instance
  * @param  monitors This parameter can be one or a combination of the following values:
  *            @arg LL_DCACHE_MONITOR_READ_HIT
  *            @arg LL_DCACHE_MONITOR_READ_MISS
  *            @arg LL_DCACHE_MONITOR_WRITE_HIT
  *            @arg LL_DCACHE_MONITOR_WRITE_MISS
  *            @arg LL_DCACHE_MONITOR_ALL
  * @retval State of parameter value (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsEnabledMonitors(const DCACHE_TypeDef *dcachex, uint32_t monitors)
{
  return (((READ_BIT(dcachex->CR, (LL_DCACHE_MONITOR_ALL)) & monitors) == (monitors)) ? 1UL : 0UL);
}

/**
  * @brief  Reset the performance monitoring.
  * @rmtoll
  *  CR     (RHITMRST/RMISSMRST/WHITMRST/WMISSMRST)     LL_DCACHE_ResetMonitors
  * @param  dcachex DCACHE instance
  * @param  monitors Monitoring type
  *         This parameter can be a combination of the following values:
  *            @arg LL_DCACHE_MONITOR_READ_HIT
  *            @arg LL_DCACHE_MONITOR_READ_MISS
  *            @arg LL_DCACHE_MONITOR_WRITE_HIT
  *            @arg LL_DCACHE_MONITOR_WRITE_MISS
  *            @arg LL_DCACHE_MONITOR_ALL
  */
__STATIC_INLINE void LL_DCACHE_ResetMonitors(DCACHE_TypeDef *dcachex, uint32_t monitors)
{
  /* Reset */
  SET_BIT(dcachex->CR, (monitors << 2U));

  /* Release reset */
  CLEAR_BIT(dcachex->CR, (monitors << 2U));
}

/**
  * @brief  Get the Read Hit monitor value.
  * @rmtoll
  *  RHMONR       LL_DCACHE_Monitor_GetReadHitValue
  * @param  dcachex DCACHE instance
  * @retval Value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DCACHE_Monitor_GetReadHitValue(const DCACHE_TypeDef *dcachex)
{
  return dcachex->RHMONR;
}

/**
  * @brief  Get the Read Miss monitor value.
  * @rmtoll
  *  RMMONR       LL_DCACHE_Monitor_GetReadMissValue
  * @param  dcachex DCACHE instance
  * @retval Value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DCACHE_Monitor_GetReadMissValue(const DCACHE_TypeDef *dcachex)
{
  return dcachex->RMMONR;
}

/**
  * @brief  Get the Write Hit monitor value.
  * @rmtoll
  *  WHMONR       LL_DCACHE_Monitor_GetWriteHitValue
  * @param  dcachex DCACHE instance
  * @retval Value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DCACHE_Monitor_GetWriteHitValue(const DCACHE_TypeDef *dcachex)
{
  return dcachex->WHMONR;
}

/**
  * @brief  Get the Write Miss monitor value.
  * @rmtoll
  *  WMMONR       LL_DCACHE_Monitor_GetWriteMissValue
  * @param  dcachex DCACHE instance
  * @retval Value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DCACHE_Monitor_GetWriteMissValue(const DCACHE_TypeDef *dcachex)
{
  return dcachex->WMMONR;
}

/**
  * @}
  */

/** @defgroup DCACHE_LL_EF_IT_Management IT-Management
  * @{
  */

/**
  * @brief  Enable interrupt(s).
  * @rmtoll
  *  IER         BSYENDIE         LL_DCACHE_EnableIT \n
  *  IER         ERRIE            LL_DCACHE_EnableIT \n
  *  IER         CMDENDIE         LL_DCACHE_EnableIT
  * @param  dcachex DCACHE instance
  * @param  mask Mask
  *         This parameter can be a combination of the following values:
  *            @arg LL_DCACHE_IER_BSYENDIE
  *            @arg LL_DCACHE_IER_ERRIE
  *            @arg LL_DCACHE_IER_CMDENDIE
  */
__STATIC_INLINE void LL_DCACHE_EnableIT(DCACHE_TypeDef *dcachex, uint32_t mask)
{
  SET_BIT(dcachex->IER, mask);
}

/**
  * @brief  Disable interrupt(s).
  * @rmtoll
  *  IER         BSYENDIE         LL_DCACHE_DisableIT \n
  *  IER         ERRIE            LL_DCACHE_DisableIT \n
  *  IER         CMDENDIE         LL_DCACHE_DisableIT
  * @param  dcachex DCACHE instance
  * @param  mask Mask
  *         This parameter can be a combination of the following values:
  *            @arg LL_DCACHE_IER_BSYENDIE
  *            @arg LL_DCACHE_IER_ERRIE
  *            @arg LL_DCACHE_IER_CMDENDIE
  */
__STATIC_INLINE void LL_DCACHE_DisableIT(DCACHE_TypeDef *dcachex, uint32_t mask)
{
  CLEAR_BIT(dcachex->IER, mask);
}

/**
  * @brief  Indicate whether the interrupt(s) is(are) enabled.
  * @rmtoll
  *  IER         BSYENDIE         LL_DCACHE_IsEnabledIT \n
  *  IER         ERRIE            LL_DCACHE_IsEnabledIT \n
  *  IER         CMDENDIE         LL_DCACHE_IsEnabledIT
  * @param  dcachex DCACHE instance
  * @param  mask Mask
  *         This parameter can be a combination of the following values:
  *            @arg LL_DCACHE_IER_BSYENDIE
  *            @arg LL_DCACHE_IER_ERRIE
  *            @arg LL_DCACHE_IER_CMDENDIE
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsEnabledIT(const DCACHE_TypeDef *dcachex, uint32_t mask)
{
  return ((READ_BIT(dcachex->IER, mask) == (mask)) ? 1UL : 0UL);
}

/**
  * @brief  Enable busy end interrupt.
  * @rmtoll
  *  IER         BSYENDIE          LL_DCACHE_EnableIT_BSYEND
  * @param  dcachex DCACHE instance
  */
__STATIC_INLINE void LL_DCACHE_EnableIT_BSYEND(DCACHE_TypeDef *dcachex)
{
  SET_BIT(dcachex->IER, LL_DCACHE_IER_BSYENDIE);
}

/**
  * @brief  Disable busy end interrupt.
  * @rmtoll
  *  IER         BSYENDIE          LL_DCACHE_DisableIT_BSYEND
  * @param  dcachex DCACHE instance
  */
__STATIC_INLINE void LL_DCACHE_DisableIT_BSYEND(DCACHE_TypeDef *dcachex)
{
  CLEAR_BIT(dcachex->IER, LL_DCACHE_IER_BSYENDIE);
}

/**
  * @brief  Indicate whether the busy end interrupt is enabled.
  * @rmtoll
  *  IER         BSYENDIE          LL_DCACHE_IsEnabledIT_BSYEND
  * @param  dcachex DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsEnabledIT_BSYEND(const DCACHE_TypeDef *dcachex)
{
  return ((READ_BIT(dcachex->IER, LL_DCACHE_IER_BSYENDIE) == (LL_DCACHE_IER_BSYENDIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable error interrupt.
  * @rmtoll
  *  IER         ERRIE          LL_DCACHE_EnableIT_ERR
  * @param  dcachex DCACHE instance
  */
__STATIC_INLINE void LL_DCACHE_EnableIT_ERR(DCACHE_TypeDef *dcachex)
{
  SET_BIT(dcachex->IER, LL_DCACHE_IER_ERRIE);
}

/**
  * @brief  Disable error interrupt.
  * @rmtoll
  *  IER         ERRIE          LL_DCACHE_DisableIT_ERR
  * @param  dcachex DCACHE instance
  */
__STATIC_INLINE void LL_DCACHE_DisableIT_ERR(DCACHE_TypeDef *dcachex)
{
  CLEAR_BIT(dcachex->IER, LL_DCACHE_IER_ERRIE);
}

/**
  * @brief  Indicate whether the error interrupt is enabled.
  * @rmtoll
  *  IER         ERRIE          LL_DCACHE_IsEnabledIT_ERR
  * @param  dcachex DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsEnabledIT_ERR(const DCACHE_TypeDef *dcachex)
{
  return ((READ_BIT(dcachex->IER, LL_DCACHE_IER_ERRIE) == (LL_DCACHE_IER_ERRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable command end interrupt.
  * @rmtoll
  *  IER         CMDENDIE         LL_DCACHE_EnableIT_CMDEND
  * @param  dcachex DCACHE instance
  */
__STATIC_INLINE void LL_DCACHE_EnableIT_CMDEND(DCACHE_TypeDef *dcachex)
{
  SET_BIT(dcachex->IER, LL_DCACHE_IER_CMDENDIE);
}

/**
  * @brief  Disable command end interrupt.
  * @rmtoll
  *  IER         CMDENDIE         LL_DCACHE_DisableIT_CMDEND
  * @param  dcachex DCACHE instance
  */
__STATIC_INLINE void LL_DCACHE_DisableIT_CMDEND(DCACHE_TypeDef *dcachex)
{
  CLEAR_BIT(dcachex->IER, LL_DCACHE_IER_CMDENDIE);
}

/**
  * @brief  Indicate whether the command end interrupt is enabled.
  * @rmtoll
  *  IER         CMDENDIE          LL_DCACHE_IsEnabledIT_CMDEND
  * @param  dcachex DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsEnabledIT_CMDEND(const DCACHE_TypeDef *dcachex)
{
  return ((READ_BIT(dcachex->IER, LL_DCACHE_IER_CMDENDIE) == (LL_DCACHE_IER_CMDENDIE)) ? 1UL : 0UL);
}

/**
  * @brief  Clear flag(s).
  * @rmtoll
  *  FCR      CBSYENDF        LL_DCACHE_ClearFlag \n
  *  FCR      CERRF           LL_DCACHE_ClearFlag \n
  *  FCR      CCMDENDF        LL_DCACHE_ClearFlag
  * @param  dcachex DCACHE instance
  * @param  mask Mask
  *         This parameter can be a combination of the following values:
  *            @arg LL_DCACHE_FCR_CBSYENDF
  *            @arg LL_DCACHE_FCR_CCMDENDF
  *            @arg LL_DCACHE_FCR_CERRF
  */
__STATIC_INLINE void LL_DCACHE_ClearFlag(DCACHE_TypeDef *dcachex, uint32_t mask)
{
  WRITE_REG(dcachex->FCR, mask);
}

/**
  * @brief  Clear full invalidate busy end flag.
  * @rmtoll
  *  FCR      CBSYENDF         LL_DCACHE_ClearFlag_BSYEND
  * @param  dcachex DCACHE instance
  */
__STATIC_INLINE void LL_DCACHE_ClearFlag_BSYEND(DCACHE_TypeDef *dcachex)
{
  WRITE_REG(dcachex->FCR, LL_DCACHE_FCR_CBSYENDF);
}

/**
  * @brief  Clear cache error flag.
  * @rmtoll
  *  FCR      CERRF        LL_DCACHE_ClearFlag_ERR
  * @param  dcachex DCACHE instance
  */
__STATIC_INLINE void LL_DCACHE_ClearFlag_ERR(DCACHE_TypeDef *dcachex)
{
  WRITE_REG(dcachex->FCR, LL_DCACHE_FCR_CERRF);
}

/**
  * @brief  Clear command end flag.
  * @rmtoll
  *  FCR      CCMDENDF        LL_DCACHE_ClearFlag_CMDEND
  * @param  dcachex DCACHE instance
  */
__STATIC_INLINE void LL_DCACHE_ClearFlag_CMDEND(DCACHE_TypeDef *dcachex)
{
  WRITE_REG(dcachex->FCR, LL_DCACHE_FCR_CCMDENDF);
}

/**
  * @brief  Get flag DCACHE.
  * @rmtoll
  *  SR      BUSYF            LL_DCACHE_IsActiveFlag \n
  *  SR      BSYENDF          LL_DCACHE_IsActiveFlag \n
  *  SR      ERRF             LL_DCACHE_IsActiveFlag \n
  *  SR      BUSYCMDF         LL_DCACHE_IsActiveFlag \n
  *  SR      CMDENDF          LL_DCACHE_IsActiveFlag
  * @param  dcachex DCACHE instance
  * @param  mask Mask
  *         This parameter can be a combination of the following values:
  *            @arg LL_DCACHE_SR_BUSYF
  *            @arg LL_DCACHE_SR_BSYENDF
  *            @arg LL_DCACHE_SR_ERRF
  *            @arg LL_DCACHE_SR_CMDENDF
  *            @arg LL_DCACHE_SR_BUSYCMDF
  * @retval Return 1 if at least one flag is set, else 0.
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsActiveFlag(const DCACHE_TypeDef *dcachex, uint32_t mask)
{
  return ((READ_BIT(dcachex->SR, mask) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Get flag DCACHE busy.
  * @rmtoll
  *  SR      BUSYF            LL_DCACHE_IsActiveFlag_BUSY
  * @param  dcachex DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsActiveFlag_BUSY(const DCACHE_TypeDef *dcachex)
{
  return ((READ_BIT(dcachex->SR, LL_DCACHE_SR_BUSYF) == (LL_DCACHE_SR_BUSYF)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag DCACHE busy end.
  * @rmtoll
  *  SR      BSYENDF            LL_DCACHE_IsActiveFlag_BSYEND
  * @param  dcachex DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsActiveFlag_BSYEND(const DCACHE_TypeDef *dcachex)
{
  return ((READ_BIT(dcachex->SR, LL_DCACHE_SR_BSYENDF) == (LL_DCACHE_SR_BSYENDF)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag DCACHE error.
  * @rmtoll
  *  SR      ERRF            LL_DCACHE_IsActiveFlag_ERR
  * @param  dcachex DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsActiveFlag_ERR(const DCACHE_TypeDef *dcachex)
{
  return ((READ_BIT(dcachex->SR, LL_DCACHE_SR_ERRF) == (LL_DCACHE_SR_ERRF)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag DCACHE busy command.
  * @rmtoll
  *  SR      BUSYCMDF            LL_DCACHE_IsActiveFlag_BUSYCMD
  * @param  dcachex DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsActiveFlag_BUSYCMD(const DCACHE_TypeDef *dcachex)
{
  return ((READ_BIT(dcachex->SR, LL_DCACHE_SR_BUSYCMDF) == (LL_DCACHE_SR_BUSYCMDF)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag DCACHE command end.
  * @rmtoll
  *  SR      CMDENDF            LL_DCACHE_IsActiveFlag_CMDEND
  * @param  dcachex DCACHE instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DCACHE_IsActiveFlag_CMDEND(const DCACHE_TypeDef *dcachex)
{
  return ((READ_BIT(dcachex->SR, LL_DCACHE_SR_CMDENDF) == (LL_DCACHE_SR_CMDENDF)) ? 1UL : 0UL);
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

#endif /* DCACHE1 || DCACHE2 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_LL_DCACHE_H */
