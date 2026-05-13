#ifndef TAD_ARVORES_H
#define TAD_ARVORES_H

typedef struct arv{
	int info;
	struct arv* dir;
	struct arv* esq;
}Arvore;

Arvore* criarArvore();
Arvore* inserirNaArvore (Arvore* arv, int chave);
void preOrdem(Arvore* arv);
void emOrdem(Arvore* arv);
void posOrdem(Arvore* arv);
Arvore* remover(Arvore *arv, int chave);
Arvore* libera(Arvore* arv);
int buscar( Arvore *arv, int chave);
int maior(int a, int b);
int maior_ramo(Arvore *arv);     
int contarNos(Arvore *arv);
#endif

