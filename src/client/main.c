/*
** EPITECH PROJECT, 2023
** myTeams Client
** File description:
** main
*/

#include "list.h"
#include "network.h"

void user_action(fd_set *fds, int client_socket, int *is_running)
{
    if (FD_ISSET(0, fds)) {
        socket_t *socket = MALLOC(sizeof(socket_t));
        socket->data = MALLOC(sizeof(char ) * 1024);
        string buff = MALLOC(sizeof(char) * 1024);
        memset(buff, 0, sizeof(char) * 1024);
        memset(socket->data, 0, sizeof(char) * 1024);
        string end = NULL;
        while (end == NULL) {
            read(0, buff, 1024);
            strcat(socket->data, buff);
            end = strstr(socket->data, "\n");
        }
        FREE(buff);
        end[0] = '\0';
        if (socket->data[0] == 0) {
            *is_running = false;
        }
        socket->code = 200;
        send_socket(client_socket, socket);
        FREE(socket->data);
        FREE(socket);
    }
}

void server_action(fd_set *fds, int client_socket, int *is_running)
{
    if (FD_ISSET(client_socket, fds)) {
        socket_t *socket = get_read(client_socket);
        if (socket->code == 200) {
            dprintf(1, "%s", socket->data);
        }
        if (socket->code == 0) {
            *is_running = false;
        }
        FREE(socket);
    }
}

int main(int ac, char **av)
{
    int client_socket = create_socket();
    sockaddr_in_t server_address = create_sockaddr_in(atoi(av[2]), av[1]);
    int is_running = true;
    fd_set fd_grp;

    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("La connexion a échoué");
        exit(EXIT_FAILURE);
    }

    while (is_running) {
        FD_ZERO(&fd_grp);
        FD_SET(0, &fd_grp);
        FD_SET(client_socket, &fd_grp);
        int activity = select(client_socket + 1, &fd_grp, NULL, NULL,
            NULL);
        if ((activity < 0) && (errno != EINTR)) {
            printf("Erreur lors de la surveillance des sockets\n");
        }
        user_action(&fd_grp, client_socket, &is_running);
    }

    close(client_socket);
    return 0;
}
