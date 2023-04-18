/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** utils
*/

#include "server.h"

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

/**
 * Create a new context uuids.
 * @return - context uuids.
 */
int sort_message(void *a, void *b)
{
    message_t *message_a = (message_t *)a;
    message_t *message_b = (message_t *)b;

    return message_b->time - message_a->time;
}
