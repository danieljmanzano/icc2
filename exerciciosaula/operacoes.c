#include <stdio.h>
#include <stdlib.h>

//digito o numero de operaçoes pra fazer, a letra da operaçao (P == potencia, I == inverte, S == soma) e depois os numeros envolvidos na operaçao (varia em cada uma)
//feito pelo kevin (peguei so pra testar pq no runcodes nao ta saindo certo por algum motivo). dei uns retoques pra ficar bonito e passar no runcodes, mas a logica eu nao fiz nada nao

int pot(int base, int expoente) //potencia
{
    int ac;
    if(expoente == 0)
    {
        return 1;
    }
    else
    {
        return base*(pot(base, expoente - 1));
    }
}

int sum(int *vet, int tam) //soma
{
    if(tam == 0)
    {
        return 0;
    }
    else
    {
        return vet[0] + sum(vet+1, tam-1);
    }
}

void inv(int *vet, int left, int right, int tam) //inverte
{
    int aux;
    if(tam == 0 || tam == 1)
    {
        return;
    }
    else
    {
        aux = vet[left];
        vet[left] = vet[right];
        vet[right] = aux;
        inv(vet, left + 1, right - 1, tam -2);
        return;
    }
}

int main()
{
    int *vet;
    int n;
    int a;
    char c;
    int base;
    int expoente;
    scanf("%d", &n);
    for(int i=0;i<n;i++)
    {
        scanf(" %c", &c);
        if(c == 80) //P == 80
        {
            scanf("%d %d", &base, &expoente);
            printf("%d\n", pot(base, expoente));
        }
        else if(c == 83) //S == 83
        {
            scanf("%d", &a); //recebe quantos numeros vao estar no bagulho
            vet = (int *) malloc (a*sizeof(int));
            for(int j=0;j<a;j++)
            {
                scanf("%d", &vet[j]);
            }
            printf("%d\n", sum(vet, a));
            free(vet);
        }
        else if(c == 73) //I == 73
        {
            scanf("%d", &a); //tambem recebe quantos numeros vao ter
            vet = (int *) malloc (a*sizeof(int));
            for(int j=0;j<a;j++)
            {
                scanf("%d", &vet[j]);
            }
            inv(vet, 0, a-1, a);
            for(int j=0;j<a-1;j++)
            {
                printf("%d ", vet[j]);
            }
            printf("%d\n", vet[a-1]);
            free(vet);
        }
    }
}