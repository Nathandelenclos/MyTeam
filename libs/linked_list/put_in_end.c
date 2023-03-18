/*
** EPITECH PROJECT, 2021
** LINKED LIST
** File description:
** put in end
*/

#include "list.h"

/**
 * Put a node in the end of the list.
 * @param list - List to put the node.
 * @param data - Data to put in the node.
 * @return 0.
 */
int put_in_end(node **list, void *data)
{
    reverse_list(list);
    put_in_list(list, data);
    reverse_list(list);
    return 0;
}
