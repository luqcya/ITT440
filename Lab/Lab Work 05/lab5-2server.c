#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 27679
#define BUFFER_SIZE 1024
#define NUM_RANDOM_NUMBERS 5

int main() {
    // Create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    struct sockaddr_in serverAddr;
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

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        perror("Error listening");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Server loop
    while (1) {
        // Accept a connection
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == -1) {
            perror("Error accepting connection");
            continue;
        }

        // Generate and send random numbers to the client
        for (int i = 0; i < NUM_RANDOM_NUMBERS; ++i) {
            int randomNumber = rand() % 100; // Generate a random number between 0 and 99
            char buffer[BUFFER_SIZE];
            snprintf(buffer, sizeof(buffer), "Random number %d: %d\n", i + 1, randomNumber);

            // Send the random number to the client
            send(clientSocket, buffer, strlen(buffer), 0);
        }

        // Close the client socket
        close(clientSocket);
    }

    // Close the server socket
    close(serverSocket);

    return 0;
}
