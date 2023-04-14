/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** init_send_message.c
*/

#include "server.h"
#include "stdbool.h"
#include "logging_server.h"
#include "time.h"

void init_structs(p_discuss_t *discuss, client_t *client,
                  char **command, message_t *message_sent)
{
    discuss->uuid = new_uuid();
    discuss->users = NULL;
    discuss->messages = NULL;
}

void add_to_discuss_list(p_discuss_t *discuss, client_t *client,
                            user_t *user, message_t *message_sent)
{
    put_in_list(&discuss->users, client->user);
    put_in_list(&discuss->users, user);
    put_in_list(&discuss->messages, message_sent);
}

message_t *init_message_struct(char **command, client_t *client)
{
    message_t *message_sent = MALLOC(sizeof(message_t));
    message_sent->uuid = new_uuid();
    message_sent->data = my_strdup(command[2]);
    time(&message_sent->time);
    message_sent->user = client->user;
    return message_sent;
}

p_discuss_t *send_message(client_t *client, server_t *server,
                            client_t *user, char **command)
{
    string message = my_multcat(5, client->user->uuid, "|",
                                client->user->name, "|", command[2]);
    packet_t *packet = create_packet(MESSAGE_SENT, message);
    p_discuss_t *discuss =
            find_correct_discussion(server, client, user->user->uuid);
    message_t *message_sent = NULL;
    if (discuss == NULL) {
        discuss = MALLOC(sizeof(p_discuss_t));
        init_structs(discuss, client, command, message_sent);
    }
    message_sent = init_message_struct(command, client);
    add_to_discuss_list(discuss, client, user->user, message_sent);
    send_packet(user->socket_fd, packet);
    server_event_private_message_sended(client->user->uuid, user->user->uuid,
                                        command[2]);
    free(message);
    return discuss;
}

p_discuss_t *send_message_offline(client_t *client, server_t *server,
                                    user_t *user, char **command)
{
    string message = my_multcat(5, client->user->uuid, "|",
                                client->user->name, "|", command[2]);
    p_discuss_t *discuss =
            find_correct_discussion(server, client, user->uuid);
    message_t *message_sent = NULL;
    init_structs(discuss, client, command, message_sent);
    message_sent = init_message_struct(command, client);
    add_to_discuss_list(discuss, client, user, message_sent);
    server_event_private_message_sended(client->user->uuid, user->uuid,
                                        command[2]);
    free(message);
    return discuss;
}
