#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

int main()
{
    int sockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    char buffer[256];

    // create a socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // set up the server address structure
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // bind the socket to the server address
    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // receive the message from the client
    recvfrom(sockfd, buffer, 255, 0, (struct sockaddr *)&cli_addr, &clilen);

    // print the message received from the client
    printf("Message from client: %s", buffer);

    // prompt the user for a message to send
    printf("Enter a message to send: ");
    fgets(buffer, 255, stdin);

    // send the message to the client
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&cli_addr, clilen);

    // close the socket
    close(sockfd);

    return 0;
}
