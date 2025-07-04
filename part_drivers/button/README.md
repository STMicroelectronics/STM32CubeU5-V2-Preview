# __Board Parts: Button__

<img src="doc/subbrand-stm32.svg" width="50"/>


## __Summary__

The Button part driver provide APIs to drive buttons and switches through a GPIO.


## __Description and Usage__

### Peripherals initialization:

The Button part driver assumes that the initialization of all needed peripherals (GPIO, optionally EXTI) is done by the main application.
After the MCU IPs have been initialized, the selected resources can be assigned to Button objects. This is done in `button_io_init()`, which the user application must override.
That function is called by `button_init()`; the `.id` field of the `button_obj_t` structure should be used to discriminate the resources to be assigned.

### GPIO flavor

The GPIO flavor drives a button through a simple GPIO (plus EXTI). Optionally, it implements software debounce.
Debounce support is enabled by default and can be disabled by defining `BUTTON_DEBOUNCE` to `0` in the project's build settings.
In addition, debounce can be tuned each Button object via the `.debounce_duration` field. Typically, setting that field to `0` effectively disables debounce for that object.

To use the Button GPIO part API, the application should define the `button_object_t` object and the `button_io_init()` function to assign HAL hardware resources (and debounce settings when relevant) to it.
The link between the two is made by `button_init()`, which should be called after all the MCU peripherals have been initialized.

In addition, after calling `button_init()`, the application should call `button_enableit()` to activate interrput-related functions.
This is especially relevant when debounce is enabled at the driver level (`BUTTON_DEBOUNCE != 0`), as the part driver is event-based in that configuration.

Once this is successfully done, all the other part APIs can be used freely.

## __Contributing__

STM32 customers and users who want to contribute to this component can follow instructions on the [STMicroelectronics GitHub page](https://github.com/STMicroelectronics)


## __License__

Copyright (c) 2025 STMicroelectronics.

This software is licensed under terms that can be found in the LICENSE file in the root directory
of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.
