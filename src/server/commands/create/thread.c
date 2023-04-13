/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** create.c
*/

#include "server.h"
#include "stdbool.h"
#include <time.h>

/**
 * Check if the command is good.
 * @param server - server.
 * @param client - client.
 * @param data - data.
 * @return - true or false.
 */
bool is_good_create_thread(server_t *server, client_t *client, string data)
{
    int nb_arg[] = {2, -1};
    if (check_args(data, nb_arg, "/create") == 1) {
        send_packet(client->socket_fd,create_packet(ERROR, "Bad command"));
        return false;
    }
    if (client->data == NULL) {
        send_packet(client->socket_fd,create_packet(ERROR, "You are not in a team."));
        return false;
    };
    return true;
}

/**
 * Create a new thread.
 * @param server - server.
 * @param client - client.
 * @param data - data.
 */
void create_thread(server_t *server, client_t *client, string data)
{
    if (!is_good_create_thread(server, client, data))
        return;
    char **command = str_to_word_array(data, "\"");
    channel_t *channel = ((channel_t *)client->data);
    thread_t *new_thread = MALLOC(sizeof(thread_t));
    new_thread->title = my_strdup(command[1]);
    new_thread->body = my_strdup(command[3]);
    new_thread->uuid = new_uuid();
    new_thread->time = time(NULL);
    new_thread->replies = NULL;
    put_in_list(&channel->threads, new_thread);
    server_event_thread_created(channel->uuid, new_thread->uuid, client->user->uuid,
        new_thread->title, new_thread->body);
    string info = my_multcat(9,channel->uuid, "|", new_thread->uuid, "|", client->user->uuid, "|",
        new_thread->title, "|", new_thread->body);
    send_packet(client->socket_fd, create_packet(CREATE_THREAD_SUCCESS,info));
    free(info);
}

