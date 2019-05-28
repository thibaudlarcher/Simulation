//
//  MM1.c
//  Simulation
//
//  Created by jean-charles SOTTAS on 23/05/2019.
//  Copyright © 2019 jean-charles SOTTAS. All rights reserved.
//

#include "MM1.h"
double tempsMM1 = 0;
long int nMM1 = 0;
int compteurMM1 = 0;
double cumuleMM1 = 0;
long int nnMM1=0;
double nmoyenMM1 = 0;
double cumuleAttenteMM1 = 0;
double tempsMoyenAttenteMM1 = 0.;
//Tableau pour 90 percenttile
double TempAttenteMM1[MAXEVENT];
echeancier EchMM1;
int sizeMM1 = 0;
void reinitilisationMM1(){
    tempsMM1 = 0;
    nMM1 = 0;
    compteurMM1 = 0;
    cumuleMM1 = 0;
    nnMM1=0;
    nmoyenMM1 = 0;
    cumuleAttenteMM1 = 0;
    tempsMoyenAttenteMM1 = 0.;
    Init_EchMM1();
}

void Init_EchMM1(){
    event e;
    e.type = 0;
    e.etat = 0;
    e.date = 0;
    EchMM1.taille = 0;
    Ajouter_EchMM1(e);
}
void Ajouter_EchMM1(event e){
    if(EchMM1.taille < MAXEVENT){
        EchMM1.Tab[EchMM1.taille] = e;
        EchMM1.taille++;
        //        printf("Taille = %d \n",EchMM1.taille);
    }
    else {//printf("Echeancier Plein \n");
        exit(1);
    }
}

void Arrive_EventMM1(event e,int Lambda){
    //    1 er méthode
    //    Donne des résultats étrange sur les 2 derniers Lambda. Les valeurs sont trop élevé.
    //    int r = random()%9;
    //    if(r == 1){
    //        nnMM1++;
    //            printf("execute EC \n");
    //        nMM1++;
    //            printf("valeur n %d \n",nMM1);
    //    }
    //    double tmp =Exponnentielle((float)Lambda);
    
    //    2 éme méthode
    //Donne des résultats étrange. Les valeurs sont trop élevé.
    double tmp =Exponnentielle((float)Lambda/(float)N);
    nnMM1++;
    nMM1++;
    
    //printf("%f \n",tmp);
    
    event e1;
    e1.type = 0;
    e1.etat = 0;
    e1.date = e.date + tmp;
    Ajouter_EchMM1(e1);
    
    if(nMM1==1){
        nnMM1--;
        event e2;
        e2.type = 1;
        e2.date = e.date + Exponnentielle(Mu);
        e2.etat = 0;
        
        Ajouter_EchMM1(e2);
    }
    tempsMM1 = e.date;
}
void Service_EventMM1(event e){
    if (nMM1>0){
        nMM1--;
        if (nMM1>0){
            nnMM1--;
            event e1;
            e1.type = 1;
            e1.date = e.date + Exponnentielle(Mu);
            e1.etat = 0;
            Ajouter_EchMM1(e1);
        }
        tempsMM1 = e.date;
    }
    else {
        //printf("Pas Service \n");
    }
    
    
}


event ExtraireMM1(){
    int i,imin = 0;
    event min;
    for(i = 0;i<EchMM1.taille;i++){
        if(EchMM1.Tab[i].etat == 0){
            min = EchMM1.Tab[i];
            imin = i;
            break;
        }
    }
    for (i = 0; i<EchMM1.taille; i++) {
        if (min.date > EchMM1.Tab[i].date && EchMM1.Tab[i].etat == 0){
            min = EchMM1.Tab[i];
            imin = i;
        }
    }
    EchMM1.Tab[imin].etat = 1;
    return min;
}

void swapMM1(double* a, double* b)
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
int partitionMM1 (double arr[], int low, int high)
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
            swapMM1(&arr[i], &arr[j]);
        }
    }
    swapMM1(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
 low  --> Starting index,
 high  --> Ending index */
void quickSortMM1(double arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
         at right place */
        int pi = partitionMM1(arr, low, high);
        
        // Separately sort elements before
        // partition and after partition
        quickSortMM1(arr, low, pi - 1);
        quickSortMM1(arr, pi + 1, high);
    }
}

void simulationMM1(FILE * F1,int Lambda){
    reinitilisationMM1();
    long double Oldmoyen=0;
    long double moyen=0;
    Init_EchMM1();
    event e;
    initialisePID();
    while (Condition_arret2(Oldmoyen,moyen,compteurMM1,tempsMM1)==0) {
        e =ExtraireMM1();
        cumuleMM1 += (e.date -tempsMM1)*nMM1;
        tempsMoyenAttenteMM1 += (e.date - tempsMM1)*nnMM1;
        Oldmoyen = moyen;
        moyen = cumuleMM1/tempsMM1;
        for (int i = 0; i<nnMM1; i++) {
            TempAttenteMM1[sizeMM1+i]+=(e.date - tempsMM1) ;
        }
        if(e.type == 0){
            
            Arrive_EventMM1(e,Lambda);
        }
        if (e.type == 1) {
            sizeMM1++;
            cumuleAttenteMM1 ++;
            Service_EventMM1(e);
        }
    }
    quickSortMM1(TempAttenteMM1,0,sizeMM1-1);
    
    int nb = sizeMM1*0.9;
    //printf("%d\n",nb );
    //Multipier Par 10 pour l'ensemble du système
    printf("Temps moyen Attente %f Temps moyen Systeme %Lf, 90 percenttile %f\n",tempsMoyenAttenteMM1/cumuleAttenteMM1,10*moyen,TempAttenteMM1[nb]);
    //A modifier pour percent tile
    fprintf(F1, "%d %f %f\n",Lambda,tempsMoyenAttenteMM1/cumuleAttenteMM1,TempAttenteMM1[nb]);
}

