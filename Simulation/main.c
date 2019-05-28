//
//  main.c
//  Simulation
//
//  Created by jean-charles SOTTAS on 22/03/2019.
//  Copyright © 2019 jean-charles SOTTAS. All rights reserved.
//
#include <stdio.h>
#include "LireFichier.h"
#include "MM10.h"
#include "MM1.h"
#include "MM10min.h"
int main(int argc, const char * argv[]) {
    LAMBDA L;
    L = lirefichier("/Users/larcher/Desktop/Simulation/Simulation/Lambda.txt");
    int i = 0;
    for (i = 0; i < L.size; i++) {
        printf("%d \n",L.tab[i]);
    }
    printf("======== MM10 ========\n");
//    Question 1
    FILE* F1 = fopen("/Users/larcher/Desktop/Simulation/Simulation/Temps1.txt", "w+");
    for (i = 0; i<L.size; i++) {
        //printf("%d \n",L.tab[i]);
        simulationMM10(F1,L.tab[i]);
    }
    fclose(F1);
     printf("======== NMM1 ========\n");
//    Question 2
    FILE* F2 = fopen("/Users/larcher/Desktop/Simulation/Simulation/Temps2.txt", "w+");
    for (i = 0; i<L.size; i++) {
//        printf("%d \n",L.tab[i]);
//        simulationMM1(F2,L.tab[i]);
    }
    fclose(F2);
     printf("======= MM10min =======\n");
//    Question 3
    FILE* F3 = fopen("/Users/larcher/Desktop/Simulation/Simulation/Temps3.txt", "w+");
    for (i = 0; i<L.size; i++) {
//        simulationMM10min(F3,L.tab[i]);
    }
    fclose(F3);
    freeL(L);
    return 0;
}
