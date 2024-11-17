#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000003

//feito pelo fernando.

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
  int valor;
  struct no_ *prox;
} NO;

typedef struct hashmap_ {
  int tamanho;
  NO **tabela;
} HM;

int sort(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int maximaSubsequenciaSort(int arr[], int tam) {
  if (tam == 0)
    return 0;

  qsort(arr, tam, sizeof(int), sort);

  int maxSequencia = 1;
  int sequenciaAtual = 1;

  for (int i = 1; i < tam; i++) {
    if (arr[i] == arr[i - 1] + 1) {
      sequenciaAtual++;
    } else {
      maxSequencia =
          maxSequencia >= sequenciaAtual ? maxSequencia : sequenciaAtual;
      sequenciaAtual = 1;
    }
  }
  return maxSequencia =
             maxSequencia >= sequenciaAtual ? maxSequencia : sequenciaAtual;
}

int funcaoHash(int valor, int tamanho) {
  if (valor < 0)
    valor = -valor;
  return valor % tamanho;
}

HM *criarHash(int tamanho) {
  HM *hm = (HM *)malloc(sizeof(HM));
  if (!hm)
    return NULL;
  hm->tamanho = tamanho;
  hm->tabela = (NO **)calloc(hm->tamanho, sizeof(NO *));
  return hm;
}

void inserir(HM *hm, int valor) {
  int indice = funcaoHash(valor, hm->tamanho);
  NO *no = (NO *)malloc(sizeof(NO));
  if (!no)
    return;
  no->valor = valor;
  no->prox = hm->tabela[indice];
  hm->tabela[indice] = no;
  return;
}

int busca(HM *hm, int valor) {
  int indice = funcaoHash(valor, hm->tamanho);
  NO *atual = hm->tabela[indice];

  while (atual != NULL) {
    if (atual->valor == valor) {
      return 1;
    }
    atual = atual->prox;
  }
  return 0;
}

int maximaSubsequenciaHash(HM *hm, int arr[], int tam) {
  int maxSequencia = 1;
  for (int i = 0; i < tam; i++) {
    if (!busca(hm, arr[i] - 1)) {
      int numeroAtual = arr[i];
      int sequenciaAtual = 1;

      while (busca(hm, numeroAtual + 1)) {
        numeroAtual++;
        sequenciaAtual++;
      }
      maxSequencia =
          maxSequencia >= sequenciaAtual ? maxSequencia : sequenciaAtual;
    }
  }
  return maxSequencia;
}

int main(void) {
  Timer timer1, timer2;
  int arraySize;
  scanf(" %d", &arraySize);
  int *codigos = (int *)malloc(sizeof(int) * arraySize);
  HM *hash = criarHash(SIZE);
  for (int i = 0; i < arraySize; i++) {
    scanf(" %d", &codigos[i]);
    inserir(hash, codigos[i]);
  }
  
  printf("numero de entradas: %d\n", arraySize);

  start_timer(&timer1);
  printf("execuçao por hashmap: ");
  maximaSubsequenciaHash(hash, codigos, arraySize);
  imprimeTempoDeExecucao(stop_timer(&timer2));

  start_timer(&timer2);
  printf("execuçao por ordenação: ");
  maximaSubsequenciaSort(codigos, arraySize);
  imprimeTempoDeExecucao(stop_timer(&timer2));
  

  return 0;
}
