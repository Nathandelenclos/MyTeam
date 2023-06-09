/*
** EPITECH PROJECT, 2021
** Bistromatic
** File description:
** include struct
*/

#include <stdlib.h>

#ifndef LINKED_LIST_H
    #define LINKED_LIST_H

    #define FREE(X) my_malloc(X, 0)
    #define FREE_ALL() my_malloc(NULL, 0)
    #define MALLOC(X) my_malloc((void * )(X), 1)

struct list_s {
    void *data;
    struct list_s *next;
};

typedef struct list_s node;

typedef struct {
    node *head;
    node *actual;
    int index;
} each_t;

int put_in_list(node **list, void *data);
int free_list(node *head, void (*screen)(void *data));
void show_list(node *list);
void delete_in_list(node **list, void *data);
int len_list(node *list);
void insert_in_list(node *previous, void *data);
void delete_first(node **head);
void reverse_list(node **head_ref);
int put_in_end(node **list, void *data);
void *my_malloc(void *size, int opt);
void my_free(void *ptr);
node *search_in_list(node *list, void *ptr);
node *get_end(node *list);
node *find_list(node *list, int (*function)(each_t each));
void map_list(node *list, void (*function)(each_t each));
void insertion_sort(node **headRef, int (*cmp)(void *, void *));

#endif
