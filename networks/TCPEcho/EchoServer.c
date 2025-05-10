#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[BUF_SIZE];
    socklen_t len = sizeof(cliaddr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); exit(EXIT_FAILURE); }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind"); exit(EXIT_FAILURE);
    }
    if (listen(sockfd, 5) < 0) {
        perror("listen"); exit(EXIT_FAILURE);
    }
    printf("TCP Echo Server listening on port %d\n", PORT);

    connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if (connfd < 0) { perror("accept"); exit(EXIT_FAILURE); }

    while (1) {
        ssize_t n = recv(connfd, buffer, BUF_SIZE, 0);
        if (n <= 0) break;
        send(connfd, buffer, n, 0);
    }
    close(connfd);
    close(sockfd);
    return 0;
}