
void criaMatriz(char*** mat, int numeroLinha, int numeroColuna)
{
    int i, j;
    *mat = (char **) malloc (numeroLinha * sizeof(char *));
    for (i = 0;i < numeroColuna ;i++)
    (*mat)[i] = (char *) malloc (numeroColuna * sizeof(char));
    for (i=0;i<numeroLinha;i++){
        for(j=0;j<numeroColuna;j++){
            (*mat)[i][j]='0';}}

}
void imprimeMatriz(char **mat, int numeroLinha, int numeroColuna)
{
    int i, j;
    for (i=0;i<numeroLinha;i++){
        for(j=0;j<numeroColuna;j++){
            printf("%c", mat[i][j]);}
            printf("\n");}
}
void limpaMatriz(char **mat, int numeroLinha)
{
    int i;
    for (i = 0; i < numeroLinha; i++ )
    free(mat[i]);
    free(mat);
}

void bloco(char **mat, int posicao1, int posicao2)
{
    int i, j;
    for (i=0;i<2;i++){
        for(j=0;j<2;j++){
            mat[i+linha][j+coluna]='X';}}
}
void bote(char **mat, int linha, int coluna)
{

    int i;
    for (i=0;i<2;i++)
        mat[linha][coluna+i]='X';
    for (i=0;i<2;i++)
        mat[linha+1][coluna-1+(3*i)]='X';
    for (i=0;i<2;i++)
        mat[linha+2][coluna+i]='X';

}
void comilao(char **mat, int linha, int coluna)
{
    int i;
    for (i=0;i<2;i++)
        mat[linha][coluna+i]='X';
    mat[linha+1][coluna]='X';
    for (i=0;i<3;i++)
        mat[linha+2][coluna+1+i]='X';
    mat [linha+3][coluna+3]='X';


}

void blinker(char **mat, int linha, int coluna)
{
    int i;
    for (i=0;i<3;i++)
        mat[linha][coluna+i]='X';

}
void frog(char **mat, int linha, int coluna)
{
    int i;
    for (i=0;i<3;i++)
        mat[linha][coluna+i]='X';
    for (i=0;i<3;i++)
        mat[linha+1][coluna+i-1]='X';

}
void glider(char **mat, int linha, int coluna)
{
   int i;
    for (i=0;i<3;i++)
        mat[linha][coluna+i]='X';
    mat[linha+1][coluna]='X';
    mat[linha+2][coluna+1]='X';
}

void lwss(char **mat, int linha, int coluna)
{
   
    int i;
    for (i=0;i<2;i++)
        mat[linha][coluna+(3*i)]='X';
    for (i=0;i<3;i++)
        mat[linha+1+i][coluna-1]='X';
    for (i=0;i<3;i++)
        mat[linha+3][coluna+i]='X';
    mat[linha+2][coluna+3]='X';
    }

void acorn (char **mat, int linha, int coluna)
{
    int i;
    mat[linha][coluna]='X';
    mat[linha+1][coluna+2]='X';
    for (i=0;i<2;i++)
        mat[linha+2][coluna-1+i]='X';
    for (i=0;i<3;i++)
        mat[linha+2][coluna+3+i]='X';

}
void diehard (char **mat, int linha, int coluna)
{
    int i;
    mat[linha-1][coluna+6]='X';
    for (i=0;i<2;i++)
        mat[linha][coluna+i]='X';
    mat[linha+1][coluna+1]='X';
    for (i=0;i<3;i++)
        mat [linha+1][coluna+i+5]='X';

}
void tetris (char **mat, int linha, int coluna)
{
    int i;
    mat [linha-1][coluna+2]='X';
    for (i=0;i<3;i++)
        mat [linha][coluna+i]='X';
    mat[linha+1][coluna+1]='X';

}

void transformMatriz(char **mat, int numLin, int numCol, char celulaViva, char celulaMorta)
{
    int i, j;
        for (i=0;i<numLin;i++){
        for(j=0;j<numCol;j++){
            if(mat[i][j]=='0')
                mat[i][j]=celulaMorta;
                else mat[i][j]=celulaViva;
            }}
}
