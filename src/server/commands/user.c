/*
** EPITECH PROJECT, 2023
** myftp
** File description:
** user commands
*/

#include "main.h"

/**
 * Create account client of server.
 * @param server
 */
void create_user(server_t *server)
{
    account_t *account = MALLOC(sizeof(account_t));
    account->name = "Anonymous";
    account->password = "";
    put_in_list(&server->accounts, account);
}
