// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    src/events/events.c: Implementation of core part of libterm_events, wrapper of libterm that adds events (YEAH, WRAPPER OF WRAPPER)

    Dependencies: libterm, libterm_events, lm
*/

#include "queue.h"
#include <libterm/events.h>

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    uint64_t flags;
    _Libterm_Events_Queue queue;
    Libterm_Terminal_Size termSize;
} _Libterm_Events_State;

static bool _initialized = false;
static _Libterm_Events_State _state;

Libterm_Result libterm_events_initialize() {
    _initialized = true;
    _state.flags = 0;
    Libterm_Result result;
    if(result = _libterm_events_queue_init(&_state.queue) < LIBTERM_SUCCESS) return result;
    if(result = libterm_get_terminal_size(&_state.termSize) < LIBTERM_SUCCESS) return result;
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_events_clean() {
    if(!_initialized) return LIBTERM_NOT_INITIALIZED;
    _initialized = false;
    _libterm_events_queue_free(&_state.queue);
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_events_enable_event_type(Libterm_Events_Event_Type type) {
    if(!_initialized) return LIBTERM_NOT_INITIALIZED;
    _state.flags |= type;
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_events_disable_event_type(Libterm_Events_Event_Type type) {
    if(!_initialized) return LIBTERM_NOT_INITIALIZED;
    _state.flags &= ~(type);
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_events_update() {
    if(!_initialized) return LIBTERM_NOT_INITIALIZED;
    Libterm_Result result;

    if(_state.flags & LIBTERM_EVENTS_TYPE_RESIZED) {
        Libterm_Terminal_Size size;
        if(result = libterm_get_terminal_size(&size) < LIBTERM_SUCCESS) return result;
        if(size.columns != _state.termSize.columns || size.rows != _state.termSize.rows) {
            if(result = _libterm_events_queue_push(&_state.queue, (Libterm_Events_Event){
                .type = LIBTERM_EVENTS_TYPE_RESIZED,
                .resized.newSize = size,
                .resized.oldSize = _state.termSize
            }) < LIBTERM_SUCCESS);
            _state.termSize = size;
        }
    }

    if(_state.flags & LIBTERM_EVENTS_TYPE_KEYPRESS) {
        Libterm_Result result;
        Libterm_Key key;
        while(result = libterm_read_key(&key) == LIBTERM_SUCCESS) {
            _libterm_events_queue_push(&_state.queue, (Libterm_Events_Event){
                .type = LIBTERM_EVENTS_TYPE_KEYPRESS,
                .keypress = key,
            });
            libterm_flush_terminal();
        }
        if(result != LIBTERM_EMPTY) return result;
    }
     
    return LIBTERM_SUCCESS;
}

Libterm_Result libterm_events_poll_event(Libterm_Events_Event *event) {
    if(!event) return LIBTERM_INVALID_ARGS;
    if(!_initialized) return LIBTERM_NOT_INITIALIZED;
    
    Libterm_Events_Event polledEvent;
    Libterm_Result result = _libterm_events_queue_poll(&_state.queue, &polledEvent);

    if(result < LIBTERM_SUCCESS) return result;
    if (result == LIBTERM_EMPTY) {
        *event = (Libterm_Events_Event){
            .type = LIBTERM_EVENTS_TYPE_NONE,
        };
    } else {
        *event = polledEvent;
    }
    
    return LIBTERM_SUCCESS;
}