/*
** EPITECH PROJECT, 2023
** myFtp
** File description:
** Main
*/

#ifndef FTP_H_
    #define FTP_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include "list.h"
    #include <errno.h>

    #define MAX_CONNECTIONS 1024

typedef char *string;

typedef struct dirent *dirent_t;

typedef struct {
    string name;
    string password;
} account_t;

typedef struct {
    int socket_fd;
    struct sockaddr_in sockaddr;
    socklen_t len;
    account_t *account;
    int state_auth;
    string pwd;
    int auth;
} client_t;

typedef struct {
    int socket_fd;
    struct sockaddr_in sockaddr;
    node *clients;
    fd_set readfds;
    int last_fd;
    node *accounts;
    string base_dir;
} server_t;

typedef struct {
    void (*function)(server_t *server, client_t *client, string data);
    string name;
    int auth_required;
    string description;
} command;

void help_init(void);
void init_socketaddr(server_t *server, int port);
server_t *create_server(int port, string dir);
void new_connection(server_t *server);
void read_action(server_t *server);
void handle_client(server_t *server);
void perror_exit(const char *string);
void disconect_client(server_t *server, client_t *client, int valread);
void command_client(server_t *server, client_t *client, int valread,
    string data);
string *split(string str, char delim);
int array_string_len(string *array);
string my_strdup(string data);
void exit_all(int code);
void create_user(server_t *server);
int exist_dir(string dir);
string get_read(int fd);

static const command commands[] = {};

#endif
