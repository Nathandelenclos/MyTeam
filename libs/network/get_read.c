/*
** EPITECH PROJECT, 2023
** Network
** File description:
** network_lib
*/

#include "network.h"
#include <string.h>
#include <unistd.h>

/**
 *
 * @param fd
 * @return
 */
socket_t *get_read(int fd)
{
    socket_t *socket = MALLOC(sizeof(socket_t));
    void *size = MALLOC(sizeof(size_t));
    memset(socket, 0, sizeof(socket_t));
    memset(size, 0, sizeof(size_t));
    read(fd, size, sizeof(size_t));
    read(fd, socket, *((size_t *)size));
    return socket;
}
