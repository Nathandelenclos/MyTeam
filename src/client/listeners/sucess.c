/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** sucess.c
*/

#include "client.h"

/**
 * Success listener.
 * @param packet - Packet to read.
 */
void success(packet_t *packet)
{
    printf("Info: %s\n", packet->data);
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

void logout_user(packet_t *packet)
{
    printf("Logout: %s\n", packet->data);
}

void give_users(packet_t *packet)
{
    printf("Users: %s\n", packet->data);
}
