#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 5

// Analisando se o caractére é vivo ou morto
int contVivo(char vet[8]) {
    // Quantidade de caracteres vivos
    int cont = 0;
    for (int i = 0; i < 8; i ++)
        if (vet[i] == 'X') {
            cont ++;
        }
    return cont;
}

int analisaVizinho(int i, int j, char matOriginal[TAM][TAM]) {
    // Vetor de caracteres
    char vet[8] = {'0', '0', '0', '0', '0', '0', '0', '0'};

    // Analisando os vizinhos da celula
    // Vizinho a direita
    if (j + 1 < TAM) { vet[0] = matOriginal[i][j + 1]; }
    // Vizinho na diagonal inferior direita
    if (i + 1 < TAM && j + 1 < TAM) { vet[1] = matOriginal[i + 1][j + 1]; }
    // Vizinho abaixo
    if (i + 1 < TAM) { vet[2] = matOriginal[i + 1][j]; }
    // Vizinho na diagonal inferior esquerda
    if (i + 1 < TAM && j - 1 >= 0) { vet[3] = matOriginal[i + 1][j - 1]; }
    // Vizinho a esquerda
    if (j - 1 >= 0) { vet[4] = matOriginal[i][j - 1]; }
    // Vizinho na diagonal superior esquerda
    if (i - 1 >= 0 && j - 1 >= 0) { vet[5] = matOriginal[i - 1][j - 1]; }
    // Vizinho acima
    if (i - 1 >= 0) { vet[6] = matOriginal[i - 1][j]; }
    // Vizinho na diagonal superior direita
    if (i - 1 >= 0 && j + 1 < TAM) { vet[7] = matOriginal[i - 1][j + 1]; }

    // Calculando a quantidade de celulas vivas
    return contVivo(vet);
}

void evoluiGeracao(char matOriginal[TAM][TAM], char matCopia[TAM][TAM], int tam) {
    // Número de células vizinhas vivas de outra célula
    int vizinhoVivo = 0;
    // Celula atual
    char celula;
    // Passando pelas células da matriz para decidir se a celula vive ou morre
    for (int i = 0; i < tam; i ++) {
        for (int j = 0; j < tam; j ++) {
            celula = matOriginal[i][j];
            vizinhoVivo = analisaVizinho(i, j, matOriginal);
            // Definindo se a celula ficará viva ou morta
            if (celula == 'X') {
                // Uma célula viva permanece viva se tiver 2 ou 3 células vizinhas vivas
                if (vizinhoVivo == 2 || vizinhoVivo == 3) {
                    celula = 'X';
                }
                // Uma célula viva, com menos de 2 ou mais de 3 células vizinhas vivas morre
                else if (vizinhoVivo < 2 || vizinhoVivo > 3) {
                    celula = '0';
                }
            }
            // Uma célula morta ganha vida se tiver exatamente 3 células vizinhas vivas
            else if (celula == '0' && vizinhoVivo == 3) {
                celula = 'X';
            }
            printf("%c ", celula);
            matCopia[i][j] = celula;
        }
        printf("\n");
    }
}

int main() {
    // Inicializando biblioteca rand
    srand(time(NULL));
    // Número aleatória que selecionará 0 ou X
    int randNumber;
    // Matriz de char
    char mat[TAM][TAM];
    char matCopia[TAM][TAM];


    // Preenchendo a matriz
    for (int i = 0; i < TAM; i ++) {
        for (int j = 0; j < TAM; j ++) {
            randNumber = rand() % 2;
            if (randNumber == 1) {
                mat[i][j] = '0';
            }
            else {
                mat[i][j] = 'X';
            }
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    evoluiGeracao(mat, matCopia, TAM);

    return 0;
}
