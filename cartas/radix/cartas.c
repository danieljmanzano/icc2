#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//feito pelo fernando

typedef struct cartas_ Cartas;
void radixSort(Cartas *cartas, int numeroDeCartas, int numeroDeDigitos,
               char ordemNumeros[10], char ordemNaipes[][4]);
void countSortNumeros(Cartas *cartas, int numeroDeCartas, int digito,
                      char ordemNumeros[10]);
void countSortNaipes(Cartas *cartas, int numeroDeCartas, char ordemNaipes[][4]);
void printCartas(Cartas *cartas, int numeroDeCartas);
int Procura(char Array[10], char chave);
int ProcuraNaipe(char Array[][4], char *chave);

struct cartas_ {
  char *maoDeCartas;
  char *naipe;
};

int Procura(char Array[10], char chave) {
  for (int i = 0; i < 10; i++) {
    if (Array[i] == chave)
      return i;
  }
  return 1000000010;
}

int ProcuraNaipe(char Array[][4], char *chave) {
  for (int i = 0; i < 4; i++) {
    if (strcmp(Array[i], chave) == 0)
      return i;
  }
  return 1000000010;
}

void countSortNumeros(Cartas *cartas, int numeroDeCartas, int digito,
                      char ordemNumeros[10]) {
  Cartas *auxArray = (Cartas *)malloc(sizeof(Cartas) * numeroDeCartas);
  int contagem[11] = {0};

  for (int i = 0; i < numeroDeCartas; i++) {
    contagem[Procura(ordemNumeros, cartas[i].maoDeCartas[digito])]++;
  }

  for (int i = 1; i < 11; i++) {
    contagem[i] += contagem[i - 1];
  }

  for (int i = numeroDeCartas - 1; i >= 0; i--) {
    int chave = Procura(ordemNumeros, cartas[i].maoDeCartas[digito]);
    auxArray[contagem[chave] - 1] = cartas[i];
    contagem[chave]--;
  }

  for (int i = 0; i < numeroDeCartas; i++) {
    cartas[i] = auxArray[i];
  }
  free(auxArray);
  return;
}

void countSortNaipes(Cartas *cartas, int numeroDeCartas,
                     char ordemNaipes[][4]) {
  Cartas *auxArray = (Cartas *)malloc(sizeof(Cartas) * numeroDeCartas);
  int contagem[5] = {0};
  for (int i = 0; i < numeroDeCartas; i++)
    contagem[ProcuraNaipe(ordemNaipes, cartas[i].naipe)]++;
  for (int i = 1; i < 5; i++)
    contagem[i] += contagem[i - 1];
  for (int i = numeroDeCartas - 1; i >= 0; i--) {
    int chave = ProcuraNaipe(ordemNaipes, cartas[i].naipe);
    auxArray[contagem[chave] - 1] = cartas[i];
    contagem[chave]--;
  }
  for (int i = 0; i < numeroDeCartas; i++)
    cartas[i] = auxArray[i];
  free(auxArray);
  return;
}

void radixSort(Cartas *cartas, int numeroDeCartas, int numeroDeDigitos,
               char ordemNumeros[10], char ordemNaipes[][4]) {
  for (int digito = 1; (numeroDeDigitos / digito) > 0; digito++) {
    countSortNumeros(cartas, numeroDeCartas, numeroDeDigitos - digito,
                     ordemNumeros);
    printf("Após ordenar o %d° dígito dos valores:\n",
           numeroDeDigitos - digito + 1);
    printCartas(cartas, numeroDeCartas);
  }
  countSortNaipes(cartas, numeroDeCartas, ordemNaipes);
  printf("Após ordenar por naipe:\n");
  printCartas(cartas, numeroDeCartas);
}

void printCartas(Cartas *cartas, int numeroDeCartas) {
  for (int i = 0; i < numeroDeCartas; i++) {
    printf("%s ", cartas[i].naipe);
    printf("%s;", cartas[i].maoDeCartas);
  }
  printf("\n");
}

int main(void) {
  int numeroDeCartas = 0, numeroDeDigitos = 0;
  char ordemNumeros[10] = {'4', '5', '6', '7', 'Q', 'J', 'K', 'A', '2', '3'};
  char ordemNaipes[][4] = {"♦", "♠", "♥", "♣"};
  scanf(" %d %d", &numeroDeCartas, &numeroDeDigitos);
  Cartas *cartas = (Cartas *)malloc(sizeof(Cartas) * numeroDeCartas);

  for (int i = 0; i < numeroDeCartas; i++) {
    cartas[i].maoDeCartas =
        (char *)malloc(sizeof(char) * (numeroDeDigitos + 1));
    cartas[i].naipe = (char *)malloc(sizeof(char) * 10);
    scanf(" %s %s", cartas[i].naipe, cartas[i].maoDeCartas);
  }

  for (int i = 0; i < numeroDeCartas; i++) {
    printf("%s %s;", cartas[i].naipe, cartas[i].maoDeCartas);
  }
  printf("\n");
  radixSort(cartas, numeroDeCartas, numeroDeDigitos, ordemNumeros, ordemNaipes);
  for (int i = 0; i < numeroDeCartas; i++) {
    free(cartas[i].maoDeCartas);
    cartas[i].maoDeCartas = NULL;
    free(cartas[i].naipe);
    cartas[i].naipe = NULL;
  }
  free(cartas);
  cartas = NULL;
  return 0;
}
