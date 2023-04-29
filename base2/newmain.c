#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "funcs.h"

/*TODO
linha 52
INPUTS
CONDIÇÃO DE FIM
OUTPUT
*/

void main(){
    int programas[3][8] = {
        {0, 3, 9, 3, 3, 4, 0, 0 },
        {1, 0, 2, 4, 1, 2, 0, 0 },
        {3, 2, 9, 3, 3, 4, 0, 0 }
    };

    int tick = 0; // a instancia inicial que comeca em 0
    int qpr = sizeof(programas)/sizeof(programas[0]); //quantidade de programas
    int qp = (sizeof(programas)/qpr)/sizeof(int); //aqui temos a quantidade de processos
    int cpt1 = 1; //epa e ver onde foi posto e um glorificado counter
    int work = 0;
    int ir = 0;
    

    Queue running = CreateQueue(2); //so pode estar 1 programa a correr mas pomos o seguinte no ciclo final do programa a correr
    Queue blocked = CreateQueue(qp); //blocked podem estar muitos mas so sai quando o primeiro estiver a 0
    Queue ready = CreateQueue(qp);  //podem estar varios mas so saiem quando o running tiver vazio    
    Queue new = CreateQueue(qp); // pode haver varios processos a começar ao mesmo tempo

    while (tick < 20){ //add a condiçao de saida
        work = 0;
        printf("Tick: %d\n", tick);
        int cp = 0; //programa a começar em

        //for(int i = 0; i + cp <= qpr;i++){//loop de atualizar   
            int cpt = 1;
            //if(programas[i][0] < tick){ //ver se nao esta ainda no new e se é suppost correr ja

                //loop ready
                if(!IsEmptyQueue(ready)){
                    int i1 = (Front(ready) - 5);
                    while(programas[i1][cpt] == -1){
                        cpt++;                           //current process timer
                    }
                    ir = (Front(running)-5);
                    while(programas[ir][cpt1] == -1){
                        cpt1++;                           //current process timer
                    }
                    if( (cpt%2!= 0) && (programas[i1][cpt] > 0) && (IsEmptyQueue(running) || (programas[ir][cpt1] - tick == 0))){
                        programas[i1][cpt] = programas[i1][cpt] + tick;
                        Enqueue(Dequeue(ready),running);
                    }else if(programas[i1][cpt] <= 0 && cpt%2 != 0 ){
                        programas[i1][cpt] = -1;
                        programas[i1][cpt+1] = programas[i1][cpt+1] + tick;
                        Enqueue(Dequeue(ready), blocked);
                    }else if(cpt%2 == 0 || (programas[i1][cpt] >= 0 )){
                        programas[i1][cpt] = programas[i1][cpt] + tick;
                        Enqueue(Dequeue(ready), blocked);
                    }
                }

                if(!IsEmptyQueue(blocked)){
                    int i1 = (Front(blocked) - 5);
                    cpt = 1;
                    while(programas[i1][cpt] == -1){
                        cpt++;                           //current process timer
                    }
                    if(programas[i1][cpt] - tick <= 0){
                        programas[i1][cpt] = -1;
                        Enqueue(Dequeue(blocked),ready);
                    }
                }

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
            //}
        //}

        printf("Start new\n");
        //ciclo new, objetivos é fazer enqueue e depois por no ready ou no running
        for(int i = 0; i + cp < qpr;i++){
            if(  programas[i][0] == tick  ){
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

        printf("new :\n");
        printQueue(new);
        printf("ready: \n");
        printQueue(ready);
        printf("Running: \n");
        printQueue(running);
        printf("blocked: \n");
        printQueue(blocked);
        printf("\n");
        printf("---------------------------");
        tick++;
    }





}

