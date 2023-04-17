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
void create(server_t *server, client_t *client, string data);
void list_team(server_t *server, client_t *client, string data);
void give_info(server_t *server, client_t *client, string data);
void display_help(server_t *server, client_t *client, string data);

static const command commands[] = {
    {display_help, "/help", 0, "show help", NONE},
    {login_user, "/login", 0, "set the user_name used by client", NONE},
    {logout_user, "/logout", 0, "disconnect the client from the server", NONE},
    {give_users, "/users", 0, "get the list of all users that exist on the\
        domain", NONE},
    {give_user_info, "/user", 0, "get information about a user", NONE},
    {send_to_user, "/send", 1, "end a message to a user", NONE},
    {message_exchanged, "/messages", 1, "list all messages exchange with an\
        user", NONE},
    {subscribe, "/subscribe", 0, "subscribe to the event of a team and its sub\
        directories (enable reception of all events from a team)", NONE},
    {subscribed, "/subscribed", 0, "list all subscribed teams or list all\
        users subscribed to a team", NONE},
    {unsubscribe, "/unsubscribe", 0, "unsubscribe from a team", NONE},
    {use, "/use", 0, "use specify a context team/channel/thread", NONE},
    {create, "/create", 0, "based on what is being used create the sub\
        resource", NONE},
    {list_team, "/list", 0, "list all existing teams", NONE},
    {give_info, "/info", 0, "based on what is being used list the current",
        NONE},
    {NULL, "", 0, "None", NONE}
};

#endif
