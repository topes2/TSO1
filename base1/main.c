#include "tb1.h"
#include <stdio.h>

int main()
{
    struct program p1;
    struct program p2;
    struct program p3;
    p1.size = p2.size = p3.size = 8;
    int np[8] = {5, 8, 6, 4, 7, 5, 9, 10};
    int np1[8] = {5, 8, 6, 4, 7, 5, 9, 10};
    int np2[8] = {5, 8, 6, 4, 7, 5, 9, 10};
    p1 = setup(p1, np);
    p2 = setup(p2, np1);
    p3 = setup(p3, np2);
    // pp(p1);
    printf("\n\n\n");

    
    return 0;
}