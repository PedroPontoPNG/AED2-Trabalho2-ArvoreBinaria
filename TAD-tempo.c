#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include "TAD-tempo.h"


double tempoDeExecucao(struct timespec inicio, struct timespec fim){
    long long tempoNano;
    double tempoMili, tempoSeg;
    tempoNano = (fim.tv_sec - inicio.tv_sec) * 1000000000LL + (fim.tv_nsec - inicio.tv_nsec);
    tempoMili = tempoNano / 1000000.0;
    tempoSeg = tempoNano / 1000000000.0;
    /*printf("\n========================\n");
    printf("Tempo de execução:\n");
    printf("  %lld nanosegundos\n", tempoNano);
    printf("  %.3lf milissegundos\n", tempoMili);
    printf("  %.6lf segundos\n", tempoSeg);
    printf("========================\n");*/
    return tempoSeg;
}
