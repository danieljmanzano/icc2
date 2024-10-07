#include <stdio.h>
#include <stdlib.h>

//exercicio de icc2. temos que arrumar uma heap (minima, ou seja, decrescente) e com identação na saída (parte mais embaçada)

void heapmin(int *vet, int n, int i){
    int menor = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if(esq < n && vet[esq] < vet[menor]) menor = esq;
    

    if(dir < n && vet[dir] < vet[menor]) menor = dir;
    

    if (menor != i){
        int temp = vet[i];
        vet[i] = vet[menor];
        vet[menor] = temp;
        heapmin(vet, n, menor);
    }
    return;
}

void criaheapmin(int *vet, int n){
    for (int i = n / 2 - 1; i >= 0; i--) heapmin(vet, n, i);
    return;
}

void heapsort(int *vet, int n) {
    criaheapmin(vet, n);
    
    for (int i = n - 1; i > 0; i--){
        int temp = vet[0];
        vet[0] = vet[i];
        vet[i] = temp;
        heapmin(vet, i, 0);
    }

    return;
}

void printaheap(int *vet, int index, int ident, int n) {
    if(index >= n) return;

    for(int i = 0; i < ident; i++) printf("*"); //pra printar os * da identação certo
    
    if(!index) printf("%d\n", vet[index]); //caso seja o primeiro do vetor (index == 0) eu nao printo com o espaço antes
    else printf(" %d\n", vet[index]);

    printaheap(vet, 2 * index + 1, ident + 1, n);
    printaheap(vet, 2 * index + 2, ident + 1, n);

    return;
}

int main(void){
    int n;
    scanf("%d", &n);
    int *vetor = malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) scanf(" %d", &vetor[i]);

    printf("\n");
    printaheap(vetor, 0, 0, n); //heap antes
    printf("\n");
    heapsort(vetor, n);
    printaheap(vetor, 0, 0, n); //heap depois

    free(vetor);

    return 0;
}
