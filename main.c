#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Queue.h"
#include "funcs.h"

#define FILENAME "programs.txt"

int main(){
    //Ficheiros
    int nPrograms = 0, nProcesses = 0;
    
    //obter os tamanhos(número de programas e processos)
    getsizesFile(FILENAME, &nPrograms, &nProcesses);

    //criação da matriz
    int** programas = malloc(nPrograms * sizeof(int*));
    for (int i = 0; i < nPrograms; i++) {
        programas[i] = malloc(nProcesses * sizeof(int));
    }

    //completar a matriz
    completeMat(FILENAME, programas, &nPrograms, &nProcesses);
    
    //Variáveis iniciais
    int tick = 0; // a instancia inicial que comeca em 0
    int cpt1 = 1; //variavel para teste do progroma atualmente a correr o running 
    int ir = 0; //indice do programam na queue do running 
    int nPExit = 0, exit = 1; //nPExit - numero de programas que ja sairam, exit - indica se um programa está para sair
    int ends[nPrograms]; //ends[] - array com os tempos de saida de todos os programas, end - variavel auxiliar para o calculo dos fins

    //Queues
    Queue running = CreateQueue(2); //A queue do running so pode ter 1 elemente mas caso seja preciso um outro programa começar a exeucao usamos um tamanho de 2 para
    //puder no teste do running fazer dequeue e nao termos um ciclo onde o running esta vazio
    Queue blocked = CreateQueue(nProcesses); //blocked podem estar muitos mas so sai quando o primeiro estiver a 0
    Queue ready = CreateQueue(nProcesses);  //podem estar varios mas so saiem quando o running tiver vazio    
    Queue new = CreateQueue(nProcesses); // pode haver varios processos a começar ao mesmo tempo

    //unblock
    int unblock = 3;//começamos com 3 porque ao fazer -5 = -2
    int unOcurred = 0;

    //Ver quando os programas acabam
    endPrograms(ends, programas, nPrograms, nProcesses);

    //Print inicial
    printf("Instant |");
    for(int i = 0; i < nPrograms; i++){
        printf("  proc%d         |", i + 1);
    }
    printf("\n");

    while (nPExit < nPrograms){
        if(tick < 10){
            printf("0");
        }

        printf("%d      | ", tick);

        //blocked
        blockedState(ready, blocked, programas, tick);

        //Unblock
        unblockState(ready, blocked, programas, unblock, &unOcurred);

        //ready
        readyState(ready, running, blocked, programas, &unblock, tick, &cpt1, &ir);

        //running
        runningState(running, blocked, programas, nProcesses, tick);

        //new
        newState(new, running, ready, programas, tick, &unblock, nPrograms);

        //Exit
        exitState(programas, ends, nPrograms, &nPExit);
        
        printStates(new, running, ready, blocked, programas, nPrograms, &unblock, &unOcurred);

        tick++; //aumentar o tick
    }
    
    return 0;
}