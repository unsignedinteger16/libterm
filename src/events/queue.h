// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    src/events/queue.c: Header of queue in libterm_events

    Dependencies: libterm, libterm_events, lm
*/

#ifndef QUEUE_H__
#define QUEUE_H__

#include <libterm/events.h>

#include <stddef.h>

typedef struct {
    size_t allocated;
    size_t used;
    size_t offset;
    Libterm_Events_Event *data;
} _Libterm_Events_Queue;

Libterm_Result _libterm_events_queue_init(_Libterm_Events_Queue *queue);
Libterm_Result _libterm_events_queue_free(_Libterm_Events_Queue *queue);
Libterm_Result _libterm_events_queue_push(_Libterm_Events_Queue *queue, Libterm_Events_Event event);
Libterm_Result _libterm_events_queue_poll(_Libterm_Events_Queue *queue, Libterm_Events_Event *event);

#endif