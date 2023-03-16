/*
** EPITECH PROJECT, 2023
** myftp
** File description:
** utils
*/

#include "main.h"


/**
 * Exit with error message.
 * @param string
 */
void perror_exit(const char *string)
{
    perror(string);
    exit_all(EXIT_FAILURE);
}

/**
 * Print help message.
 */
void help_init(void)
{
    printf("USAGE: ./myftp port path\r\n");
    printf("\tport is the port number on which "
           "the server socket listens\r\n");
    printf("\tpath is the path to the home directory "
           "for the Anonymous user\r\n");
}

/**
 * Exit with free and is use for handle of SIGINT signal
 * @param code if 84 exit with 84 otherwise exit with 0.
 */
void exit_all(int code)
{
    FREE_ALL();
    exit(code == 84 ? 84 : 0);
}

/**
 *
 * @param fd
 * @return
 */
string get_read(int fd)
{
    string result = MALLOC(sizeof(char) * 1024);
    string buff = MALLOC(sizeof(char) * 1024);
    memset(buff, 0, sizeof(char) * 1024);
    memset(result, 0, sizeof(char) * 1024);
    string end = NULL;
    while (end == NULL) {
        read(fd, buff, 1024);
        strcat(result, buff);
        end = strstr(result, "\r\n");
    }
    FREE(buff);
    end[0] = '\0';
    return result;
}
