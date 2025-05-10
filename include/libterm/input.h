// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    include/libterm/input.h: Header adding signatures for input operations
*/

#ifndef LIBTERM_INPUT_H__
#define LIBTERM_INPUT_H__

#include <stdint.h>
#include <libterm/result.h>

typedef uint32_t Libterm_Key;

#define LIBTERM_CTRL_KEY(k) ((k) & 0x1f)
#define LIBTERM_ALT_KEY(k) (0xFF | k << 8)
#define LIBTERM_ENTER_KEY LIBTERM_CTRL_KEY('m') // Beacuse of technical reasons for compatibility Enter == C-m (Ctrl+M)
#define LIBTERM_ESCAPE_KEY '\033'
#define LIBTERM_UP_ARROW 0x10000
#define LIBTERM_DOWN_ARROW 0x10001
#define LIBTERM_LEFT_ARROW 0x10002
#define LIBTERM_RIGHT_ARROW 0x10003
#define LIBTERM_PAGE_UP_KEY 0x10004
#define LIBTERM_PAGE_DOWN_KEY 0x10005
#define LIBTERM_INVALID_KEY -1

Libterm_Result libterm_read_key(Libterm_Key *key);

#endif