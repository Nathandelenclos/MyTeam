/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** str_to_word_array.c
*/

#include "my.h"

int char_checker(char c, char *str)
{
    int lensep = strlen(str);

    for (int i = 0; i < lensep; i++) {
        if (str[i] == c) {
            return (1);
        }
    }
    return (0);
}

int my_strlen_str_split(char const *str, char *sep)
{
    int i = 0;
    int line = -1;

    while (i < strlen(str)) {
        while (char_checker(str[i], sep) == 1)
            i++;
        line++;
        for (; char_checker(str[i], sep) == 0 && str[i] != '\0'; i++);
    }
    if (char_checker(str[strlen(str) - 1], sep) != 1)
        line++;
    return (line);
}

char **str_to_word_array(char *str, char *sep)
{
    int line = my_strlen_str_split(str, sep);
    char **spl = malloc(sizeof(char *) * (line + 1));
    int j = 0;
    int k = 0;
    int c = 0;

    for (int i = 0; i < line; i++) {
        while (char_checker(str[j], sep) == 1)
            j++;
        for (; char_checker(str[j], sep) == 0 && str[j] != '\0'; j++)
            c++;
        spl[i] = malloc(sizeof(char) * (c + 1));
        for (; k < c; k++)
            spl[i][k] = str[j - c + k];
        spl[i][k] = '\0';
        c = 0;
        k = 0;
    }
    spl[line] = NULL;
    return (spl);
}
