/*
** EPITECH PROJECT, 2023
** myFTP
** File description:
** CommandManager
*/

#include "main.h"
#include "list.h"

/**
 * Close fd of user when he is disconnected.
 * @param server
 * @param client
 * @param valread
 */
void disconect_client(server_t *server, client_t *client, int valread)
{
    if (valread == 0) {
        printf("Client déconnecté : %s:%d\r\n",
            inet_ntoa(client->sockaddr.sin_addr),
            ntohs(client->sockaddr.sin_port));
        close(client->socket_fd);
        client->socket_fd = 0;
    }
}

/**
 *
 * @param server
 * @param client
 * @param cmd
 * @param data
 */
void exec_command(server_t *server, client_t *client, command cmd, socket_t
*socket)
{
    if (!cmd.auth_required || (cmd.auth_required && client->user) ) {
        cmd.function(server, client, socket->data);
    } else {
        dprintf(client->socket_fd, "530 you are not authenticate.\r\n");
    }
}

/**
 * Manage all commands of server by client.
 * @param server
 * @param client
 * @param valread
 * @param data
 */
void command_client(server_t *server, client_t *client, socket_t *socket)
{
    string buff;
    for (int i = 0; i < 14; ++i) {
        buff = strstr(socket->data, commands[i].name);
        if (buff && strncmp(buff, socket->data, strlen(commands[i].name)) == 0 &&
        client->context == commands[i].context) {
            return exec_command(server, client, commands[i], socket);
        }
    }
    dprintf(client->socket_fd, "500 unknown command !\r\n");
}
