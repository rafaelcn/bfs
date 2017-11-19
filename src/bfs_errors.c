/**
 *                Universidade Tecnológica Federal do Paraná
 *
 * Copyright (c) 2017 Rafael Nunes <rafaelnunes@engineer.com>
 * Copyright (c) 2017 Mikael Messias
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#include "bfs_errors.h"
#include "macros.h"

void bfs_pferror(FILE *stream, const char *s, int line, char *file, int errc) {

    // It is possible that the programmer may pass a string longer than
    // defined in the header of bfs_errors, in that scenario it is
    // definitely UB per standard definition.
    // Should we prevent that?
    char error[BFS_MAX_ERROR_LENGTH];

    switch(errc) {
    case BFS_LOG:
        sprintf(error, "\n>>> %s | File: %s on line %d.", s, file, line);
        break;
    case BFS_CRITICAL:
        sprintf(error, "\n%s>>> %s | File: %s on line %d. %s",
                ANSI_COLOR_RED, s, file, line, ANSI_COLOR_RESET);
        break;
    case BFS_WARNING:
        sprintf(error, "\n%s>>> %s | File: %s on line %d. %s",
                ANSI_COLOR_YELLOW, s, file, line, ANSI_COLOR_RESET);
        break;
    }


    fprintf(stream, error, line, file);
}
