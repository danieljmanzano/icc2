#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ultimo exercicio de lab!!!! fernando fez tudo aqui
//primeiro vao me informar quantas cidades (grafos) tem e quantos passeios pelas cidades serao feitos
//cada cidade recebe um nome (entrada do usuario) e um indice em seguida que mostra pra qual cidade ela consegue ir
//obs.: o indice próprio de cada cidade é dado pela ordem de entrada, o indice recebido do usuario é só o destino possivel a partir daquela cidade
//depois disso, recebe o nome de uma cidade e a quantidade de passos que dará a partir dela. esse tipo de entrada é repetido ao numero de passeios que foi fornecido no começo
//a saída vai ser o destino alcançado a partir de cada uma dessas ultimas entradas

typedef struct local_ {
  char *nome;
  int proximo;
  int indice;
} local;

void tour(local *grafo, int inicio, int passos) {
  local atual = grafo[inicio];
  for (int i = 0; i < passos; i++) {
    atual = grafo[atual.proximo - 1];
  }
  printf("%s\n", atual.nome);
  return;
}

int acharIndice(local *grafo, char *nome, int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    if (!strcmp(nome, grafo[i].nome)) {
      return i;
    }
  }
  return -1;
}

int main(void) {
  int localizacoes, passeios;
  scanf(" %d", &localizacoes);
  scanf(" %d", &passeios);

  local *grafo = (local *)malloc(sizeof(local) * localizacoes);
  for (int i = 0; i < localizacoes; i++) {
    grafo[i].indice = i;
    grafo[i].nome = (char *)malloc(sizeof(char) * 51);
    scanf(" %s", grafo[i].nome);
    grafo[i].nome =
        realloc(grafo[i].nome, sizeof(char) * (strlen(grafo[i].nome) + 1));
    scanf(" %d", &grafo[i].proximo);
  }

  for (int i = 0; i < passeios; i++) {
    char *nomee = (char *)malloc(sizeof(char) * 51);
    scanf(" %s", nomee);
    nomee = realloc(nomee, sizeof(char) * (strlen(nomee) + 1));
    int passos = 0;
    scanf(" %d", &passos);
    int indice = acharIndice(grafo, nomee, localizacoes);
    tour(grafo, indice, passos);
  }

  return 0;
}

//bagulho tao simples que a unica coisa na pasta é o proprio .c