

#ifndef MM1_h
#define MM1_h


#include <stdlib.h>     /* srand, rand */
#include <stdio.h>
#include "File.h"

void réinitialisationMM1(void);
void Init_EchMM1(void);
void Arrive_EventMM1(event e,int Lambda);
void Service_EventMM1(event e);
void Ajouter_EchMM1(event e);
void Affiche_echeancierMM1(void);
event ExtraireMM1(void);

void simulationMM1(FILE *F1,int Lambda);

#endif /* MM1_h */
