// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    include/libterm/output.h: Header adding signatures for output operations
*/

#ifndef LIBTERM_OUTPUT_H__
#define LIBTERM_OUTPUT_H__

#include <libterm/result.h>
#include <libterm/extern.h>

#include <stdint.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Libterm_Color_24;

#define LIBTERM_CREATE_COLOR(hex) (Libterm_Color_24){ .r = ((uint32_t)hex >> 16) & 0xFF, .g = ((uint32_t)hex >> 8) & 0xFF, .b = hex & 0xFF } 

LIBTERM_EXTERN Libterm_Result libterm_set_foreground_color(Libterm_Color_24 color);
LIBTERM_EXTERN Libterm_Result libterm_set_background_color(Libterm_Color_24 color);
LIBTERM_EXTERN Libterm_Result libterm_reset_foreground();
LIBTERM_EXTERN Libterm_Result libterm_reset_background();

#endif