/*
** EPITECH PROJECT, 2021
** LINKED LIST
** File description:
** Insert
*/

#include "list.h"
#include <stdlib.h>

/**
 * Insert a node in the list.
 * @param previous - Previous node.
 * @param data - Data to insert.
 */
void insert_in_list(node *previous, void *data)
{
    node *list1 = MALLOC(sizeof(node)), *next = previous->next;

    list1->data = data;
    list1->next = next;
    previous->next = list1;
    return;
}
