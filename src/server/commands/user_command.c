/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** user commands
*/

#include "server.h"
#include "stdbool.h"

bool correct_uuid(string uuid, server_t *server)
{
    if (strlen(uuid) != 36)
        return false;
    for (node *users = server->users; users != NULL; users = users->next) {
        if (((client_t *)users->data)->user->uuid != NULL && strcmp(
            ((client_t *)users->data)->user->uuid, uuid) == 0)
            return true;
    }
    return false;
}

void give_user_info(server_t *server, client_t *client, string data)
{
    int i = 0;
    string msg_cli = NULL;
    packet_t *packet;
    char **command = str_to_word_array(data, " \t");
    for (i; command[i] != NULL; i++);
    if (i != 2) {
        packet = create_packet(ERROR, "invalid number of arguments");
    } else if (correct_uuid(command[1], server)) {
        msg_cli = MALLOC(sizeof(char) * strlen(command[1]) + 1);
        sprintf(msg_cli, "test %s", command[1]);
        packet = create_packet(LOGIN_SUCCESS, msg_cli);
    } else {
        packet = create_packet(LOGIN_SUCCESS, "wrong uuid");
    }
    send_packet(client->socket_fd, packet);
}
