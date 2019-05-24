////
////  MM1.h
////  Simulation
////
////  Created by jean-charles SOTTAS on 26/03/2019.
////  Copyright © 2019 jean-charles SOTTAS. All rights reserved.
////
//
#ifndef MM1_h
#define MM1_h
#include <stdio.h>
#include "File.h"
//Utile ?
double tempsMM10 = 0;
long int nMM10 = 0; //Personne dans le systeme
long int nnMM10=0;
int compteurMM10 = 0;
double cumuleMM10 = 0;
double nmoyenMM10 = 0;
double cumuleAttenteMM10 = 0;


int ServeurMM10[10];
int nbservUtilMM10 = 0;
double tempsMoyenAttenteMM10 = 0.;


echeancier EchMM10;
void réinitialisationMM10(void);
void Ajouter_EchMM10(event e);
void Init_EchMM10(void);
void Arrive_EventMM10(event e,int Lambda);
void Service_EventMM10(event e);


event ExtraireMM10(void);



void simulationMM10(FILE *F1,int Lambda);

#endif /* MM1_h */
