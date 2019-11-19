#include <stdio.h>
#include "str.h"

int main() {
    while(1){
       unsigned int i = 0;
       printf("======================================Within main=================================== \n");
       get_string();
       while( i < 1000000) i++;
    }
     return 0;
}
