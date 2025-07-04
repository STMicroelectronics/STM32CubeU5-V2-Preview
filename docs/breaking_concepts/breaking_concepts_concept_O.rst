
RTOS-aware HAL
**************

.. _breaking_concepts_concept_O2:

Provide RTOS-compatible acquire/release bus services for communication peripheral drivers.
=============================================================================================

Removing HAL1 ``lock`` mechanism
---------------------------------
In HAL1, a ``lock`` variable of type ``HAL_LockTypeDef`` is provided within the HAL PPP handle.

Example:

.. code-block:: c

    typedef struct
    {
      TIM_TypeDef *Instance;

      HAL_LockTypeDef Lock;
      ..
    } TIM_HandleTypeDef;

This variable aims to lock the given handle during a process. However, this method has several weaknesses,
especially in applications using an RTOS or when the lock needs to be extended during a sequence
of HAL API calls or processes, not just for a single process or action.

In HAL2, the ``lock`` is abandoned, the ``lock`` variable is removed from the handle, as well as the type ``HAL_LockTypeDef``.
Instead:

- A brand new HAL OS Abstraction Layer (OSAL) is provided.

- New ``HAL_PPP_AcquireBus`` and ``HAL_PPP_ReleaseBus`` functions are provided, allowing the acquisition and release of a HAL PPP handle to protect a full sequence.

Adding a new HAL2 HAL OS
------------------------

In HAL2, a brand new HAL OS Abstraction Layer (OSAL) is available.
This OSAL is designed to provide a unified interface for operating system services, ensuring that the HAL
can implement ``HAL_PPP_AcquireBus`` and ``HAL_PPP_ReleaseBus``,
allowing the acquisition and release of a HAL PPP handle for bus-like peripherals (I2C, SPI, UART, etc.).

The HAL OSAL is implemented through the ``stm32_hal_os.c`` and ``stm32_hal_os.h`` files. These files provide:

- **Semaphore Services**: Create, take, release, and delete semaphores. 
  These services are used in the ``HAL_PPP_AcquireBus`` and ``HAL_PPP_ReleaseBus`` APIs when the ``USE_HAL_MUTEX`` define is set to 1.

- **Mutex Services**: Create, take, release, and delete mutexes.

These services are crucial for managing access to shared resources in a multitasking environment.

The HAL OSAL can also be utilized by drivers' IO interfaces or any other application layer
as a simple OSAL wrapper to create, take, release, and delete semaphores and mutexes.

.. note::
   The HAL OS APIs, as well as the ``HAL_PPP_AcquireBus`` and ``HAL_PPP_ReleaseBus`` APIs, are provided
   under the compilation switch ``USE_HAL_MUTEX``, which should be set to ``1`` in the ``stm32tnxx_hal_conf.h`` file when needed.
   By default, ``USE_HAL_MUTEX`` is set to ``0``.

Implementations
~~~~~~~~~~~~~~~~

The ``stm32_hal_os.c/h`` files are provided with two implementations:

- Based on FreeRTOS.

- Based on a bare-metal implementation.

Additionally, ``stm32_hal_os.c/h`` are provided as templates, offering the required APIs with empty implementations.
This allows users to customize the HAL OSAL for their own operating system or implementation.

The HAL OSAL files are available here (example in the STM32Cube_SW_Package_U5 package):

.. code-block:: none

    STM32Cube_SW_Package_U5/
    ├── cmsis/
    ├── dfp/
    │   └── stm32u5xx/
    ├── hal/
    └── stm32u5xx/
        ├── hal/
        ├── ll/
        ├── os_port/
        │   ├── freertos
        │   │   ├── stm32_hal_os.h
        │   │   └── stm32_hal_os.c
        │   └── no_os
        │       ├── stm32_hal_os.h
        │       └── stm32_hal_os.c
        ├── templates/
        │   ├── common
        │   ├── timebases
        │   └── os_port
        │       ├── stm32_hal_os.h
        │       └── stm32_hal_os.c
        ├── timebases/
        └── utils/


HAL OSAL ``FreeRTOS`` based variant
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c

    /**
      ******************************************************************************
      * @file    stm32_hal_os.h
      * @author  MCD Application Team
      * @brief   Header file of STM32 HAL OS: implementation for FreeRTOS.
      ******************************************************************************
      */

    #ifndef STM32_HAL_OS
    #define STM32_HAL_OS

    #ifdef __cplusplus
    extern "C" {
    #endif

    #include "freertos.h"
    #include "semphr.h"

    #define HAL_OS_TIMEOUT_FOREVER portMAX_DELAY

    typedef enum
    {
      HAL_OS_OK      = 0x00,
      HAL_OS_ERROR   = 0x01
    } hal_os_status_t;

    typedef SemaphoreHandle_t hal_os_semaphore_t;
    typedef SemaphoreHandle_t hal_os_mutex_t;

    hal_os_status_t HAL_OS_SemaphoreCreate(hal_os_semaphore_t *p_sem);
    hal_os_status_t HAL_OS_SemaphoreTake(hal_os_semaphore_t *p_sem, uint32_t timeout);
    hal_os_status_t HAL_OS_SemaphoreRelease(hal_os_semaphore_t *p_sem);
    hal_os_status_t HAL_OS_SemaphoreDelete(hal_os_semaphore_t *p_sem);

    hal_os_status_t HAL_OS_MutexCreate(hal_os_mutex_t *p_mutex);
    hal_os_status_t HAL_OS_MutexTake(hal_os_mutex_t *p_mutex, uint32_t timeout);
    hal_os_status_t HAL_OS_MutexRelease(hal_os_mutex_t *p_mutex);
    hal_os_status_t HAL_OS_MutexDelete(hal_os_mutex_t *p_mutex);

    #ifdef __cplusplus
    }
    #endif
    #endif /* STM32_HAL_OS */

HAL OSAL bare-metal implementation variant
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In addition to the FreeRTOS variant, the HAL OS Abstraction Layer is provided with a NO_OS/bare-metal variant.
This version is tailored for ARM architectures, with specific implementations for ARM V7/V8 and ARM V6.

The NO_OS version uses atomic operations and critical sections to manage semaphores and mutexes,
ensuring safe and efficient operation in a bare-metal environment.

The ARM V7/V8 implementation utilizes exclusive load and store instructions (__LDREXW and __STREXW) for atomic operations,
while the ARM V6 implementation relies on critical sections to achieve atomicity.


.. code-block:: c

    /**
      ******************************************************************************
      * @file    stm32_hal_os.h
      * @author  MCD Application Team
      * @brief   Header file of STM32 HAL OS: implementation for NO OS.
      ******************************************************************************
      */

    #ifndef STM32_HAL_OS
    #define STM32_HAL_OS

    #ifdef __cplusplus
    extern "C" {
    #endif

    #include "stdint.h"

    #define HAL_OS_TIMEOUT_FOREVER 0xFFFFFFFF

    typedef enum
    {
      HAL_OS_OK      = 0x00,
      HAL_OS_ERROR   = 0x01
    } hal_os_status_t;

    typedef uint32_t hal_os_semaphore_t;
    typedef uint32_t hal_os_mutex_t;

    hal_os_status_t HAL_OS_SemaphoreCreate(hal_os_semaphore_t *p_sem);
    hal_os_status_t HAL_OS_SemaphoreTake(hal_os_semaphore_t *p_sem, uint32_t timeout);
    hal_os_status_t HAL_OS_SemaphoreRelease(hal_os_semaphore_t *p_sem);
    hal_os_status_t HAL_OS_SemaphoreDelete(hal_os_semaphore_t *p_sem);

    hal_os_status_t HAL_OS_MutexCreate(hal_os_mutex_t *p_mutex);
    hal_os_status_t HAL_OS_MutexTake(hal_os_mutex_t *p_mutex, uint32_t timeout);
    hal_os_status_t HAL_OS_MutexRelease(hal_os_mutex_t *p_mutex);
    hal_os_status_t HAL_OS_MutexDelete(hal_os_mutex_t *p_mutex);

    #ifdef __cplusplus
    }
    #endif
    #endif /* STM32_HAL_OS */


``HAL_PPP_AcquireBus`` and ``HAL_PPP_ReleaseBus`` 
-------------------------------------------------

High-level applicative layers such as BSP IO interfaces, middleware interfaces, and user applications require protection
for a sequence of HAL PPP calls against multi-threading.
This means the applicative module must ``acquire`` the HAL PPP resource, perform the necessary sequence
of HAL PPP API calls to ensure the needed applicative functionality, and then ``release`` the HAL PPP resource.

In OS-based applications, it is necessary to ``acquire`` the full HAL PPP handle to ensure an applicative sequence.
During the applicative sequence, the HAL PPP handle should be ``owned`` by a given task, and other tasks
should wait until the sequence is finished.
Any other task trying to initiate any HAL operation on the given HAL PPP handle should wait.

Example usage:

.. code-block:: c

    HAL_PPP_AcquireBus(hppp);

    HAL_PPP_Transmit(hppp, ...);
    HAL_PPP_Receive(hppp, ...);
    ...
    HAL_PPP_Transmit(hppp, ...);
    ...
    HAL_PPP_ReleaseBus(hppp);

    HAL_PPP_AcquireBus(hppp);

    HAL_PPP_Receive_IT(hppp, ...);
    ...
    /* wait for Rx Complete callback */
    ...
    HAL_PPP_ReleaseBus(hppp);

    HAL_PPP_AcquireBus(hppp);

    HAL_PPP_Transmit_IT(hppp, ...);
    ...
    /* wait for Tx Complete callback */
    ...
    HAL_PPP_ReleaseBus(hppp);

To meet these requirements, the HAL internal lock mechanism from HAL1 is removed in HAL2
and replaced by two APIs per HAL PPP driver: ``HAL_PPP_AcquireBus`` and ``HAL_PPP_ReleaseBus``.
These APIs are provided for bus peripherals such as I2C, USART, UART, SPI, SAI, I2S, PSSI, CAN/FDCAN, and I3C.

The HAL ``Acquire`` and ``Release`` APIs are based on a HAL OS Abstraction Layer.

HAL PPP handle update 
~~~~~~~~~~~~~~~~~~~~~~

Within the HAL PPP handle, a dedicated semaphore field using the HAL OSAL semaphore type is added.

.. code-block:: c

    typedef struct hal_ppp_handle_s hal_ppp_handle_t;

    struct hal_ppp_handle_s 
    {
      hal_ppp_t instance;
    
      ...
    #if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
      hal_os_semaphore_t semaphore;     
    #endif  /* USE_HAL_MUTEX */
    };

``HAL_PPP_Init`` and ``HAL_PPP_DeInit`` updates 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``HAL_PPP_Init`` function creates the corresponding OS semaphore by calling ``HAL_OS_SemaphoreCreate`` and stores the result in the ``handle->semaphore`` parameter. The semaphore creation is conditioned by the ``USE_HAL_MUTEX`` define.

.. code-block:: c

    hal_status_t HAL_PPP_Init(hal_ppp_handle_t *hppp, hal_ppp_t instance)
    {
      ASSERT_DBG_PARAM((hppp != NULL));

      ...
    #if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
      if (HAL_OS_SemaphoreCreate(&hppp->semaphore) != HAL_OS_OK)
      {
        return HAL_ERROR;       
      }
    #endif /* USE_HAL_MUTEX */
      ...
    }

The ``HAL_PPP_DeInit`` function frees the semaphore by calling ``HAL_OS_SemaphoreDelete``.

.. code-block:: c

    void HAL_PPP_DeInit(hal_ppp_handle_t *hppp)
    {
      ASSERT_DBG_PARAM((hppp != NULL));

      ...
    #if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
      (void)(HAL_OS_SemaphoreDelete(&hppp->semaphore) != HAL_OS_OK);
    #endif /* USE_HAL_MUTEX */
      ...
    }

``HAL_PPP_AcquireBus`` and ``HAL_PPP_ReleaseBus``  
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``HAL_PPP_AcquireBus`` function takes the semaphore by calling ``HAL_OS_SemaphoreTake``.

.. code-block:: c

    #if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
    hal_status_t HAL_PPP_AcquireBus(hal_ppp_handle_t *hppp, uint32_t timeout)
    {
      hal_status_t status = HAL_TIMEOUT;

      ASSERT_DBG_PARAM(hppp != NULL);

      if (HAL_OS_SemaphoreTake(&hppp->semaphore, timeout) == HAL_OS_OK)
      {
        status = HAL_OK;
      }

      return status;
    }
    #endif /* USE_HAL_MUTEX */

The ``HAL_PPP_ReleaseBus`` function releases the semaphore by calling ``HAL_OS_SemaphoreRelease``.

.. code-block:: c

    #if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
    hal_status_t HAL_PPP_ReleaseBus(hal_ppp_handle_t *hppp)
    {
      hal_status_t status = HAL_ERROR;

      ASSERT_DBG_PARAM(hppp != NULL);

      if (HAL_OS_SemaphoreRelease(&hppp->semaphore) == HAL_OS_OK)
      {
        status = HAL_OK;
      }

      return status;
    }
    #endif /* USE_HAL_MUTEX */

