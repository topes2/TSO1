#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcs.h"

void getsizesFile(char *filename, int *numPrograms, int *numProcesses){
    char line[200];

    FILE *f = fopen("programs.txt", "r");

    if(f == NULL){
        printf("Error opening file\n");
        exit(-2);
    }

    if(fgets(line, sizeof(line), f) == NULL){
        //arquivo não tem conteudo
        printf("No content in file\n");
        exit(0);
    }
    *numPrograms += 1;

    int pos = strcspn(line, "\n");
    line[pos] = '\0';
    
    for (int i = 0; i < strlen(line); i++){
        if(line[i] == ' '){
            *numProcesses += 1;
        }
    }
    *numProcesses += 1; //para o ultimo numero

    //ver o número de programas
    while(fgets(line, sizeof(line), f) != NULL){
        *numPrograms += 1;
    }

    fclose(f);

    return;
}

int completeMat(char *filename, int **programs, int *numPrograms, int *numProcesses){

    FILE *f = fopen("programs.txt", "r");

    if(f == NULL){
        printf("Error opening file\n");
        exit(-2);
    }

    for(int i = 0; i < *numPrograms; i++){
        for(int j = 0; j < *numProcesses; j++){
            if(fscanf(f, "%d", &programs[i][j]) != 1){
                printf("error\n");
            }

        }
    }

    fclose(f);

    return 1;
}