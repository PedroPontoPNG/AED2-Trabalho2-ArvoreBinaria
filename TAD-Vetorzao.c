#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include "TAD-Vetorzao.h"

const int N = 1000000;
int vetor[1000000];



void inserirNoVetor(int i, int chave){

    vetor[i] = chave;

}

long int buscaBinaria(int chave){
    int inicio, fim, meio;
    inicio = 0; fim = N-1;

    while(inicio <= fim){
        meio = (inicio+fim)/2;
        if(chave > vetor[meio]){inicio = meio + 1;}
        else if(chave < vetor[meio]){fim = meio -1;}
        else{
            printf("\nVetor: Achado na posicao %d", meio);
            return meio;
        }
    }
    printf("\nVetor: Nao achado!\n");
    return -1;
}


int sortearElementoNoVetor(){
    int indiceAleatorio = ((rand() << 15) | rand()) % 1000000;    
    indiceAleatorio=vetor[indiceAleatorio];
    printf("\nChave de busca: [%d]\n",indiceAleatorio);
    return indiceAleatorio;

}

int sortearElemento(){
    int aleatorio;
    
    aleatorio = ((rand() << 15) | rand()) % 1000000;
    printf("\nChave de busca: [%d]\n",aleatorio);
    return aleatorio;
    

}

void trocar(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int particiona(int vet[], int inicio, int fim) {
    int pivo = vet[fim];
    int i = (inicio - 1);

    for (int j = inicio; j <= fim - 1; j++) {
        if (vet[j] <= pivo) {
            i++;
            trocar(&vet[i], &vet[j]);
        }
    }
    trocar(&vet[i + 1], &vet[fim]);
    return (i + 1);
}

void quicksort(int vet[], int inicio, int fim) {
    if (inicio < fim) {
        int pi = particiona(vet, inicio, fim);

        quicksort(vet, inicio, pi - 1);
        quicksort(vet, pi + 1, fim);
    }
}