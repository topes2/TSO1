#include "tb1.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{   
    //Ficheiros
    char fileName[20] = "in.txt";
    FILE *f;
    f = fopen(fileName, "r");

    if(f == NULL){
        printf("File %s not found!\n", fileName);
        return 1;
    }

    //leitura dos dados (0 - nº de programas, 1 - nº de )
    int sizes[2];
    fscanf(f, "%d", &sizes[0]);
    fscanf(f, "%d", &sizes[1]);

    
    //Criação da matriz para guardar os valores
    int programs[sizes[0]][sizes[1]], value;

    for(int i = 0; i < sizes[0]; i++){
        for(int j = 0; j < sizes[1]; j++){
            fscanf(f, "%d", &programs[i][j]);
        }
    }

    fclose(f);

    /*
    struct program p1;
    struct program p2;
    struct program p3;
    p1.size = p2.size = p3.size = 8;
    int np[8] = {5, 8, 6, 4, 7, 5, 9, 10};
    int np1[8] = {5, 8, 6, 4, 7, 5, 9, 10};
    int np2[8] = {5, 8, 6, 4, 7, 5, 9, 10};
    p1 = setup(p1, np);
    p2 = setup(p2, np1);
    p3 = setup(p3, np2);
    // pp(p1);
    printf("\n\n\n");
    */

    return 0;
}