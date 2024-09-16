#include <stdio.h>
#include <stdlib.h>

/*o exercicio é achar um numero dado que ta dentro de um vetor (ja ordenado) com uma funcao recursiva*/
/*o problema é basico, mas o legal aqui é que esse tipo de busca é muuuuito bom (complexidade O(logn), log na base 2)*/
/*vou reutilizar o algoritmo em exercicio de alg*/

int buscabin(int *vet, int i, int f, int busca){
    int m = (i + f) / 2;

    if(i > f) return -1; //caso nao tenha achado vai chegar aqui em algum momento
    if(vet[m] == busca) return m;

    if(vet[m] < busca){
        return buscabin(vet, m + 1, f, busca);
    }else if(vet[m] > busca){
        return buscabin(vet, i, m - 1, busca);
    }
    
    return -1;  //esse return nem faz sentido, só coloquei pra nao dar warning depois
}

int main(void){
    int tam, n;
    printf("escreva o tamanho do seu vetor ");
    scanf("%d", &tam);
    int *vet = malloc(sizeof(int) * tam); 

    printf("escreva seu vetor (tem de ser ordenado!) ");
    for(int i = 0; i < tam; i++) scanf(" %d", &vet[i]);

    printf("escreva o numero que quer buscar ");
    scanf("%d", &n);

    printf("o indice do numero no vetor é %d\n", buscabin(vet, 0, tam - 1, n));
}