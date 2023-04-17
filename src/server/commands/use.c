/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** use.c
*/

#include "server.h"
#include "stdbool.h"

/**
 * check if the command is good.
 * @param server - server info.
 * @param client - client info.
 * @param data - client command beginning by /use.
 * @return - true or false.
 */
bool good_actions_use(server_t *server, client_t *client, string data)
{
    int nb_arg[] = {0, 1, 2, 3, -1};
    if (check_args(data, nb_arg, "/use") == 1) {
        send_packet(client->socket_fd,create_packet(ERROR, "bad command"));
        return false;
    }
    return true;
}
/**
 * Set team at the client.
 * @param server - server info.
 * @param client - client info.
 * @param command_parsed - command parsed.
 * @return - true or false.
 */
bool set_team(server_t *server, client_t *client, string *command_parsed)
{
    if (len_array(command_parsed) >= 2 && command_parsed[1] != NULL) {
        client->context = TEAM;
        client->team = get_team_by_uuid(server->teams, command_parsed[1]);
        if (client->context_uuids->team_uuid != NULL)
            FREE(client->context_uuids->team_uuid);
        client->context_uuids->team_uuid = my_strdup(command_parsed[1]);
        if (client->team == NULL) {
            send_packet(client->socket_fd, create_packet(UNKNOW_TEAM, client->context_uuids->team_uuid));
            return false;
        }
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
    if (len_array(command_parsed) >= 4 && command_parsed[3] != NULL) {
        client->context = CHANNEL;
        if (client->team == NULL) {
            send_packet(client->socket_fd, create_packet(UNKNOW_TEAM, client->context_uuids->team_uuid));
            return false;
        }
        client->channel = get_channel_by_uuid(client->team->channels, command_parsed[3]);
        if (client->context_uuids->channel_uuid != NULL)
            FREE(client->context_uuids->channel_uuid);
        client->context_uuids->channel_uuid = my_strdup(command_parsed[3]);
        if (client->channel == NULL) {
            send_packet(client->socket_fd, create_packet(UNKNOW_CHANNEL, client->context_uuids->channel_uuid));
            return false;
        }
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
    if (len_array(command_parsed) >= 6 && command_parsed[5] != NULL) {
        client->context = THREAD;
        if (client->team == NULL) {
            send_packet(client->socket_fd, create_packet(UNKNOW_TEAM, client->context_uuids->team_uuid));
            return false;
        }
        if (client->channel == NULL) {
            send_packet(client->socket_fd, create_packet(UNKNOW_CHANNEL, client->context_uuids->channel_uuid));
            return false;
        }
        client->thread = get_thread_by_uuid(client->channel->threads, command_parsed[5]);
        if (client->context_uuids->thread_uuid != NULL)
            FREE(client->context_uuids->thread_uuid);
        client->context_uuids->thread_uuid = my_strdup(command_parsed[5]);
        if (client->thread == NULL) {
            send_packet(client->socket_fd, create_packet(UNKNOW_THREAD, client->context_uuids->thread_uuid));
            return false;
        }
    }
    return true;
}

/**
 * use the context.
 * @param server - server info.
 * @param client - client info.
 * @param data - client command beginning by /use.
 */
void use(server_t *server, client_t *client, string data)
{
    if (!good_actions_use(server, client, data))
        return;
    client->context = NONE;
    string *command_parsed = str_to_word_array(data, "\"");
    if (!set_team(server, client, command_parsed)) {
        send_packet(client->socket_fd, create_packet(USE_SUCCESS, "You are now in the NONE"));
        return;
    }
    if (!set_channel(server, client, command_parsed)) {
        send_packet(client->socket_fd, create_packet(USE_SUCCESS, "You are now in the TEAM"));
        return;
    }
    if (!set_thread(server, client, command_parsed)) {
        send_packet(client->socket_fd, create_packet(USE_SUCCESS, "You are now in the CHANNEL"));
        return;
    }
    send_packet(client->socket_fd, create_packet(USE_SUCCESS, "You are now in the THREAD"));
    free_array(command_parsed);
}
