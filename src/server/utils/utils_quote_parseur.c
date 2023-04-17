/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** utils
*/

#include "server.h"
#include <dirent.h>

/**
 * check if the first arg.
 * @param first - first arg.
 * @param command0 - command.
 * @return - 1 or 0.
 */
int check_first_arg(char *first, char *command0)
{
    for (int i = strlen(command0); first[i]; i++)
        if (first[i] != ' ' && first[i] != '\t')
            return (1);
    return (0);
}

/**
 * check if the arg is empty.
 * @param str - arg.
 * @return - 1 or 0.
 */
int check_arg_content(char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ' && str[i] != '\t')
            return (1);
    return (0);
}

/**
 * check if the others args are good.
 * @param command - command.
 * @return - 1 or 0.
 */
int check_others_args(char **command)
{
    for (int i = 1; command[i]; i++)
        if (i % 2 == 0 && check_arg_content(command[i]) == 1)
            return (1);
    return (0);
}

/**
 * Count the number of quotes.
 * @param data - data.
 * @return - number of quotes.
 */
int count_arg(char *data)
{
    int quotes = 0;
    for (int i = 0; data[i]; i++) {
        if (data[i] == '\"')
            quotes++;
        if (i > 0 && data[i - 1] == '\"' && data[i] == '\"') {
            return (-1);
        }
    }
    return (quotes);
}

/**
 * Check if the args are good.
 * @param data - data.
 * @param nb_arg - number of args.
 * @param command0 - command.
 * @return - 1 or 0.
 */
int check_args(char *data, int *nb_arg, char *command0)
{
    int error = 1;
    int nb_quotes = count_arg(data);
    if (nb_quotes == -1)
        return (1);
    for (int i = 0; nb_arg[i] != -1; i++)
        if (nb_quotes == 2 * nb_arg[i])
            error = 0;
    if (error == 1)
        return (1);
    char **command = str_to_word_array(data, "\"");
    if (check_first_arg(command[0], command0) == 0) {
        return (check_others_args(command));
    } else
        return (0);
}
