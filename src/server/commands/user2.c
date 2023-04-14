/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** user2.c
*/

#include "server.h"
#include "stdbool.h"

void subscribe(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(LOGIN_SUCCESS, "test");
    send_packet(client->socket_fd, packet);
}

void subscribed(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(LOGIN_SUCCESS, "test");
    send_packet(client->socket_fd, packet);
}

void unsubscribe(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(LOGIN_SUCCESS, "test");
    send_packet(client->socket_fd, packet);
}
