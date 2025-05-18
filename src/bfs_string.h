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

#ifndef BFS_STRING_H
#define BFS_STRING_H

#include <wchar.h>

/**
 * @brief Compares two strings.
 * @param s The first string to use in the comparison.
 * @param s_ The second string to use in the comparison.
 */
int bfs_strcmpl(const char *restrict s, const char *restrict s_);

/**
 * @brief Compares n chars from the back of the string.
 * @param s The first string to use in the comparison.
 * @param s_ The second string to use in the comparison.
 * @param n How many characters to compare both strings.
 */
int bfs_strncmpl(const char *restrict s, const char *restrict s_, int n);

/**
 * @brief Splits a string s by a delimiter and returns the i-th string.
 * @param s The string to be split.
 * @param delim The delimiter used to split the string.
 * @param i The i-th token in the string s.
 */
char *bfs_strsplit(const char *restrict s, const char *restrict delim, int i);


/**
 * @brief Searches for the first c character inside the string s.
 * @param s The string used to search the character.
 * @param c The character to be searched in the string
 * @returns An integer representing the position of the first character c in
 * the string s or, -1 if the character c could not be found.
 */
int bfs_strchr(const char *s, const char c);

#endif// BFS_STRING_H
