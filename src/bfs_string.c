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

char *bfs_strsplit(const char *restrict s, const char *restrict delim, int i) {

    char *token = NULL;
    size_t ssize = strlen(s);


    if (i < 0) {
        bfs_pferror(stderr, "Given index is out of bounds", __LINE__,
                    __FILE__, BFS_STR_ERROR);
        return "";
    } else if (i == 0 && strlen(delim) == 1) {
        if (s != NULL && ssize > 0) {
            int pos_delim = 0;

            while (s[pos_delim] != delim[0]) {
                pos_delim++;
            }

            token = malloc(pos_delim);

            for (int idx = 0; idx < pos_delim; idx++) {
                token[idx] = s[idx];
            }

            return token;
        }

        bfs_pferror(stderr, "char *s given is either null or empty",
                    __LINE__, __FILE__, BFS_STR_ERROR);
        return "";

    } else if (i == 0) {
        const char *p = strstr(s, delim);

        if (p == NULL) {
            char log[BFS_MAX_ERROR_LENGTH];
            sprintf(log, "Couldn't find %s in %s", delim, s);
            bfs_pferror(stderr, log, __LINE__, __FILE__, BFS_STR_LOG);
            return "";
        }

        // It is nice to have a look at the documentation for strstr to
        // have a fully understanding of what I am doing here.
        for (unsigned long idx = p-s; idx <= p-s+strlen(delim); idx++) {
            token[p-s+strlen(delim)-idx] = s[idx];
        }

        return token;
    }

    token = malloc(strlen(s));
    token = strtok((char *)s, delim);

    while (i >= 0 && token) {
        printf("\n%s", token);
        token = strtok(NULL, delim);
        i--;
    }

    return token;
}
