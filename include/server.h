/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** Main
*/

#ifndef TEAMS_H_
    #define TEAMS_H_

    #include "struct.h"
    #include "my.h"
    #include "list.h"
    #include "network.h"
    #include "logging_server.h"
    #include <sys/select.h>

    #define MAX_CONNECTIONS 1024

typedef struct dirent *dirent_t;

typedef struct {
    string team_uuid;
    string channel_uuid;
    string thread_uuid;
} context_uuids_t;

typedef struct {
    int socket_fd;
    struct sockaddr_in sockaddr;
    socklen_t len;
    user_t *user;
    context_t context;
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    context_uuids_t *context_uuids;
} client_t;

typedef struct {
    int socket_fd;
    struct sockaddr_in sockaddr;
    node *clients;
    fd_set readfds;
    int last_fd;
    node *users;
    node *teams;
    node *user_in_teams;
} server_t;

void help_init(void);
void init_socketaddr(server_t *server, int port);
server_t *create_server(int port);
void new_connection(server_t *server);
void read_action(server_t *server, bool *is_running);
void handle_client(server_t *server);
void perror_exit(const char *string);
void disconect_client(server_t *server, client_t *client);
void command_client(server_t *server, client_t *client, packet_t *socket);
string *split(string str, char delim);
string my_strdup(string data);
void exit_all(int code);
int exist_dir(string dir);
int check_args(char *data, int *nb_arg, char *command0);
int len_array(string *array);
string itoa(long n);
int broadcast(server_t *server, packet_t *packet);
bool is_subscribed(team_t *team, user_t *user);
context_uuids_t *create_context_uuids(void);
client_t *create_client(int server_fd);

#endif
