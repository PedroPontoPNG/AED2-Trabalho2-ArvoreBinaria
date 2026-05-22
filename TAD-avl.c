#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "TAD-avl.h"

AVL* criarAVL() {
    return NULL;
}

int alturaAVL(AVL* no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

int fatorBalanceamento(AVL* no) {
    if (no == NULL)
        return 0;
    return alturaAVL(no->esq) - alturaAVL(no->dir);
}

AVL* atualizarAltura(AVL* no) {
    int altEsq = alturaAVL(no->esq);
    int altDir = alturaAVL(no->dir);
    no->altura = (altEsq > altDir ? altEsq : altDir) + 1;
    return no;
}

/* Rotacao simples para a direita */
AVL* rotacaoDireita(AVL* y) {
    AVL* x = y->esq;
    AVL* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    atualizarAltura(y);
    atualizarAltura(x);

    return x;
}

/* Rotacao simples para a esquerda */
AVL* rotacaoEsquerda(AVL* x) {
    AVL* y = x->dir;
    AVL* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

/* Rotacao dupla esquerda-direita */
AVL* rotacaoEsquerdaDireita(AVL* no) {
    no->esq = rotacaoEsquerda(no->esq);
    return rotacaoDireita(no);
}

/* Rotacao dupla direita-esquerda */
AVL* rotacaoDireitaEsquerda(AVL* no) {
    no->dir = rotacaoDireita(no->dir);
    return rotacaoEsquerda(no);
}

AVL* inserirNaAVL(AVL* arv, int chave) {
    /* Insercao normal de BST */
    if (arv == NULL) {
        arv = (AVL*) malloc(sizeof(AVL));
        arv->info = chave;
        arv->altura = 1;
        arv->esq = NULL;
        arv->dir = NULL;
        return arv;
    }

    if (chave < arv->info) {
        arv->esq = inserirNaAVL(arv->esq, chave);
    } else if (chave > arv->info) {
        arv->dir = inserirNaAVL(arv->dir, chave);
    } else {
        /* Chave duplicada: ignora */
        return arv;
    }

    /* Atualiza altura do no atual */

    atualizarAltura(arv);

    /* Verifica fator de balanceamento e aplica rotacoes */

    int fb = fatorBalanceamento(arv);

    /* Caso Esquerda-Esquerda */

    if (fb > 1 && chave < arv->esq->info)
        return rotacaoDireita(arv);

    /* Caso Direita-Direita */

    if (fb < -1 && chave > arv->dir->info)
        return rotacaoEsquerda(arv);

    /* Caso Esquerda-Direita */

    if (fb > 1 && chave > arv->esq->info)
        return rotacaoEsquerdaDireita(arv);

    /* Caso Direita-Esquerda */
    
    if (fb < -1 && chave < arv->dir->info)
        return rotacaoDireitaEsquerda(arv);

    return arv;
}

int buscarAVL(AVL* arv, int chave) {
    if (arv == NULL) {
        return 0;
    } else if (chave < arv->info) {
        return buscarAVL(arv->esq, chave);
    } else if (chave > arv->info) {
        return buscarAVL(arv->dir, chave);
    } else {
        return 1;
    }
}

int alturaRealAVL(AVL* arv) {
    return alturaAVL(arv);
}

AVL* liberaAVL(AVL* arv) {
    if (arv != NULL) {
        liberaAVL(arv->esq);
        liberaAVL(arv->dir);
        free(arv);
    }
    return NULL;
}
