#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Queue.h"
#include "funcs.h"

//files

/*
Esta função obtem quantos programas e quantos processos existem no ficheiro para processar.
*/
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

/*
Esta função vai voltar a abrir o ficheiro e copiar o conteudo para a matriz dada como argumento. Faz return 1 se copiou tudo com sucesso.
*/
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
                exit(-1);
            }

        }
    }

    fclose(f);

    return 1;
}

//states
//Blocked
/*
Este estado começa por verificar se a queue está vazia. Caso não esteja vamos obter o programa que está na frente da queue e verifica
se o programa é suposto sair no instante ou se já devia ter saido, e se for o caso retira o programa da queue blocked e adiciona-o á queue ready.
*/
void blockedState(Queue ready, Queue blocked, int **programas, int tick){
    int cpt;

    if(!IsEmptyQueue(blocked)){
        int i1 = (Front(blocked) - 5);
        cpt = 1;

        while(programas[i1][cpt] == -2){
            cpt++;                           //current process timer
        }

        if(programas[i1][cpt] - tick <= 0){
            programas[i1][cpt] = -2;
            Enqueue(Dequeue(blocked), ready);
        }
    }

    return;
}

//unBlock
/*
O estado unblock é responsável por retirar um programa do estado blocked e transferi-lo para o estado ready. Começamos por verificar se o valor de
unblock -5 (por causa da adição para que não haja confusões com os valores iniciais das queues) é != -2, que significa que existe um programa para fazer unblock
e se esse programa está na queue blocked. Se isso acontecer retiramos da queue blocked, transferimos o programa para a queue ready e indicamos que o blocked
foi completado.
*/
void unblockState(Queue ready,Queue blocked, int **programas, int unblock, int *unOcurred){
    if(unblock - 5 != -2 && hasValue(unblock, blocked)){

        //retirar da queue blocked e adicionar à queue ready
        dequeueValue(unblock, blocked);
        Enqueue(unblock, ready);
            
        //indicar que já saimos
        int cpt = 1;
        while(programas[unblock - 5][cpt] == -2){
            cpt++;
        }
        programas[unblock - 5][cpt] = -2;
        *unOcurred = 1;
    }
}

//ready
/*
O estado ready é responsável por conter os próximos programas a executar por ordem de chegada. Este estado começa por verificar se existe algo
na fila ready e caso exista 
*/
void readyState(Queue ready, Queue running, Queue blocked, int **programas, int *unblock, int tick, int *cpt1, int *ir) {
    int cpt = 1;

    if (!IsEmptyQueue(ready)) {
        int i1 = (Front(ready) - 5);
        while (programas[i1][cpt] == -2) { // encontrar o cpt do programa de front do ready
            cpt++; // current process timer
        }

        if (!IsEmptyQueue(running)) { // verificar se é possível mandar brevemente o programa atual para o running
            *ir = (Front(running) - 5);
            while (programas[*ir][*cpt1] == -2) {
                *cpt1 += 1; // current process timer
            }
        }

        if (programas[i1][cpt] > 0 && (IsEmptyQueue(running) || (programas[*ir][*cpt1] - tick == 0))) {
            programas[i1][cpt] = programas[i1][cpt] + tick;
            // Inserir programa no running
            Enqueue(Dequeue(ready), running);

            if (!hasValue(programas[i1][cpt + 1] + 4, ready)) {
                // Unblock
                *unblock = programas[i1][cpt + 1] + 4; // +4 porque o programa 1 corresponde ao 0, ou seja, 5 - 1
            }

            programas[i1][cpt + 1] = -2;
        } else if (programas[i1][cpt] <= 0 && programas[i1][0] != -2) {
            programas[i1][cpt] = -2;
            programas[i1][cpt + 1] = programas[i1][cpt + 1] + tick;
            Enqueue(Dequeue(ready), blocked);
        }
    }
}

//running
/*
O estado running é responsável por conter o programa que está a ser processado no instante dado. Decidimos utilizar uma queue de tamanho 2
já que facilitaria ao transferir programas do estado ready para o running, visto que primeiro processamos o estado ready e depois o estado running.
*/
void runningState(Queue running, Queue blocked, int **programas, int nProcesses, int tick){
    int cpt; //current process timer
    if(!IsEmptyQueue(running)){
        int i1 = (Front(running) - 5);
        cpt = 1;
        while(programas[i1][cpt] == -2 && cpt < nProcesses){
            cpt++;
        }

        //run
        if(programas[i1][cpt] - tick <= 0){
            programas[i1][cpt] = -2;
            programas[i1][cpt+2] = programas[i1][cpt+2] + tick;
            Enqueue(Dequeue(running), blocked);
        }
    }
}        

//new
/*
O estado new é responsável por criar um novo programa para ser processado. Este estado percorre a matriz com todos os programas e verifica
a primeira posição de cada array, comparando com o tick para verificar se o programa é suposto iniciar naquele instante. Se um programa for
suposto iniciar será verificado se a queue running está vazia e caso esteja o programa será logo transferido para ai, assim pulando a queue ready,
caso contrário o programa será colocado na queue ready e terá de esperar pela sua vez.
*/
void newState(Queue new, Queue running, Queue ready, int **programas, int tick, int *unblock, int nPrograms){
    int cpt = 1;
    
    //ciclo new, objetivos é fazer enqueue e depois por no ready ou no running
    for(int i = 0; i < nPrograms; i++){
                
        if((programas[i][0] == tick) && (programas[i][0] != -2)){
            Enqueue((i + 5), new);
        }else if(programas[i][0] < tick && hasValue((i+5), new)) {
            if(programas[i][1] > 0 && IsEmptyQueue(running)){
                programas[i][1] = programas[i][1] + tick;
                Enqueue(Dequeue(new), running); //entrar no running se estiver vazio e tiver tempo para la correr
                //unblock
                if(!hasValue(programas[i][cpt + 1] + 4, ready)){
                    *unblock = programas[i][cpt + 1] + 4; //+4 porque o programa 1 corresponde ao 0 ou seja 5 - 1
                } 

                programas[i][cpt + 1] = -2;
            }else {
                Enqueue(Dequeue(new), ready); //se nao, entra no ready
            }
        }
                
    }
}

//Exit
/*
O estado exit é responsável por indicar que um programa terminou a sua execução. Este estado vai percorrer a matriz toda e verifica se
todos os processos estão com o valor -2, o que indica que já foi tudo concluido e que o programa pode terminar. Se o programa sair da execução 
é impresso a mensagem "EXIT           | " no terminal.
*/
void exitState(int **programas,int *ends, int nPrograms, int *nPExit){
    int exit = 1;
    for(int i = 0; i < nPrograms; i++){
        if(programas[i][0] != -2){
            for(int j = 1; j < ends[i]; j++){
                if(programas[i][j] != -2){
                    exit = 0;
                }
            }
            
            if(exit){
                programas[i][0] = -2;
                printf("EXIT           | ");
                *nPExit += 1;
            } 
            exit = 1;
        }else{
            printf("               | ");
        }
    }
}

//other
/*
Esta função verifica quando os programas devem terminar. Ao achar o número 0 indica que um programa terminou, vai guardar o indice em que o programa 
termina no array ends
*/
void endPrograms(int *ends, int **programs, int nPrograms, int nProcesses){
    int end;

    for (int i = 0; i < nPrograms; i++) {
        end = 0;
        for (int j = nProcesses - 1; j >= 0; j--) {
            if (programs[i][j] == 0) {
                end++;
            } else {
                ends[i] = nProcesses - end;
                break; // sai do loop interno, pois já encontrou o fim do programa
            }
        }
    }
}

//Prints
/*
Esta função é responsável por realizar as impressões dos estatos todos, menos o exit. Vai percurrer todas as queues ou verificar se ocorreu um unblock
e indicar no terminal em que estado o programa está. 
*/
void printStates(Queue new, Queue running, Queue ready, Queue blocked, int **programas, int nPrograms, int *unblock, int *unOcurred){
    for (int i = 0; i < nPrograms; i++) {
        if (hasValue(i + 5, new) && programas[i][0] != -2) {
            printf("NEW            | ");
        } else if (hasValue(i + 5, running) && programas[i][0] != -2) {
            printf("RUN            | ");
        } else if (*unblock == i + 5  && *unOcurred){
            printf("READY (UNBLOCK)| ");
            *unblock = 3; //reset
            *unOcurred = 0;
        } else if (hasValue(i + 5, ready) && programas[i][0] != -2) {
            printf("READY          | ");
        } else if (hasValue(i + 5, blocked) && programas[i][0] != -2) {
            printf("BLOCKED        | ");
        } else if(programas[i][0] != -2){
            printf("               | ");
        }                                     
    } 
    printf("\n");
}