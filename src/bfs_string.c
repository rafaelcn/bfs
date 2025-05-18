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

#include "bfs_string.h"
#include "bfs_errors.h"


#include <stdlib.h>
#include <string.h>

int bfs_strcmpl(const char *restrict s, const char *restrict s_) {
    return bfs_strncmpl(s, s_, strlen(s));
}

int bfs_strncmpl(const char *restrict s, const char *restrict s_, int n) {
    if (&s == &s_) {
        return 1;
    }

    int j = n;

    for (unsigned int i = strlen(s)-1; i >= strlen(s)-n; i--) {
        if (s[i] != s_[j]) {
            return 1;
        }
        j--;
    }

    return 0;
}

char *bfs_strsplit(const char *restrict s, const char *restrict delim,
                   int pos) {

    char *token = NULL;
    size_t ssize = strlen(s);

    if (pos <= 0 || pos > (int)ssize) {
        bfs_pferror(stderr, "Given index is out of bounds", __LINE__,
                    __FILE__, BFS_STR_ERROR);
        return "";
    }

    //Working only with delimiters that with 1 char of size.
    unsigned int index = 0;
    pos -= 1;

    if (strlen(delim) == 1) {
        while (index < strlen(s)) {
            if (s[index] == *delim) {
                pos--;
            }

            // Found string to copy
            if (pos == 0) {
                if (s[index] == *delim) {
                    index++;
                }

                int k = 0;
                unsigned int ssize = 0;

                while (s[index+1] != *delim) {
                    index++;
                    ssize++;
                }

                token = calloc(ssize, 1);

                index -= ssize;

                while (s[index] != *delim && index != index+ssize) {
                    token[k] = s[index];

                    index++;
                    k++;
                }
                break;
            }

            index++;
        }
    }

    return token;
}

int bfs_strchr(const char *s, const char c) {
    unsigned int i = 0;

    while (i < strlen(s)) {
        if (s[i] == c) {
            return i;
        }
        i++;
    }

    return -1;
}
