#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "funcoes.h"

// Analisando se o caractére é vivo ou morto
int contVivo(char *vet, char charVivo) {
    // Quantidade de caracteres vivos
    int cont = 0;
    for (int i = 0; i < 8; i ++)
        if (vet[i] == charVivo) {
            cont ++;
        }
    return cont;
}

int analisaVizinho(int i, int j, char ** matOriginal, char charVivo, char charMorto, int linha, int coluna) {
    // Vetor de caracteres
    char *vet;
    vet = (char *)malloc(8*(sizeof(char)));
    // Preenchendo o vetor com o caractere correspondente a celula morta
    if (charMorto != '0') {
        for (int valor = 0; valor < i; valor ++) {
            vet[valor] = charMorto;
        }
    }

    // Analisando os vizinhos da celula
    // Vizinho a direita
    if (j + 1 < coluna) { vet[0] = matOriginal[i][j + 1]; }
    // Vizinho na diagonal inferior direita
    if (i + 1 < linha && j + 1 < coluna) { vet[1] = matOriginal[i + 1][j + 1]; }
    // Vizinho abaixo
    if (i + 1 < linha) { vet[2] = matOriginal[i + 1][j]; }
    // Vizinho na diagonal inferior esquerda
    if (i + 1 < linha && j - 1 >= 0) { vet[3] = matOriginal[i + 1][j - 1]; }
    // Vizinho a esquerda
    if (j - 1 >= 0) { vet[4] = matOriginal[i][j - 1]; }
    // Vizinho na diagonal superior esquerda
    if (i - 1 >= 0 && j - 1 >= 0) { vet[5] = matOriginal[i - 1][j - 1]; }
    // Vizinho acima
    if (i - 1 >= 0) { vet[6] = matOriginal[i - 1][j]; }
    // Vizinho na diagonal superior direita
    if (i - 1 >= 0 && j + 1 < coluna) { vet[7] = matOriginal[i - 1][j + 1]; }

    // Calculando a quantidade de celulas vivas
    return contVivo(vet, charVivo);
}

void evoluiGeracao(char **matOriginal, char **matCopia, char charVivo, char charMorto, int linha, int coluna) {
    // Número de células vizinhas vivas de outra célula
    int vizinhoVivo = 0;
    // Celula atual
    char celula;
    // Passando pelas células da matriz para decidir se a celula vive ou morre
    for (int i = 0; i < linha; i ++) {
        for (int j = 0; j < coluna; j ++) {
            celula = matOriginal[i][j];
            vizinhoVivo = analisaVizinho(i, j, matOriginal, charVivo, charMorto, linha, coluna);
            // Definindo se a celula ficará viva ou morta
            if (celula == charVivo) {
                // Uma célula viva permanece viva se tiver 2 ou 3 células vizinhas vivas
                if (vizinhoVivo == 2 || vizinhoVivo == 3) {
                    celula = charVivo;
                }
                // Uma célula viva, com menos de 2 ou mais de 3 células vizinhas vivas morre
                else if (vizinhoVivo < 2 || vizinhoVivo > 3) {
                    celula = charMorto;
                }
            }
            // Uma célula morta ganha vida se tiver exatamente 3 células vizinhas vivas
            else if (celula == charMorto && vizinhoVivo == 3) {
                celula = charVivo;
            }
            printf("%c ", celula);
            matCopia[i][j] = celula;
        }
        printf("\n");
    }
}

int main()
{
    // Matriz Original
    char **matriz;
    // Matriz Cópia
    char **matrizCopia;
    // Número de linhas e colunas
    int nL, nC;
    // Caractéres vivo e morto
    char vivo = '0', morto = '.';
    // Lendo as dimensões da matriz
    nL = nC = 15;
    // Criando a matriz e preenchendo com zero
    matriz = criaMatriz(matriz, nL, nC, morto);
    matrizCopia = criaMatriz(matrizCopia, nL, nC, morto);
    // Imprimindo a matriz
    bloco(matriz, 5, 5, vivo);
    bote(matriz, 3, 5, vivo);
    comilao(matriz, 7, 5, vivo);
    blinker(matriz, 9, 5, vivo);
    frog(matriz, 6, 5, vivo);
    glider(matriz, 12, 5, vivo);
    lwss(matriz, 5, 5, vivo);
    acorn(matriz, 10, 5, vivo);
    diehard(matriz, 9, 2, vivo);
    tetris(matriz, 10, 5, vivo);
    sleep(1);
    system("clear");
    imprimeMatriz(matriz, nL, nC);

    for (int i = 0; i < 100; i ++) {
      sleep(1);
      system("clear");
      if (i % 2 == 0) {
        evoluiGeracao(matriz, matrizCopia, vivo, morto, nL, nC);
      }
      else {        
        evoluiGeracao(matrizCopia, matriz, vivo, morto, nL, nC);
      }
    }

    return 0;
}
