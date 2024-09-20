#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno_{
    char *nome; //string guarda o nome do aluno
    int aum; //guarda o aumento de nota
} ALUNO;

//mergesort que eu fiz pra outra ocasiao, fiz as devidas alterações pra rodar com o tipo aluno
void merge(ALUNO *v, int *v2, int i, int m, int f){
    int z, i1 = i, i2 = m + 1; //auxiliares pro negocio dar bom

    for(z = i; z <= f; z++) v2[z] = v[z].aum; //copio o v em um v2 auxiliar
    z = i;

    while(i1 <= m && i2 <= f) { //enquanto o a primeira metade nao tiver sido inteiramente percorrida/arrumada && a segunda metade tambem nao
        if(v2[i1] <= v2[i2]) v[z++].aum = v2[i1++]; //vai arrumando aí
        else v[z++].aum = v2[i2++]; //aqui tambem
    }

    while(i1 <= m) v[z++].aum = v2[i1++]; //poe a primeira metade organizada no v
    while(i2 <= f) v[z++].aum = v2[i2++]; //poe a segunda metade organizada no v
}

void mergesort(ALUNO *v, int *v2, int i, int f){ //o v2 é só um auxiliar que vou usar pro merge, pode ignorar aqui por enquanto
    if(i >= f) return;

    int m = (i + f) / 2; //fico dividindo o vetor (obs.: funciona pra tamanhos impares tambem, nao precisa se preocupar)

    mergesort(v, v2, i, m); //faço da metade pra tras
    mergesort(v, v2, m + 1, f); //faço da metade pra frente

    if(v[m].aum <= v[m + 1].aum) return; //se isso for vdd quer dizer que ta ordenado e pode vorta 

    merge(v, v2, i, m, f); //como a função é recursiva só vai pegar depois de separar tudo 
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

//função pra pegar as repetições de nota, uso pra depois deixar em ordem alfabetica
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
}

int main(void){ 
    ALUNO *alunos = malloc(sizeof(ALUNO));
    char *aux = malloc(sizeof(char) * 51); //vou usar pra ler os nomes
    int k, cont;
    float n1, n2, n3; //eu nao uso o n2 mas preciso pra ler...

    char *nomearq = malloc(sizeof(char) * 51);
    scanf("%s ", nomearq);
    nomearq = realloc(nomearq, sizeof(char) * (strlen(nomearq) + 1));

    scanf("%d", &k);

    FILE *fp = fopen(nomearq, "r");
    if(fp == NULL) exit (1);

    int i = 0;
    while(!feof(fp)){ //leitura do arquivo. coloco tudo que preciso no vetor alunos
        fscanf(fp, " %[^,]s", aux);
        fscanf(fp, "%f,%f,%f", &n1, &n2, &n3);
        alunos = realloc(alunos, sizeof(ALUNO) * (i + 1)); //pra colocar as novas informaçoes no vetor
        alunos[i].nome = malloc(sizeof(char) * (strlen(aux) + 1));
        strcpy(alunos[i].nome, aux);
        alunos[i].aum = (int) n3 - n1;
        i++;
    }

    int *v2 = malloc(sizeof(int) * i); //tenho que usar esse vetor pra auxiliar 
    mergesort(alunos, v2, 0, i); //arrumo pelas notas (pra pegar os melhores)
    cont = busca(alunos, k, i); //esse cont me diz quantas repetições de nota vou ter
    shellsortchar(alunos, i - cont, i); 
    printa(alunos, k + cont, i);

    return 0;
}