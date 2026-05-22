#include <stdio.h>
#include <stdlib.h>
#include "TAD-avl.h"

#define TAM_PILHA_AVL 64 /* AVL com 1M elementos tem altura max ~25 */

/* -----------------------------------------------------------------------
   Funcoes auxiliares internas
   ----------------------------------------------------------------------- */
static int alturaNo(NoAVL *no){
	return (no == NULL) ? 0 : no->altura;
}

static int maiorVal(int a, int b){
	return (a > b) ? a : b;
}

static void atualizarAltura(NoAVL *no){
	no->altura = 1 + maiorVal(alturaNo(no->esq), alturaNo(no->dir));
}

static int fb(NoAVL *no){
	return alturaNo(no->esq) - alturaNo(no->dir);
}

/* Rotacao simples a direita */
static NoAVL* rotDir(NoAVL *y){
	NoAVL *x = y->esq;
	y->esq = x->dir;
	x->dir = y;
	atualizarAltura(y);
	atualizarAltura(x);
	return x;
}

/* Rotacao simples a esquerda */
static NoAVL* rotEsq(NoAVL *x){
	NoAVL *y = x->dir;
	x->dir = y->esq;
	y->esq = x;
	atualizarAltura(x);
	atualizarAltura(y);
	return y;
}

/* Balancear um no apos insercao */
static NoAVL* balancear(NoAVL *no){
	atualizarAltura(no);
	int fator = fb(no);

	if(fator > 1){
		if(fb(no->esq) < 0)
			no->esq = rotEsq(no->esq);
		return rotDir(no);
	}
	if(fator < -1){
		if(fb(no->dir) > 0)
			no->dir = rotDir(no->dir);
		return rotEsq(no);
	}
	return no;
}

/* -----------------------------------------------------------------------
   Funcoes publicas
   ----------------------------------------------------------------------- */
NoAVL* criarAVL(){ return NULL; }

/* Insercao ITERATIVA na AVL com pilha de ancestrais */
NoAVL* inserirAVL(NoAVL* raiz, int chave){
	NoAVL* novo = (NoAVL*)malloc(sizeof(NoAVL));
	novo->info = chave;
	novo->altura = 1;
	novo->esq = NULL;
	novo->dir = NULL;

	if(raiz == NULL) return novo;

	/* Pilha de ancestrais para o caminho percorrido */
	NoAVL **caminho = (NoAVL**)malloc(TAM_PILHA_AVL * sizeof(NoAVL*));
	int *direcao = (int*)malloc(TAM_PILHA_AVL * sizeof(int)); /* 0 = esq, 1 = dir */
	int profundidade = 0;

	NoAVL *atual = raiz;
	while(atual != NULL){
		caminho[profundidade] = atual;
		if(chave < atual->info){
			direcao[profundidade] = 0;
			profundidade++;
			if(atual->esq == NULL){ atual->esq = novo; break; }
			atual = atual->esq;
		}else{
			direcao[profundidade] = 1;
			profundidade++;
			if(atual->dir == NULL){ atual->dir = novo; break; }
			atual = atual->dir;
		}
	}

	/* Percorrer o caminho de volta, balanceando */
	int i;
	for(i = profundidade - 1; i >= 0; i--){
		NoAVL* balanceado = balancear(caminho[i]);
		if(i == 0){
			raiz = balanceado;
		}else{
			if(direcao[i - 1] == 0)
				caminho[i - 1]->esq = balanceado;
			else
				caminho[i - 1]->dir = balanceado;
		}
	}

	free(caminho);
	free(direcao);
	return raiz;
}

/* Busca iterativa na AVL */
int buscarAVL(NoAVL *arv, int chave){
	NoAVL *atual = arv;
	while(atual != NULL){
		if(chave == atual->info) return 1;
		if(chave < atual->info) atual = atual->esq;
		else atual = atual->dir;
	}
	return 0;
}

/* Retorna a altura da AVL (armazenada no no raiz) */
int alturaAVL(NoAVL *arv){
	return (arv == NULL) ? 0 : arv->altura;
}

/* Liberacao iterativa da AVL */
NoAVL* liberarAVL(NoAVL* arv){
	if(arv == NULL) return NULL;

	int capacidade = 1024;
	NoAVL **pilha = (NoAVL**)malloc(capacidade * sizeof(NoAVL*));
	int topo = 0;

	pilha[topo++] = arv;
	while(topo > 0){
		NoAVL *no = pilha[--topo];
		if(topo + 2 >= capacidade){
			capacidade *= 2;
			pilha = (NoAVL**)realloc(pilha, capacidade * sizeof(NoAVL*));
		}
		if(no->esq) pilha[topo++] = no->esq;
		if(no->dir) pilha[topo++] = no->dir;
		free(no);
	}
	free(pilha);
	return NULL;
}
