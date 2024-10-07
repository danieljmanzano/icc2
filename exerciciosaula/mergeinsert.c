#include <stdio.h>
#include <stdlib.h>

//exercicio de icc2. devo fazer um mergesort que divide um vetor de tamanho n ate que esteja em partes de tamanho k
//quando for de tamanho k devo fazer ordenação pelo insertion sort (que teoricamente é mais rapido pra vetores menores mesmo)
//aí quando todas as partes estão ordenadas faço uma ordenação final no vetor com insertion

void insertionsort(int *vet, int ini, int fim){
    for(int i = ini + 1; i <= fim; i++) {
        int aux = vet[i]; //pego uma posição
        int j = i - 1; //o j me vai percorrer todo o vetor comparando com a posição que peguei

        while(j >= ini && vet[j] > aux){ //troco toda vez que encontro algum no vetor 
            vet[j + 1] = vet[j]; //troco o da posição i com o i-1 basicamente
            j = j - 1; //ando pra tras 
        }
        vet[j + 1] = aux; 
    }

    return;
}

void mergesort(int *v, int i, int f, int k){ //o v2 é só um auxiliar que vou usar pro merge, pode ignorar aqui por enquanto
    if(f - i <= k){ //quando o tamanho do vetor divido for k eu chamo o insertion
        insertionsort(v, i, f);
        printa(v, i, f); //toda vez que chamo o insertion eu printo as coisas que ordenei no momento
        return; //aí como ja ordenou eu retorno
    }

    int m = (i + f) / 2; //fico dividindo o vetor (obs.: funciona pra tamanhos impares tambem, nao precisa se preocupar)

    mergesort(v, i, m, k); //faço da metade pra tras
    mergesort(v, m + 1, f, k); //faço da metade pra frente

    insertionsort(v, i, f); //quando as partes dele ja estao ordenadas chamo pra uma ultima ordenação geral
    return; 
}

void printa(int *vet, int ini, int fim){
    for(int i = ini; i <= fim; i++) printf("%d ", vet[i]);
    printf("\n");
    return;
}

int main(void){
    int n, k; //n é a quantidade de numeros no vetor e k é com quantos numeros vou chamar o insertion
    scanf("%d", &n);
    int *vet = malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) scanf(" %d", &vet[i]);
    scanf("%d", &k);

    mergesort(vet, 0, n - 1, k);
    printa(vet, 0, n - 1);

    free(vet);
    
    return 0;
}