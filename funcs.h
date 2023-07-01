//files
void getsizesFile(char *filename, int *numPrograms, int *numProcesses);
int completeMat(char *filename, int **programs, int *numPrograms, int *numProcesses);

//states
void blockedState(Queue ready, Queue blocked, int **programas, int tick);
void unblockState(Queue ready,Queue blocked, int **programas, int unblock, int *unOcurred);
void readyState(Queue ready, Queue running, Queue blocked, int **programas, int *unblock, int tick, int *cpt1, int *ir);
void runningState(Queue running, Queue blocked, int **programas, int nProcesses, int tick);
void newState(Queue new, Queue running, Queue ready, int **programas, int tick, int *unblock, int nPrograms);
void exitState(int **programas,int *ends, int nPrograms, int *nPExit);

//other
void endPrograms(int *ends, int **programs, int nPrograms, int nProcesses);
void printStates(Queue new, Queue running, Queue ready, Queue blocked, int **programas, int nPrograms, int *unblock, int *unOcurred);