#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"
#define LIN 5
#define COL 4
#define VIVO '*'
#define MORTO 'O'

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
    char vet[8] = {'0', '0', '0', '0', '0', '0', '0'};
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
/*
int main() {
     // Inicializando biblioteca rand
    srand(time(NULL));
    // Número aleatória que selecionará 0 ou X
    int randNumber;
    // Matriz de char
    char mat[LIN][COL] = {{MORTO, MORTO, MORTO, VIVO},
     {VIVO, VIVO, VIVO, MORTO}, {VIVO, MORTO, VIVO, MORTO},
     {MORTO, MORTO, VIVO, MORTO}, {MORTO, VIVO, MORTO, MORTO}};
    char matCopia[LIN][COL];


    // Preenchendo a matriz
    for (int i = 0; i < LIN; i ++) {
        for (int j = 0; j < COL; j ++) {
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < 10; i ++) {
        mat[LIN][COL] = evoluiGeracao(mat, matCopia, VIVO, MORTO);
    } 

    return 0;
}

*/
int main()
{
    // Matriz Original
    char **matriz;
    // Matriz Cópia
    char **matrizCopia;
    // Número de linhas e colunas
    int nL, nC;
    // Lendo as dimensões da matriz
    printf("Digite as dimensoes da matriz: ");
    scanf("%d %d", &nL, &nC);
    // Criando a matriz e preenchendo com zero
    criaMatriz(&matriz, nL, nC);
    // Criando o padrão sapo
    frog(matriz);
    // Imprimindo a matriz
    imprimeMatriz(matriz, nL, nC);
    
    // Evoluindo as gerações
    for (int i = 0; i < 3; i ++) {
        printf("\n");
        if (i % 2 == 0) {
            evoluiGeracao(matriz, matrizCopia, VIVO, MORTO, nL, nC);
        }
        else {
            
            evoluiGeracao(matrizCopia, matriz, VIVO, MORTO, nL, nC);
        }
    }
    imprimeMatriz(matriz, nL, nC);
    limpaMatriz(matriz, nL);

}
