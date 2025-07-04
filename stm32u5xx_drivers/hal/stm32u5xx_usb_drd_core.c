/**
  ******************************************************************************
  * @file    stm32u5xx_usb_drd_core.c
  * @brief   USB DRD Core driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the USB Peripheral Controller:
  *           + Initialization/de-initialization functions
  *           + I/O operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
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
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
    [..]
      (#) Fill parameters of peripheral configuration structure.

      (#) Call USB_DRD_InitCore() API to initialize the USB Core peripheral.

      (#) The upper HAL HCD/PCD driver will call the right routines for its internal processes.

  @endverbatim

  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_usb_drd_core.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */
#if defined (USB_DRD_FS)
/** @addtogroup USB_DRD_CORE USB DRD CORE
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint16_t  phy_chin_state[USB_DRD_MAX_CHEP_NBR];  /*!< Physical Channel in State (Used/Free) */
static uint16_t  phy_chout_state[USB_DRD_MAX_CHEP_NBR]; /*!< Physical Channel out State (Used/Free) */
static uint32_t  PMALookupTable[PMA_BLOCKS]; /*!< PMA LookUp Table */

static usb_drd_ep_config_t chep0; /*!< host channel Endpoint0 configuration */
static usb_drd_ep_db_config_t ep_db_state; /*!< Endpoint double buffer state */

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup USB_DRD_CORE_Private_Functions USB Core Low Layer Private Functions
  * @{
  */
static usb_core_status_t USB_DRD_ResetCore(uint32_t instance);

static usb_core_status_t USB_DRD_CH_BULK_DB_StartXfer(uint32_t instance, usb_core_ch_t *p_ch,
                                                      uint32_t ch_reg, uint32_t *p_length);

static usb_core_status_t USB_DRD_CH_ISO_DB_StartXfer(uint32_t instance, usb_core_ch_t *p_ch,
                                                     uint32_t size_byte);

static uint8_t USB_DRD_IsUsedChannel(usb_core_channel_t ch_num);
static usb_core_phy_ch_t USB_DRD_GetFreePhysicalChannel(const usb_core_ch_t *p_ch);
static uint16_t USB_DRD_GetFreePMA(uint16_t mps);
static usb_core_status_t USB_DRD_PMAFree(uint32_t pma_base, uint16_t mps);
static usb_core_status_t USB_DRD_PMAlloc(usb_core_ch_t *p_ch, uint16_t ch_kind);
static usb_core_status_t USB_DRD_PMADeAlloc(usb_core_ch_t *p_ch);
/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/
/** @addtogroup USB_DRD_CORE_Private_Functions USB Core Low Layer Private Functions
  * @{
  */

/**
  * @brief  Reset the USB Core (needed after USB clock settings change)
  * @param  instance Selected device
  * @retval HAL status
  */
static usb_core_status_t USB_DRD_ResetCore(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  /* Disable Host Mode */
  p_usb->CNTR &= ~USB_CNTR_HOST;

  /* Force Reset IP */
  p_usb->CNTR |= USB_CNTR_USBRST;

  return USB_CORE_OK;
}

/**
  * @brief  Start Transfer of Channel bulk out double buffer.
  * @param  instance Selected device.
  * @param  p_ch pointer to Host Channel structure.
  * @param  ch_reg snapshot of the CHEPR register.
  * @param  p_length Transfer Length pointer.
  * @retval DRD Core status
  */
static usb_core_status_t USB_DRD_CH_BULK_DB_StartXfer(uint32_t instance, usb_core_ch_t *p_ch,
                                                      uint32_t ch_reg, uint32_t *p_length)
{
  /* Double Buffer Management */
  if (p_ch->xfer_size > p_ch->max_packet)
  {
    /* Enable double buffer mode */
    (void)USB_DRD_SetChannelDoubleBuffer(instance, p_ch->phy_ch_num, USB_DRD_BULK_DB_ENBALE);
    *p_length = p_ch->max_packet;
    p_ch->xfer_size -= *p_length;

    /* Prepare two buffer before enabling host */
    if ((ch_reg & USB_CH_DTOG_TX) == 0U)
    {
      /* Write Buffer0 */
      USB_DRD_SET_CHEP_DBUF0_CNT(instance, p_ch->phy_ch_num, USB_CORE_EP_IN_DIR, (uint16_t)*p_length);
      USB_DRD_WritePMA(instance, p_ch->p_xfer_buffer, p_ch->pma_addr0, (uint16_t)*p_length);
    }
    else
    {
      /* Write Buffer1 */
      USB_DRD_SET_CHEP_DBUF1_CNT(instance, p_ch->phy_ch_num, USB_CORE_EP_IN_DIR, (uint16_t)*p_length);
      USB_DRD_WritePMA(instance, p_ch->p_xfer_buffer, p_ch->pma_addr1, (uint16_t)*p_length);
    }

    p_ch->p_xfer_buffer += *p_length;

    /* Multi packet transfer */
    if (p_ch->xfer_size > p_ch->max_packet)
    {
      p_ch->xfer_size -= *p_length;
    }
    else
    {
      *p_length = p_ch->xfer_size;
      p_ch->xfer_size = 0U;
    }

    if ((ch_reg & USB_CH_DTOG_TX) == 0U)
    {
      /* Write Buffer1 */
      USB_DRD_SET_CHEP_DBUF1_CNT(instance, p_ch->phy_ch_num, USB_CORE_EP_IN_DIR, (uint16_t)*p_length);
      USB_DRD_WritePMA(instance, p_ch->p_xfer_buffer, p_ch->pma_addr1, (uint16_t)*p_length);
    }
    else
    {
      /* Write Buffer0 */
      USB_DRD_SET_CHEP_DBUF0_CNT(instance, p_ch->phy_ch_num, USB_CORE_EP_IN_DIR, (uint16_t)*p_length);
      USB_DRD_WritePMA(instance, p_ch->p_xfer_buffer, p_ch->pma_addr0, (uint16_t)*p_length);
    }
  }
  else
  {
    /* Disable bulk double buffer mode */
    (void)USB_DRD_SetChannelDoubleBuffer(instance, p_ch->phy_ch_num, USB_DRD_BULK_DB_DISABLE);

    USB_DRD_WritePMA(instance, p_ch->p_xfer_buffer, p_ch->pma_addr0, (uint16_t)*p_length);
    USB_DRD_SET_CHEP_TX_CNT(instance, p_ch->phy_ch_num, (uint16_t)*p_length);
  }

  return USB_CORE_OK;
}

/**
  * @brief  Start Transfer of Channel isochronous out double buffer.
  * @param  instance Selected device.
  * @param  p_ch pointer to Host Channel structure.
  * @param  size_byte Transfer Length.
  * @retval DRD Core status
  */
static usb_core_status_t USB_DRD_CH_ISO_DB_StartXfer(uint32_t instance, usb_core_ch_t *p_ch, uint32_t size_byte)
{
  /* Check the DTOG_TX to determine in which buffer to write */
  if ((USB_DRD_GET_CHEP(instance, p_ch->phy_ch_num) & USB_CH_DTOG_TX) != 0U)
  {
    USB_DRD_SET_CHEP_DBUF0_CNT(instance, p_ch->phy_ch_num, USB_CORE_EP_IN_DIR, size_byte);
    USB_DRD_WritePMA(instance, p_ch->p_xfer_buffer, p_ch->pma_addr0, (uint16_t)size_byte);
  }
  else
  {
    /* DTOGTX=0 */
    /* Set the Double buffer counter for pmabuffer0 */
    USB_DRD_SET_CHEP_DBUF1_CNT(instance, p_ch->phy_ch_num, USB_CORE_EP_IN_DIR, size_byte);
    USB_DRD_WritePMA(instance, p_ch->p_xfer_buffer, p_ch->pma_addr1, (uint16_t)size_byte);
  }

  return USB_CORE_OK;
}

/**
  * @brief  Check if the ch_num is already reserved to a physical channel.
  * @param  ch_num  Channel number
  *         This parameter can be a value from 0 to 15.
  * @retval status
  */
static uint8_t USB_DRD_IsUsedChannel(usb_core_channel_t ch_num)
{
  uint8_t idx;

  /* Check if the logical channel are already opened  */
  for (idx = 0U; idx < USB_DRD_MAX_CHEP_NBR; idx++)
  {
    if ((((phy_chin_state[idx] & 0xF0U) >> 4U) == ((uint16_t)ch_num + 1U)) && (phy_chin_state[idx] != 0U))
    {
      return (1U | (idx << 4U));
    }

    if ((((phy_chout_state[idx] & 0xF0U) >> 4U) == ((uint16_t)ch_num + 1U)) && (phy_chout_state[idx] != 0U))
    {
      return (1U | (idx << 4U));
    }
  }

  return 0U;
}

/**
  * @brief  Get a free physical Channel number according to the direction.
  * @param  p_ch Host Channel.
  * @retval if physical channel is available return Phy_channel number
  *       else return USB_DRD_FREE_CH_NOT_FOUND.
  */
static usb_core_phy_ch_t USB_DRD_GetFreePhysicalChannel(const usb_core_ch_t *p_ch)
{
  uint8_t idx;

  if (p_ch->ch_dir == USB_CORE_CH_OUT_DIR)
  {
    idx = 0U;

    if (p_ch->ch_num == USB_CORE_CHANNEL_0)
    {
      if (phy_chin_state[idx] == 0U)
      {
        /* Chin_state to store the ep_type to be used for the same channel in OUT direction
         * adding + 1 to ep_type avoid starting with a 0 value. ep_type take by default (0/1/2/3) */
        phy_chin_state[idx] = (((uint16_t)p_ch->ch_num + 1U) << 4U) |
                              ((uint16_t)p_ch->ep_type + 1U) |
                              ((uint16_t)p_ch->ep_num << 8U);
      }

      if (phy_chout_state[idx] == 0U)
      {
        /* Chout_state will store the ep_type to be used for the same channel in IN direction
         * adding + 1 to ep_type avoid starting with a 0 value. ep_type take by default (0/1/2/3) */
        phy_chout_state[idx] = (((uint16_t)p_ch->ch_num + 1U) << 4U) |
                               ((uint16_t)p_ch->ep_type + 1U) |
                               ((uint16_t)p_ch->ep_num << 8U);
      }
    }
    else
    {
      /* Find a new available physical in channel */
      for (idx = 1U; idx < USB_DRD_MAX_CHEP_NBR; idx++)
      {

        /* Check if the same ep_num is allocated then allocate the same physical channel IN for OUT Logical Channel */
        if ((phy_chout_state[idx] == 0U) && ((((phy_chin_state[idx] & 0x0FU) == ((uint16_t)p_ch->ep_type + 1U))
                                              && ((phy_chin_state[idx] & 0x0F00U) == (uint16_t)p_ch->ep_num))
                                             || (phy_chin_state[idx] == 0U)))
        {
          /* chout_state will store the ep_type to be used for the same channel in IN direction
           * adding + 1 to ep_type avoid starting with a 0 value. ep_type take by default (0/1/2/3) */
          phy_chout_state[idx] = (((uint16_t)p_ch->ch_num + 1U) << 4U) |
                                 ((uint16_t)p_ch->ep_type + 1U) |
                                 ((uint16_t)p_ch->ep_num << 8U);

          return (usb_core_phy_ch_t)idx;
        }
      }
    }
    return (usb_core_phy_ch_t)idx;
  }

  if (p_ch->ch_dir == USB_CORE_CH_IN_DIR)
  {
    /* Find a new available physical in channel */
    for (idx = 1U; idx < USB_DRD_MAX_CHEP_NBR; idx++)
    {
      /* Check if the same ep_num is allocated then allocate the same physical channel OUT for IN Logical Channel */
      if ((phy_chin_state[idx] == 0U) && ((((phy_chout_state[idx] & 0x000FU) == ((uint16_t)p_ch->ep_type + 1U))
                                           && (((phy_chout_state[idx] & 0x0F00U) == (uint16_t)p_ch->ep_num)))
                                          || (phy_chout_state[idx] == 0U)))
      {
        /* Store the ep_type to be used for the same channel in OUT direction
         * adding + 1 to ep_type avoid starting with a 0 value. ep_type take by default (0/1/2/3) */
        phy_chin_state[idx] = (((uint16_t)p_ch->ch_num + 1U) << 4U) |
                              ((uint16_t)p_ch->ep_type + 1U) |
                              ((uint16_t)p_ch->ep_num << 8U);

        return (usb_core_phy_ch_t)idx;
      }
    }
  }
  else
  {
    /* Find a new available physical out channel */
    for (idx = 1U; idx < USB_DRD_MAX_CHEP_NBR; idx++)
    {
      /* Check if the same ep_num is allocated then allocate the same physical channel IN for OUT Logical Channel */
      if ((phy_chout_state[idx] == 0U) && ((((phy_chin_state[idx] & 0x0FU) == ((uint16_t)p_ch->ep_type + 1U))
                                            && ((phy_chin_state[idx] & 0x0F00U) == (uint16_t)p_ch->ep_num))
                                           || (phy_chin_state[idx] == 0U)))
      {
        /* chout_state will store the ep_type to be used for the same channel in IN direction
         * adding + 1 to ep_type avoid starting with a 0 value. ep_type take by default (0/1/2/3) */
        phy_chout_state[idx] = (((uint16_t)p_ch->ch_num + 1U) << 4U) |
                               ((uint16_t)p_ch->ep_type + 1U) |
                               ((uint16_t)p_ch->ep_num << 8U);

        return (usb_core_phy_ch_t)idx;
      }
    }
  }

  /* Return error */
  return USB_CORE_PHY_CHEP_FF;
}

/**
  * @brief  Fetch in the PMA_LockupTable free space of number of mps byte
  * @param  mps  Channel Max Packet Size
  * @retval PMA_Address of the first free block containing mps byte
            0xFFFF in case of no space available
  */
static uint16_t USB_DRD_GetFreePMA(uint16_t mps)
{
  uint32_t entry;
  uint32_t free_blocks = 0U;
  uint8_t first_free_block_col = 0U;
  uint8_t first_free_block_line = 0U;
  uint8_t col_idx;
  uint16_t nbr_req_blocks;
  uint16_t mps_t = mps;

  /* Since PMA buffer descriptor RXBD allocate address according to BLSIZE, BLSIZE=1==> mps>64
    allocation in PMA is done in 32Bytes each entry */
  if ((mps_t > 64U) && ((mps_t % 32U) != 0U))
  {
    /* Align the mps to 32byte block to match the allocation in PMA,
      check Definition of allocation buffer memory in usb user spec */
    mps_t = (uint16_t)(((mps_t / 32U) + 1U) * 32U);
  }

  /* Calculate the number of block(8byte) to allocate */
  nbr_req_blocks = mps_t / 8U;

  /* Check if we need remaining Block */
  if ((mps_t % 8U) != 0U)
  {
    nbr_req_blocks++;
  }

  /* Look For nbr_req_blocks * Empty Block */
  for (uint8_t i = 0U; ((i < PMA_BLOCKS) && (free_blocks != nbr_req_blocks)); i++)
  {
    entry = PMALookupTable[i];

    /* Check the first col to look for a contiguous block */
    if ((free_blocks != 0U) && ((entry & (uint32_t)1U) != 0U))
    {
      free_blocks = 0U;
    }
    uint8_t j = 0U;
    while ((j <= 31U) && (free_blocks != nbr_req_blocks))
    {
      /* Check if block j is free */
      if ((entry & ((uint32_t)1U << j)) == 0U)
      {
        if (free_blocks == 0U)
        {
          first_free_block_col = j;
          first_free_block_line = i;
          free_blocks++;
        }
        j++;

        /* Parse Column PMALockTable */
        while ((j <= 31U) && ((entry & ((uint32_t)1U << j)) == 0U) && (free_blocks < nbr_req_blocks))
        {
          free_blocks++;
          j++;
        }

        /* Free contiguous Blocks not found */
        if (((free_blocks < nbr_req_blocks) && (j < 31U)) || ((j == 31U) && ((entry & ((uint32_t)1U << j)) != 0U)))
        {
          free_blocks = 0U;
        }
      }
      j++;
    } /* End for j */
  } /* End for i */

  /* Free block found */
  if (free_blocks >= nbr_req_blocks)
  {
    col_idx = first_free_block_col;

    for (uint8_t i = first_free_block_line; ((i < PMA_BLOCKS) && (free_blocks > 0U)); i++)
    {
      for (uint8_t j = col_idx; j <= 31U; j++)
      {
        PMALookupTable[i] |= ((uint32_t)1U << j);

        if (--free_blocks == 0U)
        {
          break;
        }
      }
      col_idx = 0U;
    }

    return (uint16_t)((first_free_block_line * (uint16_t)256U) + (first_free_block_col * (uint16_t)8U));
  }
  else
  {
    return 0xFFFFU;
  }
}

/**
  * @brief  PMA Free
  * @param  pma_base PMA base offset
  * @param  mps  Max Packet Size
  * @retval status
  */
static usb_core_status_t USB_DRD_PMAFree(uint32_t pma_base, uint16_t mps)
{
  uint32_t block_nbr;
  uint8_t col_idx;
  uint8_t line_idx;
  uint16_t mps_t = mps;

  /* Since PMA buffer descriptor RXBD allocate address according to BLSIZE, BLSIZE=1==> mps>64
    allocation in PMA is done in 32Bytes each entry */
  if ((mps_t > 64U) && ((mps_t % 32U) != 0U))
  {
    /* Align the mps to 32byte block to match the allocation in PMA,
      check Definition of allocation buffer memory in usb user spec */
    mps_t = (uint16_t)(((mps_t / 32U) + 1U) * 32U);
  }

  /* Calculate the number of needed block to Free */
  if ((mps_t / 8U) != 0U)
  {
    block_nbr = ((uint32_t)mps_t / 8U);

    if ((mps_t % 8U) != 0U)
    {
      block_nbr++;
    }
  }
  else
  {
    block_nbr = 1U;
  }

  /* Decode Col/Line of PMA_Base position in the PMA_LookupTable */
  if (pma_base > 256U)
  {
    line_idx = (uint8_t)(pma_base / 256U);
    col_idx = (uint8_t)((pma_base - ((uint32_t)line_idx * 256U)) / 8U);
  }
  else
  {
    line_idx = 0U;
    col_idx = (uint8_t)(pma_base / 8U);
  }

  /* Reset the corresponding bit in the lookupTable */
  for (uint8_t i = line_idx; ((i < PMA_BLOCKS) && (block_nbr > 0U)); i++)
  {
    for (uint8_t j = col_idx; j <= 31U; j++)
    {
      /* Check if the block is not already reserved or it was already closed */
      if ((PMALookupTable[i] & ((uint32_t)1UL << j)) == 0U)
      {
        return USB_CORE_ERROR;
      }
      /* Free the reserved block by resetting the corresponding bit */
      PMALookupTable[i] &= ~(1UL << j);

      if (--block_nbr == 0U)
      {
        break;
      }
    }
    col_idx = 0U;
  }

  return USB_CORE_OK;
}

/**
  * @brief  Allocate PMA buffer for Channel
  *         This API will fetch a free space
  * @param  p_ch pointer to channel
  * @param  ch_kind endpoint Kind
  *                  USB_SNG_BUF Single Buffer used
  *                  USB_DBL_BUF Double Buffer used
  * @retval status
  */
static usb_core_status_t USB_DRD_PMAlloc(usb_core_ch_t *p_ch, uint16_t ch_kind)
{
  uint16_t pma_addr0;
  uint16_t pma_addr1; /* Used for double buffer mode if enabled */

  /* Get a FreePMA Address */
  pma_addr0 = USB_DRD_GetFreePMA(p_ch->max_packet);

  /* Check allocated pma address */
  if (pma_addr0 == 0xFFFFU)
  {
    return USB_CORE_ERROR;
  }
  else
  {
    /* Check if the endpoint is single or double Buffer */
    if (ch_kind == (uint16_t)USB_DRD_SNG_BUF)
    {
      /* Single Buffer */
      p_ch->double_buffer_en = (uint8_t)USB_CORE_CONFIG_DISABLED;

      if (p_ch->ep_num == USB_CORE_ENDPOINT_0)
      {
        chep0.virtual_ch_num = p_ch->ch_num;
        chep0.is_allocated = 1U;
        p_ch->max_packet = 64U;
      }

      /* Configure the PMA */
      if (p_ch->ch_dir == USB_CORE_CH_IN_DIR)
      {
        p_ch->pma_addr1 = pma_addr0;
        (USB_DRD_PMA_BUFF + (uint32_t)p_ch->phy_ch_num)->RXBD = p_ch->pma_addr1;

        if (p_ch->ep_num == USB_CORE_ENDPOINT_0)
        {
          chep0.dir = USB_CORE_EP_IN_DIR;
          chep0.pma_addr1 = p_ch->pma_addr1;
        }
      }
      else
      {
        p_ch->pma_addr0 = pma_addr0;
        (USB_DRD_PMA_BUFF + (uint32_t)p_ch->phy_ch_num)->TXBD = p_ch->pma_addr0;

        if (p_ch->ep_num == USB_CORE_ENDPOINT_0)
        {
          chep0.pma_addr0 = p_ch->pma_addr0;
        }
      }

      /* Set the PmaAddress */
      p_ch->pma_address = pma_addr0;
    }
    else /* USB_DBL_BUF */
    {
      /* Double Buffer Endpoint */
      p_ch->double_buffer_en = (uint8_t)USB_CORE_CONFIG_ENABLED;

      /* Get a FreePMA Address for buffer 2 */
      pma_addr1 = USB_DRD_GetFreePMA(p_ch->max_packet);

      if (pma_addr1 == 0xFFFFU)
      {
        /* Free the first buffer */
        (void)USB_DRD_PMAFree(pma_addr0, p_ch->max_packet);
        return USB_CORE_ERROR;
      }
      else
      {
        /* Configure the PMA */
        p_ch->pma_addr0 = (uint16_t)(pma_addr0);
        p_ch->pma_addr1 = (uint16_t)(pma_addr1);

        /* Set Buffer0 pma address */
        (USB_DRD_PMA_BUFF + (uint32_t)p_ch->phy_ch_num)->TXBD = pma_addr0;

        /* Set Buffer1 pma address */
        (USB_DRD_PMA_BUFF + (uint32_t)p_ch->phy_ch_num)->RXBD = pma_addr1;

        /* Used for Bulk DB MPS < 64bytes */
        if (p_ch->ch_dir == USB_CORE_CH_IN_DIR)
        {
          p_ch->pma_address = p_ch->pma_addr1;
        }
        else
        {
          p_ch->pma_address = p_ch->pma_addr0;
        }
      }
    }
  }

  return USB_CORE_OK;
}

/**
  * @brief  PMA De-Allocation for Channel Free the reserved block in the PMA-LookupTable
  * @param  p_ch pointer to Host Channel
  * @retval status
  */
static usb_core_status_t USB_DRD_PMADeAlloc(usb_core_ch_t *p_ch)
{
  usb_core_status_t status;
  uint8_t error = 0U;

  /* Single Buffer */
  if (p_ch->double_buffer_en == (uint8_t)USB_CORE_CONFIG_DISABLED)
  {
    status = USB_DRD_PMAFree(p_ch->pma_address, p_ch->max_packet);
  }
  else   /* Double buffer */
  {
    status = USB_DRD_PMAFree(p_ch->pma_addr0, p_ch->max_packet);
    if (status != USB_CORE_OK)
    {
      error++;
    }

    status = USB_DRD_PMAFree(p_ch->pma_addr1, p_ch->max_packet);
    if (status != USB_CORE_OK)
    {
      error++;
    }

    if (error != 0U)
    {
      return USB_CORE_ERROR;
    }
  }

  return status;
}
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup USB_DRD_CORE_Exported_Functions USB Core Low Layer Exported Functions
  * @{
  */

/**
  * @brief  Initializes the USB Core
  * @param  instance USB Instance
  * @param  p_core_config USB Instance configuration parameters
  *         for the specified USB peripheral.
  * @retval HAL status
  */
usb_core_status_t USB_DRD_InitCore(uint32_t instance, const usb_core_config_params_t *p_core_config)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);
  usb_core_status_t ret;
  STM32_UNUSED(p_core_config);

  /* Reset after a PHY select */
  ret = USB_DRD_ResetCore(instance);

  /* Clear pending interrupts */
  p_usb->ISTR = 0U;

  return ret;
}

/**
  * @brief  Initializes the USB Core
  * @param  instance USB Instance
  * @retval HAL status
  */
usb_core_status_t USB_DRD_DeInitCore(uint32_t instance)
{
  STM32_UNUSED(instance);
  uint8_t idx;

  /* Reset PMA Address */
  (void)USB_DRD_PMAReset();

  for (idx = 0U; idx < USB_DRD_MAX_CHEP_NBR; idx++)
  {
    phy_chin_state[idx] = 0U;
    phy_chout_state[idx] = 0U;
  }

  return USB_CORE_OK;
}

/**
  * @brief  Enable Global Interrupt
  *         Enables the controller's Global Int in the AHB Config reg
  * @param  instance Selected device
  * @retval HAL status
  */
usb_core_status_t USB_DRD_EnableGlobalInterrupt(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);
  uint32_t winterruptmask;

  /* Clear pending interrupts */
  p_usb->ISTR = 0U;

  /* Set winterruptmask variable */
  winterruptmask = USB_CNTR_CTRM  | USB_CNTR_WKUPM |
                   USB_CNTR_SUSPM | USB_CNTR_ERRM |
                   USB_CNTR_SOFM | USB_CNTR_ESOFM |
                   USB_CNTR_RESETM | USB_CNTR_L1REQM;

  /* Set interrupt mask */
  p_usb->CNTR = winterruptmask;

  return USB_CORE_OK;
}

/**
  * @brief  Disable Global Interrupt
  *         Disable the controller's Global Int in the AHB Config reg
  * @param  instance Selected device
  * @retval HAL status
  */
usb_core_status_t USB_DRD_DisableGlobalInterrupt(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);
  uint32_t winterruptmask;

  /* Set winterruptmask variable */
  winterruptmask = USB_CNTR_CTRM  | USB_CNTR_WKUPM |
                   USB_CNTR_SUSPM | USB_CNTR_ERRM |
                   USB_CNTR_SOFM | USB_CNTR_ESOFM |
                   USB_CNTR_RESETM | USB_CNTR_L1REQM;

  /* Clear interrupt mask */
  p_usb->CNTR &= ~winterruptmask;

  return USB_CORE_OK;
}

/**
  * @brief  Set current functional mode
  * @param  instance Selected device
  * @param  core_mode current core mode
  *          This parameter can be one of the these values:
  *            @arg USB_CORE_XXX_MODE Peripheral mode
  * @retval HAL status
  */
usb_core_status_t USB_DRD_SetCurrentMode(uint32_t instance, usb_core_mode_t core_mode)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  if (core_mode == USB_CORE_DEVICE_MODE)
  {
    p_usb->CNTR &= ~USB_CNTR_HOST;
  }
  else if (core_mode == USB_CORE_HOST_MODE)
  {
    p_usb->CNTR |= USB_CNTR_HOST;
  }
  else
  {
    return USB_CORE_ERROR;
  }

  return USB_CORE_OK;
}

/**
  * @brief  Returns USB core mode
  * @param  instance  Selected device
  * @retval return core mode : Host or Device
  *          This parameter can be one of these values:
  *           0 : USB_CORE_DEVICE_MODE
  *           1 : USB_CORE_HOST_MODE
  */
usb_core_mode_t USB_DRD_GetCurrentMode(uint32_t instance)
{
  const usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);
  uint32_t current_mode = (p_usb->CNTR & USB_CNTR_HOST) >> 31U;

  return (usb_core_mode_t)current_mode;
}

/**
  * @brief  USB_DRD_ReadInterrupts return the global USB interrupt status
  * @param  instance Selected device
  * @retval USB Global Interrupt status
  */
uint32_t USB_DRD_ReadInterrupts(uint32_t instance)
{
  const usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);
  uint32_t istr_reg;

  istr_reg = p_usb->ISTR;
  return istr_reg;
}

/**
  * @brief  USB_DRD_ClearInterrupts clear USB interrupt flags
  * @param  instance Selected device
  * @param  interrupt Interrupt flag
  */
void USB_DRD_ClearInterrupts(uint32_t instance, uint32_t interrupt)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);
  p_usb->ISTR &= (uint16_t)(~interrupt);
}

/**
  * @brief  Copy a buffer from user memory area to packet memory area (PMA)
  * @param  instance USB peripheral instance register address
  * @param  p_src pointer to user memory area
  * @param  pma_address pma buffer address
  * @param  size_byte number of bytes to be copied to packet memory area
  */
void USB_DRD_WritePMA(uint32_t instance, uint8_t *p_src, uint16_t pma_address, uint16_t size_byte)
{
  STM32_UNUSED(instance);
  __IO uint32_t *p_pma_buffer_addr;
  uint32_t remaining_data;
  uint32_t count;
  uint32_t count32b = ((uint32_t)size_byte + 3U) >> 2U;
  /* Due to the PMA access 32bit only so the last non word data to be processed alone */
  uint16_t remaining_bytes = size_byte % 4U;
  uint8_t *p_src_buffer = p_src;

  /* Check if there is a remaining byte */
  if (remaining_bytes != 0U)
  {
    count32b--;
  }

  /* Get the PMA Buffer pointer */
  p_pma_buffer_addr = (__IO uint32_t *)(USB_DRD_PMAADDR + (uint32_t)pma_address);

  /* Write the Calculated Word into the PMA related Buffer */
  for (count = count32b; count != 0U; count--)
  {
    *p_pma_buffer_addr = __UNALIGNED_UINT32_READ(p_src_buffer);
    p_pma_buffer_addr++;
    /* Increment p_src_buffer 4 Time as Word Increment */
    p_src_buffer++;
    p_src_buffer++;
    p_src_buffer++;
    p_src_buffer++;
  }

  /* When Number of data is not word aligned, write the remaining Byte */
  if (remaining_bytes != 0U)
  {
    remaining_data = 0U;

    do
    {
      remaining_data |= (uint32_t)(*(uint8_t *)p_src_buffer) << (8U * count);
      count++;
      p_src_buffer++;
      remaining_bytes--;
    } while (remaining_bytes != 0U);

    *p_pma_buffer_addr = remaining_data;
  }
}

/**
  * @brief Copy data from packet memory area (PMA) to user memory buffer
  * @param   instance USB peripheral instance register address.
  * @param   p_dest pointer to user memory area
  * @param   pma_address address into PMA
  * @param   size_byte number of bytes to be copied to user memory buffer
  */
void USB_DRD_ReadPMA(uint32_t instance, uint8_t *p_dest, uint16_t pma_address, uint16_t size_byte)
{
  STM32_UNUSED(instance);
  __IO uint32_t *p_pma_buffer_addr;
  uint32_t count;
  uint32_t remaining_data;
  uint32_t count32b = ((uint32_t)size_byte + 3U) >> 2U;

  /* Due to the PMA access 32bit only so the last non word data to be processed alone */
  uint16_t remaining_bytes = size_byte % 4U;
  uint8_t *p_dest_Buffer = p_dest;

  /* Get the PMA Buffer pointer */
  p_pma_buffer_addr = (__IO uint32_t *)(USB_DRD_PMAADDR + (uint32_t)pma_address);

  /* If number of byte is not word aligned decrement the number of word */
  if (remaining_bytes != 0U)
  {
    count32b--;
  }

  /* Read data packet From the PMA Buffer */
  for (count = count32b; count != 0U; count--)
  {
    __UNALIGNED_UINT32_WRITE(p_dest_Buffer, *p_pma_buffer_addr);

    p_pma_buffer_addr++;
    p_dest_Buffer++;
    p_dest_Buffer++;
    p_dest_Buffer++;
    p_dest_Buffer++;
  }

  /* When Number of data is not word aligned, read the remaining byte */
  if (remaining_bytes != 0U)
  {
    remaining_data = *(__IO uint32_t *)p_pma_buffer_addr;

    do
    {
      *(uint8_t *)p_dest_Buffer = (uint8_t)(remaining_data >> (8U * (uint8_t)(count)));
      count++;
      p_dest_Buffer++;
      remaining_bytes--;
    } while (remaining_bytes != 0U);
  }
}

/*----------------------  PMA Allocation Section --------------------- */
/*
                __col31________________col0__   Column-- >
          lin0 | entry31.|.......  | entry0 |   Line
               |---------|---------|--------|    |
          line1| entry63.|.......  | entry32|    |
               |---------|---------|--------|   \|/
               | entry127|.......  | entry64|
               |---------|---------|--------|
               | entry256|......   |entry128|
                ----------------------------
           an allocation space of 64byte need 8 Free contiguous entry in the Matrix
           - a Free entry is a bit with 0 Value/  a busy entry is a bit with 1 value. */


/**
  * @brief  PMA Reset
  * @retval status
  */
usb_core_status_t USB_DRD_PMAReset(void)
{
  uint16_t index;

  /* Reset All PMA entry */
  for (index = 0U; index < PMA_BLOCKS; index++)
  {
    PMALookupTable[index] = 0U;
  }

  /* Allocate a Space for buffer descriptor table depending on the Host channel number */
  for (index = 0U; index < USB_DRD_MAX_CHEP_NBR; index++)
  {
    PMALookupTable[0] |= ((uint32_t)1UL << index);
  }

  /* Reset Ep0 Pma allocation state */
  chep0.virtual_ch_num = USB_CORE_CHANNEL_FF;
  chep0.dir = USB_CORE_EP_OUT_DIR;
  chep0.is_allocated = 0U;
  chep0.is_dual_allocated = 0U;
  chep0.pma_addr0 = 0U;
  chep0.pma_addr1 = 0U;

  return USB_CORE_OK;
}
/**
  * @}
  */

/** @defgroup USB_DRD_CORE_Device_Exported_Functions USB Core Device Low Layer Exported Functions
  * @{
  */

/**
  * @brief  Initialize the USB DRD PCD Driver
  * @param  p_driver pointer to USB PCD driver structure
  * @retval HAL status
  */
usb_core_status_t USB_DRD_PCD_InitDriver(usb_core_pcd_driver_t *p_driver)
{
  p_driver->core_init = USB_DRD_InitCore;
  p_driver->core_set_mode = USB_DRD_SetCurrentMode;
  p_driver->core_get_mode = USB_DRD_GetCurrentMode;
  p_driver->core_enable_interrupts = USB_DRD_EnableGlobalInterrupt;
  p_driver->core_disable_interrupts = USB_DRD_DisableGlobalInterrupt;
  p_driver->device_init = USB_DRD_InitDevice;
  p_driver->device_start = USB_DRD_StartDevice;
  p_driver->device_stop = USB_DRD_StopDevice;
  p_driver->device_connect = USB_DRD_ConnectDevice;
  p_driver->device_disconnect = USB_DRD_DisconnectDevice;
  p_driver->device_set_address = USB_DRD_SetDeviceAddress;
  p_driver->device_get_speed = USB_DRD_GetDeviceSpeed;
  p_driver->ep_activate = USB_DRD_ActivateEndpoint;
  p_driver->ep_deactivate = USB_DRD_DeactivateEndpoint;
  p_driver->ep_start_transfer = USB_DRD_StartEndpointXfer;
  p_driver->ep_stop_transfer = USB_DRD_StopEndpointXfer;
  p_driver->ep_set_stall = USB_DRD_SetEndpointStall;
  p_driver->ep_clear_stall = USB_DRD_ClearEndpointStall;
  p_driver->remote_wakeup_activate = USB_DRD_ActivateRemoteWakeup;
  p_driver->remote_wakeup_deactivate = USB_DRD_DeActivateRemoteWakeup;

  p_driver->lpm_activate = USB_DRD_LPM_Activate;
  p_driver->lpm_deactivate = USB_DRD_LPM_DeActivate;

  p_driver->bcd_activate = USB_DRD_BCD_Activate;
  p_driver->bcd_deactivate = USB_DRD_BCD_DeActivate;
  p_driver->bcd_set_mode = USB_DRD_BCD_SetMode;
  p_driver->bcd_detect_port_type = USB_DRD_BCD_SetPortDetection;

  return USB_CORE_OK;
}

/**
  * @brief  Set BCD mode.
  * @param  instance Selected device
  * @param  bcd_config
  * @param  bcd_sts
  */
usb_core_status_t  USB_DRD_BCD_SetMode(uint32_t instance,
                                       usb_core_bcd_config_t bcd_config, usb_core_bcd_config_sts_t bcd_sts)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  switch (bcd_config)
  {
    case USB_CORE_BCD_CONFIG_DCD:
      if (bcd_sts == USB_CORE_BCD_CONFIG_STS_SET)
      {
        p_usb->BCDR |= USB_BCDR_DCDEN;
      }
      else
      {
        p_usb->BCDR &= ~USB_BCDR_DCDEN;
      }
      break;

    case USB_CORE_BCD_CONFIG_PD:
      if (bcd_sts == USB_CORE_BCD_CONFIG_STS_SET)
      {
        p_usb->BCDR |= USB_BCDR_PDEN;
      }
      else
      {
        p_usb->BCDR &= ~USB_BCDR_PDEN;
      }
      break;

    case USB_CORE_BCD_CONFIG_SD:
      if (bcd_sts == USB_CORE_BCD_CONFIG_STS_SET)
      {
        p_usb->BCDR |= USB_BCDR_SDEN;
      }
      else
      {
        p_usb->BCDR &= ~USB_BCDR_SDEN;
      }
      break;

    default:
      return USB_CORE_ERROR;
      break;
  }

  return USB_CORE_OK;
}


/**
  * @brief  Port Detection Process.
  * @param  instance Selected device
  * @param  detection Primary and Secondary detection
  * @retval port detection status
  */
usb_core_bcd_port_status_t USB_DRD_BCD_SetPortDetection(uint32_t instance, usb_core_bcd_detection_t detection)
{
  const usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);
  usb_core_bcd_port_status_t port_detection_status = USB_CORE_BCD_PORT_STATUS_DEFAULT;

  if (detection == USB_CORE_BCD_PRIMARY_DETECTION)
  {
    /* If Charger detect ? */
    if ((p_usb->BCDR & USB_BCDR_PDET) == USB_BCDR_PDET)
    {
      port_detection_status = USB_CORE_BCD_PORT_STATUS_NOT_STD_DOWNSTREAM;
    }
    else
    {
      port_detection_status = USB_CORE_BCD_PORT_STATUS_STD_DOWNSTREAM;
    }
  }
  else if (detection == USB_CORE_BCD_SECONDARY_DETECTION)
  {
    /* If CDP ? */
    if ((p_usb->BCDR & USB_BCDR_SDET) == USB_BCDR_SDET)
    {
      port_detection_status = USB_CORE_BCD_PORT_STATUS_DEDICATED_CHARGING;
    }
    else
    {
      port_detection_status = USB_CORE_BCD_PORT_STATUS_CHARGING_DOWNSTREAM;
    }
  }
  else
  {
    /* ... */
  }

  return port_detection_status;
}

/**
  * @brief  Activate BatteryCharging feature.
  * @param  instance Selected instance
  * @retval HAL status
  */
usb_core_status_t USB_DRD_BCD_Activate(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  /* Enable BCD feature */
  p_usb->BCDR |= USB_BCDR_BCDEN;

  /* Enable DCD : Data Contact Detect */
  p_usb->BCDR &= ~(USB_BCDR_PDEN);
  p_usb->BCDR &= ~(USB_BCDR_SDEN);
  p_usb->BCDR |= USB_BCDR_DCDEN;

  return USB_CORE_OK;
}

/**
  * @brief  Deactivate BatteryCharging feature.
  * @param  instance Selected instance
  * @retval HAL status
  */
usb_core_status_t USB_DRD_BCD_DeActivate(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  /* Disable BCD feature */
  p_usb->BCDR &= ~(USB_BCDR_BCDEN);

  return USB_CORE_OK;
}


/**
  * @brief  Activate LPM feature.
  * @param  instance Selected instance
  * @retval HAL status
  */
usb_core_status_t USB_DRD_LPM_Activate(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  p_usb->LPMCSR |= USB_LPMCSR_LMPEN;
  p_usb->LPMCSR |= USB_LPMCSR_LPMACK;

  return USB_CORE_OK;
}

/**
  * @brief  USB_DRD_LPM_DeActivate Deactivate LPM feature.
  * @param  instance Selected instance
  * @retval HAL status
  */
usb_core_status_t USB_DRD_LPM_DeActivate(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  p_usb->LPMCSR &= ~(USB_LPMCSR_LMPEN);
  p_usb->LPMCSR &= ~(USB_LPMCSR_LPMACK);

  return USB_CORE_OK;
}

/**
  * @brief  USB_DRD_ActivateRemoteWakeup active remote wakeup signalling
  * @param  instance Selected device
  * @retval HAL status
  */
usb_core_status_t USB_DRD_ActivateRemoteWakeup(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  p_usb->CNTR |= USB_CNTR_L2RES;

  return USB_CORE_OK;
}

/**
  * @brief  USB_DRD_DeActivateRemoteWakeup de-active remote wakeup signalling
  * @param  instance Selected device
  * @retval HAL status
  */
usb_core_status_t USB_DRD_DeActivateRemoteWakeup(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  p_usb->CNTR &= ~USB_CNTR_L2RES;

  return USB_CORE_OK;
}

/**
  * @brief  Initializes the USB controller registers
  *         for device mode
  * @param  instance Selected device
  * @param  p_core_config USB Instance configuration parameters
  *         for the specified USB peripheral.
  * @retval HAL status
  */
usb_core_status_t USB_DRD_InitDevice(uint32_t instance, const usb_core_config_params_t *p_core_config)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);
  usb_core_status_t ret;

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(p_core_config);

  /* Force Reset */
  p_usb->CNTR = USB_CNTR_USBRST;

  /* Release Reset */
  p_usb->CNTR &= ~USB_CNTR_USBRST;

  /* Set the Device Mode */
  ret = USB_DRD_SetCurrentMode(instance, USB_CORE_DEVICE_MODE);

  /* Clear pending interrupts */
  p_usb->ISTR = 0U;

  return ret;
}

/**
  * @brief  Start the USB device
  * @param  instance selected device
  * @retval status
  */
usb_core_status_t USB_DRD_StartDevice(uint32_t instance)
{
  (void)USB_DRD_EnableGlobalInterrupt(instance);
  (void)USB_DRD_ConnectDevice(instance);

  return USB_CORE_OK;
}

/**
  * @brief  Stop the usb device mode
  * @param  instance Selected device
  * @retval HAL status
  */
usb_core_status_t USB_DRD_StopDevice(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  /* Disable all interrupts and force USB reset */
  p_usb->CNTR = USB_CNTR_USBRST;

  /* Clear interrupt status register */
  p_usb->ISTR = 0U;

  /* Switch-off device */
  p_usb->CNTR = (USB_CNTR_USBRST | USB_CNTR_PDWN);

  return USB_CORE_OK;
}

/**
  * @brief  Set usb device address
  * @param  instance Selected device
  * @param  address new device address to be assigned
  *         This parameter can be a value from 0 to 255
  * @retval HAL status
  */
usb_core_status_t USB_DRD_SetDeviceAddress(uint32_t instance, uint8_t address)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  if (address == 0U)
  {
    /* Set device address and enable function */
    p_usb->DADDR = USB_DADDR_EF;
  }

  return USB_CORE_OK;
}

/**
  * @brief  Return the Device Speed
  * @param  instance  Selected device
  * @retval device_speed  device speed
  *          @arg USB_CORE_DEVICE_SPEED_FS: Full speed mode
  */
usb_core_device_speed_t USB_DRD_GetDeviceSpeed(uint32_t instance)
{
  STM32_UNUSED(instance);

  usb_core_device_speed_t device_speed = USB_CORE_DEVICE_SPEED_FS;

  return device_speed;
}

/**
  * @brief  Connect the USB device by enabling the pull-up/pull-down
  * @param  instance Selected device
  * @retval HAL status
  */
usb_core_status_t USB_DRD_ConnectDevice(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  /* Enabling DP Pull-UP bit to Connect internal PU resistor on USB DP line */
  p_usb->BCDR |= USB_BCDR_DPPU;

  return USB_CORE_OK;
}

/**
  * @brief  Disconnect the USB device by disabling the pull-up/pull-down
  * @param  instance Selected device
  * @retval HAL status
  */
usb_core_status_t USB_DRD_DisconnectDevice(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  /* Disable DP Pull-Up bit to disconnect the Internal PU resistor on USB DP line */
  p_usb->BCDR &= ~(USB_BCDR_DPPU);

  return USB_CORE_OK;
}

/**
  * @brief  Activate and configure an endpoint
  * @param  instance Selected device
  * @param  p_ep pointer to endpoint structure
  * @retval HAL status
  */
usb_core_status_t USB_DRD_ActivateEndpoint(uint32_t instance, usb_core_ep_t *p_ep)
{
  usb_core_phy_ep_t phy_ep_num;
  uint32_t ep_value;

  /* Get Endpoint Physical number */
  phy_ep_num = (usb_core_phy_ep_t)p_ep->num;

  ep_value = PCD_GET_ENDPOINT(instance, phy_ep_num) & USB_EP_T_MASK;

  /* Initialize Endpoint */
  if (p_ep->type == USB_CORE_EP_TYPE_CTRL)
  {
    ep_value |= USB_EP_CONTROL;
  }
  else if (p_ep->type == USB_CORE_EP_TYPE_BULK)
  {
    ep_value |= USB_EP_BULK;
  }
  else if (p_ep->type == USB_CORE_EP_TYPE_INTR)
  {
    ep_value |= USB_EP_INTERRUPT;
  }
  else
  {
    ep_value |= USB_EP_ISOCHRONOUS;
  }

  PCD_SET_ENDPOINT(instance, phy_ep_num, (ep_value | USB_EP_VTRX | USB_EP_VTTX));

  PCD_SET_EP_ADDRESS(instance, phy_ep_num, (uint8_t)p_ep->num);

  if (p_ep->double_buffer_en == (uint8_t)USB_CORE_CONFIG_DISABLED)
  {
    if (p_ep->dir == USB_CORE_EP_IN_DIR)
    {
      /* Set the endpoint Transmit buffer address */
      PCD_SET_EP_TX_ADDRESS(instance, phy_ep_num, p_ep->pma_address);
      PCD_CLEAR_TX_DTOG(instance, phy_ep_num);

      if (p_ep->type != USB_CORE_EP_TYPE_ISOC)
      {
        /* Configure NAK status for all non ISOC Endpoint */
        PCD_SET_EP_TX_STATUS(instance, phy_ep_num, USB_EP_TX_NAK);
      }
      else
      {
        /* Configure TX for ISOC Endpoint to disabled state */
        PCD_SET_EP_TX_STATUS(instance, phy_ep_num, USB_EP_TX_DIS);
      }
    }
    else
    {
      /* Set the endpoint Receive buffer address */
      PCD_SET_EP_RX_ADDRESS(instance, phy_ep_num, p_ep->pma_address);

      /* Set the endpoint Receive buffer counter */
      PCD_SET_EP_RX_CNT(instance, phy_ep_num, p_ep->max_packet);
      PCD_CLEAR_RX_DTOG(instance, phy_ep_num);

      if (phy_ep_num == USB_CORE_PHY_CHEP_0)
      {
        /* Configure VALID status for EP0 */
        PCD_SET_EP_RX_STATUS(instance, phy_ep_num, USB_EP_RX_VALID);
      }
      else
      {
        /* Configure NAK status for OUT Endpoint */
        PCD_SET_EP_RX_STATUS(instance, phy_ep_num, USB_EP_RX_NAK);
      }
    }
  }
  /* Double Buffer */
  else
  {
    if (p_ep->type == USB_CORE_EP_TYPE_BULK)
    {
      /* Set bulk endpoint as double buffered */
      PCD_SET_BULK_EP_DBUF(instance, phy_ep_num);
    }
    else
    {
      /* Set the ISOC endpoint in double buffer mode */
      PCD_CLEAR_EP_KIND(instance, phy_ep_num);
    }

    /* Set buffer address for double buffered mode */
    PCD_SET_EP_DBUF_ADDR(instance, phy_ep_num, p_ep->pma_addr0, p_ep->pma_addr1);

    if (p_ep->dir == USB_CORE_EP_OUT_DIR)
    {
      /* Clear the data toggle bits for the endpoint IN/OUT */
      PCD_CLEAR_RX_DTOG(instance, phy_ep_num);
      PCD_CLEAR_TX_DTOG(instance, phy_ep_num);

      /* Set endpoint RX count */
      PCD_SET_EP_DBUF_CNT(instance, phy_ep_num, p_ep->dir, p_ep->max_packet);

      /* Set endpoint RX to valid state */
      PCD_SET_EP_RX_STATUS(instance, phy_ep_num, USB_EP_RX_VALID);
      PCD_SET_EP_TX_STATUS(instance, phy_ep_num, USB_EP_TX_DIS);
    }
    else
    {
      /* Clear the data toggle bits for the endpoint IN/OUT */
      PCD_CLEAR_RX_DTOG(instance, phy_ep_num);
      PCD_CLEAR_TX_DTOG(instance, phy_ep_num);

      if (p_ep->type != USB_CORE_EP_TYPE_ISOC)
      {
        /* Configure NAK status for all non ISOC Endpoint */
        PCD_SET_EP_TX_STATUS(instance, phy_ep_num, USB_EP_TX_NAK);
      }
      else
      {
        /* Configure TX for ISOC Endpoint to disabled state */
        PCD_SET_EP_TX_STATUS(instance, phy_ep_num, USB_EP_TX_DIS);
      }

      PCD_SET_EP_RX_STATUS(instance, phy_ep_num, USB_EP_RX_DIS);
    }
  }

  return USB_CORE_OK;
}

/**
  * @brief  De-activate and de-initialize an endpoint
  * @param  instance Selected device
  * @param  p_ep pointer to endpoint structure
  * @retval HAL status
  */
usb_core_status_t USB_DRD_DeactivateEndpoint(uint32_t instance, const usb_core_ep_t *p_ep)
{
  usb_core_phy_ep_t phy_ep_num;

  if ((uint8_t)p_ep->num > USB_DRD_MAX_CHEP_NBR)
  {
    return USB_CORE_ERROR;
  }

  /* Get Endpoint Physical number */
  phy_ep_num = (usb_core_phy_ep_t)p_ep->num;

  if (p_ep->double_buffer_en == (uint8_t)USB_CORE_CONFIG_DISABLED)
  {
    if (p_ep->dir == USB_CORE_EP_IN_DIR)
    {
      PCD_CLEAR_TX_DTOG(instance, phy_ep_num);

      /* Configure DISABLE status for the Endpoint */
      PCD_SET_EP_TX_STATUS(instance, phy_ep_num, USB_EP_TX_DIS);
    }

    else
    {
      PCD_CLEAR_RX_DTOG(instance, phy_ep_num);

      /* Configure DISABLE status for the Endpoint */
      PCD_SET_EP_RX_STATUS(instance, phy_ep_num, USB_EP_RX_DIS);
    }
  }
  /* Double Buffer */
  else
  {
    if (p_ep->dir == USB_CORE_EP_OUT_DIR)
    {
      /* Clear the data toggle bits for the endpoint IN/OUT */
      PCD_CLEAR_RX_DTOG(instance, phy_ep_num);
      PCD_CLEAR_TX_DTOG(instance, phy_ep_num);

      /* Reset value of the data toggle bits for the endpoint OUT */
      PCD_TX_DTOG(instance, phy_ep_num);

      PCD_SET_EP_RX_STATUS(instance, phy_ep_num, USB_EP_RX_DIS);
      PCD_SET_EP_TX_STATUS(instance, phy_ep_num, USB_EP_TX_DIS);
    }
    else
    {
      /* Clear the data toggle bits for the endpoint IN/OUT */
      PCD_CLEAR_RX_DTOG(instance, phy_ep_num);
      PCD_CLEAR_TX_DTOG(instance, phy_ep_num);
      PCD_RX_DTOG(instance, phy_ep_num);

      /* Configure DISABLE status for the Endpoint */
      PCD_SET_EP_TX_STATUS(instance, phy_ep_num, USB_EP_TX_DIS);
      PCD_SET_EP_RX_STATUS(instance, phy_ep_num, USB_EP_RX_DIS);
    }
  }

  return USB_CORE_OK;
}

/**
  * @brief  Setup and starts a transfer over an EP
  * @param  instance Selected device
  * @param  p_ep pointer to endpoint structure
  * @retval HAL status
  */
usb_core_status_t USB_DRD_StartEndpointXfer(uint32_t instance, usb_core_ep_t *p_ep)
{
  usb_core_phy_ep_t phy_ep_num;
  uint32_t length;
  uint16_t pma_buffer;
  uint16_t ep_value;

  /* Get Endpoint Physical number */
  phy_ep_num = (usb_core_phy_ep_t)p_ep->num;

  /* IN endpoint */
  if (p_ep->dir == USB_CORE_EP_IN_DIR)
  {
    /* Multi packet transfer */
    if (p_ep->xfer_length > p_ep->max_packet)
    {
      length = p_ep->max_packet;
    }
    else
    {
      length = p_ep->xfer_length;
    }

    /* Configure and validate Tx endpoint */
    if (p_ep->double_buffer_en == (uint8_t)USB_CORE_CONFIG_DISABLED)
    {
      USB_DRD_WritePMA(instance, p_ep->p_xfer_buffer, p_ep->pma_address, (uint16_t)length);
      PCD_SET_EP_TX_CNT(instance, phy_ep_num, length);
    }
    else
    {
      /* Double buffer bulk management */
      if (p_ep->type == USB_CORE_EP_TYPE_BULK)
      {
        p_ep->xfer_fill_db = 1U;

        if (p_ep->xfer_size > p_ep->max_packet)
        {
          /* Enable double buffer */
          PCD_SET_BULK_EP_DBUF(instance, phy_ep_num);

          /* Each Time to write in PMA xfer_len_db will */
          p_ep->xfer_size -= length;

          /* Fill the two first buffer in the Buffer0 & Buffer1 */
          if ((PCD_GET_ENDPOINT(instance, phy_ep_num) & USB_EP_DTOG_TX) != 0U)
          {
            /* Set the Double buffer counter for pmabuffer1 */
            PCD_SET_EP_DBUF1_CNT(instance, phy_ep_num, p_ep->dir, length);
            pma_buffer = p_ep->pma_addr1;

            /* Write the user buffer to USB PMA */
            USB_DRD_WritePMA(instance, p_ep->p_xfer_buffer, pma_buffer, (uint16_t)length);
            p_ep->p_xfer_buffer += length;

            if (p_ep->xfer_size > p_ep->max_packet)
            {
              p_ep->xfer_size -= length;
            }
            else
            {
              length = p_ep->xfer_size;
              p_ep->xfer_size = 0U;
            }

            /* Set the Double buffer counter for pmabuffer0 */
            PCD_SET_EP_DBUF0_CNT(instance, phy_ep_num, p_ep->dir, length);
            pma_buffer = p_ep->pma_addr0;

            /* Write the user buffer to USB PMA */
            USB_DRD_WritePMA(instance, p_ep->p_xfer_buffer, pma_buffer, (uint16_t)length);
          }
          else
          {
            /* Set the Double buffer counter for pmabuffer0 */
            PCD_SET_EP_DBUF0_CNT(instance, phy_ep_num, p_ep->dir, length);
            pma_buffer = p_ep->pma_addr0;

            /* Write the user buffer to USB PMA */
            USB_DRD_WritePMA(instance, p_ep->p_xfer_buffer, pma_buffer, (uint16_t)length);
            p_ep->p_xfer_buffer += length;

            if (p_ep->xfer_size > p_ep->max_packet)
            {
              p_ep->xfer_size -= length;
            }
            else
            {
              length = p_ep->xfer_size;
              p_ep->xfer_size = 0U;
            }

            /* Set the Double buffer counter for pmabuffer1 */
            PCD_SET_EP_DBUF1_CNT(instance, phy_ep_num, p_ep->dir, length);
            pma_buffer = p_ep->pma_addr1;

            /* Write the user buffer to USB PMA */
            USB_DRD_WritePMA(instance, p_ep->p_xfer_buffer, pma_buffer, (uint16_t)length);
          }
        }
        /* Auto Switch to single buffer mode when transfer <Mps no need to manage in double buffer */
        else
        {
          length = p_ep->xfer_size;

          /* Disable double buffer mode for Bulk endpoint */
          PCD_CLEAR_BULK_EP_DBUF(instance, phy_ep_num);

          /* Set Tx count with nbre of byte to be transmitted */
          PCD_SET_EP_TX_CNT(instance, phy_ep_num, length);
          pma_buffer = p_ep->pma_addr0;

          /* Write the user buffer to USB PMA */
          USB_DRD_WritePMA(instance, p_ep->p_xfer_buffer, pma_buffer, (uint16_t)length);
        }
      }
      else /* Manage isochronous double buffer IN mode */
      {
        /* Each Time to write in PMA xfer_len_db will */
        p_ep->xfer_size -= length;

        /* Fill the data buffer */
        if ((PCD_GET_ENDPOINT(instance, phy_ep_num) & USB_EP_DTOG_TX) != 0U)
        {
          /* Set the Double buffer counter for pmabuffer1 */
          PCD_SET_EP_DBUF1_CNT(instance, phy_ep_num, p_ep->dir, length);
          pma_buffer = p_ep->pma_addr1;

          /* Write the user buffer to USB PMA */
          USB_DRD_WritePMA(instance, p_ep->p_xfer_buffer, pma_buffer, (uint16_t)length);
        }
        else
        {
          /* Set the Double buffer counter for pmabuffer0 */
          PCD_SET_EP_DBUF0_CNT(instance, phy_ep_num, p_ep->dir, length);
          pma_buffer = p_ep->pma_addr0;

          /* Write the user buffer to USB PMA */
          USB_DRD_WritePMA(instance, p_ep->p_xfer_buffer, pma_buffer, (uint16_t)length);
        }
      }
    }

    PCD_SET_EP_TX_STATUS(instance, phy_ep_num, USB_EP_TX_VALID);
  }
  else /* OUT endpoint */
  {
    if (p_ep->double_buffer_en == (uint8_t)USB_CORE_CONFIG_DISABLED)
    {
      if ((p_ep->xfer_length == 0U) && (p_ep->type == USB_CORE_EP_TYPE_CTRL))
      {
        /* This is a status out stage set the OUT_STATUS */
        PCD_SET_OUT_STATUS(instance, phy_ep_num);
      }
      else
      {
        PCD_CLEAR_OUT_STATUS(instance, phy_ep_num);
      }

      /* Multi packet transfer */
      if (p_ep->xfer_length > p_ep->max_packet)
      {
        p_ep->xfer_length -= p_ep->max_packet;
      }
      else
      {
        p_ep->xfer_length = 0U;
      }
    }
    else
    {
      /* First Transfer Coming From HAL_PCD_EP_Receive & From ISR */
      /* Set the Double buffer counter */
      if (p_ep->type == USB_CORE_EP_TYPE_BULK)
      {
        /* Coming from ISR */
        if (p_ep->xfer_count != 0U)
        {
          /* Update last value to check if there is blocking state */
          ep_value = (uint16_t)PCD_GET_ENDPOINT(instance, phy_ep_num);

          /* Blocking State */
          if ((((ep_value & USB_EP_DTOG_RX) != 0U) && ((ep_value & USB_EP_DTOG_TX) != 0U))
              || (((ep_value & USB_EP_DTOG_RX) == 0U) && ((ep_value & USB_EP_DTOG_TX) == 0U)))
          {
            /* OUT double buffered endpoint */
            USB_DRD_TX_DTOG(instance, phy_ep_num);
          }
        }
      }
      /* ISO OUT double buffer */
      else if (p_ep->type == USB_CORE_EP_TYPE_ISOC)
      {
        /* Only single packet transfer supported in FS */
        p_ep->xfer_length = 0U;
      }
      else
      {
        return USB_CORE_ERROR;
      }
    }

    PCD_SET_EP_RX_STATUS(instance, phy_ep_num, USB_EP_RX_VALID);
  }

  return USB_CORE_OK;
}


/**
  * @brief  Set a stall condition over an EP
  * @param  instance Selected device
  * @param  p_ep pointer to endpoint structure
  * @retval HAL status
  */
usb_core_status_t USB_DRD_SetEndpointStall(uint32_t instance, const usb_core_ep_t *p_ep)
{
  usb_core_phy_ep_t phy_ep_num;

  /* Get Endpoint Physical number */
  phy_ep_num = (usb_core_phy_ep_t)p_ep->num;

  if (p_ep->dir == USB_CORE_EP_IN_DIR)
  {
    PCD_SET_EP_TX_STATUS(instance, phy_ep_num, USB_EP_TX_STALL);
  }
  else
  {
    PCD_SET_EP_RX_STATUS(instance, phy_ep_num, USB_EP_RX_STALL);
  }

  return USB_CORE_OK;
}

/**
  * @brief  Clear a stall condition over an EP
  * @param  instance Selected device
  * @param  p_ep pointer to endpoint structure
  * @retval HAL status
  */
usb_core_status_t USB_DRD_ClearEndpointStall(uint32_t instance, const usb_core_ep_t *p_ep)
{
  usb_core_phy_ep_t phy_ep_num;

  /* Get Endpoint Physical number */
  phy_ep_num = (usb_core_phy_ep_t)p_ep->num;

  if (p_ep->dir == USB_CORE_EP_IN_DIR)
  {
    PCD_CLEAR_TX_DTOG(instance, phy_ep_num);

    if (p_ep->type != USB_CORE_EP_TYPE_ISOC)
    {
      /* Configure NAK status for all non ISOC Endpoint */
      PCD_SET_EP_TX_STATUS(instance, phy_ep_num, USB_EP_TX_NAK);
    }
  }
  else
  {
    PCD_CLEAR_RX_DTOG(instance, phy_ep_num);

    /* Configure VALID status for the Endpoint */
    PCD_SET_EP_RX_STATUS(instance, phy_ep_num, USB_EP_RX_VALID);
  }

  return USB_CORE_OK;
}

/**
   * @brief  Stop transfer on an EP
   * @param  instance  usb device instance
   * @param  p_ep pointer to endpoint structure
   * @retval HAL status
   */
usb_core_status_t USB_DRD_StopEndpointXfer(uint32_t instance, const usb_core_ep_t *p_ep)
{
  usb_core_phy_ep_t phy_ep_num;

  if ((uint8_t)p_ep->num > USB_DRD_MAX_CHEP_NBR)
  {
    return USB_CORE_ERROR;
  }

  /* Get Endpoint Physical number */
  phy_ep_num = (usb_core_phy_ep_t)p_ep->num;

  /* IN endpoint */
  if (p_ep->dir == USB_CORE_EP_IN_DIR)
  {
    if (p_ep->double_buffer_en == (uint8_t)USB_CORE_CONFIG_DISABLED)
    {
      if (p_ep->type != USB_CORE_EP_TYPE_ISOC)
      {
        /* Configure NAK status for all non ISOC Endpoint */
        PCD_SET_EP_TX_STATUS(instance, phy_ep_num, USB_EP_TX_NAK);
      }
      else
      {
        /* Configure TX for ISOC Endpoint to disabled state */
        PCD_SET_EP_TX_STATUS(instance, phy_ep_num, USB_EP_TX_DIS);
      }
    }
  }
  else /* OUT endpoint */
  {
    if (p_ep->double_buffer_en == (uint8_t)USB_CORE_CONFIG_DISABLED)
    {
      if (p_ep->type != USB_CORE_EP_TYPE_ISOC)
      {
        /* Configure NAK status for all non ISOC Endpoint */
        PCD_SET_EP_RX_STATUS(instance, phy_ep_num, USB_EP_RX_NAK);
      }
      else
      {
        /* Configure RX for ISOC Endpoint to disabled state */
        PCD_SET_EP_RX_STATUS(instance, phy_ep_num, USB_EP_RX_DIS);
      }
    }
  }

  return USB_CORE_OK;
}
/**
  * @}
  */


/** @defgroup USB_DRD_CORE_Host_Exported_Functions USB Core Host Low Layer Exported Functions
  * @{
  */

/**
  * @brief  Initialize the USB DRD controller registers
  *         for Host mode
  * @param  instance Selected device
  * @param  p_core_config USB Instance configuration parameters
  *         for the specified USB peripheral.
  * @retval HAL status
  */
usb_core_status_t USB_DRD_InitHost(uint32_t instance, const usb_core_config_params_t *p_core_config)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  /* Clear All Pending Interrupt */
  p_usb->ISTR = 0U;

  /* Disable all interrupts */
  p_usb->CNTR &= ~(USB_CNTR_CTRM | USB_CNTR_PMAOVRM | USB_CNTR_ERRM |
                   USB_CNTR_WKUPM | USB_CNTR_SUSPM | USB_CNTR_DCON |
                   USB_CNTR_SOFM | USB_CNTR_ESOFM | USB_CNTR_L1REQM);

  /* Clear All Pending Interrupt */
  p_usb->ISTR = 0U;

  /* Set the PullDown on the PHY */
  p_usb->BCDR |= USB_BCDR_DPPD;

  /* Enable Global interrupt */
  p_usb->CNTR |= (USB_CNTR_CTRM | USB_CNTR_PMAOVRM | USB_CNTR_ERRM |
                  USB_CNTR_WKUPM | USB_CNTR_SUSPM | USB_CNTR_DCON |
                  USB_CNTR_SOFM | USB_CNTR_ESOFM | USB_CNTR_L1REQM);

  /* Init PMA Address */
  (void)USB_DRD_PMAReset();

  /* Isochronous Ep single buffer state */
  ep_db_state.is_iso_db = (usb_drd_doublebuffer_t)p_core_config->iso_db_state;

  /* Bulk Ep double buffer state  */
  ep_db_state.is_bulk_db = (usb_drd_doublebuffer_t)p_core_config->bulk_db_state;

  return USB_CORE_OK;
}

/**
  * @brief  Initialize the USB DRD HCD Driver
  * @param  p_driver pointer USB HCD driver structure
  * @retval HAL status
  */
usb_core_status_t USB_DRD_HCD_InitDriver(usb_core_hcd_driver_t *p_driver)
{
  p_driver->core_init = USB_DRD_InitCore;
  p_driver->core_deinit = USB_DRD_DeInitCore;
  p_driver->core_set_mode = USB_DRD_SetCurrentMode;
  p_driver->core_get_mode = USB_DRD_GetCurrentMode;
  p_driver->core_enable_interrupts = USB_DRD_EnableGlobalInterrupt;
  p_driver->core_disable_interrupts = USB_DRD_DisableGlobalInterrupt;
  p_driver->core_get_dma_status = USB_DRD_GetDmaStatus;
  p_driver->host_init = USB_DRD_InitHost;
  p_driver->host_start = USB_DRD_StartHost;
  p_driver->host_stop = USB_DRD_StopHost;
  p_driver->host_channel_init = USB_DRD_InitChannel;
  p_driver->host_channel_start = USB_DRD_StartChannelXfer;
  p_driver->host_channel_halt = USB_DRD_HaltChannel;
  p_driver->host_channel_close = USB_DRD_CloseChannel;
  p_driver->host_port_reset = USB_DRD_PortReset;
  p_driver->host_port_suspend = USB_DRD_PortSuspend;
  p_driver->host_port_resume = USB_DRD_PortResume;
  p_driver->host_get_current_frame = USB_DRD_GetCurrentFrame;
  p_driver->host_get_port_speed = USB_DRD_GetHostPortSpeed;

  return USB_CORE_OK;
}

/**
  * @brief  Set the channel Kind (Single/double buffer mode)
  * @param  instance Selected host
  * @param  phy_ch_num physical channel number
  * @param  db_status double state can be USB_DRD_XXX_DBUFF_ENBALE/USB_DRD_XXX_DBUFF_DISABLE
  * @retval HAL status
  */
usb_core_status_t USB_DRD_SetChannelDoubleBuffer(uint32_t instance, usb_core_phy_chep_t phy_ch_num,
                                                 usb_drd_db_status_t db_status)
{
  uint32_t ch_reg;

  if ((db_status == USB_DRD_BULK_DB_ENBALE) || (db_status == USB_DRD_ISOC_DB_DISABLE))
  {
    ch_reg = (USB_DRD_GET_CHEP(instance, phy_ch_num) | USB_CH_KIND) & USB_CHEP_DB_MSK;
  }
  else
  {
    ch_reg = USB_DRD_GET_CHEP(instance, phy_ch_num) & (~USB_CH_KIND) & USB_CHEP_DB_MSK;
  }

  /* Set the device speed in case using HUB FS with device LS */
  USB_DRD_SET_CHEP(instance, phy_ch_num, ch_reg);

  return USB_CORE_OK;
}

/**
  * @brief  Initialize a host channel
  * @param  instance Selected host
  * @param  p_ch pointer to host Channel structure
  * @retval DRD Core status
  */
usb_core_status_t USB_DRD_InitChannel(uint32_t instance, usb_core_ch_t *p_ch)
{
  usb_core_status_t status = USB_CORE_OK;
  usb_core_port_speed_t host_port_speed;
  uint32_t ch_reg;
  uint32_t phy_channel;
  uint32_t used_channel;
  usb_core_ep_direction_t ep_dir = (usb_core_ep_direction_t)p_ch->ch_dir;

  if (p_ch->ch_num > USB_CORE_CHANNEL_15)
  {
    return USB_CORE_ERROR;
  }

  if ((p_ch->ep_num == USB_CORE_ENDPOINT_0) && (chep0.is_dual_allocated != 0U))
  {
    p_ch->pma_address = chep0.pma_address;
    p_ch->pma_addr0 = chep0.pma_addr0;
    p_ch->pma_addr1 = chep0.pma_addr1;

    phy_chin_state[0U] = (((uint16_t)p_ch->ch_num + 1U) << 4U) |
                         ((uint16_t)p_ch->ep_type + 1U) |
                         ((uint16_t)p_ch->ep_num << 8U);

    phy_chout_state[0U] = (((uint16_t)p_ch->ch_num + 1U) << 4U) |
                          ((uint16_t)p_ch->ep_type + 1U) |
                          ((uint16_t)p_ch->ep_num << 8U);

  }

  /* Check if the logical channel are already allocated */
  used_channel = USB_DRD_IsUsedChannel(p_ch->ch_num);

  /* Check if the channel is not already opened */
  if (used_channel == 0U)
  {
    /* Allocate New Physical channel */
    p_ch->phy_ch_num = USB_DRD_GetFreePhysicalChannel(p_ch);

    /* No free Channel available, return error */
    if (p_ch->phy_ch_num == USB_CORE_PHY_CHEP_FF)
    {
      return USB_CORE_ERROR;
    }
  }
  /* Channel already opened */
  else
  {
    /* Get Physical Channel number */
    phy_channel = (uint32_t)((used_channel & 0xF0U) >> 4U);
    p_ch->phy_ch_num = (usb_core_phy_chep_t)phy_channel;
  }

  if (ep_dir == USB_CORE_EP_IN_DIR)
  {
    p_ch->ch_dir = USB_CORE_CH_IN_DIR;
  }
  else
  {
    p_ch->ch_dir = USB_CORE_CH_OUT_DIR;
  }

  /* Check if the channel is not already opened */
  if (used_channel == 0U)
  {
    if (((p_ch->ep_type == USB_CORE_EP_TYPE_ISOC) && (ep_db_state.is_iso_db == USB_DRD_DBL_BUF))
        || ((p_ch->ep_type == USB_CORE_EP_TYPE_BULK) && (ep_db_state.is_bulk_db == USB_DRD_DBL_BUF)))
    {
      /* PMA Dynamic Allocation */
      status = USB_DRD_PMAlloc(p_ch, (uint16_t)USB_DRD_DBL_BUF);

      if (status == USB_CORE_ERROR)
      {
        return USB_CORE_ERROR;
      }

      /* Clear Channel DTOG_TX */
      HCD_CLEAR_TX_DTOG(instance, p_ch->phy_ch_num);

      /* Clear Channel DTOG RX */
      HCD_CLEAR_RX_DTOG(instance, p_ch->phy_ch_num);
    }
    else
    {
      if (p_ch->ep_num != USB_CORE_ENDPOINT_0)
      {
        status = USB_DRD_PMAlloc(p_ch, (uint16_t)USB_DRD_SNG_BUF);

        if (status == USB_CORE_ERROR)
        {
          return USB_CORE_ERROR;
        }
      }
      else
      {
        if (p_ch->ch_num == USB_CORE_CHANNEL_0)
        {
          if ((chep0.virtual_ch_num != USB_CORE_CHANNEL_0) && (chep0.dir == USB_CORE_EP_IN_DIR))
          {
            if (p_ch->ch_dir == USB_CORE_CH_OUT_DIR)
            {
              status = USB_DRD_PMAlloc(p_ch, (uint16_t)USB_DRD_SNG_BUF);

              if (status == USB_CORE_ERROR)
              {
                return USB_CORE_ERROR;
              }
            }
            else
            {
              return USB_CORE_ERROR;
            }
          }
          else
          {
            /* This is a dual EP0 PMA allocation */
            chep0.is_dual_allocated = 0x1U;

            /* PMA Dynamic Allocation for EP0 OUT direction */
            p_ch->ch_dir = USB_CORE_CH_OUT_DIR;
            status = USB_DRD_PMAlloc(p_ch, (uint16_t)USB_DRD_SNG_BUF);

            if (status == USB_CORE_ERROR)
            {
              return USB_CORE_ERROR;
            }

            /* PMA Dynamic Allocation for EP0 IN direction */
            p_ch->ch_dir = USB_CORE_CH_IN_DIR;
            status = USB_DRD_PMAlloc(p_ch, (uint16_t)USB_DRD_SNG_BUF);

            if (status == USB_CORE_ERROR)
            {
              return USB_CORE_ERROR;
            }
          }
        }
        else
        {
          if (chep0.is_allocated == 1U)
          {
            if (chep0.dir == USB_CORE_EP_IN_DIR)
            {
              p_ch->pma_addr1 = chep0.pma_addr1;
            }
            else
            {
              p_ch->pma_addr0 = chep0.pma_addr0;
            }
          }
          else
          {
            status = USB_DRD_PMAlloc(p_ch, (uint16_t)USB_DRD_SNG_BUF);

            if (status == USB_CORE_ERROR)
            {
              return USB_CORE_ERROR;
            }
          }
        }
      }
    }
  }

  if (ep_dir == USB_CORE_EP_IN_DIR)
  {
    p_ch->ch_dir = USB_CORE_CH_IN_DIR;

    if (p_ch->ep_num == USB_CORE_ENDPOINT_0)
    {
      p_ch->pma_address = p_ch->pma_addr1;
    }
  }
  else
  {
    p_ch->ch_dir = USB_CORE_CH_OUT_DIR;

    if (p_ch->ep_num == USB_CORE_ENDPOINT_0)
    {
      p_ch->pma_address = p_ch->pma_addr0;
    }
  }

  ch_reg = USB_DRD_GET_CHEP(instance, p_ch->phy_ch_num) & USB_CH_T_MASK;

  /* Initialize host Channel */
  switch (p_ch->ep_type)
  {
    case USB_CORE_EP_TYPE_CTRL:
      ch_reg |= USB_EP_CONTROL;
      break;

    case USB_CORE_EP_TYPE_BULK:
      ch_reg |= USB_EP_BULK;
      break;

    case USB_CORE_EP_TYPE_INTR:
      ch_reg |= USB_EP_INTERRUPT;
      break;

    case USB_CORE_EP_TYPE_ISOC:
      ch_reg |= USB_EP_ISOCHRONOUS;
      break;

    default:
      status = USB_CORE_ERROR;
      break;
  }

  /* Clear device address, Endpoint number and Low Speed Endpoint fields */
  ch_reg &= ~(USB_CHEP_DEVADDR |
              USB_CHEP_ADDR |
              USB_CHEP_LSEP |
              USB_CHEP_NAK |
              USB_CHEP_KIND |
              USB_CHEP_ERRTX |
              USB_CHEP_ERRRX |
              (0xFUL << 27));

  /* Set device address and Endpoint number associated to the channel */
  ch_reg |= (((uint32_t)p_ch->dev_addr << USB_CHEP_DEVADDR_Pos) |
             (uint32_t)p_ch->ep_num);

  /* Get Host core Speed */
  host_port_speed = USB_DRD_GetHostPortSpeed(instance);

  /* Set the device speed in case using HUB FS with device LS */
  if ((p_ch->speed == USB_CORE_DEVICE_SPEED_LS) && (host_port_speed == USB_CORE_PORT_SPEED_FS))
  {
    ch_reg |= USB_CHEP_LSEP;
  }

  /* Update the channel register value */
  USB_DRD_SET_CHEP(instance, p_ch->phy_ch_num, (ch_reg | USB_CH_VTRX | USB_CH_VTTX));

  /* Check single buffer for isochronous channel */
  if (p_ch->ep_type == USB_CORE_EP_TYPE_ISOC)
  {
    if (ep_db_state.is_iso_db != USB_DRD_DBL_BUF)
    {
      (void)USB_DRD_SetChannelDoubleBuffer(instance, p_ch->phy_ch_num, USB_DRD_ISOC_DB_DISABLE);
    }
  }

  /* Bulk double buffer check */
  if (p_ch->ep_type == USB_CORE_EP_TYPE_BULK)
  {
    if (ep_db_state.is_bulk_db == USB_DRD_DBL_BUF)
    {
      (void)USB_DRD_SetChannelDoubleBuffer(instance, p_ch->phy_ch_num, USB_DRD_BULK_DB_ENBALE);
    }
  }

  return status;
}

/**
  * @brief  Close a host channel
  * @param  instance Selected host
  * @param  p_ch pointer to host Channel structure
  * @retval DRD Core status
  */
usb_core_status_t USB_DRD_CloseChannel(uint32_t instance, usb_core_ch_t *p_ch)
{
  usb_core_status_t status = USB_CORE_OK;

  /* Stop the channel */
  (void)USB_DRD_HaltChannel(instance, p_ch);

  if (p_ch->ch_dir == USB_CORE_CH_IN_DIR)
  {
    /* Free Allocated Channel */
    phy_chin_state[p_ch->phy_ch_num] = 0U;
  }
  else
  {
    /* Free Allocated Channel */
    phy_chout_state[p_ch->phy_ch_num] = 0U;
  }

  /* Reset PMA Channel_Allocation */
  (void)USB_DRD_PMADeAlloc(p_ch);

  return status;
}

/**
  * @brief  Halt a host channel.
  * @param  instance Selected host
  * @param  p_ch pointer to host Channel structure
  * @retval HAL status
  */
usb_core_status_t USB_DRD_HaltChannel(uint32_t instance, const usb_core_ch_t *p_ch)
{
  usb_core_status_t status = USB_CORE_OK;

  if (p_ch->ch_dir == USB_CORE_CH_IN_DIR)
  {
    (void)USB_DRD_HaltInChannel(instance, p_ch->phy_ch_num);
  }
  else
  {
    (void)USB_DRD_HaltOutChannel(instance, p_ch->phy_ch_num);
  }

  return status;
}

/**
  * @brief  Start a transfer over a host channel
  * @param  instance Selected host
  * @param  p_ch pointer to host channel structure
  * @retval DRD Core status
  */
usb_core_status_t USB_DRD_StartChannelXfer(uint32_t instance, usb_core_ch_t *p_ch)
{
  uint32_t length;
  uint32_t ch_reg = USB_DRD_GET_CHEP(instance, p_ch->phy_ch_num);

  if (p_ch->ch_dir == USB_CORE_CH_IN_DIR)  /* In Channel */
  {
    /* Multi packet transfer */
    if (p_ch->xfer_length > p_ch->max_packet)
    {
      length = p_ch->max_packet;
    }
    else
    {
      length = p_ch->xfer_length;
    }

    if (p_ch->double_buffer_en == (uint8_t)USB_CORE_CONFIG_DISABLED)
    {
      if ((p_ch->ep_type == USB_CORE_EP_TYPE_BULK)
          || (p_ch->ep_type == USB_CORE_EP_TYPE_INTR))
      {
        USB_DRD_CLEAR_RX_DTOG(instance, p_ch->phy_ch_num);

        /* Set Data PID */
        if (p_ch->data_pid == USB_CORE_CH_PID_DATA1)
        {
          USB_DRD_RX_DTOG(instance, p_ch->phy_ch_num);
        }
      }

      /* Set RX buffer count */
      USB_DRD_SET_CHEP_RX_CNT(instance, p_ch->phy_ch_num, length);
    }
    else if (p_ch->ep_type == USB_CORE_EP_TYPE_BULK)
    {
      /* Double buffer activated */
      if ((p_ch->xfer_length > p_ch->max_packet))
      {
        (void)USB_DRD_SetChannelDoubleBuffer(instance, p_ch->phy_ch_num, USB_DRD_BULK_DB_ENBALE);

        /* Set the Double buffer counter */
        USB_DRD_SET_CHEP_DBUF0_CNT(instance, p_ch->phy_ch_num, USB_CORE_EP_OUT_DIR, length);
        USB_DRD_SET_CHEP_DBUF1_CNT(instance, p_ch->phy_ch_num, USB_CORE_EP_OUT_DIR, length);
      }
      else  /* Switch to single buffer mode */
      {
        (void)USB_DRD_SetChannelDoubleBuffer(instance, p_ch->phy_ch_num, USB_DRD_BULK_DB_DISABLE);

        /* Set RX buffer count */
        USB_DRD_SET_CHEP_RX_CNT(instance, p_ch->phy_ch_num, length);
      }
    }
    else  /* Isochronous */
    {
      /* Set the Double buffer counter */
      USB_DRD_SET_CHEP_DBUF0_CNT(instance, p_ch->phy_ch_num, USB_CORE_EP_OUT_DIR, length);
      USB_DRD_SET_CHEP_DBUF1_CNT(instance, p_ch->phy_ch_num, USB_CORE_EP_OUT_DIR, length);
    }

    /* Enable host channel */
    USB_DRD_SET_CHEP_RX_STATUS(instance, p_ch->phy_ch_num, USB_CH_RX_VALID);
  }
  else   /* Out Channel */
  {
    /* Multi packet transfer */
    if (p_ch->xfer_length > p_ch->max_packet)
    {
      length = p_ch->max_packet;
    }
    else
    {
      length = p_ch->xfer_length;
    }

    /* Configure and validate Tx endpoint */
    if (p_ch->double_buffer_en == (uint8_t)USB_CORE_CONFIG_DISABLED)
    {
      USB_DRD_WritePMA(instance, p_ch->p_xfer_buffer, p_ch->pma_address, (uint16_t)length);
      USB_DRD_SET_CHEP_TX_CNT(instance, p_ch->phy_ch_num, (uint16_t)length);

      /* SET PID SETUP */
      if (p_ch->data_pid == USB_CORE_CH_PID_SETUP)
      {
        USB_DRD_CHEP_TX_SETUP(instance, p_ch->phy_ch_num);
      }

      if ((p_ch->ep_type == USB_CORE_EP_TYPE_BULK)
          || (p_ch->ep_type == USB_CORE_EP_TYPE_INTR))
      {
        USB_DRD_CLEAR_TX_DTOG(instance, p_ch->phy_ch_num);

        /* Set Data PID */
        if (p_ch->data_pid == USB_CORE_CH_PID_DATA1)
        {
          USB_DRD_TX_DTOG(instance, p_ch->phy_ch_num);
        }
      }
    }
    else if (p_ch->ep_type == USB_CORE_EP_TYPE_BULK)
    {
      (void)USB_DRD_CH_BULK_DB_StartXfer(instance, p_ch, ch_reg, &length);
    }
    else
    {
      (void)USB_DRD_CH_ISO_DB_StartXfer(instance, p_ch, length);
    }

    /* Enable host channel */
    USB_DRD_SET_CHEP_TX_STATUS(instance, p_ch->phy_ch_num, USB_CH_TX_VALID);
  }

  return USB_CORE_OK;
}

/**
  * @brief  Halt a host channel in
  * @param  instance Selected device
  * @param  phy_ch_num physical host Channel number
  *         This parameter can be a value from 1 to 15
  * @retval status
  */
usb_core_status_t USB_DRD_HaltInChannel(uint32_t instance, usb_core_phy_chep_t phy_ch_num)
{
  /* Set disable to Channel */
  USB_DRD_SET_CHEP_RX_STATUS(instance, phy_ch_num, USB_CH_RX_DIS);

  return USB_CORE_OK;
}

/**
  * @brief  Halt a host channel out
  * @param  instance Selected device
  * @param  phy_ch_num physical host Channel number
  *         This parameter can be a value from 1 to 15
  * @retval status
  */
usb_core_status_t USB_DRD_HaltOutChannel(uint32_t instance, usb_core_phy_chep_t phy_ch_num)
{
  /* Set disable to Channel */
  USB_DRD_SET_CHEP_TX_STATUS(instance, phy_ch_num, USB_CH_TX_DIS);

  return USB_CORE_OK;
}

/**
  * @brief  Start Host Core
  * @param  instance Selected device
  * @retval status
  */
usb_core_status_t USB_DRD_StartHost(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);
  __IO uint32_t count = USB_DRD_PDWN_EXIT_CNT;

  /* Remove PowerDown */
  p_usb->CNTR &= ~USB_CNTR_PDWN;

  /* Few cycles to ensure exit from powerdown */
  while (count > 0U)
  {
    count--;
  }

  /* Clear Reset */
  p_usb->CNTR &= ~USB_CNTR_USBRST;

  return USB_CORE_OK;
}

/**
  * @brief  Stop Host Core
  * @param  instance Selected device
  * @retval status
  */
usb_core_status_t USB_DRD_StopHost(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  p_usb->ISTR &= ~(USB_ISTR_DIR | USB_ISTR_L1REQ |
                   USB_ISTR_ESOF | USB_ISTR_SOF |
                   USB_ISTR_RESET | USB_ISTR_DCON |
                   USB_ISTR_SUSP | USB_ISTR_WKUP |
                   USB_ISTR_ERR | USB_ISTR_PMAOVR |
                   USB_ISTR_CTR);

  /* Set PowerDown */
  p_usb->CNTR |= USB_CNTR_PDWN;

  /* Force a Reset */
  p_usb->CNTR |= USB_CNTR_USBRST;

  /* Clear all allocated virtual channels */
  USB_DRD_ClearPhysicalChannels();

  /* Reset the PMA current pointer */
  (void)USB_DRD_PMAReset();

  return USB_CORE_OK;
}

/**
  * @brief  Get a Logical Channel number from  physical Channel
  * @param  phy_ch_num
  *         This parameter can be a value from 0 to 7
  * @param  ch_dir  Channel direction
  *         -0 OUT_Channel
  *         -1 IN_Channel
  * @retval Channel number
  */
usb_core_channel_t USB_DRD_GetLogicalChannel(usb_core_phy_chep_t phy_ch_num, usb_core_ch_direction_t ch_dir)
{
  uint16_t logical_channel;

  /* Out Channel Direction */
  if (ch_dir == USB_CORE_CH_OUT_DIR)
  {
    if (((phy_chout_state[phy_ch_num] & 0x00F0U) >> 4U) != 0U)
    {
      logical_channel = ((phy_chout_state[phy_ch_num] & 0x00F0U) >> 4U) - 1U;
      return (usb_core_channel_t)logical_channel;
    }
    else
    {
      /* Channel not registered Error */
      return USB_CORE_CHANNEL_FF;
    }
  }
  /* IN Channel Direction */
  else
  {
    if (((phy_chin_state[phy_ch_num] & 0x00F0U) >> 4U) != 0U)
    {
      logical_channel = ((phy_chin_state[phy_ch_num] & 0x00F0U) >> 4U) - 1U;
      return (usb_core_channel_t)logical_channel;
    }
    else
    {
      /* Channel not registered Error */
      return USB_CORE_CHANNEL_FF;
    }
  }
}

/**
  * @brief  Free All Channel allocation
  */
void USB_DRD_ClearPhysicalChannels(void)
{
  uint8_t idx;

  for (idx = 0U; idx < USB_DRD_MAX_CHEP_NBR; idx++)
  {
    /* Reset channel allocation value */
    phy_chout_state[idx] = 0U;
    phy_chin_state[idx] = 0U;
  }
}

/**
  * @brief  Put the Device in suspend mode
  * @param  instance Selected device
  * @retval DRD Core status
  */
usb_core_status_t USB_DRD_PortSuspend(uint32_t instance)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);
  __IO uint32_t count = 0U;

  /* Set Suspend Mode */
  p_usb->CNTR |= USB_CNTR_SUSPEN;

  /* Wait for Suspend Ready */
  while ((p_usb->CNTR & USB_CNTR_SUSPRDY) == 0U)
  {
    if (++count > USB_DRD_TIMEOUT)
    {
      return USB_CORE_ERROR;
    }
  }

  return USB_CORE_OK;
}

/**
  * @brief  Resume Host Port
  * @param  instance  Selected device
  * @param  resume_status  resume status
  * @retval HAL status
  */
usb_core_status_t USB_DRD_PortResume(uint32_t instance, usb_core_port_resume_sts_t resume_status)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  if (resume_status == USB_CORE_PORT_RESUME_STS_SET)
  {
    /* Set Resume bit */
    p_usb->CNTR |= USB_CNTR_L2RES;
  }
  else
  {
    /* Clear Resume bit */
    p_usb->CNTR &= ~USB_CNTR_L2RES;
  }

  return USB_CORE_OK;
}

/**
  * @brief  USB_DRD_Port_Reset : Reset Host Port
  * @param  instance Selected device
  * @param  reset_status reset status
  * @retval HAL status
  * @note (1)The application must wait at least 10 ms
  *   before clearing the reset bit.
  */
usb_core_status_t USB_DRD_PortReset(uint32_t instance, usb_core_port_reset_sts_t reset_status)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  if (reset_status == USB_CORE_PORT_RESET_STS_SET)
  {
    /* Force USB Reset */
    p_usb->CNTR |= USB_CNTR_USBRST;
  }
  else
  {
    /* Release USB Reset */
    p_usb->CNTR &= ~USB_CNTR_USBRST;
  }

  return USB_CORE_OK;
}

/**
  * @brief  Return Host Core speed
  * @param  instance Selected host
  * @retval speed Host port speed
  *          This parameter can be one of these values
  *          USB_CORE_PORT_SPEED_FS Full speed mode
  *          USB_CORE_PORT_SPEED_LS Low speed mode
  */
usb_core_port_speed_t USB_DRD_GetHostPortSpeed(uint32_t instance)
{
  const usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  if ((p_usb->ISTR & USB_ISTR_LS_DCONN) != 0U)
  {
    return USB_CORE_PORT_SPEED_LS;
  }
  else
  {
    return USB_CORE_PORT_SPEED_FS;
  }
}

/**
  * @brief  Return Host Current Frame number
  * @param  instance Selected host
  * @retval current frame number
  */
uint32_t USB_DRD_GetCurrentFrame(uint32_t instance)
{
  const usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  return p_usb->FNR & 0x7FFU;
}

/**
  * @brief  USB_DRD_GetDmaStatus: return the HCD DMA status enabled or disabled
  * @param  instance  Selected device
  * @retval HCD DMA status enabled or disabled
  */
uint32_t USB_DRD_GetDmaStatus(uint32_t instance)
{
  STM32_UNUSED(instance);

  return (uint32_t)USB_CORE_CONFIG_DISABLED;
}
/**
  * @}
  */
/**
  * @}
  */

#endif /* defined (USB_DRD_FS) */

/**
  * @}
  */
