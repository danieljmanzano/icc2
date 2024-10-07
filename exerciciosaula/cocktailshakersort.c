#include <stdio.h>
#include <stdlib.h>

//exercicio de icc2. tenho que implementar o cocktail shaker sort (um bubblesort modificado)

void troca(int *n1, int *n2){ //vou usar no algoritmo do sort aí
    int aux = *n1;
    *n1 = *n2;
    *n2 = aux;
    return;
}

void cssort(int *v, int n){ //o negocio é um bubble sort que vai de tras pra frente e dps da frente pra tras (complexidade de O(n²))
    for(int i = 1; i <= n / 2; i++){

        for(int j = i - 1; j < n - i; j++) //tras pra frente
            if(v[j] > v[j + 1]) troca(&v[j], &v[j + 1]);
            

        for(int j = n - i - 1; j >= i; j--) //frente pra tras
            if(v[j] < v[j - 1]) troca(&v[j], &v[j - 1]);

    }

    return;
}

void printa(int *v, int n){
    for(int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
    return;
}

int main(void){
    int n;
    scanf("%d", &n);
    int *vet = malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) scanf(" %d", &vet[i]);

    cssort(vet, n);
    printa(vet, n);

    free(vet);

    return 0;
}