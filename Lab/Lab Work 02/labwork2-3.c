#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sighup_handler(int sig){
    printf("received SIGHUP signal\n");
    exit(0);
}

int main(){
    if(signal(SIGHUP, sighup_handler) == SIG_ERR){
        perror("signal");
        exit(1);
    }
    printf("waiting for SIGHUP signal\n");
    while (1)
    {
    
    }
    return 0;
    
}