/*
** EPITECH PROJECT, 2023
** Network
** File description:
** create_socket
*/

#include "network.h"

/**
 * Create socket.
 * @return - Return socket fd.
 */
int create_socket(void)
{
    int skt = socket(AF_INET, SOCK_STREAM, 0);
    if (skt < 0) {
        perror("socket()");
        exit(EXIT_FAILURE);
    }
    return skt;
}
