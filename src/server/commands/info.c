/*
** EPITECH PROJECT, 2023
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** info.c
*/

#include "server.h"

/**
 * Info of the current user.
 * @param server - server_t struct
 * @param client - client_t struct
 * @param data - data
 */
void info_user(server_t *server, client_t *client, string data)
{
    string info = my_multcat(5, client->user->uuid, "|", client->user->name,
        "|",
        is_active(server, client->user) ? "1" : "0");
    send_packet(client->socket_fd, create_packet(INFO_USER_SUCCESS, info));
    free(info);
}

/**
 * Info of the current team.
 * @param server - server_t struct
 * @param client - client_t struct
 * @param data - data
 */
void info_team(server_t *server, client_t *client, string data)
{
    if (!check_context(client, true, false, false)) {
        return;
    }
    string info = my_multcat(5, client->team->uuid, "|", client->team->name,
        "|",
        client->team->description);
    send_packet(client->socket_fd, create_packet(INFO_TEAM_SUCCESS, info));
    free(info);
}

/**
 * Info of the current channel.
 * @param server - server_t struct
 * @param client - client_t struct
 * @param data - data
 */
void info_channel(server_t *server, client_t *client, string data)
{
    if (!check_context(client, true, true, false)) {
        return;
    }
    string info = my_multcat(5, client->channel->uuid, "|",
        client->channel->name, "|", client->channel->description);
    send_packet(client->socket_fd, create_packet(INFO_CHANNEL_SUCCESS, info));
    free(info);
}

/**
 * Info of the current thread.
 * @param server - server_t struct
 * @param client - client_t struct
 * @param data - data
 */
void info_thread(server_t *server, client_t *client, string data)
{
    if (!check_context(client, true, true, true)) {
        return;
    }
    string info = my_multcat(9, client->thread->uuid, "|",
        client->thread->user->uuid, "|", itoa(client->thread->time), "|",
        client->thread->title, "|", client->thread->body);
    send_packet(client->socket_fd, create_packet(INFO_THREAD_SUCCESS, info));
    free(info);
}
