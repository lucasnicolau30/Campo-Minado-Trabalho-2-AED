#ifndef LOG_H
#define LOG_H

#include <stdio.h>

// Funções para manipulação do log
void iniciaLog();  // Abre o arquivo de log para escrita e inicia o cabeçalho
void registraCabecalho();  // Adiciona a data e hora de início no log
void registraJogada(int **mat, char **mascara, int n, int linha, int coluna);  // Registra uma jogada no log, incluindo a matriz atualizada
void registraMensagemLog(const char* mensagem);  // Escreve a mensagem que aparece para o usuário no log em casos da jogada não ser válida
void registraGameOver(int **mat, char **mascara, int n, int linha, int coluna);  // Registra a derrota e a matriz original no log , assim como aparece para o usuário no terminal
void registraVitoria(char **mascara, int n);  // Registra a vitória e a matriz final(máscara) no log , assim como aparece para o usuário no terminal
void fechaLog();  // Fecha o arquivo de log

#endif
