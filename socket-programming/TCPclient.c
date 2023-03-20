#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[1024];

    // create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // set server address properties
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(12345);

    // connect to the server
    connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // get input message from user
    printf("Enter message: ");
    fgets(buffer, sizeof(buffer), stdin);

    // send the message to the server
    write(client_socket, buffer, strlen(buffer));

    // close the connection
    close(client_socket);

    return 0;
}
