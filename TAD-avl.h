#ifndef TAD_AVL_H
#define TAD_AVL_H

typedef struct noAVL{
	int info;
	int altura;
	struct noAVL *esq;
	struct noAVL *dir;
}NoAVL;

NoAVL* criarAVL();
NoAVL* inserirAVL(NoAVL* arv, int chave);
int buscarAVL(NoAVL *arv, int chave);
int alturaAVL(NoAVL *arv);
NoAVL* liberarAVL(NoAVL* arv);

#endif
