
#include <stdio.h>
#include "LireFichier.h"
#include "MM10.h"
#include "MM1.h"
#include "MM10min.h"
int main(int argc, const char * argv[]) {
    LAMBDA L;
    L = lirefichier(argv[1]);
    int i = 0;
    for (i = 0; i < L.size; i++) {
        printf("%d \n",L.tab[i]);
    }
    printf("======== MM10 ========\n");
//    Question 1
    FILE* F1 = fopen("Temps1.txt", "w+");
    for (i = 0; i<L.size; i++) {
        if(L.tab[i]>=N){
            fprintf(F1, "%d -1 -1\n",L.tab[i]);
        }
        else{
            simulationMM10(F1,L.tab[i]);
        }
    }
    fclose(F1);
     printf("======== NMM1 ========\n");
//    Question 2
//    Linux
    FILE* F2 = fopen("Temps2.txt", "w+");
    for (i = 0; i<L.size; i++) {
        if(L.tab[i]>=N){
            fprintf(F1, "%d -1 -1\n",L.tab[i]);
        }
        else{
            simulationMM1(F2,L.tab[i]);
        }
    }
    fclose(F2);
     printf("======= MM10min =======\n");
//    Question 3
    FILE* F3 = fopen("Temps3.txt", "w+");
    for (i = 0; i<L.size; i++) {
        if(L.tab[i]>=N){
            fprintf(F1, "%d -1 -1\n",L.tab[i]);
        }
        else{
            simulationMM10min(F3,L.tab[i]);
        }
    }
    fclose(F3);
    freeL(L);
    return 0;
}
