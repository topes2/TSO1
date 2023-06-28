struct QueueRecord; 
typedef struct QueueRecord *Queue;

Queue CreateQueue( int MaxElements );
void DisposeQueue( Queue Q );

int IsEmptyQueue(Queue Q);
int IsFullQueue( Queue Q );
void MakeEmptyQueue( Queue Q );

int Front( Queue Q );
int NextX(Queue Q,int n);
void Enqueue( int X, Queue Q );
int Dequeue( Queue Q );

int DequeueValue(int v, Queue Q);

//others
void printQueue(Queue Q);
int hasValue(int v, Queue Q);