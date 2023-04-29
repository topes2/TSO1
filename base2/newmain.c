#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "funcs.h"

/*TODO
INPUTS
CONDIÇÃO DE FIM
*/

void main(){
    int programas[3][8] = {
    {1, 3, 1, 2, 2, 4, 0, 0 } ,
    {1, 4, 2, 4, 1, 3, 0, 0 } ,
    {3, 2, 1, 6, 1, 3, 0, 0 }};


    int tick = 0; // a instancia inicial que comeca em 0
    int qpr = sizeof(programas)/sizeof(programas[0]); //quantidade de programas
    int qp = (sizeof(programas)/qpr)/sizeof(int); //aqui temos a quantidade de processos
    int cpt1 = 1; //variavel para teste do progrma atualmente a correr o running 
    int ir = 0; //indice do programam na queue do running 
    int nPExit = 0, exit = 1; //nPExit - numero de programas que ja sairam, exit - indica se um programa esta para sair
    int ends[qpr], end; //ends[] - array com os tempos de saida de todos os programas, end - variavel auxiliar para o calculo dos fins

    Queue running = CreateQueue(2); //so pode estar 1 programa a correr mas pomos o seguinte no ciclo final do programa a correr
    Queue blocked = CreateQueue(qp); //blocked podem estar muitos mas so sai quando o primeiro estiver a 0
    Queue ready = CreateQueue(qp);  //podem estar varios mas so saiem quando o running tiver vazio    
    Queue new = CreateQueue(qp); // pode haver varios processos a começar ao mesmo tempo

    //Ver quando os programas acabam
    for(int i = 0; i < qpr; i++){
        end = 0;
        for(int j = qp - 1; j > 0; j--){
            if(programas[i][j] == 0){
                end++;
            } else {
                ends[i] = qp - end;
            }
        }
    }

    printf("Instant |");
    for(int i = 0; i < qpr; i++){
        printf("  proc%d  |", i + 1);
    }
    printf("\n");
    
    while (nPExit < qpr){ //add a condiçao de 
            if(tick < 10){
                printf("0");
            }

            printf("%d      | ", tick);

            int cp = 0; //programa a começar em
            int cpt = 1; 
                
            if(!IsEmptyQueue(ready)){
                int i1 = (Front(ready) - 5);
                while(programas[i1][cpt] == -1){
                    cpt++;                           //current process timer
                }
                if(cpt == 0){
                    Dequeue(ready);
                }
                if(!IsEmptyQueue(running)){
                ir = (Front(running)-5);
                while(programas[ir][cpt1] == -1){
                    cpt1++;                           //current process timer
                }
                }

                if( (cpt%2!= 0) && (programas[i1][cpt] > 0) && (IsEmptyQueue(running) || (programas[ir][cpt1] - tick == 0))){
                    programas[i1][cpt] = programas[i1][cpt] + tick;
                    Enqueue(Dequeue(ready), running);
                }else if(programas[i1][cpt] <= 0 && cpt%2 != 0 && programas[i1][0] != -1){
                    programas[i1][cpt] = -1;
                    programas[i1][cpt+1] = programas[i1][cpt+1] + tick;
                    Enqueue(Dequeue(ready), blocked);
                }else if((cpt%2 == 0 || ((programas[i1][cpt] == 0  && cpt%2 != 0))) && programas[i1][0] != -1){
                    programas[i1][cpt] = programas[i1][cpt] + tick;
                    Enqueue(Dequeue(ready), blocked);
                }
            }
            /*
            
            */

            if(!IsEmptyQueue(blocked)){ //test block
                int i1 = (Front(blocked) - 5);
                cpt = 1;
                while(programas[i1][cpt] == -1){
                    cpt++;                           //current process timer
                }
                if(programas[i1][cpt] - tick <= 0){
                    programas[i1][cpt] = -1;
                    Enqueue(Dequeue(blocked), ready);
                }
            }

            /*
            A parte do codigo responsavel para a verificação se a queue do block
            começa com um teste se a queue block esta vazia se não estiver procede a encontrar o indice 
            do programa que esta atualmente na front da queue e verifica a instancia que o prorama é suposto sair
            do estado blocked, se for caso que a instancia de saida é a instancia atual entao
            iguala o tempo de blocked a -1 para marcar como concluido e envia o seu indice para a queue ready
            */

            if(!IsEmptyQueue(running)){ 
                int i1 = (Front(running) - 5);
                cpt = 1;
                while(programas[i1][cpt] == -1 && cpt < qp){
                    cpt++;                           //current process timer
                }
                if(programas[i1][cpt] - tick <= 0){
                    programas[i1][cpt] = -1;
                    programas[i1][cpt+1] = programas[i1][cpt+1] + tick;
                    Enqueue(Dequeue(running), blocked);
                }

            }
            /*
            A parte do codigo que testa a queue do running 
            começa com um teste da front da queue e utiliza a variavel i1 para guardar esse valor
            
            */
            

            //ciclo new, objetivos é fazer enqueue e depois por no ready ou no running
            for(int i = 0; i + cp < qpr;i++){
                
                if((programas[i][0] == tick) && (programas[i][0] != -1)){
                    Enqueue((i + 5), new);
                }else if(programas[i][0] < tick && hasValue((i+5), new)) {
                    if(programas[i][1] > 0 && IsEmptyQueue(running)){
                        programas[i][1] = programas[i][1] + tick;
                        Enqueue(Dequeue(new), running); //entrar no running se estiver vazio e tiver tempo para la correr
                    }else {
                            Enqueue(Dequeue(new), ready); //se nao, entra no ready
                    }
                }
                
            }
        
        //Exit
        for(int i = 0; i < qpr; i++){
            if(programas[i][0] != -1){
                for(int j = 1; j < ends[i]; j++){
                    if(programas[i][j] != -1){
                        exit = 0;
                    }
                }
                
                if(exit){
                    programas[i][0] = -1;
                    printf("EXIT    | ");
                    nPExit++;
                }
                exit = 1;
            } else {
                printf("        | ");
            }
        }

        for (int i = 0; i < qpr; i++) {
            if (hasValue(i + 5, new) && programas[i][0] != -1) {
                printf("NEW     | ");
            } else if (hasValue(i + 5, running) && programas[i][0] != -1) {
                printf("RUN     | ");
            } else if (hasValue(i + 5, ready) && programas[i][0] != -1) {
                printf("READY   | ");
            } else if (hasValue(i + 5, blocked) && programas[i][0] != -1) {
                printf("BLOCKED | ");
            } else if(programas[i][0] != -1){
                printf("        | ");
            }                                     
        } 
        printf("\n");
        tick++;
    }
}