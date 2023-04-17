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

// Errors:
void default_error(packet_t *packet);
void unfound(packet_t *socket);
void unauthorized(packet_t *packet);
void already_exist(packet_t *packet);
void unknow_team(packet_t *packet);
void unknow_channel(packet_t *packet);
void unknow_thread(packet_t *packet);
void unknow_user(packet_t *packet);

// Success:
void success(packet_t *socket);
void login_user(packet_t *socket);
void logout_user(packet_t *socket);
void give_users(packet_t *socket);
void give_user_info(packet_t *packet);
void message_sent(packet_t *packet);
void list_messages(packet_t *packet);
void list_messages_error(packet_t *packet);
void create_team(packet_t *socket);
void create_channel(packet_t *socket);
void create_thread(packet_t *socket);
void create_reply(packet_t *socket);
void suscribe(packet_t *socket);
void suscribed(packet_t *socket);
void unsuscribe(packet_t *socket);
void use_success(packet_t *packet);

static const listener listeners[] = {
    // Errors:
    {ERROR, default_error},
    {UNFOUND, unfound},
    {UNAUTHORIZED, unauthorized},
    {ALREADY_EXIST, already_exist},
    {UNKNOW_TEAM, unknow_team},
    {UNKNOW_CHANNEL, unknow_channel},
    {UNKNOW_THREAD, unknow_thread},
    {UNKNOW_USER, unknow_user},
    {LIST_MESSAGES_ERROR_CODE, list_messages_error},
    // Success:
    {SUCCESS, success},
    {USERS_SUCCESS_CODE, give_users},
    {LIST_SUCCESS_CODE, success},
    {LOGIN_SUCCESS, login_user},
    {LOGOUT_SUCCESS, logout_user},
    {INFO_USER_GIVEN_SUCCESS, give_user_info},
    {MESSAGE_SENT, message_sent},
    {LIST_MESSAGES_SUCCESS_CODE, list_messages},
    {CREATE_TEAM_SUCCESS, create_team},
    {CREATE_CHANNEL_SUCCESS, create_channel},
    {CREATE_THREAD_SUCCESS, create_thread},
    {CREATE_REPLY_SUCCESS, create_reply},
    {SUBSCRIBE_SUCCESS, suscribe},
    {SUBSCRIBED_SUCCESS, suscribed},
    {UNSUBSCRIBE_SUCCESS, unsuscribe},
    {USE_SUCCESS, use_success},
    // Others:
    {QUIT, NULL}
};

#endif
