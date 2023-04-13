/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** use.c
*/

#include "server.h"
#include "stdbool.h"

/**
 * get the team by uuid.
 * @param teams - list of teams.
 * @param str - uuid.
 * @return - team.
 */
team_t *get_team_by_uuid(node *teams, string str)
{
    for (node *tmp = teams; tmp; tmp = tmp->next) {
        team_t *team = tmp->data;
        if (strcmp(team->uuid, str) == 0) {
            return team;
        }
    }
    return NULL;
}

/**
 * get the channel by uuid.
 * @param channels - list of channels.
 * @param str - uuid.
 * @return - channel.
 */
channel_t *get_channel_by_uuid(node *channels, string str)
{
    for (node *tmp = channels; tmp; tmp = tmp->next) {
        channel_t *channel = tmp->data;
        if (strcmp(channel->uuid, str) == 0) {
            return channel;
        }
    }
    return NULL;
}

/**
 * get the thread by uuid.
 * @param threads - list of threads.
 * @param str - uuid.
 * @return - thread.
 */
thread_t *get_thread_by_uuid(node *threads, string str)
{
    for (node *tmp = threads; tmp; tmp = tmp->next) {
        thread_t *thread = tmp->data;
        if (strcmp(thread->uuid, str) == 0) {
            return thread;
        }
    }
    return NULL;
}

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
 * use the context.
 * @param server - server info.
 * @param client - client info.
 * @param data - client command beginning by /use.
 */
void use(server_t *server, client_t *client, string data)
{
    if (!good_actions_use(server, client, data))
        return;
    char **command_parsed = str_to_word_array(data, "\"");
    client->context = NONE;
    client->data = NULL;
    if (command_parsed[1] != NULL) {
        client->context = TEAM;
        client->data = get_team_by_uuid(server->teams, command_parsed[1]);
    }
    if (len_array(command_parsed) >= 4 && command_parsed[3] != NULL) {
        team_t *team = client->data;
        client->context = CHANNEL;
        client->data = get_channel_by_uuid(team->channels, command_parsed[3]);
    }
    if (len_array(command_parsed) >= 6 && command_parsed[5] != NULL) {
        channel_t *channel = client->data;
        client->context = THREAD;
        client->data = get_thread_by_uuid(channel->threads, command_parsed[5]);
    }
    send_packet(client->socket_fd, create_packet(USE_SUCCESS, "You are now in the context."));
}
