/**
  ******************************************************************************
  * @file    stm32_hal.h
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver, whatever the STM32 family.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32_HAL_H
#define STM32_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
#include "stm32_hal_os.h"
#endif /* USE_HAL_MUTEX == 1 */

#if defined(USE_HAL_RCC_MODULE) && (USE_HAL_RCC_MODULE == 1)
#include "stm32u5xx_hal_rcc.h"
#endif /* USE_HAL_RCC_MODULE == 1 */

#if defined(USE_HAL_GPIO_MODULE) && (USE_HAL_GPIO_MODULE == 1)
#include "stm32u5xx_hal_gpio.h"
#endif /* USE_HAL_GPIO_MODULE == 1 */

#if defined(USE_HAL_ICACHE_MODULE) && (USE_HAL_ICACHE_MODULE == 1)
#include "stm32u5xx_hal_icache.h"
#endif /* USE_HAL_ICACHE_MODULE == 1 */

#if defined(USE_HAL_DCACHE_MODULE) && (USE_HAL_DCACHE_MODULE == 1)
#include "stm32u5xx_hal_dcache.h"
#endif /* USE_HAL_DCACHE_MODULE == 1 */

#if defined(USE_HAL_GTZC_MODULE) && (USE_HAL_GTZC_MODULE == 1)
#include "stm32u5xx_hal_gtzc.h"
#endif /* USE_HAL_GTZC_MODULE == 1 */

#if defined(USE_HAL_DMA_MODULE) && (USE_HAL_DMA_MODULE == 1)
#include "stm32u5xx_hal_dma.h"
#endif /* USE_HAL_DMA_MODULE == 1 */

#if defined(USE_HAL_DMA2D_MODULE) && (USE_HAL_DMA2D_MODULE == 1)
#include "stm32u5xx_hal_dma2d.h"
#endif /* USE_HAL_DMA2D_MODULE == 1 */

#if defined(USE_HAL_DSI_MODULE) && (USE_HAL_DSI_MODULE == 1)
#include "stm32u5xx_hal_dsi.h"
#endif /* USE_HAL_DSI_MODULE == 1 */

#if defined(USE_HAL_CORTEX_MODULE) && (USE_HAL_CORTEX_MODULE == 1)
#include "stm32u5xx_hal_cortex.h"
#endif /* USE_HAL_CORTEX_MODULE == 1 */

#if defined(USE_HAL_PKA_MODULE) && (USE_HAL_PKA_MODULE == 1)
#include "stm32u5xx_hal_pka.h"
#endif /* USE_HAL_PKA_MODULE == 1 */

#if defined(USE_HAL_ADC_MODULE) && (USE_HAL_ADC_MODULE == 1)
#include "stm32u5xx_hal_adc.h"
#endif /* USE_HAL_ADC_MODULE == 1 */

#if defined(USE_HAL_ADF_MODULE) && (USE_HAL_ADF_MODULE == 1)
#include "stm32u5xx_hal_adf.h"
#endif /* USE_HAL_ADF_MODULE == 1 */

#if defined(USE_HAL_COMP_MODULE) && (USE_HAL_COMP_MODULE == 1)
#include "stm32u5xx_hal_comp.h"
#endif /* USE_HAL_COMP_MODULE == 1 */

#if defined(USE_HAL_CRC_MODULE) && (USE_HAL_CRC_MODULE == 1)
#include "stm32u5xx_hal_crc.h"
#endif /* USE_HAL_CRC_MODULE == 1 */

#if defined(USE_HAL_CRS_MODULE) && (USE_HAL_CRS_MODULE == 1)
#include "stm32u5xx_hal_crs.h"
#endif /* USE_HAL_CRS_MODULE == 1 */

#if defined(USE_HAL_AES_MODULE) && (USE_HAL_AES_MODULE == 1)
#include "stm32u5xx_hal_aes.h"
#endif /* USE_HAL_AES_MODULE == 1 */

#if defined(USE_HAL_DAC_MODULE) && (USE_HAL_DAC_MODULE == 1)
#include "stm32u5xx_hal_dac.h"
#endif /* USE_HAL_DAC_MODULE == 1 */

#if defined(USE_HAL_DBGMCU_MODULE) && (USE_HAL_DBGMCU_MODULE == 1)
#include "stm32u5xx_hal_dbgmcu.h"
#endif /* USE_HAL_DBGMCU_MODULE == 1 */

#if defined(USE_HAL_FLASH_MODULE) && (USE_HAL_FLASH_MODULE == 1)
#include "stm32u5xx_hal_flash.h"
#endif /* USE_HAL_FLASH_MODULE == 1 */

#if defined(USE_HAL_FLASH_ITF_MODULE) && (USE_HAL_FLASH_ITF_MODULE == 1)
#include "stm32u5xx_hal_flash_itf.h"
#endif /* USE_HAL_FLASH_ITF_MODULE == 1 */

#if defined(USE_HAL_GPU2D_MODULE) && (USE_HAL_GPU2D_MODULE == 1)
#include "stm32u5xx_hal_gpu2d.h"
#endif /* USE_HAL_GPU2D_MODULE == 1 */

#if defined(USE_HAL_HASH_MODULE) && (USE_HAL_HASH_MODULE == 1)
#include "stm32u5xx_hal_hash.h"
#endif /* USE_HAL_HASH_MODULE == 1 */

#if defined(USE_HAL_SRAM_MODULE) && (USE_HAL_SRAM_MODULE == 1)
#include "stm32u5xx_hal_sram.h"
#endif /* USE_HAL_SRAM_MODULE == 1 */

#if defined(USE_HAL_MMC_MODULE) && (USE_HAL_MMC_MODULE == 1)
#include "stm32u5xx_hal_mmc.h"
#endif /* USE_HAL_MMC_MODULE == 1 */

#if defined(USE_HAL_NOR_MODULE) && (USE_HAL_NOR_MODULE == 1)
#include "stm32u5xx_hal_nor.h"
#endif /* USE_HAL_NOR_MODULE == 1 */

#if defined(USE_HAL_NAND_MODULE) && (USE_HAL_NAND_MODULE == 1)
#include "stm32u5xx_hal_nand.h"
#endif /* USE_HAL_NAND_MODULE == 1 */

#if defined(USE_HAL_I2C_MODULE) && (USE_HAL_I2C_MODULE == 1)
#include "stm32u5xx_hal_i2c.h"
#endif /* USE_HAL_I2C_MODULE == 1 */

#if defined(USE_HAL_IWDG_MODULE) && (USE_HAL_IWDG_MODULE == 1)
#include "stm32u5xx_hal_iwdg.h"
#endif /* USE_HAL_IWDG_MODULE == 1 */

#if defined(USE_HAL_JPEG_MODULE) && (USE_HAL_JPEG_MODULE == 1)
#include "stm32u5xx_hal_jpeg.h"
#endif /* USE_HAL_JPEG_MODULE == 1 */

#if defined(USE_HAL_LPTIM_MODULE) && (USE_HAL_LPTIM_MODULE == 1)
#include "stm32u5xx_hal_lptim.h"
#endif /* USE_HAL_LPTIM_MODULE == 1 */

#if defined(USE_HAL_OPAMP_MODULE) && (USE_HAL_OPAMP_MODULE == 1)
#include "stm32u5xx_hal_opamp.h"
#endif /* USE_HAL_OPAMP_MODULE == 1 */

#if defined(USE_HAL_PWR_MODULE) && (USE_HAL_PWR_MODULE == 1)
#include "stm32u5xx_hal_pwr.h"
#endif /* USE_HAL_PWR_MODULE == 1 */

#if defined(USE_HAL_RNG_MODULE) && (USE_HAL_RNG_MODULE == 1)
#include "stm32u5xx_hal_rng.h"
#endif /* USE_HAL_RNG_MODULE == 1 */

#if defined(USE_HAL_RTC_MODULE) && (USE_HAL_RTC_MODULE == 1)
#include "stm32u5xx_hal_rtc.h"
#endif /* USE_HAL_RTC_MODULE == 1 */

#if defined(USE_HAL_SAI_MODULE) && (USE_HAL_SAI_MODULE == 1)
#include "stm32u5xx_hal_sai.h"
#endif /* USE_HAL_SAI_MODULE == 1 */

#if defined(USE_HAL_SD_MODULE) && (USE_HAL_SD_MODULE == 1)
#include "stm32u5xx_hal_sd.h"
#endif /* USE_HAL_SD_MODULE == 1 */

#if defined(USE_HAL_SDIO_MODULE) && (USE_HAL_SDIO_MODULE == 1)
#include "stm32u5xx_hal_sdio.h"
#endif /* USE_HAL_SDIO_MODULE == 1 */

#if defined(USE_HAL_SMBUS_MODULE) && (USE_HAL_SMBUS_MODULE == 1)
#include "stm32u5xx_hal_smbus.h"
#endif /* USE_HAL_SMBUS_MODULE == 1 */

#if defined(USE_HAL_SPI_MODULE) && (USE_HAL_SPI_MODULE == 1)
#include "stm32u5xx_hal_spi.h"
#endif /* USE_HAL_SPI_MODULE == 1 */

#if defined(USE_HAL_TAMP_MODULE) && (USE_HAL_TAMP_MODULE == 1)
#include "stm32u5xx_hal_tamp.h"
#endif /* USE_HAL_TAMP_MODULE == 1 */

#if defined(USE_HAL_TIM_MODULE) && (USE_HAL_TIM_MODULE == 1)
#include "stm32u5xx_hal_tim.h"
#endif /* USE_HAL_TIM_MODULE == 1 */

#if defined(USE_HAL_UART_MODULE) && (USE_HAL_UART_MODULE == 1)
#include "stm32u5xx_hal_uart.h"
#endif /* USE_HAL_UART_MODULE == 1 */

#if defined(USE_HAL_USART_MODULE) && (USE_HAL_USART_MODULE == 1)
#include "stm32u5xx_hal_usart.h"
#endif /* USE_HAL_USART_MODULE == 1 */

#if defined(USE_HAL_SMARTCARD_MODULE) && (USE_HAL_SMARTCARD_MODULE == 1)
#include "stm32u5xx_hal_smartcard.h"
#endif /* USE_HAL_SMARTCARD_MODULE == 1 */

#if defined(USE_HAL_WWDG_MODULE) && (USE_HAL_WWDG_MODULE == 1)
#include "stm32u5xx_hal_wwdg.h"
#endif /* USE_HAL_WWDG_MODULE == 1 */

#if defined(USE_HAL_PCD_MODULE) && (USE_HAL_PCD_MODULE == 1)
#include "stm32u5xx_hal_pcd.h"
#endif /* USE_HAL_PCD_MODULE == 1 */

#if defined(USE_HAL_HCD_MODULE) && (USE_HAL_HCD_MODULE == 1)
#include "stm32u5xx_hal_hcd.h"
#endif /* USE_HAL_HCD_MODULE == 1 */

#if defined(USE_HAL_CORDIC_MODULE) && (USE_HAL_CORDIC_MODULE == 1)
#include "stm32u5xx_hal_cordic.h"
#endif /* USE_HAL_CORDIC_MODULE == 1 */

#if defined(USE_HAL_DCMI_MODULE) && (USE_HAL_DCMI_MODULE == 1)
#include "stm32u5xx_hal_dcmi.h"
#endif /* USE_HAL_DCMI_MODULE == 1 */

#if defined(USE_HAL_EXTI_MODULE) && (USE_HAL_EXTI_MODULE == 1)
#include "stm32u5xx_hal_exti.h"
#endif /* USE_HAL_EXTI_MODULE == 1 */

#if defined(USE_HAL_FDCAN_MODULE) && (USE_HAL_FDCAN_MODULE == 1)
#include "stm32u5xx_hal_fdcan.h"
#endif /* USE_HAL_FDCAN_MODULE == 1 */

#if defined(USE_HAL_FMAC_MODULE) && (USE_HAL_FMAC_MODULE == 1)
#include "stm32u5xx_hal_fmac.h"
#endif /* USE_HAL_FMAC_MODULE == 1 */

#if defined(USE_HAL_PSSI_MODULE) && (USE_HAL_PSSI_MODULE == 1)
#include "stm32u5xx_hal_pssi.h"
#endif /* USE_HAL_PSSI_MODULE == 1 */

#if defined(USE_HAL_RAMCFG_MODULE) && (USE_HAL_RAMCFG_MODULE == 1)
#include "stm32u5xx_hal_ramcfg.h"
#endif /* USE_HAL_RAMCFG_MODULE == 1 */

#if defined(USE_HAL_MDF_MODULE) && (USE_HAL_MDF_MODULE == 1)
#include "stm32u5xx_hal_mdf.h"
#endif /* USE_HAL_MDF_MODULE == 1 */

#if defined(USE_HAL_SYSCFG_MODULE) && (USE_HAL_SYSCFG_MODULE == 1)
#include "stm32u5xx_hal_syscfg.h"
#endif /* USE_HAL_SYSCFG_MODULE == 1 */

#if defined(USE_HAL_VREFBUF_MODULE) && (USE_HAL_VREFBUF_MODULE == 1)
#include "stm32u5xx_hal_vrefbuf.h"
#endif /* USE_HAL_VREFBUF_MODULE == 1 */

#if defined(USE_HAL_XSPI_MODULE) && (USE_HAL_XSPI_MODULE == 1)
#include "stm32u5xx_hal_xspi.h"
#endif /* USE_HAL_XSPI_MODULE == 1 */

#if defined(USE_HAL_GFXMMU_MODULE) && (USE_HAL_GFXMMU_MODULE == 1)
#include "stm32u5xx_hal_gfxmmu.h"
#endif /* USE_HAL_GFXMMU_MODULE == 1 */

#if defined(USE_HAL_LTDC_MODULE) && (USE_HAL_LTDC_MODULE == 1)
#include "stm32u5xx_hal_ltdc.h"
#endif /* USE_HAL_LTDC_MODULE == 1 */

#if defined(USE_HAL_UCPD_MODULE) && (USE_HAL_UCPD_MODULE == 1)
#include "stm32u5xx_hal_ucpd.h"
#endif /* USE_HAL_UCPD_MODULE == 1 */

#if defined(USE_HAL_GFXTIM_MODULE) && (USE_HAL_GFXTIM_MODULE == 1)
#include "stm32u5xx_hal_gfxtim.h"
#endif /* USE_HAL_GFXTIM_MODULE == 1 */

#if defined(USE_FULL_ASSERT)
#ifndef USE_ASSERT_DBG_PARAM
#define USE_ASSERT_DBG_PARAM
#endif /* !USE_ASSERT_DBG_PARAM */
#ifndef USE_ASSERT_DBG_STATE
#define USE_ASSERT_DBG_STATE
#endif /* !USE_ASSERT_DBG_STATE */
#endif /* USE_FULL_ASSERT */

#if defined(USE_ASSERT_DBG_PARAM) || defined(USE_ASSERT_DBG_STATE)
#include "stm32_assert.h"
#else
#define ASSERT_DBG_PARAM(expr) ((void) 0U)
#define ASSERT_DBG_STATE(__STATE__,__VAL__) ((void)0U)
#endif /* USE_ASSERT_DBG_PARAM || USE_ASSERT_DBG_STATE */

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* STM32_HAL_H */
