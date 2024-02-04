#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void get_latest_points(const char *user, const char *serverHostname);

int main() {
    const char *user = "fakhirul-c";
    const char *serverHostname = "172.16.238.10";

    get_latest_points(user, serverHostname);

    return 0;
}

void get_latest_points(const char *user, const char *serverHostname) {
    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(6123);
    serverAddress.sin_addr.s_addr = inet_addr(serverHostname);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error connecting to the server");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    // Send update request to the server
    char request[256];
    snprintf(request, sizeof(request), "%s,update", user);
    write(clientSocket, request, strlen(request) + 1);

    // Receive and print the server's response
    char response[256];
    ssize_t bytesRead = read(clientSocket, response, sizeof(response));
    if (bytesRead == -1) {
        perror("Error receiving data");
    } else {
        response[bytesRead] = '\0';
        printf("Server response: %s\n", response);
    }

    // Close the socket
    close(clientSocket);
}