#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct jogador{
    char *nome;
    int over;
}JOGADOR;

void shellsort(JOGADOR *vet, int tam){
    //algoritmo estranho de explicar, só acredita ai que da certo
    JOGADOR *aux = malloc(sizeof(JOGADOR));
    int gap = tam/2;
    while(gap > 0){
        for(int i = gap; i < tam; i++){
            *aux = vet[i];
            int j = i;
            while(j >= gap && vet[j - gap].over > aux->over){
                vet[j] = vet[j - gap];
                j -= gap;
            }
            vet[j] = *aux;
        }
        gap /= 2;
    }
}

void shellsortchar(JOGADOR *vet, int comeco, int fim){ //mesma logica do shellsort mas com char (ah é nada)
    JOGADOR *aux = malloc(sizeof(JOGADOR));
    int tam = fim - comeco + 1; //coloco +1 pq a diferença sempre come 1
    int gap = tam/2; 
    while(gap > 0){
        for(int i = gap; i < tam; i++){
            *aux = vet[i + comeco]; //sempre coloco a posiçao basica do shellsort de cima só que somando o comeco pra pegar a posiçao certa de vdd
            int j = i;
            while(j >= gap && strcmp(vet[j - gap + comeco].nome, aux->nome) < 0){ //unica mudança significativa: ao inves de comparar o int eu comparo por ordem alfabetica
                vet[j + comeco] = vet[j - gap + comeco];
                j -= gap;
            }
            vet[j + comeco] = *aux;
        }
        gap /= 2;
    }
}

void buscarep(JOGADOR *vet, int tam){ //funçao pra buscar repetiçoes de pontuaçao
    int aux, comeco;
    for(int i = 0; i < tam; i++){
        aux = vet[i].over;
        if(vet[i + 1].over == aux){ //se o proximo do vetor tem mesma pontuaçao
            comeco = i; //marco onde fica o primeiro com a pontuaçao que estou analisando
            i++; 
            while(vet[i + 1].over == aux){ //enquanto o valor no vetor continuar o mesmo que eu guardei
                i++; //incremento a cada um igual que encontro
            }
            shellsortchar(vet, comeco, i); //chamo o sort com o tanto certo de coisa que quero arrumar
        }
    }
}//bagulho aqui vai ser complexidade estorando mas nao sei mais o que fazer nao


int main(void){
    int n, over; 
    scanf("%d", &n);
    JOGADOR *jogadores = malloc(sizeof(JOGADOR) * n);

    for(int i = 0; i < n; i++){ //pra guardar todas as entradas 
        char *aux = malloc(sizeof(char) * 51);
        scanf(" %s", aux);
        aux = realloc(aux, strlen(aux));
        jogadores[i].nome = aux;
        scanf("%d", &over);
        jogadores[i].over = over;
    } //testei aqui ja e ta guardando ok

    shellsort(jogadores, n);
    buscarep(jogadores, n);

    for(int i = 0; i < n; i++){
        printf("%s ", jogadores[n - i - 1].nome);
        printf("%d\n", jogadores[n - i - 1].over);
    }//testei aqui e ele ordenou chique show da bola


}