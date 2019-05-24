//
//  LireFichier.h
//  Simulation
//
//  Created by jean-charles SOTTAS on 23/05/2019.
//  Copyright © 2019 jean-charles SOTTAS. All rights reserved.
//

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
