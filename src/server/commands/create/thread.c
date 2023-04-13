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
    if (client->channel == NULL) {
        send_packet(client->socket_fd,create_packet(UNKNOW_CHANNEL, ""));
        return false;
    };
    char **command = str_to_word_array(data, "\"");
    for (node *tmp = client->channel->threads; tmp; tmp = tmp->next) {
        thread_t *thread = ((thread_t *)tmp->data);
        if (strcmp(thread->title, command[1]) == 0) {
            send_packet(client->socket_fd,
                create_packet(ALREADY_EXIST, ""));
            return false;
        }
    }
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
    thread_t *new_thread = MALLOC(sizeof(thread_t));
    new_thread->title = my_strdup(command[1]);
    new_thread->body = my_strdup(command[3]);
    new_thread->uuid = new_uuid();
    new_thread->time = time(NULL);
    new_thread->replies = NULL;
    put_in_list(&client->channel->threads, new_thread);
    server_event_thread_created(client->channel->uuid, new_thread->uuid, client->user->uuid,
        new_thread->title, new_thread->body);
    string info = my_multcat(9,client->channel->uuid, "|", new_thread->uuid, "|", itoa(new_thread->time), "|",
    new_thread->title, "|", new_thread->body);
    send_packet(client->socket_fd, create_packet(CREATE_THREAD_SUCCESS,info));
    free(info);
}

