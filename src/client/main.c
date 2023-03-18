/*
** EPITECH PROJECT, 2023
** myTeams Client
** File description:
** main
*/

#include <signal.h>
#include "list.h"
#include "network.h"
#include "client.h"

void help_init(void)
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\tip\tis the server ip address on which"
           " the server socket listens.\n");
    printf("\tport\tis the port number on which the server socket listens.\n");
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
    if (connect(client_socket, (struct sockaddr*)&server_address,
        sizeof(server_address)) < 0) {
        perror("La connexion a échoué");
        exit(EXIT_FAILURE);
    }
    loop_actions(client_socket);
    FREE_ALL();
    close(client_socket);
    return EXIT_SUCCESS;
}
