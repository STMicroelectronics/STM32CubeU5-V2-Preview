/**
  **********************************************************************************************************************
  * @file   stm32u5xx_ll_gtzc.h
  * @brief  Header file of GTZC LL module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2023-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */
/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_LL_GTZC_H
#define STM32U5XX_LL_GTZC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

/** @addtogroup GTZC_LL GTZC
  * @{
  */
/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private constants -------------------------------------------------------------------------------------------------*/
/* Private macros ----------------------------------------------------------------------------------------------------*/
/* Exported macros ---------------------------------------------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------------------------------------------*/
/* Exported variables ------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_LL_Exported_Constants GTZC LL Exported Constants
  * @{
  */

/** @defgroup GTZC_LL_EC_RegisterSelection Register Selection
  * @{
  */
#define LL_GTZC1_PERIPH_REG1 00U                        /*!< GTZC1 peripherals register 1 */
#define LL_GTZC1_PERIPH_REG2 32U                        /*!< GTZC1 peripherals register 2 */
#define LL_GTZC1_PERIPH_REG3 64U                        /*!< GTZC1 peripherals register 3 */
#define LL_GTZC1_PERIPH_REG4 96U                        /*!< GTZC1 peripherals register 4 */
#define LL_GTZC2_PERIPH_REG1 (00U + AHB3PERIPH_BASE_NS) /*!< GTZC2 peripherals register 1 */
#define LL_GTZC2_PERIPH_REG2 (32U + AHB3PERIPH_BASE_NS) /*!< GTZC2 peripherals register 2 */
/**
  * @}
  */

/** @defgroup GTZC_LL_EC_WatermarkMaximumDescriptos Watermark Maximum Descriptos
  * @{
  */
#define LL_GTZC_MPCWM_MAX_DESC 5U /*!< GTZC Watermark maximum descriptors */
/**
  * @}
  */

/** @defgroup GTZC_LL_EC_PeripheralSelection Peripheral Selection
  * @{
  */

/**
  * @brief GTZC1 (ILAC/SEC/PRIV)CFGR1 peripheral selection
  */
#define LL_GTZC1_GRP1_TIM2   GTZC_CFGR1_TIM2_Msk   /*!< LL GTZC1 CFGR1 peripheral TIM2   */
#define LL_GTZC1_GRP1_TIM3   GTZC_CFGR1_TIM3_Msk   /*!< LL GTZC1 CFGR1 peripheral TIM3   */
#define LL_GTZC1_GRP1_TIM4   GTZC_CFGR1_TIM4_Msk   /*!< LL GTZC1 CFGR1 peripheral TIM4   */
#define LL_GTZC1_GRP1_TIM5   GTZC_CFGR1_TIM5_Msk   /*!< LL GTZC1 CFGR1 peripheral TIM5   */
#define LL_GTZC1_GRP1_TIM6   GTZC_CFGR1_TIM6_Msk   /*!< LL GTZC1 CFGR1 peripheral TIM6   */
#define LL_GTZC1_GRP1_TIM7   GTZC_CFGR1_TIM7_Msk   /*!< LL GTZC1 CFGR1 peripheral TIM7   */
#define LL_GTZC1_GRP1_WWDG   GTZC_CFGR1_WWDG_Msk   /*!< LL GTZC1 CFGR1 peripheral WWDG   */
#define LL_GTZC1_GRP1_IWDG   GTZC_CFGR1_IWDG_Msk   /*!< LL GTZC1 CFGR1 peripheral IWDG   */
#define LL_GTZC1_GRP1_SPI2   GTZC_CFGR1_SPI2_Msk   /*!< LL GTZC1 CFGR1 peripheral SPI2   */
#if defined(USART2)
#define LL_GTZC1_GRP1_USART2 GTZC_CFGR1_USART2_Msk /*!< LL GTZC1 CFGR1 peripheral USART2 */
#endif /* USART2 */
#define LL_GTZC1_GRP1_USART3 GTZC_CFGR1_USART3_Msk /*!< LL GTZC1 CFGR1 peripheral USART3 */
#define LL_GTZC1_GRP1_UART4  GTZC_CFGR1_UART4_Msk  /*!< LL GTZC1 CFGR1 peripheral UART4  */
#define LL_GTZC1_GRP1_UART5  GTZC_CFGR1_UART5_Msk  /*!< LL GTZC1 CFGR1 peripheral UART5  */
#define LL_GTZC1_GRP1_I2C1   GTZC_CFGR1_I2C1_Msk   /*!< LL GTZC1 CFGR1 peripheral I2C1   */
#define LL_GTZC1_GRP1_I2C2   GTZC_CFGR1_I2C2_Msk   /*!< LL GTZC1 CFGR1 peripheral I2C2   */
#define LL_GTZC1_GRP1_CRS    GTZC_CFGR1_CRS_Msk    /*!< LL GTZC1 CFGR1 peripheral CRS    */
#define LL_GTZC1_GRP1_I2C4   GTZC_CFGR1_I2C4_Msk   /*!< LL GTZC1 CFGR1 peripheral I2C4   */
#define LL_GTZC1_GRP1_LPTIM2 GTZC_CFGR1_LPTIM2_Msk /*!< LL GTZC1 CFGR1 peripheral LPTIM2 */
#define LL_GTZC1_GRP1_FDCAN1 GTZC_CFGR1_FDCAN1_Msk /*!< LL GTZC1 CFGR1 peripheral FDCAN1 */
#if defined(UCPD1)
#define LL_GTZC1_GRP1_UCPD1  GTZC_CFGR1_UCPD1_Msk  /*!< LL GTZC1 CFGR1 peripheral UCPD1  */
#endif /* UCPD1 */
#if defined(USART6)
#define LL_GTZC1_GRP1_USART6 GTZC_CFGR1_USART6_Msk /*!< LL GTZC1 CFGR1 peripheral USART6 */
#endif /* USART6 */
#if defined (I2C5)
#define LL_GTZC1_GRP1_I2C5   GTZC_CFGR1_I2C5_Msk   /*!< LL GTZC1 CFGR1 peripheral I2C5   */
#endif /* I2C5 */
#if defined (I2C6)
#define LL_GTZC1_GRP1_I2C6   GTZC_CFGR1_I2C6_Msk   /*!< LL GTZC1 CFGR1 peripheral I2C6   */
#endif /* I2C6 */
#if defined (USART6)
#define LL_GTZC1_GRP1_ALL    0x00EFFFFFU           /*!< LL GTZC1 CFGR1 ALL peripherals   */
#elif defined (USART2)
#define LL_GTZC1_GRP1_ALL    0x000FFFFFU           /*!< LL GTZC1 CFGR1 ALL peripherals   */
#else
#define LL_GTZC1_GRP1_ALL    0x0007FDFFU           /*!< LL GTZC1 CFGR1 ALL peripherals   */
#endif /* USART6 */

/**
  * @brief GTZC1 (ILAC/SEC/PRIV)CFGR2 peripheral selection
  */
#define LL_GTZC1_GRP2_TIM1     GTZC_CFGR2_TIM1_Msk    /*!< LL GTZC1 CFGR2 peripheral TIM1        */
#define LL_GTZC1_GRP2_SPI1     GTZC_CFGR2_SPI1_Msk    /*!< LL GTZC1 CFGR2 peripheral SPI1        */
#define LL_GTZC1_GRP2_TIM8     GTZC_CFGR2_TIM8_Msk    /*!< LL GTZC1 CFGR2 peripheral TIM8        */
#define LL_GTZC1_GRP2_USART1   GTZC_CFGR2_USART1_Msk  /*!< LL GTZC1 CFGR2 peripheral USART1      */
#define LL_GTZC1_GRP2_TIM15    GTZC_CFGR2_TIM15_Msk   /*!< LL GTZC1 CFGR2 peripheral TIM15       */
#define LL_GTZC1_GRP2_TIM16    GTZC_CFGR2_TIM16_Msk   /*!< LL GTZC1 CFGR2 peripheral TIM16       */
#define LL_GTZC1_GRP2_TIM17    GTZC_CFGR2_TIM17_Msk   /*!< LL GTZC1 CFGR2 peripheral TIM17       */
#define LL_GTZC1_GRP2_SAI1     GTZC_CFGR2_SAI1_Msk    /*!< LL GTZC1 CFGR2 peripheral SAI1        */
#if defined(SAI2)
#define LL_GTZC1_GRP2_SAI2     GTZC_CFGR2_SAI2_Msk    /*!< LL GTZC1 CFGR2 peripheral SAI2        */
#endif /* SAI2 */
#if defined(GTZC_CFGR2_LTDCUSB_Msk)
#define LL_GTZC1_GRP2_LTDC_USB GTZC_CFGR2_LTDCUSB_Msk /*!< LL GTZC1 CFGR2 peripheral LTDC or USB */
#endif /* GTZC_CFGR2_LTDCUSB_Msk*/
#if defined (DSI)
#define LL_GTZC1_GRP2_DSI      GTZC_CFGR2_DSI_Msk     /*!< LL GTZC1 CFGR2 peripheral DSI         */
#endif /* DSI */
#if defined (GFXTIM)
#define LL_GTZC1_GRP2_GFXTIM   GTZC_CFGR2_GFXTIM_Msk  /*!< LL GTZC1 CFGR2 peripheral GFXTIM      */
#endif /* GFXTIM */

#if defined (GFXTIM)
#define LL_GTZC1_GRP2_ALL      0x00000FFFU            /*!< LL GTZC1 CFGR2 ALL peripherals        */
#elif defined (LTDC)
#define LL_GTZC1_GRP2_ALL      0x000007FFU            /*!< LL GTZC1 CFGR2 ALL peripherals        */
#elif defined (SAI2)
#define LL_GTZC1_GRP2_ALL      0x000001FFU            /*!< LL GTZC1 CFGR2 ALL peripherals        */
#else
#define LL_GTZC1_GRP2_ALL      0x000002FFU            /*!< LL GTZC1 CFGR2 ALL peripherals        */
#endif /* GFXTIM */

/**
  * @brief GTZC1 (ILAC/SEC/PRIV)CFGR3 peripheral selection
  */
#define LL_GTZC1_GRP3_MDF1         GTZC_CFGR3_MDF1_Msk         /*!< LL GTZC1 CFGR3 peripheral MDF1         */
#define LL_GTZC1_GRP3_CORDIC       GTZC_CFGR3_CORDIC_Msk       /*!< LL GTZC1 CFGR3 peripheral CORDIC       */
#define LL_GTZC1_GRP3_FMAC         GTZC_CFGR3_FMAC_Msk         /*!< LL GTZC1 CFGR3 peripheral FMAC         */
#define LL_GTZC1_GRP3_CRC          GTZC_CFGR3_CRC_Msk          /*!< LL GTZC1 CFGR3 peripheral CRC          */
#define LL_GTZC1_GRP3_TSC          GTZC_CFGR3_TSC_Msk          /*!< LL GTZC1 CFGR3 peripheral TSC          */
#if defined(DMA2D)
#define LL_GTZC1_GRP3_DMA2D        GTZC_CFGR3_DMA2D_Msk        /*!< LL GTZC1 CFGR3 peripheral DMAD2        */
#endif /* DMA2D */
#define LL_GTZC1_GRP3_ICACHE_REG   GTZC_CFGR3_ICACHE_REG_Msk   /*!< LL GTZC1 CFGR3 peripheral ICACHE_REG   */
#define LL_GTZC1_GRP3_DCACHE1_REG  GTZC_CFGR3_DCACHE1_REG_Msk  /*!< LL GTZC1 CFGR3 peripheral DCACHE_REG   */
#define LL_GTZC1_GRP3_ADC12        GTZC_CFGR3_ADC12_Msk        /*!< LL GTZC1 CFGR3 peripheral ADC12        */
#define LL_GTZC1_GRP3_DCMI         GTZC_CFGR3_DCMI_Msk         /*!< LL GTZC1 CFGR3 peripheral DCMI_PSSI    */
#if defined (USB_OTG_GLOBAL_BASE)
#define LL_GTZC1_GRP3_OTG          GTZC_CFGR3_OTG_Msk          /*!< LL GTZC1 CFGR3 peripheral OTG          */
#endif /* USB_OTG_GLOBAL_BASE */
#if defined(AES)
#define LL_GTZC1_GRP3_AES          GTZC_CFGR3_AES_Msk          /*!< LL GTZC1 CFGR3 peripheral AES          */
#endif /* AES */
#define LL_GTZC1_GRP3_HASH         GTZC_CFGR3_HASH_Msk         /*!< LL GTZC1 CFGR3 peripheral HASH         */
#define LL_GTZC1_GRP3_RNG          GTZC_CFGR3_RNG_Msk          /*!< LL GTZC1 CFGR3 peripheral RNG          */
#if defined(PKA)
#define LL_GTZC1_GRP3_PKA          GTZC_CFGR3_PKA_Msk          /*!< LL GTZC1 CFGR3 peripheral PKA          */
#endif /* PKA */
#if defined(SAES)
#define LL_GTZC1_GRP3_SAES         GTZC_CFGR3_SAES_Msk         /*!< LL GTZC1 CFGR3 peripheral SAES         */
#endif /* SAES */
#if defined(OCTOSPIM)
#define LL_GTZC1_GRP3_OCTOSPIM     GTZC_CFGR3_OCTOSPIM_Msk     /*!< LL GTZC1 CFGR3 peripheral OCTOSPIM     */
#endif /* OCTOSPIM */
#define LL_GTZC1_GRP3_SDMMC1       GTZC_CFGR3_SDMMC1_Msk       /*!< LL GTZC1 CFGR3 peripheral SDMMC1       */
#if defined(SDMMC2)
#define LL_GTZC1_GRP3_SDMMC2       GTZC_CFGR3_SDMMC2_Msk       /*!< LL GTZC1 CFGR3 peripheral SDMMC2       */
#endif /* SDMMC2 */
#if defined(FMC_BASE)
#define LL_GTZC1_GRP3_FSMC_REG     GTZC_CFGR3_FSMC_REG_Msk     /*!< LL GTZC1 CFGR3 peripheral FSMC_REG     */
#endif /* FMC_BASE */
#define LL_GTZC1_GRP3_OCTOSPI1_REG GTZC_CFGR3_OCTOSPI1_REG_Msk /*!< LL GTZC1 CFGR3 peripheral OCTOSPI1_REG */
#if defined(OCTOSPI2)
#define LL_GTZC1_GRP3_OCTOSPI2_REG GTZC_CFGR3_OCTOSPI2_REG_Msk /*!< LL GTZC1 CFGR3 peripheral OCTOSPI2_REG */
#endif /* OCTOSPI2 */
#define LL_GTZC1_GRP3_RAMCFG       GTZC_CFGR3_RAMCFG_Msk       /*!< LL GTZC1 CFGR3 peripheral RAMCFG       */
#if defined (GPU2D)
#define LL_GTZC1_GRP3_GPU2D        GTZC_CFGR3_GPU2D_Msk        /*!< LL GTZC1 CFGR3 peripheral GPU2D        */
#endif /* GPU2D */
#if defined (GFXMMU)
#define LL_GTZC1_GRP3_GFXMMU       GTZC_CFGR3_GFXMMU_Msk       /*!< LL GTZC1 CFGR3 peripheral GFXMMU       */
#define LL_GTZC1_GRP3_GFXMMU_REG   GTZC_CFGR3_GFXMMU_REG_Msk   /*!< LL GTZC1 CFGR3 peripheral GFXMMU_REG   */
#endif /* GFXMMU */
#if defined (HSPI1)
#define LL_GTZC1_GRP3_HSPI1_REG    GTZC_CFGR3_HSPI1_REG_Msk    /*!< LL GTZC1 CFGR3 peripheral HSPI1_REG    */
#endif /* HSPI1 */
#if defined (DCACHE2)
#define LL_GTZC1_GRP3_DCACHE2_REG  GTZC_CFGR3_DCACHE2_REG_Msk  /*!< LL GTZC1 CFGR3 peripheral DCACHE2_REG  */
#endif /* DCACHE2 */
#if defined (JPEG)
#define LL_GTZC1_GRP3_JPEG         GTZC_CFGR3_JPEG_Msk         /*!< LL GTZC1 CFGR3 peripheral JPEG         */
#endif /* JPEG */

#if defined (JPEG)
#define LL_GTZC1_GRP3_ALL          0x1FFFFFFFU                 /*!< LL GTZC1 CFGR3 ALL peripherals         */
#elif defined (DCACHE2)
#define LL_GTZC1_GRP3_ALL          0x0FFFFFFFU                 /*!< LL GTZC1 CFGR3 ALL peripherals         */
#elif defined (OCTOSPI2)
#define LL_GTZC1_GRP3_ALL          0x007FFFFFU                 /*!< LL GTZC1 CFGR3 ALL peripherals         */
#else
#define LL_GTZC1_GRP3_ALL          0x0052FBDFU                 /*!< LL GTZC1 CFGR3 ALL peripherals         */
#endif /* JPEG */

/**
  * @brief GTZC1 (ILAC)CFGR4 peripheral selection
  */
#define LL_GTZC1_GRP4_GPDMA1       GTZC_CFGR4_GPDMA1_Msk       /*!< LL GTZC1 CFGR4 peripheral GPDMA1       */
#define LL_GTZC1_GRP4_FLASH_REG    GTZC_CFGR4_FLASH_REG_Msk    /*!< LL GTZC1 CFGR4 peripheral FLASH_REG    */
#define LL_GTZC1_GRP4_FLASH        GTZC_CFGR4_FLASH_Msk        /*!< LL GTZC1 CFGR4 peripheral FLASH        */
#if defined(OTFDEC1)
#define LL_GTZC1_GRP4_OTFDEC1      GTZC_CFGR4_OTFDEC1_Msk      /*!< LL GTZC1 CFGR4 peripheral OTFDEC2      */
#endif /* OTFDEC1 */
#if defined(OTFDEC2)
#define LL_GTZC1_GRP4_OTFDEC2      GTZC_CFGR4_OTFDEC2_Msk      /*!< LL GTZC1 CFGR4 peripheral OTFDEC1      */
#endif /* OTFDEC2 */
#define LL_GTZC1_GRP4_TZSC1        GTZC_CFGR4_TZSC1_Msk        /*!< LL GTZC1 CFGR4 peripheral TZSC1        */
#define LL_GTZC1_GRP4_TZIC1        GTZC_CFGR4_TZIC1_Msk        /*!< LL GTZC1 CFGR4 peripheral TZIC1        */
#define LL_GTZC1_GRP4_OCTOSPI1_MEM GTZC_CFGR4_OCTOSPI1_MEM_Msk /*!< LL GTZC1 CFGR4 peripheral OCTOSPI_MEM  */
#if defined(FMC_BASE)
#define LL_GTZC1_GRP4_FSMC_MEM     GTZC_CFGR4_FSMC_MEM_Msk     /*!< LL GTZC1 CFGR4 peripheral FSMC_MEM     */
#endif /* FMC_BASE */
#define LL_GTZC1_GRP4_BKPSRAM      GTZC_CFGR4_BKPSRAM_Msk      /*!< LL GTZC1 CFGR4 peripheral BKPSRAM      */
#if defined(OCTOSPI2)
#define LL_GTZC1_GRP4_OCTOSPI2_MEM GTZC_CFGR4_OCTOSPI2_MEM_Msk /*!< LL GTZC1 CFGR4 peripheral OCTOSPI2_MEM */
#endif /* OCTOSPI2 */
#if defined(HSPI1)
#define LL_GTZC1_GRP4_HSPI1_MEM    GTZC_CFGR4_HSPI1_MEM_Msk    /*!< LL GTZC1 CFGR4 peripheral HSPI1_MEM    */
#endif /* HSPI1 */
#define LL_GTZC1_GRP4_SRAM1        GTZC_CFGR4_SRAM1_Msk        /*!< LL GTZC1 CFGR4 peripheral SRAM1        */
#define LL_GTZC1_GRP4_MPCBB1_REG   GTZC_CFGR4_MPCBB1_REG_Msk   /*!< LL GTZC1 CFGR4 peripheral MPCBB1_REG   */
#define LL_GTZC1_GRP4_SRAM2        GTZC_CFGR4_SRAM2_Msk        /*!< LL GTZC1 CFGR4 peripheral SRAM2        */
#define LL_GTZC1_GRP4_MPCBB2_REG   GTZC_CFGR4_MPCBB2_REG_Msk   /*!< LL GTZC1 CFGR4 peripheral MPCBB2_REG   */
#if defined(SRAM3_BASE)
#define LL_GTZC1_GRP4_SRAM3        GTZC_CFGR4_SRAM3_Msk        /*!< LL GTZC1 CFGR4 peripheral SRAM3        */
#define LL_GTZC1_GRP4_MPCBB3_REG   GTZC_CFGR4_MPCBB3_REG_Msk   /*!< LL GTZC1 CFGR4 peripheral MPCBB3_REG   */
#endif /* SRAM3_BASE */
#if defined(SRAM5_BASE)
#define LL_GTZC1_GRP4_SRAM5        GTZC_CFGR4_SRAM5_Msk        /*!< LL GTZC1 CFGR4 peripheral SRAM5        */
#define LL_GTZC1_GRP4_MPCBB5_REG   GTZC_CFGR4_MPCBB5_REG_Msk   /*!< LL GTZC1 CFGR4 peripheral MPCBB5_REG   */
#endif /* SRAM5_BASE */

#if defined(SRAM5_BASE)
#define LL_GTZC1_GRP4_ALL          0xFF1FC01FU                 /*!< LL GTZC1 CFGR4 ALL peripherals         */
#elif defined(OCTOSPI2)
#define LL_GTZC1_GRP4_ALL          0x3F0FC01FU                 /*!< LL GTZC1 CFGR4 ALL peripherals         */
#else
#define LL_GTZC1_GRP4_ALL          0x0F05C00FU                 /*!< LL GTZC1 CFGR4 ALL peripherals         */
#endif /* SRAM5_BASE */

/**
  * @brief GTZC2 (ILAC/SEC/PRIV)CFGR2 peripheral selection
  */
#define LL_GTZC2_GRP1_SPI3    GTZC_CFGR1_SPI3_Msk    /*!< LL GTZC2 CFGR1 peripheral SPI3     */
#define LL_GTZC2_GRP1_LPUART1 GTZC_CFGR1_LPUART1_Msk /*!< LL GTZC2 CFGR1 peripheral LPUART1  */
#define LL_GTZC2_GRP1_I2C3    GTZC_CFGR1_I2C3_Msk    /*!< LL GTZC2 CFGR1 peripheral I2C3     */
#define LL_GTZC2_GRP1_LPTIM1  GTZC_CFGR1_LPTIM1_Msk  /*!< LL GTZC2 CFGR1 peripheral LPTIM1   */
#define LL_GTZC2_GRP1_LPTIM3  GTZC_CFGR1_LPTIM3_Msk  /*!< LL GTZC2 CFGR1 peripheral LPTIM3   */
#define LL_GTZC2_GRP1_LPTIM4  GTZC_CFGR1_LPTIM4_Msk  /*!< LL GTZC2 CFGR1 peripheral LPTIM4   */
#define LL_GTZC2_GRP1_OPAMP   GTZC_CFGR1_OPAMP_Msk   /*!< LL GTZC2 CFGR1 peripheral OPAMP    */
#define LL_GTZC2_GRP1_COMP    GTZC_CFGR1_COMP_Msk    /*!< LL GTZC2 CFGR1 peripheral COMP     */
#define LL_GTZC2_GRP1_ADC4    GTZC_CFGR1_ADC4_Msk    /*!< LL GTZC2 CFGR1 peripheral ADC4     */
#define LL_GTZC2_GRP1_VREFBUF GTZC_CFGR1_VREFBUF_Msk /*!< LL GTZC2 CFGR1 peripheral  VREFBUF */
#define LL_GTZC2_GRP1_DAC1    GTZC_CFGR1_DAC1_Msk    /*!< LL GTZC2 CFGR1 peripheral DAC1     */
#define LL_GTZC2_GRP1_ADF1    GTZC_CFGR1_ADF1_Msk    /*!< LL GTZC2 CFGR1 peripheral ADF1     */
#define LL_GTZC2_GRP1_ALL     0x00001BFFU            /*!< LL GTZC2 CFGR2 ALL peripherals     */

/**
  * @brief GTZC2 (ILAC)CFGR2 peripheral selection
  */
#define LL_GTZC2_GRP2_SYSCFG     GTZC_CFGR2_SYSCFG_Msk     /*!< LL GTZC2 CFGR2 peripheral SYSCFG     */
#define LL_GTZC2_GRP2_RTC        GTZC_CFGR2_RTC_Msk        /*!< LL GTZC2 CFGR2 peripheral RTC        */
#define LL_GTZC2_GRP2_TAMP       GTZC_CFGR2_TAMP_Msk       /*!< LL GTZC2 CFGR2 peripheral TAMP       */
#define LL_GTZC2_GRP2_PWR        GTZC_CFGR2_PWR_Msk        /*!< LL GTZC2 CFGR2 peripheral PWR        */
#define LL_GTZC2_GRP2_RCC        GTZC_CFGR2_RCC_Msk        /*!< LL GTZC2 CFGR2 peripheral RCC        */
#define LL_GTZC2_GRP2_LPDMA1     GTZC_CFGR2_LPDMA1_Msk     /*!< LL GTZC2 CFGR2 peripheral LPDMA1     */
#define LL_GTZC2_GRP2_EXTI       GTZC_CFGR2_EXTI_Msk       /*!< LL GTZC2 CFGR2 peripheral EXTI       */
#define LL_GTZC2_GRP2_TZSC2      GTZC_CFGR2_TZSC2_Msk      /*!< LL GTZC2 CFGR2 peripheral TZSC2      */
#define LL_GTZC2_GRP2_TZIC2      GTZC_CFGR2_TZIC2_Msk      /*!< LL GTZC2 CFGR2 peripheral TZIC2      */
#define LL_GTZC2_GRP2_SRAM4      GTZC_CFGR2_SRAM4_Msk      /*!< LL GTZC2 CFGR2 peripheral SRAM4      */
#define LL_GTZC2_GRP2_MPCBB4_REG GTZC_CFGR2_MPCBB4_REG_Msk /*!< LL GTZC2 CFGR2 peripheral MPCBB4_REG */
#define LL_GTZC2_GRP2_ALL        0x0300C07FU               /*!< LL GTZC2 CFGR2 ALL peripherals       */
/**
  * @}
  */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/** @defgroup GTZC_LL_EC_WatermarkSubRegionSelection Watermark Subregion Selection
  * @{
  */
#define LL_GTZC_TZSC_MPCWM_SUBREGION_A 0x00U /*!< LL GTZC TZSC Watermark subregion A */
#define LL_GTZC_TZSC_MPCWM_SUBREGION_B 0x01U /*!< LL GTZC TZSC Watermark subregion B */
/**
  * @}
  */
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/** @defgroup GTZC_LL_EC_PrivilegeAttributesSelection Privilege Attributes Selection
  * @{
  */
#define LL_GTZC_ATTR_NPRIV 0x00U /*!< LL GTZC Attribute non-privilege */
#define LL_GTZC_ATTR_PRIV  0x01U /*!< LL GTZC Attribute privilege     */
/**
  * @}
  */

/** @defgroup GTZC_LL_EC_SecurityAttributesSelection Security Attributes Selection
  * @{
  */
#define LL_GTZC_ATTR_NSEC 0x00U /*!< LL GTZC Attribute non-secure    */
#define LL_GTZC_ATTR_SEC  0x01U /*!< LL GTZC Attribute secure        */
/**
  * @}
  */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/** @defgroup GTZC_LL_EC_ClockSecurityInversion Clock Security Inversion
  * @{
  */
#define LL_GTZC_MPCBB_CLK_SEC_NOT_INVERTED 0x00U /*!< LL GTZC MPCBB Clock security not inverted */
#define LL_GTZC_MPCBB_CLK_SEC_INVERTED     0x01U /*!< LL GTZC MPCBB Clock security inverted     */
/**
  * @}
  */

/** @defgroup GTZC_LL_EC_SecureAccessState Secure Access State
  * @{
  */
#define LL_GTZC_MPCBB_SEC_ACCESS_NOT_ALLOWED 0x00 /*!< LL GTZC MPCBB SECURE ACCESS NOT ALLOWED */
#define LL_GTZC_MPCBB_SEC_ACCESS_ALLOWED     0x01 /*!< LL GTZC MPCBB SECURE ACCESS ALLOWED     */
/**
  * @}
  */
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/** @defgroup GTZC_LL_EC_MPCBB_Super_Block_Attr_Selection MPCBB Super Block Attr Selection
  * @{
  */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_0  0U  /*!< LL GTZC MPCBB SUPER BLOCK ATTR 0  */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_1  1U  /*!< LL GTZC MPCBB SUPER BLOCK ATTR 1  */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_2  2U  /*!< LL GTZC MPCBB SUPER BLOCK ATTR 2  */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_3  3U  /*!< LL GTZC MPCBB SUPER BLOCK ATTR 3  */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_4  4U  /*!< LL GTZC MPCBB SUPER BLOCK ATTR 4  */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_5  5U  /*!< LL GTZC MPCBB SUPER BLOCK ATTR 5  */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_6  6U  /*!< LL GTZC MPCBB SUPER BLOCK ATTR 6  */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_7  7U  /*!< LL GTZC MPCBB SUPER BLOCK ATTR 7  */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_8  8U  /*!< LL GTZC MPCBB SUPER BLOCK ATTR 8  */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_9  9U  /*!< LL GTZC MPCBB SUPER BLOCK ATTR 9  */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_10 10U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 10 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_11 11U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 11 */
#if defined (SRAM3_BASE)
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_12 12U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 12 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_13 13U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 13 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_14 14U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 14 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_15 15U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 15 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_16 16U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 16 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_17 17U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 17 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_18 18U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 18 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_19 19U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 19 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_20 20U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 20 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_21 21U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 21 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_22 22U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 22 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_23 23U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 23 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_24 24U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 24 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_25 25U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 25 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_26 26U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 26 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_27 27U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 27 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_28 28U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 28 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_29 29U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 29 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_30 30U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 30 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_31 31U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 31 */
#endif /* SRAM3_BASE */
#if defined (SRAM5_BASE)
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_32 32U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 32 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_33 33U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 33 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_34 34U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 34 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_35 35U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 35 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_36 36U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 36 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_37 37U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 37 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_38 38U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 38 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_39 39U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 39 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_40 40U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 40 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_41 41U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 41 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_42 42U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 42 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_43 43U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 43 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_44 44U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 44 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_45 45U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 45 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_46 46U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 46 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_47 47U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 47 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_48 48U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 48 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_49 49U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 49 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_50 50U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 50 */
#define LL_GTZC_MPCBB_SUPERBLK_ATTR_51 51U /*!< LL GTZC MPCBB SUPER BLOCK ATTR 51 */
#endif /* SRAM5_BASE */
/**
  * @}
  */

/** @defgroup GTZC_LL_EC_MPCBB_Super_Block_Lock_Selection MPCBB Super Block Lock Selection
  * @{
  */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_0   GTZC_MPCBB_CFGLOCKR1_SPLCK0_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 0  */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_1   GTZC_MPCBB_CFGLOCKR1_SPLCK1_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 1  */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_2   GTZC_MPCBB_CFGLOCKR1_SPLCK2_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 2  */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_3   GTZC_MPCBB_CFGLOCKR1_SPLCK3_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 3  */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_4   GTZC_MPCBB_CFGLOCKR1_SPLCK4_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 4  */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_5   GTZC_MPCBB_CFGLOCKR1_SPLCK5_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 5  */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_6   GTZC_MPCBB_CFGLOCKR1_SPLCK6_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 6  */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_7   GTZC_MPCBB_CFGLOCKR1_SPLCK7_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 7  */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_8   GTZC_MPCBB_CFGLOCKR1_SPLCK8_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 8  */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_9   GTZC_MPCBB_CFGLOCKR1_SPLCK9_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 9  */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_10  GTZC_MPCBB_CFGLOCKR1_SPLCK10_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 10 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_11  GTZC_MPCBB_CFGLOCKR1_SPLCK11_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 11 */
#if defined (SRAM3_BASE)
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_12  GTZC_MPCBB_CFGLOCKR1_SPLCK12_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 12 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_13  GTZC_MPCBB_CFGLOCKR1_SPLCK13_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 13 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_14  GTZC_MPCBB_CFGLOCKR1_SPLCK14_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 14 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_15  GTZC_MPCBB_CFGLOCKR1_SPLCK15_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 15 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_16  GTZC_MPCBB_CFGLOCKR1_SPLCK16_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 16 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_17  GTZC_MPCBB_CFGLOCKR1_SPLCK17_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 17 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_18  GTZC_MPCBB_CFGLOCKR1_SPLCK18_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 18 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_19  GTZC_MPCBB_CFGLOCKR1_SPLCK19_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 19 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_20  GTZC_MPCBB_CFGLOCKR1_SPLCK20_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 20 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_21  GTZC_MPCBB_CFGLOCKR1_SPLCK21_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 21 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_22  GTZC_MPCBB_CFGLOCKR1_SPLCK22_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 22 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_23  GTZC_MPCBB_CFGLOCKR1_SPLCK23_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 23 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_24  GTZC_MPCBB_CFGLOCKR1_SPLCK24_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 24 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_25  GTZC_MPCBB_CFGLOCKR1_SPLCK25_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 25 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_26  GTZC_MPCBB_CFGLOCKR1_SPLCK26_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 26 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_27  GTZC_MPCBB_CFGLOCKR1_SPLCK27_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 27 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_28  GTZC_MPCBB_CFGLOCKR1_SPLCK28_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 28 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_29  GTZC_MPCBB_CFGLOCKR1_SPLCK29_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 29 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_30  GTZC_MPCBB_CFGLOCKR1_SPLCK30_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 30 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_31  GTZC_MPCBB_CFGLOCKR1_SPLCK31_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 31 */
#endif /* SRAM3_BASE */
#if defined (SRAM5_BASE)
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_32  GTZC_MPCBB_CFGLOCKR2_SPLCK32_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 32 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_33  GTZC_MPCBB_CFGLOCKR2_SPLCK33_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 33 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_34  GTZC_MPCBB_CFGLOCKR2_SPLCK34_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 34 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_35  GTZC_MPCBB_CFGLOCKR2_SPLCK35_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 35 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_36  GTZC_MPCBB_CFGLOCKR2_SPLCK36_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 36 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_37  GTZC_MPCBB_CFGLOCKR2_SPLCK37_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 37 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_38  GTZC_MPCBB_CFGLOCKR2_SPLCK38_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 38 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_39  GTZC_MPCBB_CFGLOCKR2_SPLCK39_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 39 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_40  GTZC_MPCBB_CFGLOCKR2_SPLCK40_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 40 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_41  GTZC_MPCBB_CFGLOCKR2_SPLCK41_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 41 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_42  GTZC_MPCBB_CFGLOCKR2_SPLCK42_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 42 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_43  GTZC_MPCBB_CFGLOCKR2_SPLCK43_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 43 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_44  GTZC_MPCBB_CFGLOCKR2_SPLCK44_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 44 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_45  GTZC_MPCBB_CFGLOCKR2_SPLCK45_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 45 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_46  GTZC_MPCBB_CFGLOCKR2_SPLCK46_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 46 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_47  GTZC_MPCBB_CFGLOCKR2_SPLCK47_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 47 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_48  GTZC_MPCBB_CFGLOCKR2_SPLCK48_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 48 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_49  GTZC_MPCBB_CFGLOCKR2_SPLCK49_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 49 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_50  GTZC_MPCBB_CFGLOCKR2_SPLCK50_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 50 */
#define LL_GTZC_MPCBB_SUPERBLK_LOCK_51  GTZC_MPCBB_CFGLOCKR2_SPLCK51_Msk /*!< LL GTZC MPCBB SUPER BLOCK LOCK 51 */
#endif /* SRAM5_BASE */
/**
  * @}
  */

/** @defgroup GTZC_LL_EC_MPCBB_Block_Selection MPCBB Block Selection
  * @{
  */
#define LL_GTZC_MPCBB_BLK_0  0x00000001U /*!< LL GTZC MPCBB BLOCK 0  */
#define LL_GTZC_MPCBB_BLK_1  0x00000002U /*!< LL GTZC MPCBB BLOCK 1  */
#define LL_GTZC_MPCBB_BLK_2  0x00000004U /*!< LL GTZC MPCBB BLOCK 2  */
#define LL_GTZC_MPCBB_BLK_3  0x00000008U /*!< LL GTZC MPCBB BLOCK 3  */
#define LL_GTZC_MPCBB_BLK_4  0x00000010U /*!< LL GTZC MPCBB BLOCK 4  */
#define LL_GTZC_MPCBB_BLK_5  0x00000020U /*!< LL GTZC MPCBB BLOCK 5  */
#define LL_GTZC_MPCBB_BLK_6  0x00000040U /*!< LL GTZC MPCBB BLOCK 6  */
#define LL_GTZC_MPCBB_BLK_7  0x00000080U /*!< LL GTZC MPCBB BLOCK 7  */
#define LL_GTZC_MPCBB_BLK_8  0x00000100U /*!< LL GTZC MPCBB BLOCK 8  */
#define LL_GTZC_MPCBB_BLK_9  0x00000200U /*!< LL GTZC MPCBB BLOCK 9  */
#define LL_GTZC_MPCBB_BLK_10 0x00000400U /*!< LL GTZC MPCBB BLOCK 10 */
#define LL_GTZC_MPCBB_BLK_11 0x00000800U /*!< LL GTZC MPCBB BLOCK 11 */
#if defined (SRAM3_BASE)
#define LL_GTZC_MPCBB_BLK_12 0x00001000U /*!< LL GTZC MPCBB BLOCK 12 */
#define LL_GTZC_MPCBB_BLK_13 0x00002000U /*!< LL GTZC MPCBB BLOCK 13 */
#define LL_GTZC_MPCBB_BLK_14 0x00004000U /*!< LL GTZC MPCBB BLOCK 14 */
#define LL_GTZC_MPCBB_BLK_15 0x00008000U /*!< LL GTZC MPCBB BLOCK 15 */
#define LL_GTZC_MPCBB_BLK_16 0x00010000U /*!< LL GTZC MPCBB BLOCK 16 */
#define LL_GTZC_MPCBB_BLK_17 0x00020000U /*!< LL GTZC MPCBB BLOCK 17 */
#define LL_GTZC_MPCBB_BLK_18 0x00040000U /*!< LL GTZC MPCBB BLOCK 18 */
#define LL_GTZC_MPCBB_BLK_19 0x00080000U /*!< LL GTZC MPCBB BLOCK 19 */
#define LL_GTZC_MPCBB_BLK_20 0x00100000U /*!< LL GTZC MPCBB BLOCK 20 */
#define LL_GTZC_MPCBB_BLK_21 0x00200000U /*!< LL GTZC MPCBB BLOCK 21 */
#define LL_GTZC_MPCBB_BLK_22 0x00400000U /*!< LL GTZC MPCBB BLOCK 22 */
#define LL_GTZC_MPCBB_BLK_23 0x00800000U /*!< LL GTZC MPCBB BLOCK 23 */
#define LL_GTZC_MPCBB_BLK_24 0x01000000U /*!< LL GTZC MPCBB BLOCK 24 */
#define LL_GTZC_MPCBB_BLK_25 0x02000000U /*!< LL GTZC MPCBB BLOCK 25 */
#define LL_GTZC_MPCBB_BLK_26 0x04000000U /*!< LL GTZC MPCBB BLOCK 26 */
#define LL_GTZC_MPCBB_BLK_27 0x08000000U /*!< LL GTZC MPCBB BLOCK 27 */
#define LL_GTZC_MPCBB_BLK_28 0x10000000U /*!< LL GTZC MPCBB BLOCK 28 */
#define LL_GTZC_MPCBB_BLK_29 0x20000000U /*!< LL GTZC MPCBB BLOCK 29 */
#define LL_GTZC_MPCBB_BLK_30 0x40000000U /*!< LL GTZC MPCBB BLOCK 30 */
#define LL_GTZC_MPCBB_BLK_31 0x80000000U /*!< LL GTZC MPCBB BLOCK 31 */
#endif /* SRAM3_BASE */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_LL_Exported_Macros GTZC Exported Macros
  * @{
  */

/**
  * @brief  Write a value in GTZC register.
  * @param  instance GTZC Instance.
  * @param  reg      Register to be written.
  * @param  value    Value to be written in the register.
  */
#define LL_GTZC_WRITE_REG(instance, reg, value) WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in GTZC register
  * @param  instance GTZC Instance
  * @param  reg      Register to be read
  * @retval Register value
  */
#define LL_GTZC_READ_REG(instance, reg) READ_REG((instance)->reg)
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_LL_Exported_Functions GTZC Exported Functions
  * @{
  */

/** @defgroup GTZC_TZSC_LL_EF_Management GTZC TZSC Management
  * @{
  */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Lock of peripheral attributes.
  * @rmtoll
  *  CR           LCK         LL_GTZC_TZSC_LockPeriphAttr
  * @param  p_tzsc TZSC Instance
  * @if GTZC_TZSC1
  *         @arg @ref GTZC1_TZSC1_SEC_PERIPH
  * @endif
  * @if GTZC_TZSC2
  *         @arg @ref GTZC2_TZSC1_SEC_PERIPH
  * @endif
  */
__STATIC_INLINE void LL_GTZC_TZSC_LockPeriphAttr(GTZC_TZSC_SecPeriph_TypeDef *p_tzsc)
{
  SET_BIT(p_tzsc->CR, GTZC_TZSC_CR_LCK_Msk);
}

/**
  * @brief  Check if peripheral attributes is locked.
  * @rmtoll
  *  CR           LCK         LL_GTZC_TZSC_IsLockedPeriphAttr
  * @param  p_tzsc TZSC Instance
  * @if GTZC_TZSC1
  *         @arg @ref GTZC1_TZSC1_SEC_PERIPH
  * @endif
  * @if GTZC_TZSC2
  *         @arg @ref GTZC2_TZSC1_SEC_PERIPH
  * @endif
  * @retval State of parameter value (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_IsLockedPeriphAttr(const GTZC_TZSC_SecPeriph_TypeDef *p_tzsc)
{
  return ((READ_BIT(p_tzsc->CR, GTZC_TZSC_CR_LCK_Msk) == GTZC_TZSC_CR_LCK_Msk) ? 1UL : 0UL);
}

/**
  * @brief  Set SECCFGR1 peripherals security attribute.
  * @rmtoll
  *  SECCFGR1           xxxSEC         LL_GTZC_TZSC_SetSecurityAttribute_SECCFGR1
  * @param  p_tzsc TZSC Instance
  * @if GTZC_TZSC1
  *         @arg @ref GTZC1_TZSC1_SEC_PERIPH
  * @endif
  * @if GTZC_TZSC2
  *         @arg @ref GTZC2_TZSC1_SEC_PERIPH
  * @endif
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP1_TIM2
  *         @arg @ref LL_GTZC1_GRP1_TIM3
  *         @arg @ref LL_GTZC1_GRP1_TIM4
  *         @arg @ref LL_GTZC1_GRP1_TIM5
  *         @arg @ref LL_GTZC1_GRP1_TIM6
  *         @arg @ref LL_GTZC1_GRP1_TIM7
  *         @arg @ref LL_GTZC1_GRP1_WWDG
  *         @arg @ref LL_GTZC1_GRP1_IWDG
  *         @arg @ref LL_GTZC1_GRP1_SPI2
  * @if USART2
  *         @arg @ref LL_GTZC1_GRP1_USART2
  * @endif
  *         @arg @ref LL_GTZC1_GRP1_USART3
  *         @arg @ref LL_GTZC1_GRP1_UART4
  *         @arg @ref LL_GTZC1_GRP1_UART5
  *         @arg @ref LL_GTZC1_GRP1_I2C1
  *         @arg @ref LL_GTZC1_GRP1_I2C2
  *         @arg @ref LL_GTZC1_GRP1_CRS
  *         @arg @ref LL_GTZC1_GRP1_I2C4
  *         @arg @ref LL_GTZC1_GRP1_LPTIM2
  *         @arg @ref LL_GTZC1_GRP1_FDCAN1
  * @if UCPD1
  *         @arg @ref LL_GTZC1_GRP1_UCPD1
  * @endif
  * @if USART6
  *         @arg @ref LL_GTZC1_GRP1_USART6
  * @endif
  * @if I2C5
  *         @arg @ref LL_GTZC1_GRP1_I2C5
  * @endif
  * @if I2C6
  *         @arg @ref LL_GTZC1_GRP1_I2C6
  * @endif
  *
  *         @arg @ref LL_GTZC2_GRP1_SPI3
  *         @arg @ref LL_GTZC2_GRP1_LPUART1
  *         @arg @ref LL_GTZC2_GRP1_I2C3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM1
  *         @arg @ref LL_GTZC2_GRP1_LPTIM3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM4
  *         @arg @ref LL_GTZC2_GRP1_OPAMP
  *         @arg @ref LL_GTZC2_GRP1_COMP
  *         @arg @ref LL_GTZC2_GRP1_ADC4
  *         @arg @ref LL_GTZC2_GRP1_VREFBUF
  *         @arg @ref LL_GTZC2_GRP1_DAC1
  *         @arg @ref LL_GTZC2_GRP1_ADF1
  * @param  attr This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_ATTR_NSEC
  *         @arg @ref LL_GTZC_ATTR_SEC
  */
__STATIC_INLINE void LL_GTZC_TZSC_SetPeriphGrp1SecurityAttr(GTZC_TZSC_SecPeriph_TypeDef *p_tzsc,
                                                            uint32_t periph,
                                                            uint32_t attr)
{
  ATOMIC_MODIFY_REG(p_tzsc->SECCFGR1, periph, (attr * periph));
}
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Get SECCFGR1 peripheral security attribute.
  * @rmtoll
  *  SECCFGR1           xxxSEC         LL_GTZC_TZSC_GetSecurityAttribute_SECCFGR1
  * @param  p_tzsc TZSC Instance
  * @if GTZC_TZSC1
  *         @arg @ref GTZC1_TZSC1_SEC_PERIPH
  * @endif
  * @if GTZC_TZSC2
  *         @arg @ref GTZC2_TZSC1_SEC_PERIPH
  * @endif
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP1_TIM2
  *         @arg @ref LL_GTZC1_GRP1_TIM3
  *         @arg @ref LL_GTZC1_GRP1_TIM4
  *         @arg @ref LL_GTZC1_GRP1_TIM5
  *         @arg @ref LL_GTZC1_GRP1_TIM6
  *         @arg @ref LL_GTZC1_GRP1_TIM7
  *         @arg @ref LL_GTZC1_GRP1_WWDG
  *         @arg @ref LL_GTZC1_GRP1_IWDG
  *         @arg @ref LL_GTZC1_GRP1_SPI2
  * @if USART2
  *         @arg @ref LL_GTZC1_GRP1_USART2
  * @endif
  *         @arg @ref LL_GTZC1_GRP1_USART3
  *         @arg @ref LL_GTZC1_GRP1_UART4
  *         @arg @ref LL_GTZC1_GRP1_UART5
  *         @arg @ref LL_GTZC1_GRP1_I2C1
  *         @arg @ref LL_GTZC1_GRP1_I2C2
  *         @arg @ref LL_GTZC1_GRP1_CRS
  *         @arg @ref LL_GTZC1_GRP1_I2C4
  *         @arg @ref LL_GTZC1_GRP1_LPTIM2
  *         @arg @ref LL_GTZC1_GRP1_FDCAN1
  * @if UCPD1
  *         @arg @ref LL_GTZC1_GRP1_UCPD1
  * @endif
  * @if USART6
  *         @arg @ref LL_GTZC1_GRP1_USART6
  * @endif
  * @if I2C5
  *         @arg @ref LL_GTZC1_GRP1_I2C5
  * @endif
  * @if I2C6
  *         @arg @ref LL_GTZC1_GRP1_I2C6
  * @endif
  *
  *         @arg @ref LL_GTZC2_GRP1_SPI3
  *         @arg @ref LL_GTZC2_GRP1_LPUART1
  *         @arg @ref LL_GTZC2_GRP1_I2C3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM1
  *         @arg @ref LL_GTZC2_GRP1_LPTIM3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM4
  *         @arg @ref LL_GTZC2_GRP1_OPAMP
  *         @arg @ref LL_GTZC2_GRP1_COMP
  *         @arg @ref LL_GTZC2_GRP1_ADC4
  *         @arg @ref LL_GTZC2_GRP1_VREFBUF
  *         @arg @ref LL_GTZC2_GRP1_DAC1
  *         @arg @ref LL_GTZC2_GRP1_ADF1
  * @retval State of bit (0 Non-secure / 1 Secure)
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_GetPeriphGrp1SecurityAttr(const GTZC_TZSC_SecPeriph_TypeDef *p_tzsc,
                                                                uint32_t periph)
{
  return (READ_BIT(p_tzsc->SECCFGR1, periph));
}

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Set SECCFGR2 peripherals security attribute.
  * @rmtoll
  *  SECCFGR2           xxxSEC         LL_GTZC_TZSC_SetSecurityAttribute_SECCFGR2
  * @param  p_tzsc TZSC Instance
  * @if GTZC_TZSC1
  *         @arg @ref GTZC1_TZSC1_SEC_PERIPH
  * @endif
  * @if GTZC_TZSC2
  *         @arg @ref GTZC2_TZSC1_SEC_PERIPH
  * @endif
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP2_TIM1
  *         @arg @ref LL_GTZC1_GRP2_SPI1
  *         @arg @ref LL_GTZC1_GRP2_TIM8
  *         @arg @ref LL_GTZC1_GRP2_USART1
  *         @arg @ref LL_GTZC1_GRP2_TIM15
  *         @arg @ref LL_GTZC1_GRP2_TIM16
  *         @arg @ref LL_GTZC1_GRP2_TIM17
  *         @arg @ref LL_GTZC1_GRP2_SAI1
  * @if SAI2
  *         @arg @ref LL_GTZC1_GRP2_SAI2
  * @endif
  * @if GTZC_CFGR2_LTDCUSB_Msk
  *         @arg @ref LL_GTZC1_GRP2_LTDC_USB
  * @endif
  * @if DSI
  *         @arg @ref LL_GTZC1_GRP2_DSI
  * @endif
  * @param  attr This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_ATTR_NSEC
  *         @arg @ref LL_GTZC_ATTR_SEC
  */
__STATIC_INLINE void LL_GTZC_TZSC_SetPeriphGrp2SecurityAttr(GTZC_TZSC_SecPeriph_TypeDef *p_tzsc,
                                                            uint32_t periph,
                                                            uint32_t attr)
{
  ATOMIC_MODIFY_REG(p_tzsc->SECCFGR2, periph, (attr * periph));
}
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Get SECCFGR2 peripherals security attribute.
  * @rmtoll
  *  SECCFGR2           xxxSEC         LL_GTZC_TZSC_GetSecurityAttribute_SECCFGR2
  * @param  p_tzsc TZSC Instance
  * @if GTZC_TZSC1
  *         @arg @ref GTZC1_TZSC1_SEC_PERIPH
  * @endif
  * @if GTZC_TZSC2
  *         @arg @ref GTZC2_TZSC1_SEC_PERIPH
  * @endif
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP2_TIM1
  *         @arg @ref LL_GTZC1_GRP2_SPI1
  *         @arg @ref LL_GTZC1_GRP2_TIM8
  *         @arg @ref LL_GTZC1_GRP2_USART1
  *         @arg @ref LL_GTZC1_GRP2_TIM15
  *         @arg @ref LL_GTZC1_GRP2_TIM16
  *         @arg @ref LL_GTZC1_GRP2_TIM17
  *         @arg @ref LL_GTZC1_GRP2_SAI1
  * @if SAI2
  *         @arg @ref LL_GTZC1_GRP2_SAI2
  * @endif
  * @if GTZC_CFGR2_LTDCUSB_Msk
  *         @arg @ref LL_GTZC1_GRP2_LTDC_USB
  * @endif
  * @if DSI
  *         @arg @ref LL_GTZC1_GRP2_DSI
  * @endif
  * @retval State of bit (0 Non-secure / 1 Secure)
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_GetPeriphGrp2SecurityAttr(const GTZC_TZSC_SecPeriph_TypeDef *p_tzsc,
                                                                uint32_t periph)
{
  return (READ_BIT(p_tzsc->SECCFGR2, periph));
}

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Set SECCFGR3 peripherals security attribute.
  * @rmtoll
  *  SECCFGR3           xxxSEC         LL_GTZC_TZSC_SetSecurityAttribute_SECCFGR3
  * @param  p_tzsc TZSC Instance
  * @if GTZC_TZSC1
  *         @arg @ref GTZC1_TZSC1_SEC_PERIPH
  * @endif
  * @if GTZC_TZSC2
  *         @arg @ref GTZC2_TZSC1_SEC_PERIPH
  * @endif
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP3_MDF1
  *         @arg @ref LL_GTZC1_GRP3_CORDIC
  *         @arg @ref LL_GTZC1_GRP3_FMAC
  *         @arg @ref LL_GTZC1_GRP3_CRC
  *         @arg @ref LL_GTZC1_GRP3_TSC
  * @if DMA2D
  *         @arg @ref LL_GTZC1_GRP3_DMA2D
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_ICACHE_REG
  *         @arg @ref LL_GTZC1_GRP3_DCACHE1_REG
  *         @arg @ref LL_GTZC1_GRP3_ADC12
  *         @arg @ref LL_GTZC1_GRP3_DCMI
  * @if USB_OTG_GLOBAL_BASE
  *         @arg @ref LL_GTZC1_GRP3_OTG
  * @endif
  * @if AES
  *         @arg @ref LL_GTZC1_GRP3_AES
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_HASH
  *         @arg @ref LL_GTZC1_GRP3_RNG
  * @if PKA
  *         @arg @ref LL_GTZC1_GRP3_PKA
  * @endif
  * @if SAES
  *         @arg @ref LL_GTZC1_GRP3_SAES
  * @endif
  * @if OCTOSPIM
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPIM
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_SDMMC1
  * @if SDMMC2
  *         @arg @ref LL_GTZC1_GRP3_SDMMC2
  * @endif
  * @if FMC_BASE
  *         @arg @ref LL_GTZC1_GRP3_FSMC_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI1_REG
  * @if OCTOSPI2
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI2_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_RAMCFG
  * @if GPU2D
  *         @arg @ref LL_GTZC1_GRP3_GPU2D
  * @endif
  * @if GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU_REG
  * @endif
  * @if HSPI1
  *         @arg @ref LL_GTZC1_GRP3_HSPI1_REG
  * @endif
  * @if DCACHE2
  *         @arg @ref LL_GTZC1_GRP3_DCACHE2_REG
  * @endif
  * @param  attr This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_ATTR_NSEC
  *         @arg @ref LL_GTZC_ATTR_SEC
  */
__STATIC_INLINE void LL_GTZC_TZSC_SetPeriphGrp3SecurityAttr(GTZC_TZSC_SecPeriph_TypeDef *p_tzsc,
                                                            uint32_t periph,
                                                            uint32_t attr)
{
  ATOMIC_MODIFY_REG(p_tzsc->SECCFGR3, periph, (attr * periph));
}
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Get SECCFGR3 peripherals security attribute.
  * @rmtoll
  *  SECCFGR3           xxxSEC         LL_GTZC_TZSC_GetSecurityAttribute_SECCFGR3
  * @param  p_tzsc TZSC Instance
  * @if GTZC_TZSC1
  *         @arg @ref GTZC1_TZSC1_SEC_PERIPH
  * @endif
  * @if GTZC_TZSC2
  *         @arg @ref GTZC2_TZSC1_SEC_PERIPH
  * @endif
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP3_MDF1
  *         @arg @ref LL_GTZC1_GRP3_CORDIC
  *         @arg @ref LL_GTZC1_GRP3_FMAC
  *         @arg @ref LL_GTZC1_GRP3_CRC
  *         @arg @ref LL_GTZC1_GRP3_TSC
  * @if DMA2D
  *         @arg @ref LL_GTZC1_GRP3_DMA2D
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_ICACHE_REG
  *         @arg @ref LL_GTZC1_GRP3_DCACHE1_REG
  *         @arg @ref LL_GTZC1_GRP3_ADC12
  *         @arg @ref LL_GTZC1_GRP3_DCMI
  * @if USB_OTG_GLOBAL_BASE
  *         @arg @ref LL_GTZC1_GRP3_OTG
  * @endif
  * @if AES
  *         @arg @ref LL_GTZC1_GRP3_AES
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_HASH
  *         @arg @ref LL_GTZC1_GRP3_RNG
  * @if PKA
  *         @arg @ref LL_GTZC1_GRP3_PKA
  * @endif
  * @if SAES
  *         @arg @ref LL_GTZC1_GRP3_SAES
  * @endif
  * @if OCTOSPIM
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPIM
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_SDMMC1
  * @if SDMMC2
  *         @arg @ref LL_GTZC1_GRP3_SDMMC2
  * @endif
  * @if FMC_BASE
  *         @arg @ref LL_GTZC1_GRP3_FSMC_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI1_REG
  * @if OCTOSPI2
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI2_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_RAMCFG
  * @if GPU2D
  *         @arg @ref LL_GTZC1_GRP3_GPU2D
  * @endif
  * @if GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU_REG
  * @endif
  * @if HSPI1
  *         @arg @ref LL_GTZC1_GRP3_HSPI1_REG
  * @endif
  * @if DCACHE2
  *         @arg @ref LL_GTZC1_GRP3_DCACHE2_REG
  * @endif
  * @retval State of bit (0 Non-secure / 1 Secure)
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_GetPeriphGrp3SecurityAttr(const GTZC_TZSC_SecPeriph_TypeDef *p_tzsc,
                                                                uint32_t periph)
{
  return (READ_BIT(p_tzsc->SECCFGR3, periph));
}

/**
  * @brief  Set PRIVCFGR1 peripherals privilege attribute.
  * @rmtoll
  *  PRIVCFGR1           xxxPRIV         LL_GTZC_TZSC_SetPrivilegeAttribute_PRIVCFGR1
  * @param  p_tzsc TZSC Instance
  * @if GTZC_TZSC1
  *         @arg @ref GTZC1_TZSC1_SEC_PERIPH
  * @endif
  * @if GTZC_TZSC2
  *         @arg @ref GTZC2_TZSC1_SEC_PERIPH
  * @endif
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP1_TIM2
  *         @arg @ref LL_GTZC1_GRP1_TIM3
  *         @arg @ref LL_GTZC1_GRP1_TIM4
  *         @arg @ref LL_GTZC1_GRP1_TIM5
  *         @arg @ref LL_GTZC1_GRP1_TIM6
  *         @arg @ref LL_GTZC1_GRP1_TIM7
  *         @arg @ref LL_GTZC1_GRP1_WWDG
  *         @arg @ref LL_GTZC1_GRP1_IWDG
  *         @arg @ref LL_GTZC1_GRP1_SPI2
  * @if USART2
  *         @arg @ref LL_GTZC1_GRP1_USART2
  * @endif
  *         @arg @ref LL_GTZC1_GRP1_USART3
  *         @arg @ref LL_GTZC1_GRP1_UART4
  *         @arg @ref LL_GTZC1_GRP1_UART5
  *         @arg @ref LL_GTZC1_GRP1_I2C1
  *         @arg @ref LL_GTZC1_GRP1_I2C2
  *         @arg @ref LL_GTZC1_GRP1_CRS
  *         @arg @ref LL_GTZC1_GRP1_I2C4
  *         @arg @ref LL_GTZC1_GRP1_LPTIM2
  *         @arg @ref LL_GTZC1_GRP1_FDCAN1
  * @if UCPD1
  *         @arg @ref LL_GTZC1_GRP1_UCPD1
  * @endif
  * @if USART6
  *         @arg @ref LL_GTZC1_GRP1_USART6
  * @endif
  * @if I2C5
  *         @arg @ref LL_GTZC1_GRP1_I2C5
  * @endif
  * @if I2C6
  *         @arg @ref LL_GTZC1_GRP1_I2C6
  * @endif
  *         @arg @ref LL_GTZC2_GRP1_SPI3
  *         @arg @ref LL_GTZC2_GRP1_LPUART1
  *         @arg @ref LL_GTZC2_GRP1_I2C3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM1
  *         @arg @ref LL_GTZC2_GRP1_LPTIM3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM4
  *         @arg @ref LL_GTZC2_GRP1_OPAMP
  *         @arg @ref LL_GTZC2_GRP1_COMP
  *         @arg @ref LL_GTZC2_GRP1_ADC4
  *         @arg @ref LL_GTZC2_GRP1_VREFBUF
  *         @arg @ref LL_GTZC2_GRP1_DAC1
  *         @arg @ref LL_GTZC2_GRP1_ADF1
  * @param  attr This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_ATTR_NPRIV
  *         @arg @ref LL_GTZC_ATTR_PRIV
  */
__STATIC_INLINE void LL_GTZC_TZSC_SetPeriphGrp1PrivilegeAttr(GTZC_TZSC_SecPeriph_TypeDef *p_tzsc,
                                                             uint32_t periph,
                                                             uint32_t attr)
{
  ATOMIC_MODIFY_REG(p_tzsc->PRIVCFGR1, periph, (attr * periph));
}

/**
  * @brief  Get PRIVCFGR1 peripheral privilege attribute.
  * @rmtoll
  *  PRIVCFGR1           xxxPRIV         LL_GTZC_TZSC_GetPrivilegeAttribute_PRIVCFGR1
  * @param  p_tzsc TZSC Instance
  * @if GTZC_TZSC1
  *         @arg @ref GTZC1_TZSC1_SEC_PERIPH
  * @endif
  * @if GTZC_TZSC2
  *         @arg @ref GTZC2_TZSC1_SEC_PERIPH
  * @endif
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP1_TIM2
  *         @arg @ref LL_GTZC1_GRP1_TIM3
  *         @arg @ref LL_GTZC1_GRP1_TIM4
  *         @arg @ref LL_GTZC1_GRP1_TIM5
  *         @arg @ref LL_GTZC1_GRP1_TIM6
  *         @arg @ref LL_GTZC1_GRP1_TIM7
  *         @arg @ref LL_GTZC1_GRP1_WWDG
  *         @arg @ref LL_GTZC1_GRP1_IWDG
  *         @arg @ref LL_GTZC1_GRP1_SPI2
  * @if USART2
  *         @arg @ref LL_GTZC1_GRP1_USART2
  * @endif
  *         @arg @ref LL_GTZC1_GRP1_USART3
  *         @arg @ref LL_GTZC1_GRP1_UART4
  *         @arg @ref LL_GTZC1_GRP1_UART5
  *         @arg @ref LL_GTZC1_GRP1_I2C1
  *         @arg @ref LL_GTZC1_GRP1_I2C2
  *         @arg @ref LL_GTZC1_GRP1_CRS
  *         @arg @ref LL_GTZC1_GRP1_I2C4
  *         @arg @ref LL_GTZC1_GRP1_LPTIM2
  *         @arg @ref LL_GTZC1_GRP1_FDCAN1
  * @if UCPD1
  *         @arg @ref LL_GTZC1_GRP1_UCPD1
  * @endif
  * @if USART6
  *         @arg @ref LL_GTZC1_GRP1_USART6
  * @endif
  * @if I2C5
  *         @arg @ref LL_GTZC1_GRP1_I2C5
  * @endif
  * @if I2C6
  *         @arg @ref LL_GTZC1_GRP1_I2C6
  * @endif
  *
  *         @arg @ref LL_GTZC2_GRP1_SPI3
  *         @arg @ref LL_GTZC2_GRP1_LPUART1
  *         @arg @ref LL_GTZC2_GRP1_I2C3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM1
  *         @arg @ref LL_GTZC2_GRP1_LPTIM3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM4
  *         @arg @ref LL_GTZC2_GRP1_OPAMP
  *         @arg @ref LL_GTZC2_GRP1_COMP
  *         @arg @ref LL_GTZC2_GRP1_ADC4
  *         @arg @ref LL_GTZC2_GRP1_VREFBUF
  *         @arg @ref LL_GTZC2_GRP1_DAC1
  *         @arg @ref LL_GTZC2_GRP1_ADF1
  * @retval State of bit (0 Non-privilege / 1 Privilege)
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_GetPeriphGrp1PrivilegeAttr(const GTZC_TZSC_SecPeriph_TypeDef *p_tzsc,
                                                                 uint32_t periph)
{
  return (READ_BIT(p_tzsc->PRIVCFGR1, periph));
}

/**
  * @brief  Set PRIVCFGR2 peripheral privilege attribute.
  * @rmtoll
  *  PRIVCFGR2           xxxPRIV         LL_GTZC_TZSC_SetPrivilegeAttribute_PRIVCFGR2
  * @param  p_tzsc TZSC Instance
  * @if GTZC_TZSC1
  *         @arg @ref GTZC1_TZSC1_SEC_PERIPH
  * @endif
  * @if GTZC_TZSC2
  *         @arg @ref GTZC2_TZSC1_SEC_PERIPH
  * @endif
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP2_TIM1
  *         @arg @ref LL_GTZC1_GRP2_SPI1
  *         @arg @ref LL_GTZC1_GRP2_TIM8
  *         @arg @ref LL_GTZC1_GRP2_USART1
  *         @arg @ref LL_GTZC1_GRP2_TIM15
  *         @arg @ref LL_GTZC1_GRP2_TIM16
  *         @arg @ref LL_GTZC1_GRP2_TIM17
  *         @arg @ref LL_GTZC1_GRP2_SAI1
  * @if SAI2
  *         @arg @ref LL_GTZC1_GRP2_SAI2
  * @endif
  * @if GTZC_CFGR2_LTDCUSB_Msk
  *         @arg @ref LL_GTZC1_GRP2_LTDC_USB
  * @endif
  * @if DSI
  *         @arg @ref LL_GTZC1_GRP2_DSI
  * @endif
  * @param  attr This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_ATTR_NPRIV
  *         @arg @ref LL_GTZC_ATTR_PRIV
  */
__STATIC_INLINE void LL_GTZC_TZSC_SetPeriphGrp2PrivilegeAttr(GTZC_TZSC_SecPeriph_TypeDef *p_tzsc,
                                                             uint32_t periph,
                                                             uint32_t attr)
{
  ATOMIC_MODIFY_REG(p_tzsc->PRIVCFGR2, periph, (attr * periph));
}

/**
  * @brief  Get PRIVCFGR2 peripheral privilege attribute.
  * @rmtoll
  *  PRIVCFGR2           xxxPRIV         LL_GTZC_TZSC_GetPrivilegeAttribute_PRIVCFGR2
  * @param  p_tzsc TZSC Instance
  * @if GTZC_TZSC1
  *         @arg @ref GTZC1_TZSC1_SEC_PERIPH
  * @endif
  * @if GTZC_TZSC2
  *         @arg @ref GTZC2_TZSC1_SEC_PERIPH
  * @endif
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP2_TIM1
  *         @arg @ref LL_GTZC1_GRP2_SPI1
  *         @arg @ref LL_GTZC1_GRP2_TIM8
  *         @arg @ref LL_GTZC1_GRP2_USART1
  *         @arg @ref LL_GTZC1_GRP2_TIM15
  *         @arg @ref LL_GTZC1_GRP2_TIM16
  *         @arg @ref LL_GTZC1_GRP2_TIM17
  *         @arg @ref LL_GTZC1_GRP2_SAI1
  * @if SAI2
  *         @arg @ref LL_GTZC1_GRP2_SAI2
  * @endif
  * @if GTZC_CFGR2_LTDCUSB_Msk
  *         @arg @ref LL_GTZC1_GRP2_LTDC_USB
  * @endif
  * @if DSI
  *         @arg @ref LL_GTZC1_GRP2_DSI
  * @endif
  * @retval State of bit (0 Non-privilege / 1 Privilege)
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_GetPeriphGrp2PrivilegeAttr(const GTZC_TZSC_SecPeriph_TypeDef *p_tzsc,
                                                                 uint32_t periph)
{
  return (READ_BIT(p_tzsc->PRIVCFGR2, periph));
}

/**
  * @brief  Set PRIVCFGR3 peripheral privilege attribute.
  * @rmtoll
  *  PRIVCFGR3           xxxPRIV         LL_GTZC_TZSC_SetPrivilegeAttribute_PRIVCFGR3
  * @param  p_tzsc TZSC Instance
  * @if GTZC_TZSC1
  *         @arg @ref GTZC1_TZSC1_SEC_PERIPH
  * @endif
  * @if GTZC_TZSC2
  *         @arg @ref GTZC2_TZSC1_SEC_PERIPH
  * @endif
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP3_MDF1
  *         @arg @ref LL_GTZC1_GRP3_CORDIC
  *         @arg @ref LL_GTZC1_GRP3_FMAC
  *         @arg @ref LL_GTZC1_GRP3_CRC
  *         @arg @ref LL_GTZC1_GRP3_TSC
  * @if DMA2D
  *         @arg @ref LL_GTZC1_GRP3_DMA2D
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_ICACHE_REG
  *         @arg @ref LL_GTZC1_GRP3_DCACHE1_REG
  *         @arg @ref LL_GTZC1_GRP3_ADC12
  *         @arg @ref LL_GTZC1_GRP3_DCMI
  * @if USB_OTG_GLOBAL_BASE
  *         @arg @ref LL_GTZC1_GRP3_OTG
  * @endif
  * @if AES
  *         @arg @ref LL_GTZC1_GRP3_AES
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_HASH
  *         @arg @ref LL_GTZC1_GRP3_RNG
  * @if PKA
  *         @arg @ref LL_GTZC1_GRP3_PKA
  * @endif
  * @if SAES
  *         @arg @ref LL_GTZC1_GRP3_SAES
  * @endif
  * @if OCTOSPIM
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPIM
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_SDMMC1
  * @if SDMMC2
  *         @arg @ref LL_GTZC1_GRP3_SDMMC2
  * @endif
  * @if FMC_BASE
  *         @arg @ref LL_GTZC1_GRP3_FSMC_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI1_REG
  * @if OCTOSPI2
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI2_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_RAMCFG
  * @if GPU2D
  *         @arg @ref LL_GTZC1_GRP3_GPU2D
  * @endif
  * @if GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU_REG
  * @endif
  * @if HSPI1
  *         @arg @ref LL_GTZC1_GRP3_HSPI1_REG
  * @endif
  * @if DCACHE2
  *         @arg @ref LL_GTZC1_GRP3_DCACHE2_REG
  * @endif
  * @param  attr This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_ATTR_NPRIV
  *         @arg @ref LL_GTZC_ATTR_PRIV
  */
__STATIC_INLINE void LL_GTZC_TZSC_SetPeriphGrp3PrivilegeAttr(GTZC_TZSC_SecPeriph_TypeDef *p_tzsc,
                                                             uint32_t periph,
                                                             uint32_t attr)
{
  ATOMIC_MODIFY_REG(p_tzsc->PRIVCFGR3, periph, (attr * periph));
}

/**
  * @brief  Get PRIVCFGR3 peripheral privilege attribute.
  * @rmtoll
  *  PRIVCFGR3           xxxPRIV         LL_GTZC_TZSC_GetPrivilegeAttribute_PRIVCFGR3
  * @param  p_tzsc TZSC Instance
  * @if GTZC_TZSC1
  *         @arg @ref GTZC1_TZSC1_SEC_PERIPH
  * @endif
  * @if GTZC_TZSC2
  *         @arg @ref GTZC2_TZSC1_SEC_PERIPH
  * @endif
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP3_MDF1
  *         @arg @ref LL_GTZC1_GRP3_CORDIC
  *         @arg @ref LL_GTZC1_GRP3_FMAC
  *         @arg @ref LL_GTZC1_GRP3_CRC
  *         @arg @ref LL_GTZC1_GRP3_TSC
  * @if DMA2D
  *         @arg @ref LL_GTZC1_GRP3_DMA2D
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_ICACHE_REG
  *         @arg @ref LL_GTZC1_GRP3_DCACHE1_REG
  *         @arg @ref LL_GTZC1_GRP3_ADC12
  *         @arg @ref LL_GTZC1_GRP3_DCMI
  * @if USB_OTG_GLOBAL_BASE
  *         @arg @ref LL_GTZC1_GRP3_OTG
  * @endif
  * @if AES
  *         @arg @ref LL_GTZC1_GRP3_AES
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_HASH
  *         @arg @ref LL_GTZC1_GRP3_RNG
  * @if PKA
  *         @arg @ref LL_GTZC1_GRP3_PKA
  * @endif
  * @if SAES
  *         @arg @ref LL_GTZC1_GRP3_SAES
  * @endif
  * @if OCTOSPIM
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPIM
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_SDMMC1
  * @if SDMMC2
  *         @arg @ref LL_GTZC1_GRP3_SDMMC2
  * @endif
  * @if FMC_BASE
  *         @arg @ref LL_GTZC1_GRP3_FSMC_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI1_REG
  * @if OCTOSPI2
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI2_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_RAMCFG
  * @if GPU2D
  *         @arg @ref LL_GTZC1_GRP3_GPU2D
  * @endif
  * @if GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU_REG
  * @endif
  * @if HSPI1
  *         @arg @ref LL_GTZC1_GRP3_HSPI1_REG
  * @endif
  * @if DCACHE2
  *         @arg @ref LL_GTZC1_GRP3_DCACHE2_REG
  * @endif
  * @retval State of bit (0 Non-privilege / 1 Privilege)
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_GetPeriphGrp3PrivilegeAttr(const GTZC_TZSC_SecPeriph_TypeDef *p_tzsc,
                                                                 uint32_t periph)
{
  return (READ_BIT(p_tzsc->PRIVCFGR3, periph));
}

/**
  * @}
  */

/** @defgroup GTZC_TZSC_MPCWM_LL_EF_Management MPCWM Management
  * @{
  */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Enable subregion of watermark memory.
  * @rmtoll
  *  MPCWMxzCFGR           SREN         LL_GTZC_TZSC_MPCWM_EnableSubRegion
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_EnableSubRegion(GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                        uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t)p_watermark;
  SET_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_SREN);
}

/**
  * @brief  Disable subregion of watermark memory.
  * @rmtoll
  *  MPCWMxzCFGR           SREN         LL_GTZC_TZSC_MPCWM_DisableSubRegion
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_DisableSubRegion(GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                         uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t)p_watermark;
  CLEAR_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_SREN);
}

/**
  * @brief  Check if subregion of watermark is enabled.
  * @rmtoll
  *  MPCWMxzCFGR           SREN         LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  *
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion(const GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                               uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t)p_watermark;
  return ((READ_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_SREN) ==
           GTZC_TZSC_MPCWM_CFGR_SREN) ? 1UL : 0UL);
}

/**
  * @brief  Lock of subregion of watermark memory.
  * @rmtoll
  *  MPCWMxzCFGR           SRLOCK         LL_GTZC_TZSC_MPCWM_LockSubRegion
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_LockSubRegion(GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                      uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t)p_watermark;
  SET_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_SRLOCK);
}

/**
  * @brief  Check if subregion of watermark is locked.
  * @rmtoll
  *  MPCWMxzCFGR           SRLOCK         LL_GTZC_TZSC_MPCWM_IsLockedSubRegion
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_MPCWM_IsLockedSubRegion(const GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                              uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t)p_watermark;
  return ((READ_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_SRLOCK) ==
           GTZC_TZSC_MPCWM_CFGR_SRLOCK) ? 1UL : 0UL);
}

/**
  * @brief  Set watermark memory subregion attribute.
  * @rmtoll
  *  MPCWMxzCFGR           SEC         LL_GTZC_TZSC_MPCWM_SetSubRegionAttr
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @param sec_attr
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_ATTR_SEC
  *         @arg @ref LL_GTZC_ATTR_NSEC
  * @param  priv_attr
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_ATTR_PRIV
  *         @arg @ref LL_GTZC_ATTR_NPRIV
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_SetSubRegionAttr(GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                         uint32_t subregion,
                                                         uint32_t sec_attr,
                                                         uint32_t priv_attr)
{
  uint32_t reg_addr = (uint32_t)p_watermark;
  MODIFY_REG(*(__IO uint32_t *)(reg_addr + (8U * subregion)), (GTZC_TZSC_MPCWM_CFGR_SEC | GTZC_TZSC_MPCWM_CFGR_PRIV),
             ((sec_attr << GTZC_TZSC_MPCWM_CFGR_SEC_Pos) | (priv_attr << GTZC_TZSC_MPCWM_CFGR_PRIV_Pos)));
}

/**
  * @brief  Set secure attribute of watermark memory subregion.
  * @rmtoll
  *  MPCWMxzCFGR           SEC         LL_GTZC_TZSC_MPCWM_SetSubRegionSecure
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @param  sec_attr
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_ATTR_SEC
  *         @arg @ref LL_GTZC_ATTR_NSEC
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_SetSubRegionSecure(GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                           uint32_t subregion,
                                                           uint32_t sec_attr)
{
  uint32_t reg_addr = (uint32_t)p_watermark;
  MODIFY_REG(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_SEC,
             (GTZC_TZSC_MPCWM_CFGR_SEC * sec_attr));
}

/**
  * @brief  Get secure attribute of watermark memory subregion.
  * @rmtoll
  *  MPCWMxzCFGR           SEC         LL_GTZC_TZSC_MPCWM_GetSubRegionSecure
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GTZC_ATTR_SEC
  *         @arg @ref LL_GTZC_ATTR_NSEC
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_MPCWM_GetSubRegionSecure(const GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                               uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t)p_watermark;
  return (READ_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_SEC));
}

/**
  * @brief  Set privilege attribute of watermark memory subregion.
  * @rmtoll
  *  MPCWMxzCFGR           PRIV         LL_GTZC_TZSC_MPCWM_SetSubRegionPrivilege
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @param  priv_attr
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_ATTR_PRIV
  *         @arg @ref LL_GTZC_ATTR_NPRIV
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_SetSubRegionPrivilege(GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                              uint32_t subregion,
                                                              uint32_t priv_attr)
{
  uint32_t reg_addr = (uint32_t)p_watermark;
  MODIFY_REG(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_PRIV,
             (GTZC_TZSC_MPCWM_CFGR_PRIV * priv_attr));
}

/**
  * @brief  Get privilege attribute of watermark memory subregion.
  * @rmtoll
  *  MPCWMxzCFGR           PRIV         LL_GTZC_TZSC_MPCWM_GetSubRegionPrivilege
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GTZC_ATTR_PRIV
  *         @arg @ref LL_GTZC_ATTR_NPRIV
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_MPCWM_GetSubRegionPrivilege(const GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                                  uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t)p_watermark;
  return (READ_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_PRIV));
}

/**
  * @brief  Set area configuration of watermark memory subregion.
  * @rmtoll
  *  MPCWMxAR           SUBx_START/SUBx_LENGTH        LL_GTZC_TZSC_MPCWM_ConfigSubRegionArea
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @param start  : address in byte divided by granularity
  * @param length : length in byte divided by granularity
  *
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_ConfigSubRegionArea(GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                            uint32_t subregion,
                                                            uint32_t start,
                                                            uint32_t length)
{
  uint32_t reg_addr = (uint32_t) &(p_watermark->MPCWMxAR);
  MODIFY_REG(*(__IO uint32_t *)(reg_addr + (8U * subregion)),
             (GTZC_TZSC_MPCWMR_SUBZ_START | GTZC_TZSC_MPCWMR_SUBZ_LENGTH), (start | (length << 16U)));
}

/**
  * @brief  Set start of subregion of watermark memory.
  * @rmtoll
  *  MPCWMxAR           SUBx_START       LL_GTZC_TZSC_MPCWM_SetSubRegionStart
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @param start  : address in byte divided by granularity
  *
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_SetSubRegionStart(GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                          uint32_t subregion,
                                                          uint32_t start)
{
  uint32_t reg_addr = (uint32_t) &(p_watermark->MPCWMxAR);
  MODIFY_REG(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWMR_SUBZ_START, start);
}

/**
  * @brief  Get start of subregion of watermark memory.
  * @rmtoll
  *  MPCWMxAR           SUBx_START          LL_GTZC_TZSC_MPCWM_GetSubRegionStart
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @retval Returned value
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_MPCWM_GetSubRegionStart(const GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                              uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t) &(p_watermark->MPCWMxAR);
  return (READ_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWMR_SUBZ_START));
}

/**
  * @brief  Set length of subregion of watermark memory.
  * @rmtoll
  *  MPCWMxAR           SUBx_LENGTH       LL_GTZC_TZSC_MPCWM_SetSubRegionLength
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @param length  : length in byte divided by granularity
  *
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_SetSubRegionLength(GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                           uint32_t subregion,
                                                           uint32_t length)
{
  uint32_t reg_addr = (uint32_t) &(p_watermark->MPCWMxAR);
  MODIFY_REG(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWMR_SUBZ_LENGTH, (length << 16U));
}

/**
  * @brief  Get length of subregion of watermark memory.
  * @rmtoll
  *  MPCWMxAR           SUBx_LENGTH          LL_GTZC_TZSC_MPCWM_GetSubRegionLength
  * @param  p_watermark WATERMARK Instance
  * @if GTZC1_TZSC1_MPCWM1
  *         @arg @ref GTZC1_TZSC1_MPCWM1
  * @endif
  * @if FMC_BASE
  *         @arg @ref GTZC1_TZSC1_MPCWM2
  *         @arg @ref GTZC1_TZSC1_MPCWM3
  * @endif
  * @if GTZC1_TZSC1_MPCWM4
  *         @arg @ref GTZC1_TZSC1_MPCWM4
  * @endif
  * @if OCTOSPI2
  *         @arg @ref GTZC1_TZSC1_MPCWM5
  * @endif
  * @if HSPI1
  *         @arg @ref GTZC1_TZSC1_MPCWM6
  * @endif
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @retval Returned value
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_MPCWM_GetSubRegionLength(const GTZC_TZSC_WaterMark_TypeDef *p_watermark,
                                                               uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t) &(p_watermark->MPCWMxAR);
  return (READ_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWMR_SUBZ_LENGTH));
}
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @}
  */

/** @defgroup GTZC_LL_EF_MPCBB_Management MPCBB Management
  * @{
  */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Set clock security state of block based memory.
  * @rmtoll
  *  CR           INVSECSTATE        LL_GTZC_MPCBB_SetClockSecurityState
  * @param  p_blockbased BLOCKBASED Instance
  *         This parameter can be one of the following values :
  * @if GTZC1_MPCBB1
  *         @arg @ref GTZC1_MPCBB1
  * @endif
  * @if GTZC1_MPCBB2
  *         @arg @ref GTZC1_MPCBB2
  * @endif
  * @if SRAM3_BASE
  *         @arg @ref GTZC1_MPCBB3
  * @endif
  * @if GTZC2_MPCBB4
  *         @arg @ref GTZC2_MPCBB4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref GTZC1_MPCBB5
  * @endif
  * @if SRAM6_BASE
  *         @arg @ref GTZC1_MPCBB6
  * @endif
  * @param  clk_sec_state
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_MPCBB_CLK_SEC_NOT_INVERTED
  *         @arg @ref LL_GTZC_MPCBB_CLK_SEC_INVERTED
  */
__STATIC_INLINE void LL_GTZC_MPCBB_SetClockSecurityState(GTZC_BlockBased_TypeDef *p_blockbased, uint32_t clk_sec_state)
{
  MODIFY_REG(p_blockbased->CR, GTZC_MPCBB_CR_INVSECSTATE_Msk, (GTZC_MPCBB_CR_INVSECSTATE_Msk * clk_sec_state));
}

/**
  * @brief  Get clock security state of block based memory.
  * @rmtoll
  *  CR           INVSECSTATE         LL_GTZC_MPCBB_GetClockSecurityState
  * @param  p_blockbased BLOCKBASED Instance
  *         This parameter can be one of the following values :
  * @if GTZC1_MPCBB1
  *         @arg @ref GTZC1_MPCBB1
  * @endif
  * @if GTZC1_MPCBB2
  *         @arg @ref GTZC1_MPCBB2
  * @endif
  * @if SRAM3_BASE
  *         @arg @ref GTZC1_MPCBB3
  * @endif
  * @if GTZC2_MPCBB4
  *         @arg @ref GTZC2_MPCBB4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref GTZC1_MPCBB5
  * @endif
  * @if SRAM6_BASE
  *         @arg @ref GTZC1_MPCBB6
  * @endif
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GTZC_MPCBB_CLK_SEC_NOT_INVERTED
  *         @arg @ref LL_GTZC_MPCBB_CLK_SEC_INVERTED
  */
__STATIC_INLINE uint32_t LL_GTZC_MPCBB_GetClockSecurityState(const GTZC_BlockBased_TypeDef *p_blockbased)
{
  return (READ_BIT(p_blockbased->CR, GTZC_MPCBB_CR_INVSECSTATE_Msk) >> GTZC_MPCBB_CR_INVSECSTATE_Pos);
}

/**
  * @brief  Set secure access state of block based memory.
  * @rmtoll
  *  CR            SRWILADIS         LL_GTZC_MPCBB_SetSecureAccessState
  * @param  p_blockbased BLOCKBASED Instance
  *         This parameter can be one of the following values :
  * @if GTZC1_MPCBB1
  *         @arg @ref GTZC1_MPCBB1
  * @endif
  * @if GTZC1_MPCBB2
  *         @arg @ref GTZC1_MPCBB2
  * @endif
  * @if SRAM3_BASE
  *         @arg @ref GTZC1_MPCBB3
  * @endif
  * @if GTZC2_MPCBB4
  *         @arg @ref GTZC2_MPCBB4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref GTZC1_MPCBB5
  * @endif
  * @if SRAM6_BASE
  *         @arg @ref GTZC1_MPCBB6
  * @endif
  * @param  sec_access_state
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_MPCBB_SEC_ACCESS_ALLOWED
  *         @arg @ref LL_GTZC_MPCBB_SEC_ACCESS_NOT_ALLOWED
  */
__STATIC_INLINE void LL_GTZC_MPCBB_SetSecureAccessState(GTZC_BlockBased_TypeDef *p_blockbased,
                                                        uint32_t sec_access_state)
{
  MODIFY_REG(p_blockbased->CR, GTZC_MPCBB_CR_SRWILADIS_Msk, (GTZC_MPCBB_CR_SRWILADIS_Msk * sec_access_state));
}

/**
  * @brief  Get secure access state of block based memory.
  * @rmtoll
  *  CR           SRWILADIS         LL_GTZC_MPCBB_GetSecureAccessState
  * @param  p_blockbased BLOCKBASED Instance
  *         This parameter can be one of the following values :
  * @if GTZC1_MPCBB1
  *         @arg @ref GTZC1_MPCBB1
  * @endif
  * @if GTZC1_MPCBB2
  *         @arg @ref GTZC1_MPCBB2
  * @endif
  * @if SRAM3_BASE
  *         @arg @ref GTZC1_MPCBB3
  * @endif
  * @if GTZC2_MPCBB4
  *         @arg @ref GTZC2_MPCBB4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref GTZC1_MPCBB5
  * @endif
  * @if SRAM6_BASE
  *         @arg @ref GTZC1_MPCBB6
  * @endif
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GTZC_MPCBB_SEC_ACCESS_ALLOWED
  *         @arg @ref LL_GTZC_MPCBB_SEC_ACCESS_NOT_ALLOWED
  */
__STATIC_INLINE uint32_t LL_GTZC_MPCBB_GetSecureAccessState(const GTZC_BlockBased_TypeDef *p_blockbased)
{
  return (READ_BIT(p_blockbased->CR, GTZC_MPCBB_CR_SRWILADIS_Msk) >> GTZC_MPCBB_CR_SRWILADIS_Pos);
}

/**
  * @brief  Set secure attribute of blk memory.
  * @rmtoll
  *  SECCFGRx (x= 0 to 51)     SECx (x= 0 to 31)     LL_GTZC_MPCBB_SetBlkSecure
  * @param  p_blockbased BLOCKBASED Instance
  *         This parameter can be one of the following values :
  * @if GTZC1_MPCBB1
  *         @arg @ref GTZC1_MPCBB1
  * @endif
  * @if GTZC1_MPCBB2
  *         @arg @ref GTZC1_MPCBB2
  * @endif
  * @if SRAM3_BASE
  *         @arg @ref GTZC1_MPCBB3
  * @endif
  * @if GTZC2_MPCBB4
  *         @arg @ref GTZC2_MPCBB4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref GTZC1_MPCBB5
  * @endif
  * @if SRAM6_BASE
  *         @arg @ref GTZC1_MPCBB6
  * @endif
  * @param  super_blk
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_0
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_1
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_2
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_3
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_4
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_5
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_6
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_7
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_8
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_9
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_10
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_11
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_12
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_13
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_14
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_15
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_16
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_17
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_18
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_19
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_20
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_21
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_22
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_23
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_24
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_25
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_26
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_27
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_28
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_29
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_30
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_31
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_32
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_33
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_34
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_35
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_36
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_37
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_38
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_39
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_40
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_41
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_42
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_43
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_44
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_45
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_46
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_47
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_48
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_49
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_50
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_51
  * @endif
  * @param  blk
  *         This parameter can be a combination of the following values :
  *         @arg @ref LL_GTZC_MPCBB_BLK_0
  *         @arg @ref LL_GTZC_MPCBB_BLK_1
  *         @arg @ref LL_GTZC_MPCBB_BLK_2
  *         @arg @ref LL_GTZC_MPCBB_BLK_3
  *         @arg @ref LL_GTZC_MPCBB_BLK_4
  *         @arg @ref LL_GTZC_MPCBB_BLK_5
  *         @arg @ref LL_GTZC_MPCBB_BLK_6
  *         @arg @ref LL_GTZC_MPCBB_BLK_7
  *         @arg @ref LL_GTZC_MPCBB_BLK_8
  *         @arg @ref LL_GTZC_MPCBB_BLK_9
  *         @arg @ref LL_GTZC_MPCBB_BLK_10
  *         @arg @ref LL_GTZC_MPCBB_BLK_11
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_BLK_12
  *         @arg @ref LL_GTZC_MPCBB_BLK_13
  *         @arg @ref LL_GTZC_MPCBB_BLK_14
  *         @arg @ref LL_GTZC_MPCBB_BLK_15
  *         @arg @ref LL_GTZC_MPCBB_BLK_16
  *         @arg @ref LL_GTZC_MPCBB_BLK_17
  *         @arg @ref LL_GTZC_MPCBB_BLK_18
  *         @arg @ref LL_GTZC_MPCBB_BLK_19
  *         @arg @ref LL_GTZC_MPCBB_BLK_20
  *         @arg @ref LL_GTZC_MPCBB_BLK_21
  *         @arg @ref LL_GTZC_MPCBB_BLK_22
  *         @arg @ref LL_GTZC_MPCBB_BLK_23
  *         @arg @ref LL_GTZC_MPCBB_BLK_24
  *         @arg @ref LL_GTZC_MPCBB_BLK_25
  *         @arg @ref LL_GTZC_MPCBB_BLK_26
  *         @arg @ref LL_GTZC_MPCBB_BLK_27
  *         @arg @ref LL_GTZC_MPCBB_BLK_28
  *         @arg @ref LL_GTZC_MPCBB_BLK_29
  *         @arg @ref LL_GTZC_MPCBB_BLK_30
  *         @arg @ref LL_GTZC_MPCBB_BLK_31
  * @endif
  * @param sec_attr
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_ATTR_SEC
  *         @arg @ref LL_GTZC_ATTR_NSEC
  */
__STATIC_INLINE void LL_GTZC_MPCBB_SetBlkSecure(GTZC_BlockBased_TypeDef *p_blockbased,
                                                uint32_t super_blk,
                                                uint32_t blk,
                                                uint32_t sec_attr)
{
  MODIFY_REG(p_blockbased->SECCFGR[super_blk], blk, (blk * sec_attr));
}
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Get secure attribute of super-blk block based memory.
  * @rmtoll
  *  SECCFGRx (x= 0 to 51)     SECx (x= 0 to 31)     LL_GTZC_MPCBB_GetSuperBlkSecure
  * @param  p_blockbased BLOCKBASED Instance
  *         This parameter can be one of the following values :
  * @if GTZC1_MPCBB1
  *         @arg @ref GTZC1_MPCBB1
  * @endif
  * @if GTZC1_MPCBB2
  *         @arg @ref GTZC1_MPCBB2
  * @endif
  * @if SRAM3_BASE
  *         @arg @ref GTZC1_MPCBB3
  * @endif
  * @if GTZC2_MPCBB4
  *         @arg @ref GTZC2_MPCBB4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref GTZC1_MPCBB5
  * @endif
  * @if SRAM6_BASE
  *         @arg @ref GTZC1_MPCBB6
  * @endif
  * @param  super_blk
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_0
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_1
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_2
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_3
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_4
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_5
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_6
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_7
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_8
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_9
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_10
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_11
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_12
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_13
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_14
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_15
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_16
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_17
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_18
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_19
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_20
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_21
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_22
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_23
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_24
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_25
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_26
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_27
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_28
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_29
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_30
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_31
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_32
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_33
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_34
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_35
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_36
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_37
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_38
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_39
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_40
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_41
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_42
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_43
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_44
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_45
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_46
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_47
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_48
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_49
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_50
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_51
  * @endif
  * @retval The return value can be a 0x00000000U or combination of the following values :
  *         @arg @ref LL_GTZC_MPCBB_BLK_0
  *         @arg @ref LL_GTZC_MPCBB_BLK_1
  *         @arg @ref LL_GTZC_MPCBB_BLK_2
  *         @arg @ref LL_GTZC_MPCBB_BLK_3
  *         @arg @ref LL_GTZC_MPCBB_BLK_4
  *         @arg @ref LL_GTZC_MPCBB_BLK_5
  *         @arg @ref LL_GTZC_MPCBB_BLK_6
  *         @arg @ref LL_GTZC_MPCBB_BLK_7
  *         @arg @ref LL_GTZC_MPCBB_BLK_8
  *         @arg @ref LL_GTZC_MPCBB_BLK_9
  *         @arg @ref LL_GTZC_MPCBB_BLK_10
  *         @arg @ref LL_GTZC_MPCBB_BLK_11
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_BLK_12
  *         @arg @ref LL_GTZC_MPCBB_BLK_13
  *         @arg @ref LL_GTZC_MPCBB_BLK_14
  *         @arg @ref LL_GTZC_MPCBB_BLK_15
  *         @arg @ref LL_GTZC_MPCBB_BLK_16
  *         @arg @ref LL_GTZC_MPCBB_BLK_17
  *         @arg @ref LL_GTZC_MPCBB_BLK_18
  *         @arg @ref LL_GTZC_MPCBB_BLK_19
  *         @arg @ref LL_GTZC_MPCBB_BLK_20
  *         @arg @ref LL_GTZC_MPCBB_BLK_21
  *         @arg @ref LL_GTZC_MPCBB_BLK_22
  *         @arg @ref LL_GTZC_MPCBB_BLK_23
  *         @arg @ref LL_GTZC_MPCBB_BLK_24
  *         @arg @ref LL_GTZC_MPCBB_BLK_25
  *         @arg @ref LL_GTZC_MPCBB_BLK_26
  *         @arg @ref LL_GTZC_MPCBB_BLK_27
  *         @arg @ref LL_GTZC_MPCBB_BLK_28
  *         @arg @ref LL_GTZC_MPCBB_BLK_29
  *         @arg @ref LL_GTZC_MPCBB_BLK_30
  *         @arg @ref LL_GTZC_MPCBB_BLK_31
  * @endif
  */
__STATIC_INLINE uint32_t LL_GTZC_MPCBB_GetSuperBlkSecure(const GTZC_BlockBased_TypeDef *p_blockbased,
                                                         uint32_t super_blk)
{
  return (READ_REG(p_blockbased->SECCFGR[super_blk]));
}

/**
  * @brief  Set privilege attribute of super-blk block based memory.
  * @rmtoll
  *  PRIVCFGRx (x= 0 to 31)     PRIVx (x= 0 to 31)     LL_GTZC_MPCBB_SetBlkPrivilege
  * @param  p_blockbased BLOCKBASED Instance
  *         This parameter can be one of the following values :
  * @if GTZC1_MPCBB1
  *         @arg @ref GTZC1_MPCBB1
  * @endif
  * @if GTZC1_MPCBB2
  *         @arg @ref GTZC1_MPCBB2
  * @endif
  * @if SRAM3_BASE
  *         @arg @ref GTZC1_MPCBB3
  * @endif
  * @if GTZC2_MPCBB4
  *         @arg @ref GTZC2_MPCBB4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref GTZC1_MPCBB5
  * @endif
  * @if SRAM6_BASE
  *         @arg @ref GTZC1_MPCBB6
  * @endif
  * @param  super_blk
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_0
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_1
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_2
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_3
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_4
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_5
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_6
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_7
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_8
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_9
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_10
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_11
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_12
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_13
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_14
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_15
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_16
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_17
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_18
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_19
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_20
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_21
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_22
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_23
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_24
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_25
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_26
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_27
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_28
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_29
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_30
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_31
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_32
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_33
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_34
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_35
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_36
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_37
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_38
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_39
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_40
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_41
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_42
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_43
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_44
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_45
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_46
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_47
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_48
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_49
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_50
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_51
  * @endif
  * @param  blk
  *         This parameter can be a combination of the following values :
  *         @arg @ref LL_GTZC_MPCBB_BLK_0
  *         @arg @ref LL_GTZC_MPCBB_BLK_1
  *         @arg @ref LL_GTZC_MPCBB_BLK_2
  *         @arg @ref LL_GTZC_MPCBB_BLK_3
  *         @arg @ref LL_GTZC_MPCBB_BLK_4
  *         @arg @ref LL_GTZC_MPCBB_BLK_5
  *         @arg @ref LL_GTZC_MPCBB_BLK_6
  *         @arg @ref LL_GTZC_MPCBB_BLK_7
  *         @arg @ref LL_GTZC_MPCBB_BLK_8
  *         @arg @ref LL_GTZC_MPCBB_BLK_9
  *         @arg @ref LL_GTZC_MPCBB_BLK_10
  *         @arg @ref LL_GTZC_MPCBB_BLK_11
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_BLK_12
  *         @arg @ref LL_GTZC_MPCBB_BLK_13
  *         @arg @ref LL_GTZC_MPCBB_BLK_14
  *         @arg @ref LL_GTZC_MPCBB_BLK_15
  *         @arg @ref LL_GTZC_MPCBB_BLK_16
  *         @arg @ref LL_GTZC_MPCBB_BLK_17
  *         @arg @ref LL_GTZC_MPCBB_BLK_18
  *         @arg @ref LL_GTZC_MPCBB_BLK_19
  *         @arg @ref LL_GTZC_MPCBB_BLK_20
  *         @arg @ref LL_GTZC_MPCBB_BLK_21
  *         @arg @ref LL_GTZC_MPCBB_BLK_22
  *         @arg @ref LL_GTZC_MPCBB_BLK_23
  *         @arg @ref LL_GTZC_MPCBB_BLK_24
  *         @arg @ref LL_GTZC_MPCBB_BLK_25
  *         @arg @ref LL_GTZC_MPCBB_BLK_26
  *         @arg @ref LL_GTZC_MPCBB_BLK_27
  *         @arg @ref LL_GTZC_MPCBB_BLK_28
  *         @arg @ref LL_GTZC_MPCBB_BLK_29
  *         @arg @ref LL_GTZC_MPCBB_BLK_30
  *         @arg @ref LL_GTZC_MPCBB_BLK_31
  * @endif
  * @param  priv_attr
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_ATTR_PRIV
  *         @arg @ref LL_GTZC_ATTR_NPRIV
  */
__STATIC_INLINE void LL_GTZC_MPCBB_SetBlkPrivilege(GTZC_BlockBased_TypeDef *p_blockbased,
                                                   uint32_t super_blk,
                                                   uint32_t blk,
                                                   uint32_t priv_attr)
{
  MODIFY_REG(p_blockbased->PRIVCFGR[super_blk], blk, (blk * priv_attr));
}

/**
  * @brief  Get privilege attribute of super-blk block based memory.
  * @rmtoll
  *  PRIVCFGRx (x = 0 to 51)     PRIVx (x = 0 to 31)     LL_GTZC_MPCBB_GetSuperBlkPrivilege
  * @param  p_blockbased BLOCKBASED Instance
  *         This parameter can be one of the following values :
  * @if GTZC1_MPCBB1
  *         @arg @ref GTZC1_MPCBB1
  * @endif
  * @if GTZC1_MPCBB2
  *         @arg @ref GTZC1_MPCBB2
  * @endif
  * @if SRAM3_BASE
  *         @arg @ref GTZC1_MPCBB3
  * @endif
  * @if GTZC2_MPCBB4
  *         @arg @ref GTZC2_MPCBB4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref GTZC1_MPCBB5
  * @endif
  * @if SRAM6_BASE
  *         @arg @ref GTZC1_MPCBB6
  * @endif
  * @param  super_blk
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_0
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_1
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_2
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_3
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_4
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_5
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_6
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_7
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_8
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_9
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_10
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_11
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_12
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_13
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_14
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_15
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_16
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_17
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_18
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_19
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_20
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_21
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_22
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_23
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_24
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_25
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_26
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_27
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_28
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_29
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_30
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_31
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_32
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_33
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_34
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_35
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_36
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_37
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_38
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_39
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_40
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_41
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_42
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_43
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_44
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_45
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_46
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_47
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_48
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_49
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_50
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_ATTR_51
  * @endif
  * @retval The return value can be a 0x00000000U or combination of the following values :
  *         @arg @ref LL_GTZC_MPCBB_BLK_0
  *         @arg @ref LL_GTZC_MPCBB_BLK_1
  *         @arg @ref LL_GTZC_MPCBB_BLK_2
  *         @arg @ref LL_GTZC_MPCBB_BLK_3
  *         @arg @ref LL_GTZC_MPCBB_BLK_4
  *         @arg @ref LL_GTZC_MPCBB_BLK_5
  *         @arg @ref LL_GTZC_MPCBB_BLK_6
  *         @arg @ref LL_GTZC_MPCBB_BLK_7
  *         @arg @ref LL_GTZC_MPCBB_BLK_8
  *         @arg @ref LL_GTZC_MPCBB_BLK_9
  *         @arg @ref LL_GTZC_MPCBB_BLK_10
  *         @arg @ref LL_GTZC_MPCBB_BLK_11
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_BLK_12
  *         @arg @ref LL_GTZC_MPCBB_BLK_13
  *         @arg @ref LL_GTZC_MPCBB_BLK_14
  *         @arg @ref LL_GTZC_MPCBB_BLK_15
  *         @arg @ref LL_GTZC_MPCBB_BLK_16
  *         @arg @ref LL_GTZC_MPCBB_BLK_17
  *         @arg @ref LL_GTZC_MPCBB_BLK_18
  *         @arg @ref LL_GTZC_MPCBB_BLK_19
  *         @arg @ref LL_GTZC_MPCBB_BLK_20
  *         @arg @ref LL_GTZC_MPCBB_BLK_21
  *         @arg @ref LL_GTZC_MPCBB_BLK_22
  *         @arg @ref LL_GTZC_MPCBB_BLK_23
  *         @arg @ref LL_GTZC_MPCBB_BLK_24
  *         @arg @ref LL_GTZC_MPCBB_BLK_25
  *         @arg @ref LL_GTZC_MPCBB_BLK_26
  *         @arg @ref LL_GTZC_MPCBB_BLK_27
  *         @arg @ref LL_GTZC_MPCBB_BLK_28
  *         @arg @ref LL_GTZC_MPCBB_BLK_29
  *         @arg @ref LL_GTZC_MPCBB_BLK_30
  *         @arg @ref LL_GTZC_MPCBB_BLK_31
  * @endif
  */
__STATIC_INLINE uint32_t LL_GTZC_MPCBB_GetSuperBlkPrivilege(const GTZC_BlockBased_TypeDef *p_blockbased,
                                                            uint32_t super_blk)
{
  return (READ_REG(p_blockbased->PRIVCFGR[super_blk]));
}

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Lock configuration of block based memory.
  * @rmtoll
  *  CR           GLOCK         LL_GTZC_MPCBB_LockConfig
  * @param  p_blockbased BLOCKBASED Instance
  *         This parameter can be one of the following values :
  * @if GTZC1_MPCBB1
  *         @arg @ref GTZC1_MPCBB1
  * @endif
  * @if GTZC1_MPCBB2
  *         @arg @ref GTZC1_MPCBB2
  * @endif
  * @if SRAM3_BASE
  *         @arg @ref GTZC1_MPCBB3
  * @endif
  * @if GTZC2_MPCBB4
  *         @arg @ref GTZC2_MPCBB4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref GTZC1_MPCBB5
  * @endif
  * @if SRAM6_BASE
  *         @arg @ref GTZC1_MPCBB6
  * @endif
  */
__STATIC_INLINE void LL_GTZC_MPCBB_LockConfig(GTZC_BlockBased_TypeDef *p_blockbased)
{
  SET_BIT(p_blockbased->CR, GTZC_MPCBB_CR_GLOCK_Msk);
}

/**
  * @brief  Check if block based memory configuration is locked.
  * @rmtoll
  *  CR           GLOCK         LL_GTZC_MPCBB_IsLockedConfig
  * @param  p_blockbased BLOCKBASED Instance
  *         This parameter can be one of the following values :
  * @if GTZC1_MPCBB1
  *         @arg @ref GTZC1_MPCBB1
  * @endif
  * @if GTZC1_MPCBB2
  *         @arg @ref GTZC1_MPCBB2
  * @endif
  * @if SRAM3_BASE
  *         @arg @ref GTZC1_MPCBB3
  * @endif
  * @if GTZC2_MPCBB4
  *         @arg @ref GTZC2_MPCBB4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref GTZC1_MPCBB5
  * @endif
  * @if SRAM6_BASE
  *         @arg @ref GTZC1_MPCBB6
  * @endif
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GTZC_MPCBB_IsLockedConfig(const GTZC_BlockBased_TypeDef *p_blockbased)
{
  return ((READ_BIT(p_blockbased->CR, GTZC_MPCBB_CR_GLOCK_Msk) == GTZC_MPCBB_CR_GLOCK_Msk) ? 1UL : 0UL);
}

/**
  * @brief  Lock of super blk 0 to 31 of block based memory.
  * @rmtoll
  *  CFGLOCKR1           SPLCKx (x = 0 to 31)         LL_GTZC_MPCBB_LockSuperBlk_0_31
  * @param  p_blockbased BLOCKBASED Instance
  *         This parameter can be one of the following values :
  * @if GTZC1_MPCBB1
  *         @arg @ref GTZC1_MPCBB1
  * @endif
  * @if GTZC1_MPCBB2
  *         @arg @ref GTZC1_MPCBB2
  * @endif
  * @if SRAM3_BASE
  *         @arg @ref GTZC1_MPCBB3
  * @endif
  * @if GTZC2_MPCBB4
  *         @arg @ref GTZC2_MPCBB4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref GTZC1_MPCBB5
  * @endif
  * @if SRAM6_BASE
  *         @arg @ref GTZC1_MPCBB6
  * @endif
  * @param  super_blk
  *         The parameter can be a combination of the following values :
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_0
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_1
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_2
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_3
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_4
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_5
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_6
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_7
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_8
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_9
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_10
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_11
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_12
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_13
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_14
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_15
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_16
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_17
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_18
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_19
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_20
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_21
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_22
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_23
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_24
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_25
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_26
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_27
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_28
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_29
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_30
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_31
  * @endif
  */
__STATIC_INLINE void LL_GTZC_MPCBB_LockSuperBlk_0_31(GTZC_BlockBased_TypeDef *p_blockbased, uint32_t super_blk)
{
  SET_BIT(p_blockbased->CFGLOCKR1, super_blk);
}

/**
  * @brief  Get lock of super blk 0 to 31 of block based memory.
  * @rmtoll
  *  CFGLOCKR1           SPLCKx (x = 0 to 31)         LL_GTZC_MPCBB_GetLockedSuperBlk_0_31
  * @param  p_blockbased BLOCKBASED Instance
  *         This parameter can be one of the following values :
  * @if GTZC1_MPCBB1
  *         @arg @ref GTZC1_MPCBB1
  * @endif
  * @if GTZC1_MPCBB2
  *         @arg @ref GTZC1_MPCBB2
  * @endif
  * @if SRAM3_BASE
  *         @arg @ref GTZC1_MPCBB3
  * @endif
  * @if GTZC2_MPCBB4
  *         @arg @ref GTZC2_MPCBB4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref GTZC1_MPCBB5
  * @endif
  * @if SRAM6_BASE
  *         @arg @ref GTZC1_MPCBB6
  * @endif
  * @retval The return value can be a 0x00000000U or combination of the following values :
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_0
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_1
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_2
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_3
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_4
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_5
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_6
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_7
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_8
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_9
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_10
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_11
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_12
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_13
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_14
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_15
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_16
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_17
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_18
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_19
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_20
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_21
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_22
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_23
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_24
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_25
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_26
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_27
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_28
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_29
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_30
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_31
  * @endif
  */
__STATIC_INLINE uint32_t LL_GTZC_MPCBB_GetLockedSuperBlk_0_31(const GTZC_BlockBased_TypeDef *p_blockbased)
{
  return (READ_REG(p_blockbased->CFGLOCKR1));
}

#if defined (SRAM5_BASE)
/**
  * @brief  Lock of super blk 32 to 51 of block based memory.
  * @rmtoll
  *  CFGLOCKR1           SPLCKx (x = 32 to 51)         LL_GTZC_MPCBB_LockSuperBlk_32_51
  * @param  p_blockbased BLOCKBASED Instance
  *         This parameter can be one of the following values :
  * @if GTZC1_MPCBB1
  *         @arg @ref GTZC1_MPCBB1
  * @endif
  * @if GTZC1_MPCBB2
  *         @arg @ref GTZC1_MPCBB2
  * @endif
  * @if SRAM3_BASE
  *         @arg @ref GTZC1_MPCBB3
  * @endif
  * @if GTZC2_MPCBB4
  *         @arg @ref GTZC2_MPCBB4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref GTZC1_MPCBB5
  * @endif
  * @if SRAM6_BASE
  *         @arg @ref GTZC1_MPCBB6
  * @endif
  * @param  super_blk
  *         The parameter can be a combination of the following values :
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_32
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_33
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_34
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_35
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_36
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_37
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_38
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_39
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_40
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_41
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_42
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_43
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_44
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_45
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_46
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_47
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_48
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_49
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_50
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_51
  */
__STATIC_INLINE void LL_GTZC_MPCBB_LockSuperBlk_32_51(GTZC_BlockBased_TypeDef *p_blockbased, uint32_t super_blk)
{
  SET_BIT(p_blockbased->CFGLOCKR2, super_blk);
}

/**
  * @brief  Get lock of super blk 32 to 51 of block based memory.
  * @rmtoll
  *  CFGLOCKR1           SPLCKx (x = 32 to 51)         LL_GTZC_MPCBB_GetLockedSuperBlk_32_51
  * @param  p_blockbased BLOCKBASED Instance
  *         This parameter can be one of the following values :
  * @if GTZC1_MPCBB1
  *         @arg @ref GTZC1_MPCBB1
  * @endif
  * @if GTZC1_MPCBB2
  *         @arg @ref GTZC1_MPCBB2
  * @endif
  * @if SRAM3_BASE
  *         @arg @ref GTZC1_MPCBB3
  * @endif
  * @if GTZC2_MPCBB4
  *         @arg @ref GTZC2_MPCBB4
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref GTZC1_MPCBB5
  * @endif
  * @if SRAM6_BASE
  *         @arg @ref GTZC1_MPCBB6
  * @endif
  * @retval The return value can be a 0x00000000U or combination of the following values :
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_32
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_33
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_34
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_35
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_36
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_37
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_38
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_39
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_40
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_41
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_42
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_43
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_44
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_45
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_46
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_47
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_48
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_49
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_50
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLK_LOCK_51
  */
__STATIC_INLINE uint32_t LL_GTZC_MPCBB_GetLockedSuperBlk_32_51(const GTZC_BlockBased_TypeDef *p_blockbased)
{
  return (READ_REG(p_blockbased->CFGLOCKR2));
}
#endif /* SRAM5_BASE */
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @}
  */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/** @defgroup GTZC_LL_EF_TZIC_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable IER1 illegal access interrupt.
  * @rmtoll
  *  IER1           xxxIE         LL_GTZC_TZIC_EnableGrp1IT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP1_TIM2
  *         @arg @ref LL_GTZC1_GRP1_TIM3
  *         @arg @ref LL_GTZC1_GRP1_TIM4
  *         @arg @ref LL_GTZC1_GRP1_TIM5
  *         @arg @ref LL_GTZC1_GRP1_TIM6
  *         @arg @ref LL_GTZC1_GRP1_TIM7
  *         @arg @ref LL_GTZC1_GRP1_WWDG
  *         @arg @ref LL_GTZC1_GRP1_IWDG
  *         @arg @ref LL_GTZC1_GRP1_SPI2
  * @if USART2
  *         @arg @ref LL_GTZC1_GRP1_USART2
  * @endif
  *         @arg @ref LL_GTZC1_GRP1_USART3
  *         @arg @ref LL_GTZC1_GRP1_UART4
  *         @arg @ref LL_GTZC1_GRP1_UART5
  *         @arg @ref LL_GTZC1_GRP1_I2C1
  *         @arg @ref LL_GTZC1_GRP1_I2C2
  *         @arg @ref LL_GTZC1_GRP1_CRS
  *         @arg @ref LL_GTZC1_GRP1_I2C4
  *         @arg @ref LL_GTZC1_GRP1_LPTIM2
  *         @arg @ref LL_GTZC1_GRP1_FDCAN1
  * @if UCPD1
  *         @arg @ref LL_GTZC1_GRP1_UCPD1
  * @endif
  * @if USART6
  *         @arg @ref LL_GTZC1_GRP1_USART6
  * @endif
  * @if I2C5
  *         @arg @ref LL_GTZC1_GRP1_I2C5
  * @endif
  * @if I2C6
  *         @arg @ref LL_GTZC1_GRP1_I2C6
  * @endif
  *
  *         @arg @ref LL_GTZC2_GRP1_SPI3
  *         @arg @ref LL_GTZC2_GRP1_LPUART1
  *         @arg @ref LL_GTZC2_GRP1_I2C3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM1
  *         @arg @ref LL_GTZC2_GRP1_LPTIM3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM4
  *         @arg @ref LL_GTZC2_GRP1_OPAMP
  *         @arg @ref LL_GTZC2_GRP1_COMP
  *         @arg @ref LL_GTZC2_GRP1_ADC4
  *         @arg @ref LL_GTZC2_GRP1_VREFBUF
  *         @arg @ref LL_GTZC2_GRP1_DAC1
  *         @arg @ref LL_GTZC2_GRP1_ADF1
  */
__STATIC_INLINE void LL_GTZC_TZIC_EnableGrp1IT(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  ATOMIC_SET_BIT(p_tzic->IER1, periph);
}

/**
  * @brief  Disable IER1 illegal access interrupt.
  * @rmtoll
  *  IER1           xxxIE         LL_GTZC_TZIC_DisableGrp1IT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP1_TIM2
  *         @arg @ref LL_GTZC1_GRP1_TIM3
  *         @arg @ref LL_GTZC1_GRP1_TIM4
  *         @arg @ref LL_GTZC1_GRP1_TIM5
  *         @arg @ref LL_GTZC1_GRP1_TIM6
  *         @arg @ref LL_GTZC1_GRP1_TIM7
  *         @arg @ref LL_GTZC1_GRP1_WWDG
  *         @arg @ref LL_GTZC1_GRP1_IWDG
  *         @arg @ref LL_GTZC1_GRP1_SPI2
  * @if USART2
  *         @arg @ref LL_GTZC1_GRP1_USART2
  * @endif
  *         @arg @ref LL_GTZC1_GRP1_USART3
  *         @arg @ref LL_GTZC1_GRP1_UART4
  *         @arg @ref LL_GTZC1_GRP1_UART5
  *         @arg @ref LL_GTZC1_GRP1_I2C1
  *         @arg @ref LL_GTZC1_GRP1_I2C2
  *         @arg @ref LL_GTZC1_GRP1_CRS
  *         @arg @ref LL_GTZC1_GRP1_I2C4
  *         @arg @ref LL_GTZC1_GRP1_LPTIM2
  *         @arg @ref LL_GTZC1_GRP1_FDCAN1
  * @if UCPD1
  *         @arg @ref LL_GTZC1_GRP1_UCPD1
  * @endif
  * @if USART6
  *         @arg @ref LL_GTZC1_GRP1_USART6
  * @endif
  * @if I2C5
  *         @arg @ref LL_GTZC1_GRP1_I2C5
  * @endif
  * @if I2C6
  *         @arg @ref LL_GTZC1_GRP1_I2C6
  * @endif
  *
  *         @arg @ref LL_GTZC2_GRP1_SPI3
  *         @arg @ref LL_GTZC2_GRP1_LPUART1
  *         @arg @ref LL_GTZC2_GRP1_I2C3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM1
  *         @arg @ref LL_GTZC2_GRP1_LPTIM3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM4
  *         @arg @ref LL_GTZC2_GRP1_OPAMP
  *         @arg @ref LL_GTZC2_GRP1_COMP
  *         @arg @ref LL_GTZC2_GRP1_ADC4
  *         @arg @ref LL_GTZC2_GRP1_VREFBUF
  *         @arg @ref LL_GTZC2_GRP1_DAC1
  *         @arg @ref LL_GTZC2_GRP1_ADF1
  */
__STATIC_INLINE void LL_GTZC_TZIC_DisableGrp1IT(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  ATOMIC_CLEAR_BIT(p_tzic->IER1, periph);
}

/**
  * @brief  Check if IER1 illegal access interrupt is enabled.
  * @rmtoll
  *  IER1           xxxIE         LL_GTZC_TZIC_IsEnabledGrp1IT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP1_TIM2
  *         @arg @ref LL_GTZC1_GRP1_TIM3
  *         @arg @ref LL_GTZC1_GRP1_TIM4
  *         @arg @ref LL_GTZC1_GRP1_TIM5
  *         @arg @ref LL_GTZC1_GRP1_TIM6
  *         @arg @ref LL_GTZC1_GRP1_TIM7
  *         @arg @ref LL_GTZC1_GRP1_WWDG
  *         @arg @ref LL_GTZC1_GRP1_IWDG
  *         @arg @ref LL_GTZC1_GRP1_SPI2
  * @if USART2
  *         @arg @ref LL_GTZC1_GRP1_USART2
  * @endif
  *         @arg @ref LL_GTZC1_GRP1_USART3
  *         @arg @ref LL_GTZC1_GRP1_UART4
  *         @arg @ref LL_GTZC1_GRP1_UART5
  *         @arg @ref LL_GTZC1_GRP1_I2C1
  *         @arg @ref LL_GTZC1_GRP1_I2C2
  *         @arg @ref LL_GTZC1_GRP1_CRS
  *         @arg @ref LL_GTZC1_GRP1_I2C4
  *         @arg @ref LL_GTZC1_GRP1_LPTIM2
  *         @arg @ref LL_GTZC1_GRP1_FDCAN1
  * @if UCPD1
  *         @arg @ref LL_GTZC1_GRP1_UCPD1
  * @endif
  * @if USART6
  *         @arg @ref LL_GTZC1_GRP1_USART6
  * @endif
  * @if I2C5
  *         @arg @ref LL_GTZC1_GRP1_I2C5
  * @endif
  * @if I2C6
  *         @arg @ref LL_GTZC1_GRP1_I2C6
  * @endif
  *
  *         @arg @ref LL_GTZC2_GRP1_SPI3
  *         @arg @ref LL_GTZC2_GRP1_LPUART1
  *         @arg @ref LL_GTZC2_GRP1_I2C3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM1
  *         @arg @ref LL_GTZC2_GRP1_LPTIM3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM4
  *         @arg @ref LL_GTZC2_GRP1_OPAMP
  *         @arg @ref LL_GTZC2_GRP1_COMP
  *         @arg @ref LL_GTZC2_GRP1_ADC4
  *         @arg @ref LL_GTZC2_GRP1_VREFBUF
  *         @arg @ref LL_GTZC2_GRP1_DAC1
  *         @arg @ref LL_GTZC2_GRP1_ADF1
  * @retval State of interrupt (0 Disabled / 1 Enabled).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZIC_IsEnabledGrp1IT(const GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  return ((READ_BIT(p_tzic->IER1, periph) == periph) ? 1UL : 0UL);
}

/**
  * @brief  Enable IER2 illegal access interrupt.
  * @rmtoll
  *  IER2           xxxIE         LL_GTZC_TZIC_EnableGrp2IT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP2_TIM1
  *         @arg @ref LL_GTZC1_GRP2_SPI1
  *         @arg @ref LL_GTZC1_GRP2_TIM8
  *         @arg @ref LL_GTZC1_GRP2_USART1
  *         @arg @ref LL_GTZC1_GRP2_TIM15
  *         @arg @ref LL_GTZC1_GRP2_TIM16
  *         @arg @ref LL_GTZC1_GRP2_TIM17
  *         @arg @ref LL_GTZC1_GRP2_SAI1
  * @if SAI2
  *         @arg @ref LL_GTZC1_GRP2_SAI2
  * @endif
  * @if GTZC_CFGR2_LTDCUSB_Msk
  *         @arg @ref LL_GTZC1_GRP2_LTDC_USB
  * @endif
  * @if DSI
  *         @arg @ref LL_GTZC1_GRP2_DSI
  * @endif
  *
  *         @arg @ref LL_GTZC2_GRP4_SYSCFG
  *         @arg @ref LL_GTZC2_GRP4_RTC
  *         @arg @ref LL_GTZC2_GRP4_TAMP
  *         @arg @ref LL_GTZC2_GRP4_PWR
  *         @arg @ref LL_GTZC2_GRP4_RCC
  *         @arg @ref LL_GTZC2_GRP4_LPDMA1
  *         @arg @ref LL_GTZC2_GRP4_EXTI
  *         @arg @ref LL_GTZC2_GRP4_TZSC2
  *         @arg @ref LL_GTZC2_GRP4_TZIC2
  *         @arg @ref LL_GTZC2_GRP4_SRAM4
  *         @arg @ref LL_GTZC2_GRP4_MPCBB4_REG
  */
__STATIC_INLINE void LL_GTZC_TZIC_EnableGrp2IT(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  ATOMIC_SET_BIT(p_tzic->IER2, periph);
}

/**
  * @brief  Disable IER2 illegal access interrupt.
  * @rmtoll
  *  IER2           xxxIE         LL_GTZC_TZIC_DisableGrp2IT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP2_TIM1
  *         @arg @ref LL_GTZC1_GRP2_SPI1
  *         @arg @ref LL_GTZC1_GRP2_TIM8
  *         @arg @ref LL_GTZC1_GRP2_USART1
  *         @arg @ref LL_GTZC1_GRP2_TIM15
  *         @arg @ref LL_GTZC1_GRP2_TIM16
  *         @arg @ref LL_GTZC1_GRP2_TIM17
  *         @arg @ref LL_GTZC1_GRP2_SAI1
  * @if SAI2
  *         @arg @ref LL_GTZC1_GRP2_SAI2
  * @endif
  * @if GTZC_CFGR2_LTDCUSB_Msk
  *         @arg @ref LL_GTZC1_GRP2_LTDC_USB
  * @endif
  * @if DSI
  *         @arg @ref LL_GTZC1_GRP2_DSI
  * @endif
  *
  *         @arg @ref LL_GTZC2_GRP4_SYSCFG
  *         @arg @ref LL_GTZC2_GRP4_RTC
  *         @arg @ref LL_GTZC2_GRP4_TAMP
  *         @arg @ref LL_GTZC2_GRP4_PWR
  *         @arg @ref LL_GTZC2_GRP4_RCC
  *         @arg @ref LL_GTZC2_GRP4_LPDMA1
  *         @arg @ref LL_GTZC2_GRP4_EXTI
  *         @arg @ref LL_GTZC2_GRP4_TZSC2
  *         @arg @ref LL_GTZC2_GRP4_TZIC2
  *         @arg @ref LL_GTZC2_GRP4_SRAM4
  *         @arg @ref LL_GTZC2_GRP4_MPCBB4_REG
  */
__STATIC_INLINE void LL_GTZC_TZIC_DisableGrp2IT(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  ATOMIC_CLEAR_BIT(p_tzic->IER2, periph);
}

/**
  * @brief  Check if IER2 illegal access interrupt is enabled.
  * @rmtoll
  *  IER2           xxxIE         LL_GTZC_TZIC_IsEnabledGrp2IT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP2_TIM1
  *         @arg @ref LL_GTZC1_GRP2_SPI1
  *         @arg @ref LL_GTZC1_GRP2_TIM8
  *         @arg @ref LL_GTZC1_GRP2_USART1
  *         @arg @ref LL_GTZC1_GRP2_TIM15
  *         @arg @ref LL_GTZC1_GRP2_TIM16
  *         @arg @ref LL_GTZC1_GRP2_TIM17
  *         @arg @ref LL_GTZC1_GRP2_SAI1
  * @if SAI2
  *         @arg @ref LL_GTZC1_GRP2_SAI2
  * @endif
  * @if GTZC_CFGR2_LTDCUSB_Msk
  *         @arg @ref LL_GTZC1_GRP2_LTDC_USB
  * @endif
  * @if DSI
  *         @arg @ref LL_GTZC1_GRP2_DSI
  * @endif
  *
  *         @arg @ref LL_GTZC2_GRP2_SYSCFG
  *         @arg @ref LL_GTZC2_GRP2_RTC
  *         @arg @ref LL_GTZC2_GRP2_TAMP
  *         @arg @ref LL_GTZC2_GRP2_PWR
  *         @arg @ref LL_GTZC2_GRP2_RCC
  *         @arg @ref LL_GTZC2_GRP2_LPDMA1
  *         @arg @ref LL_GTZC2_GRP2_EXTI
  *         @arg @ref LL_GTZC2_GRP2_TZSC2
  *         @arg @ref LL_GTZC2_GRP2_TZIC2
  *         @arg @ref LL_GTZC2_GRP2_SRAM4
  *         @arg @ref LL_GTZC2_GRP2_MPCBB4_REG
  * @retval state of interrupt (0 Disabled / 1 Enabled).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZIC_IsEnabledGrp2IT(const GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  return ((READ_BIT(p_tzic->IER2, periph) == periph) ? 1UL : 0UL);
}

/**
  * @brief  Enable IER3 illegal access interrupt.
  * @rmtoll
  *  IER3           xxxIE         LL_GTZC_TZIC_EnableGrp3IT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP3_MDF1
  *         @arg @ref LL_GTZC1_GRP3_CORDIC
  *         @arg @ref LL_GTZC1_GRP3_FMAC
  *         @arg @ref LL_GTZC1_GRP3_CRC
  *         @arg @ref LL_GTZC1_GRP3_TSC
  * @if DMA2D
  *         @arg @ref LL_GTZC1_GRP3_DMA2D
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_ICACHE_REG
  *         @arg @ref LL_GTZC1_GRP3_DCACHE1_REG
  *         @arg @ref LL_GTZC1_GRP3_ADC12
  *         @arg @ref LL_GTZC1_GRP3_DCMI
  * @if USB_OTG_GLOBAL_BASE
  *         @arg @ref LL_GTZC1_GRP3_OTG
  * @endif
  * @if AES
  *         @arg @ref LL_GTZC1_GRP3_AES
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_HASH
  *         @arg @ref LL_GTZC1_GRP3_RNG
  * @if PKA
  *         @arg @ref LL_GTZC1_GRP3_PKA
  * @endif
  * @if SAES
  *         @arg @ref LL_GTZC1_GRP3_SAES
  * @endif
  * @if OCTOSPIM
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPIM
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_SDMMC1
  * @if SDMMC2
  *         @arg @ref LL_GTZC1_GRP3_SDMMC2
  * @endif
  * @if FMC_BASE
  *         @arg @ref LL_GTZC1_GRP3_FSMC_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI1_REG
  * @if OCTOSPI2
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI2_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_RAMCFG
  * @if GPU2D
  *         @arg @ref LL_GTZC1_GRP3_GPU2D
  * @endif
  * @if GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU_REG
  * @endif
  * @if HSPI1
  *         @arg @ref LL_GTZC1_GRP3_HSPI1_REG
  * @endif
  * @if DCACHE2
  *         @arg @ref LL_GTZC1_GRP3_DCACHE2_REG
  * @endif
  */
__STATIC_INLINE void LL_GTZC_TZIC_EnableGrp3IT(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  ATOMIC_SET_BIT(p_tzic->IER3, periph);
}

/**
  * @brief  Disable IER3 illegal access interrupt.
  * @rmtoll
  *  IER3           xxxIE         LL_GTZC_TZIC_DisableGrp3IT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP3_MDF1
  *         @arg @ref LL_GTZC1_GRP3_CORDIC
  *         @arg @ref LL_GTZC1_GRP3_FMAC
  *         @arg @ref LL_GTZC1_GRP3_CRC
  *         @arg @ref LL_GTZC1_GRP3_TSC
  * @if DMA2D
  *         @arg @ref LL_GTZC1_GRP3_DMA2D
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_ICACHE_REG
  *         @arg @ref LL_GTZC1_GRP3_DCACHE1_REG
  *         @arg @ref LL_GTZC1_GRP3_ADC12
  *         @arg @ref LL_GTZC1_GRP3_DCMI
  * @if USB_OTG_GLOBAL_BASE
  *         @arg @ref LL_GTZC1_GRP3_OTG
  * @endif
  * @if AES
  *         @arg @ref LL_GTZC1_GRP3_AES
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_HASH
  *         @arg @ref LL_GTZC1_GRP3_RNG
  * @if PKA
  *         @arg @ref LL_GTZC1_GRP3_PKA
  * @endif
  * @if SAES
  *         @arg @ref LL_GTZC1_GRP3_SAES
  * @endif
  * @if OCTOSPIM
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPIM
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_SDMMC1
  * @if SDMMC2
  *         @arg @ref LL_GTZC1_GRP3_SDMMC2
  * @endif
  * @if FMC_BASE
  *         @arg @ref LL_GTZC1_GRP3_FSMC_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI1_REG
  * @if OCTOSPI2
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI2_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_RAMCFG
  * @if GPU2D
  *         @arg @ref LL_GTZC1_GRP3_GPU2D
  * @endif
  * @if GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU_REG
  * @endif
  * @if HSPI1
  *         @arg @ref LL_GTZC1_GRP3_HSPI1_REG
  * @endif
  * @if DCACHE2
  *         @arg @ref LL_GTZC1_GRP3_DCACHE2_REG
  * @endif
  */
__STATIC_INLINE void LL_GTZC_TZIC_DisableGrp3IT(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  ATOMIC_CLEAR_BIT(p_tzic->IER3, periph);
}

/**
  * @brief  Check if IER3 illegal access interrupt is enabled.
  * @rmtoll
  *  IER3           xxxIE         LL_GTZC_TZIC_IsEnabledGrp3IT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP3_MDF1
  *         @arg @ref LL_GTZC1_GRP3_CORDIC
  *         @arg @ref LL_GTZC1_GRP3_FMAC
  *         @arg @ref LL_GTZC1_GRP3_CRC
  *         @arg @ref LL_GTZC1_GRP3_TSC
  * @if DMA2D
  *         @arg @ref LL_GTZC1_GRP3_DMA2D
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_ICACHE_REG
  *         @arg @ref LL_GTZC1_GRP3_DCACHE1_REG
  *         @arg @ref LL_GTZC1_GRP3_ADC12
  *         @arg @ref LL_GTZC1_GRP3_DCMI
  * @if USB_OTG_GLOBAL_BASE
  *         @arg @ref LL_GTZC1_GRP3_OTG
  * @endif
  * @if AES
  *         @arg @ref LL_GTZC1_GRP3_AES
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_HASH
  *         @arg @ref LL_GTZC1_GRP3_RNG
  * @if PKA
  *         @arg @ref LL_GTZC1_GRP3_PKA
  * @endif
  * @if SAES
  *         @arg @ref LL_GTZC1_GRP3_SAES
  * @endif
  * @if OCTOSPIM
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPIM
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_SDMMC1
  * @if SDMMC2
  *         @arg @ref LL_GTZC1_GRP3_SDMMC2
  * @endif
  * @if FMC_BASE
  *         @arg @ref LL_GTZC1_GRP3_FSMC_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI1_REG
  * @if OCTOSPI2
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI2_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_RAMCFG
  * @if GPU2D
  *         @arg @ref LL_GTZC1_GRP3_GPU2D
  * @endif
  * @if GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU_REG
  * @endif
  * @if HSPI1
  *         @arg @ref LL_GTZC1_GRP3_HSPI1_REG
  * @endif
  * @if DCACHE2
  *         @arg @ref LL_GTZC1_GRP3_DCACHE2_REG
  * @endif
  * @retval State of interrupt (0 Disabled / 1 Enabled).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZIC_IsEnabledGrp3IT(const GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  return ((READ_BIT(p_tzic->IER3, periph) == periph) ? 1UL : 0UL);
}

/**
  * @brief  Enable IER4 illegal access interrupt.
  * @rmtoll
  *  IER4           xxxIE         LL_GTZC_TZIC_EnableGrp4IT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP4_GPDMA1
  *         @arg @ref LL_GTZC1_GRP4_FLASH_REG
  *         @arg @ref LL_GTZC1_GRP4_FLASH
  * @if OTFDEC1
  *         @arg @ref LL_GTZC1_GRP4_OTFDEC1
  * @endif
  * @if OTFDEC2
  *         @arg @ref LL_GTZC1_GRP4_OTFDEC2
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_TZSC1
  *         @arg @ref LL_GTZC1_GRP4_TZIC1
  *         @arg @ref LL_GTZC1_GRP4_OCTOSPI1_MEM
  * @if FMC_BASE
  *         @arg @ref LL_GTZC1_GRP4_FSMC_MEM
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_BKPSRAM
  * @if OCTOSPI2
  *         @arg @ref LL_GTZC1_GRP4_OCTOSPI2_MEM
  * @endif
  * @if HSPI1
  *         @arg @ref LL_GTZC1_GRP4_HSPI1_MEM
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_SRAM1
  *         @arg @ref LL_GTZC1_GRP4_MPCBB1_REG
  *         @arg @ref LL_GTZC1_GRP4_SRAM2
  *         @arg @ref LL_GTZC1_GRP4_MPCBB2_REG
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC1_GRP4_SRAM3
  *         @arg @ref LL_GTZC1_GRP4_MPCBB3_REG
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref LL_GTZC1_GRP4_SRAM5
  *         @arg @ref LL_GTZC1_GRP4_MPCBB5_REG
  *  @endif
  */
__STATIC_INLINE void LL_GTZC_TZIC_EnableGrp4IT(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  ATOMIC_SET_BIT(p_tzic->IER4, periph);
}

/**
  * @brief  Disable IER4 illegal access interrupt.
  * @rmtoll
  *  IER4           xxxIE         LL_GTZC_TZIC_DisableGrp4IT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP4_GPDMA1
  *         @arg @ref LL_GTZC1_GRP4_FLASH_REG
  *         @arg @ref LL_GTZC1_GRP4_FLASH
  * @if OTFDEC1
  *         @arg @ref LL_GTZC1_GRP4_OTFDEC1
  * @endif
  * @if OTFDEC2
  *         @arg @ref LL_GTZC1_GRP4_OTFDEC2
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_TZSC1
  *         @arg @ref LL_GTZC1_GRP4_TZIC1
  *         @arg @ref LL_GTZC1_GRP4_OCTOSPI1_MEM
  * @if FMC_BASE
  *         @arg @ref LL_GTZC1_GRP4_FSMC_MEM
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_BKPSRAM
  * @if OCTOSPI2
  *         @arg @ref LL_GTZC1_GRP4_OCTOSPI2_MEM
  * @endif
  * @if HSPI1
  *         @arg @ref LL_GTZC1_GRP4_HSPI1_MEM
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_SRAM1
  *         @arg @ref LL_GTZC1_GRP4_MPCBB1_REG
  *         @arg @ref LL_GTZC1_GRP4_SRAM2
  *         @arg @ref LL_GTZC1_GRP4_MPCBB2_REG
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC1_GRP4_SRAM3
  *         @arg @ref LL_GTZC1_GRP4_MPCBB3_REG
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref LL_GTZC1_GRP4_SRAM5
  *         @arg @ref LL_GTZC1_GRP4_MPCBB5_REG
  *  @endif
  */
__STATIC_INLINE void LL_GTZC_TZIC_DisableGrp4IT(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  ATOMIC_CLEAR_BIT(p_tzic->IER4, periph);
}

/**
  * @brief  Check if IER4 illegal access interrupt is enabled.
  * @rmtoll
  *  IER4           xxxIE         LL_GTZC_TZIC_IsEnabledGrp4IT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP4_GPDMA1
  *         @arg @ref LL_GTZC1_GRP4_FLASH_REG
  *         @arg @ref LL_GTZC1_GRP4_FLASH
  * @if OTFDEC1
  *         @arg @ref LL_GTZC1_GRP4_OTFDEC1
  * @endif
  * @if OTFDEC2
  *         @arg @ref LL_GTZC1_GRP4_OTFDEC2
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_TZSC1
  *         @arg @ref LL_GTZC1_GRP4_TZIC1
  *         @arg @ref LL_GTZC1_GRP4_OCTOSPI1_MEM
  * @if FMC_BASE
  *         @arg @ref LL_GTZC1_GRP4_FSMC_MEM
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_BKPSRAM
  * @if OCTOSPI2
  *         @arg @ref LL_GTZC1_GRP4_OCTOSPI2_MEM
  * @endif
  * @if HSPI1
  *         @arg @ref LL_GTZC1_GRP4_HSPI1_MEM
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_SRAM1
  *         @arg @ref LL_GTZC1_GRP4_MPCBB1_REG
  *         @arg @ref LL_GTZC1_GRP4_SRAM2
  *         @arg @ref LL_GTZC1_GRP4_MPCBB2_REG
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC1_GRP4_SRAM3
  *         @arg @ref LL_GTZC1_GRP4_MPCBB3_REG
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref LL_GTZC1_GRP4_SRAM5
  *         @arg @ref LL_GTZC1_GRP4_MPCBB5_REG
  *  @endif
  * @retval State of interrupt (0 Disabled / 1 Enabled)
  */
__STATIC_INLINE uint32_t LL_GTZC_TZIC_IsEnabledGrp4IT(const GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  return ((READ_BIT(p_tzic->IER4, periph) == periph) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup GTZC_LL_EF_TZIC_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Get SR1 illegal access flag.
  * @rmtoll
  *  SR1           xxxF         LL_GTZC_TZIC_IsActiveGrp1Flag
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP1_TIM2
  *         @arg @ref LL_GTZC1_GRP1_TIM3
  *         @arg @ref LL_GTZC1_GRP1_TIM4
  *         @arg @ref LL_GTZC1_GRP1_TIM5
  *         @arg @ref LL_GTZC1_GRP1_TIM6
  *         @arg @ref LL_GTZC1_GRP1_TIM7
  *         @arg @ref LL_GTZC1_GRP1_WWDG
  *         @arg @ref LL_GTZC1_GRP1_IWDG
  *         @arg @ref LL_GTZC1_GRP1_SPI2
  * @if USART2
  *         @arg @ref LL_GTZC1_GRP1_USART2
  * @endif
  *         @arg @ref LL_GTZC1_GRP1_USART3
  *         @arg @ref LL_GTZC1_GRP1_UART4
  *         @arg @ref LL_GTZC1_GRP1_UART5
  *         @arg @ref LL_GTZC1_GRP1_I2C1
  *         @arg @ref LL_GTZC1_GRP1_I2C2
  *         @arg @ref LL_GTZC1_GRP1_CRS
  *         @arg @ref LL_GTZC1_GRP1_I2C4
  *         @arg @ref LL_GTZC1_GRP1_LPTIM2
  *         @arg @ref LL_GTZC1_GRP1_FDCAN1
  * @if UCPD1
  *         @arg @ref LL_GTZC1_GRP1_UCPD1
  * @endif
  * @if USART6
  *         @arg @ref LL_GTZC1_GRP1_USART6
  * @endif
  * @if I2C5
  *         @arg @ref LL_GTZC1_GRP1_I2C5
  * @endif
  * @if I2C6
  *         @arg @ref LL_GTZC1_GRP1_I2C6
  * @endif
  *         @arg @ref LL_GTZC2_GRP1_SPI3
  *         @arg @ref LL_GTZC2_GRP1_LPUART1
  *         @arg @ref LL_GTZC2_GRP1_I2C3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM1
  *         @arg @ref LL_GTZC2_GRP1_LPTIM3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM4
  *         @arg @ref LL_GTZC2_GRP1_OPAMP
  *         @arg @ref LL_GTZC2_GRP1_COMP
  *         @arg @ref LL_GTZC2_GRP1_ADC4
  *         @arg @ref LL_GTZC2_GRP1_VREFBUF
  *         @arg @ref LL_GTZC2_GRP1_DAC1
  *         @arg @ref LL_GTZC2_GRP1_ADF1
  * @retval State of flag (0 No-interrupt / 1 interrupt).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZIC_IsActiveGrp1Flag(const GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  return ((READ_BIT(p_tzic->SR1, periph) == periph) ? 1UL : 0UL);
}

/**
  * @brief  Get SR2 illegal access flag.
  * @rmtoll
  *  SR2           xxxF         LL_GTZC_TZIC_IsActiveGrp2Flag
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP2_TIM1
  *         @arg @ref LL_GTZC1_GRP2_SPI1
  *         @arg @ref LL_GTZC1_GRP2_TIM8
  *         @arg @ref LL_GTZC1_GRP2_USART1
  *         @arg @ref LL_GTZC1_GRP2_TIM15
  *         @arg @ref LL_GTZC1_GRP2_TIM16
  *         @arg @ref LL_GTZC1_GRP2_TIM17
  *         @arg @ref LL_GTZC1_GRP2_SAI1
  * @if SAI2
  *         @arg @ref LL_GTZC1_GRP2_SAI2
  * @endif
  * @if GTZC_CFGR2_LTDCUSB_Msk
  *         @arg @ref LL_GTZC1_GRP2_LTDC_USB
  * @endif
  * @if DSI
  *         @arg @ref LL_GTZC1_GRP2_DSI
  * @endif
  *         @arg @ref LL_GTZC2_GRP2_SYSCFG
  *         @arg @ref LL_GTZC2_GRP2_RTC
  *         @arg @ref LL_GTZC2_GRP2_TAMP
  *         @arg @ref LL_GTZC2_GRP2_PWR
  *         @arg @ref LL_GTZC2_GRP2_RCC
  *         @arg @ref LL_GTZC2_GRP2_LPDMA1
  *         @arg @ref LL_GTZC2_GRP2_EXTI
  *         @arg @ref LL_GTZC2_GRP2_TZSC2
  *         @arg @ref LL_GTZC2_GRP2_TZIC2
  *         @arg @ref LL_GTZC2_GRP2_SRAM4
  *         @arg @ref LL_GTZC2_GRP2_MPCBB4_REG
  * @retval State of flag (0 No-interrupt / 1 interrupt).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZIC_IsActiveGrp2Flag(const GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  return ((READ_BIT(p_tzic->SR2, periph) == periph) ? 1UL : 0UL);
}

/**
  * @brief  Get SR3 illegal access flag.
  * @rmtoll
  *  SR3           xxxF         LL_GTZC_TZIC_IsActiveGrp3Flag
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP3_MDF1
  *         @arg @ref LL_GTZC1_GRP3_CORDIC
  *         @arg @ref LL_GTZC1_GRP3_FMAC
  *         @arg @ref LL_GTZC1_GRP3_CRC
  *         @arg @ref LL_GTZC1_GRP3_TSC
  * @if DMA2D
  *         @arg @ref LL_GTZC1_GRP3_DMA2D
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_ICACHE_REG
  *         @arg @ref LL_GTZC1_GRP3_DCACHE1_REG
  *         @arg @ref LL_GTZC1_GRP3_ADC12
  *         @arg @ref LL_GTZC1_GRP3_DCMI
  * @if USB_OTG_GLOBAL_BASE
  *         @arg @ref LL_GTZC1_GRP3_OTG
  * @endif
  * @if AES
  *         @arg @ref LL_GTZC1_GRP3_AES
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_HASH
  *         @arg @ref LL_GTZC1_GRP3_RNG
  * @if PKA
  *         @arg @ref LL_GTZC1_GRP3_PKA
  * @endif
  * @if SAES
  *         @arg @ref LL_GTZC1_GRP3_SAES
  * @endif
  * @if OCTOSPIM
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPIM
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_SDMMC1
  * @if SDMMC2
  *         @arg @ref LL_GTZC1_GRP3_SDMMC2
  * @endif
  * @if FMC_BASE
  *         @arg @ref LL_GTZC1_GRP3_FSMC_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI1_REG
  * @if OCTOSPI2
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI2_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_RAMCFG
  * @if GPU2D
  *         @arg @ref LL_GTZC1_GRP3_GPU2D
  * @endif
  * @if GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU_REG
  * @endif
  * @if HSPI1
  *         @arg @ref LL_GTZC1_GRP3_HSPI1_REG
  * @endif
  * @if DCACHE2
  *         @arg @ref LL_GTZC1_GRP3_DCACHE2_REG
  * @endif
  * @retval State of flag (0 No-interrupt / 1 interrupt).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZIC_IsActiveGrp3Flag(const GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  return ((READ_BIT(p_tzic->SR3, periph) == periph) ? 1UL : 0UL);
}

/**
  * @brief  Get SR4 illegal access flag.
  * @rmtoll
  *  SR4           xxxF         LL_GTZC_TZIC_IsActiveGrp4Flag
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP4_GPDMA1
  *         @arg @ref LL_GTZC1_GRP4_FLASH_REG
  *         @arg @ref LL_GTZC1_GRP4_FLASH
  * @if OTFDEC1
  *         @arg @ref LL_GTZC1_GRP4_OTFDEC1
  * @endif
  * @if OTFDEC2
  *         @arg @ref LL_GTZC1_GRP4_OTFDEC2
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_TZSC1
  *         @arg @ref LL_GTZC1_GRP4_TZIC1
  *         @arg @ref LL_GTZC1_GRP4_OCTOSPI1_MEM
  * @if FMC_BASE
  *         @arg @ref LL_GTZC1_GRP4_FSMC_MEM
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_BKPSRAM
  * @if OCTOSPI2
  *         @arg @ref LL_GTZC1_GRP4_OCTOSPI2_MEM
  * @endif
  * @if HSPI1
  *         @arg @ref LL_GTZC1_GRP4_HSPI1_MEM
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_SRAM1
  *         @arg @ref LL_GTZC1_GRP4_MPCBB1_REG
  *         @arg @ref LL_GTZC1_GRP4_SRAM2
  *         @arg @ref LL_GTZC1_GRP4_MPCBB2_REG
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC1_GRP4_SRAM3
  *         @arg @ref LL_GTZC1_GRP4_MPCBB3_REG
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref LL_GTZC1_GRP4_SRAM5
  *         @arg @ref LL_GTZC1_GRP4_MPCBB5_REG
  *  @endif
  * @retval State of flag (0 No-interrupt / 1 interrupt).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZIC_IsActiveGrp4Flag(const GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  return ((READ_BIT(p_tzic->SR4, periph) == periph) ? 1UL : 0UL);
}

/**
  * @brief  Clear FCR1 illegal access flag.
  * @rmtoll
  *  FCR1           xxxF         LL_GTZC_TZIC_ClearGrp1Flag
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP1_TIM2
  *         @arg @ref LL_GTZC1_GRP1_TIM3
  *         @arg @ref LL_GTZC1_GRP1_TIM4
  *         @arg @ref LL_GTZC1_GRP1_TIM5
  *         @arg @ref LL_GTZC1_GRP1_TIM6
  *         @arg @ref LL_GTZC1_GRP1_TIM7
  *         @arg @ref LL_GTZC1_GRP1_WWDG
  *         @arg @ref LL_GTZC1_GRP1_IWDG
  *         @arg @ref LL_GTZC1_GRP1_SPI2
  * @if USART2
  *         @arg @ref LL_GTZC1_GRP1_USART2
  * @endif
  *         @arg @ref LL_GTZC1_GRP1_USART3
  *         @arg @ref LL_GTZC1_GRP1_UART4
  *         @arg @ref LL_GTZC1_GRP1_UART5
  *         @arg @ref LL_GTZC1_GRP1_I2C1
  *         @arg @ref LL_GTZC1_GRP1_I2C2
  *         @arg @ref LL_GTZC1_GRP1_CRS
  *         @arg @ref LL_GTZC1_GRP1_I2C4
  *         @arg @ref LL_GTZC1_GRP1_LPTIM2
  *         @arg @ref LL_GTZC1_GRP1_FDCAN1
  * @if UCPD1
  *         @arg @ref LL_GTZC1_GRP1_UCPD1
  * @endif
  * @if USART6
  *         @arg @ref LL_GTZC1_GRP1_USART6
  * @endif
  * @if I2C5
  *         @arg @ref LL_GTZC1_GRP1_I2C5
  * @endif
  * @if I2C6
  *         @arg @ref LL_GTZC1_GRP1_I2C6
  * @endif
  *         @arg @ref LL_GTZC2_GRP1_SPI3
  *         @arg @ref LL_GTZC2_GRP1_LPUART1
  *         @arg @ref LL_GTZC2_GRP1_I2C3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM1
  *         @arg @ref LL_GTZC2_GRP1_LPTIM3
  *         @arg @ref LL_GTZC2_GRP1_LPTIM4
  *         @arg @ref LL_GTZC2_GRP1_OPAMP
  *         @arg @ref LL_GTZC2_GRP1_COMP
  *         @arg @ref LL_GTZC2_GRP1_ADC4
  *         @arg @ref LL_GTZC2_GRP1_VREFBUF
  *         @arg @ref LL_GTZC2_GRP1_DAC1
  *         @arg @ref LL_GTZC2_GRP1_ADF1
  */
__STATIC_INLINE void LL_GTZC_TZIC_ClearGrp1Flag(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  ATOMIC_SET_BIT(p_tzic->FCR1, periph);
}

/**
  * @brief Clear FCR2 illegal access flag.
  * @rmtoll
  *  FCR2           xxxF         LL_GTZC_TZIC_ClearGrp2Flag
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP2_TIM1
  *         @arg @ref LL_GTZC1_GRP2_SPI1
  *         @arg @ref LL_GTZC1_GRP2_TIM8
  *         @arg @ref LL_GTZC1_GRP2_USART1
  *         @arg @ref LL_GTZC1_GRP2_TIM15
  *         @arg @ref LL_GTZC1_GRP2_TIM16
  *         @arg @ref LL_GTZC1_GRP2_TIM17
  *         @arg @ref LL_GTZC1_GRP2_SAI1
  * @if SAI2
  *         @arg @ref LL_GTZC1_GRP2_SAI2
  * @endif
  * @if GTZC_CFGR2_LTDCUSB_Msk
  *         @arg @ref LL_GTZC1_GRP2_LTDC_USB
  * @endif
  * @if DSI
  *         @arg @ref LL_GTZC1_GRP2_DSI
  * @endif
  *         @arg @ref LL_GTZC2_GRP2_SYSCFG
  *         @arg @ref LL_GTZC2_GRP2_RTC
  *         @arg @ref LL_GTZC2_GRP2_TAMP
  *         @arg @ref LL_GTZC2_GRP2_PWR
  *         @arg @ref LL_GTZC2_GRP2_RCC
  *         @arg @ref LL_GTZC2_GRP2_LPDMA1
  *         @arg @ref LL_GTZC2_GRP2_EXTI
  *         @arg @ref LL_GTZC2_GRP2_TZSC2
  *         @arg @ref LL_GTZC2_GRP2_TZIC2
  *         @arg @ref LL_GTZC2_GRP2_SRAM4
  *         @arg @ref LL_GTZC2_GRP2_MPCBB4_REG
  */
__STATIC_INLINE void LL_GTZC_TZIC_ClearGrp2Flag(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  ATOMIC_SET_BIT(p_tzic->FCR2, periph);
}

/**
  * @brief  Clear FCR3 illegal access flag.
  * @rmtoll
  *  FCR3           xxxF         LL_GTZC_TZIC_ClearGrp3Flag
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP3_MDF1
  *         @arg @ref LL_GTZC1_GRP3_CORDIC
  *         @arg @ref LL_GTZC1_GRP3_FMAC
  *         @arg @ref LL_GTZC1_GRP3_CRC
  *         @arg @ref LL_GTZC1_GRP3_TSC
  * @if DMA2D
  *         @arg @ref LL_GTZC1_GRP3_DMA2D
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_ICACHE_REG
  *         @arg @ref LL_GTZC1_GRP3_DCACHE1_REG
  *         @arg @ref LL_GTZC1_GRP3_ADC12
  *         @arg @ref LL_GTZC1_GRP3_DCMI
  * @if USB_OTG_GLOBAL_BASE
  *         @arg @ref LL_GTZC1_GRP3_OTG
  * @endif
  * @if AES
  *         @arg @ref LL_GTZC1_GRP3_AES
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_HASH
  *         @arg @ref LL_GTZC1_GRP3_RNG
  * @if PKA
  *         @arg @ref LL_GTZC1_GRP3_PKA
  * @endif
  * @if SAES
  *         @arg @ref LL_GTZC1_GRP3_SAES
  * @endif
  * @if OCTOSPIM
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPIM
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_SDMMC1
  * @if SDMMC2
  *         @arg @ref LL_GTZC1_GRP3_SDMMC2
  * @endif
  * @if FMC_BASE
  *         @arg @ref LL_GTZC1_GRP3_FSMC_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI1_REG
  * @if OCTOSPI2
  *         @arg @ref LL_GTZC1_GRP3_OCTOSPI2_REG
  * @endif
  *         @arg @ref LL_GTZC1_GRP3_RAMCFG
  * @if GPU2D
  *         @arg @ref LL_GTZC1_GRP3_GPU2D
  * @endif
  * @if GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU
  *         @arg @ref LL_GTZC1_GRP3_GFXMMU_REG
  * @endif
  * @if HSPI1
  *         @arg @ref LL_GTZC1_GRP3_HSPI1_REG
  * @endif
  * @if DCACHE2
  *         @arg @ref LL_GTZC1_GRP3_DCACHE2_REG
  * @endif
  */
__STATIC_INLINE void LL_GTZC_TZIC_ClearGrp3Flag(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  ATOMIC_SET_BIT(p_tzic->FCR3, periph);
}

/**
  * @brief  Clear FCR4 illegal access flag.
  * @rmtoll
  *  FCR4           xxxF         LL_GTZC_TZIC_ClearGrp4Flag
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC1_GRP4_GPDMA1
  *         @arg @ref LL_GTZC1_GRP4_FLASH_REG
  *         @arg @ref LL_GTZC1_GRP4_FLASH
  * @if OTFDEC1
  *         @arg @ref LL_GTZC1_GRP4_OTFDEC1
  * @endif
  * @if OTFDEC2
  *         @arg @ref LL_GTZC1_GRP4_OTFDEC2
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_TZSC1
  *         @arg @ref LL_GTZC1_GRP4_TZIC1
  *         @arg @ref LL_GTZC1_GRP4_OCTOSPI1_MEM
  * @if FMC_BASE
  *         @arg @ref LL_GTZC1_GRP4_FSMC_MEM
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_BKPSRAM
  * @if OCTOSPI2
  *         @arg @ref LL_GTZC1_GRP4_OCTOSPI2_MEM
  * @endif
  * @if HSPI1
  *         @arg @ref LL_GTZC1_GRP4_HSPI1_MEM
  * @endif
  *         @arg @ref LL_GTZC1_GRP4_SRAM1
  *         @arg @ref LL_GTZC1_GRP4_MPCBB1_REG
  *         @arg @ref LL_GTZC1_GRP4_SRAM2
  *         @arg @ref LL_GTZC1_GRP4_MPCBB2_REG
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC1_GRP4_SRAM3
  *         @arg @ref LL_GTZC1_GRP4_MPCBB3_REG
  * @endif
  * @if SRAM5_BASE
  *         @arg @ref LL_GTZC1_GRP4_SRAM5
  *         @arg @ref LL_GTZC1_GRP4_MPCBB5_REG
  *  @endif
  */
__STATIC_INLINE void LL_GTZC_TZIC_ClearGrp4Flag(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  ATOMIC_SET_BIT(p_tzic->FCR4, periph);
}

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

#endif /* STM32U5xx_LL_GTZC_H */
