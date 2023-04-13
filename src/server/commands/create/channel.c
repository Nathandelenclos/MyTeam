/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** create/channel.c
*/

#include "server.h"
#include "stdbool.h"
#include <time.h>

/**
 * Check if the command is good.
 * @param server - server.
 * @param client - client.
 * @param data - data.
 * @return - true or false.
 */
bool is_good_create_channel(server_t *server, client_t *client, string data)
{
    int nb_arg[] = {2, -1};
    if (check_args(data, nb_arg, "/create") == 1) {
        send_packet(client->socket_fd,create_packet(ERROR, "Bad command"));
        return false;
    }
    if (client->team == NULL) {
        send_packet(client->socket_fd,create_packet(UNKNOW_TEAM, ""));
        return false;
    }
    char **command = str_to_word_array(data, "\"");
    for (node *tmp = client->team->channels; tmp; tmp = tmp->next) {
        channel_t *channel = ((channel_t *)tmp->data);
        if (strcmp(channel->name, command[1]) == 0) {
            send_packet(client->socket_fd,
                create_packet(ALREADY_EXIST, ""));
            return false;
        }
    }
    return true;
}

/**
 * Create a new channel.
 * @param server - server.
 * @param client - client.
 * @param data - data.
 */
void create_channel(server_t *server, client_t *client, string data)
{
    if (!is_good_create_channel(server, client, data))
        return;
    char **command = str_to_word_array(data, "\"");
    channel_t *new_channel = MALLOC(sizeof(channel_t));
    new_channel->name = my_strdup(command[1]);
    new_channel->threads = NULL;
    new_channel->uuid = new_uuid();
    new_channel->description = my_strdup(command[3]);
    put_in_list(&client->team->channels, new_channel);
    server_event_channel_created(client->team->uuid, new_channel->uuid, new_channel->name);
    string info = my_multcat(5, new_channel->uuid, "|", new_channel->name, "|", new_channel->description);
    send_packet(client->socket_fd, create_packet(CREATE_CHANNEL_SUCCESS,info));
    free(info);
}
