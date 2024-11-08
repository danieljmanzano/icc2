#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

typedef struct no_{
    int num;
    struct no_ *prox;
}NO;

typedef struct tabela_{
    NO *tabela[TAM];
    int tam;
}TABELA;

int hash(int n){
    return n % TAM;
}

TABELA *inicializa(){
    TABELA *t = malloc(sizeof(TABELA));
    if(t == NULL) exit (1); //caso dê erro de alocação

    for(int i = 0; i < TAM; i++){ //inicializar os nós da tabela
        t->tabela[i] = malloc(sizeof(NO));
        t->tabela[i]->num = VAZIO;
        t->tabela[i]->prox = NULL;
    }

    t->tam = 0;
    return t;
}

void insere(TABELA *t, int valor){
    int num = t->tabela[hash(valor)]->num; //pego o que tem na tabela na posiçao que quero inserir

    if(num == VAZIO){
        t->tabela[hash(valor)]->num = valor; //caso a posiçao esteja vazia eu só coloco ali
        t->tam++;
        return;
    }else{
        NO *aux = t->tabela[hash(valor)];
        while(aux->prox != NULL) //vou procurar a primeira posição vazia para aquela posiçao da tabela
            aux = aux->prox; //quando sair daqui, tenho que inserir meu numero no aux->prox (ta apontando pra null, ta vazio)

        aux->prox = malloc(sizeof(NO)); //aloco o proximo
        aux = aux->prox; //ando pra frente
        aux->num = valor; //guarda o numero
        aux->prox = NULL; //poe o proximo nulo, pode receber algum numero depois
        t->tam++;
        return;
    }

    return; //pra evitar warning
}

int busca(TABELA *t, int chave){
    int indice = hash(chave);
    NO *aux = t->tabela[indice];

    while(aux != NULL){ //busca dentre os nós encadeados naquela posiçao
        if(aux->num == chave)
            return 1;
    
        aux = aux->prox;
    }

    return 0; //caso nao tenha achado 
}

void printatabela(TABELA *t){
    NO *aux;

    for(int i = 0; i < TAM; i++){
        if(t->tabela[i]->num != VAZIO){ //caso tenha algo ali tenho que printar
            printf("%d ", t->tabela[i]->num);

            aux = t->tabela[i];
            while(aux->prox != NULL){ //pra printar os possiveis nós encadeados naquela posiçao
                aux = aux->prox;
                printf("%d ", aux->num);
            }
        }
    }

    return;
}

void quicksort(int *vet, int esq, int dir) { 
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

int msc(TABELA *t){ //maior subsequencia crescente
    int *vet = malloc(sizeof(int) * t->tam); //para armazenar os numeros da tabela
    int index = 0;

    for (int i = 0; i < TAM; i++){ //pega os numeros da tabela e poe no vetor
        NO *aux = t->tabela[i];
        while(aux != NULL && aux->num != VAZIO){
            vet[index++] = aux->num;
            aux = aux->prox;
        }
    }

    quicksort(vet, 0, index - 1);

    if(t->tam == 0){
        printf("tabela vazia\n");
        free(vet);
        return 0;
    }

    int maiorsubseq = 1; //vai guardar o valor da maior subseq ate o momento
    int atual = 1; //vai guardar o tamanho da subseq atual

    for(int i = 1; i < t->tam; i++){
        if(vet[i] == vet[i - 1] + 1)  //se forem consecutivos é crescente, aí guarda
            atual++;

        else{
            if(atual > maiorsubseq)
                maiorsubseq = atual;
            
            atual = 1;  //reinicia a contagem
        }
    }

    if(atual > maiorsubseq) //pra nao deixar passar a ultima
        maiorsubseq = atual;
    
    free(vet);
    return maiorsubseq;
}
