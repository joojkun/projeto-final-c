#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funcoes_desenhos.h"
#ifdef _WIN32 
    #include <Windows.h> 
    #define LIMPA "cls"
#else 
    #include <unistd.h> 
    #define LIMPA "clear"
#endif

typedef struct {
  int modo, modoInv; // Modo da figura principal e invasora
  char figura, figuraInv; // Forma da figura principal
  int locX, locY, locXInv, locYInv; // Localização da figura
  int linhas, colunas; // Tamanho da matriz
  int numGeracoes; // Numero de gerações que serão simuladas
  int inicioInv; // Quando a célula invasora irá surgir
  char vivo, morto;
  char **matriz;
  char **matrizCopia;
}MatrizConfig;

int contVivo(char *vet, char charVivo);
void montaMatrizArquivo(char ***matriz, char vivo, int locX, int locY);
int analisaVizinho(int i, int j, char ***matOriginal, char charVivo, char charMorto, int linha, int coluna);
void evoluiGeracao(char ***matOriginal, char ***matCopia, char charVivo, char charMorto, int linha, int coluna);
void simulaGeracoes(MatrizConfig matCfg, char vivo, char morto);
void configuraMatriz(int modo, char figura, char ***matriz, char vivo, int locX, int locY);

void montaMatrizArquivo(char ***matriz, char vivo, int locX, int locY) {
    // Linha do arquivo
    char line[200];
    char *token;
    // Números escritos no arquvio
    int numero;
    // Linha da matriz
    int linhaMatriz = locX;

    // Arquivo contendo a configuração da matriz
    FILE *arquivo = fopen("desenho.csv", "r");

    // Caso não consiga abrir o arquivo
    if (arquivo == NULL) {
        perror("Unable to read the file");
        exit(1);
    }

    // Lendo as linhas do arquivo
    while(fgets(line, sizeof(line), arquivo)) {
        // Separando a linha pelas virgulas
        token = strtok(line, ",");
        // Lendo até que não encontre mais nada na linha
        while(token != NULL) {
            // Convertendo string para inteiro
            numero = atoi(token);
            numero --;
            (*matriz)[linhaMatriz][numero + locY] = vivo;
            token = strtok(NULL, ",");
        }
        linhaMatriz ++;
    }
    // Fechando o arquivo
    fclose(arquivo);
}

// Analisando se o caractére é vivo ou morto
int contVivo(char *vet, char charVivo) {
    // Quantidade de caracteres vivos
    int cont = 0;
    for (int i = 0; i < 8; i ++)
        if (vet[i] == charVivo) {
            cont ++;
        }
    free(vet);
    return cont;
}

int analisaVizinho(int i, int j, char *** matOriginal, char charVivo, char charMorto, int linha, int coluna) {
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
    if (j + 1 < coluna) { vet[0] = (*matOriginal)[i][j + 1]; }
    // Vizinho na diagonal inferior direita
    if (i + 1 < linha && j + 1 < coluna) { vet[1] = (*matOriginal)[i + 1][j + 1]; }
    // Vizinho abaixo
    if (i + 1 < linha) { vet[2] = (*matOriginal)[i + 1][j]; }
    // Vizinho na diagonal inferior esquerda
    if (i + 1 < linha && j - 1 >= 0) { vet[3] = (*matOriginal)[i + 1][j - 1]; }
    // Vizinho a esquerda
    if (j - 1 >= 0) { vet[4] = (*matOriginal)[i][j - 1]; }
    // Vizinho na diagonal superior esquerda
    if (i - 1 >= 0 && j - 1 >= 0) { vet[5] = (*matOriginal)[i - 1][j - 1]; }
    // Vizinho acima
    if (i - 1 >= 0) { vet[6] = (*matOriginal)[i - 1][j]; }
    // Vizinho na diagonal superior direita
    if (i - 1 >= 0 && j + 1 < coluna) { vet[7] = (*matOriginal)[i - 1][j + 1]; }

    // Calculando a quantidade de celulas vivas
    return contVivo(vet, charVivo);
}

void evoluiGeracao(char ***matOriginal, char ***matCopia, char charVivo, char charMorto, int linha, int coluna) {
    // Número de células vizinhas vivas de outra célula
    int vizinhoVivo = 0;
    // Celula atual
    char celula;
    // Passando pelas células da matriz para decidir se a celula vive ou morre
    for (int i = 0; i < linha; i ++) {
        for (int j = 0; j < coluna; j ++) {
            celula = (*matOriginal)[i][j];
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
            (*matCopia)[i][j] = celula;
        }
    }
}

void configuraMatriz(int modo, char figura, char ***matriz, char vivo, int locX, int locY) {
    // Vida eterna
    if (modo == 1) {
        // Bloco
        if (figura == 'A') {
            bloco(matriz, locX, locY, vivo);
        }
        else if (figura == 'B') {  // Bote
            bote(matriz, locX, locY, vivo);
        }
        else {  // Comilão
            comilao(matriz, locX, locY, vivo);
        }
    }
    // Osciladores
    else if (modo == 2) {
        // Blinker
        if (figura == 'A') {       
            blinker(matriz, locX, locY, vivo);
        }
        else if (figura == 'B') {  // Sapo
            frog(matriz, locX, locY, vivo);
        }
    }
    // Naves espaciais
    else if (modo == 3) {
        // Glider
        if (figura == 'A') {       
            glider(matriz, locX, locY, vivo);
        }
        else if (figura == 'B') {  // LWSS
            lwss(matriz, locX, locY, vivo);
        }
    }
    // Lendo a partir de um arquivo .csv
    else {
        montaMatrizArquivo(matriz, vivo, locX, locY);
    }
}

void simulaGeracoes(MatrizConfig matCfg, char vivo, char morto) {
    int locx = matCfg.locXInv;
    int locy = matCfg.locXInv;
    // Criando a matriz e preenchendo com zero
    criaMatriz(&matCfg.matriz, matCfg.linhas, matCfg.colunas, morto);
    criaMatriz(&matCfg.matrizCopia, matCfg.linhas, matCfg.colunas, morto);    
    configuraMatriz(matCfg.modo, matCfg.figura, &matCfg.matriz, matCfg.vivo, matCfg.locX, matCfg.locY);
    // Caso os invasores devam ser adicionados já na primeira geração
    if (matCfg.inicioInv == 1) {
      configuraMatriz(matCfg.modoInv, matCfg.figuraInv, &matCfg.matriz, matCfg.vivo, locx, locy);
    }

    // Imprimindo a matriz
    sleep(1);
	  system(LIMPA);
    imprimeMatriz(&matCfg.matriz, matCfg.linhas, matCfg.colunas);    

    for (int i = 2; i <= matCfg.numGeracoes; i ++) {
      // Espera um segundo e limpa a tela
      sleep(1);
	  system(LIMPA);
      // Modificando matriz cópia
      if (i % 2 == 0) {
        evoluiGeracao(&matCfg.matriz, &matCfg.matrizCopia, vivo, morto, matCfg.linhas, matCfg.colunas);
        // Caso esteja na hora de adicionar a célula invasora
        if (i == matCfg.inicioInv) {
            configuraMatriz(matCfg.modoInv, matCfg.figuraInv, &matCfg.matrizCopia, matCfg.vivo, locx, locy);
        }
        imprimeMatriz(&matCfg.matrizCopia, matCfg.linhas, matCfg.colunas); // Imprimindo matriz cópia

      }
      // Modificando matriz original
      else {
        evoluiGeracao(&matCfg.matrizCopia, &matCfg.matriz, vivo, morto, matCfg.linhas, matCfg.colunas);
        // Caso esteja na hora de adicionar a célula invasora
        if (i == matCfg.inicioInv) {
            configuraMatriz(matCfg.modoInv, matCfg.figuraInv, &matCfg.matriz, matCfg.vivo, locx, locy);
        }
        imprimeMatriz(&matCfg.matriz, matCfg.linhas, matCfg.colunas); // Imprimindo matriz original
      }
    }
    limpaMatriz(&matCfg.matriz, matCfg.linhas);
    limpaMatriz(&matCfg.matrizCopia, matCfg.linhas);
}