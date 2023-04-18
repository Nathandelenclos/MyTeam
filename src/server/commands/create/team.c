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
 * Check if the team already exist.
 * @param server - server.
 * @param client - client.
 * @param data - data.
 * @return - true or false.
 */
bool already_exist_team(server_t *server, client_t *client, string data)
{
    string *command = str_to_word_array(data, "\"");
    for (node *tmp = server->teams; tmp; tmp = tmp->next) {
        team_t *team = tmp->data;
        if (strcmp(team->name, command[1]) == 0) {
            send_packet(client->socket_fd, create_packet(ALREADY_EXIST, ""));
            return false;
        }
    }
    free_array(command);
    return true;
}

/**
 * Check if the command is good.
 * @param server - server.
 * @param client - client.
 * @param data - data.
 * @return - true or false.
 */
bool is_good_create_team(server_t *server, client_t *client, string data)
{
    int nb_arg[] = {2, -1};
    if (check_args(data, nb_arg, "/create") == 1) {
        send_packet(client->socket_fd, create_packet(ERROR, "Bad command."));
        return false;
    }
    if (!already_exist_team(server, client, data)) {
        return false;
    }
    return true;
}

/**
 * Create a new team.
 * @param server - server.
 * @param client - client.
 * @param data - data.
 */
void create_team(server_t *server, client_t *client, string data)
{
    if (!is_good_create_team(server, client, data)) {
        return;
    }
    char **command = str_to_word_array(data, "\"");
    team_t *new_team = MALLOC(sizeof(team_t));
    new_team->name = my_strdup(command[1]);
    new_team->channels = NULL;
    new_team->uuid = new_uuid();
    new_team->subscribers = NULL;
    new_team->description = my_strdup(command[3]);
    put_in_list(&server->teams, new_team);
    server_event_team_created(new_team->uuid, new_team->name,
        client->user->uuid);
    string info = my_multcat(5, new_team->uuid, "|", new_team->name,
        "|", new_team->description);
    broadcast_logged(server, create_packet(CREATE_TEAM_SUCCESS, info));
    free(info);
    free_array(command);
}
