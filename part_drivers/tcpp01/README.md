# __Board Parts: TCPP Part__

  ![Alt text](doc/st_logo.png "Title")

## __Summary__

Part TCPP01 provides APIs to drive the TCPPO1 through EXTI to detect type-C cable presence and ADC for VBUS sensing.

## __Description__

### Peripherals initialization:

Part TCPP01 assumes that the initialization of all needed peripherals (ADC, EXTI,  GPIO) is done by the main application. After the MCU IPs have been initialized, the selected resources can be assigned to the TCPP object. This is done in `tcpp01_io_init()`, which the user application must override.
That function is called by `tcpp01_at_init()`; the `dev_id` field of the `tcpp01_io_t` structure should be used to discriminate the resources to be assigned.

## __How to use it?__

To use the TCPP01 part API, the application should define the `tcpp01_obj_t` object and the `tcpp01_io_init()` function to assign hardware resources to it.
The link between the two is made by `tcpp01_init()`, which should be called after all the MCU peripherals have been initialized.

Once this is successfully done, all the other part APIs can be used freely.

## __Contributing__

STM32 customers and users who want to contribute to this component can follow instructions on [STMicroelectronics GitHub page]( https://github.com/STMicroelectronics)

## __Keywords__
STM32
BSP
Parts
TCPP01
USBPD

## __License__

Copyright (c) 2025 STMicroelectronics

This software is licensed under terms that can be found in the LICENSE file in the root directory of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.
