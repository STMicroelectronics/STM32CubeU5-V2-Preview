/**
  ******************************************************************************
  * @file    stm32u5xx_usb_otg_core.h
  * @brief   Header file of USB OTG Core Driver module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_USB_OTG_CORE_H
#define STM32U5xx_USB_OTG_CORE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"
#include "stm32u5xx_usb_core_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */
#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
/** @defgroup USB_OTG_CORE USB OTG CORE
  * @{
  */
/* Private constants ---------------------------------------------------------*/
/** @defgroup PCD_Private_Constants PCD Private Constants
  * @{
  */

/**
  * @brief  USB OTG Timeout
  */
#ifndef USB_OTG_TIMEOUT
#define USB_OTG_TIMEOUT                                              0x0F00000U
#endif /* define USB_OTG_TIMEOUT */

/**
  * @brief  USB OTG Current Mode Max Delay in ms
  */
#ifndef USB_OTG_CURRENT_MODE_MAX_DELAY_MS
#define USB_OTG_CURRENT_MODE_MAX_DELAY_MS                                  200U
#endif /* define USB_OTG_CURRENT_MODE_MAX_DELAY_MS */

/**
  * @brief  USB OTG core typedef definition
  */
typedef USB_OTG_GlobalTypeDef usb_otg_global_t;

/**
  * @brief  USB OTG Device typedef definition
  */
typedef USB_OTG_DeviceTypeDef usb_otg_device_t;

/**
  * @brief  USB OTG IN endpoint typedef definition
  */
typedef USB_OTG_INEndpointTypeDef usb_otg_in_endpoint_t;

/**
  * @brief  USB OTG OUT endpoint typedef definition
  */
typedef USB_OTG_OUTEndpointTypeDef usb_otg_out_endpoint_t;

/**
  * @brief  USB OTG Host typedef definition
  */
typedef USB_OTG_HostTypeDef usb_otg_host_t;

/**
  * @brief  USB OTG Host channel typedef definition
  */
typedef USB_OTG_HostChannelTypeDef usb_otg_host_channel_t;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PCD_Exported_Constants PCD Exported Constants
  * @{
  */
/**
  * @brief  USB_OTG_CORE VERSION ID 300A
  */
#define USB_OTG_CORE_ID_300A                                        0x4F54300AU

/**
  * @brief  USB_OTG_CORE VERSION ID 310A
  */
#define USB_OTG_CORE_ID_310A                                        0x4F54310AU

/**
  * @brief  USB OTG Core Speed HIGH
  */
#define USB_OTG_SPEED_HIGH                                                   0U

/**
  * @brief  USB OTG Core Speed HIGH IN FULL
  */
#define USB_OTG_SPEED_HIGH_IN_FULL                                           1U

/**
  * @brief  USB OTG Core Speed FULL
  */
#define USB_OTG_SPEED_FULL                                                   3U

/**
  * @brief  USB OTG HS Turnaround Timeout Value
  */
#ifndef USB_OTG_HS_TRDT_VALUE
#define USB_OTG_HS_TRDT_VALUE                                                9U
#endif /* USBD_HS_TRDT_VALUE */

/**
  * @brief  USB OTG FS Turnaround Timeout Value
  */
#ifndef USB_OTG_FS_TRDT_VALUE
#define USB_OTG_FS_TRDT_VALUE                                                5U
#endif /* USBD_HS_TRDT_VALUE */

/**
  * @brief  USB OTG Default Turnaround Timeout Value
  */
#define USB_OTG_DEFAULT_TRDT_VALUE                                           9U


/**
  * @brief  OTG USB HS PHY Frequency 30MHZ OR 60MHZ
  */
#define USB_OTG_DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ                    (0U << 1)

/**
  * @brief  OTG USB FS PHY Frequency 30MHZ OR 60MHZ
  */
#define USB_OTG_DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ                    (1U << 1)


/**
  * @brief  OTG USB FS PHY Frequency 48MHZ
  */
#define USB_OTG_DSTS_ENUMSPD_FS_PHY_48MHZ                             (3U << 1)

/**
  * @brief  OTG USB Endpoint Address mask
  */
#define USB_OTG_EP_ADDR_MSK                                                0xFU

/**
  * @brief  OTG USB clear interrupt mask
  */
#define USB_OTG_CLEAR_INTERRUPT_MASK                                0xFFFFFFFFU

/**
  * @brief  OTG USB channel max packet counter
  */
#define USB_OTG_CH_MAX_PKT_CNT                                             256U

/**
  * @brief  OTG USB Isochronous split MPS
  */
#define USB_OTG_ISO_SPLT_MPS                                               188U


/**
  * @brief  USB OTG Status Phase Received interrupt
  */
#ifndef USB_OTG_DOEPINT_OTEPSPR
#define USB_OTG_DOEPINT_OTEPSPR                (0x1UL << 5)      /*!< Status Phase Received interrupt */
#endif /* defined USB_OTG_DOEPINT_OTEPSPR */

/**
  * @brief  USB OTG Setup Packet Received interrupt mask
  */
#ifndef USB_OTG_DOEPMSK_OTEPSPRM
#define USB_OTG_DOEPMSK_OTEPSPRM               (0x1UL << 5)      /*!< Setup Packet Received interrupt mask */
#endif /* defined USB_OTG_DOEPMSK_OTEPSPRM */

/**
  * @brief  USB OTG NAK interrupt
  */
#ifndef USB_OTG_DOEPINT_NAK
#define USB_OTG_DOEPINT_NAK                    (0x1UL << 13)      /*!< NAK interrupt */
#endif /* defined USB_OTG_DOEPINT_NAK */

/**
  * @brief  USB OTG OUT Packet NAK interrupt mask
  */
#ifndef USB_OTG_DOEPMSK_NAKM
#define USB_OTG_DOEPMSK_NAKM                   (0x1UL << 13)      /*!< OUT Packet NAK interrupt mask */
#endif /* defined USB_OTG_DOEPMSK_NAKM */

/**
  * @brief  USB OTG Setup Packet Received interrupt
  */
#ifndef USB_OTG_DOEPINT_STPKTRX
#define USB_OTG_DOEPINT_STPKTRX                (0x1UL << 15)      /*!< Setup Packet Received interrupt */
#endif /* defined USB_OTG_DOEPINT_STPKTRX */

/**
  * @brief  USB OTG Setup Packet Received interrupt mask
  */
#ifndef USB_OTG_DOEPMSK_NYETM
#define USB_OTG_DOEPMSK_NYETM                  (0x1UL << 14)      /*!< Setup Packet Received interrupt mask */
#endif /* defined USB_OTG_DOEPMSK_NYETM */


/**
  * @brief  USB OTG Low Layer STS definition
  */
typedef enum
{
  USB_OTG_STS_GOUT_NAK   = 0x01U,
  USB_OTG_STS_DATA_UPDT  = 0x02U,
  USB_OTG_STS_XFER_COMP  = 0x03U,
  USB_OTG_STS_SETUP_COMP = 0x04U,
  USB_OTG_STS_SETUP_UPDT = 0x06U,
} usb_otg_sts_t;


/**
  * @brief  USB OTG Low Layer HCFG Speed definition
  */
typedef enum
{
  USB_OTG_HCFG_30_60_MHZ = 0x00U,
  USB_OTG_HCFG_48_MHZ    = 0x01U,
  USB_OTG_HCFG_6_MHZ     = 0x02U,
} usb_otg_hcfg_speed_t;


/**
  * @brief  USB OTG Low Layer Frame Interval definition
  */
typedef enum
{
  USB_OTG_HFIR_6_MHZ  = 6000U,
  USB_OTG_HFIR_60_MHZ = 60000U,
  USB_OTG_HFIR_48_MHZ = 48000U,
} usb_otg_frame_interval_t;


/**
  * @brief  USB OTG Low Layer Core Frame Interval definition
  */
typedef enum
{
  USB_OTG_DCFG_FRAME_INTERVAL_80 = 0x00U,
  USB_OTG_DCFG_FRAME_INTERVAL_85 = 0x01U,
  USB_OTG_DCFG_FRAME_INTERVAL_90 = 0x02U,
  USB_OTG_DCFG_FRAME_INTERVAL_95 = 0x03U,
} usb_otg_core_frame_interval_t;


/**
  * @brief  USB OTG Low Layer Received Packet Status structure definition
  */
typedef enum
{
  USB_OTG_GRXSTS_PKTSTS_IN              = 0x02U,
  USB_OTG_GRXSTS_PKTSTS_IN_XFER_COMP    = 0x03U,
  USB_OTG_GRXSTS_PKTSTS_DATA_TOGGLE_ERR = 0x05U,
  USB_OTG_GRXSTS_PKTSTS_CH_HALTED       = 0x07U,
} usb_otg_received_pkt_status_t;


/**
  * @brief  USB OTG Split OUT Transaction Position structure definition
  */
typedef enum
{
  USB_OTG_HCSPLT_BEGIN  = 0x01U,
  USB_OTG_HCSPLT_MIDDLE = 0x02U,
  USB_OTG_HCSPLT_END    = 0x03U,
  USB_OTG_HCSPLT_FULL   = 0x04U,
} usb_otg_split_out_xact_pos_t;


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup OTG_Exported_Macros OTG Exported Macros
  * @{
  */

/**
  * @brief  USB OTG GET Instance
  */
#define USB_OTG_GET_INSTANCE(instance)         ((usb_otg_global_t *)((uint32_t)instance))

/**
  * @brief  USB OTG Instance address in PCGCCTL register
  */
#define USB_OTG_PCGCCTL(instance)              *(__IO uint32_t *)((uint32_t)(instance) + USB_OTG_PCGCCTL_BASE)

/**
  * @brief  USB OTG Instance address in HPRT0 register
  */
#define USB_OTG_HPRT0(instance)                *(__IO uint32_t *)((uint32_t)(instance) + USB_OTG_HOST_PORT_BASE)

/**
  * @brief  USB OTG device instance
  */
#define USB_OTG_DEVICE(instance)               ((usb_otg_device_t *)((uint32_t)(instance) + USB_OTG_DEVICE_BASE))

/**
  * @brief  USB OTG host instance
  */
#define USB_OTG_HOST(instance)                 ((usb_otg_host_t *)((uint32_t)(instance) + USB_OTG_HOST_BASE))

/**
  * @brief  USB OTG IN endpoint address
  */
#define USB_OTG_IN_EP(instance, ep_index) \
  ((usb_otg_in_endpoint_t *)((uint32_t)(instance) + USB_OTG_IN_ENDPOINT_BASE + \
                             ((uint32_t)(ep_index) * USB_OTG_EP_REG_SIZE)))

/**
  * @brief  USB OTG OUT endpoint address
  */
#define USB_OTG_OUT_EP(instance, ep_index) \
  ((usb_otg_out_endpoint_t *)((uint32_t)(instance) + USB_OTG_OUT_ENDPOINT_BASE + \
                              ((uint32_t)(ep_index) * USB_OTG_EP_REG_SIZE)))

/**
  * @brief  USB OTG Data FIFO address
  */
#define USB_OTG_DFIFO(instance, fifo_index) \
  *(__IO uint32_t *)((uint32_t)(instance) + USB_OTG_FIFO_BASE + ((uint32_t)(fifo_index) * USB_OTG_FIFO_SIZE))

/**
  * @brief  USB OTG Channel address
  */
#define USB_OTG_CHANNEL(instance, ch_index) \
  ((usb_otg_host_channel_t *)((uint32_t)(instance) + USB_OTG_HOST_CHANNEL_BASE + \
                              ((uint32_t)(ch_index) * USB_OTG_HOST_CHANNEL_SIZE)))

/**
  * @brief  USB OTG UNGATE PHY Clock
  */
#define USB_OTG_UNGATE_PHYCLOCK(instance) \
  *(__IO uint32_t *)((uint32_t)(instance) + USB_OTG_PCGCCTL_BASE) &= ~(USB_OTG_PCGCCTL_STOPCLK)

/**
  * @brief  USB OTG GATE PHY Clock
  */
#define USB_OTG_GATE_PHYCLOCK(instance) \
  *(__IO uint32_t *)((uint32_t)(instance) + USB_OTG_PCGCCTL_BASE) |= USB_OTG_PCGCCTL_STOPCLK

/**
  * @brief  USB OTG Is PHY Suspende check
  */
#define USB_OTG_IS_PHY_SUSPENDED(instance) \
  ((*(__IO uint32_t *)((uint32_t)(instance) + USB_OTG_PCGCCTL_BASE)) & 0x10U)

/**
  * @brief  USB OTG Channel clear Interrupt
  */
#define USB_OTG_CHANNEL_CLEAR_IT(instance, ch_num, interrupt) \
  (USB_OTG_CHANNEL((instance), (ch_num))->HCINT = (interrupt))

/**
  * @brief  USB OTG Channel mask Halt Interrupt
  */
#define USB_OTG_CHANNEL_MASK_HALT_IT(instance, ch_num) \
  (USB_OTG_CHANNEL((instance), (ch_num))->HCINTMSK &= ~USB_OTG_HCINTMSK_CHHM)

/**
  * @brief  USB OTG Channel Unmask Halt Interrupt
  */
#define USB_OTG_CHANNEL_UNMASK_HALT_IT(instance, ch_num) \
  (USB_OTG_CHANNEL((instance), (ch_num))->HCINTMSK |= USB_OTG_HCINTMSK_CHHM)

/**
  * @brief  USB OTG Channel Mask Ack Interrupt
  */
#define USB_OTG_CHANNEL_MASK_ACK_IT(instance, ch_num) \
  (USB_OTG_CHANNEL((instance), (ch_num))->HCINTMSK &= ~USB_OTG_HCINTMSK_ACKM)

/**
  * @brief  USB OTG Channel Unmask Ack Interrupt
  */
#define USB_OTG_CHANNEL_UNMASK_ACK_IT(instance, ch_num) \
  (USB_OTG_CHANNEL((instance), (ch_num))->HCINTMSK |= USB_OTG_HCINTMSK_ACKM)

/**
  * @brief  USB OTG Channel Set CSPLT
  */
#define USB_OTG_CHANNEL_SET_CSPLT(instance, ch_num) \
  (USB_OTG_CHANNEL((instance), (ch_num))->HCSPLT |= USB_OTG_HCSPLT_COMPLSPLT)

/**
  * @brief  USB OTG Channel clear CSPLT
  */
#define USB_OTG_CHANNEL_CLEAR_CSPLT(instance, ch_num) \
  (USB_OTG_CHANNEL((instance), (ch_num))->HCSPLT &= ~USB_OTG_HCSPLT_COMPLSPLT)

/**
  * @brief  USB OTG Channel clear SSPLT
  */
#define USB_OTG_CHANNEL_CLEAR_SSPLT(instance, ch_num) \
  (USB_OTG_CHANNEL((instance), (ch_num))->HCSPLT &= ~USB_OTG_HCSPLT_SPLITEN)

/**
  * @brief  USB OTG mask interrupt
  */
#define USB_OTG_MASK_IT(instance, interrupt)                  ((instance)->GINTMSK &= ~(interrupt))

/**
  * @brief  USB OTG unmask interrupt
  */
#define USB_OTG_UNMASK_IT(instance, interrupt)                ((instance)->GINTMSK |= (interrupt))

/**
  * @brief  USB OTG IN Endpoint clear interrupt
  */
#define USB_OTG_IN_EP_CLEAR_IT(instance, ep_num, interrupt)   (USB_OTG_IN_EP(instance, ep_num)->DIEPINT = (interrupt))

/**
  * @brief  USB OTG OUT Endpoint clear interrupt
  */
#define USB_OTG_OUT_EP_CLEAR_IT(instance, ep_num, interrupt)  (USB_OTG_OUT_EP(instance, ep_num)->DOEPINT = (interrupt))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup USB_CORE_OTG_Exported_Functions USB CORE OTG Low Layer Exported Functions
  * @{
  */
usb_core_status_t USB_OTG_InitCore(uint32_t instance, const usb_core_config_params_t *p_core_config);
usb_core_status_t USB_OTG_DeInitCore(uint32_t instance);
usb_core_status_t USB_OTG_EnableGlobalInterrupt(uint32_t instance);
usb_core_status_t USB_OTG_DisableGlobalInterrupt(uint32_t instance);
usb_core_status_t USB_OTG_SetCurrentMode(uint32_t instance, usb_core_mode_t core_mode);
usb_core_mode_t USB_OTG_GetCurrentMode(uint32_t instance);
usb_core_status_t USB_OTG_FlushRxFifo(uint32_t instance);
usb_core_status_t USB_OTG_FlushTxFifo(uint32_t instance, uint32_t tx_fifo);
usb_core_status_t USB_OTG_WritePacket(uint32_t instance, const uint8_t *p_src, uint8_t ch_ep_num, uint32_t size_byte);
void    *USB_OTG_ReadPacket(uint32_t instance, uint8_t *p_dest, uint8_t ch_ep_num, uint32_t size_byte);
void     USB_OTG_ClearInterrupts(uint32_t instance, uint32_t interrupt);
uint32_t USB_OTG_ReadInterrupts(uint32_t instance);

usb_core_status_t USB_OTG_PCD_InitDriver(usb_core_pcd_driver_t *p_driver);
usb_core_status_t USB_OTG_InitDevice(uint32_t instance, const usb_core_config_params_t *p_core_config);
usb_core_status_t USB_OTG_StartDevice(uint32_t instance);
usb_core_status_t USB_OTG_StopDevice(uint32_t instance);
usb_core_status_t USB_OTG_ConnectDevice(uint32_t instance);
usb_core_status_t USB_OTG_DisconnectDevice(uint32_t instance);
usb_core_status_t USB_OTG_SetDeviceAddress(uint32_t instance, uint8_t address);
usb_core_status_t USB_OTG_SetDeviceSpeed(uint32_t instance, uint8_t speed);
usb_core_status_t USB_OTG_ActivateEndpoint(uint32_t instance, usb_core_ep_t *p_ep);
usb_core_status_t USB_OTG_DeactivateEndpoint(uint32_t instance, const usb_core_ep_t *p_ep);
usb_core_status_t USB_OTG_ActivateDedicatedEndpoint(uint32_t instance, usb_core_ep_t *p_ep);
usb_core_status_t USB_OTG_DeactivateDedicatedEndpoint(uint32_t instance, usb_core_ep_t *p_ep);
usb_core_status_t USB_OTG_SetEndpointStall(uint32_t instance, const usb_core_ep_t *p_ep);
usb_core_status_t USB_OTG_ClearEndpointStall(uint32_t instance, const usb_core_ep_t *p_ep);
usb_core_status_t USB_OTG_StartOutEP0(uint32_t instance, const uint8_t *p_setup);
usb_core_status_t USB_OTG_StartEndpointXfer(uint32_t instance, usb_core_ep_t *p_ep);
usb_core_status_t USB_OTG_StopEndpointXfer(uint32_t instance, const usb_core_ep_t *p_ep);
usb_core_status_t USB_OTG_ActivateSetup(uint32_t instance);
usb_core_status_t USB_OTG_SetTurnaroundTime(uint32_t instance, uint32_t hclk, usb_core_device_speed_t device_speed);
usb_core_status_t USB_OTG_SetTxFiFoSize(uint32_t instance, uint8_t fifo, uint16_t size_words);
usb_core_status_t USB_OTG_SetRxFiFoSize(uint32_t instance, uint16_t size_words);

usb_core_status_t USB_OTG_BCD_SetMode(uint32_t instance, usb_core_bcd_config_t bcd_config,
                                      usb_core_bcd_config_sts_t bcd_sts);
usb_core_bcd_port_status_t USB_OTG_BCD_PortTypeDetection(uint32_t instance, usb_core_bcd_detection_t detection);
usb_core_status_t USB_OTG_BCD_Activate(uint32_t instance);
usb_core_status_t USB_OTG_BCD_DeActivate(uint32_t instance);

usb_core_status_t USB_OTG_LPM_Activate(uint32_t instance);
usb_core_status_t USB_OTG_LPM_DeActivate(uint32_t instance);

usb_core_status_t USB_OTG_ActivateRemoteWakeup(uint32_t instance);
usb_core_status_t USB_OTG_DeActivateRemoteWakeup(uint32_t instance);
uint32_t USB_OTG_ReadDevAllOutEpInterrupt(uint32_t instance);
uint32_t USB_OTG_ReadDevOutEPInterrupt(uint32_t instance, uint8_t ep_num);
uint32_t USB_OTG_ReadDevAllInEpInterrupt(uint32_t instance);
uint32_t USB_OTG_ReadDevInEPInterrupt(uint32_t instance, uint8_t ep_num);
usb_core_device_speed_t USB_OTG_GetDeviceSpeed(uint32_t instance);

usb_core_status_t USB_OTG_HCD_InitDriver(usb_core_hcd_driver_t *p_driver);
usb_core_status_t USB_OTG_InitHost(uint32_t instance, const usb_core_config_params_t *p_core_config);
usb_core_status_t USB_OTG_StartHost(uint32_t instance);
usb_core_status_t USB_OTG_StopHost(uint32_t instance);
usb_core_status_t USB_OTG_InitFSLSPClkSel(uint32_t instance, uint8_t frequency);
usb_core_status_t USB_OTG_PortReset(uint32_t instance, usb_core_port_reset_sts_t reset_status);
usb_core_status_t USB_OTG_PortSuspend(uint32_t instance);
usb_core_status_t USB_OTG_PortResume(uint32_t instance, usb_core_port_resume_sts_t resume_status);
usb_core_status_t USB_OTG_PortPower(uint32_t instance, uint8_t state);
usb_core_status_t USB_OTG_DoPing(uint32_t instance, usb_core_channel_t ch_num);

usb_core_status_t USB_OTG_InitChannel(uint32_t instance, usb_core_ch_t *p_ch);
usb_core_status_t USB_OTG_StartChannelXfer(uint32_t instance, usb_core_ch_t *p_ch);
usb_core_status_t USB_OTG_HaltChannel(uint32_t instance, const usb_core_ch_t *p_ch);
uint32_t USB_OTG_ReadChannelInterrupts(uint32_t instance, usb_core_channel_t ch_num);
uint32_t USB_OTG_GetChannelInterrupt(uint32_t instance);

uint32_t USB_OTG_GetCurrentFrame(uint32_t instance);
uint32_t USB_OTG_GetDmaStatus(uint32_t instance);

usb_core_port_speed_t USB_OTG_GetHostPortSpeed(uint32_t instance);
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

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* STM32U5xx_USB_OTG_CORE_H */
