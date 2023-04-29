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

/*
void main(){
    int programas[3][8] = {
        {0, 3, 9, 3, 3, 4, 0, 0 },
        {1, 0, 2, 4, 1, 2, 0, 0 },
        {3, 2, 9, 3, 3, 4, 0, 0 }
    };
    
    //estados = NEW --> READY --> RUNNING -->programas[p1][0] == tickBLOCKED -->EXIT
    int tick = 0; // a instancia inicial que comeca em 0
    int qpr = sizeof(programas)/sizeof(programas[0]); //quantidade de programas
    int qp = (sizeof(programas)/qpr)/sizeof(int); //aqui temos a quantidade de processos
    int cp = 0; // algo para parar tbh just help me ;-;
    int cpt1 = 1; //epa e ver onde foi posto e um glorificado counter
    

    Queue running = CreateQueue(2); //so pode estar 1 programa a correr mas pomos o seguinte no ciclo final do programa a correr
    Queue blocked = CreateQueue(qp); //blocked podem estar muitos mas so sai quando o primeiro estiver a 0
    Queue ready = CreateQueue(qp);  //podem estar varios mas so saiem quando o running tiver vazio    
    Queue new = CreateQueue(qp); // pode haver varios processos a começar ao mesmo tempo
    
    printf("\033[31mInstant |\033[0m");   
    for(int i = 0; i < qpr; i++){
        printf("  proc%d  |", i + 1);
    }
    printf("\n");
    
    

    while(tick < 10){
        printf("%d       | ", tick);
        

        for(int p1 = 0; p1 < qpr; p1++){ //verificar se o programa é suposto começar neste tick
            if(programas[p1][0] == tick){ //se sim entao vai para new
                Enqueue(p1 + 5, new); //New
            }
        }


            for(int i0 = 0; i0 < qpr; i0++){ //encontrar o tempo de processo que esta a ser testado, ignorando o primeiro (primeira instancia e os a -1)
                int i = i0; //O i e otimizado para o void

                if(programas[i][0] < tick){

                    int cpt = 1; //add check para ver se acabou de entrar algo como comparar tick de entrada com o tick atual
                    while(programas[i][cpt] == -1){
                        cpt++;                 //current process timer
                    }
                    
                    int cptt = cpt; //optimizado para o void

                
                if(Front(running) - 5 == i){
                    if(programas[i][cpt] - tick == 0){
                        programas[i][cpt] = -1;
                        programas[i][cpt+1] += tick;
                        Enqueue(Dequeue(running), blocked);
                    }
                }
                           
                if(Front(blocked) - 5 == i){
                    if(programas[i][cpt] - tick == 0){
                        programas[i][cpt] = -1;
                        Enqueue(Dequeue(blocked), ready);
                    } 
                }

                if (Front(ready) - 5 == i){
                    int cpt1 = 1;
                    while(programas[Front(running) - 5][cpt1] == -1){ //encontrar o cpt do programa a correr no running
                            cpt1++;
                    } 
                    if( ((programas[Front(running) - 5][cpt1] - tick == 0) || IsEmptyQueue(running)) && (programas[i][cpt] > 0) && (cpt % 2 != 0)){ 
                        //ver se o current running é para sair ou nao ou se o running esta vazio e o tempo de correr no running é maior que 0 e que é o tempo de running que estamos a ver
                        programas[i][cpt] += tick; //add o tick atual ao tempo do running 
                        Enqueue(Dequeue(ready), running); //fazer enqueue para a running 
                    }else if( (programas[i][cpt] == 0) && (cpt % 2 != 0)){
                        //ou o tempo de running é 0 ou estamos a ver o tempo de blocked
                        programas[i][cpt] = -1;
                        programas[i][cpt+1] += tick;
                        Enqueue(Dequeue(ready), blocked);
                    }else if(cpt % 2 == 0){
                        programas[i][cpt] += tick;
                        Enqueue(Dequeue(ready), blocked);

                    }
                }

                if(Front(new) - 5 == i){//tudo o que esta o new tem de ir para o ready                  
                    if(IsEmptyQueue(running) && IsEmptyQueue(ready) && (programas[i][1] != 0)){
                        programas[i][cpt] = programas[i][cpt] + tick; //adding the tick so that we can subtract it   
                        Enqueue(Dequeue(new),running);
                       
                    }else 
                        Enqueue(Dequeue(new), ready);
                }



                }
            }//for(programas)
        for (int i = 0; i < qpr; i++) {
            if (hasValue(i + 5, new)) {
                printf("NEW     | ");
            } else if (hasValue(i + 5, running)) {
                printf("RUNNING | ");
            } else if (hasValue(i + 5, ready)) {
                printf("READY   | ");
            } else if (hasValue(i + 5, blocked)) {
                printf("BLOCKED | ");
            } else {
                printf("        | ");
            }
                                                           
        } 
        printf("\n"); 
        tick++; 
    }//while   
}//main
*/

int main(){
    Queue Q = CreateQueue(3);

    Enqueue(1, Q);
    Enqueue(5, Q);
    Enqueue(2, Q);

    printQueue(Q);

    Dequeue(Q);

    printQueue(Q);

    Enqueue(10, Q);

    printQueue(Q);

    printf("%d\n", hasValue(10, Q));
    return 0;
}