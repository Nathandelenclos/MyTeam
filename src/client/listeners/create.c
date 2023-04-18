/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** create.c
*/

#include "client.h"

/**
 * Create team listener.
 * @param packet - Packet to read.
 */
void create_team(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_event_team_created(data[0], data[1], data[2]);
    printf("New Team \"%s - %s\" created (%s)\n", data[1], data[2], data[0]);
    free_array(data);
}

/**
 * Create channel listener.
 * @param packet - Packet to read.
 */
void create_channel(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_event_channel_created(data[0], data[1], data[2]);
    printf("New Channel \"%s - %s\" created (%s)\n", data[1], data[2], data[0]);
    free_array(data);
}

/**
 * Create thread listener.
 * @param packet - Packet to read.
 */
void create_thread(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    time_t time = atoi(data[2]);
    client_event_thread_created(data[0], data[1], time, data[3], data[4]);
    printf("New Thread \"%s - %s\" created (%s)\n", data[3], data[4], data[0]);
    free_array(data);
}

/**
 * Create reply listener.
 * @param packet - Packet to read.
 */
void create_reply(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    time_t time = atoi(data[3]);
    client_event_thread_reply_received(data[0], data[1], data[2], data[4]);
    client_print_reply_created(data[1], data[2], time, data[4]);
    free_array(data);
}
