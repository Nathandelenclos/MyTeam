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

thread_t *new_thread(string title, string body)
{
    thread_t *thread = MALLOC(sizeof(thread_t));
    thread->title = my_strdup(title);
    thread->body = my_strdup(body);
    thread->uuid = new_uuid();
    thread->time = time(NULL);
    thread->replies = NULL;
    return thread;
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
    if (!is_subscribed(client->team, client->user)) {
        send_packet(client->socket_fd, create_packet(UNAUTHORIZED, client->team->uuid));
        return;
    }
    string *command = str_to_word_array(data, "\"");
    thread_t *thread = new_thread(command[1], command[3]);
    put_in_list(&client->channel->threads, thread);
    server_event_thread_created(client->channel->uuid, thread->uuid, client->user->uuid,
        thread->title, thread->body);
    string info = my_multcat(9,client->channel->uuid, "|", thread->uuid, "|", itoa(thread->time), "|",
        thread->title, "|", thread->body);
    send_packet(client->socket_fd, create_packet(CREATE_THREAD_SUCCESS,info));
    free(info);
    free_array(command);
}

