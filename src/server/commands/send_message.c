/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** send_message.c
*/

#include "server.h"
#include "stdbool.h"
#include "logging_server.h"
#include "time.h"

/**
 * @brief Send a message to an online user.
 * @param server - Server structure.
 * @param command - Message to send.
 * @param client - Client structure.
 */
int send_to_online_user(server_t *server, message_t *message, client_t *client, user_t *user)
{
    int count = 0;
    string message_str = my_multcat(5, client->user->uuid, "|",
        client->user->name, "|", message->data);
    for (node *tmp = server->clients; tmp; tmp = tmp->next) {
        client_t *clt = tmp->data;
        if (strcmp(clt->user ? clt->user->uuid : "Invalid", user->uuid) == 0) {
            send_packet(clt->socket_fd, create_packet(MESSAGE_SENT, message_str));
            count++;
        }
    }
    free(message_str);
    return count;
}

/**
 * @brief Send a message to an offline user.
 * @param server - Server structure.
 * @param client - Client structure.
 * @param data - Message to send.
 */
void send_to_user(server_t *server, client_t *client, string data)
{
    packet_t *packet = NULL;
    int nb_arg[] = {2, -1};
    if (check_args(data, nb_arg, "/send") == 1) {
        send_packet(client->socket_fd, create_packet(ERROR, "bad command"));
        return;
    }
    char **command = str_to_word_array(data, "\"");
    user_t *offline_user = correct_uuid_user(command[1], server);
    if (offline_user) {
        p_discuss_t *discuss = send_message_offline(client, server,
                                                    offline_user, command);
        send_to_online_user(server, discuss->messages->data, client, offline_user);
        put_in_list(&server->discusses, discuss);
    } else {
        packet = create_packet(UNKNOW_USER, command[1]);
        send_packet(client->socket_fd, packet);
    }
    free_array(command);
}
