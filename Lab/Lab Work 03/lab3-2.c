#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child1, child2;
    int status1, status2;

    child1 = fork();

    if (child1 < 0) {
        perror("Fork failed for child1");
        exit(EXIT_FAILURE);
    } else if (child1 == 0) {
        printf("Child 1 (PID: %d) is running\n", getpid());
        exit(EXIT_SUCCESS);
    }

    child2 = fork();

    if (child2 < 0) {
        perror("Fork failed for child2");
        exit(EXIT_FAILURE);
    } else if (child2 == 0) {
        printf("Child 2 (PID: %d) is running\n", getpid());
        exit(EXIT_SUCCESS);
    }

    waitpid(child1, &status1, 0);

    printf("Child 1 (PID: %d) exited with status %d\n", child1, WEXITSTATUS(status1));

    return 0;
}