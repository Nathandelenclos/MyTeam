/*
** EPITECH PROJECT, 2023
** myftp
** File description:
** utils
*/

#include "main.h"
#include <dirent.h>

/**
 * Count of occurrence of char in string.
 * @param str
 * @param c
 * @return
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
 * strdup with my_malloc for garbage collector.
 * @param data
 * @return
 */
string my_strdup(string data)
{
    string ret = MALLOC(sizeof(char) * strlen(data) + 1);
    for (int i = 0; i <= strlen(data); ++i) {
        ret[i] = data[i];
    }
    return ret;
}

/**
 * sl
 * @param str - {string} is string to split
 * @param delim 
 * @return 
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
 * @param array
 * @return
 */
int array_string_len(string *array)
{
    int i = 0;
    for (; array[i] != NULL; ++i);
    return i;
}

int exist_dir(string dir)
{
    if (chdir(dir) == 0) {
        chdir("-");
        return 1;
    }
    return 0;
}
