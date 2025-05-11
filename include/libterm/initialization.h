// SPDX-License-Identifier: MIT License
/*
    LibTerm - Lightweight terminal library in C99

    include/libterm/initialization.h: Header adding signatures for initialization
*/

#ifndef LIBTERM_INITIALIZATION_H__
#define LIBTERM_INITIALIZATION_H__

#include <libterm/extern.h>
#include <libterm/result.h>

LIBTERM_EXTERN Libterm_Result libterm_initialize();
LIBTERM_EXTERN Libterm_Result libterm_clean();

#endif