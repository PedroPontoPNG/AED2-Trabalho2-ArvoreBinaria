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

    long memoriaVetor = 1000000 * sizeof(int);

    long memoriaArvore = 1000000 * sizeof(struct arv); 




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

        printf("\n%.6lf segundos\n", tempoDeExecucao(inicio,fim));

        clock_gettime(CLOCK_REALTIME, &inicio);

        buscaBinaria(chave);

        clock_gettime(CLOCK_REALTIME, &fim);

        tempoVet+= tempoDeExecucao(inicio,fim);

        printf("\n%.6lf segundos\n", tempoDeExecucao(inicio,fim));


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


        printf("\n%.6lf segundos\n", tempoDeExecucao(inicio,fim));

        clock_gettime(CLOCK_REALTIME, &inicio);

        buscaBinaria(chave);

        clock_gettime(CLOCK_REALTIME, &fim);

        tempoVet+= tempoDeExecucao(inicio,fim);

        printf("\n%.6lf segundos\n", tempoDeExecucao(inicio,fim));


    }

    printf("\n//////////////////////////////////////////////////////////////////////////////////\n");

    printf("\n%.6lf segundos\n", tempoVet);

    printf("\n%.6lf segundos\n", tempoArv);

    printf("\n//////////////////////////////////////////////////////////////////////////////////\n");

    printf("\n tempo medio da busca em arvore: [%f]\n",mediaTempo30(tempoArv));

    printf("\n tempo medio da buca binaria no vetor: [%f]\n",mediaTempo30(tempoVet));


    printf("\n//////////////////////////////////////////////////////////////////////////////////\n");

    printf("\nMemoria do Vetor: %ld bytes (aprox. %ld MB)\n", memoriaVetor, memoriaVetor / 1048576);

    printf("\nMemoria da Arvore: %ld bytes (aprox. %ld MB)\n", memoriaArvore, memoriaArvore / 1048576);

    printf("\n//////////////////////////////////////////////////////////////////////////////////\n");

    if (memoriaVetor>memoriaArvore){

    printf("\nMemoria do Vetor eh maior que a da Arvore por aprox. %ld MB)\n", (memoriaVetor / 1048576)-memoriaArvore / 1048576);

    }else{

        printf("\nMemoria da Arvore eh maior que a do Vetor por aprox. %ld MB)\n", (memoriaArvore / 1048576)-memoriaVetor / 1048576);

    }
    
    printf("\n//////////////////////////////////////////////////////////////////////////////////\n");

    return 0;
}