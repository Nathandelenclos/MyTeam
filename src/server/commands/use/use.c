/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** use.c
*/

#include "server.h"
#include "stdbool.h"

/**
 * check if the command is good.
 * @param server - server info.
 * @param client - client info.
 * @param data - client command beginning by /use.
 * @return - true or false.
 */
bool good_actions_use(server_t *server, client_t *client, string data)
{
    int nb_arg[] = {0, 1, 2, 3, -1};
    if (check_args(data, nb_arg, "/use") == 1) {
        send_packet(client->socket_fd, create_packet(ERROR, "bad command"));
        return false;
    }
    return true;
}

/**
 * use the context.
 * @param server - server info.
 * @param client - client info.
 * @param data - client command beginning by /use.
 */
void use(server_t *server, client_t *client, string data)
{
    if (!good_actions_use(server, client, data)) {
        return;
    }
    client->context = NONE;
    string *command_parsed = str_to_word_array(data, "\"");
    if (!set_team(server, client, command_parsed)) {
        send_packet(client->socket_fd,
            create_packet(USE_SUCCESS, "You are now in the NONE"));
        return;
    }
    if (!set_channel(server, client, command_parsed)) {
        send_packet(client->socket_fd,
            create_packet(USE_SUCCESS, "You are now in the TEAM"));
        return;
    }
    if (!set_thread(server, client, command_parsed)) {
        send_packet(client->socket_fd,
            create_packet(USE_SUCCESS, "You are now in the CHANNEL"));
        return;
    }
    send_packet(client->socket_fd,
        create_packet(USE_SUCCESS, "You are now in the THREAD"));
    free_array(command_parsed);
}
