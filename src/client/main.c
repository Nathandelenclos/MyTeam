/*
** EPITECH PROJECT, 2023
** myTeams Client
** File description:
** main
*/

#include <signal.h>
#include "list.h"
#include "network.h"

void help_init(void)
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\tip\tis the server ip address on which the server socket listens.\n");
    printf("\tport\tis the port number on which the server socket listens.\n");
}

socket_t *user_read(void)
{
    socket_t *socket = MALLOC(sizeof(socket_t));
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


void user_action(fd_set *fds, int client_socket, int *is_running)
{
    if (FD_ISSET(0, fds)) {
        socket_t *socket = user_read();
        if (socket == NULL) {
            *is_running = false;
            return;
        }
        printf("client send: %s\n", socket->data);
        socket->len = strlen(socket->data);
        printf("len: %d\n", socket->len);
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
        if (socket->code == 200)
            dprintf(1, "%s\n", socket->data);
        if (socket->code == 0) {
            *is_running = false;
        }
        FREE(socket);
    }
}

void exit_all(int code)
{
    FREE_ALL();
    exit(code == 84 ? 84 : 0);
}

int main(int ac, char **av)
{
    signal(SIGINT, exit_all);
    if (ac != 3 && atoi(av[2]) <= 0) {
        help_init();
        return EXIT_FAILURE;
    }
    int client_socket = create_socket();
    sockaddr_in_t server_address = create_sockaddr_in(atoi(av[2]), av[1]);
    int is_running = true;
    fd_set fds;
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("La connexion a échoué");
        exit(EXIT_FAILURE);
    }
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
    FREE_ALL();
    close(client_socket);
    return EXIT_SUCCESS;
}
