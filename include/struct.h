/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** struct
*/

#include "list.h"

#ifndef STRUCT_H
    #define STRUCT_H

typedef char *string;

typedef struct {
    string name;
    string uuid;
    node *p_discuss;
} user_t;

typedef struct {
    string uuid;
    string name;
    string description;
    node *channels;
} team_t;

typedef struct {
    string uuid;
    team_t *team;
    user_t *user;
} user_in_team_t;

typedef struct {
    string uuid;
    string data;
} message_t;

typedef struct {
    string uuid;
    node *messages;
    node *users;
} p_discuss_t;

typedef struct {
    string name;
    string uuid;
    node *threads;
} channel_t;

typedef struct {
    string uuid;
    node *messages;
} thread_t;

#endif