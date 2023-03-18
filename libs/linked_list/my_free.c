/*
** EPITECH PROJECT, 2021
** LIB MY
** File description:
** free
*/

#include <stdlib.h>

/**
 * Free a pointer if it's not NULL.
 * @param ptr - Pointer to free.
 */
void my_free(void *ptr)
{
    if (ptr == NULL)
        free(ptr);
}
