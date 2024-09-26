#include <stdio.h>
#include <stdlib.h>

//implementação do algoritmo do quicksort, nada mais nada menos

void quicksort(int *vet, int esq, int dir) { //vetor a ser ordenado, esquerda (começo) do vet, direita (fim) do vet
    int i = esq, j = dir, x = vet[(esq + dir) / 2], y; //auxiliares

    while(i <= j){ //paia de explicar, fica a cargo do leitor
        while(vet[i] < x && i < dir) i++;
        while(vet[j] > x && j > esq) j--;
        if(i <= j){
            y = vet[i];
            vet[i] = vet[j];
            vet[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > esq) quicksort(vet, esq, j);
    if(i < dir) quicksort(vet, i, dir);
    
    return;
}

int main(void){
    int *vet = malloc(sizeof(int) * 11); //vetor de tamanho 11

    for(int i = 0; i < 11; i++){ 
        scanf(" %d", &vet[i]);
    }

    quicksort(vet, 0, 10);
    
    for(int i = 0; i < 11; i++){
        printf("%d ", vet[i]);
    }

    return 0;
}