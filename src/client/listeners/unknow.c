/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** sucess.c
*/

#include "client.h"

/**
 * Unknow Team listener.
 * @param packet - Packet to read.
 */
void unknow_team(packet_t *packet)
{
    client_error_unknown_team(packet->data);
    printf("Unknow: %s\n", packet->data);
}

/**
 * Unknow Channel listener.
 * @param packet - Packet to read.
 */
void unknow_channel(packet_t *packet)
{
    client_error_unknown_channel(packet->data);
    printf("Unknow: %s\n", packet->data);
}

/**
 * Unknow Thread listener.
 * @param packet - Packet to read.
 */
void unknow_thread(packet_t *packet)
{
    client_error_unknown_thread(packet->data);
    printf("Unknow: %s\n", packet->data);
}

/**
 * Unknow User listener.
 * @param packet - Packet to read.
 */
void unknow_user(packet_t *packet)
{
    client_error_unknown_user(packet->data);
    printf("Unknow: %s\n", packet->data);
}