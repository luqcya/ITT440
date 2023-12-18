#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int id = fork();
    if(id != 0){
        fork();
    }
    printf("hellow\n");
    // if(id == 0){
    //     printf("hello from child\n");
    // }
    // else{
    //     printf("hello from parent\n");
    // }
    return 0;
}