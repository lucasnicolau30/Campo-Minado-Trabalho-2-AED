# Trabalho-2-AED
# Jogo de Campo Minado em C

Este projeto implementa o clássico jogo **Campo Minado** utilizando a linguagem C. O jogo consiste em um campo de células ocultas, onde o jogador deve "abrir" células sem ativar minas, com base em dicas fornecidas pelas células adjacentes. O jogo registra as jogadas e as interações, além de fornecer um log detalhado das ações realizadas.

## Funcionalidades

- **Campo Minado**: O campo é gerado com minas aleatórias e as células adjacentes a cada mina são preenchidas com o número de minas ao redor.
- **Máscara**: Uma máscara é usada para mostrar ao jogador o estado do jogo, com células não reveladas indicadas por `#`.
- **Flood Fill**: Células adjacentes com valor `0` são automaticamente reveladas, permitindo uma experiência mais fluida.
- **Registro em Log**: Cada jogada do jogador é registrada em um arquivo de log, incluindo a data e hora, a jogada realizada, o estado do campo após a jogada, e as mensagens de erro.
- **Vitória e Derrota**: O jogo termina com vitória quando todas as células seguras são abertas ou derrota quando uma mina é ativada. O log é atualizado com a matriz final.

## Estrutura do Código

O código é composto por vários arquivos que lidam com diferentes aspectos do jogo:

1. **`matriz.h` e `matriz.c`**: Responsáveis pela manipulação das matrizes que representam o campo minado e a máscara do jogo.
   - Alocação de memória para a matriz e a máscara.
   - Inicialização do campo e da máscara.
   - Adição de minas aleatórias e contagem de minas adjacentes.
   - Função `floodFill` para revelar células adjacentes quando um valor `0` é clicado.
   
2. **`log.h` e `log.c`**: Gerenciam o registro das jogadas e do estado do jogo em um arquivo de log.
   - Registra cada jogada, o campo após a jogada, e mensagens de erro.
   - Registra a vitória e a derrota, junto com a matriz final.
   
3. **`main.c`**: Contém a lógica principal do jogo e a interação com o jogador.

## Como Jogar

1. Compile o código utilizando o comando abaixo no terminal. **Não use IDEs**, pois o comando de compilação é para ser executado no terminal:

   ```bash
   gcc lucas_nicolau.c matriz.c log.c -o campo_minado -lm
