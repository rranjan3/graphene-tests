#include <stdio.h>
#include "str.h"

int main() {
    for(int i=0;i<5;i++) // loop will run n times (n=5) 
    { 
        if(fork() == 0) 
        { 
            printf("===========================================[son] pid %d from [parent] pid %d\n",getpid(),getppid()); 
            while(1){
               unsigned int i = 0;
               while( i < 1000000) i++;
            }
            exit(0); 
        } 
    } 
    for(int i=0;i<5;i++) // loop will run n times (n=5) 
        wait(NULL); 
    return 0;
}
