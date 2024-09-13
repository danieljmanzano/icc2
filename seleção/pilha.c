#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

//TAD do daniel
//deu certo ah mulek (mas acho que nem vai usar, fica aí de enfeite)

typedef struct jogador{
    char *nome;
    int over; //over de overall, é a pontuação do rapaz
    struct jogador *anterior; //o anterior aqui é o nó logo abaixo na pilha
}JOGADOR;

typedef struct pilha{
    JOGADOR *topo; 
    int tam;  
}PILHA;

PILHA *pilha_criar(){
    PILHA *p = malloc(sizeof(PILHA));
    if(p != NULL){
        p->topo = NULL;
        p->tam = 0;
    }
    return p;
}

void pilha_apagar(PILHA *p){
    if(p == NULL) return;
    JOGADOR *aux = malloc(sizeof(JOGADOR));
    while(p->tam > 0){
        aux = p->topo;
        p->topo = p->topo->anterior;
        free(aux);
        p->tam--;
    }
}

void pilha_inserir(PILHA *p, JOGADOR *j){
    if(p == NULL) return;
    if(p->topo == NULL){
        j->anterior = NULL;
        p->topo = j;
    }else{
        j->anterior = p->topo;
        p->topo = j;
        p->tam++;
    }
    return;
}

JOGADOR *pilha_remover(PILHA *p){
    if(p == NULL && !pilha_vazia(p)) return NULL;
    JOGADOR *aux = malloc(sizeof(JOGADOR));
    aux = p->topo;
    p->topo = p->topo->anterior;
    p->tam--;
    return aux;
}

int pilha_vazia(PILHA *p){
    if(p == NULL || p->tam == 0) return 1;
    return 0;
}

JOGADOR *jogador_criar(char *nome, int over){
    JOGADOR *aux = malloc(sizeof(JOGADOR));
    if(aux != NULL){
        aux->nome = nome;
        aux->over = over;
        aux->anterior = NULL;
    }
    return aux;
}

int jogador_ponto(JOGADOR *jogador){
    if(jogador == NULL) return -1;
    return jogador->over;
}

char *jogador_nome(JOGADOR *jogador){
    if(jogador == NULL) return NULL;
    return jogador->nome;
}

