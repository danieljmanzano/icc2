#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//feito pelo fernando
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

typedef struct carta_ {
  int value, index;
} Carta;

int binarySearch(Carta *cards, int target, int arraySize) {
  int left = 0, right = arraySize - 1;
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (target > cards[mid].value)
      left = mid + 1;
    else
      right = mid;
  }
  return cards[right].index + 1;
}

void radixSort(int numberOfCards, Carta *cards, int biggestNumber) {
  for (int dig = 1; biggestNumber / dig > 0; dig *= 10) {
    Carta array_auxiliar[numberOfCards];
    int i, contador[10] = {0};
    for (i = 0; i < numberOfCards; i++) {
      contador[(cards[i].value / dig) % 10]++;
    }
    for (i = 1; i < 10; i++)
      contador[i] += contador[i - 1];
    for (i = numberOfCards - 1; i >= 0; i--) {
      array_auxiliar[contador[(cards[i].value / dig) % 10] - 1] = cards[i];
      contador[(cards[i].value / dig % 10)]--;
    }
    for (i = 0; i < numberOfCards; i++) {
      cards[i] = array_auxiliar[i];
    }
  }
  return;
}

int main(void) {
  Timer timer;
  int numberOfCards, target, max = 0;
  scanf(" %d %d", &numberOfCards, &target);
  Carta *cards = (Carta *)malloc(sizeof(Carta) * numberOfCards);
  for (int i = 0; i < numberOfCards; i++) {
    Carta carta;
    carta.index = i;
    scanf(" %d", &carta.value);
    cards[i] = carta;
    if (carta.value > max)
      max = carta.value;
  }

  start_timer(&timer);
  radixSort(numberOfCards, cards, max);
  printf("numero de entradas: %d\n", numberOfCards);
  int result = binarySearch(cards, target, numberOfCards);
  printf("execucao de busca binaria (com radix sort): %d\n", result);
  imprimeTempoDeExecucao(stop_timer(&timer));
  free(cards);
  cards = NULL;
  return 0;
}
