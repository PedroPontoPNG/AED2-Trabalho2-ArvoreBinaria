#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TAD-pacotes.h"
#include <time.h>

ArvorePacotes *criarArvorePacotes()
{
    return NULL;
}

Pacote criarPacote(int id, char dados[])
{
    Pacote p;

    p.id = id;

    strcpy(p.dados, dados);

    return p;
}

Pacote gerarPacoteAutomatico(int id)
{
    Pacote p;

    p.id = id;

    sprintf(p.dados, "%d", id);

    return p;
}

void imprimirPacote(Pacote p)
{
    printf("Pacote [%d] -> %s\n", p.id, p.dados);
}

ArvorePacotes *inserirPacote(
    ArvorePacotes *arv,
    Pacote p)
{
    if (arv == NULL)
    {
        arv = (ArvorePacotes *)malloc(sizeof(ArvorePacotes));

        arv->pacote = p;

        arv->esq = NULL;
        arv->dir = NULL;
    }
    else if (p.id < arv->pacote.id)
    {
        arv->esq = inserirPacote(arv->esq, p);
    }
    else if (p.id > arv->pacote.id)
    {
        arv->dir = inserirPacote(arv->dir, p);
    }
    else
    {
        printf("Pacote duplicado ignorado: %d\n", p.id);
    }

    return arv;
}

int buscarPacote(
    ArvorePacotes *arv,
    int id)
{
    if (arv == NULL)
    {
        return 0;
    }

    if (id < arv->pacote.id)
    {
        return buscarPacote(arv->esq, id);
    }
    else if (id > arv->pacote.id)
    {
        return buscarPacote(arv->dir, id);
    }
    else
    {
        return 1;
    }
}

void emOrdemPacotes(
    ArvorePacotes *arv)
{
    if (arv != NULL)
    {
        emOrdemPacotes(arv->esq);

        imprimirPacote(arv->pacote);

        emOrdemPacotes(arv->dir);
    }
}

void salvarArquivo(
    ArvorePacotes *arv,
    FILE *fp)
{
    if (arv != NULL)
    {
        salvarArquivo(arv->esq, fp);

        fprintf(fp, "%s", arv->pacote.dados);

        salvarArquivo(arv->dir, fp);
    }
}

void liberarArvorePacotes(
    ArvorePacotes *arv)
{
    if (arv != NULL)
    {
        liberarArvorePacotes(arv->esq);

        liberarArvorePacotes(arv->dir);

        free(arv);
    }
}

// FUNÇÕES PARA ARQUIVOS QUESTAO02

void lerArquivo(
    char nomeArquivo[],
    char texto[])
{
    FILE *fp;

    fp = fopen(nomeArquivo, "r");

    if (fp == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    fgets(texto, MAX_TEXTO, fp);

    fclose(fp);
}

int dividirPacotes(
    char texto[],
    Pacote pacotes[])
{
    int i;
    int id = 1;

    int tamanho = strlen(texto);

    char parte[TAM_PACOTE + 1];

    for (i = 0; i < tamanho; i += TAM_PACOTE)
    {
        strncpy(
            parte,
            &texto[i],
            TAM_PACOTE);

        parte[TAM_PACOTE] = '\0';

        pacotes[id - 1] =
            criarPacote(id, parte);

        id++;
    }

    return id - 1;
}

void embaralharPacotes(
    Pacote pacotes[],
    int n)
{
    int i;
    int j;

    Pacote temp;

    srand(time(NULL));

    for (i = n - 1; i > 0; i--)
    {
        j = rand() % (i + 1);

        temp = pacotes[i];

        pacotes[i] = pacotes[j];

        pacotes[j] = temp;
    }
}
void mostrarPacotes(
    Pacote pacotes[],
    int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        imprimirPacote(pacotes[i]);
    }
}