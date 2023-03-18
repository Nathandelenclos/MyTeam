/*
** EPITECH PROJECT, 2023
** Network
** File description:
** create data
*/

#include "network.h"

socket_t *create_data(int code, string data)
{
    socket_t *socket = MALLOC(sizeof(socket_t));
    socket->data = my_strdup(data);
    socket->code = code;
    socket->len = strlen(data);
    return socket;
}