/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** client main
*/

#include "network.h"
#include "logging_client.h"
#include <sys/select.h>

#ifndef CLIENT_H
    #define CLIENT_H

typedef struct {
    int code;
    void (*func)(packet_t *);
} listener;

void help_init(void);
packet_t *user_read(void);
void user_action(fd_set *fds, int client_socket, int *is_running);
void server_action(fd_set *fds, int client_socket, int *is_running);
void exit_all(int code);
void loop_actions(int client_socket);

void success(packet_t *socket);
void unfound(packet_t *socket);
void login_user(packet_t *socket);
void logout_user(packet_t *socket);
void give_users(packet_t *socket);
void create_team(packet_t *socket);
void create_channel(packet_t *socket);
void create_thread(packet_t *socket);
void create_reply(packet_t *socket);
void suscribe(packet_t *socket);
void suscribed(packet_t *socket);
void unsuscribe(packet_t *socket);

static const listener listeners[] = {
    {SUCCESS, success},
    {ERROR, unfound},
    {USERS_SUCCESS_CODE, give_users},
    {LIST_SUCCESS_CODE, success},
    {LOGIN_SUCCESS, login_user},
    {LOGOUT_SUCCESS, logout_user},
    {CREATE_TEAM_SUCCESS, create_team},
    {CREATE_CHANNEL_SUCCESS, create_channel},
    {CREATE_THREAD_SUCCESS, create_thread},
    {CREATE_REPLY_SUCCESS, create_reply},
    {SUSCRIBE_SUCCESS, suscribe},
    {SUSCRIBED_SUCCESS, suscribed},
    {UNSUSCRIBE_SUCCESS, unsuscribe},
    {UNFOUND, unfound},
    {QUIT, NULL}
};

#endif
