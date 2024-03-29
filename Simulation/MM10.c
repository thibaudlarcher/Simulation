
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
int sizeMM10 = 0;
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
    sizeMM10 = 0;
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
    }
    else {printf("Echeancier Plein \n");
        exit(1);
    }
}


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
    nMM10++;
    event e1;
    e1.type = 0;
    e1.etat = 0;
    e1.date = e.date + Exponnentielle(Lambda);
    Ajouter_EchMM10(e1);

    if(nMM10>=1 && nMM10<=10){
        //client plus en attente
        nnMM10--;

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
        e2.etat = 0;

        Ajouter_EchMM10(e2);

    }
    tempsMM10 = e.date;

}
void Service_EventMM10(event e){
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
            e1.etat = 0;
            Ajouter_EchMM10(e1);
        }

        tempsMM10 = e.date;
    }
    else {
    }
}




void swapMM10(double* a, double* b)
{
    double t = *a;
    *a = *b;
    *b = t;
}


int partitionMM10 (double arr[], int low, int high)
{
    double pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {

        if (arr[j] <= pivot)
        {
            i++;
            swapMM10(&arr[i], &arr[j]);
        }
    }
    swapMM10(&arr[i + 1], &arr[high]);
    return (i + 1);
}


void quickSortMM10(double arr[], int low, int high)
{
    if (low < high)
    {

        int pi = partitionMM10(arr, low, high);


        quickSortMM10(arr, low, pi - 1);
        quickSortMM10(arr, pi + 1, high);
    }
}


void simulationMM10(FILE * F1,int Lambda){

    réinitialisationMM10();
    for (int i = 0; i<MAXEVENT; i++) {
        TempAttenteMM10[i]=0 ;
    }
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

        //Ajout des valeurs dans tableau 90tile
        for (int i = 0; i<nnMM10; i++) {
            TempAttenteMM10[sizeMM10+i]+=(e.date - tempsMM10) ;
        }

        if(e.type == 0){

            Arrive_EventMM10(e,Lambda);

        }
        if (e.type == 1) {
            //1 personne sort de l'attente
            sizeMM10++;
            cumuleAttenteMM10++;
            Service_EventMM10(e);
        }
    }
    quickSortMM10(TempAttenteMM10,0,sizeMM10-1);
    int nb = sizeMM10*0.9;

    printf("Temps moyen Attente %f Temps moyen Systeme %Lf 90percentile %f\n",tempsMoyenAttenteMM10/cumuleAttenteMM10,moyen,TempAttenteMM10[nb]);
    fprintf(F1, "%d %f %f\n",Lambda,tempsMoyenAttenteMM10/cumuleAttenteMM10,TempAttenteMM10[nb]);
}
