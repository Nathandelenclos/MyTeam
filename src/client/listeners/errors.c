/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** sucess.c
*/

#include "client.h"

/**
 * Default error listener.
 * @param packet - Packet to read.
 */
void default_error(packet_t *packet)
{
    printf("Error: %s\n", packet->data);
}

/**
 * Unfound listener.
 * @param packet - Packet to read.
 */
void unfound(packet_t *packet)
{
    printf("Error unfound: %s\n", packet->data);
}

/**
 * Unauthorized listener.
 * @param packet - Packet to read.
 */
void unauthorized(packet_t *packet)
{
    client_error_unauthorized();
    printf("Error unauthorized command: %s\n", packet->data);
}

/**
 * Already exist listener.
 * @param packet - Packet to read.
 */
void already_exist(packet_t *packet)
{
    printf("Error already exist: %s\n", packet->data);
}
