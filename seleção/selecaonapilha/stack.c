#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

struct jogador {
  char *nome;
  int nota;
};

struct element {
  Jogador *jogador;
  struct element *next;
};

struct stack {
  int total_qnt;
  struct element *head;
};

Pilha *create_stack(void) {
  Pilha *stack = (Pilha *)malloc(sizeof(Pilha));
  if (stack == NULL) {
    exit(1);
  }
  stack->total_qnt = 0;
  stack->head = NULL;
  return stack;
}

Jogador *create_player(char *nome, int score) {
  Jogador *jogador = malloc(sizeof(Jogador));
  if (!jogador) {
    return NULL;
  }
  jogador->nome = nome;
  jogador->nota = score;
  return jogador;
}

bool isEmpty(Pilha *pilha) {
  if (pilha == NULL || pilha->head == NULL) {
    return true;
  }
  return false;
}

bool insert(Pilha *pilha, Jogador *jogador) {
  Elemento *elemento = (Elemento *)malloc(sizeof(Elemento));
  if (pilha != NULL && jogador != NULL) {
    elemento->jogador = jogador;
    elemento->next = pilha->head;
    pilha->head = elemento;
    pilha->total_qnt++;
    return true;
  }
  return false;
}

Jogador *pop_item(Pilha *pilha) {
  Jogador *jogador = malloc(sizeof(Jogador));
  if (pilha != NULL && !(isEmpty(pilha))) {
    Elemento *dummy;
    dummy = pilha->head;
    pilha->head = dummy->next;
    pilha->total_qnt--;
    jogador = dummy->jogador;
    free(dummy);
    return jogador;
  }
  return NULL;
}

Jogador *top(Pilha *pilha) {
  if (pilha != NULL) {
    return pilha->head->jogador;
  }
  return NULL;
}

int stack_size(Pilha *pilha) {
  if (pilha != NULL) {
    return pilha->total_qnt;
  }
  exit(1);
}

char *getNome(Jogador *jogador) {
  if (jogador) {
    return jogador->nome;
  }
  exit(1);
}

int getNota(Jogador *jogador) {
  if (jogador) {
    return jogador->nota;
  }
  exit(1);
}
void printPilha(Pilha *pilha) {
  if (!pilha) {
    return;
  }
  Pilha *pilhaAux = pilha;
  while (!isEmpty(pilhaAux)) {
    printf("%s %d\n", getNome(top(pilhaAux)), getNota(top(pilhaAux)));
    pilhaAux->head = pilhaAux->head->next;
  }
  return;
}
