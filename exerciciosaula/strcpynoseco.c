#include <stdio.h>
#include <stdlib.h>
//só pra treinar, fazendo um strcpy sem string.h (e um strlen pra completar)

int strlen(char *str1){
    int cont = 0;

    for(int i = 0; i < 100; i++){
        if(str1[i] != 0) cont++;
        else break;
    }

    return cont;
}

char *strcpy(int tam, char *str1){
    char *str2;
    str2 = malloc(tam * sizeof(char));

    for(int i = 0; i <= tam; i++){
        str2[i] = str1[i];
        if(str1[i] == 0) break; //coloquei esse dps pra colocar o /0 na str2 tbm
    }

    return str2;
}

int main(void){
    char *str1, *str2;
    int tam;

    str1 = malloc(100 * sizeof(char)); //tamanho maximo de 100
    scanf("%[^\n]", str1);

    tam = strlen(str1);
    str1 = realloc(str1, sizeof(char) * tam);
    str2 = malloc(tam * sizeof(char));

    str2 = strcpy(tam, str1);
    
    free(str1);
    free(str2);
    printf("\nstring copiada : %s", str2);
}
//funcionando show de bola