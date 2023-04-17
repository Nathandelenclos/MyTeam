/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** Main
*/

#include "server.h"
#include "list.h"
#include <signal.h>

/**
 * Main function for Server.
 * @param ac Number of args.
 * @param av Array of args.
 * @return - EXIT_SUCCESS or EXIT_FAILURE.
 */
int main(int ac, char **av)
{
    if (ac != 2 || atoi(av[1]) == 0) {
        help_init();
        return 84;
    }
    signal(SIGINT, exit_all);
    server_t *server = create_server(atoi(av[1]));
    handle_client(server);
    FREE_ALL();
    return 0;
}
