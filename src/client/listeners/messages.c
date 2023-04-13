/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** messages.c
*/

#include "client.h"
#include "logging_client.h"
#include "server.h"

/**
 * Message listener.
 * @param packet - Packet to read.
 */
void message_sent(packet_t *packet)
{
    string data = my_strdup(packet->data);
    char **array = str_to_word_array(data, "|");
    printf("Message: %s\n", array[2]);
    client_event_private_message_received(array[0], array[2]);
}
