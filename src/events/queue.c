// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    src/events/queue.c: Implementation of queue for libterm_events

    Dependencies: libterm, libterm_events, lm
*/

#include <libterm/libterm.h>
#include "queue.h"

#include <stdlib.h>

Libterm_Result _libterm_events_queue_init(_Libterm_Events_Queue *queue) {
    if(!queue) return LIBTERM_INVALID_ARGS;
    queue->allocated = ALLOCATION_CHUNK;
    queue->used = 0;
    queue->offset = 0;
    queue->data = malloc(ALLOCATION_CHUNK * sizeof(Libterm_Events_Event));
    if(!queue->data) return LIBTERM_BUY_MORE_RAM;
    return LIBTERM_SUCCESS;
} 

Libterm_Result _libterm_events_queue_free(_Libterm_Events_Queue *queue) {
    if(!queue) return LIBTERM_INVALID_ARGS;
    free(queue->data);
    return LIBTERM_SUCCESS;
}

Libterm_Result _libterm_events_queue_push(_Libterm_Events_Queue *queue, Libterm_Events_Event event) {
    if(!queue) return LIBTERM_INVALID_ARGS;
    if(queue->used + queue->offset >= queue->allocated) {
        queue->allocated += ALLOCATION_CHUNK;
        Libterm_Events_Event *new = realloc(queue->data, (queue->allocated) * sizeof(Libterm_Events_Event));
        if(!new) {
            _libterm_events_queue_free(queue);
            return LIBTERM_BUY_MORE_RAM;
        }
    }
    queue->data[queue->offset + queue->used++] = event; 
}

Libterm_Result _libterm_events_queue_poll(_Libterm_Events_Queue *queue, Libterm_Events_Event *event) {
    if(!queue) return LIBTERM_INVALID_ARGS;
    if(queue->used == 0) return LIBTERM_EMPTY;

    *event = queue->data[(--queue->used, queue->offset++)];

    if(queue->used == 0) {
        queue->offset = 0;
    }

    return LIBTERM_SUCCESS;
}