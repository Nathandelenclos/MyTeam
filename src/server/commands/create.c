/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** create.c
*/

#include "server.h"
#include "stdbool.h"

void create_team(server_t *server, client_t *client, string data)
{
    int nb_arg[] = {2, -1};
    if (check_args(data, nb_arg, "/create") == 1) {
        send_packet(client->socket_fd,create_packet(ERROR, "Bad command."));
        return;
    }
    char **command = str_to_word_array(data, "\"");
    team_t *new_team = MALLOC(sizeof(team_t));
    new_team->name = my_strdup(command[1]);
    new_team->channels = NULL;
    new_team->uuid = new_uuid();
    new_team->description = my_strdup(command[3]);
    put_in_list(&server->teams, new_team);
    server_event_team_created(new_team->uuid, new_team->name, client->user->uuid);
    string info = my_multcat(5, new_team->uuid, "|", new_team->name, "|", new_team->description);
    send_packet(client->socket_fd, create_packet(CREATE_TEAM_SUCCESS,info));
    free(info);
}

void create_channel(server_t *server, client_t *client, string data)
{
    int nb_arg[] = {2, -1};
    if (check_args(data, nb_arg, "/create") == 1) {
        send_packet(client->socket_fd,create_packet(ERROR, "Bad command"));
        return;
    }
    if (client->data == NULL) {
        send_packet(client->socket_fd,create_packet(ERROR, "You are not in a team."));
        return;
    }
    char **command = str_to_word_array(data, "\"");
    team_t *team = ((team_t *)client->data);
    channel_t *new_channel = MALLOC(sizeof(channel_t));
    new_channel->name = my_strdup(command[1]);
    new_channel->threads = NULL;
    new_channel->uuid = new_uuid();
    new_channel->description = my_strdup(command[3]);
    put_in_list(&team->channels, new_channel);
    server_event_channel_created(team->uuid, new_channel->uuid, new_channel->name);
    string info = my_multcat(5, new_channel->uuid, "|", new_channel->name, "|", new_channel->description);
    send_packet(client->socket_fd, create_packet(CREATE_CHANNEL_SUCCESS,info));
    free(info);
}

void create_thread(server_t *server, client_t *client, string data)
{
    ;
}

void create_reply(server_t *server, client_t *client, string data)
{
    ;
}
