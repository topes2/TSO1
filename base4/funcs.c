#include <stdio.h>
#include "funcs.h"


int check_running(int i,int time,int tick,Queue running){
    int x = Front(running) - 5;
    return((x == i) && (tick - time == 0));
}


int check_blocked(int i,int time,int tick,Queue blocked){
    int x = Front(blocked) - 5;
    
}

int check_out(int time,int tick){
    return(time - tick == 0);
}

int check_ready(int i, int time, int tick, Queue ready){
    int x = Front(ready) - 5 == i;
    if(x == i){

    }
}

/*

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
                        programas[i][cpt] += tick; //add o tick atual ao tempo do running 
                        Enqueue(Dequeue(ready), running); //fazer enqueue para a running 
                    }else if( (programas[i][cpt] == 0) && (cpt % 2 != 0)){
                        //ou o tempo de running é 0 ou estamos a ver o tempo de blocked
                        programas[i][cpt] = -1;
                        programas[i][cpt+1] += tick;
                        Enqueue(Dequeue(ready), blocked);
                    }else if(cpt % 2 == 0 ){
                        programas[i][cpt] = -1;
                        programas[i][cpt] += tick;
                        Enqueue(Dequeue(ready), blocked);

                    }
                }
*/