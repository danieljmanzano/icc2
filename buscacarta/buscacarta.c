#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//exercicio de lab de icc2
//tenho um vetor de cartas (são só numeros alias, uso a struct pra facilitar) desorganizado e quero achar uma especifica. pra isso, organizo o vetor e faço uma busca binaria nele
//depois, tenho que retornar a posição "antiga" da carta no vetor. caso tenha repetição do numero, tenho que printar a primeira ocorrencia dele no vetor original
//faço esse algoritmo usando quicksort/busca binaria e busca linear simples, aí comparo qual se sai melhor

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

typedef struct{ //como as cartas vão ser organizadas com base no numero e vou precisar da posição inicial delas, faço uma struct que guarda ambos
    int num, pos;
}carta;

void quicksort(carta *vet, int esq, int dir) { 
    int i = esq, j = dir, x = vet[(esq + dir) / 2].num; 
    carta y;

    while(i <= j){ 
        while(vet[i].num < x && i < dir) i++;
        while(vet[j].num > x && j > esq) j--;
        if(i <= j){
            y = vet[i];
            vet[i] = vet[j];
            vet[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > esq) quicksort(vet, esq, j);
    if(i < dir) quicksort(vet, i, dir);
    
    return;
}

int buscabin(carta *vet, int i, int f, int busca){ //busca um numero ja presente dentro do vetor (retorna a posicao dele)
    int m = (i + f) / 2;

    if(i > f) return -1; //caso nao tenha achado vai chegar aqui em algum momento
    if(vet[m].num == busca) return m;

    if(vet[m].num < busca){
        return buscabin(vet, m + 1, f, busca);
    }else if(vet[m].num > busca){
        return buscabin(vet, i, m - 1, busca);
    }

    return -1; //esse aqui é só pra nao dar warning
}

int achaprimeiro(carta *vet, int pos, int quant, int primeiro){ //função pra tentar encontrar a primeira ocorrencia do numero que achei (pra caso exista repetição do numero)
    int num = vet[pos].num;

    int i = pos;
    while(i >= 0 && num == vet[i].num){ //enquanto for o mesmo numero (da carta que entrou na função) que estou analisando, vai andando pra tras
        if(vet[i].pos < primeiro) primeiro = vet[i].pos; //vejo se a posição original da carta é menor do que a posição da carta que entrou
        i--;
    }

    int j = pos;
    while(j < quant && num == vet[j].num){ //mesma coisa de cima, só vai andando para frente
        if(vet[j].pos < primeiro) primeiro = vet[j].pos;
        j++;
    }

    return primeiro;
}

int buscalinear(carta *vet, int busca, int tam){ //busca linear básica para comparar com o outro algoritmo
    for(int i = 0; i < tam; i++)
        if(vet[i].num == busca) return i;

    return -1; //caso não ache
}

carta *copiavetor(carta *vet, int tam){
    carta *vet2 = malloc(sizeof(carta) * tam);
    for(int i = 0; i < tam; i++){
        vet2[i].num = vet[i].num;
        vet2[i].pos = vet[i].pos;
    }

    return vet2;
}

int main(void){
    Timer timer1, timer2;
    int quant, n; //quantidade de cartas, numero da carta danificada
    scanf("%d %d", &quant, &n);
    carta *vet = malloc(sizeof(carta) * quant); //vetor que guarda as cartas
    for(int i = 0; i < quant; i++){
        scanf("%d", &vet[i].num);
        vet[i].pos = i;
    }

    printf("numero de entradas: %d\n", quant);

    /*-----testando busca linear-----*/
    /*carta *vet2 = copiavetor(vet, quant);
    start_timer(&timer1);
    printf("execução de busca linear: %d\n", (buscalinear(vet2, n, quant) + 1));
    imprimeTempoDeExecucao(stop_timer(&timer1));
    free(vet2);*/

    /*-----testando ordenação e busca binária------*/
    start_timer(&timer2);
    quicksort(vet, 0, quant - 1);

    int pos = buscabin(vet, 0, quant - 1, n); //pego a nova posição da carta no vetor (depois de organizar)
    int antigapos = vet[pos].pos; //pego a posição original da carta no vetor (antes de organizar)

    //aqui embaixo tento ver se meu numero repete (pelo menos uma vez) no vetor, aí tento achar qual a primeira ocorrencia do numero no vetor original
    if((pos != 0) && ((vet[pos - 1].num == vet[pos].num) || (vet[pos + 1].num == vet[pos].num))){ 
        pos = achaprimeiro(vet, pos, quant, antigapos);
        printf("execução de busca binária: %d\n", pos + 1);
        imprimeTempoDeExecucao(stop_timer(&timer2));
        free(vet);
        return 0;
    }    
    
    printf("execução de busca binária: %d\n", antigapos + 1); //esse aqui é pra caso nao tenha achado nenhuma repetição, só printa normal a posição original da carta
    imprimeTempoDeExecucao(stop_timer(&timer2));
    free(vet);
    return 0;
}