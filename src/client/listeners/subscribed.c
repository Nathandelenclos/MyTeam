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
    printf("Suscribe to team: \"%s\"\n", data[1]);
    free_array(data);
}

/**
 * Subscribed listener.
 * @param packet - Packet to read.
 */
void suscribed(packet_t *packet)
{
    printf("Is suscribed to team: %s\n", packet->data);
}

/**
 * Unsubscribe listener.
 * @param packet - Packet to read.
 */
void unsuscribe(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_print_unsubscribed(data[0], data[1]);
    printf("Unsuscribe to team: %s\n", packet->data);
    free_array(data);
}
