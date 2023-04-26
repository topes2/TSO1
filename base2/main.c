#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "func.h"

void main(){
    int programas[3][8] = { 
    {0, 6, 9, 3, 3, 4, 0, 0 },
    {1, 7, 2, 4, 1, 2, 0, 0 },
    {2, 1, 1, 5, 1, 1, 0, 0 }};

    //estados = NEW --> READY --> RUNNING --> BLOCKED -->EXIT
    int tick = 0; // a instancia inicial que comeca em 0
    int qpr = sizeof(programas)/sizeof(programas[0]);
    int qp = (sizeof(programas)/qpr)/sizeof(int); //aqui temos a quantidade de processos
    int cp = 0; // programa que esta a ser importado para dentro de queues
    

    Queue running = CreateQueue(1); //mais vale criar logo todo e apagar se nao for preciso 
    Queue blocked = CreateQueue(qp);
    Queue ready = CreateQueue(qp);    
    Queue new = CreateQueue(1);

    printf("%d row \n",qp);
    printf("%d colum \n",qpr);


    while(1){        
            if(!(IsFullQueue(new)) && (cp<=qpr)){
                Enqueue(cp,new);
                cp++;
            }

            if(!(IsEmptyQueue(ready)) && (IsEmptyQueue(running)) && programas[Front(ready)] ){ 
                Enqueue(Front(ready),running);
                Dequeue(ready);
                }else if(!(IsEmptyQueue(running))){

                }
        



        tick++;
        
    }


    
}

/*
if(IsFullQueue(running)){
    enqueue(dequeue(ready), blocked);
}else{
    enqueue(dequeue(ready), runnung);
}
*/