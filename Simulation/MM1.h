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
#define Lambda 9
#define Mu 1
#define N 10
#define EPSILON 1e-5
#define MAXEVENT 1000000
#define MAXTEMPS 5000
#include <stdlib.h>     /* srand, rand */
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
//Utile ?
double temps = 0;
long int n = 0; //Personne dans le systeme
long int nn=0;
int compteur = 0;
double cumule = 0;
double nmoyen = 0;
double cumuleAttente = 0;


int Serveur[10];
int nbservUtil = 0;
double tempsMoyenAttente = 0.;
typedef struct Element Element;
struct Element
{
    double val;
    Element *suiv;
};
typedef struct List List;
struct List
{
    Element *p;
};
List L;


typedef struct Event{
    int serveur;
    int type;
    double date;
    int etat;
}event;

typedef struct Echeancier{
    event Tab[MAXEVENT];
    int taille;
}echeancier;

echeancier Ech;
void initialisePID(void);
double Exponnentielle(int tab);
void Ajouter_Ech(event e);

void Init_Ech(void);
void Arrive_Event(event e);
void Service_Event(event e);

void Affiche_echeancier(void);

event Extraire(void);



void simulation(FILE *F1);

#endif /* MM1_h */
