#include <stdio.h>
#include <stdlib.h>

//recebo um vetor de 5 numeros inteiros e devo ver se, realizando certas operaçoes neles (+, -, / ou *) vou obter o numero 23
//alias, tenho que fazer recursivamente


//minha logica. entendi o enunciado errado kkkkkkkk (achei que era pra analisar cada uma das operaçoes separadamente)
/*int mult(int *vet, int i){
    if(i == 4) return vet[4];
    return vet[i] * mult(vet, i+1);
}

int soma(int *vet, int i){
    if(i == 4) return vet[4];
    return vet[i] + soma(vet, i+1);
}

int subt(int *vet, int i){
    if(i == 4) return vet[4];
    return  vet[i] - subt(vet, i+1);
}

int main(void){
    int *vet = malloc(sizeof(int) * 5);

    while(1){ //fica recebendo entradas ate que voce digite cinco zeros 
        for(int i = 0; i < 5; i++) scanf("%d", &vet[i]);
        if(vet[0] == 0 && vet[1] == 0 && vet[2] == 0 && vet[3] == 0 && vet[4] == 0) return 0;
        if(soma(vet, 0) == 23 || mult(vet, 0) == 23 || subt(vet, 0) == 23) printf("possivel\n");
        else printf("impossivel\n");
    }
}*/

//logica do mano gustavo (entendeu o enunciado certo)
#include <stdbool.h>

#define ALVO 23

void troca(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool calc(int num[], int pos, int res){
    if(pos == 5){
        return res == ALVO;
    }

    return calc(num, pos + 1, res + num[pos]) || calc(num, pos + 1, res - num[pos]) || calc(num, pos + 1, res * num[pos + 1]);
} //pra eu entender : analisa todas as combinaçoes possiveis entre os numeros recebidos com as operaçoes possiveis entre eles (a ordem dos numeros nao muda alias, só as operaçoes)

bool permuta(int num[], int ini){
    if (ini == 5){
        return calc(num, 1, num[0]);
    }
    for(int i = ini; i < 5; i++){
        troca(&num[ini], &num[i]);
        if(permuta(num, ini + 1)){
            return true;
        }
        troca(&num[ini], &num[i]);
    }
    return false;
}

int main(void){
    int num[5];
    while(true){
        scanf("%d %d %d %d %d", &num[0], &num[1], &num[2], &num[3], &num[4]);
        if(num[0] == 0 && num[1] == 0 && num[2] == 0 && num[3] == 0 && num[4] == 0){
            break;
        }
        if(permuta(num, 0)){
            printf("possivel\n");
        } else {
            printf("impossivel\n");
        }
    }
    return 0;
}