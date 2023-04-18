/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** channel.c
*/

#include "client.h"

/**
 * Create channel listener.
 * @param packet - Packet to read.
 */
void create_channel(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_event_channel_created(data[0], data[1], data[2]);
    printf("New Channel \"%s - %s\" created (%s)\n",
        data[1], data[2], data[0]);
    free_array(data);
}

/**
 * Create channel listener.
 * @param packet - Packet to read.
 */
void channel_created(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_print_channel_created(data[0], data[1], data[2]);
    printf("New Channel \"%s - %s\" created (%s)\n",
        data[1], data[2], data[0]);
    free_array(data);
}
