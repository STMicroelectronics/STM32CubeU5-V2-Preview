# Release Notes for **STM32CubeU5 HAL2 drivers**

Copyright © 2025 STMicroelectronics

<p align="center">
  <a href="https://www.st.com">
    <img src="_htmresc/st_logo_2020.png" alt="ST logo" />
  </a>
</p>

---

## Purpose

The STM32Cube HAL and LL, an STM32 abstraction layer embedded software, ensure maximized portability across STM32 portfolio.

The portable APIs layer provides a generic, multi-instanced and simple set of APIs to interact with the upper layer (application, libraries and stacks). It is composed of native and extended APIs set. It is directly built around a generic architecture and allows the build-upon layers, like the middleware layer, to implement its functions without knowing in-depth the used STM32 device. This improves the library code reusability and guarantees an easy portability on other devices and STM32 families.

The Low Layer (LL) drivers are part of the STM32Cube firmware HAL that provides a basic set of optimized and one-shot services. The Low layer drivers, contrary to the HAL ones are not fully portable across the STM32 families; the availability of some functions depends on the physical availability of the relative features on the product. The Low Layer (LL) drivers are designed to offer the following features:

- New set of inline functions for direct and atomic register access
- One-shot operations that can be used by the HAL drivers or from application level
- Full independence from HAL and standalone usage (without HAL drivers)
- Full features coverage of all the supported peripherals

---

## Update History

### V2.0.0-beta.1.1 / 04-July-2025

#### First Beta release

Beta public release supporting STM32U535 / STM32U545 / STM32U575 / STM32U585 / STM32U595xx / STM32U5A5xx / STM32U599xx / STM32U5A9xx devices.

For more information, see [STM32 HAL/LL drivers Documentation](https://dev.st.com/stm32cube-docs/stm32u5-hal2/2.0.0-beta.1.1/docs/drivers/stm32u5xx_drivers_documentation.html) which provides detailed description of the individual HAL2 Drivers, including How to Use, Use Cases, and API References.

---

### HAL/LL drivers status

| Component  | Code  |
|------------|-------|
| ADC        | HAL2  |
| ADF        | HAL1  |
| AES        | HAL2  |
| COMP       | HAL2  |
| CORDIC     | HAL2  |
| CORTEX     | HAL2  |
| CRC        | HAL2  |
| CRS        | HAL2  |
| DAC        | HAL2  |
| DBGMCU     | HAL2  |
| DCACHE     | HAL2  |
| DCMI       | HAL2  |
| DLYB       | HAL2  |
| DMA        | HAL2  |
| DMA2D      | HAL2  |
| DSI        | HAL1  |
| EXTI       | HAL2  |
| FDCAN      | HAL2  |
| FLASH      | HAL2  |
| FMAC       | HAL2  |
| FMC-SRAM   | HAL2  |
| FMC-NAND   | HAL1  |
| FMC-NOR    | HAL2  |
| GFXMMU     | HAL2  |
| GFXTIM     | HAL2  |
| GPIO       | HAL2  |
| GPU2D      | HAL2  |
| GTZC       | HAL2  |
| HASH       | HAL2  |
| I2C        | HAL2  |
| ICACHE     | HAL2  |
| IWDG       | HAL2  |
| JPEG       | HAL2  |
| LPTIM      | HAL2  |
| LTDC       | HAL2  |
| MDF        | HAL2  |
| MMC        | HAL2  |
| OPAMP      | HAL2  |
| OS         | HAL2  |
| OTFDEC     | HAL2  |
| PKA        | HAL2  |
| PSSI       | HAL2  |
| PWR        | HAL2  |
| Q          | HAL2  |
| RAMCFG     | HAL2  |
| RCC        | HAL2  |
| RNG        | HAL2  |
| RTC        | HAL2  |
| SAI        | HAL2  |
| SD         | HAL2  |
| SDIO       | HAL2  |
| SMARTCARD  | HAL2  |
| SMBUS      | HAL2  |
| SPI        | HAL2  |
| SYSCFG     | HAL2  |
| TAMP       | HAL2  |
| TIM        | HAL2  |
| TSC        | HAL2  |
| UART       | HAL2  |
| UCPD       | HAL2  |
| USART      | HAL2  |
| USB-D      | HAL2  |
| USB-H      | HAL2  |
| VREFBUF    | HAL2  |
| WWDG       | HAL2  |
| XSPI       | HAL2  |

---

## Known Limitations

- As an Beta release, it does not implement full features neither fully tested, it may contain bugs.
- A few drivers are not yet available in HAL2 format: DSI, FMC-NAND and MDF.

---

## Backward compatibility

- STM32CubeU5 HAL2 drivers brings major evolutions vs. STM32CubeU5 HAL1 which leads to API breaks.

---

## Additional Information

For complete documentation on STM32 Microcontrollers, visit: [www.st.com/stm32](http://www.st.com/stm32)
