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

void server_action(fd_set *fds, int client_socket, int *is_running)
{
    if (FD_ISSET(client_socket, fds)) {
        packet_t *socket = read_packet(client_socket);
        if (socket == NULL) {
            *is_running = false;
            return;
        }
        for (int i = 0; listeners[i].code != 0; i++) {
            if (listeners[i].code == socket->code) {
                listeners[i].func(socket);
                break;
            }
        }
        FREE(socket);
    }
}

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
        send_packet(client_socket, socket);
        FREE(socket->data);
        FREE(socket);
    }
}

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
