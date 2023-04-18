/*
** EPITECH PROJECT, 2023
** Lib
** File description:
** insertionSort
*/

#include "list.h"

/**
 * Insertion sort.
 * @param headRef - Head of the list.
 * @param cmp - Compare function.
 */
void insertion_sort(node **headRef, int (*cmp)(void *, void *))
{
    node *sorted = NULL;
    node *current = *headRef;
    while (current != NULL) {
        node *nextnode = current->next;
        if (sorted == NULL || cmp(current->data, sorted->data) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            node *temp = sorted;
            while (temp->next != NULL &&
                cmp(current->data, temp->next->data) > 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = nextnode;
    }
    *headRef = sorted;
}