#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//feito pelo jhonatan. sabe muito o menino
//o trabalho teoricamente nao precisa prever entrada mal feita nem dar um suporte pro usuario, mas fiz por vontade de brincar com o negocio aq tb

//enunciado no pdf:
/*Sua tarefa é implementar um soletra para o terminal que tenha os seguintes comandos:
• inicio [lista com 7 letras separadas por espaço]: recebe como entrada 7 le-
tras, sendo a primeira a letra aquela que deve estar presente em todas as palavras
• palavra [entrada]: recebe uma palavra que será validada, isto é, se atende aos
critérios como uma resposta válida. Se for uma resposta válida, será impressa a men-
sagem “sucesso + 1”, caso contrário, será impressa a mensagem “palavra invalida”.
Caso o usuário tenha terminado de listar todas as palavras válidas, então a mensagem
“parabens! voce encontrou todas as palavras” deve ser mostrada e o programa é encer-
rado
• progresso: lista a quantidade de palavras identificadas e faltantes, agrupadas por
número de letras
• solucao: a lista com todas as palavras que ainda não foram identificadas é impressa
(agrupadas por número de letras) e o programa é encerrado
Um arquivo auxiliar com a lista de palavras válidas será disponibilizado e também parte do
projeto no run.codes. Consideramos válidas apenas palavras com 4 ou mais letras. Todas as
entradas serão em letra maiúscula.*/

#define MAX_PALAVRAS 244770     // Limite para o número máximo de palavras válidas
#define MAX_TAMANHO_PALAVRA 20  // Tamanho máximo de cada palavra

// Estrutura para armazenar as palavras válidas
char palavras_validas[MAX_PALAVRAS][MAX_TAMANHO_PALAVRA]; // Guarda as palavras que conterão as letra obrigatoria e as iniciais 
int total_palavras_validas = 0;                           // Quantidade de palavras carregadas 
int palavras_encontradas[MAX_PALAVRAS] = {0};             // Flag para palavras encontradas (0 não encotrada 1 encotrada)

char obrigatoria;
char letras[7];
int total_palavras[5] = {0};      // Total de palavras com 4, 5, 6, 7 e 8 letras
int progresso_palavras[5] = {0};  // Total de palavras corretas com 4, 5, 6, 7 e 8 letras (quanto o usuario já acertou)


// Função de busca binária
int busca_binaria(const char *palavra) {
    int esquerda = 0;
    int direita = total_palavras_validas - 1;
    
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int cmp = strcmp(palavra, palavras_validas[meio]);
        
        if (cmp == 0) {
            return meio;  // Palavra encontrada, retorna o índice
        } else if (cmp < 0) {
            direita = meio - 1;
        } else {
            esquerda = meio + 1;
        }
    }
    return -1;  // Palavra não encontrada
}

// Função para verificar se a palavra contém a letra obrigatória
bool verifica_letra_obrigatoria (const char *palavra) {
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (palavra[i] == obrigatoria) { // Verifica se a letra obrigatória está na palavra
            return true;
        }
    }
    return false;
}

// Função para verificar se uma palavra pode ser formada com as letras iniciais
bool verifica_letras(const char *palavra) {
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (strchr(letras, palavra[i]) == NULL) { // Se a letra não estiver em `letras`
            return false;
        }
    }
    return true;
}

// Função para carregar palavras válidas a partir do arquivo, considerando apenas palavras com letras permitidas
int carregar_palavras(const char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return 0;
    }

    char palavra[MAX_TAMANHO_PALAVRA];
    total_palavras_validas = 0;

    while (fscanf(file, "%s", palavra) != EOF) {
        if (verifica_letra_obrigatoria(palavra) && verifica_letras(palavra)) {  // Verifica se a palavra é composta apenas pelas letras permitidas
            int len = strlen(palavra);
            if (len >= 4 && len <= 8) {  // Considera palavras de 4 a 8 letras
                strncpy(palavras_validas[total_palavras_validas], palavra, MAX_TAMANHO_PALAVRA);
                total_palavras_validas++;
                total_palavras[len - 4]++;  // Incrementa o contador correspondente (4 letras => índice 0)
            }
        }
    }

    fclose(file);
    return 1;
}

// Função para inicializar o jogo com a letra obrigatória e as letras
void inicio(char obrig, char* letras_iniciais) {
    obrigatoria = obrig;
    letras[0] = obrigatoria;  // Coloca a letra obrigatória no início
    strncpy(letras+1, letras_iniciais, 6);  // Copia as 7 letras a partir da posição 1
    carregar_palavras("valid_words.txt");
}

// Função para verificar se uma palavra é válida
int palavra(char* entrada) {
    // Verifica se a palavra contém a letra obrigatória e todas as letras permitidas
    if (!verifica_letra_obrigatoria(entrada) || !verifica_letras(entrada)) {
        printf("palavra invalida\n");
        return 0;
    }
    
    // Busca a palavra na lista de palavras válidas
    int indice = busca_binaria(entrada);
    if (indice != -1) {  // Palavra foi encontrada
        if (strcmp(entrada, palavras_validas[indice]) == 0) {
            if (palavras_encontradas[indice] == 0) {  // Verifica se já não foi encontrada
                printf("sucesso + 1\n");
                palavras_encontradas[indice] = 1;
                progresso_palavras[strlen(entrada) - 4]++;
                return 1;
            } else {
                printf("palavra ja encontrada\n");
                return 1;
            }
        }   
    }
    printf("palavra invalida\n");
    return 0;
}

// Função para mostrar o progresso
void progresso() {
    printf("progresso atual:\n");
    for (int i = 0; i < 5; i++) {
        int faltando = total_palavras[i] - progresso_palavras[i];
        printf("(%d letras) %d palavra(s) encontrada(s) / %d palavra(s) faltando\n", i + 4, progresso_palavras[i], faltando);
    }
}

// Função para mostrar a solução final com as palavras restantes
void solucao() {
    printf("para encerrar o jogo estavam faltando as palavras: \n");

    // Exibir palavras de acordo com o número de letras
    for (int len = 4; len <= 8; len++) {
        printf("(%d letras) ", len);

        // Percorrer as palavras válidas e imprimir as que têm o tamanho adequado
        int encontrou_palavra = 0;
        for (int i = 0; i < total_palavras_validas; i++) {
            if (strlen(palavras_validas[i]) == len) {
                if (encontrou_palavra) printf(", ");
                printf("%s", palavras_validas[i]);
                encontrou_palavra = 1;
            }
        }
        printf("\n");
    }

    printf("fim!\n");
}

// Função principal com entrada interativa do usuário
int main() {
    char comando[50];
    char entrada[20];
    int flag_erro = 0, flag_inicio = 0; //adiçoes minhas (daniel). nao precisava pra entregar o trabalho, assim como comentei la em cima fiz só pra brincar 
    printf("bem vindo(a) ao nosso programa de adivinhação de palavras! \npara entender o funcionamento, digite 'ajuda'\npara entender os comandos, digite 'comandos'\n");
    // ^ adição minha (daniel): só bobeira pra quem quiser brincar com o bixo ^

    while (1) {
        flag_erro = 0;
        scanf("%s", comando);

        if (strcmp(comando, "inicio") == 0) {  // Lê a letra obrigatória e as outras letras
            flag_inicio = 1; //adiçao minha (daniel): quando inicializa ele permite fazer outras coisas; se nao, nao deixa nada
            char letras_ini[7];
            // Lê a letra obrigatória
            scanf(" %c", &obrigatoria);
            
            // Lê as outras letras uma por uma
            for(int i = 0; i < 6; i++) {  // Lê 6 letras adicionais
                scanf(" %c", &letras_ini[i]);
            }
            letras_ini[6] = '\0';  // Adiciona o terminador de string
            
            inicio(obrigatoria, letras_ini);
        } 
        else if (strcmp(comando, "palavra") == 0 && flag_inicio) { // Lê a palavra a ser verificada
            scanf(" %s", entrada);
            palavra(entrada);
        } 
        else if (strcmp(comando, "progresso") == 0 && flag_inicio) {
            progresso();
        } 
        else if (strcmp(comando, "solucao") == 0 && flag_inicio) {
            solucao();
            break;
        } 
        else if (strcmp(comando, "comandos") == 0) { //adiçao minha (daniel): mais bobeira pra deixar ele bonitin de usar
            printf("comandos do programa:\n");
            printf("-para inicializar, digite 'inicio' e, em seguida, as 7 letras (em maiúsculo e espaçadas entre si) que podem compor sua palavra\n");
            printf("-para registrar uma tentativa, digite 'palavra' e, em seguida, sua palavra de tentativa em maiúsculo\n");
            printf("-para verificar seu progresso no jogo, digite 'progresso'\n");
            printf("-para finalizar o jogo e obter a resposta, digite 'solucao'\n");
            continue;
        }
        else if (strcmp(comando, "ajuda") == 0) { //adiçao minha (daniel): mais bobeira, denovo
            printf("nesse programa, seu objetivo é adivinhar todas as palavras que podem ser formadas por certas letras específicas que você, usuário, escolher\n");
            printf("o programa levará em conta as 7 letras de entrada fornecidas na inicialização e acompanhará seu progresso\n");
            printf("detalhe importante: a primeira letra da inicialização deve estar obrigatoriamente na sua palavra de tentativa\n");
            continue;
        }
        else {
            printf("Comando desconhecido: %s\n", comando);
            flag_erro = 1; //adição minha (daniel): pra quando o comando é invalido poe a flag aq pra nao printar a mensagem parabens e dar break
        }

        int contA = 0, contB = 0;
        for (int j=0 ; j<5 ; j++){
            contA += total_palavras[j];
            contB += progresso_palavras[j]; 
        }

        if (contA == 0) { //adição minha (daniel): mais bobeira
            printf("nenhuma palavra válida encontrada com as letras fornecidas\n");
            break;
        }

        if (contA == contB && !flag_erro){
            printf("parabens! voce encontrou todas as palavras");
            break;
        }

        if(!flag_inicio) //adiçao minha (daniel): mais bobeira
            printf("o programa ainda nao foi inicializado! digite 'comandos' para casos de dúvidas do funcionamento do programa\n");
    }
    
    return 0;
}