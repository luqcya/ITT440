#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigkill_handler(int sig){
    printf("received SIGKILL signal \n");
    exit(0);
}

int main(){
    if(signal(SIGKILL, sigkill_handler) == SIG_ERR){
        perror("signal");
        exit(1);
    }
    printf("waiting for SIGKILL signal");
    while (1)
    {
        
    }

    return 0;
    
}