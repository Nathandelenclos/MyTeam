/*
** EPITECH PROJECT, 2023
** NetworkLib
** File description:
** network.h
*/

#include "my.h"
#include "list.h"

#ifndef NETWORK_H
    #define NETWORK_H

typedef struct {
    int code;
    int len;
    string data;
} socket_t;

socket_t *get_read(int fd);


#endif