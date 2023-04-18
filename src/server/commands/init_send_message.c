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

/**
 * Initialize structures inside p_discuss_t struct
 * @param discuss - p_discuss_t struct
 * @param client - client_t struct
 * @param command - command received
 * @param message_sent - message_t struct
 */
void init_structs(p_discuss_t *discuss, client_t *client,
                    char **command, message_t *message_sent)
{
    discuss->uuid = new_uuid();
    discuss->users = NULL;
    discuss->messages = NULL;
}

/**
 * Add the user and the message to the discussion
 * @param discuss - p_discuss_t struct
 * @param client - client_t struct
 * @param user - user_t struct
 * @param message_sent - message_t struct
 */
void add_to_discuss_list(p_discuss_t *discuss, client_t *client,
                            user_t *user, message_t *message_sent)
{
    put_in_list(&discuss->users, client->user);
    put_in_list(&discuss->users, user);
    put_in_list(&discuss->messages, message_sent);
}

/**
 * Initialize the message struct
 * @param command - command received
 * @param client - client_t struct
 * @return message_t * - message_t struct
 */
message_t *init_message_struct(char **command, client_t *client)
{
    message_t *message_sent = MALLOC(sizeof(message_t));
    message_sent->uuid = new_uuid();
    message_sent->data = my_strdup(command[3]);
    time(&message_sent->time);
    message_sent->user = client->user;
    return message_sent;
}

/**
 * Send a message to a user
 * @param client - client_t struct
 * @param server - server_t struct
 * @param user - user_t struct
 * @param command - command received
 * @return p_discuss_t * - p_discuss_t struct
 */
p_discuss_t *send_message(client_t *client, server_t *server,
                            client_t *user, char **command)
{
    string message = my_multcat(5, client->user->uuid, "|",
                                client->user->name, "|", command[3]);
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
                                        command[3]);
    free(message);
    return discuss;
}

/**
 * Send a message to a user when he is offline
 * @param client - client_t struct
 * @param server - server_t struct
 * @param user - user_t struct
 * @param command - command received
 * @return p_discuss_t * - p_discuss_t struct
 */
p_discuss_t *send_message_offline(client_t *client, server_t *server,
                                    user_t *user, char **command)
{
    string message = my_multcat(5, client->user->uuid, "|",
                                client->user->name, "|", command[3]);
    p_discuss_t *discuss =
            find_correct_discussion(server, client, user->uuid);
    message_t *message_sent = NULL;
    init_structs(discuss, client, command, message_sent);
    message_sent = init_message_struct(command, client);
    add_to_discuss_list(discuss, client, user, message_sent);
    server_event_private_message_sended(client->user->uuid, user->uuid,
                                        command[3]);
    free(message);
    return discuss;
}
