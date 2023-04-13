/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** user commands
*/

#include "server.h"
#include "stdbool.h"
#include "server.h"

packet_t *create_info(client_t *given_user, client_t *client)
{
    string msg_cli = NULL;
    packet_t *packet;
    msg_cli = MALLOC(sizeof(char) * strlen(client->user->name) + 41);
    sprintf(msg_cli, "the user with the given uuid's name is %s",
            client->user->name);
    string message = my_multcat(7, given_user->user->name, "|",
                                given_user->user->uuid, "|", msg_cli, "|",
                                given_user->user->online ? "1" : "0");
    packet = create_packet(INFO_USER_GIVEN_SUCCESS, message);
    free(message);
    return packet;
}

void give_user_info(server_t *server, client_t *client, string data)
{
    int i = 0;
    packet_t *packet;
    char **command = str_to_word_array(data, " \t");
    for (i; command[i] != NULL; i++);
    if (i != 2) {
        packet = create_packet(ERROR, "invalid number of arguments");
        send_packet(client->socket_fd, packet);
        return;
    }
    client_t *given_user = correct_uuid(command[1], server);
    if (given_user) {
        packet = create_info(given_user, client);
    } else
        packet = create_packet(UNFOUND, "invalid uuid/offline user");
    send_packet(client->socket_fd, packet);
}
