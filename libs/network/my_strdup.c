/*
** EPITECH PROJECT, 2023
** Network
** File description:
** strdup
*/

#include "network.h"


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