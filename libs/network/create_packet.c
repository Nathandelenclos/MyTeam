/*
** EPITECH PROJECT, 2023
** Network
** File description:
** create data
*/

#include "network.h"

/**
 * Create packet.
 * @param code - Code of packet.
 * @param data - Data of packet.
 * @return - Return packet.
 */
packet_t *create_packet(int code, string data)
{
    packet_t *socket = MALLOC(sizeof(packet_t));
    socket->data = my_strdup(data);
    socket->code = code;
    socket->len = strlen(data);
    return socket;
}
