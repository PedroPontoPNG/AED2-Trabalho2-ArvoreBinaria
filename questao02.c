#include <stdio.h>

#include "TAD-pacotes.h"

int main()
{
    ArvorePacotes *raiz;

    raiz = criarArvorePacotes();

    Pacote p1 = criarPacote(3, "  ");
    Pacote p2 = criarPacote(1, "Wi-");
    Pacote p3 = criarPacote(2, "fi");
    Pacote p4 = criarPacote(4, "Ral");
    Pacote p5 = criarPacote(5, "ph!");
    Pacote p6 = criarPacote(6, " ");

    Pacote p7 = gerarPacoteAutomatico(7);

    raiz = inserirPacote(raiz, p1);
    raiz = inserirPacote(raiz, p2);
    raiz = inserirPacote(raiz, p3);
    raiz = inserirPacote(raiz, p4);
    raiz = inserirPacote(raiz, p5);
    raiz = inserirPacote(raiz, p6);

    printf("\nPACOTES EM ORDEM:\n\n");

    emOrdemPacotes(raiz);

    FILE *fp;

    fp = fopen("arquivo_final.txt", "w");

    salvarArquivo(raiz, fp);

    fclose(fp);

    liberarArvorePacotes(raiz);

    return 0;
}