// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    src/linux/initialization.h: Internal initialization header for libterm linux implementation
*/

#ifndef INITIALIZATION_H__
#define INITIALIZATION_H__

#include <stdbool.h>
#include <termios.h>

typedef struct {
    struct termios orginal;
} _Libterm_State;

bool _libterm_is_initialized();
_Libterm_State *_libterm_get_state();

#endif