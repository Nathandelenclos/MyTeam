/*
** EPITECH PROJECT, 2023
** lib My
** File description:
** new channels_uuid
*/

#include <uuid/uuid.h>
#include "network.h"

/**
 * Generate new channels_uuid.
 * @return - Return new channels_uuid.
 */
string new_uuid(void)
{
    uuid_t uuid;
    string str = MALLOC(sizeof(char) * 37);

    uuid_generate(uuid);
    uuid_unparse(uuid, str);
    return str;
}
