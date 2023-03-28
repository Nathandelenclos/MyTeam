/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** commands server
*/

#ifndef COMMANDS_H
    #define COMMANDS_H

#include "server.h"

typedef struct {
    void (*function)(server_t *server, client_t *client, string data);
    string name;
    int auth_required;
    string description;
    context_t context;
} command;

void list_team(server_t *server, client_t *client, string data);

static const command commands[] = {
    {list_team, "/list", 0, "list all existing channels", NONE},
    {NULL, "", 0, "None", NONE},
};

#endif