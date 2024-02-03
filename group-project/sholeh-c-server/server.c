#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>

#define DB_HOST "mysql"
#define DB_USER "root"
#define DB_PASSWORD "root123"
#define DB_NAME "itt440"
#define DB_PORT 3306

void update_database(MYSQL *mysql, const char *user, int points) {
    char query[256];
    sprintf(query, "SELECT * FROM itt440 WHERE user='%s'", user);

    if (mysql_query(mysql, query) != 0) {
        fprintf(stderr, "Error with SELECT query: %s\n", mysql_error(mysql));
        return;
    }

    MYSQL_RES *result = mysql_store_result(mysql);
    if (result == NULL) {
        fprintf(stderr, "Error storing result: %s\n", mysql_error(mysql));
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row) {
        points++;

        sprintf(query, "UPDATE itt440 SET points=%d, datetime_stamp=NOW() WHERE user='%s'", points, user);
    } else {
        sprintf(query, "INSERT INTO itt440 (user, points, datetime_stamp) VALUES ('%s', 1, NOW())", user);
    }

    if (mysql_query(mysql, query) != 0) {
        fprintf(stderr, "Error with UPDATE/INSERT query: %s\n", mysql_error(mysql));
    }

    mysql_free_result(result);
}

int main() {
    MYSQL *mysql = mysql_init(NULL);
    if (mysql == NULL) {
        fprintf(stderr, "Error initializing MySQL: %s\n", mysql_error(mysql));
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(mysql, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, DB_PORT, NULL, 0) == NULL) {
        fprintf(stderr, "Error connecting to MySQL: %s\n", mysql_error(mysql));
        mysql_close(mysql);
        exit(EXIT_FAILURE);
    }

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        mysql_close(mysql);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9002);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error binding socket");
        close(serverSocket);
        mysql_close(mysql);
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 5) == -1) {
        perror("Error listening on socket");
        close(serverSocket);
        mysql_close(mysql);
        exit(EXIT_FAILURE);
    }

    printf("C Server listening on port 6002\n");

    while (1) {
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == -1) {
            perror("Error accepting connection");
            continue;
        }

        char buffer[1024];
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead == -1) {
            perror("Error receiving data");
            close(clientSocket);
            continue;
        }

        buffer[bytesRead] = '\0';
        char user[256];
        int points;
        sscanf(buffer, "%[^,],%d", user, &points);

        update_database(mysql, user, points);
        printf("Updated user %s's points.\n", user);

        close(clientSocket);
    }

    mysql_close(mysql);
    close(serverSocket);
    return 0;
}
