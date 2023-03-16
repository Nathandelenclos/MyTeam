/*
** EPITECH PROJECT, 2023
** LinkedList
** File description:
** find
*/

#include "list.h"

node *find_list(node *list, int (*function)(each_t each))
{
    node *tmp = list;
    for (int i = 0; tmp != NULL; ++i) {
        each_t each = {list, tmp, i};
        if (function(each)) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}
