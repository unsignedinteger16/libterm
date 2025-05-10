/*
    LibTerm - Lightweight terminal library in C99

    include/libterm/terminal.h: Header adding signatures for terminal operations in LibTerm
*/

#include <libterm/result.h>

#include <stdint.h>

typedef struct {
    uint16_t rows;
    uint16_t columns;
} Libterm_Terminal_Size;

Libterm_Result libterm_flush_terminal();

Libterm_Result libterm_clear_screen(); // This doesn't move a cursor

Libterm_Result libterm_enter_raw_mode();
Libterm_Result libterm_exit_raw_mode();

Libterm_Result libterm_enter_alternate_screen_buffer();
Libterm_Result libterm_exit_alternate_screen_buffer();

Libterm_Result libterm_get_terminal_size(Libterm_Terminal_Size *size);
