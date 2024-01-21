#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 11235
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
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Assuming server is running locally

    // Client loop
    while (1) {
        // Get user input for the term number
        int termNumber;
        printf("Enter term number (or -1 to quit): ");
        scanf("%d", &termNumber);

        // Send the term number to the server
        char buffer[BUFFER_SIZE];
        snprintf(buffer, sizeof(buffer), "%d", termNumber);
        sendto(clientSocket, buffer, strlen(buffer), 0,
               (struct sockaddr*)&serverAddr, sizeof(serverAddr));

        // Receive and print the Fibonacci sequence from the server
        for (int i = 0; i < 5; ++i) {
            ssize_t bytesReceived = recvfrom(clientSocket, buffer, sizeof(buffer), 0, NULL, NULL);
            if (bytesReceived == -1) {
                perror("Error receiving data");
                close(clientSocket);
                exit(EXIT_FAILURE);
            }
            buffer[bytesReceived] = '\0'; // Null-terminate the received data
            printf("%s", buffer);
        }

        // Ask the user if they want more sequences
        int choice;
        printf("\nDo you want more sequences? (1 for yes, 0 for no): ");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }
    }

    // Close the socket
    close(clientSocket);

    return 0;
}
