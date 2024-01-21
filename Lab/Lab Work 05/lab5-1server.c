#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 22000
#define BUFFER_SIZE 1024

int main() {
    // Create socket
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Server loop
    while (1) {
        char buffer[BUFFER_SIZE];
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        // Receive request from client
        ssize_t bytesReceived = recvfrom(serverSocket, buffer, sizeof(buffer), 0,
                                         (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (bytesReceived == -1) {
            perror("Error receiving data");
            continue;
        }

        // Get current time
        time_t currentTime;
        time(&currentTime);

        // Convert time to string and send it back to the client
        char* timeString = ctime(&currentTime);
        sendto(serverSocket, timeString, strlen(timeString), 0,
               (struct sockaddr*)&clientAddr, sizeof(clientAddr));
    }

    // Close the socket
    close(serverSocket);

    return 0;
}
