/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** Server Manager
*/

#include "server.h"
#include "list.h"

/**
 * Handle server actions.
 * @param server - Server to handle.
 */
void stop_server(server_t *server, bool *is_running)
{
    if (FD_ISSET(0, &server->readfds)) {
        char *buffer = NULL;
        size_t size = 0;
        ssize_t ret = getline(&buffer, &size, stdin);
        if (ret == -1 || strcmp(buffer, "exit\n") == 0) {
            *is_running = false;
        }
        free(buffer);
    }
}

/**
 * Handle client actions.
 * @param server - Server to handle.
 * @param client - Client to handle.
 * @return - True if client is still connected, false otherwise.
 */
bool action(server_t *server, client_t *client)
{
    if (FD_ISSET(client->socket_fd, &server->readfds)) {
        packet_t *socket = read_packet(client->socket_fd);
        if (socket == NULL && client->user != NULL) {
            disconect_client(server, client);
            string info = my_multcat(3, client->user->uuid, "|",
                client->user->name);
            broadcast_logged(server, create_packet(LOGOUT_SUCCESS, info));
            server_event_user_logged_out(client->user->uuid);
            free(info);
            return false;
        } else if (socket == NULL) {
            disconect_client(server, client);
            return false;
        }
        command_client(server, client, socket);
        FREE(socket);
        return false;
    }
    return true;
}

/**
 * Handle message of user and execute commands.
 * @param server - Server to handle.
 */
void read_action(server_t *server, bool *is_running)
{
    client_t *tmp_client;
    stop_server(server, is_running);
    if (!(*is_running))
        return;
    for (node *tmp = server->clients; tmp; tmp = tmp->next) {
        tmp_client = tmp->data;
        if (!action(server, tmp_client))
            return;
    }
}
