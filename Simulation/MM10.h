
#ifndef MM10_h
#define MM10_h
#include <stdio.h>
#include "File.h"

void réinitialisationMM10(void);
void Ajouter_EchMM10(event e);
void Init_EchMM10(void);
void Arrive_EventMM10(event e,int Lambda);
void Service_EventMM10(event e);

event ExtraireMM10(void);



void simulationMM10(FILE *F1,int Lambda);

#endif /* MM10_h */
