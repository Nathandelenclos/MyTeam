/*
** EPITECH PROJECT, 2021
** LINKED_LIST
** File description:
** put in list
*/

#include "list.h"

int put_in_list(node **list, void *data)
{
    node *list1 = MALLOC(sizeof(node));

    list1->data = data;
    list1->next = *list;
    *list = list1;

    return (0);
}
