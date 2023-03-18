/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
**
*/

#include "client.h"

void success(packet_t *socket)
{
    printf("Info: %s\n", socket->data);
}

void unfound(packet_t *socket)
{
    printf("Error: %s\n", socket->data);
}