#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 22000
#define BUFFER_SIZE 1024

int main() {
    // Create socket
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Send a request to the server
    sendto(clientSocket, "Time request", strlen("Time request"), 0,
           (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Receive and print the time from the server
    char buffer[BUFFER_SIZE];
    ssize_t bytesReceived = recvfrom(clientSocket, buffer, sizeof(buffer), 0, NULL, NULL);
    if (bytesReceived == -1) {
        perror("Error receiving data");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    printf("Time received from server:\n%s\n", buffer);

    // Close the socket
    close(clientSocket);

    return 0;
}
