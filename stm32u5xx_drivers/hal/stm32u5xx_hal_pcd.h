/**
  ******************************************************************************
  * @file    stm32u5xx_hal_pcd.h
  * @brief   Header file of PCD HAL module.
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
#ifndef STM32U5xx_HAL_PCD_H
#define STM32U5xx_HAL_PCD_H

#ifdef __cplusplus
extern "C" {
#endif /* defined __cplusplus */

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup PCD PCD
  * @{
  */
/* Includes ------------------------------------------------------------------*/
#if defined (USB_OTG_FS) || defined (USB_OTG_HS) || defined (USB_DRD_FS)
#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
#include "stm32u5xx_usb_otg_core.h"
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */
#if defined (USB_DRD_FS)
#include "stm32u5xx_usb_drd_core.h"
#endif /* defined (USB_DRD_FS) */

/* Private constants ---------------------------------------------------------*/
/** @defgroup PCD_Private_Constants PCD Private Constants
  * @{
  */

/**
  * @brief  USE HAL PCD USB EP TYPE ISOC
  */
#ifndef USE_HAL_PCD_USB_EP_TYPE_ISOC
#define USE_HAL_PCD_USB_EP_TYPE_ISOC                                         1U
#endif /* USE_HAL_PCD_USB_EP_TYPE_ISOC */

/**
  * @brief  USE HAL PCD USB BCD
  */
#ifndef USE_HAL_PCD_USB_BCD
#define USE_HAL_PCD_USB_BCD                                                  1U
#endif /* USE_HAL_PCD_USB_BCD */

/**
  * @brief  USE HAL PCD USB LPM
  */
#ifndef USE_HAL_PCD_USB_LPM
#define USE_HAL_PCD_USB_LPM                                                  1U
#endif /* USE_HAL_PCD_USB_LPM */

/**
  * @brief  USE HAL PCD USB DOUBLE BUFFER
  */
#ifndef USE_HAL_PCD_USB_DOUBLE_BUFFER
#define USE_HAL_PCD_USB_DOUBLE_BUFFER                                        1U
#endif /* USE_HAL_PCD_USB_DOUBLE_BUFFER */

/**
  * @brief  USE HAL PCD MAX ENDPOINT NB
  */
#ifndef USE_HAL_PCD_MAX_ENDPOINT_NB
#define USE_HAL_PCD_MAX_ENDPOINT_NB                                         16U
#endif /* HAL_PCD_MAX_ENDPOINT_NB */
/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup PCD_Exported_Types PCD Exported Types
  * @{
  */

/**
  * @brief PCD Defined IP Options
  */
typedef enum
{
#if defined (USB_OTG_FS)
  HAL_PCD_OTG_FS = (uint32_t)USB_OTG_FS, /*!< USB OTG FS IP */
#endif /* defined (USB_OTG_FS) */
#if defined (USB_OTG_HS)
  HAL_PCD_OTG_HS = (uint32_t)USB_OTG_HS, /*!< USB OTG HS IP */
#endif /* defined (USB_OTG_HS) */
#if defined (USB_DRD_FS)
  HAL_PCD_DRD_FS = (uint32_t)USB_DRD_FS, /*!< USB DRD FS IP */
#endif /* defined (USB_DRD_FS) */
} hal_pcd_t;


/**
  * @brief  PCD State structure definition
  */
typedef enum
{
  HAL_PCD_STATE_RESET     = 0x00U,         /*!< HAL PCD STATE RESET */
  HAL_PCD_STATE_INIT      = (1U << 31U),   /*!< HAL PCD STATE INIT  */
  HAL_PCD_STATE_IDLE      = (1U << 30U),   /*!< HAL PCD STATE IDLE  */
  HAL_PCD_STATE_ACTIVE    = (1U << 29U),   /*!< HAL PCD STATE ACTIVE */
  HAL_PCD_STATE_XFR_ABORT = (1U << 28U),   /*!< HAL PCD STATE TRANSFER ABORT */
  HAL_PCD_STATE_FAULT     = (1U << 27U),   /*!< HAL PCD STATE FAULT */
} hal_pcd_state_t;


/**
  * @brief PCD Device State Options
  */
typedef enum
{
  HAL_PCD_PORT_STATE_DEV_DISCONNECT = (1U << 31U),   /*!< HAL PCD PORT STATE Device DISCONNECT */
  HAL_PCD_PORT_STATE_DEV_CONNECT    = (1U << 30U),   /*!< HAL PCD PORT STATE Device CONNECT    */
  HAL_PCD_PORT_STATE_DEV_RESET      = (1U << 29U),   /*!< HAL PCD PORT STATE Device RESET      */
  HAL_PCD_PORT_STATE_DEV_RUN        = (1U << 28U),   /*!< HAL PCD PORT STATE Device RUN        */
  HAL_PCD_PORT_STATE_DEV_SUSPEND    = (1U << 27U),   /*!< HAL PCD PORT STATE Device SUSPEND    */
  HAL_PCD_PORT_STATE_DEV_RESUME     = (1U << 26U),   /*!< HAL PCD PORT STATE Device RESUME     */
  HAL_PCD_PORT_STATE_DEV_TESTMODE   = (1U << 25U),   /*!< HAL PCD PORT STATE Device TESTMODE   */
} hal_pcd_port_state_t;


#if defined (USE_HAL_PCD_USB_LPM) && (USE_HAL_PCD_USB_LPM == 1)
/**
  * @brief  PCD LPM State structure definition
  */
typedef enum
{
  HAL_PCD_LPM_STATE_L0     = (1U << 31U),   /*!< PCD LPM STATE L0: on      */
  HAL_PCD_LPM_STATE_L1     = (1U << 30U),   /*!< PCD LPM STATE L1: sleep   */
} hal_pcd_lpm_state_t;
#endif /* defined (USE_HAL_PCD_USB_LPM) && (USE_HAL_PCD_USB_LPM == 1) */


/**
  * @brief  PCD LPM message structure definition
  */
typedef enum
{
  HAL_PCD_LPM_L0_ACTIVE = 0x00U, /*!< PCD LPM ACTIVE STATE L0: on    */
  HAL_PCD_LPM_L1_ACTIVE = 0x01U, /*!< PCD LPM ACTIVE STATE L1: sleep */
} hal_pcd_lpm_active_status_t;


/**
  * @brief  PCD BCD State structure definition
  */
typedef enum
{
  HAL_PCD_BCD_STD_DOWNSTREAM_PORT       = USB_CORE_BCD_PORT_STATUS_STD_DOWNSTREAM,        /*!< PCD BCD STANDARD DOWNSTREAM PORT */
  HAL_PCD_BCD_CHARGING_DOWNSTREAM_PORT  = USB_CORE_BCD_PORT_STATUS_CHARGING_DOWNSTREAM,   /*!< PCD BCD CHARGING DOWNSTREAM PORT */
  HAL_PCD_BCD_DEDICATED_CHARGING_PORT   = USB_CORE_BCD_PORT_STATUS_DEDICATED_CHARGING,    /*!< PCD BCD DEDICATED CHARGING PORT  */
  HAL_PCD_BCD_DISCOVERY_COMPLETED       = 0xFEU,                                          /*!< PCD BCD DISCOVERY COMPLETED      */
  HAL_PCD_BCD_ERROR                     = 0xFFU,                                          /*!< PCD BCD ERROR                    */
} hal_pcd_bcd_port_type_t;


#if defined (USE_HAL_PCD_USB_BCD) && (USE_HAL_PCD_USB_BCD == 1)
/**
  * @brief  BCD Structure definition
  */
typedef enum
{
  HAL_PCD_BCD_PORT_STATUS_DEFAULT             = USB_CORE_BCD_PORT_STATUS_DEFAULT,               /*!< USB PCD Default BCD Status Port  */
  HAL_PCD_BCD_PORT_STATUS_NOT_STD_DOWNSTREAM  = USB_CORE_BCD_PORT_STATUS_NOT_STD_DOWNSTREAM,    /*!< USB PCD NOT STD Downstream Port  */
  HAL_PCD_BCD_PORT_STATUS_STD_DOWNSTREAM      = USB_CORE_BCD_PORT_STATUS_STD_DOWNSTREAM,        /*!< USB PCD STD Downstream Port      */
  HAL_PCD_BCD_PORT_STATUS_DEDICATED_CHARGING  = USB_CORE_BCD_PORT_STATUS_DEDICATED_CHARGING,    /*!< USB PCD Dedicated Charging Port  */
  HAL_PCD_BCD_PORT_STATUS_CHARGING_DOWNSTREAM = USB_CORE_BCD_PORT_STATUS_CHARGING_DOWNSTREAM,   /*!< USB PCD Charging Downstream Port */
} hal_pcd_bcd_port_status_t;
#endif /* defined (USE_HAL_PCD_USB_BCD) && (USE_HAL_PCD_USB_BCD == 1) */


/**
  * @brief  USB PCD Speed structure definition
  */
typedef enum
{
  HAL_PCD_SPEED_FS       = USB_CORE_SPEED_FS,         /*!< HAL PCD SPEED FULL SPEED               */
  HAL_PCD_SPEED_HS       = USB_CORE_SPEED_HS,         /*!< HAL PCD SPEED HIDH SPEED               */
  HAL_PCD_SPEED_HS_IN_FS = USB_CORE_SPEED_HS_IN_FS,   /*!< HAL PCD SPEED HIGH SPEED IN FULL SPEED */
} hal_pcd_speed_t;


/**
  * @brief  USB PCD Device Speed structure definition
  */
typedef enum
{
  HAL_PCD_DEVICE_SPEED_FS    = USB_CORE_DEVICE_SPEED_FS,            /*!< HAL PCD DEVICE FULL SPEED    */
  HAL_PCD_DEVICE_SPEED_HS    = USB_CORE_DEVICE_SPEED_HS,            /*!< HAL PCD DEVICE HIGH SPEED    */
  HAL_PCD_DEVICE_SPEED_ERROR = USB_CORE_DEVICE_SPEED_ERROR          /*!< HAL PCD DEVICE SPEED ERROR   */
} hal_pcd_device_speed_t;


/**
  * @brief  PCD USB PHY Module structure definition
  */
typedef enum
{
  HAL_PCD_PHY_EXTERNAL_ULPI = USB_CORE_PHY_EXTERNAL_ULPI,   /*!< PCD PHY ULPI     */
  HAL_PCD_PHY_EMBEDDED_FS   = USB_CORE_PHY_EMBEDDED_FS,     /*!< PCD PHY EMBEDDED */
  HAL_PCD_PHY_EMBEDDED_HS   = USB_CORE_PHY_EMBEDDED_HS,     /*!< PCD PHY UTMI     */
} hal_pcd_phy_module_t;


/**
  * @brief  HAL PCD USB DMA status definition
  */
typedef enum
{
  HAL_PCD_DMA_DISABLED = USB_CORE_CONFIG_DISABLED,   /*!< HAL PCD DMA DISABLED */
  HAL_PCD_DMA_ENABLED  = USB_CORE_CONFIG_ENABLED,    /*!< HAL PCD DMA ENABLED  */
} hal_pcd_dma_status_t;


/**
  * @brief  HAL PCD USB SOF status definition
  */
typedef enum
{
  HAL_PCD_SOF_DISABLED = USB_CORE_CONFIG_DISABLED,   /*!< HAL PCD SOF DISABLED */
  HAL_PCD_SOF_ENABLED  = USB_CORE_CONFIG_ENABLED,    /*!< HAL PCD SOF ENABLED  */
} hal_pcd_sof_status_t;


/**
  * @brief  HAL PCD USB Low Power Management status definition
  */
typedef enum
{
  HAL_PCD_LPM_DISABLED = USB_CORE_CONFIG_DISABLED,   /*!< HAL PCD Low Power Management DISABLED */
  HAL_PCD_LPM_ENABLED  = USB_CORE_CONFIG_ENABLED,    /*!< HAL PCD Low Power Management ENABLED  */
} hal_pcd_lpm_status_t;


/**
  * @brief  HAL PCD USB Battery Charging status definition
  */
typedef enum
{
  HAL_PCD_BCD_DISABLED = USB_CORE_CONFIG_DISABLED,   /*!< HAL PCD USB Battery Charging DISABLED */
  HAL_PCD_BCD_ENABLED  = USB_CORE_CONFIG_ENABLED,    /*!< HAL PCD USB Battery Charging ENABLED  */
} hal_pcd_bcd_status_t;


/**
  * @brief  HAL PCD USB Vbus Sensing status definition
  */
typedef enum
{
  HAL_PCD_VBUS_SENSE_DISABLED = USB_CORE_CONFIG_DISABLED,   /*!< HAL PCD USB Vbus sensing DISABLED */
  HAL_PCD_VBUS_SENSE_ENABLED  = USB_CORE_CONFIG_ENABLED,    /*!< HAL PCD USB Vbus sensing ENABLED  */
} hal_pcd_vbus_sense_status_t;


/**
  * @brief  HAL PCD USB Dedicated EP1 status definition
  */
typedef enum
{
  HAL_PCD_DEDICATED_EP1_DISABLED = USB_CORE_CONFIG_DISABLED,   /*!< HAL PCD USB Dedicated EP1 DISABLED */
  HAL_PCD_DEDICATED_EP1_ENABLED  = USB_CORE_CONFIG_ENABLED,    /*!< HAL PCD USB Dedicated EP1 ENABLED  */
} hal_pcd_dedicated_ep1_status_t;


/**
  * @brief  HAL PCD USB bulk double buffer status definition
  */
typedef enum
{
  HAL_PCD_BULK_DB_DISABLED = USB_CORE_CONFIG_DISABLED,   /*!< HAL PCD USB Bulk Double buffer mode DISABLED */
  HAL_PCD_BULK_DB_ENABLED  = USB_CORE_CONFIG_ENABLED,    /*!< HAL PCD USB Bulk Double buffer mode ENABLED  */
} hal_pcd_bulk_db_status_t;


/**
  * @brief  PCD EP Kind structure definition
  */
typedef enum
{
  HAL_PCD_SNG_BUF = 0x00U,   /*!< PCD SINGLE BUFFER */
  HAL_PCD_DBL_BUF = 0x01U,   /*!< PCD DOUBLE BUFFER */
} hal_pcd_ep_kind_t;


/**
  * @brief  PCD USB Test Mode Type structure definition
  */
typedef enum
{
  HAL_PCD_HSET_J        = USB_CORE_HSET_J,           /*!< PCD High Speed Electrical TEST J            */
  HAL_PCD_HSET_K        = USB_CORE_HSET_K,           /*!< PCD High Speed Electrical TEST K            */
  HAL_PCD_HSET_SE0_NAK  = USB_CORE_HSET_SE0_NAK,     /*!< PCD High Speed Electrical TEST SE0 NAK      */
  HAL_PCD_HSET_PACKET   = USB_CORE_HSET_PACKET,      /*!< PCD High Speed Electrical TEST PACKET       */
  HAL_PCD_HSET_FORCE_EN = USB_CORE_HSET_FORCE_EN,    /*!< PCD High Speed Electrical TEST FORCE ENABLE */
} hal_pcd_hset_t;


/**
  * @brief  PCD EP Type structure definition
  */
typedef enum
{
  HAL_PCD_EP_TYPE_CTRL = USB_CORE_EP_TYPE_CTRL,
  HAL_PCD_EP_TYPE_ISOC = USB_CORE_EP_TYPE_ISOC,
  HAL_PCD_EP_TYPE_BULK = USB_CORE_EP_TYPE_BULK,
  HAL_PCD_EP_TYPE_INTR = USB_CORE_EP_TYPE_INTR,
} hal_pcd_ep_type_t;


/**
  * @brief  USB CORE Endpoint Direction definition
  */
typedef enum
{
  HAL_PCD_EP_OUT_DIR = USB_CORE_EP_OUT_DIR,      /*!< HAL_PCD Endpoint OUT DIR: 0 */
  HAL_PCD_EP_IN_DIR  = USB_CORE_EP_IN_DIR,       /*!< HAL_PCD Endpoint IN DIR:  1 */
} hal_pcd_ep_direction_t;


/**
  * @brief  USB Instance Initialization Structure definition
  */
typedef struct
{
  hal_pcd_dma_status_t dma_enable;                         /*!< USB DMA state.                                        */

  hal_pcd_speed_t pcd_speed;                               /*!< USB pcd Core speed.                                   */

  hal_pcd_phy_module_t phy_interface;                      /*!< Select the used PHY interface.                        */

  hal_pcd_sof_status_t Sof_enable;                         /*!< Enable/disable the output of the SOF signal.          */

  hal_pcd_lpm_status_t lpm_enable;                         /*!< Enable/disable Link Power Management.                 */

  hal_pcd_bcd_status_t battery_charging_enable;            /*!< Enable/disable Battery charging.                      */

  hal_pcd_vbus_sense_status_t vbus_sensing_enable;         /*!< Enable/disable VBUS Sensing feature.                  */

  hal_pcd_dedicated_ep1_status_t use_dedicated_ep1_enable; /*!< Enable/disable use of the dedicated EP1 interrupt.    */

#if defined (USB_DRD_FS)
  hal_pcd_bulk_db_status_t bulk_doublebuffer_enable;       /*!< Enable/disable the double buffer mode on bulk EP      */
#endif /* defined (USB_DRD_FS) */
} hal_pcd_config_t;

typedef usb_core_ep_t             hal_pcd_ep_t;     /*!< PCD endpoint structure type */
typedef struct hal_pcd_handle_s   hal_pcd_handle_t; /*!< PCD handle structure type */

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
/**
  * @brief pointer to a PCD callback function
  */
typedef void (*hal_pcd_cb_t)(hal_pcd_handle_t *hpcd);

/**
  * @brief pointer to a data callback function
  */
typedef void (*hal_pcd_data_cb_t)(hal_pcd_handle_t *hpcd, uint8_t ep_num);

/**
  * @brief pointer to an iso callback function
  */
typedef void (*hal_pcd_iso_cb_t)(hal_pcd_handle_t *hpcd, uint8_t ep_num);

/**
  * @brief pointer to an LPM callback function
  */
typedef void (*hal_pcd_lpm_cb_t)(hal_pcd_handle_t *hpcd, hal_pcd_lpm_active_status_t lpm_status);

/**
  * @brief pointer to a BCD callback function
  */
typedef void (*hal_pcd_bcd_cb_t)(hal_pcd_handle_t *hpcd, hal_pcd_bcd_port_type_t port_type);

#endif /* (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U) */


/**
  * @brief  PCD Handle Structure definition
  */
struct hal_pcd_handle_s
{
  hal_pcd_t instance;                                      /*!< Register base address                                 */
  volatile hal_pcd_state_t global_state;                   /*!< PCD communication state                               */
  volatile hal_pcd_port_state_t device_state;              /*!< PCD Port Device state                                 */

#if defined (USE_HAL_PCD_USB_LPM) && (USE_HAL_PCD_USB_LPM == 1)
  volatile hal_pcd_lpm_state_t lpm_state;                  /*!< LPM State                                             */
#endif /* defined (USE_HAL_PCD_USB_LPM) && (USE_HAL_PCD_USB_LPM == 1) */
  volatile uint8_t usb_address;                            /*!< USB Device Address                                    */

#if defined (USE_HAL_PCD_GET_LAST_ERRORS) && (USE_HAL_PCD_GET_LAST_ERRORS == 1)
  volatile uint32_t last_error_codes;                      /*!< Errors limited to the last process
                                                                This parameter can be a combination of
                                                                @ref PCD_Error_Codes                                  */
#endif /* USE_HAL_PCD_GET_LAST_ERRORS */

  uint8_t endpoints_nbr;                                   /*!< Device Endpoints number.
                                                                This parameter depends on the used USB core.          */

  uint32_t setup[12];                                      /*!< Setup packet buffer                                   */

  hal_pcd_ep_t in_ep[USE_HAL_PCD_MAX_ENDPOINT_NB];         /*!< IN endpoint parameters                                */
  hal_pcd_ep_t out_ep[USE_HAL_PCD_MAX_ENDPOINT_NB];        /*!< OUT endpoint parameters                               */

  usb_core_mode_t current_mode;                            /*!< store Current Mode                                    */
  hal_pcd_dedicated_ep1_status_t use_dedicated_ep1;        /*!< Enable or disable the use of the dedicated EP1
                                                                interrupt.                                            */

  hal_pcd_lpm_status_t lpm_active;                         /*!< Enable or disable the Link Power Management .
                                                                This parameter can be set to ENABLE or DISABLE        */
  uint32_t lpm_besl;                                       /*!< Best Effort Service Latency                           */

  hal_pcd_bcd_status_t battery_charging_active;            /*!< Enable or disable Battery charging.
                                                                This parameter can be set to ENABLE or DISABLE        */

  usb_core_pcd_driver_t driver;                            /*!< USB low layer driver                                  */
  void (* p_irq_handler)(struct hal_pcd_handle_s *hpcd);   /*!< USB instance interrupt handler                        */

#if defined (USE_HAL_PCD_USER_DATA) && (USE_HAL_PCD_USER_DATA == 1)
  const void *p_user_data;                                 /*!< User Data Pointer                                     */
#endif /* USE_HAL_PCD_USER_DATA */

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)

  hal_pcd_cb_t p_sof_cb;                                   /*!< USB HAL PCD SOF callback                              */
  hal_pcd_cb_t p_setup_stage_cb;                           /*!< USB HAL PCD Setup Stage callback                      */
  hal_pcd_cb_t p_reset_cb;                                 /*!< USB HAL PCD Reset callback                            */
  hal_pcd_cb_t p_suspend_cb;                               /*!< USB HAL PCD Suspend callback                          */
  hal_pcd_cb_t p_resume_cb;                                /*!< USB HAL PCD Resume callback                           */
  hal_pcd_cb_t p_connect_cb;                               /*!< USB HAL PCD Connect callback                          */
  hal_pcd_cb_t p_disconnect_cb;                            /*!< USB HAL PCD Disconnect callback                       */
  hal_pcd_data_cb_t p_data_out_stage_cb;                   /*!< USB HAL PCD Data OUT Stage callback                   */
  hal_pcd_data_cb_t p_data_in_stage_cb;                    /*!< USB HAL PCD Data IN Stage callback                    */
  hal_pcd_iso_cb_t p_iso_out_incomplete_cb;                /*!< USB HAL PCD ISO OUT Incomplete callback               */
  hal_pcd_iso_cb_t p_iso_in_incomplete_cb;                 /*!< USB HAL PCD ISO IN Incomplete callback                */
  hal_pcd_cb_t p_error_cb;                                 /*!< USB HAL PCD Error callback                            */
  hal_pcd_bcd_cb_t p_battery_charging_cb;                  /*!< USB HAL PCD Battery charging callback                 */
  hal_pcd_lpm_cb_t p_low_power_management_cb;              /*!< USB HAL PCD USB Link Power management callback        */
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
};

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup PCD_Exported_Constants PCD Exported Constants
  * @{
  */
#if defined (USE_HAL_PCD_GET_LAST_ERRORS) && (USE_HAL_PCD_GET_LAST_ERRORS == 1)
/** @defgroup PCD_Error_Codes PCD Error Codes
  * @{
  */
#define  HAL_PCD_ERROR_NONE                          0x0U     /*!< No error                   */
#define  HAL_PCD_ERROR_BCD                           0x1U     /*!< USB Battery Charging error */
#define  HAL_PCD_ERROR_IN_EP_AHB                     0x2U     /*!< USB IN EP AHB error        */
#define  HAL_PCD_ERROR_IN_EP_TIMEOUT                 0x3U     /*!< USB IN EP TIMEOUT error    */
#define  HAL_PCD_ERROR_IN_EP_BABBLE                  0x4U     /*!< USB IN EP BABBLE error     */
#define  HAL_PCD_ERROR_OUT_EP_AHB                    0x5U     /*!< USB OUT EP AHB error       */
#define  HAL_PCD_ERROR_OUT_EP_PACKET                 0x6U     /*!< USB OUT EP PACKET  error   */
/**
  * @}
  */
#endif /* USE_HAL_PCD_GET_LAST_ERRORS */
#define HAL_PCD_EP_ADDR_MSK                          0x7FU     /*!< Endpoint Address Mask      */
/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup PCD_Exported_Macros PCD Exported Macros
  *  @brief macros to handle interrupts and specific clock configurations
  * @{
  */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PCD_Exported_Functions PCD Exported Functions
  * @{
  */

/* Initialization/de-initialization functions  ********************************/
/** @defgroup PCD_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_PCD_Init(hal_pcd_handle_t *hpcd, hal_pcd_t instance);
void         HAL_PCD_DeInit(hal_pcd_handle_t *hpcd);
/**
  * @}
  */
/** @defgroup PCD_Exported_Functions_Group2 Global Configuration functions
  * @{
  */
hal_status_t HAL_PCD_SetConfig(hal_pcd_handle_t *hpcd, const hal_pcd_config_t *p_config);

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
/* Register callbacks */
hal_status_t HAL_PCD_RegisterSofCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback);
hal_status_t HAL_PCD_RegisterSetupCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback);
hal_status_t HAL_PCD_RegisterResetCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback);
hal_status_t HAL_PCD_RegisterSuspendCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback);
hal_status_t HAL_PCD_RegisterResumeCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback);
hal_status_t HAL_PCD_RegisterConnectCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback);
hal_status_t HAL_PCD_RegisterDisconnectCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback);
hal_status_t HAL_PCD_RegisterDataOutStageCallback(hal_pcd_handle_t *hpcd, hal_pcd_data_cb_t p_callback);
hal_status_t HAL_PCD_RegisterDataInStageCallback(hal_pcd_handle_t *hpcd, hal_pcd_data_cb_t p_callback);
hal_status_t HAL_PCD_RegisterIsoOutIncpltCallback(hal_pcd_handle_t *hpcd, hal_pcd_iso_cb_t p_callback);
hal_status_t HAL_PCD_RegisterIsoInIncpltCallback(hal_pcd_handle_t *hpcd, hal_pcd_iso_cb_t p_callback);
hal_status_t HAL_PCD_RegisterErrorCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback);
hal_status_t HAL_PCD_RegisterBcdCallback(hal_pcd_handle_t *hpcd, hal_pcd_bcd_cb_t p_callback);
hal_status_t HAL_PCD_RegisterLpmCallback(hal_pcd_handle_t *hpcd, hal_pcd_lpm_cb_t p_callback);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

#if defined (USE_HAL_PCD_GET_LAST_ERRORS) && (USE_HAL_PCD_GET_LAST_ERRORS == 1)
uint32_t HAL_PCD_GetLastErrorCodes(const hal_pcd_handle_t *hpcd);
#endif /* USE_HAL_PCD_GET_LAST_ERRORS */
/**
  * @}
  */

/** @defgroup PCD_Exported_Functions_Group3 Input and Output operation functions
  * @{
  */
void HAL_PCD_IRQHandler(hal_pcd_handle_t *hpcd);
#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
void HAL_PCD_OTG_IRQHandler(hal_pcd_handle_t *hpcd);
hal_status_t HAL_PCD_SetTxFiFoSize(const hal_pcd_handle_t *hpcd, uint8_t fifo, uint16_t size_words);
hal_status_t HAL_PCD_SetRxFiFoSize(const hal_pcd_handle_t *hpcd, uint16_t size_words);
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */

#if defined (USB_DRD_FS)
void HAL_PCD_DRD_IRQHandler(hal_pcd_handle_t *hpcd);
hal_status_t HAL_PCD_PMAConfig(hal_pcd_handle_t *hpcd, uint16_t ep_addr, uint16_t ep_kind, uint32_t pma_adress);
#endif /* defined (USB_DRD_FS) */

hal_status_t HAL_PCD_Start(hal_pcd_handle_t *hpcd);
hal_status_t HAL_PCD_Stop(hal_pcd_handle_t *hpcd);

void HAL_PCD_SofCallback(hal_pcd_handle_t *hpcd);
void HAL_PCD_SetupStageCallback(hal_pcd_handle_t *hpcd);
void HAL_PCD_ResetCallback(hal_pcd_handle_t *hpcd);
void HAL_PCD_SuspendCallback(hal_pcd_handle_t *hpcd);
void HAL_PCD_ResumeCallback(hal_pcd_handle_t *hpcd);
void HAL_PCD_ConnectCallback(hal_pcd_handle_t *hpcd);
void HAL_PCD_DisconnectCallback(hal_pcd_handle_t *hpcd);
void HAL_PCD_DataOutStageCallback(hal_pcd_handle_t *hpcd, uint8_t ep_num);
void HAL_PCD_DataInStageCallback(hal_pcd_handle_t *hpcd, uint8_t ep_num);
void HAL_PCD_ISOOUTIncompleteCallback(hal_pcd_handle_t *hpcd, uint8_t ep_num);
void HAL_PCD_ISOINIncompleteCallback(hal_pcd_handle_t *hpcd, uint8_t ep_num);
void HAL_PCD_LpmCallback(hal_pcd_handle_t *hpcd, hal_pcd_lpm_active_status_t lpm_status);
void HAL_PCD_BcdCallback(hal_pcd_handle_t *hpcd, hal_pcd_bcd_port_type_t port_type);

#if defined (USE_HAL_PCD_USB_LPM) && (USE_HAL_PCD_USB_LPM == 1)
hal_status_t HAL_PCD_LPM_Start(hal_pcd_handle_t *hpcd);
hal_status_t HAL_PCD_LPM_Stop(hal_pcd_handle_t *hpcd);
#endif /* defined (USE_HAL_PCD_USB_LPM) && (USE_HAL_PCD_USB_LPM == 1) */


#if defined (USE_HAL_PCD_USB_BCD) && (USE_HAL_PCD_USB_BCD == 1)
hal_status_t HAL_PCD_BCD_PortTypeDetection(hal_pcd_handle_t *hpcd);
hal_status_t HAL_PCD_BCD_Start(hal_pcd_handle_t *hpcd);
hal_status_t HAL_PCD_BCD_Stop(hal_pcd_handle_t *hpcd);
#endif /* defined (USE_HAL_PCD_USB_BCD) && (USE_HAL_PCD_USB_BCD == 1) */

/**
  * @}
  */

/* Peripheral Control functions  **********************************************/
/** @defgroup PCD_Exported_Functions_Group4 Peripheral Control functions
  * @{
  */
hal_status_t HAL_PCD_DeviceConnect(const hal_pcd_handle_t *hpcd);
hal_status_t HAL_PCD_DeviceDisconnect(const hal_pcd_handle_t *hpcd);
hal_pcd_device_speed_t HAL_PCD_GetDeviceSpeed(const hal_pcd_handle_t *hpcd);
hal_status_t HAL_PCD_SetDeviceAddress(hal_pcd_handle_t *hpcd, uint8_t address);
hal_status_t HAL_PCD_OpenEndpoint(hal_pcd_handle_t *hpcd, uint8_t ep_addr, uint16_t ep_mps, hal_pcd_ep_type_t ep_type);
hal_status_t HAL_PCD_CloseEndpoint(hal_pcd_handle_t *hpcd, uint8_t ep_addr);
hal_status_t HAL_PCD_FlushEndpoint(const hal_pcd_handle_t *hpcd, uint8_t ep_addr);

hal_status_t HAL_PCD_SetEndpointReceive(hal_pcd_handle_t *hpcd, uint8_t ep_addr, uint8_t *p_buffer, uint32_t size_byte);
hal_status_t HAL_PCD_SetEndpointTransmit(hal_pcd_handle_t *hpcd, uint8_t ep_addr,
                                         uint8_t *p_buffer, uint32_t size_byte);

hal_status_t HAL_PCD_SetEndpointStall(hal_pcd_handle_t *hpcd, uint8_t ep_addr);
hal_status_t HAL_PCD_ClearEndpointStall(hal_pcd_handle_t *hpcd, uint8_t ep_addr);
hal_status_t HAL_PCD_AbortEndpointTransfer(hal_pcd_handle_t *hpcd, uint8_t ep_addr);

hal_status_t HAL_PCD_RemoteWakeup_Start(const hal_pcd_handle_t *hpcd);
hal_status_t HAL_PCD_RemoteWakeup_Stop(const hal_pcd_handle_t *hpcd);

#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
hal_status_t HAL_PCD_SetDeviceTestMode(hal_pcd_handle_t *hpcd, hal_pcd_hset_t test_mode);
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */

uint32_t HAL_PCD_EP_GetRxCount(const hal_pcd_handle_t *hpcd, uint8_t ep_addr);
/**
  * @}
  */

/* Peripheral State functions  ************************************************/
/** @defgroup PCD_Exported_Functions_Group5 Peripheral State functions
  * @{
  */
hal_pcd_state_t HAL_PCD_GetState(const hal_pcd_handle_t *hpcd);
void HAL_PCD_ErrorCallback(hal_pcd_handle_t *hpcd);
/**
  * @}
  */
#if defined (USE_HAL_PCD_USER_DATA) && (USE_HAL_PCD_USER_DATA == 1)
/** @defgroup PCD_Exported_Functions_Group6 Set/Get user data
  * @{
  */
void        HAL_PCD_SetUserData(hal_pcd_handle_t *hpcd, const void *p_user_data);
const void *HAL_PCD_GetUserData(const hal_pcd_handle_t *hpcd);
/**
  * @}
  */
#endif /* USE_HAL_PCD_USER_DATA */

/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/
/** @defgroup PCD_Private_Constants PCD Private Constants
  * @{
  */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup PCD_Private_Macros PCD Private Macros
  * @{
  */
/**
  * @}
  */
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) || defined (USB_DRD_FS) */

/**
  * @}
  */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* defined __cplusplus */

#endif /* STM32U5xx_HAL_PCD_H */
