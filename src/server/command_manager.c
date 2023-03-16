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
 * No operation.
 * @param server
 * @param client
 * @param data
 */
void noop(server_t *server, client_t *client, string data)
{
    dprintf(client->socket_fd, "200 Command okay\r\n");
}

/**
 *
 * @param server
 * @param client
 * @param cmd
 * @param data
 */
void exec_command(server_t *server, client_t *client, command cmd, string data)
{
    if (!cmd.auth_required || (cmd.auth_required && client->auth) ) {
        cmd.function(server, client, data);
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
void command_client(server_t *server, client_t *client, int valread,
    string data)
{
    string buff;
    for (int i = 0; i < 14; ++i) {
        buff = strstr(data, commands[i].name);
        if (buff && strncmp(buff, data, strlen(commands[i].name)) == 0) {
            return exec_command(server, client, commands[i], data);
        }
    }
    dprintf(client->socket_fd, "500 unknown command !\r\n");
}
