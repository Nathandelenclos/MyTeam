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

void add_to_disscus_list(p_discuss_t *discuss, client_t *client,
                            user_t *user, message_t *message_sent)
{
    put_in_list(&discuss->users, client->user);
    put_in_list(&discuss->users, user);
    put_in_list(&discuss->messages, message_sent);
}

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
    time(&message_sent->time);
    message_sent->user = client->user;
    add_to_disscus_list(discuss, client, user->user, message_sent);
    send_packet(user->socket_fd, packet);
    server_event_private_message_sended(client->user->uuid, user->user->uuid,
                                        command[2]);
    free(message);
    return discuss;
}

p_discuss_t *send_message_offline(client_t *client,
                                    user_t *user, char **command)
{
    string message = my_multcat(5, client->user->uuid, "|",
                                client->user->name, "|", command[2]);
    p_discuss_t *discuss = MALLOC(sizeof(p_discuss_t));
    discuss->uuid = new_uuid();
    discuss->users = NULL;
    discuss->messages = NULL;
    message_t *message_sent = MALLOC(sizeof(message_t));
    message_sent->uuid = new_uuid();
    message_sent->data = my_strdup(command[2]);
    time(&message_sent->time);
    message_sent->user = client->user;
    add_to_disscus_list(discuss, client, user, message_sent);
    server_event_private_message_sended(client->user->uuid, user->uuid,
                                        command[2]);
    free(message);
    return discuss;
}

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
        p_discuss_t *discuss = send_message(packet, client, user, command);
        put_in_list(&server->discusses, discuss);
    } else if (offline_user) {
        p_discuss_t *discuss = send_message_offline(client, offline_user,
                                                    command);
        put_in_list(&server->discusses, discuss);
    } else {
        packet = create_packet(UNFOUND, "invalid uuid");
        send_packet(client->socket_fd, packet);
    }
}
