/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** messages_command.c
*/

#include "server.h"
#include "stdbool.h"

void message_exchanged(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(LIST_MESSAGES_SUCCESS_CODE, "test");
    send_packet(client->socket_fd, packet);
}
