# Jogo de Campo Minado em C

Este projeto implementa o clássico jogo **Campo Minado** utilizando a linguagem C. O jogo consiste em um campo de células ocultas, onde o jogador deve "abrir" células sem ativar minas, com base em dicas fornecidas pelas células adjacentes. O jogo registra as jogadas e as interações, além de fornecer um log detalhado das ações realizadas.

## Funcionalidades

- **Campo Minado**: O campo é gerado com minas aleatórias e as células adjacentes a cada mina são preenchidas com o número de minas ao redor.
- **Máscara**: Uma máscara é usada para mostrar ao jogador o estado do jogo, com células não reveladas indicadas por `#`.
- **Flood Fill**: Células adjacentes com valor `0` são automaticamente reveladas, permitindo uma experiência de jogo mais fluida.
- **Registro em Log**: Cada jogada do jogador é registrada em um arquivo de log, incluindo:
  - A data e hora da jogada
  - A jogada realizada
  - O estado do campo após a jogada
  - Mensagens de erro (em caso de jogadas inválidas)
- **Vitória e Derrota**: O jogo termina com **vitória** quando todas as células seguras são abertas ou com **derrota** quando uma mina é ativada. O log é atualizado com a matriz final de ambos os casos.

### Níveis de Dificuldade

O jogo possui três níveis de dificuldade:

- **Fácil**:
  - Tamanho do campo: 10x10
  - Número de minas: 15
- **Médio**:
  - Tamanho do campo: 20x20
  - Número de minas: 60
- **Difícil**:
  - Tamanho do campo: 30x30
  - Número de minas: 135

## Estrutura do Código

O código é composto por vários arquivos que lidam com diferentes aspectos do jogo:

### `matriz.h` e `matriz.c`

Estes arquivos são responsáveis pela manipulação das matrizes que representam o campo minado e a máscara do jogo.

- **Alocação de memória** para a matriz e a máscara.
- **Inicialização do campo** e da máscara.
- **Adição de minas aleatórias** e contagem de minas adjacentes.
- **Função `floodFill`**: Revela células adjacentes com valor `0` quando clicadas.

### `log.h` e `log.c`

Estes arquivos gerenciam o registro das jogadas e do estado do jogo em um arquivo de log.

- **Registra cada jogada**, incluindo a matriz após a jogada e mensagens de erro.
- **Registra a vitória** e a derrota, com a matriz final e as coordenadas do campo.

### `main.c`

Contém a lógica principal do jogo e a interação com o jogador. O jogador escolhe a dificuldade, faz as jogadas e o programa interage com o jogador revelando células e atualizando o campo.

## Como Jogar

### Compilação

Compile o código utilizando o comando abaixo no terminal. **Não use IDEs**, pois o comando de compilação deve ser executado diretamente no terminal:

```bash
gcc lucas_nicolau.c matriz.c log.c -o campo_minado -lm
./campo_minado

Essa será a visão do jogo:
Escolha a dificuldade do jogo: (facil, medio ou dificil)
facil

# # # # # # # # # # 
# # # # # # # # # # 
# # # # # # # # # # 
# # # # # # # # # # 
# # # # # # # # # # 
# # # # # # # # # # 
# # # # # # # # # # 
# # # # # # # # # # 
# # # # # # # # # # 
# # # # # # # # # # 

Bem-vindo ao Jogo!!

Digite as coordenadas (linha, coluna): 1,1
0 1 1 # # # # # # 
1 2 2 # # # # # # 
...

Digite as coordenadas (linha, coluna): 2,2
0 1 1 # # # # # # 
1 2 2 # # # # # # 
...

Você encontrou uma mina! Game Over.

Exemplo do log:
Data e hora do início: 2024-11-17 14:30:00
Histórico de jogo:
------------------------------------------------
Jogada #1
Jogador escolheu a coordenada: 1 1
Matriz após jogada (depois do floodFill):
# # # # # 
# 0 1 1 # 
# 1 2 2 # 
# # # # # 
# # # # # 
------------------------------------------------

Jogada #2
Jogador escolheu a coordenada: 2 2
Matriz após jogada (depois do floodFill):
# # # # # 
# 0 1 1 # 
# 1 2 2 # 
# # # # # 
# # # # # 
------------------------------------------------

Game Over! Matrizes após a derrota:
Matriz original (campo minado):
-1 0 0 0 0 
0 -1 0 0 0 
0 1 2 -1 0 
0 0 0 1 0 
0 0 0 0 0 
------------------------------------------------
