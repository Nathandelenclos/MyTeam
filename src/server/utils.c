/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** utils
*/

#include "server.h"
#include <dirent.h>

/**
 * Count of occurrence of char in string.
 * @param str - String to count.
 * @param c - Char to count.
 * @return - Return count of occurrence.
 */
int count_occurrence_char(string str, char c)
{
    if (str[0] == 0) {
        return 0;
    } else if (str[0] == c) {
        str++;
        return 1 + count_occurrence_char(str, c);
    } else {
        str++;
        return count_occurrence_char(str, c);
    }
}

/**
 * Split string.
 * @param str - String to split
 * @param delim - Delimiter
 * @return - Return array of string.
 */
string *split(string str, char delim)
{
    size_t size = sizeof(string) * (count_occurrence_char(str, delim) + 3);
    string *words = MALLOC(size);
    memset(words, 0, size);
    char deli[2] = {delim, 0};
    string word = strtok(str, deli);
    int i = 0;
    for (; word != NULL; ++i) {
        words[i] = my_strdup(word);
        word = strtok(NULL, deli);
    }
    words[i + 1] = NULL;
    return words;
}

/**
 * Len of array.
 * @param array - Array to count.
 * @return - Return len of array.
 */
int array_string_len(string *array)
{
    int i = 0;
    for (; array[i] != NULL; ++i);
    return i;
}

/**
 * Check if dir exist.
 * @param dir - Dir to check.
 * @return - Return 1 if exist, 0 if not.
 */
int exist_dir(string dir)
{
    if (chdir(dir) == 0) {
        chdir("-");
        return 1;
    }
    return 0;
}
