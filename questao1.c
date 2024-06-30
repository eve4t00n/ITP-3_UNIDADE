//Jogo da Velha
#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 3

typedef struct {
    char **tabuleiro;
    char jogador1;
    char jogador2;
} Jogo;

void inicializarTabuleiro(Jogo *jogo);
void liberarTabuleiro(Jogo *jogo);
void imprimirTabuleiro(const Jogo *jogo);
int verificarVencedor(const Jogo *jogo);
int movimentosRestantes(const Jogo *jogo);
int avaliar(const Jogo *jogo);
int minimax(Jogo *jogo, int profundidade, int maximizar);
void jogadaComputador(Jogo *jogo);
void jogadaJogador(Jogo *jogo, char jogador);
void mapearEscolhaParaCoordenadas(int escolha, int *linha, int *coluna);

void inicializarTabuleiro(Jogo *jogo) {
    jogo->tabuleiro = (char **)malloc(TAMANHO * sizeof(char *));
    for (int i = 0; i < TAMANHO; i++) {
        jogo->tabuleiro[i] = (char *)malloc(TAMANHO * sizeof(char));
        for (int j = 0; j < TAMANHO; j++) {
            jogo->tabuleiro[i][j] = ' ';
        }
    }
}

void liberarTabuleiro(Jogo *jogo) {
    for (int i = 0; i < TAMANHO; i++) {
        free(jogo->tabuleiro[i]);
    }
    free(jogo->tabuleiro);
}

void imprimirTabuleiro(const Jogo *jogo) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (jogo->tabuleiro[i][j] == ' ') {
                printf("%d", i * TAMANHO + j + 1);
            } else {
                printf("%c", jogo->tabuleiro[i][j]);
            }
            if (j < TAMANHO - 1) printf("|");
        }
        printf("\n");
        if (i < TAMANHO - 1) printf("-----\n");
    }
}

int verificarVencedor(const Jogo *jogo) {
    for (int i = 0; i < TAMANHO; i++) {
        if (jogo->tabuleiro[i][0] == jogo->tabuleiro[i][1] && jogo->tabuleiro[i][1] == jogo->tabuleiro[i][2]) {
            if (jogo->tabuleiro[i][0] != ' ') {
                return jogo->tabuleiro[i][0] == jogo->jogador1 ? 1 : -1;
            }
        }
    }

    for (int j = 0; j < TAMANHO; j++) {
        if (jogo->tabuleiro[0][j] == jogo->tabuleiro[1][j] && jogo->tabuleiro[1][j] == jogo->tabuleiro[2][j]) {
            if (jogo->tabuleiro[0][j] != ' ') {
                return jogo->tabuleiro[0][j] == jogo->jogador1 ? 1 : -1;
            }
        }
    }

    if (jogo->tabuleiro[0][0] == jogo->tabuleiro[1][1] && jogo->tabuleiro[1][1] == jogo->tabuleiro[2][2]) {
        if (jogo->tabuleiro[0][0] != ' ') {
            return jogo->tabuleiro[0][0] == jogo->jogador1 ? 1 : -1;
        }
    }

    if (jogo->tabuleiro[0][2] == jogo->tabuleiro[1][1] && jogo->tabuleiro[1][1] == jogo->tabuleiro[2][0]) {
        if (jogo->tabuleiro[0][2] != ' ') {
            return jogo->tabuleiro[0][2] == jogo->jogador1 ? 1 : -1;
        }
    }

    return movimentosRestantes(jogo) ? 0 : 2;
}

int movimentosRestantes(const Jogo *jogo) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (jogo->tabuleiro[i][j] == ' ') return 1;
        }
    }
    return 0;
}

int avaliar(const Jogo *jogo) {
    for (int linha = 0; linha < TAMANHO; linha++) {
        if (jogo->tabuleiro[linha][0] == jogo->tabuleiro[linha][1] && jogo->tabuleiro[linha][1] == jogo->tabuleiro[linha][2]) {
            if (jogo->tabuleiro[linha][0] == jogo->jogador2) return +10;
            else if (jogo->tabuleiro[linha][0] == jogo->jogador1) return -10;
        }
    }

    for (int coluna = 0; coluna < TAMANHO; coluna++) {
        if (jogo->tabuleiro[0][coluna] == jogo->tabuleiro[1][coluna] && jogo->tabuleiro[1][coluna] == jogo->tabuleiro[2][coluna]) {
            if (jogo->tabuleiro[0][coluna] == jogo->jogador2) return +10;
            else if (jogo->tabuleiro[0][coluna] == jogo->jogador1) return -10;
        }
    }

    if (jogo->tabuleiro[0][0] == jogo->tabuleiro[1][1] && jogo->tabuleiro[1][1] == jogo->tabuleiro[2][2]) {
        if (jogo->tabuleiro[0][0] == jogo->jogador2) return +10;
        else if (jogo->tabuleiro[0][0] == jogo->jogador1) return -10;
    }

    if (jogo->tabuleiro[0][2] == jogo->tabuleiro[1][1] && jogo->tabuleiro[1][1] == jogo->tabuleiro[2][0]) {
        if (jogo->tabuleiro[0][2] == jogo->jogador2) return +10;
        else if (jogo->tabuleiro[0][2] == jogo->jogador1) return -10;
    }

    return 0;
}

int minimax(Jogo *jogo, int profundidade, int maximizar) {
    int pontuacao = avaliar(jogo);
    if (pontuacao == 10) return pontuacao - profundidade;
    if (pontuacao == -10) return pontuacao + profundidade;
    if (!movimentosRestantes(jogo)) return 0;

    if (maximizar) {
        int melhor = -10;
        for (int i = 0; i < TAMANHO; i++) {
            for (int j = 0; j < TAMANHO; j++) {
                if (jogo->tabuleiro[i][j] == ' ') {
                    jogo->tabuleiro[i][j] = jogo->jogador2;
                    melhor = (melhor > minimax(jogo, profundidade + 1, 0)) ? melhor : minimax(jogo, profundidade + 1, 0);
                    jogo->tabuleiro[i][j] = ' ';
                }
            }
        }
        return melhor;
    } else {
        int melhor = 10;
        for (int i = 0; i < TAMANHO; i++) {
            for (int j = 0; j < TAMANHO; j++) {
                if (jogo->tabuleiro[i][j] == ' ') {
                    jogo->tabuleiro[i][j] = jogo->jogador1;
                    melhor = (melhor < minimax(jogo, profundidade + 1, 1)) ? melhor : minimax(jogo, profundidade + 1, 1);
                    jogo->tabuleiro[i][j] = ' ';
                }
            }
        }
        return melhor;
    }
}

void jogadaComputador(Jogo *jogo) {
    int melhorValor = -10;
    int linha = -1, coluna = -1;

    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (jogo->tabuleiro[i][j] == ' ') {
                jogo->tabuleiro[i][j] = jogo->jogador2;
                int valorMovimento = minimax(jogo, 0, 0);
                jogo->tabuleiro[i][j] = ' ';
                if (valorMovimento > melhorValor) {
                    linha = i;
                    coluna = j;
                    melhorValor = valorMovimento;
                }
            }
        }
    }

    jogo->tabuleiro[linha][coluna] = jogo->jogador2;
}

void jogadaJogador(Jogo *jogo, char jogador) {
    int escolha, linha, coluna;
    do {
        printf("Jogador %c, escolha uma posição (1-9): ", jogador);
        scanf("%d", &escolha);
        mapearEscolhaParaCoordenadas(escolha, &linha, &coluna);
    } while (escolha < 1 || escolha > 9 || jogo->tabuleiro[linha][coluna] != ' ');

    jogo->tabuleiro[linha][coluna] = jogador;
}

void mapearEscolhaParaCoordenadas(int escolha, int *linha, int *coluna) {
    *linha = (escolha - 1) / TAMANHO;
    *coluna = (escolha - 1) % TAMANHO;
}

int main() {
    int modo;
    Jogo jogo;
    jogo.jogador1 = 'X';
    jogo.jogador2 = 'O';
    inicializarTabuleiro(&jogo);
    puts("Escolha o modo de Jogo:\n1: Jogador Vs Maquina\n2: Jogador Vs Jogador\n");
    scanf("%d", &modo);

    if (modo == 1) {
        while (1) {
            imprimirTabuleiro(&jogo);
            jogadaJogador(&jogo, jogo.jogador1);
            if (verificarVencedor(&jogo) != 0) {
                break;
            }
            jogadaComputador(&jogo);
            if (verificarVencedor(&jogo) != 0) {
                break;
            }
        }
    } else if (modo == 2) {
        while (1) {
            imprimirTabuleiro(&jogo);
            jogadaJogador(&jogo, jogo.jogador1);
            if (verificarVencedor(&jogo) != 0) {
                break;
            }
            imprimirTabuleiro(&jogo);
            jogadaJogador(&jogo, jogo.jogador2);
            if (verificarVencedor(&jogo) != 0) {
                break;
            }
        }
    } else {
        puts("Modo de Jogo Inválido!!!");
        return 0;
    }
    imprimirTabuleiro(&jogo);
    int resultado = verificarVencedor(&jogo);
    if (resultado == 1) {
        printf("Jogador X ganhou!\n");
    } else if (resultado == -1) {
        printf("Jogador O ganhou!\n");
    } else {
        printf("Empate!\n");
    }

    liberarTabuleiro(&jogo);
    return 0;
}