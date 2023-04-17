/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** sucess.c
*/

#include "client.h"
#include "logging_client.h"

/**
 * Success listener.
 * @param packet - Packet to read.
 */
void success(packet_t *packet)
{
    printf("Info: %s\n", packet->data);
}

/**
 * Unfound listener.
 * @param packet - Packet to read.
 */
void unfound(packet_t *packet)
{
    printf("Error unfound: %s\n", packet->data);
}

/**
 * LOGIN_SUCCESS listener.
 * @param packet - Packet to read.
 */
void login_user(packet_t *packet)
{
    printf("Login: %s\n", packet->data);
}

/**
 * LOGOUT_SUCCESS listener.
 * @param packet - Packet to read.
 */
void logout_user(packet_t *packet)
{
    printf("Logout: %s\n", packet->data);
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
    string *users = str_to_word_array(packet->data, "\n");
    for (int i = 0; users[i] != NULL; i++) {
        if (sscanf(users[i],
        "%s %s %d", user_uuid, user_name, &user_status) == 3)
            client_print_users(user_uuid, user_name, user_status);
    }
    free_array(users);
    FREE(user_uuid);
    FREE(user_name);
}

/**
 * USE_SUCCESS listener.
 * @param packet - Packet to read.
 */
void use_success(packet_t *packet)
{
    printf("Info: %s\n", packet->data);
}
