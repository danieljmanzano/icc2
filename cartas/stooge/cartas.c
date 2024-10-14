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

void stoogesortnaipe(carta *vet, int i, int j){ //vai valer pra ordenar primeiro os naipes
    int k;
    carta temp;           

    if(buscanaipe(vet[i].naipe) > buscanaipe(vet[j].naipe)){ //se o naipe de vet[i] é maior que de vet[j], tenho que inverter
        temp = vet[i];
        vet[i] = vet[j];
        vet[j] = temp;
    }

    if((i + 1) >= j) return;

    k = (int)((j - i + 1) / 3);

    stoogesortnaipe(vet, i, j - k);
    stoogesortnaipe(vet, i + k, j);
    stoogesortnaipe(vet, i, j - k);
}

void stoogesortnum(carta *vet, int i, int j, int seq[], int dig, int n){ //dig é qual a posição do digito que to analisando (tem que ser um digito de cada vez, ent vou chamar dps pros outros talvez)
    if(dig == -1) return stoogesortnaipe(vet, 0 , n - 1); //caso base, quando bate o digito -1 quer dizer que ordenei todos e agora tem que ser por naipe
    
    int k;
    carta temp;

    int veti = buscaemseq(seq, vet[i].num[dig]); //busca a posição do digito do numero do vet[i] no vetor seq 
    int vetj = buscaemseq(seq, vet[j].num[dig]); //mesma coisa de cima
    if(veti > vetj){
        temp = vet[i];
        vet[i] = vet[j];
        vet[j] = temp;
    }

    if((i + 1) >= j) return;

    k = (int)((j - i + 1) / 3);

    stoogesortnum(vet, i, j - k, seq, dig, n);
    stoogesortnum(vet, i + k, j, seq, dig, n);
    stoogesortnum(vet, i, j - k, seq, dig, n);
    stoogesortnum(vet, i, j, seq, dig - 1, n); //quando faço o sort com o tanto de digito atual, chamo denovo pro proximo digito
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