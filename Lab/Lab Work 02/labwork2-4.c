#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigterm_handler(int sig){
    printf("received SIGTERM signal\n");
}

int main(){
    if(signal(SIGTERM,sigterm_handler) == SIG_ERR){
        perror("signal");
        exit(1);
    }
    printf("waiting for SIGTERM signal\n");
    while (1)
    {
    
    }
    return 0;
    
}