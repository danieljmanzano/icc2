#include <stdio.h>
#include <stdlib.h>

//exercicio de icc2. divido um vetor em "baldes" que contém numeros com tantos específicos de 1's quando analisados em binario (os numeros, alias, têm que ser ordenados)
//ex.: meu primeiro balde tem binarios com 1 unico numero 1, meu segundo tem numeros com 2 numero 1, meu terceiro tem numeros com 3... e vai
//entao, se tenho os numeros 1, 2, 3, 4 e 5, o primeiro balde tem 1, 2 e 4 (1, 10 e 100 em binario) e o segundo 3 e 5 (11 e 101)
//obs.: nao vi ajuda nenhuma em fazer a ordenação em baldes pq depois de tudo, de qualquer forma, vou ter que ordenar pro vetor final. talvez eu tenha feito errado, mas fiz do jeito que dava na minha cabesinha

typedef struct{ //essa struct facilita minha vida pra guardar tanto o numero em binario (como vetor) e o numero de digitos (tamanho) do binario
    int *vet;
    int tam;
}BIN;

void quicksort(int *vet, int esq, int dir) { //pra ordenar os baldes escolhi o quicksort mesmo
    int i = esq, j = dir, x = vet[(esq + dir) / 2], y; 

    while(i <= j){ 
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

BIN decimalprabin(int num){
    int tam = 32; //tamanho maximo de inteiro, 32 bits
    BIN bin;
    bin.vet = calloc(sizeof(int), tam); //vetor binario começa tudo 0
    if(bin.vet == NULL) exit (1);

    for(int i = 0; i < tam && num > 0; i++){ 
        bin.vet[i] = num % 2; //pega o resto da divisao por 2 do nosso numero e guarda no bin
        num /= 2; 
        if(!num) tam = i + 1; //quando o numero for 0 retorno o tamanho novo do bagulho
    }

    bin.vet = realloc(bin.vet, sizeof(int) * tam);
    bin.tam = tam;
    return bin;
}

int contauns(BIN bin, int tam){
    int num = 0;
    for(int i = 0; i < tam; i++)
        if(bin.vet[i]) num++; //vou pegando a quantidade de 1's que tem no meu binario

    return num;
}

void printa(int *vet, int tam){
    for(int i = 0; i < tam; i++) printf("%d ", vet[i]);
    printf("\n");
    return;
}

//funçao que vai contar o numero de 1's e printar por baldes (primeiro balde tem 1 numeros 1, segundo tem 2, terceiro 3... ate o balde de 32, que é o tanto de bits max pra int)
void contaeprinta(int *vet, int n, int uns){ //(vet == vetor original, n == tamanho do vet, uns == quantidade de 1's que to procurando)
    if(uns == 32){ //caso base
        quicksort(vet, 0, n - 1);
        printa(vet, n);
        return; //quando bater 32 (numero de bits maximo, entao numero maximo possivel de numeros 1) retorna
    }

    int *vet2 = malloc(sizeof(int) * n); //vet2 funciona como o balde
    int j = 0;
    for(int i = 0; i < n; i++){
        BIN bin = decimalprabin(vet[i]);
        if(contauns(bin, bin.tam) == uns){ //se o tanto de numeros 1 no meu vetor binario é o tanto de 1's que to analisando no momento
            vet2[j] = vet[i]; //guardo o numero no balde
            j++;
        }
    }

    if(j) quicksort(vet2, 0, j - 1); //ordena o balde (caso o j nao seja 0, ou seja, tem o que ordenar)
    if(j) printa(vet2, j); //printa aquele balde ordenado
    contaeprinta(vet, n, uns + 1); //chamo pro proximo balde 
    return;
}

int main(void){
    int quant; //numero de entradas
    scanf("%d", &quant);

    int *vet = malloc(sizeof(int) * quant); //guarda os numeros de entrada
    for(int i = 0; i < quant; i++) scanf(" %d", &vet[i]);
    contaeprinta(vet, quant, 1);
    
    return 0;
}