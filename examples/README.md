![banner](../_htmresc/st_banner.png)

# Cube Software Examples

The Cube Software Examples demonstrate the STM32Cube embedded software and illustrate how to use the STM32 microcontrollers with the STM32Cube ecosystem.

With HAL2, the examples are updated to utilize the new API. 
Additionally, the structure of these examples has been improved to make them more modular and reusable, simplify the process of porting them to other STM32 series. 
Furthermore, the README files have been expanded to provide more detailed guidance on how to work with the examples and integrate the code into your own project. 

For more information, see [STM32Cube Software Examples](https://dev.st.com/stm32cube-docs/examples/1.0.0-beta.1.0/). 

## Usage

These examples are preconfigured IDE projects that run on the STM32 development boards.
For the preview, we are supporting the IDEs VS Code and IAR, with the developement board NUCLEO-U575ZI-Q supporting all the examples and the two boads B-U585I-IOT02A and NUCLEO-U545RE-Q supporting a subset of the examples.

The preview includes only a small subest of the examples that will be available with the final release.

To get started with the examples and VS code, follow the [Getting started guide](Getting_Started.md)

## Compatibility

The examples are compatible and configurable with the new version of STM32CubeMX, which will be available upon the official release of HAL2.

> [!IMPORTANT]
> The examples will be compatible and configurable with the new version of STM32CubeMX, which will be available upon the official release of HAL2.
> Therefore are they **not** configurable with the current STM32CubeMX version.

As a consequence, the examples available in this repository do not contain an STM32CubeMX project.

> [!CAUTION]
> These examples are not compatible with HAL1.
