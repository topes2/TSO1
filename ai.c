#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "funcs.h"

int main() {
    int programas[3][8] = {
        {0, 3, 9, 3, 3, 4, 0, 0 },
        {1, 0, 2, 4, 1, 2, 0, 0 },
        {3, 2, 9, 3, 3, 4, 0, 0 }
    };

    int tick = -1;
    int qpr = sizeof(programas) / sizeof(programas[0]);
    int qp = (sizeof(programas) / qpr) / sizeof(int);

    Queue running = CreateQueue(2);
    Queue blocked = CreateQueue(qp);
    Queue ready = CreateQueue(qp);
    Queue new = CreateQueue(qp);

    while (tick < 10) {
        tick++;
        printf("start while loop \n");
        printf("%d tick \n", tick);

        for (int p1 = 0; p1 < qpr; p1++) {
            if (programas[p1][0] == tick) {
                Enqueue(p1 + 5, new);
            }
        }

        for (int i = 0; i < qpr; i++) {
            int i_prog = i + 5;

            if (programas[i][0] < tick) {
                int cpt = 1;
                while (programas[i][cpt] == -1) {
                    cpt++;
                }

                if (Front(new) == i_prog) {
                    if (IsEmptyQueue(running) && IsEmptyQueue(ready) && (programas[i][1] != 0)) {
                        programas[i][cpt] = programas[i][cpt] + tick;
                        Enqueue(Dequeue(new), running);
                    } else {
                        Enqueue(Dequeue(new), ready);
                    }
                }

                if (Front(ready) == i_prog) {
                    if (IsEmptyQueue(running) && programas[i][cpt] > 0 && cpt % 2 != 0) {
                        programas[i][cpt] += tick;
                        Enqueue(Dequeue(ready), running);
                    } else if (programas[i][cpt] == 0 && cpt % 2 != 0) {
                        programas[i][cpt] = -1;
                        programas[i][cpt + 1] += tick;
                        Enqueue(Dequeue(ready), blocked);
                    } else if (cpt % 2 == 0) {
                        programas[i][cpt] += tick;
                        Enqueue(Dequeue(ready), blocked);
                    }
                }

                if (Front(blocked) == i_prog) {
                    if (programas[i][cpt] - tick == 0) {
programas[i][cpt] = -1;
Enqueue(Dequeue(blocked), ready);
}
}
if (Front(running) == i_prog) {
                if (programas[i][cpt] - tick == 0) {
                    programas[i][cpt] = -1;
                    programas[i][cpt + 1] += tick;
                    Enqueue(Dequeue(running), blocked);
                }
            }
        }
    }

    printf("New \n");
    printQueue(new);
    printf("Running \n");
    printQueue(running);
    printf("Ready \n");
    printQueue(ready);
    printf("Blocked \n");
    printQueue(blocked);
    printf("\n");
    printf("----------------------------------------");
}

return 0;
}