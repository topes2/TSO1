#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

/*TODO
tudo o que esta o new tem de ir para o ready
INPUTS
CONDIÇÃO DE FIM
OUTPUT
*/

/*Problemas
o loop esta a correr sempre para tentar por no ready
and legit nao é suposto fazer lo :(


*/

void main(){
    int programas[2][8] = { 
    {0, 6, 9, 3, 3, 4, 0, 0 },
    {1, 7, 2, 4, 1, 2, 0, 0 } };   //0

    //estados = NEW --> READY --> RUNNING -->programas[p1][0] == tickBLOCKED -->EXIT
    int tick = -1; // a instancia inicial que comeca em 0
    int qpr = sizeof(programas)/sizeof(programas[0]); //quantidade de programas
    int qp = (sizeof(programas)/qpr)/sizeof(int); //aqui temos a quantidade de processos
    int cp = 0; // algo para parar tbh just help me ;-;
    int cpt1 = 1; //epa e ver onde foi posto e um glorificado counter
    

    Queue running = CreateQueue(2); //so pode estar 1 programa a correr mas pomos o seguinte no ciclo final do programa a correr
    Queue blocked = CreateQueue(qp); //blocked podem estar muitos mas so sai quando o primeiro estiver a 0
    Queue ready = CreateQueue(qp);  //podem estar varios mas so saiem quando o running tiver vazio    
    Queue new = CreateQueue(qp); // pode haver varios processos a começar ao mesmo tempo



    while(tick < 5){
        tick++; 
        printf("start while loop \n"); 
        printf("%d tick \n",tick);

        for(int p1 = 0;p1 <= qpr-1;p1++){ //verificar se o programa é suposto começar neste tick
            if(programas[p1][0] == tick){ //se sim entao vai para new
                Enqueue(p1,new);
                printf("enqueued a program into new\n");
            }
        }
    
            for(int i = 0;i <= qpr-1;i++){ //encontrar o tempo de processo que esta a ser testado, ignorando o primeiro (primeira instancia e os a -1)
                int cpt = 1;
                while(programas[i][cpt] == -1){
                    cpt++;                 //current process timer
                }
                printf("started the for loop program n %d \n",i);
                
                
                if((Front(new) == i) && (programas[i][0] =! tick)){//tudo o que esta o new tem de ir para o ready
                    printf("trying to take from new to put to ready\n");
                    if(programas[i][0] == tick)
                        break;    
                    }else if(IsEmptyQueue(running) && IsEmptyQueue(ready) && (programas[i][1] =! 0)){
                            programas[i][cpt] += tick; //adding the tick so that we can subtract it 
                            Enqueue(Dequeue(new),running);
                        }else if(!(IsEmptyQueue(running))){
                            Enqueue(Dequeue(new),ready);
                        }

                if(0){
                
                if(Front(running) == i){
                    printf("running \n");
                    if(programas[i][cpt] - tick > 0){
                        break;
                    }else if(programas[i][cpt] - tick <= 0){
                        programas[i][cpt] = -1;
                        programas[i][cpt+1] += tick;
                        Enqueue(Dequeue(running),blocked);
                        break;
                    }
                }

                if (Front(ready) == i){
                    printf("ready \n");
                    int cpt1 = 1;
                    for(int i = 0;i <= qp-1;i++){//encontrar e saber se é para mudar o programa actualmente a run
                        while(programas[Front(running)][cpt1] == -1){
                            cpt1++;                
                        }
                        if(programas[Front(running)][cpt1] - tick <= 0 && (programas[i][cpt+1] =! 0)){
                            programas[i][cpt] += tick;
                            Enqueue(Dequeue(ready),running);
                            break;
                        }else if(programas[i][cpt+1] == 0){
                            Enqueue(Dequeue(ready),blocked);
                            break;
                        }
                    }
                }
                
                if(Front(blocked) == i){
                    printf("blocked\n");
                    if(programas[i][cpt] - tick <= 0){
                        Enqueue(Dequeue(blocked),ready);
                        break;
                    } 
                }   
                }//debug
            }//for(programas)
            
    
        printf("\n");   
    }//while   
}//main