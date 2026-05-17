#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

#include "TAD-arvores.h"
#include "TAD-Vetorzao.h"
#include "TAD-tempo.h"



int main(){

    struct timespec inicio, fim;

    setlocale(LC_ALL, "Portuguese");

    Arvore* arv = criarArvore();

    double tempoVet=0;
    double tempoArv=0;

    int i, n = 1000000;

    srand(time(NULL));

    for(i = 0; i < n; i++){

        int num = ((rand() << 15) | rand()) % 1000000;

        arv = inserirNaArvore(arv, num);

        inserirNoVetor(i, num);

    }

 quicksort(vetor, 0, 999999);

    for(int i=0;i<15;i++){
        int chave=sortearElementoNoVetor();

        clock_gettime(CLOCK_REALTIME, &inicio);

        buscar(arv, chave);

        clock_gettime(CLOCK_REALTIME, &fim);

        if (buscar(arv, chave)==1){

            printf("arvore:achado");

        }else {

            printf("arvore:nao achado");
        }

        tempoArv+= tempoDeExecucao(inicio,fim);

        printf("\n");

        printf("%.6lf segundos\n", tempoDeExecucao(inicio,fim));

        clock_gettime(CLOCK_REALTIME, &inicio);

        buscaBinaria(chave);

        clock_gettime(CLOCK_REALTIME, &fim);

        tempoVet+= tempoDeExecucao(inicio,fim);

        printf("\n");

        printf("%.6lf segundos\n", tempoDeExecucao(inicio,fim));


    }

    for(int i=0;i<15;i++){

        int chave=sortearElemento();

        clock_gettime(CLOCK_REALTIME, &inicio);

        buscar(arv, chave);

        clock_gettime(CLOCK_REALTIME, &fim);

         if (buscar(arv, chave)==1){

            printf("arvore: achado");

        }else {
            printf("arvore: nao achado");

        }
        tempoArv+= tempoDeExecucao(inicio,fim);

        printf("\n");

        printf("%.6lf segundos\n", tempoDeExecucao(inicio,fim));

        clock_gettime(CLOCK_REALTIME, &inicio);

        buscaBinaria(chave);

        clock_gettime(CLOCK_REALTIME, &fim);

        tempoVet+= tempoDeExecucao(inicio,fim);

        printf("\n");

        printf("%.6lf segundos\n", tempoDeExecucao(inicio,fim));


    }

    printf("%.6lf segundos\n", tempoVet);
    printf("%.6lf segundos\n", tempoArv);
    printf("\n");

    printf("tempo medio da busca em arvore: [%f]",mediaTempo30(tempoArv));
    printf("\n");
    printf("tempo medio da buca binaria no vetor: [%f]",mediaTempo30(tempoVet));
    printf("\n");


    printf("\n");
    return 0;
}