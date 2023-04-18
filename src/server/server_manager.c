/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** Server Manager
*/

#include "server.h"
#include "list.h"

/**
 * Init socket address
 * @param server - Server to init.
 * @param port - Port to init.
 */
void init_socketaddr(server_t *server, int port)
{
    memset(&server->sockaddr, 0, sizeof(server->sockaddr));
    server->sockaddr.sin_family = AF_INET;
    server->sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    server->sockaddr.sin_port = htons(port);
}

/**
 * Create server and queue.
 * @param port - Port listening for socket.
 * @param dir - Base of directory for server.
 * @see typedef server_t
 * @return - Return typedef server_t malloc.
 */
server_t *create_server(int port)
{
    server_t *server = MALLOC(sizeof(server_t));
    server->clients = NULL;
    server->users = NULL;
    server->teams = NULL;
    server->user_in_teams = NULL;
    server->discusses = NULL;
    int ret;
    server->socket_fd = create_socket();
    init_socketaddr(server, port);
    ret = bind(server->socket_fd, (struct sockaddr *) &server->sockaddr,
        sizeof(server->sockaddr));
    if (ret < 0)
        perror_exit("bind()");
    ret = listen(server->socket_fd, MAX_CONNECTIONS);
    if (ret < 0)
        perror_exit("listen()");
    return server;
}

/**
 * Add new user to server on new connection.
 * @param server - Server to add user.
 */
void new_connection(server_t *server)
{
    if (FD_ISSET(server->socket_fd, &server->readfds)) {
        client_t *client = create_client(server->socket_fd);
        if (client->socket_fd < 0) {
            perror_exit("Erreur lors de l'acceptation de la connexion client");
        }
        dprintf(1, "Nouveau client connecté : %s:%d\r\n",
            inet_ntoa(client->sockaddr.sin_addr),
            ntohs(client->sockaddr.sin_port));
        server->last_fd = client->socket_fd;
        put_in_list(&server->clients, client);
        send_packet(client->socket_fd, create_packet(SUCCESS, "You are now "
            "connected to the server."));
    }
}

/**
 * Manage all action of users.
 * @param server - Server to manage.
 */
void handle_client(server_t *server)
{
    int activity;
    server->last_fd = server->socket_fd;
    bool is_running = true;
    while (is_running) {
        FD_ZERO(&server->readfds);
        FD_SET(0, &server->readfds);
        FD_SET(server->socket_fd, &server->readfds);
        for (node *tmp = server->clients;
            tmp != NULL; tmp = tmp->next)
            FD_SET(((client_t *) tmp->data)->socket_fd, &server->readfds);

        activity = select(server->last_fd + 1, &server->readfds, NULL, NULL,
            NULL);
        if ((activity < 0) && (errno != EINTR)) {
            printf("Erreur lors de la surveillance des sockets\n");
        }
        read_action(server, &is_running);
        new_connection(server);
    }
}
