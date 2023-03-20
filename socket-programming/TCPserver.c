#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    char buffer[1024];

    // create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // set server address properties
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(12345);

    // bind the socket to the address
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // start listening for incoming connections
    listen(server_socket, 1);
    printf("Server is listening for incoming connections...\n");

    // accept a new connection
    socklen_t client_address_size = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_size);
    printf("Connected by %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

    // receive data from client
    memset(buffer, 0, sizeof(buffer));
    read(client_socket, buffer, sizeof(buffer));
    printf("Received message: %s\n", buffer);

    // close the connection
    close(client_socket);
    close(server_socket);

    return 0;
}
