#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT 8084
#define MESSAGE "Broadcast message"

int main() {
    int sockfd;
    struct sockaddr_in bcast_addr;
    int broadcast = 1;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));

    memset(&bcast_addr, 0, sizeof(bcast_addr));
    bcast_addr.sin_family = AF_INET;
    bcast_addr.sin_port = htons(PORT);
    bcast_addr.sin_addr.s_addr = inet_addr("255.255.255.255");

    sendto(sockfd, MESSAGE, strlen(MESSAGE), 0,
           (struct sockaddr*)&bcast_addr, sizeof(bcast_addr));
    printf("Broadcast sent\n");
    close(sockfd);
    return 0;
}