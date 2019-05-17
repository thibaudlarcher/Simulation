//
//  main.c
//  Simulation
//
//  Created by jean-charles SOTTAS on 22/03/2019.
//  Copyright © 2019 jean-charles SOTTAS. All rights reserved.
//

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>     /* srand, rand */
#include <stdio.h>
#include <time.h>
int main(int argc, const char * argv[]) {
//    Question 1
    FILE* F1 = fopen("/Users/jean-charles/Desktop/Simulation/Projet/Simulation/Temps.txt", "w+");
    simulation(F1);
    fclose(F1);
//    Question 2
//    FILE* F1 = fopen("/Users/jean-charles/Desktop/Simulation/Projet/Simulation/Temps.txt", "w+");
//    simulation(F1);
//    fclose(F1);
//    Question 3
//    FILE* F1 = fopen("/Users/jean-charles/Desktop/Simulation/Projet/Simulation/Temps.txt", "w+");
//    simulation(F1);
//    fclose(F1);
    return 0;
}
