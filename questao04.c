#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "TAD-arvores.h"
#include "TAD-avl.h"
#include "TAD-tempo.h"

/* =====================================================================
   Questao 04 - Comparacao entre Arvore AVL e Arvore Binaria de Pesquisa
   ===================================================================== */

#define NUM_ELEMENTOS 1000000
#define NUM_EXECUCOES 10
#define NUM_CONSULTAS 30

/* -----------------------------------------------------------------------
   Funcoes auxiliares para a BST (inserção e busca iterativas,
   altura via BFS e liberação iterativa para evitar stack overflow)
   ----------------------------------------------------------------------- */

/* Inserção iterativa na BST */
Arvore* inserirBST(Arvore* arv, int chave){
	Arvore* novo = (Arvore*)malloc(sizeof(Arvore));
	novo->info = chave;
	novo->esq = NULL;
	novo->dir = NULL;

	if(arv == NULL) return novo;

	Arvore* atual = arv;
	while(1){
		if(chave < atual->info){
			if(atual->esq == NULL){ atual->esq = novo; return arv; }
			atual = atual->esq;
		}else{
			if(atual->dir == NULL){ atual->dir = novo; return arv; }
			atual = atual->dir;
		}
	}
}

/* Busca iterativa na BST */
int buscarBST(Arvore *arv, int chave){
	Arvore* atual = arv;
	while(atual != NULL){
		if(chave == atual->info) return 1;
		if(chave < atual->info) atual = atual->esq;
		else atual = atual->dir;
	}
	return 0;
}

/* Altura da BST via BFS iterativo */
int alturaBST(Arvore *arv){
	if(arv == NULL) return 0;

	int capacidade = NUM_ELEMENTOS;
	Arvore **fila = (Arvore**)malloc(capacidade * sizeof(Arvore*));
	int frente = 0, tras = 0;
	int altura = 0;

	fila[tras++] = arv;
	while(frente < tras){
		int tamanhoNivel = tras - frente;
		altura++;
		int i;
		for(i = 0; i < tamanhoNivel; i++){
			Arvore *no = fila[frente++];
			if(no->esq) fila[tras++] = no->esq;
			if(no->dir) fila[tras++] = no->dir;
		}
	}
	free(fila);
	return altura;
}

/* Liberação iterativa da BST */
Arvore* liberarBST(Arvore* arv){
	if(arv == NULL) return NULL;

	Arvore **pilha = (Arvore**)malloc(NUM_ELEMENTOS * sizeof(Arvore*));
	int topo = 0;

	pilha[topo++] = arv;
	while(topo > 0){
		Arvore *no = pilha[--topo];
		if(no->esq) pilha[topo++] = no->esq;
		if(no->dir) pilha[topo++] = no->dir;
		free(no);
	}
	free(pilha);
	return NULL;
}

/* -----------------------------------------------------------------------
   Programa Principal
   ----------------------------------------------------------------------- */
int main(){
	struct timespec inicio, fim;
	int i, j, k;

	setlocale(LC_ALL, "Portuguese");

	int *numeros = (int*)malloc(NUM_ELEMENTOS * sizeof(int));
	if(numeros == NULL){
		printf("Erro ao alocar memoria para o vetor de numeros.\n");
		return 1;
	}

	int chavesBusca[NUM_CONSULTAS];

	printf("================================================================\n");
	printf("  Questao 04 - Comparacao: Arvore AVL  vs  Arvore Binaria (BST)\n");
	printf("  Elementos: %d | Execucoes: %d | Consultas: %d\n",
	       NUM_ELEMENTOS, NUM_EXECUCOES, NUM_CONSULTAS);
	printf("================================================================\n\n");

	/* Gerar numeros aleatorios UMA vez (mesmos valores em todas as execucoes) */
	srand(42);
	for(i = 0; i < NUM_ELEMENTOS; i++){
		numeros[i] = ((rand() << 15) | rand()) % 10000000;
	}

	/* Gerar chaves de busca: 15 existentes + 15 aleatorias */
	for(i = 0; i < 15; i++){
		chavesBusca[i] = numeros[rand() % NUM_ELEMENTOS];
	}
	for(i = 15; i < NUM_CONSULTAS; i++){
		chavesBusca[i] = ((rand() << 15) | rand()) % 10000000;
	}

	double tempoTotalCriacaoBST = 0, tempoTotalCriacaoAVL = 0;
	double tempoTotalBuscaBST = 0, tempoTotalBuscaAVL = 0;

	printf("+-----------+----------------------+----------------------+------------+------------+\n");
	printf("| Execucao  |  Tempo Criacao BST   |  Tempo Criacao AVL   | Altura BST | Altura AVL |\n");
	printf("+-----------+----------------------+----------------------+------------+------------+\n");

	for(k = 0; k < NUM_EXECUCOES; k++){

		/* ---------- Criacao da BST ---------- */
		Arvore *bst = criarArvore();
		clock_gettime(CLOCK_REALTIME, &inicio);
		for(i = 0; i < NUM_ELEMENTOS; i++){
			bst = inserirBST(bst, numeros[i]);
		}
		clock_gettime(CLOCK_REALTIME, &fim);
		double tempoCriacaoBST = tempoDeExecucao(inicio, fim);

		/* ---------- Criacao da AVL ---------- */
		NoAVL *avl = criarAVL();
		clock_gettime(CLOCK_REALTIME, &inicio);
		for(i = 0; i < NUM_ELEMENTOS; i++){
			avl = inserirAVL(avl, numeros[i]);
		}
		clock_gettime(CLOCK_REALTIME, &fim);
		double tempoCriacaoAVL = tempoDeExecucao(inicio, fim);

		/* ---------- Alturas ---------- */
		int hBST = alturaBST(bst);
		int hAVL = alturaAVL(avl);

		tempoTotalCriacaoBST += tempoCriacaoBST;
		tempoTotalCriacaoAVL += tempoCriacaoAVL;

		printf("|   %2d      |  %14.6f seg  |  %14.6f seg  |     %4d   |     %4d   |\n",
		       k + 1, tempoCriacaoBST, tempoCriacaoAVL, hBST, hAVL);

		/* ---------- Busca na BST (30 consultas) ---------- */
		double tempoBuscaBST = 0;
		clock_gettime(CLOCK_REALTIME, &inicio);
		for(j = 0; j < NUM_CONSULTAS; j++){
			buscarBST(bst, chavesBusca[j]);
		}
		clock_gettime(CLOCK_REALTIME, &fim);
		tempoBuscaBST = tempoDeExecucao(inicio, fim);

		/* ---------- Busca na AVL (30 consultas) ---------- */
		double tempoBuscaAVL = 0;
		clock_gettime(CLOCK_REALTIME, &inicio);
		for(j = 0; j < NUM_CONSULTAS; j++){
			buscarAVL(avl, chavesBusca[j]);
		}
		clock_gettime(CLOCK_REALTIME, &fim);
		tempoBuscaAVL = tempoDeExecucao(inicio, fim);

		tempoTotalBuscaBST += tempoBuscaBST;
		tempoTotalBuscaAVL += tempoBuscaAVL;

		/* Liberar memoria das arvores */
		bst = liberarBST(bst);
		avl = liberarAVL(avl);
	}

	printf("+-----------+----------------------+----------------------+------------+------------+\n\n");

	double mediaCriacaoBST = tempoTotalCriacaoBST / NUM_EXECUCOES;
	double mediaCriacaoAVL = tempoTotalCriacaoAVL / NUM_EXECUCOES;
	double mediaBuscaBST   = mediaTempo30(tempoTotalBuscaBST / NUM_EXECUCOES);
	double mediaBuscaAVL   = mediaTempo30(tempoTotalBuscaAVL / NUM_EXECUCOES);

	printf("================================================================\n");
	printf("                     RESUMO DOS RESULTADOS\n");
	printf("================================================================\n\n");

	printf("--- Tempo medio de CRIACAO (media de %d execucoes) ---\n", NUM_EXECUCOES);
	printf("  BST: %.6f segundos\n", mediaCriacaoBST);
	printf("  AVL: %.6f segundos\n", mediaCriacaoAVL);
	printf("\n");

	printf("--- Tempo total de BUSCA (%d consultas x %d execucoes) ---\n",
	       NUM_CONSULTAS, NUM_EXECUCOES);
	printf("  BST total: %.6f segundos\n", tempoTotalBuscaBST);
	printf("  AVL total: %.6f segundos\n", tempoTotalBuscaAVL);
	printf("\n");

	printf("--- Tempo medio por CONSULTA (media de %d consultas) ---\n", NUM_CONSULTAS);
	printf("  BST: %.9f segundos\n", mediaBuscaBST);
	printf("  AVL: %.9f segundos\n", mediaBuscaAVL);
	printf("\n");

	printf("================================================================\n");

	/* Detalhamento das 30 consultas (ultima execucao recriada) */
	printf("\n--- Detalhamento das %d consultas (ultima execucao recriada) ---\n\n", NUM_CONSULTAS);

	Arvore *bstFinal = criarArvore();
	NoAVL *avlFinal = criarAVL();
	for(i = 0; i < NUM_ELEMENTOS; i++){
		bstFinal = inserirBST(bstFinal, numeros[i]);
		avlFinal = inserirAVL(avlFinal, numeros[i]);
	}

	double somaDetBST = 0, somaDetAVL = 0;

	printf("+----------+------------+----------------------+----------------------+\n");
	printf("| Consulta |   Chave    |    Tempo BST (seg)   |    Tempo AVL (seg)   |\n");
	printf("+----------+------------+----------------------+----------------------+\n");

	for(j = 0; j < NUM_CONSULTAS; j++){
		clock_gettime(CLOCK_REALTIME, &inicio);
		buscarBST(bstFinal, chavesBusca[j]);
		clock_gettime(CLOCK_REALTIME, &fim);
		double tBST = tempoDeExecucao(inicio, fim);

		clock_gettime(CLOCK_REALTIME, &inicio);
		buscarAVL(avlFinal, chavesBusca[j]);
		clock_gettime(CLOCK_REALTIME, &fim);
		double tAVL = tempoDeExecucao(inicio, fim);

		somaDetBST += tBST;
		somaDetAVL += tAVL;

		printf("|    %2d    | %9d  |    %14.9f  |    %14.9f  |\n",
		       j + 1, chavesBusca[j], tBST, tAVL);
	}

	printf("+----------+------------+----------------------+----------------------+\n");
	printf("|  TOTAL   |     -      |    %14.9f  |    %14.9f  |\n", somaDetBST, somaDetAVL);
	printf("|  MEDIA   |     -      |    %14.9f  |    %14.9f  |\n",
	       mediaTempo30(somaDetBST), mediaTempo30(somaDetAVL));
	printf("+----------+------------+----------------------+----------------------+\n");

	/* Liberar memoria */
	liberarBST(bstFinal);
	liberarAVL(avlFinal);
	free(numeros);

	return 0;
}
