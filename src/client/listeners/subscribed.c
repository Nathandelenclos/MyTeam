/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** sucess.c
*/

#include "client.h"


void suscribe(packet_t *packet)
{
    printf("Suscribe to team: %s\n", packet->data);
}

void suscribed(packet_t *packet)
{
    printf("Is suscribed to team: %s\n", packet->data);
}

void unsuscribe(packet_t *packet)
{
    printf("Unsuscribe to team: %s\n", packet->data);
}
