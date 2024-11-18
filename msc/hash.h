#ifndef OIE
    #define OIE

    #define TAM 1000 //tamanho maximo da tabela

    typedef struct no_ NO;
    typedef struct tabela_ TABELA;

    int hash(int n);
    TABELA *inicializa();
    void insere(TABELA *t, int valor);
    int busca(TABELA *t, int chave);
    void printatabela(TABELA *t);
    int msc(TABELA *t);

    int sort(const void *a, const void *b);
    int maximaSubsequenciaSort(int arr[], int tam);

#endif