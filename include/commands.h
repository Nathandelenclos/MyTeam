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

static const command commands[] = {
    {NULL, "", 0, "None", NONE},
};

#endif