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

void login_user(server_t *server, client_t *client, string data);
void logout_user(server_t *server, client_t *client, string data);
void give_users(server_t *server, client_t *client, string data);
void give_user_info(server_t *server, client_t *client, string data);
void send_to_user(server_t *server, client_t *client, string data);
void message_exchanged(server_t *server, client_t *client, string data);
void subscribe(server_t *server, client_t *client, string data);
void subscribed(server_t *server, client_t *client, string data);
void unsubscribe(server_t *server, client_t *client, string data);
void use(server_t *server, client_t *client, string data);
void create_team(server_t *server, client_t *client, string data);
void create_channel(server_t *server, client_t *client, string data);
void create_thread(server_t *server, client_t *client, string data);
void create_reply(server_t *server, client_t *client, string data);
void list_team(server_t *server, client_t *client, string data);
void give_info(server_t *server, client_t *client, string data);
void display_help(server_t *server, client_t *client, string data);
void list_teams(server_t *server, client_t *client, string data);
void list_channels(server_t *server, client_t *client, string data);
void list_thread(server_t *server, client_t *client, string data);
void list_reply(server_t *server, client_t *client, string data);

static const command commands[] = {
    {login_user, "/login", 0, "set the user_name used by client", NONE},
    {logout_user, "/logout", 0, "disconnect the client from the server", NONE},
    {display_help, "/help", 1, "show help", NONE},
    {give_users, "/users", 1, "get the list of all users that exist on the\
        domain", ANY},
    {give_user_info, "/user", 1, "get information about a user", ANY},
    {send_to_user, "/send", 1, "end a message to a user", ANY},
    {message_exchanged, "/messages", 1, "list all messages exchange with an\
        user", ANY},
    {subscribe, "/subscribe", 1, "subscribe to the event of a team and its sub\
        directories (enable reception of all events from a team)", ANY},
    {subscribed, "/subscribed", 1, "list all subscribed teams or list all\
        users subscribed to a team", ANY},
    {unsubscribe, "/unsubscribe", 1, "unsubscribe from a team", ANY},
    {use, "/use", 1, "use specify a context team/channel/thread", ANY},
    {create_channel, "/create", 1, "create a team", TEAM},
    {create_thread, "/create", 1, "create a team", CHANNEL},
    {create_reply, "/create", 1, "create a team", THREAD},
    {create_team, "/create", 1, "create a team", NONE},
    {list_teams, "/list", 1, "list all existing teams", NONE},
    {list_channels, "/list", 1, "list all existing channels in team", TEAM},
    {list_thread, "/list", 1, "list all existing thread in channel", CHANNEL},
    {list_reply, "/list", 1, "list all existing replies in thread", THREAD},
    {give_info, "/info", 1, "based on what is being used list the current",
        NONE},
    {NULL, "", 0, "None", NONE}
};

#endif
