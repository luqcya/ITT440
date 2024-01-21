#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 11235
#define BUFFER_SIZE 1024
#define FIBO_SEQUENCE_LENGTH 5

unsigned long long fibonacci(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    // Create socket
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    struct sockaddr_in serverAddr, clientAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        char buffer[BUFFER_SIZE];
        socklen_t clientAddrLen = sizeof(clientAddr);

        // Receive request from client
        ssize_t bytesReceived = recvfrom(serverSocket, buffer, sizeof(buffer), 0,
                                         (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (bytesReceived == -1) {
            perror("Error receiving data");
            continue;
        }

        // Extract the term number from the client's request
        int termNumber = atoi(buffer);

        // Generate and send the Fibonacci sequence
        char responseBuffer[BUFFER_SIZE];
        for (int i = 0; i < FIBO_SEQUENCE_LENGTH; ++i) {
            unsigned long long fiboTerm = fibonacci(termNumber + i);
            snprintf(responseBuffer, sizeof(responseBuffer), "Term %d: %llu\n", termNumber + i, fiboTerm);

            // Send the Fibonacci term to the client
            sendto(serverSocket, responseBuffer, strlen(responseBuffer), 0,
                   (struct sockaddr*)&clientAddr, clientAddrLen);
        }
    }

    // Close the socket
    close(serverSocket);

    return 0;
}
