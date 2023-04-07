/*
** EPITECH PROJECT, 2021
** LIB
** File description:
** str cat
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int len_dest = my_strlen(dest);
    int i = 0;
    for (i; src[i] != '\0'; ++i)
        dest[len_dest + i] = src[i];
    dest[len_dest + i] = '\0';
    return dest;
}

char *my_strconcat(char *str1, char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char *res = malloc(sizeof(char) * (len1 + len2 + 1));
    if (res == NULL) {
        exit(84);
    }
    res[0] = '\0';
    strcat(res, str1);
    strcat(res, str2);
    return (res);
}
