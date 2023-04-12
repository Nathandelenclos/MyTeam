/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** user commands
*/

#include "server.h"
#include "stdbool.h"

string create_message_format(string str1, string str2, string str3, string str4)
{
    string final_string;
    size_t size = strlen(str1) + strlen(str2) + strlen(str3) + strlen(str4) + 4;
    final_string = MALLOC(size);
    final_string = my_multcat(7, str1, "|", str2, "|", str3, "|", str4);
    return final_string;
}

user_t *correct_uuid(string uuid, server_t *server)
{
    if (strlen(uuid) != 36)
        return NULL;
    for (node *users = server->users; users != NULL; users = users->next) {
        user_t *user = (user_t *)users->data;
        if (user != NULL && user->uuid != NULL &&
        strcmp(user->uuid, uuid) == 0) {
            return user;
        }
    }
    return NULL;
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
        send_packet(client->socket_fd, packet);
        return;
    }
    user_t *user = correct_uuid(command[1], server);
    if (user) {
        msg_cli = MALLOC(sizeof(char) * strlen(user->name) + 41);
        sprintf(msg_cli, "the user with the given uuid's name is %s", user->name);
        packet = create_packet(INFO_USER_GIVEN_SUCCESS,
                               create_message_format(user->name, user->uuid, msg_cli, user->online ? "1" : "0"));
    } else {
        packet = create_packet(UNFOUND, "invalid uuid");
    }
    send_packet(client->socket_fd, packet);
}
