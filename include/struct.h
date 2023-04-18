/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** struct
*/

#include "list.h"
#include "my.h"
#include "stdbool.h"

#ifndef STRUCT_H
    #define STRUCT_H

typedef enum {
    ANY,
    NONE,
    TEAM,
    CHANNEL,
    THREAD,
} context_t;

typedef struct {
    string name;
    string uuid;
    node *p_discuss;
    bool online;
} user_t;

typedef struct {
    string uuid;
    string name;
    string description;
    node *channels;
    node *subscribers;
} team_t;

typedef struct {
    string uuid;
    team_t *team;
    user_t *user;
} user_in_team_t;

typedef struct {
    string uuid;
    string data;
    time_t time;
    user_t *user;
} message_t;

typedef struct {
    string uuid;
    node *messages;
    node *users;
} p_discuss_t;

typedef struct {
    string name;
    string uuid;
    string description;
    node *threads;
} channel_t;

typedef struct {
    string uuid;
    user_t *user;
    time_t time;
    string title;
    string body;
    node *replies;
} thread_t;

thread_t *get_thread_by_uuid(node *threads, string str);
channel_t *get_channel_by_uuid(node *channels, string str);
team_t *get_team_by_uuid(node *teams, string str);

#endif
