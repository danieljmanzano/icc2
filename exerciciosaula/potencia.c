#include <stdio.h>
#include <stdlib.h>

//exercicio pra treinar pra prova. tem que fazer uma função de O(logn) que calcula um numero a elevado a potencia de n

int pot(int a, int n){
    if(n == 1) return a;
    if(n == 0) return 1;

    if(!(n%2)){ //caso em que n é par
        int metade = pot(a, n/2);
        return metade * metade;
    }

    return a * pot(a, n - 1); //caso seja impar, chama isso aq e vira par, aí volta pra logica de cima
}

int main(void){
    int a, n;
    scanf("%d %d", &a, &n);
    printf("%d\n", pot(a, n));
    return 0;
}

//vai tomando filho pensei nisso sozinho 