/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** utils
*/

#include "server.h"
#include <dirent.h>

/**
 * Send packet to all clients.
 * @param server - server to send packet.
 * @param packet - packet to send.
 * @return - Return number of clients.
 */
int broadcast(server_t *server, packet_t *packet)
{
    int len = 0;
    for (node *tmp = server->clients; tmp; tmp = tmp->next) {
        client_t *client = tmp->data;
        len++;
        send_packet(client->socket_fd, packet);
    }
    return len;
}

/**
 * Send packet to all logged clients.
 * @param server - server to send packet.
 * @param packet - packet to send.
 * @return - Return number of clients.
 */
int broadcast_logged(server_t *server, packet_t *packet)
{
    int len = 0;
    for (node *tmp = server->clients; tmp; tmp = tmp->next) {
        client_t *client = tmp->data;
        if (client->user != NULL) {
            len++;
            send_packet(client->socket_fd, create_packet(packet->code,
                packet->data));
        }
    }
    FREE(packet);
    return len;
}

/**
 * Send packet to all subscribed clients.
 * @param server - server to send packet.
 * @param team - team to send packet.
 * @param packet - packet to send.
 * @return - Return number of clients.
 */
int broadcast_subscribed_logged(server_t *server, team_t *team, packet_t *packet)
{
    int len = 0;
    for (node *tmp = server->clients; tmp; tmp = tmp->next) {
        client_t *client = tmp->data;
        if (client->user != NULL && is_subscribed(team, client->user)) {
            len++;
            send_packet(client->socket_fd, create_packet(packet->code,
                packet->data));
        }
    }
    FREE(packet);
    return len;
}