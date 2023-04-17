/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** messages_command.c
*/

#include "server.h"
#include "stdbool.h"
#include "time.h"

void send_in_reverse_order(node* tmp, client_t *client)
{
    if (tmp == NULL) {
        return;
    }
    send_in_reverse_order(tmp->next, client);
    packet_t *packet;
    message_t *message = tmp->data;
    string data = my_multcat(7, message->user->uuid, "|",
                                message->user->name, "|",
                                ctime(&message->time),
                                "|", message->data);
    packet = create_packet(LIST_MESSAGES_SUCCESS_CODE, data);
    send_packet(client->socket_fd, packet);
    free(data);
    FREE(packet);
}

void message_exchanged(server_t *server, client_t *client, string data)
{
    int i = 0;
    packet_t *packet = NULL;
    char **command = str_to_word_array(data, " \t");
    for (i; command[i] != NULL; i++);
    if (i != 2) {
        packet = create_packet(ERROR, "invalid number of arguments");
        send_packet(client->socket_fd, packet);
        return;
    }
    p_discuss_t *discussion = find_correct_discussion(server, client,
                                                        command[1]);
    if (discussion == NULL) {
        packet = create_packet(LIST_MESSAGES_ERROR_CODE,
                                "no messages exchanged with this user");
        send_packet(client->socket_fd, packet);
        return;
    }
    send_in_reverse_order(discussion->messages, client);
}
