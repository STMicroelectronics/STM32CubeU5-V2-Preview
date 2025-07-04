/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_dsi.c
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the DSI peripheral:
  *           + Initialization and de-initialization functions
  *           + Configuration functions
  *           + IO operation functions
  *           + Peripheral State and Errors functions
  *
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

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup DSI
  * @{
# DSI peripheral overview
-The DSI Host integrated inside STM32 microcontrollers provides a high-speed communication interface that allows
 the microcontroller to communicate with a display using a reduced pin count.
 This interface is fully configurable, making it easy to connect DSI displays available today on the market.

# How to use this driver

## The HAL DSI driver can be used as follows:

- Declare a hal_dsi_handle_t handle structure, for example:  hal_dsi_handle_t  hdsi;

- Initialize the DSI low level resources:
  - Enable the DSI interface clock (if not enabled in HAL_DSI_Init() when USE_HAL_DSI_CLK_ENABLE_MODEL
  set to HAL_CLK_ENABLE_NO)
  - Configure the DSI clock source
  - NVIC configuration if you need to use interrupt process
    - Configure the DSI interrupt priority
    - Enable the NVIC DSI IRQ Channel

- Use HAL_DSI_Init() function to initialize the DSI handle and associate the physical instance.

- Configure the DSI PLL, D_PHY band control, PHY parameters, and DSI clock parameters using the HAL_DSI_SetConfig()

- Select the needed mode(s) as follows:

  - Configure the video mode using the HAL_DSI_SetConfigVideoMode() function

  - Configure the adapted command mode using the HAL_DSI_SetConfigAdaptedCommandMode() function

  - Configure the low power command using the HAL_DSI_SetConfigLPCommand () function

- Configure the timings in the DSI HOST clock lane timer using the HAL_DSI_SetConfigPhyTimer () function

- Configure the time-out using the HAL_DSI_SetConfigHostTimeouts() function

- And finally start the DSI display by calling HAL_DSI_Start().

## Callback registration

When the compilation flag **USE_HAL_DSI_REGISTER_CALLBACKS** is set to 1,
use Functions **HAL_DSI_RegisterXxxCallback()** to register an interrupt callback.

When the compilation flag is set to 0 or not defined, the callback registration feature is not available
and all callbacks are set to the corresponding weak functions.

## Configuration inside the DSI driver

Config defines                    | Description           | Default value | Note
--------------------------------- | --------------------- | ------------- | -------------------------------------------
USE_HAL_DSI_MODULE                | from hal_conf.h       | 1  | When set, HAL DSI module is enabled
USE_HAL_DSI_REGISTER_CALLBACKS    | from hal_conf.h       | 0  | When set, enable the register callbacks
USE_HAL_DSI_CLK_ENABLE_MODEL | from hal_conf.h | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
USE_HAL_CHECK_PARAM | from hal_conf.h | 0  | When set, the vital parameters (pointers or sizes) are checked in runtime
USE_ASSERT_DBG_PARAM              | from PreProcessor env | None | When defined, enable the params assert
USE_ASSERT_DBG_STATE              | from PreProcessor env | None | When defined, enable the state assert
USE_HAL_DSI_USER_DATA               | from hal_conf.h | 0   | When set, user data is defined in handle
USE_HAL_DSI_GET_LAST_ERRORS         | from hal_conf.h | 0   | When set, user can get the last error code
  */

#if defined(USE_HAL_DSI_MODULE) && (USE_HAL_DSI_MODULE == 1U)
#if defined(DSI)

/* Private constants ---------------------------------------------------------*/
/** @addtogroup DSI_Private_Constants
  * @{
  */
#define DSI_TIMEOUT_VALUE ((uint32_t)100U)    /*!< Timeout value for DSI operations, set to 100 milliseconds        */
/**
  * @}
  */
/* Private variables ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup DSI_CustomLane DSI CustomLane
  * @{
  */
#define DSI_SWAP_LANE_PINS          0x00U  /*!< 80-750Mbits/s */
/**
  * @}
  */

/** @defgroup DSI_DPHY_Slew_Rate DSI D-PHY Slew rate
  * @{
  */
#define DSI_DPHY_SLEW_HS_TX_SPEED        0x0EU       /*!< 80-750Mbits/s */
/**
  * @}
  */

/** @defgroup DSI_HS_PREPARE_Offset DSI HS Prepare Offset
  * @{
  */
#define DSI_HS_PREPARE_OFFSET0   0x00U    /*!< 100-120 & 120-160 & 240-320 MHz          */
#define DSI_HS_PREPARE_OFFSET1   0x01U    /*!< 80-100 & 160-200 & 200-240 & 320-390 MHz */
#define DSI_HS_PREPARE_OFFSET2   0x02U    /*!< 390-450 & 450-510 MHz                    */
/**
  * @}
  */

/**
  * @brief DSI get instance macro
  */
#define DSI_GET_INSTANCE(handle)  ((DSI_TypeDef *)((uint32_t)(handle)->instance))
/** @defgroup DSI_Private_Macros DSI Private Macros
  * @{
  */
/*! Macro to check that the PLL NDIV value is less than or equal to 511 */
#define IS_DSI_PLL_NDIV(ndiv)                       ((ndiv) <= 511U)

/*! Macro to check that the PLL NDIV value is less than or equal to 511 */

#define IS_DSI_PLL_IDF(idf)                         ((idf) <= 511U)
/*! Macro to check that the PLL NDIV value is less than or equal to 511 */
#define IS_DSI_PLL_ODF(odf)                         ((odf) <= 511U)

/*! Macro to check that the Auto Clock Lane Control is either disabled or enabled */
#define IS_DSI_AUTO_CLKLANE_CONTROL(auto_clk_lane)  (((auto_clk_lane) == HAL_DSI_AUTO_CLK_LANE_CTRL_DISABLE)\
                                                     || ((auto_clk_lane) == HAL_DSI_AUTO_CLK_LANE_CTRL_ENABLE))

/*! Macro to check that the number of lanes is either one or two */
#define IS_DSI_NUMBER_OF_LANES(number_of_lanes)     (((number_of_lanes) == HAL_DSI_DATA_1_LANE)\
                                                     || ((number_of_lanes) == HAL_DSI_DATA_2_LANES))

/*! Macro to check that the flow control is set to all */
#define IS_DSI_FLOW_CONTROL(flow_control)            (((flow_control) |\
                                                       HAL_DSI_FLOW_CONTROL_ALL) == HAL_DSI_FLOW_CONTROL_ALL)

/*! Macro to check that the color coding value is less than or equal to 5 */
#define IS_DSI_COLOR_CODING(color_coding)            ((color_coding) <= 5U)

/*! Macroto check that the loosely packed option is either enabled or disabled */
#define IS_DSI_LOOSELY_PACKED(loosely_packed)        (((loosely_packed) == HAL_DSI_LOOSELY_PACKED_ENABLE)\
                                                      || ((loosely_packed) == HAL_DSI_LOOSELY_PACKED_DISABLE))

/*! Macroto check that the data enable polarity is either active high or active low */
#define IS_DSI_DE_POLARITY(data_enable)              (((data_enable) == HAL_DSI_DATA_ENABLE_ACTIVE_HIGH)\
                                                      || ((data_enable) == HAL_DSI_DATA_ENABLE_ACTIVE_LOW))

/*! Macro to check that the vsync polarity is either active high or active low */
#define IS_DSI_VSYNC_POLARITY(vsync)                (((vsync) == HAL_DSI_VSYNC_ACTIVE_HIGH)\
                                                     || ((vsync) == HAL_DSI_VSYNC_ACTIVE_LOW))
/*! Macro to check that the hsync polarity is either active high or active low */
#define IS_DSI_HSYNC_POLARITY(hsync)                (((hsync) == HAL_DSI_HSYNC_ACTIVE_HIGH)\
                                                     || ((hsync) == HAL_DSI_HSYNC_ACTIVE_LOW))

/*! Macro to check that the video mode type is either number of pulses, number of events, or burst */
#define IS_DSI_VIDEO_MODE_TYPE(video_mode_type)     (((video_mode_type) == HAL_DSI_VIDEO_MODE_NB_PULSES)    \
                                                     || ((video_mode_type) == HAL_DSI_VIDEO_MODE_NB_EVENTS) \
                                                     || ((video_mode_type) == HAL_DSI_VIDEO_MODE_BURST_MODE_BURST))
/*! Macro to check that the color mode is either full or eight */
#define IS_DSI_COLOR_MODE(color_mode)               (((color_mode) == HAL_DSI_COLOR_MODE_FULL)\
                                                     || ((color_mode) == HAL_DSI_COLOR_MODE_EIGHT))
/*! Macro to check that the display is either on or off */
#define IS_DSI_SHUT_DOWN(display)                 (((display) == HAL_DSI_DISPLAY_ON) \
                                                   || ((display) == HAL_DSI_DISPLAY_OFF))
/*! Macro to check that the low power command is either disabled or enabled */
#define IS_DSI_LP_COMMAND(lp_command)               (((lp_command) == HAL_DSI_LP_COMMAND_DISABLE)\
                                                     || ((lp_command) == HAL_DSI_LP_COMMAND_ENABLE))
/*! Macro to check that the low power horizontal front porch is either disabled or enabled */
#define IS_DSI_LP_HFP(lp_hfp)                        (((lp_hfp) == HAL_DSI_LP_HFP_DISABLE) \
                                                      || ((lp_hfp) == HAL_DSI_LP_HFP_ENABLE))

/*! Macro to check that the low power horizontal back porch is either disabled or enabled */
#define IS_DSI_LP_HBP(lp_hbp)                        (((lp_hbp) == HAL_DSI_LP_HBP_DISABLE) \
                                                      || ((lp_hbp) == HAL_DSI_LP_HBP_ENABLE))

/*! Macro to check that the low power vertical active is either disabled or enabled */
#define IS_DSI_LP_VACTIVE(lp_vactive)               (((lp_vactive) == HAL_DSI_LP_VACT_DISABLE)\
                                                     || ((lp_vactive) == HAL_DSI_LP_VACT_ENABLE))
/*! Macro to check that the low power vertical front porch is either disabled or enabled */
#define IS_DSI_LP_VFP(lp_vfp)                        (((lp_vfp) == HAL_DSI_LP_VFP_DISABLE) \
                                                      || ((lp_vfp) == HAL_DSI_LP_VFP_ENABLE))

/*! Macro to check that the low power vertical back porch is either disabled or enabled */
#define IS_DSI_LP_VBP(lp_vbp)                        (((lp_vbp) == HAL_DSI_LP_VBP_DISABLE) \
                                                      || ((lp_vbp) == HAL_DSI_LP_VBP_ENABLE))

/*! Macro to check that the low power VSYNC is either disabled or enabled */
#define IS_DSI_LP_VSYNC(lp_vsync)                    (((lp_vsync) == HAL_DSI_LP_VSYNC_DISABLE)\
                                                      || ((lp_vsync) == HAL_DSI_LP_VSYNC_ENABLE))
/*! Macro to check that the frame BTAA acknowledge is either disabled or enabled */

#define IS_DSI_FBTAA(frame_bta_acknowledge)         (((frame_bta_acknowledge)  == HAL_DSI_FBTAA_DISABLE)\
                                                     || ((frame_bta_acknowledge) == HAL_DSI_FBTAA_ENABLE))
/*! Macro to check that the TE source is either DSILINK or external */
#define IS_DSI_TE_SOURCE(te_source)                 (((te_source) == HAL_DSI_TE_SOURCE_DSILINK) \
                                                     || ((te_source) == HAL_DSI_TE_SOURCE_EXTERNAL))

/*! Macro to check that the TE polarity is either rising edge or falling edge */
#define IS_DSI_TE_POLARITY(te_polarity)             (((te_polarity) == HAL_DSI_TE_POLARITY_RISING_EDGE)\
                                                     || ((te_polarity) == HAL_DSI_TE_POLARITY_FALLING_EDGE))

/*! Macro to check that the automatic refresh is either disabled or enabled */

#define IS_DSI_AUTOMATIC_REFRESH(automatic_refresh)  (((automatic_refresh) == HAL_DSI_AR_DISABLE)\
                                                      || ((automatic_refresh) == HAL_DSI_AR_ENABLE))

/*! Macro to check that the VS polarity is either falling or rising */
#define IS_DSI_VS_POLARITY(vs_polarity)              (((vs_polarity) == HAL_DSI_VSYNC_FALLING)\
                                                      || ((vs_polarity) == HAL_DSI_VSYNC_RISING))

/*! Macro to check that the TE acknowledge request is either disabled or enabled */
#define IS_DSI_TE_ACK_REQUEST(te_acknowledge_request) (((te_acknowledge_request) == HAL_DSI_TE_ACKNOWLEDGE_DISABLE)\
                                                       || ((te_acknowledge_request) == HAL_DSI_TE_ACKNOWLEDGE_ENABLE))

/*! Macro to check that the acknowledge request is either disabled or enabled */
#define IS_DSI_ACK_REQUEST(acknowledge_request)      (((acknowledge_request) == DSI_ACKNOWLEDGE_DISABLE)\
                                                      || ((acknowledge_request) == DSI_ACKNOWLEDGE_ENABLE))

/*! Macro to check that the low power group short write  is either disabled or enabled */
#define IS_DSI_LP_GSW0P(LP_GSW0P)                   (((LP_GSW0P) == HAL_DSI_LP_SHORT_WRITE_GEN_NO_PARAM_DISABLE)\
                                                     || ((LP_GSW0P) == HAL_DSI_LP_SHORT_WRITE_GEN_NO_PARAM_ENABLE))

/*! Macro to check that the low power GSW1P is either disabled or enabled */
#define IS_DSI_LP_GSW1P(LP_GSW1P)                   (((LP_GSW1P) == HAL_DSI_LP_SHORT_WRITE_GEN_1_PARAM_DISABLE)\
                                                     || ((LP_GSW1P) == HAL_DSI_LP_SHORT_WRITE_GEN_1_PARAM_ENABLE))

/*! Macro to check that the low power GSW2P is either disabled or enabled */
#define IS_DSI_LP_GSW2P(LP_GSW2P)                   (((LP_GSW2P) == HAL_DSI_LP_SHORT_WRITE_GEN_2_PARAM_DISABLE)\
                                                     || ((LP_GSW2P) == HAL_DSI_LP_SHORT_WRITE_GEN_2_PARAM_ENABLE))

/*! Macro to check that the low power GSR0P is either disabled or enabled */
#define IS_DSI_LP_GSR0P(LP_GSR0P)                   (((LP_GSR0P) == HAL_DSI_LP_SHORT_READ_GEN_NO_PARAM_DISABLE)\
                                                     || ((LP_GSR0P) == HAL_DSI_LP_SHORT_READ_GEN_NO_PARAM_ENABLE))

/*! Macro to check that the low power GSR1P is either disabled or enabled */
#define IS_DSI_LP_GSR1P(LP_GSR1P)                   (((LP_GSR1P) == HAL_DSI_LP_SHORT_READ_GEN_1_PARAM_DISABLE)\
                                                     || ((LP_GSR1P) == HAL_DSI_LP_SHORT_READ_GEN_1_PARAM_ENABLE))

/*! Macro to check that the low power GSR2P is either disabled or enabled */
#define IS_DSI_LP_GSR2P(LP_GSR2P)                   (((LP_GSR2P) == HAL_DSI_LP_SHORT_READ_GEN_2_PARAM_DISABLE)\
                                                     || ((LP_GSR2P) == HAL_DSI_LP_SHORT_READ_GEN_2_PARAM_ENABLE))

/*! Macro to check that the low power GLW is either disabled or enabled */
#define IS_DSI_LP_GLW(LP_GLW)                       (((LP_GLW) == HAL_DSI_LP_LONG_WRITE_GEN_TX_DISABLE)\
                                                     || ((LP_GLW) == HAL_DSI_LP_LONG_WRITE_GEN_TX_ENABLE))

/*! Macro to check that the low power DSW0P is either disabled or enabled */
#define IS_DSI_LP_DSW0P(LP_DSW0P)                   (((LP_DSW0P) == HAL_DSI_LP_SHORT_WRITE_DCS_TX_NO_PARAM_DISABLE)\
                                                     || ((LP_DSW0P) == HAL_DSI_LP_SHORT_WRITE_DCS_TX_NO_PARAM_ENABLE))
/*! Macro to check that the low power DSW1P is either disabled or enabled */
#define IS_DSI_LP_DSW1P(LP_DSW1P)                   (((LP_DSW1P) == HAL_DSI_LP_DCS_SHORT_WRITE_1_PARAM_DISABLE)\
                                                     || ((LP_DSW1P) == HAL_DSI_LP_DCS_SHORT_WRITE_1_PARAM_ENABLE))

/*! Macro to check that the low power DSR0P is either disabled or enabled */
#define IS_DSI_LP_DSR0P(LP_DSR0P)                   (((LP_DSR0P) == HAL_DSI_LP_SHORT_READ_DCS_TX_NO_PARAM_DISABLE)\
                                                     || ((LP_DSR0P) == HAL_DSI_LP_SHORT_READ_DCS_TX_NO_PARAM_ENABLE))

/*! Macro to check that the low power DLW is either disabled or enabled */
#define IS_DSI_LP_DLW(LP_DLW)                       (((LP_DLW) == HAL_DSI_LP_LONG_WRITE_DCS_TX_DISABLE)\
                                                     || ((LP_DLW) == HAL_DSI_LP_LONG_WRITE_DCS_TX_ENABLE))

/*! Macro to check that the low power MRDP is either disabled or enabled */
#define IS_DSI_LP_MRDP(LP_MRDP)                     (((LP_MRDP) == HAL_DSI_LP_MAX_READ_PKT_DISABLE)\
                                                     || ((LP_MRDP) == HAL_DSI_LP_MAX_READ_PKT_ENABLE))

/*! Macro to check that the short write packet type is one of the defined types */
#define IS_DSI_SHORT_WRITE_PACKET_TYPE(mode)        (((mode) == HAL_DSI_SHORT_WRITE_PKT_DCS_NO_PARAM)    \
                                                     || ((mode) == HAL_DSI_SHORT_WRITE_PKT_DCS_1_PARAM)  \
                                                     || ((mode) == HAL_DSI_SHORT_WRITE_PKT_GEN_NO_PARAM) \
                                                     || ((mode) == HAL_DSI_SHORT_WRITE_PKT_GEN_1_PARAM)  \
                                                     || ((mode) == HAL_DSI_SHORT_WRITE_PKT_GEN_2_PARAM))

/*! Macro to check that the long write packet type is one of the defined types */
#define IS_DSI_LONG_WRITE_PACKET_TYPE(mode)         (((mode) == HAL_DSI_LONG_WRITE_PKT_DCS) \
                                                     || ((mode) == HAL_DSI_LONG_WRITE_PKT_GEN))

/*! Macro to check that the read packet type is one of the defined types */
#define IS_DSI_READ_SHORT_PACKET_TYPE(mode)          (((mode) == HAL_DSI_SHORT_READ_PKT_DCS)             \
                                                      || ((mode) == HAL_DSI_SHORT_READ_PKT_GEN_NO_PARAM) \
                                                      || ((mode) == HAL_DSI_SHORT_READ_PKT_GEN_1_PARAM)  \
                                                      || ((mode) == HAL_DSI_SHORT_READ_PKT_GEN_2_PARAM))

/*! Macro to check that the lane group is either clock lane or data lanes */
#define IS_DSI_LANE_GROUP(lane_group)                (((lane_group) == HAL_DSI_FORCE_CLK_LANE) \
                                                      || ((lane_group) == HAL_DSI_FORCE_DATA_LANES))

/*! Macro to check that the custom lane is swap lane pins */
#define IS_DSI_CUSTOM_LANE(custom_lane)              ((custom_lane) == DSI_SWAP_LANE_PINS)

/*! Macro to check that the lane is either clock lane, data lane 0, or data lane 1 */
#define IS_DSI_LANE(lane)                           (((lane) == HAL_DSI_SWAP_CLK_LANE)       \
                                                     || ((lane) == HAL_DSI_SWAP_DATA_LANE_0) \
                                                     || ((lane) == HAL_DSI_SWAP_DATA_LANE_1))

/*! Macro to check that the channel id  is one of the defined types */
#define IS_DSI_VIRTUAL_CHANNEL_ID(channel_id)       (((channel_id) == HAL_DSI_VIRTUAL_CHANNEL_ID_0)     \
                                                     || ((channel_id) == HAL_DSI_VIRTUAL_CHANNEL_ID_1) \
                                                     || ((channel_id) == HAL_DSI_VIRTUAL_CHANNEL_ID_2) \
                                                     || ((channel_id) == HAL_DSI_VIRTUAL_CHANNEL_ID_3))

/*! Macro to check that the VCO frequency range is within the defined limits */
#define IS_DSI_DPHY_VCO_FREQUENCY_RANGE(vco_freq_range) (((vco_freq_range) == HAL_DSI_VCO_FREQ_RANGE_500MHZ_800MHZ) \
                                                         ||((vco_freq_range) == HAL_DSI_VCO_FREQ_RANGE_800MHZ_1GHZ))

/*! Macro to check that the band control frequency range is within the defined limits */
#define IS_DSI_DPHY_BAND_CTL_FRANGE(phy_freq_range) (((phy_freq_range) == HAL_DSI_DPHY_FREQ_RANGE_80MHZ_100MHZ)     \
                                                     || ((phy_freq_range) == HAL_DSI_DPHY_FREQ_RANGE_100MHZ_120MHZ) \
                                                     || ((phy_freq_range) == HAL_DSI_DPHY_FREQ_RANGE_120MHZ_160MHZ) \
                                                     || ((phy_freq_range) == HAL_DSI_DPHY_FREQ_RANGE_160MHZ_200MHZ) \
                                                     || ((phy_freq_range) == HAL_DSI_DPHY_FREQ_RANGE_200MHZ_240MHZ) \
                                                     || ((phy_freq_range) == HAL_DSI_DPHY_FREQ_RANGE_240MHZ_320MHZ) \
                                                     || ((phy_freq_range) == HAL_DSI_DPHY_FREQ_RANGE_320MHZ_390MHZ) \
                                                     || ((phy_freq_range) == HAL_DSI_DPHY_FREQ_RANGE_390MHZ_450MHZ) \
                                                     || ((phy_freq_range) == HAL_DSI_DPHY_FREQ_RANGE_450MHZ_510MHZ))

/*! Macro to check that the low power offset is within the defined limits */
#define IS_DSI_DPHY_LOW_POWER_OFFSET(phy_low_power_offset) (((phy_low_power_offset) == HAL_DPHY_LP_OFFSSET_0_CLKP)    \
                                                            || ((phy_low_power_offset) == HAL_DPHY_LP_OFFSSET_1_CLKP) \
                                                            || ((phy_low_power_offset) == HAL_DPHY_LP_OFFSSET_2_CLKP) \
                                                            || ((phy_low_power_offset) == HAL_DPHY_LP_OFFSSET_3_CLKP) \
                                                            || ((phy_low_power_offset) == HAL_DPHY_LP_OFFSSET_4_CLKP) \
                                                            || ((phy_low_power_offset) == HAL_DPHY_LP_OFFSSET_5_CLKP) \
                                                            || ((phy_low_power_offset) == HAL_DPHY_LP_OFFSSET_6_CLKP) \
                                                            || ((phy_low_power_offset) == HAL_DPHY_LP_OFFSSET_7_CLKP) \
                                                            || ((phy_low_power_offset)               \
                                                                == HAL_DPHY_LP_OFFSSET_MINUS_1_CLKP) \
                                                            || ((phy_low_power_offset)               \
                                                                == HAL_DPHY_LP_OFFSSET_MINUS_2_CLKP) \
                                                            || ((phy_low_power_offset)               \
                                                                == HAL_DPHY_LP_OFFSSET_MINUS_3_CLKP) \
                                                            || ((phy_low_power_offset)               \
                                                                == HAL_DPHY_LP_OFFSSET_MINUS_4_CLKP) \
                                                            || ((phy_low_power_offset)               \
                                                                == HAL_DPHY_LP_OFFSSET_MINUS_5_CLKP) \
                                                            || ((phy_low_power_offset)               \
                                                                == HAL_DPHY_LP_OFFSSET_MINUS_6_CLKP) \
                                                            || ((phy_low_power_offset)               \
                                                                == HAL_DPHY_LP_OFFSSET_MINUS_7_CLKP) \
                                                            || ((phy_low_power_offset)               \
                                                                == HAL_DPHY_LP_OFFSSET_MINUS_8_CLKP))

/*! Macro to check that the PLL loop is within the defined limits */
#define IS_DSI_PLL_LOOP_FILTER(pll_loop_filter) (((pll_loop_filter) == HAL_DSI_PLL_LOOP_FILTER_2000HZ_4400HZ)     \
                                                 || ((pll_loop_filter) == HAL_DSI_PLL_LOOP_FILTER_4400HZ_30900HZ) \
                                                 || ((pll_loop_filter) == HAL_DSI_PLL_LOOP_FILTER_30900HZ_50000HZ))

/*! Macro to check that the PLL charge pump is within the defined limits */
#define IS_DSI_PLL_CHARGEPUMP(pll_charge_pump) (((pll_charge_pump) == HAL_DSI_PLL_CHARGE_PUMP_2000HZ_4400HZ)      \
                                                || ((pll_charge_pump) == HAL_DSI_PLL_CHARGE_PUMP_4400HZ_14100HZ)  \
                                                || ((pll_charge_pump) == HAL_DSI_PLL_CHARGE_PUMP_30900HZ_45700HZ) \
                                                || ((pll_charge_pump) == HAL_DSI_PLL_CHARGE_PUMP_45700HZ_50000HZ))

/*! Macro to check that the interrupts are within the defined limits */
#define IS_DSI_INTERRUPT(interrupts) (((interrupts) == HAL_DSI_IT_TE)      \
                                      || ((interrupts) == HAL_DSI_IT_ER)   \
                                      || ((interrupts) == HAL_DSI_IT_PLLL) \
                                      || ((interrupts) == HAL_DSI_IT_PLLU) \
                                      || ((interrupts) == HAL_DSI_IT_NONE) \
                                      || ((interrupts) == HAL_DSI_IT_ACK)  \
                                      || ((interrupts) == HAL_DSI_IT_TX)   \
                                      || ((interrupts) == HAL_DSI_IT_RX)   \
                                      || ((interrupts) == HAL_DSI_IT_CRC)  \
                                      || ((interrupts) == HAL_DSI_IT_PSE)  \
                                      || ((interrupts) == HAL_DSI_IT_EOT)  \
                                      || ((interrupts) == HAL_DSI_IT_OVF)  \
                                      || ((interrupts) == HAL_DSI_IT_PBU)  \
                                      || ((interrupts) == HAL_DSI_IT_ECC)  \
                                      || ((interrupts) == HAL_DSI_IT_PHY)  \
                                      || ((interrupts) == HAL_DSI_IT_GEN))

/**
  * @}
  */
/* Private function prototypes ---------------------------------------------------------------------------------------*/
/** @defgroup DSI_Private_Functions DSI Private Functions
  * @{
  */
static void DSI_ConfigPacketHeader(DSI_TypeDef *DSIx, hal_dsi_virtual_channel_t channel_id, uint32_t data_type,
                                   uint32_t data0,
                                   uint32_t data1);

static hal_status_t DSI_ShortWrite(hal_dsi_handle_t *hdsi,
                                   hal_dsi_virtual_channel_t channel_id,
                                   hal_dsi_short_write_packet_t mode,
                                   uint32_t first_param,
                                   uint32_t second_param);

static void DSI_ConfigBandControl(hal_dsi_handle_t *hdsi, const hal_dsi_config_t *p_config);

static void DSI_SetWrapperPLLTuning(hal_dsi_handle_t *hdsi, const hal_dsi_pll_config_t *p_pllinit);
/**
  * @}
  */
/* Private functions ---------------------------------------------------------*/
/** @defgroup DSI_Private_Functions DSI Private Functions
  * @{
  */
/**
  * @brief  Generic DSI packet header configuration.
  * @param  DSIx  Pointer to DSI register base
  * @param  channel_id Virtual channel ID of the header packet
  * @param  data_type  Packet data type of the header packet
  *                   This parameter can be any value of :
  *                      @arg DSI_SHORT_WRITE_PKT_Data_Type
  *                      @arg DSI_LONG_WRITE_PKT_Data_Type
  *                      @arg DSI_SHORT_READ_PKT_Data_Type
  *                      @arg DSI_MAX_RETURN_PKT_SIZE
  * @param  data0  Word count LSB
  * @param  data1  Word count MSB
  */
static void DSI_ConfigPacketHeader(DSI_TypeDef *DSIx,
                                   hal_dsi_virtual_channel_t channel_id,
                                   uint32_t data_type,
                                   uint32_t data0,
                                   uint32_t data1)
{
  /* Update the DSI packet header with new information */
  DSIx->GHCR = (data_type | (channel_id << 6U) | (data0 << 8U) | (data1 << 16U));
}

/**
  * @brief  write short DCS or short generic command.
  * @param  hdsi  pointer to a DSI_HandleTypeDef structure that contains
  *               the configuration information for the DSI.
  * @param  channel_id  Virtual channel ID.
  * @param  mode  DSI short packet data type.
  *               This parameter can be any value of @arg DSI SHORT WRITE PKT Data Type.
  * @param  first_param  DSC command or first generic parameter.
  *                 This parameter can be any value of @arg DSI DCS Command or a
  *                 generic command code.
  * @param  second_param  DSC parameter or second generic parameter.
  * @retval HAL_OK
  */
static hal_status_t DSI_ShortWrite(hal_dsi_handle_t *hdsi,
                                   hal_dsi_virtual_channel_t channel_id,
                                   hal_dsi_short_write_packet_t mode,
                                   uint32_t first_param,
                                   uint32_t second_param)
{
  uint32_t tickstart;

  DSI_TypeDef *p_dsi;

  tickstart = HAL_GetTick();

  p_dsi = DSI_GET_INSTANCE(hdsi);

  /* Wait for Command FIFO Empty */
  while (READ_BIT(DSI_GET_INSTANCE(hdsi)->GPSR, (DSI_GPSR_CMDFE)) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }
  }

  /* Configure the packet to send a short DCS command with 0 or 1 parameter */
  /* Update the DSI packet header with new information */
  p_dsi->GHCR = (mode | (channel_id << 6U) | (first_param << 8U) | (second_param << 16U));

  return HAL_OK;
}

/**
  * @brief  Configure Band Control Frequency and LPX Offset.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  p_config pointer to @ref hal_dsi_config_t structure.
  */
static void DSI_ConfigBandControl(hal_dsi_handle_t *hdsi, const hal_dsi_config_t *p_config)
{
  WRITE_REG(DSI_GET_INSTANCE(hdsi)->DPCBCR, p_config->phy_cfg.phy_frequency_range << DSI_DPCBCR_Pos);

  SET_BIT(DSI_GET_INSTANCE(hdsi)->DPCSRCR, DSI_DPHY_SLEW_HS_TX_SPEED);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->DPDL0BCR, p_config->phy_cfg.phy_frequency_range << DSI_DPDL0BCR_Pos);

  SET_BIT(DSI_GET_INSTANCE(hdsi)->DPDL0SRCR, DSI_DPHY_SLEW_HS_TX_SPEED);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->DPDL1BCR, p_config->phy_cfg.phy_frequency_range << DSI_DPDL1BCR_Pos);

  SET_BIT(DSI_GET_INSTANCE(hdsi)->DPDL1SRCR, DSI_DPHY_SLEW_HS_TX_SPEED);

  if ((p_config->phy_cfg.phy_frequency_range == HAL_DSI_DPHY_FREQ_RANGE_100MHZ_120MHZ) \
      || (p_config->phy_cfg.phy_frequency_range == HAL_DSI_DPHY_FREQ_RANGE_120MHZ_160MHZ) \
      || (p_config->phy_cfg.phy_frequency_range == HAL_DSI_DPHY_FREQ_RANGE_240MHZ_320MHZ))
  {
    WRITE_REG(DSI_GET_INSTANCE(hdsi)->DPDL0HSOCR, (DSI_HS_PREPARE_OFFSET0 << DSI_DPDL0HSOCR_Pos));

    WRITE_REG(DSI_GET_INSTANCE(hdsi)->DPDL1HSOCR, (DSI_HS_PREPARE_OFFSET0 << DSI_DPDL1HSOCR_Pos));
  }
  else if ((p_config->phy_cfg.phy_frequency_range == HAL_DSI_DPHY_FREQ_RANGE_80MHZ_100MHZ) \
           || (p_config->phy_cfg.phy_frequency_range == HAL_DSI_DPHY_FREQ_RANGE_160MHZ_200MHZ) \
           || (p_config->phy_cfg.phy_frequency_range == HAL_DSI_DPHY_FREQ_RANGE_200MHZ_240MHZ) \
           || (p_config->phy_cfg.phy_frequency_range == HAL_DSI_DPHY_FREQ_RANGE_320MHZ_390MHZ))
  {
    WRITE_REG(DSI_GET_INSTANCE(hdsi)->DPDL0HSOCR, (DSI_HS_PREPARE_OFFSET1 << DSI_DPDL0HSOCR_Pos));

    WRITE_REG(DSI_GET_INSTANCE(hdsi)->DPDL1HSOCR, (DSI_HS_PREPARE_OFFSET1 << DSI_DPDL1HSOCR_Pos));
  }
  else if ((p_config->phy_cfg.phy_frequency_range == HAL_DSI_DPHY_FREQ_RANGE_390MHZ_450MHZ) \
           || (p_config->phy_cfg.phy_frequency_range == HAL_DSI_DPHY_FREQ_RANGE_450MHZ_510MHZ))
  {
    WRITE_REG(DSI_GET_INSTANCE(hdsi)->DPDL0HSOCR, (DSI_HS_PREPARE_OFFSET2 << DSI_DPDL0HSOCR_Pos));

    WRITE_REG(DSI_GET_INSTANCE(hdsi)->DPDL1HSOCR, (DSI_HS_PREPARE_OFFSET2 << DSI_DPDL1HSOCR_Pos));
  }
  else
  {
    /* Nothing to do */
  }

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->DPDL0LPXOCR, p_config->phy_cfg.phy_low_pwr_offset);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->DPDL1LPXOCR, p_config->phy_cfg.phy_low_pwr_offset);
}

/**
  * @brief  Set Wrapper PLL Tuning and Charge Pump.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  p_pllinit  pointer to a hal_dsi_pll_config_t structure that contains
  *                  the PLL Clock structure definition for the DSI.
  */
static void DSI_SetWrapperPLLTuning(hal_dsi_handle_t *hdsi, const hal_dsi_pll_config_t *p_pllinit)
{

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->WRPCR, DSI_WRPCR_BC, p_pllinit->vco_range << DSI_WRPCR_BC_Pos);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->WPTR, (DSI_WPTR_LPF | DSI_WPTR_CP), p_pllinit->pll_loop_filter << DSI_WPTR_LPF_Pos
             | p_pllinit->pll_charge_pump << DSI_WPTR_CP_Pos);

}
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup DSI_Exported_Functions
  * @{
  */

/** @addtogroup DSI_Exported_Functions_Group1
  * @{
A set of functions allowing to initialize and deinitialize the DSI peripheral :
 - HAL_DSI_Init()   : Initialize the HAL DSI handle and associate it to a given DSI peripheral instance.
 - HAL_DSI_DeInit() : De-initialize the HAL DSI handle and stop any ongoing capture process.
  */

/**
  * @brief  Initialize the selected HAL DSI handle and associate a DSI peripheral instance.
  * @param  hdsi             Pointer to a hal_dsi_handle_t structure.
  * @param  instance          Specify the DSI instance.
  * @retval HAL_INVALID_PARAM Invalid parameter when hdsi pointer is NULL.
  * @retval HAL_OK            HAL DSI handle has been correctly initialized.
  */
hal_status_t HAL_DSI_Init(hal_dsi_handle_t *hdsi, hal_dsi_t instance)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_ALL_INSTANCE((DSI_TypeDef *)(uint32_t)instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hdsi == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdsi->instance = instance;
#if defined (USE_HAL_DSI_CLK_ENABLE_MODEL) && (USE_HAL_DSI_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_DSI);
#endif /* USE_HAL_DSI_CLK_ENABLE_MODEL */

#if defined(USE_HAL_DSI_REGISTER_CALLBACKS) && (USE_HAL_DSIS_REGISTER_CALLBACKS == 1U)
  hdsi->p_error_cb = HAL_DSI_ErrorCallback;
  hdsi->p_tearing_effect_cb = HAL_DSI_TearingEffectCallback;
  hdsi->p_refresh_cb = HAL_DSI_EndOfRefreshCallback;
#endif /* USE_HAL_DSI_REGISTER_CALLBACKS */

#if defined(USE_HAL_DSI_GET_LAST_ERRORS) && (USE_HAL_DSI_GET_LAST_ERRORS== 1U)
  hdsi->last_error_codes = HAL_DSI_ERROR_NONE;
#endif /* USE_HAL_DSI_GET_LAST_ERRORS */

#if defined(USE_HAL_DSI_USER_DATA) && (USE_HAL_DSI_USER_DATA == 1)
  p_dsi->p_user_data = NULL;
#endif /* USE_HAL_DSI_USER_DATA */

  hdsi->global_state = HAL_DSI_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  De-initializes the DSI peripheral registers to their default reset
  *         values.
  * @param  hdsi  pointer to a DSI_HandleTypeDef structure that contains
  *               the configuration information for the DSI.
  */
void HAL_DSI_DeInit(hal_dsi_handle_t *hdsi)
{
  DSI_TypeDef *p_dsi;

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_ALL_INSTANCE(DSI_GET_INSTANCE(hdsi)));

  p_dsi = DSI_GET_INSTANCE(hdsi);

  CLEAR_REG(p_dsi->WCR);
  CLEAR_REG(p_dsi->CR);
  CLEAR_REG(p_dsi->PCTLR);
  CLEAR_REG(p_dsi->WRPCR);
  CLEAR_REG(p_dsi->BCFGR);

#if defined(USE_HAL_DSI_USER_DATA) && (USE_HAL_DSI_USER_DATA == 1)
  p_dsi->p_user_data = NULL;
#endif /* USE_HAL_DSI_USER_DATA */

  /* Initialize the DSI state*/
  hdsi->global_state = HAL_DSI_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup DSI_Exported_Functions_Group2
  * @{
A set of functions allowing to configure the DSI peripheral:

- Global configuration :
  - HAL_DSI_SetConfig() : Configure the DSI according to the specified parameters.
  - HAL_DSI_GetConfig() : Retrieve the DSI configuration.
  */

/**
  * @brief  Configure the DSI with the specified parameters in the @ref hal_dsi_config_t.
  * @param  hdsi           pointer to @ref hal_dsi_handle_t structure.
  * @param  p_config          pointer to @ref hal_dsi_config_t structure.
  * @retval HAL_OK            configuration succeeded.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */

hal_status_t HAL_DSI_SetConfig(hal_dsi_handle_t *hdsi, const hal_dsi_config_t *p_config)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_INIT | (uint32_t)HAL_DSI_STATE_CONFIGURED);

  ASSERT_DBG_PARAM((p_config->tx_escape_clk_div) != NULL);
  ASSERT_DBG_PARAM(IS_DSI_NUMBER_OF_LANES(p_config->nbr_of_lanes));
  ASSERT_DBG_PARAM(IS_DSI_PLL_NDIV(p_config->pll_cfg.pll_ndiv));
  ASSERT_DBG_PARAM(IS_DSI_PLL_IDF(p_config->pll_cfg.pll_idf));
  ASSERT_DBG_PARAM(IS_DSI_PLL_ODF(p_config->pll_cfg.pll_odf));
  ASSERT_DBG_PARAM(IS_DSI_PLL_LOOP_FILTER(p_config->pll_cfg.pll_loop_filter));
  ASSERT_DBG_PARAM(IS_DSI_PLL_CHARGEPUMP(p_config->pll_cfg.pll_charge_pump));
  ASSERT_DBG_PARAM(IS_DSI_DPHY_VCO_FREQUENCY_RANGE(p_config->pll_cfg.vco_range));
  ASSERT_DBG_PARAM(IS_DSI_DPHY_BAND_CTL_FRANGE(p_config->phy_cfg.phy_frequency_range));
  ASSERT_DBG_PARAM(IS_DSI_DPHY_LOW_POWER_OFFSET(p_config->phy_cfg.phy_low_pwr_offset));


#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /**************** Turn on the Reference Bias and enable the DSI PLL ****************/

  SET_BIT(DSI_GET_INSTANCE(hdsi)->BCFGR, DSI_BCFGR_PWRUP);

  HAL_Delay(2);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->WRPCR, (DSI_WRPCR_PLL_NDIV | DSI_WRPCR_PLL_IDF | DSI_WRPCR_PLL_ODF),
             (((p_config->pll_cfg.pll_ndiv) << DSI_WRPCR_PLL_NDIV_Pos)
              | ((p_config->pll_cfg.pll_idf) << DSI_WRPCR_PLL_IDF_Pos)
              | ((p_config->pll_cfg.pll_odf) << DSI_WRPCR_PLL_ODF_Pos)));

  /************************ Set D-PHY Band Control registers ******************************/

  DSI_SetWrapperPLLTuning(hdsi, &p_config->pll_cfg);

  SET_BIT(DSI_GET_INSTANCE(hdsi)->WRPCR, DSI_WRPCR_PLLEN);

  HAL_Delay(1);

  tickstart = HAL_GetTick();

  while (HAL_DSI_GetFlag(hdsi, HAL_DSI_FLAG_PLLLS) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }
  }

  SET_BIT(DSI_GET_INSTANCE(hdsi)->CR, DSI_CR_EN);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->CCR, DSI_CCR_TXECKDIV, p_config->tx_escape_clk_div);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->PCTLR, (DSI_PCTLR_CKE | DSI_PCTLR_DEN));

  DSI_ConfigBandControl(hdsi, p_config);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL, (uint32_t)p_config->nbr_of_lanes);

  tickstart = HAL_GetTick();

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_1_LANE)
  {
    while (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_PSS0 | DSI_PSR_PSSC)) != (DSI_PSR_PSS0 | DSI_PSR_PSSC))
    {
      if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
      {
        return HAL_ERROR;
      }
    }
  }
  else
  {
    while (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_PSS0 | DSI_PSR_PSS1 | DSI_PSR_PSSC)) != (DSI_PSR_PSS0 | \
           DSI_PSR_PSS1 | DSI_PSR_PSSC))
    {
      if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
      {
        return HAL_ERROR;
      }
    }
  }

  hdsi->global_state = HAL_DSI_STATE_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief  Get the DSI configuration and fill parameters in the @ref hal_dsi_config_t.
  * @param  hdsi           pointer to @ref hal_dsi_handle_t structure.
  * @param  p_config          pointer to @ref hal_dsi_config_t structure.
  */
void HAL_DSI_GetConfig(const hal_dsi_handle_t *hdsi, hal_dsi_config_t *p_config)
{
  uint32_t pll_factor;
  uint32_t pll_config;
  uint32_t phy_control;
  uint32_t phy_freq;
  uint32_t lanes_number;
  uint32_t tx_clkdiv;

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_INIT | (uint32_t)HAL_DSI_STATE_CONFIGURED);

  pll_factor = READ_BIT(DSI_GET_INSTANCE(hdsi)->WRPCR,
                        (DSI_WRPCR_PLL_NDIV | DSI_WRPCR_PLL_IDF | DSI_WRPCR_PLL_ODF | DSI_WRPCR_BC));

  pll_config = READ_BIT(DSI_GET_INSTANCE(hdsi)->WPTR, (DSI_WPTR_LPF | DSI_WPTR_CP));

  phy_control = READ_BIT(DSI_GET_INSTANCE(hdsi)->PCTLR,
                         (DSI_PCTLR_CKE | DSI_PCTLR_DEN));

  phy_freq = READ_BIT(DSI_GET_INSTANCE(hdsi)->DPCBCR, DSI_DPCBCR);

  lanes_number = READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL);

  tx_clkdiv = READ_BIT(DSI_GET_INSTANCE(hdsi)->CCR, DSI_CCR_TXECKDIV);

  p_config->pll_cfg.pll_ndiv = (uint32_t)((pll_factor & DSI_WRPCR_PLL_NDIV) >> DSI_WRPCR_PLL_NDIV_Pos);

  p_config->pll_cfg.pll_idf  = (uint32_t)((pll_factor & DSI_WRPCR_PLL_IDF) >> DSI_WRPCR_PLL_IDF_Pos);

  p_config->pll_cfg.pll_odf  = (uint32_t)((pll_factor & DSI_WRPCR_PLL_ODF) >> DSI_WRPCR_PLL_ODF_Pos);

  p_config->pll_cfg.vco_range  = (hal_dsi_vco_freq_range_t)((pll_factor & DSI_WRPCR_BC) >> DSI_WRPCR_BC_Pos);

  p_config->nbr_of_lanes = (hal_dsi_data_lane_t)(uint32_t)(lanes_number & DSI_PCONFR_NL);

  p_config->tx_escape_clk_div = (uint32_t)(tx_clkdiv & DSI_CCR_TXECKDIV);

  p_config->pll_cfg.pll_loop_filter = (hal_dsi_pll_loop_filter_t)((pll_config & DSI_WPTR_LPF) >> DSI_WPTR_LPF_Pos);

  p_config->pll_cfg.pll_charge_pump = (hal_dsi_pll_charge_pump_t)((pll_config & DSI_WPTR_CP) >> DSI_WPTR_CP_Pos);

  p_config->pll_cfg.pll_charge_pump = (hal_dsi_pll_charge_pump_t)((pll_config & DSI_WPTR_CP) >> DSI_WPTR_CP_Pos);

  p_config->phy_cfg.phy_frequency_range = (hal_dsi_vco_freq_range_t)((phy_freq & DSI_DPCBCR) >> DSI_DPCBCR_Pos);
}

/**
  * @}
 */

/** @addtogroup DSI_Exported_Functions_Group3
  * @{
This subsection provides a set the DSI callbacks registration APIs:
- HAL_DSI_IRQHandler() to handle the interrupt request.
- HAL_DSI_TearingEffectCallback() to register callback function for interrupts when error occurs.
- HAL_DSI_EndOfRefreshCallback()  to register callback function for interrupts when error occurs.
- HAL_DSI_RegisterErrorCallback() to register callback function for interrupts when error occurs.
  */

/**
  * @brief  Handles DSI interrupt request.
  * @param  hdsi pointer to @ref hal_dsi_handle_t structure.
  */
void HAL_DSI_IRQHandler(hal_dsi_handle_t *hdsi)
{
  uint32_t ErrorStatus0;
  uint32_t ErrorStatus1;
  uint32_t flag_status;
  uint32_t it_sources;

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_ACTIVE);

  flag_status = READ_REG(DSI_GET_INSTANCE(hdsi)->WISR);
  it_sources  = READ_REG(DSI_GET_INSTANCE(hdsi)->WIER);

  ErrorStatus0 = READ_REG(DSI_GET_INSTANCE(hdsi)->ISR[0U]);
  ErrorStatus0 &= READ_REG(DSI_GET_INSTANCE(hdsi)->IER[0U]);
  ErrorStatus1 = READ_REG(DSI_GET_INSTANCE(hdsi)->ISR[1U]);
  ErrorStatus1 &= READ_REG(DSI_GET_INSTANCE(hdsi)->IER[1U]);

  /* Tearing Effect Interrupt management ***************************************/
  if ((flag_status & it_sources & HAL_DSI_FLAG_ER) != 0U)
  {
    HAL_DSI_DisableIT(hdsi, HAL_DSI_IT_ER);

    HAL_DSI_ClearFlag(hdsi, HAL_DSI_FLAG_ER);

#if defined (USE_HAL_DSI_REGISTER_CALLBACKS) && (USE_HAL_DSI_REGISTER_CALLBACKS == 1)
    hdsi->p_tearing_effect_cb(hdsi);
#else
    HAL_DSI_TearingEffectCallback(hdsi);
#endif /* USE_HAL_DSI_REGISTER_CALLBACKS */
  }

  /* End of Refresh Interrupt management ***************************************/
  if ((flag_status & it_sources & HAL_DSI_FLAG_TE) != 0U)
  {
    HAL_DSI_DisableIT(hdsi, HAL_DSI_IT_TE);

    HAL_DSI_ClearFlag(hdsi, HAL_DSI_FLAG_TE);

#if defined (USE_HAL_DSI_REGISTER_CALLBACKS) && (USE_HAL_DSI_REGISTER_CALLBACKS == 1)
    hdsi->p_refresh_cb(hdsi);
#else
    HAL_DSI_EndOfRefreshCallback(hdsi);
#endif /* USE_HAL_DSI_REGISTER_CALLBACKS */
  }

  /* Error Interrupts management ***********************************************/
#if defined(USE_HAL_DSI_GET_LAST_ERRORS) && (USE_HAL_DSI_GET_LAST_ERRORS == 1U)
  if ((ErrorStatus0 & HAL_DSI_FLAG_ACK) != 0U)
  {
    hdsi->last_error_codes |= HAL_DSI_ERROR_ACK;
  }

  if ((ErrorStatus0 & HAL_DSI_FLAG_PHY) != 0U)
  {
    hdsi->last_error_codes |= HAL_DSI_ERROR_PHY;
  }

  if ((ErrorStatus1 & HAL_DSI_FLAG_TX) != 0U)
  {
    hdsi->last_error_codes |= HAL_DSI_ERROR_TX;
  }

  if ((ErrorStatus1 & HAL_DSI_FLAG_RX) != 0U)
  {
    hdsi->last_error_codes |= HAL_DSI_ERROR_RX;
  }

  if ((ErrorStatus1 & HAL_DSI_FLAG_ECC) != 0U)
  {
    hdsi->last_error_codes |= HAL_DSI_ERROR_ECC;
  }

  if ((ErrorStatus1 & HAL_DSI_FLAG_CRC) != 0U)
  {
    hdsi->last_error_codes |= HAL_DSI_ERROR_CRC;
  }

  if ((ErrorStatus1 & HAL_DSI_FLAG_PSE) != 0U)
  {
    hdsi->last_error_codes |= HAL_DSI_ERROR_PSE;
  }

  if ((ErrorStatus1 & HAL_DSI_FLAG_EOT) != 0U)
  {
    hdsi->last_error_codes |= HAL_DSI_ERROR_EOT;
  }

  if ((ErrorStatus1 & HAL_DSI_FLAG_OVF) != 0U)
  {
    hdsi->last_error_codes |= HAL_DSI_ERROR_OVF;
  }

  if ((ErrorStatus1 & HAL_DSI_FLAG_GEN) != 0U)
  {
    hdsi->last_error_codes |= HAL_DSI_ERROR_GEN;
  }

  if ((ErrorStatus1 & HAL_DSI_FLAG_PBU) != 0U)
  {
    hdsi->last_error_codes |= HAL_DSI_ERROR_PBU;
  }

  if (hdsi->last_error_codes != HAL_DSI_ERROR_NONE)
  {

#if defined (USE_HAL_DSI_REGISTER_CALLBACKS) && (USE_HAL_DSI_REGISTER_CALLBACKS == 1)

    hdsi->p_error_cb(hdsi);
#else
    HAL_DSI_ErrorCallback(hdsi);
#endif /* USE_HAL_DSI_REGISTER_CALLBACKS */
  }
#endif /* USE_HAL_DSI_REGISTER_CALLBACKS */
}

/**
  * @brief  Return the DSI acknowledge error source.
  * @param  hdsi pointer to a hal_dsi_handle_t structure that contains
  *         the configuration information for the DSI.
  * @retval uint32_t Error source
  */
uint32_t HAL_DSI_GetACKErrorSource(hal_dsi_handle_t *hdsi)
{
  uint32_t ack_error_source;

  ASSERT_DBG_PARAM(hdsi != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_ACTIVE);

  ack_error_source = READ_REG(DSI_GET_INSTANCE(hdsi)->ISR[0U]) & HAL_DSI_ERROR_ACK;

  return ack_error_source;
}

/**
  * @brief  Tearing Effect DSI callback.
  * @param  hdsi  pointer to a DSI_HandleTypeDef structure that contains
  *               the configuration information for the DSI.
  */
__WEAK void HAL_DSI_TearingEffectCallback(hal_dsi_handle_t *hdsi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdsi);
  /** WARNING: This function must not be modified, when the callback is needed,
    *          the HAL_DSI_TearingEffectCallback could be implemented in the user file.
    */
}

/**
  * @brief  End of Refresh DSI callback.
  * @param  hdsi  pointer to a DSI_HandleTypeDef structure that contains
  *               the configuration information for the DSI.
  */
__WEAK void HAL_DSI_EndOfRefreshCallback(hal_dsi_handle_t *hdsi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdsi);
  /** WARNING: This function must not be modified, when the callback is needed,
     *          the HAL_DSI_EndOfRefreshCallback could be implemented in the user file.
     */
}

/**
  * @brief  Operation Error DSI callback.
  * @param  hdsi  pointer to a DSI_HandleTypeDef structure that contains
  *               the configuration information for the DSI.
  */
__WEAK void HAL_DSI_ErrorCallback(hal_dsi_handle_t *hdsi)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdsi);
  /** WARNING: This function must not be modified, when the callback is needed,
     *          the HAL_DSI_ErrorCallback could be implemented in the user file.
     */
}

/**
  * @}
  */

/** @addtogroup DSI_Peripheral_control_functions_Group4
  * @{
A set of functions allowing to configure the DSIperipheral:

  - HAL_DSI_SetGenericVCIDRX()
  - HAL_DSI_GetGenericVCIDRX()
  - HAL_DSI_SetGenericVCIDTX()
  - HAL_DSI_GetGenericVCIDTX()
  - HAL_DSI_SetGenericVCID()
  - HAL_DSI_GetGenericVCID()

- Video mode :
  - HAL_DSI_SetConfigVideoMode()
  - HAL_DSI_GetConfigVideoMode()

- Adapted command mode :
  - HAL_DSI_SetConfigAdaptedCommandMode()
  - HAL_DSI_GetConfigAdaptedCommandMode()

- APB Command mode :
  - HAL_DSI_SetConfigLPCommand()
  - HAL_DSI_GetConfigLPCommand()

  - HAL_DSI_SetFlowControl()
  - HAL_DSI_GetFlowControl()
  - HAL_DSI_SetConfigPhyTimer()
  - HAL_DSI_GetConfigPhyTimer()
  - HAL_DSI_EnablePatternGenerator()
  - HAL_DSI_DisablePatternGenerator()
  - HAL_DSI_IsEnabledPatternGenerator()
  - HAL_DSI_Start()
  - HAL_DSI_Stop()
  - HAL_DSI_Refresh()
  - HAL_DSI_EnableAutomaticClockLane()
  - HAL_DSI_DisableAutomaticClockLane()
  - HAL_DSI_IsEnabledAutomaticClockLane()
  - HAL_DSI_EnableFrameBusAcknowledge()
  - HAL_DSI_DisableFrameBusAcknowledge()
  - HAL_DSI_IsEnableFrameBusAcknowledge()
  - HAL_DSI_SetConfigTearingEffect()
  - HAL_DSI_GetConfigTearingEffect()
  - HAL_DSI_EnableAutomaticRefresh()
  - HAL_DSI_DisableAutomaticRefresh()
  - HAL_DSI_IsEnableAutomaticRefresh()
  - HAL_DSI_EnableAcknowledge()
  - HAL_DSI_DisableAcknowledge()
  - HAL_DSI_IsEnableAcknowledge()
  - HAL_DSI_SetColorMode()
  - HAL_DSI_GetColorMode()
  - HAL_DSI_Shutdown()
  - HAL_DSI_ShortWrite()
  - HAL_DSI_LongWrite()
  - HAL_DSI_Read()
  - HAL_DSI_GetClockFreq()
  - HAL_DSI_GetACKErrorSource()
  - HAL_DSI_EnterULPMData()
  - HAL_DSI_ExitULPMData()
  - HAL_DSI_EnterULPM()
  - HAL_DSI_ExitULPM()
  - HAL_DSI_EnableSwapLanePins()
  - HAL_DSI_DisableSwapLanePins()
  - HAL_DSI_IsEnableSwapLanePins()
  - HAL_DSI_EnableForceTXStopMode()
  - HAL_DSI_DisableForceTXStopMode()
  - HAL_DSI_IsEnabledForceTXStopMode()
  - HAL_DSI_GetVideoTimingFromLTDC()
  - HAL_DSI_GetVideoTimingFromDSI()

  */

/**
  * @brief  Configure the generic interface read-back Virtual Channel ID.
  * @param  hdsi  pointer to a DSI_HandleTypeDef structure that contains
  *               the configuration information for the DSI.
  * @param  virtual_channel_id_rx  Virtual channel ID
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_SetGenericVCIDRX(hal_dsi_handle_t *hdsi, hal_dsi_virtual_channel_t virtual_channel_id_rx)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_VIRTUAL_CHANNEL_ID(virtual_channel_id_rx));

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_CONFIGURED);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->GVCIDR, (uint32_t)virtual_channel_id_rx << DSI_GVCIDR_VCIDRX_Pos);

  return HAL_OK;
}

/**
  * @brief  Get generic VCIDRX configuration.
  * @param  hdsi     Pointer to a hal_dsi_handle_t structure
  * @retval HAL_DSI_VIRTUAL_CHANNEL_ID_0  virtual channel id 0
  * @retval HAL_DSI_VIRTUAL_CHANNEL_ID_1  virtual channel id 1
  * @retval HAL_DSI_VIRTUAL_CHANNEL_ID_2  virtual channel id 2
  * @retval HAL_DSI_VIRTUAL_CHANNEL_ID_3  virtual channel id 3
  */
hal_dsi_virtual_channel_t HAL_DSI_GetGenericVCIDRX(const hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_CONFIGURED);

  return ((hal_dsi_virtual_channel_t)(uint32_t)READ_BIT(DSI_GET_INSTANCE(hdsi)->GVCIDR, DSI_GVCIDR_VCIDRX));
}

/**
  * @brief  Configure the Virtual channel ID for transmission.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  virtual_channel_id_tx  Virtual channel ID
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_SetGenericVCIDTX(hal_dsi_handle_t *hdsi, hal_dsi_virtual_channel_t virtual_channel_id_tx)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_VIRTUAL_CHANNEL_ID(virtual_channel_id_tx));

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t) HAL_DSI_STATE_CONFIGURED);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->GVCIDR, (uint32_t)virtual_channel_id_tx << DSI_GVCIDR_VCIDTX_Pos);

  return HAL_OK;
}

/**
  * @brief  Configure the generic interface read-back Virtual Channel ID.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @retval HAL_DSI_VIRTUAL_CHANNEL_ID_0  virtual channel id 0
  * @retval HAL_DSI_VIRTUAL_CHANNEL_ID_1  virtual channel id 1
  * @retval HAL_DSI_VIRTUAL_CHANNEL_ID_2  virtual channel id 2
  * @retval HAL_DSI_VIRTUAL_CHANNEL_ID_3  virtual channel id 3
  */
hal_dsi_virtual_channel_t HAL_DSI_GetGenericVCIDTX(const hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_CONFIGURED);

  return ((hal_dsi_virtual_channel_t)(uint32_t)READ_BIT(DSI_GET_INSTANCE(hdsi)->GVCIDR, DSI_GVCIDR_VCIDTX));
}

/**
  * @brief  Configure the generic interface read-back Virtual Channel ID.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  virtual_channel_id  Virtual channel ID
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_SetGenericVCID(hal_dsi_handle_t *hdsi, hal_dsi_virtual_channel_t virtual_channel_id)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_VIRTUAL_CHANNEL_ID(virtual_channel_id));

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_CONFIGURED);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->GVCIDR, (((uint32_t)virtual_channel_id << DSI_GVCIDR_VCIDRX_Pos) | \
                                             ((uint32_t)virtual_channel_id << DSI_GVCIDR_VCIDTX_Pos)));

  return HAL_OK;
}

/**
  * @brief  Configure the generic interface read-back Virtual Channel ID.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @retval HAL_DSI_VIRTUAL_CHANNEL_ID_0  virtual channel id 0
  * @retval HAL_DSI_VIRTUAL_CHANNEL_ID_1  virtual channel id 1
  * @retval HAL_DSI_VIRTUAL_CHANNEL_ID_2  virtual channel id 2
  * @retval HAL_DSI_VIRTUAL_CHANNEL_ID_3  virtual channel id 3
  */
hal_dsi_virtual_channel_t HAL_DSI_GetGenericVCID(const hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_CONFIGURED);

  return ((hal_dsi_virtual_channel_t)(uint32_t)READ_BIT(DSI_GET_INSTANCE(hdsi)->GVCIDR,
                                                        (DSI_GVCIDR_VCIDRX | DSI_GVCIDR_VCIDTX)));
}

/**
  * @brief  Select video mode and configure the corresponding parameters.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  p_videoconfig pointer to a hal_dsi_video_config_t structure that contains
  *                the DSI video mode configuration parameters
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_SetConfigVideoMode(hal_dsi_handle_t *hdsi, const hal_dsi_video_config_t *p_videoconfig)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(p_videoconfig != NULL);
  ASSERT_DBG_PARAM(IS_DSI_COLOR_CODING(p_videoconfig->ColorCoding));
  ASSERT_DBG_PARAM(IS_DSI_LP_COMMAND(p_videoconfig->lp_command));
  ASSERT_DBG_PARAM(IS_DSI_LP_HFP(p_videoconfig->lp_horizontal_front_porch));
  ASSERT_DBG_PARAM(IS_DSI_LP_HBP(p_videoconfig->lp_horizontal_back_porch));
  ASSERT_DBG_PARAM(IS_DSI_LP_VACTIVE(p_videoconfig->lp_vertical_active));
  ASSERT_DBG_PARAM(IS_DSI_LP_VFP(p_videoconfig->lp_vertical_front_porch));
  ASSERT_DBG_PARAM(IS_DSI_LP_VBP(p_videoconfig->lp_vertical_back_porch));
  ASSERT_DBG_PARAM(IS_DSI_LP_VSYNC(p_videoconfig->lp_vertical_sync_active));

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_CONFIGURED | (uint32_t)HAL_DSI_STATE_IDLE);

  CLEAR_REG(DSI_GET_INSTANCE(hdsi)->MCR);

  CLEAR_REG(DSI_GET_INSTANCE(hdsi)->WCFGR);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->VMCR, DSI_VMCR_VMT, p_videoconfig->mode);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->VPCR, p_videoconfig->packet_size);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->VCCR, p_videoconfig->nbr_of_chunks);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->VNPCR, p_videoconfig->null_packet_size);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->LVCIDR, p_videoconfig->VirtualChannel);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->LCOLCR, (uint32_t)p_videoconfig->ColorCoding);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->WCFGR, DSI_WCFGR_COLMUX,
             ((uint32_t)p_videoconfig->ColorCoding << DSI_WCFGR_COLMUX_Pos));

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->VHSACR, (uint32_t)p_videoconfig->h_sync_active);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->VHBPCR, (uint32_t)p_videoconfig->h_back_porch);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->VLCR, (uint32_t)p_videoconfig->h_line);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->VVSACR, (uint32_t)p_videoconfig->v_sync_active);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->VVBPCR, (uint32_t)p_videoconfig->v_back_porch);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->VVFPCR, (uint32_t)p_videoconfig->v_front_porch);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->VVACR, (uint32_t)p_videoconfig->v_active);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->LPMCR,
             (DSI_LPMCR_LPSIZE | DSI_LPMCR_VLPSIZE),
             ((p_videoconfig->lp_largest_packet_size << DSI_LPMCR_LPSIZE_Pos
               | p_videoconfig->lp_vact_largest_packet_size << DSI_LPMCR_VLPSIZE_Pos)));

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->VMCR,
             (DSI_VMCR_LPHFPE | DSI_VMCR_LPHBPE | DSI_VMCR_LPVAE | DSI_VMCR_LPVFPE |
              DSI_VMCR_LPVBPE | DSI_VMCR_LPVSAE | DSI_VMCR_LPCE),
             ((uint32_t)p_videoconfig->lp_horizontal_front_porch
              | (uint32_t) p_videoconfig->lp_horizontal_back_porch
              | (uint32_t) p_videoconfig->lp_command
              | (uint32_t) p_videoconfig->lp_vertical_front_porch
              | (uint32_t) p_videoconfig->lp_vertical_back_porch
              | (uint32_t)p_videoconfig->lp_vertical_sync_active));

  hdsi->global_state = HAL_DSI_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Get video mode configuration.
  * @param  hdsi     Pointer to a hal_dsi_handle_t structure
  * @param  p_videoconfig  Pointer to a hal_dsi_video_config_t structure
  */
void HAL_DSI_GetConfigVideoMode(const hal_dsi_handle_t *hdsi, hal_dsi_video_config_t *p_videoconfig)
{

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(p_videoconfig != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  uint32_t mode_video;
  uint32_t packet;
  uint32_t number_chunks;
  uint32_t null_packet;
  uint32_t virtual_channel;
  uint32_t dsi_polarity;
  uint32_t color_coding_host;
  uint32_t color_coding_wrapper;
  uint32_t hs_active;
  uint32_t h_backporch;
  uint32_t h_line;
  uint32_t vs_active;
  uint32_t v_backporch;
  uint32_t v_frontproch;
  uint32_t v_active;
  uint32_t largest_packet_size;
  uint32_t lp_transition;

  mode_video = READ_BIT(DSI_GET_INSTANCE(hdsi)->VMCR, DSI_VMCR_VMT);

  packet = READ_BIT(DSI_GET_INSTANCE(hdsi)->VPCR, DSI_VPCR_VPSIZE);

  number_chunks = READ_BIT(DSI_GET_INSTANCE(hdsi)->VCCR, DSI_VCCR_NUMC);

  null_packet = READ_BIT(DSI_GET_INSTANCE(hdsi)->VNPCR, DSI_VNPCR_NPSIZE);

  virtual_channel = READ_BIT(DSI_GET_INSTANCE(hdsi)->LVCIDR, DSI_LVCIDR_VCID);

  dsi_polarity = READ_BIT(DSI_GET_INSTANCE(hdsi)->LPCR, (DSI_LPCR_DEP | DSI_LPCR_VSP | DSI_LPCR_HSP));

  color_coding_host = READ_BIT(DSI_GET_INSTANCE(hdsi)->LCOLCR, DSI_LCOLCR_COLC);

  color_coding_wrapper = READ_BIT(DSI_GET_INSTANCE(hdsi)->WCFGR, DSI_WCFGR_COLMUX);

  hs_active = READ_BIT(DSI_GET_INSTANCE(hdsi)->VHSACR, DSI_VHSACR_HSA);

  h_backporch = READ_BIT(DSI_GET_INSTANCE(hdsi)->VHBPCR, DSI_VHBPCR_HBP);

  h_line = READ_BIT(DSI_GET_INSTANCE(hdsi)->VLCR, DSI_VLCR_HLINE);

  vs_active = READ_BIT(DSI_GET_INSTANCE(hdsi)->VVSACR, DSI_VVSACR_VSA);

  v_backporch = READ_BIT(DSI_GET_INSTANCE(hdsi)->VVBPCR, DSI_VVBPCR_VBP);

  v_frontproch = READ_BIT(DSI_GET_INSTANCE(hdsi)->VVFPCR, DSI_VVFPCR_VFP);

  v_active = READ_BIT(DSI_GET_INSTANCE(hdsi)->VVACR, DSI_VVACR_VA);

  largest_packet_size = READ_BIT(DSI_GET_INSTANCE(hdsi)->LPMCR, (DSI_LPMCR_LPSIZE | DSI_LPMCR_VLPSIZE));

  lp_transition = READ_BIT(DSI_GET_INSTANCE(hdsi)->VMCR, (DSI_VMCR_LPHFPE | DSI_VMCR_LPHBPE | DSI_VMCR_LPVAE
                                                          | DSI_VMCR_LPVFPE | DSI_VMCR_LPVBPE
                                                          | DSI_VMCR_LPVSAE | DSI_VMCR_LPCE));

  p_videoconfig->mode  = (hal_dsi_video_mode_t)((mode_video & DSI_VMCR_VMT));

  p_videoconfig->packet_size = (uint32_t)((packet & DSI_VPCR_VPSIZE));

  p_videoconfig->nbr_of_chunks = (uint32_t)((number_chunks & DSI_VCCR_NUMC));

  p_videoconfig->null_packet_size = (uint32_t)((null_packet & DSI_VNPCR_NPSIZE));

  p_videoconfig->VirtualChannel = (uint32_t)((virtual_channel & DSI_LVCIDR_VCID));

  p_videoconfig->ColorCoding = (hal_dsi_color_t)((color_coding_host & DSI_LCOLCR_COLC));

  p_videoconfig->ColorCoding = (hal_dsi_color_t)((color_coding_wrapper & DSI_WCFGR_COLMUX) >> DSI_WCFGR_COLMUX_Pos);

  p_videoconfig->h_sync_active = (uint32_t)((hs_active & DSI_VHSACR_HSA));

  p_videoconfig->h_back_porch = (uint32_t)((h_backporch & DSI_VHBPCR_HBP));

  p_videoconfig->h_line = (uint32_t)((h_line & DSI_VLCR_HLINE));

  p_videoconfig->v_sync_active = (uint32_t)((vs_active & DSI_VVSACR_VSA));

  p_videoconfig->v_back_porch = (uint32_t)((v_backporch & DSI_VVBPCR_VBP));

  p_videoconfig->v_front_porch = (uint32_t)((v_frontproch & DSI_VVFPCR_VFP));

  p_videoconfig->v_active = (uint32_t)((v_active & DSI_VVACR_VA));

  p_videoconfig->lp_largest_packet_size = (uint32_t)((largest_packet_size & DSI_LPMCR_LPSIZE) >> DSI_LPMCR_LPSIZE_Pos);

  p_videoconfig->lp_vact_largest_packet_size = (uint32_t)((largest_packet_size & DSI_LPMCR_VLPSIZE)
                                                          >> DSI_LPMCR_VLPSIZE_Pos);

  p_videoconfig->lp_command = (hal_dsi_lp_command_state_t)((lp_transition & DSI_VMCR_LPCE));

  p_videoconfig->lp_horizontal_front_porch = (hal_dsi_lp_hfp_state_t)((lp_transition & DSI_VMCR_LPHFPE));

  p_videoconfig->lp_horizontal_back_porch = (hal_dsi_lp_hbp_state_t)((lp_transition & DSI_VMCR_LPHBPE));

  p_videoconfig->lp_vertical_active = (hal_dsi_lp_vact_state_t)((lp_transition & DSI_VMCR_LPVAE));

  p_videoconfig->lp_vertical_front_porch = (hal_dsi_lp_vfp_state_t)((lp_transition & DSI_VMCR_LPVFPE));

  p_videoconfig->lp_vertical_back_porch = (hal_dsi_lp_vbp_state_t)((lp_transition & DSI_VMCR_LPVBPE));

  p_videoconfig->lp_vertical_sync_active = (hal_dsi_lp_vsync_state_t)((lp_transition & DSI_VMCR_LPVSAE));

}

/**
  * @brief  Select adapted command mode and configure the corresponding parameters.
  * @param  hdsi  pointer to a DSI_HandleTypeDef structure that contains
  *               the configuration information for the DSI.
  * @param  p_cmdconfig  pointer to a DSI_CmdCfgTypeDef structure that contains
  *                 the DSI command mode configuration parameters
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_SetConfigAdaptedCommandMode(hal_dsi_handle_t *hdsi, const hal_dsi_cmd_config_t *p_cmdconfig)
{

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(p_cmdconfig != NULL);
  ASSERT_DBG_PARAM(IS_DSI_COLOR_CODING(p_cmdconfig->color_coding));

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_CONFIGURED | (uint32_t)HAL_DSI_STATE_IDLE);

  SET_BIT(DSI_GET_INSTANCE(hdsi)->MCR, DSI_MCR_CMDM);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->LVCIDR, p_cmdconfig->VirtualChannel);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->LCOLCR, DSI_LCOLCR_COLC, (uint32_t) p_cmdconfig->color_coding);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->LCCR, p_cmdconfig->command_size);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->WCFGR, (DSI_WCFGR_COLMUX | DSI_WCFGR_DSIM), DSI_WCFGR_DSIM |
             ((uint32_t)p_cmdconfig->color_coding) << DSI_WCFGR_COLMUX_Pos);

  hdsi->global_state = HAL_DSI_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Get Adapted command mode configuration.
  * @param  hdsi     Pointer to a hal_dsi_handle_t structure
  * @param  p_cmdconfig  Pointer to a hal_dsi_cmd_config_t structure
  */
void HAL_DSI_GetConfigAdaptedCommandMode(const hal_dsi_handle_t *hdsi, hal_dsi_cmd_config_t *p_cmdconfig)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(p_cmdconfig != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  uint32_t virtual_channel;
  uint32_t dsi_polarity;
  uint32_t cmd_size;
  uint32_t vsync_polarity;
  uint32_t color_coding_host;
  uint32_t color_coding_wrapper;

  virtual_channel = READ_BIT(DSI_GET_INSTANCE(hdsi)->LVCIDR, DSI_LVCIDR_VCID);

  dsi_polarity = READ_BIT(DSI_GET_INSTANCE(hdsi)->LPCR, (DSI_LPCR_DEP | DSI_LPCR_VSP | DSI_LPCR_HSP));

  cmd_size = READ_BIT(DSI_GET_INSTANCE(hdsi)->LCOLCR, DSI_LCOLCR_COLC);

  vsync_polarity = READ_BIT(DSI_GET_INSTANCE(hdsi)->WCFGR, DSI_WCFGR_VSPOL);

  color_coding_host = READ_BIT(DSI_GET_INSTANCE(hdsi)->LCOLCR, DSI_LCOLCR_COLC);

  color_coding_wrapper = READ_BIT(DSI_GET_INSTANCE(hdsi)->WCFGR, DSI_WCFGR_COLMUX);

  p_cmdconfig->VirtualChannel  = (uint32_t)((virtual_channel & DSI_LVCIDR_VCID));

  p_cmdconfig->command_size  = (uint32_t)((cmd_size & DSI_LCCR_CMDSIZE));

  p_cmdconfig->color_coding  = (hal_dsi_color_t)((color_coding_host & DSI_WCFGR_VSPOL));

  p_cmdconfig->color_coding  = (hal_dsi_color_t)((color_coding_wrapper & DSI_WCFGR_COLMUX) >> DSI_WCFGR_COLMUX_Pos);
}

/**
  * @brief  Configure command transmission mode: High-speed or Low-power
  *         and enable/disable acknowledge request after packet transmission.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  p_lpcmd  pointer to a hal_dsi_lp_cmd_config_t structure that contains
  *                the DSI command transmission mode configuration parameters
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_SetConfigLPCommand(hal_dsi_handle_t *hdsi, const hal_dsi_lp_cmd_config_t *p_lpcmd)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(p_lpcmd != NULL);
  ASSERT_DBG_PARAM(IS_DSI_LP_GSW0P(p_lpcmd->lp_short_write_gen_no_param));
  ASSERT_DBG_PARAM(IS_DSI_LP_GSW1P(p_lpcmd->lp_short_write_gen_1_param));
  ASSERT_DBG_PARAM(IS_DSI_LP_GSW2P(p_lpcmd->lp_short_write_gen_2_param));
  ASSERT_DBG_PARAM(IS_DSI_LP_GSR0P(p_lpcmd->lp_short_read_gen_no_param));
  ASSERT_DBG_PARAM(IS_DSI_LP_GSR1P(p_lpcmd->lp_short_read_gen_1_param));
  ASSERT_DBG_PARAM(IS_DSI_LP_GSR2P(p_lpcmd->lp_short_read_gen_2_param));
  ASSERT_DBG_PARAM(IS_DSI_LP_GLW(p_lpcmd->lp_long_write_gen_tx));
  ASSERT_DBG_PARAM(IS_DSI_LP_DSW0P(p_lpcmd->lp_short_write_dcs_tx_no_param));
  ASSERT_DBG_PARAM(IS_DSI_LP_DSW1P(p_lpcmd->lp_short_write_dcs_tx_1_param));
  ASSERT_DBG_PARAM(IS_DSI_LP_DSR0P(p_lpcmd->lp_short_read_dcs_tx_no_param));
  ASSERT_DBG_PARAM(IS_DSI_LP_DLW(p_lpcmd->lp_long_write_dcs_tx));
  ASSERT_DBG_PARAM(IS_DSI_LP_MRDP(p_lpcmd->lp_max_read_pkt));

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  /* Select High-speed or Low-power for command transmission */

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->CMCR, (DSI_CMCR_GSW0TX | \
                                            DSI_CMCR_GSW1TX | \
                                            DSI_CMCR_GSW2TX | \
                                            DSI_CMCR_GSR0TX | \
                                            DSI_CMCR_GSR1TX | \
                                            DSI_CMCR_GSR2TX | \
                                            DSI_CMCR_GLWTX  | \
                                            DSI_CMCR_DSW0TX | \
                                            DSI_CMCR_DSW1TX | \
                                            DSI_CMCR_DSR0TX | \
                                            DSI_CMCR_DLWTX  | \
                                            DSI_CMCR_MRDPS) \
             , ((uint32_t)p_lpcmd->lp_short_write_gen_no_param
                | (uint32_t)p_lpcmd->lp_short_write_gen_1_param
                | (uint32_t)p_lpcmd->lp_short_write_gen_2_param
                | (uint32_t)p_lpcmd->lp_short_read_gen_no_param
                | (uint32_t)p_lpcmd->lp_short_read_gen_1_param
                | (uint32_t)p_lpcmd->lp_short_read_gen_2_param
                | (uint32_t)p_lpcmd->lp_long_write_gen_tx
                | (uint32_t)p_lpcmd->lp_short_write_dcs_tx_no_param
                | (uint32_t)p_lpcmd->lp_short_write_dcs_tx_1_param
                | (uint32_t)p_lpcmd->lp_short_read_dcs_tx_no_param
                | (uint32_t)p_lpcmd->lp_long_write_dcs_tx
                | (uint32_t)p_lpcmd->lp_max_read_pkt));

  return HAL_OK;
}

/**
  * @brief  Get command transmission mode: High-speed or Low-power
  * @param  hdsi     Pointer to a hal_dsi_handle_t structure
  * @param  p_lpcmd  Pointer to a hal_dsi_lp_cmd_config_t structure
  */
void HAL_DSI_GetConfigLPCommand(const hal_dsi_handle_t *hdsi, hal_dsi_lp_cmd_config_t *p_lpcmd)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(p_lpcmd != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  uint32_t lp_generic;

  lp_generic = READ_BIT(DSI_GET_INSTANCE(hdsi)->CMCR, (DSI_CMCR_GSW0TX | DSI_CMCR_GSW1TX | DSI_CMCR_GSW2TX  \
                                                       | DSI_CMCR_GSR0TX | DSI_CMCR_GSR1TX | DSI_CMCR_GSR2TX  \
                                                       | DSI_CMCR_GLWTX  |  DSI_CMCR_DSW0TX | DSI_CMCR_DSW1TX \
                                                       | DSI_CMCR_DSR0TX | DSI_CMCR_DLWTX  |  DSI_CMCR_MRDPS));

  p_lpcmd->lp_short_write_gen_no_param = (hal_dsi_lp_short_write_gen_no_param_state_t)((lp_generic & DSI_CMCR_GSW0TX));

  p_lpcmd->lp_short_write_gen_1_param = (hal_dsi_lp_short_write_gen_1_param_state_t)((lp_generic & DSI_CMCR_GSW1TX));

  p_lpcmd->lp_short_write_gen_2_param = (hal_dsi_lp_short_write_gen_2_param_state_t)((lp_generic & DSI_CMCR_GSW2TX));

  p_lpcmd->lp_short_read_gen_no_param = (hal_dsi_lp_short_read_gen_no_param_state_t)((lp_generic & DSI_CMCR_GSR0TX));

  p_lpcmd->lp_short_read_gen_1_param = (hal_dsi_lp_short_read_gen_1_param_state_t)((lp_generic & DSI_CMCR_GSR1TX));

  p_lpcmd->lp_short_read_gen_2_param = (hal_dsi_lp_short_read_gen_2_param_state_t)((lp_generic & DSI_CMCR_GSR2TX));

  p_lpcmd->lp_long_write_gen_tx = (hal_dsi_long_write_gen_tx_state_t)((lp_generic & DSI_CMCR_GLWTX));

  p_lpcmd->lp_short_write_dcs_tx_no_param = (hal_dsi_short_write_dcs_tx_no_param_state_t)
                                            ((lp_generic & DSI_CMCR_DSW0TX));

  p_lpcmd->lp_short_write_dcs_tx_1_param = (hal_dsi_short_write_dcs_tx_1_param_state_t)((lp_generic
                                           & DSI_CMCR_DSW1TX));

  p_lpcmd->lp_short_read_dcs_tx_no_param = (hal_dsi_short_read_dcs_tx_no_param_state_t)((lp_generic
                                           & DSI_CMCR_DSR0TX));

  p_lpcmd->lp_long_write_dcs_tx = (hal_dsi_long_write_dcs_tx_state_t)((lp_generic & DSI_CMCR_DLWTX));

  p_lpcmd->lp_max_read_pkt = (hal_dsi_lp_max_read_pkt_state_t)((lp_generic & DSI_CMCR_MRDPS));

}

/**
  * @brief  Configure the Tearing effect  parameters.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  tearing_effect_config_t  Pointer to a hal_dsi_tearing_effect_config_t structure
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_SetConfigTearingEffect(hal_dsi_handle_t *hdsi,
                                            const hal_dsi_tearing_effect_config_t *tearing_effect_config_t)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(tearing_effect_config_t != NULL)
  ASSERT_DBG_PARAM(IS_DSI_TE_POLARITY(tearing_effect_config_t->polarity));
  ASSERT_DBG_PARAM(IS_DSI_TE_SOURCE(tearing_effect_config_t->src));
  ASSERT_DBG_PARAM(IS_DSI_TE_ACK_REQUEST(tearing_effect_config_t->acknowledge));

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->WCFGR, (DSI_WCFGR_TESRC | DSI_WCFGR_TEPOL),
             ((uint32_t)tearing_effect_config_t-> src
              | (uint32_t)tearing_effect_config_t-> polarity));

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->CMCR, DSI_CMCR_TEARE, ((uint32_t)tearing_effect_config_t->acknowledge));

  return HAL_OK;
}

/**
  * @brief  Get tearing effect configuration.
  * @param  hdsi     Pointer to a hal_dsi_handle_t structure
  * @param  tearing_effect_config_t  Pointer to a hal_dsi_tearing_effect_config_t structure
  */
void HAL_DSI_GetConfigTearingEffect(const hal_dsi_handle_t *hdsi,
                                    hal_dsi_tearing_effect_config_t *tearing_effect_config_t)
{
  uint32_t te_config;
  uint32_t te_acknowledge;

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(tearing_effect_config_t != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  te_config = READ_BIT(DSI_GET_INSTANCE(hdsi)->WCFGR, (DSI_WCFGR_TESRC | DSI_WCFGR_TEPOL));
  te_acknowledge = READ_BIT(DSI_GET_INSTANCE(hdsi)->WCFGR, DSI_CMCR_TEARE);

  tearing_effect_config_t->src = (hal_dsi_te_source_t)((te_config & DSI_WCFGR_TESRC));
  tearing_effect_config_t->polarity = (hal_dsi_te_polarity_t)((te_config & DSI_WCFGR_TEPOL));
  tearing_effect_config_t->acknowledge = (hal_dsi_te_acknowledge_state_t)((te_acknowledge & DSI_CMCR_TEARE));
}

/**
  * @brief  Enable the Automatic refresh.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_OK Automatic refresh enabled.
  */
hal_status_t HAL_DSI_EnableAutomaticRefresh(hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  SET_BIT(DSI_GET_INSTANCE(hdsi)->WCFGR, DSI_WCFGR_AR);

  return HAL_OK;
}

/**
  * @brief  Disable the Automatic refresh.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_OK Automatic refresh disabled.
  */
hal_status_t HAL_DSI_DisableAutomaticRefresh(hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  CLEAR_BIT(DSI_GET_INSTANCE(hdsi)->WCFGR, DSI_WCFGR_AR);

  return HAL_OK;
}

/**
  * @brief  Check if the  is Automatic refresh enabled or disabled.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_DSI_AR_DISABLE  Automatic clock lane control disabled
  * @retval HAL_DSI_AR_ENABLE  Automatic clock lane control enabled
  */
hal_dsi_auto_refresh_status_t HAL_DSI_IsEnabledAutomaticRefresh(const hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  return ((hal_dsi_auto_refresh_status_t)(uint32_t)READ_BIT(DSI_GET_INSTANCE(hdsi)->WCFGR, DSI_WCFGR_AR));
}

/**
  * @brief  Enable the Acknowledge.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_OK Automatic clock lane control enabled.
  */
hal_status_t HAL_DSI_EnableAcknowledge(hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  SET_BIT(DSI_GET_INSTANCE(hdsi)->CMCR, DSI_CMCR_ARE);

  return HAL_OK;
}

/**
  * @brief  Disable the acknowledge.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_OK Automatic clock lane control enabled.
  */
hal_status_t HAL_DSI_DisableAcknowledge(hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  CLEAR_BIT(DSI_GET_INSTANCE(hdsi)->CMCR, DSI_CMCR_ARE);

  return HAL_OK;
}

/**
  * @brief  Check if the  is acknowledge enabled or disabled.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_OK Automatic clock lane control enabled.
  */
hal_dsi_acknowledge_status_t HAL_DSI_IsEnabledAcknowledge(const hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t) HAL_DSI_STATE_IDLE);

  return ((hal_dsi_acknowledge_status_t)(uint32_t)READ_BIT(DSI_GET_INSTANCE(hdsi)->CLCR, DSI_CMCR_ARE));

}

/**
  * @brief  Enable the Pattern generator.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_OK Automatic clock lane control enabled.
  */
hal_status_t HAL_DSI_EnablePatternGenerator(hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  SET_BIT(DSI_GET_INSTANCE(hdsi)->VMCR, DSI_VMCR_PGE);

  return HAL_OK;
}

/**
  * @brief  Disable the Pattern generator.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_OK Automatic clock lane control enabled.
  */
hal_status_t HAL_DSI_DisablePatternGenerator(hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t) HAL_DSI_STATE_IDLE);

  CLEAR_BIT(DSI_GET_INSTANCE(hdsi)->VMCR, DSI_VMCR_PGE);

  return HAL_OK;
}

/**
  * @brief  Check if the Pattern Generator is enabled or disabled.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_OK Automatic clock lane control enabled.
  */
hal_dsi_pattern_generator_status_t HAL_DSI_IsEnabledPatternGenerator(const hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  return ((hal_dsi_pattern_generator_status_t)(uint32_t)READ_BIT(DSI_GET_INSTANCE(hdsi)->VMCR, DSI_VMCR_PGE));

}

/**
  * @brief  Enable the Automatic clock lane control.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_OK Automatic clock lane control enabled.
  */
hal_status_t HAL_DSI_EnableAutomaticClockLane(hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t) HAL_DSI_STATE_IDLE);

  SET_BIT(DSI_GET_INSTANCE(hdsi)->CLCR, DSI_CLCR_ACR);

  return HAL_OK;
}

/**
  * @brief  Disable the Automatic clock lane control.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_OK Automatic clock lane control disabled.
  */
hal_status_t HAL_DSI_DisableAutomaticClockLane(hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  CLEAR_REG(DSI_GET_INSTANCE(hdsi)->CLCR);
  return HAL_OK;
}

/**
  * @brief  Check if the  is Automatic clock lane control enabled or disabled.
  * @param  hdsi Pointer to a hal_dsi_handle_t structure
  * @retval HAL_DSI_AUTO_CLK_LANE_CTRL_DISABLE  Automatic clock lane control disabled
  * @retval HAL_DSI_AUTO_CLK_LANE_CTRL_ENABLE  Automatic clock lane control enabled
  */
hal_dsi_auto_clk_lane_ctrl_status_t HAL_DSI_IsEnabledAutomaticClockLane(const hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t) HAL_DSI_STATE_IDLE);

  return ((hal_dsi_auto_clk_lane_ctrl_status_t)(uint32_t)READ_BIT(DSI_GET_INSTANCE(hdsi)->CLCR,
                                                                  (DSI_CLCR_DPCC | DSI_CLCR_ACR)));
}

/**
  * @brief  Configure the flow control parameters.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  flow_control  flow control feature(s) to be enabled.
  *                      This parameter can be any combination of @arg DSI_FlowControl.
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_SetFlowControl(hal_dsi_handle_t *hdsi, const uint32_t flow_control)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_FLOW_CONTROL(flow_control));

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->PCR, flow_control);

  return HAL_OK;
}

/**
  * @brief  Get flow control configuration.
  * @param  hdsi     Pointer to a hal_dsi_handle_t structure
  * @param  flow_control  flow control feature(s) to be enabled.
  *                      This parameter can be any combination of @arg DSI_FlowControl.
  */
void HAL_DSI_GetFlowControl(const hal_dsi_handle_t *hdsi, uint32_t flow_control)
{
  uint32_t flow_ctrl;

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(flow_control != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  flow_ctrl = READ_BIT(DSI_GET_INSTANCE(hdsi)->PCR, HAL_DSI_FLOW_CONTROL_ALL);
}

/**
  * @brief Enable the Frame Bus Acknowledge.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_OK Automatic clock lane control enabled.
  */
hal_status_t HAL_DSI_EnableFrameBusAcknowledge(hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  SET_BIT(DSI_GET_INSTANCE(hdsi)-> VMCR, DSI_VMCR_FBTAAE);

  return HAL_OK;
}

/**
  * @brief Disable the Frame Bus Acknowledge.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_OK Automatic clock lane control disabled.
  */
hal_status_t HAL_DSI_DisableFrameBusAcknowledge(hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  CLEAR_BIT(DSI_GET_INSTANCE(hdsi)->VMCR, DSI_VMCR_FBTAAE);

  return HAL_OK;
}

/**
  * @brief  Check if the  is Frame Bus Acknowledge enabled or disabled.
  * @param  hdsi Pointer to a hal_dsi_handle_t structure
  * @retval HAL_DSI_FBTAA_DISABLE  Automatic clock lane control disabled
  * @retval HAL_DSI_FBTAA_ENABLE  Automatic clock lane control enabled
  */
hal_dsi_fbtaa_status_t HAL_DSI_IsEnabledFrameBusAcknowledge(const hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  return ((hal_dsi_fbtaa_status_t)(uint32_t)READ_BIT(DSI_GET_INSTANCE(hdsi)->VMCR, DSI_VMCR_FBTAAE));
}

/**
  * @brief  Configure the DSI PHY timer parameters.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  p_phytimers  hal_dsi_phy_tim_config_t structure that contains
  *                    the DSI PHY timing parameters
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_SetConfigPhyTimer(hal_dsi_handle_t *hdsi, hal_dsi_phy_tim_config_t *p_phytimers)
{
  uint32_t maxTime;
  uint32_t powerOffset;

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(p_phytimers != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  powerOffset = READ_REG(DSI_GET_INSTANCE(hdsi)->DPDL0LPXOCR);

  /* Insert LPX Offset into the timings */
  p_phytimers->clk_lane_hs2_lp_time = p_phytimers->clk_lane_hs2_lp_time + powerOffset ;
  p_phytimers->clk_lane_lp2_hs_time = p_phytimers->clk_lane_lp2_hs_time + (3U * powerOffset);
  p_phytimers->data_lane_lp_2hs_time  = p_phytimers->data_lane_lp_2hs_time + (2U * powerOffset);

  maxTime = (p_phytimers->clk_lane_lp2_hs_time > p_phytimers->clk_lane_hs2_lp_time) ?
            p_phytimers->clk_lane_lp2_hs_time :
            p_phytimers->clk_lane_hs2_lp_time;

  /* Clock lane timer configuration */

  /* In Automatic Clock Lane control mode, the DSI Host can turn off the clock lane between two
     High-Speed transmission.
     To do so, the DSI Host calculates the time required for the clock lane to change from HighSpeed
     to Low-Power and from Low-Power to High-Speed.
     This timings are configured by the HS2LP_TIME and LP2HS_TIME in the DSI Host Clock Lane Timer Configuration
     Register (DSI_CLTCR).
     But the DSI Host is not calculating LP2HS_TIME + HS2LP_TIME but 2 x HS2LP_TIME.

     Workaround : Configure HS2LP_TIME and LP2HS_TIME with the same value being the max of HS2LP_TIME or LP2HS_TIME.
    */
  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->CLTCR, (DSI_CLTCR_LP2HS_TIME | DSI_CLTCR_HS2LP_TIME),
             (maxTime | ((maxTime) << DSI_CLTCR_HS2LP_TIME_Pos)));

  /* Data lane timer configuration */
  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->DLTCR, (DSI_DLTCR_LP2HS_TIME | DSI_DLTCR_HS2LP_TIME),
             (p_phytimers->data_lane_lp_2hs_time
              | ((p_phytimers->data_lanehs2_lp_time) << DSI_DLTCR_HS2LP_TIME_Pos)));

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->DLTRCR, p_phytimers->data_lane_max_read_time);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_SW_TIME,
             (p_phytimers->stop_wait_time) << DSI_PCONFR_SW_TIME_Pos);

  return HAL_OK;
}

/**
  * @brief  Get the PHY Timer configuration.
  * @param  hdsi  pointer to a DSI_HandleTypeDef structure that contains
  *               the configuration information for the DSI.
  * @param  p_phytimers  pointer to a hal_dsi_phy_tim_config_t structure that will
  *                      contain the retrieved PHY timer configuration.
  */
void HAL_DSI_GetConfigPhyTimer(const hal_dsi_handle_t *hdsi, hal_dsi_phy_tim_config_t *p_phytimers)
{
  uint32_t powerOffset;

  ASSERT_DBG_PARAM(hdsi != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  powerOffset = DSI_GET_INSTANCE(hdsi)->DPDL0LPXOCR;

  p_phytimers->clk_lane_hs2_lp_time = READ_REG(DSI_GET_INSTANCE(hdsi)->CLTCR) & DSI_CLTCR_HS2LP_TIME_Msk;

  p_phytimers->clk_lane_lp2_hs_time = (READ_REG(DSI_GET_INSTANCE(hdsi)->CLTCR) & DSI_CLTCR_LP2HS_TIME_Msk)
                                      >> DSI_CLTCR_LP2HS_TIME_Pos;

  p_phytimers->clk_lane_hs2_lp_time = p_phytimers->clk_lane_hs2_lp_time - powerOffset;

  p_phytimers->clk_lane_lp2_hs_time = p_phytimers->clk_lane_lp2_hs_time - (3U * powerOffset);

  p_phytimers->data_lane_lp_2hs_time = READ_REG(DSI_GET_INSTANCE(hdsi)->DLTCR) & DSI_DLTCR_LP2HS_TIME_Msk;

  p_phytimers->data_lanehs2_lp_time = (READ_REG(DSI_GET_INSTANCE(hdsi)->DLTCR) & DSI_DLTCR_HS2LP_TIME_Msk)
                                      >> DSI_DLTCR_HS2LP_TIME_Pos;

  p_phytimers->data_lane_lp_2hs_time = p_phytimers->data_lane_lp_2hs_time - (2U * powerOffset);

  p_phytimers->data_lane_max_read_time = READ_REG(DSI_GET_INSTANCE(hdsi)->DLTRCR);

  p_phytimers->stop_wait_time = (READ_REG(DSI_GET_INSTANCE(hdsi)->PCONFR) & DSI_PCONFR_SW_TIME_Msk)
                                >> DSI_PCONFR_SW_TIME_Pos;
}

/**
  * @brief  Configure the DSI HOST timeout parameters.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  p_host_timeout  hal_dsi_timeout_config_t structure that contains
  *                       the DSI host timeout parameters
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_SetConfigHostTimeouts(hal_dsi_handle_t *hdsi, const hal_dsi_timeout_config_t *p_host_timeout)
{

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(p_host_timeout != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->CCR, DSI_CCR_TOCKDIV,
             ((uint32_t)p_host_timeout->time_out_clk_div) << DSI_CCR_TOCKDIV_Pos);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->TCCR[0U], (DSI_TCCR0_HSTX_TOCNT | DSI_TCCR0_LPRX_TOCNT),
             (p_host_timeout->high_speed_tr_timeout) << DSI_TCCR0_HSTX_TOCNT0_Pos
             | p_host_timeout->low_power_reception_timeout);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->TCCR[1U], p_host_timeout->high_Speed_read_timeout);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->TCCR[2U], p_host_timeout->low_power_read_timeout);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->TCCR[3U], (DSI_TCCR3_HSWR_TOCNT | DSI_TCCR3_PM),
             p_host_timeout->high_speed_write_timeout
             | (uint32_t)p_host_timeout-> high_Speed_write_Presp_mode);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->TCCR[4U], p_host_timeout->low_power_write_timeout);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->TCCR[5U], p_host_timeout->bta_timeout);

  return HAL_OK;
}

/**
  * @brief  Configure the DSI HOST timeout parameters.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  p_host_timeout  hal_dsi_timeout_config_t structure that contains
  *                       the DSI host timeout parameters
  */
void HAL_DSI_GetConfigHostTimeouts(const hal_dsi_handle_t *hdsi, hal_dsi_timeout_config_t *p_host_timeout)
{
  uint32_t timeout_clock_div;
  uint32_t hs_tr_timeout;
  uint32_t lp_rp_timeout;
  uint32_t hs_read_timeout;
  uint32_t lp_read_timeout;
  uint32_t hs_write_timeout;
  uint32_t hs_write_presp_mode;
  uint32_t lp_write_timeout;
  uint32_t bta_time_out;

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  timeout_clock_div = READ_BIT(DSI_GET_INSTANCE(hdsi)->CCR, DSI_CCR_TOCKDIV);

  hs_tr_timeout     = READ_BIT(DSI_GET_INSTANCE(hdsi)->TCCR[0U], (DSI_TCCR0_HSTX_TOCNT | DSI_TCCR0_LPRX_TOCNT));

  hs_read_timeout   = READ_BIT(DSI_GET_INSTANCE(hdsi)->TCCR[1U], DSI_TCCR1_HSRD_TOCNT);

  lp_read_timeout   = READ_BIT(DSI_GET_INSTANCE(hdsi)->TCCR[2U], DSI_TCCR2_LPRD_TOCNT);

  hs_write_timeout  = READ_BIT(DSI_GET_INSTANCE(hdsi)->TCCR[3U], (DSI_TCCR3_HSWR_TOCNT | DSI_TCCR3_PM));

  lp_write_timeout  = READ_BIT(DSI_GET_INSTANCE(hdsi)->TCCR[4U], DSI_TCCR4_LPWR_TOCNT);

  bta_time_out      = READ_BIT(DSI_GET_INSTANCE(hdsi)->TCCR[5U], DSI_TCCR5_BTA_TOCNT);

  p_host_timeout->time_out_clk_div            = (uint32_t)((timeout_clock_div & DSI_CCR_TOCKDIV)
                                                           >> DSI_CCR_TOCKDIV_Pos);

  p_host_timeout->high_speed_tr_timeout       = (uint32_t)((hs_tr_timeout & DSI_TCCR0_HSTX_TOCNT)
                                                           >> DSI_TCCR0_HSTX_TOCNT0_Pos);

  p_host_timeout->low_power_reception_timeout = (uint32_t)((hs_tr_timeout & DSI_TCCR0_LPRX_TOCNT));

  p_host_timeout->high_Speed_read_timeout     = (uint32_t)((hs_read_timeout & DSI_TCCR1_HSRD_TOCNT));

  p_host_timeout->low_power_read_timeout      = (uint32_t)((lp_read_timeout & DSI_TCCR2_LPRD_TOCNT));

  p_host_timeout->high_speed_write_timeout    = (uint32_t)((hs_write_timeout & DSI_TCCR3_HSWR_TOCNT));

  p_host_timeout->high_Speed_write_Presp_mode = (hal_dsi_hs_presp_mode_t)((hs_write_timeout & DSI_TCCR3_PM));

  p_host_timeout->low_power_write_timeout     = (uint32_t)((lp_write_timeout & DSI_TCCR4_LPWR_TOCNT));

  p_host_timeout->bta_timeout                 = (uint32_t)((bta_time_out & DSI_TCCR5_BTA_TOCNT));
}

/**
  * @brief  Start the DSI module.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  interrupts  Specify the LTDC interrupt sources to be enabled while starting.
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_Start(hal_dsi_handle_t *hdsi, uint32_t interrupts)
{
  DSI_TypeDef *p_dsi;

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_INTERRUPT(interrupts));

  HAL_CHECK_UPDATE_STATE(hdsi, global_state, HAL_DSI_STATE_CONFIGURED, HAL_DSI_STATE_ACTIVE);

  p_dsi = DSI_GET_INSTANCE(hdsi);

  SET_BIT(p_dsi->CR, DSI_CR_EN);

  SET_BIT(p_dsi->WCR, DSI_WCR_DSIEN);

  hdsi->global_state = HAL_DSI_STATE_ACTIVE;

  return HAL_OK;
}

/**
  * @brief  Stop the DSI module.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_Stop(hal_dsi_handle_t *hdsi)
{
  DSI_TypeDef *p_dsi;

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE | (uint32_t)HAL_DSI_STATE_ACTIVE);

  p_dsi = DSI_GET_INSTANCE(hdsi);

  CLEAR_BIT(p_dsi->CR, DSI_CR_EN);

  CLEAR_BIT(p_dsi->WCR, DSI_WCR_DSIEN);

  hdsi->global_state = HAL_DSI_STATE_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief  Refresh the display in command mode.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_Refresh(hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_ACTIVE);

  SET_BIT(DSI_GET_INSTANCE(hdsi)->WCR, DSI_WCR_LTDCEN);

  hdsi->global_state = HAL_DSI_STATE_ACTIVE;

  return HAL_OK;
}

/**
  * @brief  Controls the display color mode in Video mode.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  color_mode  Color mode (full or 8-colors).
  *                    This parameter can be any value of @arg DSI color mode
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_SetColorMode(hal_dsi_handle_t *hdsi, hal_dsi_color_mode_t color_mode)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_COLOR_MODE(color_mode));

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->WCR, DSI_WCR_COLM, (uint32_t)color_mode);

  return HAL_OK;
}

/**
  * @brief  Get color mode.
  * @param  hdsi                   Pointer to a hal_dcmi_handle_t structure
  * @retval HAL_DSI_COLOR_MODE_FULL   Full color mode
  * @retval HAL_DSI_COLOR_MODE_EIGHT  Eight color mode
  */
hal_dsi_color_mode_t HAL_DSI_GetColorMode(const hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  return ((hal_dsi_color_mode_t)(uint32_t)READ_BIT(DSI_GET_INSTANCE(hdsi)->WCR, DSI_WCR_COLM));
}

/**
  * @brief  Enable LoosleyPacked.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_OK Automatic clock lane control enabled.
  */
hal_status_t HAL_DSI_EnableLooselyPacked(hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t) HAL_DSI_STATE_IDLE);

  SET_BIT(DSI_GET_INSTANCE(hdsi)->LCOLCR, DSI_LCOLCR_LPE);

  return HAL_OK;
}

/**
  * @brief  Disable LoosleyPacked.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @retval HAL_OK Automatic clock lane control disabled.
  */
hal_status_t HAL_DSI_DisableLooselyPacked(hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  CLEAR_BIT(DSI_GET_INSTANCE(hdsi)->LCOLCR, DSI_LCOLCR_LPE);

  return HAL_OK;
}

/**
  * @brief  Check if the  LoosleyPacked is  enabled or disabled.
  * @param  hdsi                          Pointer to a hal_dsi_handle_t structure
  * @retval HAL_DSI_AUTO_CLK_LANE_CTRL_DISABLE  Automatic clock lane control disabled
  * @retval HAL_DSI_AUTO_CLK_LANE_CTRL_ENABLE  Automatic clock lane control enabled
  */
hal_dsi_loosely_packed_status_t HAL_DSI_IsEnabledLoosleyPacked(const hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  return ((hal_dsi_loosely_packed_status_t)(uint32_t)READ_BIT(DSI_GET_INSTANCE(hdsi)->LCOLCR, DSI_LCOLCR_LPE));
}

/**
  * @brief  Control the display display in Video mode.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  display  Shut-down (Display-ON or Display-OFF).
  *                     This parameter can be any value of @arg DSI shut down definition
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_Shutdown(hal_dsi_handle_t *hdsi, hal_dsi_display_t display)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_SHUT_DOWN(display));

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->WCR, DSI_WCR_SHTDN, (uint32_t)display);

  return HAL_OK;
}

/**
  * @brief  write short DCS or short generic command.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  channel_id  Virtual channel ID.
  * @param  mode  DSI short packet data type.
  *               This parameter can be any value of @arg DSI SHORT WRITE PKT Data Type.
  * @param  first_param  DSC command or first generic parameter.
  *                 This parameter can be any value of @arg DSI DCS Command or a
  *                 generic command code.
  * @param  second_param  DSC parameter or second generic parameter.
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_ShortWrite(hal_dsi_handle_t *hdsi,
                                hal_dsi_virtual_channel_t channel_id,
                                hal_dsi_short_write_packet_t mode,
                                uint32_t first_param,
                                uint32_t second_param)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_SHORT_WRITE_PACKET_TYPE(mode));
  ASSERT_DBG_PARAM(IS_DSI_VIRTUAL_CHANNEL_ID(channel_id));

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_ACTIVE);

  status = DSI_ShortWrite(hdsi, channel_id, mode, first_param, second_param);

  return status;
}

/**
  * @brief  write long DCS or long generic command.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  channel_id  Virtual channel ID.
  * @param  mode  DSI long packet data type.
  *               This parameter can be any value of @arg DSI LONG WRITE PKT Data Type.
  * @param  nbparams  Number of parameters.
  * @param  first_param  DSC command or first generic parameter.
  *                 This parameter can be any value of @arg DSI DCS Command or a
  *                 generic command code
  * @param  p_param_table  Pointer to parameter values table.
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_LongWrite(hal_dsi_handle_t *hdsi,
                               hal_dsi_virtual_channel_t channel_id,
                               hal_dsi_long_write_packet_t mode,
                               uint32_t nbparams,
                               uint32_t first_param,
                               uint8_t *p_param_table)
{
  uint32_t uicounter;
  uint32_t nb_bytes;
  uint32_t tickstart;
  uint32_t fifoword;
  uint8_t *pparams = p_param_table;

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_LONG_WRITE_PACKET_TYPE(mode));
  ASSERT_DBG_PARAM(IS_DSI_VIRTUAL_CHANNEL_ID(channel_id));

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_ACTIVE);

  tickstart = HAL_GetTick();

  /* Wait for Command FIFO Empty */
  while (READ_BIT(DSI_GET_INSTANCE(hdsi)->GPSR, DSI_GPSR_CMDFE) == 0U)
  {

    if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }
  }

  /* Set the DCS code on payload byte 1, and the other parameters on the write FIFO command*/
  fifoword = first_param;
  nb_bytes = (nbparams < 3U) ? nbparams : 3U;

  for (uint32_t count = 0U; count < nb_bytes; count++)
  {
    fifoword |= (((uint32_t)(*(pparams + count))) << (8U + (8U * count)));
  }
  WRITE_REG(DSI_GET_INSTANCE(hdsi)->GPDR, fifoword);
  uicounter = nbparams - nb_bytes;
  pparams += nb_bytes;
  /* Set the Next parameters on the write FIFO command*/
  while (uicounter != 0U)
  {
    nb_bytes = (uicounter < 4U) ? uicounter : 4U;
    fifoword = 0U;
    for (uint32_t count = 0U; count < nb_bytes; count++)
    {
      fifoword |= (((uint32_t)(*(pparams + count))) << (8U * count));
    }
    WRITE_REG(DSI_GET_INSTANCE(hdsi)->GPDR, fifoword);
    uicounter -= nb_bytes;
    pparams += nb_bytes;
  }

  /* Configure the packet to send a long DCS command */
  DSI_ConfigPacketHeader(DSI_GET_INSTANCE(hdsi),
                         channel_id,
                         mode,
                         ((nbparams + 1U) & 0x00FFU),
                         (((nbparams + 1U) & 0xFF00U) >> 8U));

  return HAL_OK;
}

/**
  * @brief  Read command (DCS or generic).
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  channel_nbr  Virtual channel ID
  * @param  p_array pointer to a buffer to store the payload of a read back operation.
  * @param  size  Data size to be read (in byte).
  * @param  mode  DSI read packet data type.
  *               This parameter can be any value of @arg DSI SHORT READ PKT Data Type.
  * @param  cmdDCS  DCS get/read command.
  * @param  p_parameters_table  Pointer to parameter values table.
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_Read(hal_dsi_handle_t *hdsi,
                          hal_dsi_virtual_channel_t channel_nbr,
                          uint8_t *p_array,
                          uint32_t size,
                          hal_dsi_short_read_packet_t mode,
                          uint32_t cmdDCS,
                          uint8_t *p_parameters_table)
{
  uint32_t tickstart;
  uint8_t *pdata = p_array;
  uint32_t datasize = size;
  uint32_t fifoword;
  uint32_t nbbytes;

  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_READ_SHORT_PACKET_TYPE(mode));
  ASSERT_DBG_PARAM(IS_DSI_VIRTUAL_CHANNEL_ID(channel_nbr));

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_ACTIVE);

  if (datasize > 2U)
  {
    /* set max return packet size */
    if (DSI_ShortWrite(hdsi, channel_nbr, HAL_DSI_MAX_RETURN_PKT_SIZE, ((datasize) & 0xFFU),
                       (((datasize) >> 8U) & 0xFFU)) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  if (mode == HAL_DSI_SHORT_READ_PKT_DCS)
  {
    DSI_ConfigPacketHeader(DSI_GET_INSTANCE(hdsi), channel_nbr, mode, cmdDCS, 0U);
  }
  else if (mode == HAL_DSI_SHORT_READ_PKT_GEN_NO_PARAM)
  {
    DSI_ConfigPacketHeader(DSI_GET_INSTANCE(hdsi), channel_nbr, mode, 0U, 0U);
  }
  else if (mode == HAL_DSI_SHORT_READ_PKT_GEN_1_PARAM)
  {
    DSI_ConfigPacketHeader(DSI_GET_INSTANCE(hdsi), channel_nbr, mode, p_parameters_table[0U], 0U);
  }
  else if (mode == HAL_DSI_SHORT_READ_PKT_GEN_2_PARAM)
  {
    DSI_ConfigPacketHeader(DSI_GET_INSTANCE(hdsi), channel_nbr, mode, p_parameters_table[0U], p_parameters_table[1U]);
  }
  else
  {

    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();

  while (((int32_t)(datasize)) > 0)
  {
    if (READ_BIT(DSI_GET_INSTANCE(hdsi)->GPSR, DSI_GPSR_PRDFE) == 0U)
    {
      fifoword = DSI_GET_INSTANCE(hdsi)->GPDR;
      nbbytes = (datasize < 4U) ? datasize : 4U;

      for (uint32_t count = 0U; count < nbbytes; count++)
      {
        *pdata = (uint8_t)(fifoword >> (8U * count));
        pdata++;
        datasize--;
      }
    }

    if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }

    /* Software workaround to avoid HAL_TIMEOUT when a DSI read command is   */
    /* issued to the panel and the read data is not captured by the DSI Host */
    /* which returns Packet Size Error.                                      */
    /* Need to ensure that the Read command has finished before checking PSE */
    if (READ_BIT(DSI_GET_INSTANCE(hdsi)->GPSR, DSI_GPSR_RCB) == 0U)
    {
      if (READ_BIT(DSI_GET_INSTANCE(hdsi)->ISR[1U], DSI_ISR1_PSE == DSI_ISR1_PSE))
      {
        return HAL_ERROR;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Enter the ULPM (Ultra Low Power Mode) with the D-PHY PLL running
  *         (only data lanes are in ULPM).
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_EnterULPMData(hal_dsi_handle_t *hdsi)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hdsi != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_ACTIVE);

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCTLR, (DSI_PCTLR_CKE | DSI_PCTLR_DEN)) != (DSI_PCTLR_CKE | DSI_PCTLR_DEN))
  {
    return HAL_ERROR;
  }

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->WRPCR, DSI_WRPCR_PLLEN) != DSI_WRPCR_PLLEN)
  {
    return HAL_ERROR;
  }
  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->BCFGR, DSI_BCFGR_PWRUP) != DSI_BCFGR_PWRUP)
  {
    return HAL_ERROR;
  }

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PUCR, (DSI_PUCR_UEDL | DSI_PUCR_URDL)) != 0)
  {
    return HAL_ERROR;
  }

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)-> PTTCR, DSI_PTTCR_TX_TRIG) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_Delay(1);

  tickstart = HAL_GetTick();

  while ((HAL_DSI_GetFlag(hdsi, HAL_DSI_FLAG_PLLLS) == 0U))
  {
    if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }
  }

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) != HAL_DSI_DATA_1_LANE)
  {
    if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, DSI_PSR_UAN0) != DSI_PSR_UAN0)
    {
      return HAL_ERROR;
    }
  }
  else if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) != HAL_DSI_DATA_2_LANES)
  {
    if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_UAN0 | DSI_PSR_UAN1)) != (DSI_PSR_UAN0 | DSI_PSR_UAN1))
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  SET_BIT(DSI_GET_INSTANCE(hdsi)->PUCR, DSI_PUCR_URDL);

  tickstart = HAL_GetTick();

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_1_LANE)
  {
    while (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, DSI_PSR_UAN0) != 0U)
    {
      if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
      {
        return HAL_ERROR;
      }
    }
  }
  else if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_2_LANES)
  {
    while (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_UAN0 | DSI_PSR_UAN1)) != 0U)
    {
      if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
      {
        return HAL_ERROR;
      }
    }
  }
  else
  {
    return HAL_ERROR;
  }
  return HAL_OK;
}

/**
  * @brief  Exit the ULPM (Ultra Low Power Mode) with the D-PHY PLL running
  *         (only data lanes are in ULPM).
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_ExitULPMData(hal_dsi_handle_t *hdsi)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hdsi != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_ACTIVE);

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_1_LANE)
  {
    if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, DSI_PSR_UAN0) != 0U)
    {
      return HAL_ERROR;
    }
  }
  else if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_2_LANES)
  {
    if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_UAN0  | DSI_PSR_UAN1)) != 0U)
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  SET_BIT(DSI_GET_INSTANCE(hdsi)-> WRPCR, DSI_WRPCR_PLLEN);

  HAL_Delay(1);

  tickstart = HAL_GetTick();

  while (HAL_DSI_GetFlag(hdsi, HAL_DSI_FLAG_PLLLS) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }
  }

  SET_BIT(DSI_GET_INSTANCE(hdsi)->PUCR, DSI_PUCR_UEDL);

  tickstart = HAL_GetTick();

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_1_LANE)
  {
    while (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, DSI_PSR_UAN0) == DSI_PSR_UAN0)
    {

      if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
      {
        return HAL_ERROR;
      }
    }
  }
  else if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_2_LANES)
  {
    while (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_UAN0 | DSI_PSR_UAN1)) != (DSI_PSR_UAN0 | DSI_PSR_UAN1))
    {
      if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
      {
        return HAL_ERROR;
      }
    }
  }
  else
  {
    return HAL_ERROR;
  }

  HAL_Delay(1U);

  CLEAR_REG(DSI_GET_INSTANCE(hdsi)->PUCR);

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->WRPCR, DSI_WRPCR_PLLEN) == DSI_WRPCR_PLLEN)
  {
    return HAL_ERROR;
  }

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_1_LANE)
  {
    if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, DSI_PSR_UAN0) != DSI_PSR_UAN0)
    {
      return HAL_ERROR;
    }
  }
  else if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_2_LANES)
  {
    if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_UAN0  |  DSI_PSR_UAN1)) != (DSI_PSR_UAN0 | DSI_PSR_UAN1))
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  HAL_Delay(1);

  tickstart = HAL_GetTick();

  while (HAL_DSI_GetFlag(hdsi, HAL_DSI_FLAG_PLLLS) == 0U)
  {

    if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Enter the ULPM (Ultra Low Power Mode) with the D-PHY PLL turned off
  *         (both data and clock lanes are in ULPM).
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_EnterULPM(hal_dsi_handle_t *hdsi)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hdsi != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_ACTIVE);

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCTLR, (DSI_PCTLR_CKE | DSI_PCTLR_DEN)) != (DSI_PCTLR_CKE | DSI_PCTLR_DEN))
  {
    return HAL_ERROR;
  }

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->WRPCR, DSI_WRPCR_PLLEN) != DSI_WRPCR_PLLEN)
  {
    return HAL_ERROR;
  }

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->BCFGR, DSI_BCFGR_PWRUP) != DSI_BCFGR_PWRUP)
  {
    return HAL_ERROR;
  }

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PUCR, (DSI_PUCR_UEDL | DSI_PUCR_URDL | DSI_PUCR_UECL | DSI_PUCR_URCL)) != 0U)
  {
    return HAL_ERROR;
  }

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PTTCR, DSI_PTTCR_TX_TRIG) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_Delay(1);

  tickstart = HAL_GetTick();

  while ((HAL_DSI_GetFlag(hdsi, HAL_DSI_FLAG_PLLLS) == 0U))
  {

    if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }
  }

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_1_LANE)
  {
    if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_UAN0 | DSI_PSR_PSS0)) != (DSI_PSR_UAN0 | DSI_PSR_PSS0))
    {
      return HAL_ERROR;
    }
  }
  else if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_2_LANES)
  {
    if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_UAN0 | DSI_PSR_PSS0 | DSI_PSR_PSS1 |   \
                                               DSI_PSR_UAN1)) != (DSI_PSR_UAN0 | DSI_PSR_PSS0 \
                                                                  | DSI_PSR_PSS1 | DSI_PSR_UAN1))
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  CLEAR_BIT(DSI_GET_INSTANCE(hdsi)->CLCR, DSI_CLCR_DPCC);

  HAL_RCC_DSI_SetKernelClkSource(HAL_RCC_DSI_CLK_SRC_PLL3);

  WRITE_REG(DSI_GET_INSTANCE(hdsi)->PUCR, (DSI_PUCR_URCL | DSI_PUCR_URDL));

  tickstart = HAL_GetTick();

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_1_LANE)
  {
    while (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_UAN0 | DSI_PSR_UANC)) != 0U)
    {
      if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
      {
        return HAL_ERROR;
      }
    }
  }
  else if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_2_LANES)
  {
    while (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_UAN0 | DSI_PSR_UAN1 | DSI_PSR_UANC)) != 0U)
    {
      if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
      {
        return HAL_ERROR;
      }
    }
  }
  else
  {
    return HAL_ERROR;
  }

  CLEAR_BIT(DSI_GET_INSTANCE(hdsi)->WRPCR, DSI_WRPCR_PLLEN);

  return HAL_OK;
}

/**
  * @brief  Exit the ULPM (Ultra Low Power Mode) with the D-PHY PLL turned off
  *         (both data and clock lanes are in ULPM).
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_ExitULPM(hal_dsi_handle_t *hdsi)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hdsi != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_ACTIVE);

  /* Verify that all active lanes are in ULPM */
  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_1_LANE)
  {
    if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_RUE0 | DSI_PSR_UAN0 | DSI_PSR_PSS0 | \
                                               DSI_PSR_UANC | DSI_PSR_PSSC | DSI_PSR_PD)) != 0U)
    {
      return HAL_ERROR;
    }
  }
  else if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_2_LANES)
  {
    if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_RUE0 | DSI_PSR_UAN0 | DSI_PSR_PSS0 | DSI_PSR_UAN1 | \
                                               DSI_PSR_PSS1 | DSI_PSR_UANC | DSI_PSR_PSSC | DSI_PSR_PD)) != 0U)
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  SET_BIT(DSI_GET_INSTANCE(hdsi)->WRPCR, DSI_WRPCR_PLLEN);

  HAL_Delay(1);

  tickstart = HAL_GetTick();

  while (HAL_DSI_GetFlag(hdsi, HAL_DSI_FLAG_PLLLS) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
    {

      return HAL_ERROR;
    }
  }

  SET_BIT(DSI_GET_INSTANCE(hdsi)->PUCR, (DSI_PUCR_UECL | DSI_PUCR_UEDL));

  tickstart = HAL_GetTick();

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_1_LANE)
  {
    while (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_UAN0 | DSI_PSR_UANC)) == (DSI_PSR_UAN0 | DSI_PSR_UANC))
    {

      if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
      {

        return HAL_ERROR;
      }
    }
  }
  else if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_2_LANES)
  {
    while (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_UAN0 | DSI_PSR_UAN1 | DSI_PSR_UANC)) == (DSI_PSR_UAN0
           | DSI_PSR_UAN1
           | DSI_PSR_UANC))
    {

      if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
      {

        return HAL_ERROR;
      }
    }
  }
  else
  {

    return HAL_ERROR;
  }

  HAL_Delay(1U);

  CLEAR_REG(DSI_GET_INSTANCE(hdsi)->PUCR);

  HAL_RCC_DSI_SetKernelClkSource(HAL_RCC_DSI_CLK_SRC_DSIPHY);

  SET_BIT(DSI_GET_INSTANCE(hdsi)->CLCR, DSI_CLCR_DPCC);

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->WRPCR, DSI_WRPCR_PLLEN) == DSI_WRPCR_PLLEN)
  {
    return HAL_ERROR;
  }

  if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_1_LANE)
  {
    if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_UAN0 | DSI_PSR_PSS0)) == (DSI_PSR_UAN0 | DSI_PSR_PSS0))
    {
      return HAL_ERROR;
    }
  }
  else if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PCONFR, DSI_PCONFR_NL) == HAL_DSI_DATA_2_LANES)
  {
    if (READ_BIT(DSI_GET_INSTANCE(hdsi)->PSR, (DSI_PSR_UAN0 | DSI_PSR_PSS0 | DSI_PSR_PSS1 | \
                                               DSI_PSR_UAN1)) != (DSI_PSR_UAN0 | DSI_PSR_PSS0 \
                                                                  | DSI_PSR_PSS1 | DSI_PSR_UAN1))
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  HAL_Delay(1);

  tickstart = HAL_GetTick();

  while (HAL_DSI_GetFlag(hdsi, HAL_DSI_FLAG_PLLLS) == 0U)
  {

    if ((HAL_GetTick() - tickstart) > DSI_TIMEOUT_VALUE)
    {

      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/** @brief  Return the peripheral clock frequency for DSI.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Source clock of the DSI not configured or not ready
  */
uint32_t HAL_DSI_GetClockFreq(const hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM((hdsi != NULL));

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_INIT \
                   | (uint32_t)HAL_DSI_STATE_CONFIGURED \
                   | (uint32_t)HAL_DSI_STATE_ACTIVE);

  STM32_UNUSED(hdsi);

  return HAL_RCC_DSI_GetKernelClkFreq();
}

/**
  * @brief  Start test pattern generation.
  * @param  hdsi  pointer to a hal_dsi_handle_t structure that contains
  *               the configuration information for the DSI.
  * @param  pattern_generator  Pattern generator mode
  * @retval HAL_OK
  */
hal_status_t HAL_DSI_SetConfigPatternGenerator(hal_dsi_handle_t *hdsi, const hal_dsi_pattern_t pattern_generator)
{
  ASSERT_DBG_PARAM(hdsi != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_ACTIVE);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->VMCR, (DSI_VMCR_PGM | DSI_VMCR_PGO), (uint32_t)pattern_generator);

  return HAL_OK;
}

/**
  * @brief  Get pattern generator configuration.
  * @param  hdsi     Pointer to a hal_dsi_handle_t structure
  *                      This parameter can be any combination of @arg DSI Pattern generator
  * @retval HAL_DSI_PATTERN_VERTICAL_COLOR_BARS   Orientation vertical color bars
  * @retval HAL_DSI_PATTERN_HORIZONTAL_COLOR_BARS Orientation horizontal color bars
  * @retval HAL_DSI_PATTERN_VERTICAL_BER          BER pattern
  */
hal_dsi_pattern_t HAL_DSI_GetConfigPatternGenerator(const hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);

  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_ACTIVE);

  return ((hal_dsi_pattern_t)(uint32_t)READ_BIT(DSI_GET_INSTANCE(hdsi)->VMCR, (DSI_VMCR_PGM | DSI_VMCR_PGO)));
}

/**
  * @brief  Enable the swap lane pins.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @param  lane  DSI swap lane feature .
  * @retval HAL_OK swap lane pins enabled.
  */
hal_status_t HAL_DSI_EnableSwapLanePins(hal_dsi_handle_t *hdsi, hal_dsi_swap_lane_t lane)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_LANE(lane));
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->WPCR[0U], (DSI_WPCR0_SWCL | DSI_WPCR0_SWDL0 | DSI_WPCR0_SWDL1), (uint32_t)lane);

  return HAL_OK;
}

/**
  * @brief  Disable the swap lane pins.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @param  lane  DSI swap lane feature .
  * @retval HAL_OK swap lane pins enabled.
  */
hal_status_t HAL_DSI_DisableSwapLanePins(hal_dsi_handle_t *hdsi, hal_dsi_swap_lane_t lane)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_LANE(lane));
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  CLEAR_BIT(DSI_GET_INSTANCE(hdsi)-> WPCR[0U], DSI_WPCR0_SWCL);
  CLEAR_BIT(DSI_GET_INSTANCE(hdsi)-> WPCR[0U], DSI_WPCR0_SWDL0);
  CLEAR_BIT(DSI_GET_INSTANCE(hdsi)-> WPCR[0U], DSI_WPCR0_SWDL1);

  return HAL_OK;
}

/**
  * @brief  Check if the the swap lane pins is enabled or disabled.
  * @param  hdsi Pointer to a hal_dsi_handle_t structure.
  * @param  lane  DSI swap lane feature.
  * @retval HAL_DSI_AUTO_CLK_LANE_CTRL_DISABLE  Automatic clock lane control disabled
  * @retval HAL_DSI_AUTO_CLK_LANE_CTRL_ENABLE  Automatic clock lane control enabled
  */
hal_dsi_swap_lane_status_t HAL_DSI_IsEnabledSwapLanePins(const hal_dsi_handle_t *hdsi, hal_dsi_swap_lane_t lane)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  return ((hal_dsi_swap_lane_status_t)(uint32_t)READ_BIT(DSI_GET_INSTANCE(hdsi)-> WPCR[0U], (DSI_WPCR0_SWCL \
                                                         | DSI_WPCR0_SWDL0 | DSI_WPCR0_SWDL1, (uint32_t)lane)));
}

/**
  * @brief  Enable the Force TX stop mode.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @param  lane  DSI swap lane feature.
  * @retval HAL_OK Automatic clock lane control enabled.
  */
hal_status_t HAL_DSI_EnableForceTXStopMode(hal_dsi_handle_t *hdsi, hal_dsi_force_lane_t lane)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_LANE_GROUP(lane));
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  MODIFY_REG(DSI_GET_INSTANCE(hdsi)->WPCR[0U], (DSI_WPCR0_FTXSMCL | DSI_WPCR0_FTXSMDL), (uint32_t)lane);

  return HAL_OK;
}

/**
  * @brief  Disable the Force TX stop mode.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @param  lane  DSI swap lane feature.
  * @retval HAL_OK the Force TX stop mode enabled.
  */
hal_status_t HAL_DSI_DisableForceTXStopMode(hal_dsi_handle_t *hdsi, hal_dsi_force_lane_t lane)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(IS_DSI_LANE_GROUP(lane));
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  CLEAR_BIT(DSI_GET_INSTANCE(hdsi)-> WPCR[0U], DSI_WPCR0_FTXSMCL);
  CLEAR_BIT(DSI_GET_INSTANCE(hdsi)-> WPCR[0U], DSI_WPCR0_FTXSMDL);

  return HAL_OK;
}

/**
  * @brief  Check if the Force TX stop mode is enabled or disabled.
  * @param  hdsi Pointer to a hal_dsi_handle_t structure
  * @param  lane  DSI force lane feature.
  * @retval HAL_DSI_AUTO_CLK_LANE_CTRL_DISABLE  Automatic clock lane control disabled
  * @retval HAL_DSI_AUTO_CLK_LANE_CTRL_ENABLE  Automatic clock lane control enabled
  */
hal_dsi_force_lane_status_t HAL_DSI_IsEnabledForceTXStopMode(const hal_dsi_handle_t *hdsi, hal_dsi_force_lane_t lane)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_IDLE);

  return ((hal_dsi_force_lane_status_t)(uint32_t)READ_BIT(DSI_GET_INSTANCE(hdsi)-> WPCR[0U], (DSI_WPCR0_FTXSMCL \
                                                          | DSI_WPCR0_FTXSMCL, (uint32_t)lane)));
}

#if defined(USE_HAL_LTDC_MODULE) && defined(USE_HAL_DSI_MODULE)
/**
  * @brief  Get Video Timing From LTDC.
  * @param  hdsi  Pointer to a hal_dsi_handle_t structure
  * @param  p_config pointer to a hal_ltdc_config_t structure that contains
  *                 the DSI video mode configuration parameters
  * @param  p_videoconfig pointer to a hal_dsi_video_config_t structure that contains
  *                the DSI video mode configuration parameters
  * @retval HAL_OK.
  */
hal_status_t HAL_DSI_GetVideoTimingFromDSI(hal_dsi_handle_t *hdsi, hal_dsi_video_config_t *p_videoconfig,
                                           hal_ltdc_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_videoconfig != NULL);
  ASSERT_DBG_STATE(hdsi->global_state, (uint32_t)HAL_DSI_STATE_CONFIGURED);

  p_config->vsync = p_videoconfig->v_sync_active - 1U;

  p_config->v_back_porch = p_videoconfig->v_sync_active + p_videoconfig->v_back_porch - 1U;

  p_config->active_height = p_videoconfig->v_sync_active + p_videoconfig->v_back_porch + \
                            p_videoconfig-> v_active - 1U;

  p_config->v_front_porch = p_videoconfig->v_sync_active + p_videoconfig->v_back_porch + \
                            p_videoconfig->v_active + p_videoconfig->v_front_porch - 1U;

  return HAL_OK;
}

/**
  * @brief  Get Video Timing From LTDC.
  * @param  hltdc  Pointer to a hal_ltdc_handle_t structure
  * @param  p_config pointer to a hal_ltdc_config_t structure that contains
  *                 the DSI video mode configuration parameters
  * @param  p_videoconfig pointer to a hal_dsi_video_config_t structure that contains
  *                the DSI video mode configuration parameters
  * @retval HAL_OK.
  */
hal_status_t HAL_DSI_GetVideoTimingFromLTDC(hal_ltdc_handle_t *hltdc, hal_ltdc_config_t *p_config,
                                            hal_dsi_video_config_t *p_videoconfig)
{
  ASSERT_DBG_PARAM(hdsi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_videoconfig != NULL);
  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t)HAL_LTDC_STATE_CONFIGURED);

  p_videoconfig->v_sync_active = p_config->vsync + 1U;

  p_videoconfig->v_back_porch = p_config->v_back_porch - p_config->v_sync_active ;

  p_videoconfig->v_active = p_config->active_height - p_config->v_back_porch;

  p_videoconfig->v_front_porch = p_config->v_front_porch - p_config->active_heigh;

  return HAL_OK;
}
#endif /* USE_HAL_LTDC_MODULE */

/**
  * @}
  */

/** @addtogroup DSI_Exported_Functions_Group5
  * @{
This subsection provides functions allowing to
 - HAL_DSI_GetState()          : Check the DSI state.
 - HAL_DSI_GetLastErrorCodes() : Get the specific DSI error flag.
  */

/**
  * @brief  Return the DSI state.
  * @param  hdsi            Pointer to a hal_dsi_handle_t structure
  * @retval hal_dsi_state_t  DSI global state
  */
hal_dsi_state_t HAL_DSI_GetState(hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);

  return hdsi->global_state;
}

#if defined (USE_HAL_DSI_REGISTER_CALLBACKS) && (USE_HAL_DSI_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register a User DSI callback.
  * @param  hdsi              pointer to @ref hal_dsi_handle_t structure.
  * @param  p_callback          pointer to the callback function
  * @retval HAL_OK            succeed.
  * @retval HAL_INVALID_PARAM invalid callback.
  */
hal_status_t HAL_DSI_RegisterErrorCallback(hal_dsi_handle_t *hdsi, hal_dsi_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hdsi != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdsi->p_error_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_DSI_REGISTER_CALLBACKS*/

#if defined (USE_HAL_DSI_REGISTER_CALLBACKS) && (USE_HAL_DSI_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register a User DSI callback.
  * @param  hdsi              pointer to @ref hal_dsi_handle_t structure.
  * @param  p_callback          pointer to the callback function
  * @retval HAL_OK            succeed.
  * @retval HAL_INVALID_PARAM invalid callback.
  */
hal_status_t HAL_DSI_RegisterTearingEffectCallback(hal_dsi_handle_t *hdsi, hal_dsi_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hdsi != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdsi->p_tearing_effect_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_DSI_REGISTER_CALLBACKS*/

#if defined (USE_HAL_DSI_REGISTER_CALLBACKS) && (USE_HAL_DSI_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register a User DSI callback.
  * @param  hdsi              pointer to @ref hal_dsi_handle_t structure.
  * @param  p_callback          pointer to the callback function
  * @retval HAL_OK            succeed.
  * @retval HAL_INVALID_PARAM invalid callback.
  */
hal_status_t HAL_DSI_RegisterEndOfRefreshCallback(hal_dsi_handle_t *hdsi, hal_dsi_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hdsi != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdsi->p_refresh_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_DSI_REGISTER_CALLBACKS*/

#if defined (USE_HAL_DSI_GET_LAST_ERRORS) && (USE_HAL_DSI_GET_LAST_ERRORS == 1)
/**
  * @brief  Return the DSI error code.
  * @param  hdsi    Pointer to a hal_dsi_handle_t structure
  * @retval uint32_t Error code value which can be a combination of:
  *                  @arg @ref HAL_DSI_ERROR_NONE    : No error
  *                  @arg @ref HAL_DSI_ERROR_ACK     : Acknowledge errors
  *                  @arg @ref HAL_DSI_ERROR_TX      : Transmission error
  *                  @arg @ref HAL_DSI_ERROR_RX      : Reception error
  *                  @arg @ref HAL_DSI_ERROR_CRC     : CRC error
  *                  @arg @ref HAL_DSI_ERROR_PSE     : Packet Size error
  *                  @arg @ref HAL_DSI_ERROR_EOT     : End Of Transmission error
  *                  @arg @ref HAL_DSI_ERROR_OVF     : FIFO overflow error
  *                  @arg @ref HAL_DSI_ERROR_PBU     : Payload Buffer Underflow error
  *                  @arg @ref HAL_DSI_ERROR_ECC     : ECC errors
  *                  @arg @ref HAL_DSI_ERROR_PHY     : PHY related errors
  *                  @arg @ref HAL_DSI_ERROR_GEN     : Generic FIFO related errors
  *
  *
  */
uint32_t HAL_DSI_GetLastErrorCodes(const hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);

  return hdsi->last_error_codes;
}
#endif /* USE_HAL_DCMI_GET_LAST_ERRORS */

/**
  * @}
  */

/** @addtogroup DSI_Exported_Functions_Group6
  * @{
  This subsection provides functions allowing to:
   - HAL_DSI_SetUserData() Set a user data pointer (ex: a user context) in a HAL DSI handle,
   - HAL_DSI_GetUserData() Get a user data pointer (ex: a user context) from a HAL DSI handle.
  */

#if defined(USE_HAL_DSI_USER_DATA) && (USE_HAL_DSI_USER_DATA == 1)
/**
  * @brief Store the user data into the DSI handle.
  * @param hdsi        Pointer to DSI handle
  * @param p_user_data  Pointer to the user data
  */
void HAL_DSI_SetUserData(hal_dsi_handle_t *hdsi, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hdsi != NULL);

  hltdc->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the user data from the DSI handle.
  * @param hdsi   Pointer to DSI handle
  * @retval Pointer to the user data
  */
const void *HAL_DSI_GetUserData(const hal_dsi_handle_t *hdsi)
{
  ASSERT_DBG_PARAM(hdsi != NULL);

  return (hdsi->p_user_data);
}
#endif /* USE_HAL_DSI_USER_DATA */

/**
  * @}
  */
/**
  * @}
  */
#endif /* DSI */
#endif /* HAL_DSI_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
