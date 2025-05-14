/*
    LibTerm - Lightweight terminal library in C99

    include/libterm/terminal.h: Header adding signatures for terminal operations in LibTerm
*/

#include <libterm/result.h>
#include <libterm/extern.h>

#include <stdint.h>

typedef struct {
    uint16_t rows;
    uint16_t columns;
} Libterm_Terminal_Size;

LIBTERM_EXTERN Libterm_Result libterm_flush_terminal();
 
LIBTERM_EXTERN Libterm_Result libterm_clear_screen(); // This doesn't move a cursor
 
LIBTERM_EXTERN Libterm_Result libterm_enter_raw_mode();
LIBTERM_EXTERN Libterm_Result libterm_exit_raw_mode();
 
LIBTERM_EXTERN Libterm_Result libterm_enter_alternate_screen_buffer();
LIBTERM_EXTERN Libterm_Result libterm_exit_alternate_screen_buffer();

LIBTERM_EXTERN Libterm_Result libterm_get_terminal_size(Libterm_Terminal_Size *size);
