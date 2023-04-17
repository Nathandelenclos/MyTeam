/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** utils
*/

#include "server.h"


/**
 * Exit with error message.
 * @param string
 */
void perror_exit(const char *string)
{
    perror(string);
    exit_all(EXIT_FAILURE);
}

/**
 * Print help message.
 */
void help_init(void)
{
    printf("USAGE: ./myteams_server port\r\n");
    printf("\tport is the port number on which "
        "the server socket listens\r\n");
}

/**
 * Exit with free and is use for handle of SIGINT signal
 * @param code if 84 exit with 84 otherwise exit with 0.
 */
void exit_all(int code)
{
    FREE_ALL();
    exit(code == 84 ? 84 : 0);
}

/**
 * Get the length of an array.
 * @param array - array to get length.
 * @return - length of array.
 */
int len_array(string *array)
{
    int i = 0;

    for (; array[i]; i++);
    return i;
}

/**
 * create a client.
 * @param server_fd - server fd.
 * @return - client.
 */
client_t *create_client(int server_fd)
{
    client_t *client = MALLOC(sizeof(client_t));

    if (!client) {
        return NULL;
    }
    struct sockaddr_in address;
    client->len = sizeof(address);
    client->socket_fd = accept(server_fd,
        (struct sockaddr *)
            &address,
        &client->len);
    client->sockaddr = address;
    client->user = NULL;
    client->context = NONE;
    client->team = NULL;
    client->channel = NULL;
    client->thread = NULL;
    client->context_uuids = create_context_uuids();
    return client;
}
