#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decide(char *aux, char *palavra, char obgt){ //função pra decidir entre registrar palavra, mostrar progresso ou solução
    if(strcmp(aux, "inicio")){
        printf("o programa ja foi incializado, por favor insira uma entrada válida\n");
        return;
    }

    if(strcmp(aux, "palavra")){
        scanf(" %s", palavra);
        sucesso(palavra, obgt);
        return;
    }

    if(strcmp(aux, "progresso")){
        progresso();
        return;
    }

    if(strcmp(aux, "solucao")){

    }
}

int sucesso(char *palavra, char obgt){ //vai verificar se a palavra é valida. se sim, printa sucesso + 1
    int flag = 0;

    for(int i = 0; i < 7; i++){
        if(palavra[i] == '\n') //se chegar ao fim da palavra
            break;
        if(palavra[i] == obgt){ //se encontrar o caracter obrigatorio, a palavra ja é valida
            flag = 1;
            break;
        }
    }

    //aqui a gente tenta buscar a palavra na lista de palavras validas (e altera a flag com base nisso)

    if(flag)
        printf("sucesso + 1\n");
    else 
        printf("palavra invalida\n");

    return;
}

void progresso(){

}

int main(void){
    char *aux = calloc(sizeof(char), 10); //vai guardar o comando 
    char *ini = malloc(sizeof(char) * 8); //a lista de letras inicial
    char *palavra = malloc(sizeof(char) * 8); //a palavra a ser analisada como valida ou nao

    scanf("%s", aux); //vai receber inicio de primeira
    scanf(" %c %c %c %c %c %c %c", &ini[0], &ini[1], &ini[2], &ini[3], &ini[4], &ini[5], &ini[6]); //guarda as letras do inico
    ini[7] = '\n';
    char obgt = ini[0]; //caracter obrigatorio para uma palavra valida (o primeiro dentre as letras da primeira entrada)


    while(1){
        scanf(" %s", aux); //pode ser inicio, palavra, progresso ou solução




    }

    return 0;
}