// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    example/clear.c: Example program that clears the screen

    Dependencies: libterm
*/

#include <libterm/libterm.h>

int main() {
    libterm_initialize();
    libterm_clear_screen();
    libterm_set_cursor_pos(LIBTERM_CREATE_CURSOR_POSITION(0, 0));
    libterm_flush_terminal();
    libterm_clean();
}