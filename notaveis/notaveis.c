#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno_{
    char *nome; //string guarda o nome do aluno
    int aum; //guarda o aumento de nota
} ALUNO;



int main(void){ //fazendo sem modularização ate agr pq minha cabeca funciona melhor colocando tudo aqui do jeito que ta assim
    ALUNO *alunos = malloc(sizeof(ALUNO));
    char *aux = malloc(sizeof(char) * 51); //vou usar pra ler os nomes
    int k;
    float n1, n2, n3;

    char *nomearq = malloc(sizeof(char) * 51);
    scanf("%s ", nomearq);
    nomearq = realloc(nomearq, sizeof(char) * (strlen(nomearq) + 1));

    scanf("%d", &k);

    FILE *fp = fopen(nomearq, 'r');
    if(fp == NULL) exit (1);

    while(!feof(fp)){
        int i = 0;
        fscanf(fp, " %[^,]s", aux);
        fscanf(fp, "%f,%f,%f", &n1, &n2, &n3);
        alunos = realloc(alunos, sizeof(ALUNO) * (i + 1)); //pra colocar as novas informaçoes no vetor
        strcpy(alunos[i].nome, aux);
        alunos[i].aum = (int) n3 - n1; //parei aqui;
        i++;
    }
    return 0;
}