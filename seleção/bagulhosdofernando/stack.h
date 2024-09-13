#ifndef STACK_H
#define STACK_H
#include <stdbool.h>
typedef struct jogador Jogador;
typedef struct element Elemento;
typedef struct stack Pilha;

Pilha *create_stack(void);
Jogador *create_player(char *nome, int score);
bool isEmpty(Pilha *pilha);
bool insert(Pilha *pilha, Jogador *jogador);
Jogador *pop_item(Pilha *pilha);
Jogador *top(Pilha *pilha);
int stack_size(Pilha *pilha);
char *getNome(Jogador *jogador);
int getNota(Jogador *jogador);
void printPilha(Pilha *pilha);

#endif
