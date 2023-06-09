/*
** EPITECH PROJECT, 2021
** LINKED LIST
** File description:
** len list
*/

#include "list.h"
#include <stddef.h>
#include <stdio.h>

/**
 * Get the length of the list.
 * @param list - List to get the length.
 * @return The length of the list.
 */
int len_list(node *list)
{
    int len = 0;

    for (; list != NULL; len++)
        list = list->next;
    return len;
}
