#include <stdio.h>
#include <stdlib.h>

/*o exercicio é achar um numero dado que ta dentro de um vetor (ja ordenado) com uma funcao recursiva / fiz tb funçao que busca onde inserir algo*/
/*o problema é basico, mas o legal aqui é que esse tipo de busca é muuuuito bom (complexidade O(logn), log na base 2)*/
/*principal motivo de fazer isso aq é pra se for usar pra outros exercicios, é bem util ja ter esses algoritmos implementados pra usar dps*/

int buscabin(int *vet, int i, int f, int busca){ //busca um numero ja presente dentro do vetor (retorna a posicao dele)
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

int buscaBinInsercIter(int *vet, int esquerda, int direita, int chave){ //busca uma posiçao para inserir um numero no vetor iterativamente

    while(esquerda <= direita){
        int meio = esquerda + (direita - esquerda) / 2;

        if(vet[meio] == chave){
            return meio; //se ja tem a chave eu retorno a posição dela
        }else if (vet[meio] < chave){
            esquerda = meio + 1; //procura na direita
        }else {
            direita = meio - 1; //procura na esquerda
        }
    }

    return esquerda; //onde tenho que inserir
}

int buscaBinInsercRec(int *vet, int esquerda, int direita, int chave){ //busca uma posiçao para inserir um numero no vetor recursivamente
    if(esquerda > direita){
        return esquerda; //se chegou aqui quer dizer que achei a posiçao pra inserir (esquerda passando a direita)
    }

    int meio = esquerda + (direita - esquerda) / 2;

    if(vet[meio] == chave){
        return meio; //se ja tem a chave eu retorno a posição dela
    }else if(vet[meio] < chave){
        return buscaBinInsercRec(vet, meio + 1, direita, chave); //procura na direita
    }else{
        return buscaBinInsercRec(vet, esquerda, meio - 1, chave); //procura na esquerda
    }
}

void insereEprinta(int *vet, int tam, int pos, int chave){ //depois de achar a posiçao com alguma das funçoes de antes eu chamo isso aq pra inserir
    vet = realloc(vet, sizeof(int) * (tam + 1));

    for(int i = tam; i >= pos; i--){
        vet[i] = vet[i - 1];
    }
    vet[pos] = chave;

    for(int i = 0; i < tam + 1; i++) printf("%d ", vet[i]); //printo dps tb
    return;
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

    if(buscabin(vet, 0, tam - 1, n) != -1) printf("o indice do numero no vetor é %d\n", buscabin(vet, 0, tam - 1, n));
    else printf("posiçao nao encontrada\n"); //caso volte -1 da funcao é que eu nao achei o q tava procurando

    printf("escreva o numero que quer inserir ");
    scanf("%d", &n);

    //int pos = buscaBinInsercIter(vet, 0, tam - 1, n);
    int pos = buscaBinInsercRec(vet, 0, tam - 1, n);
    printf("seu vetor final: ");
    insereEprinta(vet, tam, pos, n);

    free(vet);
    return 0;
}

//ta tudo funcionando ok