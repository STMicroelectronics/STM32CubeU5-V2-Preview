# __Board Parts: LED__

<img src="doc/subbrand-stm32.svg" width="50"/>


## __Summary__

The LED part drivers provide APIs to drive LEDs through a GPIO, a timer (PWM), or an I/O expander component.


## __Description and Usage__

### GPIO flavor

This part driver is a simple wrapper around the HAL GPIO.
It relies on macros to link a LED to the HAL GPIO. Example for a LED named `LED0`:
```c
#define LED0_GPIO_PORT        HAL_GPIOE
#define LED0_PIN              HAL_GPIO_PIN_13
#define LED0_ACTIVE_STATE     HAL_GPIO_PIN_SET
#define LED0_INACTIVE_STATE   HAL_GPIO_PIN_RESET
```

The required macros may be generated or written manually in the software project.

The usage sequence for an application is the following:
1. GPIO initialization (`HAL_Init()`, `HAL_GPIO_Init(...)`, ...)
2. LED initialization (`led_init(LED0)`)
3. LED usage (`led_on(LED0)`, `led_off(LED0)`, ...)

### PWM flavor

This driver assumes that the initialization of all needed peripherals (GPIO, TIM) is done by the main application.
After the MCU IPs have been initialized, the selected resources can be assigned to LED PWM objects. This is done in `led_pwm_io_init()`, which the user application must override.
That function is called by `led_pwm_init()`; the `.id` field of the `led_pwm_t` structure must be used to discriminate the resources to be assigned.

To use the LED PWM part API, the application must define the `led_pwm_t` object and the `led_pwm_io_init()` function to assign GPIO and TIM resources to it. This code may be generated or written manually in the software project.
The link between the two is made by `led_pwm_init()`, which must be called after all the MCU peripherals have been initialized.

Once this is successfully done, all the other part APIs can be used freely.


### IOExpander flavor

This driver relies on an IOExpander part driver to function. The following part drivers are supported:
- MFXSTM32L152

After the IOExpander object has been initialized, the associated resources can be assigned to LED IOE objects. This is done in `led_ioe_io_init()`, which the user application must override.
That function is called by `led_ioe_init()`; the `.id` field of the `led_ioe_t` structure must be used to discriminate the resources to be assigned.

To use the LED IOE part APIs, the application must define the `led_ioe_t` object and the `led_ioe_io_init()` function to assign IO Expander resources to it.
The link between the two is made by `led_ioe_init()`, which must be called after all the MCU peripherals have been initialized.
In addition, the basic I/O functions must be overridden with a proper implementation that uses the right IOExpander in the right way:
- `void led_ioe_io_write_pin(led_ioe_t *p_led, uint32_t state);`
- `int32_t led_ioe_io_read_pin(led_ioe_t *p_led);`

This code may be generated or written manually in the software project.

Once this is successfully done, all the other part APIs can be used freely.


## __Contributing__

STM32 customers and users who want to contribute to this component can follow instructions on the [STMicroelectronics GitHub page](https://github.com/STMicroelectronics)


## __License__

Copyright (c) 2025 STMicroelectronics

This software is licensed under terms that can be found in the LICENSE file in the root directory
of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.
