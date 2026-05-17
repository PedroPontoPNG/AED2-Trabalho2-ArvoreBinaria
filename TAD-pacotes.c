#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TAD-pacotes.h"

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

    sprintf(p.dados, "Pacote%d", id);

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