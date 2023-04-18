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
    string *data = str_to_word_array(packet->data, "|");
    client_event_logged_in(data[0], data[1]);
    free_array(data);
}

/**
 * LOGOUT_SUCCESS listener.
 * @param packet - Packet to read.
 */
void logout_user(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_event_logged_out(data[0], data[1]);
    free_array(data);
}
