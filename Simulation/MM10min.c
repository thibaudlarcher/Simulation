//
//  Question3.c
//  Simulation
//
//  Created by jean-charles SOTTAS on 23/05/2019.
//  Copyright © 2019 jean-charles SOTTAS. All rights reserved.
//

#include "MM10min.h"
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
//Tableau pour 90 percenttile
double TempAttenteMM10min[MAXEVENT];
int sizeMM10min = 0;
echeancier EchMM10min;
void réinitialisationMM10min(){
    tempsMM10min = 0;
    nMM10min = 0; //Personne dans le systeme
    nnMM10min=0;
    compteurMM10min = 0;
    cumuleMM10min = 0;
    nmoyenMM10min = 0;
    cumuleAttenteMM10min = 0;
    nbservUtilMM10min = 0;
    tempsMoyenAttenteMM10min = 0.;
    for (int i = 0; i<10; i++) {
        fileServeurMM10min[i] = 0;
        ServeurMM10min[i] = 0;
    }
    Init_EchMM10min();
}

void Init_EchMM10min(){
    event e;
    e.type = 0;
    e.etat = 0;
    e.date = 0;
    EchMM10min.taille = 0;
    Ajouter_EchMM10min(e);
}

void Ajouter_EchMM10min(event e){
    if(EchMM10min.taille < MAXEVENT){
        EchMM10min.Tab[EchMM10min.taille] = e;
        EchMM10min.taille++;
        //printf("Taille = %d \n",Ech.taille);
    }
    else {printf("Echeancier Plein \n");
        exit(1);
    }
}


//void Affiche_echeancier(){
//    event e;
//
//    printf("--> temps %f et N = %ld taille : %d [",temps,n,Ech.taille);
//    for (int i = 0; i<Ech.taille; i++) {
//        e = Ech.Tab[i];
//
//        if(e.type ==0)
//            printf(" (AC %lf,%d",e.date,e.etat);
//        if(e.type ==1)
//            printf(" (FS %lf,%d",e.date,e.etat);
//    }
//    printf("] \n \n");
//}

event ExtraireMM10min(){
    int i,imin = 0;
    event min;
    
    for(i = 0;i<EchMM10min.taille;i++){
        if(EchMM10min.Tab[i].etat == 0){
            min = EchMM10min.Tab[i];
            imin = i;
            break;
        }
    }
    for (i = 0; i<EchMM10min.taille; i++) {
        if (min.date > EchMM10min.Tab[i].date && EchMM10min.Tab[i].etat == 0){
            min = EchMM10min.Tab[i];
            imin = i;
        }
    }
    EchMM10min.Tab[imin].etat = 1;
    return min;
}

void Arrive_EventMM10min(event e,int Lambda){
    nnMM10min++;
    nmoyenMM10min+=nMM10min;
    
    nMM10min++;    int j = 0;
    for (int i =0; i<N; i++) {
        if(fileServeurMM10min[i]<fileServeurMM10min[j]){
            j=i;
        }
    }
    
    event e1;
    fileServeurMM10min[j]++;
    e1.type = 0;
    e1.etat = 0;
    e1.date = e.date + Exponnentielle(Lambda);
    Ajouter_EchMM10min(e1);
    
    if(fileServeurMM10min[j] == 1){
        nnMM10min--;
        ServeurMM10min[j]=1;
        event e2;
        e2.serveur=j;
        e2.type = 1;
        e2.date = e.date + Exponnentielle(Mu);
        e2.etat = 0;
        Ajouter_EchMM10min(e2);
    }
    tempsMM10min = e.date;
    
}
void Service_EventMM10min(event e){
    if (fileServeurMM10min[e.serveur]>0){
        nMM10min--;
        fileServeurMM10min[e.serveur]--;
        ServeurMM10min[e.serveur] = 0;
        if (fileServeurMM10min[e.serveur]!=0){
            nnMM10min--;
            event e1;
            ServeurMM10min[e.serveur] = 1;
            e1.serveur = e.serveur;
            e1.type = 1;
            e1.date = e.date + Exponnentielle(Mu);
            e1.etat = 0;
            Ajouter_EchMM10min(e1);
        }
        
        tempsMM10min = e.date;
    }
    else {
        printf("Pas Service \n");
    }
    
    
}

void swapMM10min(double* a, double* b)
{
    double t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
 the pivot element at its correct position in sorted
 array, and places all smaller (smaller than pivot)
 to left of pivot and all greater elements to right
 of pivot */
int partitionMM10min (double arr[], int low, int high)
{
    double pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
    
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swapMM10min(&arr[i], &arr[j]);
        }
    }
    swapMM10min(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
 low  --> Starting index,
 high  --> Ending index */
void quickSortMM10min(double arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
         at right place */
        int pi = partitionMM10min(arr, low, high);
        
        // Separately sort elements before
        // partition and after partition
        quickSortMM10min(arr, low, pi - 1);
        quickSortMM10min(arr, pi + 1, high);
    }
}

void simulationMM10min(FILE * F1,int Lambda){
    printf("Lambda %d \n",Lambda);
    réinitialisationMM10min();
    long double Oldmoyen=0;
    long double moyen=0;
    Init_EchMM10min();
    event e;
    initialisePID();
    while (Condition_arret(Oldmoyen,moyen,compteurMM10min,tempsMM10min)==0) {
        e =ExtraireMM10min();
        
        cumuleMM10min += (e.date -tempsMM10min)*nMM10min;
        
        //Temps dans le systéme
        Oldmoyen = moyen;
        moyen = cumuleMM10min/tempsMM10min;
        tempsMoyenAttenteMM10min+= (e.date -tempsMM10min)*nnMM10min;
        //Ajout des valeurs dans tableau 90tile
        for (int i = 0; i<nnMM10min; i++) {
            TempAttenteMM10min[sizeMM10min+i]+=(e.date - tempsMM10min) ;
        }
        if(e.type == 0){
            Arrive_EventMM10min(e,Lambda);
        }
        if (e.type == 1) {
            sizeMM10min++;
            cumuleAttenteMM10min++;
            Service_EventMM10min(e);
        }
    }
    quickSortMM10min(TempAttenteMM10min,0,sizeMM10min-1);
    int nb = sizeMM10min*0.9;
    printf("Temps moyen Attente %f Temps moyen Systeme %Lf, 90 percentile %f\n",tempsMoyenAttenteMM10min/cumuleAttenteMM10min,moyen,TempAttenteMM10min[nb]);
    fprintf(F1, "%d %f %f\n",Lambda,tempsMoyenAttenteMM10min/cumuleAttenteMM10min,TempAttenteMM10min[nb]);
}

