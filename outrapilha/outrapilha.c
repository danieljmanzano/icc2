#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//exercicio de lab de icc2. reutilizamos a ideia do ultimo exercicio (da pasta "pratos") só que agora a ordenação é por merge e heap sort

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
    printf(" %f segundos\n", tempo);
}
/*daqui pra frente é o codigo de vdd*/


typedef struct prato_{
    int prep, prior; //tempo de preparaçao, ordem de prioridade
    char *nome; //nome do prato
}PRATO;


/*----------funçoes pra mergesort----------*/
void mergeprior(PRATO *v, PRATO *v2, int i, int m, int f){ //merge pra ordem de prioridade
    int z, i1 = i, i2 = m + 1; 

    for(z = i; z <= f; z++) v2[z] = v[z]; //copio o v em um v2 auxiliar
    z = i;

    while(i1 <= m && i2 <= f) { //enquanto o a primeira metade nao tiver sido inteiramente percorrida/arrumada && a segunda metade tambem nao
        if(v2[i1].prior <= v2[i2].prior) v[z++] = v2[i1++]; //vai arrumando aí
        else v[z++] = v2[i2++]; //aqui tambem
    }

    while(i1 <= m) v[z++] = v2[i1++]; //poe a primeira metade organizada no v
    while(i2 <= f) v[z++] = v2[i2++]; //poe a segunda metade organizada no v
    return;
}

void mergesortprior(PRATO *v, int i, int f){ 
    if(i >= f) return;

    int m = (i + f) / 2; //fico dividindo o vetor 

    mergesortprior(v, i, m); //faço da metade pra tras
    mergesortprior(v, m + 1, f); //faço da metade pra frente

    if(v[m].prior <= v[m + 1].prior) return; //se isso for vdd quer dizer que ta ordenado e pode voltar 

    PRATO *v2 = malloc(sizeof(PRATO) * (f + 1));
    mergeprior(v, v2, i, m, f); //como a função é recursiva só vai pegar depois de separar tudo 
}

void mergeprep(PRATO *v, PRATO *v2, int i, int m, int f){ //merge pra tempo de preparo
    int z, i1 = i, i2 = m + 1; 

    for(z = i; z <= f; z++) v2[z] = v[z]; 
    z = i;

    while(i1 <= m && i2 <= f) {
        if(v2[i1].prep >= v2[i2].prep) v[z++] = v2[i1++]; 
        else v[z++] = v2[i2++]; 
    }

    while(i1 <= m) v[z++] = v2[i1++]; 
    while(i2 <= f) v[z++] = v2[i2++]; 
    return;
}

void mergesortprep(PRATO *v, int i, int f){ 
    if(i >= f) return;

    int m = (i + f) / 2; 

    mergesortprep(v, i, m); 
    mergesortprep(v, m + 1, f); 

    if(v[m].prep >= v[m + 1].prep) return; 

    PRATO *v2 = malloc(sizeof(PRATO) * (f + 1));
    mergeprep(v, v2, i, m, f); 
}

void buscarepmerge(PRATO *vet, int tam){
    int aux, comeco;
    for(int i = 0; i < tam; i++){
        aux = vet[i].prior;
        if(vet[i + 1].prior == aux){ //se o proximo do vetor tem mesma prioridade
            comeco = i; //marco onde fica o primeiro com a prioridade que estou analisando
            i++; 
            while(vet[i + 1].prior == aux){ //enquanto o valor no vetor continuar o mesmo que eu guardei
                i++; //incremento a cada um igual que encontro
            }
            mergesortprep(vet, comeco, i); //chamo o sort com o tanto certo de coisa que quero arrumar 
        }
    }
    return;
}
/*------------------------------------------*/

/*----------funções para heapsort----------*/
void heapify(PRATO *vet, int n, int i){ 
    int maior = i; //inicializa o maior como raiz
    int esq = 2 * i + 1; //indice do filho à esquerda
    int dir = 2 * i + 2; //indice do filho à direita

    if(esq < n && vet[esq].prior > vet[maior].prior) maior = esq; //se o filho à esquerda for maior que a raiz
    else if(esq < n && vet[esq].prior == vet[maior].prior && vet[esq].prep < vet[maior].prep) maior = esq; //pra organizar se a prioridade for igual (arruma por preparo ao contrario)

    if(dir < n && vet[dir].prior > vet[maior].prior) maior = dir; //se o filho à direita for o maior até agora
    else if(dir < n && vet[dir].prior == vet[maior].prior && vet[dir].prep < vet[maior].prep) maior = dir; //mesma coisa de cima


    if(maior != i){ //se o maior nao for a raiz
        PRATO prep = vet[i];
        vet[i] = vet[maior];
        vet[maior] = prep;

        heapify(vet, n, maior); //recursão pra subarvore
    }

    return;
}

void heapsort(PRATO *vet, int n){
    for(int i = n / 2 - 1; i >= 0; i--) heapify(vet, n, i); //constrói heap

    for(int i = n - 1; i > 0; i--){ //vai mexendo no que tem na heap
        PRATO prep = vet[0]; //move a raiz atual pro fim
        vet[0] = vet[i];
        vet[i] = prep;

        heapify(vet, i, 0); //reorganiza heap
    }

    return;
}
/*-----------------------------------------*/

void printa(PRATO *vet, int tam){
    for(int i = 0; i < tam; i++) printf("%s\n", vet[i].nome);
    return;
}

char *strcopy(int tam, char *str1){ //nao confio no strcpy da string.h entao usei o meu
    char *str2;
    str2 = malloc(tam * sizeof(char));

    for(int i = 0; i <= tam; i++){
        str2[i] = str1[i];
        if(str1[i] == 0) break; //coloquei esse dps pra colocar o /0 na str2 tbm
    }

    return str2;
}

PRATO *clonavetor(PRATO *v, int n){ 
    PRATO *v2 = malloc(sizeof(PRATO) * n);

    for(int i = 0; i < n; i++){
        v2[i].prior = v[i].prior;
        v2[i].prep = v[i].prep;
        v2[i].nome = strcopy(strlen(v[i].nome) + 1, v[i].nome);
    }

    return v2;
}

int main(void){
    Timer timer, timer2;
    int n;
    scanf("%d", &n); //numero de linhas de entrada
    PRATO *vet = malloc(sizeof(PRATO) * n);
    for(int i = 0; i < n; i++){
        vet[i].nome = malloc(sizeof(char) * 50);
        scanf(" %d %d %s", &vet[i].prior, &vet[i].prep, vet[i].nome);
        vet[i].nome = realloc(vet[i].nome, sizeof(char) * (strlen(vet[i].nome) + 1));
    }
    PRATO *vet2 = clonavetor(vet, n); //tenho que ter dois vetor pra poder ordenar duas vezes e comparar os algoritmos

    printf("numero de entradas: %d\n", n);

    start_timer(&timer);
    heapsort(vet, n);
    printf("execução do heapsort: ");
    imprimeTempoDeExecucao(stop_timer(&timer));

    start_timer(&timer2);
    mergesortprior(vet2, 0, n - 1);
    buscarepmerge(vet2, n);
    printf("execução do mergesort: ");
    imprimeTempoDeExecucao(stop_timer(&timer2));
    
    //printa(vet2, n); //depois escolhe se quer printar aq e tira o bagulho do comentario pra ver

    free(vet);
    free(vet2);
    return 0;
}