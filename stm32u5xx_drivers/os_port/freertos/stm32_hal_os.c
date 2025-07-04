/**
  ******************************************************************************
  * @file    stm32_hal_os.c
  * @brief   STM32 HAL OS abstraction: implementation for FreeRTOS OS.
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

1. Create and delete a Semaphore:
  - To Create a new semaphore instance, use the HAL_OS_SemaphoreCreate() function.
    - The HAL_OS_SemaphoreCreate() API allows to:
      - create a binary semaphore using xSemaphoreCreateBinary() when configSUPPORT_DYNAMIC_ALLOCATION is equal to 1.
    - ensure that the semaphore instance is free.

  - To Delete a semaphore instance, use the HAL_OS_SemaphoreDelete() function.
    - The HAL_OS_SemaphoreCreate() API allows to delete the semaphore using vSemaphoreDelete() function when
      the the processor is not in interrupt mode.

2. Take and Release a Semaphore:
  - To Take a semaphore that have previously been created with a call to HAL_OS_SemaphoreCreate(),
    use the HAL_OS_SemaphoreTake() function.
    - The HAL_OS_SemaphoreTake() API allows to wait until a semaphore is free and take it or a timeout.

  - In case of HAL_OS_SemaphoreTake is called from a thread, it calls xSemaphoreTake() FreeRTOS function
    with the user given semaphore object and timeout.
    - In case of HAL_OS_SemaphoreTake frm an ISR, it calls xSemaphoreTakeFromISR() FreeRTOS function with the
      user given  semaphore object.
    - if the timeout is different from zero the HAL_OS_SemaphoreTake return HAL_OS_ERROR as the usage of a timeout
      within an ISR is forbidden.

  - To Release a semaphore, use the HAL_OS_SemaphoreRelease() function.
    - In case of HAL_OS_SemaphoreRelease is called from a thread, it calls xSemaphoreGive() FreeRTOS function with
      the user given semaphore object.
    - If it is called from an ISR, the HAL_OS_SemaphoreRelease calls xSemaphoreGiveFromISR() FreeRTOS function.

3. Create and delete the mutex:
  - To Create a new mutex instance, use the HAL_OS_MutexCreate() function that calls xSemaphoreCreateMutex()
    FreeRTOS function.

  - To Delete a mutex instance, use the HAL_OS_MutexDelete() function.
    - The HAL_OS_MutexDelete() API allows to delete the mutex using FreeRTOS function "vSemaphoreDelete".

4. Take and Release a mutex:
  - To Take a mutex have previously been created with a call to HAL_OS_MutexTake(), use the HAL_OS_MutexTake() function.
    - The HAL_OS_MutexTake() allows to obtain the mutex using FreeRTOS function "xSemaphoreTake".

  - To Release a mutex, use the HAL_OS_MutexRelease() function.
    - The HAL_OS_MutexRelease() allows to free the mutex using FreeRTOS function "xSemaphoreGive".

## Note
 - Mutex services are forbidden under ISR, HAL mutex APIs return HAL_OS_ERROR if called from an ISR.
 - The OS FreeRTOS Abstraction layer can be used only with the config configSUPPORT_DYNAMIC_ALLOCATION set to "1".

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
  * @brief  Create a new binary semaphore instance.
  * @param  p_sem         Pointer to a hal_os_semaphore_t structure.
  * @retval HAL_OS_OK     Semaphore instance created successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_SemaphoreCreate(hal_os_semaphore_t *p_sem)
{
#if (configSUPPORT_DYNAMIC_ALLOCATION == 1)
  SemaphoreHandle_t hsemaphore;
  hal_os_status_t status = HAL_OS_ERROR;

  hsemaphore = xSemaphoreCreateBinary();

  if (hsemaphore != NULL)
  {
    if (xSemaphoreGive(hsemaphore) != pdPASS)
    {
      /*If The semaphore not be given back once obtained, delete semaphore instance using FreeRTos function */
      vSemaphoreDelete(hsemaphore);
      hsemaphore = NULL;
      return status;
    }

    *p_sem = hsemaphore;
    status = HAL_OS_OK;
  }

  return status;
#else
  /* Only DYNAMIC_ALLOCATION is supported */
  STM32_UNUSED(p_sem);
  return HAL_OS_ERROR;
#endif /* configSUPPORT_DYNAMIC_ALLOCATION == 1 */
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
  SemaphoreHandle_t hsemaphore = (SemaphoreHandle_t) * p_sem;
  hal_os_status_t status = HAL_OS_ERROR;
  BaseType_t yield;

  if (hsemaphore != NULL)
  {
    if ((__get_IPSR() != 0U))
    {
      if (timeout_ms == 0U)
      {
        yield = pdFALSE;

        if (xSemaphoreTakeFromISR(hsemaphore, &yield) == pdPASS)
        {
          status = HAL_OS_OK;
          portYIELD_FROM_ISR(yield);
        }
      }
    }
    else
    {
      if (xSemaphoreTake(hsemaphore, (TickType_t)timeout_ms) == pdPASS)
      {
        status = HAL_OS_OK;
      }
    }
  }
  return status;
}

/**
  * @brief  Release the semaphore.
  * @param  p_sem         Pointer to a hal_os_semaphore_t structure.
  * @retval HAL_OS_OK     Semaphore released successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_SemaphoreRelease(hal_os_semaphore_t *p_sem)
{
  SemaphoreHandle_t hsemaphore = (SemaphoreHandle_t) * p_sem;
  hal_os_status_t status = HAL_OS_ERROR;
  BaseType_t yield;

  if (hsemaphore != NULL)
  {
    if ((__get_IPSR() != 0U))
    {
      yield = pdFALSE;

      if (xSemaphoreGiveFromISR(hsemaphore, &yield) == pdTRUE)
      {
        status = HAL_OS_OK;
        portYIELD_FROM_ISR(yield);
      }
    }
    else
    {
      if (xSemaphoreGive(hsemaphore) == pdPASS)
      {
        status = HAL_OS_OK;
      }
    }
  }

  return (status);
}

/**
  * @brief  Delete the semaphore.
  * @param  p_sem         Pointer to a hal_os_semaphore_t structure.
  * @retval HAL_OS_OK     Semaphore deleted successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_SemaphoreDelete(hal_os_semaphore_t *p_sem)
{
  SemaphoreHandle_t hsemaphore = (SemaphoreHandle_t) * p_sem;
  hal_os_status_t status = HAL_OS_ERROR;

  if ((!(__get_IPSR() != 0U)) && (hsemaphore != NULL))
  {
    vSemaphoreDelete(hsemaphore);
    hsemaphore = NULL;
    status = HAL_OS_OK;
  }

  return (status);
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
#if (configSUPPORT_DYNAMIC_ALLOCATION == 1)
  SemaphoreHandle_t hmutex;
  hal_os_status_t status = HAL_OS_ERROR;

  if (!(__get_IPSR() != 0U))
  {
    /* Mutex creation is possible in thread mode only not in interrupt mode */
    hmutex = xSemaphoreCreateMutex();

    if (hmutex != NULL)
    {
      *p_mutex = hmutex;
      status = HAL_OS_OK;
    }
  }
  return status;
#else
  /* Only DYNAMIC_ALLOCATION is supported */
  STM32_UNUSED(p_mutex);
  return HAL_OS_ERROR;
#endif /* configSUPPORT_DYNAMIC_ALLOCATION == 1 */
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
  SemaphoreHandle_t hmutex = (SemaphoreHandle_t) * p_mutex;
  hal_os_status_t status = HAL_OS_ERROR;

  if (hmutex != NULL)
  {
    if (!(__get_IPSR() != 0U))
    {
      /* Mutex can be taken in thread mode only not in interrupt mode */
      if (xSemaphoreTake(hmutex, (TickType_t)timeout_ms) == pdPASS)
      {
        status = HAL_OS_OK;
      }
    }
  }
  return status;
}

/**
  * @brief  Release the mutex.
  * @param  p_mutex       Pointer to a hal_os_mutex_t structure.
  * @retval HAL_OS_OK     Mutex released successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_MutexRelease(hal_os_mutex_t *p_mutex)
{
  SemaphoreHandle_t hmutex = (SemaphoreHandle_t) * p_mutex;
  hal_os_status_t status = HAL_OS_ERROR;

  if (hmutex != NULL)
  {
    if (!(__get_IPSR() != 0U))
    {
      /* Mutex can be released in thread mode only not in interrupt mode */
      if (xSemaphoreGive(hmutex) == pdPASS)
      {
        status = HAL_OS_OK;
      }
    }
  }
  return status;
}

/**
  * @brief  Delete the mutex.
  * @param  p_mutex   Pointer to a hal_os_mutex_t structure.
  * @retval HAL_OS_OK    Mutex was deleted successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_MutexDelete(hal_os_mutex_t *p_mutex)
{
  SemaphoreHandle_t hmutex = (SemaphoreHandle_t) * p_mutex;
  hal_os_status_t status = HAL_OS_ERROR;

  if ((!(__get_IPSR() != 0U)) && (hmutex != NULL))
  {
    /* Mutex can be deleted in thread mode only not in interrupt mode */
    vSemaphoreDelete(hmutex);
    hmutex = NULL;
    status = HAL_OS_OK;
  }
  return status;
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
