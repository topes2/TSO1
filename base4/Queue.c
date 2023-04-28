#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Queue.h"

#define MinQueueSize (2)

#define True 1
#define False 0
struct QueueRecord
{
    int Capacity;
    int size;
    int Front;
    int Rear;
    int *Array;
};

/* FUNCOES AUXILIARES */
/* numero de elementos na fila */
int size(Queue Q)
{
    return (Q->Capacity - Q->Front + Q->Rear) % Q->Capacity;
}

/* indice do proximo elemento  */
int successor(int i, Queue Q)
{
    return (i + 1) % Q->Capacity;
}

/* FUNCOES DE MANIPULACAO DE QUEUES */
Queue CreateQueue(int MaxElements)
{
    Queue Q;
    
    if (MaxElements < MinQueueSize){
        printf("Queue size is too small");
        exit(-1);
    }

    Q = malloc(sizeof(struct QueueRecord));
    if (Q == NULL){
        printf("Out of space!");
        exit(-1);
    }

    Q->Array = malloc(sizeof(int) * MaxElements);
    if (Q->Array == NULL){
        printf("Out of space!");
        exit(-1);
    }

    Q->size = 0;
    Q->Capacity = MaxElements + 1;
    MakeEmptyQueue(Q);

    return Q;
}

int NextX(Queue Q,int n){ //adicionei esta funçao para saber quais programas correr
    if(IsEmptyQueue(Q)){
        return -1;
    } else {
        return (Q->Array[Q->Front]+ n);
    }
}

void DisposeQueue(Queue Q)
{
    if (Q != NULL)
    {
        free(Q->Array);
        free(Q);
    }
}

int IsEmptyQueue(Queue Q)
{
    return Q->size == 0;
    
}

int IsFullQueue(Queue Q)
{
    if(Q->Capacity - 1 == Q->Rear){
        return 1;
    } else {
        return 0;
    }

    (Q->Front == Q->Rear);
}

void MakeEmptyQueue(Queue Q)
{
    Q->Front = Q->Rear = NULL; //talvez mudar !!!!!!!!!!!!!!!!
}

void Enqueue(int X, Queue Q)
{
    if (size(Q) == Q->Capacity -1){
        printf("Overflow\n");
        exit(-1);
    }

    Q->size++;
    Q->Array[Q->Rear] = X;
    Q->Rear = successor(Q->Rear, Q);
}

int Front(Queue Q)
{
    if(IsEmptyQueue(Q)){
        printf("The queue is Empty\n");
        return 0;
    } else {
        return Q->Array[Q->Front];
    }
}

int Dequeue(Queue Q)
{
    int X;

    if(IsEmptyQueue(Q)){
        printf("Empty Queue\n");
        exit(-1);
    }

    Q->size--;
    X = Q->Array[Q->Front];
    Q->Front = successor(Q->Front, Q);

    return X;
}

void printQueue(Queue Q){ 
    for(int i = Q->Front; i < Q->size; i++){
        printf("%d ", Q->Array[i] - 5);
    }
        
    printf("\n");
}


int hasValue(int v, Queue Q){
    //Vamos percorrer o array inteiro da queue e se encontrarmos o id do programa fazemos return true
    for(int i = 0; i < Q->size; i++){ 
        if(Q->Array[i] == v){
            return 1;
        }
    }
    return 0;
}
