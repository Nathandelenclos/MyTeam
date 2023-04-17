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
 * Read packet from socket.
 * @param fd - fd to read packet.
 * @return - Return packet.
 */
packet_t *read_packet(int fd)
{
    packet_t *skt = MALLOC(sizeof(packet_t));
    skt->code = -1;
    read(fd, &skt->code, sizeof(int ));
    if (skt->code == -1) {
        FREE(skt);
        return NULL;
    }
    read(fd, &skt->len, sizeof(int ));
    skt->data = MALLOC(sizeof(char) * (skt->len + 1));
    memset(skt->data, 0, (skt->len + 1));
    read(fd, skt->data, skt->len);
    return skt;
}
