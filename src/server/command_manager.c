/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** CommandManager
*/

#include "server.h"
#include "commands.h"
#include "list.h"
#include "network.h"

/**
 * Close fd of user when he is disconnected.
 * @param server - server.
 * @param client - client.
 */
void disconect_client(server_t *server, client_t *client)
{
    printf("Client déconnecté : %s:%d\r\n",
        inet_ntoa(client->sockaddr.sin_addr),
        ntohs(client->sockaddr.sin_port));
    close(client->socket_fd);
    delete_in_list(&server->clients, client);
}

/**
 * Execute command.
 * @param server - server.
 * @param client - client.
 * @param cmd - command.
 * @param data - data of command.
 */
void exec_command(server_t *server, client_t *client, command cmd, packet_t
*socket)
{
    if (!cmd.auth_required || (cmd.auth_required && client->user)) {
        cmd.function(server, client, socket->data);
    } else {
        send_packet(client->socket_fd,
            create_packet(UNAUTHORIZED, "You are not logged in."));
    }
}

/**
 * Manage all commands of server by client.
 * @param server - server.
 * @param client - client.
 * @param data - data of command.
 */
void command_client(server_t *server, client_t *client, packet_t *packet)
{
    string buff;
    for (int i = 0; commands[i].function != NULL; ++i) {
        buff = strstr(packet->data, commands[i].name);
        if (buff && strncmp(buff, packet->data, strlen(commands[i].name)) == 0
            && (client->context == commands[i].context ||
            commands[i].context == ANY)) {
            return exec_command(server, client, commands[i], packet);
        }
    }
    send_packet(client->socket_fd,
        create_packet(UNFOUND, "Command not found."));
}
