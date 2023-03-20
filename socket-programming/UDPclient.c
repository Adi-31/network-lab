#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[256];

    // create a socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // set up the server address structure
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // prompt the user for a message to send
    printf("Enter a message to send: ");
    fgets(buffer, 255, stdin);

    // send the message to the server
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // receive the message from the server
    recvfrom(sockfd, buffer, 255, 0, NULL, NULL);

    // print the message received from the server
    printf("Message from server: %s", buffer);

    // close the socket
    close(sockfd);

    return 0;
}
