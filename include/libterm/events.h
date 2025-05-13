// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    include/libterm/events.h: Header for libterm_events, wrapper of libterm that adds events (YEAH, WRAPPER OF WRAPPER)
*/

#ifndef LIBTERM_EVENTS_H__
#define LIBTERM_EVENTS_H__

#include <libterm/extern.h>
#include <libterm/libterm.h>

typedef enum {
    LIBTERM_EVENTS_TYPE_RESIZED = 1 << 0,
    LIBTERM_EVENTS_TYPE_KEYPRESS = 1 << 1,
} Libterm_Events_Event_Type;

typedef struct {
    Libterm_Terminal_Size oldSize;
    Libterm_Terminal_Size newSize;
} Libterm_Events_Resized_Event_Data;

typedef struct aaa {
    Libterm_Events_Event_Type type;
    union {
        Libterm_Events_Resized_Event_Data resized;
        Libterm_Key keypress;
    };
} Libterm_Events_Event;

LIBTERM_EXTERN Libterm_Result libterm_events_initialize();
LIBTERM_EXTERN Libterm_Result libterm_events_clean();
 
// * * Passing LIBTERM_EVENTS_TYPE_NONE does nothing
LIBTERM_EXTERN Libterm_Result libterm_events_enable_event_type(Libterm_Events_Event_Type type);
LIBTERM_EXTERN Libterm_Result libterm_events_disable_event_type(Libterm_Events_Event_Type type);

LIBTERM_EXTERN Libterm_Result libterm_events_update();
LIBTERM_EXTERN Libterm_Result libterm_events_poll_event(Libterm_Events_Event *event);

#endif