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
p_discuss_t *init_structs(client_t *client,
                    user_t *receiver, message_t *message_sent)
{
    p_discuss_t *discuss = MALLOC(sizeof(p_discuss_t));
    discuss->uuid = new_uuid();
    discuss->users = NULL;
    put_in_list(&discuss->users, client->user);
    put_in_list(&discuss->users, receiver);
    discuss->messages = NULL;
    put_in_list(&discuss->messages, message_sent);
    return discuss;
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
    message_t *message_sent = init_message_struct(command, client);
    p_discuss_t *discuss =
            find_correct_discussion(server, client, user->uuid);
    if (discuss == NULL) {
        discuss = init_structs(client, user, message_sent);
    } else {
        put_in_list(&discuss->messages, message_sent);
    }
    server_event_private_message_sended(
        client->user->uuid, user->uuid, command[3]);
    return discuss;
}
