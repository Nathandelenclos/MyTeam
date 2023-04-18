/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** reply.c
*/

#include "client.h"

/**
 * Create reply listener.
 * @param packet - Packet to read.
 */
void create_reply(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    time_t time = atoi(data[3]);
    client_event_thread_reply_received(data[0], data[1], data[2], data[4]);
    free_array(data);
}

/**
 * Create reply listener.
 * @param packet - Packet to read.
 */
void reply_created(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    time_t time = atoi(data[3]);
    client_print_reply_created(data[1], data[2], time, data[4]);
    free_array(data);
}
