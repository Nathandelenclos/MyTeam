/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** suscribe.c
*/

#include "server.h"
#include "stdbool.h"

/**
 * @brief Check if a user is subscribed to a team
 * @param team - team to check.
 * @param user - user to check.
 * @return - true if the user is subscribed to the team, false otherwise.
 */
bool is_subscribed(team_t *team, user_t *user)
{
    for (node *tmp = team->subscribers; tmp; tmp = tmp->next) {
        user_t *subscriber = tmp->data;
        if (strcmp(subscriber->uuid, user->uuid) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Subscribe a user to a team.
 * @param server - server.
 * @param client - client.
 * @param data - data.
 */
void subscribe(server_t *server, client_t *client, string data)
{
    int nb_arg[] = {1, -1};
    if (check_args(data, nb_arg, "/subscribe") == 1) {
        send_packet(client->socket_fd, create_packet(ERROR, "Bad command"));
        return;
    }
    string *splited = str_to_word_array(data, "\"");
    for (node *tmp = server->teams; tmp; tmp = tmp->next) {
        team_t *team = tmp->data;
        if (strcmp(team->uuid, splited[1]) == 0) {
            put_in_list(&team->subscribers, client->user);
            server_event_user_subscribed(team->uuid, client->user->uuid);
            string info = my_multcat(3, client->user->uuid, "|", team->uuid);
            send_packet(client->socket_fd,
                create_packet(SUBSCRIBE_SUCCESS, info));
            free(info);
            free_array(splited);
            return;
        }
    }
    send_packet(client->socket_fd, create_packet(UNKNOW_TEAM, splited[1]));
    free_array(splited);
}

/**
 * Unsubscribe user in team
 * @param team - team.
 * @param client - client.
 * @param splited - command splited.
 * @return - true or false.
 */
bool unsubscribe_second_part(team_t *team, client_t *client, string *splited)
{
    if (!is_subscribed(team, client->user)) {
        send_packet(client->socket_fd,
            create_packet(ERROR, "You are not subscribe at this team !"));
        return false;
    }
    delete_in_list(&team->subscribers, client->user);
    server_event_user_unsubscribed(team->uuid, client->user->uuid);
    string info = my_multcat(3, client->user->uuid, "|", team->uuid);
    send_packet(client->socket_fd, create_packet(UNSUBSCRIBE_SUCCESS, info));
    free(info);
    return true;
}

/**
 * @brief Unsubscribe a user to a team.
 * @param server - server.
 * @param client - client.
 * @param data - data.
 */
void unsubscribe(server_t *server, client_t *client, string data)
{
    int nb_arg[] = {1, -1};
    if (check_args(data, nb_arg, "/unsubscribe") == 1) {
        send_packet(client->socket_fd, create_packet(ERROR, "Bad command"));
        return;
    }
    string *splited = str_to_word_array(data, "\"");
    for (node *tmp = server->teams; tmp; tmp = tmp->next) {
        team_t *team = tmp->data;
        if (strcmp(team->uuid, splited[1]) == 0 &&
            unsubscribe_second_part(team, client, splited)) {
            free_array(splited);
            return;
        }
    }
    send_packet(client->socket_fd, create_packet(UNKNOW_TEAM, splited[1]));
    free_array(splited);
}
