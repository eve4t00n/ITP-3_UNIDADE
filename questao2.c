//N Rainhas
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void imprimirMapa(int **mapa, int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (mapa[i][j]) {
                printf("R ");
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
    printf("\n");
}
bool podeColocarRainha(int **mapa, int linha, int coluna, int N) {
    int i, j;
    // coluna
    for (i=0; i<linha; i++) {
        if (mapa[i][coluna]) {
            return false;
        }
    }
    // diag 1
    for (i=linha, j=coluna; i>=0 && j>=0; i--, j--){
        if (mapa[i][j]) {
            return false;
        }
    }
    // diag 2
    for (i=linha, j=coluna; i>=0 && j<N; i--, j++) {
        if (mapa[i][j]) {
            return false;
        }
    }
    return true;
}

bool nRainhas(int **mapa, int linha, int N) {
    if (linha >= N) {
        return true;
    }

    for (int coluna = 0; coluna<N; coluna++) {
        if (podeColocarRainha(mapa, linha, coluna, N)) {
            mapa[linha][coluna] = 1; //rainha

            if (nRainhas(mapa, linha + 1, N)) {
                return true;
            }

            mapa[linha][coluna] = 0; // 'backtrack' aqui a mágica ocorre, pois não satisfez o que era necessário
        }
    }

    return false;
}

int main() {
    int n;
    printf("Qual o tamanho nxn do tabuleiro deseja verificar uma posicao para n rainhas?: ");
    scanf("%d", &n);
    //alocar dinamicamente as linhas e colunas
    int **mapa = malloc(n * sizeof(int *));
    for (int i=0; i<n; i++) {
        mapa[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            mapa[i][j] = 0;
        }
    }
    if (nRainhas(mapa, 0, n)){
        imprimirMapa(mapa, n);
    } else{
        printf("Nao existe solucao para o tabuleiro dado!");
    }
    //importante para liberar espaço depois do fim da compilação do código
    for (int i=0; i<n; i++) {
        free(mapa[i]);
    }
    free(mapa);

    return 0;
}