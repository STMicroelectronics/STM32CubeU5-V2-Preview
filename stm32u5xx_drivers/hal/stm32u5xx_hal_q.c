/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_q.c
  * @brief   This file provides Q services.
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

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/**
  * @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup Q
  * @{

# How to use the Q HAL module driver

## The Q HAL module can be used as follows:

Q is the abbreviation of Queue wording. It is an entity that contains a node or set of nodes linked between each others.
Each node contains a set of data a link to the next node.

This module is an utility HAL driver that can be used only with specific HAL modules that supports linked-list feature.
This module is activated automatically when activation USE_HAL_PPP_LINKEDLIST compilation flag through
stm32ynxx_hal_conf.h module.
This module allows to build a linked-list Q executable from masters that supports linked-list feature.
In order to build Q(s) compatible with different linked-list masters, this module supports two addressing modes :
   - Direct addressing mode : where node links addresses presents the physical node address.
   - Base offset addressing mode : where node links addresses presents the offset of the node versus Q head node
     address.
This module supports singly linked-list Q nodes.
The behavior of this module is not granted when a Q is modified outside this module.

This module provides 6 different set of APIs that allows to :

1. Initialize and de-initialize the logical Q object :
   - Initialize the logical Q object thanks to a set of information provided by any HAL peripheral module that supports
     the linked list feature. When initialized, the Q must be ready to apply any operation provided by this module.
   - De-initialize the logical Q object and unlink all Q node(s). When de-initialized, the Q object can be reused for
     the same or another master executor.

2. Insert new node in a Q :
   - Insert a new node to a Q into any position thanks to the following set of functions models :
     - Generic new node insertion function that allows to add a new node at any selected Q position.
       - This functionality is ensured by HAL_Q_InsertNode() function. The p_node parameter allows to specify where the
         new node must be inserted.
         - When the p_node is null, the new node is placed at the head of Q.
         - When the p_node is not null, the new node is placed directly after the p_node. If the p_node is not found
           within the Q, the function returns an error and the Q is not modified.
     - New head node insertion function that allows to add a new node as a new head node Q.
       - This functionality is ensured by HAL_Q_InsertNode_Head() function.
     - New tail node insertion function that allows to add a new node as a new tail node Q.
       - This functionality is ensured by HAL_Q_InsertNode_Tail() function.
   - It is forbidden to add a new node when the selected Q is circular.
   - When possible, it is recommended to use tail node insertion model function to reduce footprint.

3. Remove an existing node from a Q :
   - Remove any existing node from a Q thanks to the following set of functions models :
     - Generic node removing function that allows to remove any existing node from a Q.
       - This functionality is ensured by HAL_Q_RemoveNode() function.
         - The p_node parameter allows to select the node to be removed. This function returns an error when the p_node
           is not found within the Q or the p_node parameter is null.
     - Head node removing function that allows to remove the head node from a Q.
       - This functionality is ensured by HAL_Q_RemoveNode_Head() function.
     - Tail node removing function that allows to remove the tail node from a Q.
       - This functionality is ensured by HAL_Q_RemoveNode_Tail() function.
   - It is forbidden to remove an existent node when the selected Q is circular.
   - When successfully removed, the removed node can be reusable later.

4. Replace an existing node in a Q :
   - Replace any existing node by a new node in a Q thanks to the following set of functions models :
     - Generic node replacing function that allows to replace any existing node by a new node in a Q.
       - This functionality is ensured by HAL_Q_ReplaceNode() function. The p_old_node parameter allows to specify the
         node to be replaced.
         - When the p_old_node is not null, the p_new_node replaces the p_old_node. If the p_old_node is not found
           within the Q, the function returns an error and the Q is not modified.
     - Head node replacing function that allows to replace the existing head node by a new head node in a Q.
       - This functionality is ensured by HAL_Q_ReplaceNode_Head() function.
     - Tail node replacing function that allows to replace the existing tail node by a new tail node in a Q.
       - This functionality is ensured by HAL_Q_ReplaceNode_Tail() function.
   - It is forbidden to replace an existent node when the selected Q is circular.
   - When successfully replaced, the replaced node can be reusable later.

5. Insert source Q in a destination Q :
   - Insert a source Q to a destination Q into any position thanks to the following set of functions models :
     - Generic source Q insertion function that allows to insert a source Q node(s) to any selected destination Q
       position.
       - This functionality is ensured by HAL_Q_InsertNode() function. The p_node parameter allows to specify where the
         source Q node(s) must be inserted.
         - When the p_node is null, the source Q node(s) is placed at the head of destination Q.
         - When the p_node is not null, the source Q node(s) is placed directly after the p_node. If the p_node is not
           found within the destination Q, the function returns an error and the source and destination Qs are not
           modified.
     - Head source Q insertion function that allows to insert a source Q node(s) before all the destination Q node(s).
       - This functionality is ensured by HAL_Q_InsertNode_Head() function.
     - Tail source Q insertion function that allows to insert a source Q node(s) after all the destination Q node(s).
       - This functionality is ensured by HAL_Q_InsertNode_Tail() function.
   - It is forbidden to add a source Q node(s) to a destination Q node(s) when any Q is circular.
   - When possible, it is recommended to use tail Q insertion model function to reduce footprint.
   - When successfully inserted, the destination Q must contains source Q nodes and destination Q nodes and the source Q
     must be cleared and can be reused later without need reinitialize it.

6. Set and clear a circular link to not empty Q :
   - Set a circular link to any Q node thanks to the following set of functions models :
     - Generic circular link Q setting function that allows to set a circular link to a any not empty Q position.
       - This functionality is ensured by HAL_Q_SetCircularLinkQ() function. The p_node parameter allows to specify
         the first circular node (Node linked to Q tail node). This function returns an error when the p_node
         is not found within the Q or the p_node parameter is null.
     - Head circular link Q setting function that allows to set a circular link to the head node of Q.
       - This functionality is ensured by HAL_Q_SetCircularLinkQ_Head() function.
     - Tail circular link Q setting function that allows to set a circular link to the tail node of Q.
       - This functionality is ensured by HAL_Q_SetCircularLinkQ_Tail() function.
   - Clear a circular link from a Q.
     - This functionality is ensured by HAL_Q_ClearCircularLinkQ() function.

## Configuration inside the Q module

Config defines           | Description     | Default value | Note
------------------------ | --------------- | ------------- | ---------------------------------------------------------
USE_ASSERT_DBG_PARAM     | from IDE        |     None      | When defined, enable the params assert.
USE_HAL_CHECK_PARAM      | from hal_conf.h |     0U        | It allows to use the run-time checks on parameters.
USE_HAL_{PPP}_LINKEDLIST | from hal_conf.h |     0U        | It allows to use the PPP in linked-list mode.
USE_HAL_Q_CIRCULAR_LINK  | from hal_ppp.h  |     0U        | It allows to use circular link queue.
  */

#if (defined(USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)) \
  || (defined(USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1))

/* Private constants -------------------------------------------------------------------------------------------------*/
/* Private types -----------------------------------------------------------------------------------------------------*/
/** @defgroup Q_Private_Types Q Private Types
  * @{
  */
/*! Q operations */
typedef enum
{
  /* Node operation */
  Q_INSERT_NODE     = 0U, /*!< Q insert node operation     */
  Q_REMOVE_NODE     = 1U, /*!< Q remove node operation     */
  Q_REPLACE_NODE    = 2U, /*!< Q replace node operation    */
  /* Q operation */
  Q_INSERT_Q_HEAD   = 3U, /*!< Q insert head Q operation   */
  Q_INSERT_Q_MIDDLE = 4U, /*!< Q insert middle Q operation */
  Q_INSERT_Q_TAIL   = 5U  /*!< Q insert tail Q operation   */
} q_operation_t;

#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
/*! Q check nodes */
typedef enum
{
  Q_CHECK_HEAD_NODE = 0U, /*!< Q check only head node address */
  Q_CHECK_ALL_NODES = 1U  /*!< Q check all nodes addresses    */
} q_check_nodes_t;
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */
/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @defgroup Q_Private_Functions Q Private Functions
  * @{
  */
static void Q_UnlinkNodes(hal_q_t *p_q, uint32_t head_node_addr);
static void Q_ResetInfo(hal_q_t *p_q);
static hal_status_t Q_FindNode(const hal_q_t *p_q, uint32_t head_node_addr, uint32_t node_addr,
                               uint32_t *p_prev_node_addr);
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
static void Q_FormatBaseOffsetNodes(const hal_q_t *p_q, uint32_t node, q_operation_t node_operation);
static void Q_FormatBaseOffsetQ(const hal_q_t *p_dest_q, const hal_q_t *p_src_q, uint32_t node,
                                q_operation_t q_operation);
static hal_status_t Q_IsValidNodeAddr(const hal_q_t *p_q, uint32_t start_node, uint32_t node, q_check_nodes_t mode);
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup Q_Exported_Functions Q Exported Functions
  * @{
  */

/** @addtogroup Q_Exported_Functions_Group1 Q Initialization and de-initialization functions
  * @{
This section provides functions allowing to initialize and de-initialize the logical Q object :
- Call the function HAL_Q_Init() initialize the logical Q object and associate its operation information.
- Call the function HAL_Q_DeInit() to de-initialize the logical Q object and unlink its nodes.
  */

/**
  * @brief  Initialize the logical Q object and associate its operation information.
  * @param  p_q               Pointer to a hal_q_t structure that contains Q information.
  * @param  p_desc_ops        Pointer to a hal_q_desc_ops_t structure that contains Q operation information.
  * @note                     The p_desc_ops is a constant provided by HAL PPP modules that supports linked-list feature
  *                           titled HAL_PPP_{mode}_DescOps or HAL_PPP_DescOps.
  * @retval HAL_OK            In case of valid initialization.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  */
hal_status_t HAL_Q_Init(hal_q_t *p_q, const hal_q_desc_ops_t *p_desc_ops)
{
  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(p_desc_ops != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_q == NULL) || (p_desc_ops == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_desc_ops->p_get_node_info(&p_q->next_addr_offset, &p_q->addr_mode);

  p_q->p_head_node           = NULL;
  p_q->p_tail_node           = NULL;
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  p_q->p_first_circular_node = NULL;
#endif /* USE_HAL_Q_CIRCULAR_LINK */
  p_q->node_nbr              = 0U;
  p_q->p_set_node            = p_desc_ops->p_set_node;
  p_q->p_get_node            = p_desc_ops->p_get_node;

  return HAL_OK;
}

/**
  * @brief Deinitialize the logical Q object and unlink its node(s).
  * @param p_q Pointer to a hal_q_t structure that contains Q information.
  */
void HAL_Q_DeInit(hal_q_t *p_q)
{
  uint32_t head;

  ASSERT_DBG_PARAM(p_q != NULL);

  head = (uint32_t)p_q->p_head_node;

  Q_UnlinkNodes(p_q, head);

  p_q->p_head_node = NULL;
}
/**
  * @}
  */

/** @addtogroup Q_Exported_Functions_Group2 Q node insertion functions
  * @{
This section provides functions allowing to insert new node in any Q position :
- Call the function HAL_Q_InsertNode() to insert a new node in any Q position.
- Call the function HAL_Q_InsertNode_Head() to insert a new node in the head position of a Q.
- Call the function HAL_Q_InsertNode_Tail() to insert a new node in the tail position of a Q.
  */

/**
  * @brief  Insert a new node after a previous node in a Q.
  * @param  p_q               Pointer to a hal_q_t structure that contains Q information.
  * @param  p_node            Pointer to node that specifies insertion position. When null, the new node is placed at
  *                           the head of Q
  * @param  p_new_node        Pointer to new node.
  * @retval HAL_OK            In case of node inserted successfully.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  * @retval HAL_ERROR         In case of p_prev_node node not found in the Q.
  */
hal_status_t HAL_Q_InsertNode(hal_q_t *p_q, const void *p_node, void *p_new_node)
{
  uint32_t head;
  uint32_t node;
  uint32_t new_node;
  uint32_t offset;

  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(p_new_node != NULL);
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  ASSERT_DBG_PARAM(p_q->p_first_circular_node == NULL);
#endif /* USE_HAL_Q_CIRCULAR_LINK */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_new_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  if (p_q->p_first_circular_node != NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_Q_CIRCULAR_LINK */
#endif /* USE_HAL_CHECK_PARAM */

  head     = (uint32_t)p_q->p_head_node;
  node     = (uint32_t)p_node;
  new_node = (uint32_t)p_new_node;
  offset   = p_q->next_addr_offset;

  /* Empty Q */
  if ((p_q->p_head_node == NULL) && (p_node == NULL))
  {
    p_q->p_head_node = p_new_node;
    p_q->p_tail_node = p_new_node;
  }
  /* Not empty Q */
  else if (p_q->p_head_node != NULL)
  {
    /* Insert node at head level */
    if (p_node == NULL)
    {
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
      if (p_q->addr_mode != HAL_Q_ADDRESSING_DIRECT)
      {
        if (Q_IsValidNodeAddr(p_q, head, new_node, Q_CHECK_ALL_NODES) == HAL_OK)
        {
          Q_FormatBaseOffsetNodes(p_q, new_node, Q_INSERT_NODE);
        }
        else
        {
          return HAL_ERROR;
        }
      }
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
      if (p_q->addr_mode == HAL_Q_ADDRESSING_DIRECT)
      {
        p_q->p_set_node(head, new_node, head, offset);
      }
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */

      p_q->p_head_node = p_new_node;
    }
    else
    {
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
      if (p_q->addr_mode != HAL_Q_ADDRESSING_DIRECT)
      {
        if (Q_IsValidNodeAddr(p_q, head, new_node, Q_CHECK_HEAD_NODE) != HAL_OK)
        {
          return HAL_ERROR;
        }
      }
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

      /* Insert node at tail level */
      if (p_node == p_q->p_tail_node)
      {
        p_q->p_set_node(head, node, new_node, offset);
        p_q->p_tail_node = p_new_node;
      }
      /* Insert node at middle level */
      else
      {
        /* Find node */
        if (Q_FindNode(p_q, head, node, NULL) == HAL_OK)
        {
          p_q->p_set_node(head, new_node, p_q->p_get_node(head, node, offset), offset);
          p_q->p_set_node(head, node, new_node, offset);
        }
        else
        {
          return HAL_ERROR;
        }
      }
    }
  }
  else
  {
    return HAL_ERROR;
  }

  p_q->node_nbr++;

  return HAL_OK;
}

/**
  * @brief Insert a new node in the head of the Q.
  * @param p_q                Pointer to a hal_q_t structure that contains Q information.
  * @param p_new_node         Pointer to a new node.
  * @retval HAL_OK            In case of node inserted successfully in the head of the Q.
  * @retval HAL_ERROR         In case of node not inserted.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  */
hal_status_t HAL_Q_InsertNode_Head(hal_q_t *p_q, void *p_new_node)
{
  uint32_t head;
  uint32_t new_node;
#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
  uint32_t offset;
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */

  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(p_new_node != NULL);
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  ASSERT_DBG_PARAM(p_q->p_first_circular_node == NULL);
#endif /* USE_HAL_Q_CIRCULAR_LINK */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_new_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  if (p_q->p_first_circular_node != NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_Q_CIRCULAR_LINK */
#endif /* USE_HAL_CHECK_PARAM */

  head     = (uint32_t)p_q->p_head_node;
  new_node = (uint32_t)p_new_node;
#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
  offset   = p_q->next_addr_offset;
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */

  /* Empty Q */
  if (p_q->p_head_node == NULL)
  {
    p_q->p_head_node = p_new_node;
    p_q->p_tail_node = p_new_node;
  }
  /* Not empty Q */
  else
  {
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
    if (p_q->addr_mode != HAL_Q_ADDRESSING_DIRECT)
    {
      if (Q_IsValidNodeAddr(p_q, head, new_node, Q_CHECK_ALL_NODES) == HAL_OK)
      {
        Q_FormatBaseOffsetNodes(p_q, new_node, Q_INSERT_NODE);
      }
      else
      {
        return HAL_ERROR;
      }
    }
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
    if (p_q->addr_mode == HAL_Q_ADDRESSING_DIRECT)
    {
      p_q->p_set_node(head, new_node, head, offset);
    }
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */

    p_q->p_head_node = p_new_node;
  }

  p_q->node_nbr++;

  return HAL_OK;
}

/**
  * @brief  Insert a new node in the tail of the Q.
  * @param  p_q               Pointer to a hal_q_t structure that contains Q information.
  * @param  p_new_node        Pointer to a new node.
  * @retval HAL_OK            In case of node inserted successfully in the tail of the Q.
  * @retval HAL_ERROR         In case of node not inserted.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  */
hal_status_t HAL_Q_InsertNode_Tail(hal_q_t *p_q, void *p_new_node)
{
  uint32_t head;
  uint32_t tail;
  uint32_t new_node;
  uint32_t offset;

  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(p_new_node != NULL);
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  ASSERT_DBG_PARAM(p_q->p_first_circular_node == NULL);
#endif /* USE_HAL_Q_CIRCULAR_LINK */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_new_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  if (p_q->p_first_circular_node != NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_Q_CIRCULAR_LINK */
#endif /* USE_HAL_CHECK_PARAM */

  head     = (uint32_t)p_q->p_head_node;
  tail     = (uint32_t)p_q->p_tail_node;
  new_node = (uint32_t)p_new_node;
  offset   = p_q->next_addr_offset;

  /* Empty Q */
  if (p_q->p_head_node == NULL)
  {
    p_q->p_head_node = p_new_node;
    p_q->p_tail_node = p_new_node;
  }
  /* Not empty Q */
  else
  {
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
    if (p_q->addr_mode != HAL_Q_ADDRESSING_DIRECT)
    {
      if (Q_IsValidNodeAddr(p_q, head, new_node, Q_CHECK_HEAD_NODE) != HAL_OK)
      {
        return HAL_ERROR;
      }
    }
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

    p_q->p_set_node(head, tail, new_node, offset);
    p_q->p_tail_node = p_new_node;
  }

  p_q->node_nbr++;

  return HAL_OK;
}
/**
  * @}
  */


/** @addtogroup Q_Exported_Functions_Group3 Q node removing functions
  * @{
This section provides functions allowing to remove any existing node from a Q :
- Call the function HAL_Q_RemoveNode() to remove any existing node from a Q.
- Call the function HAL_Q_RemoveNode_Head() to remove the head node from a Q.
- Call the function HAL_Q_RemoveNode_Tail() to remove the tail node from a Q.
  */

/**
  * @brief  Remove node from the Q.
  * @param  p_q               Pointer to a hal_q_t structure that contains Q information.
  * @param  p_node            Pointer to a previous node.
  * @retval HAL_OK            In case of node removed successfully.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  * @retval HAL_ERROR         In case of node not found in the Q.
  */
hal_status_t HAL_Q_RemoveNode(hal_q_t *p_q, const void *p_node)
{
  uint32_t prev;
  uint32_t head;
  uint32_t tail;
  uint32_t node;
  uint32_t offset;
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
  uint32_t new_head;
  uint32_t next_node;
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(p_node != NULL);
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  ASSERT_DBG_PARAM(p_q->p_first_circular_node == NULL);
#endif /* USE_HAL_Q_CIRCULAR_LINK */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  if (p_q->p_first_circular_node != NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_Q_CIRCULAR_LINK */
#endif /* USE_HAL_CHECK_PARAM */

  head   = (uint32_t)p_q->p_head_node;
  tail   = (uint32_t)p_q->p_tail_node;
  node   = (uint32_t)p_node;
  offset = p_q->next_addr_offset;

  /* Delete head node */
  if (p_node == p_q->p_head_node)
  {
    if (p_q->node_nbr == 1U)
    {
      Q_ResetInfo(p_q);
    }
    else
    {
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
      if (p_q->addr_mode != HAL_Q_ADDRESSING_DIRECT)
      {
        /* Get new head and next node */
        new_head = p_q->p_get_node(head, head, offset);
        next_node = p_q->p_get_node(head, new_head, offset);

        if (Q_IsValidNodeAddr(p_q, next_node, new_head, Q_CHECK_ALL_NODES) == HAL_OK)
        {
          Q_FormatBaseOffsetNodes(p_q, p_q->p_get_node(head, head, offset), Q_REMOVE_NODE);
        }
        else
        {
          return HAL_ERROR;
        }
      }
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

      /* Set the new head node */
      p_q->p_head_node = (void *)(p_q->p_get_node(head, head, offset));
      p_q->p_set_node(0U, node, 0U, offset);
    }
  }
  else
  {
    /* Delete tail node */
    if (p_node == p_q->p_tail_node)
    {
      prev = tail;
    }
    /* Delete middle node */
    else
    {
      prev = node;
    }

    if (Q_FindNode(p_q, head, prev, &prev) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Delete tail node */
    if (p_node == p_q->p_tail_node)
    {
      /* Set the new tail node */
      p_q->p_tail_node = (void *)prev;
      p_q->p_set_node(0U, prev, 0U, offset);
    }
    /* Delete middle node */
    else
    {
      p_q->p_set_node(head, prev, p_q->p_get_node(head, node, offset), offset);
      p_q->p_set_node(0U, node, 0U, offset);
    }
  }

  p_q->node_nbr--;

  return HAL_OK;
}

/**
  * @brief  Remove the head node of Q.
  * @param  p_q               Pointer to a hal_q_t structure that contains Q information.
  * @retval HAL_OK            In case of head node removed successfully.
  * @retval HAL_ERROR         In case of node not found.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  */
hal_status_t HAL_Q_RemoveNode_Head(hal_q_t *p_q)
{
  uint32_t head;
  uint32_t offset;
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
  uint32_t new_head;
  uint32_t next_node;
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(p_q->p_head_node != NULL);
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  ASSERT_DBG_PARAM(p_q->p_first_circular_node == NULL);
#endif /* USE_HAL_Q_CIRCULAR_LINK */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_q->p_head_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  if (p_q->p_first_circular_node != NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_Q_CIRCULAR_LINK */
#endif /* USE_HAL_CHECK_PARAM */

  offset = p_q->next_addr_offset;

  if (p_q->node_nbr == 1U)
  {
    Q_ResetInfo(p_q);
  }
  else
  {
    /* Store the old head node */
    head = (uint32_t)p_q->p_head_node;

#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
    if (p_q->addr_mode != HAL_Q_ADDRESSING_DIRECT)
    {
      new_head  = p_q->p_get_node(head, head, offset);
      next_node = p_q->p_get_node(head, new_head, offset);

      if (Q_IsValidNodeAddr(p_q, next_node, new_head, Q_CHECK_ALL_NODES) == HAL_OK)
      {
        Q_FormatBaseOffsetNodes(p_q, p_q->p_get_node(head, head, offset), Q_REMOVE_NODE);
      }
      else
      {
        return HAL_ERROR;
      }
    }
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

    /* Set the new head node */
    p_q->p_head_node = (void *)(p_q->p_get_node(head, head, offset));
    p_q->p_set_node(0U, head, 0U, offset);
  }

  p_q->node_nbr--;

  return HAL_OK;
}

/**
  * @brief  Remove the tail node of Q.
  * @param  p_q               Pointer to a hal_q_t structure that contains Q information.
  * @retval HAL_OK            In case of tail node removed successfully.
  * @retval HAL_ERROR         In case of node not found.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  */
hal_status_t HAL_Q_RemoveNode_Tail(hal_q_t *p_q)
{
  uint32_t prev = 0U;
  uint32_t head;
  uint32_t tail;
  uint32_t offset;

  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(p_q->p_tail_node != NULL);
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  ASSERT_DBG_PARAM(p_q->p_first_circular_node == NULL);
#endif /* USE_HAL_Q_CIRCULAR_LINK */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_q->p_tail_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  if (p_q->p_first_circular_node != NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_Q_CIRCULAR_LINK */
#endif /* USE_HAL_CHECK_PARAM */

  head   = (uint32_t)p_q->p_head_node;
  tail   = (uint32_t)p_q->p_tail_node;
  offset = p_q->next_addr_offset;

  if (p_q->node_nbr == 1U)
  {
    Q_ResetInfo(p_q);
  }
  else
  {
    if (Q_FindNode(p_q, head, tail, &prev) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Set the new tail node */
    p_q->p_tail_node = (void *)prev;
    p_q->p_set_node(0U, prev, 0U, offset);
  }

  p_q->node_nbr--;

  return HAL_OK;
}
/**
  * @}
  */


/** @addtogroup Q_Exported_Functions_Group4 Q node replacing functions
  * @{
This section provides functions allowing to replace any existing node in a Q :
- Call the function HAL_Q_ReplaceNode() to replace any existing node by a new node in a Q.
- Call the function HAL_Q_ReplaceNode_Head() to replace the head node in a Q.
- Call the function HAL_Q_ReplaceNode_Tail() to replace the tail node in a Q.
  */

/**
  * @brief  Replace node in the Q.
  * @param  p_q               Pointer to a hal_q_t structure that contains Q information.
  * @param  p_old_node        Pointer to a old node.
  * @param  p_new_node        Pointer to a new node.
  * @retval HAL_OK            In case of node replaced successfully.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  * @retval HAL_ERROR         In case of old node not found in the Q.
  */
hal_status_t HAL_Q_ReplaceNode(hal_q_t *p_q, const void *p_old_node, void *p_new_node)
{
  uint32_t prev;
  uint32_t head;
  uint32_t tail;
  uint32_t new_node;
  uint32_t old_node;
  uint32_t offset;

  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(p_old_node != NULL);
  ASSERT_DBG_PARAM(p_new_node != NULL);
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  ASSERT_DBG_PARAM(p_q->p_first_circular_node == NULL);
#endif /* USE_HAL_Q_CIRCULAR_LINK */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_old_node == NULL) || (p_new_node == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  if (p_q->p_first_circular_node != NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_Q_CIRCULAR_LINK */
#endif /* USE_HAL_CHECK_PARAM */

  head     = (uint32_t)p_q->p_head_node;
  tail     = (uint32_t)p_q->p_tail_node;
  new_node = (uint32_t)p_new_node;
  old_node = (uint32_t)p_old_node;
  offset   = p_q->next_addr_offset;

  if (p_old_node == p_q->p_head_node)
  {
    if (p_q->node_nbr == 1U)
    {
      p_q->p_tail_node = p_new_node;
    }
    else
    {
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
      if (p_q->addr_mode != HAL_Q_ADDRESSING_DIRECT)
      {
        if (Q_IsValidNodeAddr(p_q, head, new_node, Q_CHECK_ALL_NODES) == HAL_OK)
        {
          Q_FormatBaseOffsetNodes(p_q, new_node, Q_REPLACE_NODE);
        }
        else
        {
          return HAL_ERROR;
        }
      }
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
      if (p_q->addr_mode == HAL_Q_ADDRESSING_DIRECT)
      {
        p_q->p_set_node(head, new_node, p_q->p_get_node(head, head, offset), offset);
      }
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */

      p_q->p_set_node(0U, head, 0U, offset);
    }

    p_q->p_head_node = p_new_node;
  }
  else
  {
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
    if (p_q->addr_mode != HAL_Q_ADDRESSING_DIRECT)
    {
      if (Q_IsValidNodeAddr(p_q, head, new_node, Q_CHECK_HEAD_NODE) != HAL_OK)
      {
        return HAL_ERROR;
      }
    }
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

    if (p_old_node == p_q->p_tail_node)
    {
      prev = tail;
    }
    else
    {
      prev = old_node;
    }

    if (Q_FindNode(p_q, head, prev, &prev) != HAL_OK)
    {
      return HAL_ERROR;
    }

    if (p_old_node == p_q->p_tail_node)
    {
      p_q->p_set_node(head, prev, new_node, offset);
      p_q->p_tail_node = p_new_node;
    }
    else
    {
      p_q->p_set_node(head, new_node, p_q->p_get_node(head, old_node, offset), offset);
      p_q->p_set_node(head, prev, new_node, offset);
      p_q->p_set_node(0U, old_node, 0U, offset);
    }
  }

  return HAL_OK;
}

/**
  * @brief  Replace the head node in the Q.
  * @param  p_q               Pointer to a hal_q_t structure that contains Q information.
  * @param  p_new_node        Pointer to a new node.
  * @retval HAL_OK            In case of head node replaced successfully.
  * @retval HAL_ERROR         In case of old node not found in the Q.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  */
hal_status_t HAL_Q_ReplaceNode_Head(hal_q_t *p_q, void *p_new_node)
{
  uint32_t head;
  uint32_t new_node;
  uint32_t offset;

  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(p_q->p_head_node != NULL);
  ASSERT_DBG_PARAM(p_new_node != NULL);
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  ASSERT_DBG_PARAM(p_q->p_first_circular_node == NULL);
#endif /* USE_HAL_Q_CIRCULAR_LINK */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_q->p_head_node == NULL) || (p_new_node == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  if (p_q->p_first_circular_node != NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_Q_CIRCULAR_LINK */
#endif /* USE_HAL_CHECK_PARAM */

  head     = (uint32_t)p_q->p_head_node;
  new_node = (uint32_t)p_new_node;
  offset   = p_q->next_addr_offset;

  if (p_q->node_nbr == 1U)
  {
    p_q->p_tail_node = p_new_node;
  }
  else
  {
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
    if (p_q->addr_mode != HAL_Q_ADDRESSING_DIRECT)
    {
      if (Q_IsValidNodeAddr(p_q, head, new_node, Q_CHECK_ALL_NODES) == HAL_OK)
      {
        Q_FormatBaseOffsetNodes(p_q, new_node, Q_REPLACE_NODE);
      }
      else
      {
        return HAL_ERROR;
      }
    }
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
    if (p_q->addr_mode == HAL_Q_ADDRESSING_DIRECT)
    {
      p_q->p_set_node(head, new_node, p_q->p_get_node(head, head, offset), offset);
    }
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */

    p_q->p_set_node(0U, head, 0U, offset);
  }

  p_q->p_head_node = p_new_node;

  return HAL_OK;
}

/**
  * @brief  Replace the tail node in the Q.
  * @param  p_q               Pointer to a hal_q_t structure that contains Q information.
  * @param  p_new_node        Pointer to a new node.
  * @retval HAL_OK            In case of tail node replaced successfully.
  * @retval HAL_ERROR         In case of old node not found in the Q.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  */
hal_status_t HAL_Q_ReplaceNode_Tail(hal_q_t *p_q, void *p_new_node)
{
  uint32_t prev = 0U;
  uint32_t head;
  uint32_t tail;
  uint32_t new_node;
  uint32_t offset;

  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(p_new_node != NULL);
  ASSERT_DBG_PARAM(p_q->p_tail_node != NULL);
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  ASSERT_DBG_PARAM(p_q->p_first_circular_node == NULL);
#endif /* USE_HAL_Q_CIRCULAR_LINK */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_q->p_tail_node == NULL) || (p_new_node == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  if (p_q->p_first_circular_node != NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_Q_CIRCULAR_LINK */
#endif /* USE_HAL_CHECK_PARAM */

  head     = (uint32_t)p_q->p_head_node;
  tail     = (uint32_t)p_q->p_tail_node;
  new_node = (uint32_t)p_new_node;
  offset   = p_q->next_addr_offset;

  if (p_q->node_nbr == 1U)
  {
    p_q->p_head_node = p_new_node;
  }
  else
  {
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
    if (p_q->addr_mode != HAL_Q_ADDRESSING_DIRECT)
    {
      if (Q_IsValidNodeAddr(p_q, head, new_node, Q_CHECK_HEAD_NODE) != HAL_OK)
      {
        return HAL_ERROR;
      }
    }
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

    /* Find the tail previous node */
    if (Q_FindNode(p_q, head, tail, &prev) != HAL_OK)
    {
      return HAL_ERROR;
    }

    p_q->p_set_node(head, prev, new_node, offset);
  }

  p_q->p_tail_node = p_new_node;

  return HAL_OK;
}
/**
  * @}
  */


/** @addtogroup Q_Exported_Functions_Group5 Q inserting Q functions
  * @{
This section provides functions allowing to insert a source Q in any destination Q position :
- Call the function HAL_Q_InsertQ() to insert a source Q in any destination Q position.
- Call the function HAL_Q_InsertQ_Head() to insert a source Q before all destination Q node(s).
- Call the function HAL_Q_InsertQ_Tail() to insert a source Q after all destination Q node(s).
  */

/**
  * @brief  Insert a source Q directly after the previous node in the destination Q.
  * @param  p_dest_q Pointer to a hal_q_t structure that contains Q information.
  * @param  p_src_q  Pointer to a hal_q_t structure that contains Q information.
  * @param  p_node   Pointer to a previous node. When null, the source Q node(s) is placed at the head of destination Q.
  * @retval HAL_OK            In case of source Q inserted successfully in destination Q.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  * @retval HAL_ERROR         In case of p_prev_node node not found in the Q.
  */
hal_status_t HAL_Q_InsertQ(hal_q_t *p_dest_q, hal_q_t *p_src_q, const void *p_node)
{
  uint32_t src_head;
  uint32_t dest_head;
#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
  uint32_t src_tail;
  uint32_t dest_tail;
  uint32_t offset;
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */
  uint32_t node_addr;

  ASSERT_DBG_PARAM(p_src_q != NULL);
  ASSERT_DBG_PARAM(p_dest_q != NULL);
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  ASSERT_DBG_PARAM(p_src_q->p_first_circular_node == NULL);
  ASSERT_DBG_PARAM(p_dest_q->p_first_circular_node == NULL);
#endif /* USE_HAL_Q_CIRCULAR_LINK */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  if ((p_src_q->p_first_circular_node != NULL) || (p_dest_q->p_first_circular_node != NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_Q_CIRCULAR_LINK */
#endif /* USE_HAL_CHECK_PARAM */

  src_head  = (uint32_t)p_src_q->p_head_node;
  dest_head = (uint32_t)p_dest_q->p_head_node;
#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
  src_tail  = (uint32_t)p_src_q->p_tail_node;
  dest_tail = (uint32_t)p_dest_q->p_tail_node;
  offset    = p_dest_q->next_addr_offset;
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */
  node_addr = (uint32_t)p_node;

  /* Empty source Q */
  if (p_src_q->node_nbr == 0U)
  {
    return HAL_OK;
  }

  /* Empty destination Q */
  if (p_dest_q->p_head_node == NULL)
  {
    p_dest_q->p_head_node = p_src_q->p_head_node;
    p_dest_q->p_tail_node = p_src_q->p_tail_node;
  }
  /* Not empty destination Q */
  else
  {
    /* Insert source Q at head level of destination Q */
    if (p_node == NULL)
    {
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
      if (p_dest_q->addr_mode != HAL_Q_ADDRESSING_DIRECT)
      {
        if (Q_IsValidNodeAddr(p_dest_q, dest_head, src_head, Q_CHECK_ALL_NODES) == HAL_OK)
        {
          Q_FormatBaseOffsetQ(p_dest_q, p_src_q, src_head, Q_INSERT_Q_HEAD);
        }
        else
        {
          return HAL_ERROR;
        }
      }
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
      if (p_dest_q->addr_mode == HAL_Q_ADDRESSING_DIRECT)
      {
        /* Link source Q tail node address to destination Q head node address */
        p_src_q->p_set_node(src_head, src_tail, dest_head, offset);
      }
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */

      /* Set destination Q head node as source Q head node */
      p_dest_q->p_head_node = p_src_q->p_head_node;
    }
    else
    {
      if (Q_FindNode(p_dest_q, dest_head, node_addr, NULL) != HAL_OK)
      {
        return HAL_ERROR;
      }

#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
      if (p_dest_q->addr_mode != HAL_Q_ADDRESSING_DIRECT)
      {
        if (Q_IsValidNodeAddr(p_src_q, src_head, dest_head, Q_CHECK_ALL_NODES) == HAL_OK)
        {
          if (p_node == p_dest_q->p_tail_node)
          {
            Q_FormatBaseOffsetQ(p_dest_q, p_src_q, dest_head, Q_INSERT_Q_TAIL);
          }
          else
          {
            Q_FormatBaseOffsetQ(p_dest_q, p_src_q, node_addr, Q_INSERT_Q_MIDDLE);
          }
        }
        else
        {
          return HAL_ERROR;
        }
      }
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
      if (p_dest_q->addr_mode == HAL_Q_ADDRESSING_DIRECT)
      {
        if (p_node == p_dest_q->p_tail_node)
        {
          /* Link source Q to tail destination Q */
          p_src_q->p_set_node(dest_head, dest_tail, src_head, offset);
        }
        else
        {
          /* Link source Q to middle destination Q */
          p_dest_q->p_set_node(dest_head, src_tail, p_dest_q->p_get_node(dest_head, node_addr, offset), offset);
          p_dest_q->p_set_node(dest_head, node_addr, src_head, offset);
        }
      }
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */

      if (p_node == p_dest_q->p_tail_node)
      {
        /* Set source Q tail node as destination Q tail node */
        p_dest_q->p_tail_node = p_src_q->p_tail_node;
      }
    }
  }

  /* Set destination Q node number */
  p_dest_q->node_nbr += p_src_q->node_nbr;

  Q_ResetInfo(p_src_q);
  p_src_q->node_nbr = 0U;

  return HAL_OK;
}

/**
  * @brief  Insert a source Q in the head of destination Q.
  * @param  p_dest_q          Pointer to a hal_q_t structure that contains Q information.
  * @param  p_src_q           Pointer to a hal_q_t structure that contains Q information.
  * @retval HAL_OK            In case of head source Q inserted successfully in head destination Q.
  * @retval HAL_ERROR         In case of source Q not inserted in destination Q.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  */
hal_status_t HAL_Q_InsertQ_Head(hal_q_t *p_dest_q, hal_q_t *p_src_q)
{
  uint32_t src_head;
  uint32_t dest_head;
#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
  uint32_t src_tail;
  uint32_t offset;
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */

  ASSERT_DBG_PARAM(p_src_q != NULL);
  ASSERT_DBG_PARAM(p_dest_q != NULL);
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  ASSERT_DBG_PARAM(p_src_q->p_first_circular_node == NULL);
  ASSERT_DBG_PARAM(p_dest_q->p_first_circular_node == NULL);
#endif /* USE_HAL_Q_CIRCULAR_LINK */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  if ((p_src_q->p_first_circular_node != NULL) || (p_dest_q->p_first_circular_node != NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_Q_CIRCULAR_LINK */
#endif /* USE_HAL_CHECK_PARAM */

  src_head  = (uint32_t)p_src_q->p_head_node;
  dest_head = (uint32_t)p_dest_q->p_head_node;
#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
  src_tail  = (uint32_t)p_src_q->p_tail_node;
  offset    = p_dest_q->next_addr_offset;
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */

  if (p_src_q->node_nbr == 0U)
  {
    return HAL_OK;
  }

  /* Empty destination Q */
  if (p_dest_q->p_head_node == NULL)
  {
    p_dest_q->p_head_node = p_src_q->p_head_node;
    p_dest_q->p_tail_node = p_src_q->p_tail_node;
  }
  /* Not empty destination Q */
  else
  {
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
    if (p_dest_q->addr_mode != HAL_Q_ADDRESSING_DIRECT)
    {
      if (Q_IsValidNodeAddr(p_dest_q, dest_head, src_head, Q_CHECK_ALL_NODES) == HAL_OK)
      {
        Q_FormatBaseOffsetQ(p_dest_q, p_src_q, src_head, Q_INSERT_Q_HEAD);
      }
      else
      {
        return HAL_ERROR;
      }
    }
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
    if (p_dest_q->addr_mode == HAL_Q_ADDRESSING_DIRECT)
    {
      /* Link source Q tail node address to destination Q head node address */
      p_src_q->p_set_node(src_head, src_tail, dest_head, offset);
    }
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */

    /* Set destination Q head node as source Q head node */
    p_dest_q->p_head_node = p_src_q->p_head_node;
  }

  /* Set node number of new Q */
  p_dest_q->node_nbr += p_src_q->node_nbr;

  Q_ResetInfo(p_src_q);
  p_src_q->node_nbr = 0U;

  return HAL_OK;
}

/**
  * @brief  Insert a source Q in the tail of destination Q.
  * @param  p_dest_q          Pointer to a hal_q_t structure that contains Q information.
  * @param  p_src_q           Pointer to a hal_q_t structure that contains Q information.
  * @retval HAL_OK            In case of tail source Q inserted successfully in tail destination Q.
  * @retval HAL_ERROR         In case of source Q not inserted in destination Q.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  */
hal_status_t HAL_Q_InsertQ_Tail(hal_q_t *p_dest_q, hal_q_t *p_src_q)
{
  uint32_t src_head_addr;
  uint32_t dest_head_addr;
#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
  uint32_t dest_tail_addr;
  uint32_t offset;
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */

  ASSERT_DBG_PARAM(p_src_q != NULL);
  ASSERT_DBG_PARAM(p_dest_q != NULL);
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  ASSERT_DBG_PARAM(p_src_q->p_first_circular_node == NULL);
  ASSERT_DBG_PARAM(p_dest_q->p_first_circular_node == NULL);
#endif /* USE_HAL_Q_CIRCULAR_LINK */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  if ((p_src_q->p_first_circular_node != NULL) || (p_dest_q->p_first_circular_node != NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_Q_CIRCULAR_LINK */
#endif /* USE_HAL_CHECK_PARAM */

  src_head_addr  = (uint32_t)p_src_q->p_head_node;
  dest_head_addr = (uint32_t)p_dest_q->p_head_node;
#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
  dest_tail_addr = (uint32_t)p_dest_q->p_tail_node;
  offset         = p_dest_q->next_addr_offset;
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */

  /* Check if source Q is empty */
  if (p_src_q->node_nbr == 0U)
  {
    return HAL_OK;
  }

  /* Empty destination Q */
  if (p_dest_q->p_head_node == NULL)
  {
    p_dest_q->p_head_node   = p_src_q->p_head_node;
    p_dest_q->p_tail_node   = p_src_q->p_tail_node;
  }
  /* Not empty destination Q */
  else
  {
#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
    if (p_dest_q->addr_mode != HAL_Q_ADDRESSING_DIRECT)
    {
      if (Q_IsValidNodeAddr(p_src_q, src_head_addr, dest_head_addr, Q_CHECK_ALL_NODES) == HAL_OK)
      {
        Q_FormatBaseOffsetQ(p_dest_q, p_src_q, dest_head_addr, Q_INSERT_Q_TAIL);
      }
      else
      {
        return HAL_ERROR;
      }
    }
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

#if (USE_HAL_Q_DIRECT_ADDR_MODE) && (USE_HAL_Q_DIRECT_ADDR_MODE == 1)
    if (p_dest_q->addr_mode == HAL_Q_ADDRESSING_DIRECT)
    {
      /* Link source Q tail node address to destination Q head node address */
      p_src_q->p_set_node(dest_head_addr, dest_tail_addr, src_head_addr, offset);
    }
#endif /* USE_HAL_Q_DIRECT_ADDR_MODE */

    /* Set destination Q tail node as source Q tail node */
    p_dest_q->p_tail_node = p_src_q->p_tail_node;
  }

  /* Set node number of new Q */
  p_dest_q->node_nbr += p_src_q->node_nbr;

  Q_ResetInfo(p_src_q);
  p_src_q->node_nbr = 0U;

  return HAL_OK;
}
/**
  * @}
  */

#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
/** @addtogroup Q_Exported_Functions_Group6 Q circularizing Q functions
  * @{
This section provides functions allowing to set and clear a circular link to any node in not empty Q :
- Call the function HAL_Q_SetCircularLinkQ() to set a circular link to any node in not empty Q.
- Call the function HAL_Q_SetCircularLinkQ_Head() to set a circular link to the head Q node.
- Call the function HAL_Q_SetCircularLinkQ_Tail() to set a circular link to the tail Q node.
- Call the function HAL_Q_ClearCircularLinkQ() to clear any existent circular link in a Q.
  */

/**
  * @brief  Set circular link to any selected Q node.
  * @param  p_q               Pointer to a hal_q_t structure that contains Q information.
  * @param  p_node            Pointer to first circular node.
  * @retval HAL_OK            In case of Q is circularized.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  * @retval HAL_ERROR         In case of p_node node not found in the Q.
  */
hal_status_t HAL_Q_SetCircularLinkQ(hal_q_t *p_q, void *p_node)
{
  uint32_t head;
  uint32_t tail;
  uint32_t node;
  uint32_t offset;

  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(p_q->p_head_node != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_q->p_head_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  head   = (uint32_t)p_q->p_head_node;
  tail   = (uint32_t)p_q->p_tail_node;
  node   = (uint32_t)p_node;
  offset = p_q->next_addr_offset;

  if (Q_FindNode(p_q, head, node, NULL) == HAL_OK)
  {
    /* Link the tail node to the p_node */
    p_q->p_set_node(head, tail, node, offset);

    /* Update first circular node in Q */
    p_q->p_first_circular_node = p_node;
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief Set Q circular mode.
  * @param p_q                Pointer to a hal_q_t structure that contains Q information.
  * @retval HAL_OK            In case of Q is circularized on Head.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  */
hal_status_t HAL_Q_SetCircularLinkQ_Head(hal_q_t *p_q)
{
  uint32_t head;
  uint32_t tail;
  uint32_t offset;

  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(p_q->p_head_node != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_q->p_head_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  head   = (uint32_t)p_q->p_head_node;
  tail   = (uint32_t)p_q->p_tail_node;
  offset = p_q->next_addr_offset;

  /* Link the tail node to the head node */
  p_q->p_set_node(head, tail, head, offset);

  /* Update first circular node in Q */
  p_q->p_first_circular_node = p_q->p_head_node;

  return HAL_OK;
}

/**
  * @brief  Set Q circular mode.
  * @param  p_q               Pointer to a hal_q_t structure that contains Q information.
  * @retval HAL_OK            In case of Q is circularized on Tail.
  * @retval HAL_INVALID_PARAM In case of invalid parameter.
  */
hal_status_t HAL_Q_SetCircularLinkQ_Tail(hal_q_t *p_q)
{
  uint32_t head;
  uint32_t tail;
  uint32_t offset;

  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(p_q->p_head_node != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_q->p_tail_node ==  NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  head   = (uint32_t)p_q->p_head_node;
  tail   = (uint32_t)p_q->p_tail_node;
  offset = p_q->next_addr_offset;

  /* Link the tail node to itself */
  p_q->p_set_node(head, tail, tail, offset);

  /* Update first circular node in Q */
  p_q->p_first_circular_node = p_q->p_tail_node;

  return HAL_OK;
}

/**
  * @brief Clear circular mode of Q.
  * @param p_q     Pointer to a hal_q_t structure that contains Q information.
  * @retval HAL_OK In case of Q is Cleared.
  */
hal_status_t HAL_Q_ClearCircularLinkQ(hal_q_t *p_q)
{
  uint32_t tail;
  uint32_t offset;

  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(p_q->p_head_node != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_q->p_tail_node ==  NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  tail   = (uint32_t)p_q->p_tail_node;
  offset = p_q->next_addr_offset;

  /* Clear circular link within tail node */
  p_q->p_set_node(0U, tail, 0U, offset);

  /* Update first circular node in Q */
  p_q->p_first_circular_node = NULL;

  return HAL_OK;
}
#endif /* USE_HAL_Q_CIRCULAR_LINK */
/**
  * @}
  */

/**
  * @}
  */


/** @addtogroup Q_Private_Functions
  * @{
  */

/**
  * @brief Unlink all Q nodes.
  * @param p_q            Pointer to a hal_q_t structure that contains Q information.
  * @param head_node_addr Head node address.
  */
static void Q_UnlinkNodes(hal_q_t *p_q, uint32_t head_node_addr)
{
  uint32_t current_node = head_node_addr;
  uint32_t offset       = p_q->next_addr_offset;
  uint32_t next_node;

  /* Repeat for all Q nodes */
  while (p_q->node_nbr > 0U)
  {
    next_node = p_q->p_get_node(head_node_addr, current_node, offset);
    p_q->p_set_node(0U, current_node, 0U, offset);
    current_node = next_node;
    p_q->node_nbr--;
  }
}

/**
  * @brief Reset Q information.
  * @param p_q Pointer to a hal_q_t structure that contains Q information.
  */
static void Q_ResetInfo(hal_q_t *p_q)
{
  p_q->p_head_node           = NULL;
  p_q->p_tail_node           = NULL;
#if defined(USE_HAL_Q_CIRCULAR_LINK) && (USE_HAL_Q_CIRCULAR_LINK == 1)
  p_q->p_first_circular_node = NULL;
#endif /* USE_HAL_Q_CIRCULAR_LINK */
}

/**
  * @brief Find node in Q.
  * @param p_q              Pointer to a hal_q_t structure that contains Q information.
  * @param head_node_addr   Head node address.
  * @param node_addr        Node address to find.
  * @param p_prev_node_addr Pointer to previous Node address.
  * @retval HAL_OK          In case of node was found.
  * @retval HAL_ERROR       In case of p_first_circular_node node not found in the Q.
  */
static hal_status_t Q_FindNode(const hal_q_t *p_q, uint32_t head_node_addr, uint32_t node_addr,
                               uint32_t *p_prev_node_addr)
{
  uint32_t current_node_addr = head_node_addr;
  uint32_t offset            = p_q->next_addr_offset;
  uint32_t current_node_idx  = 0U;

  /* Loop while node not found */
  while ((current_node_addr != node_addr) && (current_node_idx < p_q->node_nbr))
  {
    if (p_prev_node_addr != NULL)
    {
      *p_prev_node_addr = current_node_addr;
    }

    current_node_addr = p_q->p_get_node(head_node_addr, current_node_addr, offset);
    current_node_idx++;
  }

  if ((current_node_idx == p_q->node_nbr) && (current_node_addr != node_addr))
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

#if (USE_HAL_Q_BASE_OFFSET_ADDR_MODE) && (USE_HAL_Q_BASE_OFFSET_ADDR_MODE == 1)
/**
  * @brief  Check the address of the node to be inserted into the Q is valid
  * @note   This function is used on case of base offset address mode
  * @param  p_q          Pointer to a hal_q_t structure that contains Q information.
  * @param  start_node   Start Node address.
  * @param  node         Node address to format.
  * @param  mode         Node operation to execute.
  * @retval HAL_OK       In case of valid node address.
  * @retval HAL_ERROR    In case of invalid node address.
  */
static hal_status_t Q_IsValidNodeAddr(const hal_q_t *p_q, uint32_t start_node, uint32_t node, q_check_nodes_t mode)
{
  uint32_t head_addr    = (uint32_t)p_q->p_head_node;
  uint32_t offset       = p_q->next_addr_offset;
  uint32_t current_addr = start_node;

  if (mode == Q_CHECK_HEAD_NODE)
  {
    if (current_addr >= node)
    {
      return HAL_ERROR;
    }
  }
  else
  {
    do
    {
      if (current_addr <= node)
      {
        return HAL_ERROR;
      }

      current_addr = p_q->p_get_node(head_addr, current_addr, offset);

    } while (current_addr != head_addr);
  }

  return HAL_OK;
}

/**
  * @brief  Format base offset nodes link.
  * @param  p_q            Pointer to a hal_q_t structure that contains Q information.
  * @param  node           Node address to format.
  * @param  node_operation Node operation to execute.
  */
static void Q_FormatBaseOffsetNodes(const hal_q_t *p_q, uint32_t node, q_operation_t node_operation)
{
  uint32_t node_num;
  uint32_t head_addr     = (uint32_t)p_q->p_head_node;
  uint32_t offset        = p_q->next_addr_offset;
  uint32_t previous_addr = node;
  uint32_t current_addr  = p_q->p_get_node(head_addr, previous_addr, offset);

  if (node_operation == Q_INSERT_NODE)
  {
    node_num = p_q->node_nbr;
  }
  else if (node_operation == Q_REMOVE_NODE)
  {
    node_num = p_q->node_nbr - 2U;
  }
  else
  {
    current_addr = p_q->p_get_node(head_addr, head_addr, offset);
    node_num     = p_q->node_nbr - 1U;
  }

  /* Repeat for all Q nodes */
  while (node_num > 0U)
  {
    p_q->p_set_node(node, (uint32_t)previous_addr, (uint32_t)current_addr, offset);
    previous_addr = current_addr;
    current_addr = p_q->p_get_node(head_addr, (uint32_t)previous_addr, offset);

    node_num--;
  }
}

/**
  * @brief Update nodes in Q.
  * @param  p_dest_q    Pointer to a hal_q_t structure that contains Q information.
  * @param  p_src_q     Pointer to a hal_q_t structure that contains Q information
  * @param  node        Previous node.
  * @param  q_operation Q operation to execute
  */
static void Q_FormatBaseOffsetQ(const hal_q_t *p_dest_q, const hal_q_t *p_src_q, uint32_t node,
                                q_operation_t q_operation)
{
  uint32_t node_num       = p_dest_q->node_nbr - 1U;
  uint32_t previous_addr  = (uint32_t)p_src_q->p_head_node;
  uint32_t src_tail_addr  = (uint32_t)p_src_q->p_tail_node;
  uint32_t dest_head_addr = (uint32_t)p_dest_q->p_head_node;
  uint32_t dest_tail_addr = (uint32_t)p_dest_q->p_tail_node;
  uint32_t dest_offset    = p_dest_q->next_addr_offset;
  uint32_t src_offset     = p_src_q->next_addr_offset;
  uint32_t current_addr   = p_dest_q->p_get_node(previous_addr, previous_addr, dest_offset);
  uint32_t set_ref_addr   = node;
  uint32_t get_ref_addr   = previous_addr;
  uint32_t src_head_addr  = previous_addr;
  uint32_t node_addr      = set_ref_addr;

  if (q_operation == Q_INSERT_Q_HEAD)
  {
    p_src_q->p_set_node(src_head_addr, src_tail_addr, dest_head_addr, src_offset);

    previous_addr = dest_head_addr;
    current_addr  = p_dest_q->p_get_node(dest_head_addr, dest_head_addr, src_offset);
    get_ref_addr  = dest_head_addr;
  }
  else if (q_operation == Q_INSERT_Q_MIDDLE)
  {
    set_ref_addr = dest_head_addr;
  }
  else
  {
    p_dest_q->p_set_node(node_addr, dest_tail_addr, src_head_addr, dest_offset);
  }

  while (node_num > 0U)
  {
    p_dest_q->p_set_node((uint32_t)set_ref_addr, (uint32_t)previous_addr, (uint32_t)current_addr, dest_offset);
    previous_addr = current_addr;
    current_addr = p_src_q->p_get_node(get_ref_addr, (uint32_t)previous_addr, src_offset);

    node_num--;
  }

  if (q_operation == Q_INSERT_Q_MIDDLE)
  {
    previous_addr = src_tail_addr;
    current_addr  = p_dest_q->p_get_node(dest_head_addr, node_addr, dest_offset);

    do
    {
      p_dest_q->p_set_node(dest_head_addr, (uint32_t)previous_addr, (uint32_t)current_addr, dest_offset);
      previous_addr = current_addr;
      current_addr = p_dest_q->p_get_node(dest_head_addr, (uint32_t)previous_addr, dest_offset);
    } while (current_addr != dest_head_addr);

    p_dest_q->p_set_node(dest_head_addr, node_addr, src_head_addr, dest_offset);

  }
}
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */
/**
  * @}
  */

#endif /* USE_HAL_Q_DIRECT_ADDR_MODE || USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

/**
  * @}
  */

/**
  * @}
  */
