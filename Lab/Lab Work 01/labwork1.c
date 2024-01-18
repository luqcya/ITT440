#include <unistd.h>
#include <stdio.h>
// #include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t child_pid;
    int child_status;

    child_pid = fork();

    switch (child_pid){
        case -1:
            perror("fork");
            exit(1);

        case 0:
            printf("hello world\n");
            exit(0);

        default:
            wait(&child_status);
    }
}

