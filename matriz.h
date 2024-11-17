#ifndef MATRIZ_H
#define MATRIZ_H

#define MINA -1 // Define o valor que representa uma mina no campo

// Função para alocar a matriz de inteiros (campo minado)
int** alocaMatriz(int n);
//retorna o ponteiro para a matriz alocada

// Função para alocar a matriz auxiliar (máscara do campo minado)
char** alocaMascara(int n);
//retorna o ponteiro para a matriz alocada

// Função para inicializar a matriz com 0 (campo minado original)
void inicializaMatriz(int **mat, int n);

// Função para inicializar a máscara (matriz auxiliar) com '#'
void inicializaMascara(char **mascara, int n);
// Matriz essa que o usário verá durante o jogo

// Função para atualizar a contagem de minas adjacentes , chamada após as minas serem adicionadas na matriz original
void atualizaContagemAdjacente(int **mat, int n);
// os valores com 0 em que hajam mina(s) próximas serão substituídos pela quantidade de minas adjacentes 

// Função para adicionar as minas na matriz
void adicionaMinas(int **mat, int n, int minas);
// Matriz original que irá receber as minas e os valores com 0 em que a mina será aleatoriamnte colocado será substituído por -1

// Função para imprimir a matriz original (usado quando o jogador perde)
void imprimeMatriz(int **mat, int n);

// Função para imprimir a máscara (exibida para o jogador)
void imprimeMascara(char **mascara, int n);

// Função de Flood Fill para revelar as células adjacentes quando valor 0 é clicado 
void floodFill(int **mat, char **mascara, int x, int y, int n);
// Retorna esses novos valores para a matriz máscara(repassada para o usuário)

#endif
