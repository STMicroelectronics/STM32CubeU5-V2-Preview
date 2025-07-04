/**
  ******************************************************************************
  * @file    stm32u5xx_usb_drd_core.h
  * @brief   Header file of USB DRD Core module.
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
#ifndef STM32U5xx_USB_DRD_CORE_H
#define STM32U5xx_USB_DRD_CORE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"
#include "stm32u5xx_usb_core_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */
#if defined (USB_DRD_FS)
/** @defgroup USB_DRD_CORE USB DRD CORE
  * @{
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup USB_DRD_Private_Constants USB DRD Private Constants
  * @{
  */
/**
  * @brief  USB DRD Timeout
  */
#ifndef USB_DRD_TIMEOUT
#define USB_DRD_TIMEOUT                                              0xF000000U
#endif /* define USB_DRD_TIMEOUT */


/**
  * @brief  USB DRD PMA Lookup Table: size depending on PMA Size
  *         8Bytes each Block 32Bit in each word
  */
#define PMA_BLOCKS                            ((USB_DRD_PMA_SIZE) / (8U * 32U))


/**
  * @brief  USB DRD First available address in PMA
  */
#define PMA_START_ADDR            (0x10U + (8U * (USB_DRD_USED_CHANNELS - 2U)))


/**
  * @brief  USB DRD Last available address in PMA
  */
#define PMA_END_ADDR                                           USB_DRD_PMA_SIZE


/**
  * @brief USB DRD MAX channels/endpoints
  */
#define USB_DRD_MAX_CHEP_NBR                                                 8U

/**
  * @brief USB DRD GET CHEP DBUF0 CNT
  */
#define USB_DRD_GET_CHEP_DBUF0_CNT                        USB_DRD_GET_CHEP_TX_CNT

/**
  * @brief  Gets buffer 1 address of a double buffer endpoint
  */
#define USB_DRD_GET_CHEP_DBUF1_CNT                        USB_DRD_GET_CHEP_RX_CNT

/**
  * @brief  Gets TX Endpoint address
  */
#define USB_DRD_GET_EP_TX_CNT                             USB_DRD_GET_CHEP_TX_CNT

/**
  * @brief  Gets TX Channel address
  */
#define USB_DRD_GET_CH_TX_CNT                             USB_DRD_GET_CHEP_TX_CNT

/**
  * @brief  Gets RX Endpoint address
  */
#define USB_DRD_GET_EP_RX_CNT                             USB_DRD_GET_CHEP_RX_CNT

/**
  * @brief USB DRD GET CHANNEL RX CNT
  */
#define USB_DRD_GET_CH_RX_CNT                             USB_DRD_GET_CHEP_RX_CNT

/**
  * @brief USB DRD CNTRX_NBLK Mask
  */
#define USB_CNTRX_NBLK_MSK                                         (0x1FUL << 26)

/**
  * @brief USB DRD CNTRX_BLSIZE Mask
  */
#define USB_CNTRX_BLSIZE                                            (0x1UL << 31)

/**
  * @brief PMA RX counter
  */
#ifndef PCD_RX_PMA_CNT
#define PCD_RX_PMA_CNT                                               10U
#endif /* PCD_RX_PMA_CNT */

/**
  * @brief Set ENDPOINT Register value
  */
#define PCD_SET_ENDPOINT                       USB_DRD_SET_CHEP

/**
  * @brief Get ENDPOINT Register value
  */
#define PCD_GET_ENDPOINT                       USB_DRD_GET_CHEP

/**
  * @brief  sets the status for tx transfer (bits STAT_TX[1:0])
  */
#define PCD_SET_EP_TX_STATUS                   USB_DRD_SET_CHEP_TX_STATUS

/**
  * @brief  sets the status for rx transfer (bits STAT_TX[1:0])
  */
#define PCD_SET_EP_RX_STATUS                   USB_DRD_SET_CHEP_RX_STATUS

/**
  * @brief  Sets directly EP_KIND bit in the endpoint register
  */
#define PCD_SET_EP_KIND                        USB_DRD_SET_CHEP_KIND

/**
  * @brief  Clears directly EP_KIND bit in the endpoint register
  */
#define PCD_CLEAR_EP_KIND                      USB_DRD_CLEAR_CHEP_KIND

/**
  * @brief  Sets directly Bulk Endpoint_Double_Buffer bit in the endpoint register
  */
#define PCD_SET_BULK_EP_DBUF                   USB_DRD_SET_CHEP_KIND

/**
  * @brief  Clears directly Bulk Endpoint_Double_Buffer bit in the endpoint register
  */
#define PCD_CLEAR_BULK_EP_DBUF                 USB_DRD_CLEAR_CHEP_KIND

/**
  * @brief  Sets directly STATUS_OUT bit in the endpoint register
  */
#define PCD_SET_OUT_STATUS                     USB_DRD_SET_CHEP_KIND

/**
  * @brief  Clears directly STATUS_OUT bit in the endpoint register
  */
#define PCD_CLEAR_OUT_STATUS                   USB_DRD_CLEAR_CHEP_KIND

/**
  * @brief  Clears bit CTR_RX / CTR_TX in the endpoint register
  */
#define PCD_CLEAR_RX_EP_CTR                    USB_DRD_CLEAR_RX_CHEP_CTR

/**
  * @brief  Clears bit CTR_TX in the endpoint register
  */
#define PCD_CLEAR_TX_EP_CTR                    USB_DRD_CLEAR_TX_CHEP_CTR

/**
  * @brief  Toggles DTOG_RX bit in the endpoint register
  */
#define PCD_RX_DTOG                            USB_DRD_RX_DTOG

/**
  * @brief  Toggles DTOG_TX bit in the endpoint register
  */
#define PCD_TX_DTOG                            USB_DRD_TX_DTOG

/**
  * @brief  Clears DTOG_RX bit in the endpoint register
  */
#define PCD_CLEAR_RX_DTOG                      USB_DRD_CLEAR_RX_DTOG

/**
  * @brief  Clears DTOG_TX bit in the endpoint register
  */
#define PCD_CLEAR_TX_DTOG                      USB_DRD_CLEAR_TX_DTOG


/**
  * @brief  Sets address in an endpoint register
  */
#define PCD_SET_EP_ADDRESS                     USB_DRD_SET_CHEP_ADDRESS

/**
  * @brief  sets address of the tx buffer
  */
#define PCD_SET_EP_TX_ADDRESS                  USB_DRD_SET_CHEP_TX_ADDRESS


/**
  * @brief  sets address of the rx buffer
  */
#define PCD_SET_EP_RX_ADDRESS                  USB_DRD_SET_CHEP_RX_ADDRESS


/**
  * @brief  sets counter for the txbuffer
  */
#define PCD_SET_EP_TX_CNT                      USB_DRD_SET_CHEP_TX_CNT

/**
  * @brief  sets counter for the rx buffer
  */
#define PCD_SET_EP_RX_CNT                      USB_DRD_SET_CHEP_RX_CNT

/**
  * @brief  gets counter of the tx buffer
  */
#define PCD_GET_EP_TX_CNT                      USB_DRD_GET_CHEP_TX_CNT

/**
  * @brief  Sets addresses in a double buffer endpoint
  */
#define PCD_SET_EP_DBUF_ADDR                   USB_DRD_SET_CHEP_DBUF_ADDR

/**
  * @brief  Sets buffer 0 address of a double buffer endpoint
  */
#define PCD_SET_EP_DBUF0_CNT                   USB_DRD_SET_CHEP_DBUF0_CNT

/**
  * @brief  Sets buffer 1 address of a double buffer endpoint
  */
#define PCD_SET_EP_DBUF1_CNT                   USB_DRD_SET_CHEP_DBUF1_CNT

/**
  * @brief  Sets double buffer address of a double buffer endpoint
  */
#define PCD_SET_EP_DBUF_CNT                    USB_DRD_SET_CHEP_DBUF_CNT

/**
  * @brief  Powerdown exit count
  */
#define USB_DRD_PDWN_EXIT_CNT                  0x100U

/**
  * @brief  Set Channel
  */
#define HCD_SET_CHANNEL                        USB_DRD_SET_CHEP

/**
  * @brief  Get Channel Register
  */
#define HCD_GET_CHANNEL                        USB_DRD_GET_CHEP


/**
  * @brief Set the Setup bit in the corresponding channel, when a Setup
     transaction is needed
  */
#define HCD_SET_CH_TX_SETUP                    USB_DRD_CHEP_TX_SETUP


/**
  * @brief  sets the status for tx transfer (bits STAT_TX[1:0])
  */
#define HCD_SET_CH_TX_STATUS                   USB_DRD_SET_CHEP_TX_STATUS


/**
  * @brief  sets the status for rx transfer (bits STAT_TX[1:0])
  */
#define HCD_SET_CH_RX_STATUS                   USB_DRD_SET_CHEP_RX_STATUS

/**
  * @brief  gets the status for tx transfer (bits STAT_TX[1:0])
  */
#define HCD_GET_CH_TX_STATUS                   USB_DRD_GET_CHEP_TX_STATUS

/**
  * @brief  gets the status for rx transfer (bits STAT_RX[1:0])
  */
#define HCD_GET_CH_RX_STATUS                   USB_DRD_GET_CHEP_RX_STATUS

/**
  * @brief  Sets CH_KIND bit in the Channel register
  */
#define HCD_SET_CH_KIND                        USB_DRD_SET_CH_KIND

/**
  * @brief  Clears CH_KIND bit in the Channel register
  */
#define HCD_CLEAR_CH_KIND                      USB_DRD_CLEAR_CH_KIND

/**
  * @brief  Sets Bulk Channel bit in the Channel register
  */
#define HCD_SET_BULK_CH_DBUF                   HCD_SET_CH_KIND

/**
  * @brief  Clears Bulk Channel bit in the Channel register
  */
#define HCD_CLEAR_BULK_CH_DBUF                 HCD_CLEAR_CH_KIND


/**
  * @brief  Clears bit ERR_RX in the Channel register
  */
#define HCD_CLEAR_RX_CH_ERR                    USB_DRD_CLEAR_CHEP_RX_ERR

/**
  * @brief  Clears bit ERR_TX in the Channel register
  */
#define HCD_CLEAR_TX_CH_ERR                    USB_DRD_CLEAR_CHEP_TX_ERR

/**
  * @brief  Clears bit CTR_RX in the endpoint register
  */
#define HCD_CLEAR_RX_CH_CTR                    USB_DRD_CLEAR_RX_CHEP_CTR

/**
  * @brief  Clears bit CTR_TX in the endpoint register
  */
#define HCD_CLEAR_TX_CH_CTR                    USB_DRD_CLEAR_TX_CHEP_CTR

/**
  * @brief  Toggles DTOG_RX bit in the endpoint register
  */
#define HCD_RX_DTOG                            USB_DRD_RX_DTOG

/**
  * @brief  Toggles DTOG_TX bit in the endpoint register
  */
#define HCD_TX_DTOG                            USB_DRD_TX_DTOG

/**
  * @brief  Clears DTOG_RX bit in the endpoint register
  */
#define HCD_CLEAR_RX_DTOG                      USB_DRD_CLEAR_RX_DTOG

/**
  * @brief  Clears DTOG_TX bit in the endpoint register
  */
#define HCD_CLEAR_TX_DTOG                      USB_DRD_CLEAR_TX_DTOG


/**
  * @brief  sets counter for the tx buffer
  */
#define HCD_SET_CH_TX_CNT                      USB_DRD_SET_CHEP_TX_CNT

/**
  * @brief  sets counter for the rx buffer
  */
#define HCD_SET_CH_RX_CNT                      USB_DRD_SET_CHEP_RX_CNT


/**
  * @brief  gets counter of the tx buffer
  */
#define HCD_GET_CH_TX_CNT                      USB_DRD_GET_CHEP_TX_CNT

/**
  * @brief  Sets buffer 0 address of a double buffer endpoint
  */
#define HCD_SET_CH_DBUF0_CNT                   USB_DRD_SET_CHEP_DBUF0_CNT

/**
  * @brief  Sets buffer 1 address of a double buffer endpoint
  */
#define HCD_SET_CH_DBUF1_CNT                   USB_DRD_SET_CHEP_DBUF1_CNT

/**
  * @brief  Sets double buffer address of a double buffer endpoint
  */
#define HCD_SET_CH_DBUF_CNT                    USB_DRD_SET_CHEP_DBUF_CNT

/**
  * @brief  USB DRD core typedef definition
  */
typedef USB_DRD_TypeDef usb_drd_global_t;


/**
  * @brief  USB Endpoint Configuration Structure definition
  */
typedef struct
{
  usb_core_channel_t virtual_ch_num;  /*!< Virtual Channel number associated to the Endpoint number
                                           This parameter must be a number between Min_Data = 1 and Max_Data = 15 */

  usb_core_ep_direction_t dir;        /*!< Endpoint direction state
                                           This parameter must be a number between Min_Data = 0 and Max_Data = 1  */

  uint8_t is_allocated;               /*!< Endpoint allocation state
                                           This parameter must be a number between Min_Data = 0 and Max_Data = 1  */

  uint8_t is_dual_allocated;          /*!< Endpoint dual allocation state
                                           This parameter must be a number between Min_Data = 0 and Max_Data = 1  */

  uint16_t pma_address;               /*!< PMA Address
                                           This parameter can be any value between Min_addr = 0 and Max_addr = 1K */

  uint16_t pma_addr0;                 /*!< PMA Address0
                                           This parameter can be any value between Min_addr = 0 and Max_addr = 1K */

  uint16_t pma_addr1;                 /*!< PMA Address1
                                           This parameter can be any value between Min_addr = 0 and Max_addr = 1K */

} usb_drd_ep_config_t;


/**
  * @brief  USB DRD DoubleBuffer structure definition
  */
typedef enum
{
  USB_DRD_SNG_BUF = USB_CORE_CONFIG_DISABLED,   /*!< USB DOUBLE Buffer state disabled: 0 */
  USB_DRD_DBL_BUF = USB_CORE_CONFIG_ENABLED,    /*!< USB DOUBLE Buffer state enabled:  1 */
} usb_drd_doublebuffer_t;


/**
  * @brief  USB Endpoint double buffer Configuration Structure definition
  */
typedef struct
{
  usb_drd_doublebuffer_t is_bulk_db;      /*!< bulk Endpoint double buffer state
                                               This parameter must be a number between Min_Data = 0 and Max_Data = 1  */

  usb_drd_doublebuffer_t is_iso_db;       /*!< isochrone Endpoint double buffer state
                                               This parameter must be a number between Min_Data = 0 and Max_Data = 1  */
} usb_drd_ep_db_config_t;


/**
  * @brief  USB DRD DoubleBuffer API structure definition
  */
typedef enum
{
  USB_DRD_BULK_DB_ENBALE  = 0x01U,    /*!< USB DRD BULK Double Buffer Enable*/
  USB_DRD_BULK_DB_DISABLE = 0x02U,    /*!< USB DRD BULK Double Buffer Disable*/
  USB_DRD_ISOC_DB_ENBALE  = 0x03U,    /*!< USB DRD Isochnronous Double Buffer Enable*/
  USB_DRD_ISOC_DB_DISABLE = 0x04U,    /*!< USB DRD Isochnronous Double Buffer Disable*/
} usb_drd_db_status_t;

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/

/** @defgroup DRD_Exported_Macros DRD Exported Macros
  *  @brief macros to handle interrupts and specific clock configurations
  * @{
  */

/**
  *  @brief macros to get Instance
  */
#define USB_DRD_GET_INSTANCE(instance)         ((usb_drd_global_t *)((uint32_t)instance))

/**
  *  @brief macros to get Channel Number
  */
#define USB_DRD_GET_CHNUM(instance)          (((instance)->ISTR) & USB_ISTR_IDN)

/**
  *  @brief macros to get Channel Direction
  */
#define USB_DRD_GET_CHDIR(instance)          (((instance)->ISTR) & USB_ISTR_DIR)


/**
  * @brief  Set Channel/Endpoint to the USB Register
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  reg_value Register Value
  */
__STATIC_INLINE void USB_DRD_SET_CHEP(uint32_t instance, usb_core_phy_chep_t ch_ep_num, uint32_t reg_value)
{
  usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  *(__IO uint32_t *)(&p_usb->CHEP0R + (uint32_t)ch_ep_num) = reg_value;

  return;
}

/**
  * @brief  Get Channel/Endpoint from the USB Register
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @retval Channel/endpoint number
  */
__STATIC_INLINE uint32_t USB_DRD_GET_CHEP(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  const usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);

  return (*(__IO const uint32_t *)(&p_usb->CHEP0R + (uint32_t)ch_ep_num));
}

/**
  * @brief  Toggles DTOG_RX bit in the endpoint register
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  */
__STATIC_INLINE void USB_DRD_RX_DTOG(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  uint32_t reg_value;

  reg_value = USB_DRD_GET_CHEP(instance, ch_ep_num) & USB_CHEP_REG_MASK;
  USB_DRD_SET_CHEP(instance, ch_ep_num, reg_value | USB_CHEP_VTRX | USB_CHEP_VTTX | USB_CHEP_DTOG_RX);

  return;
}

/**
  * @brief  Toggles DTOG_TX bit in the endpoint register
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  */
__STATIC_INLINE void USB_DRD_TX_DTOG(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  uint32_t reg_value;

  reg_value = USB_DRD_GET_CHEP(instance, ch_ep_num) & USB_CHEP_REG_MASK;
  USB_DRD_SET_CHEP(instance, ch_ep_num, reg_value | USB_CHEP_VTRX | USB_CHEP_VTTX | USB_CHEP_DTOG_TX);

  return;
}

/**
  * @brief Set the Setup bit in the corresponding channel, when a Setup
     transaction is needed
  * @param instance USB device
  * @param  ch_ep_num Channel/Endpoint Number
  */
__STATIC_INLINE void USB_DRD_CHEP_TX_SETUP(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  uint32_t reg_value;

  reg_value = USB_DRD_GET_CHEP(instance, ch_ep_num);

  /* Set Setup bit */
  USB_DRD_SET_CHEP(instance, ch_ep_num, reg_value | USB_CHEP_SETUP);

  return;
}

/**
  * @brief  Clears bit ERR_RX in the Channel register
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Channel/Endpoint Number
  */
__STATIC_INLINE void USB_DRD_CLEAR_CHEP_RX_ERR(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  uint32_t reg_value;

  reg_value = USB_DRD_GET_CHEP(instance, ch_ep_num);
  reg_value = (reg_value & USB_CHEP_REG_MASK & (~USB_CHEP_ERRRX) & (~USB_CHEP_VTRX)) | (USB_CHEP_VTTX | USB_CHEP_ERRTX);
  USB_DRD_SET_CHEP(instance, ch_ep_num, reg_value);

  return;
}

/**
  * @brief  Clears bit ERR_TX in the Channel register
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Channel/Endpoint Number
  */
__STATIC_INLINE void USB_DRD_CLEAR_CHEP_TX_ERR(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  uint32_t reg_value;

  reg_value = USB_DRD_GET_CHEP(instance, ch_ep_num);
  reg_value = (reg_value & USB_CHEP_REG_MASK & (~USB_CHEP_ERRTX) & (~USB_CHEP_VTTX)) | (USB_CHEP_VTRX | USB_CHEP_ERRRX);
  USB_DRD_SET_CHEP(instance, ch_ep_num, reg_value);

  return;
}

/**
  * @brief  sets the status for tx transfer (bits STAT_TX[1:0])
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  ep_ch_state new state
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_TX_STATUS(uint32_t instance, usb_core_phy_chep_t ch_ep_num, uint32_t ep_ch_state)
{
  uint32_t reg_value;

  reg_value = USB_DRD_GET_CHEP(instance, ch_ep_num) & USB_CHEP_TX_DTOGMASK;

  /* toggle first bit ? */
  if ((USB_CHEP_TX_DTOG1 & ep_ch_state) != 0U)
  {
    reg_value ^= USB_CHEP_TX_DTOG1;
  }

  /* toggle second bit ? */
  if ((USB_CHEP_TX_DTOG2 & ep_ch_state) != 0U)
  {
    reg_value ^= USB_CHEP_TX_DTOG2;
  }

  USB_DRD_SET_CHEP(instance, ch_ep_num, (reg_value | USB_CHEP_VTRX | USB_CHEP_VTTX));

  return;
}

/**
  * @brief  sets the status for rx transfer (bits STAT_TX[1:0])
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  ep_ch_state new state
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_RX_STATUS(uint32_t instance, usb_core_phy_chep_t ch_ep_num, uint32_t ep_ch_state)
{
  uint32_t reg_value;

  reg_value = USB_DRD_GET_CHEP(instance, ch_ep_num) & USB_CHEP_RX_DTOGMASK;

  /* toggle first bit ? */
  if ((USB_CHEP_RX_DTOG1 & ep_ch_state) != 0U)
  {
    reg_value ^= USB_CHEP_RX_DTOG1;
  }
  else
  {
    /* nothing to do */
  }

  /* toggle second bit ? */
  if ((USB_CHEP_RX_DTOG2 & ep_ch_state) != 0U)
  {
    reg_value ^= USB_CHEP_RX_DTOG2;
  }
  else
  {
    /* nothing to do */
  }

  USB_DRD_SET_CHEP(instance, ch_ep_num, (reg_value | USB_CHEP_VTRX | USB_CHEP_VTTX));

  return;
}

/**
  * @brief  gets the status for tx transfer (bits STAT_TX[1:0]
  *         /STAT_RX[1:0])
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @retval status for tx transfer
  */
__STATIC_INLINE uint16_t USB_DRD_GET_CHEP_TX_STATUS(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  return (uint16_t)(USB_DRD_GET_CHEP(instance, ch_ep_num) & USB_CHEP_TX_STTX);
}

/**
  * @brief  gets the status for rx transfer (bits STAT_TX[1:0]
  *         /STAT_RX[1:0])
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @retval  ch_ep_num RX status
  */
__STATIC_INLINE uint16_t USB_DRD_GET_CHEP_RX_STATUS(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  return (uint16_t)(USB_DRD_GET_CHEP(instance, ch_ep_num) & USB_CHEP_RX_STRX);
}

/**
  * @brief  set  EP_KIND bit
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_KIND(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  uint32_t reg_value;

  reg_value = USB_DRD_GET_CHEP(instance, ch_ep_num) & USB_CHEP_REG_MASK;
  USB_DRD_SET_CHEP(instance, ch_ep_num, (reg_value | USB_CHEP_VTRX | USB_CHEP_VTTX | USB_CHEP_KIND));

  return;
}

/**
  * @brief  clear EP_KIND bit
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  */
__STATIC_INLINE void USB_DRD_CLEAR_CHEP_KIND(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  uint32_t reg_value;

  reg_value = USB_DRD_GET_CHEP(instance, ch_ep_num) & USB_EP_KIND_MASK;
  USB_DRD_SET_CHEP(instance, ch_ep_num, (reg_value | USB_CHEP_VTRX | USB_CHEP_VTTX));

  return;
}

/**
  * @brief  Clears bit CTR_RX in the endpoint register
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  */
__STATIC_INLINE void USB_DRD_CLEAR_RX_CHEP_CTR(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  uint32_t reg_value;

  reg_value = USB_DRD_GET_CHEP(instance, ch_ep_num) & (0xFFFF7FFFU & USB_CHEP_REG_MASK);
  USB_DRD_SET_CHEP(instance, ch_ep_num, (reg_value | USB_CHEP_VTTX));

  return;
}

/**
  * @brief  Clears bit CTR_TX in the endpoint register
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  */
__STATIC_INLINE void USB_DRD_CLEAR_TX_CHEP_CTR(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  uint32_t reg_value;

  reg_value = USB_DRD_GET_CHEP(instance, ch_ep_num) & (0xFFFFFF7FU & USB_CHEP_REG_MASK);
  USB_DRD_SET_CHEP(instance, ch_ep_num, (reg_value | USB_CHEP_VTRX));

  return;
}

/**
  * @brief  Clears DTOG_RX bit in the endpoint register
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  */
__STATIC_INLINE void USB_DRD_CLEAR_RX_DTOG(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  uint32_t reg_value;

  reg_value = USB_DRD_GET_CHEP(instance, ch_ep_num);
  if ((reg_value & USB_CHEP_DTOG_RX) != 0U)
  {
    USB_DRD_RX_DTOG(instance, ch_ep_num);
  }
  else
  {
    /* nothing to do */
  }

  return;
}

/**
  * @brief  Clears DTOG_TX bit in the endpoint register
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  */
__STATIC_INLINE void USB_DRD_CLEAR_TX_DTOG(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  uint32_t reg_value;

  reg_value = USB_DRD_GET_CHEP(instance, ch_ep_num);
  if ((reg_value & USB_CHEP_DTOG_TX) != 0U)
  {
    USB_DRD_TX_DTOG(instance, ch_ep_num);
  }
  else
  {
    /* nothing to do */
  }

  return;
}

/**
  * @brief  Sets address in an endpoint register
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  address Address
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_ADDRESS(uint32_t instance, usb_core_phy_chep_t ch_ep_num, uint32_t address)
{
  uint32_t reg_value;

  /* Read the USB->CHEPx into reg_value, Reset(DTOGRX/STRX/DTOGTX/STTX) and set the Ep Address */
  reg_value = (USB_DRD_GET_CHEP(instance, ch_ep_num) & USB_CHEP_REG_MASK) | address;

  /* Set reg_value in USB->CHEPx and set Transmit/Receive Valid Transfer  (x=ch_ep_num) */
  USB_DRD_SET_CHEP(instance, ch_ep_num, (reg_value | USB_CHEP_VTRX | USB_CHEP_VTTX));

  return;
}

/* PMA API Buffer Descriptor Management ------------------------------------------------------------*/

/**
  * @brief  Set TX Buffer Descriptor Address Field
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  address TX address
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_TX_ADDRESS(uint32_t instance, usb_core_phy_chep_t ch_ep_num, uint32_t address)
{
  STM32_UNUSED(instance);

  /* Reset old Address */
  (USB_DRD_PMA_BUFF + (uint32_t)ch_ep_num)->TXBD &= USB_PMA_TXBD_ADDMSK;

  /* Bit0 & Bit1 = 0 PMA must be Word aligned */
  (USB_DRD_PMA_BUFF + (uint32_t)ch_ep_num)->TXBD |= (uint32_t)(((uint32_t)address >> 2U) << 2U);

  return;
}

/**
  * @brief  Set RX Buffer Descriptor Address Field
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  address RX address
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_RX_ADDRESS(uint32_t instance, usb_core_phy_chep_t ch_ep_num, uint32_t address)
{
  STM32_UNUSED(instance);

  /* Reset old Address */
  (USB_DRD_PMA_BUFF + (uint32_t)ch_ep_num)->RXBD &= USB_PMA_RXBD_ADDMSK;

  /* Bit0 & Bit1 = 0 PMA must be Word aligned */
  (USB_DRD_PMA_BUFF + (uint32_t)ch_ep_num)->RXBD |= (uint32_t)(((uint32_t)address >> 2U) << 2U);

  return;
}

/**
  * @brief  Sets counter of rx buffer with no of blocks
  * @param  rx_count Register pointer
  * @param  count Counter
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_CNT_RX_REG(volatile uint32_t *rx_count, uint32_t count)
{
  uint32_t nbr_blocks;

  *rx_count &= ~(USB_CNTRX_BLSIZE | USB_CNTRX_NBLK_MSK);

  if (count == 0U)
  {
    *rx_count |= USB_CNTRX_BLSIZE;
  }
  else if ((count) <= 62U)
  {
    /* Divide PacketSize by 32 to calculate the Nb of Block32 */
    nbr_blocks = (uint32_t)((uint32_t)count >> 1U);

    if ((count & 0x1U) != 0U)
    {
      nbr_blocks++;
    }

    *rx_count |= (uint32_t)(nbr_blocks << 26U);
  }
  else
  {
    /* Divide PacketSize by 32 to calculate the Nb of Block32 */
    nbr_blocks = ((uint32_t)count >> 5U);

    if (((uint32_t)(count) % 32U) == 0U)
    {
      nbr_blocks--;
    }

    *rx_count |= (uint32_t)(((nbr_blocks << 26U)) | USB_CNTRX_BLSIZE);
  }

  return;
}

/**
  * @brief  sets counter for the tx buffer
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  count Counter value
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_TX_CNT(uint32_t instance, usb_core_phy_chep_t ch_ep_num, uint32_t count)
{
  STM32_UNUSED(instance);

  /* Reset old TX_Count value */
  (USB_DRD_PMA_BUFF + (uint32_t)ch_ep_num)->TXBD &= USB_PMA_TXBD_COUNTMSK;

  /* Set the count in the dedicated EP_TXBuffer */
  (USB_DRD_PMA_BUFF + (uint32_t)ch_ep_num)->TXBD |= (uint32_t)((uint32_t)count << 16U);

  return;
}

/**
  * @brief  sets counter for the rx double buffer0
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  count Counter value
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_RX_DBUF0_CNT(uint32_t instance, usb_core_phy_chep_t ch_ep_num, uint32_t count)
{
  STM32_UNUSED(instance);

  /* Set the count in the dedicated EP_TXBuffer */
  USB_DRD_SET_CHEP_CNT_RX_REG((volatile uint32_t *) & (USB_DRD_PMA_BUFF + (uint32_t)ch_ep_num)->TXBD, count);

  return;
}

/**
  * @brief  sets counter for the rx buffer
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  count Counter value
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_RX_CNT(uint32_t instance, usb_core_phy_chep_t ch_ep_num, uint32_t count)
{
  STM32_UNUSED(instance);

  /* Set the count in the dedicated EP_RXBuffer */
  USB_DRD_SET_CHEP_CNT_RX_REG((volatile uint32_t *) & (USB_DRD_PMA_BUFF + (uint32_t)ch_ep_num)->RXBD, count);

  return;
}

/**
  * @brief  gets counter of the tx buffer
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @retval Counter value
  */
__STATIC_INLINE uint16_t USB_DRD_GET_CHEP_TX_CNT(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  STM32_UNUSED(instance);
  return (uint16_t)(((USB_DRD_PMA_BUFF + (uint32_t)ch_ep_num)->TXBD & 0x03FF0000U) >> 16U);
}

/**
  * @brief  gets counter of the rx buffer
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @retval Counter value
  */
__STATIC_INLINE uint16_t USB_DRD_GET_CHEP_RX_CNT(uint32_t instance, usb_core_phy_chep_t ch_ep_num)
{
  STM32_UNUSED(instance);
  return (uint16_t)(((USB_DRD_PMA_BUFF + (uint32_t)ch_ep_num)->RXBD & 0x03FF0000U) >> 16U);
}

/**
  * @brief  Sets buffer 0 address in a double buffer endpoint
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  buff0_addr buffer 0 address
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_DBUF0_ADDR(uint32_t instance, usb_core_phy_chep_t ch_ep_num, uint32_t buff0_addr)
{
  USB_DRD_SET_CHEP_TX_ADDRESS(instance, ch_ep_num, buff0_addr);

  return;
}

/**
  * @brief  Sets buffer 1 address in a double buffer endpoint
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  buff1_addr buffer 1 address
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_DBUF1_ADDR(uint32_t instance, usb_core_phy_chep_t ch_ep_num, uint32_t buff1_addr)
{
  USB_DRD_SET_CHEP_RX_ADDRESS(instance, ch_ep_num, buff1_addr);

  return;
}

/**
  * @brief  Sets addresses in a double buffer endpoint
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  buff0_addr: buffer 0 address
  * @param  buff1_addr = buffer 1 address
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_DBUF_ADDR(uint32_t instance, usb_core_phy_chep_t ch_ep_num,
                                                uint32_t buff0_addr, uint32_t buff1_addr)
{
  USB_DRD_SET_CHEP_DBUF0_ADDR(instance, ch_ep_num, buff0_addr);
  USB_DRD_SET_CHEP_DBUF1_ADDR(instance, ch_ep_num, buff1_addr);

  return;
}

/**
  * @brief  Gets buffer 0 address of a double buffer endpoint
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  direction endpoint direction
  *         USB_CORE_EP_OUT_DIR = OUT
  *         USB_CORE_EP_IN_DIR  = IN
  * @param  count: Counter value
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_DBUF0_CNT(uint32_t instance, usb_core_phy_chep_t ch_ep_num,
                                                usb_core_ep_direction_t direction, uint32_t count)
{
  if (direction == USB_CORE_EP_OUT_DIR)
  {
    /* OUT endpoint */
    USB_DRD_SET_CHEP_RX_DBUF0_CNT(instance, ch_ep_num, count);
  }
  else
  {
    /* IN endpoint */
    USB_DRD_SET_CHEP_TX_CNT(instance, ch_ep_num, count);
  }

  return;
}

/**
  * @brief  Gets buffer 1 address of a double buffer endpoint
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  direction endpoint direction
  *         USB_CORE_EP_OUT_DIR = OUT
  *         USB_CORE_EP_IN_DIR  = IN
  * @param  count: Counter value
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_DBUF1_CNT(uint32_t instance, usb_core_phy_chep_t ch_ep_num,
                                                usb_core_ep_direction_t direction, uint32_t count)
{
  if (direction == USB_CORE_EP_OUT_DIR)
  {
    /* OUT endpoint */
    USB_DRD_SET_CHEP_RX_CNT(instance, ch_ep_num, count);
  }
  else
  {
    if (direction == USB_CORE_EP_IN_DIR)
    {
      /* IN endpoint */
      (USB_DRD_PMA_BUFF + (uint32_t)ch_ep_num)->RXBD &= USB_PMA_TXBD_COUNTMSK;
      (USB_DRD_PMA_BUFF + (uint32_t)ch_ep_num)->RXBD |= (uint32_t)((uint32_t)count << 16U);
    }
  }

  return;
}

/**
  * @brief  Sets buffer address of a double buffer endpoint
  * @param  instance USB peripheral instance register address
  * @param  ch_ep_num Endpoint Number
  * @param  direction endpoint direction
  *         USB_CORE_EP_OUT_DIR = OUT
  *         USB_CORE_EP_IN_DIR  = IN
  * @param  count: Counter value
  */
__STATIC_INLINE void USB_DRD_SET_CHEP_DBUF_CNT(uint32_t instance, usb_core_phy_chep_t ch_ep_num,
                                               usb_core_ep_direction_t direction, uint32_t count)
{
  USB_DRD_SET_CHEP_DBUF0_CNT(instance, ch_ep_num, direction, count);
  USB_DRD_SET_CHEP_DBUF1_CNT(instance, ch_ep_num, direction, count);

  return;
}

/**
  * @}
  */


/**
  * @brief  gets counter of the rx buffer
  * @param  instance USB peripheral instance register address
  * @param  ep_num Endpoint Number
  * @retval Counter value
  */
__STATIC_INLINE uint16_t PCD_GET_EP_RX_CNT(uint32_t instance, usb_core_phy_chep_t ep_num)
{
  STM32_UNUSED(instance);
  __IO uint32_t count = PCD_RX_PMA_CNT;

  /* WA: few cycles for RX PMA descriptor to update */
  while (count > 0U)
  {
    count--;
  }

  return (uint16_t)USB_DRD_GET_CHEP_RX_CNT(instance, ep_num);
}


/**
  * @brief  gets counter of the rx buffer0
  * @param  instance USB peripheral instance register address
  * @param  ep_num Endpoint Number
  * @retval Counter value
  */
__STATIC_INLINE uint16_t PCD_GET_EP_DBUF0_CNT(uint32_t instance, usb_core_phy_chep_t ep_num)
{
  STM32_UNUSED(instance);
  __IO uint32_t count = PCD_RX_PMA_CNT;

  /* WA: few cycles for RX PMA descriptor to update */
  while (count > 0U)
  {
    count--;
  }

  return (uint16_t)USB_DRD_GET_CHEP_DBUF0_CNT(instance, ep_num);
}


/**
  * @brief  gets counter of the rx buffer1
  * @param  instance USB peripheral instance register address
  * @param  ep_num Endpoint Number
  * @retval Counter value
  */
__STATIC_INLINE uint16_t PCD_GET_EP_DBUF1_CNT(uint32_t instance, usb_core_phy_chep_t ep_num)
{
  STM32_UNUSED(instance);
  __IO uint32_t count = PCD_RX_PMA_CNT;

  /* WA: few cycles for RX PMA descriptor to update */
  while (count > 0U)
  {
    count--;
  }

  return (uint16_t)USB_DRD_GET_CHEP_DBUF1_CNT(instance, ep_num);
}


/**
  * @brief  gets counter of the rx buffer
  * @param  instance USB peripheral instance register address
  * @param  phy_ch_num physical channel Number
  * @retval Counter value
  */
__STATIC_INLINE uint16_t HCD_GET_CH_RX_CNT(uint32_t instance, usb_core_phy_chep_t phy_ch_num)
{
  const usb_drd_global_t *p_usb = USB_DRD_GET_INSTANCE(instance);
  uint32_t ep_reg = USB_DRD_GET_CHEP(instance, phy_ch_num);
  __IO uint32_t count = 10U;

  /* Count depends on device LS */
  if (((p_usb->ISTR & USB_ISTR_LS_DCONN) == USB_ISTR_LS_DCONN) || ((ep_reg & USB_CHEP_LSEP) == USB_CHEP_LSEP))
  {
    count = (70U * (SystemCoreClock / 1000000U)) / 100U;
  }

  if (count > 15U)
  {
    count = USB_CORE_MAX(10U, (count - 15U));
  }

  /* WA: few cycles for RX PMA descriptor to update */
  while (count > 0U)
  {
    count--;
  }

  return (uint16_t)USB_DRD_GET_CHEP_RX_CNT(instance, phy_ch_num);
}

/**
  * @brief  gets counter of the rx buffer0.
  * @param  instance USB peripheral instance register address.
  * @param  phy_ch_num physical channel Number.
  * @retval Counter value
  */
__STATIC_INLINE uint16_t HCD_GET_CH_DBUF0_CNT(uint32_t instance, usb_core_phy_chep_t phy_ch_num)
{
  STM32_UNUSED(instance);
  __IO uint32_t count = 10U;

  /* WA: few cycles for RX PMA descriptor to update */
  while (count > 0U)
  {
    count--;
  }

  return (uint16_t)USB_DRD_GET_CHEP_DBUF0_CNT(instance, phy_ch_num);
}


/**
  * @brief  gets counter of the rx buffer1.
  * @param  instance USB peripheral instance register address.
  * @param  phy_ch_num physical channel Number.
  * @retval Counter value
  */
__STATIC_INLINE uint16_t HCD_GET_CH_DBUF1_CNT(uint32_t instance, usb_core_phy_chep_t phy_ch_num)
{
  STM32_UNUSED(instance);
  __IO uint32_t count = 10U;

  /* WA: few cycles for RX PMA descriptor to update */
  while (count > 0U)
  {
    count--;
  }

  return (uint16_t)USB_DRD_GET_CHEP_DBUF1_CNT(instance, phy_ch_num);
}

/* Exported functions --------------------------------------------------------*/
/** @defgroup USB_CORE_Exported_Functions USB Core Low Layer Exported Functions
  * @{
  */
usb_core_status_t USB_DRD_InitCore(uint32_t instance, const usb_core_config_params_t *p_core_config);
usb_core_status_t USB_DRD_DeInitCore(uint32_t instance);
usb_core_status_t USB_DRD_EnableGlobalInterrupt(uint32_t instance);
usb_core_status_t USB_DRD_DisableGlobalInterrupt(uint32_t instance);
usb_core_status_t USB_DRD_SetCurrentMode(uint32_t instance, usb_core_mode_t core_mode);
usb_core_mode_t USB_DRD_GetCurrentMode(uint32_t instance);

usb_core_status_t USB_DRD_ActivateRemoteWakeup(uint32_t instance);
usb_core_status_t USB_DRD_DeActivateRemoteWakeup(uint32_t instance);

uint32_t USB_DRD_ReadInterrupts(uint32_t instance);
void     USB_DRD_ClearInterrupts(uint32_t instance, uint32_t interrupt);
void     USB_DRD_WritePMA(uint32_t instance, uint8_t *p_src, uint16_t pma_address, uint16_t size_byte);
void     USB_DRD_ReadPMA(uint32_t instance, uint8_t *p_dest, uint16_t pma_address, uint16_t size_byte);

usb_core_status_t USB_DRD_PCD_InitDriver(usb_core_pcd_driver_t *p_driver);
usb_core_status_t USB_DRD_InitDevice(uint32_t instance, const usb_core_config_params_t *p_core_config);
usb_core_status_t USB_DRD_StartDevice(uint32_t instance);
usb_core_status_t USB_DRD_StopDevice(uint32_t instance);
usb_core_status_t USB_DRD_ActivateEndpoint(uint32_t instance, usb_core_ep_t *p_ep);
usb_core_status_t USB_DRD_DeactivateEndpoint(uint32_t instance, const usb_core_ep_t *p_ep);
usb_core_status_t USB_DRD_StartEndpointXfer(uint32_t instance, usb_core_ep_t *p_ep);
usb_core_status_t USB_DRD_StopEndpointXfer(uint32_t instance, const usb_core_ep_t *p_ep);
usb_core_status_t USB_DRD_SetEndpointStall(uint32_t instance, const usb_core_ep_t *p_ep);
usb_core_status_t USB_DRD_ClearEndpointStall(uint32_t instance, const usb_core_ep_t *p_ep);
usb_core_status_t USB_DRD_SetDeviceAddress(uint32_t instance, uint8_t address);
usb_core_status_t USB_DRD_ConnectDevice(uint32_t instance);
usb_core_status_t USB_DRD_DisconnectDevice(uint32_t instance);
usb_core_device_speed_t USB_DRD_GetDeviceSpeed(uint32_t instance);

usb_core_status_t  USB_DRD_BCD_SetMode(uint32_t instance,
                                       usb_core_bcd_config_t bcd_config, usb_core_bcd_config_sts_t bcd_sts);
usb_core_bcd_port_status_t USB_DRD_BCD_SetPortDetection(uint32_t instance, usb_core_bcd_detection_t detection);
usb_core_status_t USB_DRD_BCD_Activate(uint32_t instance);
usb_core_status_t USB_DRD_BCD_DeActivate(uint32_t instance);

usb_core_status_t USB_DRD_LPM_Activate(uint32_t instance);
usb_core_status_t USB_DRD_LPM_DeActivate(uint32_t instance);

usb_core_status_t USB_DRD_HCD_InitDriver(usb_core_hcd_driver_t *p_driver);
usb_core_status_t USB_DRD_PortReset(uint32_t instance, usb_core_port_reset_sts_t reset_status);
usb_core_status_t USB_DRD_PortSuspend(uint32_t instance);
usb_core_status_t USB_DRD_PortResume(uint32_t instance, usb_core_port_resume_sts_t resume_status);
usb_core_status_t USB_DRD_InitHost(uint32_t instance, const usb_core_config_params_t *p_core_config);
usb_core_status_t USB_DRD_StartHost(uint32_t instance);
usb_core_status_t USB_DRD_StopHost(uint32_t instance);
usb_core_status_t USB_DRD_SetChannelDoubleBuffer(uint32_t instance, usb_core_phy_chep_t phy_ch_num,
                                                 usb_drd_db_status_t db_status);

usb_core_status_t USB_DRD_InitChannel(uint32_t instance, usb_core_ch_t *p_ch);
usb_core_status_t USB_DRD_CloseChannel(uint32_t instance, usb_core_ch_t *p_ch);
usb_core_status_t USB_DRD_HaltInChannel(uint32_t instance, usb_core_phy_chep_t phy_ch_num);
usb_core_status_t USB_DRD_HaltOutChannel(uint32_t instance, usb_core_phy_chep_t phy_ch_num);
usb_core_status_t USB_DRD_HaltChannel(uint32_t instance, const usb_core_ch_t *p_ch);
usb_core_status_t USB_DRD_StartChannelXfer(uint32_t instance, usb_core_ch_t *p_ch);
usb_core_status_t USB_DRD_PMAReset(void);
usb_core_port_speed_t USB_DRD_GetHostPortSpeed(uint32_t instance);
usb_core_channel_t USB_DRD_GetLogicalChannel(usb_core_phy_chep_t phy_ch_num, usb_core_ch_direction_t ch_dir);
void     USB_DRD_ClearPhysicalChannels(void);
uint32_t USB_DRD_GetCurrentFrame(uint32_t instance);
uint32_t USB_DRD_GetDmaStatus(uint32_t instance);
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

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* STM32U5xx_USB_DRD_CORE_H */
