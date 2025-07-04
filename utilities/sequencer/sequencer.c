/**
  **********************************************************************************************************************
  * @file    sequencer.c
  * @author  MCD Application Team
  * @brief   Simple sequencer implementation
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2019-2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "sequencer.h"

/** @addtogroup SEQUENCER
  * @{
The sequencer utility has been designed as a simple alternative to using a real-time operating system for less complex
application cases. However, it does not cover all the services provided by an operating system. For instance, this
software solution does not offer a preemption mechanism, which must be considered in the application design.
We suggest using reentrant functions based on state machines instead of tasks that could potentially freeze the system.
# Main features
The main features of sequencers are described below:
  - Task creation: allow to initialize the task and render it callable by the internal scheduler of the sequencer.
  - Task enable: through a task or an interrupt, the task is enabled, and so could be executed by the scheduler.
  - Task Pause/Resume: allows to pause/Resume the task execution from scheduler point of view independent whether the
    task is enabled or not.
  - Idle Task: if the scheduler has not task to execute it call an optional hook function to manage entry in idle mode.
  - Task execution: call the function associated to the task, the scheduler is locked until function return.
  - Sequencer: embed a task scheduler which sequences the tasks execution and also allows the task to stop until an
  event reception.
  */

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/** @defgroup SEQUENCER_Private_type SEQUENCER private type
  *  @{
  */

/**
  * @brief structure used to manage task scheduling
  */
typedef struct
{
  uint32_t priority;    /*!<bit field of the enabled task.          */
  uint32_t round_robin; /*!<mask on the allowed task to be running. */
} seq_priority_t;

/**
  * @}
  */

/* Private defines ---------------------------------------------------------------------------------------------------*/

/** @defgroup SEQUENCER_Private_define SEQUENCER private defines
  *  @{
  */

/**
  * @brief define to represent no task running
  */
#define SEQ_NOTASKRUNNING       (0xFFFFFFFFU)

/**
  * @brief define to represent no bit set inside uint32_t mapping
  */
#define SEQ_NO_BIT_SET     (0U)

/**
  * @brief define to represent all bits set inside uint32_t mapping
  */
#define SEQ_ALL_BIT_SET    (~0U)


#if SEQ_CONF_TASK_NBR > 32
#error "SEQ_CONF_TASK_NBR must be less than or equal to 32"
#endif /* SEQ_CONF_TASK_NBR */

/**
  * @}
  */

/* Private variables -------------------------------------------------------------------------------------------------*/

/** @defgroup SEQUENCER_Private_variable SEQUENCER private variables
  *  @{
  */

/**
  * @brief task set.
  */
static volatile seq_bm_t TaskSet;

/**
  * @brief task mask.
  */
static volatile seq_bm_t TaskMask = SEQ_ALL_BIT_SET;

/**
  * @brief super mask.
  */
static seq_bm_t SuperMask = SEQ_ALL_BIT_SET;

/**
  * @brief evt set mask.
  */
static volatile seq_bm_t EvtSet = SEQ_NO_BIT_SET;

/**
  * @brief evt expected mask.
  */
static volatile seq_bm_t EvtWaited = SEQ_NO_BIT_SET;

/**
  * @brief current task id.
  */
static uint32_t CurrentTaskIdx = 0U;

/**
  * @brief task function registered.
  */
static void (*TaskCb[SEQ_CONF_TASK_NBR])(void);

/**
  * @brief task prio management.
  */
static volatile seq_priority_t TaskPrio[SEQ_CONF_PRIO_NBR];

/**
  * @brief List of the cleared tasks.
  */
static seq_bm_t  TaskClearList = 0;

/**
  * @}
  */

/* Private function prototypes ---------------------------------------------------------------------------------------*/
/** @defgroup SEQUENCER_Private_function SEQUENCER private functions
  *  @{
  */
uint8_t SEQ_BitPosition(uint32_t value);

/**
  * @}
  */

/* Functions Definition ----------------------------------------------------------------------------------------------*/

/** @addtogroup SEQUENCER_Exported_function SEQUENCER exported functions
  *  @{
  */

/** @addtogroup SEQUENCER_Exported_function_G1 Initialization and DeInitialization functions
  * @{
  */

/**
  * @brief  This function initializes the sequencer resources.
  *
  * @note   It must not be called from an ISR.
  *
  */
void SEQ_Init(void)
{
  TaskSet = SEQ_NO_BIT_SET;
  TaskMask = SEQ_ALL_BIT_SET;
  SuperMask = SEQ_ALL_BIT_SET;
  EvtSet = SEQ_NO_BIT_SET;
  EvtWaited = SEQ_NO_BIT_SET;
  CurrentTaskIdx = 0U;
  (void)SEQ_MEMSET8((uint8_t *)TaskCb, 0, sizeof(TaskCb));
  for (uint32_t index = 0; index < SEQ_CONF_PRIO_NBR; index++)
  {
    TaskPrio[index].priority = 0;
    TaskPrio[index].round_robin = 0;
  }
  SEQ_INIT_CRITICAL_SECTION();
  TaskClearList = 0;
}

/**
  * @brief  This function un-initializes the sequencer resources.
  *
  * @note   It must not be called from an ISR
  *
  */
void SEQ_DeInit(void)
{
}
/**
  * @}
  */

/** @addtogroup SEQUENCER_Exported_function_G2 Idle Task functions
  * @{
  */

/**
  * @brief This function is called by the sequencer in critical section (PRIMASK bit) when
  *          - there are no more tasks to be executed
  *          AND
  *          - there are no pending event or the pending event is still not set
  * @note  The application must enter low power mode in this function
  *        When this function is not implemented by the application, the sequencer keeps running a while loop (RUN MODE)
  *        It must be called only by the sequencer.
  *
  */
__WEAK void SEQ_Idle(void)
{
  /*
   * Unless specified by the application, there is nothing to be done
   */
  return;
}

/**
  * @brief This function is called by the sequencer outside critical section just before calling SEQ_Idle( )
  *        SEQ_PreIdle() is considered as the last task executed before calling SEQ_Idle( )
  *        In case a task or an event is set from an interrupt handler just after SEQ_PreIdle() is called,
  *        SEQ_Idle() will not be called.
  *
  * @note  It must be called only by the sequencer.
  *
  */
__WEAK void SEQ_PreIdle(void)
{
  /*
   * Unless specified by the application, there is nothing to be done
   */
  return;
}

/**
  * @brief This function is called by the sequencer outside critical section either
  *        - after calling SEQ_Idle( )
  *        OR
  *        - after calling SEQ_PreIdle( ) without call to SEQ_Idle() due to an incoming task set or event
  *          requested after SEQ_PreIdle() has been called.
  *
  * @note  SEQ_PostIdle() is always called if SEQ_PreIdle() has been called and never called otherwise.
  *        It must be called only by the sequencer.
  *
  */
__WEAK void SEQ_PostIdle(void)
{
  /*
   * Unless specified by the application, there is nothing to be done
   */
  return;
}
/**
  * @}
  */

/** @addtogroup SEQUENCER_Exported_function_G3 Scheduler functions
  * @{
 */

/**
  * @brief This function requests the sequencer to execute all pending tasks using round robin mechanism.
  *        When no task are pending, it calls SEQ_Idle();
  *        This function must be called in a while loop in the application
  *
  * @param mask_bm list of task (bit mapping) that is be kept in the sequencer list.
  *
  * @note  It must not be called from an ISR.
  * @note  The construction of the task must take into account the fact that there is no counting / protection
  *        on the activation of the task. Thus, when the task is running, it must perform all the operations
  *        in progress programmed before its call or manage a reprogramming of the task.
  * This function can be nested.
  * That is the reason why many variables that are used only in that function are declared static.
  * @note: These variables could have been declared static in the function.
  *
  */
void SEQ_Run(seq_bm_t mask_bm)
{
  uint32_t counter;
  seq_bm_t current_task_set;
  seq_bm_t super_mask_backup;
  seq_bm_t local_taskset;
  seq_bm_t local_evtset;
  seq_bm_t local_taskmask;
  seq_bm_t local_evtwaited;
  uint32_t round_robin[SEQ_CONF_PRIO_NBR];
  seq_bm_t task_starving_list;

  /*
   * When this function is nested, the mask to be applied cannot be larger than the first call
   * The mask is always getting smaller and smaller
   * A copy is made of the mask set by SEQ_Run() in case it is called again in the task
   */
  super_mask_backup = SuperMask;
  SuperMask &= mask_bm;

  /*
   * There are two independent mask to check:
   * TaskMask that comes from SEQ_PauseTask() / SEQ_ResumeTask
   * SuperMask that comes from SEQ_Run
   * If the waited event is there, exit from  SEQ_Run() to return to the
   * waiting task
   */
  local_taskset = TaskSet;
  local_evtset = EvtSet;
  local_taskmask = TaskMask;
  local_evtwaited = EvtWaited;
  while (((local_taskset & local_taskmask & SuperMask) != 0U) && ((local_evtset & local_evtwaited) == 0U))
  {
    counter = 0U;
    /*
     * When a flag is set, the associated bit is set in TaskPrio[counter].priority mask depending
     * on the priority parameter given from SEQ_SetTask()
     * The while loop is looking for a flag set from the highest priority mask to the lower
     */
    while ((TaskPrio[counter].priority & local_taskmask & SuperMask) == 0U)
    {
      counter++;
    }

    current_task_set = TaskPrio[counter].priority & local_taskmask & SuperMask;

    /*
     * The round_robin register is a mask of allowed flags to be evaluated.
     * The concept is to make sure that on each round on SEQ_Run(), if two same flags are always set,
     * the sequencer does not run always only the first one.
     * When a task has been executed, The flag is removed from the round_robin mask.
     * If on the next SEQ_RUN(), the two same flags are set again, the round_robin mask will
     * mask out the first flag so that the second one can be executed.
     * Note that the first flag is not removed from the list of pending task but just masked by
     * the round_robin mask
     *
     * In the check below, the round_robin mask is reinitialize in case all pending
     * tasks haven been executed at least once
     */
    if ((TaskPrio[counter].round_robin & current_task_set) == 0U)
    {
      TaskPrio[counter].round_robin = SEQ_ALL_BIT_SET;
    }

    /*
     * Compute the Stack Starving List
     * This is the list of the task that have been set at least once minus one that have been cleared ar least once
     */
    task_starving_list = TaskSet;

    /*
     * Due to the concept of TaskPrio[counter].round_robin and TaskClearList, it could be that at some points in time,
     * (when using SEQ_WaitEvt()), that there is a situation where at the same time, a bit is set in
     * TaskPrio[counter].round_robin and reset in TaskClearList and another bit is set in TaskClearList and reset in
     * TaskPrio[counter].round_robin.
     * Such situation must not happen when evaluating task_starving_list
     * At any time, there must not be any bit reset in TaskPrio[counter].round_robin and reset in TaskClearList
     * It is correct with regard to the Sequencer Architecture to set in TaskClearList all tasks that are said to be
     * executed from TaskPrio[counter].round_robin.
     * This synchronizes both information before calculating the CurrentTaskIdx
     */
    TaskClearList |= (~TaskPrio[counter].round_robin);

    task_starving_list &= (~TaskClearList);

    /*
     * Consider first the starving list and update current_task_set accordingly
     */
    if ((task_starving_list & current_task_set) != 0U)
    {
      current_task_set = (task_starving_list & current_task_set);
    }
    else
    {
      /* nothing to go */
    }

    /*
     * Reinitialize the Starving List if required
     */
    if (task_starving_list == 0U)
    {
      TaskClearList = 0;
    }

    /*
     * Read the flag index of the task to be executed
     * Once the index is read, the associated task will be executed even though a higher priority stack is requested
     * before task execution.
     */
    CurrentTaskIdx = (SEQ_BitPosition(current_task_set & TaskPrio[counter].round_robin));

    SEQ_ENTER_CRITICAL_SECTION();
    /* remove from the list or pending task the one that has been selected to be executed */
    TaskSet &= ~(1U << CurrentTaskIdx);
    /* remove from all priority mask the task that has been selected to be executed */
    for (counter = SEQ_CONF_PRIO_NBR; counter != 0U; counter--)
    {
      TaskPrio[counter - 1U].priority &= ~(1U << CurrentTaskIdx);
    }
    SEQ_EXIT_CRITICAL_SECTION();

    SEQ_PreTask(CurrentTaskIdx);

    /*
     * Check that function exists before calling it
     */
    if ((CurrentTaskIdx < SEQ_CONF_TASK_NBR) && (TaskCb[CurrentTaskIdx] != NULL))
    {
      /*
       * save the round-robin value to take into account the operation done in SEQ_WaitEvt
       */
      for (uint32_t index = 0; index < SEQ_CONF_PRIO_NBR; index++)
      {
        TaskPrio[index].round_robin &= ~(1UL << CurrentTaskIdx);
        round_robin[index] = TaskPrio[index].round_robin;
      }

      /* Execute the task */
      TaskCb[CurrentTaskIdx]();

      /*
       * restore the round-robin context
       */
      for (uint32_t index = 0; index < SEQ_CONF_PRIO_NBR; index++)
      {
        TaskPrio[index].round_robin &= round_robin[index];
      }

      SEQ_PostTask(CurrentTaskIdx);

      local_taskset = TaskSet;
      local_evtset = EvtSet;
      local_taskmask = TaskMask;
      local_evtwaited = EvtWaited;

      /*
       * Update the two list for next round
       */
      TaskClearList |= (uint32_t)(1U) << CurrentTaskIdx;
    }
    else
    {
      /*
       * must never occurs, it means there is a warning in the system
       */
      SEQ_CatchWarning(SEQ_WARNING_INVALIDTASKID);
    }
  }

  /* the set of CurrentTaskIdx to no task running allows to call WaitEvt in the Pre/Post idle context */
  CurrentTaskIdx = SEQ_NOTASKRUNNING;
  /* if a waited event is present, ignore the IDLE sequence */
  if ((local_evtset & EvtWaited) == 0U)
  {
    SEQ_PreIdle();

    SEQ_ENTER_CRITICAL_SECTION_IDLE();
    local_taskset = TaskSet;
    local_evtset = EvtSet;
    local_taskmask = TaskMask;
    if ((local_taskset & local_taskmask & SuperMask) == 0U)
    {
      if ((local_evtset & EvtWaited) == 0U)
      {
        SEQ_Idle();
      }
    }
    SEQ_EXIT_CRITICAL_SECTION_IDLE();

    SEQ_PostIdle();
  }

  /* restore the mask from SEQ_Run() */
  SuperMask = super_mask_backup;

  return;
}

/**
  * @}
  */

/** @addtogroup SEQUENCER_Exported_function_G4 Task Creation functions
  * @{
  */
/**
  * @brief This function registers a task in the sequencer.
  *
  * @param task_id_bm The Id of the task, this parameter must be a value of the enumeration @ref seq_task_id_t
  * @param flags flags are reserved parameter for future use
  * @param task Reference of the function to be executed
  *
  * @note  It can be called from an ISR.
  *
  */
void SEQ_RegTask(seq_task_id_t task_id_bm, uint32_t flags, void (*task)(void))
{
  (void)flags;
  SEQ_ENTER_CRITICAL_SECTION();
  uint32_t position = SEQ_BitPosition((uint32_t)task_id_bm);
  if (position < SEQ_CONF_TASK_NBR)
  {
    TaskCb[position] = task;
  }
  SEQ_EXIT_CRITICAL_SECTION();

  return;
}

/**
  * @brief This function checks if a task is registered
  *
  * @param task_id_bm The Id of the task, this parameter must be a value of the enumeration @ref seq_task_id_t
  * @retval 0 if not 1 if true
  */
uint32_t SEQ_IsRegisteredTask(seq_task_id_t task_id_bm)
{
  uint32_t status = 0;
  SEQ_ENTER_CRITICAL_SECTION();
  uint32_t position = SEQ_BitPosition((uint32_t)task_id_bm);
  if (position < SEQ_CONF_TASK_NBR)
  {
    if (TaskCb[position] != NULL)
    {
      status = 1;
    }
  }

  SEQ_EXIT_CRITICAL_SECTION();
  return status;
}

/**
  * @}
  */

/** @addtogroup SEQUENCER_Exported_function_G5 Task Enable functions
  * @{
 */

/**
  * @brief This function requests a task to be executed
  *
  * @param task_id_bm The Id of the task, this parameter must be a value of the enumeration @ref seq_task_id_t
  * @param task_prio The priority of the task
  *        It must a number from  0 (high priority) to 31 (low priority)
  *        The priority is checked each time the sequencer needs to select a new task to execute
  *        It does not permit to preempt a running task with lower priority
  *
  * @note   It can be called from an ISR
  *
  */
void SEQ_SetTask(seq_task_id_t task_id_bm, uint32_t task_prio)
{
  SEQ_ENTER_CRITICAL_SECTION();

  TaskSet |= (seq_bm_t)task_id_bm;
  TaskPrio[task_prio].priority |= (uint32_t)task_id_bm;

  SEQ_EXIT_CRITICAL_SECTION();

  return;
}

/**
  * @brief This function checks if a task could be scheduled.
  *
  * @param task_id_bm The Id of the task, this parameter must be a value of the enumeration @ref seq_task_id_t
  * @retval 0 if not 1 if true
  *
  * @note   It can be called from an ISR.
  *
  */
uint32_t SEQ_IsSchedulableTask(seq_task_id_t task_id_bm)
{
  uint32_t _status;
  seq_bm_t local_taskset;

  SEQ_ENTER_CRITICAL_SECTION();

  local_taskset = TaskSet;
  _status = ((local_taskset & TaskMask & SuperMask & ((seq_bm_t)task_id_bm)) == ((seq_bm_t)task_id_bm)) \
            ? 1U : 0U;

  SEQ_EXIT_CRITICAL_SECTION();
  return _status;
}

/**
  * @}
  */

/** @addtogroup SEQUENCER_Exported_function_G6 Task Pause/Resume functions
  * @{
  */
/**
  * @brief This function prevents a task to be called by the sequencer even when set with SEQ_SetTask()
  *        By default, all tasks are executed by the sequencer when set with SEQ_SetTask()
  *        When a task is paused, it is moved out from the sequencer list
  *
  * @param task_id_bm The Id of the task, this parameter must be a value of the enumeration @ref seq_task_id_t
  *
  * @note  It can be called from an ISR.
  *
  */
void SEQ_PauseTask(seq_task_id_t task_id_bm)
{
  SEQ_ENTER_CRITICAL_SECTION();

  TaskMask &= ((seq_bm_t)(~task_id_bm));

  SEQ_EXIT_CRITICAL_SECTION();

  return;
}

/**
  * @brief This function allows to know if the task has been put in pause.
  *        By default, all tasks are executed by the sequencer when set with SEQ_SetTask()
  *        The exit of the pause must be done by the function SEQ_ResumeTask.
  *
  * @param task_id_bm The Id of the task, this parameter must be a value of the enumeration @ref seq_task_id_t
  * @retval 0 if not 1 if true
  * @note  It can be called from an ISR.
  *
  */
uint32_t SEQ_IsPauseTask(seq_task_id_t task_id_bm)
{
  uint32_t _status;
  SEQ_ENTER_CRITICAL_SECTION();

  _status = ((TaskMask & ((seq_bm_t)task_id_bm)) == ((seq_bm_t)task_id_bm)) ? 0U : 1U;

  SEQ_EXIT_CRITICAL_SECTION();
  return _status;
}

/**
  * @brief This function allows again a task to be called by the sequencer if set with SEQ_SetTask()
  *        This is used in relation with SEQ_PauseTask()
  *
  * @param task_id_bm The Id of the task, this parameter must be a value of the enumeration @ref seq_task_id_t
  *
  * @note  It can be called from an ISR.
  *
  */
void SEQ_ResumeTask(seq_task_id_t task_id_bm)
{
  SEQ_ENTER_CRITICAL_SECTION();

  TaskMask |= ((seq_bm_t)task_id_bm);

  SEQ_EXIT_CRITICAL_SECTION();

  return;
}
/**
  * @}
  */

/** @addtogroup SEQUENCER_Exported_function_G7 Task Event functions
  * @{
  */
/**
  * @brief This function sets an event that is waited with SEQ_WaitEvt()
  *
  * @param evt_id_bm event id bit mask
  *
  * @note  An event must be a 32 bit mapping where only 1 bit is set
  *        It can be called from an ISR.
  *
  */
void SEQ_SetEvt(seq_bm_t evt_id_bm)
{
  SEQ_ENTER_CRITICAL_SECTION();

  EvtSet |= evt_id_bm;

  SEQ_EXIT_CRITICAL_SECTION();

  return;
}

/**
  * @brief This function can be used to clear the event before calling SEQ_WaitEvt()
  *        This API is useful when the SEQ_SetEvt() is called several time to notify the same event.
  *        Due to Software Architecture where the timings are hard to control, this can be an unwanted case.
  *
  * @param evt_id_bm event id bm
  *        It must be a bit mapping where only 1 bit is set
  *
  * @note   It can be called from an ISR.
  *
  */
void SEQ_ClrEvt(seq_bm_t evt_id_bm)
{
  SEQ_ENTER_CRITICAL_SECTION();

  EvtSet &= (~evt_id_bm);

  SEQ_EXIT_CRITICAL_SECTION();

  return;
}

/**
  * @brief This function waits for a specific event to be set. Sequencer loops SEQ_EvtIdle() until the event is set
  *        When called recursively, it acts as a First in / Last out mechanism. The sequencer waits for the
  *        last event requested to be set even though one of the already requested event has been set.
  *
  * @param evt_id_bm event id bit mask
  *        It must be a bit mapping where only 1 bit is set
  *
  * @note  It must not be called from an ISR.
  * @note  The construction of the task must take into account the fact that there is no counting / protection on the
  *        event. Thus, when the task is running, it must perform all the operations in progress programmed before its
  *        call or manage a reprogramming of the task.
  */
void SEQ_WaitEvt(seq_bm_t evt_id_bm)
{
  seq_bm_t event_waited_id_backup;
  seq_bm_t current_task_idx;
  seq_bm_t wait_task_idx;
  /*
   * store in local the current_task_id_bm as the global variable CurrentTaskIdx
   * can be overwritten in case there are nested call of SEQ_Run()
   */
  current_task_idx = CurrentTaskIdx;
  if (SEQ_NOTASKRUNNING == CurrentTaskIdx)
  {
    wait_task_idx = 0U;
  }
  else
  {
    wait_task_idx = (uint32_t)1U << CurrentTaskIdx;
  }

  /* backup the event id that was currently waited */
  event_waited_id_backup = EvtWaited;
  EvtWaited = evt_id_bm;
  /*
   * wait for the new event
   * note: that means that if the previous waited event occurs, it will not exit
   * the while loop below.
   * The system is waiting only for the last waited event.
   * When it will go out, it will wait again from the previous one.
   * It case it occurs while waiting for the second one, the while loop will exit immediately
   */

  while ((EvtSet & evt_id_bm) == 0U)
  {
    SEQ_EvtIdle(wait_task_idx, evt_id_bm);
  }

  /*
   * Restore the CurrentTaskIdx that can have been modified by call of SEQ_Run()
   * from SEQ_EvtIdle(). This is required so that a second call of SEQ_WaitEvt()
   * in the same process pass the correct current_task_id_bm in the call of SEQ_EvtIdle()
   */
  CurrentTaskIdx = current_task_idx;

  SEQ_ENTER_CRITICAL_SECTION();

  EvtSet &= (~evt_id_bm);

  SEQ_EXIT_CRITICAL_SECTION();

  EvtWaited = event_waited_id_backup;
  return;
}

/**
  * @brief This function returns whether the waited event is pending or not
  *        It is useful only when the SEQ_EvtIdle() is overloaded by the application. In that case, when the low
  *        power mode needs to be executed, the application must first check whether the waited event is pending
  *        or not. Both the event checking and the low power mode processing must be done in critical section
  *
  * @retval 0 when the waited event is not there or the evt_id when the waited event is pending
  *
  * @note   It can be called from an ISR.
  *
  */
seq_bm_t SEQ_IsEvtPend(void)
{
  seq_bm_t local_evtwaited = EvtWaited;
  return (EvtSet & local_evtwaited);
}

/**
  * @brief This function loops until the waited event is set
  * @param task_id_bm The task id that is currently running. When task_id_bm = 0, it means SEQ_WaitEvt( )
  *                     has been called outside a registered task (ie at startup before SEQ_Run( ) has been called
  * @param evt_waited_bm The event id that is waited.
  *
  * @note  When not implemented by the application, it calls SEQ_Run(~task_id_bm) which means the waited
  *        task is suspended until the waited event and the other tasks are running or the application enter
  *        low power mode.
  *        Else the user can redefine his own function for example call sequencer SEQ_Run(0) to suspend all
  *        the task and let the sequencer enter the low power mode.
  *        It must be called only by the sequencer.
  *
  */
__WEAK void SEQ_EvtIdle(seq_bm_t task_id_bm, seq_bm_t evt_waited_bm)
{
  (void)evt_waited_bm;
  SEQ_Run(~task_id_bm);
  return;
}

/**
  * @}
  */

/** @addtogroup SEQUENCER_Exported_function_G8 Pre-Post Task functions
  * @{
  */

/**
  * @brief This function is call before a task execution
  * @param task_id The task id.
  *
  * @note  the function is provided to help the debug and
  *        the default implementation does nothing
  *
  */
__WEAK void SEQ_PreTask(uint32_t task_id)
{
  (void)task_id;
  return;
}

/**
  * @brief This function is called after a task execution
  * @param task_id The task id.
  *
  * @note  the function is provided to help the debug and
  *        the default implementation does nothing
  *
  */
__WEAK void SEQ_PostTask(uint32_t task_id)
{
  (void)task_id;
  return;
}

/**
  * @brief This function is called when a warning is detected
  * @param warning_id The warning id.
  *
  * @note  the function is provided to help the debug and
  *        the default implementation does nothing
  */
__WEAK void SEQ_CatchWarning(seq_warning_t warning_id)
{
  (void)warning_id;
  return;
}

/**
  * @}
  */
/**
  * @}
 */
/** @addtogroup SEQUENCER_Private_function
  *  @{
  */

#if defined(__CORTEX_M) && (__CORTEX_M == 0U)

const uint8_t SEQ_clz_table_4bit[16U] = {4U, 3U, 2U, 2U, 1U, 1U, 1U, 1U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};
/**
  * @brief return the position of the first bit set to 1
  * @param value 32 bit value
  * @retval bit position
  */
uint8_t SEQ_BitPosition(uint32_t value)
{
  uint8_t position = 0U;
  uint32_t lvalue = value;

  if ((lvalue & 0xFFFF0000U) == 0U)
  {
    position = 16U;
    lvalue <<= 16U;
  }
  if ((lvalue & 0xFF000000U) == 0U)
  {
    position += 8U;
    lvalue <<= 8U;
  }
  if ((lvalue & 0xF0000000U) == 0U)
  {
    position += 4U;
    lvalue <<= 4U;
  }

  position += SEQ_clz_table_4bit[lvalue >> (32U - 4U)];

  return (uint8_t)(31U - position);
}
#else
/**
  * @brief return the position of the first bit set to 1
  * @param value 32 bit value
  * @retval bit position
  */
uint8_t SEQ_BitPosition(uint32_t value)
{
  return (uint8_t)(31U - __CLZ(value));
}
#endif /* __CORTEX_M */

/**
  * @}
  */

/**
  * @}
  */
