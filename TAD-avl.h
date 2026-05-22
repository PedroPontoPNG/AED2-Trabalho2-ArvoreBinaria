#ifndef TAD_AVL_H
#define TAD_AVL_H

typedef struct avl {
    int info;
    int altura;
    struct avl* esq;
    struct avl* dir;
} AVL;

AVL* criarAVL();
int alturaAVL(AVL* no);
int fatorBalanceamento(AVL* no);
AVL* atualizarAltura(AVL* no);
AVL* rotacaoDireita(AVL* y);
AVL* rotacaoEsquerda(AVL* x);
AVL* rotacaoEsquerdaDireita(AVL* no);
AVL* rotacaoDireitaEsquerda(AVL* no);
AVL* inserirNaAVL(AVL* arv, int chave);
int buscarAVL(AVL* arv, int chave);
int alturaRealAVL(AVL* arv);
AVL* liberaAVL(AVL* arv);

#endif
