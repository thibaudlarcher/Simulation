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

void réinitialisationMM10min(void);
void Ajouter_EchMM10min(event e);
void Init_EchMM10min(void);
void Arrive_EventMM10min(event e,int Lambda);
void Service_EventMM10min(event e);


event ExtraireMM10min(void);



void simulationMM10min(FILE *F1,int Lambda);

#endif /* MM10min */
