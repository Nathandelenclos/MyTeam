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
    size_t size = sizeof(socket);
    write(fd, &size, sizeof(size_t));
    write(fd, socket, sizeof(socket));
}