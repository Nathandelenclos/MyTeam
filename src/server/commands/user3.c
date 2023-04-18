/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** user3.c
*/

#include "server.h"
#include "stdbool.h"

/**
 * Create a new team
 * @param server - server_t struct
 * @param client - client_t struct
 * @param data - data received
 */
void create(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(LOGIN_SUCCESS, "test");
    send_packet(client->socket_fd, packet);
}

/**
 * List all the teams
 * @param server - server_t struct
 * @param client - client_t struct
 * @param data - data received
 */
void list_team(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(LIST_SUCCESS_CODE, "test");
    send_packet(client->socket_fd, packet);
}

/**
 * List all the channels of a team
 * @param server - server_t struct
 * @param client - client_t struct
 * @param data - data received
 */
void give_info(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(LOGIN_SUCCESS, "test");
    send_packet(client->socket_fd, packet);
}
