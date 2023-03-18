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
    socket_t *skt = MALLOC(sizeof(socket_t));
    read(fd, &skt->code, sizeof(int ));
    read(fd, &skt->len, sizeof(int ));
    skt->data = MALLOC(sizeof(char) * (skt->len + 1));
    memset(skt->data, 0, (skt->len + 1));
    read(fd, skt->data, skt->len);
    return skt;
}
