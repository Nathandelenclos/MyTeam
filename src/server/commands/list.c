/*
** EPITECH PROJECT, 2023
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** list.c
*/

#include "server.h"

/**
 * Check if the client is in the right context
 * @param client - client_t struct
 * @param team - bool
 * @param channel - bool
 * @param thread - bool
 * @return bool
 */
bool check_context(client_t *client, bool team, bool channel, bool thread)
{
    if (team && client->team == NULL) {
        send_packet(client->socket_fd, create_packet(UNKNOW_TEAM,
            client->context_uuids->team_uuid));
        return false;
    }
    if (channel && client->channel == NULL) {
        send_packet(client->socket_fd, create_packet(UNKNOW_CHANNEL,
            client->context_uuids->channel_uuid));
        return false;
    }
    if (thread && client->thread == NULL) {
        send_packet(client->socket_fd, create_packet(UNKNOW_THREAD,
            client->context_uuids->thread_uuid));
        return false;
    }
    return true;
}

/**
 * List all the teams
 * @param server - server_t struct
 * @param client - client_t struct
 * @param data - data
 */
void list_teams(server_t *server, client_t *client, string data)
{
    for (node *tmp = server->teams; tmp; tmp = tmp->next) {
        team_t *team = tmp->data;
        string info = my_multcat(5, team->uuid, "|", team->name,
            "|", team->description);
        send_packet(client->socket_fd,
            create_packet(LIST_TEAMS_SUCCESS, info));
        free(info);
    }
}

/**
 * List all the channels
 * @param server - server_t struct
 * @param client - client_t struct
 * @param data - data
 */
void list_channels(server_t *server, client_t *client, string data)
{
    if (!check_context(client, true, false, false))
        return;
    for (node *tmp = client->team->channels; tmp; tmp = tmp->next) {
        channel_t *channel = tmp->data;
        string info = my_multcat(5, channel->uuid, "|", channel->name,
            "|", channel->description);
        send_packet(client->socket_fd,
            create_packet(LIST_CHANNEL_SUCCESS, info));
        free(info);
    }
}

/**
 * List all the threads
 * @param server - server_t struct
 * @param client - client_t struct
 * @param data - data
 */
void list_thread(server_t *server, client_t *client, string data)
{
    if (!check_context(client, true, true, false))
        return;
    for (node *tmp = client->channel->threads; tmp; tmp = tmp->next) {
        thread_t *thread = tmp->data;
        string info = my_multcat(9, thread->uuid, "|", thread->user->uuid,
            "|", itoa(thread->time), "|", thread->title, "|", thread->body);
        send_packet(client->socket_fd,
            create_packet(LIST_THREAD_SUCCESS, info));
        free(info);
    }
}

/**
 * List all the replies
 * @param server - server_t struct
 * @param client - client_t struct
 * @param data - data
 */
void list_reply(server_t *server, client_t *client, string data)
{
    if (!check_context(client, true, true, true))
        return;
    for (node *tmp = client->thread->replies; tmp; tmp = tmp->next) {
        message_t *message = tmp->data;
        string info = my_multcat(7, client->thread->uuid, "|",
            message->user->uuid, "|", itoa(message->time),
            "|", message->data);
        send_packet(client->socket_fd,
            create_packet(LIST_REPLY_SUCCESS, info));
        free(info);
    }
}
