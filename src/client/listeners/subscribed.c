/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** sucess.c
*/

#include "client.h"

/**
 * Subscribe listener.
 * @param packet - Packet to read.
 */
void suscribe(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_print_subscribed(data[0], data[1]);
    printf("User \"%s\" suscribe to team: \"%s\"\n", data[0], data[1]);
    free_array(data);
}

/**
 * Subscribed listener.
 * @param packet - Packet to read.
 */
void suscribed_team(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_print_users(data[1], data[2], atoi(data[3]));
    printf("User \"%s\" suscribed to team: \"%s\"\n", data[1], data[0]);
}

/**
 * Subscribed listener.
 * @param packet - Packet to read.
 */
void suscribed_user(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_print_teams(data[1], data[2], data[3]);
    printf("User \"%s\" suscribed to team: \"%s\"\n", data[0], data[1]);
}

/**
 * Unsubscribe listener.
 * @param packet - Packet to read.
 */
void unsuscribe(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_print_unsubscribed(data[0], data[1]);
    printf("User \"%s\" unsuscribe to team: \"%s\"\n", data[0], data[1]);
    free_array(data);
}
