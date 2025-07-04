# __Utilities : SEQUENCER__

![Alt text](doc/subbrand-stm32.svg "Title")


## __Summary__

The sequencer is an utility to help the task scheduling inside a system without OS.


## __Description and Usage__

The sequencer utility has been designed as a simple alternative to using a real-time operating system for less complex application cases. However, it does not cover all the services provided by an operating system.

### __Description__:

The mains features of sequencer are :

__Task creation__: allow to initialize the task and render it callable by the internal scheduler of the sequencer.

__Task enable__: through a task or an interrupt, the task is enabled, and so could be executed by the scheduler.

__Task Pause/Resume__: allows to pause/Resume the task execution from scheduler point of view independent whether the task is enabled or not.
Idle Task: if the scheduler has not task to execute it call an optional hook function to manage entry in idle mode.

__Task execution__: call the function associated to the task, the scheduler is locked until function return.

__Sequencer__: embed a task scheduler which sequences the tasks execution and also allows the task to stop until an event reception.

### __Usage__:

the startup sequence could be split into 4 steps:

### Step 1: Sequencer initialization:

This step prepare the sequencer to have a clean startup environment. this done by calling `SEQ_Init()`.

### Step 2: Task initialization

Allow to register a task  by setting all the tasks callbacks. this is done by calling `SEQ_RegTask(TASK1, 0, Task1_func)`

* `TASK1`: ID of the task
* `Task1_func`: is the function pointer to the task function that will be executed.
* `0`: the priority of the task (lower value indicate high priority)

### Step 3: Task setting:

Call the function `SEQ_SetTask(TASK1)` to set the task `TASK1` within the sequencer.

### Step 4: Task execution:

Call `SEQ_Run(SEQ_DEFAULT)` to allow the sequencer to process all tasks.


## __Contributing__

STM32 customers and users who want to contribute to this component can follow instructions on the [STMicroelectronics GitHub page](https://github.com/STMicroelectronics)


## __License__

Copyright (c) 2024 STMicroelectronics.

This software is licensed under terms that can be found in the LICENSE file in the root directory
of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.
