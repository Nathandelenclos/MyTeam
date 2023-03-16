/*
** EPITECH PROJECT, 2021
** LIB MY
** File description:
** malloc c
*/

#include <stdlib.h>
#include "list.h"

void m_free(node *list, void *size)
{
    node *m;

    if (size == NULL)
        free_list(list, free);
    else {
        m = search_in_list(list, size);
        if (m->data != NULL)
            free(m->data);
        m->data = NULL;
    }
}

void *my_malloc(void *size, int opt)
{
    static node *list = NULL;
    void *m = NULL;

    if (opt) {
        m = malloc((size_t)size);
        if (m == NULL) {
            FREE_ALL();
            exit(84);
        }
        node *list1 = malloc(sizeof(node));
        list1->data = m;
        list1->next = list;
        list = list1;
    } else
        m_free(list, size);
    return m;
}
