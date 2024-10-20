#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "operacoes.h"

//exercicio de lab de icc2
//temos que fazer duas funções para multiplicar strings numericas (uma usando multiplicaçao normal e a outra usando o algoritmo de karatsuba)
//pra analisar as diferenças a gente usa esses negocio de medir o tempo e etc., mas o karatsuba que era pra ser mais rapido ta sendo mais lento pela alocaçao de memoria exagerada rsrs

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
    printf("Tempo de execução: %f segundos\n", tempo);
}


char* multiplicacao(const char* str1, const char* str2);

char* karatsuba(char* str1, char* str2);

int main(void){
    Timer timer;

    char *str1, *str2;

    str1 = malloc(sizeof(char) * 100001);
    str2 = malloc(sizeof(char) * 100001);
    scanf(" %s", str1);
    scanf(" %s", str2);
    str1 = realloc(str1, sizeof(char) * (strlen(str1)+1));
    str2 = realloc(str2, sizeof(char) * (strlen(str2)+1));
    if(str1 == NULL || str2 == NULL){ 
        printf("erro na alocação");
        exit(1);
    }

    start_timer(&timer);
    printf("convencional: %s\n", multiplicacao(str1, str2));
    imprimeTempoDeExecucao(stop_timer(&timer));

    start_timer(&timer);
    printf("\nkaratsuba: %s\n", karatsuba(str1, str2));
    imprimeTempoDeExecucao(stop_timer(&timer));

    free(str1);
    free(str2);
    return 0;
}
