/**
 *                Universidade Tecnológica Federal do Paraná
 *
 * Copyright (c) 2017 Rafael Nunes <rcamposnunes@outlook.com>
 * Copyright (c) 2017 Mikael Messias <mikaelmessias@outlook.com>
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

#ifndef BFS_ERRORS_H
#define BFS_ERRORS_H

#include <stdio.h>

// The maximum size of an error message.
#define BFS_MAX_ERROR_LENGTH 2048

// List of possible ~errors~ and their numerical correspondents.
#define BFS_LOG        0x00
#define BFS_CRITICAL   0x01
#define BFS_WARNING    0x02

#define BFS_STR_LOG     0x10
#define BFS_STR_ERROR   0x11
#define BFS_STR_WARNING 0X12

#define BFS_PARSER_ERROR 0x20

void bfs_pfinfo(const char *f);
void bfs_pferror(FILE *stream, const char *s, int line, char *file, int errc);

#endif // BFS_ERRORS_H
