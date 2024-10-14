#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//feito pelo daniel
//exercicio de lab de icc2. temos que ordenar cartas de baralho (truco) com o stoogesort (pior algoritmo possivel)
//curiosamente a carta tem mais de um dígito de numero/letra, aí tem que ordenar com base nisso tambem. depois disso ainda temos que ordenar no naipe
//como o stoogesort, alias, nao é estavel, quando ordeno por naipe muito provavelmente ele tira as cartas de ordem 
//assim, esse algoritmo é terrivel e nao deve ser usado quando compara com o outro da aula

typedef struct{
    char *naipe; //naipe é um caracter especial, funciona como uma string pra garantir que cabe aí
    char *num; //sim, o numero da carta é uma string
}carta;

int buscanaipe(char chave[]){ //vejo qual a posição do naipe (de 0 a 3)
    if(!strcmp("♦", chave)) return 0;
    else if(!strcmp("♠", chave)) return 1;
    else if(!strcmp("♥", chave)) return 2;
    else if(!strcmp("♣", chave)) return 3;
    exit (1); //se nao for nenhum dos naipe eu saio 
}

int buscaemseq(int seq[], int chave){ //função que busca a posição da chave no vetor sequencia (basicamente, retorna a posição do numero da carta na sequencia do baralho)
    for(int i = 0; i < 10; i++) 
        if(seq[i] == chave) return i; //retorna a posiçao da minha chave dentro do vetor sequencia
    exit (1); //caso nao tenha achado nao tem o que fazer, dou exit pq tem algo errado
}

void swap(carta *a, carta *b){
    carta temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void stoogesortnum(carta *vet, int i, int j, int seq[], int tam, int n){    
    int k, flag = 0;
    
    if(buscaemseq(seq, vet[i].num[0]) > buscaemseq(seq, vet[j].num[0]))
        swap(&vet[i], &vet[j]);
    else{
        for(int k = 1; k < tam; k++){ //vou analisar todos os digitos do numero da carta
            if(buscaemseq(seq, vet[i].num[k]) > buscaemseq(seq, vet[j].num[k])){
                swap(&vet[i], &vet[j]);
                flag = 1; //essa é pra ver se vou ter q analisar o naipe dps
                break;
            }
        }
        if(!flag){ //essa é pra se o numero foi todo igual e tenho que analisar o naipe
            if(buscanaipe(vet[i].naipe) > buscanaipe(vet[j].naipe))
                swap(&vet[i], &vet[j]);
        }
    }

    if((i + 1) >= j) return;

    k = (int)((j - i + 1) / 3);

    stoogesortnum(vet, i, j - k, seq, tam, n);
    stoogesortnum(vet, i + k, j, seq, tam, n);
    stoogesortnum(vet, i, j - k, seq, tam, n);
}

void printa(carta *vet, int n){
    for(int i = 0; i < n; i++) printf("%s %s\n", vet[i].naipe, vet[i].num);
    return;
}

int main(void){ 
    int n, tam; //n == numero de cartas, tam == tamanho do numero da carta (o numero da carta tem mais de um digito, nada ve)
    int seq[10] = {52, 53, 54, 55, 81, 74, 75, 65, 50, 51}; //a ordem convencional de baralho de truco so que ta tudo em ascii
    scanf("%d %d", &n, &tam);
    carta *cartas = malloc(sizeof(carta) * n);
    for(int i = 0; i < n; i++){ //pra entrada
        cartas[i].naipe = malloc(sizeof(carta) * 2);
        cartas[i].num = malloc(sizeof(cartas) * (n + 1));
        scanf(" %s %s", cartas[i].naipe, cartas[i].num);
    }
    
    stoogesortnum(cartas, 0, n - 1, seq, tam - 1, n);
    printa(cartas, n);

    return 0;
}