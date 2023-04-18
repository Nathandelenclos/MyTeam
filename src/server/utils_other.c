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

user_t *correct_uuid_user(string uuid, server_t *server)
{
    if (strlen(uuid) != 36)
        return NULL;
    for (node *users = server->users; users != NULL;
            users = users->next) {
        user_t *user = (user_t *)users->data;
        if (user != NULL && strcmp(user->uuid, uuid) == 0) {
            return user;
        }
    }
    return NULL;
}

/**
 * Check if a uuid exists.
 * @param uuid - uuid to check
 * @param server - server
 * @return user_t structure if exist otherwise NULL
 */
client_t *correct_uuid(string uuid, server_t *server)
{
    if (strlen(uuid) != 36)
        return NULL;
    for (node *clients = server->clients; clients != NULL;
    clients = clients->next) {
        client_t *client = (client_t *)clients->data;
        if (client != NULL && client->user && client->user->uuid != NULL &&
            strcmp(client->user->uuid, uuid) == 0) {
            return client;
        }
    }
    return NULL;
}
