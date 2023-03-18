/*
** EPITECH PROJECT, 2023
** Network
** File description:
** network_lib
*/

#include "network.h"
#include <stdio.h>
#include <unistd.h>

/**
 * Send packet to socket.
 * @param fd - fr to send packet.
 * @param packet - packet to send.
 * @return - Return 0 if success.
 */
int send_packet(int fd, packet_t *packet)
{
    write(fd, &packet->code, sizeof(int));
    write(fd, &packet->len, sizeof(int));
    write(fd, packet->data, packet->len);
    return 0;
}
