#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "operacoes.h"

#define max(a, b) ((a) > (b) ? (a) : (b))


char* multiplicacao(const char* str1, const char* str2)
{
    if(str1[0]=='0' || str2[0]=='0') return "0";
    size_t tam1,tam2;
    tam1 = strlen(str1);
    tam2 = strlen(str2);
    char* ans = (char*)calloc((tam1+tam2+1), sizeof(char));
    
    if(ans == NULL){
        printf("erro na alocação");
        exit(1);
    }
    ans[tam1 +tam2] = '\0';
    for(size_t i=0 ; i<tam1; i++){
        for(size_t j=0 ; j<tam2; j++){
            size_t index = i+j+1;
            size_t mul = (str1[i]-'0') * (str2[j]-'0');
            while(mul){
                mul += ans[index];
                ans[index] = (mul)%10;
                mul = mul/10;
                index--;
            }
        }
    }
    for(size_t i=0 ; i<tam2+tam1 ; i++){
        ans[i] += '0';
    }
    if(ans[0]=='0') return ans+1;
    return ans;
   
}

//divido a string e pego a metade de mais valor (a da esquerda)
char *dividir(char *str, int begin, int count){
    //strndup(str, count);

    char* r = (char*)calloc((count+1), sizeof(char));
    if(r == NULL){
        printf("erro na alocaçao");
        exit(1);
    }
    strncpy(r,str+begin,count);
    return r;
}


char *karatsuba(char *str1, char *str2){    
    //algoritmo: tenho a * b de tamanho n cada um
    //a0 = n / 2 primeiros numeros do numero a; b0 = n / 2 primeiros numeros do numero b
    //a1 = n / 2 ultimos numeros " " " "; b1 = n / 2 ultimos numeros " " " "
    //a multiplicacao é feita com a * b = a0 * b0 + b0 * a1 * 10^n/2 + b1 * a0 * 10^n/2 + a1 * b1 * 10^n
    
    if(strlen(str1) <= 1 || strlen(str2) <= 1){
        return multiplicacao(str1, str2);
    }

    char *a0, *a1, *b0, *b1, *z0, *z1, *z2;
    size_t tam, meio;  
    if(strlen(str1) > strlen(str2)) tam = strlen(str1);
    else tam = strlen(str2);
    meio = (tam/2);

    a0 = dividir(str1, strlen(str1) - meio, meio); // menor 1
    a1 = dividir(str1, 0, strlen(str1) - meio); // maior 1
    b0 = dividir(str2, strlen(str2) - meio, meio); // menor 2
    b1 = dividir(str2, 0, strlen(str2) - meio); // maior 2
    
    z0 = malloc(sizeof(char) * (tam + 2));
    z1 = malloc(sizeof(char) * (tam + 2));
    z2 = malloc(sizeof(char) * (tam + 2));

    z0 = karatsuba(a0, b0);
    z1 = karatsuba(add(a0, a1), add(b0, b1));
    z2 = karatsuba(a1, b1);

    free(a0);
    free(a1);
    free(b0);
    free(b1);
    
    return add(add(potencia_de_10(z2, meio * 2), potencia_de_10(sub(sub(z1, z2), z0), meio)), z0);
    
}

// Soma de dois números representados por strings
char* add(char* str1, char* str2) {
    int tam = max(strlen(str1), strlen(str2));
    int carry = 0;
    int sum = 0;

    char* res = calloc(tam + 2, sizeof(char));

    // Adiciona zeros à esquerda para igualar o tamanho das strings
    char* tmp1 = calloc(tam + 1, sizeof(char));
    char* tmp2 = calloc(tam + 1, sizeof(char));
    memset(tmp1, '0', tam);
    memset(tmp2, '0', tam);
    strcpy(tmp1 + (tam - strlen(str1)), str1);
    strcpy(tmp2 + (tam - strlen(str2)), str2);

    for (int i = tam - 1; i >= 0; i--) {
        sum = carry + (tmp1[i] - '0') + (tmp2[i] - '0');
        res[i + 1] = (sum % 10) + '0';
        carry = sum / 10;
    }

    if (carry) {
        res[0] = carry + '0';
        free(tmp1);
        free(tmp2);
        return res;
    } else {
        free(tmp1);
        free(tmp2);
        return res + 1;
    }
}

// Subtração de dois números representados por strings
char* sub(char* str1, char* str2) {
    int tam1 = strlen(str1);
    int tam2 = strlen(str2);
    int tam = max(tam1, tam2); 

    char* res = calloc((tam + 2), sizeof(char));
    memset(res, '0', tam + 1);

    int empresta = 0, i = tam1 - 1, j = tam2 - 1, k = tam;

    while (i >= 0 || j >= 0 || empresta) {
        int digito1 = (i >= 0) ? str1[i--] - '0' : 0;
        int digito2 = (j >= 0) ? str2[j--] - '0' : 0;
        digito2 += empresta;

        if (digito1 < digito2) {
            digito1 += 10;
            empresta = 1;
        } else {
            empresta = 0;
        }

        res[k--] = (digito1 - digito2) + '0';
    }

    while (*res == '0' && *(res + 1)) res++;

    return res; 
}

// Multiplica um número, representado por uma string, por uma potência de 10
char* potencia_de_10(const char* str, int potencia) {
    int tam = strlen(str);
    char* res = calloc(tam + potencia + 1, sizeof(char));

    strcpy(res, str);
    for (int i = 0; i < potencia; i++) {
        res[tam + i] = '0';
    }
    res[tam + potencia] = '\0';

    return res;
}

void liberatotal(char **str){
    free(*str);
    *str = NULL;
    return;
}

