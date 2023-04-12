/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** sucess.c
*/

#include "client.h"
#include "logging_client.h"

/**
 * Success listener.
 * @param packet - Packet to read.
 */
void success(packet_t *packet)
{
    //sscanf(packet->data, "%s|%s|%s", client_uuid, client_name, message);
    printf("Info: %s\n", packet->data);
    //client_event_logged_in()
}

/**
 * Unfound listener.
 * @param packet - Packet to read.
 */
void unfound(packet_t *packet)
{
    printf("Error: %s\n", packet->data);
}

void login_user(packet_t *packet)
{
    printf("Login: %s\n", packet->data);
}
