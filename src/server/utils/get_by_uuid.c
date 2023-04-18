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
 * Check if the user is active.
 * @param server - server info.
 * @param user - user to check.
 * @return - true if the user is active, false otherwise.
 */
bool is_active(server_t *server, user_t *user)
{
    for (node *tmp = server->clients; tmp; tmp = tmp->next) {
        client_t *client = tmp->data;
        if (client->user == user) {
            return true;
        }
    }
    return false;
}
