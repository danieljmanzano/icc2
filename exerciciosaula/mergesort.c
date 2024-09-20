#include <stdio.h>
#include <stdlib.h>

//aplicando algoritmo do mergesort (nossa essa eu nao ia saber obrigado por avisar daniel)
//nao deduzi a logica inteira nao, o sort (função mergesort aqui embaixo) foi ok mas tentei enterder o merge pela internet
void merge(int *v, int *v2, int i, int m, int f){
    int z, i1 = i, i2 = m + 1; //auxiliares pro negocio dar bom

    for(z = i; z <= f; z++) v2[z] = v[z]; //copio o v em um v2 auxiliar
    z = i;

    while(i1 <= m && i2 <= f) { //enquanto o a primeira metade nao tiver sido inteiramente percorrida/arrumada && a segunda metade tambem nao
        if(v2[i1] <= v2[i2]) v[z++] = v2[i1++]; //vai arrumando aí
        else v[z++] = v2[i2++]; //aqui tambem
    }

    while(i1 <= m) v[z++] = v2[i1++]; //poe a primeira metade organizada no v
    while(i2 <= f) v[z++] = v2[i2++]; //poe a segunda metade organizada no v
}

void mergesort(int *v, int *v2, int i, int f){ //o v2 é só um auxiliar que vou usar pro merge, pode ignorar aqui por enquanto
    if(i >= f) return;

    int m = (i + f) / 2; //fico dividindo o vetor (obs.: funciona pra tamanhos impares tambem, nao precisa se preocupar)

    mergesort(v, v2, i, m); //faço da metade pra tras
    mergesort(v, v2, m + 1, f); //faço da metade pra frente

    if(v[m] <= v[m + 1]) return; //se isso for vdd quer dizer que ta ordenado e pode vorta 

    merge(v, v2, i, m, f); //como a função é recursiva só vai pegar depois de separar tudo 
}



int main(void){
    int tam;

    printf("escreva o tamanho do vetor:");
    scanf("%d", &tam);

    int *vet = malloc(sizeof(int) * tam);
    int *vet2 = malloc(sizeof(int) * tam);

    printf("digite os numeros no seu vetor:");
    for(int i = 0; i < tam; i++) scanf(" %d", &vet[i]);

    mergesort(vet, vet2, 0, tam - 1);

    printf("seu vetor ordenado por mergesort:");
    for(int i = 0; i < tam; i++) printf("%d ", vet[i]);

    return 0; 
}
