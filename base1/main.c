#include "tb1.h"
#include <stdio.h>
#include <stdlib.h>

void main(){

    //Ficheiros
    char fileName[20] = "in.txt";
    FILE *f;
    f = fopen(fileName, "r");

    if(f == NULL){
        printf("File %s not found!\n", fileName);
        //return 1; temos de usar error catching aqui mas pronto
    }

    //leitura dos dados (0 - nº de programas, 1 - nº de processos )
    int sizes[2];
    fscanf(f, "%d", &sizes[0]);
    fscanf(f, "%d", &sizes[1]);
    struct program *s = malloc(sizeof(struct program) + sizes[1] * sizeof(ptime));

    program programas[sizes[0]]; // criar um array para guardar os programas a correr, talvez usar queues ou listas para isto mais tarde
    programas->sz[sizes[1]];
    int value;
    int p = 0;

    for (int i = 0; i < sizes[0]; i++) {
    int p = 0;
    for (int j = 0; j < sizes[1]; j++) {
        if (j % 2 == 0) {
            fscanf(f, "%d", &programas[i].pl[p].time);
            programas[i].pl[p].type = 0;
        } else {
            fscanf(f, "%d", &programas[i].pl[p].time);
            programas[i].pl[p].type = 1;
            p++;
        }
    }
    }

    printf("Don't call it a debug");
    


    
    //Criação da matriz para guardar os valores   vou comentar isto so para tentar usar bi dimensional arrays 
    /*
    int programs[sizes[0]][sizes[1]], value;

    for(int i = 0; i < sizes[0]; i++){
        for(int j = 0; j < sizes[1]; j++){
            fscanf(f, "%d", &programs[i][j]);
        }
    }
    */

    fclose(f);

}