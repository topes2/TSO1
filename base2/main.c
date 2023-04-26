#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
//TODO
/*
tudo o que esta o new tem de ir para o ready
INPUTS
CONDIÇÃO DE FIM
OUTPUT
*/

void main(){
    int programas[3][8] = { 
    {0, 6, 9, 3, 3, 4, 0, 0 },    //0
    {2, 7, 0, 4, 1, 2, 0, 0 },    //1
    {3, 1, 1, 5, 1, 1, 0, 0 }};   //2

    //estados = NEW --> READY --> RUNNING -->programas[p1][0] == tickBLOCKED -->EXIT
    int tick = 0; // a instancia inicial que comeca em 0
    int qpr = sizeof(programas)/sizeof(programas[0]); //quantidade de programas
    int qp = (sizeof(programas)/qpr)/sizeof(int); //aqui temos a quantidade de processos
    int cp = 0; // programa que esta a ser importado para dentro de queues
    int cpt1 = 1; //epa e ver onde foi posto e um glorificado counter
    

    Queue running = CreateQueue(2); //so pode estar 1 programa a correr mas pomos o seguinte no ciclo final do programa a correr
    Queue blocked = CreateQueue(qp); //blocked podem estar muitos mas so sai quando o primeiro estiver a 0
    Queue ready = CreateQueue(qp);  //podem estar varios mas so saiem quando o running tiver vazio    
    Queue new = CreateQueue(qp); // pode haver varios processos a começar ao mesmo tempo


    //debug remove later
    printf("%d row \n",qp);
    printf("%d colum \n",qpr);
    //

    while(1){ 
        for(int p1 = 0;p1 <= qp;p1++){ //verificar se o programa é suposto começar neste tick
            if(programas[p1][0] == tick){ //se sim entao vai para new
                Enqueue(p1,new);
                continue;
            }else if(programas[p1][0] < tick) //se nao é ignorado e o ciclo while continua
                continue;            
        }

        for(int i = 0;i <= qp;i++){ //encontrar o tempo de processo que esta a ser testado, ignorando o primeiro (primeira instancia e os a -1)
            int cpt = 1;
            while(programas[i][cpt] == -1){
                cpt++;                 //current process timer
            }
            printf("%d  \n",Front(running));
            printf("%d  \n",Front(blocked));
            printf("%d  \n",Front(ready));
            printf("%d  \n",Front(new));

            if(Front(new) == i){//tudo o que esta o new tem de ir para o ready
                if(programas[i][0] == tick)
                    continue;    
                }else if(IsEmptyQueue(running) && IsEmptyQueue(ready) && (programas[i][1] =! 0)){
                        programas[i][cpt] += tick; //adding the tick so that we can subtract it 
                        Enqueue(Dequeue(new),running);
                    }else if(!(IsEmptyQueue(running))){
                        Enqueue(Dequeue(new),ready);
                    }
            
            if(Front(running) == i){
                if(programas[i][cpt] - tick > 0){
                    continue;
                }else if(programas[i][cpt] - tick <= 0){
                    programas[i][cpt] = -1;
                    programas[i][cpt+1] += tick;
                    Enqueue(Dequeue(running),blocked);
                    continue;
                }
            }

            if (Front(ready) == i){
                int cpt1 = 1;
                for(int i = 0;i <= qp;i++){//encontrar e saber se é para mudar o programa actualmente a run
                    while(programas[Front(running)][cpt1] == -1){
                        cpt1++;                
                    }
                    if(programas[Front(running)][cpt1] - tick <= 0 && (programas[i][cpt+1] =! 0)){
                        programas[i][cpt] += tick;
                        Enqueue(Dequeue(ready),running);
                        continue;
                    }else if(programas[i][cpt+1] == 0){
                        Enqueue(Dequeue(ready),blocked);
                        continue;
                    }
                }
            }
            
            if(Front(blocked) == i){
                if(programas[i][cpt] - tick <= 0){
                    Enqueue(Dequeue(blocked),ready);
                    continue;
                } 
            }           
        }//for(programas)
        tick++;        
    }//while   
}//main