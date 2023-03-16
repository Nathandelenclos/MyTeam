/*
** EPITECH PROJECT, 2023
** LinkedList
** File description:
** Map
*/

#include "list.h"

void map_list(node *list, void (*function)(each_t each))
{
    node *tmp = list;
    for (int i = 0; tmp != NULL; ++i) {
        each_t each = {list, tmp, i};
        function(each);
        tmp = tmp->next;
    }
}
