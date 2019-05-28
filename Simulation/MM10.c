////
////  MM10.c
////  Simulation
////
////  Created by jean-charles SOTTAS on 26/03/2019.
////  Copyright © 2019 jean-charles SOTTAS. All rights reserved.
////



//void Ecrire_Valeur(){
//    FILE *f = fopen("/Users/jean-charles/Desktop/Simulation/Simulation/Data_Expontielle.txt","w+");
//    for (int i = 0; i<TAILLE_MAX; i++) {
//        fprintf(f, "%.15Lf   %.15Lf   %.15Lf\n",Valeur[i],FctRepart1[i],FctRepart2[i]);
//    }
//    fclose(f);
//}


#include "MM10.h"
//Utile ?
double tempsMM10 = 0;
long int nMM10 = 0; //Personne dans le systeme
int compteurMM10 = 0;
double cumuleMM10 = 0;
double nmoyenMM10 = 0;
double cumuleAttenteMM10 = 0;


int ServeurMM10[10];
int nbservUtilMM10 = 0;
long int nnMM10=0;
double tempsMoyenAttenteMM10 = 0.;

//Tableau pour 90 percenttile
double TempAttenteMM10[MAXEVENT];

echeancier EchMM10;
void réinitialisationMM10(){
    tempsMM10 = 0;
    nMM10 = 0; //Personne dans le systeme
    nnMM10=0;
    compteurMM10 = 0;
    cumuleMM10 = 0;
    nmoyenMM10 = 0;
    cumuleAttenteMM10 = 0;
    nbservUtilMM10 = 0;
    tempsMoyenAttenteMM10 = 0.;
    for (int i = 0; i<10; i++) {
        ServeurMM10[i] = 0;
    }
    Init_EchMM10();
}

void Init_EchMM10(){
    event e;
    e.type = 0;
    e.etat = 0;
    e.date = 0;
    EchMM10.taille = 0;
    Ajouter_EchMM10(e);
}

void Ajouter_EchMM10(event e){
    if(EchMM10.taille < MAXEVENT){
        EchMM10.Tab[EchMM10.taille] = e;
        EchMM10.taille++;
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

event ExtraireMM10(){
    int i,imin = 0;
    event min;
    
    for(i = 0;i<EchMM10.taille;i++){
        if(EchMM10.Tab[i].etat == 0){
            min = EchMM10.Tab[i];
            imin = i;
            break;
        }
    }
    for (i = 0; i<EchMM10.taille; i++) {
        if (min.date > EchMM10.Tab[i].date && EchMM10.Tab[i].etat == 0){
            min = EchMM10.Tab[i];
            imin = i;
        }
    }
    EchMM10.Tab[imin].etat = 1;
    return min;
}

void Arrive_EventMM10(event e,int Lambda){
    nnMM10++;
//    printf("execute EC \n");
    nMM10++;
    event e1;
//    printf("valeur de n %d \n",n);
    e1.type = 0;
    e1.etat = 0;
    e1.date = e.date + Exponnentielle(Lambda);
    //printf("Lambda");
    Ajouter_EchMM10(e1);

    if(nMM10>=1 && nMM10<=10){
        //client plus en attente
        nnMM10--;
        //tempsMoyenAttenteMM10 += 0.0;
        
        nbservUtilMM10++;
        int serv = -1;
        for (int i =0; i<N; i++) {
            if(ServeurMM10[i]==0){
                serv = i;
                break;
            }
        }
        ServeurMM10[serv]=1;
        event e2;
        e2.serveur=serv;
        e2.type = 1;
        e2.date = e.date + Exponnentielle(Mu);
        //printf("Mu");
        e2.etat = 0;

        Ajouter_EchMM10(e2);

    }
    tempsMM10 = e.date;
    
}
void Service_EventMM10(event e){
    //printf("execute SE \n");
    if (nMM10>0){
        nMM10--;
        nbservUtilMM10--;
        ServeurMM10[e.serveur] = 0;
        if (nMM10>nbservUtilMM10){
            nnMM10--;
            //on recupere le temps d'attente
            nbservUtilMM10++;
            event e1;
            ServeurMM10[e.serveur] = 1;
            e1.serveur = e.serveur;
            e1.type = 1;
            e1.date = e.date + Exponnentielle(Mu);
            //printf("Mu");
            e1.etat = 0;
            Ajouter_EchMM10(e1);
        }
            
        tempsMM10 = e.date;
    }
    else {
        printf("Pas Service \n");
    }


}



void simulationMM10(FILE * F1,int Lambda){
    printf("Lambda %d \n",Lambda);
    réinitialisationMM10();
    long double Oldmoyen=0;
    long double moyen=0;
    Init_EchMM10();
    event e;
    initialisePID();
    while (Condition_arret(Oldmoyen,moyen,compteurMM10,tempsMM10)==0) {
        e =ExtraireMM10();
        
        cumuleMM10 += (e.date -tempsMM10)*nMM10;
        tempsMoyenAttenteMM10 +=(e.date - tempsMM10)*nnMM10;
        //Temps dans le systéme
        Oldmoyen = moyen;
        moyen = cumuleMM10/tempsMM10;
        //printf("%d %d\n",nnMM10,nMM10);
        if(e.type == 0){
            
            Arrive_EventMM10(e,Lambda);
            
        }
        if (e.type == 1) {
            cumuleAttenteMM10++;
            Service_EventMM10(e);
        }
    }
    printf("Temps moyen Attente %f Temps moyen Systeme %Lf\n",tempsMoyenAttenteMM10/cumuleAttenteMM10,moyen);
    fprintf(F1, "%d %f\n",Lambda,tempsMoyenAttenteMM10/cumuleAttenteMM10);
}

