/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** user2.c
*/

#include "server.h"
#include "stdbool.h"
#include "logging_server.h"

p_discuss_t *send_message(packet_t *packet, client_t *client,
                  client_t *user, char **command)
{
    string message = my_multcat(5, client->user->uuid, "|",
                                client->user->name, "|", command[2]);
    packet = create_packet(MESSAGE_SENT, message);
    p_discuss_t *discuss = MALLOC(sizeof(p_discuss_t));
    discuss->uuid = new_uuid();
    discuss->users = NULL;
    discuss->messages = NULL;
    message_t *message_sent = MALLOC(sizeof(message_t));
    message_sent->uuid = new_uuid();
    message_sent->data = my_strdup(command[2]);
    put_in_list(&discuss->users, client->user);
    put_in_list(&discuss->users, user->user);
    put_in_list(&discuss->messages, message_sent);
    send_packet(user->socket_fd, packet);
    server_event_private_message_sended(client->user->uuid, user->user->uuid,
                                        command[2]);
    free(message);
    return discuss;
}

void send_to_user(server_t *server, client_t *client, string data)
{
    int i = 0;
    packet_t *packet = NULL;
    char **command = str_to_word_array(data, " \t");
    for (i; command[i] != NULL; i++);
    if (i != 3) {
        packet = create_packet(ERROR, "invalid number of arguments");
        send_packet(client->socket_fd, packet);
        return;
    }
    client_t *user = correct_uuid(command[1], server);
    if (!user) {
        packet = create_packet(UNFOUND, "invalid uuid");
        send_packet(client->socket_fd, packet);
        return;
    }
    p_discuss_t *discuss = send_message(packet, client, user, command);
    put_in_list(&server->discusses, discuss);

}
