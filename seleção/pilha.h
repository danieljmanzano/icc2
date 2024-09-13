#ifndef PILHAEHNOIS
    #define PILHAEHNOIS
    
    typedef struct jogador JOGADOR;
    typedef struct pilha PILHA;

    PILHA *pilha_criar();
    void pilha_apagar(PILHA *p);
    void pilha_inserir(PILHA *p, JOGADOR *j);
    JOGADOR *pilha_remover(PILHA *p);
    int pilha_vazia(PILHA *p);

    JOGADOR *jogador_criar(char *nome, int over);
    int jogador_ponto(JOGADOR *jogador);
    char *jogador_nome(JOGADOR *jogador);
#endif