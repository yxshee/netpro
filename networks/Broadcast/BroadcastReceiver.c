#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT 8084
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in addr;
    char buffer[BUF_SIZE];
    socklen_t len = sizeof(addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));

    printf("Listening for broadcasts on port %d\n", PORT);
    ssize_t n = recvfrom(sockfd, buffer, BUF_SIZE, 0,
                         (struct sockaddr*)&addr, &len);
    buffer[n] = '\0';
    printf("Received: %s\n", buffer);
    close(sockfd);
    return 0;
}