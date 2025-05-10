#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8082
#define BUF_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    char buffer[BUF_SIZE];
    socklen_t addrlen = sizeof(addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); exit(EXIT_FAILURE); }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);
    printf("TCP Chat Server listening on %d\n", PORT);

    client_fd = accept(server_fd, (struct sockaddr*)&addr, &addrlen);
    printf("Client connected\n");

    while (1) {
        ssize_t n = recv(client_fd, buffer, BUF_SIZE, 0);
        if (n <= 0 || strncmp(buffer, "exit", 4) == 0) break;
        buffer[n] = '\0';
        printf("Client: %s", buffer);
        printf("You: ");
        fgets(buffer, BUF_SIZE, stdin);
        send(client_fd, buffer, strlen(buffer), 0);
        if (strncmp(buffer, "exit", 4) == 0) break;
    }
    close(client_fd);
    close(server_fd);
    return 0;
}