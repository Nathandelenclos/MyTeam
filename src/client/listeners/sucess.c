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
 * USERS_SUCCESS_CODE listener.
 * @param packet - Packet to read.
 */
void give_users(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_print_users(data[0], data[1], atoi(data[2]));
}

/**
 * USE_SUCCESS listener.
 * @param packet - Packet to read.
 */
void use_success(packet_t *packet)
{
    printf("Info: %s\n", packet->data);
}
