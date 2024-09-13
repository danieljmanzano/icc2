#include "./stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  long int qnt = 0;
  scanf(" %ld", &qnt);
  Pilha *pilha = create_stack();
  Pilha *pilhaAux = create_stack();
  char *nome = NULL;
  int score = 0;
  for (int i = 0; i < qnt; i++) {
    nome = malloc(sizeof(char) * 51);
    scanf(" %s", nome);
    nome = realloc(nome, sizeof(char) * (strlen(nome) + 1));
    scanf(" %d", &score);
    Jogador *jogador = create_player(nome, score);
    insert(pilha, jogador);
  }
  while (!isEmpty(pilha)) {
    Jogador *jogador = pop_item(pilha);
    while (!isEmpty(pilhaAux) &&
           ((getNota(top(pilhaAux)) > getNota(jogador)) ||
            ((getNota(top(pilhaAux)) == getNota(jogador)) &&
             strcmp(getNome(top(pilhaAux)), getNome(jogador)) <= 0))) {
      insert(pilha, pop_item(pilhaAux));
    }
    insert(pilhaAux, jogador);
  }
  printPilha(pilhaAux);
  return 0;
}
