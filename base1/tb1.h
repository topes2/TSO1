typedef struct process{
    int state;
    int time; 
}process;

typedef struct program{
    process plist[8];
    int size;
}program;

//Debug
void printp(program p);

//Final
program setup(program p1, int n[8]);

void pp(program p);

char ps(int i);