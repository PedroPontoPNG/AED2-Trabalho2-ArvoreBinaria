#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

#include "TAD-arvores.h"
#include "TAD-avl.h"
#include "TAD-Vetorzao.h"
#include "TAD-tempo.h"

/* -----------------------------------------------------------------------
   Funcoes auxiliares locais para a BST
   (inserção iterativa que rejeita duplicatas e cálculo de altura)
   ----------------------------------------------------------------------- */

/* Inserção iterativa na BST - ignora duplicatas para comparacao justa com AVL */
Arvore* inserirBST(Arvore* arv, int chave) {
    Arvore* novo = (Arvore*)malloc(sizeof(Arvore));
    novo->info = chave;
    novo->esq = NULL;
    novo->dir = NULL;

    if (arv == NULL) return novo;

    Arvore* atual = arv;
    while (1) {
        if (chave < atual->info) {
            if (atual->esq == NULL) { atual->esq = novo; return arv; }
            atual = atual->esq;
        } else if (chave > atual->info) {
            if (atual->dir == NULL) { atual->dir = novo; return arv; }
            atual = atual->dir;
        } else {
            /* Chave duplicada: ignora (mesmo comportamento da AVL) */
            free(novo);
            return arv;
        }
    }
}

/* Altura da BST (recursiva - segura para altura ~50 com dados aleatorios) */
int alturaBST(Arvore* arv) {
    if (arv == NULL) return 0;
    int hEsq = alturaBST(arv->esq);
    int hDir = alturaBST(arv->dir);
    return 1 + (hEsq > hDir ? hEsq : hDir);
}

/* -----------------------------------------------------------------------
   Programa Principal
   ----------------------------------------------------------------------- */
int main() {

    struct timespec inicio, fim;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    int n = 1000000;
    int execucoes = 10;
    int buscas = 30;

    /* Gera os valores uma unica vez para usar em todas as execucoes */
    int* valores = (int*) malloc(n * sizeof(int));
    if (valores == NULL) {
        printf("Erro ao alocar memoria para os valores.\n");
        return 1;
    }

    srand(42); /* Semente fixa para reproducibilidade entre execucoes */
    for (int i = 0; i < n; i++) {
        valores[i] = (int)((unsigned int)((rand() << 15) | rand()) % 1000000U);
    }

    /* Preenche o vetor com os mesmos valores e ordena para busca binaria */
    for (int i = 0; i < n; i++) {
        inserirNoVetor(i, valores[i]);
    }
    quicksort(vetor, 0, n - 1);

    /* Gera as 30 chaves de busca
     (as mesmas para todas as execucoes):
       15 presentes no vetor + 15 aleatorias (podem ou nao estar) */

    int chavesBusca[30];
    srand(time(NULL));

    printf("=== Chaves de busca geradas ===\n");
    for (int i = 0; i < 15; i++) {
        int idx = (int)((unsigned int)((rand() << 15) | rand()) % (unsigned int)n);
        chavesBusca[i] = vetor[idx]; /* presente */
        printf("Busca %2d (presente): %d\n", i + 1, chavesBusca[i]);
    }
    for (int i = 15; i < 30; i++) {
        chavesBusca[i] = (int)((unsigned int)((rand() << 15) | rand()) % 1000000U); /* aleatoria */
        printf("Busca %2d (aleatoria): %d\n", i + 1, chavesBusca[i]);
    }
    printf("\n");


    /* Variaveis para acumular resultados das 10 execucoes */

    double tempoCriacaoAVL_total  = 0.0;
    double tempoCriacaoBST_total  = 0.0;
    double tempoBuscaAVL_total    = 0.0;
    double tempoBuscaBST_total    = 0.0;

    printf("============================================================\n");
    printf("       COMPARACAO: ARVORE AVL  x  ARVORE BST\n");
    printf("       %d elementos | %d execucoes | %d buscas por execucao\n", n, execucoes, buscas);
    printf("============================================================\n\n");

    for (int exec = 0; exec < execucoes; exec++) {

        printf("--- Execucao %d/%d ---\n", exec + 1, execucoes);

        /* ---- Criacao da AVL ---- */

        AVL* avl = criarAVL();

        clock_gettime(CLOCK_REALTIME, &inicio);
        for (int i = 0; i < n; i++) {
            avl = inserirNaAVL(avl, valores[i]);
        }
        clock_gettime(CLOCK_REALTIME, &fim);

        double tCriacaoAVL = tempoDeExecucao(inicio, fim);
        tempoCriacaoAVL_total += tCriacaoAVL;

        int altAVL = alturaRealAVL(avl);
        printf("  AVL  - Criacao: %.6lf s | Altura: %d\n", tCriacaoAVL, altAVL);

        /* ---- Criacao da BST ---- */

        Arvore* bst = criarArvore();

        clock_gettime(CLOCK_REALTIME, &inicio);
        for (int i = 0; i < n; i++) {
            bst = inserirBST(bst, valores[i]);
        }
        clock_gettime(CLOCK_REALTIME, &fim);

        double tCriacaoBST = tempoDeExecucao(inicio, fim);
        tempoCriacaoBST_total += tCriacaoBST;

        /* Calcula altura da BST */
        int altBST = alturaBST(bst);

        printf("  BST  - Criacao: %.6lf s | Altura: %d\n", tCriacaoBST, altBST);

        /* ---- Buscas na AVL ---- */

        double tBuscaAVL = 0.0;
        for (int b = 0; b < buscas; b++) {
            clock_gettime(CLOCK_REALTIME, &inicio);
            int achou = buscarAVL(avl, chavesBusca[b]);
            clock_gettime(CLOCK_REALTIME, &fim);
            tBuscaAVL += tempoDeExecucao(inicio, fim);
        }
        tempoBuscaAVL_total += tBuscaAVL;
        printf("  AVL  - Tempo total %d buscas: %.6lf s | Media: %.9lf s\n",
               buscas, tBuscaAVL, tBuscaAVL / buscas);

        /* ---- Buscas na BST ---- */

        double tBuscaBST = 0.0;
        for (int b = 0; b < buscas; b++) {
            clock_gettime(CLOCK_REALTIME, &inicio);
            int achou = buscar(bst, chavesBusca[b]);
            clock_gettime(CLOCK_REALTIME, &fim);
            tBuscaBST += tempoDeExecucao(inicio, fim);
        }
        tempoBuscaBST_total += tBuscaBST;
        printf("  BST  - Tempo total %d buscas: %.6lf s | Media: %.9lf s\n",
               buscas, tBuscaBST, tBuscaBST / buscas);

        printf("\n");

        /* Libera memoria das arvores desta execucao */

        avl = liberaAVL(avl);
        bst = libera(bst);
    }

    /* ---- Resultados finais ---- */

    printf("============================================================\n");
    printf("                   RESULTADOS FINAIS\n");
    printf("============================================================\n\n");

    printf("CRIACAO DAS ARVORES (%d execucoes com %d elementos):\n", execucoes, n);
    printf("  AVL  - Tempo total: %.6lf s | Tempo medio por execucao: %.6lf s\n",
           tempoCriacaoAVL_total, tempoCriacaoAVL_total / execucoes);
    printf("  BST  - Tempo total: %.6lf s | Tempo medio por execucao: %.6lf s\n",
           tempoCriacaoBST_total, tempoCriacaoBST_total / execucoes);
    printf("\n");

    printf("BUSCA NAS ARVORES (%d execucoes x %d buscas = %d buscas totais):\n",
           execucoes, buscas, execucoes * buscas);
    printf("  AVL  - Tempo total: %.6lf s | Media por busca: %.9lf s\n",
           tempoBuscaAVL_total, tempoBuscaAVL_total / (execucoes * buscas));
    printf("  BST  - Tempo total: %.6lf s | Media por busca: %.9lf s\n",
           tempoBuscaBST_total, tempoBuscaBST_total / (execucoes * buscas));
    printf("\n");

    if (tempoCriacaoAVL_total > tempoCriacaoBST_total) {
        printf("  -> Criacao: BST foi %.2lf%% mais rapida que AVL.\n",
               ((tempoCriacaoAVL_total - tempoCriacaoBST_total) / tempoCriacaoAVL_total) * 100.0);
    } else {
        printf("  -> Criacao: AVL foi %.2lf%% mais rapida que BST.\n",
               ((tempoCriacaoBST_total - tempoCriacaoAVL_total) / tempoCriacaoBST_total) * 100.0);
    }

    if (tempoBuscaAVL_total < tempoBuscaBST_total) {
        printf("  -> Busca:   AVL foi %.2lf%% mais rapida que BST.\n",
               ((tempoBuscaBST_total - tempoBuscaAVL_total) / tempoBuscaBST_total) * 100.0);
    } else {
        printf("  -> Busca:   BST foi %.2lf%% mais rapida que AVL.\n",
               ((tempoBuscaAVL_total - tempoBuscaBST_total) / tempoBuscaAVL_total) * 100.0);
    }

    printf("\n");

    free(valores);
    return 0;
}
