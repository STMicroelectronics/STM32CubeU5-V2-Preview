.. meta::
    :description: This metadata is used to be referenced properly in st.com and in the search engines.
    :keywords: HAL migration, HAL2, concepts, breaking changes

.. _breaking_concepts_concept_N:

.. index:: HAL flash driver rework

Flash driver refactoring
************************

.. _breaking_concepts_concept_N1:

Rework the HAL Flash Driver APIs to use a handle object.
========================================================

On HAL1, the HAL FLASH driver is not built around a handle.
As a consequence, several global variables are used to handle the various programming
and erasing asynchronous processes. Additionally, due to the absence of the handle,
the register callback feature is not available on the HAL1 FLASH driver.

On HAL2, the HAL FLASH driver is reworked to use a handle that holds:

- The flash instance: making the driver architecture ready to handle an STM32 device with multiple FLASH instances.

- The driver context including the various parameters allowing the handling of the various programming and erasing asynchronous processes.

- The callback pointer with the capability for the user to register their own callback (which is not possible on HAL1).

- The last occurred error code.

- Several other useful context parameters.

.. list-table:: HAL FLASH Driver Comparison
   :header-rows: 1
   :widths: 50 50

   * - HAL1
     - HAL2
   * - ``stm32tnxx_hal_flash.h``

       .. code-block:: c

         typedef struct
         {
           HAL_LockTypeDef        Lock;
           uint32_t               ErrorCode;
           uint32_t               ProcedureOnGoing;

           uint32_t               Address;

           uint32_t               Bank;

           uint32_t               Page;

           uint32_t               NbPagesToErase;
         } FLASH_ProcessTypeDef;

         extern FLASH_ProcessTypeDef pFlash;

     - stm32tnxx_hal_flash.h

       .. code-block:: c

         /*!< HAL FLASH handle structure type */
         typedef struct hal_flash_handle_s hal_flash_handle_t;

         /*!< HAL FLASH handle structure definition */
         struct hal_flash_handle_s
         {
           hal_flash_t                       instance;
           volatile hal_flash_state_t        global_state;
           ..
           hal_flash_program_mode_t          programming_mode;
           uint32_t                          prog_data_addr;
           uint32_t                          prog_flash_addr;
           ..
           volatile uint32_t                 last_error_codes;
           ..
           hal_flash_program_cplt_cb_t       p_program_cplt_cb;
           hal_flash_erase_page_cplt_cb_t    p_erase_page_cplt_cb;
           ..
           hal_flash_error_cb_t              p_error_cb;
           hal_flash_ecc_error_cb_t          p_ecc_error_cb;
           ..
           const void                        *p_user_data;
         };
   * - stm32tnxx_hal_flash.c: a global variable is declared by the HAL FLASH driver itself.

       .. code-block:: c

         FLASH_ProcessTypeDef pFlash = {.Lock = HAL_UNLOCKED, \
                                        .ErrorCode = HAL_FLASH_ERROR_NONE, \
                                        .ProcedureOnGoing = 0U, \
                                        .Address = 0U, \
                                        .Bank = FLASH_BANK_1, \
                                        .Page = 0U, \
                                        .NbPagesToErase = 0U
                                       };

     - As per the other HAL PPP drivesr based on a handle, a variable of type hal_flash_handle_t should be declared in the user application and then used within HAL_FLASH_Init and the various HAL FLASH process APIs.


Please refer to the dedicated HAL FLASH migration guide page for full details.


____

.. _breaking_concepts_concept_N2:

Fully rework HAL Flash driver APIs.
====================================

The HAL FLASH driver is fully reworked in HAL2 with the following principles:

- HAL driver Split into 2 modules:

  - Module 1: ``stm32tnxx_hal_flash.h`` and ``stm32tnxx_hal_flash.c``:

    - Providing programming and erasing services.

    - Based on a handle. See also :ref:`breaking_concepts_concept_N1`.

  - Module 2: ``stm32tnxx_hal_flash_itf.h`` and ``stm32tnxx_hal_flash_itf.c``:

    - Providing option bytes setting programming services.

    - Providing control services, e.g., ``HAL_FLASH_ITF_Lock``, ``HAL_FLASH_ITF_SetLatency``, etc.

Additionally, a brand new LL FLASH driver is provided: ``stm32tnxx_ll_flash.h``.

Please refer to the dedicated HAL FLASH migration guide page for full details.




