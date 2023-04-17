/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** sucess.c
*/

#include "client.h"

/**
 * Success listener.
 * @param packet - Packet to read.
 */
void success(packet_t *packet)
{
    printf("Info: %s\n", packet->data);
}

/**
 * USERS_SUCCESS_CODE listener.
 * @param packet - Packet to read.
 */
void give_users(packet_t *packet)
{
    string user_uuid = MALLOC(sizeof(char) * 37);
    string user_name = MALLOC(sizeof(char) * 33);
    int user_status;
    char **users = str_to_word_array(packet->data, "\n");
    for (int i = 0; users[i] != NULL; i++) {
        if (sscanf(users[i],
        "%s %s %d", user_uuid, user_name, &user_status) == 3)
            client_print_users(user_uuid, user_name, user_status);
    }
    FREE(user_name);
    FREE(user_uuid);
}

/**
 * USE_SUCCESS listener.
 * @param packet - Packet to read.
 */
void use_success(packet_t *packet)
{
    printf("Info: %s\n", packet->data);
}
