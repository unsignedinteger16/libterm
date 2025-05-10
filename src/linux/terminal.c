// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    src/linux/terminal.c: implemention of terminal operations in linux OS
*/

#include <libterm/result.h>

#include <libterm/result.h>
#include <libterm/terminal.h>
#include "initialization.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

Libterm_Result libterm_flush_terminal() {
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    fflush(stdout);
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_clear_screen() {
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    printf("\033[2J");
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_enter_raw_mode() {
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    struct termios raw = _libterm_get_state()->orginal;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) return LIBTERM_INTERNAL_FAILURE;
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_exit_raw_mode() {
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &_libterm_get_state()->orginal) == -1) return LIBTERM_INTERNAL_FAILURE;
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_enter_alternate_screen_buffer() {
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    printf("\033[?1049h");
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_exit_alternate_screen_buffer() {
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    printf("\033[?1049l");
    return LIBTERM_SUCCESS;
}


Libterm_Result libterm_get_terminal_size(Libterm_Terminal_Size *size) {
    if(!size) return LIBTERM_INVALID_ARGS;
    if(!_libterm_is_initialized()) return LIBTERM_NOT_INITIALIZED;
    struct winsize termsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &termsize);
    *size = (Libterm_Terminal_Size){
        .rows = termsize.ws_row,
        .columns = termsize.ws_col
    };
    return LIBTERM_SUCCESS;
}
