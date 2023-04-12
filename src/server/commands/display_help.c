/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** display_help.c
*/

#include <fcntl.h>
#include "server.h"
#include "stdbool.h"
#include "commands.h"

string create_message_format(string str1, string str2, string str3)
{
    string final_string;
    size_t size = strlen(str1) + strlen(str2) + strlen(str3) + 4;
    final_string = MALLOC(size);
    final_string[size] = '\0';
    my_strconcat(final_string, str1);
    my_strconcat(final_string, "|");
    my_strconcat(final_string, str2);
    my_strconcat(final_string, "|");
    my_strconcat(final_string, str3);
    fprintf(stderr, "final_string: %s", final_string);
    return final_string;
}

void display_help(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(SUCCESS,"Help");
    send_packet(client->socket_fd, packet);
}
