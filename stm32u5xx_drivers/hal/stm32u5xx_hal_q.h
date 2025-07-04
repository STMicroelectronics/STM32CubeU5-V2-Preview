/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_q.h
  * @brief   Header file of HAL Q module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_HAL_Q_H
#define STM32U5XX_HAL_Q_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup Q Q
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup Q_Exported_Types Q Exported Types
  * @{
  */

/*! Q addressing mode enumeration definition */
typedef enum
{
  HAL_Q_ADDRESSING_DIRECT      = 0U, /*!< Specifies that addressing is used directly for nodes link                    */
  HAL_Q_ADDRESSING_BASE_OFFSET = 1U  /*!< Specifies that addressing is calculated versus a base address for nodes link */
} hal_q_addressing_mode_t;

/*! Q descriptor operations structure definition */
typedef struct
{
  void (* p_get_node_info)(uint32_t *offset, hal_q_addressing_mode_t *addressing_mode);
  /*!< Specifies the Q node structure information provided by HAL PPP that supports linked-list feature \n
       @param offset          next node address offset \n
       @param addressing_mode node addressing mode */

  void (* p_set_node)(uint32_t head, uint32_t prev, uint32_t next, uint32_t offset);
  /*!< Specifies the Q set node address information provided by HAL PPP that supports linked-list feature \n
       @param head    Head node address     \n
       @param prev    Previous node address \n
       @param next    Next node address     \n
       @param offset  Node address offset          */

  uint32_t (* p_get_node)(uint32_t head, uint32_t node, uint32_t offset);
  /*!< Specifies the Q get node address information provided by HAL PPP that supports linked-list feature \n
       @param head    Head node address    \n
       @param node    Current node address \n
       @param offset  Node address offset          */
} hal_q_desc_ops_t;

/*! Q structure definition */
typedef struct
{
  void     *p_head_node;                                                             /*!< Specifies the Q head node                                                                          */

  void     *p_tail_node;                                                             /*!< Specifies the Q tail node                                                                          */

#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1U)
  void     *p_first_circular_node;                                                   /*!< Specifies the Q first circular node                                                                */
#endif /* USE_HAL_Q_CIRCULAR_LINK */

  uint32_t node_nbr;                                                                 /*!< Specifies the Q node number                                                                        */

  uint32_t next_addr_offset;                                                         /*!< Specifies next node address offset provided by HAL PPP that supports linked-list feature           */

  hal_q_addressing_mode_t addr_mode;                                                 /*!< Specifies the Q addressing mode provided by HAL PPP that supports linked-list feature              */

  void (* p_set_node)(uint32_t head, uint32_t prev, uint32_t next, uint32_t offset); /*!< Specifies the Q set node address information provided by HAL PPP that supports linked-list feature */

  uint32_t (* p_get_node)(uint32_t head, uint32_t node, uint32_t offset);            /*!< Specifies the Q get node address information provided by HAL PPP that supports linked-list feature */

} hal_q_t;
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup Q_Exported_Functions Q Exported Functions
  * @{
  */

/** @defgroup Q_Exported_Functions_Group1 Q Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_Q_Init(hal_q_t *p_q, const hal_q_desc_ops_t *p_desc_ops);
void         HAL_Q_DeInit(hal_q_t *p_q);
/**
  * @}
  */

/** @defgroup Q_Exported_Functions_Group2 Q node insertion functions
  * @{
  */
hal_status_t HAL_Q_InsertNode(hal_q_t *p_q, const void *p_node, void *p_new_node);
hal_status_t HAL_Q_InsertNode_Head(hal_q_t *p_q, void *p_new_node);
hal_status_t HAL_Q_InsertNode_Tail(hal_q_t *p_q, void *p_new_node);
/**
  * @}
  */

/** @defgroup Q_Exported_Functions_Group3 Q node removing functions
  * @{
  */
hal_status_t HAL_Q_RemoveNode(hal_q_t *p_q, const void *p_node);
hal_status_t HAL_Q_RemoveNode_Head(hal_q_t *p_q);
hal_status_t HAL_Q_RemoveNode_Tail(hal_q_t *p_q);
/**
  * @}
  */

/** @defgroup Q_Exported_Functions_Group4 Q node replacing functions
  * @{
  */
hal_status_t HAL_Q_ReplaceNode(hal_q_t *p_q, const void *p_old_node, void *p_new_node);
hal_status_t HAL_Q_ReplaceNode_Head(hal_q_t *p_q, void *p_new_node);
hal_status_t HAL_Q_ReplaceNode_Tail(hal_q_t *p_q, void *p_new_node);
/**
  * @}
  */

/** @defgroup Q_Exported_Functions_Group5 Q inserting Q functions
  * @{
  */
hal_status_t HAL_Q_InsertQ(hal_q_t *p_dest_q, hal_q_t *p_src_q, const void *p_node);
hal_status_t HAL_Q_InsertQ_Head(hal_q_t *p_dest_q, hal_q_t *p_src_q);
hal_status_t HAL_Q_InsertQ_Tail(hal_q_t *p_dest_q, hal_q_t *p_src_q);
/**
  * @}
  */

#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1U)
/** @defgroup Q_Exported_Functions_Group6 Q circularizing Q functions
  * @{
  */
hal_status_t HAL_Q_SetCircularLinkQ(hal_q_t *p_q, void *p_node);
hal_status_t HAL_Q_SetCircularLinkQ_Head(hal_q_t *p_q);
hal_status_t HAL_Q_SetCircularLinkQ_Tail(hal_q_t *p_q);
hal_status_t HAL_Q_ClearCircularLinkQ(hal_q_t *p_q);
/**
  * @}
  */
#endif /* USE_HAL_Q_CIRCULAR_LINK */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_HAL_Q_H */
