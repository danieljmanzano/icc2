#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//nao é exercicio nem nada, só comparando os dois sort

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

//pra mergesort
void merge(int *v, int *v2, int i, int m, int f){
    int z, i1 = i, i2 = m + 1; 

    for(z = i; z <= f; z++) v2[z] = v[z]; //copio o v em um v2 auxiliar
    z = i;

    while(i1 <= m && i2 <= f) { //enquanto o a primeira metade nao tiver sido inteiramente percorrida/arrumada && a segunda metade tambem nao
        if(v2[i1] <= v2[i2]) v[z++] = v2[i1++]; 
        else v[z++] = v2[i2++]; 
    }

    while(i1 <= m) v[z++] = v2[i1++]; //poe a primeira metade organizada no v
    while(i2 <= f) v[z++] = v2[i2++]; //poe a segunda metade organizada no v

    return;
}

void mergesort(int *v, int i, int f){ 
    if(i >= f) return;

    int m = (i + f) / 2; //fico dividindo o vetor

    mergesort(v, i, m); //faço da metade pra tras
    mergesort(v, m + 1, f); //faço da metade pra frente

    if(v[m] <= v[m + 1]) return; //se isso for vdd quer dizer que ta ordenado e pode voltar
    int *v2 = malloc(sizeof(int) * (f + 1));
    merge(v, v2, i, m, f); //como a função é recursiva só vai pegar depois de separar tudo 
}

//pra heapsort
void heapify(int *vet, int n, int i){ 
    int maior = i; //inicializa o maior como raiz
    int esq = 2 * i + 1; //indice do filho à esquerda
    int dir = 2 * i + 2; //indice do filho à direita

    if(esq < n && vet[esq] > vet[maior]) maior = esq; //se o filho à esquerda for maior que a raiz

    if(dir < n && vet[dir] > vet[maior]) maior = dir; //se o filho à direita for o maior até agora


    if(maior != i){ //se o maior nao for a raiz
        int aux = vet[i];
        vet[i] = vet[maior];
        vet[maior] = aux;

        heapify(vet, n, maior); //recursão pra subarvore
    }

    return;
}

void heapsort(int *vet, int n){
    for(int i = n / 2 - 1; i >= 0; i--) heapify(vet, n, i); //constrói heap

    for(int i = n - 1; i > 0; i--){ //vai mexendo no que tem na heap
        int aux = vet[0]; //move a raiz atual pro fim
        vet[0] = vet[i];
        vet[i] = aux;

        heapify(vet, i, 0); //reorganiza heap
    }

    return;
}


//função para gerar um numero aleatorio (para os casos teste)
void gerarvetor(int *vet, int n){
    for(int i = 0; i < n; i++) vet[i] = rand() % 100000;
    return;
}

//como vou ordenar duas vezes, clono o vetor
int *clonavetor(int *vet, int n){
    int *vet2 = malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) vet2[i] = vet[i];
    return vet2;
}

int main(void){
    Timer timer1, timer2;
    int n; //tamanho do vetor
    scanf("%d", &n);
    int *vet = malloc(sizeof(int) * n);
    gerarvetor(vet, n);
    int *vet2 = clonavetor(vet, n);

    printf("numero de entradas: %d\n", n);

    start_timer(&timer1);
    heapsort(vet, n);
    printf("execução do heapsort: ");
    imprimeTempoDeExecucao(stop_timer(&timer1));

    start_timer(&timer2);
    mergesort(vet2, 0, n - 1);
    printf("execução do mergesort: ");
    imprimeTempoDeExecucao(stop_timer(&timer2));

    return 0;
}