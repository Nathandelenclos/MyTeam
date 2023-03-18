/*
** EPITECH PROJECT, 2023
** NetworkLib
** File description:
** network.h
*/

#include "my.h"
#include "list.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#ifndef NETWORK_H
    #define NETWORK_H

typedef struct sockaddr_in sockaddr_in_t;

typedef struct {
    int code;
    int len;
    string data;
} socket_t;

socket_t *get_read(int fd);
int send_socket(int fd, socket_t *socket);
int create_socket(void);
sockaddr_in_t create_sockaddr_in(int port, string ip);

#endif
