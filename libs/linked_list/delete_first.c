/*
** EPITECH PROJECT, 2021
** LINKED LIST
** File description:
** delete first node
*/

#include "list.h"
#include <stdlib.h>

/**
 * Delete the first node of the list.
 * @param head - Head of the list.
 */
void delete_first(node **head)
{
    node *tmp;

    if (head == NULL || *head == NULL)
        return;
    tmp = *head;
    *head = (*head)->next;
    free(tmp);
}
