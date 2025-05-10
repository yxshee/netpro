#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MCAST_GROUP "224.0.0.1"
#define MCAST_PORT 8085
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in addr;
    struct ip_mreq mreq;
    char buffer[BUF_SIZE];
    socklen_t addrlen = sizeof(addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(MCAST_PORT);
    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));

    mreq.imr_multiaddr.s_addr = inet_addr(MCAST_GROUP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
               (void*)&mreq, sizeof(mreq));

    printf("Listening for multicast on %s:%d\n", MCAST_GROUP, MCAST_PORT);
    ssize_t n = recvfrom(sockfd, buffer, BUF_SIZE, 0,
                         (struct sockaddr*)&addr, &addrlen);
    buffer[n] = '\0';
    printf("Received: %s\n", buffer);
    close(sockfd);
    return 0;
}