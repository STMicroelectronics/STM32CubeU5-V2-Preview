/**
  ******************************************************************************
  * @file    stm32u5xx_usb_otg_core.c
  * @brief   USB Core OTG driver.
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
      (#) Fill parameters of core config structure in usb_core_config_params_t structure.

      (#) Call USB_OTG_InitCore() API to initialize the USB Core peripheral.

      (#) The upper HAL HCD/PCD driver will call the right routines for its internal processes.

  @endverbatim

  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_usb_otg_core.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
/** @defgroup USB_OTG_CORE USB OTG CORE
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------------------------------------------*/
/** @defgroup USB_OTG_Core_Private_Functions USB OTG Core Private Functions
  * @{
  */
static usb_core_status_t USB_OTG_ResetCore(uint32_t instance);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup USB_OTG_Core_Private_Functions USB OTG Core Private Functions
  * @{
  */
/**
  * @brief  Reset the USB Core (needed after USB clock settings change)
  * @param  instance  Selected device
  * @retval OTG Core status
  */
static usb_core_status_t USB_OTG_ResetCore(uint32_t instance)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  __IO uint32_t count = 0U;

  /* Wait for AHB master IDLE state. */
  do
  {
    count++;

    if (count > USB_OTG_TIMEOUT)
    {
      return USB_CORE_ERROR;
    }
  } while ((p_usb->GRSTCTL & USB_OTG_GRSTCTL_AHBIDL) == 0U);

  /* Wait few cycles before setting core reset */
  count = 10U;

  while (count > 0U)
  {
    count--;
  }

  /* Core Soft Reset */
  p_usb->GRSTCTL |= USB_OTG_GRSTCTL_CSRST;

  do
  {
    count++;

    if (count > USB_OTG_TIMEOUT)
    {
      return USB_CORE_ERROR;
    }
  } while ((p_usb->GRSTCTL & USB_OTG_GRSTCTL_CSRST) == USB_OTG_GRSTCTL_CSRST);

  return USB_CORE_OK;
}

/**
  * @}
  */

/** @defgroup USB_OTG_Core_Exported_Functions USB Low Layer Exported Functions
  * @{
  */

/** @defgroup USB_OTG_Core_Exported_Functions_Group1 Initialization/de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
                      ##### Initialization/de-initialization functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the USB Core
  * @param  instance USB Instance
  * @param  p_core_config USB Instance configuration parameters
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_InitCore(uint32_t instance, const usb_core_config_params_t *p_core_config)
{
  usb_core_status_t ret = USB_CORE_OK;
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);

#if defined (USB_OTG_HS)
  if (p_core_config->phy_interface == USB_CORE_PHY_EMBEDDED_HS)
  {
    /* Init The UTMI Interface */
    p_usb->GUSBCFG &= ~(USB_OTG_GUSBCFG_TSDPS);
  }

  /* Reset after a PHY select */
  ret = USB_OTG_ResetCore(instance);

  if (p_core_config->dma_state == USB_CORE_CONFIG_ENABLED)
  {
    p_usb->GAHBCFG |= USB_OTG_GAHBCFG_HBSTLEN_2;
    p_usb->GAHBCFG |= USB_OTG_GAHBCFG_DMAEN;
  }

#else

  /* Select FS Embedded PHY */
  p_usb->GUSBCFG |= USB_OTG_GUSBCFG_PHYSEL;

  /* Reset after a PHY select */
  ret = USB_OTG_ResetCore(instance);

  if (p_core_config->bcd_state == USB_CORE_CONFIG_DISABLED)
  {
    /* Activate the USB Transceiver */
    p_usb->GCCFG |= USB_OTG_GCCFG_PWRDWN;
  }
  else
  {
    /* Deactivate the USB Transceiver */
    p_usb->GCCFG &= ~(USB_OTG_GCCFG_PWRDWN);
  }
#endif /* defined (USB_OTG_HS) */

  return ret;
}

/**
  * @brief  Deinitializes the USB Core
  * @param  instance USB Instance
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_DeInitCore(uint32_t instance)
{
  STM32_UNUSED(instance);

  return USB_CORE_OK;
}

/**
  * @}
  */

/** @defgroup USB_OTG_Core_Exported_Functions_Group2 Input and Output operation functions
  *  @brief   Data transfers functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the LL data
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  USB_OTG_EnableGlobalInterrupt
  *         Enables the controller's Global Int in the AHB Config reg
  * @param  instance  Selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_EnableGlobalInterrupt(uint32_t instance)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  p_usb->GAHBCFG |= USB_OTG_GAHBCFG_GINT;
  return USB_CORE_OK;
}

/**
  * @brief  USB_OTG_DisableGlobalInterrupt
  *         Disable the controller's Global Int in the AHB Config reg
  * @param  instance  Selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_DisableGlobalInterrupt(uint32_t instance)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  p_usb->GAHBCFG &= ~USB_OTG_GAHBCFG_GINT;
  return USB_CORE_OK;
}

/**
  * @brief  USB_OTG_SetCurrentMode Set functional mode
  * @param  instance  Selected device
  * @param  core_mode  current core mode
  *          This parameter can be one of these values:
  *            @arg USB_CORE_DEVICE_MODE Peripheral mode
  *            @arg USB_CORE_HOST_MODE Host mode
  * @retval USB_CORE_OK
  */
usb_core_status_t USB_OTG_SetCurrentMode(uint32_t instance, usb_core_mode_t core_mode)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);

  p_usb->GUSBCFG &= ~(USB_OTG_GUSBCFG_FHMOD | USB_OTG_GUSBCFG_FDMOD);

  if (core_mode == USB_CORE_HOST_MODE)
  {
    p_usb->GUSBCFG |= USB_OTG_GUSBCFG_FHMOD;
  }
  else if (core_mode == USB_CORE_DEVICE_MODE)
  {
    p_usb->GUSBCFG |= USB_OTG_GUSBCFG_FDMOD;
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
usb_core_mode_t USB_OTG_GetCurrentMode(uint32_t instance)
{
  const usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  uint32_t current_mode = (p_usb->GINTSTS) & USB_OTG_GINTSTS_CMOD;

  return (usb_core_mode_t)current_mode;
}


/**
  * @brief  Set BCD mode.
  * @param  instance Selected device
  * @param  bcd_config BCD configuration
  * @param  bcd_sts BCD OTG Core status
  */
usb_core_status_t USB_OTG_BCD_SetMode(uint32_t instance, usb_core_bcd_config_t bcd_config,
                                      usb_core_bcd_config_sts_t bcd_sts)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);

  switch (bcd_config)
  {
    case USB_CORE_BCD_CONFIG_DCD:
      if (bcd_sts == USB_CORE_BCD_CONFIG_STS_SET)
      {
        p_usb->GCCFG |= USB_OTG_GCCFG_DCDEN;
      }
      else
      {
        p_usb->GCCFG &= ~USB_OTG_GCCFG_DCDEN;
      }
      break;

    case USB_CORE_BCD_CONFIG_PD:
      if (bcd_sts == USB_CORE_BCD_CONFIG_STS_SET)
      {
        p_usb->GCCFG |= USB_OTG_GCCFG_PDEN;
      }
      else
      {
        p_usb->GCCFG &= ~USB_OTG_GCCFG_PDEN;
      }
      break;

    case USB_CORE_BCD_CONFIG_SD:
      if (bcd_sts == USB_CORE_BCD_CONFIG_STS_SET)
      {
        p_usb->GCCFG |= USB_OTG_GCCFG_SDEN;
      }
      else
      {
        p_usb->GCCFG &= ~USB_OTG_GCCFG_SDEN;
      }
      break;

    default:
      return USB_CORE_ERROR;
      break;
  }
  return USB_CORE_OK;
}

/**
  * @brief  Port Type Detection Process.
  * @param  instance Selected device
  * @param  detection BCD Primary and Secondary detection
  * @retval port detection status
  */
usb_core_bcd_port_status_t USB_OTG_BCD_PortTypeDetection(uint32_t instance, usb_core_bcd_detection_t detection)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  usb_core_bcd_port_status_t port_detection_status = USB_CORE_BCD_PORT_STATUS_DEFAULT;

  if (detection == USB_CORE_BCD_PRIMARY_DETECTION)
  {
#if defined (STM32U575xx) || defined (STM32U585xx)
    if ((p_usb->GCCFG & USB_OTG_GCCFG_PDET) == 0U)
#else
    if ((p_usb->GCCFG & USB_OTG_GCCFG_CHGDET) == 0U)
#endif /* defined (STM32U575xx) || defined (STM32U585xx) */
    {
      port_detection_status = USB_CORE_BCD_PORT_STATUS_STD_DOWNSTREAM;
    }
    else
    {
      port_detection_status = USB_CORE_BCD_PORT_STATUS_NOT_STD_DOWNSTREAM;
    }
  }
  else
  {
    /* Start secondary detection to check connection to Charging Downstream
    Port or Dedicated Charging Port */
#if defined (STM32U575xx) || defined (STM32U585xx)
    if ((p_usb->GCCFG & USB_OTG_GCCFG_SDET) == USB_OTG_GCCFG_SDET)
#else
    if ((p_usb->GCCFG & USB_OTG_GCCFG_FSVPLUS) == USB_OTG_GCCFG_FSVPLUS)
#endif /* defined (STM32U575xx) || defined (STM32U585xx) */
    {
      port_detection_status = USB_CORE_BCD_PORT_STATUS_DEDICATED_CHARGING;
    }
    else
    {
      port_detection_status = USB_CORE_BCD_PORT_STATUS_CHARGING_DOWNSTREAM;
    }
  }

  return port_detection_status;
}

/**
  * @brief  Activate BCD feature
  * @param  instance selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_BCD_Activate(uint32_t instance)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);

  p_usb->GCCFG &= ~(USB_OTG_GCCFG_PDEN);
  p_usb->GCCFG &= ~(USB_OTG_GCCFG_SDEN);

#if defined (STM32U575xx) || defined (STM32U585xx)
  /* Power Down USB transceiver  */
  p_usb->GCCFG &= ~(USB_OTG_GCCFG_PWRDWN);

  /* Enable Battery charging */
  p_usb->GCCFG |= USB_OTG_GCCFG_BCDEN;
#endif /* defined (STM32U575xx) || defined (STM32U585xx) */

  return USB_CORE_OK;
}

/**
  * @brief  DeActivate BCD feature
  * @param  instance selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_BCD_DeActivate(uint32_t instance)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);

  p_usb->GCCFG &= ~(USB_OTG_GCCFG_SDEN);
  p_usb->GCCFG &= ~(USB_OTG_GCCFG_PDEN);

#if defined (STM32U575xx) || defined (STM32U585xx)
  /* Disable Battery charging */
  p_usb->GCCFG &= ~(USB_OTG_GCCFG_BCDEN);
#endif /* defined (STM32U575xx) || defined (STM32U585xx) */

  return USB_CORE_OK;
}

/**
  * @brief  USB_ActivateRemoteWakeup active remote wakeup signalling
  * @param  instance Selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_ActivateRemoteWakeup(uint32_t instance)
{
  if ((USB_OTG_DEVICE(instance)->DSTS & USB_OTG_DSTS_SUSPSTS) == USB_OTG_DSTS_SUSPSTS)
  {
    /* Active Remote wakeup signalling */
    USB_OTG_DEVICE(instance)->DCTL |= USB_OTG_DCTL_RWUSIG;
  }

  return USB_CORE_OK;
}

/**
  * @brief  USB_DeActivateRemoteWakeup de-active remote wakeup signalling
  * @param  instance Selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_DeActivateRemoteWakeup(uint32_t instance)
{
  /* Active Remote wakeup signalling */
  USB_OTG_DEVICE(instance)->DCTL &= ~(USB_OTG_DCTL_RWUSIG);

  return USB_CORE_OK;
}


/**
  * @brief  USB_OTG_WritePacket : Writes a packet into the Tx FIFO associated
  *         with the EP/channel
  * @param  instance  Selected device
  * @param  p_src  pointer to source buffer
  * @param  ch_ep_num  endpoint or host channel number
  * @param  size_byte  Number of bytes to write
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_WritePacket(uint32_t instance, const uint8_t *p_src, uint8_t ch_ep_num, uint32_t size_byte)
{
  const usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  const uint8_t *p_src_buffer = p_src;
  uint32_t count32b;
  uint32_t count_idx;

  if ((p_usb->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) == 0U)
  {
    count32b = ((uint32_t)size_byte + 3U) / 4U;
    for (count_idx = 0U; count_idx < count32b; count_idx++)
    {
      USB_OTG_DFIFO(instance, ch_ep_num) = __UNALIGNED_UINT32_READ(p_src_buffer);
      p_src_buffer++;
      p_src_buffer++;
      p_src_buffer++;
      p_src_buffer++;
    }
  }

  return USB_CORE_OK;
}

/**
  * @brief  USB_OTG_ReadPacket : read a packet from the RX FIFO
  * @param  instance   Selected device
  * @param  p_dest     channel or endpoint number
  * @param  ch_ep_num  source pointer
  * @param  size_byte  Number of bytes to read
  * @retval pointer to destination buffer
  */
void *USB_OTG_ReadPacket(uint32_t instance, uint8_t *p_dest, uint8_t ch_ep_num, uint32_t size_byte)
{
  uint8_t *p_dest_buffer = p_dest;
  uint32_t data;
  uint32_t count_idx;
  uint32_t count32b = (uint32_t)size_byte >> 2U;
  uint32_t remaining_bytes = size_byte % 4U;

  STM32_UNUSED(ch_ep_num);

  for (count_idx = 0U; count_idx < count32b; count_idx++)
  {
    __UNALIGNED_UINT32_WRITE(p_dest_buffer, USB_OTG_DFIFO(instance, 0U));
    p_dest_buffer++;
    p_dest_buffer++;
    p_dest_buffer++;
    p_dest_buffer++;
  }

  /* When Number of data is not word aligned, read the remaining byte */
  if (remaining_bytes != 0U)
  {
    count_idx = 0U;
    __UNALIGNED_UINT32_WRITE(&data, USB_OTG_DFIFO(instance, 0U));

    do
    {
      *(uint8_t *)p_dest_buffer = (uint8_t)(data >> (8U * (uint8_t)(count_idx)));
      count_idx++;
      p_dest_buffer++;
      remaining_bytes--;
    } while (remaining_bytes != 0U);
  }

  return ((void *)p_dest_buffer);
}

/**
  * @brief  USB_OTG_ReadInterrupts: return the global USB interrupt status
  * @param  instance  Selected device
  * @retval USB Global Interrupt status
  */
uint32_t USB_OTG_ReadInterrupts(uint32_t instance)
{
  const usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  uint32_t gintsts_reg;

  gintsts_reg = p_usb->GINTSTS;
  gintsts_reg &= p_usb->GINTMSK;

  return gintsts_reg;
}

/**
  * @brief  USB_OTG_ClearInterrupts: clear a USB interrupt
  * @param  instance  Selected device
  * @param  interrupt  flag
  */
void USB_OTG_ClearInterrupts(uint32_t instance, uint32_t interrupt)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  p_usb->GINTSTS &= interrupt;
}

/**
  * @brief  Set Tx FIFO Size
  * @param  instance selected device
  * @param  fifo number
  * @param  size_words fifo size in words
  * @retval HAL OTG Core status
  */
usb_core_status_t USB_OTG_SetTxFiFoSize(uint32_t instance, uint8_t fifo, uint16_t size_words)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  uint8_t fifo_idx;
  uint32_t Tx_Offset;

  /*  TXn min size = 16 32bits words. (n  : Transmit FIFO index)
      When a TxFIFO is not used, the Configuration to be as follows:
          case 1 :  n > m    and Txn is not used    (n,m  : Transmit FIFO indexes)
         --> Txm can use the space allocated for Txn.
         case2  :  n < m    and Txn is not used    (n,m  : Transmit FIFO indexes)
         --> Txn to be configured with the minimum space of 16 words
     The FIFO is used optimally when used TxFIFOs are allocated in the top
         of the FIFO.Ex: use EP1 and EP2 as IN instead of EP1 and EP3 as IN ones.
     When DMA is used 3n * FIFO locations to be reserved for internal DMA registers */

  Tx_Offset = p_usb->GRXFSIZ;

  if (fifo == 0U)
  {
    p_usb->DIEPTXF0_HNPTXFSIZ = ((uint32_t)size_words << 16) | Tx_Offset;
  }
  else
  {
    Tx_Offset += (p_usb->DIEPTXF0_HNPTXFSIZ) >> 16;
    for (fifo_idx = 0U; fifo_idx < (fifo - 1U); fifo_idx++)
    {
      Tx_Offset += (p_usb->DIEPTXF[fifo_idx] >> 16);
    }

    /* Multiply Tx_Size by 2 to get higher performance */
    p_usb->DIEPTXF[fifo - 1U] = ((uint32_t)size_words << 16) | Tx_Offset;
  }

  return USB_CORE_OK;
}

/**
  * @brief  Set Rx FIFO Size
  * @param  instance selected device
  * @param  size_words fifo size in words
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_SetRxFiFoSize(uint32_t instance, uint16_t size_words)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);

  p_usb->GRXFSIZ = size_words;

  return USB_CORE_OK;
}

/**
  * @}
  */

/** @defgroup USB_OTG_CORE_Exported_Functions_Group3 Peripheral Control functions
  *  @brief   management functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the PCD data
    transfers.

@endverbatim
  * @{
  */


/**
  * @brief  Flush a Tx FIFO
  * @param  instance  Selected device
  * @param  tx_fifo  FIFO number
  *         This parameter can be a value from 1 to 15
            15 means Flush all Tx FIFOs
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_FlushTxFifo(uint32_t instance, uint32_t tx_fifo)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  __IO uint32_t count = 0U;

  /* Wait for AHB master IDLE state. */
  do
  {
    count++;

    if (count > USB_OTG_TIMEOUT)
    {
      return USB_CORE_ERROR;
    }
  } while ((p_usb->GRSTCTL & USB_OTG_GRSTCTL_AHBIDL) == 0U);

  /* Flush TX Fifo */
  count = 0U;
  p_usb->GRSTCTL = (USB_OTG_GRSTCTL_TXFFLSH | (tx_fifo << 6));

  do
  {
    count++;

    if (count > USB_OTG_TIMEOUT)
    {
      return USB_CORE_ERROR;
    }
  } while ((p_usb->GRSTCTL & USB_OTG_GRSTCTL_TXFFLSH) == USB_OTG_GRSTCTL_TXFFLSH);

  return USB_CORE_OK;
}

/**
  * @brief  USB_OTG_FlushRxFifo  Flush Rx FIFO
  * @param  instance  Selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_FlushRxFifo(uint32_t instance)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  __IO uint32_t count = 0U;

  /* Wait for AHB master IDLE state. */
  do
  {
    count++;

    if (count > USB_OTG_TIMEOUT)
    {
      return USB_CORE_ERROR;
    }
  } while ((p_usb->GRSTCTL & USB_OTG_GRSTCTL_AHBIDL) == 0U);

  /* Flush RX Fifo */
  count = 0U;
  p_usb->GRSTCTL = USB_OTG_GRSTCTL_RXFFLSH;

  do
  {
    count++;

    if (count > USB_OTG_TIMEOUT)
    {
      return USB_CORE_ERROR;
    }
  } while ((p_usb->GRSTCTL & USB_OTG_GRSTCTL_RXFFLSH) == USB_OTG_GRSTCTL_RXFFLSH);

  return USB_CORE_OK;
}


/**
  * @}
  */

/**
  * @}
  */

/** @defgroup USB_OTG_Core_Device_Exported_Functions USB Core Device Exported Functions
  * @{
  */

/**
  * @brief  Initialize the USB OTG PCD Driver
  * @param  p_driver pointer to USB PCD driver structure
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_PCD_InitDriver(usb_core_pcd_driver_t *p_driver)
{
  p_driver->core_init = USB_OTG_InitCore;
  p_driver->core_deinit = USB_OTG_DeInitCore;
  p_driver->core_set_mode = USB_OTG_SetCurrentMode;
  p_driver->core_get_mode = USB_OTG_GetCurrentMode;
  p_driver->core_enable_interrupts = USB_OTG_EnableGlobalInterrupt;
  p_driver->core_disable_interrupts = USB_OTG_DisableGlobalInterrupt;
  p_driver->device_init = USB_OTG_InitDevice;
  p_driver->device_start = USB_OTG_StartDevice;
  p_driver->device_stop = USB_OTG_StopDevice;
  p_driver->device_connect = USB_OTG_ConnectDevice;
  p_driver->device_disconnect = USB_OTG_DisconnectDevice;
  p_driver->device_set_address = USB_OTG_SetDeviceAddress;
  p_driver->device_get_speed = USB_OTG_GetDeviceSpeed;
  p_driver->ep_activate = USB_OTG_ActivateEndpoint;
  p_driver->ep_deactivate = USB_OTG_DeactivateEndpoint;
  p_driver->ep_start_transfer = USB_OTG_StartEndpointXfer;
  p_driver->ep_stop_transfer = USB_OTG_StopEndpointXfer;
  p_driver->ep_set_stall = USB_OTG_SetEndpointStall;
  p_driver->ep_clear_stall = USB_OTG_ClearEndpointStall;
  p_driver->ep0_out_start = USB_OTG_StartOutEP0;
  p_driver->set_tx_fifo = USB_OTG_SetTxFiFoSize;
  p_driver->set_rx_fifo = USB_OTG_SetRxFiFoSize;
  p_driver->flush_tx_fifo = USB_OTG_FlushTxFifo;
  p_driver->flush_rx_fifo = USB_OTG_FlushRxFifo;
  p_driver->read_packet = USB_OTG_ReadPacket;
  p_driver->write_packet = USB_OTG_WritePacket;
  p_driver->remote_wakeup_activate = USB_OTG_ActivateRemoteWakeup;
  p_driver->remote_wakeup_deactivate = USB_OTG_DeActivateRemoteWakeup;

  p_driver->lpm_activate = USB_OTG_LPM_Activate;
  p_driver->lpm_deactivate = USB_OTG_LPM_DeActivate;

  p_driver->bcd_activate = USB_OTG_BCD_Activate;
  p_driver->bcd_deactivate = USB_OTG_BCD_DeActivate;
  p_driver->bcd_set_mode = USB_OTG_BCD_SetMode;
  p_driver->bcd_detect_port_type = USB_OTG_BCD_PortTypeDetection;

  return USB_CORE_OK;
}

/**
  * @brief  Initializes the USB_OTG controller registers
  *         for device mode
  * @param  instance  Selected device
  * @param  p_core_config USB Instance configuration parameters
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_InitDevice(uint32_t instance, const usb_core_config_params_t *p_core_config)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  usb_core_status_t ret = USB_CORE_OK;
  uint32_t ep_idx;

  for (ep_idx = 0U; ep_idx < 15U; ep_idx++)
  {
    p_usb->DIEPTXF[ep_idx] = 0U;
  }

#if defined (USB_OTG_HS)
  /* Disable USB PHY pulldown resistors */
  p_usb->GCCFG &= ~USB_OTG_GCCFG_PULLDOWNEN;
#endif /* defined (USB_OTG_HS) */

  /* VBUS Sensing setup */
  if (p_core_config->vbus_sense_state == USB_CORE_CONFIG_DISABLED)
  {
    USB_OTG_DEVICE(instance)->DCTL |= USB_OTG_DCTL_SDIS;

    /* Deactivate VBUS Sensing B */
    p_usb->GCCFG &= ~USB_OTG_GCCFG_VBDEN;

    /* B-peripheral session valid override enable */
#if defined (USB_OTG_HS)
    p_usb->GCCFG |= USB_OTG_GCCFG_VBVALEXTOEN;
    p_usb->GCCFG |= USB_OTG_GCCFG_VBVALOVAL;
#else
    p_usb->GOTGCTL |= USB_OTG_GOTGCTL_BVALOEN;
    p_usb->GOTGCTL |= USB_OTG_GOTGCTL_BVALOVAL;
#endif /* defined (USB_OTG_HS) */
  }
  else
  {
#if defined (USB_OTG_HS)
    /* B-peripheral session valid override disable */
    p_usb->GCCFG &= ~USB_OTG_GCCFG_VBVALEXTOEN;
    p_usb->GCCFG &= ~USB_OTG_GCCFG_VBVALOVAL;
#endif /* defined (USB_OTG_HS) */

    /* Enable HW VBUS sensing */
    p_usb->GCCFG |= USB_OTG_GCCFG_VBDEN;
  }

  /* Restart the Phy Clock */
  USB_OTG_PCGCCTL(instance) = 0U;

#if defined (USB_OTG_HS)
  if (p_core_config->phy_interface == USB_CORE_PHY_EMBEDDED_HS)
  {
    if (p_core_config->core_speed == USB_CORE_SPEED_HS)
    {
      /* Set Core speed to High speed mode */
      (void)USB_OTG_SetDeviceSpeed(instance, USB_OTG_SPEED_HIGH);
    }
    else
    {
      /* Set Core speed to Full speed mode */
      (void)USB_OTG_SetDeviceSpeed(instance, USB_OTG_SPEED_HIGH_IN_FULL);
    }
  }
  else
#endif /* defined (USB_OTG_HS) */
  {
    /* Set Core speed to Full speed mode */
    (void)USB_OTG_SetDeviceSpeed(instance, USB_OTG_SPEED_FULL);
  }

  /* Flush the FIFOs */
  if (USB_OTG_FlushTxFifo(instance, 0x10U) != USB_CORE_OK) /* all Tx FIFOs */
  {
    ret = USB_CORE_ERROR;
  }

  if (USB_OTG_FlushRxFifo(instance) != USB_CORE_OK)
  {
    ret = USB_CORE_ERROR;
  }

  /* Clear all pending Device Interrupts */
  USB_OTG_DEVICE(instance)->DIEPMSK = 0U;
  USB_OTG_DEVICE(instance)->DOEPMSK = 0U;
  USB_OTG_DEVICE(instance)->DAINTMSK = 0U;

  for (ep_idx = 0U; ep_idx < p_core_config->endpoints_nbr; ep_idx++)
  {
    if ((USB_OTG_IN_EP(instance, ep_idx)->DIEPCTL & USB_OTG_DIEPCTL_EPENA) == USB_OTG_DIEPCTL_EPENA)
    {
      if (ep_idx == 0U)
      {
        USB_OTG_IN_EP(instance, ep_idx)->DIEPCTL = USB_OTG_DIEPCTL_SNAK;
      }
      else
      {
        USB_OTG_IN_EP(instance, ep_idx)->DIEPCTL = USB_OTG_DIEPCTL_EPDIS | USB_OTG_DIEPCTL_SNAK;
      }
    }
    else
    {
      USB_OTG_IN_EP(instance, ep_idx)->DIEPCTL = 0U;
    }

    USB_OTG_IN_EP(instance, ep_idx)->DIEPTSIZ = 0U;
    USB_OTG_IN_EP(instance, ep_idx)->DIEPINT  = 0xFB7FU;
  }

  for (ep_idx = 0U; ep_idx < p_core_config->endpoints_nbr; ep_idx++)
  {
    if ((USB_OTG_OUT_EP(instance, ep_idx)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA)
    {
      if (ep_idx == 0U)
      {
        USB_OTG_OUT_EP(instance, ep_idx)->DOEPCTL = USB_OTG_DOEPCTL_SNAK;
      }
      else
      {
        USB_OTG_OUT_EP(instance, ep_idx)->DOEPCTL = USB_OTG_DOEPCTL_EPDIS | USB_OTG_DOEPCTL_SNAK;
      }
    }
    else
    {
      USB_OTG_OUT_EP(instance, ep_idx)->DOEPCTL = 0U;
    }

    USB_OTG_OUT_EP(instance, ep_idx)->DOEPTSIZ = 0U;
    USB_OTG_OUT_EP(instance, ep_idx)->DOEPINT  = 0xFB7FU;
  }

  USB_OTG_DEVICE(instance)->DIEPMSK &= ~(USB_OTG_DIEPMSK_TXFURM);

  /* Disable all interrupts. */
  p_usb->GINTMSK = 0U;

  /* Clear any pending interrupts */
  p_usb->GINTSTS = 0xBFFFFFFFU;

  /* Enable the common interrupts */
  if (p_core_config->dma_state == USB_CORE_CONFIG_DISABLED)
  {
    p_usb->GINTMSK |= USB_OTG_GINTMSK_RXFLVLM;
  }

  /* Enable interrupts matching to the Device mode ONLY */
  p_usb->GINTMSK |= USB_OTG_GINTMSK_USBSUSPM | USB_OTG_GINTMSK_USBRST |
                    USB_OTG_GINTMSK_ENUMDNEM | USB_OTG_GINTMSK_IEPINT |
                    USB_OTG_GINTMSK_OEPINT   | USB_OTG_GINTMSK_IISOIXFRM |
                    USB_OTG_GINTMSK_PXFRM_IISOOXFRM | USB_OTG_GINTMSK_WUIM;

  if (p_core_config->sof_state == USB_CORE_CONFIG_ENABLED)
  {
    p_usb->GINTMSK |= USB_OTG_GINTMSK_SOFM;
  }

  if (p_core_config->vbus_sense_state == USB_CORE_CONFIG_ENABLED)
  {
    p_usb->GINTMSK |= (USB_OTG_GINTMSK_SRQIM | USB_OTG_GINTMSK_OTGINT);
  }

  return ret;
}

/**
  * @brief  Initializes the DevSpd field of DCFG register
  *         depending the PHY type and the enumeration speed of the device.
  * @param  instance  Selected device
  * @param  speed  device speed
  *          This parameter can be one of these values:
  *            @arg USB_OTG_SPEED_HIGH: High speed mode
  *            @arg USB_OTG_SPEED_HIGH_IN_FULL: High speed core in Full Speed mode
  *            @arg USB_OTG_SPEED_FULL: Full speed mode
  * @retval  OTG Core status
  */
usb_core_status_t USB_OTG_SetDeviceSpeed(uint32_t instance, uint8_t speed)
{
  USB_OTG_DEVICE(instance)->DCFG |= speed;

  return USB_CORE_OK;
}

/**
  * @brief  Return the Dev Speed
  * @param  instance  Selected device
  * @retval device_speed  device speed
  *          This parameter can be one of these values:
  *          @arg USB_CORE_DEVICE_SPEED_HS: High speed mode
  *          @arg USB_CORE_DEVICE_SPEED_FS: Full speed mode
  */
usb_core_device_speed_t USB_OTG_GetDeviceSpeed(uint32_t instance)
{
  usb_core_device_speed_t device_speed;
  uint32_t dev_enum_speed = USB_OTG_DEVICE(instance)->DSTS & USB_OTG_DSTS_ENUMSPD;

  if (dev_enum_speed == USB_OTG_DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ)
  {
    device_speed = USB_CORE_DEVICE_SPEED_HS;
  }
  else if ((dev_enum_speed == USB_OTG_DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ)
           || (dev_enum_speed == USB_OTG_DSTS_ENUMSPD_FS_PHY_48MHZ))
  {
    device_speed = USB_CORE_DEVICE_SPEED_FS;
  }
  else
  {
    device_speed = USB_CORE_DEVICE_SPEED_ERROR;
  }

  return device_speed;
}

/**
  * @brief  USB_ReadDevAllOutEpInterrupt: return the USB device OUT endpoints interrupt status
  * @param  instance  Selected device
  * @retval USB Device OUT EP interrupt status
  */
uint32_t USB_OTG_ReadDevAllOutEpInterrupt(uint32_t instance)
{
  uint32_t daint_reg;

  daint_reg  = USB_OTG_DEVICE(instance)->DAINT;
  daint_reg &= USB_OTG_DEVICE(instance)->DAINTMSK;

  return ((daint_reg & 0xffff0000U) >> 16);
}

/**
  * @brief  USB_ReadDevAllInEpInterrupt: return the USB device IN endpoints interrupt status
  * @param  instance  Selected device
  * @retval USB Device IN EP interrupt status
  */
uint32_t USB_OTG_ReadDevAllInEpInterrupt(uint32_t instance)
{
  uint32_t daint_reg;

  daint_reg  = USB_OTG_DEVICE(instance)->DAINT;
  daint_reg &= USB_OTG_DEVICE(instance)->DAINTMSK;

  return ((daint_reg & 0xFFFFU));
}

/**
  * @brief  Returns Device OUT EP Interrupt register
  * @param  instance  Selected device
  * @param  ep_num  endpoint number
  *          This parameter can be a value from 0 to 15
  * @retval Device OUT EP Interrupt register
  */
uint32_t USB_OTG_ReadDevOutEPInterrupt(uint32_t instance, uint8_t ep_num)
{
  uint32_t doepint_reg;

  doepint_reg  = USB_OTG_OUT_EP(instance, ep_num)->DOEPINT;
  doepint_reg &= USB_OTG_DEVICE(instance)->DOEPMSK;

  return doepint_reg;
}

/**
  * @brief  Returns Device IN EP Interrupt register
  * @param  instance  Selected device
  * @param  ep_num  endpoint number
  *          This parameter can be a value from 0 to 15
  * @retval Device IN EP Interrupt register
  */
uint32_t USB_OTG_ReadDevInEPInterrupt(uint32_t instance, uint8_t ep_num)
{
  uint32_t diepint_reg;
  uint32_t msk;
  uint32_t emp;

  msk = USB_OTG_DEVICE(instance)->DIEPMSK;
  emp = USB_OTG_DEVICE(instance)->DIEPEMPMSK;
  msk |= ((emp >> (ep_num & USB_OTG_EP_ADDR_MSK)) & 0x1U) << 7;
  diepint_reg = USB_OTG_IN_EP(instance, ep_num)->DIEPINT & msk;

  return diepint_reg;
}

/**
  * @brief  Set the USB turnaround time
  * @param  instance USB Instance
  * @param  hclk: AHB clock frequency
  * @param  device_speed USB device speed
  * @retval USB turnaround time In PHY Clocks number
  */
usb_core_status_t USB_OTG_SetTurnaroundTime(uint32_t instance, uint32_t hclk, usb_core_device_speed_t device_speed)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  uint32_t usb_trd;

  /* The USBTRD is configured according to the tables below, depending on AHB frequency
  used by application. In the low AHB frequency range it is used to stretch enough the USB response
  time to IN tokens, the USB turnaround time, so to compensate for the longer AHB read access
  latency to the Data FIFO */
  if (device_speed == USB_CORE_DEVICE_SPEED_FS)
  {
    if ((hclk >= 14200000U) && (hclk < 15000000U))
    {
      /* hclk Clock Range between 14.2-15 MHz */
      usb_trd = 0xFU;
    }
    else if ((hclk >= 15000000U) && (hclk < 16000000U))
    {
      /* hclk Clock Range between 15-16 MHz */
      usb_trd = 0xEU;
    }
    else if ((hclk >= 16000000U) && (hclk < 17200000U))
    {
      /* hclk Clock Range between 16-17.2 MHz */
      usb_trd = 0xDU;
    }
    else if ((hclk >= 17200000U) && (hclk < 18500000U))
    {
      /* hclk Clock Range between 17.2-18.5 MHz */
      usb_trd = 0xCU;
    }
    else if ((hclk >= 18500000U) && (hclk < 20000000U))
    {
      /* hclk Clock Range between 18.5-20 MHz */
      usb_trd = 0xBU;
    }
    else if ((hclk >= 20000000U) && (hclk < 21800000U))
    {
      /* hclk Clock Range between 20-21.8 MHz */
      usb_trd = 0xAU;
    }
    else if ((hclk >= 21800000U) && (hclk < 24000000U))
    {
      /* hclk Clock Range between 21.8-24 MHz */
      usb_trd = 0x9U;
    }
    else if ((hclk >= 24000000U) && (hclk < 27700000U))
    {
      /* hclk Clock Range between 24-27.7 MHz */
      usb_trd = 0x8U;
    }
    else if ((hclk >= 27700000U) && (hclk < 32000000U))
    {
      /* hclk Clock Range between 27.7-32 MHz */
      usb_trd = 0x7U;
    }
    else /* if(hclk >= 32000000) */
    {
      /* hclk Clock Range between 32-200 MHz */
      usb_trd = 0x6U;
    }
  }
  else if (device_speed == USB_CORE_DEVICE_SPEED_HS)
  {
    usb_trd = USB_OTG_HS_TRDT_VALUE;
  }
  else
  {
    usb_trd = USB_OTG_DEFAULT_TRDT_VALUE;
  }

  p_usb->GUSBCFG &= ~USB_OTG_GUSBCFG_TRDT;
  p_usb->GUSBCFG |= (uint32_t)((usb_trd << 10) & USB_OTG_GUSBCFG_TRDT);

  return USB_CORE_OK;
}

/**
  * @brief  Activate and configure an endpoint
  * @param  instance  Selected device
  * @param  p_ep pointer to endpoint structure
  * @retval HAL OTG Core status
  */
usb_core_status_t USB_OTG_ActivateEndpoint(uint32_t instance, usb_core_ep_t *p_ep)
{
  if (p_ep->dir == USB_CORE_EP_IN_DIR)
  {
    USB_OTG_DEVICE(instance)->DAINTMSK |= USB_OTG_DAINTMSK_IEPM & (uint32_t)(1UL << p_ep->num);

    if ((USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL & USB_OTG_DIEPCTL_USBAEP) == 0U)
    {
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= (p_ep->max_packet & USB_OTG_DIEPCTL_MPSIZ) |
                                                     ((uint32_t)p_ep->type << 18) | ((uint32_t)p_ep->num << 22) |
                                                     USB_OTG_DIEPCTL_SD0PID_SEVNFRM |
                                                     USB_OTG_DIEPCTL_USBAEP;
    }
  }
  else
  {
    USB_OTG_DEVICE(instance)->DAINTMSK |= USB_OTG_DAINTMSK_OEPM &
                                          ((uint32_t)(1UL << ((uint8_t)p_ep->num & USB_OTG_EP_ADDR_MSK)) << 16);

    if (((USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL) & USB_OTG_DOEPCTL_USBAEP) == 0U)
    {
      USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL |= (p_ep->max_packet & USB_OTG_DOEPCTL_MPSIZ) |
                                                      ((uint32_t)p_ep->type << 18) |
                                                      USB_OTG_DIEPCTL_SD0PID_SEVNFRM |
                                                      USB_OTG_DOEPCTL_USBAEP;
    }
  }
  return USB_CORE_OK;
}

/**
  * @brief  Activate and configure a dedicated endpoint
  * @param  instance  Selected device
  * @param  p_ep pointer to endpoint structure
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_ActivateDedicatedEndpoint(uint32_t instance, usb_core_ep_t *p_ep)
{
  if (p_ep->dir == USB_CORE_EP_IN_DIR)
  {
    if (((USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL) & USB_OTG_DIEPCTL_USBAEP) == 0U)
    {
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= (p_ep->max_packet & USB_OTG_DIEPCTL_MPSIZ) |
                                                     ((uint32_t)p_ep->type << 18) | ((uint32_t)p_ep->num << 22) |
                                                     USB_OTG_DIEPCTL_SD0PID_SEVNFRM |
                                                     USB_OTG_DIEPCTL_USBAEP;
    }

    USB_OTG_DEVICE(instance)->DEACHMSK |= USB_OTG_DAINTMSK_IEPM &
                                          (uint32_t)(1UL << ((uint8_t)p_ep->num & USB_OTG_EP_ADDR_MSK));
  }
  else
  {
    if (((USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL) & USB_OTG_DOEPCTL_USBAEP) == 0U)
    {
      USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL |= (p_ep->max_packet & USB_OTG_DOEPCTL_MPSIZ) |
                                                      ((uint32_t)p_ep->type << 18) | ((uint32_t)p_ep->num << 22) |
                                                      USB_OTG_DOEPCTL_USBAEP;
    }

    USB_OTG_DEVICE(instance)->DEACHMSK |= USB_OTG_DAINTMSK_OEPM &
                                          ((uint32_t)(1UL << ((uint8_t)p_ep->num & USB_OTG_EP_ADDR_MSK)) << 16);
  }

  return USB_CORE_OK;
}

/**
  * @brief  De-activate and de-initialize an endpoint
  * @param  instance  Selected device
  * @param  p_ep pointer to endpoint structure
  * @retval HAL OTG Core status
  */
usb_core_status_t USB_OTG_DeactivateEndpoint(uint32_t instance, const usb_core_ep_t *p_ep)
{
  if (p_ep->dir == USB_CORE_EP_IN_DIR)
  {
    if ((USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL & USB_OTG_DIEPCTL_EPENA) == USB_OTG_DIEPCTL_EPENA)
    {
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= USB_OTG_DIEPCTL_SNAK;
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= USB_OTG_DIEPCTL_EPDIS;
    }

    USB_OTG_DEVICE(instance)->DEACHMSK &= ~(USB_OTG_DAINTMSK_IEPM &
                                            (uint32_t)(1UL << ((uint8_t)p_ep->num & USB_OTG_EP_ADDR_MSK)));

    USB_OTG_DEVICE(instance)->DAINTMSK &= ~(USB_OTG_DAINTMSK_IEPM &
                                            (uint32_t)(1UL << ((uint8_t)p_ep->num & USB_OTG_EP_ADDR_MSK)));

    USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL &= ~(USB_OTG_DIEPCTL_USBAEP |
                                                     USB_OTG_DIEPCTL_MPSIZ |
                                                     USB_OTG_DIEPCTL_TXFNUM |
                                                     USB_OTG_DIEPCTL_SD0PID_SEVNFRM |
                                                     USB_OTG_DIEPCTL_EPTYP);
  }
  else
  {
    if ((USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA)
    {
      USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL |= USB_OTG_DOEPCTL_SNAK;
      USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL |= USB_OTG_DOEPCTL_EPDIS;
    }

    USB_OTG_DEVICE(instance)->DEACHMSK &= ~(USB_OTG_DAINTMSK_OEPM &
                                            ((uint32_t)(1UL << ((uint8_t)p_ep->num & USB_OTG_EP_ADDR_MSK)) << 16));

    USB_OTG_DEVICE(instance)->DAINTMSK &= ~(USB_OTG_DAINTMSK_OEPM &
                                            ((uint32_t)(1UL << ((uint8_t)p_ep->num & USB_OTG_EP_ADDR_MSK)) << 16));

    USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL &= ~(USB_OTG_DOEPCTL_USBAEP |
                                                      USB_OTG_DOEPCTL_MPSIZ |
                                                      USB_OTG_DOEPCTL_SD0PID_SEVNFRM |
                                                      USB_OTG_DOEPCTL_EPTYP);
  }

  return USB_CORE_OK;
}

/**
  * @brief  De-activate and de-initialize a dedicated endpoint
  * @param  instance  Selected device
  * @param  p_ep pointer to endpoint structure
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_DeactivateDedicatedEndpoint(uint32_t instance, usb_core_ep_t *p_ep)
{
  if (p_ep->dir == USB_CORE_EP_IN_DIR)
  {
    if ((USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL & USB_OTG_DIEPCTL_EPENA) == USB_OTG_DIEPCTL_EPENA)
    {
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= USB_OTG_DIEPCTL_SNAK;
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= USB_OTG_DIEPCTL_EPDIS;
    }

    USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL &= ~USB_OTG_DIEPCTL_USBAEP;
    USB_OTG_DEVICE(instance)->DAINTMSK &= ~(USB_OTG_DAINTMSK_IEPM &
                                            (uint32_t)(1UL << ((uint8_t)p_ep->num & USB_OTG_EP_ADDR_MSK)));
  }
  else
  {
    if ((USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA)
    {
      USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL |= USB_OTG_DOEPCTL_SNAK;
      USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL |= USB_OTG_DOEPCTL_EPDIS;
    }

    USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL &= ~USB_OTG_DOEPCTL_USBAEP;
    USB_OTG_DEVICE(instance)->DAINTMSK &= ~(USB_OTG_DAINTMSK_OEPM &
                                            ((uint32_t)(1UL << ((uint8_t)p_ep->num & USB_OTG_EP_ADDR_MSK)) << 16));
  }

  return USB_CORE_OK;
}

/**
  * @brief  Setup and starts a transfer over an EP
  * @param  instance  Selected device
  * @param  p_ep pointer to endpoint structure
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_StartEndpointXfer(uint32_t instance, usb_core_ep_t *p_ep)
{
  const usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  uint16_t packet_count;

  /* IN endpoint */
  if (p_ep->dir == USB_CORE_EP_IN_DIR)
  {
    /* Zero Length Packet? */
    if (p_ep->xfer_length == 0U)
    {
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_PKTCNT);
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_PKTCNT & (1U << 19));
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_XFRSIZ);
    }
    else
    {
      /* Program the transfer size and packet count
      * as follows: xfersize = N * maxpacket + short_packet
      *             pktcnt = N + (short_packet exist ? 1 : 0)
      */
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_XFRSIZ);
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_PKTCNT);

      if (p_ep->num == USB_CORE_ENDPOINT_0)
      {
        if (p_ep->xfer_length > p_ep->max_packet)
        {
          p_ep->xfer_length = p_ep->max_packet;
        }

        USB_OTG_IN_EP(instance, p_ep->num)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_PKTCNT & (1U << 19));
      }
      else
      {
        packet_count = (uint16_t)((p_ep->xfer_length + p_ep->max_packet - 1U) / p_ep->max_packet);
        USB_OTG_IN_EP(instance, p_ep->num)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_PKTCNT & ((uint32_t)packet_count << 19));

        if (p_ep->type == USB_CORE_EP_TYPE_ISOC)
        {
          USB_OTG_IN_EP(instance, p_ep->num)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_MULCNT);
          USB_OTG_IN_EP(instance, p_ep->num)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_MULCNT & ((uint32_t)packet_count << 29));
        }
      }

      USB_OTG_IN_EP(instance, p_ep->num)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_XFRSIZ & p_ep->xfer_length);
    }

    if ((p_usb->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) == USB_OTG_GAHBCFG_DMAEN)
    {
      p_ep->dma_addr = (uint32_t)p_ep->p_xfer_buffer;

      if ((uint32_t)p_ep->dma_addr != 0U)
      {
        USB_OTG_IN_EP(instance, p_ep->num)->DIEPDMA = (uint32_t)(p_ep->dma_addr);
      }

      if (p_ep->type == USB_CORE_EP_TYPE_ISOC)
      {
        if ((USB_OTG_DEVICE(instance)->DSTS & (1U << 8)) == 0U)
        {
          USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= USB_OTG_DIEPCTL_SODDFRM;
        }
        else
        {
          USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= USB_OTG_DIEPCTL_SD0PID_SEVNFRM;
        }
      }

      /* EP enable, IN data in FIFO */
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= (USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA);
    }
    else
    {
      /* EP enable, IN data in FIFO */
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= (USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA);

      if (p_ep->type != USB_CORE_EP_TYPE_ISOC)
      {
        /* Enable the Tx FIFO Empty Interrupt for this EP */
        if (p_ep->xfer_length > 0U)
        {
          USB_OTG_DEVICE(instance)->DIEPEMPMSK |= 1UL << ((uint8_t)p_ep->num & USB_OTG_EP_ADDR_MSK);
        }
      }
      else
      {
        if ((USB_OTG_DEVICE(instance)->DSTS & (1U << 8)) == 0U)
        {
          USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= USB_OTG_DIEPCTL_SODDFRM;
        }
        else
        {
          USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= USB_OTG_DIEPCTL_SD0PID_SEVNFRM;
        }

        (void)USB_OTG_WritePacket(instance, p_ep->p_xfer_buffer, (uint8_t)p_ep->num, (uint16_t)p_ep->xfer_length);
      }
    }
  }
  else /* OUT endpoint */
  {
    /* Program the transfer size and packet count as follows:
    * pktcnt = N
    * xfersize = N * maxpacket
    */
    USB_OTG_OUT_EP(instance, p_ep->num)->DOEPTSIZ &= ~(USB_OTG_DOEPTSIZ_XFRSIZ);
    USB_OTG_OUT_EP(instance, p_ep->num)->DOEPTSIZ &= ~(USB_OTG_DOEPTSIZ_PKTCNT);

    if (p_ep->num == USB_CORE_ENDPOINT_0)
    {
      if (p_ep->xfer_length > 0U)
      {
        p_ep->xfer_length = p_ep->max_packet;
      }

      /* Store transfer size, for EP0 this is equal to endpoint max packet size */
      p_ep->xfer_size = p_ep->max_packet;

      USB_OTG_OUT_EP(instance, p_ep->num)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_XFRSIZ & p_ep->xfer_size);
      USB_OTG_OUT_EP(instance, p_ep->num)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (1U << 19));
    }
    else
    {
      if (p_ep->xfer_length == 0U)
      {
        USB_OTG_OUT_EP(instance, p_ep->num)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_XFRSIZ & p_ep->max_packet);
        USB_OTG_OUT_EP(instance, p_ep->num)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (1U << 19));
      }
      else
      {
        packet_count = (uint16_t)((p_ep->xfer_length + p_ep->max_packet - 1U) / p_ep->max_packet);
        p_ep->xfer_size = p_ep->max_packet * packet_count;

        USB_OTG_OUT_EP(instance, p_ep->num)->DOEPTSIZ |= USB_OTG_DOEPTSIZ_PKTCNT & ((uint32_t)packet_count << 19);
        USB_OTG_OUT_EP(instance, p_ep->num)->DOEPTSIZ |= USB_OTG_DOEPTSIZ_XFRSIZ & p_ep->xfer_size;
      }
    }

    if ((p_usb->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) == USB_OTG_GAHBCFG_DMAEN)
    {
      p_ep->dma_addr = (uint32_t)p_ep->p_xfer_buffer;

      if ((uint32_t)p_ep->dma_addr != 0U)
      {
        USB_OTG_OUT_EP(instance, p_ep->num)->DOEPDMA = (uint32_t)(p_ep->dma_addr);
      }
    }

    if (p_ep->type == USB_CORE_EP_TYPE_ISOC)
    {
      if ((USB_OTG_DEVICE(instance)->DSTS & (1U << 8)) == 0U)
      {
        USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL |= USB_OTG_DOEPCTL_SODDFRM;
      }
      else
      {
        USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL |= USB_OTG_DOEPCTL_SD0PID_SEVNFRM;
      }
    }

    /* EP enable */
    USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);
  }

  return USB_CORE_OK;
}


/**
   * @brief  Stop transfer on an EP
   * @param  instance usb device instance
   * @param  p_ep pointer to endpoint structure
   * @retval HAL OTG Core status
   */
usb_core_status_t USB_OTG_StopEndpointXfer(uint32_t instance, const usb_core_ep_t *p_ep)
{
  __IO uint32_t count = 0U;
  usb_core_status_t ret = USB_CORE_OK;

  /* IN endpoint */
  if (p_ep->dir == USB_CORE_EP_IN_DIR)
  {
    /* EP enable, IN data in FIFO */
    if (((USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL) & USB_OTG_DIEPCTL_EPENA) == USB_OTG_DIEPCTL_EPENA)
    {
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= (USB_OTG_DIEPCTL_SNAK);
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= (USB_OTG_DIEPCTL_EPDIS);

      do
      {
        count++;

        if (count > 10000U)
        {
          ret = USB_CORE_ERROR;
          break;
        }
      } while (((USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL) & USB_OTG_DIEPCTL_EPENA) ==  USB_OTG_DIEPCTL_EPENA);
    }
  }
  else /* OUT endpoint */
  {
    if (((USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL) & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA)
    {
      USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL |= (USB_OTG_DOEPCTL_SNAK);
      USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL |= (USB_OTG_DOEPCTL_EPDIS);

      do
      {
        count++;

        if (count > 10000U)
        {
          ret = USB_CORE_ERROR;
          break;
        }
      } while (((USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL) & USB_OTG_DOEPCTL_EPENA) ==  USB_OTG_DOEPCTL_EPENA);
    }
  }

  return ret;
}

/**
  * @brief  Set a stall condition over an EP
  * @param  instance  Selected device
  * @param  p_ep pointer to endpoint structure
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_SetEndpointStall(uint32_t instance, const usb_core_ep_t *p_ep)
{
  if (p_ep->dir == USB_CORE_EP_IN_DIR)
  {
    if (((USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL & USB_OTG_DIEPCTL_EPENA) == 0U)
        && (p_ep->num != USB_CORE_ENDPOINT_0))
    {
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL &= ~(USB_OTG_DIEPCTL_EPDIS);
    }
    USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= USB_OTG_DIEPCTL_STALL;
  }
  else
  {
    if (((USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == 0U)
        && (p_ep->num != USB_CORE_ENDPOINT_0))
    {
      USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL &= ~(USB_OTG_DOEPCTL_EPDIS);
    }
    USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL |= USB_OTG_DOEPCTL_STALL;
  }

  return USB_CORE_OK;
}

/**
  * @brief  Clear a stall condition over an EP
  * @param  instance  Selected device
  * @param  p_ep pointer to endpoint structure
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_ClearEndpointStall(uint32_t instance, const usb_core_ep_t *p_ep)
{
  if (p_ep->dir == USB_CORE_EP_IN_DIR)
  {
    USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL &= ~USB_OTG_DIEPCTL_STALL;
    if ((p_ep->type == USB_CORE_EP_TYPE_INTR) || (p_ep->type == USB_CORE_EP_TYPE_BULK))
    {
      USB_OTG_IN_EP(instance, p_ep->num)->DIEPCTL |= USB_OTG_DIEPCTL_SD0PID_SEVNFRM; /* DATA0 */
    }
  }
  else
  {
    USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL &= ~USB_OTG_DOEPCTL_STALL;
    if ((p_ep->type == USB_CORE_EP_TYPE_INTR) || (p_ep->type == USB_CORE_EP_TYPE_BULK))
    {
      USB_OTG_OUT_EP(instance, p_ep->num)->DOEPCTL |= USB_OTG_DOEPCTL_SD0PID_SEVNFRM; /* DATA0 */
    }
  }
  return USB_CORE_OK;
}

/**
  * @brief  Start the USB device
  * @param  instance selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_StartDevice(uint32_t instance)
{
  (void)USB_OTG_EnableGlobalInterrupt(instance);
  (void)USB_OTG_ConnectDevice(instance);

  return USB_CORE_OK;
}

/**
  * @brief  Stop the usb device mode
  * @param  instance  Selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_StopDevice(uint32_t instance)
{
  usb_core_status_t ret;
  uint32_t ep_idx;

  /* Clear Pending interrupt */
  for (ep_idx = 0U; ep_idx < 15U; ep_idx++)
  {
    USB_OTG_IN_EP(instance, ep_idx)->DIEPINT = 0xFB7FU;
    USB_OTG_OUT_EP(instance, ep_idx)->DOEPINT = 0xFB7FU;
  }

  /* Clear interrupt masks */
  USB_OTG_DEVICE(instance)->DIEPMSK  = 0U;
  USB_OTG_DEVICE(instance)->DOEPMSK  = 0U;
  USB_OTG_DEVICE(instance)->DAINTMSK = 0U;


  /* Flush the RX FIFO */
  if (USB_OTG_FlushRxFifo(instance) != USB_CORE_OK)
  {
    ret = USB_CORE_ERROR;
  }
  /* Flush the TX FIFO */
  if (USB_OTG_FlushTxFifo(instance, 0x10U) != USB_CORE_OK)
  {
    ret = USB_CORE_ERROR;
  }

  return ret;
}

/**
  * @brief  Set USB device Address
  * @param  instance  Selected device
  * @param  address  new device address to be assigned
  *          This parameter can be a value from 0 to 255
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_SetDeviceAddress(uint32_t instance, uint8_t address)
{
  USB_OTG_DEVICE(instance)->DCFG &= ~(USB_OTG_DCFG_DAD);
  USB_OTG_DEVICE(instance)->DCFG |= ((uint32_t)address << 4) & USB_OTG_DCFG_DAD;

  return USB_CORE_OK;
}

/**
  * @brief  Connect the USB device by enabling Rpu
  * @param  instance  Selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_ConnectDevice(uint32_t instance)
{
#if defined (STM32U575xx) || defined (STM32U585xx)
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);

  /* Enable USB Transceiver */
  p_usb->GCCFG |= USB_OTG_GCCFG_PWRDWN;
#endif /* defined (STM32U575xx) || defined (STM32U585xx) */

  /* In case phy is stopped, ensure to ungate and restore the phy CLK */
  USB_OTG_PCGCCTL(instance) &= ~(USB_OTG_PCGCCTL_STOPCLK | USB_OTG_PCGCCTL_GATECLK);

  USB_OTG_DEVICE(instance)->DCTL &= ~USB_OTG_DCTL_SDIS;

  return USB_CORE_OK;
}

/**
  * @brief  Disconnect the USB device by disabling Rpu
  * @param  instance  Selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_DisconnectDevice(uint32_t instance)
{
  /* In case phy is stopped, ensure to ungate and restore the phy CLK */
  USB_OTG_PCGCCTL(instance) &= ~(USB_OTG_PCGCCTL_STOPCLK | USB_OTG_PCGCCTL_GATECLK);

  USB_OTG_DEVICE(instance)->DCTL |= USB_OTG_DCTL_SDIS;

#if defined (STM32U575xx) || defined (STM32U585xx)
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);

  /* Disable USB Transceiver */
  p_usb->GCCFG &= ~(USB_OTG_GCCFG_PWRDWN);
#endif /* defined (STM32U575xx) || defined (STM32U585xx) */

  return USB_CORE_OK;
}

/**
  * @brief  Activate EP0 for Setup transactions
  * @param  instance  Selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_ActivateSetup(uint32_t instance)
{
  /* Set the MPS of the IN EP0 to 64 bytes */
  USB_OTG_IN_EP(instance, 0U)->DIEPCTL &= ~USB_OTG_DIEPCTL_MPSIZ;

  USB_OTG_DEVICE(instance)->DCTL |= USB_OTG_DCTL_CGINAK;

  return USB_CORE_OK;
}

/**
  * @brief  Prepare the EP0 to start the first control setup
  * @param  instance  Selected device
  * @param  p_setup  pointer to setup packet
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_StartOutEP0(uint32_t instance, const uint8_t *p_setup)
{
  const usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  uint32_t g_snps_id = *(__IO const uint32_t *)(&p_usb->GSNPSID);

  if (g_snps_id > USB_OTG_CORE_ID_300A)
  {
    if ((USB_OTG_OUT_EP(instance, 0U)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA)
    {
      return USB_CORE_OK;
    }
  }

  USB_OTG_OUT_EP(instance, 0U)->DOEPTSIZ = 0U;
  USB_OTG_OUT_EP(instance, 0U)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (1U << 19));
  USB_OTG_OUT_EP(instance, 0U)->DOEPTSIZ |= (3U * 8U);
  USB_OTG_OUT_EP(instance, 0U)->DOEPTSIZ |=  USB_OTG_DOEPTSIZ_STUPCNT;

  if ((p_usb->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) == USB_OTG_GAHBCFG_DMAEN)
  {
    USB_OTG_OUT_EP(instance, 0U)->DOEPDMA = (uint32_t)p_setup;
    /* EP enable */
    USB_OTG_OUT_EP(instance, 0U)->DOEPCTL |= USB_OTG_DOEPCTL_EPENA | USB_OTG_DOEPCTL_USBAEP;
  }

  return USB_CORE_OK;
}

/**
  * @brief  Activate LPM feature
  * @param  instance selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_LPM_Activate(uint32_t instance)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);

  p_usb->GINTMSK |= USB_OTG_GINTMSK_LPMINTM;
  p_usb->GLPMCFG |= (USB_OTG_GLPMCFG_LPMEN | USB_OTG_GLPMCFG_LPMACK | USB_OTG_GLPMCFG_ENBESL);

  return USB_CORE_OK;
}

/**
  * @brief  DeActivate LPM feature
  * @param  instance selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_LPM_DeActivate(uint32_t instance)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);

  p_usb->GINTMSK &= ~USB_OTG_GINTMSK_LPMINTM;
  p_usb->GLPMCFG &= ~(USB_OTG_GLPMCFG_LPMEN | USB_OTG_GLPMCFG_LPMACK | USB_OTG_GLPMCFG_ENBESL);

  return USB_CORE_OK;
}


/**
  * @}
  */


/** @defgroup USB_OTG_Core_Host_Exported_Functions USB Core Host Exported Functions
  * @{
  */


/**
  * @brief  Initialize the USB OTG HCD Driver
  * @param  p_driver pointer to USB HCD driver structure
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_HCD_InitDriver(usb_core_hcd_driver_t *p_driver)
{
  p_driver->core_init = USB_OTG_InitCore;
  p_driver->core_deinit = USB_OTG_DeInitCore;
  p_driver->core_set_mode = USB_OTG_SetCurrentMode;
  p_driver->core_get_mode = USB_OTG_GetCurrentMode;
  p_driver->core_enable_interrupts = USB_OTG_EnableGlobalInterrupt;
  p_driver->core_disable_interrupts = USB_OTG_DisableGlobalInterrupt;
  p_driver->core_get_dma_status = USB_OTG_GetDmaStatus;
  p_driver->host_init = USB_OTG_InitHost;
  p_driver->host_start = USB_OTG_StartHost;
  p_driver->host_stop = USB_OTG_StopHost;
  p_driver->host_channel_init = USB_OTG_InitChannel;
  p_driver->host_channel_start = USB_OTG_StartChannelXfer;
  p_driver->host_channel_halt = USB_OTG_HaltChannel;
  p_driver->host_port_power = USB_OTG_PortPower;
  p_driver->host_port_reset = USB_OTG_PortReset;
  p_driver->host_port_suspend = USB_OTG_PortSuspend;
  p_driver->host_port_resume = USB_OTG_PortResume;
  p_driver->host_get_port_speed = USB_OTG_GetHostPortSpeed;
  p_driver->host_get_current_frame = USB_OTG_GetCurrentFrame;

  return USB_CORE_OK;
}

/**
  * @brief  Initializes the USB OTG controller registers
  *         for Host mode
  * @param  instance  Selected device
  * @param  p_core_config USB Instance configuration parameters
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_InitHost(uint32_t instance, const usb_core_config_params_t *p_core_config)
{
  usb_core_status_t ret = USB_CORE_OK;
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  uint32_t ch_idx;

#if defined (USB_OTG_HS)
  /* Enable USB PHY pulldown resistors */
  p_usb->GCCFG |= USB_OTG_GCCFG_PULLDOWNEN;

  /* Disable VBUS override */
  p_usb->GCCFG &= ~(USB_OTG_GCCFG_VBVALOVAL | USB_OTG_GCCFG_VBVALEXTOEN);

#else

  /* Disable Battery chargin detector */
  p_usb->GCCFG &= ~(USB_OTG_GCCFG_BCDEN);
#endif /* defined (USB_OTG_HS) */

  /* Disable Battery chargin detector */
  p_usb->GCCFG &= ~(USB_OTG_GCCFG_PDEN);
  p_usb->GCCFG &= ~(USB_OTG_GCCFG_SDEN);

  /* Disable VBUS sensing */
  p_usb->GCCFG &= ~(USB_OTG_GCCFG_VBDEN);

  /* Restart the Phy Clock */
  USB_OTG_PCGCCTL(instance) = 0U;

  if ((p_usb->GUSBCFG & USB_OTG_GUSBCFG_PHYSEL) == 0U)
  {
    if (p_core_config->core_speed == USB_CORE_SPEED_HS_IN_FS)
    {
      /* Force Device Enumeration to FS/LS mode only */
      USB_OTG_HOST(instance)->HCFG |= USB_OTG_HCFG_FSLSS;
    }
    else
    {
      /* Set default Max speed support */
      USB_OTG_HOST(instance)->HCFG &= ~(USB_OTG_HCFG_FSLSS);
    }
  }
  else
  {
    /* Set default Max speed support */
    USB_OTG_HOST(instance)->HCFG &= ~(USB_OTG_HCFG_FSLSS);
  }

  /* Flush all TX FIFOs */
  if (USB_OTG_FlushTxFifo(instance, 0x10U) != USB_CORE_OK)
  {
    ret = USB_CORE_ERROR;
  }

  /* Flush the RX FIFO */
  if (USB_OTG_FlushRxFifo(instance) != USB_CORE_OK)
  {
    ret = USB_CORE_ERROR;
  }

  /* Clear all pending HC Interrupts */
  for (ch_idx = 0U; ch_idx < p_core_config->channels_nbr; ch_idx++)
  {
    USB_OTG_CHANNEL(instance, ch_idx)->HCINT = USB_OTG_CLEAR_INTERRUPT_MASK;
    USB_OTG_CHANNEL(instance, ch_idx)->HCINTMSK = 0U;
  }

  /* Disable all interrupts. */
  p_usb->GINTMSK = 0U;

  /* Clear any pending interrupts */
  p_usb->GINTSTS = USB_OTG_CLEAR_INTERRUPT_MASK;
#if defined (USB_OTG_HS)
  if (instance == (uint32_t)USB_OTG_HS)
  {
    /* Set Rx FIFO size */
    p_usb->GRXFSIZ  = 0x200U;
    p_usb->DIEPTXF0_HNPTXFSIZ = (uint32_t)(((0x100U << 16) & USB_OTG_NPTXFD) | 0x200U);
    p_usb->HPTXFSIZ = (uint32_t)(((0xE0U << 16) & USB_OTG_HPTXFSIZ_PTXFD) | 0x300U);
  }
  else
#endif /* defined (USB_OTG_HS) */
  {
    /* Set Rx FIFO size */
    p_usb->GRXFSIZ  = 0x80U;
    p_usb->DIEPTXF0_HNPTXFSIZ = (uint32_t)(((0x60U << 16) & USB_OTG_NPTXFD) | 0x80U);
    p_usb->HPTXFSIZ = (uint32_t)(((0x40U << 16)& USB_OTG_HPTXFSIZ_PTXFD) | 0xE0U);
  }

  /* Enable the common interrupts */
  if ((p_usb->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) == 0U)
  {
    p_usb->GINTMSK |= USB_OTG_GINTMSK_RXFLVLM;
  }

  /* Enable interrupts matching to the Host mode ONLY */
  p_usb->GINTMSK |= (USB_OTG_GINTMSK_PRTIM            | USB_OTG_GINTMSK_HCIM | \
                     USB_OTG_GINTMSK_SOFM             | USB_OTG_GINTSTS_DISCINT | \
                     USB_OTG_GINTMSK_PXFRM_IISOOXFRM  | USB_OTG_GINTMSK_WUIM);

  return ret;
}

/**
  * @brief  Initializes the FSLSPClkSel field of the
  *         HCFG register on the PHY type and set the right frame interval
  * @param  instance  Selected device
  * @param  frequency  clock frequency
  *          This parameter can be one of these values:
  *           USB_OTG_HCFG_48_MHZ : Full Speed 48 MHz Clock
  *           USB_OTG_HCFG_6_MHZ : Low Speed 6 MHz Clock
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_InitFSLSPClkSel(uint32_t instance, uint8_t frequency)
{
  USB_OTG_HOST(instance)->HCFG &= ~(USB_OTG_HCFG_FSLSPCS);
  USB_OTG_HOST(instance)->HCFG |= (uint32_t)frequency & USB_OTG_HCFG_FSLSPCS;

  if (frequency == (uint8_t)USB_OTG_HCFG_48_MHZ)
  {
    USB_OTG_HOST(instance)->HFIR = (__IO uint32_t)USB_OTG_HFIR_48_MHZ;
  }
  else if (frequency == (uint8_t)USB_OTG_HCFG_6_MHZ)
  {
    USB_OTG_HOST(instance)->HFIR = (__IO uint32_t)USB_OTG_HFIR_6_MHZ;
  }
  else
  {
    return USB_CORE_ERROR;
  }

  return USB_CORE_OK;
}

/**
  * @brief  Initialize a host channel
  * @param  instance  Selected device
  * @param  p_ch pointer to host Channel configuration
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_InitChannel(uint32_t instance, usb_core_ch_t *p_ch)
{
  usb_core_status_t ret = USB_CORE_OK;
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  uint32_t hcchar_mps = p_ch->max_packet;
  uint32_t hcchar_ep_dir;
  uint32_t hcchar_low_speed;
  usb_core_port_speed_t host_port_speed;

  /* Clear old interrupt conditions for this host channel. */
  USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCINT = USB_OTG_CLEAR_INTERRUPT_MASK;

  /* Enable channel interrupts required for this transfer. */
  switch (p_ch->ep_type)
  {
    case USB_CORE_EP_TYPE_CTRL:
    case USB_CORE_EP_TYPE_BULK:
      USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCINTMSK = USB_OTG_HCINTMSK_XFRCM  |
                                                          USB_OTG_HCINTMSK_STALLM |
                                                          USB_OTG_HCINTMSK_TXERRM |
                                                          USB_OTG_HCINTMSK_DTERRM |
                                                          USB_OTG_HCINTMSK_AHBERR |
                                                          USB_OTG_HCINTMSK_NAKM;

      if (p_ch->ch_dir == USB_CORE_CH_IN_DIR)
      {
        USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCINTMSK |= USB_OTG_HCINTMSK_BBERRM;
      }
      else
      {
#if defined (USB_OTG_HS)
        if (instance == (uint32_t)USB_OTG_HS)
        {
          USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCINTMSK |= USB_OTG_HCINTMSK_NYET |
                                                               USB_OTG_HCINTMSK_ACKM;
        }
#endif /* defined (USB_OTG_HS) */
      }
      break;

    case USB_CORE_EP_TYPE_INTR:
      USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCINTMSK = USB_OTG_HCINTMSK_XFRCM  |
                                                          USB_OTG_HCINTMSK_STALLM |
                                                          USB_OTG_HCINTMSK_TXERRM |
                                                          USB_OTG_HCINTMSK_DTERRM |
                                                          USB_OTG_HCINTMSK_NAKM   |
                                                          USB_OTG_HCINTMSK_AHBERR |
                                                          USB_OTG_HCINTMSK_FRMORM;

      if (p_ch->ch_dir == USB_CORE_CH_IN_DIR)
      {
        USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCINTMSK |= USB_OTG_HCINTMSK_BBERRM;
      }

      break;

    case USB_CORE_EP_TYPE_ISOC:
      USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCINTMSK = USB_OTG_HCINTMSK_XFRCM  |
                                                          USB_OTG_HCINTMSK_ACKM   |
                                                          USB_OTG_HCINTMSK_AHBERR |
                                                          USB_OTG_HCINTMSK_FRMORM;

      if (p_ch->ch_dir == USB_CORE_CH_IN_DIR)
      {
        USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCINTMSK |= (USB_OTG_HCINTMSK_TXERRM | USB_OTG_HCINTMSK_BBERRM);
      }
      break;

    default:
      ret = USB_CORE_ERROR;
      break;
  }

  /* Clear Hub Start Split transaction */
  USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCSPLT = 0U;

  /* Enable host channel Halt interrupt */
  USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCINTMSK |= USB_OTG_HCINTMSK_CHHM;

  /* Enable the top level host channel interrupt. */
  USB_OTG_HOST(instance)->HAINTMSK |= 1UL << ((uint32_t)p_ch->ch_num & 0xFU);

  /* Make sure host channel interrupts are enabled. */
  p_usb->GINTMSK |= USB_OTG_GINTMSK_HCIM;

  /* Program the HCCHAR register */
  if (p_ch->ch_dir == USB_CORE_CH_IN_DIR)
  {
    hcchar_ep_dir = (0x1U << 15) & USB_OTG_HCCHAR_EPDIR;
  }
  else
  {
    hcchar_ep_dir = 0U;
  }

  host_port_speed = USB_OTG_GetHostPortSpeed(instance);

  /* LS device plugged to HUB */
  if ((p_ch->speed == USB_CORE_DEVICE_SPEED_LS) && (host_port_speed != USB_CORE_PORT_SPEED_LS))
  {
    hcchar_low_speed = (0x1U << 17) & USB_OTG_HCCHAR_LSDEV;
  }
  else
  {
    hcchar_low_speed = 0U;
  }

  if (p_ch->ep_type == USB_CORE_EP_TYPE_ISOC)
  {
    /* FS device plugged to HS HUB */
    if ((p_ch->speed == USB_CORE_DEVICE_SPEED_FS) && (host_port_speed == USB_CORE_PORT_SPEED_HS))
    {
      if (hcchar_mps > USB_OTG_ISO_SPLT_MPS)
      {
        /* ISO Max Packet Size for Split mode */
        hcchar_mps = USB_OTG_ISO_SPLT_MPS;
      }
    }
  }

  p_ch->max_packet = (uint16_t)hcchar_mps;

  USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR = (((uint32_t)p_ch->dev_addr << 22) & USB_OTG_HCCHAR_DAD) |
                                                    (((uint32_t)p_ch->ep_num << 11) & USB_OTG_HCCHAR_EPNUM) |
                                                    (((uint32_t)p_ch->ep_type << 18) & USB_OTG_HCCHAR_EPTYP) |
                                                    (hcchar_mps & USB_OTG_HCCHAR_MPSIZ) |
                                                    USB_OTG_HCCHAR_MC_0 | hcchar_ep_dir | hcchar_low_speed;

  if ((p_ch->ep_type == USB_CORE_EP_TYPE_INTR) || (p_ch->ep_type == USB_CORE_EP_TYPE_ISOC))
  {
    USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR |= USB_OTG_HCCHAR_ODDFRM;
  }

  return ret;
}

/**
  * @brief  Start a transfer over a host channel
  * @param  instance  Selected device
  * @param  p_ch pointer to host Channel configuration
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_StartChannelXfer(uint32_t instance, usb_core_ch_t *p_ch)
{
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  uint32_t dma_enable = (p_usb->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) >> 0x5U;
  uint16_t max_hc_pkt_count = USB_OTG_CH_MAX_PKT_CNT;
  __IO uint32_t hcchar_reg;
  uint8_t  is_odd_frame;
  uint16_t len_words;
  uint16_t num_packets;

  /* Reset channel transfer size */
  p_ch->xfer_size = 0U;

#if defined (USB_OTG_HS)
  if (instance == (uint32_t)USB_OTG_HS)
  {
    /* In DMA mode host Core automatically issues ping in case of NYET/NAK */
    if (dma_enable == 1U)
    {
      if (((p_ch->ep_type == USB_CORE_EP_TYPE_CTRL)
           || (p_ch->ep_type == USB_CORE_EP_TYPE_BULK)) && (p_ch->do_ssplit == 0U))
      {
        USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCINTMSK &= ~(USB_OTG_HCINTMSK_NYET |
                                                               USB_OTG_HCINTMSK_ACKM |
                                                               USB_OTG_HCINTMSK_NAKM);
      }
    }
    else
    {
      if ((p_ch->speed == USB_CORE_DEVICE_SPEED_HS) && (p_ch->do_ping == 1U))
      {
        (void)USB_OTG_DoPing(instance, p_ch->ch_num);
        return USB_CORE_OK;
      }
    }
  }
#endif /* defined (USB_OTG_HS) */

  if (p_ch->do_ssplit == 1U)
  {
    /* Set number of packet to 1 for Split transaction */
    num_packets = 1U;

    if (p_ch->ch_dir == USB_CORE_CH_IN_DIR)
    {
      p_ch->xfer_size = (uint32_t)num_packets * p_ch->max_packet;
    }
    else
    {
      if (p_ch->ep_type == USB_CORE_EP_TYPE_ISOC)
      {
        if (p_ch->xfer_length > USB_OTG_ISO_SPLT_MPS)
        {
          /* Isochrone Max Packet Size for Split mode */
          p_ch->xfer_size = p_ch->max_packet;
          p_ch->xfer_length = p_ch->xfer_size;

          if ((p_ch->iso_split_xact_pos == (uint8_t)USB_OTG_HCSPLT_BEGIN)
              || (p_ch->iso_split_xact_pos == (uint8_t)USB_OTG_HCSPLT_MIDDLE))
          {
            p_ch->iso_split_xact_pos = (uint8_t)USB_OTG_HCSPLT_MIDDLE;
          }
          else
          {
            p_ch->iso_split_xact_pos = (uint8_t)USB_OTG_HCSPLT_BEGIN;
          }
        }
        else
        {
          p_ch->xfer_size = p_ch->xfer_length;

          if ((p_ch->iso_split_xact_pos != (uint8_t)USB_OTG_HCSPLT_BEGIN)
              && (p_ch->iso_split_xact_pos != (uint8_t)USB_OTG_HCSPLT_MIDDLE))
          {
            p_ch->iso_split_xact_pos = (uint8_t)USB_OTG_HCSPLT_FULL;
          }
          else
          {
            p_ch->iso_split_xact_pos = (uint8_t)USB_OTG_HCSPLT_END;
          }
        }
      }
      else
      {
        if ((dma_enable == 1U) && (p_ch->xfer_length > p_ch->max_packet))
        {
          p_ch->xfer_size = (uint32_t)num_packets * p_ch->max_packet;
        }
        else
        {
          p_ch->xfer_size = p_ch->xfer_length;
        }
      }
    }
  }
  else
  {
    /* Compute the expected number of packets associated to the transfer */
    if (p_ch->xfer_length > 0U)
    {
      num_packets = (uint16_t)((p_ch->xfer_length + p_ch->max_packet - 1U) / p_ch->max_packet);

      if (num_packets > max_hc_pkt_count)
      {
        num_packets = max_hc_pkt_count;
        p_ch->xfer_size = (uint32_t)num_packets * p_ch->max_packet;
      }
      else
      {
        /*
        * For IN channel HCTSIZ.xfer_size is expected to be an integer multiple of
        * max_packet size.
        */
        if (p_ch->ch_dir == USB_CORE_CH_IN_DIR)
        {
          p_ch->xfer_size = (uint32_t)num_packets * p_ch->max_packet;
        }
        else
        {
          p_ch->xfer_size = p_ch->xfer_length;
        }
      }
    }
    else
    {
      num_packets = 1U;
      /*
      * For IN channel HCTSIZ.xfer_size is expected to be an integer multiple of
      * max_packet size.
      */
      if (p_ch->ch_dir == USB_CORE_CH_IN_DIR)
      {
        p_ch->xfer_size = (uint32_t)num_packets * p_ch->max_packet;
      }
      else
      {
        p_ch->xfer_size = p_ch->xfer_length;
      }
    }
  }

  /* Initialize the HCTSIZn register */
  USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCTSIZ = (p_ch->xfer_size & USB_OTG_HCTSIZ_XFRSIZ) |
                                                    (((uint32_t)num_packets << 19) & USB_OTG_HCTSIZ_PKTCNT) |
                                                    (((uint32_t)p_ch->data_pid << 29) & USB_OTG_HCTSIZ_DPID);

  if (dma_enable == 1U)
  {
    /* p_xfer_buffer MUST be 32-bits aligned */
    USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCDMA = (uint32_t)p_ch->p_xfer_buffer;
  }

  is_odd_frame = (((uint32_t)USB_OTG_HOST(instance)->HFNUM & 0x01U) != 0U) ? 0U : 1U;
  USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR &= ~USB_OTG_HCCHAR_ODDFRM;
  USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR |= (uint32_t)is_odd_frame << 29;

  if (p_ch->do_ssplit == 1U)
  {
    /* Set Hub start Split transaction */
    USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCSPLT = ((uint32_t)p_ch->hub_addr << USB_OTG_HCSPLT_HUBADDR_Pos) |
                                                      (uint32_t)p_ch->hub_port_nbr | USB_OTG_HCSPLT_SPLITEN;

    /* Unmask ack & nyet for IN/OUT transactions */
    USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCINTMSK |= (USB_OTG_HCINTMSK_ACKM |
                                                          USB_OTG_HCINTMSK_NYET);

    if ((p_ch->do_csplit == 1U) && (p_ch->ch_dir == USB_CORE_CH_OUT_DIR))
    {
      USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCSPLT |= USB_OTG_HCSPLT_COMPLSPLT;
      USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCINTMSK |= USB_OTG_HCINTMSK_NYET;
    }

    if (((p_ch->ep_type == USB_CORE_EP_TYPE_ISOC) || (p_ch->ep_type == USB_CORE_EP_TYPE_INTR))
        && (p_ch->do_csplit == 1U) && (p_ch->ch_dir == USB_CORE_CH_IN_DIR))
    {
      USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCSPLT |= USB_OTG_HCSPLT_COMPLSPLT;
    }

    /* Position management for iso out transaction on split mode */
    if ((p_ch->ep_type == USB_CORE_EP_TYPE_ISOC) && (p_ch->ch_dir == USB_CORE_CH_OUT_DIR))
    {
      if (p_ch->iso_split_xact_pos == USB_OTG_HCSPLT_BEGIN)
      {
        USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCSPLT |= USB_OTG_HCSPLT_XACTPOS_1;
      }
      else if (p_ch->iso_split_xact_pos == USB_OTG_HCSPLT_MIDDLE)
      {
        USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCSPLT |= USB_OTG_HCSPLT_XACTPOS_Pos;
      }
      else if (p_ch->iso_split_xact_pos == USB_OTG_HCSPLT_END)
      {
        USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCSPLT |= USB_OTG_HCSPLT_XACTPOS_0;
      }
      else if (p_ch->iso_split_xact_pos == USB_OTG_HCSPLT_FULL)
      {
        USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCSPLT |= USB_OTG_HCSPLT_XACTPOS;
      }
      else
      {
        /* .. */
      }
    }
  }
  else
  {
    /* Clear Hub Start Split transaction */
    USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCSPLT = 0U;
  }

  /* Set host channel enable */
  hcchar_reg = USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR;
  hcchar_reg &= ~USB_OTG_HCCHAR_CHDIS;

  /* Make sure to set the correct ep direction */
  if (p_ch->ch_dir == USB_CORE_CH_IN_DIR)
  {
    hcchar_reg |= USB_OTG_HCCHAR_EPDIR;
  }
  else
  {
    hcchar_reg &= ~USB_OTG_HCCHAR_EPDIR;
  }
  hcchar_reg |= USB_OTG_HCCHAR_CHENA;
  USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR = hcchar_reg;

  if (dma_enable == 1U) /* dma mode */
  {
    return USB_CORE_OK;
  }

  if ((p_ch->ch_dir == USB_CORE_CH_OUT_DIR) && (p_ch->xfer_length > 0U) && (p_ch->do_csplit == 0U))
  {
    switch (p_ch->ep_type)
    {
      /* Non periodic transfer */
      case USB_CORE_EP_TYPE_CTRL:
      case USB_CORE_EP_TYPE_BULK:

        len_words = (uint16_t)((p_ch->xfer_length + 3U) / 4U);

        /* Check if there is enough space in FIFO space */
        if (len_words > (p_usb->HNPTXSTS & 0xFFFFU))
        {
          /* Need to process data in nptxfempty interrupt */
          p_usb->GINTMSK |= USB_OTG_GINTMSK_NPTXFEM;
        }
        break;

      /* Periodic transfer */
      case USB_CORE_EP_TYPE_INTR:
      case USB_CORE_EP_TYPE_ISOC:

        len_words = (uint16_t)((p_ch->xfer_length + 3U) / 4U);
        /* Check if there is enough space in FIFO space */
        if (len_words > (USB_OTG_HOST(instance)->HPTXSTS & 0xFFFFU)) /* split the transfer */
        {
          /* Need to process data in ptxfempty interrupt */
          p_usb->GINTMSK |= USB_OTG_GINTMSK_PTXFEM;
        }
        break;

      default:
        return USB_CORE_ERROR;
        break;
    }

    /* Write packet into the Tx FIFO. */
    (void)USB_OTG_WritePacket(instance, p_ch->p_xfer_buffer, (uint8_t)p_ch->ch_num, (uint16_t)p_ch->xfer_length);
  }

  return USB_CORE_OK;
}

/**
  * @brief  Halt a host channel
  * @param  instance  Selected device
  * @param  p_ch pointer to host Channel configuration
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_HaltChannel(uint32_t instance, const usb_core_ch_t *p_ch)
{
  const usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  uint32_t hcchar_ep_type = (USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR & USB_OTG_HCCHAR_EPTYP) >> 18;
  usb_core_ep_type_t ch_ep_type = (usb_core_ep_type_t)hcchar_ep_type;
  uint32_t channel_enable = (USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR & USB_OTG_HCCHAR_CHENA) >> 31;
  uint32_t split_enable = (USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCSPLT & USB_OTG_HCSPLT_SPLITEN) >> 31;
  uint32_t dma_enable = (p_usb->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) >> 0x5U;
  volatile uint32_t count = 0U;

  /* In buffer DMA, Channel disable must not be programmed for non-split periodic channels.
     At the end of the next uframe/frame (in the worst case), the core generates a channel halted
     and disables the channel automatically. */

  if (((channel_enable == 0U) || (((ch_ep_type == USB_CORE_EP_TYPE_ISOC) || (ch_ep_type == USB_CORE_EP_TYPE_INTR))))
      && ((dma_enable == 1U) && (split_enable == 0U)))
  {
    return USB_CORE_OK;
  }

  /* Check for space in the request queue to issue the halt. */
  if ((ch_ep_type == USB_CORE_EP_TYPE_CTRL) || (ch_ep_type == USB_CORE_EP_TYPE_BULK))
  {
    USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR |= USB_OTG_HCCHAR_CHDIS;

    if (dma_enable == 0U)
    {
      if ((p_usb->HNPTXSTS & (0xFFU << 16)) == 0U)
      {
        USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR &= ~USB_OTG_HCCHAR_CHENA;
        USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR |= USB_OTG_HCCHAR_CHENA;
        do
        {
          count++;

          if (count > 1000U)
          {
            break;
          }
        } while ((USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR & USB_OTG_HCCHAR_CHENA) == USB_OTG_HCCHAR_CHENA);
      }
      else
      {
        USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR |= USB_OTG_HCCHAR_CHENA;
      }
    }
    else
    {
      USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR |= USB_OTG_HCCHAR_CHENA;
    }
  }
  else
  {
    USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR |= USB_OTG_HCCHAR_CHDIS;

    if ((USB_OTG_HOST(instance)->HPTXSTS & (0xFFU << 16)) == 0U)
    {
      USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR &= ~USB_OTG_HCCHAR_CHENA;
      USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR |= USB_OTG_HCCHAR_CHENA;
      do
      {
        count++;

        if (count > 1000U)
        {
          break;
        }
      } while ((USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR & USB_OTG_HCCHAR_CHENA) == USB_OTG_HCCHAR_CHENA);
    }
    else
    {
      USB_OTG_CHANNEL(instance, p_ch->ch_num)->HCCHAR |= USB_OTG_HCCHAR_CHENA;
    }
  }

  return USB_CORE_OK;
}

/**
  * @brief  Initiate Do Ping protocol
  * @param  instance  Selected device
  * @param  ch_num  Host Channel number
  *         This parameter can be a value from 1 to 15
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_DoPing(uint32_t instance, usb_core_channel_t ch_num)
{
  uint32_t num_packets = 1U;
  uint32_t hcchar_reg;

  USB_OTG_CHANNEL(instance, ch_num)->HCTSIZ = ((num_packets << 19) & USB_OTG_HCTSIZ_PKTCNT) | USB_OTG_HCTSIZ_DOPING;

  /* Set host channel enable */
  hcchar_reg = USB_OTG_CHANNEL(instance, ch_num)->HCCHAR;
  hcchar_reg &= ~USB_OTG_HCCHAR_CHDIS;
  hcchar_reg |= USB_OTG_HCCHAR_CHENA;
  USB_OTG_CHANNEL(instance, ch_num)->HCCHAR = hcchar_reg;

  return USB_CORE_OK;
}

/**
  * @brief  Start Host Core
  * @param  instance  Selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_StartHost(uint32_t instance)
{
  /* Enable port power */
  (void)USB_OTG_PortPower(instance, 1U);

  /* Enable global interrupt */
  (void)USB_OTG_EnableGlobalInterrupt(instance);

  return USB_CORE_OK;
}

/**
  * @brief  Stop Host Core
  * @param  instance  Selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_StopHost(uint32_t instance)
{
  usb_core_status_t ret = USB_CORE_OK;
  usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);
  __IO uint32_t count = 0U;
  uint32_t hcchar_reg;
  uint32_t ch_idx;

  (void)USB_OTG_DisableGlobalInterrupt(instance);

  /* Flush USB FIFO */
  if (USB_OTG_FlushTxFifo(instance, 0x10U) != USB_CORE_OK) /* all Tx FIFOs */
  {
    ret = USB_CORE_ERROR;
  }

  if (USB_OTG_FlushRxFifo(instance) != USB_CORE_OK)
  {
    ret = USB_CORE_ERROR;
  }

  /* Flush out any leftover queued requests. */
  for (ch_idx = 0U; ch_idx <= 15U; ch_idx++)
  {
    hcchar_reg = USB_OTG_CHANNEL(instance, ch_idx)->HCCHAR;
    hcchar_reg |=  USB_OTG_HCCHAR_CHDIS;
    hcchar_reg &= ~USB_OTG_HCCHAR_CHENA;
    hcchar_reg &= ~USB_OTG_HCCHAR_EPDIR;
    USB_OTG_CHANNEL(instance, ch_idx)->HCCHAR = hcchar_reg;
  }

  /* Halt all channels to put them into a known state. */
  for (ch_idx = 0U; ch_idx <= 15U; ch_idx++)
  {
    hcchar_reg = USB_OTG_CHANNEL(instance, ch_idx)->HCCHAR;
    hcchar_reg |= USB_OTG_HCCHAR_CHDIS;
    hcchar_reg |= USB_OTG_HCCHAR_CHENA;
    hcchar_reg &= ~USB_OTG_HCCHAR_EPDIR;
    USB_OTG_CHANNEL(instance, ch_idx)->HCCHAR = hcchar_reg;

    do
    {
      count++;

      if (count > 1000U)
      {
        break;
      }
    } while ((USB_OTG_CHANNEL(instance, ch_idx)->HCCHAR & USB_OTG_HCCHAR_CHENA) == USB_OTG_HCCHAR_CHENA);
  }

  /* Clear any pending Host interrupts */
  USB_OTG_HOST(instance)->HAINT = USB_OTG_CLEAR_INTERRUPT_MASK;
  p_usb->GINTSTS = USB_OTG_CLEAR_INTERRUPT_MASK;

  (void)USB_OTG_EnableGlobalInterrupt(instance);

  return ret;
}

/**
  * @brief  Return Host Core port speed
  * @param  instance  Selected device
  * @retval port_speed : Host port speed
  *          This parameter can be one of these values:
  *            @arg USB_CORE_PORT_SPEED_HS: High speed mode
  *            @arg USB_CORE_PORT_SPEED_FS: Full speed mode
  *            @arg USB_CORE_PORT_SPEED_LS: Low speed mode
  */
usb_core_port_speed_t USB_OTG_GetHostPortSpeed(uint32_t instance)
{
  __IO uint32_t hprt0 = 0U;
  uint32_t port_speed;

  hprt0 = USB_OTG_HPRT0(instance);

  port_speed = ((hprt0 & USB_OTG_HPRT_PSPD) >> 17);

  return (usb_core_port_speed_t)port_speed;
}

/**
  * @brief  Return Host Current Frame number
  * @param  instance  Selected device
  * @retval current frame number
  */
uint32_t USB_OTG_GetCurrentFrame(uint32_t instance)
{
  return (USB_OTG_HOST(instance)->HFNUM & USB_OTG_HFNUM_FRNUM);
}

/**
  * @brief Read all host channel interrupts status
  * @param  instance  Selected device
  * @retval host interrupt value
  */
uint32_t USB_OTG_GetChannelInterrupt(uint32_t instance)
{
  return ((USB_OTG_HOST(instance)->HAINT) & 0xFFFFU);
}

/**
  * @brief  Return USB channel interrupt status
  * @param  instance  Selected device
  * @param  ch_num Channel number
  * @retval USB Channel Interrupt status
  */
uint32_t USB_OTG_ReadChannelInterrupts(uint32_t instance, usb_core_channel_t ch_num)
{
  uint32_t hcint_reg;

  hcint_reg = USB_OTG_CHANNEL(instance, ch_num)->HCINT;
  hcint_reg &= USB_OTG_CHANNEL(instance, ch_num)->HCINTMSK;

  return hcint_reg;
}

/**
  * @brief  USB_OTG_isEnabledDma: return the HCD DMA status enabled or disabled
  * @param  instance  Selected device
  * @retval HCD DMA status enabled or disabled
  */
uint32_t USB_OTG_GetDmaStatus(uint32_t instance)
{
  const usb_otg_global_t *p_usb = USB_OTG_GET_INSTANCE(instance);

  if ((p_usb->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) == USB_OTG_GAHBCFG_DMAEN)
  {
    return (uint32_t)USB_CORE_CONFIG_ENABLED;
  }
  else
  {
    return (uint32_t)USB_CORE_CONFIG_DISABLED;
  }
}


/**
  * @brief  Reset Host Port
  * @param  instance  Selected device
  * @param  reset_status Host Port reset status
  * @retval USB_CORE_OK
  * @note (1)The application must wait at least 10 ms
  *   before clearing the reset bit.
  */
usb_core_status_t USB_OTG_PortReset(uint32_t instance, usb_core_port_reset_sts_t reset_status)
{
  __IO uint32_t hprt0 = 0U;

  hprt0 = USB_OTG_HPRT0(instance);

  hprt0 &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET |
             USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG);

  if (reset_status == USB_CORE_PORT_RESET_STS_SET)
  {
    USB_OTG_HPRT0(instance) = (USB_OTG_HPRT_PRST | hprt0);
  }
  else
  {
    USB_OTG_HPRT0(instance) = ((~USB_OTG_HPRT_PRST) & hprt0);
  }

  return USB_CORE_OK;
}

/**
  * @brief  Suspend Host Port
  * @param  instance  Selected device
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_PortSuspend(uint32_t instance)
{
  STM32_UNUSED(instance);

  return USB_CORE_OK;
}

/**
  * @brief  Resume Host Port
  * @param  instance  Selected device
  * @param  resume_status  Resume OTG Core status
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_PortResume(uint32_t instance, usb_core_port_resume_sts_t resume_status)
{
  STM32_UNUSED(instance);
  STM32_UNUSED(resume_status);

  return USB_CORE_OK;
}

/**
  * @brief  activate or de-activate Port Power
  * @param  instance  Selected device
  * @param  state  Port Power state
  *          This parameter can be one of these values:
  *           0 : Deactivate Port Power
  *           1 : Activate Port Power
  * @retval OTG Core status
  */
usb_core_status_t USB_OTG_PortPower(uint32_t instance, uint8_t state)
{
  __IO uint32_t hprt0 = 0U;

  hprt0 = USB_OTG_HPRT0(instance);

  hprt0 &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET |
             USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG);

  if (((hprt0 & USB_OTG_HPRT_PPWR) == 0U) && (state == 1U))
  {
    USB_OTG_HPRT0(instance) = (USB_OTG_HPRT_PPWR | hprt0);
  }

  if (((hprt0 & USB_OTG_HPRT_PPWR) == USB_OTG_HPRT_PPWR) && (state == 0U))
  {
    USB_OTG_HPRT0(instance) = ((~USB_OTG_HPRT_PPWR) & hprt0);
  }

  return USB_CORE_OK;
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */
/**
  * @}
  */
