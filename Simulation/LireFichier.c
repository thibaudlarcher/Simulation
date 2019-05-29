
#include "LireFichier.h"
#include <stdlib.h>
#define TAILLEMAX 1024
LAMBDA lirefichier(char* file){
    FILE* F = NULL;
    F = fopen(file, "r+");
    if(F == NULL)
        exit(1);
    LAMBDA L;
    L.size = 0;L.tab=NULL;
    int compt = -1;
    char chaine[TAILLEMAX] = "";
    while(fgets(chaine, TAILLEMAX , F) != NULL) {
        if(compt == -1){
            L.size = atoi(chaine);
            L.tab = malloc(L.size * sizeof(double));
            compt=0;
        }else{
            L.tab[compt]=atoi(chaine);
            compt++;
        }
    }
    return L;
}
void freeL(LAMBDA L){
    free(L.tab);
}
