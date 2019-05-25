//
//  Question3.h
//  Simulation
//
//  Created by jean-charles SOTTAS on 23/05/2019.
//  Copyright © 2019 jean-charles SOTTAS. All rights reserved.
//

#ifndef MM10min_h
#define MM10min_h
#include "File.h"
#include <stdio.h>
double tempsMM10min = 0;
long int nMM10min = 0; //Personne dans le systeme
long int nnMM10min=0;
int compteurMM10min = 0;
double cumuleMM10min = 0;
double nmoyenMM10min = 0;
double cumuleAttenteMM10min = 0;

int fileServeurMM10min[10];  //Taille de la file pour chaque serveur
int ServeurMM10min[10];     //vaut 0 ou 1 si le serveur est disponible
int nbservUtilMM10min = 0;
double tempsMoyenAttenteMM10min = 0.;


echeancier EchMM10min;
void réinitialisationMM10min(void);
void Ajouter_EchMM10min(event e);
void Init_EchMM10min(void);
void Arrive_EventMM10min(event e,int Lambda);
void Service_EventMM10min(event e);


event ExtraireMM10min(void);



void simulationMM10min(FILE *F1,int Lambda);

#endif /* MM10min */
