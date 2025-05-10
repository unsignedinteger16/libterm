// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    example/colorful.c: Example program that writes colorful string

    Dependencies: libterm, lm
*/

#include <libterm/libterm.h>

#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Syntax: %s <string>\n", argv[0]);
        return -1;
    }

    libterm_initialize();

    const uint8_t minCol = 0x0;
    const uint8_t maxCol = 0xFF;
    const double colorChange = (double)(maxCol - minCol) / (double)strlen(argv[1]);
    double currentCol = maxCol;

    for (size_t i = 0; i < strlen(argv[1]); i++)
    {
        libterm_set_foreground_color((Libterm_Color_24){ .r = 0xFF, .b = floor(currentCol), .g = floor(currentCol) });
        printf("%c", argv[1][i]);
        currentCol -= colorChange;
    }    
    printf("\n");
    libterm_reset_foreground();
    libterm_flush_terminal();
    libterm_clean();
}