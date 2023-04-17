/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** user3.c
*/

#include "server.h"
#include "stdbool.h"

void create(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(LOGIN_SUCCESS, "test");
    send_packet(client->socket_fd, packet);
}

void list_team(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(LIST_SUCCESS_CODE, "test");
    send_packet(client->socket_fd, packet);
}

void give_info(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(LOGIN_SUCCESS, "test");
    send_packet(client->socket_fd, packet);
}

void give_user_info(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(LOGIN_SUCCESS, "test");
    send_packet(client->socket_fd, packet);
}
