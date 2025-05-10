#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8082
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); exit(EXIT_FAILURE); }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    printf("Connected to Chat Server. Type 'exit' to quit.\n");

    while (1) {
        printf("You: ");
        fgets(buffer, BUF_SIZE, stdin);
        send(sockfd, buffer, strlen(buffer), 0);
        if (strncmp(buffer, "exit", 4) == 0) break;
        ssize_t n = recv(sockfd, buffer, BUF_SIZE, 0);
        buffer[n] = '\0';
        printf("Server: %s", buffer);
        if (strncmp(buffer, "exit", 4) == 0) break;
    }
    close(sockfd);
    return 0;
}