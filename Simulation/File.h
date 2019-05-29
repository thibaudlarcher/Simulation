
#ifndef File_h
#define File_h
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


typedef struct Event{
    int serveur;    //Pour la file MM10 et MM10min
    int type;
    double date;
    int etat;
}event;

typedef struct Echeancier{
    event Tab[MAXEVENT];
    int taille;
}echeancier;


void initialisePID(void);
double Exponnentielle(float tab);
int Condition_arret(long double old,long double new ,int compteur, int temps);
int Condition_arret2(long double old,long double new ,int compteur, int temps);
#endif /* File_h */
