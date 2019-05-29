
#ifndef LireFichier_h
#define LireFichier_h

#include <stdio.h>
typedef struct LAMBDA{
    int* tab;
    int size;
}LAMBDA;

LAMBDA lirefichier(char* file);
void freeL(LAMBDA L);
#endif /* LireFichier_h */
