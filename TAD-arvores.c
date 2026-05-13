#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "TAD-arvores.h"



Arvore* criarArvore(){return NULL;}

Arvore* inserirNaArvore (Arvore* arv, int chave){
	if(arv == NULL){
		arv = (Arvore*)malloc(sizeof(Arvore));
		arv->info = chave;
		arv->esq = NULL;
		arv->dir = NULL;
	}
	else if(chave < arv->info){
		arv->esq = inserirNaArvore(arv->esq,chave);
	}
	else{
		arv->dir = inserirNaArvore(arv->dir,chave);
	}
	return arv;
}

void preOrdem(Arvore* arv){
	if(arv != NULL){
		printf("%d, ",arv->info);
		preOrdem(arv->esq);
		preOrdem(arv->dir);
	}
}

void emOrdem(Arvore* arv){
	if(arv != NULL){
		emOrdem(arv->esq);
		printf("%d, ",arv->info);
		emOrdem(arv->dir);
	}
}

void posOrdem(Arvore* arv){
	if(arv != NULL){
		posOrdem(arv->esq);
		posOrdem(arv->dir);
		printf("%d, ",arv->info);
	}
}

Arvore* remover(Arvore *arv, int chave){
	if(arv == NULL){return NULL;}
	else{/*Caminho na árvore procurando onde está o nó como info a ser removido*/
		if(arv->info > chave){
			arv->esq = remover(arv->esq,chave);
		}
		else if(arv->info < chave){
			arv->dir = remover(arv->dir,chave);
		}
		else{   /*Se for um nó folha, apenas o libero da memória*/
			if((arv->esq == NULL) && (arv->dir == NULL)){
				free(arv);
				arv = NULL;
			}/*Caso se tiver um nó filho na direita ou na esquerda*/
			else if(arv->dir == NULL){
				Arvore* temp = arv;
				arv = arv->esq;
				free(temp);
			}
			else if(arv->esq == NULL){
				Arvore* temp = arv;
				arv = arv->dir;
				free(temp);
			}
			else{
				Arvore* temp = arv->esq; 
				while(temp->dir != NULL){temp = temp->dir;}/*Procurar o elemento mais a direita da sub árvore a esquerda*/
				arv->info = temp->info;
				arv->esq = remover(arv->esq,chave);
			}
		}
	}
	return arv;
}


Arvore* libera(Arvore* arv){
	if(arv != NULL){
		libera(arv->esq);
		libera(arv->dir);
		free(arv);
	}
	return NULL;
}

int buscar( Arvore *arv, int chave){
	if(arv == NULL){
		return 0;
	}
	else if(chave < arv->info){
		return buscar(arv->esq,chave);
	}else if(chave > arv->info){
		return buscar(arv->dir,chave);
	}
	else{
		return 1;
	}
}

int maior(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

int maior_ramo(Arvore *arv){
   if((arv == NULL)){
        return 0;
   }
   else{
        return maior(maior_ramo(arv->dir) +arv->info, maior_ramo(arv->esq) + arv->info);
   }
}

int contarNos(Arvore *arv){
   if(arv == NULL)
        return 0;
   else
        return 1 + contarNos(arv->esq) + contarNos(arv->dir);
}

