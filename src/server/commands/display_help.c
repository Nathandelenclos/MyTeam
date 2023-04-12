/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** display_help.c
*/

#include <fcntl.h>
#include "server.h"
#include "stdbool.h"
#include "commands.h"

void display_help(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(SUCCESS,"Help");
    send_packet(client->socket_fd, packet);
}
