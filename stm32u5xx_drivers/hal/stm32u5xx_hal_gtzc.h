/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_gtzc.h
  * @brief   Header file of GTZC HAL module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_HAL_GTZC_H
#define STM32U5XX_HAL_GTZC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_gtzc.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup GTZC GTZC
  * @{
  */
/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_Exported_Types GTZC Exported Types
  * @{
  */

/*! GTZC Secure attribute */
typedef enum
{
  HAL_GTZC_ATTR_NSEC = LL_GTZC_ATTR_NSEC, /*!< Non-secure attribute */
  HAL_GTZC_ATTR_SEC  = LL_GTZC_ATTR_SEC   /*!< Secure attribute     */
} hal_gtzc_security_attr_t;

/*! GTZC Privilege attribute */
typedef enum
{
  HAL_GTZC_ATTR_NPRIV = LL_GTZC_ATTR_NPRIV, /*!< Non-privilege attribute */
  HAL_GTZC_ATTR_PRIV  = LL_GTZC_ATTR_PRIV   /*!< Privilege attribute     */
} hal_gtzc_privilege_attr_t;

/*! GTZC Attribute configuration structure definition */
typedef struct
{
  hal_gtzc_security_attr_t  sec;  /*!< Security attribute  */

  hal_gtzc_privilege_attr_t priv; /*!< Privilege attribute */

} hal_gtzc_attr_config_t;

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/*! GTZC Watermark memory descriptor structure definition */
typedef struct
{
  uint32_t               offset_byte; /*!< Byte offset of watermark memory area */

  uint32_t               size_byte;   /*!< Byte size of watermark memory area   */

  hal_gtzc_attr_config_t attr;        /*!< Security and privilege attributes    */

} hal_gtzc_watermark_mem_desc_t;

/*! GTZC Watermark memory mapping structure definition */
typedef struct
{
  hal_gtzc_watermark_mem_desc_t mem_desc[LL_GTZC_MPCWM_MAX_DESC]; /*!< Descriptor of watermark memory regions */

} hal_gtzc_watermark_mem_map_t;
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/*! GTZC peripheral identifier */
typedef enum
{
  /* GTZC1 */
  HAL_GTZC_TIM2         = (GTZC_CFGR1_TIM2_Pos         + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral TIM2         */
  HAL_GTZC_TIM3         = (GTZC_CFGR1_TIM3_Pos         + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral TIM3         */
  HAL_GTZC_TIM4         = (GTZC_CFGR1_TIM4_Pos         + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral TIM4         */
  HAL_GTZC_TIM5         = (GTZC_CFGR1_TIM5_Pos         + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral TIM5         */
  HAL_GTZC_TIM6         = (GTZC_CFGR1_TIM6_Pos         + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral TIM6         */
  HAL_GTZC_TIM7         = (GTZC_CFGR1_TIM7_Pos         + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral TIM7         */
  HAL_GTZC_WWDG         = (GTZC_CFGR1_WWDG_Pos         + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral WWDG         */
  HAL_GTZC_IWDG         = (GTZC_CFGR1_IWDG_Pos         + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral IWDG         */
  HAL_GTZC_SPI2         = (GTZC_CFGR1_SPI2_Pos         + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral SPI2         */
#if defined (USART2)
  HAL_GTZC_USART2       = (GTZC_CFGR1_USART2_Pos       + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral USART2       */
#endif /* USART2 */
  HAL_GTZC_USART3       = (GTZC_CFGR1_USART3_Pos       + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral USART3       */
  HAL_GTZC_UART4        = (GTZC_CFGR1_UART4_Pos        + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral UART4        */
  HAL_GTZC_UART5        = (GTZC_CFGR1_UART5_Pos        + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral UART5        */
  HAL_GTZC_I2C1         = (GTZC_CFGR1_I2C1_Pos         + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral I2C1         */
  HAL_GTZC_I2C2         = (GTZC_CFGR1_I2C2_Pos         + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral I2C2         */
  HAL_GTZC_CRS          = (GTZC_CFGR1_CRS_Pos          + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral CRS          */
  HAL_GTZC_I2C4         = (GTZC_CFGR1_I2C4_Pos         + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral I2C4         */
  HAL_GTZC_LPTIM2       = (GTZC_CFGR1_LPTIM2_Pos       + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral LPTIM2       */
  HAL_GTZC_FDCAN1       = (GTZC_CFGR1_FDCAN1_Pos       + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral FDCAN1       */
#if defined (UCPD1)
  HAL_GTZC_UCPD1        = (GTZC_CFGR1_UCPD1_Pos        + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral UCPD1        */
#endif /* UCPD1 */
#if defined (USART6)
  HAL_GTZC_USART6       = (GTZC_CFGR1_USART6_Pos       + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral USART6       */
#endif /* USART6 */
#if defined (I2C5)
  HAL_GTZC_I2C5         = (GTZC_CFGR1_I2C5_Pos         + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral I2C5         */
#endif /* I2C5 */
#if defined (I2C6)
  HAL_GTZC_I2C6         = (GTZC_CFGR1_I2C6_Pos         + LL_GTZC1_PERIPH_REG1), /*!< GTZC1 peripheral I2C6         */
#endif /* I2C6 */
  HAL_GTZC_TIM1         = (GTZC_CFGR2_TIM1_Pos         + LL_GTZC1_PERIPH_REG2), /*!< GTZC1 peripheral TIM1         */
  HAL_GTZC_SPI1         = (GTZC_CFGR2_SPI1_Pos         + LL_GTZC1_PERIPH_REG2), /*!< GTZC1 peripheral SPI1         */
  HAL_GTZC_TIM8         = (GTZC_CFGR2_TIM8_Pos         + LL_GTZC1_PERIPH_REG2), /*!< GTZC1 peripheral TIM8         */
  HAL_GTZC_USART1       = (GTZC_CFGR2_USART1_Pos       + LL_GTZC1_PERIPH_REG2), /*!< GTZC1 peripheral USART1       */
  HAL_GTZC_TIM15        = (GTZC_CFGR2_TIM15_Pos        + LL_GTZC1_PERIPH_REG2), /*!< GTZC1 peripheral TIM15        */
  HAL_GTZC_TIM16        = (GTZC_CFGR2_TIM16_Pos        + LL_GTZC1_PERIPH_REG2), /*!< GTZC1 peripheral TIM16        */
  HAL_GTZC_TIM17        = (GTZC_CFGR2_TIM17_Pos        + LL_GTZC1_PERIPH_REG2), /*!< GTZC1 peripheral TIM17        */
  HAL_GTZC_SAI1         = (GTZC_CFGR2_SAI1_Pos         + LL_GTZC1_PERIPH_REG2), /*!< GTZC1 peripheral SAI1         */
#if defined (SAI2)
  HAL_GTZC_SAI2         = (GTZC_CFGR2_SAI2_Pos         + LL_GTZC1_PERIPH_REG2), /*!< GTZC1 peripheral SAI2         */
#endif /* SAI2 */
#if defined (GTZC_CFGR2_LTDCUSB_Msk)
  HAL_GTZC_LTDC_USB     = (GTZC_CFGR2_LTDCUSB_Pos      + LL_GTZC1_PERIPH_REG2), /*!< GTZC1 peripheral LTDC or USB  */
#endif /* GTZC_CFGR2_LTDCUSB_Msk */
#if defined (DSI)
  HAL_GTZC_DSI          = (GTZC_CFGR2_DSI_Pos          + LL_GTZC1_PERIPH_REG2), /*!< GTZC1 peripheral DSI          */
#endif /* DSI */
#if defined (GFXTIM)
  HAL_GTZC_GFXTIM       = (GTZC_CFGR2_GFXTIM_Pos       + LL_GTZC1_PERIPH_REG2), /*!< GTZC1 peripheral GFXTIM       */
#endif /* GFXTIM */
  HAL_GTZC_MDF1         = (GTZC_CFGR3_MDF1_Pos         + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral MDF1         */
  HAL_GTZC_CORDIC       = (GTZC_CFGR3_CORDIC_Pos       + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral CORDIC       */
  HAL_GTZC_FMAC         = (GTZC_CFGR3_FMAC_Pos         + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral FMAC         */
  HAL_GTZC_CRC          = (GTZC_CFGR3_CRC_Pos          + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral CRC          */
  HAL_GTZC_TSC          = (GTZC_CFGR3_TSC_Pos          + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral TSC          */
#if defined (DMA2D)
  HAL_GTZC_DMA2D        = (GTZC_CFGR3_DMA2D_Pos        + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral DMAD2        */
#endif /* DMA2D */
  HAL_GTZC_ICACHE_REG   = (GTZC_CFGR3_ICACHE_REG_Pos   + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral ICACHE_REG   */
  HAL_GTZC_DCACHE1_REG  = (GTZC_CFGR3_DCACHE1_REG_Pos  + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral DCACHE_REG   */
  HAL_GTZC_ADC12        = (GTZC_CFGR3_ADC12_Pos        + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral ADC12        */
  HAL_GTZC_DCMI_PSSI    = (GTZC_CFGR3_DCMI_Pos         + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral DCMI_PSSI    */
#if defined (USB_OTG_GLOBAL_BASE)
  HAL_GTZC_OTG          = (GTZC_CFGR3_OTG_Pos          + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral OTG          */
#endif /* USB_OTG_GLOBAL_BASE */
#if defined(AES)
  HAL_GTZC_AES          = (GTZC_CFGR3_AES_Pos          + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral AES          */
#endif /* AES */
  HAL_GTZC_HASH         = (GTZC_CFGR3_HASH_Pos         + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral HASH         */
  HAL_GTZC_RNG          = (GTZC_CFGR3_RNG_Pos          + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral RNG          */
#if defined(PKA)
  HAL_GTZC_PKA          = (GTZC_CFGR3_PKA_Pos          + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral PKA          */
#endif /* PKA */
#if defined(SAES)
  HAL_GTZC_SAES         = (GTZC_CFGR3_SAES_Pos         + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral SAES         */
#endif /* SAES */
#if defined (OCTOSPIM)
  HAL_GTZC_OCTOSPIM     = (GTZC_CFGR3_OCTOSPIM_Pos     + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral OCTOSPIM     */
#endif /* OCTOSPIM */
  HAL_GTZC_SDMMC1       = (GTZC_CFGR3_SDMMC1_Pos       + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral SDMMC1       */
#if defined (SDMMC2)
  HAL_GTZC_SDMMC2       = (GTZC_CFGR3_SDMMC2_Pos       + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral SDMMC2       */
#endif /* SDMMC2 */
#if defined (FMC_BASE)
  HAL_GTZC_FSMC_REG     = (GTZC_CFGR3_FSMC_REG_Pos     + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral FSMC_REG     */
#endif /* FMC_BASE */
  HAL_GTZC_OCTOSPI1_REG = (GTZC_CFGR3_OCTOSPI1_REG_Pos + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral OCTOSPI1_REG */
#if defined (OCTOSPI2)
  HAL_GTZC_OCTOSPI2_REG = (GTZC_CFGR3_OCTOSPI2_REG_Pos + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral OCTOSPI2_REG */
#endif /* OCTOSPI2 */
  HAL_GTZC_RAMCFG       = (GTZC_CFGR3_RAMCFG_Pos       + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral RAMCFG       */
#if defined (GPU2D)
  HAL_GTZC_GPU2D        = (GTZC_CFGR3_GPU2D_Pos        + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral GPU2D        */
#endif /* GPU2D */
#if defined (GFXMMU)
  HAL_GTZC_GFXMMU       = (GTZC_CFGR3_GFXMMU_Pos       + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral GFXMMU       */
  HAL_GTZC_GFXMMU_REG   = (GTZC_CFGR3_GFXMMU_REG_Pos   + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral GFXMMU_REG   */
#endif /* GFXMMU */
#if defined (HSPI1)
  HAL_GTZC_HSPI1_REG    = (GTZC_CFGR3_HSPI1_REG_Pos    + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral HSPI1_REG    */
#endif /* HSPI1 */
#if defined (DCACHE2)
  HAL_GTZC_DCACHE2_REG  = (GTZC_CFGR3_DCACHE2_REG_Pos  + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral DCACHE2_REG  */
#endif /* DCACHE2 */
#if defined (JPEG)
  HAL_GTZC_JPEG         = (GTZC_CFGR3_JPEG_Pos         + LL_GTZC1_PERIPH_REG3), /*!< GTZC1 peripheral JPEG         */
#endif /* JPEG */
  HAL_GTZC_GPDMA1       = (GTZC_CFGR4_GPDMA1_Pos       + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral GPDMA1       */
  HAL_GTZC_FLASH_REG    = (GTZC_CFGR4_FLASH_REG_Pos    + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral FLASH_REG    */
  HAL_GTZC_FLASH        = (GTZC_CFGR4_FLASH_Pos        + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral FLASH        */
#if defined(OTFDEC1)
  HAL_GTZC_OTFDEC1      = (GTZC_CFGR4_OTFDEC1_Pos      + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral OTFDEC1      */
#endif /* OTFDEC1 */
#if defined (OTFDEC2)
  HAL_GTZC_OTFDEC2      = (GTZC_CFGR4_OTFDEC2_Pos      + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral OTFDEC2      */
#endif /* OTFDEC2 */
  HAL_GTZC_TZSC1        = (GTZC_CFGR4_TZSC1_Pos        + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral TZSC1        */
  HAL_GTZC_TZIC1        = (GTZC_CFGR4_TZIC1_Pos        + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral TZIC1        */
  HAL_GTZC_OCTOSPI1_MEM = (GTZC_CFGR4_OCTOSPI1_MEM_Pos + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral OCTOSPI_MEM  */
#if defined (FMC_BASE)
  HAL_GTZC_FSMC_MEM     = (GTZC_CFGR4_FSMC_MEM_Pos     + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral FSMC_MEM     */
#endif /* FMC_BASE */
  HAL_GTZC_BKPSRAM      = (GTZC_CFGR4_BKPSRAM_Pos      + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral BKPSRAM      */
#if defined (OCTOSPI2)
  HAL_GTZC_OCTOSPI2_MEM = (GTZC_CFGR4_OCTOSPI2_MEM_Pos + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral OCTOSPI2_MEM */
#endif /* OCTOSPI2 */
#if defined (HSPI1)
  HAL_GTZC1_HSPI1_MEM   = (GTZC_CFGR4_HSPI1_MEM_Pos    + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral HSPI1_MEM   */
#endif /* HSPI1 */
  HAL_GTZC_SRAM1        = (GTZC_CFGR4_SRAM1_Pos        + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral SRAM1        */
  HAL_GTZC_MPCBB1_REG   = (GTZC_CFGR4_MPCBB1_REG_Pos   + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral MPCBB1_REG   */
  HAL_GTZC_SRAM2        = (GTZC_CFGR4_SRAM2_Pos        + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral SRAM2        */
  HAL_GTZC_MPCBB2_REG   = (GTZC_CFGR4_MPCBB2_REG_Pos   + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral MPCBB2_REG   */
#if defined (SRAM3_BASE)
  HAL_GTZC_SRAM3        = (GTZC_CFGR4_SRAM3_Pos        + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral SRAM3        */
  HAL_GTZC_MPCBB3_REG   = (GTZC_CFGR4_MPCBB3_REG_Pos   + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral MPCBB3_REG   */
#endif /* SRAM3_BASE */
#if defined (SRAM5_BASE)
  HAL_GTZC_SRAM5        = (GTZC_CFGR4_SRAM5_Pos        + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral SRAM5        */
  HAL_GTZC_MPCBB5_REG   = (GTZC_CFGR4_MPCBB5_REG_Pos   + LL_GTZC1_PERIPH_REG4), /*!< GTZC1 peripheral MPCBB5_REG   */
#endif /* SRAM5_BASE */

  /* GTZC2 */
  HAL_GTZC_SPI3         = (GTZC_CFGR1_SPI3_Pos         + LL_GTZC2_PERIPH_REG1), /*!< GTZC2 peripheral SPI3         */
  HAL_GTZC_LPUART1      = (GTZC_CFGR1_LPUART1_Pos      + LL_GTZC2_PERIPH_REG1), /*!< GTZC2 peripheral LPUART1      */
  HAL_GTZC_I2C3         = (GTZC_CFGR1_I2C3_Pos         + LL_GTZC2_PERIPH_REG1), /*!< GTZC2 peripheral I2C3         */
  HAL_GTZC_LPTIM1       = (GTZC_CFGR1_LPTIM1_Pos       + LL_GTZC2_PERIPH_REG1), /*!< GTZC2 peripheral LPTIM1       */
  HAL_GTZC_LPTIM3       = (GTZC_CFGR1_LPTIM3_Pos       + LL_GTZC2_PERIPH_REG1), /*!< GTZC2 peripheral LPTIM3       */
  HAL_GTZC_LPTIM4       = (GTZC_CFGR1_LPTIM4_Pos       + LL_GTZC2_PERIPH_REG1), /*!< GTZC2 peripheral LPTIM4       */
  HAL_GTZC_OPAMP        = (GTZC_CFGR1_OPAMP_Pos        + LL_GTZC2_PERIPH_REG1), /*!< GTZC2 peripheral OPAMP        */
  HAL_GTZC_COMP         = (GTZC_CFGR1_COMP_Pos         + LL_GTZC2_PERIPH_REG1), /*!< GTZC2 peripheral COMP         */
  HAL_GTZC_ADC4         = (GTZC_CFGR1_ADC4_Pos         + LL_GTZC2_PERIPH_REG1), /*!< GTZC2 peripheral ADC4         */
  HAL_GTZC_VREFBUF      = (GTZC_CFGR1_VREFBUF_Pos      + LL_GTZC2_PERIPH_REG1), /*!< GTZC2 peripheral VREFBUF      */
  HAL_GTZC_DAC1         = (GTZC_CFGR1_DAC1_Pos         + LL_GTZC2_PERIPH_REG1), /*!< GTZC2 peripheral DAC1         */
  HAL_GTZC_ADF1         = (GTZC_CFGR1_ADF1_Pos         + LL_GTZC2_PERIPH_REG1), /*!< GTZC2 peripheral ADF1         */
  HAL_GTZC_SYSCFG       = (GTZC_CFGR2_SYSCFG_Pos       + LL_GTZC2_PERIPH_REG2), /*!< GTZC2 peripheral SYSCFG       */
  HAL_GTZC_RTC          = (GTZC_CFGR2_RTC_Pos          + LL_GTZC2_PERIPH_REG2), /*!< GTZC2 peripheral RTC          */
  HAL_GTZC_TAMP         = (GTZC_CFGR2_TAMP_Pos         + LL_GTZC2_PERIPH_REG2), /*!< GTZC2 peripheral TAMP         */
  HAL_GTZC_PWR          = (GTZC_CFGR2_PWR_Pos          + LL_GTZC2_PERIPH_REG2), /*!< GTZC2 peripheral PWR          */
  HAL_GTZC_RCC          = (GTZC_CFGR2_RCC_Pos          + LL_GTZC2_PERIPH_REG2), /*!< GTZC2 peripheral RCC          */
  HAL_GTZC_LPDMA1       = (GTZC_CFGR2_LPDMA1_Pos       + LL_GTZC2_PERIPH_REG2), /*!< GTZC2 peripheral LPDMA1       */
  HAL_GTZC_EXTI         = (GTZC_CFGR2_EXTI_Pos         + LL_GTZC2_PERIPH_REG2), /*!< GTZC2 peripheral EXTI         */
  HAL_GTZC_TZSC2        = (GTZC_CFGR2_TZSC2_Pos        + LL_GTZC2_PERIPH_REG2), /*!< GTZC2 peripheral TZSC2        */
  HAL_GTZC_TZIC2        = (GTZC_CFGR2_TZIC2_Pos        + LL_GTZC2_PERIPH_REG2), /*!< GTZC2 peripheral TZIC2        */
  HAL_GTZC_SRAM4        = (GTZC_CFGR2_SRAM4_Pos        + LL_GTZC2_PERIPH_REG2), /*!< GTZC2 peripheral SRAM4        */
  HAL_GTZC_MPCBB4_REG   = (GTZC_CFGR2_MPCBB4_REG_Pos   + LL_GTZC2_PERIPH_REG2), /*!< GTZC2 peripheral MPCBB4_REG   */

  /* GTZC1 and GTZC2 */
  HAL_GTZC_PERIPH_ALL   = 0xFFFFFFFFU                                           /*!< GTZC all peripherals : must be used
                                                                                     only for (enable/disable) illegal
                                                                                     access interrupt APIs         */
} hal_gtzc_periph_t;

/*! GTZC Securable peripherals groups */
typedef enum
{
  HAL_GTZC1_PERIPH_ALL = (uint32_t)GTZC1_TZSC1_SEC_PERIPH, /*!< GTZC1 lock peripheral attribute */
  HAL_GTZC2_PERIPH_ALL = (uint32_t)GTZC2_TZSC1_SEC_PERIPH  /*!< GTZC2 lock peripheral attribute */
} hal_gtzc_lock_periphs_t;

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/*! GTZC Watermark memories */
typedef enum
{
  HAL_GTZC_WATERMARK_OCTOSPI1    = (uint32_t)GTZC1_TZSC1_MPCWM1, /*!< GTZC water mark OCTOSPI1 memory    */
#if defined(FMC_BASE)
  HAL_GTZC_WATERMARK_FMC_NOR     = (uint32_t)GTZC1_TZSC1_MPCWM2, /*!< GTZC water mark FMC_NOR memory     */
  HAL_GTZC_WATERMARK_FMC_NAND    = (uint32_t)GTZC1_TZSC1_MPCWM3, /*!< GTZC water mark FMC_NAND memory    */
#endif /* FMC_BASE */
  HAL_GTZC_WATERMARK_BKPSRAM     = (uint32_t)GTZC1_TZSC1_MPCWM4, /*!< GTZC water mark FMC_BKPSRAM memory */
#if defined(OCTOSPI2)
  HAL_GTZC_WATERMARK_OCTOSPI2    = (uint32_t)GTZC1_TZSC1_MPCWM5, /*!< GTZC water mark OCTOSPI2 memory    */
#endif /* OCTOSPI2 */
#if defined (HSPI1)
  HAL_GTZC_WATERMARK_HSPI1       = (uint32_t)GTZC1_TZSC1_MPCWM6  /*!< GTZC water mark HSPI1 memory       */
#endif /* HSPI1 */
} hal_gtzc_watermark_mem_t;
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/*! GTZC Block based memories */
typedef enum
{
  HAL_GTZC_BLOCKBASED_SRAM1 = (uint32_t)GTZC1_MPCBB1, /*!< GTZC block based SRAM1 memory */
  HAL_GTZC_BLOCKBASED_SRAM2 = (uint32_t)GTZC1_MPCBB2, /*!< GTZC block based SRAM2 memory */
#if defined (SRAM3_BASE)
  HAL_GTZC_BLOCKBASED_SRAM3 = (uint32_t)GTZC1_MPCBB3, /*!< GTZC block based SRAM3 memory */
#endif /* SRAM3_BASE */
  HAL_GTZC_BLOCKBASED_SRAM4 = (uint32_t)GTZC2_MPCBB4, /*!< GTZC block based SRAM4 memory */
#if defined (SRAM5_BASE)
  HAL_GTZC_BLOCKBASED_SRAM5 = (uint32_t)GTZC1_MPCBB5,  /*!< GTZC block based SRAM5 memory */
#endif /* SRAM5_BASE */
#if defined (SRAM6_BASE)
  HAL_GTZC_BLOCKBASED_SRAM6 = (uint32_t)GTZC1_MPCBB6  /*!< GTZC block based SRAM6 memory */
#endif /* SRAM6_BASE */
} hal_gtzc_blockbased_mem_t;

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/*! GTZC watermark subregion */
typedef enum
{
  HAL_GTZC_WATERMARK_SUBREGION_A = (uint32_t)LL_GTZC_TZSC_MPCWM_SUBREGION_A, /*!< GTZC watermark subregion A */
  HAL_GTZC_WATERMARK_SUBREGION_B = (uint32_t)LL_GTZC_TZSC_MPCWM_SUBREGION_B  /*!< GTZC watermark subregion B */
} hal_gtzc_watermark_subregion_t;

/*! GTZC watermark memory subregion state */
typedef enum
{
  HAL_GTZC_WATERMARK_SUBREGION_DISABLED = 0x00U, /*!< GTZC watermark subregion disabled */
  HAL_GTZC_WATERMARK_SUBREGION_ENABLED  = 0x01U  /*!< GTZC watermark subregion enabled  */
} hal_gtzc_watermark_subregion_state_t ;
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/*! GTZC Attribute lock state */
typedef enum
{
  HAL_GTZC_ATTR_UNLOCKED = 0x00U, /*!< GTZC attribute unlocked */
  HAL_GTZC_ATTR_LOCKED   = 0x01U  /*!< GTZC attribute locked   */
} hal_gtzc_attr_lock_state_t;

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/*! GTZC Memory clock security state */
typedef enum
{
  HAL_GTZC_CLK_SEC_NOT_INVERTED = LL_GTZC_MPCBB_CLK_SEC_NOT_INVERTED, /*!< GTZC clock security not inverted */
  HAL_GTZC_CLK_SEC_INVERTED     = LL_GTZC_MPCBB_CLK_SEC_INVERTED      /*!< GTZC clock security inverted     */
} hal_gtzc_blockbased_mem_clk_sec_state_t;

/*! GTZC Memory security access state */
typedef enum
{
  HAL_GTZC_SEC_ACCESS_NOT_ALLOWED = LL_GTZC_MPCBB_SEC_ACCESS_NOT_ALLOWED, /*!< GTZC memory secure access not allowed */
  HAL_GTZC_SEC_ACCESS_ALLOWED     = LL_GTZC_MPCBB_SEC_ACCESS_ALLOWED      /*!< GTZC memory secure access allowed     */
} hal_gtzc_blockbased_mem_sec_access_state_t;

/*! GTZC Illegal access interrupt state */
typedef enum
{
  HAL_GTZC_ILAC_IT_DISABLED = 0x00U, /*!< GTZC Illegal access interrupt disabled */
  HAL_GTZC_ILAC_IT_ENABLED  = 0x01U  /*!< GTZC Illegal access interrupt enabled  */
} hal_gtzc_illegal_access_it_state_t;
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_Exported_Functions GTZC Exported Functions
  * @{
  */
/** @defgroup GTZC_Exported_Functions_Group1 Securable peripherals attributes configuration functions
  * @{
  */
hal_status_t HAL_GTZC_SetPeriphAttr(hal_gtzc_periph_t periph, const hal_gtzc_attr_config_t *p_attr);
void         HAL_GTZC_GetPeriphAttr(hal_gtzc_periph_t periph, hal_gtzc_attr_config_t *p_attr);
/**
  * @}
  */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/** @defgroup GTZC_Exported_Functions_Group2 Lock the attributes configurations of securable peripherals functions
  * @{
  */
void                       HAL_GTZC_LockPeriphAttr(hal_gtzc_lock_periphs_t lock_periphs);
hal_gtzc_attr_lock_state_t HAL_GTZC_IsPeriphAttrLocked(hal_gtzc_lock_periphs_t lock_periphs);
/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group3 Watermark memories subregion attributes configuration functions
  * @{
  */
hal_status_t HAL_GTZC_WATERMARK_SetConfigMemSubRegionAttr(hal_gtzc_watermark_mem_t memory,
                                                          uint32_t offset_byte,
                                                          uint32_t size_byte,
                                                          hal_gtzc_watermark_subregion_t sub_region,
                                                          const hal_gtzc_attr_config_t *p_attr);

hal_status_t HAL_GTZC_WATERMARK_GetMemAreaAttr(hal_gtzc_watermark_mem_t memory,
                                               uint32_t offset_byte,
                                               uint32_t size_byte,
                                               hal_gtzc_attr_config_t *p_attr);

uint32_t     HAL_GTZC_WATERMARK_GetMemMapAttr(hal_gtzc_watermark_mem_t memory,
                                              hal_gtzc_watermark_mem_map_t *p_map);
/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group4 Enable/Disable watermark memories subregion functions
  * @{
  */
void HAL_GTZC_WATERMARK_EnableMemSubRegionAttr(hal_gtzc_watermark_mem_t memory,
                                               hal_gtzc_watermark_subregion_t sub_region);

void HAL_GTZC_WATERMARK_DisableMemSubRegionAttr(hal_gtzc_watermark_mem_t memory,
                                                hal_gtzc_watermark_subregion_t sub_region);
hal_gtzc_watermark_subregion_state_t
HAL_GTZC_WATERMARK_IsEnabledMemSubRegionAttr(hal_gtzc_watermark_mem_t memory,
                                             hal_gtzc_watermark_subregion_t sub_region);
/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group5 Lock the configurations of watermark memories subregion functions
  * @{
  */
void                       HAL_GTZC_WATERMARK_LockMemSubRegionConfig(hal_gtzc_watermark_mem_t memory,
                                                                     hal_gtzc_watermark_subregion_t sub_region);

hal_gtzc_attr_lock_state_t HAL_GTZC_WATERMARK_IsMemSubRegionConfigLocked(hal_gtzc_watermark_mem_t memory,
                                                                         hal_gtzc_watermark_subregion_t sub_region);
/**
  * @}
  */
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/** @defgroup GTZC_Exported_Functions_Group6 Block based memories attributes configuration functions
  * @{
  */
hal_status_t HAL_GTZC_BLOCKBASED_SetMemBlockAttr(hal_gtzc_blockbased_mem_t memory,
                                                 uint32_t block_idx,
                                                 uint32_t block_nbr,
                                                 const hal_gtzc_attr_config_t *p_attr);

void         HAL_GTZC_BLOCKBASED_GetMemBlockAttr(hal_gtzc_blockbased_mem_t memory,
                                                 uint32_t block_idx,
                                                 hal_gtzc_attr_config_t *p_attr);

hal_status_t HAL_GTZC_BLOCKBASED_SetMemAddrAttr(hal_gtzc_blockbased_mem_t memory,
                                                uint32_t offset_byte,
                                                uint32_t size_byte,
                                                const hal_gtzc_attr_config_t *p_attr);

void         HAL_GTZC_BLOCKBASED_GetMemAddrAttr(hal_gtzc_blockbased_mem_t memory,
                                                uint32_t offset_byte,
                                                hal_gtzc_attr_config_t *p_attr);
/**
  * @}
  */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/** @defgroup GTZC_Exported_Functions_Group7 Clock security state of block based memories configuration functions
  * @{
  */
void HAL_GTZC_BLOCKBASED_SetMemClkSecStateInvertion(hal_gtzc_blockbased_mem_t memory,
                                                    hal_gtzc_blockbased_mem_clk_sec_state_t clk_sec_state);

hal_gtzc_blockbased_mem_clk_sec_state_t
HAL_GTZC_BLOCKBASED_GetMemClkSecStateInvertion(hal_gtzc_blockbased_mem_t memory);
/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group8 Secure access state of block based memories configuration functions
  * @{
  */
void HAL_GTZC_BLOCKBASED_SetMemSecAccessState(hal_gtzc_blockbased_mem_t memory,
                                              hal_gtzc_blockbased_mem_sec_access_state_t state);

hal_gtzc_blockbased_mem_sec_access_state_t HAL_GTZC_BLOCKBASED_GetMemSecAccessState(hal_gtzc_blockbased_mem_t memory);
/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group9 Lock the configurations of block based memories functions
  * @{
  */
void                       HAL_GTZC_BLOCKBASED_LockMemAttr(hal_gtzc_blockbased_mem_t memory,
                                                           uint32_t offset_byte,
                                                           uint32_t size_byte);

hal_gtzc_attr_lock_state_t HAL_GTZC_BLOCKBASED_IsMemAttrLocked(hal_gtzc_blockbased_mem_t memory,
                                                               uint32_t offset_byte);

void                       HAL_GTZC_BLOCKBASED_LockMemSuperBlockAttr(hal_gtzc_blockbased_mem_t memory,
                                                                     uint32_t super_blk_idx,
                                                                     uint32_t super_blk_nbr);

hal_gtzc_attr_lock_state_t HAL_GTZC_BLOCKBASED_IsMemSuperBlockAttrLocked(hal_gtzc_blockbased_mem_t memory,
                                                                         uint32_t super_blk_idx);

void                       HAL_GTZC_BLOCKBASED_LockMemConfig(hal_gtzc_blockbased_mem_t memory);

hal_gtzc_attr_lock_state_t HAL_GTZC_BLOCKBASED_IsMemConfigLocked(hal_gtzc_blockbased_mem_t memory);
/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group10 Enable/Disable the illegal access interrupt of peripherals functions
  * @{
  */
void HAL_GTZC_ILLEGALACCESS_EnableIT(hal_gtzc_periph_t periph);
void HAL_GTZC_ILLEGALACCESS_DisableIT(hal_gtzc_periph_t periph);
hal_gtzc_illegal_access_it_state_t HAL_GTZC_ILLEGALACCESS_IsEnabledIT(hal_gtzc_periph_t periph);
/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group11 Treat the illegal access interrupt functions
  * @{
  */
void HAL_GTZC_ILLEGALACCESS_IRQHandler(void);
void HAL_GTZC_ILLEGALACCESS_Callback(hal_gtzc_periph_t periph);
/**
  * @}
  */
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
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
#endif

#endif /* STM32U5xx_HAL_GTZC_H */
