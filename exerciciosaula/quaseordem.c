#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//recebo um vetor char com m letras do alfabeto e devo decidir se com uma unica troca entre char do vetor consigo ordenar ele em ordem alfabetica
//se sim printa 1, se nao sai 0

int compara(char alfabeto[26], char *vet, int m){
    int flag = 0;
    for(int i = 0; i < m; i++){
        if(vet[i] != alfabeto[i]){
            flag++; //se achar diferença entre os dois coloco um a mais na flag. caso passe de 2, quer dizer que só uma troca nao rola nao
        }
    }
    return flag;
}


int main(void){
    //vetor de baixo vai me auxiliar pra achar as "desordens"
    char alfabeto[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; 
    char *vet = malloc(sizeof(char) * 28);
    int m, flag = 0; //o vetor flag vai me sinalizar onde vao ter diferenças entre o vet e o alfabeto

    scanf("%d", &m);
    vet = realloc(vet, sizeof(char) * (m + 1));
    for(int i = 0; i < m; i++){
        scanf(" %c", &vet[i]);
    }

    if(compara(alfabeto, vet, m) == 2 || !compara(alfabeto, vet, m)) printf("1\n");
    else printf("0\n");

    free(vet);
    return 0;
}