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
        client_t *client = MALLOC(sizeof(client_t));
        client->user = NULL;
        client->context = NONE;
        client->socket_fd = accept(server->socket_fd,
        (struct sockaddr *)
        &client->sockaddr,
        &client->len);
        if (client->socket_fd < 0) {
            perror_exit("Erreur lors de l'acceptation de la connexion client");
        }
        dprintf(1, "Nouveau client connecté : %s:%d\r\n",
            inet_ntoa(client->sockaddr.sin_addr),
            ntohs(client->sockaddr.sin_port));
        server->last_fd = client->socket_fd;
        put_in_list(&server->clients, client);
        send_packet(client->socket_fd, create_packet(SUCCESS, "test"));
    }
}

/**
 * Handle message of user and execute commands.
 * @param server - Server to handle.
 */
void read_action(server_t *server)
{
    client_t *tmp_client;

    for (node *tmp_node = server->clients;
        tmp_node != NULL; tmp_node = tmp_node->next) {
        tmp_client = tmp_node->data;
        if (FD_ISSET(tmp_client->socket_fd, &server->readfds)) {
            packet_t *socket = read_packet(tmp_client->socket_fd);
            disconect_client(server, tmp_client, strlen(socket->data));
            command_client(server, tmp_client, socket);
            FREE(socket);
        }
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
    while (1) {
        FD_ZERO(&server->readfds);
        FD_SET(server->socket_fd, &server->readfds);
        for (node *tmp_node = server->clients;
            tmp_node != NULL; tmp_node = tmp_node->next)
            FD_SET(((client_t *) tmp_node->data)->socket_fd, &server->readfds);

        activity = select(server->last_fd + 1, &server->readfds, NULL, NULL,
            NULL);
        if ((activity < 0) && (errno != EINTR)) {
            printf("Erreur lors de la surveillance des sockets\n");
        }
        read_action(server);
        new_connection(server);
    }
}
