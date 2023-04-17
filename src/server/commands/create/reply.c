/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** create/team.c
*/

#include "server.h"
#include "stdbool.h"
#include <time.h>

/**
 * Check if the context is good.
 * @param client - client.
 * @return - true or false.
 */
bool id_good_context_reply(client_t *client)
{
    if (client->team == NULL) {
        send_packet(client->socket_fd,create_packet(UNKNOW_TEAM, client->context_uuids->team_uuid));
        return false;
    }
    if (client->channel == NULL) {
        send_packet(client->socket_fd,create_packet(UNKNOW_CHANNEL, client->context_uuids->channel_uuid));
        return false;
    }
    if (client->thread == NULL) {
        send_packet(client->socket_fd,create_packet(UNKNOW_THREAD, client->context_uuids->thread_uuid));
        return false;
    }
    return true;
}

/**
 * Check if the command is good.
 * @param server - server.
 * @param client - client.
 * @param data - data.
 * @return - true or false.
 */
bool is_good_create_reply(server_t *server, client_t *client, string data)
{
    int nb_arg[] = {1, -1};
    if (check_args(data, nb_arg, "/create") == 1) {
        send_packet(client->socket_fd,create_packet(ERROR, "Bad command"));
        return false;
    }
    if (!is_subscribed(client->team, client->user)) {
        send_packet(client->socket_fd,create_packet(UNAUTHORIZED, "You are not subscribed to this team."));
        return false;
    }
    if (!id_good_context_reply(client))
        return false;
    return true;
}

/**
 * Create a new reply.
 * @param server - server.
 * @param client - client.
 * @param data - data.
 */
void create_reply(server_t *server, client_t *client, string data)
{
    if (!is_good_create_reply(server, client, data))
        return;
    string *command_parsed = str_to_word_array(data, " ");
    message_t *new_reply = MALLOC(sizeof(message_t));
    new_reply->data = my_strdup(command_parsed[1]);
    new_reply->uuid = new_uuid();
    new_reply->time = time(NULL);
    new_reply->user = client->user;
    put_in_list(&client->thread->replies, new_reply);
    string info = my_multcat(7, client->thread->uuid, "|",  client->user->uuid, "|",
        itoa(new_reply->time), "|", new_reply->data);
    server_event_reply_created(client->thread->uuid, client->user->uuid,
        new_reply->data);
    send_packet(client->socket_fd,create_packet(CREATE_REPLY_SUCCESS, info));
    free_array(command_parsed);
    free(info);
}