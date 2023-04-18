/*
** EPITECH PROJECT, 2023
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** list.c
*/

#include "client.h"

/**
 * LIST_TEAMS_SUCCESS listener.
 * @param packet - Packet to read.
 */
void list_teams(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_print_teams(data[0], data[1], data[2]);
    free_array(data);
}

/**
 * LIST_CHANNEL_SUCCESS listener.
 * @param packet - Packet to read.
 */
void list_channel(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_team_print_channels(data[0], data[1], data[2]);
    free_array(data);
}

/**
 * LIST_THREAD_SUCCESS listener.
 * @param packet - Packet to read.
 */
void list_thread(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    time_t time = atoi(data[2]);
    client_channel_print_threads(data[0], data[1], time, data[3], data[4]);
    free_array(data);
}

/**
 * LIST_REPLY_SUCCESS listener.
 * @param packet - Packet to read.
 */
void list_reply(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    time_t time = atoi(data[2]);
    client_thread_print_replies(data[0], data[1], time, data[3]);
    free_array(data);
}
