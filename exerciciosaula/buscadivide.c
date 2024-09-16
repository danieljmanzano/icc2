#include <stdio.h>
#include <stdlib.h>
//o exercicio é achar um numero dado que ta dentro de um vetor (ja ordenado) com uma funcao recursiva
//essa funcao fica dividindo o vetor no meio e vai procurar o numero na metade que tem teoricamente o valor mais proximo ao que voce ta procurando
//começarei eventualmente, esse .c é só pra eu nao esquecer

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
    int n;
    scanf("%d", &n);

    int vet[] = {1, 2, 3, 4, 5, 6, 7};
    printf("%d\n", buscabin(vet, 0, 6, n));
}