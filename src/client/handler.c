/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** handler
*/

#include "client.h"
#include "list.h"
#include "my.h"
#include <errno.h>

/**
 * Loop for actions.
 * @param client_socket - Socket of client.
 */
void loop_actions(int client_socket)
{
    int is_running = true;
    fd_set fds;
    while (is_running) {
        FD_ZERO(&fds);
        FD_SET(0, &fds);
        FD_SET(client_socket, &fds);
        int activity = select(client_socket + 1, &fds, NULL, NULL,
            NULL);
        if ((activity < 0) && (errno != EINTR)) {
            printf("Erreur lors de la surveillance des sockets\n");
        }
        user_action(&fds, client_socket, &is_running);
        server_action(&fds, client_socket, &is_running);
    }
}

/**
 * Execute the server action
 * @param socket - packet_t struct
 */
void exec_server_action(packet_t *socket)
{
    for (int i = 0; listeners[i].code != 0; i++) {
        if (listeners[i].code == socket->code) {
            listeners[i].func(socket);
            return;
        }
    }
}

/**
 * Handle server actions.
 * @param fds - Groups of file descriptors.
 * @param client_socket  - Socket of client.
 * @param is_running - Is running.
 */
void server_action(fd_set *fds, int client_socket, int *is_running)
{
    if (FD_ISSET(client_socket, fds)) {
        packet_t *socket = read_packet(client_socket);
        if (socket == NULL) {
            *is_running = false;
            return;
        }
        exec_server_action(socket);
        FREE(socket);
    }
}

/**
 * Handle user actions.
 * @param fds - Groups of file descriptors.
 * @param client_socket - Socket of client.
 * @param is_running - Is running.
 */
void user_action(fd_set *fds, int client_socket, int *is_running)
{
    if (FD_ISSET(0, fds)) {
        packet_t *socket = user_read();
        if (socket == NULL) {
            *is_running = false;
            return;
        }
        socket->len = strlen(socket->data);
        socket->code = 200;
        string data = socket->data;
        send_packet(client_socket, socket);
        FREE(data);
    }
}

/**
 * Read user input.
 * @return - Return packet.
 */
packet_t *user_read(void)
{
    packet_t *socket = MALLOC(sizeof(packet_t));
    socket->data = MALLOC(sizeof(char ) * 1024);
    string buff = MALLOC(sizeof(char) * 1024);
    memset(buff, 0, sizeof(char) * 1024);
    memset(socket->data, 0, sizeof(char) * 1024);
    string end = NULL;
    while (end == NULL) {
        if (read(0, buff, 1024) <= 0) {
            FREE(buff);
            FREE(socket->data);
            FREE(socket);
            return NULL;
        };
        strcat(socket->data, buff);
        end = strstr(socket->data, "\n");
    }
    FREE(buff);
    end[0] = '\0';
    return socket;
}
