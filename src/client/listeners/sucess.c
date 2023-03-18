/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
**
*/

#include "client.h"

/**
 * Success listener.
 * @param packet - Packet to read.
 */
void success(packet_t *packet)
{
    printf("Info: %s\n", socket->data);
}

/**
 * Unfound listener.
 * @param packet - Packet to read.
 */
void unfound(packet_t *socket)
{
    printf("Error: %s\n", socket->data);
}