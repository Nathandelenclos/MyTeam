/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** suscribed.c
*/

#include "server.h"
#include "stdbool.h"

/**
 * Get all the teams where the user is subscribed.
 * @param server - server info.
 * @param client - client info.
 * @return - string with all the teams.
 */
string get_my_subscribe(server_t *server, client_t *client)
{
    string info = "";
    for (node *tmp = server->teams; tmp; tmp = tmp->next) {
        team_t *team = tmp->data;
        if (is_subscribed(team, client->user)) {
            string temp = my_multcat(3, info, team->uuid, "|");
            free(info);
            info = temp;
        }
    }
    return info;
}

/**
 * Get all the subscribers of a team.
 * @param team - team to check.
 * @return - string with all the subscribers.
 */
string get_subscribers(team_t *team)
{
    string info = "";
    for (node *tmp = team->subscribers; tmp; tmp = tmp->next) {
        user_t *subscriber = tmp->data;
        string temp = my_multcat(3, info, subscriber->uuid, "|");
        free(info);
        info = temp;
    }
    return info;
}

/**
 * Get all the subscribers of a team or all the teams where
 * the user is subscribed.
 * @param server - server info.
 * @param client - client info.
 * @param data - command data.
 */
void subscribed(server_t *server, client_t *client, string data)
{
    int nb_arg[] = {0, 1, -1};
    if (check_args(data, nb_arg, "/subscribed") == 1) {
        send_packet(client->socket_fd, create_packet(ERROR, "Bad command"));
        return;
    }
    string info = "";
    string *splited = str_to_word_array(data, "\"");
    if (len_array(splited) == 1) {
        info = get_my_subscribe(server, client);
    } else {
        info = get_subscribers(get_team_by_uuid(server->teams, splited[1]));
    }
    send_packet(client->socket_fd, create_packet(SUBSCRIBED_SUCCESS, info));
    free_array(splited);
    free(info);
}
