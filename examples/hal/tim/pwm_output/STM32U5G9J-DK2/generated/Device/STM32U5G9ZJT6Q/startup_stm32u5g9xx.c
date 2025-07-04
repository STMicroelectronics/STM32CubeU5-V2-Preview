/**
  ******************************************************************************
  * @file    startup_stm32u5g9xx.c
  * @author  GPM Application Team
  * @brief   Startup File for STM32U5G9xx Device
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5g9xx.h"

/* External References -------------------------------------------------------*/
extern void SystemInit(void);
extern uint32_t __INITIAL_SP;
extern __NO_RETURN void __PROGRAM_START(void);

/* Private typedef -----------------------------------------------------------*/
typedef void(*VECTOR_TABLE_Type)(void);

/* Private function prototypes -----------------------------------------------*/
/* ISR headers */
void Default_IRQHandler(void) __attribute__((weak));
void Reset_Handler(void) __attribute__((weak));

/* Cortex-M interrupts  alias on the default handler */
void NMI_Handler(void) __attribute__((weak, alias("Default_IRQHandler")));
void HardFault_Handler(void) __attribute__((weak));
void MemManage_Handler(void) __attribute__((weak, alias("Default_IRQHandler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_IRQHandler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_IRQHandler")));
void SecureFault_Handler(void) __attribute__((weak, alias("Default_IRQHandler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_IRQHandler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_IRQHandler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_IRQHandler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_IRQHandler")));

/* Externals/Peripherals interrupts : alias on the default handler */
void WWDG_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void PVD_PVM_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void RTC_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void RTC_S_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TAMP_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void RAMCFG_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void FLASH_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void FLASH_S_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GTZC_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void RCC_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void RCC_S_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI0_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI2_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI3_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI4_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI5_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI6_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI7_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI8_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI9_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI10_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI11_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI12_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI13_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI14_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI15_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void IWDG_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void SAES_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH0_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH2_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH3_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH4_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH5_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH6_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH7_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void ADC1_2_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void DAC1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void FDCAN1_IT0_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void FDCAN1_IT1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM1_BRK_TERR_IERR_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM1_UPD_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM1_TRGI_COM_DIR_IDX_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM1_CC_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM2_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM3_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM4_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM5_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM6_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM7_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM8_BRK_TERR_IERR_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM8_UPD_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM8_TRGI_COM_DIR_IDX_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM8_CC_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C1_EV_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C1_ERR_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C2_EV_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C2_ERR_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void SPI2_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void USART1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void USART2_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void USART3_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void UART4_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void UART5_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void LPUART1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void LPTIM1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void LPTIM2_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM15_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM16_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM17_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void COMP_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void OTG_HS_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void CRS_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void FMC_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void OCTOSPI1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void PWR_S3WU_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void SDMMC1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void SDMMC2_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH8_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH9_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH10_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH11_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH12_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH13_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH14_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH15_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C3_EV_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C3_ERR_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void SAI1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void SAI2_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void TSC_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void AES_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void RNG_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void FPU_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void HASH_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void PKA_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void LPTIM3_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void SPI3_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C4_ERR_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C4_EV_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void MDF1_FLT0_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void MDF1_FLT1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void MDF1_FLT2_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void MDF1_FLT3_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void UCPD1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void ICACHE_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void OTFDEC1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void OTFDEC2_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void LPTIM4_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void DCACHE1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void ADF1_FLT0_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void ADC4_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void LPDMA1_CH0_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void LPDMA1_CH1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void LPDMA1_CH2_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void LPDMA1_CH3_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void DMA2D_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void DCMI_PSSI_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void OCTOSPI2_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void MDF1_FLT4_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void MDF1_FLT5_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void CORDIC_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void FMAC_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void LSECSSD_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void USART6_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C5_ERR_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C5_EV_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C6_ERR_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C6_EV_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void HSPI1_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPU2D_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GPU2D_ERR_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GFXMMU_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void LTDC_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void LTDC_ERR_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void DSI_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void DCACHE2_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void GFXTIM_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));
void JPEG_IRQHandler(void) __attribute__((weak, alias("Default_IRQHandler")));

/* Legacy defines */
#define GPDMA1_Channel0_IRQHandler GPDMA1_CH0_IRQHandler
#define GPDMA1_Channel1_IRQHandler GPDMA1_CH1_IRQHandler
#define GPDMA1_Channel2_IRQHandler GPDMA1_CH2_IRQHandler
#define GPDMA1_Channel3_IRQHandler GPDMA1_CH3_IRQHandler
#define GPDMA1_Channel4_IRQHandler GPDMA1_CH4_IRQHandler
#define GPDMA1_Channel5_IRQHandler GPDMA1_CH5_IRQHandler
#define GPDMA1_Channel6_IRQHandler GPDMA1_CH6_IRQHandler
#define GPDMA1_Channel7_IRQHandler GPDMA1_CH7_IRQHandler
#define GPDMA1_Channel8_IRQHandler GPDMA1_CH8_IRQHandler
#define GPDMA1_Channel9_IRQHandler GPDMA1_CH9_IRQHandler
#define GPDMA1_Channel10_IRQHandler GPDMA1_CH10_IRQHandler
#define GPDMA1_Channel11_IRQHandler GPDMA1_CH11_IRQHandler
#define GPDMA1_Channel12_IRQHandler GPDMA1_CH12_IRQHandler
#define GPDMA1_Channel13_IRQHandler GPDMA1_CH13_IRQHandler
#define GPDMA1_Channel14_IRQHandler GPDMA1_CH14_IRQHandler
#define GPDMA1_Channel15_IRQHandler GPDMA1_CH15_IRQHandler
#define LPDMA1_Channel0_IRQHandler LPDMA1_CH0_IRQHandler
#define LPDMA1_Channel1_IRQHandler LPDMA1_CH1_IRQHandler
#define LPDMA1_Channel2_IRQHandler LPDMA1_CH2_IRQHandler
#define LPDMA1_Channel3_IRQHandler LPDMA1_CH3_IRQHandler

/* Private variables ---------------------------------------------------------*/
/**
  Vector table
  */
extern const VECTOR_TABLE_Type __VECTOR_TABLE[];
const VECTOR_TABLE_Type __VECTOR_TABLE[] __VECTOR_TABLE_ATTRIBUTE =
{
  (VECTOR_TABLE_Type)(&__INITIAL_SP),/* The initial stack pointer */
  Reset_Handler,
  NMI_Handler,
  HardFault_Handler,
  MemManage_Handler,
  BusFault_Handler,
  UsageFault_Handler,
  SecureFault_Handler,
  0,
  0,
  0,
  SVC_Handler,
  DebugMon_Handler,
  0,
  PendSV_Handler,
  SysTick_Handler,
  WWDG_IRQHandler,
  PVD_PVM_IRQHandler,
  RTC_IRQHandler,
  RTC_S_IRQHandler,
  TAMP_IRQHandler,
  RAMCFG_IRQHandler,
  FLASH_IRQHandler,
  FLASH_S_IRQHandler,
  GTZC_IRQHandler,
  RCC_IRQHandler,
  RCC_S_IRQHandler,
  EXTI0_IRQHandler,
  EXTI1_IRQHandler,
  EXTI2_IRQHandler,
  EXTI3_IRQHandler,
  EXTI4_IRQHandler,
  EXTI5_IRQHandler,
  EXTI6_IRQHandler,
  EXTI7_IRQHandler,
  EXTI8_IRQHandler,
  EXTI9_IRQHandler,
  EXTI10_IRQHandler,
  EXTI11_IRQHandler,
  EXTI12_IRQHandler,
  EXTI13_IRQHandler,
  EXTI14_IRQHandler,
  EXTI15_IRQHandler,
  IWDG_IRQHandler,
  SAES_IRQHandler,
  GPDMA1_CH0_IRQHandler,
  GPDMA1_CH1_IRQHandler,
  GPDMA1_CH2_IRQHandler,
  GPDMA1_CH3_IRQHandler,
  GPDMA1_CH4_IRQHandler,
  GPDMA1_CH5_IRQHandler,
  GPDMA1_CH6_IRQHandler,
  GPDMA1_CH7_IRQHandler,
  ADC1_2_IRQHandler,
  DAC1_IRQHandler,
  FDCAN1_IT0_IRQHandler,
  FDCAN1_IT1_IRQHandler,
  TIM1_BRK_TERR_IERR_IRQHandler,
  TIM1_UPD_IRQHandler,
  TIM1_TRGI_COM_DIR_IDX_IRQHandler,
  TIM1_CC_IRQHandler,
  TIM2_IRQHandler,
  TIM3_IRQHandler,
  TIM4_IRQHandler,
  TIM5_IRQHandler,
  TIM6_IRQHandler,
  TIM7_IRQHandler,
  TIM8_BRK_TERR_IERR_IRQHandler,
  TIM8_UPD_IRQHandler,
  TIM8_TRGI_COM_DIR_IDX_IRQHandler,
  TIM8_CC_IRQHandler,
  I2C1_EV_IRQHandler,
  I2C1_ERR_IRQHandler,
  I2C2_EV_IRQHandler,
  I2C2_ERR_IRQHandler,
  SPI1_IRQHandler,
  SPI2_IRQHandler,
  USART1_IRQHandler,
  USART2_IRQHandler,
  USART3_IRQHandler,
  UART4_IRQHandler,
  UART5_IRQHandler,
  LPUART1_IRQHandler,
  LPTIM1_IRQHandler,
  LPTIM2_IRQHandler,
  TIM15_IRQHandler,
  TIM16_IRQHandler,
  TIM17_IRQHandler,
  COMP_IRQHandler,
  OTG_HS_IRQHandler,
  CRS_IRQHandler,
  FMC_IRQHandler,
  OCTOSPI1_IRQHandler,
  PWR_S3WU_IRQHandler,
  SDMMC1_IRQHandler,
  SDMMC2_IRQHandler,
  GPDMA1_CH8_IRQHandler,
  GPDMA1_CH9_IRQHandler,
  GPDMA1_CH10_IRQHandler,
  GPDMA1_CH11_IRQHandler,
  GPDMA1_CH12_IRQHandler,
  GPDMA1_CH13_IRQHandler,
  GPDMA1_CH14_IRQHandler,
  GPDMA1_CH15_IRQHandler,
  I2C3_EV_IRQHandler,
  I2C3_ERR_IRQHandler,
  SAI1_IRQHandler,
  SAI2_IRQHandler,
  TSC_IRQHandler,
  AES_IRQHandler,
  RNG_IRQHandler,
  FPU_IRQHandler,
  HASH_IRQHandler,
  PKA_IRQHandler,
  LPTIM3_IRQHandler,
  SPI3_IRQHandler,
  I2C4_ERR_IRQHandler,
  I2C4_EV_IRQHandler,
  MDF1_FLT0_IRQHandler,
  MDF1_FLT1_IRQHandler,
  MDF1_FLT2_IRQHandler,
  MDF1_FLT3_IRQHandler,
  UCPD1_IRQHandler,
  ICACHE_IRQHandler,
  OTFDEC1_IRQHandler,
  OTFDEC2_IRQHandler,
  LPTIM4_IRQHandler,
  DCACHE1_IRQHandler,
  ADF1_FLT0_IRQHandler,
  ADC4_IRQHandler,
  LPDMA1_CH0_IRQHandler,
  LPDMA1_CH1_IRQHandler,
  LPDMA1_CH2_IRQHandler,
  LPDMA1_CH3_IRQHandler,
  DMA2D_IRQHandler,
  DCMI_PSSI_IRQHandler,
  OCTOSPI2_IRQHandler,
  MDF1_FLT4_IRQHandler,
  MDF1_FLT5_IRQHandler,
  CORDIC_IRQHandler,
  FMAC_IRQHandler,
  LSECSSD_IRQHandler,
  USART6_IRQHandler,
  I2C5_ERR_IRQHandler,
  I2C5_EV_IRQHandler,
  I2C6_ERR_IRQHandler,
  I2C6_EV_IRQHandler,
  HSPI1_IRQHandler,
  GPU2D_IRQHandler,
  GPU2D_ERR_IRQHandler,
  GFXMMU_IRQHandler,
  LTDC_IRQHandler,
  LTDC_ERR_IRQHandler,
  DSI_IRQHandler,
  DCACHE2_IRQHandler,
  GFXTIM_IRQHandler,
  JPEG_IRQHandler
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function is the Reset Handler called on controller reset
  * @param  None
  * @retval None
  */
__WEAK __NO_RETURN void Reset_Handler(void)
{
  SystemInit();         /* CMSIS System Initialization */
  __PROGRAM_START();    /* Enter PreMain (C library entry point) */
}


/**
  * @brief  Hard Fault Handler
  * @param  None
  * @retval None
  */
__WEAK void HardFault_Handler(void)
{
  while (1);
}

/**
  * @brief  This function is the default IRQ handler
  *         when the IRQ line is not used by the application
  * @param  None
  * @retval None
  */
__WEAK void Default_IRQHandler(void)
{
  while (1);
}
