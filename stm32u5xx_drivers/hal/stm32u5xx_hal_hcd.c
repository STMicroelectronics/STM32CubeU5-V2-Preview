/**
  ******************************************************************************
  * @file    stm32u5xx_hal_hcd.c
  * @brief   HCD HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the USB Peripheral Controller:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
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
    (#)Declare a hal_hcd_handle_t handle structure, for example:
       hal_hcd_handle_t  hhcd;

    (#)Fill parameters of Init structure in HCD handle

    (#)Call HAL_HCD_Init() API to initialize the HCD peripheral (Core, Host core, ...)

    (#)Initialize the HCD Clock resources through the HAL_HCD_Init() API:
        (##) Enable the HCD/USB Low Level interface clock using the following macros
             (+++) HAL_RCC_USB_OTG_FS_CLK_ENABLE();
             (+++) HAL_RCC_USB_OTG_HS_CLK_ENABLE(); (For High Speed Mode)
             (+++) HAL_RCC_USB_OTG_HS_ULPI_CLK_ENABLE(); (For High Speed Mode)

             (+++) HAL_RCC_USB_CLK_ENABLE();
        (##) Initialize the related GPIO clocks
        (##) Configure HCD pin-out
        (##) Configure HCD NVIC interrupt

    (#)Associate the Upper USB Host stack to the HAL HCD Driver:
        (##) hhcd.p_user_data = phost;

    (#)Enable HCD transmission and reception:
        (##) HAL_HCD_Start();

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

#if defined (USE_HAL_HCD_MODULE) && (USE_HAL_HCD_MODULE == 1)
#if defined (USB_OTG_FS) || defined (USB_OTG_HS) || defined (USB_DRD_FS)

/** @defgroup HCD HCD
  * @brief HCD HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/** @defgroup HCD_Private_Macros HCD Private Macros
  * @{
  */
/*! Macro to get the min value */
#define HCD_MIN(a, b)  (((a) < (b)) ? (a) : (b))
/*! Macro to get the max value */
#define HCD_MAX(a, b)  (((a) > (b)) ? (a) : (b))
/**
  * @}
  */
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup HCD_Private_Functions HCD Private Functions
  * @{
  */
#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
static void HCD_OTG_CHANNEL_IN_IRQHandler(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num);
static void HCD_OTG_CHANNEL_OUT_IRQHandler(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num);
static void HCD_OTG_RXQLVL_IRQHandler(hal_hcd_handle_t *hhcd);
static void HCD_OTG_Port_IRQHandler(hal_hcd_handle_t *hhcd);
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */

#if defined (USB_DRD_FS)
static void HCD_DRD_CHANNEL_IN_IRQHandler(hal_hcd_handle_t *hhcd, usb_core_phy_chep_t phy_ch_num);
static void HCD_DRD_CHANNEL_OUT_IRQHandler(hal_hcd_handle_t *hhcd, usb_core_phy_chep_t phy_ch_num);
static void HCD_DRD_Port_IRQHandler(hal_hcd_handle_t *hhcd);

#if defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1)
static void HCD_DRD_CHANNEL_IN_BulkDb(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num,
                                      usb_core_phy_chep_t phy_ch_num, uint32_t reg_value);

static void HCD_DRD_CHANNEL_OUT_BulkDb(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num,
                                       usb_core_phy_chep_t phy_ch_num, uint32_t reg_value);
#endif /* defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1) */

#if defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1)
static void HCD_DRD_CHANNEL_IN_IsocDb(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num,
                                      usb_core_phy_chep_t phy_ch_num, uint32_t reg_value);
#endif /* defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1) */
#endif /* defined (USB_DRD_FS) */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup HCD_Exported_Functions HCD Exported Functions
  * @{
  */

/** @defgroup HCD_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
          ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the host driver.
  * @param  hhcd HCD handle
  * @param  instance HCD instance
  * @retval HAL status
  */
hal_status_t HAL_HCD_Init(hal_hcd_handle_t *hhcd, hal_hcd_t instance)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check USB instance */
#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
  ASSERT_DBG_PARAM(IS_HCD_ALL_INSTANCE((usb_otg_global_t *)((uint32_t)instance)));
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */

#if defined (USB_DRD_FS)
  ASSERT_DBG_PARAM(IS_HCD_ALL_INSTANCE((usb_drd_global_t *)((uint32_t)instance)));
#endif /* defined (USB_DRD_FS) */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hhcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->instance = instance;

  switch (instance)
  {
#if defined (USB_OTG_FS)
    case HAL_HCD_OTG_FS:

      /* Register USB core instance operational functions */
      (void)USB_OTG_HCD_InitDriver(&hhcd->driver);

      hhcd->p_irq_handler = HAL_HCD_OTG_IRQHandler;

      /* Get the host channels number */
      hhcd->host_channels_nbr = USB_OTG_FS_CH_NBR;
      break;

#endif /* defined (USB_OTG_FS) */
#if defined (USB_OTG_HS)
    case HAL_HCD_OTG_HS:

      /* Register USB core instance operational functions */
      (void)USB_OTG_HCD_InitDriver(&hhcd->driver);

      hhcd->p_irq_handler = HAL_HCD_OTG_IRQHandler;

      /* Get the host channels number */
      hhcd->host_channels_nbr = USB_OTG_HS_CH_NBR;
      break;
#endif /* defined (USB_OTG_HS) */

#if defined (USB_DRD_FS)
    case HAL_HCD_DRD_FS:

      /* Register USB core instance operational functions */
      (void)USB_DRD_HCD_InitDriver(&hhcd->driver);

      hhcd->p_irq_handler = HAL_HCD_DRD_IRQHandler;

      /* Get the host channels number */
      hhcd->host_channels_nbr = USB_DRD_FS_CH_NBR;
      break;

#endif /* defined (USB_DRD_FS) */
    default:
      return HAL_ERROR;
      break;
  }

#if defined (USE_HAL_HCD_GET_LAST_ERRORS) && (USE_HAL_HCD_GET_LAST_ERRORS == 1)
  hhcd->last_error_codes = HAL_HCD_ERROR_NONE;
#endif /* USE_HAL_HCD_GET_LAST_ERRORS */

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
  hhcd->p_sof_cb = HAL_HCD_SofCallback;
  hhcd->p_port_connect_cb = HAL_HCD_PortConnectCallback;
  hhcd->p_port_disconnect_cb = HAL_HCD_PortDisconnectCallback;
  hhcd->p_port_enable_cb = HAL_HCD_PortEnabledCallback;
  hhcd->p_port_disable_cb = HAL_HCD_PortDisabledCallback;
  hhcd->p_port_suspend_cb = HAL_HCD_PortSuspendCallback;
  hhcd->p_port_resume_cb = HAL_HCD_PortResumeCallback;
  hhcd->p_ch_notify_urb_change_cb = HAL_HCD_ChannelNotifyURBChangeCallback;
  hhcd->p_error_cb = HAL_HCD_ErrorCallback;
#endif /* (USE_HAL_HCD_REGISTER_CALLBACKS) */

#if defined (USE_HAL_HCD_USER_DATA) && (USE_HAL_HCD_USER_DATA == 1U)
  hhcd->p_user_data = (void *)NULL;
#endif /* USE_HAL_HCD_USER_DATA */

  hhcd->global_state = HAL_HCD_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  DeInitialize the host driver.
  * @param  hhcd HCD handle
  */
void HAL_HCD_DeInit(hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check USB instance */
#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
  ASSERT_DBG_PARAM(IS_HCD_ALL_INSTANCE((usb_otg_global_t *)((uint32_t)hhcd->instance)));
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */

#if defined (USB_DRD_FS)
  ASSERT_DBG_PARAM(IS_HCD_ALL_INSTANCE((usb_drd_global_t *)((uint32_t)hhcd->instance)));
#endif /* defined (USB_DRD_FS) */

  hhcd->driver.core_deinit((uint32_t)hhcd->instance);

  /* Update Host Port State */
  hhcd->port_state = HAL_HCD_PORT_STATE_DEV_DISCONNECT;

  /* Disable global interrupt */
  (void)hhcd->driver.core_disable_interrupts((uint32_t)hhcd->instance);

#if defined (USE_HAL_HCD_USER_DATA) && (USE_HAL_HCD_USER_DATA == 1U)
  /* Reset the user data pointer to NULL */
  hhcd->p_user_data = (void *) NULL;
#endif /* USE_HAL_HCD_USER_DATA */

#if defined (USE_HAL_HCD_GET_LAST_ERRORS) && (USE_HAL_HCD_GET_LAST_ERRORS == 1)
  hhcd->last_error_codes = HAL_HCD_ERROR_NONE;
#endif /* USE_HAL_HCD_GET_LAST_ERRORS */

  hhcd->global_state = HAL_HCD_STATE_RESET;
}

/**
  * @brief  Configure the HCD according to the specified
  *         parameters in the hal_hcd_handle_t and initialize the associated handle.
  * @param  hhcd HCD handle
  * @param  p_config pointer to the peripheral configuration structure
  * @retval HAL status
  */
hal_status_t HAL_HCD_SetConfig(hal_hcd_handle_t *hhcd, const hal_hcd_config_t *p_config)
{
  hal_status_t ret = HAL_OK;
  usb_core_config_params_t usb_core_config = {0U};
  uint32_t ms = 0U;

  /* Check hhcd handler and configuration parameter */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_config == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hhcd->global_state, HAL_HCD_STATE_INIT);

  switch (hhcd->instance)
  {
#if defined (USB_OTG_FS)
    case HAL_HCD_OTG_FS:

      usb_core_config.phy_interface = (usb_core_phy_module_t)p_config->phy_interface;
      usb_core_config.channels_nbr = hhcd->host_channels_nbr;
      usb_core_config.core_speed = (usb_core_speed_t)p_config->hcd_speed;
      usb_core_config.dma_state = (usb_core_config_satus_t)HAL_HCD_DMA_DISABLED;
      break;
#endif /* defined (USB_OTG_FS) */
#if defined (USB_OTG_HS)
    case HAL_HCD_OTG_HS:

      usb_core_config.phy_interface = (usb_core_phy_module_t)p_config->phy_interface;
      usb_core_config.channels_nbr = hhcd->host_channels_nbr;
      usb_core_config.core_speed = (usb_core_speed_t)p_config->hcd_speed;
      usb_core_config.dma_state = (usb_core_config_satus_t)p_config->dma_enable;
      break;
#endif /* defined (USB_OTG_HS) */
#if defined (USB_DRD_FS)
    case HAL_HCD_DRD_FS:

      usb_core_config.phy_interface = (usb_core_phy_module_t)p_config->phy_interface;
      usb_core_config.channels_nbr = hhcd->host_channels_nbr;
      usb_core_config.core_speed = (usb_core_speed_t)p_config->hcd_speed;
      usb_core_config.bulk_db_state = (usb_core_config_satus_t)p_config->bulk_doublebuffer_enable;
#if defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1)
      usb_core_config.iso_db_state = (usb_core_config_satus_t)p_config->iso_doublebuffer_enable;
#endif /* defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1) */
      break;
#endif /* defined (USB_DRD_FS) */

    default:
      return HAL_ERROR;
      break;
  }

  /* Disable the Interrupts */
  (void)hhcd->driver.core_disable_interrupts((uint32_t)hhcd->instance);

  /* Init the Core (common init.) */
  if (hhcd->driver.core_init((uint32_t)hhcd->instance, &usb_core_config) != USB_CORE_OK)
  {
    hhcd->global_state = HAL_HCD_STATE_FAULT;
    return HAL_ERROR;
  }

  /* Force Host Mode */
  hhcd->driver.core_set_mode((uint32_t)hhcd->instance, USB_CORE_HOST_MODE);

  do
  {
    HAL_Delay(1U);
    ms++;
  } while ((hhcd->driver.core_get_mode((uint32_t)hhcd->instance) != USB_CORE_HOST_MODE)
           && (ms < USB_CORE_CURRENT_MODE_MAX_DELAY_MS));

  if (ms == USB_CORE_CURRENT_MODE_MAX_DELAY_MS)
  {
    hhcd->global_state = HAL_HCD_STATE_FAULT;
    ret = HAL_ERROR;
  }

  /* Init Host */
  if (hhcd->driver.host_init((uint32_t)hhcd->instance, &usb_core_config) != USB_CORE_OK)
  {
    hhcd->global_state = HAL_HCD_STATE_FAULT;
    ret = HAL_ERROR;
  }

  /* Host Port State */
  hhcd->port_state = HAL_HCD_PORT_STATE_DEV_DISCONNECT;

  if (ret != HAL_ERROR)
  {
    /* Set HCD Global state to IDLE */
    hhcd->global_state = HAL_HCD_STATE_IDLE;
  }

  return ret;
}

/**
  * @brief  Initialize a host channel.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  p_channel_config channel config structure
  * @retval HAL status
  */
hal_status_t HAL_HCD_SetConfigChannel(hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num,
                                      const hal_hcd_channel_config_t *p_channel_config)
{
  uint8_t ep_num;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  /* Check channel config */
  ASSERT_DBG_PARAM((p_channel_config != NULL));
  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_channel_config == NULL) || ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ep_num = p_channel_config->ep_address & 0xFU;

  hhcd->channel[ch_num].core_ch.do_ping = 0U;
  hhcd->channel[ch_num].core_ch.dev_addr = p_channel_config->device_address;
  hhcd->channel[ch_num].core_ch.ch_num = (usb_core_channel_t)ch_num;
  hhcd->channel[ch_num].core_ch.ep_type = (usb_core_ep_type_t)p_channel_config->ep_type;
  hhcd->channel[ch_num].core_ch.ep_num = (usb_core_endpoint_t)ep_num;

  (void)HAL_HCD_ClearChannelHubInfo(hhcd, ch_num);

  if ((p_channel_config->ep_address & USB_CORE_IN_EP_DIR_MSK) == USB_CORE_IN_EP_DIR_MSK)
  {
    hhcd->channel[ch_num].core_ch.ch_dir = USB_CORE_CH_IN_DIR;
  }
  else
  {
    hhcd->channel[ch_num].core_ch.ch_dir = USB_CORE_CH_OUT_DIR;
  }

  hhcd->channel[ch_num].core_ch.speed = (usb_core_device_speed_t)p_channel_config->device_speed;
  hhcd->channel[ch_num].core_ch.max_packet = p_channel_config->ep_mps;

  if (hhcd->driver.host_channel_init((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch) != USB_CORE_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Halt a host channel.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval HAL status
  */
hal_status_t HAL_HCD_HaltChannel(const hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num)
{
  hal_status_t status = HAL_OK;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->driver.host_channel_halt((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);

  return status;
}


/**
  * @brief  SOF callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_SofCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_SofCallback could be implemented in the user file
   */
}

/**
  * @brief Connection Event callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_PortConnectCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_PortConnectCallback could be implemented in the user file
   */
}

/**
  * @brief  Disconnection Event callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_PortDisconnectCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_PortDisconnectCallback could be implemented in the user file
   */
}

/**
  * @brief  Port Enabled  Event callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_PortEnabledCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_PortEnabledCallback could be implemented in the user file
   */
}

/**
  * @brief  Port Disabled  Event callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_PortDisabledCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_PortDisabledCallback could be implemented in the user file
   */
}

/**
  * @brief  Suspend Event callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_PortSuspendCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_PortSuspendCallback could be implemented in the user file
  */

}

/**
  * @brief  Resume Event callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_PortResumeCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_PortResumeCallback could be implemented in the user file
  */
}

/**
  * @brief  Notify URB state change callback.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  urb_state:
  *          This parameter can be one of these values:
  *            HAL_HCD_CHANNEL_URB_STATE_IDLE/
  *            HAL_HCD_CHANNEL_URB_STATE_DONE/
  *            HAL_HCD_CHANNEL_URB_STATE_NOTREADY/
  *            HAL_HCD_CHANNEL_URB_STATE_ERROR/
  *            HAL_HCD_CHANNEL_URB_STATE_STALL/
  */
__WEAK void HAL_HCD_ChannelNotifyURBChangeCallback(hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num,
                                                   hal_hcd_channel_urb_state_t urb_state)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);
  STM32_UNUSED(ch_num);
  STM32_UNUSED(urb_state);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_ChannelNotifyURBChangeCallback could be implemented in the user file
   */
}

/**
  * @brief  HCD Error callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_ErrorCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_ErrorCallback could be implemented in the user file
   */
}

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register User SOF Callback
  *         To be used instead of the weak predefined callback
  * @param  hhcd USB HCD handle
  * @param  p_callback pointer to the Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterSofCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_sof_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB HCD Connect Callback
  *         To be used instead of the weak predefined callback
  * @param  hhcd USB HCD handle
  * @param  p_callback pointer to the Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterPortConnectCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_port_connect_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB HCD Disconnect Callback
  *         To be used instead of the weak predefined callback
  * @param  hhcd USB HCD handle
  * @param  p_callback pointer to the Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterPortDisconnectCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_port_disconnect_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB HCD Port Enabled Callback
  *         To be used instead of the weak predefined callback
  * @param  hhcd USB HCD handle
  * @param  p_callback pointer to the Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterPortEnabledCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_port_enable_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB HCD Port Disabled Callback
  *         To be used instead of the weak predefined callback
  * @param  hhcd USB HCD handle
  * @param  p_callback pointer to the Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterPortDisabledCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_port_disable_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB HCD Suspend Callback
  *         To be used instead of the weak predefined callback
  * @param  hhcd USB HCD handle
  * @param  p_callback pointer to the Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterPortSuspendCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_port_suspend_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB HCD Resume Callback
  *         To be used instead of the weak predefined callback
  * @param  hhcd USB HCD handle
  * @param  p_callback pointer to the Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterPortResumeCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_port_resume_cb = p_callback;

  return HAL_OK;
}


/**
  * @brief  Register USB HCD Host Channel Notify URB Change Callback
  *         To be used instead of the weak HAL_HCD_ChannelNotifyURBChangeCallback() predefined callback
  * @param  hhcd HCD handle
  * @param  p_callback pointer to the USB HCD Host Channel Notify URB Change Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterChannelNotifyURBChangeCallback(hal_hcd_handle_t *hhcd,
                                                            hal_hcd_ch_notify_urb_change_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_ch_notify_urb_change_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register USB HCD Error Callback
  *         To be used instead of the weak HAL_HCD_ErrorCallback() predefined callback
  * @param  hhcd HCD handle
  * @param  p_callback pointer to the USB HCD Error Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterErrorCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_error_cb = p_callback;

  return HAL_OK;
}

#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup HCD_Exported_Functions_Group2 Input and Output operation functions
  *  @brief   Data transfers functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the HCD data
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Return the last host transfer size.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval last transfer size in byte
  */
uint32_t HAL_HCD_GetChannelTransferCount(const hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

  return hhcd->channel[ch_num].core_ch.xfer_count;
}

/**
  * @brief  Return the current Host frame number.
  * @param  hhcd HCD handle
  * @retval Current Host frame number
  */
uint32_t HAL_HCD_GetCurrentFrame(const hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  return (hhcd->driver.host_get_current_frame((uint32_t)hhcd->instance));
}

/**
  * @brief  Return the Host enumeration speed.
  * @param  hhcd HCD handle
  * @retval Enumeration speed
  */
hal_hcd_port_speed_t HAL_HCD_GetPortSpeed(const hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  return (hal_hcd_port_speed_t)hhcd->driver.host_get_port_speed((uint32_t)hhcd->instance);
}

/**
  * @brief  Set host channel hub information.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  hub_addr Hub address
  * @param  port_nbr Hub port number
  * @retval HAL status
  */
hal_status_t HAL_HCD_SetChannelHubInfo(hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num,
                                       uint8_t hub_addr, uint8_t port_nbr)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

#if defined (USB_OTG_HS)
  hal_hcd_port_speed_t host_port_speed;

  host_port_speed = (hal_hcd_port_speed_t)hhcd->driver.host_get_port_speed((uint32_t)hhcd->instance);

  /* LS/FS device plugged to HS HUB */
  if ((hhcd->channel[ch_num].core_ch.speed != (usb_core_device_speed_t)HAL_HCD_DEVICE_SPEED_HS)
      && (host_port_speed == HAL_HCD_PORT_SPEED_HS))
  {
    hhcd->channel[ch_num].core_ch.do_ssplit = 1U;

    if ((hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_CTRL)
        && (hhcd->channel[ch_num].core_ch.ch_dir == USB_CORE_CH_IN_DIR))
    {
      hhcd->channel[ch_num].toggle_in = 1U;
    }
  }
#endif /* defined (USB_OTG_HS) */

  hhcd->channel[ch_num].core_ch.hub_addr = hub_addr;
  hhcd->channel[ch_num].core_ch.hub_port_nbr = port_nbr;

  return HAL_OK;
}

/**
  * @brief  Clear host channel hub information.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval HAL status
  */
hal_status_t HAL_HCD_ClearChannelHubInfo(hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

#if defined (USB_OTG_HS)
  hhcd->channel[ch_num].core_ch.do_ssplit = 0U;
  hhcd->channel[ch_num].core_ch.do_csplit = 0U;
#endif /* defined (USB_OTG_HS) */
  hhcd->channel[ch_num].core_ch.hub_addr = 0U;
  hhcd->channel[ch_num].core_ch.hub_port_nbr = 0U;

  return HAL_OK;
}

/**
  * @brief  Return the HCD DMA status enabled or disabled.
  * @param  hhcd HCD handle
  * @retval state
  */
hal_hcd_dma_status_t HAL_HCD_IsEnabledDma(const hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  return (hal_hcd_dma_status_t)(hhcd->driver.core_get_dma_status((uint32_t)hhcd->instance));
}


/**
  * @brief  Submit a new URB transfer request for processing.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  p_channel_transfer_req Channel transfer request.
  * @retval HAL status
  */
hal_status_t HAL_HCD_RequestChannelTransfer(hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num,
                                            hal_hcd_channel_transfer_req_t *p_channel_transfer_req)
{
  hal_status_t ret = HAL_OK;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->channel[ch_num].core_ch.ch_dir = (usb_core_ch_direction_t)p_channel_transfer_req->ch_dir;
  hhcd->channel[ch_num].core_ch.ep_type = (usb_core_ep_type_t)p_channel_transfer_req->ep_type;

  if (p_channel_transfer_req->token_type == 0U)
  {
    hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_SETUP;
    hhcd->channel[ch_num].core_ch.do_ping = p_channel_transfer_req->do_ping;
  }
  else
  {
    hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA1;
  }

  /* Manage Data Toggle */
  switch (p_channel_transfer_req->ep_type)
  {
    case HAL_HCD_EP_TYPE_CTRL:
      if (p_channel_transfer_req->token_type == 1U) /* send data */
      {
        if (p_channel_transfer_req->ch_dir == HAL_HCD_CH_OUT_DIR)
        {
          if (p_channel_transfer_req->transfer_length == 0U)
          {
            /* For Status OUT stage, Length == 0U, Status Out PID = 1 */
            hhcd->channel[ch_num].toggle_out = 1U;
          }

          /* Set the Data Toggle bit as per the Flag */
          if (hhcd->channel[ch_num].toggle_out == 0U)
          {
            /* Put the PID 0 */
            hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA0;
          }
          else
          {
            /* Put the PID 1 */
            hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA1;
          }
        }
        else
        {
          if (hhcd->channel[ch_num].core_ch.do_ssplit == 1U)
          {
            if (hhcd->channel[ch_num].toggle_in == 0U)
            {
              hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA0;
            }
            else
            {
              hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA1;
            }
          }
        }
      }
      break;

    case HAL_HCD_EP_TYPE_BULK:
      if (p_channel_transfer_req->ch_dir == HAL_HCD_CH_OUT_DIR)
      {
        /* Set the Data Toggle bit as per the Flag */
        if (hhcd->channel[ch_num].toggle_out == 0U)
        {
          /* Put the PID 0 */
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA0;
        }
        else
        {
          /* Put the PID 1 */
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA1;
        }
      }
      else
      {
        if (hhcd->channel[ch_num].toggle_in == 0U)
        {
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA0;
        }
        else
        {
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA1;
        }
      }

      break;
    case HAL_HCD_EP_TYPE_INTR:
      if (p_channel_transfer_req->ch_dir == HAL_HCD_CH_OUT_DIR)
      {
        /* Set the Data Toggle bit as per the Flag */
        if (hhcd->channel[ch_num].toggle_out == 0U)
        {
          /* Put the PID 0 */
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA0;
        }
        else
        {
          /* Put the PID 1 */
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA1;
        }
      }
      else
      {
        if (hhcd->channel[ch_num].toggle_in == 0U)
        {
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA0;
        }
        else
        {
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA1;
        }
      }
      break;
#if defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1)
    case HAL_HCD_EP_TYPE_ISOC:
      hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA0;
      break;
#endif /* defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1) */
    default:
      return HAL_ERROR;
      break;
  }

  hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_IDLE;
  hhcd->channel[ch_num].core_ch.p_xfer_buffer = p_channel_transfer_req->p_buffer;
  hhcd->channel[ch_num].core_ch.xfer_length = p_channel_transfer_req->transfer_length;
  hhcd->channel[ch_num].core_ch.xfer_size = p_channel_transfer_req->transfer_length;
  hhcd->channel[ch_num].core_ch.xfer_count = 0U;
  hhcd->channel[ch_num].core_ch.ch_num = (usb_core_channel_t)ch_num;
  hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_IDLE;

  if (hhcd->driver.host_channel_start((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch) != USB_CORE_OK)
  {
    ret = HAL_ERROR;
  }

  return ret;
}

/**
  * @brief  Handles HCD interrupt request.
  * @param  hhcd HCD handle
  */
void HAL_HCD_IRQHandler(hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((hhcd->p_irq_handler != NULL));

  hhcd->current_mode = hhcd->driver.core_get_mode((uint32_t)hhcd->instance);

  hhcd->p_irq_handler(hhcd);

  return;
}

#if defined (USE_HAL_HCD_GET_LAST_ERRORS) && (USE_HAL_HCD_GET_LAST_ERRORS == 1)
/**
  * @brief Get Last Error codes.
  * @param hhcd Pointer to a hal_hcd_handle_t
  * @retval last error code.
  */
uint32_t HAL_HCD_GetLastErrorCodes(const hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  return (hhcd->last_error_codes);
}
#endif /* USE_HAL_HCD_GET_LAST_ERRORS */

#if defined (USE_HAL_HCD_USER_DATA) && (USE_HAL_HCD_USER_DATA == 1)

/**
  * @brief Set the user data pointer into the handle.
  * @param hhcd Pointer to a hal_hcd_handle_t
  * @param p_user_data Pointer to the user data.
  */
void HAL_HCD_SetUserData(hal_hcd_handle_t *hhcd, const void *p_user_data)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  hhcd->p_user_data = p_user_data;
  return;
}

/**
  * @brief Get the user data pointer from the handle.
  * @param hhcd Pointer to a hal_hcd_handle_t
  * @retval Pointer to the user data.
  */
const void *HAL_HCD_GetUserData(const hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  return (hhcd->p_user_data);
}

#endif /* USE_HAL_HCD_USER_DATA */

/**
  * @}
  */

/** @defgroup HCD_Exported_Functions_Group3 Peripheral Control functions
  *  @brief   Management functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the HCD data
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Start the host driver.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
hal_status_t HAL_HCD_Start(hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hhcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hhcd->global_state, HAL_HCD_STATE_IDLE);

  /* start host */
  (void)hhcd->driver.host_start((uint32_t)hhcd->instance);

  hhcd->global_state = HAL_HCD_STATE_ACTIVE;

  return HAL_OK;
}

/**
  * @brief  Stop the host driver.
  * @param  hhcd HCD handle
  * @retval HAL status
  */

hal_status_t HAL_HCD_Stop(hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hhcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hhcd->global_state, HAL_HCD_STATE_ACTIVE);

  (void)hhcd->driver.host_stop((uint32_t)hhcd->instance);

  hhcd->global_state = HAL_HCD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Reset the host port.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
hal_status_t HAL_HCD_ResetPort(hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hhcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Reset the USB Port by inserting an SE0 on the bus */
  (void)hhcd->driver.host_port_reset((uint32_t)hhcd->instance, USB_CORE_PORT_RESET_STS_SET);

  HAL_Delay(100);

  (void)hhcd->driver.host_port_reset((uint32_t)hhcd->instance, USB_CORE_PORT_RESET_STS_CLEAR);

  HAL_Delay(30);

  if (hhcd->port_state == HAL_HCD_PORT_STATE_DEV_CONNECT)
  {
    hhcd->port_state = HAL_HCD_PORT_STATE_DEV_RESET;
  }

  return HAL_OK;
}

/**
  * @brief  Put the Device in suspend mode
  * @param  hhcd HCD handle
  * @retval HAL status
  */
hal_status_t HAL_HCD_SuspendPort(hal_hcd_handle_t *hhcd)
{
  hal_status_t ret = HAL_OK;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hhcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (hhcd->driver.host_port_suspend((uint32_t)hhcd->instance) != USB_CORE_OK)
  {
    ret = HAL_ERROR;
  }

  if (ret != HAL_ERROR)
  {
    hhcd->port_state = HAL_HCD_PORT_STATE_DEV_SUSPEND;
  }

  return ret;
}

/**
  * @brief  Resme the host port.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
hal_status_t HAL_HCD_ResumePort(hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hhcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  (void)hhcd->driver.host_port_resume((uint32_t)hhcd->instance, USB_CORE_PORT_RESUME_STS_SET);

  HAL_Delay(30U);

  (void)hhcd->driver.host_port_resume((uint32_t)hhcd->instance, USB_CORE_PORT_RESUME_STS_CLEAR);

  hhcd->port_state = HAL_HCD_PORT_STATE_DEV_RESUME;

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup HCD_Exported_Functions_Group4 Peripheral State functions
  *  @brief   Peripheral State functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral State functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  Return the HCD handle state.
  * @param  hhcd HCD handle
  * @retval HAL state
  */
hal_hcd_state_t HAL_HCD_GetState(const hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  return hhcd->global_state;
}

/**
  * @brief  Return  URB state for a channel.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval URB state.
  *          This parameter can be one of these values:
  *            HAL_HCD_CHANNEL_URB_STATE_IDLE/
  *            HAL_HCD_CHANNEL_URB_STATE_DONE/
  *            HAL_HCD_CHANNEL_URB_STATE_NOTREADY/
  *            HAL_HCD_CHANNEL_URB_STATE_ERROR/
  *            HAL_HCD_CHANNEL_URB_STATE_STALL
  */
hal_hcd_channel_urb_state_t HAL_HCD_GetChannelURBState(const hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

  return hhcd->channel[ch_num].urb_state;
}

/**
  * @brief  Return the Host Channel state.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 0 to 15
  * @retval Host channel state
  *          This parameter can be one of these values:
  *            HAL_HCD_CHANNEL_STATE_RESET
  *            HAL_HCD_CHANNEL_STATE_IDLE
  *            HAL_HCD_CHANNEL_STATE_XFRC
  *            HAL_HCD_CHANNEL_STATE_HALTED
  *            HAL_HCD_CHANNEL_STATE_NYET
  *            HAL_HCD_CHANNEL_STATE_NAK
  *            HAL_HCD_CHANNEL_STATE_STALL
  *            HAL_HCD_CHANNEL_STATE_XACTERR
  *            HAL_HCD_CHANNEL_STATE_BBLERR
  *            HAL_HCD_CHANNEL_STATE_DATATGLERR
  */
hal_hcd_channel_state_t HAL_HCD_GetChannelState(const hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

  return hhcd->channel[ch_num].state;
}

/**
  * @}
  */


/**
  * @}
  */

/** @addtogroup HCD_Private_Functions HCD Private Functions
  * @{
  */


#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
/**
  * @brief  Handle HCD interrupt request.
  * @param  hhcd HCD handle
  */
void HAL_HCD_OTG_IRQHandler(hal_hcd_handle_t *hhcd)
{
  usb_otg_global_t *p_usb;
  uint32_t ch_idx;
  uint32_t interrupt;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  p_usb = USB_OTG_GET_INSTANCE((uint32_t)hhcd->instance);

  /* Ensure that we are in host mode */
  if (hhcd->current_mode == USB_CORE_HOST_MODE)
  {
    /* Avoid spurious interrupt */
    if (USB_OTG_ReadInterrupts((uint32_t)hhcd->instance) == 0U)
    {
      return;
    }

    if ((USB_OTG_ReadInterrupts((uint32_t)hhcd->instance) & USB_OTG_GINTSTS_PXFR_INCOMPISOOUT) ==
        USB_OTG_GINTSTS_PXFR_INCOMPISOOUT)
    {
      /* Incorrect mode, acknowledge the interrupt */
      USB_OTG_ClearInterrupts((uint32_t)hhcd->instance, USB_OTG_GINTSTS_PXFR_INCOMPISOOUT);
    }

    if ((USB_OTG_ReadInterrupts((uint32_t)hhcd->instance) & USB_OTG_GINTSTS_IISOIXFR) == USB_OTG_GINTSTS_IISOIXFR)
    {
      /* Incorrect mode, acknowledge the interrupt */
      USB_OTG_ClearInterrupts((uint32_t)hhcd->instance, USB_OTG_GINTSTS_IISOIXFR);
    }

    if ((USB_OTG_ReadInterrupts((uint32_t)hhcd->instance) & USB_OTG_GINTSTS_PTXFE) == USB_OTG_GINTSTS_PTXFE)
    {
      /* Incorrect mode, acknowledge the interrupt */
      USB_OTG_ClearInterrupts((uint32_t)hhcd->instance, USB_OTG_GINTSTS_PTXFE);
    }

    if ((USB_OTG_ReadInterrupts((uint32_t)hhcd->instance) & USB_OTG_GINTSTS_MMIS) == USB_OTG_GINTSTS_MMIS)
    {
      /* Incorrect mode, acknowledge the interrupt */
      USB_OTG_ClearInterrupts((uint32_t)hhcd->instance, USB_OTG_GINTSTS_MMIS);
    }

    /* Handle Host Disconnect Interrupts */
    if ((USB_OTG_ReadInterrupts((uint32_t)hhcd->instance) & USB_OTG_GINTSTS_DISCINT) == USB_OTG_GINTSTS_DISCINT)
    {
      USB_OTG_ClearInterrupts((uint32_t)hhcd->instance, USB_OTG_GINTSTS_DISCINT);

      hhcd->port_state = HAL_HCD_PORT_STATE_DEV_DISCONNECT;

      if ((USB_OTG_HPRT0((uint32_t)hhcd->instance) & USB_OTG_HPRT_PCSTS) == 0U)
      {
        /* Flush USB Fifo */
        (void)USB_OTG_FlushTxFifo((uint32_t)hhcd->instance, 0x10U);
        (void)USB_OTG_FlushRxFifo((uint32_t)hhcd->instance);

        if ((p_usb->GUSBCFG & USB_OTG_GUSBCFG_PHYSEL) == USB_OTG_GUSBCFG_PHYSEL)
        {
          /* Restore FS Clock */
          (void)USB_OTG_InitFSLSPClkSel((uint32_t)hhcd->instance, (uint8_t)USB_OTG_HCFG_48_MHZ);
        }

        /* Handle Host Port Disconnect Interrupt */
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
        hhcd->p_port_disconnect_cb(hhcd);
#else
        HAL_HCD_PortDisconnectCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
      }
    }

    /* Handle Host Port Interrupts */
    if ((USB_OTG_ReadInterrupts((uint32_t)hhcd->instance) & USB_OTG_GINTSTS_HPRTINT) == USB_OTG_GINTSTS_HPRTINT)
    {
      HCD_OTG_Port_IRQHandler(hhcd);
    }

    /* Handle Host SOF Interrupt */
    if ((USB_OTG_ReadInterrupts((uint32_t)hhcd->instance) & USB_OTG_GINTSTS_SOF) == USB_OTG_GINTSTS_SOF)
    {
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_sof_cb(hhcd);
#else
      HAL_HCD_SofCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

      USB_OTG_ClearInterrupts((uint32_t)hhcd->instance, USB_OTG_GINTSTS_SOF);
    }

    /* Handle Host channel Interrupt */
    if ((USB_OTG_ReadInterrupts((uint32_t)hhcd->instance) & USB_OTG_GINTSTS_HCINT) == USB_OTG_GINTSTS_HCINT)
    {
      interrupt = USB_OTG_GetChannelInterrupt((uint32_t)hhcd->instance);
      for (ch_idx = 0U; ch_idx < HCD_MIN(hhcd->host_channels_nbr, USE_HAL_HCD_MAX_CHANNEL_NB); ch_idx++)
      {
        if ((interrupt & (1UL << (ch_idx & 0xFU))) != 0U)
        {
          if ((USB_OTG_CHANNEL(hhcd->instance, ch_idx)->HCCHAR & USB_OTG_HCCHAR_EPDIR) == USB_OTG_HCCHAR_EPDIR)
          {
            HCD_OTG_CHANNEL_IN_IRQHandler(hhcd, (usb_core_channel_t)ch_idx);
          }
          else
          {
            HCD_OTG_CHANNEL_OUT_IRQHandler(hhcd, (usb_core_channel_t)ch_idx);
          }
        }
      }
      USB_OTG_ClearInterrupts((uint32_t)hhcd->instance, USB_OTG_GINTSTS_HCINT);
    }

    /* Handle Rx Queue Level Interrupts */
    if ((USB_OTG_ReadInterrupts((uint32_t)hhcd->instance) & USB_OTG_GINTSTS_RXFLVL) == USB_OTG_GINTSTS_RXFLVL)
    {
      USB_OTG_MASK_IT(p_usb, USB_OTG_GINTSTS_RXFLVL);

      HCD_OTG_RXQLVL_IRQHandler(hhcd);

      USB_OTG_UNMASK_IT(p_usb, USB_OTG_GINTSTS_RXFLVL);
    }
  }
}


/**
  * @brief  Handle Host Channel IN interrupt requests.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  */
static void HCD_OTG_CHANNEL_IN_IRQHandler(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num)
{
  const usb_otg_global_t *p_usb;
  uint32_t hcchar_reg;

  p_usb = USB_OTG_GET_INSTANCE((uint32_t)hhcd->instance);

  if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                     (usb_core_channel_t)ch_num) & USB_OTG_HCINT_AHBERR) == USB_OTG_HCINT_AHBERR)
  {
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_AHBERR);
    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XACTERR;
    (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_BBERR) == USB_OTG_HCINT_BBERR)
  {
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_BBERR);
    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_BBLERR;
    (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_STALL) == USB_OTG_HCINT_STALL)
  {
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_STALL);
    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_STALL;
    (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_DTERR) == USB_OTG_HCINT_DTERR)
  {
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_DTERR);
    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_DATATGLERR;
    (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_TXERR) == USB_OTG_HCINT_TXERR)
  {
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_TXERR);
    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XACTERR;
    (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
  }
  else
  {
    /* ... */
  }

  if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance, ch_num) & USB_OTG_HCINT_FRMOR) == USB_OTG_HCINT_FRMOR)
  {
    (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_FRMOR);
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_XFRC) == USB_OTG_HCINT_XFRC)
  {
    /* Clear any pending ACK IT */
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_ACK);

    if (hhcd->channel[ch_num].core_ch.do_csplit == 1U)
    {
      hhcd->channel[ch_num].core_ch.do_csplit = 0U;
      USB_OTG_CHANNEL_CLEAR_CSPLT(hhcd->instance, ch_num);
    }

    if ((p_usb->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) == USB_OTG_GAHBCFG_DMAEN)
    {
      uint32_t rx_count = hhcd->channel[ch_num].core_ch.xfer_size - \
                          (USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCTSIZ & USB_OTG_HCTSIZ_XFRSIZ);

      hhcd->channel[ch_num].core_ch.xfer_count = rx_count;
    }

    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XFRC;
    hhcd->channel[ch_num].err_cnt = 0U;
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_XFRC);

    if ((hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_CTRL)
        || (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_BULK))
    {
      (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
      USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_NAK);
    }
    else if ((hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_ISOC)
             || (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_INTR))
    {
      USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR |= USB_OTG_HCCHAR_ODDFRM;
      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
      HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
    }
    else
    {
      /* ... */
    }

    if ((p_usb->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) == USB_OTG_GAHBCFG_DMAEN)
    {
      if ((((hhcd->channel[ch_num].core_ch.xfer_count + hhcd->channel[ch_num].core_ch.max_packet - 1U) /
            hhcd->channel[ch_num].core_ch.max_packet) & 1U) != 0U)
      {
        hhcd->channel[ch_num].toggle_in ^= 1U;
      }
    }
    else
    {
      hhcd->channel[ch_num].toggle_in ^= 1U;
    }
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_ACK) == USB_OTG_HCINT_ACK)
  {
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_ACK);

    if (hhcd->channel[ch_num].core_ch.do_ssplit == 1U)
    {
      hhcd->channel[ch_num].core_ch.do_csplit = 1U;
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_ACK;

      (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
    }
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_CHH) == USB_OTG_HCINT_CHH)
  {
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_CHH);

    if (hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_XFRC)
    {
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;
      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;
    }
    else if (hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_STALL)
    {
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;
      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_STALL;
    }
    else if ((hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_XACTERR)
             || (hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_DATATGLERR))
    {
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;
      hhcd->channel[ch_num].err_cnt++;

      if (hhcd->channel[ch_num].err_cnt > 2U)
      {
        hhcd->channel[ch_num].err_cnt = 0U;

        if (hhcd->channel[ch_num].core_ch.do_ssplit == 1U)
        {
          hhcd->channel[ch_num].core_ch.do_csplit = 0U;
          hhcd->channel[ch_num].ep_ss_schedule = 0U;
          USB_OTG_CHANNEL_CLEAR_CSPLT(hhcd->instance, ch_num);
        }

        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_ERROR;
      }
      else
      {
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;

        if ((hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_CTRL)
            || (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_BULK))
        {
          /* Re-activate the channel */
          hcchar_reg = USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR;
          hcchar_reg &= ~USB_OTG_HCCHAR_CHDIS;
          hcchar_reg |= USB_OTG_HCCHAR_CHENA;
          USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR = hcchar_reg;
        }
      }
    }
    else if (hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_NYET)
    {
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;

      if (hhcd->channel[ch_num].core_ch.do_csplit == 1U)
      {
        if (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_INTR)
        {
          hhcd->channel[ch_num].nyet_err_cnt++;

          if (hhcd->channel[ch_num].nyet_err_cnt > 2U)
          {
            hhcd->channel[ch_num].nyet_err_cnt = 0U;
            hhcd->channel[ch_num].core_ch.do_csplit = 0U;

            if (hhcd->channel[ch_num].err_cnt < 3U)
            {
              hhcd->channel[ch_num].ep_ss_schedule = 1U;
            }

            USB_OTG_CHANNEL_CLEAR_CSPLT(hhcd->instance, ch_num);
            hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_ERROR;
          }
          else
          {
            hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;
          }
        }
        else
        {
          hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;
        }

        if ((hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_CTRL)
            || (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_BULK))
        {
          /* Re-activate the channel */
          hcchar_reg = USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR;
          hcchar_reg &= ~USB_OTG_HCCHAR_CHDIS;
          hcchar_reg |= USB_OTG_HCCHAR_CHENA;
          USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR = hcchar_reg;
        }
      }
    }
    else if (hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_ACK)
    {
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;

      if (hhcd->channel[ch_num].core_ch.do_csplit == 1U)
      {
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;

        /* Set Complete split and re-activate the channel */
        USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCSPLT |= USB_OTG_HCSPLT_COMPLSPLT;
        USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCINTMSK |= USB_OTG_HCINTMSK_NYET;
        USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCINTMSK &= ~USB_OTG_HCINT_ACK;

        if ((hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_CTRL)
            || (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_BULK))
        {
          /* Re-activate the channel */
          hcchar_reg = USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR;
          hcchar_reg &= ~USB_OTG_HCCHAR_CHDIS;
          hcchar_reg |= USB_OTG_HCCHAR_CHENA;
          USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR = hcchar_reg;
        }
      }
    }
    else if (hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_NAK)
    {
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;
      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;

      if ((hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_CTRL)
          || (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_BULK))
      {
        /* Re-activate the channel */
        hcchar_reg = USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR;
        hcchar_reg &= ~USB_OTG_HCCHAR_CHDIS;
        hcchar_reg |= USB_OTG_HCCHAR_CHENA;
        USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR = hcchar_reg;
      }
    }
    else if (hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_BBLERR)
    {
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;
      hhcd->channel[ch_num].err_cnt++;
      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_ERROR;
    }
    else
    {
      if (hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_HALTED)
      {
        return;
      }
    }

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
    HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_NYET) == USB_OTG_HCINT_NYET)
  {
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_NYET);
    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_NYET;

    if (hhcd->channel[ch_num].core_ch.do_ssplit == 0U)
    {
      hhcd->channel[ch_num].err_cnt = 0U;
    }

    (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_NAK) == USB_OTG_HCINT_NAK)
  {
    if (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_INTR)
    {
      hhcd->channel[ch_num].err_cnt = 0U;
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_NAK;
      (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
    }
    else if ((hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_CTRL)
             || (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_BULK))
    {
      hhcd->channel[ch_num].err_cnt = 0U;

      if (((p_usb->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) != USB_OTG_GAHBCFG_DMAEN)
          || (hhcd->channel[ch_num].core_ch.do_csplit == 1U))
      {
        hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_NAK;
        (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
      }
    }
    else
    {
      /* ... */
    }

    if (hhcd->channel[ch_num].core_ch.do_csplit == 1U)
    {
      hhcd->channel[ch_num].core_ch.do_csplit = 0U;
      USB_OTG_CHANNEL_CLEAR_CSPLT(hhcd->instance, ch_num);
      USB_OTG_CHANNEL_UNMASK_ACK_IT(hhcd->instance, ch_num);
    }

    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_NAK);
  }
  else
  {
    /* ... */
  }
}

/**
  * @brief  Handle Host Channel OUT interrupt requests.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  */
static void HCD_OTG_CHANNEL_OUT_IRQHandler(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num)
{
  const usb_otg_global_t *p_usb;
  uint32_t hcchar_reg;
  uint32_t num_packets;

  p_usb = USB_OTG_GET_INSTANCE((uint32_t)hhcd->instance);

  if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                     ch_num) & USB_OTG_HCINT_AHBERR) == USB_OTG_HCINT_AHBERR)
  {
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_AHBERR);
    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XACTERR;
    (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_ACK) == USB_OTG_HCINT_ACK)
  {
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_ACK);

    if (hhcd->channel[ch_num].core_ch.do_ping == 1U)
    {
      hhcd->channel[ch_num].core_ch.do_ping = 0U;
      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_ACK;
      (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
    }

    if ((hhcd->channel[ch_num].core_ch.do_ssplit == 1U) && (hhcd->channel[ch_num].core_ch.do_csplit == 0U))
    {
      if (hhcd->channel[ch_num].core_ch.ep_type != USB_CORE_EP_TYPE_ISOC)
      {
        hhcd->channel[ch_num].core_ch.do_csplit = 1U;
      }

      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_ACK;
      (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);

      /* Reset error_count */
      hhcd->channel[ch_num].err_cnt = 0U;
    }
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_FRMOR) == USB_OTG_HCINT_FRMOR)
  {
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_FRMOR);
    (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_XFRC) == USB_OTG_HCINT_XFRC)
  {
    hhcd->channel[ch_num].err_cnt = 0U;

    /* Transaction completed with NYET state, update do ping state */
    if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                       ch_num) & USB_OTG_HCINT_NYET) == USB_OTG_HCINT_NYET)
    {
      hhcd->channel[ch_num].core_ch.do_ping = 1U;
      USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_NYET);
    }

    if (hhcd->channel[ch_num].core_ch.do_csplit != 0U)
    {
      hhcd->channel[ch_num].core_ch.do_csplit = 0U;
      USB_OTG_CHANNEL_CLEAR_CSPLT(hhcd->instance, ch_num);
    }

    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_XFRC);
    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XFRC;
    (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_NYET) == USB_OTG_HCINT_NYET)
  {
    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_NYET;

    if (hhcd->channel[ch_num].core_ch.do_ssplit == 0U)
    {
      hhcd->channel[ch_num].core_ch.do_ping = 1U;
    }

    hhcd->channel[ch_num].err_cnt = 0U;
    (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_NYET);
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_STALL) == USB_OTG_HCINT_STALL)
  {
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_STALL);
    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_STALL;
    (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_NAK) == USB_OTG_HCINT_NAK)
  {
    hhcd->channel[ch_num].err_cnt = 0U;
    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_NAK;

    if (hhcd->channel[ch_num].core_ch.do_ping == 0U)
    {
      if (hhcd->channel[ch_num].core_ch.speed == (usb_core_device_speed_t)HAL_HCD_DEVICE_SPEED_HS)
      {
        hhcd->channel[ch_num].core_ch.do_ping = 1U;
      }
    }

    (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_NAK);
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_TXERR) == USB_OTG_HCINT_TXERR)
  {
    if ((p_usb->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) != USB_OTG_GAHBCFG_DMAEN)
    {
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XACTERR;
      (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
    }
    else
    {
      hhcd->channel[ch_num].err_cnt++;
      if (hhcd->channel[ch_num].err_cnt > 2U)
      {
        hhcd->channel[ch_num].err_cnt = 0U;
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_ERROR;

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
        hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
        HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
      }
      else
      {
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;

        /* Re-activate the channel  */
        hcchar_reg = USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR;
        hcchar_reg &= ~USB_OTG_HCCHAR_CHDIS;
        hcchar_reg |= USB_OTG_HCCHAR_CHENA;
        USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR = hcchar_reg;
      }
    }
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_TXERR);
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_DTERR) == USB_OTG_HCINT_DTERR)
  {
    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_DATATGLERR;
    (void)USB_OTG_HaltChannel((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_DTERR);
  }
  else if ((USB_OTG_ReadChannelInterrupts((uint32_t)hhcd->instance,
                                          ch_num) & USB_OTG_HCINT_CHH) == USB_OTG_HCINT_CHH)
  {
    USB_OTG_CHANNEL_CLEAR_IT(hhcd->instance, ch_num, USB_OTG_HCINT_CHH);

    if (hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_XFRC)
    {
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;
      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;

      if ((hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_BULK)
          || (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_INTR))
      {
        if ((p_usb->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) != USB_OTG_GAHBCFG_DMAEN)
        {
          hhcd->channel[ch_num].toggle_out ^= 1U;
        }

        if (((p_usb->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) == USB_OTG_GAHBCFG_DMAEN)
            && (hhcd->channel[ch_num].core_ch.xfer_length > 0U))
        {
          num_packets = (hhcd->channel[ch_num].core_ch.xfer_length + hhcd->channel[ch_num].core_ch.max_packet - 1U) \
                        / hhcd->channel[ch_num].core_ch.max_packet;

          if ((num_packets & 1U) != 0U)
          {
            hhcd->channel[ch_num].toggle_out ^= 1U;
          }
        }
      }
    }
    else if (hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_ACK)
    {
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;

      if (hhcd->channel[ch_num].core_ch.do_csplit == 1U)
      {
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;
      }
    }
    else if (hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_NAK)
    {
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;
      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;

      if (hhcd->channel[ch_num].core_ch.do_csplit == 1U)
      {
        hhcd->channel[ch_num].core_ch.do_csplit = 0U;
        USB_OTG_CHANNEL_CLEAR_CSPLT(hhcd->instance, ch_num);
      }
    }
    else if (hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_NYET)
    {
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;
      hhcd->channel[ch_num].urb_state  = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;
    }
    else if (hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_STALL)
    {
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;
      hhcd->channel[ch_num].urb_state  = HAL_HCD_CHANNEL_URB_STATE_STALL;
    }
    else if ((hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_XACTERR)
             || (hhcd->channel[ch_num].state == HAL_HCD_CHANNEL_STATE_DATATGLERR))
    {
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;
      hhcd->channel[ch_num].err_cnt++;
      if (hhcd->channel[ch_num].err_cnt > 2U)
      {
        hhcd->channel[ch_num].err_cnt = 0U;
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_ERROR;
      }
      else
      {
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;

        /* Re-activate the channel  */
        hcchar_reg = USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR;
        hcchar_reg &= ~USB_OTG_HCCHAR_CHDIS;
        hcchar_reg |= USB_OTG_HCCHAR_CHENA;
        USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR = hcchar_reg;
      }
    }
    else
    {
      return;
    }

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
    HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
  }
  else
  {
    return;
  }
}

/**
  * @brief  Handle Rx Queue Level interrupt requests.
  * @param  hhcd HCD handle
  */
static void HCD_OTG_RXQLVL_IRQHandler(hal_hcd_handle_t *hhcd)
{
  const usb_otg_global_t *p_usb;
  uint32_t pktsts;
  uint32_t pktcnt;
  uint32_t xfer_size_pktcnt;
  uint32_t grxstsp_reg;
  uint32_t hcchar_reg;
  uint32_t ch_num;

  p_usb = USB_OTG_GET_INSTANCE((uint32_t)hhcd->instance);

  grxstsp_reg = p_usb->GRXSTSP;
  ch_num = grxstsp_reg & USB_OTG_GRXSTSP_EPNUM;
  pktsts = (grxstsp_reg & USB_OTG_GRXSTSP_PKTSTS) >> 17;
  pktcnt = (grxstsp_reg & USB_OTG_GRXSTSP_BCNT) >> 4;

  if (ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB)
  {
    return;
  }

  switch (pktsts)
  {
    case USB_OTG_GRXSTS_PKTSTS_IN:
      /* Read the data into the host buffer. */
      if ((pktcnt > 0U) && (hhcd->channel[ch_num].core_ch.p_xfer_buffer != (void *)0))
      {
        if ((hhcd->channel[ch_num].core_ch.xfer_count + pktcnt) <= hhcd->channel[ch_num].core_ch.xfer_length)
        {
          (void)USB_OTG_ReadPacket((uint32_t)hhcd->instance,
                                   hhcd->channel[ch_num].core_ch.p_xfer_buffer, (uint8_t)ch_num, (uint16_t)pktcnt);

          /* Manage multiple Xfer */
          hhcd->channel[ch_num].core_ch.p_xfer_buffer += pktcnt;
          hhcd->channel[ch_num].core_ch.xfer_count += pktcnt;

          /* Get transfer size packet count */
          xfer_size_pktcnt = (USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCTSIZ & USB_OTG_HCTSIZ_PKTCNT) >> 19;

          if ((hhcd->channel[ch_num].core_ch.max_packet == pktcnt) && (xfer_size_pktcnt > 0U))
          {
            /* Re-activate the channel when more packets are expected */
            hcchar_reg = USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR;
            hcchar_reg &= ~USB_OTG_HCCHAR_CHDIS;
            hcchar_reg |= USB_OTG_HCCHAR_CHENA;
            USB_OTG_CHANNEL(hhcd->instance, ch_num)->HCCHAR = hcchar_reg;
            hhcd->channel[ch_num].toggle_in ^= 1U;
          }
        }
        else
        {
          hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_ERROR;
        }
      }
      break;

    case USB_OTG_GRXSTS_PKTSTS_DATA_TOGGLE_ERR:
      break;

    case USB_OTG_GRXSTS_PKTSTS_IN_XFER_COMP:
    case USB_OTG_GRXSTS_PKTSTS_CH_HALTED:
    default:
      break;
  }
}

/**
  * @brief  Handle Host Port interrupt requests.
  * @param  hhcd HCD handle
  */
static void HCD_OTG_Port_IRQHandler(hal_hcd_handle_t *hhcd)
{
  const usb_otg_global_t *p_usb;
  __IO uint32_t hprt0;
  __IO uint32_t hprt0_dup;

  p_usb = USB_OTG_GET_INSTANCE((uint32_t)hhcd->instance);

  /* Handle Host Port Interrupts */
  hprt0 = USB_OTG_HPRT0(hhcd->instance);
  hprt0_dup = USB_OTG_HPRT0(hhcd->instance);

  hprt0_dup &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET | \
                 USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG);

  /* Check whether Port Connect detected */
  if ((hprt0 & USB_OTG_HPRT_PCDET) == USB_OTG_HPRT_PCDET)
  {
    if ((hprt0 & USB_OTG_HPRT_PCSTS) == USB_OTG_HPRT_PCSTS)
    {
      /* Update Host port state */
      hhcd->port_state = HAL_HCD_PORT_STATE_DEV_CONNECT;

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_port_connect_cb(hhcd);
#else
      HAL_HCD_PortConnectCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
    }
    hprt0_dup |= USB_OTG_HPRT_PCDET;
  }

  /* Check whether Port Enable Changed */
  if ((hprt0 & USB_OTG_HPRT_PENCHNG) == USB_OTG_HPRT_PENCHNG)
  {
    hprt0_dup |= USB_OTG_HPRT_PENCHNG;

    if ((hprt0 & USB_OTG_HPRT_PENA) == USB_OTG_HPRT_PENA)
    {
      if ((p_usb->GUSBCFG & USB_OTG_GUSBCFG_PHYSEL) == USB_OTG_GUSBCFG_PHYSEL)
      {
        if ((hprt0 & USB_OTG_HPRT_PSPD) == ((uint32_t)HAL_HCD_PORT_SPEED_LS << 17))
        {
          (void)USB_OTG_InitFSLSPClkSel((uint32_t)hhcd->instance, (uint8_t)USB_OTG_HCFG_6_MHZ);
        }
        else
        {
          (void)USB_OTG_InitFSLSPClkSel((uint32_t)hhcd->instance, (uint8_t)USB_OTG_HCFG_48_MHZ);
        }
      }
      else
      {
        if ((USB_OTG_HOST(hhcd->instance)->HCFG & USB_OTG_HCFG_FSLSS) == USB_OTG_HCFG_FSLSS)
        {
          USB_OTG_HOST(hhcd->instance)->HFIR = (__IO uint32_t)USB_OTG_HFIR_60_MHZ;
        }
      }
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_port_enable_cb(hhcd);
#else
      HAL_HCD_PortEnabledCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

    }
    else
    {
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_port_disable_cb(hhcd);
#else
      HAL_HCD_PortDisabledCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
    }
  }

  /* Check for an overcurrent */
  if ((hprt0 & USB_OTG_HPRT_POCCHNG) == USB_OTG_HPRT_POCCHNG)
  {
    hprt0_dup |= USB_OTG_HPRT_POCCHNG;
  }

  /* Clear Port Interrupts */
  USB_OTG_HPRT0(hhcd->instance) = hprt0_dup;
}


#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */
#if defined (USB_DRD_FS)

/**
  * @brief  Close host channel
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval HAL status
  */
hal_status_t HAL_HCD_CloseChannel(hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (hhcd->driver.host_channel_close((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch) != USB_CORE_OK)
  {
    return HAL_ERROR;
  }

  hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;

  return HAL_OK;
}

/**
  * @brief  Handle HCD interrupt request.
  * @param  hhcd HCD handle
  */
void HAL_HCD_DRD_IRQHandler(hal_hcd_handle_t *hhcd)
{
  usb_drd_global_t *p_usb;
  uint32_t wIstr;
  uint32_t ch_dir;
  uint32_t phy_ch_num;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  wIstr = USB_DRD_ReadInterrupts((uint32_t)hhcd->instance);
  p_usb = USB_DRD_GET_INSTANCE((uint32_t)hhcd->instance);

  /* Port Change Detected (Connection/Disconnection) */
  if ((wIstr & USB_ISTR_DCON) == USB_ISTR_DCON)
  {
    /* Clear Flag */
    USB_DRD_ClearInterrupts((uint32_t)hhcd->instance, USB_ISTR_DCON);

    /* Call Port IRQHandler */
    HCD_DRD_Port_IRQHandler(hhcd);

    return;
  }

  /* Correct Transaction Detected -------*/
  if ((wIstr & USB_ISTR_CTR) == USB_ISTR_CTR)
  {
    /* Get Physical channel */
    phy_ch_num = USB_DRD_GET_CHNUM(p_usb);

    /* Get channel direction */
    ch_dir = USB_DRD_GET_CHDIR(p_usb);

    if (ch_dir == (uint32_t)USB_CORE_CH_OUT_DIR)
    {
      /* Call Channel_OUT_IRQ() */
      HCD_DRD_CHANNEL_OUT_IRQHandler(hhcd, (usb_core_phy_chep_t)phy_ch_num);
    }
    else
    {
      /* Call Channel_IN_IRQ() */
      HCD_DRD_CHANNEL_IN_IRQHandler(hhcd, (usb_core_phy_chep_t)phy_ch_num);
    }

    return;
  }

  /* Wakeup Flag Detected */
  if ((wIstr & USB_ISTR_WKUP) == USB_ISTR_WKUP)
  {
    if (hhcd->port_state == HAL_HCD_PORT_STATE_DEV_SUSPEND)
    {
      /* Set The L2Resume bit */
      p_usb->CNTR |= USB_CNTR_L2RES;

      /* Clear the wake-up flag */
      USB_DRD_ClearInterrupts((uint32_t)hhcd->instance, USB_ISTR_WKUP);

      /* Update the USB Software state machine */
      HAL_HCD_PortResumeCallback(hhcd);
      hhcd->port_state = HAL_HCD_PORT_STATE_DEV_RESUME;
    }
    else
    {
      /* Clear the wake-up flag */
      USB_DRD_ClearInterrupts((uint32_t)hhcd->instance, USB_ISTR_WKUP);
    }

    return;
  }

  /* Global Error Flag Detected */
  if ((wIstr & USB_ISTR_ERR) == USB_ISTR_ERR)
  {
    USB_DRD_ClearInterrupts((uint32_t)hhcd->instance, USB_ISTR_ERR);

    return;
  }

  /* PMA Overrun detected */
  if ((wIstr & USB_ISTR_PMAOVR) == USB_ISTR_PMAOVR)
  {
    USB_DRD_ClearInterrupts((uint32_t)hhcd->instance, USB_ISTR_PMAOVR);

    return;
  }

  /* Suspend Detected */
  if ((wIstr & USB_ISTR_SUSP) == USB_ISTR_SUSP)
  {
    /* Set HAL Port State to Suspend */
    hhcd->port_state = HAL_HCD_PORT_STATE_DEV_SUSPEND;

    /* Force low-power mode in the macrocell */
    p_usb->CNTR |= USB_CNTR_SUSPEN;

    /* Clear of the ISTR bit must be done after setting of CNTR_FSUSP */
    USB_DRD_ClearInterrupts((uint32_t)hhcd->instance, USB_ISTR_SUSP);

    /* Call suspend Callback */
    HAL_HCD_PortSuspendCallback(hhcd);

    return;
  }

  /* Start Of Frame Detected */
  if ((wIstr & USB_ISTR_SOF) == USB_ISTR_SOF)
  {
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->p_sof_cb(hhcd);
#else
    HAL_HCD_SofCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

    USB_DRD_ClearInterrupts((uint32_t)hhcd->instance, USB_ISTR_SOF);

    /* First SOF detected after USB_RESET, set port state to run */
    if (hhcd->port_state == HAL_HCD_PORT_STATE_DEV_RESET)
    {
      /* HAL State */
      hhcd->port_state = HAL_HCD_PORT_STATE_DEV_RUN;

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_port_enable_cb(hhcd);
#else
      HAL_HCD_PortEnabledCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
    }

    return;
  }
}

#if defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1)
/**
  * @brief  Handle Host Channel OUT Double Buffer Bulk requests.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number This parameter can be a value from 1 to 15
  * @param  phy_ch_num Physical Channel number [0..7]
  * @param  reg_value contain Snapshot of the EPCHn register when ISR is detected
  */
static void HCD_DRD_CHANNEL_OUT_BulkDb(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num,
                                       usb_core_phy_chep_t phy_ch_num, uint32_t reg_value)
{
  uint16_t data_xfr;
  uint16_t len;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

  /* Send Buffer0 */
  if ((reg_value & USB_CH_DTOG_TX) != 0U)
  {
    data_xfr = (uint16_t)(((USB_DRD_PMA_BUFF + (uint32_t)phy_ch_num)->TXBD & 0x03FF0000U) >> 16U);

    if (hhcd->channel[ch_num].core_ch.xfer_length >= data_xfr)
    {
      hhcd->channel[ch_num].core_ch.xfer_length -= data_xfr;
    }
    else
    {
      hhcd->channel[ch_num].core_ch.xfer_length = 0U;
    }

    /* Transfer not yet finished only one packet of mps is transferred and ACKed from device */
    if (hhcd->channel[ch_num].core_ch.xfer_length != 0U)
    {
      /* Manage multiple Xfer */
      hhcd->channel[ch_num].core_ch.xfer_count += data_xfr;

      /* Check if we need to free user buffer */
      if ((reg_value & USB_CH_DTOG_RX) != 0U)
      {
        /* Toggle SwBuff */
        HCD_CLEAR_TX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
        HCD_CLEAR_RX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
        HCD_TX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
      }

      /* hhcd->channel[ch_num&0xFU].xfer_size==0 ==> when all data are written in the PMA to yet transferred */
      if (hhcd->channel[ch_num].core_ch.xfer_size > 0U) /* Still data to fill in the buffer */
      {
        hhcd->channel[ch_num].core_ch.p_xfer_buffer += data_xfr;

        /* Calculate len of new buffer to fill */
        if (hhcd->channel[ch_num].core_ch.xfer_size > hhcd->channel[ch_num].core_ch.max_packet)
        {
          len = (uint16_t)hhcd->channel[ch_num].core_ch.max_packet;
          hhcd->channel[ch_num].core_ch.xfer_size -= len;
        }
        else
        {
          len = (uint16_t)hhcd->channel[ch_num].core_ch.xfer_size;
          hhcd->channel[ch_num].core_ch.xfer_size = 0U; /* end of fill buffer */
        }

        /* Write remaining data to Buffer0 */
        HCD_SET_CH_DBUF0_CNT((uint32_t)hhcd->instance, phy_ch_num, USB_CORE_EP_IN_DIR, (uint16_t)len);
        USB_DRD_WritePMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                         hhcd->channel[ch_num].core_ch.pma_addr0, (uint16_t)len);
      }
      /* Start a new transfer */
      HCD_SET_CH_TX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_TX_VALID);
    }
    else
    {
      /* Transfer complete state */
      hhcd->channel[ch_num].core_ch.xfer_count += data_xfr;
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XFRC;
      hhcd->channel[ch_num].urb_state  = HAL_HCD_CHANNEL_URB_STATE_DONE;
      hhcd->channel[ch_num].toggle_out ^= 1U;
      /* Close the Channel */
      HCD_SET_CH_TX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_TX_DIS);
    }
  }
  else
  {
    /* Send Buffer1 */
    data_xfr = (uint16_t)(((USB_DRD_PMA_BUFF + (uint32_t)phy_ch_num)->RXBD & 0x03FF0000U) >> 16U);

    if (hhcd->channel[ch_num].core_ch.xfer_length >= data_xfr) /* updated */
    {
      hhcd->channel[ch_num].core_ch.xfer_length -= data_xfr;
    }

    /* Transfer not yet finished only one packet of mps is transferred and ACKed from device */
    if (hhcd->channel[ch_num].core_ch.xfer_length != 0U)
    {
      /* Manage multiple Xfer */
      hhcd->channel[ch_num].core_ch.xfer_count += data_xfr;

      /* Check if we need to free user buffer */
      if ((reg_value & USB_CH_DTOG_RX) == 0U)
      {
        /* Toggle SwBuff */
        HCD_CLEAR_TX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
        HCD_CLEAR_RX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
        HCD_RX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
      }

      if (hhcd->channel[ch_num].core_ch.xfer_size > 0U) /* Still data to fill in the buffer */
      {
        hhcd->channel[ch_num].core_ch.p_xfer_buffer += data_xfr;

        /* Calculate length of new buffer to fill */
        if (hhcd->channel[ch_num].core_ch.xfer_size > hhcd->channel[ch_num].core_ch.max_packet)
        {
          len = hhcd->channel[ch_num].core_ch.max_packet;
          hhcd->channel[ch_num].core_ch.xfer_size -= len;
        }
        else
        {
          len = (uint16_t)hhcd->channel[ch_num].core_ch.xfer_size;
          hhcd->channel[ch_num].core_ch.xfer_size = 0U; /* end of fill buffer */
        }

        /* Write remaining data to Buffer0 */
        HCD_SET_CH_DBUF1_CNT((uint32_t)hhcd->instance, phy_ch_num, USB_CORE_EP_IN_DIR, (uint16_t)len);

        USB_DRD_WritePMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                         hhcd->channel[ch_num].core_ch.pma_addr1, (uint16_t)len);
      }

      /* Start a new transfer */
      HCD_SET_CH_TX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_TX_VALID);
    }
    else
    {
      /* Transfer complete state */
      hhcd->channel[ch_num].core_ch.xfer_count += data_xfr;
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XFRC;
      hhcd->channel[ch_num].urb_state  = HAL_HCD_CHANNEL_URB_STATE_DONE;
      hhcd->channel[ch_num].toggle_out ^= 1U;

      /* Close the channel */
      HCD_SET_CH_TX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_TX_DIS);
    }
  }
}


/**
  * @brief  Handle Host Channel IN Double Buffer Bulk requests.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number: This parameter can be a value from 1 to 15
  * @param  phy_ch_num Physical Channel number [0..7]
  * @param  reg_value contain Snapshot of the EPCHn register when ISR is detected
  */
static void HCD_DRD_CHANNEL_IN_BulkDb(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num,
                                      usb_core_phy_chep_t phy_ch_num, uint32_t reg_value)
{
  uint16_t received_bytes;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

  /* Read from Buffer 0 */
  if ((reg_value & USB_CH_DTOG_RX) != 0U)
  {
    received_bytes = (uint16_t)HCD_GET_CH_DBUF0_CNT((uint32_t)hhcd->instance, phy_ch_num);

    if (hhcd->channel[ch_num].core_ch.xfer_length <= received_bytes)
    {
      hhcd->channel[ch_num].core_ch.xfer_length = 0U;
    }
    else
    {
      hhcd->channel[ch_num].core_ch.xfer_length -= received_bytes;
    }

    /* Check if we Need to free the other buffer for the IP */
    if ((hhcd->channel[ch_num].core_ch.xfer_length != 0U) && ((reg_value & USB_CH_DTOG_TX) != 0U))
    {
      /* Toggle SwBuff */
      USB_DRD_TX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
    }

    /* Read the byte from PMA to user Buffer(System Memory) */
    USB_DRD_ReadPMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                    hhcd->channel[ch_num].core_ch.pma_addr0, (uint16_t)received_bytes);
  }
  else
  {
    /* Read from Buffer 1 */
    received_bytes = (uint16_t) HCD_GET_CH_DBUF1_CNT((uint32_t)hhcd->instance, phy_ch_num);

    if (hhcd->channel[ch_num].core_ch.xfer_length <= received_bytes)
    {
      hhcd->channel[ch_num].core_ch.xfer_length = 0U;
    }
    else
    {
      hhcd->channel[ch_num].core_ch.xfer_length -= received_bytes;
    }

    /* Check if we Need to free the other buffer for the IP */
    if ((hhcd->channel[ch_num].core_ch.xfer_length != 0U) && ((reg_value & USB_CH_DTOG_TX) == 0U))
    {
      /* Toggle SwBuff */
      USB_DRD_TX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
    }

    /* Read the byte from PMA to user Buffer(System Memory) */
    USB_DRD_ReadPMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                    hhcd->channel[ch_num].core_ch.pma_addr1, (uint16_t)received_bytes);
  }

  /* Update the global number of all received bytes */
  hhcd->channel[ch_num].core_ch.xfer_count += received_bytes;

  /* Transfer complete state */
  hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_ACK;
  hhcd->channel[ch_num].err_cnt = 0U;

  if ((hhcd->channel[ch_num].core_ch.xfer_length == 0U)
      || ((received_bytes < hhcd->channel[ch_num].core_ch.max_packet)))
  {
    hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;
    hhcd->channel[ch_num].state  = HAL_HCD_CHANNEL_STATE_XFRC;

    /* disable channel */
    HCD_SET_CH_RX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_RX_DIS);
  }
  else
  {
    hhcd->channel[ch_num].core_ch.p_xfer_buffer += received_bytes;

    /* Reactivate the Channel Submit an other URB since the Transfer is not yet completed */
    HCD_SET_CH_RX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_RX_STRX);
  }
}
#endif /* defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1) */

#if defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1)
/**
  * @brief  Handle Host Channel IN Isochronous Transaction
  * @param  hhcd HCD handle
  * @param  ch_num Channel number: This parameter can be a value from 1 to 15
  * @param  phy_ch_num Physical Channel number [0..7]
  * @param  reg_value contain Snapshot of the EPCHn register when ISR is detected
  */
static void HCD_DRD_CHANNEL_IN_IsocDb(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num,
                                      usb_core_phy_chep_t phy_ch_num, uint32_t reg_value)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

  /* Check if Double buffer isochronous */
  if ((reg_value & USB_CH_KIND) != 0U)
  {
    /* Get Data IN Packet */
    hhcd->channel[ch_num].core_ch.xfer_count = HCD_GET_CH_RX_CNT((uint32_t)hhcd->instance, phy_ch_num);

    if (hhcd->channel[ch_num].core_ch.xfer_count != 0U)
    {
      USB_DRD_ReadPMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                      hhcd->channel[ch_num].core_ch.pma_address,
                      (uint16_t)hhcd->channel[ch_num].core_ch.xfer_count);

      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;
    }
  }
#if defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1)
  else  /* double buffer isochronous */
  {
    /* Read from Buffer0 */
    if ((reg_value & USB_CH_DTOG_RX) != 0U)
    {
      /* Get number of Received byte in buffer0 */
      hhcd->channel[ch_num].core_ch.xfer_count = HCD_GET_CH_DBUF0_CNT((uint32_t)hhcd->instance, phy_ch_num);

      if (hhcd->channel[ch_num].core_ch.xfer_count != 0U)
      {
        /* Read from Buffer0 */
        USB_DRD_ReadPMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                        hhcd->channel[ch_num].core_ch.pma_addr0,
                        (uint16_t)hhcd->channel[ch_num].core_ch.xfer_count);

        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;
      }
    }
    else
    {
      /* Get number of Received byte in buffer1 */
      hhcd->channel[ch_num].core_ch.xfer_count = HCD_GET_CH_DBUF1_CNT((uint32_t)hhcd->instance, phy_ch_num);

      if (hhcd->channel[ch_num].core_ch.xfer_count != 0U)
      {
        /* Read from Buffer1 */
        USB_DRD_ReadPMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                        hhcd->channel[ch_num].core_ch.pma_addr1,
                        (uint16_t)hhcd->channel[ch_num].core_ch.xfer_count);

        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;
      }
    }
  }
#endif /* defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1) */

  /* Transfer complete state */
  hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XFRC;

  /* Clear VTRX */
  HCD_CLEAR_RX_CH_CTR((uint32_t)hhcd->instance, phy_ch_num);
}
#endif /* defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1) */

/**
  * @brief  Handle Host Channel IN interrupt requests.
  * @param  hhcd HCD handle
  * @param  phy_ch_num Channel number
  *         This parameter can be a value from 1 to 8
  */
static void HCD_DRD_CHANNEL_IN_IRQHandler(hal_hcd_handle_t *hhcd, usb_core_phy_chep_t phy_ch_num)
{
  uint16_t received_bytes;
  usb_core_channel_t ch_num = USB_DRD_GetLogicalChannel(phy_ch_num, USB_CORE_CH_IN_DIR);

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB)
  {
    return;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Take a Flag snapshot from the CHEP register, due to STRX bits are used for both control and status */
  uint32_t ch_reg = HCD_GET_CHANNEL((uint32_t)hhcd->instance, phy_ch_num);

  /* Manage Correct Transaction */
  if ((ch_reg & USB_CH_ERRRX) == 0U)
  {
    /* Manage all Non Isochronous Transaction */
    if ((ch_reg & USB_CH_UTYPE) != USB_EP_ISOCHRONOUS)
    {
      /* manage ACK response single buffer */
      if (((ch_reg) & USB_CH_RX_STRX) == USB_CH_RX_ACK_SBUF)
      {
        /* Get Control Data OUT Packet */
        received_bytes = (uint16_t)HCD_GET_CH_RX_CNT((uint32_t)hhcd->instance, phy_ch_num);

        /* Read the byte from PMA to user Buffer(System Memory) */
        USB_DRD_ReadPMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                        hhcd->channel[ch_num].core_ch.pma_address, (uint16_t)received_bytes);

        /* update the global number of all received bytes */
        hhcd->channel[ch_num].core_ch.xfer_count += received_bytes;

        /* Transfer complete state */
        hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_ACK;
        hhcd->channel[ch_num].err_cnt = 0U;

        if (hhcd->channel[ch_num].core_ch.xfer_length <= received_bytes)
        {
          hhcd->channel[ch_num].core_ch.xfer_length = 0U;
        }
        else
        {
          hhcd->channel[ch_num].core_ch.xfer_length -= received_bytes;
        }

        if ((hhcd->channel[ch_num].core_ch.xfer_length == 0U)
            || ((received_bytes < hhcd->channel[ch_num].core_ch.max_packet)))
        {
          hhcd->channel[ch_num].urb_state  = HAL_HCD_CHANNEL_URB_STATE_DONE;
          hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XFRC;
        }
        else
        {
          hhcd->channel[ch_num].core_ch.p_xfer_buffer += received_bytes;

          /* Reactivate the Channel to Submit another URB since the Transfer is not yet completed */
          HCD_SET_CH_RX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_RX_STRX);
        }

        if ((hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_BULK)
            || (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_INTR))
        {
          hhcd->channel[ch_num].toggle_in ^= 1U;
        }
      }
      /* Manage NACK Response */
      else if (((ch_reg & USB_CH_RX_STRX) == USB_CH_RX_NAK)
               && (hhcd->channel[ch_num].urb_state != HAL_HCD_CHANNEL_URB_STATE_DONE))
      {
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;
        hhcd->channel[ch_num].err_cnt = 0U;
        hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_NAK;

        if (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_INTR)
        {
          /* Close the channel */
          HCD_SET_CH_RX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_RX_DIS);
        }
      }
      /* Manage STALL Response */
      else if ((ch_reg & USB_CH_RX_STRX) == USB_CH_RX_STALL)
      {
        (void)HAL_HCD_HaltChannel(hhcd, (hal_hcd_channel_t)ch_num);
        hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_STALL;
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_STALL;

        /* Close the channel */
        HCD_SET_CH_RX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_RX_DIS);
      }
#if defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1)
      /* Double Buffer Management in case of Bulk Transaction */
      else  if (((ch_reg & USB_CH_RX_STRX) == USB_CH_RX_ACK_DBUF) && ((ch_reg & USB_CH_KIND) != 0U))
      {
        /* Bulk IN Double Buffer ISR */
        HCD_DRD_CHANNEL_IN_BulkDb(hhcd, ch_num, phy_ch_num, ch_reg);
      }
#endif /* defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1) */
      else
      {
        /*....*/
        /* Not defined state: STRX=11 in single buffer no iso is not defined */
      }

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
      HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

      /* Clear VTRX */
      HCD_CLEAR_RX_CH_CTR((uint32_t)hhcd->instance, phy_ch_num);
    }
#if defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1)
    /* Isochronous Channel */
    else
    {
      HCD_DRD_CHANNEL_IN_IsocDb(hhcd, ch_num, phy_ch_num, ch_reg);
    }
#endif /* defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1) */
  }
  else /* Error detected during last transaction */
  {
    /* Set URB Error State */
    hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;
    hhcd->channel[ch_num].err_cnt++;
    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XACTERR;

    /* Clear VTTRX & ERR_RX */
    HCD_CLEAR_RX_CH_ERR((uint32_t)hhcd->instance, phy_ch_num);

    /* Check Error number */
    if (hhcd->channel[ch_num].err_cnt > 3U)
    {
      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_ERROR;
      HCD_SET_CH_RX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_RX_DIS);

      /* Clear pending err_tx */
      HCD_CLEAR_RX_CH_ERR((uint32_t)hhcd->instance, phy_ch_num);
    }

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
    HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
  }
}


/**
  * @brief  Handle Host Channel OUT interrupt requests.
  * @param  hhcd  HCD handle
  * @param  phy_ch_num Channel number
  *         This parameter can be a value from 1 to 8
  */
static void HCD_DRD_CHANNEL_OUT_IRQHandler(hal_hcd_handle_t *hhcd, usb_core_phy_chep_t phy_ch_num)
{
  const usb_drd_global_t *p_usb;
  __IO uint32_t get_ch_reg;
  uint16_t data_xfr;
  usb_core_channel_t ch_num = USB_DRD_GetLogicalChannel(phy_ch_num, USB_CORE_CH_OUT_DIR);

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

  if ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB)
  {
    return;
  }

  p_usb = USB_DRD_GET_INSTANCE((uint32_t)hhcd->instance);

  /* Take a Flag snapshot from the CHEP register, due to STRX bits are used for both control & status */
  uint32_t ch_reg = *(__IO uint32_t *)((__IO uint32_t)(&(p_usb->CHEP0R) + (uint32_t)phy_ch_num));

  /*------ Manage Correct Transaction ------*/
  if ((ch_reg & USB_CH_ERRTX) == 0U)
  {
    /* Manage all Non Isochronous Transaction */
    if ((ch_reg & USB_CH_UTYPE) != USB_EP_ISOCHRONOUS)
    {
      /* Check ACK response */
      if ((ch_reg & USB_CH_TX_STTX) == USB_CH_TX_ACK_SBUF)
      {
        data_xfr = (uint16_t)(((USB_DRD_PMA_BUFF + (uint32_t)phy_ch_num)->TXBD & 0x03FF0000U) >> 16U);

        if (hhcd->channel[ch_num].core_ch.xfer_length >= data_xfr)
        {
          hhcd->channel[ch_num].core_ch.xfer_length -= data_xfr;
        }
        else
        {
          hhcd->channel[ch_num].core_ch.xfer_length = 0U;
        }

        if ((hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_BULK)
            || (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_INTR))
        {
          hhcd->channel[ch_num].toggle_out ^= 1U;
        }

        /* Transfer no yet finished only one packet of mps is transferred and ACKed from device */
        if (hhcd->channel[ch_num].core_ch.xfer_length != 0U)
        {
          /* Manage multiple Xfer */
          hhcd->channel[ch_num].core_ch.p_xfer_buffer += data_xfr;
          hhcd->channel[ch_num].core_ch.xfer_count += data_xfr;

          /* Start a new transfer */
          (void)hhcd->driver.host_channel_start((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
        }
        else
        {
          /* Transfer complete */
          hhcd->channel[ch_num].core_ch.xfer_count += data_xfr;
          hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XFRC;
          hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;
        }
      }
      /* Check NACK Response */
      else if (((ch_reg & USB_CHEP_NAK) == USB_CHEP_NAK) || ((ch_reg & USB_CH_TX_STTX) == USB_CH_TX_NAK))
      {
        /* Update Channel status */
        hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_NAK;
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;
        hhcd->channel[ch_num].err_cnt = 0U;

        /* Get Channel register value */
        get_ch_reg = *(__IO uint32_t *)((__IO uint32_t)(&(p_usb->CHEP0R) + (uint32_t)phy_ch_num));

        /* Clear NAK status */
        get_ch_reg &= ~USB_CHEP_NAK & USB_CHEP_REG_MASK;

        /* Update channel register Value */
        HCD_SET_CHANNEL((uint32_t)hhcd->instance, phy_ch_num, get_ch_reg);

        if (hhcd->channel[ch_num].core_ch.double_buffer_en == 0U)
        {
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
          hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
          HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
        }
      }
      /* Check STALL Response */
      else if ((ch_reg & USB_CH_TX_STTX) == USB_CH_TX_STALL)
      {
        (void) HAL_HCD_HaltChannel(hhcd, (hal_hcd_channel_t)ch_num);
        hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_STALL;
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_STALL;
      }
#if defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1)
      /* Check double buffer ACK in case of bulk transaction */
      else if ((ch_reg & USB_CH_TX_STTX) == USB_CH_TX_ACK_DBUF)
      {
        /* Double buffer management Bulk Out */
        (void)HCD_DRD_CHANNEL_OUT_BulkDb(hhcd, ch_num, phy_ch_num, ch_reg);
      }
#endif /* defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1) */
      else
      {
        /*...*/
      }

      if ((ch_reg & USB_CH_TX_STTX) != USB_CH_TX_NAK)
      {
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
        hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
        HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
      }

      HCD_CLEAR_TX_CH_CTR((uint32_t)hhcd->instance, phy_ch_num);
    }
#if defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1)
    /* Handle Isochronous channel */
    else
    {
      /* Correct transaction */
      if ((p_usb->ISTR & USB_ISTR_ERR) == 0U)
      {
        /* Double buffer isochronous out */
        if ((ch_reg & USB_CH_KIND) != 0U)
        {
          HCD_SET_CH_TX_CNT((uint32_t)hhcd->instance, phy_ch_num, 0U);
        }
#if defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1)
        else /* Double buffer isochronous out */
        {
          /* Odd Transaction */
          if ((ch_reg & USB_CH_DTOG_TX) != 0U)
          {
            HCD_SET_CH_TX_CNT((uint32_t)hhcd->instance, phy_ch_num, 0U);
          }
          /* Even Transaction */
          else
          {
            HCD_SET_CH_RX_CNT((uint32_t)hhcd->instance, phy_ch_num, 0U);
          }

          USB_DRD_SET_CHEP_TX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_TX_DIS);
        }
#endif /* defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1) */

        /* Transfer complete state */
        hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XFRC;
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;
      }

      /* Clear Correct Transfer */
      HCD_CLEAR_TX_CH_CTR((uint32_t)hhcd->instance, phy_ch_num);

      /* TX COMPLETE */
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
      HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

    }
#endif /* defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1) */
  }
  /*------ Manage Transaction Error------*/
  else
  {
    hhcd->channel[ch_num].err_cnt++;
    if (hhcd->channel[ch_num].err_cnt > 3U)
    {
      HCD_SET_CH_TX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_TX_DIS);
      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_ERROR;
    }
    else
    {
      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;
    }

    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XACTERR;

    /* Clear ERR_TX */
    HCD_CLEAR_TX_CH_ERR((uint32_t)hhcd->instance, phy_ch_num);

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
    HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
  }
}


/**
  * @brief  Handle Host Port interrupt requests.
  * @param  hhcd  HCD handle
  */
static void HCD_DRD_Port_IRQHandler(hal_hcd_handle_t *hhcd)
{
  const usb_drd_global_t *p_usb;
  uint32_t FnrReg;
  uint32_t IstrReg;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  p_usb = USB_DRD_GET_INSTANCE((uint32_t)hhcd->instance);
  FnrReg = p_usb->FNR;
  IstrReg = p_usb->ISTR;

  /* SE0 detected USB Disconnected state */
  if ((FnrReg & (USB_FNR_RXDP | USB_FNR_RXDM)) == 0U)
  {
    /* Host Port State */
    hhcd->port_state = HAL_HCD_PORT_STATE_DEV_DISCONNECT;

    /* Clear all allocated virtual channel */
    (void)USB_DRD_ClearPhysicalChannels();

    /* Reset the PMA current pointer */
    (void)USB_DRD_PMAReset();

    /* Disconnection Callback */
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->p_port_disconnect_cb(hhcd);
#else
    HAL_HCD_PortDisconnectCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

    return;
  }

  if ((hhcd->port_state == HAL_HCD_PORT_STATE_DEV_DISCONNECT) != 0U)
  {
    /* J-state or K-state detected & LastState=Disconnected */
    if (((FnrReg & USB_FNR_RXDP) != 0U) || ((IstrReg & USB_ISTR_LS_DCONN) != 0U))
    {
      hhcd->port_state = HAL_HCD_PORT_STATE_DEV_CONNECT;

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_port_connect_cb(hhcd);
#else
      HAL_HCD_PortConnectCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
    }
  }
  else
  {
    /* J-state or K-state detected & lastState=Connected: a Missed disconnection is detected */
    if (((FnrReg & USB_FNR_RXDP) != 0U) || ((IstrReg & USB_ISTR_LS_DCONN) != 0U))
    {
      /* Host Port State */
      hhcd->port_state = HAL_HCD_PORT_STATE_DEV_DISCONNECT;

      /* Clear all allocated virtual channel */
      (void)USB_DRD_ClearPhysicalChannels();

      /* Reset the PMA current pointer */
      (void)USB_DRD_PMAReset();

      /* Disconnection Callback */
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_port_disconnect_cb(hhcd);
#else
      HAL_HCD_PortDisconnectCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
    }
  }
}
#endif /* defined (USB_DRD_FS) */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) || defined (USB_DRD_FS) */
#endif /* defined (USE_HAL_HCD_MODULE) && (USE_HAL_HCD_MODULE == 1) */

/**
  * @}
  */
