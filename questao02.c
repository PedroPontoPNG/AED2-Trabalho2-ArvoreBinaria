#include "TAD-pacotes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    char texto[MAX_TEXTO];

    Pacote pacotes[MAX_PACOTES];

    int quantidade;

    int i;

    ArvorePacotes *raiz;

    raiz = criarArvorePacotes();

    lerArquivo(
        "arquivo_inicial.txt",
        texto);

    printf("\nTEXTO ORIGINAL:\n\n");

    printf("%s\n", texto);

    quantidade =
        dividirPacotes(
            texto,
            pacotes);

    printf("\nPACOTES CRIADOS:\n\n");

    mostrarPacotes(
        pacotes,
        quantidade);

    embaralharPacotes(
        pacotes,
        quantidade);

    printf("\nPACOTES EMBARALHADOS:\n\n");

    mostrarPacotes(
        pacotes,
        quantidade);

    for (i = 0; i < quantidade; i++)
    {
        raiz =
            inserirPacote(
                raiz,
                pacotes[i]);
    }

    printf("\nPACOTES ORGANIZADOS:\n\n");

    emOrdemPacotes(raiz);

    FILE *fp;

    fp = fopen(
        "arquivo_reconstruido.txt",
        "w");

    salvarArquivo(
        raiz,
        fp);

    fclose(fp);

    printf(
        "\nArquivo reconstruido com sucesso.\n");

    liberarArvorePacotes(raiz);

    return 0;
}