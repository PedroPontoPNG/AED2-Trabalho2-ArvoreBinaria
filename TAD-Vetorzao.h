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

/*Vetor global acessível entre módulos*/
extern int vetor[];
extern const int N;


/*Busca Binária no Vetor Ordenado*/
long int buscaBinaria(int chave);

void inserirNoVetor(int i,int chave);



int sortearElemento();
int sortearElementoNoVetor();
void quicksort(int vet[], int inicio, int fim);
int particiona(int vet[], int inicio, int fim);
void trocar(int* a, int* b);