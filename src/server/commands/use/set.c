/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** use.c
*/

#include "server.h"
#include "stdbool.h"

/**
 * Set team at the client.
 * @param server - server info.
 * @param client - client info.
 * @param command_parsed - command parsed.
 * @return - true or false.
 */
bool set_team(server_t *server, client_t *client, string *command_parsed)
{
    if (len_array(command_parsed) < 2)
        return false;
    if (command_parsed[1] != NULL) {
        client->context = TEAM;
        client->team = get_team_by_uuid(server->teams, command_parsed[1]);
        if (client->context_uuids->team_uuid != NULL)
            FREE(client->context_uuids->team_uuid);
        client->context_uuids->team_uuid = my_strdup(command_parsed[1]);
        if (client->team == NULL) {
            client->context = NONE;
            send_packet(client->socket_fd,
                create_packet(UNKNOW_TEAM, client->context_uuids->team_uuid));
            return false;
        }
    }
    return true;
}

bool set_channel_second_part(client_t *client)
{
    if (client->channel == NULL) {
        client->context = TEAM;
        send_packet(client->socket_fd, create_packet(UNKNOW_CHANNEL,
            client->context_uuids->channel_uuid));
        return false;
    }
    return true;
}

/**
 * Set channel at the client.
 * @param server - server info.
 * @param client - client info.
 * @param command_parsed - command parsed.
 * @return - true or false.
 */
bool set_channel(server_t *server, client_t *client, string *command_parsed)
{
    if (len_array(command_parsed) < 4)
        return false;
    if (command_parsed[3] != NULL) {
        client->context = CHANNEL;
        if (client->team == NULL) {
            send_packet(client->socket_fd,
                create_packet(UNKNOW_TEAM, client->context_uuids->team_uuid));
            return false;
        }
        client->channel = get_channel_by_uuid(client->team->channels,
            command_parsed[3]);
        if (client->context_uuids->channel_uuid != NULL)
            FREE(client->context_uuids->channel_uuid);
        client->context_uuids->channel_uuid = my_strdup(command_parsed[3]);
        if (!set_channel_second_part(client))
            return false;
    }
    return true;
}

/**
 * Set thread at the client.
 * @param server - server info.
 * @param client - client info.
 * @param command_parsed - command parsed.
 * @return - true or false.
 */
bool set_thread_second_part(server_t *server, client_t *client,
    string *command_parsed)
{
    client->thread = get_thread_by_uuid(client->channel->threads,
        command_parsed[5]);
    if (client->context_uuids->thread_uuid != NULL)
        FREE(client->context_uuids->thread_uuid);
    client->context_uuids->thread_uuid = my_strdup(command_parsed[5]);
    if (client->thread == NULL) {
        client->context = CHANNEL;
        send_packet(client->socket_fd, create_packet(UNKNOW_THREAD,
            client->context_uuids->thread_uuid));
        return false;
    }
    return true;
}

/**
 * Set thread at the client.
 * @param server - server info.
 * @param client - client info.
 * @param command_parsed - command parsed.
 * @return - true or false.
 */
bool set_thread(server_t *server, client_t *client, string *command_parsed)
{
    if (len_array(command_parsed) < 6)
        return false;
    if (command_parsed[5] != NULL) {
        client->context = THREAD;
        if (client->team == NULL) {
            client->context = NONE;
            send_packet(client->socket_fd,
                create_packet(UNKNOW_TEAM, client->context_uuids->team_uuid));
            return false;
        }
        if (client->channel == NULL) {
            client->context = TEAM;
            send_packet(client->socket_fd, create_packet(UNKNOW_CHANNEL,
                client->context_uuids->channel_uuid));
            return false;
        }
        if (!set_thread_second_part(server, client, command_parsed))
            return false;
    }
    return true;
}
