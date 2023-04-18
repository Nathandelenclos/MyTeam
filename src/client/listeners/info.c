/*
** EPITECH PROJECT, 2023
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** list.c
*/

#include "client.h"

/**
 * INFO_USER_SUCCESS listener.
 * @param packet - Packet to read.
 */
void info_user(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_print_user(data[0], data[1], atoi(data[2]));
    free_array(data);
}

/**
 * INFO_TEAM_SUCCESS listener.
 * @param packet - Packet to read.
 */
void info_team(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_print_team(data[0], data[1], data[2]);
    free_array(data);
}

/**
 * INFO_CHANNEL_SUCCESS listener.
 * @param packet - Packet to read.
 */
void info_channel(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_print_channel(data[0], data[1], data[2]);
    free_array(data);
}

/**
 * INFO_THREAD_SUCCESS listener.
 * @param packet - Packet to read.
 */
void info_thread(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    time_t time = atoi(data[2]);
    client_print_thread(data[0], data[1], time, data[3], data[4]);
    free_array(data);
}
