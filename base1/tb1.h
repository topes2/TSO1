#include <stdbool.h>

#define true 1
#define false 0



typedef struct ptime
{
    int type; // 0 é running e 1 é blocked
    int time;
} ptime;

typedef struct program{
    int sz;
    ptime pl[];
}program;





//typedef struct programe   wtf esta a dar erro com comentario?
//{
//    int *Ar;
//    int *Ab;
//} programe;//pid =!= PiD




//pid = o processo
//PiD = id do program pertence

//void importFile(char fileName[20], *mat);

int check(int p[],int sz);
int getsize(int p[]);