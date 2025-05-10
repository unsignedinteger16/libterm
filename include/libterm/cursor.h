// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    include/libterm/cursor.h: Header adding signatures for cursor operations
*/

#ifndef LIBTERM_CURSOR_H__
#define LIBTERM_CURSOR_H__

#include <libterm/result.h>

#include <stdint.h>

// Opposite to Ansi Escape Codes libterm starts from 0 not 1
typedef struct {
    uint16_t row;
    uint16_t column;
} Libterm_Cursor_Position;

#define LIBTERM_CREATE_CURSOR_POSITION(x, y) (Libterm_Cursor_Position){ .row = x, .column = y } 

Libterm_Result libterm_set_cursor_pos(Libterm_Cursor_Position pos);
Libterm_Result libterm_hide_cursor();
Libterm_Result libterm_show_cursor();

#endif