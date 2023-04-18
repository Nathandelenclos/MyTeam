/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** thread.c
*/

#include "client.h"

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
 * Create thread listener.
 * @param packet - Packet to read.
 */
void thread_created(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    time_t time = atoi(data[2]);
    client_print_thread_created(data[0], data[1], time, data[3], data[4]);
    printf("New Thread \"%s - %s\" created (%s)\n", data[3], data[4], data[0]);
    free_array(data);
}
