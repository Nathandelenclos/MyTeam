/*
** EPITECH PROJECT, 2021
** Day06
** File description:
** task06
*/

#include "my.h"
#include <stdio.h>

int my_strcmp(char const *s1, char const *s2)
{
    if (s1 == NULL || s2 == NULL)
        return 0;
    if (my_strlen(s1) != my_strlen(s2))
        return 0;
    for (int i = 0; i < my_strlen(s1); ++i) {
        if (s1[i] != s2[i])
            return 0;
    }
    return 1;
}
