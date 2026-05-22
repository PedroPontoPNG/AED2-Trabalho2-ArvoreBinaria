#ifndef TAD_PACOTES_H
#define TAD_PACOTES_H

#include <stdio.h>

#define TAM_DADOS 100
#define MAX_TEXTO 5000
#define TAM_PACOTE 5
#define MAX_PACOTES 1000

typedef struct Pacote
{
    int id;
    char dados[TAM_DADOS];
} Pacote;

typedef struct noPacote
{
    Pacote pacote;
    struct noPacote *esq;
    struct noPacote *dir;
} ArvorePacotes;

ArvorePacotes *criarArvorePacotes();

ArvorePacotes *inserirPacote(
    ArvorePacotes *arv,
    Pacote p);

int buscarPacote(
    ArvorePacotes *arv,
    int id);

void emOrdemPacotes(
    ArvorePacotes *arv);

void liberarArvorePacotes(
    ArvorePacotes *arv);

Pacote criarPacote(
    int id,
    char dados[]);

Pacote gerarPacoteAutomatico(
    int id);

void imprimirPacote(
    Pacote p);

void salvarArquivo(
    ArvorePacotes *arv,
    FILE *fp);
// FUNÇÕES PARA ARQUIVOS QUESTAO02
void lerArquivo(
    char nomeArquivo[],
    char texto[]);

int dividirPacotes(
    char texto[],
    Pacote pacotes[]);
void embaralharPacotes(
    Pacote pacotes[],
    int n);
void mostrarPacotes(
    Pacote pacotes[],
    int n);
#endif