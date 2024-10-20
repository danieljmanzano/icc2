#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*exercicio de lab de icc2, temos que selecionar e ordenar informaçoes que vao passar*/
/*no caso a gente vai receber um monte de nome de jogador cada um com um overall e temo que organizar isso aí*/
/*vai sair a pontuação decrescente e pros que tiver ponto igual a gente coloca em ordem alfabetica*/
/*a ideia era fazer dois algoritmo e comparar, um usandocd pilha (fernando fez, ta na outra pasta) e aqui eu uso o shellsort que é mais melhor de bom*/

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


typedef struct jogador{
    char *nome;
    int over;
}JOGADOR;

void shellsort(JOGADOR *vet, int tam){ //algoritmo estranho de explicar, só acredita ai que da certo
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

    return;
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

    return;
} //deu certo show d bola

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

char *strcopy(int tam, char *str1){ //kkkkkkkkk fiz um strcpy na mao pq nao tava rolando com o normal
    char *str2;
    str2 = malloc(tam * sizeof(char) + 1); //ja aloco a string que vai receber a copia aqui dentro

    for(int i = 0; i <= tam + 1; i++){ //o +1 é pra pegar o /0 (talvez ate passe do /0? de qualquer forma o if ali embaixo limita caso aconteça)
        str2[i] = str1[i];
        if(str1[i] == 0) break; //coloquei esse dps pra colocar o /0 na str2 tbm
    }

    return str2;
}//realmente o strcpy original tava dando problema, talvez ele nao copie o /0 pra outra string. aqui eu faço isso e funcionou 10/10 no runcodes ah mulek

int main(void){
    Timer timer;
    start_timer(&timer);

    int n, over; 
    scanf("%d", &n);
    JOGADOR *jogadores = malloc(sizeof(JOGADOR) * n);
    char *aux = malloc(sizeof(char) * 51);

    for(int i = 0; i < n; i++){ //pra guardar todas as entradas 
        scanf(" %s", aux);
        jogadores[i].nome = strcopy(strlen(aux), aux);
        scanf("%d", &over);
        jogadores[i].over = over;
    } //testei aqui ja e ta guardando ok

    shellsort(jogadores, n);
    buscarep(jogadores, n);

    for(int i = 0; i < n; i++){
        printf("%s ", jogadores[n - i - 1].nome);
        printf("%d\n", jogadores[n - i - 1].over);
    }//testei aqui e ele ordenou chique show da bola

    printf("seleção com shellsort\n");
    imprimeTempoDeExecucao(stop_timer(&timer));

    free(jogadores);
    return 0;
}