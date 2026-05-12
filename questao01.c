#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include "TAD-arvores.h"

int main(){
    setlocale(LC_ALL, "Portuguese");
    Arvore* arv = criarArvore();

    int i, n = 20;
    srand(time(NULL));
    for(i = 0; i < n; i++){
        int num = rand() % 100;
        printf("%d ", num);
        arv = inserirNaArvore(arv, num);
    }
    printf("\n");
    printf("Pre-ordem: ");
    preOrdem(arv);
    printf("\n");
    printf("Em-ordem: ");
    emOrdem(arv);
    printf("\n");
    printf("Pós-ordem: ");
    posOrdem(arv);
    printf("\n");
    
    return 0;
}