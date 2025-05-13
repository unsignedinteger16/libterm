// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    src/linux/input.c: Implemention of input operations in linux OS
*/

#include <libterm/input.h>
#include <libterm/result.h>
#include "initialization.h"

#include <errno.h>
#include <unistd.h>

// Parses ESC[A, ESC[B, ESC[C, ESC[D 
// sqb means square brackets (i don't want name of function bigger than my screen)
Libterm_Key _libterm_parse_esc_opening_sqb_keys(char seq1) {
    char seq2;
    switch (seq1) {
    case 'A':
        return LIBTERM_UP_ARROW;
    case 'B':
        return LIBTERM_DOWN_ARROW;
    case 'C':
        return LIBTERM_RIGHT_ARROW;
    case 'D':
        return LIBTERM_LEFT_ARROW;
    case '5':
        if(read(STDIN_FILENO, &seq2, 1) != 1) return LIBTERM_ESCAPE_KEY;
        if(seq2 != '~') return LIBTERM_ESCAPE_KEY;
        return LIBTERM_PAGE_UP_KEY;
    case '6':
        if(read(STDIN_FILENO, &seq2, 1) != 1) return LIBTERM_ESCAPE_KEY;
        if(seq2 != '~') return LIBTERM_ESCAPE_KEY;
        return LIBTERM_PAGE_DOWN_KEY;
    default:
        return LIBTERM_ESCAPE_KEY;
    }
}

Libterm_Result libterm_read_key(Libterm_Key *key) {
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    int readResult;
    uint8_t c;
    if(readResult = read(STDIN_FILENO, &c, 1) != 1) {
        // If errno equalt EAGAIN that means nothing is in stdin ...
        if(readResult == -1 && errno == EAGAIN) return LIBTERM_EMPTY;
        // ... else read failed 
        return LIBTERM_READ_ERROR;
    }

    // Parsing Escape Characters
    if(c == '\x1b') {
        char seq[3];

        if(read(STDIN_FILENO, &seq[0], 1) != 1) return LIBTERM_ESCAPE_KEY;
        if(seq[0] == '[') {
            if(read(STDIN_FILENO, &seq[1], 1) != 1) {
                *key = LIBTERM_ALT_KEY('[');
                return LIBTERM_SUCCESS;
            }
            Libterm_Key parsedKey = _libterm_parse_esc_opening_sqb_keys(seq[1]);
            if(parsedKey == LIBTERM_INVALID_KEY) return LIBTERM_INTERNAL_FAILURE;
            *key = parsedKey;
            return LIBTERM_SUCCESS;
        } else {
            *key = LIBTERM_ALT_KEY(seq[1]);
            return LIBTERM_SUCCESS;
        }
    } else {
        *key = c;
    }
    return LIBTERM_SUCCESS;
}