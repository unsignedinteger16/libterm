// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    src/linux/output.c: implemention of output operations in linux OS
*/

#include <libterm/output.h>
#include <libterm/result.h>
#include "initialization.h"

#include <stdio.h>

Libterm_Result libterm_set_foreground_color(Libterm_Color_24 color) {
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    printf("\033[38;2;%d;%d;%dm", color.r, color.g, color.b);
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_set_background_color(Libterm_Color_24 color) {
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    printf("\033[48;2;%d;%d;%dm", color.r, color.g, color.b);   
    return LIBTERM_SUCCESS; 
}

Libterm_Result libterm_reset_foreground() {
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    printf("\033[39m");
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_reset_background() {
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    printf("\033[49m");
    return LIBTERM_SUCCESS;
}
