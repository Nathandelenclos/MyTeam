/*
** EPITECH PROJECT, 2023
** Network
** File description:
** create_sockaddr_in
*/

#include "network.h"

/**
 * Create sockaddr_in.
 * @param port - Port to use.
 * @param ip - Ip to use.
 * @return - Return sockaddr_in.
 */
sockaddr_in_t create_sockaddr_in(int port, string ip)
{
    sockaddr_in_t addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) {
        perror("Adresse IP invalide ou non prise en charge");
        exit(EXIT_FAILURE);
    }
    return addr;
}
