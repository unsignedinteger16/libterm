// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    example/alternate.c: Example program that switches to alternate buffer

    Dependencies: libterm
*/

#include <libterm/libterm.h>

int main() { 
    libterm_initialize();
    libterm_enter_alternate_screen_buffer();
    libterm_flush_terminal();
    libterm_clean();
}