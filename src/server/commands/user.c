/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** user commands
*/

#include "server.h"


void list_team(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(LIST_SUCCESS_CODE, "test");
    send_packet(client->socket_fd, packet);
}