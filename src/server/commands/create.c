/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** create.c
*/

#include "server.h"
#include "stdbool.h"

char *set_team(server_t *server, client_t *client, string name, string desc)
{
    team_t *new_team = MALLOC(sizeof(team_t));
    new_team->name = my_strdup(name);
    new_team->channels = NULL;
    new_team->uuid = new_uuid();
    new_team->description = desc;
    put_in_list(&server->teams, new_team);
    server_event_team_created(new_team->uuid, name, client->user->uuid);
    return my_multcat(4, "Team ", name, " ", new_team->uuid, " created");
}

void create_team(server_t *server, client_t *client, string data)
{
    int i = 0;
    char *msg_cli = NULL;
    packet_t *packet;
    char **command = str_to_word_array(data, " \t");
    int nb_arg[] = {2, -1};
    if (check_args(data, nb_arg, "/create") == 1) {
        packet = create_packet(ERROR, "bad command");
    } else if (client->user == NULL) {
        packet = create_packet(ERROR, "client not login");
    } else {
        char **command = str_to_word_array(data, "\"");
        string msg_cli = set_team(server, client, command[1], command[3]);
        packet = create_packet(CREATE_TEAM_SUCCESS, msg_cli);
    }
    send_packet(client->socket_fd, packet);
}

void create_channel(server_t *server, client_t *client, string data)
{
    ;
}

void create_thread(server_t *server, client_t *client, string data)
{
    ;
}

void create_reply(server_t *server, client_t *client, string data)
{
    ;
}
