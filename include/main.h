/*
** EPITECH PROJECT, 2023
** myFtp
** File description:
** Main
*/

#ifndef FTP_H_
    #define FTP_H_

    #include "struct.h"
    #include "my.h"
    #include "list.h"
    #include "network.h"

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
} server_t;

typedef struct {
    void (*function)(server_t *server, client_t *client, string data);
    string name;
    int auth_required;
    string description;
    context_t context;
} command;

void help_init(void);
void init_socketaddr(server_t *server, int port);
server_t *create_server(int port);
void new_connection(server_t *server);
void read_action(server_t *server);
void handle_client(server_t *server);
void perror_exit(const char *string);
void disconect_client(server_t *server, client_t *client, int valread);
void command_client(server_t *server, client_t *client, socket_t *socket);
string *split(string str, char delim);
int array_string_len(string *array);
string my_strdup(string data);
void exit_all(int code);
int exist_dir(string dir);

static const command commands[] = {};

#endif
