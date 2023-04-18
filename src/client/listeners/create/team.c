/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** team.c
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
 * Create team listener.
 * @param packet - Packet to read.
 */
void team_created(packet_t *packet)
{
    string *data = str_to_word_array(packet->data, "|");
    client_print_team_created(data[0], data[1], data[2]);
    printf("New Team \"%s - %s\" created (%s)\n", data[1], data[2], data[0]);
    free_array(data);
}