#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8083
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[BUF_SIZE];
    socklen_t len = sizeof(servaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) { perror("socket"); exit(EXIT_FAILURE); }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    printf("UDP Chat Client. Type 'exit' to quit.\n");
    while (1) {
        printf("You: ");
        fgets(buffer, BUF_SIZE, stdin);
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr*)&servaddr, len);
        if (strncmp(buffer, "exit", 4)==0) break;
        ssize_t n = recvfrom(sockfd, buffer, BUF_SIZE, 0,
                             NULL, NULL);
        buffer[n] = '\0';
        printf("Server: %s", buffer);
    }
    close(sockfd);
    return 0;
}