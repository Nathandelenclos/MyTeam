/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** sucess.c
*/

#include "client.h"


/**
 * LOGIN_SUCCESS listener.
 * @param packet - Packet to read.
 */
void login_user(packet_t *packet)
{
    printf("Login: %s\n", packet->data);
}

/**
 * LOGOUT_SUCCESS listener.
 * @param packet - Packet to read.
 */
void logout_user(packet_t *packet)
{
    printf("Logout: %s\n", packet->data);
}
