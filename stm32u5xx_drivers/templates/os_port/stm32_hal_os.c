/**
  ******************************************************************************
  * @file    stm32_hal_os.c
  * @brief   STM32 HAL OS abstraction: implementation for MY OS.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "stm32_hal.h"

/** @addtogroup STM32_HAL_OS
  * @{
  */

/** @addtogroup OS
  * @{

# How to use the OS HAL module driver
The OS HAL driver can be used as follows:

1. Create a semaphore or mutex :
  - To Create a new semaphore instance, use the HAL_OS_SemaphoreCreate() function.
  - To Create a new mutex instance, use the HAL_OS_MutexCreate() function.
  - A semaphore or a mutex is a simple uint32 variable that is set in an atomic way.

2. Delete a semaphore or mutex :
  - To Delete a semaphore instance, use the HAL_OS_SemaphoreDelete() function.

  - To Delete a mutex instance, use the HAL_OS_MutexDelete() function.

3. Take the semaphore or mutex when the processor :
  - To Take a semaphore, use the HAL_OS_SemaphoreTake() function.

  - To Take a mutex, use HAL_OS_MutexTake() function that "behave" the same as HAL_OS_SemaphoreTake.

4. Release the semaphore or mutex :
  - To Release a semaphore, use the HAL_OS_SemaphoreRelease() function.

  - To Release a mutex, use the HAL_OS_MutexRelease() function that "behave" the same as HAL_OS_SemaphoreRelease().

## Configuration inside the OS driver

Config defines             | Description           | Default value   | Note
---------------------------| --------------------- | ----------------| --------------------------------------------
USE_HAL_MUTEX              | from hal_conf.h       | 0               | Allows HAL PPP drivers to enable HAL PPP
                           |                       |                 | acquire/release based on the HAL OS
  */
#if defined (USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
/* Private constants --------------------------------------------------------*/
/* Private types ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
/* Private functions --------------------------------------------------------*/
/* Exported types -----------------------------------------------------------*/
/* Exported functions -------------------------------------------------------*/
/** @addtogroup OS_Exported_Functions OS Exported Functions
  * @{
  */
/** @addtogroup OS_Exported_Functions_Group1 OS Semaphore functions
  * @{
This subsection provides a set of functions allowing to control access to shared resources using Semaphore:
- Call the function HAL_OS_SemaphoreCreate() to create a new semaphore instance.
- Call the function HAL_OS_SemaphoreTake() to to obtain a semaphore already created.
- Call the function HAL_OS_SemaphoreRelease() to release a semaphore.
- Call the function HAL_OS_SemaphoreDelete() to delete a semaphore.
  */

/**
  * @brief  Create a new semaphore instance.
  * @param  p_sem         Pointer to a hal_os_semaphore_t structure.
  * @retval HAL_OS_OK     Semaphore instance created successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_SemaphoreCreate(hal_os_semaphore_t *p_sem)
{
  return HAL_OS_ERROR;

}

/**
  * @brief  Take a semaphore that was created previously.
  * @param  p_sem         Pointer to a hal_os_semaphore_t structure.
  * @param  timeout_ms    The time to wait for the semaphore to become available in ms.
  * @retval HAL_OS_OK     Semaphore taken successfully.
  * @retval HAL_OS_ERROR  The timeout_ms expired without the semaphore becoming available.
  */
hal_os_status_t HAL_OS_SemaphoreTake(hal_os_semaphore_t *p_sem, uint32_t timeout_ms)
{
  return HAL_OS_ERROR;
}

/**
  * @brief  Release the semaphore.
  * @param  p_sem         Pointer to a hal_os_semaphore_t structure.
  * @retval HAL_OS_OK     Semaphore released successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_SemaphoreRelease(hal_os_semaphore_t *p_sem)
{
  return HAL_OS_ERROR;
}

/**
  * @brief  Delete the semaphore.
  * @param  p_sem         Pointer to a hal_os_semaphore_t structure.
  * @retval HAL_OS_OK     Semaphore deleted successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_SemaphoreDelete(hal_os_semaphore_t *p_sem)
{
  return HAL_OS_ERROR;
}

/**
  * @}
  */

/** @addtogroup OS_Exported_Functions_Group2 OS Mutex functions
  * @{
This subsection provides a set of functions allowing to control access to shared resources using Mutex:
- Call the function HAL_OS_MutexCreate() to create a mutex
- Call the function HAL_OS_MutexTake() to take a mutex
- Call the function HAL_OS_MutexRelease() to release a mutex
- Call the function HAL_OS_MutexDelete() to delete a mutex
  */

/**
  * @brief  Create a new mutex instance.
  * @param  p_mutex       Pointer to a hal_os_mutex_t structure.
  * @retval HAL_OS_OK     Mutex created successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_MutexCreate(hal_os_mutex_t *p_mutex)
{
  return HAL_OS_ERROR;

}

/**
  * @brief  Take a mutex that was created previously.
  * @param  p_mutex       Pointer to a hal_os_mutex_t structure.
  * @param  timeout_ms    The time to wait for the mutex to become available in ms.
  * @retval HAL_OS_OK     Semaphore taken successfully.
  * @retval HAL_OS_ERROR  The timeout_ms expired without the mutex becoming available.
  */
hal_os_status_t HAL_OS_MutexTake(hal_os_mutex_t *p_mutex, uint32_t timeout_ms)
{
  return HAL_OS_ERROR;
}

/**
  * @brief  Release the mutex.
  * @param  p_mutex       Pointer to a hal_os_mutex_t structure.
  * @retval HAL_OS_OK     Mutex released successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_MutexRelease(hal_os_mutex_t *p_mutex)
{
  return HAL_OS_ERROR;
}

/**
  * @brief  Delete the mutex.
  * @param  p_mutex   Pointer to a hal_os_mutex_t structure.
  * @retval HAL_OS_OK    Mutex deleted successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_MutexDelete(hal_os_mutex_t *p_mutex)
{
  return HAL_OS_ERROR;
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_MUTEX */

/**
  * @}
  */

/**
  * @}
  */
