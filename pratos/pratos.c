#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//exercicio do lab de icc2, vamos receber pratos (tempo de preparo, prioridade de preparo, nome) e temos que ordenar
//primeiro usamos a prioridade como base, caso seja igual ordenamos por tempo (maior tempo primeiro)
//pra ordenar temos que comparar quicksort com bubblesort


/*daqui pra baixo é pra funcionar o timer*/
// Struct para o funcionamento do timer
typedef struct {
    clock_t start;
    clock_t end;
} Timer;

// Inicializa o timer
void start_timer(Timer *timer) {
    timer->start = clock();
}

// Para o timer e calcula o tempo decorrido
double stop_timer(Timer *timer) {
    timer->end = clock();
    return ((double) (timer->end - timer->start)) / CLOCKS_PER_SEC;
}

void imprimeTempoDeExecucao(double tempo){
    printf(" %f segundos\n", tempo);
}
/*daqui pra frente é o codigo de vdd*/


typedef struct prato_{
    int prep, prior; //tempo de preparaçao, ordem de prioridade
    char *nome; //nome do prato
}PRATO;

//quicksort pra ordenar por prioridade
void quicksortprior(PRATO *vet, int esq, int dir) { //vetor a ser ordenado, esquerda (começo) do vet, direita (fim) do vet
    int i = esq, j = dir, x = vet[(esq + dir) / 2].prior; //auxiliares
    PRATO y;

    while(i <= j){ 
        while(vet[i].prior < x && i < dir) i++;
        while(vet[j].prior > x && j > esq) j--;
        if(i <= j){
            y = vet[i];
            vet[i] = vet[j];
            vet[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > esq) quicksortprior(vet, esq, j);
    if(i < dir) quicksortprior(vet, i, dir);
    
    return;
}

//quicksort pra ordenar por tempo de preparo
void quicksortprep(PRATO *vet, int esq, int dir) { //vetor a ser ordenado, esquerda (começo) do vet, direita (fim) do vet
    int i = esq, j = dir, x = vet[(esq + dir) / 2].prep; //auxiliares
    PRATO y;

    while(i <= j){ 
        while(vet[i].prep > x && i < dir) i++; //aqui e na linha de baixo muda a logica de comparar pq a ordenaçao dos repetidos é ao contrario
        while(vet[j].prep < x && j > esq) j--; //ao inves de ser <x em cima e >x aqui fica o contrario
        if(i <= j){
            y = vet[i];
            vet[i] = vet[j];
            vet[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > esq) quicksortprep(vet, esq, j);
    if(i < dir) quicksortprep(vet, i, dir);
    
    return;
}

//bubblesort pra ordenar por prioridade
void bubblesortprior(PRATO *vetor, int esq, int dir){
    PRATO aux;

    for(int i = dir; i > esq; i--){
        for(int j = esq; j < i; j++){
            if(vetor[j].prior > vetor[j + 1].prior){
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }

    return;
}

//bubblesort pra ordenar por tempo de preparo
void bubblesortprep(PRATO *vetor, int esq, int dir){
    PRATO aux;

    for(int i = dir; i > esq; i--){
        for(int j = esq; j < i; j++){
            if(vetor[j].prep < vetor[j + 1].prep){ //aqui muda a logica pq a ordenaçao dos repetidos é ao contrario (muda > pra <)
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }

    return;
}

void buscarepquick(PRATO *vet, int tam){ //funçao pra buscar repetiçoes de prioridade (aí ordeno os repetidos por preparo em quicksort)
    int aux, comeco;
    for(int i = 0; i < tam; i++){
        aux = vet[i].prior;
        if(vet[i + 1].prior == aux){ //se o proximo do vetor tem mesma prioridade
            comeco = i; //marco onde fica o primeiro com a prioridade que estou analisando
            i++; 
            while(vet[i + 1].prior == aux){ //enquanto o valor no vetor continuar o mesmo que eu guardei
                i++; //incremento a cada um igual que encontro
            }
            quicksortprep(vet, comeco, i); //chamo o sort com o tanto certo de coisa que quero arrumar
        }
    }
    return;
}

void buscarepbubble(PRATO *vet, int tam){ //mesma coisa de cima mas pra ordenar os repetidos por bubblesort
    int aux, comeco;
    for(int i = 0; i < tam; i++){
        aux = vet[i].prior;
        if(vet[i + 1].prior == aux){ 
            comeco = i; 
            i++; 
            while(vet[i + 1].prior == aux){ 
                i++; 
            }
            bubblesortprep(vet, comeco, i - 1); 
        }
    }
    return;
}

//printa um vetor
void printa(PRATO *vet, int tam){
    for(int i = 0; i < tam; i++) printf("%s\n", vet[i].nome);
    return;
}

int main(void){
    Timer timer;
    int n;
    scanf("%d", &n); //numero de linhas de entrada
    PRATO *vet = malloc(sizeof(PRATO) * n);

    for(int i = 0; i < n; i++){
        vet[i].nome = malloc(sizeof(char) * 50);
        scanf(" %d %d %s", &vet[i].prior, &vet[i].prep, vet[i].nome);
        vet[i].nome = realloc(vet[i].nome, sizeof(char) * (strlen(vet[i].nome) + 1));
    }

    printf("numero de entradas: %d\n", n);
    start_timer(&timer);
    quicksortprior(vet, 0, n-1);
    buscarepquick(vet, n);
    printf("execuçao do quicksort:");
    imprimeTempoDeExecucao(stop_timer(&timer));

    printf("\n");
    printa(vet, n); //escolhi printar depois do quicksort pq o bubble nao aguenta todos os casos (aí não printa a saída)
    printf("\n");

    start_timer(&timer);
    bubblesortprior(vet, 0, n-1);
    buscarepbubble(vet, n);
    printf("execuçao do bubblesort:");
    imprimeTempoDeExecucao(stop_timer(&timer));
    
    return 0;
}

//tive que repetir uns par de coisa pra fazer dar tanto pelo bubblesort quanto pelo quicksort, aí o negocio ficou meio grande
//maaas no geral nao é nada complicadissimo, ta ate de boa. repete muita ideia la nas funções