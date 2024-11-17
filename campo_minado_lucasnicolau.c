#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "log.h"

int main() {
    int nivel;
    int n = 0, minas = 0;

    // Pergunta ao usuário o nível de dificuldade
    while (1) { 
        printf("Escolha uma das dificuldades a seguir: 1 (facil), 2 (medio) ou 3 (dificil).\n");
        scanf("%d", &nivel);

        // Define a configuração da matriz e quantidade de minas(15% do número total de casas)
        if(nivel == 1) {
            n = 10; minas = 15; 
            break; 
        } 
        else if(nivel == 2) {
            n = 20; minas = 60; 
            break; 
        } 
        else if(nivel == 3) {
            n = 30; minas = 135; 
            break;
        } 
        else {
            printf("Dificuldade inválida! Tente novamente.\n");
            // Registra a mensagem de dificuldade inválida
            registraMensagemLog("Dificuldade inválida! Tente novamente.");
            continue; // Reinicia o loop para nova entrada
        }
    }

    // Inicia o log
    iniciaLog(); 

    // Alocação e inicialização da matriz original (campo minado) e máscara
    int **mat = alocaMatriz(n);
    inicializaMatriz(mat, n); // Inicializa a matriz com zeros
    adicionaMinas(mat, n, minas); // Adiciona minas e atualiza contagem adjacente

    char **mascara = alocaMascara(n);
    inicializaMascara(mascara, n); // Inicializa a máscara com '#'
    imprimeMascara(mascara, n); // Exibe a máscara inicial para o jogador

    printf("Bem-Vindo ao Jogo!! \n");

    int jogoAtivo = 1; // Controle do estado do jogo
    int numeroJogada = 1; // Número da jogada, usado no registro do log

    while(jogoAtivo) {
        printf("Digite as coordenadas dessa maneira: (linha, coluna): ");
        int linha, coluna;
        scanf("%d,%d", &linha, &coluna);
        linha--; // Ajusta para índice zero
        coluna--;

        // Verifica se as coordenadas estão fora dos limites da matriz
        if(linha < 0 || linha >= n || coluna < 0 || coluna >= n) {
            printf("Coordenadas inválidas! Tente novamente.\n");
            // Registra a mensagem de coordenadas inválidas
            registraMensagemLog("Coordenadas inválidas! Tente novamente.");
        } 
        else if(mascara[linha][coluna] != '#') { 
            // Verifica se a posição já foi revelada
            printf("Você já revelou essa posição! Tente outra.\n");
            // Registra a mensagem de posição já revelada
            registraMensagemLog("Você já revelou essa posição! Tente outra.");
        } 
        else {
            // Registra a jogada no log
            registraJogada(mat, mascara, n, linha, coluna);

            if(mat[linha][coluna] == MINA) { 
                // Se o jogador revela uma mina, o jogo termina
                imprimeMatriz(mat, n); // Exibe a matriz original
                printf("Game Over!\n");
                // Registra o Game Over no log com a última coordenada
                registraGameOver(mat, mascara, n, linha, coluna);
                break;
            }

            // Caso contrário, revela a célula usando Flood Fill
            floodFill(mat, mascara, linha, coluna, n);
            imprimeMascara(mascara, n); // Exibe a máscara atualizada

            // Verifica se todas as células não-mina foram reveladas
            int venceu = 1;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    if(mascara[i][j] == '#' && mat[i][j] != MINA) {
                        venceu = 0; // Ainda há células não reveladas
                        break;
                    }
                }
                if(!venceu) break;
            }

            if(venceu) { 
                // Se todas as células não-mina foram reveladas, jogador vence
                if(nivel == 1) {
                    printf("Agora que venceu no nível fácil, por que não jogar no médio?\n");
                } 
                else if(nivel == 2) {
                    printf("Agora que venceu no nível médio, por que não jogar no difícil?\n");
                } 
                else if(nivel == 3) {
                    printf("Impressionante!! Nem o nível mais difícil foi capaz de te parar. Espere novos níveis!\n");
                }
                // Registra a vitória no log
                registraVitoria(mascara, n);
                jogoAtivo = 0; // Termina o loop do jogo
            }
        }
    }

    // Libera a memória alocada para a matriz e a máscara
    for(int i = 0; i < n; i++) {
        free(mat[i]);
        free(mascara[i]);
    }
    free(mat);
    free(mascara);

    // Fecha o log
    fechaLog(); 

    return 0; // Termina o programa
}
