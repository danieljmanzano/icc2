#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//feito pelo daniel
//exercicio de lab de icc2. temos que ordenar cartas de baralho (truco) com o stoogesort (pior algoritmo possivel)
//curiosamente a carta tem mais de um dígito de numero/letra, aí tem que ordenar primeiro pelo naipe e depois com base nisso 


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
    printf("tempo de execução: %f segundos\n", tempo);
}
/*daqui pra frente é o codigo de vdd*/


typedef struct{
    char *naipe; //naipe é um caracter especial, funciona como uma string pra garantir que cabe aí
    char *num; //sim, o numero da carta é uma string
}carta;

int buscanaipe(char chave[]){ //vejo qual a posição do naipe (de 0 a 3)
    if(!strcmp("♦", chave)) return 0;
    else if(!strcmp("♠", chave)) return 1;
    else if(!strcmp("♥", chave)) return 2;
    else if(!strcmp("♣", chave)) return 3;
    exit (1); //se nao for nenhum dos naipe eu saio 
}

int buscaemseq(int seq[], int chave){ //função que busca a posição da chave no vetor sequencia (basicamente, retorna a posição do numero da carta na sequencia do baralho)
    for(int i = 0; i < 10; i++) 
        if(seq[i] == chave) return i; //retorna a posiçao da minha chave dentro do vetor sequencia
    exit (1); //caso nao tenha achado nao tem o que fazer, dou exit pq tem algo errado
}

void swap(carta *a, carta *b){
    carta temp = *a;
    *a = *b;
    *b = temp;
    return;
}

int comparacarta(carta *vet, int i, int j, int seq[], int tam){ //aqui vou ver se preciso trocar duas cartas (1 é que tem que trocar, 0 não)
    if(buscanaipe(vet[i].naipe) > buscanaipe(vet[j].naipe)) return 1;
    else if(buscanaipe(vet[i].naipe) < buscanaipe(vet[j].naipe)) return 0;

    for(int cont = 0; cont <= tam; cont++){ //esse for é pra ver dentre os numeros se eu preciso trocar os numeros ou nao
        if(buscaemseq(seq, vet[i].num[cont]) > buscaemseq(seq, vet[j].num[cont])) //se for menor troca
            return 1;
        else if(buscaemseq(seq, vet[i].num[cont]) < buscaemseq(seq, vet[j].num[cont])) //se for maior nao
            return 0;
    }

    return 0; //por via das duvidas, se a carta for igual eu nao troco
}

void stoogesort(carta *vet, int i, int j, int seq[], int tam){ 
    if(comparacarta(vet, i, j, seq, tam))
        swap(&vet[i], &vet[j]);
    
    if((i + 1) >= j) return;

    int k = ((j - i + 1) / 3);

    stoogesort(vet, i, j - k, seq, tam);
    stoogesort(vet, i + k, j, seq, tam);
    stoogesort(vet, i, j - k, seq, tam);
}

void printa(carta *vet, int n){
    for(int i = 0; i < n; i++) printf("%s %s\n", vet[i].naipe, vet[i].num);
    return;
}

int main(void){ 
    Timer timer;
    int n, tam; //n == numero de cartas, tam == tamanho do numero da carta (o numero da carta tem mais de um digito, nada ve)
    int seq[10] = {52, 53, 54, 55, 81, 74, 75, 65, 50, 51}; //a ordem convencional de baralho de truco so que ta tudo em ascii
    scanf("%d %d", &n, &tam);
    carta *cartas = malloc(sizeof(carta) * n);
    for(int i = 0; i < n; i++){ //pra entrada
        cartas[i].naipe = malloc(sizeof(char) * 3);
        cartas[i].num = malloc(sizeof(char) * (tam + 1));
        scanf(" %s %s", cartas[i].naipe, cartas[i].num);
    }
    
    start_timer(&timer);
    stoogesort(cartas, 0, n - 1, seq, tam - 1);
    printa(cartas, n);
    imprimeTempoDeExecucao(stop_timer(&timer));

    return 0;
}