/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** utils_command.c
*/

#include "server.h"
#include <dirent.h>

/**
 * Find the correct user in the discussion
 * @param i - number of users
 * @param discussion - discussion_t struct
 * @param client - client_t struct
 * @param data - data of the user
 * @return
 */
p_discuss_t *find_correct_user(int i, p_discuss_t *discussion,
                                client_t *client, string data)
{
    for (node *tmp2 = discussion->users; tmp2 != NULL; tmp2 = tmp2->next) {
        user_t *users = tmp2->data;
        if (strcmp(users->uuid, data) == 0 ||
            strcmp(users->uuid, client->user->uuid) == 0)
            i++;
        if (i == 2)
            return discussion;
    }
    return NULL;
}

/**
 * Find the correct discussion
 * @param server - server_t struct
 * @param client - client_t struct
 * @param data - data of the user
 * @return
 */
p_discuss_t *find_correct_discussion(server_t *server,
                                        client_t *client, string data)
{
    int i = 0;
    p_discuss_t *discussion = NULL;
    for (node *tmp = server->discusses; tmp != NULL; tmp = tmp->next) {
        discussion = tmp->data;
        if (find_correct_user(i, discussion, client, data) != NULL)
            return discussion;
    }
    return NULL;
}
