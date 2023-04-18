/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** user commands
*/

#include "server.h"
#include "stdbool.h"
#include "server.h"

packet_t *create_info_from_user(user_t *given_user, client_t *client)
{
    string msg_cli = NULL;
    packet_t *packet;
    msg_cli = MALLOC(sizeof(char) * strlen(client->user->name) + 41);
    sprintf(msg_cli,
            "the user with the given uuid is offline and his name is %s",
            client->user->name);
    string message = my_multcat(7, given_user->name, "|",
                                given_user->uuid, "|", msg_cli, "|",
                                given_user->online ? "1" : "0");
    packet = create_packet(INFO_USER_GIVEN_SUCCESS, message);
    free(message);
    return packet;
}

packet_t *create_info_from_client(client_t *given_user, client_t *client)
{
    string msg_cli = NULL;
    packet_t *packet;
    msg_cli = MALLOC(sizeof(char) * strlen(given_user->user->name) + 41);
    sprintf(msg_cli, "the user with the given uuid's name is %s",
            given_user->user->name);
    string message = my_multcat(7, given_user->user->name, "|",
                                given_user->user->uuid, "|", msg_cli, "|",
                                given_user->user->online ? "1" : "0");
    packet = create_packet(INFO_USER_GIVEN_SUCCESS, message);
    free(message);
    return packet;
}

packet_t *create_packet_to_send(client_t *client,
                                char **command, server_t *server)
{
    packet_t *packet;
    client_t *given_user = correct_uuid(command[1], server);
    user_t *offline_user = correct_uuid_user(command[1], server);
    if (given_user) {
        packet = create_info_from_client(given_user, client);
    } else if (offline_user) {
        packet = create_info_from_user(offline_user, client);
    } else {
        string message = my_multcat(3, client->user->uuid, "|",
                                    "this uuid does not exist.");
        packet = create_packet(UNFOUND, message);
        free(message);
    }
    return packet;
}

void give_user_info(server_t *server, client_t *client, string data)
{
    packet_t *packet;
    int nb_arg[] = {1, -1};
    if (check_args(data, nb_arg, "/user") == 1) {
        send_packet(client->socket_fd, create_packet(ERROR, "bad command"));
        return;
    }
    char **command = str_to_word_array(data, "\"");
    packet = create_packet_to_send(client, command, server);
    send_packet(client->socket_fd, packet);
}
