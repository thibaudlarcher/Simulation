////
////  MM1.c
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


#include "MM1.h"

void initialisePID(){
    pid_t pid = getpid();
    printf("PID : %d\n",pid);
    srandom(pid);
}

double Exponnentielle(int tab){
    double r = (double)random()/RAND_MAX;
    while(r == 0  || r==1){
        r = (double)random()/RAND_MAX;
    }
    printf(" %f \n",-log(r)/(tab*1.0));
    return -log(r)/(tab*1.0);
}
void Ajouter_Ech(event e){
    if(Ech.taille < MAXEVENT){
        Ech.Tab[Ech.taille] = e;
        Ech.taille++;
        //printf("Taille = %d \n",Ech.taille);
    }
    else {printf("Echeancier Plein \n");
        exit(1);
    }
}

void Init_Ech(){
    event e;
    for (int i =0; i<N; i++) {
        Serveur[i]=0;
    }
    e.type = 0;
    e.etat = 0;
    e.date = 0;
    Ech.taille = 0;
    Ajouter_Ech(e);
}
void Arrive_Event(event e){
    nn++;
    nmoyen+=n;
//    printf("execute EC \n");
    n++;
    event e1;
//    printf("valeur de n %d \n",n);
    e1.type = 0;
    e1.etat = 0;
    e1.date = e.date + Exponnentielle(Lambda);
    printf("Lambda");
    Ajouter_Ech(e1);

    if(n>=1 && n<=10){
        nbservUtil++;
        int serv = -1;
        for (int i =0; i<N; i++) {
            if(Serveur[i]==0){
                serv = i;
                break;
            }
        }
        Serveur[serv]=1;
        event e2;
        e2.serveur=serv;
        e2.type = 1;
        e2.date = e.date + Exponnentielle(Mu);
        printf("Mu");
        e2.etat = 0;

        Ajouter_Ech(e2);

    }
    temps = e.date;
    
}
void Service_Event(event e){
    //printf("execute SE \n");
    if (n>0){
        n--;
        nbservUtil--;
        Serveur[e.serveur] = 0;
        if (n>nbservUtil){
            nbservUtil++;
            event e1;
            Serveur[e.serveur] = 1;
            e1.serveur = e.serveur;
            e1.type = 1;
            e1.date = e.date + Exponnentielle(Mu);
            printf("Mu");
            e1.etat = 0;
            Ajouter_Ech(e1);
        }
            
        temps = e.date;
    }
    else {
        printf("Pas Service \n");
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

event Extraire(){
    int i,imin = 0;
    event min;

    for(i = 0;i<Ech.taille;i++){
        if(Ech.Tab[i].etat == 0){
            min = Ech.Tab[i];
            imin = i;
            break;
        }
    }
    for (i = 0; i<Ech.taille; i++) {
        if (min.date > Ech.Tab[i].date && Ech.Tab[i].etat == 0){
            min = Ech.Tab[i];
            imin = i;
        }
    }
    Ech.Tab[imin].etat = 1;
    return min;
}

int Condition_arret(long double old,long double new){

    if (fabs(old - new)<EPSILON && temps>1000) {
        compteur++;
        if (compteur<1e3) {
            return 1;
        }
    }
    return 0;
}

void simulation(FILE * F1){

    long double Oldmoyen=0;
    long double moyen=0;
    Init_Ech();
    event e;
    initialisePID();
    while (Condition_arret(Oldmoyen,moyen)==0) {
        e =Extraire();
        
        cumule += (e.date -temps)*n;
        
        //Temps dans le systéme
        Oldmoyen = moyen;
        moyen = cumule/temps;
        
        if(e.type == 0){
            Arrive_Event(e);
        }
        if (e.type == 1) {
            Service_Event(e);
        }
    }
    printf("Temps moyen Attente %f Temps moyen Systeme %Lf n moyen %f iteration %ld\n",tempsMoyenAttente,moyen,nmoyen/nn,nn);
}

