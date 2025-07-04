/**
  ******************************************************************************
  * @file    stm32u5xx_hal_sai.h
  * @brief   Header file of SAI HAL module.
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
#ifndef STM32U5XX_HAL_SAI_H
#define STM32U5XX_HAL_SAI_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup SAI SAI
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup SAI_Exported_Types SAI Exported Types
  * @{
  */

/** @defgroup SAI_Exported_Types_Group1 Enumerations
  * @{
  */

/**
  * @brief HAL SAI block definitions.
  */
typedef enum
{
  HAL_SAI1_BLOCK_A = (uint32_t)SAI1_Block_A,        /*!< Instance SAI1, Block A */
  HAL_SAI1_BLOCK_B = (uint32_t)SAI1_Block_B,        /*!< Instance SAI1, Block B */
#if defined(SAI2)
  HAL_SAI2_BLOCK_A = (uint32_t)SAI2_Block_A,        /*!< Instance SAI2, Block A */
  HAL_SAI2_BLOCK_B = (uint32_t)SAI2_Block_B         /*!< Instance SAI2, Block B */
#endif /* SAI2 */
} hal_sai_block_t;

/**
  * @brief HAL SAI state definitions.
  */
typedef enum
{
  HAL_SAI_STATE_RESET     = 0U,          /*!< SAI not initialized, not configured and not started */
  HAL_SAI_STATE_INIT      = (1U << 31U), /*!< SAI initialized, not configured and not started */
  HAL_SAI_STATE_IDLE      = (1U << 30U), /*!< SAI initialized, configured and not started */
  HAL_SAI_STATE_TX_ACTIVE = (1U << 29U), /*!< SAI started, data transmission process is ongoing */
  HAL_SAI_STATE_RX_ACTIVE = (1U << 28U), /*!< SAI started, data reception process is ongoing */
  HAL_SAI_STATE_TX_PAUSED = (1U << 27U), /*!< SAI started, data transmission process is paused */
  HAL_SAI_STATE_RX_PAUSED = (1U << 26U), /*!< SAI started, data reception process is paused */
  HAL_SAI_STATE_ABORT     = (1U << 25U), /*!< SAI is aborting current process */
} hal_sai_state_t;

#if defined(SAI2)
/**
  * @brief HAL SAI synchronization output definitions.
  */
typedef enum
{
  HAL_SAI_SYNC_OUTPUT_DISABLE        = 0U,                /*!< Synchronization output signals disabled */
  HAL_SAI_SYNC_OUTPUT_BLOCK_A_ENABLE = SAI_GCR_SYNCOUT_0, /*!< Synchronization output signals block A enabled */
  HAL_SAI_SYNC_OUTPUT_BLOCK_B_ENABLE = SAI_GCR_SYNCOUT_1  /*!< Synchronization output signals block B enabled */
} hal_sai_sync_output_t;
#endif /* SAI2 */

/**
  * @brief HAL SAI master clock output status definitions.
  */
typedef enum
{
  HAL_SAI_MCLK_OUTPUT_DISABLED = 0U,            /*!< Master clock generation is disabled */
  HAL_SAI_MCLK_OUTPUT_ENABLED  = SAI_xCR1_MCKEN /*!< Master clock generation is enabled */
} hal_sai_mclk_output_status_t;

/**
  * @brief HAL SAI audio frequency definitions.
  */
typedef enum
{
  HAL_SAI_AUDIO_FREQUENCY_MCLK_DIV = 0U,     /*!< Audio frequency set during the configuration with mclk_div */
  HAL_SAI_AUDIO_FREQUENCY_8KHZ     = 8000U,  /*!< Audio frequency 8 kHz */
  HAL_SAI_AUDIO_FREQUENCY_11KHZ    = 11025U, /*!< Audio frequency 11.025 kHz */
  HAL_SAI_AUDIO_FREQUENCY_16KHZ    = 16000U, /*!< Audio frequency 16 kHz */
  HAL_SAI_AUDIO_FREQUENCY_22KHZ    = 22050U, /*!< Audio frequency 22.05 kHz */
  HAL_SAI_AUDIO_FREQUENCY_32KHZ    = 32000U, /*!< Audio frequency 32 kHz */
  HAL_SAI_AUDIO_FREQUENCY_44KHZ    = 44100U, /*!< Audio frequency 44.1 kHz */
  HAL_SAI_AUDIO_FREQUENCY_48KHZ    = 48000U, /*!< Audio frequency 48 kHz */
  HAL_SAI_AUDIO_FREQUENCY_96KHZ    = 96000U, /*!< Audio frequency 96 kHz */
  HAL_SAI_AUDIO_FREQUENCY_192KHZ   = 192000U /*!< Audio frequency 192 kHz */
} hal_sai_audio_frequency_t;

/**
  * @brief HAL SAI master clock oversampling definitions.
  */
typedef enum
{
  HAL_SAI_MCLK_OVERSAMPLING_DISABLE = 0U,          /*!< Master clock oversampling disable */
  HAL_SAI_MCLK_OVERSAMPLING_ENABLE  = SAI_xCR1_OSR /*!< Master clock oversampling enable */
} hal_sai_mclk_oversampling_t;

/**
  * @brief HAL SAI PDM clock definitions.
  */
typedef enum
{
  HAL_SAI_PDM_CLOCK1_CLOCK2_DISABLE = 0U,                                 /*!< PDM clock1 and clock2 disable */
  HAL_SAI_PDM_CLOCK1_ENABLE         = SAI_PDMCR_CKEN1,                    /*!< PDM clock1 enable */
  HAL_SAI_PDM_CLOCK2_ENABLE         = SAI_PDMCR_CKEN2,                    /*!< PDM clock2 enable */
  HAL_SAI_PDM_CLOCK1_CLOCK2_ENABLE  = (SAI_PDMCR_CKEN1 | SAI_PDMCR_CKEN2) /*!< PDM clock1 and clock2 enable */
} hal_sai_pdm_clock_t;

/**
  * @brief HAL SAI mode definitions.
  */
typedef enum
{
  HAL_SAI_MODE_MASTER_TX = 0U,                                 /*!< Master transmitter mode */
  HAL_SAI_MODE_MASTER_RX = SAI_xCR1_MODE_0,                    /*!< Master receiver mode */
  HAL_SAI_MODE_SLAVE_TX  = SAI_xCR1_MODE_1,                    /*!< Slave transmitter mode */
  HAL_SAI_MODE_SLAVE_RX  = (SAI_xCR1_MODE_1 | SAI_xCR1_MODE_0) /*!< Slave receiver mode */
} hal_sai_mode_t;

/**
  * @brief HAL SAI protocol definitions.
  */
typedef enum
{
  HAL_SAI_PROTOCOL_FREE  = 0U,                /*!< Free protocol */
  HAL_SAI_PROTOCOL_SPDIF = SAI_xCR1_PRTCFG_0, /*!< SPDIF protocol */
  HAL_SAI_PROTOCOL_AC97  = SAI_xCR1_PRTCFG_1, /*!< AC97 protocol */
} hal_sai_protocol_t;

/**
  * @brief HAL SAI data size definitions.
  */
typedef enum
{
  HAL_SAI_DATA_SIZE_8BITS  = SAI_xCR1_DS_1,                                  /*!< Data size 8 bits */
  HAL_SAI_DATA_SIZE_10BITS = (SAI_xCR1_DS_1 | SAI_xCR1_DS_0),                /*!< Data size 10 bits */
  HAL_SAI_DATA_SIZE_16BITS = SAI_xCR1_DS_2,                                  /*!< Data size 16 bits */
  HAL_SAI_DATA_SIZE_20BITS = (SAI_xCR1_DS_2 | SAI_xCR1_DS_0),                /*!< Data size 20 bits */
  HAL_SAI_DATA_SIZE_24BITS = (SAI_xCR1_DS_2 | SAI_xCR1_DS_1),                /*!< Data size 24 bits */
  HAL_SAI_DATA_SIZE_32BITS = (SAI_xCR1_DS_2 | SAI_xCR1_DS_1 | SAI_xCR1_DS_0) /*!< Data size 32 bits */
} hal_sai_data_size_t;

/**
  * @brief HAL SAI bit order definitions.
  */
typedef enum
{
  HAL_SAI_BIT_ORDER_MSB = 0U,               /*!< Data transfer with MSB first */
  HAL_SAI_BIT_ORDER_LSB = SAI_xCR1_LSBFIRST /*!< Data transfer with LSB first */
} hal_sai_bit_order_t;

/**
  * @brief HAL SAI clock strobing edge definitions.
  */
typedef enum
{
  HAL_SAI_CLOCK_STROBING_FALLING_EDGE = 0U,            /*!< Clock strobing falling edge */
  HAL_SAI_CLOCK_STROBING_RISING_EDGE  = SAI_xCR1_CKSTR /*!< Clock strobing rising edge */
} hal_sai_clock_strobing_edge_t;

/**
  * @brief HAL SAI synchronization definitions.
  */
typedef enum
{
  HAL_SAI_SYNC_NO       = 0U,                /*!< Asynchronous */
  HAL_SAI_SYNC_INTERNAL = SAI_xCR1_SYNCEN_0, /*!< Synchronous with other block of same SAI */
#if defined(SAI2)
  HAL_SAI_SYNC_EXTERNAL = SAI_xCR1_SYNCEN_1, /*!< Synchronous with other SAI, SAI1 or SAI2 */
#endif /* SAI2 */
} hal_sai_sync_t;

/**
  * @brief HAL SAI output drive status definitions.
  */
typedef enum
{
  HAL_SAI_OUTPUT_DRIVE_DISABLED = 0U,              /*!< Output drive is disabled */
  HAL_SAI_OUTPUT_DRIVE_ENABLED  = SAI_xCR1_OUTDRIV /*!< Output drive is enabled */
} hal_sai_output_drive_status_t;

/**
  * @brief HAL SAI master divider definitions.
  */
typedef enum
{
  HAL_SAI_MASTER_DIVIDER_ENABLE  = 0U,            /*!< Master divider enable */
  HAL_SAI_MASTER_DIVIDER_DISABLE = SAI_xCR1_NODIV /*!< Master divider disable */
} hal_sai_master_divider_t;

/**
  * @brief HAL SAI frame synchronization definitions.
  */
typedef enum
{
  HAL_SAI_FS_START_FRAME            = 0U,             /*!< Frame synchronization signal is a start frame signal */
  HAL_SAI_FS_CHANNEL_IDENTIFICATION = SAI_xFRCR_FSDEF /*!< Frame synchronization signal is a start frame signal
                                                           and channel side identification */
} hal_sai_fs_definition_t;

/**
  * @brief HAL SAI frame synchronization polarity definitions.
  */
typedef enum
{
  HAL_SAI_FS_POLARITY_FALLING = 0U,             /*!< Frame synchronization is active low (falling edge) */
  HAL_SAI_FS_POLARITY_RISING  = SAI_xFRCR_FSPOL /*!< Frame synchronization is active high (rising edge) */
} hal_sai_fs_polarity_t;

/**
  * @brief HAL SAI frame synchronization offset definitions.
  */
typedef enum
{
  HAL_SAI_FS_FIRST_BIT        = 0U,             /*!< Frame synchronization is asserted on the 1st bit of the slot 0 */
  HAL_SAI_FS_BEFORE_FIRST_BIT = SAI_xFRCR_FSOFF /*!< Frame synchronization is asserted one bit before the 1st bit
                                                     of the slot 0 */
} hal_sai_fs_offset_t;

/**
  * @brief HAL SAI slot size definitions.
  */
typedef enum
{
  HAL_SAI_SLOT_SIZE_DATA_SIZE    = 0U,                  /*!< Slot size is equivalent to the data size */
  HAL_SAI_SLOT_SIZE_16BITS       = SAI_xSLOTR_SLOTSZ_0, /*!< Slot size 16 bits */
  HAL_SAI_SLOT_SIZE_32BITS       = SAI_xSLOTR_SLOTSZ_1  /*!< Slot size 32 bits */
} hal_sai_slot_size_t;

/**
  * @brief   HAL SAI mono mode status definitions.
  * @warning It is meaningful only when the number of slots is equal to 2.
  */
typedef enum
{
  HAL_SAI_MONO_MODE_DISABLED = 0U,           /*!< Mono mode disabled (stereo mode) */
  HAL_SAI_MONO_MODE_ENABLED  = SAI_xCR1_MONO /*!< Mono mode enabled */
} hal_sai_mono_mode_status_t;

/**
  * @brief HAL SAI tristate SD output status definitions.
  */
typedef enum
{
  HAL_SAI_TRISTATE_SD_OUTPUT_NOT_RELEASED = 0U,           /*!< SD output line is still driven by the SAI
                                                               when a slot is inactive */
  HAL_SAI_TRISTATE_SD_OUTPUT_RELEASED     = SAI_xCR2_TRIS /*!< SD output line is released (HI-Z) at the end of the last
                                                               data bit of the last active slot
                                                               if the next one is inactive */
} hal_sai_tristate_sd_output_status_t;

/**
  * @brief HAL SAI FIFO threshold definitions.
  */
typedef enum
{
  HAL_SAI_FIFO_THRESHOLD_EMPTY = 0U,                                /*!< FIFO threshold empty */
  HAL_SAI_FIFO_THRESHOLD_1_4   = SAI_xCR2_FTH_0,                    /*!< FIFO threshold quarter */
  HAL_SAI_FIFO_THRESHOLD_1_2   = SAI_xCR2_FTH_1,                    /*!< FIFO threshold half */
  HAL_SAI_FIFO_THRESHOLD_3_4   = (SAI_xCR2_FTH_1 | SAI_xCR2_FTH_0), /*!< FIFO threshold three-quarter */
  HAL_SAI_FIFO_THRESHOLD_FULL  = SAI_xCR2_FTH_2                     /*!< FIFO threshold full */
} hal_sai_fifo_threshold_t;

/**
  * @brief HAL SAI companding definitions.
  */
typedef enum
{
  HAL_SAI_COMPANDING_NO        = 0U,                                                /*!< No companding */
  HAL_SAI_COMPANDING_ULAW_1CPL = SAI_xCR2_COMP_1,                                   /*!< Micro-law companding
                                                                                         with 1's complement */
  HAL_SAI_COMPANDING_ALAW_1CPL = (SAI_xCR2_COMP_1 | SAI_xCR2_COMP_0),               /*!< A-law companding
                                                                                         with 1's complement */
  HAL_SAI_COMPANDING_ULAW_2CPL = (SAI_xCR2_COMP_1 | SAI_xCR2_CPL),                  /*!< Micro-law companding
                                                                                         with 2's complement */
  HAL_SAI_COMPANDING_ALAW_2CPL = (SAI_xCR2_COMP_1 | SAI_xCR2_COMP_0 | SAI_xCR2_CPL) /*!< A-law companding
                                                                                         with 2's complement */
} hal_sai_companding_t;

/**
  * @brief HAL SAI mute mode definitions.
  */
typedef enum
{
  HAL_SAI_MUTE_MODE_ZERO_VALUE = 0U,              /*!< Bit value 0 is sent during the mute mode */
  HAL_SAI_MUTE_MODE_LAST_VALUE = SAI_xCR2_MUTEVAL /*!< Last values are sent during the mute mode */
} hal_sai_mute_mode_t;

/**
  * @brief HAL SAI PDM status definitions.
  */
typedef enum
{
  HAL_SAI_PDM_DISABLED = 0U,             /*!< PDM is disabled */
  HAL_SAI_PDM_ENABLED  = SAI_PDMCR_PDMEN /*!< PDM is enabled */
} hal_sai_pdm_status_t;

/**
  * @brief HAL SAI mute Rx detection status definitions.
  */
typedef enum
{
  HAL_SAI_MUTE_RX_DETECTION_DISABLED = 0U, /*!< Mute Rx detection is disabled */
  HAL_SAI_MUTE_RX_DETECTION_ENABLED  = 1U  /*!< Mute Rx detection is enabled */
} hal_sai_mute_rx_detection_status_t;

/**
  * @}
  */

/** @defgroup SAI_Exported_Types_Group2 SAI Frame Structure
  * @{
  */

/**
  * @brief HAL SAI frame structure definition.
  * @note  For SPDIF and AC97 protocol, these parameters are not used (set by hardware).
  */
typedef struct
{
  uint32_t frame_length;                 /*!< Frame length, the number of SCK clocks for each audio frame.
                                              This parameter must be a number between Min_Data = 8 and Max_Data = 256.
                                              If master clock MCLK_x pin is declared as an output, the frame length
                                              must be aligned to a number equal to power of 2 in order to keep
                                              in an audio frame, an integer number of MCLK pulses by bit Clock. */

  uint32_t active_frame_length;          /*!< Frame synchronization active level length.
                                              This parameter specifies the length in number of bit clock (SCK + 1) of
                                              the active level of FS signal in audio frame. This parameter must be a
                                              number between Min_Data = 1 and Max_Data = 128. */

  hal_sai_fs_definition_t fs_definition; /*!< Frame synchronization definition. */

  hal_sai_fs_polarity_t fs_polarity;     /*!< Frame synchronization polarity. */

  hal_sai_fs_offset_t fs_offset;         /*!< Frame synchronization offset. */
} hal_sai_frame_t;
/**
  * @}
  */

/** @defgroup SAI_Exported_Types_Group3 SAI Slot Structure
  * @{
  */

/**
  * @brief HAL SAI slot structure definition.
  * @note  For SPDIF protocol, these parameters are not used (set by hardware).
  * @note  For AC97 protocol, only slot_active parameter is used (the others are set by hardware).
  */
typedef struct
{
  uint32_t slot_first_bit_offset; /*!< Position of first data transfer bit in the slot.
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 24. */

  uint32_t slot_number;           /*!< Number of slot in the audio frame.
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 16. */

  uint32_t slot_active;           /*!< Slots in audio frame that will be activated.
                                       This parameter can be a combination of @ref SAI_Block_Slot_Active. */

  hal_sai_slot_size_t slot_size;  /*!< Slot Size. */
} hal_sai_slot_t;
/**
  * @}
  */

/** @defgroup SAI_Exported_Types_Group4 SAI Configuration Structure
  * @{
  */

/**
  * @brief HAL SAI configuration structure definition.
  */
typedef struct
{
  hal_sai_mode_t mode;                               /*!< Audio Mode. */

  hal_sai_master_divider_t divider;                  /*!< Whether master clock will be divided or not.
                                                          If bit NODIV in the SAI_xCR1 register is cleared,
                                                          the frame length must be aligned to a number equal to
                                                          a power of 2, from 8 to 256.
                                                          If bit NODIV in the SAI_xCR1 register is set,
                                                          the frame length can take any of the values from 8 to 256. */

  hal_sai_audio_frequency_t audio_frequency;         /*!< Audio frequency sampling. */

  uint32_t mclk_div;                                 /*!< Master clock divider.
                                                          This parameter must be a number between Min_Data = 0 and
                                                          Max_Data = 63. This parameter is used only if audio_frequency
                                                          is set to @ref HAL_SAI_AUDIO_FREQUENCY_MCLK_DIV
                                                          otherwise it is internally computed. */

  hal_sai_mclk_oversampling_t mclk_oversampling;     /*!< Master clock oversampling. */

  hal_sai_protocol_t protocol;                       /*!< Protocol. */

  hal_sai_data_size_t data_size;                     /*!< Data size. */

  hal_sai_bit_order_t bit_order;                     /*!< Data transfers start from MSB or LSB bit. */

  hal_sai_clock_strobing_edge_t clock_strobing_edge; /*!< Clock strobing edge sensitivity. */

  hal_sai_frame_t frame;                             /*!< Frame structure. */

  hal_sai_slot_t slot;                               /*!< Slot structure. */
} hal_sai_config_t;
/**
  * @}
  */

/** @defgroup SAI_Exported_Types_Group5 SAI PDM Structure
  * @{
  */

/**
  * @brief  HAL SAI PDM microphone delay structure definition.
  */
typedef struct
{
  uint32_t pdm_mic_pairs_nbr; /*!< Pair of microphones selected.
                                   This parameter must be a number between Min_Data = 1 and Max_Data = 3. */

  uint32_t pdm_left_delay;    /*!< Delay in PDM clock unit to apply on left microphone.
                                   This parameter must be a number between Min_Data = 0 and Max_Data = 7. */

  uint32_t pdm_right_delay;   /*!< Delay in PDM clock unit to apply on right microphone.
                                   This parameter must be a number between Min_Data = 0 and Max_Data = 7. */
} hal_sai_pdm_mic_delay_t;
/**
  * @}
  */

/** @defgroup SAI_Exported_Types_Group6 SAI Handle Structure
  * @{
  */
typedef struct hal_sai_handle_s hal_sai_handle_t; /*!< SAI handle type definition */

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
typedef  void (*hal_sai_cb_t)(hal_sai_handle_t *hsai);  /*!< Pointer to SAI callback functions */
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */

/**
  * @brief HAL SAI handle structure definition.
  *
  */
struct hal_sai_handle_s
{
  /*! SAI Blockx registers base address */
  hal_sai_block_t block;

  /*! SAI global state */
  volatile hal_sai_state_t global_state;

#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
  /*! SAI errors limited to the last process. This parameter can be a combination of @ref SAI_Error_Code. */
  volatile uint32_t last_error_codes;
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  /*! SAI OS semaphore */
  hal_os_semaphore_t semaphore;
#endif /* USE_HAL_MUTEX  */

  /*! Pointer to SAI transfer buffer */
  uint8_t *p_buff;

  /*! SAI transfer size */
  volatile uint32_t xfer_size;

  /*! SAI transfer counter */
  volatile uint32_t xfer_count;

#if defined(USE_HAL_SAI_DMA) && (USE_HAL_SAI_DMA == 1)
  /*! SAI Tx DMA handle */
  hal_dma_handle_t         *hdma_tx;

  /*! SAI Rx DMA handle */
  hal_dma_handle_t         *hdma_rx;
#endif /* USE_HAL_SAI_DMA */

#if defined (USE_HAL_SAI_USER_DATA) && (USE_HAL_SAI_USER_DATA == 1)
  /*! User Data Pointer */
  const void *p_user_data;
#endif /* USE_HAL_SAI_USER_DATA */

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
  /*! SAI receive complete callback */
  hal_sai_cb_t p_rx_cplt_cb;

  /*! SAI receive half complete callback */
  hal_sai_cb_t p_rx_half_cplt_cb;

  /*! SAI transmit complete callback */
  hal_sai_cb_t p_tx_cplt_cb;

  /*! SAI transmit half complete callback */
  hal_sai_cb_t p_tx_half_cplt_cb;

  /*! SAI mute callback */
  hal_sai_cb_t p_mute_cb;

  /*! SAI abort complete callback */
  hal_sai_cb_t p_abort_cplt_cb;

  /*! SAI error callback */
  hal_sai_cb_t p_error_cb;

#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */

  /*! Function pointer on SAI IRQ Handler */
  void (*p_isr)(struct hal_sai_handle_s *hsai);
};

/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup SAI_Exported_Constants SAI Exported Constants
  * @{
  */

#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
/** @defgroup SAI_Error_Code SAI Error Code
  * @{
  */
#define HAL_SAI_ERROR_NONE             0U          /*!< No error */
#define HAL_SAI_ERROR_OVR              (1U << 0U)  /*!< Overrun error */
#define HAL_SAI_ERROR_UDR              (1U << 1U)  /*!< Underrun error */
#define HAL_SAI_ERROR_AFSDET           (1U << 2U)  /*!< Anticipated frame synchronization detection */
#define HAL_SAI_ERROR_LFSDET           (1U << 3U)  /*!< Late frame synchronization detection */
#define HAL_SAI_ERROR_CNREADY          (1U << 4U)  /*!< Codec not ready */
#define HAL_SAI_ERROR_WCKCFG           (1U << 5U)  /*!< Wrong clock configuration */
#define HAL_SAI_ERROR_TIMEOUT          (1U << 6U)  /*!< Timeout error */
#if defined (USE_HAL_SAI_DMA) && (USE_HAL_SAI_DMA == 1)
#define HAL_SAI_ERROR_DMA              (1U << 7U)  /*!< DMA error */
#endif /* USE_HAL_SAI_DMA */
/**
  * @}
  */
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */

/** @defgroup SAI_Block_Slot_Active SAI Block Slot Active
  * @{
  */
#define HAL_SAI_SLOT_NOT_ACTIVE           0U          /*!< No slot active */
#define HAL_SAI_SLOT_ACTIVE_0             (1U << 0U)  /*!< Slot 0 active */
#define HAL_SAI_SLOT_ACTIVE_1             (1U << 1U)  /*!< Slot 1 active */
#define HAL_SAI_SLOT_ACTIVE_2             (1U << 2U)  /*!< Slot 2 active */
#define HAL_SAI_SLOT_ACTIVE_3             (1U << 3U)  /*!< Slot 3 active */
#define HAL_SAI_SLOT_ACTIVE_4             (1U << 4U)  /*!< Slot 4 active */
#define HAL_SAI_SLOT_ACTIVE_5             (1U << 5U)  /*!< Slot 5 active */
#define HAL_SAI_SLOT_ACTIVE_6             (1U << 6U)  /*!< Slot 6 active */
#define HAL_SAI_SLOT_ACTIVE_7             (1U << 7U)  /*!< Slot 7 active */
#define HAL_SAI_SLOT_ACTIVE_8             (1U << 8U)  /*!< Slot 8 active */
#define HAL_SAI_SLOT_ACTIVE_9             (1U << 9U)  /*!< Slot 9 active */
#define HAL_SAI_SLOT_ACTIVE_10            (1U << 10U) /*!< Slot 10 active */
#define HAL_SAI_SLOT_ACTIVE_11            (1U << 11U) /*!< Slot 11 active */
#define HAL_SAI_SLOT_ACTIVE_12            (1U << 12U) /*!< Slot 12 active */
#define HAL_SAI_SLOT_ACTIVE_13            (1U << 13U) /*!< Slot 13 active */
#define HAL_SAI_SLOT_ACTIVE_14            (1U << 14U) /*!< Slot 14 active */
#define HAL_SAI_SLOT_ACTIVE_15            (1U << 15U) /*!< Slot 15 active */
#define HAL_SAI_SLOT_ACTIVE_ALL           0xFFFFU     /*!< All slots active */
/**
  * @}
  */

/** @defgroup SAI_Block_Interrupts_Definition SAI Block Interrupts Definition
  * @{
  */
#define HAL_SAI_IT_OVRUDR                     SAI_xIMR_OVRUDRIE  /*!< Overrun/underrun interrupt */
#define HAL_SAI_IT_MUTEDET                    SAI_xIMR_MUTEDETIE /*!< Mute detection interrupt */
#define HAL_SAI_IT_WCKCFG                     SAI_xIMR_WCKCFGIE  /*!< Wrong clock configuration interrupt */
#define HAL_SAI_IT_FREQ                       SAI_xIMR_FREQIE    /*!< FIFO request interrupt */
#define HAL_SAI_IT_CNRDY                      SAI_xIMR_CNRDYIE   /*!< Codec not ready interrupt (AC'97) */
#define HAL_SAI_IT_AFSDET                     SAI_xIMR_AFSDETIE  /*!< Anticipated frame synchronization detection interrupt */
#define HAL_SAI_IT_LFSDET                     SAI_xIMR_LFSDETIE  /*!< Late frame synchronization detection interrupt */
/**
  * @}
  */

/** @defgroup SAI_Block_Flags_Definition  SAI Block Flags Definition
  * @{
  */
#define HAL_SAI_FLAG_OVRUDR                   SAI_xSR_OVRUDR  /*!< Overrun/underrun flag */
#define HAL_SAI_FLAG_MUTEDET                  SAI_xSR_MUTEDET /*!< Mute detection flag */
#define HAL_SAI_FLAG_WCKCFG                   SAI_xSR_WCKCFG  /*!< Wrong clock configuration flag */
#define HAL_SAI_FLAG_FREQ                     SAI_xSR_FREQ    /*!< FIFO request flag */
#define HAL_SAI_FLAG_CNRDY                    SAI_xSR_CNRDY   /*!< Codec not ready (AC'97) flag */
#define HAL_SAI_FLAG_AFSDET                   SAI_xSR_AFSDET  /*!< Anticipated frame synchronization detection flag */
#define HAL_SAI_FLAG_LFSDET                   SAI_xSR_LFSDET  /*!< Late frame synchronization detection flag */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup SAI_Exported_Macros SAI Exported Macros as inline
  * @{
  */

/** @brief  Enable the specified SAI interrupts.
  * @param  p_saix    SAI block.
  * @param  interrupt SAI interrupt source to enable.
  *         This parameter can be a combination of the following values:
  *            @arg @ref HAL_SAI_IT_OVRUDR Overrun underrun interrupt
  *            @arg @ref HAL_SAI_IT_MUTEDET Mute detection interrupt
  *            @arg @ref HAL_SAI_IT_WCKCFG Wrong Clock Configuration interrupt
  *            @arg @ref HAL_SAI_IT_FREQ FIFO request interrupt
  *            @arg @ref HAL_SAI_IT_CNRDY Codec not ready interrupt
  *            @arg @ref HAL_SAI_IT_AFSDET Anticipated frame synchronization detection interrupt
  *            @arg @ref HAL_SAI_IT_LFSDET Late frame synchronization detection interrupt
  * @warning This is not recommended to use this function for user code.
  */
__STATIC_INLINE void HAL_SAI_EnableIT(SAI_Block_TypeDef *p_saix, uint32_t interrupt)
{
  SET_BIT(p_saix->IMR, interrupt);
}

/** @brief  Disable the specified SAI interrupts.
  * @param  p_saix    SAI block.
  * @param  interrupt SAI interrupt source to disable.
  *         This parameter can be a combination of the following values:
  *            @arg @ref HAL_SAI_IT_OVRUDR Overrun underrun interrupt
  *            @arg @ref HAL_SAI_IT_MUTEDET Mute detection interrupt
  *            @arg @ref HAL_SAI_IT_WCKCFG Wrong Clock Configuration interrupt
  *            @arg @ref HAL_SAI_IT_FREQ FIFO request interrupt
  *            @arg @ref HAL_SAI_IT_CNRDY Codec not ready interrupt
  *            @arg @ref HAL_SAI_IT_AFSDET Anticipated frame synchronization detection interrupt
  *            @arg @ref HAL_SAI_IT_LFSDET Late frame synchronization detection interrupt
  * @warning This is not recommended to use this function for user code.
  */
__STATIC_INLINE void HAL_SAI_DisableIT(SAI_Block_TypeDef *p_saix, uint32_t interrupt)
{
  CLEAR_BIT(p_saix->IMR, interrupt);
}

/** @brief  Check whether the specified SAI interrupt source is enabled or not.
  * @param  p_saix    SAI block.
  * @param  interrupt SAI interrupt source to check.
  *         This parameter can be a combination of the following values:
  *            @arg @ref HAL_SAI_IT_OVRUDR Overrun underrun interrupt
  *            @arg @ref HAL_SAI_IT_MUTEDET Mute detection interrupt
  *            @arg @ref HAL_SAI_IT_WCKCFG Wrong Clock Configuration interrupt
  *            @arg @ref HAL_SAI_IT_FREQ FIFO request interrupt
  *            @arg @ref HAL_SAI_IT_CNRDY Codec not ready interrupt
  *            @arg @ref HAL_SAI_IT_AFSDET Anticipated frame synchronization detection interrupt
  *            @arg @ref HAL_SAI_IT_LFSDET Late frame synchronization detection interrupt
  * @warning This is not recommended to use this function for user code.
  * @retval uint32_t State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t HAL_SAI_GetIT(const SAI_Block_TypeDef *p_saix, uint32_t interrupt)
{
  return ((READ_BIT(p_saix->IMR, interrupt) == (interrupt)) ? 1UL : 0UL);
}

/** @brief  Check whether the specified SAI flag is set or not.
  * @param  p_saix SAI block.
  * @param  flag   SAI flag to check.
  *         This parameter can be a combination of the following values:
  *            @arg @ref HAL_SAI_FLAG_OVRUDR Overrun underrun
  *            @arg @ref HAL_SAI_FLAG_MUTEDET Mute detection
  *            @arg @ref HAL_SAI_FLAG_WCKCFG Wrong Clock Configuration
  *            @arg @ref HAL_SAI_FLAG_FREQ FIFO request
  *            @arg @ref HAL_SAI_FLAG_CNRDY Codec not ready
  *            @arg @ref HAL_SAI_FLAG_AFSDET Anticipated frame synchronization detection
  *            @arg @ref HAL_SAI_FLAG_LFSDET Late frame synchronization detection
  * @warning This is not recommended to use this function for user code.
  * @retval uint32_t State of flag.
  */
__STATIC_INLINE uint32_t HAL_SAI_GetFlag(const SAI_Block_TypeDef *p_saix, uint32_t flag)
{
  return READ_BIT(p_saix->SR, flag);
}

/** @brief  Clear the specified SAI pending flag.
  * @param  p_saix SAI block.
  * @param  flag   SAI flag to clear.
  *          This parameter can be a combination of the following values:
  *            @arg @ref HAL_SAI_FLAG_OVRUDR Clear Overrun underrun
  *            @arg @ref HAL_SAI_FLAG_MUTEDET Clear Mute detection
  *            @arg @ref HAL_SAI_FLAG_WCKCFG Clear Wrong Clock Configuration
  *            @arg @ref HAL_SAI_FLAG_FREQ Clear FIFO request
  *            @arg @ref HAL_SAI_FLAG_CNRDY Clear Codec not ready
  *            @arg @ref HAL_SAI_FLAG_AFSDET Clear Anticipated frame synchronization detection
  *            @arg @ref HAL_SAI_FLAG_LFSDET Clear Late frame synchronization detection
  * @warning This is not recommended to use this function for user code.
  */
__STATIC_INLINE void HAL_SAI_ClearFlag(SAI_Block_TypeDef *p_saix, uint32_t flag)
{
  WRITE_REG(p_saix->CLRFR, flag);
}

/** @brief  Enable SAI.
  * @param  p_saix SAI block.
  * @warning This is not recommended to use this function for user code.
  */
__STATIC_INLINE void HAL_SAI_Enable(SAI_Block_TypeDef *p_saix)
{
  SET_BIT(p_saix->CR1, SAI_xCR1_SAIEN);
}

/** @brief  Disable SAI.
  * @param  p_saix SAI block.
  * @warning This is not recommended to use this function for user code.
  */
__STATIC_INLINE void HAL_SAI_Disable(SAI_Block_TypeDef *p_saix)
{
  CLEAR_BIT(p_saix->CR1, SAI_xCR1_SAIEN);
}
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup SAI_Exported_Functions SAI Exported functions
  * @{
  */

/** @defgroup SAI_Exported_Functions_Group1 Initialization and DeInitialization functions
  * @{
  */
hal_status_t HAL_SAI_Init(hal_sai_handle_t *hsai, hal_sai_block_t block);
void HAL_SAI_DeInit(hal_sai_handle_t *hsai);
/**
  * @}
  */

/** @defgroup SAI_Exported_Functions_Group2 Configuration functions
  * @{
  */
hal_status_t HAL_SAI_SetConfig(hal_sai_handle_t *hsai, const hal_sai_config_t *p_config);
void HAL_SAI_GetConfig(const hal_sai_handle_t *hsai, hal_sai_config_t *p_config);

hal_status_t HAL_SAI_SetSync(hal_sai_handle_t *hsai, hal_sai_sync_t sync);
hal_sai_sync_t HAL_SAI_GetSync(const hal_sai_handle_t *hsai);

#if defined(SAI2)
hal_status_t HAL_SAI_SetSyncOutput(hal_sai_handle_t *hsai, hal_sai_sync_output_t sync_output);
hal_sai_sync_output_t HAL_SAI_GetSyncOutput(const hal_sai_handle_t *hsai);
#endif /* SAI2 */

hal_status_t HAL_SAI_SetFifoThreshold(hal_sai_handle_t *hsai, hal_sai_fifo_threshold_t fifo_threshold);
hal_sai_fifo_threshold_t HAL_SAI_GetFifoThreshold(const hal_sai_handle_t *hsai);

hal_status_t HAL_SAI_SetCompanding(hal_sai_handle_t *hsai, hal_sai_companding_t companding);
hal_sai_companding_t HAL_SAI_GetCompanding(const hal_sai_handle_t *hsai);

hal_status_t HAL_SAI_SetPdmMicDelay(const hal_sai_handle_t *hsai, const hal_sai_pdm_mic_delay_t *p_pdm_mic_delay);
void HAL_SAI_GetPdmMicDelay(const hal_sai_handle_t *hsai, hal_sai_pdm_mic_delay_t *p_pdm_mic_delay);

#if defined (USE_HAL_SAI_DMA) && (USE_HAL_SAI_DMA == 1)
hal_status_t HAL_SAI_SetTxDMA(hal_sai_handle_t *hsai, hal_dma_handle_t *hdma_tx);
hal_status_t HAL_SAI_SetRxDMA(hal_sai_handle_t *hsai, hal_dma_handle_t *hdma_rx);
#endif /* USE_HAL_SAI_DMA */

hal_status_t HAL_SAI_SetAudioFrequency(hal_sai_handle_t *hsai, hal_sai_audio_frequency_t audio_frequency);
hal_sai_audio_frequency_t HAL_SAI_GetAudioFrequency(const hal_sai_handle_t *hsai);
uint32_t HAL_SAI_GetRealAudioFrequency(const hal_sai_handle_t *hsai);

hal_status_t HAL_SAI_SetDataSize(hal_sai_handle_t *hsai, hal_sai_data_size_t data_size);
hal_sai_data_size_t HAL_SAI_GetDataSize(const hal_sai_handle_t *hsai);

hal_status_t HAL_SAI_SetSlotActive(hal_sai_handle_t *hsai, uint32_t slot_active);
uint32_t HAL_SAI_GetSlotActive(const hal_sai_handle_t *hsai);
/**
  * @}
  */

/** @defgroup SAI_Exported_Functions_Group3 Control functions
  * @{
  */
hal_status_t HAL_SAI_EnableMclkOutput(hal_sai_handle_t *hsai);
hal_status_t HAL_SAI_DisableMclkOutput(hal_sai_handle_t *hsai);
hal_sai_mclk_output_status_t HAL_SAI_IsEnabledMclkOutput(const hal_sai_handle_t *hsai);

hal_status_t HAL_SAI_EnableOutputDrive(hal_sai_handle_t *hsai);
hal_status_t HAL_SAI_DisableOutputDrive(hal_sai_handle_t *hsai);
hal_sai_output_drive_status_t HAL_SAI_IsEnabledOutputDrive(const hal_sai_handle_t *hsai);

hal_status_t HAL_SAI_EnableTristateSDOutput(hal_sai_handle_t *hsai);
hal_status_t HAL_SAI_DisableTristateSDOutput(hal_sai_handle_t *hsai);
hal_sai_tristate_sd_output_status_t HAL_SAI_IsEnabledTristateSDOutput(const hal_sai_handle_t *hsai);

hal_status_t HAL_SAI_EnableMonoMode(hal_sai_handle_t *hsai);
hal_status_t HAL_SAI_DisableMonoMode(hal_sai_handle_t *hsai);
hal_sai_mono_mode_status_t HAL_SAI_IsEnabledMonoMode(const hal_sai_handle_t *hsai);

hal_status_t HAL_SAI_EnablePdm(const hal_sai_handle_t *hsai, uint32_t pdm_mic_pairs_nbr, hal_sai_pdm_clock_t clock);
hal_status_t HAL_SAI_DisablePdm(const hal_sai_handle_t *hsai);
hal_sai_pdm_status_t HAL_SAI_IsEnabledPdm(const hal_sai_handle_t *hsai);
/**
  * @}
  */

/** @defgroup SAI_Exported_Functions_Group4 Process functions
  * @{
  */
/* Blocking mode: Polling */
hal_status_t HAL_SAI_Transmit(hal_sai_handle_t *hsai, void *p_data, uint32_t size_sample, uint32_t timeout_ms);
hal_status_t HAL_SAI_Receive(hal_sai_handle_t *hsai, void *p_data, uint32_t size_sample, uint32_t timeout_ms);

/* Non-Blocking mode: Interrupt */
hal_status_t HAL_SAI_Transmit_IT(hal_sai_handle_t *hsai, void *p_data, uint32_t size_sample);
hal_status_t HAL_SAI_Receive_IT(hal_sai_handle_t *hsai, void *p_data, uint32_t size_sample);

#if defined (USE_HAL_SAI_DMA) && (USE_HAL_SAI_DMA == 1)
/* Non-Blocking mode: DMA */
hal_status_t HAL_SAI_Transmit_DMA(hal_sai_handle_t *hsai, void *p_data, uint32_t size_sample);
hal_status_t HAL_SAI_Receive_DMA(hal_sai_handle_t *hsai, void *p_data, uint32_t size_sample);
hal_status_t HAL_SAI_Pause_DMA(hal_sai_handle_t *hsai);
hal_status_t HAL_SAI_Resume_DMA(hal_sai_handle_t *hsai);
#endif /* USE_HAL_SAI_DMA */

/* Abort function */
hal_status_t HAL_SAI_Abort(hal_sai_handle_t *hsai);
hal_status_t HAL_SAI_Abort_IT(hal_sai_handle_t *hsai);

/* Mute management */
hal_status_t HAL_SAI_MuteTx(hal_sai_handle_t *hsai, hal_sai_mute_mode_t mode);
hal_status_t HAL_SAI_UnmuteTx(hal_sai_handle_t *hsai);
hal_status_t HAL_SAI_EnableMuteRxDetection(hal_sai_handle_t *hsai, uint16_t counter);
hal_status_t HAL_SAI_DisableMuteRxDetection(hal_sai_handle_t *hsai);
hal_sai_mute_rx_detection_status_t HAL_SAI_IsEnabledMuteRxDetection(const hal_sai_handle_t *hsai);
/**
  * @}
  */

/** @defgroup SAI_Exported_Functions_Group5 IRQHandler and Callbacks functions
  * @{
  */
void HAL_SAI_IRQHandler(hal_sai_handle_t *hsai);
void HAL_SAI_RxCpltCallback(hal_sai_handle_t *hsai);
void HAL_SAI_RxHalfCpltCallback(hal_sai_handle_t *hsai);
void HAL_SAI_TxCpltCallback(hal_sai_handle_t *hsai);
void HAL_SAI_TxHalfCpltCallback(hal_sai_handle_t *hsai);
void HAL_SAI_MuteCallback(hal_sai_handle_t *hsai);
void HAL_SAI_AbortCpltCallback(hal_sai_handle_t *hsai);
void HAL_SAI_ErrorCallback(hal_sai_handle_t *hsai);

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
hal_status_t HAL_SAI_RegisterRxCpltCallback(hal_sai_handle_t *hsai, hal_sai_cb_t p_callback);
hal_status_t HAL_SAI_RegisterRxHalfCpltCallback(hal_sai_handle_t *hsai, hal_sai_cb_t p_callback);
hal_status_t HAL_SAI_RegisterTxCpltCallback(hal_sai_handle_t *hsai, hal_sai_cb_t p_callback);
hal_status_t HAL_SAI_RegisterTxHalfCpltCallback(hal_sai_handle_t *hsai, hal_sai_cb_t p_callback);
hal_status_t HAL_SAI_RegisterMuteCallback(hal_sai_handle_t *hsai, hal_sai_cb_t p_callback);
hal_status_t HAL_SAI_RegisterAbortCpltCallback(hal_sai_handle_t *hsai, hal_sai_cb_t p_callback);
hal_status_t HAL_SAI_RegisterErrorCallback(hal_sai_handle_t *hsai, hal_sai_cb_t p_callback);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
/**
  * @}
  */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
/** @defgroup SAI_Exported_Functions_Group6 Bus Operation functions
  * @{
  */
hal_status_t HAL_SAI_AcquireBus(hal_sai_handle_t *hsai, uint32_t timeout_ms);
hal_status_t HAL_SAI_ReleaseBus(hal_sai_handle_t *hsai);
/**
  * @}
  */
#endif /* USE_HAL_MUTEX */

#if defined (USE_HAL_SAI_USER_DATA) && (USE_HAL_SAI_USER_DATA == 1)
/** @defgroup SAI_Exported_Functions_Group7 User Data functions
  * @{
  */
void HAL_SAI_SetUserData(hal_sai_handle_t *hsai, const void *p_user_data);
const void *HAL_SAI_GetUserData(const hal_sai_handle_t *hsai);
/**
  * @}
  */
#endif /* USE_HAL_SAI_USER_DATA */

/** @defgroup SAI_Exported_Functions_Group8 State functions
  * @{
  */
hal_sai_state_t HAL_SAI_GetState(const hal_sai_handle_t *hsai);
/**
  * @}
  */

#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
/** @defgroup SAI_Exported_Functions_Group9 Error functions
  * @{
  */
uint32_t HAL_SAI_GetLastErrorCodes(const hal_sai_handle_t *hsai);
/**
  * @}
  */
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */

/** @defgroup SAI_Exported_Functions_Group10 Clock frequency functions
  * @{
  */
uint32_t HAL_SAI_GetClockFreq(const hal_sai_handle_t *hsai);
/**
  * @}
  */

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

#endif /* STM32U5XX_HAL_SAI_H */
