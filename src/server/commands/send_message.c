/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** user2.c
*/

#include "server.h"
#include "stdbool.h"
#include "logging_server.h"
#include "time.h"

int check_arg_nbr(char **command, client_t *client, packet_t *packet)
{
    int i = 0;
    for (i; command[i] != NULL; i++);
    if (i != 3) {
        packet = create_packet(ERROR, "invalid number of arguments");
        send_packet(client->socket_fd, packet);
        return 1;
    }
    return 0;
}

void send_to_user(server_t *server, client_t *client, string data)
{
    packet_t *packet = NULL;
    char **command = str_to_word_array(data, " \t");
    if (check_arg_nbr(command, client, packet))
        return;
    client_t *user = correct_uuid(command[1], server);
    user_t *offline_user = correct_uuid_user(command[1], server);
    if (user) {
        p_discuss_t *discuss = send_message(client, server, user, command);
        put_in_list(&server->discusses, discuss);
    } else if (offline_user) {
        p_discuss_t *discuss = send_message_offline(client, server,
                                                    offline_user, command);
        put_in_list(&server->discusses, discuss);
    } else {
        packet = create_packet(UNFOUND, "invalid uuid");
        send_packet(client->socket_fd, packet);
    }
}
