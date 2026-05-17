/*Definindo o tipoNo*/
typedef struct tipoNo {
    int dado;
    struct tipoNo *prox;
} tipoNo;

/*Definindo o tipoLista*/
typedef struct tipoLista {
    tipoNo *prim;
    int tamanho;
} tipoLista;

extern int vetor[];
extern const int N;

double tempoDeExecucao(struct timespec inicio, struct timespec fim);
double mediaTempo30(double tempo);