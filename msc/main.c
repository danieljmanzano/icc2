#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main(void){
    int n, valor;
    scanf("%d", &n);

    /*pra testar com hashmap*/
    TABELA *t = inicializa();
    for(int i = 0; i < n; i++){
        scanf("%d", &valor);
        insere(t, valor);
    }
    printf("%d\n", msc(t));

    return 0;
}