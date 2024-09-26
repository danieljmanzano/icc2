#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//exercicio de lab de icc2. 
//recebe um arquivo com nomes e notas de alunos. tenho que ver os k primeiros com maiores notas e printar
//caso tenha mais de um na ultima posição (mesma nota do ultimo) printo mesmo assim só que organizando por ordem alfabetica

typedef struct aluno_{
    char *nome; //string guarda o nome do aluno
    int aum; //guarda o aumento de nota
} ALUNO;

//vou usar pra organizar por notas primeiro o vetor
void quicksort(ALUNO *vet, int esq, int dir) { //vetor a ser ordenado, esquerda (começo) do vet, direita (fim) do vet
    int i = esq, j = dir, x = vet[(esq + dir) / 2].aum; //auxiliares
    ALUNO y;

    while(i <= j){ //paia de explicar, fica a cargo do leitor
        while(vet[i].aum < x && i < dir) i++;
        while(vet[j].aum > x && j > esq) j--;
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

//usei em outro exercicio. ordena por ordem lexicografica
void shellsortchar(ALUNO *vet, int comeco, int fim){ 
    ALUNO *aux = malloc(sizeof(ALUNO));
    int tam = fim - comeco + 1; //coloco +1 pq a diferença sempre come 1
    int gap = tam/2; 
    while(gap > 0){
        for(int i = gap; i < tam; i++){
            *aux = vet[i + comeco]; //sempre coloco a posiçao basica do shellsort de cima só que somando o comeco pra pegar a posiçao certa de vdd
            int j = i;
            while(j >= gap && strcmp(vet[j - gap + comeco].nome, aux->nome) < 0){ 
                vet[j + comeco] = vet[j - gap + comeco];
                j -= gap;
            }
            vet[j + comeco] = *aux;
        }
        gap /= 2;
    }

    return;
} 

//função pra pegar as repetições de nota, uso pra depois deixar os repetidos em ordem alfabetica
int busca(ALUNO *alunos, int k, int i){ //k é o numero de alunos que tenho a printar (se nao tiver repetiçao) e i é o numero de posições no vetor
    int cont = 0;
    
    for(int j = i - k + 1; j >= 0; j--){ //vou contar quantas notas iguais à do ultimo colocado eu tenho
        if(alunos[j].aum != alunos[j + 1].aum) break; //se nao repetiu a nota do ultimo eu saio
        else cont++; //se repetiu adiciono no contador 
    }

    return cont;
}

//só printa os nomes dos alunos
void printa(ALUNO *alunos, int total, int fim){ //o total me diz quantos vou ter que printar e o fim é o fim do meu vetor
    for(int i = fim; i >= fim - total; i--){ //como dexei organizado crescente tenho que printar "ao contrario"
        printf("%s\n", alunos[i].nome);
    }
    return;
}

int main(void){ 
    ALUNO *alunos = malloc(sizeof(ALUNO));
    char *aux = malloc(sizeof(char) * 51); //vou usar pra ler os nomes
    int k, cont;
    float n1, n3;

    char *nomearq = malloc(sizeof(char) * 51);
    scanf("%s ", nomearq);
    nomearq = realloc(nomearq, sizeof(char) * (strlen(nomearq) + 1));

    scanf("%d", &k);

    FILE *fp = fopen(nomearq, "r");
    if(fp == NULL) exit (1);

    char *stringpulaprimeiralinhadoarquivo = malloc(sizeof(char) * 52); //nome autoexplicativo
    fscanf(fp, "%s\n", stringpulaprimeiralinhadoarquivo);
    free(stringpulaprimeiralinhadoarquivo);

    int i = 0;
    while(!feof(fp)){ //leitura do arquivo. coloco tudo que preciso no vetor alunos
        fscanf(fp, "%[^,],%f,%f,%f\n", aux, &n1, &n3, &n3);
        alunos = realloc(alunos, sizeof(ALUNO) * (i + 1)); //pra colocar as novas informaçoes no vetor
        alunos[i].nome = malloc(sizeof(char) * (strlen(aux) + 1)); //aloco o nome do tal aluno com o numero certo de caracteres
        strcpy(alunos[i].nome, aux); //copio do aux pro novo endereço (que realmente vai ficar guardado)
        alunos[i].nome[strlen(aux)] = '\0'; //só pra colocar /0 no final do nome e nao dar problema depois
        alunos[i].aum = (int) ((n3 - n1) * 10);
        i++;
    }

    fclose(fp);
    fp = NULL;

    quicksort(alunos, 0, i); //arrumo pelas notas (pra pegar os melhores)
    cont = busca(alunos, k, i); //esse cont me diz quantas repetições de nota vou ter
    shellsortchar(alunos, i - k - cont, i - k); //organizo as repeticoes por ordem alfabetica
    printa(alunos, k + cont, i); 

    return 0;
}