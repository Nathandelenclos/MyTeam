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
    int socket_fd;
    struct sockaddr_in sockaddr;
    socklen_t len;
    user_t *user;
    context_t context;
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
    node *discusses;
} server_t;

void help_init(void);
void init_socketaddr(server_t *server, int port);
server_t *create_server(int port);
void new_connection(server_t *server);
void read_action(server_t *server);
void handle_client(server_t *server);
void perror_exit(const char *string);
void disconect_client(server_t *server, client_t *client, int valread);
void command_client(server_t *server, client_t *client, packet_t *socket);
string *split(string str, char delim);
int array_string_len(string *array);
string my_strdup(string data);
void exit_all(int code);
int exist_dir(string dir);
client_t *correct_uuid(string uuid, server_t *server);
user_t *correct_uuid_user(string uuid, server_t *server);
p_discuss_t *find_correct_user(int i, p_discuss_t *discussion,
                                client_t *client, string data);
p_discuss_t *find_correct_discussion(server_t *server,
                                        client_t *client, string data);
p_discuss_t *send_message_offline(client_t *client, server_t *server,
                                    user_t *user, char **command);
p_discuss_t *send_message(client_t *client, server_t *server,
                            client_t *user, char **command);

#endif
