// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    example/menu.c: Example program that shows little interactive menu

    Dependencies: libterm, lm
*/

#include <libterm/libterm.h>
#include <libterm/events.h>

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ARR_SIZE(arr) sizeof(arr)/sizeof(arr[0])
#define max(a, b) a > b ? a : b

#define OPTION_SIZE_MAX 256

typedef struct {
    char string[OPTION_SIZE_MAX + 1];
    void (*behavior)();
} Menu_Option;

void exit_ok();

char title_string[] = "Simple Example Menu";
Menu_Option menu_options[] = {
    (Menu_Option){ .string = "Exit", .behavior = exit_ok },
    (Menu_Option){ .string = "Close", .behavior = exit_ok },
    (Menu_Option){ .string = "Quit", .behavior = exit_ok },
};

size_t biggest_option_lenght();

typedef struct {
    Libterm_Terminal_Size size;
    uint8_t selectedOption;
} Application_State;

Application_State state;

void clean();
void render();

int main() { 
    Libterm_Result result;
    atexit(clean);
    if(result = libterm_initialize() < LIBTERM_SUCCESS) return result;
    if(result = libterm_events_initialize() < LIBTERM_SUCCESS) return result;


    libterm_enter_alternate_screen_buffer();
    libterm_enter_raw_mode();
    libterm_hide_cursor();
    libterm_flush_terminal();

    libterm_events_enable_event_type(LIBTERM_EVENTS_TYPE_RESIZED | LIBTERM_EVENTS_TYPE_KEYPRESS);
    Libterm_Events_Event event;
    libterm_get_terminal_size(&state.size);
    state.selectedOption = 0;
    render();
    while(1) {
        if(result = libterm_events_update() < LIBTERM_SUCCESS) return result;
        if(result = libterm_events_poll_event(&event) < LIBTERM_SUCCESS) return result;
        switch (event.type) {
        case LIBTERM_EVENTS_TYPE_RESIZED:        
            state.size = event.resized.newSize;
            render();
        case LIBTERM_EVENTS_TYPE_KEYPRESS:
            switch (event.keypress) {
            case LIBTERM_UP_ARROW:
                if(state.selectedOption == 0) state.selectedOption = ARR_SIZE(menu_options) - 1;
                else --state.selectedOption;
                render();
                libterm_flush_terminal();
                break;
            case LIBTERM_DOWN_ARROW:
                if(state.selectedOption == ARR_SIZE(menu_options) - 1) state.selectedOption = 0;
                else ++state.selectedOption;
                render();
                libterm_flush_terminal();
                break;
            case LIBTERM_ENTER_KEY:
                render();
                menu_options[state.selectedOption].behavior();
                libterm_flush_terminal();
                break;
            default:
                break;
            }
        default:
            break;
        }
    }
}

void exit_ok() {
    exit(0);
}

size_t biggest_option_lenght() {
    size_t val = 0;
    for(int i = 0; i < ARR_SIZE(menu_options); i++) {
        val = max(val, strlen(menu_options[i].string));
    }
    return val;
}

void clean() {
    libterm_show_cursor();
    libterm_exit_alternate_screen_buffer();
    libterm_flush_terminal();
    libterm_exit_raw_mode();
    libterm_events_clean();
    libterm_clean();
}

void render() {
    libterm_clear_screen();
    libterm_set_cursor_pos(LIBTERM_CREATE_CURSOR_POSITION(0, floor((state.size.columns - ARR_SIZE(title_string)) / 2)));
    printf("%s", title_string);
    int coloringStart = floor((state.size.columns - biggest_option_lenght()) / 2);
    for(int i = 0; i < ARR_SIZE(menu_options); i++) {
        int textStart = floor((state.size.columns - strlen(menu_options[i].string)) / 2);
        libterm_set_cursor_pos(LIBTERM_CREATE_CURSOR_POSITION(3 + i, coloringStart));
        if(state.selectedOption == i) {
            libterm_set_background_color(LIBTERM_CREATE_COLOR(0xFFFFFF));
            libterm_set_foreground_color(LIBTERM_CREATE_COLOR(0x181818));
        }
        printf("%s", menu_options[i].string);
        libterm_reset_background();
        libterm_reset_foreground();
    }
    
    libterm_flush_terminal();
} 