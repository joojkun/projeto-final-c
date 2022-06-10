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

void vidaEterna1(char **mat)
{
    int posicao1, posicao2,i,j;
    printf("A figura sera assim: \n");
    printf("XX \n");
    printf("XX \n");
    printf("Em que posicao deseja colocar a primeira populacao (considere a primeira como a primeira da esquerda pra direita e de cima para baixo) \n");
    printf("Digite primeiro a Linha e depois a Coluna \n");
    scanf("%d%d", &posicao1,&posicao2);
     for (i=0;i<2;i++){
        for(j=0;j<2;j++){
            mat[i+posicao1-1][j+posicao2-1]='X';}}
}
void vidaEterna2(char **mat)
{
   int posicao1, posicao2,i;
    printf("A figura sera assim: \n");
    printf("  XX \n");
    printf("X    X \n");
    printf("  XX \n");
    printf("Em que posicao deseja colocar a primeira populacao (considere a primeira como a primeira da esquerda pra direita e de cima para baixo) \n");
    printf("Digite primeiro a Linha e depois a Coluna \n");
    scanf("%d%d", &posicao1,&posicao2);
    posicao1=posicao1-1;
    posicao2=posicao2-1;
    for (i=0;i<2;i++)
        mat[posicao1][posicao2+i]='X';
    for (i=0;i<2;i++)
        mat[posicao1+1][posicao2-1+(3*i)]='X';
    for (i=0;i<2;i++)
        mat[posicao1+2][posicao2+i]='X';

}
void blinker(char **mat)
{
   int posicao1, posicao2,i;
    printf("A figura sera assim: \n");
    printf("XXX \n");
    printf("Em que posicao deseja colocar a primeira populacao (considere a primeira como a primeira da esquerda pra direita e de cima para baixo) \n");
    printf("Digite primeiro a Linha e depois a Coluna \n");
    scanf("%d%d", &posicao1,&posicao2);
    posicao1=posicao1-1;
    posicao2=posicao2-1;
    for (i=0;i<3;i++)
        mat[posicao1][posicao2+i]='X';

}
void frog(char **mat)
{
   int posicao1, posicao2,i;
    printf("A figura sera assim: \n");
    printf(" XXX \n");
    printf("XXX\n");
    printf("Em que posicao deseja colocar a primeira populacao (considere a primeira como a primeira da esquerda pra direita e de cima para baixo) \n");
    printf("Digite primeiro a Linha e depois a Coluna \n");
    scanf("%d%d", &posicao1,&posicao2);
    posicao1=posicao1-1;
    posicao2=posicao2-1;
    for (i=0;i<3;i++)
        mat[posicao1][posicao2+i]='X';
    for (i=0;i<3;i++)
        mat[posicao1+1][posicao2+i-1]='X';

}
void glider(char **mat)
{
   int posicao1, posicao2,i;
    printf("A figura sera assim: \n");
    printf("XXX \n");
    printf("X\n");
    printf(" X\n");
    printf("Em que posicao deseja colocar a primeira populacao (considere a primeira como a primeira da esquerda pra direita e de cima para baixo) \n");
    printf("Digite primeiro a Linha e depois a Coluna \n");
    scanf("%d%d", &posicao1,&posicao2);
    posicao1=posicao1-1;
    posicao2=posicao2-1;
    for (i=0;i<3;i++)
        mat[posicao1][posicao2+i]='X';
    mat[posicao1+1][posicao2]='X';
    mat[posicao1+2][posicao2+1]='X';
}

void lwss(char **mat)
{
   int posicao1, posicao2,i;
    printf("A figura sera assim: \n");
    printf(" X   X\nX\n");
    printf("X    X\n");
    printf("XXXX \n");
    printf("Em que posicao deseja colocar a primeira populacao (considere a primeira como a primeira da esquerda pra direita e de cima para baixo) \n");
    printf("Digite primeiro a Linha e depois a Coluna \n");
    scanf("%d%d", &posicao1,&posicao2);
    posicao1=posicao1-1;
    posicao2=posicao2-1;
    for (i=0;i<2;i++)
        mat[posicao1][posicao2+(3*i)]='X';
    for (i=0;i<3;i++)
        mat[posicao1+1+i][posicao2-1]='X';
    for (i=0;i<3;i++)
        mat[posicao1+3][posicao2+i]='X';
    mat[posicao1+2][posicao2+3]='X';
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
