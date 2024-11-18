#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <time.h>

//exercicio de lab de icc2. 
//temos que comparar duas implementaçoes diferentes de algoritmos que veem a maxima subsequencia crescente de um vetor (que tem uma funçao hash envolvida)
//fiz um usando tabela hash e o fernando fez logo os dois que precisava no problema
//aqui eu comparo o que nao usa hash dele (so ordenaçao) com o meu de hash. no msc.c eu comparo as duas implementaçao dele mesmo

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
    printf("%f segundos\n", tempo);
}
/*daqui pra frente é o codigo de vdd*/

int main(void){
    Timer timer1, timer2;
    int n, valor;
    scanf("%d", &n);
    int *vet = malloc(sizeof(int) * n);
    TABELA *t = inicializa();
    
    for(int i = 0; i < n; i++){
        scanf("%d", &valor);
        vet[i] = valor;
        insere(t, valor);
    }
    

    printf("numero de entradas: %d\n", n);

    //pra testar com hashmap
    start_timer(&timer1);
    printf("execuçao por hashmap: ");
    msc(t);
    imprimeTempoDeExecucao(stop_timer(&timer1));

    //pra testar o algoritmo do fernando
    start_timer(&timer2);
    printf("execuçao por ordenaçao: ");
    maximaSubsequenciaSort(vet, n);
    imprimeTempoDeExecucao(stop_timer(&timer2));
    
    return 0;
}