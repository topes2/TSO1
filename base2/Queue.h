struct QueueRecord; 
typedef struct QueueRecord *Queue;

Queue CreateQueue( int MaxElements );
void DisposeQueue( Queue Q );

int IsEmptyQueue(Queue Q);
int IsFullQueue( Queue Q );
void MakeEmptyQueue( Queue Q );

int Front( Queue Q );
void Enqueue( int X, Queue Q );
int Dequeue( Queue Q );
