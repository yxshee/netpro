#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#define MCAST_GROUP "224.0.0.1"
#define MCAST_PORT 8085
#define MESSAGE "Multicast message"

int main() {
    int sockfd;
    struct sockaddr_in mcast_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&mcast_addr, 0, sizeof(mcast_addr));
    mcast_addr.sin_family = AF_INET;
    mcast_addr.sin_addr.s_addr = inet_addr(MCAST_GROUP);
    mcast_addr.sin_port = htons(MCAST_PORT);

    sendto(sockfd, MESSAGE, strlen(MESSAGE), 0,
           (struct sockaddr*)&mcast_addr, sizeof(mcast_addr));
    printf("Multicast sent\n");
    close(sockfd);
    return 0;
}