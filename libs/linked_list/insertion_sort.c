/*
** EPITECH PROJECT, 2023
** Lib
** File description:
** insertionSort
*/

#include "list.h"
/**
 * Insert a node into a sorted list (in ascending order).
 * @param head - Head of the list.
 * @param newnode - Node to insert.
 * @param cmp - Compare function.
 */
void insert_node_sorted(node **head, node *newnode, int (*cmp)(void *, void *))
{
    if (*head == NULL || cmp(newnode->data, (*head)->data) < 0) {
        newnode->next = *head;
        *head = newnode;
        return;
    }
    node *current = *head;
    while (current->next != NULL &&
        cmp(newnode->data, current->next->data) > 0) {
        current = current->next;
    }
    newnode->next = current->next;
    current->next = newnode;
}

/**
 * Sorts a linked list using insertion sort.
 * @param headRef - Head of the list.
 * @param cmp - Compare function.
 */
void insertion_sort(node **headRef, int (*cmp)(void *, void *))
{
    node *sorted = NULL;
    node *current = *headRef;
    while (current != NULL) {
        node *nextnode = current->next;
        insert_node_sorted(&sorted, current, cmp);
        current = nextnode;
    }
    *headRef = sorted;
}
