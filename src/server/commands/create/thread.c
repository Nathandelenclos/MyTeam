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
 * @param client - client.
 * @param data - data.
 * @return - true or false.
 */
bool is_good_context_thread(client_t *client)
{
    if (client->team == NULL) {
        send_packet(client->socket_fd,create_packet(UNKNOW_TEAM,
            client->context_uuids->team_uuid));
        return false;
    }
    if (client->channel == NULL) {
        send_packet(client->socket_fd,create_packet(UNKNOW_CHANNEL,
            client->context_uuids->channel_uuid));
        return false;
    }
    return true;
}

/**
 * Check if the thread already exist.
 * @param client - client.
 * @param data - data.
 * @return - true or false.
 */
bool already_exist_thread(client_t *client, string data)
{
    char **command = str_to_word_array(data, "\"");
    for (node *tmp = client->channel->threads; tmp; tmp = tmp->next) {
        thread_t *thread = ((thread_t *)tmp->data);
        if (strcmp(thread->title, command[1]) == 0) {
            send_packet(client->socket_fd,
                create_packet(ALREADY_EXIST, ""));
            free_array(command);
            return false;
        }
    }
    free_array(command);
    return true;
}

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
    if (!is_good_context_thread(client))
        return false;
    if (!already_exist_thread(client, data))
        return false;
    return true;
}

thread_t *new_thread(string title, string body, user_t *user)
{
    thread_t *thread = MALLOC(sizeof(thread_t));
    thread->title = my_strdup(title);
    thread->body = my_strdup(body);
    thread->user = user;
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
        send_packet(client->socket_fd, create_packet(UNAUTHORIZED,
            "You are not subscribed to this team."));
        return;
    }
    string *command = str_to_word_array(data, "\"");
    thread_t *thread = new_thread(command[1], command[3], client->user);
    put_in_list(&client->channel->threads, thread);
    server_event_thread_created(client->channel->uuid, thread->uuid,
        client->user->uuid,thread->title, thread->body);
    string info = my_multcat(9,thread->uuid, "|", client->user->uuid, "|",
        itoa(thread->time), "|", thread->title, "|", thread->body);
    send_packet(client->socket_fd, create_packet(CREATE_THREAD_SUCCESS,
        info));
    broadcast_subscribed_logged(server, client->team, create_packet(
        THREAD_CREATED, info));
    free(info);
    free_array(command);
}
