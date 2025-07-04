/**
  ******************************************************************************
  * @file    stm32u5xx_hal_dsi.h
  * @brief   Header file of DSI HAL module.
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
#ifndef STM32U5XX_HAL_DSI_H
#define STM32U5XX_HAL_DSI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

#if defined(DSI)

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup DSI DSI
  * @brief DSI HAL module driver
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup DSI_Exported_Constants DSI Exported Constants
  * @{
  */

#define HAL_DSI_MAX_RETURN_PKT_SIZE (0x00000037U) /*!< Maximum return packet configuration */

#if defined (USE_HAL_DSI_GET_LAST_ERRORS) && (USE_HAL_DSI_GET_LAST_ERRORS == 1)
/** @defgroup DSI_Error_Data_Type DSI Error Data Type
  * @{
  */
#define HAL_DSI_ERROR_NONE              0U                               /*!< No error                       */
#define HAL_DSI_ERROR_ACK               (DSI_ISR0_AE0   \
                                         | DSI_ISR0_AE1 \
                                         | DSI_ISR0_AE2 \
                                         | DSI_ISR0_AE3 \
                                         | DSI_ISR0_AE4 \
                                         | DSI_ISR0_AE5 \
                                         | DSI_ISR0_AE6 \
                                         | DSI_ISR0_AE7 \
                                         | DSI_ISR0_AE8 \
                                         | DSI_ISR0_AE9 \
                                         | DSI_ISR0_AE10 \
                                         | DSI_ISR0_AE11 \
                                         | DSI_ISR0_AE12 \
                                         | DSI_ISR0_AE13 \
                                         | DSI_ISR0_AE14 \
                                         | DSI_ISR0_AE15)                /*!< Acknowledge errors             */

#define HAL_DSI_ERROR_TX                DSI_ISR1_TOHSTX                  /*!< Transmission error             */
#define HAL_DSI_ERROR_RX                DSI_ISR1_TOLPRX                  /*!< Reception error                */
#define HAL_DSI_ERROR_CRC               DSI_ISR1_CRCE                    /*!< CRC error                      */
#define HAL_DSI_ERROR_PSE               DSI_ISR1_PSE                     /*!< Packet Size error              */
#define HAL_DSI_ERROR_EOT               DSI_ISR1_EOTPE                   /*!< End Of Transmission error      */
#define HAL_DSI_ERROR_OVF               DSI_ISR1_LPWRE                   /*!< FIFO overflow error            */
#define HAL_DSI_ERROR_PBU               DSI_ISR1_PBUE                    /*!< Payload Buffer Underflow error */
#define HAL_DSI_ERROR_ECC              (DSI_ISR1_ECCSE | DSI_ISR1_ECCME) /*!< ECC errors                     */
#define HAL_DSI_ERROR_PHY              (DSI_ISR0_PE0 | DSI_ISR0_PE1   \
                                        | DSI_ISR0_PE2 | DSI_ISR0_PE3 \
                                        | DSI_ISR0_PE4)                  /*!< PHY related errors             */
#define HAL_DSI_ERROR_GEN              (DSI_ISR1_GCWRE | DSI_ISR1_GPWRE   \
                                        | DSI_ISR1_GPTXE | DSI_ISR1_GPRDE \
                                        | DSI_ISR1_GPRXE)                /*!< Generic FIFO related errors    */

/**
  * @}
  */
#endif /* USE_HAL_DSI_GET_LAST_ERRORS */
/** @defgroup DSI_Interrupt DSI Interrupts
  * @{
  */
#define HAL_DSI_IT_TE                   DSI_WIER_TEIE   /*!< DSI Tearing effect Interrupt */
#define HAL_DSI_IT_ER                   DSI_WIER_ERIE   /*!< End of Refresh Interrupt     */
#define HAL_DSI_IT_PLLL                 DSI_WIER_PLLLIE /*!< PLL Lock Interrupt           */
#define HAL_DSI_IT_PLLU                 DSI_WIER_PLLUIE /*!< PLL Unlock Interrupt         */

#define HAL_DSI_IT_NONE              0U                 /*!< No interrupt                 */
#define HAL_DSI_IT_ACK              (DSI_IER0_AE0IE    \
                                     | DSI_IER0_AE1IE  \
                                     | DSI_IER0_AE2IE  \
                                     | DSI_IER0_AE3IE  \
                                     | DSI_IER0_AE4IE  \
                                     | DSI_IER0_AE5IE  \
                                     | DSI_IER0_AE6IE  \
                                     | DSI_IER0_AE7IE  \
                                     | DSI_IER0_AE8IE  \
                                     | DSI_IER0_AE9IE  \
                                     | DSI_IER0_AE10IE \
                                     | DSI_IER0_AE11IE \
                                     | DSI_IER0_AE12IE \
                                     | DSI_IER0_AE13IE \
                                     | DSI_IER0_AE14IE \
                                     | DSI_IER0_AE15IE)                 /*!< Acknowledge errors interrupts            */

#define HAL_DSI_IT_TX                DSI_IER1_TOHSTXIE                  /*!< Transmission error interrupt             */
#define HAL_DSI_IT_RX                DSI_IER1_TOLPRXIE                  /*!< Reception error interrupt                */
#define HAL_DSI_IT_CRC               DSI_IER1_CRCEIE                    /*!< CRC error interrupt                      */
#define HAL_DSI_IT_PSE               DSI_IER1_PSEIE                     /*!< Packet Size error interrupt              */
#define HAL_DSI_IT_EOT               DSI_IER1_EOTPEIE                   /*!< End Of Transmission error interrupt      */
#define HAL_DSI_IT_OVF               DSI_IER1_LPWREIE                   /*!< FIFO overflow error interrupt            */
#define HAL_DSI_IT_PBU               DSI_IER1_PBUEIE                    /*!< Payload Buffer Underflow error interrupt */
#define HAL_DSI_IT_ECC              (DSI_IER1_ECCSEIE | DSI_IER1_ECCMEIE) /*!< ECC errors interrupts                  */
#define HAL_DSI_IT_PHY              (DSI_IER0_PE0IE | DSI_IER0_PE1IE   \
                                     | DSI_IER0_PE2IE | DSI_IER0_PE3IE \
                                     | DSI_IER0_PE4IE)                  /*!< PHY related errors interrupts            */
#define HAL_DSI_IT_GEN              (DSI_IER1_GCWREIE | DSI_IER1_GPWREIE   \
                                     | DSI_IER1_GPTXEIE | DSI_IER1_GPRDEIE \
                                     | DSI_IER1_GPRXEIE)                /*!< Generic FIFO related errors interrupts   */
/**
  * @}
  */
/** @defgroup DSI_Flags DSI Flags
  * @{
  */
#define HAL_DSI_FLAG_TE                DSI_WISR_TEIF   /*!< DSI Tearing effect Interrupt Flag   */
#define HAL_DSI_FLAG_ER                DSI_WISR_ERIF   /*!< End of Refresh Interrupt Flag       */
#define HAL_DSI_FLAG_BUSY              DSI_WISR_BUSY   /*!< Busy Flag                           */
#define HAL_DSI_FLAG_PLLLS             DSI_WISR_PLLLS  /*!< PLL Lock Status Flag                */
#define HAL_DSI_FLAG_PLLL              DSI_WISR_PLLLIF /*!< PLL Lock Interrupt Flag             */
#define HAL_DSI_FLAG_PLLU              DSI_WISR_PLLUIF /*!< PLL Unlock Interrupt Flag           */


#define HAL_DSI_FLAG_NONE              0U              /*!< No flag                             */
#define HAL_DSI_FLAG_ACK              (DSI_ISR0_AE0    \
                                       | DSI_ISR0_AE1  \
                                       | DSI_ISR0_AE2  \
                                       | DSI_ISR0_AE3  \
                                       | DSI_ISR0_AE4  \
                                       | DSI_ISR0_AE5  \
                                       | DSI_ISR0_AE6  \
                                       | DSI_ISR0_AE7  \
                                       | DSI_ISR0_AE8  \
                                       | DSI_ISR0_AE9  \
                                       | DSI_ISR0_AE10 \
                                       | DSI_ISR0_AE11 \
                                       | DSI_ISR0_AE12 \
                                       | DSI_ISR0_AE13 \
                                       | DSI_ISR0_AE14 \
                                       | DSI_ISR0_AE15)                 /*!< Acknowledge errors Flag             */

#define HAL_DSI_FLAG_TX                DSI_ISR1_TOHSTX                  /*!< Transmission error Flag             */
#define HAL_DSI_FLAG_RX                DSI_ISR1_TOLPRX                  /*!< Reception error  Flag               */
#define HAL_DSI_FLAG_CRC               DSI_ISR1_CRCE                    /*!< CRC error  Flag                     */
#define HAL_DSI_FLAG_PSE               DSI_ISR1_PSE                     /*!< Packet Size error Flag              */
#define HAL_DSI_FLAG_EOT               DSI_ISR1_EOTPE                   /*!< End Of Transmission error Flag      */
#define HAL_DSI_FLAG_OVF               DSI_ISR1_LPWRE                   /*!< FIFO overflow error Flag            */
#define HAL_DSI_FLAG_PBU               DSI_ISR1_PBUE                    /*!< Payload Buffer Underflow error Flag */
#define HAL_DSI_FLAG_ECC              (DSI_ISR1_ECCSE | DSI_ISR1_ECCME) /*!< ECC errors Flag                     */
#define HAL_DSI_FLAG_PHY              (DSI_ISR0_PE0 | DSI_ISR0_PE1   \
                                       | DSI_ISR0_PE2 | DSI_ISR0_PE3 \
                                       | DSI_ISR0_PE4)                  /*!< PHY related errors Flag             */
#define HAL_DSI_FLAG_GEN              (DSI_ISR1_GCWRE | DSI_ISR1_GPWRE   \
                                       | DSI_ISR1_GPTXE | DSI_ISR1_GPRDE \
                                       | DSI_ISR1_GPRXE)                /*!< Generic FIFO related errors Flag    */
/**
  * @}
  */
/** @defgroup DSI_DCS_Command DSI DCS Command
  * @{
  */
#define HAL_DSI_ENTER_IDLE_MODE       0x39U /*!< Enter idle mode                            */
#define HAL_DSI_ENTER_INVERT_MODE     0x21U /*!< Enter invert mode                          */
#define HAL_DSI_ENTER_NORMAL_MODE     0x13U /*!< Enter normal mode                          */
#define HAL_DSI_ENTER_PARTIAL_MODE    0x12U /*!< Enter partial mode                         */
#define HAL_DSI_ENTER_SLEEP_MODE      0x10U /*!< Enter sleep mode                           */
#define HAL_DSI_EXIT_IDLE_MODE        0x38U /*!< Exit idle mode                             */
#define HAL_DSI_EXIT_INVERT_MODE      0x20U /*!< Exit invert mode                           */
#define HAL_DSI_EXIT_SLEEP_MODE       0x11U /*!< Exit sleep mode                            */
#define HAL_DSI_GET_3D_CONTROL        0x3FU /*!< Get 3D control settings                    */
#define HAL_DSI_GET_ADDRESS_MODE      0x0BU /*!< Get address mode                           */
#define HAL_DSI_GET_BLUE_CHANNEL      0x08U /*!< Get blue channel                           */
#define HAL_DSI_GET_DIAGNOSTIC_RESULT 0x0FU /*!< Get diagnostic result                      */
#define HAL_DSI_GET_DISPLAY_MODE      0x0DU /*!< Get display mode                           */
#define HAL_DSI_GET_GREEN_CHANNEL     0x07U /*!< Get green channel                          */
#define HAL_DSI_GET_PIXEL_FORMAT      0x0CU /*!< Get pixel format                           */
#define HAL_DSI_GET_POWER_MODE        0x0AU /*!< Get power mode                             */
#define HAL_DSI_GET_RED_CHANNEL       0x06U /*!< Get red channel                            */
#define HAL_DSI_GET_SCANLINE          0x45U /*!< Get scanline                               */
#define HAL_DSI_GET_SIGNAL_MODE       0x0EU /*!< Get signal mode                            */
#define HAL_DSI_NOP                   0x00U /*!< No operation                               */
#define HAL_DSI_READ_DDB_CONTINUE     0xA8U /*!< Continue reading DDB (Display Data Buffer) */
#define HAL_DSI_READ_DDB_START        0xA1U /*!< Start reading DDB                          */
#define HAL_DSI_READ_MEMORY_CONTINUE  0x3EU /*!< Continue reading memory                    */
#define HAL_DSI_READ_MEMORY_START     0x2EU /*!< Start reading memory                       */
#define HAL_DSI_SET_3D_CONTROL        0x3DU /*!< Set 3D control settings                    */
#define HAL_DSI_SET_ADDRESS_MODE      0x36U /*!< Set address mode                           */
#define HAL_DSI_SET_COLUMN_ADDRESS    0x2AU /*!< Set column address                         */
#define HAL_DSI_SET_DISPLAY_OFF       0x28U /*!< Set display off                            */
#define HAL_DSI_SET_DISPLAY_ON        0x29U /*!< Set display on                             */
#define HAL_DSI_SET_GAMMA_CURVE       0x26U /*!< Set gamma curve                            */
#define HAL_DSI_SET_PAGE_ADDRESS      0x2BU /*!< Set page address                           */
#define HAL_DSI_SET_PARTIAL_COLUMNS   0x31U /*!< Set partial columns                        */
#define HAL_DSI_SET_PARTIAL_ROWS      0x30U /*!< Set partial rows                           */
#define HAL_DSI_SET_PIXEL_FORMAT      0x3AU /*!< Set pixel format                           */
#define HAL_DSI_SET_SCROLL_AREA       0x33U /*!< Set scroll area                            */
#define HAL_DSI_SET_SCROLL_START      0x37U /*!< Set scroll start                           */
#define HAL_DSI_SET_TEAR_OFF          0x34U /*!< Set tearing effect off                     */
#define HAL_DSI_SET_TEAR_ON           0x35U /*!< Set tearing effect on                      */
#define HAL_DSI_SET_TEAR_SCANLINE     0x44U /*!< Set tearing scanline                       */
#define HAL_DSI_SET_VSYNC_TIMING      0x40U /*!< Set VSYNC timing                           */
#define HAL_DSI_SOFT_RESET            0x01U /*!< Perform a software reset                   */
#define HAL_DSI_WRITE_LUT             0x2DU /*!< Write to LUT (Look-Up Table)               */
#define HAL_DSI_WRITE_MEMORY_CONTINUE 0x3CU /*!< Continue writing to memory                 */
#define HAL_DSI_WRITE_MEMORY_START    0x2CU /*!< Start writing to memory                    */
/**
  * @}
  */
/** @defgroup DSI_FlowControl DSI flow Control
  * @{
  */
#define HAL_DSI_FLOW_CONTROL_EOTP_TX_LP DSI_PCR_ETTXLPE /*!< EoTp Transmission in Low-Power enable */
#define HAL_DSI_FLOW_CONTROL_CRC_RX     DSI_PCR_CRCRXE  /*!< CRC reception enable                  */
#define HAL_DSI_FLOW_CONTROL_ECC_RX     DSI_PCR_ECCRXE  /*!< ECC reception enable                  */
#define HAL_DSI_FLOW_CONTROL_BTA        DSI_PCR_BTAE    /*!< Bus-turn-around enable                */
#define HAL_DSI_FLOW_CONTROL_EOTP_RX    DSI_PCR_ETRXE   /*!< EoTp reception enable                 */
#define HAL_DSI_FLOW_CONTROL_EOTP_TX    DSI_PCR_ETTXE   /*!< EoTp transmission enable              */
#define HAL_DSI_FLOW_CONTROL_ALL       (HAL_DSI_FLOW_CONTROL_CRC_RX  | HAL_DSI_FLOW_CONTROL_ECC_RX  | \
                                        HAL_DSI_FLOW_CONTROL_BTA     | HAL_DSI_FLOW_CONTROL_EOTP_RX | \
                                        HAL_DSI_FLOW_CONTROL_EOTP_TX | HAL_DSI_FLOW_CONTROL_EOTP_TX_LP)
/*!< Enable all the DSI flow control */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup DSI_Exported_Types DSI Exported Types
  * @{
  */
/**
  * @brief DSI instance enumeration definition
  */
typedef enum
{
  HAL_DSI = (uint32_t)DSI, /*!< HAL DSI instance */
} hal_dsi_t;

/**
  * @brief  HAL DSI State structures definition
  */
typedef enum
{
  HAL_DSI_STATE_RESET              =  0UL,         /*!< Reset state                               */
  HAL_DSI_STATE_INIT               = (1UL << 31U), /*!< DSI initialized but not yet configured    */
  HAL_DSI_STATE_CONFIGURED         = (1UL << 30U), /*!< DSI initialized and configured            */
  HAL_DSI_STATE_TIMING_CONFIGURED  = (1UL << 29U), /*!< DSI initialized and configured            */
  HAL_DSI_STATE_HOST_CONFIGURED    = (1UL << 28U), /*!< DSI initialized and configured            */
  HAL_DSI_STATE_IDLE               = (1UL << 27U), /*!< DSI is Idle                               */
  HAL_DSI_STATE_ACTIVE             = (1UL << 26U)  /*!< DSI initialized, configured and activated */

} hal_dsi_state_t;

/**
  *@brief DSI video mode type definition
  */
typedef enum
{
  HAL_DSI_VIDEO_MODE_NB_PULSES = 0U,            /*!< Video non burst with sync pulses mode */
  HAL_DSI_VIDEO_MODE_NB_EVENTS = DSI_VMCR_VMT0, /*!< Video non burst with sync events mode */
  HAL_DSI_VIDEO_MODE_BURST     = DSI_VMCR_VMT1  /*!< Video burst mode                      */
} hal_dsi_video_mode_t;

/**
  *@brief DSI color mode definition
  */
typedef enum
{
  HAL_DSI_COLOR_MODE_FULL  = 0x00U,       /*!< Full color mode  */
  HAL_DSI_COLOR_MODE_EIGHT = DSI_WCR_COLM /*!< Eight color mode */
} hal_dsi_color_mode_t;

/**
  *@brief DSI shut down definition
  */
typedef enum
{
  HAL_DSI_DISPLAY_ON  = 0x00U,        /*!< Display ON  */
  HAL_DSI_DISPLAY_OFF = DSI_WCR_SHTDN /*!< Display OFF */
} hal_dsi_display_t;

/**
  *@brief DSI low-power command state
  */
typedef enum
{
  HAL_DSI_LP_COMMAND_DISABLE = 0x00U,        /*Command transmission in low-power mode is disabled */
  HAL_DSI_LP_COMMAND_ENABLE  = DSI_VMCR_LPCE /*Command transmission in low-power mode is enabled  */
} hal_dsi_lp_command_state_t;

/**
  *@brief DSI Low-power horizontal front-porch state
  */
typedef enum
{
  HAL_DSI_LP_HFP_DISABLE = 0x00U,          /* Low-power inside the HFP period is disabled */
  HAL_DSI_LP_HFP_ENABLE  = DSI_VMCR_LPHFPE /* Low-power inside the HFP period is enabled  */
} hal_dsi_lp_hfp_state_t;

/**
  *@brief DSI Low-power horizontal back-porch state
  */
typedef enum
{
  HAL_DSI_LP_HBP_DISABLE = 0x00U,          /* Low-power inside the HBP period is disabled */
  HAL_DSI_LP_HBP_ENABLE  = DSI_VMCR_LPHBPE /* Low-power inside the HBP period is enabled  */
} hal_dsi_lp_hbp_state_t;

/**
  *@brief DSI Low-power vertical active state
  */
typedef enum
{
  HAL_DSI_LP_VACT_DISABLE = 0x00U,         /* Low-power inside the VACT period is disabled */
  HAL_DSI_LP_VACT_ENABLE  = DSI_VMCR_LPVAE /* Low-power inside the VACT period is enabled  */
} hal_dsi_lp_vact_state_t;

/**
  *@brief DSI low-power vertical front-porch state
  */
typedef enum
{
  HAL_DSI_LP_VFP_DISABLE = 0x00U,           /* Low-power inside the VFP period is disabled */
  HAL_DSI_LP_VFP_ENABLE  = DSI_VMCR_LPVFPE  /* Low-power inside the VFP period is enabled  */
} hal_dsi_lp_vfp_state_t;

/**
  *@brief DSI low-power vertical back-porch state
  */
typedef enum
{
  HAL_DSI_LP_VBP_DISABLE = 0x00U,          /* Low-power inside the VBP period is disabled */
  HAL_DSI_LP_VBP_ENABLE  = DSI_VMCR_LPVBPE /* Low-power inside the VBP period is enabled  */
} hal_dsi_lp_vbp_state_t;

/**
  *@brief DSI low-power vertical sync active state
  */
typedef enum
{
  HAL_DSI_LP_VSYNC_DISABLE = 0x00U,          /* Low-power inside the VSA period is disabled */
  HAL_DSI_LP_VSYNC_ENABLE  = DSI_VMCR_LPVSAE /* Low-power inside the VSA period is enabled  */
} hal_dsi_lp_vsync_state_t;

/**
  *@brief DSI frame bus-turn-around acknowledge status
  */
typedef enum
{
  HAL_DSI_FBTAA_DISABLED = 0x00U,          /* Acknowledge response at the end of a frame is disabled */
  HAL_DSI_FBTAA_ENABLED  = DSI_VMCR_FBTAAE /* Acknowledge response at the end of a frame is enabled  */
} hal_dsi_fbtaa_status_t;

/**
  *@brief DSI tearing effect source
  */
typedef enum
{
  HAL_DSI_TE_SOURCE_DSILINK  = 0x00U,          /* TE source DSI link     */
  HAL_DSI_TE_SOURCE_EXTERNAL = DSI_WCFGR_TESRC /* TE source external pin */
} hal_dsi_te_source_t;

/**
  *@brief DSI tearing effect polarity
  */
typedef enum
{
  HAL_DSI_TE_POLARITY_RISING_EDGE  = 0x00U,          /* TE polarity rising edge  */
  HAL_DSI_TE_POLARITY_FALLING_EDGE = DSI_WCFGR_TEPOL /* TE polarity falling edge */
} hal_dsi_te_polarity_t;

/**
  *@brief DSI Automatic Refresh status
  */
typedef enum
{
  HAL_DSI_AUTO_REFRESH_DISABLED = 0x00U,        /* Automatic Refresh is disabled */
  HAL_DSI_AUTO_REFRESH_ENABLED  = DSI_WCFGR_AR  /* Automatic Refresh is enabled  */
} hal_dsi_auto_refresh_status_t;

/**
  *@brief DSI Tearing Effect Acknowledge request
  */
typedef enum
{
  HAL_DSI_TE_ACKNOWLEDGE_DISABLE = 0x00U,         /* TE Acknowledge is disabled */
  HAL_DSI_TE_ACKNOWLEDGE_ENABLE  = DSI_CMCR_TEARE /* TE Acknowledge is enabled  */
} hal_dsi_te_acknowledge_state_t;

/**
  *@brief DSI Acknowledge request status
  */
typedef enum
{
  HAL_DSI_ACKNOWLEDGE_DISABLED = 0x00U,       /* Acknowledge request is disabled */
  HAL_DSI_ACKNOWLEDGE_ENABLED  = DSI_CMCR_ARE /* Acknowledge request is enabled  */
} hal_dsi_acknowledge_status_t;

/**
  *@brief DSI Generic Short Write Zero parameters Transmission state
  */
typedef enum
{
  HAL_DSI_LP_SHORT_WRITE_GEN_NO_PARAM_DISABLE = 0x00U,          /* GSW0P with high speed */
  HAL_DSI_LP_SHORT_WRITE_GEN_NO_PARAM_ENABLE  = DSI_CMCR_GSW0TX /* GSW0P with low power  */
} hal_dsi_lp_short_write_gen_no_param_state_t;

/**
  *@brief DSI Generic Short Write One parameters Transmission state
  */
typedef enum
{
  HAL_DSI_LP_SHORT_WRITE_GEN_1_PARAM_DISABLE = 0x00U,          /* GSW1P with high speed */
  HAL_DSI_LP_SHORT_WRITE_GEN_1_PARAM_ENABLE  = DSI_CMCR_GSW1TX /* GSW1P with low power  */
} hal_dsi_lp_short_write_gen_1_param_state_t;

/**
  *@brief DSI Generic Short Write Two parameters Transmission state
  */
typedef enum
{
  HAL_DSI_LP_SHORT_WRITE_GEN_2_PARAM_DISABLE = 0x00U,          /* GSW2P with high speed */
  HAL_DSI_LP_SHORT_WRITE_GEN_2_PARAM_ENABLE  = DSI_CMCR_GSW2TX /* GSW2P with low power  */
} hal_dsi_lp_short_write_gen_2_param_state_t;

/**
  *@brief DSI Generic Short Read Zero parameters Transmission state
  */
typedef enum
{
  HAL_DSI_LP_SHORT_READ_GEN_NO_PARAM_DISABLE = 0x00U,          /* GSR0P with high speed */
  HAL_DSI_LP_SHORT_READ_GEN_NO_PARAM_ENABLE  = DSI_CMCR_GSR0TX /* GSR0P with low power  */
} hal_dsi_lp_short_read_gen_no_param_state_t;

/**
  *@brief DSI Generic Short Read One parameters Transmission state
  */
typedef enum
{
  HAL_DSI_LP_SHORT_READ_GEN_1_PARAM_DISABLE = 0x00U,          /* GSR1P with high speed */
  HAL_DSI_LP_SHORT_READ_GEN_1_PARAM_ENABLE  = DSI_CMCR_GSR1TX /* GSR1P with low power  */
} hal_dsi_lp_short_read_gen_1_param_state_t;

/**
  *@brief DSI Generic Short Read two parameters Transmission state
  */
typedef enum
{
  HAL_DSI_LP_SHORT_READ_GEN_2_PARAM_DISABLE = 0x00U,          /* GSR2P with high speed */
  HAL_DSI_LP_SHORT_READ_GEN_2_PARAM_ENABLE  = DSI_CMCR_GSR2TX /* GSR2P with low power  */
} hal_dsi_lp_short_read_gen_2_param_state_t;

/**
  *@brief DSI Generic Long Write Transmission state
  */
typedef enum
{
  HAL_DSI_LP_LONG_WRITE_GEN_TX_DISABLE = 0x00U,         /* GLW with high speed */
  HAL_DSI_LP_LONG_WRITE_GEN_TX_ENABLE  = DSI_CMCR_GLWTX /* GLW with low power  */
} hal_dsi_long_write_gen_tx_state_t;

/**
  *@brief DSI DCS Short Write Zero parameter Transmission state
  */
typedef enum
{
  HAL_DSI_LP_SHORT_WRITE_DCS_TX_NO_PARAM_DISABLE = 0x00U,          /* DSW0P with high speed */
  HAL_DSI_LP_SHORT_WRITE_DCS_TX_NO_PARAM_ENABLE  = DSI_CMCR_DSW0TX /* DSW0P with low power  */
} hal_dsi_short_write_dcs_tx_no_param_state_t;

/**
  *@brief DSI DCS Short Write One parameter Transmission state
  */
typedef enum
{
  HAL_DSI_LP_DCS_SHORT_WRITE_1_PARAM_DISABLE = 0x00U,          /* DSW1P with high speed */
  HAL_DSI_LP_DCS_SHORT_WRITE_1_PARAM_ENABLE  = DSI_CMCR_DSW1TX /* DSW1P with low power  */
} hal_dsi_short_write_dcs_tx_1_param_state_t;

/**
  *@brief DSI DCS Short Read Zero parameter Transmission state
  */
typedef enum
{
  HAL_DSI_LP_SHORT_READ_DCS_TX_NO_PARAM_DISABLE = 0x00U,          /* DSR0P with high speed */
  HAL_DSI_LP_SHORT_READ_DCS_TX_NO_PARAM_ENABLE  = DSI_CMCR_DSR0TX /* DSR0P with low power  */
} hal_dsi_short_read_dcs_tx_no_param_state_t;

/**
  *@brief DSI DCS Long Write Transmission state
  */
typedef enum
{
  HAL_DSI_LP_LONG_WRITE_DCS_TX_DISABLE = 0x00U,         /* DLW with high speed */
  HAL_DSI_LP_LONG_WRITE_DCS_TX_ENABLE  = DSI_CMCR_DLWTX /* DLW with low power  */
} hal_dsi_long_write_dcs_tx_state_t;

/**
  *@brief DSI Maximum Read Packet Size state
  */
typedef enum
{
  HAL_DSI_LP_MAX_READ_PKT_DISABLE = 0x00U,          /* MRDP with high speed */
  HAL_DSI_LP_MAX_READ_PKT_ENABLE  = DSI_CMCR_MRDPS  /* MRDP with low power  */
} hal_dsi_lp_max_read_pkt_state_t;

/**
  *@brief DSI Automatic Clocklane Control status
  */
typedef enum
{
  HAL_DSI_AUTO_CLK_LANE_CTRL_DISABLED = 0x00U,       /* Automatic clock lane control disabled */
  HAL_DSI_AUTO_CLK_LANE_CTRL_ENABLED  = DSI_CLCR_ACR /* Automatic clock lane control enabled  */
} hal_dsi_auto_clk_lane_ctrl_status_t;

/**
  *@brief DSI Number Of Lanes
  */
typedef enum
{
  HAL_DSI_DATA_1_LANE  = 0U,            /* One data lane  */
  HAL_DSI_DATA_2_LANES = DSI_PCONFR_NL0 /* Two data lanes */
} hal_dsi_data_lane_t;

/**
  *@brief DSI Loosely Packed status
  */
typedef enum
{
  HAL_DSI_LOOSELY_PACKED_DISABLED = 0x00U,         /* Loosely packet is disabled */
  HAL_DSI_LOOSELY_PACKED_ENABLED  = DSI_LCOLCR_LPE /* Loosely packet is ensabled */
} hal_dsi_loosely_packed_status_t;

/**
  *@brief DSI Pattern Generator status
  */
typedef enum
{
  HAL_DSI_PATTERN_GENERATOR_DISABLED = 0x00U,       /* Pattern generator is disabled */
  HAL_DSI_PATTERN_GENERATOR_ENABLED  = DSI_VMCR_PGE /* Pattern generator is enabled  */
} hal_dsi_pattern_generator_status_t;

/**
  *@brief DSI HS Presp Mode
  */
typedef enum
{
  HAL_DSI_HS_PM_DISABLE = 0x00U,       /* Presp Mode is disabled */
  HAL_DSI_HS_PM_ENABLE  = DSI_TCCR3_PM /* Presp Mode is enabled  */
} hal_dsi_hs_presp_mode_t;

/**
  *@brief DSI Lane Force Select
  */
typedef enum
{
  HAL_DSI_FORCE_CLK_LANE   = DSI_WPCR0_FTXSMCL, /* DSI Lane Force with no effect        */
  HAL_DSI_FORCE_DATA_LANES = DSI_WPCR0_FTXSMDL  /* Force the clock lane in TX Stop mode */
} hal_dsi_force_lane_t;

/**
  *@brief DSI Lane Swap Select
  */
typedef enum
{
  HAL_DSI_SWAP_CLK_LANE    = DSI_WPCR0_SWCL,  /* Swap clock lane pins  */
  HAL_DSI_SWAP_DATA_LANE_0 = DSI_WPCR0_SWDL0, /* Swap data lane 0 pins */
  HAL_DSI_SWAP_DATA_LANE_1 = DSI_WPCR0_SWDL1  /* Swap data lane 1 pins */
} hal_dsi_swap_lane_t;

/**
  * @brief DSI Lane Force Enable or Disable Enumeration Definition
  */
typedef enum
{
  HAL_DSI_FORCE_LANE_DISABLED  = 0x00U, /*!< Force lane  disabled */
  HAL_DSI_FORCE_LANE_ENABLED   = 0x01U  /*!< Force lane enabled   */
} hal_dsi_force_lane_status_t ;

/**
  * @brief DSI Lane Force Enable or Disable Enumeration Definition
  */
typedef enum
{
  HAL_DSI_SWAP_LANE_DISABLED  = 0x00U, /*!< SWAP select  disabled */
  HAL_DSI_SWAP_LANE_ENABLED   = 0x01U  /*!< SWAP select enabled   */
} hal_dsi_swap_lane_status_t ;

/**
  *@brief DSI Color Coding
  */
typedef enum
{
  HAL_DSI_COLOR_RGB565 = 0x00U, /*!< The values 0x00000001 and 0x00000002 can also be used for the RGB565
                                     color mode configuration */
  HAL_DSI_COLOR_RGB666 = 0x03U, /*!< The value 0x00000004 can also be used for the RGB666
                                     color mode configuration */
  HAL_DSI_COLOR_RGB888 = 0x05U
} hal_dsi_color_t;

/**
  *@brief DSI DPHY Frequency Range
  */
typedef enum
{
  HAL_DSI_DPHY_FREQ_RANGE_80MHZ_100MHZ   = 0x00U, /*!< 80-100  MHz */
  HAL_DSI_DPHY_FREQ_RANGE_100MHZ_120MHZ  = 0x01U, /*!< 100-120 MHz */
  HAL_DSI_DPHY_FREQ_RANGE_120MHZ_160MHZ  = 0x02U, /*!< 120-160 MHz */
  HAL_DSI_DPHY_FREQ_RANGE_160MHZ_200MHZ  = 0x03U, /*!< 160-200 MHz */
  HAL_DSI_DPHY_FREQ_RANGE_200MHZ_240MHZ  = 0x04U, /*!< 200-240 MHz */
  HAL_DSI_DPHY_FREQ_RANGE_240MHZ_320MHZ  = 0x05U, /*!< 240-320 MHz */
  HAL_DSI_DPHY_FREQ_RANGE_320MHZ_390MHZ  = 0x06U, /*!< 320-390 MHz */
  HAL_DSI_DPHY_FREQ_RANGE_390MHZ_450MHZ  = 0x07U, /*!< 390-450 MHz */
  HAL_DSI_DPHY_FREQ_RANGE_450MHZ_510MHZ  = 0x08U  /*!< 450-510 MHz */
} hal_dsi_dphy_freq_range_t;

/**
  *@brief DSI PLL Charge pump
  */
typedef enum
{
  HAL_DSI_PLL_CHARGE_PUMP_2000HZ_4400HZ   = 0U,                            /*!< 2.0 to 4.4 MHz and 14.1 to 30.9 MHz */
  HAL_DSI_PLL_CHARGE_PUMP_4400HZ_14100HZ  = DSI_WPTR_CP0,                  /*!< 4.4 to 14.1 MHz                     */
  HAL_DSI_PLL_CHARGE_PUMP_30900HZ_45700HZ = (DSI_WPTR_CP0 | DSI_WPTR_CP1), /*!< 30.9 to 45.7 MHz                    */
  HAL_DSI_PLL_CHARGE_PUMP_45700HZ_50000HZ = DSI_WPTR_CP1                   /*!< 45.7 to 50 MHz                      */
} hal_dsi_pll_charge_pump_t;

/**
  *@brief DSI PLL Tuning
  */
typedef enum
{
  HAL_DSI_PLL_LOOP_FILTER_2000HZ_4400HZ   = 0U,            /*!< 2.0 to 4.4 MHz  */
  HAL_DSI_PLL_LOOP_FILTER_4400HZ_30900HZ  = DSI_WPTR_LPF0, /*!< 4.4 to 30.9 MHz */
  HAL_DSI_PLL_LOOP_FILTER_30900HZ_50000HZ = DSI_WPTR_LPF1  /*!< 30.9 to 50  MHz */
} hal_dsi_pll_loop_filter_t;

/**
  *@brief DSI SHORT READ PKT Data Type
  */
typedef enum
{
  HAL_DSI_SHORT_READ_PKT_DCS    = (DSI_GHCR_DT1 | DSI_GHCR_DT2),      /*!< DCS short read                     */
  HAL_DSI_SHORT_READ_PKT_GEN_NO_PARAM =  DSI_GHCR_DT2,                /*!< Generic short read, no parameters  */
  HAL_DSI_SHORT_READ_PKT_GEN_1_PARAM = (DSI_GHCR_DT2 | DSI_GHCR_DT4), /*!< Generic short read, one parameter  */
  HAL_DSI_SHORT_READ_PKT_GEN_2_PARAM = (DSI_GHCR_DT2 | DSI_GHCR_DT5), /*!< Generic short read, two parameters */
} hal_dsi_short_read_packet_t;

/**
  *@brief DSI SHORT WRITE PKT Data Type
  */
typedef enum
{
  HAL_DSI_SHORT_WRITE_PKT_DCS_NO_PARAM = (DSI_GHCR_DT0 | DSI_GHCR_DT2),               /*!< DCS short write,
                                                                                          no parameters  */
  HAL_DSI_SHORT_WRITE_PKT_DCS_1_PARAM = (DSI_GHCR_DT1 | DSI_GHCR_DT2 | DSI_GHCR_DT4), /*!< DCS short write,
                                                                                          one parameter  */
  HAL_DSI_SHORT_WRITE_PKT_GEN_NO_PARAM = (DSI_GHCR_DT0 | DSI_GHCR_DT1),               /*!< Generic short write,
                                                                                           no parameters */
  HAL_DSI_SHORT_WRITE_PKT_GEN_1_PARAM = (DSI_GHCR_DT0 | DSI_GHCR_DT1 | DSI_GHCR_DT4), /*!< Generic short write,
                                                                                          one parameter  */
  HAL_DSI_SHORT_WRITE_PKT_GEN_2_PARAM = (DSI_GHCR_DT0 | DSI_GHCR_DT1 | DSI_GHCR_DT5),  /*!< Generic short write,
                                                                                          two parameters */
} hal_dsi_short_write_packet_t;

/**
  *@brief DSI LONG WRITE PKT Data Type
  */
typedef enum
{
  HAL_DSI_LONG_WRITE_PKT_DCS  = (DSI_GHCR_DT0 | DSI_GHCR_DT3 | DSI_GHCR_DT4 | DSI_GHCR_DT5), /*!< DCS long write     */
  HAL_DSI_LONG_WRITE_PKT_GEN  = (DSI_GHCR_DT0 | DSI_GHCR_DT3 | DSI_GHCR_DT5)                 /*!< Generic long write */
} hal_dsi_long_write_packet_t;

/**
  *@brief DSI DPHY VCO Frequency Range
  */
typedef enum
{
  HAL_DSI_VCO_FREQ_RANGE_500MHZ_800MHZ = 0U,          /*!< 500-800 MHz  */
  HAL_DSI_VCO_FREQ_RANGE_800MHZ_1GHZ   = DSI_WRPCR_BC /*!< 800-1000 MHz */
} hal_dsi_vco_freq_range_t;

/**
  *@brief DSI Virtual channel ID
  */
typedef enum
{
  HAL_DSI_VIRTUAL_CHANNEL_ID_0 = 0U, /*!< virtual channel id 0 */
  HAL_DSI_VIRTUAL_CHANNEL_ID_1 = 1U, /*!< virtual channel id 1 */
  HAL_DSI_VIRTUAL_CHANNEL_ID_2 = 2U, /*!< virtual channel id 2 */
  HAL_DSI_VIRTUAL_CHANNEL_ID_3 = 3U  /*!< virtual channel id 3 */
} hal_dsi_virtual_channel_t;

/**
  *@brief DSI Pattern generator
  */
typedef enum
{
  HAL_DSI_PATTERN_VERTICAL_COLOR_BARS   = 0U,                            /* Orientation vertical color bars   */
  HAL_DSI_PATTERN_HORIZONTAL_COLOR_BARS = DSI_VMCR_PGO,                  /* Orientation horizontal color bars */
  HAL_DSI_PATTERN_VERTICAL_BER          = (DSI_VMCR_PGM | ~DSI_VMCR_PGO) /* BER pattern                       */
} hal_dsi_pattern_t;

/**
  *@brief DSI PHY Low Power Offset
  */
typedef enum
{
  HAL_DPHY_LP_OFFSSET_0_CLKP        = 0x00U, /*Offset value 0 for the clock lane       */
  HAL_DPHY_LP_OFFSSET_1_CLKP        = 0x01U, /*Offset value 1 for the clock lane       */
  HAL_DPHY_LP_OFFSSET_2_CLKP        = 0x02U, /*Offset value 2 for the clock lane       */
  HAL_DPHY_LP_OFFSSET_3_CLKP        = 0x03U, /*Offset value 3 for the clock lane       */
  HAL_DPHY_LP_OFFSSET_4_CLKP        = 0x04U, /*Offset value 4 for the clock lane       */
  HAL_DPHY_LP_OFFSSET_5_CLKP        = 0x05U, /*Offset value 5 for the clock lane       */
  HAL_DPHY_LP_OFFSSET_6_CLKP        = 0x06U, /*Offset value 6 for the clock lane       */
  HAL_DPHY_LP_OFFSSET_7_CLKP        = 0x07U, /*Offset value 7 for the clock lane       */
  HAL_DPHY_LP_OFFSSET_MINUS_1_CLKP  = 0x08U, /*Offset minus value 1 for the clock lane */
  HAL_DPHY_LP_OFFSSET_MINUS_2_CLKP  = 0x09U, /*Offset minus value 2 for the clock lane */
  HAL_DPHY_LP_OFFSSET_MINUS_3_CLKP  = 0x0AU, /*Offset minus value 3 for the clock lane */
  HAL_DPHY_LP_OFFSSET_MINUS_4_CLKP  = 0x0BU, /*Offset minus value 4 for the clock lane */
  HAL_DPHY_LP_OFFSSET_MINUS_5_CLKP  = 0x0CU, /*Offset minus value 5 for the clock lane */
  HAL_DPHY_LP_OFFSSET_MINUS_6_CLKP  = 0x0DU, /*Offset minus value 6 for the clock lane */
  HAL_DPHY_LP_OFFSSET_MINUS_7_CLKP  = 0x0EU, /*Offset minus value 7 for the clock lane */
  HAL_DPHY_LP_OFFSSET_MINUS_8_CLKP  = 0x0FU  /*Offset minus value 8 for the clock lane */
} hal_dsi_dphy_lp_offset_t;

/**
  * @brief  DSI PLL Config Structure definition
  */

typedef struct
{
  uint32_t pll_ndiv;                          /*!< PLL Loop Division Factor
                                                   This parameter must be a value between 10 and 125       */

  uint32_t pll_idf;                           /*!< PLL Input Division Factor                               */

  uint32_t pll_odf;                           /*!< PLL Output Division Factor                              */

  hal_dsi_vco_freq_range_t  vco_range;        /*!< PLLVCORange
                                      This parameter can be any value of @ref DSI DPHY VCO Frequency Range */

  hal_dsi_pll_charge_pump_t pll_charge_pump;  /*!< PLLChargePump
                                               This parameter can be any value of @ref DSI PLL Charge pump */

  hal_dsi_pll_loop_filter_t  pll_loop_filter; /*!< PLLTuning
                                                   This parameter can be any value of @ref DSI PLL Tuning */

} hal_dsi_pll_config_t;

/**
  * @brief  DSI PHY Config Structure definition
  */

typedef struct
{

  hal_dsi_dphy_freq_range_t phy_frequency_range; /*!< PHY Frequency Range
                                      This parameter can be any value of @arg DSI DPHY Frequency Range */

  hal_dsi_dphy_lp_offset_t phy_low_pwr_offset;  /*!< PHY Low Power Offset
                                      This parameter can be any value of @arg DSI PHY Low Power Offset */

} hal_dsi_dphy_config_t;
/**
  * @brief  DSI Config Structure definition
  */

typedef struct
{

  uint32_t tx_escape_clk_div;       /*!< TX Escape clock division
                                         The values 0 and 1 stop the TX_ESC clock generation         */

  hal_dsi_data_lane_t nbr_of_lanes; /*!< Number of lanes
                                         This parameter can be any value of @ref DSI Number Of Lanes */

  hal_dsi_pll_config_t  pll_cfg;    /*!< DSI PLL Config Structure definition                         */

  hal_dsi_dphy_config_t phy_cfg;    /*!< DSI PHY Config Structure definition                         */

} hal_dsi_config_t;

/**
  * @brief  DSI Video mode configuration
  */
typedef struct
{
  hal_dsi_virtual_channel_t VirtualChannel;  /*!< Virtual channel ID                                                 */

  hal_dsi_color_t ColorCoding;                  /*!< Color coding for DSI interface
                                                     This parameter can be any value of @ref DSI Color Coding        */

  hal_dsi_video_mode_t mode;                        /*!< Video mode type
                                         This parameter can be any value of @ref DSI video mode type definition      */

  uint32_t packet_size;                             /*!< Video packet size                                           */

  uint32_t nbr_of_chunks;                           /*!< Number of chunks                                            */

  uint32_t null_packet_size;                        /*!< Null packet size                                            */

  uint32_t h_sync_active;                           /*!< Horizontal synchronism active duration
                                                    (in lane byte clock cycles)                                      */

  uint32_t h_back_porch;                            /*!< Horizontal back-porch duration (in lane byte clock cycles)  */

  uint32_t h_line;                                  /*!< Horizontal line duration (in lane byte clock cycles)        */

  uint32_t v_sync_active;                           /*!< Vertical synchronism active duration                        */

  uint32_t v_back_porch;                           /*!< Vertical back-porch duration                                 */

  uint32_t v_front_porch;                          /*!< Vertical front-porch duration                                */

  uint32_t v_active;                               /*!< Vertical active duration                                     */

  hal_dsi_lp_command_state_t lp_command;           /*!< Low-power command enable
                                               This parameter can be any value of @ref  DSI low-power command state  */

  uint32_t lp_largest_packet_size;              /*!< The size, in bytes, of the low power largest packet that
                                                 can fit in a line during VSA, VBP and VFP regions                   */

  uint32_t lp_vact_largest_packet_size;         /*!< The size, in bytes, of the low power largest packet that
                                                 can fit in a line during VACT region                                */

  hal_dsi_lp_hfp_state_t lp_horizontal_front_porch;   /*!< Low-power horizontal front-porch enable
                              This parameter can be any value of @ref DSI Low-power horizontal front-porch state     */

  hal_dsi_lp_hbp_state_t lp_horizontal_back_porch;    /*!< Low-power horizontal back-porch enable
                              This parameter can be any value of @ref DSI Low-power horizontal back-porch state      */

  hal_dsi_lp_vact_state_t lp_vertical_active;         /*!< Low-power vertical active enable
                              This parameter can be any value of @ref DSI Low-power vertical active state            */

  hal_dsi_lp_vfp_state_t lp_vertical_front_porch;     /*!< Low-power vertical front-porch enable
                              This parameter can be any value of @ref DSI low-power vertical front-porch state       */

  hal_dsi_lp_vbp_state_t lp_vertical_back_porch;      /*!< Low-power vertical back-porch enable!
                              This parameter can be any value of @ref DSI low-power vertical back-porch state        */

  hal_dsi_lp_vsync_state_t lp_vertical_sync_active;   /*!< Low-power vertical sync active enable
                              This parameter can be any value of @ref DSI low-power vertical sync active state       */

} hal_dsi_video_config_t;

/**
  * @brief  DSI Adapted command mode configuration
  */
typedef struct
{
  hal_dsi_virtual_channel_t VirtualChannel; /*!< Virtual channel ID                                                */

  hal_dsi_color_t color_coding;             /*!< Color coding for DSI interface
                                                 This parameter can be any value of @ref DSI Color Coding          */

  uint32_t command_size;                    /*!< Maximum allowed size for an DSI write memory command, measured in
                                                pixels. This parameter can be any value between 0x00 and 0xFFFFU   */

} hal_dsi_cmd_config_t;

/**
  * @brief  DSI tearing effect configuration
  */
typedef struct
{
  hal_dsi_te_source_t      src;                /*!< Tearing effect source              */

  hal_dsi_te_polarity_t    polarity;           /*!< Tearing effect polarity            */

  hal_dsi_te_acknowledge_state_t  acknowledge; /*!< Tearing effect Acknowledge request */

} hal_dsi_tearing_effect_config_t;

/**
  * @brief  DSI command transmission mode configuration
  */
typedef struct
{
  hal_dsi_lp_short_write_gen_no_param_state_t lp_short_write_gen_no_param;  /*!< Generic Short Write Zero
                                                                                    parameters Transmission
                This parameter can be any value of @ref DSI Generic Short Write Zero parameters Transmission state  */

  hal_dsi_lp_short_write_gen_1_param_state_t lp_short_write_gen_1_param;    /*!< Generic Short Write One
                                                                                         parameter Transmission
                This parameter can be any value of @ref DSI Generic Short Write One parameters Transmission state   */

  hal_dsi_lp_short_write_gen_2_param_state_t lp_short_write_gen_2_param;   /*!< Generic Short Write Two
                                                                                         parameters Transmission
                This parameter can be any value of @ref DSI Generic Short Write Two parameters Transmission state   */

  hal_dsi_lp_short_read_gen_no_param_state_t lp_short_read_gen_no_param;  /*!< Generic Short Read Zero
                                                                                         parameters Transmission
                This parameter can be any value of @ref DSI Generic Short Read Zero parameters Transmission state   */

  hal_dsi_lp_short_read_gen_1_param_state_t lp_short_read_gen_1_param;        /*!< Generic Short Read One
                                                                                          parameter Transmission
                This parameter can be any value of @ref DSI Generic Short Read One parameters Transmission state    */

  hal_dsi_lp_short_read_gen_2_param_state_t lp_short_read_gen_2_param;  /*!< Generic Short Read Two
                                                                                   Two parameters Transmission
                This parameter can be any value of @ref DSI Generic Short Read two parameters Transmission state    */

  hal_dsi_long_write_gen_tx_state_t lp_long_write_gen_tx;  /*!< Generic Long Write Transmission
                This parameter can be any value of @ref DSI Generic Long Write Transmission state                   */

  hal_dsi_short_write_dcs_tx_no_param_state_t lp_short_write_dcs_tx_no_param;   /*!< DCS Short Write Zero
                                                                            parameters Transmission
                This parameter can be any value of @ref DSI DCS Short Write Zero parameter Transmission state       */

  hal_dsi_short_write_dcs_tx_1_param_state_t lp_short_write_dcs_tx_1_param;  /*!< DCS Short Write One
                                                                             parameter Transmission
                This parameter can be any value of @ref DSI DCS Short Write One parameter Transmission state        */

  hal_dsi_short_read_dcs_tx_no_param_state_t lp_short_read_dcs_tx_no_param;  /*!< DCS Short Read Zero
                                                                             parameters Transmission
                This parameter can be any value of @ref DSI DCS Short Read Zero parameter Transmission state        */

  hal_dsi_long_write_dcs_tx_state_t lp_long_write_dcs_tx;  /*!< DCS Long Write Transmission
                This parameter can be any value of @ref DSI DCS Long Write Transmission state                       */

  hal_dsi_lp_max_read_pkt_state_t lp_max_read_pkt;  /*!< Maximum Read Packet Size Transmission
                This parameter can be any value of @ref DSI Maximum Read Packet Size state                          */

} hal_dsi_lp_cmd_config_t;

/**
  * @brief  DSI PHY Timings definition
  */
typedef struct
{
  uint32_t clk_lane_hs2_lp_time;    /*!< The maximum time that the D-PHY clock lane takes to go from high-speed
                                              to low-power transmission                                          */

  uint32_t clk_lane_lp2_hs_time;    /*!< The maximum time that the D-PHY clock lane takes to go from low-power
                                              to high-speed transmission                                         */

  uint32_t data_lanehs2_lp_time;    /*!< The maximum time that the D-PHY data lanes takes to go from high-speed
                                              to low-power transmission                                          */

  uint32_t data_lane_lp_2hs_time;   /*!< The maximum time that the D-PHY data lanes takes to go from low-power
                                              to high-speed transmission                                         */

  uint32_t data_lane_max_read_time; /*!< The maximum time required to perform a read command */

  uint32_t stop_wait_time;          /*!< The minimum wait period to request a High-Speed transmission after the
                                              Stop state                                                         */

} hal_dsi_phy_tim_config_t;

/**
  * @brief  DSI HOST Timeouts definition
  */
typedef struct
{
  uint32_t time_out_clk_div;                             /*!< Time-out clock division                               */

  uint32_t high_speed_tr_timeout;                        /*!< High-speed transmission time-out                      */

  uint32_t low_power_reception_timeout;                  /*!< Low-power reception time-out                          */

  uint32_t high_Speed_read_timeout;                      /*!< High-speed read time-out                              */

  uint32_t low_power_read_timeout;                       /*!< Low-power read time-out                               */

  uint32_t high_speed_write_timeout;                     /*!< High-speed write time-out                             */

  hal_dsi_hs_presp_mode_t high_Speed_write_Presp_mode;   /*!< High-speed write presp mode
                                                        This parameter can be any value of @ref DSI HS Presp Mode   */

  uint32_t low_power_write_timeout;                      /*!< Low-speed write time-out                              */

  uint32_t bta_timeout;                                  /*!< BTA time-out                                          */

} hal_dsi_timeout_config_t;

/**
  * @brief  DSI States Structure definition
  */
typedef struct hal_dsi_handle_s hal_dsi_handle_t;  /*!< DSI handle Structure type */

#if defined (USE_HAL_DSI_REGISTER_CALLBACKS) && (USE_HAL_DSI_REGISTER_CALLBACKS == 1)
/*! DSI Callback pointer definition */
typedef void (*hal_dsi_cb_t)(hal_dsi_handle_t *hdsi);

#endif /* USE_HAL_DSI_REGISTER_CALLBACKS */

/**
  * @brief  DSI Handle Structure definition
  */
struct hal_dsi_handle_s
{
  hal_dsi_t                instance;            /*!< DSI instance                */
  volatile hal_dsi_state_t global_state;        /*!< DSI communication state     */
#if defined(USE_HAL_DSI_GET_LAST_ERRORS) && (USE_HAL_DSI_GET_LAST_ERRORS == 1)
  volatile uint32_t        last_error_codes;    /*!< DSI last error codes        */
#endif /* USE_HAL_DSI_GET_LAST_ERRORS */
#if defined (USE_HAL_DSI_REGISTER_CALLBACKS) && (USE_HAL_DSI_REGISTER_CALLBACKS == 1)
  hal_dsi_cb_t             p_tearing_effect_cb; /*!< DSI Tearing Effect Callback */
  hal_dsi_cb_t             p_refresh_cb;        /*!< DSI End Of Refresh Callback */
  hal_dsi_cb_t             p_error_cb;          /*!< DSI Error Callback          */
#endif /* USE_HAL_DSI_REGISTER_CALLBACKS */

#if defined(USE_HAL_DSI_USER_DATA) && (USE_HAL_DSI_USER_DATA == 1)
  const void               *p_user_data;        /*!< DSI user data               */
#endif /* USE_HAL_DSI_USER_DATA */
};

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup DSI_Exported_Functions DSI Exported Functions
  * @{
  */
/** @defgroup DSI_Exported_Functions_Group1 Initialization and Configuration functions
  * @{
  */
hal_status_t HAL_DSI_Init(hal_dsi_handle_t *hdsi, hal_dsi_t instance);
void HAL_DSI_DeInit(hal_dsi_handle_t *hdsi);
/**
  * @}
  */

/** @defgroup DSI_Exported_Functions_Group2 Global configuration functions
  * @{
  */
hal_status_t HAL_DSI_SetConfig(hal_dsi_handle_t *hdsi, const hal_dsi_config_t *p_config);
void         HAL_DSI_GetConfig(const hal_dsi_handle_t *hdsi, hal_dsi_config_t *p_config);
/**
  * @}
  */

/** @defgroup DSI_Exported_Functions_Group3 IRQHandler and Callbacks functions
  * @{
  */
void HAL_DSI_IRQHandler(hal_dsi_handle_t *hdsi);

void HAL_DSI_TearingEffectCallback(hal_dsi_handle_t *hdsi);
void HAL_DSI_EndOfRefreshCallback(hal_dsi_handle_t *hdsi);
void HAL_DSI_ErrorCallback(hal_dsi_handle_t *hdsi);

#if (USE_HAL_DSI_REGISTER_CALLBACKS == 1)
hal_status_t HAL_DSI_RegisterErrorCallback(hal_dsi_handle_t *hdsi, hal_dsi_cb_t p_callback);
hal_status_t HAL_DSI_RegisterTearingEffectCallback(hal_dsi_handle_t *hdsi, hal_dsi_cb_t p_callback);
hal_status_t HAL_DSI_RegisterEndOfRefreshCallback(hal_dsi_handle_t *hdsi, hal_dsi_cb_t p_callback);
#endif /* USE_HAL_DSI_REGISTER_CALLBACKS */
/**
  * @}
  */
/** @defgroup DSI_Peripheral_control_functions_Group4 Peripheral Control functions
  * @{
  */
hal_status_t HAL_DSI_SetGenericVCIDRX(hal_dsi_handle_t *hdsi, hal_dsi_virtual_channel_t virtual_channel_id_rx);
hal_dsi_virtual_channel_t HAL_DSI_GetGenericVCIDRX(const hal_dsi_handle_t *hdsi);

hal_status_t HAL_DSI_SetGenericVCIDTX(hal_dsi_handle_t *hdsi, hal_dsi_virtual_channel_t virtual_channel_id_tx);
hal_dsi_virtual_channel_t HAL_DSI_GetGenericVCIDTX(const hal_dsi_handle_t *hdsi);

hal_status_t HAL_DSI_SetGenericVCID(hal_dsi_handle_t *hdsi, hal_dsi_virtual_channel_t virtual_channel_id);
hal_dsi_virtual_channel_t HAL_DSI_GetGenericVCID(const hal_dsi_handle_t *hdsi);

hal_status_t HAL_DSI_SetConfigVideoMode(hal_dsi_handle_t *hdsi, const hal_dsi_video_config_t *p_videoconfig);
void HAL_DSI_GetConfigVideoMode(const hal_dsi_handle_t *hdsi, hal_dsi_video_config_t *p_videoconfig);

hal_status_t HAL_DSI_SetConfigAdaptedCommandMode(hal_dsi_handle_t *hdsi, const hal_dsi_cmd_config_t *p_cmdcfg);
void HAL_DSI_GetConfigAdaptedCommandMode(const hal_dsi_handle_t *hdsi, hal_dsi_cmd_config_t *p_cmdcfg);

hal_status_t HAL_DSI_SetConfigLPCommand(hal_dsi_handle_t *hdsi, const hal_dsi_lp_cmd_config_t *p_lpcmd);
void HAL_DSI_GetConfigLPCommand(const hal_dsi_handle_t *hdsi, hal_dsi_lp_cmd_config_t *p_lpcmd);

hal_status_t HAL_DSI_SetFlowControl(hal_dsi_handle_t *hdsi, const uint32_t flow_control);
void HAL_DSI_GetFlowControl(const hal_dsi_handle_t *hdsi, uint32_t flow_control);

hal_status_t HAL_DSI_SetConfigPhyTimer(hal_dsi_handle_t *hdsi, hal_dsi_phy_tim_config_t *p_phytimers);
void HAL_DSI_GetConfigPhyTimer(const hal_dsi_handle_t *hdsi, hal_dsi_phy_tim_config_t *p_phytimers);

hal_status_t HAL_DSI_SetConfigHostTimeouts(hal_dsi_handle_t *hdsi, const hal_dsi_timeout_config_t *p_host_timeout);
void HAL_DSI_GetConfigHostTimeouts(const hal_dsi_handle_t *hdsi, hal_dsi_timeout_config_t *p_host_timeout);

hal_status_t HAL_DSI_SetConfigPatternGenerator(hal_dsi_handle_t *hdsi, hal_dsi_pattern_t pattern_generator);
hal_dsi_pattern_t HAL_DSI_GetConfigPatternGenerator(const hal_dsi_handle_t *hdsi);

hal_status_t HAL_DSI_EnablePatternGenerator(hal_dsi_handle_t *hdsi);
hal_status_t HAL_DSI_DisablePatternGenerator(hal_dsi_handle_t *hdsi);
hal_dsi_pattern_generator_status_t HAL_DSI_IsEnabledPatternGenerator(const hal_dsi_handle_t *hdsi);

hal_status_t HAL_DSI_Start(hal_dsi_handle_t *hdsi, uint32_t interrupts);
hal_status_t HAL_DSI_Stop(hal_dsi_handle_t *hdsi);

hal_status_t HAL_DSI_Refresh(hal_dsi_handle_t *hdsi);

hal_status_t HAL_DSI_EnableAutomaticClockLane(hal_dsi_handle_t *hdsi);
hal_status_t HAL_DSI_DisableAutomaticClockLane(hal_dsi_handle_t *hdsi);
hal_dsi_auto_clk_lane_ctrl_status_t HAL_DSI_IsEnabledAutomaticClockLane(const hal_dsi_handle_t *hdsi);

hal_status_t HAL_DSI_EnableLooselyPacked(hal_dsi_handle_t *hdsi);
hal_status_t HAL_DSI_DisableLooselyPacked(hal_dsi_handle_t *hdsi);
hal_dsi_loosely_packed_status_t HAL_DSI_IsEnabledLoosleyPacked(const hal_dsi_handle_t *hdsi);

hal_status_t HAL_DSI_EnableFrameBusAcknowledge(hal_dsi_handle_t *hdsi);
hal_status_t HAL_DSI_DisableFrameBusAcknowledge(hal_dsi_handle_t *hdsi);
hal_dsi_fbtaa_status_t HAL_DSI_IsEnabledFrameBusAcknowledge(const hal_dsi_handle_t *hdsi);


hal_status_t HAL_DSI_SetConfigTearingEffect(hal_dsi_handle_t *hdsi,
                                            const hal_dsi_tearing_effect_config_t *p_tearing_effect_config_t);
void HAL_DSI_GetConfigTearingEffect(const hal_dsi_handle_t *hdsi,
                                    hal_dsi_tearing_effect_config_t *p_tearing_effect_config_t);

hal_status_t HAL_DSI_EnableAutomaticRefresh(hal_dsi_handle_t *hdsi);
hal_status_t HAL_DSI_DisableAutomaticRefresh(hal_dsi_handle_t *hdsi);
hal_dsi_auto_refresh_status_t HAL_DSI_IsEnabledAutomaticRefresh(const hal_dsi_handle_t *hdsi);


hal_status_t HAL_DSI_EnableAcknowledge(hal_dsi_handle_t *hdsi);
hal_status_t HAL_DSI_DisableAcknowledge(hal_dsi_handle_t *hdsi);
hal_dsi_acknowledge_status_t HAL_DSI_IsEnabledAcknowledge(const hal_dsi_handle_t *hdsi);

hal_status_t HAL_DSI_SetColorMode(hal_dsi_handle_t *hdsi, hal_dsi_color_mode_t color_mode);
hal_dsi_color_mode_t HAL_DSI_GetColorMode(const hal_dsi_handle_t *hdsi);

hal_status_t HAL_DSI_Shutdown(hal_dsi_handle_t *hdsi, hal_dsi_display_t display);
hal_status_t HAL_DSI_ShortWrite(hal_dsi_handle_t *hdsi, hal_dsi_virtual_channel_t channel_id,
                                hal_dsi_short_write_packet_t mode, uint32_t first_param, uint32_t second_param);

hal_status_t HAL_DSI_LongWrite(hal_dsi_handle_t *hdsi,
                               hal_dsi_virtual_channel_t channel_id,
                               hal_dsi_long_write_packet_t mode,
                               uint32_t nbparams,
                               uint32_t first_param,
                               uint8_t *p_param_table);

hal_status_t HAL_DSI_Read(hal_dsi_handle_t *hdsi,
                          hal_dsi_virtual_channel_t channel_nbr,
                          uint8_t *p_array,
                          uint32_t size,
                          hal_dsi_short_read_packet_t mode,
                          uint32_t cmdDCS,
                          uint8_t *p_parameters_table);

uint32_t  HAL_DSI_GetClockFreq(const hal_dsi_handle_t *hdsi);
uint32_t  HAL_DSI_GetACKErrorSource(hal_dsi_handle_t *hdsi);

hal_status_t HAL_DSI_EnterULPMData(hal_dsi_handle_t *hdsi);
hal_status_t HAL_DSI_ExitULPMData(hal_dsi_handle_t *hdsi);
hal_status_t HAL_DSI_EnterULPM(hal_dsi_handle_t *hdsi);
hal_status_t HAL_DSI_ExitULPM(hal_dsi_handle_t *hdsi);

hal_status_t HAL_DSI_EnableSwapLanePins(hal_dsi_handle_t *hdsi, hal_dsi_swap_lane_t lane);
hal_status_t HAL_DSI_DisableSwapLanePins(hal_dsi_handle_t *hdsi, hal_dsi_swap_lane_t lane);
hal_dsi_swap_lane_status_t HAL_DSI_IsEnabledSwapLanePins(const hal_dsi_handle_t *hdsi, hal_dsi_swap_lane_t lane);

hal_status_t HAL_DSI_EnableForceTXStopMode(hal_dsi_handle_t *hdsi, hal_dsi_force_lane_t lane);
hal_status_t HAL_DSI_DisableForceTXStopMode(hal_dsi_handle_t *hdsi, hal_dsi_force_lane_t lane);
hal_dsi_force_lane_status_t HAL_DSI_IsEnabledForceTXStopMode(const hal_dsi_handle_t *hdsi, hal_dsi_force_lane_t lane);

#if defined(USE_HAL_LTDC_MODULE) && defined(USE_HAL_DSI_MODULE)
hal_status_t HAL_DSI_GetVideoTimingFromLTDC(hal_ltdc_handle_t *hltdc,
                                            hal_ltdc_config_t *p_config,
                                            hal_dsi_video_config_t *p_videoconfig);
hal_status_t HAL_DSI_GetVideoTimingFromDSI(hal_dsi_handle_t *hdsi,
                                           hal_dsi_video_config_t *p_videoconfig,
                                           hal_ltdc_config_t *p_config);
#endif /* USE_HAL_LTDC_MODULE */
/**
  * @}
  */

/** @defgroup DSI_Exported_Functions_Group5 Peripheral State and Error functions
  * @{
  */
hal_dsi_state_t HAL_DSI_GetState(hal_dsi_handle_t *hdsi);
#if defined (USE_HAL_DSI_GET_LAST_ERRORS) && (USE_HAL_DSI_GET_LAST_ERRORS == 1)
uint32_t        HAL_DSI_GetLastErrorCodes(const hal_dsi_handle_t *hdsi);
#endif /* USE_HAL_DSI_GET_LAST_ERRORS */
/**
  * @}
  */
#if defined (USE_HAL_DSI_USER_DATA) && (USE_HAL_DSI_USER_DATA == 1)
/** @defgroup DSI_Exported_Functions_Group6 Set/Get user data
  * @{
  */
void        HAL_DSI_SetUserData(hal_dsi_handle_t *hdsi, const void *p_user_data);
const void *HAL_DSI_GetUserData(const hal_dsi_handle_t *hdsi);
/**
  * @}
  */
#endif /* USE_HAL_DSI_USER_DATA */
/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup DSI_Exported_Functions_Group7 Interrupt and Flag management
  * @{
 - HAL_DSI_EnableWrapper()             : Enable the DSI wrapper.
 - HAL_DSI_DisableWrapper()            : Disable the DSI wrapper.
 - HAL_DSI_GetFlag()                   : Retrieve flags.
 - HAL_DSI_ClearFlag()                 : Clear the specified DSI flags.
 - HAL_DSI_EnableIT()                  : Enable the specified DSI interrupts.
 - HAL_DSI_DisableIT()                 : Disable the specified DSI interrupts.
 - HAL_DSI_IsEnabledIT()               : Check whether or not the specified DSI interrupt is set.
 - HAL_DSI_GetHostErrorGrp0Flag()      : Retrieve hot error groupe0 flag.
 - HAL_DSI_EnableHostErrorGrp0IT()     : Enable host error groupe0 interruption.
 - HAL_DSI_DisableHostErrorGrp0IT()    : Disable host error groupe0 interruption.
 - HAL_DSI_IsEnabledHostErrorGrp0IT()  : Check whether or not host error group 0 interruption is set.
 - HAL_DSI_GetHostErrorGrp1Flag()      : Retrieve hot error groupe1 flag.
 - HAL_DSI_EnableHostErrorGrp1IT()     : Enable host error groupe1 interruption.
 - HAL_DSI_DisableHostErrorGrp1IT()    : Disable host error groupe1 interruption.
 - HAL_DSI_IsEnabledHostErrorGrp1IT()  : Check whether or not host error group 1 interruption is set.
  */

/**
  * @brief  Enable the DSI wrapper.
  * @param  hdsi  DSI handle
  */
__STATIC_INLINE void HAL_DSI_EnableWrapper(hal_dsi_handle_t *hdsi)
{
  SET_BIT(((DSI_TypeDef *)((uint32_t) hdsi->instance))->WCR, DSI_WCR_DSIEN);
}

/**
  * @brief  Disable the DSI wrapper.
  * @param  hdsi  DSI handle
  */
__STATIC_INLINE void HAL_DSI_DisableWrapper(hal_dsi_handle_t *hdsi)
{
  CLEAR_BIT(((DSI_TypeDef *)((uint32_t) hdsi->instance))->WCR, DSI_WCR_DSIEN);
}

/* Interrupt & Flag management */
/**
  * @brief  Get the DSI pending flags.
  * @param  hdsi  DSI handle
  * @param  flag   Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg HAL_DSI_FLAG_TE   : Tearing Effect Interrupt Flag
  *            @arg HAL_DSI_FLAG_ER   : End of Refresh Interrupt Flag
  *            @arg HAL_DSI_FLAG_PLLL : PLL Lock Interrupt Flag
  *            @arg HAL_DSI_FLAG_PLLU : PLL Unlock Interrupt Flag
  *            @arg HAL_DSI_FLAG_RR   : Regulator Ready Interrupt Flag
  * @retval The state of DSI flag (0 or 1).
  */
__STATIC_INLINE uint32_t HAL_DSI_GetFlag(const hal_dsi_handle_t *hdsi, uint32_t flag)
{
  return ((READ_BIT(((DSI_TypeDef *)((uint32_t) hdsi->instance))->WISR,
                    (uint32_t)flag) == (uint32_t)flag) ? 1U : 0U);
}

/**
  * @brief Clear the specified DSI flags.
  * @param  hdsi  DSI handle
  * @param flag   Specify the DSI flag to clear
  *          This parameter can be any combination of the following values:
  *            @arg DSI_FLAG_TE   : Tearing Effect Interrupt Flag
  *            @arg HAL_DSI_FLAG_ER   : End of Refresh Interrupt Flag
  *            @arg HAL_DSI_FLAG_PLLL : PLL Lock Interrupt Flag
  *            @arg HAL_DSI_FLAG_PLLU : PLL Unlock Interrupt Flag
  *            @arg HAL_DSI_FLAG_RR   : Regulator Ready Interrupt Flag
  */
__STATIC_INLINE void HAL_DSI_ClearFlag(hal_dsi_handle_t *hdsi, uint32_t flag)
{
  SET_BIT(((DSI_TypeDef *)(uint32_t)(hdsi->instance))->WIFCR, flag);
}

/**
  * @brief Enable the specified DSI interrupts.
  * @param  hdsi  DSI handle
  * @param interrupt Specify the DSI interrupt to enable
  *          This parameter can be any combination of the following values:
  *            @arg HAL_DSI_IT_TE  : Tearing Effect Interrupt flag
  *            @arg HAL_DSI_IT_ER  : End of Refresh Interrupt flag
  *            @arg HAL_DSI_IT_PLLL: PLL Lock Interrupt flag
  *            @arg HAL_DSI_IT_PLLU: PLL Unlock Interrupt flag
  *            @arg HAL_DSI_IT_RR  : Regulator Ready Interrupt flag
  */
__STATIC_INLINE void HAL_DSI_EnableIT(hal_dsi_handle_t *hdsi, uint32_t interrupt)
{
  SET_BIT(((DSI_TypeDef *)(uint32_t)(hdsi->instance))->WIER, interrupt);
}

/**
  * @brief Disable the specified DSI interrupts.
  * @param  hdsi  DSI handle
  * @param interrupt Specify the DSI interrupt to disable
  *          This parameter can be any combination of the following values:
  *            @arg HAL_DSI_IT_TE  : Tearing Effect Interrupt flag
  *            @arg HAL_DSI_IT_ER  : End of Refresh Interrupt flag
  *            @arg HAL_DSI_IT_PLLL: PLL Lock Interrupt flag
  *            @arg HAL_DSI_IT_PLLU: PLL Unlock Interrupt flag
  *            @arg HAL_DSI_IT_RR  : Regulator Ready Interrupt flag
  */
__STATIC_INLINE void HAL_DSI_DisableIT(hal_dsi_handle_t *hdsi, uint32_t interrupt)
{
  CLEAR_BIT(((DSI_TypeDef *)(uint32_t)(hdsi->instance))->WIER, interrupt);
}

/**
  * @brief  Check whether the specified DSI interrupt is enabled or not
  * @param  hdsi  DSI handle
  * @param  interrupt  Specify the DCMI interrupt to check their status
  *          This parameter can be one of the following values:
  *            @arg HAL_DSI_IT_TE  : Tearing Effect Interrupt flag
  *            @arg HAL_DSI_IT_ER  : End of Refresh Interrupt flag
  *            @arg HAL_DSI_IT_PLLL: PLL Lock Interrupt flag
  *            @arg HAL_DSI_IT_PLLU: PLL Unlock Interrupt flag
  *            @arg HAL_DSI_IT_RR  : Regulator Ready Interrupt flag
  * @retval The state of DSI interrupt (0 or 1).
  */
__STATIC_INLINE uint32_t HAL_DSI_IsEnabledIT(const hal_dsi_handle_t *hdsi, uint32_t interrupt)
{
  return ((READ_BIT(((DSI_TypeDef *)((uint32_t) hdsi->instance))->WIER,
                    (uint32_t)interrupt) == (uint32_t)interrupt) ? 1U : 0U);
}

/**
  * @brief  Get the DSI pending flags.
  * @param  hdsi  DSI handle
  * @param  flag  Specify the DCMI flag to check their status
  *          This parameter can be any combination of the following values:
  *            @arg HAL_DSI_FLAG_ACK   : Acknowledge Interrupt Flag
  *            @arg HAL_DSI_FLAG_PHY   : PHY Interrupt Flag
  * @retval The state of DSI flag (0 or 1).
  */
__STATIC_INLINE uint32_t HAL_DSI_GetHostErrorGrp0Flag(const hal_dsi_handle_t *hdsi, uint32_t flag)
{
  return ((READ_BIT(((DSI_TypeDef *)((uint32_t) hdsi->instance))->ISR[0],
                    (uint32_t)flag) == (uint32_t)flag) ? 1U : 0U);
}

/**
  * @brief Enable the specified DSI interrupts.
  * @param  hdsi  DSI handle
  * @param interrupt Specify the DSI interrupt to enable
  *          This parameter can be any combination of the following values:
  *            @arg HAL_DSI_IT_ACK  : Acknowledge Interrupt flag
  *            @arg HAL_DSI_IT_PHY  : PHY Interrupt flag
  */
__STATIC_INLINE void HAL_DSI_EnableHostErrorGrp0IT(hal_dsi_handle_t *hdsi, uint32_t interrupt)
{
  SET_BIT(((DSI_TypeDef *)(uint32_t)(hdsi->instance))->IER[0], interrupt);
}

/**
  * @brief Disable the specified DSI interrupts.
  * @param  hdsi  DSI handle
  * @param interrupt Specify the DSI interrupt to disable
  *          This parameter can be any combination of the following values:
  *            @arg HAL_DSI_IT_ACK  : Acknowledge Interrupt flag
  *            @arg HAL_DSI_IT_PHY  : PHY Interrupt flag
  */
__STATIC_INLINE void HAL_DSI_DisableHostErrorGrp0IT(hal_dsi_handle_t *hdsi, uint32_t interrupt)
{
  CLEAR_BIT(((DSI_TypeDef *)(uint32_t)(hdsi->instance))->IER[0], interrupt);
}

/**
  * @brief  Check whether the specified DSI interrupt is enabled or not
  * @param  hdsi  DSI handle
  * @param  interrupt  Specify the DCMI interrupt to check their status
  *          This parameter can be one of the following values:
  *            @arg HAL_DSI_IT_ACK  : Acknowledge Interrupt flag
  *            @arg HAL_DSI_IT_PHY  : PHY Interrupt flag
  * @retval The state of DSI interrupt (0 or 1)
  */
__STATIC_INLINE uint32_t HAL_DSI_IsEnabledHostErrorGrp0IT(const hal_dsi_handle_t *hdsi, uint32_t interrupt)
{
  return ((READ_BIT(((DSI_TypeDef *)((uint32_t) hdsi->instance))->IER[0],
                    (uint32_t)interrupt) == (uint32_t)interrupt) ? 1U : 0U);
}

/**
  * @brief  Get the DSI pending flags.
  * @param  hdsi  DSI handle
  * @param  flag   Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg HAL_DSI_FLAG_TX   : Transmission Interrupt Flag
  *            @arg HAL_DSI_FLAG_RX   : Reception Interrupt Flag
  *            @arg HAL_DSI_FLAG_CRC  : CRC Interrupt Flag
  *            @arg HAL_DSI_FLAG_PSE  : Packet Size Interrupt Flag
  *            @arg HAL_DSI_FLAG_EOT  : End Of Transmission  Interrupt Flag
  *            @arg HAL_DSI_FLAG_OVF  : FIFO overflow Interrupt Flag
  *            @arg HAL_DSI_FLAG_PB   : Payload Buffer Underflow Interrupt Flag
  *            @arg HAL_DSI_FLAG_ECC  : ECC Interrupt Flag
  *            @arg HAL_DSI_FLAG_GEN  :  Generic FIFO related Interrupt Flag
  * @retval The state of DSI flag (0 or 1).
  */
__STATIC_INLINE uint32_t HAL_DSI_GetHostErrorGrp1Flag(const hal_dsi_handle_t *hdsi, uint32_t flag)
{
  return ((READ_BIT(((DSI_TypeDef *)((uint32_t) hdsi->instance))->ISR[1],
                    (uint32_t)flag) == (uint32_t)flag) ? 1U : 0U);
}

/**
  * @brief Enable the specified DSI interrupts.
  * @param  hdsi  DSI handle
  * @param interrupt Specify the DSI interrupt to enable
  *          This parameter can be any combination of the following values:
  *            @arg HAL_DSI_IT_TX   : Transmission Interrupt flag
  *            @arg HAL_DSI_IT_RX   : Reception Interrupt flag
  *            @arg HAL_DSI_IT_CRC  : CRC Interrupt flag
  *            @arg HAL_DSI_IT_PSE  : Packet Size Interrupt flag
  *            @arg HAL_DSI_IT_EOT  : End Of Transmission  Interrupt flag
  *            @arg HAL_DSI_IT_OVF  : FIFO overflow Interrupt flag
  *            @arg HAL_DSI_IT_PB   : Payload Buffer Underflow Interrupt flag
  *            @arg HAL_DSI_IT_ECC  : ECC Interrupt flag
  *            @arg HAL_DSI_IT_GEN  :  Generic FIFO related Interrupt flag
  */
__STATIC_INLINE void HAL_DSI_EnableHostErrorGrp1IT(hal_dsi_handle_t *hdsi, uint32_t interrupt)
{
  SET_BIT(((DSI_TypeDef *)(uint32_t)(hdsi->instance))->IER[1], interrupt);
}

/**
  * @brief Disable the specified DSI interrupts.
  * @param  hdsi  DSI handle
  * @param interrupt Specify the DSI interrupt to disable
  *          This parameter can be any combination of the following values:
  *            @arg HAL_DSI_IT_TX   : Transmission Interrupt flag
  *            @arg HAL_DSI_IT_RX   : Reception Interrupt flag
  *            @arg HAL_DSI_IT_CRC  : CRC Interrupt flag
  *            @arg HAL_DSI_IT_PSE  : Packet Size Interrupt flag
  *            @arg HAL_DSI_IT_EOT  : End Of Transmission  Interrupt flag
  *            @arg HAL_DSI_IT_OVF  : FIFO overflow Interrupt flag
  *            @arg HAL_DSI_IT_PB   : Payload Buffer Underflow Interrupt flag
  *            @arg HAL_DSI_IT_ECC  : ECC Interrupt flag
  *            @arg HAL_DSI_IT_GEN  :  Generic FIFO related Interrupt flag
  */
__STATIC_INLINE void HAL_DSI_DisableHostErrorGrp1IT(hal_dsi_handle_t *hdsi, uint32_t interrupt)
{
  CLEAR_BIT(((DSI_TypeDef *)(uint32_t)(hdsi->instance))->IER[1], interrupt);
}

/**
  * @brief  Check whether the specified DSI interrupt is enabled or not
  * @param  hdsi  DSI handle
  * @param  interrupt  Specify the DCMI interrupt to check their status
  *          This parameter can be one of the following values:
  *            @arg HAL_DSI_IT_TX   : Transmission Interrupt Flag
  *            @arg HAL_DSI_IT_RX   : Reception Interrupt Flag
  *            @arg HAL_DSI_IT_CRC  : CRC Interrupt Flag
  *            @arg HAL_DSI_IT_PSE  : Packet Size Interrupt Flag
  *            @arg HAL_DSI_IT_EOT  : End Of Transmission  Interrupt Flag
  *            @arg HAL_DSI_IT_OVF  : FIFO overflow Interrupt Flag
  *            @arg HAL_DSI_IT_PB   : Payload Buffer Underflow Interrupt Flag
  *            @arg HAL_DSI_IT_ECC  : ECC Interrupt Flag
  *            @arg HAL_DSI_IT_GEN  :  Generic FIFO related Interrupt Flag
  * @retval The state of DSI interrupt (0 or 1).
  */
__STATIC_INLINE uint32_t HAL_DSI_IsEnabledHostErrorGrp1IT(const hal_dsi_handle_t *hdsi, uint32_t interrupt)
{
  return ((READ_BIT(((DSI_TypeDef *)((uint32_t) hdsi->instance))->IER[1],
                    (uint32_t)interrupt) == (uint32_t)interrupt) ? 1U : 0U);
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* DSI */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_HAL_DSI_H */
