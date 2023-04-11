#include <stdio.h>
#include <string.h>
#include "tb1.h"

#define READY 0;
#define RUN 1;
#define SIZE 8;

program setup(program p1, int n[8] ){
    for (int i = 0; i < p1.size; i++){
        p1.plist[i].cputime = n[i];
        if(i == 0){
            p1.plist[i].state = RUN;
        } else {
            p1.plist[i].state = READY;
        }
            
        printf(" %d %d//",n[i],i);
    }
    printf("\n");
    return p1;
}

//debugggggggs 
void printp(program p){
    for (int i = 0;i < p.size; i++){
    printf("%d %d\n", p.plist[i].cputime, i);
    }
}


void pp(program p){
    int psize = 20 + 7*p.size;
    /*char header[psize] = ps(p.size); a maneira que deviamos fazer mas da erro*/
    char toppart[100];
    *toppart = ps(p.size);
    printf("%s",toppart);
}

char ps(int i){
    char temp[15];
    char part1[1000] = {"instante "};
    for(int i1 = 0;i1 < i;i1++){
        char base[20] = {" | proc"};
        char num[2];
        num[0] = i;
        num[1] = '0';
        strcat(num,base);
        strcat(temp,part1);
    }
}




//cada process é a sua propria struct cada program ade ser um struct com um array e depois uma queue para correr os programas que em si correm os processos
