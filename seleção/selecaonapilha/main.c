#include "./stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*daqui pra baixo é pra funcionar o timer*/
// Struct para o funcionamento do timer
    typedef struct{
    clock_t start;
    clock_t end;
}Timer;

// Inicializa o timer
void start_timer(Timer *timer){
    timer->start = clock();
}

// Para o timer e calcula o tempo decorrido
double stop_timer(Timer *timer){
    timer->end = clock();
    return ((double) (timer->end - timer->start)) / CLOCKS_PER_SEC;
}

void imprimeTempoDeExecucao(double tempo){
    printf("Tempo de execução: %f segundos\n", tempo);
}
/*daqui pra frente é o codigo de vdd*/


int main(void) {
  Timer timer;
  start_timer(&timer);
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
  printf("seleção usando pilha\n");
  imprimeTempoDeExecucao(stop_timer(&timer));
  return 0;
}
//seloco que bagunça filho, coisa do fernando isso aí
