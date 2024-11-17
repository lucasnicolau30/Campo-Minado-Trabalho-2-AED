#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para alocar a matriz de inteiros (campo minado)
int** alocaMatriz(int n){
    int **mat = malloc(n * sizeof(int *)); // Aloca memória para as linhas
    if (mat == NULL){
        printf("Erro na alocação de memória para a matriz\n");
        exit(1); // Finaliza o programa em caso de erro
    }
    for(int i = 0; i < n; i++){
        mat[i] = malloc(n * sizeof(int)); // Aloca memória para cada linha
        if (mat[i] == NULL){
            printf("Erro na alocação de memória para a linha %d da matriz\n", i);
            exit(1); // Finaliza o programa em caso de erro
        }
    }
    return mat; // Retorna o ponteiro para a matriz alocada
}

// Função para alocar a matriz auxiliar (máscara do campo minado , qual o usuário irá ver ao jogar)
char** alocaMascara(int n){
    char **mascara = malloc(n * sizeof(char *)); // Aloca memória para as linhas
    if (mascara == NULL){
        printf("Erro na alocação de memória para a máscara\n");
        exit(1); // Finaliza o programa em caso de erro
    }
    for(int i = 0; i < n; i++){
        mascara[i] = malloc(n * sizeof(char)); // Aloca memória para cada linha
        if (mascara[i] == NULL){
            printf("Erro na alocação de memória para a linha %d da máscara\n", i);
            exit(1); // Finaliza o programa em caso de erro
        }
    }
    return mascara; // Retorna o ponteiro para a máscara alocada
}

// Função para inicializar a matriz com 0 (campo minado original)
void inicializaMatriz(int **mat, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            mat[i][j] = 0; // Inicializa cada célula com 0
        }
    }
}

// Função para inicializar a máscara (matriz auxiliar) com '#'
void inicializaMascara(char **mascara, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            mascara[i][j] = '#'; // Inicializa cada célula com '#'
        }
    }
}

// Função para atualizar a contagem de minas adjacentes
void atualizaContagemAdjacente(int **mat, int n){
    for(int x = 0; x < n; x++){
        for(int y = 0; y < n; y++){
            if(mat[x][y] == MINA){ 
                continue; // Ignora células que já possuem mina
            }

            int acum = 0; // Contador de minas adjacentes
            
            // Verifica as posições adjacentes
            if(x + 1 < n && mat[x + 1][y] == MINA) acum++; // Célula abaixo
            if(x - 1 >= 0 && mat[x - 1][y] == MINA) acum++; // Célula acima
            if(y + 1 < n && mat[x][y + 1] == MINA) acum++; // Célula à direita
            if(y - 1 >= 0 && mat[x][y - 1] == MINA) acum++; // Célula à esquerda
            if(x - 1 >= 0 && y - 1 >= 0 && mat[x - 1][y - 1] == MINA) acum++; // Diagonal superior esquerda
            if(x - 1 >= 0 && y + 1 < n && mat[x - 1][y + 1] == MINA) acum++; // Diagonal superior direita
            if(x + 1 < n && y - 1 >= 0 && mat[x + 1][y - 1] == MINA) acum++; // Diagonal inferior esquerda
            if(x + 1 < n && y + 1 < n && mat[x + 1][y + 1] == MINA) acum++; // Diagonal inferior direita

            mat[x][y] = acum; // Atualiza a célula com o número de minas adjacentes
        }
    }
}

// Função para adicionar as minas na matriz
void adicionaMinas(int **mat, int n, int minas){
    int cont = 0; // Contador de minas adicionadas
    srand(time(NULL)); // Inicializa o gerador de números aleatórios a partir do horário que o usuário iniciou o jogo
    while(cont < minas){
        int x = rand() % n; // Gera coordenada aleatória
        int y = rand() % n; // Gera coordenada aleatória
        if(mat[x][y] != MINA){ // Verifica se a célula já não contém mina
            mat[x][y] = MINA; // Adiciona a mina
            cont++;
        }
    }
    atualizaContagemAdjacente(mat, n); // Atualiza o campo após adicionar as minas
}

// Função para imprimir a matriz original (usado quando o jogador perde)
void imprimeMatriz(int **mat, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(mat[i][j] == -1){
                printf("%d ", mat[i][j]); // Exibe as minas como -1 
            } else {
                printf(" %d ", mat[i][j]); // Exibe os outros valores
            }
        }
		 // Há esse if e else para manter a matriz totalmente reta ao exibir as coordenadas com -1 
        printf("\n");
    }
}

// Função para imprimir a máscara (exibida para o jogador)
void imprimeMascara(char **mascara, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%c ", mascara[i][j]); // Exibe o conteúdo da máscara
        }
        printf("\n");
    }
}

// Função de Flood Fill para revelar as células adjacentes quando valor 0 é clicado
void floodFill(int **mat, char **mascara, int x, int y, int n){
    if(x < 0 || x >= n || y < 0 || y >= n || mascara[x][y] != '#'){
        return; // Retorna se a célula for inválida ou já revelada
    }

    mascara[x][y] = '0' + mat[x][y]; // Revela a célula atual

    if(mat[x][y] == 0){ // Se a célula for 0, continua o Flood Fill
        floodFill(mat, mascara, x - 1, y, n); // Célula acima
        floodFill(mat, mascara, x + 1, y, n); // Célula abaixo
        floodFill(mat, mascara, x, y - 1, n); // Célula à esquerda
        floodFill(mat, mascara, x, y + 1, n); // Célula à direita
        floodFill(mat, mascara, x - 1, y - 1, n); // Diagonal superior esquerda
        floodFill(mat, mascara, x - 1, y + 1, n); // Diagonal superior direita
        floodFill(mat, mascara, x + 1, y - 1, n); // Diagonal inferior esquerda
        floodFill(mat, mascara, x + 1, y + 1, n); // Diagonal inferior direita
    }
}
