/*
** EPITECH PROJECT, 2021
** LINKED LIST
** File description:
** delete in list
*/

#include "list.h"
#include <stdlib.h>

node *get_end(node *list)
{
    int len = 0;
    if (list == NULL)
        return NULL;
    for (; list->next != NULL; len++)
        list = list->next;
    return list;
}
