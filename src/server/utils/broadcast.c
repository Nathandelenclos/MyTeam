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
        if (client->socket_fd != -1)
            len++;
        send_packet(client->socket_fd, packet);
    }
    return len;
}
