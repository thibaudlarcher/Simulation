//
//  MM1.h
//  Simulation
//
//  Created by jean-charles SOTTAS on 23/05/2019.
//  Copyright © 2019 jean-charles SOTTAS. All rights reserved.
//

#ifndef MM1_h
#define MM1_h


#include <stdlib.h>     /* srand, rand */
#include <stdio.h>
#include "File.h"
double tempsMM1 = 0;
long int nMM1 = 0;
int compteurMM1 = 0;
double cumuleMM1 = 0;
long int nnMM1=0;
double nmoyenMM1 = 0;
double cumuleAttenteMM1 = 0;
double tempsMoyenAttenteMM1 = 0.;
echeancier EchMM1;
void réinitialisationMM1(void);
void Init_EchMM1(void);
void Arrive_EventMM1(event e,int Lambda);
void Service_EventMM1(event e);
void Ajouter_EchMM1(event e);
void Affiche_echeancierMM1(void);
event ExtraireMM1(void);

void simulationMM1(FILE *F1,int Lambda);

#endif /* MM1_h */
