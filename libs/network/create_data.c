/*
** EPITECH PROJECT, 2023
** Network
** File description:
** create data
*/

#include "network.h"

packet_t *create_packet(int code, string data)
{
    packet_t *socket = MALLOC(sizeof(packet_t));
    socket->data = my_strdup(data);
    socket->code = code;
    socket->len = strlen(data);
    return socket;
}