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
int get_my_subscribe(server_t *server, client_t *client)
{
    int len = 0;
    for (node *tmp = server->teams; tmp; tmp = tmp->next) {
        team_t *team = tmp->data;
        if (is_subscribed(team, client->user)) {
            string info = my_multcat(8, client->user->uuid, "|", team->uuid,
                "|", team->name, "|", team->description, "|");
            send_packet(client->socket_fd,
                create_packet(SUBSCRIBED_USER_SUCCESS, info));
            free(info);
        }
    }
    return len;
}

/**
 * Get all the subscribers of a team.
 * @param server - server info.
 * @param team - team to check.
 * @return - string with all the subscribers.
 */
int get_subscribers(server_t *server, client_t *client, team_t *team)
{
    int len = 0;
    for (node *tmp = team->subscribers; tmp; tmp = tmp->next) {
        user_t *subscriber = tmp->data;
        string info = my_multcat(8, team->uuid, "|", subscriber->uuid,
            "|", subscriber->name, "|",
            is_active(server, subscriber) ? "1" : "0", "|");
        send_packet(client->socket_fd,
            create_packet(SUBSCRIBED_TEAM_SUCCESS, info));
        free(info);
        len++;
    }
    return len;
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
        send_packet(client->socket_fd,
            create_packet(ERROR, "Bad command"));
        return;
    }
    string *splited = str_to_word_array(data, "\"");
    if (len_array(splited) == 1) {
        get_my_subscribe(server, client);
    } else {
        get_subscribers(server, client,
            get_team_by_uuid(server->teams, splited[1]));
    }
    free_array(splited);
}
