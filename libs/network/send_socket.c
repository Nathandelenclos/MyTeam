/*
** EPITECH PROJECT, 2023
** Network
** File description:
** network_lib
*/

#include "network.h"
#include <stdio.h>
#include <unistd.h>

int send_socket(int fd, socket_t *socket)
{
    write(fd, &socket->code, sizeof(int));
    write(fd, &socket->len, sizeof(int));
    write(fd, socket->data, socket->len);
}