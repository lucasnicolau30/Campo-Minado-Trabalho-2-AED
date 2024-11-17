#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "log.h"

FILE *logFile;  // Ponteiro global para o arquivo de log
int numeroJogada = 1;  // Contador de jogadas para registro no log

// Função para inicializar o log
void iniciaLog() {
    // Abre o arquivo de log para escrita (substitui conteúdo anterior)
    logFile = fopen("log.txt", "w");
    if (logFile == NULL) {  // Valida se o arquivo foi aberto com sucesso
        printf("Erro ao abrir o arquivo de log!\n");
        exit(1);  // Encerra o programa em caso de falha
    }
    registraCabecalho();  // Adiciona informações iniciais ao log
}

// Função para registrar o cabeçalho com data e hora
void registraCabecalho() {
    if (logFile == NULL) {  // Verifica se o log foi inicializado
        printf("Log não inicializado.\n");
        return;
    }

    time_t t;
    struct tm *tm_info;
    char dataHora[26];  // Buffer para armazenar a data e hora formatada

    time(&t);  // Obtém o tempo atual
    tm_info = localtime(&t);  // Converte o tempo para estrutura local
    strftime(dataHora, 26, "%Y-%m-%d %H:%M:%S", tm_info);  // Formata data/hora

    // Escreve a data, hora e uma linha separadora no log
    fprintf(logFile, "Data e hora do início: %s\n", dataHora);
    fprintf(logFile, "Histórico de jogo:\n");
    fprintf(logFile, "------------------------------------------------\n");
}

// Escreve a mensagem que aparece para o usuário no log em casos da jogada não ser válida
void registraMensagemLog(const char* mensagem) {
    if (logFile == NULL) {  // Verifica se o log foi inicializado
        printf("Log não inicializado.\n");
        return;
    }

    // Adiciona a mensagem e uma linha separadora no log
    fprintf(logFile, "%s\n", mensagem);
    fprintf(logFile, "------------------------------------------------\n");
}

// Função para registrar a jogada e a matriz após o floodFill
void registraJogada(int **mat, char **mascara, int n, int linha, int coluna) {
    if (logFile == NULL) {  // Verifica se o log foi inicializado
        printf("Log não inicializado.\n");
        return;
    }

    // Registra o número da jogada e a coordenada escolhida
    fprintf(logFile, "Jogada #%d\n", numeroJogada);
    fprintf(logFile, "Jogador escolheu a coordenada: %d %d\n", linha + 1, coluna + 1);

    // Escreve a matriz atualizada (máscara) no log
    fprintf(logFile, "Matriz após jogada (depois do floodFill):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mascara[i][j] == '#') {  // Representa células ocultas
                fprintf(logFile, "# ");
            } else {  // Representa células reveladas
                fprintf(logFile, "%c ", mascara[i][j]);
            }
        }
        fprintf(logFile, "\n");
    }

    fprintf(logFile, "------------------------------------------------\n");
    numeroJogada++;  // Incrementa o contador de jogadas
}

// Função para registrar o Game Over e a matriz original
void registraGameOver(int **mat, char **mascara, int n, int linha, int coluna) {
    if (logFile == NULL) {  // Verifica se o log foi inicializado
        printf("Log não inicializado.\n");
        return;
    }

    // Registra a última jogada antes da derrota
    fprintf(logFile, "Última jogada antes do Game Over: %d %d\n", linha + 1, coluna + 1);

    // Escreve a matriz original (campo minado) no log
    fprintf(logFile, "Game Over! Matrizes após a derrota:\n");
    fprintf(logFile, "Matriz original (campo minado):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == -1) {  // Representa minas
                fprintf(logFile, "%d ", mat[i][j]);
            } else {  // Representa contagens de minas adjacentes
                fprintf(logFile, " %d ", mat[i][j]);
            }
        }
        fprintf(logFile, "\n");
    }
    fprintf(logFile, "------------------------------------------------\n");
}

// Função para registrar a vitória e a matriz final(máscara)
void registraVitoria(char **mascara, int n) {
    if (logFile == NULL) {  // Verifica se o log foi inicializado
        printf("Log não inicializado.\n");
        return;
    }

    // Escreve a matriz final (máscara completamente revelada) no log
    fprintf(logFile, "Você venceu! Matrizes finais:\n");
    fprintf(logFile, "Matriz final (máscara):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(logFile, "%c ", mascara[i][j]);
        }
        fprintf(logFile, "\n");
    }
    fprintf(logFile, "------------------------------------------------\n");
}

// Função para fechar o log
void fechaLog() {
    if (logFile != NULL) {  // Fecha o arquivo de log, se aberto
        fclose(logFile);
        logFile = NULL;  // Reseta o ponteiro para evitar uso inválido
    }
}
