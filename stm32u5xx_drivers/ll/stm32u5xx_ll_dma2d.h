/**
  **********************************************************************************************************************
  * @file    stm32u5xx_ll_dma2d.h
  * @brief   Header file of DMA2D LL module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2021-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_LL_DMA2D_H
#define STM32U5XX_LL_DMA2D_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined (DMA2D)

/** @defgroup DMA2D_LL DMA2D
  * @{
  */

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private constants -------------------------------------------------------------------------------------------------*/
/* Private macros ----------------------------------------------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup DMA2D_LL_Exported_Constants DMA2D Exported Constants
  * @{
  */

/** @defgroup DMA2D_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_DMA2D_READ_REG function
  * @{
  */
#define LL_DMA2D_FLAG_CEIF          DMA2D_ISR_CEIF                         /*!< Configuration Error Interrupt Flag */
#define LL_DMA2D_FLAG_CTCIF         DMA2D_ISR_CTCIF                        /*!< CLUT Transfer Complete Interrupt Flag */
#define LL_DMA2D_FLAG_CAEIF         DMA2D_ISR_CAEIF                        /*!< CLUT Access Error Interrupt Flag */
#define LL_DMA2D_FLAG_TWIF          DMA2D_ISR_TWIF                         /*!< Transfer Watermark Interrupt Flag */
#define LL_DMA2D_FLAG_TCIF          DMA2D_ISR_TCIF                         /*!< Transfer Complete Interrupt Flag */
#define LL_DMA2D_FLAG_TEIF          DMA2D_ISR_TEIF                         /*!< Transfer Error Interrupt Flag */
#define LL_DMA2D_FLAG_ALL           (DMA2D_ISR_CEIF | DMA2D_ISR_CTCIF   \
                                     | DMA2D_ISR_CAEIF | DMA2D_ISR_TWIF \
                                     | DMA2D_ISR_TCIF | DMA2D_ISR_TEIF)    /*!< All flag */
/**
  * @}
  */

/** @defgroup DMA2D_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_DMA2D_READ_REG and  LL_DMA2D_WRITE_REG functions
  * @{
  */
#define LL_DMA2D_IT_CEIE             DMA2D_CR_CEIE    /*!< Configuration Error Interrupt */
#define LL_DMA2D_IT_CTCIE            DMA2D_CR_CTCIE   /*!< CLUT Transfer Complete Interrupt */
#define LL_DMA2D_IT_CAEIE            DMA2D_CR_CAEIE   /*!< CLUT Access Error Interrupt */
#define LL_DMA2D_IT_TWIE             DMA2D_CR_TWIE    /*!< Transfer Watermark Interrupt */
#define LL_DMA2D_IT_TCIE             DMA2D_CR_TCIE    /*!< Transfer Complete Interrupt */
#define LL_DMA2D_IT_TEIE             DMA2D_CR_TEIE    /*!< Transfer Error Interrupt */
/**
  * @}
  */

/** @defgroup DMA2D_LL_EC_MODE Mode
  * @{
  */
#define LL_DMA2D_MODE_M2M                       0x00000000U         /*!< DMA2D memory to memory transfer mode     */
#define LL_DMA2D_MODE_M2M_PFC                   DMA2D_CR_MODE_0     /*!< DMA2D memory to memory with pixel format 
                                                                         conversion transfer mode                 */
#define LL_DMA2D_MODE_M2M_BLEND                 DMA2D_CR_MODE_1     /*!< DMA2D memory to memory with blending transfer
                                                                         mode                                         */
#define LL_DMA2D_MODE_R2M                       (DMA2D_CR_MODE_0 \
                                                 | DMA2D_CR_MODE_1) /*!< DMA2D register to memory transfer mode */
#define LL_DMA2D_MODE_M2M_BLEND_FIXED_COLOR_FG  DMA2D_CR_MODE_2     /*!< DMA2D memory to memory with blending transfer 
                                                                         mode and fixed color foreground              */
#define LL_DMA2D_MODE_M2M_BLEND_FIXED_COLOR_BG  (DMA2D_CR_MODE_0 \
                                                 | DMA2D_CR_MODE_2) /*!< DMA2D memory to memory with blending transfer
                                                                         mode and fixed color background              */
/**
  * @}
  */

/** @defgroup DMA2D_LL_EC_OUTPUT_COLOR_MODE Output Color Mode
  * @{
  */
#define LL_DMA2D_OUTPUT_MODE_ARGB8888     0x00000000U                             /*!< ARGB8888 */
#define LL_DMA2D_OUTPUT_MODE_RGB888       DMA2D_OPFCCR_CM_0                       /*!< RGB888   */
#define LL_DMA2D_OUTPUT_MODE_RGB565       DMA2D_OPFCCR_CM_1                       /*!< RGB565   */
#define LL_DMA2D_OUTPUT_MODE_ARGB1555     (DMA2D_OPFCCR_CM_0 | DMA2D_OPFCCR_CM_1) /*!< ARGB1555 */
#define LL_DMA2D_OUTPUT_MODE_ARGB4444     DMA2D_OPFCCR_CM_2                       /*!< ARGB4444 */
/**
  * @}
  */

/** @defgroup DMA2D_LL_EC_INPUT_COLOR_MODE Input Color Mode
  * @{
  */
#define LL_DMA2D_INPUT_MODE_ARGB8888     0x00000000U                                                    /*!< ARGB8888 */
#define LL_DMA2D_INPUT_MODE_RGB888       DMA2D_FGPFCCR_CM_0                                             /*!< RGB888   */
#define LL_DMA2D_INPUT_MODE_RGB565       DMA2D_FGPFCCR_CM_1                                             /*!< RGB565   */
#define LL_DMA2D_INPUT_MODE_ARGB1555     (DMA2D_FGPFCCR_CM_0 | DMA2D_FGPFCCR_CM_1)                      /*!< ARGB1555 */
#define LL_DMA2D_INPUT_MODE_ARGB4444     DMA2D_FGPFCCR_CM_2                                             /*!< ARGB4444 */
#define LL_DMA2D_INPUT_MODE_L8           (DMA2D_FGPFCCR_CM_0 | DMA2D_FGPFCCR_CM_2)                      /*!< L8       */
#define LL_DMA2D_INPUT_MODE_AL44         (DMA2D_FGPFCCR_CM_1 | DMA2D_FGPFCCR_CM_2)                      /*!< AL44     */
#define LL_DMA2D_INPUT_MODE_AL88         (DMA2D_FGPFCCR_CM_0 | DMA2D_FGPFCCR_CM_1 | DMA2D_FGPFCCR_CM_2) /*!< AL88     */
#define LL_DMA2D_INPUT_MODE_L4           DMA2D_FGPFCCR_CM_3                                             /*!< L4       */
#define LL_DMA2D_INPUT_MODE_A8           (DMA2D_FGPFCCR_CM_0 | DMA2D_FGPFCCR_CM_3)                      /*!< A8       */
#define LL_DMA2D_INPUT_MODE_A4           (DMA2D_FGPFCCR_CM_1 | DMA2D_FGPFCCR_CM_3)                      /*!< A4       */
#if defined(DMA2D_FGPFCCR_CSS)
#define LL_DMA2D_INPUT_MODE_YCBCR        (DMA2D_FGPFCCR_CM_0 | DMA2D_FGPFCCR_CM_1 | DMA2D_FGPFCCR_CM_3) /*!< YCbCr    */
#endif /* DMA2D_FGPFCCR_CSS */
/**
  * @}
  */

/** @defgroup DMA2D_LL_EC_ALPHA_MODE Alpha Mode
  * @{
  */
#define LL_DMA2D_ALPHA_MODE_NO_MODIF       0x00000000U             /*!< No modification of the alpha channel value */
#define LL_DMA2D_ALPHA_MODE_REPLACE        DMA2D_FGPFCCR_AM_0      /*!< Replace original alpha channel value by
                                                                        programmed alpha value                     */
#define LL_DMA2D_ALPHA_MODE_COMBINE        DMA2D_FGPFCCR_AM_1      /*!< Replace original alpha channel value by
                                                                        programmed alpha value with,
                                                                        original alpha channel value               */
/**
  * @}
  */

/** @defgroup DMA2D_LL_EC_OUTPUT_SWAP_MODE Swap Mode
  * @{
  */
#define LL_DMA2D_SWAP_MODE_REGULAR        0x00000000U                      /*!< Regular order */
#define LL_DMA2D_SWAP_MODE_TWO_BY_TWO     DMA2D_OPFCCR_SB                  /*!< Bytes swapped two by two */
/**
  * @}
  */

/** @defgroup DMA2D_LL_EC_RED_BLUE_SWAP Red Blue Swap
  * @{
  */
#define LL_DMA2D_RB_MODE_REGULAR          0x00000000U                      /*!< RGB or ARGB */
#define LL_DMA2D_RB_MODE_SWAP             DMA2D_FGPFCCR_RBS                /*!< BGR or ABGR */
/**
  * @}
  */

/** @defgroup DMA2D_LL_EC_ALPHA_INVERSION Alpha Inversion
  * @{
  */
#define LL_DMA2D_ALPHA_REGULAR          0x00000000U                     /*!< Regular alpha  */
#define LL_DMA2D_ALPHA_INVERTED         DMA2D_FGPFCCR_AI                /*!< Inverted alpha */
/**
  * @}
  */


/** @defgroup DMA2D_LL_EC_LINE_OFFSET_MODE Line Offset Mode
  * @{
  */
#define LL_DMA2D_LINE_OFFSET_PIXELS     0x00000000U                     /*!< Line offsets are expressed in pixels  */
#define LL_DMA2D_LINE_OFFSET_BYTES      DMA2D_CR_LOM                    /*!< Line offsets are expressed in bytes   */
/**
  * @}
  */

/** @defgroup DMA2D_LL_EC_CLUT_COLOR_MODE CLUT Color Mode
  * @{
  */
#define LL_DMA2D_CLUT_COLOR_MODE_ARGB8888          0x00000000U                     /*!< ARGB8888 */
#define LL_DMA2D_CLUT_COLOR_MODE_RGB888            DMA2D_FGPFCCR_CCM               /*!< RGB888   */
/**
  * @}
  */

#if defined(DMA2D_FGPFCCR_CSS)
/** @defgroup DMA2D_LL_CHROMA_SUB_SAMPLING Chroma Sub Sampling
  * @{
  */
#define LL_DMA2D_CSS_444              0x00000000U             /*!< No chroma sub-sampling 4:4:4 */
#define LL_DMA2D_CSS_422              DMA2D_FGPFCCR_CSS_0     /*!< chroma sub-sampling 4:2:2 */
#define LL_DMA2D_CSS_420              DMA2D_FGPFCCR_CSS_1     /*!< chroma sub-sampling 4:2:0 */
/**
  * @}
  */
#endif /* DMA2D_FGPFCCR_CSS */

/**
  * @}
  */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/** @defgroup DMA2D_LL_Exported_Macros DMA2D Exported Macros
  * @{
  */

/** @defgroup DMA2D_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in DMA2D register.
  * @param  instance DMA2D Instance
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_DMA2D_WRITE_REG(instance, reg, value) WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in DMA2D register.
  * @param  instance DMA2D Instance
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_DMA2D_READ_REG(instance, reg) READ_REG((instance)->reg)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup DMA2D_LL_Exported_Functions DMA2D Exported Functions
  * @{
  */

/** @defgroup DMA2D_LL_EF_Configuration Configuration Functions
  * @{
  */

/**
  * @brief  Start a DMA2D transfer.
  * @rmtoll
  *  CR          START            LL_DMA2D_Start
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_Start(DMA2D_TypeDef *dma2dx)
{
  SET_BIT(dma2dx->CR, DMA2D_CR_START);
}

/**
  * @brief  Indicate if a DMA2D transfer is ongoing.
  * @rmtoll
  *  CR          START            LL_DMA2D_IsTransferOngoing
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsTransferOngoing(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->CR, DMA2D_CR_START) == (DMA2D_CR_START)) ? 1UL : 0UL);
}

/**
  * @brief  Suspend DMA2D transfer.
  * @rmtoll
  *  CR          SUSP            LL_DMA2D_Suspend
  * @param  dma2dx DMA2D Instance
  * @note   This API can be used to suspend automatic foreground or background CLUT loading.
  */
__STATIC_INLINE void LL_DMA2D_Suspend(DMA2D_TypeDef *dma2dx)
{
  MODIFY_REG(dma2dx->CR, DMA2D_CR_SUSP | DMA2D_CR_START, DMA2D_CR_SUSP);
}

/**
  * @brief  Resume DMA2D transfer.
  * @rmtoll
  *  CR          SUSP            LL_DMA2D_Resume
  * @param  dma2dx DMA2D Instance
  * @note   This API can be used to resume automatic foreground or background CLUT loading.
  */
__STATIC_INLINE void LL_DMA2D_Resume(DMA2D_TypeDef *dma2dx)
{
  CLEAR_BIT(dma2dx->CR, DMA2D_CR_SUSP | DMA2D_CR_START);
}

/**
  * @brief  Indicate if DMA2D transfer is suspended.
  *         background CLUT loading is suspended.
  * @rmtoll
  *  CR          SUSP            LL_DMA2D_IsSuspended
  * @param  dma2dx DMA2D Instance
  * @note   This API can be used to indicate whether or not automatic foreground or
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsSuspended(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->CR, DMA2D_CR_SUSP) == (DMA2D_CR_SUSP)) ? 1UL : 0UL);
}

/**
  * @brief  Abort DMA2D transfer.
  * @rmtoll
  *  CR          ABORT            LL_DMA2D_Abort
  * @param  dma2dx DMA2D Instance
  * @note   This API can be used to abort automatic foreground or background CLUT loading.
  */
__STATIC_INLINE void LL_DMA2D_Abort(DMA2D_TypeDef *dma2dx)
{
  MODIFY_REG(dma2dx->CR, DMA2D_CR_ABORT | DMA2D_CR_START, DMA2D_CR_ABORT);
}

/**
  * @brief  Indicate if DMA2D transfer is aborted.
  * @rmtoll
  *  CR          ABORT            LL_DMA2D_IsAborted
  * @param  dma2dx DMA2D Instance
  * @note   This API can be used to indicate whether or not automatic foreground or
  *         background CLUT loading is aborted.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsAborted(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->CR, DMA2D_CR_ABORT) == (DMA2D_CR_ABORT)) ? 1UL : 0UL);
}

/**
  * @brief  Set DMA2D mode.
  * @rmtoll
  *  CR          MODE          LL_DMA2D_SetMode
  * @param  dma2dx DMA2D Instance
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_MODE_M2M
  *         @arg @ref LL_DMA2D_MODE_M2M_PFC
  *         @arg @ref LL_DMA2D_MODE_M2M_BLEND
  *         @arg @ref LL_DMA2D_MODE_R2M
  *         @arg @ref LL_DMA2D_MODE_M2M_BLEND_FIXED_COLOR_FG
  *         @arg @ref LL_DMA2D_MODE_M2M_BLEND_FIXED_COLOR_BG
  */
__STATIC_INLINE void LL_DMA2D_SetMode(DMA2D_TypeDef *dma2dx, uint32_t mode)
{
  MODIFY_REG(dma2dx->CR, DMA2D_CR_MODE, mode);
}

/**
  * @brief  Return DMA2D mode
  * @rmtoll
  *  CR          MODE         LL_DMA2D_GetMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_MODE_M2M
  *         @arg @ref LL_DMA2D_MODE_M2M_PFC
  *         @arg @ref LL_DMA2D_MODE_M2M_BLEND
  *         @arg @ref LL_DMA2D_MODE_R2M
  *         @arg @ref LL_DMA2D_MODE_M2M_BLEND_FIXED_COLOR_FG
  *         @arg @ref LL_DMA2D_MODE_M2M_BLEND_FIXED_COLOR_BG
  */
__STATIC_INLINE uint32_t LL_DMA2D_GetMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->CR, DMA2D_CR_MODE));
}

/**
  * @brief  Set DMA2D output color mode.
  * @rmtoll
  *  OPFCCR          CM          LL_DMA2D_SetOutputColorMode
  * @param  dma2dx DMA2D Instance
  * @param  color_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_OUTPUT_MODE_ARGB8888
  *         @arg @ref LL_DMA2D_OUTPUT_MODE_RGB888
  *         @arg @ref LL_DMA2D_OUTPUT_MODE_RGB565
  *         @arg @ref LL_DMA2D_OUTPUT_MODE_ARGB1555
  *         @arg @ref LL_DMA2D_OUTPUT_MODE_ARGB4444
  */
__STATIC_INLINE void LL_DMA2D_SetOutputColorMode(DMA2D_TypeDef *dma2dx, uint32_t color_mode)
{
  MODIFY_REG(dma2dx->OPFCCR, DMA2D_OPFCCR_CM, color_mode);
}

/**
  * @brief  Return DMA2D output color mode.
  * @rmtoll
  *  OPFCCR          CM         LL_DMA2D_GetOutputColorMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_OUTPUT_MODE_ARGB8888
  *         @arg @ref LL_DMA2D_OUTPUT_MODE_RGB888
  *         @arg @ref LL_DMA2D_OUTPUT_MODE_RGB565
  *         @arg @ref LL_DMA2D_OUTPUT_MODE_ARGB1555
  *         @arg @ref LL_DMA2D_OUTPUT_MODE_ARGB4444
  */
__STATIC_INLINE uint32_t LL_DMA2D_GetOutputColorMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->OPFCCR, DMA2D_OPFCCR_CM));
}

/**
  * @brief  Set DMA2D output Red Blue swap mode.
  * @rmtoll
  *  OPFCCR          RBS          LL_DMA2D_SetOutputRBSwapMode
  * @param  dma2dx DMA2D Instance
  * @param  rb_swap_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_RB_MODE_REGULAR
  *         @arg @ref LL_DMA2D_RB_MODE_SWAP
  */
__STATIC_INLINE void LL_DMA2D_SetOutputRBSwapMode(DMA2D_TypeDef *dma2dx, uint32_t rb_swap_mode)
{
  MODIFY_REG(dma2dx->OPFCCR, DMA2D_OPFCCR_RBS, rb_swap_mode);
}

/**
  * @brief  Return DMA2D output Red Blue swap mode.
  * @rmtoll
  *  OPFCCR          RBS         LL_DMA2D_GetOutputRBSwapMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_RB_MODE_REGULAR
  *         @arg @ref LL_DMA2D_RB_MODE_SWAP
  */
__STATIC_INLINE uint32_t LL_DMA2D_GetOutputRBSwapMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->OPFCCR, DMA2D_OPFCCR_RBS));
}

/**
  * @brief  Set DMA2D output alpha inversion mode.
  * @rmtoll
  *  OPFCCR          AI          LL_DMA2D_SetOutputAlphaInvMode
  * @param  dma2dx DMA2D Instance
  * @param  alpha_inversion_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_ALPHA_REGULAR
  *         @arg @ref LL_DMA2D_ALPHA_INVERTED
  */
__STATIC_INLINE void LL_DMA2D_SetOutputAlphaInvMode(DMA2D_TypeDef *dma2dx, uint32_t alpha_inversion_mode)
{
  MODIFY_REG(dma2dx->OPFCCR, DMA2D_OPFCCR_AI, alpha_inversion_mode);
}

/**
  * @brief  Return DMA2D output alpha inversion mode.
  * @rmtoll
  *  OPFCCR          AI         LL_DMA2D_GetOutputAlphaInvMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_ALPHA_REGULAR
  *         @arg @ref LL_DMA2D_ALPHA_INVERTED
  */
__STATIC_INLINE uint32_t LL_DMA2D_GetOutputAlphaInvMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->OPFCCR, DMA2D_OPFCCR_AI));
}


/**
  * @brief  Set DMA2D output swap mode.
  * @rmtoll
  *  OPFCCR          SB          LL_DMA2D_SetOutputSwapMode
  * @param  dma2dx DMA2D Instance
  * @param  output_swap_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_SWAP_MODE_REGULAR
  *         @arg @ref LL_DMA2D_SWAP_MODE_TWO_BY_TWO
  */
__STATIC_INLINE void LL_DMA2D_SetOutputSwapMode(DMA2D_TypeDef *dma2dx, uint32_t output_swap_mode)
{
  MODIFY_REG(dma2dx->OPFCCR, DMA2D_OPFCCR_SB, output_swap_mode);
}

/**
  * @brief  Return DMA2D output swap mode.
  * @rmtoll
  *  OPFCCR          SB         LL_DMA2D_GetOutputSwapMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_SWAP_MODE_REGULAR
  *         @arg @ref LL_DMA2D_SWAP_MODE_TWO_BY_TWO
  */
__STATIC_INLINE uint32_t LL_DMA2D_GetOutputSwapMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->OPFCCR, DMA2D_OPFCCR_SB));
}

/**
  * @brief  Set DMA2D line offset mode.
  * @rmtoll
  *  CR          LOM          LL_DMA2D_SetLineOffsetMode
  * @param  dma2dx DMA2D Instance
  * @param  line_offset_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_LINE_OFFSET_PIXELS
  *         @arg @ref LL_DMA2D_LINE_OFFSET_BYTES
  */
__STATIC_INLINE void LL_DMA2D_SetLineOffsetMode(DMA2D_TypeDef *dma2dx, uint32_t line_offset_mode)
{
  MODIFY_REG(dma2dx->CR, DMA2D_CR_LOM, line_offset_mode);
}

/**
  * @brief  Return DMA2D line offset mode.
  * @rmtoll
  *  CR          LOM         LL_DMA2D_GetLineOffsetMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_LINE_OFFSET_PIXELS
  *         @arg @ref LL_DMA2D_LINE_OFFSET_BYTES
  */
__STATIC_INLINE uint32_t LL_DMA2D_GetLineOffsetMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->CR, DMA2D_CR_LOM));
}

/**
  * @brief  Set DMA2D line offset.
  * @rmtoll
  *  OOR          LO          LL_DMA2D_SetLineOffset
  * @param  dma2dx DMA2D Instance
  * @param  line_offset Value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE void LL_DMA2D_SetLineOffset(DMA2D_TypeDef *dma2dx, uint32_t line_offset)
{
  MODIFY_REG(dma2dx->OOR, DMA2D_OOR_LO, line_offset);
}

/**
  * @brief  Return DMA2D line offset.
  * @rmtoll
  *  OOR          LO         LL_DMA2D_GetLineOffset
  * @param  dma2dx DMA2D Instance
  * @retval Line offset value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_GetLineOffset(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->OOR, DMA2D_OOR_LO));
}

/**
  * @brief  Set DMA2D number of pixels per lines, expressed on 14 bits ([13:0] bits),
  *         and number of lines, expressed on 16 bits ([15:0] bits).
  * @rmtoll
  *  NLR          PL          LL_DMA2D_ConfigAreaSize \n
  *  NLR          NL          LL_DMA2D_ConfigAreaSize
  * @param  dma2dx DMA2D Instance
  * @param  nbr_of_pixels_per_lines Value between Min_Data=0 and Max_Data=0x3FFF
  * @param  nbr_of_lines Value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE void LL_DMA2D_ConfigAreaSize(DMA2D_TypeDef *dma2dx, uint32_t nbr_of_pixels_per_lines,
                                             uint32_t nbr_of_lines)
{
  WRITE_REG(dma2dx->NLR, nbr_of_lines | (nbr_of_pixels_per_lines << DMA2D_NLR_PL_Pos));
}

/**
  * @brief  Set DMA2D number of pixels per lines, expressed on 14 bits ([13:0] bits).
  * @rmtoll
  *  NLR          PL          LL_DMA2D_SetNbrOfPixelsPerLines
  * @param  dma2dx DMA2D Instance
  * @param  nbr_of_pixels_per_lines Value between Min_Data=0 and Max_Data=0x3FFF
  */
__STATIC_INLINE void LL_DMA2D_SetNbrOfPixelsPerLines(DMA2D_TypeDef *dma2dx, uint32_t nbr_of_pixels_per_lines)
{
  MODIFY_REG(dma2dx->NLR, DMA2D_NLR_PL, (nbr_of_pixels_per_lines << DMA2D_NLR_PL_Pos));
}

/**
  * @brief  Return DMA2D number of pixels per lines, expressed on 14 bits ([13:0] bits)
  * @rmtoll
  *  NLR          PL          LL_DMA2D_GetNbrOfPixelsPerLines
  * @param  dma2dx DMA2D Instance
  * @retval Number of pixels per lines value between Min_Data=0 and Max_Data=0x3FFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_GetNbrOfPixelsPerLines(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->NLR, DMA2D_NLR_PL) >> DMA2D_NLR_PL_Pos);
}

/**
  * @brief  Set DMA2D number of lines, expressed on 16 bits ([15:0] bits).
  * @rmtoll
  *  NLR          NL          LL_DMA2D_SetNbrOfLines
  * @param  dma2dx DMA2D Instance
  * @param  nbr_of_lines Value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE void LL_DMA2D_SetNbrOfLines(DMA2D_TypeDef *dma2dx, uint32_t nbr_of_lines)
{
  MODIFY_REG(dma2dx->NLR, DMA2D_NLR_NL, nbr_of_lines);
}

/**
  * @brief  Return DMA2D number of lines, expressed on 16 bits ([15:0] bits).
  * @rmtoll
  *  NLR          NL          LL_DMA2D_GetNbrOfLines
  * @param  dma2dx DMA2D Instance
  * @retval Number of lines value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_GetNbrOfLines(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->NLR, DMA2D_NLR_NL));
}

/**
  * @brief  Set DMA2D output memory address, expressed on 32 bits ([31:0] bits).
  * @rmtoll
  *  OMAR          MA          LL_DMA2D_SetOutputMemAddr
  * @param  dma2dx DMA2D Instance
  * @param  output_memory_address Value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE void LL_DMA2D_SetOutputMemAddr(DMA2D_TypeDef *dma2dx, uint32_t output_memory_address)
{
  WRITE_REG(dma2dx->OMAR, output_memory_address);
}

/**
  * @brief  Get DMA2D output memory address, expressed on 32 bits ([31:0] bits).
  * @rmtoll
  *  OMAR          MA          LL_DMA2D_GetOutputMemAddr
  * @param  dma2dx DMA2D Instance
  * @retval Output memory address value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_GetOutputMemAddr(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_REG(dma2dx->OMAR));
}

/**
  * @brief  Set DMA2D output color, expressed on 32 bits ([31:0] bits).
  * @param  dma2dx DMA2D Instance
  * @param  output_color Value between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @note   Output color format depends on output color mode, ARGB8888, RGB888,
  *         RGB565, ARGB1555 or ARGB4444.
  */
__STATIC_INLINE void LL_DMA2D_SetOutputColor(DMA2D_TypeDef *dma2dx, uint32_t output_color)
{
  WRITE_REG(dma2dx->OCOLR, output_color);
}

/**
  * @brief  Get DMA2D output color, expressed on 32 bits ([31:0] bits).
  * @rmtoll
  *  OCOLR        BLUE        LL_DMA2D_GetOutputColor \n
  *  OCOLR        GREEN       LL_DMA2D_GetOutputColor \n
  *  OCOLR        RED         LL_DMA2D_GetOutputColor \n
  *  OCOLR        ALPHA       LL_DMA2D_GetOutputColor
  * @param  dma2dx DMA2D Instance
  * @note   Alpha channel and red, green, blue color values must be retrieved from the returned
  *         value based on the output color mode (ARGB8888, RGB888,  RGB565, ARGB1555 or ARGB4444)
  *         as set by @ref LL_DMA2D_SetOutputColorMode.
  * @retval Output color value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_GetOutputColor(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->OCOLR, \
                             (DMA2D_OCOLR_BLUE_1 | DMA2D_OCOLR_GREEN_1 | DMA2D_OCOLR_RED_1 | DMA2D_OCOLR_ALPHA_1)));
}

/**
  * @brief  Set DMA2D line watermark, expressed on 16 bits ([15:0] bits).
  * @rmtoll
  *  LWR          LW          LL_DMA2D_SetLineWatermark
  * @param  dma2dx DMA2D Instance
  * @param  line_watermark Value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE void LL_DMA2D_SetLineWatermark(DMA2D_TypeDef *dma2dx, uint32_t line_watermark)
{
  MODIFY_REG(dma2dx->LWR, DMA2D_LWR_LW, line_watermark);
}

/**
  * @brief  Return DMA2D line watermark, expressed on 16 bits ([15:0] bits).
  * @rmtoll
  *  LWR          LW          LL_DMA2D_GetLineWatermark
  * @param  dma2dx DMA2D Instance
  * @retval Line watermark value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_GetLineWatermark(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->LWR, DMA2D_LWR_LW));
}

/**
  * @brief  Set DMA2D dead time, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  AMTCR          DT          LL_DMA2D_SetDeadTime
  * @param  dma2dx DMA2D Instance
  * @param  dead_time Value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_DMA2D_SetDeadTime(DMA2D_TypeDef *dma2dx, uint32_t dead_time)
{
  MODIFY_REG(dma2dx->AMTCR, DMA2D_AMTCR_DT, (dead_time << DMA2D_AMTCR_DT_Pos));
}

/**
  * @brief  Return DMA2D dead time, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  AMTCR          DT          LL_DMA2D_GetDeadTime
  * @param  dma2dx DMA2D Instance
  * @retval Dead time value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_GetDeadTime(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->AMTCR, DMA2D_AMTCR_DT) >> DMA2D_AMTCR_DT_Pos);
}

/**
  * @brief  Enable DMA2D dead time functionality.
  * @rmtoll
  *  AMTCR          EN            LL_DMA2D_EnableDeadTime
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_EnableDeadTime(DMA2D_TypeDef *dma2dx)
{
  SET_BIT(dma2dx->AMTCR, DMA2D_AMTCR_EN);
}

/**
  * @brief  Disable DMA2D dead time functionality.
  * @rmtoll
  *  AMTCR          EN            LL_DMA2D_DisableDeadTime
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_DisableDeadTime(DMA2D_TypeDef *dma2dx)
{
  CLEAR_BIT(dma2dx->AMTCR, DMA2D_AMTCR_EN);
}

/**
  * @brief  Indicate if DMA2D dead time functionality is enabled.
  * @rmtoll
  *  AMTCR          EN            LL_DMA2D_IsEnabledDeadTime
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsEnabledDeadTime(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->AMTCR, DMA2D_AMTCR_EN) == (DMA2D_AMTCR_EN)) ? 1UL : 0UL);
}

/** @defgroup DMA2D_LL_EF_FGND_Configuration Foreground Configuration Functions
  * @{
  */

/**
  * @brief  Set DMA2D foreground memory address, expressed on 32 bits ([31:0] bits).
  * @rmtoll
  *  FGMAR          MA          LL_DMA2D_FGND_SetMemAddr
  * @param  dma2dx DMA2D Instance
  * @param  memory_address Value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetMemAddr(DMA2D_TypeDef *dma2dx, uint32_t memory_address)
{
  WRITE_REG(dma2dx->FGMAR, memory_address);
}

/**
  * @brief  Get DMA2D foreground memory address, expressed on 32 bits ([31:0] bits).
  * @rmtoll
  *  FGMAR          MA          LL_DMA2D_FGND_GetMemAddr
  * @param  dma2dx DMA2D Instance
  * @retval Foreground memory address value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_GetMemAddr(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_REG(dma2dx->FGMAR));
}

/**
  * @brief  Enable DMA2D foreground CLUT loading.
  * @rmtoll
  *  FGPFCCR          START            LL_DMA2D_FGND_EnableCLUTLoad
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_FGND_EnableCLUTLoad(DMA2D_TypeDef *dma2dx)
{
  SET_BIT(dma2dx->FGPFCCR, DMA2D_FGPFCCR_START);
}

/**
  * @brief  Indicate if DMA2D foreground CLUT loading is enabled.
  * @rmtoll
  *  FGPFCCR          START            LL_DMA2D_FGND_IsEnabledCLUTLoad
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_IsEnabledCLUTLoad(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->FGPFCCR, DMA2D_FGPFCCR_START) == (DMA2D_FGPFCCR_START)) ? 1UL : 0UL);
}

/**
  * @brief  Set DMA2D foreground color mode.
  * @rmtoll
  *  FGPFCCR          CM          LL_DMA2D_FGND_SetColorMode
  * @param  dma2dx DMA2D Instance
  * @param  color_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB8888
  *         @arg @ref LL_DMA2D_INPUT_MODE_RGB888
  *         @arg @ref LL_DMA2D_INPUT_MODE_RGB565
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB1555
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB4444
  *         @arg @ref LL_DMA2D_INPUT_MODE_L8
  *         @arg @ref LL_DMA2D_INPUT_MODE_AL44
  *         @arg @ref LL_DMA2D_INPUT_MODE_AL88
  *         @arg @ref LL_DMA2D_INPUT_MODE_L4
  *         @arg @ref LL_DMA2D_INPUT_MODE_A8
  *         @arg @ref LL_DMA2D_INPUT_MODE_A4
  * @if DMA2D_FGPFCCR_CSS
  *         @arg @ref LL_DMA2D_INPUT_MODE_YCBCR (*)
  * @endif
  *         @note     (*)not available on all devices
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetColorMode(DMA2D_TypeDef *dma2dx, uint32_t color_mode)
{
  MODIFY_REG(dma2dx->FGPFCCR, DMA2D_FGPFCCR_CM, color_mode);
}

/**
  * @brief  Return DMA2D foreground color mode.
  * @rmtoll
  *  FGPFCCR          CM         LL_DMA2D_FGND_GetColorMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB8888
  *         @arg @ref LL_DMA2D_INPUT_MODE_RGB888
  *         @arg @ref LL_DMA2D_INPUT_MODE_RGB565
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB1555
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB4444
  *         @arg @ref LL_DMA2D_INPUT_MODE_L8
  *         @arg @ref LL_DMA2D_INPUT_MODE_AL44
  *         @arg @ref LL_DMA2D_INPUT_MODE_AL88
  *         @arg @ref LL_DMA2D_INPUT_MODE_L4
  *         @arg @ref LL_DMA2D_INPUT_MODE_A8
  *         @arg @ref LL_DMA2D_INPUT_MODE_A4
  * @if DMA2D_FGPFCCR_CSS
  *         @arg @ref LL_DMA2D_INPUT_MODE_YCBCR (*)
  * @endif
  *         @note     (*)not available on all devices
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_GetColorMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->FGPFCCR, DMA2D_FGPFCCR_CM));
}

/**
  * @brief  Set DMA2D foreground alpha mode.
  * @rmtoll
  *  FGPFCCR          AM          LL_DMA2D_FGND_SetAlphaMode
  * @param  dma2dx DMA2D Instance
  * @param  alpha_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_ALPHA_MODE_NO_MODIF
  *         @arg @ref LL_DMA2D_ALPHA_MODE_REPLACE
  *         @arg @ref LL_DMA2D_ALPHA_MODE_COMBINE
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetAlphaMode(DMA2D_TypeDef *dma2dx, uint32_t alpha_mode)
{
  MODIFY_REG(dma2dx->FGPFCCR, DMA2D_FGPFCCR_AM, alpha_mode);
}

/**
  * @brief  Return DMA2D foreground alpha mode.
  * @rmtoll
  *  FGPFCCR          AM         LL_DMA2D_FGND_GetAlphaMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_ALPHA_MODE_NO_MODIF
  *         @arg @ref LL_DMA2D_ALPHA_MODE_REPLACE
  *         @arg @ref LL_DMA2D_ALPHA_MODE_COMBINE
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_GetAlphaMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->FGPFCCR, DMA2D_FGPFCCR_AM));
}

/**
  * @brief  Set DMA2D foreground alpha value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  FGPFCCR          ALPHA          LL_DMA2D_FGND_SetAlpha
  * @param  dma2dx DMA2D Instance
  * @param  alpha Value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetAlpha(DMA2D_TypeDef *dma2dx, uint32_t alpha)
{
  MODIFY_REG(dma2dx->FGPFCCR, DMA2D_FGPFCCR_ALPHA, (alpha << DMA2D_FGPFCCR_ALPHA_Pos));
}

/**
  * @brief  Return DMA2D foreground alpha value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  FGPFCCR          ALPHA         LL_DMA2D_FGND_GetAlpha
  * @param  dma2dx DMA2D Instance
  * @retval Alpha value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_GetAlpha(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->FGPFCCR, DMA2D_FGPFCCR_ALPHA) >> DMA2D_FGPFCCR_ALPHA_Pos);
}

/**
  * @brief  Set DMA2D foreground input color mode, input alpha mode, and input alpha value
  * @rmtoll
  *  FGPFCCR          CM         LL_DMA2D_FGND_SetARGBMode \n
  *  FGPFCCR          ALPHA      LL_DMA2D_FGND_SetARGBMode \n
  *  FGPFCCR          AM         LL_DMA2D_FGND_SetARGBMode
  * @param  dma2dx DMA2D Instance
  * @param  color_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB8888
  *         @arg @ref LL_DMA2D_INPUT_MODE_RGB888
  *         @arg @ref LL_DMA2D_INPUT_MODE_RGB565
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB1555
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB4444
  *         @arg @ref LL_DMA2D_INPUT_MODE_L8
  *         @arg @ref LL_DMA2D_INPUT_MODE_AL44
  *         @arg @ref LL_DMA2D_INPUT_MODE_AL88
  *         @arg @ref LL_DMA2D_INPUT_MODE_L4
  *         @arg @ref LL_DMA2D_INPUT_MODE_A8
  *         @arg @ref LL_DMA2D_INPUT_MODE_A4
  * @if DMA2D_FGPFCCR_CSS
  *         @arg @ref LL_DMA2D_INPUT_MODE_YCBCR (*)
  * @endif
  * @param  alpha_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_ALPHA_MODE_NO_MODIF
  *         @arg @ref LL_DMA2D_ALPHA_MODE_REPLACE
  *         @arg @ref LL_DMA2D_ALPHA_MODE_COMBINE
  * @param  alpha Value between Min_Data=0 and Max_Data=0xFF
  * @note   (*)not available on all devices
  */
#if defined(DMA2D_FGPFCCR_CSS)
__STATIC_INLINE void LL_DMA2D_FGND_SetARGBMode(DMA2D_TypeDef *dma2dx, uint32_t color_mode, \
                                               uint32_t alpha_mode, uint32_t alpha)
{
  MODIFY_REG(dma2dx->FGPFCCR, DMA2D_FGPFCCR_CM | DMA2D_FGPFCCR_AM | DMA2D_FGPFCCR_CSS | DMA2D_BGPFCCR_RBS \
             | DMA2D_FGPFCCR_ALPHA,  color_mode | alpha_mode | (alpha << DMA2D_FGPFCCR_ALPHA_Pos));
}
#else
__STATIC_INLINE void LL_DMA2D_FGND_SetARGBMode(DMA2D_TypeDef *dma2dx, uint32_t color_mode, \
                                               uint32_t alpha_mode, uint32_t alpha)
{
  MODIFY_REG(dma2dx->FGPFCCR, DMA2D_FGPFCCR_CM | DMA2D_FGPFCCR_AM | DMA2D_BGPFCCR_RBS | DMA2D_FGPFCCR_ALPHA, \
             color_mode | alpha_mode | (alpha << DMA2D_FGPFCCR_ALPHA_Pos));
}
#endif /* DMA2D_FGPFCCR_CSS  */

/**
  * @brief  Set DMA2D foreground Red Blue swap mode.
  * @rmtoll
  *  FGPFCCR          RBS          LL_DMA2D_FGND_SetRBSwapMode
  * @param  dma2dx DMA2D Instance
  * @param  rb_swap_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_RB_MODE_REGULAR
  *         @arg @ref LL_DMA2D_RB_MODE_SWAP
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetRBSwapMode(DMA2D_TypeDef *dma2dx, uint32_t rb_swap_mode)
{
  MODIFY_REG(dma2dx->FGPFCCR, DMA2D_FGPFCCR_RBS, rb_swap_mode);
}

/**
  * @brief  Return DMA2D foreground Red Blue swap mode.
  * @rmtoll
  *  FGPFCCR          RBS         LL_DMA2D_FGND_GetRBSwapMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_RB_MODE_REGULAR
  *         @arg @ref LL_DMA2D_RB_MODE_SWAP
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_GetRBSwapMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->FGPFCCR, DMA2D_FGPFCCR_RBS));
}

/**
  * @brief  Set DMA2D foreground alpha inversion mode.
  * @rmtoll
  *  FGPFCCR          AI          LL_DMA2D_FGND_SetAlphaInvMode
  * @param  dma2dx DMA2D Instance
  * @param  alpha_inversion_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_ALPHA_REGULAR
  *         @arg @ref LL_DMA2D_ALPHA_INVERTED
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetAlphaInvMode(DMA2D_TypeDef *dma2dx, uint32_t alpha_inversion_mode)
{
  MODIFY_REG(dma2dx->FGPFCCR, DMA2D_FGPFCCR_AI, alpha_inversion_mode);
}

/**
  * @brief  Return DMA2D foreground alpha inversion mode.
  * @rmtoll
  *  FGPFCCR          AI         LL_DMA2D_FGND_GetAlphaInvMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_ALPHA_REGULAR
  *         @arg @ref LL_DMA2D_ALPHA_INVERTED
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_GetAlphaInvMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->FGPFCCR, DMA2D_FGPFCCR_AI));
}

/**
  * @brief  Set DMA2D foreground line offset.
  * @rmtoll
  *  FGOR          LO          LL_DMA2D_FGND_SetLineOffset
  * @param  dma2dx DMA2D Instance
  * @param  line_offset Value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetLineOffset(DMA2D_TypeDef *dma2dx, uint32_t line_offset)
{
  MODIFY_REG(dma2dx->FGOR, DMA2D_FGOR_LO, line_offset);
}

/**
  * @brief  Return DMA2D foreground line offset.
  * @rmtoll
  *  FGOR          LO         LL_DMA2D_FGND_GetLineOffset
  * @param  dma2dx DMA2D Instance
  * @retval Foreground line offset value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_GetLineOffset(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->FGOR, DMA2D_FGOR_LO));
}

/**
  * @brief  Set DMA2D foreground color values, expressed on 24 bits ([23:0] bits).
  * @rmtoll
  *  FGCOLR          COLOR          LL_DMA2D_FGND_SetColor
  * @param  dma2dx DMA2D Instance
  * @param  color   Value between Min_Data=0 and Max_Data=0xFFFFFF
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetRGBColor(DMA2D_TypeDef *dma2dx, uint32_t color)
{
  WRITE_REG(dma2dx->FGCOLR, color);
}

/**
  * @brief  Set DMA2D foreground color values, expressed on 24 bits ([23:0] bits).
  * @rmtoll
  *  FGCOLR          RED          LL_DMA2D_FGND_SetColor \n
  *  FGCOLR          GREEN        LL_DMA2D_FGND_SetColor \n
  *  FGCOLR          BLUE         LL_DMA2D_FGND_SetColor
  * @param  dma2dx DMA2D Instance
  * @param  red   Value between Min_Data=0 and Max_Data=0xFF
  * @param  green Value between Min_Data=0 and Max_Data=0xFF
  * @param  blue  Value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetColor(DMA2D_TypeDef *dma2dx, uint32_t red, uint32_t green, uint32_t blue)
{
  MODIFY_REG(dma2dx->FGCOLR, (DMA2D_FGCOLR_RED | DMA2D_FGCOLR_GREEN | DMA2D_FGCOLR_BLUE), \
             ((red << DMA2D_FGCOLR_RED_Pos) | (green << DMA2D_FGCOLR_GREEN_Pos) | blue));
}

/**
  * @brief  Set DMA2D foreground red color value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  FGCOLR          RED          LL_DMA2D_FGND_SetRedColor
  * @param  dma2dx DMA2D Instance
  * @param  red Value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetRedColor(DMA2D_TypeDef *dma2dx, uint32_t red)
{
  MODIFY_REG(dma2dx->FGCOLR, DMA2D_FGCOLR_RED, (red << DMA2D_FGCOLR_RED_Pos));
}

/**
  * @brief  Return DMA2D foreground red color value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  FGCOLR          RED         LL_DMA2D_FGND_GetRedColor
  * @param  dma2dx DMA2D Instance
  * @retval Red color value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_GetRedColor(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->FGCOLR, DMA2D_FGCOLR_RED) >> DMA2D_FGCOLR_RED_Pos);
}

/**
  * @brief  Set DMA2D foreground green color value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  FGCOLR          GREEN          LL_DMA2D_FGND_SetGreenColor
  * @param  dma2dx DMA2D Instance
  * @param  green Value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetGreenColor(DMA2D_TypeDef *dma2dx, uint32_t green)
{
  MODIFY_REG(dma2dx->FGCOLR, DMA2D_FGCOLR_GREEN, (green << DMA2D_FGCOLR_GREEN_Pos));
}

/**
  * @brief  Return DMA2D foreground green color value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  FGCOLR          GREEN         LL_DMA2D_FGND_GetGreenColor
  * @param  dma2dx DMA2D Instance
  * @retval Green color value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_GetGreenColor(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->FGCOLR, DMA2D_FGCOLR_GREEN) >> DMA2D_FGCOLR_GREEN_Pos);
}

/**
  * @brief  Set DMA2D foreground blue color value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  FGCOLR          BLUE          LL_DMA2D_FGND_SetBlueColor
  * @param  dma2dx DMA2D Instance
  * @param  blue Value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetBlueColor(DMA2D_TypeDef *dma2dx, uint32_t blue)
{
  MODIFY_REG(dma2dx->FGCOLR, DMA2D_FGCOLR_BLUE, blue);
}

/**
  * @brief  Return DMA2D foreground blue color value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  FGCOLR          BLUE         LL_DMA2D_FGND_GetBlueColor
  * @param  dma2dx DMA2D Instance
  * @retval Blue color value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_GetBlueColor(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->FGCOLR, DMA2D_FGCOLR_BLUE));
}

/**
  * @brief  Set DMA2D foreground CLUT memory address, expressed on 32 bits ([31:0] bits).
  * @rmtoll
  *  FGCMAR          MA          LL_DMA2D_FGND_SetCLUTMemAddr
  * @param  dma2dx DMA2D Instance
  * @param  clut_memory_address Value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetCLUTMemAddr(DMA2D_TypeDef *dma2dx, uint32_t clut_memory_address)
{
  WRITE_REG(dma2dx->FGCMAR, clut_memory_address);
}

/**
  * @brief  Get DMA2D foreground CLUT memory address, expressed on 32 bits ([31:0] bits).
  * @rmtoll
  *  FGCMAR          MA          LL_DMA2D_FGND_GetCLUTMemAddr
  * @param  dma2dx DMA2D Instance
  * @retval Foreground CLUT memory address value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_GetCLUTMemAddr(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_REG(dma2dx->FGCMAR));
}

/**
  * @brief  Set DMA2D foreground CLUT size, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  FGPFCCR          CS          LL_DMA2D_FGND_SetCLUTSize
  * @param  dma2dx DMA2D Instance
  * @param  clut_size Value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetCLUTSize(DMA2D_TypeDef *dma2dx, uint32_t clut_size)
{
  MODIFY_REG(dma2dx->FGPFCCR, DMA2D_FGPFCCR_CS, (clut_size << DMA2D_FGPFCCR_CS_Pos));
}

/**
  * @brief  Get DMA2D foreground CLUT size, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  FGPFCCR          CS          LL_DMA2D_FGND_GetCLUTSize
  * @param  dma2dx DMA2D Instance
  * @retval Foreground CLUT size value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_GetCLUTSize(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->FGPFCCR, DMA2D_FGPFCCR_CS) >> DMA2D_FGPFCCR_CS_Pos);
}

/**
  * @brief  Set DMA2D foreground CLUT color mode.
  * @rmtoll
  *  FGPFCCR          CCM          LL_DMA2D_FGND_SetCLUTColorMode
  * @param  dma2dx DMA2D Instance
  * @param  clut_color_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_CLUT_COLOR_MODE_ARGB8888
  *         @arg @ref LL_DMA2D_CLUT_COLOR_MODE_RGB888
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetCLUTColorMode(DMA2D_TypeDef *dma2dx, uint32_t clut_color_mode)
{
  MODIFY_REG(dma2dx->FGPFCCR, DMA2D_FGPFCCR_CCM, clut_color_mode);
}

/**
  * @brief  Return DMA2D foreground CLUT color mode.
  * @rmtoll
  *  FGPFCCR          CCM         LL_DMA2D_FGND_GetCLUTColorMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_CLUT_COLOR_MODE_ARGB8888
  *         @arg @ref LL_DMA2D_CLUT_COLOR_MODE_RGB888
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_GetCLUTColorMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->FGPFCCR, DMA2D_FGPFCCR_CCM));
}

#if defined(DMA2D_FGPFCCR_CSS)
/**
  * @brief  Set DMA2D foreground Chroma Sub Sampling (for YCbCr input color mode).
  * @rmtoll
  *  FGPFCCR          CSS          LL_DMA2D_FGND_SetChrSubSampling
  * @param  dma2dx DMA2D Instance
  * @param  chroma_sub_sampling This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_CSS_444
  *         @arg @ref LL_DMA2D_CSS_422
  *         @arg @ref LL_DMA2D_CSS_420
  */
__STATIC_INLINE void LL_DMA2D_FGND_SetChrSubSampling(DMA2D_TypeDef *dma2dx, uint32_t chroma_sub_sampling)
{
  MODIFY_REG(dma2dx->FGPFCCR, DMA2D_FGPFCCR_CSS, chroma_sub_sampling);
}

/**
  * @brief  Return DMA2D foreground Chroma Sub Sampling (for YCbCr input color mode).
  * @rmtoll
  *  FGPFCCR          CSS         LL_DMA2D_FGND_GetChrSubSampling
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_CSS_444
  *         @arg @ref LL_DMA2D_CSS_422
  *         @arg @ref LL_DMA2D_CSS_420
  */
__STATIC_INLINE uint32_t LL_DMA2D_FGND_GetChrSubSampling(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->FGPFCCR, DMA2D_FGPFCCR_CSS));
}
#endif /* DMA2D_FGPFCCR_CSS */
/**
  * @}
  */

/** @defgroup DMA2D_LL_EF_BGND_Configuration Background Configuration Functions
  * @{
  */

/**
  * @brief  Set DMA2D background memory address, expressed on 32 bits ([31:0] bits).
  * @rmtoll
  *  BGMAR          MA          LL_DMA2D_BGND_SetMemAddr
  * @param  dma2dx DMA2D Instance
  * @param  memory_address Value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetMemAddr(DMA2D_TypeDef *dma2dx, uint32_t memory_address)
{
  WRITE_REG(dma2dx->BGMAR, memory_address);
}

/**
  * @brief  Get DMA2D background memory address, expressed on 32 bits ([31:0] bits).
  * @rmtoll
  *  BGMAR          MA          LL_DMA2D_BGND_GetMemAddr
  * @param  dma2dx DMA2D Instance
  * @retval Background memory address value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DMA2D_BGND_GetMemAddr(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_REG(dma2dx->BGMAR));
}

/**
  * @brief  Enable DMA2D background CLUT loading.
  * @rmtoll
  *  BGPFCCR          START            LL_DMA2D_BGND_EnableCLUTLoad
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_BGND_EnableCLUTLoad(DMA2D_TypeDef *dma2dx)
{
  SET_BIT(dma2dx->BGPFCCR, DMA2D_BGPFCCR_START);
}

/**
  * @brief  Indicate if DMA2D background CLUT loading is enabled.
  * @rmtoll
  *  BGPFCCR          START            LL_DMA2D_BGND_IsEnabledCLUTLoad
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_BGND_IsEnabledCLUTLoad(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->BGPFCCR, DMA2D_BGPFCCR_START) == (DMA2D_BGPFCCR_START)) ? 1UL : 0UL);
}

/**
  * @brief  Set DMA2D background color mode.
  * @rmtoll
  *  BGPFCCR          CM          LL_DMA2D_BGND_SetColorMode
  * @param  dma2dx DMA2D Instance
  * @param  color_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB8888
  *         @arg @ref LL_DMA2D_INPUT_MODE_RGB888
  *         @arg @ref LL_DMA2D_INPUT_MODE_RGB565
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB1555
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB4444
  *         @arg @ref LL_DMA2D_INPUT_MODE_L8
  *         @arg @ref LL_DMA2D_INPUT_MODE_AL44
  *         @arg @ref LL_DMA2D_INPUT_MODE_AL88
  *         @arg @ref LL_DMA2D_INPUT_MODE_L4
  *         @arg @ref LL_DMA2D_INPUT_MODE_A8
  *         @arg @ref LL_DMA2D_INPUT_MODE_A4
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetColorMode(DMA2D_TypeDef *dma2dx, uint32_t color_mode)
{
  MODIFY_REG(dma2dx->BGPFCCR, DMA2D_BGPFCCR_CM, color_mode);
}

/**
  * @brief  Return DMA2D background color mode.
  * @rmtoll
  *  BGPFCCR          CM          LL_DMA2D_BGND_GetColorMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB8888
  *         @arg @ref LL_DMA2D_INPUT_MODE_RGB888
  *         @arg @ref LL_DMA2D_INPUT_MODE_RGB565
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB1555
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB4444
  *         @arg @ref LL_DMA2D_INPUT_MODE_L8
  *         @arg @ref LL_DMA2D_INPUT_MODE_AL44
  *         @arg @ref LL_DMA2D_INPUT_MODE_AL88
  *         @arg @ref LL_DMA2D_INPUT_MODE_L4
  *         @arg @ref LL_DMA2D_INPUT_MODE_A8
  *         @arg @ref LL_DMA2D_INPUT_MODE_A4
  */
__STATIC_INLINE uint32_t  LL_DMA2D_BGND_GetColorMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->BGPFCCR, DMA2D_BGPFCCR_CM));
}

/**
  * @brief  Set DMA2D background alpha mode.
  * @rmtoll
  *  BGPFCCR          AM         LL_DMA2D_BGND_SetAlphaMode
  * @param  dma2dx DMA2D Instance
  * @param  alpha_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_ALPHA_MODE_NO_MODIF
  *         @arg @ref LL_DMA2D_ALPHA_MODE_REPLACE
  *         @arg @ref LL_DMA2D_ALPHA_MODE_COMBINE
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetAlphaMode(DMA2D_TypeDef *dma2dx, uint32_t alpha_mode)
{
  MODIFY_REG(dma2dx->BGPFCCR, DMA2D_BGPFCCR_AM, alpha_mode);
}

/**
  * @brief  Return DMA2D background alpha mode.
  * @rmtoll
  *  BGPFCCR          AM          LL_DMA2D_BGND_GetAlphaMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_ALPHA_MODE_NO_MODIF
  *         @arg @ref LL_DMA2D_ALPHA_MODE_REPLACE
  *         @arg @ref LL_DMA2D_ALPHA_MODE_COMBINE
  */
__STATIC_INLINE uint32_t  LL_DMA2D_BGND_GetAlphaMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->BGPFCCR, DMA2D_BGPFCCR_AM));
}

/**
  * @brief  Set DMA2D background alpha value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  BGPFCCR          ALPHA         LL_DMA2D_BGND_SetAlpha
  * @param  dma2dx DMA2D Instance
  * @param  alpha Value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetAlpha(DMA2D_TypeDef *dma2dx, uint32_t alpha)
{
  MODIFY_REG(dma2dx->BGPFCCR, DMA2D_BGPFCCR_ALPHA, (alpha << DMA2D_BGPFCCR_ALPHA_Pos));
}

/**
  * @brief  Return DMA2D background alpha value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  BGPFCCR          ALPHA          LL_DMA2D_BGND_GetAlpha
  * @param  dma2dx DMA2D Instance
  * @retval Alpha value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE uint32_t  LL_DMA2D_BGND_GetAlpha(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->BGPFCCR, DMA2D_BGPFCCR_ALPHA) >> DMA2D_BGPFCCR_ALPHA_Pos);
}

/**
  * @brief  Set DMA2D background input color mode, input alpha mode, and input alpha value
  * @rmtoll
  *  BGPFCCR          CM         LL_DMA2D_BGND_SetARGBMode \n
  *  BGPFCCR          ALPHA      LL_DMA2D_BGND_SetARGBMode \n
  *  BGPFCCR          AM         LL_DMA2D_BGND_SetARGBMode
  * @param  dma2dx DMA2D Instance
  * @param  color_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB8888
  *         @arg @ref LL_DMA2D_INPUT_MODE_RGB888
  *         @arg @ref LL_DMA2D_INPUT_MODE_RGB565
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB1555
  *         @arg @ref LL_DMA2D_INPUT_MODE_ARGB4444
  *         @arg @ref LL_DMA2D_INPUT_MODE_L8
  *         @arg @ref LL_DMA2D_INPUT_MODE_AL44
  *         @arg @ref LL_DMA2D_INPUT_MODE_AL88
  *         @arg @ref LL_DMA2D_INPUT_MODE_L4
  *         @arg @ref LL_DMA2D_INPUT_MODE_A8
  *         @arg @ref LL_DMA2D_INPUT_MODE_A4
  * @param  alpha_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_ALPHA_MODE_NO_MODIF
  *         @arg @ref LL_DMA2D_ALPHA_MODE_REPLACE
  *         @arg @ref LL_DMA2D_ALPHA_MODE_COMBINE
  * @param  alpha Value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetARGBMode(DMA2D_TypeDef *dma2dx, uint32_t color_mode, \
                                               uint32_t alpha_mode, uint32_t alpha)
{
  MODIFY_REG(dma2dx->BGPFCCR, DMA2D_BGPFCCR_CM | DMA2D_BGPFCCR_AM | DMA2D_BGPFCCR_ALPHA | DMA2D_BGPFCCR_RBS, \
             color_mode | alpha_mode | (alpha << DMA2D_BGPFCCR_ALPHA_Pos));
}


/**
  * @brief  Set DMA2D background Red Blue swap mode.
  * @rmtoll
  *  BGPFCCR          RBS         LL_DMA2D_BGND_SetRBSwapMode
  * @param  dma2dx DMA2D Instance
  * @param  rb_swap_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_RB_MODE_REGULAR
  *         @arg @ref LL_DMA2D_RB_MODE_SWAP
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetRBSwapMode(DMA2D_TypeDef *dma2dx, uint32_t rb_swap_mode)
{
  MODIFY_REG(dma2dx->BGPFCCR, DMA2D_BGPFCCR_RBS, rb_swap_mode);
}

/**
  * @brief  Return DMA2D background Red Blue swap mode.
  * @rmtoll
  *  BGPFCCR          RBS          LL_DMA2D_BGND_GetRBSwapMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_RB_MODE_REGULAR
  *         @arg @ref LL_DMA2D_RB_MODE_SWAP
  */
__STATIC_INLINE uint32_t  LL_DMA2D_BGND_GetRBSwapMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->BGPFCCR, DMA2D_BGPFCCR_RBS));
}

/**
  * @brief  Set DMA2D background alpha inversion mode.
  * @rmtoll
  *  BGPFCCR          AI         LL_DMA2D_BGND_SetAlphaInvMode
  * @param  dma2dx DMA2D Instance
  * @param  alpha_inversion_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_ALPHA_REGULAR
  *         @arg @ref LL_DMA2D_ALPHA_INVERTED
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetAlphaInvMode(DMA2D_TypeDef *dma2dx, uint32_t alpha_inversion_mode)
{
  MODIFY_REG(dma2dx->BGPFCCR, DMA2D_BGPFCCR_AI, alpha_inversion_mode);
}

/**
  * @brief  Return DMA2D background alpha inversion mode.
  * @rmtoll
  *  BGPFCCR          AI          LL_DMA2D_BGND_GetAlphaInvMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_ALPHA_REGULAR
  *         @arg @ref LL_DMA2D_ALPHA_INVERTED
  */
__STATIC_INLINE uint32_t  LL_DMA2D_BGND_GetAlphaInvMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->BGPFCCR, DMA2D_BGPFCCR_AI));
}

/**
  * @brief  Set DMA2D background line offset.
  * @rmtoll
  *  BGOR          LO          LL_DMA2D_BGND_SetLineOffset
  * @param  dma2dx DMA2D Instance
  * @param  line_offset Value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetLineOffset(DMA2D_TypeDef *dma2dx, uint32_t line_offset)
{
  MODIFY_REG(dma2dx->BGOR, DMA2D_BGOR_LO, line_offset);
}

/**
  * @brief  Return DMA2D background line offset.
  * @rmtoll
  *  BGOR          LO         LL_DMA2D_BGND_GetLineOffset
  * @param  dma2dx DMA2D Instance
  * @retval Background line offset value between Min_Data=0 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t  LL_DMA2D_BGND_GetLineOffset(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->BGOR, DMA2D_BGOR_LO));
}

/**
  * @brief  Set DMA2D background color values, expressed on 24 bits ([23:0] bits).
  * @rmtoll
  *  BGCOLR          COLOR          LL_DMA2D_BGND_SetColor
  * @param  dma2dx DMA2D Instance
  * @param  color   Value between Min_Data=0 and Max_Data=0xFFFFFF
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetRGBColor(DMA2D_TypeDef *dma2dx, uint32_t color)
{
  WRITE_REG(dma2dx->BGCOLR, color);
}

/**
  * @brief  Set DMA2D background color values, expressed on 24 bits ([23:0] bits).
  * @rmtoll
  *  BGCOLR          RED          LL_DMA2D_BGND_SetColor \n
  *  BGCOLR          GREEN        LL_DMA2D_BGND_SetColor \n
  *  BGCOLR          BLUE         LL_DMA2D_BGND_SetColor
  * @param  dma2dx DMA2D Instance
  * @param  red   Value between Min_Data=0 and Max_Data=0xFF
  * @param  green Value between Min_Data=0 and Max_Data=0xFF
  * @param  blue  Value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetColor(DMA2D_TypeDef *dma2dx, uint32_t red, uint32_t green, uint32_t blue)
{
  MODIFY_REG(dma2dx->BGCOLR, (DMA2D_BGCOLR_RED | DMA2D_BGCOLR_GREEN | DMA2D_BGCOLR_BLUE), \
             ((red << DMA2D_BGCOLR_RED_Pos) | (green << DMA2D_BGCOLR_GREEN_Pos) | blue));
}

/**
  * @brief  Set DMA2D background red color value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  BGCOLR          RED         LL_DMA2D_BGND_SetRedColor
  * @param  dma2dx DMA2D Instance
  * @param  red Value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetRedColor(DMA2D_TypeDef *dma2dx, uint32_t red)
{
  MODIFY_REG(dma2dx->BGCOLR, DMA2D_BGCOLR_RED, (red << DMA2D_BGCOLR_RED_Pos));
}

/**
  * @brief  Return DMA2D background red color value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  BGCOLR          RED          LL_DMA2D_BGND_GetRedColor
  * @param  dma2dx DMA2D Instance
  * @retval Red color value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE uint32_t  LL_DMA2D_BGND_GetRedColor(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->BGCOLR, DMA2D_BGCOLR_RED) >> DMA2D_BGCOLR_RED_Pos);
}

/**
  * @brief  Set DMA2D background green color value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  BGCOLR          GREEN         LL_DMA2D_BGND_SetGreenColor
  * @param  dma2dx DMA2D Instance
  * @param  green Value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetGreenColor(DMA2D_TypeDef *dma2dx, uint32_t green)
{
  MODIFY_REG(dma2dx->BGCOLR, DMA2D_BGCOLR_GREEN, (green << DMA2D_BGCOLR_GREEN_Pos));
}

/**
  * @brief  Return DMA2D background green color value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  BGCOLR          GREEN          LL_DMA2D_BGND_GetGreenColor
  * @param  dma2dx DMA2D Instance
  * @retval Green color value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE uint32_t  LL_DMA2D_BGND_GetGreenColor(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->BGCOLR, DMA2D_BGCOLR_GREEN) >> DMA2D_BGCOLR_GREEN_Pos);
}

/**
  * @brief  Set DMA2D background blue color value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  BGCOLR          BLUE         LL_DMA2D_BGND_SetBlueColor
  * @param  dma2dx DMA2D Instance
  * @param  blue Value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetBlueColor(DMA2D_TypeDef *dma2dx, uint32_t blue)
{
  MODIFY_REG(dma2dx->BGCOLR, DMA2D_BGCOLR_BLUE, blue);
}

/**
  * @brief  Return DMA2D background blue color value, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  BGCOLR          BLUE          LL_DMA2D_BGND_GetBlueColor
  * @param  dma2dx DMA2D Instance
  * @retval Blue color value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE uint32_t  LL_DMA2D_BGND_GetBlueColor(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->BGCOLR, DMA2D_BGCOLR_BLUE));
}

/**
  * @brief  Set DMA2D background CLUT memory address, expressed on 32 bits ([31:0] bits).
  * @rmtoll
  *  BGCMAR          MA         LL_DMA2D_BGND_SetCLUTMemAddr
  * @param  dma2dx DMA2D Instance
  * @param  clut_memory_address Value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetCLUTMemAddr(DMA2D_TypeDef *dma2dx, uint32_t clut_memory_address)
{
  WRITE_REG(dma2dx->BGCMAR, clut_memory_address);
}

/**
  * @brief  Get DMA2D background CLUT memory address, expressed on 32 bits ([31:0] bits).
  * @rmtoll
  *  BGCMAR          MA           LL_DMA2D_BGND_GetCLUTMemAddr
  * @param  dma2dx DMA2D Instance
  * @retval Background CLUT memory address value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t  LL_DMA2D_BGND_GetCLUTMemAddr(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_REG(dma2dx->BGCMAR));
}

/**
  * @brief  Set DMA2D background CLUT size, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  BGPFCCR          CS         LL_DMA2D_BGND_SetCLUTSize
  * @param  dma2dx DMA2D Instance
  * @param  clut_size Value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetCLUTSize(DMA2D_TypeDef *dma2dx, uint32_t clut_size)
{
  MODIFY_REG(dma2dx->BGPFCCR, DMA2D_BGPFCCR_CS, (clut_size << DMA2D_BGPFCCR_CS_Pos));
}

/**
  * @brief  Get DMA2D background CLUT size, expressed on 8 bits ([7:0] bits).
  * @rmtoll
  *  BGPFCCR          CS           LL_DMA2D_BGND_GetCLUTSize
  * @param  dma2dx DMA2D Instance
  * @retval Background CLUT size value between Min_Data=0 and Max_Data=0xFF
  */
__STATIC_INLINE uint32_t  LL_DMA2D_BGND_GetCLUTSize(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->BGPFCCR, DMA2D_BGPFCCR_CS) >> DMA2D_BGPFCCR_CS_Pos);
}

/**
  * @brief  Set DMA2D background CLUT color mode.
  * @rmtoll
  *  BGPFCCR          CCM         LL_DMA2D_BGND_SetCLUTColorMode
  * @param  dma2dx DMA2D Instance
  * @param  clut_color_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA2D_CLUT_COLOR_MODE_ARGB8888
  *         @arg @ref LL_DMA2D_CLUT_COLOR_MODE_RGB888
  */
__STATIC_INLINE void LL_DMA2D_BGND_SetCLUTColorMode(DMA2D_TypeDef *dma2dx, uint32_t clut_color_mode)
{
  MODIFY_REG(dma2dx->BGPFCCR, DMA2D_BGPFCCR_CCM, clut_color_mode);
}

/**
  * @brief  Return DMA2D background CLUT color mode.
  * @rmtoll
  *  BGPFCCR          CCM          LL_DMA2D_BGND_GetCLUTColorMode
  * @param  dma2dx DMA2D Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA2D_CLUT_COLOR_MODE_ARGB8888
  *         @arg @ref LL_DMA2D_CLUT_COLOR_MODE_RGB888
  */
__STATIC_INLINE uint32_t  LL_DMA2D_BGND_GetCLUTColorMode(const DMA2D_TypeDef *dma2dx)
{
  return (uint32_t)(READ_BIT(dma2dx->BGPFCCR, DMA2D_BGPFCCR_CCM));
}

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup DMA2D_LL_EF_FLAG_MANAGEMENT Flag Management
  * @{
  */

/**
  * @brief  Check if the DMA2D Configuration Error Interrupt Flag is set or not
  * @rmtoll
  *  ISR          CEIF            LL_DMA2D_IsActiveFlag_CE
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsActiveFlag_CE(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->ISR, DMA2D_ISR_CEIF) == (DMA2D_ISR_CEIF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the DMA2D CLUT Transfer Complete Interrupt Flag is set or not
  * @rmtoll
  *  ISR          CTCIF            LL_DMA2D_IsActiveFlag_CTC
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsActiveFlag_CTC(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->ISR, DMA2D_ISR_CTCIF) == (DMA2D_ISR_CTCIF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the DMA2D CLUT Access Error Interrupt Flag is set or not
  * @rmtoll
  *  ISR          CAEIF            LL_DMA2D_IsActiveFlag_CAE
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsActiveFlag_CAE(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->ISR, DMA2D_ISR_CAEIF) == (DMA2D_ISR_CAEIF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the DMA2D Transfer Watermark Interrupt Flag is set or not
  * @rmtoll
  *  ISR          TWIF            LL_DMA2D_IsActiveFlag_TW
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsActiveFlag_TW(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->ISR, DMA2D_ISR_TWIF) == (DMA2D_ISR_TWIF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the DMA2D Transfer Complete Interrupt Flag is set or not
  * @rmtoll
  *  ISR          TCIF            LL_DMA2D_IsActiveFlag_TC
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsActiveFlag_TC(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->ISR, DMA2D_ISR_TCIF) == (DMA2D_ISR_TCIF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the DMA2D Transfer Error Interrupt Flag is set or not
  * @rmtoll
  *  ISR          TEIF            LL_DMA2D_IsActiveFlag_TE
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsActiveFlag_TE(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->ISR, DMA2D_ISR_TEIF) == (DMA2D_ISR_TEIF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Interrupts Flag
  * @param  dma2dx DMA2D Instance
  * @param  flag This parameter can be a combination of the following values:
  *         @arg @ref LL_DMA2D_FLAG_CEIF
  *         @arg @ref LL_DMA2D_FLAG_CTCIF
  *         @arg @ref LL_DMA2D_FLAG_CAEIF
  *         @arg @ref LL_DMA2D_FLAG_TWIF
  *         @arg @ref LL_DMA2D_FLAG_TCIF
  *         @arg @ref LL_DMA2D_FLAG_TEIF
  *         @arg @ref LL_DMA2D_FLAG_ALL
  */
__STATIC_INLINE void LL_DMA2D_ClearFlag(DMA2D_TypeDef *dma2dx, uint32_t flag)
{
  WRITE_REG(dma2dx->IFCR, flag);
}

/**
  * @brief  Clear DMA2D Configuration Error Interrupt Flag
  * @rmtoll
  *  IFCR          CCEIF          LL_DMA2D_ClearFlag_CE
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_ClearFlag_CE(DMA2D_TypeDef *dma2dx)
{
  WRITE_REG(dma2dx->IFCR, DMA2D_IFCR_CCEIF);
}

/**
  * @brief  Clear DMA2D CLUT Transfer Complete Interrupt Flag
  * @rmtoll
  *  IFCR          CCTCIF          LL_DMA2D_ClearFlag_CTC
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_ClearFlag_CTC(DMA2D_TypeDef *dma2dx)
{
  WRITE_REG(dma2dx->IFCR, DMA2D_IFCR_CCTCIF);
}

/**
  * @brief  Clear DMA2D CLUT Access Error Interrupt Flag
  * @rmtoll
  *  IFCR          CAECIF          LL_DMA2D_ClearFlag_CAE
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_ClearFlag_CAE(DMA2D_TypeDef *dma2dx)
{
  WRITE_REG(dma2dx->IFCR, DMA2D_IFCR_CAECIF);
}

/**
  * @brief  Clear DMA2D Transfer Watermark Interrupt Flag
  * @rmtoll
  *  IFCR          CTWIF          LL_DMA2D_ClearFlag_TW
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_ClearFlag_TW(DMA2D_TypeDef *dma2dx)
{
  WRITE_REG(dma2dx->IFCR, DMA2D_IFCR_CTWIF);
}

/**
  * @brief  Clear DMA2D Transfer Complete Interrupt Flag
  * @rmtoll
  *  IFCR          CTCIF          LL_DMA2D_ClearFlag_TC
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_ClearFlag_TC(DMA2D_TypeDef *dma2dx)
{
  WRITE_REG(dma2dx->IFCR, DMA2D_IFCR_CTCIF);
}

/**
  * @brief  Clear DMA2D Transfer Error Interrupt Flag
  * @rmtoll
  *  IFCR          CTEIF          LL_DMA2D_ClearFlag_TE
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_ClearFlag_TE(DMA2D_TypeDef *dma2dx)
{
  WRITE_REG(dma2dx->IFCR, DMA2D_IFCR_CTEIF);
}

/**
  * @}
  */

/** @defgroup DMA2D_LL_EF_IT_MANAGEMENT Interruption Management
  * @{
  */

/**
  * @brief  Enable Interrupts
  * @param  dma2dx DMA2D Instance
  * @param  interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_DMA2D_IT_CEIE
  *         @arg @ref LL_DMA2D_IT_CTCIE
  *         @arg @ref LL_DMA2D_IT_CAEIE
  *         @arg @ref LL_DMA2D_IT_TWIE
  *         @arg @ref LL_DMA2D_IT_TCIE
  *         @arg @ref LL_DMA2D_IT_TEIE
  */
__STATIC_INLINE void LL_DMA2D_EnableIT(DMA2D_TypeDef *dma2dx, uint32_t interrupt)
{
  SET_BIT(dma2dx->CR, interrupt);
}

/**
  * @brief  Disable Interrupts
  * @param  dma2dx DMA2D Instance
  * @param  interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_DMA2D_IT_CEIE
  *         @arg @ref LL_DMA2D_IT_CTCIE
  *         @arg @ref LL_DMA2D_IT_CAEIE
  *         @arg @ref LL_DMA2D_IT_TWIE
  *         @arg @ref LL_DMA2D_IT_TCIE
  *         @arg @ref LL_DMA2D_IT_TEIE
  */
__STATIC_INLINE void LL_DMA2D_DisableIT(DMA2D_TypeDef *dma2dx, uint32_t interrupt)
{
  CLEAR_BIT(dma2dx->CR, interrupt);
}

/**
  * @brief  Enable Configuration Error Interrupt
  * @rmtoll
  *  CR          CEIE        LL_DMA2D_EnableIT_CE
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_EnableIT_CE(DMA2D_TypeDef *dma2dx)
{
  SET_BIT(dma2dx->CR, DMA2D_CR_CEIE);
}

/**
  * @brief  Enable CLUT Transfer Complete Interrupt
  * @rmtoll
  *  CR          CTCIE        LL_DMA2D_EnableIT_CTC
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_EnableIT_CTC(DMA2D_TypeDef *dma2dx)
{
  SET_BIT(dma2dx->CR, DMA2D_CR_CTCIE);
}

/**
  * @brief  Enable CLUT Access Error Interrupt
  * @rmtoll
  *  CR          CAEIE        LL_DMA2D_EnableIT_CAE
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_EnableIT_CAE(DMA2D_TypeDef *dma2dx)
{
  SET_BIT(dma2dx->CR, DMA2D_CR_CAEIE);
}

/**
  * @brief  Enable Transfer Watermark Interrupt
  * @rmtoll
  *  CR          TWIE        LL_DMA2D_EnableIT_TW
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_EnableIT_TW(DMA2D_TypeDef *dma2dx)
{
  SET_BIT(dma2dx->CR, DMA2D_CR_TWIE);
}

/**
  * @brief  Enable Transfer Complete Interrupt
  * @rmtoll
  *  CR          TCIE        LL_DMA2D_EnableIT_TC
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_EnableIT_TC(DMA2D_TypeDef *dma2dx)
{
  SET_BIT(dma2dx->CR, DMA2D_CR_TCIE);
}

/**
  * @brief  Enable Transfer Error Interrupt
  * @rmtoll
  *  CR          TEIE        LL_DMA2D_EnableIT_TE
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_EnableIT_TE(DMA2D_TypeDef *dma2dx)
{
  SET_BIT(dma2dx->CR, DMA2D_CR_TEIE);
}

/**
  * @brief  Disable Configuration Error Interrupt
  * @rmtoll
  *  CR          CEIE        LL_DMA2D_DisableIT_CE
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_DisableIT_CE(DMA2D_TypeDef *dma2dx)
{
  CLEAR_BIT(dma2dx->CR, DMA2D_CR_CEIE);
}

/**
  * @brief  Disable CLUT Transfer Complete Interrupt
  * @rmtoll
  *  CR          CTCIE        LL_DMA2D_DisableIT_CTC
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_DisableIT_CTC(DMA2D_TypeDef *dma2dx)
{
  CLEAR_BIT(dma2dx->CR, DMA2D_CR_CTCIE);
}

/**
  * @brief  Disable CLUT Access Error Interrupt
  * @rmtoll
  *  CR          CAEIE        LL_DMA2D_DisableIT_CAE
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_DisableIT_CAE(DMA2D_TypeDef *dma2dx)
{
  CLEAR_BIT(dma2dx->CR, DMA2D_CR_CAEIE);
}

/**
  * @brief  Disable Transfer Watermark Interrupt
  * @rmtoll
  *  CR          TWIE        LL_DMA2D_DisableIT_TW
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_DisableIT_TW(DMA2D_TypeDef *dma2dx)
{
  CLEAR_BIT(dma2dx->CR, DMA2D_CR_TWIE);
}

/**
  * @brief  Disable Transfer Complete Interrupt
  * @rmtoll
  *  CR          TCIE        LL_DMA2D_DisableIT_TC
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_DisableIT_TC(DMA2D_TypeDef *dma2dx)
{
  CLEAR_BIT(dma2dx->CR, DMA2D_CR_TCIE);
}

/**
  * @brief  Disable Transfer Error Interrupt
  * @rmtoll
  *  CR          TEIE        LL_DMA2D_DisableIT_TE
  * @param  dma2dx DMA2D Instance
  */
__STATIC_INLINE void LL_DMA2D_DisableIT_TE(DMA2D_TypeDef *dma2dx)
{
  CLEAR_BIT(dma2dx->CR, DMA2D_CR_TEIE);
}

/**
  * @brief  Check if the DMA2D Configuration Error interrupt source is enabled or disabled.
  * @rmtoll
  *  CR          CEIE        LL_DMA2D_IsEnabledIT_CE
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsEnabledIT_CE(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->CR, DMA2D_CR_CEIE) == (DMA2D_CR_CEIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the DMA2D CLUT Transfer Complete interrupt source is enabled or disabled.
  * @rmtoll
  *  CR          CTCIE        LL_DMA2D_IsEnabledIT_CTC
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsEnabledIT_CTC(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->CR, DMA2D_CR_CTCIE) == (DMA2D_CR_CTCIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the DMA2D CLUT Access Error interrupt source is enabled or disabled.
  * @rmtoll
  *  CR          CAEIE        LL_DMA2D_IsEnabledIT_CAE
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsEnabledIT_CAE(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->CR, DMA2D_CR_CAEIE) == (DMA2D_CR_CAEIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the DMA2D Transfer Watermark interrupt source is enabled or disabled.
  * @rmtoll
  *  CR          TWIE        LL_DMA2D_IsEnabledIT_TW
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsEnabledIT_TW(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->CR, DMA2D_CR_TWIE) == (DMA2D_CR_TWIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the DMA2D Transfer Complete interrupt source is enabled or disabled.
  * @rmtoll
  *  CR          TCIE        LL_DMA2D_IsEnabledIT_TC
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsEnabledIT_TC(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->CR, DMA2D_CR_TCIE) == (DMA2D_CR_TCIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the DMA2D Transfer Error interrupt source is enabled or disabled.
  * @rmtoll
  *  CR          TEIE        LL_DMA2D_IsEnabledIT_TE
  * @param  dma2dx DMA2D Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA2D_IsEnabledIT_TE(const DMA2D_TypeDef *dma2dx)
{
  return ((READ_BIT(dma2dx->CR, DMA2D_CR_TEIE) == (DMA2D_CR_TEIE)) ? 1UL : 0UL);
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

#endif /* defined (DMA2D) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_LL_DMA2D_H */
