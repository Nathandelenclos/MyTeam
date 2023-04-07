/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** user commands
*/

#include "server.h"
#include "stdbool.h"

char *login_user_exist(server_t *server, client_t *client, string name)
{
    user_t *tmp;
    char *str = NULL;
    printf("%s\n", name);
    for (node *node_tmp = server->users; node_tmp != NULL;
        node_tmp = node_tmp->next) {
        tmp = (user_t *)node_tmp->data;
        if (strcmp(tmp->name, name) == 0) {
            str = my_strconcat("Welcome back ", name);
            client->user = tmp;
            return str;
        }
    }
    user_t *new_user = MALLOC(sizeof(user_t));
    new_user->name = my_strdup(name);
    new_user->p_discuss = NULL;
    new_user->uuid = my_strdup("uuid");
    put_in_list(&server->users, new_user);
    client->user = new_user;
    str = my_strconcat("You are now login ", name);
    return str;
}

void login_user(server_t *server, client_t *client, string data)
{
    int i = 0;
    char *msg_cli = NULL;
    packet_t *packet;
    printf("Data received : %s\n", data);
    char **command = str_to_word_array(data, " \t");
    for (i; command[i] != NULL; i++);
    if (i != 2) {
        packet = create_packet(ERROR, "bad nb arg");
    } else {
        msg_cli = login_user_exist(server, client, command[1]);
        packet = create_packet(LOGIN_SUCCESS, msg_cli);
    }
    send_packet(client->socket_fd, packet);
}

char *logout_user_exist(server_t *server, client_t *client, string name)
{
    user_t *tmp;
    char *str = NULL;
    printf("%s\n", name);
    for (node *node_tmp = server->users; node_tmp != NULL;
        node_tmp = node_tmp->next) {
        tmp = (user_t *)node_tmp->data;
        if (strcmp(tmp->name, name) == 0) {
            str = my_strconcat(name, " is now logout");
            free(client->user);
            client->user = NULL;
            return str;
        }
    }
    str = my_strdup("Missed logout");
    return str;
}

void logout_user(server_t *server, client_t *client, string data)
{
    int i = 0;
    char *msg_cli = NULL;
    packet_t *packet;
    printf("Data received : %s\n", data);
    char **command = str_to_word_array(data, " \t");
    for (i; command[i] != NULL; i++);
    if (i != 1) {
        packet = create_packet(ERROR, "bad nb arg");
        send_packet(client->socket_fd, packet);
        return;
    }
    if (client->user == NULL) {
        packet = create_packet(ERROR, "No user login");
        send_packet(client->socket_fd, packet);
        return;
    }
    msg_cli = logout_user_exist(server, client, client->user->name);
    if (strcmp(msg_cli, "Missed logout") == 0) {
        packet = create_packet(ERROR, "Missed logout");
        send_packet(client->socket_fd, packet);
        return;
    }
    packet = create_packet(LOGOUT_SUCCESS, msg_cli);
    send_packet(client->socket_fd, packet);
}

void give_users(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(LOGIN_SUCCESS, "test");
    send_packet(client->socket_fd, packet);
}

void give_user_info(server_t *server, client_t *client, string data)
{
    packet_t *packet = create_packet(LOGIN_SUCCESS, "test");
    send_packet(client->socket_fd, packet);
}
