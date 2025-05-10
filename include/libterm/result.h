// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    include/libterm/raw.h: Header adding signatures for returning results in LibTerm
*/

#ifndef LIBTERM_RESULT_H__
#define LIBTERM_RESULT_H__

typedef enum {
    LIBTERM_READ_ERROR = -5,
    LIBTERM_INTERNAL_FAILURE = -4,
    LIBTERM_BUY_MORE_RAM = -3,
    LIBTERM_INVALID_ARGS = -2,
    LIBTERM_NOT_INITIALIZED = -1,
    LIBTERM_SUCCESS = 0,
    LIBTERM_EMPTY = 1,
} Libterm_Result;

#endif