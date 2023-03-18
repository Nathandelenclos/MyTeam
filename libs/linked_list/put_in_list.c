/*
** EPITECH PROJECT, 2021
** LINKED_LIST
** File description:
** put in list
*/

#include "list.h"

/**
 * Put a node in the list.
 * @param list - List to put the node.
 * @param data - Data to put in the node.
 * @return 0.
 */
int put_in_list(node **list, void *data)
{
    node *list1 = MALLOC(sizeof(node));

    list1->data = data;
    list1->next = *list;
    *list = list1;

    return (0);
}
