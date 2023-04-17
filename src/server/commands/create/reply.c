/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** create/team.c
*/

#include "server.h"
#include "stdbool.h"
#include <time.h>

void create_reply(server_t *server, client_t *client, string data)
{
    int nb_arg[] = {1, -1};
    if (check_args(data, nb_arg, "/create") == 1) {
        send_packet(client->socket_fd,create_packet(ERROR, "Bad command"));
        return;
    }
    if (!is_subscribed(client->team, client->user)) {
        send_packet(client->socket_fd,create_packet(UNAUTHORIZED, "You are not subscribed to this team."));
        return;
    }
    string *command_parsed = str_to_word_array(data, " ");
    if (client->thread == NULL) {
        send_packet(client->socket_fd,create_packet(UNKNOW_THREAD, client->context_uuids->thread_uuid));
        return;
    }
    message_t *new_reply = MALLOC(sizeof(message_t));
    new_reply->data = my_strdup(command_parsed[1]);
    new_reply->uuid = new_uuid();
    new_reply->time = time(NULL);
    new_reply->user = client->user;
    put_in_list(&client->thread->replies, new_reply);
    string info = my_multcat(7, client->team->uuid, "|",  client->thread->uuid, "|", client->user->uuid, "|", new_reply->data);
    send_packet(client->socket_fd,create_packet(CREATE_REPLY_SUCCESS, info));
    free_array(command_parsed);
    free(info);
}