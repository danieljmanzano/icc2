#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//exercicio de lab de icc2. fernando que fez, nao sei como funciona valeu eh nois

/*daqui pra baixo é pra funcionar o timer*/
// Struct para o funcionamento do timer
typedef struct {
    clock_t start;
    clock_t end;
} Timer;

// Inicializa o timer
void start_timer(Timer *timer) {
    timer->start = clock();
}

// Para o timer e calcula o tempo decorrido
double stop_timer(Timer *timer) {
    timer->end = clock();
    return ((double) (timer->end - timer->start)) / CLOCKS_PER_SEC;
}

void imprimeTempoDeExecucao(double tempo){
    printf("%f segundos\n", tempo);
}
/*daqui pra frente é o codigo de vdd*/

typedef struct no_ {
  int chave;
  struct no_ *esquerda, *direita;
} no;

no *novoNo(int chave) {
  no *NO = (no *)malloc(sizeof(no));
  if (!NO)
    return NULL;
  NO->chave = chave;
  NO->direita = NO->esquerda = NULL;
  return NO;
}

no *procuraNo(no *raiz, int chave) {
  if (!raiz || raiz->chave == chave)
    return raiz;
  if (raiz->chave < chave)
    return procuraNo(raiz->direita, chave);
  return procuraNo(raiz->esquerda, chave);
}

no *dfs(no *raiz, int chave) {
  if (!raiz || raiz->chave == chave)
    return raiz;
  no *esquerda = dfs(raiz->esquerda, chave);
  no *direita = dfs(raiz->direita, chave);
  return esquerda ? esquerda : direita ? direita : NULL;
}

no *inserirNo(no *raiz, int chave) {
  if (!raiz)
    return novoNo(chave);
  if (raiz->chave > chave)
    raiz->esquerda = inserirNo(raiz->esquerda, chave);
  else if (raiz->chave < chave)
    raiz->direita = inserirNo(raiz->direita, chave);
  return raiz;
}

int main(void) {
  Timer timer1, timer2;
  int tamanho, elemento, alvo;
  scanf(" %d", &tamanho);
  scanf(" %d", &elemento);
  no *raiz = NULL;
  raiz = inserirNo(raiz, elemento);
  for (int i = 0; i < tamanho - 1; i++) {
    scanf(" %d", &elemento);
    inserirNo(raiz, elemento);
  }
  scanf(" %d", &alvo);

  printf("numero de entradas: %d\n", tamanho);

  start_timer(&timer1);
  no *noo1 = procuraNo(raiz, alvo);
  printf("busca binária\n");
  imprimeTempoDeExecucao(stop_timer(&timer1));

  start_timer(&timer2);
  no *noo2 = dfs(raiz, alvo);
  printf("dfs\n");
  imprimeTempoDeExecucao(stop_timer(&timer2));

  return 0;
}
