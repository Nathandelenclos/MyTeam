/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** messages.c
*/

#include "client.h"
#include "logging_client.h"
#include "server.h"
#include "time.h"
#include "string.h"

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

/**
 * Message listener.
 * @param packet - Packet to read.
 */
void list_messages(packet_t *packet)
{
    string data = my_strdup(packet->data);
    char **array = str_to_word_array(data, "|");
    printf("[%s] User %s said %s\n", array[2], array[1], array[3]);
    struct tm tm_time = {0};
    sscanf(array[2], "%*s %*s %d %d:%d:%d %d",
            &tm_time.tm_mday, &tm_time.tm_hour,
            &tm_time.tm_min, &tm_time.tm_sec,
            &tm_time.tm_year);
    tm_time.tm_year -= 1900;
    tm_time.tm_mon += 3;
    time_t my_time = mktime(&tm_time);
    client_private_message_print_messages(array[0], my_time, array[3]);
}
