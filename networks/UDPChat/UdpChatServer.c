#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8083
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[BUF_SIZE];
    socklen_t len = sizeof(cliaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) { perror("socket"); exit(EXIT_FAILURE); }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    printf("UDP Chat Server on port %d\n", PORT);
    while (1) {
        ssize_t n = recvfrom(sockfd, buffer, BUF_SIZE, 0,
                             (struct sockaddr*)&cliaddr, &len);
        buffer[n] = '\0';
        if (strncmp(buffer, "exit", 4)==0) break;
        printf("Client: %s", buffer);
        printf("You: ");
        fgets(buffer, BUF_SIZE, stdin);
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr*)&cliaddr, len);
        if (strncmp(buffer, "exit", 4)==0) break;
    }
    close(sockfd);
    return 0;
}