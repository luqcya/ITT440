#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 128

int main(){
    int pipe1[2], pipe2[2];
    pid_t child1_pid, child2_pid;

    if(pipe(pipe1) == -1 || pipe(pipe2) == -1){
        perror("Failed to create pipe");
        exit (EXIT_FAILURE);
    }
    child1_pid = fork();
    if(child1_pid == -1){
        perror("Failed to fork child 1");
        exit(EXIT_FAILURE);
    }
    else if(child1_pid == 0){
        close(pipe1[0]);
        char buffer[BUFFER_SIZE];
        printf("Child 1: Enter String: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        write(pipe1[1], buffer, BUFFER_SIZE);
        close(pipe1[1]);
        exit(EXIT_SUCCESS);
    }
    close(pipe1[1]);

    char buffer1[BUFFER_SIZE], buffer2[BUFFER_SIZE];
    read(pipe1[0], buffer1, BUFFER_SIZE);
    close(pipe1[0]);

    printf("Parent: String from Child 1: %s", buffer1);

    waitpid(child1_pid, NULL, 0);

    child2_pid = fork();
    if(child2_pid == -1){
        perror("Failed to fork child 2");
        exit(EXIT_FAILURE);
    }
    else if(child2_pid == 0){
        close(pipe2[0]);
        char buffer[BUFFER_SIZE];
        printf("Child 2: Enter String: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        write(pipe2[1], buffer, BUFFER_SIZE);
        close(pipe2[1]);
        exit(EXIT_SUCCESS);
    }

    close(pipe2[1]);
    read(pipe2[0], buffer2, BUFFER_SIZE);
    close(pipe2[0]);

    printf("Parent: String from Child 2: %s", buffer2);

    waitpid(child2_pid, NULL, 0);
    exit(EXIT_SUCCESS);
    return 0;
}