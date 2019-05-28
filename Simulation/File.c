//
//  File.c
//  Simulation
//
//  Created by jean-charles SOTTAS on 23/05/2019.
//  Copyright © 2019 jean-charles SOTTAS. All rights reserved.
//

#include "File.h"

void initialisePID(){
    pid_t pid = getpid();
    printf("PID : %d\n",pid);
    srandom(pid);
}

double Exponnentielle(float tab){
    double r = (double)random()/RAND_MAX;
    while(r == 0  || r==1){
        r = (double)random()/RAND_MAX;
    }
//    printf(" %lf \n",-log(r)/(tab*1.0));
    return -log(r)/(tab*1.0);
}

int Condition_arret(long double old,long double new,int compteur, int temps){
    
    if (fabs(old - new)<EPSILON && temps>1000) {
        compteur++;
        if (compteur<1e3) {
            return 1;
        }
    }
    return 0;
}
//Pour la file MM1.
int Condition_arret2(long double old,long double new,int compteur, int temps){
    
    if (fabs(old - new)<EPSILON && temps>100000) {
        compteur++;
        if (compteur<1e3) {
            return 1;
        }
    }
    return 0;
}
