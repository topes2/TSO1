#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Queue.h"

struct Unblocked {
    int tick;
    int unblock;
};

int main(){
    //Read content from file
    int nPrograms = 0, nProcesses = 0;
    char line[100];
    int n_programs = 0;

    FILE *f = fopen("programs.txt", "r");

    if(f == NULL){
        printf("Error opening file\n");
        return -2;
    }

    //ver quantos programas e processos existem
    //ler a primeira linha para saber o número de processos
    

    if(fgets(line, sizeof(line), f) == NULL){
        //arquivo não tem conteudo
        printf("No content in file\n");
        return 0;
    }
    nPrograms++;

    int pos = strcspn(line, "\n");
    line[pos] = '\0';
    
    for (int i = 0; i < strlen(line); i++){
        if(line[i] == ' '){
            nProcesses++;
        }
    }
    nProcesses++; //para o ultimo numero
    
    //ver o número de programas
    while(fgets(line, sizeof(line), f) != NULL){
        nPrograms++;
    }

    //voltar o ponteiro
    rewind(f);

    //criação da matriz
    int programas[nPrograms][nProcesses];

    //completar a matriz
    
    for(int i = 0; i < nPrograms; i++){
        for(int j = 0; j < nProcesses; j++){
            if(fscanf(f, "%d", &programas[i][j]) != 1){
                printf("error\n");
            }

        }
    }

    fclose(f);
    
    int tick = 0; // a instancia inicial que comeca em 0
    int cpt1 = 1; //variavel para teste do progroma atualmente a correr o running 
    int ir = 0; //indice do programam na queue do running 
    int nPExit = 0, exit = 1; //nPExit - numero de programas que ja sairam, exit - indica se um programa esta para sair
    int ends[nPrograms], end; //ends[] - array com os tempos de saida de todos os programas, end - variavel auxiliar para o calculo dos fins

    Queue running = CreateQueue(2); //A queue do running so pode ter 1 elemente mas caso seja preciso um outro programa começar a exeucao usamos um tamanho de 2 para
    //puder no teste do running fazer dequeue e nao termos um ciclo onde o running esta vazio
    Queue blocked = CreateQueue(nProcesses); //blocked podem estar muitos mas so sai quando o primeiro estiver a 0
    Queue ready = CreateQueue(nProcesses);  //podem estar varios mas so saiem quando o running tiver vazio    
    Queue new = CreateQueue(nProcesses); // pode haver varios processos a começar ao mesmo tempo

    Queue unBlock = CreateQueue(nPrograms);

    struct Unblocked unblock;     //Variavél que nos indica se existe unblock ou não
    unblock.unblock = 3; //começamos com 3 porque ao fazer -5 = -2
    
    //Ver quando os programas acabam
    for(int i = 0; i < nPrograms; i++){
        end = 0;
        for(int j = nProcesses - 1; j > 0; j--){
            if(programas[i][j] == 0){
                end++;
            } else {
                ends[i] = nProcesses - end;
            }
        }
    }

    printf("Instant |");
    for(int i = 0; i < nPrograms; i++){
        printf("  proc%d         |", i + 1);
    }
    printf("\n");

    int u = 0;

    while (nPExit < nPrograms){ //add a condiçao de 
        if(tick < 10){
            printf("0");
        }

        printf("%d      | ", tick);

        /*
            Parte do codigo para testar a queue ready
            começa com um teste para ver se a queue esta vazia ou nao, se nao tiver nao vai testar mais nenhuma condição
            Esta parte é responsavel pela enqueue para a queue do running e se for caso para a queue de block, no primeiro caso vai adicionar ao 
            tempo de execução o numero da instancia que entra na queue running, no caso do tempo de running for 0 vai igual essa tempo de 
            execução para -2 dado como corrido e faz enqueue para blocked
            Se for caso de ir para o block apenas adicona a instancia ao tempo de block para quando é suposto ser dequeue, se possivel.
            */
        int cpt = 1; 

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

        //Unblock
        if(unblock.unblock - 5 != -2 && hasValue(unblock.unblock, blocked) && tick == unblock.tick + 1){
            //retirar da queue blocked e adicionar à queue ready
            DequeueValue(unblock.unblock, blocked);
            Enqueue(unblock.unblock, ready);
            
            //indicar que já saimos
            int cpt = 1;
            while(programas[unblock.unblock - 5][cpt] == -2){
                cpt++;
            }
            programas[unblock.unblock - 5][cpt] = -2;
                u = 1;
        }

        int cp = 0; //programa a começar em
        cpt = 1; 
                
        if(!IsEmptyQueue(ready)){
            int i1 = (Front(ready) - 5);
            while(programas[i1][cpt] == -2){ //encontrar o cpt do programa de front do ready
                cpt++;                           //current process timer
            }
            
            if(!IsEmptyQueue(running)){ //ver se é possivel mandar brevemente o programa atual para o running
                ir = (Front(running)-5);
                while(programas[ir][cpt1] == -2){
                    cpt1++;                           //current process timer
                }
            }

            if(programas[i1][cpt] > 0 && (IsEmptyQueue(running) || (programas[ir][cpt1] - tick == 0))){
                programas[i1][cpt] = programas[i1][cpt] + tick;
                //Inserir programa no running
                Enqueue(Dequeue(ready), running);

                if(!hasValue(programas[i1][cpt + 1] + 4, ready)){
                //unblock
                    unblock.unblock = programas[i1][cpt + 1] + 4; //+4 porque o programa 1 corresponde ao 0 ou seja 5 - 1
                    unblock.tick = tick;
                } 

                programas[i1][cpt + 1] = -2;
            }else if(programas[i1][cpt] <= 0 && programas[i1][0] != -2){
                programas[i1][cpt] = -2;
                programas[i1][cpt+1] = programas[i1][cpt+1] + tick;
                Enqueue(Dequeue(ready), blocked);
            }
        }

            /*
            A parte do codigo responsavel para a verificação se a queue do block
            começa com um teste se a queue block esta vazia se não estiver procede a encontrar o indice 
            do programa que esta atualmente na front da queue e verifica a instancia que o prorama é suposto sair
            do estado blocked, se for caso que a instancia de saida é a instancia atual entao
            iguala o tempo de blocked a -2 para marcar como concluido e envia o seu indice para a queue ready
            */

            if(!IsEmptyQueue(running)){
                int i1 = (Front(running) - 5);
                cpt = 1;
                while(programas[i1][cpt] == -2 && cpt < nProcesses){
                    cpt++;                           //current process timer
                }

                //run
                if(programas[i1][cpt] - tick <= 0){
                    programas[i1][cpt] = -2;
                    programas[i1][cpt+2] = programas[i1][cpt+2] + tick;
                    Enqueue(Dequeue(running), blocked);
                }
            }
            
            /*
            A parte do codigo que testa a queue do running 
            começa com um teste da front da queue e utiliza a variavel i1 para guardar esse valor
            Testa a instancia de saida do indice e compara com o intancia atual e ve se tem de ser dequeued
            se for dequeued entao vai fazer enqueue do valor de i1 para o blocked
            */
            

            //ciclo new, objetivos é fazer enqueue e depois por no ready ou no running
            for(int i = 0; i + cp < nPrograms;i++){
                
                if((programas[i][0] == tick) && (programas[i][0] != -2)){
                    Enqueue((i + 5), new);
                }else if(programas[i][0] < tick && hasValue((i+5), new)) {
                    if(programas[i][1] > 0 && IsEmptyQueue(running)){
                        programas[i][1] = programas[i][1] + tick;
                        Enqueue(Dequeue(new), running); //entrar no running se estiver vazio e tiver tempo para la correr
                        //unblock
                        if(!hasValue(programas[i][cpt + 1] + 4, ready)){
                            unblock.unblock = programas[i][cpt + 1] + 4; //+4 porque o programa 1 corresponde ao 0 ou seja 5 - 1
                            unblock.tick = tick;  
                        } 

                        programas[i][cpt + 1] = -2;
                    }else {
                        Enqueue(Dequeue(new), ready); //se nao, entra no ready
                    }
                }
                
            }
            /*
            Corre a input de programa para testar se um programa e supposto comecar a sua execução
            se o running estiver vazio e o ready tambem entao vai entrar diretamente na queue de running
            se a queue running nao estiver vazia entao faz enqueue para o ready.            
            */

           //Exit
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
                    nPExit++;
                } 
                exit = 1;
            }else{
                printf("               | ");
            }
        }

        /*
        Vamos percorrer a lista dos programas todos e vamos verificar se esta na altura de sair. Se todos os processos estiverem
        a -2 significa que o programa esta pronto a sair, vai indicar no terminal que o programa vai sair e vamos colocar o primeiro indice a -2
        para indicar que o programa ja terminou. Se um programa ja tiver terminado vamos imprimir espacos.
        */
        
        for (int i = 0; i < nPrograms; i++) {
            if (hasValue(i + 5, new) && programas[i][0] != -2) {
                printf("NEW            | ");
            } else if (hasValue(i + 5, running) && programas[i][0] != -2) {
                printf("RUN            | ");
            } else if (unblock.unblock == i + 5 && unblock.tick + 1 == tick && u){
                printf("READY (UNBLOCK)| ");
                unblock.unblock = 3;
                unblock.tick = 0;
                u = 0;
            } else if (hasValue(i + 5, ready) && programas[i][0] != -2) {
                printf("READY          | ");
            } else if (hasValue(i + 5, blocked) && programas[i][0] != -2) {
                printf("BLOCKED        | ");
            } else if(programas[i][0] != -2){
                printf("               | ");
            }                                     
        } 
        printf("\n");

        /*
        Esta parte e o print de todos os estados, vamos estar a verificar se o programa esta em certa fila e se estiver vamos indicar no terminal
        onde o programa se encontra.
        */
        tick++; //mudar o tick
    }
    
    

    return 0;
}