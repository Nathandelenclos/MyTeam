/*
** EPITECH PROJECT, 2023
** myFtp
** File description:
** Main
*/

#include "main.h"
#include "list.h"
#include <signal.h>

/**
 * Main function.
 * @param ac Number of args.
 * @param av Array of args.
 * @return
 */
int main(int ac, char **av)
{
    if (ac != 3 || atoi(av[1]) == 0 || exist_dir(av[2]) == 0) {
        help_init();
        return 84;
    }
    signal(SIGINT, exit_all);
    server_t *server = create_server(atoi(av[1]), av[2]);
    handle_client(server);
    return 0;
}
