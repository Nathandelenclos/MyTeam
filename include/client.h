/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** client main
*/

#include "network.h"

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

static const listener listeners[] = {
    {SUCCESS, success},
    {UNFOUND, unfound},
    {QUIT, NULL}
};

#endif