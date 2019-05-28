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
echeancier EchMM1;
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
        //        printf("%f \n",cumuleMM1);
        
        Oldmoyen = moyen;
        moyen = cumuleMM1/tempsMM1;
        if(e.type == 0){
            
            Arrive_EventMM1(e,Lambda);
        }
        if (e.type == 1) {
            cumuleAttenteMM1 ++;
            Service_EventMM1(e);
            
        }
    }
    //Multipier Par 10 pour l'ensemble du système
    printf("Temps moyen Attente %f Temps moyen Systeme %Lf\n",tempsMoyenAttenteMM1/cumuleAttenteMM1,10*moyen);
    //A modifier pour percent tile
    fprintf(F1, "%d %f\n",Lambda,tempsMoyenAttenteMM1/cumuleAttenteMM1);
}

