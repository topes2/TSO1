#include <stdio.h>
#include <string.h>
#include "tb1.h"

#define READY 0;
#define RUN 1;

int check(int p[],int sz){ // ver se ha algum valor de tempo inferior a 0
    for(int i = 0; i <= sz;i++){
        if(p[i]<0)
            return 1; //erro no input dos programas, nao ha tempo negativo
    }
    return 0;
}


void setsize(program p,int size){
    for(int i;i <= size;i++){
        

    }
}

int getsize(program p[]){ //em caso de nao sabermos o tamanho
    return (sizeof(p) / sizeof(int));
}