// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    src/linux/initialization.c: Implemention of initialization in linux OS
*/

#include <libterm/result.h>
#include "initialization.h"

#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

bool _libterm_initialized = false;
_Libterm_State _libterm_state;

bool _libterm_is_initialized() {
    return _libterm_initialized;
}

_Libterm_State *_libterm_get_state() {
    return &_libterm_state;
}

Libterm_Result libterm_initialize() {
    if(tcgetattr(STDIN_FILENO, &_libterm_state.orginal) == -1) return LIBTERM_INTERNAL_FAILURE;
    _libterm_initialized = true;
    printf("\033[?1000l\033[?1006l");
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_clean() {
    if(!_libterm_initialized) return LIBTERM_NOT_INITIALIZED;
    printf("\033[?1000h\033[?1006h");
    return LIBTERM_SUCCESS;
}