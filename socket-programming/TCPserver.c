#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server_socket, client_socket;                  // client_socket and server_socket are file descriptors
    struct sockaddr_in server_address, client_address; // creating structures of the type sockaddr_in
    char buffer[1024];

    // create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // set server address properties
    server_address.sin_family = AF_INET;         // setting the family of the server address to AF_INET
    server_address.sin_addr.s_addr = INADDR_ANY; // setting the IP address of the server address to INADDR_ANY
    server_address.sin_port = htons(12345);      // setting the port number of the server address

    // bind the socket to the address
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // start listening for incoming connections
    listen(server_socket, 5); // 5 is the number of clients that can connect to the server
    printf("Server is listening for incoming connections...\n");

    // accept a new connection
    socklen_t client_address_size = sizeof(client_address);                                          // storing the length of the client address
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_size); // accepting the client connection
    printf("Connected by %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

    // receive data from client
    memset(buffer, 0, sizeof(buffer));           // memset is used to fill a block of memory with a particular value (in this case, with 0)
    read(client_socket, buffer, sizeof(buffer)); // reading the message from the client and storing it in buffer
    printf("Received message: %s\n", buffer);    // display the message in the buffer

    // close the connection
    close(client_socket);
    close(server_socket);

    return 0;
}
