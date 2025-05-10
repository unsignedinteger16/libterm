// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    src/linux/cursor.c: Header implemention of cursor operations in linux OS
*/

#include <libterm/cursor.h>
#include "initialization.h"

#include <stdio.h>

Libterm_Result libterm_set_cursor_pos(Libterm_Cursor_Position pos) {
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    printf("\033[%d;%dH", pos.row + 1, pos.column + 1);
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_hide_cursor() {
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    printf("\033[?25l");
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_show_cursor() {
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    printf("\033[?25h");
    return LIBTERM_SUCCESS;
}