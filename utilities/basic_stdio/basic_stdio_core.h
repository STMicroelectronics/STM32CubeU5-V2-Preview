/**
  ******************************************************************************
  * @file    basic_stdio_core.h
  * @brief   public API header for the Basic stdio utility
  ******************************************************************************
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
#ifndef BASIC_STDIO_CORE_H
#define BASIC_STDIO_CORE_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

/* Internal functions ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/** @def WRITE_PROTO
  * @brief __If defined__, expands to the signature of the low-level hook specified by your libc
  * to write a string buffer to stdout.
  *
  * This macro is conditionally defined, or not, depending on the compiler parsing it;
  * see also @ref _write(), @ref __write(), @ref fputc().
  *
  * The recommended approach is to implement a function with signature extracted from @ref WRITE_PROTO
  * when it is defined (`#ifdef WRITE_PROTO`), and @ref fputc() as a fallback.
  *
  * @param file name of the "file handle" argument of the hook
  * @param ptr name of the "string pointer" argument of the hook
  * @param len name of the "buffer length" argument of the hook
  * @returns code signature of the hook, if available (without trailing `";"` nor `"{"`)
  */

#if defined(__GNUC__) && !defined(__clang__)
/*
 * GNUC dialect, not (arm-)clang = (arm-none-eabi-)GCC
 * Assuming this implies ulibc at link-time.
 */

/* _const_ char *ptr is a basic_stdio specific addition -- to be propagated? */

/** @brief I/O redirection hook as defined by __Micro-/Nano-libc__
  *
  * Signature generated thanks to @ref WRITE_PROTO when it is processed by a GCC;
  * don't use this definition directly, write it using that macro for portability.
  *
  * @param file Unused
  * @param ptr string buffer to be written
  * @param len length of the string buffer (excluding the final '\0', if any).
  * @returns number of chars actually written
  */
#define WRITE_PROTO(file, ptr, len) int _write(int file, const char *ptr, int len)

#elif defined(__ICCARM__) && (__VER__ >= 9020001)
/*
 * Recent IAR (v.>=9.20.1)
 *Assuming this implies similarly recent EWARM runtime at link-time
 */

/** @brief I/O redirection hook as defined by __EWARM v>=9.20.1__
  *
  * Signature generated thanks to @ref WRITE_PROTO when it is processed by a recent IAR;
  * don't use this definition directly, write it using that macro for portability.
  *
  * @param file Unused
  * @param ptr string buffer to be written
  * @param len length of the string buffer (excluding the final '\0', if any).
  * @returns number of chars actually written
  */
#define WRITE_PROTO(file, ptr, len) size_t __write(int file, const unsigned char *ptr, size_t len)
#endif /* GNUC and not __clang__ */

/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief Overall module initialization function.
  *
  * This function initializes Basic Trace.
  * @param pobj pointer to a peripheral object.
  *
  * @note Its actual effect changes depending on the selected variant:
  * - UART: pobj is actually a `UART_HandleTypeDef*`, and will be initialized manually
  * in polling mode with the desired output configuration.
  * The calls stores it for use for all later transmissions.
  * - ITM: pobj unused. Pass NULL in when calling.
  * - Template: behavior and semantics are user-defined.
  */
void UTIL_BASIC_STDIO_Init(void *pobj);

/*
  If a WRITE_PROTO-based hook is available, it will be implemented
  to redirect stdout to the desired peripheral.
  Else, fputc as defined in stdio.h will be implemented for this purpose.
*/
#ifdef WRITE_PROTO
WRITE_PROTO(file, ptr, len);
#endif /* WRITE_PROTO */

/** @fn int fputc(int c, FILE *f)
  * @brief Fallback I/O redirection hook
  *
  * Definition taken from <stdio.h>.
  *
  * EWARM (IAR) v<9.20.1 and armclang document this API in their stdio redirection hooks.
  *
  * This is only a fallback API: a @ref WRITE_PROTO -based hook is preferred if available, for the sake of performance.
  *
  * @param c character to write. Will be cast to `char` before being written.
  * @param f Unused
  * @returns c (on success)
  * @returns EOF (on failure)
  */
#ifdef __cplusplus
}
#endif

#endif /* BASIC_STDIO_CORE_H */
