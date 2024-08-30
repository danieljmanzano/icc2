#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*exercicio de lab de icc2, temos que comparar funções que fazem exponenciação tanto interativamente quanto recursivamente (divisao e conquista)*/
/*como os numeros vao ser imensos, temos que usar só os ultimos 4 digitos (por isso a infestação de % 10000 no código)*/    

/*daqui pra baixo é pra funcionar o timer*/
// Struct para o funcionamento do timer
    typedef struct{
    clock_t start;
    clock_t end;
}Timer;

// Inicializa o timer
void start_timer(Timer *timer){
    timer->start = clock();
}

// Para o timer e calcula o tempo decorrido
double stop_timer(Timer *timer){
    timer->end = clock();
    return ((double) (timer->end - timer->start)) / CLOCKS_PER_SEC;
}

void imprimeTempoDeExecucao(double tempo){
    printf("Tempo de execução: %f segundos\n", tempo);
}
/*daqui pra frente é o codigo de vdd*/



int expnormal(int n, int k){

    int aux = n;
    for(int i = 1; i < k; i++){
        n *= aux;
        if(n > 10000) n %= 10000;
    }

    return n;
}

int diveconqs(int n, int k){

    n %= 100000;
    if(k <= 1) return n % 10000;
    int aux = diveconqs(n, k/2) % 10000;

    if(k % 2) return(((aux * aux) % 10000) * n);
    else return((aux * aux) % 10000);
    
}

int main(void){
    int n, k;
    Timer timer;

    scanf(" %d %d", &n, &k);

    start_timer(&timer);
    printf("exp normal: %d\n", expnormal(n, k));
    imprimeTempoDeExecucao(stop_timer(&timer));

    start_timer(&timer);
    printf("divisao e conquista: %d\n", diveconqs(n, k));
    imprimeTempoDeExecucao(stop_timer(&timer));

    printf("%d\n", diveconqs(n, k) % 10000);
}