/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** sucess.c
*/

#include "client.h"
#include "logging_client.h"

/**
 * Success listener.
 * @param packet - Packet to read.
 */
void give_user_info(packet_t *packet)
{
    string data = my_strdup(packet->data);
    char **array = str_to_word_array(data, "|");
    printf("Info: %s\n", array[2]);
    client_print_user(array[1], array[0], my_str_to_int(array[3]));
}
